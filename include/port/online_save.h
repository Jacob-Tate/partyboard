#ifndef PORT_ONLINE_SAVE_H
#define PORT_ONLINE_SAVE_H

// Online autosave and continue.
//
// During an online game the host (only the host) keeps <user dir>/online/<started>_<board>.pbsave up to date. If
// the host drops, the server makes someone else host and their game saves from then on. A continued game keeps
// saving into the file it came from.
//
// The file holds two checkpoints of the board state the game's own party save keeps (GWSystem and the four
// GWPlayer, in the GameCube byte order SLSaveBoard writes):
// - resume point: where the game's own party save is taken (the results after each minigame). The game's
//   Continue is built to start from exactly this state, so a continue starts here.
// - latest turn start: the start of the latest player's turn (player_curr = that player). Kept for a finer
//   resume later; not used to continue yet.
// It also records the room (board, turn count, CPU level, input delay, each port's character and who played it)
// and the build: a continue needs the same build. It is marked finished when the party reaches its results.
//
// File layout (little-endian, written with netplay/protocol.h's writer):
//   char magic[8] "PBSAVE02", u32 version, str build, u32 created lo/hi, u32 updated lo/hi (unix s), u8 finished,
//   u8 board, u8 maxTurns, u8 cpuLevel, u8 inputDelay,
//   4 x (u8 character, u8 wasHuman, str name),
//   u8 hasResume, u16 size, size bytes   (resume point)
//   u8 hasLatest, u16 size, size bytes   (latest turn start)

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PB_ONLINE_SAVE_MAGIC "PBSAVE02"
#define PB_ONLINE_SAVE_VERSION 2
#define PB_ONLINE_SAVE_STATE_SIZE 412 // sizeof(SystemState) + 4 * sizeof(PlayerState)

typedef struct PbOnlineSave {
    char path[512];      // UTF-8
    char build[48];
    u64 created;         // unix seconds
    u64 updated;
    u8 finished;
    u8 board;
    u8 maxTurns;
    u8 cpuLevel;
    u8 inputDelay;
    u8 chars[4];
    u8 wasHuman[4];
    char names[4][32];
    u8 hasResume;
    u8 resumeTurn;       // the turn the resume point starts (GWSystem.turn)
    u8 resumeState[PB_ONLINE_SAVE_STATE_SIZE];
    u8 hasLatest;
    u8 latestTurn;
    s8 latestPlayer;
} PbOnlineSave;

// ---- saving (board and result screens; every machine calls them, only the host writes) ----
// Board main loop, just before player `player`'s turn runs.
void partyboard_online_save_turn(int player);
// resultDll, where the game's own party save (SLSaveBoard) is taken after a minigame.
void partyboard_online_save_resume_point(void);
// Board main loop, when the last turn's minigame is over and the party goes to its results.
void partyboard_online_save_party_over(void);

// ---- continuing ----
// Reads a save file. Returns 1 on success.
int partyboard_online_save_load(const char *path, PbOnlineSave *out);
// The saves in <user dir>/online that can be continued (not finished, with a resume point; from any build),
// newest first. Returns how many were written to `out` (at most `max`).
int partyboard_online_save_list(PbOnlineSave *out, int max);
// The next online game this machine hosts is a continue of `path`: it keeps saving into that file.
void partyboard_online_save_continue_into(const char *path);
// The file the game now running saves into, if this machine is the host and has saved; else "".
const char *partyboard_online_save_host_path(void);

#ifdef __cplusplus
}
#endif

#endif
