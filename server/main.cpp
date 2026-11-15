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
};

struct PendingFrame {
    uint8_t have = 0; // bit per port whose input arrived
    std::array<std::array<uint8_t, PB_NET_MAX_PAD_SIZE>, PB_NET_MAX_PLAYERS> pads{};
};

struct Room {
    std::string code;
    std::string build;
    uint8_t padSize = 0;
    uint8_t hostId = 0;
    std::vector<uint8_t> members; // client ids, join order
    bool inGame = false;
    PbNetSettings settings{};
    uint8_t humanMask = 0;
    uint32_t nextFrame = 0;
    std::map<uint32_t, PendingFrame> frames;
    std::map<uint32_t, std::map<uint8_t, uint32_t>> checksums;
};

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

void sendRoomState(Room &room) {
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
    }
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
    broadcast(room, PB_NET_CHANNEL_CONTROL, w);
    room.inGame = false;
    room.frames.clear();
    room.checksums.clear();
    logf("room %s: game ended (reason %d)", room.code.c_str(), reason);
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
    broadcast(room, PB_NET_CHANNEL_CONTROL, w);
    logf("room %s: %s dropped at frame %u; CPU takes ports 0x%x", room.code.c_str(), c.name.c_str(), room.nextFrame,
         ports);
    flushFrames(room); // frames that were only waiting on the dropped player can go now
}

void leaveRoom(Client &c) {
    Room *room = c.room;
    if (!room) return;
    c.room = nullptr;
    room->members.erase(std::find(room->members.begin(), room->members.end(), c.id));
    logf("room %s: %s left (%zu remaining)", room->code.c_str(), c.name.c_str(), room->members.size());
    if (room->members.empty()) {
        logf("room %s: closed", room->code.c_str());
        gRooms.erase(room->code);
        return;
    }
    if (room->inGame) {
        dropFromGame(*room, c);
    }
    if (room->hostId == c.id) {
        room->hostId = room->members.front();
    }
    sendRoomState(*room);
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
        for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            if (room.humanMask & (1 << port)) pbw_bytes(&w, it->second.pads[port].data(), room.padSize);
        }
        broadcast(room, PB_NET_CHANNEL_INPUT, w);
        room.frames.erase(it);
        room.nextFrame++;
    }
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
        sendError(c, PB_ERR_VERSION, "protocol version mismatch; update Party Board");
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
    if (room.inGame) return sendError(c, PB_ERR_IN_GAME, "that room is already playing");
    if (room.members.size() >= PB_NET_MAX_PLAYERS) return sendError(c, PB_ERR_ROOM_FULL, "room is full");
    if (c.build != room.build || c.padSize != room.padSize) {
        return sendError(c, PB_ERR_VERSION, "your Party Board build differs from the host's");
    }
    leaveRoom(c);
    room.members.push_back(c.id);
    c.room = &room;
    logf("room %s: %s joined (%zu players)", room.code.c_str(), c.name.c_str(), room.members.size());
    sendRoomState(room);
}

void onStartGame(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room) return sendError(c, PB_ERR_NO_SUCH_ROOM, "not in a room");
    if (room->hostId != c.id) return sendError(c, PB_ERR_NOT_HOST, "only the host can start");
    if (room->inGame) return sendError(c, PB_ERR_IN_GAME, "already playing");
    PbNetSettings s;
    pbr_settings(&r, &s);
    if (r.error || !pb_settings_valid(&s)) return sendError(c, PB_ERR_BAD_SETTINGS, "invalid game settings");

    uint8_t humanMask = 0;
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        const uint8_t owner = s.portOwner[port];
        if (owner == PB_NET_PORT_CPU) continue;
        if (std::find(room->members.begin(), room->members.end(), owner) == room->members.end()) {
            return sendError(c, PB_ERR_BAD_SETTINGS, "a port is assigned to someone not in the room");
        }
        humanMask |= static_cast<uint8_t>(1 << port);
    }
    for (uint8_t id : room->members) {
        bool ownsPort = false;
        for (uint8_t owner : s.portOwner) ownsPort |= owner == id;
        if (!ownsPort) return sendError(c, PB_ERR_BAD_SETTINGS, "every player in the room needs a port");
    }

    room->settings = s;
    room->humanMask = humanMask;
    room->inGame = true;
    room->nextFrame = 0;
    room->frames.clear();
    room->checksums.clear();

    uint8_t buf[64];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_GAME_START);
    pbw_settings(&w, &s);
    broadcast(*room, PB_NET_CHANNEL_CONTROL, w);
    logf("room %s: game started (board %u, %u turns, seed %u, delay %u, human ports 0x%x)", room->code.c_str(),
         s.board, s.turns, s.seed, s.inputDelay, humanMask);
}

void onInput(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room || !room->inGame) return; // stale input after a game ended
    const uint32_t frame = pbr_u32(&r);
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed INPUT");
    if (frame < room->nextFrame || frame >= room->nextFrame + kMaxFramesAhead) return;
    PendingFrame &pending = room->frames[frame];
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (room->settings.portOwner[port] != c.id) continue;
        pbr_bytes(&r, pending.pads[port].data(), room->padSize);
        pending.have |= static_cast<uint8_t>(1 << port);
    }
    if (r.error) return sendError(c, PB_ERR_BAD_MESSAGE, "malformed INPUT");
    flushFrames(*room);
}

void onChecksum(Client &c, PbNetReader &r) {
    Room *room = c.room;
    if (!room || !room->inGame) return;
    const uint32_t frame = pbr_u32(&r);
    const uint32_t hash = pbr_u32(&r);
    if (r.error) return;
    auto &reports = room->checksums[frame];
    reports[c.id] = hash;
    if (reports.size() < room->members.size()) return;
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
    broadcast(*room, PB_NET_CHANNEL_CONTROL, w);
    endGame(*room, PB_END_DESYNC, 0xFF);
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
    default: return sendError(c, PB_ERR_BAD_MESSAGE, "unknown message type");
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
        while (enet_host_service(host, &event, 50) > 0) {
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
