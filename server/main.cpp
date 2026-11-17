// Party Board netplay relay server.
//
// Clients create or join 4-letter rooms. When the host starts a game, the server sends the
// settings to everyone, then for every frame collects each human port's controller state and
// broadcasts the bundle once all of them have arrived (lockstep). Clients report periodic
// checksums; the server compares them and announces a desync. No game code runs here.

#include "netplay/protocol.h"

#include <enet/enet.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

namespace {

constexpr uint32_t kMaxFramesAhead = 600; // reject input this far past the oldest pending frame
constexpr size_t kMaxClients = 256;

void logf(const char *fmt, ...) {
    char stamp[32];
    const std::time_t now = std::time(nullptr);
    std::strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", std::gmtime(&now));
    std::printf("%s ", stamp);
    va_list args;
    va_start(args, fmt);
    std::vprintf(fmt, args);
    va_end(args);
    std::printf("\n");
    std::fflush(stdout);
}

struct Room;

struct Client {
    uint8_t id = 0;
    ENetPeer *peer = nullptr;
    bool helloed = false;
    std::string name;
    std::string build;
    uint8_t padSize = 0;
    Room *room = nullptr;
    uint32_t lastSentRtt = 0; // the ping the last ROOM_STATE showed
    // Stutter tracking (NET_STATS). How much later than the first player's this player's input usually arrives
    // (ms, slow average), and what happened since the last NET_STATS.
    float lateBaseline = 0.f;
    uint16_t lateFrames = 0, worstLateMs = 0;
    uint16_t slowFrames = 0, netStalls = 0, worstFrameMs = 0; // summed PERF reports
};

struct PendingFrame {
    uint8_t have = 0; // bit per port whose input arrived
    std::array<uint32_t, PB_NET_MAX_PLAYERS> arrivedMs{}; // when each port's input arrived (enet time)
    std::array<std::array<uint8_t, PB_NET_MAX_PAD_SIZE>, PB_NET_MAX_PLAYERS> pads{};
};

struct Room {
    std::string code;
    std::string build;
    uint8_t padSize = 0;
    uint8_t hostId = 0;
    std::vector<uint8_t> members; // client ids, join order
    // Lobby seating: who plays each port and with which character. Every member owns exactly one
    // port; the rest are CPUs. People always have a character; a CPU may be PB_NET_CHAR_AUTO.
    std::array<uint8_t, PB_NET_MAX_PLAYERS> slotOwner{PB_NET_PORT_CPU, PB_NET_PORT_CPU, PB_NET_PORT_CPU, PB_NET_PORT_CPU};
    std::array<uint8_t, PB_NET_MAX_PLAYERS> slotChar{PB_NET_CHAR_AUTO, PB_NET_CHAR_AUTO, PB_NET_CHAR_AUTO, PB_NET_CHAR_AUTO};
    // A continued game (SET_CONTINUE): characters stay with their ports, and seats go back to the people who
    // played them (by name).
    bool continuing = false;
    std::array<std::string, PB_NET_MAX_PLAYERS> savedName; // "" for a seat a CPU played
    bool inGame = false;
    PbNetSettings settings{};
    uint8_t humanMask = 0;
    uint32_t nextFrame = 0;
    uint32_t lastProgressMs = 0;  // when the last frame went out (or the game started)
    uint32_t lastWaitingMs = 0;   // when the last WAITING went out
    uint32_t lastLobbyStateMs = 0; // lobby: when ROOM_STATE (with fresh pings) last went out
    uint32_t lastStatsMs = 0;      // in game: when NET_STATS last went out
    std::map<uint32_t, PendingFrame> frames;
    std::map<uint32_t, std::map<uint8_t, uint32_t>> checksums;
    // Who played each port in the running game ("" for a CPU), kept for people coming back mid-game, and
    // the host's name (the host role goes back to them after a reload).
    std::array<std::string, PB_NET_MAX_PLAYERS> gameNames;
    std::string hostName;
    // Members who joined while the game runs, waiting for the reload that seats them: client id -> port.
    std::map<uint8_t, int> waiting;
    // Reloading: the game ended at a save point so everyone can restart from it with the returners seated.
    bool reloading = false;
    uint32_t reloadStartMs = 0;
    uint8_t reloadExpect = 0; // ports whose people we wait for before starting
    std::vector<uint8_t> reloadState;
    // Desync recovery: the board state at the last save point every player agreed on (the game's starting state
    // until the first one; empty = a new game, which starts over), and how many desyncs in a row restarted from it.
    std::vector<uint8_t> recoveryState;
    int desyncRestarts = 0;
    // The lobby's continuing/savedName while a reload borrows them to seat people by name.
    bool lobbyContinuing = false;
    std::array<std::string, PB_NET_MAX_PLAYERS> lobbySavedName;
    std::map<uint32_t, std::map<uint8_t, std::vector<uint8_t>>> saveReports; // frame -> client -> state
};

constexpr int kMaxDesyncRestarts = 2;

std::map<uint8_t, std::unique_ptr<Client>> gClients;
std::map<std::string, std::unique_ptr<Room>> gRooms;
std::mt19937 gRng{std::random_device{}()};

void send(Client &c, uint8_t channel, const PbNetWriter &w) {
    if (w.overflow) {
        logf("BUG: outgoing message overflowed its buffer");
        return;
    }
    ENetPacket *packet = enet_packet_create(w.data, w.pos, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(c.peer, channel, packet);
}

void sendError(Client &c, PbNetError code, const char *message) {
    uint8_t buf[256];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_ERROR);
    pbw_u8(&w, code);
    pbw_str(&w, message, 200);
    send(c, PB_NET_CHANNEL_CONTROL, w);
}

void broadcast(Room &room, uint8_t channel, const PbNetWriter &w) {
    for (uint8_t id : room.members) {
        send(*gClients.at(id), channel, w);
    }
}

// To the players of the running game only (not those waiting to rejoin it).
void broadcastGame(Room &room, uint8_t channel, const PbNetWriter &w) {
    for (uint8_t id : room.members) {
        if (!room.waiting.count(id)) send(*gClients.at(id), channel, w);
    }
}

size_t playingCount(const Room &room) { return room.members.size() - room.waiting.size(); }

const char *const kCharNames[PB_NET_MAX_CHARS] = {"Mario", "Luigi", "Peach", "Yoshi",
                                                  "Wario", "Donkey Kong", "Daisy", "Waluigi"};

std::array<uint8_t, PB_NET_MAX_PLAYERS> resolvedChars(const Room &room) {
    std::array<uint8_t, PB_NET_MAX_PLAYERS> out{};
    pb_resolve_chars(room.slotChar.data(), out.data());
    return out;
}

int portOf(const Room &room, uint8_t id) {
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room.slotOwner[port] == id) return port;
    }
    return -1;
}

// Lowest character id no slot holds explicitly (AUTO CPUs give theirs up).
uint8_t firstFreeChar(const Room &room) {
    for (uint8_t c = 0; c < PB_NET_MAX_CHARS; c++) {
        if (std::find(room.slotChar.begin(), room.slotChar.end(), c) == room.slotChar.end()) return c;
    }
    return 0; // unreachable: 4 slots, 8 characters
}

// A newcomer takes the lowest CPU port and the first free character. In a continued game they take back the seat
// saved under their name if it is free, else the lowest free seat a CPU played (else any free one), and the
// seat's character stays.
void seat(Room &room, uint8_t id) {
    if (room.continuing) {
        const std::string &name = gClients.at(id)->name;
        for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            if (room.slotOwner[port] == PB_NET_PORT_CPU && !room.savedName[port].empty() && room.savedName[port] == name) {
                room.slotOwner[port] = id;
                return;
            }
        }
        // Others prefer a seat a CPU played, so a saved player who hasn't come back yet still finds theirs free.
        for (int pass = 0; pass < 2; pass++) {
            for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
                if (room.slotOwner[port] == PB_NET_PORT_CPU && (pass == 1 || room.savedName[port].empty())) {
                    room.slotOwner[port] = id;
                    return;
                }
            }
        }
        return;
    }
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room.slotOwner[port] != PB_NET_PORT_CPU) continue;
        room.slotOwner[port] = id;
        room.slotChar[port] = PB_NET_CHAR_AUTO; // the CPU's pick is released first
        room.slotChar[port] = firstFreeChar(room);
        return;
    }
}

void sendRoomState(Room &room) {
    room.lastLobbyStateMs = enet_time_get();
    uint8_t buf[512];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_ROOM_STATE);
    pbw_bytes(&w, room.code.data(), PB_NET_ROOM_CODE_LEN);
    pbw_u8(&w, room.hostId);
    pbw_u8(&w, static_cast<uint8_t>(room.members.size()));
    for (uint8_t id : room.members) {
        pbw_u8(&w, id);
        pbw_str(&w, gClients.at(id)->name.c_str(), PB_NET_MAX_NAME);
        Client &member = *gClients.at(id);
        member.lastSentRtt = member.peer->roundTripTime;
        pbw_u16(&w, static_cast<uint16_t>(std::min<enet_uint32>(member.lastSentRtt, 65535)));
    }
    const auto chars = resolvedChars(room);
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        pbw_u8(&w, room.slotOwner[port]);
        pbw_u8(&w, chars[port]);
        pbw_u8(&w, room.slotChar[port] == PB_NET_CHAR_AUTO ? 1 : 0);
    }
    pbw_u8(&w, room.continuing ? 1 : 0);
    if (room.continuing) {
        for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) pbw_str(&w, room.savedName[port].c_str(), PB_NET_MAX_NAME);
    }
    pbw_u8(&w, room.reloading ? PB_ROOM_RELOADING : room.inGame ? PB_ROOM_IN_GAME : PB_ROOM_LOBBY);
    broadcast(room, PB_NET_CHANNEL_CONTROL, w);
}

std::string newRoomCode() {
    static const char letters[] = "ABCDEFGHJKLMNPQRSTUVWXYZ"; // no I/O, easy to read aloud
    std::uniform_int_distribution<int> pick(0, sizeof(letters) - 2);
    for (;;) {
        std::string code;
        for (int i = 0; i < PB_NET_ROOM_CODE_LEN; i++) code += letters[pick(gRng)];
        if (!gRooms.count(code)) return code;
    }
}

void endGame(Room &room, PbNetEndReason reason, uint8_t who) {
    uint8_t buf[8];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_GAME_ENDED);
    pbw_u8(&w, reason);
    pbw_u8(&w, who);
    broadcastGame(room, PB_NET_CHANNEL_CONTROL, w);
    room.inGame = false;
    room.frames.clear();
    room.checksums.clear();
    logf("room %s: game ended (reason %d)", room.code.c_str(), reason);
    if (!room.waiting.empty()) {
        room.waiting.clear(); // anyone waiting to rejoin is now just in the room's lobby
        sendRoomState(room);
    }
}

void flushFrames(Room &room);

// Mid-game disconnect: the player's ports stop being human from the next frame the server sends,
// so every client switches them to CPU on the same frame. The game ends only if no humans remain.
void dropFromGame(Room &room, Client &c) {
    uint8_t ports = 0;
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room.settings.portOwner[port] == c.id) ports |= static_cast<uint8_t>(1 << port);
    }
    room.humanMask &= static_cast<uint8_t>(~ports);
    for (auto &[frame, reports] : room.checksums) reports.erase(c.id);
    if (room.humanMask == 0) {
        endGame(room, PB_END_PLAYER_LEFT, c.id);
        return;
    }
    uint8_t buf[8];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_PLAYER_DROPPED);
    pbw_u8(&w, c.id);
    pbw_u32(&w, room.nextFrame);
    broadcastGame(room, PB_NET_CHANNEL_CONTROL, w);
    logf("room %s: %s dropped at frame %u; CPU takes ports 0x%x", room.code.c_str(), c.name.c_str(), room.nextFrame,
         ports);
    flushFrames(room); // frames that were only waiting on the dropped player can go now
}

void leaveRoom(Client &c) {
    Room *room = c.room;
    if (!room) return;
    c.room = nullptr;
    room->members.erase(std::find(room->members.begin(), room->members.end(), c.id));
    const bool wasWaiting = room->waiting.erase(c.id) > 0;
    if (const int port = portOf(*room, c.id); port >= 0) {
        room->slotOwner[port] = PB_NET_PORT_CPU;
        if (!room->continuing) room->slotChar[port] = PB_NET_CHAR_AUTO;
    }
    logf("room %s: %s left (%zu remaining)", room->code.c_str(), c.name.c_str(), room->members.size());
    if (room->members.empty() && !room->reloading) { // a reloading room waits for its players to come back
        logf("room %s: closed", room->code.c_str());
        gRooms.erase(room->code);
        return;
    }
    if (room->inGame && !wasWaiting) {
        dropFromGame(*room, c);
    }
    if (room->hostId == c.id && !room->members.empty()) {
        // The host should be someone playing (the host's game keeps the autosave).
        room->hostId = room->members.front();
        for (uint8_t id : room->members) {
            if (!room->waiting.count(id)) {
                room->hostId = id;
                break;
            }
        }
    }
    if (!room->members.empty()) sendRoomState(*room);
}

// Stutter tracking: a complete frame's inputs arrived at these times. The player whose input came last held everyone
// else's game up by the gap to the one before. Some players always arrive a little later than others (their game
// started later, or they are further from the server), so only lateness beyond their usual amount counts.
void noteLateness(Room &room, const PendingFrame &frame) {
    struct Arrival {
        Client *client;
        uint32_t ms;
    };
    std::vector<Arrival> arrivals;
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (!(room.humanMask & (1 << port))) continue;
        Client *c = gClients.count(room.settings.portOwner[port]) ? gClients.at(room.settings.portOwner[port]).get() : nullptr;
        if (!c) continue;
        auto same = std::find_if(arrivals.begin(), arrivals.end(), [c](const Arrival &a) { return a.client == c; });
        if (same == arrivals.end()) arrivals.push_back({c, frame.arrivedMs[port]});
        else same->ms = (std::max)(same->ms, frame.arrivedMs[port]);
    }
    if (arrivals.size() < 2) return;
    uint32_t first = arrivals[0].ms;
    for (const Arrival &a : arrivals) first = (std::min)(first, a.ms);
    Arrival *last = &arrivals[0];
    for (Arrival &a : arrivals) {
        if (static_cast<int32_t>(a.ms - last->ms) > 0) last = &a;
    }
    for (Arrival &a : arrivals) {
        const float lateness = static_cast<float>(a.ms - first);
        if (&a == last) {
            const float extra = lateness - a.client->lateBaseline;
            if (extra >= PB_NET_LATE_MS) {
                a.client->lateFrames++;
                a.client->worstLateMs = static_cast<uint16_t>(std::max<float>(a.client->worstLateMs, (std::min)(extra, 65535.f)));
            }
        }
        // Slow average; a spike only nudges it, so one long hitch doesn't hide the next.
        a.client->lateBaseline += ((std::min)(lateness, a.client->lateBaseline + PB_NET_LATE_MS) - a.client->lateBaseline) / 8.f;
    }
}

// Sends every frame whose inputs are complete, in order.
void flushFrames(Room &room) {
    for (;;) {
        auto it = room.frames.find(room.nextFrame);
        if (it == room.frames.end() || (it->second.have & room.humanMask) != room.humanMask) return;
        uint8_t buf[8 + PB_NET_MAX_PLAYERS * PB_NET_MAX_PAD_SIZE];
        PbNetWriter w;
        pbw_init(&w, buf, sizeof(buf));
        pbw_u8(&w, PB_MSG_FRAME);
        pbw_u32(&w, room.nextFrame);
        pbw_u8(&w, room.humanMask);
        pbw_u8(&w, room.waiting.empty() ? 0 : PB_FRAME_RELOAD);
        for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            if (room.humanMask & (1 << port)) pbw_bytes(&w, it->second.pads[port].data(), room.padSize);
        }
        broadcastGame(room, PB_NET_CHANNEL_INPUT, w);
        noteLateness(room, it->second);
        room.frames.erase(it);
        room.lastProgressMs = enet_time_get();
        room.nextFrame++;
    }
}

// Starts the room's game for everyone in it: seating and characters from the slots, the rest from s. state is
// the board state a continued (or reloaded) game starts from, empty for a new game.
void startGame(Room &room, PbNetSettings s, const std::vector<uint8_t> &state) {
    const auto chars = resolvedChars(room);
    std::copy(chars.begin(), chars.end(), s.chars);
    std::copy(room.slotOwner.begin(), room.slotOwner.end(), s.portOwner);
    uint8_t humanMask = 0;
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        const uint8_t owner = s.portOwner[port];
        if (owner != PB_NET_PORT_CPU) {
            humanMask |= static_cast<uint8_t>(1 << port);
            room.gameNames[port] = gClients.at(owner)->name;
        } else {
            // A saved seat nobody took keeps its name, so that person can still come back mid-game.
            room.gameNames[port] = room.continuing ? room.savedName[port] : "";
        }
    }
    // ...unless that person now plays another seat.
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (s.portOwner[port] != PB_NET_PORT_CPU) continue;
        for (int other = 0; other < PB_NET_MAX_PLAYERS; other++) {
            if (s.portOwner[other] != PB_NET_PORT_CPU && room.gameNames[other] == room.gameNames[port]) {
                room.gameNames[port].clear();
            }
        }
    }
    room.hostName = gClients.at(room.hostId)->name;
    room.settings = s;
    room.humanMask = humanMask;
    room.inGame = true;
    room.reloading = false;
    room.reloadState.clear();
    room.recoveryState = state; // a desync before the first save point restarts from here
    room.saveReports.clear();
    room.waiting.clear();
    room.nextFrame = 0;
    room.lastProgressMs = enet_time_get();
    room.lastStatsMs = room.lastProgressMs;
    room.frames.clear();
    room.checksums.clear();
    for (uint8_t id : room.members) {
        Client &m = *gClients.at(id);
        m.lateBaseline = 0.f;
        m.lateFrames = m.worstLateMs = m.slowFrames = m.netStalls = m.worstFrameMs = 0;
    }

    std::vector<uint8_t> buf(64 + state.size());
    PbNetWriter w;
    pbw_init(&w, buf.data(), buf.size());
    pbw_u8(&w, PB_MSG_GAME_START);
    pbw_settings(&w, &s);
    pbw_u16(&w, static_cast<uint16_t>(state.size()));
    pbw_bytes(&w, state.data(), state.size());
    broadcast(room, PB_NET_CHANNEL_CONTROL, w);
    logf("room %s: %s (board %u, %u turns, seed %u, delay %u, human ports 0x%x, chars %u,%u,%u,%u)",
         room.code.c_str(), state.empty() ? "game started" : "continued game started", s.board, s.turns, s.seed,
         s.inputDelay, humanMask, s.chars[0], s.chars[1], s.chars[2], s.chars[3]);
}

// A reloading room starts by itself once everyone it waits for is back, or at the timeout with whoever is.
void startReloadedIfReady(Room &room) {
    if (!room.reloading || room.members.empty()) return;
    uint8_t seated = 0;
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room.slotOwner[port] != PB_NET_PORT_CPU) seated |= static_cast<uint8_t>(1 << port);
    }
    const bool timedOut = enet_time_get() - room.reloadStartMs >= PB_NET_RELOAD_TIMEOUT_MS;
    if ((seated & room.reloadExpect) != room.reloadExpect && !timedOut) return;
    if (timedOut) logf("room %s: not everyone came back in time; starting with ports 0x%x", room.code.c_str(), seated);
    const std::vector<uint8_t> state = room.reloadState;
    startGame(room, room.settings, state);
    // Back to the lobby's own continue state (a continued game's room keeps showing its saved names).
    room.continuing = room.lobbyContinuing;
    room.savedName = room.lobbySavedName;
}

// Someone joins while the game runs: they get a CPU's seat (the one saved under their name if it is free) and
// wait. From now on every FRAME asks the players' games to reload at their next save point.
void joinRunningGame(Client &c, Room &room) {
    int port = -1;
    bool stillPlaying = false; // the server hasn't noticed this person's old connection drop yet
    for (uint8_t id : room.members) {
        stillPlaying |= !room.waiting.count(id) && gClients.at(id)->name == c.name;
    }
    const auto isFree = [&](int p) {
        if (room.humanMask & (1 << p)) return false;
        for (const auto &[id, claimed] : room.waiting) {
            if (claimed == p) return false;
        }
        return true;
    };
    for (int p = 0; p < PB_NET_MAX_PLAYERS && port < 0; p++) {
        if (isFree(p) && !room.gameNames[p].empty() && room.gameNames[p] == c.name) port = p;
    }
    if (port < 0 && stillPlaying) {
        return sendError(c, PB_ERR_IN_GAME, "the server still has you in this game; try again in a few seconds");
    }
    // Otherwise a seat a CPU played all along, then one whose player hasn't come back.
    for (int pass = 0; pass < 2 && port < 0; pass++) {
        for (int p = 0; p < PB_NET_MAX_PLAYERS && port < 0; p++) {
            if (isFree(p) && (pass == 1 || room.gameNames[p].empty())) port = p;
        }
    }
    if (port < 0) return sendError(c, PB_ERR_IN_GAME, "that room's game has no free seat");
    leaveRoom(c);
    room.members.push_back(c.id);
    room.waiting[c.id] = port;
    c.room = &room;
    logf("room %s: %s joined the running game for P%d; reloading at the next save point", room.code.c_str(),
         c.name.c_str(), port + 1);
    uint8_t buf[64];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_REJOINING);
    pbw_u8(&w, static_cast<uint8_t>(port));
    pbw_str(&w, c.name.c_str(), PB_NET_MAX_NAME);
    broadcastGame(room, PB_NET_CHANNEL_CONTROL, w);
    sendRoomState(room);
}

// End the running game and wait for everyone to come back (their games restart and rejoin by name), then start
// from state (empty: the game starts over).
void beginReload(Room &rm, std::vector<uint8_t> state, uint32_t frame) {
    rm.inGame = false;
    rm.reloading = true;
    rm.reloadStartMs = enet_time_get();
    rm.reloadState = std::move(state);
    rm.frames.clear();
    rm.checksums.clear();
    rm.saveReports.clear();
    rm.reloadExpect = rm.humanMask; // the people playing now restart and come back
    // The players leave the room (their games restart); those who waited stay, already in their seats.
    std::vector<uint8_t> stay;
    for (uint8_t id : rm.members) {
        if (rm.waiting.count(id)) {
            stay.push_back(id);
        } else {
            gClients.at(id)->room = nullptr;
        }
    }
    rm.members = stay;
    rm.lobbyContinuing = rm.continuing;
    rm.lobbySavedName = rm.savedName;
    rm.continuing = true;
    rm.slotOwner.fill(PB_NET_PORT_CPU);
    std::copy(rm.settings.chars, rm.settings.chars + PB_NET_MAX_PLAYERS, rm.slotChar.begin());
    for (const auto &[id, port] : rm.waiting) {
        rm.slotOwner[port] = id;
        rm.gameNames[port] = gClients.at(id)->name;
    }
    rm.savedName = rm.gameNames;
    rm.waiting.clear();
    if (!rm.members.empty()) rm.hostId = rm.members.front();
    logf("room %s: reloading from the save point at frame %u (%zu bytes); waiting for ports 0x%x", rm.code.c_str(),
         frame, rm.reloadState.size(), rm.reloadExpect);
    if (!rm.members.empty()) sendRoomState(rm);
}

// A player's game reached a save point. With restarting set (someone waits to rejoin), the first one there
// decides: the others' copies (identical in lockstep) arrive after the room moved on. Otherwise, once every
// player's state agrees, it is the point a desync restarts from.
void onSavePoint(Client &c, PbNetReader &r) {
    Room *room = c.room;
    const uint32_t frame = pbr_u32(&r);
    const uint8_t restarting = pbr_u8(&r);
    const uint16_t size = pbr_u16(&r);
    std::vector<uint8_t> state(size <= PB_NET_MAX_CONTINUE_STATE ? size : 0);
    pbr_bytes(&r, state.data(), state.size());
    if (r.error || size == 0 || size > PB_NET_MAX_CONTINUE_STATE) {
        return sendError(c, PB_ERR_BAD_MESSAGE, "malformed SAVE_POINT");
    }
    if (!room || !room->inGame || room->waiting.count(c.id)) return;
    if (restarting) return beginReload(*room, std::move(state), frame);
    auto &reports = room->saveReports[frame];
    reports[c.id] = std::move(state);
    if (reports.size() < playingCount(*room)) return;
    bool agree = true;
    for (const auto &[id, s] : reports) agree &= s == reports.begin()->second;
    if (agree) {
        room->recoveryState = reports.begin()->second;
        room->desyncRestarts = 0;
        logf("room %s: save point at frame %u agreed; desyncs restart from here", room->code.c_str(), frame);
    }
    // (Disagreeing states also show up as a checksum desync, which restarts from the previous agreed point.)
    room->saveReports.erase(room->saveReports.begin(), room->saveReports.upper_bound(frame));
}

void onHello(Client &c, PbNetReader &r) {
    char name[PB_NET_MAX_NAME + 1];
    char build[PB_NET_MAX_BUILD_ID + 1];
    const uint16_t version = pbr_u16(&r);
    pbr_str(&r, name, sizeof(name));
    pbr_str(&r, build, sizeof(build));
    const uint8_t padSize = pbr_u8(&r);
    if (r.error || padSize == 0 || padSize > PB_NET_MAX_PAD_SIZE) {
        sendError(c, PB_ERR_BAD_MESSAGE, "malformed HELLO");
        return;
    }
    if (version != PB_NET_PROTOCOL_VERSION) {
        char msg[160];
        std::snprintf(msg, sizeof(msg), "this server speaks protocol %d, your Party Board protocol %u: %s",
                      PB_NET_PROTOCOL_VERSION, version,
                      version < PB_NET_PROTOCOL_VERSION ? "get the new Party Board zip" : "the server needs updating (re-pull its image)");
        sendError(c, PB_ERR_VERSION, msg);
        return;
    }
    c.helloed = true;
    c.name = name[0] ? name : "Player";
    c.build = build;
    c.padSize = padSize;
    uint8_t buf[4];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_WELCOME);
    pbw_u8(&w, c.id);
    send(c, PB_NET_CHANNEL_CONTROL, w);
    logf("client %u: hello from '%s' (build %s)", c.id, c.name.c_str(), c.build.c_str());
}

void onCreateRoom(Client &c) {
    leaveRoom(c);
    auto room = std::make_unique<Room>();
    room->code = newRoomCode();
    room->build = c.build;
    room->padSize = c.padSize;
    room->hostId = c.id;
    room->members.push_back(c.id);
    seat(*room, c.id);
    c.room = room.get();
    logf("room %s: created by %s", room->code.c_str(), c.name.c_str());
    Room &ref = *room;
    gRooms[room->code] = std::move(room);
    sendRoomState(ref);
}

void onJoinRoom(Client &c, PbNetReader &r) {
    char code[PB_NET_ROOM_CODE_LEN + 1] = {};
    pbr_bytes(&r, code, PB_NET_ROOM_CODE_LEN);
    for (char &ch : code) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed JOIN_ROOM");
    auto it = gRooms.find(code);
    if (it == gRooms.end()) return sendError(c, PB_ERR_NO_SUCH_ROOM, "no room with that code");
    Room &room = *it->second;
    if (room.members.size() >= PB_NET_MAX_PLAYERS) return sendError(c, PB_ERR_ROOM_FULL, "room is full");
    if (c.build != room.build || c.padSize != room.padSize) {
        // Build ids look like "Nov 15 2026 04:20:31/16" (compile time / pad size): show the times.
        const auto when = [](const std::string &b) { return b.substr(0, b.find('/')); };
        char msg[200];
        std::snprintf(msg, sizeof(msg), "your Party Board (built %s) differs from the host's (built %s): everyone needs the same zip",
                      when(c.build).c_str(), when(room.build).c_str());
        return sendError(c, PB_ERR_VERSION, msg);
    }
    if (room.inGame) return joinRunningGame(c, room);
    leaveRoom(c);
    room.members.push_back(c.id);
    seat(room, c.id);
    if (room.reloading && c.name == room.hostName) room.hostId = c.id; // the host role goes back to the host
    c.room = &room;
    logf("room %s: %s joined (%zu players)%s", room.code.c_str(), c.name.c_str(), room.members.size(),
         room.reloading ? " for the reload" : "");
    sendRoomState(room);
    startReloadedIfReady(room);
}

void onStartGame(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room) return sendError(c, PB_ERR_NO_SUCH_ROOM, "not in a room");
    if (room->hostId != c.id) return sendError(c, PB_ERR_NOT_HOST, "only the host can start");
    if (room->inGame || room->reloading) return sendError(c, PB_ERR_IN_GAME, "already playing");
    PbNetSettings s;
    pbr_settings(&r, &s);
    const uint16_t stateSize = pbr_u16(&r);
    std::vector<uint8_t> state(stateSize <= PB_NET_MAX_CONTINUE_STATE ? stateSize : 0);
    pbr_bytes(&r, state.data(), state.size());
    if (r.error || stateSize > PB_NET_MAX_CONTINUE_STATE) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed START_GAME");
    if (room->continuing && state.empty()) {
        return sendError(c, PB_ERR_BAD_SETTINGS, "a continued game needs its saved state");
    }
    // Seating and characters come from the lobby, not from the host's message.
    const auto chars = resolvedChars(*room);
    std::copy(chars.begin(), chars.end(), s.chars);
    std::copy(room->slotOwner.begin(), room->slotOwner.end(), s.portOwner);
    if (!pb_settings_valid(&s)) return sendError(c, PB_ERR_BAD_SETTINGS, "invalid game settings");
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        const uint8_t owner = s.portOwner[port];
        if (owner != PB_NET_PORT_CPU && std::find(room->members.begin(), room->members.end(), owner) == room->members.end()) {
            return sendError(c, PB_ERR_BAD_SETTINGS, "a port is assigned to someone not in the room");
        }
    }
    for (uint8_t id : room->members) {
        bool ownsPort = false;
        for (uint8_t owner : s.portOwner) ownsPort |= owner == id;
        if (!ownsPort) return sendError(c, PB_ERR_BAD_SETTINGS, "every player in the room needs a port");
    }
    room->desyncRestarts = 0;
    startGame(*room, s, state);
}

// Name of whoever holds a slot, for error messages.
std::string slotName(const Room &room, int port) {
    const uint8_t owner = room.slotOwner[port];
    return owner == PB_NET_PORT_CPU ? std::string("a CPU") : gClients.at(owner)->name;
}

void onChoose(Client &c, PbNetReader &r) {
    Room *room = c.room;
    const uint8_t wantPort = pbr_u8(&r);
    const uint8_t wantChar = pbr_u8(&r);
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed CHOOSE");
    if (!room) return sendError(c, PB_ERR_NO_SUCH_ROOM, "not in a room");
    if (room->inGame || room->reloading) return sendError(c, PB_ERR_IN_GAME, "the game has started");
    if ((wantPort != PB_NET_KEEP && wantPort >= PB_NET_MAX_PLAYERS) ||
        (wantChar != PB_NET_KEEP && wantChar >= PB_NET_MAX_CHARS)) {
        return sendError(c, PB_ERR_BAD_MESSAGE, "no such port or character");
    }
    int port = portOf(*room, c.id);
    if (port < 0) return sendError(c, PB_ERR_BAD_MESSAGE, "you have no port"); // can't happen
    auto owners = room->slotOwner;
    auto chars = room->slotChar;
    if (room->continuing && wantChar != PB_NET_KEEP && wantChar != chars[port]) {
        return sendError(c, PB_ERR_TAKEN, "characters are fixed in a continued game");
    }
    if (wantPort != PB_NET_KEEP && wantPort != port) {
        if (owners[wantPort] != PB_NET_PORT_CPU) {
            char msg[96];
            std::snprintf(msg, sizeof(msg), "P%d is taken by %s", wantPort + 1, slotName(*room, wantPort).c_str());
            return sendError(c, PB_ERR_TAKEN, msg);
        }
        std::swap(owners[port], owners[wantPort]); // the CPU (and its character choice) moves to our old port
        if (!room->continuing) std::swap(chars[port], chars[wantPort]); // continued: characters stay with ports
        port = wantPort;
    }
    if (wantChar != PB_NET_KEEP && !room->continuing) {
        for (int other = 0; other < PB_NET_MAX_PLAYERS; other++) {
            if (other != port && chars[other] == wantChar) {
                char msg[96];
                std::snprintf(msg, sizeof(msg), "%s is taken by %s", kCharNames[wantChar],
                              owners[other] == PB_NET_PORT_CPU ? "a CPU" : gClients.at(owners[other])->name.c_str());
                return sendError(c, PB_ERR_TAKEN, msg);
            }
        }
        chars[port] = wantChar;
    }
    room->slotOwner = owners;
    room->slotChar = chars;
    logf("room %s: %s is P%d as %s", room->code.c_str(), c.name.c_str(), port + 1, kCharNames[chars[port]]);
    sendRoomState(*room);
}

void onSetLayout(Client &c, PbNetReader &r) {
    Room *room = c.room;
    std::array<uint8_t, PB_NET_MAX_PLAYERS> owners{}, chars{};
    pbr_bytes(&r, owners.data(), owners.size());
    pbr_bytes(&r, chars.data(), chars.size());
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed SET_LAYOUT");
    if (!room) return sendError(c, PB_ERR_NO_SUCH_ROOM, "not in a room");
    if (room->hostId != c.id) return sendError(c, PB_ERR_NOT_HOST, "only the host can arrange the ports");
    if (room->inGame || room->reloading) return sendError(c, PB_ERR_IN_GAME, "the game has started");
    if (room->continuing && chars != room->slotChar) {
        return sendError(c, PB_ERR_BAD_SETTINGS, "characters are fixed in a continued game");
    }
    for (uint8_t id : room->members) {
        if (std::count(owners.begin(), owners.end(), id) != 1) {
            return sendError(c, PB_ERR_BAD_SETTINGS, "every player needs exactly one port");
        }
    }
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        const bool cpu = owners[port] == PB_NET_PORT_CPU;
        if (!cpu && std::find(room->members.begin(), room->members.end(), owners[port]) == room->members.end()) {
            return sendError(c, PB_ERR_BAD_SETTINGS, "a port is assigned to someone not in the room");
        }
        if (chars[port] >= PB_NET_MAX_CHARS && !(cpu && chars[port] == PB_NET_CHAR_AUTO)) {
            return sendError(c, PB_ERR_BAD_SETTINGS, "invalid character");
        }
        for (int other = 0; other < port; other++) {
            if (chars[port] != PB_NET_CHAR_AUTO && chars[other] == chars[port]) {
                char msg[96];
                std::snprintf(msg, sizeof(msg), "%s is on two ports", kCharNames[chars[port]]);
                return sendError(c, PB_ERR_TAKEN, msg);
            }
        }
    }
    room->slotOwner = owners;
    room->slotChar = chars;
    logf("room %s: host set the layout", room->code.c_str());
    sendRoomState(*room);
}

void onSetContinue(Client &c, PbNetReader &r) {
    Room *room = c.room;
    const uint8_t enabled = pbr_u8(&r);
    std::array<uint8_t, PB_NET_MAX_PLAYERS> chars{};
    std::array<std::string, PB_NET_MAX_PLAYERS> names;
    if (enabled) {
        for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            char name[PB_NET_MAX_NAME + 1];
            chars[port] = pbr_u8(&r);
            const uint8_t wasHuman = pbr_u8(&r);
            pbr_str(&r, name, sizeof(name));
            names[port] = wasHuman ? name : "";
        }
    }
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed SET_CONTINUE");
    if (!room) return sendError(c, PB_ERR_NO_SUCH_ROOM, "not in a room");
    if (room->hostId != c.id) return sendError(c, PB_ERR_NOT_HOST, "only the host can continue a game");
    if (room->inGame || room->reloading) return sendError(c, PB_ERR_IN_GAME, "the game has started");
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        for (int other = 0; enabled && other < port; other++) {
            if (chars[port] >= PB_NET_MAX_CHARS || chars[port] == chars[other]) {
                return sendError(c, PB_ERR_BAD_SETTINGS, "the save's characters are invalid");
            }
        }
    }
    room->continuing = enabled != 0;
    room->savedName = names;
    room->slotOwner.fill(PB_NET_PORT_CPU);
    room->slotChar.fill(PB_NET_CHAR_AUTO);
    if (room->continuing) room->slotChar = chars;
    for (uint8_t id : room->members) seat(*room, id); // join order: the host first
    logf("room %s: %s", room->code.c_str(), room->continuing ? "continuing a saved game" : "new game");
    sendRoomState(*room);
}

void onInput(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room || !room->inGame || room->waiting.count(c.id)) return; // stale input after a game ended
    const uint32_t frame = pbr_u32(&r);
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed INPUT");
    if (frame < room->nextFrame || frame >= room->nextFrame + kMaxFramesAhead) return;
    PendingFrame &pending = room->frames[frame];
    const uint32_t now = enet_time_get();
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room->settings.portOwner[port] != c.id) continue;
        pbr_bytes(&r, pending.pads[port].data(), room->padSize);
        pending.have |= static_cast<uint8_t>(1 << port);
        pending.arrivedMs[port] = now;
    }
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed INPUT");
    flushFrames(*room);
}

void onChecksum(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room || !room->inGame || room->waiting.count(c.id)) return;
    const uint32_t frame = pbr_u32(&r);
    const uint32_t hash = pbr_u32(&r);
    if (r.error) return;
    auto &reports = room->checksums[frame];
    reports[c.id] = hash;
    if (reports.size() < playingCount(*room)) return;
    bool agree = true;
    for (const auto &[id, h] : reports) agree &= h == reports.begin()->second;
    room->checksums.erase(frame);
    if (agree) return;

    logf("room %s: DESYNC at frame %u", room->code.c_str(), frame);
    uint8_t buf[8];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_DESYNC);
    pbw_u32(&w, frame);
    broadcastGame(*room, PB_NET_CHANNEL_CONTROL, w);
    if (room->desyncRestarts >= kMaxDesyncRestarts) {
        // Restarting from that point didn't help: something there doesn't replay the same. Give up.
        endGame(*room, PB_END_DESYNC, 0xFF);
        return;
    }
    // Everyone restarts and the game goes on from the last save point they all agreed on.
    room->desyncRestarts++;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_RESTART);
    pbw_u8(&w, PB_RESTART_DESYNC);
    broadcastGame(*room, PB_NET_CHANNEL_CONTROL, w);
    logf("room %s: restarting everyone from the last agreed save point (%zu bytes; restart %d)", room->code.c_str(),
         room->recoveryState.size(), room->desyncRestarts);
    beginReload(*room, room->recoveryState, frame);
}

void onPerf(Client &c, PbNetReader &r) {
    Room *room = c.room;
    pbr_u16(&r); // frames
    const uint16_t slow = pbr_u16(&r);
    const uint16_t stalls = pbr_u16(&r);
    const uint16_t worst = pbr_u16(&r);
    pbr_u16(&r); // netWaitMs
    if (r.error || !room || !room->inGame) return;
    c.slowFrames = static_cast<uint16_t>((std::min)(c.slowFrames + slow, 65535));
    c.netStalls = static_cast<uint16_t>((std::min)(c.netStalls + stalls, 65535));
    c.worstFrameMs = (std::max)(c.worstFrameMs, worst);
}

// Once a second in game: everyone's connection and who held the game up (see noteLateness, PB_MSG_PERF).
void sendNetStats(Room &room) {
    uint8_t buf[8 + PB_NET_MAX_PLAYERS * 32];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_NET_STATS);
    std::vector<Client *> players;
    for (uint8_t id : room.members) {
        if (!room.waiting.count(id) && portOf(room, id) >= 0) players.push_back(gClients.at(id).get());
    }
    pbw_u8(&w, static_cast<uint8_t>(players.size()));
    for (Client *c : players) {
        const ENetPeer *peer = c->peer;
        pbw_u8(&w, c->id);
        pbw_u16(&w, static_cast<uint16_t>(std::min<enet_uint32>(peer->roundTripTime, 65535)));
        pbw_u16(&w, static_cast<uint16_t>(std::min<enet_uint32>(peer->roundTripTimeVariance, 65535)));
        pbw_u16(&w, static_cast<uint16_t>(std::min<uint64_t>(uint64_t(peer->packetLoss) * 1000 / ENET_PEER_PACKET_LOSS_SCALE, 1000)));
        pbw_u16(&w, c->lateFrames);
        pbw_u16(&w, c->worstLateMs);
        pbw_u16(&w, c->slowFrames);
        pbw_u16(&w, c->netStalls);
        pbw_u16(&w, c->worstFrameMs);
        if (c->lateFrames) {
            logf("room %s: %s held the game up on %u frame(s), worst %u ms (ping %u, jitter %u; own slow frames %u, worst %u ms)",
                 room.code.c_str(), c->name.c_str(), c->lateFrames, c->worstLateMs, peer->roundTripTime,
                 peer->roundTripTimeVariance, c->slowFrames, c->worstFrameMs);
        }
        c->lateFrames = c->worstLateMs = c->slowFrames = c->netStalls = c->worstFrameMs = 0;
    }
    broadcastGame(room, PB_NET_CHANNEL_CONTROL, w);
    room.lastStatsMs = enet_time_get();
}

void onReceive(Client &c, ENetPacket *packet) {
    PbNetReader r;
    pbr_init(&r, packet->data, packet->dataLength);
    const uint8_t type = pbr_u8(&r);
    if (!c.helloed && type != PB_MSG_HELLO) return sendError(c, PB_ERR_BAD_MESSAGE, "say HELLO first");
    switch (type) {
    case PB_MSG_HELLO: return onHello(c, r);
    case PB_MSG_CREATE_ROOM: return onCreateRoom(c);
    case PB_MSG_JOIN_ROOM: return onJoinRoom(c, r);
    case PB_MSG_LEAVE_ROOM: return leaveRoom(c);
    case PB_MSG_START_GAME: return onStartGame(c, r);
    case PB_MSG_INPUT: return onInput(c, r);
    case PB_MSG_CHECKSUM: return onChecksum(c, r);
    case PB_MSG_CHOOSE: return onChoose(c, r);
    case PB_MSG_SET_LAYOUT: return onSetLayout(c, r);
    case PB_MSG_SET_CONTINUE: return onSetContinue(c, r);
    case PB_MSG_SAVE_POINT: return onSavePoint(c, r);
    case PB_MSG_PERF: return onPerf(c, r);
    default: return sendError(c, PB_ERR_BAD_MESSAGE, "unknown message type");
    }
}

// Called often from the main loop: tells players who a stalled game is waiting for, and refreshes lobby pings.
void tick() {
    const uint32_t now = enet_time_get();
    for (auto it = gRooms.begin(); it != gRooms.end();) {
        Room &room = *it->second;
        if (room.reloading && now - room.reloadStartMs >= PB_NET_RELOAD_TIMEOUT_MS) {
            if (room.members.empty()) {
                logf("room %s: nobody came back after the reload; closed", room.code.c_str());
                it = gRooms.erase(it);
                continue;
            }
            startReloadedIfReady(room);
        }
        ++it;
        if (room.inGame && now - room.lastStatsMs >= 1000) sendNetStats(room);
        if (room.inGame) {
            const uint32_t waited = now - room.lastProgressMs;
            if (waited >= 500 && now - room.lastWaitingMs >= 500) {
                const auto it = room.frames.find(room.nextFrame);
                const uint8_t have = it == room.frames.end() ? 0 : it->second.have;
                const uint8_t missing = static_cast<uint8_t>(room.humanMask & ~have);
                uint8_t buf[8];
                PbNetWriter w;
                pbw_init(&w, buf, sizeof(buf));
                pbw_u8(&w, PB_MSG_WAITING);
                pbw_u8(&w, missing);
                pbw_u16(&w, static_cast<uint16_t>(std::min<uint32_t>(waited, 65535)));
                broadcastGame(room, PB_NET_CHANNEL_CONTROL, w);
                room.lastWaitingMs = now;
            }
        } else if (now - room.lastLobbyStateMs >= 2000) {
            // Lobby: refresh everyone's ping when one has moved noticeably.
            bool changed = false;
            for (uint8_t id : room.members) {
                const Client &m = *gClients.at(id);
                const int rtt = static_cast<int>(m.peer->roundTripTime);
                changed |= std::abs(rtt - static_cast<int>(m.lastSentRtt)) >= 5;
            }
            if (changed) sendRoomState(room);
            else room.lastLobbyStateMs = now;
        }
    }
}

int allocateId() {
    for (int id = 1; id < 255; id++) {
        if (!gClients.count(static_cast<uint8_t>(id))) return id;
    }
    return -1;
}

} // namespace

int main(int argc, char **argv) {
    uint16_t port = PB_NET_DEFAULT_PORT;
    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "--port") == 0 && i + 1 < argc) {
            port = static_cast<uint16_t>(std::atoi(argv[++i]));
        } else {
            std::fprintf(stderr, "usage: %s [--port N]   (default %d)\n", argv[0], PB_NET_DEFAULT_PORT);
            return 2;
        }
    }
    if (const char *env = std::getenv("PB_SERVER_PORT")) port = static_cast<uint16_t>(std::atoi(env));

    if (enet_initialize() != 0) {
        std::fprintf(stderr, "enet_initialize failed\n");
        return 1;
    }
    ENetAddress address{};
    address.host = ENET_HOST_ANY;
    address.port = port;
    ENetHost *host = enet_host_create(&address, kMaxClients, PB_NET_CHANNEL_COUNT, 0, 0);
    if (!host) {
        std::fprintf(stderr, "could not listen on UDP port %u\n", port);
        return 1;
    }
    logf("Party Board relay server, protocol %d, listening on UDP %u", PB_NET_PROTOCOL_VERSION, port);

    for (;;) {
        ENetEvent event;
        tick();
        while (enet_host_service(host, &event, 50) > 0) {
            tick();
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                const int id = allocateId();
                if (id < 0) {
                    enet_peer_disconnect_now(event.peer, 0);
                    break;
                }
                auto client = std::make_unique<Client>();
                client->id = static_cast<uint8_t>(id);
                client->peer = event.peer;
                event.peer->data = client.get();
                enet_peer_timeout(event.peer, 0, 5000, 15000);
                char ip[64];
                enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
                logf("client %d: connected from %s", id, ip);
                gClients[client->id] = std::move(client);
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                if (auto *c = static_cast<Client *>(event.peer->data)) onReceive(*c, event.packet);
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT: {
                if (auto *c = static_cast<Client *>(event.peer->data)) {
                    logf("client %u: disconnected", c->id);
                    leaveRoom(*c);
                    gClients.erase(c->id);
                }
                event.peer->data = nullptr;
                break;
            }
            default:
                break;
            }
        }
    }
}
