#ifndef PORT_AUTOTEST_H
#define PORT_AUTOTEST_H

// Automated test / quick-start mode, driven by command-line options.
//
//   --iso <path>          Disc image to boot (skips the prelaunch UI)
//   --config-dir <path>   Use this folder for settings and memory card (handled in portmain.cpp)
//   --quickstart          Boot straight into a party-mode board with 4 CPU players
//   --board <0-5>         Board for --quickstart (default 0 = Toad's Midway Madness)
//   --turns <n>           Turn count for --quickstart (default 10)
//   --chars <a,b,c,d>     Character ids 0-7 for players 1-4 (default 0,1,2,3)
//   --cpu-level <0-3>     CPU difficulty (default 1)
//   --humans <0-4>        First N players are human, on controller ports 1-N (default 0)
//   --record / --replay   Input recording, see port/inputsync.h
//   --seed <n>            Fix all game RNG seeds so runs are repeatable
//   --fast                Disable the frame limiter and vsync
//   --loop                After a game ends, start another on the next board (default: quit)
//   --checksum-log <path> Write one line per frame: frame, overlay, RNG seeds, game-state hash
//   --max-frames <n>      Quit after n frames
//   --dump-frame <n>      Hex-dump the hashed game state into the checksum log at frame n

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PartyBoardAutotest {
    int quickstart;
    int board;
    int turns;
    int chars[4];
    int cpuLevel;
    int humans;
    int humanMask; // bit per player port that a human controls (from --humans or netplay)
    int seedSet;
    unsigned int seed;
    int fast;
    int loop;
    int gamesFinished;
    unsigned int maxFrames;
    unsigned int dumpFrame;
    const char *isoPath;
    const char *checksumLogPath;
    int charsSet; // --chars was given
    int menu; // --menu: always open the Party Board menu (the restart after an online party)
    int minigame; // --minigame <401-4xx>: straight into that minigame instead of a board (0: off)
} PartyBoardAutotest;

// Parses argv; unknown arguments are ignored. Returns 0 on a malformed option.
int partyboard_autotest_parse(int argc, char *argv[]);
const PartyBoardAutotest *partyboard_autotest_get(void);

// Exported to RELs (see dol.def).
int partyboard_autotest_quickstart(void);
void partyboard_autotest_apply_seed(void);
// Whether --seed was given, and a seed derived from it and the current frame number.
// Use these to replace clock-based RNG seeding so runs stay repeatable.
int partyboard_autotest_seeded(void);
unsigned int partyboard_autotest_frame_seed(void);
// Gives up the CPU briefly while spin-waiting on a worker thread.
void partyboard_autotest_yield(void);
void partyboard_autotest_setup_party(void);
// --minigame: sets up the players and teams for that minigame (as Mini-Game mode does) and returns 1;
// returns 0 without it (or when it names no minigame), and the caller starts a board instead.
int partyboard_autotest_setup_minigame(void);
// Applies netplay game settings; humanMask has a bit per human-controlled port.
// Online games: team battle (P1+P2 against P3+P4) and the end-of-party bonus stars, for the next new party.
void partyboard_autotest_set_party_options(int teams, int bonusStars);
// A continued online game: the saved board state the next game starts from (NULL/0: a new party).
void partyboard_autotest_set_continue_state(const unsigned char *state, int size);
void partyboard_autotest_configure_netplay(unsigned int seed, int board, int turns, const int chars[4], int cpuLevel,
    int humanMask);
// Applies the game settings stored in an input recording (implies --quickstart and --seed).
void partyboard_autotest_configure_replay(unsigned int seed, int board, int turns, const int chars[4], int cpuLevel,
    int humans);
// Called when a board returns to boot. Returns 1 to start another game, 0 after requesting exit.
int partyboard_autotest_next_game(void);

// Called once per game frame from the main loop, after GlobalCounter is incremented.
void partyboard_autotest_frame_end(void);
// Flushes and closes the checksum log.
void partyboard_autotest_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif
