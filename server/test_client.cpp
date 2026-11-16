// Integration test for the relay server: two simulated players over real UDP.
//   partyboard-server-test [host] [port]
// Exits 0 if every check passes.

#include "netplay/protocol.h"

#include <enet/enet.h>

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <string>
#include <vector>

namespace {

constexpr uint8_t kPadSize = 16;
int gFailures = 0;

#define CHECK(cond, ...)                                                                                              \
    do {                                                                                                              \
        if (!(cond)) {                                                                                                \
            std::printf("FAIL line %d: ", __LINE__);                                                                  \
            std::printf(__VA_ARGS__);                                                                                 \
            std::printf("\n");                                                                                        \
            gFailures++;                                                                                              \
        }                                                                                                             \
    } while (0)

struct TestClient {
    ENetHost *host = nullptr;
    ENetPeer *peer = nullptr;
    std::deque<std::vector<uint8_t>> inbox;

    bool connect(const char *hostname, uint16_t port) {
        host = enet_host_create(nullptr, 1, PB_NET_CHANNEL_COUNT, 0, 0);
        ENetAddress address{};
        enet_address_set_host(&address, hostname);
        address.port = port;
        peer = enet_host_connect(host, &address, PB_NET_CHANNEL_COUNT, 0);
        ENetEvent event;
        return enet_host_service(host, &event, 3000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT;
    }
    void send(uint8_t channel, const PbNetWriter &w) {
        enet_peer_send(peer, channel, enet_packet_create(w.data, w.pos, ENET_PACKET_FLAG_RELIABLE));
        enet_host_flush(host);
    }
    void pump(int ms) {
        ENetEvent event;
        while (enet_host_service(host, &event, ms) > 0) {
            if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                inbox.emplace_back(event.packet->data, event.packet->data + event.packet->dataLength);
                enet_packet_destroy(event.packet);
            }
            ms = 0;
        }
    }
    // Waits for the next message of the given type, discarding others. Empty on timeout.
    std::vector<uint8_t> waitFor(uint8_t type, int timeoutMs = 2000) {
        for (int waited = 0; waited <= timeoutMs; waited += 10) {
            while (!inbox.empty()) {
                auto msg = std::move(inbox.front());
                inbox.pop_front();
                if (!msg.empty() && msg[0] == type) return msg;
            }
            pump(10);
        }
        return {};
    }
};

void hello(TestClient &c, const char *name) {
    uint8_t buf[128];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_HELLO);
    pbw_u16(&w, PB_NET_PROTOCOL_VERSION);
    pbw_str(&w, name, PB_NET_MAX_NAME);
    pbw_str(&w, "test-build", PB_NET_MAX_BUILD_ID);
    pbw_u8(&w, kPadSize);
    c.send(PB_NET_CHANNEL_CONTROL, w);
}

void simple(TestClient &c, uint8_t type, const void *payload = nullptr, size_t n = 0) {
    uint8_t buf[64];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, type);
    if (n) pbw_bytes(&w, payload, n);
    c.send(PB_NET_CHANNEL_CONTROL, w);
}

struct RoomState {
    bool ok = false;
    uint8_t host = 0;
    uint8_t count = 0;
    uint8_t owner[PB_NET_MAX_PLAYERS] = {};
    uint8_t chr[PB_NET_MAX_PLAYERS] = {};
    uint8_t isAuto[PB_NET_MAX_PLAYERS] = {};
    uint16_t ping[PB_NET_MAX_PLAYERS] = {};
    bool continuing = false;
    std::string savedName[PB_NET_MAX_PLAYERS];
    uint8_t phase = 0xFF;
};

RoomState parseRoomState(const std::vector<uint8_t> &msg) {
    RoomState st;
    if (msg.empty() || msg[0] != PB_MSG_ROOM_STATE) return st;
    PbNetReader r;
    pbr_init(&r, msg.data() + 1, msg.size() - 1);
    char code[PB_NET_ROOM_CODE_LEN];
    pbr_bytes(&r, code, sizeof(code));
    st.host = pbr_u8(&r);
    st.count = pbr_u8(&r);
    for (int i = 0; i < st.count; i++) {
        char name[PB_NET_MAX_NAME + 1];
        pbr_u8(&r);
        pbr_str(&r, name, sizeof(name));
        st.ping[i] = pbr_u16(&r);
    }
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        st.owner[port] = pbr_u8(&r);
        st.chr[port] = pbr_u8(&r);
        st.isAuto[port] = pbr_u8(&r);
    }
    st.continuing = pbr_u8(&r) != 0;
    for (int port = 0; st.continuing && port < PB_NET_MAX_PLAYERS; port++) {
        char name[PB_NET_MAX_NAME + 1];
        pbr_str(&r, name, sizeof(name));
        st.savedName[port] = name;
    }
    st.phase = pbr_u8(&r);
    st.ok = !r.error && r.pos == r.size;
    return st;
}

bool slotsAre(const RoomState &st, const uint8_t owner[4], const uint8_t chr[4]) {
    return st.ok && std::memcmp(st.owner, owner, 4) == 0 && std::memcmp(st.chr, chr, 4) == 0;
}

void choose(TestClient &c, uint8_t port, uint8_t chr) {
    const uint8_t payload[2] = {port, chr};
    simple(c, PB_MSG_CHOOSE, payload, 2);
}

void setLayout(TestClient &c, const uint8_t owner[4], const uint8_t chr[4]) {
    uint8_t payload[8];
    std::memcpy(payload, owner, 4);
    std::memcpy(payload + 4, chr, 4);
    simple(c, PB_MSG_SET_LAYOUT, payload, 8);
}

// Expects an error of the given code (and no room-state change in between).
bool expectError(TestClient &c, uint8_t code) {
    auto msg = c.waitFor(PB_MSG_ERROR);
    return msg.size() > 1 && msg[1] == code;
}

void setContinue(TestClient &c, bool enabled, const uint8_t chr[4], const char *const names[4]) {
    uint8_t buf[256];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_SET_CONTINUE);
    pbw_u8(&w, enabled ? 1 : 0);
    for (int port = 0; enabled && port < 4; port++) {
        pbw_u8(&w, chr[port]);
        pbw_u8(&w, names[port][0] ? 1 : 0);
        pbw_str(&w, names[port], PB_NET_MAX_NAME);
    }
    c.send(PB_NET_CHANNEL_CONTROL, w);
}

void sendInput(TestClient &c, uint32_t frame, uint8_t value) {
    uint8_t buf[64];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_INPUT);
    pbw_u32(&w, frame);
    uint8_t pad[kPadSize];
    std::memset(pad, value, sizeof(pad));
    pbw_bytes(&w, pad, sizeof(pad));
    c.send(PB_NET_CHANNEL_INPUT, w);
}

void sendChecksum(TestClient &c, uint32_t frame, uint32_t hash) {
    uint8_t buf[16];
    PbNetWriter w;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_CHECKSUM);
    pbw_u32(&w, frame);
    pbw_u32(&w, hash);
    c.send(PB_NET_CHANNEL_CONTROL, w);
}

void sendSavePoint(TestClient &c, uint32_t frame, bool restarting, const uint8_t *state, uint16_t size) {
    std::vector<uint8_t> buf(16 + size);
    PbNetWriter w;
    pbw_init(&w, buf.data(), buf.size());
    pbw_u8(&w, PB_MSG_SAVE_POINT);
    pbw_u32(&w, frame);
    pbw_u8(&w, restarting ? 1 : 0);
    pbw_u16(&w, size);
    pbw_bytes(&w, state, size);
    c.send(PB_NET_CHANNEL_CONTROL, w);
}

} // namespace

int main(int argc, char **argv) {
    const char *hostname = argc > 1 ? argv[1] : "127.0.0.1";
    const uint16_t port = static_cast<uint16_t>(argc > 2 ? std::atoi(argv[2]) : PB_NET_DEFAULT_PORT);
    enet_initialize();

    TestClient a, b;
    if (!a.connect(hostname, port) || !b.connect(hostname, port)) {
        std::printf("FAIL: could not connect to %s:%u\n", hostname, port);
        return 1;
    }
    hello(a, "Alice");
    hello(b, "Bob");
    auto wa = a.waitFor(PB_MSG_WELCOME);
    auto wb = b.waitFor(PB_MSG_WELCOME);
    CHECK(wa.size() == 2 && wb.size() == 2, "both clients welcomed");
    const uint8_t idA = wa.size() == 2 ? wa[1] : 0, idB = wb.size() == 2 ? wb[1] : 0;

    // Room create/join.
    simple(a, PB_MSG_CREATE_ROOM);
    auto state = a.waitFor(PB_MSG_ROOM_STATE);
    CHECK(state.size() > 6, "room created");
    char code[5] = {};
    if (state.size() > 6) std::memcpy(code, &state[1], 4);
    std::printf("room code %s\n", code);
    simple(b, PB_MSG_JOIN_ROOM, "ZZZZ", 4);
    CHECK(!b.waitFor(PB_MSG_ERROR).empty(), "joining a bad code errors");
    simple(b, PB_MSG_JOIN_ROOM, code, 4);
    state = b.waitFor(PB_MSG_ROOM_STATE);
    CHECK(state.size() > 7 && state[6] == 2, "room shows 2 members after join");
    a.waitFor(PB_MSG_ROOM_STATE); // Alice's copy of the creation state
    a.waitFor(PB_MSG_ROOM_STATE); // ...and of Bob's join

    // ---- Seating and characters ----
    const uint8_t CPU = PB_NET_PORT_CPU, AUTO = PB_NET_CHAR_AUTO, KEEP = PB_NET_KEEP;
    {
        // Default: join order, first free characters, CPUs auto-filled (Mario Luigi Peach Yoshi).
        RoomState st = parseRoomState(state);
        const uint8_t owner[4] = {idA, idB, CPU, CPU}, chr[4] = {0, 1, 2, 3};
        CHECK(slotsAre(st, owner, chr), "default seating is join order with Mario/Luigi/Peach/Yoshi");
        CHECK(st.isAuto[2] && st.isAuto[3] && !st.isAuto[0] && !st.isAuto[1], "CPUs are auto");
    }
    choose(b, KEEP, 0);
    CHECK(expectError(b, PB_ERR_TAKEN), "picking Alice's character is rejected");
    choose(b, 0, KEEP);
    CHECK(expectError(b, PB_ERR_TAKEN), "moving onto Alice's port is rejected");
    choose(b, 3, 5); // Bob moves to P4 as Donkey Kong
    {
        RoomState st = parseRoomState(a.waitFor(PB_MSG_ROOM_STATE));
        const uint8_t owner[4] = {idA, CPU, CPU, idB}, chr[4] = {0, 1, 2, 5};
        CHECK(slotsAre(st, owner, chr), "Bob is P4 as DK; CPUs refill from the rest");
        b.waitFor(PB_MSG_ROOM_STATE);
    }
    setLayout(b, std::array<uint8_t, 4>{idA, idB, CPU, CPU}.data(), std::array<uint8_t, 4>{0, 1, AUTO, AUTO}.data());
    CHECK(expectError(b, PB_ERR_NOT_HOST), "only the host can set the layout");
    setLayout(a, std::array<uint8_t, 4>{idA, idB, CPU, CPU}.data(), std::array<uint8_t, 4>{0, 0, AUTO, AUTO}.data());
    CHECK(expectError(a, PB_ERR_TAKEN), "layout with a duplicate character is rejected");
    setLayout(a, std::array<uint8_t, 4>{idA, CPU, CPU, CPU}.data(), std::array<uint8_t, 4>{0, AUTO, AUTO, AUTO}.data());
    CHECK(expectError(a, PB_ERR_BAD_SETTINGS), "layout without Bob is rejected");
    setLayout(a, std::array<uint8_t, 4>{idA, CPU, CPU, idA}.data(), std::array<uint8_t, 4>{0, AUTO, AUTO, 1}.data());
    CHECK(expectError(a, PB_ERR_BAD_SETTINGS), "layout with Alice twice is rejected");
    setLayout(a, std::array<uint8_t, 4>{CPU, idA, CPU, idB}.data(), std::array<uint8_t, 4>{7, 0, AUTO, 5}.data());
    {
        RoomState st = parseRoomState(b.waitFor(PB_MSG_ROOM_STATE));
        const uint8_t owner[4] = {CPU, idA, CPU, idB}, chr[4] = {7, 0, 1, 5};
        CHECK(slotsAre(st, owner, chr), "host rearranged: CPU Waluigi P1, Alice P2, auto CPU P3, Bob P4");
        CHECK(!st.isAuto[0] && st.isAuto[2], "host-picked CPU is not auto");
        a.waitFor(PB_MSG_ROOM_STATE);
    }
    choose(a, KEEP, 7);
    CHECK(expectError(a, PB_ERR_TAKEN), "a host-picked CPU character can't be taken");
    choose(a, KEEP, 1); // the auto CPU's character is free to take; the CPU picks another
    {
        RoomState st = parseRoomState(a.waitFor(PB_MSG_ROOM_STATE));
        const uint8_t owner[4] = {CPU, idA, CPU, idB}, chr[4] = {7, 1, 0, 5};
        CHECK(slotsAre(st, owner, chr), "taking an auto CPU's character re-rolls the CPU");
        b.waitFor(PB_MSG_ROOM_STATE);
    }
    {
        // A third player takes the lowest CPU port and the first free character, and leaving frees it.
        TestClient c;
        CHECK(c.connect(hostname, port), "third client connects");
        hello(c, "Cara");
        c.waitFor(PB_MSG_WELCOME);
        simple(c, PB_MSG_JOIN_ROOM, code, 4);
        RoomState st = parseRoomState(c.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.count == 3 && st.owner[0] != CPU && st.chr[0] == 0 && st.owner[2] == CPU,
              "Cara takes P1 (the lowest CPU port) as Mario");
        a.waitFor(PB_MSG_ROOM_STATE);
        b.waitFor(PB_MSG_ROOM_STATE);
        enet_peer_disconnect(c.peer, 0);
        c.pump(200);
        st = parseRoomState(a.waitFor(PB_MSG_ROOM_STATE, 3000));
        const uint8_t owner[4] = {CPU, idA, CPU, idB}, chr[4] = {0, 1, 2, 5};
        CHECK(slotsAre(st, owner, chr) && st.isAuto[0], "Cara's port returns to an auto CPU");
        b.waitFor(PB_MSG_ROOM_STATE, 3000);
        enet_host_destroy(c.host);
    }
    // ---- Continuing a saved game ----
    {
        const uint8_t savedChars[4] = {7, 6, 5, 4};
        const char *const savedNames[4] = {"", "Bob", "Alice", ""};
        setContinue(b, true, savedChars, savedNames);
        CHECK(expectError(b, PB_ERR_NOT_HOST), "only the host can continue a game");
        setContinue(a, true, savedChars, savedNames);
        RoomState st = parseRoomState(b.waitFor(PB_MSG_ROOM_STATE));
        const uint8_t owner[4] = {CPU, idB, idA, CPU};
        CHECK(slotsAre(st, owner, savedChars) && st.continuing, "continue reseats by name: Bob P2, Alice P3, chars fixed");
        CHECK(st.savedName[1] == "Bob" && st.savedName[2] == "Alice" && st.savedName[0].empty(), "saved names listed");
        a.waitFor(PB_MSG_ROOM_STATE);
        choose(b, KEEP, 0);
        CHECK(expectError(b, PB_ERR_TAKEN), "characters are fixed in a continued game");
        choose(b, 3, KEEP); // Bob takes the CPU seat P4; the characters stay with the ports
        st = parseRoomState(a.waitFor(PB_MSG_ROOM_STATE));
        const uint8_t owner2[4] = {CPU, CPU, idA, idB};
        CHECK(slotsAre(st, owner2, savedChars), "moving keeps each port's character");
        b.waitFor(PB_MSG_ROOM_STATE);
        setLayout(a, std::array<uint8_t, 4>{idB, CPU, idA, CPU}.data(), std::array<uint8_t, 4>{0, 1, 2, 3}.data());
        CHECK(expectError(a, PB_ERR_BAD_SETTINGS), "a continued game's layout can't change characters");

        TestClient c;
        CHECK(c.connect(hostname, port), "third client connects");
        hello(c, "Cara");
        c.waitFor(PB_MSG_WELCOME);
        simple(c, PB_MSG_JOIN_ROOM, code, 4);
        st = parseRoomState(c.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.count == 3 && st.chr[0] == 7 && st.owner[0] != CPU && st.owner[1] == CPU,
              "a newcomer takes a seat a CPU played (P1), not Bob's saved seat (P2)");
        a.waitFor(PB_MSG_ROOM_STATE);
        b.waitFor(PB_MSG_ROOM_STATE);
        enet_peer_disconnect(c.peer, 0);
        c.pump(200);
        st = parseRoomState(a.waitFor(PB_MSG_ROOM_STATE, 3000));
        CHECK(st.ok && st.owner[0] == CPU && st.chr[0] == 7 && !st.isAuto[0], "a leaver's seat keeps its character");
        b.waitFor(PB_MSG_ROOM_STATE, 3000);
        enet_host_destroy(c.host);

        // Starting a continued game needs the saved state, and everyone gets it as sent.
        PbNetSettings cs{};
        cs.seed = 99;
        cs.turns = 20;
        cs.cpuLevel = 2;
        cs.inputDelay = 4;
        uint8_t cbuf[64 + 412];
        PbNetWriter cw;
        pbw_init(&cw, cbuf, sizeof(cbuf));
        pbw_settings(&cw, &cs);
        pbw_u16(&cw, 0);
        simple(a, PB_MSG_START_GAME, cbuf, cw.pos);
        CHECK(expectError(a, PB_ERR_BAD_SETTINGS), "a continued game can't start without its saved state");
        uint8_t state[412];
        for (int i = 0; i < 412; i++) state[i] = static_cast<uint8_t>(i * 7);
        pbw_init(&cw, cbuf, sizeof(cbuf));
        pbw_settings(&cw, &cs);
        pbw_u16(&cw, sizeof(state));
        pbw_bytes(&cw, state, sizeof(state));
        {
            uint8_t msg[sizeof(cbuf) + 1];
            msg[0] = PB_MSG_START_GAME;
            std::memcpy(msg + 1, cbuf, cw.pos);
            PbNetWriter mw;
            mw.data = msg;
            mw.size = sizeof(msg);
            mw.pos = cw.pos + 1;
            mw.overflow = 0;
            a.send(PB_NET_CHANNEL_CONTROL, mw);
        }
        auto ga = a.waitFor(PB_MSG_GAME_START);
        auto gb = b.waitFor(PB_MSG_GAME_START);
        bool stateOk = false;
        if (!gb.empty()) {
            PbNetReader r;
            PbNetSettings got;
            pbr_init(&r, gb.data() + 1, gb.size() - 1);
            pbr_settings(&r, &got);
            const uint16_t n = pbr_u16(&r);
            stateOk = !r.error && n == sizeof(state) && r.size - r.pos == n &&
                      std::memcmp(gb.data() + 1 + r.pos, state, n) == 0 && got.portOwner[3] == idB && got.chars[0] == 7;
        }
        CHECK(!ga.empty() && ga == gb && stateOk, "both get the continued game's start with the saved state");
        // A desync restarts everyone from the last agreed save point: here none yet, so the continued game's own
        // start. Everyone rejoins by name and gets the same start again. The third desync in a row ends the game.
        for (int round = 0; round < 3; round++) {
            sendChecksum(a, 60, 1);
            sendChecksum(b, 60, 2);
            CHECK(!a.waitFor(PB_MSG_DESYNC).empty() && !b.waitFor(PB_MSG_DESYNC).empty(), "desync %d reported", round + 1);
            if (round == 2) break;
            auto ra = a.waitFor(PB_MSG_RESTART);
            auto rb = b.waitFor(PB_MSG_RESTART);
            CHECK(ra.size() == 2 && ra[1] == PB_RESTART_DESYNC && ra == rb, "desync %d restarts everyone", round + 1);
            simple(b, PB_MSG_JOIN_ROOM, code, 4); // Bob back first: Alice still gets host back by name
            simple(a, PB_MSG_JOIN_ROOM, code, 4);
            auto ga2 = a.waitFor(PB_MSG_GAME_START);
            auto gb2 = b.waitFor(PB_MSG_GAME_START);
            CHECK(!ga2.empty() && ga2 == ga && gb2 == ga,
                  "after restart %d both get the same start again (Alice P3, Bob P4, saved state)", round + 1);
        }
        CHECK(!a.waitFor(PB_MSG_GAME_ENDED).empty() && !b.waitFor(PB_MSG_GAME_ENDED).empty(),
              "a desync that restarting didn't fix ends the game");
        // Then Bob leaves the room and comes back by its code.
        simple(b, PB_MSG_LEAVE_ROOM);
        a.waitFor(PB_MSG_ROOM_STATE);
        simple(b, PB_MSG_JOIN_ROOM, code, 4);
        st = parseRoomState(b.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.owner[1] == idB, "rejoining a continued room by name takes the saved seat back (P2)");
        a.waitFor(PB_MSG_ROOM_STATE);
        setContinue(a, false, savedChars, savedNames);
        st = parseRoomState(b.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && !st.continuing, "back to a new game");
        a.waitFor(PB_MSG_ROOM_STATE);
    }
    // Back to Alice P1, Bob P2 for the lockstep checks below, with a host-picked CPU on P4.
    setLayout(a, std::array<uint8_t, 4>{idA, idB, CPU, CPU}.data(), std::array<uint8_t, 4>{6, 1, AUTO, 0}.data());
    a.waitFor(PB_MSG_ROOM_STATE);
    b.waitFor(PB_MSG_ROOM_STATE);

    // Only the host may start.
    PbNetSettings s{};
    s.seed = 1234;
    s.board = 0;
    s.turns = 10;
    s.cpuLevel = 1;
    s.inputDelay = 4;
    // Deliberately wrong: the server must use the lobby's seating instead.
    s.chars[0] = 3; s.chars[1] = 3; s.chars[2] = 3; s.chars[3] = 3;
    s.portOwner[0] = idB; s.portOwner[1] = idB; s.portOwner[2] = idB; s.portOwner[3] = idB;
    uint8_t sbuf[64];
    PbNetWriter sw;
    pbw_init(&sw, sbuf, sizeof(sbuf));
    pbw_settings(&sw, &s);
    pbw_u16(&sw, 0); // a new game: no saved state
    simple(b, PB_MSG_START_GAME, sbuf, sw.pos);
    CHECK(!b.waitFor(PB_MSG_ERROR).empty(), "non-host start is rejected");
    simple(a, PB_MSG_START_GAME, sbuf, sw.pos);
    auto startA = a.waitFor(PB_MSG_GAME_START);
    auto startB = b.waitFor(PB_MSG_GAME_START);
    CHECK(!startA.empty() && startA == startB, "both clients get identical GAME_START");
    if (!startA.empty()) {
        PbNetReader r;
        PbNetSettings got;
        pbr_init(&r, startA.data() + 1, startA.size() - 1);
        pbr_settings(&r, &got);
        const uint8_t owner[4] = {idA, idB, CPU, CPU}, chr[4] = {6, 1, 2, 0};
        CHECK(!r.error && std::memcmp(got.portOwner, owner, 4) == 0 && std::memcmp(got.chars, chr, 4) == 0,
              "GAME_START carries the lobby's seating (Daisy, Luigi, auto Peach, Mario)");
        CHECK(got.seed == 1234 && got.turns == 10, "GAME_START keeps the host's game options");
    }
    choose(b, KEEP, 4);
    CHECK(expectError(b, PB_ERR_IN_GAME), "no character changes mid-game");

    // Lockstep: a frame is only released once both players' inputs arrive.
    sendInput(a, 0, 0xA1);
    a.pump(100);
    CHECK(a.waitFor(PB_MSG_FRAME, 200).empty(), "frame 0 withheld until Bob's input arrives");
    {
        auto waiting = a.waitFor(PB_MSG_WAITING, 1500);
        CHECK(waiting.size() == 4 && waiting[1] == 0x02, "a stalled frame names the missing player's port (Bob, P2)");
    }
    sendInput(b, 0, 0xB1);
    auto f0 = a.waitFor(PB_MSG_FRAME);
    CHECK(f0.size() == 1 + 4 + 2 + 2 * kPadSize, "frame 0 carries two pads");
    if (f0.size() == 1 + 4 + 2 + 2 * kPadSize) {
        CHECK(f0[5] == 0x03, "human mask covers ports 0 and 1");
        CHECK(f0[6] == 0, "no reload flag");
        CHECK(f0[7] == 0xA1 && f0[7 + kPadSize] == 0xB1, "pads in port order");
    }
    b.waitFor(PB_MSG_FRAME);

    // 300 frames, sent out of step, must arrive complete and in order.
    const uint32_t frames = 300;
    for (uint32_t f = 1; f <= frames; f++) sendInput(a, f, static_cast<uint8_t>(f));
    for (uint32_t f = 1; f <= frames; f++) sendInput(b, f, static_cast<uint8_t>(f + 1));
    uint32_t expect = 1;
    for (uint32_t i = 0; i < frames; i++) {
        auto msg = b.waitFor(PB_MSG_FRAME);
        if (msg.size() < 6) break;
        PbNetReader r;
        pbr_init(&r, msg.data() + 1, msg.size() - 1);
        const uint32_t f = pbr_u32(&r);
        CHECK(f == expect, "frames in order (got %u, expected %u)", f, expect);
        expect = f + 1;
    }
    CHECK(expect == frames + 1, "all %u frames delivered (last %u)", frames, expect - 1);

    // Both reach a save point with the same state: that becomes the point a desync restarts from.
    uint8_t saved[412];
    for (int i = 0; i < 412; i++) saved[i] = static_cast<uint8_t>(i * 5 + 1);
    sendSavePoint(a, 250, false, saved, sizeof(saved));
    sendSavePoint(b, 250, false, saved, sizeof(saved));

    // Matching checksums are silent; a mismatch restarts everyone from that save point.
    sendChecksum(a, 60, 0x1111);
    sendChecksum(b, 60, 0x1111);
    CHECK(a.waitFor(PB_MSG_DESYNC, 300).empty(), "matching checksums cause no desync");
    sendChecksum(a, 120, 0x2222);
    sendChecksum(b, 120, 0x3333);
    CHECK(!a.waitFor(PB_MSG_DESYNC).empty() && !b.waitFor(PB_MSG_DESYNC).empty(), "mismatch reported to both");
    CHECK(!a.waitFor(PB_MSG_RESTART).empty() && !b.waitFor(PB_MSG_RESTART).empty(), "both told to restart");
    simple(a, PB_MSG_JOIN_ROOM, code, 4);
    simple(b, PB_MSG_JOIN_ROOM, code, 4);
    {
        auto sa = a.waitFor(PB_MSG_GAME_START);
        auto sb = b.waitFor(PB_MSG_GAME_START);
        bool ok = false;
        if (!sa.empty()) {
            PbNetReader r;
            PbNetSettings got;
            pbr_init(&r, sa.data() + 1, sa.size() - 1);
            pbr_settings(&r, &got);
            const uint16_t n = pbr_u16(&r);
            ok = !r.error && n == sizeof(saved) && std::memcmp(sa.data() + 1 + r.pos, saved, n) == 0 &&
                 got.portOwner[0] == idA && got.portOwner[1] == idB && got.seed == 1234;
        }
        CHECK(ok && sa == sb, "the restarted game goes on from the agreed save point");
    }

    // A player leaving mid-game: their port becomes CPU and the game goes on for the rest.
    sendInput(a, 0, 0x11);
    sendInput(a, 1, 0x12); // frames 0-1 wait on Bob...
    sendInput(b, 0, 0x21);
    auto g0 = a.waitFor(PB_MSG_FRAME);
    CHECK(g0.size() > 5 && g0[5] == 0x03, "frame 0 has both players");
    enet_peer_disconnect(b.peer, 0);
    b.pump(200);
    auto dropped = a.waitFor(PB_MSG_PLAYER_DROPPED, 3000);
    CHECK(dropped.size() == 6 && dropped[1] == idB, "Bob's drop is announced");
    if (dropped.size() == 6) {
        PbNetReader r;
        pbr_init(&r, dropped.data() + 2, 4);
        CHECK(pbr_u32(&r) == 1, "takeover starts at the first frame not yet sent");
    }
    // ...and frame 1 is released with Alice alone, without waiting for Bob.
    auto g1 = a.waitFor(PB_MSG_FRAME);
    CHECK(g1.size() == 1 + 4 + 2 + kPadSize && g1[5] == 0x01, "frame 1 carries only Alice's pad");
    CHECK(a.waitFor(PB_MSG_GAME_ENDED, 300).empty(), "the game keeps going");
    sendInput(a, 2, 0x13);
    CHECK(!a.waitFor(PB_MSG_FRAME).empty(), "later frames flow with one human");

    // ---- Rejoining mid-game ----
    {
        // Someone with the name of a person still playing is told to try again (their old connection lingers).
        TestClient a2;
        CHECK(a2.connect(hostname, port), "second Alice connects");
        hello(a2, "Alice");
        const uint8_t idA2 = a2.waitFor(PB_MSG_WELCOME)[1];
        simple(a2, PB_MSG_JOIN_ROOM, code, 4);
        CHECK(expectError(a2, PB_ERR_IN_GAME), "joining under the name of someone still playing is refused");

        // Bob comes back: he waits on his old seat (P2), the players hear about it, FRAMEs ask for a reload.
        TestClient b2;
        CHECK(b2.connect(hostname, port), "Bob reconnects");
        hello(b2, "Bob");
        const uint8_t idB2 = b2.waitFor(PB_MSG_WELCOME)[1];
        simple(b2, PB_MSG_JOIN_ROOM, code, 4);
        RoomState st = parseRoomState(b2.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.phase == PB_ROOM_IN_GAME && st.count == 2, "Bob is in the room, waiting for the game");
        auto rejoining = a.waitFor(PB_MSG_REJOINING);
        CHECK(rejoining.size() > 2 && rejoining[1] == 1, "Alice hears that Bob is coming back to P2");
        sendInput(a, 3, 0x14);
        auto f3 = a.waitFor(PB_MSG_FRAME);
        CHECK(f3.size() > 6 && f3[5] == 0x01 && (f3[6] & PB_FRAME_RELOAD), "frames carry the reload flag");
        CHECK(b2.waitFor(PB_MSG_FRAME, 300).empty(), "the waiting player gets no game frames");
        sendChecksum(a, 180, 0x4444);
        CHECK(a.waitFor(PB_MSG_DESYNC, 300).empty(), "checksums only count the players in the game");

        // Alice's game reaches the save point: the room reloads; Bob keeps P2, P1 waits for Alice by name.
        uint8_t state[412];
        for (int i = 0; i < 412; i++) state[i] = static_cast<uint8_t>(i * 3);
        sendSavePoint(a, 4, true, state, sizeof(state));
        st = parseRoomState(b2.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.phase == PB_ROOM_RELOADING && st.count == 1 && st.owner[1] == idB2 && st.owner[0] == CPU &&
                  st.continuing && st.savedName[0] == "Alice" && st.savedName[1] == "Bob",
              "reloading: Bob seated on P2, P1 kept for Alice");
        CHECK(st.chr[0] == 6 && st.chr[1] == 1 && st.chr[3] == 0, "characters stay with their ports");
        choose(b2, 0, KEEP);
        CHECK(expectError(b2, PB_ERR_IN_GAME), "no seat changes while reloading");

        // Alice's restarted game joins: the game starts by itself from the saved state, Alice host again.
        simple(a2, PB_MSG_JOIN_ROOM, code, 4);
        st = parseRoomState(a2.waitFor(PB_MSG_ROOM_STATE));
        CHECK(st.ok && st.owner[0] == idA2 && st.host == idA2, "Alice takes P1 back by name and is host again");
        auto ga = a2.waitFor(PB_MSG_GAME_START);
        auto gb = b2.waitFor(PB_MSG_GAME_START);
        bool ok = false;
        if (!ga.empty()) {
            PbNetReader r;
            PbNetSettings got;
            pbr_init(&r, ga.data() + 1, ga.size() - 1);
            pbr_settings(&r, &got);
            const uint16_t n = pbr_u16(&r);
            const uint8_t owner[4] = {idA2, idB2, CPU, CPU}, chr[4] = {6, 1, 2, 0};
            ok = !r.error && n == sizeof(state) && std::memcmp(ga.data() + 1 + r.pos, state, n) == 0 &&
                 std::memcmp(got.portOwner, owner, 4) == 0 && std::memcmp(got.chars, chr, 4) == 0 && got.seed == 1234;
        }
        CHECK(ok && ga == gb, "the reloaded game starts for both from the saved state, Bob human on P2 again");
        sendInput(a2, 0, 0x31);
        sendInput(b2, 0, 0x32);
        auto r0 = b2.waitFor(PB_MSG_FRAME);
        CHECK(r0.size() == 1 + 4 + 2 + 2 * kPadSize && r0[5] == 0x03 && r0[6] == 0, "the reloaded game's lockstep has both");
        CHECK(a.waitFor(PB_MSG_FRAME, 300).empty(), "the old connection is out of the room");
        enet_host_destroy(a2.host);
        enet_host_destroy(b2.host);
    }

    std::printf(gFailures ? "%d check(s) FAILED\n" : "all checks passed\n", gFailures);
    enet_deinitialize();
    return gFailures ? 1 : 0;
}
