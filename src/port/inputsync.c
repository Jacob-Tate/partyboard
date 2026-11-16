#include "port/inputsync.h"

#include "port/autotest.h"
#include "port/main.h"
#include "port/netplay.h"

#include <dolphin/pad.h>
#include <stdio.h>
#include <string.h>

// Recording file layout (same build on both ends, so PADStatus is written raw):
//   InputFileHeader, then per controller read: u32 PADRead result + PADStatus[4].

#define INPUT_MAGIC "PBINPUT1"
#define INPUT_VERSION 1

typedef struct InputFileHeader {
    char magic[8];
    u32 version;
    u32 padStatusSize;
    u32 seed;
    s32 board;
    s32 turns;
    s32 chars[4];
    s32 cpuLevel;
    s32 humans;
} InputFileHeader;

typedef enum { INPUT_LIVE, INPUT_RECORD, INPUT_REPLAY } InputMode;

static InputMode sMode = INPUT_LIVE;
static FILE *sFile = NULL;
static u32 sReads = 0;
static int sReplayEnded = 0;

int partyboard_input_open(const char *recordPath, const char *replayPath)
{
    if (recordPath && replayPath) {
        fprintf(stderr, "[input] --record and --replay can't be used together\n");
        return 0;
    }
    if (replayPath) {
        InputFileHeader header;
        sFile = fopen(replayPath, "rb");
        if (!sFile || fread(&header, sizeof(header), 1, sFile) != 1 || memcmp(header.magic, INPUT_MAGIC, 8) != 0
            || header.version != INPUT_VERSION) {
            fprintf(stderr, "[input] '%s' is not a Party Board input recording\n", replayPath);
            return 0;
        }
        if (header.padStatusSize != sizeof(PADStatus)) {
            fprintf(stderr, "[input] recording was made by a different build (PADStatus %u bytes, expected %u)\n",
                header.padStatusSize, (unsigned)sizeof(PADStatus));
            return 0;
        }
        // The recording carries the game settings, so a replay needs nothing else.
        partyboard_autotest_configure_replay(header.seed, header.board, header.turns, header.chars, header.cpuLevel,
            header.humans);
        sMode = INPUT_REPLAY;
        printf("[input] replaying %s\n", replayPath);
        return 1;
    }
    if (recordPath) {
        const PartyBoardAutotest *t = partyboard_autotest_get();
        InputFileHeader header;
        if (!t->quickstart || !t->seedSet) {
            fprintf(stderr, "[input] --record needs --quickstart and --seed so the game can be replayed\n");
            return 0;
        }
        sFile = fopen(recordPath, "wb");
        if (!sFile) {
            fprintf(stderr, "[input] cannot create '%s'\n", recordPath);
            return 0;
        }
        memset(&header, 0, sizeof(header));
        memcpy(header.magic, INPUT_MAGIC, 8);
        header.version = INPUT_VERSION;
        header.padStatusSize = sizeof(PADStatus);
        header.seed = t->seed;
        header.board = t->board;
        header.turns = t->turns;
        memcpy(header.chars, t->chars, sizeof(header.chars));
        header.cpuLevel = t->cpuLevel;
        header.humans = t->humans;
        fwrite(&header, sizeof(header), 1, sFile);
        sMode = INPUT_RECORD;
        printf("[input] recording to %s\n", recordPath);
        return 1;
    }
    return 1;
}

u32 partyboard_input_pad_read(PADStatus *status)
{
    u32 result;
    if (partyboard_netplay_active()) {
        // The result is which controllers can rumble; minigames show "!!" instead for the ones that
        // can't. It must be the same on every machine, so say all of them can (they do: vibration goes
        // to each player's own controller, see partyboard_input_control_motor).
        partyboard_netplay_pad_read(status);
        return PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;
    }
    if (sMode == INPUT_REPLAY) {
        if (!sReplayEnded && fread(&result, sizeof(result), 1, sFile) == 1
            && fread(status, sizeof(PADStatus), PAD_MAX_CONTROLLERS, sFile) == PAD_MAX_CONTROLLERS) {
            sReads++;
            return result;
        }
        if (!sReplayEnded) {
            sReplayEnded = 1;
            printf("[input] replay ended after %u controller reads\n", sReads);
            fflush(stdout);
            PartyBoard_IsRunning = false;
        }
        memset(status, 0, sizeof(PADStatus) * PAD_MAX_CONTROLLERS);
        return 0;
    }

    result = PADRead(status);
    if (sMode == INPUT_RECORD) {
        fwrite(&result, sizeof(result), 1, sFile);
        fwrite(status, sizeof(PADStatus), PAD_MAX_CONTROLLERS, sFile);
        sReads++;
    }
    return result;
}

void partyboard_input_control_motor(s32 chan, u32 command)
{
    if (partyboard_netplay_active()) {
        // chan is a seat; only the seats played on this machine rumble, on their local controller.
        const int slot = partyboard_netplay_local_slot(chan);
        if (slot >= 0) {
            PADControlMotor(slot, command);
        }
        return;
    }
    PADControlMotor(chan, command);
}

int partyboard_input_is_synced(void)
{
    return sMode != INPUT_LIVE || partyboard_netplay_active();
}

void partyboard_input_close(void)
{
    if (sFile) {
        fclose(sFile);
        sFile = NULL;
        if (sMode == INPUT_RECORD) {
            printf("[input] recorded %u controller reads\n", sReads);
        }
    }
}
