// MP5 m547 (a 1 vs 1 button-mashing duel), generated from its m2c draft by tools/mp5/ports/m547dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m547dll (tools/mp5/decomp.py m547dll --types tools/mp5/types/m547dll.h)
// Written from the draft: a 1 vs 1 button-mashing duel on MP5's MgSeq sequencer. The same game framework as
// m550/m548 (a work struct lbl_1_bss_488, also reached through the pointer lbl_1_bss_6E8), but the work starts at
// the object manager, the players follow at 0x4 and the per-player animation request is only 0x24 bytes.

typedef struct M547Model { // model table entry, 0x1C (30 of them in lbl_1_bss_E8)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M547Model;

typedef struct M547Player { // 0x1C
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // com: difficulty + 1
    s16 unk6; // pad
    s32 unk8; // HuPadBtn
    s32 unkC; // HuPadBtnDown (the game masks it with 0x100)
    s8 unk10; // stick x (dead zone 10)
    s8 unk11; // stick y
    u16 unk12; // HuPadBtnRep
    s8 unk14; // sub stick x
    s8 unk15;
    u8 unk16; // trigger L
    u8 unk17;
    u8 unk18; // HuPadDStk
    u8 unk19; // HuPadDStkRep
    char pad1A[2];
} M547Player;

typedef struct M547Char { // per MP5 character, 0x1C
    u32 unk0[7]; // MP5 motion data numbers
} M547Char;

typedef struct M547Anim { // per player character animation request, 0x24 (fn_1_933C applies it)
    s16 unk0; // motion index
    s16 unk2; // motion index applied
    f32 unk4; // speed
    f32 unk8; // speed applied
    f32 unkC; // time
    f32 unk10; // time seen last frame
    f32 unk14; // motion length
    u32 unk18; // model attrs to set
    u32 unk1C; // set last frame
    u32 unk20; // model attrs to reset
} M547Anim;

typedef struct M547Work { // lbl_1_bss_488, 0x210 on GC
    HUPROCESS *unk0; // object manager
    M547Player unk4[2];
    M547Model *unk3C; // model table (lbl_1_bss_E8)
    M547Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_5C)
    M547Anim unk50[2];
    s32 *unk98; // data numbers (lbl_1_data_0)
    s16 unk9C;
    char pad9E[2];
    s32 unkA0; // mode step
    s32 unkA4; // sub step
    s32 unkA8; // nonzero while the rod / fruit fall is over
    s32 unkAC; // bits: which players' marker is bobbing
    s32 unkB0; // counter
    s32 unkB4[2]; // press count per player
    s32 unkBC; // frame counter
    Vec unkC0[4]; // positions
    s32 unkF0; // background model 3 is frozen
    s32 unkF4;
    s32 unkF8;
    s32 unkFC; // background step
    char pad100[8];
    char pad108[8];
    f32 unk110;
    f32 unk114;
    char pad118[8];
    s32 unk120;
    s32 unk124;
    s32 unk128;
    s32 unk12C;
    char pad130[0x10];
    f32 unk140;
    f32 unk144;
    f32 unk148;
    char pad14C[4];
    s32 unk150;
    s32 unk154;
    s32 unk158;
    s32 unk15C;
    char pad160[0x10];
    f32 unk170;
    f32 unk174;
    char pad178[0xC];
    s32 unk184;
    char pad188[4];
    s32 unk18C;
    char pad190[0x10];
    f32 unk1A0;
    f32 unk1A4;
    f32 unk1A8;
    char pad1AC[8];
    s32 unk1B4;
    char pad1B8[4];
    s32 unk1BC;
    char pad1C0[0x50];
} M547Work;

typedef struct M547Fall { // lbl_1_bss_440, 0xC
    f32 unk0;
    f32 unk4;
    f32 unk8;
} M547Fall;


void fn_1_4094(void);
void fn_1_7A08(void);
void fn_1_7DAC(void);
void fn_1_7F2C(void);
void fn_1_21BC(s32 player, f32 alpha);
void fn_1_223C(s16 arg0);
void fn_1_243C(s32 player, s16 arg1);
void fn_1_2648(s32 player);
void fn_1_670C(s32 player);
void fn_1_6A88(s32 player);
void fn_1_86B8(M547Work *work, M547Model *models, s32 *dataNums);
void fn_1_8904(s16 arg0);
void fn_1_8B9C(M547Char *chr0, M547Char *chr1);
void fn_1_8BC0(s16 *mot0, s16 *mot1);
void fn_1_4094(void);
void fn_1_41B0(void);
void fn_1_43A0(void);
void fn_1_47E0(void);
void fn_1_4A94(void);
void fn_1_5894(void);
void fn_1_5DC4(void);
void fn_1_670C(s32 player);
void fn_1_6A88(s32 player);
void fn_1_6FF4(void);
void fn_1_750C(void);
void fn_1_7724(void);
void fn_1_7A08(void);
void fn_1_7DAC(void);
void fn_1_7F2C(void);
void fn_1_8298(void);
void ObjectSetup(void);
void fn_1_17C(s16 arg0, s16 frameNo);
void fn_1_A84(s16 mode, s16 frameNo);
void fn_1_ACC(s16 arg0, s16 frameNo);
void fn_1_B24(s16 arg1, s16 frameNo);
void fn_1_C70(s16 arg0, s16 frameNo);
void fn_1_CF0(s16 mode, s16 frameNo);
void fn_1_D7C(s16 mode, s16 frameNo);
void fn_1_DA8(s16 mode, s16 frameNo);
void fn_1_DE4(s16 mode, s16 frameNo);
void fn_1_E88(omObjData *obj);
void fn_1_10D0(omObjData *obj);
void fn_1_1544(omObjData *obj);
void fn_1_162C(void);
void fn_1_1BA8(void);
void fn_1_21BC(s32 player, f32 alpha);
void fn_1_223C(s16 arg0);
void fn_1_231C(void);
void fn_1_23A8(void);
void fn_1_243C(s32 player, s16 arg1);
void fn_1_2648(s32 player);
void fn_1_2678(omObjData *obj);
void fn_1_2CE4(void);
void fn_1_376C(void);
void fn_1_3ADC(omObjData *obj);
void fn_1_86B8(M547Work *work, M547Model *models, s32 *dataNums);
void fn_1_8904(s16 arg0);
void fn_1_8B9C(M547Char *chr0, M547Char *chr1);
void fn_1_8BC0(s16 *mot0, s16 *mot1);
void fn_1_8BE4(void);
void fn_1_8D2C(omObjData *obj);
void fn_1_91E8(void);
void fn_1_933C(omObjData *obj);
void fn_1_954C(omObjData *obj);
void fn_1_95A0(void);
void fn_1_9BD8(void);
void fn_1_A124(void);
void fn_1_AA08(void);
void fn_1_B414(void);

struct _struct_lbl_1_data_248_0x8 {
    /* 0x0 */ s32 unk0;                             /* inferred */
    /* 0x4 */ s32 unk4;                             /* inferred */
};                                                  /* size = 0x8 */

struct _struct_lbl_1_data_2BC_0x8 {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
};                                                  /* size = 0x8 */

struct _struct_lbl_1_data_350_0xC {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
    /* 0x8 */ f32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

static Vec lbl_1_data_280 = { 0.0f, 200.0f, 200.0f };
static Vec lbl_1_data_28C = { 0.0f, 1.0f, 0.0f };
static Vec lbl_1_data_298 = { 0.0f, 200.0f, 0.0f };
s32 lbl_1_data_2A4[2] = { -1, -1 };
static s32 lbl_1_data_2AC[4] = { 0, 0, 0, 0 };
static struct _struct_lbl_1_data_2BC_0x8 lbl_1_data_2BC[0xD] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.5f, 0.0f },
    { 0.75f, 0.0f },
    { 0.0f, 0.25f },
    { 0.25f, 0.25f },
    { 0.5f, 0.25f },
    { 0.75f, 0.25f },
    { 0.0f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
};
static s32 lbl_1_data_324 = -1;
static s32 lbl_1_data_328[2] = { 0, 0 };
static s16 lbl_1_data_330[2] = { 0, 0 };
static s32 lbl_1_data_334[2] = { 0, 0 };
static f32 lbl_1_data_33C = 5.0f;
static s32 lbl_1_data_340 = -1;
static struct { // TODO(mp5): synthesized from the symbol size
    f32 unk0;
    f32 unk4;
    f32 unk8;
} lbl_1_data_344;
static f32 lbl_1_bss_698;
static f32 lbl_1_bss_69C;
static s32 lbl_1_bss_6A0;
static s16 lbl_1_bss_6A4;
static MGTIMER *lbl_1_bss_6A8;
f32 lbl_1_bss_6AC[4];
s16 lbl_1_bss_6BC[4];
s32 lbl_1_bss_6C4[4];
s32 lbl_1_bss_6D4[5];
s32 lbl_1_data_0[0xD] = {
    DATA_MAKE_NUM(DATADIR_MP5_M547, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 12),
};
s32 lbl_1_data_34[0xB] = {
    DATA_MAKE_NUM(DATADIR_MP5_M547, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M547, 24),
};
static s32 lbl_1_data_60 = DATA_MAKE_NUM(DATADIR_MP5_M547, 18);
M547Char lbl_1_data_64[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 78), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 79), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
};
static MGSEQ_PARAM lbl_1_data_1D0 = {
    0,
    0,
    fn_1_17C,
    fn_1_A84,
    fn_1_ACC,
    fn_1_B24,
    fn_1_C70,
    fn_1_CF0,
    fn_1_D7C,
    fn_1_DA8,
    fn_1_DE4,
};
void (*lbl_1_data_1F8[2])() = { fn_1_41B0, fn_1_43A0 };
void (*lbl_1_data_200[5])() = { fn_1_47E0, fn_1_4A94, fn_1_5894, fn_1_5DC4, fn_1_6FF4 };
void (*lbl_1_data_214[3])() = { fn_1_7A08, fn_1_7DAC, fn_1_7F2C };
static s32 lbl_1_data_240[2] = { 0, 0 };
static struct _struct_lbl_1_data_248_0x8 lbl_1_data_248[2] = { { 0, 0 }, { 0, 0 } };
static s8 lbl_1_data_26F[0xD] = { 0x6D, 0x35, 0x34, 0x37, 0x70, 0x61, 0x72, 0x61, 0x30, 0x31, 0, 0, 0 };
static f32 lbl_1_data_27C = 1.0f;
static s16 lbl_1_bss_0;
static s16 lbl_1_bss_2;
static s32 lbl_1_bss_4;
static s32 lbl_1_bss_8;
static s32 lbl_1_bss_C;
static s32 lbl_1_bss_10;
static s32 lbl_1_bss_14;
static MGSCORE *lbl_1_bss_18;
static MGSCORE *lbl_1_bss_1C;
static s16 lbl_1_bss_20;
s32 lbl_1_bss_24[4];
static s32 lbl_1_bss_34;
static Vec lbl_1_bss_38[3];
s16 lbl_1_bss_5C[2][7];
static OMCAMERAVIEW lbl_1_bss_78[4];
M547Model lbl_1_bss_E8[0x1E];
s32 lbl_1_bss_430[4];
M547Fall lbl_1_bss_440[2];
Vec lbl_1_bss_458;
Vec lbl_1_bss_464;
s16 lbl_1_bss_470[8];
s16 lbl_1_bss_480[2];
static omObjData *lbl_1_bss_484;
M547Work lbl_1_bss_488;
static struct _struct_lbl_1_data_350_0xC lbl_1_data_350[0xD] = {
    { 0.0f, 0.0f, 0.0f },
    { 913.0f, 0.0f, -1177.0f },
    { 993.0f, 0.0f, -1038.0f },
    { 550.0f, 1000.0f, -3250.0f },
    { 593.0f, 312.0f, -1119.0f },
    { -462.0f, 330.0f, -1100.0f },
    { -1000.0f, 40.0f, -2100.0f },
    { -2500.0f, 0.0f, -3900.0f },
    { -1000.0f, 0.0f, -2100.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
void (*lbl_1_data_3EC[5])() = { fn_1_95A0, fn_1_9BD8, fn_1_A124, fn_1_AA08, fn_1_B414 };
M547Work *lbl_1_bss_6E8;
f32 lbl_1_rodata_90[0xD] = {
    102.0f,
    102.0f,
    114.0f,
    98.0f,
    102.0f,
    114.0f,
    90.0f,
    100.0f,
    102.0f,
    102.0f,
    102.0f,
    102.0f,
    102.0f,
}; /* const */
s32 lbl_1_rodata_130[4] = { 0x28, 0x32, 0x55, 0x6E }; /* const */

void fn_1_4094(void) {
    s16 var_r31;

    var_r31 = 1;
loop_2:
    if (var_r31 < 9) {
        Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31].unk0, lbl_1_bss_488.unk3C[var_r31].unk4.x, lbl_1_bss_488.unk3C[var_r31].unk4.y, lbl_1_bss_488.unk3C[var_r31].unk4.z);
        Hu3DModelRotSet(lbl_1_bss_488.unk3C[var_r31].unk0, lbl_1_bss_488.unk3C[var_r31].unk10.x, lbl_1_bss_488.unk3C[var_r31].unk10.y, lbl_1_bss_488.unk3C[var_r31].unk10.z);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_41B0(void) {
    s32 var_r30;
    s32 var_r31;

    lbl_1_bss_488.unkB0 += 1;
    var_r31 = 0;
loop_7:
    if (var_r31 < 2) {
        lbl_1_bss_488.unkC0[var_r31].y = 800.0f - ((600.0f * (f32) lbl_1_bss_488.unkB0) / 30.0f);
        if ((s32) lbl_1_bss_488.unkB0 == 0x1E) {
            lbl_1_bss_488.unkC0[var_r31].y = 200.0f;
            lbl_1_bss_488.unk50[var_r31].unk4 = 1.0f;
            if (var_r31 != 0) {
                lbl_1_bss_488.unkA0 += 1;
                lbl_1_bss_488.unkA4 = 0;
                lbl_1_bss_488.unkB0 = 0;
                omCameraViewMoveSimpleMulti(1U, lbl_1_bss_78, 0x3C);
                HuAudFXPlay(0x835);
                var_r30 = 0;
loop_5:
                if (var_r30 < 4) {
                    lbl_1_bss_6C4[var_r30] = 0;
                    lbl_1_bss_6D4[var_r30] = 0;
                    var_r30 += 1;
                    goto loop_5;
                }
            }
        }
        var_r31 += 1;
        goto loop_7;
    }
    if ((WipeCheckEnd() == 0) && ((s32) lbl_1_data_324 < 0)) {
        lbl_1_data_324 = HuAudBGMPlay(0x3B);
    }
}

void fn_1_43A0(void) {
    s32 var_r31;

    lbl_1_bss_488.unkB0 += 1;
    var_r31 = 0;
loop_13:
    if (var_r31 < 2) {
        if ((s32) lbl_1_bss_488.unkB0 <= 0xF) {
            lbl_1_bss_488.unkC0[var_r31].y = (f32) (180.0 + (20.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_488.unkB0 * 0x168) / 15)) / 180.0)));
        } else if ((s32) lbl_1_bss_488.unkB0 <= 0x1E) {
            lbl_1_bss_488.unkC0[var_r31].y = (f32) (185.0 + (15.0 * cos((3.141592653589793 * (f64) (((lbl_1_bss_488.unkB0 - 0xF) * 0x168) / 15)) / 180.0)));
        } else if ((s32) lbl_1_bss_488.unkB0 <= 0x2D) {
            lbl_1_bss_488.unkC0[var_r31].y = (f32) (195.0 + (5.0 * cos((3.141592653589793 * (f64) (((lbl_1_bss_488.unkB0 - 0x1E) * 0x168) / 15)) / 180.0)));
        } else if ((s32) lbl_1_bss_488.unkB0 <= 0x3C) {
            lbl_1_bss_488.unkC0[var_r31].y = (f32) (198.0 + (2.0 * cos((3.141592653589793 * (f64) (((lbl_1_bss_488.unkB0 - 0x2D) * 0x168) / 15)) / 180.0)));
        }
        if ((s32) lbl_1_bss_488.unkB0 == 0x3C) {
            Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31][0], 0.0f, 20.0f, 0x40000001U);
            if (var_r31 != 0) {
                lbl_1_bss_488.unkA0 = 0;
                lbl_1_bss_488.unkA4 = 0;
                lbl_1_bss_488.unkB0 = 0;
                MgSeqModeNext();
            }
        }
        var_r31 += 1;
        goto loop_13;
    }
    if ((WipeCheckEnd() == 0) && ((s32) lbl_1_data_324 < 0)) {
        lbl_1_data_324 = HuAudBGMPlay(0x3B);
    }
}

void fn_1_47E0(void) {
    lbl_1_bss_6A8 = MgTimerCreate(0);
    MgTimerParamSet(lbl_1_bss_6A8, 0x258, 0, 0);
    MgTimerPosSet(lbl_1_bss_6A8, 288.0f, 416.0f);
    MgTimerModeOnSet(lbl_1_bss_6A8, 1);
    lbl_1_bss_488.unkB0 = 1;
    lbl_1_bss_488.unkA0 += 1;
    lbl_1_bss_6BC[0] = 0;
    lbl_1_bss_6BC[1] = 0;
    lbl_1_bss_6AC[0] = 0.0f;
    lbl_1_bss_6AC[1] = 3.0f;
    lbl_1_bss_6AC[2] = 600.0f;
    lbl_1_bss_6AC[3] = 200.0f;
}


void fn_1_4A94(void) {
    s32 *temp_r4;
    s32 *temp_r4_2;
    s32 *temp_r4_3;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;
    s32 var_r31_6;
    u32 temp_r4_5;
    u8 temp_r3_3;
    s32 *temp_r4_4;
    s32 *temp_r4_6;

    var_r31 = 0;
loop_18:
    if (var_r31 < 2) {
        if ((s32) lbl_1_bss_488.unkB4[var_r31] == 1) {
            lbl_1_bss_488.unkB4[var_r31] = 2;
            Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31][3], 0.0f, 20.0f, 0x40000001U);
        }
        if (((s16) lbl_1_bss_488.unk4[var_r31].unk4 == 0) && ((s32) lbl_1_bss_488.unkB4[var_r31] >= 2)) {
            if ((s32) lbl_1_data_2AC[(var_r31 * 2) + 1] < 0) {
                temp_r4 = &lbl_1_data_2AC[(var_r31 * 2) + 1];
                *temp_r4 -= 1;
            }
            if ((s32) lbl_1_bss_488.unkB4[var_r31] == (s32) lbl_1_data_2AC[var_r31 * 2]) {
                if ((s32) lbl_1_data_2AC[(var_r31 * 2) + 1] >= 0) {
                    temp_r4_2 = &lbl_1_data_2AC[(var_r31 * 2) + 1];
                    *temp_r4_2 += 1;
                }
                if (((s32) lbl_1_data_2AC[(var_r31 * 2) + 1] >= 0x1E) && (MgTimerValueGet(lbl_1_bss_6A8) >= 0x2D)) {
                    Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31][0], 0.0f, 20.0f, 0x40000001U);
                    lbl_1_data_2AC[(var_r31 * 2) + 1] = -1;
                    lbl_1_data_2AC[var_r31 * 2] = lbl_1_bss_488.unkB4[var_r31];
                }
            } else if ((s32) lbl_1_data_2AC[(var_r31 * 2) + 1] >= 0) {
                lbl_1_data_2AC[var_r31 * 2] = lbl_1_bss_488.unkB4[var_r31];
                lbl_1_data_2AC[(var_r31 * 2) + 1] = 0;
            } else if ((s32) lbl_1_data_2AC[(var_r31 * 2) + 1] < -0x14) {
                Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31][3], 0.0f, 20.0f, 0x40000001U);
                lbl_1_data_2AC[var_r31 * 2] = lbl_1_bss_488.unkB4[var_r31];
                lbl_1_data_2AC[(var_r31 * 2) + 1] = 0;
            }
        }
        var_r31 += 1;
        goto loop_18;
    }
    var_r31_2 = 0;
loop_29:
    if (var_r31_2 < 2) {
        if ((s32) lbl_1_bss_488.unkB4[var_r31_2] >= 0x50) {
            lbl_1_bss_488.unkC0[var_r31_2].y = 150.0f;
            lbl_1_data_330[var_r31_2] = 0x2000;
        } else {
            lbl_1_bss_488.unkC0[var_r31_2].y = (f32) (0xC8 - ((lbl_1_bss_488.unkB4[var_r31_2] * 0x32) / 80));
            lbl_1_data_330[var_r31_2] = (s16) ((lbl_1_bss_488.unkB4[var_r31_2] << 0xD) / 80);
        }
        if ((s32) (lbl_1_bss_488.unkB4[var_r31_2] - lbl_1_data_328[var_r31_2]) >= 3) {
            lbl_1_data_328[var_r31_2] = lbl_1_bss_488.unkB4[var_r31_2];
            temp_r3 = HuAudFXPlay(0x83A);
            HuAudFXPanning(temp_r3, (s16) ((var_r31_2 << 5) + 0x30));
            HuAudFXPitchSet(temp_r3, lbl_1_data_330[var_r31_2]);
            lbl_1_data_334[var_r31_2] = 0;
        } else {
            temp_r4_3 = &lbl_1_data_334[var_r31_2];
            *temp_r4_3 += 1;
            if (((s16) lbl_1_bss_488.unk4[var_r31_2].unk4 != 0) && ((s32) lbl_1_data_334[var_r31_2] >= 0xF)) {
                lbl_1_data_328[var_r31_2] = lbl_1_bss_488.unkB4[var_r31_2];
                temp_r3_2 = HuAudFXPlay(0x83A);
                HuAudFXPanning(temp_r3_2, (s16) ((var_r31_2 << 5) + 0x30));
                HuAudFXPitchSet(temp_r3_2, lbl_1_data_330[var_r31_2]);
                lbl_1_data_334[var_r31_2] = 0;
            }
        }
        var_r31_2 += 1;
        goto loop_29;
    }
    if ((s16) *lbl_1_bss_6BC < 0xB4) {
        *lbl_1_bss_6BC += 1;
    } else {
        lbl_1_bss_6AC[0] += lbl_1_bss_6AC[1];
        lbl_1_bss_6AC[1] = (f32) ((f64) lbl_1_bss_6AC[1] * 0.985);
        lbl_1_bss_6AC[2] = (f32) ((f64) lbl_1_bss_6AC[2] * 0.985);
        lbl_1_bss_6AC[3] = (f32) ((f64) lbl_1_bss_6AC[3] * 0.985);
        lbl_1_bss_464.x = (f32) (-100.0 + ((f64) lbl_1_bss_6AC[2] * cos((3.141592653589793 * (f64) lbl_1_bss_6AC[0]) / 180.0)));
        lbl_1_bss_464.y = (f32) (300.0 - ((f64) lbl_1_bss_6AC[3] * sin((3.141592653589793 * (f64) lbl_1_bss_6AC[0]) / 180.0)));
        lbl_1_bss_464.z = -500.0f;
    }
    if (MgTimerDoneCheck(lbl_1_bss_6A8) != 0) {
        var_r31_3 = 0;
loop_38:
        if (var_r31_3 < 2) {
            if ((s32) lbl_1_bss_488.unkB4[var_r31_3] != 0) {
                temp_r4_4 = &lbl_1_bss_488.unkB4[var_r31_3];
                *temp_r4_4 -= 1;
            }
            var_r31_3 += 1;
            goto loop_38;
        }
        var_r31_4 = 0;
loop_43:
        if (var_r31_4 < 2) {
            if ((s16) lbl_1_bss_488.unk4[var_r31_4].unk4 != 0) {
                fn_1_2648(var_r31_4);
            }
            var_r31_4 += 1;
            goto loop_43;
        }
        lbl_1_bss_488.unkB0 = 0;
        if (((s32) (lbl_1_bss_488.unkB4[0] * 2) != 0) && ((s32) lbl_1_bss_488.unkB4[0] == (s32) lbl_1_bss_488.unkB4[1])) {
            temp_r3_3 = rand8();
            temp_r4_5 = temp_r3_3 >> 0x1FU;
            temp_r4_6 = &lbl_1_bss_488.unkB4[temp_r3_3 & 1];
            *temp_r4_6 -= 1;
        }
        lbl_1_bss_488.unkA0 += 1;
        lbl_1_bss_488.unkA4 = 0;
        lbl_1_bss_488.unkC0[3].z = 30.0f;
        var_r31_5 = 0;
        var_r30 = 0;
loop_52:
        if (var_r31_5 < 2) {
            if ((s32) lbl_1_bss_488.unkB4[var_r31_5] != 0) {
                lbl_1_bss_488.unkC0[var_r31_5 + 2].y = 10000.0f;
            } else {
                lbl_1_bss_488.unkC0[var_r31_5 + 2].y = 0.0f;
                var_r30 += 1;
            }
            Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31_5 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31_5][1], 0.0f, 10.0f, 0U);
            lbl_1_bss_488.unk50[var_r31_5].unk20 = 0x40000001;
            var_r31_5 += 1;
            goto loop_52;
        }
        HuAudSStreamFadeOut(lbl_1_data_324, 0x64);
        if (var_r30 == 2) {
            lbl_1_bss_488.unkA0 = 4;
            lbl_1_bss_488.unkA4 = 0;
            lbl_1_bss_488.unkB4[0] = 0;
            lbl_1_bss_488.unkB4[1] = 0;
            return;
        }
        HuAudFXPlay(0x836);
        *lbl_1_bss_24 = 1;
        lbl_1_bss_484->work[0] = 0;
        Mp5CameraPosGet(1, lbl_1_bss_38, &lbl_1_bss_38[1], &lbl_1_bss_38[2]);
        var_r31_6 = 0;
loop_57:
        if (var_r31_6 < 4) {
            lbl_1_bss_6BC[var_r31_6] = 0;
            lbl_1_bss_6AC[var_r31_6] = 0.0f;
            var_r31_6 += 1;
            goto loop_57;
        }
        lbl_1_bss_6AC[1] = 9.0f;
        if (var_r30 == 1) {
            if ((s32) lbl_1_bss_488.unkB4[0] != 0) {
                lbl_1_bss_488.unkC0[3].y = 10000.0f;
                return;
            }
            lbl_1_bss_488.unkC0[2].y = 10000.0f;
        }
    }
}


void fn_1_5894(void) {
    s32 temp_r3;
    s32 var_r30;
    s32 var_r31;

    var_r31 = 0;
    var_r30 = 0;
loop_5:
    if (var_r31 < 2) {
        if (lbl_1_bss_488.unkC0[var_r31 + 2].y > (lbl_1_bss_488.unkC0[var_r31].y + lbl_1_bss_488.unkC0[3].z)) {
            lbl_1_bss_488.unkC0[var_r31].y += lbl_1_bss_488.unkC0[3].z;
        } else {
            lbl_1_bss_488.unkC0[var_r31].y = lbl_1_bss_488.unkC0[var_r31 + 2].y;
            var_r30 += 1;
        }
        var_r31 += 1;
        goto loop_5;
    }
    lbl_1_bss_488.unkC0[3].z = (f32) ((f64) lbl_1_bss_488.unkC0[3].z * 1.06);
    lbl_1_bss_6AC[0] += lbl_1_bss_6AC[1];
    if (lbl_1_bss_6AC[0] > 180.0f) {
        lbl_1_bss_6AC[0] = 180.0f;
    }
    lbl_1_bss_464.x = (f32) (-100.0 + (500.0 * sin((3.141592653589793 * (f64) lbl_1_bss_6AC[0]) / 180.0)));
    if ((lbl_1_bss_6AC[0] >= 90.0f) && (lbl_1_bss_464.x < 0.0f)) {
        lbl_1_bss_464.x = 0.0f;
    }
    lbl_1_bss_464.y += lbl_1_bss_488.unkC0[3].z;
    lbl_1_bss_464.z = (f32) (-500.0 * cos((3.141592653589793 * (f64) lbl_1_bss_6AC[0]) / 180.0));
    lbl_1_bss_458.y = -lbl_1_bss_6AC[0];
    temp_r3 = lbl_1_bss_488.unkA4;
    lbl_1_bss_488.unkA4 = temp_r3 + 1;
    if ((temp_r3 >= 5) && (lbl_1_bss_38[2].y < 4000.0f)) {
        lbl_1_bss_38[2].y += 25.0f;
    }
    if ((s32) lbl_1_bss_488.unkA4 >= 0xA) {
        lbl_1_bss_38->z -= 20.0f;
        if (lbl_1_bss_38->z < 0.0f) {
            lbl_1_bss_38->z = 0.1f;
        }
        lbl_1_bss_38->y -= 4.0f;
        if (lbl_1_bss_38->y < 250.0f) {
            lbl_1_bss_38->y = 250.0f;
        }
    }
    lbl_1_bss_38[1].y = lbl_1_bss_38[2].y;
    lbl_1_bss_38[1].z = lbl_1_bss_38[2].z;
    Hu3DCameraPosSetV(1, lbl_1_bss_38, &lbl_1_bss_38[1], &lbl_1_bss_38[2]);
    if (var_r30 == 2) {
        memcpy(&lbl_1_bss_488.unkC0[2], lbl_1_bss_488.unkC0, 0xC);
        memcpy(&lbl_1_bss_488.unkC0[3], &lbl_1_bss_488.unkC0[1], 0xC);
        lbl_1_bss_488.unkA0 += 1;
        lbl_1_bss_488.unkA4 = 0;
        Hu3DModelAttrSet(lbl_1_bss_488.unk3C[0xD].unk0, 1U);
        Hu3DModelAttrSet(lbl_1_bss_488.unk3C[0xE].unk0, 1U);
        Hu3DCameraPosSetV(2, &lbl_1_data_280, &lbl_1_data_28C, &lbl_1_data_298);
        lbl_1_bss_488.unkBC = 0;
        lbl_1_bss_488.unkA8 = 0;
        lbl_1_bss_488.unkAC = 3;
        HuAudFXPlay(0x839);
        lbl_1_data_324 = HuAudBGMPlay(0x4B);
    }
}

void fn_1_5DC4(void) {
    s32 temp_r0_2;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r4;
    s32 *temp_r4_2;
    s32 *temp_r4_3;

    if ((s16) lbl_1_bss_2 < 0x64) {
        lbl_1_bss_2 += 1;
    }
    switch ((s32) lbl_1_bss_488.unkA4) {            /* irregular */
    case 0:
        if ((s16) lbl_1_bss_2 == 0xA) {
            var_r31 = 0;
loop_11:
            if (var_r31 < 2) {
                Hu3DModelCameraSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, 2U);
                Hu3DModelAttrReset(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, 1U);
                lbl_1_bss_488.unkC0[var_r31].x = (f32) ((var_r31 * 0xF0) - 0x78);
                lbl_1_bss_488.unkC0[var_r31].y = 80.0f;
                lbl_1_bss_488.unkC0[var_r31].z = -400.0f;
                var_r31 += 1;
                goto loop_11;
            }
            lbl_1_bss_488.unkA4 += 1;
        }
        break;
    case 1:
        lbl_1_bss_488.unkBC += 1;
        temp_r4 = (u32) lbl_1_bss_488.unkBC >> 0x1FU;
        temp_r3 = (lbl_1_bss_488.unkBC << 0x1E) - temp_r4;
        if ((s32) ((lbl_1_bss_488.unkBC % 4)) == 0) {
            var_r31_2 = 0;
loop_18:
            if (var_r31_2 < 2) {
                temp_r4_2 = &lbl_1_bss_488.unkB4[var_r31_2];
                *temp_r4_2 -= 1;
                if ((s32) lbl_1_bss_488.unkB4[var_r31_2] < 0) {
                    lbl_1_bss_488.unkAC -= var_r31_2 + 1;
                    lbl_1_bss_488.unkA4 += 1;
                    lbl_1_data_2A4[1] = var_r31_2;
                    Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31_2 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31_2][4], 0.0f, 10.0f, 0x40000001U);
                }
                var_r31_2 += 1;
                goto loop_18;
            }
        }
        break;
    case 2:
        lbl_1_bss_488.unkBC += 1;
        temp_r3_2 = (u32) lbl_1_bss_488.unkBC >> 0x1FU;
        temp_r0 = (lbl_1_bss_488.unkBC << 0x1E) - temp_r3_2;
        if ((s32) ((lbl_1_bss_488.unkBC % 4)) == 0) {
            var_r31_3 = 0;
loop_26:
            if (var_r31_3 < 2) {
                if ((s32) lbl_1_bss_488.unkB4[var_r31_3] >= 0) {
                    temp_r4_3 = &lbl_1_bss_488.unkB4[var_r31_3];
                    *temp_r4_3 -= 1;
                    if ((s32) lbl_1_bss_488.unkB4[var_r31_3] <= 0) {
                        lbl_1_bss_488.unkAC -= var_r31_3 + 1;
                        lbl_1_data_2A4[0] = var_r31_3;
                        Hu3DTexScrollPosSet(lbl_1_bss_480[1], lbl_1_data_2BC[lbl_1_bss_488.unk4[var_r31_3].unk2].unk0, lbl_1_data_2BC[lbl_1_bss_488.unk4[var_r31_3].unk2].unk4, 0.0f);
                        lbl_1_bss_488.unkA8 = 1;
                        lbl_1_bss_488.unkA4 += 1;
                        lbl_1_bss_24[3] = 1;
                    }
                }
                var_r31_3 += 1;
                goto loop_26;
            }
        }
        break;
    }
    if ((s32) lbl_1_bss_488.unkA8 == 0) {
        Hu3DTexScrollPosSet(lbl_1_bss_480[0], 0.0f, 0.5f - ((0.5f * (f32) (lbl_1_bss_488.unkBC % 25)) / 25.0f), 0.0f);
    }
    var_r31_4 = 0;
loop_34:
    if (var_r31_4 < 2) {
        if ((var_r31_4 != (s32) lbl_1_data_2A4[1]) && (lbl_1_bss_488.unkC0[var_r31_4 + 2].y < 23000.0f)) {
            temp_r0_2 = var_r31_4 + 2;
            lbl_1_bss_488.unkC0[temp_r0_2].y += 80.0f;
        }
        var_r31_4 += 1;
        goto loop_34;
    }
    if (((s32) lbl_1_bss_488.unkA4 < 3) && (lbl_1_bss_464.y < 23000.0f)) {
        lbl_1_bss_464.y += 80.0f;
    }
    if ((s32) (lbl_1_bss_488.unkAC & 1) != 0) {
        lbl_1_bss_488.unkC0[0].y = (f32) (80.0 + (15.0 * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 80) * 0x168) / 80)) / 180.0)));
        lbl_1_bss_488.unkC0[0].z = (f32) (-400.0 + (35.0 * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0)));
    }
    if ((s32) (lbl_1_bss_488.unkAC & 2) != 0) {
        lbl_1_bss_488.unkC0[1].y = (f32) (80.0 - (15.0 * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 80) * 0x168) / 80)) / 180.0)));
        lbl_1_bss_488.unkC0[1].z = (f32) (-400.0 - (35.0 * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0)));
    }
    var_r31_5 = 0;
loop_48:
    if (var_r31_5 < 2) {
        if ((s32) lbl_1_data_2A4[var_r31_5] >= 0) {
            if (var_r31_5 != 0) {
                fn_1_670C(lbl_1_data_2A4[1]);
            } else {
                fn_1_6A88(lbl_1_data_2A4[0]);
            }
        }
        var_r31_5 += 1;
        goto loop_48;
    }
}

void fn_1_670C(s32 player) {
    Vec sp8;
    f32 temp_f31;

    switch ((s32) lbl_1_bss_6D4[0]) {            /* irregular */
    case 0:
        lbl_1_bss_488.unkC0[player].y -= lbl_1_data_33C;
        lbl_1_data_33C = (f32) ((f64) lbl_1_data_33C * 1.05);
        if (lbl_1_bss_488.unkC0[player].y < -250.0f) {
            lbl_1_bss_6D4[0] += 1;
            temp_f31 = (lbl_1_bss_488.unkC0[player + 2].y - 11040.0f) / 12000.0f;
            Hu3DModelCameraSet(lbl_1_bss_488.unk3C[player + 0xD].unk0, 1U);
            Hu3DModelLayerSet(lbl_1_bss_488.unk3C[player + 0xD].unk0, 6);
            memcpy(&lbl_1_bss_488.unkC0[player], &lbl_1_bss_488.unkC0[player + 2], 0xC);
            lbl_1_bss_6D4[1] = 0;
            lbl_1_data_344.unk0 = 0.0f;
            lbl_1_data_344.unk4 = (f32) (0.5 + (0.5 * (f64) temp_f31));
            lbl_1_data_344.unk8 = (f32) (75.0f + (75.0f * temp_f31));
            VECSubtract(&lbl_1_bss_38[2], lbl_1_bss_38, &sp8);
            VECNormalize(&sp8, &sp8);
            HuAudFXListnerSet(lbl_1_bss_38, &sp8, 30000.0f, 1000.0f);
            lbl_1_data_340 = HuAudFXEmiterPlay(0x837, &lbl_1_bss_488.unkC0[player]);
            return;
        }
        return;
    case 1:
        if (lbl_1_bss_488.unkC0[player].y > -2000.0f) {
            lbl_1_data_344.unk0 = (f32) (lbl_1_data_344.unk0 + lbl_1_data_344.unk4);
            lbl_1_bss_488.unkC0[player].y -= lbl_1_data_344.unk8;
            lbl_1_bss_488.unkC0[player].z = lbl_1_data_344.unk0;
            HuAudFXEmiterUpDate(lbl_1_data_340, &lbl_1_bss_488.unkC0[player]);
            return;
        }
        lbl_1_bss_6D4[0] += 1;
        break;
    }
}

void fn_1_6A88(s32 player) {
    s32 temp_r3;

    switch ((s32) lbl_1_bss_6C4[0]) {            /* irregular */
    case 0:
        Hu3DModelAttrReset(lbl_1_bss_488.unk3C[0x16].unk0, 1U);
        lbl_1_bss_6C4[0] += 1;
        lbl_1_bss_698 = (f32) (lbl_1_bss_488.unkBC % 25);
        lbl_1_bss_698 += 1.0f;
        lbl_1_bss_69C = 25.0f;
        lbl_1_bss_6C4[1] = 0;
        lbl_1_bss_6C4[2] = 0;
        break;
    case 1:
        lbl_1_bss_6A0 += 1;
        lbl_1_bss_698 = (f32) ((f64) lbl_1_bss_698 + cos((3.141592653589793 * (f64) ((lbl_1_bss_6A0 * 0x5A) / 60)) / 180.0));
        if ((s32) lbl_1_bss_6A0 >= 0x3C) {
            Hu3DMotionSpeedSet(lbl_1_bss_488.unk3C[0x16].unk0, 2.0f);
            Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[player + 0xD].unk0, lbl_1_bss_488.unk48[player][5], 0.0f, 10.0f, 0x40000001U);
            lbl_1_bss_6C4[0] += 1;
            HuAudSStreamFadeOut(lbl_1_data_324, 0x64);
        }
        break;
    case 2:
        lbl_1_bss_698 -= 0.046875004f;
        if (lbl_1_bss_698 < 0.0f) {
            lbl_1_bss_698 += lbl_1_bss_69C;
        }
        temp_r3 = lbl_1_bss_6C4[2];
        lbl_1_bss_6C4[2] = temp_r3 + 1;
        if (temp_r3 == 0x19) {
            Hu3DMotionSpeedSet(lbl_1_bss_488.unk3C[0x16].unk0, 6.0f);
            HuAudFXPlay(0x838);
        }
        if ((s32) *lbl_1_bss_6D4 >= 2) {
            lbl_1_bss_6C4[1] += 1;
            if ((s32) lbl_1_bss_6C4[1] >= 0x64) {
                MgSeqModeNext();
            }
        }
        break;
    }
    lbl_1_bss_488.unkBC += 1;
    if (lbl_1_bss_698 >= lbl_1_bss_69C) {
        lbl_1_bss_698 -= lbl_1_bss_69C;
    }
    Hu3DTexScrollPosSet(*lbl_1_bss_480, 0.0f, 0.5f - ((0.5f * lbl_1_bss_698) / lbl_1_bss_69C), 0.0f);
    lbl_1_bss_488.unkC0[player].z = (f32) (-400.0 + ((f64) (0x23 - (player * 0x46)) * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0)));
}

void fn_1_6FF4(void) {
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;

    switch ((s32) lbl_1_bss_488.unkA4) {            /* irregular */
    case 0:
        var_r31 = 0;
loop_9:
        if (var_r31 < 2) {
            Hu3DMotionSpeedSet(lbl_1_bss_488.unk3C[var_r31 + 0x17].unk0, 1.0f);
            Hu3DModelAttrReset(lbl_1_bss_488.unk3C[var_r31 + 0x17].unk0, 1U);
            var_r31 += 1;
            goto loop_9;
        }
        lbl_1_bss_488.unkA4 += 1;
        return;
    case 1:
        lbl_1_bss_488.unkB0 += 1;
        lbl_1_bss_488.unkC0[0].y = (f32) ((f64) lbl_1_bss_488.unkC0[0].y + (20.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_488.unkB0 * 0x5A) / 12)) / 180.0)));
        lbl_1_bss_488.unkC0[1].y = (f32) ((f64) lbl_1_bss_488.unkC0[1].y + (20.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_488.unkB0 * 0x5A) / 12)) / 180.0)));
        if ((s32) lbl_1_bss_488.unkB0 == 0xC) {
            var_r31_2 = 0;
loop_14:
            if (var_r31_2 < 2) {
                Hu3DModelAttrSet(lbl_1_bss_488.unk3C[var_r31_2 + 0xF].unk0, 1U);
                var_r31_2 += 1;
                goto loop_14;
            }
            lbl_1_bss_488.unkA4 += 1;
            return;
        }
        return;
    case 2:
        lbl_1_bss_488.unkB0 += 1;
        if ((s32) lbl_1_bss_488.unkB0 > 0x18) {
            lbl_1_bss_488.unkB0 = 0x18;
        }
        lbl_1_bss_488.unkC0[0].y = (f32) ((f64) lbl_1_bss_488.unkC0[0].y + (20.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_488.unkB0 * 0x5A) / 12)) / 180.0)));
        lbl_1_bss_488.unkC0[1].y = (f32) ((f64) lbl_1_bss_488.unkC0[1].y + (20.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_488.unkB0 * 0x5A) / 12)) / 180.0)));
        if (lbl_1_bss_488.unkC0[0].y < 100.0f) {
            var_r31_3 = 0;
loop_21:
            if (var_r31_3 < 2) {
                lbl_1_bss_488.unkC0[var_r31_3].y = 100.0f;
                lbl_1_bss_488.unk50[var_r31_3].unk0 = 2;
                lbl_1_bss_488.unk50[var_r31_3].unk2 = 0;
                var_r31_3 += 1;
                goto loop_21;
            }
            lbl_1_bss_488.unkB0 = 0;
            lbl_1_bss_488.unkA4 += 1;
            return;
        }
        break;
    case 3:
        lbl_1_bss_488.unkB0 += 1;
        if ((s32) lbl_1_bss_488.unkB0 >= 0x18) {
            var_r31_4 = 0;
loop_26:
            if (var_r31_4 < 2) {
                Hu3DMotionShiftSet(lbl_1_bss_488.unk3C[var_r31_4 + 0xD].unk0, lbl_1_bss_488.unk48[var_r31_4][0], 0.0f, 30.0f, 0x40000001U);
                var_r31_4 += 1;
                goto loop_26;
            }
            MgSeqModeNext();
        }
        break;
    }
}

void fn_1_750C(void) {
    lbl_1_bss_698 -= 0.046875004f;
    if (lbl_1_bss_698 < 0.0f) {
        lbl_1_bss_698 += lbl_1_bss_69C;
    }
    Hu3DTexScrollPosSet(*lbl_1_bss_480, 0.0f, 0.5f - ((0.5f * lbl_1_bss_698) / lbl_1_bss_69C), 0.0f);
    lbl_1_bss_488.unkBC += 1;
    lbl_1_bss_488.unkC0[*lbl_1_data_2A4].z = (f32) (-400.0 + ((f64) (0x23 - (*lbl_1_data_2A4 * 0x46)) * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0)));
}

void fn_1_7724(void) {
    if ((s32) *lbl_1_data_2A4 >= 0) {
        lbl_1_bss_698 -= 0.046875004f;
        if (lbl_1_bss_698 < 0.0f) {
            lbl_1_bss_698 += lbl_1_bss_69C;
        }
        Hu3DTexScrollPosSet(*lbl_1_bss_480, 0.0f, 0.5f - ((0.5f * lbl_1_bss_698) / lbl_1_bss_69C), 0.0f);
        lbl_1_bss_488.unkBC += 1;
        lbl_1_bss_488.unkC0[*lbl_1_data_2A4].z = (f32) (-400.0 + ((f64) (0x23 - (*lbl_1_data_2A4 * 0x46)) * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0)));
        lbl_1_bss_2 += 1;
        lbl_1_bss_488.unkA0 = 0;
        if (((s16) lbl_1_bss_488.unk4[*lbl_1_data_2A4].unk4 == 0) && ((s32) lbl_1_bss_24[1] > (s32) lbl_1_bss_34)) {
            lbl_1_bss_488.unkA0 = 2;
        }
    } else {
        lbl_1_bss_488.unkA0 = 1;
    }
    lbl_1_bss_488.unkA4 = 0;
    lbl_1_bss_488.unkB0 = 0;
}

void fn_1_7A08(void) {
    f64 temp_f1;
    s16 temp_r31;

    lbl_1_bss_698 -= 0.046875004f;
    if (lbl_1_bss_698 < 0.0f) {
        lbl_1_bss_698 += lbl_1_bss_69C;
    }
    Hu3DTexScrollPosSet(*lbl_1_bss_480, 0.0f, 0.5f - ((0.5f * lbl_1_bss_698) / lbl_1_bss_69C), 0.0f);
    lbl_1_bss_488.unkBC += 1;
    temp_f1 = (f64) (0x23 - (*lbl_1_data_2A4 * 0x46)) * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0);
    lbl_1_bss_488.unkC0[*lbl_1_data_2A4].z = (f32) (-400.0 + temp_f1);
    lbl_1_bss_2 += 1;
    lbl_1_bss_488.unkB0 += 1;
    if (((s32) lbl_1_bss_488.unkA4 == 0) && ((s32) lbl_1_bss_488.unkB0 > 0x1E)) {
        lbl_1_bss_6A4 = MGSeqWinCreate(lbl_1_bss_488.unk4[*lbl_1_data_2A4].unk2, -1, -1, -1);
        HuAudJinglePlay(0x79);
        CharFXPlay(lbl_1_bss_488.unk4[*lbl_1_data_2A4].unk2, 0x1FA);
        lbl_1_bss_488.unkA4 = 1;
        lbl_1_bss_488.unkB0 = 0;
        temp_r31 = lbl_1_bss_488.unk4[*lbl_1_data_2A4].unk0;
        if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
            GWPlayer[temp_r31].coin_win = 0xA;
        }
    } else if ((GameMesStatGet(lbl_1_bss_6A4) == 0) && ((s32) lbl_1_bss_488.unkB0 >= 0xD2)) {
        GameMesKill(lbl_1_bss_6A4);
        MgSeqModeNext();
    }
}

void fn_1_7DAC(void) {
    s32 var_r31;

    lbl_1_bss_488.unkB0 += 1;
    if (((s32) lbl_1_bss_488.unkA4 == 0) && ((s32) lbl_1_bss_488.unkB0 > 0x1E)) {
        var_r31 = 0;
loop_4:
        if (var_r31 < 2) {
            lbl_1_bss_488.unk50[var_r31].unk0 = 6;
            lbl_1_bss_488.unk50[var_r31].unk2 = 0;
            lbl_1_bss_488.unk50[var_r31].unk20 = 0x40000001;
            var_r31 += 1;
            goto loop_4;
        }
        lbl_1_bss_6A4 = MGSeqDrawCreate();
        HuAudJinglePlay(0x7B);
        lbl_1_bss_488.unkA4 += 1;
        lbl_1_bss_488.unkB0 = 0;
        CharFXPlayPan(lbl_1_bss_488.unk4[0].unk2, 0x200, 0x30);
        CharFXPlayPan(lbl_1_bss_488.unk4[1].unk2, 0x200, 0x50);
        return;
    }
    if ((GameMesStatGet(lbl_1_bss_6A4) == 0) && ((s32) lbl_1_bss_488.unkB0 >= 0xD2)) {
        GameMesKill(lbl_1_bss_6A4);
        MgSeqModeNext();
    }
}

void fn_1_7F2C(void) {
    f64 temp_f1;

    lbl_1_bss_488.unkB0 += 1;
    lbl_1_bss_698 -= 0.046875004f;
    if (lbl_1_bss_698 < 0.0f) {
        lbl_1_bss_698 += lbl_1_bss_69C;
    }
    Hu3DTexScrollPosSet(*lbl_1_bss_480, 0.0f, 0.5f - ((0.5f * lbl_1_bss_698) / lbl_1_bss_69C), 0.0f);
    lbl_1_bss_488.unkBC += 1;
    temp_f1 = (f64) (0x23 - (*lbl_1_data_2A4 * 0x46)) * sin((3.141592653589793 * (f64) (((lbl_1_bss_488.unkBC % 160) * 0x168) / 160)) / 180.0);
    lbl_1_bss_488.unkC0[*lbl_1_data_2A4].z = (f32) (-400.0 + temp_f1);
    lbl_1_bss_2 += 1;
    if (((s32) lbl_1_bss_488.unkA4 == 0) && ((s32) lbl_1_bss_488.unkB0 > 0x1E)) {
        lbl_1_bss_6A4 = GameMesCreate(0xE, lbl_1_bss_24[1], temp_f1);
        GWMgRecordSet(7, (u32) lbl_1_bss_24[1]);
        lbl_1_bss_488.unkA4 += 1;
        lbl_1_bss_24[0] += 1;
        if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
            HuAudJinglePlay(0x86);
            return;
        }
        lbl_1_bss_488.unkB0 = 0x96;
        return;
    }
    if ((GameMesStatGet(lbl_1_bss_6A4) == 0) && ((s32) lbl_1_bss_488.unkB0 >= 0x96)) {
        GameMesKill(lbl_1_bss_6A4);
        lbl_1_bss_488.unkA0 = 0;
        lbl_1_bss_488.unkA4 = 0;
    }
}

void fn_1_8298(void) {
    M547Fall *temp_r4;
    f32 temp_f31;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
    var_r30 = 0;
loop_4:
    if (var_r31 < 2) {
        if ((s32) lbl_1_bss_488.unkB4[var_r31] > 0xA) {
            var_r30 += 1;
        }
        var_r31 += 1;
        goto loop_4;
    }
    var_r31_2 = 0;
loop_16:
    if (var_r31_2 < 2) {
        if ((s32) lbl_1_bss_430[var_r31_2] == 0) {
            if ((s32) lbl_1_bss_430[2] <= 0) {
                lbl_1_bss_430[2] = (rand8() % 50) + 0x64;
                lbl_1_bss_440[var_r31_2].unk4 = 1000.0f;
                Hu3DModelAttrReset(lbl_1_bss_488.unk3C[var_r31_2 + 0x1B].unk0, 1U);
                lbl_1_bss_440[var_r31_2].unk8 = (f32) (-0x28 - (rand8() % 20));
                lbl_1_bss_430[var_r31_2] = 1;
                temp_f31 = (f32) (rand8() % 10);
                Hu3DModelScaleSet(lbl_1_bss_488.unk3C[var_r31_2 + 0x1B].unk0, (f32) (0.5 + ((0.5 * (f64) temp_f31) / 10.0)), (f32) (0.5 + ((0.5 * (f64) temp_f31) / 10.0)), (f32) (0.5 + ((0.5 * (f64) temp_f31) / 10.0)));
                if (var_r31_2 != 0) {
                    lbl_1_bss_440[var_r31_2].unk0 = (f32) ((rand8() % 40) + 0x3C);
                } else {
                    lbl_1_bss_440[var_r31_2].unk0 = (f32) (-0x3C - (rand8() % 40));
                }
            } else if (var_r30 != 0) {
                lbl_1_bss_430[2] -= 1;
            }
        } else {
            temp_r4 = &lbl_1_bss_440[var_r31_2];
            temp_r4->unk4 -= 40.0f;
            if (lbl_1_bss_440[var_r31_2].unk4 < -600.0f) {
                lbl_1_bss_430[var_r31_2] = 0;
                Hu3DModelAttrSet(lbl_1_bss_488.unk3C[var_r31_2 + 0x1B].unk0, 1U);
            }
        }
        var_r31_2 += 1;
        goto loop_16;
    }
}



void ObjectSetup(void) {
    fn_1_86B8(&lbl_1_bss_488, lbl_1_bss_E8, lbl_1_data_0);
    lbl_1_bss_488.unk0 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_488.unk0);
    lbl_1_bss_484 = omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, omOutViewMulti);
    lbl_1_bss_484->work[0] = 2;
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_8D2C);
    MgSeqCreate(&lbl_1_data_1D0);
}

void fn_1_17C(s16 arg0, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    s16 sp8;
    s16 temp_r3;
    s32 var_r31;

    sp8 = arg0;
    fn_1_8904(1);
    fn_1_8B9C(&lbl_1_data_64[lbl_1_bss_488.unk4[0].unk2], &lbl_1_data_64[lbl_1_bss_488.unk4[1].unk2]);
    fn_1_8BC0(lbl_1_bss_5C[0], lbl_1_bss_5C[1]);
    fn_1_8BE4();
    fn_1_2CE4();
    fn_1_376C();
    Hu3DModelPosSet(lbl_1_bss_488.unk3C[0xD].unk0, -150.0f, 800.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_488.unk3C[0xE].unk0, 150.0f, 800.0f, 0.0f);
    lbl_1_bss_488.unkC0[0].x = -150.0f;
    lbl_1_bss_488.unkC0[0].y = 800.0f;
    lbl_1_bss_488.unkC0[0].z = 0.0f;
    lbl_1_bss_488.unkC0[1].x = 150.0f;
    lbl_1_bss_488.unkC0[1].y = 800.0f;
    lbl_1_bss_488.unkC0[1].z = 0.0f;
    fn_1_91E8();
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_933C);
    CenterM->x = 0.0f;
    CenterM->y = 275.0f;
    CenterM->z = 0.0f;
    CRotM->x = -40.0f;
    CRotM->y = 0.0f;
    CRotM->z = 0.0f;
    CZoomM[0] = 1000.0f;
    lbl_1_bss_78->center.x = 0.0f;
    lbl_1_bss_78->center.y = 275.0f;
    lbl_1_bss_78->center.z = 0.0f;
    lbl_1_bss_78->rot.x = -20.0f;
    lbl_1_bss_78->rot.y = 0.0f;
    lbl_1_bss_78->rot.z = 0.0f;
    lbl_1_bss_78->zoom = 600.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 100.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 500.0f;
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    Hu3DCameraPerspectiveSet(2, 45.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 360.0f, 256.0f, 240.0f, 180.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0x140U, 0xF0U, 0U, 0U);
    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_954C);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_E88);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_10D0);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_1544);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_2678);
    omAddObjEx(lbl_1_bss_488.unk0, 0x7FDA, 0U, 0U, -1, fn_1_3ADC);
    Hu3DBGColorSet(0xBAU, 0xF5U, 0xFFU);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    sp24.x = 0.0f;
    sp24.y = 1500.0f;
    sp24.z = 250.0f;
    sp18.x = 0.0f;
    sp18.y = 1.0f;
    sp18.z = 0.0f;
    spC.x = 0.0f;
    spC.y = 100.0f;
    spC.z = 0.0f;
    Hu3DShadowTPLvlSet(0.25f);
    Hu3DModelShadowSet(lbl_1_bss_488.unk3C[0xD].unk0);
    Hu3DModelShadowSet(lbl_1_bss_488.unk3C[0xE].unk0);
    Hu3DModelShadowMapSet(lbl_1_bss_488.unk3C->unk0);
    Hu3DModelShadowMapSet(lbl_1_bss_488.unk3C[0xF].unk0);
    Hu3DModelShadowMapSet(lbl_1_bss_488.unk3C[0x10].unk0);
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    lbl_1_bss_488.unk50[0].unk0 = 2;
    lbl_1_bss_488.unk50[0].unk4 = 0.0f;
    lbl_1_bss_488.unk50[0].unkC = 0.0f;
    lbl_1_bss_488.unk50[0].unk20 = 0x40000001;
    lbl_1_bss_488.unk50[1].unk0 = 2;
    lbl_1_bss_488.unk50[1].unk4 = 0.0f;
    lbl_1_bss_488.unk50[1].unkC = 0.0f;
    lbl_1_bss_488.unk50[1].unk20 = 0x40000001;
    lbl_1_bss_34 = GWMgRecordGet(7);
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        lbl_1_bss_430[var_r31] = 0;
        lbl_1_bss_24[var_r31] = 0;
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_430[2] = (rand8() % 50) + 0x64;
    Hu3DZClearLayerSet(0xE);
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    MgSeqModeNext();
    fn_1_162C();
}

void fn_1_A84(s16 mode, s16 frameNo) {
    lbl_1_data_1F8[lbl_1_bss_488.unkA0]();
    fn_1_4094();
}

void fn_1_ACC(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    lbl_1_bss_488.unkA0 = 0;
    lbl_1_bss_488.unkA4 = 0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    fn_1_4094();
}

void fn_1_B24(s16 arg1, s16 frameNo) {
    s16 sp8;
    s32 temp_r0;
    u32 temp_r3;

    sp8 = frameNo;
    lbl_1_data_200[lbl_1_bss_488.unkA0]();
    if ((s16) lbl_1_bss_2 >= 0x28) {
        temp_r0 = sp8 / 16;
        temp_r3 = (u32) temp_r0 >> 0x1FU;
        if ((s32) (((temp_r0 & 1) ^ temp_r3) - temp_r3) != 0) {
            espPosSet(lbl_1_bss_470[6], 350.0f, 416.0f);
        } else {
            espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
        }
    }
    if ((s16) lbl_1_bss_2 < 0x64) {
        fn_1_162C();
    }
    if ((s16) lbl_1_bss_2 > 0x64) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_231C();
    if ((s16) lbl_1_bss_2 != 0) {
        fn_1_23A8();
    }
    fn_1_4094();
}

void fn_1_C70(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    fn_1_7724();
    if ((s16) lbl_1_bss_2 > 0x64) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_23A8();
    fn_1_4094();
}

void fn_1_CF0(s16 mode, s16 frameNo) {
    lbl_1_data_214[lbl_1_bss_488.unkA0]();
    if ((s16) lbl_1_bss_2 > 0x64) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_23A8();
    fn_1_4094();
}

void fn_1_D7C(s16 mode, s16 frameNo) {
    fn_1_750C();
    fn_1_23A8();
    fn_1_4094();
    MgSeqModeNext();
}

void fn_1_DA8(s16 mode, s16 frameNo) {
    fn_1_750C();
    fn_1_23A8();
    fn_1_4094();
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

void fn_1_DE4(s16 mode, s16 frameNo) {

}


void fn_1_E88(omObjData *obj) {
    f32 sp8[13];
    s32 var_r31;
    s32 *temp_r4;

    sp8[0] = lbl_1_rodata_90[0];
    sp8[1] = lbl_1_rodata_90[1];
    sp8[2] = lbl_1_rodata_90[2];
    sp8[3] = lbl_1_rodata_90[3];
    sp8[4] = lbl_1_rodata_90[4];
    sp8[5] = lbl_1_rodata_90[5];
    sp8[6] = lbl_1_rodata_90[6];
    sp8[7] = lbl_1_rodata_90[7];
    sp8[8] = lbl_1_rodata_90[8];
    sp8[9] = lbl_1_rodata_90[9];
    sp8[10] = lbl_1_rodata_90[0xA];
    sp8[11] = lbl_1_rodata_90[0xB];
    sp8[12] = lbl_1_rodata_90[0xC];
    var_r31 = 0;
loop_11:
    if (var_r31 < 2) {
        Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31 + 0xD].unk0, lbl_1_bss_488.unkC0[var_r31].x, lbl_1_bss_488.unkC0[var_r31].y, lbl_1_bss_488.unkC0[var_r31].z);
        if (((s32) lbl_1_bss_488.unkB0 != 0) && (MgSeqModeGet() == 5)) {
            if ((s16) lbl_1_bss_488.unk4[var_r31].unk4 != 0) {
                fn_1_243C(var_r31, (s16) (lbl_1_bss_488.unk4[var_r31].unk4 - 1));
            }
            if (((s32) (lbl_1_bss_488.unk4[var_r31].unkC & 0x100) != 0) && ((s32) lbl_1_bss_488.unkB4[var_r31] < 0xC8)) {
                temp_r4 = &lbl_1_bss_488.unkB4[var_r31];
                *temp_r4 += 1;
            }
        }
        if ((s32) *lbl_1_data_2A4 == var_r31) {
            Hu3DModelPosSet(lbl_1_bss_488.unk3C[0x16].unk0, lbl_1_bss_488.unkC0[var_r31].x, lbl_1_bss_488.unkC0[var_r31].y + sp8[lbl_1_bss_488.unk4[var_r31].unk2], lbl_1_bss_488.unkC0[var_r31].z);
        }
        var_r31 += 1;
        goto loop_11;
    }
}

void fn_1_10D0(omObjData *obj) {
    f32 var_f31;
    f32 var_f31_2;
    s32 var_r31;
    s32 var_r31_2;

    if (MgSeqModeGet() == 5) {
        if ((s32) lbl_1_bss_488.unkA0 == 2) {
            var_r31 = 0;
loop_12:
            if (var_r31 < 2) {
                Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31 + 0x12].unk0, lbl_1_bss_488.unkC0[var_r31].x, lbl_1_bss_488.unkC0[var_r31].y, lbl_1_bss_488.unkC0[var_r31].z);
                var_f31 = 1.0f;
                if (lbl_1_bss_488.unkC0[var_r31].y >= 7500.0f) {
                    var_f31 = (f32) (1.0 - (f64) ((lbl_1_bss_488.unkC0[var_r31].y - 7500.0f) / 2500.0f));
                }
                if (lbl_1_bss_488.unkC0[var_r31].y == 10000.0f) {
                    var_f31 = 0.0f;
                }
                if (var_f31 > 1.0f) {
                    var_f31 = 1.0f;
                }
                if (var_f31 < 0.0f) {
                    var_f31 = 0.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_488.unk3C[var_r31 + 0x12].unk0, (f32) (0.5 + (0.30000001192092896 * (1.0 - (f64) var_f31))), (f32) (0.5 + (0.30000001192092896 * (1.0 - (f64) var_f31))), (f32) (0.5 + (0.30000001192092896 * (1.0 - (f64) var_f31))));
                fn_1_21BC(var_r31, var_f31);
                var_r31 += 1;
                goto loop_12;
            }
        }
        if ((s32) lbl_1_bss_488.unkA0 == 3) {
            var_r31_2 = 0;
loop_26:
            if (var_r31_2 < 2) {
                if ((var_r31_2 != (s32) lbl_1_data_2A4[0]) && (var_r31_2 != (s32) lbl_1_data_2A4[1])) {
                    Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31_2 + 0x12].unk0, lbl_1_bss_488.unkC0[var_r31_2 + 2].x, lbl_1_bss_488.unkC0[var_r31_2 + 2].y, lbl_1_bss_488.unkC0[var_r31_2 + 2].z);
                } else if ((var_r31_2 == (s32) lbl_1_data_2A4[1]) && ((s32) *lbl_1_bss_6D4 == 1)) {
                    Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31_2 + 0x12].unk0, lbl_1_bss_488.unkC0[var_r31_2 + 2].x, lbl_1_bss_488.unkC0[var_r31_2].y, lbl_1_bss_488.unkC0[var_r31_2].z);
                    var_f31_2 = 1.0f;
                    if (lbl_1_bss_488.unkC0[var_r31_2].y >= 7500.0f) {
                        var_f31_2 = (f32) (1.0 - (f64) ((lbl_1_bss_488.unkC0[var_r31_2].y - 7500.0f) / 2500.0f));
                    }
                    if (lbl_1_bss_488.unkC0[var_r31_2].y > 10000.0f) {
                        var_f31_2 = 0.0f;
                    }
                    fn_1_21BC(var_r31_2, var_f31_2);
                }
                var_r31_2 += 1;
                goto loop_26;
            }
        }
    }
}

void fn_1_1544(omObjData *obj) {
    s16 temp_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        temp_r30 = lbl_1_bss_488.unk3C[var_r31 + 0xF].unk0;
        if (lbl_1_bss_488.unkC0[var_r31].y >= 200.0f) {
            Hu3DMotionTimeSet(temp_r30, 0.0f);
        } else {
            Hu3DMotionTimeSet(temp_r30, 2.0f * (200.0f - lbl_1_bss_488.unkC0[var_r31].y));
        }
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_162C(void) {
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    f32 var_f31_2;
    s16 var_r29;
    s16 var_r31;
    s16 var_r31_2;
    s32 var_r30;
    u32 temp_r3;

    fn_1_223C(lbl_1_bss_2);
    if ((s16) lbl_1_bss_2 > 0xA) {
        var_r31 = 0xA;
    } else {
        var_r31 = lbl_1_bss_2;
    }
    var_f31 = (f32) (((var_r31 * 0xF0) / 10) + 1);
    var_f29 = (576.0f * ((1.5f * (f32) var_r31) / 10.0f)) / 640.0f;
    if ((s16) lbl_1_bss_2 < 0xA) {
        var_r31_2 = 0;
    } else if ((s16) lbl_1_bss_2 > 0x14) {
        var_r31_2 = 0xA;
    } else {
        var_r31_2 = lbl_1_bss_2 - 0xA;
    }
    var_f30 = (f32) (((var_r31_2 * 0xB4) / 10) + 3);
    var_f28 = (f32) ((1.5 * (f64) var_r31_2) / 10.0);
    if ((s16) lbl_1_bss_2 == 0) {
        var_f28 = 0.0f;
        var_f29 = 0.0f;
        var_f30 = 0.0f;
        var_f31 = 0.0f;
    }
    espPosSet(lbl_1_bss_470[0], 0.9f * (480.0f + (var_f31 * 0.5f)), 346.0f);
    espPosSet(lbl_1_bss_470[1], 0.9f * (480.0f - (var_f31 * 0.5f)), 346.0f);
    espPosSet(lbl_1_bss_470[2], 432.0f, 346.0f + (var_f30 * 0.5f));
    espPosSet(lbl_1_bss_470[3], 432.0f, 346.0f - (var_f30 * 0.5f));
    var_r30 = 0;
loop_15:
    if (var_r30 < 4) {
        if (var_r30 < 2) {
            espScaleSet(lbl_1_bss_470[var_r30], 1.0f, var_f30 / 480.0f);
        } else {
            espScaleSet(lbl_1_bss_470[var_r30], var_f31 / 640.0f, 1.0f);
        }
        var_r30 += 1;
        goto loop_15;
    }
    temp_r3 = (u32) lbl_1_bss_2 >> 0x1FU;
    if ((s32) (((lbl_1_bss_2 & 1) ^ temp_r3) - temp_r3) != 0) {
        var_r29 = 5;
    } else {
        var_r29 = 4;
    }
    espPosSet(lbl_1_bss_470[var_r29], 432.0f, 346.0f);
    espScaleSet(lbl_1_bss_470[var_r29], var_f29, var_f28);
    espScaleSet(lbl_1_bss_470[var_r29 ^ 1], 0.0f, 0.0f);
    if (((s16) lbl_1_bss_2 >= 0x1E) && ((s16) lbl_1_bss_2 <= 0x5A)) {
        var_f31_2 = 1.0f - ((f32) (lbl_1_bss_2 - 0x1E) / 60.0f);
        if ((s16) lbl_1_bss_2 > 0x5A) {
            var_f31_2 = 0.0f;
        }
        espTPLvlSet(lbl_1_bss_470[var_r29], var_f31_2);
    }
}

void fn_1_1BA8(void) {
    s16 var_r31;
    s32 var_r30;
    u32 temp_r26;
    u32 temp_r27;
    u32 temp_r28;
    u32 temp_r29;

    var_r31 = lbl_1_bss_2 - 0x65;
    if (var_r31 > 0x3C) {
        var_r31 = 0x3C;
    }
    temp_r27 = ((var_r31 * 0x190) / 60) + 0xF0;
    temp_r26 = ((var_r31 * 0x12C) / 60) + 0xB4;
    temp_r29 = 0x168 - ((var_r31 * 0x168) / 60);
    temp_r28 = 0x100 - ((var_r31 << 8) / 60);
    Hu3DCameraScissorSet(2, temp_r29, temp_r28, temp_r27, temp_r26);
    Hu3DCameraViewportSet(2, (f32) temp_r29, (f32) temp_r28, (f32) temp_r27, (f32) temp_r26, 0.0f, 1.0f);
    espPosSet(lbl_1_bss_470[0], 0.9f * (f32) (temp_r29 + temp_r27), (f32) (temp_r28 + (temp_r26 >> 1U)));
    espPosSet(lbl_1_bss_470[1], 0.9f * (f32) temp_r29, (f32) (temp_r28 + (temp_r26 >> 1U)));
    espPosSet(lbl_1_bss_470[2], 0.9f * (f32) (temp_r29 + (temp_r27 >> 1U)), (f32) (temp_r28 + temp_r26));
    espPosSet(lbl_1_bss_470[3], 0.9f * (f32) (temp_r29 + (temp_r27 >> 1U)), (f32) temp_r28);
    lbl_1_data_280.x = (f32) ((var_r31 * (0x78 - (lbl_1_data_2A4[1] * 0xF0))) / 60);
    lbl_1_data_298.x = (f32) ((var_r31 * (0x78 - (lbl_1_data_2A4[1] * 0xF0))) / 60);
    lbl_1_data_280.y = 200.0f + (((lbl_1_bss_488.unkC0[lbl_1_data_2A4[0]].y - 100.0f) * (f32) var_r31) / 60.0f);
    lbl_1_data_298.y = 200.0f + (((lbl_1_bss_488.unkC0[lbl_1_data_2A4[0]].y - 100.0f) * (f32) var_r31) / 60.0f);
    Hu3DCameraPosSetV(2, &lbl_1_data_280, &lbl_1_data_28C, &lbl_1_data_298);
    var_r30 = 0;
loop_7:
    if (var_r30 < 4) {
        if (var_r30 < 2) {
            espScaleSet(lbl_1_bss_470[var_r30], 1.0f, (f32) temp_r26 / 480.0f);
        } else {
            espScaleSet(lbl_1_bss_470[var_r30], (f32) temp_r27 / 640.0f, 1.0f);
        }
        var_r30 += 1;
        goto loop_7;
    }
}

void fn_1_21BC(s32 player, f32 alpha) {
    HSFMATERIAL *var_r30;
    HU3DMODEL *temp_r31;
    s32 var_r29;

    temp_r31 = &Hu3DData[lbl_1_bss_488.unk3C[player + 0x12].unk0];
    var_r30 = temp_r31->hsf->material;
    var_r29 = 0;
loop_2:
    if (var_r29 < (s16) temp_r31->hsf->materialNum) {
        var_r30->invAlpha = alpha;
        var_r29 += 1;
        var_r30++;
        goto loop_2;
    }
}

void fn_1_223C(s16 arg0) {
    u32 var_r28;
    u32 var_r29;
    u32 var_r30;
    u32 var_r31;

    if (arg0 < 0xA) {
        var_r31 = (arg0 * 0xF0) / 10;
        var_r29 = 0x1E0 - ((arg0 * 0xF0) / 20);
        var_r28 = 0x159;
        var_r30 = 2;
    } else if (arg0 < 0x14) {
        var_r29 = 0x168;
        var_r31 = 0xF0;
        var_r30 = (((arg0 - 0xA) * 0xB4) / 10) + 2;
        var_r28 = 0x15A - (var_r30 >> 1U);
    } else {
        var_r29 = 0x168;
        var_r31 = 0xF0;
        var_r28 = 0x100;
        var_r30 = 0xB4;
    }
    Hu3DCameraScissorSet(2, var_r29, var_r28, var_r31, var_r30);
}

void fn_1_231C(void) {
    Hu3DModelPosSet(lbl_1_bss_488.unk3C[0x14].unk0, lbl_1_bss_464.x, lbl_1_bss_464.y, lbl_1_bss_464.z);
    Hu3DModelRotSet(lbl_1_bss_488.unk3C[0x14].unk0, lbl_1_bss_458.x, lbl_1_bss_458.y, lbl_1_bss_458.z);
}

void fn_1_23A8(void) {
    s32 var_r31;

    fn_1_8298();
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        Hu3DModelPosSet(lbl_1_bss_488.unk3C[var_r31 + 0x1B].unk0, lbl_1_bss_440[var_r31].unk0, lbl_1_bss_440[var_r31].unk4, lbl_1_bss_440[var_r31].unk8);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_243C(s32 player, s16 arg1) {
    s32 sp8[4];
    struct _struct_lbl_1_data_248_0x8 *temp_r4;

    sp8[0] = lbl_1_rodata_130[0];
    sp8[1] = lbl_1_rodata_130[1];
    sp8[2] = lbl_1_rodata_130[2];
    sp8[3] = lbl_1_rodata_130[3];
    if ((s32) lbl_1_data_240[player] == 0) {
        if (arg1 == 3) {
            lbl_1_data_240[player] = (rand8() % 15) + sp8[arg1];
        } else {
            lbl_1_data_240[player] = (rand8() % 20) + sp8[arg1];
        }
        lbl_1_data_248[player].unk0 = 0x258 / (s32) lbl_1_data_240[player];
    }
    temp_r4 = &lbl_1_data_248[player];
    temp_r4->unk4 += 1;
    if ((s32) lbl_1_data_248[player].unk4 >= (s32) lbl_1_data_248[player].unk0) {
        lbl_1_data_248[player].unk4 = 0;
        if ((s32) lbl_1_bss_488.unkB4[player] < (s32) lbl_1_data_240[player]) {
            lbl_1_bss_488.unk4[player].unkC = 0x100;
        }
    }
}

void fn_1_2648(s32 player) {
    lbl_1_bss_488.unkB4[player] = (s32) lbl_1_data_240[player];
}

void fn_1_2678(omObjData *obj) {
    switch ((s32) lbl_1_bss_24[0]) {             /* irregular */
    case 0:
        lbl_1_bss_20 = MgScoreWinCreate(0x8C, 0x30);
        MgScoreWinPosSet(lbl_1_bss_20, 288.0f, 68.0f);
        MgScoreWinTPLvlSet(lbl_1_bss_20, 0.7f);
        MgScoreWinColorSet(lbl_1_bss_20, 0U, 0U, 0U);
        lbl_1_bss_1C = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 53), 0);
        MgScoreMaxDigitSet(lbl_1_bss_1C, 3);
        MgScoreValueSet(lbl_1_bss_1C, lbl_1_bss_34);
        MgScoreColorSet(lbl_1_bss_1C, 0x42U, 0xFFU, 0x7AU);
        MgScorePosSet(lbl_1_bss_1C, 259.0f, 60.0f);
        espPosSet(lbl_1_bss_470[7], 238.0f, 60.0f);
        lbl_1_bss_18 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 53), 0);
        MgScoreMaxDigitSet(lbl_1_bss_18, 3);
        MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
        MgScoreColorSet(lbl_1_bss_18, 0xFFU, 0xFFU, 0xFFU);
        MgScorePosSet(lbl_1_bss_18, 259.0f, 76.0f);
        lbl_1_bss_24[2] = 0;
        lbl_1_bss_24[1] = 0;
        lbl_1_bss_24[0] = 0x63;
        return;
    case 1:
        if ((s32) lbl_1_bss_24[3] == 0) {
            lbl_1_bss_24[1] += 1;
        }
        MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
        return;
    case 2:
        MgScoreValueSet(lbl_1_bss_1C, lbl_1_bss_24[1]);
        MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
        lbl_1_bss_24[0] = 3;
        lbl_1_bss_24[2] = 0;
        lbl_1_bss_24[3] = 0;
        return;
    case 3:
        if ((s32) lbl_1_bss_24[2] == 0) {
            lbl_1_bss_24[3] += 1;
            MgScoreDigitScaleSet(lbl_1_bss_1C, 1.0f + (0.02f * (f32) lbl_1_bss_24[3]), 1.0f + (0.02f * (f32) lbl_1_bss_24[3]));
            espScaleSet(lbl_1_bss_470[7], 1.0f + (0.02f * (f32) lbl_1_bss_24[3]), 1.0f + (0.02f * (f32) lbl_1_bss_24[3]));
            if ((s32) lbl_1_bss_24[3] == 0xA) {
                lbl_1_bss_24[2] = 1;
                lbl_1_bss_24[3] = 0;
                return;
            }
        } else {
            lbl_1_bss_24[3] += 1;
            MgScoreDigitScaleSet(lbl_1_bss_1C, 1.2f - (0.04f * (f32) lbl_1_bss_24[3]), 1.2f - (0.04f * (f32) lbl_1_bss_24[3]));
            espScaleSet(lbl_1_bss_470[7], 1.2f - (0.04f * (f32) lbl_1_bss_24[3]), 1.2f - (0.04f * (f32) lbl_1_bss_24[3]));
            if ((s32) lbl_1_bss_24[3] == 5) {
                lbl_1_bss_24[2] = 0;
                lbl_1_bss_24[3] = 0;
            }
            return;
        }
        break;
    }
}

void fn_1_2CE4(void) {
    HSFMATERIAL *var_r29;
    HU3DMODEL *temp_r28;
    s16 temp_r3;
    s16 temp_r3_10;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r3_9;
    s16 var_r31;
    s16 var_r31_2;
    s32 var_r27;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;

    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_488.unk3C[var_r30 + 0xF].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelPosSet(temp_r3, -150.0f + (300.0f * (f32) var_r30), 100.0f, 5.0f);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DMotionSpeedSet(temp_r3, 0.0f);
        Hu3DModelAttrReset(temp_r3, 1U);
        var_r30 += 1;
        goto loop_2;
    }
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_488.unk3C[0x11].unk0 = temp_r3_2;
    Hu3DModelAttrSet(temp_r3_2, 1U);
    Hu3DModelPosSet(temp_r3_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(temp_r3_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(temp_r3_2, 2U);
    Hu3DModelAttrReset(temp_r3_2, 1U);
    lbl_1_bss_480[0] = Hu3DTexScrollCreate(temp_r3_2, "m547sky01");
    var_r30_2 = 0;
loop_8:
    if (var_r30_2 < 2) {
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[var_r30_2 + 2], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_488.unk3C[var_r30_2 + 0x12].unk0 = temp_r3_3;
        Hu3DModelAttrSet(temp_r3_3, 1U);
        Hu3DModelPosSet(temp_r3_3, -150.0f + (300.0f * (f32) var_r30_2), 250.0f, 0.0f);
        Hu3DModelRotSet(temp_r3_3, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(temp_r3_3, 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(temp_r3_3, 1U);
        Hu3DModelLayerSet(temp_r3_3, 7);
        Hu3DModelAttrReset(temp_r3_3, 1U);
        temp_r28 = &Hu3DData[lbl_1_bss_488.unk3C[var_r30_2 + 0x12].unk0];
        var_r29 = temp_r28->hsf->material;
        var_r27 = 0;
loop_6:
        if (var_r27 < (s16) temp_r28->hsf->materialNum) {
            var_r29->invAlpha = 1.0f;
            var_r27 += 1;
            var_r29++;
            goto loop_6;
        }
        var_r30_2 += 1;
        goto loop_8;
    }
    var_r30_3 = 0;
loop_14:
    if (var_r30_3 < 2) {
        temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[var_r30_3 + 4], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_488.unk3C[var_r30_3 + 0x14].unk0 = temp_r3_4;
        Hu3DModelAttrSet(temp_r3_4, 1U);
        Hu3DModelRotSet(temp_r3_4, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(temp_r3_4, 1U);
        if (var_r30_3 != 0) {
            Hu3DModelPosSet(temp_r3_4, 0.0f, 0.0f, 0.0f);
            Hu3DModelHookSet(lbl_1_bss_488.unk3C[0x14].unk0, "itemhook_sao", temp_r3_4);
        } else {
            lbl_1_bss_464.x = 2000.0f;
            Hu3DModelPosSet(temp_r3_4, 2000.0f, 0.0f, 0.0f);
            lbl_1_bss_0 = Hu3DJointMotion(temp_r3_4, HuDataSelHeapReadNum(lbl_1_data_60, MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DMotionSet(temp_r3_4, lbl_1_bss_0);
            Hu3DMotionSpeedSet(temp_r3_4, 1.0f);
            Hu3DModelAttrSet(temp_r3_4, 0x40000001U);
        }
        Hu3DModelAttrReset(temp_r3_4, 1U);
        var_r30_3 += 1;
        goto loop_14;
    }
    temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_488.unk3C[0x16].unk0 = temp_r3_5;
    Hu3DModelAttrSet(temp_r3_5, 1U);
    Hu3DModelPosSet(temp_r3_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(temp_r3_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(temp_r3_5, 2U);
    Hu3DMotionSpeedSet(temp_r3_5, 0.0f);
    Hu3DMotionTimeSet(temp_r3_5, 0.0f);
    Hu3DModelAttrReset(temp_r3_5, 0x40000001U);
    lbl_1_bss_480[1] = Hu3DTexScrollCreate(temp_r3_5, lbl_1_data_26F);
    var_r30_4 = 0;
loop_20:
    if (var_r30_4 < 2) {
        if (var_r30_4 == 0) {
            temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
            lbl_1_bss_488.unk3C[0x17].unk0 = temp_r3_6;
            var_r31 = temp_r3_6;
        } else {
            temp_r3_7 = Hu3DModelLink(lbl_1_bss_488.unk3C[0x17].unk0);
            lbl_1_bss_488.unk3C[0x18].unk0 = temp_r3_7;
            var_r31 = temp_r3_7;
        }
        Hu3DModelAttrSet(var_r31, 1U);
        Hu3DModelPosSet(var_r31, -130.0f + (260.0f * (f32) var_r30_4), 180.0f, 85.0f);
        Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(var_r31, 1U);
        Hu3DMotionSpeedSet(var_r31, 0.0f);
        Hu3DModelAttrReset(var_r31, 0x40000001U);
        Hu3DModelScaleSet(var_r31, 1.9f, 1.6f, 1.5f);
        var_r30_4 += 1;
        goto loop_20;
    }
    var_r30_5 = 0;
loop_26:
    if (var_r30_5 < 2) {
        temp_r3_8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[var_r30_5 + 8], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_488.unk3C[var_r30_5 + 0x19].unk0 = temp_r3_8;
        Hu3DModelAttrSet(temp_r3_8, 1U);
        if (var_r30_5 != 0) {
            Hu3DModelPosSet(temp_r3_8, -4000.0f, 18000.0f, 3000.0f);
        } else {
            Hu3DModelPosSet(temp_r3_8, -5000.0f, 19000.0f, 4000.0f);
        }
        Hu3DModelRotSet(temp_r3_8, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(temp_r3_8, 1U);
        Hu3DModelLayerSet(temp_r3_8, 7);
        Hu3DModelAttrReset(temp_r3_8, 1U);
        var_r30_5 += 1;
        goto loop_26;
    }
    var_r30_6 = 0;
loop_32:
    if (var_r30_6 < 2) {
        if (var_r30_6 == 0) {
            temp_r3_9 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
            lbl_1_bss_488.unk3C[0x1B].unk0 = temp_r3_9;
            var_r31_2 = temp_r3_9;
        } else {
            temp_r3_10 = Hu3DModelLink(lbl_1_bss_488.unk3C[0x1B].unk0);
            lbl_1_bss_488.unk3C[0x1C].unk0 = temp_r3_10;
            var_r31_2 = temp_r3_10;
        }
        Hu3DModelAttrSet(var_r31_2, 1U);
        Hu3DModelPosSet(var_r31_2, 0.0f, 0.0f, -100.0f);
        lbl_1_bss_440[var_r30_6].unk0 = (f32) ((var_r30_6 * 0xC8) - 0x64);
        lbl_1_bss_440[var_r30_6].unk4 = (f32) ((var_r30_6 * 0x64) - 0x32);
        lbl_1_bss_440[var_r30_6].unk8 = -100.0f;
        Hu3DModelRotSet(var_r31_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(var_r31_2, 2U);
        Hu3DModelLayerSet(var_r31_2, 3);
        var_r30_6 += 1;
        goto loop_32;
    }
}

void fn_1_376C(void) {
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        if (var_r31 < 2) {
            lbl_1_bss_470[var_r31] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 25), 0xD2, 0);
        } else {
            lbl_1_bss_470[var_r31] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 26), 0xD2, 0);
        }
        espDispOff(lbl_1_bss_470[var_r31]);
        espDrawNoSet(lbl_1_bss_470[var_r31], 0);
        espPosSet(lbl_1_bss_470[var_r31], 288.0f, 240.0f);
        espAttrSet(lbl_1_bss_470[var_r31], 1U);
        espDispOn(lbl_1_bss_470[var_r31]);
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        if (var_r31_2 != 0) {
            lbl_1_bss_470[var_r31_2 + 4] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 28), 0xD7, 0);
        } else {
            lbl_1_bss_470[var_r31_2 + 4] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 27), 0xD7, 0);
        }
        espDispOff(lbl_1_bss_470[var_r31_2 + 4]);
        espDrawNoSet(lbl_1_bss_470[var_r31_2 + 4], 0);
        espPosSet(lbl_1_bss_470[var_r31_2 + 4], 288.0f, 240.0f);
        espAttrSet(lbl_1_bss_470[var_r31_2 + 4], 1U);
        espDispOn(lbl_1_bss_470[var_r31_2 + 4]);
        var_r31_2 += 1;
        goto loop_11;
    }
    lbl_1_bss_470[6] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 29), 0xF, 0);
    espDispOff(lbl_1_bss_470[6]);
    espDrawNoSet(lbl_1_bss_470[6], 0);
    espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    espAttrSet(lbl_1_bss_470[6], 1U);
    espDispOn(lbl_1_bss_470[6]);
    lbl_1_bss_470[7] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M547, 30), 0xF, 0);
    espDispOff(lbl_1_bss_470[7]);
    espDrawNoSet(lbl_1_bss_470[7], 0);
    espPosSet(lbl_1_bss_470[7], -100.0f, 0.0f);
    espAttrSet(lbl_1_bss_470[7], 1U);
    espDispOn(lbl_1_bss_470[7]);
}

void fn_1_3ADC(omObjData *obj) {
    HSFDATA *sp8;
    HSFMATERIAL *var_r25;
    HSFMATERIAL *var_r27;
    HSFMATERIAL *var_r29;
    HSFMATERIAL *var_r31;
    HU3DMODEL *temp_r24;
    HU3DMODEL *temp_r26;
    HU3DMODEL *temp_r28;
    HU3DMODEL *temp_r30;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 var_r20;
    s32 var_r21;
    s32 var_r22;
    s32 var_r23;

    lbl_1_bss_14 = (lbl_1_bss_14 + 1) % 360;
    lbl_1_bss_488.unk3C[0x1A].unk10.y = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_14) / 180.0));
    Hu3DModelRotSet(lbl_1_bss_488.unk3C[0x1A].unk0, 0.0f, lbl_1_bss_488.unk3C[0x1A].unk10.y, 0.0f);
    switch ((s32) lbl_1_bss_8) {                    /* irregular */
    case 0:
        temp_r30 = &Hu3DData[lbl_1_bss_488.unk3C[0x1A].unk0];
        var_r31 = temp_r30->hsf->material;
        var_r23 = 0;
loop_10:
        if (var_r23 < (s16) temp_r30->hsf->materialNum) {
            var_r31->invAlpha = lbl_1_data_27C;
            var_r23 += 1;
            var_r31++;
            goto loop_10;
        }
        lbl_1_bss_8 += 1;
        return;
    case 1:
        if ((MgSeqModeGet() == 5) && ((s32) lbl_1_bss_488.unkA0 == 2)) {
            temp_r4 = lbl_1_bss_4;
            lbl_1_bss_4 = temp_r4 + 1;
            if (temp_r4 > 0x1E) {
                lbl_1_bss_8 += 1;
                lbl_1_bss_4 = 0;
                return;
            }
        }
        return;
    case 2:
        lbl_1_bss_4 += 1;
        lbl_1_data_27C = (f32) (1.0 - (0.4 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_4 * 0x5A) / 16)) / 180.0)));
        temp_r28 = &Hu3DData[lbl_1_bss_488.unk3C[0x1A].unk0];
        var_r29 = temp_r28->hsf->material;
        var_r22 = 0;
loop_18:
        if (var_r22 < (s16) temp_r28->hsf->materialNum) {
            var_r29->invAlpha = lbl_1_data_27C;
            var_r22 += 1;
            var_r29++;
            goto loop_18;
        }
        if ((s32) lbl_1_bss_4 == 0x10) {
            lbl_1_bss_4 = 0;
            lbl_1_bss_8 += 1;
            lbl_1_bss_C = (rand8() % 60) + 0x40;
            return;
        }
        break;
    case 3:
        temp_r4_2 = lbl_1_bss_4;
        lbl_1_bss_4 = temp_r4_2 + 1;
        if (temp_r4_2 >= (s32) lbl_1_bss_C) {
            temp_r26 = &Hu3DData[lbl_1_bss_488.unk3C[0x1A].unk0];
            var_r27 = temp_r26->hsf->material;
            var_r21 = 0;
loop_24:
            if (var_r21 < (s16) temp_r26->hsf->materialNum) {
                var_r27->invAlpha = 1.0f;
                var_r21 += 1;
                var_r27++;
                goto loop_24;
            }
            lbl_1_bss_10 = (lbl_1_bss_10 + 1) % 5;
            if (((s32) lbl_1_bss_10 == 1) || ((s32) lbl_1_bss_10 == 4)) {
                lbl_1_bss_8 = 2;
            } else {
                lbl_1_bss_8 += 1;
            }
            lbl_1_bss_4 = 0;
            return;
        }
        break;
    case 4:
        temp_r4_3 = lbl_1_bss_4;
        lbl_1_bss_4 = temp_r4_3 + 1;
        if (temp_r4_3 >= 6) {
            temp_r24 = &Hu3DData[lbl_1_bss_488.unk3C[0x1A].unk0];
            sp8 = temp_r24->hsf;
            var_r25 = sp8->material;
            var_r20 = 0;
loop_33:
            if (var_r20 < (s16) temp_r24->hsf->materialNum) {
                var_r25->invAlpha = 0.6f;
                var_r20 += 1;
                var_r25++;
                goto loop_33;
            }
            lbl_1_bss_8 = 2;
            lbl_1_bss_4 = 0;
        }
        break;
    }
}

void fn_1_86B8(M547Work *work, M547Model *models, s32 *dataNums) {
    s32 *sp10;
    M547Model *spC;
    M547Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_6E8 = sp8;
    memset(lbl_1_bss_6E8, 0, sizeof(M547Work));
    lbl_1_bss_6E8->unk3C = spC;
    lbl_1_bss_6E8->unk98 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_6E8->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_6E8->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_6E8->unk4[var_r31_2].unk0].character;
        lbl_1_bss_6E8->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_6E8->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_6E8->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_6E8->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_6E8->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_8904(s16 arg0) {
    s16 sp8;
    s16 temp_r3;
    s16 var_r31;

    sp8 = arg0;
    lbl_1_bss_6E8->unk9C = sp8;
    var_r31 = 0;
loop_4:
    if (var_r31 < 0xD) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_6E8->unk98[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_6E8->unk3C[var_r31].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DModelPosSetV(temp_r3, (Vec *) &lbl_1_data_350[var_r31]);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(temp_r3, 0.0f);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        lbl_1_bss_6E8->unk3C[var_r31].unk4.x = lbl_1_data_350[var_r31].unk0;
        lbl_1_bss_6E8->unk3C[var_r31].unk4.y = lbl_1_data_350[var_r31].unk4;
        lbl_1_bss_6E8->unk3C[var_r31].unk4.z = lbl_1_data_350[var_r31].unk8;
        lbl_1_bss_6E8->unk3C[var_r31].unk10.x = 0.0f;
        lbl_1_bss_6E8->unk3C[var_r31].unk10.y = 0.0f;
        lbl_1_bss_6E8->unk3C[var_r31].unk10.z = 0.0f;
        Hu3DModelAttrReset(temp_r3, 1U);
        if (var_r31 == 0) {
            Hu3DModelShadowMapSet(temp_r3);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_8B9C(M547Char *chr0, M547Char *chr1) {
    lbl_1_bss_6E8->unk40[0] = chr0;
    lbl_1_bss_6E8->unk40[1] = chr1;
}

void fn_1_8BC0(s16 *mot0, s16 *mot1) {
    lbl_1_bss_6E8->unk48[0] = mot0;
    lbl_1_bss_6E8->unk48[1] = mot1;
}

void fn_1_8BE4(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_6E8->unk3C[var_r31 + 0xD].unk0 = CharModelCreate(lbl_1_bss_6E8->unk4[var_r31].unk2, 1);
        Hu3DModelPosSet(lbl_1_bss_6E8->unk3C[var_r31 + 0xD].unk0, (f32) ((var_r31 * 0xC8) - 0x64), 100.0f, 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_6E8->unk3C[var_r31 + 0xD].unk0, 0x40000001U);
        Hu3DModelCameraSet(lbl_1_bss_6E8->unk3C[var_r31 + 0xD].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_6E8->unk3C[var_r31 + 0xD].unk0, 0);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_8D2C(omObjData *obj) {
    s32 var_r31;
    s8 var_r27;
    s8 var_r28;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_6E8->unk4[var_r31].unk4 != 0) {
            memset((M547Work *) &lbl_1_bss_6E8->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_6E8->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_6E8->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk10;
            }
            lbl_1_bss_6E8->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_6E8->unk4[var_r31].unk11 = (s8) (u8) HuPadStkY[lbl_1_bss_6E8->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk11 >= 0) {
                var_r28 = (s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk11;
            } else {
                var_r28 = -(s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk11;
            }
            if (var_r28 < 0xA) {
                var_r27 = 0;
            } else {
                var_r27 = (s8) (u8) lbl_1_bss_6E8->unk4[var_r31].unk11;
            }
            lbl_1_bss_6E8->unk4[var_r31].unk11 = var_r27;
            lbl_1_bss_6E8->unk4[var_r31].unk14 = (s8) (u8) HuPadSubStkX[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkY[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk16 = HuPadTrigL[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk17 = HuPadTrigR[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk18 = HuPadDStk[lbl_1_bss_6E8->unk4[var_r31].unk6];
            lbl_1_bss_6E8->unk4[var_r31].unk19 = HuPadDStkRep[lbl_1_bss_6E8->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_91E8(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 7) {
            lbl_1_bss_6E8->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_6E8->unk4[var_r31].unk2, lbl_1_bss_6E8->unk40[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_6E8->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_6E8->unk50[var_r31_2].unk4 = 1.0f;
        lbl_1_bss_6E8->unk50[var_r31_2].unk8 = 1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

void fn_1_933C(omObjData *obj) {
    M547Anim *temp_r31;
    s16 temp_r0;
    s16 var_r29;

    var_r29 = 0;
loop_12:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_6E8->unk50[var_r29];
        temp_r0 = var_r29 + 0xD;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_6E8->unk3C[temp_r0].unk0, lbl_1_bss_6E8->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_6E8->unk3C[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_6E8->unk3C[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_6E8->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_6E8->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r31->unk20 = 0;
            temp_r31->unk18 = 0;
            temp_r31->unk1C = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_6E8->unk3C[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_6E8->unk3C[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        var_r29 += 1;
        goto loop_12;
    }
}

void fn_1_954C(omObjData *obj) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        lbl_1_data_3EC[var_r31]();
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_95A0(void) {
    M547Model *temp_r3;
    s32 temp_r0;
    s32 temp_r3_2;

    temp_r3 = lbl_1_bss_6E8->unk3C;
    if ((s32) lbl_1_bss_6E8->unkF0 == 0) {
        temp_r0 = lbl_1_bss_6E8->unkFC;
        switch (temp_r0) {                          /* irregular */
        case 0:
            lbl_1_bss_6E8->unkF4 = (rand8() % 120) + 0xB4;
            lbl_1_bss_6E8->unkFC = 1;
            lbl_1_bss_6E8->unk114 = 0.4f;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, lbl_1_bss_6E8->unk114);
            temp_r3[3].unk10.y = -60.0f;
            return;
        case 1:
            temp_r3_2 = lbl_1_bss_6E8->unkF4;
            lbl_1_bss_6E8->unkF4 = temp_r3_2 - 1;
            if (temp_r3_2 < 0) {
                lbl_1_bss_6E8->unkFC += 1;
                lbl_1_bss_6E8->unkF4 = 0;
                lbl_1_bss_6E8->unk110 = temp_r3[3].unk10.y;
                lbl_1_bss_6E8->unkF8 = 0x78;
                lbl_1_bss_6E8->unk114 = (f32) ((rand8() % 10) + 0x1E);
                if (lbl_1_bss_6E8->unk110 > -45.0f) {
                    lbl_1_bss_6E8->unk114 = -lbl_1_bss_6E8->unk114;
                    return;
                }
            }
            break;
        case 2:
            lbl_1_bss_6E8->unkF4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.4 + (0.5 * sin((3.141592653589793 * (f64) ((lbl_1_bss_6E8->unkF4 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_6E8->unkF4 == 0x28) {
                lbl_1_bss_6E8->unkF4 = 0;
                lbl_1_bss_6E8->unkFC += 1;
                return;
            }
            break;
        case 3:
            lbl_1_bss_6E8->unkF4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.8 + (0.2 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_6E8->unkF4 * 0xB4) / (s32) lbl_1_bss_6E8->unkF8)) / 180.0))));
            temp_r3[3].unk10.y = (f32) ((f64) lbl_1_bss_6E8->unk110 + ((f64) lbl_1_bss_6E8->unk114 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_6E8->unkF4 * 0x5A) / (s32) lbl_1_bss_6E8->unkF8)) / 180.0)));
            if ((s32) lbl_1_bss_6E8->unkF4 == (s32) lbl_1_bss_6E8->unkF8) {
                temp_r3[3].unk10.y = lbl_1_bss_6E8->unk110 + lbl_1_bss_6E8->unk114;
                lbl_1_bss_6E8->unkFC += 1;
                lbl_1_bss_6E8->unkF4 = 0;
                return;
            }
            break;
        case 4:
            lbl_1_bss_6E8->unkF4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.8 - (0.4 * sin((3.141592653589793 * (f64) ((lbl_1_bss_6E8->unkF4 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_6E8->unkF4 == 0x28) {
                lbl_1_bss_6E8->unkF4 = (rand8() % 120) + 0xB4;
                lbl_1_bss_6E8->unkFC = 1;
            }
            break;
        }
    }
}

void fn_1_9BD8(void) {
    M547Model *temp_r3;
    M547Model *temp_r3_2;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_6E8->unk3C;
    temp_r3_2 = lbl_1_bss_6E8->unk3C;
    if ((s32) lbl_1_bss_6E8->unk120 == 0) {
        temp_r3[1].unk10.y = 30.0f;
        temp_r3_2[2].unk10.y = 30.0f;
        temp_r0 = lbl_1_bss_6E8->unk12C;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) lbl_1_bss_6E8->unkFC == 2) {
                lbl_1_bss_6E8->unk124 = 0;
                lbl_1_bss_6E8->unk12C += 1;
                lbl_1_bss_6E8->unk140 = 20.0f;
                lbl_1_bss_6E8->unk144 = 5.0f;
                lbl_1_bss_6E8->unk148 = -5.0f;
                return;
            }
            break;
        case 1:
            lbl_1_bss_6E8->unk124 += 1;
            temp_r3[1].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_6E8->unk140 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk124 * lbl_1_bss_6E8->unk144)) / 180.0)));
            temp_r3_2[2].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_6E8->unk140 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk124 * lbl_1_bss_6E8->unk148)) / 180.0)));
            if ((s32) lbl_1_bss_6E8->unkFC == 4) {
                lbl_1_bss_6E8->unk12C += 1;
                lbl_1_bss_6E8->unk128 = 0;
                return;
            }
            break;
        case 2:
            lbl_1_bss_6E8->unk124 += 1;
            lbl_1_bss_6E8->unk128 += 1;
            if ((s32) lbl_1_bss_6E8->unk128 > 0x28) {
                lbl_1_bss_6E8->unk128 = 0x28;
            }
            lbl_1_bss_6E8->unk140 = (f32) (20.0 - (20.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_6E8->unk128 * 0x5A) / 40)) / 180.0)));
            temp_r3[1].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_6E8->unk140 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk124 * lbl_1_bss_6E8->unk144)) / 180.0)));
            temp_r3_2[2].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_6E8->unk140 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk124 * lbl_1_bss_6E8->unk148)) / 180.0)));
            if ((s32) lbl_1_bss_6E8->unkFC == 1) {
                lbl_1_bss_6E8->unk12C = 0;
            }
            break;
        }
    }
}

void fn_1_A124(void) {
    Mtx sp8;
    Mtx sp38;
    M547Model *temp_r30;
    M547Model *temp_r31;
    s32 temp_r3;

    temp_r31 = &lbl_1_bss_6E8->unk3C[4];
    temp_r30 = &lbl_1_bss_6E8->unk3C[5];
    if ((s32) lbl_1_bss_6E8->unk150 == 0) {
        MTXIdentity(sp38);
        MTXRotRad(sp8, 0x79, -0.7853982f);
        MTXConcat(sp38, sp8, sp38);
        temp_r31->unk10.y = 30.0f;
        temp_r3 = lbl_1_bss_6E8->unk15C;
        switch (temp_r3) {                          /* irregular */
        case 0:
            temp_r30->unk10.y = -45.0f;
            if ((s32) lbl_1_bss_6E8->unkFC == 2) {
                lbl_1_bss_6E8->unk170 = 10.0f;
                lbl_1_bss_6E8->unk174 = 5.0f;
                lbl_1_bss_6E8->unk154 = 0;
                lbl_1_bss_6E8->unk15C += 1;
            }
            break;
        case 1:
            lbl_1_bss_6E8->unk154 += 1;
            lbl_1_bss_6E8->unk174 = (f32) (5.0 + (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_6E8->unk154 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_6E8->unkFC == 3) {
                lbl_1_bss_6E8->unk174 = 10.0f;
                lbl_1_bss_6E8->unk15C += 1;
            }
            break;
        case 2:
            lbl_1_bss_6E8->unk154 += 1;
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_6E8->unkFC == 4) {
                lbl_1_bss_6E8->unk15C += 1;
                lbl_1_bss_6E8->unk158 = 0;
            }
            break;
        case 3:
            lbl_1_bss_6E8->unk158 += 1;
            lbl_1_bss_6E8->unk154 += 1;
            if ((s32) lbl_1_bss_6E8->unk158 > 0x28) {
                lbl_1_bss_6E8->unk158 = 0x28;
            }
            lbl_1_bss_6E8->unk170 = (f32) (10.0 - (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_6E8->unk158 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_6E8->unk170 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_6E8->unk154 * lbl_1_bss_6E8->unk174)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
loop_17:
            if (temp_r31->unk10.x >= 360.0f) {
                temp_r31->unk10.x -= 360.0f;
                goto loop_17;
            }
            if (((s32) lbl_1_bss_6E8->unkFC == 1) && ((temp_r31->unk10.x >= 359.0f) || (temp_r31->unk10.x <= 1.0f))) {
                lbl_1_bss_6E8->unk170 = 0.0f;
                temp_r31->unk10.x = 0.0f;
                temp_r30->unk10.x = 0.0f;
                temp_r30->unk10.y = -45.0f;
                temp_r30->unk10.z = 0.0f;
                lbl_1_bss_6E8->unk15C = 0;
            }
            break;
        }
loop_23:
        if (temp_r31->unk10.x >= 360.0f) {
            temp_r31->unk10.x -= 360.0f;
            goto loop_23;
        }
    }
}

void fn_1_AA08(void) {
    M547Model *temp_r30;
    M547Model *temp_r31;
    s32 temp_r4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u8 temp_r3;
    u8 temp_r3_3;

    temp_r31 = &lbl_1_bss_6E8->unk3C[6];
    temp_r30 = &lbl_1_bss_6E8->unk3C[8];
    temp_r4 = lbl_1_bss_6E8->unk18C;
    if ((u32) temp_r4 <= 7U) {
        switch (temp_r4) {
        case 0:
            if ((s32) lbl_1_bss_6E8->unkFC == 2) {
                lbl_1_bss_6E8->unk184 = 0;
                if (lbl_1_bss_6E8->unk1A0 == 0.0f) {
                    lbl_1_bss_6E8->unk18C += 1;
                    lbl_1_bss_6E8->unk184 = 0;
                    lbl_1_bss_6E8->unk1A0 = 15.0f;
                    temp_r3 = rand8();
                    temp_r4_2 = temp_r3 >> 0x1FU;
                    temp_r3_2 = (temp_r3 << 0x1C) - temp_r4_2;
                    lbl_1_bss_6E8->unk1A8 = (f32) ((((temp_r3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                } else {
                    lbl_1_bss_6E8->unk18C = 4;
                    lbl_1_bss_6E8->unk1A0 = 10.0f;
                    temp_r3_3 = rand8();
                    temp_r4_3 = temp_r3_3 >> 0x1FU;
                    temp_r3_4 = (temp_r3_3 << 0x1C) - temp_r4_3;
                    lbl_1_bss_6E8->unk1A8 = (f32) ((((temp_r3_3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                }
                lbl_1_bss_6E8->unk1A4 = (250.0f * lbl_1_bss_6E8->unk1A0) / 360.0f;
            }
            break;
        case 1:
            temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
            temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
            if (temp_r31->unk4.x >= lbl_1_bss_6E8->unk1A8) {
                lbl_1_bss_6E8->unk18C += 1;
            }
            break;
        case 2:
            lbl_1_bss_6E8->unk184 += 1;
            lbl_1_bss_6E8->unk1A0 = (f32) (7.5 + (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_6E8->unk184) / 180.0)));
            lbl_1_bss_6E8->unk1A4 = (250.0f * lbl_1_bss_6E8->unk1A0) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
            temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
            if ((s32) lbl_1_bss_6E8->unk184 >= 0x5A) {
                lbl_1_bss_6E8->unk18C += 1;
            }
            break;
        case 3:
            lbl_1_bss_6E8->unk184 += 1;
            if ((s32) lbl_1_bss_6E8->unk184 >= 0xB4) {
                lbl_1_bss_6E8->unk184 = 0xB4;
            }
            lbl_1_bss_6E8->unk1A0 = (f32) (7.5 - (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_6E8->unk184) / 180.0)));
            lbl_1_bss_6E8->unk1A4 = (250.0f * lbl_1_bss_6E8->unk1A0) / 360.0f;
            if (temp_r31->unk4.x < 1000.0f) {
                temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
                temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
            } else if ((s32) lbl_1_bss_6E8->unkFC == 1) {
                lbl_1_bss_6E8->unk18C = 0;
            }
            break;
        case 4:
            lbl_1_bss_6E8->unk184 += 1;
            if ((s32) lbl_1_bss_6E8->unk184 >= 0x14) {
                temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
                temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
                if (temp_r31->unk4.x >= lbl_1_bss_6E8->unk1A8) {
                    lbl_1_bss_6E8->unk18C += 1;
                    lbl_1_bss_6E8->unk184 = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_6E8->unk184 += 1;
            lbl_1_bss_6E8->unk1A0 = (f32) (10.0 * cos((3.141592653589793 * (f64) lbl_1_bss_6E8->unk184) / 180.0));
            lbl_1_bss_6E8->unk1A4 = (250.0f * lbl_1_bss_6E8->unk1A0) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
            temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
            if ((s32) lbl_1_bss_6E8->unk184 == 0x5A) {
                lbl_1_bss_6E8->unk18C += 1;
                lbl_1_bss_6E8->unk184 = 0;
            }
            break;
        case 6:
            if ((s32) lbl_1_bss_6E8->unkFC == 2) {
                lbl_1_bss_6E8->unk18C += 1;
            }
            break;
        case 7:
            lbl_1_bss_6E8->unk184 += 1;
            if ((s32) lbl_1_bss_6E8->unk184 >= 0x96) {
                lbl_1_bss_6E8->unk184 = 0x96;
            }
            if ((s32) lbl_1_bss_6E8->unk184 >= 0x3C) {
                lbl_1_bss_6E8->unk1A0 = (f32) (10.0 * sin((3.141592653589793 * (f64) (lbl_1_bss_6E8->unk184 - 0x3C)) / 180.0));
                lbl_1_bss_6E8->unk1A4 = (250.0f * lbl_1_bss_6E8->unk1A0) / 360.0f;
                if (temp_r31->unk4.x < 1000.0f) {
                    if ((s32) lbl_1_bss_6E8->unk184 >= 0x46) {
                        temp_r31->unk10.z -= lbl_1_bss_6E8->unk1A0;
                    }
                    temp_r31->unk4.x += lbl_1_bss_6E8->unk1A4;
                } else if ((s32) lbl_1_bss_6E8->unkFC == 1) {
                    lbl_1_bss_6E8->unk18C = 0;
                    lbl_1_bss_6E8->unk1A0 = 0.0f;
                }
            }
            break;
        }
    }
    temp_r30->unk4.x = temp_r31->unk4.x;
    temp_r30->unk4.y = temp_r31->unk4.y - 40.0f;
    temp_r30->unk4.z = temp_r31->unk4.z;
}

void fn_1_B414(void) {
    M547Model *temp_r3;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_6E8->unk3C;
    temp_r0 = lbl_1_bss_6E8->unk1BC;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s32) lbl_1_bss_6E8->unkFC == 2) {
            lbl_1_bss_6E8->unk1BC += 1;
            lbl_1_bss_6E8->unk1B4 = 0;
            Hu3DMotionSpeedSet(temp_r3[7].unk0, 0.5f);
            Hu3DMotionTimeSet(temp_r3[7].unk0, 0.0f);
            return;
        }
        return;
    case 1:
        lbl_1_bss_6E8->unk1B4 += 1;
        temp_r3[7].unk4.x = (f32) (((lbl_1_bss_6E8->unk1B4 * 0xFA0) / 200) - 0x7D0);
        if ((s32) lbl_1_bss_6E8->unk1B4 == 0xC8) {
            lbl_1_bss_6E8->unk1BC += 1;
            return;
        }
        break;
    case 2:
        if ((s32) lbl_1_bss_6E8->unkFC == 1) {
            lbl_1_bss_6E8->unk1BC = 0;
        }
        break;
    }
}
