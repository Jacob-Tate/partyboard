#ifndef PORT_AUTOTEST_H
#define PORT_AUTOTEST_H

// Automated test / quick-start mode, driven by command-line options.
//
//   --iso <path>          Disc image to boot (skips the prelaunch UI)
//   --quickstart          Boot straight into a party-mode board with 4 CPU players
//   --board <0-5>         Board for --quickstart (default 0 = Toad's Midway Madness)
//   --turns <n>           Turn count for --quickstart (default 10)
//   --chars <a,b,c,d>     Character ids 0-7 for players 1-4 (default 0,1,2,3)
//   --cpu-level <0-3>     CPU difficulty (default 1)
//   --seed <n>            Fix all game RNG seeds so runs are repeatable
//   --fast                Disable the frame limiter and vsync
//   --loop                After a game ends, start another on the next board (default: quit)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PartyBoardAutotest {
    int quickstart;
    int board;
    int turns;
    int chars[4];
    int cpuLevel;
    int seedSet;
    unsigned int seed;
    int fast;
    int loop;
    int gamesFinished;
    const char *isoPath;
} PartyBoardAutotest;

// Parses argv; unknown arguments are ignored. Returns 0 on a malformed option.
int partyboard_autotest_parse(int argc, char *argv[]);
const PartyBoardAutotest *partyboard_autotest_get(void);

// Exported to RELs (see dol.def).
int partyboard_autotest_quickstart(void);
void partyboard_autotest_apply_seed(void);
void partyboard_autotest_setup_party(void);
// Called when a board returns to boot. Returns 1 to start another game, 0 after requesting exit.
int partyboard_autotest_next_game(void);

#ifdef __cplusplus
}
#endif

#endif
