// MP5 m506 (Leaf Leap), generated from its m2c draft by tools/mp5/ports/m506Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m506Dll (Leaf Leap, 4 players; tools/mp5/decomp.py m506Dll --types tools/mp5/types/m506Dll.h)
// Written from MP5's decomp header (include/REL/m506Dll.h, M506_WORK / M506_PLAYER_WORK / M506_YCAMERA ...) and from the
// draft for the part of the REL the decomp doesn't cover (object.c = the flow work M506_FLOW, player.c).
// Offsets are GameCube's; ids are s16.
// objdata: M506_PLAYER_WORK
// objdata ObjectSetup M506Exit M506FlowEndWatch M506MainUpdate M506FlowModeEnd M506MainCreate: M506_WORK
// objexpr M506MainObj: M506_WORK

#ifdef M2CTX
// MP5's MGSCORE (game/mg/score.h), which the context headers don't pull in
typedef struct MgScore_s {
    int mode;
    int prevMode;
    HuVecF pos;
    HuVecF scale;
    HuVecF digitScale;
    HuVecF unitOfs;
    float zRot;
    float digitW;
    float tpLvl;
    u8 r;
    u8 g;
    u8 b;
    int value;
    int maxDigit;
    s32 *sprId;
    s16 grpId;
    s16 prio;
    BOOL dispF;
    BOOL validF;
    BOOL dispLeadZeroF;
    void *digitAnim;
    HUPROCESS *proc;
} MGSCORE;
#endif

typedef struct M506Work { // 0x780: OMOBJ::data of M506MainObj
    s16 stageMdlId; // 0x0
    s16 bgMdlId[2]; // 0x2
    s16 mameMdlId[4][60]; // 0x6
    s16 mameVineMdlId[4][31]; // 0x1E6
    s16 mameSmallMdlId[4][10]; // 0x2DE
    s16 mameSpiralMdlId[4][10]; // 0x32E
    s16 kumoMdlId[4]; // 0x37E
    s16 auroraMdlId; // 0x386
    s16 seedMdlId; // 0x388
    s16 moundMdlId; // 0x38A
    s16 windmillMdlId; // 0x38C
    s16 starMdlId[2]; // 0x38E
    s16 rocketMdlId; // 0x392
    s16 moonMdlId; // 0x394
    s16 noko2MdlId; // 0x396
    s16 starfighterMdlId[4]; // 0x398
    s16 stageBorderMdlId; // 0x3A0
    s16 sunMdlId; // 0x3A2
    s16 kumo2MdlId[4]; // 0x3A4
    s16 smokeMdlId[3]; // 0x3AC
    s16 mameShadowMdlId[4]; // 0x3B2
    s16 glowShadowMdlId; // 0x3BA
    s16 mameVineShadowMdlId; // 0x3BC
    s16 unk3BE;
    s16 moundMotId; // 0x3C0
    s16 windmillMotId; // 0x3C2
    s16 mameShadowTexScrId[4]; // 0x3C4
    u8 mameSide[4][60]; // 0x3CC
    u8 mameSmallFlag[4][10]; // 0x4BC
    u8 mameSpiralFlag[4][10]; // 0x4E4
    f32 mameVinePosY[4]; // 0x50C
    f32 mameVineRotY[4]; // 0x51C
    s16 mameVineTime[4]; // 0x52C
    s16 mameEnterTime[4]; // 0x534
    s16 unk53C[4]; // 0x53C
    s16 mameMissTime[4]; // 0x544
    f32 mameSpiralPosY[4][10]; // 0x54C
    f32 mameSmallPosY[4][10]; // 0x5EC
    s16 mameSpiralTime[4][10]; // 0x68C
    s16 mameSmallTime[4][10]; // 0x6DC
    f32 kumoDir[4]; // 0x72C
    f32 kumoPosX[4]; // 0x73C
    f32 kumoAngle[4]; // 0x74C
    s16 starTime[2]; // 0x75C
    f32 noko2Time; // 0x760
    f32 noko2Angle; // 0x764
    u16 noko2CamBit; // 0x768
    u16 rocketCamBit; // 0x76A
    u32 recordIdx; // 0x76C
    MGTIMER *timer; // 0x770
    s16 gameMesId; // 0x774
    u32 recordVal; // 0x778
    s32 gameMesDelay; // 0x77C
} M506_WORK;

typedef struct M506PlayerWork { // 0x60: OMOBJ::data of a player
    s32 no; // 0x0
    s32 charNo; // 0x4
    s32 padNo; // 0x8
    s32 unkC;
    s32 unk10;
    s32 newHeight; // 0x14
    s32 height; // 0x18
    s32 prevHeight; // 0x1C
    Vec pos; // 0x20
    s32 jumpTicks; // 0x2C
    s16 jumpF; // 0x30
    s16 upJumpF; // 0x32
    s16 nextJumpF; // 0x34
    s16 curDir; // 0x36
    s16 prevDir; // 0x38
    s16 fallTime; // 0x3A
    s16 prevFallTime; // 0x3C
    s16 fallLevel; // 0x3E
    s16 mode; // 0x40
    s16 modeTimer; // 0x42
    s16 jumpTimer; // 0x44
    s16 motId; // 0x46
    f32 motTime; // 0x48
    f32 motMaxTime; // 0x4C
    s16 playerType; // 0x50
    s16 comDif; // 0x52
    s16 comMode; // 0x54
    s16 comDelayMax; // 0x56
    s16 comDelay; // 0x58
    s16 comRecoverF; // 0x5A
    s16 comMoveChance; // 0x5C
    s16 comMoveChanceMax; // 0x5E
} M506_PLAYER_WORK;

typedef struct M506YCamera { // 0x74
    s32 bit; // 0x0
    Vec center; // 0x4
    Vec target; // 0x10
    Vec upDir; // 0x1C
    Vec up; // 0x28
    Vec dir; // 0x34
    Vec hvr; // 0x40
    f32 unk4C;
    Vec pos; // 0x50
    f32 aspect; // 0x5C
    f32 viewportX; // 0x60
    f32 viewportW; // 0x64
    f32 scissorX; // 0x68
    f32 scissorW; // 0x6C
    f32 fov; // 0x70
} M506_YCAMERA;

typedef struct M506YCameraWork { // 0x1E0
    M506_YCAMERA camera[4]; // 0x0
    f32 splitTime; // 0x1D0
    s32 unk1D4;
    s16 splitSprId[4]; // 0x1D8
} M506_YCAMERA_WORK;

typedef struct M506YLight { // 0x50
    s16 lightId; // 0x0
    s16 pad2;
    Vec hvr; // 0x4
    Vec unk10;
    Vec target; // 0x1C
    Vec center; // 0x28
    Vec pos; // 0x34
    Vec dir; // 0x40
    GXColor color; // 0x4C
} M506_YLIGHT;

typedef struct M506YShadow { // 0x5C
    s32 bit; // 0x0
    f32 tpLvl; // 0x4
    Vec hvr; // 0x8
    Vec center; // 0x14
    Vec pos; // 0x20
    Vec target; // 0x2C
    Vec upDir; // 0x38
    Vec up; // 0x44
    Vec forward; // 0x50
} M506_YSHADOW;

typedef struct M506YShadowWork { // 0x1C8
    M506_YSHADOW shadow[4]; // 0x0
    u8 unk170[0x58];
} M506_YSHADOW_WORK;

typedef struct M506Stop { // 0x14: a player's end-of-game camera ride up to the height reached
    s32 state; // 0x0
    f32 target; // 0x4
    f32 speed; // 0x8
    f32 accel; // 0xC
    f32 drag; // 0x10
} M506_STOP;

typedef struct M506Rocket { // 0x28
    Vec pos; // 0x0
    Vec rot; // 0xC
    f32 speed; // 0x18
    s32 state; // 0x1C
    s32 start; // 0x20
    s32 armed; // 0x24
} M506_ROCKET;

typedef struct M506Starfighter { // 0x24
    Vec pos; // 0x0
    Vec rot; // 0xC
    f32 speed; // 0x18
    s32 state; // 0x1C
    s32 start; // 0x20
} M506_STARFIGHTER;

typedef struct M506Flow { // 0x218: bss M506Flow
    M506_WORK *work0; // 0x0
    M506_WORK *work; // 0x4
    OMOBJ *playerObj[4]; // 0x8
    M506_PLAYER_WORK *player[4]; // 0x18
    s32 step; // 0x28
    s32 unk2C;
    s32 unk30;
    f32 time; // 0x34
    s32 humanWinner; // 0x38
    s32 winnerNum; // 0x3C
    s32 prevRecord; // 0x40
    s32 bestHeight; // 0x44
    s8 score[4]; // 0x48
    s8 charStep[4]; // 0x4C
    s8 winOrder[4]; // 0x50
    s8 winFlag[4]; // 0x54
    s8 winMot[4]; // 0x58
    s8 winMotStep[4]; // 0x5C
    M506_STOP stop[4]; // 0x60
    u8 padB0[0x20];
    s8 scoreShow[4]; // 0xD0
    u8 padD4[8];
    s16 recordSprId; // 0xDC
    u8 padDE[8];
    s16 recordWinId; // 0xE6
    MGSCORE *recordScore; // 0xE8
    MGSCORE *scoreDisp[4]; // 0xEC
    f32 seedY; // 0xFC
    f32 seedRot; // 0x100
    f32 moundY; // 0x104
    f32 scrollY; // 0x108
    f32 scrollRot; // 0x10C
    f32 scrollScale; // 0x110
    f32 mameRotX; // 0x114
    f32 mameScale; // 0x118
    f32 playerRot; // 0x11C
    f32 seedSpeed; // 0x120
    f32 unk124;
    s32 scrollStep; // 0x128
    s32 endF; // 0x12C
    M506_ROCKET rocket; // 0x130
    s32 unk158;
    M506_STARFIGHTER fighter[4]; // 0x15C
    s16 shadowTexScrId; // 0x1EC
    s16 pad1EE;
    f32 shadowScroll; // 0x1F0
    s16 particleMdlId; // 0x1F4
    s16 gameMesId; // 0x1F6
    s16 unk1F8[4]; // 0x1F8
    s32 unk200;
    Vec winPos; // 0x204
    s32 seedState; // 0x210
    HUPROCESS *seedProc; // 0x214
} M506_FLOW;

typedef struct M506CamView { // 0x34
    f32 rate; // 0x0
    f32 from[6]; // 0x4: hvr.x, hvr.y, hvr.z (dist), pos.x, pos.y, pos.z
    f32 to[6]; // 0x1C
} M506_CAMVIEW;

typedef struct M506Pos { // 4
    s16 x;
    s16 y;
} M506_POS;

typedef struct M506MotShift { // 0xC
    f32 mot;
    f32 start;
    f32 speed;
} M506_MOTSHIFT;

typedef struct M506LookUp { // 8
    f32 from;
    f32 to;
} M506_LOOKUP;



void ObjectSetup(void);
void M506Exit(omObjData *obj);
s32 M506ExitCheck(omObjData *obj);
void M506Update(omObjData *obj);
void M506Create(M506_WORK *work);
void M506TimerCreate(M506_WORK *work);
s32 M506FlowUpdate(M506_WORK *work);
void M506MameUpdate(M506_PLAYER_WORK *player);
void M506MameModeEnter(M506_PLAYER_WORK *player);
void M506MameModeMiss(M506_PLAYER_WORK *player);
void M506MameModeJump(M506_PLAYER_WORK *player);
void M506ModelUpdate(M506_WORK *work);
void M506MainCreate(omObjData *obj);
void M506FlowEndWatch(omObjData *obj);
void M506ObjShadowMapSet(s32 no, s32 mame);
void M506ObjShadowMapReset(s32 no, s32 from, s32 to);
void M506MainUpdate(omObjData *obj);
void M506ObjInit(M506_FLOW *flow);
s32 M506FlowModeStart(M506_FLOW *flow);
void M506FlowModeStartSetup(M506_FLOW *flow);
void M506FlowMameSetup(M506_FLOW *flow);
s32 M506ShadowScrollInit(M506_FLOW *flow);
void M506FlowP1Update(M506_FLOW *flow);
void M506FlowModeEnd(omObjData *obj);
void M506FlowModeEndSetup(M506_FLOW *flow);
s32 M506FlowStopCheck(M506_FLOW *flow);
s32 M506FlowResult(M506_FLOW *flow);
void M506ScoreCreate(M506_FLOW *flow);
void M506ScoreDispUpdate(M506_FLOW *flow);
void M506MameShadowOff(M506_FLOW *flow);
void M506MameShadowOn(M506_FLOW *flow);
void M506MameShadowScrollOn(M506_FLOW *flow);
void M506MameShadowScrollExec(M506_FLOW *flow);
void M506ParticleCreate(M506_FLOW *flow);
void M506ParticleUpdate(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void M506ParticleKill(M506_FLOW *flow);
void M506RocketInit(M506_FLOW *flow);
void M506RocketUpdate(void);
s32 M506RocketModelUpdate(M506_FLOW *flow);
void M506RocketMove(M506_FLOW *flow);
void M506StarfighterStart(M506_FLOW *flow);
void M506StarfighterUpdate(void);
void M506StarfighterModelUpdate(M506_STARFIGHTER *fighter, s16 mdlId);
void M506RecordCreate(M506_FLOW *flow);
void M506RecordSet(M506_FLOW *flow);
void M506RecordBlink(M506_FLOW *flow);
void M506RecordBlinkInit(void);
void M506YCameraInit(void);
void M506YCameraClose(void);
void M506YCameraUpdate(void);
void M506YCameraProjUpdate(void);
void M506YCameraViewUpdate(void);
void M506YCameraSplitCreate(void);
void M506YCameraSplitKill(void);
void M506YLightInit(void);
void M506YLightClose(void);
void M506YLightUpdate(void);
void M506YShadowInit(void);
void M506YShadowClose(void);
void M506YShadowPosUpdate(void);
void M506YShadowUpdate(void);
void M506YCameraViewSet(s32 no, s32 view);
s32 M506YCameraViewLerp(s32 no, s32 view);
s32 M506PointLerp(f32 *value, f32 start, f32 end, f32 rate);
void M506MakeRotMtx(Mtx mtx, Vec *rot);
void M506SeedUpdate(void);
void M506PlayerCreate(omObjData *obj);
void M506PlayerUpdate(omObjData *obj);
void M506PlayerMotionSet(omObjData *obj, s16 motNo);
s32 M506PlayerInputRead(omObjData *obj);
s32 M506PlayerModeNormalJump(omObjData *obj);
s32 M506PlayerModeUpJump(omObjData *obj);
s32 M506PlayerModeSideJump(omObjData *obj);
s32 M506PlayerModeFall(omObjData *obj);
s16 M506ComInputDelayGet(omObjData *obj);
s16 M506ComInputCheck(omObjData *obj);

struct _struct_MameSideData_0x3 {
    /* 0x0 */ u8 unk0;                              /* inferred */
    /* 0x1 */ u8 unk1;                              /* inferred */
    /* 0x2 */ u8 unk2;                              /* inferred */
};                                                  /* size = 0x3 */

s32 M506ModelFile[0x1A] = {
    DATA_MAKE_NUM(DATADIR_MP5_M506, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M506, 7),
};
s32 M506MotionFile[2] = { DATA_MAKE_NUM(DATADIR_MP5_M506, 25), DATA_MAKE_NUM(DATADIR_MP5_M506, 26) };
static struct _struct_MameSideData_0x3 MameSideData[6] = {
    { 0, 0, 1 },
    { 0, 1, 0 },
    { 0, 1, 1 },
    { 1, 0, 0 },
    { 1, 0, 1 },
    { 1, 1, 0 },
};
Vec StarPosTbl[2] = { { 210.0f, 12500.0f, -3700.0f }, { -300.0f, 14000.0f, -3000.0f } };
Vec KumoPosTbl[4] = {
    { 300.0f, 1700.0f, -2100.0f },
    { 220.0f, 2700.0f, -1500.0f },
    { -100.0f, 3700.0f, -1500.0f },
    { 270.0f, 4700.0f, -2200.0f },
};
s16 StarMaxTime[3] = { 0x64, 0xAA, 0x96 };
s16 KumoDirTbl[4] = { -1, 1, 1, -1 };
static s8 lbl_1_data_F0[0x10] = {
    0x49,
    0x38,
    0x6D,
    0x35,
    0x30,
    0x36,
    0x61,
    0x6C,
    0x6F,
    0x72,
    0x61,
    0x7A,
    0,
    0,
    0,
    0,
};
omObjData *M506UpdateObj;
omObjData **M506PlayerObj;
omObjData *M506MainObj;
HUPROCESS *M506ObjMan;
static s32 streamNo;
u32 LookUpRotLockFlag[0xD] = {
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
    0x200,
};
M506_LOOKUP LookUpRotTbl[0xD] = {
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
    { 100.0f, 85.0f },
    { 88.0f, 43.0f },
    { 84.0f, 52.0f },
    { 100.0f, 75.0f },
    { 72.0f, 27.0f },
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
    { 180.0f, 135.0f },
};
M506_CAMVIEW YCameraView[3] = {
    {
        0.0f,
        { 90.0f, 12.0f, 2150.0f, 0.0f, 300.0f, 0.0f },
        { 90.0f, 12.0f, 2150.0f, 0.0f, 300.0f, 0.0f },
    },
    {
        120.0f,
        { 73.0f, 0.0f, 300.0f, 0.0f, 60.0f, 0.0f },
        { 90.0f, 0.0f, 1500.0f, 0.0f, 150.0f, 0.0f },
    },
    {
        120.0f,
        { 90.0f, 0.0f, 1500.0f, 0.0f, 150.0f, 0.0f },
        { 90.0f, 12.0f, 2150.0f, 0.0f, 300.0f, 0.0f },
    },
};
M506_POS ScorePos[0x10] = {
    { 0x3C, 0xA0 },
    { 0x4C, 0xA0 },
    { 0x5C, 0xA0 },
    { 0xC8, 0xA0 },
    { 0xD8, 0xA0 },
    { 0xE8, 0xA0 },
    { 0x158, 0xA0 },
    { 0x168, 0xA0 },
    { 0x178, 0xA0 },
    { 0x1E8, 0xA0 },
    { 0x1F8, 0xA0 },
    { 0x208, 0xA0 },
    { 0x78, 0xA0 },
    { 0x104, 0xA0 },
    { 0x194, 0xA0 },
    { 0x224, 0xA0 },
};
static s8 lbl_1_data_298[0xC] = { 0x73, 0x6B, 0x65, 0x5F, 0x68, 0x65, 0x61, 0x64, 0, 0, 0, 0 };
static const f32 rotTbl_700[6] = { 0.0f, 90.0f, 15.0f, 30.0f, 10.0f, 45.0f };
static f32 recordScale_725 = 1.0f;
static Vec up_800 = { 0.0f, 1.0f, 0.0f };
static Vec up_1000 = { 0.0f, 1.0f, 0.0f };
s32 lbl_1_bss_18;
static f32 ScrollHeight;
static f32 ScrollAngle;
static s32 MameShadowF;
s8 lbl_1_bss_28;
static u8 RecordInitF;
static s32 SeedInitF;
static f32 LookUpCurrRot;
static s32 StartFXFlag;
static f32 StartFXTime;
static f32 FlowTime;
M506_YSHADOW_WORK *M506YShadow;
M506_YLIGHT *M506YLight;
M506_YCAMERA_WORK *M506YCamera;
M506_FLOW M506Flow;
s16 PlayerModeNoTbl[4] = { 0, 0, 0, 0 };
s32 PlayerMotionTbl[0xD][7] = {
    { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 49), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 13) },
    { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 13) },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 13 */ },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 13 */ },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */ },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */ },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */ },
    { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */ },
};
s16 ComMaxDelayTbl[4][5] = {
    { 0x28, 0x34, 0x19, 8, 0x28 },
    { 0xF, 0x1C, 0x4B, 7, 0xF },
    { 6, 0xF, 0x55, 4, 7 },
    { 4, 9, 0x5A, 2, 6 },
};
s32 FallStartFXTbl[4] = { 0x66F, 0x670, 0x671, 0x672 };
s32 FallEndFXTbl[4] = { 0x673, 0x674, 0x675, 0x676 };
s32 CharFallFXTbl[0xD] = {
    0x1F9,
    0x1E5,
    0x25D,
    0x2AD,
    0x285,
    0x1BD,
    0x299,
    0x1D1,
    0x271,
    0x235,
    0x249,
    0x221,
    0x20D,
};
s32 PlayerPanTbl[4] = { 0x28, 0x38, 0x48, 0x58 };
s32 (*PlayerModeTbl[4])(omObjData *) = {
    M506PlayerModeNormalJump,
    M506PlayerModeUpJump,
    M506PlayerModeSideJump,
    M506PlayerModeFall,
};
f32 MotSpeedTbl[0xA] = { 1.0f, 0.75f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
M506_MOTSHIFT MotShiftTbl[4] = {
    { 0.0f, 0.0f, 3.0f },
    { 3.0f, 0.0f, 5.0f },
    { 1.0f, 0.0f, 8.0f },
    { 2.0f, 0.0f, 12.0f },
};
f32 JumpUpSpeedTbl[0xF] = {
    38.0f,
    36.0f,
    34.0f,
    32.0f,
    30.0f,
    28.0f,
    26.0f,
    24.0f,
    22.0f,
    20.0f,
    18.0f,
    16.0f,
    14.0f,
    12.0f,
    10.0f,
};
f32 JumpDownSpeedTbl[8] = { 0.0f, -2.0f, -4.0f, -6.0f, -9.0f, -11.0f, -13.0f, -15.0f };
f32 BounceUpSpeedTbl[7] = { 20.0f, 18.0f, 16.0f, 14.0f, 12.0f, 10.0f, 8.0f };
f32 BounceDownSpeedTbl[8] = { 0.0f, -8.0f, -10.0f, -12.0f, -14.0f, -16.0f, -18.0f, -20.0f };
s32 CharFallSeNo[4];
s32 FallEndSeNo[4];
s32 FallStartSeNo[4];
static s16 M506CameraBit[4] = { 1, 2, 4, 8 };       /* const */
static const f32 lbl_1_rodata_18[4] = { 90.0f, 170.0f, 390.0f, 470.0f };
static const f32 lbl_1_rodata_28[4] = { 200.0f, 280.0f, 500.0f, 580.0f };
static const f32 lbl_1_rodata_25C[2] = { -64.5f, 64.5f };
static const s16 lbl_1_rodata_280[4] = { 0x28, 0x38, 0x48, 0x58 };
static const f32 lbl_1_rodata_338[3] = { 144.0f, 288.0f, 432.0f };



void ObjectSetup(void) {
    omObjData *temp_r3;
    s32 var_r31;
    M506_WORK *temp_r29;

    M506ObjMan = omInitObjMan(0x200, 0x2000);
    omGameSysInit(M506ObjMan);
    M506YCameraInit();
    M506YLightInit();
    M506YShadowInit();
    M506MainObj = omAddObjEx(M506ObjMan, 0x65, 0U, 0U, -1, M506MainCreate);
    M506MainObj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M506_WORK), MEMORY_DEFAULT_NUM);
    temp_r29 = M506MainObj->data;
    omMakeGroupEx(M506ObjMan, 0U, 4U);
    M506PlayerObj = omGetGroupMemberListEx(M506ObjMan, 0);
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        temp_r3 = omAddObjEx(M506ObjMan, 0x64, 1U, 7U, 0, M506PlayerCreate);
        M506PlayerObj[var_r31] = temp_r3;
        temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M506_PLAYER_WORK), MEMORY_DEFAULT_NUM);
        temp_r3->work[0] = (u32) var_r31;
        var_r31 += 1;
        goto loop_2;
    }
    M506TimerCreate(temp_r29);
    M506MainObj->work[3] = 0;
    M506MainObj->work[2] = 0;
    Hu3DBGColorSet(0U, 0U, 0U);
    M506UpdateObj = omAddObjEx(M506ObjMan, 0x66, 0U, 0U, -1, M506Update);
}

void M506Exit(omObjData *obj) {
    M506_WORK *temp_r31;

    temp_r31 = obj->data;
    M506ModelUpdate((M506_WORK *) temp_r31);
    if (WipeCheckEnd() == 0) {
        HuAudAllStop();
        if ((s16) temp_r31->gameMesId >= 0) {
            GameMesKill(temp_r31->gameMesId);
        }
        Hu3DTexScrollAllKill();
        M506YShadowClose();
        M506YLightClose();
        M506YCameraClose();
        GameMesClose();
        MgTimerKill(temp_r31->timer);
        omOvlReturnEx(1, 1);
    }
}

s32 M506ExitCheck(omObjData *obj) {
    s32 var_r30;

    var_r30 = 0;
    if ((s16) omSysExitReq != 0) {
        obj->work[3] = 3;
        Mp5WipeWhite(2, 0x3C);
        HuAudFadeOut(0x3E8);
        obj->func = M506Exit;
        var_r30 = 1;
    }
    return var_r30;
}

void M506Update(omObjData *obj) {
    M506YCameraUpdate();
    M506YShadowUpdate();
}

void M506Create(M506_WORK *work) {
    f32 sp18[4];
    f32 sp8[4];
    s32 temp_r28_2;
    s32 temp_r28_3;
    s32 temp_r28_4;
    s32 temp_r28_5;
    s32 var_r27;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r29_4;
    s32 var_r29_5;
    s32 var_r29_6;
    s32 var_r29_7;
    s32 var_r29_8;
    s32 var_r29_9;
    s32 var_r30;
    s32 var_r30_10;
    s32 var_r30_11;
    s32 var_r30_12;
    s32 var_r30_13;
    s32 var_r30_14;
    s32 var_r30_15;
    s32 var_r30_16;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;
    s32 var_r30_7;
    s32 var_r30_8;
    s32 var_r30_9;
    u32 temp_r28;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r5;
    u32 temp_r5_2;
    u8 var_r28;
    u8 var_r28_2;

    sp18[0] = lbl_1_rodata_18[0];
    sp18[1] = lbl_1_rodata_18[1];
    sp18[2] = lbl_1_rodata_18[2];
    sp18[3] = lbl_1_rodata_18[3];
    sp8[0] = lbl_1_rodata_28[0];
    sp8[1] = lbl_1_rodata_28[1];
    sp8[2] = lbl_1_rodata_28[2];
    sp8[3] = lbl_1_rodata_28[3];
    work->recordIdx = (work->recordVal / 3) - 1;
    work->stageMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->stageMdlId, 1U);
    Hu3DModelAttrSet(work->stageMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->stageMdlId, 1);
    Hu3DModelPosSet(work->stageMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(work->stageMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->stageMdlId, 1U);
    Hu3DModelShadowMapSet(work->stageMdlId);
    work->stageBorderMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x12], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->stageBorderMdlId, 1U);
    Hu3DModelAttrSet(work->stageBorderMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->stageBorderMdlId, 1);
    Hu3DModelPosSet(work->stageBorderMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(work->stageBorderMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->stageBorderMdlId, 1U);
    Hu3DModelShadowMapSet(work->stageBorderMdlId);
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        work->bgMdlId[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[var_r30 + 0xE], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(work->bgMdlId[var_r30], 1U);
        Hu3DModelAttrSet(work->bgMdlId[var_r30], 0x40000002U);
        Hu3DModelLayerSet(work->bgMdlId[var_r30], 0);
        Hu3DModelPosSet(work->bgMdlId[var_r30], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(work->bgMdlId[var_r30], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(work->bgMdlId[var_r30], 1U);
        var_r30 += 1;
        goto loop_2;
    }
    work->windmillMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->windmillMdlId, 1U);
    Hu3DModelAttrSet(work->windmillMdlId, 0x40000001U);
    Hu3DModelLayerSet(work->windmillMdlId, 2);
    Hu3DModelPosSet(work->windmillMdlId, 265.0f, 336.0f, -2360.0f);
    Hu3DModelRotSet(work->windmillMdlId, 0.0f, -30.0f, 0.0f);
    Hu3DModelAttrReset(work->windmillMdlId, 1U);
    work->windmillMotId = Hu3DJointMotion(work->windmillMdlId, HuDataSelHeapReadNum(M506MotionFile[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(work->windmillMdlId, work->windmillMotId);
    work->rocketMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->rocketMdlId, 1U);
    Hu3DModelAttrSet(work->rocketMdlId, 0x40000001U);
    Hu3DModelLayerSet(work->rocketMdlId, 3);
    Hu3DModelPosSet(work->rocketMdlId, 0.0f, 14000.0f, -2500.0f);
    Hu3DModelRotSet(work->rocketMdlId, 0.0f, 0.0f, 0.0f);
    var_r29 = 0;
loop_8:
    if (var_r29 < 4) {
        if (var_r29 == 0) {
            work->starfighterMdlId[var_r29] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x10], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            work->starfighterMdlId[var_r29] = Hu3DModelLink(work->starfighterMdlId[0]);
        }
        Hu3DModelAttrSet(work->starfighterMdlId[var_r29], 1U);
        Hu3DModelAttrSet(work->starfighterMdlId[var_r29], 0x40000001U);
        Hu3DModelLayerSet(work->starfighterMdlId[var_r29], 3);
        Hu3DModelPosSet(work->starfighterMdlId[var_r29], 150.0f, 16000.0f, -2500.0f);
        Hu3DModelRotSet(work->starfighterMdlId[var_r29], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(work->starfighterMdlId[var_r29], (u16) M506CameraBit[var_r29]);
        Hu3DModelAttrReset(work->starfighterMdlId[var_r29], 1U);
        var_r29 += 1;
        goto loop_8;
    }
    work->moonMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->moonMdlId, 1U);
    Hu3DModelAttrSet(work->moonMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->moonMdlId, 2);
    Hu3DModelPosSet(work->moonMdlId, 0.0f, 17400.0f, -4000.0f);
    Hu3DModelRotSet(work->moonMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->moonMdlId, 1U);
    var_r29_2 = 0;
loop_21:
    if (var_r29_2 < 4) {
        work->mameVinePosY[var_r29_2] = 0.0f;
        work->mameVineRotY[var_r29_2] = 0.0f;
        if (var_r29_2 == 0) {
            work->mameVineMdlId[0][0] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            work->mameVineMdlId[var_r29_2][0] = Hu3DModelLink(work->mameVineMdlId[0][0]);
        }
        Hu3DModelAttrSet(work->mameVineMdlId[var_r29_2][0], 1U);
        Hu3DModelAttrSet(work->mameVineMdlId[var_r29_2][0], 0x40000002U);
        Hu3DModelLayerSet(work->mameVineMdlId[var_r29_2][0], 4);
        Hu3DModelPosSet(work->mameVineMdlId[var_r29_2][0], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(work->mameVineMdlId[var_r29_2][0], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(work->mameVineMdlId[var_r29_2][0], (u16) M506CameraBit[var_r29_2]);
        Hu3DModelAttrReset(work->mameVineMdlId[var_r29_2][0], 1U);
        var_r30_2 = 1;
loop_19:
        if (var_r30_2 < 0x1F) {
            if ((var_r29_2 == 0) && (var_r30_2 == 1)) {
                work->mameVineMdlId[0][1] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
            } else {
                work->mameVineMdlId[var_r29_2][var_r30_2] = Hu3DModelLink(work->mameVineMdlId[0][1]);
            }
            Hu3DModelAttrSet(work->mameVineMdlId[var_r29_2][var_r30_2], 1U);
            Hu3DModelAttrSet(work->mameVineMdlId[var_r29_2][var_r30_2], 0x40000002U);
            Hu3DModelLayerSet(work->mameVineMdlId[var_r29_2][var_r30_2], 4);
            Hu3DModelPosSet(work->mameVineMdlId[var_r29_2][var_r30_2], 0.0f, -600.0f * (f32) var_r30_2, 0.0f);
            Hu3DModelRotSet(work->mameVineMdlId[var_r29_2][var_r30_2], 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(work->mameVineMdlId[var_r29_2][var_r30_2], (u16) M506CameraBit[var_r29_2]);
            var_r30_2 += 1;
            goto loop_19;
        }
        Hu3DModelAttrReset(work->mameVineMdlId[var_r29_2][1], 1U);
        var_r29_2 += 1;
        goto loop_21;
    }
    var_r29_3 = 0;
loop_32:
    if (var_r29_3 < 4) {
        work->mameVineTime[var_r29_3] = 0;
        if (var_r29_3 == 0) {
            var_r30_3 = 0;
loop_26:
            if (var_r30_3 < 0x3C) {
                temp_r28 = rand8() / 43;
                work->mameSide[0][(var_r29_3 * 0x3C) + var_r30_3] = MameSideData[temp_r28].unk0;
                work->mameSide[var_r29_3][var_r30_3 + 1] = (u8) MameSideData[temp_r28].unk1;
                work->mameSide[var_r29_3][var_r30_3 + 2] = (u8) MameSideData[temp_r28].unk2;
                var_r30_3 += 3;
                goto loop_26;
            }
        } else {
            var_r30_4 = 0;
loop_30:
            if (var_r30_4 < 0x3C) {
                work->mameSide[0][(var_r29_3 * 0x3C) + var_r30_4] = work->mameSide[0][var_r30_4];
                work->mameSide[var_r29_3][var_r30_4 + 1] = (u8) work->mameSide[0][var_r30_4 + 1];
                work->mameSide[var_r29_3][var_r30_4 + 2] = (u8) work->mameSide[0][var_r30_4 + 2];
                var_r30_4 += 3;
                goto loop_30;
            }
        }
        var_r29_3 += 1;
        goto loop_32;
    }
    var_r29_4 = 0;
loop_46:
    if (var_r29_4 < 4) {
        if (var_r29_4 == 0) {
            var_r30_5 = 0;
loop_40:
            if (var_r30_5 < 0xA) {
                temp_r28_2 = (rand8() / 128) * 0x10;
                if (var_r30_5 == 0) {
                    var_r28 = temp_r28_2 | ((rand8() / 32) + 4);
                } else {
                    var_r28 = temp_r28_2 | (rand8() / 22);
                }
                work->mameSmallFlag[0][(var_r29_4 * 0xA) + var_r30_5] = var_r28;
                var_r30_5 += 1;
                goto loop_40;
            }
        } else {
            var_r30_6 = 0;
loop_44:
            if (var_r30_6 < 0xA) {
                work->mameSmallFlag[0][(var_r29_4 * 0xA) + var_r30_6] = work->mameSmallFlag[0][var_r30_6];
                var_r30_6 += 1;
                goto loop_44;
            }
        }
        var_r29_4 += 1;
        goto loop_46;
    }
    var_r29_5 = 0;
loop_60:
    if (var_r29_5 < 4) {
        if (var_r29_5 == 0) {
            var_r30_7 = 0;
loop_54:
            if (var_r30_7 < 0xA) {
                temp_r28_3 = (rand8() / 128) * 0x10;
                if (var_r30_7 == 0) {
                    var_r28_2 = temp_r28_3 | ((rand8() / 32) + 4);
                } else {
                    var_r28_2 = temp_r28_3 | (rand8() / 22);
                }
                work->mameSpiralFlag[0][(var_r29_5 * 0xA) + var_r30_7] = var_r28_2;
                var_r30_7 += 1;
                goto loop_54;
            }
        } else {
            var_r30_8 = 0;
loop_58:
            if (var_r30_8 < 0xA) {
                work->mameSpiralFlag[0][(var_r29_5 * 0xA) + var_r30_8] = work->mameSpiralFlag[0][var_r30_8];
                var_r30_8 += 1;
                goto loop_58;
            }
        }
        var_r29_5 += 1;
        goto loop_60;
    }
    var_r27 = -1;
    var_r29_6 = 0;
loop_78:
    if (var_r29_6 < 4) {
        var_r30_9 = 0;
loop_76:
        if (var_r30_9 < 0x3C) {
            if (((u32) var_r30_9 == (u32) work->recordIdx) && (0 == 0)) {
                if (var_r29_6 == 0) {
                    work->mameMdlId[0][work->recordIdx] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x14], MEMORY_DEFAULT_NUM, HEAP_DATA));
                } else {
                    work->mameMdlId[var_r29_6][var_r30_9] = Hu3DModelLink(work->mameMdlId[0][work->recordIdx]);
                }
            } else if ((var_r29_6 == 0) && (var_r27 < 0)) {
                var_r27 = var_r30_9;
                work->mameMdlId[0][var_r27] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
            } else {
                work->mameMdlId[var_r29_6][var_r30_9] = Hu3DModelLink(work->mameMdlId[0][var_r27]);
            }
            Hu3DModelAttrSet(work->mameMdlId[var_r29_6][var_r30_9], 1U);
            Hu3DModelAttrSet(work->mameMdlId[var_r29_6][var_r30_9], 0x40000002U);
            Hu3DModelLayerSet(work->mameMdlId[var_r29_6][var_r30_9], 4);
            Hu3DModelPosSet(work->mameMdlId[var_r29_6][var_r30_9], 0.0f, 300.0f + (300.0f * (f32) var_r30_9), 0.0f);
            if ((u8) work->mameSide[0][(var_r29_6 * 0x3C) + var_r30_9] != 0) {
                Hu3DModelRotSet(work->mameMdlId[var_r29_6][var_r30_9], 0.0f, 20.0f, 0.0f);
            } else {
                Hu3DModelRotSet(work->mameMdlId[var_r29_6][var_r30_9], 0.0f, -20.0f, 0.0f);
            }
            Hu3DModelCameraSet(work->mameMdlId[var_r29_6][var_r30_9], (u16) M506CameraBit[var_r29_6]);
            var_r30_9 += 1;
            goto loop_76;
        }
        Hu3DModelAttrReset(work->mameMdlId[var_r29_6][0], 1U);
        var_r29_6 += 1;
        goto loop_78;
    }
    work->seedMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->seedMdlId, 1U);
    Hu3DModelAttrSet(work->seedMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->seedMdlId, 4);
    Hu3DModelPosSet(work->seedMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(work->seedMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->seedMdlId, 1U);
    work->moundMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->moundMdlId, 1U);
    Hu3DModelAttrSet(work->moundMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->moundMdlId, 4);
    Hu3DModelPosSet(work->moundMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(work->moundMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->moundMdlId, 1U);
    work->moundMotId = Hu3DJointMotion(work->moundMdlId, HuDataSelHeapReadNum(M506MotionFile[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(work->moundMdlId, work->moundMotId);
    var_r30_10 = 0;
loop_84:
    if (var_r30_10 < 4) {
        work->mameShadowMdlId[var_r30_10] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x17], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(work->mameShadowMdlId[var_r30_10], 1U);
        Hu3DModelAttrSet(work->mameShadowMdlId[var_r30_10], 0x40000002U);
        Hu3DModelLayerSet(work->mameShadowMdlId[var_r30_10], 5);
        Hu3DModelPosSet(work->mameShadowMdlId[var_r30_10], 0.0f, 10.0f, 0.0f);
        Hu3DModelRotSet(work->mameShadowMdlId[var_r30_10], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(work->mameShadowMdlId[var_r30_10], (u16) M506CameraBit[var_r30_10]);
        work->mameShadowTexScrId[var_r30_10] = Hu3DTexScrollCreate(work->mameShadowMdlId[var_r30_10], "I8m506sdw01");
        if (var_r30_10 == 0) {
            Hu3DTexScrollPosSet(work->mameShadowTexScrId[var_r30_10], 0.0f, 0.0f, 0.0f);
        } else {
            Hu3DTexScrollPosSet(work->mameShadowTexScrId[var_r30_10], 0.0f, 0.4f, 0.0f);
            Hu3DModelAttrReset(work->mameShadowMdlId[var_r30_10], 0x40000002U);
            Hu3DModelAttrReset(work->mameShadowMdlId[var_r30_10], 1U);
        }
        var_r30_10 += 1;
        goto loop_84;
    }
    work->glowShadowMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x18], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->glowShadowMdlId, 1U);
    Hu3DModelAttrSet(work->glowShadowMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->glowShadowMdlId, 5);
    Hu3DModelPosSet(work->glowShadowMdlId, -135.0f, 10.0f, 400.0f);
    if ((u8) work->mameSide[0][0] != 0) {
        Hu3DModelRotSet(work->glowShadowMdlId, 0.0f, 50.0f, 180.0f);
    } else {
        Hu3DModelRotSet(work->glowShadowMdlId, 0.0f, 50.0f, 0.0f);
    }
    work->mameVineShadowMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x19], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->mameVineShadowMdlId, 1U);
    Hu3DModelAttrSet(work->mameVineShadowMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->mameVineShadowMdlId, 2);
    Hu3DModelPosSet(work->mameVineShadowMdlId, 0.0f, -5.0f, 0.0f);
    Hu3DModelRotSet(work->mameVineShadowMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->mameVineShadowMdlId, 1U);
    var_r30_11 = 0;
loop_93:
    if (var_r30_11 < 4) {
        if (var_r30_11 == 0) {
            work->kumoMdlId[var_r30_11] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            work->kumoMdlId[var_r30_11] = Hu3DModelLink(work->kumoMdlId[0]);
        }
        Hu3DModelAttrSet(work->kumoMdlId[var_r30_11], 1U);
        Hu3DModelAttrSet(work->kumoMdlId[var_r30_11], 0x40000002U);
        Hu3DModelLayerSet(work->kumoMdlId[var_r30_11], 3);
        Hu3DModelPosSetV(work->kumoMdlId[var_r30_11], &KumoPosTbl[var_r30_11]);
        Hu3DModelRotSet(work->kumoMdlId[var_r30_11], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(work->kumoMdlId[var_r30_11], 1U);
        work->kumoPosX[var_r30_11] = KumoPosTbl[var_r30_11].x;
        work->kumoDir[var_r30_11] = (f32) KumoDirTbl[var_r30_11];
        work->kumoAngle[var_r30_11] = 0.0f;
        var_r30_11 += 1;
        goto loop_93;
    }
    var_r30_12 = 0;
loop_99:
    if (var_r30_12 < 2) {
        if (var_r30_12 == 0) {
            work->starMdlId[var_r30_12] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            work->starMdlId[var_r30_12] = Hu3DModelLink(work->starMdlId[0]);
        }
        Hu3DModelAttrSet(work->starMdlId[var_r30_12], 1U);
        Hu3DModelAttrSet(work->starMdlId[var_r30_12], 0x40000002U);
        Hu3DModelLayerSet(work->starMdlId[var_r30_12], 3);
        Hu3DModelPosSetV(work->starMdlId[var_r30_12], &StarPosTbl[var_r30_12]);
        Hu3DModelRotSet(work->starMdlId[var_r30_12], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(work->starMdlId[var_r30_12], 1U);
        work->starTime[var_r30_12] = 0;
        var_r30_12 += 1;
        goto loop_99;
    }
    work->auroraMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->auroraMdlId, 1U);
    Hu3DModelAttrSet(work->auroraMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->auroraMdlId, 3);
    Hu3DModelPosSet(work->auroraMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(work->auroraMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(work->auroraMdlId, 1U);
    Hu3DTexScrollPosMoveSet(Hu3DTexScrollCreate(work->auroraMdlId, "m506alora"), 0.0f, 0.0016666667f, 0.0f);
    Hu3DTexScrollPosMoveSet(Hu3DTexScrollCreate(work->auroraMdlId, lbl_1_data_F0), 0.0f, 0.0016666667f, 0.0f);
    var_r29_7 = 0;
loop_112:
    if (var_r29_7 < 4) {
        var_r30_13 = 0;
loop_110:
        if (var_r30_13 < 0xA) {
            if ((var_r29_7 == 0) && (var_r30_13 == 0)) {
                work->mameSmallMdlId[var_r29_7][var_r30_13] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
            } else {
                work->mameSmallMdlId[var_r29_7][var_r30_13] = Hu3DModelLink(work->mameSmallMdlId[0][0]);
            }
            Hu3DModelAttrSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 1U);
            Hu3DModelAttrSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 0x40000002U);
            Hu3DModelLayerSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 4);
            temp_r28_4 = work->mameSmallFlag[0][(var_r29_7 * 0xA) + var_r30_13] & 0xF;
            temp_r5 = (u32) temp_r28_4 >> 0x1FU;
            temp_r4 = (temp_r28_4 << 0x1E) - temp_r5;
            work->mameSmallPosY[var_r29_7][var_r30_13] = (600.0f * (f32) (temp_r28_4 / 4)) + ((1800.0f * (f32) var_r30_13) + sp8[(temp_r28_4 % 4)]);
            Hu3DModelPosSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 0.0f, work->mameSmallPosY[var_r29_7][var_r30_13], 0.0f);
            if ((s32) (work->mameSmallFlag[0][(var_r29_7 * 0xA) + var_r30_13] & 0x10) != 0) {
                Hu3DModelRotSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 50.0f, -90.0f, 0.0f);
            } else {
                Hu3DModelRotSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 50.0f, 90.0f, 0.0f);
            }
            Hu3DModelCameraSet(work->mameSmallMdlId[var_r29_7][var_r30_13], (u16) M506CameraBit[var_r29_7]);
            Hu3DModelScaleSet(work->mameSmallMdlId[var_r29_7][var_r30_13], 0.0f, 0.0f, 0.0f);
            work->mameSmallTime[var_r29_7][var_r30_13] = 0;
            var_r30_13 += 1;
            goto loop_110;
        }
        var_r29_7 += 1;
        goto loop_112;
    }
    var_r29_8 = 0;
loop_125:
    if (var_r29_8 < 4) {
        var_r30_14 = 0;
loop_123:
        if (var_r30_14 < 0xA) {
            if ((var_r29_8 == 0) && (var_r30_14 == 0)) {
                work->mameSpiralMdlId[var_r29_8][var_r30_14] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
            } else {
                work->mameSpiralMdlId[var_r29_8][var_r30_14] = Hu3DModelLink(work->mameSpiralMdlId[0][0]);
            }
            Hu3DModelAttrSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 1U);
            Hu3DModelAttrSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 0x40000002U);
            Hu3DModelLayerSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 4);
            temp_r28_5 = work->mameSpiralFlag[0][(var_r29_8 * 0xA) + var_r30_14] & 0xF;
            temp_r5_2 = (u32) temp_r28_5 >> 0x1FU;
            temp_r4_2 = (temp_r28_5 << 0x1E) - temp_r5_2;
            work->mameSpiralPosY[var_r29_8][var_r30_14] = (600.0f * (f32) (temp_r28_5 / 4)) + ((1800.0f * (f32) var_r30_14) + sp18[(temp_r28_5 % 4)]);
            Hu3DModelPosSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 0.0f, work->mameSpiralPosY[var_r29_8][var_r30_14], 0.0f);
            if ((s32) (work->mameSpiralFlag[0][(var_r29_8 * 0xA) + var_r30_14] & 0x10) != 0) {
                Hu3DModelRotSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 0.0f, -90.0f, 0.0f);
            } else {
                Hu3DModelRotSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 0.0f, 90.0f, 0.0f);
            }
            Hu3DModelCameraSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], (u16) M506CameraBit[var_r29_8]);
            Hu3DModelScaleSet(work->mameSpiralMdlId[var_r29_8][var_r30_14], 0.0f, 0.0f, 0.0f);
            work->mameSpiralTime[var_r29_8][var_r30_14] = 0;
            var_r30_14 += 1;
            goto loop_123;
        }
        var_r29_8 += 1;
        goto loop_125;
    }
    work->noko2MdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x11], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->noko2MdlId, 1U);
    Hu3DModelAttrSet(work->noko2MdlId, 0x40000001U);
    Hu3DModelLayerSet(work->noko2MdlId, 2);
    Hu3DModelPosSet(work->noko2MdlId, 100.0f, 6500.0f, -100.0f);
    Hu3DModelRotSet(work->noko2MdlId, 0.0f, -90.0f, 0.0f);
    Hu3DModelAttrReset(work->noko2MdlId, 1U);
    work->sunMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x13], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(work->sunMdlId, 1U);
    Hu3DModelAttrSet(work->sunMdlId, 0x40000002U);
    Hu3DModelLayerSet(work->sunMdlId, 1);
    Hu3DModelPosSet(work->sunMdlId, -210.0f, 10050.0f, -4500.0f);
    Hu3DModelRotSet(work->sunMdlId, 0.0f, 30.0f, 0.0f);
    Hu3DModelAttrReset(work->sunMdlId, 1U);
    var_r29_9 = 0;
loop_128:
    if (var_r29_9 < 4) {
        work->mameEnterTime[var_r29_9] = 0;
        work->unk53C[var_r29_9] = 0;
        work->mameMissTime[var_r29_9] = 0;
        var_r29_9 += 1;
        goto loop_128;
    }
    work->noko2Time = 0.0f;
    work->noko2Angle = 0.0f;
    work->noko2CamBit = 0;
    work->rocketCamBit = 0;
    work->kumo2MdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
    work->kumo2MdlId[1] = Hu3DModelLink(work->kumo2MdlId[0]);
    work->kumo2MdlId[2] = Hu3DModelLink(work->kumo2MdlId[0]);
    work->kumo2MdlId[3] = Hu3DModelLink(work->kumo2MdlId[0]);
    var_r30_15 = 0;
loop_131:
    if (var_r30_15 < 4) {
        Hu3DModelAttrSet(work->kumo2MdlId[var_r30_15], 1U);
        Hu3DModelAttrSet(work->kumo2MdlId[var_r30_15], 0x40000002U);
        Hu3DModelLayerSet(work->kumo2MdlId[var_r30_15], 6);
        Hu3DModelPosSet(work->kumo2MdlId[var_r30_15], 0.0f, 9300.0f, 1200.0f);
        Hu3DModelRotSet(work->kumo2MdlId[var_r30_15], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(work->kumo2MdlId[var_r30_15], (u16) M506CameraBit[var_r30_15]);
        Hu3DModelAttrReset(work->kumo2MdlId[var_r30_15], 1U);
        var_r30_15 += 1;
        goto loop_131;
    }
    work->smokeMdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(M506ModelFile[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
    work->smokeMdlId[1] = Hu3DModelLink(work->smokeMdlId[0]);
    work->smokeMdlId[2] = Hu3DModelLink(work->smokeMdlId[0]);
    var_r30_16 = 0;
loop_134:
    if (var_r30_16 < 3) {
        Hu3DModelAttrSet(work->smokeMdlId[var_r30_16], 1U);
        Hu3DModelAttrSet(work->smokeMdlId[var_r30_16], 0x40000002U);
        Hu3DModelLayerSet(work->smokeMdlId[var_r30_16], 6);
        Hu3DModelPosSet(work->smokeMdlId[var_r30_16], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(work->smokeMdlId[var_r30_16], 0.0f, 0.0f, 0.0f);
        var_r30_16 += 1;
        goto loop_134;
    }
}

void M506TimerCreate(M506_WORK *work) {
    work->gameMesId = -1;
    work->timer = MgTimerCreate(0);
    MgTimerParamSet(work->timer, 0x708, 0, 0);
    work->recordVal = GWMgRecordGet(0);
}

s32 M506FlowUpdate(M506_WORK *work) {
    s32 temp_r0_2;
    s32 var_r29;
    uintptr_t *temp_r30;
    u32 temp_r0;

    var_r29 = 0;
    temp_r30 = &M506MainObj->work[3];
    temp_r0 = M506MainObj->work[3];
    switch (temp_r0) {
    case 0:
        if ((s16) work->gameMesId < 0) {
            work->gameMesId = MGSeqStartCreate();
            *temp_r30 = 1;
            Hu3DModelAttrSet(work->stageBorderMdlId, 1U);
            work->gameMesDelay = 0;
            streamNo = HuAudBGMPlay(0x3C);
        }
        break;
    case 1:
        if (GameMesStatGet(work->gameMesId) == 0) {
            work->gameMesId = -1;
            MgTimerModeOnSet(work->timer, 1);
            *temp_r30 = 2;
        }
        break;
    case 2:
        if (MgTimerDoneCheck(work->timer) != 0) {
            *temp_r30 = 4;
        }
        break;
    case 3:
        temp_r0_2 = work->gameMesDelay + 1;
        work->gameMesDelay = temp_r0_2;
        if (temp_r0_2 > 0x1E) {
            *temp_r30 = 5;
        }
        break;
    case 4:
        if ((s16) work->gameMesId < 0) {
            work->gameMesId = MGSeqFinishCreate();
            HuAudSStreamFadeOut(streamNo, 0x3E8);
        } else if (GameMesStatGet(work->gameMesId) == 0) {
            work->gameMesId = -1;
            *temp_r30 = 3;
        }
        break;
    case 5:
        WipeColorSet(0xFFU, 0xFFU, 0xFFU);
        WipeCreate(2, 0, 0x3C);
        *temp_r30 = 6;
        break;
    case 6:
        if (WipeCheckEnd() == 0) {
            var_r29 = 1;
        }
        break;
    }
    M506ModelUpdate(work);
    return var_r29;
}








void M506MameUpdate(M506_PLAYER_WORK *player) {
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r4;
    s32 var_r28;
    M506_WORK *temp_r26;
    M506_WORK *temp_r27;

    if ((s32) player->jumpTicks < 0x10) {
        temp_r27 = M506MainObj->data;
        if (((s32) player->newHeight == (s32) player->height) && ((s32) player->height < 0x3C) && ((s16) player->jumpF != 0)) {
            temp_r27->mameVinePosY[player->no] = temp_r27->mameVinePosY[player->no] + 20.0f;
            Hu3DModelPosSet(temp_r27->mameVineMdlId[player->no][0], 0.0f, temp_r27->mameVinePosY[player->no], 0.0f);
            temp_r27->mameVineRotY[player->no] = temp_r27->mameVineRotY[player->no] + 24.0f;
            if (temp_r27->mameVineRotY[player->no] > 360.0f) {
                temp_r27->mameVineRotY[player->no] = temp_r27->mameVineRotY[player->no] - 360.0f;
            }
            Hu3DModelRotSet(temp_r27->mameVineMdlId[player->no][0], 0.0f, temp_r27->mameVineRotY[player->no], 0.0f);
            Hu3DModelPosSet(temp_r27->mameVineMdlId[player->no][1], 0.0f, temp_r27->mameVinePosY[player->no] - 600.0f, 0.0f);
            Hu3DModelRotSet(temp_r27->mameVineMdlId[player->no][1], 0.0f, temp_r27->mameVineRotY[player->no], 0.0f);
            var_r28 = 2;
loop_8:
            if (var_r28 < 0x1F) {
                Hu3DModelPosSet(temp_r27->mameVineMdlId[player->no][var_r28], 0.0f, temp_r27->mameVinePosY[player->no] - (600.0f * (f32) var_r28), 0.0f);
                var_r28 += 1;
                goto loop_8;
            }
            if (temp_r27->mameVinePosY[player->no] < 300.0f) {
                var_f29 = 0.4f + (0.4f * (temp_r27->mameVinePosY[player->no] / 300.0f));
            } else {
                var_f29 = 0.8f;
            }
            Hu3DTexScrollPosSet(temp_r27->mameShadowTexScrId[player->no], 0.0f, var_f29, 0.0f);
        }
    } else if (((s32) player->jumpTicks < 0x1F) && (temp_r26 = M506MainObj->data, (((s32) player->newHeight == (s32) player->height) != 0)) && ((s32) player->height < 0x3C) && ((s16) player->jumpF != 0)) {
        if ((s16) temp_r26->mameVineTime[player->no] == 0) {
            Hu3DModelAttrReset(temp_r26->mameMdlId[player->no][player->height], 1U);
        }
        temp_r26->mameVineTime[player->no] = temp_r26->mameVineTime[player->no] + 1;
        if ((s16) temp_r26->mameVineTime[player->no] < 5) {
            var_f31 = 1.1f * (f32) temp_r26->mameVineTime[player->no] * 0.25f;
        } else if ((s16) temp_r26->mameVineTime[player->no] < 7) {
            var_f31 = 1.1f - (0.05f * (f32) (temp_r26->mameVineTime[player->no] - 5));
        } else {
            var_f31 = 1.0f;
            if ((s16) temp_r26->mameVineTime[player->no] == 0xF) {
                temp_r26->mameVineTime[player->no] = 0;
            }
        }
        if ((s16) temp_r26->mameVineTime[player->no] < 4) {
            var_f30 = 2.0f * (f32) -temp_r26->mameVineTime[player->no];
        } else if ((s16) temp_r26->mameVineTime[player->no] < 7) {
            var_f30 = -6.0f + ((6.0f * (f32) (temp_r26->mameVineTime[player->no] - 3)) / 3.0f);
        } else {
            var_f30 = 0.0f;
        }
        Hu3DModelScaleSet(temp_r26->mameMdlId[player->no][player->height], var_f31, var_f31, var_f31);
        if ((u8) temp_r26->mameSide[player->no][player->height] != 0) {
            Hu3DModelRotSet(temp_r26->mameMdlId[player->no][player->height], var_f30, 20.0f, 0.0f);
            return;
        }
        Hu3DModelRotSet(temp_r26->mameMdlId[player->no][player->height], var_f30, -20.0f, 0.0f);
    }
}

void M506MameModeEnter(M506_PLAYER_WORK *player) {
    f32 var_f31;
    s32 temp_r29;
    s32 temp_r4;
    M506_WORK *temp_r28;

    temp_r28 = M506MainObj->data;
    if ((s32) player->newHeight > 0) {
        temp_r29 = player->newHeight - 1;
        temp_r28->mameEnterTime[player->no] = temp_r28->mameEnterTime[player->no] + 1;
        if ((s16) temp_r28->mameEnterTime[player->no] < 8) {
            var_f31 = 0.0f;
        } else if ((s16) temp_r28->mameEnterTime[player->no] < 0xA) {
            var_f31 = (f32) temp_r28->mameEnterTime[player->no] - 7.0f;
        } else if ((s16) temp_r28->mameEnterTime[player->no] < 0xF) {
            var_f31 = 5.0f * (1.0f - (((f32) temp_r28->mameEnterTime[player->no] - 9.0f) / 5.0f));
        } else {
            temp_r28->mameEnterTime[player->no] = 0;
            var_f31 = 0.0f;
        }
        if ((u8) temp_r28->mameSide[player->no][temp_r29] != 0) {
            Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], var_f31, 20.0f, 0.0f);
            return;
        }
        Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], var_f31, -20.0f, 0.0f);
    }
}

void M506MameModeMiss(M506_PLAYER_WORK *player) {
    f32 var_f31;
    s32 temp_r29;
    s32 temp_r4;
    M506_WORK *temp_r28;

    temp_r28 = M506MainObj->data;
    temp_r29 = player->prevHeight;
    temp_r28->mameMissTime[player->no] = temp_r28->mameMissTime[player->no] + 1;
    if ((s16) temp_r28->mameMissTime[player->no] < 2) {
        var_f31 = 0.0f;
    } else if ((s16) temp_r28->mameMissTime[player->no] < 6) {
        var_f31 = 20.0f * ((f32) temp_r28->mameMissTime[player->no] - 1.0f) * 0.25f;
    } else if ((s16) temp_r28->mameMissTime[player->no] < 0x14) {
        var_f31 = (f32) (20.0 * sin((3.141592653589793 * (f64) ((90.0f * (19.0f - (f32) temp_r28->mameMissTime[player->no])) / 13.0f)) / 180.0));
    } else if ((s16) temp_r28->mameMissTime[player->no] < 0x1E) {
        var_f31 = 0.0f;
    } else {
        temp_r28->mameMissTime[player->no] = 0;
        var_f31 = 0.0f;
    }
    if ((u8) temp_r28->mameSide[player->no][temp_r29] != 0) {
        Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], -var_f31, 20.0f, 0.0f);
        return;
    }
    Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], -var_f31, -20.0f, 0.0f);
}

void M506MameModeJump(M506_PLAYER_WORK *player) {
    f32 var_f31;
    s32 temp_r29;
    s32 temp_r4;
    M506_WORK *temp_r28;

    temp_r28 = M506MainObj->data;
    if ((s32) player->newHeight > 0) {
        temp_r29 = player->newHeight - 1;
        temp_r28->mameMissTime[player->no] = temp_r28->mameMissTime[player->no] + 1;
        if ((s16) temp_r28->mameMissTime[player->no] < 4) {
            var_f31 = 0.0f;
        } else if ((s16) temp_r28->mameMissTime[player->no] < 6) {
            var_f31 = 50.0f * ((f32) temp_r28->mameMissTime[player->no] - 3.0f) * 0.5f;
        } else if ((s16) temp_r28->mameMissTime[player->no] < 0x14) {
            var_f31 = (f32) (50.0 * sin((3.141592653589793 * (f64) ((90.0f * (19.0f - (f32) temp_r28->mameMissTime[player->no])) / 13.0f)) / 180.0));
        } else if ((s16) temp_r28->mameMissTime[player->no] < 0x1E) {
            var_f31 = 0.0f;
        } else {
            temp_r28->mameMissTime[player->no] = 0;
            var_f31 = 0.0f;
        }
        if ((u8) temp_r28->mameSide[player->no][temp_r29] != 0) {
            Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], 0.0f, 20.0f, var_f31);
            return;
        }
        Hu3DModelRotSet(temp_r28->mameMdlId[player->no][temp_r29], 0.0f, -20.0f, -var_f31);
    }
}

void M506ModelUpdate(M506_WORK *work) {
    M506_PLAYER_WORK *sp50[4];
    f64 sp48;
    M506_WORK *sp40;
    s32 sp3C;
    M506_WORK *sp38;
    M506_PLAYER_WORK *sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    u16 sp18;
    u16 sp16;
    u16 sp14;
    u16 sp12;
    u16 sp10;
    u16 spE;
    u16 spC;
    M506_WORK *sp8;
    f32 temp_f0;
    f32 temp_f0_3;
    f32 temp_f18;
    f32 temp_f19;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f31;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f64 temp_f0_2;
    s32 temp_r3;
    s32 temp_r4;
    s32 var_r19;
    s32 var_r20;
    s32 var_r22;
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;
    s32 var_r30_7;
    u16 var_r17;
    u16 var_r18;
    u16 var_r21;
    M506_PLAYER_WORK *temp_r23;
    M506_PLAYER_WORK *temp_r27;

    sp8 = work;
    var_r18 = 0;
    var_r21 = 0;
    var_r17 = 0;
    sp18 = 0;
    sp16 = 0;
    sp14 = 0;
    sp12 = 0;
    sp10 = 0;
    spE = 0;
    spC = 0;
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        sp50[var_r30] = M506PlayerObj[var_r30]->data;
        var_r30 += 1;
        goto loop_2;
    }
    var_r29 = 0;
loop_82:
    if (var_r29 < 4) {
        temp_f31 = M506YCamera->camera[sp50[var_r29]->no].target.y;
        if (temp_f31 < 8300.0f) {
            var_f27 = 0.0f;
        } else {
            var_f27 = (29.0f * (temp_f31 - 8300.0f)) / 10000.0f;
        }
        var_r30_2 = 0;
loop_13:
        if (var_r30_2 < 0x1F) {
            Hu3DMotionTimeSet(sp8->mameVineMdlId[var_r29][var_r30_2], var_f27);
            temp_f30 = sp8->mameVinePosY[sp50[var_r29]->no] - (600.0f * (f32) var_r30_2);
            if ((temp_f30 < (600.0f + temp_f31)) && (temp_f30 > (temp_f31 - 1800.0f))) {
                Hu3DModelAttrReset(sp8->mameVineMdlId[sp50[var_r29]->no][var_r30_2], 1U);
            } else {
                Hu3DModelAttrSet(sp8->mameVineMdlId[sp50[var_r29]->no][var_r30_2], 1U);
            }
            var_r30_2 += 1;
            goto loop_13;
        }
        var_r30_3 = 0;
loop_20:
        if (var_r30_3 < (s32) sp50[var_r29]->height) {
            Hu3DMotionTimeSet(sp8->mameMdlId[sp50[var_r29]->no][var_r30_3], var_f27);
            temp_f30_2 = 300.0f + (300.0f * (f32) var_r30_3);
            if ((temp_f30_2 < (600.0f + temp_f31)) && (temp_f30_2 > (temp_f31 - 900.0f))) {
                Hu3DModelAttrReset(sp8->mameMdlId[sp50[var_r29]->no][var_r30_3], 1U);
            } else {
                Hu3DModelAttrSet(sp8->mameMdlId[sp50[var_r29]->no][var_r30_3], 1U);
            }
            var_r30_3 += 1;
            goto loop_20;
        }
        if (var_r30_3 < 0x3C) {
            Hu3DMotionTimeSet(sp8->mameMdlId[sp50[var_r29]->no][var_r30_3], var_f27);
        }
        temp_f29 = 660.0f + temp_f31;
        temp_f28 = temp_f31 - 900.0f;
        var_r30_4 = 0;
loop_29:
        if (var_r30_4 < 0xA) {
            Hu3DMotionTimeSet(sp8->mameSpiralMdlId[sp50[var_r29]->no][var_r30_4], var_f27);
            temp_f30_3 = sp8->mameSpiralPosY[var_r29][var_r30_4];
            if ((temp_f30_3 < temp_f29) && (temp_f30_3 > temp_f28)) {
                Hu3DModelAttrReset(sp8->mameSpiralMdlId[sp50[var_r29]->no][var_r30_4], 1U);
            } else {
                Hu3DModelAttrSet(sp8->mameSpiralMdlId[sp50[var_r29]->no][var_r30_4], 1U);
            }
            var_r30_4 += 1;
            goto loop_29;
        }
        var_r30_5 = 0;
loop_36:
        if (var_r30_5 < 0xA) {
            Hu3DMotionTimeSet(sp8->mameSmallMdlId[sp50[var_r29]->no][var_r30_5], var_f27);
            temp_f30_4 = sp8->mameSmallPosY[var_r29][var_r30_5];
            if ((temp_f30_4 < temp_f29) && (temp_f30_4 > temp_f28)) {
                Hu3DModelAttrReset(sp8->mameSmallMdlId[sp50[var_r29]->no][var_r30_5], 1U);
            } else {
                Hu3DModelAttrSet(sp8->mameSmallMdlId[sp50[var_r29]->no][var_r30_5], 1U);
            }
            var_r30_5 += 1;
            goto loop_36;
        }
        if (temp_f31 > 14500.0f) {
            var_r18 |= M506CameraBit[var_r29];
        }
        if (temp_f31 < 3000.0f) {
            var_r21 |= M506CameraBit[var_r29];
        }
        if ((temp_f31 > 8000.0f) && (temp_f31 < 15000.0f)) {
            var_r17 |= M506CameraBit[var_r29];
        }
        if ((temp_f31 > 4500.0f) && (temp_f31 < 6500.0f)) {
            sp18 |= M506CameraBit[var_r29];
        }
        if (temp_f31 > 11000.0f) {
            sp16 |= M506CameraBit[var_r29];
        }
        if (temp_f31 < 6600.0f) {
            sp14 |= M506CameraBit[var_r29];
        }
        if (temp_f31 < 14000.0f) {
            sp10 |= M506CameraBit[var_r29];
        }
        if (temp_f31 > 6000.0f) {
            spE |= M506CameraBit[var_r29];
        }
        if ((temp_f31 > 6000.0f) && (temp_f31 < 13000.0f)) {
            sp12 |= M506CameraBit[var_r29];
        }
        if (temp_f31 > 10000.0f) {
            spC |= M506CameraBit[var_r29];
        }
        temp_r23 = sp50[var_r29];
        sp40 = M506MainObj->data;
        temp_f19 = sp40->mameVinePosY[temp_r23->no];
        var_r20 = 0;
loop_67:
        if (var_r20 < 0xA) {
            if ((temp_f19 > (sp40->mameSpiralPosY[temp_r23->no][var_r20] - 600.0f)) && ((s16) sp40->mameSpiralTime[temp_r23->no][var_r20] < 0x19)) {
                sp40->mameSpiralTime[temp_r23->no][var_r20] = sp40->mameSpiralTime[temp_r23->no][var_r20] + 1;
                temp_f23 = (f32) sp40->mameSpiralTime[temp_r23->no][var_r20] / 25.0f;
                var_f24 = 3.0f * temp_f23;
                if (var_f24 > 1.0f) {
                    var_f24 = 1.0f;
                }
                Hu3DModelScaleSet(sp40->mameSpiralMdlId[temp_r23->no][var_r20], var_f24, temp_f23, var_f24);
            }
            var_r20 += 1;
            goto loop_67;
        }
        temp_r27 = sp50[var_r29];
        sp38 = M506MainObj->data;
        temp_f18 = sp38->mameVinePosY[temp_r27->no];
        var_r25 = 0;
loop_80:
        if (var_r25 < 0xA) {
            if (temp_f18 > (sp38->mameSmallPosY[temp_r27->no][var_r25] - 600.0f)) {
                sp38->mameSmallTime[temp_r27->no][var_r25] = sp38->mameSmallTime[temp_r27->no][var_r25] + 1;
                if ((s16) sp38->mameSmallTime[temp_r27->no][var_r25] < 0x28) {
                    var_f26 = (f32) sp38->mameSmallTime[temp_r27->no][var_r25] / 40.0f;
                    if (var_f26 > 1.0f) {
                        var_f26 = 1.0f;
                    }
                    Hu3DModelScaleSet(sp38->mameSmallMdlId[temp_r27->no][var_r25], var_f26, var_f26, var_f26);
                }
                if ((s16) sp38->mameSmallTime[temp_r27->no][var_r25] >= 0x50) {
                    sp38->mameSmallTime[temp_r27->no][var_r25] = 0x28;
                }
                temp_f22 = (f32) (10.0 * sin((3.141592653589793 * (f64) ((360.0f * (f32) (sp38->mameSmallTime[temp_r27->no][var_r25] - 0x28)) / 40.0f)) / 180.0));
                sp3C = (s32) sp38->mameSmallFlag[temp_r27->no][var_r25];
                if ((s32) (sp3C & 0x10) != 0) {
                    Hu3DModelRotSet(sp38->mameSmallMdlId[temp_r27->no][var_r25], 50.0f - temp_f22, -90.0f, 0.0f);
                } else {
                    Hu3DModelRotSet(sp38->mameSmallMdlId[temp_r27->no][var_r25], 50.0f - temp_f22, 90.0f, 0.0f);
                }
            }
            var_r25 += 1;
            goto loop_80;
        }
        var_r29 += 1;
        goto loop_82;
    }
    Hu3DModelCameraSet(sp8->stageMdlId, var_r21);
    Hu3DModelCameraSet(sp8->windmillMdlId, var_r21);
    Hu3DModelCameraSet(sp8->moundMdlId, var_r21);
    Hu3DModelCameraSet(sp8->moonMdlId, var_r18);
    Hu3DModelCameraSet(sp8->auroraMdlId, var_r17);
    Hu3DModelCameraSet(sp8->noko2MdlId, (u16) (sp18 & sp8->noko2CamBit));
    Hu3DModelCameraSet(sp8->rocketMdlId, (u16) (spC & sp8->rocketCamBit));
    Hu3DModelCameraSet(sp8->bgMdlId[0], sp10);
    Hu3DModelCameraSet(sp8->bgMdlId[1], spE);
    Hu3DModelCameraSet(sp8->sunMdlId, sp12);
    Hu3DModelCameraSet(sp8->glowShadowMdlId, var_r21);
    Hu3DModelCameraSet(sp8->mameVineShadowMdlId, var_r21);
    if (var_r21 != 0) {
        Hu3DModelAttrReset(sp8->stageMdlId, 1U);
        Hu3DModelAttrReset(sp8->windmillMdlId, 1U);
        Hu3DModelAttrReset(sp8->moundMdlId, 1U);
        Hu3DModelAttrReset(sp8->glowShadowMdlId, 1U);
        Hu3DModelAttrReset(sp8->mameVineShadowMdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->stageMdlId, 1U);
        Hu3DModelAttrSet(sp8->windmillMdlId, 1U);
        Hu3DModelAttrSet(sp8->moundMdlId, 1U);
        Hu3DModelAttrSet(sp8->glowShadowMdlId, 1U);
        Hu3DModelAttrSet(sp8->mameVineShadowMdlId, 1U);
    }
    if (var_r18 != 0) {
        Hu3DModelAttrReset(sp8->moonMdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->moonMdlId, 1U);
    }
    if (var_r17 != 0) {
        Hu3DModelAttrReset(sp8->auroraMdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->auroraMdlId, 1U);
    }
    if (sp18 != 0) {
        Hu3DModelAttrReset(sp8->noko2MdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->noko2MdlId, 1U);
    }
    if (spC != 0) {
        Hu3DModelAttrReset(sp8->rocketMdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->rocketMdlId, 1U);
    }
    if (sp10 != 0) {
        Hu3DModelAttrReset(sp8->bgMdlId[0], 1U);
    } else {
        Hu3DModelAttrSet(sp8->bgMdlId[0], 1U);
    }
    if (spE != 0) {
        Hu3DModelAttrReset(sp8->bgMdlId[1], 1U);
    } else {
        Hu3DModelAttrSet(sp8->bgMdlId[1], 1U);
    }
    if (sp12 != 0) {
        Hu3DModelAttrReset(sp8->sunMdlId, 1U);
    } else {
        Hu3DModelAttrSet(sp8->sunMdlId, 1U);
    }
    var_r30_6 = 0;
loop_109:
    if (var_r30_6 < 4) {
        Hu3DModelCameraSet(sp8->kumoMdlId[var_r30_6], sp14);
        var_r30_6 += 1;
        goto loop_109;
    }
    var_r30_7 = 0;
loop_112:
    if (var_r30_7 < 2) {
        Hu3DModelCameraSet(sp8->starMdlId[var_r30_7], sp16);
        var_r30_7 += 1;
        goto loop_112;
    }
    var_r26 = 0;
loop_124:
    if (var_r26 < 4) {
        temp_f0 = sp8->kumoPosX[var_r26];
        sp24 = temp_f0;
        temp_f0_2 = fabs(temp_f0);
        sp48 = temp_f0_2;
        temp_f0_3 = (f32) temp_f0_2;
        sp20 = temp_f0_3;
        sp1C = temp_f0_3;
        var_f25 = (300.0f - temp_f0_3) / 100.0f;
        if (var_f25 > 1.0f) {
            var_f25 = 1.0f;
        }
        if (var_f25 < 0.2f) {
            var_f25 = 0.2f;
        }
        sp8->kumoPosX[var_r26] += sp8->kumoDir[var_r26] * var_f25;
        if ((sp8->kumoPosX[var_r26] < -300.0f) || (sp8->kumoPosX[var_r26] > 300.0f)) {
            sp8->kumoDir[var_r26] *= -1.0f;
        }
        Hu3DModelPosSet(sp8->kumoMdlId[var_r26], sp8->kumoPosX[var_r26], KumoPosTbl[var_r26].y, KumoPosTbl[var_r26].z);
        sp8->kumoAngle[var_r26] += 10.0f * (f32) KumoDirTbl[var_r26];
        if (sp8->kumoAngle[var_r26] > 360.0f) {
            sp8->kumoAngle[var_r26] -= 360.0f;
        }
        temp_f21 = (f32) (1.0 + (0.05000000074505806 * sin((3.141592653589793 * (f64) sp8->kumoAngle[var_r26]) / 180.0)));
        Hu3DModelScaleSet(sp8->kumoMdlId[var_r26], temp_f21, temp_f21, 1.0f);
        var_r26 += 1;
        goto loop_124;
    }
    var_r22 = 0;
loop_129:
    if (var_r22 < 2) {
        sp8->starTime[var_r22] += 1;
        if ((s16) sp8->starTime[var_r22] > (s16) StarMaxTime[var_r22]) {
            sp8->starTime[var_r22] = 0;
        }
        temp_f20 = (f32) (0.949999988079071 + (0.10000000149011612 * sin((3.141592653589793 * (f64) ((360.0f * (f32) sp8->starTime[var_r22]) / (f32) StarMaxTime[var_r22])) / 180.0)));
        Hu3DModelScaleSet(sp8->starMdlId[var_r22], temp_f20, temp_f20, 1.0f);
        var_r22 += 1;
        goto loop_129;
    }
    if ((u16) sp8->noko2CamBit == 0) {
        var_r19 = 0;
loop_135:
        if (var_r19 < 4) {
            sp34 = M506PlayerObj[var_r19]->data;
            if ((s32) sp34->newHeight == 0xF) {
                sp8->noko2CamBit |= M506CameraBit[var_r19];
            }
            var_r19 += 1;
            goto loop_135;
        }
    }
    sp8->noko2Time += 1.0f;
    if (sp8->noko2Time > 360.0f) {
        sp8->noko2Time -= 360.0f;
    }
    sp8->noko2Angle += 1.0f;
    if (sp8->noko2Angle > 360.0f) {
        sp8->noko2Angle -= 360.0f;
    }
    sp28 = (f32) (5500.0 + (20.0 * sin((3.141592653589793 * (f64) sp8->noko2Time) / 180.0)));
    sp2C = (f32) (120.0 * sin((3.141592653589793 * (f64) sp8->noko2Angle) / 180.0));
    sp30 = (f32) ((20.0 * cos((3.141592653589793 * (f64) sp8->noko2Angle) / 180.0)) - 220.0);
    Hu3DModelPosSet(sp8->noko2MdlId, sp2C, sp28, sp30);
    Hu3DModelRotSet(sp8->noko2MdlId, 0.0f, sp8->noko2Angle, 0.0f);
    M506RocketUpdate();
    M506StarfighterUpdate();
}

void M506MainCreate(omObjData *obj) {
    M506Create((M506_WORK *) obj->data);
    obj->func = M506MainUpdate;
}

void M506FlowEndWatch(omObjData *obj) {
    M506_WORK *temp_r30;

    temp_r30 = obj->data;
    if ((M506ExitCheck(obj) == 0) && (M506FlowUpdate((M506_WORK *) temp_r30) != 0)) {
        obj->func = M506FlowModeEnd;
    }
}

void M506ObjShadowMapSet(s32 no, s32 mame) {
    s32 spC;
    s32 sp8;

    sp8 = no;
    spC = mame;
    Hu3DModelShadowMapSet(((M506_WORK *) M506MainObj->data)->mameMdlId[sp8][spC - 1]);
}

void M506ObjShadowMapReset(s32 no, s32 from, s32 to) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r31;
    M506_WORK *temp_r30;

    sp8 = no;
    spC = from;
    sp10 = to;
    temp_r30 = M506MainObj->data;
    var_r31 = spC;
loop_2:
    if (var_r31 < sp10) {
        Hu3DModelShadowMapObjReset(temp_r30->mameMdlId[sp8][var_r31]);
        var_r31 += 1;
        goto loop_2;
    }
}

void M506MainUpdate(omObjData *obj) {
    s32 temp_r27;
    s32 temp_r28;
    s32 var_r29;
    u32 temp_r0;

    temp_r27 = M506ExitCheck(obj);
    temp_r0 = obj->work[2];
    switch ((s32) temp_r0) {                        /* irregular */
    case 0:
        Hu3DBGColorSet(0U, 0U, 0U);
        M506Flow.work0 = (M506_WORK *) obj->data;
        M506Flow.work = M506Flow.work0;
        var_r29 = 0;
loop_9:
        if (var_r29 < 4) {
            M506Flow.playerObj[var_r29] = M506PlayerObj[var_r29];
            M506Flow.player[var_r29] = (M506_PLAYER_WORK *) M506Flow.playerObj[var_r29]->data;
            var_r29 += 1;
            goto loop_9;
        }
        M506Flow.seedState = 0;
        M506Flow.seedProc = HuPrcChildCreate(M506SeedUpdate, 0x64U, 0x3000U, 0, M506ObjMan);
        FlowTime = 0.0f;
        M506ObjInit(&M506Flow);
        M506RecordCreate(&M506Flow);
        M506RecordSet(&M506Flow);
        M506ModelUpdate(M506Flow.work0);
        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
        StartFXFlag = 0;
        StartFXTime = 0.0f;
        M506Flow.step = 0;
        M506Flow.unk2C = 0;
        M506Flow.unk30 = 0;
        M506Flow.time = 0.0f;
        obj->work[2] = 1;
        return;
    case 1:
        if ((s32) StartFXFlag == 0) {
            StartFXTime += 1.0f;
            if (StartFXTime >= 50.0f) {
                HuAudFXPlay(0x66B);
                StartFXFlag = 1;
            }
        }
        if (WipeCheckEnd() == 0) {
            M506Flow.seedState = 1;
            obj->work[2] = 2;
            return;
        }
        return;
    case 2:
        temp_r28 = M506FlowModeStart(&M506Flow);
        M506FlowMameSetup(&M506Flow);
        M506ModelUpdate(M506Flow.work0);
        if (temp_r28 != 0) {
            obj->work[2] = 3;
            return;
        }
        break;
    case 3:
        if (temp_r27 != 1) {
            M506ParticleKill(&M506Flow);
            obj->work[2] = 0;
            obj->func = M506FlowEndWatch;
        }
        break;
    }
}

void M506ObjInit(M506_FLOW *flow) {
    M506_YCAMERA *sp8;
    s32 var_r30;
    s32 var_r30_2;

    flow->step = 0;
    flow->seedSpeed = 0.0f;
    flow->winMotStep[0] = 0;
    flow->scrollStep = 0;
    flow->endF = 0;
    flow->gameMesId = -1;
    M506YCamera->splitTime = 0.0f;
    M506YCameraProjUpdate();
    if ((s32) lbl_1_bss_18 == 0) {
        var_r30 = 0;
loop_6:
        if (var_r30 < 4) {
            sp8 = &M506YCamera->camera[var_r30];
            if (var_r30 == 0) {
                M506YCameraViewSet(var_r30, 1);
            } else {
                M506YCameraViewSet(var_r30, 0);
            }
            var_r30 += 1;
            goto loop_6;
        }
    }
    M506FlowModeStartSetup(flow);
    M506RocketInit(flow);
    flow->rocket.armed = 0;
    flow->unk158 = 0;
    M506StarfighterStart(flow);
    M506MameShadowOff(flow);
    M506ParticleCreate(flow);
    var_r30_2 = 0;
loop_9:
    if (var_r30_2 < 4) {
        flow->unk1F8[var_r30_2] = 0;
        var_r30_2 += 1;
        goto loop_9;
    }
    flow->unk200 = 0;
}

s32 M506FlowModeStart(M506_FLOW *flow) {
    s32 temp_r0;
    s32 var_r30;

    temp_r0 = flow->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s32) flow->seedState == 3) {
            flow->unk30 = 0;
            flow->time = 0.0f;
            flow->step = 1;
        }
block_43:
    default:
        return 0;
    case 1:
        flow->time += 1.0f;
        if (flow->time >= 30.0f) {
            M506MameShadowOn(flow);
            LookUpCurrRot = LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].from;
            Hu3DModelAttrReset(flow->work->moundMdlId, 0x40000002U);
            flow->unk30 = 0;
            flow->time = 0.0f;
            flow->step = 2;
        }
        goto block_43;
    case 2:
        M506YCameraViewLerp(0, 1);
        M506MameShadowScrollExec(flow);
        flow->scrollRot += 3.0f;
        flow->scrollScale += 0.008333334f;
        flow->scrollY += 5.4166665f;
        LookUpCurrRot -= (LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].from - LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].to) / 120.0f;
        if (flow->scrollRot >= 360.0f) {
            flow->scrollRot = 360.0f;
        }
        if (flow->scrollScale >= 1.0f) {
            flow->scrollScale = 1.0f;
        }
        if (flow->scrollY >= 0.0f) {
            flow->scrollY = 0.0f;
        }
        if (LookUpCurrRot <= LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].to) {
            LookUpCurrRot = LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].to;
        }
        if (flow->scrollY >= -108.333374f) {
            M506ShadowScrollInit(flow);
        }
        if (flow->scrollY == 0.0f) {
            flow->scrollRot = 0.0f;
            flow->scrollScale = 1.0f;
            flow->scrollY = 0.0f;
            LookUpCurrRot = LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].to;
            flow->step = 3;
        }
        if ((s32) flow->player[0]->charNo != 8) {
            Hu3DMotionForceSet(*flow->playerObj[0]->model, lbl_1_data_298, LookUpRotLockFlag[Mp5CharNo(flow->player[0]->charNo)], LookUpCurrRot);
        }
        goto block_43;
    case 3:
        M506ShadowScrollInit(flow);
        flow->time += 1.0f;
        if (flow->time >= 15.0f) {
            M506YCameraViewSet(0, 2);
            flow->unk30 = 0;
            flow->mameScale = 1.0f;
            flow->step = 4;
        }
        goto block_43;
    case 4:
        M506ShadowScrollInit(flow);
        M506FlowP1Update(flow);
        M506YCameraViewLerp(0, 2);
        M506YCamera->splitTime += 0.008333334f;
        if (M506YCamera->splitTime >= 1.0f) {
            M506YCamera->splitTime = 1.0f;
        }
        M506YCameraProjUpdate();
        if ((s32) flow->player[0]->charNo != 8) {
            LookUpCurrRot += (LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].from - LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].to) / 60.0f;
            if (LookUpCurrRot >= LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].from) {
                LookUpCurrRot = LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)].from;
            }
            Hu3DMotionForceSet(*flow->playerObj[0]->model, lbl_1_data_298, LookUpRotLockFlag[Mp5CharNo(flow->player[0]->charNo)], LookUpCurrRot);
        }
        if (M506YCamera->splitTime >= 1.0f) {
            var_r30 = 0;
loop_38:
            if (var_r30 < 3) {
                espDispOn(M506YCamera->splitSprId[var_r30]);
                var_r30 += 1;
                goto loop_38;
            }
            Hu3DBGColorSet(0U, 0x7FU, 0xFFU);
            if ((s32) flow->player[0]->charNo != 8) {
                Hu3DMotionNoMotReset(*flow->playerObj[0]->model, lbl_1_data_298, LookUpRotLockFlag[Mp5CharNo(flow->player[0]->charNo)]);
            }
            Hu3DModelAttrSet(flow->work->seedMdlId, 1U);
            flow->step = 5;
        }
        goto block_43;
    case 5:
        flow->step = 0;
        return 1;
    }
}

void M506FlowModeStartSetup(M506_FLOW *flow) {
    s32 var_r30;

    flow->seedY = 200.0f;
    flow->seedRot = 0.0f;
    flow->moundY = 10.0f;
    flow->scrollY = -650.0f;
    flow->scrollRot = 0.0f;
    flow->scrollScale = 0.0f;
    flow->mameRotX = 0.0f;
    flow->mameScale = 0.0f;
    flow->playerRot = 120.0f;
    Hu3DModelAttrReset(flow->work->seedMdlId, 1U);
    Hu3DModelRotSet(flow->work->moundMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(flow->work->moundMdlId, 1U);
    Hu3DModelAttrReset(flow->work->moundMdlId, 0x40000001U);
    Hu3DMotionSpeedSet(flow->work->moundMdlId, 0.5f);
    Hu3DMotionTimeSet(flow->work->moundMdlId, 0.0f);
    Hu3DModelAttrSet(flow->work->moundMdlId, 0x40000002U);
    M506FlowMameSetup(flow);
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        omSetTra(flow->playerObj[var_r30], -64.5f, 0.0f, 179.5f);
        omSetRot(flow->playerObj[var_r30], 0.0f, 0.0f, 0.0f);
        var_r30 += 1;
        goto loop_2;
    }
    omSetRot(flow->playerObj[0], 0.0f, flow->playerRot, 0.0f);
}

void M506FlowMameSetup(M506_FLOW *flow) {
    s32 var_r30;

    Hu3DModelPosSet(flow->work->seedMdlId, 0.0f, flow->seedY, 0.0f);
    Hu3DModelRotSet(flow->work->seedMdlId, flow->seedRot, flow->seedRot, 0.0f);
    Hu3DModelPosSet(flow->work->moundMdlId, 0.0f, flow->moundY, 0.0f);
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        Hu3DModelPosSet(flow->work->mameVineMdlId[0][var_r30], 0.0f, flow->scrollY - (600.0f * (f32) var_r30), 0.0f);
        Hu3DModelRotSet(flow->work->mameVineMdlId[0][var_r30], 0.0f, flow->scrollRot, 0.0f);
        Hu3DModelScaleSet(flow->work->mameVineMdlId[0][var_r30], flow->scrollScale, 1.0f, flow->scrollScale);
        var_r30 += 1;
        goto loop_2;
    }
    Hu3DModelRotSet(flow->work->mameMdlId[0][0], flow->mameRotX, -20.0f + (40.0f * (f32) flow->work->mameSide[0][0]), 0.0f);
    Hu3DModelScaleSet(flow->work->mameMdlId[0][0], flow->mameScale, flow->mameScale, flow->mameScale);
}

s32 M506ShadowScrollInit(M506_FLOW *flow) {
    s32 temp_r0;

    temp_r0 = flow->scrollStep;
    switch (temp_r0) {                              /* irregular */
    case 0:
        flow->mameScale += 0.06666667f;
        if (flow->mameScale >= 1.0f) {
            ScrollHeight = 2.0f;
            ScrollAngle = 0.0f;
            flow->mameScale = 1.0f;
            flow->scrollStep += 1;
        }
        if ((s32) MameShadowF == 0) {
            M506MameShadowScrollOn(flow);
            MameShadowF = 1;
        }
block_11:
    default:
        return 0;
    case 1:
        ScrollHeight -= 0.033333335f;
        if (ScrollHeight < 0.0f) {
            ScrollHeight = 0.0f;
            flow->scrollStep += 1;
            MameShadowF = 0;
            return 1;
        }
        ScrollAngle += 16.0f;
        flow->mameRotX = (f32) ((f64) ScrollHeight * sin((3.141592653589793 * (f64) ScrollAngle) / 180.0));
        goto block_11;
    }
}

void M506FlowP1Update(M506_FLOW *flow) {
    omObjData *temp_r30;
    u8 temp_r0;

    temp_r30 = *M506PlayerObj;
    temp_r0 = (u8) flow->winMotStep[0];
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s32) flow->player[0]->charNo != 8) {
            Hu3DMotionTimeSet(*temp_r30->model, 0.0f);
            Hu3DMotionSpeedSet(*temp_r30->model, 1.0f);
            Hu3DMotionShiftSet(*temp_r30->model, temp_r30->motion[6], 0.0f, 4.0f, 0U);
        }
        flow->winMotStep[0] = (u8) flow->winMotStep[0] + 1;
        break;
    case 1:
        if ((s32) flow->player[0]->charNo != 8) {
            if (Hu3DMotionTimeGet(*temp_r30->model) >= 58.0f) {
                Hu3DMotionShiftSet(*temp_r30->model, temp_r30->motion[0], 0.0f, 4.0f, 0x40000001U);
                flow->winMotStep[0] = (u8) flow->winMotStep[0] + 1;
            }
        } else {
            flow->winMotStep[0] = (u8) flow->winMotStep[0] + 1;
        }
        break;
    }
    flow->playerRot -= 2.0f;
    if (flow->playerRot < 0.0f) {
        flow->playerRot = 0.0f;
    }
    omSetRot(flow->playerObj[0], 0.0f, flow->playerRot, 0.0f);
}

void M506FlowModeEnd(omObjData *obj) {
    f32 temp_f1;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    u32 temp_r0;

    temp_r27 = M506ExitCheck(obj);
    temp_r0 = obj->work[2];
    switch (temp_r0) {
    case 0:
        M506Flow.work0 = (M506_WORK *) obj->data;
        M506Flow.work = M506Flow.work0;
        var_r29 = 0;
loop_4:
        if (var_r29 < 4) {
            M506Flow.playerObj[var_r29] = M506PlayerObj[var_r29];
            M506Flow.player[var_r29] = (M506_PLAYER_WORK *) M506Flow.playerObj[var_r29]->data;
            var_r29 += 1;
            goto loop_4;
        }
        M506Flow.endF = 1;
        M506FlowModeEndSetup(&M506Flow);
        M506ModelUpdate(M506Flow.work0);
        M506ScoreCreate(&M506Flow);
        M506RecordBlinkInit();
        WipeColorSet(0xFFU, 0xFFU, 0xFFU);
        WipeCreate(1, 0, 0x3C);
        obj->work[2] = 1;
        return;
    case 1:
        M506ModelUpdate(M506Flow.work0);
        if (WipeCheckEnd() == 0) {
            HuAudFXPlay(0x1D);
            obj->work[2] = 2;
            return;
        }
    default:
        return;
    case 2:
        temp_r28 = M506FlowStopCheck(&M506Flow);
        M506ModelUpdate(M506Flow.work0);
        if (temp_r28 != 0) {
            var_r29_2 = 0;
loop_11:
            if (var_r29_2 < 4) {
                M506Flow.scoreShow[var_r29_2] = 1;
                var_r29_2 += 1;
                goto loop_11;
            }
            M506Flow.step = 0;
            M506Flow.unk30 = 0;
            M506Flow.time = 0.0f;
            if (0 != 0) {
                obj->work[2] = 6;
            } else {
                obj->work[2] = 3;
            }
        }
        M506ScoreDispUpdate(&M506Flow);
        return;
    case 3:
        M506ModelUpdate(M506Flow.work0);
        M506Flow.time += 1.0f;
        if (M506Flow.time >= 30.0f) {
            M506Flow.unk30 = 0;
            M506Flow.time = 0.0f;
            obj->work[2] = 4;
            return;
        }
        break;
    case 4:
        M506ModelUpdate(M506Flow.work0);
        temp_r28_2 = M506FlowResult(&M506Flow);
        M506RecordBlink(&M506Flow);
        if (temp_r28_2 != 0) {
            obj->work[2] = 5;
            return;
        }
        break;
    case 5:
        M506RecordBlink(&M506Flow);
        temp_f1 = FlowTime + 1.0f;
        FlowTime = temp_f1;
        if (temp_f1 >= 210.0f) {
            obj->work[2] = 6;
            return;
        }
        break;
    case 6:
        M506ModelUpdate(M506Flow.work0);
        if (0 == 0) {
            M506RecordBlink(&M506Flow);
            Mp5WipeWhite(2, 0x3C);
            obj->work[2] = 7;
            return;
        }
        M506Flow.time += 1.0f;
        if (M506Flow.time >= 60.0f) {
            var_r29_3 = 0;
loop_27:
            if (var_r29_3 < 4) {
                /* MP5 decathlon score */
                var_r29_3 += 1;
                goto loop_27;
            }
            Mp5WipeWhite(2, 0x3C);
            M506Flow.unk30 = 0;
            M506Flow.time = 0.0f;
            obj->work[2] = 7;
            return;
        }
        break;
    case 7:
        M506ModelUpdate(M506Flow.work0);
        if (0 == 0) {
            M506RecordBlink(&M506Flow);
        }
        if (WipeCheckEnd() == 0) {
            obj->work[2] = 8;
            return;
        }
        break;
    case 8:
        if (temp_r27 != 1) {
            obj->work[2] = 0;
            HuAudFadeOut(0x3E8);
            obj->func = M506Exit;
        }
        break;
    }
}

void M506FlowModeEndSetup(M506_FLOW *flow) {
    s32 sp14[4];
    f32 spC[2];
    s8 winner[4];
    M506_STOP *temp_r28;
    M506_YCAMERA *temp_r29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r26;
    s32 var_r27_2;
    s32 var_r31;
    s32 var_r31_10;
    s32 var_r31_11;
    s32 var_r31_12;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;
    s32 var_r31_6;
    s32 var_r31_7;
    s32 var_r31_8;
    s32 var_r31_9;
    s8 var_r25;
    s8 var_r27;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp14[var_r31] = flow->player[var_r31]->charNo;
        var_r31 += 1;
        goto loop_2;
    }
    flow->prevRecord = flow->work0->recordVal / 3;
    flow->winnerNum = 0;
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 4) {
        flow->charStep[var_r31_2] = (s8) flow->player[var_r31_2]->height;
        flow->score[var_r31_2] = (s8) flow->player[var_r31_2]->newHeight;
        flow->winOrder[var_r31_2] = -1;
        winner[var_r31_2] = -1;
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r27 = 0;
    var_r31_3 = 0;
loop_16:
    if (var_r31_3 < 4) {
        if ((s8) (u8) flow->score[var_r31_3] > var_r27) {
            var_r27 = (s8) (u8) flow->score[var_r31_3];
            flow->winnerNum = 1;
            winner[var_r31_3] = 0;
            var_r26 = 0;
loop_10:
            if (var_r26 < var_r31_3) {
                winner[var_r26] = -1;
                var_r26 += 1;
                goto loop_10;
            }
        } else if (((s8) (u8) flow->score[var_r31_3] == var_r27) && (var_r27 != 0)) {
            flow->winnerNum += 1;
            winner[var_r31_3] = 0;
        }
        var_r31_3 += 1;
        goto loop_16;
    }
    var_r31_4 = 0;
loop_19:
    if (var_r31_4 < 4) {
        flow->winFlag[var_r31_4] = (s8) winner[var_r31_4];
        var_r31_4 += 1;
        goto loop_19;
    }
    var_r25 = 0;
    var_r31_5 = 0;
loop_26:
    if (var_r31_5 < 4) {
        if (((s8) (u8) flow->score[var_r31_5] > var_r25) && ((s8) winner[var_r31_5] == 0) && ((s16) GWPlayerCfg[flow->player[var_r31_5]->no].iscom == 0)) {
            var_r25 = (s8) (u8) flow->score[var_r31_5];
        }
        var_r31_5 += 1;
        goto loop_26;
    }
    flow->bestHeight = (s32) var_r25;
    flow->humanWinner = 0;
    var_r31_6 = 0;
loop_32:
    if (var_r31_6 < 4) {
        if (((s8) winner[var_r31_6] == 0) && ((s16) GWPlayerCfg[flow->player[var_r31_6]->no].iscom == 0)) {
            flow->humanWinner = 1;
        } else {
            var_r31_6 += 1;
            goto loop_32;
        }
    }
    var_r31_7 = 0;
loop_39:
    if (var_r31_7 < 4) {
        flow->winMotStep[var_r31_7] = 0;
        if ((s8) winner[var_r31_7] == -1) {
            flow->winMot[var_r31_7] = 5;
        } else if ((s8) winner[var_r31_7] == 0) {
            flow->winMot[var_r31_7] = 4;
        }
        var_r31_7 += 1;
        goto loop_39;
    }
    var_r27_2 = 0;
    var_r31_8 = 0;
loop_44:
    if (var_r31_8 < 4) {
        if ((s8) winner[var_r31_8] != -1) {
            flow->winOrder[var_r27_2] = (s8) sp14[var_r31_8];
            var_r27_2 += 1;
        }
        var_r31_8 += 1;
        goto loop_44;
    }
    var_r31_9 = 0;
loop_50:
    if (var_r31_9 < 4) {
        temp_r28 = &flow->stop[var_r31_9];
        if ((s8) (u8) flow->score[var_r31_9] < 1) {
            temp_r28->target = 300.0f;
        } else {
            temp_r28->target = 100.0f + (300.0f * (f32) (s8) (u8) flow->score[var_r31_9]);
        }
        temp_r28->state = 0;
        temp_r28->speed = 0.0f;
        temp_r28->accel = 0.4f;
        temp_r28->drag = 0.01f;
        var_r31_9 += 1;
        goto loop_50;
    }
    M506YCamera->splitTime = 1.0f;
    var_r31_10 = 0;
loop_53:
    if (var_r31_10 < 4) {
        temp_r29 = &M506YCamera->camera[var_r31_10];
        temp_r29->hvr.x = 90.0f;
        temp_r29->hvr.y = 12.0f;
        temp_r29->hvr.z = 2150.0f;
        temp_r29->pos.x = 0.0f;
        temp_r29->pos.y = 300.0f;
        temp_r29->pos.z = 0.0f;
        var_r31_10 += 1;
        goto loop_53;
    }
    M506YCameraUpdate();
    M506YCameraProjUpdate();
    spC[0] = lbl_1_rodata_25C[0];
    spC[1] = lbl_1_rodata_25C[1];
    var_r31_11 = 0;
loop_62:
    if (var_r31_11 < 4) {
        if ((s8) (u8) flow->score[var_r31_11] == 0) {
            var_f31 = spC[0];
        } else {
            var_f31 = spC[flow->work->mameSide[var_r31_11][(s8) (u8) flow->score[var_r31_11] - 1]];
        }
        if ((s8) (u8) flow->score[var_r31_11] == 0) {
            var_f30 = 0.0f;
        } else {
            var_f30 = 60.0f;
        }
        flow->winPos.x = var_f31;
        flow->winPos.y = (300.0f * (f32) (s8) (u8) flow->score[var_r31_11]) + var_f30;
        flow->winPos.z = 179.5f;
        omSetTra(flow->playerObj[var_r31_11], flow->winPos.x, flow->winPos.y, flow->winPos.z);
        omSetRot(flow->playerObj[var_r31_11], 0.0f, 0.0f, 0.0f);
        var_r31_11 += 1;
        goto loop_62;
    }
    M506RocketInit(flow);
    var_r31_12 = 0;
loop_65:
    if (var_r31_12 < 4) {
        Hu3DModelAttrSet(flow->work->starfighterMdlId[var_r31_12], 1U);
        var_r31_12 += 1;
        goto loop_65;
    }
    M506StarfighterStart(flow);
}


s32 M506FlowStopCheck(M506_FLOW *flow) {
    u16 sp8[4];
    M506_STOP *temp_r31;
    M506_YCAMERA *temp_r29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r26;
    s32 var_r27;
    s32 var_r30;

    var_r26 = 0;
    var_r30 = 0;
loop_16:
    if (var_r30 < 4) {
        temp_r29 = &M506YCamera->camera[var_r30];
        temp_r31 = &flow->stop[var_r30];
        if (temp_r29->pos.y < temp_r31->target) {
            if ((s32) temp_r31->state == 0) {
                temp_r31->speed += temp_r31->accel - (temp_r31->speed * temp_r31->drag);
                var_f31 = 0.0f;
                var_f30 = temp_r31->speed;
                var_r27 = 0;
loop_5:
                if (var_r27 < 0x20) {
                    var_f31 += var_f30;
                    var_f30 *= 0.9f;
                    var_r27 += 1;
                    goto loop_5;
                }
                if (var_f31 > (temp_r31->target - temp_r29->pos.y)) {
                    temp_r31->state = 1;
                }
            } else if ((s32) temp_r31->state == 1) {
                temp_r31->speed *= 0.9f;
            }
            temp_r29->pos.y += temp_r31->speed;
            if (temp_r29->pos.y > temp_r31->target) {
                temp_r29->pos.y = temp_r31->target;
            }
        } else {
            if ((s8) (u8) flow->scoreShow[var_r30] == 0) {
                sp8[0] = lbl_1_rodata_280[0];
                sp8[1] = lbl_1_rodata_280[1];
                sp8[2] = lbl_1_rodata_280[2];
                sp8[3] = lbl_1_rodata_280[3];
                HuAudFXPlayPan(0x21, (s16) sp8[var_r30]);
            }
            flow->scoreShow[var_r30] = 1;
            var_r26 += 1;
        }
        var_r30 += 1;
        goto loop_16;
    }
    if (var_r26 == 4) {
        HuAudFXPlay(0x1E);
        return 1;
    }
    return 0;
}

s32 M506FlowResult(M506_FLOW *flow) {
    omObjData *temp_r26;
    omObjData *temp_r27;
    f32 temp_f1;
    s32 temp_r0;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    u8 temp_r0_2;
    u8 temp_r0_3;

    temp_r0 = flow->step;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        lbl_1_bss_28 = 0;
        flow->gameMesId = -1;
        if ((s32) flow->bestHeight > (s32) flow->prevRecord) {
            flow->gameMesId = GameMesCreate(0xE, flow->bestHeight * 3);
            flow->step = 1;
            flow->work0->recordVal = flow->bestHeight * 3;
            M506RecordSet(flow);
            GWMgRecordSet(0, flow->bestHeight * 3);
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                HuAudJinglePlay(0x86);
            }
        } else {
            flow->step = 2;
        }
block_46:
    default:                                        /* switch 1 */
        return 0;
    case 1:                                         /* switch 1 */
        if (GameMesStatGet(flow->gameMesId) == 0) {
            if ((s16) flow->gameMesId >= 0) {
                GameMesKill(flow->gameMesId);
            }
            flow->step = 2;
        }
        goto block_46;
    case 2:                                         /* switch 1 */
        var_r30 = 0;
loop_22:
        if (var_r30 < 4) {
            temp_r27 = M506PlayerObj[var_r30];
            temp_r0_2 = (u8) flow->winMotStep[var_r30];
            switch ((s8) temp_r0_2) {               /* switch 2; irregular */
            case 1:                                 /* switch 2 */
                break;
            case 0:                                 /* switch 2 */
                Hu3DMotionSpeedSet(*temp_r27->model, 1.0f);
                Hu3DMotionShiftSet(*temp_r27->model, temp_r27->motion[(s8) (u8) flow->winMot[var_r30]], 0.0f, 4.0f, 0U);
                flow->winMotStep[var_r30] = (u8) flow->winMotStep[var_r30] + 1;
                break;
            }
            var_r30 += 1;
            goto loop_22;
        }
        temp_f1 = FlowTime;
        FlowTime = temp_f1 + 1.0f;
        flow->gameMesId = -1;
        if ((s32) flow->winnerNum == 0) {
            flow->gameMesId = MGSeqDrawCreate();
            HuAudJinglePlay(0x7B);
            CharLoseVoicePlay((s16) flow->player[0]->charNo, (s16) flow->player[1]->charNo, (s16) flow->player[2]->charNo, (s16) flow->player[3]->charNo);
        } else {
            flow->gameMesId = GameMesCreate(4, 3, (s8) (u8) flow->winOrder[0], (s8) (u8) flow->winOrder[1], (s8) (u8) flow->winOrder[2], (s8) (u8) flow->winOrder[3], temp_f1);
            if ((s32) flow->humanWinner == 0) {
                HuAudJinglePlay(0x79);
            } else if ((s32) flow->humanWinner == 1) {
                HuAudJinglePlay(0x79);
            }
            var_r28 = 0;
loop_34:
            if (var_r28 < 4) {
                if (((s8) (u8) flow->winFlag[var_r28] == 0) && (_CheckFlag(MP5_PRACTICE_FLAG) == 0)) {
                    GWPlayer[var_r28].coin_win = 0xA;
                }
                var_r28 += 1;
                goto loop_34;
            }
        }
        flow->step = 3;
        goto block_46;
    case 3:                                         /* switch 1 */
        var_r29 = 0;
loop_43:
        if (var_r29 < 4) {
            temp_r26 = M506PlayerObj[var_r29];
            temp_r0_3 = (u8) flow->winMotStep[var_r29];
            switch ((s8) temp_r0_3) {               /* switch 3; irregular */
            case 1:                                 /* switch 3 */
                break;
            case 0:                                 /* switch 3 */
                Hu3DMotionSpeedSet(*temp_r26->model, 1.0f);
                Hu3DMotionShiftSet(*temp_r26->model, temp_r26->motion[(s8) (u8) flow->winMot[var_r29]], 0.0f, 4.0f, 0U);
                flow->winMotStep[var_r29] = (u8) flow->winMotStep[var_r29] + 1;
                break;
            }
            var_r29 += 1;
            goto loop_43;
        }
        FlowTime += 1.0f;
        if (GameMesStatGet(flow->gameMesId) == 0) {
            flow->step = 0;
            return 1;
        }
        goto block_46;
    }
}

void M506ScoreCreate(M506_FLOW *flow) {
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        flow->scoreShow[var_r30] = 0;
        flow->scoreDisp[var_r30] = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 50), DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 54), 0);
        MgScoreMaxDigitSet(flow->scoreDisp[var_r30], 3);
        MgScoreScaleSet(flow->scoreDisp[var_r30], 1.0f, 1.0f);
        MgScoreValueSet(flow->scoreDisp[var_r30], 0);
        MgScorePosSet(flow->scoreDisp[var_r30], ((f32) ScorePos[var_r30 * 3].x - 20.0f) - 8.0f, 12.0f + (f32) ScorePos[var_r30 * 3].y);
        MgScoreZRotSet(flow->scoreDisp[var_r30], 0.0f);
        MgScoreTPLvlSet(flow->scoreDisp[var_r30], 1.0f);
        MgScoreColorSet(flow->scoreDisp[var_r30], 0xFFU, 0xFFU, 0xFFU);
        MgScoreDigitWidthSet(flow->scoreDisp[var_r30], 18.0f);
        MgScorePriSet(flow->scoreDisp[var_r30], 0x100);
        MgScoreDispOff(flow->scoreDisp[var_r30]);
        HuSprBankSet(flow->scoreDisp[var_r30]->grpId, 5, 1);
        var_r30 += 1;
        goto loop_2;
    }
}

void M506ScoreDispUpdate(M506_FLOW *flow) {
    s32 var_r31;

    var_r31 = 0;
loop_6:
    if (var_r31 < 4) {
        if ((s8) (u8) flow->scoreShow[var_r31] == 0) {
            MgScoreDispOff(flow->scoreDisp[var_r31]);
        } else if ((s8) (u8) flow->scoreShow[var_r31] == 1) {
            MgScoreValueSet(flow->scoreDisp[var_r31], (s8) (u8) flow->score[var_r31] * 3);
            MgScoreDispOn(flow->scoreDisp[var_r31]);
        }
        var_r31 += 1;
        goto loop_6;
    }
}


void M506MameShadowOff(M506_FLOW *flow) {
    Hu3DModelAttrSet(flow->work->mameShadowMdlId[0], 1U);
    Hu3DModelAttrSet(flow->work->mameShadowMdlId[0], 0x40000002U);
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], 0x40000001U);
    Hu3DMotionTimeSet(flow->work->mameShadowMdlId[0], 0.0f);
    Hu3DMotionSpeedSet(flow->work->mameShadowMdlId[0], 0.5f);
    flow->shadowScroll = 0.0f;
    flow->shadowTexScrId = Hu3DTexScrollCreate(flow->work->mameShadowMdlId[0], "I8m506sdw01");
    Hu3DTexScrollPosSet(flow->shadowTexScrId, 0.0f, flow->shadowScroll, 0.0f);
    Hu3DModelAttrSet(flow->work->glowShadowMdlId, 1U);
    Hu3DModelAttrSet(flow->work->glowShadowMdlId, 0x40000002U);
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, 0x40000001U);
    Hu3DMotionTimeSet(flow->work->glowShadowMdlId, 0.0f);
    Hu3DMotionSpeedSet(flow->work->glowShadowMdlId, 1.0f);
}

void M506MameShadowOn(M506_FLOW *flow) {
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], 1U);
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], 0x40000002U);
}

void M506MameShadowScrollOn(M506_FLOW *flow) {
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, 1U);
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, 0x40000002U);
}

void M506MameShadowScrollExec(M506_FLOW *flow) {
    flow->shadowScroll += 0.0033333334f;
    if (flow->shadowScroll > 0.4f) {
        flow->shadowScroll = 0.4f;
    }
    Hu3DTexScrollPosSet(flow->shadowTexScrId, 0.0f, flow->shadowScroll, 0.0f);
}

void M506ParticleCreate(M506_FLOW *flow) {
    s32 var_r28;
    HU3DPARTICLE *temp_r29;
    HU3DPARTICLEDATA *var_r30;

    flow->particleMdlId = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M506, 32), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x20);
    temp_r29 = Hu3DData[flow->particleMdlId].hookData;
    Hu3DParticleBlendModeSet(flow->particleMdlId, 1U);
    Hu3DParticleHookSet(flow->particleMdlId, M506ParticleUpdate);
    Hu3DModelLayerSet(flow->particleMdlId, 6);
    Hu3DModelPosSet(flow->particleMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DParticleColSet(flow->particleMdlId, 0x80U, 0x40U, 0x20U);
    var_r30 = temp_r29->data;
    var_r28 = 0;
loop_2:
    if (var_r28 < (s16) temp_r29->maxCnt) {
        var_r30->time = 0;
        var_r30->scale = 0.0f;
        var_r30->color.a = 0;
        var_r28 += 1;
        var_r30++;
        goto loop_2;
    }
}

void M506ParticleUpdate(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 temp_f28_4;
    f32 temp_f28_5;
    f32 temp_f29;
    f32 temp_f29_2;
    f64 var_f31;
    s16 temp_r0;
    s16 temp_r0_2;
    s32 var_r29;

    var_r31 = particleP->data;
    var_f31 = 0.0;
    var_r29 = 0;
loop_21:
    if (var_r29 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            break;
        case 1:
            var_r31->parManId = frandmod(0x10U);
            var_r31->accel.x = 0.0f;
            var_r31->color.a = 0;
            var_r31->color.r = 0xE0;
            var_r31->color.g = 0x80;
            var_r31->color.b = 0x40;
            var_r31->scale = 0.0f;
            var_r31->zRot = 0.0f;
            temp_f28 = (f32) (frandmod(0x12CU) + 1) / 100.0f;
            var_r31->pos.x = ((f32) (frandmod(0x12CU) + 1) / 100.0f) - temp_f28;
            var_r31->pos.y = 10.0f;
            temp_f28_2 = (f32) (frandmod(0x12CU) + 1) / 100.0f;
            var_r31->pos.z = ((f32) (frandmod(0x12CU) + 1) / 100.0f) - temp_f28_2;
            temp_f29 = (f32) (frandmod(0x14U) + 1) / 100.0f;
            temp_f28_3 = (f32) (frandmod(0x14U) + 1) / 100.0f;
            var_r31->vel.x = (f32) (((0.25f * cos((3.141592653589793 * var_f31) / 180.0)) + (f64) temp_f28_3) - (f64) temp_f29);
            temp_f28_4 = (f32) (frandmod(0xAU) + 1) / 100.0f;
            var_r31->vel.y = (0.3f + ((f32) (frandmod(0xAU) + 1) / 100.0f)) - temp_f28_4;
            temp_f28_5 = (f32) (frandmod(0x14U) + 1) / 100.0f;
            temp_f29_2 = (f32) (frandmod(0x14U) + 1) / 100.0f;
            var_r31->vel.z = (f32) (((0.25f * sin((3.141592653589793 * var_f31) / 180.0)) + (f64) temp_f29_2) - (f64) temp_f28_5);
            var_f31 = (f64) ((f32) var_f31 + (360.0f / (f32) particleP->maxCnt));
            var_r31->time += 1;
            /* fallthrough */
        case 2:
            temp_r0_2 = var_r31->parManId - 1;
            var_r31->parManId = temp_r0_2;
            if (temp_r0_2 < 0) {
                var_r31->time += 1;
            }
            break;
        default:
            var_r31->scale += 0.3f;
            var_r31->pos.x += var_r31->vel.x;
            var_r31->pos.y += var_r31->vel.y;
            var_r31->pos.z += var_r31->vel.z;
            if ((s16) var_r31->time == 3) {
                var_r31->accel.x += 0.125f;
                if (var_r31->accel.x >= 1.0f) {
                    var_r31->time += 1;
                    var_r31->accel.x = 1.0f;
                }
            } else if ((s16) var_r31->time == 4) {
                var_r31->accel.x -= 0.010416667f;
                if (var_r31->accel.x <= 0.0f) {
                    var_r31->accel.x = 0.0f;
                }
            }
            var_r31->color.a = (u8) (s32) (64.0f * var_r31->accel.x);
            if (((s16) var_r31->time == 4) && (var_r31->accel.x <= 0.0f)) {
                var_r31->time = 0;
            }
            break;
        }
        var_r29 += 1;
        var_r31++;
        goto loop_21;
    }
}


void M506ParticleKill(M506_FLOW *flow) {
    Hu3DModelKill(flow->particleMdlId);
}

void M506RocketInit(M506_FLOW *flow) {
    flow->rocket.pos.x = 600.0f;
    flow->rocket.pos.y = 11100.0f;
    flow->rocket.pos.z = -2500.0f;
    flow->rocket.rot.x = 0.0f;
    flow->rocket.rot.y = 0.0f;
    flow->rocket.rot.z = 90.0f;
    if ((s32) flow->endF == 0) {
        flow->rocket.speed = 5.0f;
    } else if ((s32) flow->endF == 1) {
        flow->rocket.speed = 7.5f;
    }
    flow->rocket.state = 0;
    flow->rocket.start = 0;
}

void M506RocketUpdate(void) {
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;

    if (((s32) M506Flow.endF == 0) && ((u16) M506Flow.work->rocketCamBit == 0)) {
        var_r29 = 0;
loop_6:
        if (var_r29 < 4) {
            if ((s32) M506Flow.player[var_r29]->newHeight == 0x1E) {
                M506Flow.work->rocketCamBit |= M506CameraBit[var_r29];
            }
            var_r29 += 1;
            goto loop_6;
        }
    }
    if ((s32) M506Flow.rocket.start == 0) {
        if ((s32) M506Flow.endF == 0) {
            var_r29_2 = 0;
loop_13:
            if (var_r29_2 >= 4) {

            } else if ((s32) M506Flow.player[var_r29_2]->newHeight == 0x23) {
                M506Flow.rocket.start = 1;
                M506Flow.rocket.armed = 1;
            } else {
                var_r29_2 += 1;
                goto loop_13;
            }
        } else if (((s32) M506Flow.endF == 1) && ((s32) M506Flow.rocket.armed == 1)) {
            var_r29_3 = 0;
loop_21:
            if (var_r29_3 < 4) {
                if (M506YCamera->camera[var_r29_3].pos.y >= 9900.0f) {
                    M506Flow.rocket.start = 1;
                } else {
                    var_r29_3 += 1;
                    goto loop_21;
                }
            }
        }
    }
    switch ((s32) M506Flow.rocket.state) {          /* irregular */
    case 0:
        if ((s32) M506Flow.rocket.start != 0) {
            M506Flow.rocket.state += 1;
            return;
        }
        return;
    case 1:
        if (M506RocketModelUpdate(&M506Flow) != 0) {
            M506Flow.rocket.state += 1;
        }
        break;
    }
}

s32 M506RocketModelUpdate(M506_FLOW *flow) {
    Mtx sp14;
    Vec sp8;

    M506RocketMove(flow);
    sp8.x = 0.0f;
    sp8.y = flow->rocket.speed;
    sp8.z = 0.0f;
    M506MakeRotMtx(sp14, &flow->rocket.rot);
    MTXMultVec(sp14, &sp8, &sp8);
    flow->rocket.pos.x += sp8.x;
    flow->rocket.pos.y += sp8.y;
    flow->rocket.pos.z += sp8.z;
    Hu3DModelPosSet(flow->work->rocketMdlId, flow->rocket.pos.x, flow->rocket.pos.y, flow->rocket.pos.z);
    Hu3DModelRotSet(flow->work->rocketMdlId, flow->rocket.rot.x, flow->rocket.rot.y, flow->rocket.rot.z);
    return 0;
}

void M506RocketMove(M506_FLOW *flow) {
    switch ((s32) flow->endF) {                     /* irregular */
    case 0:
        flow->rocket.rot.x += (rotTbl_700[2] - rotTbl_700[0]) / 200.0f;
        flow->rocket.rot.z += (rotTbl_700[3] - rotTbl_700[1]) / 200.0f;
        return;
    case 1:
        flow->rocket.rot.x += (rotTbl_700[4] - rotTbl_700[0]) / 200.0f;
        flow->rocket.rot.z += (rotTbl_700[5] - rotTbl_700[1]) / 200.0f;
        return;
    }
}

void M506StarfighterStart(M506_FLOW *flow) {
    M506_STARFIGHTER *temp_r31;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31 = &flow->fighter[var_r30];
        temp_r31->pos.x = 700.0f;
        temp_r31->pos.y = 15300.0f;
        temp_r31->pos.z = -2500.0f;
        temp_r31->rot.x = -45.0f;
        temp_r31->rot.y = 0.0f;
        temp_r31->rot.z = 135.0f;
        temp_r31->speed = 16.0f;
        temp_r31->state = 0;
        temp_r31->start = 0;
        M506StarfighterModelUpdate(temp_r31, flow->work->starfighterMdlId[var_r30]);
        Hu3DModelAttrSet(flow->work->starfighterMdlId[var_r30], 1U);
        var_r30 += 1;
        goto loop_2;
    }
}

void M506StarfighterUpdate(void) {
    M506_STARFIGHTER *temp_r31;
    s32 temp_r0;
    s32 var_r29;

    var_r29 = 0;
loop_13:
    if (var_r29 < 4) {
        temp_r31 = &M506Flow.fighter[var_r29];
        if (((s32) temp_r31->start == 0) && ((s32) M506Flow.player[var_r29]->newHeight == 0x32) && ((s16) M506Flow.player[var_r29]->upJumpF == 0)) {
            Hu3DModelAttrReset(M506Flow.work->starfighterMdlId[var_r29], 1U);
            temp_r31->start = 1;
        }
        temp_r0 = temp_r31->state;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) temp_r31->start != 0) {
                temp_r31->state += 1;
            }
            break;
        case 1:
            M506StarfighterModelUpdate(temp_r31, M506Flow.work->starfighterMdlId[var_r29]);
            break;
        }
        var_r29 += 1;
        goto loop_13;
    }
}

void M506StarfighterModelUpdate(M506_STARFIGHTER *fighter, s16 mdlId) {
    Mtx sp14;
    Vec sp8;

    sp8.x = 0.0f;
    sp8.y = fighter->speed;
    sp8.z = 0.0f;
    M506MakeRotMtx(sp14, &fighter->rot);
    MTXMultVec(sp14, &sp8, &sp8);
    fighter->pos.x += sp8.x;
    fighter->pos.y += sp8.y;
    fighter->pos.z += sp8.z;
    Hu3DModelPosSet(mdlId, fighter->pos.x, fighter->pos.y, fighter->pos.z);
    Hu3DModelRotSet(mdlId, fighter->rot.x, fighter->rot.y, fighter->rot.z);
}

void M506RecordCreate(M506_FLOW *flow) {
    if (0 == 0) {
        flow->recordSprId = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M506, 30), 0, 0);
        espDispOff(flow->recordSprId);
        espPriSet(flow->recordSprId, 0x10);
        espPosSet(flow->recordSprId, 236.0f, 420.0f);
        espScaleSet(flow->recordSprId, 1.0f, 1.0f);
        espAttrSet(flow->recordSprId, 1U);
        espDispOn(flow->recordSprId);
        flow->recordScore = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 63), DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 53), 0);
        MgScoreMaxDigitSet(flow->recordScore, 3);
        MgScoreScaleSet(flow->recordScore, 1.0f, 1.0f);
        MgScoreValueSet(flow->recordScore, 0);
        MgScorePosSet(flow->recordScore, 258.0f, 420.0f);
        MgScoreZRotSet(flow->recordScore, 0.0f);
        MgScoreTPLvlSet(flow->recordScore, 1.0f);
        MgScoreColorSet(flow->recordScore, 0x42U, 0xFFU, 0x7AU);
        MgScoreDigitWidthSet(flow->recordScore, 16.0f);
        MgScoreDispOn(flow->recordScore);
        flow->recordWinId = MgScoreWinCreate(0x90, 0x28);
        MgScoreWinColorSet(flow->recordWinId, 0U, 0U, 0U);
        MgScoreWinTPLvlSet(flow->recordWinId, 0.7f);
        MgScoreWinPosSet(flow->recordWinId, 288.0f, 420.0f);
        MgScoreWinDispSet(flow->recordWinId, 1);
    }
}

void M506RecordSet(M506_FLOW *flow) {
    if (0 == 0) {
        MgScoreValueSet(flow->recordScore, (s32) flow->work0->recordVal);
    }
}


void M506RecordBlink(M506_FLOW *flow) {
    if ((0 == 0) && ((s32) flow->bestHeight > (s32) flow->prevRecord)) {
        if ((s8) RecordInitF == 0) {
            recordScale_725 += 0.02f;
            if (recordScale_725 >= 1.2f) {
                recordScale_725 = 1.2f;
                RecordInitF = 1;
            }
        } else if ((s8) RecordInitF == 1) {
            recordScale_725 -= 0.04f;
            if (recordScale_725 <= 1.0f) {
                recordScale_725 = 1.0f;
                RecordInitF = 0;
            }
        }
        espScaleSet(flow->recordSprId, recordScale_725, recordScale_725);
        MgScoreDigitScaleSet(flow->recordScore, recordScale_725, recordScale_725);
    }
}

void M506RecordBlinkInit(void) {
    if (0 == 0) {
        RecordInitF = 0;
        recordScale_725 = 1.0f;
    }
}





void M506YCameraInit(void) {
    M506_YCAMERA *temp_r31;
    M506_YCAMERA_WORK *temp_ret;
    s32 var_r30;

    temp_ret = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M506_YCAMERA_WORK), MEMORY_DEFAULT_NUM);
    M506YCamera = temp_ret;
    if ((M506_YCAMERA_WORK *) M506YCamera == NULL) {
        OSReport("M506YCameraInit Error...\n");
        return;
    }
    var_r30 = 0;
loop_4:
    if (var_r30 < 4) {
        temp_r31 = &M506YCamera->camera[var_r30];
        temp_r31->bit = (s32) M506CameraBit[var_r30];
        Hu3DCameraCreate(temp_r31->bit);
        temp_r31->center.x = 0.0f;
        temp_r31->center.y = 0.0f;
        temp_r31->center.z = 0.0f;
        temp_r31->target.x = 0.0f;
        temp_r31->target.y = 0.0f;
        temp_r31->target.z = 0.0f;
        temp_r31->hvr.x = 90.0f;
        temp_r31->hvr.y = 0.0f;
        temp_r31->hvr.z = 2000.0f;
        temp_r31->unk4C = 0.0f;
        temp_r31->pos.x = 0.0f;
        temp_r31->pos.y = 300.0f;
        temp_r31->pos.z = 0.0f;
        temp_r31->fov = 30.0f;
        var_r30 += 1;
        goto loop_4;
    }
    M506YCamera->splitTime = 1.0f;
    M506YCamera->unk1D4 = 0;
    M506YCameraSplitCreate();
    M506YCameraUpdate();
    M506YCameraProjUpdate();
}

void M506YCameraClose(void) {
    s32 var_r30;

    HuMemDirectFree(M506YCamera);
    var_r30 = 0;
loop_4:
    if (var_r30 < 4) {
        if ((MGSCORE *) M506Flow.scoreDisp[var_r30] != NULL) {
            MgScoreKill(M506Flow.scoreDisp[var_r30]);
        }
        var_r30 += 1;
        goto loop_4;
    }
    M506YCameraSplitKill();
    if (0 == 0) {
        espKill(M506Flow.recordSprId);
        if ((MGSCORE *) M506Flow.recordScore != NULL) {
            MgScoreKill(M506Flow.recordScore);
        }
    }
    Hu3DModelKill(M506Flow.particleMdlId);
    if ((s16) M506Flow.gameMesId >= 0) {
        GameMesKill(M506Flow.gameMesId);
    }
}


void M506YCameraUpdate(void) {
    f32 sp8;
    M506_YCAMERA *temp_r31;
    f64 temp_f31;
    f64 temp_f31_2;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31 = &M506YCamera->camera[var_r30];
        temp_r31->target.x = temp_r31->pos.x;
        temp_r31->target.y = temp_r31->pos.y;
        temp_r31->target.z = temp_r31->pos.z;
        temp_f31 = cos((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.x = (f32) ((f64) temp_r31->target.x + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31));
        temp_r31->center.y = (f32) ((f64) temp_r31->target.y + ((f64) temp_r31->hvr.z * sin((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0)));
        temp_f31_2 = sin((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.z = (f32) ((f64) temp_r31->target.z + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31_2));
        VECSubtract(&temp_r31->target, &temp_r31->center, &temp_r31->dir);
        VECNormalize(&temp_r31->dir, &temp_r31->dir);
        VECCrossProduct(&up_800, &temp_r31->dir, &temp_r31->upDir);
        VECNormalize(&temp_r31->upDir, &temp_r31->upDir);
        VECCrossProduct(&temp_r31->dir, &temp_r31->upDir, &temp_r31->up);
        VECNormalize(&temp_r31->up, &temp_r31->up);
        sp8 = temp_r31->target.z;
        Hu3DCameraPosSet(temp_r31->bit, temp_r31->center.x, temp_r31->center.y, temp_r31->center.z, temp_r31->up.x, temp_r31->up.y, temp_r31->up.z, temp_r31->target.x, temp_r31->target.y, temp_r31->target.z);
        var_r30 += 1;
        goto loop_2;
    }
}

void M506YCameraProjUpdate(void) {
    M506_YCAMERA *temp_r31;
    s32 var_r30;

    M506YCameraViewUpdate();
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31 = &M506YCamera->camera[var_r30];
        Hu3DCameraPerspectiveSet(temp_r31->bit, temp_r31->fov, 20.0f, 30000.0f, temp_r31->aspect);
        Hu3DCameraViewportSet(temp_r31->bit, temp_r31->viewportX, 0.0f, temp_r31->viewportW, 480.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(temp_r31->bit, (u32) temp_r31->scissorX, 0U, (u32) temp_r31->scissorW, 0x1E0U);
        var_r30 += 1;
        goto loop_2;
    }
}

void M506YCameraViewUpdate(void) {
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;

    temp_f31 = M506YCamera->splitTime;
    M506YCamera->camera[0].aspect = (151.0f + (425.0f * (1.0f - temp_f31))) / 480.0f;
    M506YCamera->camera[0].viewportX = 0.0f;
    M506YCamera->camera[0].viewportW = 160.0f + (480.0f * (1.0f - temp_f31));
    if (temp_f31 < 0.33333334f) {
        M506YCamera->camera[0].scissorX = 0.0f;
        M506YCamera->camera[0].scissorW = (f32) (s32) M506YCamera->camera[0].viewportW - 2.0f;
    } else if (temp_f31 < 1.0f) {
        M506YCamera->camera[0].scissorX = 0.0f;
        M506YCamera->camera[0].scissorW = M506YCamera->camera[0].viewportW - 2.0f;
    } else {
        M506YCamera->camera[0].scissorX = 0.0f;
        M506YCamera->camera[0].scissorW = M506YCamera->camera[0].viewportW;
    }
    M506YCamera->camera[1].aspect = 0.28541666f;
    M506YCamera->camera[1].viewportX = 160.0f;
    M506YCamera->camera[1].viewportW = 160.0f;
    if (temp_f31 < 1.0f) {
        temp_f30 = 160.0f * ((temp_f31 - 0.6666667f) / 0.33333334f);
        M506YCamera->camera[1].scissorX = 160.0f + (160.0f - temp_f30);
        M506YCamera->camera[1].scissorW = temp_f30;
    } else {
        M506YCamera->camera[1].scissorX = 161.0f;
        M506YCamera->camera[1].scissorW = 158.0f;
    }
    M506YCamera->camera[2].aspect = 0.28541666f;
    M506YCamera->camera[2].viewportX = 320.0f;
    M506YCamera->camera[2].viewportW = 160.0f;
    if (temp_f31 < 0.6666667f) {
        temp_f30_2 = 160.0f * ((temp_f31 - 0.33333334f) / 0.33333334f);
        M506YCamera->camera[2].scissorX = 320.0f + (160.0f - temp_f30_2);
        M506YCamera->camera[2].scissorW = temp_f30_2;
    } else {
        M506YCamera->camera[2].scissorX = 321.0f;
        M506YCamera->camera[2].scissorW = 158.0f;
    }
    M506YCamera->camera[3].aspect = 0.31458333f;
    M506YCamera->camera[3].viewportX = 480.0f;
    M506YCamera->camera[3].viewportW = 160.0f;
    if (temp_f31 < 0.33333334f) {
        M506YCamera->camera[3].scissorX = (f32) (0x280 - (s32) (160.0f * (temp_f31 / 0.33333334f)));
        M506YCamera->camera[3].scissorW = 640.0f - M506YCamera->camera[3].scissorX;
        return;
    }
    M506YCamera->camera[3].scissorX = 481.0f;
    M506YCamera->camera[3].scissorW = 159.0f;
}

void M506YCameraSplitCreate(void) {
    f32 sp8[3];
    s32 var_r31;

    sp8[0] = lbl_1_rodata_338[0];
    sp8[1] = lbl_1_rodata_338[1];
    sp8[2] = lbl_1_rodata_338[2];
    var_r31 = 0;
loop_2:
    if (var_r31 < 3) {
        M506YCamera->splitSprId[var_r31] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M506, 29), 0, 0);
        espDispOff(M506YCamera->splitSprId[var_r31]);
        espPriSet(M506YCamera->splitSprId[var_r31], 0x102);
        espPosSet(M506YCamera->splitSprId[var_r31], 0.0f, 240.0f);
        espPosSet(M506YCamera->splitSprId[var_r31], sp8[var_r31], 240.0f);
        espScaleSet(M506YCamera->splitSprId[var_r31], 0.6f, 1.0f);
        espAttrSet(M506YCamera->splitSprId[var_r31], 1U);
        var_r31 += 1;
        goto loop_2;
    }
}

void M506YCameraSplitKill(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 3) {
        espKill(M506YCamera->splitSprId[var_r31]);
        var_r31 += 1;
        goto loop_2;
    }
}


void M506YLightInit(void) {
    M506_YLIGHT *temp_ret;

    Hu3DLighInit();
    temp_ret = HuMemDirectMallocNum(HEAP_SYSTEM, 0x50, MEMORY_DEFAULT_NUM);
    M506YLight = temp_ret;
    if ((M506_YLIGHT *) M506YLight == NULL) {
        OSReport("M506YLightInit Error...\n");
        return;
    }
    M506YLight->hvr.x = 60.0f;
    M506YLight->hvr.y = 50.0f;
    M506YLight->hvr.z = 1000.0f;
    M506YLight->unk10.x = 0.0f;
    M506YLight->unk10.y = 0.0f;
    M506YLight->unk10.z = 0.0f;
    M506YLight->color.r = 0xE8;
    M506YLight->color.g = 0xE8;
    M506YLight->color.b = 0xE8;
    M506YLight->color.a = 0xFF;
    M506YLight->target.x = 0.0f;
    M506YLight->target.y = 20000.0f;
    M506YLight->target.z = -1000.0f;
    M506YLight->center.x = 0.0f;
    M506YLight->center.y = 0.0f;
    M506YLight->center.z = 0.0f;
    M506YLight->pos.x = M506YLight->target.x;
    M506YLight->pos.y = M506YLight->target.y;
    M506YLight->pos.z = M506YLight->target.z;
    VECSubtract(&M506YLight->center, &M506YLight->target, &M506YLight->dir);
    M506YLight->lightId = Hu3DGLightCreateV(&M506YLight->pos, &M506YLight->dir, &M506YLight->color);
    M506YLightUpdate();
    Hu3DGLightStaticSet(M506YLight->lightId, 1);
    Hu3DGLightInfinitytSet(M506YLight->lightId);
}

void M506YLightClose(void) {
    HuMemDirectFree(M506YLight);
}

void M506YLightUpdate(void) {
    f64 temp_f31;
    f64 temp_f31_2;

    M506YLight->center.x = M506YLight->unk10.x;
    M506YLight->center.y = M506YLight->unk10.y;
    M506YLight->center.z = M506YLight->unk10.z;
    temp_f31 = cos((3.141592653589793 * (f64) M506YLight->hvr.x) / 180.0);
    M506YLight->target.x = (f32) ((f64) M506YLight->center.x + ((f64) M506YLight->hvr.z * cos((3.141592653589793 * (f64) M506YLight->hvr.y) / 180.0) * temp_f31));
    M506YLight->target.y = (f32) ((f64) M506YLight->center.y + ((f64) M506YLight->hvr.z * sin((3.141592653589793 * (f64) M506YLight->hvr.y) / 180.0)));
    temp_f31_2 = sin((3.141592653589793 * (f64) M506YLight->hvr.x) / 180.0);
    M506YLight->target.z = (f32) ((f64) M506YLight->center.z + ((f64) M506YLight->hvr.z * cos((3.141592653589793 * (f64) M506YLight->hvr.y) / 180.0) * temp_f31_2));
    M506YLight->pos.x = M506YLight->target.x;
    M506YLight->pos.y = M506YLight->target.y;
    M506YLight->pos.z = M506YLight->target.z;
    VECSubtract(&M506YLight->center, &M506YLight->target, &M506YLight->dir);
    VECNormalize(&M506YLight->dir, &M506YLight->dir);
    Hu3DGLightPosSetV(M506YLight->lightId, &M506YLight->pos, &M506YLight->dir);
    Hu3DGLightColorSet(M506YLight->lightId, M506YLight->color.r, M506YLight->color.g, M506YLight->color.b, M506YLight->color.a);
}

void M506YShadowInit(void) {
    M506_YSHADOW *temp_r31;
    M506_YSHADOW_WORK *temp_ret;
    s32 var_r30;

    temp_ret = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M506_YSHADOW_WORK), MEMORY_DEFAULT_NUM);
    M506YShadow = temp_ret;
    if ((M506_YSHADOW_WORK *) M506YShadow == NULL) {
        OSReport("M506YShadowInit Error...\n");
        return;
    }
    Hu3DShadowMultiCreate(30.0f, 20.0f, 30000.0f, (s16) (M506CameraBit[3] | (M506CameraBit[2] | (M506CameraBit[0] | M506CameraBit[1]))));
    var_r30 = 0;
loop_4:
    if (var_r30 < 4) {
        temp_r31 = &M506YShadow->shadow[var_r30];
        temp_r31->bit = (s32) M506CameraBit[var_r30];
        temp_r31->tpLvl = 0.3f;
        temp_r31->hvr.x = -70.0f;
        temp_r31->hvr.y = 50.0f;
        temp_r31->hvr.z = 2000.0f;
        temp_r31->center.x = 0.0f;
        temp_r31->center.y = 0.0f;
        temp_r31->center.z = 0.0f;
        var_r30 += 1;
        goto loop_4;
    }
    M506YShadowPosUpdate();
}

void M506YShadowClose(void) {
    HuMemDirectFree(M506YShadow);
}

void M506YShadowPosUpdate(void) {
    M506_YSHADOW *temp_r31;
    f64 temp_f31;
    f64 temp_f31_2;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31 = &M506YShadow->shadow[var_r30];
        temp_r31->target.x = temp_r31->center.x;
        temp_r31->target.y = temp_r31->center.y;
        temp_r31->target.z = temp_r31->center.z;
        temp_f31 = cos((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->pos.x = (f32) ((f64) temp_r31->target.x + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31));
        temp_r31->pos.y = (f32) ((f64) temp_r31->target.y + ((f64) temp_r31->hvr.z * sin((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0)));
        temp_f31_2 = sin((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->pos.z = (f32) ((f64) temp_r31->target.z + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31_2));
        VECSubtract(&temp_r31->target, &temp_r31->pos, &temp_r31->forward);
        VECNormalize(&temp_r31->forward, &temp_r31->forward);
        VECCrossProduct(&up_1000, &temp_r31->forward, &temp_r31->upDir);
        VECNormalize(&temp_r31->upDir, &temp_r31->upDir);
        VECCrossProduct(&temp_r31->forward, &temp_r31->upDir, &temp_r31->up);
        VECNormalize(&temp_r31->up, &temp_r31->up);
        Hu3DShadowMultiTPLvlSet(temp_r31->tpLvl, (s16) temp_r31->bit);
        Hu3DShadowMultiPosSet(&temp_r31->pos, &temp_r31->up, &temp_r31->target, (s16) temp_r31->bit);
        var_r30 += 1;
        goto loop_2;
    }
}

void M506YShadowUpdate(void) {
    M506_YSHADOW *temp_r29;
    M506_YSHADOW *temp_r31;
    f64 temp_f31;
    f64 temp_f31_2;
    s32 var_r28;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r29 = &M506YShadow->shadow[var_r30];
        temp_r29->center.x = M506PlayerObj[var_r30]->trans.x;
        temp_r29->center.y = M506PlayerObj[var_r30]->trans.y;
        temp_r29->center.z = M506PlayerObj[var_r30]->trans.z;
        var_r30 += 1;
        goto loop_2;
    }
    var_r28 = 0;
loop_5:
    if (var_r28 < 4) {
        temp_r31 = &M506YShadow->shadow[var_r28];
        temp_r31->target.x = temp_r31->center.x;
        temp_r31->target.y = temp_r31->center.y;
        temp_r31->target.z = temp_r31->center.z;
        temp_f31 = cos((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->pos.x = (f32) ((f64) temp_r31->target.x + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31));
        temp_r31->pos.y = (f32) ((f64) temp_r31->target.y + ((f64) temp_r31->hvr.z * sin((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0)));
        temp_f31_2 = sin((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->pos.z = (f32) ((f64) temp_r31->target.z + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31_2));
        VECSubtract(&temp_r31->target, &temp_r31->pos, &temp_r31->forward);
        VECNormalize(&temp_r31->forward, &temp_r31->forward);
        VECCrossProduct(&up_1000, &temp_r31->forward, &temp_r31->upDir);
        VECNormalize(&temp_r31->upDir, &temp_r31->upDir);
        VECCrossProduct(&temp_r31->forward, &temp_r31->upDir, &temp_r31->up);
        VECNormalize(&temp_r31->up, &temp_r31->up);
        Hu3DShadowMultiTPLvlSet(temp_r31->tpLvl, (s16) temp_r31->bit);
        Hu3DShadowMultiPosSet(&temp_r31->pos, &temp_r31->up, &temp_r31->target, (s16) temp_r31->bit);
        var_r28 += 1;
        goto loop_5;
    }
}

void M506YCameraViewSet(s32 no, s32 view) {
    s32 sp14;
    s32 sp10;
    f32 sp8;
    M506_CAMVIEW *temp_r27;
    M506_YCAMERA *temp_r29;
    M506_YCAMERA *temp_r31;
    f64 temp_f31;
    f64 temp_f31_2;
    s32 var_r28;

    sp10 = no;
    sp14 = view;
    temp_r27 = &YCameraView[sp14];
    temp_r29 = &M506YCamera->camera[sp10];
    temp_r29->hvr.x = temp_r27->from[0];
    temp_r29->hvr.y = temp_r27->from[1];
    temp_r29->hvr.z = temp_r27->from[2];
    temp_r29->pos.x = temp_r27->from[3];
    temp_r29->pos.y = temp_r27->from[4];
    temp_r29->pos.z = temp_r27->from[5];
    var_r28 = 0;
loop_2:
    if (var_r28 < 4) {
        temp_r31 = &M506YCamera->camera[var_r28];
        temp_r31->target.x = temp_r31->pos.x;
        temp_r31->target.y = temp_r31->pos.y;
        temp_r31->target.z = temp_r31->pos.z;
        temp_f31 = cos((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.x = (f32) ((f64) temp_r31->target.x + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31));
        temp_r31->center.y = (f32) ((f64) temp_r31->target.y + ((f64) temp_r31->hvr.z * sin((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0)));
        temp_f31_2 = sin((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.z = (f32) ((f64) temp_r31->target.z + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f31_2));
        VECSubtract(&temp_r31->target, &temp_r31->center, &temp_r31->dir);
        VECNormalize(&temp_r31->dir, &temp_r31->dir);
        VECCrossProduct(&up_800, &temp_r31->dir, &temp_r31->upDir);
        VECNormalize(&temp_r31->upDir, &temp_r31->upDir);
        VECCrossProduct(&temp_r31->dir, &temp_r31->upDir, &temp_r31->up);
        VECNormalize(&temp_r31->up, &temp_r31->up);
        sp8 = temp_r31->target.z;
        Hu3DCameraPosSet(temp_r31->bit, temp_r31->center.x, temp_r31->center.y, temp_r31->center.z, temp_r31->up.x, temp_r31->up.y, temp_r31->up.z, temp_r31->target.x, temp_r31->target.y, temp_r31->target.z);
        var_r28 += 1;
        goto loop_2;
    }
}

s32 M506YCameraViewLerp(s32 no, s32 view) {
    s32 sp14;
    s32 sp10;
    f32 sp8;
    M506_CAMVIEW *temp_r26;
    M506_YCAMERA *temp_r27;
    M506_YCAMERA *temp_r31;
    f32 temp_f31;
    f64 temp_f30;
    f64 temp_f30_2;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_3;
    s32 temp_r30_4;
    s32 temp_r30_5;
    s32 temp_r30_6;
    s32 var_r25;

    sp10 = no;
    sp14 = view;
    temp_r26 = &YCameraView[sp14];
    temp_r27 = &M506YCamera->camera[sp10];
    temp_f31 = temp_r26->rate;
    temp_r30_2 = M506PointLerp(&temp_r27->hvr.x, temp_r26->from[0], temp_r26->to[0], temp_f31);
    temp_r30_3 = temp_r30_2 + M506PointLerp(&temp_r27->hvr.y, temp_r26->from[1], temp_r26->to[1], temp_f31);
    temp_r30_4 = temp_r30_3 + M506PointLerp(&temp_r27->hvr.z, temp_r26->from[2], temp_r26->to[2], temp_f31);
    temp_r30_5 = temp_r30_4 + M506PointLerp(&temp_r27->pos.x, temp_r26->from[3], temp_r26->to[3], temp_f31);
    temp_r30_6 = temp_r30_5 + M506PointLerp(&temp_r27->pos.y, temp_r26->from[4], temp_r26->to[4], temp_f31);
    temp_r30 = temp_r30_6 + M506PointLerp(&temp_r27->pos.z, temp_r26->from[5], temp_r26->to[5], temp_f31);
    var_r25 = 0;
loop_2:
    if (var_r25 < 4) {
        temp_r31 = &M506YCamera->camera[var_r25];
        temp_r31->target.x = temp_r31->pos.x;
        temp_r31->target.y = temp_r31->pos.y;
        temp_r31->target.z = temp_r31->pos.z;
        temp_f30 = cos((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.x = (f32) ((f64) temp_r31->target.x + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f30));
        temp_r31->center.y = (f32) ((f64) temp_r31->target.y + ((f64) temp_r31->hvr.z * sin((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0)));
        temp_f30_2 = sin((3.141592653589793 * (f64) temp_r31->hvr.x) / 180.0);
        temp_r31->center.z = (f32) ((f64) temp_r31->target.z + ((f64) temp_r31->hvr.z * cos((3.141592653589793 * (f64) temp_r31->hvr.y) / 180.0) * temp_f30_2));
        VECSubtract(&temp_r31->target, &temp_r31->center, &temp_r31->dir);
        VECNormalize(&temp_r31->dir, &temp_r31->dir);
        VECCrossProduct(&up_800, &temp_r31->dir, &temp_r31->upDir);
        VECNormalize(&temp_r31->upDir, &temp_r31->upDir);
        VECCrossProduct(&temp_r31->dir, &temp_r31->upDir, &temp_r31->up);
        VECNormalize(&temp_r31->up, &temp_r31->up);
        sp8 = temp_r31->target.z;
        Hu3DCameraPosSet(temp_r31->bit, temp_r31->center.x, temp_r31->center.y, temp_r31->center.z, temp_r31->up.x, temp_r31->up.y, temp_r31->up.z, temp_r31->target.x, temp_r31->target.y, temp_r31->target.z);
        var_r25 += 1;
        goto loop_2;
    }
    return temp_r30;
}

s32 M506PointLerp(f32 *value, f32 start, f32 end, f32 rate) {
    if (*value != end) {
        *value += (end - start) / rate;
        if (((start > end) && (*value < end)) || ((start < end) && (*value > end))) {
            *value = end;
            return 0;
        }
        return 1;
    }
    return 0;
}

void M506MakeRotMtx(Mtx mtx, Vec *rot) {
    Mtx sp8;
    Mtx sp38;
    Mtx sp68;
    MTXRotRad(sp68, 0x58, 0.017453292f * rot->x);
    MTXRotRad(sp38, 0x59, 0.017453292f * rot->y);
    MTXRotRad(sp8, 0x5A, 0.017453292f * rot->z);
    MTXConcat(sp8, sp68, mtx);
    MTXConcat(mtx, sp38, mtx);
}

void M506SeedUpdate(void) {
    HU3DPARTICLEDATA *var_r30;
    s32 var_r28;
    HU3DPARTICLE *temp_r29;

loop_1:
    switch ((s32) M506Flow.seedState) {             /* irregular */
    case 0:
        break;
    case 1:
        SeedInitF = 0;
        M506Flow.seedState = 2;
        break;
    case 2:
        M506Flow.seedSpeed += 0.016666668f;
        M506Flow.seedY -= 3.0f * M506Flow.seedSpeed;
        M506Flow.seedRot += 2.1f;
        if (((s32) SeedInitF == 0) && (M506Flow.seedY < 93.5f)) {
            temp_r29 = Hu3DData[M506Flow.particleMdlId].hookData;
            var_r30 = temp_r29->data;
            var_r28 = 0;
loop_12:
            if (var_r28 < (s16) temp_r29->maxCnt) {
                var_r30->time = 1;
                var_r28 += 1;
                var_r30++;
                goto loop_12;
            }
            SeedInitF = 1;
        }
        if (M506Flow.seedY < 13.5f) {
            M506Flow.seedY = 13.5f;
            SeedInitF = 0;
            M506Flow.seedState = 3;
        }
        Hu3DModelPosSet(M506Flow.work->seedMdlId, 0.0f, M506Flow.seedY, 0.0f);
        Hu3DModelRotSet(M506Flow.work->seedMdlId, M506Flow.seedRot, M506Flow.seedRot, 0.0f);
        break;
    }
    HuPrcVSleep();
    goto loop_1;
}

void M506PlayerCreate(omObjData *obj) {
    s16 var_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    memset(temp_r31, 0, 0x60);
    temp_r31->no = (u32) obj->work[0];
    temp_r31->charNo = (s32) GWPlayerCfg[temp_r31->no].character;
    temp_r31->padNo = (s32) GWPlayerCfg[temp_r31->no].pad_idx;
    temp_r31->playerType = (s16) GWPlayerCfg[temp_r31->no].iscom;
    temp_r31->comDif = (s16) GWPlayerCfg[temp_r31->no].diff;
    temp_r31->unk10 = 0;
    temp_r31->unkC = 0;
    temp_r31->height = 0;
    temp_r31->newHeight = 0;
    temp_r31->motId = 0;
    temp_r31->curDir = -1;
    temp_r31->upJumpF = 0;
    temp_r31->comMoveChance = 0;
    temp_r31->comMoveChanceMax = (s16) (ComMaxDelayTbl[temp_r31->comDif][3] + frandmod(ComMaxDelayTbl[temp_r31->comDif][4] - ComMaxDelayTbl[temp_r31->comDif][3]));
    temp_r31->comMoveChanceMax = (s16) ((temp_r31->comMoveChanceMax * 0x2D) + 0xF);
    temp_r31->pos.x = -64.5f;
    temp_r31->pos.y = 0.0f;
    temp_r31->pos.z = 179.0f;
    PlayerModeNoTbl[temp_r31->no] = 4;
    if ((s32) temp_r31->no == 0) {
        *obj->model = CharModelCreate((s16) temp_r31->charNo, 4);
    } else {
        *obj->model = CharModelCreate((s16) temp_r31->charNo, 8);
    }
    omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
    Hu3DModelShadowSet(*obj->model);
    CharModelStepFxSet((s16) temp_r31->charNo, 1);
    var_r29 = 0;
loop_5:
    if (var_r29 < 7) {
        obj->motion[var_r29] = Mp5CharMotionCreateData((s16) temp_r31->charNo, (u32) PlayerMotionTbl[Mp5CharNo(temp_r31->charNo)][var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_5;
    }
    CharMotionUpdateSet((s16) temp_r31->charNo, DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), 0);
    CharMotionVoiceOnSet((s16) temp_r31->charNo, 0x2B, 0);
    CharMotionSet((s16) temp_r31->charNo, *obj->motion);
    Hu3DModelAttrSet(*obj->model, 0x40000001U);
    Hu3DModelLayerSet(*obj->model, 5);
    Hu3DModelCameraSet(*obj->model, (u16) M506CameraBit[temp_r31->no]);
    CharEffectLayerSet(6);
    CharMotionDataClose((s16) temp_r31->charNo);
    CharModelVoicePanSet((s16) temp_r31->charNo, (s16) PlayerPanTbl[temp_r31->no]);
    obj->func = M506PlayerUpdate;
}

void M506PlayerUpdate(omObjData *obj) {
    u32 temp_r0;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    temp_r0 = M506MainObj->work[3];
    switch ((s32) temp_r0) {                        /* irregular */
    case 2:
        if ((s16) PlayerModeNoTbl[temp_r31->no] == 4) {
            M506PlayerInputRead(obj);
            if ((s16) PlayerModeNoTbl[temp_r31->no] != 4) {
                PlayerModeTbl[PlayerModeNoTbl[temp_r31->no]](obj);
                return;
            }
        case 5:
            return;
        }
        PlayerModeTbl[PlayerModeNoTbl[temp_r31->no]](obj);
        return;
    default:
        if ((s16) PlayerModeNoTbl[temp_r31->no] != 4) {
            PlayerModeTbl[PlayerModeNoTbl[temp_r31->no]](obj);
        }
        break;
    }
}

void M506PlayerMotionSet(omObjData *obj, s16 motNo) {
    M506_PLAYER_WORK *temp_r30;

    temp_r30 = obj->data;
    Hu3DModelAttrReset(*obj->model, 0x40000001U);
    Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[motNo]);
    temp_r30->motId = motNo;
    if ((u32) motNo <= 0xAU) {
        switch (motNo) {
        case 0:
        case 3:
            Hu3DModelAttrSet(*obj->model, 0x40000001U);
            /* fallthrough */
        case 2:
        case 4:
        case 5:
            Hu3DMotionSet(*obj->model, obj->motion[motNo]);
            return;
        case 7:
            /* fallthrough */
        case 8:
            M506ObjShadowMapReset(temp_r30->no, temp_r30->newHeight, temp_r30->height);
            /* fallthrough */
        case 9:
        case 10:
            Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[motNo - 7].mot], MotShiftTbl[motNo - 7].start, MotShiftTbl[motNo - 7].speed, 0U);
            break;
        }
    }
}


s32 M506PlayerInputRead(omObjData *obj) {
    s16 var_r28;
    s16 var_r29;
    s32 temp_r3;
    s32 temp_r3_2;
    M506_WORK *temp_r30;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r29 = 0;
    temp_r30 = M506MainObj->data;
    if ((s32) temp_r31->newHeight < 0x3C) {
        if ((s16) temp_r31->playerType == 0) {
            if ((s32) (HuPadBtnDown[temp_r31->padNo] & 0x100) != 0) {
                temp_r31->curDir = -1;
                var_r29 = 1;
            }
            if (((s8) (u8) HuPadStkX[temp_r31->padNo] > 0x20) && ((s32) (HuPadBtnDown[temp_r31->padNo] & 0x100) != 0)) {
                temp_r31->curDir = 1;
                var_r29 = 1;
            }
            if (((s8) (u8) HuPadStkX[temp_r31->padNo] < -0x20) && ((s32) (HuPadBtnDown[temp_r31->padNo] & 0x100) != 0)) {
                temp_r31->curDir = 0;
                var_r29 = 1;
            }
        } else if ((s16) temp_r31->playerType == 1) {
            var_r29 = M506ComInputCheck(obj);
        }
    }
    if (var_r29 != 0) {
        temp_r31->jumpTicks = 0;
        temp_r31->jumpF = 0;
        temp_r31->modeTimer = 0;
        if ((s32) temp_r31->newHeight == 0) {
            temp_r31->nextJumpF = 1;
        } else {
            temp_r31->nextJumpF = 0;
        }
        if (((s16) temp_r31->curDir != -1) && ((s16) temp_r31->curDir != (s16) temp_r31->prevDir)) {
            if ((s16) temp_r31->curDir == (s32) temp_r30->mameSide[temp_r31->no][temp_r31->newHeight]) {
                PlayerModeNoTbl[temp_r31->no] = 2;
                temp_r3 = temp_r31->newHeight + 1;
                temp_r31->newHeight = temp_r3;
                if (temp_r3 > (s32) temp_r31->height) {
                    temp_r31->height = (s32) (temp_r31->height + 1);
                    temp_r31->jumpF = 1;
                }
            } else {
                PlayerModeNoTbl[temp_r31->no] = 3;
                temp_r31->upJumpF = 1;
                if ((s32) temp_r31->newHeight != 0) {
                    temp_r31->fallLevel = (s16) (temp_r31->fallLevel + 1);
                    var_r28 = (s16) temp_r31->newHeight;
loop_23:
                    if ((s32) temp_r30->mameSide[temp_r31->no][var_r28 - 1] != (s16) temp_r31->curDir) {
                        temp_r31->fallLevel = (s16) (temp_r31->fallLevel + 1);
                        var_r28 -= 1;
                        if (var_r28 != 0) {
                            goto loop_23;
                        }
                    }
                    temp_r31->prevHeight = (s32) temp_r31->newHeight;
                    temp_r31->newHeight = (s32) var_r28;
                } else {
                    temp_r31->fallLevel = 1;
                }
            }
            temp_r31->prevDir = (s16) temp_r31->curDir;
        } else if ((s32) temp_r30->mameSide[temp_r31->no][temp_r31->newHeight] == (s16) temp_r31->prevDir) {
            PlayerModeNoTbl[temp_r31->no] = 0;
            temp_r3_2 = temp_r31->newHeight + 1;
            temp_r31->newHeight = temp_r3_2;
            if (temp_r3_2 > (s32) temp_r31->height) {
                temp_r31->height = (s32) (temp_r31->height + 1);
                temp_r31->jumpF = 1;
            }
        } else {
            PlayerModeNoTbl[temp_r31->no] = 1;
            temp_r31->upJumpF = 1;
        }
    }
    return 0;
}

s32 M506PlayerModeNormalJump(omObjData *obj) {
    s16 temp_r0_2;
    s32 temp_r0;
    s32 var_r25;
    M506_PLAYER_WORK *temp_r26;
    M506_PLAYER_WORK *temp_r27;
    M506_PLAYER_WORK *temp_r28;
    M506_PLAYER_WORK *temp_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r25 = 0;
    temp_r31->jumpTicks = (s32) (temp_r31->jumpTicks + 1);
    temp_r31->modeTimer = (s16) (temp_r31->modeTimer + 1);
    M506MameUpdate((M506_PLAYER_WORK *) temp_r31);
    temp_r0 = temp_r31->no;
    M506YCamera->camera[temp_r0].pos.y += 10.0f;
    temp_r0_2 = temp_r31->mode;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        temp_r29 = obj->data;
        Hu3DModelAttrReset(*obj->model, 0x40000001U);
        Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[9]);
        temp_r29->motId = 9;
        Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[2].mot], MotShiftTbl[2].start, MotShiftTbl[2].speed, 0U);
        temp_r31->mode = (s16) (temp_r31->mode + 1);
        temp_r31->jumpTimer = 0;
        M506ObjShadowMapSet(temp_r31->no, temp_r31->newHeight);
        /* fallthrough */
    case 1:
        if ((s32) temp_r31->newHeight != 1) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpUpSpeedTbl[temp_r31->jumpTimer]);
        } else {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + (4.8f + JumpUpSpeedTbl[temp_r31->jumpTimer]));
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        if ((s16) temp_r31->modeTimer > 0xE) {
            temp_r28 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[2]);
            temp_r28->motId = 2;
            Hu3DMotionSet(*obj->model, obj->motion[2]);
            temp_r31->mode = (s16) (temp_r31->mode + 1);
            temp_r31->jumpTimer = 0;
        }
        break;
    case 2:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->jumpTimer < 8) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if ((s16) temp_r31->jumpTimer >= 7) {
                CharModelLandDustCreate((s16) temp_r31->charNo, &temp_r31->pos);
                omVibrate((s16) temp_r31->no, 0xC, 6, 6);
            }
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        if ((s16) temp_r31->modeTimer > 0x1A) {
            temp_r27 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[7]);
            temp_r27->motId = 7;
            M506ObjShadowMapReset(temp_r27->no, temp_r27->newHeight, temp_r27->height);
            Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl->mot], MotShiftTbl->start, MotShiftTbl->speed, 0U);
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 3:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->modeTimer > 0x1D) {
            temp_r26 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[0]);
            temp_r26->motId = 0;
            Hu3DModelAttrSet(*obj->model, 0x40000001U);
            Hu3DMotionSet(*obj->model, obj->motion[0]);
            temp_r31->mode = 0;
            temp_r31->curDir = -1;
            PlayerModeNoTbl[temp_r31->no] = 4;
            var_r25 = 1;
        }
        break;
    }
    M506MameModeJump((M506_PLAYER_WORK *) temp_r31);
    return var_r25;
}

s32 M506PlayerModeUpJump(omObjData *obj) {
    s16 temp_r0;
    s32 var_r25;
    M506_PLAYER_WORK *temp_r26;
    M506_PLAYER_WORK *temp_r27;
    M506_PLAYER_WORK *temp_r28;
    M506_PLAYER_WORK *temp_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r25 = 0;
    temp_r31->modeTimer = (s16) (temp_r31->modeTimer + 1);
    temp_r0 = temp_r31->mode;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r29 = obj->data;
        Hu3DModelAttrReset(*obj->model, 0x40000001U);
        Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[9]);
        temp_r29->motId = 9;
        Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[2].mot], MotShiftTbl[2].start, MotShiftTbl[2].speed, 0U);
        temp_r31->jumpTimer = 0;
        temp_r31->mode = (s16) (temp_r31->mode + 1);
        /* fallthrough */
    case 1:
        if ((s16) temp_r31->nextJumpF == 0) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpUpSpeedTbl[temp_r31->jumpTimer]);
        } else {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + (4.8f + JumpUpSpeedTbl[temp_r31->jumpTimer]));
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        if ((s16) temp_r31->modeTimer > 0xE) {
            temp_r31->jumpTimer = 0;
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 2:
        if ((s16) temp_r31->jumpTimer < 8) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
        } else if ((s16) temp_r31->nextJumpF == 0) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
        } else {
            temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
        }
        omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        if ((s16) temp_r31->modeTimer > 0x1D) {
            temp_r28 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[2]);
            temp_r28->motId = 2;
            Hu3DMotionSet(*obj->model, obj->motion[2]);
            temp_r31->jumpTimer = 0;
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 3:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->jumpTimer < 8) {
            if ((s16) temp_r31->nextJumpF == 0) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
            } else {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
            }
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if ((s16) temp_r31->jumpTimer >= 7) {
                CharModelLandDustCreate((s16) temp_r31->charNo, &temp_r31->pos);
                omVibrate((s16) temp_r31->no, 0xC, 6, 6);
            }
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        if ((s16) temp_r31->modeTimer > 0x29) {
            temp_r27 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[7]);
            temp_r27->motId = 7;
            M506ObjShadowMapReset(temp_r27->no, temp_r27->newHeight, temp_r27->height);
            Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl->mot], MotShiftTbl->start, MotShiftTbl->speed, 0U);
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 4:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->modeTimer > 0x2C) {
            temp_r26 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[0]);
            temp_r26->motId = 0;
            Hu3DModelAttrSet(*obj->model, 0x40000001U);
            Hu3DMotionSet(*obj->model, obj->motion[0]);
            temp_r31->mode = 0;
            temp_r31->curDir = -1;
            PlayerModeNoTbl[temp_r31->no] = 4;
            var_r25 = 1;
        }
        break;
    }
    return var_r25;
}

s32 M506PlayerModeSideJump(omObjData *obj) {
    s16 temp_r0_2;
    s32 temp_r0;
    s32 var_r25;
    M506_PLAYER_WORK *temp_r26;
    M506_PLAYER_WORK *temp_r27;
    M506_PLAYER_WORK *temp_r28;
    M506_PLAYER_WORK *temp_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r25 = 0;
    temp_r0 = temp_r31->no;
    M506YCamera->camera[temp_r0].pos.y += 10.0f;
    temp_r31->jumpTicks = (s32) (temp_r31->jumpTicks + 1);
    temp_r31->modeTimer = (s16) (temp_r31->modeTimer + 1);
    M506MameUpdate((M506_PLAYER_WORK *) temp_r31);
    temp_r0_2 = temp_r31->mode;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        temp_r29 = obj->data;
        Hu3DModelAttrReset(*obj->model, 0x40000001U);
        Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[9]);
        temp_r29->motId = 9;
        Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[2].mot], MotShiftTbl[2].start, MotShiftTbl[2].speed, 0U);
        temp_r31->jumpTimer = 0;
        temp_r31->mode = (s16) (temp_r31->mode + 1);
        M506ObjShadowMapSet(temp_r31->no, temp_r31->newHeight);
        /* fallthrough */
    case 1:
        if ((s16) temp_r31->curDir == 0) {
            temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
        } else {
            temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
        }
        if ((s32) temp_r31->newHeight != 1) {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpUpSpeedTbl[temp_r31->jumpTimer]);
        } else {
            temp_r31->pos.y = (f32) (temp_r31->pos.y + (4.8f + JumpUpSpeedTbl[temp_r31->jumpTimer]));
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        if ((s16) temp_r31->modeTimer > 0xE) {
            temp_r28 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[2]);
            temp_r28->motId = 2;
            Hu3DMotionSet(*obj->model, obj->motion[2]);
            temp_r31->jumpTimer = 0;
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 2:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->jumpTimer < 8) {
            if ((s16) temp_r31->curDir == 0) {
                temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
            } else {
                temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
            }
            temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if ((s16) temp_r31->jumpTimer >= 7) {
                CharModelLandDustCreate((s16) temp_r31->charNo, &temp_r31->pos);
                omVibrate((s16) temp_r31->no, 0xC, 6, 6);
            }
        }
        temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
        if ((s16) temp_r31->modeTimer > 0x1A) {
            temp_r27 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[7]);
            temp_r27->motId = 7;
            M506ObjShadowMapReset(temp_r27->no, temp_r27->newHeight, temp_r27->height);
            Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl->mot], MotShiftTbl->start, MotShiftTbl->speed, 0U);
            temp_r31->jumpTimer = 0;
            temp_r31->mode = (s16) (temp_r31->mode + 1);
        }
        break;
    case 3:
        M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
        if ((s16) temp_r31->modeTimer > 0x1D) {
            temp_r26 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[0]);
            temp_r26->motId = 0;
            Hu3DModelAttrSet(*obj->model, 0x40000001U);
            Hu3DMotionSet(*obj->model, obj->motion[0]);
            temp_r31->mode = 0;
            temp_r31->curDir = -1;
            PlayerModeNoTbl[temp_r31->no] = 4;
            var_r25 = 1;
        }
        break;
    }
    return var_r25;
}

s32 M506PlayerModeFall(omObjData *obj) {
    s32 sp24;
    u32 sp20;
    s32 sp1C;
    u32 sp18;
    s32 sp14;
    s32 sp10;
    u32 spC;
    s32 sp8;
    s16 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 var_r19;
    M506_PLAYER_WORK *temp_r20;
    M506_PLAYER_WORK *temp_r21;
    M506_PLAYER_WORK *temp_r22;
    M506_PLAYER_WORK *temp_r23;
    M506_PLAYER_WORK *temp_r24;
    M506_PLAYER_WORK *temp_r25;
    M506_PLAYER_WORK *temp_r26;
    M506_PLAYER_WORK *temp_r27;
    M506_PLAYER_WORK *temp_r28;
    M506_PLAYER_WORK *temp_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r19 = 0;
    temp_r31->modeTimer = (s16) (temp_r31->modeTimer + 1);
    temp_r0 = temp_r31->mode;
    if ((u32) temp_r0 <= 0xAU) {
        switch (temp_r0) {
        case 0:
            temp_r29 = obj->data;
            Hu3DModelAttrReset(*obj->model, 0x40000001U);
            Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[9]);
            temp_r29->motId = 9;
            Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[2].mot], MotShiftTbl[2].start, MotShiftTbl[2].speed, 0U);
            temp_r31->jumpTimer = 0;
            temp_r31->mode = (s16) (temp_r31->mode + 1);
            /* fallthrough */
        case 1:
            M506MameModeMiss((M506_PLAYER_WORK *) temp_r31);
            if ((s16) temp_r31->curDir == 0) {
                temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
            } else {
                temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
            }
            if ((s16) temp_r31->nextJumpF == 0) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpUpSpeedTbl[temp_r31->jumpTimer]);
            } else {
                temp_r31->pos.y = (f32) (temp_r31->pos.y + (4.8f + JumpUpSpeedTbl[temp_r31->jumpTimer]));
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if ((s16) temp_r31->modeTimer > 0xE) {
                if ((s16) temp_r31->nextJumpF == 0) {
                    temp_r28 = obj->data;
                    Hu3DModelAttrReset(*obj->model, 0x40000001U);
                    Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[8]);
                    temp_r28->motId = 8;
                    M506ObjShadowMapReset(temp_r28->no, temp_r28->newHeight, temp_r28->height);
                    Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[1].mot], MotShiftTbl[1].start, MotShiftTbl[1].speed, 0U);
                    FallStartSeNo[temp_r31->no] = HuAudFXPlay(FallStartFXTbl[temp_r31->no]);
                    HuAudFXPanning(FallStartSeNo[temp_r31->no], (s16) PlayerPanTbl[temp_r31->no]);
                    CharFallSeNo[temp_r31->no] = HuAudFXPlay(CharFallFXTbl[Mp5CharNo(temp_r31->charNo)]);
                    HuAudFXPanning(CharFallSeNo[temp_r31->no], (s16) PlayerPanTbl[temp_r31->no]);
                    temp_r31->mode = (s16) (temp_r31->mode + 1);
                } else {
                    temp_r31->mode = 8;
                }
                temp_r31->fallTime = 0;
                temp_r31->jumpTimer = 0;
            }
            break;
        case 2:
            M506MameModeMiss((M506_PLAYER_WORK *) temp_r31);
            temp_r31->fallTime = (s16) (temp_r31->fallTime + 1);
            if ((s32) temp_r31->newHeight != 0) {
                if ((s16) temp_r31->jumpTimer < 8) {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
                } else {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
                }
            } else if ((s16) temp_r31->jumpTimer < 8) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
            } else if ((s32) ((temp_r31->fallLevel * 0xF) - temp_r31->fallTime) < 0xF) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
            } else {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
            }
            if ((s16) temp_r31->jumpTimer < 8) {
                if ((s16) temp_r31->curDir == 0) {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
                } else {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
                }
            }
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if (((s16) temp_r31->jumpTimer > 7) && ((s16) temp_r31->fallTime <= (s32) (((temp_r31->fallLevel - 1) * 0xF) + 8))) {
                temp_r0_2 = temp_r31->no;
                M506YCamera->camera[temp_r0_2].pos.y -= 20.0f;
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->modeTimer > 0x13) {
                temp_r27 = obj->data;
                sp24 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[3]);
                temp_r27->motId = 3;
                Hu3DModelAttrSet(*obj->model, 0x40000001U);
                Hu3DMotionSet(*obj->model, obj->motion[3]);
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 3:
            if ((s16) temp_r31->modeTimer < 0x1F) {
                M506MameModeMiss((M506_PLAYER_WORK *) temp_r31);
            }
            temp_r31->fallTime = (s16) (temp_r31->fallTime + 1);
            if ((s32) temp_r31->newHeight != 0) {
                if ((s16) temp_r31->jumpTimer < 8) {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
                } else {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
                }
            } else if ((s16) temp_r31->jumpTimer < 8) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
            } else if ((s32) ((temp_r31->fallLevel * 0xF) - temp_r31->fallTime) < 0xF) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
            } else {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
            }
            if ((s16) temp_r31->jumpTimer < 8) {
                if ((s16) temp_r31->curDir == 0) {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
                } else {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
                }
            }
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            if (((s16) temp_r31->jumpTimer > 7) && ((s16) temp_r31->fallTime <= (s32) (((temp_r31->fallLevel - 1) * 0xF) + 8))) {
                temp_r0_3 = temp_r31->no;
                M506YCamera->camera[temp_r0_3].pos.y -= 20.0f;
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->fallTime >= (s32) (temp_r31->fallLevel * 0xF)) {
                temp_r31->jumpTimer = 0;
                temp_r31->prevFallTime = (s16) temp_r31->fallTime;
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 4:
            if ((s16) temp_r31->modeTimer < 0x1F) {
                M506MameModeMiss((M506_PLAYER_WORK *) temp_r31);
            }
            if ((s16) temp_r31->jumpTimer < 8) {
                M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
                if ((s16) temp_r31->nextJumpF == 0) {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y - 20.0f);
                } else {
                    temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
                }
                omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
                if ((s16) temp_r31->jumpTimer >= 7) {
                    CharModelLandDustCreate((s16) temp_r31->charNo, &temp_r31->pos);
                    omVibrate((s16) temp_r31->no, 0xC, 4, 2);
                }
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            temp_r31->fallTime = (s16) (temp_r31->fallTime + 1);
            if ((s16) temp_r31->fallTime <= (s32) (((temp_r31->fallLevel - 1) * 0xF) + 8)) {
                temp_r0_4 = temp_r31->no;
                M506YCamera->camera[temp_r0_4].pos.y -= 20.0f;
            }
            if ((s16) temp_r31->jumpTimer >= 9) {
                temp_r31->fallTime = 0;
                temp_r31->jumpTimer = 0;
                temp_r31->mode = (s16) (temp_r31->mode + 1);
                FallEndSeNo[temp_r31->no] = HuAudFXPlay(FallEndFXTbl[temp_r31->no]);
                HuAudFXPanning(FallEndSeNo[temp_r31->no], (s16) PlayerPanTbl[temp_r31->no]);
            }
            break;
        case 5:
            if ((s16) temp_r31->jumpTimer < 7) {
                M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
                temp_r31->pos.y = (f32) (temp_r31->pos.y + BounceUpSpeedTbl[temp_r31->jumpTimer]);
                omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->jumpTimer >= 7) {
                temp_r26 = obj->data;
                sp20 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[10]);
                temp_r26->motId = 0xA;
                Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl[3].mot], MotShiftTbl[3].start, MotShiftTbl[3].speed, sp20);
                temp_r31->jumpTimer = 0;
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 6:
            if ((s16) temp_r31->jumpTimer < 8) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y + BounceDownSpeedTbl[temp_r31->jumpTimer]);
                omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->jumpTimer >= 0xC) {
                temp_r25 = obj->data;
                sp1C = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[2]);
                temp_r25->motId = 2;
                Hu3DMotionSet(*obj->model, obj->motion[2]);
                Hu3DMotionTimeSet(*obj->model, Hu3DMotionMotionMaxTimeGet(*obj->model));
                temp_r24 = obj->data;
                sp18 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[7]);
                temp_r24->motId = 7;
                sp18 = 0;
                M506ObjShadowMapReset(temp_r24->no, temp_r24->newHeight, temp_r24->height);
                Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl->mot], MotShiftTbl->start, MotShiftTbl->speed, sp18);
                temp_r31->jumpTimer = 1;
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 7:
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->jumpTimer > 3) {
                temp_r23 = obj->data;
                sp14 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[0]);
                temp_r23->motId = 0;
                Hu3DModelAttrSet(*obj->model, 0x40000001U);
                Hu3DMotionSet(*obj->model, obj->motion[0]);
                temp_r31->mode = 0;
                temp_r31->fallLevel = 0;
                temp_r31->curDir = -1;
                PlayerModeNoTbl[temp_r31->no] = 4;
                var_r19 = 1;
            }
            break;
        case 8:
            M506MameModeMiss((M506_PLAYER_WORK *) temp_r31);
            if ((s16) temp_r31->jumpTimer < 8) {
                if ((s16) temp_r31->curDir == 0) {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x - 5.6f);
                } else {
                    temp_r31->pos.x = (f32) (temp_r31->pos.x + 5.6f);
                }
                temp_r31->pos.y = (f32) (temp_r31->pos.y + JumpDownSpeedTbl[temp_r31->jumpTimer]);
            } else {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
            }
            omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->modeTimer > 0x1D) {
                temp_r22 = obj->data;
                sp10 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[2]);
                temp_r22->motId = 2;
                Hu3DMotionSet(*obj->model, obj->motion[2]);
                temp_r31->jumpTimer = 0;
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 9:
            M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
            if ((s16) temp_r31->jumpTimer < 8) {
                temp_r31->pos.y = (f32) (temp_r31->pos.y - 24.8f);
                omSetTra(obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
                if ((s16) temp_r31->jumpTimer >= 7) {
                    CharModelLandDustCreate((s16) temp_r31->charNo, &temp_r31->pos);
                    omVibrate((s16) temp_r31->no, 0xC, 6, 6);
                }
            }
            temp_r31->jumpTimer = (s16) (temp_r31->jumpTimer + 1);
            if ((s16) temp_r31->modeTimer > 0x29) {
                temp_r21 = obj->data;
                spC = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[7]);
                temp_r21->motId = 7;
                spC = 0;
                M506ObjShadowMapReset(temp_r21->no, temp_r21->newHeight, temp_r21->height);
                Hu3DMotionShiftSet(*obj->model, obj->motion[(s32) MotShiftTbl->mot], MotShiftTbl->start, MotShiftTbl->speed, spC);
                temp_r31->mode = (s16) (temp_r31->mode + 1);
            }
            break;
        case 10:
            M506MameModeEnter((M506_PLAYER_WORK *) temp_r31);
            if ((s16) temp_r31->modeTimer > 0x2C) {
                temp_r20 = obj->data;
                sp8 = 0;
                Hu3DModelAttrReset(*obj->model, 0x40000001U);
                Hu3DMotionSpeedSet(*obj->model, MotSpeedTbl[0]);
                temp_r20->motId = 0;
                Hu3DModelAttrSet(*obj->model, 0x40000001U);
                Hu3DMotionSet(*obj->model, obj->motion[0]);
                temp_r31->mode = 0;
                temp_r31->fallLevel = 0;
                temp_r31->curDir = -1;
                PlayerModeNoTbl[temp_r31->no] = 4;
                var_r19 = 1;
            }
            break;
        }
    }
    return var_r19;
}

s16 M506ComInputDelayGet(omObjData *obj) {
    s16 sp8;
    s16 var_r27;
    s16 var_r28;
    s16 var_r30;
    s16 var_r30_2;
    M506_WORK *temp_r26;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    temp_r26 = M506MainObj->data;
    sp8 = 0;
    if ((s16) temp_r31->prevDir == (s32) temp_r26->mameSide[temp_r31->no][temp_r31->newHeight]) {
        if ((s16) temp_r31->prevDir == 1) {
            var_r27 = 0;
        } else {
            var_r27 = 1;
        }
        if ((s32) temp_r31->newHeight != 0) {
            var_r30_2 = 1;
            var_r28 = (s16) temp_r31->newHeight;
loop_6:
            if ((s32) temp_r26->mameSide[temp_r31->no][var_r28 - 1] != var_r27) {
                var_r30_2 += 1;
                var_r28 -= 1;
                if (var_r28 != 0) {
                    goto loop_6;
                }
            }
        } else {
            var_r30_2 = 1;
        }
    } else {
        var_r30_2 = 1;
    }
    if (var_r30_2 >= 2) {
        var_r30 = (var_r30_2 * 0x2D) + 0xF;
    } else {
        var_r30 = var_r30_2 * 0x2D;
    }
    return var_r30;
}

s16 M506ComInputCheck(omObjData *obj) {
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 var_r28;
    s16 var_r30;
    M506_WORK *temp_r29;
    M506_PLAYER_WORK *temp_r31;

    temp_r31 = obj->data;
    var_r28 = 0;
    var_r30 = -1;
    temp_r29 = M506MainObj->data;
    temp_r0 = temp_r31->comMode;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->comDelayMax = (s16) (ComMaxDelayTbl[temp_r31->comDif][0] + frandmod(ComMaxDelayTbl[temp_r31->comDif][1] - ComMaxDelayTbl[temp_r31->comDif][0]));
        if ((s16) temp_r31->nextJumpF == 1) {
            temp_r3 = temp_r31->comDelayMax;
            temp_r31->comDelayMax = (s16) ((s32) (((u32) temp_r3 >> 0x1FU) + temp_r3) >> 1);
        }
        if ((s16) temp_r31->jumpF == 0) {
            temp_r3_2 = temp_r31->comDelayMax;
            temp_r31->comDelayMax = (s16) ((s32) (((u32) temp_r3_2 >> 0x1FU) + temp_r3_2) >> 1);
        } else if ((s16) temp_r31->comRecoverF != 0) {
            temp_r3_3 = temp_r31->comDelayMax;
            temp_r31->comDelayMax = (s16) ((s32) (((u32) temp_r3_3 >> 0x1FU) + temp_r3_3) >> 1);
        }
        temp_r31->comMode = (s16) (temp_r31->comMode + 1);
        /* fallthrough */
    case 1:
        temp_r0_2 = temp_r31->comDelay + 1;
        temp_r31->comDelay = temp_r0_2;
        if ((s16) temp_r31->comDelayMax <= temp_r0_2) {
            if (frandmod(0x64U) <= (u32) ComMaxDelayTbl[temp_r31->comDif][2]) {
                var_r30 = 1;
            } else {
                temp_r3_4 = M506ComInputDelayGet(obj);
                if ((s32) (temp_r3_4 + temp_r31->comMoveChance) > (s16) temp_r31->comMoveChanceMax) {
                    var_r30 = 1;
                } else {
                    var_r30 = 0;
                    temp_r31->comMoveChance = (s16) (temp_r31->comMoveChance + temp_r3_4);
                }
            }
            if ((s16) temp_r31->nextJumpF == 1) {
                var_r30 = 1;
            }
            if ((s16) temp_r31->jumpF == 0) {
                var_r30 = 1;
            } else if ((s16) temp_r31->comRecoverF != 0) {
                temp_r31->comRecoverF = 0;
                var_r30 = 1;
            }
            temp_r31->comMode = 0;
            temp_r31->comDelayMax = 0;
            temp_r31->comDelay = 0;
        }
        break;
    }
    if (var_r30 == 1) {
        temp_r31->curDir = (s16) temp_r29->mameSide[temp_r31->no][temp_r31->newHeight];
        var_r28 = 1;
    } else if (var_r30 == 0) {
        if ((u8) temp_r29->mameSide[temp_r31->no][temp_r31->newHeight] == 0) {
            temp_r31->curDir = 1;
        } else if ((u8) temp_r29->mameSide[temp_r31->no][temp_r31->newHeight] == 1) {
            temp_r31->curDir = 0;
        }
        temp_r31->comRecoverF = 1;
        var_r28 = 1;
    }
    return var_r28;
}
