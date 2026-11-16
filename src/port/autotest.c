#include "port/autotest.h"

#include "game/board/main.h"
#include "game/chrman.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/saveload.h"
#include "game/board/mg_setup.h"
#include "port/byteswap.h"
#include "port/inputsync.h"
#include "port/main.h"
#include "port/netplay.h"
#include "netplay/protocol.h"

#include <SDL3/SDL_timer.h>
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
    0,              // humans
    0,              // humanMask
    0,              // seedSet
    0,              // seed
    0,              // fast
    0,              // loop
    0,              // gamesFinished
    0,              // maxFrames
    0,              // dumpFrame
    NULL,           // isoPath
    NULL,           // checksumLogPath
};

static FILE *sChecksumLog = NULL;
static OMOVL sLastOvl = -1;

extern u32 GlobalCounter;
u32 frand_seed_get(void);

// FNV-1a, 32-bit.
static u32 hash_bytes(u32 hash, const void *data, size_t size)
{
    const u8 *p = (const u8 *)data;
    size_t i;
    for (i = 0; i < size; i++) {
        hash ^= p[i];
        hash *= 16777619u;
    }
    return hash;
}

static void dump_bytes(const char *name, const void *data, size_t size)
{
    const u8 *p = (const u8 *)data;
    size_t i;
    fprintf(sChecksumLog, "# dump %s %u bytes:", name, (unsigned)size);
    for (i = 0; i < size; i++) {
        fprintf(sChecksumLog, "%s%02x", (i % 32) ? " " : "\n#   ", p[i]);
    }
    fprintf(sChecksumLog, "\n");
}

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
    const char *recordPath = NULL;
    const char *replayPath = NULL;
    for (i = 1; i < argc; i++) {
        const char *arg = argv[i];
        const char *next = (i + 1 < argc) ? argv[i + 1] : NULL;
        int value;

        if (strcmp(arg, "--quickstart") == 0) {
            sAutotest.quickstart = 1;
        } else if (strcmp(arg, "--menu") == 0) {
            sAutotest.menu = 1;
        } else if (strcmp(arg, "--fast") == 0) {
            sAutotest.fast = 1;
        } else if (strcmp(arg, "--loop") == 0) {
            sAutotest.loop = 1;
        } else if (strcmp(arg, "--dump-frame") == 0 && next) {
            sAutotest.dumpFrame = (unsigned int)strtoul(next, NULL, 0);
            i++;
        } else if (strcmp(arg, "--checksum-log") == 0 && next) {
            sAutotest.checksumLogPath = next;
            i++;
        } else if (strcmp(arg, "--max-frames") == 0 && next) {
            char *end;
            unsigned long frames = strtoul(next, &end, 0);
            if (end != next && *end == '\0' && frames > 0) {
                sAutotest.maxFrames = (unsigned int)frames;
            } else {
                fprintf(stderr, "[autotest] --max-frames expects a positive number, got '%s'\n", next);
                ok = 0;
            }
            i++;
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
            // At least 3: board events divide by (max_turn / 3), e.g. w03Dll/statue.c. The real game
            // never goes below 10, and PowerPC doesn't trap on divide by zero but x86 does.
            if (parse_int(next, 3, 99, &value)) {
                sAutotest.turns = value;
            } else {
                fprintf(stderr, "[autotest] --turns expects 3-99, got '%s'\n", next);
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
        } else if (strcmp(arg, "--humans") == 0 && next) {
            if (parse_int(next, 0, 4, &value)) {
                sAutotest.humans = value;
                sAutotest.humanMask = (1 << value) - 1;
            } else {
                fprintf(stderr, "[autotest] --humans expects 0-4, got '%s'\n", next);
                ok = 0;
            }
            i++;
        } else if (strcmp(arg, "--record") == 0 && next) {
            recordPath = next;
            i++;
        } else if (strcmp(arg, "--replay") == 0 && next) {
            replayPath = next;
            i++;
        } else if (strcmp(arg, "--chars") == 0 && next) {
            if (!parse_chars(next, sAutotest.chars)) {
                fprintf(stderr, "[autotest] --chars expects four ids 0-7 like 0,1,2,3, got '%s'\n", next);
                ok = 0;
            }
            sAutotest.charsSet = 1;
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
    if (ok && !partyboard_input_open(recordPath, replayPath)) {
        ok = 0;
    }
    if (sAutotest.checksumLogPath) {
        sChecksumLog = fopen(sAutotest.checksumLogPath, "w");
        if (!sChecksumLog) {
            fprintf(stderr, "[autotest] cannot open checksum log '%s'\n", sAutotest.checksumLogPath);
            ok = 0;
        } else {
            setvbuf(sChecksumLog, NULL, _IOFBF, 1 << 16);
            fprintf(sChecksumLog, "# frame ovl frand rand8 boardrand system players playercfg\n");
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

void partyboard_autotest_configure_replay(unsigned int seed, int board, int turns, const int chars[4], int cpuLevel,
    int humans)
{
    sAutotest.quickstart = 1;
    sAutotest.seedSet = 1;
    sAutotest.seed = seed;
    sAutotest.board = board;
    sAutotest.turns = turns;
    memcpy(sAutotest.chars, chars, sizeof(sAutotest.chars));
    sAutotest.cpuLevel = cpuLevel;
    sAutotest.humans = humans;
    sAutotest.humanMask = (1 << humans) - 1;
}

void partyboard_autotest_configure_netplay(unsigned int seed, int board, int turns, const int chars[4], int cpuLevel,
    int humanMask)
{
    int i;
    partyboard_autotest_configure_replay(seed, board, turns, chars, cpuLevel, 0);
    sAutotest.humanMask = humanMask;
    for (i = 0; i < 4; i++) {
        sAutotest.humans += (humanMask >> i) & 1;
    }
}

int partyboard_autotest_seeded(void)
{
    return sAutotest.seedSet;
}

unsigned int partyboard_autotest_frame_seed(void)
{
    // Frame counts match across machines in lockstep, so this stays deterministic.
    u32 x = (u32)sAutotest.seed ^ (GlobalCounter * 0x9E3779B9u);
    x ^= x >> 16;
    x *= 0x7FEB352Du;
    x ^= x >> 15;
    return x;
}

void partyboard_autotest_yield(void)
{
    SDL_Delay(0);
}

// A continued online game's saved board state (GWSystem + GWPlayer[4], GameCube byte order), 0 bytes for a new game.
static u8 sContinueState[PB_NET_MAX_CONTINUE_STATE];
static int sContinueSize = 0;

static int sTeamBattle = 0;
static int sBonusStars = 1;

void partyboard_autotest_set_party_options(int teams, int bonusStars)
{
    sTeamBattle = teams ? 1 : 0;
    sBonusStars = bonusStars ? 1 : 0;
}

void partyboard_autotest_set_continue_state(const unsigned char *state, int size)
{
    sContinueSize = (state && size > 0 && size <= (int)sizeof(sContinueState)) ? size : 0;
    if (sContinueSize) {
        memcpy(sContinueState, state, sContinueSize);
    }
}

// A continue: what mentDll's party Continue does (SLLoadBoard), from the online save's state, then today's seating.
static void setup_continue(void)
{
    s32 i;
    memcpy(&GWSystem, sContinueState, sizeof(SystemState));
    byteswap_systemstate(&GWSystem);
    for (i = 0; i < 4; i++) {
        int human;
        memcpy(&GWPlayer[i], sContinueState + sizeof(SystemState) + i * sizeof(PlayerState), sizeof(PlayerState));
        byteswap_playerstate(&GWPlayer[i]);
        // The records are in turn order; each keeps the seat (lockstep pad) it plays. Whoever sits in that seat now
        // decides human or CPU.
        human = (sAutotest.humanMask >> (GWPlayer[i].port & 3)) & 1;
        GWPlayer[i].com = human ? 0 : 1;
        if (!human) {
            GWPlayer[i].diff = sAutotest.cpuLevel;
        }
        GWPlayerCfg[i].character = GWPlayer[i].character;
        GWPlayerCfg[i].pad_idx = GWPlayer[i].port;
        GWPlayerCfg[i].diff = GWPlayer[i].diff;
        GWPlayerCfg[i].iscom = GWPlayer[i].com;
        GWPlayerCfg[i].group = GWPlayer[i].team;
    }
    GWMessSpeedSet(1);
    GWMGExplainSet(1);
    SLSaveFlagSet(0);
    // A continued board keeps its flags, so it doesn't clear the recently played minigames (board/main.c): those
    // are whatever this process played before. Clear them, as a console's Continue after power-on has them.
    BoardMGSetupPlayClear();
    for (i = 0; i < 4; i++) {
        CharMotionInit(GWPlayerCfg[i].character);
    }
    printf("[autotest] continuing: board %d, turn %d of %d\n", GWSystem.board, GWSystem.turn, GWSystem.max_turn);
    fflush(stdout);
}

// Mirrors what party mode (mentDll) does before calling the board overlay.
void partyboard_autotest_setup_party(void)
{
    s32 i;
    if (partyboard_netplay_active()) {
        // Minigames pick rumble or "!!" signals from this option; it comes from each machine's memory
        // card, so make it the same everywhere (the pause menu can still change it, in sync).
        GWRumbleSet(1);
    }
    if (sContinueSize == (int)(sizeof(SystemState) + 4 * sizeof(PlayerState))) {
        setup_continue();
        return;
    }
    BoardPartyConfigSet(sTeamBattle, sBonusStars, 0, sAutotest.turns, 0, 0, 0, 0);
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = sAutotest.chars[i];
        GWPlayerCfg[i].pad_idx = i;
        GWPlayerCfg[i].diff = sAutotest.cpuLevel;
        GWPlayerCfg[i].group = sTeamBattle ? i / 2 : 0; // team battle: P1+P2 against P3+P4
        GWPlayerCfg[i].iscom = (sAutotest.humanMask & (1 << i)) ? 0 : 1;
    }
    if (partyboard_netplay_active()) {
        // People are playing: the game's own defaults, with minigame instructions (and Practice).
        GWMessSpeedSet(1);
        GWMGExplainSet(1);
    } else {
        // Unattended test runs: fast text and no instruction screens to wait on.
        GWMessSpeedSet(0);
        GWMGExplainSet(0);
    }
    GWMGShowComSet(1);
    // Never touch the memory card: whether a save file exists changes how many frames the
    // results screen takes (save path vs. plain fade), which desyncs PCs with different saves.
    SLSaveFlagSet(0);
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
    if (sChecksumLog) {
        fprintf(sChecksumLog, "# game %d finished at frame %u\n", sAutotest.gamesFinished, GlobalCounter);
    }
    if (!sAutotest.loop) {
        partyboard_netplay_game_over();
        PartyBoard_IsRunning = false;
        return 0;
    }
    sAutotest.board = (sAutotest.board + 1) % 6;
    return 1;
}

void partyboard_autotest_frame_end(void)
{
    if (partyboard_netplay_active() && GlobalCounter % PB_NET_CHECKSUM_INTERVAL == 0) {
        u32 hash = 2166136261u;
        u32 seeds[3];
        seeds[0] = frand_seed_get();
        seeds[1] = (u32)rnd_seed;
        seeds[2] = boardRandSeed;
        hash = hash_bytes(hash, seeds, sizeof(seeds));
        hash = hash_bytes(hash, &GWSystem, sizeof(GWSystem));
        hash = hash_bytes(hash, GWPlayer, sizeof(GWPlayer));
        hash = hash_bytes(hash, GWPlayerCfg, sizeof(GWPlayerCfg));
        partyboard_netplay_checksum(GlobalCounter, hash);
    }
    if (sChecksumLog) {
        u32 sys = hash_bytes(2166136261u, &GWSystem, sizeof(GWSystem));
        u32 players = hash_bytes(2166136261u, GWPlayer, sizeof(GWPlayer));
        u32 cfg = hash_bytes(2166136261u, GWPlayerCfg, sizeof(GWPlayerCfg));
        if (omcurovl != sLastOvl) {
            fprintf(sChecksumLog, "# overlay %d at frame %u\n", (int)omcurovl, GlobalCounter);
            sLastOvl = omcurovl;
        }
        fprintf(sChecksumLog, "%u %d %08x %08x %08x %08x %08x %08x\n", GlobalCounter, (int)omcurovl,
            frand_seed_get(), (u32)rnd_seed, boardRandSeed, sys, players, cfg);
        if (GlobalCounter % 60 == 0) {
            fflush(sChecksumLog); // about once a second, so the log can be watched live
        }
        if (sAutotest.dumpFrame && GlobalCounter == sAutotest.dumpFrame) {
            dump_bytes("GWSystem", &GWSystem, sizeof(GWSystem));
            dump_bytes("GWPlayer", GWPlayer, sizeof(GWPlayer));
            dump_bytes("GWPlayerCfg", GWPlayerCfg, sizeof(GWPlayerCfg));
        }
    }
    if (sAutotest.maxFrames && GlobalCounter >= sAutotest.maxFrames) {
        printf("[autotest] reached --max-frames %u\n", sAutotest.maxFrames);
        fflush(stdout);
        PartyBoard_IsRunning = false;
    }
}

void partyboard_autotest_shutdown(void)
{
    partyboard_input_close();
    if (sChecksumLog) {
        fclose(sChecksumLog);
        sChecksumLog = NULL;
    }
}
