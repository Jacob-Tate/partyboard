// MP5 m554 (Wind Wavers), generated from its m2c draft by tools/mp5/ports/m554dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m554dll (tools/mp5/decomp.py m554dll --types tools/mp5/types/m554dll.h)
// Written from the draft: Wind Wavers (1 vs 1). Runs on MP5's MgSeq sequencer; the camera uses
// MP5's omCameraView* helpers (mp5compat.h). lbl_1_bss_1360 points at the work struct lbl_1_bss_B1C.

typedef struct M554Model { // model table entry, 0x1C (0x5C of them in lbl_1_bss_10C)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M554Model;

typedef struct M554Player { // 0x1C
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // com: difficulty + 1
    s16 unk6; // pad
    s32 unk8; // HuPadBtn
    s32 unkC; // HuPadBtnDown
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
} M554Player;

typedef struct M554Rec { // per player, 0x54
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    s32 unk24;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    u32 unk30;
    u32 unk34;
    s16 unk38;
    s16 unk3A;
    u32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    char pad50[4];
} M554Rec;

typedef struct M554Char { // per MP5 character, 0x14
    u32 unk0[5]; // MP5 motion data numbers: 2 in the character's archive, 3 in its mot archive
} M554Char;

typedef struct M554Prop { // background animation state, 0x3C
    s32 unk0; // mode
    s32 unk4[3]; // counters
    s32 unk10; // stop flag
    char pad14[0x18];
    f32 unk2C; // angle
    f32 unk30; // distance
    f32 unk34; // angle speed
    f32 unk38; // height
} M554Prop;

typedef struct M554Pow { // 0x8
    s32 unk0;
    s32 unk4;
} M554Pow;

typedef struct M554Sail { // 0x10
    f32 unk0; // distance
    f32 unk4; // angle
    f32 unk8;
    f32 unkC;
} M554Sail;

typedef struct M554Work { // lbl_1_bss_B1C, 0x814
    HUPROCESS *unk0; // object manager
    M554Player unk4[2];
    M554Model *unk3C; // model table (lbl_1_bss_10C)
    M554Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_84)
    M554Rec unk50[2];
    s32 *unkF8; // data numbers (lbl_1_data_4)
    s32 unkFC;
    s32 unk100; // mode step
    s32 unk104;
    s32 unk108;
    s32 unk10C; // winner (2: draw)
    s32 unk110[4];
    s32 unk120;
    M554Pow unk124[2];
    M554Sail unk134[2];
    s32 unk154[2][60]; // per player, per frame of the last 60: an alternating L/R press
    char pad334[0x30];
    M554Prop unk364[10]; // 0-3 fn_1_78F4, 4-7 fn_1_7D74, 8-9 fn_1_7FCC
    char pad5BC[0x258];
} M554Work;

void fn_1_1F00(void);
void fn_1_2118(void);
void fn_1_22CC(void);
void fn_1_240C(void);
void fn_1_2654(void);
void fn_1_2800(void);
void fn_1_2804(void);
void fn_1_2870(void);
void fn_1_2C74(void);
void fn_1_31C8(void);
void fn_1_3210(s32 arg0);
void fn_1_3518(void);
void fn_1_3578(s32 arg0);
s32 fn_1_38D4(s32 arg0);
void fn_1_3AC8(s32 arg0);
s32 fn_1_3B58(s32 arg0);
void fn_1_3D6C(s32 arg0);
void fn_1_4050(s32 arg0);
void fn_1_4D60(s32 arg0);
s32 fn_1_514C(s32 arg0);
void fn_1_53B0(omObjData *obj);
void fn_1_5A5C(void);
void fn_1_5CCC(s32 arg0);
void ObjectSetup(void);
void fn_1_1C0(s16 arg0, s16 frameNo);
void fn_1_808(s16 mode, s16 frameNo);
void fn_1_84C(s16 arg0, s16 frameNo);
void fn_1_914(s16 mode, s16 frameNo);
void fn_1_958(s16 arg0, s16 frameNo);
void fn_1_990(s16 mode, s16 frameNo);
void fn_1_9D4(s16 mode, s16 frameNo);
void fn_1_9F8(s16 mode, s16 frameNo);
void fn_1_A2C(s16 mode, s16 frameNo);
void fn_1_A30(omObjData *obj);
void fn_1_A34(void);
s32 fn_1_A54(void);
void fn_1_A64(void);
void fn_1_EB4(omObjData *obj);
void fn_1_144C(void);
void fn_1_62F0(M554Work *arg0, M554Model *arg1, s32 *arg2);
void fn_1_653C(s16 arg0);
void fn_1_6C20(M554Char *arg0, M554Char *arg1);
void fn_1_6C44(s16 *arg0, s16 *arg1);
void fn_1_6C68(void);
void fn_1_6E80(omObjData *obj);
void fn_1_733C(void);
void fn_1_7490(omObjData *obj);
void fn_1_7880(omObjData *obj);
void fn_1_78A8(void);
void fn_1_78F4(void);
void fn_1_7D74(void);
void fn_1_7F84(void);
void fn_1_7FCC(void);

struct _struct_lbl_1_bss_14_0xC {
    /* 0x0 */ s32 unk0;                             /* inferred */
    /* 0x4 */ s32 unk4;                             /* inferred */
    /* 0x8 */ f32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

struct _struct_lbl_1_bss_6C_0xC {
    /* 0x0 */ s16 unk0;                             /* inferred */
    /* 0x2 */ char pad2[2];
    /* 0x4 */ s32 unk4;                             /* inferred */
    /* 0x8 */ s32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

struct _struct_lbl_1_data_1C4_0x8 {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
};                                                  /* size = 0x8 */

static s32 lbl_1_data_238 = -1;
s32 lbl_1_data_23C[2] = { -1, -1 };
static s16 lbl_1_data_244 = 0x7F;
s16 lbl_1_data_246[3] = { 0, 0, 0 };
static s32 lbl_1_data_24C[2] = { 0, 0 };
static s32 lbl_1_data_254 = -1;
static s16 lbl_1_bss_133C;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
} lbl_1_bss_1340;
static s32 lbl_1_bss_1348;
static s32 lbl_1_bss_134C;
static s32 lbl_1_bss_1350;
static s32 lbl_1_bss_1354;
static s32 lbl_1_bss_1358;
static s32 lbl_1_data_0 = DATA_MAKE_NUM(DATADIR_MP5_M554, 3);
s32 lbl_1_data_4[0x14] = {
    DATA_MAKE_NUM(DATADIR_MP5_M554, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M554, 20),
};
M554Char lbl_1_data_54[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIO, 175), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 176), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 175), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 176), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACH, 175), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 176), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 175), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 176), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIO, 175), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 176), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISY, 175), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 176), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 43) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 175), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 176), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 126), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 43) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 43 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 43 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 175 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 176 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 126 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */ } },
};
MGSEQ_PARAM lbl_1_data_158 = {
    0,
    0,
    fn_1_1C0,
    fn_1_808,
    fn_1_84C,
    fn_1_914,
    fn_1_958,
    fn_1_990,
    fn_1_9D4,
    fn_1_9F8,
    fn_1_A2C,
};
static void (*lbl_1_data_180[3])() = { fn_1_1F00, fn_1_2118, fn_1_22CC };
static void (*lbl_1_data_18C[3])() = { fn_1_240C, fn_1_2654, fn_1_2800 };
static void (*lbl_1_data_198[4])() = { fn_1_2870, fn_1_2C74, fn_1_31C8, NULL };
s32 lbl_1_data_1A8[2] = { 0, 0 };
f32 lbl_1_data_1B0[2] = { 0.5f, 0.2f };
f32 lbl_1_data_1B8[2] = { 0.0f, 2.0f };
static s32 lbl_1_data_1C0 = 0x12;
static struct _struct_lbl_1_data_1C4_0x8 lbl_1_data_1C4[0xD] = {
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
static s8 lbl_1_data_22C[0xC] = { 0x43, 0x49, 0x38, 0x6D, 0x35, 0x35, 0x34, 0, 0, 0, 0, 0 };
static s32 lbl_1_bss_0;
static s32 lbl_1_bss_4;
Vec lbl_1_bss_8;
static struct _struct_lbl_1_bss_14_0xC lbl_1_bss_14[7];
static struct _struct_lbl_1_bss_6C_0xC lbl_1_bss_6C[2];
s16 lbl_1_bss_84[2][5];
OMCAMERAVIEW lbl_1_bss_98[4];
static s16 lbl_1_bss_108[2];
M554Model lbl_1_bss_10C[0x5C];
M554Work lbl_1_bss_B1C;
Vec lbl_1_data_258[6] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
static s32 lbl_1_data_2A0 = DATA_MAKE_NUM(DATADIR_MP5_M554, 21);
static s16 lbl_1_data_2A8[8];                       /* unable to generate initializer: cannot parse fn_1_78F4 as integer */
M554Work *lbl_1_bss_1360;
s32 lbl_1_rodata_178[8][6] = {
    { -3, -2, 0, 1, 2, 3 },
    { -3, -1, -1, 0, 2, 2 },
    { -4, -2, -2, -1, 1, 1 },
    { -5, -3, -3, -2, -1, 0 },
    { -6, -4, -4, -3, -2, -1 },
    { -7, -5, -5, -4, -3, -2 },
    { -8, -6, -6, -5, -4, -3 },
    { -9, -7, -7, -6, -5, -4 },
}; /* const */
f32 lbl_1_rodata_238[6] = { 0.5f, 0.75f, 1.0f, 1.25f, 1.5f, 1.75f }; /* const */
s32 lbl_1_rodata_264[7] = { 0, 2, 5, 7, 0xA, 0x3D, 0 }; /* const */
s32 lbl_1_rodata_2F0[6] = { 0x12C, 0x258, 0x384, 0x4B0, 0x708, 0x960 }; /* const */
s32 lbl_1_rodata_308[0xC] = { 0, 1, 3, 2, 0, 2, 3, 1, 0, 1, 3, 1 }; /* const */
f32 lbl_1_rodata_390[5] = { 800.0f, 400.0f, 500.0f, 350.0f, 250.0f }; /* const */
f32 lbl_1_rodata_3A4[5] = { 1.0f, 1.0f, 1.0f, 1.0f, 0.0f }; /* const */
s32 lbl_1_rodata_3E4[5] = { 0x56, 0x58, 0x57, 0x59, 0 }; /* const */
s32 lbl_1_rodata_404[2] = { 0x5A, 0x5B };           /* const */

void fn_1_1F00(void) {
    s32 var_r31;
    s32 var_r31_2;

    fn_1_3210(0);
    fn_1_5A5C();
    if ((s32) lbl_1_data_23C[0] == -1) {
        lbl_1_data_23C[0] = HuAudFXPlay(0x890);
        lbl_1_data_23C[1] = HuAudFXPlay(0x892);
        HuAudFXVolSet(lbl_1_data_23C[1], lbl_1_data_244);
    }
    if (WipeCheckEnd() == 0) {
        lbl_1_data_238 = HuAudBGMPlay(0x36);
        lbl_1_bss_B1C.unk100 += 1;
        lbl_1_bss_B1C.unk104 = 0;
        omCameraViewMoveSimple(lbl_1_bss_98, 0x3C);
        var_r31 = 0;
loop_7:
        if (var_r31 < 2) {
            if ((s16) lbl_1_bss_B1C.unk4[var_r31].unk4 != 0) {
                fn_1_3AC8(var_r31);
            }
            var_r31 += 1;
            goto loop_7;
        }
        var_r31_2 = 0;
loop_10:
        if (var_r31_2 < 5) {
            lbl_1_bss_B1C.unk154[0][(var_r31_2 + 1) * 0xA] = 1;
            lbl_1_bss_B1C.unk154[1][(var_r31_2 + 1) * 0xA] = 1;
            var_r31_2 += 1;
            goto loop_10;
        }
        lbl_1_bss_1350 = 0;
        lbl_1_bss_1354 = 0;
        lbl_1_bss_1358 = 0;
        lbl_1_bss_134C = 0;
        lbl_1_bss_1348 = 0;
        lbl_1_bss_1340.unk0 = (s32) ((rand8() % 20) + 0x14);
        lbl_1_bss_1340.unk4 = (s32) ((rand8() % 20) + 0x14);
    }
}

void fn_1_2118(void) {
    lbl_1_bss_B1C.unk3C[2].unk10.y -= 5.0f;
    if (lbl_1_bss_B1C.unk3C[2].unk10.y <= -360.0f) {
        lbl_1_bss_B1C.unk3C[2].unk10.y = 0.0f;
        lbl_1_bss_B1C.unk50[0].unk38 = 1;
        lbl_1_bss_B1C.unk50[0].unk3A = 2;
        lbl_1_bss_B1C.unk50[0].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[0].unk44 = 20.0f;
        lbl_1_bss_B1C.unk50[0].unk3C = 0;
        lbl_1_bss_B1C.unk50[1].unk38 = 1;
        lbl_1_bss_B1C.unk50[1].unk3A = 2;
        lbl_1_bss_B1C.unk50[1].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[1].unk44 = 20.0f;
        lbl_1_bss_B1C.unk50[1].unk3C = 0;
        lbl_1_bss_B1C.unk100 += 1;
        omVibrate(lbl_1_bss_B1C.unk4[0].unk0, 0xF, 0xC, 0);
        omVibrate(lbl_1_bss_B1C.unk4[1].unk0, 0xF, 0xC, 0);
        CharFXPlayPan(lbl_1_bss_B1C.unk4[0].unk2, 0x1FC, 0x30);
        CharFXPlayPan(lbl_1_bss_B1C.unk4[1].unk2, 0x1FC, 0x50);
    }
}

void fn_1_22CC(void) {
    if (((s16) lbl_1_bss_B1C.unk50[0].unk38 == 0) && (lbl_1_bss_B1C.unk50[0].unk14 == lbl_1_bss_B1C.unk50[0].unkC)) {
        lbl_1_bss_B1C.unk50[0].unk38 = 1;
        lbl_1_bss_B1C.unk50[0].unk3A = 1;
        lbl_1_bss_B1C.unk50[0].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[0].unk44 = 30.0f;
        lbl_1_bss_B1C.unk50[0].unk3C = 0x40000001;
        lbl_1_bss_B1C.unk50[1].unk38 = 1;
        lbl_1_bss_B1C.unk50[1].unk3A = 1;
        lbl_1_bss_B1C.unk50[1].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[1].unk44 = 30.0f;
        lbl_1_bss_B1C.unk50[1].unk3C = 0x40000001;
        omCameraViewMoveSimple(&lbl_1_bss_98[1], 0x78);
        lbl_1_bss_134C = 1;
        MgSeqModeNext();
    }
}

void fn_1_240C(void) {
    s32 var_r31;
    s32 var_r31_2;

    fn_1_3518();
    var_r31 = 0;
loop_4:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_B1C.unk4[var_r31].unk4 != 0) {
            fn_1_3D6C(var_r31);
        }
        fn_1_3578(var_r31);
        var_r31 += 1;
        goto loop_4;
    }
    fn_1_3210(0);
    if ((lbl_1_bss_B1C.unk134[0].unk0 < 280.0f) || (lbl_1_bss_B1C.unk134[1].unk0 < 280.0f)) {
        lbl_1_bss_B1C.unk100 += 1;
        lbl_1_bss_B1C.unk104 = 0;
        lbl_1_bss_B1C.unk108 = 0;
        lbl_1_bss_B1C.unk10C = 0;
        if (lbl_1_bss_B1C.unk134[0].unk0 < lbl_1_bss_B1C.unk134[1].unk0) {
            lbl_1_bss_B1C.unk10C = 1;
        }
        if ((lbl_1_bss_B1C.unk134[0].unk0 < 280.0f) && (lbl_1_bss_B1C.unk134[1].unk0 < 280.0f)) {
            lbl_1_bss_B1C.unk10C = 2;
            lbl_1_bss_134C = 3;
        }
        if ((s32) lbl_1_bss_B1C.unk10C == 2) {
            omVibrate(lbl_1_bss_B1C.unk4[0].unk0, 0x3C, 0xC, 0);
            omVibrate(lbl_1_bss_B1C.unk4[1].unk0, 0x3C, 0xC, 0);
        } else {
            omVibrate(lbl_1_bss_B1C.unk4[lbl_1_bss_B1C.unk10C ^ 1].unk0, 0x3C, 0xC, 0);
        }
        var_r31_2 = 0;
loop_17:
        if (var_r31_2 < 4) {
            lbl_1_bss_B1C.unk110[var_r31_2] = 0;
            var_r31_2 += 1;
            goto loop_17;
        }
        fn_1_7F84();
        HuAudFXPlay(0x88F);
    }
    fn_1_5CCC(0);
}

void fn_1_2654(void) {
    s32 var_r30;
    s32 var_r31;

    var_r31 = 0;
    var_r30 = 0;
loop_9:
    if (var_r31 < 2) {
        if (((s32) lbl_1_bss_B1C.unk10C == 2) || ((s32) (lbl_1_bss_B1C.unk10C ^ 1) == var_r31)) {
            fn_1_4050(var_r31);
        } else {
            fn_1_4D60(var_r31);
        }
        if (((s32) lbl_1_bss_B1C.unk110[var_r31] >= 0x78) && (var_r30 == 0)) {
            var_r30 += 1;
        }
        var_r31 += 1;
        goto loop_9;
    }
    if (((s32) lbl_1_bss_B1C.unk10C == 2) && ((s32) lbl_1_bss_B1C.unk110[0] >= 0x14)) {
        lbl_1_bss_134C = 3;
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_238, 0x64);
        lbl_1_bss_B1C.unk100 = 0;
        lbl_1_bss_B1C.unk104 = 0;
    }
    if (var_r30 != 0) {
        if ((s32) lbl_1_bss_B1C.unk10C != 2) {
            lbl_1_bss_134C = 2;
        } else {
            lbl_1_bss_134C = 3;
        }
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_238, 0x64);
        lbl_1_bss_B1C.unk100 = 0;
        lbl_1_bss_B1C.unk104 = 0;
        lbl_1_bss_B1C.unk110[0] = 0;
    }
    fn_1_5CCC(0);
}

void fn_1_2800(void) {

}

void fn_1_2804(void) {
    s32 var_r31;

    if ((s32) lbl_1_bss_B1C.unk10C == 2) {
        var_r31 = 0;
loop_3:
        if (var_r31 < 2) {
            fn_1_4050(var_r31);
            var_r31 += 1;
            goto loop_3;
        }
        lbl_1_bss_B1C.unk100 = 0;
    }
    fn_1_5CCC(0);
}

void fn_1_2870(void) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M554Model *temp_r30;
    M554Model *temp_r31;
    s16 temp_r29;
    s32 temp_ret;

    if ((s32) lbl_1_bss_B1C.unk10C == 2) {
        lbl_1_bss_133C = MGSeqDrawCreate();
        lbl_1_bss_134C = 3;
        lbl_1_bss_B1C.unk110[0] = 0;
        HuAudJinglePlay(0x7B);
    } else {
        temp_r30 = &lbl_1_bss_B1C.unk3C[lbl_1_bss_B1C.unk10C + 0x4E];
        temp_r31 = &lbl_1_bss_B1C.unk3C[lbl_1_bss_B1C.unk10C + 3];
        temp_r29 = lbl_1_bss_B1C.unk4[lbl_1_bss_B1C.unk10C].unk0;
        temp_ret = _CheckFlag(MP5_PRACTICE_FLAG);
        if (temp_ret == 0) {
            GWPlayer[temp_r29].coin_win = 0xA;
        }
        lbl_1_bss_133C = MGSeqWinCreate(lbl_1_bss_B1C.unk4[lbl_1_bss_B1C.unk10C].unk2, -1, -1, -1);
        HuAudJinglePlay(0x79);
        lbl_1_bss_98[2].center.x = temp_r30->unk4.x;
        lbl_1_bss_98[2].center.y = 150.0f + temp_r30->unk4.y;
        lbl_1_bss_98[2].center.z = 350.0f + temp_r30->unk4.z;
        lbl_1_bss_98[2].rot.x = -32.0f;
        lbl_1_bss_98[2].rot.y = 0.0f;
        lbl_1_bss_98[2].rot.z = 0.0f;
        lbl_1_bss_98[2].zoom = 495.0f;
        omCameraViewMoveSimple(&lbl_1_bss_98[2], 0x3C);
        lbl_1_bss_134C = 0;
        lbl_1_bss_B1C.unk50[lbl_1_bss_B1C.unk10C].unk38 = 1;
        lbl_1_bss_B1C.unk50[lbl_1_bss_B1C.unk10C].unk3A = 3;
        lbl_1_bss_B1C.unk50[lbl_1_bss_B1C.unk10C].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[lbl_1_bss_B1C.unk10C].unk44 = 45.0f;
        lbl_1_bss_B1C.unk50[lbl_1_bss_B1C.unk10C].unk3C = 0;
        Hu3DModelObjMtxGet(temp_r30->unk0, CharModelItemHookGet(lbl_1_bss_B1C.unk4[lbl_1_bss_B1C.unk10C].unk2, 1, 0), sp20);
        Hu3DModelHookReset(temp_r30->unk0);
        Hu3DMtxRotGet(sp20, &sp8);
        sp14.x = sp20[0][3];
        sp14.y = sp20[1][3];
        sp14.z = sp20[2][3];
        Hu3DModelPosSetV(temp_r31->unk0, &sp14);
        Hu3DModelRotSetV(temp_r31->unk0, &sp8);
        temp_r31->unk4.x = sp14.x;
        temp_r31->unk4.y = sp14.y;
        temp_r31->unk4.z = sp14.z;
        temp_r31->unk10.x = sp8.x;
        temp_r31->unk10.y = sp8.y;
        temp_r31->unk10.z = sp8.z;
        fn_1_78A8();
        lbl_1_bss_B1C.unk110[0] = 0;
        lbl_1_data_246[0] = lbl_1_data_246[1];
    }
    lbl_1_bss_B1C.unk100 += 1;
    fn_1_5CCC(1);
}

void fn_1_2C74(void) {
    M554Model *temp_r31;
    M554Model *temp_r31_2;
    M554Model *temp_r31_3;

    lbl_1_bss_B1C.unk110[0] += 1;
    if ((s32) lbl_1_bss_B1C.unk10C != 2) {
        temp_r31 = &lbl_1_bss_B1C.unk3C[lbl_1_bss_B1C.unk10C + 0x4E];
        if ((s32) lbl_1_bss_B1C.unk10C != 0) {
            temp_r31->unk10.y += 8.0f;
            if (temp_r31->unk10.y > 360.0f) {
                temp_r31->unk10.y = 360.0f;
            }
        } else {
            temp_r31->unk10.y -= 8.0f;
            if (temp_r31->unk10.y < 0.0f) {
                temp_r31->unk10.y = 0.0f;
            }
        }
        temp_r31_2 = &lbl_1_bss_B1C.unk3C[lbl_1_bss_B1C.unk10C + 3];
        if ((s32) lbl_1_bss_B1C.unk110[0] <= 0x5A) {
            temp_r31_2->unk4.y = (f32) ((f64) temp_r31_2->unk4.y + (8.0 * cos((3.141592653589793 * (f64) ((lbl_1_bss_B1C.unk110[0] * 0x5A) / 90)) / 180.0)));
            temp_r31_2->unk4.z = (f32) ((f64) temp_r31_2->unk4.z - (8.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_B1C.unk110[0] * 0x5A) / 90)) / 180.0)));
            temp_r31_2->unk10.x += 10.0f;
            Hu3DModelScaleSet(temp_r31_2->unk0, (90.0f - (f32) lbl_1_bss_B1C.unk110[0]) / 90.0f, (90.0f - (f32) lbl_1_bss_B1C.unk110[0]) / 90.0f, (90.0f - (f32) lbl_1_bss_B1C.unk110[0]) / 90.0f);
        }
        temp_r31_3 = &lbl_1_bss_B1C.unk3C[lbl_1_bss_B1C.unk10C + 5];
        if ((s32) lbl_1_bss_B1C.unk10C != 0) {
            temp_r31_3->unk10.y = (f32) ((f64) temp_r31_3->unk10.y - 0.6428571428571429);
            if (temp_r31_3->unk10.y < 0.0f) {
                temp_r31_3->unk10.y = 0.0f;
            }
        } else {
            temp_r31_3->unk10.y = (f32) ((f64) temp_r31_3->unk10.y + 0.6428571428571429);
            if (temp_r31_3->unk10.y > 0.0f) {
                temp_r31_3->unk10.y = 0.0f;
            }
        }
        if ((s32) (lbl_1_bss_B1C.unk110[0] % 3) == 0) {
            lbl_1_data_244 -= 1;
            if ((s16) lbl_1_data_244 >= 0x40) {
                HuAudFXVolSet(lbl_1_data_23C[1], lbl_1_data_244);
            }
        }
    } else if ((s32) lbl_1_bss_B1C.unk110[0] == 0xB4) {
        HuAudFXFadeOut(lbl_1_data_23C[0], 0x14);
        HuAudFXFadeOut(lbl_1_data_23C[1], 0x14);
    }
    if ((GameMesStatGet(lbl_1_bss_133C) == 0) && ((s32) lbl_1_bss_B1C.unk110[0] >= 0xD2)) {
        GameMesKill(lbl_1_bss_133C);
        MgSeqModeNext();
    }
    fn_1_5CCC(1);
    fn_1_514C(lbl_1_bss_B1C.unk110[0]);
}

void fn_1_31C8(void) {
    lbl_1_bss_B1C.unk110[0] += 1;
    fn_1_514C(lbl_1_bss_B1C.unk110[0]);
    fn_1_5CCC(1);
}

void fn_1_3210(s32 arg0) {
    M554Model *temp_r29;
    M554Model *temp_r30;
    f32 temp_f31;
    s32 var_r28;
    s32 var_r31;

    if (arg0 == 0) {
        var_r31 = 0;
        var_r28 = 2;
    } else {
        var_r31 = arg0 - 1;
        var_r28 = arg0;
    }
loop_4:
    if (var_r31 < var_r28) {
        temp_r30 = &lbl_1_bss_B1C.unk3C[var_r31 + 0x4E];
        temp_r29 = &lbl_1_bss_B1C.unk3C[var_r31 + 5];
        temp_r30->unk4.x = (f32) ((f64) lbl_1_bss_B1C.unk134[var_r31].unk0 * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0));
        temp_r30->unk4.z = (f32) (-600.0 + ((f64) lbl_1_bss_B1C.unk134[var_r31].unk0 * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0)));
        temp_r30->unk10.y = 180.0f + lbl_1_bss_B1C.unk134[var_r31].unk4;
        temp_r29->unk4.x = (f32) ((f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 40.0f) * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0));
        temp_r29->unk4.z = (f32) (-600.0 + ((f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 40.0f) * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0)));
        temp_r29->unk10.y = temp_r30->unk10.y - 180.0f;
        temp_f31 = (f32) (0.6000000238418579 + ((0.9 * (f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 280.0f)) / 700.0));
        temp_r29->unk4.y = temp_r30->unk4.y - 80.0f;
        Hu3DModelScaleSet(temp_r29->unk0, temp_f31, 1.0f, temp_f31);
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_3518(void) {
    M554Model *sp8;
    s32 temp_r3;

    sp8 = &lbl_1_bss_B1C.unk3C[2];
    temp_r3 = lbl_1_bss_B1C.unk110[0];
    lbl_1_bss_B1C.unk110[0] = temp_r3 + 1;
    if (temp_r3 >= 0x1E) {
        lbl_1_bss_B1C.unk110[0] = 0;
        lbl_1_bss_B1C.unk120 += 1;
    }
}

void fn_1_3578(s32 arg0) {
    f32 sp18[6];
    Vec spC;
    M554Model *sp8;
    s16 temp_r29;
    u32 var_r30;

    sp18[0] = lbl_1_rodata_238[0];
    sp18[1] = lbl_1_rodata_238[1];
    sp18[2] = lbl_1_rodata_238[2];
    sp18[3] = lbl_1_rodata_238[3];
    sp18[4] = lbl_1_rodata_238[4];
    sp18[5] = lbl_1_rodata_238[5];
    sp8 = &lbl_1_bss_B1C.unk3C[arg0 + 0x4E];
    lbl_1_bss_B1C.unk124[arg0].unk0 = fn_1_38D4(arg0);
    var_r30 = lbl_1_bss_B1C.unk120 / 5;
    if ((s32) var_r30 > 7) {
        var_r30 = 7;
    }
    lbl_1_bss_B1C.unk124[arg0].unk4 = lbl_1_rodata_178[var_r30][lbl_1_bss_B1C.unk124[arg0].unk0];
    lbl_1_bss_B1C.unk134[arg0].unk0 += (f32) lbl_1_bss_B1C.unk124[arg0].unk4;
    if (lbl_1_bss_B1C.unk134[arg0].unk0 >= 1000.0f) {
        lbl_1_bss_B1C.unk134[arg0].unk0 = 1000.0f;
    }
    lbl_1_bss_B1C.unk50[arg0].unk4 = sp18[lbl_1_bss_B1C.unk124[arg0].unk0];
    if ((lbl_1_bss_B1C.unk50[arg0].unkC >= 10.0f) && ((s32) lbl_1_data_24C[arg0] == 0)) {
        lbl_1_data_24C[arg0] = 0;
        Hu3D3Dto2D(&lbl_1_bss_B1C.unk3C[arg0 + 0x4E].unk4, 1, &spC);
        temp_r29 = (s16) (32.0f + ((64.0f * spC.x) / 576.0f));
        if (arg0 != 0) {
            HuAudFXPlayPan(0x88D, temp_r29);
        } else {
            HuAudFXPlayPan(0x88E, temp_r29);
        }
    }
    if (((s32) lbl_1_data_24C[arg0] != 0) && (lbl_1_bss_B1C.unk50[arg0].unkC < 2.0f)) {
        lbl_1_data_24C[arg0] = 0;
    }
}

s32 fn_1_38D4(s32 arg0) {
    s32 sp8[6];
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;

    sp8[0] = lbl_1_rodata_264[0];
    sp8[1] = lbl_1_rodata_264[1];
    sp8[2] = lbl_1_rodata_264[2];
    sp8[3] = lbl_1_rodata_264[3];
    sp8[4] = lbl_1_rodata_264[4];
    sp8[5] = lbl_1_rodata_264[5];
    lbl_1_bss_B1C.unk154[arg0][lbl_1_bss_B1C.unk110[0]] = 0;
    if (((s32) (lbl_1_bss_B1C.unk4[arg0].unkC & 0x40) != 0) && ((s32) lbl_1_data_254 != 0)) {
        lbl_1_data_254 = 0;
        lbl_1_bss_B1C.unk154[arg0][lbl_1_bss_B1C.unk110[0]] = 1;
    } else if (((s32) (lbl_1_bss_B1C.unk4[arg0].unkC & 0x20) != 0) && ((s32) lbl_1_data_254 != 1)) {
        lbl_1_data_254 = 1;
        lbl_1_bss_B1C.unk154[arg0][lbl_1_bss_B1C.unk110[0]] = 1;
    }
    var_r31_2 = 0;
    var_r29 = 0;
loop_12:
    if (var_r31_2 < 0x3C) {
        var_r30 = lbl_1_bss_B1C.unk110[0] - var_r31_2;
        if (var_r30 < 0) {
            var_r30 += 0x3C; /* TODO(mp5): byte step? */
        }
        if ((s32) lbl_1_bss_B1C.unk154[arg0][var_r30] != 0) {
            var_r29 += 1;
        }
        var_r31_2 += 1;
        goto loop_12;
    }
    var_r31 = 0;
loop_16:
    if (var_r31 < 6) {
        if (var_r29 > (s32) sp8[var_r31]) {
            var_r31 += 1;
            goto loop_16;
        }
    }
    return var_r31;
}

void fn_1_3AC8(s32 arg0) {
    memset(&lbl_1_bss_6C[arg0], 0, 0xC);
    lbl_1_bss_6C[arg0].unk0 = lbl_1_bss_B1C.unk4[arg0].unk4 - 1;
    lbl_1_bss_6C[arg0].unk8 = fn_1_3B58(arg0);
}

s32 fn_1_3B58(s32 arg0) {
    s32 var_r31;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r3_6;
    u32 temp_r3_8;
    u8 temp_r3;
    u8 temp_r3_3;
    u8 temp_r3_5;
    u8 temp_r3_7;

    var_r31 = 0 /* TODO(mp5): uninitialised in the original */;
    if ((s16) lbl_1_bss_6C[arg0].unk0 == 0) {
        if ((s32) lbl_1_bss_B1C.unk120 >= 6) {
            temp_r3 = rand8();
            temp_r3_2 = temp_r3 >> 0x1FU;
            temp_r0 = (temp_r3 << 0x1D) - temp_r3_2;
            var_r31 = ((temp_r0 << 3) | (temp_r0 >> 0x1DU)) + temp_r3_2 + 0x19;
        } else {
            var_r31 = (rand8() % 5) + 0x14;
        }
    } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 1) {
        if ((s32) lbl_1_bss_B1C.unk120 >= 0x12) {
            temp_r3_3 = rand8();
            temp_r3_4 = temp_r3_3 >> 0x1FU;
            temp_r0_2 = (temp_r3_3 << 0x1D) - temp_r3_4;
            var_r31 = ((temp_r0_2 << 3) | (temp_r0_2 >> 0x1DU)) + temp_r3_4 + 6;
        } else {
            temp_r3_5 = rand8();
            temp_r3_6 = temp_r3_5 >> 0x1FU;
            temp_r0_3 = (temp_r3_5 << 0x1E) - temp_r3_6;
            var_r31 = ((temp_r0_3 << 2) | (temp_r0_3 >> 0x1EU)) + temp_r3_6 + 6;
        }
    } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 2) {
        if ((s32) lbl_1_bss_B1C.unk120 >= 0x14) {
            var_r31 = (rand8() % 3) + 6;
        } else {
            var_r31 = (rand8() % 3) + 5;
        }
    } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 3) {
        if ((s32) lbl_1_bss_B1C.unk120 >= 0x19) {
            temp_r3_7 = rand8();
            temp_r3_8 = temp_r3_7 >> 0x1FU;
            temp_r0_4 = (temp_r3_7 << 0x1E) - temp_r3_8;
            var_r31 = ((temp_r0_4 << 2) | (temp_r0_4 >> 0x1EU)) + temp_r3_8 + 4;
        } else {
            var_r31 = (rand8() % 3) + 3;
        }
    }
    return var_r31;
}

void fn_1_3D6C(s32 arg0) {
    s32 var_r30;
    struct _struct_lbl_1_bss_6C_0xC *temp_r4;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r3_6;
    u32 temp_r3_8;
    u8 temp_r3;
    u8 temp_r3_3;
    u8 temp_r3_5;
    u8 temp_r3_7;

    var_r30 = 0 /* TODO(mp5): uninitialised in the original */;
    temp_r4 = &lbl_1_bss_6C[arg0];
    temp_r4->unk8 -= 1;
    if ((s32) lbl_1_bss_6C[arg0].unk8 <= 0) {
        if ((s32) lbl_1_bss_6C[arg0].unk4 != 0) {
            lbl_1_bss_B1C.unk4[arg0].unkC = 0x40;
        } else {
            lbl_1_bss_B1C.unk4[arg0].unkC = 0x20;
        }
        lbl_1_bss_6C[arg0].unk4 = lbl_1_bss_6C[arg0].unk4 ^ 1;
        if ((s16) lbl_1_bss_6C[arg0].unk0 == 0) {
            if ((s32) lbl_1_bss_B1C.unk120 >= 6) {
                temp_r3 = rand8();
                temp_r3_2 = temp_r3 >> 0x1FU;
                temp_r0 = (temp_r3 << 0x1D) - temp_r3_2;
                var_r30 = ((temp_r0 << 3) | (temp_r0 >> 0x1DU)) + temp_r3_2 + 0x19;
            } else {
                var_r30 = (rand8() % 5) + 0x14;
            }
        } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 1) {
            if ((s32) lbl_1_bss_B1C.unk120 >= 0x12) {
                temp_r3_3 = rand8();
                temp_r3_4 = temp_r3_3 >> 0x1FU;
                temp_r0_2 = (temp_r3_3 << 0x1D) - temp_r3_4;
                var_r30 = ((temp_r0_2 << 3) | (temp_r0_2 >> 0x1DU)) + temp_r3_4 + 6;
            } else {
                temp_r3_5 = rand8();
                temp_r3_6 = temp_r3_5 >> 0x1FU;
                temp_r0_3 = (temp_r3_5 << 0x1E) - temp_r3_6;
                var_r30 = ((temp_r0_3 << 2) | (temp_r0_3 >> 0x1EU)) + temp_r3_6 + 6;
            }
        } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 2) {
            if ((s32) lbl_1_bss_B1C.unk120 >= 0x14) {
                var_r30 = (rand8() % 3) + 6;
            } else {
                var_r30 = (rand8() % 3) + 5;
            }
        } else if ((s16) lbl_1_bss_6C[arg0].unk0 == 3) {
            if ((s32) lbl_1_bss_B1C.unk120 >= 0x19) {
                temp_r3_7 = rand8();
                temp_r3_8 = temp_r3_7 >> 0x1FU;
                temp_r0_4 = (temp_r3_7 << 0x1E) - temp_r3_8;
                var_r30 = ((temp_r0_4 << 2) | (temp_r0_4 >> 0x1EU)) + temp_r3_8 + 4;
            } else {
                var_r30 = (rand8() % 3) + 3;
            }
        }
        lbl_1_bss_6C[arg0].unk8 = var_r30;
    }
}

void fn_1_4050(s32 arg0) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M554Model *temp_r28;
    M554Model *temp_r29;
    M554Model *temp_r30;
    f32 temp_f31;
    f32 temp_f31_2;
    s32 temp_r0_2;
    s32 temp_r3;
    u32 temp_r0;
    u32 temp_r3_2;
    u32 temp_r4;

    temp_r29 = &lbl_1_bss_B1C.unk3C[arg0 + 0x4E];
    temp_r30 = &lbl_1_bss_B1C.unk3C[arg0 + 3];
    temp_r28 = &lbl_1_bss_B1C.unk3C[arg0 + 5];
    if ((s32) lbl_1_bss_B1C.unk110[arg0] == 0) {
        Hu3DModelObjMtxGet(temp_r29->unk0, CharModelItemHookGet(lbl_1_bss_B1C.unk4[arg0].unk2, 1, 0), sp20);
        Hu3DModelHookReset(temp_r29->unk0);
        Hu3DMtxRotGet(sp20, &sp8);
        sp14.x = sp20[0][3];
        sp14.y = sp20[1][3];
        sp14.z = sp20[2][3];
        Hu3DModelPosSetV(temp_r30->unk0, &sp14);
        Hu3DModelRotSetV(temp_r30->unk0, &sp8);
        temp_r30->unk4.x = sp14.x;
        temp_r30->unk4.y = sp14.y;
        temp_r30->unk4.z = sp14.z;
        temp_r30->unk10.x = sp8.x;
        temp_r30->unk10.y = sp8.y;
        temp_r30->unk10.z = sp8.z;
        lbl_1_bss_B1C.unk134[arg0].unk8 = lbl_1_bss_B1C.unk134[arg0].unk0;
        lbl_1_bss_B1C.unk134[arg0].unkC = lbl_1_bss_B1C.unk134[arg0].unk4;
        lbl_1_bss_B1C.unk50[arg0].unk38 = 1;
        lbl_1_bss_B1C.unk50[arg0].unk3A = 4;
        lbl_1_bss_B1C.unk50[arg0].unk40 = 0.0f;
        lbl_1_bss_B1C.unk50[arg0].unk44 = 10.0f;
        lbl_1_bss_B1C.unk50[arg0].unk3C = 0x40000001;
    }
    lbl_1_bss_B1C.unk110[arg0] += 1;
    if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x1E) {
        lbl_1_bss_B1C.unk134[arg0].unk0 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk0 - 7.5);
        if ((s32) lbl_1_bss_B1C.unk10C == 2) {
            if (arg0 != 0) {
                lbl_1_bss_B1C.unk134[arg0].unk4 -= 17.75f;
            } else {
                lbl_1_bss_B1C.unk134[arg0].unk4 -= 22.25f;
            }
        } else {
            lbl_1_bss_B1C.unk134[arg0].unk4 -= 20.0f;
        }
        temp_r29->unk4.y += (f32) ((s32) lbl_1_bss_B1C.unk110[arg0] / 4);
        temp_r29->unk10.y += 15.0f;
    } else if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x3C) {
        lbl_1_bss_B1C.unk134[arg0].unk0 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk0 + 8.5);
        lbl_1_bss_B1C.unk134[arg0].unk4 -= 20.0f;
        temp_r29->unk4.y += (f32) ((s32) lbl_1_bss_B1C.unk110[arg0] / 4);
        temp_r29->unk10.z += 5.0f;
        temp_r29->unk10.y += 15.0f;
        temp_r29->unk10.x += 5.0f;
    } else {
        lbl_1_bss_B1C.unk134[arg0].unk0 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk0 + (30.0 + (f64) ((lbl_1_bss_B1C.unk110[arg0] - 0x3C) * 4)));
        lbl_1_bss_B1C.unk134[arg0].unk4 -= 20.0f;
        temp_r29->unk4.y += (f32) lbl_1_bss_B1C.unk110[arg0];
        temp_r29->unk10.x += 5.0f;
        temp_r29->unk10.y += 15.0f;
        temp_r29->unk10.z += 5.0f;
    }
    temp_r29->unk4.x = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk0 * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[arg0].unk4) / 180.0));
    temp_r29->unk4.z = (f32) (-600.0 + ((f64) lbl_1_bss_B1C.unk134[arg0].unk0 * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[arg0].unk4) / 180.0)));
    if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0xF) {
        temp_r3 = lbl_1_bss_B1C.unk110[arg0];
        temp_r3_2 = (u32) temp_r3 >> 0x1FU;
        temp_r0 = (temp_r3 << 0x1E) - temp_r3_2;
        if ((s32) (((temp_r0 << 2) | (temp_r0 >> 0x1EU)) + temp_r3_2) != 0) {
            Hu3DModelAttrReset(temp_r28->unk0, 1U);
        } else {
            Hu3DModelAttrSet(temp_r28->unk0, 1U);
        }
        temp_f31 = 0.6f - (0.02f * (f32) lbl_1_bss_B1C.unk110[arg0]);
        Hu3DModelScaleSet(temp_r28->unk0, temp_f31, temp_f31, temp_f31);
    } else if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x1E) {
        temp_r0_2 = lbl_1_bss_B1C.unk110[arg0];
        temp_r4 = (u32) temp_r0_2 >> 0x1FU;
        if ((s32) (((temp_r0_2 & 1) ^ temp_r4) - temp_r4) != 0) {
            Hu3DModelAttrReset(temp_r28->unk0, 1U);
        } else {
            Hu3DModelAttrSet(temp_r28->unk0, 1U);
        }
        temp_f31_2 = 0.6f - (0.02f * (f32) lbl_1_bss_B1C.unk110[arg0]);
        Hu3DModelScaleSet(temp_r28->unk0, temp_f31_2, temp_f31_2, temp_f31_2);
    } else if ((s32) lbl_1_bss_B1C.unk110[arg0] == 0x1E) {
        Hu3DModelAttrSet(temp_r28->unk0, 1U);
    }
    if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x1E) {
        lbl_1_bss_B1C.unk134[arg0].unk8 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 - 7.5);
        if ((s32) lbl_1_bss_B1C.unk10C == 2) {
            if (arg0 != 0) {
                lbl_1_bss_B1C.unk134[arg0].unkC -= 12.75f;
            } else {
                lbl_1_bss_B1C.unk134[arg0].unkC = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unkC - 17.25);
            }
        } else {
            lbl_1_bss_B1C.unk134[arg0].unkC -= 15.0f;
        }
        temp_r30->unk4.y += (f32) (lbl_1_bss_B1C.unk110[arg0] / 6);
    } else if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x3C) {
        lbl_1_bss_B1C.unk134[arg0].unk8 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 + 8.5);
        lbl_1_bss_B1C.unk134[arg0].unkC -= 15.0f;
        temp_r30->unk4.y += (f32) (lbl_1_bss_B1C.unk110[arg0] / 6);
    } else if ((s32) lbl_1_bss_B1C.unk110[arg0] < 0x5A) {
        lbl_1_bss_B1C.unk134[arg0].unk8 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 + 8.5);
        lbl_1_bss_B1C.unk134[arg0].unkC -= 20.0f;
        temp_r30->unk4.y += (f32) ((s32) lbl_1_bss_B1C.unk110[arg0] / 4);
    } else {
        lbl_1_bss_B1C.unk134[arg0].unk8 = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 + (30.0 + (f64) ((lbl_1_bss_B1C.unk110[arg0] - 0x3C) * 4)));
        lbl_1_bss_B1C.unk134[arg0].unkC -= 20.0f;
        temp_r30->unk4.y += (f32) lbl_1_bss_B1C.unk110[arg0];
    }
    temp_r30->unk4.x = (f32) ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[arg0].unkC) / 180.0));
    temp_r30->unk4.z = (f32) (-600.0 + ((f64) lbl_1_bss_B1C.unk134[arg0].unk8 * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[arg0].unkC) / 180.0)));
    temp_r30->unk10.x -= 5.0f;
    temp_r30->unk10.y += 10.0f;
    temp_r30->unk10.z += 5.0f;
}

void fn_1_4D60(s32 arg0) {
    M554Model *temp_r29;
    M554Model *temp_r30;
    f32 temp_f31;
    s32 var_r27;
    s32 var_r31;

    lbl_1_bss_B1C.unk134[arg0].unk0 += 4.0f;
    if (lbl_1_bss_B1C.unk134[arg0].unk0 > 1000.0f) {
        lbl_1_bss_B1C.unk134[arg0].unk0 = 1000.0f;
    }
    if ((s32) (arg0 + 1) == 0) {
        var_r31 = 0;
        var_r27 = 2;
    } else {
        var_r31 = arg0;
        var_r27 = arg0 + 1;
    }
loop_6:
    if (var_r31 < var_r27) {
        temp_r29 = &lbl_1_bss_B1C.unk3C[var_r31 + 0x4E];
        temp_r30 = &lbl_1_bss_B1C.unk3C[var_r31 + 5];
        temp_r29->unk4.x = (f32) ((f64) lbl_1_bss_B1C.unk134[var_r31].unk0 * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0));
        temp_r29->unk4.z = (f32) (-600.0 + ((f64) lbl_1_bss_B1C.unk134[var_r31].unk0 * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0)));
        temp_r29->unk10.y = 180.0f + lbl_1_bss_B1C.unk134[var_r31].unk4;
        temp_r30->unk4.x = (f32) ((f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 40.0f) * sin((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0));
        temp_r30->unk4.z = (f32) (-600.0 + ((f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 40.0f) * cos((3.141592653589793 * (f64) lbl_1_bss_B1C.unk134[var_r31].unk4) / 180.0)));
        temp_r30->unk10.y = temp_r29->unk10.y - 180.0f;
        temp_f31 = (f32) (0.6000000238418579 + ((0.9 * (f64) (lbl_1_bss_B1C.unk134[var_r31].unk0 - 280.0f)) / 700.0));
        temp_r30->unk4.y = temp_r29->unk4.y - 80.0f;
        Hu3DModelScaleSet(temp_r30->unk0, temp_f31, 1.0f, temp_f31);
        var_r31 += 1;
        goto loop_6;
    }
    lbl_1_bss_B1C.unk50[arg0].unk4 += 0.05f;
    if (lbl_1_bss_B1C.unk50[arg0].unk4 > 1.5f) {
        lbl_1_bss_B1C.unk50[arg0].unk4 = 1.5f;
    }
}

s32 fn_1_514C(s32 arg0) {
    M554Model *temp_r30;
    f32 var_f31;
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = arg0;
    temp_r30 = &lbl_1_bss_B1C.unk3C[2];
    if ((s32) lbl_1_bss_B1C.unk10C != 2) {
        if (var_r31 >= 0xF0) {
            var_r31 = 0xF0;
        }
        var_f31 = 1.0f + (0.3f * (f32) var_r31);
        if (var_f31 >= 50.0f) {
            var_f31 = 50.0f;
        }
        temp_r30->unk4.y = (f32) ((f64) temp_r30->unk4.y - (1.0 + (6.0 * sin((3.141592653589793 * (f64) ((var_r31 * 0x5A) / 240)) / 180.0))));
    } else {
        var_r31_2 = var_r31 - 0x7D;
        if (var_r31_2 > 0) {
            if (var_r31_2 >= 0x3C) {
                var_r31_2 = 0x3C;
            }
            var_f31 = (f32) -(1.0 + (100.0 * sin((3.141592653589793 * (f64) ((var_r31_2 * 0x5A) / 60)) / 180.0)));
            if (fn_1_A54() > 1) {
                fn_1_A34();
            }
        } else {
            var_f31 = 0.0f;
        }
    }
    temp_r30->unk4.z -= var_f31;
    return 0;
}

void fn_1_53B0(omObjData *obj) {
    s32 sp20[12];
    s32 sp8[6];
    f32 temp_f1;
    f32 temp_f30;
    s32 var_r31;

    sp8[0] = lbl_1_rodata_2F0[0];
    sp8[1] = lbl_1_rodata_2F0[1];
    sp8[2] = lbl_1_rodata_2F0[2];
    sp8[3] = lbl_1_rodata_2F0[3];
    sp8[4] = lbl_1_rodata_2F0[4];
    sp8[5] = lbl_1_rodata_2F0[5];
    sp20[0] = lbl_1_rodata_308[0];
    sp20[1] = lbl_1_rodata_308[1];
    sp20[2] = lbl_1_rodata_308[2];
    sp20[3] = lbl_1_rodata_308[3];
    sp20[4] = lbl_1_rodata_308[4];
    sp20[5] = lbl_1_rodata_308[5];
    sp20[6] = lbl_1_rodata_308[6];
    sp20[7] = lbl_1_rodata_308[7];
    sp20[8] = lbl_1_rodata_308[8];
    sp20[9] = lbl_1_rodata_308[9];
    sp20[10] = lbl_1_rodata_308[0xA];
    sp20[11] = lbl_1_rodata_308[0xB];
    if ((s32) lbl_1_bss_134C != 0) {
        lbl_1_bss_1354 += 1;
        switch ((s32) lbl_1_bss_134C) {             /* irregular */
        case 0:
            return;
        case 1:
            var_r31 = 0;
loop_13:
            if (var_r31 < 6) {
                if ((s32) lbl_1_bss_1354 == (s32) sp8[var_r31]) {
                    lbl_1_bss_1358 += 2;
                    Hu3DMotionSpeedSet(lbl_1_bss_B1C.unk3C[0x4D].unk0, (f32) (1.0 + (0.1 * (f64) lbl_1_bss_1358)));
                    lbl_1_data_246[1] += 0x1F4;
                }
                var_r31 += 1;
                goto loop_13;
            }
        default:
block_22:
            if ((s32) sp20[lbl_1_bss_1354 % 12] == 0) {
                Center.y = (f32) (290.0 - (0.8 * (f64) (lbl_1_bss_1358 + 1)));
            }
            if ((s32) sp20[lbl_1_bss_1354 % 12] == 1) {
                Center.y = 290.0f;
            }
            if ((s32) sp20[lbl_1_bss_1354 % 12] == 2) {
                Center.y = (f32) (290.0 + (0.8 * (f64) (lbl_1_bss_1358 + 1)));
            }
            if ((s32) sp20[lbl_1_bss_1354 % 12] == 3) {
                Center.y = (f32) (290.0 + (1.2 * (f64) (lbl_1_bss_1358 + 1)));
            }
            if ((s32) lbl_1_bss_1348 == 0) {
                temp_f1 = Hu3DMotionTimeGet(lbl_1_bss_B1C.unk3C[0x4D].unk0);
                temp_f30 = (f32) (1.0 + (0.1 * (f64) lbl_1_bss_1358));
                if ((temp_f1 + temp_f30) > 99.0f) {
                    Hu3DMotionTimeSet(lbl_1_bss_B1C.unk3C[0x4D].unk0, (50.0f + (temp_f1 + temp_f30)) - 99.0f);
                }
            }
            if ((s16) lbl_1_data_246[0] != (s16) lbl_1_data_246[1]) {
                lbl_1_data_246[0] += 0xA;
                if ((s16) lbl_1_data_246[0] > (s16) lbl_1_data_246[1]) {
                    lbl_1_data_246[0] = lbl_1_data_246[1];
                }
                HuAudFXPitchSet(lbl_1_data_23C[1], lbl_1_data_246[0]);
            }
            break;
        case 2:
            lbl_1_bss_1350 += 1;
            if (((s32) lbl_1_bss_1358 > -1) && ((s32) lbl_1_bss_1350 >= 5)) {
                lbl_1_bss_1358 -= 1;
                lbl_1_bss_1350 = 0;
            }
            goto block_22;
        case 3:
            lbl_1_bss_1350 += 1;
            if ((s32) lbl_1_bss_1350 >= 5) {
                if ((s32) lbl_1_bss_1358 < 0x12) {
                    lbl_1_bss_1358 += 1;
                }
                lbl_1_bss_1350 = 0;
            }
            goto block_22;
        }
    }
}

void fn_1_5A5C(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 7) {
        memset((struct _struct_lbl_1_bss_6C_0xC *) &lbl_1_bss_14[var_r31], 0, 0xC);
        var_r31 += 1;
        goto loop_2;
    }
}


void fn_1_5CCC(s32 arg0) {
    M554Model *temp_r30;
    s32 temp_r26;
    s32 temp_r26_10;
    s32 temp_r26_2;
    s32 temp_r26_3;
    s32 temp_r26_4;
    s32 temp_r26_5;
    s32 temp_r26_6;
    s32 temp_r26_7;
    s32 temp_r26_8;
    s32 temp_r26_9;
    s32 temp_r3;
    s32 var_r28;
    s32 var_r29;
    s32 var_r31;
    struct _struct_lbl_1_bss_14_0xC *temp_r4;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r3_3;
    u32 temp_r3_5;
    u8 temp_r3_2;
    u8 temp_r3_4;

    var_r31 = 0;
loop_35:
    if (var_r31 < 7) {
        temp_r30 = &lbl_1_bss_B1C.unk3C[var_r31 + 7];
        temp_r3 = lbl_1_bss_14[var_r31].unk0;
        switch (temp_r3) {                          /* irregular */
        case 0:
            lbl_1_bss_14[var_r31].unk0 = 1;
            if ((s32) lbl_1_bss_B1C.unk120 <= 0xF) {
                temp_r26 = (rand8() % 5) * 8;
                var_r29 = temp_r26 + (rand8() % 10) + 0x28;
            } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x14) {
                temp_r26_2 = (rand8() % 5) * 7;
                var_r29 = temp_r26_2 + (rand8() % 9) + 0x23;
            } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x19) {
                temp_r26_3 = (rand8() % 5) * 6;
                temp_r3_2 = rand8();
                temp_r3_3 = temp_r3_2 >> 0x1FU;
                temp_r0 = (temp_r3_2 << 0x1D) - temp_r3_3;
                var_r29 = temp_r26_3 + (((temp_r0 << 3) | (temp_r0 >> 0x1DU)) + temp_r3_3) + 0x1E;
            } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x1E) {
                temp_r26_4 = (rand8() % 5) * 5;
                var_r29 = temp_r26_4 + (rand8() % 7) + 0x19;
            } else {
                temp_r26_5 = (rand8() % 5) * 4;
                var_r29 = temp_r26_5 + (rand8() % 6) + 0x14;
            }
            lbl_1_bss_14[var_r31].unk4 = var_r29;
            break;
        case 1:
            temp_r4 = &lbl_1_bss_14[var_r31];
            temp_r4->unk4 -= 1;
            if ((s32) lbl_1_bss_14[var_r31].unk4 <= 0) {
                Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
                Hu3DMotionSpeedSet(temp_r30->unk0, 1.0f);
                Hu3DModelAttrReset(temp_r30->unk0, 1U);
                lbl_1_bss_14[var_r31].unk0 = 2;
                if (arg0 != 0) {
                    lbl_1_bss_14[var_r31].unk0 = 3;
                }
                lbl_1_bss_14[var_r31].unk8 = Hu3DMotionMaxTimeGet(temp_r30->unk0);
            }
            break;
        case 2:
            if (Hu3DMotionTimeGet(temp_r30->unk0) >= lbl_1_bss_14[var_r31].unk8) {
                Hu3DModelAttrSet(temp_r30->unk0, 1U);
                lbl_1_bss_14[var_r31].unk0 = 1;
                if (arg0 != 0) {
                    lbl_1_bss_14[var_r31].unk0 = 3;
                }
                if ((s32) lbl_1_bss_B1C.unk120 <= 0xF) {
                    temp_r26_6 = (rand8() % 5) * 8;
                    var_r28 = temp_r26_6 + (rand8() % 10) + 0x28;
                } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x14) {
                    temp_r26_7 = (rand8() % 5) * 7;
                    var_r28 = temp_r26_7 + (rand8() % 9) + 0x23;
                } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x19) {
                    temp_r26_8 = (rand8() % 5) * 6;
                    temp_r3_4 = rand8();
                    temp_r3_5 = temp_r3_4 >> 0x1FU;
                    temp_r0_2 = (temp_r3_4 << 0x1D) - temp_r3_5;
                    var_r28 = temp_r26_8 + (((temp_r0_2 << 3) | (temp_r0_2 >> 0x1DU)) + temp_r3_5) + 0x1E;
                } else if ((s32) lbl_1_bss_B1C.unk120 <= 0x1E) {
                    temp_r26_9 = (rand8() % 5) * 5;
                    var_r28 = temp_r26_9 + (rand8() % 7) + 0x19;
                } else {
                    temp_r26_10 = (rand8() % 5) * 4;
                    var_r28 = temp_r26_10 + (rand8() % 6) + 0x14;
                }
                lbl_1_bss_14[var_r31].unk4 = var_r28;
            }
            break;
        }
        var_r31 += 1;
        goto loop_35;
    }
    if (arg0 != 0) {
        lbl_1_bss_1348 = 1;
    }
}



void ObjectSetup(void) {
    s16 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x5C) {
        lbl_1_bss_10C[var_r31].unk0 = -1;
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_62F0(&lbl_1_bss_B1C, lbl_1_bss_10C, lbl_1_data_4);
    lbl_1_bss_B1C.unk0 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_B1C.unk0);
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_6E80);
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_A30);
    MgSeqCreate(&lbl_1_data_158);
}

void fn_1_1C0(s16 arg0, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    s16 sp8;
    s16 temp_r3;

    sp8 = arg0;
    fn_1_653C(2);
    fn_1_6C20(&lbl_1_data_54[Mp5CharNo(lbl_1_bss_B1C.unk4[0].unk2)], &lbl_1_data_54[Mp5CharNo(lbl_1_bss_B1C.unk4[1].unk2)]);
    fn_1_6C44(lbl_1_bss_84[0], lbl_1_bss_84[1]);
    fn_1_6C68();
    fn_1_733C();
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_7490);
    fn_1_144C();
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_7880);
    Center.x = 0.0f;
    Center.y = 390.0f;
    Center.z = 200.0f;
    CRot.x = -20.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 220.0f;
    lbl_1_bss_98->center.x = 0.0f;
    lbl_1_bss_98->center.y = 400.0f;
    lbl_1_bss_98->center.z = 100.0f;
    lbl_1_bss_98->rot.x = -25.0f;
    lbl_1_bss_98->rot.y = 0.0f;
    lbl_1_bss_98->rot.z = 0.0f;
    lbl_1_bss_98->zoom = 1450.0f;
    lbl_1_bss_98[1].center.x = -40.0f;
    lbl_1_bss_98[1].center.y = 290.0f;
    lbl_1_bss_98[1].center.z = 200.0f;
    lbl_1_bss_98[1].rot.x = -14.0f;
    lbl_1_bss_98[1].rot.y = -26.0f;
    lbl_1_bss_98[1].rot.z = -8.0f;
    lbl_1_bss_98[1].zoom = 1560.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_EB4);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    sp24.x = 0.0f;
    sp24.y = 1200.0f;
    sp24.z = 10.0f;
    sp18.x = 0.0f;
    sp18.y = 1.0f;
    sp18.z = 0.0f;
    spC.x = 0.0f;
    spC.y = 0.0f;
    spC.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    Hu3DModelShadowSet(lbl_1_bss_B1C.unk3C[0x4E].unk0);
    Hu3DModelShadowSet(lbl_1_bss_B1C.unk3C[0x4F].unk0);
    lbl_1_bss_B1C.unk50[0].unk0 = 0;
    lbl_1_bss_B1C.unk50[0].unk4 = 1.0f;
    lbl_1_bss_B1C.unk50[0].unkC = 0.0f;
    lbl_1_bss_B1C.unk50[0].unk18 = 0x40000001;
    lbl_1_bss_B1C.unk50[1].unk0 = 0;
    lbl_1_bss_B1C.unk50[1].unk4 = 1.0f;
    lbl_1_bss_B1C.unk50[1].unkC = 0.0f;
    lbl_1_bss_B1C.unk50[1].unk18 = 0x40000001;
    lbl_1_bss_B1C.unk134[0].unk0 = 800.0f;
    lbl_1_bss_B1C.unk134[0].unk4 = -22.5f;
    lbl_1_bss_B1C.unk134[1].unk0 = 800.0f;
    lbl_1_bss_B1C.unk134[1].unk4 = 22.5f;
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    MgSeqModeNext();
}

void fn_1_808(s16 mode, s16 frameNo) {
    lbl_1_data_180[lbl_1_bss_B1C.unk100]();
}

void fn_1_84C(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    lbl_1_bss_B1C.unk100 = 0;
    lbl_1_bss_B1C.unk104 = 0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    if (((s32) lbl_1_bss_0 == 0) && (omCameraViewCheck(1U) != 0)) {
        omAddObjEx(lbl_1_bss_B1C.unk0, 0x7FDA, 0U, 0U, -1, fn_1_53B0);
        Hu3DModelAttrReset(lbl_1_bss_B1C.unk3C[0x4D].unk0, 1U);
        lbl_1_bss_0 = 1;
    }
}

void fn_1_914(s16 mode, s16 frameNo) {
    lbl_1_data_18C[lbl_1_bss_B1C.unk100]();
}

void fn_1_958(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    fn_1_2804();
}

void fn_1_990(s16 mode, s16 frameNo) {
    lbl_1_data_198[lbl_1_bss_B1C.unk100]();
}

void fn_1_9D4(s16 mode, s16 frameNo) {
    fn_1_31C8();
    MgSeqModeNext();
}

void fn_1_9F8(s16 mode, s16 frameNo) {
    fn_1_31C8();
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

void fn_1_A2C(s16 mode, s16 frameNo) {

}

void fn_1_A30(omObjData *obj) {

}

void fn_1_A34(void) {
    lbl_1_data_1C0 -= 1;
}

s32 fn_1_A54(void) {
    return lbl_1_data_1C0;
}

void fn_1_A64(void) {
    M554Model *temp_r31;
    M554Model *temp_r31_2;
    s32 temp_r4;
    s32 var_r30;
    s32 var_r30_2;

    lbl_1_data_1A8[1] += 1;
    var_r30 = 0;
loop_8:
    if (var_r30 < 0x3C) {
        temp_r31 = &lbl_1_bss_10C[var_r30 + 0x11];
        if ((s32) (var_r30 % 3) == 0) {
            temp_r31->unk4.x -= 6.0f;
            temp_r31->unk4.z -= 4.0f;
            temp_r31->unk4.y -= 1.0f;
        }
        if ((s32) (var_r30 % 3) == 1) {
            temp_r31->unk4.y -= 1.0f;
            temp_r31->unk4.z -= 2.0f;
        }
        if ((s32) (var_r30 % 3) == 2) {
            temp_r31->unk4.x += 6.0f;
            temp_r31->unk4.z -= 4.0f;
            temp_r31->unk4.y -= 1.0f;
        }
        var_r30 += 1;
        goto loop_8;
    }
    temp_r4 = lbl_1_data_1A8[1];
    lbl_1_data_1A8[1] = temp_r4 + 1;
    if (temp_r4 > (s32) lbl_1_data_1C0) {
        var_r30_2 = 0;
loop_15:
        if (var_r30_2 < 3) {
            temp_r31_2 = &lbl_1_bss_10C[(lbl_1_bss_4 * 3) + var_r30_2 + 0x11];
            temp_r31_2->unk4.x = lbl_1_bss_8.x;
            temp_r31_2->unk4.y = lbl_1_bss_8.y;
            temp_r31_2->unk4.z = lbl_1_bss_8.z;
            temp_r31_2->unk4.x = (f32) ((f64) temp_r31_2->unk4.x + (50.0 * sin((3.141592653589793 * (f64) (((var_r30_2 * 0x2D) + ((var_r30_2 - 5) * 2)) - 0x2D)) / 180.0)));
            temp_r31_2->unk4.z = (f32) ((f64) temp_r31_2->unk4.z + (40.0 * cos((3.141592653589793 * (f64) (((var_r30_2 * 0x2D) + ((var_r30_2 - 5) * 2)) - 0x2D)) / 180.0)));
            temp_r31_2->unk4.y -= 25.0f;
            Hu3DMotionTimeSet(temp_r31_2->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r31_2->unk0, 1.0f);
            Hu3DModelAttrReset(temp_r31_2->unk0, 1U);
            if (var_r30_2 == 1) {
                Hu3DModelScaleSet(temp_r31_2->unk0, 6.0f, 6.0f, 6.0f);
            } else {
                Hu3DModelScaleSet(temp_r31_2->unk0, 5.0f, 5.0f, 5.0f);
            }
            var_r30_2 += 1;
            goto loop_15;
        }
        lbl_1_data_1A8[1] = 0;
        lbl_1_bss_4 = (lbl_1_bss_4 + 1) % 10;
        if (((s32) lbl_1_bss_4 == 0) && ((s32) lbl_1_data_1C0 > 8)) {
            lbl_1_data_1C0 -= 1;
        }
    }
}

void fn_1_EB4(omObjData *obj) {
    Vec sp8;
    Vec sp14;
    M554Model *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_10C;
    var_r30 = 0;
loop_19:
    if (var_r30 < 0x5C) {
        if ((s16) var_r31->unk0 >= 0) {
            if (var_r30 == 2) {
                sp14.x = var_r31->unk4.x;
                sp14.y = var_r31->unk4.y;
                sp14.z = var_r31->unk4.z;
                sp8.x = var_r31->unk10.x;
                sp8.y = var_r31->unk10.y;
                sp8.z = var_r31->unk10.z;
                if (var_r31->unk10.y == 0.0f) {
                    *lbl_1_data_1A8 += 1;
                    if ((s32) *lbl_1_data_1A8 > 0x1E) {
                        *lbl_1_data_1A8 = 0;
                        if (lbl_1_data_1B0[0] < 25.0f) {
                            lbl_1_data_1B0[0] += 1.25f;
                        }
                        if (lbl_1_data_1B8[1] < 25.0f) {
                            lbl_1_data_1B8[1] += 0.5f;
                        }
                        if (lbl_1_data_1B0[1] < 2.0f) {
                            lbl_1_data_1B0[1] += 0.1f;
                        }
                    }
                    lbl_1_data_1B8[0] -= lbl_1_data_1B8[1];
                    if (lbl_1_data_1B8[0] > 360.0f) {
                        lbl_1_data_1B8[0] -= 360.0f;
                    }
                    if (lbl_1_data_1B8[0] < 0.0f) {
                        lbl_1_data_1B8[0] += 360.0f;
                    }
                    sp14.z = (f32) ((f64) sp14.z + ((f64) lbl_1_data_1B0[0] * cos((3.141592653589793 * (f64) lbl_1_data_1B8[0]) / 180.0)));
                    sp14.x = (f32) ((f64) sp14.x + ((f64) lbl_1_data_1B0[0] * sin((3.141592653589793 * (f64) lbl_1_data_1B8[0]) / 180.0)));
                    sp8.z = (f32) ((f64) lbl_1_data_1B0[1] * cos((3.141592653589793 * (f64) lbl_1_data_1B8[0]) / 180.0));
                    sp8.x = (f32) ((f64) lbl_1_data_1B0[1] * sin((3.141592653589793 * (f64) lbl_1_data_1B8[0]) / 180.0));
                }
                lbl_1_bss_8.x = sp14.x;
                lbl_1_bss_8.y = sp14.y;
                lbl_1_bss_8.z = sp14.z;
                Hu3DModelPosSetV(var_r31->unk0, &sp14);
                Hu3DModelRotSetV(var_r31->unk0, &sp8);
                fn_1_A64();
            } else {
                Hu3DModelPosSetV(var_r31->unk0, &var_r31->unk4);
                Hu3DModelRotSetV(var_r31->unk0, &var_r31->unk10);
            }
        }
        var_r30 += 1;
        var_r31++;
        goto loop_19;
    }
}



void fn_1_144C(void) {
    M554Model *temp_r31;
    M554Model *temp_r31_2;
    M554Model *temp_r31_3;
    M554Model *temp_r31_4;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;

    lbl_1_bss_10C[2].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(lbl_1_bss_10C[2].unk0, Hu3DJointMotion(lbl_1_bss_10C[2].unk0, HuDataSelHeapReadNum(lbl_1_data_0, MEMORY_DEFAULT_NUM, HEAP_DATA)));
    Hu3DModelAttrSet(lbl_1_bss_10C[2].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_10C[2].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10C[2].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10C[2].unk4.x = 0.0f;
    lbl_1_bss_10C[2].unk4.y = 0.0f;
    lbl_1_bss_10C[2].unk4.z = 0.0f;
    lbl_1_bss_10C[2].unk10.x = 0.0f;
    lbl_1_bss_10C[2].unk10.y = 0.0f;
    lbl_1_bss_10C[2].unk10.z = 0.0f;
    Hu3DModelCameraSet(lbl_1_bss_10C[2].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_10C[2].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_10C[2].unk0, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_10C[2].unk0, 1U);
    Hu3DMotionSpeedSet(lbl_1_bss_10C[2].unk0, 1.0f);
    Hu3DModelScaleSet(lbl_1_bss_10C[2].unk0, 5.0f, 5.0f, 5.0f);
    Hu3DModelAttrSet(lbl_1_bss_10C[2].unk0, 0x40000001U);
    lbl_1_bss_10C[2].unk4.x = 0.0f;
    lbl_1_bss_10C[2].unk4.y = -200.0f;
    lbl_1_bss_10C[2].unk4.z = -600.0f;
    lbl_1_bss_10C[2].unk10.x = 0.0f;
    lbl_1_bss_10C[2].unk10.y = -180.0f;
    lbl_1_bss_10C[2].unk10.z = 0.0f;
    Hu3DModelLayerSet(lbl_1_bss_10C[2].unk0, 3);
    var_r30 = 0;
loop_4:
    if (var_r30 < 2) {
        temp_r31 = &lbl_1_bss_10C[var_r30 + 3];
        temp_r31->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31->unk0, 1U);
        Hu3DModelPosSet(temp_r31->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31->unk4.x = 0.0f;
        temp_r31->unk4.y = 0.0f;
        temp_r31->unk4.z = 0.0f;
        temp_r31->unk10.x = 0.0f;
        temp_r31->unk10.y = 0.0f;
        temp_r31->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31->unk0, 1U);
        lbl_1_bss_108[var_r30] = Hu3DTexScrollCreate(temp_r31->unk0, lbl_1_data_22C);
        if ((s16) lbl_1_bss_108[var_r30] >= 0) {
            Hu3DTexScrollPosSet(lbl_1_bss_108[var_r30], lbl_1_data_1C4[Mp5CharNo(lbl_1_bss_B1C.unk4[var_r30].unk2)].unk0, lbl_1_data_1C4[Mp5CharNo(lbl_1_bss_B1C.unk4[var_r30].unk2)].unk4, 0.0f);
        }
        Hu3DModelHookSet(lbl_1_bss_10C[var_r30 + 0x4E].unk0, CharModelItemHookGet(lbl_1_bss_B1C.unk4[var_r30].unk2, 1, 0), temp_r31->unk0);
        temp_r31_2 = &lbl_1_bss_10C[var_r30 + 5];
        temp_r31_2->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31_2->unk0, 1U);
        Hu3DModelPosSet(temp_r31_2->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31_2->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31_2->unk4.x = 0.0f;
        temp_r31_2->unk4.y = 0.0f;
        temp_r31_2->unk4.z = 0.0f;
        temp_r31_2->unk10.x = 0.0f;
        temp_r31_2->unk10.y = 0.0f;
        temp_r31_2->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31_2->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31_2->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31_2->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31_2->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31_2->unk0, 1.0f);
        Hu3DModelAttrSet(temp_r31_2->unk0, 0x40000001U);
        Hu3DModelShadowMapSet(temp_r31_2->unk0);
        Hu3DModelLayerSet(temp_r31_2->unk0, 4);
        var_r30 += 1;
        goto loop_4;
    }
    var_r30_2 = 0;
loop_7:
    if (var_r30_2 < 7) {
        temp_r31_3 = &lbl_1_bss_10C[var_r30_2 + 7];
        temp_r31_3->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[var_r30_2 + 5], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31_3->unk0, 1U);
        Hu3DModelPosSet(temp_r31_3->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31_3->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31_3->unk4.x = 0.0f;
        temp_r31_3->unk4.y = 0.0f;
        temp_r31_3->unk4.z = 0.0f;
        temp_r31_3->unk10.x = 0.0f;
        temp_r31_3->unk10.y = 0.0f;
        temp_r31_3->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31_3->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31_3->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31_3->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31_3->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_3->unk0, 4);
        Hu3DModelAttrSet(temp_r31_3->unk0, 1U);
        var_r30_2 += 1;
        goto loop_7;
    }
    var_r30_3 = 0;
loop_13:
    if (var_r30_3 < 0x3C) {
        temp_r31_4 = &lbl_1_bss_10C[var_r30_3 + 0x11];
        if (var_r30_3 == 0) {
            temp_r31_4->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            temp_r31_4->unk0 = Hu3DModelLink(lbl_1_bss_B1C.unk3C[0x11].unk0);
        }
        Hu3DModelAttrSet(temp_r31_4->unk0, 1U);
        Hu3DModelPosSet(temp_r31_4->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31_4->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31_4->unk4.x = 0.0f;
        temp_r31_4->unk4.y = 0.0f;
        temp_r31_4->unk4.z = 0.0f;
        temp_r31_4->unk10.x = 0.0f;
        temp_r31_4->unk10.y = 0.0f;
        temp_r31_4->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31_4->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31_4->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31_4->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31_4->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_4->unk0, 4);
        Hu3DModelAttrSet(temp_r31_4->unk0, 1U);
        Hu3DModelScaleSet(temp_r31_4->unk0, 6.0f, 6.0f, 6.0f);
        var_r30_3 += 1;
        goto loop_13;
    }
    lbl_1_bss_10C[0x4D].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_10C[0x4D].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_10C[0x4D].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10C[0x4D].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10C[0x4D].unk4.x = 0.0f;
    lbl_1_bss_10C[0x4D].unk4.y = 0.0f;
    lbl_1_bss_10C[0x4D].unk4.z = 0.0f;
    lbl_1_bss_10C[0x4D].unk10.x = 0.0f;
    lbl_1_bss_10C[0x4D].unk10.y = 0.0f;
    lbl_1_bss_10C[0x4D].unk10.z = 0.0f;
    Hu3DModelCameraSet(lbl_1_bss_10C[0x4D].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_10C[0x4D].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_10C[0x4D].unk0, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_10C[0x4D].unk0, 1U);
    Hu3DModelLayerSet(lbl_1_bss_10C[0x4D].unk0, 3);
    Hu3DMotionTimeSet(lbl_1_bss_10C[0x4D].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_10C[0x4D].unk0, 1.0f);
    Hu3DModelAttrSet(lbl_1_bss_10C[0x4D].unk0, 1U);
}

void fn_1_62F0(M554Work *arg0, M554Model *arg1, s32 *arg2) {
    s32 *sp10;
    M554Model *spC;
    M554Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = arg0;
    spC = arg1;
    sp10 = arg2;
    lbl_1_bss_1360 = sp8;
    memset((struct _struct_lbl_1_bss_6C_0xC *) lbl_1_bss_1360, 0, sizeof(M554Work));
    lbl_1_bss_1360->unk3C = spC;
    lbl_1_bss_1360->unkF8 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_1360->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_1360->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_1360->unk4[var_r31_2].unk0].character;
        lbl_1_bss_1360->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_1360->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_1360->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_1360->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_1360->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_653C(s16 arg0) {
    s16 sp8;
    M554Model *temp_r31;
    M554Model *temp_r31_2;
    M554Model *var_r31;
    M554Model *var_r31_2;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 var_r28;
    s16 var_r30;
    s32 var_r26;
    s32 var_r26_2;
    s32 var_r29;
    s32 var_r29_2;

    var_r30 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = arg0;
    lbl_1_bss_1360->unkFC = sp8;
    var_r28 = 0;
loop_5:
    if (var_r28 < 2) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->unkF8[var_r28], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_1360->unk3C[var_r28].unk0 = temp_r3;
        var_r30 = temp_r3;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelCameraSet(var_r30, 1U);
        Hu3DModelPosSetV(var_r30, &lbl_1_data_258[var_r28]);
        lbl_1_bss_1360->unk3C[var_r28].unk4.x = lbl_1_data_258[var_r28].x;
        lbl_1_bss_1360->unk3C[var_r28].unk4.y = lbl_1_data_258[var_r28].y;
        lbl_1_bss_1360->unk3C[var_r28].unk4.z = lbl_1_data_258[var_r28].z;
        if (var_r28 != 0) {
            Hu3DModelRotSet(var_r30, 0.0f, -180.0f, 0.0f);
            lbl_1_bss_1360->unk3C[var_r28].unk10.x = 0.0f;
            lbl_1_bss_1360->unk3C[var_r28].unk10.y = -180.0f;
            lbl_1_bss_1360->unk3C[var_r28].unk10.z = 0.0f;
            Hu3DMotionTimeSet(var_r30, 0.0f);
            Hu3DMotionSpeedSet(var_r30, 1.0f);
            Hu3DModelAttrSet(var_r30, 0x40000001U);
        } else {
            Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
            lbl_1_bss_1360->unk3C[var_r28].unk10.x = 0.0f;
            lbl_1_bss_1360->unk3C[var_r28].unk10.y = 0.0f;
            lbl_1_bss_1360->unk3C[var_r28].unk10.z = 0.0f;
        }
        Hu3DModelLayerSet(var_r30, 0);
        Hu3DModelAttrReset(var_r30, 1U);
        var_r28 += 1;
        goto loop_5;
    }
    var_r29 = 0;
loop_17:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_1360->unk3C[var_r29 + 0x54];
        temp_r31->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->unkF8[var_r29 + 0xF], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31->unk0, 0.5f);
        Hu3DModelCameraSet(temp_r31->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
        if (var_r29 != 0) {
            Hu3DModelLayerSet(temp_r31->unk0, 1);
        } else {
            Hu3DModelLayerSet(temp_r31->unk0, 7);
        }
        var_r31 = &lbl_1_bss_1360->unk3C[(var_r29 * 2) + 0x56];
        var_r26 = 0;
loop_15:
        if (var_r26 < 2) {
            if (var_r26 == 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->unkF8[var_r29 + 0x11], MEMORY_DEFAULT_NUM, HEAP_DATA));
                var_r31->unk0 = temp_r3_2;
                var_r30 = temp_r3_2;
            } else {
                var_r31->unk0 = Hu3DModelLink(var_r30);
            }
            Hu3DModelAttrSet(var_r31->unk0, 1U);
            Hu3DMotionSpeedSet(var_r31->unk0, 0.5f);
            Hu3DModelCameraSet(var_r31->unk0, 1U);
            Hu3DMotionTimeSet(var_r31->unk0, 0.0f);
            Hu3DModelAttrSet(var_r31->unk0, 0x40000001U);
            Hu3DModelLayerSet(var_r31->unk0, 1);
            var_r26 += 1;
            var_r31++;
            goto loop_15;
        }
        var_r29 += 1;
        goto loop_17;
    }
    var_r29_2 = 0;
loop_23:
    if (var_r29_2 < 4) {
        temp_r31_2 = &lbl_1_bss_1360->unk3C[var_r29_2 + 0x50];
        if (var_r29_2 == 0) {
            temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->unkF8[0xE], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31_2->unk0 = temp_r3_3;
            var_r30 = temp_r3_3;
        } else {
            temp_r31_2->unk0 = Hu3DModelLink(var_r30);
        }
        Hu3DModelAttrSet(temp_r31_2->unk0, 1U);
        Hu3DModelCameraSet(temp_r31_2->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_2->unk0, 2);
        Hu3DMotionTimeSet(temp_r31_2->unk0, 50.0f);
        Hu3DMotionSpeedSet(temp_r31_2->unk0, 0.5f);
        var_r29_2 += 1;
        goto loop_23;
    }
    var_r31_2 = &lbl_1_bss_1360->unk3C[0x5A];
    var_r26_2 = 0;
loop_29:
    if (var_r26_2 < 2) {
        if (var_r26_2 == 0) {
            temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->unkF8[0x13], MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r31_2->unk0 = temp_r3_4;
            var_r30 = temp_r3_4;
            lbl_1_data_2A8[var_r29_2] = Hu3DJointMotion(var_r31_2->unk0, HuDataSelHeapReadNum(lbl_1_data_2A0, MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            var_r31_2->unk0 = Hu3DModelLink(var_r30);
        }
        Hu3DModelScaleSet(var_r31_2->unk0, 1.0f, 1.0f, 1.0f);
        Hu3DMotionSet(var_r31_2->unk0, lbl_1_data_2A8[var_r29_2]);
        Hu3DMotionSpeedSet(var_r31_2->unk0, 1.0f);
        Hu3DModelAttrSet(var_r31_2->unk0, 0x40000001U);
        Hu3DModelCameraSet(var_r31_2->unk0, 1U);
        Hu3DModelLayerSet(var_r31_2->unk0, 1);
        Hu3DModelAttrSet(var_r31_2->unk0, 1U);
        var_r26_2 += 1;
        var_r31_2++;
        goto loop_29;
    }
}

void fn_1_6C20(M554Char *arg0, M554Char *arg1) {
    lbl_1_bss_1360->unk40[0] = arg0;
    lbl_1_bss_1360->unk40[1] = arg1;
}

void fn_1_6C44(s16 *arg0, s16 *arg1) {
    lbl_1_bss_1360->unk48[0] = arg0;
    lbl_1_bss_1360->unk48[1] = arg1;
}

void fn_1_6C68(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk0 = CharModelCreate(lbl_1_bss_1360->unk4[var_r31].unk2, 1);
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk4.x = 0.0f;
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk4.y = 0.0f;
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk4.z = 100.0f - (f32) (var_r31 * 0xC8);
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk10.x = 0.0f;
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk10.y = -90.0f;
        lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk10.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk0, 0x40000001U);
        Hu3DModelCameraSet(lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_1360->unk3C[var_r31 + 0x4E].unk0, 0);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_6E80(omObjData *obj) {
    s32 var_r31;
    s8 var_r27;
    s8 var_r28;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_1360->unk4[var_r31].unk4 != 0) {
            memset((struct _struct_lbl_1_bss_6C_0xC *) &lbl_1_bss_1360->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_1360->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_1360->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk10;
            }
            lbl_1_bss_1360->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_1360->unk4[var_r31].unk11 = (s8) (u8) HuPadStkY[lbl_1_bss_1360->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk11 >= 0) {
                var_r28 = (s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk11;
            } else {
                var_r28 = -(s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk11;
            }
            if (var_r28 < 0xA) {
                var_r27 = 0;
            } else {
                var_r27 = (s8) (u8) lbl_1_bss_1360->unk4[var_r31].unk11;
            }
            lbl_1_bss_1360->unk4[var_r31].unk11 = var_r27;
            lbl_1_bss_1360->unk4[var_r31].unk14 = (s8) (u8) HuPadSubStkX[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkY[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk16 = HuPadTrigL[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk17 = HuPadTrigR[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk18 = HuPadDStk[lbl_1_bss_1360->unk4[var_r31].unk6];
            lbl_1_bss_1360->unk4[var_r31].unk19 = HuPadDStkRep[lbl_1_bss_1360->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_733C(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 5) {
            lbl_1_bss_1360->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_1360->unk4[var_r31].unk2, lbl_1_bss_1360->unk40[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_1360->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_1360->unk50[var_r31_2].unk4 = 1.0f;
        lbl_1_bss_1360->unk50[var_r31_2].unk8 = 1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

void fn_1_7490(omObjData *obj) {
    M554Rec *temp_r31;
    s16 temp_r0;
    s16 temp_r0_4;
    s16 temp_r0_5;
    s16 var_r29;
    u32 temp_r0_2;
    u32 temp_r0_3;

    var_r29 = 0;
loop_27:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_1360->unk50[var_r29];
        temp_r0 = var_r29 + 0x4E;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_1360->unk3C[temp_r0].unk0, lbl_1_bss_1360->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_1360->unk3C[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_1360->unk3C[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_1360->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_1360->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r0_2 = temp_r31->unk20;
            temp_r31->unk20 = ~(temp_r0_2 | temp_r0_2);
            temp_r0_3 = temp_r31->unk18 & temp_r31->unk20;
            temp_r31->unk18 = temp_r0_3;
            temp_r31->unk1C = temp_r0_3;
            temp_r31->unk20 = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_1360->unk3C[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r0_4 = temp_r31->unk38;
        switch (temp_r0_4) {                        /* irregular */
        case 0:
            break;
        case 1:
            Hu3DMotionShiftSet(lbl_1_bss_1360->unk3C[temp_r0].unk0, lbl_1_bss_1360->unk48[var_r29][temp_r31->unk3A], temp_r31->unk40, temp_r31->unk44, temp_r31->unk3C);
            temp_r31->unk4C = Hu3DMotionShiftMaxTimeGet(lbl_1_bss_1360->unk3C[temp_r0].unk0);
            temp_r31->unk38 = 2;
            break;
        case 2:
            temp_r31->unk48 = Hu3DMotionShiftTimeGet(lbl_1_bss_1360->unk3C[temp_r0].unk0);
            if (((u32) (temp_r31->unk3C & 0x40000001) == 0) && (temp_r31->unk48 >= (temp_r31->unk44 - 1.0f))) {
                temp_r31->unk38 = 3;
            }
            break;
        case 3:
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_1360->unk3C[temp_r0].unk0);
            temp_r31->unk10 = temp_r31->unkC;
            temp_r31->unk38 = 0;
            temp_r0_5 = temp_r31->unk3A;
            temp_r31->unk2 = temp_r0_5;
            temp_r31->unk0 = temp_r0_5;
            break;
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_1360->unk3C[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        temp_r31->unk24 = Hu3DMotionEndCheck(lbl_1_bss_1360->unk3C[temp_r0].unk0);
        if (((s32) temp_r31->unk24 != 0) && ((s16) temp_r31->unk28 != 0)) {
            temp_r31->unk24 = 0;
            temp_r31->unk28 = 0;
            temp_r31->unk0 = temp_r31->unk2A;
            temp_r31->unkC = temp_r31->unk2C;
            temp_r31->unk18 = temp_r31->unk30;
            temp_r31->unk20 = temp_r31->unk34;
        }
        var_r29 += 1;
        goto loop_27;
    }
}

void fn_1_7880(omObjData *obj) {
    fn_1_78F4();
    fn_1_7D74();
    fn_1_7FCC();
}

void fn_1_78A8(void) {
    M554Prop *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_1360->unk364;
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        var_r31->unk10 = 1;
        var_r30 += 1;
        var_r31++;
        goto loop_2;
    }
}

void fn_1_78F4(void) {
    f32 sp18[5];
    f32 sp8[4];
    M554Model *temp_r30;
    M554Prop *temp_r31;
    s32 var_r28;
    s32 var_r29;

    sp18[0] = lbl_1_rodata_390[0];
    sp18[1] = lbl_1_rodata_390[1];
    sp18[2] = lbl_1_rodata_390[2];
    sp18[3] = lbl_1_rodata_390[3];
    sp18[4] = lbl_1_rodata_390[4];
    sp8[0] = lbl_1_rodata_3A4[0];
    sp8[1] = lbl_1_rodata_3A4[1];
    sp8[2] = lbl_1_rodata_3A4[2];
    sp8[3] = lbl_1_rodata_3A4[3];
    var_r29 = 0;
loop_19:
    if (var_r29 < 4) {
        temp_r31 = &lbl_1_bss_1360->unk364[var_r29];
        temp_r30 = &lbl_1_bss_1360->unk3C[var_r29 + 0x50];
        if ((s32) temp_r31->unk0 == 0) {
            temp_r31->unk0 = 1;
            temp_r31->unk4[0] = 0;
            temp_r31->unk4[1] = 0;
            temp_r31->unk4[2] = 0;
            temp_r31->unk2C = (f32) (((var_r29 * 0x23) + 0x82) - (rand8() % 20));
            temp_r31->unk30 = (f32) ((var_r29 * 0x195) + 0x9C4);
            temp_r31->unk34 = (f32) (0.125 + (0.0165 * (f64) var_r29));
            temp_r31->unk38 = sp18[var_r29];
            Hu3DModelScaleSet(temp_r30->unk0, sp8[var_r29], sp8[var_r29], 1.0f);
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.y = 100.0f + temp_r31->unk38;
            Hu3DModelAttrReset(temp_r30->unk0, 1U);
            Hu3DMotionTimeSet(temp_r30->unk0, 50.0f);
            Hu3DMotionSpeedSet(temp_r30->unk0, 0.5f);
            Hu3DModelPosSetV(temp_r30->unk0, &temp_r30->unk4);
        }
        var_r28 = 0;
loop_17:
        if (var_r28 < 3) {
            temp_r31->unk4[var_r28] += 1;
            switch (var_r28) {                      /* irregular */
            case 0:
                temp_r31->unk2C += temp_r31->unk34;
                if (temp_r31->unk2C >= 240.0f) {
                    temp_r31->unk2C = 100.0f;
                }
                break;
            case 1:
                if ((s32) temp_r31->unk4[var_r28] >= 0x64) {
                    temp_r31->unk4[var_r28] = 0;
                    Hu3DMotionTimeSet(temp_r30->unk0, 50.0f);
                }
                break;
            case 2:
                if ((s32) temp_r31->unk4[var_r28 + 1] != 0) {
                    temp_r31->unk30 += 20.0f;
                }
                break;
            }
            var_r28 += 1;
            goto loop_17;
        }
        temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
        temp_r30->unk4.z = (f32) ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
        temp_r30->unk4.y = 100.0f + temp_r31->unk38;
        temp_r30->unk10.y = 180.0f + temp_r31->unk2C;
        var_r29 += 1;
        goto loop_19;
    }
}

void fn_1_7D74(void) {
    s32 sp8[4];
    M554Model *temp_r31;
    M554Model *temp_r31_2;
    M554Prop *temp_r30;
    s32 var_r29;

    sp8[0] = lbl_1_rodata_3E4[0];
    sp8[1] = lbl_1_rodata_3E4[1];
    sp8[2] = lbl_1_rodata_3E4[2];
    sp8[3] = lbl_1_rodata_3E4[3];
    var_r29 = 0;
loop_4:
    if (var_r29 < 4) {
        temp_r30 = &lbl_1_bss_1360->unk364[var_r29 + 4];
        temp_r31 = &lbl_1_bss_1360->unk3C[sp8[var_r29]];
        if ((s32) temp_r30->unk0 == 0) {
            temp_r30->unk0 = 1;
            temp_r30->unk4[0] = 0;
            temp_r31->unk4.x = 0.0f;
            temp_r31->unk4.y = 0.0f;
            temp_r31->unk4.z = 0.0f;
            temp_r31->unk10.y = (f32) ((var_r29 * 0x1E) - 0xF);
            Hu3DModelAttrReset(temp_r31->unk0, 1U);
            Hu3DMotionTimeSet(temp_r31->unk0, (f32) (var_r29 * 0x19));
            Hu3DMotionSpeedSet(temp_r31->unk0, 0.5f);
            Hu3DModelPosSetV(temp_r31->unk0, &temp_r31->unk4);
            Hu3DModelRotSetV(temp_r31->unk0, &temp_r31->unk10);
            Hu3DModelAttrSet(temp_r31->unk0, 0x40000001U);
        }
        temp_r30->unk4[0] += 1;
        temp_r31->unk10.y = (f32) ((f64) temp_r31->unk10.y - 0.01);
        var_r29 += 1;
        goto loop_4;
    }
    temp_r31_2 = lbl_1_bss_1360->unk3C;
    temp_r31_2->unk10.y -= 0.005f;
}



void fn_1_7F84(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_1360->unk364[var_r31 + 8].unk10 = -1;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_7FCC(void) {
    s32 sp8[2];
    M554Model *temp_r30;
    M554Prop *temp_r31;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r29;

    sp8[0] = lbl_1_rodata_404[0];
    sp8[1] = lbl_1_rodata_404[1];
    var_r29 = 0;
loop_31:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_1360->unk364[var_r29 + 8];
        temp_r30 = &lbl_1_bss_1360->unk3C[sp8[var_r29]];
        temp_r0 = temp_r31->unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            temp_r31->unk0 = 1;
            temp_r31->unk4[0] = 0;
            temp_r31->unk10 = 0;
            Hu3DModelAttrReset(temp_r30->unk0, 1U);
            Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r30->unk0, 1.0f);
            Hu3DModelAttrSet(temp_r30->unk0, 0x40000001U);
            temp_r31->unk2C = 70.0f - (0.3f * (f32) (rand8() % 10));
            temp_r30->unk4.y = 1352.0f;
            if (var_r29 == 0) {
                temp_r31->unk4[0] = 0x23A;
                temp_r31->unk2C = 80.0f;
            } else {
                temp_r31->unk4[0] = 0xC8;
                temp_r31->unk2C = -(0.3f * (f32) (rand8() % 10));
            }
            temp_r31->unk34 = (f32) (1.1 + (0.1 * (f64) (rand8() % 40)));
            temp_r31->unk30 = 1770.0f;
            temp_r31->unk38 = temp_r31->unk30 - 270.0f;
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) (-600.0 + ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0)));
            break;
        case 1:
            temp_r3 = temp_r31->unk4[0];
            temp_r31->unk4[0] = temp_r3 + 1;
            if (temp_r3 > 0x258) {
                if ((s32) temp_r31->unk10 == 0) {
                    temp_r31->unk0 += 1;
                }
                temp_r31->unk4[0] = 0x30;
            }
            temp_r30->unk4.y = 1352.0f;
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) (-600.0 + ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0)));
            break;
        case 2:
            temp_r31->unk4[0] -= 1;
            temp_r30->unk4.y -= 24.0f;
            temp_r31->unk30 -= temp_r31->unk38 / 48.0f;
            temp_r31->unk2C -= temp_r31->unk34;
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) (-600.0 + ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0)));
            temp_r30->unk10.y -= 15.0f;
            if ((s32) temp_r31->unk4[0] == 0) {
                temp_r31->unk0 += 1;
                HuAudFXPlay(0x891);
            }
            break;
        case 3:
            temp_r31->unk4[0] += 1;
            if (temp_r30->unk4.y >= 520.0f) {
                temp_r30->unk4.y += 23.0f;
                temp_r31->unk2C = (f32) ((f64) temp_r31->unk2C - 10.0);
                temp_r31->unk30 += 15.2f;
            } else {
                temp_r30->unk4.y = (f32) ((f64) temp_r30->unk4.y + 3.5);
                temp_r31->unk2C = (f32) ((f64) temp_r31->unk2C - 6.0);
                temp_r31->unk30 += 1.3f;
            }
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) (-600.0 + ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0)));
            temp_r30->unk10.y -= 25.0f;
            if ((s32) temp_r31->unk4[0] >= 0x96) {
                temp_r31->unk4[0] = rand8() - 0x190;
                if ((s32) temp_r31->unk10 == 0) {
                    temp_r31->unk0 = 1;
                } else {
                    temp_r31->unk0 = 4;
                }
                if (var_r29 != 0) {
                    temp_r31->unk2C = (f32) (0.5 * (f64) (rand8() % 40));
                } else {
                    temp_r31->unk2C = (f32) (55.0 + (0.5 * (f64) (rand8() % 35)));
                }
                temp_r31->unk34 = (f32) (1.1 + (0.1 * (f64) (rand8() % 40)));
                temp_r31->unk30 = 1570.0f;
                temp_r31->unk30 += (f32) ((rand8() % 9) * 0x32);
                temp_r31->unk38 = temp_r31->unk30 - 270.0f;
            }
            break;
        }
        var_r29 += 1;
        goto loop_31;
    }
}
