// m2c context for m514Dll (tools/mp5/decomp.py m514Dll --types tools/mp5/types/m514Dll.h)
// Written from the draft: Triple Jump (4 players free for all: run up, press A/B alternately for three jumps).
// Runs on MP5's MgSeq sequencer. Four immediate-mode GX hooks (jump arcs, sparks, footprints, goal line).
// objdata fn_1_20E0 fn_1_2338 fn_1_284C fn_1_2A88 fn_1_2D10 fn_1_2E8C fn_1_37CC fn_1_387C fn_1_3CF8 fn_1_3D6C fn_1_3EC0 fn_1_3FB8: M514Player
// objdata fn_1_45D4 fn_1_48B0 fn_1_4A4C fn_1_4C40: M514Obs
// objdata fn_1_76D0 fn_1_77BC: M514Pop
// objdata fn_1_83A8 fn_1_879C fn_1_8C7C fn_1_8D58 fn_1_900C fn_1_9258: M514Score
// objdata fn_1_98C fn_1_9E4: M514Cam
// objexpr lbl_1_bss_70: M514Player
// objexpr lbl_1_bss_208: M514Flag
// objexpr lbl_1_bss_220: M514Score
// objexpr lbl_1_bss_210: M514Goal
// objexpr lbl_1_bss_64: M514Cam
// objexpr lbl_1_bss_218: M514Pop
// var fn_1_45D4 temp_r3: M514Obs
// var fn_1_4A4C temp_r27: M514MotEnt
// var fn_1_4C40 temp_r26: M514MotEnt
// var fn_1_4C40 temp_r25: M514MotEnt
// var fn_1_1ED4 temp_r26: M514Player
// var fn_1_1ED4 temp_r27: M514Player
// var fn_1_8268 temp_r3_2: M514Score
// var fn_1_5CD4 var_r31: M514Arc
// var fn_1_5DE4 var_r31: M514Arc
// var fn_1_79F8 var_r31: M514Arc
// var fn_1_7B8C temp_r31: M514Arc
// var fn_1_7C10 temp_r31: M514Arc
// var fn_1_6644 temp_r24: M514Sparks
// var fn_1_68EC temp_r28: M514Sparks
// var fn_1_7EBC temp_r31: M514Spark
// var fn_1_6D7C var_r31: M514Foot
// var fn_1_6ED4 var_r31: M514Foot
// var fn_1_6ED4 temp_r27: M514Foots
// var fn_1_80C0 var_r31: M514Foot
// var fn_1_585C temp_r30: M514Goal

typedef struct M514Arc { // one jump arc effect (hook data of the first effect model: 3 of them), 0x44
    s32 unk0; // 0: free 1: new 2: growing 3: fading
    s32 unk4;
    s32 unk8; // spark countdown
    f32 unkC; // band width
    f32 unk10; // band width at the start
    f32 unk14; // alpha
    f32 unk18; // angle offset
    f32 unk1C; // arc angle
    f32 unk20; // arc angle goal
    f32 unk24; // highest point
    f32 unk28; // height scale
    f32 unk2C; // start x, y, z
    f32 unk30;
    f32 unk34;
    f32 unk38; // end x, y, z
    f32 unk3C;
    f32 unk40;
} M514Arc;

typedef struct M514Spark { // one spark (hook data of the second effect model), 0x24
    s32 unk0; // used
    s32 unk4; // colour phases
    s32 unk8;
    s32 unkC;
    GXColor unk10;
    f32 unk14; // size
    f32 unk18; // x
    f32 unk1C; // y
    f32 unk20; // z
} M514Spark;

typedef struct M514Sparks { // 0x2404
    ANIMDATA *unk0;
    M514Spark unk4[256];
} M514Sparks;

typedef struct M514Foot { // one footprint (hook data of the third effect model), 0x1C
    s32 unk0; // 0: free 1: new 2: fading in 3: stay 4: fading out
    s32 unk4; // timer
    f32 unk8; // radius
    GXColor unkC;
    f32 unk10; // x, y, z
    f32 unk14;
    f32 unk18;
} M514Foot;

typedef struct M514Foots { // 0x3880
    M514Foot unk0[512];
    f32 unk3800[16]; // sin
    f32 unk3840[16]; // cos
} M514Foots;

typedef struct M514Pop { // effect object data (the "+" popup sprite), 0x1C
    s32 unk0; // mode
    char pad4[4];
    f32 unk8; // alpha
    s16 unkC; // sprite group
    char padE[2];
    f32 unk10; // scale
    s16 unk14; // wanted bank
    s16 unk16; // shown bank
    char pad18[4];
} M514Pop;

typedef struct M514Flag { // 4
    s32 unk0;
} M514Flag;

typedef struct M514Goal { // 4
    f32 unk0; // x
} M514Goal;

typedef struct M514Cam { // camera object data, 8
    s32 unk0; // intro camera running
    s16 unk4; // motion
    s16 unk6; // camera model
} M514Cam;

typedef struct M514Player { // OMOBJ::data, 0x98
    s32 unk0; // player
    s32 unk4; // group
    s32 unk8; // slot
    s32 unkC; // character
    u32 unk10; // buttons pressed this frame
    u32 unk14; // buttons held
    f32 unk18;
    f32 unk1C;
    s32 unk20; // com
    s32 unk24; // difficulty
    s32 unk28; // com mode
    s32 unk2C; // com timer
    u32 unk30; // mode
    s32 unk34; // mode timer
    s32 unk38; // frame counter
    s32 unk3C; // motion
    Vec unk40; // pos
    Vec unk4C; // vel
    f32 unk58; // facing
    f32 unk5C; // motion speed
    f32 unk60; // gravity
    s32 unk64; // distance tracked
    s32 unk68; // on the track
    s32 unk6C;
    s32 unk70;
    s32 unk74; // walking to a point
    s32 unk78; // footstep side
    u32 unk7C; // run mode
    s32 unk80;
    s32 unk84; // jump no
    s32 unk88;
    s32 unk8C; // done
    s32 unk90; // arc effect
    s32 unk94; // sound
} M514Player;

typedef struct M514MotEnt { // motion list entry: data number, shift time, attributes
    u32 unk0;
    f32 unk4;
    u32 unk8;
} M514MotEnt;

typedef struct M514ObsDef { // obstacle definition, 0x1C
    s32 unk0; // kind
    s32 unk4; // model
    s32 unk8; // model data number
    M514MotEnt *unkC; // motions
    Vec *unk10; // position
    f32 unk14; // rotation
    void (*unk18)(OMOBJ *);
} M514ObsDef;

typedef struct M514Obs { // obstacle object data, 0x58
    M514ObsDef *unk0;
    s32 unk4; // mode
    s32 unk8; // timer
    s32 unkC;
    s32 unk10; // motion
    s32 unk14; // sound
    s32 unk18; // sound
    Vec unk1C; // pos
    Vec unk28; // vel
    Vec unk34; // rot
    char pad40[4];
    s32 unk44; // frame
    char pad48[0x10];
} M514Obs;

typedef struct M514Slot { // per player score slot, 0x24 (the first one's first 12 bytes hold the common state)
    s32 unk0; // mode
    s32 unk4;
    f32 unk8; // alpha
    s32 unkC; // score
    s32 unk10; // rank
    s16 unk14; // score window
    s16 unk16; // sprite group
    MGSCORE *unk18;
    MGSCORE *unk1C;
    f32 unk20; // pos x (the original goes on with y, goal x, goal y into the next slot's first bytes: M514Score unkB8)
} M514Slot;

typedef struct M514Score { // 0xB8
    M514Slot unk0[4];
    char pad90[0xC];
    s32 unk9C; // best score display mode
    s32 unkA0;
    s32 unkA4; // best score
    s32 unkA8; // shown
    s16 unkAC; // window
    s16 unkAE; // sprite group
    MGSCORE *unkB0;
    MGSCORE *unkB4;
    f32 unkB8[4]; // PC: per slot pos y
    f32 unkC8[4][2]; // PC: per slot goal pos
} M514Score;

typedef struct M514Light { // x, y rotation, distance
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M514Light;

typedef struct M514Jump { // lbl_1_data_23C: per jump, 0x1C
    s32 unk0; // wait
    f32 unk4; // speed
    f32 unk8; // jump speed
    f32 unkC; // boost
    f32 unk10; // up boost
    f32 unk14; // down boost
    f32 unk18; // hold distance
} M514Jump;

typedef struct M514Com { // lbl_1_data_2BC: COM timing, 0x10
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M514Com;

typedef struct M514Fog { // lbl_1_data_4A0: start, end, colour; 0xC
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} M514Fog;

typedef struct M514Anim { // lbl_1_data_D8: motion slot, shift time, attributes; 0xC
    u16 unk0;
    char pad2[2];
    f32 unk4;
    u32 unk8;
} M514Anim;

typedef struct M514Pos2 { // 8
    f32 unk0;
    f32 unk4;
} M514Pos2;

extern M514ObsDef lbl_1_data_3B4[6];
extern M514MotEnt lbl_1_data_300[2];
extern M514MotEnt lbl_1_data_318[2];
extern M514MotEnt lbl_1_data_330[2];
extern M514MotEnt lbl_1_data_348[2];
extern M514MotEnt lbl_1_data_360[2];
extern Vec lbl_1_data_378;
extern Vec lbl_1_data_384;
extern Vec lbl_1_data_390;
extern Vec lbl_1_data_39C;
extern Vec lbl_1_data_3A8;
extern GXColor lbl_1_data_4D8[7];
extern M514Light lbl_1_data_5C;
extern MGSEQ_PARAM lbl_1_data_90;
extern f32 lbl_1_data_0;
extern f32 lbl_1_data_4;
extern f32 lbl_1_data_8;
extern OMCAMERAVIEW lbl_1_data_C[2];
extern Vec lbl_1_data_44;
extern Vec lbl_1_data_50;
extern GXColor lbl_1_data_68;
extern s32 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s16 lbl_1_bss_8[4];
extern s16 lbl_1_bss_10[4];
extern s16 lbl_1_bss_18[4];
extern s16 lbl_1_bss_20[4];
extern Vec lbl_1_bss_28;
extern Vec lbl_1_bss_34;
extern Vec lbl_1_bss_40;
extern s32 lbl_1_bss_4C;
extern s32 lbl_1_bss_50;
extern s16 lbl_1_bss_54;
extern s16 lbl_1_bss_56;
extern s32 lbl_1_bss_58;
extern s32 lbl_1_bss_5C;
extern s32 lbl_1_bss_60;
extern OMOBJ *lbl_1_bss_64;
extern HUPROCESS *lbl_1_bss_68;
extern OMOBJ *lbl_1_bss_70[4];
extern OMOBJ *lbl_1_bss_80;
extern s16 lbl_1_bss_88[0x20];
extern s16 lbl_1_bss_C8[0x20];
extern s32 lbl_1_bss_108[0x20];
extern s32 lbl_1_bss_188[0x20];
extern OMOBJ *lbl_1_bss_208;
extern OMOBJ *lbl_1_bss_210;
extern f32 lbl_1_bss_214;
extern OMOBJ *lbl_1_bss_218;
extern OMOBJ *lbl_1_bss_220;
extern s32 lbl_1_data_45C[5];
extern s8 lbl_1_data_470[8];
extern u32 lbl_1_data_B8[8];
extern M514Anim lbl_1_data_D8[8];
extern Vec lbl_1_data_138[10];
extern f32 lbl_1_data_1B0[16];
extern f32 lbl_1_data_1F0[4];
extern M514Jump lbl_1_data_23C[3];
extern s32 lbl_1_data_290[3];
extern M514Com lbl_1_data_2BC[4];
extern M514Pos2 lbl_1_data_4F8;
extern s32 lbl_1_data_500[0xF];
extern M514Pos2 lbl_1_data_53C[4];
extern M514Fog lbl_1_data_4A0[3];
extern Vec lbl_1_data_4C4;
extern u32 lbl_1_data_4D0;
extern Vec lbl_1_rodata_88[2];


void fn_1_5B04(HUPROCESS *arg0);
void fn_1_5B8C(void);
void fn_1_5B90(OMOBJ *obj);
void fn_1_5BEC(OMOBJ *obj);
void fn_1_5C34(OMOBJ *arg0);
void fn_1_5CD4(OMOBJ *arg0);
void fn_1_5DE4(HU3DMODEL *modelP, Mtx mtx);
void fn_1_6588(OMOBJ *arg0);
void fn_1_6644(OMOBJ *arg0);
void fn_1_68EC(HU3DMODEL *modelP, Mtx mtx);
void fn_1_6C44(OMOBJ *arg0);
void fn_1_6D7C(OMOBJ *arg0);
void fn_1_6ED4(HU3DMODEL *modelP, Mtx mtx);
void fn_1_7184(OMOBJ *arg0);
void fn_1_728C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_76D0(OMOBJ *arg0);
void fn_1_77BC(OMOBJ *arg0);
s32 fn_1_79F8(Vec *arg0, f32 farg0);
void fn_1_7B14(s32 arg0);
void fn_1_7B8C(s32 arg0);
void fn_1_7C10(s32 arg0, Vec *arg1);
void fn_1_7EBC(Vec *arg0);
void fn_1_80C0(Vec *arg0, f32 farg0);
void fn_1_8180(Vec *arg0);
void fn_1_8228(s16 arg0);
void ObjectSetup(void);
void fn_1_3A0(s16 mode, s16 frameNo);
void fn_1_448(s16 arg1, s16 frameNo);
void fn_1_540(s16 arg1, s16 frameNo);
void fn_1_580(s16 mode, s16 frameNo);
void fn_1_600(s16 arg1, s16 frameNo);
void fn_1_7B0(s16 arg1, s16 frameNo);
void fn_1_8A0(s16 arg1, s16 frameNo);
void fn_1_958(s16 mode, s16 frameNo);
void fn_1_95C(s16 mode, s16 frameNo);
void fn_1_98C(OMOBJ *obj);
void fn_1_9E4(OMOBJ *obj);
void fn_1_14F4(Vec *arg0, Vec *arg1, f32 farg0);
void fn_1_163C(void *arg0);
s32 fn_1_16AC(void);
s16 fn_1_16DC(void);
s16 fn_1_16EC(s32 arg0);
u32 fn_1_1704(u32 arg0);
s32 fn_1_1814(void);
void fn_1_1824(void);
void fn_1_1838(s32 arg0, s16 arg1, s16 arg2);
void fn_1_1870(s32 arg0);
void fn_1_1890(void);
s32 fn_1_1904(f32 farg0);
s16 fn_1_1960(Point3d *arg0);
s16 fn_1_19F4(void);
void fn_1_1A18(s32 arg0, Point3d *arg1);
void fn_1_1AF4(s32 arg0, Point3d *arg1);
f32 fn_1_1BCC(f32 farg0, f32 farg1, f32 farg2);
f32 fn_1_1CE8(f32 farg0, f32 farg1);
void fn_1_4270(HUPROCESS *arg0);
void fn_1_4344(void);
void fn_1_4348(OMOBJ *obj);
void fn_1_4358(OMOBJ *obj);
void fn_1_435C(void);
s16 fn_1_43F8(s32 arg0);
s16 fn_1_44E4(s16 arg0, s32 arg1);
void fn_1_45D4(HUPROCESS *arg0, M514ObsDef *arg1);
void fn_1_48B0(OMOBJ *arg0);
void fn_1_490C(void *arg0, s32 arg1);
s32 fn_1_49E4(void *arg0);
void fn_1_4A4C(OMOBJ *arg0);
void fn_1_4C40(OMOBJ *arg0);
s32 fn_1_50E4(void);
void fn_1_1D9C(HUPROCESS *arg0);
void fn_1_1EA0(void);
void fn_1_1EC4(OMOBJ *obj);
void fn_1_1ED4(OMOBJ *obj);
void fn_1_20E0(OMOBJ *obj);
void fn_1_22C8(void *arg0);
void fn_1_2338(OMOBJ *obj);
void fn_1_284C(OMOBJ *obj);
void fn_1_2A88(OMOBJ *arg0);
void fn_1_2BC8(void *arg0, Vec *arg1, s32 arg2);
void fn_1_2D10(OMOBJ *arg0, s32 arg1);
void fn_1_2E88(void);
void fn_1_2E8C(OMOBJ *arg0);
void fn_1_37CC(OMOBJ *arg0, s32 arg1);
void fn_1_3CF8(OMOBJ *arg0);
void fn_1_3D6C(OMOBJ *arg0);
void fn_1_3EC0(OMOBJ *arg0, u32 arg1);
s32 fn_1_3FB8(OMOBJ *arg0);
s32 fn_1_4024(void *arg0);
s32 fn_1_4084(void *arg0, u32 arg1);
s32 fn_1_41C4(u32 arg0);
f32 fn_1_4238(s32 arg0);
void fn_1_8268(HUPROCESS *arg0);
void fn_1_8300(void);
void fn_1_8304(OMOBJ *obj);
void fn_1_835C(OMOBJ *obj);
void fn_1_83A8(OMOBJ *arg0);
void fn_1_879C(OMOBJ *arg0);
void fn_1_8B54(void *arg0);
void fn_1_8C7C(OMOBJ *arg0);
void fn_1_8D58(OMOBJ *arg0);
void fn_1_900C(OMOBJ *arg0);
void fn_1_9258(OMOBJ *arg0);
void fn_1_9300(s16 arg0, s16 arg1);
void fn_1_9334(void);
void fn_1_9570(s32 arg0, f32 farg0);
s32 fn_1_95BC(s32 arg0);
f32 fn_1_95F4(s32 arg0);
f32 fn_1_9688(void);
f32 fn_1_9794(void);
s32 fn_1_9820(void);
void fn_1_98F4(void);
void fn_1_510C(HUPROCESS *arg0);
void fn_1_51BC(void);
void fn_1_51C0(OMOBJ *obj);
void fn_1_536C(OMOBJ *obj);
void fn_1_5430(enum _GXFogType arg0, s32 arg1);
void fn_1_54DC(s16 layerNo);
void fn_1_5574(s16 layerNo);
void fn_1_5610(s16 layerNo);
void fn_1_56AC(s16 layerNo);
void fn_1_5744(void);
void fn_1_57F0(OMOBJ *arg0);
void fn_1_5858(void);
void fn_1_585C(HU3DMODEL *modelP, Mtx mtx);
