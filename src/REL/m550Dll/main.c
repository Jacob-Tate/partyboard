// MP5 m550 (a 1 vs 1 button-mashing duel), generated from its m2c draft by tools/mp5/ports/m550dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m550dll (tools/mp5/decomp.py m550dll --types tools/mp5/types/m550dll.h)
// Written from the draft: a 1 vs 1 button-mashing duel (A/B alternation) on MP5's MgSeq sequencer. The same
// game framework as m548 (work struct lbl_1_bss_14AC, reached through the pointer lbl_1_bss_1FC0).

typedef struct M550Model { // model table entry, 0x1C (0xB7 of them in lbl_1_bss_A8)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M550Model;

typedef struct M550Player { // 0x1C
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // com: difficulty + 1
    s16 unk6; // pad
    s32 unk8; // HuPadBtn
    s32 unkC; // HuPadBtnDown (the game masks it with 0x300)
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
} M550Player;

typedef struct M550Char { // per MP5 character, 0x14
    u32 unk0[5]; // MP5 motion data numbers
} M550Char;

typedef struct M550Anim { // per player character animation request, 0x54 (fn_1_61E8 applies it)
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
    s32 unk24; // motion ended
    s16 unk28; // switch to the next motion when it ends
    s16 unk2A; // next motion
    f32 unk2C; // next time
    u32 unk30; // next attrs to set
    u32 unk34; // next attrs to reset
    s16 unk38; // shift state
    s16 unk3A; // shift target motion
    u32 unk3C; // shift attr
    f32 unk40; // shift start time
    f32 unk44; // shift length
    f32 unk48;
    f32 unk4C; // shift max time
    f32 unk50;
} M550Anim;

typedef struct M550Prop { // background animation state, 0x4C
    s32 unk0; // started
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    char pad20[0xC];
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    char pad48[4];
} M550Prop;

typedef struct M550Work { // lbl_1_bss_14AC, 0xA14
    HUPROCESS *unk0; // object manager
    M550Player unk4[2];
    M550Model *unk3C; // model table (lbl_1_bss_A8)
    M550Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_24)
    M550Anim unk50[2];
    s32 *unkF8; // data numbers (lbl_1_data_8)
    s16 unkFC;
    char padFE[2];
    s32 unk100; // mode step
    s32 unk104[3]; // [0]: mode sub step, and per player state (0x104 + 4 * player, the first one shared)
    s32 unk110; // frame counter
    s32 unk114;
    s32 unk118;
    char pad11C[4];
    s32 unk120[4]; // button press count per player, then the saved counts
    s32 unk130; // winner + 1
    s32 unk134; // ending state
    f32 unk138[2];
    char pad140[8];
    Vec unk148[4]; // hook positions / rotations (also used as scratch while the loser falls)
    M550Prop unk178[17];
    char pad68C[0x388];
} M550Work;

typedef struct M550Ai { // lbl_1_bss_4, 0x10
    s16 unk0; // level
    char pad2[6];
    s32 unk8; // frames until the next press
    s32 unkC; // counter
} M550Ai;


void fn_1_984(s32 model, f32 alpha);
void fn_1_A00(s32 player, Vec *pos, Vec *rot);
void fn_1_B5C(s32 player);
void fn_1_D64(void);
void fn_1_F7C(void);
void fn_1_10BC(s32 player);
void fn_1_11F0(M550Model *m);
s32 fn_1_3BB0(s32 player);
void fn_1_3904(s32 player);
void fn_1_3DD8(s32 player);
s32 fn_1_4308(s32 player);
void fn_1_4494(s32 player);
void fn_1_4688(s32 player);
void fn_1_4898(s32 player, s32 count);
s32 fn_1_4990(s32 player);
void fn_1_49F0(s32 player, s32 slot);
void fn_1_4C00(void);
void fn_1_4D94(void);
void fn_1_4E8C(M550Work *work, M550Model *models, s32 *dataNums);
void fn_1_50D8(s16 arg);
void fn_1_58F4(M550Char *chr0, M550Char *chr1);
void fn_1_5918(s16 *mot0, s16 *mot1);
void fn_1_593C(void);
void fn_1_6094(void);
void fn_1_6D8C(void);
void fn_1_7C00(void);
void fn_1_7E94(void);
void fn_1_8190(void);
void fn_1_1C84(void);
void fn_1_1D88(void);
void fn_1_1DCC(void);
void fn_1_1E38(void);
void fn_1_235C(void);
void fn_1_2360(void);
void fn_1_2364(void);
void fn_1_2618(void);
void fn_1_2670(void);
void fn_1_2D98(void);
void fn_1_3088(void);
void fn_1_3174(void);
void fn_1_3324(void);
void fn_1_3904(s32 player);
s32 fn_1_3BB0(s32 player);
void fn_1_3DD8(s32 player);
void fn_1_4494(s32 player);
void fn_1_4688(s32 player);
void fn_1_4898(s32 player, s32 count);
void fn_1_49F0(s32 player, s32 slot);
void fn_1_4C00(void);
void fn_1_4D94(void);
void ObjectSetup(void);
void fn_1_198(s16 arg0, s16 frameNo);
void fn_1_6B4(s16 mode, s16 frameNo);
void fn_1_6F8(s16 arg0, s16 frameNo);
void fn_1_750(s16 mode, s16 frameNo);
void fn_1_794(s16 arg0, s16 frameNo);
void fn_1_7FC(s16 mode, s16 frameNo);
void fn_1_840(s16 mode, s16 frameNo);
void fn_1_8A0(s16 mode, s16 frameNo);
void fn_1_910(s16 mode, s16 frameNo);
void fn_1_914(omObjData *obj);
void fn_1_984(s32 model, f32 alpha);
void fn_1_A00(s32 player, Vec *pos, Vec *rot);
void fn_1_D64(void);
void fn_1_F7C(void);
void fn_1_10BC(s32 player);
void fn_1_131C(void);
void fn_1_4E8C(M550Work *work, M550Model *models, s32 *dataNums);
void fn_1_50D8(s16 arg);
void fn_1_58F4(M550Char *chr0, M550Char *chr1);
void fn_1_5918(s16 *mot0, s16 *mot1);
void fn_1_593C(void);
void fn_1_5BD8(omObjData *obj);
void fn_1_6094(void);
void fn_1_61E8(omObjData *obj);
void fn_1_65AC(omObjData *obj);
void fn_1_6600(void);
void fn_1_6B6C(void);
void fn_1_6D8C(void);
void fn_1_6DA4(void);
void fn_1_719C(void);
void fn_1_7C00(void);
void fn_1_7C4C(void);
void fn_1_7E94(void);
void fn_1_7EE0(void);
void fn_1_8190(void);
void fn_1_8350(void);

Vec lbl_1_data_250[0x1E] = {
    { -35.0f, 220.0f, 75.0f },
    { 80.0f, 145.0f, 0.0f },
    { -80.0f, 145.0f, 0.0f },
    { -29.0f, 165.0f, 90.0f },
    { 29.0f, 165.0f, 90.0f },
    { 70.0f, 190.0f, 55.0f },
    { 50.0f, 190.0f, -50.0f },
    { -50.0f, 190.0f, -50.0f },
    { -70.0f, 190.0f, 55.0f },
    { 0.0f, 260.0f, 0.0f },
    { 30.0f, 235.0f, -28.0f },
    { -30.0f, 235.0f, -28.0f },
    { -30.0f, 235.0f, 28.0f },
    { 30.0f, 235.0f, 28.0f },
    { 60.0f, 190.0f, 0.0f },
    { 0.0f, 200.0f, -60.0f },
    { -60.0f, 190.0f, 0.0f },
    { 0.0f, 200.0f, 60.0f },
    { 0.0f, 210.0f, 0.0f },
    { 29.0f, 180.0f, 28.0f },
    { 29.0f, 180.0f, -28.0f },
    { -29.0f, 180.0f, -28.0f },
    { -29.0f, 180.0f, 28.0f },
    { 50.0f, 135.0f, 30.0f },
    { 50.0f, 135.0f, -30.0f },
    { 0.0f, 135.0f, -55.0f },
    { -50.0f, 135.0f, -30.0f },
    { -50.0f, 135.0f, 30.0f },
    { 0.0f, 135.0f, 55.0f },
    { 0.0f, 120.0f, 0.0f },
};
s32 lbl_1_data_3B8 = -1;
s32 lbl_1_bss_1EC0[2];
s16 lbl_1_bss_1EC8;
s32 lbl_1_bss_1ECC[2][0x1E];
s32 lbl_1_data_0[2] = { DATA_MAKE_NUM(DATADIR_MP5_M550, 60), DATA_MAKE_NUM(DATADIR_MP5_M550, 61) };
s32 lbl_1_data_8[0x3C] = {
    DATA_MAKE_NUM(DATADIR_MP5_M550, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 31),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 32),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 33),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 34),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 35),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 36),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 37),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 38),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 39),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 40),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 41),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 42),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 43),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 44),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 45),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 46),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 47),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 48),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 49),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 50),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 51),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 52),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 53),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 54),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 55),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 56),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 57),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 58),
    DATA_MAKE_NUM(DATADIR_MP5_M550, 59),
};
M550Char lbl_1_data_F8[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIO, 172), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 173), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 172), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 173), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACH, 172), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 173), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 172), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 173), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIO, 172), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 173), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISY, 172), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 173), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 125) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 172), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 173), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 96), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 128), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 125) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 125 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 125 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 125 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 125 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 125 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 172 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 173 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 96 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 128 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 125 */ } },
};
MGSEQ_PARAM lbl_1_data_1FC = {
    0,
    0,
    fn_1_198,
    fn_1_6B4,
    fn_1_6F8,
    fn_1_750,
    fn_1_794,
    fn_1_7FC,
    fn_1_840,
    fn_1_8A0,
    fn_1_910,
};
void (*lbl_1_data_224[3])() = { fn_1_1C84, fn_1_1D88, fn_1_1DCC };
void (*lbl_1_data_230[3])() = { fn_1_1E38, fn_1_235C, fn_1_2360 };
void (*lbl_1_data_23C[5])() = { fn_1_2670, fn_1_2D98, fn_1_3088, fn_1_3174, fn_1_3324 };
MGTIMER *lbl_1_bss_0;
M550Ai lbl_1_bss_4[2];
s16 lbl_1_bss_24[2][5];
OMCAMERAVIEW lbl_1_bss_38[4];
M550Model lbl_1_bss_A8[0xB7];
M550Work lbl_1_bss_14AC;
Vec lbl_1_data_3D8[6] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
s16 lbl_1_data_420[2] = { 0, 0 };
void (*lbl_1_data_424[7])() = { fn_1_6600, fn_1_6B6C, fn_1_6DA4, fn_1_719C, fn_1_7C4C, fn_1_7EE0, fn_1_8350 };
M550Work *lbl_1_bss_1FC0;
s32 lbl_1_rodata_C8[0xD] = {
    0x85C,
    0x85D,
    0x85A,
    0x856,
    0x858,
    0x85F,
    0x857,
    0x85E,
    0x859,
    0x85B,
    0x85B,
    0x85B,
    0x85B,
}; /* const */
s32 lbl_1_rodata_158[3] = { 0xA0, 0xA7, 0xA8 };     /* const */
s32 lbl_1_rodata_164[3] = { 0x32, 0x37, 0x38 };     /* const */
s32 lbl_1_rodata_1A0[5] = { 0x97, 0x9A, 0x9D, 0x98, 0x9E }; /* const */
f32 lbl_1_rodata_1B4[5] = { 152.0f, 191.0f, 207.0f, 176.0f, 170.0f }; /* const */
f32 lbl_1_rodata_1C8[5] = { 5000.0f, 3200.0f, 5500.0f, 7000.0f, 6800.0f }; /* const */
f32 lbl_1_rodata_1DC[5] = { -800.0f, -900.0f, -800.0f, -300.0f, -400.0f }; /* const */
s32 lbl_1_rodata_220[4] = { 0xA3, 0xA5, 0xA4, 0xA6 }; /* const */
static s32 lbl_1_rodata_244 = 0xA7;                 /* const */
s32 lbl_1_rodata_274[6] = { 0xA8, 0xB3, 0xB5, 0xB4, 0xB6, 0xA9 }; /* const */
f32 lbl_1_rodata_28C[5] = { 2900.0f, 700.0f, 700.0f, 300.0f, 300.0f }; /* const */
f32 lbl_1_rodata_2A0[5] = { 90.0f, 180.0f, 0.0f, 90.0f, 270.0f }; /* const */
f32 lbl_1_rodata_2B4[5] = { 0.3f, 0.5f, 0.5f, 0.5f, 0.5f }; /* const */
f32 lbl_1_rodata_2C8[6] = { 1000.0f, 1200.0f, -6600.0f, -550.0f, 550.0f, -3120.0f }; /* const */
static s32 lbl_1_rodata_330 = 0xA1;                 /* const */
static s32 lbl_1_rodata_350 = 0xA2;                 /* const */
Vec lbl_1_rodata_370[4] = {
    { -700.0f, -1600.0f, 1100.0f },
    { 1100.0f, -1100.0f, -500.0f },
    { 800.0f, -2700.0f, 1200.0f },
    { -800.0f, -500.0f, -600.0f },
}; /* const */
f32 lbl_1_rodata_3A0[4] = { 1.0f, 1.2f, 0.7f, 1.5f }; /* const */
s32 lbl_1_rodata_3B0[4] = { 0x99, 0x9B, 0x9C, 0x9F }; /* const */
s32 lbl_1_rodata_3C0[4] = { 0x99, 0x9B, 0x9C, 0x9F }; /* const */

void fn_1_1C84(void) {
    s32 var_r31;
    s32 var_r31_2;

    lbl_1_bss_14AC.unk100 += 1;
    lbl_1_bss_14AC.unk104[0] = 0;
    lbl_1_bss_14AC.unk110 = 0x3F48;
    lbl_1_bss_0 = NULL;
    var_r31 = 0;
loop_4:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_14AC.unk4[var_r31].unk4 != 0) {
            fn_1_4494(var_r31);
        }
        var_r31 += 1;
        goto loop_4;
    }
    var_r31_2 = 0;
loop_7:
    if (var_r31_2 < 0x1E) {
        lbl_1_bss_1ECC[0][var_r31_2] = 0;
        lbl_1_bss_1ECC[1][var_r31_2] = 0;
        var_r31_2 += 1;
        goto loop_7;
    }
    omCameraViewMoveSimple(&lbl_1_bss_38[1], 0xB4);
    HuAudFXPlay(0x860);
    fn_1_D64();
}

void fn_1_1D88(void) {
    fn_1_D64();
    if (WipeCheckEnd() == 0) {
        lbl_1_bss_14AC.unk100 += 1;
    }
}

void fn_1_1DCC(void) {
    if (omCameraViewCheck(1U) != 0) {
        lbl_1_bss_14AC.unk100 = 0;
        lbl_1_bss_14AC.unk104[0] = 0;
        MgSeqModeNext();
        lbl_1_data_3B8 = HuAudBGMPlay(0x4B);
    }
    fn_1_D64();
}


void fn_1_1E38(void) {
    M550Model *temp_r30;
    s32 temp_r29;
    s32 temp_r31;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    u32 temp_r4;
    u8 temp_r3;

    var_r31 = 0;
loop_4:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_14AC.unk4[var_r31].unk4 != 0) {
            fn_1_4688(var_r31);
        }
        fn_1_3904(var_r31);
        var_r31 += 1;
        goto loop_4;
    }
    if ((s32) lbl_1_bss_14AC.unk130 == 0) {
        if (((s32) lbl_1_bss_14AC.unk120[0] >= 0x1E) || ((s32) lbl_1_bss_14AC.unk120[1] >= 0x1E)) {
            if ((s32) lbl_1_bss_14AC.unk120[0] == (s32) lbl_1_bss_14AC.unk120[1]) {
                temp_r3 = rand8();
                temp_r31 = temp_r3 & 1;
                lbl_1_bss_14AC.unk120[temp_r31] -= 1;
            }
            var_r31_2 = 0;
            if ((s32) lbl_1_bss_14AC.unk120[1] >= 0x1E) {
                var_r31_2 = 1;
            }
            lbl_1_bss_14AC.unk130 = var_r31_2 + 1;
            if ((MGTIMER *) lbl_1_bss_0 != NULL) {
                MgTimerKill(lbl_1_bss_0);
                lbl_1_bss_0 = NULL;
            }
        }
        if ((s32) lbl_1_bss_14AC.unk110 > 0) {
            lbl_1_bss_14AC.unk110 -= 1;
        } else if ((MGTIMER *) lbl_1_bss_0 != NULL) {
            if (MgTimerDoneCheck(lbl_1_bss_0) != 0) {
                lbl_1_bss_14AC.unk100 = 1;
                lbl_1_bss_14AC.unk120[0] = lbl_1_bss_14AC.unk120[2];
                lbl_1_bss_14AC.unk120[1] = lbl_1_bss_14AC.unk120[3];
                MgSeqModeNext();
                HuAudSStreamFadeOut(lbl_1_data_3B8, 0x3E8);
            }
        } else if ((s32) lbl_1_bss_14AC.unk110 == 0) {
            lbl_1_bss_0 = MgTimerCreate(0);
            MgTimerParamSet(lbl_1_bss_0, 0x708, 0, 0);
            MgTimerPosSet(lbl_1_bss_0, 288.0f, 64.0f);
            MgTimerModeOnSet(lbl_1_bss_0, 1);
            lbl_1_bss_14AC.unk110 -= 1;
        }
    }
    if ((s32) lbl_1_bss_14AC.unk130 != 0) {
        temp_r29 = (lbl_1_bss_14AC.unk130 - 1) ^ 1;
        if ((s32) lbl_1_bss_14AC.unk134 != 2) {
            switch ((s32) lbl_1_bss_14AC.unk134) {  /* irregular */
            case 0:
                if ((s32) lbl_1_bss_14AC.unk120[lbl_1_bss_14AC.unk130 - 1] == (s32) lbl_1_bss_14AC.unk120[lbl_1_bss_14AC.unk130 + 1]) {
                    lbl_1_bss_14AC.unk134 += 1;
                }
                break;
            case 1:
                if ((s32) lbl_1_bss_14AC.unk104[lbl_1_bss_14AC.unk130 - 1] == 0) {
                    lbl_1_bss_14AC.unk134 += 1;
                    lbl_1_bss_14AC.unk148[0].y = 1.0f;
                    lbl_1_bss_14AC.unk148[0].z = 0.0f;
                }
                break;
            default:
                temp_r30 = &lbl_1_bss_14AC.unk3C[temp_r29 + 4];
                temp_r30->unk10.z += (f32) ((temp_r29 * 0x28) - 0x14);
                temp_r30->unk4.x -= lbl_1_bss_14AC.unk148[0].y * (f32) (3 - (temp_r29 * 6));
                temp_r30->unk4.y += 6.0f * lbl_1_bss_14AC.unk148[0].y;
                lbl_1_bss_14AC.unk148[0].y = (f32) ((f64) lbl_1_bss_14AC.unk148[0].y * 0.95);
                Hu3DModelScaleSet(lbl_1_bss_14AC.unk3C[temp_r29 + 4].unk0, lbl_1_bss_14AC.unk148[0].y, lbl_1_bss_14AC.unk148[0].y, lbl_1_bss_14AC.unk148[0].y);
                break;
            }
        }
    }
    var_r31_3 = 0;
loop_36:
    if (var_r31_3 < 2) {
        fn_1_3DD8(var_r31_3);
        var_r31_3 += 1;
        goto loop_36;
    }
    fn_1_4C00();
    fn_1_D64();
}

void fn_1_235C(void) {

}

void fn_1_2360(void) {

}

void fn_1_2364(void) {
    M550Model *temp_r31;
    s32 temp_r29;
    s32 var_r30;

    temp_r29 = (lbl_1_bss_14AC.unk130 - 1) ^ 1;
    if (((s32) lbl_1_bss_14AC.unk130 != 0) && ((s32) lbl_1_bss_14AC.unk134 != 2)) {
        switch ((s32) lbl_1_bss_14AC.unk134) {      /* irregular */
        case 4:
            break;
        case 0:
            if ((s32) lbl_1_bss_14AC.unk120[lbl_1_bss_14AC.unk130 - 1] != (s32) lbl_1_bss_14AC.unk120[lbl_1_bss_14AC.unk130 + 1]) {
                lbl_1_bss_14AC.unk134 += 1;
            }
            break;
        case 1:
            if ((s32) lbl_1_bss_14AC.unk104[lbl_1_bss_14AC.unk130 - 1] == 0) {
                lbl_1_bss_14AC.unk134 += 1;
                lbl_1_bss_14AC.unk148[0].y = 1.0f;
                lbl_1_bss_14AC.unk148[0].z = 0.0f;
            }
            break;
        default:
            temp_r31 = &lbl_1_bss_14AC.unk3C[temp_r29 + 4];
            temp_r31->unk10.z += (f32) ((temp_r29 * 0x28) - 0x14);
            temp_r31->unk4.x -= lbl_1_bss_14AC.unk148[0].y * (f32) (3 - (temp_r29 * 6));
            temp_r31->unk4.y += 6.0f * lbl_1_bss_14AC.unk148[0].y;
            lbl_1_bss_14AC.unk148[0].y = (f32) ((f64) lbl_1_bss_14AC.unk148[0].y * 0.95);
            Hu3DModelScaleSet(lbl_1_bss_14AC.unk3C[temp_r29 + 4].unk0, lbl_1_bss_14AC.unk148[0].y, lbl_1_bss_14AC.unk148[0].y, lbl_1_bss_14AC.unk148[0].y);
            break;
        }
    }
    var_r30 = 0;
loop_16:
    if (var_r30 < 2) {
        fn_1_3DD8(var_r30);
        var_r30 += 1;
        goto loop_16;
    }
    fn_1_4C00();
    fn_1_D64();
}

void fn_1_2618(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        fn_1_3DD8(var_r31);
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_14AC.unk100 = 4;
    fn_1_4C00();
    fn_1_D64();
}

void fn_1_2670(void) {
    s32 temp_r30;
    s32 temp_r31;

    Center.x = 0.0f;
    Center.y = 2000.0f;
    Center.z = 0.0f;
    CRot.x = -90.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 300.0f;
    omOutView(NULL);
    temp_r31 = lbl_1_bss_14AC.unk130 - 1;
    temp_r30 = temp_r31 ^ 1;
    Hu3DModelHookReset(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0);
    Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[temp_r31 + 4].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, -200.0f + (400.0f * (f32) temp_r31), 2300.0f, 300.0f);
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk4.x = -200.0f + (400.0f * (f32) temp_r31);
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk4.y = 2300.0f;
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk4.z = 300.0f;
    Hu3DModelRotSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk10.x = 0.0f;
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk10.y = 0.0f;
    lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk10.z = 0.0f;
    lbl_1_bss_38[1].center.x = -200.0f + (400.0f * (f32) temp_r31);
    lbl_1_bss_38[1].center.y = 2400.0f;
    lbl_1_bss_38[1].center.z = 300.0f;
    lbl_1_bss_38[1].rot.x = -15.0f;
    lbl_1_bss_38[1].rot.y = 0.0f;
    lbl_1_bss_38[1].rot.z = 0.0f;
    lbl_1_bss_38[1].zoom = 600.0f;
    Hu3DMotionSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, lbl_1_bss_14AC.unk48[temp_r31][2]);
    Hu3DMotionTimeSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, 1.0f);
    Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, 0x40000001U);
    Hu3DMotionAttrSet(lbl_1_bss_14AC.unk48[temp_r31][2], 1U);
    Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[temp_r30 + 4].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, 0.0f, 1900.0f, 0.0f);
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk4.x = 0.0f;
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk4.y = 1900.0f;
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk4.z = 0.0f;
    Hu3DModelRotSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk10.x = 0.0f;
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk10.y = 0.0f;
    lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk10.z = 0.0f;
    Hu3DMotionSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, lbl_1_bss_14AC.unk48[temp_r30][4]);
    Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, 0x40000001U);
    Hu3DMotionTimeSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_14AC.unk3C[temp_r30 + 2].unk0, 1.0f);
    lbl_1_bss_14AC.unk100 += 1;
    lbl_1_bss_14AC.unk148[0].x = 1.0f;
    fn_1_D64();
    fn_1_7C00();
    fn_1_7E94();
    fn_1_8190();
}

void fn_1_2D98(void) {
    s32 sp8[13];
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r31;

    sp8[0] = lbl_1_rodata_C8[0];
    sp8[1] = lbl_1_rodata_C8[1];
    sp8[2] = lbl_1_rodata_C8[2];
    sp8[3] = lbl_1_rodata_C8[3];
    sp8[4] = lbl_1_rodata_C8[4];
    sp8[5] = lbl_1_rodata_C8[5];
    sp8[6] = lbl_1_rodata_C8[6];
    sp8[7] = lbl_1_rodata_C8[7];
    sp8[8] = lbl_1_rodata_C8[8];
    sp8[9] = lbl_1_rodata_C8[9];
    sp8[10] = lbl_1_rodata_C8[0xA];
    sp8[11] = lbl_1_rodata_C8[0xB];
    sp8[12] = lbl_1_rodata_C8[0xC];
    temp_r31 = (lbl_1_bss_14AC.unk130 - 1) ^ 1;
    if (lbl_1_bss_14AC.unk148[0].x == 1.0f) {
        HuAudFXPlay(sp8[lbl_1_bss_14AC.unk4[temp_r31].unk2]);
    }
    temp_r0 = temp_r31 + 2;
    lbl_1_bss_14AC.unk3C[temp_r0].unk4.y -= 8.0f;
    temp_r0_2 = temp_r31 + 2;
    lbl_1_bss_14AC.unk3C[temp_r0_2].unk10.y -= 1.0f;
    lbl_1_bss_14AC.unk148[0].x *= 0.96f;
    if (lbl_1_bss_14AC.unk148[0].x < 0.03f) {
        lbl_1_bss_14AC.unk148[0].x = 0.0f;
    }
    Hu3DModelScaleSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, lbl_1_bss_14AC.unk148[0].x, 1.0f, lbl_1_bss_14AC.unk148[0].x);
    if ((lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk4.y < -100.0f) || (lbl_1_bss_14AC.unk148[0].x <= 0.0f)) {
        Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[temp_r31 + 2].unk0, 1U);
        lbl_1_bss_14AC.unk100 += 1;
        lbl_1_bss_14AC.unk104[0] = 0;
        lbl_1_bss_14AC.unk120[1] = 0;
        lbl_1_bss_14AC.unk120[0] = 0;
        lbl_1_bss_14AC.unk114 = 0;
        lbl_1_bss_14AC.unk110 = 0;
        fn_1_4D94();
        omVibrate(lbl_1_bss_14AC.unk4[temp_r31].unk0, 0x1E, 6, 6);
        HuAudFXPlay(0x855);
    }
    fn_1_D64();
}

void fn_1_3088(void) {
    M550Model *temp_r31;
    s32 temp_r3;

    temp_r31 = &lbl_1_bss_14AC.unk3C[0x94];
    temp_r31->unk4.x = (f32) ((f64) temp_r31->unk4.x + (5.5 * sin(0.39269908169872414)));
    temp_r31->unk4.z = (f32) ((f64) temp_r31->unk4.z + (5.5 * cos(0.39269908169872414)));
    temp_r3 = lbl_1_bss_14AC.unk110;
    lbl_1_bss_14AC.unk110 = temp_r3 + 1;
    if (temp_r3 > 0x3C) {
        omCameraViewMoveSimple(&lbl_1_bss_38[1], 0xB4);
        lbl_1_bss_14AC.unk100 += 1;
        lbl_1_bss_14AC.unk118 = 0;
    }
    fn_1_D64();
}

void fn_1_3174(void) {
    s16 temp_r30;
    s32 temp_r31;
    s32 temp_r3;

    temp_r31 = lbl_1_bss_14AC.unk130 - 1;
    switch ((s32) lbl_1_bss_14AC.unk104[0]) {       /* irregular */
    case 0:
        temp_r3 = lbl_1_bss_14AC.unk118;
        lbl_1_bss_14AC.unk118 = temp_r3 + 1;
        if (temp_r3 > 0x78) {
            lbl_1_bss_14AC.unk104[0] += 1;
            lbl_1_bss_1EC8 = MGSeqWinCreate(lbl_1_bss_14AC.unk4[temp_r31].unk2, -1, -1, -1);
            temp_r30 = lbl_1_bss_14AC.unk4[temp_r31].unk0;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r30].coin_win = 0xA;
            }
            lbl_1_bss_14AC.unk110 = 0;
            HuAudJinglePlay(0x79);
            CharFXPlay(lbl_1_bss_14AC.unk4[temp_r31].unk2, 0x1FA);
        }
        break;
    case 1:
        lbl_1_bss_14AC.unk110 += 1;
        if ((GameMesStatGet(lbl_1_bss_1EC8) == 0) && ((s32) lbl_1_bss_14AC.unk110 >= 0xD0)) {
            GameMesKill(lbl_1_bss_1EC8);
            lbl_1_bss_14AC.unk100 = 0;
            MgSeqModeNext();
        }
        break;
    }
    fn_1_D64();
}

void fn_1_3324(void) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M550Model *temp_r30;
    M550Model *temp_r30_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 var_r31;
    s32 var_r31_2;

    switch ((s32) lbl_1_bss_14AC.unk104[0]) {       /* irregular */
    case 0:
        lbl_1_bss_1EC8 = MGSeqDrawCreate();
        lbl_1_bss_14AC.unk110 = 0;
        lbl_1_bss_14AC.unk104[0] += 1;
        fn_1_10BC(0);
        fn_1_10BC(1);
        omVibrate(lbl_1_bss_14AC.unk4[0].unk0, 0x28, 0xC, 0);
        omVibrate(lbl_1_bss_14AC.unk4[1].unk0, 0x28, 0xC, 0);
        HuAudJinglePlay(0x7B);
        break;
    case 1:
        lbl_1_bss_14AC.unk110 += 1;
        if ((GameMesStatGet(lbl_1_bss_1EC8) == 0) && ((s32) lbl_1_bss_14AC.unk110 >= 0xD0)) {
            GameMesKill(lbl_1_bss_1EC8);
            MgSeqModeNext();
            lbl_1_bss_14AC.unk100 = 1;
        }
        break;
    }
    if ((s32) lbl_1_bss_14AC.unk110 == 8) {
        var_r31 = 0;
loop_11:
        if (var_r31 < 2) {
            lbl_1_bss_14AC.unk50[var_r31].unk38 = 1;
            lbl_1_bss_14AC.unk50[var_r31].unk3A = 3;
            lbl_1_bss_14AC.unk50[var_r31].unk40 = 0.0f;
            lbl_1_bss_14AC.unk50[var_r31].unk44 = 8.0f;
            lbl_1_bss_14AC.unk50[var_r31].unk3C = 0x40000001;
            Hu3DModelObjMtxGet(lbl_1_bss_14AC.unk3C[var_r31 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r31].unk2, 1, 0), sp20);
            Hu3DModelHookReset(lbl_1_bss_14AC.unk3C[var_r31 + 2].unk0);
            temp_r30 = &lbl_1_bss_14AC.unk3C[var_r31 + 4];
            Hu3DMtxRotGet(sp20, &sp8);
            sp14.x = sp20[0][3];
            sp14.y = sp20[1][3];
            sp14.z = sp20[2][3];
            Hu3DModelPosSetV(temp_r30->unk0, &sp14);
            Hu3DModelRotSetV(temp_r30->unk0, &sp8);
        Hu3DModelScaleSet(temp_r30->unk0, 1.0f, 1.0f, 1.0f);
            temp_r30->unk4.x = sp14.x;
            temp_r30->unk4.y = sp14.y;
            temp_r30->unk4.z = sp14.z;
            temp_r30->unk10.x = sp8.x;
            temp_r30->unk10.y = sp8.y;
            temp_r30->unk10.z = sp8.z;
            fn_1_F7C();
            lbl_1_bss_14AC.unk138[0] = 1.0f;
            lbl_1_bss_14AC.unk138[1] = 1.0f;
            var_r31 += 1;
            goto loop_11;
        }
    }
    if ((s32) lbl_1_bss_14AC.unk110 > 8) {
        var_r31_2 = 0;
loop_15:
        if (var_r31_2 < 2) {
            fn_1_A00(var_r31_2, &lbl_1_bss_14AC.unk148[var_r31_2 * 2], &lbl_1_bss_14AC.unk148[(var_r31_2 * 2) + 1]);
            temp_r0 = var_r31_2 * 2;
            lbl_1_bss_14AC.unk148[temp_r0].y = (f32) ((f64) lbl_1_bss_14AC.unk148[temp_r0].y + (3.0 + (0.1 * (f64) (lbl_1_bss_14AC.unk110 - 8))));
            temp_r0_2 = (var_r31_2 * 2) + 1;
            lbl_1_bss_14AC.unk148[temp_r0_2].y = (f32) ((f64) lbl_1_bss_14AC.unk148[temp_r0_2].y + (2.0 - (f64) (var_r31_2 * 4)));
            temp_r30_2 = &lbl_1_bss_14AC.unk3C[var_r31_2 + 4];
            temp_r30_2->unk10.z += (f32) ((var_r31_2 * 0x28) - 0x14);
            temp_r30_2->unk4.x -= lbl_1_bss_14AC.unk138[var_r31_2] * (f32) (3 - (var_r31_2 * 6));
            temp_r30_2->unk4.y += 6.0f * lbl_1_bss_14AC.unk138[var_r31_2];
            lbl_1_bss_14AC.unk138[var_r31_2] = (f32) ((f64) lbl_1_bss_14AC.unk138[var_r31_2] * 0.95);
            Hu3DModelScaleSet(lbl_1_bss_14AC.unk3C[var_r31_2 + 4].unk0, lbl_1_bss_14AC.unk138[var_r31_2], lbl_1_bss_14AC.unk138[var_r31_2], lbl_1_bss_14AC.unk138[var_r31_2]);
            temp_r0_3 = var_r31_2 + 2;
            lbl_1_bss_14AC.unk3C[temp_r0_3].unk4.y -= 20.0f;
            var_r31_2 += 1;
            goto loop_15;
        }
        return;
    }
    fn_1_D64();
}

void fn_1_3904(s32 player) {
    s32 temp_r0;

    lbl_1_bss_14AC.unk4[player].unkC &= 0x300;
    if ((s32) lbl_1_bss_14AC.unk4[player].unkC == 0x300) {
        lbl_1_bss_1EC0[player] = 0;
        if ((s32) lbl_1_bss_14AC.unk130 == 0) {
            lbl_1_bss_14AC.unk120[player] += 1;
            return;
        }
        if ((s32) lbl_1_bss_14AC.unk120[player] < 0x1D) {
            lbl_1_bss_14AC.unk120[player] += 1;
        }
    } else {
        temp_r0 = lbl_1_bss_1EC0[player];
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) lbl_1_bss_14AC.unk4[player].unkC == 0x100) {
                lbl_1_bss_1EC0[player] = 1;
            }
            if ((s32) lbl_1_bss_14AC.unk4[player].unkC == 0x200) {
                lbl_1_bss_1EC0[player] = 2;
                return;
            }
            return;
        case 1:
            if ((s32) lbl_1_bss_14AC.unk4[player].unkC == 0x200) {
                if ((s32) lbl_1_bss_14AC.unk130 == 0) {
                    lbl_1_bss_14AC.unk120[player] += 1;
                } else if ((s32) lbl_1_bss_14AC.unk120[player] < 0x1D) {
                    lbl_1_bss_14AC.unk120[player] += 1;
                }
            }
            lbl_1_bss_1EC0[player] = 0;
            return;
        case 2:
            if ((s32) lbl_1_bss_14AC.unk4[player].unkC == 0x100) {
                if ((s32) lbl_1_bss_14AC.unk130 == 0) {
                    lbl_1_bss_14AC.unk120[player] += 1;
                } else if ((s32) lbl_1_bss_14AC.unk120[player] < 0x1D) {
                    lbl_1_bss_14AC.unk120[player] += 1;
                }
            }
            lbl_1_bss_1EC0[player] = 0;
            break;
        }
    }
}

s32 fn_1_3BB0(s32 player) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M550Model *temp_r31;
    s32 var_r29;

    var_r29 = 0;
    if (((s32) lbl_1_bss_14AC.unk134 > 1) && (player != (s32) (lbl_1_bss_14AC.unk130 - 1))) {
        lbl_1_bss_14AC.unk104[(player + 1) - 1] = 5;
        lbl_1_bss_14AC.unk50[player].unk38 = 1;
        lbl_1_bss_14AC.unk50[player].unk3A = 3;
        lbl_1_bss_14AC.unk50[player].unk40 = 0.0f;
        lbl_1_bss_14AC.unk50[player].unk44 = 8.0f;
        lbl_1_bss_14AC.unk50[player].unk3C = 0x40000001;
        Hu3DModelObjMtxGet(lbl_1_bss_14AC.unk3C[player + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[player].unk2, 1, 0), sp20);
        Hu3DModelHookReset(lbl_1_bss_14AC.unk3C[player + 2].unk0);
        temp_r31 = &lbl_1_bss_14AC.unk3C[player + 4];
        Hu3DMtxRotGet(sp20, &sp8);
        sp14.x = sp20[0][3];
        sp14.y = sp20[1][3];
        sp14.z = sp20[2][3];
        Hu3DModelPosSetV(temp_r31->unk0, &sp14);
        Hu3DModelRotSetV(temp_r31->unk0, &sp8);
        Hu3DModelScaleSet(temp_r31->unk0, 1.0f, 1.0f, 1.0f);
        temp_r31->unk4.x = sp14.x;
        temp_r31->unk4.y = sp14.y;
        temp_r31->unk4.z = sp14.z;
        temp_r31->unk10.x = sp8.x;
        temp_r31->unk10.y = sp8.y;
        temp_r31->unk10.z = sp8.z;
        lbl_1_bss_14AC.unk134 = 3;
        var_r29 = 1;
        if (player != 0) {
            HuAudFXPlay(0x853);
        } else {
            HuAudFXPlay(0x854);
        }
    }
    return var_r29;
}

void fn_1_3DD8(s32 player) {
    M550Model *temp_r30;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    u32 temp_r0;

    temp_r30 = &lbl_1_bss_14AC.unk3C[player + 4];
    temp_r0 = lbl_1_bss_14AC.unk104[(player + 1) - 1];
    switch (temp_r0) {
    case 0:
        if ((fn_1_3BB0(player) == 0) && ((s32) lbl_1_bss_14AC.unk120[player] > (s32) lbl_1_bss_14AC.unk120[player + 2])) {
            temp_r0_2 = player + 2;
            lbl_1_bss_14AC.unk120[temp_r0_2] += 1;
            lbl_1_bss_14AC.unk50[player].unk38 = 1;
            lbl_1_bss_14AC.unk50[player].unk3A = 1;
            lbl_1_bss_14AC.unk50[player].unk40 = 0.0f;
            lbl_1_bss_14AC.unk50[player].unk44 = 4.0f;
            lbl_1_bss_14AC.unk50[player].unk3C = 0;
            lbl_1_bss_14AC.unk104[(player + 1) - 1] = 1;
            return;
        }
    default:
        return;
    case 1:
        if ((s16) lbl_1_bss_14AC.unk50[player].unk38 == 0) {
            lbl_1_bss_14AC.unk104[(player + 1) - 1] = 2;
            return;
        }
        break;
    case 2:
        if ((fn_1_3BB0(player) == 0) && (lbl_1_bss_14AC.unk50[player].unkC >= 8.0f)) {
            lbl_1_bss_14AC.unk104[(player + 1) - 1] = 3;
            Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
            if (player != 0) {
                HuAudFXPlay(0x84F);
                return;
            }
            HuAudFXPlay(0x850);
            return;
        }
        break;
    case 3:
        if (fn_1_3BB0(player) == 0) {
            if (lbl_1_bss_14AC.unk50[player].unkC >= 10.0f) {
                Hu3DMotionSpeedSet(temp_r30->unk0, 1.0f);
            }
            if (lbl_1_bss_14AC.unk50[player].unkC >= 14.0f) {
                fn_1_4898(player, lbl_1_bss_14AC.unk120[player + 2]);
                Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
                Hu3DMotionSpeedSet(temp_r30->unk0, 0.0f);
                if ((s32) lbl_1_bss_14AC.unk120[player] != (s32) lbl_1_bss_14AC.unk120[player + 2]) {
                    lbl_1_bss_14AC.unk50[player].unkC = 8.0f;
                    lbl_1_bss_14AC.unk104[(player + 1) - 1] = 2;
                    temp_r0_3 = player + 2;
                    lbl_1_bss_14AC.unk120[temp_r0_3] += 1;
                    return;
                }
                lbl_1_bss_14AC.unk50[player].unk38 = 1;
                lbl_1_bss_14AC.unk50[player].unk3A = 0;
                lbl_1_bss_14AC.unk50[player].unk40 = 0.0f;
                lbl_1_bss_14AC.unk50[player].unk44 = 6.0f;
                lbl_1_bss_14AC.unk50[player].unk3C = 0x40000001;
                lbl_1_bss_14AC.unk104[(player + 1) - 1] = 4;
                return;
            }
        }
        break;
    case 4:
        if ((s16) lbl_1_bss_14AC.unk50[player].unk38 == 0) {
            lbl_1_bss_14AC.unk104[(player + 1) - 1] = 0;
            return;
        }
        break;
    case 5:
        if ((s16) lbl_1_bss_14AC.unk50[player].unk38 == 0) {
            lbl_1_bss_14AC.unk104[(player + 1) - 1] = 6;
        }
        temp_r0_4 = player + 2;
        lbl_1_bss_14AC.unk3C[temp_r0_4].unk4.y -= 20.0f;
        return;
    case 6:
        temp_r0_5 = player + 2;
        lbl_1_bss_14AC.unk3C[temp_r0_5].unk4.y -= 20.0f;
        break;
    }
}


void fn_1_4494(s32 player) {
    M550Ai *temp_r4;
    M550Ai *temp_r4_2;
    s16 temp_r0;
    s32 var_r31;
    s32 var_r31_2;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u8 temp_r3;
    u8 temp_r3_3;

    memset(&lbl_1_bss_4[player], 0, 0x10);
    lbl_1_bss_4[player].unk0 = lbl_1_bss_14AC.unk4[player].unk4 - 1;
    var_r31 = 0;
    temp_r0 = lbl_1_bss_4[player].unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r31 = (rand8() % 5) + 0xD;
        break;
    case 1:
        temp_r3 = rand8();
        var_r31 = (temp_r3 % 4) + 9;
        break;
    case 2:
        temp_r4 = &lbl_1_bss_4[player];
        temp_r4->unkC += 1;
        temp_r3_3 = rand8();
        var_r31 = (temp_r3_3 % 4) + 7;
        break;
    case 3:
        var_r31_2 = 4;
        temp_r4_2 = &lbl_1_bss_4[player];
        temp_r4_2->unkC += 1;
        if ((s32) (lbl_1_bss_4[player].unkC % 5) == 0) {
            var_r31_2 = 3;
        }
        var_r31 = var_r31_2 + (rand8() % 3);
        break;
    }
    lbl_1_bss_4[player].unk8 = var_r31;
}

void fn_1_4688(s32 player) {
    M550Ai *temp_r4;
    M550Ai *temp_r4_2;
    M550Ai *temp_r4_3;
    s16 temp_r0;
    s32 var_r31;
    s32 var_r31_2;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u8 temp_r3;
    u8 temp_r3_3;

    temp_r4 = &lbl_1_bss_4[player];
    temp_r4->unk8 -= 1;
    if ((s32) lbl_1_bss_4[player].unk8 <= 0) {
        lbl_1_bss_14AC.unk4[player].unkC = 0x300;
        lbl_1_bss_14AC.unk4[player].unk8 = 0x300;
        var_r31 = 0;
        temp_r0 = lbl_1_bss_4[player].unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31 = (rand8() % 5) + 0xD;
            break;
        case 1:
            temp_r3 = rand8();
            var_r31 = (temp_r3 % 4) + 9;
            break;
        case 2:
            temp_r4_2 = &lbl_1_bss_4[player];
            temp_r4_2->unkC += 1;
            temp_r3_3 = rand8();
            var_r31 = (temp_r3_3 % 4) + 7;
            break;
        case 3:
            var_r31_2 = 4;
            temp_r4_3 = &lbl_1_bss_4[player];
            temp_r4_3->unkC += 1;
            if ((s32) (lbl_1_bss_4[player].unkC % 5) == 0) {
                var_r31_2 = 3;
            }
            var_r31 = var_r31_2 + (rand8() % 3);
            break;
        }
        lbl_1_bss_4[player].unk8 = var_r31;
    }
}

void fn_1_4898(s32 player, s32 count) {
    Hu3DModelAttrSet(lbl_1_bss_14AC.unk3C[((player ^ 1) * 0x1E) + (0x1D - (count - 1)) + 6].unk0, 1U);
    if (count > 0x13) {
        Hu3DMotionSpeedSet(lbl_1_bss_14AC.unk3C[((player ^ 1) * 0xB) + (0xA - (count - 0x14)) + 0x7E].unk0, 1.0f);
    }
    fn_1_49F0(player ^ 1, count - 1);
    if (count == 0x1E) {
        omVibrate(lbl_1_bss_14AC.unk4[player ^ 1].unk0, 0x32, 0xC, 0);
    }
}


void fn_1_49F0(s32 player, s32 slot) {
    Mtx sp38;
    Mtx sp8;
    M550Model *temp_r31;
    s32 var_r27;
    s32 var_r30;

    var_r30 = 0;
loop_3:
    if (var_r30 < 0x1E) {
        if ((s32) lbl_1_bss_1ECC[player][var_r30] != 0) {
            var_r30 += 1;
            goto loop_3;
        }
    }
    if (var_r30 == 0x1E) {
        var_r27 = -1;
    } else {
        var_r27 = var_r30;
    }
    if (var_r27 >= 0) {
        lbl_1_bss_1ECC[player][var_r27] = 1;
        Hu3DModelObjMtxGet(lbl_1_bss_14AC.unk3C[player + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[player].unk2, 1, 4), sp8);
        MTXTrans(sp38, lbl_1_data_250[slot].x, lbl_1_data_250[slot].y, lbl_1_data_250[slot].z);
        MTXConcat(sp8, sp38, sp38);
        temp_r31 = &lbl_1_bss_14AC.unk3C[(player * 0x1E) + var_r27 + 0x42];
        Hu3DModelAttrReset(temp_r31->unk0, 1U);
        Hu3DModelPosSet(temp_r31->unk0, sp38[0][3], sp38[1][3], sp38[2][3]);
        temp_r31->unk4.x = sp38[0][3];
        temp_r31->unk4.y = sp38[1][3];
        temp_r31->unk4.z = sp38[2][3];
        Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
        Hu3DMotionSpeedSet(temp_r31->unk0, 1.0f);
        if (player != 0) {
            HuAudFXPlay(0x851);
            return;
        }
        HuAudFXPlay(0x852);
    }
}

void fn_1_4C00(void) {
    M550Model *temp_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_14:
    if (var_r31 < 2) {
        var_r29 = 0;
        var_r30 = 0;
loop_7:
        if (var_r30 < 0x1E) {
            if ((s32) lbl_1_bss_1ECC[var_r31][var_r30] != 0) {
                temp_r28 = &lbl_1_bss_14AC.unk3C[(var_r31 * 0x1E) + var_r30 + 0x42];
                if (Hu3DMotionTimeGet(temp_r28->unk0) >= 18.0f) {
                    lbl_1_bss_1ECC[var_r31][var_r30] = 0;
                    Hu3DModelAttrSet(temp_r28->unk0, 1U);
                }
                var_r29 += 1;
            }
            var_r30 += 1;
            goto loop_7;
        }
        if ((var_r29 == 0) && ((s32) lbl_1_bss_14AC.unk120[(var_r31 ^ 1) + 2] == 0x1E) && (MgSeqModeGet() == 5) && ((s32) lbl_1_bss_14AC.unk104[((var_r31 ^ 1) + 1) - 1] == 0)) {
            MgSeqModeNext();
            HuAudSStreamFadeOut(lbl_1_data_3B8, 0x3E8);
        }
        var_r31 += 1;
        goto loop_14;
    }
}

void fn_1_4D94(void) {
    M550Model *temp_r31;

    temp_r31 = &lbl_1_bss_14AC.unk3C[0x94];
    Hu3DModelAttrReset(lbl_1_bss_14AC.unk3C[0x94].unk0, 1U);
    Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
    Hu3DMotionSpeedSet(temp_r31->unk0, 1.5f);
    Hu3DModelPosSet(temp_r31->unk0, 0.0f, 20.0f, 0.0f);
    temp_r31->unk4.x = 0.0f;
    temp_r31->unk4.y = 20.0f;
    temp_r31->unk4.z = 0.0f;
    Hu3DModelScaleSet(temp_r31->unk0, 0.3f, 0.3f, 0.3f);
    fn_1_6D8C();
}




void ObjectSetup(void) {
    s16 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0xB7) {
        lbl_1_bss_A8[var_r31].unk0 = -1;
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_4E8C(&lbl_1_bss_14AC, lbl_1_bss_A8, lbl_1_data_8);
    lbl_1_bss_14AC.unk0 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_14AC.unk0);
    omAddObjEx(lbl_1_bss_14AC.unk0, 0x7FDA, 0U, 0U, -1, omOutView);
    omAddObjEx(lbl_1_bss_14AC.unk0, 0x7FDA, 0U, 0U, -1, fn_1_5BD8);
    MgSeqCreate(&lbl_1_data_1FC);
}

void fn_1_198(s16 arg0, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    s16 sp8;
    s16 temp_r3;

    sp8 = arg0;
    fn_1_50D8(2);
    fn_1_58F4(&lbl_1_data_F8[lbl_1_bss_14AC.unk4[0].unk0], &lbl_1_data_F8[lbl_1_bss_14AC.unk4[1].unk0]);
    fn_1_5918(lbl_1_bss_24[0], lbl_1_bss_24[1]);
    fn_1_593C();
    fn_1_6094();
    omAddObjEx(lbl_1_bss_14AC.unk0, 0x7FDA, 0U, 0U, -1, fn_1_61E8);
    fn_1_131C();
    Center.x = 0.0f;
    Center.y = 1000.0f;
    Center.z = 100.0f;
    CRot.x = -90.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 4000.0f;
    lbl_1_bss_38[1].center.x = 0.0f;
    lbl_1_bss_38[1].center.y = 1150.0f;
    lbl_1_bss_38[1].center.z = 0.0f;
    lbl_1_bss_38[1].rot.x = -10.0f;
    lbl_1_bss_38[1].rot.y = 0.0f;
    lbl_1_bss_38[1].rot.z = 0.0f;
    lbl_1_bss_38[1].zoom = 700.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 100000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, 0x1E0U);
    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DGLightStaticSet(temp_r3, 1);
    omAddObjEx(lbl_1_bss_14AC.unk0, 0x7FDA, 0U, 0U, -1, fn_1_914);
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
    lbl_1_bss_14AC.unk50[0].unk0 = 0;
    lbl_1_bss_14AC.unk50[0].unk4 = 1.0f;
    lbl_1_bss_14AC.unk50[0].unkC = 0.0f;
    lbl_1_bss_14AC.unk50[0].unk18 = 0x40000001;
    lbl_1_bss_14AC.unk50[1].unk0 = 0;
    lbl_1_bss_14AC.unk50[1].unk4 = 1.0f;
    lbl_1_bss_14AC.unk50[1].unkC = 0.0f;
    lbl_1_bss_14AC.unk50[1].unk18 = 0x40000001;
    Hu3DFogClear();
    MgSeqModeDelaySet((s16) (sp8 + 1), -1);
    omAddObjEx(lbl_1_bss_14AC.unk0, 0x7FDA, 0U, 0U, -1, fn_1_65AC);
    MgSeqModeNext();
}

void fn_1_6B4(s16 mode, s16 frameNo) {
    lbl_1_data_224[lbl_1_bss_14AC.unk100]();
}

void fn_1_6F8(s16 arg0, s16 frameNo) {
    s16 sp8;

    sp8 = arg0;
    lbl_1_bss_14AC.unk100 = 0;
    lbl_1_bss_14AC.unk104[0] = 0;
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    fn_1_D64();
}

void fn_1_750(s16 mode, s16 frameNo) {
    lbl_1_data_230[lbl_1_bss_14AC.unk100]();
}

void fn_1_794(s16 arg0, s16 frameNo) {
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
    if ((s32) lbl_1_bss_14AC.unk100 != 0) {
        fn_1_2618();
    } else {
        fn_1_2364();
    }
    MgSeqModeDelaySet((s16) (arg0 + 1), -1);
}

void fn_1_7FC(s16 mode, s16 frameNo) {
    lbl_1_data_23C[lbl_1_bss_14AC.unk100]();
}

void fn_1_840(s16 mode, s16 frameNo) {
    if ((s32) lbl_1_bss_14AC.unk100 != 0) {
        CZoom += 5.0f;
    }
    fn_1_D64();
    MgSeqModeNext();
}

void fn_1_8A0(s16 mode, s16 frameNo) {
    if ((s32) lbl_1_bss_14AC.unk100 != 0) {
        CZoom += 5.0f;
    }
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
    fn_1_D64();
}

void fn_1_910(s16 mode, s16 frameNo) {

}

void fn_1_914(omObjData *obj) {
    M550Model *var_r31;
    s32 var_r30;

    var_r31 = lbl_1_bss_A8;
    var_r30 = 0;
loop_4:
    if (var_r30 < 0xB7) {
        if ((s16) var_r31->unk0 >= 0) {
            Hu3DModelPosSetV(var_r31->unk0, &var_r31->unk4);
            Hu3DModelRotSetV(var_r31->unk0, &var_r31->unk10);
        }
        var_r30 += 1;
        var_r31++;
        goto loop_4;
    }
}

void fn_1_984(s32 model, f32 alpha) {
    HSFMATERIAL *var_r30;
    HU3DMODEL *temp_r31;
    s32 var_r29;

    temp_r31 = &Hu3DData[lbl_1_bss_14AC.unk3C[model].unk0];
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

void fn_1_A00(s32 player, Vec *pos, Vec *rot) {
    M550Model *temp_r31;
    M550Model *temp_r31_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r29;
    s32 var_r29_2;

    temp_f31 = pos->x;
    temp_f30 = pos->y;
    temp_f29 = pos->z;
    var_r29 = 0;
loop_4:
    if (var_r29 < 0x1E) {
        temp_r31 = &lbl_1_bss_A8[(player * 0x1E) + var_r29 + 6];
        if ((s16) temp_r31->unk0 != 0) {
            Hu3DModelPosSet(temp_r31->unk0, temp_f31, temp_f30, temp_f29);
            temp_r31->unk4.x = temp_f31;
            temp_r31->unk4.y = temp_f30;
            temp_r31->unk4.z = temp_f29;
            temp_r31->unk10.x = rot->x;
            temp_r31->unk10.y = rot->y;
            temp_r31->unk10.z = rot->z;
        }
        var_r29 += 1;
        goto loop_4;
    }
    var_r29_2 = 0;
loop_9:
    if (var_r29_2 < 0xB) {
        temp_r31_2 = &lbl_1_bss_A8[(player * 0xB) + var_r29_2 + 0x7E];
        if ((s16) temp_r31_2->unk0 != 0) {
            Hu3DModelPosSet(temp_r31_2->unk0, temp_f31, temp_f30, temp_f29);
            temp_r31_2->unk4.x = temp_f31;
            temp_r31_2->unk4.y = temp_f30;
            temp_r31_2->unk4.z = temp_f29;
            temp_r31_2->unk10.x = rot->x;
            temp_r31_2->unk10.y = rot->y;
            temp_r31_2->unk10.z = rot->z;
        }
        var_r29_2 += 1;
        goto loop_9;
    }
}


void fn_1_D64(void) {
    Mtx sp20;
    Mtx sp50;
    Vec sp14;
    Vec sp8;
    M550Model *temp_r31;
    M550Model *temp_r31_2;
    f32 temp_f29;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30;

    var_r30 = 0;
loop_12:
    if (var_r30 < 2) {
        MTXIdentity(sp50);
        Hu3DModelObjPosGet(lbl_1_bss_14AC.unk3C[var_r30 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r30].unk2, 1, 4), &sp8);
        Hu3DModelObjMtxGet(lbl_1_bss_14AC.unk3C[var_r30 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r30].unk2, 1, 4), sp20);
        MTXConcat(sp20, sp50, sp20);
        Hu3DMtxRotGet(sp20, &sp14);
        temp_f29 = sp8.x;
        var_r29 = 0;
loop_5:
        if (var_r29 < 0x1E) {
            temp_r31 = &lbl_1_bss_A8[(var_r30 * 0x1E) + var_r29 + 6];
            if ((s16) temp_r31->unk0 != 0) {
                Hu3DModelPosSet(temp_r31->unk0, temp_f29, sp8.y, sp8.z);
                temp_r31->unk4.x = temp_f29;
                temp_r31->unk4.y = sp8.y;
                temp_r31->unk4.z = sp8.z;
                temp_r31->unk10.x = sp14.x;
                temp_r31->unk10.y = sp14.y;
                temp_r31->unk10.z = sp14.z;
            }
            var_r29 += 1;
            goto loop_5;
        }
        var_r29_2 = 0;
loop_10:
        if (var_r29_2 < 0xB) {
            temp_r31_2 = &lbl_1_bss_A8[(var_r30 * 0xB) + var_r29_2 + 0x7E];
            if ((s16) temp_r31_2->unk0 != 0) {
                Hu3DModelPosSet(temp_r31_2->unk0, temp_f29, sp8.y, sp8.z);
                temp_r31_2->unk4.x = temp_f29;
                temp_r31_2->unk4.y = sp8.y;
                temp_r31_2->unk4.z = sp8.z;
                temp_r31_2->unk10.x = sp14.x;
                temp_r31_2->unk10.y = sp14.y;
                temp_r31_2->unk10.z = sp14.z;
            }
            var_r29_2 += 1;
            goto loop_10;
        }
        var_r30 += 1;
        goto loop_12;
    }
}

void fn_1_F7C(void) {
    Mtx sp50;
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        MTXIdentity(sp20);
        Hu3DModelObjPosGet(lbl_1_bss_14AC.unk3C[var_r31 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r31].unk2, 1, 4), &sp14);
        Hu3DModelObjMtxGet(lbl_1_bss_14AC.unk3C[var_r31 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r31].unk2, 1, 4), sp50);
        MTXConcat(sp50, sp20, sp50);
        Hu3DMtxRotGet(sp50, &sp8);
        temp_r0 = var_r31 * 2;
        lbl_1_bss_14AC.unk148[temp_r0].x = sp14.x;
        lbl_1_bss_14AC.unk148[temp_r0].y = sp14.y;
        lbl_1_bss_14AC.unk148[temp_r0].z = sp14.z;
        temp_r0_2 = (var_r31 * 2) + 1;
        lbl_1_bss_14AC.unk148[temp_r0_2].x = sp8.x;
        lbl_1_bss_14AC.unk148[temp_r0_2].y = sp8.y;
        lbl_1_bss_14AC.unk148[temp_r0_2].z = sp8.z;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_10BC(s32 player) {
    Vec sp8;
    M550Model *temp_r31;

    Hu3DModelObjPosGet(lbl_1_bss_14AC.unk3C[player + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[player].unk2, 1, 4), &sp8);
    temp_r31 = &lbl_1_bss_A8[player + 0x95];
    Hu3DModelAttrReset(temp_r31->unk0, 1U);
    Hu3DMotionSpeedSet(temp_r31->unk0, 3.0f);
    sp8.z += 80.0f;
    sp8.x += (f32) (0x1E - (player * 0x3C));
    sp8.y += 20.0f;
    temp_r31->unk4.x = sp8.x;
    temp_r31->unk4.y = sp8.y;
    temp_r31->unk4.z = sp8.z;
    Hu3DModelPosSetV(temp_r31->unk0, &temp_r31->unk4);
}


void fn_1_131C(void) {
    M550Model *temp_r31;
    M550Model *temp_r31_2;
    M550Model *temp_r31_3;
    M550Model *temp_r31_4;
    M550Model *temp_r31_5;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;

    var_r29 = 0;
loop_11:
    if (var_r29 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 0x1E) {
            temp_r31 = &lbl_1_bss_A8[(var_r29 * 0x1E) + var_r30 + 6];
            temp_r31->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[var_r30 + 2], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
            var_r30 += 1;
            goto loop_3;
        }
        var_r30_2 = 0;
loop_6:
        if (var_r30_2 < 0x1E) {
            temp_r31_2 = &lbl_1_bss_A8[(var_r29 * 0x1E) + var_r30_2 + 0x42];
            temp_r31_2->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[0x20], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
            Hu3DMotionTimeSet(temp_r31_2->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r31_2->unk0, 1.0f);
            Hu3DModelAttrSet(temp_r31_2->unk0, 1U);
            Hu3DModelLayerSet(temp_r31_2->unk0, 3);
            var_r30_2 += 1;
            goto loop_6;
        }
        var_r30_3 = 0;
loop_9:
        if (var_r30_3 < 0xB) {
            temp_r31_3 = &lbl_1_bss_A8[(var_r29 * 0xB) + var_r30_3 + 0x7E];
            temp_r31_3->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[var_r30_3 + 0x21], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
            Hu3DMotionTimeSet(temp_r31_3->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r31_3->unk0, 0.0f);
            Hu3DModelLayerSet(temp_r31_3->unk0, 2);
            var_r30_3 += 1;
            goto loop_9;
        }
        temp_r31_4 = &lbl_1_bss_A8[var_r29 + 4];
        temp_r31_4->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[0x2C], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
        Hu3DMotionTimeSet(temp_r31_4->unk0, 0.0f);
        Hu3DModelLayerSet(temp_r31_4->unk0, 5);
        Hu3DMotionSpeedSet(temp_r31_4->unk0, 0.0f);
        Hu3DModelHookSet(lbl_1_bss_A8[var_r29 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r29].unk2, 1, 0), temp_r31_4->unk0);
        if (lbl_1_bss_14AC.unk4[var_r29].unk2 == 5 && !Mp5CharHasMotions(5)) {
            Hu3DModelScaleSet(temp_r31_4->unk0, 2.5f, 2.5f, 2.5f);
        }
        temp_r31_5 = &lbl_1_bss_A8[var_r29 + 0x95];
        temp_r31_5->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[0x2E], MEMORY_DEFAULT_NUM, HEAP_DATA));
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
        Hu3DMotionTimeSet(temp_r31_5->unk0, 0.0f);
        Hu3DModelLayerSet(temp_r31_5->unk0, 4);
        Hu3DMotionSpeedSet(temp_r31_5->unk0, 0.0f);
        Hu3DModelAttrSet(temp_r31_5->unk0, 1U);
        var_r29 += 1;
        goto loop_11;
    }
    lbl_1_bss_A8[0x94].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_8[0x2D], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_A8[0x94].unk0, 1U);
    Hu3DModelPosSet(lbl_1_bss_A8[0x94].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_A8[0x94].unk0, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_A8[0x94].unk4.x = 0.0f;
    lbl_1_bss_A8[0x94].unk4.y = 0.0f;
    lbl_1_bss_A8[0x94].unk4.z = 0.0f;
    lbl_1_bss_A8[0x94].unk10.x = 0.0f;
    lbl_1_bss_A8[0x94].unk10.y = 0.0f;
    lbl_1_bss_A8[0x94].unk10.z = 0.0f;
    Hu3DModelCameraSet(lbl_1_bss_A8[0x94].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_A8[0x94].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_A8[0x94].unk0, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_A8[0x94].unk0, 1U);
    Hu3DMotionTimeSet(lbl_1_bss_A8[0x94].unk0, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_A8[0x94].unk0, 1.0f);
    Hu3DModelLayerSet(lbl_1_bss_A8[0x94].unk0, 4);
    Hu3DModelAttrSet(lbl_1_bss_A8[0x94].unk0, 1U);
}

void fn_1_4E8C(M550Work *work, M550Model *models, s32 *dataNums) {
    s32 *sp10;
    M550Model *spC;
    M550Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_1FC0 = sp8;
    memset((M550Ai *) lbl_1_bss_1FC0, 0, 0xA14);
    lbl_1_bss_1FC0->unk3C = spC;
    lbl_1_bss_1FC0->unkF8 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_1FC0->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_1FC0->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_1FC0->unk4[var_r31_2].unk0].character;
        lbl_1_bss_1FC0->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_1FC0->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_1FC0->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_1FC0->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_1FC0->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_50D8(s16 arg) {
    s32 sp18[3];
    s32 spC[3];
    s16 sp8;
    M550Model *temp_r31;
    M550Model *temp_r31_2;
    M550Model *temp_r31_3;
    M550Model *var_r31;
    M550Model *var_r31_2;
    M550Model *var_r31_3;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 var_r27;
    s16 var_r29;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;

    var_r29 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = arg;
    lbl_1_bss_1FC0->unkFC = arg;
    var_r27 = 0;
loop_2:
    if (var_r27 < 2) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[var_r27], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_1FC0->unk3C[var_r27].unk0 = temp_r3;
        var_r29 = temp_r3;
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelCameraSet(var_r29, 1U);
        Hu3DModelPosSetV(var_r29, &lbl_1_data_3D8[var_r27]);
        Hu3DModelRotSet(var_r29, 0.0f, -22.5f, 0.0f);
        lbl_1_bss_1FC0->unk3C[var_r27].unk4.x = lbl_1_data_3D8[var_r27].x;
        lbl_1_bss_1FC0->unk3C[var_r27].unk4.y = lbl_1_data_3D8[var_r27].y;
        lbl_1_bss_1FC0->unk3C[var_r27].unk4.z = lbl_1_data_3D8[var_r27].z;
        lbl_1_bss_1FC0->unk3C[var_r27].unk10.x = 0.0f;
        lbl_1_bss_1FC0->unk3C[var_r27].unk10.y = 22.5f;
        lbl_1_bss_1FC0->unk3C[var_r27].unk10.z = 0.0f;
        Hu3DMotionTimeSet(var_r29, 0.0f);
        Hu3DMotionSpeedSet(var_r29, 0.25f);
        Hu3DModelAttrSet(var_r29, 0x40000001U);
        Hu3DModelLayerSet(var_r29, 1);
        Hu3DModelAttrReset(var_r29, 1U);
        var_r27 += 1;
        goto loop_2;
    }
    var_r30 = 0;
loop_11:
    if (var_r30 < 3) {
        var_r31 = &lbl_1_bss_1FC0->unk3C[(var_r30 * 3) + 0x97];
        var_r28 = 0;
loop_9:
        if (var_r28 < 3) {
            if (var_r28 == 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[var_r30 + 0x2F], MEMORY_DEFAULT_NUM, HEAP_DATA));
                var_r31->unk0 = temp_r3_2;
                var_r29 = temp_r3_2;
            } else {
                var_r31->unk0 = Hu3DModelLink(var_r29);
            }
            Hu3DModelAttrSet(var_r31->unk0, 1U);
            Hu3DMotionTimeSet(var_r31->unk0, 50.0f);
            Hu3DMotionSpeedSet(var_r31->unk0, 0.5f);
            Hu3DModelCameraSet(var_r31->unk0, 1U);
            Hu3DModelLayerSet(var_r31->unk0, 1);
            var_r28 += 1;
            var_r31++;
            goto loop_9;
        }
        var_r30 += 1;
        goto loop_11;
    }
    var_r30_2 = 0;
loop_20:
    if (var_r30_2 < 2) {
        temp_r31 = &lbl_1_bss_1FC0->unk3C[var_r30_2 + 0xA1];
        temp_r31->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[var_r30_2 + 0x33], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31->unk0, 0.5f);
        Hu3DModelCameraSet(temp_r31->unk0, 1U);
        Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
        Hu3DModelLayerSet(temp_r31->unk0, 7);
        var_r31_2 = &lbl_1_bss_1FC0->unk3C[(var_r30_2 * 2) + 0xA3];
        var_r28_2 = 0;
loop_18:
        if (var_r28_2 < 2) {
            if (var_r28_2 == 0) {
                temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[var_r30_2 + 0x35], MEMORY_DEFAULT_NUM, HEAP_DATA));
                var_r31_2->unk0 = temp_r3_3;
                var_r29 = temp_r3_3;
            } else {
                var_r31_2->unk0 = Hu3DModelLink(var_r29);
            }
            Hu3DModelAttrSet(var_r31_2->unk0, 1U);
            Hu3DMotionSpeedSet(var_r31_2->unk0, 0.5f);
            Hu3DModelCameraSet(var_r31_2->unk0, 1U);
            Hu3DMotionTimeSet(var_r31_2->unk0, 0.0f);
            Hu3DModelAttrSet(var_r31_2->unk0, 0x40000001U);
            Hu3DModelLayerSet(var_r31_2->unk0, 3);
            var_r28_2 += 1;
            var_r31_2++;
            goto loop_18;
        }
        var_r30_2 += 1;
        goto loop_20;
    }
    var_r30_3 = 0;
loop_26:
    if (var_r30_3 < 3) {
        sp18[0] = lbl_1_rodata_158[0];
        sp18[1] = lbl_1_rodata_158[1];
        sp18[2] = lbl_1_rodata_158[2];
        spC[0] = lbl_1_rodata_164[0];
        spC[1] = lbl_1_rodata_164[1];
        spC[2] = lbl_1_rodata_164[2];
        temp_r31_2 = &lbl_1_bss_1FC0->unk3C[sp18[var_r30_3]];
        temp_r31_2->unk0 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[spC[var_r30_3]], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r31_2->unk0, 1U);
        Hu3DModelCameraSet(temp_r31_2->unk0, 1U);
        if (var_r30_3 < 2) {
            Hu3DModelLayerSet(temp_r31_2->unk0, 4);
        } else {
            Hu3DModelLayerSet(temp_r31_2->unk0, 1);
        }
        var_r30_3 += 1;
        goto loop_26;
    }
    var_r30_4 = 0;
loop_32:
    if (var_r30_4 < 0xA) {
        temp_r31_3 = &lbl_1_bss_1FC0->unk3C[var_r30_4 + 0xA9];
        if (var_r30_4 == 0) {
            temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[0x39], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31_3->unk0 = temp_r3_4;
            var_r29 = temp_r3_4;
        } else {
            temp_r31_3->unk0 = Hu3DModelLink(var_r29);
        }
        Hu3DModelAttrSet(temp_r31_3->unk0, 1U);
        Hu3DModelCameraSet(temp_r31_3->unk0, 1U);
        Hu3DModelLayerSet(temp_r31_3->unk0, 4);
        var_r30_4 += 1;
        goto loop_32;
    }
    var_r30_5 = 0;
loop_41:
    if (var_r30_5 < 2) {
        var_r31_3 = &lbl_1_bss_1FC0->unk3C[(var_r30_5 * 2) + 0xB3];
        var_r28_3 = 0;
loop_39:
        if (var_r28_3 < 2) {
            Hu3DModelAttrSet(var_r31_3->unk0, 1U);
            if (var_r28_3 == 0) {
                temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1FC0->unkF8[var_r30_5 + 0x3A], MEMORY_DEFAULT_NUM, HEAP_DATA));
                var_r31_3->unk0 = temp_r3_5;
                var_r29 = temp_r3_5;
                lbl_1_data_420[var_r30_5] = Hu3DJointMotion(var_r31_3->unk0, HuDataSelHeapReadNum(lbl_1_data_0[var_r30_5], MEMORY_DEFAULT_NUM, HEAP_DATA));
                Hu3DModelScaleSet(var_r31_3->unk0, 2.2f, 2.2f, 2.2f);
            } else {
                var_r31_3->unk0 = Hu3DModelLink(var_r29);
                Hu3DModelScaleSet(var_r31_3->unk0, 1.0f, 1.0f, 1.0f);
            }
            Hu3DMotionSet(var_r31_3->unk0, lbl_1_data_420[var_r30_5]);
            Hu3DMotionSpeedSet(var_r31_3->unk0, 1.0f);
            Hu3DModelAttrSet(var_r31_3->unk0, 0x40000001U);
            Hu3DModelCameraSet(var_r31_3->unk0, 1U);
            Hu3DModelLayerSet(var_r31_3->unk0, 1);
            var_r28_3 += 1;
            var_r31_3++;
            goto loop_39;
        }
        var_r30_5 += 1;
        goto loop_41;
    }
}

void fn_1_58F4(M550Char *chr0, M550Char *chr1) {
    lbl_1_bss_1FC0->unk40[0] = chr0;
    lbl_1_bss_1FC0->unk40[1] = chr1;
}

void fn_1_5918(s16 *mot0, s16 *mot1) {
    lbl_1_bss_1FC0->unk48[0] = mot0;
    lbl_1_bss_1FC0->unk48[1] = mot1;
}

void fn_1_593C(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_1FC0->unk3C[var_r31 + 0x2].unk0 = CharModelCreate(lbl_1_bss_1FC0->unk4[var_r31].unk2, 1);
        Hu3DModelPosSet(lbl_1_bss_1FC0->unk3C[var_r31 + 0x2].unk0, (f32) ((var_r31 * 0x1A4) - 0xD2), 1000.0f, 0.0f);
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk4.x = (f32) ((var_r31 * 0x1A4) - 0xD2);
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk4.y = 1000.0f;
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk4.z = 0.0f;
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk10.x = 0.0f;
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk10.y = 90.0f + (f32) (var_r31 * 0xB4);
        lbl_1_bss_1FC0->unk3C[var_r31 + 2].unk10.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_1FC0->unk3C[var_r31 + 0x2].unk0, 0x40000001U);
        Hu3DModelCameraSet(lbl_1_bss_1FC0->unk3C[var_r31 + 0x2].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_1FC0->unk3C[var_r31 + 0x2].unk0, 4);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_5BD8(omObjData *obj) {
    s32 var_r31;
    s8 var_r27;
    s8 var_r28;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_17:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_1FC0->unk4[var_r31].unk4 != 0) {
            memset((M550Ai *) &lbl_1_bss_1FC0->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_1FC0->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk10;
            }
            lbl_1_bss_1FC0->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_1FC0->unk4[var_r31].unk11 = (s8) (u8) HuPadStkY[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk11 >= 0) {
                var_r28 = (s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk11;
            } else {
                var_r28 = -(s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk11;
            }
            if (var_r28 < 0xA) {
                var_r27 = 0;
            } else {
                var_r27 = (s8) (u8) lbl_1_bss_1FC0->unk4[var_r31].unk11;
            }
            lbl_1_bss_1FC0->unk4[var_r31].unk11 = var_r27;
            lbl_1_bss_1FC0->unk4[var_r31].unk14 = (s8) (u8) HuPadSubStkX[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkY[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk16 = HuPadTrigL[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk17 = HuPadTrigR[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk18 = HuPadDStk[lbl_1_bss_1FC0->unk4[var_r31].unk6];
            lbl_1_bss_1FC0->unk4[var_r31].unk19 = HuPadDStkRep[lbl_1_bss_1FC0->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_17;
    }
}

void fn_1_6094(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 5) {
            lbl_1_bss_1FC0->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_1FC0->unk4[var_r31].unk2, lbl_1_bss_1FC0->unk40[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_1FC0->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_1FC0->unk50[var_r31_2].unk4 = 1.0f;
        lbl_1_bss_1FC0->unk50[var_r31_2].unk8 = 1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

void fn_1_61E8(omObjData *obj) {
    M550Anim *temp_r31;
    s16 temp_r0;
    s16 temp_r0_4;
    s16 temp_r0_5;
    s16 var_r29;
    u32 temp_r0_2;
    u32 temp_r0_3;

    var_r29 = 0;
loop_26:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_1FC0->unk50[var_r29];
        temp_r0 = var_r29 + 2;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, lbl_1_bss_1FC0->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r0_2 = temp_r31->unk20;
            temp_r31->unk20 = ~(temp_r0_2 | temp_r0_2);
            temp_r0_3 = temp_r31->unk18 & temp_r31->unk20;
            temp_r31->unk18 = temp_r0_3;
            temp_r31->unk1C = temp_r0_3;
            temp_r31->unk20 = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r0_4 = temp_r31->unk38;
        switch (temp_r0_4) {                        /* irregular */
        case 0:
            break;
        case 1:
            Hu3DMotionShiftSet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0, lbl_1_bss_1FC0->unk48[var_r29][temp_r31->unk3A], temp_r31->unk40, temp_r31->unk44, temp_r31->unk3C);
            temp_r31->unk4C = Hu3DMotionShiftMaxTimeGet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0);
            temp_r31->unk38 = 2;
            break;
        case 2:
            temp_r31->unk40 -= 1.0f;
            if (temp_r31->unk40 <= 0.0f) {
                temp_r31->unk38 = 3;
            }
            break;
        case 3:
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0);
            temp_r31->unk10 = temp_r31->unkC;
            temp_r31->unk38 = 0;
            temp_r0_5 = temp_r31->unk3A;
            temp_r31->unk2 = temp_r0_5;
            temp_r31->unk0 = temp_r0_5;
            break;
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_1FC0->unk3C[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        temp_r31->unk24 = Hu3DMotionEndCheck(lbl_1_bss_1FC0->unk3C[temp_r0].unk0);
        if (((s32) temp_r31->unk24 != 0) && ((s16) temp_r31->unk28 != 0)) {
            temp_r31->unk24 = 0;
            temp_r31->unk28 = 0;
            temp_r31->unk0 = temp_r31->unk2A;
            temp_r31->unkC = temp_r31->unk2C;
            temp_r31->unk18 = temp_r31->unk30;
            temp_r31->unk20 = temp_r31->unk34;
        }
        var_r29 += 1;
        goto loop_26;
    }
}

void fn_1_65AC(omObjData *obj) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 7) {
        lbl_1_data_424[var_r31]();
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_6600(void) {
    s32 sp44[5];
    f32 sp30[5];
    f32 sp1C[5];
    f32 sp8[5];
    M550Model *temp_r30;
    M550Prop *temp_r31;
    s32 temp_r4;
    s32 var_r28;
    s32 var_r29;

    sp44[0] = lbl_1_rodata_1A0[0];
    sp44[1] = lbl_1_rodata_1A0[1];
    sp44[2] = lbl_1_rodata_1A0[2];
    sp44[3] = lbl_1_rodata_1A0[3];
    sp44[4] = lbl_1_rodata_1A0[4];
    sp30[0] = lbl_1_rodata_1B4[0];
    sp30[1] = lbl_1_rodata_1B4[1];
    sp30[2] = lbl_1_rodata_1B4[2];
    sp30[3] = lbl_1_rodata_1B4[3];
    sp30[4] = lbl_1_rodata_1B4[4];
    sp1C[0] = lbl_1_rodata_1C8[0];
    sp1C[1] = lbl_1_rodata_1C8[1];
    sp1C[2] = lbl_1_rodata_1C8[2];
    sp1C[3] = lbl_1_rodata_1C8[3];
    sp1C[4] = lbl_1_rodata_1C8[4];
    sp8[0] = lbl_1_rodata_1DC[0];
    sp8[1] = lbl_1_rodata_1DC[1];
    sp8[2] = lbl_1_rodata_1DC[2];
    sp8[3] = lbl_1_rodata_1DC[3];
    sp8[4] = lbl_1_rodata_1DC[4];
    var_r29 = 0;
loop_23:
    if (var_r29 < 5) {
        temp_r31 = &lbl_1_bss_1FC0->unk178[var_r29];
        temp_r30 = &lbl_1_bss_1FC0->unk3C[sp44[var_r29]];
        if ((s32) temp_r31->unk0 == 0) {
            temp_r31->unk0 = 1;
            temp_r31->unk4 = 0;
            temp_r31->unk8 = 0;
            temp_r31->unkC = 0;
            temp_r31->unk2C = sp30[var_r29];
            temp_r31->unk30 = sp1C[var_r29];
            temp_r31->unk34 = (f32) (var_r29 * 0x2D);
            temp_r31->unk38 = sp8[var_r29];
            temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.z = (f32) ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
            temp_r30->unk4.y = (f32) ((f64) (1000.0f - (f32) (var_r29 * 0xC8)) + (200.0 * sin((3.141592653589793 * (f64) temp_r31->unk34) / 180.0)));
            Hu3DModelAttrReset(temp_r30->unk0, 1U);
            Hu3DMotionTimeSet(temp_r30->unk0, 50.0f);
            Hu3DMotionSpeedSet(temp_r30->unk0, 0.5f);
            Hu3DModelPosSetV(temp_r30->unk0, &temp_r30->unk4);
            if (var_r29 == 3) {
                Hu3DModelScaleSet(temp_r30->unk0, 0.75f, 0.75f, 0.75f);
            } else if (var_r29 == 4) {
                Hu3DModelScaleSet(temp_r30->unk0, 1.8f, 1.8f, 1.8f);
            } else {
                Hu3DModelScaleSet(temp_r30->unk0, 0.9f, 0.9f, 0.9f);
            }
        }
        var_r28 = 0;
loop_21:
        if (var_r28 < 3) {
            temp_r4 = (var_r28 * 4) + 4;
            (&temp_r31->unk4)[var_r28] += 1;
            switch (var_r28) {                      /* irregular */
            case 0:
                if ((s32) (&temp_r31->unk4)[var_r28] >= 0x10) {
                    (&temp_r31->unk4)[var_r28] = 0;
                    temp_r31->unk2C = (f32) ((f64) temp_r31->unk2C + 0.001);
                }
                break;
            case 1:
                if ((s32) (&temp_r31->unk4)[var_r28] >= 0x64) {
                    (&temp_r31->unk4)[var_r28] = 0;
                    Hu3DMotionTimeSet(temp_r30->unk0, 50.0f);
                }
                break;
            case 2:
                if ((s32) (&temp_r31->unk4)[var_r28] >= 4) {
                    (&temp_r31->unk4)[var_r28] = 0;
                    temp_r31->unk34 += 1.0f;
                }
                break;
            }
            var_r28 += 1;
            goto loop_21;
        }
        temp_r30->unk4.x = (f32) ((f64) temp_r31->unk30 * sin((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
        temp_r30->unk4.z = (f32) ((f64) temp_r31->unk30 * cos((3.141592653589793 * (f64) temp_r31->unk2C) / 180.0));
        temp_r30->unk4.y = (f32) ((f64) (1000.0f + temp_r31->unk38) + (200.0 * sin((3.141592653589793 * (f64) temp_r31->unk34) / 180.0)));
        var_r29 += 1;
        goto loop_23;
    }
}

void fn_1_6B6C(void) {
    s32 sp8[4];
    M550Model *temp_r31;
    M550Model *temp_r31_2;
    M550Prop *temp_r30;
    s32 var_r29;

    sp8[0] = lbl_1_rodata_220[0];
    sp8[1] = lbl_1_rodata_220[1];
    sp8[2] = lbl_1_rodata_220[2];
    sp8[3] = lbl_1_rodata_220[3];
    var_r29 = 0;
loop_6:
    if (var_r29 < 4) {
        temp_r30 = &lbl_1_bss_1FC0->unk178[var_r29 + 5];
        temp_r31 = &lbl_1_bss_1FC0->unk3C[sp8[var_r29]];
        if ((s32) temp_r30->unk0 == 0) {
            temp_r30->unk0 = 1;
            temp_r30->unk4 = 0;
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
        temp_r30->unk4 += 1;
        temp_r31->unk10.y = (f32) ((f64) temp_r31->unk10.y - 0.01);
        if (temp_r31->unk10.y <= -45.0f) {
            temp_r31->unk10.y = 75.0f;
        }
        var_r29 += 1;
        goto loop_6;
    }
    temp_r31_2 = lbl_1_bss_1FC0->unk3C;
    temp_r31_2->unk10.y -= 0.005f;
}

void fn_1_6D8C(void) {
    lbl_1_bss_1FC0->unk178[9].unk4 = -1;
}

void fn_1_6DA4(void) {
    s32 sp8;
    M550Model *temp_r30;
    M550Prop *temp_r31;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;

    sp8 = lbl_1_rodata_244;
    temp_r31 = &lbl_1_bss_1FC0->unk178[9];
    temp_r30 = &lbl_1_bss_1FC0->unk3C[lbl_1_rodata_244];
    if ((s32) lbl_1_bss_1FC0->unk178[9].unk4 >= -1) {
        if ((s32) lbl_1_bss_1FC0->unk178[9].unk4 == -1) {
            Hu3DModelAttrSet(temp_r30->unk0, 1U);
            temp_r31->unk4 -= 1;
            return;
        }
        if ((s32) temp_r31->unk0 == 0) {
            temp_r31->unk0 = 1;
            temp_r31->unk4 = 0;
            temp_r31->unk8 = 0;
            temp_r31->unkC = 0;
            temp_r31->unk10 = 0;
            temp_r31->unk18 = 0;
            temp_r30->unk4.x = -1100.0f;
            temp_r30->unk4.y = 1850.0f;
            temp_r30->unk4.z = -2800.0f;
            temp_r30->unk10.x = 0.0f;
            temp_r30->unk10.z = 0.0f;
            Hu3DModelPosSetV(temp_r30->unk0, &temp_r30->unk4);
            Hu3DModelAttrReset(temp_r30->unk0, 1U);
            Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
            Hu3DMotionSpeedSet(temp_r30->unk0, 1.0f);
            temp_r31->unk2C = 1.0f;
            fn_1_984(0xA7, temp_r31->unk2C);
            return;
        }
        temp_r31->unk4 = (temp_r31->unk4 + 1) % 360;
        temp_r30->unk10.z = (f32) (2.0 * sin((3.141592653589793 * (f64) temp_r31->unk4) / 180.0));
        temp_r0 = temp_r31->unk18;
        switch (temp_r0) {                          /* irregular */
        case 0:
            temp_r31->unk8 += 1;
            temp_r31->unk2C = (f32) (1.0 - (0.4 * sin((3.141592653589793 * (f64) ((s32) (temp_r31->unk8 * 0x5A) / 16)) / 180.0)));
            fn_1_984(0xA7, temp_r31->unk2C);
            if ((s32) temp_r31->unk8 == 0x10) {
                temp_r31->unk8 = 0;
                temp_r31->unkC = (rand8() % 60) + 0x40;
                temp_r31->unk18 += 1;
                return;
            }
            break;
        case 1:
            temp_r3 = temp_r31->unk8;
            temp_r31->unk8 = temp_r3 + 1;
            if (temp_r3 >= (s32) temp_r31->unkC) {
                fn_1_984(0xA7, 1.0f);
                temp_r31->unk10 = (temp_r31->unk10 + 1) % 6;
                if (((s32) temp_r31->unk10 == 1) || ((s32) temp_r31->unk10 == 4)) {
                    temp_r31->unk18 = 0;
                } else {
                    temp_r31->unk18 += 1;
                }
                temp_r31->unk8 = 0;
                return;
            }
            break;
        case 2:
            temp_r3_2 = temp_r31->unk8;
            temp_r31->unk8 = temp_r3_2 + 1;
            if (temp_r3_2 >= 6) {
                fn_1_984(0xA7, 0.6f);
                temp_r31->unk18 = 0;
                temp_r31->unk8 = 0;
            }
            break;
        }
    }
}

void fn_1_719C(void) {
    s32 sp5C[6];
    f32 sp48[5];
    f32 sp34[5];
    f32 sp20[5];
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    M550Model *temp_r29;
    M550Model *temp_r30;
    M550Prop *temp_r31;
    f64 temp_f31;
    f64 temp_f31_2;
    s32 temp_r3;
    s32 var_r28;

    sp5C[0] = lbl_1_rodata_274[0];
    sp5C[1] = lbl_1_rodata_274[1];
    sp5C[2] = lbl_1_rodata_274[2];
    sp5C[3] = lbl_1_rodata_274[3];
    sp5C[4] = lbl_1_rodata_274[4];
    sp5C[5] = lbl_1_rodata_274[5];
    sp48[0] = lbl_1_rodata_28C[0];
    sp48[1] = lbl_1_rodata_28C[1];
    sp48[2] = lbl_1_rodata_28C[2];
    sp48[3] = lbl_1_rodata_28C[3];
    sp48[4] = lbl_1_rodata_28C[4];
    sp34[0] = lbl_1_rodata_2A0[0];
    sp34[1] = lbl_1_rodata_2A0[1];
    sp34[2] = lbl_1_rodata_2A0[2];
    sp34[3] = lbl_1_rodata_2A0[3];
    sp34[4] = lbl_1_rodata_2A0[4];
    sp20[0] = lbl_1_rodata_2B4[0];
    sp20[1] = lbl_1_rodata_2B4[1];
    sp20[2] = lbl_1_rodata_2B4[2];
    sp20[3] = lbl_1_rodata_2B4[3];
    sp20[4] = lbl_1_rodata_2B4[4];
    sp8 = lbl_1_rodata_2C8[0];
    spC = lbl_1_rodata_2C8[1];
    sp10 = lbl_1_rodata_2C8[2];
    sp14 = lbl_1_rodata_2C8[3];
    sp18 = lbl_1_rodata_2C8[4];
    sp1C = lbl_1_rodata_2C8[5];
    var_r28 = 0;
loop_35:
    if (var_r28 < 5) {
        temp_r31 = &lbl_1_bss_1FC0->unk178[var_r28 + 0xA];
        temp_r30 = &lbl_1_bss_1FC0->unk3C[sp5C[var_r28]];
        if ((s32) temp_r31->unk0 == 0) {
            temp_r31->unk0 = 1;
            temp_r31->unk4 = 0;
            Hu3DModelAttrReset(temp_r30->unk0, 1U);
            Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
            if (var_r28 == 0) {
                Hu3DMotionSpeedSet(temp_r30->unk0, 4.0f);
            } else {
                Hu3DMotionSpeedSet(temp_r30->unk0, 1.0f);
            }
            Hu3DModelAttrSet(temp_r30->unk0, 0x40000001U);
            temp_r31->unk2C = sp48[var_r28];
            temp_r31->unk30 = sp34[var_r28];
            temp_r31->unk34 = sp20[var_r28];
        }
        temp_r31->unk30 += temp_r31->unk34;
        if (var_r28 == 0) {
            if (temp_r31->unk30 > 270.0f) {
                temp_r31->unk30 = 0.0f;
                temp_r31->unk1C = 0;
            }
            if ((temp_r31->unk30 > 0.0f) && (temp_r31->unk30 <= 90.0f)) {
                temp_r31->unk30 -= 3.0f * temp_r31->unk34 * 0.25f;
            }
        }
        if (temp_r31->unk34 >= 0.0f) {
            temp_r30->unk10.y = 90.0f + temp_r31->unk30;
        } else {
            temp_r30->unk10.y = 270.0f + temp_r31->unk30;
        }
        if (var_r28 < 3) {
            if (var_r28 != 0) {
                if (var_r28 < 0) {

                } else {
                    temp_r30->unk4.x = (f32) ((f64) sp8 + ((f64) temp_r31->unk2C * sin((3.141592653589793 * (f64) temp_r31->unk30) / 180.0)));
                    temp_r30->unk4.z = (f32) ((f64) sp10 + ((f64) temp_r31->unk2C * cos((3.141592653589793 * (f64) temp_r31->unk30) / 180.0)));
                    temp_r30->unk4.y = spC;
                }
            } else {
                if ((s32) temp_r31->unk18 == 0) {
                    temp_r30->unk4.x = (f32) ((f64) temp_r31->unk2C * sin((3.141592653589793 * (f64) temp_r31->unk30) / 180.0));
                    temp_r30->unk4.z = (f32) ((f64) temp_r31->unk2C * cos((3.141592653589793 * (f64) temp_r31->unk30) / 180.0));
                    temp_f31 = sin((3.141592653589793 * (f64) (180.0f + temp_r31->unk30)) / 180.0);
                    temp_r30->unk4.y = (f32) (400.0 + (5000.0 * sin(0.20943951023931953) * temp_f31));
                    temp_r30->unk10.x = (f32) (12.0 * sin((3.141592653589793 * (f64) (90.0f + temp_r31->unk30)) / 180.0));
                    if (((s32) temp_r31->unk1C == 0) && (temp_r31->unk30 > 180.0f)) {
                        temp_r31->unk18 += 1;
                        temp_r31->unk3C = (f32) ((f64) temp_r30->unk4.x + (600.0 * cos((3.141592653589793 * (f64) (90.0f + temp_r30->unk10.x)) / 180.0)));
                        temp_r31->unk40 = (f32) ((f64) temp_r30->unk4.y + (600.0 * sin((3.141592653589793 * (f64) (90.0f + temp_r30->unk10.x)) / 180.0)));
                        temp_r31->unk44 = (90.0f + temp_r30->unk10.x) - 180.0f;
                        temp_r31->unk10 = 0;
                        temp_r31->unk34 = 0.0f;
                        temp_r31->unk1C = 1;
                    }
                } else {
                    temp_r31->unk44 = (f32) ((f64) temp_r31->unk44 - 1.5);
                    temp_r30->unk10.x = (f32) ((f64) temp_r30->unk10.x - 1.5);
                    temp_r30->unk4.x = (f32) ((f64) temp_r31->unk3C + (600.0 * cos((3.141592653589793 * (f64) temp_r31->unk44) / 180.0)));
                    temp_r30->unk4.y = (f32) ((f64) temp_r31->unk40 + (600.0 * sin((3.141592653589793 * (f64) temp_r31->unk44) / 180.0)));
                    temp_r3 = temp_r31->unk10;
                    temp_r31->unk10 = temp_r3 + 1;
                    if (temp_r3 >= 0xEF) {
                        temp_r31->unk34 = 0.3f;
                        temp_r31->unk18 = 0;
                    }
                }
                temp_r31->unk4 += 1;
                if ((s32) temp_r31->unk4 >= 0xF) {
                    temp_r31->unk4 = 0;
                    temp_r29 = &lbl_1_bss_1FC0->unk3C[sp5C[5] + temp_r31->unk8];
                    Hu3DModelAttrReset(temp_r29->unk0, 1U);
                    Hu3DMotionTimeSet(temp_r29->unk0, 0.0f);
                    Hu3DMotionSpeedSet(temp_r29->unk0, 1.0f);
                    if ((s32) temp_r31->unk18 == 0) {
                        temp_r29->unk4.x = (f32) ((f64) temp_r31->unk2C * sin((3.141592653589793 * (f64) (temp_r31->unk30 - temp_r31->unk34)) / 180.0));
                        temp_r29->unk4.z = (f32) ((f64) temp_r31->unk2C * cos((3.141592653589793 * (f64) (temp_r31->unk30 - temp_r31->unk34)) / 180.0));
                        temp_f31_2 = sin((3.141592653589793 * (f64) (180.0f + (temp_r31->unk30 - temp_r31->unk34))) / 180.0);
                        temp_r29->unk4.y = (f32) (400.0 + (5000.0 * sin(0.20943951023931953) * temp_f31_2));
                    } else {
                        temp_r29->unk4.x = (f32) ((f64) temp_r31->unk3C + (600.0 * cos((3.141592653589793 * (f64) (1.5f + temp_r31->unk44)) / 180.0)));
                        temp_r29->unk4.y = (f32) ((f64) temp_r31->unk40 + (600.0 * sin((3.141592653589793 * (f64) (1.5f + temp_r31->unk44)) / 180.0)));
                        temp_r29->unk4.z = temp_r30->unk4.z;
                    }
                    Hu3DModelPosSetV(temp_r29->unk0, &temp_r29->unk4);
                    temp_r31->unk8 = (temp_r31->unk8 + 1) % 10;
                }
            }
        } else if (var_r28 < 5) {
            temp_r30->unk4.x = (f32) ((f64) sp14 + ((f64) temp_r31->unk2C * sin((3.141592653589793 * (f64) temp_r31->unk30) / 180.0)));
            temp_r30->unk4.z = (f32) ((f64) sp1C + ((f64) temp_r31->unk2C * cos((3.141592653589793 * (f64) temp_r31->unk30) / 180.0)));
            temp_r30->unk4.y = sp18;
        }
        var_r28 += 1;
        goto loop_35;
    }
}

void fn_1_7C00(void) {
    lbl_1_bss_1FC0->unk178[0xF].unk4 = -1;
    Hu3DModelAttrSet(lbl_1_bss_1FC0->unk3C[0xA1].unk0, 1U);
}

void fn_1_7C4C(void) {
    s32 sp8;
    M550Model *temp_r3;
    M550Prop *temp_r31;
    s32 temp_r3_2;
    s32 temp_r3_3;

    sp8 = lbl_1_rodata_330;
    temp_r31 = &lbl_1_bss_1FC0->unk178[0xF];
    temp_r3 = lbl_1_bss_1FC0->unk3C;
    if ((s32) lbl_1_bss_1FC0->unk178[0xF].unk4 >= -1) {
        if ((s32) lbl_1_bss_1FC0->unk178[0xF].unk4 == -1) {
            Hu3DModelAttrSet(temp_r3[0xA1].unk0, 1U);
            temp_r31->unk4 -= 1;
        }
        if ((s32) temp_r31->unk0 == 0) {
            temp_r3_2 = temp_r31->unk4;
            temp_r31->unk4 = temp_r3_2 + 1;
            if (temp_r3_2 > 0x320) {
                temp_r31->unk0 = 1;
                temp_r31->unk4 = 0;
                Hu3DModelAttrReset(temp_r3[0xA1].unk0, 1U);
                Hu3DMotionTimeSet(temp_r3[0xA1].unk0, 50.0f);
                Hu3DMotionSpeedSet(temp_r3[0xA1].unk0, 0.5f);
                Hu3DModelScaleSet(temp_r3[0xA1].unk0, 2.0f, 2.0f, 2.0f);
                temp_r3[0xA1].unk4.x = -2000.0f;
                temp_r3[0xA1].unk4.z = 2000.0f;
                temp_r3[0xA1].unk4.y = 1200.0f;
                Hu3DModelPosSetV(temp_r3[0xA1].unk0, &temp_r3[0xA1].unk4);
            }
        }
        if ((s32) temp_r31->unk0 == 1) {
            temp_r31->unk4 += 1;
            if ((s32) temp_r31->unk4 >= 0x63) {
                Hu3DMotionTimeSet(temp_r3[0xA1].unk0, 51.0f);
                temp_r31->unk4 = 0;
            }
            temp_r3[0xA1].unk4.x += 5.0f;
            if (temp_r3[0xA1].unk4.x > 4000.0f) {
                temp_r31->unk0 = 2;
                temp_r31->unk4 = 0;
                temp_r31->unk8 = ((rand8() % 5) * 0x1E) + 0x258;
            }
        }
        if ((s32) temp_r31->unk0 == 2) {
            temp_r3_3 = temp_r31->unk4;
            temp_r31->unk4 = temp_r3_3 + 1;
            if (temp_r3_3 >= (s32) temp_r31->unk8) {
                temp_r3[0xA1].unk4.x = -2000.0f;
                temp_r31->unk0 = 1;
            }
        }
    }
}

void fn_1_7E94(void) {
    Hu3DModelAttrSet(lbl_1_bss_1FC0->unk3C[0xA2].unk0, 1U);
    lbl_1_bss_1FC0->unk178[0x10].unk0 = -1;
}

void fn_1_7EE0(void) {
    s32 sp8;
    M550Model *temp_r30;
    M550Prop *temp_r31;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_4;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r3_3;
    u32 temp_r3_6;
    u8 temp_r3_2;
    u8 temp_r3_5;

    sp8 = lbl_1_rodata_350;
    temp_r31 = &lbl_1_bss_1FC0->unk178[0x10];
    temp_r30 = &lbl_1_bss_1FC0->unk3C[lbl_1_rodata_350];
    if ((s32) lbl_1_bss_1FC0->unk178[0x10].unk0 >= 0) {
        temp_r0 = lbl_1_bss_1FC0->unk178[0x10].unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            temp_r3 = lbl_1_bss_1FC0->unk178[0x10].unk4;
            lbl_1_bss_1FC0->unk178[0x10].unk4 = temp_r3 + 1;
            if (temp_r3 > 0x12C) {
                lbl_1_bss_1FC0->unk178[0x10].unk4 = -0xC8;
                lbl_1_bss_1FC0->unk178[0x10].unk0 = 1;
                Hu3DModelAttrReset(temp_r30->unk0, 1U);
                Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
                Hu3DMotionSpeedSet(temp_r30->unk0, 0.25f);
                temp_r30->unk4.x = -4356.0f;
                temp_r30->unk4.z = -13000.0f;
                temp_r30->unk4.y = 0.0f;
                Hu3DModelPosSetV(temp_r30->unk0, &temp_r30->unk4);
                return;
            }
            break;
        case 1:
            temp_r31->unk4 += 1;
            if ((s32) temp_r31->unk4 >= 0xC8) {
                temp_r31->unk4 = 0;
                Hu3DMotionTimeSet(temp_r30->unk0, 51.0f);
            }
            temp_r30->unk4.x = (f32) ((f64) temp_r30->unk4.x + (14.85 * sin(0.39269908169872414)));
            temp_r30->unk4.z = (f32) ((f64) temp_r30->unk4.z + (14.85 * cos(0.39269908169872414)));
            if (temp_r30->unk4.z >= 2000.0f) {
                temp_r31->unk0 = 2;
                temp_r31->unk4 = 0;
                temp_r3_2 = rand8();
                temp_r31->unk8 = (((temp_r3_2 % 8)) * 0x1E) + 0x12C;
                return;
            }
            break;
        case 2:
            temp_r3_4 = lbl_1_bss_1FC0->unk178[0x10].unk4;
            lbl_1_bss_1FC0->unk178[0x10].unk4 = temp_r3_4 + 1;
            if (temp_r3_4 >= (s32) lbl_1_bss_1FC0->unk178[0x10].unk8) {
                lbl_1_bss_1FC0->unk178[0x10].unk0 = 1;
                Hu3DMotionTimeSet(temp_r30->unk0, 0.0f);
                temp_r3_5 = rand8();
                temp_r30->unk4.x = (f32) ((((temp_r3_5 % 4)) * 0x1F4) - 0x1104);
                temp_r30->unk4.z = -13000.0f;
                temp_r31->unk4 = -0xC8;
            }
            break;
        }
    }
}

void fn_1_8190(void) {
    M550Model *temp_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r31 = &lbl_1_bss_1FC0->unk3C[lbl_1_rodata_3B0[var_r30]];
        Hu3DModelAttrReset(temp_r31->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31->unk0, 1.0f);
        Hu3DMotionTimeSet(temp_r31->unk0, 50.0f);
        temp_r31->unk4 = lbl_1_rodata_370[var_r30];
        Hu3DModelPosSetV(temp_r31->unk0, &temp_r31->unk4);
        Hu3DModelScaleSet(temp_r31->unk0, lbl_1_rodata_3A0[var_r30], lbl_1_rodata_3A0[var_r30], lbl_1_rodata_3A0[var_r30]);
    }
}

void fn_1_8350(void) {
    s32 sp8[4];
    M550Model *temp_r30;
    s32 var_r31;

    sp8[0] = lbl_1_rodata_3C0[0];
    sp8[1] = lbl_1_rodata_3C0[1];
    sp8[2] = lbl_1_rodata_3C0[2];
    sp8[3] = lbl_1_rodata_3C0[3];
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        temp_r30 = &lbl_1_bss_1FC0->unk3C[sp8[var_r31]];
        if (Hu3DMotionTimeGet(temp_r30->unk0) >= 99.0f) {
            Hu3DMotionTimeSet(temp_r30->unk0, 50.0f);
        }
        var_r31 += 1;
        goto loop_4;
    }
}
