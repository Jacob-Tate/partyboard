#include "port/netplay.h"

#include "netplay/protocol.h"
#include "game/gamework_data.h"
#include "port/autotest.h"
#include "port/main.h"
#include "port/online_save.h"
#include "port/ui.h"

#include <enet/enet.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include "game/object.h" // after enet.h: it pulls in windows.h, which must not come before winsock2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef _WIN32
#include <signal.h>
#include <unistd.h>
#endif

#define NET_RING 1024           // received frames buffered ahead of the game
#define NET_WAIT_TIMEOUT_MS 20000 // give up if a frame's inputs haven't arrived in this long

typedef struct NetFrame {
    u32 frame;
    int valid;
    u8 humanMask;
    u8 flags; // PB_FRAME_*
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
static int sTeams = 0;      // --teams: team battle (P1+P2 against P3+P4)
static int sBonusStars = 1; // --no-bonus-stars turns them off
// Host: the save the next room continues (Online screen or --continue).
static PbOnlineSave sPendingContinue;
static int sHasPendingContinue = 0;

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
// Rejoin: the latest frame asked for a reload at the next save point (lockstep, so the same on every machine);
// sReloading once we reached it and quit to restart.
static int sReloadWanted = 0;
static int sReloading = 0;
static int sReloaded = 0; // --reloaded <why>: this process is such a restart
static char sReloadedWhy[16]; // "rejoin", "desync" or "reconnect"
static const char *sRestartWhy = "rejoin"; // why this process is about to restart
static void begin_restart(const char *why);
// The command line, to restart with (without the netplay options, which the restart sets itself).
static int sArgc = 0;
static char **sArgv = NULL;

static void parse_server(const char *server);

// ---- options ----

int partyboard_netplay_parse(int argc, char *argv[])
{
    int i;
    int ok = 1;
    const char *user = getenv("USERNAME");
    snprintf(sName, sizeof(sName), "%s", user && user[0] ? user : "Player");
    sArgc = argc;
    sArgv = argv;
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
        } else if (strcmp(arg, "--teams") == 0) {
            sTeams = 1;
        } else if (strcmp(arg, "--no-bonus-stars") == 0) {
            sBonusStars = 0;
        } else if (strcmp(arg, "--continue") == 0 && next) {
            // Host: continue the online save in this file (board and turn count come from it).
            if (!partyboard_online_save_load(next, &sPendingContinue) || !sPendingContinue.hasResume) {
                fprintf(stderr, "[netplay] --continue: can't read a continuable save from %s\n", next);
                ok = 0;
            } else {
                sHasPendingContinue = 1;
            }
            i++;
        } else if (strcmp(arg, "--save-into") == 0 && next) {
            // A restarted host keeps autosaving into the game's file (see partyboard_netplay_save_point).
            partyboard_online_save_continue_into(next);
            i++;
        } else if (strcmp(arg, "--reloaded") == 0 && next) {
            sReloaded = 1;
            snprintf(sReloadedWhy, sizeof(sReloadedWhy), "%s", next);
            i++;
        } else if (strcmp(arg, "--wait-pid") == 0 && next) {
            i++; // handled by partyboard_netplay_wait_for_parent
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
    ENetPacket *packet;
    if (sPeer == NULL) {
        return;
    }
    packet = enet_packet_create(w->data, w->pos, ENET_PACKET_FLAG_RELIABLE);
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
    const u8 flags = pbr_u8(r);
    NetFrame *slot = &sRing[frame % NET_RING];
    int port;
    if (r->error || frame < sFrame || frame >= sFrame + NET_RING) {
        return;
    }
    memset(slot, 0, sizeof(*slot));
    slot->humanMask = mask;
    slot->flags = flags;
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
static u16 sRoomPings[PB_NET_MAX_PLAYERS]; // each member's round trip to the server (ms)
// WAITING: the ports whose input a stalled frame lacks, and since when (enet time) we know
static u8 sWaitingMask = 0;
static u16 sWaitingMs = 0;
static int sWaitingShown = 0;
static char sRoomCode[PB_NET_ROOM_CODE_LEN + 1];
static u8 sSlotOwner[PB_NET_MAX_PLAYERS];
static u8 sSlotChar[PB_NET_MAX_PLAYERS];
static u8 sSlotAuto[PB_NET_MAX_PLAYERS];
// A continued game's room (ROOM_STATE): who played each seat in the save ("" = a CPU).
static int sRoomContinuing = 0;
static char sSavedNames[PB_NET_MAX_PLAYERS][PB_NET_MAX_NAME + 1];
static u8 sRoomPhase = PB_ROOM_LOBBY;
// GAME_START's saved board state (a continued game), 0 bytes for a new game.
static u8 sStartState[PB_NET_MAX_CONTINUE_STATE];
static u16 sStartStateSize = 0;
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
            sRoomPings[i] = pbr_u16(&r);
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
        sRoomContinuing = pbr_u8(&r) != 0 && !r.error;
        for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
            sSavedNames[i][0] = '\0';
            if (sRoomContinuing) {
                pbr_str(&r, sSavedNames[i], sizeof(sSavedNames[i]));
            }
        }
        if (sRoomContinuing) {
            printf("[netplay]   continuing a saved game\n");
        }
        sRoomPhase = pbr_u8(&r);
        if (r.error) {
            sRoomPhase = PB_ROOM_LOBBY;
        } else if (sRoomPhase == PB_ROOM_IN_GAME && !sActive) {
            printf("[netplay]   a game is running: you're back in at its next save point (after this round's minigame)\n");
        } else if (sRoomPhase == PB_ROOM_RELOADING) {
            printf("[netplay]   the game restarts from its save point once everyone is back\n");
        }
        fflush(stdout);
        sRoomStateTime = enet_time_get();
        break;
    }
    case PB_MSG_GAME_START:
        pbr_settings(&r, &sSettings);
        sStartStateSize = pbr_u16(&r);
        if (sStartStateSize > PB_NET_MAX_CONTINUE_STATE) {
            r.error = 1;
        } else {
            pbr_bytes(&r, sStartState, sStartStateSize);
        }
        if (!r.error) {
            sGameStarted = 1;
        } else {
            sStartStateSize = 0;
        }
        break;
    case PB_MSG_FRAME:
        handle_frame(&r);
        break;
    case PB_MSG_DESYNC:
        // A RESTART follows (or GAME_ENDED, if restarting didn't help).
        printf("[netplay] out of sync at frame %u\n", pbr_u32(&r));
        fflush(stdout);
        break;
    case PB_MSG_RESTART:
        if (sActive && !sEnded) {
            begin_restart("desync");
        }
        break;
    case PB_MSG_WAITING:
        sWaitingMask = pbr_u8(&r);
        sWaitingMs = pbr_u16(&r);
        break;
    case PB_MSG_REJOINING: {
        char name[PB_NET_MAX_NAME + 1];
        const u8 port = pbr_u8(&r);
        pbr_str(&r, name, sizeof(name));
        if (!r.error && sActive) {
            char msg[200];
            snprintf(msg, sizeof(msg),
                "%s is coming back as P%u. After this round's minigame everyone's game restarts (the window closes and "
                "reopens) and goes on from there.",
                name, port + 1u);
            printf("[netplay] %s\n", msg);
            fflush(stdout);
            ui_push_toast("", "Player rejoining", msg, 10000);
        }
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
        end_game(reason == PB_END_PLAYER_LEFT ? "a player left, game over"
                 : reason == PB_END_DESYNC
                     ? "Out of sync again after restarting. The host can continue from the last save: Play Online > "
                       "Saved Game."
                     : "game ended by the server");
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
    sRoomContinuing = 0;
    sRoomPhase = PB_ROOM_LOBBY;
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

// Name of the person on each port when the game started ("" for CPU ports), for in-game name tags.
static char sPortNames[PB_NET_MAX_PLAYERS][PB_NET_MAX_NAME + 1];

static void finalize_start(void)
{
    int i, m;
    int chars[PB_NET_MAX_PLAYERS];
    // Game settings from the server: same on every machine.
    sHumanMask = 0;
    sOwnedMask = 0;
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        sPortNames[i][0] = '\0';
        for (m = 0; m < sRoomCount; m++) {
            if (sSettings.portOwner[i] != PB_NET_PORT_CPU && sRoomIds[m] == sSettings.portOwner[i]) {
                snprintf(sPortNames[i], sizeof(sPortNames[i]), "%s", sRoomNames[m]);
            }
        }
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
    // A continued game boots the board from the saved state instead of a new party (same on every machine).
    partyboard_autotest_set_continue_state(sStartStateSize ? sStartState : NULL, sStartStateSize);
    partyboard_autotest_set_party_options(sSettings.teams, sSettings.bonusStars);
    memset(sRing, 0, sizeof(sRing));
    sReloadWanted = 0;
    if (sStartStateSize) {
        printf("[netplay] continuing a saved game (%u bytes of board state)\n", sStartStateSize);
    }
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
            if (sHasPendingContinue && partyboard_netplay_is_host()) {
                partyboard_netplay_set_continue(&sPendingContinue);
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

int partyboard_netplay_start_game(int board, int turns, int inputDelay, int cpuLevel, u32 seed, int teams,
    int bonusStars)
{
    PbNetSettings s;
    u8 buf[64 + PB_NET_MAX_CONTINUE_STATE];
    const int continuing = sRoomContinuing && sHasPendingContinue;
    PbNetWriter w;
    int i;
    if (sState != PB_LOBBY_IN_ROOM || !partyboard_netplay_is_host()) {
        return 0;
    }
    memset(&s, 0, sizeof(s));
    if (continuing) {
        // The save decides the board and turn count; the host's CPU level and delay still apply.
        board = sPendingContinue.board;
        turns = sPendingContinue.maxTurns;
        // The continued game keeps saving into the file it came from.
        partyboard_online_save_continue_into(sPendingContinue.path);
    }
    s.seed = seed ? seed : (u32)time(NULL);
    s.board = (u8)board;
    s.turns = (u8)turns;
    s.cpuLevel = (u8)cpuLevel;
    s.inputDelay = (u8)inputDelay;
    s.teams = teams ? 1 : 0;
    s.bonusStars = bonusStars ? 1 : 0;
    // Ports and characters come from the room's seating (the server fills them in).
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        s.chars[i] = sSlotChar[i];
        s.portOwner[i] = sSlotOwner[i];
    }
    sNotice[0] = '\0';
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_START_GAME);
    pbw_settings(&w, &s);
    if (continuing) {
        pbw_u16(&w, PB_ONLINE_SAVE_STATE_SIZE);
        pbw_bytes(&w, sPendingContinue.resumeState, PB_ONLINE_SAVE_STATE_SIZE);
    } else {
        pbw_u16(&w, 0);
    }
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    return 1;
}

int partyboard_netplay_set_continue(const PbOnlineSave *save)
{
    u8 buf[256];
    PbNetWriter w;
    int i;
    sHasPendingContinue = save != NULL;
    if (save != NULL && save != &sPendingContinue) {
        sPendingContinue = *save;
    }
    if (sState != PB_LOBBY_IN_ROOM || !partyboard_netplay_is_host()) {
        return 0; // sent on entering the room
    }
    sNotice[0] = '\0';
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_SET_CONTINUE);
    pbw_u8(&w, sHasPendingContinue ? 1 : 0);
    for (i = 0; sHasPendingContinue && i < PB_NET_MAX_PLAYERS; i++) {
        pbw_u8(&w, sPendingContinue.chars[i]);
        pbw_u8(&w, sPendingContinue.wasHuman[i]);
        pbw_str(&w, sPendingContinue.names[i], PB_NET_MAX_NAME);
    }
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    return 1;
}

const PbOnlineSave *partyboard_netplay_pending_continue(void)
{
    return sHasPendingContinue ? &sPendingContinue : NULL;
}

int partyboard_netplay_member_ping(int index)
{
    return (index >= 0 && index < sRoomCount) ? sRoomPings[index] : -1;
}

int partyboard_netplay_slot_ping(int port)
{
    int i;
    const int owner = partyboard_netplay_slot_owner(port);
    for (i = 0; owner != PB_NET_PORT_CPU && i < sRoomCount; i++) {
        if (sRoomIds[i] == owner) {
            return sRoomPings[i];
        }
    }
    return -1;
}

int partyboard_netplay_suggested_delay(void)
{
    // A frame's inputs travel sender -> server -> receiver: about half the slowest player's round trip plus half
    // the next slowest one's. In frames of 16.7 ms, rounded up, plus one for jitter.
    int first = 0, second = 0, i, frames;
    if (sRoomCount < 2) {
        return -1;
    }
    for (i = 0; i < sRoomCount; i++) {
        const int ping = sRoomPings[i];
        if (ping > first) {
            second = first;
            first = ping;
        } else if (ping > second) {
            second = ping;
        }
    }
    frames = (int)(((first + second) / 2.0 + 16.66) / 16.67) + 1;
    return frames < 2 ? 2 : (frames > 15 ? 15 : frames);
}

int partyboard_netplay_room_phase(void)
{
    return sRoomCount > 0 ? sRoomPhase : PB_ROOM_LOBBY;
}

int partyboard_netplay_room_continuing(void)
{
    return sRoomCount > 0 && sRoomContinuing;
}

const char *partyboard_netplay_saved_name(int port)
{
    return (partyboard_netplay_room_continuing() && port >= 0 && port < PB_NET_MAX_PLAYERS) ? sSavedNames[port] : "";
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

int partyboard_netplay_player_for_port(int port)
{
    int i;
    // The board orders players by turn order (board/start.c); pad_idx keeps the seat (lockstep pad) each plays.
    for (i = 0; i < PB_NET_MAX_PLAYERS; i++) {
        if (GWPlayerCfg[i].pad_idx == port) {
            return i;
        }
    }
    return port;
}

const char *partyboard_netplay_port_name(int port)
{
    return (sActive && port >= 0 && port < PB_NET_MAX_PLAYERS) ? sPortNames[port] : "";
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

const PbNetSettings *partyboard_netplay_game_settings(void)
{
    return sActive ? &sSettings : NULL;
}

const char *partyboard_netplay_build_id(void)
{
    return sBuildId;
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

// A restarted game has no window until the game starts again: this small one says what is going on.
static SDL_Window *sWaitWindow = NULL;
static SDL_Renderer *sWaitRenderer = NULL;

static void wait_window_close(void)
{
    if (sWaitRenderer) {
        SDL_DestroyRenderer(sWaitRenderer);
        sWaitRenderer = NULL;
    }
    if (sWaitWindow) {
        SDL_DestroyWindow(sWaitWindow);
        sWaitWindow = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO); // the game initializes video its own way
    }
}

// Draws the lines (wrapped). Returns 0 once the player closed the window.
static int wait_window_update(const char *const *lines, int count)
{
    const float scale = 2.0f;
    const int width = 760, cols = (int)(width / (8 * scale)) - 2;
    SDL_Event event;
    int i;
    float y = 10;
    if (!sWaitWindow) {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
            return 1;
        }
        sWaitWindow = SDL_CreateWindow("Party Board", width, 230, 0);
        sWaitRenderer = sWaitWindow ? SDL_CreateRenderer(sWaitWindow, NULL) : NULL;
        if (!sWaitRenderer) {
            wait_window_close();
            return 1;
        }
    }
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            return 0;
        }
    }
    SDL_SetRenderScale(sWaitRenderer, 1.0f, 1.0f);
    SDL_SetRenderDrawColor(sWaitRenderer, 24, 28, 48, 255);
    SDL_RenderClear(sWaitRenderer);
    SDL_SetRenderScale(sWaitRenderer, scale, scale);
    for (i = 0; i < count; i++) {
        const char *text = lines[i];
        SDL_SetRenderDrawColor(sWaitRenderer, i == 0 ? 255 : 200, i == 0 ? 220 : 205, i == 0 ? 120 : 220, 255);
        // Word wrap at `cols` characters.
        while (*text) {
            char row[128];
            int len = (int)strlen(text), cut = len;
            if (len > cols) {
                for (cut = cols; cut > 0 && text[cut] != ' '; cut--) {}
                if (cut == 0) {
                    cut = cols;
                }
            }
            snprintf(row, sizeof(row), "%.*s", cut, text);
            SDL_RenderDebugText(sWaitRenderer, 8, y / scale + 4, row);
            y += 22;
            text += cut;
            while (*text == ' ') {
                text++;
            }
        }
        y += 12;
    }
    SDL_RenderPresent(sWaitRenderer);
    return 1;
}

// The restarted game's waiting window: why we restarted and who is back so far.
static int show_restart_wait(const char *retrying)
{
    const char *title = strcmp(sReloadedWhy, "desync") == 0 ? "The games went out of sync."
                        : strcmp(sReloadedWhy, "reconnect") == 0 ? "Lost the connection to the server."
                                                                  : "A player is rejoining.";
    char status[300];
    const char *lines[3];
    if (retrying) {
        snprintf(status, sizeof(status), "Getting back into room %s... (%s)", sJoinCode, retrying);
    } else if (sRoomCount > 0) {
        int i;
        snprintf(status, sizeof(status), "Back in room %s:", sRoomCode);
        for (i = 0; i < sRoomCount; i++) {
            snprintf(status + strlen(status), sizeof(status) - strlen(status), "%s %s", i ? "," : "", sRoomNames[i]);
        }
        snprintf(status + strlen(status), sizeof(status) - strlen(status),
            sRoomPhase == PB_ROOM_IN_GAME ? ". You're back in after this round's minigame."
                                          : ". The game goes on once everyone is back.");
    } else {
        snprintf(status, sizeof(status), "Getting back into room %s...", sJoinCode);
    }
    lines[0] = title;
    lines[1] = status;
    lines[2] = "Close this window to give up.";
    return wait_window_update(lines, 3);
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
    const Uint64 startTicks = SDL_GetTicks();
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
        if (sReloaded && !show_restart_wait(NULL)) {
            printf("[netplay] gave up getting back into the game\n");
            wait_window_close();
            return 0;
        }
        if (sState == PB_LOBBY_FAILED) {
            if (sReloaded && SDL_GetTicks() - startTicks < 60000) {
                // The server may not have noticed our old connection drop yet, or the network is still down:
                // keep trying for a minute.
                char why[300];
                const Uint64 until = SDL_GetTicks() + 2000;
                snprintf(why, sizeof(why), "%s", sError);
                printf("[netplay] couldn't get back in yet (%s); retrying\n", why);
                fflush(stdout);
                while (SDL_GetTicks() < until) {
                    if (!show_restart_wait(why)) {
                        wait_window_close();
                        return 0;
                    }
                    SDL_Delay(50);
                }
                snprintf(code, sizeof(code), "%s", sJoinCode);
                partyboard_netplay_begin(server, name, sCreate, code);
                continue;
            }
            if (sReloaded) {
                char msg[400];
                wait_window_close();
                snprintf(msg, sizeof(msg), "Couldn't get back into the online game after it restarted:\n%s", sError);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Party Board", msg, NULL);
            }
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
            partyboard_netplay_start_game(t->board, t->turns, sDelay, t->cpuLevel, t->seedSet ? t->seed : 0, sTeams,
                sBonusStars);
            startSent = 1;
        }
    }
    wait_window_close();
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

// While a frame waits on other players: keep the window alive and say who we wait for in its title (the game
// can't draw while it waits). waitedMs 0 restores the title.
static void show_waiting(int waitedMs)
{
    static char original[256];
    SDL_Window **windows;
    int count = 0;
    char title[256];
    int port;
    SDL_PumpEvents();
    windows = SDL_GetWindows(&count);
    if (windows == NULL || count < 1) {
        SDL_free(windows);
        return;
    }
    if (waitedMs == 0) {
        if (sWaitingShown && original[0]) {
            SDL_SetWindowTitle(windows[0], original);
        }
        if (sWaitingShown) {
            printf("[netplay] going again at frame %u\n", sFrame);
            fflush(stdout);
        }
        sWaitingShown = 0;
        sWaitingMask = 0;
        SDL_free(windows);
        return;
    }
    if (waitedMs < 500) {
        SDL_free(windows);
        return;
    }
    if (!sWaitingShown) {
        snprintf(original, sizeof(original), "%s", SDL_GetWindowTitle(windows[0]));
    }
    snprintf(title, sizeof(title), "Waiting for");
    for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
        if (sWaitingMask & (1 << port)) {
            const char *name = sPortNames[port][0] ? sPortNames[port] : "a player";
            snprintf(title + strlen(title), sizeof(title) - strlen(title), " %s (P%d)", name, port + 1);
        }
    }
    if (sWaitingMask == 0) {
        snprintf(title + strlen(title), sizeof(title) - strlen(title), " the server");
    }
    snprintf(title + strlen(title), sizeof(title) - strlen(title), " - %.1f s", waitedMs / 1000.0);
    SDL_SetWindowTitle(windows[0], title);
    if (!sWaitingShown || waitedMs % 2000 == 0) {
        printf("[netplay] frame %u: %s\n", sFrame, title);
        fflush(stdout);
    }
    sWaitingShown = 1;
    SDL_free(windows);
}

u32 partyboard_netplay_pad_read(PADStatus *status)
{
    PADStatus local[PB_NET_MAX_PLAYERS];
    NetFrame *slot;
    int waited = 0;
    int port;

    if (sReloading) {
        // Quitting to restart: the last frames before the window closes need no one else's input.
        for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            memset(&status[port], 0, sizeof(PADStatus));
            status[port].err = PAD_ERR_NO_CONTROLLER;
        }
        PartyBoard_IsRunning = false;
        return 0;
    }
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
    {
        // Test aid: PB_NETPLAY_TEST_TAP=<n> taps A for 5 frames every n frames instead of the controller, so
        // unattended online tests get past messages and prompts (off unless set).
        static int tapEvery = -1;
        if (tapEvery < 0) {
            const char *env = getenv("PB_NETPLAY_TEST_TAP");
            tapEvery = env ? atoi(env) : 0;
        }
        if (tapEvery > 0) {
            memset(local, 0, sizeof(PADStatus) * PB_NET_MAX_PLAYERS);
            if ((int)(sFrame % (u32)tapEvery) < 5) {
                local[0].button = PAD_BUTTON_A;
                local[0].analogA = 0xFF;
            } else if (omcurovl == DLL_instdll && (int)(sFrame % (u32)tapEvery) >= tapEvery / 2 &&
                       (int)(sFrame % (u32)tapEvery) < tapEvery / 2 + 5) {
                local[0].button = PAD_BUTTON_START; // a minigame's instructions start on START
            }
        }
    }
    send_input(sFrame + sSettings.inputDelay, local);
    {
        // Test aids (off unless set; not in a restarted game): PB_NETPLAY_TEST_DESYNC=<frame> changes this
        // game's state at that frame, PB_NETPLAY_TEST_DROP=<frame> drops the connection without a word.
        static int desyncAt = -1, dropAt = -1;
        if (desyncAt < 0) {
            const char *env = getenv("PB_NETPLAY_TEST_DESYNC");
            desyncAt = env && !sReloaded ? atoi(env) : 0;
            env = getenv("PB_NETPLAY_TEST_DROP");
            dropAt = env && !sReloaded ? atoi(env) : 0;
        }
        if (desyncAt > 0 && sFrame == (u32)desyncAt) {
            printf("[netplay] test: desyncing at frame %u\n", sFrame);
            GWPlayer[0].coins++;
        }
        if (dropAt > 0 && sFrame == (u32)dropAt) {
            printf("[netplay] test: dropping the connection at frame %u\n", sFrame);
            enet_peer_reset(sPeer);
            sPeer = NULL;
            begin_restart("reconnect");
            return partyboard_netplay_pad_read(status);
        }
    }
    {
        // A minigame's instructions wait for everyone: get the attention of a player who looked away.
        static s16 lastOvl = -1;
        if (omcurovl != lastOvl && omcurovl == DLL_instdll && sOwnedMask) {
            partyboard_netplay_attention();
        }
        lastOvl = omcurovl;
    }

    slot = &sRing[sFrame % NET_RING];
    while (!(slot->valid && slot->frame == sFrame)) {
        if (waited > 0 && waited % 100 == 0) {
            show_waiting(waited);
        }
        if (!pump(1)) {
            if (sRoomCode[0] && sServerHost) {
                begin_restart("reconnect"); // restart and get back into the room
            } else {
                end_game("lost connection to the server");
            }
            return partyboard_netplay_pad_read(status);
        }
        if (sEnded || sReloading) {
            return partyboard_netplay_pad_read(status);
        }
        if (++waited > NET_WAIT_TIMEOUT_MS) {
            end_game("timed out waiting for the other players");
            return partyboard_netplay_pad_read(status);
        }
    }
    if (sWaitingShown) {
        show_waiting(0);
    }
    if (slot->humanMask != sHumanMask) {
        // A player dropped: every client reaches this frame's bundle with the same mask, so the
        // CPU takes over on the same frame everywhere.
        for (port = 0; port < PB_NET_MAX_PLAYERS; port++) {
            if ((sHumanMask & (1 << port)) && !(slot->humanMask & (1 << port))) {
                const int player = partyboard_netplay_player_for_port(port);
                GWPlayerCfg[player].iscom = 1;
                GWPlayerCfg[player].diff = sSettings.cpuLevel;
                GWPlayer[player].com = 1;
                GWPlayer[player].diff = sSettings.cpuLevel;
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
    if (((slot->flags & PB_FRAME_RELOAD) != 0) != sReloadWanted) {
        sReloadWanted = (slot->flags & PB_FRAME_RELOAD) != 0;
        printf("[netplay] frame %u: %s\n", sFrame,
            sReloadWanted ? "someone is rejoining; restarting at the next save point" : "nobody is waiting to rejoin any more");
        fflush(stdout);
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
    if (!sActive || sEnded || sReloading) {
        return;
    }
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_CHECKSUM);
    pbw_u32(&w, frame);
    pbw_u32(&w, hash);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
}

// ---- rejoin: restarting at a save point ----

static char sRelaunchCode[PB_NET_ROOM_CODE_LEN + 1];
static char sRelaunchSave[600];

// Quit now and restart into the same room (see relaunch).
static void begin_restart(const char *why)
{
    if (sReloading) {
        return;
    }
    snprintf(sRelaunchCode, sizeof(sRelaunchCode), "%s", sRoomCode);
    // The host's restarted game keeps writing the same autosave.
    snprintf(sRelaunchSave, sizeof(sRelaunchSave), "%s", partyboard_online_save_host_path());
    sRestartWhy = why;
    printf("[netplay] frame %u: restarting (%s) to get back into room %s\n", sFrame, why, sRelaunchCode);
    fflush(stdout);
    sReloading = 1;
    PartyBoard_IsRunning = false;
}

void partyboard_netplay_save_point(const u8 *state, int size)
{
    u8 buf[16 + PB_NET_MAX_CONTINUE_STATE];
    PbNetWriter w;
    if (!sActive || sEnded || sReloading || size <= 0 || size > PB_NET_MAX_CONTINUE_STATE) {
        return;
    }
    // Every save point goes to the server: once all players' states agree it is where a desync restarts from.
    pbw_init(&w, buf, sizeof(buf));
    pbw_u8(&w, PB_MSG_SAVE_POINT);
    pbw_u32(&w, sFrame);
    pbw_u8(&w, sReloadWanted ? 1 : 0);
    pbw_u16(&w, (u16)size);
    pbw_bytes(&w, state, (size_t)size);
    send_writer(PB_NET_CHANNEL_CONTROL, &w);
    if (sReloadWanted) {
        begin_restart("rejoin"); // someone waits to rejoin: everyone restarts from here
    }
}

void partyboard_netplay_attention(void)
{
    SDL_Window **windows;
    int count = 0;
    if (!sActive || sEnded) {
        return;
    }
    windows = SDL_GetWindows(&count);
    if (windows != NULL && count > 0 && !(SDL_GetWindowFlags(windows[0]) & SDL_WINDOW_INPUT_FOCUS)) {
        SDL_FlashWindow(windows[0], SDL_FLASH_UNTIL_FOCUSED);
    }
    SDL_free(windows);
}

void partyboard_netplay_turn_starts(int player)
{
    if (player >= 0 && player < PB_NET_MAX_PLAYERS && !GWPlayer[player].com &&
        (sOwnedMask & (1 << (GWPlayer[player].port & 3)))) {
        partyboard_netplay_attention();
    }
}

#ifdef _WIN32
// Appends one argument to a Windows command line, quoted the way CommandLineToArgvW reads it back.
static void append_arg(char *cmd, size_t cap, const char *arg)
{
    size_t len = strlen(cmd);
    const char *p;
#define PUT(ch)                                                                                                        \
    do {                                                                                                               \
        if (len + 1 < cap) {                                                                                           \
            cmd[len++] = (ch);                                                                                         \
            cmd[len] = '\0';                                                                                           \
        }                                                                                                              \
    } while (0)
    if (len > 0) {
        PUT(' ');
    }
    PUT('"');
    for (p = arg;; p++) {
        int slashes = 0;
        int k;
        while (*p == '\\') {
            slashes++;
            p++;
        }
        if (*p == '\0') {
            for (k = 0; k < slashes * 2; k++) {
                PUT('\\');
            }
            break;
        }
        if (*p == '"') {
            for (k = 0; k < slashes * 2 + 1; k++) {
                PUT('\\');
            }
        } else {
            for (k = 0; k < slashes; k++) {
                PUT('\\');
            }
        }
        PUT(*p);
    }
    PUT('"');
#undef PUT
}
#endif

// Starts this program again to rejoin the room: the original command line without its netplay options, then
// --server/--join/--name for the same room. The new process waits for this one to exit (--wait-pid).
static void relaunch(void)
{
    static const char *const withValue[] = { "--server", "--join", "--players", "--delay", "--name", "--char", "--port",
        "--continue", "--save-into", "--wait-pid", "--reloaded" };
    static const char *const flags[] = { "--create", "--teams", "--no-bonus-stars" };
    const char *args[160];
    char server[300], pid[32], checksumLog[1024];
    int n = 0;
    int i;
    size_t k;
    args[n++] = (sArgv && sArgc > 0) ? sArgv[0] : "partyboard";
    for (i = 1; i < sArgc && n < 140; i++) {
        const char *arg = sArgv[i];
        int skip = 0;
        for (k = 0; k < sizeof(withValue) / sizeof(withValue[0]); k++) {
            if (strcmp(arg, withValue[k]) == 0) {
                skip = 2;
            }
        }
        for (k = 0; k < sizeof(flags) / sizeof(flags[0]); k++) {
            if (strcmp(arg, flags[k]) == 0) {
                skip = 1;
            }
        }
        if (skip) {
            i += skip - 1;
            continue;
        }
        if (strcmp(arg, "--checksum-log") == 0 && i + 1 < sArgc) {
            // Tests compare logs per process: the restarted game writes <log>.reload.
            snprintf(checksumLog, sizeof(checksumLog), "%s.reload", sArgv[i + 1]);
            args[n++] = arg;
            args[n++] = checksumLog;
            i++;
            continue;
        }
        args[n++] = arg;
    }
    snprintf(server, sizeof(server), "%s:%u", sServerHost ? sServerHost : "", sServerPort);
#ifdef _WIN32
    snprintf(pid, sizeof(pid), "%lu", (unsigned long)GetCurrentProcessId());
#else
    snprintf(pid, sizeof(pid), "%ld", (long)getpid());
#endif
    args[n++] = "--wait-pid";
    args[n++] = pid;
    args[n++] = "--reloaded";
    args[n++] = sRestartWhy;
    args[n++] = "--server";
    args[n++] = server;
    args[n++] = "--join";
    args[n++] = sRelaunchCode;
    args[n++] = "--name";
    args[n++] = sName;
    if (sRelaunchSave[0]) {
        args[n++] = "--save-into";
        args[n++] = sRelaunchSave;
    }
    args[n] = NULL;
#ifdef _WIN32
    {
        static char cmd[16384];
        static wchar_t wcmd[16384];
        wchar_t exe[MAX_PATH * 2];
        STARTUPINFOW si;
        PROCESS_INFORMATION pi;
        cmd[0] = '\0';
        for (i = 0; i < n; i++) {
            append_arg(cmd, sizeof(cmd), args[i]);
        }
        if (GetModuleFileNameW(NULL, exe, MAX_PATH * 2) == 0 ||
            MultiByteToWideChar(CP_UTF8, 0, cmd, -1, wcmd, (int)(sizeof(wcmd) / sizeof(wcmd[0]))) == 0) {
            printf("[netplay] can't restart: %lu\n", (unsigned long)GetLastError());
            return;
        }
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        if (!CreateProcessW(exe, wcmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            printf("[netplay] can't restart: error %lu\n", (unsigned long)GetLastError());
            return;
        }
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
#else
    if (fork() == 0) {
        execvp(args[0], (char *const *)args);
        _exit(127);
    }
#endif
    printf("[netplay] restarted to rejoin room %s\n", sRelaunchCode);
    fflush(stdout);
}

void partyboard_netplay_wait_for_parent(int argc, char *argv[])
{
    int i;
    for (i = 1; i + 1 < argc; i++) {
        if (strcmp(argv[i], "--wait-pid") == 0) {
            const unsigned long pid = strtoul(argv[i + 1], NULL, 10);
#ifdef _WIN32
            HANDLE process = OpenProcess(SYNCHRONIZE, FALSE, (DWORD)pid);
            if (process != NULL) {
                WaitForSingleObject(process, 20000);
                CloseHandle(process);
            }
#else
            int tries;
            for (tries = 0; tries < 400 && kill((pid_t)pid, 0) == 0; tries++) {
                usleep(50000);
            }
#endif
        }
    }
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
    if (sReloading) {
        sReloading = 0;
        relaunch();
    }
}
