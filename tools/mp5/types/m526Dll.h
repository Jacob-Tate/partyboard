// m2c context for m526Dll; started by tools/mp5/infer.py from the draft, then reviewed
typedef struct M526BombWork { // size 0x40
    s32 unk0; // ?
    HUPROCESS *unk4;
    s32 unk8; // ?
    s32 unkC; // ?
    s32 unk10; // ?
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38; // ?
    char pad3A[0x2];
    s32 unk3C; // ?
} M526BombWork;

typedef struct M526FuseWork { // size 0x40
    s32 unk0; // ?
    s32 unk4;
    s32 unk8;
    s32 unkC;
    HUPROCESS *unk10;
    s16 unk14; // ?
    s16 unk16; // ?
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s32 unk34; // ?
    s32 unk38; // ?
    s32 unk3C; // ?
} M526FuseWork;

typedef struct M526SmokeWork { // size 0x1C
    s32 unk0; // ?
    HUPROCESS *unk4;
    s32 unk8; // ?
    Vec unkC; // pos
    s16 unk18; // ?
    char pad1A[0x2];
} M526SmokeWork;

typedef struct M526StageWork { // malloc'd as 0x44, but StagePosSet writes unk2C[2..3] (out of bounds on GC)
    s32 unk0; // mode
    HUPROCESS *unk4;
    s16 unk8[8]; // models
    s16 unk18; // camera bit
    s32 unk1C;
    f32 unk20, unk24, unk28; // pos
    Vec unk2C[4];
} M526StageWork;

typedef struct M526CamParam { // 0x34; also playerCameraTbl entries
    Vec unk0; // target
    Vec unkC; // rot
    f32 unk18; // distance
    Vec unk1C; // eye
    Vec unk28; // up
} M526CamParam;

typedef struct M526CameraWork {
    s32 unk0; // mode
    HUPROCESS *unk4;
    M526CamParam unk8[3]; // current, from, to
    s32 unkA4;
    s32 unkA8; // move time
    s16 unkAC; // camera bit
} M526CameraWork;

typedef struct M526PlayerWork { // size 0x94
    s32 unk0; // mode
    HUPROCESS *unk4;
    Vec unk8; // pos
    Vec unk14; // walk target
    Vec unk20; // rot
    Vec unk2C; // velocity
    f32 unk38;
    s32 unk3C; // ?
    s16 unk40; // ?
    char pad42[0x2];
    s16 unk44; // ?
    char pad46[0x2];
    s32 unk48; // ?
    s32 unk4C;
    s16 unk50; // ?
    s16 unk52[10]; // motions
    s16 unk66; // motion slot
    f32 unk68;
    s32 unk6C; // ?
    s32 unk70; // ?
    s32 unk74; // ?
    s32 unk78; // ?
    f32 unk7C;
    s16 unk80; // ?
    char pad82[0x2];
    s32 unk84; // ?
    s32 unk88;
    struct M526FuseWork *unk8C; // held fuse
    s16 unk90; // ?
    char pad92[0x2];
} M526PlayerWork;

typedef struct M526GameFlowWork { // size 0xC
    s32 unk0; // ?
    HUPROCESS *unk4;
    s16 unk8[2]; // array, count guessed
} M526GameFlowWork;

typedef struct M526KingBombWork { // size 0x28
    s32 unk0; // ?
    HUPROCESS *unk4;
    s32 unk8; // ?
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18[6]; // models
    s16 unk24[2]; // motions
} M526KingBombWork;

typedef struct M526ExplosionBombWork { // size 0x20
    s32 unk0; // ?
    HUPROCESS *unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14[2]; // models
    s16 unk18[2]; // motions
    s32 unk1C; // ?
} M526ExplosionBombWork;

// var M526BombCreate temp_r3: M526BombWork
// var M526BombCreate temp_ret: M526BombWork
// var M526BombExit temp_r3: M526BombWork
// var M526BombExit temp_r3_2: M526BombWork
// var M526BombFollow temp_r3_2: M526BombWork
// var M526BombFollow temp_r3_3: M526BombWork
// var M526BombLaunch temp_r3: M526BombWork
// var M526BombLaunch temp_r3_2: M526BombWork
// var M526BombLaunch temp_r3_3: M526BombWork
// var M526BombMain temp_r31: M526BombWork
// var M526BombModeRotate temp_r3: M526BombWork
// var M526BombModeWait temp_r3: M526BombWork
// var M526CameraCreate temp_r3: M526CameraWork
// var M526CameraCreate temp_ret: M526CameraWork
// var M526CameraMain temp_r31: M526CameraWork
// var M526CameraMove temp_r3: M526CameraWork
// var M526CameraWait temp_r3: M526CameraWork
// var M526ExplosionBombCreate temp_r3: M526ExplosionBombWork
// var M526ExplosionBombCreate temp_ret: M526ExplosionBombWork
// var M526ExplosionBombExplode temp_r3: M526ExplosionBombWork
// var M526ExplosionBombExplode temp_r3_2: M526ExplosionBombWork
// var M526ExplosionBombExplode temp_r3_3: M526ExplosionBombWork
// var M526ExplosionBombMain temp_r31: M526ExplosionBombWork
// var M526ExplosionBombWalk temp_r3: M526ExplosionBombWork
// var M526FuseCreate temp_r3: M526FuseWork
// var M526FuseCreate temp_ret: M526FuseWork
// var M526FuseExplode temp_r3: M526FuseWork
// var M526FuseIdle temp_r3: M526FuseWork
// var M526FuseMain temp_r31: M526FuseWork
// var M526FuseStop temp_r3: M526FuseWork
// var M526FuseStop temp_r3_2: M526FuseWork
// var M526FuseWait temp_r3: M526FuseWork
// var M526GameFlowCreate temp_r3: M526GameFlowWork
// var M526GameFlowCreate temp_ret: M526GameFlowWork
// var M526GameFlowFinish temp_r3: M526GameFlowWork
// var M526GameFlowFinish temp_r3_2: M526GameFlowWork
// var M526GameFlowFinish temp_r3_3: M526GameFlowWork
// var M526GameFlowFinish temp_r3_4: M526GameFlowWork
// var M526GameFlowFinish temp_r3_5: M526GameFlowWork
// var M526GameFlowFinish temp_r3_6: M526GameFlowWork
// var M526GameFlowFinish temp_r3_7: M526GameFlowWork
// var M526GameFlowFinish temp_r3_8: M526GameFlowWork
// var M526GameFlowFinish temp_r3_9: M526GameFlowWork
// var M526GameFlowMain temp_r31: M526GameFlowWork
// var M526GameFlowPlay temp_r3: M526GameFlowWork
// var M526GameFlowStart temp_r3: M526GameFlowWork
// var M526GameFlowStart temp_r3_2: M526GameFlowWork
// var M526GameFlowStart temp_r3_3: M526GameFlowWork
// var M526GameFlowStart temp_r3_4: M526GameFlowWork
// var M526GameFlowStart temp_r3_5: M526GameFlowWork
// var M526GameFlowStart temp_r3_6: M526GameFlowWork
// var M526GameFlowStart temp_r3_7: M526GameFlowWork
// var M526GameFlowWait temp_r3: M526GameFlowWork
// var M526KingBombCreate temp_r3: M526KingBombWork
// var M526KingBombCreate temp_ret: M526KingBombWork
// var M526KingBombExplode temp_r3: M526KingBombWork
// var M526KingBombExplode temp_r3_3: M526KingBombWork
// var M526KingBombIdle temp_r3: M526KingBombWork
// var M526KingBombMain temp_r31: M526KingBombWork
// var M526KingBombWin temp_r3: M526KingBombWork
// var M526PlayerCreate temp_r3: M526PlayerWork
// var M526PlayerCreate temp_ret: M526PlayerWork
// var M526PlayerCrossWalk temp_r3: M526PlayerWork
// var M526PlayerHipDrop temp_r3: M526PlayerWork
// var M526PlayerHipDrop temp_r3_2: M526PlayerWork
// var M526PlayerHipDrop temp_r3_3: M526PlayerWork
// var M526PlayerHipDrop temp_r4: M526PlayerWork
// var M526PlayerLaunch temp_r3: M526PlayerWork
// var M526PlayerLaunch temp_r3_2: M526PlayerWork
// var M526PlayerLaunch temp_r3_3: M526PlayerWork
// var M526PlayerMain temp_r31: M526PlayerWork
// var M526PlayerModeMove temp_r3: M526PlayerWork
// var M526PlayerWait temp_r3: M526PlayerWork
// var M526PlayerWinner temp_r3: M526PlayerWork
// var M526PlayerWinnerWalk temp_r3: M526PlayerWork
// var M526PlayerWinnerWalk temp_r3_2: M526PlayerWork
// var M526SmokeCreate temp_r3: M526SmokeWork
// var M526SmokeCreate temp_ret: M526SmokeWork
// var M526SmokeHide temp_r3: M526SmokeWork
// var M526SmokeMain temp_r31: M526SmokeWork
// var M526SmokeShow temp_r3: M526SmokeWork
// var M526StageCameraMove temp_r3: M526StageWork
// var M526StageCreate temp_r3: M526StageWork
// var M526StageCreate temp_ret: M526StageWork
// var M526StageMain temp_r31: M526StageWork
// var M526StageSmokeStart temp_r3: M526StageWork
// var M526StageWait temp_r3: M526StageWork

void ObjectSetup(void);
void M526Main(void);
M526GameFlowWork *M526GameFlowCreate(void);
void M526GameFlowMain(void);
void M526GameFlowWaitSet(M526GameFlowWork *arg0);
void M526GameFlowWait(void);
void M526GameFlowInitSet(M526GameFlowWork *arg0);
void M526GameFlowInit(M526GameFlowWork *arg0);
void M526GameFlowStartSet(M526GameFlowWork *arg0);
void M526GameFlowStart(M526GameFlowWork *arg0);
void M526GameFlowFinishSet(M526GameFlowWork *arg0);
void M526GameFlowFinish(M526GameFlowWork *arg0);
void M526GameFlowPlaySet(M526GameFlowWork *arg0);
void M526GameFlowPlay(M526GameFlowWork *arg0);
void M526GameFlowSplitSet(M526GameFlowWork *arg0, f32 farg0);
void M526GameFlowBombCull(void);
void M526GameFlowBombFollow(void);
void M526GameFlowFuseStart(void);
void M526GameFlowPush(void);
M526StageWork *M526StageCreate(s32 arg0);
void M526StageMain(void);
void M526StagePosSet(M526StageWork *arg0, Vec *arg1);
void M526StagePosGet(M526StageWork *arg0, void *arg1);
void M526StageShadowOff(M526StageWork *arg0);
void M526StageShadowOn(M526StageWork *arg0);
void M526StageWaitSet(M526StageWork *arg0);
void M526StageWait(M526StageWork *arg0);
void M526StageSmokeStartSet(M526StageWork *arg0);
void M526StageSmokeStart(M526StageWork *arg0);
void M526StageCameraMoveSet(M526StageWork *arg0);
void M526StageCameraMove(M526StageWork *arg0);
void M526StageCloudUpdate(M526StageWork *arg0);
M526CameraWork *M526CameraCreate(s32 arg0);
void M526CameraMain(void);
void M526CameraOutView(s32 arg0);
void M526CameraPosSet(M526CameraWork *arg0, f32 farg8);
void M526CameraPosGet(void);
void M526CameraCenterGet(M526CameraWork *arg0, void *arg1);
void M526CameraCenterSet(void);
void M526CameraWaitSet(M526CameraWork *arg0);
void M526CameraWait(M526CameraWork *arg0);
void M526CameraMove(M526CameraWork *arg0);
void M526CameraViewportSet(M526CameraWork *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5);
void M526CameraPerspectiveSet(M526CameraWork *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void M526CameraScissorSet(M526CameraWork *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
M526PlayerWork *M526PlayerCreate(s32 arg0, s32 arg1, s32 arg2);
void M526PlayerMain(void);
void M526PlayerDispOn(M526PlayerWork *arg0);
void M526PlayerDispOff(M526PlayerWork *arg0);
void M526PlayerMotionSet(M526PlayerWork *arg0, s16 arg1, s32 arg2, s32 arg3);
void M526PlayerPosSet(M526PlayerWork *arg0, Vec *arg1);
void M526PlayerPosGet(Vec *arg0, M526PlayerWork *arg1);
void M526PlayerRotSet(M526PlayerWork *arg0, Vec *arg1);
void M526PlayerRotGet(M526PlayerWork *arg0, void *arg1);
void M526PlayerMove(M526PlayerWork *arg0);
f32 M526AngleLerp(f32 farg0, f32 farg1, f32 farg2);
void M526PlayerCollideCheck(M526PlayerWork *arg0);
void M526PlayerWallHit(M526PlayerWork *arg0);
void M526PlayerInput(M526PlayerWork *arg0);
void M526PlayerInputMan(M526PlayerWork *arg0);
void M526PlayerInputCom(M526PlayerWork *arg0);
void M526PlayerComWait(M526PlayerWork *arg0);
void M526PlayerComWalk(M526PlayerWork *arg0);
s32 M526PlayerFuseCheck(M526PlayerWork *arg0, s32 *arg1);
void M526PlayerComJump(M526PlayerWork *arg0);
void M526PlayerComHipDrop(M526PlayerWork *arg0);
void fn_1_62F0(void);
void M526PlayerVibrate(M526PlayerWork *arg0, s32 arg1, s16 arg2);
void M526PlayerWaitSet(M526PlayerWork *arg0);
void M526PlayerWait(M526PlayerWork *arg0);
void M526PlayerModeMoveSet(M526PlayerWork *arg0);
void M526PlayerModeMove(M526PlayerWork *arg0);
void M526PlayerHipDropSet(M526PlayerWork *arg0);
void M526PlayerHipDrop(M526PlayerWork *arg0);
void M526PlayerHipDropFuse(M526PlayerWork *arg0);
void M526PlayerCrossWalkSet(M526PlayerWork *arg0, Vec *arg1);
void M526PlayerCrossWalk(M526PlayerWork *arg0);
void M526PlayerWinnerWalkSet(M526PlayerWork *arg0, Vec *arg1);
void M526PlayerWinnerWalk(M526PlayerWork *arg0);
void M526PlayerWinnerSet(M526PlayerWork *arg0);
void M526PlayerWinner(M526PlayerWork *arg0);
void M526PlayerLaunchSet(M526PlayerWork *arg0);
void M526PlayerLaunch(M526PlayerWork *arg0);
M526FuseWork *M526FuseCreate(s32 arg0, s32 arg1);
void M526FuseMain(void);
void M526FusePosSet(M526FuseWork *arg0, Vec *arg1);
void M526FuseDispOn(M526FuseWork *arg0);
void M526FuseDispOff(M526FuseWork *arg0);
s32 M526FuseCheckActive(M526FuseWork *arg0);
s32 M526FuseCheckDone(M526FuseWork *arg0);
void M526FusePosGet(Vec *arg0, M526FuseWork *arg1);
void M526FuseHookPosGet(Vec *arg0, M526FuseWork *arg1);
void M526FuseSpeedSet(M526FuseWork *arg0, f32 farg0);
void M526FuseWaitSet(M526FuseWork *arg0);
void M526FuseWait(M526FuseWork *arg0);
void M526FuseStopSet(M526FuseWork *arg0);
void M526FuseStop(M526FuseWork *arg0);
void M526FuseIdleSet(M526FuseWork *arg0);
void M526FuseIdle(M526FuseWork *arg0);
void M526FuseExplodeSet(M526FuseWork *arg0);
void M526FuseExplode(M526FuseWork *arg0);
s32 M526FuseDelayGet(M526FuseWork *arg0);
M526KingBombWork *M526KingBombCreate(s32 arg0);
void M526KingBombMain(void);
void M526KingBombPosSet(M526KingBombWork *arg0, Vec *arg1);
void M526KingBombPosGet(M526KingBombWork *arg0, void *arg1);
void M526KingBombMotionSet(M526KingBombWork *arg0, s32 arg1, s32 arg2, s32 arg3);
void M526KingBombIdleSet(M526KingBombWork *arg0);
void M526KingBombIdle(M526KingBombWork *arg0);
void M526KingBombExplodeSet(M526KingBombWork *arg0);
void M526KingBombExplode(M526KingBombWork *arg0);
void M526KingBombWinSet(M526KingBombWork *arg0);
void M526KingBombWin(M526KingBombWork *arg0);
M526ExplosionBombWork *M526ExplosionBombCreate(void);
void M526ExplosionBombMain(void);
void M526ExplosionBombPosSet(M526ExplosionBombWork *arg0, Vec *arg1);
void M526ExplosionBombPosGet(M526ExplosionBombWork *arg0, void *arg1);
void M526ExplosionBombMotionSet(M526ExplosionBombWork *arg0, s32 arg1, s32 arg2, s32 arg3, u32 arg4);
void M526ExplosionBombWalkSet(M526ExplosionBombWork *arg0);
void M526ExplosionBombWalk(M526ExplosionBombWork *arg0);
void M526ExplosionBombExplodeSet(M526ExplosionBombWork *arg0);
void M526ExplosionBombExplode(M526ExplosionBombWork *arg0);
M526BombWork *M526BombCreate(s32 arg0, s32 arg1);
void M526BombMain(void);
void M526BombPosSet(M526BombWork *arg0, Vec *arg1);
void M526BombPosGet(M526BombWork *arg0, void *arg1);
void M526BombRotSet(M526BombWork *arg0, Vec *arg1);
void M526BombRotGet(M526BombWork *arg0, void *arg1);
void M526BombDispOn(M526BombWork *arg0);
void M526BombDispOff(M526BombWork *arg0);
void M526BombModeRandomSet(M526BombWork *arg0);
void M526BombModeRandom(M526BombWork *arg0);
void M526BombModeWait(void);
void M526BombModeRotate(M526BombWork *arg0);
void M526BombLaunchSet(M526BombWork *arg0, s32 arg1);
void M526BombLaunch(M526BombWork *arg0);
void M526BombExitSet(M526BombWork *arg0);
void M526BombExit(M526BombWork *arg0);
void M526BombFollowSet(M526BombWork *arg0);
void M526BombFollow(M526BombWork *arg0);
void M526BombModelUpdate(M526BombWork *arg0);
M526SmokeWork *M526SmokeCreate(s32 arg0);
void M526SmokeMain(void);
void M526SmokePosSet(M526SmokeWork *arg0, Vec *arg1);
void M526SmokePosGet(M526SmokeWork *arg0, void *arg1);
void M526SmokeHideSet(M526SmokeWork *arg0);
void M526SmokeHide(M526SmokeWork *arg0);
void M526SmokeShowSet(M526SmokeWork *arg0);
void M526SmokeShow(M526SmokeWork *arg0);
s32 M526SmokeDispGet(M526SmokeWork *arg0);
void M526SmokeSidePosSet(s32 arg0, Vec *arg1);
s16 M526Audio3DPanGet(s16 arg0, f32 *arg1);
void M526Audio3DPlay(s32 arg0, s16 arg1, Vec *arg2);
typedef struct M526Vec2 { f32 unk0, unk4; } M526Vec2;
typedef struct M526Poly { s32 unk0; M526Vec2 *unk4; } M526Poly; // point count, points

f32 MathDot2DGet(Vec *arg0, Vec *arg1);
f32 MathCross2DGet(Vec *arg0, Vec *arg1);
f32 MathVecMag2DGet(Vec *arg0);
void MathVecNorm2D(Vec *arg0, Vec *arg1);
s32 MathCirclePointCheck(Vec *arg0, Vec *arg1);
s32 MathCircleCircleCheck(Vec *arg0, Vec *arg1);
s32 MathBBoxCheck(f32 *arg0, f32 *arg1);
s32 MathPointShapeCheck(Vec *arg0, M526Poly *arg1);
s32 MathBBoxCircleCheck(Vec *arg0, f32 *arg1);
s32 MathCircleShapeCheck(Vec *arg0, M526Poly *arg1);
s32 MathCircleRectCheck(f32 *arg0, Vec *arg1);
s32 MathSphereCheck(f32 *arg0, f32 *arg1);
s32 MathCircleCollide(Vec *arg0, Vec *arg1);
extern void (*GameFlowModeTbl[5])(M526GameFlowWork *);
extern void (*StageModeTbl[3])(M526StageWork *);
extern void (*CameraModeTbl[2])(M526CameraWork *);
extern void (*PlayerModeTbl[7])(M526PlayerWork *);
extern void (*PlayerInputFuncTbl[2])(M526PlayerWork *);
extern void (*PlayerComModeTbl[4])(M526PlayerWork *);
extern void (*FuseModeTbl[4])(M526FuseWork *);
extern void (*KingBombModeTbl[3])(M526KingBombWork *);
extern void (*ExplosionBombModeTbl[2])(M526ExplosionBombWork *);
extern void (*BombModeTbl[4])(M526BombWork *);
extern void (*SmokeModeTbl[2])(M526SmokeWork *);

// ---- globals (sizes from mp5ref symbols.txt) ----
typedef struct M526LightData {
    f32 unk0, unk4, unk8, unkC, unk10, unk14;
    u8 unk18, unk19, unk1A, unk1B; // color
} M526LightData;

extern s32 ObjProcData[18]; // { prio, stack } x 9
extern u32 PlayerMotFileTbl[13][10];
extern u32 ExplosionBombMotFileTbl[3];
extern u16 CameraBitTbl[2];
extern M526LightData StageLightTbl[1];
extern Vec ShadowPosTbl[6];
extern f32 GameDist[2];
extern s32 GameActiveF[2];
extern M526SmokeWork *SmokeObj[2][6];
extern M526BombWork *BombObj[2][56];
extern M526KingBombWork *KingBombObj[2];
extern M526PlayerWork *PlayerObj[2][2];
extern M526CameraWork *CameraObj[2];
extern M526FuseWork *FuseObj[2][3];
extern M526StageWork *StageObj[2];
extern M526GameFlowWork *GameFlowObj;
extern char *FuseHookTbl[2][3];
extern M526FuseWork *FuseTbl[2][3];
extern M526FuseWork *FuseStartTbl[2][3];
extern s32 lbl_1_bss_18[2][3];
void M526CameraMoveSet(M526CameraWork *arg0, Vec *arg1, Vec *arg2, f32 *arg3, s32 arg4);

// function-local statics (MP5 names name$N -> name_N)
// static poly_209: M526Poly
