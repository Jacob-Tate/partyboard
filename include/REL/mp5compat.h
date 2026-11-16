#ifndef _REL_MP5COMPAT_H
#define _REL_MP5COMPAT_H

// Shared glue for minigames ported from the Mario Party 5 decompilation (mariopartyrd/marioparty5) onto
// MP4's engine. Their assets come from the user's MP5 image, mounted under /mp5 (port/mp5disc.h, the
// DATADIR_MP5_* entries of datadir_table.h). Include once per overlay, after the game headers.

#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/gamework_data.h"
#include "game/hsfformat.h"
#include "game/hu3d.h"
#include "game/msm.h"
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include <math.h>
#include <string.h>

// MP5 code names parameters near/far; windows.h (pulled in on Windows) defines both as macros.
#undef near
#undef far

// m2c drafts (tools/mp5/fixups.py): a swap whose temporary m2c lost
#define M2C_SWAP(a, b)                         \
    do {                                       \
        char m2c_swap_[sizeof(a)];             \
        memcpy(m2c_swap_, &(a), sizeof(a));    \
        (a) = (b);                             \
        memcpy(&(b), m2c_swap_, sizeof(b));    \
    } while (0)

// ---- Names -------------------------------------------------------------------------------------------

typedef Process HUPROCESS;
typedef Process OMOBJMAN;
typedef omObjData OMOBJ;
#define property user_data // HUPROCESS::property

#define HEAP_HEAP HEAP_SYSTEM
#define HEAP_MODEL HEAP_DATA
#define HU_MEMNUM_OVL MEMORY_DEFAULT_NUM

#define omObjGetDataAs(obj, type) ((type *)(obj)->data)
#define omOvlReturn(level) omOvlReturnEx((level), 1)
#define MP5_PRACTICE_FLAG FLAG_ID_MAKE(1, 12)
#define GWMgCoinSet(player, value) GWPlayerCoinWinSet((player), (value))
#define GW_TYPE_MAN 0 // GWPlayerCfg[].iscom

// MP5 humath.h
#ifndef HuAbs
#define HuAbs(x) (((x) < 0) ? -(x) : (x))
#endif
#ifndef HuSquare
#define HuSquare(x) ((x) * (x))
#endif
#define HuSetVecF(vec, x, y, z) \
    (vec)->x = (x);             \
    (vec)->y = (y);             \
    (vec)->z = (z)
#define HuAddVecF(dst, src1, src2) VECAdd(src1, src2, dst)
#define HuSubVecF(dst, src1, src2) VECSubtract(src1, src2, dst)
#define HuCopyVecF(dst, src) \
    (dst)->x = (src)->x;     \
    (dst)->y = (src)->y;     \
    (dst)->z = (src)->z
#define HuCopyVec2F(dst, src) \
    (dst)->x = (src)->x;      \
    (dst)->y = (src)->y
#define HuMag2Point2D(x, y) (HuSquare(x) + HuSquare(y))
#define HuMag2Point3D(x, y, z) (HuSquare(x) + HuSquare(y) + HuSquare(z))
#define HuMagPoint2D(x, y) sqrtf(HuMag2Point2D(x, y))
#define HuMagPoint3D(x, y, z) sqrtf(HuMag2Point3D(x, y, z))
#define HuMagVecF(vec) HuMagPoint3D((vec)->x, (vec)->y, (vec)->z)
#define HuDistVecF(a, b) HuMagPoint3D((a)->x - (b)->x, (a)->y - (b)->y, (a)->z - (b)->z)
#define HuMagXZVecF(vec) HuMagPoint2D((vec)->x, (vec)->z)
#define HuDistXZVecF(a, b) HuMagPoint2D((a)->x - (b)->x, (a)->z - (b)->z)
#define HuMagXYVecF(vec) HuMagPoint2D((vec)->x, (vec)->y)
#define HuDistXYVecF(a, b) HuMagPoint2D((a)->x - (b)->x, (a)->y - (b)->y)
#define HuMagVec2F(vec) HuMagPoint2D((vec)->x, (vec)->y)
#define HuDistVec2F(a, b) HuMagPoint2D((a)->x - (b)->x, (a)->y - (b)->y)
#define HuScaleVecF(src, dst, scale) VECScale(src, dst, scale)
#define HuNormVecF(src, dst) VECNormalize(src, dst)
#define HuSin(x) sin(M_PI * (x) / 180.0)
#define HuCos(x) cos(M_PI * (x) / 180.0)
#define HuTan(x) tan(M_PI * (x) / 180.0)
#define HuAtan(y, x) (180.0 * (atan2((y), (x)) / M_PI))

#define Hu3DModelCreateData(dataNum) Hu3DModelCreateFile(dataNum)
#define Hu3DModelDispOn(modelId) Hu3DModelAttrReset((modelId), HU3D_ATTR_DISPOFF)
#define Hu3DModelDispOff(modelId) Hu3DModelAttrSet((modelId), HU3D_ATTR_DISPOFF)
#define Hu3DJointMotionData(modelId, dataNum) Hu3DJointMotionFile((modelId), (dataNum))

#define WIPE_TYPE_PREVTYPE WIPE_TYPE_NORMAL
#define WipeCheckEnd() WipeStatGet()

// MP5's GameMes minigame messages are MP4's MGSeq.
typedef s16 GAMEMESID;
#define GAMEMES_MG_WINNER_NONE -1
#define GameMesMgStartCreate() MGSeqStartCreate()
#define GameMesMgFinishCreate() MGSeqFinishCreate()
#define GameMesMgDrawCreate() MGSeqDrawCreate()
#define GameMesMgWinnerCreate(c0, c1, c2, c3) MGSeqWinCreate((c0), (c1), (c2), (c3))
#define GameMesStatGet(id) MGSeqStatGet(id)
#define GameMesKill(id) MGSeqKill(id)
#define GameMesClose() MGSeqKillAll()

// Sound: while a port runs, MSM has Mario Party 5's own sound file loaded (game/audio.c), so the MP5 ids
// below (and the decompilation's) play as they did in MP5.
#include "mp5/msm_grp.h"
#include "mp5/msm_se.h"
#include "mp5/msm_stream.h"
#define MSM_SENO_NONE -1
#define MSM_STREAMNO_NONE -1
#define HuAudFXPlay(seId) HuAudMp5FXPlay(seId)
#define HuAudFXPlayVol(seId, vol) HuAudMp5FXPlayVol((seId), (vol))
#define HuAudFXPlayPan(seId, pan) HuAudMp5FXPlayPan((seId), (pan))
#define HuAudFXPlayVolPan(seId, vol, pan) HuAudMp5FXPlayVolPan((seId), (vol), (pan))
#define HuAudFXEmiterPlay(seId, pos) HuAudMp5FXEmiterPlay((seId), (pos))
#define CharFXPlay(charNo, seId) HuAudMp5CharFXPlayVolPan((charNo), (seId), MSM_VOL_MAX, MSM_PAN_CENTER)
#define CharFXPlayVol(charNo, seId, vol) HuAudMp5CharFXPlayVolPan((charNo), (seId), (vol), MSM_PAN_CENTER)
#define CharFXPlayPan(charNo, seId, pan) HuAudMp5CharFXPlayVolPan((charNo), (seId), MSM_VOL_MAX, (pan))
#define CharFXPlayVolPan(charNo, seId, vol, pan) HuAudMp5CharFXPlayVolPan((charNo), (seId), (vol), (pan))
#define CharFXPlayPos(charNo, seId, pos) HuAudMp5CharFXPlayPos((charNo), (seId), (pos))
#define CharFXStop(charNo, seId) HuAudMp5CharFXStop((charNo), (seId))
#define HuAudJinglePlay(streamId) HuAudSStreamPlay(streamId)
#define HuAudBGMPlay(streamId) HuAudSStreamPlay(streamId)

// MP5's motion end checks honour the start/end range (Hu3DMotionStartEndSet / ShiftStartEndSet); MP4's wait for
// the whole motion, so an MP5 game that plays part of a motion would wait forever (m524's winners kept turning).
static BOOL Mp5MotionEndCheck(s16 modelId)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    if (!(modelP->motAttr & HU3D_MOTATTR_REV)) {
        return modelP->motWork.end <= Hu3DMotionTimeGet(modelId) + 0.0001;
    }
    return Hu3DMotionTimeGet(modelId) <= modelP->motWork.start;
}
#define Hu3DMotionEndCheck(modelId) Mp5MotionEndCheck(modelId)
#define CharMotionEndCheck(charNo) Mp5MotionEndCheck(CharModelIdGet(charNo))

// MP5 motion attributes: bit 0 (HU3D_ATTR_MOT_RESET_LOCK) restarts a looping motion where its visibility lock
// track turns on. MP4's motion code has no such feature, so the bit is only stored (a cosmetic difference).
static void Hu3DMotionAttrSet(s16 motId, u16 attr)
{
    Hu3DMotion[motId].attr |= attr;
}

static void Hu3DMotionAttrReset(s16 motId, u16 attr)
{
    Hu3DMotion[motId].attr &= ~attr;
}

// MP5's landing dust: MP4's smoke puff at the feet.
#ifndef CharModelLandDustCreate
#define CharModelLandDustCreate(charNo, pos) CharEffectSmokeCreate(HU3D_CAM_ALL, (pos))
#endif

// Voice panning has no MP4 counterpart.
#define CharModelVoicePanSet(charNo, pan) ((void)(charNo), (void)(pan))

static void Mp5WipeWhite(s16 mode, s16 duration)
{
    WipeColorSet(255, 255, 255);
    WipeCreate(mode, WIPE_TYPE_NORMAL, duration);
}

// MP5's cross-fade (WIPE_TYPE_CROSSCOPY): its OUT grabs the frame and is done at once, so MP5 code starts the
// IN on the next frame. MP4's cross OUT (1 frame) is still running then and would drop the IN, leaving the
// still frame up: start the IN as soon as the OUT has finished.
static s16 mp5WipeCrossInDuration;

static void Mp5WipeCrossInProc(void)
{
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, mp5WipeCrossInDuration);
    HuPrcEnd();
}

static void Mp5WipeCrossIn(s16 duration)
{
    if (!WipeStatGet()) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSS, duration);
        return;
    }
    mp5WipeCrossInDuration = duration;
    HuPrcChildCreate(Mp5WipeCrossInProc, 100, 0x1000, 0, HuPrcCurrentGet());
}

static void WipeWait(void)
{
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
}

// MP5 can read a camera's pos/up/target back; MP4 keeps the same fields in Hu3DCamera.
static void Mp5CameraPosGet(s32 cameraBit, HuVecF *pos, HuVecF *up, HuVecF *target)
{
    s32 i;
    for (i = 0; i < HU3D_CAM_MAX; i++) {
        if (cameraBit & (1 << i)) {
            *pos = Hu3DCamera[i].pos;
            *up = Hu3DCamera[i].up;
            *target = Hu3DCamera[i].target;
            return;
        }
    }
}

// MP5 keeps a shadow per camera; MP4 has one shadow shared by every camera.
static void Hu3DShadowMultiCreate(float fov, float nnear, float ffar, s16 cameraBit)
{
    (void)cameraBit;
    Hu3DShadowCreate(fov, nnear, ffar);
}

static void Hu3DShadowMultiTPLvlSet(float tpLvl, s16 cameraBit)
{
    (void)cameraBit;
    Hu3DShadowTPLvlSet(tpLvl);
}

static void Hu3DShadowMultiPosSet(HuVecF *pos, HuVecF *up, HuVecF *target, s16 cameraBit)
{
    (void)cameraBit;
    Hu3DShadowPosSet(pos, up, target);
}

// ---- Characters ------------------------------------------------------------------------------------------
// MP4 order: Mario, Luigi, Peach, Yoshi, Wario, DK, Daisy, Waluigi. MP5 has all but DK, so those seven use
// MP5's own motions (same skeletons as MP4's models); DK falls back to an MP4 motion.

static const s32 mp5CharDir[8] = { DATADIR_MP5_MARIO, DATADIR_MP5_LUIGI, DATADIR_MP5_PEACH, DATADIR_MP5_YOSHI,
    DATADIR_MP5_WARIO, -1, DATADIR_MP5_DAISY, DATADIR_MP5_WALUIGI };
static const s32 mp5CharMotDir[8] = { DATADIR_MP5_MARIOMOT, DATADIR_MP5_LUIGIMOT, DATADIR_MP5_PEACHMOT,
    DATADIR_MP5_YOSHIMOT, DATADIR_MP5_WARIOMOT, -1, DATADIR_MP5_DAISYMOT, DATADIR_MP5_WALUIGIMOT };

static BOOL Mp5CharHasMotions(s16 charNo)
{
    return charNo >= 0 && charNo < 8 && mp5CharMotDir[charNo] >= 0;
}

// MP5 character motions also animate the eye texture through attribute tracks that name the attribute by
// its index in MP5's model. MP4's models number their attributes differently (Yoshi's index 1 is not his
// eyes), so those tracks would scramble other textures; MP4's character code animates the eyes itself.
// The joints match MP4's (same names and rest positions), so the transform tracks are kept.
static void Mp5MotionStripAttrTracks(s16 motId)
{
    HSFMOTION *motion;
    s32 i;
    if (motId < 0 || Hu3DMotion[motId].hsf == NULL) {
        return;
    }
    motion = Hu3DMotion[motId].hsf->motion;
    for (i = 0; i < motion->numTracks; i++) {
        if (motion->track[i].type == HSF_TRACK_ATTRIBUTE) {
            motion->track[i].type = 0; // ignored by the motion code
        }
    }
}

// A character motion: MP5's <char>mot.bin entry `mp5MotNo` (or, with `inCharArchive`, <char>.bin entry), or
// for DK the MP4 motion `mp4MotNo` (an index into MP4's <char>mot.bin).
static s16 Mp5CharMotionCreate(s16 charNo, s32 mp5MotNo, BOOL inCharArchive, s32 mp4MotNo)
{
    s16 motId;
    if (!Mp5CharHasMotions(charNo)) {
        return CharMotionCreate(charNo, DATA_MAKE_NUM(DATADIR_MARIOMOT, mp4MotNo));
    }
    motId = CharMotionCreate(charNo, DATA_MAKE_NUM(inCharArchive ? mp5CharDir[charNo] : mp5CharMotDir[charNo], mp5MotNo));
    Mp5MotionStripAttrTracks(motId);
    return motId;
}

// The MP4 motion (index into <char>mot.bin) that is the same animation as MP5's <char>mot.bin entry, or -1.
// generated by tools/mp5/dkmot.py: 22 of 146 mapped
static const s16 mp5ToMp4MotTbl[146] = {
    0, 1, 2, 5, 6, 7, 23, 24, 8, 9, 10, -1, -1, 53, 54, -1,
    -1, -1, -1, -1, -1, 19, 21, 22, 25, 26, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 73, -1,
    76, 114, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1,
};

// The same from an MP5 data number as MP5 code passes it to CharMotionCreate: an entry of <char>mot.bin, or
// with the Mario archive's directory, of <char>.bin. DK gets the matching MP4 motion when there is one, else
// `mp4MotNo`.
static s16 Mp5CharMotionCreateData(s16 charNo, u32 dataNum, s32 mp4MotNo)
{
    BOOL inCharArchive = (s32)(dataNum & ~0xFFFF) == DATADIR_MP5_MARIO;
    u32 no = dataNum & 0xFFFF;
    if (!inCharArchive && no < sizeof(mp5ToMp4MotTbl) / sizeof(mp5ToMp4MotTbl[0]) && mp5ToMp4MotTbl[no] >= 0) {
        mp4MotNo = mp5ToMp4MotTbl[no];
    }
    return Mp5CharMotionCreate(charNo, no, inCharArchive, mp4MotNo);
}

// MP5's CharModelMotListCreate: the model plus every motion of a 0-terminated list of MP5 data numbers.
// DK (no MP5 motions) gets the matching MP4 motions (idle for those MP4 lacks).
static s16 CharModelMotListCreate(s16 charNo, s16 model, u32 *motDataNum, s16 *motId)
{
    s16 modelId = CharModelCreate(charNo, model);
    s16 no;
    for (no = 0; motDataNum[no] != 0; no++) {
        motId[no] = Mp5CharMotionCreateData(charNo, motDataNum[no], 0);
    }
    CharMotionDataClose(charNo);
    return modelId;
}

// MP5 charman calls MP4 doesn't have: thin wrappers on the character's model.
static void CharModelAttrSet(s16 charNo, u32 attr)
{
    Hu3DModelAttrSet(CharModelIdGet(charNo), attr);
}

static void CharModelAttrReset(s16 charNo, u32 attr)
{
    Hu3DModelAttrReset(CharModelIdGet(charNo), attr);
}

static void CharMotionStartEndSet(s16 charNo, float start, float end)
{
    Hu3DMotionStartEndSet(CharModelIdGet(charNo), start, end);
}

static s16 Mp5CharNo(s16 charNo);

// MP5's charHeightTbl, by MP4 character (DK uses Wario's row like the other tables).
static float CharModelHeightGet(s16 charNo)
{
    static const float height[7] = { 150, 170, 188, 169, 164, 180, 210 };
    return height[Mp5CharNo(charNo)];
}

// Index of `charNo` (MP4 numbering) in MP5's per-character tables: DK, who isn't in MP5, borrows Wario's row.
static s16 Mp5CharNo(s16 charNo)
{
    static const s16 tbl[8] = { 0, 1, 2, 3, 4, 4, 5, 6 };
    return (charNo >= 0 && charNo < 8) ? tbl[charNo] : 0;
}

// ---- Minigame timer (MgTimer*): MP5's frame counter, shown with MP4's MGSeq countdown ----------------

#define MGTIMER_TYPE_NORMAL 0
#define MGTIMER_MODE_OFF 0
#define MGTIMER_MODE_ON 1
#define MGTIMER_OFFTYPE_NONE 0
#define MGTIMER_OFFTYPE_FADEOUT 1

typedef struct Mp5MgTimer {
    s32 mode;
    s32 maxTime, endTime, speed, time; // frames
    BOOL stopF; // MP5 code sets it to freeze the timer
    s16 seqId;
    HUPROCESS *proc;
    s16 posX, posY; // display position (-1: MGSeq's default, top centre)
} MGTIMER;

static void Mp5MgTimerMain(void)
{
    MGTIMER *timer = (MGTIMER *)HuPrcCurrentGet()->property;
    while (TRUE) {
        if (timer->mode == MGTIMER_MODE_ON && !timer->stopF && timer->time != timer->endTime) {
            timer->time += timer->speed;
            if (timer->seqId >= 0) {
                MGSeqParamSet(timer->seqId, 1, (timer->time + 59) / 60);
            }
            if (timer->time == timer->endTime) {
                timer->mode = MGTIMER_MODE_OFF;
                if (timer->seqId >= 0) {
                    MGSeqParamSet(timer->seqId, 2, -1);
                    timer->seqId = -1;
                }
            }
        }
        if (timer->stopF && timer->seqId >= 0) {
            // stopped early (MP5 then fades the display out)
            MGSeqParamSet(timer->seqId, 2, -1);
            timer->seqId = -1;
        }
        HuPrcVSleep();
    }
}

static MGTIMER *MgTimerCreate(s32 type)
{
    MGTIMER *timer = (MGTIMER *)HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(MGTIMER), MEMORY_DEFAULT_NUM);
    (void)type;
    memset(timer, 0, sizeof(*timer));
    timer->seqId = -1;
    timer->posX = timer->posY = -1;
    timer->proc = HuPrcChildCreate(Mp5MgTimerMain, 100, 0x1000, 0, HuPrcCurrentGet());
    timer->proc->property = timer;
    return timer;
}

static void MgTimerParamSet(MGTIMER *timer, s32 maxTime, s32 endTime, s32 recordTime)
{
    (void)recordTime;
    timer->maxTime = timer->time = maxTime;
    timer->endTime = endTime;
    timer->speed = (maxTime == endTime) ? 0 : ((maxTime > endTime) ? -1 : 1);
}

static void MgTimerModeOnSet(MGTIMER *timer, s32 offType)
{
    (void)offType;
    timer->mode = MGTIMER_MODE_ON;
    if (timer->seqId < 0) {
        timer->seqId = MGSeqCreate(1, (timer->time + 59) / 60, timer->posX, timer->posY);
    }
}

static void MgTimerPosSet(MGTIMER *timer, float posX, float posY)
{
    timer->posX = (s16)posX;
    timer->posY = (s16)posY;
    if (timer->seqId >= 0) {
        MGSeqPosSet(timer->seqId, posX, posY);
    }
}

static void MgTimerKill(MGTIMER *timer)
{
    HuPrcKill(timer->proc);
    if (timer->seqId >= 0) {
        MGSeqParamSet(timer->seqId, 2, -1);
    }
    HuMemDirectFree(timer);
}

static BOOL MgTimerDoneCheck(MGTIMER *timer)
{
    return timer->endTime == timer->time;
}

static s32 MgTimerValueGet(MGTIMER *timer)
{
    return timer->time;
}

// ---- Score window (MgScoreWin*): a dark translucent panel ---------------------------------------------

static ANIMDATA *mp5ScoreWinAnim;

static s16 MgScoreWinCreate(s16 sizeX, s16 sizeY)
{
    s16 gid;
    s16 sprid;
    if (!mp5ScoreWinAnim) {
        u8 *bmp;
        s32 i;
        mp5ScoreWinAnim = HuSprAnimMake(8, 4, ANIM_BMP_I8);
        bmp = mp5ScoreWinAnim->bmp->data = HuMemDirectMallocNum(HEAP_SYSTEM, 8 * 4, MEMORY_DEFAULT_NUM);
        for (i = 0; i < 8 * 4; i++) {
            bmp[i] = 0xFF;
        }
        DCStoreRangeNoSync(bmp, 8 * 4);
    }
    gid = HuSprGrpCreate(1);
    sprid = HuSprCreate(mp5ScoreWinAnim, 100, 0);
    HuSprGrpMemberSet(gid, 0, sprid);
    HuSprScaleSet(gid, 0, sizeX / 8.0f, sizeY / 4.0f);
    HuSprColorSet(gid, 0, 64, 64, 64);
    HuSprTPLvlSet(gid, 0, 0.7f);
    return gid;
}

static void MgScoreWinTPLvlSet(s16 gid, float tpLvl)
{
    HuSprTPLvlSet(gid, 0, tpLvl);
}

static void MgScoreWinPosSet(s16 gid, float posX, float posY)
{
    HuSprGrpPosSet(gid, posX, posY);
}

static void MgScoreWinDispSet(s16 gid, BOOL disp)
{
    if (disp) {
        HuSprAttrReset(gid, 0, HUSPR_ATTR_DISPOFF);
    }
    else {
        HuSprAttrSet(gid, 0, HUSPR_ATTR_DISPOFF);
    }
}

#include "REL/mp5seqman.h"

#endif
