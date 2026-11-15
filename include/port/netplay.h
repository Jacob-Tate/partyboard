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
//   --char <0-7>            Your character (Mario Luigi Peach Yoshi Wario DK Daisy Waluigi)
//   --port <1-4>            Your player number, if free
//   --continue <file>       With --create: continue an online save (<user dir>/online/*.pbsave)
//   --teams                 With --create: team battle, P1+P2 against P3+P4
//   --no-bonus-stars        With --create: no bonus stars at the end of the party
//
// Rejoining mid-game: --join the room's code with the same --name. Everyone's game restarts at the next save
// point (after the current round's minigame) and continues from there with you back in your seat. The
// restarted games get --reloaded, --wait-pid <old pid> and, on the host, --save-into <its autosave>.
//
// The host's --board, --turns, --cpu-level and --seed choose the game; the host's --chars sets all
// four characters. Without --port/--char, people get ports 1, 2, ... in join order and the first
// free characters; the remaining ports are CPU players with the characters nobody took. Each person
// plays with their own controller 1.

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
// Host only, while in a room: starts with the room's seating. seed 0 picks one at random. teams: team battle
// (P1+P2 against P3+P4); bonusStars: the end-of-party bonus stars (the game's default is on).
int partyboard_netplay_start_game(int board, int turns, int inputDelay, int cpuLevel, u32 seed, int teams,
    int bonusStars);
// Lobby: a member's / a seat's round trip to the server in ms (-1 if unknown or a CPU), and the input delay
// those pings suggest (-1 with fewer than two people in the room).
int partyboard_netplay_member_ping(int index);
int partyboard_netplay_slot_ping(int port);
int partyboard_netplay_suggested_delay(void);
// Port (0-3) and character (0-7) to ask for on entering a room; -1 = no preference.
void partyboard_netplay_set_preference(int port, int character);
// In a room: move to a free port and/or pick a character (-1 keeps the current one). The server
// may refuse (taken); partyboard_netplay_notice() then says why.
int partyboard_netplay_choose(int port, int character);
// Host only, in a room: sets every port's owner (client id or 0xFF = CPU) and character
// (0-7; 0xFF = CPU picks automatically).
int partyboard_netplay_set_layout(const u8 owner[4], const u8 chars[4]);
int partyboard_netplay_client_id(void); // -1 until welcomed
int partyboard_netplay_member_id(int index);
int partyboard_netplay_my_port(void);   // -1 when not in a room
int partyboard_netplay_slot_owner(int port); // client id, or 0xFF for a CPU
int partyboard_netplay_slot_char(int port);  // 0-7, -1 when not in a room
int partyboard_netplay_slot_auto(int port);  // 1 for a CPU whose character the server picks
const char *partyboard_netplay_slot_name(int port); // player name or "CPU"
const char *partyboard_netplay_notice(void); // last rejected request, "" if none
const char *partyboard_netplay_char_name(int character);
// During an online game: the name of the person who started on a port, "" for CPU ports.
const char *partyboard_netplay_port_name(int port);
// The player record (GWPlayer/GWPlayerCfg index) that plays seat `port`. The board orders the records by turn
// order, so record i is not seat i once a party has started.
int partyboard_netplay_player_for_port(int port);
// During an online game: the settings every client started with (NULL otherwise).
struct PbNetSettings;
const struct PbNetSettings *partyboard_netplay_game_settings(void);
// This build's id (the same executable on every machine has the same id).
const char *partyboard_netplay_build_id(void);
// Host: continue a saved online game (port/online_save.h) in the room, or NULL for a new game. Sent now if in a
// room as host, else on entering one. The save's board, turn count and seats then apply; people get their seats
// back by name.
struct PbOnlineSave;
int partyboard_netplay_set_continue(const struct PbOnlineSave *save);
const struct PbOnlineSave *partyboard_netplay_pending_continue(void);
// In a room that continues a saved game: who played `port` in the save ("" for a CPU seat).
int partyboard_netplay_room_continuing(void);
const char *partyboard_netplay_saved_name(int port);
// The room's phase (PB_ROOM_* in netplay/protocol.h): 0 lobby, 1 a game is running (we wait to rejoin it at its
// next save point), 2 the game restarts from a save point once everyone is back.
int partyboard_netplay_room_phase(void);
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
// The game reached a save point (resultDll, after a minigame); state is the board state a continue starts
// from. If someone is waiting to rejoin, sends it to the server and quits; the shutdown then restarts this
// program, which rejoins the room and continues from that state with everyone else.
void partyboard_netplay_save_point(const u8 *state, int size);
// Rejoining after a reload: a restarted game first waits for the old process (--wait-pid) to exit, so the two
// never share the log file or the window. Call first thing in main.
void partyboard_netplay_wait_for_parent(int argc, char *argv[]);
void partyboard_netplay_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif
