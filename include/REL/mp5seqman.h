#ifndef _REL_MP5SEQMAN_H
#define _REL_MP5SEQMAN_H

// Mario Party 5's minigame sequencer (game/mg/seqman.c) for the MP5 ports: it runs a minigame through
// init -> fade in -> START -> main -> FINISH -> winner -> fade out, calling the game's hook for each mode
// with (mode, frame in that mode). Same logic as MP5's, on MP4's MGSeq messages, wipes and the MgTimer of
// mp5compat.h. Included by REL/mp5compat.h (static: each overlay gets its own copy).

#define MGSEQ_MODEHOOK_NULL -1

#define MGSEQ_MODE_NONE 0
#define MGSEQ_MODE_INIT 1
#define MGSEQ_MODE_FADEIN 2
#define MGSEQ_MODE_START 3
#define MGSEQ_MODE_PREMAIN 4
#define MGSEQ_MODE_MAIN 5
#define MGSEQ_MODE_FINISH 6
#define MGSEQ_MODE_PREWIN 7
#define MGSEQ_MODE_WINNER 8
#define MGSEQ_MODE_FADEOUT 9
#define MGSEQ_MODE_CLOSE 10
#define MGSEQ_MODE_EXIT 11
#define MGSEQ_MODE_MAX 12

#define MGSEQ_MODEHOOK_MAX 64

#define MGSEQ_STAT_MODENEXT (1 << 0)
#define MGSEQ_STAT_MODECHANGE_OFF (1 << 1)
#define MGSEQ_STAT_RECORD (1 << 2)
#define MGSEQ_STAT_WINNER (1 << 3)
#define MGSEQ_STAT_UNKBIT (1 << 4)
#define MGSEQ_STAT_FADEIN_OFF (1 << 5)
#define MGSEQ_STAT_FADEOUT_OFF (1 << 6)

#define MGSEQ_TIMER_TOP 0
#define MGSEQ_TIMER_BOTTOM 1
#define MGSEQ_TIMER_RIGHT 2

#ifndef CHARNO_NONE
#define CHARNO_NONE -1
#endif
#define MgSeqWinnerSet1(charNo) MgSeqWinnerSet(charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE)
#define MgSeqWinnerSet2(charNo1, charNo2) MgSeqWinnerSet(charNo1, charNo2, CHARNO_NONE, CHARNO_NONE)
#define MgSeqWinnerSet3(charNo1, charNo2, charNo3) MgSeqWinnerSet(charNo1, charNo2, charNo3, CHARNO_NONE)

typedef void (*MGSEQ_FUNC)(s16 mode, s16 frameNo);

typedef struct MgSeqParam_s {
    s16 maxTime; // seconds; 0: no timer, 300: a 30 s timer appears after 269 s
    u8 timerPos; // MGSEQ_TIMER_*
    MGSEQ_FUNC initHook;
    MGSEQ_FUNC fadeInHook;
    MGSEQ_FUNC startHook;
    MGSEQ_FUNC mainHook;
    MGSEQ_FUNC finishHook;
    MGSEQ_FUNC preWinnerHook;
    MGSEQ_FUNC winnerHook;
    MGSEQ_FUNC fadeOutHook;
    MGSEQ_FUNC closeHook;
} MGSEQ_PARAM;

typedef struct {
    u16 mode;
    MGSEQ_FUNC hook;
} MGSEQ_MODEHOOK;

static struct {
    MGSEQ_PARAM param;
    MGTIMER *timer;
    u16 statBit;
    u16 mode;
    s32 recordVal;
    s16 winner[4];
    s16 modeDelayTbl[MGSEQ_MODE_MAX];
    u16 modeHookNum;
    MGSEQ_MODEHOOK modeHook[MGSEQ_MODEHOOK_MAX];
} mp5SeqWork;
static HUPROCESS *mp5SeqProc;
static u32 mp5SeqFrameNo;
static s16 mp5SeqGameMesId;
static const s16 mp5SeqDefModeDelayTbl[MGSEQ_MODE_MAX] = { -1, -1, 240, -1, -1, -1, -1, 240, 210, 60, -1, -1 };

static void Mp5SeqExecModeHooks(s16 mode, s16 frameNo)
{
    s16 i;
    for (i = 0; i < mp5SeqWork.modeHookNum; i++) {
        if (mp5SeqWork.modeHook[i].mode == mode) {
            mp5SeqWork.modeHook[i].hook(mode, frameNo);
        }
    }
}

static void Mp5SeqSetTimerPos(s32 pos, MGTIMER *timer)
{
    switch (pos) {
        case MGSEQ_TIMER_BOTTOM:
            MgTimerPosSet(timer, 288.0f, 420.0f);
            break;
        case MGSEQ_TIMER_RIGHT:
            MgTimerPosSet(timer, 525.0f, 64.0f);
            break;
    }
}

// One mode: call its hook (and the mode hooks) each frame for `delay` frames, or until MgSeqModeNext when the
// delay is -1 (or MgSeqModeChangeOff is set). `done` (if set) ends the mode as well, when it returns FALSE.
static void Mp5SeqRunMode(MGSEQ_FUNC hook, s32 delay, BOOL (*active)(void))
{
    if (delay == -1) {
        mp5SeqWork.statBit |= MGSEQ_STAT_MODECHANGE_OFF;
        delay = 0;
    }
    for (; active ? active() : (mp5SeqFrameNo < (u32)delay || (mp5SeqWork.statBit & MGSEQ_STAT_MODECHANGE_OFF));
         mp5SeqFrameNo++) {
        if (hook) {
            hook(mp5SeqWork.mode, mp5SeqFrameNo);
        }
        Mp5SeqExecModeHooks(mp5SeqWork.mode, mp5SeqFrameNo);
        if (mp5SeqWork.statBit & MGSEQ_STAT_MODENEXT) {
            mp5SeqWork.statBit &= ~MGSEQ_STAT_MODENEXT;
            break;
        }
        HuPrcVSleep();
    }
}

static BOOL Mp5SeqGameMesActive(void)
{
    return MGSeqStatGet(mp5SeqGameMesId) != 0;
}

static void Mp5SeqExecProc(void)
{
    while (TRUE) {
        if (mp5SeqWork.mode == MGSEQ_MODE_NONE) {
            mp5SeqWork.mode = MGSEQ_MODE_INIT;
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.initHook, mp5SeqWork.modeDelayTbl[MGSEQ_MODE_INIT], NULL);
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_INIT || mp5SeqWork.mode == MGSEQ_MODE_FADEIN) {
            mp5SeqWork.mode = MGSEQ_MODE_FADEIN;
            if (!(mp5SeqWork.statBit & MGSEQ_STAT_FADEIN_OFF)) {
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            }
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.fadeInHook, mp5SeqWork.modeDelayTbl[MGSEQ_MODE_FADEIN], NULL);
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_FADEIN || mp5SeqWork.mode == MGSEQ_MODE_START) {
            mp5SeqWork.mode = MGSEQ_MODE_START;
            mp5SeqGameMesId = MGSeqStartCreate();
            if (mp5SeqWork.param.maxTime != 0 && mp5SeqWork.param.maxTime != 300) {
                mp5SeqWork.timer = MgTimerCreate(0);
                MgTimerParamSet(mp5SeqWork.timer, mp5SeqWork.param.maxTime * 60, 0, 0);
                Mp5SeqSetTimerPos(mp5SeqWork.param.timerPos, mp5SeqWork.timer);
            }
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.startHook, 0, Mp5SeqGameMesActive);
            if (mp5SeqWork.timer) {
                MgTimerModeOnSet(mp5SeqWork.timer, MGTIMER_OFFTYPE_FADEOUT);
            }
            mp5SeqFrameNo = 0;
            Mp5SeqExecModeHooks(MGSEQ_MODE_PREMAIN, mp5SeqFrameNo);
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_START || mp5SeqWork.mode == MGSEQ_MODE_MAIN) {
            mp5SeqWork.mode = MGSEQ_MODE_MAIN;
            mp5SeqFrameNo = 0;
            while (TRUE) {
                if (mp5SeqWork.param.mainHook) {
                    mp5SeqWork.param.mainHook(mp5SeqWork.mode, mp5SeqFrameNo);
                }
                Mp5SeqExecModeHooks(mp5SeqWork.mode, mp5SeqFrameNo);
                if (mp5SeqWork.param.maxTime == 300 && mp5SeqFrameNo == 16140) {
                    mp5SeqWork.timer = MgTimerCreate(0);
                    MgTimerParamSet(mp5SeqWork.timer, 1800, 0, 0);
                    Mp5SeqSetTimerPos(mp5SeqWork.param.timerPos, mp5SeqWork.timer);
                    MgTimerModeOnSet(mp5SeqWork.timer, MGTIMER_OFFTYPE_FADEOUT);
                }
                if ((mp5SeqWork.timer && MgTimerDoneCheck(mp5SeqWork.timer)) || (mp5SeqWork.statBit & MGSEQ_STAT_MODENEXT)) {
                    HuPrcVSleep();
                    mp5SeqWork.statBit &= ~MGSEQ_STAT_MODENEXT;
                    break;
                }
                HuPrcVSleep();
                mp5SeqFrameNo++;
            }
        }
        if (mp5SeqWork.timer && !MgTimerDoneCheck(mp5SeqWork.timer)) {
            if (!mp5SeqWork.timer->stopF) {
                mp5SeqWork.timer->stopF = TRUE;
                mp5SeqWork.timer->mode = MGTIMER_MODE_ON;
            }
            mp5SeqWork.timer = NULL;
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_MAIN || mp5SeqWork.mode == MGSEQ_MODE_FINISH) {
            mp5SeqWork.mode = MGSEQ_MODE_FINISH;
            mp5SeqGameMesId = MGSeqFinishCreate();
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.finishHook, 0, Mp5SeqGameMesActive);
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_FINISH || mp5SeqWork.mode == MGSEQ_MODE_PREWIN) {
            s32 delay = mp5SeqWork.modeDelayTbl[MGSEQ_MODE_PREWIN];
            // the pre-winner mode counts on from FINISH's frames (up to 90)
            if (mp5SeqWork.mode != MGSEQ_MODE_FINISH || mp5SeqFrameNo >= 90) {
                mp5SeqFrameNo = 0;
            }
            mp5SeqWork.mode = MGSEQ_MODE_PREWIN;
            if (delay == -1) {
                mp5SeqWork.statBit |= MGSEQ_STAT_MODECHANGE_OFF;
                delay = 0;
            }
            for (; mp5SeqFrameNo < (u32)delay || (mp5SeqWork.statBit & MGSEQ_STAT_MODECHANGE_OFF); mp5SeqFrameNo++) {
                if (mp5SeqWork.param.preWinnerHook) {
                    mp5SeqWork.param.preWinnerHook(mp5SeqWork.mode, mp5SeqFrameNo);
                }
                Mp5SeqExecModeHooks(mp5SeqWork.mode, mp5SeqFrameNo);
                if ((mp5SeqWork.statBit & MGSEQ_STAT_RECORD) && mp5SeqFrameNo == 90) {
                    if (delay == mp5SeqDefModeDelayTbl[MGSEQ_MODE_PREWIN]) {
                        delay = 270;
                    }
                    MGSeqRecordCreate(mp5SeqWork.recordVal);
                }
                if (mp5SeqWork.statBit & MGSEQ_STAT_MODENEXT) {
                    mp5SeqWork.statBit &= ~MGSEQ_STAT_MODENEXT;
                    break;
                }
                HuPrcVSleep();
            }
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_PREWIN || mp5SeqWork.mode == MGSEQ_MODE_WINNER) {
            mp5SeqWork.mode = MGSEQ_MODE_WINNER;
            if (mp5SeqWork.statBit & MGSEQ_STAT_WINNER) {
                if (mp5SeqWork.winner[0] == GAMEMES_MG_WINNER_NONE && mp5SeqWork.winner[1] == GAMEMES_MG_WINNER_NONE
                    && mp5SeqWork.winner[2] == GAMEMES_MG_WINNER_NONE && mp5SeqWork.winner[3] == GAMEMES_MG_WINNER_NONE) {
                    MGSeqDrawCreate();
                    HuAudJinglePlay(MSM_STREAM_JNGL_MG_DRAW);
                }
                else {
                    MGSeqWinCreate(mp5SeqWork.winner[0], mp5SeqWork.winner[1], mp5SeqWork.winner[2], mp5SeqWork.winner[3]);
                    HuAudJinglePlay(MSM_STREAM_JNGL_MG_WIN);
                }
            }
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.winnerHook, mp5SeqWork.modeDelayTbl[MGSEQ_MODE_WINNER], NULL);
        }
        mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
        if (mp5SeqWork.mode == MGSEQ_MODE_WINNER || mp5SeqWork.mode == MGSEQ_MODE_FADEOUT) {
            mp5SeqWork.mode = MGSEQ_MODE_FADEOUT;
            if (!(mp5SeqWork.statBit & MGSEQ_STAT_FADEOUT_OFF)) {
                Mp5WipeWhite(WIPE_MODE_OUT, 60);
                HuAudFadeOut(1000);
            }
            mp5SeqFrameNo = 0;
            Mp5SeqRunMode(mp5SeqWork.param.fadeOutHook, mp5SeqWork.modeDelayTbl[MGSEQ_MODE_FADEOUT], NULL);
        }
        if (mp5SeqWork.mode == MGSEQ_MODE_FADEOUT || mp5SeqWork.mode == MGSEQ_MODE_CLOSE) {
            break;
        }
    }
    mp5SeqWork.mode = MGSEQ_MODE_CLOSE;
    mp5SeqFrameNo = 0;
    if (mp5SeqWork.param.closeHook) {
        mp5SeqWork.param.closeHook(mp5SeqWork.mode, mp5SeqFrameNo);
    }
    Mp5SeqExecModeHooks(mp5SeqWork.mode, mp5SeqFrameNo);
    omOvlReturn(1);
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

// Quitting the minigame (omSysExitReq, e.g. from the pause menu).
static void Mp5SeqExit(void)
{
    while (!omSysExitReq) {
        HuPrcVSleep();
    }
    Mp5WipeWhite(WIPE_MODE_OUT, 60);
    HuAudFadeOut(1000);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    if (mp5SeqWork.param.closeHook) {
        mp5SeqWork.param.closeHook(MGSEQ_MODE_EXIT, 0);
    }
    Mp5SeqExecModeHooks(MGSEQ_MODE_EXIT, 0);
    omOvlReturn(1);
    HuPrcKill(mp5SeqProc);
    while (TRUE) {
        HuPrcVSleep();
    }
}

static void MgSeqCreatePrio(MGSEQ_PARAM *param, s32 prio)
{
    s16 i;
    mp5SeqWork.param = *param;
    mp5SeqWork.statBit = 0;
    mp5SeqWork.mode = MGSEQ_MODE_NONE;
    mp5SeqWork.timer = NULL;
    mp5SeqWork.modeHookNum = 0;
    for (i = 0; i < MGSEQ_MODE_MAX; i++) {
        mp5SeqWork.modeDelayTbl[i] = mp5SeqDefModeDelayTbl[i];
    }
    mp5SeqProc = HuPrcChildCreate(Mp5SeqExecProc, prio, 0x3000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(Mp5SeqExit, prio, 0x3000, 0, mp5SeqProc);
    mp5SeqGameMesId = -1;
}

static void MgSeqCreate(MGSEQ_PARAM *param)
{
    MgSeqCreatePrio(param, 100);
}

static void MgSeqKill(void)
{
    mp5SeqWork.mode = MGSEQ_MODE_NONE;
    HuPrcKill(mp5SeqProc);
}

static u32 MgSeqModeGet(void)
{
    return mp5SeqWork.mode;
}

static u32 MgSeqModeNext(void)
{
    mp5SeqWork.statBit |= MGSEQ_STAT_MODENEXT;
    return mp5SeqWork.mode;
}

static u32 MgSeqModeSet(u32 mode)
{
    if (mode > MGSEQ_MODE_CLOSE) {
        mode = MGSEQ_MODE_CLOSE;
    }
    mp5SeqWork.mode = mode;
    mp5SeqWork.statBit |= MGSEQ_STAT_MODENEXT;
    return mp5SeqWork.mode;
}

static u16 MgSeqModeChangeOff(void)
{
    mp5SeqWork.statBit |= MGSEQ_STAT_MODECHANGE_OFF;
    return mp5SeqWork.statBit;
}

static u16 MgSeqModeChangeOn(void)
{
    mp5SeqWork.statBit &= ~MGSEQ_STAT_MODECHANGE_OFF;
    return mp5SeqWork.statBit;
}

static s32 MgSeqTimerValueGet(void)
{
    if (!mp5SeqWork.timer) {
        return mp5SeqWork.param.maxTime * 60;
    }
    return MgTimerValueGet(mp5SeqWork.timer);
}

static void MgSeqRecordSet(s32 recordVal)
{
    if (!_CheckFlag(MP5_PRACTICE_FLAG)) {
        mp5SeqWork.statBit |= MGSEQ_STAT_RECORD;
        mp5SeqWork.recordVal = recordVal;
    }
}

static u16 MgSeqStatGet(void)
{
    return mp5SeqWork.statBit;
}

static u16 MgSeqWinnerSet(s16 charNo1, s16 charNo2, s16 charNo3, s16 charNo4)
{
    mp5SeqWork.winner[0] = charNo1;
    mp5SeqWork.winner[1] = charNo2;
    mp5SeqWork.winner[2] = charNo3;
    mp5SeqWork.winner[3] = charNo4;
    mp5SeqWork.statBit |= MGSEQ_STAT_WINNER;
    return mp5SeqWork.statBit;
}

static u16 MgSeqDrawSet(void)
{
    mp5SeqWork.winner[0] = mp5SeqWork.winner[1] = mp5SeqWork.winner[2] = mp5SeqWork.winner[3] = GAMEMES_MG_WINNER_NONE;
    mp5SeqWork.statBit |= MGSEQ_STAT_WINNER;
    return mp5SeqWork.statBit;
}

static void MgSeqModeDelaySet(s16 mode, s16 delay)
{
    if (mode < 0 || mode >= MGSEQ_MODE_MAX) {
        return;
    }
    mp5SeqWork.modeDelayTbl[mode] = delay;
}

static u32 MgSeqModeHookAdd(s16 mode, MGSEQ_FUNC hook)
{
    if (mode < 0 || mode >= MGSEQ_MODE_MAX || mp5SeqWork.modeHookNum >= MGSEQ_MODEHOOK_MAX) {
        return -1;
    }
    mp5SeqWork.modeHook[mp5SeqWork.modeHookNum].mode = mode;
    mp5SeqWork.modeHook[mp5SeqWork.modeHookNum].hook = hook;
    mp5SeqWork.modeHookNum++;
    return mp5SeqWork.modeHookNum - 1;
}

static void MgSeqModeHookReset(s16 hook)
{
    mp5SeqWork.modeHook[hook].mode = MGSEQ_MODEHOOK_NULL;
}

static u32 MgSeqFrameNoGet(void)
{
    return mp5SeqFrameNo;
}

static s16 MgSeqGameMesIdGet(void)
{
    return mp5SeqGameMesId;
}

static void MgSeqMaxTimeSet(s16 maxTime)
{
    if (mp5SeqWork.timer) {
        MgTimerKill(mp5SeqWork.timer);
    }
    mp5SeqWork.timer = NULL;
    mp5SeqWork.param.maxTime = maxTime;
}

static void MgSeqStatBitSet(u16 bit)
{
    mp5SeqWork.statBit |= bit;
}

static void MgSeqStatBitReset(u16 bit)
{
    mp5SeqWork.statBit &= ~bit;
}

#endif
