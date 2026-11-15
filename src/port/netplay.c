#include "port/netplay.h"

#include "netplay/protocol.h"
#include "game/gamework_data.h"
#include "port/autotest.h"
#include "port/main.h"

#include <enet/enet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NET_RING 1024           // received frames buffered ahead of the game
#define NET_WAIT_TIMEOUT_MS 20000 // give up if a frame's inputs haven't arrived in this long

typedef struct NetFrame {
    u32 frame;
    int valid;
    u8 humanMask;
    PADStatus pads[PB_NET_MAX_PLAYERS];
} NetFrame;

static const char *sServerHost = NULL;
static u16 sServerPort = PB_NET_DEFAULT_PORT;
static int sCreate = 0;
static char sJoinCode[PB_NET_ROOM_CODE_LEN + 1];
static int sPlayers = 2;
static int sDelay = 4;
static char sName[PB_NET_MAX_NAME + 1];

static ENetHost *sHost = NULL;
static ENetPeer *sPeer = NULL;
static u8 sClientId = 0;
static int sActive = 0;
static int sEnded = 0;
static PbNetSettings sSettings;
static u8 sHumanMask = 0;
static u8 sOwnedMask = 0;
static u32 sFrame = 0; // next frame the game will consume
static int sPrimed = 0;
static NetFrame sRing[NET_RING];
static char sBuildId[PB_NET_MAX_BUILD_ID + 1];

// ---- options ----

int partyboard_netplay_parse(int argc, char *argv[])
{
    int i;
    int ok = 1;
    const char *user = getenv("USERNAME");
    snprintf(sName, sizeof(sName), "%s", user && user[0] ? user : "Player");
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        const char *next = (i + 1 < argc) ? argv[i + 1] : NULL;
        if (strcmp(arg, "--server") == 0 && next) {
            static char host[256];
            char *colon;
            snprintf(host, sizeof(host), "%s", next);
            colon = strrchr(host, ':');
            if (colon) {
                *colon = '\0';
                sServerPort = (u16)atoi(colon + 1);
            }
            sServerHost = host;
            i++;
        } else if (strcmp(arg, "--create") == 0) {
            sCreate = 1;
        } else if (strcmp(arg, "--join") == 0 && next) {
            int k;
            if (strlen(next) != PB_NET_ROOM_CODE_LEN) {
                fprintf(stderr, "[netplay] room codes are %d letters\n", PB_NET_ROOM_CODE_LEN);
                ok = 0;
            }
            for (k = 0; k < PB_NET_ROOM_CODE_LEN && next[k]; k++) {
                sJoinCode[k] = (char)((next[k] >= 'a' && next[k] <= 'z') ? next[k] - 32 : next[k]);
            }
            i++;
        } else if (strcmp(arg, "--players") == 0 && next) {
            sPlayers = atoi(next);
            if (sPlayers < 1 || sPlayers > PB_NET_MAX_PLAYERS) {
                fprintf(stderr, "[netplay] --players expects 1-4\n");
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--delay") == 0 && next) {
            sDelay = atoi(next);
            if (sDelay < 1 || sDelay > 30) {
                fprintf(stderr, "[netplay] --delay expects 1-30 frames\n");
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--name") == 0 && next) {
            snprintf(sName, sizeof(sName), "%s", next);
            i++;
        }
    }
    if (sServerHost) {
        if (sCreate == (sJoinCode[0] != '\0')) {
            fprintf(stderr, "[netplay] use exactly one of --create or --join CODE with --server\n");
            ok = 0;
        }
        if (partyboard_autotest_get()->fast) {
            fprintf(stderr, "[netplay] --fast can't be used online\n");
            ok = 0;
        }
    }
    // Same executable on every machine => same build id. (Compile time of this file.)
    snprintf(sBuildId, sizeof(sBuildId), "%s %s/%u", __DATE__, __TIME__, (unsigned)sizeof(PADStatus));
    return ok;
}

int partyboard_netplay_requested(void)
{
    return sServerHost != NULL;
}

int partyboard_netplay_active(void)
{
    return sActive;
}

// ---- sending ----

static void send_writer(int channel, const PbNetWriter *w)
{
    ENetPacket *packet = enet_packet_create(w->data, w->pos, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(sPeer, (enet_uint8)channel, packet);
    enet_host_flush(sHost);
}

static void send_input(u32 frame, const PADStatus *local)
{
    u8 buf[8 + PB_NET_MAX_PLAYERS * sizeof(PADStatus)];
    PbNetWriter w;
    int port;
    int localIndex = 0;
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_INPUT);
    pbw_u32(&w, frame);
    // The first port this client owns takes its controller 1, the second takes controller 2, ...
    for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (sOwnedMask & (1 << port)) {
            pbw_bytes(&w, &local[localIndex++], sizeof(PADStatus));
        }
    }
    send_writer(PB_NET_CHANNEL_INPUT, &w);
}

// ---- receiving ----

static void end_game(const char *why)
{
    if (!sEnded) {
        sEnded = 1;
        printf("[netplay] %s\n", why);
        fflush(stdout);
        PartyBoard_IsRunning = false;
    }
}

static void handle_frame(PbNetReader *r)
{
    const u32 frame = pbr_u32(r);
    const u8 mask = pbr_u8(r);
    NetFrame *slot = &sRing[frame % NET_RING];
    int port;
    if (r->error || frame < sFrame || frame >= sFrame + NET_RING) {
        return;
    }
    memset(slot, 0, sizeof(*slot));
    slot->humanMask = mask;
    for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (mask & (1 << port)) {
            pbr_bytes(r, &slot->pads[port], sizeof(PADStatus));
        } else {
            // CPU port: a fixed "no controller" state, identical on every machine.
            slot->pads[port].err = PAD_ERR_NO_CONTROLLER;
        }
    }
    if (!r->error) {
        slot->frame = frame;
        slot->valid = 1;
    }
}

// Lobby-phase state, filled by handle_packet.
static int sWelcomed = 0;
static int sGameStarted = 0;
static int sLobbyError = 0;
static u8 sRoomHost = 0;
static u8 sRoomCount = 0;
static u8 sRoomIds[PB_NET_MAX_PLAYERS];
static char sRoomCode[PB_NET_ROOM_CODE_LEN + 1];

static void handle_packet(const u8 *data, size_t size)
{
    PbNetReader r;
    u8 type;
    pbr_init(&r, data, size);
    type = pbr_u8(&r);
    switch (type) {
    case PB_MSG_WELCOME:
        sClientId = pbr_u8(&r);
        sWelcomed = 1;
        break;
    case PB_MSG_ERROR: {
        char message[256];
        const u8 code = pbr_u8(&r);
        pbr_str(&r, message, sizeof(message));
        printf("[netplay] server error %u: %s\n", code, message);
        sLobbyError = 1;
        break;
    }
    case PB_MSG_ROOM_STATE: {
        int i;
        pbr_bytes(&r, sRoomCode, PB_NET_ROOM_CODE_LEN);
        sRoomCode[PB_NET_ROOM_CODE_LEN] = '\0';
        sRoomHost = pbr_u8(&r);
        sRoomCount = pbr_u8(&r);
        printf("[netplay] room %s, %u player(s):", sRoomCode, sRoomCount);
        for (i = 0; i < sRoomCount && i < PB_NET_MAX_PLAYERS; i++) {
            char name[PB_NET_MAX_NAME + 1];
            sRoomIds[i] = pbr_u8(&r);
            pbr_str(&r, name, sizeof(name));
            printf(" %s%s", name, sRoomIds[i] == sRoomHost ? " (host)" : "");
        }
        printf("\n");
        fflush(stdout);
        break;
    }
    case PB_MSG_GAME_START:
        pbr_settings(&r, &sSettings);
        if (!r.error) {
            sGameStarted = 1;
        }
        break;
    case PB_MSG_FRAME:
        handle_frame(&r);
        break;
    case PB_MSG_DESYNC: {
        char why[96];
        snprintf(why, sizeof(why), "DESYNC detected at frame %u - the game has drifted apart", pbr_u32(&r));
        end_game(why);
        break;
    }
    case PB_MSG_PLAYER_DROPPED: {
        const u8 who = pbr_u8(&r);
        const u32 frame = pbr_u32(&r);
        printf("[netplay] player %u disconnected; a CPU takes over from frame %u\n", who, frame);
        fflush(stdout);
        break;
    }
    case PB_MSG_GAME_ENDED: {
        const u8 reason = pbr_u8(&r);
        end_game(reason == PB_END_PLAYER_LEFT ? "a player left, game over" : "game ended by the server");
        break;
    }
    default:
        break;
    }
}

// Services the connection for up to timeoutMs. Returns 0 if the connection dropped.
static int pump(int timeoutMs)
{
    ENetEvent event;
    int connected = 1;
    while (enet_host_service(sHost, &event, (enet_uint32)timeoutMs) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            handle_packet(event.packet->data, event.packet->dataLength);
            enet_packet_destroy(event.packet);
        } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
            connected = 0;
        }
        timeoutMs = 0;
    }
    return connected;
}

// ---- lobby ----

static void start_game_as_host(void)
{
    const PartyBoardAutotest *t = partyboard_autotest_get();
    PbNetSettings s;
    u8 buf[64];
    PbNetWriter w;
    int i;
    memset(&s, 0, sizeof(s));
    s.seed = t->seedSet ? t->seed : (u32)time(NULL);
    s.board = (u8)t->board;
    s.turns = (u8)t->turns;
    s.cpuLevel = (u8)t->cpuLevel;
    s.inputDelay = (u8)sDelay;
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        s.chars[i] = (u8)t->chars[i];
        s.portOwner[i] = i < sRoomCount ? sRoomIds[i] : PB_NET_PORT_CPU;
    }
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_START_GAME);
    pbw_settings(&w, &s);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
}

int partyboard_netplay_lobby(void)
{
    ENetAddress address;
    ENetEvent event;
    u8 buf[256];
    PbNetWriter w;
    int i;
    int chars[PB_NET_MAX_PLAYERS];

    if (enet_initialize() != 0) {
        fprintf(stderr, "[netplay] network init failed\n");
        return 0;
    }
    sHost = enet_host_create(NULL, 1, PB_NET_CHANNEL_COUNT, 0, 0);
    if (!sHost || enet_address_set_host(&address, sServerHost) != 0) {
        fprintf(stderr, "[netplay] can't resolve server '%s'\n", sServerHost);
        return 0;
    }
    address.port = sServerPort;
    printf("[netplay] connecting to %s:%u as '%s'...\n", sServerHost, sServerPort, sName);
    fflush(stdout);
    sPeer = enet_host_connect(sHost, &address, PB_NET_CHANNEL_COUNT, 0);
    if (!sPeer || enet_host_service(sHost, &event, 5000) <= 0 || event.type != ENET_EVENT_TYPE_CONNECT) {
        fprintf(stderr, "[netplay] no answer from %s:%u (is UDP %u open?)\n", sServerHost, sServerPort, sServerPort);
        return 0;
    }
    enet_peer_timeout(sPeer, 0, 5000, 15000);

    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_HELLO);
    pbw_u16(&w, PB_NET_PROTOCOL_VERSION);
    pbw_str(&w, sName, PB_NET_MAX_NAME);
    pbw_str(&w, sBuildId, PB_NET_MAX_BUILD_ID);
    pbw_u8(&w, (u8)sizeof(PADStatus));
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    while (!sWelcomed && !sLobbyError) {
        if (!pump(100)) {
            fprintf(stderr, "[netplay] disconnected\n");
            return 0;
        }
    }
    if (sLobbyError) {
        return 0;
    }

    pbw_init(&w, buf, sizeof(buf));
    if (sCreate) {
        pbw_u8(&w, PB_MSG_CREATE_ROOM);
    } else {
        pbw_u8(&w, PB_MSG_JOIN_ROOM);
        pbw_bytes(&w, sJoinCode, PB_NET_ROOM_CODE_LEN);
    }
    send_writer(PB_NET_CHANNEL_CONTROL, &w);

    if (sCreate) {
        printf("[netplay] creating a room; waiting for %d player(s)...\n", sPlayers);
    } else {
        printf("[netplay] joining room %s; waiting for the host to start...\n", sJoinCode);
    }
    fflush(stdout);
    {
        int startSent = 0;
        u8 lastCount = 0;
        while (!sGameStarted) {
            if (!pump(100) || sLobbyError) {
                fprintf(stderr, "[netplay] left the lobby\n");
                return 0;
            }
            if (sCreate && sRoomCount != lastCount) {
                lastCount = sRoomCount;
                if (sRoomCount == 1) {
                    printf("[netplay] ROOM CODE: %s  (others run --server %s --join %s)\n", sRoomCode, sServerHost,
                        sRoomCode);
                    fflush(stdout);
                }
            }
            if (sCreate && !startSent && sRoomCount >= sPlayers) {
                start_game_as_host();
                startSent = 1;
            }
        }
    }

    // Game settings from the server: same on every machine.
    sHumanMask = 0;
    sOwnedMask = 0;
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        chars[i] = sSettings.chars[i];
        if (sSettings.portOwner[i] != PB_NET_PORT_CPU) {
            sHumanMask |= (u8)(1 << i);
        }
        if (sSettings.portOwner[i] == sClientId) {
            sOwnedMask |= (u8)(1 << i);
        }
    }
    partyboard_autotest_configure_netplay(sSettings.seed, sSettings.board, sSettings.turns, chars, sSettings.cpuLevel,
        sHumanMask);
    sActive = 1;
    printf("[netplay] game starting: board %u, %u turns, seed %u, input delay %u, your port(s) 0x%x\n",
        sSettings.board, sSettings.turns, sSettings.seed, sSettings.inputDelay, sOwnedMask);
    fflush(stdout);
    return 1;
}

// ---- in game ----

// Gives each local controller slot this client plays with (1, or 1 and 2, ...) a gamepad if it has
// none, so a fresh install works without visiting Settings. Keyboard bindings don't count: port 1
// has default keyboard bindings, and a gamepad works alongside them.
static void ensure_local_controllers(void)
{
    u32 slot;
    u32 slots = 0;
    int port;
    for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        slots += (sOwnedMask >> port) & 1;
    }
    for (slot = 0; slot < slots; slot++) {
        u32 index;
        if (PADGetIndexForPort(slot) >= 0) {
            continue;
        }
        for (index = 0; index < PADCount(); index++) {
            int taken = 0;
            u32 other;
            for (other = 0; other < PAD_MAX_CONTROLLERS; other++) {
                taken |= PADGetIndexForPort(other) == (s32)index;
            }
            if (!taken) {
                const char *name = PADGetNameForControllerIndex(index);
                PADSetPortForIndex(index, slot);
                printf("[netplay] using '%s' as your controller %u\n", name ? name : "gamepad", slot + 1);
                fflush(stdout);
                break;
            }
        }
    }
}

u32 partyboard_netplay_pad_read(PADStatus *status)
{
    PADStatus local[PB_NET_MAX_PLAYERS];
    NetFrame *slot;
    int waited = 0;
    int port;

    if (sEnded) {
        for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            memset(&status[port], 0, sizeof(PADStatus));
            status[port].err = PAD_ERR_NO_CONTROLLER;
        }
        return 0;
    }

    if (!sPrimed) {
        // Frames before the input delay elapses have no real input yet: send neutral pads.
        PADStatus neutral[PB_NET_MAX_PLAYERS];
        u32 f;
        memset(neutral, 0, sizeof(neutral));
        for (f = 0; f < sSettings.inputDelay; f++) {
            send_input(f, neutral);
        }
        sPrimed = 1;
    }

    if (sFrame % 60 == 0) {
        ensure_local_controllers();
    }
    if (sFrame == 120) { // ~2 s in: SDL reports connected gamepads as events once the game loop runs
        u32 index;
        const s32 mine = PADGetIndexForPort(0);
        printf("[netplay] gamepads connected: %u\n", PADCount());
        for (index = 0; index < PADCount(); index++) {
            const char *name = PADGetNameForControllerIndex(index);
            printf("[netplay]   %u: %s%s\n", index, name ? name : "?", (s32)index == mine ? "  <- your controller 1" : "");
        }
        if (mine < 0) {
            printf("[netplay] no gamepad on your controller 1; keyboard bindings only\n");
        }
        fflush(stdout);
    }
    PADRead(local);
    send_input(sFrame + sSettings.inputDelay, local);

    slot = &sRing[sFrame % NET_RING];
    while (!(slot->valid && slot->frame == sFrame)) {
        if (!pump(1)) {
            end_game("lost connection to the server");
            return partyboard_netplay_pad_read(status);
        }
        if (sEnded) {
            return partyboard_netplay_pad_read(status);
        }
        if (++waited > NET_WAIT_TIMEOUT_MS) {
            end_game("timed out waiting for the other players");
            return partyboard_netplay_pad_read(status);
        }
    }
    if (slot->humanMask != sHumanMask) {
        // A player dropped: every client reaches this frame's bundle with the same mask, so the
        // CPU takes over on the same frame everywhere.
        for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            if ((sHumanMask & (1 << port)) && !(slot->humanMask & (1 << port))) {
                GWPlayerCfg[port].iscom = 1;
                GWPlayerCfg[port].diff = sSettings.cpuLevel;
                GWPlayer[port].com = 1;
                GWPlayer[port].diff = sSettings.cpuLevel;
                printf("[netplay] frame %u: player %d is now a CPU\n", sFrame, port + 1);
                fflush(stdout);
            }
        }
        sHumanMask = slot->humanMask;
    }
    memcpy(status, slot->pads, sizeof(slot->pads));
    slot->valid = 0;
    sFrame++;
    pump(0);
    return 0;
}

void partyboard_netplay_checksum(u32 frame, u32 hash)
{
    u8 buf[16];
    PbNetWriter w;
    if (!sActive || sEnded) {
        return;
    }
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_CHECKSUM);
    pbw_u32(&w, frame);
    pbw_u32(&w, hash);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
}

void partyboard_netplay_shutdown(void)
{
    if (sPeer) {
        ENetEvent event;
        int i;
        enet_peer_disconnect(sPeer, 0);
        for (i = 0; i < 20 && enet_host_service(sHost, &event, 50) > 0; i++) {
            if (event.type == ENET_EVENT_TYPE_RECEIVE) {
                enet_packet_destroy(event.packet);
            } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
                break;
            }
        }
        sPeer = NULL;
    }
    if (sHost) {
        enet_host_destroy(sHost);
        sHost = NULL;
        enet_deinitialize();
    }
    sActive = 0;
}
