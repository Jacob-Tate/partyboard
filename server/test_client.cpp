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
    }
    for (int port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        st.owner[port] = pbr_u8(&r);
        st.chr[port] = pbr_u8(&r);
        st.isAuto[port] = pbr_u8(&r);
    }
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
    sendInput(b, 0, 0xB1);
    auto f0 = a.waitFor(PB_MSG_FRAME);
    CHECK(f0.size() == 1 + 4 + 1 + 2 * kPadSize, "frame 0 carries two pads");
    if (f0.size() == 1 + 4 + 1 + 2 * kPadSize) {
        CHECK(f0[5] == 0x03, "human mask covers ports 0 and 1");
        CHECK(f0[6] == 0xA1 && f0[6 + kPadSize] == 0xB1, "pads in port order");
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

    // Matching checksums are silent; a mismatch ends the game for everyone.
    sendChecksum(a, 60, 0x1111);
    sendChecksum(b, 60, 0x1111);
    CHECK(a.waitFor(PB_MSG_DESYNC, 300).empty(), "matching checksums cause no desync");
    sendChecksum(a, 120, 0x2222);
    sendChecksum(b, 120, 0x3333);
    CHECK(!a.waitFor(PB_MSG_DESYNC).empty() && !b.waitFor(PB_MSG_DESYNC).empty(), "mismatch reported to both");
    CHECK(!a.waitFor(PB_MSG_GAME_ENDED).empty(), "game ended after desync");

    // A player leaving mid-game: their port becomes CPU and the game goes on for the rest.
    simple(a, PB_MSG_START_GAME, sbuf, sw.pos);
    a.waitFor(PB_MSG_GAME_START);
    b.waitFor(PB_MSG_GAME_START);
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
    CHECK(g1.size() == 1 + 4 + 1 + kPadSize && g1[5] == 0x01, "frame 1 carries only Alice's pad");
    CHECK(a.waitFor(PB_MSG_GAME_ENDED, 300).empty(), "the game keeps going");
    sendInput(a, 2, 0x13);
    CHECK(!a.waitFor(PB_MSG_FRAME).empty(), "later frames flow with one human");

    std::printf(gFailures ? "%d check(s) FAILED\n" : "all checks passed\n", gFailures);
    enet_deinitialize();
    return gFailures ? 1 : 0;
}
