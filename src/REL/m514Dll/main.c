// MP5 m514 (Triple Jump), generated from its m2c draft by tools/mp5/ports/m514Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
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
void fn_1_5B04(HUPROCESS *arg0);
void fn_1_5B8C(void);
void fn_1_5B90(omObjData *arg0);
void fn_1_5BEC(omObjData *obj);
void fn_1_5C34(omObjData *arg0);
void fn_1_5CD4(omObjData *arg0);
void fn_1_5DE4(HU3DMODEL *modelP, Mtx mtx);
void fn_1_6588(omObjData *arg0);
void fn_1_6644(omObjData *arg0);
void fn_1_68EC(HU3DMODEL *modelP, Mtx mtx);
void fn_1_6C44(omObjData *arg0);
void fn_1_6D7C(omObjData *arg0);
void fn_1_6ED4(HU3DMODEL *modelP, Mtx mtx);
void fn_1_7184(omObjData *arg0);
void fn_1_728C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_76D0(omObjData *arg0);
void fn_1_77BC(omObjData *arg0);
s32 fn_1_79F8(Vec *arg0, f32 farg0);
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
void fn_1_98C(omObjData *arg0);
void fn_1_9E4(omObjData *obj);
void fn_1_14F4(Vec *arg0, Vec *arg1, f32 farg0);
void fn_1_163C(void *arg0);
s32 fn_1_16AC(void);
s16 fn_1_16EC(s32 arg0);
u32 fn_1_1704(u32 arg0);
s32 fn_1_1814(void);
void fn_1_1824(void);
void fn_1_1838(s32 arg0, s16 arg1, s16 arg2);
void fn_1_1870(s32 arg0);
void fn_1_1890(void);
s16 fn_1_1960(Vec *arg0);
s16 fn_1_19F4(void);
void fn_1_1AF4(s32 arg0, Vec *arg1);
f32 fn_1_1BCC(f32 farg0, f32 farg1, f32 farg2);
f32 fn_1_1CE8(f32 farg0, f32 farg1);
void fn_1_4270(HUPROCESS *arg0);
void fn_1_4344(void);
void fn_1_4348(omObjData *arg0);
void fn_1_4358(omObjData *obj);
void fn_1_435C(void);
void fn_1_45D4(HUPROCESS *arg0, M514ObsDef *arg1);
void fn_1_48B0(omObjData *arg0);
void fn_1_4A4C(omObjData *arg0);
void fn_1_4C40(omObjData *obj);
s32 fn_1_50E4(void);
void fn_1_1D9C(HUPROCESS *arg0);
void fn_1_1EA0(void);
void fn_1_1EC4(omObjData *arg0);
void fn_1_1ED4(omObjData *obj);
void fn_1_20E0(omObjData *arg0);
void fn_1_2338(omObjData *obj);
void fn_1_284C(omObjData *obj);
void fn_1_2A88(omObjData *arg0);
void fn_1_2D10(omObjData *arg0, s32 arg1);
void fn_1_2E88(void);
void fn_1_2E8C(omObjData *arg0);
void fn_1_37CC(omObjData *arg0, s32 arg1);
s32 fn_1_387C(omObjData *arg0, Vec *arg1, s32 arg2, f32 farg0);
void fn_1_3CF8(omObjData *arg0);
void fn_1_3D6C(omObjData *arg0);
void fn_1_3EC0(omObjData *arg0, u32 arg1);
s32 fn_1_3FB8(omObjData *arg0);
s32 fn_1_41C4(u32 arg0);
f32 fn_1_4238(s32 arg0);
void fn_1_8268(HUPROCESS *arg0);
void fn_1_8300(void);
void fn_1_8304(omObjData *arg0);
void fn_1_835C(omObjData *obj);
void fn_1_83A8(omObjData *arg0);
void fn_1_879C(omObjData *arg0);
void fn_1_8C7C(omObjData *arg0);
void fn_1_8D58(omObjData *arg0);
void fn_1_900C(omObjData *arg0);
void fn_1_9258(omObjData *arg0);
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
void fn_1_51C0(omObjData *arg0);
void fn_1_536C(omObjData *obj);
void fn_1_54DC(s16 layerNo);
void fn_1_5574(s16 layerNo);
void fn_1_5610(s16 layerNo);
void fn_1_56AC(s16 layerNo);
void fn_1_5744(void);
void fn_1_57F0(omObjData *arg0);
void fn_1_5858(void);
void fn_1_585C(HU3DMODEL *modelP, Mtx mtx);

GXColor lbl_1_data_4D8[7] = {
    { 0xFF, 0, 0, 0 },
    { 0xFF, 0x80, 0, 0 },
    { 0xFF, 0xFF, 0, 0 },
    { 0, 0xFF, 0, 0 },
    { 0, 0x80, 0xFF, 0 },
    { 0, 0, 0xFF, 0 },
    { 0x80, 0, 0xFF, 0 },
};
omObjData *lbl_1_bss_218;
f32 lbl_1_data_0 = 20.0f;
f32 lbl_1_data_4 = 25000.0f;
f32 lbl_1_data_8 = 48.0f;
OMCAMERAVIEW lbl_1_data_C[2] = {
    { { -1500.0f, 1250.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, 1180.0f },
    { { -2500.0f, 120.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, 750.0f },
};
Vec lbl_1_data_44 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_50 = { 0.3f, -0.8f, 0.3f };
M514Light lbl_1_data_5C = { 40.0f, -60.0f, 1000.0f };
GXColor lbl_1_data_68 = { 0xFF, 0xFF, 0xFF, 0xFF };
MGSEQ_PARAM lbl_1_data_90 = {
    0,
    1,
    fn_1_3A0,
    fn_1_448,
    fn_1_540,
    fn_1_580,
    fn_1_600,
    fn_1_7B0,
    fn_1_8A0,
    fn_1_958,
    fn_1_95C,
};
s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s16 lbl_1_bss_8[4];
s16 lbl_1_bss_10[4];
s16 lbl_1_bss_18[4];
s16 lbl_1_bss_20[4];
Vec lbl_1_bss_28;
Vec lbl_1_bss_34;
Vec lbl_1_bss_40;
s32 lbl_1_bss_4C;
s32 lbl_1_bss_50;
s16 lbl_1_bss_54;
s16 lbl_1_bss_56;
s32 lbl_1_bss_58;
s32 lbl_1_bss_5C;
s32 lbl_1_bss_60;
omObjData *lbl_1_bss_64;
HUPROCESS *lbl_1_bss_68;
M514MotEnt lbl_1_data_300[2] = { { DATA_MAKE_NUM(DATADIR_MP5_M514, 7), 0.2f, 0x40000001 }, { DATA_MAKE_NUM(DATADIR_MP5_M514, 8), 0.2f, 0x40000001 } };
M514MotEnt lbl_1_data_318[2] = { { DATA_MAKE_NUM(DATADIR_MP5_M514, 10), 0.2f, 0x40000001 }, { DATA_MAKE_NUM(DATADIR_MP5_M514, 11), 0.2f, 0x40000001 } };
M514MotEnt lbl_1_data_330[2] = { { DATA_MAKE_NUM(DATADIR_MP5_M514, 13), 0.2f, 0x40000001 }, { DATA_MAKE_NUM(DATADIR_MP5_M514, 14), 0.2f, 0x40000001 } };
M514MotEnt lbl_1_data_348[2] = { { DATA_MAKE_NUM(DATADIR_MP5_M514, 16), 0.2f, 0x40000001 }, { DATA_MAKE_NUM(DATADIR_MP5_M514, 17), 0.2f, 0x40000001 } };
M514MotEnt lbl_1_data_360[2] = { { DATA_MAKE_NUM(DATADIR_MP5_M514, 20), 0.2f, 0x40000001 }, { DATA_MAKE_NUM(DATADIR_MP5_M514, 21), 0.2f, 0x40000001 } };
Vec lbl_1_data_378 = { -1500.0f, 70.0f, -400.0f };
Vec lbl_1_data_384 = { -500.0f, 70.0f, -400.0f };
Vec lbl_1_data_390 = { 500.0f, 70.0f, -400.0f };
Vec lbl_1_data_39C = { 1500.0f, 70.0f, -400.0f };
Vec lbl_1_data_3A8 = { 2500.0f, 70.0f, -400.0f };
M514ObsDef lbl_1_data_3B4[6] = {
    { 0, 0, DATA_MAKE_NUM(DATADIR_MP5_M514, 6), lbl_1_data_300, &lbl_1_data_378, 0.0f, fn_1_4A4C },
    { 1, 1, DATA_MAKE_NUM(DATADIR_MP5_M514, 9), lbl_1_data_318, &lbl_1_data_384, 0.0f, fn_1_4A4C },
    { 2, 2, DATA_MAKE_NUM(DATADIR_MP5_M514, 12), lbl_1_data_330, &lbl_1_data_390, 0.0f, fn_1_4A4C },
    { 3, 3, DATA_MAKE_NUM(DATADIR_MP5_M514, 15), lbl_1_data_348, &lbl_1_data_39C, 0.0f, fn_1_4A4C },
    { 4, 4, DATA_MAKE_NUM(DATADIR_MP5_M514, 19), lbl_1_data_360, &lbl_1_data_3A8, 0.0f, fn_1_4A4C },
    { -1, 0, 0, NULL, NULL, 0.0f, NULL },
};
s32 lbl_1_data_45C[5] = { DATA_MAKE_NUM(DATADIR_MP5_M514, 24), DATA_MAKE_NUM(DATADIR_MP5_M514, 27), DATA_MAKE_NUM(DATADIR_MP5_M514, 28), DATA_MAKE_NUM(DATADIR_MP5_M514, 29), DATA_MAKE_NUM(DATADIR_MP5_M514, 30) };
s8 lbl_1_data_470[8] = { 0x6F, 0x62, 0x6A, 0x31, 0x32, 0, 0, 0 };
s16 lbl_1_bss_88[0x20];
s16 lbl_1_bss_C8[0x20];
s32 lbl_1_bss_108[0x20];
s32 lbl_1_bss_188[0x20];
omObjData *lbl_1_bss_208;
u32 lbl_1_data_B8[8] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 49),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3),
    DATA_MAKE_NUM(DATADIR_MP5_MARIO, 33),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4),
};
M514Anim lbl_1_data_D8[8] = {
    { 0, 0.2f, 0x40000001 },
    { 1, 0.2f, 0x40000001 },
    { 2, 0.2f, 0x40000001 },
    { 3, 0.2f, 0 },
    { 4, 0.2f, 0 },
    { 5, 0.1f, 0 },
    { 6, 0.2f, 0x40000001 },
    { 7, 0.2f, 0 },
};
Vec lbl_1_data_138[0xA] = {
    { -2100.0f, 0.0f, -500.0f },
    { -1900.0f, 0.0f, -500.0f },
    { -1700.0f, 0.0f, -500.0f },
    { -1500.0f, 0.0f, -500.0f },
    { -3200.0f, 0.0f, -500.0f },
    { -3000.0f, 0.0f, -500.0f },
    { -2800.0f, 0.0f, -500.0f },
    { -2600.0f, 0.0f, -500.0f },
    { -3100.0f, 0.0f, 0.0f },
    { -2570.0f, 0.0f, 0.0f },
};
f32 lbl_1_data_1B0[0x10] = {
    0.98f,
    1.06f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};
f32 lbl_1_data_1F0[4] = { 270.0f, 270.0f, 270.0f, 270.0f };
M514Jump lbl_1_data_23C[3] = {
    { 3, 13.333334f, 16.666668f, 0.5833334f, 1.0f, 6.666667f, 1500.0f },
    { 4, 13.333334f, 16.666668f, 0.5833334f, 1.0f, 6.666667f, 3000.0f },
    { 6, 16.666668f, 16.666668f, 0.75000006f, 1.0f, 8.333334f, 5000.0f },
};
s32 lbl_1_data_290[3] = { 0x6DA, 0x6DB, 0x6DC };
M514Com lbl_1_data_2BC[4] = {
    { 6.0f, 1.2f, 9.66f, 0.9f },
    { 4.2f, 3.0f, 6.9f, 3.0f },
    { 3.6f, 3.6f, 6.3f, 3.0f },
    { 3.0f, 4.8f, 5.28f, 3.0f },
};
omObjData *lbl_1_bss_70[4];
omObjData *lbl_1_bss_80;
M514Pos2 lbl_1_data_4F8 = { 288.0f, 58.0f };
s32 lbl_1_data_500[0xF] = {
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 32),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 33),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 34),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 35),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 36),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 38),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 39),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 40),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 41),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 42),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 43),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 44),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 45),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 42),
    DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 42),
};
M514Pos2 lbl_1_data_53C[4] = {
    { 102.0f, 58.0f },
    { 102.0f, 108.0f },
    { 102.0f, 158.0f },
    { 102.0f, 208.0f },
};
omObjData *lbl_1_bss_220;
M514Fog lbl_1_data_4A0[3] = {
    { 20.0f, 7700.0f, 0xFF, 0xFF, 0xEE, 0 },
    { 20.0f, 15000.0f, 0xFF, 0xFF, 0xEE, 0 },
    { 20.0f, 25000.0f, 0xFF, 0xFF, 0xEE, 0 },
};
Vec lbl_1_data_4C4 = { -4644.0f, -1228.0f, -4732.0f };
u32 lbl_1_data_4D0 = 0x42FF7A80;
omObjData *lbl_1_bss_210;
f32 lbl_1_bss_214;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
    s32 unk8;
} lbl_1_rodata_10;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
    s32 unk8;
} lbl_1_rodata_1C;
Vec lbl_1_rodata_88[2] = { { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } }; /* const */

// ---- Triple Jump's four immediate-mode effect hooks and the code driving them (hand-written from the asm) ----
// Each hook sets its whole GX state (nothing is left to the previous draw). The fixed-function pipeline
// writes are GXBegin / GXPosition3f32 / GXColor4u8 / GXTexCoord2f32 / GXEnd on Aurora.

static void M514ColorPassInit(void)
{
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
}

static void M514Vtx(f32 x, f32 y, f32 z, GXColor color)
{
    GXPosition3f32(x, y, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
}

void fn_1_5C34(omObjData *arg0)
{
    s16 mdl;

    mdl = Hu3DHookFuncCreate(fn_1_5DE4);
    arg0->model[0] = mdl;
    Hu3DModelLayerSet(mdl, 6);
    Hu3DData[mdl].hookData = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Arc) * 3, MEMORY_DEFAULT_NUM);
    memset(Hu3DData[mdl].hookData, 0, sizeof(M514Arc) * 3);
}

void fn_1_5CD4(omObjData *arg0)
{
    M514Arc *arc;
    s32 i;

    arc = Hu3DData[arg0->model[0]].hookData;
    for (i = 0; i < 3; i++, arc++) {
        switch (arc->unk0) {
            case 1:
                arc->unk0++;
                arc->unk18 = 0.0f;
                arc->unk20 = 5.0f;
                arc->unk1C = 5.0f;
                arc->unk28 = 1.0f;
                break;
            case 3:
                arc->unk14 = (f32)((f64)arc->unk14 - 0.01);
                if (!(arc->unk14 > 0.0f)) {
                    arc->unk0 = 0;
                }
                break;
            default:
                break;
        }
    }
}

// the jump arcs: 24 segments of a half ring of 6 colour bands each, standing on the ground between the
// jump's start and end
void fn_1_5DE4(HU3DMODEL *modelP, Mtx mtx)
{
    M514Arc *arc;
    GXColor cols0[7];
    GXColor cols1[7];
    Vec radius;
    Mtx m;
    f32 cx, cz, scaleY, rad, width, step, ang, a0, a1, frac, r0, r1;
    s32 i, seg, ring, k, alpha0, alpha1;

    arc = modelP->hookData;
    M514ColorPassInit();
    memcpy(cols0, lbl_1_data_4D8, sizeof(cols0));
    memcpy(cols1, lbl_1_data_4D8, sizeof(cols1));
    for (i = 0; i < 3; i++, arc++) {
        if (arc->unk0 < 2) {
            continue;
        }
        cx = (f32)((f64)arc->unk2C + 0.5 * (f64)(arc->unk38 - arc->unk2C));
        cz = (f32)((f64)arc->unk34 + 0.5 * (f64)(arc->unk40 - arc->unk34));
        scaleY = arc->unk28;
        radius.x = arc->unk38 - cx;
        radius.y = arc->unk3C - 0.0f;
        radius.z = arc->unk40 - cz;
        rad = VECMag(&radius);
        width = arc->unkC;
        step = arc->unk1C / 24.0f;
        MTXIdentity(m);
        MTXTrans(m, cx, 0.0f, cz);
        MTXConcat(mtx, m, m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        ang = 0.0f;
        for (seg = 0; seg < 24; seg++) {
            a0 = (f32)(270.0 + (f64)(ang + arc->unk18));
            a1 = a0 + step;
            if (0.0 != (f64)arc->unk1C) {
                frac = (f32)(180.0 * (f64)(ang / arc->unk1C));
            } else {
                frac = 0.0f;
            }
            alpha0 = (s32)(128.0f * (f32)sin(3.141592653589793 * (f64)frac / 180.0) * arc->unk14);
            alpha1 = (s32)(128.0f * (f32)sin(3.141592653589793 * (f64)(frac + step) / 180.0) * arc->unk14);
            for (k = 0; k < 7; k++) {
                cols0[k].a = (u8)alpha0;
                cols1[k].a = (u8)alpha1;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 24);
            for (ring = 0; ring < 6; ring++) {
                r0 = rad - width * (f32)ring;
                if (r0 < 0.0f) {
                    r0 = 0.0f;
                }
                r1 = r0 - width;
                if (r1 < 0.0f) {
                    r1 = 0.0f;
                }
                M514Vtx(r0 * (f32)sin(3.141592653589793 * (f64)a0 / 180.0),
                    (f32)((f64)scaleY * ((f64)r0 * cos(3.141592653589793 * (f64)a0 / 180.0))), 0.0f, cols0[ring]);
                M514Vtx(r0 * (f32)sin(3.141592653589793 * (f64)a1 / 180.0),
                    (f32)((f64)scaleY * ((f64)r0 * cos(3.141592653589793 * (f64)a1 / 180.0))), 0.0f, cols1[ring]);
                M514Vtx(r1 * (f32)sin(3.141592653589793 * (f64)a1 / 180.0),
                    (f32)((f64)scaleY * ((f64)r1 * cos(3.141592653589793 * (f64)a1 / 180.0))), 0.0f, cols1[ring + 1]);
                M514Vtx(r1 * (f32)sin(3.141592653589793 * (f64)a0 / 180.0),
                    (f32)((f64)scaleY * ((f64)r1 * cos(3.141592653589793 * (f64)a0 / 180.0))), 0.0f, cols0[ring + 1]);
            }
            GXEnd();
            ang += step;
        }
    }
}

void fn_1_6588(omObjData *arg0)
{
    s16 mdl;
    M514Sparks *sparks;

    mdl = Hu3DHookFuncCreate(fn_1_68EC);
    arg0->model[1] = mdl;
    Hu3DModelLayerSet(mdl, 6);
    sparks = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Sparks), MEMORY_DEFAULT_NUM);
    Hu3DData[mdl].hookData = sparks;
    memset(sparks, 0, sizeof(M514Sparks));
    sparks->unk0 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 32), MEMORY_DEFAULT_NUM, HEAP_DATA));
}

void fn_1_6644(omObjData *arg0)
{
    M514Sparks *sparks;
    M514Spark *s;
    s32 i, t0, t1, t2;

    sparks = Hu3DData[arg0->model[1]].hookData;
    for (i = 0; i < 0x100; i++) {
        s = &sparks->unk4[i];
        if (s->unk0 == 0) {
            continue;
        }
        s->unk14 = (f32)((f64)s->unk14 - 0.5);
        s->unk1C = (f32)((f64)s->unk1C + 2.0);
        s->unk10.a = (u8)(s->unk10.a - 6);
        t0 = s->unk4;
        s->unk4 = t0 + 1;
        s->unk10.r = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t0 & 0x1F)) / 180.0));
        t1 = s->unk8;
        s->unk8 = t1 + 1;
        s->unk10.g = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t1 & 0x1F)) / 180.0));
        t2 = s->unkC;
        s->unkC = t2 + 1;
        s->unk10.b = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t2 & 0x1F)) / 180.0));
        if (s->unk14 <= 0.0f || s->unk10.a == 0) {
            s->unk0 = 0;
        }
    }
}

// the sparks: textured, additive quads (all in the z = 0 plane of the hook's matrix)
void fn_1_68EC(HU3DMODEL *modelP, Mtx mtx)
{
    M514Sparks *sparks;
    M514Spark *s;
    s32 i;
    f32 size, x, y;

    sparks = modelP->hookData;
    HuSprTexLoad(sparks->unk0, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_OR);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    for (i = 0; i < 0x100; i++) {
        s = &sparks->unk4[i];
        if (s->unk0 == 0) {
            continue;
        }
        size = s->unk14;
        x = s->unk18;
        y = s->unk1C;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        M514Vtx(x - size, y - size, 0.0f, s->unk10);
        GXTexCoord2f32(0.0f, 0.0f);
        M514Vtx(x + size, y - size, 0.0f, s->unk10);
        GXTexCoord2f32(1.0f, 0.0f);
        M514Vtx(x + size, y + size, 0.0f, s->unk10);
        GXTexCoord2f32(1.0f, 1.0f);
        M514Vtx(x - size, y + size, 0.0f, s->unk10);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}

void fn_1_6C44(omObjData *arg0)
{
    s16 mdl;
    M514Foots *foots;
    s32 i;
    f64 deg;

    mdl = Hu3DHookFuncCreate(fn_1_6ED4);
    arg0->model[2] = mdl;
    Hu3DModelLayerSet(mdl, 4);
    foots = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Foots), MEMORY_DEFAULT_NUM);
    Hu3DData[mdl].hookData = foots;
    memset(foots, 0, sizeof(M514Foots));
    deg = 0.0;
    for (i = 0; i < 0x10; i++) {
        foots->unk3800[i] = (f32)sin(3.141592653589793 * deg / 180.0);
        foots->unk3840[i] = (f32)cos(3.141592653589793 * deg / 180.0);
        deg = (f64)((f32)deg + 22.0f);
    }
}

void fn_1_6D7C(omObjData *arg0)
{
    M514Foots *foots;
    M514Foot *f;
    s32 i;

    foots = Hu3DData[arg0->model[2]].hookData;
    f = foots->unk0;
    for (i = 0; i < 0x200; i++, f++) {
        switch (f->unk0) {
            case 1:
                f->unk0++;
                f->unkC.r = f->unkC.g = f->unkC.b = f->unkC.a = 0;
                // fall through
            case 2:
                f->unkC.a += 4;
                if (f->unkC.a < 0x30) {
                    break;
                }
                f->unk0++;
                f->unk4 = 0;
                f->unkC.a = 0x30;
                // fall through
            case 3:
                f->unk4++;
                if ((f32)f->unk4 < 300.0f) {
                    break;
                }
                f->unk0++;
                // fall through
            case 4:
                f->unkC.a--;
                if (f->unkC.a > 4) {
                    break;
                }
                f->unk0 = 0;
                break;
            default:
                break;
        }
    }
}

// the footprints: translucent discs (a 16-sided fan) on the ground
void fn_1_6ED4(HU3DMODEL *modelP, Mtx mtx)
{
    M514Foots *foots;
    M514Foot *f;
    Mtx m;
    s32 i, k;
    f32 r;

    foots = modelP->hookData;
    M514ColorPassInit();
    f = foots->unk0;
    for (i = 0; i < 0x200; i++, f++) {
        if (f->unk0 < 2) {
            continue;
        }
        r = f->unk8;
        MTXIdentity(m);
        MTXTrans(m, f->unk10, f->unk14, f->unk18);
        MTXConcat(mtx, m, m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 18);
        M514Vtx(0.0f, 0.0f, 0.0f, f->unkC);
        for (k = 0; k < 0x10; k++) {
            M514Vtx(r * foots->unk3800[k], 0.0f, r * foots->unk3840[k], f->unkC);
        }
        M514Vtx(foots->unk3800[0] * r, 0.0f, foots->unk3840[0] * r, f->unkC);
        GXEnd();
    }
}

s32 fn_1_79F8(Vec *arg0, f32 farg0)
{
    M514Arc *arc;
    s32 i;

    arc = Hu3DData[lbl_1_bss_218->model[0]].hookData;
    for (i = 0; i < 3; i++, arc++) {
        if (arc->unk0 == 0) {
            arc->unk0++;
            arc->unk8 = 1;
            arc->unk2C = arg0->x;
            arc->unk30 = arg0->y;
            arc->unk34 = arg0->z;
            arc->unk38 = arg0->x;
            arc->unk3C = arg0->y;
            arc->unk40 = arg0->z;
            arc->unk10 = farg0;
            arc->unkC = farg0;
            arc->unk14 = 1.0f;
            arc->unk20 = 5.0f;
            arc->unk1C = 5.0f;
            arc->unk24 = 0.0f;
            arc->unk28 = 1.0f;
            return i;
        }
    }
    return -1;
}

void fn_1_7B8C(s32 arg0)
{
    M514Arc *arc;

    if (arg0 >= 0 && arg0 < 3) {
        arc = &((M514Arc *)Hu3DData[lbl_1_bss_218->model[0]].hookData)[arg0];
        if (arc->unk0 != 0) {
            arc->unk0 = 3;
        }
    }
}

void fn_1_585C(HU3DMODEL *modelP, Mtx mtx)
{
    Mtx m;
    GXColor color;

    color.r = (lbl_1_data_4D0 >> 24) & 0xFF;
    color.g = (lbl_1_data_4D0 >> 16) & 0xFF;
    color.b = (lbl_1_data_4D0 >> 8) & 0xFF;
    color.a = lbl_1_data_4D0 & 0xFF;
    MTXIdentity(m);
    MTXTrans(m, ((M514Goal *)lbl_1_bss_210->data)->unk0, 0.0f, 0.0f);
    MTXConcat(mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    M514ColorPassInit();
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    M514Vtx(-15.0f, 1.0f, -240.0f, color);
    M514Vtx(15.0f, 1.0f, -240.0f, color);
    M514Vtx(15.0f, 1.0f, 230.0f, color);
    M514Vtx(-15.0f, 1.0f, 230.0f, color);
    GXEnd();
}

// the layer hooks set the fog of the layers they precede
static void M514FogSet(s32 idx, GXFogType type)
{
    f32 fov, nnear, ffar;
    GXColor color;

    Hu3DCameraPerspectiveGet(1, &fov, &nnear, &ffar);
    color.r = lbl_1_data_4A0[idx].unk8;
    color.g = lbl_1_data_4A0[idx].unk9;
    color.b = lbl_1_data_4A0[idx].unkA;
    color.a = lbl_1_data_4A0[idx].unkB;
    GXSetFog(type, lbl_1_data_4A0[idx].unk0, lbl_1_data_4A0[idx].unk4 * lbl_1_bss_214, nnear, ffar, color);
}

void fn_1_54DC(s16 layerNo)
{
    M514FogSet(0, GX_FOG_LIN);
}

void fn_1_5574(s16 layerNo)
{
    M514FogSet(1, GX_FOG_LIN);
}

void fn_1_5610(s16 layerNo)
{
    M514FogSet(2, GX_FOG_LIN);
}

void fn_1_56AC(s16 layerNo)
{
    M514FogSet(0, GX_FOG_NONE);
}

void fn_1_5B04(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    ANIMDATA **temp_r3_2;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x3C, 4U, 0U, -1, fn_1_5B90);
    lbl_1_bss_218 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x1C, MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 0x1C);
}

void fn_1_5B8C(void) {

}

void fn_1_5B90(omObjData *arg0) {
    fn_1_5C34(arg0);
    fn_1_6588(arg0);
    fn_1_6C44(arg0);
    fn_1_76D0(arg0);
    fn_1_7184(arg0);
    arg0->func = fn_1_5BEC;
}

void fn_1_5BEC(omObjData *obj) {
    fn_1_5CD4(obj);
    fn_1_6644(obj);
    fn_1_6D7C(obj);
    fn_1_77BC(obj);
}










void fn_1_7184(omObjData *arg0) {
    s16 temp_r3;
    s32 var_r28;
    HU3DPARTICLE *temp_r29;
    HU3DPARTICLEDATA *var_r31;

    temp_r3 = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 33), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x80);
    arg0->model[3] = temp_r3;
    temp_r29 = Hu3DData[temp_r3].hookData;
    Hu3DParticleBlendModeSet(temp_r3, 0U);
    Hu3DParticleHookSet(temp_r3, fn_1_728C);
    Hu3DModelLayerSet(temp_r3, 5);
    Hu3DModelPosSet(temp_r3, 0.0f, 0.0f, 0.0f);
    var_r31 = temp_r29->data;
    var_r28 = 0;
loop_2:
    if (var_r28 < (s16) temp_r29->maxCnt) {
        var_r31->time = -1;
        var_r31->scale = 0.0f;
        var_r28 += 1;
        var_r31++;
        goto loop_2;
    }
}

void fn_1_728C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    s16 temp_r0;
    s32 var_r30;

    var_r31 = particleP->data;
    var_r30 = 0;
loop_10:
    if (var_r30 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31->time += 1;
            var_r31->pos.x = (f32) ((f64) var_r31->pos.x + (100.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
            var_r31->pos.y = (f32) ((f64) var_r31->pos.y + (30.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
            var_r31->pos.z = (f32) ((f64) var_r31->pos.z + (100.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
            var_r31->accel.x = (f32) (2.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000)));
            var_r31->accel.y = (f32) (1.0 + (0.2 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
            var_r31->accel.z = (f32) (0.8 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000)));
            var_r31->scale = (f32) (80.0 + (30.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
            var_r31->zRot = (f32) (360.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)));
            var_r31->color.a = 0xC8;
            /* fallthrough */
        case 1:
            var_r31->scale += 5.0f;
            var_r31->color.a -= 2;
            if ((u8) var_r31->color.a > 0xF0U) {
                var_r31->time = -1;
                var_r31->scale = 0.0f;
            } else {
                var_r31->pos.x += var_r31->accel.x;
                var_r31->pos.y += var_r31->accel.y;
                var_r31->pos.z += var_r31->accel.z;
                var_r31->accel.x = (f32) ((f64) var_r31->accel.x * 0.95);
                var_r31->accel.y = (f32) ((f64) var_r31->accel.y - 0.03);
                var_r31->accel.z = (f32) ((f64) var_r31->accel.z * 0.95);
            }
            break;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_10;
    }
}

void fn_1_76D0(omObjData *arg0) {
    ANIMDATA *temp_r27;
    s16 temp_r3;
    M514Pop *temp_r28;

    temp_r28 = arg0->data;
    temp_r28->unk0 = 0;
    temp_r28->unk8 = 0.0f;
    temp_r28->unk10 = 0.0f;
    temp_r28->unk16 = -1;
    temp_r28->unk14 = -1;
    temp_r27 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 31), MEMORY_DEFAULT_NUM, HEAP_DATA));
    temp_r3 = HuSprGrpCreate(1);
    temp_r28->unkC = temp_r3;
    HuSprGrpPosSet(temp_r3, 288.0f, 410.0f);
    HuSprGrpMemberSet(temp_r3, 0, HuSprCreate(temp_r27, 0xA, 0));
    HuSprAttrSet(temp_r3, 0, 4);
}

void fn_1_77BC(omObjData *arg0) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    s16 temp_r30;
    s32 temp_r0;
    M514Pop *temp_r28;

    temp_r28 = arg0->data;
    temp_r30 = temp_r28->unkC;
    if ((s16) temp_r28->unk14 >= 0) {
        temp_f1 = (f32) ((f64) temp_r28->unk8 + 0.2);
        temp_r28->unk8 = temp_f1;
        if (temp_f1 > 1.0f) {
            temp_r28->unk8 = 1.0f;
        }
        HuSprTPLvlSet(temp_r30, 0, temp_r28->unk8);
        HuSprAttrReset(temp_r30, 0, 4);
        if ((s16) temp_r28->unk16 != (s16) temp_r28->unk14) {
            temp_r28->unk0 = 1;
            temp_r28->unk10 = 0.0f;
        }
    } else {
        temp_f1_2 = (f32) ((f64) temp_r28->unk8 - 0.2);
        temp_r28->unk8 = temp_f1_2;
        if (temp_f1_2 <= 0.0f) {
            temp_r28->unk8 = 0.0f;
            HuSprAttrSet(temp_r30, 0, 4);
        } else {
            HuSprTPLvlSet(temp_r30, 0, temp_r28->unk8);
        }
    }
    temp_r0 = temp_r28->unk0;
    switch (temp_r0) {                              /* irregular */
    case 1:
        temp_f1_3 = (f32) ((f64) temp_r28->unk10 + 0.3);
        temp_r28->unk10 = temp_f1_3;
        if (!(temp_f1_3 < 1.5f)) {
            temp_r28->unk0 = (s32) (temp_r28->unk0 + 1);
        }
        break;
    case 2:
        temp_f1_4 = (f32) ((f64) temp_r28->unk10 - 0.1);
        temp_r28->unk10 = temp_f1_4;
        if (!(temp_f1_4 > 1.0f)) {
            temp_r28->unk0 = 0;
            temp_r28->unk10 = 1.0f;
        }
        break;
    }
    HuSprScaleSet(temp_r30, 0, temp_r28->unk10, temp_r28->unk10);
    if ((s16) temp_r28->unk14 != (s16) temp_r28->unk16) {
        if ((s16) temp_r28->unk14 >= 0) {
            HuSprBankSet(temp_r30, 0, temp_r28->unk14);
        }
        temp_r28->unk16 = (s16) temp_r28->unk14;
    }
}




void fn_1_7C10(s32 arg0, Vec *arg1) {
    f32 temp_f1;
    s32 temp_r0;
    s32 var_r27;
    M514Arc *temp_r31;

    var_r27 = 0;
    if ((arg0 >= 0) && (arg0 < 3)) {
        temp_r31 = &((M514Arc *) Hu3DData[lbl_1_bss_218->model[0]].hookData)[arg0];
        if (arg1->y < temp_r31->unk3C) {
            var_r27 = 1;
        }
        if (temp_r31->unk24 < arg1->y) {
            temp_r31->unk24 = (f32) arg1->y;
        }
        temp_r31->unk38 = (f32) ((f64) temp_r31->unk38 + (0.1 * (f64) (arg1->x - temp_r31->unk38)));
        temp_r31->unk3C = (f32) ((f64) temp_r31->unk3C + (0.1 * (f64) (arg1->y - temp_r31->unk3C)));
        temp_r31->unk40 = (f32) arg1->z;
        temp_r31->unk28 = (f32) (1.0 - ((f64) (temp_r31->unk38 - temp_r31->unk2C) / 4000.0));
        temp_r31->unkC = (f32) ((f64) temp_r31->unk10 * (0.9 * (1.0 + (1.0 - (f64) temp_r31->unk28))));
        if ((temp_r31->unk20 < 120.0f) && (var_r27 == 0)) {
            temp_f1 = temp_r31->unk20 + 4.0f;
            temp_r31->unk20 = temp_f1;
            if (temp_f1 > 120.0f) {
                temp_r31->unk20 = 120.0f;
            }
        } else if (0.0f != temp_r31->unk24) {
            temp_r31->unk20 = (f32) (120.0 + (60.0 * (f64) ((temp_r31->unk24 - arg1->y) / temp_r31->unk24)));
        }
        temp_r31->unk1C = (f32) ((f64) temp_r31->unk1C + (0.2 * (f64) (temp_r31->unk20 - temp_r31->unk1C)));
        if (temp_r31->unk1C > 180.0f) {
            temp_r31->unk1C = 180.0f;
        }
        temp_r0 = temp_r31->unk8 - 1;
        temp_r31->unk8 = temp_r0;
        if (temp_r0 <= 0) {
            temp_r31->unk8 = 2;
            fn_1_7EBC(arg1);
        }
    }
}

void fn_1_7EBC(Vec *arg0) {
    s32 var_r29;
    M514Spark *temp_r31;

    var_r29 = 0;
loop_4:
    if (var_r29 >= 0x100) {
        return;
    }
    temp_r31 = &((M514Sparks *) Hu3DData[lbl_1_bss_218->model[1]].hookData)->unk4[var_r29];
    if ((s32) temp_r31->unk0 == 0) {
        temp_r31->unk0 = 1;
        temp_r31->unk4 = frand();
        temp_r31->unk8 = frand();
        temp_r31->unkC = frand();
        temp_r31->unk10.r = temp_r31->unk10.g = temp_r31->unk10.b = temp_r31->unk10.a = 0xFF;
        temp_r31->unk14 = (f32) (40.0 + (20.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
        temp_r31->unk18 = (f32) (((f64) arg0->x + (30.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000)))) - 50.0);
        temp_r31->unk1C = (f32) ((f64) arg0->y + (50.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
        temp_r31->unk20 = (f32) ((f64) arg0->z - 100.0);
        return;
    }
    var_r29 += 1;
    goto loop_4;
}

void fn_1_80C0(Vec *arg0, f32 farg0) {
    s32 var_r30;
    M514Foot *var_r31;

    var_r31 = ((M514Foots *) Hu3DData[lbl_1_bss_218->model[2]].hookData)->unk0;
    var_r30 = 0;
loop_4:
    if (var_r30 >= 0x200) {
        return;
    }
    if ((s32) var_r31->unk0 == 0) {
        var_r31->unk0 = (s32) (var_r31->unk0 + 1);
        var_r31->unk10 = (f32) arg0->x;
        var_r31->unk14 = (f32) (3.0 + (f64) arg0->y);
        var_r31->unk18 = (f32) arg0->z;
        var_r31->unk8 = farg0;
        return;
    }
    var_r30 += 1;
    var_r31++;
    goto loop_4;
}

void fn_1_8180(Vec *arg0) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    temp_r30 = Hu3DData[(s16) lbl_1_bss_218->model[3]].hookData;
    var_r31 = temp_r30->data;
    var_r29 = 0;
loop_4:
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        return;
    }
    if ((s16) var_r31->time < 0) {
        var_r31->time = 0;
        var_r31->pos.x = (f32) arg0->x;
        var_r31->pos.y = (f32) arg0->y;
        var_r31->pos.z = (f32) arg0->z;
        return;
    }
    var_r29 += 1;
    var_r31++;
    goto loop_4;
}

void fn_1_8228(s16 arg0) {
    ((M514Pop *)lbl_1_bss_218->data)->unk14 = arg0;
}



void ObjectSetup(void) {
    Mtx sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    HU3DLIGHT *temp_r30;
    s32 var_r31;

    sp14 = lbl_1_rodata_10.unk0;
    sp18 = lbl_1_rodata_10.unk4;
    sp1C = lbl_1_rodata_10.unk8;
    sp8 = lbl_1_rodata_1C.unk0;
    spC = lbl_1_rodata_1C.unk4;
    sp10 = lbl_1_rodata_1C.unk8;
    lbl_1_bss_60 = 0;
    lbl_1_bss_58 = 0;
    lbl_1_bss_56 = 0;
    lbl_1_bss_50 = -1;
    lbl_1_bss_4C = -1;
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        lbl_1_bss_10[var_r31] = -1;
        lbl_1_bss_18[var_r31] = -1;
        lbl_1_bss_20[var_r31] = -1;
        lbl_1_bss_8[var_r31] = 0;
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_68 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_68);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, lbl_1_data_0, lbl_1_data_4, 1.2f);
    lbl_1_bss_64 = omAddObjEx(lbl_1_bss_68, 0x7FDA, 0U, 0U, -1, fn_1_98C);
    omCameraViewSet(lbl_1_data_C);
    lbl_1_bss_54 = Hu3DGLightCreateV(&lbl_1_data_44, &lbl_1_data_50, &lbl_1_data_68);
    Hu3DGLightInfinitytSet(lbl_1_bss_54);
    temp_r30 = &Hu3DGlobalLight[lbl_1_bss_54];
    temp_r30->type |= 0x8000;
    lbl_1_bss_40.z = 0.0f;
    lbl_1_bss_40.y = 0.0f;
    lbl_1_bss_40.x = 0.0f;
    lbl_1_bss_34.z = 0.0f;
    lbl_1_bss_34.x = 0.0f;
    lbl_1_bss_34.y = lbl_1_data_5C.unk8;
    mtxRot(sp20, lbl_1_data_5C.unk0, lbl_1_data_5C.unk4, 0.0f);
    MTXMultVec(sp20, &lbl_1_bss_34, &lbl_1_bss_34);
    Hu3DGLightPosAimSetV(lbl_1_bss_54, &lbl_1_bss_34, &lbl_1_bss_40);
    VECSubtract(&lbl_1_bss_40, &lbl_1_bss_34, &lbl_1_bss_28);
    MgSeqCreate(&lbl_1_data_90);
}

void fn_1_3A0(s16 mode, s16 frameNo) {
    fn_1_8268(lbl_1_bss_68);
    fn_1_5B04(lbl_1_bss_68);
    fn_1_510C(lbl_1_bss_68);
    fn_1_1D9C(lbl_1_bss_68);
    fn_1_4270(lbl_1_bss_68);
    lbl_1_bss_4 = 0;
    lbl_1_bss_0 = 0;
    fn_1_163C(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 5), MEMORY_DEFAULT_NUM, HEAP_DATA));
    MgSeqModeNext();
}

void fn_1_448(s16 arg1, s16 frameNo) {
    if (frameNo == 0) {
        lbl_1_bss_5C = 0;
    }
    if (((s32) lbl_1_bss_4C == -1) && (frameNo >= 0x12)) {
        lbl_1_bss_4C = HuAudFXPlay(0x6DD);
    }
    switch ((s32) lbl_1_bss_5C) {                   /* irregular */
    case 0:
        if (frameNo >= 0x1E) {
            lbl_1_bss_5C += 1;
        case 1:
            if (fn_1_16AC() == 0) {
                lbl_1_bss_5C += 1;
                MgSeqModeNext();
            }
        }
        return;
    }
}

void fn_1_540(s16 arg1, s16 frameNo) {
    s16 sp8;

    sp8 = frameNo;
    if (sp8 == 0) {
        lbl_1_bss_50 = HuAudBGMPlay(0x34);
    }
}

void fn_1_580(s16 mode, s16 frameNo) {
    s32 temp_r0;
    s32 var_r31;

    var_r31 = 0;
    if ((s32) lbl_1_bss_0 != 0) {
        lbl_1_bss_0 = 0;
        temp_r0 = lbl_1_bss_4 + 1;
        lbl_1_bss_4 = temp_r0;
        if (temp_r0 >= 4) {
            var_r31 = 1;
        }
    }
    if (var_r31 != 0) {
        MgSeqModeNext();
    }
}

void fn_1_600(s16 arg1, s16 frameNo) {
    s32 spC[4];
    u16 spA;
    s16 sp8;
    s32 temp_r3;
    s32 var_r29;
    s32 var_r31;
    s32 var_r31_2;

    sp8 = frameNo;
    var_r29 = 0;
    if (sp8 == 0) {
        if ((s32) lbl_1_bss_50 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_50, 0x64);
            lbl_1_bss_50 = -1;
        }
        lbl_1_bss_56 = 0;
        var_r31 = 0;
loop_7:
        if (var_r31 < 4) {
            temp_r3 = fn_1_95BC(var_r31);
            if (temp_r3 > var_r29) {
                var_r29 = temp_r3;
            }
            spC[var_r31] = temp_r3;
            var_r31 += 1;
            goto loop_7;
        }
        var_r31_2 = 0;
loop_13:
        if (var_r31_2 < 4) {
            lbl_1_bss_20[var_r31_2] = -1;
            if (((s16) lbl_1_bss_8[var_r31_2] != 0) && (var_r29 == (s32) spC[var_r31_2])) {
                lbl_1_bss_20[var_r31_2] = lbl_1_bss_10[var_r31_2];
            }
            var_r31_2 += 1;
            goto loop_13;
        }
        spA = MgSeqWinnerSet(lbl_1_bss_20[0], lbl_1_bss_20[1], lbl_1_bss_20[2], lbl_1_bss_20[3]);
        if (0 == 0) {
            lbl_1_bss_58 = fn_1_9820();
            return;
        }
        fn_1_98F4();
    }
}

void fn_1_7B0(s16 arg1, s16 frameNo) {
    if (0 != 0) {
        MgSeqModeSet(9U);
        return;
    }
    if (frameNo == 0) {
        lbl_1_data_C[1].center.x = fn_1_9688();
        omCameraViewMove(&lbl_1_data_C[1], 0x48, 0);
    }
    if ((frameNo == 0x5A) && ((s32) lbl_1_bss_58 != 0) && (_CheckFlag(MP5_PRACTICE_FLAG) == 0)) {
        HuAudJinglePlay(0x86);
    }
    if ((((s32) lbl_1_bss_58 == 0) || (_CheckFlag(MP5_PRACTICE_FLAG) != 0)) && (frameNo >= 0x5A)) {
        MgSeqModeNext();
    }
}

void fn_1_8A0(s16 arg1, s16 frameNo) {
    s16 sp8;
    s16 temp_r30;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 == 0) {
        var_r31 = 0;
loop_6:
        if (var_r31 < 4) {
            if ((s16) lbl_1_bss_20[var_r31] >= 0) {
                temp_r30 = GWPlayer[var_r31].coin_win + 0xA;
                if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                    GWPlayer[var_r31].coin_win = temp_r30;
                }
            }
            var_r31 += 1;
            goto loop_6;
        }
    }
}

void fn_1_958(s16 mode, s16 frameNo) {

}

void fn_1_95C(s16 mode, s16 frameNo) {
    fn_1_5B8C();
    fn_1_51BC();
    fn_1_1EA0();
    fn_1_4344();
    fn_1_8300();
}

void fn_1_98C(omObjData *arg0) {
    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, 8, MEMORY_DEFAULT_NUM);
    memset((ANIMDATA **) arg0->data, 0, 8);
    arg0->func = fn_1_9E4;
}

void fn_1_9E4(omObjData *obj) {
    Vec sp18;
    Vec sp3C;
    Vec sp48;
    Vec sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp14;
    f32 sp10;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f31;
    f32 var_f23;
    f32 var_f24;
    f64 temp_f21;
    f64 temp_f21_10;
    f64 temp_f21_11;
    f64 temp_f21_12;
    f64 temp_f21_2;
    f64 temp_f21_3;
    f64 temp_f21_4;
    f64 temp_f21_5;
    f64 temp_f21_6;
    f64 temp_f21_7;
    f64 temp_f21_8;
    f64 temp_f21_9;
    f64 temp_f22;
    f64 temp_f22_2;
    f64 temp_f22_3;
    f64 temp_f22_4;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    f64 temp_f30;
    f64 temp_f30_2;
    f64 temp_f30_3;
    M514Cam *temp_r31;

    temp_r31 = obj->data;
    temp_f1 = (f32) ((f64) lbl_1_data_8 + 0.40000002086162567);
    lbl_1_data_8 = temp_f1;
    if (temp_f1 > 120.0f) {
        lbl_1_data_8 = 120.0f;
    }
    Mp5CameraPosGet(1, &sp48, &sp30, &sp3C);
    fn_1_14F4(&lbl_1_bss_28, &sp3C, 1200.0f);
    if ((s32) temp_r31->unk0 != 0) {
        if (Hu3DMotionEndCheck(temp_r31->unk6) != 0) {
            Hu3DModelKill(temp_r31->unk6);
            Center.x = sp3C.x;
            Center.y = sp3C.y;
            Center.z = sp3C.z;
            temp_f0 = sp48.x - sp3C.x;
            sp18.x = temp_f0;
            sp18.y = sp48.y - sp3C.y;
            temp_f0_2 = sp48.z - sp3C.z;
            sp18.z = temp_f0_2;
            temp_f28 = (sp18.x * temp_f0) + (sp18.z * temp_f0_2);
            var_f24 = sqrtf(temp_f28);
            CRot.x = (f32) (57.295780181884766 * atan2(-sp18.y, (f64) var_f24));
            CRot.y = (f32) (57.295780181884766 * atan2((f64) sp18.x, (f64) sp18.z));
            CRot.z = 0.0f;
            temp_f27 = (sp18.z * sp18.z) + ((sp18.x * sp18.x) + (sp18.y * sp18.y));
            var_f23 = sqrtf(temp_f27);
            CZoom = var_f23;
            temp_r31->unk0 = 0;
            goto block_11;
        }
    } else {
block_11:
        temp_f26 = CRot.x;
        temp_f25 = CRot.y;
        temp_f31 = CRot.z;
        temp_f21 = cos((3.141592653589793 * (f64) temp_f26) / 180.0);
        sp48.x = (f32) ((f64) Center.x + ((f64) CZoom * (sin((3.141592653589793 * (f64) temp_f25) / 180.0) * temp_f21)));
        sp48.y = (f32) ((f64) Center.y + ((f64) CZoom * -sin((3.141592653589793 * (f64) temp_f26) / 180.0)));
        temp_f21_2 = cos((3.141592653589793 * (f64) temp_f26) / 180.0);
        sp48.z = (f32) ((f64) Center.z + ((f64) CZoom * (cos((3.141592653589793 * (f64) temp_f25) / 180.0) * temp_f21_2)));
        sp3C.x = Center.x;
        sp3C.y = Center.y;
        sp3C.z = Center.z;
        temp_f21_3 = sin((3.141592653589793 * (f64) temp_f26) / 180.0);
        sp24 = (f32) (sin((3.141592653589793 * (f64) temp_f25) / 180.0) * temp_f21_3);
        sp28 = (f32) cos((3.141592653589793 * (f64) temp_f26) / 180.0);
        temp_f21_4 = sin((3.141592653589793 * (f64) temp_f26) / 180.0);
        sp2C = (f32) (cos((3.141592653589793 * (f64) temp_f25) / 180.0) * temp_f21_4);
        VECSubtract(&sp48, &sp3C, &sp18);
        VECNormalize(&sp18, &sp18);
        temp_f21_5 = (f64) sp18.y * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f22 = (f64) sp2C * (((f64) (sp18.x * sp18.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f21_5);
        temp_f21_6 = (f64) sp18.z * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f21_7 = (f64) sp28 * (((f64) (sp18.x * sp18.y) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f21_6);
        sp30.x = (f32) (((f64) sp24 * ((f64) (sp18.x * sp18.x) + ((f64) (1.0f - (sp18.x * sp18.x)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f21_7 + temp_f22);
        temp_f21_8 = (f64) sp18.x * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f21_9 = (f64) sp2C * (((f64) (sp18.y * sp18.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f21_8);
        temp_f22_2 = (f64) sp18.z * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f22_3 = (f64) sp24 * (((f64) (sp18.x * sp18.y) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f22_2);
        sp30.y = (f32) (((f64) sp28 * ((f64) (sp18.y * sp18.y) + ((f64) (1.0f - (sp18.y * sp18.y)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f22_3 + temp_f21_9);
        temp_f21_10 = (f64) sp18.x * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f22_4 = (f64) sp28 * (((f64) (sp18.y * sp18.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f21_10);
        temp_f21_11 = (f64) sp18.y * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
        temp_f21_12 = ((f64) sp24 * (((f64) (sp18.x * sp18.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f21_11)) + temp_f22_4;
        sp30.z = (f32) (((f64) sp2C * ((f64) (sp18.z * sp18.z) + ((f64) (1.0f - (sp18.z * sp18.z)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f21_12);
        VECNormalize(&sp30, &sp30);
        sp8 = sp3C.z;
        Hu3DCameraPosSet(1, sp48.x, sp48.y, sp48.z, sp30.x, sp30.y, sp30.z, sp3C.x, sp3C.y, sp3C.z);
    }
}

void fn_1_14F4(Vec *arg0, Vec *arg1, f32 farg0) {
    Vec sp18;
    Vec spC;
    Vec *sp8;
    Vec *var_r31;
    f32 temp_f31;

    sp8 = arg0;
    var_r31 = lbl_1_rodata_88;
    temp_f31 = farg0 / (f32) tan(0.1745329201221466);
    VECNormalize(arg0, &spC);
    VECScale(&spC, &sp18, temp_f31);
    VECSubtract(arg1, &sp18, &sp18);
    if (fabs(spC.y) > 0.5f) {
        var_r31 = &lbl_1_rodata_88[1];
    }
    Hu3DShadowCreate(20.0f, temp_f31 - farg0, temp_f31 + farg0);
    Hu3DShadowPosSet(&sp18, var_r31, arg1);
    Hu3DShadowSizeSet(0x1E0U);
    Hu3DShadowTPLvlSet(0.4f);
}

void fn_1_163C(void *arg0) {
    void *sp8;
    M514Cam *temp_r31;

    sp8 = arg0;
    temp_r31 = lbl_1_bss_64->data;
    temp_r31->unk4 = Hu3DMotionCreate(arg0);
    temp_r31->unk6 = Hu3DModelCameraCreate(temp_r31->unk4, 1U);
    Hu3DCameraMotionStart(temp_r31->unk6, 1U);
    temp_r31->unk0 = 1;
}

s32 fn_1_16AC(void) {
    return ((M514Cam *)lbl_1_bss_64->data)->unk0;
}


s16 fn_1_16EC(s32 arg0) {
    return lbl_1_bss_20[arg0];
}

u32 fn_1_1704(u32 arg0) {
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    u32 var_r30;

    var_r31 = 0;
loop_3:
    if (var_r31 < 4) {
        if ((s16) lbl_1_bss_20[var_r31] < 0) {
            var_r31 += 1;
            goto loop_3;
        }
    }
    if (var_r31 >= 4) {
        var_r31_2 = 0;
loop_10:
        if (var_r31_2 >= 4) {
            return 0U;
        }
        if ((arg0 == (u32) lbl_1_bss_18[var_r31_2]) && ((s16) lbl_1_bss_8[var_r31_2] != 0)) {
            return 1U;
        }
        var_r31_2 += 1;
        goto loop_10;
    }
    var_r31_3 = 0;
loop_19:
    if (var_r31_3 >= 4) {
        return arg0;
    }
    if (arg0 == (u32) lbl_1_bss_18[var_r31_3]) {
        if ((s16) lbl_1_bss_20[var_r31_3] >= 0) {
            var_r30 = 1;
        } else {
            var_r30 = -1U;
        }
        return var_r30;
    }
    var_r31_3 += 1;
    goto loop_19;
}

s32 fn_1_1814(void) {
    return lbl_1_bss_4;
}

void fn_1_1824(void) {
    lbl_1_bss_0 = 1;
}

void fn_1_1838(s32 arg0, s16 arg1, s16 arg2) {
    s32 temp_r3;

    temp_r3 = arg0 & 3;
    lbl_1_bss_18[temp_r3] = arg1;
    lbl_1_bss_10[temp_r3] = arg2;
}

void fn_1_1870(s32 arg0) {
    lbl_1_bss_8[arg0 & 3] = 1;
}

void fn_1_1890(void) {
    s32 temp_r0;

    temp_r0 = lbl_1_bss_60 + 1;
    lbl_1_bss_60 = temp_r0;
    if (temp_r0 == 4) {
        CharLoseVoicePlay(lbl_1_bss_10[0], lbl_1_bss_10[1], lbl_1_bss_10[2], lbl_1_bss_10[3]);
    }
}


s16 fn_1_1960(Vec *arg0) {
    Vec spC;
    Vec *sp8;
    s16 var_r31;

    sp8 = arg0;
    Hu3D3Dto2D(arg0, 1, &spC);
    var_r31 = (s16) (48.0f + (spC.x * 0.055555556f));
    if (var_r31 < 0x30) {
        var_r31 = 0x30;
    }
    if (var_r31 > 0x50) {
        var_r31 = 0x50;
    }
    return var_r31;
}

s16 fn_1_19F4(void) {
    return (s16) lbl_1_data_8;
}


void fn_1_1AF4(s32 arg0, Vec *arg1) {
    Vec spC;
    Vec *sp8;
    s16 var_r31;

    sp8 = arg1;
    if ((arg0 != -1) && (HuAudFXStatusGet(arg0) == 2)) {
        Hu3D3Dto2D(sp8, 1, &spC);
        var_r31 = (s16) (48.0f + (spC.x * 0.055555556f));
        if (var_r31 < 0x30) {
            var_r31 = 0x30;
        }
        if (var_r31 > 0x50) {
            var_r31 = 0x50;
        }
        HuAudFXPanning(arg0, var_r31);
    }
}

f32 fn_1_1BCC(f32 farg0, f32 farg1, f32 farg2) {
    f32 spC;
    f32 sp8;
    f32 var_f31;
    f32 var_f31_2;

    sp8 = farg1;
    spC = farg2;
    var_f31_2 = (f32) fmod((f64) (sp8 - farg0), 360.0);
    if (var_f31_2 < 0.0f) {
        var_f31_2 += 360.0f;
    }
    if (var_f31_2 > 180.0f) {
        var_f31_2 -= 360.0f;
    }
    var_f31 = (f32) fmod((f64) (farg0 + (spC * var_f31_2)), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}

f32 fn_1_1CE8(f32 farg0, f32 farg1) {
    f32 spC;
    f32 sp8;
    f32 var_f31;

    sp8 = farg0;
    spC = farg1;
    var_f31 = (f32) fmod((f64) (spC - sp8), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

void fn_1_4270(HUPROCESS *arg0) {
    ANIMDATA **temp_r3_2;
    M514ObsDef *var_r30;
    omObjData *temp_r3;

    temp_r3 = omAddObjEx(arg0, 0x32, 0U, 0U, -1, fn_1_4348);
    lbl_1_bss_208 = temp_r3;
    temp_r3->stat |= 0x100;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, 4, MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 4);
    fn_1_435C();
    var_r30 = lbl_1_data_3B4;
loop_2:
    if ((s32) var_r30->unk0 != -1) {
        fn_1_45D4(arg0, var_r30);
        var_r30++;
        goto loop_2;
    }
}

void fn_1_4344(void) {

}

void fn_1_4348(omObjData *arg0) {
    arg0->func = fn_1_4358;
}

void fn_1_4358(omObjData *obj) {

}

void fn_1_435C(void) {
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x20) {
        lbl_1_bss_188[var_r31] = -1;
        lbl_1_bss_C8[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 0x20) {
        lbl_1_bss_108[var_r31_2] = -1;
        lbl_1_bss_88[var_r31_2] = -1;
        var_r31_2 += 1;
        goto loop_5;
    }
}



void fn_1_45D4(HUPROCESS *arg0, M514ObsDef *arg1) {
    s32 spC;
    HUPROCESS *sp8;
    M514Obs *temp_r3;
    M514MotEnt *var_r24;
    omObjData *temp_r29;
    Vec *temp_r4;
    s16 temp_r17;
    s16 temp_r23;
    s16 var_r19;
    s16 var_r21;
    s32 temp_r0;
    s32 temp_r18;
    s32 temp_r20;
    s32 var_r26;
    s32 var_r27;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    u32 temp_r25;

    sp8 = arg0;
    temp_r29 = omAddObjEx(arg0, 0x32, 3U, 2U, 0, arg1->unk18);
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Obs), MEMORY_DEFAULT_NUM);
    temp_r29->data = temp_r3;
    memset(temp_r3, 0, 0x58);
    temp_r29->stat |= 0x100;
    temp_r3->unk0 = arg1;
    temp_r3->unk10 = -1;
    temp_r3->unk14 = -1;
    temp_r3->unk18 = -1;
    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        temp_r29->model[var_r30] = -1;
        var_r30 += 1;
        goto loop_2;
    }
    var_r30_2 = 0;
loop_5:
    if (var_r30_2 < 2) {
        temp_r29->motion[var_r30_2] = -1;
        var_r30_2 += 1;
        goto loop_5;
    }
    temp_r20 = arg1->unk8;
    var_r27 = 0;
loop_11:
    if (var_r27 >= 0x20) {
        goto block_12;
    }
    temp_r18 = lbl_1_bss_188[var_r27];
    if (temp_r18 != -1) {
        if (temp_r20 == temp_r18) {
            var_r21 = Hu3DModelLink(lbl_1_bss_C8[var_r27]);
        } else {
            var_r27 += 1;
            goto loop_11;
        }
    } else {
block_12:
        if (var_r27 < 0x20) {
            temp_r23 = Hu3DModelCreate(HuDataSelHeapReadNum(temp_r20, MEMORY_DEFAULT_NUM, HEAP_DATA));
            lbl_1_bss_188[var_r27] = temp_r20;
            lbl_1_bss_C8[var_r27] = temp_r23;
            var_r21 = temp_r23;
        } else {
            var_r21 = -1;
        }
    }
    *temp_r29->model = var_r21;
    var_r24 = arg1->unkC;
    var_r30_3 = 0;
loop_29:
    if (var_r30_3 < 2) {
        temp_r25 = var_r24->unk0;
        if ((s32) temp_r25 != -2) {
            if ((s32) temp_r25 != -1) {
                var_r26 = 0;
loop_23:
                if (var_r26 >= 0x20) {
                    goto block_24;
                }
                temp_r0 = lbl_1_bss_108[var_r26];
                spC = temp_r0;
                if (temp_r0 != -1) {
                    if ((s32) temp_r25 == spC) {
                        var_r19 = lbl_1_bss_88[var_r26];
                    } else {
                        var_r26 += 1;
                        goto loop_23;
                    }
                } else {
block_24:
                    if (var_r26 < 0x20) {
                        temp_r17 = Hu3DJointMotion(var_r21, HuDataSelHeapReadNum((s32) temp_r25, MEMORY_DEFAULT_NUM, HEAP_DATA));
                        lbl_1_bss_108[var_r26] = (s32) temp_r25;
                        lbl_1_bss_88[var_r26] = temp_r17;
                        var_r19 = temp_r17;
                    } else {
                        var_r19 = -1;
                    }
                }
                temp_r29->motion[var_r30_3] = var_r19;
            }
            var_r30_3 += 1;
            var_r24++;
            goto loop_29;
        }
    }
    temp_r4 = arg1->unk10;
    temp_r3->unk1C.x = (f32) temp_r4->x;
    temp_r3->unk1C.y = (f32) temp_r4->y;
    temp_r3->unk1C.z = (f32) temp_r4->z;
    temp_r3->unk34.y = (f32) arg1->unk14;
    Hu3DModelLayerSet(var_r21, 4);
    fn_1_48B0(temp_r29);
}

void fn_1_48B0(omObjData *arg0) {
    s16 temp_r29;
    M514Obs *temp_r30;

    temp_r30 = arg0->data;
    temp_r29 = *arg0->model;
    Hu3DModelPosSetV(temp_r29, &temp_r30->unk1C);
    Hu3DModelRotSetV(temp_r29, &temp_r30->unk34);
}



void fn_1_4A4C(omObjData *arg0) {
    HSFOBJECT *temp_r3_3;
    s16 temp_r24;
    s16 temp_r25;
    s16 temp_r3;
    s16 temp_r3_2;
    M514MotEnt *temp_r27;
    M514Obs *temp_r28;
    M514Obs *temp_r31;

    temp_r31 = arg0->data;
    Hu3DModelShadowSet(arg0->model[0]);
    temp_r28 = arg0->data;
    if ((s32) temp_r28->unk10 != 0) {
        temp_r25 = *arg0->motion;
        if (temp_r25 != -1) {
            temp_r27 = temp_r28->unk0->unkC;
            temp_r24 = arg0->model[0];
            if ((s32) temp_r28->unk10 < 0) {
                Hu3DMotionSet(temp_r24, temp_r25);
                Hu3DModelAttrSet(temp_r24, temp_r27->unk8);
            } else {
                Hu3DMotionShiftSet(temp_r24, temp_r25, 0.0f, 60.0f * temp_r27->unk4, temp_r27->unk8);
            }
            temp_r28->unk10 = 0;
        }
    }
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_45C[temp_r31->unk0->unk4], MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[1] = temp_r3;
    Hu3DModelPosSet(temp_r3, temp_r31->unk1C.x, temp_r31->unk1C.y, (f32) ((f64) temp_r31->unk1C.z - 50.0));
    Hu3DModelLayerSet(temp_r3, 4);
    if ((s32) temp_r31->unk0->unk0 == 3) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 18), MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[2] = temp_r3_2;
        Hu3DModelPosSet(temp_r3_2, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        Hu3DModelAttrSet(temp_r3_2, 1U);
        Hu3DModelLayerSet(temp_r3_2, 4);
    }
    if ((s32) temp_r31->unk0->unk0 == 4) {
        temp_r3_3 = Hu3DModelObjPtrGet(arg0->model[0], lbl_1_data_470);
        if (temp_r3_3 != NULL) {
            temp_r3_3->flags |= 0x400;
        }
    }
    arg0->func = fn_1_4C40;
}

void fn_1_4C40(omObjData *obj) {
    s16 temp_r19;
    s16 temp_r20;
    s16 temp_r21;
    s16 temp_r22;
    s16 temp_r23;
    s16 temp_r29;
    s16 temp_r29_2;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    u32 temp_r0;
    M514Obs *temp_r18;
    M514Flag *temp_r24;
    M514MotEnt *temp_r25;
    M514MotEnt *temp_r26;
    M514Obs *temp_r27;
    M514Obs *temp_r28;
    M514Obs *temp_r31;

    temp_r24 = lbl_1_bss_208->data;
    temp_r31 = obj->data;
    temp_r0 = temp_r31->unk4;
    switch (temp_r0) {                              /* switch 1 */
    case 0:                                         /* switch 1 */
        temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
        /* fallthrough */
    case 1:                                         /* switch 1 */
        if (MgSeqModeGet() == 5) {
            temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
        case 2:                                     /* switch 1 */
            temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
            temp_r31->unk44 = fn_1_1814();
            temp_r28 = obj->data;
            if ((s32) temp_r28->unk10 != 0) {
                temp_r23 = obj->motion[0];
                if (temp_r23 != -1) {
                    temp_r26 = temp_r28->unk0->unkC;
                    temp_r22 = obj->model[0];
                    if ((s32) temp_r28->unk10 < 0) {
                        Hu3DMotionSet(temp_r22, temp_r23);
                        Hu3DModelAttrSet(temp_r22, temp_r26->unk8);
                    } else {
                        Hu3DMotionShiftSet(temp_r22, temp_r23, 0.0f, 60.0f * temp_r26->unk4, temp_r26->unk8);
                    }
                    temp_r28->unk10 = 0;
                }
            }
        case 3:                                     /* switch 1 */
            if (!(fn_1_95F4(fn_1_1814()) < temp_r31->unk1C.x)) {
                temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
                temp_r31->unk8 = 0;
                temp_r27 = obj->data;
                if ((s32) temp_r27->unk10 != 1) {
                    temp_r21 = obj->motion[1];
                    if (temp_r21 != -1) {
                        temp_r25 = temp_r27->unk0->unkC + 1;
                        temp_r20 = obj->model[0];
                        if ((s32) temp_r27->unk10 < 0) {
                            Hu3DMotionSet(temp_r20, temp_r21);
                            Hu3DModelAttrSet(temp_r20, temp_r25->unk8);
                        } else {
                            Hu3DMotionShiftSet(temp_r20, temp_r21, 0.0f, 60.0f * temp_r25->unk4, temp_r25->unk8);
                        }
                        temp_r27->unk10 = 1;
                    }
                }
                temp_r0_2 = temp_r31->unk0->unk0;
                switch (temp_r0_2) {                /* switch 2; irregular */
                case 4:                             /* switch 2 */
                    break;
                case 0:                             /* switch 2 */
                    temp_r31->unk14 = HuAudFXPlay(0x2CF);
                    break;
                case 1:                             /* switch 2 */
                    temp_r31->unk14 = HuAudFXPlay(0x2C4);
                    break;
                case 2:                             /* switch 2 */
                    temp_r31->unk14 = HuAudFXPlay(0x2D4);
                    break;
                case 3:                             /* switch 2 */
                    temp_r31->unk14 = HuAudFXPlay(0x2D7);
                    temp_r31->unk4 = 5U;
                    temp_r24->unk0 = 1;
                    break;
                }
            }
        }
        break;
    case 4:                                         /* switch 1 */
        if ((s32) temp_r31->unk44 != fn_1_1814()) {
            temp_r31->unk4 = 2U;
        }
        break;
    case 5:                                         /* switch 1 */
        temp_r0_3 = temp_r31->unk8 + 1;
        temp_r31->unk8 = temp_r0_3;
        if (!((f32) (f64) temp_r0_3 < 90.0f)) {
            temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
            temp_r31->unk8 = 0;
            temp_r29 = obj->model[2];
            Hu3DMotionTimeSet(temp_r29, 0.0f);
            Hu3DModelAttrReset(temp_r29, 0x40000002U);
            Hu3DModelAttrReset(temp_r29, 1U);
            temp_r31->unk18 = HuAudFXPlay(0x6DE);
        case 6:                                     /* switch 1 */
            temp_r0_4 = temp_r31->unk8 + 1;
            temp_r31->unk8 = temp_r0_4;
            if (!((f32) (f64) temp_r0_4 < 6.0f)) {
                temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
                Hu3DModelAttrSet(obj->model[0], 1U);
            case 7:                                 /* switch 1 */
                temp_r29_2 = obj->model[2];
                if (Hu3DMotionEndCheck(temp_r29_2) != 0) {
                    Hu3DModelAttrSet(temp_r29_2, 1U);
                    temp_r31->unk4 = (u32) (temp_r31->unk4 + 1);
                    temp_r24->unk0 = 0;
                case 8:                             /* switch 1 */
                    if (!(Center.x > -1000.0f)) {
                        temp_r31->unk4 = 2U;
                        Hu3DModelAttrReset(obj->model[0], 1U);
                    }
                }
            }
        }
        break;
    }
    VECAdd(&temp_r31->unk1C, &temp_r31->unk28, &temp_r31->unk1C);
    if ((s32) temp_r31->unk14 != -1) {
        if (HuAudFXStatusGet(temp_r31->unk14) == 2) {
            fn_1_1AF4(temp_r31->unk14, &temp_r31->unk1C);
        } else {
            temp_r31->unk14 = -1;
        }
    }
    if ((s32) temp_r31->unk18 != -1) {
        if (HuAudFXStatusGet(temp_r31->unk18) == 2) {
            fn_1_1AF4(temp_r31->unk18, &temp_r31->unk1C);
        } else {
            temp_r31->unk18 = -1;
        }
    }
    temp_r18 = obj->data;
    temp_r19 = obj->model[0];
    Hu3DModelPosSetV(temp_r19, &temp_r18->unk1C);
    Hu3DModelRotSetV(temp_r19, &temp_r18->unk34);
}

s32 fn_1_50E4(void) {
    return ((M514Flag *)lbl_1_bss_208->data)->unk0;
}

void fn_1_1D9C(HUPROCESS *arg0) {
    omObjData *temp_r3;
    s32 var_r30;

    lbl_1_bss_80 = omAddObjEx(arg0, 0x28, 0U, 0U, 0, fn_1_1EC4);
    omMakeGroupEx(arg0, 0U, 4U);
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r3 = omAddObjEx(arg0, 0x1E, 1U, 8U, 0, fn_1_20E0);
        lbl_1_bss_70[var_r30] = temp_r3;
        temp_r3->work[0] = (u32) var_r30;
        temp_r3->work[1] = (u32) GWPlayerCfg[var_r30].group;
        temp_r3->work[2] = (u32) var_r30;
        fn_1_1838(var_r30, (s16) temp_r3->work[1], GWPlayerCfg[var_r30].character);
        var_r30 += 1;
        goto loop_2;
    }
}

void fn_1_1EA0(void) {
    CharModelKill(-1);
}

void fn_1_1EC4(omObjData *arg0) {
    arg0->func = fn_1_1ED4;
}

void fn_1_1ED4(omObjData *obj) {
    s32 temp_r22;
    s32 temp_r3;
    s32 var_r25;
    s32 var_r28;
    s32 var_r29;
    M514Player *temp_r26;
    M514Player *temp_r27;

    var_r29 = 0;
loop_17:
    if (var_r29 < 3) {
        temp_r27 = lbl_1_bss_70[var_r29]->data;
        if ((s32) temp_r27->unk68 != 0) {
            temp_r22 = fn_1_95BC(var_r29);
            var_r28 = var_r29 + 1;
loop_15:
            if (var_r28 < 4) {
                temp_r26 = lbl_1_bss_70[var_r28]->data;
                if (((s32) temp_r26->unk68 != 0) && !(fabs(temp_r27->unk40.z - temp_r26->unk40.z) > 200.0f) && !(fabs(temp_r27->unk40.x - temp_r26->unk40.x) > 160.0f)) {
                    temp_r3 = fn_1_95BC(var_r28);
                    var_r25 = 0;
                    if (temp_r22 < temp_r3) {
                        var_r25 = 1;
                    }
                    if ((temp_r22 == temp_r3) && (var_r29 > var_r28)) {
                        var_r25 = 1;
                    }
                    if (var_r25 == 0) {
                        temp_r27->unk40.x = (f32) ((f64) temp_r27->unk40.x + 5.0);
                        temp_r26->unk40.x = (f32) ((f64) temp_r26->unk40.x - 5.0);
                    } else {
                        temp_r27->unk40.x = (f32) ((f64) temp_r27->unk40.x - 5.0);
                        temp_r26->unk40.x = (f32) ((f64) temp_r26->unk40.x + 5.0);
                    }
                }
                var_r28 += 1;
                goto loop_15;
            }
        }
        var_r29 += 1;
        goto loop_17;
    }
}

void fn_1_20E0(omObjData *arg0) {
    Vec *temp_r4;
    s16 temp_r27;
    s16 temp_r3;
    s32 var_r29;
    u32 temp_r25;
    u32 temp_r28;
    M514Player *temp_r31;

    arg0->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Player), MEMORY_DEFAULT_NUM);
    temp_r31 = arg0->data;
    memset((ANIMDATA **) temp_r31, 0, 0x98);
    arg0->stat |= 0x100;
    temp_r28 = arg0->work[0];
    temp_r31->unk0 = temp_r28;
    temp_r31->unk4 = (u32) arg0->work[1];
    temp_r25 = arg0->work[2];
    temp_r31->unk8 = temp_r25;
    temp_r27 = GWPlayerCfg[temp_r28].character;
    temp_r31->unkC = (s32) temp_r27;
    temp_r31->unk24 = (s32) (GWPlayerCfg[temp_r28].diff & 3);
    temp_r31->unk20 = (s32) GWPlayerCfg[temp_r28].iscom;
    temp_r31->unk28 = 0;
    temp_r3 = CharModelCreate(temp_r27, 2);
    *arg0->model = temp_r3;
    Hu3DModelLayerSet(temp_r3, 6);
    Hu3DModelShadowSet(temp_r3);
    CharEffectLayerSet(6);
    var_r29 = 0;
loop_2:
    if (var_r29 < 8) {
        arg0->motion[var_r29] = Mp5CharMotionCreateData(temp_r27, lbl_1_data_B8[var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionDataClose(temp_r27);
    temp_r31->unk3C = -1;
    fn_1_3EC0(arg0, 0U);
    temp_r4 = &lbl_1_data_138[temp_r25];
    temp_r31->unk40.x = (f32) temp_r4->x;
    temp_r31->unk40.y = (f32) temp_r4->y;
    temp_r31->unk40.z = (f32) temp_r4->z;
    temp_r31->unk4C.z = 0.0f;
    temp_r31->unk4C.y = 0.0f;
    temp_r31->unk4C.x = 0.0f;
    temp_r31->unk58 = (f32) lbl_1_data_1F0[temp_r25];
    temp_r31->unk90 = -1;
    temp_r31->unk94 = -1;
    temp_r31->unk30 = 0;
    temp_r31->unk7C = 0;
    arg0->func = fn_1_2338;
}


void fn_1_2338(omObjData *obj) {
    Vec sp8;
    s16 temp_r27;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    u32 temp_r0;
    u32 temp_r3;
    M514Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0.0f;
    temp_r31->unk1C = 0.0f;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {
    case 0:
        if (fn_1_387C(obj, &lbl_1_data_138[temp_r31->unk0 + 4], 1, 0.0f) != 0) {
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
            temp_r31->unk6C = 1;
        case 1:
            if (MgSeqModeGet() == 5) {
                temp_r3 = fn_1_1814();
                if (temp_r3 != (u32) temp_r31->unk0) {
                    fn_1_387C(obj, &lbl_1_data_138[(temp_r31->unk0 - temp_r3) - 1 + 4], 1, 0.0f);
                } else {
                    temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
                    temp_r31->unk34 = 0;
                    fn_1_37CC(obj, 9);
                case 2:
                    Center.x = (f32) ((f64) Center.x + (0.1 * (f64) ((f32) ((M514Player *)obj->data)->unk40.x - Center.x)));
                    if (fn_1_387C(obj, &lbl_1_data_138[8], 1, 90.0f) != 0) {
                        temp_r0_2 = temp_r31->unk34 + 1;
                        temp_r31->unk34 = temp_r0_2;
                        if (!((f32) (f64) temp_r0_2 < 30.0f)) {
                            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
                            temp_r31->unk34 = 0;
                            temp_r31->unk6C = 0;
                            temp_r31->unk68 = 1;
                        case 3:
                            Center.x = (f32) ((f64) Center.x + (0.1 * (f64) ((f32) ((M514Player *)obj->data)->unk40.x - Center.x)));
                            if ((s32) temp_r31->unk8C != 0) {
                                temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
                                temp_r31->unk34 = 0;
                            } else if ((s32) temp_r31->unk20 != 0) {
                                fn_1_3D6C(obj);
                            } else {
                                temp_r27 = GWPlayerCfg[temp_r31->unk0].pad_idx;
                                temp_r31->unk14 = (s32) HuPadBtn[temp_r27];
                                temp_r31->unk10 = (s32) HuPadBtnDown[temp_r27];
                            }
                        }
                    }
                }
            }
        }
        break;
    case 4:
        Center.x = (f32) ((f64) Center.x + (0.1 * (f64) ((f32) ((M514Player *)obj->data)->unk40.x - Center.x)));
        if (fn_1_50E4() == 0) {
            sp8.x = temp_r31->unk40.x;
            sp8.y = 0.0f;
            sp8.z = -220.0f;
            temp_r31->unk4C.y = 0.0f;
            temp_r31->unk40.y = 0.0f;
            if (fn_1_387C(obj, &sp8, 0, 0.0f) != 0) {
                temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
                temp_r31->unk34 = 0;
            }
        }
        break;
    case 5:
        temp_r0_3 = temp_r31->unk34 + 1;
        temp_r31->unk34 = temp_r0_3;
        if (!((f32) (f64) temp_r0_3 < 30.0f)) {
            fn_1_1824();
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
            temp_r31->unk34 = 0;
            temp_r31->unk6C = 1;
            fn_1_9334();
        }
        break;
    case 6:
        temp_r0_4 = temp_r31->unk34 + 1;
        temp_r31->unk34 = temp_r0_4;
        if (!((f32) (f64) temp_r0_4 < 18.0f)) {
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
        case 7:
            if (MgSeqModeGet() == 7) {
                temp_r31->unk30 = 0U;
                obj->func = fn_1_284C;
            }
        }
        break;
    }
    fn_1_2E8C(obj);
    fn_1_2E88();
    VECAdd(&temp_r31->unk40, &temp_r31->unk4C, &temp_r31->unk40);
    fn_1_2A88(obj);
    fn_1_3CF8(obj);
}

void fn_1_284C(omObjData *obj) {
    Vec sp8;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u32 temp_r0;
    M514Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0.0f;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk4C.z = 0.0f;
    temp_r31->unk4C.y = 0.0f;
    temp_r31->unk4C.x = 0.0f;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {
    case 0:
        temp_r31->unk6C = 0;
        temp_r31->unk70 = 0;
        temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
        /* fallthrough */
    case 1:
        if (((fn_1_16EC(temp_r31->unk0) < 0) || (sp8.x = temp_r31->unk40.x, sp8.y = temp_r31->unk40.y, sp8.z = -100.0f, ((fn_1_387C(obj, &sp8, 0, 0.0f) == 0) == 0))) && (MgSeqModeGet() == 8)) {
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
            temp_r31->unk34 = 0;
        }
        break;
    case 2:
        temp_r31->unk58 = fn_1_1BCC(temp_r31->unk58, 0.0f, 0.1f);
        temp_r0_2 = temp_r31->unk34 + 1;
        temp_r31->unk34 = temp_r0_2;
        if (temp_r0_2 >= 0xA) {
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
            temp_r31->unk34 = 0;
        }
        break;
    case 3:
        temp_r31->unk58 = fn_1_1BCC(temp_r31->unk58, 0.0f, 0.1f);
        temp_r0_3 = temp_r31->unk34 + 1;
        temp_r31->unk34 = temp_r0_3;
        if (temp_r0_3 >= 0x14) {
            if (fn_1_16EC(temp_r31->unk0) >= 0) {
                fn_1_3EC0(obj, 3U);
            } else {
                fn_1_3EC0(obj, 4U);
                fn_1_1890();
            }
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
        }
        break;
    case 5:
        if (fn_1_3FB8(obj) != 0) {
            temp_r31->unk30 = (u32) (temp_r31->unk30 + 1);
        }
        break;
    }
    VECAdd(&temp_r31->unk40, &temp_r31->unk4C, &temp_r31->unk40);
    fn_1_2A88(obj);
    fn_1_3CF8(obj);
}

void fn_1_2A88(omObjData *arg0) {
    s32 temp_r0;
    s32 temp_r4;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk38 = (s32) (temp_r31->unk38 + 1);
    fn_1_7C10(temp_r31->unk90, &temp_r31->unk40);
    CharModelVoicePanSet((s16) temp_r31->unkC, fn_1_1960(&temp_r31->unk40));
    CharModelVoiceVolSet((s16) temp_r31->unkC, fn_1_19F4());
    if (((s32) (temp_r31->unk38 % 6) == 0) && (temp_r31->unk40.y == 0.0f) && (VECMag(&temp_r31->unk4C) > 5.000000260770321f)) {
        temp_r0 = temp_r31->unk78 + 1;
        temp_r31->unk78 = temp_r0;
        temp_r4 = temp_r0 & 1;
        temp_r31->unk78 = temp_r4;
        fn_1_2D10(arg0, temp_r4);
    }
    if (((s32) temp_r31->unk3C == 5) && (fn_1_3FB8(arg0) != 0)) {
        fn_1_3EC0(arg0, 6U);
    }
    if (((s32) temp_r31->unk70 != 0) && (fn_1_3FB8(arg0) != 0)) {
        temp_r31->unk70 = 0;
    }
}


void fn_1_2D10(omObjData *arg0, s32 arg1) {
    Vec spC;
    s32 sp8;
    f32 temp_f31;
    f64 var_f30;
    M514Player *temp_r31;

    sp8 = arg1;
    if ((u32) ((M514Player *)arg0->data)->unkC != 8U) {
        temp_r31 = arg0->data;
        if (sp8 == 0) {
            var_f30 = 90.0;
        } else {
            var_f30 = -90.0;
        }
        temp_f31 = (f32) ((f64) temp_r31->unk58 + var_f30);
        spC.x = (f32) ((f64) temp_r31->unk40.x + (100.0 * (0.15 * sin((3.141592653589793 * (f64) temp_f31) / 180.0))));
        spC.y = temp_r31->unk40.y;
        spC.z = (f32) ((f64) temp_r31->unk40.z + (100.0 * (0.15 * cos((3.141592653589793 * (f64) temp_f31) / 180.0))));
        spC.y = 0.0f;
        fn_1_80C0(&spC, 10.0f);
    }
}

void fn_1_2E88(void) {

}

void fn_1_2E8C(omObjData *arg0) {
    Vec sp8;
    Vec sp14;
    M514Jump *temp_r29;
    M514Jump *temp_r29_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    f64 var_f27;
    f64 var_f28;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r3;
    s32 var_r24;
    u32 temp_r0;
    M514Player *temp_r27;
    M514Player *temp_r28;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    if ((s32) temp_r31->unk74 == 0) {
        temp_r0 = temp_r31->unk7C;
        switch (temp_r0) {
        case 0:
            if ((s32) temp_r31->unk6C == 0) {
                temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                temp_r31->unk80 = 0;
                temp_r31->unk84 = 0;
            case 1:
                temp_r0_2 = temp_r31->unk80 + 1;
                temp_r31->unk80 = temp_r0_2;
                if (!((f32) (f64) temp_r0_2 < 18.0f)) {
                    temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                    temp_r31->unk80 = 0;
                    temp_r31->unk5C = 0.2f;
                case 2:
                    temp_r31->unk4C.x = (f32) ((f64) temp_r31->unk4C.x + (0.1 * (f64) (9.166667f - temp_r31->unk4C.x)));
                    if (temp_r31->unk40.x > (f32) ((f64) lbl_1_data_138[9].x - 100.0)) {
                        fn_1_8228(0);
                        temp_r31->unk64 = 1;
                    }
                    if (temp_r31->unk40.x < lbl_1_data_138[9].x) {
                        fn_1_3EC0(arg0, 2U);
                        temp_r31->unk5C = (f32) ((f64) temp_r31->unk5C + (0.1 * (1.0 - (f64) temp_r31->unk5C)));
                        Hu3DMotionSpeedSet(*arg0->model, temp_r31->unk5C * lbl_1_data_1B0[Mp5CharNo(temp_r31->unkC)]);
                    } else {
                        temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                        temp_r31->unk80 = 0;
                    case 3:
                        temp_r29 = &lbl_1_data_23C[temp_r31->unk84];
                        temp_r31->unk4C.x = (f32) ((f64) temp_r31->unk4C.x * 0.5);
                        temp_r3 = temp_r31->unk80 + 1;
                        temp_r31->unk80 = temp_r3;
                        if (temp_r3 >= (s32) temp_r29->unk0) {
                            temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                            temp_r31->unk88 = 1;
                            temp_r31->unk4C.x = (f32) temp_r29->unk4;
                            temp_r31->unk4C.y = (f32) temp_r29->unk8;
                            temp_r31->unk60 = -0.6666667f;
                            fn_1_3EC0(arg0, 5U);
                            temp_r31->unk90 = fn_1_79F8(&temp_r31->unk40, 20.0f);
                            temp_r31->unk94 = HuAudFXPlay(lbl_1_data_290[temp_r31->unk84]);
                            fn_1_37CC(arg0, 0);
                        }
                    }
                }
            }
            break;
        case 4:
            temp_r29_2 = &lbl_1_data_23C[temp_r31->unk84];
            if (temp_r31->unk4C.y >= 0.0f) {
                temp_r31->unk60 = (f32) ((f64) temp_r31->unk60 - 0.00500000026077032);
            } else {
                temp_r31->unk60 = (f32) ((f64) temp_r31->unk60 - 0.01666666753590107);
            }
            temp_r31->unk4C.x = (f32) ((f64) temp_r31->unk4C.x * 0.98);
            temp_r31->unk4C.y = (f32) (temp_r31->unk4C.y + temp_r31->unk60);
            if ((s32) (temp_r31->unk84 & 1) == 0) {
                var_r24 = 0x100;
            } else {
                var_r24 = 0x200;
            }
            if ((u32) (temp_r31->unk10 & var_r24) != 0) {
                temp_r31->unk4C.x = (f32) (temp_r31->unk4C.x + temp_r29_2->unkC);
                if (temp_r31->unk4C.y > 0.0f) {
                    temp_r31->unk4C.y = (f32) (temp_r31->unk4C.y + temp_r29_2->unk10);
                } else {
                    temp_r31->unk4C.y = (f32) (temp_r31->unk4C.y + temp_r29_2->unk14);
                }
                fn_1_1870(temp_r31->unk0);
            }
            if (!(temp_r31->unk4C.y > 0.0f) && !(temp_r31->unk40.y > 0.0f)) {
                temp_r31->unk40.y = 0.0f;
                temp_r31->unk4C.y = 0.0f;
                temp_r31->unk4C.x = 0.0f;
                temp_r31->unk88 = 0;
                CharModelLandDustCreate((s16) temp_r31->unkC, &temp_r31->unk40);
                fn_1_3EC0(arg0, 7U);
                if ((u32) ((M514Player *)arg0->data)->unkC != 8) {
                    temp_r28 = arg0->data;
                    if ((s32) (temp_r31->unk84 & 1) == 0) {
                        var_f28 = 90.0;
                    } else {
                        var_f28 = -90.0;
                    }
                    temp_f30 = (f32) ((f64) temp_r28->unk58 + var_f28);
                    sp14.x = (f32) ((f64) temp_r28->unk40.x + (100.0 * (0.15 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))));
                    sp14.y = temp_r28->unk40.y;
                    sp14.z = (f32) ((f64) temp_r28->unk40.z + (100.0 * (0.15 * cos((3.141592653589793 * (f64) temp_f30) / 180.0))));
                    sp14.y = 0.0f;
                    fn_1_80C0(&sp14, 10.0f);
                }
                fn_1_7B8C(temp_r31->unk90);
                temp_r31->unk90 = -1;
                HuAudFXFadeOut(temp_r31->unk94, 0x7D);
                temp_r31->unk94 = -1;
                HuAudFXPlay(0x21);
                temp_r0_3 = temp_r31->unk84 + 1;
                temp_r31->unk84 = temp_r0_3;
                if (temp_r0_3 < 3) {
                    fn_1_8228(temp_r31->unk84 & 1);
                    temp_r31->unk7C = (u32) (temp_r31->unk7C - 1);
                    temp_r31->unk80 = 0;
                } else {
                    fn_1_37CC(arg0, temp_r31->unk84);
                    if ((u32) ((M514Player *)arg0->data)->unkC != 8) {
                        temp_r27 = arg0->data;
                        if ((s32) (temp_r31->unk84 & 1) == 0) {
                            var_f27 = 90.0;
                        } else {
                            var_f27 = -90.0;
                        }
                        temp_f29 = (f32) ((f64) temp_r27->unk58 + var_f27);
                        sp8.x = (f32) ((f64) temp_r27->unk40.x + (100.0 * (0.15 * sin((3.141592653589793 * (f64) temp_f29) / 180.0))));
                        sp8.y = temp_r27->unk40.y;
                        sp8.z = (f32) ((f64) temp_r27->unk40.z + (100.0 * (0.15 * cos((3.141592653589793 * (f64) temp_f29) / 180.0))));
                        sp8.y = 0.0f;
                        fn_1_80C0(&sp8, 10.0f);
                    }
                    fn_1_8228(-1);
                    temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                    temp_r31->unk80 = 0;
                case 5:
                    temp_r31->unk4C.x = (f32) ((f64) temp_r31->unk4C.x * 0.5);
                    temp_r0_4 = temp_r31->unk80 + 1;
                    temp_r31->unk80 = temp_r0_4;
                    if (temp_r0_4 >= 0xA) {
                        temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                        temp_r31->unk80 = 0;
                        temp_r31->unk64 = 0;
                        temp_r31->unk4C.x = 0.0f;
                        fn_1_3EC0(arg0, 0U);
                    }
                }
            }
            break;
        case 6:
            temp_r0_5 = temp_r31->unk80 + 1;
            temp_r31->unk80 = temp_r0_5;
            if (!((f32) (f64) temp_r0_5 < 48.0f)) {
                temp_r31->unk7C = (u32) (temp_r31->unk7C + 1);
                temp_r31->unk8C = 1;
            }
            break;
        }
        if (temp_r31->unk40.y > 400.0f) {
            temp_r31->unk60 = (f32) ((f64) temp_r31->unk60 - 0.03333333507180214);
        }
        if (temp_r31->unk40.y > 500.0f) {
            temp_r31->unk60 = (f32) ((f64) temp_r31->unk60 - 0.03333333507180214);
        }
        if ((s32) temp_r31->unk64 != 0) {
            var_f31 = (f32) ((f64) temp_r31->unk40.x - -2500.0);
            if (var_f31 < 0.0f) {
                var_f31 = 0.0f;
            }
            fn_1_9570(temp_r31->unk4, var_f31);
            if (((s32) temp_r31->unk84 < 3) && (var_f31 > lbl_1_data_23C[temp_r31->unk84].unk18)) {
                temp_r31->unk60 = (f32) ((f64) temp_r31->unk60 - 0.3333333507180214);
            }
        }
    }
}

void fn_1_37CC(omObjData *arg0, s32 arg1) {
    s32 sp8;
    s32 temp_r31;

    sp8 = arg1;
    temp_r31 = ((M514Player *) arg0->data)->unk0;
    switch (sp8) {                                  /* irregular */
    default:
        omVibrate((s16) temp_r31, 0xA, 6, 6);
        return;
    case 3:
        omVibrate((s16) temp_r31, 0xC, 0xC, 0);
        return;
    case 9:
        omVibrate((s16) temp_r31, 0x14, 0xC, 0);
        return;
    }
}

s32 fn_1_387C(omObjData *arg0, Vec *arg1, s32 arg2, f32 farg0) {
    f32 sp8;
    f32 temp_f30;
    f32 var_f26;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    f64 var_f27;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk74 = 1;
    if (arg2 != 0) {
        var_f31 = arg1->x - temp_r31->unk40.x;
    } else {
        var_f31 = 0.0f;
    }
    temp_f30 = arg1->z - temp_r31->unk40.z;
    var_f26 = sqrtf((var_f31 * var_f31) + (temp_f30 * temp_f30));
    if (var_f26 < 10.0f) {
        fn_1_3EC0(arg0, 0U);
        if (arg2 != 0) {
            temp_r31->unk40.x = (f32) ((f64) temp_r31->unk40.x + (0.1 * (f64) var_f31));
        }
        temp_r31->unk40.z = (f32) ((f64) temp_r31->unk40.z + (0.1 * (f64) temp_f30));
        temp_r31->unk4C.z = 0.0f;
        temp_r31->unk4C.y = 0.0f;
        temp_r31->unk4C.x = 0.0f;
        temp_r31->unk58 = fn_1_1BCC(temp_r31->unk58, farg0, 0.1f);
        if (var_f26 > 1.0f) {
            return 0;
        }
        if (fn_1_1CE8(temp_r31->unk58, farg0) > 2.0f) {
            return 0;
        }
        if (arg2 != 0) {
            temp_r31->unk40.x = (f32) arg1->x;
        }
        temp_r31->unk40.y = (f32) arg1->y;
        temp_r31->unk40.z = (f32) arg1->z;
        temp_r31->unk58 = farg0;
        temp_r31->unk74 = 0;
        return 1;
    }
    if (var_f26 < 50.0f) {
        fn_1_3EC0(arg0, 1U);
        var_f27 = 0.5f;
    } else {
        fn_1_3EC0(arg0, 2U);
        var_f27 = 1.0f;
    }
    temp_r31->unk58 = fn_1_1BCC(temp_r31->unk58, (f32) (180.0 * (atan2((f64) var_f31, (f64) temp_f30) / 3.141592653589793)), 0.2f);
    temp_r31->unk4C.x = (f32) (0.01666666753590107 * (550.0 * (var_f27 * sin((3.141592653589793 * (f64) temp_r31->unk58) / 180.0))));
    temp_r31->unk4C.z = (f32) (0.01666666753590107 * (550.0 * (var_f27 * cos((3.141592653589793 * (f64) temp_r31->unk58) / 180.0))));
    if (arg2 == 0) {
        temp_r31->unk4C.x = 0.0f;
    }
    return 0;
}

void fn_1_3CF8(omObjData *arg0) {
    s16 temp_r29;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r29 = *arg0->model;
    Hu3DModelPosSetV(temp_r29, &temp_r31->unk40);
    Hu3DModelRotSet(temp_r29, 0.0f, temp_r31->unk58, 0.0f);
}

void fn_1_3D6C(omObjData *arg0) {
    M514Com *temp_r30;
    s32 temp_r0;
    s32 temp_r0_2;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r30 = &lbl_1_data_2BC[temp_r31->unk24];
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
        temp_r31->unk2C = (s32) ((f64) temp_r30->unk0 + ((f64) temp_r30->unk4 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
        /* fallthrough */
    case 1:
        temp_r0_2 = temp_r31->unk2C - 1;
        temp_r31->unk2C = temp_r0_2;
        if (temp_r0_2 <= 0) {
            temp_r31->unk10 = 0x300;
            temp_r31->unk14 = 0x300;
            temp_r31->unk2C = (s32) ((f64) temp_r30->unk8 + ((f64) temp_r30->unkC * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
        }
        return;
    }
}

void fn_1_3EC0(omObjData *arg0, u32 arg1) {
    f32 var_f31;
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    if (((u32) temp_r31->unk3C != arg1) && (arg1 < 8U)) {
        if ((s32) temp_r31->unk3C < 0) {
            var_f31 = 0.0f;
        } else {
            var_f31 = 60.0f * lbl_1_data_D8[arg1].unk4;
        }
        temp_r31->unk3C = arg1;
        CharMotionShiftSet((s16) temp_r31->unkC, arg0->motion[lbl_1_data_D8[arg1].unk0], 0.0f, var_f31, lbl_1_data_D8[arg1].unk8);
    }
}

s32 fn_1_3FB8(omObjData *arg0) {
    M514Player *temp_r31;

    temp_r31 = arg0->data;
    if ((CharMotionEndCheck((s16) temp_r31->unkC) != 0) && (CharMotionShiftIDGet((s16) temp_r31->unkC) < 0)) {
        return 1;
    }
    return 0;
}



s32 fn_1_41C4(u32 arg0) {
    s32 var_r30;
    M514Player *temp_r31;

    var_r30 = 0;
loop_5:
    if (var_r30 >= 4) {
        return 0;
    }
    temp_r31 = lbl_1_bss_70[var_r30]->data;
    if (((u32) temp_r31->unk4 == arg0) && ((s32) temp_r31->unk20 == 0)) {
        return 1;
    }
    var_r30 += 1;
    goto loop_5;
}

f32 fn_1_4238(s32 arg0) {
    return ((M514Player *)lbl_1_bss_70[arg0]->data)->unk40.x;
}

void fn_1_8268(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    M514Score *temp_r3_2;
    omObjData *temp_r3;
    u32 temp_r3_3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x46, 0U, 0U, -1, fn_1_8304);
    lbl_1_bss_220 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Score), MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 0xB8);
    temp_r3_3 = GWMgRecordGet(5);
    temp_r3_2->unkA8 = temp_r3_3;
    temp_r3_2->unkA4 = temp_r3_3;
}

void fn_1_8300(void) {

}

void fn_1_8304(omObjData *arg0) {
    fn_1_83A8(arg0);
    if (0 == 0) {
        fn_1_8D58(arg0);
    }
    arg0->func = fn_1_835C;
}

void fn_1_835C(omObjData *obj) {
    fn_1_879C(obj);
    if (0 == 0) {
        fn_1_900C(obj);
    }
}

void fn_1_83A8(omObjData *arg0) {
    ANIMDATA *temp_r23;
    ANIMDATA *temp_r24;
    MGSCORE *temp_r3_2;
    MGSCORE *temp_r3_3;
    s16 temp_r3;
    s16 temp_r3_4;
    s16 var_r27;
    s32 var_r31;
    M514Score *temp_r30;

    temp_r30 = arg0->data;
    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        temp_r30->unk0[var_r31].unk10 = var_r31;
        temp_r30->unk0[var_r31].unk20 = lbl_1_data_53C[var_r31].unk0;
        temp_r30->unkB8[var_r31] = lbl_1_data_53C[var_r31].unk4;
        temp_r30->unkC8[var_r31][0] = lbl_1_data_53C[var_r31].unk0;
        temp_r30->unkC8[var_r31][1] = lbl_1_data_53C[var_r31].unk4;
        temp_r3 = MgScoreWinCreate(0xB0, 0x28);
        temp_r30->unk0[var_r31].unk14 = temp_r3;
        MgScoreWinPosSet(temp_r3, lbl_1_data_53C[var_r31].unk0, lbl_1_data_53C[var_r31].unk4);
        MgScoreWinDispSet(temp_r3, 0);
        temp_r3_2 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 0);
        temp_r30->unk0[var_r31].unk18 = temp_r3_2;
        MgScoreMaxDigitSet(temp_r3_2, 3);
        MgScoreDispOff(temp_r3_2);
        MgScorePosSet(temp_r3_2, -48.0f + lbl_1_data_53C[var_r31].unk0, lbl_1_data_53C[var_r31].unk4);
        MgScoreColorSet(temp_r3_2, 0xFFU, 0xD8U, 0x15U);
        temp_r3_3 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 1);
        temp_r30->unk0[var_r31].unk1C = temp_r3_3;
        MgScoreMaxDigitSet(temp_r3_3, 2);
        MgScoreDispOff(temp_r3_3);
        MgScorePosSet(temp_r3_3, 10.0f + lbl_1_data_53C[var_r31].unk0, lbl_1_data_53C[var_r31].unk4);
        MgScoreColorSet(temp_r3_3, 0xFFU, 0xD8U, 0x15U);
        temp_r24 = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_500[Mp5CharNo(GWPlayerCfg[var_r31].character)], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r23 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 34), MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r3_4 = HuSprGrpCreate(3);
        temp_r30->unk0[var_r31].unk16 = temp_r3_4;
        HuSprGrpPosSet(temp_r3_4, lbl_1_data_53C[var_r31].unk0, lbl_1_data_53C[var_r31].unk4);
        HuSprGrpMemberSet(temp_r3_4, 0, HuSprCreate(temp_r24, 0x32, 0));
        HuSprPosSet(temp_r3_4, 0, -70.0f, 0.0f);
        HuSprGrpMemberSet(temp_r3_4, 1, HuSprCreate(temp_r3_3->digitAnim, 0x32, 0xC));
        HuSprPosSet(temp_r3_4, 1, 0.0f, 0.0f);
        HuSprColorSet(temp_r3_4, 1, 0xFFU, 0xD8U, 0x15U);
        HuSprGrpMemberSet(temp_r3_4, 2, HuSprCreate(temp_r23, 0x32, 2));
        HuSprPosSet(temp_r3_4, 2, 60.0f, 0.0f);
        HuSprColorSet(temp_r3_4, 2, 0xFFU, 0xD8U, 0x15U);
        var_r27 = 0;
loop_3:
        if (var_r27 < 3) {
            HuSprAttrSet(temp_r3_4, var_r27, 1);
            HuSprAttrSet(temp_r3_4, var_r27, 4);
            var_r27 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    fn_1_8C7C(arg0);
}

void fn_1_879C(omObjData *arg0) {
    f32 temp_f1;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r27;
    s16 temp_r27_2;
    s16 var_r29;
    s16 var_r29_2;
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    u32 var_r28;
    M514Score *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = temp_r31->unk0[0].unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (MgSeqModeGet() == 5) {
            temp_r31->unk0[0].unk0 = (s32) (temp_r31->unk0[0].unk0 + 1);
            temp_r31->unk0[0].unk8 = 0.0f;
            var_r30 = 0;
loop_11:
            if (var_r30 < 4) {
                MgScoreWinDispSet(temp_r31->unk0[var_r30].unk14, 1);
                MgScoreDispOn(temp_r31->unk0[var_r30].unk18);
                MgScoreDispOn(temp_r31->unk0[var_r30].unk1C);
                temp_r27 = temp_r31->unk0[var_r30].unk16;
                var_r29 = 0;
loop_9:
                if (var_r29 < 3) {
                    HuSprAttrReset(temp_r27, var_r29, 4);
                    var_r29 += 1;
                    goto loop_9;
                }
                var_r30 += 1;
                goto loop_11;
            }
        case 1:
            temp_f1 = (f32) ((f64) temp_r31->unk0[0].unk8 + 0.1);
            temp_r31->unk0[0].unk8 = temp_f1;
            if (temp_f1 >= 1.0f) {
                temp_r31->unk0[0].unk8 = 1.0f;
                temp_r31->unk0[0].unk0 = (s32) (temp_r31->unk0[0].unk0 + 1);
            }
            var_r30_2 = 0;
loop_19:
            if (var_r30_2 < 4) {
                MgScoreWinTPLvlSet(temp_r31->unk0[var_r30_2].unk14, (f32) (0.7 * (f64) temp_r31->unk0[0].unk8));
                MgScoreTPLvlSet(temp_r31->unk0[var_r30_2].unk18, temp_r31->unk0[0].unk8);
                MgScoreTPLvlSet(temp_r31->unk0[var_r30_2].unk1C, temp_r31->unk0[0].unk8);
                temp_r27_2 = temp_r31->unk0[var_r30_2].unk16;
                var_r29_2 = 0;
loop_17:
                if (var_r29_2 < 3) {
                    HuSprTPLvlSet(temp_r27_2, var_r29_2, temp_r31->unk0[0].unk8);
                    var_r29_2 += 1;
                    goto loop_17;
                }
                var_r30_2 += 1;
                goto loop_19;
            }
        }
        break;
    }
    var_r30_3 = 0;
loop_24:
    if (var_r30_3 < 4) {
        var_r28 = temp_r31->unk0[var_r30_3].unkC / 100;
        if ((s32) var_r28 > 0x3E7) {
            var_r28 = 0x3E7;
        }
        MgScoreValueSet(temp_r31->unk0[var_r30_3].unk18, (s32) var_r28);
        MgScoreValueSet(temp_r31->unk0[var_r30_3].unk1C, temp_r31->unk0[var_r30_3].unkC % 100);
        temp_r31->unk0[var_r30_3].unk20 = (f32) ((f64) temp_r31->unk0[var_r30_3].unk20 + (0.2 * (f64) (temp_r31->unkC8[var_r30_3][0] - temp_r31->unk0[var_r30_3].unk20)));
        temp_r31->unkB8[var_r30_3] = (f32) ((f64) temp_r31->unkB8[var_r30_3] + (0.2 * (f64) (temp_r31->unkC8[var_r30_3][1] - temp_r31->unkB8[var_r30_3])));
        temp_f31 = temp_r31->unk0[var_r30_3].unk20;
        temp_f30 = temp_r31->unkB8[var_r30_3];
        MgScoreWinPosSet(temp_r31->unk0[var_r30_3].unk14, temp_f31, temp_f30);
        MgScorePosSet(temp_r31->unk0[var_r30_3].unk18, -48.0f + temp_f31, temp_f30);
        MgScorePosSet(temp_r31->unk0[var_r30_3].unk1C, 10.0f + temp_f31, temp_f30);
        HuSprGrpPosSet(temp_r31->unk0[var_r30_3].unk16, temp_f31, temp_f30);
        var_r30_3 += 1;
        goto loop_24;
    }
}


void fn_1_8C7C(omObjData *arg0) {
    s16 temp_r0;
    s16 temp_r28;
    s32 var_r30;
    M514Score *temp_r31;

    temp_r31 = arg0->data;
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r0 = (temp_r31->unk0[var_r30].unk10 * 2) + 0x32;
        fn_1_9300(temp_r31->unk0[var_r30].unk14, (s16) (temp_r0 + 1));
        MgScorePriSet(temp_r31->unk0[var_r30].unk18, temp_r0);
        MgScorePriSet(temp_r31->unk0[var_r30].unk1C, temp_r0);
        temp_r28 = temp_r31->unk0[var_r30].unk16;
        HuSprPriSet(temp_r28, 0, temp_r0);
        HuSprPriSet(temp_r28, 1, temp_r0);
        HuSprPriSet(temp_r28, 2, temp_r0);
        var_r30 += 1;
        goto loop_2;
    }
}

void fn_1_8D58(omObjData *arg0) {
    MGSCORE *temp_r3_2;
    MGSCORE *temp_r3_3;
    s16 temp_r3;
    s16 temp_r3_4;
    M514Score *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk9C = 0;
    temp_r3 = MgScoreWinCreate(0xB0, 0x28);
    temp_r31->unkAC = temp_r3;
    MgScoreWinPosSet(temp_r3, lbl_1_data_4F8.unk0, lbl_1_data_4F8.unk4);
    temp_r3_2 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 0);
    temp_r31->unkB0 = temp_r3_2;
    MgScoreMaxDigitSet(temp_r3_2, 3);
    MgScorePosSet(temp_r3_2, -48.0f + lbl_1_data_4F8.unk0, lbl_1_data_4F8.unk4);
    MgScoreColorSet(temp_r3_2, 0x42U, 0xFFU, 0x7AU);
    temp_r3_3 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 1);
    temp_r31->unkB4 = temp_r3_3;
    MgScoreMaxDigitSet(temp_r3_3, 2);
    MgScorePosSet(temp_r3_3, 10.0f + lbl_1_data_4F8.unk0, lbl_1_data_4F8.unk4);
    MgScoreColorSet(temp_r3_3, 0x42U, 0xFFU, 0x7AU);
    temp_r3_4 = HuSprGrpCreate(3);
    temp_r31->unkAE = temp_r3_4;
    HuSprGrpPosSet(temp_r3_4, lbl_1_data_4F8.unk0, lbl_1_data_4F8.unk4);
    HuSprGrpMemberSet(temp_r3_4, 0, HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 69), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x32, 0));
    HuSprPosSet(temp_r3_4, 0, -70.0f, 0.0f);
    HuSprGrpMemberSet(temp_r3_4, 1, HuSprCreate(temp_r3_3->digitAnim, 0x32, 0xC));
    HuSprPosSet(temp_r3_4, 1, 0.0f, 0.0f);
    HuSprColorSet(temp_r3_4, 1, 0x42U, 0xFFU, 0x7AU);
    HuSprGrpMemberSet(temp_r3_4, 2, HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 34), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x32, 2));
    HuSprPosSet(temp_r3_4, 2, 60.0f, 0.0f);
    HuSprColorSet(temp_r3_4, 2, 0x42U, 0xFFU, 0x7AU);
    fn_1_9258(arg0);
}

void fn_1_900C(omObjData *arg0) {
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    M514Score *temp_r31;

    temp_r31 = arg0->data;
    var_f31 = 1.0f;
    temp_r0 = temp_r31->unk9C;
    switch (temp_r0) {                              /* irregular */
    case 0:
        break;
    case 1:
        if (MgSeqModeGet() == 7) {
            temp_r31->unk9C = (s32) (temp_r31->unk9C + 1);
        }
        break;
    case 2:
        if (MgSeqFrameNoGet() >= 0x5AU) {
            temp_r31->unk9C = (s32) (temp_r31->unk9C + 1);
            temp_r31->unkA0 = 0;
            fn_1_9258(arg0);
        }
        break;
    case 3:
        temp_r0_2 = temp_r31->unkA0 + 1;
        temp_r31->unkA0 = temp_r0_2;
        var_f31 = (f32) (1.0 + (0.02 * (f64) (f32) temp_r0_2));
        if ((s32) temp_r31->unkA0 >= 0xA) {
            temp_r31->unk9C = (s32) (temp_r31->unk9C + 1);
            temp_r31->unkA0 = 0;
        }
        break;
    case 4:
        temp_r0_3 = temp_r31->unkA0 + 1;
        temp_r31->unkA0 = temp_r0_3;
        var_f31 = (f32) (1.2 - (0.04 * (f64) (f32) temp_r0_3));
        if ((s32) temp_r31->unkA0 >= 5) {
            temp_r31->unk9C = (s32) (temp_r31->unk9C - 1);
            temp_r31->unkA0 = 0;
        }
        break;
    }
    if ((s32) temp_r31->unk9C != 0) {
        MgScoreDigitScaleSet(temp_r31->unkB0, var_f31, var_f31);
        MgScoreDigitScaleSet(temp_r31->unkB4, var_f31, var_f31);
        HuSprScaleSet(temp_r31->unkAE, 0, var_f31, var_f31);
        HuSprScaleSet(temp_r31->unkAE, 1, var_f31, var_f31);
        HuSprScaleSet(temp_r31->unkAE, 2, (f32) (1.0 + (0.5 * ((f64) var_f31 - 1.0))), var_f31);
    }
}

void fn_1_9258(omObjData *arg0) {
    u32 var_r30;
    M514Score *temp_r31;

    temp_r31 = arg0->data;
    var_r30 = temp_r31->unkA4 / 100;
    if ((s32) var_r30 > 0x3E7) {
        var_r30 = 0x3E7;
    }
    MgScoreValueSet(temp_r31->unkB0, (s32) var_r30);
    MgScoreValueSet(temp_r31->unkB4, temp_r31->unkA4 % 100);
    temp_r31->unkA8 = (s32) temp_r31->unkA4;
}

void fn_1_9300(s16 arg0, s16 arg1) {
    s16 spA;
    s16 sp8;

    sp8 = arg0;
    spA = arg1;
    HuSprPriSet(arg0, 0, spA);
}

void fn_1_9334(void) {
    s32 sp8[4];
    s16 temp_r0;
    s16 temp_r19;
    s32 temp_r20;
    s32 temp_r21;
    s32 var_r24;
    s32 var_r27;
    s32 var_r28;
    s32 var_r30;
    s32 var_r30_2;
    M514Score *temp_r23;
    M514Score *temp_r29;
    M514Score *temp_r31;

    temp_r23 = lbl_1_bss_220->data;
    temp_r31 = lbl_1_bss_220->data;
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31->unk0[var_r30].unk10 = var_r30;
        sp8[var_r30] = var_r30;
        var_r30 += 1;
        goto loop_2;
    }
    var_r30_2 = 0;
loop_10:
    if (var_r30_2 < 3) {
        var_r28 = 0;
loop_8:
        if (var_r28 < 3) {
            temp_r20 = sp8[var_r28];
            temp_r21 = sp8[var_r28 + 1];
            if ((s32) temp_r31->unk0[temp_r20].unkC < (s32) temp_r31->unk0[temp_r21].unkC) {
                {
                    s32 swap = temp_r31->unk0[temp_r20].unk10;
                    temp_r31->unk0[temp_r20].unk10 = temp_r31->unk0[temp_r21].unk10;
                    temp_r31->unk0[temp_r21].unk10 = swap;
                    swap = sp8[var_r28];
                    sp8[var_r28] = sp8[var_r28 + 1];
                    sp8[var_r28 + 1] = swap;
                }
            }
            var_r28 += 1;
            goto loop_8;
        }
        var_r30_2 += 1;
        goto loop_10;
    }
    temp_r29 = lbl_1_bss_220->data;
    var_r27 = 0;
loop_13:
    if (var_r27 < 4) {
        temp_r0 = (temp_r29->unk0[var_r27].unk10 * 2) + 0x32;
        HuSprPriSet(temp_r29->unk0[var_r27].unk14, 0, (s16) (temp_r0 + 1));
        MgScorePriSet(temp_r29->unk0[var_r27].unk18, temp_r0);
        MgScorePriSet(temp_r29->unk0[var_r27].unk1C, temp_r0);
        temp_r19 = temp_r29->unk0[var_r27].unk16;
        HuSprPriSet(temp_r19, 0, temp_r0);
        HuSprPriSet(temp_r19, 1, temp_r0);
        HuSprPriSet(temp_r19, 2, temp_r0);
        var_r27 += 1;
        goto loop_13;
    }
    var_r24 = 0;
loop_16:
    if (var_r24 < 4) {
        temp_r23->unkC8[var_r24][0] = lbl_1_data_53C[temp_r23->unk0[var_r24].unk10].unk0;
        temp_r23->unkC8[var_r24][1] = lbl_1_data_53C[temp_r23->unk0[var_r24].unk10].unk4;
        var_r24 += 1;
        goto loop_16;
    }
}

void fn_1_9570(s32 arg0, f32 farg0) {
    ((M514Score *)lbl_1_bss_220->data)->unk0[arg0].unkC = (s32) (3.0f * farg0);
}

s32 fn_1_95BC(s32 arg0) {
    return ((M514Score *)lbl_1_bss_220->data)->unk0[arg0].unkC;
}

f32 fn_1_95F4(s32 arg0) {
    return (f32) (-2500.0 + (f64) ((f32) ((M514Score *)lbl_1_bss_220->data)->unk0[arg0].unkC / 3.0f));
}

f32 fn_1_9688(void) {
    f32 temp_f1;
    s32 var_r27;
    s32 var_r29;
    s32 var_r31;
    M514Score *temp_r30;

    temp_r30 = lbl_1_bss_220->data;
    var_r29 = 0;
    var_r27 = 0;
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        if (var_r29 < (s32) temp_r30->unk0[var_r31].unkC) {
            var_r29 = temp_r30->unk0[var_r31].unkC;
            var_r27 = var_r31;
        }
        var_r31 += 1;
        goto loop_4;
    }
    temp_f1 = fn_1_4238(var_r27);
    return (f32) ((f64) temp_f1 + (0.5 * (f64) ((f32) (-2500.0 + (f64) ((f32) var_r29 / 3.0f)) - temp_f1)));
}

f32 fn_1_9794(void) {
    return (f32) (-2500.0 + (f64) ((f32) ((M514Score *)lbl_1_bss_220->data)->unkA8 / 3.0f));
}

s32 fn_1_9820(void) {
    s32 var_r29;
    s32 var_r30;
    M514Score *temp_r31;

    temp_r31 = lbl_1_bss_220->data;
    var_r29 = 0;
    var_r30 = 0;
loop_6:
    if (var_r30 < 4) {
        if ((fn_1_1704((u32) var_r30) != -1) && (fn_1_41C4((u32) var_r30) != 0) && ((s32) temp_r31->unk0[var_r30].unkC > var_r29)) {
            var_r29 = temp_r31->unk0[var_r30].unkC;
        }
        var_r30 += 1;
        goto loop_6;
    }
    if (var_r29 > (s32) temp_r31->unkA4) {
        MgSeqRecordSet(var_r29);
        GWMgRecordSet(5, (u32) var_r29);
        temp_r31->unkA4 = var_r29;
        temp_r31->unk9C = 1;
        return 1;
    }
    return 0;
}

void fn_1_98F4(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        /* MP5 decathlon score */
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_510C(HUPROCESS *arg0) {
    ANIMDATA **temp_r3_2;
    omObjData *temp_r3;

    temp_r3 = omAddObjEx(arg0, 0x14, 6U, 0U, -1, fn_1_51C0);
    lbl_1_bss_210 = temp_r3;
    temp_r3->stat |= 0x100;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, 4, MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 4);
    fn_1_5744();
    temp_r3->work[0] = 0;
}

void fn_1_51BC(void) {

}

void fn_1_51C0(omObjData *arg0) {
    void *sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;

    sp8 = arg0->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 0), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[0] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DModelLayerSet(temp_r3, 4);
    Hu3DModelShadowMapSet(temp_r3);
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 1), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[1] = temp_r3_2;
    Hu3DModelAttrSet(temp_r3_2, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_2, 4);
    temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 2), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[2] = temp_r3_3;
    Hu3DModelAttrSet(temp_r3_3, 0x40000040U);
    Hu3DModelLayerSet(temp_r3_3, 3);
    temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 3), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[3] = temp_r3_4;
    Hu3DModelAttrSet(temp_r3_4, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_4, 2);
    temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M514, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[4] = temp_r3_5;
    Hu3DModelAttrSet(temp_r3_5, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_5, 1);
    Hu3DModelShadowMapSet(temp_r3_5);
    if (0 == 0) {
        fn_1_57F0(arg0);
    }
    arg0->func = fn_1_536C;
}

void fn_1_536C(omObjData *obj) {
    f32 temp_f1;

    if ((u32) (obj->work[0] & 3) == 0) {
        fn_1_8180(&lbl_1_data_4C4);
    }
    temp_f1 = (f32) ((f64) lbl_1_bss_214 - 0.013);
    lbl_1_bss_214 = temp_f1;
    if (temp_f1 < 1.0f) {
        lbl_1_bss_214 = 1.0f;
    }
    if (0 == 0) {
        fn_1_5858();
    }
    obj->work[0] += 1;
}






void fn_1_5744(void) {
    lbl_1_bss_214 = 2.0f;
    Hu3DBGColorSet(lbl_1_data_4A0->unk8, lbl_1_data_4A0->unk9, lbl_1_data_4A0->unkA);
    Hu3DFogSet(lbl_1_data_4A0->unk0, lbl_1_data_4A0->unk4, lbl_1_data_4A0->unk8, lbl_1_data_4A0->unk9, lbl_1_data_4A0->unkA);
    Hu3DLayerHookSet(0, fn_1_56AC);
    Hu3DLayerHookSet(2, fn_1_5610);
    Hu3DLayerHookSet(3, fn_1_5574);
    Hu3DLayerHookSet(4, fn_1_54DC);
}

void fn_1_57F0(omObjData *arg0) {
    s16 temp_r3;
    void *temp_r30;

    temp_r30 = arg0->data;
    ((M514Goal *) temp_r30)->unk0 = fn_1_9794();
    temp_r3 = Hu3DHookFuncCreate(fn_1_585C);
    arg0->model[5] = temp_r3;
    Hu3DModelLayerSet(temp_r3, 5);
}

void fn_1_5858(void) {

}

