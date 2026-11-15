#ifndef PORT_ONLINE_SAVE_H
#define PORT_ONLINE_SAVE_H

// Online autosave. During an online game the host (only the host) writes a checkpoint at the start of every
// player's turn to <user dir>/online/<started>_<board>.pbsave, so an interrupted party can be continued later.
// If the host drops, the server makes someone else host and their game saves from then on.
//
// A checkpoint is the board state the game's own party save keeps (GWSystem and the four GWPlayer, in the
// GameCube byte order SLSaveBoard writes), with GWSystem.player_curr set to the player whose turn starts. The file
// keeps two: the latest turn start, and the latest round start (player 1's turn, where the game's own Continue
// resumes). It also records the room: board, turn count, CPU level, input delay, who played each port and as
// whom, and the build (a continue needs the same build).
//
// File layout (little-endian, written with netplay/protocol.h's writer):
//   char magic[8] "PBSAVE01", u32 version, str build, u64 created (unix s), u64 updated (unix s), u8 finished,
//   u8 board, u8 maxTurns, u8 cpuLevel, u8 inputDelay,
//   4 x (u8 character, u8 startedHuman, str name),
//   u8 hasLatest,     u16 size, size bytes   (latest turn start: GWSystem + GWPlayer[4])
//   u8 hasRoundStart, u16 size, size bytes   (latest round start)

#ifdef __cplusplus
extern "C" {
#endif

#define PB_ONLINE_SAVE_MAGIC "PBSAVE01"
#define PB_ONLINE_SAVE_VERSION 1

// Board main loop, just before player `player`'s turn runs (the same frame on every machine).
void partyboard_online_save_turn(int player);
// Board main loop, when the last turn's minigame is over and the party goes to its results.
void partyboard_online_save_party_over(void);

#ifdef __cplusplus
}
#endif

#endif
