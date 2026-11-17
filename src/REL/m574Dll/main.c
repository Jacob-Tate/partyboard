// MP5 m574 (Panic Pinball), generated from its m2c draft by tools/mp5/ports/m574Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m574Dll (tools/mp5/decomp.py m574Dll --types tools/mp5/types/m574Dll.h)
// Written from the draft: Panic Pinball (2 vs 2; one pinball table, each team has two flippers (a player each)
// and shoots balls at the targets, bumpers and slot machines). Runs on MP5's MgSeq sequencer.
// Source files in MP5: m574.c (sequence), player.c (lbl_1_bss_38), stage.c (lbl_1_bss_48), ball.c (lbl_1_bss_50),
// score.c (lbl_1_bss_58), collide.c (lbl_1_bss_60: the collision registry + mesh colliders).
// objdata: M574Stage
// objdata fn_1_1068 fn_1_1264 fn_1_1588 fn_1_17A0 fn_1_1830 fn_1_1938 fn_1_19AC fn_1_1D54 fn_1_1E4C fn_1_1F28 fn_1_1F9C: M574Player
// objdata fn_1_7238 fn_1_7328 fn_1_7468 fn_1_75EC fn_1_71BC fn_1_7200: M574Score
// objdata fn_1_6758 fn_1_686C: M574Balls
// objdata fn_1_7AE4: M574Reg
// objexpr lbl_1_bss_48: M574Stage
// objexpr lbl_1_bss_50: M574Balls
// objexpr lbl_1_bss_58: M574Score
// objexpr lbl_1_bss_60: M574Reg
// objexpr lbl_1_bss_38: M574Player

// var fn_1_6758 temp_r30: M574Ball
// var fn_1_686C temp_r31: M574Ball
// var fn_1_6C2C temp_r31: M574Ball
// var fn_1_6CC8 temp_r31: M574Ball
// var fn_1_6D7C temp_r31: M574Ball
// var fn_1_70B0 temp_r31: M574Ball
// var fn_1_7AE4 temp_r26_2: M574Hit
// var fn_1_7238 temp_r29: M574Side
// var fn_1_7328 temp_r31: M574Side
// var fn_1_7874 temp_r30: M574Side
// var fn_1_26F4 temp_r29: M574Prop
// var fn_1_3240 temp_r27: M574Prop
// var fn_1_34B0 var_r30: M574Hit
// var fn_1_4660 temp_r31: M574Prop
// var fn_1_47DC temp_r27: M574Kicker
// var fn_1_5680 temp_r31: M574Prop
// var fn_1_5750 temp_r31: M574Prop
// var fn_1_5934 temp_r26: M574Prop
// var fn_1_6478 temp_r31: M574Flipper
// var fn_1_6568 temp_r31: M574Flipper

typedef struct M574Pair {
    f32 unk0;
    f32 unk4;
} M574Pair;

typedef struct M574Hit { // a ball's collision shape (kind 0), 0x30
    s32 unk0; // 1 active, 2 held by a kicker
    s32 unk4;
    s32 unk8; // index
    s32 unkC; // kind: 0 ball
    void *unk10; // owner (M574Ball)
    void *unk14; // update callback (void (*)(owner))
    Vec *unk18; // pos
    Vec *unk1C; // vel
    f32 unk20; // previous pos
    f32 unk24;
    f32 unk28;
    f32 unk2C; // radius
} M574Hit;

typedef struct M574Circle { // a round obstacle (kind 0 of the second collision table), 0x24
    s32 unk0; // 1 active
    s32 unk4; // type
    s32 unk8; // index
    s32 unkC; // kind: 0 circle
    void *unk10; // owner
    void *unk14;
    void *unk18; // on-hit callback: s32 (*)(M574Circle *, M574Hit *)
    Vec *unk1C; // center
    f32 unk20; // radius
} M574Circle;

typedef struct M574Line { // collision line (current frame / previous frame), 0x28
    f32 unk0; // from
    f32 unk4;
    f32 unk8;
    f32 unkC; // to
    f32 unk10;
    f32 unk14;
    f32 unk18; // normal
    f32 unk1C;
    f32 unk20;
    f32 unk24; // plane offset
} M574Line;

typedef struct M574Seg { // a collision line of the model (local), 0x1C
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void *unk18; // matrix of its object
} M574Seg;

typedef struct M574Mesh { // collision lines taken from a model (kind 1), 0x3C
    s32 unk0; // 1 active
    s32 unk4; // type
    s32 unk8; // index
    s32 unkC; // kind: 1 mesh
    void *unk10; // owner
    void *unk14;
    void *unk18; // on-hit callback: s32 (*)(M574Mesh *, M574Hit *)
    s32 unk1C; // line count
    M574Line *unk20; // lines (current)
    M574Line *unk24; // lines (previous)
    M574Seg *unk28; // lines (local)
    s32 unk2C; // object count
    HSFTRANSFORM **unk30; // object transforms
    void *unk34; // their matrices
    M574Line *unk38; // line hit last
} M574Mesh;

typedef struct M574Reg { // lbl_1_bss_60 data, 0x198
    M574Hit *unk0[0x52]; // balls
    M574Circle *unk148[0x14]; // obstacles (circles and meshes)
} M574Reg;

typedef struct M574Ball { // 0x6C
    s32 unk0; // state
    s32 unk4;
    s32 unk8;
    s32 unkC; // 1: beyond the plunger line
    s32 unk10; // in the goal zone
    s16 unk14; // model
    char pad16[2];
    Vec unk18; // pos
    Vec unk24; // vel
    char pad30[0xC];
    M574Hit unk3C;
} M574Ball;

typedef struct M574Balls { // lbl_1_bss_50 data, 0x21C0
    M574Ball unk0[0x50];
} M574Balls;

typedef struct M574Player { // OMOBJ::data of lbl_1_bss_38[4], 0x78
    s32 unk0; // player
    s32 unk4; // team
    s32 unk8; // slot in the team (the flipper)
    s32 unkC; // character
    s32 unk10; // motion
    s32 unk14; // buttons pressed
    s32 unk18; // buttons held
    f32 unk1C;
    f32 unk20; // flipper power
    s32 unk24; // com
    s32 unk28; // com level
    s32 unk2C; // com state
    s32 unk30; // com timer
    s32 unk34; // com: fast ball
    s32 unk38; // mode step
    s32 unk3C;
    s32 unk40; // frame counter
    s32 unk44;
    Vec unk48; // pos
    Vec unk54; // vel
    char pad60[0xC];
    f32 unk6C; // rot y
    s32 unk70;
    s32 unk74;
} M574Player;

typedef struct M574Side { // score of a team, 0x1C
    s32 unk0; // score
    s32 unk4; // shown
    s32 unk8; // blink timer
    s32 unkC; // last added
    s16 unk10[5]; // digit anims
    char pad1A[2];
} M574Side;

typedef struct M574Score { // lbl_1_bss_58 data, 0x4C
    M574Side unk0[2];
    s32 unk38; // step
    s32 unk3C;
    s32 unk40; // record
    s16 unk44; // score window
    s16 unk46; // sprite group
    MGSCORE *unk48;
} M574Score;

typedef struct M574Prop { // targets, bumpers, the centre bumper, the enemies: 0x88
    s32 unk0; // state
    s32 unk4; // timer
    s32 unk8;
    s32 unkC; // side
    Vec unk10; // pos
    Vec unk1C; // offset / velocity
    Vec unk28; // rot
    f32 unk34;
    s32 unk38; // hit flag
    Vec unk3C; // scale / offsets
    HSFOBJECT *unk48; // object of the model
    M574Circle unk4C;
    char pad70[0x18];
} M574Prop;

typedef struct M574Flipper { // 0x50
    f32 unk0; // power
    f32 unk4; // shown
    f32 unk8; // angle
    f32 unkC; // target angle
    s32 unk10; // 1: layers changed
    M574Mesh unk14;
} M574Flipper;

typedef struct M574Slot { // slot machine, 0x5C
    s32 unk0; // state
    s32 unk4; // timer
    s32 unk8; // timer 2
    s32 unkC; // sound
    s32 unk10; // spinning
    s32 unk14[3]; // reel stopped
    s32 unk20[3]; // symbol
    f32 unk2C[3]; // angle
    f32 unk38[3]; // target angle
    f32 unk44[3]; // speed
    HSFOBJECT *unk50[3];
} M574Slot;

typedef struct M574Kicker { // 0x88
    s32 unk0; // state
    char pad4[0xC];
    f32 unk10; // pos
    f32 unk14;
    char pad18[0x1C];
    f32 unk34; // offset
    char pad38[0x10];
    M574Hit *unk48; // ball held
    char pad4C[0x3C];
} M574Kicker;

typedef struct M574Stage { // lbl_1_bss_48 data, 0x108C
    s32 unk0[2]; // ball spawn timers
    s32 unk8;
    s32 unkC; // balls left
    char pad10[4];
    M574Prop unk14; // centre bumper
    s16 unk9C[5]; // particles
    char padA6[2];
    M574Flipper unkA8[4];
    M574Slot unk1E8[2];
    M574Kicker unk2A0[2];
    M574Prop unk3B0[14];
    M574Prop unkB20[6];
    M574Prop unkE50[2];
    M574Mesh unkF60; // cage
    M574Mesh unkF9C[4];
} M574Stage;


void fn_1_6C2C(Vec *pos, Vec *vel);
s32 fn_1_6CC8(s32 side);
s32 fn_1_6D7C(s32 side, Vec *pos, f32 farg0, f32 farg1, f32 farg2);
M574Hit *fn_1_70B0(s32 idx, Vec *pos, Vec *vel);
s32 fn_1_7C88(M574Hit *a, M574Hit *b);
s32 fn_1_7FD8(M574Hit *a, M574Circle *b);
s32 fn_1_82AC(M574Hit *ball, M574Mesh *mesh, M574Line *lines, f32 *prev);
s32 fn_1_87B8(M574Hit *ball, M574Mesh *mesh);
s32 fn_1_8AD0(M574Hit *hit);
s32 fn_1_8B48(M574Circle *hit);
void fn_1_8C94(M574Mesh *mesh, HSFOBJECT *objs, s32 count);
void fn_1_8F54(M574Mesh *mesh, s16 model);
void fn_1_8FA8(M574Mesh *mesh, HSFOBJECT *obj);
void fn_1_8FDC(M574Mesh *mesh);
s32 fn_1_2D88(M574Mesh *mesh, M574Hit *ball);
s32 fn_1_3240(M574Circle *self, M574Hit *ball);
s32 fn_1_47DC(M574Mesh *mesh, M574Hit *ball);
s32 fn_1_5628(M574Circle *self, M574Hit *ball);
s32 fn_1_5D64(M574Circle *self, M574Hit *ball);
void fn_1_5680(Vec *pos);
void fn_1_63B0(Vec *pos, Vec *accel, s32 count);
void fn_1_6478(s32 flipper, f32 power);
f64 fn_1_6568(s32 flipper);
s32 fn_1_4330(f32 angle);
f32 fn_1_CC8(f32 cur, f32 target, f32 rate);
void fn_1_C10(s32 sound, Vec *pos);
void fn_1_77D4(s32 team, s32 prize);
void fn_1_7874(s32 team, s32 prize);
static void Mp5VecReflect(Vec *src, Vec *normal, Vec *dst)
{
    Vec uI, uN;
    f32 cosA;

    uI.x = -src->x;
    uI.y = -src->y;
    uI.z = -src->z;
    VECNormalize(&uI, &uI);
    VECNormalize(normal, &uN);
    cosA = VECDotProduct(&uI, &uN);
    dst->x = 2.0f * uN.x * cosA - uI.x;
    dst->y = 2.0f * uN.y * cosA - uI.y;
    dst->z = 2.0f * uN.z * cosA - uI.z;
    VECNormalize(dst, dst);
}

static double __frsqrte(double x)
{
    return 1.0 / sqrt(x);
}

void fn_1_6650(HUPROCESS *arg0);
void fn_1_66F0(void);
void fn_1_66F4(omObjData *obj);
void fn_1_6730(omObjData *obj);
void fn_1_6758(omObjData *arg0);
void fn_1_686C(omObjData *arg0);
s32 fn_1_6B38(M574Ball *arg0);
void fn_1_6BD4(M574Ball *arg0);
void fn_1_6C2C(Vec *pos, Vec *vel);
s32 fn_1_6CC8(s32 side);
s32 fn_1_6D7C(s32 side, Vec *pos, f32 farg0, f32 farg1, f32 farg2);
M574Hit *fn_1_70B0(s32 idx, Vec *pos, Vec *vel);
void fn_1_7A48(HUPROCESS *arg0);
void fn_1_7AD0(void);
void fn_1_7AD4(omObjData *obj);
void fn_1_7AE4(omObjData *obj);
s32 fn_1_7C88(M574Hit *a, M574Hit *b);
s32 fn_1_7FD8(M574Hit *a, M574Circle *b);
s32 fn_1_82AC(M574Hit *ball, M574Mesh *mesh, M574Line *lines, f32 *prev);
s32 fn_1_87B8(M574Hit *ball, M574Mesh *mesh);
s32 fn_1_8AD0(M574Hit *hit);
s32 fn_1_8B48(M574Circle *hit);
void fn_1_8C94(M574Mesh *mesh, HSFOBJECT *objs, s32 count);
void fn_1_8F54(M574Mesh *mesh, s16 model);
void fn_1_8FA8(M574Mesh *mesh, HSFOBJECT *obj);
void fn_1_8FDC(M574Mesh *mesh);
void ObjectSetup(void);
void fn_1_348(s16 mode, s16 frameNo);
void fn_1_3B8(s16 arg1, s16 frameNo);
void fn_1_548(s16 mode, s16 frameNo);
void fn_1_54C(s16 arg1, s16 frameNo);
void fn_1_5A8(s16 arg1, s16 frameNo);
void fn_1_730(s16 arg1, s16 frameNo);
void fn_1_82C(s16 arg1, s16 frameNo);
void fn_1_8E4(s16 mode, s16 frameNo);
void fn_1_8E8(s16 mode, s16 frameNo);
s16 fn_1_918(void);
s16 fn_1_928(s32 arg0);
u32 fn_1_940(u32 arg0);
void fn_1_9FC(s32 arg0, s16 arg1, s16 arg2);
void fn_1_AAC(void);
void fn_1_C10(s32 sound, Vec *pos);
f32 fn_1_CC8(f32 cur, f32 target, f32 rate);
void fn_1_E98(HUPROCESS *arg0);
void fn_1_1044(void);
void fn_1_1068(omObjData *obj);
void fn_1_1264(omObjData *obj);
void fn_1_1588(omObjData *obj);
void fn_1_17A0(omObjData *arg0);
void fn_1_182C(void);
void fn_1_1830(omObjData *arg0);
void fn_1_1938(omObjData *arg0);
void fn_1_19AC(omObjData *arg0);
void fn_1_1D54(omObjData *arg0, u32 arg1);
s32 fn_1_1E4C(omObjData *arg0);
s32 fn_1_1F28(u32 arg0);
void fn_1_1F9C(u32 arg0);
void fn_1_7130(HUPROCESS *arg0);
void fn_1_71B8(void);
void fn_1_71BC(omObjData *obj);
void fn_1_7200(omObjData *obj);
void fn_1_7238(omObjData *arg0);
void fn_1_7328(omObjData *arg0);
void fn_1_7468(omObjData *arg0);
void fn_1_75EC(omObjData *arg0);
void fn_1_77D4(s32 team, s32 prize);
void fn_1_7874(s32 team, s32 prize);
s32 fn_1_7948(s32 arg0);
s32 fn_1_797C(void);
void fn_1_2028(HUPROCESS *arg0);
void fn_1_20C8(void);
void fn_1_20CC(omObjData *obj);
void fn_1_2364(omObjData *obj);
void fn_1_26F4(omObjData *arg0);
void fn_1_2928(omObjData *arg0);
void fn_1_2B88(omObjData *arg0);
s32 fn_1_2D88(M574Mesh *mesh, M574Hit *ball);
void fn_1_2F8C(omObjData *arg0);
void fn_1_3154(omObjData *arg0);
s32 fn_1_3240(M574Circle *self, M574Hit *ball);
void fn_1_3374(omObjData *arg0);
void fn_1_34B0(omObjData *arg0);
void fn_1_383C(omObjData *arg0);
void fn_1_3A1C(omObjData *arg0);
s32 fn_1_4330(f32 angle);
void fn_1_448C(omObjData *arg0);
void fn_1_4660(omObjData *arg0);
s32 fn_1_47DC(M574Mesh *mesh, M574Hit *ball);
void fn_1_4D28(omObjData *arg0);
void fn_1_4EE8(omObjData *arg0);
s32 fn_1_5628(M574Circle *self, M574Hit *ball);
void fn_1_5680(Vec *pos);
void fn_1_5750(omObjData *arg0);
void fn_1_5934(omObjData *arg0);
s32 fn_1_5D64(M574Circle *self, M574Hit *ball);
void fn_1_5E5C(omObjData *arg0);
void fn_1_5ECC(omObjData *arg0);
void fn_1_6168(omObjData *arg0);
void fn_1_629C(void);
void fn_1_62A0(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_63B0(Vec *pos, Vec *accel, s32 count);
void fn_1_6478(s32 flipper, f32 power);
f64 fn_1_6568(s32 flipper);

struct _struct_lbl_1_data_1BC_0x18 {
    /* 0x00 */ f32 unk0;                            /* inferred */
    /* 0x04 */ s32 unk4;                            /* inferred */
    /* 0x08 */ s32 unk8;                            /* inferred */
    /* 0x0C */ s32 unkC;                            /* inferred */
    /* 0x10 */ s32 unk10;                           /* inferred */
    /* 0x14 */ f32 unk14;                           /* inferred */
};                                                  /* size = 0x18 */

struct _struct_lbl_1_data_C4_0xC {
    /* 0x0 */ u16 unk0;                             /* inferred */
    /* 0x2 */ char pad2[2];
    /* 0x4 */ f32 unk4;                             /* inferred */
    /* 0x8 */ u32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

omObjData *lbl_1_bss_50;
static s32 lbl_1_data_5D8[4] = { 0, 1, 3, 2 };
omObjData *lbl_1_bss_60;
OMCAMERAVIEW lbl_1_data_0[2] = {
    { { 0.0f, 1350.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1180.0f },
    { { 0.0f, 800.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 2750.0f },
};
Vec lbl_1_data_38 = { 100.0f, 800.0f, -100.0f };
Vec lbl_1_data_44 = { 0.3f, -0.8f, 0.3f };
Vec lbl_1_data_50 = { 20.0f, 45.0f, 1000.0f };
static GXColor lbl_1_data_5C = { 0xFF, 0xFF, 0xFF, 0xFF };
static Vec lbl_1_data_60 = { 0.0f, 1000.0f, 1500.0f };
static Vec lbl_1_data_6C = { 0.0f, 0.0f, 1.0f };
static Vec lbl_1_data_78 = { 0.0f, 0.0f, 0.0f };
static MGSEQ_PARAM lbl_1_data_84 = {
    0x3C,
    1,
    fn_1_348,
    fn_1_3B8,
    fn_1_548,
    fn_1_54C,
    fn_1_5A8,
    fn_1_730,
    fn_1_82C,
    fn_1_8E4,
    fn_1_8E8,
};
s16 lbl_1_bss_0[4];
s16 lbl_1_bss_8[4];
s16 lbl_1_bss_10[4];
s32 lbl_1_bss_18;
s16 lbl_1_bss_1C;
s16 lbl_1_bss_1E;
s32 lbl_1_bss_20;
s32 lbl_1_bss_24;
s32 lbl_1_bss_28;
s32 lbl_1_bss_2C;
omObjData *lbl_1_bss_30;
HUPROCESS *lbl_1_bss_34;
static u32 lbl_1_data_B0[5] = { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 76), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 49) };
static struct _struct_lbl_1_data_C4_0xC lbl_1_data_C4[5] = {
    { 0, 0.2f, 0x40000001 },
    { 1, 0.1f, 0x40000001 },
    { 2, 0.2f, 0 },
    { 3, 0.2f, 0 },
    { 4, 0.2f, 0 },
};
Vec lbl_1_data_100[4] = {
    { -1100.0f, 0.0f, 0.0f },
    { -220.0f, 0.0f, 0.0f },
    { 220.0f, 0.0f, 0.0f },
    { 1100.0f, 0.0f, 0.0f },
};
Vec lbl_1_data_130[4] = {
    { -900.0f, 50.0f, 0.0f },
    { -420.0f, 50.0f, 0.0f },
    { 420.0f, 50.0f, 0.0f },
    { 900.0f, 50.0f, 0.0f },
};
static f32 lbl_1_data_160[4] = { 90.0f, 270.0f, 90.0f, 270.0f };
static s32 lbl_1_data_1AC[4] = { 0x24, 0x3C, 0x44, 0x5C };
static struct _struct_lbl_1_data_1BC_0x18 lbl_1_data_1BC[4] = {
    { 400.0f, 0x12, 0x10, 9, 9, 0.7f },
    { 350.0f, 0x13, 0xF, 8, 8, 0.75f },
    { 320.0f, 0x15, 0xE, 7, 7, 0.8f },
    { 300.0f, 0x18, 0xD, 6, 6, 0.85f },
};
omObjData *lbl_1_bss_38[4];
M574Pair lbl_1_data_570 = { 288.0f, 58.0f };
static s32 lbl_1_data_578[0xD] = {
    0x1F4,
    0x3E8,
    0x7D0,
    0xA,
    0x32,
    0x64,
    0x64,
    0x32,
    0x32,
    0x64,
    0xA,
    0x14,
    0xC8,
};
s8 lbl_1_data_5AC[2][5][4] = {
    {
        { 0x30, 0, 0, 0 },
        { 0x31, 0, 0, 0 },
        { 0x32, 0, 0, 0 },
        { 0x33, 0, 0, 0 },
        { 0x34, 0, 0, 0 },
    },
    {
        { 0x35, 0, 0, 0 },
        { 0x36, 0, 0, 0 },
        { 0x37, 0, 0, 0 },
        { 0x38, 0, 0, 0 },
        { 0x39, 0, 0, 0 },
    },
};
omObjData *lbl_1_bss_58;
static s32 lbl_1_data_220[4] = { DATA_MAKE_NUM(DATADIR_MP5_M574, 12), DATA_MAKE_NUM(DATADIR_MP5_M574, 13), DATA_MAKE_NUM(DATADIR_MP5_M574, 17), DATA_MAKE_NUM(DATADIR_MP5_M574, 18) };
static s32 lbl_1_data_230[4] = { DATA_MAKE_NUM(DATADIR_MP5_M574, 24), DATA_MAKE_NUM(DATADIR_MP5_M574, 25), DATA_MAKE_NUM(DATADIR_MP5_M574, 24), DATA_MAKE_NUM(DATADIR_MP5_M574, 25) };
static s32 lbl_1_data_240[4] = { DATA_MAKE_NUM(DATADIR_MP5_M574, 15), DATA_MAKE_NUM(DATADIR_MP5_M574, 16), DATA_MAKE_NUM(DATADIR_MP5_M574, 20), DATA_MAKE_NUM(DATADIR_MP5_M574, 21) };
Vec lbl_1_data_250[4] = {
    { -875.0f, 100.0f, -40.0f },
    { -445.0f, 100.0f, -40.0f },
    { 445.0f, 100.0f, -40.0f },
    { 875.0f, 100.0f, -40.0f },
};
static f32 lbl_1_data_280[4] = { 60.0f, 300.0f, 60.0f, 300.0f };
s8 lbl_1_data_290[4][0xA] = {
    { 0x66, 0x75, 0x72, 0x69, 0x68, 0x61, 0x6E, 0, 0, 0 },
    { 0x66, 0x75, 0x72, 0x69, 0x68, 0x61, 0x6E, 0, 0, 0 },
    { 0x66, 0x75, 0x72, 0x69, 0x68, 0x61, 0x6E, 0, 0, 0 },
    { 0x66, 0x75, 0x72, 0x69, 0x68, 0x61, 0x6E, 0, 0, 0 },
};
static s32 lbl_1_data_2B8[3] = { 0, 1, 2 };
u8 lbl_1_data_2C4[0x14] = { 0, 1, 0, 0, 1, 1, 2, 0, 1, 2, 2, 1, 0, 2, 1, 1, 0, 2, 0, 2 };
s8 lbl_1_data_2D8[6][0xA] = {
    { 0x73, 0x6C, 0x6F, 0x74, 0x5F, 0x4C, 0x33, 0, 0, 0 },
    { 0x73, 0x6C, 0x6F, 0x74, 0x5F, 0x4C, 0x32, 0, 0, 0 },
    { 0x53, 0x6C, 0x6F, 0x74, 0, 0, 0, 0, 0, 0 },
    { 0x73, 0x6C, 0x6F, 0x74, 0x5F, 0x52, 0x33, 0, 0, 0 },
    { 0x73, 0x6C, 0x6F, 0x74, 0x5F, 0x52, 0x32, 0, 0, 0 },
    { 0x73, 0x6C, 0x6F, 0x74, 0x5F, 0x52, 0x31, 0, 0, 0 },
};
static s32 lbl_1_data_314[2] = { DATA_MAKE_NUM(DATADIR_MP5_M574, 14), DATA_MAKE_NUM(DATADIR_MP5_M574, 19) };
s8 lbl_1_data_31C[0xE][0xA] = {
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0, 0, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x32, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x33, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x34, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x35, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x4C, 0x44, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x4C, 0x4C, 0x55, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x35, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x34, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x33, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x32, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x31, 0, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x52, 0x44, 0, 0 },
    { 0x62, 0x6C, 0x6F, 0x63, 0x6B, 0x52, 0x52, 0x55, 0, 0 },
};
s8 lbl_1_data_3A8[4][0xA] = {
    { 0x62, 0x5F, 0x61, 0x74, 0x61, 0x4C, 0x4C, 0, 0, 0 },
    { 0x62, 0x5F, 0x61, 0x74, 0x61, 0x4C, 0, 0, 0, 0 },
    { 0x62, 0x5F, 0x61, 0x74, 0x61, 0x52, 0, 0, 0, 0 },
    { 0x62, 0x5F, 0x61, 0x74, 0x61, 0x52, 0x52, 0, 0, 0 },
};
s8 lbl_1_data_3D0[9][0xA] = {
    { 0x6B, 0x75, 0x70, 0x70, 0x61, 0, 0, 0, 0, 0 },
    { 0x31, 0x30, 0x4C, 0, 0, 0, 0, 0, 0, 0 },
    { 0x35, 0x30, 0x4C, 0, 0, 0, 0, 0, 0, 0 },
    { 0x31, 0x30, 0x30, 0x4C, 0, 0, 0, 0, 0, 0 },
    { 0x31, 0x30, 0x52, 0, 0, 0, 0, 0, 0, 0 },
    { 0x35, 0x30, 0x52, 0, 0, 0, 0, 0, 0, 0 },
    { 0x31, 0x30, 0x30, 0x52, 0, 0, 0, 0, 0, 0 },
    { 0x62, 0x61, 0x6E, 0x65, 0x4C, 0, 0, 0, 0, 0 },
    { 0x62, 0x61, 0x6E, 0x65, 0x52, 0, 0, 0, 0, 0 },
};
static s32 lbl_1_data_42C[9] = {
    DATA_MAKE_NUM(DATADIR_MP5_M574, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M574, 11),
};
static s32 lbl_1_data_450[6] = { 0, 0, 0, 1, 1, 1 };
static s32 lbl_1_data_468[6] = { 3, 4, 5, 3, 4, 5 };
static s32 lbl_1_data_480[3] = { DATA_MAKE_NUM(DATADIR_MP5_M574, 27), DATA_MAKE_NUM(DATADIR_MP5_M574, 28), DATA_MAKE_NUM(DATADIR_MP5_M574, 29) };
Vec lbl_1_data_48C[2] = { { -650.0f, 960.0f, 0.0f }, { 650.0f, 960.0f, 0.0f } };
s8 lbl_1_data_4A4[0xC] = { 0x6B, 0x75, 0x70, 0x70, 0x61, 0x62, 0x6F, 0x6D, 0x62, 0, 0, 0 };
static Vec lbl_1_data_4B0[2] = { { -95.0f, 1215.0f, 1000.0f }, { 95.0f, 1215.0f, 1000.0f } };
static Vec lbl_1_data_4C8[2] = { { 3.0f, 3.0f, -1.0f }, { -3.0f, 3.0f, -1.0f } };
s8 lbl_1_data_504[0xC] = { 0x6D, 0x35, 0x34, 0x38, 0x74, 0x69, 0x6D, 0x65, 0, 0, 0, 0 };
M574Pair lbl_1_data_510[0xA] = {
    { -0.25f, -0.125f },
    { -0.25f, 0.0f },
    { -0.25f, 0.125f },
    { -0.25f, 0.25f },
    { -0.25f, 0.375f },
    { -0.25f, 0.5f },
    { -0.25f, 0.625f },
    { -0.25f, 0.75f },
    { 0.0f, -0.125f },
    { 0.0f, 0.0f },
};
static s32 lbl_1_data_560[4] = { 0x923, 0x924, 0x925, 0x926 };
omObjData *lbl_1_bss_48;
s32 lbl_1_rodata_10[3] = { 0, 0, 0 };               /* const */
s32 lbl_1_rodata_1C[3] = { 0, 0, 0xBF800000 };      /* const */
s32 lbl_1_rodata_60[2] = { 0, 0 };                  /* const */
s32 lbl_1_rodata_68[2] = { 0, 2 };                  /* const */

void fn_1_6650(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    M574Seg *temp_r3_2;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x1E, 0x50U, 0U, -1, fn_1_66F4);
    lbl_1_bss_50 = temp_r3;
    temp_r3->stat |= 0x100;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M574Balls), MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, sizeof(M574Balls));
    temp_r3->work[0] = 0;
}

void fn_1_66F0(void) {

}

void fn_1_66F4(omObjData *obj) {
    fn_1_6758(obj);
    obj->func = fn_1_6730;
}

void fn_1_6730(omObjData *obj) {
    omObjData *sp8;

    sp8 = obj;
    fn_1_686C(obj);
}

void fn_1_6758(omObjData *arg0) {
    M574Hit *temp_r31;
    s16 var_r26;
    s16 var_r28;
    s32 var_r29;
    M574Balls *temp_r27;
    M574Ball *temp_r30;

    var_r26 = 0 /* TODO(mp5): uninitialised in the original */;
    temp_r27 = arg0->data;
    var_r29 = 0;
loop_5:
    if (var_r29 < 0x50) {
        temp_r30 = (M574Ball *)((u8 *)temp_r27 + var_r29 * sizeof(M574Ball));
        if (var_r29 == 0) {
            var_r26 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 7), MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r28 = var_r26;
        } else {
            var_r28 = Hu3DModelLink(var_r26);
        }
        temp_r30->unk14 = var_r28;
        Hu3DModelLayerSet(var_r28, 4);
        Hu3DModelAttrSet(var_r28, 1U);
        temp_r31 = &temp_r30->unk3C;
        temp_r30->unk3C.unk0 = 0;
        temp_r31->unk4 = 0;
        temp_r31->unk8 = var_r29;
        temp_r31->unkC = 0;
        temp_r31->unk10 = temp_r30;
        temp_r31->unk14 = fn_1_6BD4;
        temp_r31->unk18 = &temp_r30->unk18;
        temp_r31->unk1C = &temp_r30->unk24;
        temp_r31->unk20 = temp_r30->unk18.x;
        temp_r31->unk24 = temp_r30->unk18.y;
        temp_r31->unk28 = temp_r30->unk18.z;
        temp_r31->unk2C = 40.0f;
        fn_1_8AD0(temp_r31);
        var_r29 += 1;
        goto loop_5;
    }
}

void fn_1_686C(omObjData *arg0) {
    s16 temp_r28;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r27;
    s32 var_r30;
    u32 var_r26;
    M574Balls *temp_r25;
    M574Ball *temp_r31;

    temp_r25 = arg0->data;
    var_r30 = 0;
loop_32:
    if (var_r30 < 0x50) {
        temp_r31 = (M574Ball *)((u8 *)temp_r25 + var_r30 * sizeof(M574Ball));
        temp_r28 = temp_r31->unk14;
        temp_r0 = temp_r31->unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            break;
        case 1:
            temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            temp_r31->unk8 = 0;
            Hu3DModelAttrReset(temp_r28, 1U);
            HuAudFXPlay(0x915);
            /* fallthrough */
        case 2:
            temp_r31->unk24.z = (f32) ((f64) temp_r31->unk24.z - 20.0);
            if ((temp_r31->unk18.z + temp_r31->unk24.z) <= 0.0f) {
                temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                temp_r31->unk18.z = 0.0f;
                temp_r31->unk24.z = 0.0f;
                temp_r31->unk3C.unk0 = (s32) (temp_r31->unk3C.unk0 | 1);
            }
            /* fallthrough */
        case 3:
            if ((u32) (temp_r31->unk3C.unk0 & 2) == 0) {
                if ((s32) temp_r31->unkC != 0) {
                    if (temp_r31->unk18.y < 1550.0f) {
                        temp_r31->unkC = 0;
                    }
                } else if (temp_r31->unk18.y > 1600.0f) {
                    temp_r31->unkC = 1;
                    if (temp_r31->unk18.x < 0.0f) {
                        var_r27 = 0;
                    } else {
                        var_r27 = 1;
                    }
                    fn_1_77D4(var_r27, 0xC);
                }
                temp_r31->unk24.x = (f32) ((f64) temp_r31->unk24.x * 0.98);
                temp_r31->unk24.y = (f32) ((f64) temp_r31->unk24.y - 1.666666753590107);
                if ((temp_r31->unk24.y < 0.0f) && (temp_r31->unk18.y < -200.0f)) {
                    if (temp_r31->unk18.x < 0.0f) {
                        var_r26 = 0;
                    } else {
                        var_r26 = 1;
                    }
                    fn_1_1F9C(var_r26);
                    temp_r31->unk0 = 0;
                    temp_r31->unk3C.unk0 = 0;
                    Hu3DModelAttrSet(temp_r28, 1U);
                    if (temp_r31->unk24.x < 0.0f) {
                        HuAudFXPlay(0x92D);
                    } else {
                        HuAudFXPlay(0x92E);
                    }
                }
            }
            break;
        }
        if ((s32) temp_r31->unk0 != 0) {
            VECAdd(&temp_r31->unk18, &temp_r31->unk24, &temp_r31->unk18);
            temp_r3 = fn_1_6B38(temp_r31);
            if ((s32) temp_r31->unk10 != temp_r3) {
                temp_r31->unk10 = temp_r3;
                HuAudFXPlay(0x91D);
            }
        }
        var_r30 += 1;
        goto loop_32;
    }
}

s32 fn_1_6B38(M574Ball *arg0) {
    if (arg0->unk18.x < -170.0f) {
        return 0;
    }
    if (arg0->unk18.x > 170.0f) {
        return 0;
    }
    if (arg0->unk18.y < 598.0f) {
        return 0;
    }
    if (arg0->unk18.y > 817.0f) {
        return 0;
    }
    return 1;
}

void fn_1_6BD4(M574Ball *arg0) {
    Hu3DModelPosSetV(arg0->unk14, &arg0->unk18);
    arg0->unk3C.unk20 = arg0->unk18.x;
    arg0->unk3C.unk24 = arg0->unk18.y;
    arg0->unk3C.unk28 = arg0->unk18.z;
}

void fn_1_6C2C(Vec *pos, Vec *vel) {
    s32 var_r30;
    M574Ball *temp_r31;

    var_r30 = 0;
loop_4:
    if (var_r30 >= 0x50) {
        return;
    }
    temp_r31 = (M574Ball *)((u8 *)lbl_1_bss_50->data + var_r30 * sizeof(M574Ball));
    if ((s32) temp_r31->unk0 == 0) {
        temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
        temp_r31->unk18.x = (f32) pos->x;
        temp_r31->unk18.y = (f32) pos->y;
        temp_r31->unk18.z = (f32) pos->z;
        temp_r31->unk24.x = (f32) vel->x;
        temp_r31->unk24.y = (f32) vel->y;
        temp_r31->unk24.z = (f32) vel->z;
        return;
    }
    var_r30 += 1;
    goto loop_4;
}

s32 fn_1_6CC8(s32 side) {
    s32 var_r29;
    s32 var_r30;
    M574Ball *temp_r31;

    var_r30 = 0;
    var_r29 = 0;
loop_8:
    if (var_r29 < 0x50) {
        temp_r31 = (M574Ball *)((u8 *)lbl_1_bss_50->data + var_r29 * sizeof(M574Ball));
        if ((s32) temp_r31->unk0 != 0) {
            if (side == 0) {
                if (temp_r31->unk18.x < 0.0f) {
                    var_r30 += 1;
                }
            } else if (temp_r31->unk18.x >= 0.0f) {
                var_r30 += 1;
            }
        }
        var_r29 += 1;
        goto loop_8;
    }
    return var_r30;
}

s32 fn_1_6D7C(s32 side, Vec *pos, f32 farg0, f32 farg1, f32 farg2) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    s32 sp8;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    s32 var_r28;
    s32 var_r30;
    M574Balls *temp_r27;
    M574Ball *temp_r31;

    sp8 = side;
    spC = farg0;
    sp10 = farg2;
    temp_r27 = lbl_1_bss_50->data;
    var_f27 = 100000.0f;
    var_r28 = -1;
    var_r30 = 0;
loop_18:
    if (var_r30 < 0x50) {
        temp_r31 = (M574Ball *)((u8 *)temp_r27 + var_r30 * sizeof(M574Ball));
        if ((s32) temp_r31->unk0 != 0) {
            if (sp8 == 0) {
                if (!(temp_r31->unk18.x >= 0.0f)) {
                    goto block_6;
                }
            } else if (!(temp_r31->unk18.x < 0.0f)) {
block_6:
                temp_f31 = temp_r31->unk18.x - pos->x;
                temp_f30 = temp_r31->unk18.y - pos->y;
                if (farg1 < 180.0f) {
                    var_f28 = (f32) fmod((f64) ((f32) (180.0 * (atan2((f64) temp_f31, (f64) temp_f30) / 3.141592653589793)) - spC), 360.0);
                    if (var_f28 < 0.0f) {
                        var_f28 += 360.0f;
                    }
                    if (!(var_f28 > farg1) || !(var_f28 < (360.0f - farg1))) {
                        goto block_11;
                    }
                } else {
block_11:
                    if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) > 0.0f) {
                        temp_f29 = __frsqrte((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
                        temp_f29_2 = 0.5 * temp_f29 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29 * temp_f29)));
                        temp_f29_3 = 0.5 * temp_f29_2 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_2 * temp_f29_2)));
                        sp14 = (f32) ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (0.5 * temp_f29_3 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_3 * temp_f29_3)))));
                        var_f26 = sp14;
                    } else {
                        var_f26 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
                    }
                    if (!(var_f26 > sp10) && (var_f26 < var_f27)) {
                        var_f27 = var_f26;
                        var_r28 = var_r30;
                    }
                }
            }
        }
        var_r30 += 1;
        goto loop_18;
    }
    return var_r28;
}

M574Hit *fn_1_70B0(s32 idx, Vec *pos, Vec *vel) {
    M574Ball *temp_r31;

    temp_r31 = (M574Ball *)((u8 *)lbl_1_bss_50->data + idx * sizeof(M574Ball));
    if (pos != NULL) {
        pos->x = temp_r31->unk18.x;
        pos->y = temp_r31->unk18.y;
        pos->z = temp_r31->unk18.z;
    }
    if (vel != NULL) {
        vel->x = temp_r31->unk24.x;
        vel->y = temp_r31->unk24.y;
        vel->z = temp_r31->unk24.z;
    }
    return &temp_r31->unk3C;
}

void fn_1_7A48(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    M574Seg *temp_r3_2;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x32, 0U, 0U, -1, fn_1_7AD4);
    lbl_1_bss_60 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M574Reg), MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, sizeof(M574Reg));
}

void fn_1_7AD0(void) {

}

void fn_1_7AD4(omObjData *obj) {
    obj->func = fn_1_7AE4;
}

void fn_1_7AE4(omObjData *obj) {
    M574Circle *temp_r25_2;
    M574Hit *temp_r25;
    M574Hit *temp_r26;
    s32 temp_r0;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r30;
    s32 var_r30_2;
    M574Hit *temp_r26_2;
    M574Reg *temp_r27;

    temp_r27 = obj->data;
    var_r30 = 0;
loop_24:
    if (var_r30 < 0x52) {
        temp_r26 = temp_r27->unk0[var_r30];
        if ((temp_r26 != NULL) && ((u32) (temp_r26->unk0 & 1) != 0) && ((s32) temp_r26->unkC == 0)) {
            var_r28 = var_r30 + 1;
loop_10:
            if (var_r28 < 0x52) {
                temp_r25 = temp_r27->unk0[var_r28];
                if ((temp_r25 != NULL) && ((u32) (temp_r25->unk0 & 1) != 0) && ((s32) temp_r25->unkC == 0)) {
                    fn_1_7C88(temp_r26, temp_r25);
                }
                var_r28 += 1;
                goto loop_10;
            }
            if ((u32) (temp_r26->unk0 & 2) == 0) {
                var_r28_2 = 0;
loop_22:
                if (var_r28_2 < 0x14) {
                    temp_r25_2 = temp_r27->unk148[var_r28_2];
                    if ((temp_r25_2 != NULL) && ((u32) (temp_r25_2->unk0 & 1) != 0)) {
                        temp_r0 = temp_r25_2->unkC;
                        switch (temp_r0) {          /* irregular */
                        case 0:
                            fn_1_7FD8(temp_r26, temp_r25_2);
                            break;
                        case 1:
                            fn_1_87B8(temp_r26, (M574Mesh *) temp_r25_2);
                            break;
                        }
                    }
                    var_r28_2 += 1;
                    goto loop_22;
                }
            }
        }
        var_r30 += 1;
        goto loop_24;
    }
    var_r30_2 = 0;
loop_30:
    if (var_r30_2 < 0x52) {
        temp_r26_2 = temp_r27->unk0[var_r30_2];
        if ((temp_r26_2 != NULL) && (temp_r26_2->unk14 != NULL)) {
            ((void (*)(void *)) temp_r26_2->unk14)(temp_r26_2->unk10);
        }
        var_r30_2 += 1;
        goto loop_30;
    }
}

s32 fn_1_7C88(M574Hit *a, M574Hit *b) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    Vec *temp_r30;
    Vec *temp_r31;
    Vec *temp_r6;
    Vec *temp_r6_2;
    f32 temp_f27;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;
    f64 temp_f28;
    f64 temp_f28_2;
    f64 temp_f28_3;

    temp_r31 = a->unk18;
    temp_r30 = b->unk18;
    temp_f31 = temp_r31->x - temp_r30->x;
    temp_f30 = temp_r31->y - temp_r30->y;
    if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) > 0.0f) {
        temp_f28 = __frsqrte((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        temp_f28_2 = 0.5 * temp_f28 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f28 * temp_f28)));
        temp_f28_3 = 0.5 * temp_f28_2 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f28_2 * temp_f28_2)));
        sp8 = (f32) ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (0.5 * temp_f28_3 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f28_3 * temp_f28_3)))));
        var_f26 = sp8;
    } else {
        var_f26 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
    }
    temp_f27 = a->unk2C + b->unk2C;
    if (temp_f27 > var_f26) {
        if (0.0f == var_f26) {
            var_f31 = 0.0f;
            var_f30 = -1.0f;
        } else {
            var_f31 = temp_f31 / var_f26;
            var_f30 = temp_f30 / var_f26;
        }
        spC = (f32) ((f64) temp_r31->x + (0.5 * (f64) (temp_r30->x - temp_r31->x)));
        sp10 = (f32) ((f64) temp_r31->y + (0.5 * (f64) (temp_r30->y - temp_r31->y)));
        temp_f29 = (f32) (0.5 * (f64) temp_f27);
        temp_r31->x = spC + (var_f31 * temp_f29);
        temp_r31->y = sp10 + (var_f30 * temp_f29);
        temp_r30->x = spC - (var_f31 * temp_f29);
        temp_r30->y = sp10 - (var_f30 * temp_f29);
        a->unk1C->x = (f32) ((f64) a->unk1C->x + (0.3 * (f64) (var_f31 * temp_f29)));
        temp_r6 = a->unk1C;
        temp_r6->y = (f32) ((f64) temp_r6->y + (0.3 * (f64) (var_f30 * temp_f29)));
        b->unk1C->x = (f32) ((f64) b->unk1C->x + (-0.3 * (f64) (var_f31 * temp_f29)));
        temp_r6_2 = b->unk1C;
        temp_r6_2->y = (f32) ((f64) temp_r6_2->y + (-0.3 * (f64) (var_f30 * temp_f29)));
        return 1;
    }
    return 0;
}

s32 fn_1_7FD8(M574Hit *a, M574Circle *b) {
    f32 sp8;
    Vec *temp_r30;
    Vec *temp_r31;
    Vec *temp_r4;
    f32 temp_f27;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;

    temp_r31 = a->unk18;
    temp_r30 = b->unk1C;
    temp_f31 = temp_r31->x - temp_r30->x;
    temp_f30 = temp_r31->y - temp_r30->y;
    if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) > 0.0f) {
        temp_f29 = __frsqrte((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
        temp_f29_2 = 0.5 * temp_f29 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29 * temp_f29)));
        temp_f29_3 = 0.5 * temp_f29_2 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_2 * temp_f29_2)));
        sp8 = (f32) ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (0.5 * temp_f29_3 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_3 * temp_f29_3)))));
        var_f26 = sp8;
    } else {
        var_f26 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
    }
    temp_f27 = a->unk2C + b->unk20;
    if (temp_f27 > var_f26) {
        if ((void *) b->unk18 != NULL) {
            ((s32 (*)(M574Circle *, M574Hit *)) b->unk18)(b, a);
        }
        if (0.0f == var_f26) {
            var_f31 = 0.0f;
            var_f30 = -1.0f;
        } else {
            var_f31 = temp_f31 / var_f26;
            var_f30 = temp_f30 / var_f26;
        }
        temp_r31->x = temp_r30->x + (var_f31 * temp_f27);
        temp_r31->y = temp_r30->y + (var_f30 * temp_f27);
        a->unk1C->x = (f32) ((f64) a->unk1C->x + (100.0 * (0.5 * (f64) var_f31)));
        temp_r4 = a->unk1C;
        temp_r4->y = (f32) ((f64) temp_r4->y + (100.0 * (0.5 * (f64) var_f30)));
        return 1;
    }
    return 0;
}

s32 fn_1_82AC(M574Hit *ball, M574Mesh *mesh, M574Line *lines, f32 *prev) {
    Vec sp10;
    f32 spC;
    f32 sp8;
    M574Line *var_r31;
    Vec *temp_r30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f24;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f25;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r23;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;

    var_r31 = lines;
    var_r23 = 0;
    temp_r30 = ball->unk18;
    temp_f28 = ball->unk2C;
    var_r24 = 0;
loop_37:
    if (var_r24 < (s32) mesh->unk1C) {
        temp_f29 = var_r31->unk24 + ((var_r31->unk18 * prev[0]) + (var_r31->unk1C * prev[1]));
        if (!(temp_f29 < 0.0f) && ((temp_f30 = var_r31->unk24 + ((var_r31->unk18 * temp_r30->x) + (var_r31->unk1C * temp_r30->y)), (((var_r31->unk24 + ((var_r31->unk18 * (temp_r30->x - (var_r31->unk18 * temp_f28))) + (var_r31->unk1C * (temp_r30->y - (var_r31->unk1C * temp_f28))))) >= 0.0f) == 0)) || !(temp_f30 >= 0.0f))) {
            temp_f30_2 = -temp_f30;
            temp_f31 = temp_f29 + temp_f30_2;
            if (temp_f31 != 0.0f) {
                sp10.x = temp_r30->x + ((temp_f30_2 * (prev[0] - temp_r30->x)) / temp_f31);
                sp10.y = temp_r30->y + ((temp_f30_2 * (prev[1] - temp_r30->y)) / temp_f31);
                if (!((((sp10.x - var_r31->unk0) * (sp10.x - var_r31->unkC)) + ((sp10.y - var_r31->unk4) * (sp10.y - var_r31->unk10))) > 0.0f)) {
                    temp_f0 = (f32) ((f64) temp_r30->x + (100.0 * (3.0 * (f64) var_r31->unk18)));
                    sp10.x = temp_f0;
                    temp_f0_2 = (f32) ((f64) temp_r30->y + (100.0 * (3.0 * (f64) var_r31->unk1C)));
                    sp10.y = temp_f0_2;
                    temp_f31_2 = var_r31->unk24 + ((var_r31->unk18 * temp_f0) + (var_r31->unk1C * temp_f0_2)) + temp_f30_2;
                    if ((temp_f31_2 != 0.0f) && ((temp_r30->x += ((temp_f30_2 * (sp10.x - temp_r30->x)) / temp_f31_2) + (var_r31->unk18 * temp_f28), temp_r30->y += ((temp_f30_2 * (sp10.y - temp_r30->y)) / temp_f31_2) + (var_r31->unk1C * temp_f28), var_r23 = 1, (((void *) mesh->unk18 == NULL) != 0)) || (mesh->unk38 = var_r31, ((((s32 (*)(M574Mesh *, M574Hit *)) mesh->unk18)(mesh, ball) == 0) != 0)))) {
                        var_f25 = VECMag(ball->unk1C);
                        if (var_f25 > 100.00000521540642f) {
                            var_f25 = 100.00001f;
                        }
                        Mp5VecReflect(ball->unk1C, (Vec *) &var_r31->unk18, &sp10);
                        if (!isnan(sp10.x)) {
                            if (!isnan(sp10.y)) {
                                temp_f24 = (f32) (0.8 * (f64) var_f25);
                                ball->unk1C->x = sp10.x * temp_f24;
                                ball->unk1C->y = sp10.y * temp_f24;
                            }
                        }
                    }
                }
            }
        }
        var_r24 += 1;
        var_r31++;
        goto loop_37;
    }
    return var_r23;
}

s32 fn_1_87B8(M574Hit *ball, M574Mesh *mesh) {
    f32 spC[3]; // the previous position as a Vec
    f32 sp8;
    M574Line *var_r30;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f28;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    s32 var_r27;
    s32 var_r28;

    if ((u32) mesh->unk4 == 6U) {
        if (ball->unk18->x < 0.0f) {
            var_r27 = 0;
        } else {
            var_r27 = 1;
        }
        if ((s32) ((s32) mesh->unk8 >> 1) == var_r27) {
            var_r30 = mesh->unk20;
            spC[0] = ball->unk20;
            spC[1] = ball->unk24;
            spC[2] = 0.0f;
            var_r28 = 0;
loop_8:
            if (var_r28 < (s32) mesh->unk1C) {
                if (!((var_r30->unk24 + ((var_r30->unk18 * spC[0]) + (var_r30->unk1C * spC[1]))) < 0.0f)) {
                    var_r28 += 1;
                    var_r30++;
                    goto loop_8;
                }
            }
            if (var_r28 < (s32) mesh->unk1C) {
                temp_f31 = ((var_r30->unk0 + var_r30->unkC) * 0.5f) - spC[0];
                temp_f30 = ((var_r30->unk4 + var_r30->unk10) * 0.5f) - spC[1];
                if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) > 0.0f) {
                    temp_f29 = __frsqrte((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
                    temp_f29_2 = 0.5 * temp_f29 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29 * temp_f29)));
                    temp_f29_3 = 0.5 * temp_f29_2 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_2 * temp_f29_2)));
                    sp8 = (f32) ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (0.5 * temp_f29_3 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_3 * temp_f29_3)))));
                    var_f28 = sp8;
                } else {
                    var_f28 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
                }
                if (var_f28 < 300.0f) {
                    spC[1] = (f32) ((f64) spC[1] + 40.0);
                    if (fn_1_82AC(ball, mesh, mesh->unk20, spC) == 0) {
                        return fn_1_82AC(ball, mesh, mesh->unk24, spC);
                    }
                    return 1;
                }
                goto block_17;
            }
            goto block_17;
        }
        goto block_17;
    }
block_17:
    return fn_1_82AC(ball, mesh, mesh->unk20, &ball->unk20);
}

s32 fn_1_8AD0(M574Hit *hit) {
    s32 i;
    M574Reg *reg = lbl_1_bss_60->data;

    for (i = 0; i < 0x52; i++) {
        if (reg->unk0[i] == NULL) {
            reg->unk0[i] = hit;
            return i;
        }
    }
    return -1;
}

s32 fn_1_8B48(M574Circle *hit) {
    s32 i;
    M574Reg *reg = lbl_1_bss_60->data;

    for (i = 0; i < 0x14; i++) {
        if (reg->unk148[i] == NULL) {
            reg->unk148[i] = hit;
            return i + 0x52;
        }
    }
    return -1;
}



void fn_1_8C94(M574Mesh *mesh, HSFOBJECT *objs, s32 count) {
    HSFOBJECT *obj;
    HSFTRANSFORM **tp;
    Mtx *mtx;
    M574Seg *seg;
    s32 total = 0;
    s32 i, f, k;

    for (i = 0, obj = objs; i < count; i++, obj++) {
        if (obj->type == 2) {
            HSFFACE *face = obj->mesh.face->data;
            for (f = 0; f < obj->mesh.face->count; f++) {
                if (face[f].type == 3) {
                    total++;
                }
            }
        }
    }
    seg = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Seg), MEMORY_DEFAULT_NUM);
    mesh->unk28 = seg;
    memset(seg, 0, total * sizeof(M574Seg));
    mesh->unk20 = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Line), MEMORY_DEFAULT_NUM);
    memset(mesh->unk20, 0, total * sizeof(M574Line));
    mesh->unk24 = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Line), MEMORY_DEFAULT_NUM);
    memset(mesh->unk24, 0, total * sizeof(M574Line));
    mesh->unk2C = count;
    tp = HuMemDirectMallocNum(HEAP_SYSTEM, count * sizeof(HSFTRANSFORM *), MEMORY_DEFAULT_NUM);
    mesh->unk30 = tp;
    memset(tp, 0, count * sizeof(HSFTRANSFORM *));
    mtx = HuMemDirectMallocNum(HEAP_SYSTEM, count * sizeof(Mtx), MEMORY_DEFAULT_NUM);
    mesh->unk34 = mtx;
    memset(mtx, 0, count * sizeof(Mtx));
    mesh->unk1C = 0;
    for (i = 0, obj = objs; i < count; i++, obj++) {
        if (obj->type == 2) {
            Vec *vtx = obj->mesh.vertex->data;
            HSFFACE *face = obj->mesh.face->data;
            for (f = 0; f < obj->mesh.face->count; f++) {
                if (face[f].type == 3) {
                    for (k = 0; k < 4; k++) {
                        Vec *a = &vtx[face[f].indices[lbl_1_data_5D8[k]][0]];
                        Vec *b = &vtx[face[f].indices[lbl_1_data_5D8[(k + 1) & 3]][0]];
                        if ((a->z > -50.0f) && (b->z > -50.0f)) {
                            seg->unk0 = a->x;
                            seg->unk4 = a->y;
                            seg->unkC = b->x;
                            seg->unk10 = b->y;
                            seg->unk18 = mtx;
                            seg++;
                            mesh->unk1C += 1;
                            break;
                        }
                    }
                }
            }
        }
        *tp++ = &obj->mesh.base;
        mtx++;
    }
}

void fn_1_8F54(M574Mesh *mesh, s16 model) {
    s16 spC;
    M574Mesh *sp8;
    HSFDATA *temp_r31;

    sp8 = mesh;
    spC = model;
    temp_r31 = Hu3DData[spC].hsf;
    fn_1_8C94(mesh, temp_r31->object, (s32) temp_r31->objectNum);
}

void fn_1_8FA8(M574Mesh *mesh, HSFOBJECT *obj) {
    HSFOBJECT *spC;
    M574Mesh *sp8;

    sp8 = mesh;
    spC = obj;
    fn_1_8C94(mesh, obj, 1);
}

void fn_1_8FDC(M574Mesh *mesh) {
    Mtx sp8;
    Mtx sp68;
    Mtx sp38;
    HSFTRANSFORM **var_r30;
    M574Line *var_r31;
    M574Seg *var_r28;
    f32 var_f30;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    f64 temp_f29_4;
    f64 var_f28;
    s32 var_r27;
    s32 var_r27_2;
    Mtx *var_r26;

    var_r30 = mesh->unk30;
    var_r26 = mesh->unk34;
    var_r28 = mesh->unk28;
    var_r31 = mesh->unk24;
    mesh->unk24 = mesh->unk20;
    mesh->unk20 = var_r31;
    var_r27 = 0;
loop_2:
    if (var_r27 < (s32) mesh->unk2C) {
        MTXRotRad(sp38, 0x7A, 0.017453292f * (*var_r30)->rot.z);
        MTXRotRad(sp68, 0x79, 0.017453292f * (*var_r30)->rot.y);
        MTXConcat(sp38, sp68, sp8);
        MTXRotRad(sp38, 0x78, 0.017453292f * (*var_r30)->rot.x);
        MTXConcat(sp8, sp38, sp68);
        MTXTrans(sp38, (*var_r30)->pos.x, (*var_r30)->pos.y, (*var_r30)->pos.z);
        MTXConcat(sp38, sp68, sp8);
        MTXScale(sp38, (*var_r30)->scale.x, (*var_r30)->scale.y, (*var_r30)->scale.z);
        MTXConcat(sp8, sp38, *var_r26);
        var_r30++;
        var_r26++;
        var_r27 += 1;
        goto loop_2;
    }
    var_r27_2 = 0;
loop_14:
    if (var_r27_2 < (s32) mesh->unk1C) {
        MTXMultVec((f32 (*)[4]) var_r28->unk18, (Vec *) var_r28, (Vec *) var_r31);
        MTXMultVec((f32 (*)[4]) var_r28->unk18, (Vec *) &var_r28->unkC, (Vec *) &var_r31->unkC);
        var_f31 = var_r31->unk10 - var_r31->unk4;
        var_f30 = var_r31->unkC - var_r31->unk0;
        if ((f32) (((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) > 0.0f) {
            temp_f29 = __frsqrte(((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30));
            temp_f29_2 = 0.5 * temp_f29 * (3.0 - ((((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) * (temp_f29 * temp_f29)));
            temp_f29_3 = 0.5 * temp_f29_2 * (3.0 - ((((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) * (temp_f29_2 * temp_f29_2)));
            temp_f29_4 = 0.5 * temp_f29_3 * (3.0 - ((((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) * (temp_f29_3 * temp_f29_3)));
            var_f28 = (((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) * (0.5 * temp_f29_4 * (3.0 - ((((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) * (temp_f29_4 * temp_f29_4))));
        } else if (0.0f == (f32) (((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30))) {
            var_f28 = 0.0;
        } else if ((f32) (((f64) var_f31 * (f64) var_f31) + ((f64) var_f30 * (f64) var_f30)) != 0.0f) {
            var_f28 = (f64) NAN;
        } else {
            var_f28 = (f64) HUGE_VAL;
        }
        if (0.0f != (f32) var_f28) {
            var_f31 = (f32) ((f64) var_f31 / var_f28);
            var_f30 = (f32) ((f64) var_f30 / var_f28);
        }
        var_r31->unk18 = (f32) -var_f31;
        var_r31->unk1C = (f32) var_f30;
        var_r31->unk20 = 0.0f;
        var_r31->unk24 = (f32) -((-var_f31 * (f64) var_r31->unk0) + ((f64) var_f30 * (f64) var_r31->unk4));
        var_r31++;
        var_r28++;
        var_r27_2 += 1;
        goto loop_14;
    }
}



static s16 Mp5TeamNo(s16 player)
{
    s16 i, slot = 0;
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].group < GWPlayerCfg[player].group || (GWPlayerCfg[i].group == GWPlayerCfg[player].group && i < player)) {
            slot++;
        }
    }
    return slot / 2;
}

void ObjectSetup(void) {
    Mtx sp38;
    Vec sp14;
    Vec sp8;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    HU3DLIGHT *temp_r31;

    sp2C = lbl_1_rodata_10[0];
    sp30 = lbl_1_rodata_10[1];
    sp34 = lbl_1_rodata_10[2];
    sp20 = lbl_1_rodata_1C[0];
    sp24 = lbl_1_rodata_1C[1];
    sp28 = lbl_1_rodata_1C[2];
    lbl_1_bss_2C = 0;
    lbl_1_bss_20 = 0;
    lbl_1_bss_1E = 0x3C;
    lbl_1_bss_18 = -1;
    lbl_1_bss_34 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_34);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 10000.0f, 1.2f);
    lbl_1_bss_30 = omAddObjEx(lbl_1_bss_34, 0x7FDA, 0U, 0U, -1, omOutView);
    omCameraViewSet(lbl_1_data_0);
    lbl_1_bss_1C = Hu3DGLightCreateV(&lbl_1_data_38, &lbl_1_data_44, &lbl_1_data_5C);
    Hu3DGLightInfinitytSet(lbl_1_bss_1C);
    temp_r31 = &Hu3DGlobalLight[lbl_1_bss_1C];
    temp_r31->type |= 0x8000;
    sp14.z = 0.0f;
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp8.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = lbl_1_data_50.z;
    mtxRot(sp38, lbl_1_data_50.x, lbl_1_data_50.y, 0.0f);
    MTXMultVec(sp38, &sp8, &sp8);
    Hu3DGLightPosAimSetV(lbl_1_bss_1C, &sp8, &sp14);
    Hu3DShadowCreate(80.0f, 20.0f, 5000.0f);
    Hu3DShadowPosSet(&lbl_1_data_60, &lbl_1_data_6C, &lbl_1_data_78);
    Hu3DShadowColSet(0x32U, 0x32U, 0x32U);
    Hu3DShadowSizeSet(0xF0U);
    MgSeqCreate(&lbl_1_data_84);
}

void fn_1_348(s16 mode, s16 frameNo) {
    fn_1_7130(lbl_1_bss_34);
    fn_1_7A48(lbl_1_bss_34);
    fn_1_2028(lbl_1_bss_34);
    fn_1_E98(lbl_1_bss_34);
    fn_1_6650(lbl_1_bss_34);
    MgSeqModeNext();
}

void fn_1_3B8(s16 arg1, s16 frameNo) {
    s32 temp_r0;
    s32 temp_r0_2;

    if (frameNo == 0) {
        lbl_1_bss_28 = 0;
        lbl_1_bss_24 = 0;
    }
    if (((s32) lbl_1_bss_18 == -1) && (frameNo >= 0x12)) {
        lbl_1_bss_18 = HuAudBGMPlay(0x54);
    }
    switch ((s32) lbl_1_bss_28) {                   /* irregular */
    case 0:
        temp_r0 = lbl_1_bss_24 + 1;
        lbl_1_bss_24 = temp_r0;
        if (temp_r0 >= 0x1E) {
            lbl_1_bss_28 += 1;
            omCameraViewMove(&lbl_1_data_0[1], 0x5A, 1);
        case 1:
            if (omCameraViewCheck(1U) != 0) {
                lbl_1_bss_28 += 1;
                lbl_1_bss_24 = 0;
            case 2:
                temp_r0_2 = lbl_1_bss_24 + 1;
                lbl_1_bss_24 = temp_r0_2;
                if (temp_r0_2 >= 0x5A) {
                    lbl_1_bss_28 += 1;
                    MgSeqModeNext();
                }
            }
        }
        return;
    }
}

void fn_1_548(s16 mode, s16 frameNo) {

}

void fn_1_54C(s16 arg1, s16 frameNo) {
    lbl_1_bss_1E = 0x3C - (frameNo / 60);
    if ((s16) lbl_1_bss_1E < 0) {
        lbl_1_bss_1E = 0;
    }
}

void fn_1_5A8(s16 arg1, s16 frameNo) {
    u16 spA;
    s16 sp8;
    s32 temp_r29;
    s32 temp_r30;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 == 0) {
        if ((s32) lbl_1_bss_18 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_18, 0x64);
            lbl_1_bss_18 = -1;
        }
        lbl_1_bss_1E = 0;
        temp_r30 = fn_1_7948(0);
        temp_r29 = fn_1_7948(1);
        var_r31 = 0;
loop_10:
        if (var_r31 < 4) {
            lbl_1_bss_10[var_r31] = -1;
            if (((temp_r30 > temp_r29) && ((s16) lbl_1_bss_8[var_r31] == 0)) || ((temp_r30 < temp_r29) && ((s16) lbl_1_bss_8[var_r31] == 1))) {
                lbl_1_bss_10[var_r31] = lbl_1_bss_0[var_r31];
            }
            var_r31 += 1;
            goto loop_10;
        }
        spA = MgSeqWinnerSet(lbl_1_bss_10[0], lbl_1_bss_10[1], lbl_1_bss_10[2], lbl_1_bss_10[3]);
        lbl_1_bss_20 = fn_1_797C();
    }
}

void fn_1_730(s16 arg1, s16 frameNo) {
    s32 var_r31;

    if (frameNo == 0) {
        var_r31 = 0;
loop_5:
        if ((fn_1_6CC8(0) != 0) || (fn_1_6CC8(1) != 0)) {
            if ((s16) omSysExitReq == 0) {
                var_r31 += 1;
                if (var_r31 <= 0x12C) {
                    HuPrcVSleep();
                    goto loop_5;
                }
            }
        }
    }
    if ((frameNo == 0x5A) && ((s32) lbl_1_bss_20 != 0) && (_CheckFlag(MP5_PRACTICE_FLAG) == 0)) {
        HuAudJinglePlay(0x86);
    }
    if ((((s32) lbl_1_bss_20 == 0) || (_CheckFlag(MP5_PRACTICE_FLAG) != 0)) && (frameNo >= 0x5A)) {
        MgSeqModeNext();
    }
}

void fn_1_82C(s16 arg1, s16 frameNo) {
    s16 sp8;
    s16 temp_r30;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 == 0) {
        var_r31 = 0;
loop_6:
        if (var_r31 < 4) {
            if ((s16) lbl_1_bss_10[var_r31] >= 0) {
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

void fn_1_8E4(s16 mode, s16 frameNo) {

}

void fn_1_8E8(s16 mode, s16 frameNo) {
    fn_1_20C8();
    fn_1_66F0();
    fn_1_1044();
    fn_1_7AD0();
    fn_1_71B8();
}

s16 fn_1_918(void) {
    return lbl_1_bss_1E;
}

s16 fn_1_928(s32 arg0) {
    return lbl_1_bss_10[arg0];
}

u32 fn_1_940(u32 arg0) {
    s32 var_r31;
    s32 var_r31_2;
    u32 var_r30;

    var_r31 = 0;
loop_3:
    if (var_r31 < 4) {
        if ((s16) lbl_1_bss_10[var_r31] < 0) {
            var_r31 += 1;
            goto loop_3;
        }
    }
    if (var_r31 >= 4) {
        return 0U;
    }
    var_r31_2 = 0;
loop_13:
    if (var_r31_2 >= 4) {
        return arg0;
    }
    if (arg0 == (u32) lbl_1_bss_8[var_r31_2]) {
        if ((s16) lbl_1_bss_10[var_r31_2] >= 0) {
            var_r30 = 1;
        } else {
            var_r30 = -1U;
        }
        return var_r30;
    }
    var_r31_2 += 1;
    goto loop_13;
}

void fn_1_9FC(s32 arg0, s16 arg1, s16 arg2) {
    s32 temp_r3;

    temp_r3 = arg0 & 3;
    lbl_1_bss_8[temp_r3] = arg1;
    lbl_1_bss_0[temp_r3] = arg2;
}


void fn_1_AAC(void) {
    s32 temp_r0;

    temp_r0 = lbl_1_bss_2C + 1;
    lbl_1_bss_2C = temp_r0;
    if (temp_r0 == 4) {
        CharLoseVoicePlay(lbl_1_bss_0[0], lbl_1_bss_0[1], lbl_1_bss_0[2], lbl_1_bss_0[3]);
    }
}



void fn_1_C10(s32 sound, Vec *pos) {
    Vec sp10;
    Vec *spC;
    s32 sp8;
    s16 var_r31;

    sp8 = sound;
    spC = pos;
    Hu3D3Dto2D(spC, 1, &sp10);
    var_r31 = (s16) (32.0f + (sp10.x * 0.11111111f));
    if (var_r31 < 0x20) {
        var_r31 = 0x20;
    }
    if (var_r31 > 0x60) {
        var_r31 = 0x60;
    }
    HuAudFXPlayPan(sp8, var_r31);
}

f32 fn_1_CC8(f32 cur, f32 target, f32 rate) {
    f32 spC;
    f32 sp8;
    f32 var_f31;
    f32 var_f31_2;

    sp8 = target;
    spC = rate;
    var_f31_2 = (f32) fmod((f64) (sp8 - cur), 360.0);
    if (var_f31_2 < 0.0f) {
        var_f31_2 += 360.0f;
    }
    if (var_f31_2 > 180.0f) {
        var_f31_2 -= 360.0f;
    }
    var_f31 = (f32) fmod((f64) (cur + (spC * var_f31_2)), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    return var_f31;
}


void fn_1_E98(HUPROCESS *arg0) {
    s32 sp18[4];
    s32 sp10[2];
    s32 sp8[2];
    omObjData *temp_r3;
    s16 temp_r29;
    s32 temp_r29_2;
    s32 temp_r3_2;
    s32 var_r28;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    sp10[0] = lbl_1_rodata_60[0];
    sp10[1] = lbl_1_rodata_60[1];
    sp8[0] = lbl_1_rodata_68[0];
    sp8[1] = lbl_1_rodata_68[1];
    var_r28 = 0;
    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        temp_r29 = Mp5TeamNo(var_r31);
        sp18[var_r31] = (s32) temp_r29;
        if (temp_r29 >= 2) {
            var_r28 = 1;
        } else {
            sp10[temp_r29] += 1;
        }
        var_r31 += 1;
        goto loop_5;
    }
    if ((sp10[0] != 2) || (sp10[1] != 2)) {
        var_r28 = 1;
    }
    if (var_r28 != 0) {
        var_r31_2 = 0;
loop_12:
        if (var_r31_2 < 4) {
            sp18[var_r31_2] = var_r31_2 >> 1;
            var_r31_2 += 1;
            goto loop_12;
        }
    }
    omMakeGroupEx(arg0, 0U, 4U);
    var_r31_3 = 0;
loop_15:
    if (var_r31_3 < 4) {
        temp_r3 = omAddObjEx(arg0, 0x28, 1U, 5U, 0, fn_1_1068);
        lbl_1_bss_38[var_r31_3] = temp_r3;
        temp_r3->work[0] = (u32) var_r31_3;
        temp_r29_2 = sp18[var_r31_3];
        temp_r3->work[1] = (u32) temp_r29_2;
        temp_r3_2 = sp8[temp_r29_2];
        sp8[temp_r29_2] = temp_r3_2 + 1;
        temp_r3->work[2] = (u32) temp_r3_2;
        fn_1_9FC(var_r31_3, (s16) temp_r29_2, GWPlayerCfg[var_r31_3].character);
        var_r31_3 += 1;
        goto loop_15;
    }
}

void fn_1_1044(void) {
    CharModelKill(-1);
}

void fn_1_1068(omObjData *obj) {
    Vec *temp_r4;
    s16 temp_r26;
    s16 temp_r3;
    s32 var_r29;
    u32 temp_r25;
    u32 temp_r27;
    M574Player *temp_r31;

    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M574Player), MEMORY_DEFAULT_NUM);
    temp_r31 = obj->data;
    memset((M574Seg *) temp_r31, 0, 0x78);
    obj->stat |= 0x100;
    temp_r27 = obj->work[0];
    temp_r31->unk0 = temp_r27;
    temp_r31->unk4 = (u32) obj->work[1];
    temp_r25 = obj->work[2];
    temp_r31->unk8 = temp_r25;
    temp_r26 = GWPlayerCfg[temp_r27].character;
    temp_r31->unkC = (s32) temp_r26;
    temp_r31->unk28 = (s32) (GWPlayerCfg[temp_r27].diff & 3);
    temp_r31->unk24 = (s32) GWPlayerCfg[temp_r27].iscom;
    temp_r31->unk2C = 0;
    temp_r3 = CharModelCreate(temp_r26, 2);
    *obj->model = temp_r3;
    Hu3DModelLayerSet(temp_r3, 6);
    Hu3DModelShadowSet(temp_r3);
    CharEffectLayerSet(6);
    var_r29 = 0;
loop_2:
    if (var_r29 < 5) {
        obj->motion[var_r29] = Mp5CharMotionCreateData(temp_r26, lbl_1_data_B0[var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionDataClose(temp_r26);
    temp_r31->unk10 = -1;
    fn_1_1D54(obj, 2U);
    temp_r4 = &lbl_1_data_100[temp_r25];
    temp_r31->unk48.x = (f32) temp_r4->x;
    temp_r31->unk48.y = (f32) temp_r4->y;
    temp_r31->unk48.z = (f32) temp_r4->z;
    temp_r31->unk54.z = 0.0f;
    temp_r31->unk54.y = 0.0f;
    temp_r31->unk54.x = 0.0f;
    Hu3DModelScaleSet(temp_r3, 1.2f, 1.2f, 1.2f);
    temp_r31->unk6C = (f32) lbl_1_data_160[temp_r25];
    temp_r31->unk38 = 0;
    obj->func = fn_1_1264;
}

void fn_1_1264(omObjData *obj) {
    f32 spC;
    f32 sp8;
    s16 temp_r29;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    u32 temp_r0;
    M574Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk20 = 0.0f;
    temp_r0 = temp_r31->unk38;
    switch (temp_r0) {
    case 0:
        temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
        temp_r31->unk44 = 0;
        /* fallthrough */
    case 1:
        temp_r0_2 = temp_r31->unk44 + 1;
        temp_r31->unk44 = temp_r0_2;
        if (!((f32) (f64) temp_r0_2 < 144.0f)) {
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
            temp_r31->unk44 = 0;
            temp_r31->unk3C = 2;
        case 2:
            temp_r31->unk18 = 0x100;
            temp_r0_3 = temp_r31->unk44 + 1;
            temp_r31->unk44 = temp_r0_3;
            if (!((f32) (f64) temp_r0_3 < 12.0f)) {
                temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
                temp_r31->unk44 = 0;
            case 3:
                temp_r0_4 = temp_r31->unk44 + 1;
                temp_r31->unk44 = temp_r0_4;
                if (!((f32) (f64) temp_r0_4 < 12.0f)) {
                    temp_r0_5 = temp_r31->unk3C - 1;
                    temp_r31->unk3C = temp_r0_5;
                    if (temp_r0_5 > 0) {
                        temp_r31->unk38 = (u32) (temp_r31->unk38 - 1);
                        temp_r31->unk44 = 0;
                    } else {
                        temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
                    case 4:
                        if (MgSeqModeGet() == 5) {
                            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
                        case 5:
                            if (MgSeqModeGet() != 5) {
                                temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
                                temp_r31->unk3C = 0;
                                temp_r31->unk70 = 1;
                            } else if ((s32) temp_r31->unk24 != 0) {
                                fn_1_19AC(obj);
                            } else {
                                temp_r29 = GWPlayerCfg[temp_r31->unk0].pad_idx;
                                spC = 0.0f;
                                sp8 = 0.0f;
                                temp_r31->unk18 = (s32) HuPadBtn[temp_r29];
                                temp_r31->unk14 = (s32) HuPadBtnDown[temp_r29];
                            }
                        }
                    }
                }
            }
        }
        break;
    case 6:
        temp_r0_6 = temp_r31->unk3C + 1;
        temp_r31->unk3C = temp_r0_6;
        if (temp_r0_6 >= 0xA) {
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
            fn_1_1D54(obj, 0U);
        case 7:
            if (MgSeqModeGet() == 7) {
                temp_r31->unk38 = 0U;
                obj->func = fn_1_1588;
            }
        }
        break;
    }
    fn_1_1830(obj);
    fn_1_182C();
    VECAdd(&temp_r31->unk48, &temp_r31->unk54, &temp_r31->unk48);
    fn_1_17A0(obj);
    fn_1_1938(obj);
}

void fn_1_1588(omObjData *obj) {
    s32 temp_r0_2;
    s32 temp_r0_3;
    u32 temp_r0;
    M574Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk20 = 0.0f;
    temp_r31->unk54.z = 0.0f;
    temp_r31->unk54.y = 0.0f;
    temp_r31->unk54.x = 0.0f;
    temp_r0 = temp_r31->unk38;
    switch (temp_r0) {
    case 0:
        temp_r31->unk70 = 0;
        temp_r31->unk74 = 0;
        temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
        /* fallthrough */
    case 1:
        fn_1_182C();
        if (MgSeqModeGet() != 7) {
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
            temp_r31->unk3C = 0;
            fn_1_1D54(obj, 1U);
        }
        break;
    case 2:
        fn_1_182C();
        temp_r31->unk6C = fn_1_CC8(temp_r31->unk6C, 0.0f, 0.05f);
        temp_r0_2 = temp_r31->unk3C + 1;
        temp_r31->unk3C = temp_r0_2;
        if (temp_r0_2 >= 0x14) {
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
            temp_r31->unk3C = 0;
            fn_1_1D54(obj, 0U);
        }
        break;
    case 3:
        fn_1_182C();
        temp_r31->unk6C = fn_1_CC8(temp_r31->unk6C, 0.0f, 0.05f);
        temp_r0_3 = temp_r31->unk3C + 1;
        temp_r31->unk3C = temp_r0_3;
        if (temp_r0_3 >= 0x14) {
            if (fn_1_928(temp_r31->unk0) >= 0) {
                fn_1_1D54(obj, 3U);
            } else {
                fn_1_1D54(obj, 4U);
                fn_1_AAC();
            }
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
        }
        break;
    case 5:
        if (fn_1_1E4C(obj) != 0) {
            temp_r31->unk38 = (u32) (temp_r31->unk38 + 1);
        }
        break;
    }
    VECAdd(&temp_r31->unk48, &temp_r31->unk54, &temp_r31->unk48);
    fn_1_17A0(obj);
    fn_1_1938(obj);
}

void fn_1_17A0(omObjData *arg0) {
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk40 = (s32) (temp_r31->unk40 + 1);
    CharModelVoicePanSet((s16) temp_r31->unkC, (s16) lbl_1_data_1AC[temp_r31->unk8]);
    if (((s32) temp_r31->unk74 != 0) && (fn_1_1E4C(arg0) != 0)) {
        temp_r31->unk74 = 0;
    }
}

void fn_1_182C(void) {

}

void fn_1_1830(omObjData *arg0) {
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    if ((u32) (temp_r31->unk18 & 0x100) != 0) {
        fn_1_6478(temp_r31->unk8, 1.0f);
    } else if (temp_r31->unk20 > 0.0f) {
        fn_1_6478(temp_r31->unk8, temp_r31->unk20);
    } else {
        fn_1_6478(temp_r31->unk8, 0.0f);
    }
    if (((s32) temp_r31->unk10 == 2) && (CharMotionShiftIDGet((s16) temp_r31->unkC) < 0)) {
        CharMotionTimeSet((s16) temp_r31->unkC, (f32) (30.0 * (1.0 - fn_1_6568(temp_r31->unk8))));
    }
}

void fn_1_1938(omObjData *arg0) {
    s16 temp_r29;
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r29 = *arg0->model;
    Hu3DModelPosSetV(temp_r29, &temp_r31->unk48);
    Hu3DModelRotSet(temp_r29, 0.0f, temp_r31->unk6C, 0.0f);
}

void fn_1_19AC(omObjData *arg0) {
    Vec sp8;
    Vec *temp_r28;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r3;
    struct _struct_lbl_1_data_1BC_0x18 *temp_r30;
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r30 = &lbl_1_data_1BC[temp_r31->unk28];
    temp_r28 = &lbl_1_data_130[temp_r31->unk8];
    temp_r0 = temp_r31->unk2C;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (!((f32) (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)) > temp_r30->unk14)) {
            temp_r3 = fn_1_6D7C(temp_r31->unk4, temp_r28, 0.0f, 120.0f, temp_r30->unk0);
            if (temp_r3 >= 0) {
                fn_1_70B0(temp_r3, NULL, &sp8);
                if (VECMag(&sp8) > 33.33333507180214f) {
                    temp_r31->unk34 = 1;
                } else {
                    temp_r31->unk34 = 0;
                }
                temp_r31->unk2C = (s32) (temp_r31->unk2C + 1);
                if ((s32) temp_r31->unk34 != 0) {
                    temp_r31->unk30 = (s32) temp_r30->unkC;
                } else {
                    temp_r31->unk30 = (s32) temp_r30->unk4;
                }
                if ((f32) (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)) > temp_r30->unk14) {
                    temp_r31->unk30 = (s32) (temp_r31->unk30 + (s32) (12.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
                }
            case 1:
                temp_r31->unk18 = 0x100;
                temp_r0_2 = temp_r31->unk30 - 1;
                temp_r31->unk30 = temp_r0_2;
                if (temp_r0_2 <= 0) {
                    temp_r31->unk2C = (s32) (temp_r31->unk2C + 1);
                    if ((s32) temp_r31->unk34 != 0) {
                        temp_r31->unk30 = (s32) temp_r30->unk10;
                    } else {
                        temp_r31->unk30 = (s32) temp_r30->unk8;
                    }
                    if ((f32) (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)) > temp_r30->unk14) {
                        temp_r31->unk30 = (s32) (temp_r31->unk30 + (s32) (15.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
                    }
                case 2:
                    temp_r0_3 = temp_r31->unk30 - 1;
                    temp_r31->unk30 = temp_r0_3;
                    if (temp_r0_3 <= 0) {
                        temp_r31->unk2C = 0;
                    }
                }
            }
        }
        return;
    }
}


void fn_1_1D54(omObjData *arg0, u32 arg1) {
    f32 var_f31;
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    if (((u32) temp_r31->unk10 != arg1) && (arg1 < 5U)) {
        if ((s32) temp_r31->unk10 < 0) {
            var_f31 = 0.0f;
        } else {
            var_f31 = 60.0f * lbl_1_data_C4[arg1].unk4;
        }
        temp_r31->unk10 = arg1;
        CharMotionShiftSet((s16) temp_r31->unkC, arg0->motion[lbl_1_data_C4[arg1].unk0], 0.0f, var_f31, lbl_1_data_C4[arg1].unk8);
    }
}

s32 fn_1_1E4C(omObjData *arg0) {
    M574Player *temp_r31;

    temp_r31 = arg0->data;
    if ((CharMotionEndCheck((s16) temp_r31->unkC) != 0) && (CharMotionShiftIDGet((s16) temp_r31->unkC) < 0)) {
        return 1;
    }
    return 0;
}



s32 fn_1_1F28(u32 arg0) {
    s32 var_r30;
    M574Player *temp_r31;

    var_r30 = 0;
loop_5:
    if (var_r30 >= 4) {
        return 0;
    }
    temp_r31 = lbl_1_bss_38[var_r30]->data;
    if (((u32) temp_r31->unk4 == arg0) && ((s32) temp_r31->unk24 == 0)) {
        return 1;
    }
    var_r30 += 1;
    goto loop_5;
}

void fn_1_1F9C(u32 arg0) {
    u32 sp8;
    s32 var_r30;
    M574Player *temp_r31;

    sp8 = arg0;
    var_r30 = 0;
loop_4:
    if (var_r30 < 4) {
        temp_r31 = lbl_1_bss_38[var_r30]->data;
        if ((u32) temp_r31->unk4 == sp8) {
            omVibrate((s16) temp_r31->unk0, 0xF, 6, 6);
        }
        var_r30 += 1;
        goto loop_4;
    }
}

void fn_1_7130(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    M574Seg *temp_r3_2;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x46, 1U, 0U, -1, fn_1_71BC);
    lbl_1_bss_58 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M574Score), MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, sizeof(M574Score));
}

void fn_1_71B8(void) {

}

void fn_1_71BC(omObjData *obj) {
    fn_1_7238(obj);
    fn_1_7468(obj);
    obj->func = fn_1_7200;
}

void fn_1_7200(omObjData *obj) {
    fn_1_7328(obj);
    fn_1_75EC(obj);
}

void fn_1_7238(omObjData *arg0) {
    s16 temp_r3;
    s32 var_r30;
    s32 var_r31;
    void *temp_r25;
    M574Score *temp_r26;
    M574Side *temp_r29;

    temp_r26 = arg0->data;
    temp_r25 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 31), MEMORY_DEFAULT_NUM, HEAP_DATA);
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 30), MEMORY_DEFAULT_NUM, HEAP_DATA));
    *arg0->model = temp_r3;
    Hu3DModelLayerSet(temp_r3, 4);
    var_r30 = 0;
loop_5:
    if (var_r30 < 2) {
        temp_r29 = (M574Side *)((u8 *)temp_r26 + var_r30 * 0x1C);
        var_r31 = 0;
loop_3:
        if (var_r31 < 5) {
            temp_r29->unk10[var_r31] = Hu3DAnimCreate(temp_r25, temp_r3, lbl_1_data_5AC[var_r30][var_r31]);
            Hu3DAnimAttrSet(temp_r29->unk10[var_r31], 1U);
            var_r31 += 1;
            goto loop_3;
        }
        var_r30 += 1;
        goto loop_5;
    }
}

void fn_1_7328(omObjData *arg0) {
    s32 temp_r30;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    M574Score *temp_r23;
    M574Side *temp_r31;

    temp_r23 = arg0->data;
    var_r29 = 0;
loop_18:
    if (var_r29 < 2) {
        temp_r31 = (M574Side *)((u8 *)temp_r23 + var_r29 * 0x1C);
        if ((s32) temp_r31->unk8 != 0) {
            temp_r31->unk8 = (s32) (temp_r31->unk8 - 1);
            if ((s32) (temp_r31->unk8 & 0xF) < 6) {
                var_r25 = 0;
            } else {
                var_r25 = 1;
            }
            var_r26 = var_r25;
            var_r30 = temp_r31->unkC;
        } else {
            var_r26 = 0;
            temp_r30 = temp_r31->unk4;
            if ((s32) (temp_r31->unk0 - temp_r30) > 0x64) {
                var_r24 = 0x28;
            } else {
                var_r24 = 0xA;
            }
            var_r30 = temp_r30 + var_r24;
            if (var_r30 > (s32) temp_r31->unk0) {
                var_r30 = temp_r31->unk0;
            }
            temp_r31->unk4 = var_r30;
        }
        if (var_r30 > 0x1869F) {
            var_r30 = 0x1869F;
        }
        var_r27 = 0x2710;
        var_r28 = 0;
loop_16:
        if (var_r28 < 5) {
            Hu3DAnimBankSet(temp_r31->unk10[var_r28], (s32) (u16) (var_r26 + ((var_r30 / var_r27) * 2)));
            var_r30 %= var_r27;
            var_r27 = (s32) (var_r27 / 10);
            var_r28 += 1;
            goto loop_16;
        }
        var_r29 += 1;
        goto loop_18;
    }
}

void fn_1_7468(omObjData *arg0) {
    MGSCORE *temp_r3_2;
    s16 temp_r3;
    s16 temp_r3_3;
    M574Score *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk38 = 0;
    temp_r31->unk40 = GWMgRecordGet(9);
    temp_r3 = MgScoreWinCreate(0x78, 0x28);
    temp_r31->unk44 = temp_r3;
    MgScoreWinPosSet(temp_r3, lbl_1_data_570.unk0, lbl_1_data_570.unk4);
    temp_r3_2 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 1);
    temp_r31->unk48 = temp_r3_2;
    MgScoreMaxDigitSet(temp_r3_2, 5);
    MgScorePosSet(temp_r3_2, lbl_1_data_570.unk0 - 22.0f, lbl_1_data_570.unk4);
    MgScoreColorSet(temp_r3_2, 0x42U, 0xFFU, 0x7AU);
    MgScoreValueSet(temp_r3_2, (s32) temp_r31->unk40);
    temp_r3_3 = HuSprGrpCreate(1);
    temp_r31->unk46 = temp_r3_3;
    HuSprGrpPosSet(temp_r3_3, lbl_1_data_570.unk0, lbl_1_data_570.unk4);
    HuSprGrpMemberSet(temp_r3_3, 0, HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 69), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x32, 0));
    HuSprPosSet(temp_r3_3, 0, -42.0f, 0.0f);
}

void fn_1_75EC(omObjData *arg0) {
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    M574Score *temp_r31;

    temp_r31 = arg0->data;
    var_f31 = 1.0f;
    temp_r0 = temp_r31->unk38;
    switch (temp_r0) {                              /* irregular */
    case 0:
        break;
    case 1:
        if (MgSeqModeGet() == 7) {
            temp_r31->unk38 = (s32) (temp_r31->unk38 + 1);
        }
        break;
    case 2:
        if (MgSeqFrameNoGet() >= 0x5AU) {
            temp_r31->unk38 = (s32) (temp_r31->unk38 + 1);
            temp_r31->unk3C = 0;
            MgScoreValueSet(temp_r31->unk48, temp_r31->unk40);
        }
        break;
    case 3:
        temp_r0_2 = temp_r31->unk3C + 1;
        temp_r31->unk3C = temp_r0_2;
        var_f31 = (f32) (1.0 + (0.02 * (f64) (f32) temp_r0_2));
        if ((s32) temp_r31->unk3C >= 0xA) {
            temp_r31->unk38 = (s32) (temp_r31->unk38 + 1);
            temp_r31->unk3C = 0;
        }
        break;
    case 4:
        temp_r0_3 = temp_r31->unk3C + 1;
        temp_r31->unk3C = temp_r0_3;
        var_f31 = (f32) (1.2 - (0.04 * (f64) (f32) temp_r0_3));
        if ((s32) temp_r31->unk3C >= 5) {
            temp_r31->unk38 = (s32) (temp_r31->unk38 - 1);
            temp_r31->unk3C = 0;
        }
        break;
    }
    if ((s32) temp_r31->unk38 != 0) {
        MgScoreDigitScaleSet(temp_r31->unk48, var_f31, var_f31);
        HuSprScaleSet(temp_r31->unk46, 0, var_f31, var_f31);
    }
}

void fn_1_77D4(s32 team, s32 prize) {
    s32 spC;
    s32 sp8;
    s32 *temp_r30;
    s32 var_r31;

    sp8 = team;
    spC = prize;
    if (MgSeqModeGet() == 5) {
        temp_r30 = (s32 *)((u8 *)lbl_1_bss_58->data + sp8 * 0x1C);
        var_r31 = lbl_1_data_578[spC] + *temp_r30;
        if (var_r31 > 0x1869F) {
            var_r31 = 0x1869F;
        }
        *temp_r30 = var_r31;
    }
}

void fn_1_7874(s32 team, s32 prize) {
    s32 *temp_r29;
    s32 *temp_r3;
    s32 var_r31;
    M574Side *temp_r30;

    if (MgSeqModeGet() == 5) {
        temp_r30 = (M574Side *)((u8 *)lbl_1_bss_58->data + team * 0x1C);
        temp_r3 = &lbl_1_data_578[prize];
        temp_r30->unkC = (s32) *temp_r3;
        temp_r30->unk8 = 0x3C;
        if (MgSeqModeGet() == 5) {
            temp_r29 = (s32 *)((u8 *)lbl_1_bss_58->data + team * 0x1C);
            var_r31 = lbl_1_data_578[prize] + *temp_r29;
            if (var_r31 > 0x1869F) {
                var_r31 = 0x1869F;
            }
            *temp_r29 = var_r31;
        }
    }
}

s32 fn_1_7948(s32 arg0) {
    return ((M574Score *)lbl_1_bss_58->data)->unk0[arg0].unk0;
}

s32 fn_1_797C(void) {
    s32 var_r29;
    s32 var_r30;
    M574Score *temp_r31;

    temp_r31 = lbl_1_bss_58->data;
    var_r29 = 0;
    var_r30 = 0;
loop_6:
    if (var_r30 < 2) {
        if ((fn_1_940((u32) var_r30) != -1) && (fn_1_1F28((u32) var_r30) != 0) && ((s32) temp_r31->unk0[var_r30].unk0 > var_r29)) {
            var_r29 = temp_r31->unk0[var_r30].unk0;
        }
        var_r30 += 1;
        goto loop_6;
    }
    if (var_r29 > (s32) temp_r31->unk40) {
        MgSeqRecordSet(var_r29);
        GWMgRecordSet(9, (u32) var_r29);
        temp_r31->unk40 = var_r29;
        temp_r31->unk38 = 1;
        return 1;
    }
    return 0;
}

void fn_1_2028(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    M574Seg *temp_r3_2;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x14, 0x21U, 3U, -1, fn_1_20CC);
    lbl_1_bss_48 = temp_r3;
    temp_r3->stat |= 0x100;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M574Stage), MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, sizeof(M574Stage));
    temp_r3->work[0] = 0;
}

void fn_1_20C8(void) {

}

void fn_1_20CC(omObjData *obj) {
    M574Mesh *temp_r29;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    M574Stage *temp_r28;

    temp_r28 = obj->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 0), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[0] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DModelLayerSet(temp_r3, 3);
    Hu3DModelShadowMapSet(temp_r3);
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 1), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[1] = temp_r3_2;
    Hu3DModelAttrSet(temp_r3_2, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_2, 3);
    temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 2), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[2] = temp_r3_3;
    Hu3DModelAttrSet(temp_r3_3, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_3, 7);
    temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 3), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[3] = temp_r3_4;
    Hu3DModelAttrSet(temp_r3_4, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_4, 7);
    temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 6), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[4] = temp_r3_5;
    Hu3DModelAttrSet(temp_r3_5, 1U);
    temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[5] = temp_r3_6;
    Hu3DModelAttrSet(temp_r3_6, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_6, 3);
    temp_r3_7 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 22), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[6] = temp_r3_7;
    Hu3DModelAttrSet(temp_r3_7, 1U);
    temp_r29 = &temp_r28->unkF60;
    temp_r28->unkF60.unk0 = 1;
    temp_r29->unk4 = 5;
    temp_r29->unk8 = 0;
    temp_r29->unkC = 1;
    temp_r29->unk10 = obj;
    temp_r29->unk14 = NULL;
    temp_r29->unk18 = NULL;
    fn_1_8F54(temp_r29, temp_r3_7);
    fn_1_8FDC(temp_r29);
    fn_1_8B48((M574Circle *) temp_r29);
    fn_1_2928(obj);
    fn_1_2F8C(obj);
    fn_1_3374(obj);
    fn_1_383C(obj);
    fn_1_448C(obj);
    fn_1_4D28(obj);
    fn_1_5750(obj);
    fn_1_5E5C(obj);
    fn_1_6168(obj);
    Hu3DZClearLayerSet(5);
    obj->func = fn_1_2364;
}

void fn_1_2364(omObjData *obj) {
    fn_1_2B88(obj);
    fn_1_3154(obj);
    fn_1_34B0(obj);
    fn_1_3A1C(obj);
    fn_1_4660(obj);
    fn_1_4EE8(obj);
    fn_1_5934(obj);
    fn_1_5ECC(obj);
    fn_1_629C();
    fn_1_26F4(obj);
    obj->work[0] += 1;
}




void fn_1_26F4(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    f64 var_f31;
    s32 temp_r0;
    s32 temp_r4;
    s32 var_r28;
    s32 var_r31;
    M574Prop *temp_r29;
    M574Stage *temp_r30;

    temp_r30 = arg0->data;
    if ((MgSeqModeGet() == 5) && (fn_1_918() > 1)) {
        var_r31 = 0;
loop_14:
        if (var_r31 < 2) {
            if (fn_1_6CC8(var_r31) != 0) {
                temp_r30->unk0[var_r31] = 0x78;
            } else {
                                temp_r0 = temp_r30->unk0[var_r31] - 1;
                temp_r30->unk0[var_r31] = temp_r0;
                if (temp_r0 < 0) {
                    temp_r29 = &((M574Stage *)arg0->data)->unk14;
                    sp8.x = temp_r29->unk10.x;
                    sp8.y = (f32) ((f64) temp_r29->unk10.y - 150.0);
                    sp8.z = 300.0f;
                    sp14.z = 80.0f;
                    var_r28 = 0;
loop_11:
                    if (var_r28 < 1) {
                        if (var_r31 == 0) {
                            var_f31 = 240.0f;
                        } else {
                            var_f31 = 120.0f;
                        }
                        temp_f31 = (f32) (var_f31 + (10.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
                        sp14.x = (f32) (100.0 * (0.2 * sin((3.141592653589793 * (f64) temp_f31) / 180.0)));
                        sp14.y = (f32) (100.0 * (0.2 * cos((3.141592653589793 * (f64) temp_f31) / 180.0)));
                        fn_1_6C2C(&sp8, &sp14);
                        var_r28 += 1;
                        goto loop_11;
                    }
                    temp_r30->unk0[var_r31] = 0x78;
                }
            }
            var_r31 += 1;
            goto loop_14;
        }
    }
}

void fn_1_2928(omObjData *arg0) {
    HSFOBJECT *temp_r3_4;
    M574Mesh *temp_r30;
    f32 temp_f0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s32 var_r31;
    M574Stage *temp_r26;

    temp_r26 = arg0->data;
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_220[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31 + 9] = temp_r3;
        Hu3DModelLayerSet(temp_r3, 4);
        Hu3DModelShadowSet(temp_r3);
        Hu3DModelPosSetV(temp_r3, &lbl_1_data_250[var_r31]);
        temp_f0 = lbl_1_data_280[var_r31];
        ((M574Stage *)temp_r26)->unkA8[var_r31].unkC = temp_f0;
        ((M574Stage *)temp_r26)->unkA8[var_r31].unk8 = temp_f0;
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_240[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31 + 0x11] = temp_r3_2;
        Hu3DModelLayerSet(temp_r3_2, 6);
        Hu3DModelShadowSet(temp_r3_2);
        Hu3DModelAttrSet(temp_r3_2, 0x40000002U);
        Hu3DMotionTimeSet(temp_r3_2, 0.0f);
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_230[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31 + 0xD] = temp_r3_3;
        Hu3DModelAttrSet(temp_r3_3, 1U);
        temp_r3_4 = Hu3DModelObjPtrGet(temp_r3_3, lbl_1_data_290[var_r31]);
        if (temp_r3_4 != NULL) {
            temp_r3_4->mesh.base.pos.x = lbl_1_data_250[var_r31].x;
            temp_r3_4->mesh.base.pos.y = lbl_1_data_250[var_r31].y;
            temp_r3_4->mesh.base.pos.z = lbl_1_data_250[var_r31].z;
        }
        temp_r30 = &((M574Stage *)temp_r26)->unkA8[var_r31].unk14;
        temp_r30->unk0 = 1;
        temp_r30->unk4 = 6;
        temp_r30->unk8 = var_r31;
        temp_r30->unkC = 1;
        temp_r30->unk10 = arg0;
        temp_r30->unk14 = NULL;
        temp_r30->unk18 = fn_1_2D88;
        fn_1_8F54(temp_r30, temp_r3_3);
        fn_1_8FDC(temp_r30);
        fn_1_8FDC(temp_r30);
        fn_1_8B48((M574Circle *) temp_r30);
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_2B88(omObjData *arg0) {
    HSFOBJECT *temp_r3;
    s16 temp_r28;
    s32 var_r30;
    M574Stage *temp_r26;
    M574Flipper *temp_r31;

    temp_r26 = arg0->data;
    var_r30 = 0;
loop_11:
    if (var_r30 < 4) {
        temp_r31 = &temp_r26->unkA8[var_r30];
        temp_r31->unk8 = (f32) ((f64) temp_r31->unk8 + (0.5 * (f64) (temp_r31->unkC - temp_r31->unk8)));
        temp_r31->unk4 = (f32) (temp_r31->unkC - temp_r31->unk8);
        if ((s32) (var_r30 & 1) != 0) {
            temp_r31->unk4 = (f32) -temp_r31->unk4;
        }
        if (temp_r31->unk4 < 0.0f) {
            temp_r31->unk4 = 0.0f;
        }
        temp_r31->unk4 = (f32) ((f64) temp_r31->unk4 / 60.0);
        Hu3DModelRotSet(arg0->model[var_r30 + 9], 0.0f, 0.0f, temp_r31->unk8);
        temp_r28 = arg0->model[var_r30 + 0x11];
        Hu3DMotionTimeSet(temp_r28, (f32) (30.0 * (1.0 - fn_1_6568(var_r30))));
        if (((s32) temp_r31->unk10 == 0) && (MgSeqModeGet() == 6)) {
            temp_r31->unk10 = 1;
            Hu3DModelLayerSet(temp_r28, 3);
            Hu3DModelLayerSet(arg0->model[2], 3);
        }
        temp_r3 = Hu3DModelObjPtrGet(arg0->model[var_r30 + 0xD], lbl_1_data_290[var_r30]);
        if (temp_r3 != NULL) {
            temp_r3->mesh.base.rot.z = temp_r31->unk8;
        }
        fn_1_8FDC(&temp_r31->unk14);
        var_r30 += 1;
        goto loop_11;
    }
}

s32 fn_1_2D88(M574Mesh *mesh, M574Hit *ball) {
    Vec *temp_r6;
    f32 var_f31;
    s32 temp_r31;

    temp_r31 = mesh->unk8;
    if ((mesh->unk38->unk1C > 0.3f) && (((M574Stage *)lbl_1_bss_48->data)->unkA8[temp_r31].unk4 >= 0.1f)) {
        var_f31 = (f32) (100.0 * ((f64) (ball->unk18->x - lbl_1_data_250[temp_r31].x) * 0.5));
        if ((s32) (temp_r31 & 1) != 0) {
            var_f31 = -var_f31;
        }
        if (var_f31 > 0.1f) {
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            ball->unk1C->x = (f32) ((f64) ball->unk1C->x - (0.01666666753590107 * (100.0 * (50.0 * (f64) mesh->unk38->unk18)) * (f64) var_f31));
            temp_r6 = ball->unk1C;
            temp_r6->y = (f32) ((f64) temp_r6->y - (0.01666666753590107 * (100.0 * (50.0 * (f64) mesh->unk38->unk1C)) * (f64) var_f31));
            if ((s32) (temp_r31 & 1) != 0) {
                var_f31 = -var_f31;
            }
            ball->unk1C->x = (f32) ((f64) ball->unk1C->x + (100.0 * (0.1 * (f64) var_f31)));
        }
    }
    return 0;
}

void fn_1_2F8C(omObjData *arg0) {
    M574Stage *spC;
    M574Stage *sp8;
    HSFOBJECT *temp_r3_2;
    HSFOBJECT *temp_r3_3;
    M574Circle *temp_r31;
    s16 temp_r3;
    s32 var_r29;
    M574Stage *temp_r24;
    M574Prop *temp_r28;

    temp_r24 = arg0->data;
    var_r29 = 0;
loop_6:
    if (var_r29 < 6) {
        temp_r28 = &temp_r24->unkB20[var_r29];
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_42C[var_r29 + 1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r29 + 0x15] = temp_r3;
        Hu3DModelLayerSet(temp_r3, 4);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        Hu3DMotionStartEndSet(temp_r3, 0.0f, 60.0f);
        spC = arg0->data;
        temp_r3_2 = Hu3DModelObjPtrGet(arg0->model[4], lbl_1_data_3D0[var_r29 + 1]);
        if (temp_r3_2 != NULL) {
            Hu3DModelPosSet(temp_r3, temp_r3_2->mesh.base.pos.x, temp_r3_2->mesh.base.pos.y, temp_r3_2->mesh.base.pos.z);
        }
        sp8 = arg0->data;
        temp_r3_3 = Hu3DModelObjPtrGet(arg0->model[4], lbl_1_data_3D0[var_r29 + 1]);
        if (temp_r3_3 != NULL) {
            temp_r28->unk10.x = (f32) temp_r3_3->mesh.base.pos.x;
            temp_r28->unk10.y = (f32) temp_r3_3->mesh.base.pos.y;
            temp_r28->unk10.z = (f32) temp_r3_3->mesh.base.pos.z;
        }
        temp_r31 = &temp_r28->unk4C;
        temp_r28->unk4C.unk0 = 1;
        temp_r31->unk4 = 3;
        temp_r31->unk8 = var_r29;
        temp_r31->unkC = 0;
        temp_r31->unk10 = arg0;
        temp_r31->unk14 = NULL;
        temp_r31->unk18 = fn_1_3240;
        temp_r31->unk1C = &temp_r28->unk10;
        temp_r31->unk20 = 80.0f;
        fn_1_8B48(temp_r31);
        var_r29 += 1;
        goto loop_6;
    }
}

void fn_1_3154(omObjData *arg0) {
    Vec sp8;
    s16 temp_r30;
    s32 var_r31;
    M574Stage *temp_r27;
    M574Prop *temp_r29;

    temp_r27 = arg0->data;
    var_r31 = 0;
loop_4:
    if (var_r31 < 6) {
        temp_r29 = &temp_r27->unkB20[var_r31];
        temp_r30 = arg0->model[var_r31 + 0x15];
        if (Hu3DMotionEndCheck(temp_r30) != 0) {
            Hu3DModelAttrSet(temp_r30, 0x40000001U);
            Hu3DMotionStartEndSet(temp_r30, 0.0f, 60.0f);
            Hu3DMotionTimeSet(temp_r30, 0.0f);
        }
        VECScale(&temp_r29->unk1C, &temp_r29->unk1C, 0.2f);
        VECAdd(&temp_r29->unk10, &temp_r29->unk1C, &sp8);
        Hu3DModelPosSetV(temp_r30, &sp8);
        var_r31 += 1;
        goto loop_4;
    }
}

s32 fn_1_3240(M574Circle *self, M574Hit *ball) {
    s16 temp_r28;
    s32 temp_r30;
    M574Prop *temp_r27;

    temp_r30 = self->unk8;
    temp_r27 = &((M574Stage *)lbl_1_bss_48->data)->unkB20[temp_r30];
    temp_r28 = lbl_1_bss_48->model[temp_r30 + 0x15];
    Hu3DModelAttrReset(temp_r28, 0x40000001U);
    Hu3DMotionStartEndSet(temp_r28, 60.0f, Hu3DMotionMaxTimeGet(temp_r28));
    Hu3DMotionTimeSet(temp_r28, 60.0f);
    VECNormalize(ball->unk1C, &temp_r27->unk1C);
    VECScale(&temp_r27->unk1C, &temp_r27->unk1C, 50.0f);
    fn_1_77D4(lbl_1_data_450[temp_r30], lbl_1_data_468[temp_r30]);
    if (ball->unk18->x < 0.0f) {
        fn_1_C10(0x918, ball->unk18);
    } else {
        fn_1_C10(0x919, ball->unk18);
    }
    return 0;
}

void fn_1_3374(omObjData *arg0) {
    M574Stage *sp8;
    HSFOBJECT *temp_r3_2;
    s16 temp_r3;
    s32 var_r31;
    M574Stage *temp_r26;

    temp_r26 = arg0->data;
    var_r31 = 0;
loop_4:
    if (var_r31 < 2) {
        ((M574Stage *)temp_r26)->unk2A0[var_r31].unk0 = 0;
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_42C[var_r31 + 7], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31 + 0x1B] = temp_r3;
        Hu3DModelAttrSet(temp_r3, 0x40000002U);
        Hu3DModelAttrSet(temp_r3, 0x40000080U);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        Hu3DMotionShapeTimeSet(temp_r3, 0.0f);
        Hu3DModelLayerSet(temp_r3, 4);
        sp8 = arg0->data;
        temp_r3_2 = Hu3DModelObjPtrGet(arg0->model[4], lbl_1_data_3D0[var_r31 + 7]);
        if (temp_r3_2 != NULL) {
            Hu3DModelPosSet(temp_r3, temp_r3_2->mesh.base.pos.x, temp_r3_2->mesh.base.pos.y, temp_r3_2->mesh.base.pos.z);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_34B0(omObjData *arg0) {
    s16 temp_r28;
    s32 temp_r0;
    s32 var_r29;
    M574Stage *temp_r26;
    M574Kicker *temp_r31;
    M574Hit *var_r30;

    temp_r26 = arg0->data;
    var_r29 = 0;
loop_23:
    if (var_r29 < 2) {
        temp_r31 = &temp_r26->unk2A0[var_r29];
        temp_r28 = arg0->model[var_r29 + 0x1B];
        var_r30 = temp_r31->unk48;
        temp_r0 = temp_r31->unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            break;
        case 1:
            temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            Hu3DModelAttrReset(temp_r28, 0x40000002U);
            Hu3DModelAttrReset(temp_r28, 0x40000080U);
            Hu3DMotionTimeSet(temp_r28, 0.0f);
            Hu3DMotionShapeTimeSet(temp_r28, 0.0f);
            if (var_r29 == 0) {
                HuAudFXPlay(0x927);
            } else {
                HuAudFXPlay(0x928);
            }
            /* fallthrough */
        case 2:
            temp_r31->unk34 = (f32) ((f64) temp_r31->unk34 - 20.0);
            if (!(Hu3DMotionTimeGet(temp_r28) < 3.0f)) {
                temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                temp_r31->unk34 = 0.0f;
            case 3:
                if (!(Hu3DMotionTimeGet(temp_r28) < 19.0f)) {
                    temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                    var_r30->unk1C->x = 0.0f;
                    var_r30->unk1C->y = 333.33334f;
                    var_r30->unk0 = (s32) (var_r30->unk0 & 0xFFFFFFFD);
                    var_r30 = NULL;
                    temp_r31->unk48 = NULL;
                    if (var_r29 == 0) {
                        HuAudFXPlay(0x929);
                    } else {
                        HuAudFXPlay(0x92A);
                    }
                case 4:
                    if (!(Hu3DMotionTimeGet(temp_r28) < 22.0f)) {
                        temp_r31->unk0 = 0;
                    }
                }
            }
            break;
        }
        if (var_r30 != NULL) {
            var_r30->unk1C->x = 0.0f;
            var_r30->unk1C->y = 0.0f;
            var_r30->unk18->x = (f32) temp_r31->unk10;
            var_r30->unk18->y = (f32) (temp_r31->unk14 + temp_r31->unk34);
        }
        var_r29 += 1;
        goto loop_23;
    }
}


void fn_1_383C(omObjData *arg0) {
    f32 temp_f0;
    s16 temp_r23;
    s16 temp_r3;
    s32 temp_r24;
    s32 var_r29;
    s32 var_r30;
    M574Stage *temp_r26;
    M574Slot *temp_r31;

    temp_r26 = arg0->data;
    temp_r23 = arg0->model[5];
    var_r29 = 0;
loop_5:
    if (var_r29 < 2) {
        temp_r31 = &temp_r26->unk1E8[var_r29];
        temp_r31->unkC = -1;
        var_r30 = 0;
loop_3:
        if (var_r30 < 3) {
            temp_r31->unk50[var_r30] = Hu3DModelObjPtrGet(temp_r23, lbl_1_data_2D8[var_r30 + (var_r29 * 3)]);
            temp_r24 = (s32) (20.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)));
            temp_r31->unk20[var_r30] = temp_r24;
            temp_f0 = 18.0f * (f32) temp_r24;
            temp_r31->unk38[var_r30] = temp_f0;
            temp_r31->unk2C[var_r30] = temp_f0;
            var_r30 += 1;
            goto loop_3;
        }
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_314[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r29 + 0x1D] = temp_r3;
        Hu3DModelLayerSet(temp_r3, 4);
        Hu3DModelAttrSet(temp_r3, 0x40000002U);
        Hu3DMotionStartEndSet(temp_r3, 0.0f, 60.0f);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        var_r29 += 1;
        goto loop_5;
    }
}

void fn_1_3A1C(omObjData *arg0) {
    s16 sp8;
    f32 temp_f1;
    f32 var_f31;
    s16 temp_r28;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r24;
    s32 temp_r24_2;
    s32 temp_r29;
    s32 temp_r4;
    s32 var_r20;
    s32 var_r21;
    s32 var_r22;
    s32 var_r23;
    s32 var_r27;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    M574Stage *temp_r19;
    HSFOBJECT *temp_r25;
    M574Slot *temp_r31;

    var_r23 = 0 /* TODO(mp5): uninitialised in the original */;
    temp_r19 = arg0->data;
    sp8 = arg0->model[5];
    var_r27 = 0;
loop_78:
    if (var_r27 < 2) {
        temp_r31 = &temp_r19->unk1E8[var_r27];
        temp_r28 = arg0->model[var_r27 + 0x1D];
        temp_r0 = temp_r31->unk0;
        switch (temp_r0) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            break;
        case 1:                                     /* switch 1 */
            temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            temp_r31->unk4 = 0;
            temp_r31->unk10 = 1;
            var_r30 = 0;
loop_11:
            if (var_r30 < 3) {
                temp_r31->unk44[var_r30] = (f32) (4.0 + (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)));
                temp_r31->unk14[var_r30] = 0;
                var_r30 += 1;
                goto loop_11;
            }
            Hu3DModelAttrReset(temp_r28, 0x40000002U);
            Hu3DModelAttrSet(temp_r28, 0x40000001U);
            Hu3DMotionStartEndSet(temp_r28, 0.0f, 60.0f);
            Hu3DMotionTimeSet(temp_r28, 0.0f);
            if (var_r27 == 0) {
                temp_r31->unkC = HuAudFXPlay(0x91F);
            } else {
                temp_r31->unkC = HuAudFXPlay(0x920);
            }
            break;
        case 2:                                     /* switch 1 */
            var_r30_2 = 0;
loop_55:
            if (var_r30_2 < 3) {
                if ((s32) temp_r31->unk14[var_r30_2] == 0) {
                    if (MgSeqModeGet() == 5) {
                        var_r22 = (s32) (60.0 * (3.0 + (0.4 * (f64) var_r30_2)));
                    } else {
                        var_r22 = (s32) (60.0 * (1.0 + (0.4 * (f64) var_r30_2)));
                    }
                    if ((s32) temp_r31->unk4 > var_r22) {
                        temp_r31->unk14[var_r30_2] = 1;
                        var_r29 = (s32) (temp_r31->unk38[var_r30_2] / 18.0f);
                        temp_r31->unk38[var_r30_2] = 18.0f * (f32) var_r29;
                        switch (var_r30_2) {        /* switch 2; irregular */
                        case 0:                     /* switch 2 */
                            var_r23 = 0;
                            break;
                        case 1:                     /* switch 2 */
                            if ((f32) (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)) < 0.5f) {
                                var_r21 = 1;
                            } else {
                                var_r21 = 0;
                            }
                            var_r23 = var_r21;
                            break;
                        case 2:                     /* switch 2 */
                            if ((f32) (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF)) < 0.5f) {
                                var_r20 = 1;
                            } else {
                                var_r20 = 0;
                            }
                            var_r23 = var_r20;
                            break;
                        }
                        if ((var_r30_2 != 0) && (var_r23 != 0)) {
                            temp_r24 = fn_1_4330(temp_r31->unk38[0]);
loop_39:
                            if (var_r29 >= 0x14) {
                                var_r29 = 0;
                            }
                            if ((s32) lbl_1_data_2C4[var_r29] != temp_r24) {
                                var_r29 += 1;
                                goto loop_39;
                            }
                            temp_r31->unk38[var_r30_2] = 18.0f * (f32) var_r29;
                        }
                        if (var_r30_2 == 2) {
                            temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                            temp_r31->unk4 = 0;
                            if (fn_1_918() <= 1) {
                                temp_r24_2 = fn_1_4330(temp_r31->unk38[0]);
loop_47:
                                if (var_r29 >= 0x14) {
                                    var_r29 = 0;
                                }
                                if ((s32) lbl_1_data_2C4[var_r29] == temp_r24_2) {
                                    var_r29 += 1;
                                    goto loop_47;
                                }
                                temp_r31->unk38[var_r30_2] = 18.0f * (f32) var_r29;
                            }
                        } else {
                            goto block_54;
                        }
                    } else {
                        if ((f32) (f64) temp_r31->unk4 > (f32) (60.0 * (0.2 * (f64) var_r30_2))) {
                                                        temp_r31->unk38[var_r30_2] = temp_r31->unk38[var_r30_2] + temp_r31->unk44[var_r30_2];
                        }
                        goto block_54;
                    }
                } else {
block_54:
                    var_r30_2 += 1;
                    goto loop_55;
                }
            }
            temp_r31->unk4 = (s32) (temp_r31->unk4 + 1);
            break;
        case 3:                                     /* switch 1 */
            temp_r0_2 = temp_r31->unk4 + 1;
            temp_r31->unk4 = temp_r0_2;
            if (!((f32) (f64) temp_r0_2 < 54.0f)) {
                temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                temp_r31->unk10 = 0;
                if (var_r27 == 0) {
                    HuAudFXStop(temp_r31->unkC);
                } else {
                    HuAudFXStop(temp_r31->unkC);
                }
                temp_r29 = temp_r31->unk20[0];
                if ((temp_r29 == (s32) temp_r31->unk20[1]) && (temp_r29 == (s32) temp_r31->unk20[2])) {
                    fn_1_7874(var_r27, lbl_1_data_2B8[temp_r29]);
                    if (var_r27 == 0) {
                        HuAudFXPlay(0x921);
                    } else {
                        HuAudFXPlay(0x922);
                    }
                    temp_r31->unk8 = 0x3C;
                    Hu3DModelAttrReset(temp_r28, 0x40000002U);
                    Hu3DModelAttrSet(temp_r28, 0x40000001U);
                    Hu3DMotionStartEndSet(temp_r28, 60.0f, Hu3DMotionMaxTimeGet(temp_r28));
                    Hu3DMotionTimeSet(temp_r28, 60.0f);
                } else {
                    temp_r31->unk8 = 0x1E;
                    Hu3DModelAttrSet(temp_r28, 0x40000002U);
                    Hu3DModelAttrReset(temp_r28, 0x40000001U);
                    Hu3DMotionStartEndSet(temp_r28, 0.0f, 60.0f);
                    Hu3DMotionTimeSet(temp_r28, 0.0f);
                }
            }
            break;
        case 4:                                     /* switch 1 */
            temp_r0_3 = temp_r31->unk8 - 1;
            temp_r31->unk8 = temp_r0_3;
            if (temp_r0_3 <= 0) {
                temp_r31->unk0 = 0;
                Hu3DModelAttrSet(temp_r28, 0x40000002U);
                Hu3DModelAttrReset(temp_r28, 0x40000001U);
                Hu3DMotionStartEndSet(temp_r28, 0.0f, 60.0f);
                Hu3DMotionTimeSet(temp_r28, 0.0f);
            }
            break;
        }
        var_r30_3 = 0;
loop_76:
        if (var_r30_3 < 3) {
            var_f31 = (f32) fmod((f64) temp_r31->unk38[var_r30_3], 360.0);
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            temp_r31->unk38[var_r30_3] = var_f31;
            temp_f1 = fn_1_CC8(temp_r31->unk2C[var_r30_3], temp_r31->unk38[var_r30_3], 0.1f);
            temp_r31->unk2C[var_r30_3] = temp_f1;
            temp_r31->unk20[var_r30_3] = fn_1_4330(temp_f1);
            temp_r25 = temp_r31->unk50[var_r30_3];
            if (temp_r25 != NULL) {
                temp_r25->mesh.base.rot.x = (f32) temp_r31->unk2C[var_r30_3];
            }
            var_r30_3 += 1;
            goto loop_76;
        }
        var_r27 += 1;
        goto loop_78;
    }
}

s32 fn_1_4330(f32 angle) {
    f32 var_f1;
    s32 var_r31;

    var_f1 = (f32) ((f64) angle + 9.0);
    if (var_f1 >= 360.0f) {
        var_f1 -= 360.0f;
    }
    if (var_f1 < 0.0f) {
        var_f1 += 360.0f;
    }
    var_r31 = (s32) (var_f1 / 18.0f);
    if (var_r31 < 0) {
        var_r31 = 0x13;
    }
    if (var_r31 >= 0x14) {
        var_r31 = 0;
    }
    return (s32) lbl_1_data_2C4[var_r31];
}



void fn_1_448C(omObjData *arg0) {
    HSFOBJECT *temp_r3_2;
    HSFOBJECT *temp_r3_3;
    M574Mesh *temp_r30;
    s16 temp_r26;
    s16 temp_r3;
    s32 var_r24;
    s32 var_r25;
    s32 var_r29;
    s32 var_r29_2;
    M574Stage *temp_r23;
    M574Prop *temp_r31;

    temp_r23 = arg0->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 23), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[7] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 1U);
    var_r29 = 0;
loop_4:
    if (var_r29 < 4) {
        temp_r3_2 = Hu3DModelObjPtrGet(temp_r3, lbl_1_data_3A8[var_r29]);
        if (temp_r3_2 != NULL) {
            temp_r30 = &temp_r23->unkF9C[var_r29];
            temp_r30->unk0 = 1;
            temp_r30->unk4 = 4;
            temp_r30->unk8 = var_r29;
            temp_r30->unkC = 1;
            temp_r30->unk10 = arg0;
            temp_r30->unk14 = NULL;
            temp_r30->unk18 = fn_1_47DC;
            fn_1_8FA8(temp_r30, temp_r3_2);
            fn_1_8FDC(temp_r30);
            fn_1_8B48((M574Circle *) temp_r30);
        }
        var_r29 += 1;
        goto loop_4;
    }
    temp_r26 = arg0->model[5];
    var_r25 = 0;
    var_r24 = 0;
loop_12:
    if (var_r24 < 2) {
        var_r29_2 = 0;
loop_10:
        if (var_r29_2 < 7) {
            temp_r31 = &temp_r23->unk3B0[var_r25];
            temp_r3_3 = Hu3DModelObjPtrGet(temp_r26, lbl_1_data_31C[var_r25]);
            temp_r31->unk48 = temp_r3_3;
            if (temp_r3_3 != NULL) {
                temp_r31->unk10.x = (f32) temp_r3_3->mesh.base.pos.x;
                temp_r31->unk10.y = (f32) temp_r3_3->mesh.base.pos.y;
                temp_r31->unk10.z = 0.0f;
            }
            temp_r31->unk0 = 0;
            temp_r31->unk34 = 0.0f;
            temp_r31->unk3C.z = 0.0f;
            temp_r31->unk3C.y = 0.0f;
            temp_r31->unk3C.x = 0.0f;
            temp_r31->unk1C.z = 0.0f;
            temp_r31->unk1C.y = 0.0f;
            temp_r31->unk1C.x = 0.0f;
            var_r25 += 1;
            var_r29_2 += 1;
            goto loop_10;
        }
        var_r24 += 1;
        goto loop_12;
    }
}

void fn_1_4660(omObjData *arg0) {
    s32 temp_r0;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    HSFOBJECT *temp_r30;
    M574Prop *temp_r31;

    var_r27 = 0;
    var_r29 = 0;
loop_20:
    if (var_r29 < 2) {
        var_r28 = 0;
loop_18:
        if (var_r28 < 7) {
            temp_r31 = &((M574Stage *)arg0->data)->unk3B0[var_r27];
            temp_r30 = temp_r31->unk48;
            if (temp_r30 != NULL) {
                temp_r0 = temp_r31->unk0;
                switch (temp_r0) {                  /* irregular */
                case 1:
                    temp_r31->unk1C.y = 8.333334f;
                    temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
                    break;
                case 2:
                    temp_r31->unk34 = (f32) (temp_r31->unk34 + temp_r31->unk1C.y);
                    temp_r31->unk1C.y = (f32) ((f64) temp_r31->unk1C.y - 1.666666753590107);
                    if (!(temp_r31->unk34 > 0.0f)) {
                        temp_r31->unk34 = 0.0f;
                        temp_r31->unk0 = 0;
                    }
                    break;
                }
                if (var_r28 < 5) {
                    temp_r31->unk3C.y = (f32) temp_r31->unk34;
                } else if (var_r29 == 0) {
                    temp_r31->unk3C.x = (f32) -temp_r31->unk34;
                } else {
                    temp_r31->unk3C.x = (f32) temp_r31->unk34;
                }
                temp_r30->mesh.base.pos.x = (f32) (temp_r31->unk10.x + temp_r31->unk3C.x);
                temp_r30->mesh.base.pos.y = (f32) (temp_r31->unk10.y + temp_r31->unk3C.y);
                temp_r31->unk4 = (s32) (temp_r31->unk4 + 1);
                var_r27 += 1;
            }
            var_r28 += 1;
            goto loop_18;
        }
        var_r29 += 1;
        goto loop_20;
    }
}

s32 fn_1_47DC(M574Mesh *mesh, M574Hit *ball) {
    f32 sp8;
    M574Line *temp_r28;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f28;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;
    M574Prop *temp_r26;
    s32 temp_r25;
    s32 var_r20;
    s32 var_r21;
    s32 var_r23;
    s32 var_r29;
    s32 var_r29_2;
    M574Stage *temp_r19;
    M574Kicker *temp_r27;

    temp_r19 = lbl_1_bss_48->data;
    temp_r25 = mesh->unk8;
    var_r29 = -1;
    if (temp_r25 < 2) {
        var_r21 = 0;
    } else {
        var_r21 = 1;
    }
    if ((temp_r25 >= 1) && (temp_r25 <= 2)) {
        if (!(mesh->unk38->unk1C > -0.5f)) {
            var_r29 = (s32) ((f64) (mesh->unk38->unk0 - ball->unk18->x) / 100.0);
            if (var_r29 < 0) {
                var_r29 = 0;
            }
            if (var_r29 > 4) {
                var_r29 = 4;
            }
            fn_1_77D4(var_r21, 0xA);
            if (ball->unk18->x < 0.0f) {
                fn_1_C10(0x916, ball->unk18);
            } else {
                fn_1_C10(0x917, ball->unk18);
            }
        }
        goto block_40;
    }
    if (mesh->unk38->unk1C > 0.5f) {
        temp_f31 = ((mesh->unk38->unk0 + mesh->unk38->unkC) * 0.5f) - ball->unk18->x;
        temp_f30 = ((mesh->unk38->unk4 + mesh->unk38->unk10) * 0.5f) - ball->unk18->y;
        if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) > 0.0f) {
            temp_f29 = __frsqrte((temp_f31 * temp_f31) + (temp_f30 * temp_f30));
            temp_f29_2 = 0.5 * temp_f29 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29 * temp_f29)));
            temp_f29_3 = 0.5 * temp_f29_2 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_2 * temp_f29_2)));
            sp8 = (f32) ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (0.5 * temp_f29_3 * (3.0 - ((f64) ((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) * (temp_f29_3 * temp_f29_3)))));
            var_f28 = sp8;
        } else {
            var_f28 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
        }
        if (var_f28 < 300.0f) {
            if ((u32) (ball->unk0 & 2) == 0) {
                if ((s32) mesh->unk8 == 0) {
                    var_r20 = 0;
                } else {
                    var_r20 = 1;
                }
                temp_r27 = &((M574Stage *)lbl_1_bss_48->data)->unk2A0[var_r20];
                if ((s32) temp_r27->unk0 == 0) {
                    temp_r27->unk0 = (s32) (temp_r27->unk0 + 1);
                    temp_r27->unk48 = ball;
                    ball->unk0 |= 2;
                    ball->unk1C->x = 0.0f;
                    ball->unk1C->y = 0.0f;
                    temp_r28 = mesh->unk38;
                    temp_r27->unk10 = (f32) ((f64) temp_r28->unk0 + (0.5 * (f64) (temp_r28->unkC - temp_r28->unk0)));
                    temp_r27->unk14 = (f32) ((f64) temp_r28->unk4 + (0.5 * (f64) (temp_r28->unk10 - temp_r28->unk4)));
                    temp_r27->unk34 = 80.0f;
                    var_r23 = 1;
                } else {
                    goto block_24;
                }
            } else {
block_24:
                var_r23 = 0;
            }
            if (var_r23 != 0) {
                return 1;
            }
            goto block_27;
        }
        goto block_27;
    }
block_27:
    if (((temp_r25 != 0) || !(mesh->unk38->unk18 < 0.5f)) && ((temp_r25 != 3) || !(mesh->unk38->unk18 > -0.5f))) {
        var_f31 = mesh->unk38->unk4;
        if (var_f31 > mesh->unk38->unk10) {
            var_f31 = mesh->unk38->unk10;
        }
        var_r29_2 = (s32) ((f64) (ball->unk18->y - var_f31) / 100.0);
        if (var_r29_2 < 0) {
            var_r29_2 = 0;
        }
        if (var_r29_2 >= 2) {
            var_r29 = -1;
        } else {
            var_r29 = var_r29_2 + 5;
            fn_1_77D4(var_r21, 0xB);
            if (ball->unk18->x < 0.0f) {
                fn_1_C10(0x916, ball->unk18);
            } else {
                fn_1_C10(0x917, ball->unk18);
            }
        }
    }
block_40:
    if (var_r29 >= 0) {
        temp_r26 = &temp_r19->unk3B0[var_r29 + (var_r21 * 7)];
        if (temp_r26->unk0 == 0) {
            temp_r26->unk0 += 1;
            if (var_r29 < 5) {
                fn_1_5680(&temp_r26->unk10);
            }
        }
    }
    return 0;
}

void fn_1_4D28(omObjData *arg0) {
    M574Circle *temp_r31;
    Vec *temp_r4;
    s16 var_r24;
    s16 var_r27;
    s32 var_r26;
    s32 var_r29;
    M574Stage *temp_r25;
    M574Prop *temp_r30;

    var_r24 = 0 /* TODO(mp5): uninitialised in the original */;
    temp_r25 = arg0->data;
    var_r29 = 0;
loop_8:
    if (var_r29 < 2) {
        temp_r30 = &temp_r25->unkE50[var_r29];
        if (var_r29 == 0) {
            var_r24 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 26), MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r27 = var_r24;
            var_r26 = 0;
loop_4:
            if (var_r26 < 3) {
                arg0->motion[var_r26] = Hu3DJointMotion(var_r27, HuDataSelHeapReadNum(lbl_1_data_480[var_r26], MEMORY_DEFAULT_NUM, HEAP_DATA));
                var_r26 += 1;
                goto loop_4;
            }
        } else {
            var_r27 = Hu3DModelLink(var_r24);
        }
        arg0->model[var_r29 + 0x1F] = var_r27;
        Hu3DMotionSet(var_r27, *arg0->motion);
        Hu3DModelAttrSet(var_r27, 0x40000001U);
        Hu3DModelLayerSet(var_r27, 4);
        Hu3DModelShadowSet(var_r27);
        temp_r30->unk0 = 0;
        temp_r4 = &lbl_1_data_48C[var_r29];
        temp_r30->unk10.x = (f32) temp_r4->x;
        temp_r30->unk10.y = (f32) temp_r4->y;
        temp_r30->unk10.z = (f32) temp_r4->z;
        temp_r30->unk3C.z = 1.0f;
        temp_r30->unk3C.y = 1.0f;
        temp_r30->unk3C.x = 1.0f;
        temp_r31 = &temp_r30->unk4C;
        temp_r30->unk4C.unk0 = 1;
        temp_r31->unk4 = 2;
        temp_r31->unk8 = var_r29;
        temp_r31->unkC = 0;
        temp_r31->unk10 = arg0;
        temp_r31->unk14 = NULL;
        temp_r31->unk18 = fn_1_5628;
        temp_r31->unk1C = &temp_r30->unk10;
        temp_r31->unk20 = 40.0f;
        fn_1_8B48(temp_r31);
        var_r29 += 1;
        goto loop_8;
    }
}

void fn_1_4EE8(omObjData *arg0) {
    Vec *temp_r27;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 var_f31;
    f64 var_f29;
    f64 var_f30;
    s16 temp_r28;
    s32 *temp_r26;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 var_r29;
    u32 temp_r0;
    M574Stage *temp_r23;
    M574Prop *temp_r31;

    temp_r23 = arg0->data;
    var_r29 = 0;
loop_46:
    if (var_r29 >= 2) {
        return;
    }
    temp_r31 = &temp_r23->unkE50[var_r29];
    temp_r28 = arg0->model[var_r29 + 0x1F];
    temp_r27 = &lbl_1_data_48C[var_r29];
    var_f31 = 0.0f;
    temp_r0 = temp_r31->unk0;
    switch (temp_r0) {
    case 0:
        temp_r31->unk0 = (u32) (temp_r31->unk0 + 1);
        temp_r31->unk10.x = (f32) ((f64) temp_r31->unk10.x + (150.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
        temp_r31->unk34 = 0.0f;
        Hu3DMotionSet(temp_r28, arg0->motion[0]);
        /* fallthrough */
    case 1:
        if (MgSeqModeGet() == 5) {
            temp_r31->unk0 = (u32) (temp_r31->unk0 + 1);
            if ((s32) (frand() & 1) != 0) {
                var_f30 = -1.0;
            } else {
                var_f30 = 1.0;
            }
            temp_r31->unk34 = (f32) var_f30;
            Hu3DMotionShiftSet(temp_r28, arg0->motion[1], 0.0f, 12.0f, 0x40000001U);
        case 2:
            if (MgSeqModeGet() != 5) {
                temp_r31->unk0 = 8U;
                temp_r31->unk34 = 0.0f;
                Hu3DMotionShiftSet(temp_r28, arg0->motion[0], 0.0f, 12.0f, 0x40000001U);
            } else if (temp_r31->unk34 < 0.0f) {
                if (temp_r31->unk10.x > (f32) ((f64) temp_r27->x - 180.0)) {
                    var_f31 = 270.0f;
                } else {
                    temp_r31->unk34 = 1.0f;
                }
            } else if (temp_r31->unk10.x < (f32) (180.0 + (f64) temp_r27->x)) {
                var_f31 = 90.0f;
            } else {
                temp_r31->unk34 = -1.0f;
            }
        }
        break;
    case 3:
        temp_r31->unk1C.y = (f32) ((f64) temp_r31->unk1C.y - 1.666666753590107);
        if (!((temp_r31->unk10.y + temp_r31->unk1C.y) > temp_r27->y)) {
            temp_r31->unk10.y = (f32) temp_r27->y;
            temp_r31->unk1C.y = 0.0f;
            if ((s32) ((M574Stage *)arg0->data)->unk1E8[var_r29].unk10 == 0) {
                temp_r31->unk0 = (u32) (temp_r31->unk0 + 1);
                temp_r31->unk4 = 0;
                Hu3DMotionShiftSet(temp_r28, arg0->motion[0], 0.0f, 30.0f, 0x40000001U);
            }
        }
        break;
    case 4:
        temp_r0_2 = temp_r31->unk4 + 1;
        temp_r31->unk4 = temp_r0_2;
        if (!((f32) (f64) temp_r0_2 < 30.0f)) {
            temp_r31->unk0 = 2U;
            if ((s32) (frand() & 1) != 0) {
                var_f29 = -1.0;
            } else {
                var_f29 = 1.0;
            }
            temp_r31->unk34 = (f32) var_f29;
            Hu3DMotionShiftSet(temp_r28, arg0->motion[1], 0.0f, 12.0f, 0x40000001U);
        }
        break;
    case 5:
        temp_f1 = (f32) ((f64) temp_r31->unk3C.y - 0.2);
        temp_r31->unk3C.y = temp_f1;
        if (!(temp_f1 > 0.4f)) {
            temp_r31->unk3C.y = 0.4f;
            temp_r31->unk0 = (u32) (temp_r31->unk0 + 1);
        case 6:
            if ((s32) ((M574Stage *)arg0->data)->unk1E8[var_r29].unk10 == 0) {
                temp_r31->unk0 = (u32) (temp_r31->unk0 + 1);
            case 7:
                temp_f1_2 = (f32) ((f64) temp_r31->unk3C.y + 0.1);
                temp_r31->unk3C.y = temp_f1_2;
                if (!(temp_f1_2 < 1.0f)) {
                    temp_r31->unk3C.y = 1.0f;
                    temp_r31->unk0 = 4U;
                    temp_r31->unk4 = 0;
                    Hu3DMotionShiftSet(temp_r28, arg0->motion[0], 0.0f, 30.0f, 0x40000001U);
                }
            }
        }
        break;
    }
    if ((((s32) temp_r31->unk0 == 2) || ((s32) temp_r31->unk0 == 4)) && ((s32) temp_r31->unk38 != 0)) {
        temp_r31->unk4 = 0;
        temp_r31->unk34 = 0.0f;
                temp_r26 = &((M574Stage *)arg0->data)->unk1E8[var_r29].unk0;
        if ((MgSeqModeGet() == 5) && ((s32) *temp_r26 == 0)) {
            *temp_r26 += 1;
        }
        Hu3DMotionShiftSet(temp_r28, arg0->motion[2], 0.0f, 12.0f, 0x40000001U);
        if ((s32) temp_r31->unk38 == 1) {
            temp_r31->unk0 = 5U;
            fn_1_77D4(var_r29, 7);
            if (temp_r31->unk10.x < 0.0f) {
                fn_1_C10(0x92B, &temp_r31->unk10);
                return;
            }
            fn_1_C10(0x92C, &temp_r31->unk10);
            return;
        }
        temp_r31->unk0 = 3U;
        temp_r31->unk1C.y = 13.333334f;
        fn_1_77D4(var_r29, 8);
        if (temp_r31->unk10.x < 0.0f) {
            fn_1_C10(0x91A, &temp_r31->unk10);
            return;
        }
        fn_1_C10(0x91B, &temp_r31->unk10);
        return;
    }
    temp_r31->unk38 = 0;
    temp_r31->unk28.y = fn_1_CC8(temp_r31->unk28.y, var_f31, 0.05f);
    temp_r31->unk1C.x = (f32) ((f64) temp_r31->unk1C.x + (0.05 * ((0.01666666753590107 * (150.0 * (f64) temp_r31->unk34)) - (f64) temp_r31->unk1C.x)));
    VECAdd(&temp_r31->unk10, &temp_r31->unk1C, &temp_r31->unk10);
    Hu3DModelPosSet(temp_r28, temp_r31->unk10.x, (f32) ((f64) temp_r31->unk10.y - 20.0), temp_r31->unk10.z);
    Hu3DModelRotSetV(temp_r28, &temp_r31->unk28);
    Hu3DModelScaleSetV(temp_r28, &temp_r31->unk3C);
    var_r29 += 1;
    goto loop_46;
}

s32 fn_1_5628(M574Circle *self, M574Hit *ball) {
    ((M574Stage *)lbl_1_bss_48->data)->unkE50[self->unk8].unk38 = 1;
    return 0;
}

void fn_1_5680(Vec *pos) {
    s32 var_r30;
    M574Prop *temp_r31;

    var_r30 = 0;
loop_4:
    if (var_r30 < 2) {
        temp_r31 = &((M574Stage *)lbl_1_bss_48->data)->unkE50[var_r30];
        if ((f32) fabs(temp_r31->unk10.x - pos->x) < 50.0f) {
            temp_r31->unk38 = 2;
        }
        var_r30 += 1;
        goto loop_4;
    }
}

void fn_1_5750(omObjData *arg0) {
    M574Stage *spC;
    M574Stage *sp8;
    HSFOBJECT *temp_r3_2;
    HSFOBJECT *temp_r3_3;
    HSFOBJECT *temp_r3_4;
    M574Circle *temp_r30;
    s16 temp_r3;
    M574Prop *temp_r31;

    temp_r31 = &((M574Stage *)arg0->data)->unk14;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 5), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[8] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DMotionStartEndSet(temp_r3, 0.0f, 60.0f);
    Hu3DModelLayerSet(temp_r3, 4);
    spC = arg0->data;
    temp_r3_2 = Hu3DModelObjPtrGet(arg0->model[4], *lbl_1_data_3D0);
    if (temp_r3_2 != NULL) {
        Hu3DModelPosSet(temp_r3, temp_r3_2->mesh.base.pos.x, temp_r3_2->mesh.base.pos.y, temp_r3_2->mesh.base.pos.z);
    }
    sp8 = arg0->data;
    temp_r3_3 = Hu3DModelObjPtrGet(arg0->model[4], *lbl_1_data_3D0);
    if (temp_r3_3 != NULL) {
        temp_r31->unk10.x = (f32) temp_r3_3->mesh.base.pos.x;
        temp_r31->unk10.y = (f32) temp_r3_3->mesh.base.pos.y;
        temp_r31->unk10.z = (f32) temp_r3_3->mesh.base.pos.z;
    }
    temp_r30 = &temp_r31->unk4C;
    temp_r31->unk4C.unk0 = 1;
    temp_r30->unk4 = 1;
    temp_r30->unk8 = 0x64;
    temp_r30->unkC = 0;
    temp_r30->unk10 = arg0;
    temp_r30->unk14 = NULL;
    temp_r30->unk18 = fn_1_5D64;
    temp_r30->unk1C = &temp_r31->unk10;
    temp_r30->unk20 = 200.0f;
    fn_1_8B48(temp_r30);
    temp_r31->unk0 = 0;
    temp_r31->unk38 = 0;
    temp_r31->unk1C.z = 0.0f;
    temp_r31->unk1C.y = 0.0f;
    temp_r31->unk1C.x = 0.0f;
    temp_r3_4 = Hu3DModelObjPtrGet(temp_r3, lbl_1_data_4A4);
    temp_r31->unk48 = temp_r3_4;
    if (temp_r3_4 != NULL) {
        temp_r31->unk3C.x = (f32) temp_r3_4->mesh.base.pos.x;
        temp_r31->unk3C.y = (f32) temp_r3_4->mesh.base.pos.y;
        temp_r31->unk3C.z = (f32) temp_r3_4->mesh.base.pos.z;
    }
}

void fn_1_5934(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    f32 temp_f31;
    f64 var_f31;
    s16 temp_r27;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r23;
    s32 var_r25;
    M574Prop *temp_r26;
    HSFOBJECT *temp_r29;
    M574Stage *temp_r30;
    M574Prop *temp_r31;

    temp_r30 = arg0->data;
    temp_r31 = &temp_r30->unk14;
    temp_r27 = arg0->model[8];
    temp_r0 = temp_r30->unk14.unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (((s32) temp_r31->unk38 != 0) && (MgSeqModeGet() == 5)) {
            temp_r30->unk14.unk0 = (s32) (temp_r30->unk14.unk0 + 1);
            temp_r31->unk4 = 0;
            fn_1_77D4(temp_r31->unkC, 6);
            HuAudFXPlay(0x91C);
            HuAudFXPlay(0x91E);
            temp_r30->unkC = (s32) (temp_r30->unkC - 1);
            fn_1_63B0(lbl_1_data_4B0, lbl_1_data_4C8, temp_r30->unkC);
            fn_1_63B0(&lbl_1_data_4B0[1], &lbl_1_data_4C8[1], temp_r30->unkC);
        case 1:
            if ((s32) temp_r30->unkC > 0) {
                temp_r0_2 = temp_r31->unk4 + 1;
                temp_r31->unk4 = temp_r0_2;
                if (temp_r0_2 >= 4) {
                    temp_r30->unk14.unk0 = (s32) (temp_r30->unk14.unk0 - 1);
                    temp_r31->unk4 = 0;
                }
            } else {
                temp_r30->unk14.unk0 = (s32) (temp_r30->unk14.unk0 + 1);
                temp_r31->unk4 = 0;
            case 2:
                temp_r0_3 = temp_r31->unk4 + 1;
                temp_r31->unk4 = temp_r0_3;
                if (!((f32) (f64) temp_r0_3 < 60.0f)) {
                    temp_r23 = temp_r31->unkC;
                    temp_r26 = &((M574Stage *)arg0->data)->unk14;
                    sp8.x = temp_r26->unk10.x;
                    sp8.y = (f32) ((f64) temp_r26->unk10.y - 150.0);
                    sp8.z = 300.0f;
                    sp14.z = 80.0f;
                    var_r25 = 0;
loop_20:
                    if (var_r25 < 5) {
                        if (temp_r23 == 0) {
                            var_f31 = 240.0f;
                        } else {
                            var_f31 = 120.0f;
                        }
                        temp_f31 = (f32) (var_f31 + (10.0 * (3.0517578125e-05 * (f64) (f32) ((s32) (frand() & 0xFFFF) - 0x8000))));
                        sp14.x = (f32) (100.0 * (0.2 * sin((3.141592653589793 * (f64) temp_f31) / 180.0)));
                        sp14.y = (f32) (100.0 * (0.2 * cos((3.141592653589793 * (f64) temp_f31) / 180.0)));
                        fn_1_6C2C(&sp8, &sp14);
                        var_r25 += 1;
                        goto loop_20;
                    }
                    temp_r30->unk14.unk0 = (s32) (temp_r30->unk14.unk0 + 1);
                    temp_r31->unk4 = 0;
                case 3:
                    temp_r0_4 = temp_r31->unk4 + 1;
                    temp_r31->unk4 = temp_r0_4;
                    if (!((f32) (f64) temp_r0_4 < 60.0f)) {
                        temp_r30->unk14.unk0 = 0;
                        temp_r31->unk4 = 0;
                        temp_r30->unkC = 5;
                    }
                }
            }
        }
        break;
    }
    if (Hu3DMotionEndCheck(temp_r27) != 0) {
        Hu3DModelAttrSet(temp_r27, 0x40000001U);
        Hu3DMotionStartEndSet(temp_r27, 0.0f, 60.0f);
        Hu3DMotionTimeSet(temp_r27, 0.0f);
    }
    temp_r31->unk38 = 0;
    VECScale(&temp_r31->unk1C, &temp_r31->unk1C, 0.2f);
    temp_r29 = temp_r31->unk48;
    if (temp_r29 != NULL) {
        temp_r29->mesh.base.pos.x = (f32) (temp_r31->unk3C.x + temp_r31->unk1C.x);
        temp_r29->mesh.base.pos.y = (f32) (temp_r31->unk3C.y + temp_r31->unk1C.y);
    }
}

s32 fn_1_5D64(M574Circle *self, M574Hit *ball) {
    s16 temp_r29;
    s32 var_r27;
    M574Stage *temp_r26;
    M574Prop *temp_r31;

    temp_r26 = lbl_1_bss_48->data;
    temp_r31 = &temp_r26->unk14;
    temp_r29 = lbl_1_bss_48->model[8];
    if ((s32) temp_r26->unk14.unk0 == 0) {
        temp_r31->unk38 = 1;
        if (ball->unk18->x < 0.0f) {
            var_r27 = 0;
        } else {
            var_r27 = 1;
        }
        temp_r31->unkC = var_r27;
        Hu3DModelAttrReset(temp_r29, 0x40000001U);
        Hu3DMotionStartEndSet(temp_r29, 60.0f, Hu3DMotionMaxTimeGet(temp_r29));
        Hu3DMotionTimeSet(temp_r29, 60.0f);
        VECNormalize(ball->unk1C, &temp_r31->unk1C);
        VECScale(&temp_r31->unk1C, &temp_r31->unk1C, 50.0f);
    }
    return 0;
}

void fn_1_5E5C(omObjData *arg0) {
    M574Stage *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk8 = Hu3DTexScrollCreate(arg0->model[8], lbl_1_data_504);
    temp_r31->unkC = 5;
    temp_r31->pad10[0] = 5.0f;
}

void fn_1_5ECC(omObjData *arg0) {
    f32 temp_f28;
    f32 var_f31;
    f32 var_f31_2;
    s32 var_r30;
    M574Stage *temp_r31;

    temp_r31 = arg0->data;
    var_f31 = (f32) fmod((f64) ((f32) temp_r31->unkC - temp_r31->pad10[0]), 10.0);
    if (var_f31 < 0.0f) {
        var_f31 = (f32) ((f64) var_f31 + 10.0);
    }
    if (var_f31 > 5.0f) {
        var_f31 = (f32) ((f64) var_f31 - 10.0);
    }
    var_f31_2 = (f32) fmod((f64) (f32) ((f64) temp_r31->pad10[0] + (0.1 * (f64) var_f31)), 10.0);
    if (var_f31_2 < 0.0f) {
        var_f31_2 = (f32) ((f64) var_f31_2 + 10.0);
    }
    temp_r31->pad10[0] = var_f31_2;
    var_r30 = (s32) (0.5 + (f64) var_f31_2);
    temp_f28 = (f32) (0.125 * (f64) (var_f31_2 - (f32) var_r30));
    if (var_r30 > 9) {
        var_r30 = 0;
    }
    if (var_r30 < 0) {
        var_r30 = 0;
    }
    Hu3DTexScrollPosSet(temp_r31->unk8, lbl_1_data_510[var_r30].unk0, temp_f28 + lbl_1_data_510[var_r30].unk4, 0.0f);
}

void fn_1_6168(omObjData *arg0) {
    ANIMDATA *temp_r25;
    s16 temp_r3;
    s32 var_r27;
    s32 var_r29;
    M574Stage *temp_r26;
    HU3DPARTICLE *temp_r28;
    HU3DPARTICLEDATA *var_r31;

    temp_r26 = arg0->data;
    temp_r25 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M574, 32), MEMORY_DEFAULT_NUM, HEAP_DATA));
    var_r29 = 0;
loop_5:
    if (var_r29 < 5) {
        temp_r3 = Hu3DParticleCreate(temp_r25, 8);
        temp_r26->unk9C[var_r29] = temp_r3;
        temp_r28 = Hu3DData[temp_r3].hookData;
        Hu3DParticleBlendModeSet(temp_r3, 0U);
        Hu3DParticleHookSet(temp_r3, fn_1_62A0);
        Hu3DModelLayerSet(temp_r3, 7);
        Hu3DModelPosSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DParticleAnimModeSet(temp_r3, (s16) (4 - var_r29));
        var_r31 = temp_r28->data;
        var_r27 = 0;
loop_3:
        if (var_r27 < (s16) temp_r28->maxCnt) {
            var_r31->time = -1;
            var_r31->scale = 0.0f;
            var_r27 += 1;
            var_r31++;
            goto loop_3;
        }
        var_r29 += 1;
        goto loop_5;
    }
}

void fn_1_629C(void) {

}

void fn_1_62A0(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    s16 temp_r0;
    s32 var_r30;

    var_r31 = particleP->data;
    var_r30 = 0;
loop_11:
    if (var_r30 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31->time += 1;
            var_r31->scale = 200.0f;
            var_r31->color.a = 0xB4;
            /* fallthrough */
        case 1:
            var_r31->scale -= 10.0f;
            var_r31->color.a -= 4;
            if ((var_r31->scale <= 0.0f) || ((u8) var_r31->color.a > 0xF0U)) {
                var_r31->time = -1;
                var_r31->scale = 0.0f;
            } else {
                VECAdd(&var_r31->pos, &var_r31->accel, &var_r31->pos);
            }
            break;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_11;
    }
}

void fn_1_63B0(Vec *pos, Vec *accel, s32 count) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    temp_r30 = Hu3DData[((M574Stage *)lbl_1_bss_48->data)->unk9C[4 - count]].hookData;
    var_r31 = temp_r30->data;
    var_r29 = 0;
loop_4:
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        return;
    }
    if ((s16) var_r31->time < 0) {
        var_r31->time = 0;
        var_r31->pos.x = (f32) pos->x;
        var_r31->pos.y = (f32) pos->y;
        var_r31->pos.z = (f32) pos->z;
        var_r31->accel.x = (f32) accel->x;
        var_r31->accel.y = (f32) accel->y;
        var_r31->accel.z = (f32) accel->z;
        return;
    }
    var_r29 += 1;
    var_r31++;
    goto loop_4;
}

void fn_1_6478(s32 flipper, f32 power) {
    f32 var_f31;
    M574Flipper *temp_r31;

    temp_r31 = &((M574Stage *)lbl_1_bss_48->data)->unkA8[flipper];
    if ((power - temp_r31->unk0) > 0.2f) {
        HuAudFXPlay(lbl_1_data_560[flipper]);
    }
    temp_r31->unk0 = power;
    var_f31 = (f32) (60.0 * (f64) power);
    if ((s32) (flipper & 1) != 0) {
        var_f31 = -var_f31;
    }
    temp_r31->unkC = (f32) (var_f31 + lbl_1_data_280[flipper]);
}

f64 fn_1_6568(s32 flipper) {
    f32 var_f31;
    f32 var_f31_2;
    M574Flipper *temp_r31;

    temp_r31 = &((M574Stage *)lbl_1_bss_48->data)->unkA8[flipper];
    if ((s32) (flipper & 1) != 0) {
        var_f31_2 = lbl_1_data_280[flipper] - temp_r31->unk8;
    } else {
        var_f31_2 = temp_r31->unk8 - lbl_1_data_280[flipper];
    }
    var_f31 = (f32) ((f64) var_f31_2 / 60.0);
    if (var_f31 < 0.0f) {
        var_f31 = 0.0f;
    }
    if (var_f31 > 1.0f) {
        var_f31 = 1.0f;
    }
    return (f64) var_f31;
}
