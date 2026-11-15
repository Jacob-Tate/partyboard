#ifndef PORT_NETPLAY_H
#define PORT_NETPLAY_H

// Online play through the relay server (server/). Lockstep: every frame each player sends their
// controller state, and the game only advances once the server has delivered every human
// player's input for that frame.
//
//   --server <host[:port]>  Relay server (default port 7845)
//   --create                Create a room; prints the room code, starts when --players have joined
//   --join <CODE>           Join a room by its 4-letter code
//   --players <2-4>         With --create: how many people to wait for (default 2)
//   --name <name>           Name shown to the other players (default: your Windows user name)
//   --delay <frames>        With --create: input delay in frames (default 4)
//
// The host's --board, --turns, --chars, --cpu-level and --seed choose the game. People join in
// order and get ports 1, 2, ...; the remaining ports are CPU players. Each person plays with their
// own controller 1 (and controller 2 if they own a second port).

#include <dolphin/pad.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum PbNetLobbyState {
    PB_LOBBY_IDLE,       // not connected
    PB_LOBBY_CONNECTING, // waiting for the server to answer
    PB_LOBBY_HELLO,      // connected, waiting to be welcomed
    PB_LOBBY_JOINING,    // asked to create/join a room
    PB_LOBBY_IN_ROOM,    // in a room, waiting for the host to start
    PB_LOBBY_STARTED,    // game settings received; the game should boot now
    PB_LOBBY_FAILED,     // see partyboard_netplay_error()
} PbNetLobbyState;

// ---- Lobby (non-blocking; the Online screen calls update() every frame) ----
// Starts connecting and creating (create=1) or joining a room. Returns 0 on immediate failure.
int partyboard_netplay_begin(const char *server, const char *name, int create, const char *joinCode);
void partyboard_netplay_update(void);
// Host only, while in a room: everyone in the room gets ports in join order; the rest are CPUs.
// seed 0 picks one at random.
int partyboard_netplay_start_game(int board, int turns, int inputDelay, int cpuLevel, const int chars[4], u32 seed);
// Leaves the room and disconnects (not once the game has started).
void partyboard_netplay_leave(void);
PbNetLobbyState partyboard_netplay_state(void);
const char *partyboard_netplay_error(void);
const char *partyboard_netplay_room_code(void);
int partyboard_netplay_is_host(void);
int partyboard_netplay_member_count(void);
const char *partyboard_netplay_member_name(int index);

// Parses netplay options. Returns 0 on a malformed option.
int partyboard_netplay_parse(int argc, char *argv[]);
// True once --server was given.
int partyboard_netplay_requested(void);
// Connects, runs the console lobby, and blocks until the game starts. Returns 0 on failure.
int partyboard_netplay_lobby(void);
// True while a networked game is running.
int partyboard_netplay_active(void);
// Replaces PADRead() during a networked game: sends local input, waits for this frame's inputs.
u32 partyboard_netplay_pad_read(PADStatus *status);
// Reports the game-state hash for a frame so the server can detect desyncs.
void partyboard_netplay_checksum(u32 frame, u32 hash);
void partyboard_netplay_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif
