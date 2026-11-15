#include "port/autotest.h"

#include "game/board/main.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "port/main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern s32 rnd_seed;
void frand_seed_set(u32 seed);

static PartyBoardAutotest sAutotest = {
    0,              // quickstart
    0,              // board
    10,             // turns
    { 0, 1, 2, 3 }, // chars
    1,              // cpuLevel
    0,              // seedSet
    0,              // seed
    0,              // fast
    0,              // loop
    0,              // gamesFinished
    NULL,           // isoPath
};

static int parse_int(const char *text, int lo, int hi, int *out)
{
    char *end;
    long value = strtol(text, &end, 0);
    if (end == text || *end != '\0' || value < lo || value > hi) {
        return 0;
    }
    *out = (int)value;
    return 1;
}

static int parse_chars(const char *text, int out[4])
{
    int i;
    for (i = 0; i < 4; i++) {
        char *end;
        long value = strtol(text, &end, 10);
        if (end == text || value < 0 || value > 7) {
            return 0;
        }
        out[i] = (int)value;
        if (i < 3) {
            if (*end != ',') {
                return 0;
            }
            text = end + 1;
        } else if (*end != '\0') {
            return 0;
        }
    }
    return 1;
}

int partyboard_autotest_parse(int argc, char *argv[])
{
    int i;
    int ok = 1;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        const char *next = (i + 1 < argc) ? argv[i + 1] : NULL;
        int value;

        if (strcmp(arg, "--quickstart") == 0) {
            sAutotest.quickstart = 1;
        } else if (strcmp(arg, "--fast") == 0) {
            sAutotest.fast = 1;
        } else if (strcmp(arg, "--loop") == 0) {
            sAutotest.loop = 1;
        } else if (strcmp(arg, "--iso") == 0 && next) {
            sAutotest.isoPath = next;
            i++;
        } else if (strcmp(arg, "--board") == 0 && next) {
            if (parse_int(next, 0, 5, &value)) {
                sAutotest.board = value;
            } else {
                fprintf(stderr, "[autotest] --board expects 0-5, got '%s'\n", next);
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--turns") == 0 && next) {
            if (parse_int(next, 1, 99, &value)) {
                sAutotest.turns = value;
            } else {
                fprintf(stderr, "[autotest] --turns expects 1-99, got '%s'\n", next);
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--cpu-level") == 0 && next) {
            if (parse_int(next, 0, 3, &value)) {
                sAutotest.cpuLevel = value;
            } else {
                fprintf(stderr, "[autotest] --cpu-level expects 0-3, got '%s'\n", next);
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--chars") == 0 && next) {
            if (!parse_chars(next, sAutotest.chars)) {
                fprintf(stderr, "[autotest] --chars expects four ids 0-7 like 0,1,2,3, got '%s'\n", next);
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--seed") == 0 && next) {
            char *end;
            unsigned long seed = strtoul(next, &end, 0);
            if (end != next && *end == '\0') {
                sAutotest.seedSet = 1;
                sAutotest.seed = (unsigned int)seed;
            } else {
                fprintf(stderr, "[autotest] --seed expects a number, got '%s'\n", next);
                ok = 0;
            }
            i++;
        }
    }
    if (sAutotest.quickstart) {
        printf("[autotest] quickstart: board %d, %d turns, chars %d,%d,%d,%d, cpu level %d, seed %s%u, fast %d\n",
            sAutotest.board, sAutotest.turns, sAutotest.chars[0], sAutotest.chars[1], sAutotest.chars[2],
            sAutotest.chars[3], sAutotest.cpuLevel, sAutotest.seedSet ? "" : "(clock) ", sAutotest.seed,
            sAutotest.fast);
    }
    return ok;
}

const PartyBoardAutotest *partyboard_autotest_get(void)
{
    return &sAutotest;
}

int partyboard_autotest_quickstart(void)
{
    return sAutotest.quickstart;
}

void partyboard_autotest_apply_seed(void)
{
    if (!sAutotest.seedSet) {
        return;
    }
    // frand treats 0 as "unseeded" and reseeds from the clock, so never hand it 0.
    frand_seed_set(sAutotest.seed ? sAutotest.seed : 1);
    rnd_seed = (s32)sAutotest.seed;
    srand(sAutotest.seed);
}

// Mirrors what party mode (mentDll) does before calling the board overlay.
void partyboard_autotest_setup_party(void)
{
    s32 i;
    BoardPartyConfigSet(0, 1, 0, sAutotest.turns, 0, 0, 0, 0);
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = sAutotest.chars[i];
        GWPlayerCfg[i].pad_idx = i;
        GWPlayerCfg[i].diff = sAutotest.cpuLevel;
        GWPlayerCfg[i].group = 0;
        GWPlayerCfg[i].iscom = 1;
    }
    GWMessSpeedSet(0);
    GWMGExplainSet(0);
    GWMGShowComSet(1);
    BoardSaveInit(sAutotest.board);
    for (i = 0; i < 4; i++) {
        CharMotionInit(GWPlayerCfg[i].character);
    }
    printf("[autotest] game %d start: board %d, %d turns\n", sAutotest.gamesFinished + 1, sAutotest.board,
        sAutotest.turns);
    fflush(stdout);
}

int partyboard_autotest_next_game(void)
{
    sAutotest.gamesFinished++;
    printf("[autotest] game %d finished: board %d\n", sAutotest.gamesFinished, sAutotest.board);
    fflush(stdout);
    if (!sAutotest.loop) {
        PartyBoard_IsRunning = false;
        return 0;
    }
    sAutotest.board = (sAutotest.board + 1) % 6;
    return 1;
}
