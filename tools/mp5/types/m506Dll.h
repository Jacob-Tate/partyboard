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

extern MGSCORE *MgScoreCreate(s32 digitFile, s32 unitFile, s32 dispLeadZeroF);
extern void MgScoreKill(MGSCORE *score);
extern void MgScoreValueSet(MGSCORE *score, s32 value);
extern void MgScorePosSet(MGSCORE *score, f32 x, f32 y);
extern void MgScoreScaleSet(MGSCORE *score, f32 x, f32 y);
extern void MgScoreDigitScaleSet(MGSCORE *score, f32 x, f32 y);
extern void MgScoreZRotSet(MGSCORE *score, f32 zRot);
extern void MgScoreTPLvlSet(MGSCORE *score, f32 tpLvl);
extern void MgScoreColorSet(MGSCORE *score, u8 r, u8 g, u8 b);
extern void MgScoreMaxDigitSet(MGSCORE *score, s32 maxDigit);
extern void MgScoreDigitWidthSet(MGSCORE *score, f32 w);
extern void MgScoreDispOn(MGSCORE *score);
extern void MgScoreDispOff(MGSCORE *score);
extern void MgScorePriSet(MGSCORE *score, s16 prio);
extern MGTIMER *MgTimerCreate(s32 type);
extern void MgTimerKill(MGTIMER *timer);
extern void MgTimerParamSet(MGTIMER *timer, s32 maxTime, s32 endTime, s32 recordTime);
extern void MgTimerModeOnSet(MGTIMER *timer, s32 offType);
extern s32 MgTimerDoneCheck(MGTIMER *timer);

extern HUPROCESS *M506ObjMan;
extern OMOBJ *M506MainObj;
extern OMOBJ **M506PlayerObj;
extern OMOBJ *M506UpdateObj;
extern M506_YCAMERA_WORK *M506YCamera;
extern M506_YLIGHT *M506YLight;
extern M506_YSHADOW_WORK *M506YShadow;
extern M506_FLOW M506Flow;
extern s32 lbl_1_bss_18;
extern s8 lbl_1_bss_28;
extern s32 M506ModelFile[0x1A];
extern s32 M506MotionFile[2];
extern Vec StarPosTbl[2];
extern Vec KumoPosTbl[4];
extern s16 StarMaxTime[3];
extern s16 KumoDirTbl[4];
extern u32 LookUpRotLockFlag[0xD];
extern M506_LOOKUP LookUpRotTbl[0xD];
extern M506_CAMVIEW YCameraView[3];
extern M506_POS ScorePos[16];
extern s32 PlayerMotionTbl[0xD][7];
extern s16 ComMaxDelayTbl[4][5];
extern M506_MOTSHIFT MotShiftTbl[4];
extern f32 MotSpeedTbl[0xA];
extern f32 JumpUpSpeedTbl[0xF];
extern f32 JumpDownSpeedTbl[8];
extern f32 BounceUpSpeedTbl[7];
extern f32 BounceDownSpeedTbl[8];
extern s16 PlayerModeNoTbl[4];
extern s32 CharFallFXTbl[0xD];
extern s32 FallStartFXTbl[4];
extern s32 FallEndFXTbl[4];
extern s32 PlayerPanTbl[4];
extern s32 CharFallSeNo[4];
extern s32 FallEndSeNo[4];
extern s32 FallStartSeNo[4];
extern s32 (*PlayerModeTbl[4])(OMOBJ *);

extern void ObjectSetup(void);
extern void M506Exit(OMOBJ *obj);
extern s32 M506ExitCheck(OMOBJ *obj);
extern void M506Update(OMOBJ *obj);
extern void M506Create(M506_WORK *work);
extern void M506TimerCreate(M506_WORK *work);
extern s32 M506FlowUpdate(M506_WORK *work);
extern void M506MameVineScrollUp(M506_PLAYER_WORK *player);
extern void M506MameIn(M506_PLAYER_WORK *player);
extern void M506MameSpiralIn(M506_PLAYER_WORK *player);
extern void M506MameSmallIn(M506_PLAYER_WORK *player);
extern void M506KumoUpdate(M506_WORK *work);
extern void M506StarUpdate(M506_WORK *work);
extern void M506Noko2Update(M506_WORK *work);
extern void M506MameUpdate(M506_PLAYER_WORK *player);
extern void M506MameModeEnter(M506_PLAYER_WORK *player);
extern void M506MameModeMiss(M506_PLAYER_WORK *player);
extern void M506MameModeJump(M506_PLAYER_WORK *player);
extern void M506ModelUpdate(M506_WORK *work);
extern void M506MainCreate(OMOBJ *obj);
extern void M506FlowEndWatch(OMOBJ *obj);
extern void M506ObjShadowMapSet(s32 no, s32 mame);
extern void M506ObjShadowMapReset(s32 no, s32 from, s32 to);
extern void M506MainUpdate(OMOBJ *obj);
extern void M506ObjInit(M506_FLOW *flow);
extern s32 M506FlowModeStart(M506_FLOW *flow);
extern void M506FlowModeStartSetup(M506_FLOW *flow);
extern void M506FlowMameSetup(M506_FLOW *flow);
extern s32 M506ShadowScrollInit(M506_FLOW *flow);
extern void M506FlowP1Update(M506_FLOW *flow);
extern void M506FlowModeEnd(OMOBJ *obj);
extern void M506FlowModeEndSetup(M506_FLOW *flow);
extern void M506FlowWinStart(M506_FLOW *flow);
extern s32 M506FlowStopCheck(M506_FLOW *flow);
extern s32 M506FlowResult(M506_FLOW *flow);
extern void M506ScoreCreate(M506_FLOW *flow);
extern void M506ScoreDispUpdate(M506_FLOW *flow);
extern void M506ScoreKill(M506_FLOW *flow);
extern void M506MameShadowOff(M506_FLOW *flow);
extern void M506MameShadowOn(M506_FLOW *flow);
extern void M506MameShadowScrollOn(M506_FLOW *flow);
extern void M506MameShadowScrollExec(M506_FLOW *flow);
extern void M506ParticleCreate(M506_FLOW *flow);
extern void M506ParticleUpdate(HU3DMODEL *modelP, HU3DPARTICLE *particleP, f32 mtx[3][4]);
extern void M506ParticleStart(M506_FLOW *flow);
extern void M506ParticleKill(M506_FLOW *flow);
extern void M506RocketInit(M506_FLOW *flow);
extern void M506RocketUpdate(void);
extern s32 M506RocketModelUpdate(M506_FLOW *flow);
extern void M506RocketMove(M506_FLOW *flow);
extern void M506StarfighterStart(M506_FLOW *flow);
extern void M506StarfighterUpdate(void);
extern void M506StarfighterModelUpdate(M506_STARFIGHTER *fighter, s16 mdlId);
extern void M506RecordCreate(M506_FLOW *flow);
extern void M506RecordSet(M506_FLOW *flow);
extern void M506RecordKill(M506_FLOW *flow);
extern void M506RecordBlink(M506_FLOW *flow);
extern void M506RecordBlinkInit(void);
extern void M506YCameraInit(void);
extern void M506YCameraClose(void);
extern void M506YCameraUpdate(void);
extern void M506YCameraProjUpdate(void);
extern void M506YCameraViewUpdate(void);
extern void M506YCameraSplitCreate(void);
extern void M506YCameraSplitKill(void);
extern void M506YCameraViewSet(s32 no, s32 view);
extern s32 M506YCameraViewLerp(s32 no, s32 view);
extern void M506YLightInit(void);
extern void M506YLightClose(void);
extern void M506YLightUpdate(void);
extern void M506YShadowInit(void);
extern void M506YShadowClose(void);
extern void M506YShadowPosUpdate(void);
extern void M506YShadowUpdate(void);
extern s32 M506PointLerp(f32 *value, f32 start, f32 end, f32 rate);
extern void M506MakeRotMtx(f32 mtx[3][4], Vec *rot);
extern void M506SeedUpdate(void);
extern void M506PlayerCreate(OMOBJ *obj);
extern void M506PlayerUpdate(OMOBJ *obj);
extern void M506PlayerMotionSet(OMOBJ *obj, s16 motNo);
extern s32 M506PlayerMotionEndCheck(OMOBJ *obj);
extern s32 M506PlayerInputRead(OMOBJ *obj);
extern s32 M506PlayerModeNormalJump(OMOBJ *obj);
extern s32 M506PlayerModeUpJump(OMOBJ *obj);
extern s32 M506PlayerModeSideJump(OMOBJ *obj);
extern s32 M506PlayerModeFall(OMOBJ *obj);
extern s16 M506ComInputDelayGet(OMOBJ *obj);
extern s16 M506ComInputCheck(OMOBJ *obj);
