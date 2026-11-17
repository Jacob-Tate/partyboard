// MP5 m542 (Countdown Pound), generated from its m2c draft by tools/mp5/ports/m542dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m542dll (tools/mp5/decomp.py m542dll --types tools/mp5/types/m542dll.h)
// Written from the draft: Countdown Pound (1 vs 1 duel). Runs on MP5's MgSeq sequencer; the camera uses
// MP5's omCameraView* helpers (mp5compat.h). lbl_1_bss_1B38 points at the work struct lbl_1_bss_1954.

typedef struct M542Model { // model table entry, 0x1C (0x22 of them in lbl_1_bss_1588)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M542Model;

typedef struct M542Player { // 0x1C
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
} M542Player;

typedef struct M542Char { // per MP5 character, 0x24
    u32 unk0[9]; // MP5 motion data numbers
} M542Char;

typedef struct M542Anim { // per player character animation request, 0x24 (fn_1_92A4 applies it)
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
} M542Anim;

typedef struct M542Stomp { // per player jump state, 0x10
    s32 unk0; // state
    s32 unk4; // frames in state
    char pad8[8];
} M542Stomp;

typedef struct M542Work { // lbl_1_bss_1954, 0x154
    HUPROCESS *unk0; // object manager
    M542Player unk4[2];
    M542Model *unk3C; // model table (lbl_1_bss_1588)
    M542Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_54)
    M542Anim unk50[2];
    s32 *unk98; // data numbers (lbl_1_data_0)
    s32 unk9C;
    s32 unkA0; // mode
    s32 unkA4; // mode step
    s32 unkA8[2]; // player is done
    s32 unkB0; // end step
    s32 unkB4[2]; // frame counter per player
    char padBC[4];
    s32 unkC0; // timer
    M542Stomp unkC4[2];
    s32 unkE4[2]; // com cloud pause
    s32 unkEC[2];
    f32 unkF4[2]; // cloud time
    s32 unkFC[4]; // wobble phases
    char pad10C[0x1C];
    Vec unk128[2]; // x: jump speed
    char pad140[0x14];
} M542Work;

typedef struct M542Com { // lbl_1_bss_14, 0x1C
    s16 unk0;
    char pad2[2];
    s32 unk4; // state
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
} M542Com;

typedef struct M542Spark { // lbl_1_bss_E8 entry, 0x2C
    s32 unk0; // active
    s32 unk4; // age
    char pad8[4];
    f32 unkC; // angle
    s16 unk10; // model
    char pad12[2];
    Vec unk14; // pos
    Vec unk20; // rot
} M542Spark;

typedef struct M542Fx { // lbl_1_bss_1AA8, 0x20
    s32 unk0; // active
    s32 unk4; // state
    s32 unk8; // next spark
    s32 unkC; // frames
    f32 unk10; // direction
    Vec unk14; // pos
} M542Fx;

typedef struct M542Pair {
    f32 unk0;
    f32 unk4;
} M542Pair;


void fn_1_84D0(M542Work *work, M542Model *models, s32 *dataNums);
void fn_1_871C(s16 arg);
void fn_1_89DC(M542Char *chr0, M542Char *chr1);
void fn_1_8A00(s16 *mot0, s16 *mot1);
void fn_1_249C(s8 *alpha);
void fn_1_328C(void);
void fn_1_3178(void);
void fn_1_39E0(void);
void fn_1_4008(s32 arg0);
void fn_1_4D48(s32 arg0);
void fn_1_7778(s32 arg0);
void fn_1_771C(s32 arg0);
void fn_1_77EC(void);
void fn_1_7848(s32 arg0);
void fn_1_7E90(s32 arg0);
s32 fn_1_800C(s32 arg0);
void fn_1_8180(s32 arg0);
s32 fn_1_835C(s32 arg0);
void fn_1_2858(void);
void fn_1_2978(void);
void fn_1_2A14(void);
void fn_1_2AD0(void);
void fn_1_2BDC(void);
void fn_1_2DAC(void);
void fn_1_2F90(void);
void fn_1_3178(void);
void fn_1_328C(void);
void fn_1_39E0(void);
void fn_1_4008(s32 arg0);
void fn_1_4994(void);
void fn_1_4D48(s32 arg0);
void fn_1_5120(void);
void fn_1_5420(void);
void fn_1_5D30(void);
void fn_1_6A30(void);
void fn_1_737C(void);
void fn_1_771C(s32 arg0);
void fn_1_7778(s32 arg0);
void fn_1_77EC(void);
void fn_1_7848(s32 arg0);
void fn_1_7E90(s32 arg0);
s32 fn_1_800C(s32 arg0);
void fn_1_8180(s32 arg0);
s32 fn_1_835C(s32 arg0);
void ObjectSetup(void);
void fn_1_248(s16 arg0, s16 frameNo);
void fn_1_7A0(s16 mode, s16 frameNo);
void fn_1_7E4(s16 arg0, s16 frameNo);
void fn_1_838(s16 mode, s16 frameNo);
void fn_1_9F0(s16 arg0, s16 frameNo);
void fn_1_B70(s16 mode, s16 frameNo);
void fn_1_CC4(s16 mode, s16 frameNo);
void fn_1_CE8(s16 mode, s16 frameNo);
void fn_1_D1C(s16 mode, s16 frameNo);
void fn_1_D3C(omObjData *obj);
void fn_1_FC8(void);
void fn_1_249C(s8 *alpha);
void fn_1_24F8(void);
void fn_1_2524(HU3DMODEL *modelP, Mtx mtx);
void fn_1_84D0(M542Work *work, M542Model *models, s32 *dataNums);
void fn_1_871C(s16 arg);
void fn_1_89DC(M542Char *chr0, M542Char *chr1);
void fn_1_8A00(s16 *mot0, s16 *mot1);
void fn_1_8A24(void);
void fn_1_8C94(omObjData *obj);
void fn_1_9150(void);
void fn_1_92A4(omObjData *obj);
void fn_1_94B4(omObjData *obj);

s32 lbl_1_data_330 = -1;
s32 lbl_1_data_334[2] = { -1, -1 };
M542Pair lbl_1_data_33C[0xE] = {
    { 0.0f, 0.0f },
    { 0.0f, 0.25f },
    { 0.0f, 0.5f },
    { 0.0f, 0.75f },
    { 0.25f, 0.0f },
    { 0.25f, 0.25f },
    { 0.25f, 0.5f },
    { 0.25f, 0.75f },
    { 0.5f, 0.0f },
    { 0.5f, 0.25f },
    { 0.5f, 0.5f },
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.75f, 0.75f },
};
Vec lbl_1_data_3B0[6] = {
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
};
M542Spark lbl_1_bss_E8[4][0x1E];
M542Model lbl_1_bss_1588[0x22];
s16 lbl_1_bss_1940[2][5];
M542Work lbl_1_bss_1954;
M542Fx lbl_1_bss_1AA8[4];
s16 lbl_1_bss_1B28;
s32 lbl_1_data_0[0x20] = {
    DATA_MAKE_NUM(DATADIR_MP5_M542, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M542, 31),
};
M542Char lbl_1_data_80[0xD] = {
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 121),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 47),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 43),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 121),
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 121 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 121 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 47 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 121 */,
        },
    },
};
MGSEQ_PARAM lbl_1_data_254 = {
    0,
    0,
    fn_1_248,
    fn_1_7A0,
    fn_1_7E4,
    fn_1_838,
    fn_1_9F0,
    fn_1_B70,
    fn_1_CC4,
    fn_1_CE8,
    fn_1_D1C,
};
void (*lbl_1_data_27C[4])() = { fn_1_2858, fn_1_2978, fn_1_2A14, fn_1_2AD0 };
void (*lbl_1_data_28C[3])() = { fn_1_2BDC, fn_1_2DAC, fn_1_2F90 };
s32 lbl_1_data_298 = -1;
void (*lbl_1_data_29C[3])() = { fn_1_5420, fn_1_5D30, fn_1_6A30 };
M542Pair lbl_1_data_2A8[0xD] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.5f, 0.0f },
    { 0.75f, 0.0f },
    { 0.0f, 0.25f },
    { 0.25f, 0.25f },
    { 0.5f, 0.25f },
    { 0.75f, 0.25f },
    { 0.0f, 0.25f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
};
static s8 lbl_1_data_31C[0x14] = {
    0x54,
    0x4C,
    0x33,
    0x32,
    0x6D,
    0x35,
    0x34,
    0x32,
    0x62,
    0x75,
    0x72,
    0x73,
    0x74,
    0x30,
    0x31,
    0,
    0,
    0,
    0,
    0,
};
s16 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s32 lbl_1_bss_C;
s8 lbl_1_bss_10;
M542Com lbl_1_bss_14[2];
s16 lbl_1_bss_54[2][9];
OMCAMERAVIEW lbl_1_bss_78[4];
M542Work *lbl_1_bss_1B38;
s32 lbl_1_rodata_11C[4] = { 0x1B6, 0x1F8, 0x210, 0x21C }; /* const */

void fn_1_2858(void) {
    if (WipeCheckEnd() == 0) {
        fn_1_3178();
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[7].unk0, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[8].unk0, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[9].unk0, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[0xA].unk0, 2.0f);
        HuAudFXPlay(0x815);
        HuAudFXPlay(0x816);
        lbl_1_data_330 = HuAudBGMPlay(0x3E);
        lbl_1_bss_1954.unkA0 += 1;
        lbl_1_bss_1954.unkA4 = 0;
        CharModelVoicePanSet(lbl_1_bss_1954.unk4[0].unk2, 0x30);
        CharModelVoicePanSet(lbl_1_bss_1954.unk4[1].unk2, 0x50);
    }
}

void fn_1_2978(void) {
    s32 temp_r3;

    temp_r3 = lbl_1_bss_1954.unkA4;
    lbl_1_bss_1954.unkA4 = temp_r3 + 1;
    if (temp_r3 >= 0x2D) {
        lbl_1_bss_1954.unkA0 += 1;
        lbl_1_bss_1954.unkA4 = 0;
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[0xF].unk0, 1.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[0x10].unk0, 1.0f);
    }
}

void fn_1_2A14(void) {
    lbl_1_bss_1954.unkA4 += 1;
    if ((s32) lbl_1_bss_1954.unkA4 >= 0xA) {
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[0xF].unk0, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[0x10].unk0, 0.0f);
    }
    if ((s32) lbl_1_bss_1954.unkA4 >= 0x14) {
        omCameraViewMoveSimple(lbl_1_bss_78, 0x3C);
        lbl_1_bss_1954.unkA0 += 1;
    }
}

void fn_1_2AD0(void) {
    s32 temp_r31;
    s32 temp_r31_2;

    if (omCameraViewCheck(1U) != 0) {
        lbl_1_bss_1954.unkA0 = 0;
        MgSeqModeNext();
        fn_1_3178();
        temp_r31 = (rand8() % 3) * 0x1E;
        lbl_1_bss_1954.unkE4[0] = temp_r31 + (rand8() % 60) + 0x3C;
        temp_r31_2 = (rand8() % 3) * 0x1E;
        lbl_1_bss_1954.unkE4[1] = temp_r31_2 + (rand8() % 60) + 0x3C;
    }
}

void fn_1_2BDC(void) {
    s32 var_r31;
    u32 temp_r4;
    u32 temp_r4_2;
    u8 temp_r3;
    u8 temp_r3_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 7].unk0, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31 + 7].unk0, 2.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 9].unk0, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31 + 9].unk0, 2.0f);
        lbl_1_bss_1954.unkEC[var_r31] = 0;
        lbl_1_bss_1954.unkF4[var_r31] = 10.0f;
        temp_r3 = rand8();
        temp_r4 = temp_r3 >> 0x1FU;
        lbl_1_bss_1954.unkFC[var_r31 * 2] = (s32) ((((temp_r3 & 1) ^ temp_r4) - temp_r4) * 0xB4);
        temp_r3_2 = rand8();
        temp_r4_2 = temp_r3_2 >> 0x1FU;
        lbl_1_bss_1954.unkFC[var_r31 * 2 + 1] = (s32) ((((temp_r3_2 & 1) ^ temp_r4_2) - temp_r4_2) * 0xB4);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(var_r31 * 5) + 0x15].unk0, 1.0f);
        fn_1_771C(-1);
        var_r31 += 1;
        goto loop_2;
    }
    HuAudFXPlay(0x815);
    HuAudFXPlay(0x816);
    lbl_1_bss_1954.unkA0 += 1;
    lbl_1_bss_4 = 1;
}

void fn_1_2DAC(void) {
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 var_r31;
    u32 temp_r4;
    u8 temp_r3_2;

    var_r31 = 0;
loop_11:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_1954.unk4[var_r31].unk4 != 0) {
            fn_1_4D48(var_r31);
        }
        fn_1_4008(var_r31);
        if ((s32) lbl_1_bss_1954.unkA8[var_r31] == 0) {
            temp_r3 = lbl_1_bss_1954.unkE4[var_r31];
            lbl_1_bss_1954.unkE4[var_r31] = temp_r3 - 1;
            if (temp_r3 <= 0) {
                temp_r3_2 = rand8();
                temp_r4 = temp_r3_2 >> 0x1FU;
                temp_r30 = ((temp_r3_2 & 1) ^ temp_r4) - temp_r4;
                fn_1_7778(temp_r30 + (var_r31 * 2));
                if ((s32) (rand8() % 3) != 0) {
                    fn_1_7778((temp_r30 ^ 1) + (var_r31 * 2));
                }
                lbl_1_bss_1954.unkE4[var_r31] = ((rand8() % 3) * 0xF) + 0x42;
                if (var_r31 == 0) {
                    HuAudFXPlay(0x813);
                } else {
                    HuAudFXPlay(0x814);
                }
            }
        }
        var_r31 += 1;
        goto loop_11;
    }
    if (((s32) lbl_1_bss_1954.unkA8[0] != 0) && ((s32) lbl_1_bss_1954.unkA8[1] != 0)) {
        temp_r3_3 = lbl_1_bss_1954.unkA0;
        lbl_1_bss_1954.unkA0 = temp_r3_3 + 1;
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_330, 0x3E8);
        lbl_1_bss_4 = 0;
    }
    fn_1_39E0();
    lbl_1_bss_C += 1;
}

void fn_1_2F90(void) {
    lbl_1_bss_1954.unkA0 = 0;
    MgSeqModeNext();
    HuAudSStreamFadeOut(lbl_1_data_330, 0x64);
    fn_1_39E0();
}


void fn_1_3178(void) {
    s32 sp8[4];
    s32 var_r30;
    s32 var_r31;

    var_r30 = 0;
loop_5:
    if (var_r30 < 2) {
        sp8[0] = 1;
        sp8[1] = 0;
        sp8[2] = 0;
        sp8[3] = 0;
        var_r31 = 0;
loop_3:
        if (var_r31 < 4) {
            Hu3DTexScrollPosSet(lbl_1_bss_1940[var_r30][var_r31], lbl_1_data_33C[sp8[var_r31]].unk0, lbl_1_data_33C[sp8[var_r31]].unk4, 0.0f);
            var_r31 += 1;
            goto loop_3;
        }
        lbl_1_bss_1954.unkA8[var_r30] = 0;
        lbl_1_bss_1954.unkB4[var_r30] = 0;
        var_r30 += 1;
        goto loop_5;
    }
}

void fn_1_328C(void) {
    s32 sp8[4];
    s32 sp28[4];
    u32 sp18[4];
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;
    u32 temp_r0;

    var_r31 = 0;
loop_8:
    if (var_r31 < 2) {
        if ((s32) lbl_1_bss_1954.unkA8[var_r31] == 0) {
            lbl_1_bss_1954.unkB4[var_r31] += 1;
            if ((s32) lbl_1_bss_1954.unkB4[var_r31] > 0x258) {
                lbl_1_bss_1954.unkB4[var_r31] = 0x259;
                lbl_1_bss_1954.unkA8[var_r31] = 1;
                if (var_r31 == 0) {
                    HuAudFXPlay(0x80E);
                } else {
                    HuAudFXPlay(0x80F);
                }
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(var_r31 * 5) + 0x15].unk0, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[(var_r31 * 5) + 0x15].unk0, 30.0f);
            }
        }
        var_r31 += 1;
        goto loop_8;
    }
    var_r31_2 = 0;
loop_32:
    if (var_r31_2 < 2) {
        if ((s32) lbl_1_bss_1954.unkB4[var_r31_2] == 0x258) {
            sp28[0] = 0;
            sp28[1] = 0;
            sp28[2] = 0;
            sp28[3] = 1;
            var_r30 = 0;
loop_13:
            if (var_r30 < 4) {
                Hu3DTexScrollPosSet(lbl_1_bss_1940[var_r31_2][var_r30], lbl_1_data_33C[sp28[var_r30]].unk0, lbl_1_data_33C[sp28[var_r30]].unk4, 0.0f);
                var_r30 += 1;
                goto loop_13;
            }
        } else if ((s32) lbl_1_bss_1954.unkB4[var_r31_2] < 0x258) {
            temp_r0 = (lbl_1_bss_1954.unkB4[var_r31_2] * 0x3E8) / 600;
            if ((s32) (0x3E8 - temp_r0) != 0x270F) {
                sp18[0] = (0x3E8 - temp_r0) / 1000;
                sp18[1] = ((0x3E8 - temp_r0) % 1000) / 100;
                sp18[2] = ((0x3E8 - temp_r0) % 100) / 10;
                sp18[3] = (0x3E8 - temp_r0) % 10;
            } else {
                var_r29 = 0;
loop_20:
                if (var_r29 < 4) {
                    sp18[var_r29] = 0xA;
                    var_r29 += 1;
                    goto loop_20;
                }
            }
            var_r29_2 = 0;
loop_23:
            if (var_r29_2 < 4) {
                Hu3DTexScrollPosSet(lbl_1_bss_1940[var_r31_2][var_r29_2], lbl_1_data_33C[sp18[var_r29_2]].unk0, lbl_1_data_33C[sp18[var_r29_2]].unk4, 0.0f);
                var_r29_2 += 1;
                goto loop_23;
            }
        } else {
            var_r28 = 0;
loop_27:
            if (var_r28 < 4) {
                sp8[var_r28] = 0xA;
                var_r28 += 1;
                goto loop_27;
            }
            var_r28_2 = 0;
loop_30:
            if (var_r28_2 < 4) {
                Hu3DTexScrollPosSet(lbl_1_bss_1940[var_r31_2][var_r28_2], lbl_1_data_33C[sp8[var_r28_2]].unk0, lbl_1_data_33C[sp8[var_r28_2]].unk4, 0.0f);
                var_r28_2 += 1;
                goto loop_30;
            }
        }
        var_r31_2 += 1;
        goto loop_32;
    }
}



void fn_1_39E0(void) {
    M542Model *temp_r28;
    M542Model *temp_r29;
    s32 temp_r3;
    s32 var_r30;
    s32 var_r31;

    var_r30 = 0;
loop_5:
    if (var_r30 < 2) {
        temp_r28 = &lbl_1_bss_1954.unk3C[var_r30 + 0x20];
        temp_r29 = &lbl_1_bss_1954.unk3C[var_r30 + 0xB];
        if (temp_r28->unk4.y >= 170.0f) {
            temp_r29->unk4.y = 0.0f;
        } else {
            temp_r29->unk4.y = temp_r28->unk4.y - 170.0f;
        }
        var_r30 += 1;
        goto loop_5;
    }
    fn_1_328C();
    lbl_1_bss_1954.unkFC[0] = (lbl_1_bss_1954.unkFC[0] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[1] = (lbl_1_bss_1954.unkFC[1] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[2] = (lbl_1_bss_1954.unkFC[2] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    lbl_1_bss_1954.unkFC[3] = (lbl_1_bss_1954.unkFC[3] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    fn_1_77EC();
    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        temp_r3 = lbl_1_bss_1954.unkEC[var_r31];
        lbl_1_bss_1954.unkEC[var_r31] = temp_r3 + 1;
        if (temp_r3 >= 0x32) {
            lbl_1_bss_1954.unkEC[var_r31] = 0;
            if ((s32) lbl_1_bss_1954.unkA8[var_r31] == 0) {
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 7].unk0, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 9].unk0, 0.0f);
                if (var_r31 == 0) {
                    HuAudFXPlay(0x815);
                } else {
                    HuAudFXPlay(0x816);
                }
            }
        }
        if ((s32) ((lbl_1_bss_1954.unkA8[var_r31] == 0) | (lbl_1_bss_1954.unkB4[var_r31] > 0x258)) != 0) {
            lbl_1_bss_1954.unkF4[var_r31] = (f32) ((f64) lbl_1_bss_1954.unkF4[var_r31] + 0.1);
            if (lbl_1_bss_1954.unkF4[var_r31] > 85.0f) {
                lbl_1_bss_1954.unkF4[var_r31] = 85.0f;
            }
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 0xF].unk0, lbl_1_bss_1954.unkF4[var_r31]);
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_4008(s32 arg0) {
    M542Model *temp_r30;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r6;

    temp_r30 = &lbl_1_bss_1954.unk3C[arg0 + 0x20];
    temp_r0 = lbl_1_bss_1954.unkC4[arg0].unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (((s32) lbl_1_bss_1954.unkA8[arg0] == 0) && ((s32) (lbl_1_bss_1954.unk4[arg0].unkC & 0x100) != 0)) {
            lbl_1_bss_1954.unkC4[arg0].unk0 = 1;
            lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x1], 0.0f, 2.0f, 0U);
            lbl_1_bss_1954.unk128[arg0].x = 25.0f;
            return;
        }
        return;
    case 1:
        lbl_1_bss_1954.unkC4[arg0].unk4 += 1;
        temp_r30->unk4.y += lbl_1_bss_1954.unk128[arg0].x;
        lbl_1_bss_1954.unk128[arg0].x = (f32) ((f64) lbl_1_bss_1954.unk128[arg0].x * 0.85);
        if (lbl_1_bss_1954.unk128[arg0].x < 1.0f) {
            lbl_1_bss_1954.unk128[arg0].x = 1.0f;
        }
        if (((s32) (lbl_1_bss_1954.unk4[arg0].unk8 & 0x100) == 0) && ((s32) lbl_1_bss_1954.unkC4[arg0].unk4 > 4)) {
            lbl_1_bss_1954.unkC4[arg0].unk0 = 2;
            lbl_1_bss_1954.unk128[arg0].x *= 0.5f;
        }
        if ((s32) lbl_1_bss_1954.unkC4[arg0].unk4 > 0x10) {
            lbl_1_bss_1954.unkC4[arg0].unk0 = 2;
            lbl_1_bss_1954.unk128[arg0].x *= 0.5f;
        }
        if (((s32) lbl_1_bss_1954.unkC4[arg0].unk4 > 3) && ((s32) lbl_1_bss_1954.unkA8[arg0] == 0) && (((s32) (lbl_1_bss_1954.unk4[arg0].unkC & 0x100) != 0) || ((s32) (lbl_1_bss_1954.unk4[arg0].unkC & 0x40) != 0))) {
            lbl_1_bss_1954.unkC4[arg0].unk0 = 3;
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x3], 0.0f, 8.0f, 0U);
            lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
            lbl_1_bss_1954.unk128[arg0].x *= 0.5f;
            return;
        }
        break;
    case 2:
        temp_r30->unk4.y -= lbl_1_bss_1954.unk128[arg0].x;
        lbl_1_bss_1954.unk128[arg0].x *= 1.1764705f;
        if (lbl_1_bss_1954.unk128[arg0].x > 30.0f) {
            lbl_1_bss_1954.unk128[arg0].x = 30.0f;
        }
        if (temp_r30->unk4.y <= 170.0f) {
            temp_r30->unk4.y = 170.0f;
            lbl_1_bss_1954.unkC4[arg0].unk0 = 0;
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x0], 0.0f, 5.0f, 0U);
            lbl_1_bss_1954.unk128[arg0].x = 25.0f;
            lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
            CharModelLandDustCreate(lbl_1_bss_1954.unk4[arg0].unk2, &temp_r30->unk4);
            return;
        }
        if (((s32) lbl_1_bss_1954.unkA8[arg0] == 0) && (((s32) (lbl_1_bss_1954.unk4[arg0].unkC & 0x100) != 0) || ((s32) (lbl_1_bss_1954.unk4[arg0].unkC & 0x40) != 0))) {
            lbl_1_bss_1954.unkC4[arg0].unk0 = 3;
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x3], 0.0f, 8.0f, 0U);
            lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
            lbl_1_bss_1954.unk128[arg0].x *= 0.5f;
            return;
        }
        break;
    case 3:
        temp_r4 = lbl_1_bss_1954.unkC4[arg0].unk4;
        lbl_1_bss_1954.unkC4[arg0].unk4 = temp_r4 + 1;
        if (temp_r4 > 0xF) {
            temp_r30->unk4.y -= lbl_1_bss_1954.unk128[arg0].x;
            lbl_1_bss_1954.unk128[arg0].x *= 1.1764705f;
            if (lbl_1_bss_1954.unk128[arg0].x > 45.0f) {
                lbl_1_bss_1954.unk128[arg0].x = 45.0f;
            }
            if (temp_r30->unk4.y <= 150.0f) {
                temp_r30->unk4.y = 150.0f;
                if ((s32) lbl_1_bss_1954.unkA8[arg0] == 0) {
                    if (arg0 == 0) {
                        HuAudFXPlay(0x80C);
                    } else {
                        HuAudFXPlay(0x80D);
                    }
                }
                Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x5], 0.0f, 4.0f, 0U);
                lbl_1_bss_1954.unkA8[arg0] = 1;
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(arg0 * 5) + 0x15].unk0, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[(arg0 * 5) + 0x15].unk0, 30.0f);
                lbl_1_bss_1954.unkC4[arg0].unk0 = 4;
                lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
                omVibrate(lbl_1_bss_1954.unk4[arg0].unk0, 0x14, 4, 2);
                return;
            }
        }
        break;
    case 4:
        temp_r3 = lbl_1_bss_1954.unkC4[arg0].unk4;
        lbl_1_bss_1954.unkC4[arg0].unk4 = temp_r3 + 1;
        if (temp_r3 > 0xF) {
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x4], 0.0f, 4.0f, 0U);
            lbl_1_bss_1954.unkC4[arg0].unk0 = 5;
            lbl_1_bss_1954.unkC4[arg0].unk4 = 0;
        }
        /* fallthrough */
    case 5:
        temp_r6 = lbl_1_bss_1954.unkC4[arg0].unk4;
        lbl_1_bss_1954.unkC4[arg0].unk4 = temp_r6 + 1;
        if (temp_r6 > 0x1E) {
            Hu3DMotionShiftSet(temp_r30->unk0, lbl_1_bss_1954.unk48[arg0][0x0], 0.0f, 2.0f, 0x40000001U);
            lbl_1_bss_1954.unkC4[arg0].unk0 = 6;
        }
        break;
    }
}

void fn_1_4994(void) {
    s32 sp8[4];
    M542Com *temp_r3;
    M542Com *temp_r3_2;
    s32 var_r31;

    sp8[0] = lbl_1_rodata_11C[0];
    sp8[1] = lbl_1_rodata_11C[1];
    sp8[2] = lbl_1_rodata_11C[2];
    sp8[3] = lbl_1_rodata_11C[3];
    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        memset(&lbl_1_bss_14[var_r31], 0, 0x1C);
        lbl_1_bss_14[var_r31].unk0 = lbl_1_bss_1954.unk4[var_r31].unk4 - 1;
        lbl_1_bss_14[var_r31].unk14 = sp8[lbl_1_bss_14[var_r31].unk0];
        if ((s16) lbl_1_bss_14[var_r31].unk0 == 3) {
            temp_r3 = &lbl_1_bss_14[var_r31];
            temp_r3->unk14 -= rand8() % 3;
        } else {
            temp_r3_2 = &lbl_1_bss_14[var_r31];
            temp_r3_2->unk14 -= rand8() % 18;
        }
        lbl_1_bss_14[var_r31].unk18 = (rand8() % 120) + 0x78;
        var_r31 += 1;
        goto loop_5;
    }
}


void fn_1_4D48(s32 arg0) {
    M542Com *temp_r4;
    M542Com *temp_r4_2;
    M542Com *temp_r4_3;
    M542Com *temp_r4_4;
    M542Com *temp_r4_5;
    M542Com *temp_r4_6;
    s32 temp_r0;
    s32 var_r30;

    temp_r0 = lbl_1_bss_14[arg0].unk4;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r30 = 0;
        if ((s32) lbl_1_bss_1954.unkB4[arg0] >= (s32) lbl_1_bss_14[arg0].unk14) {
            lbl_1_bss_14[arg0].unkC = 0xF - (rand8() % 6);
            lbl_1_bss_14[arg0].unk10 = lbl_1_bss_14[arg0].unkC + (rand8() % 3) + 5;
            var_r30 = 1;
        } else if ((s32) lbl_1_bss_1954.unkB4[arg0] < (s32) (lbl_1_bss_14[arg0].unk14 - 0x2D)) {
            temp_r4 = &lbl_1_bss_14[arg0];
            temp_r4->unk18 -= 1;
            if ((s32) lbl_1_bss_14[arg0].unk18 <= 0) {
                lbl_1_bss_14[arg0].unkC = (rand8() % 6) + 0xA;
                lbl_1_bss_14[arg0].unk10 = 0;
                lbl_1_bss_14[arg0].unk18 = (rand8() % 60) + 0x3C;
                var_r30 = 1;
            }
        }
        if (var_r30 != 0) {
            lbl_1_bss_14[arg0].unk8 = 0;
            temp_r4_2 = &lbl_1_bss_14[arg0];
            temp_r4_2->unk4 += 1;
            lbl_1_bss_1954.unk4[arg0].unkC = 0x100;
            lbl_1_bss_1954.unk4[arg0].unk8 = 0x100;
            return;
        }
        return;
    case 1:
        lbl_1_bss_1954.unk4[arg0].unk8 = 0x100;
        temp_r4_3 = &lbl_1_bss_14[arg0];
        temp_r4_3->unk8 += 1;
        if ((s32) lbl_1_bss_14[arg0].unk8 >= (s32) lbl_1_bss_14[arg0].unkC) {
            if ((s32) lbl_1_bss_14[arg0].unk10 != 0) {
                temp_r4_4 = &lbl_1_bss_14[arg0];
                temp_r4_4->unk4 += 1;
                return;
            }
            lbl_1_bss_14[arg0].unk4 = 0;
            return;
        }
        break;
    case 2:
        temp_r4_5 = &lbl_1_bss_14[arg0];
        temp_r4_5->unk8 += 1;
        if ((s32) lbl_1_bss_14[arg0].unk8 == (s32) lbl_1_bss_14[arg0].unk10) {
            lbl_1_bss_1954.unk4[arg0].unkC = 0x100;
            temp_r4_6 = &lbl_1_bss_14[arg0];
            temp_r4_6->unk4 += 1;
        }
        break;
    }
}

void fn_1_5120(void) {
    M542Model *temp_r28;
    M542Model *temp_r29;
    s32 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_8:
    if (var_r31 < 2) {
        fn_1_4008(var_r31);
        lbl_1_bss_1954.unkFC[var_r31 * 2] = (s32) ((lbl_1_bss_1954.unkFC[var_r31 * 2] + (rand8() % 10) + 2) % 360);
        lbl_1_bss_1954.unk3C[var_r31 + 0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[var_r31 * 2]) / 180.0));
        lbl_1_bss_1954.unkFC[var_r31 * 2 + 1] = (s32) ((lbl_1_bss_1954.unkFC[var_r31 * 2 + 1] + (rand8() % 10) + 2) % 360);
        lbl_1_bss_1954.unk3C[var_r31 + 0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[var_r31 * 2]) / 180.0));
        var_r30 = 0;
loop_6:
        if (var_r30 < 2) {
            temp_r28 = &lbl_1_bss_1954.unk3C[var_r30 + 0x20];
            temp_r29 = &lbl_1_bss_1954.unk3C[var_r30 + 0xB];
            if (temp_r28->unk4.y >= 170.0f) {
                temp_r29->unk4.y = 0.0f;
            } else {
                temp_r29->unk4.y = temp_r28->unk4.y - 170.0f;
            }
            var_r30 += 1;
            goto loop_6;
        }
        var_r31 += 1;
        goto loop_8;
    }
    lbl_1_bss_1954.unkA0 = 0;
    fn_1_77EC();
}

void fn_1_5420(void) {
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
    var_r30 = 0;
loop_6:
    if (var_r31 < 2) {
        fn_1_4008(var_r31);
        if ((s32) lbl_1_bss_1954.unkC4[var_r31].unk0 == 0) {
            var_r30 += 1;
        }
        if ((s32) lbl_1_bss_1954.unkC4[var_r31].unk0 == 6) {
            var_r30 += 1;
        }
        var_r31 += 1;
        goto loop_6;
    }
    if (var_r30 == 2) {
        if ((s32) lbl_1_bss_1954.unkB4[0] == (s32) lbl_1_bss_1954.unkB4[1]) {
            lbl_1_bss_1954.unkA0 = 2;
            lbl_1_bss_1954.unkA4 = 0;
            if ((s32) lbl_1_bss_1954.unkB4[0] > 0x258) {
                lbl_1_bss_1954.unkA4 = 1;
            }
            var_r31_2 = 0;
loop_13:
            if (var_r31_2 < 2) {
                lbl_1_bss_1954.unkEC[var_r31_2] = 0;
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31_2 + 7].unk0, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31_2 + 7].unk0, 3.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31_2 + 9].unk0, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31_2 + 9].unk0, 3.0f);
                lbl_1_bss_1954.unkA8[var_r31_2] = 0;
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(var_r31_2 * 5) + 0x15].unk0, 2.0f);
                Hu3DMotionShiftSet(lbl_1_bss_1954.unk3C[var_r31_2 + 0x20].unk0, lbl_1_bss_1954.unk48[var_r31_2][0x8], 0.0f, 10.0f, 0U);
                var_r31_2 += 1;
                goto loop_13;
            }
            HuAudFXPlay(0x815);
            HuAudFXPlay(0x816);
            lbl_1_data_334[0] = HuAudFXPlay(0x817);
            lbl_1_data_334[1] = HuAudFXPlay(0x818);
            HuAudFXPlay(0x1D);
        } else {
            lbl_1_bss_1954.unkA0 = 1;
            if ((s32) lbl_1_bss_1954.unkB4[0] > (s32) lbl_1_bss_1954.unkB4[1]) {
                if ((s32) lbl_1_bss_1954.unkB4[0] > 0x258) {
                    lbl_1_bss_1954.unkA4 = 1;
                } else {
                    lbl_1_bss_1954.unkA4 = 0;
                }
            } else if ((s32) lbl_1_bss_1954.unkB4[1] > 0x258) {
                lbl_1_bss_1954.unkA4 = 0;
            } else {
                lbl_1_bss_1954.unkA4 = 1;
            }
            lbl_1_bss_1954.unkEC[lbl_1_bss_1954.unkA4 ^ 1] = 0;
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[(lbl_1_bss_1954.unkA4 ^ 1) + 7].unk0, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(lbl_1_bss_1954.unkA4 ^ 1) + 7].unk0, 3.0f);
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[(lbl_1_bss_1954.unkA4 ^ 1) + 9].unk0, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[(lbl_1_bss_1954.unkA4 ^ 1) + 9].unk0, 3.0f);
            if ((s32) lbl_1_bss_1954.unkA4 == 0) {
                HuAudFXPlay(0x816);
                lbl_1_data_334[1] = HuAudFXPlay(0x818);
            } else {
                HuAudFXPlay(0x815);
                lbl_1_data_334[0] = HuAudFXPlay(0x817);
            }
            HuAudFXPlay(0x1D);
            lbl_1_bss_1954.unkA8[(lbl_1_bss_1954.unkA4 ^ 1)] = 0;
            Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[((lbl_1_bss_1954.unkA4 ^ 1) * 5) + 0x15].unk0, 2.0f);
            Hu3DMotionShiftSet(lbl_1_bss_1954.unk3C[(lbl_1_bss_1954.unkA4 ^ 1) + 0x20].unk0, lbl_1_bss_1954.unk48[lbl_1_bss_1954.unkA4 ^ 1][0x8], 0.0f, 10.0f, 0U);
        }
        lbl_1_bss_1954.unkB0 = 0;
    }
    lbl_1_bss_1954.unkFC[0] = (lbl_1_bss_1954.unkFC[0] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[1] = (lbl_1_bss_1954.unkFC[1] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[2] = (lbl_1_bss_1954.unkFC[2] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    lbl_1_bss_1954.unkFC[3] = (lbl_1_bss_1954.unkFC[3] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
}

void fn_1_5D30(void) {
    s16 temp_r29;
    s32 temp_r0;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r5;

    temp_r31 = lbl_1_bss_1954.unkA4 ^ 1;
    temp_r5 = lbl_1_bss_1954.unkEC[temp_r31];
    lbl_1_bss_1954.unkEC[temp_r31] = temp_r5 + 1;
    if (temp_r5 >= 0x21) {
        lbl_1_bss_1954.unkEC[temp_r31] = 0;
        Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[temp_r31 + 7].unk0, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[temp_r31 + 9].unk0, 0.0f);
        if ((s32) lbl_1_bss_1954.unkB0 < 1) {
            if (temp_r31 == 0) {
                HuAudFXPlay(0x815);
            } else {
                HuAudFXPlay(0x816);
            }
        }
    }
    switch ((s32) lbl_1_bss_1954.unkB0) {           /* irregular */
    case 0:
        lbl_1_bss_1954.unkF4[temp_r31] = (f32) ((f64) lbl_1_bss_1954.unkF4[temp_r31] + 0.2);
        Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[temp_r31 + 0xF].unk0, lbl_1_bss_1954.unkF4[temp_r31]);
        if (lbl_1_bss_1954.unkF4[temp_r31] > 99.0f) {
            lbl_1_bss_1954.unkF4[temp_r31] = 99.0f;
            lbl_1_bss_1954.unkB0 += 1;
            Hu3DMotionShiftSet(lbl_1_bss_1954.unk3C[temp_r31 + 0x20].unk0, lbl_1_bss_1954.unk48[temp_r31][0x7], 0.0f, 4.0f, 0U);
            omVibrate(lbl_1_bss_1954.unk4[temp_r31].unk0, 0x50, 0xC, 0);
            Hu3DModelAttrSet(lbl_1_bss_1954.unk3C[temp_r31 + 0xF].unk0, 1U);
            Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[temp_r31 + 0x1B].unk0, 1U);
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[temp_r31 + 0x1B].unk0, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[temp_r31 + 0x1B].unk0, 4.0f);
            Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[temp_r31 + 0x1B].unk0, 0x40000001U);
            Hu3DModelAttrSet(lbl_1_bss_1954.unk3C[temp_r31 + 0xF].unk0, 1U);
            Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[temp_r31 + 0x1E].unk0, 1U);
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[temp_r31 + 0x1E].unk0, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[temp_r31 + 0x1E].unk0, 4.0f);
            HuAudFXPlay(0x1E);
            if (temp_r31 == 0) {
                HuAudFXStop(lbl_1_data_334[0]);
                HuAudFXPlay(0x810);
            } else {
                HuAudFXStop(lbl_1_data_334[1]);
                HuAudFXPlay(0x811);
            }
            fn_1_7778(temp_r31 + 4);
        }
        break;
    case 1:
        temp_r0 = temp_r31 + 0x20;
        lbl_1_bss_1954.unk3C[temp_r0].unk4.z += 30.0f;
        temp_r3 = temp_r31 + 0x20;
        lbl_1_bss_1954.unk3C[temp_r3].unk4.y = (f32) ((f64) lbl_1_bss_1954.unk3C[temp_r3].unk4.y + 6.0);
        temp_r3_2 = temp_r31 + 0x20;
        lbl_1_bss_1954.unk3C[temp_r3_2].unk4.x += (f32) (6 - (temp_r31 * 0xC));
        if (lbl_1_bss_1954.unk3C[temp_r31 + 0x20].unk4.z >= 2000.0f) {
            lbl_1_bss_1954.unkB0 += 1;
            lbl_1_bss_78->center.x = (f32) ((lbl_1_bss_1954.unkA4 * 0x1A4) - 0xD2);
            lbl_1_bss_78->center.z = 254.0f;
            lbl_1_bss_78->rot.x = -5.0f;
            lbl_1_bss_78->zoom = 600.0f;
            omCameraViewMoveSimple(lbl_1_bss_78, 0x3C);
        }
        break;
    case 2:
        if (omCameraViewCheck(1U) != 0) {
            CharModelVoicePanSet(lbl_1_bss_1954.unk4[0].unk2, 0x40);
            CharModelVoicePanSet(lbl_1_bss_1954.unk4[1].unk2, 0x40);
            lbl_1_bss_1B28 = MGSeqWinCreate(lbl_1_bss_1954.unk4[lbl_1_bss_1954.unkA4].unk2, -1, -1, -1);
            Hu3DMotionShiftSet(lbl_1_bss_1954.unk3C[lbl_1_bss_1954.unkA4 + 0x20].unk0, lbl_1_bss_1954.unk48[lbl_1_bss_1954.unkA4][0x6], 0.0f, 8.0f, 0U);
            temp_r29 = lbl_1_bss_1954.unk4[lbl_1_bss_1954.unkA4].unk0;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r29].coin_win = 0xA;
            }
            HuAudJinglePlay(0x79);
            lbl_1_bss_1954.unkB0 += 1;
            lbl_1_bss_1954.unkC0 = 0;
        }
        break;
    case 3:
        lbl_1_bss_1954.unkC0 += 1;
        if ((GameMesStatGet(lbl_1_bss_1B28) == 0) && ((s32) lbl_1_bss_1954.unkC0 >= 0xD2)) {
            GameMesKill(lbl_1_bss_1B28);
            MgSeqModeNext();
        }
        break;
    }
    lbl_1_bss_1954.unkFC[0] = (lbl_1_bss_1954.unkFC[0] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[1] = (lbl_1_bss_1954.unkFC[1] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[2] = (lbl_1_bss_1954.unkFC[2] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    lbl_1_bss_1954.unkFC[3] = (lbl_1_bss_1954.unkFC[3] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    temp_r30 = lbl_1_bss_1954.unkA4 ^ 1;
    lbl_1_bss_1954.unkFC[temp_r30 * 2] = (s32) ((lbl_1_bss_1954.unkFC[temp_r30 * 2] + (rand8() % 10) + 2) % 360);
    lbl_1_bss_1954.unk3C[temp_r30 + 0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[temp_r30 * 2]) / 180.0));
    lbl_1_bss_1954.unkFC[temp_r30 * 2 + 1] = (s32) ((lbl_1_bss_1954.unkFC[temp_r30 * 2 + 1] + (rand8() % 10) + 2) % 360);
    lbl_1_bss_1954.unk3C[temp_r30 + 0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[temp_r30 * 2]) / 180.0));
    fn_1_328C();
    fn_1_328C();
    fn_1_77EC();
}

void fn_1_6A30(void) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r4;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;

    var_r31 = 0;
loop_7:
    if (var_r31 < 2) {
        temp_r4 = lbl_1_bss_1954.unkEC[var_r31];
        lbl_1_bss_1954.unkEC[var_r31] = temp_r4 + 1;
        if (temp_r4 >= 0x21) {
            lbl_1_bss_1954.unkEC[var_r31] = 0;
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 7].unk0, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31 + 9].unk0, 0.0f);
            if ((s32) lbl_1_bss_1954.unkB0 < 1) {
                if (var_r31 == 0) {
                    HuAudFXPlay(0x815);
                } else {
                    HuAudFXPlay(0x816);
                }
            }
        }
        var_r31 += 1;
        goto loop_7;
    }
    switch ((s32) lbl_1_bss_1954.unkB0) {           /* irregular */
    case 0:
        var_r31_2 = 0;
        var_r30 = 0;
loop_19:
        if (var_r31_2 < 2) {
            lbl_1_bss_1954.unkF4[var_r31_2] = (f32) ((f64) lbl_1_bss_1954.unkF4[var_r31_2] + 0.2);
            if (lbl_1_bss_1954.unkF4[var_r31_2] > 99.0f) {
                lbl_1_bss_1954.unkF4[var_r31_2] = 99.0f;
                var_r30 += 1;
            }
            Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31_2 + 0xF].unk0, lbl_1_bss_1954.unkF4[var_r31_2]);
            var_r31_2 += 1;
            goto loop_19;
        }
        if (var_r30 == 2) {
            lbl_1_bss_1954.unkB0 += 1;
            var_r31_3 = 0;
loop_23:
            if (var_r31_3 < 2) {
                Hu3DMotionShiftSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0x20].unk0, lbl_1_bss_1954.unk48[var_r31_3][0x7], 0.0f, 8.0f, 0U);
                omVibrate(lbl_1_bss_1954.unk4[var_r31_3].unk0, 0x50, 0xC, 0);
                Hu3DModelAttrSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0xF].unk0, 1U);
                Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1B].unk0, 1U);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1B].unk0, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1B].unk0, 4.0f);
                Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1B].unk0, 0x40000001U);
                Hu3DModelAttrReset(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1E].unk0, 1U);
                Hu3DMotionTimeSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1E].unk0, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.unk3C[var_r31_3 + 0x1E].unk0, 4.0f);
                fn_1_7778(var_r31_3 + 4);
                var_r31_3 += 1;
                goto loop_23;
            }
            HuAudFXPlay(0x1E);
            HuAudFXStop(lbl_1_data_334[0]);
            HuAudFXStop(lbl_1_data_334[1]);
            HuAudFXPlay(0x810);
            HuAudFXPlay(0x811);
        }
        break;
    case 1:
        var_r31_4 = 0;
loop_27:
        if (var_r31_4 < 2) {
            temp_r0 = var_r31_4 + 0x20;
            lbl_1_bss_1954.unk3C[temp_r0].unk4.z += 30.0f;
            temp_r0_2 = var_r31_4 + 0x20;
            lbl_1_bss_1954.unk3C[temp_r0_2].unk4.y = (f32) ((f64) lbl_1_bss_1954.unk3C[temp_r0_2].unk4.y + 6.0);
            temp_r0_3 = var_r31_4 + 0x20;
            lbl_1_bss_1954.unk3C[temp_r0_3].unk4.x += (f32) (6 - (var_r31_4 * 0xC));
            var_r31_4 += 1;
            goto loop_27;
        }
        if (lbl_1_bss_1954.unk3C[0x20].unk4.z >= 2000.0f) {
            lbl_1_bss_1954.unkB0 += 1;
        }
        break;
    case 2:
        lbl_1_bss_1B28 = MGSeqDrawCreate();
        HuAudJinglePlay(0x7B);
        lbl_1_bss_1954.unkB0 += 1;
        lbl_1_bss_1954.unkC0 = 0;
        break;
    case 3:
        lbl_1_bss_1954.unkC0 += 1;
        if ((GameMesStatGet(lbl_1_bss_1B28) == 0) && ((s32) lbl_1_bss_1954.unkC0 >= 0xD2)) {
            GameMesKill(lbl_1_bss_1B28);
            MgSeqModeNext();
        }
        break;
    }
    var_r31_5 = 0;
loop_36:
    if (var_r31_5 < 2) {
        lbl_1_bss_1954.unkFC[0] = (lbl_1_bss_1954.unkFC[0] + (rand8() % 10) + 2) % 360;
        lbl_1_bss_1954.unk3C[0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
        lbl_1_bss_1954.unkFC[1] = (lbl_1_bss_1954.unkFC[1] + (rand8() % 10) + 2) % 360;
        lbl_1_bss_1954.unk3C[0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
        lbl_1_bss_1954.unkFC[2] = (lbl_1_bss_1954.unkFC[2] + (rand8() % 10) + 2) % 360;
        lbl_1_bss_1954.unk3C[0x10].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
        lbl_1_bss_1954.unkFC[3] = (lbl_1_bss_1954.unkFC[3] + (rand8() % 10) + 2) % 360;
        lbl_1_bss_1954.unk3C[0x10].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
        var_r31_5 += 1;
        goto loop_36;
    }
    fn_1_328C();
    fn_1_328C();
    fn_1_77EC();
}

void fn_1_737C(void) {
    fn_1_77EC();
    lbl_1_bss_1954.unkFC[0] = (lbl_1_bss_1954.unkFC[0] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[1] = (lbl_1_bss_1954.unkFC[1] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0xF].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[0]) / 180.0));
    lbl_1_bss_1954.unkFC[2] = (lbl_1_bss_1954.unkFC[2] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.x = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
    lbl_1_bss_1954.unkFC[3] = (lbl_1_bss_1954.unkFC[3] + (rand8() % 10) + 2) % 360;
    lbl_1_bss_1954.unk3C[0x10].unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) lbl_1_bss_1954.unkFC[2]) / 180.0));
}

void fn_1_771C(s32 arg0) {
    s32 var_r30;
    s32 var_r31;

    var_r31 = arg0;
    var_r30 = var_r31 + 1;
    if (var_r31 < 0) {
        var_r31 = 0;
        var_r30 = 4;
    }
loop_3:
    if (var_r31 < var_r30) {
        lbl_1_bss_1AA8[arg0].unk4 = 0;
        var_r31 += 1;
        goto loop_3;
    }
}

void fn_1_7778(s32 arg0) {
    if (arg0 < 4) {
        lbl_1_bss_1AA8[arg0].unk0 = 1;
        lbl_1_bss_1AA8[arg0].unk4 = 0;
        return;
    }
    lbl_1_bss_1AA8[arg0 - 4].unk0 = 1;
    lbl_1_bss_1AA8[arg0 - 4].unk4 = arg0;
}

void fn_1_77EC(void) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        if ((s32) lbl_1_bss_1AA8[var_r31].unk0 != 0) {
            fn_1_7848(var_r31);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_7848(s32 arg0) {
    M542Fx *temp_r4;
    M542Fx *temp_r4_2;
    M542Fx *temp_r4_3;
    M542Fx *temp_r4_4;
    M542Fx *temp_r5;
    s32 temp_r0;

    temp_r0 = lbl_1_bss_1AA8[arg0].unk4;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        lbl_1_bss_1AA8[arg0].unkC = 0;
        lbl_1_bss_1AA8[arg0].unk8 = 0;
        temp_r5 = &lbl_1_bss_1AA8[arg0];
        temp_r5->unk4 += 1;
        switch (arg0) {                             /* switch 2; irregular */
        case 2:                                     /* switch 2 */
        case 0:                                     /* switch 2 */
            lbl_1_bss_1AA8[arg0].unk14.x = (f32) (-0x190 - ((rand8() * 0x10) % 6));
            lbl_1_bss_1AA8[arg0].unk14.y = (f32) (0xAA - (rand8() % 40));
            lbl_1_bss_1AA8[arg0].unk14.z = 400.0f;
            lbl_1_bss_1AA8[arg0].unk10 = (f32) (0x32 - (rand8() % 30));
            break;
        case 3:                                     /* switch 2 */
            lbl_1_bss_1AA8[arg0].unk14.x = (f32) (-0x1F4 - ((rand8() * 0x10) % 6));
            lbl_1_bss_1AA8[arg0].unk14.y = (f32) ((rand8() % 20) + 0x12C);
            lbl_1_bss_1AA8[arg0].unk14.z = 200.0f;
            lbl_1_bss_1AA8[arg0].unk10 = (f32) -(0x14 - (rand8() % 10));
            break;
        }
        if (arg0 >= 2) {
            lbl_1_bss_1AA8[arg0].unk14.x = -lbl_1_bss_1AA8[arg0].unk14.x;
            if (arg0 == 2) {
                lbl_1_bss_1AA8[arg0].unk10 = 180.0f - lbl_1_bss_1AA8[arg0].unk10;
                return;
            }
            lbl_1_bss_1AA8[arg0].unk10 = -180.0f - lbl_1_bss_1AA8[arg0].unk10;
            return;
        }
        return;
    case 1:                                         /* switch 1 */
        temp_r4 = &lbl_1_bss_1AA8[arg0];
        temp_r4->unkC += 1;
        if ((s32) lbl_1_bss_1AA8[arg0].unkC >= 0x1E) {
            temp_r4_2 = &lbl_1_bss_1AA8[arg0];
            temp_r4_2->unk4 += 1;
            return;
        }
        fn_1_7E90(arg0);
        fn_1_800C(arg0);
        return;
    case 2:                                         /* switch 1 */
        if (fn_1_800C(arg0) == 0) {
            temp_r4_3 = &lbl_1_bss_1AA8[arg0];
            temp_r4_3->unk4 += 1;
            return;
        }
        break;
    case 3:                                         /* switch 1 */
        lbl_1_bss_1AA8[arg0].unk0 = 0;
        return;
    default:                                        /* switch 1 */
        lbl_1_bss_1AA8[arg0].unkC = 0;
        lbl_1_bss_1AA8[arg0].unk8 = 0;
        lbl_1_bss_1AA8[arg0].unk14.x = (f32) (((lbl_1_bss_1AA8[arg0].unk4 - 4) * 0x244) - 0x122);
        lbl_1_bss_1AA8[arg0].unk14.y = 132.0f;
        lbl_1_bss_1AA8[arg0].unk14.z = -128.0f;
        lbl_1_bss_1AA8[arg0].unk10 = 90.0f;
        lbl_1_bss_1AA8[arg0].unk4 = 6;
        return;
    case 6:                                         /* switch 1 */
        temp_r4_4 = &lbl_1_bss_1AA8[arg0];
        temp_r4_4->unkC += 1;
        if ((s32) (lbl_1_bss_1AA8[arg0].unkC % 5) == 0) {
            fn_1_8180(arg0);
        }
        fn_1_835C(arg0);
        break;
    }
}

void fn_1_7E90(s32 arg0) {
    M542Fx *temp_r4;
    M542Spark *temp_r31;

    temp_r31 = &lbl_1_bss_E8[arg0][lbl_1_bss_1AA8[arg0].unk8];
    temp_r31->unk0 += 1;
    temp_r31->unkC = (f32) ((s32) ((rand8() % 48) - 0x18) / 4);
    temp_r31->unk4 = 0;
    Hu3DModelAttrReset(temp_r31->unk10, 1U);
    Hu3DMotionTimeSet(temp_r31->unk10, 0.0f);
    Hu3DMotionSpeedSet(temp_r31->unk10, 3.33f);
    Hu3DModelPosSetV(temp_r31->unk10, &lbl_1_bss_1AA8[arg0].unk14);
    temp_r31->unk14.x = lbl_1_bss_1AA8[arg0].unk14.x;
    temp_r31->unk14.y = lbl_1_bss_1AA8[arg0].unk14.y;
    temp_r31->unk14.z = lbl_1_bss_1AA8[arg0].unk14.z;
    temp_r4 = &lbl_1_bss_1AA8[arg0];
    temp_r4->unk8 += 1;
}

s32 fn_1_800C(s32 arg0) {
    M542Spark *var_r31;
    s32 var_r29;
    s32 var_r30;

    var_r29 = 0;
    var_r31 = lbl_1_bss_E8[arg0];
    var_r30 = 0;
loop_7:
    if (var_r30 < 0x1E) {
        if ((s32) var_r31->unk0 != 0) {
            if ((s32) var_r31->unk4 < 0x1D) {
                var_r31->unk14.x = (f32) ((f64) var_r31->unk14.x + (13.5f * cos((3.141592653589793 * (f64) (var_r31->unkC + lbl_1_bss_1AA8[arg0].unk10)) / 180.0)));
                var_r31->unk14.y = (f32) ((f64) var_r31->unk14.y + (13.5f * sin((3.141592653589793 * (f64) (var_r31->unkC + lbl_1_bss_1AA8[arg0].unk10)) / 180.0)));
                var_r31->unk4 += 1;
            } else {
                var_r31->unk0 = 0;
                Hu3DModelAttrSet(var_r31->unk10, 1U);
            }
            var_r29 += 1;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_7;
    }
    return var_r29;
}

void fn_1_8180(s32 arg0) {
    M542Spark *temp_r31;

    temp_r31 = &lbl_1_bss_E8[arg0][lbl_1_bss_1AA8[arg0].unk8];
    temp_r31->unk0 += 1;
    temp_r31->unkC = (f32) ((s32) ((rand8() % 24) - 0xC) / 4);
    temp_r31->unk4 = 0;
    Hu3DModelAttrReset(temp_r31->unk10, 1U);
    Hu3DMotionTimeSet(temp_r31->unk10, 0.0f);
    Hu3DMotionSpeedSet(temp_r31->unk10, 3.3f);
    Hu3DModelScaleSet(temp_r31->unk10, 0.3f, 0.3f, 1.0f);
    Hu3DModelPosSetV(temp_r31->unk10, &lbl_1_bss_1AA8[arg0].unk14);
    temp_r31->unk14.x = lbl_1_bss_1AA8[arg0].unk14.x;
    temp_r31->unk14.y = lbl_1_bss_1AA8[arg0].unk14.y;
    temp_r31->unk14.z = lbl_1_bss_1AA8[arg0].unk14.z;
    lbl_1_bss_1AA8[arg0].unk8 = (lbl_1_bss_1AA8[arg0].unk8 + 1) % 30;
}

s32 fn_1_835C(s32 arg0) {
    M542Spark *var_r31;
    s32 var_r29;
    s32 var_r30;

    var_r29 = 0;
    var_r31 = lbl_1_bss_E8[arg0];
    var_r30 = 0;
loop_7:
    if (var_r30 < 0x1E) {
        if ((s32) var_r31->unk0 != 0) {
            if ((s32) var_r31->unk4 < 0x1E) {
                var_r31->unk14.x = (f32) ((f64) var_r31->unk14.x + (4.0f * cos((3.141592653589793 * (f64) (var_r31->unkC + lbl_1_bss_1AA8[arg0].unk10)) / 180.0)));
                var_r31->unk14.y = (f32) ((f64) var_r31->unk14.y + (4.0f * sin((3.141592653589793 * (f64) (var_r31->unkC + lbl_1_bss_1AA8[arg0].unk10)) / 180.0)));
                var_r31->unk4 += 1;
            } else {
                var_r31->unk0 = 0;
                Hu3DModelAttrSet(var_r31->unk10, 1U);
            }
            var_r29 += 1;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_7;
    }
    return var_r29;
}



void ObjectSetup(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x22) {
        lbl_1_bss_1588[var_r31].unk0 = -1;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 4) {
        var_r30 = 0;
loop_6:
        if (var_r30 < 0x1E) {
            lbl_1_bss_E8[var_r31_2][var_r30].unk0 = 0;
            lbl_1_bss_E8[var_r31_2][var_r30].unk10 = -1;
            var_r30 += 1;
            goto loop_6;
        }
        var_r31_2 += 1;
        goto loop_8;
    }
    fn_1_84D0(&lbl_1_bss_1954, lbl_1_bss_1588, lbl_1_data_0);
    lbl_1_bss_1954.unk0 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_1954.unk0);
    omAddObjEx(lbl_1_bss_1954.unk0, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(lbl_1_bss_1954.unk0, 0x7FDA, 0U, 0U, -1, fn_1_8C94);
    omAddObjEx(lbl_1_bss_1954.unk0, 0x7FDA, 0U, 0U, -1, fn_1_94B4);
    MgSeqCreate(&lbl_1_data_254);
}

void fn_1_248(s16 arg0, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    s16 sp8;
    s16 temp_r3;

    sp8 = arg0;
    fn_1_871C(0);
    fn_1_89DC(&lbl_1_data_80[lbl_1_bss_1954.unk4[0].unk0], &lbl_1_data_80[lbl_1_bss_1954.unk4[1].unk0]);
    fn_1_8A00(lbl_1_bss_54[0], lbl_1_bss_54[1]);
    fn_1_8A24();
    fn_1_9150();
    omAddObjEx(lbl_1_bss_1954.unk0, 0x7FDA, 0U, 0U, -1, fn_1_92A4);
    fn_1_FC8();
    Center.x = 0.0f;
    Center.y = 275.0f;
    Center.z = 0.0f;
    CRot.x = -50.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 800.0f;
    lbl_1_bss_78->center.x = 0.0f;
    lbl_1_bss_78->center.y = 185.0f;
    lbl_1_bss_78->center.z = 0.0f;
    lbl_1_bss_78->rot.x = -10.0f;
    lbl_1_bss_78->rot.y = 0.0f;
    lbl_1_bss_78->rot.z = 0.0f;
    lbl_1_bss_78->zoom = 1120.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    omAddObjEx(lbl_1_bss_1954.unk0, 0x7FDA, 0U, 0U, -1, fn_1_D3C);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    sp24.x = 0.0f;
    sp24.y = 1200.0f;
    sp24.z = 600.0f;
    sp18.x = 0.0f;
    sp18.y = 1.0f;
    sp18.z = 0.0f;
    spC.x = 0.0f;
    spC.y = 0.0f;
    spC.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&sp24, &sp18, &spC);
    Hu3DModelShadowSet(lbl_1_bss_1954.unk3C[0x20].unk0);
    Hu3DModelShadowSet(lbl_1_bss_1954.unk3C[0x21].unk0);
    Hu3DModelShadowMapSet(lbl_1_bss_1954.unk3C->unk0);
    lbl_1_bss_1954.unk50[0].unk0 = 0;
    lbl_1_bss_1954.unk50[0].unk4 = 1.0f;
    lbl_1_bss_1954.unk50[0].unkC = 0.0f;
    lbl_1_bss_1954.unk50[0].unk18 = 0x40000001;
    lbl_1_bss_1954.unk50[1].unk0 = 0;
    lbl_1_bss_1954.unk50[1].unk4 = 1.0f;
    lbl_1_bss_1954.unk50[1].unkC = 0.0f;
    lbl_1_bss_1954.unk50[1].unk18 = 0x40000001;
    fn_1_4994();
    lbl_1_bss_10 = 0;
    fn_1_249C(&lbl_1_bss_10);
    Hu3DModelAttrReset(lbl_1_bss_0, 1U);
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    MgSeqModeNext();
}

void fn_1_7A0(s16 mode, s16 frameNo) {
    lbl_1_data_27C[lbl_1_bss_1954.unkA0]();
}

void fn_1_7E4(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    lbl_1_bss_1954.unkA0 = 0;
    lbl_1_bss_1954.unkA4 = 0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
}

void fn_1_838(s16 mode, s16 frameNo) {
    lbl_1_data_28C[lbl_1_bss_1954.unkA0]();
    if (((s32) lbl_1_bss_4 != 0) || ((s32) lbl_1_bss_8 != 0)) {
        if ((s32) lbl_1_bss_C >= 0x12C) {
            if ((s32) lbl_1_data_298 < 0) {
                lbl_1_data_298 = HuAudFXPlay(0x812);
            }
            lbl_1_bss_8 = (lbl_1_bss_8 + 1) % 48;
            lbl_1_bss_10 = (s8) (96.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_8 * 0xB4) / 48)) / 180.0));
        }
    } else if ((s32) lbl_1_data_298 >= 0) {
        HuAudFXFadeOut(lbl_1_data_298, 0x14);
        lbl_1_data_298 = -1;
    }
}

void fn_1_9F0(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    if ((s32) lbl_1_data_298 >= 0) {
        HuAudFXFadeOut(lbl_1_data_298, 0x14);
        lbl_1_data_298 = -1;
    }
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    fn_1_5120();
    if ((((s32) lbl_1_bss_4 != 0) || ((s32) lbl_1_bss_8 != 0)) && ((s32) lbl_1_bss_C >= 0x12C)) {
        lbl_1_bss_8 = (lbl_1_bss_8 + 1) % 48;
        lbl_1_bss_10 = (s8) (96.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_8 * 0xB4) / 48)) / 180.0));
    }
}

void fn_1_B70(s16 mode, s16 frameNo) {
    lbl_1_data_29C[lbl_1_bss_1954.unkA0]();
    if ((((s32) lbl_1_bss_4 != 0) || ((s32) lbl_1_bss_8 != 0)) && ((s32) lbl_1_bss_C >= 0x12C)) {
        lbl_1_bss_8 = (lbl_1_bss_8 + 1) % 48;
        lbl_1_bss_10 = (s8) (96.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_8 * 0xB4) / 48)) / 180.0));
    }
}

void fn_1_CC4(s16 mode, s16 frameNo) {
    MgSeqModeNext();
    fn_1_737C();
}

void fn_1_CE8(s16 mode, s16 frameNo) {
    fn_1_737C();
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

void fn_1_D1C(s16 mode, s16 frameNo) {
    fn_1_24F8();
}

void fn_1_D3C(omObjData *obj) {
    M542Model *var_r31;
    M542Spark *temp_r29;
    s32 var_r28;
    s32 var_r30;
    s32 var_r30_2;

    var_r31 = lbl_1_bss_1588;
    var_r30 = 0;
loop_4:
    if (var_r30 < 0x22) {
        if ((s16) var_r31->unk0 >= 0) {
            Hu3DModelPosSetV(var_r31->unk0, &var_r31->unk4);
            Hu3DModelRotSetV(var_r31->unk0, &var_r31->unk10);
        }
        var_r30 += 1;
        var_r31++;
        goto loop_4;
    }
    var_r30_2 = 0;
loop_12:
    if (var_r30_2 < 4) {
        var_r28 = 0;
loop_10:
        if (var_r28 < 0x1E) {
            temp_r29 = &lbl_1_bss_E8[var_r30_2][var_r28];
            if ((s32) temp_r29->unk0 != 0) {
                Hu3DModelPosSetV(temp_r29->unk10, &temp_r29->unk14);
                Hu3DModelRotSetV(temp_r29->unk10, &temp_r29->unk20);
            }
            var_r28 += 1;
            goto loop_10;
        }
        var_r30_2 += 1;
        goto loop_12;
    }
}



void fn_1_FC8(void) {
    M542Model *temp_r31;
    M542Model *temp_r31_2;
    M542Model *temp_r31_3;
    M542Model *temp_r31_4;
    M542Model *temp_r31_5;
    M542Model *temp_r31_6;
    M542Model *temp_r31_7;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;
    s32 var_r30_7;
    s32 var_r30_8;

    lbl_1_bss_1588[6].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_1588[6].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_1588[6].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_1588[6].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_1588[6].unk4.x = 0.0f;
    lbl_1_bss_1588[6].unk4.y = 0.0f;
    lbl_1_bss_1588[6].unk4.z = 0.0f;
    lbl_1_bss_1588[6].unk10.x = 0.0f;
    lbl_1_bss_1588[6].unk10.y = 0.0f;
    lbl_1_bss_1588[6].unk10.z = 0.0f;
    Hu3DModelCameraSet(lbl_1_bss_1588[6].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_1588[6].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_1588[6].unk0, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1588[6].unk0, 1U);
    var_r30 = 0;
loop_4:
    if (var_r30 < 4) {
        temp_r31 = &lbl_1_bss_1588[var_r30 + 7];
        temp_r31->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[var_r30 + 7], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
        Hu3DModelAttrReset(temp_r31->unk0, 0x40000001U);
        if (var_r30 >= 2) {
            Hu3DModelShadowMapSet(temp_r31->unk0);
        }
        var_r30 += 1;
        goto loop_4;
    }
    var_r30_2 = 0;
loop_10:
    if (var_r30_2 < 2) {
        temp_r31_2 = &lbl_1_bss_1588[var_r30_2 + 0xB];
        if (var_r30_2 == 0) {
            temp_r31_2->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            temp_r31_2->unk0 = Hu3DModelLink(lbl_1_bss_1954.unk3C[0xB].unk0);
        }
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
        Hu3DModelPosSet(temp_r31_2->unk0, -210.0f + (420.0f * (f32) var_r30_2), 0.0f, 254.0f);
        temp_r31_2->unk4.x = -210.0f + (420.0f * (f32) var_r30_2);
        temp_r31_2->unk4.y = 0.0f;
        temp_r31_2->unk4.z = 254.0f;
        Hu3DModelShadowMapSet(temp_r31_2->unk0);
        var_r30_2 += 1;
        goto loop_10;
    }
    var_r30_3 = 0;
loop_16:
    if (var_r30_3 < 2) {
        temp_r31_3 = &lbl_1_bss_1588[var_r30_3 + 0xD];
        if (var_r30_3 == 0) {
            temp_r31_3->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            temp_r31_3->unk0 = Hu3DModelLink(lbl_1_bss_1954.unk3C[0xD].unk0);
        }
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
        Hu3DModelPosSet(temp_r31_3->unk0, -210.0f + (420.0f * (f32) var_r30_3), 0.0f, 254.0f);
        temp_r31_3->unk4.x = -210.0f + (420.0f * (f32) var_r30_3);
        temp_r31_3->unk4.y = 0.0f;
        temp_r31_3->unk4.z = 254.0f;
        Hu3DModelAttrSet(temp_r31_3->unk0, 1U);
        var_r30_3 += 1;
        goto loop_16;
    }
    var_r30_4 = 0;
loop_22:
    if (var_r30_4 < 2) {
        temp_r31_4 = &lbl_1_bss_1588[var_r30_4 + 0xF];
        if (Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_4].unk2) > 9) {
            temp_r31_4->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            temp_r31_4->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_4].unk2) + 0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
        Hu3DModelPosSet(temp_r31_4->unk0, -290.0f + (580.0f * (f32) var_r30_4), 132.0f, -128.0f);
        temp_r31_4->unk4.x = -290.0f + (580.0f * (f32) var_r30_4);
        temp_r31_4->unk4.y = 132.0f;
        temp_r31_4->unk4.z = -128.0f;
        var_r30_4 += 1;
        goto loop_22;
    }
    var_r30_5 = 0;
loop_31:
    if (var_r30_5 < 5) {
        var_r29 = 0;
loop_29:
        if (var_r29 < 2) {
            temp_r31_5 = &lbl_1_bss_1588[var_r30_5 + (var_r29 * 5) + 0x11];
            temp_r31_5->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[var_r30_5 + 0x17], MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelAttrSet(temp_r31_5->unk0, 1U);
            Hu3DModelPosSet(temp_r31_5->unk0, 0.0f, 0.0f, 0.0f);
            Hu3DModelRotSet(temp_r31_5->unk0, 0.0f, 0.0f, 0.0f);
            temp_r31_5->unk4.x = 0.0f;
            temp_r31_5->unk4.y = 0.0f;
            temp_r31_5->unk4.z = 0.0f;
            temp_r31_5->unk10.x = 0.0f;
            temp_r31_5->unk10.y = 0.0f;
            temp_r31_5->unk10.z = 0.0f;
            Hu3DModelCameraSet(temp_r31_5->unk0, 1U);
            Hu3DMotionTimeSet(temp_r31_5->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r31_5->unk0, 0.0f);
            Hu3DModelAttrReset(temp_r31_5->unk0, 1U);
            Hu3DModelPosSet(temp_r31_5->unk0, -210.0f + (420.0f * (f32) var_r29), 0.0f, 0.0f);
            temp_r31_5->unk4.x = -210.0f + (420.0f * (f32) var_r29);
            temp_r31_5->unk4.y = 0.0f;
            temp_r31_5->unk4.z = 0.0f;
            if (var_r30_5 == 4) {
                Hu3DMotionTimeSet(temp_r31_5->unk0, 30.0f);
                Hu3DMotionSpeedSet(temp_r31_5->unk0, 0.0f);
                Hu3DModelAttrSet(temp_r31_5->unk0, 0x40000001U);
            } else {
                lbl_1_bss_1940[var_r29][var_r30_5] = Hu3DTexScrollCreate(temp_r31_5->unk0, "m542count01");
            }
            var_r29 += 1;
            goto loop_29;
        }
        var_r30_5 += 1;
        goto loop_31;
    }
    var_r30_6 = 0;
loop_34:
    if (var_r30_6 < 2) {
        temp_r31_6 = &lbl_1_bss_1588[var_r30_6 + 0x1B];
        temp_r31_6->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[var_r30_6 + 0x1C], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31_6->unk0, 1U);
        Hu3DModelPosSet(temp_r31_6->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31_6->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31_6->unk4.x = 0.0f;
        temp_r31_6->unk4.y = 0.0f;
        temp_r31_6->unk4.z = 0.0f;
        temp_r31_6->unk10.x = 0.0f;
        temp_r31_6->unk10.y = 0.0f;
        temp_r31_6->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31_6->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31_6->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31_6->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31_6->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_6->unk0, 4);
        Hu3DModelPosSet(temp_r31_6->unk0, -290.0f + (580.0f * (f32) var_r30_6), 132.0f, -128.0f);
        temp_r31_6->unk4.x = -290.0f + (580.0f * (f32) var_r30_6);
        temp_r31_6->unk4.y = 132.0f;
        temp_r31_6->unk4.z = -128.0f;
        Hu3DModelAttrSet(temp_r31_6->unk0, 1U);
        lbl_1_bss_1940[var_r30_6][4] = Hu3DTexScrollCreate(temp_r31_6->unk0, lbl_1_data_31C);
        Hu3DTexScrollPosSet(lbl_1_bss_1940[var_r30_6][4], lbl_1_data_2A8[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_6].unk2)].unk0, lbl_1_data_2A8[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_6].unk2)].unk4, 0.0f);
        var_r30_6 += 1;
        goto loop_34;
    }
    lbl_1_bss_1588[0x1D].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[0x1E], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_1588[0x1D].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_1588[0x1D].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_1588[0x1D].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_1588[0x1D].unk4.x = 0.0f;
    lbl_1_bss_1588[0x1D].unk4.y = 0.0f;
    lbl_1_bss_1588[0x1D].unk4.z = 0.0f;
    lbl_1_bss_1588[0x1D].unk10.x = 0.0f;
    lbl_1_bss_1588[0x1D].unk10.y = 0.0f;
    lbl_1_bss_1588[0x1D].unk10.z = 0.0f;
    Hu3DModelCameraSet(lbl_1_bss_1588[0x1D].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_1588[0x1D].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_1588[0x1D].unk0, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1588[0x1D].unk0, 1U);
    Hu3DModelAttrSet(lbl_1_bss_1588[0x1D].unk0, 1U);
    var_r30_7 = 0;
loop_40:
    if (var_r30_7 < 4) {
        var_r29_2 = 0;
loop_38:
        if (var_r29_2 < 0x1E) {
            lbl_1_bss_E8[var_r30_7][var_r29_2].unk10 = Hu3DModelLink(lbl_1_bss_1588[0x1D].unk0);
            Hu3DModelAttrSet(lbl_1_bss_1588[0x1D].unk0, 1U);
            Hu3DModelPosSet(lbl_1_bss_1588[0x1D].unk0, 0.0f, 0.0f, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_1588[0x1D].unk0, 0.0f, 0.0f, 0.0f);
            lbl_1_bss_1588[0x1D].unk4.x = 0.0f;
            lbl_1_bss_1588[0x1D].unk4.y = 0.0f;
            lbl_1_bss_1588[0x1D].unk4.z = 0.0f;
            lbl_1_bss_1588[0x1D].unk10.x = 0.0f;
            lbl_1_bss_1588[0x1D].unk10.y = 0.0f;
            lbl_1_bss_1588[0x1D].unk10.z = 0.0f;
            Hu3DModelCameraSet(lbl_1_bss_1588[0x1D].unk0, 1U);
            Hu3DMotionTimeSet(lbl_1_bss_1588[0x1D].unk0, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1588[0x1D].unk0, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_1588[0x1D].unk0, 1U);
            Hu3DModelAttrSet(lbl_1_bss_E8[var_r30_7][var_r29_2].unk10, 1U);
            Hu3DModelLayerSet(lbl_1_bss_E8[var_r30_7][var_r29_2].unk10, 5);
            var_r29_2 += 1;
            goto loop_38;
        }
        var_r30_7 += 1;
        goto loop_40;
    }
    var_r30_8 = 0;
loop_43:
    if (var_r30_8 < 2) {
        temp_r31_7 = &lbl_1_bss_1588[var_r30_8 + 0x1E];
        temp_r31_7->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[0x1F], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31_7->unk0, 1U);
        Hu3DModelPosSet(temp_r31_7->unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(temp_r31_7->unk0, 0.0f, 0.0f, 0.0f);
        temp_r31_7->unk4.x = 0.0f;
        temp_r31_7->unk4.y = 0.0f;
        temp_r31_7->unk4.z = 0.0f;
        temp_r31_7->unk10.x = 0.0f;
        temp_r31_7->unk10.y = 0.0f;
        temp_r31_7->unk10.z = 0.0f;
        Hu3DModelCameraSet(temp_r31_7->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31_7->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31_7->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31_7->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_7->unk0, 5);
        Hu3DModelPosSet(temp_r31_7->unk0, -290.0f + (580.0f * (f32) var_r30_8), 464.0f, -128.0f);
        temp_r31_7->unk4.x = -290.0f + (580.0f * (f32) var_r30_8);
        temp_r31_7->unk4.y = 464.0f;
        temp_r31_7->unk4.z = -128.0f;
        Hu3DModelAttrSet(temp_r31_7->unk0, 1U);
        var_r30_8 += 1;
        goto loop_43;
    }
}

void fn_1_249C(s8 *alpha) {
    lbl_1_bss_0 = Hu3DHookFuncCreate(fn_1_2524);
    Hu3DModelLayerSet(lbl_1_bss_0, 6);
    Hu3DModelCameraSet(lbl_1_bss_0, 1U);
}

void fn_1_24F8(void) {
    Hu3DModelKill(lbl_1_bss_0);
}

void fn_1_2524(HU3DMODEL *modelP, Mtx mtx) {
    Mtx44 proj;
    GXColor color = { 255, 0, 0, 0 };

    color.a = (u8) lbl_1_bss_10;
    if (color.a == 0) {
        return;
    }
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1000.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXPosition3f32(640.0f, 480.0f, 0.0f);
    GXPosition3f32(0.0f, 480.0f, 0.0f);
    GXEnd();
}

void fn_1_84D0(M542Work *work, M542Model *models, s32 *dataNums) {
    s32 *sp10;
    M542Model *spC;
    M542Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_1B38 = sp8;
    memset((M542Com *) lbl_1_bss_1B38, 0, sizeof(M542Work));
    lbl_1_bss_1B38->unk3C = spC;
    lbl_1_bss_1B38->unk98 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_1B38->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_1B38->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_1B38->unk4[var_r31_2].unk0].character;
        lbl_1_bss_1B38->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_1B38->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_1B38->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_1B38->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_1B38->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_871C(s16 arg) {
    s16 sp8;
    s16 temp_r3;
    s16 var_r31;

    sp8 = arg;
    lbl_1_bss_1B38->unk9C = sp8;
    var_r31 = 0;
loop_7:
    if (var_r31 < 6) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1B38->unk98[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_1B38->unk3C[var_r31].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DModelPosSetV(temp_r3, &lbl_1_data_3B0[var_r31]);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        if (var_r31 != 0) {
            if (var_r31 == 4) {
                Hu3DMotionSpeedSet(temp_r3, 0.5f);
            } else {
                Hu3DMotionSpeedSet(temp_r3, 1.0f);
            }
            Hu3DMotionTimeSet(temp_r3, 0.0f);
            Hu3DModelAttrSet(temp_r3, 0x40000001U);
        }
        lbl_1_bss_1B38->unk3C[var_r31].unk4.x = lbl_1_data_3B0[var_r31].x;
        lbl_1_bss_1B38->unk3C[var_r31].unk4.y = lbl_1_data_3B0[var_r31].y;
        lbl_1_bss_1B38->unk3C[var_r31].unk4.z = lbl_1_data_3B0[var_r31].z;
        lbl_1_bss_1B38->unk3C[var_r31].unk10.x = 0.0f;
        lbl_1_bss_1B38->unk3C[var_r31].unk10.y = 0.0f;
        lbl_1_bss_1B38->unk3C[var_r31].unk10.z = 0.0f;
        Hu3DModelLayerSet(temp_r3, 0);
        Hu3DModelAttrReset(temp_r3, 1U);
        var_r31 += 1;
        goto loop_7;
    }
}

void fn_1_89DC(M542Char *chr0, M542Char *chr1) {
    lbl_1_bss_1B38->unk40[0] = chr0;
    lbl_1_bss_1B38->unk40[1] = chr1;
}

void fn_1_8A00(s16 *mot0, s16 *mot1) {
    lbl_1_bss_1B38->unk48[0] = mot0;
    lbl_1_bss_1B38->unk48[1] = mot1;
}

void fn_1_8A24(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk0 = CharModelCreate(lbl_1_bss_1B38->unk4[var_r31].unk2, 2);
        Hu3DModelPosSet(lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk0, (f32) ((var_r31 * 0x1A4) - 0xD2), 170.0f, 254.0f);
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk4.x = (f32) ((var_r31 * 0x1A4) - 0xD2);
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk4.y = 170.0f;
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk4.z = 254.0f;
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk10.x = 0.0f;
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk10.y = 0.0f;
        lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk10.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk0, 0x40000001U);
        Hu3DModelCameraSet(lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_1B38->unk3C[var_r31 + 0x20].unk0, 0);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_8C94(omObjData *obj) {
    s32 var_r31;
    s8 var_r27;
    s8 var_r28;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_1B38->unk4[var_r31].unk4 != 0) {
            memset((M542Com *) &lbl_1_bss_1B38->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_1B38->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_1B38->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk10;
            }
            lbl_1_bss_1B38->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_1B38->unk4[var_r31].unk11 = (s8) (u8) HuPadStkY[lbl_1_bss_1B38->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk11 >= 0) {
                var_r28 = (s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk11;
            } else {
                var_r28 = -(s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk11;
            }
            if (var_r28 < 0xA) {
                var_r27 = 0;
            } else {
                var_r27 = (s8) (u8) lbl_1_bss_1B38->unk4[var_r31].unk11;
            }
            lbl_1_bss_1B38->unk4[var_r31].unk11 = var_r27;
            lbl_1_bss_1B38->unk4[var_r31].unk14 = (s8) (u8) HuPadSubStkX[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkY[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk16 = HuPadTrigL[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk17 = HuPadTrigR[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk18 = HuPadDStk[lbl_1_bss_1B38->unk4[var_r31].unk6];
            lbl_1_bss_1B38->unk4[var_r31].unk19 = HuPadDStkRep[lbl_1_bss_1B38->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_9150(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 9) {
            lbl_1_bss_1B38->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_1B38->unk4[var_r31].unk2, lbl_1_bss_1B38->unk40[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_1B38->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_1B38->unk50[var_r31_2].unk4 = 1.0f;
        lbl_1_bss_1B38->unk50[var_r31_2].unk8 = 1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

void fn_1_92A4(omObjData *obj) {
    M542Anim *temp_r31;
    s16 temp_r0;
    s16 var_r29;

    var_r29 = 0;
loop_12:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_1B38->unk50[var_r29];
        temp_r0 = var_r29 + 0x20;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_1B38->unk3C[temp_r0].unk0, lbl_1_bss_1B38->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_1B38->unk3C[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_1B38->unk3C[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_1B38->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_1B38->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r31->unk20 = 0;
            temp_r31->unk18 = 0;
            temp_r31->unk1C = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_1B38->unk3C[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_1B38->unk3C[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        var_r29 += 1;
        goto loop_12;
    }
}

void fn_1_94B4(omObjData *obj) {

}
