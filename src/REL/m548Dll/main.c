// MP5 m548 (Head Waiter), generated from its m2c draft by tools/mp5/ports/m548dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m548dll (tools/mp5/decomp.py m548dll --types tools/mp5/types/m548dll.h)
// Written from the draft: Head Waiter (1 vs 1 duel). Runs on MP5's MgSeq sequencer; the camera uses
// MP5's omCameraView* helpers (mp5compat.h). lbl_1_bss_5F8 points at the work struct lbl_1_bss_3F0.

typedef struct M548Model { // model table entry, 0x1C (20 of them in lbl_1_bss_154)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M548Model;

typedef struct M548Player { // 0x1C
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
} M548Player;

typedef struct M548Char { // per MP5 character, 0x14
    u32 unk0[5]; // MP5 motion data numbers
} M548Char;

typedef struct M548Anim { // per player character animation request, 0x24 (fn_1_6EA0 applies it)
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
} M548Anim;

typedef struct M548Prop { // background animation state, 0x30
    s32 unk0; // stop flag
    s32 unk4;
    s32 unk8;
    s32 unkC; // mode
    char pad10[0x10];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    char pad2C[4];
} M548Prop;

typedef struct M548Work { // lbl_1_bss_3F0, 0x1E0
    HUPROCESS *unk0; // object manager
    M548Player unk4[2];
    M548Model *unk3C; // model table (lbl_1_bss_154)
    M548Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_138)
    M548Anim unk50[2];
    s32 *unk98; // data numbers (lbl_1_data_138)
    s32 unk9C;
    s32 unkA0; // mode
    s32 unkA4; // mode step
    s32 unkA8; // turn
    char padAC[4];
    s32 unkB0; // frame counter
    s32 unkB4; // camera step
    s32 unkB8;
    char padBC[4];
    f32 unkC0; // flash
    char padC4[8];
    f32 unkCC; // thrown character pos
    f32 unkD0;
    f32 unkD4;
    f32 unkD8; // frame counter
    char padDC[0x14];
    M548Prop unkF0[5]; // 0: wobble 1: left sail 2: right sail 3: clouds 4: slide
} M548Work;

typedef struct M548Game { // lbl_1_bss_3D0, 0x20
    s16 unk0; // 1: opponent's turn is over
    s16 unk2; // second round
    s16 unk4; // cards left
    s16 unk6; // turn player
    s16 unk8;
    s16 unkA;
    s16 unkC;
    char padE[2];
    f32 unk10[2];
    f32 unk18[2];
} M548Game;

typedef struct M548Count { // lbl_1_bss_0 and lbl_1_bss_5DC, 0x10
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} M548Count;

typedef struct M548Rect { // lbl_1_bss_384, 0x18
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} M548Rect;

typedef struct M548Fx { // lbl_1_bss_3B8, 0x18
    s32 unk0; // mode
    s32 unk4;
    s32 unk8;
    Vec unkC;
} M548Fx;

typedef struct M548Pair {
    f32 unk0;
    f32 unk4;
} M548Pair;


void fn_1_6104(M548Work *work, M548Model *models, s32 *dataNums);
void fn_1_6350(s16 arg);
void fn_1_65E8(M548Char *chr0, M548Char *chr1);
void fn_1_660C(s16 *mot0, s16 *mot1);
void fn_1_4FC4(Vec *pos);
void fn_1_5014(s32 show);
s32 fn_1_4658(s16 arg0);
s32 fn_1_196C(void);
void fn_1_1D84(omObjData *obj);
void fn_1_202C(void);
void fn_1_23A4(void);
void fn_1_257C(void);
void fn_1_282C(void);
void fn_1_2AD4(void);
void fn_1_309C(void);
void fn_1_3DCC(void);
s32 fn_1_4658(s16 arg0);
void fn_1_4AA0(omObjData *obj);
void fn_1_4F44(void);
void fn_1_4FC4(Vec *pos);
void fn_1_5014(s32 show);
void fn_1_5098(omObjData *obj);
void fn_1_54C0(void);
void fn_1_59FC(void);
void fn_1_5D84(void);
void fn_1_5DF4(void);
void ObjectSetup(void);
void fn_1_15C(s16 arg0, s16 frameNo);
void fn_1_8C0(s16 mode, s16 frameNo);
void fn_1_934(s16 arg0, s16 frameNo);
void fn_1_9B4(s16 mode, s16 frameNo);
void fn_1_9FC(s16 arg0, s16 frameNo);
void fn_1_A54(s16 mode, s16 frameNo);
void fn_1_A78(s16 mode, s16 frameNo);
void fn_1_A9C(s16 mode, s16 frameNo);
void fn_1_AD0(s16 mode, s16 frameNo);
void fn_1_1204(omObjData *obj);
void fn_1_167C(void);
void fn_1_194C(void);
s32 fn_1_196C(void);
void fn_1_19A4(omObjData *obj);
void fn_1_1CB4(void);
void fn_1_6104(M548Work *work, M548Model *models, s32 *dataNums);
void fn_1_6350(s16 arg);
void fn_1_65E8(M548Char *chr0, M548Char *chr1);
void fn_1_660C(s16 *mot0, s16 *mot1);
void fn_1_6630(void);
void fn_1_6890(omObjData *obj);
void fn_1_6D4C(void);
void fn_1_6EA0(omObjData *obj);
void fn_1_70B0(omObjData *obj);
void fn_1_7104(void);
void fn_1_773C(void);
void fn_1_7C88(void);
void fn_1_856C(void);
void fn_1_8F78(void);

s32 lbl_1_data_398 = -1;
M548Pair lbl_1_data_39C[0x11] = {
    { -0.75f, -0.125f },
    { -0.75f, 0.125f },
    { -0.75f, 0.375f },
    { -0.75f, 0.625f },
    { -0.5f, 0.0f },
    { -0.5f, 0.25f },
    { -0.5f, 0.5f },
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
f32 lbl_1_data_424[0xD] = {
    24.0f,
    24.0f,
    24.0f,
    20.0f,
    28.0f,
    24.0f,
    24.0f,
    28.0f,
    28.0f,
    28.0f,
    28.0f,
    28.0f,
    28.0f,
};
Vec lbl_1_data_458[3] = { { 0.0f, 185.0f, 0.0f }, { -85.0f, 185.0f, 0.0f }, { 85.0f, 185.0f, 0.0f } };
Vec lbl_1_data_47C[3] = { { -20.0f, 0.0f, 0.0f }, { -20.0f, -21.0f, 0.0f }, { -20.0f, 21.0f, 0.0f } };
f32 lbl_1_data_4A0[3] = { 550.0f, 420.0f, 420.0f };
static s8 lbl_1_data_4AC[0x1C] = {
    0x74,
    0x65,
    0x73,
    0x74,
    0x31,
    0x31,
    0x5F,
    0x74,
    0x65,
    0x78,
    0x5F,
    0x77,
    0x65,
    0x2D,
    0x69,
    0x74,
    0x65,
    0x6D,
    0x68,
    0x6F,
    0x6F,
    0x6B,
    0x2D,
    0x72,
    0,
    0,
    0,
    0,
};
f32 lbl_1_data_4C8[4] = { 0.0f, 80.0f, -80.0f, 0.0f };
f32 lbl_1_data_4D8[4] = { 240.0f, 160.0f, 240.0f, 200.0f };
f32 lbl_1_data_4E8[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 lbl_1_data_4F8[4] = { 2.0f, 2.0f, 1.5f, 1.0f };
f32 lbl_1_bss_5D8;
M548Count lbl_1_bss_5DC;
u8 lbl_1_bss_5EC;
s32 lbl_1_bss_5F0;
f32 lbl_1_data_0[0xD][6] = {
    { 148.03f, 173.65f, 138.69f, 182.5f, 125.0f, 207.0f },
    { 154.95f, 180.53f, 142.9f, 190.31f, 141.0f, 217.0f },
    { 126.02f, 206.1f, 101.54f, 218.15f, 127.0f, 233.0f },
    { 131.71f, 199.45f, 90.45f, 191.7f, 130.0f, 210.0f },
    { 151.55f, 240.86f, 116.39f, 246.55f, 144.0f, 228.0f },
    { 124.06f, 202.75f, 100.98f, 214.31f, 126.0f, 227.0f },
    { 130.47f, 206.43f, 117.83f, 236.28f, 138.5f, 228.2f },
    { 126.35f, 195.32f, 111.63f, 202.39f, 126.0f, 196.0f },
    { 83.79f, 228.14f, 62.16f, 227.45f, 130.0f, 276.0f },
    { 122.57f, 164.46f, 108.48f, 208.13f, 109.0f, 181.0f },
    { 122.57f, 164.46f, 108.48f, 208.13f, 109.0f, 181.0f },
    { 122.57f, 164.46f, 108.48f, 208.13f, 109.0f, 181.0f },
    { 122.57f, 164.46f, 108.48f, 208.13f, 109.0f, 181.0f },
};
s32 lbl_1_data_138[0xC] = {
    DATA_MAKE_NUM(DATADIR_MP5_M548, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M548, 11),
};
s32 lbl_1_data_168[7] = { DATA_MAKE_NUM(DATADIR_MP5_M548, 12), DATA_MAKE_NUM(DATADIR_MP5_M548, 13), DATA_MAKE_NUM(DATADIR_MP5_M548, 14), DATA_MAKE_NUM(DATADIR_MP5_M548, 14), DATA_MAKE_NUM(DATADIR_MP5_M548, 14), DATA_MAKE_NUM(DATADIR_MP5_M548, 14), DATA_MAKE_NUM(DATADIR_MP5_M548, 14) };
M548Char lbl_1_data_184[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 121) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 35), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 34), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 121) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 121 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 121 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 35 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 34 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */ } },
};
M548Pair lbl_1_data_288[0xD] = {
    { 0.0f, -0.15f },
    { -5.0f, -0.3f },
    { 10.0f, -0.25f },
    { 0.0f, -0.1f },
    { -5.0f, -0.35f },
    { 10.0f, -0.25f },
    { -10.0f, -0.5f },
    { 0.0f, 0.2f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
};
MGSEQ_PARAM lbl_1_data_2F0 = {
    0,
    0,
    fn_1_15C,
    fn_1_8C0,
    fn_1_934,
    fn_1_9B4,
    fn_1_9FC,
    fn_1_A54,
    fn_1_A78,
    fn_1_A9C,
    fn_1_AD0,
};
void (*lbl_1_data_318[8])() = {
    fn_1_2AD4,
    fn_1_309C,
    fn_1_2AD4,
    fn_1_309C,
    fn_1_3DCC,
    fn_1_54C0,
    fn_1_59FC,
    fn_1_5D84,
};
static s8 lbl_1_data_38F[9] = "m548time";
M548Count lbl_1_bss_0[2];
u32 lbl_1_bss_20[2];
f32 lbl_1_bss_28;
Vec lbl_1_bss_38;
Vec lbl_1_bss_44;
s16 lbl_1_bss_50;
MGTIMER *lbl_1_bss_54;
OMCAMERAVIEW lbl_1_bss_58[8];
s16 lbl_1_bss_138[2][7];
M548Model lbl_1_bss_154[0x14];
M548Rect lbl_1_bss_384[2];
s16 lbl_1_bss_3B4;
M548Fx lbl_1_bss_3B8;
M548Game lbl_1_bss_3D0;
M548Work lbl_1_bss_3F0;
s16 lbl_1_bss_5D0;
s16 lbl_1_bss_5D2[3];
Vec lbl_1_data_530[0xC] = {
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
};
void (*lbl_1_data_5C0[5])() = { fn_1_7104, fn_1_773C, fn_1_7C88, fn_1_856C, fn_1_8F78 };
M548Work *lbl_1_bss_5F8;
s32 lbl_1_rodata_C0[4] = { 1, 3, 5, 6 };            /* const */
s32 lbl_1_rodata_D0[2] = { 0, 2 };                  /* const */
Vec lbl_1_rodata_118 = { 0.0f, 50.0f, 70.0f };  /* const */
f32 lbl_1_rodata_15C[7] = { 5.0f, 0.0f, -5.0f, 0.0f, 5.0f, 0.0f, -5.0f }; /* const */
f32 lbl_1_rodata_178[7] = { -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f, 5.0f }; /* const */
Vec lbl_1_rodata_1C8 = { 0.0f, 0.0f, 0.0f };    /* const */
s32 lbl_1_rodata_1DC[3] = { 1, 3, 0 };              /* const */
s32 lbl_1_rodata_1E8[4] = { 1, 3, 4, 7 };           /* const */
s32 lbl_1_rodata_200[2] = { 1, 3 };                 /* const */
s32 lbl_1_rodata_208[2] = { 1, 3 };                 /* const */

void fn_1_1D84(omObjData *obj) {
    M548Count *temp_r4;
    M548Count *temp_r4_2;
    s32 var_r30;
    s32 var_r31;
    u32 temp_r4_3;
    u8 temp_r3;

    if ((s16) lbl_1_bss_3D0.unk4 != 9) {
        var_r31 = 0;
loop_16:
        if (var_r31 < 2) {
            if (((var_r31 != 0) || ((s16) lbl_1_bss_3D0.unk0 != 0)) && ((s16) lbl_1_bss_3F0.unk50[var_r31].unk0 == 1) && (lbl_1_bss_3F0.unk50[var_r31].unkC >= 24.0f) && (lbl_1_bss_3F0.unk50[var_r31].unkC < 80.0f)) {
                temp_r4 = &lbl_1_bss_0[var_r31];
                temp_r4->unk4 += 1;
                if ((s32) lbl_1_bss_0[var_r31].unk4 == (s32) lbl_1_bss_0[var_r31].unk8) {
                    lbl_1_bss_0[var_r31].unk4 = 0;
                    var_r30 = 0;
loop_10:
                    if (var_r30 < (s32) lbl_1_bss_0[var_r31].unkC) {
                        CharModelCryCreate(lbl_1_bss_3F0.unk4[var_r31].unk2, lbl_1_data_288[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)].unk0, lbl_1_data_288[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)].unk4);
                        var_r30 += 1;
                        goto loop_10;
                    }
                    if ((s32) lbl_1_bss_0[var_r31].unk0 != 0) {
                        lbl_1_bss_0[var_r31].unk8 = (rand8() % 10) + 0x3C;
                        lbl_1_bss_0[var_r31].unk0 = 0;
                    } else {
                        lbl_1_bss_0[var_r31].unk8 = 0xA;
                        temp_r4_2 = &lbl_1_bss_0[var_r31];
                        temp_r4_2->unk0 += 1;
                    }
                    temp_r3 = rand8();
                    temp_r4_3 = temp_r3 >> 0x1FU;
                    lbl_1_bss_0[var_r31].unkC = (((temp_r3 & 1) ^ temp_r4_3) - temp_r4_3) + 6;
                }
            }
            var_r31 += 1;
            goto loop_16;
        }
    }
}

void fn_1_202C(void) {
    s16 var_r31;

    var_r31 = 1;
loop_2:
    if (var_r31 < 0xC) {
        Hu3DModelPosSet(lbl_1_bss_3F0.unk3C[var_r31].unk0, lbl_1_bss_3F0.unk3C[var_r31].unk4.x, lbl_1_bss_3F0.unk3C[var_r31].unk4.y, lbl_1_bss_3F0.unk3C[var_r31].unk4.z);
        Hu3DModelRotSet(lbl_1_bss_3F0.unk3C[var_r31].unk0, lbl_1_bss_3F0.unk3C[var_r31].unk10.x, lbl_1_bss_3F0.unk3C[var_r31].unk10.y, lbl_1_bss_3F0.unk3C[var_r31].unk10.z);
        var_r31 += 1;
        goto loop_2;
    }
}


void fn_1_23A4(void) {
    s32 temp_r3;
    u32 temp_r0;
    u32 temp_r3_2;
    u8 temp_r31;
    u8 var_r31;

    var_r31 = rand8() % 10;
    if ((u8) lbl_1_bss_5EC == var_r31) {
        var_r31 = (var_r31 + 1) % 10;
    }
    lbl_1_bss_5EC = var_r31;
    temp_r31 = var_r31 + 7;
    temp_r3 = lbl_1_bss_3F0.unkB0;
    lbl_1_bss_3F0.unkB0 = temp_r3 + 1;
    temp_r3_2 = (u32) temp_r3 >> 0x1FU;
    temp_r0 = (temp_r3 << 0x1E) - temp_r3_2;
    if ((s32) ((temp_r3 % 4)) == 0) {
        Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[temp_r31].unk0, lbl_1_data_39C[temp_r31].unk4, 0.0f);
        HuAudFXPlay(0x83B);
    }
    if ((WipeCheckEnd() == 0) && ((s32) lbl_1_bss_3F0.unkB0 > 0x78)) {
        lbl_1_bss_3F0.unkB0 = 0;
        lbl_1_bss_3F0.unkA0 += 1;
        Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[6].unk0, lbl_1_data_39C[6].unk4, 0.0f);
        HuAudFXPlay(0x83C);
        lbl_1_bss_5F0 = 0;
    }
}

void fn_1_257C(void) {
    s32 var_r31;
    s32 var_r31_2;

    if (fn_1_4658(0) != 0) {
        lbl_1_bss_3D0.unk0 = 0;
        lbl_1_bss_3D0.unk2 = 0;
        lbl_1_bss_3D0.unk4 = 9;
        lbl_1_bss_3D0.unk6 = 0;
        lbl_1_bss_3D0.unk8 = 0;
        lbl_1_bss_3D0.unkA = 0;
        lbl_1_bss_3D0.unkC = 0;
        var_r31 = 0;
loop_3:
        if (var_r31 < 2) {
            lbl_1_bss_3D0.unk10[var_r31] = lbl_1_data_424[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)] - 8.0f;
            lbl_1_bss_3D0.unk18[var_r31] = lbl_1_data_424[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)] - 8.0f;
            var_r31 += 1;
            goto loop_3;
        }
        var_r31_2 = 0;
loop_6:
        if (var_r31_2 < 3) {
            lbl_1_bss_58[var_r31_2].center.x = lbl_1_data_458[var_r31_2].x;
            lbl_1_bss_58[var_r31_2].center.y = lbl_1_data_458[var_r31_2].y;
            lbl_1_bss_58[var_r31_2].center.z = lbl_1_data_458[var_r31_2].z;
            lbl_1_bss_58[var_r31_2].rot.x = lbl_1_data_47C[var_r31_2].x;
            lbl_1_bss_58[var_r31_2].rot.y = lbl_1_data_47C[var_r31_2].y;
            lbl_1_bss_58[var_r31_2].rot.z = lbl_1_data_47C[var_r31_2].z;
            lbl_1_bss_58[var_r31_2].zoom = lbl_1_data_4A0[var_r31_2];
            var_r31_2 += 1;
            goto loop_6;
        }
        lbl_1_bss_3F0.unkA0 += 1;
        lbl_1_bss_3F0.unkB0 = 0;
        omCameraViewMoveSimple(lbl_1_bss_58, 0x3C);
    }
}

void fn_1_282C(void) {
    if (omCameraViewCheck(1U) != 0) {
        lbl_1_bss_3F0.unkA0 += 1;
        lbl_1_bss_3F0.unkA4 = 0;
        omCameraViewMoveSimple(&lbl_1_bss_58[1], 0x3C);
        MgSeqModeNext();
    }
}



void fn_1_2AD4(void) {
    s32 sp8[4];
    s16 temp_r31;
    s32 temp_r30;
    s32 temp_r3_3;
    u32 temp_r0;
    u32 temp_r3_2;
    u32 temp_r4;
    u8 temp_r3;
    u8 temp_r3_4;

    temp_r31 = lbl_1_bss_3D0.unk4;
    sp8[0] = lbl_1_rodata_C0[0];
    sp8[1] = lbl_1_rodata_C0[1];
    sp8[2] = lbl_1_rodata_C0[2];
    sp8[3] = lbl_1_rodata_C0[3];
    if (omCameraViewCheck(1U) != 0) {
        if ((s32) lbl_1_bss_3F0.unkA4 == 0) {
            lbl_1_bss_54 = MgTimerCreate(0);
            MgTimerParamSet(lbl_1_bss_54, 0x12C, 0, 0);
            MgTimerPosSet(lbl_1_bss_54, 288.0f, 64.0f);
            MgTimerModeOnSet(lbl_1_bss_54, 1);
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_5DC.unk0 = 0;
            return;
        }
        if ((s16) lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk4 != 0) {
            if ((s32) lbl_1_bss_5DC.unk0 == 0) {
                temp_r3 = rand8();
                temp_r3_2 = temp_r3 >> 0x1FU;
                temp_r0 = (temp_r3 << 0x1E) - temp_r3_2;
                temp_r30 = ((temp_r3 % 4)) * 0x1E;
                lbl_1_bss_5DC.unk8 = temp_r30 + (rand8() % 30) + 0x1E;
                lbl_1_bss_5DC.unk0 += 1;
            } else {
                temp_r3_3 = lbl_1_bss_5DC.unk8;
                lbl_1_bss_5DC.unk8 = temp_r3_3 - 1;
                if (temp_r3_3 <= 0) {
                    if ((s16) lbl_1_bss_3D0.unk2 != 0) {
                        if ((s32) (rand8() % 3) != 0) {
                            lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC = 0x100;
                        } else {
                            lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC = 0x200;
                        }
                    } else if ((s32) (rand8() % 3) != 0) {
                        lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC = 0x200;
                    } else {
                        lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC = 0x100;
                    }
                }
            }
        }
        if ((s32) (lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC & 0x100) != 0) {
            lbl_1_bss_3D0.unk4 -= 1;
        } else if ((s32) (lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unkC & 0x200) != 0) {
            lbl_1_bss_3D0.unk4 -= 2;
        }
        if (temp_r31 != (s16) lbl_1_bss_3D0.unk4) {
            lbl_1_bss_3F0.unkA4 = 0;
            MgTimerKill(lbl_1_bss_54);
            lbl_1_bss_54 = NULL;
            if ((s16) lbl_1_bss_3D0.unk4 > 0) {
                lbl_1_bss_3D0.unkC = 0;
                if ((s16) lbl_1_bss_3D0.unk2 != 0) {
                    lbl_1_bss_3F0.unkA0 = sp8[lbl_1_bss_3D0.unk6];
                    lbl_1_bss_3D0.unkA = 0;
                    lbl_1_bss_3D0.unk8 = 0;
                    if ((s32) lbl_1_bss_3F0.unkA8 > 3) {
                        temp_r3_4 = rand8();
                        temp_r4 = temp_r3_4 >> 0x1FU;
                        if ((s32) (((temp_r3_4 & 1) ^ temp_r4) - temp_r4) != 0) {
                            lbl_1_bss_3F0.unkA0 = sp8[2];
                            return;
                        }
                    }
                    HuAudFXPlay(0x83F);
                    if (fn_1_196C() != 0) {
                        lbl_1_bss_3F0.unkA0 = 7;
                    }
                } else {
                    if ((s32) lbl_1_bss_3F0.unkA8 >= 2) {
                        lbl_1_bss_3D0.unk2 = 1;
                    }
                    HuAudFXPlay(0x83E);
                    lbl_1_bss_3D0.unk8 = temp_r31 - lbl_1_bss_3D0.unk4;
                    lbl_1_bss_3D0.unkA = 0;
                    lbl_1_bss_3F0.unkA0 = sp8[3];
                    lbl_1_bss_3F0.unkA4 = 0;
                }
            } else {
                lbl_1_bss_3D0.unk4 = 0;
                lbl_1_bss_3F0.unkA0 = 4;
                lbl_1_bss_3D0.unkA = 0;
                lbl_1_bss_3D0.unk8 = 0;
            }
        } else if (MgTimerDoneCheck(lbl_1_bss_54) != 0) {
            lbl_1_bss_3D0.unk4 = 0;
            lbl_1_bss_3F0.unkA0 = 4;
            lbl_1_bss_3F0.unkA4 = 0;
            lbl_1_bss_3D0.unkA = 0;
            lbl_1_bss_3D0.unk8 = 0;
        }
    }
}

void fn_1_309C(void) {
    s32 sp8[2];
    Vec pos;

    sp8[0] = lbl_1_rodata_D0[0];
    sp8[1] = lbl_1_rodata_D0[1];
    switch ((s32) lbl_1_bss_3F0.unkA4) {            /* irregular */
    case 0:
        fn_1_194C();
        lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk4 = 1.0f;
        lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk20 = 0x40000001;
        lbl_1_bss_3F0.unkA4 += 1;
        lbl_1_bss_3D0.unkC = 0;
        return;
    case 1:
        lbl_1_bss_3D0.unkC += 1;
        Hu3DModelObjPosGet(lbl_1_bss_3F0.unk3C[lbl_1_bss_3D0.unk6 + 0xC].unk0, lbl_1_data_4AC, &pos);
        pos.y -= lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk4;
        lbl_1_bss_44.y = pos.y + lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk14;
        if ((s16) lbl_1_bss_3D0.unk6 != 0) {
            lbl_1_bss_44.x = pos.x + (lbl_1_bss_384[1].unk10 - lbl_1_bss_384[1].unk0);
        } else {
            lbl_1_bss_44.x = pos.x + -(lbl_1_bss_384->unk10 - lbl_1_bss_384->unk0);
        }
        if ((s16) lbl_1_bss_3D0.unkC == 0x14) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3D0.unkC = 0;
            lbl_1_bss_38.y = 300.0f - lbl_1_bss_44.y;
            lbl_1_bss_38.z = lbl_1_bss_44.y;
            lbl_1_bss_38.x = lbl_1_bss_44.x;
            omCameraViewMoveSimple(&lbl_1_bss_58[(lbl_1_bss_3D0.unk6 ^ 1) + 1], 0x18);
            HuAudFXPanning(HuAudFXPlay(0x842), (s16) (0x50 - (lbl_1_bss_3D0.unk6 << 5)));
            return;
        }
        return;
    case 2:
        lbl_1_bss_3D0.unkC += 1;
        if ((s16) lbl_1_bss_3D0.unkC == 4) {
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unk0 = 1;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC = 1.0f;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unk4 = 1.0f;
        }
        lbl_1_bss_44.x -= lbl_1_bss_38.x / 12.0f;
        lbl_1_bss_44.y = (f32) ((f64) lbl_1_bss_38.z + ((f64) lbl_1_bss_38.y * sin((3.141592653589793 * (f64) ((lbl_1_bss_3D0.unkC * 0x5A) / 12)) / 180.0)));
        if ((s16) lbl_1_bss_3D0.unkC == 0xC) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_44.x = 0.0f;
            lbl_1_bss_44.y = 300.0f;
            lbl_1_bss_3D0.unkC = 0;
            lbl_1_bss_38.x = lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk8 + (lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk10 - lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk0);
            lbl_1_bss_38.y = (300.0f - lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unkC) - (lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk14 - lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk4);
            return;
        }
        break;
    case 3:
        lbl_1_bss_3D0.unkC += 1;
        if ((s16) lbl_1_bss_3D0.unk6 != 0) {
            lbl_1_bss_44.x -= lbl_1_bss_38.x / lbl_1_bss_3D0.unk10[lbl_1_bss_3D0.unk6 ^ 1];
        } else {
            lbl_1_bss_44.x += lbl_1_bss_38.x / lbl_1_bss_3D0.unk10[lbl_1_bss_3D0.unk6 ^ 1];
        }
        lbl_1_bss_44.y = (f32) ((f64) (lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk14 - lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk4) + ((f64) lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unkC + ((f64) lbl_1_bss_38.y * sin((3.141592653589793 * (f64) (90.0f + ((f32) (lbl_1_bss_3D0.unkC * 0x5A) / lbl_1_bss_3D0.unk10[lbl_1_bss_3D0.unk6 ^ 1]))) / 180.0))));
        if ((f32) lbl_1_bss_3D0.unkC == lbl_1_bss_3D0.unk18[lbl_1_bss_3D0.unk6 ^ 1]) {
            lbl_1_bss_3D0.unkC = 0;
            lbl_1_bss_3F0.unkA4 += 1;
            if ((s16) lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_44.x = -lbl_1_bss_38.x;
            } else {
                lbl_1_bss_44.x = lbl_1_bss_38.x;
            }
            lbl_1_bss_44.y = lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unkC + (lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk14 - lbl_1_bss_384[lbl_1_bss_3D0.unk6 ^ 1].unk4);
            HuAudFXPlay(0x841);
            return;
        }
        break;
    case 4:
        lbl_1_bss_3D0.unkC += 1;
        Hu3DModelObjPosGet(lbl_1_bss_3F0.unk3C[(lbl_1_bss_3D0.unk6 ^ 1) + 0xC].unk0, lbl_1_data_4AC, &pos);
        if ((s16) lbl_1_bss_3D0.unk6 != 0) {
            lbl_1_bss_44.x = pos.x - (lbl_1_bss_384->unk10 - lbl_1_bss_384->unk0);
            lbl_1_bss_44.y = pos.y + (lbl_1_bss_384->unk14 - lbl_1_bss_384->unk4);
        } else {
            lbl_1_bss_44.x = pos.x + (lbl_1_bss_384[1].unk10 - lbl_1_bss_384[1].unk0);
            lbl_1_bss_44.y = pos.y + (lbl_1_bss_384[1].unk14 - lbl_1_bss_384[1].unk4);
        }
        if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6 ^ 1].unk2)) {
            lbl_1_bss_44.y += 40.0f;
            lbl_1_bss_44.x += -2.0f;
        }
        if (lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC == 49.0f) {
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unk4 = 0.0f;
        }
        if (lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC >= 50.0f) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3F0.unkA0 = sp8[lbl_1_bss_3D0.unk6 ^ 1];
            lbl_1_bss_3F0.unkA4 = 0;
            lbl_1_bss_3F0.unkA8 += 1;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC = 50.0f;
            lbl_1_bss_3D0.unk6 ^= 1;
        }
        if (lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unkC == 110.0f) {
            lbl_1_bss_3D0.unk0 = 1;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk0 = 0;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk2 = 0;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk4 = 1.0f;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk18 = 0x40000001;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk1C = 0x40000001;
            Hu3DMotionShiftSet(lbl_1_bss_3F0.unk3C[lbl_1_bss_3D0.unk6 + 0xC].unk0, *lbl_1_bss_3F0.unk48[lbl_1_bss_3D0.unk6], 0.0f, 10.0f, 0x40000001U);
        }
        break;
    }
}

void fn_1_3DCC(void) {
    Vec sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    s32 temp_r3;

    switch ((s32) lbl_1_bss_3F0.unkA4) {            /* irregular */
    case 0:
        memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6 + 1], 0x1C);
        if ((s16) lbl_1_bss_3D0.unk6 != 0) {
            lbl_1_bss_58->center.x = lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk10;
        } else {
            lbl_1_bss_58->center.x = -lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk10;
        }
        lbl_1_bss_58->zoom = 250.0f;
        if ((s16) lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk2 == 8) {
            lbl_1_bss_58->zoom = 400.0f;
        }
        lbl_1_bss_58->rot.y = 0.0f;
        omCameraViewMoveSimple(lbl_1_bss_58, 0xF);
        lbl_1_bss_3F0.unkA4 += 1;
        return;
    case 1:
        if (omCameraViewCheck(1U) != 0) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3F0.unkB0 = 0;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unk0 = 4;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unk20 = 0x40000001;
            Hu3DModelRotSet(lbl_1_bss_3F0.unk3C[lbl_1_bss_3D0.unk6 ^ 1 + 0xC].unk0, 0.0f, 0.0f, 0.0f);
            return;
        }
        return;
    case 2:
        temp_r3 = lbl_1_bss_3F0.unkB0;
        lbl_1_bss_3F0.unkB0 = temp_r3 + 1;
        if (temp_r3 > 0x14) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3F0.unkB0 = 0;
            lbl_1_bss_5F0 = 0;
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.015625f, 0.0f);
            return;
        }
        break;
    case 3:
        lbl_1_bss_3F0.unkB0 += 1;
        if ((s32) lbl_1_bss_3F0.unkB0 == 8) {
            Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C->unk0, 0.0f, 0.0f);
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.015625f, 0.0f);
        }
        if ((s32) lbl_1_bss_3F0.unkB0 == 0x10) {
            Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C->unk0, lbl_1_data_39C->unk4, 0.0f);
            HuAudFXPlay(0x83D);
            HuAudSStreamFadeOut(lbl_1_data_398, 0x64);
        }
        if (((s32) lbl_1_bss_3F0.unkB0 >= 0xC) && (fn_1_4658(0) != 0)) {
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_58->zoom = 750.0f;
            lbl_1_bss_58->rot.x = -25.0f;
            lbl_1_bss_3F0.unkCC = (f32) ((lbl_1_bss_3D0.unk6 * 0x12C) - 0x96);
            lbl_1_bss_3F0.unkD0 = (f32) (100.0 + (0.85 * (750.0 * sin(0.4363323129985824))));
            lbl_1_bss_3F0.unkD4 = (f32) (0.85 * (750.0 * cos(0.4363323129985824)));
            lbl_1_bss_3F0.unkD8 = 0.0f;
            lbl_1_bss_3F0.unkB0 = 0;
            lbl_1_bss_3F0.unkB4 = 0;
            sp14 = lbl_1_rodata_118;
            sp14.x = -120.0f + (f32) (lbl_1_bss_3D0.unk6 * 0xF0);
            fn_1_4FC4(&sp14);
            omCameraViewMoveSimple(lbl_1_bss_58, 0x14);
            omVibrate(lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk0, 0x28, 4, 2);
            return;
        }
        break;
    case 4:
        if (omCameraViewCheck(1U) != 0) {
            lbl_1_bss_3F0.unkB0 += 1;
            if ((s32) lbl_1_bss_3F0.unkB0 == 0x14) {
                omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_5098);
                HuAudFXPanning(HuAudFXPlay(0x843), (s16) (0x50 - (lbl_1_bss_3D0.unk6 << 5)));
            }
            if ((s32) lbl_1_bss_3F0.unkB0 == 0x1A) {
                omVibrate(lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk0, 0x78, 0xC, 0);
                Hu3DModelAttrSet(lbl_1_bss_3F0.unk3C[0xE].unk0, 1U);
                omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_4AA0);
                lbl_1_bss_3F0.unkC0 = 1.0f;
                lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk0 = 2;
                lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk4 = 0.0f;
                lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unkC = 0.0f;
                lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk20 = 0x40000001;
                Hu3DModelRotSet(lbl_1_bss_3F0.unk3C[lbl_1_bss_3D0.unk6 + 0xC].unk0, 0.0f, 0.0f, 0.0f);
            }
            if ((s32) lbl_1_bss_3F0.unkB0 > 0x78) {
                MgSeqModeNext();
                lbl_1_bss_3F0.unkA0 = 0;
                lbl_1_bss_3F0.unkA4 = 0;
            }
        }
        break;
    }
}

s32 fn_1_4658(s16 arg0) {
    f32 spC[14];
    s16 sp8;
    OMCAMERAVIEW *temp_r4;
    OMCAMERAVIEW *temp_r4_2;
    s32 var_r31;

    sp8 = arg0;
    spC[7] = lbl_1_rodata_15C[0];
    spC[8] = lbl_1_rodata_15C[1];
    spC[9] = lbl_1_rodata_15C[2];
    spC[10] = lbl_1_rodata_15C[3];
    spC[11] = lbl_1_rodata_15C[4];
    spC[12] = lbl_1_rodata_15C[5];
    spC[13] = lbl_1_rodata_15C[6];
    spC[0] = lbl_1_rodata_178[0];
    spC[1] = lbl_1_rodata_178[1];
    spC[2] = lbl_1_rodata_178[2];
    spC[3] = lbl_1_rodata_178[3];
    spC[4] = lbl_1_rodata_178[4];
    spC[5] = lbl_1_rodata_178[5];
    spC[6] = lbl_1_rodata_178[6];
    switch ((s32) lbl_1_bss_5F0) {                  /* irregular */
    case 0:
        var_r31 = 0;
loop_18:
        if (var_r31 < 7) {
            memcpy(&lbl_1_bss_58[var_r31 + 1], lbl_1_bss_58, 0x1C);
            if (sp8 != 0) {
                temp_r4 = &lbl_1_bss_58[var_r31 + 1];
                temp_r4->zoom += 5.0f * spC[var_r31];
                lbl_1_bss_58->rot.z = (f32) ((lbl_1_bss_3D0.unk6 * 0x32) - 0x19);
                if (var_r31 == 3) {
                    lbl_1_bss_58[var_r31 + 1].rot.z = (f32) ((lbl_1_bss_3D0.unk6 * 0x50) - 0x2D);
                }
                if (var_r31 == 4) {
                    lbl_1_bss_58[var_r31 + 1].rot.z = (f32) ((lbl_1_bss_3D0.unk6 * 0x32) - 0x19);
                }
                if (var_r31 == 5) {
                    lbl_1_bss_58[var_r31 + 1].rot.z = (f32) ((lbl_1_bss_3D0.unk6 * 0x46) - 0x23);
                }
                if (var_r31 >= 6) {
                    lbl_1_bss_58[var_r31 + 1].rot.z = (f32) ((lbl_1_bss_3D0.unk6 * 0x32) - 0x19);
                }
            } else {
                temp_r4_2 = &lbl_1_bss_58[var_r31 + 1];
                temp_r4_2->zoom += 3.0f * spC[var_r31];
            }
            var_r31 += 1;
            goto loop_18;
        }
        lbl_1_bss_5F0 += 1;
        lbl_1_bss_3F0.unkB4 = 0;
block_25:
    default:
        return 0;
    case 1:
        omCameraViewMoveSimple(&lbl_1_bss_58[lbl_1_bss_3F0.unkB4], 1);
        lbl_1_bss_3F0.unkB4 = (lbl_1_bss_3F0.unkB4 + 1) & 7;
        lbl_1_bss_5F0 += 1;
        goto block_25;
    case 2:
        if (omCameraViewCheck(1U) != 0) {
            if ((s32) lbl_1_bss_3F0.unkB4 != 0) {
                omCameraViewMoveSimple(&lbl_1_bss_58[lbl_1_bss_3F0.unkB4], 1);
                lbl_1_bss_3F0.unkB4 = (lbl_1_bss_3F0.unkB4 + 1) & 7;
                goto block_25;
            }
            return 1;
        }
        goto block_25;
    }
}

void fn_1_4AA0(omObjData *obj) {
    s32 sp8;
    HSFMATERIAL *var_r31;
    HU3DMODEL *temp_r29;
    s16 temp_r28;
    s32 temp_r30;
    s32 var_r27;

    temp_r28 = lbl_1_bss_3D0.unk6;
    sp8 = 1;
    temp_r29 = &Hu3DData[lbl_1_bss_3F0.unk3C[temp_r28 + 0xC].unk0];
    var_r31 = temp_r29->hsf->material;
    if (lbl_1_bss_3F0.unkC0 == 0.0f) {
        lbl_1_bss_3F0.unkB8 += 1;
        temp_r30 = lbl_1_bss_3F0.unkB8;
        if (temp_r30 == 0x19) {
            HuAudFXPlay(0x844);
        }
        if (temp_r30 <= 0x19) {
            lbl_1_bss_5F0 = 0;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unkC = (10.0f * (f32) temp_r30) / 25.0f;
            Hu3DModelPosSet(lbl_1_bss_3F0.unk3C[temp_r28 + 0xC].unk0, lbl_1_bss_3F0.unkCC, (lbl_1_bss_3F0.unkD0 * (f32) temp_r30) / 25.0f, (lbl_1_bss_3F0.unkD4 * (f32) temp_r30) / 25.0f);
        } else if (lbl_1_bss_3F0.unkD8 == 0.0f) {
            if (fn_1_4658(1) != 0) {
                lbl_1_bss_3F0.unkD8 = 1.0f;
            }
        } else if (lbl_1_bss_3F0.unkD8 < 60.0f) {
            lbl_1_bss_3F0.unkD0 = (f32) ((f64) lbl_1_bss_3F0.unkD0 - (10.0 * sin((3.141592653589793 * (f64) lbl_1_bss_3F0.unkD8) / 180.0)));
            Hu3DModelPosSet(lbl_1_bss_3F0.unk3C[temp_r28 + 0xC].unk0, lbl_1_bss_3F0.unkCC, lbl_1_bss_3F0.unkD0, lbl_1_bss_3F0.unkD4);
            lbl_1_bss_3F0.unkD8 += 1.0f;
        } else {
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk18 = 1;
        }
        return;
    }
    lbl_1_bss_3F0.unkC0 = (f32) ((f64) lbl_1_bss_3F0.unkC0 - 0.2);
    if (lbl_1_bss_3F0.unkC0 < 0.0f) {
        lbl_1_bss_3F0.unkC0 = 0.0f;
    }
    if (lbl_1_bss_3F0.unkC0 >= 0.4f) {
        var_r27 = 0;
loop_17:
        if (var_r27 < (s16) temp_r29->hsf->materialNum) {
            var_r31->color[0] = (u8) (s32) ((f32) var_r31->color[0] * lbl_1_bss_3F0.unkC0);
            var_r31->color[1] = (u8) (s32) ((f32) var_r31->color[1] * lbl_1_bss_3F0.unkC0);
            var_r31->color[2] = (u8) (s32) ((f32) var_r31->color[2] * lbl_1_bss_3F0.unkC0);
            var_r27 += 1;
            var_r31++;
            goto loop_17;
        }
    }
}

void fn_1_4F44(void) {
    f32 sp10;
    f32 spC;
    f32 sp8;

    lbl_1_bss_3B8.unkC = lbl_1_rodata_1C8;
    lbl_1_bss_3B8.unk8 = 0;
    lbl_1_bss_3B8.unk4 = 0;
    lbl_1_bss_3B8.unk0 = 0;
}

void fn_1_4FC4(Vec *pos) {
    lbl_1_bss_3B8.unk0 = 1;
    lbl_1_bss_3B8.unk8 = 0;
    lbl_1_bss_3B8.unk4 = 0;
    lbl_1_bss_3B8.unkC.x = pos->x;
    lbl_1_bss_3B8.unkC.y = pos->y;
    lbl_1_bss_3B8.unkC.z = pos->z;
}

void fn_1_5014(s32 show) {
    s32 sp8;
    s16 temp_r30;
    s32 var_r31;

    sp8 = show;
    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        temp_r30 = lbl_1_bss_3F0.unk3C[var_r31 + 0xF].unk0;
        if (sp8 != 0) {
            Hu3DModelAttrReset(temp_r30, 0x400000U);
        } else {
            Hu3DModelAttrSet(temp_r30, 0x400000U);
        }
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_5098(omObjData *obj) {
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r31;
    s16 temp_r31_2;
    s16 temp_r31_3;
    s32 temp_r0_6;
    s32 var_r30;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_5;
    u32 temp_r3;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 temp_r4_4;

    switch ((s32) lbl_1_bss_3B8.unk0) {             /* irregular */
        return;
    case 1:
        temp_r31 = lbl_1_bss_3F0.unk3C[0xF].unk0;
        Hu3DModelPosSet(temp_r31, lbl_1_bss_3B8.unkC.x, lbl_1_bss_3B8.unkC.y, lbl_1_bss_3B8.unkC.z);
        Hu3DModelScaleSet(temp_r31, 1.5f, 1.5f, 1.0f);
        Hu3DModelAttrReset(temp_r31, 1U);
        Hu3DMotionTimeSet(temp_r31, 0.0f);
        lbl_1_bss_3B8.unk8 = 0;
        lbl_1_bss_3B8.unk0 += 1;
    default:
block_17:
        var_r30 = 0;
loop_21:
        if (var_r30 < 4) {
            temp_r31_2 = lbl_1_bss_3F0.unk3C[var_r30 + 0xF].unk0;
            temp_f31 = Hu3DMotionTimeGet(temp_r31_2);
            if (!(temp_f31 < Hu3DMotionMaxTimeGet(temp_r31_2))) {
                Hu3DModelAttrSet(temp_r31_2, 1U);
            }
            var_r30 += 1;
            goto loop_21;
        }
        return;
    case 2:
        temp_r3 = (u32) lbl_1_bss_3B8.unk8 >> 0x1FU;
        temp_r0 = (lbl_1_bss_3B8.unk8 << 0x1E) - temp_r3;
        temp_r31_3 = lbl_1_bss_3F0.unk3C[(lbl_1_bss_3B8.unk8 % 4) + 0x10].unk0;
        temp_r4 = (u32) lbl_1_bss_3B8.unk8 >> 0x1FU;
        temp_r0_2 = (lbl_1_bss_3B8.unk8 << 0x1E) - temp_r4;
        temp_r4_2 = (u32) lbl_1_bss_3B8.unk8 >> 0x1FU;
        temp_r0_3 = (lbl_1_bss_3B8.unk8 << 0x1E) - temp_r4_2;
        temp_r4_3 = (u32) lbl_1_bss_3B8.unk8 >> 0x1FU;
        temp_r0_4 = (lbl_1_bss_3B8.unk8 << 0x1E) - temp_r4_3;
        Hu3DModelPosSet(temp_r31_3, lbl_1_bss_3B8.unkC.x + lbl_1_data_4C8[(lbl_1_bss_3B8.unk8 % 4)], lbl_1_bss_3B8.unkC.y + lbl_1_data_4D8[(lbl_1_bss_3B8.unk8 % 4)], lbl_1_bss_3B8.unkC.z + lbl_1_data_4E8[(lbl_1_bss_3B8.unk8 % 4)]);
        Hu3DModelScaleSet(temp_r31_3, 1.25f, 1.25f, 1.0f);
        Hu3DModelAttrReset(temp_r31_3, 1U);
        Hu3DMotionTimeSet(temp_r31_3, 0.0f);
        temp_r4_4 = (u32) lbl_1_bss_3B8.unk8 >> 0x1FU;
        temp_r0_5 = (lbl_1_bss_3B8.unk8 << 0x1E) - temp_r4_4;
        Hu3DMotionSpeedSet(temp_r31_3, lbl_1_data_4F8[(lbl_1_bss_3B8.unk8 % 4)]);
        lbl_1_bss_3B8.unk4 = 0;
        lbl_1_bss_3B8.unk0 += 1;
        goto block_17;
    case 3:
        temp_r0_6 = lbl_1_bss_3B8.unk4 + 1;
        lbl_1_bss_3B8.unk4 = temp_r0_6;
        if (temp_r0_6 >= 6) {
            lbl_1_bss_3B8.unk8 += 1;
            if ((s32) lbl_1_bss_3B8.unk8 == 4) {
                lbl_1_bss_3B8.unk0 += 1;
            } else {
                lbl_1_bss_3B8.unk0 -= 1;
            }
        }
        goto block_17;
    case 4:
        temp_f31_2 = Hu3DMotionTimeGet(lbl_1_bss_3F0.unk3C[0x13].unk0);
        if (!(temp_f31_2 < Hu3DMotionMaxTimeGet(lbl_1_bss_3F0.unk3C[0x13].unk0))) {
            lbl_1_bss_3B8.unk0 = 0;
        }
        goto block_17;
    }
}

void fn_1_54C0(void) {
    s32 sp18[3];
    s32 sp8[4];
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    u32 temp_r0;
    u32 temp_r3_2;
    u8 temp_r3;

    sp18[0] = lbl_1_rodata_1DC[0];
    sp18[1] = lbl_1_rodata_1DC[1];
    sp18[2] = lbl_1_rodata_1DC[2];
    sp8[0] = lbl_1_rodata_1E8[0];
    sp8[1] = lbl_1_rodata_1E8[1];
    sp8[2] = lbl_1_rodata_1E8[2];
    sp8[3] = lbl_1_rodata_1E8[3];
    if ((u32) lbl_1_bss_3F0.unkA4 <= 9U) {
        switch (lbl_1_bss_3F0.unkA4) {
        case 0:
            temp_r3 = rand8();
            temp_r3_2 = temp_r3 >> 0x1FU;
            temp_r0 = (temp_r3 << 0x1E) - temp_r3_2;
            lbl_1_bss_3F0.unkA4 = sp8[(temp_r3 % 4)];
            HuAudFXPlay(0x840);
            lbl_1_bss_3F0.unkB0 = 0;
            break;
        case 1:
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3F0.unkB0 = -0x1E;
            break;
        case 2:
            temp_r3_3 = lbl_1_bss_3F0.unkB0;
            lbl_1_bss_3F0.unkB0 = temp_r3_3 + 1;
            if (temp_r3_3 > 0x1E) {
                lbl_1_bss_3F0.unkA4 = 0;
            }
            break;
        case 3:
            omVibrate(lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk0, 0x14, 0xC, 0);
            lbl_1_bss_3F0.unkB0 = -0x1E;
            lbl_1_bss_3F0.unkA4 = 2;
            break;
        case 4:
            memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6 + 1], 0x1C);
            if ((s16) lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_58->center.x = lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk10;
            } else {
                lbl_1_bss_58->center.x = -lbl_1_bss_384[lbl_1_bss_3D0.unk6].unk10;
            }
            lbl_1_bss_58->zoom = 250.0f;
            lbl_1_bss_58->rot.y = 0.0f;
            if ((s16) lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6].unk2 == 8) {
                lbl_1_bss_58->zoom = 400.0f;
            }
            omCameraViewMoveSimple(lbl_1_bss_58, 0xF);
            lbl_1_bss_3F0.unkA4 += 1;
            break;
        case 5:
            if (omCameraViewCheck(1U) != 0) {
                temp_r3_4 = lbl_1_bss_3F0.unkB0;
                lbl_1_bss_3F0.unkB0 = temp_r3_4 + 1;
                if (temp_r3_4 > 0x14) {
                    memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6 + 1], 0x1C);
                    omCameraViewMoveSimple(lbl_1_bss_58, 0xF);
                    lbl_1_bss_3F0.unkA4 += 1;
                }
            }
            break;
        case 6:
            if (omCameraViewCheck(1U) != 0) {
                lbl_1_bss_3F0.unkA4 = 0;
            }
            break;
        case 7:
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.0078125f, 0.0f);
            lbl_1_bss_3F0.unkA4 += 1;
            lbl_1_bss_3F0.unkB0 = 0;
            break;
        case 8:
            temp_r3_5 = lbl_1_bss_3F0.unkB0;
            lbl_1_bss_3F0.unkB0 = temp_r3_5 + 1;
            if (temp_r3_5 > 0xE) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1].unk0, 0.125f + lbl_1_data_39C[1].unk4, 0.0f);
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.0078125f, 0.0f);
                lbl_1_bss_3F0.unkA4 += 1;
                lbl_1_bss_3F0.unkB0 = 0;
            }
            break;
        case 9:
            temp_r3_6 = lbl_1_bss_3F0.unkB0;
            lbl_1_bss_3F0.unkB0 = temp_r3_6 + 1;
            if (temp_r3_6 > 0xE) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1].unk0, lbl_1_data_39C[1].unk4, 0.0f);
                lbl_1_bss_3F0.unkB0 = 0;
                lbl_1_bss_3F0.unkA4 = 2;
            }
            break;
        }
    }
    if ((s32) lbl_1_bss_3F0.unkA4 == 0) {
        lbl_1_bss_3F0.unkA0 = sp18[lbl_1_bss_3D0.unk6];
        lbl_1_bss_3F0.unkB0 = 0;
    }
}

void fn_1_59FC(void) {
    s32 spC[2];
    s32 sp8;

    spC[0] = lbl_1_rodata_200[0];
    spC[1] = lbl_1_rodata_200[1];
    sp8 = 0;
    switch ((s32) lbl_1_bss_3F0.unkA4) {            /* irregular */
    case 0:
        lbl_1_bss_3F0.unkA4 += 1;
        lbl_1_bss_5D2[1] = lbl_1_bss_3D0.unk8 * 0x10;
        lbl_1_bss_5D2[0] = -1;
        if ((s16) lbl_1_bss_3D0.unk4 == 6) {
            if ((s16) lbl_1_bss_3D0.unk8 == 1) {
                lbl_1_bss_5D2[0] = 8;
            } else {
                lbl_1_bss_5D2[0] = 0x18;
            }
        }
        if (((s16) lbl_1_bss_3D0.unk4 == 5) && ((s16) lbl_1_bss_3D0.unk8 == 2)) {
            lbl_1_bss_5D2[0] = 8;
        }
        if ((s16) lbl_1_bss_3D0.unk4 == 3) {
            lbl_1_bss_5D2[1] = 0x10;
        }
        if ((s16) lbl_1_bss_3D0.unk2 != 0) {
            lbl_1_bss_5D2[0] = 8;
            lbl_1_bss_5D2[1] = 0x10;
        }
        lbl_1_bss_5D8 = -0.015625f;
        Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, lbl_1_bss_5D8, 0.0f);
        return;
    case 1:
        lbl_1_bss_3D0.unkA += 1;
        if ((s16) lbl_1_bss_3D0.unkA == (s16) lbl_1_bss_5D2[0]) {
            if ((s16) lbl_1_bss_3D0.unk2 != 0) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1].unk0, 0.125f + lbl_1_data_39C[1].unk4, 0.0f);
            } else {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[3].unk0, 0.125f + lbl_1_data_39C[3].unk4, 0.0f);
            }
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, lbl_1_bss_5D8, 0.0f);
        }
        if ((s16) lbl_1_bss_3D0.unkA == (s16) lbl_1_bss_5D2[1]) {
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, 0.0f, 0.0f);
            lbl_1_bss_3F0.unkA0 = spC[lbl_1_bss_3D0.unk6];
            lbl_1_bss_3F0.unkA4 = 0;
            lbl_1_bss_3D0.unkA = 0;
            lbl_1_bss_3D0.unk8 = 0;
        }
        return;
    }
}

void fn_1_5D84(void) {
    s32 sp8[2];

    sp8[0] = lbl_1_rodata_208[0];
    sp8[1] = lbl_1_rodata_208[1];
    if (fn_1_196C() == 0) {
        lbl_1_bss_3F0.unkA0 = sp8[lbl_1_bss_3D0.unk6];
    }
}

void fn_1_5DF4(void) {
    s16 temp_r30;
    s32 temp_r31;

    temp_r31 = lbl_1_bss_3D0.unk6 ^ 1;
    switch ((s32) lbl_1_bss_3F0.unkA4) {            /* irregular */
    case 0:
        lbl_1_bss_58->zoom = 400.0f;
        lbl_1_bss_58->center.x = (f32) ((temp_r31 * 0x12C) - 0x96);
        lbl_1_bss_58->rot.x = -25.0f;
        lbl_1_bss_58->rot.y = 0.0f;
        lbl_1_bss_58->center.y = 200.0f;
        omCameraViewMoveSimple(lbl_1_bss_58, 0x1E);
        lbl_1_bss_3F0.unkA4 += 1;
        return;
    case 1:
        if (omCameraViewCheck(1U) != 0) {
            lbl_1_bss_3F0.unk50[temp_r31].unk0 = 3;
            lbl_1_bss_3F0.unk50[temp_r31].unk2 = 3;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk18 = 0;
            lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6].unk1C = 0;
            Hu3DMotionShiftSet(lbl_1_bss_3F0.unk3C[temp_r31 + 0xC].unk0, lbl_1_bss_3F0.unk48[temp_r31][3], 0.0f, 10.0f, 0U);
            lbl_1_bss_5D0 = MGSeqWinCreate(lbl_1_bss_3F0.unk4[temp_r31].unk2, -1, -1, -1);
            lbl_1_bss_3F0.unkA4 += 1;
            HuAudJinglePlay(0x79);
            temp_r30 = lbl_1_bss_3F0.unk4[temp_r31].unk0;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r30].coin_win = 0xA;
            }
            lbl_1_bss_5D2[0] = 0;
            return;
        }
        return;
    case 2:
        lbl_1_bss_5D2[0] += 1;
        if ((GameMesStatGet(lbl_1_bss_5D0) == 0) && ((s16) lbl_1_bss_5D2[0] >= 0xD0)) {
            GameMesKill(lbl_1_bss_5D0);
            MgSeqModeNext();
        }
        break;
    }
}



void ObjectSetup(void) {
    fn_1_6104(&lbl_1_bss_3F0, lbl_1_bss_154, lbl_1_data_138);
    lbl_1_bss_3F0.unk0 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_3F0.unk0);
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_6890);
    MgSeqCreate(&lbl_1_data_2F0);
}

void fn_1_15C(s16 arg0, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    s16 sp8;
    f32 temp_f0;
    s16 temp_r3;
    s32 var_r31;
    s32 var_r31_2;

    sp8 = arg0;
    lbl_1_bss_3D0.unk4 = 9;
    fn_1_6350(1);
    fn_1_65E8(&lbl_1_data_184[Mp5CharNo(lbl_1_bss_3F0.unk4[0].unk2)], &lbl_1_data_184[Mp5CharNo(lbl_1_bss_3F0.unk4[1].unk2)]);
    fn_1_660C(lbl_1_bss_138[0], lbl_1_bss_138[1]);
    fn_1_6630();
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_384[var_r31].unk0 = *lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)];
        lbl_1_bss_384[var_r31].unk4 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][1];
        lbl_1_bss_384[var_r31].unk8 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][2];
        lbl_1_bss_384[var_r31].unkC = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][3];
        lbl_1_bss_384[var_r31].unk10 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][4];
        lbl_1_bss_384[var_r31].unk14 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][5];
        if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[var_r31].unk2)) {
            lbl_1_bss_384[var_r31].unk14 += 14.0f;
        }
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_167C();
    fn_1_6D4C();
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_6EA0);
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 2) {
        CharMotionUpdateSet(lbl_1_bss_3F0.unk4[var_r31_2].unk2, lbl_1_data_184[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31_2].unk2)].unk0[1], 0);
        var_r31_2 += 1;
        goto loop_5;
    }
    temp_f0 = -lbl_1_bss_384->unk10;
    Center.x = temp_f0;
    lbl_1_bss_58->center.x = temp_f0;
    Center.y = lbl_1_bss_384->unk14;
    lbl_1_bss_58->center.y = lbl_1_bss_384->unk14;
    Center.z = 0.0f;
    lbl_1_bss_58->center.z = 0.0f;
    CRot.x = -20.0f;
    lbl_1_bss_58->rot.x = -20.0f;
    CRot.y = 0.0f;
    lbl_1_bss_58->rot.y = 0.0f;
    CRot.z = 0.0f;
    lbl_1_bss_58->rot.z = 0.0f;
    CZoom = 200.0f;
    lbl_1_bss_58->zoom = 200.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_1204);
    fn_1_1CB4();
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_1D84);
    fn_1_4F44();
    Hu3DBGColorSet(0xBAU, 0xF5U, 0xFFU);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
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
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    Hu3DShadowSizeSet(0xC8U);
    Hu3DModelShadowSet(lbl_1_bss_3F0.unk3C[0xC].unk0);
    Hu3DModelShadowSet(lbl_1_bss_3F0.unk3C[0xD].unk0);
    Hu3DModelShadowSet(lbl_1_bss_3F0.unk3C[0xE].unk0);
    lbl_1_bss_3F0.unk50[0].unk0 = 1;
    lbl_1_bss_3F0.unk50[0].unk4 = 0.0f;
    lbl_1_bss_3F0.unk50[0].unkC = 50.0f;
    lbl_1_bss_3F0.unk50[0].unk20 = 0x40000001;
    lbl_1_bss_3F0.unk50[1].unk0 = 0;
    lbl_1_bss_3F0.unk50[1].unk4 = 1.0f;
    lbl_1_bss_3F0.unk50[1].unkC = 0.0f;
    lbl_1_bss_3F0.unk50[1].unk18 = 0x40000001;
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_19A4);
    lbl_1_bss_20[1] = 0;
    lbl_1_bss_20[0] = 0;
    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, fn_1_70B0);
    lbl_1_bss_54 = NULL;
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    MgSeqModeNext();
}

void fn_1_8C0(s16 mode, s16 frameNo) {
    if (WipeCheckEnd() == 0) {
        switch ((s32) lbl_1_bss_3F0.unkA0) {        /* irregular */
        case 0:
            fn_1_23A4();
            break;
        case 1:
            fn_1_257C();
            break;
        case 2:
            fn_1_282C();
            break;
        }
    }
    fn_1_202C();
}

void fn_1_934(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    lbl_1_bss_3F0.unkA0 = 0;
    lbl_1_bss_3F0.unkA4 = 0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    fn_1_202C();
    if ((s32) lbl_1_data_398 < 0) {
        lbl_1_data_398 = HuAudBGMPlay(0x3B);
    }
}

void fn_1_9B4(s16 mode, s16 frameNo) {
    lbl_1_data_318[lbl_1_bss_3F0.unkA0]();
    fn_1_202C();
}

void fn_1_9FC(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    lbl_1_bss_3F0.unkA0 = 0;
    lbl_1_bss_3F0.unkA4 = 0;
    fn_1_202C();
}

void fn_1_A54(s16 mode, s16 frameNo) {
    fn_1_5DF4();
    fn_1_202C();
}

void fn_1_A78(s16 mode, s16 frameNo) {
    fn_1_202C();
    MgSeqModeNext();
}

void fn_1_A9C(s16 mode, s16 frameNo) {
    fn_1_202C();
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

void fn_1_AD0(s16 mode, s16 frameNo) {

}



void fn_1_1204(omObjData *obj) {
    Hu3DModelPosSet(lbl_1_bss_50, lbl_1_bss_44.x, lbl_1_bss_44.y + lbl_1_bss_28, lbl_1_bss_44.z);
}


void fn_1_167C(void) {
    s16 temp_r3;
    s16 temp_r3_2;
    s32 var_r30;

    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(*lbl_1_data_168, MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_3F0.unk3C[0xE].unk0 = temp_r3;
    lbl_1_bss_50 = temp_r3;
    Hu3DModelAttrSet(temp_r3, 1U);
    Hu3DModelPosSet(temp_r3, -140.0f, 215.0f, 0.0f);
    Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(temp_r3, 1U);
    Hu3DModelAttrReset(temp_r3, 1U);
    lbl_1_bss_3B4 = Hu3DTexScrollCreate(temp_r3, "m548time");
    lbl_1_bss_44.x = -lbl_1_bss_384->unk10;
    if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[0].unk2)) {
        lbl_1_bss_44.x += 32.0f;
    }
    lbl_1_bss_44.y = lbl_1_bss_384->unk14;
    lbl_1_bss_44.z = 0.0f;
    lbl_1_bss_38.x = 0.0f;
    lbl_1_bss_38.y = 0.0f;
    lbl_1_bss_38.z = 0.0f;
    var_r30 = 0;
loop_2:
    if (var_r30 < 5) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_168[var_r30 + 1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_3F0.unk3C[var_r30 + 0xF].unk0 = temp_r3_2;
        Hu3DModelAttrSet(temp_r3_2, 1U);
        Hu3DModelPosSet(temp_r3_2, -500.0f + (1000.0f * (f32) var_r30), 500.0f, 200.0f);
        Hu3DModelRotSet(temp_r3_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(temp_r3_2, 7);
        Hu3DModelCameraSet(temp_r3_2, 1U);
        Hu3DMotionSpeedSet(temp_r3_2, 1.0f);
        Hu3DMotionTimeSet(temp_r3_2, 0.0f);
        var_r30 += 1;
        goto loop_2;
    }
    fn_1_5014(1);
}

void fn_1_194C(void) {
    lbl_1_bss_20[1] = 0;
    lbl_1_bss_20[0] = 0;
}

s32 fn_1_196C(void) {
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;

    temp_r3_2 = lbl_1_bss_20[lbl_1_bss_3D0.unk6];
    temp_r3 = temp_r3_2 >> 0x1FU;
    temp_r0 = (temp_r3_2 << 0x1B) - temp_r3;
    return (temp_r3_2 % 32);
}

void fn_1_19A4(omObjData *obj) {
    s32 var_r31;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;

    lbl_1_bss_28 = 0.0f;
    var_r31 = 0;
loop_8:
    if (var_r31 < 2) {
        if ((lbl_1_bss_3F0.unk50[var_r31].unkC == 50.0f) || (lbl_1_bss_3F0.unk50[var_r31].unkC == 51.0f)) {
            if ((s16) lbl_1_bss_3F0.unk50[var_r31].unk0 == 1) {
                temp_r3 = lbl_1_bss_20[var_r31] + 1;
                temp_r3_2 = temp_r3 >> 0x1FU;
                temp_r0 = (temp_r3 << 0x1A) - temp_r3_2;
                lbl_1_bss_20[var_r31] = (temp_r3 % 64);
                Hu3DModelScaleSet(lbl_1_bss_3F0.unk3C[var_r31 + 0xC].unk0, 1.0f, (f32) (1.0 - (0.009999999776482582 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_20[var_r31] * 0x168) / 64)) / 180.0))), 1.0f);
                lbl_1_bss_28 = (f32) (-1.0 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_20[var_r31] * 0x168) / 64)) / 180.0));
            } else {
                lbl_1_bss_20[var_r31] = 0;
                Hu3DModelScaleSet(lbl_1_bss_3F0.unk3C[var_r31 + 0xC].unk0, 1.0f, 1.0f, 1.0f);
            }
        } else {
            lbl_1_bss_20[var_r31] = 0;
            Hu3DModelScaleSet(lbl_1_bss_3F0.unk3C[var_r31 + 0xC].unk0, 1.0f, 1.0f, 1.0f);
        }
        var_r31 += 1;
        goto loop_8;
    }
}

void fn_1_1CB4(void) {
    s32 var_r31;
    u32 temp_r4;
    u8 temp_r3;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_0[var_r31].unk0 = 0;
        lbl_1_bss_0[var_r31].unk4 = 0;
        lbl_1_bss_0[var_r31].unk8 = (rand8() % 10) + 0x1E;
        temp_r3 = rand8();
        temp_r4 = temp_r3 >> 0x1FU;
        lbl_1_bss_0[var_r31].unkC = (((temp_r3 & 1) ^ temp_r4) - temp_r4) + 6;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_6104(M548Work *work, M548Model *models, s32 *dataNums) {
    s32 *sp10;
    M548Model *spC;
    M548Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_5F8 = sp8;
    memset(lbl_1_bss_5F8, 0, sizeof(M548Work));
    lbl_1_bss_5F8->unk3C = spC;
    lbl_1_bss_5F8->unk98 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_5F8->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_5F8->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_5F8->unk4[var_r31_2].unk0].character;
        lbl_1_bss_5F8->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_5F8->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_5F8->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_5F8->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_5F8->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_6350(s16 arg) {
    s16 sp8;
    s16 temp_r3;
    s16 var_r31;

    sp8 = arg;
    lbl_1_bss_5F8->unk9C = sp8;
    var_r31 = 0;
loop_4:
    if (var_r31 < 0xC) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_5F8->unk98[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_5F8->unk3C[var_r31].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DModelPosSetV(temp_r3, &lbl_1_data_530[var_r31]);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(temp_r3, 0.0f);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        lbl_1_bss_5F8->unk3C[var_r31].unk4.x = lbl_1_data_530[var_r31].x;
        lbl_1_bss_5F8->unk3C[var_r31].unk4.y = lbl_1_data_530[var_r31].y;
        lbl_1_bss_5F8->unk3C[var_r31].unk4.z = lbl_1_data_530[var_r31].z;
        lbl_1_bss_5F8->unk3C[var_r31].unk10.x = 0.0f;
        lbl_1_bss_5F8->unk3C[var_r31].unk10.y = 0.0f;
        lbl_1_bss_5F8->unk3C[var_r31].unk10.z = 0.0f;
        Hu3DModelAttrReset(temp_r3, 1U);
        if (var_r31 == 0) {
            Hu3DModelShadowMapSet(temp_r3);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_65E8(M548Char *chr0, M548Char *chr1) {
    lbl_1_bss_5F8->unk40[0] = chr0;
    lbl_1_bss_5F8->unk40[1] = chr1;
}

void fn_1_660C(s16 *mot0, s16 *mot1) {
    lbl_1_bss_5F8->unk48[0] = mot0;
    lbl_1_bss_5F8->unk48[1] = mot1;
}

void fn_1_6630(void) {
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0 = CharModelCreate(lbl_1_bss_5F8->unk4[var_r31].unk2, 1);
        Hu3DModelPosSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, (f32) ((var_r31 * 0x12C) - 0x96), 100.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 0.0f, 90.0f + (180.0f * (f32) var_r31), 0.0f);
        if (var_r31 != 0) {
            Hu3DModelAttrSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 0x40000001U);
            Hu3DMotionSpeedSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 1.0f);
            Hu3DMotionTimeSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 0.0f);
        } else {
            Hu3DModelAttrReset(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 0x40000001U);
            Hu3DMotionSpeedSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_5F8->unk3C[var_r31 + 0xC].unk0, 25.0f);
        }
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6890(omObjData *obj) {
    s32 var_r31;
    s8 var_r27;
    s8 var_r28;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_5F8->unk4[var_r31].unk4 != 0) {
            memset((M548Work *) &lbl_1_bss_5F8->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_5F8->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_5F8->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk10;
            }
            lbl_1_bss_5F8->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_5F8->unk4[var_r31].unk11 = (s8) (u8) HuPadStkY[lbl_1_bss_5F8->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk11 >= 0) {
                var_r28 = (s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk11;
            } else {
                var_r28 = -(s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk11;
            }
            if (var_r28 < 0xA) {
                var_r27 = 0;
            } else {
                var_r27 = (s8) (u8) lbl_1_bss_5F8->unk4[var_r31].unk11;
            }
            lbl_1_bss_5F8->unk4[var_r31].unk11 = var_r27;
            lbl_1_bss_5F8->unk4[var_r31].unk14 = (s8) (u8) HuPadSubStkX[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkY[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk16 = HuPadTrigL[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk17 = HuPadTrigR[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk18 = HuPadDStk[lbl_1_bss_5F8->unk4[var_r31].unk6];
            lbl_1_bss_5F8->unk4[var_r31].unk19 = HuPadDStkRep[lbl_1_bss_5F8->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_6D4C(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 5) {
            lbl_1_bss_5F8->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_5F8->unk4[var_r31].unk2, lbl_1_bss_5F8->unk40[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_5F8->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_5F8->unk50[var_r31_2].unk4 = 1.0f;
        lbl_1_bss_5F8->unk50[var_r31_2].unk8 = -1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

static const f32 sMp5MotLen[5] = { 59.0f, 119.0f, 9.0f, 0.0f, 24.0f };
static f32 sDkMotScale[2] = { 1.0f, 1.0f }; // MP4 motion length / MP5 motion length
static s32 sDkCarryFixed[2];

static void Mp5DkCarryFix(s16 model, s16 motId)
{
    HSFDATA *hsf = Hu3DData[model].hsf;
    HSFMOTION *mo = Hu3DMotion[motId].hsf->motion;
    s32 ti;
    for (ti = 0; ti < mo->numTracks; ti++) {
        HSFTRACK *tr = &mo->track[ti];
        if (tr->type == HSF_TRACK_TRANSFORM && tr->curveType == HSF_CURVE_CONST && tr->target < hsf->objectNum) {
            const char *name = hsf->object[tr->target].name;
            if (tr->channel == HSF_CHANNEL_ROTX && strcmp(name, "root_R_hand") == 0) {
                tr->value += 125.0f;
            } else if (tr->channel == HSF_CHANNEL_ROTZ && strcmp(name, "root_head") == 0) {
                tr->value += -35.0f;
            } else if (tr->channel >= HSF_CHANNEL_SCALEX && tr->channel <= HSF_CHANNEL_SCALEZ
                && (strcmp(name, "donkey_L_eye") == 0 || strcmp(name, "donkey_R_eye") == 0)) {
                tr->value += 1.0f;
            }
        }
    }
}

void fn_1_6EA0(omObjData *obj) {
    M548Anim *temp_r31;
    s16 temp_r0;
    s16 var_r29;

    var_r29 = 0;
loop_12:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_5F8->unk50[var_r29];
        temp_r0 = var_r29 + 0xC;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, lbl_1_bss_5F8->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0);
            sDkMotScale[var_r29] = 1.0f;
            if (temp_r31->unk0 == 1 && !Mp5CharHasMotions(lbl_1_bss_5F8->unk4[var_r29].unk2) && !sDkCarryFixed[var_r29]) {
                sDkCarryFixed[var_r29] = 1;
                Mp5DkCarryFix(lbl_1_bss_5F8->unk3C[temp_r0].unk0, lbl_1_bss_5F8->unk48[var_r29][1]);
            }
            if (!Mp5CharHasMotions(lbl_1_bss_5F8->unk4[var_r29].unk2) && sMp5MotLen[temp_r31->unk0] > 0.0f) {
                sDkMotScale[var_r29] = temp_r31->unk14 / sMp5MotLen[temp_r31->unk0];
                temp_r31->unk14 = sMp5MotLen[temp_r31->unk0];
                temp_r31->unk8 = temp_r31->unk4 + 1.0f; // re-apply the (scaled) speed below
            }
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unk4 * sDkMotScale[var_r29]);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r31->unk20 = 0;
            temp_r31->unk18 = 0;
            temp_r31->unk1C = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unkC * sDkMotScale[var_r29]);
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0) / sDkMotScale[var_r29];
        if (sDkMotScale[var_r29] != 1.0f) {
            f32 whole = (f32)(s32)(temp_r31->unkC + 0.5f);
            if (temp_r31->unkC - whole < 0.01f && whole - temp_r31->unkC < 0.01f) {
                temp_r31->unkC = whole;
            }
        }
        temp_r31->unk10 = temp_r31->unkC;
        var_r29 += 1;
        goto loop_12;
    }
}

void fn_1_70B0(omObjData *obj) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        lbl_1_data_5C0[var_r31]();
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_7104(void) {
    M548Model *temp_r3;
    s32 temp_r0;
    s32 temp_r3_2;

    temp_r3 = lbl_1_bss_5F8->unk3C;
    if ((s32) lbl_1_bss_5F8->unkF0[0].unk0 == 0) {
        temp_r0 = lbl_1_bss_5F8->unkF0[0].unkC;
        switch (temp_r0) {                          /* irregular */
        case 0:
            lbl_1_bss_5F8->unkF0[0].unk4 = (rand8() % 120) + 0xB4;
            lbl_1_bss_5F8->unkF0[0].unkC = 1;
            lbl_1_bss_5F8->unkF0[0].unk24 = 0.4f;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, lbl_1_bss_5F8->unkF0[0].unk24);
            temp_r3[3].unk10.y = -60.0f;
            return;
        case 1:
            temp_r3_2 = lbl_1_bss_5F8->unkF0[0].unk4;
            lbl_1_bss_5F8->unkF0[0].unk4 = temp_r3_2 - 1;
            if (temp_r3_2 < 0) {
                lbl_1_bss_5F8->unkF0[0].unkC += 1;
                lbl_1_bss_5F8->unkF0[0].unk4 = 0;
                lbl_1_bss_5F8->unkF0[0].unk20 = temp_r3[3].unk10.y;
                lbl_1_bss_5F8->unkF0[0].unk8 = 0x78;
                lbl_1_bss_5F8->unkF0[0].unk24 = (f32) ((rand8() % 10) + 0x1E);
                if (lbl_1_bss_5F8->unkF0[0].unk20 > -45.0f) {
                    lbl_1_bss_5F8->unkF0[0].unk24 = -lbl_1_bss_5F8->unkF0[0].unk24;
                    return;
                }
            }
            break;
        case 2:
            lbl_1_bss_5F8->unkF0[0].unk4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.4 + (0.5 * sin((3.141592653589793 * (f64) ((lbl_1_bss_5F8->unkF0[0].unk4 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_5F8->unkF0[0].unk4 == 0x28) {
                lbl_1_bss_5F8->unkF0[0].unk4 = 0;
                lbl_1_bss_5F8->unkF0[0].unkC += 1;
                return;
            }
            break;
        case 3:
            lbl_1_bss_5F8->unkF0[0].unk4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.8 + (0.2 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_5F8->unkF0[0].unk4 * 0xB4) / (s32) lbl_1_bss_5F8->unkF0[0].unk8)) / 180.0))));
            temp_r3[3].unk10.y = (f32) ((f64) lbl_1_bss_5F8->unkF0[0].unk20 + ((f64) lbl_1_bss_5F8->unkF0[0].unk24 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_5F8->unkF0[0].unk4 * 0x5A) / (s32) lbl_1_bss_5F8->unkF0[0].unk8)) / 180.0)));
            if ((s32) lbl_1_bss_5F8->unkF0[0].unk4 == (s32) lbl_1_bss_5F8->unkF0[0].unk8) {
                temp_r3[3].unk10.y = lbl_1_bss_5F8->unkF0[0].unk20 + lbl_1_bss_5F8->unkF0[0].unk24;
                lbl_1_bss_5F8->unkF0[0].unkC += 1;
                lbl_1_bss_5F8->unkF0[0].unk4 = 0;
                return;
            }
            break;
        case 4:
            lbl_1_bss_5F8->unkF0[0].unk4 += 1;
            Hu3DMotionSpeedSet(temp_r3[3].unk0, (f32) (0.8 - (0.4 * sin((3.141592653589793 * (f64) ((lbl_1_bss_5F8->unkF0[0].unk4 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_5F8->unkF0[0].unk4 == 0x28) {
                lbl_1_bss_5F8->unkF0[0].unk4 = (rand8() % 120) + 0xB4;
                lbl_1_bss_5F8->unkF0[0].unkC = 1;
            }
            break;
        }
    }
}

void fn_1_773C(void) {
    M548Model *temp_r3;
    M548Model *temp_r3_2;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_5F8->unk3C;
    temp_r3_2 = lbl_1_bss_5F8->unk3C;
    if ((s32) lbl_1_bss_5F8->unkF0[1].unk0 == 0) {
        temp_r3[1].unk10.y = 30.0f;
        temp_r3_2[2].unk10.y = 30.0f;
        temp_r0 = lbl_1_bss_5F8->unkF0[1].unkC;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 2) {
                lbl_1_bss_5F8->unkF0[1].unk4 = 0;
                lbl_1_bss_5F8->unkF0[1].unkC += 1;
                lbl_1_bss_5F8->unkF0[1].unk20 = 20.0f;
                lbl_1_bss_5F8->unkF0[1].unk24 = 5.0f;
                lbl_1_bss_5F8->unkF0[1].unk28 = -5.0f;
                return;
            }
            break;
        case 1:
            lbl_1_bss_5F8->unkF0[1].unk4 += 1;
            temp_r3[1].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_5F8->unkF0[1].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[1].unk4 * lbl_1_bss_5F8->unkF0[1].unk24)) / 180.0)));
            temp_r3_2[2].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_5F8->unkF0[1].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[1].unk4 * lbl_1_bss_5F8->unkF0[1].unk28)) / 180.0)));
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 4) {
                lbl_1_bss_5F8->unkF0[1].unkC += 1;
                lbl_1_bss_5F8->unkF0[1].unk8 = 0;
                return;
            }
            break;
        case 2:
            lbl_1_bss_5F8->unkF0[1].unk4 += 1;
            lbl_1_bss_5F8->unkF0[1].unk8 += 1;
            if ((s32) lbl_1_bss_5F8->unkF0[1].unk8 > 0x28) {
                lbl_1_bss_5F8->unkF0[1].unk8 = 0x28;
            }
            lbl_1_bss_5F8->unkF0[1].unk20 = (f32) (20.0 - (20.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_5F8->unkF0[1].unk8 * 0x5A) / 40)) / 180.0)));
            temp_r3[1].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_5F8->unkF0[1].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[1].unk4 * lbl_1_bss_5F8->unkF0[1].unk24)) / 180.0)));
            temp_r3_2[2].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_5F8->unkF0[1].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[1].unk4 * lbl_1_bss_5F8->unkF0[1].unk28)) / 180.0)));
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 1) {
                lbl_1_bss_5F8->unkF0[1].unkC = 0;
            }
            break;
        }
    }
}

void fn_1_7C88(void) {
    Mtx sp8;
    Mtx sp38;
    M548Model *temp_r30;
    M548Model *temp_r31;
    s32 temp_r3;

    temp_r31 = &lbl_1_bss_5F8->unk3C[4];
    temp_r30 = &lbl_1_bss_5F8->unk3C[5];
    if ((s32) lbl_1_bss_5F8->unkF0[2].unk0 == 0) {
        MTXIdentity(sp38);
        MTXRotRad(sp8, 0x79, -0.7853982f);
        MTXConcat(sp38, sp8, sp38);
        temp_r31->unk10.y = 30.0f;
        temp_r3 = lbl_1_bss_5F8->unkF0[2].unkC;
        switch (temp_r3) {                          /* irregular */
        case 0:
            temp_r30->unk10.y = -45.0f;
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 2) {
                lbl_1_bss_5F8->unkF0[2].unk20 = 10.0f;
                lbl_1_bss_5F8->unkF0[2].unk24 = 5.0f;
                lbl_1_bss_5F8->unkF0[2].unk4 = 0;
                lbl_1_bss_5F8->unkF0[2].unkC += 1;
            }
            break;
        case 1:
            lbl_1_bss_5F8->unkF0[2].unk4 += 1;
            lbl_1_bss_5F8->unkF0[2].unk24 = (f32) (5.0 + (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_5F8->unkF0[2].unk4 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 3) {
                lbl_1_bss_5F8->unkF0[2].unk24 = 10.0f;
                lbl_1_bss_5F8->unkF0[2].unkC += 1;
            }
            break;
        case 2:
            lbl_1_bss_5F8->unkF0[2].unk4 += 1;
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 4) {
                lbl_1_bss_5F8->unkF0[2].unkC += 1;
                lbl_1_bss_5F8->unkF0[2].unk8 = 0;
            }
            break;
        case 3:
            lbl_1_bss_5F8->unkF0[2].unk8 += 1;
            lbl_1_bss_5F8->unkF0[2].unk4 += 1;
            if ((s32) lbl_1_bss_5F8->unkF0[2].unk8 > 0x28) {
                lbl_1_bss_5F8->unkF0[2].unk8 = 0x28;
            }
            lbl_1_bss_5F8->unkF0[2].unk20 = (f32) (10.0 - (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_5F8->unkF0[2].unk8 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_5F8->unkF0[2].unk20 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_5F8->unkF0[2].unk4 * lbl_1_bss_5F8->unkF0[2].unk24)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
loop_17:
            if (temp_r31->unk10.x >= 360.0f) {
                temp_r31->unk10.x -= 360.0f;
                goto loop_17;
            }
            if (((s32) lbl_1_bss_5F8->unkF0[0].unkC == 1) && ((temp_r31->unk10.x >= 359.0f) || (temp_r31->unk10.x <= 1.0f))) {
                lbl_1_bss_5F8->unkF0[2].unk20 = 0.0f;
                temp_r31->unk10.x = 0.0f;
                temp_r30->unk10.x = 0.0f;
                temp_r30->unk10.y = -45.0f;
                temp_r30->unk10.z = 0.0f;
                lbl_1_bss_5F8->unkF0[2].unkC = 0;
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

void fn_1_856C(void) {
    M548Model *temp_r30;
    M548Model *temp_r31;
    s32 temp_r4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u8 temp_r3;
    u8 temp_r3_3;

    temp_r31 = &lbl_1_bss_5F8->unk3C[6];
    temp_r30 = &lbl_1_bss_5F8->unk3C[8];
    temp_r4 = lbl_1_bss_5F8->unkF0[3].unkC;
    if ((u32) temp_r4 <= 7U) {
        switch (temp_r4) {
        case 0:
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 2) {
                lbl_1_bss_5F8->unkF0[3].unk4 = 0;
                if (lbl_1_bss_5F8->unkF0[3].unk20 == 0.0f) {
                    lbl_1_bss_5F8->unkF0[3].unkC += 1;
                    lbl_1_bss_5F8->unkF0[3].unk4 = 0;
                    lbl_1_bss_5F8->unkF0[3].unk20 = 15.0f;
                    temp_r3 = rand8();
                    temp_r4_2 = temp_r3 >> 0x1FU;
                    temp_r3_2 = (temp_r3 << 0x1C) - temp_r4_2;
                    lbl_1_bss_5F8->unkF0[3].unk28 = (f32) ((((temp_r3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                } else {
                    lbl_1_bss_5F8->unkF0[3].unkC = 4;
                    lbl_1_bss_5F8->unkF0[3].unk20 = 10.0f;
                    temp_r3_3 = rand8();
                    temp_r4_3 = temp_r3_3 >> 0x1FU;
                    temp_r3_4 = (temp_r3_3 << 0x1C) - temp_r4_3;
                    lbl_1_bss_5F8->unkF0[3].unk28 = (f32) ((((temp_r3_3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                }
                lbl_1_bss_5F8->unkF0[3].unk24 = (250.0f * lbl_1_bss_5F8->unkF0[3].unk20) / 360.0f;
            }
            break;
        case 1:
            temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
            temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
            if (temp_r31->unk4.x >= lbl_1_bss_5F8->unkF0[3].unk28) {
                lbl_1_bss_5F8->unkF0[3].unkC += 1;
            }
            break;
        case 2:
            lbl_1_bss_5F8->unkF0[3].unk4 += 1;
            lbl_1_bss_5F8->unkF0[3].unk20 = (f32) (7.5 + (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_5F8->unkF0[3].unk4) / 180.0)));
            lbl_1_bss_5F8->unkF0[3].unk24 = (250.0f * lbl_1_bss_5F8->unkF0[3].unk20) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
            temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0x5A) {
                lbl_1_bss_5F8->unkF0[3].unkC += 1;
            }
            break;
        case 3:
            lbl_1_bss_5F8->unkF0[3].unk4 += 1;
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0xB4) {
                lbl_1_bss_5F8->unkF0[3].unk4 = 0xB4;
            }
            lbl_1_bss_5F8->unkF0[3].unk20 = (f32) (7.5 - (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_5F8->unkF0[3].unk4) / 180.0)));
            lbl_1_bss_5F8->unkF0[3].unk24 = (250.0f * lbl_1_bss_5F8->unkF0[3].unk20) / 360.0f;
            if (temp_r31->unk4.x < 1000.0f) {
                temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
                temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
            } else if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 1) {
                lbl_1_bss_5F8->unkF0[3].unkC = 0;
            }
            break;
        case 4:
            lbl_1_bss_5F8->unkF0[3].unk4 += 1;
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0x14) {
                temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
                temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
                if (temp_r31->unk4.x >= lbl_1_bss_5F8->unkF0[3].unk28) {
                    lbl_1_bss_5F8->unkF0[3].unkC += 1;
                    lbl_1_bss_5F8->unkF0[3].unk4 = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_5F8->unkF0[3].unk4 += 1;
            lbl_1_bss_5F8->unkF0[3].unk20 = (f32) (10.0 * cos((3.141592653589793 * (f64) lbl_1_bss_5F8->unkF0[3].unk4) / 180.0));
            lbl_1_bss_5F8->unkF0[3].unk24 = (250.0f * lbl_1_bss_5F8->unkF0[3].unk20) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
            temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 == 0x5A) {
                lbl_1_bss_5F8->unkF0[3].unkC += 1;
                lbl_1_bss_5F8->unkF0[3].unk4 = 0;
            }
            break;
        case 6:
            if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 2) {
                lbl_1_bss_5F8->unkF0[3].unkC += 1;
            }
            break;
        case 7:
            lbl_1_bss_5F8->unkF0[3].unk4 += 1;
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0x96) {
                lbl_1_bss_5F8->unkF0[3].unk4 = 0x96;
            }
            if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0x3C) {
                lbl_1_bss_5F8->unkF0[3].unk20 = (f32) (10.0 * sin((3.141592653589793 * (f64) (lbl_1_bss_5F8->unkF0[3].unk4 - 0x3C)) / 180.0));
                lbl_1_bss_5F8->unkF0[3].unk24 = (250.0f * lbl_1_bss_5F8->unkF0[3].unk20) / 360.0f;
                if (temp_r31->unk4.x < 1000.0f) {
                    if ((s32) lbl_1_bss_5F8->unkF0[3].unk4 >= 0x46) {
                        temp_r31->unk10.z -= lbl_1_bss_5F8->unkF0[3].unk20;
                    }
                    temp_r31->unk4.x += lbl_1_bss_5F8->unkF0[3].unk24;
                } else if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 1) {
                    lbl_1_bss_5F8->unkF0[3].unkC = 0;
                    lbl_1_bss_5F8->unkF0[3].unk20 = 0.0f;
                }
            }
            break;
        }
    }
    temp_r30->unk4.x = temp_r31->unk4.x;
    temp_r30->unk4.y = temp_r31->unk4.y - 40.0f;
    temp_r30->unk4.z = temp_r31->unk4.z;
}

void fn_1_8F78(void) {
    M548Model *temp_r3;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_5F8->unk3C;
    temp_r0 = lbl_1_bss_5F8->unkF0[4].unkC;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 2) {
            lbl_1_bss_5F8->unkF0[4].unkC += 1;
            lbl_1_bss_5F8->unkF0[4].unk4 = 0;
            Hu3DMotionSpeedSet(temp_r3[7].unk0, 0.5f);
            Hu3DMotionTimeSet(temp_r3[7].unk0, 0.0f);
            return;
        }
        return;
    case 1:
        lbl_1_bss_5F8->unkF0[4].unk4 += 1;
        temp_r3[7].unk4.x = (f32) (((lbl_1_bss_5F8->unkF0[4].unk4 * 0xFA0) / 200) - 0x7D0);
        if ((s32) lbl_1_bss_5F8->unkF0[4].unk4 == 0xC8) {
            lbl_1_bss_5F8->unkF0[4].unkC += 1;
            return;
        }
        break;
    case 2:
        if ((s32) lbl_1_bss_5F8->unkF0[0].unkC == 1) {
            lbl_1_bss_5F8->unkF0[4].unkC = 0;
        }
        break;
    }
}
