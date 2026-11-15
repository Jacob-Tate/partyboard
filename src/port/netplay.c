#include "port/netplay.h"

#include "netplay/protocol.h"
#include "game/gamework_data.h"
#include "port/autotest.h"
#include "port/main.h"
#include "port/ui.h"

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
static int sPrefPort = -1; // --port / Online screen: wanted port (0-3) and character (0-7), -1 = any
static int sPrefChar = -1;

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

static void parse_server(const char *server);

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
            parse_server(next);
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
        } else if (strcmp(arg, "--char") == 0 && next) {
            sPrefChar = atoi(next);
            if (sPrefChar < 0 || sPrefChar >= PB_NET_MAX_CHARS) {
                fprintf(stderr, "[netplay] --char expects a character id 0-7\n");
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--port") == 0 && next) {
            sPrefPort = atoi(next) - 1;
            if (sPrefPort < 0 || sPrefPort >= PB_NET_MAX_PLAYERS) {
                fprintf(stderr, "[netplay] --port expects 1-4\n");
                ok = 0;
            }
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

static u32 sEndedFrames = 0;

// The online game can't continue: tell the player, then quit after ~5 seconds (see pad_read).
static void end_game(const char *why)
{
    if (!sEnded) {
        sEnded = 1;
        sEndedFrames = 0;
        printf("[netplay] %s\n", why);
        fflush(stdout);
        ui_push_toast("", "Online game over", why, 6000);
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
static int sConnected = 0;
static int sWelcomed = 0;
static int sGameStarted = 0;
static int sLobbyError = 0;
static u8 sRoomHost = 0;
static u8 sRoomCount = 0;
static u8 sRoomIds[PB_NET_MAX_PLAYERS];
static char sRoomNames[PB_NET_MAX_PLAYERS][PB_NET_MAX_NAME + 1];
static char sRoomCode[PB_NET_ROOM_CODE_LEN + 1];
static u8 sSlotOwner[PB_NET_MAX_PLAYERS];
static u8 sSlotChar[PB_NET_MAX_PLAYERS];
static u8 sSlotAuto[PB_NET_MAX_PLAYERS];
static char sError[256];
static char sNotice[200]; // last rejected lobby request ("Luigi is taken by Bob"); not fatal
static u32 sRoomStateTime = 0; // enet_time_get() of the last one

static const char *const sCharNames[PB_NET_MAX_CHARS] = { "Mario", "Luigi", "Peach", "Yoshi", "Wario", "Donkey Kong",
    "Daisy", "Waluigi" };

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
        char message[200];
        const u8 code = pbr_u8(&r);
        pbr_str(&r, message, sizeof(message));
        printf("[netplay] server error %u: %s\n", code, message);
        fflush(stdout);
        if (sRoomCount > 0 && code != PB_ERR_VERSION) {
            // In a room, a rejected request (taken port/character, bad layout) isn't fatal.
            snprintf(sNotice, sizeof(sNotice), "%s", message);
        } else {
            snprintf(sError, sizeof(sError), "%s", message);
            sLobbyError = 1;
        }
        break;
    }
    case PB_MSG_ROOM_STATE: {
        int i;
        u8 count;
        pbr_bytes(&r, sRoomCode, PB_NET_ROOM_CODE_LEN);
        sRoomCode[PB_NET_ROOM_CODE_LEN] = '\0';
        sRoomHost = pbr_u8(&r);
        count = pbr_u8(&r);
        if (count > PB_NET_MAX_PLAYERS) {
            count = PB_NET_MAX_PLAYERS;
        }
        printf("[netplay] room %s, %u player(s):", sRoomCode, count);
        for (i = 0; i < count; i++) {
            sRoomIds[i] = pbr_u8(&r);
            pbr_str(&r, sRoomNames[i], sizeof(sRoomNames[i]));
            printf(" %s%s", sRoomNames[i], sRoomIds[i] == sRoomHost ? " (host)" : "");
        }
        printf("\n[netplay]   ");
        sRoomCount = count;
        for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
            sSlotOwner[i] = pbr_u8(&r);
            sSlotChar[i] = pbr_u8(&r);
            sSlotAuto[i] = pbr_u8(&r);
            if (sSlotChar[i] >= PB_NET_MAX_CHARS) {
                sSlotChar[i] = 0;
            }
            printf("P%d %s (%s)%s", i + 1, partyboard_netplay_slot_name(i), sCharNames[sSlotChar[i]], i < 3 ? ", " : "");
        }
        printf("\n");
        fflush(stdout);
        sRoomStateTime = enet_time_get();
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
    if (!sHost) {
        return 0;
    }
    while (enet_host_service(sHost, &event, (enet_uint32)timeoutMs) > 0) {
        if (event.type == ENET_EVENT_TYPE_CONNECT) {
            sConnected = 1;
        } else if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            handle_packet(event.packet->data, event.packet->dataLength);
            enet_packet_destroy(event.packet);
        } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
            connected = 0;
        }
        timeoutMs = 0;
    }
    return connected;
}

// ---- lobby state machine (shared by the in-game Online screen and the --server command line) ----

static PbNetLobbyState sState = PB_LOBBY_IDLE;
static int sWantCreate = 0;
static enet_uint32 sConnectStart = 0;
static int sEnetReady = 0;
static char sServerBuf[256];

static void drop_connection(void)
{
    if (sPeer) {
        enet_peer_disconnect_now(sPeer, 0);
        sPeer = NULL;
    }
    if (sHost) {
        enet_host_destroy(sHost);
        sHost = NULL;
    }
    sConnected = sWelcomed = sGameStarted = sLobbyError = 0;
    sRoomCount = 0;
    sRoomCode[0] = '\0';
    sNotice[0] = '\0';
}

static void fail(const char *why)
{
    snprintf(sError, sizeof(sError), "%s", why);
    printf("[netplay] %s\n", why);
    fflush(stdout);
    drop_connection();
    sState = PB_LOBBY_FAILED;
}

// Splits "host[:port]" into sServerBuf and sServerPort.
static void parse_server(const char *server)
{
    char *colon;
    snprintf(sServerBuf, sizeof(sServerBuf), "%s", server);
    sServerPort = PB_NET_DEFAULT_PORT;
    colon = strrchr(sServerBuf, ':');
    if (colon) {
        *colon = '\0';
        sServerPort = (u16)atoi(colon + 1);
    }
    sServerHost = sServerBuf;
}

int partyboard_netplay_begin(const char *server, const char *name, int create, const char *joinCode)
{
    ENetAddress address;
    int k;
    partyboard_netplay_leave();
    sError[0] = '\0';
    if (!server || !server[0]) {
        fail("enter the server address first");
        return 0;
    }
    if (!create && (!joinCode || strlen(joinCode) != PB_NET_ROOM_CODE_LEN)) {
        fail("room codes are 4 letters");
        return 0;
    }
    parse_server(server);
    snprintf(sName, sizeof(sName), "%s", name && name[0] ? name : "Player");
    sWantCreate = create;
    memset(sJoinCode, 0, sizeof(sJoinCode));
    for (k = 0; !create && k < PB_NET_ROOM_CODE_LEN; k++) {
        const char ch = joinCode[k];
        sJoinCode[k] = (char)((ch >= 'a' && ch <= 'z') ? ch - 32 : ch);
    }
    if (!sEnetReady) {
        if (enet_initialize() != 0) {
            fail("network init failed");
            return 0;
        }
        sEnetReady = 1;
    }
    sHost = enet_host_create(NULL, 1, PB_NET_CHANNEL_COUNT, 0, 0);
    if (!sHost || enet_address_set_host(&address, sServerHost) != 0) {
        char why[300];
        snprintf(why, sizeof(why), "can't find server '%s'", sServerHost);
        fail(why);
        return 0;
    }
    address.port = sServerPort;
    printf("[netplay] connecting to %s:%u as '%s'...\n", sServerHost, sServerPort, sName);
    fflush(stdout);
    sPeer = enet_host_connect(sHost, &address, PB_NET_CHANNEL_COUNT, 0);
    if (!sPeer) {
        fail("couldn't start connecting");
        return 0;
    }
    sConnectStart = enet_time_get();
    sState = PB_LOBBY_CONNECTING;
    return 1;
}

static void finalize_start(void)
{
    int i;
    int chars[PB_NET_MAX_PLAYERS];
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
    sState = PB_LOBBY_STARTED;
    printf("[netplay] game starting: board %u, %u turns, seed %u, input delay %u, chars %u,%u,%u,%u, your port(s) "
           "0x%x\n",
        sSettings.board, sSettings.turns, sSettings.seed, sSettings.inputDelay, sSettings.chars[0], sSettings.chars[1],
        sSettings.chars[2], sSettings.chars[3], sOwnedMask);
    fflush(stdout);
}

static void lobby_update(int timeoutMs)
{
    u8 buf[256];
    PbNetWriter w;
    if (sState == PB_LOBBY_IDLE || sState == PB_LOBBY_FAILED || sState == PB_LOBBY_STARTED) {
        return;
    }
    if (!pump(timeoutMs)) {
        fail(sState == PB_LOBBY_CONNECTING ? "no answer from the server" : "disconnected from the server");
        return;
    }
    if (sLobbyError) {
        char why[256];
        snprintf(why, sizeof(why), "%s", sError[0] ? sError : "server error");
        fail(why);
        return;
    }
    switch (sState) {
    case PB_LOBBY_CONNECTING:
        if (sConnected) {
            enet_peer_timeout(sPeer, 0, 5000, 15000);
            pbw_init(&w, buf, sizeof(buf));
            pbw_u8(&w, PB_MSG_HELLO);
            pbw_u16(&w, PB_NET_PROTOCOL_VERSION);
            pbw_str(&w, sName, PB_NET_MAX_NAME);
            pbw_str(&w, sBuildId, PB_NET_MAX_BUILD_ID);
            pbw_u8(&w, (u8)sizeof(PADStatus));
            send_writer(PB_NET_CHANNEL_CONTROL, &w);
            sState = PB_LOBBY_HELLO;
        } else if (enet_time_get() - sConnectStart > 5000) {
            char why[300];
            snprintf(why, sizeof(why), "no answer from %s:%u (is UDP port %u open?)", sServerHost, sServerPort,
                sServerPort);
            fail(why);
        }
        break;
    case PB_LOBBY_HELLO:
        if (sWelcomed) {
            pbw_init(&w, buf, sizeof(buf));
            if (sWantCreate) {
                pbw_u8(&w, PB_MSG_CREATE_ROOM);
            } else {
                pbw_u8(&w, PB_MSG_JOIN_ROOM);
                pbw_bytes(&w, sJoinCode, PB_NET_ROOM_CODE_LEN);
            }
            send_writer(PB_NET_CHANNEL_CONTROL, &w);
            sState = PB_LOBBY_JOINING;
        }
        break;
    case PB_LOBBY_JOINING:
    case PB_LOBBY_IN_ROOM:
        if (sState == PB_LOBBY_JOINING && sRoomCount > 0) {
            sState = PB_LOBBY_IN_ROOM;
            // Ask for the wanted port and character once, separately so a taken character doesn't
            // cancel the port move. Whatever is taken keeps the server's default.
            if (sPrefPort >= 0) {
                partyboard_netplay_choose(sPrefPort, -1);
            }
            if (sPrefChar >= 0) {
                partyboard_netplay_choose(-1, sPrefChar);
            }
        }
        if (sGameStarted) {
            finalize_start();
        }
        break;
    default:
        break;
    }
}

void partyboard_netplay_update(void)
{
    lobby_update(0);
}

int partyboard_netplay_start_game(int board, int turns, int inputDelay, int cpuLevel, u32 seed)
{
    PbNetSettings s;
    u8 buf[64];
    PbNetWriter w;
    int i;
    if (sState != PB_LOBBY_IN_ROOM || !partyboard_netplay_is_host()) {
        return 0;
    }
    memset(&s, 0, sizeof(s));
    s.seed = seed ? seed : (u32)time(NULL);
    s.board = (u8)board;
    s.turns = (u8)turns;
    s.cpuLevel = (u8)cpuLevel;
    s.inputDelay = (u8)inputDelay;
    // Ports and characters come from the room's seating (the server fills them in).
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        s.chars[i] = sSlotChar[i];
        s.portOwner[i] = sSlotOwner[i];
    }
    sNotice[0] = '\0';
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_START_GAME);
    pbw_settings(&w, &s);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    return 1;
}

void partyboard_netplay_set_preference(int port, int character)
{
    sPrefPort = port >= 0 && port < PB_NET_MAX_PLAYERS ? port : -1;
    sPrefChar = character >= 0 && character < PB_NET_MAX_CHARS ? character : -1;
}

int partyboard_netplay_choose(int port, int character)
{
    u8 buf[8];
    PbNetWriter w;
    if (sState != PB_LOBBY_IN_ROOM) {
        return 0;
    }
    sNotice[0] = '\0';
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_CHOOSE);
    pbw_u8(&w, port >= 0 && port < PB_NET_MAX_PLAYERS ? (u8)port : PB_NET_KEEP);
    pbw_u8(&w, character >= 0 && character < PB_NET_MAX_CHARS ? (u8)character : PB_NET_KEEP);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    return 1;
}

int partyboard_netplay_set_layout(const u8 owner[4], const u8 chars[4])
{
    u8 buf[16];
    PbNetWriter w;
    if (sState != PB_LOBBY_IN_ROOM || !partyboard_netplay_is_host()) {
        return 0;
    }
    sNotice[0] = '\0';
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_SET_LAYOUT);
    pbw_bytes(&w, owner, PB_NET_MAX_PLAYERS);
    pbw_bytes(&w, chars, PB_NET_MAX_PLAYERS);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    return 1;
}

int partyboard_netplay_client_id(void)
{
    return sWelcomed ? sClientId : -1;
}

int partyboard_netplay_member_id(int index)
{
    return (index >= 0 && index < sRoomCount) ? sRoomIds[index] : -1;
}

int partyboard_netplay_slot_owner(int port)
{
    return (sRoomCount > 0 && port >= 0 && port < PB_NET_MAX_PLAYERS) ? sSlotOwner[port] : PB_NET_PORT_CPU;
}

int partyboard_netplay_slot_char(int port)
{
    return (sRoomCount > 0 && port >= 0 && port < PB_NET_MAX_PLAYERS) ? sSlotChar[port] : -1;
}

int partyboard_netplay_slot_auto(int port)
{
    return (sRoomCount > 0 && port >= 0 && port < PB_NET_MAX_PLAYERS) ? sSlotAuto[port] : 0;
}

const char *partyboard_netplay_slot_name(int port)
{
    int i;
    const int owner = partyboard_netplay_slot_owner(port);
    if (owner == PB_NET_PORT_CPU) {
        return "CPU";
    }
    for (i = 0; i < sRoomCount; i++) {
        if (sRoomIds[i] == owner) {
            return sRoomNames[i];
        }
    }
    return "?";
}

int partyboard_netplay_my_port(void)
{
    int port;
    for (port = 0; sWelcomed && sRoomCount > 0 && port < PB_NET_MAX_PLAYERS; port++) {
        if (sSlotOwner[port] == sClientId) {
            return port;
        }
    }
    return -1;
}

const char *partyboard_netplay_notice(void)
{
    return sNotice;
}

const char *partyboard_netplay_char_name(int character)
{
    return (character >= 0 && character < PB_NET_MAX_CHARS) ? sCharNames[character] : "?";
}

void partyboard_netplay_leave(void)
{
    if (sState == PB_LOBBY_STARTED) {
        return; // the game owns the connection now
    }
    drop_connection();
    sState = PB_LOBBY_IDLE;
}

PbNetLobbyState partyboard_netplay_state(void)
{
    return sState;
}

const char *partyboard_netplay_error(void)
{
    return sError;
}

const char *partyboard_netplay_room_code(void)
{
    return sRoomCode;
}

int partyboard_netplay_is_host(void)
{
    return sRoomCount > 0 && sRoomHost == sClientId;
}

int partyboard_netplay_member_count(void)
{
    return sRoomCount;
}

const char *partyboard_netplay_member_name(int index)
{
    return (index >= 0 && index < sRoomCount) ? sRoomNames[index] : "";
}

// Command-line flow (--server ... --create/--join): console lobby before the window opens.
int partyboard_netplay_lobby(void)
{
    const PartyBoardAutotest *t = partyboard_autotest_get();
    int startSent = 0;
    int layoutSent = 0;
    int codeShown = 0;
    char server[300];
    char name[PB_NET_MAX_NAME + 1];
    char code[PB_NET_ROOM_CODE_LEN + 1];
    // begin() rewrites the server/name/code buffers, so hand it copies.
    snprintf(server, sizeof(server), "%s:%u", sServerHost, sServerPort);
    snprintf(name, sizeof(name), "%s", sName);
    snprintf(code, sizeof(code), "%s", sJoinCode);
    if (!partyboard_netplay_begin(server, name, sCreate, code)) {
        return 0;
    }
    if (sCreate) {
        printf("[netplay] creating a room; waiting for %d player(s)...\n", sPlayers);
    } else {
        printf("[netplay] joining room %s; waiting for the host to start...\n", sJoinCode);
    }
    fflush(stdout);
    while (sState != PB_LOBBY_STARTED) {
        lobby_update(50);
        if (sState == PB_LOBBY_FAILED) {
            return 0;
        }
        if (sNotice[0]) {
            printf("[netplay] %s\n", sNotice);
            fflush(stdout);
            sNotice[0] = '\0';
            if (startSent) {
                fail("the server rejected the game settings");
                return 0;
            }
        }
        if (sCreate && sState == PB_LOBBY_IN_ROOM && !codeShown) {
            printf("[netplay] ROOM CODE: %s  (others run --server %s --join %s)\n", sRoomCode, sServerHost, sRoomCode);
            fflush(stdout);
            codeShown = 1;
        }
        // Once everyone is in, give their --port/--char requests a moment to settle before starting.
        if (sCreate && !layoutSent && sState == PB_LOBBY_IN_ROOM && sRoomCount >= sPlayers &&
            enet_time_get() - sRoomStateTime > 1000) {
            // --chars on the host sets every port's character (people keep their ports).
            if (t->charsSet) {
                u8 chars[PB_NET_MAX_PLAYERS];
                int i;
                for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
                    chars[i] = (u8)t->chars[i];
                }
                partyboard_netplay_set_layout(sSlotOwner, chars);
            }
            layoutSent = 1;
            continue; // start once the server has answered with the final seating
        }
        if (sCreate && layoutSent && !startSent && sState == PB_LOBBY_IN_ROOM) {
            if (t->charsSet) {
                int i, match = 1;
                for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
                    match &= sSlotChar[i] == t->chars[i];
                }
                if (!match) {
                    continue;
                }
            }
            partyboard_netplay_start_game(t->board, t->turns, sDelay, t->cpuLevel, t->seedSet ? t->seed : 0);
            startSent = 1;
        }
    }
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
                {
                    char msg[128];
                    snprintf(msg, sizeof(msg), "Using %s as controller %u.", name ? name : "gamepad", slot + 1);
                    ui_push_toast("controller", "Controller", msg, 4000);
                }
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
        if (++sEndedFrames == 300) {
            PartyBoard_IsRunning = false;
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
                {
                    char msg[64];
                    snprintf(msg, sizeof(msg), "Player %d disconnected. A CPU takes over.", port + 1);
                    ui_push_toast("", "Player left", msg, 5000);
                }
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
    }
    if (sEnetReady) {
        enet_deinitialize();
        sEnetReady = 0;
    }
    sActive = 0;
}
