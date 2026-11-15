// Integration test for the relay server: two simulated players over real UDP.
//   partyboard-server-test [host] [port]
// Exits 0 if every check passes.

#include "netplay/protocol.h"

#include <enet/enet.h>

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

    // Only the host may start.
    PbNetSettings s{};
    s.seed = 1234;
    s.board = 0;
    s.turns = 10;
    s.cpuLevel = 1;
    s.inputDelay = 4;
    s.chars[0] = 0; s.chars[1] = 1; s.chars[2] = 2; s.chars[3] = 3;
    s.portOwner[0] = idA; s.portOwner[1] = idB; s.portOwner[2] = PB_NET_PORT_CPU; s.portOwner[3] = PB_NET_PORT_CPU;
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

    // A player leaving mid-game ends it for the rest.
    simple(a, PB_MSG_START_GAME, sbuf, sw.pos);
    a.waitFor(PB_MSG_GAME_START);
    b.waitFor(PB_MSG_GAME_START);
    enet_peer_disconnect(b.peer, 0);
    b.pump(200);
    auto ended = a.waitFor(PB_MSG_GAME_ENDED, 3000);
    CHECK(ended.size() == 3 && ended[1] == PB_END_PLAYER_LEFT && ended[2] == idB, "Bob leaving ends the game");

    std::printf(gFailures ? "%d check(s) FAILED\n" : "all checks passed\n", gFailures);
    enet_deinitialize();
    return gFailures ? 1 : 0;
}
