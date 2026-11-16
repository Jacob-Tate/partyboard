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
#include "game/memory.h"
#include "game/minigame_seq.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include <math.h>

// MP5 code names parameters near/far; windows.h (pulled in on Windows) defines both as macros.
#undef near
#undef far

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

// Jingles are MP4 streams: 1 = win, 4 = draw.
#define MP5_JINGLE_WIN 1
#define MP5_JINGLE_DRAW 4

// Voice panning has no MP4 counterpart.
#define CharModelVoicePanSet(charNo, pan) ((void)(charNo), (void)(pan))

static void Mp5WipeWhite(s16 mode, s16 duration)
{
    WipeColorSet(255, 255, 255);
    WipeCreate(mode, WIPE_TYPE_NORMAL, duration);
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

// Index of `charNo` (MP4 numbering) in MP5's per-character tables: DK, who isn't in MP5, borrows Wario's row.
static s16 Mp5CharNo(s16 charNo)
{
    static const s16 tbl[8] = { 0, 1, 2, 3, 4, 4, 5, 6 };
    return (charNo >= 0 && charNo < 8) ? tbl[charNo] : 0;
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

#endif
