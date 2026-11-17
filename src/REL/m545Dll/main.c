// MP5 m545 (button-sequence duel), generated from its m2c draft by tools/mp5/ports/m545dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m545dll (tools/mp5/decomp.py m545dll --types tools/mp5/types/m545dll.h)
// Written from the draft: m545 (1 vs 1 duel, a button-sequence memory game). Runs on MP5's MgSeq sequencer.
// lbl_1_bss_9B8 points at the work struct lbl_1_bss_67C; lbl_1_bss_C holds the two per-player game states.

typedef struct M545Model { // model table entry, 0x1C (0x26 of them in lbl_1_bss_254)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M545Model;

typedef struct M545Player { // 0x1C
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // com: difficulty + 1
    s16 unk6; // pad
    s32 unk8; // HuPadBtn
    s32 unkC; // HuPadBtnDown
    s8 unk10; // stick x (dead zone 10)
    char pad11;
    u16 unk12; // HuPadBtnRep
    s8 unk14; // stick y
    s8 unk15; // sub stick x
    s8 unk16; // sub stick y
    u8 unk17; // trigger L
    u8 unk18; // trigger R
    u8 unk19; // HuPadDStk
    u8 unk1A; // HuPadDStkRep
    char pad1B;
} M545Player;

typedef struct M545Char { // per MP5 character, 0x14
    u32 unk0[5]; // MP5 motion data numbers
} M545Char;

typedef struct M545Anim { // per player character animation request, 0x44 (fn_1_8580 applies it)
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
    s32 unk24; // motion end
    s16 unk28; // shift state
    s16 unk2A; // shift motion index
    u32 unk2C; // shift attrs
    f32 unk30; // shift start time
    f32 unk34; // shift length
    f32 unk38; // shift time
    f32 unk3C; // shift max time
    char pad40[4];
} M545Anim;

typedef struct M545Work { // lbl_1_bss_67C, 0x250
    char pad0[4];
    M545Player unk4[2];
    M545Model *unk3C; // model table (lbl_1_bss_254)
    M545Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_240)
    M545Anim unk50[2];
    u32 *unkD8; // data numbers (lbl_1_data_12C)
    s16 unkDC; // models: 1 = scenery shown
    char padDE[2];
    s32 unkE0; // mode step
    s32 unkE4;
    s32 unkE8;
    s32 unkEC;
    s32 unkF0; // frame counter
    s32 unkF4; // mode step
    char padF8[0x38];
    s32 unk130; // bird hold flag
    s32 unk134;
    s32 unk138;
    s32 unk13C; // beat phase
    char pad140[0x10];
    f32 unk150;
    f32 unk154;
    char pad158[8];
    s32 unk160;
    s32 unk164;
    s32 unk168;
    s32 unk16C;
    char pad170[0x10];
    f32 unk180;
    f32 unk184;
    f32 unk188;
    char pad18C[4];
    s32 unk190;
    s32 unk194;
    s32 unk198;
    s32 unk19C;
    char pad1A0[0x10];
    f32 unk1B0;
    f32 unk1B4;
    char pad1B8[0xC];
    s32 unk1C4;
    char pad1C8[4];
    s32 unk1CC;
    char pad1D0[0x10];
    f32 unk1E0;
    f32 unk1E4;
    f32 unk1E8;
    char pad1EC[8];
    s32 unk1F4;
    char pad1F8[4];
    s32 unk1FC;
    char pad200[0x50];
} M545Work;

typedef struct M545Pl { // lbl_1_bss_C, per player game state, 0xC8
    s16 unk0;
    s16 unk2;
    s16 unk4; // sequence length reached
    s16 unk6; // retries
    Vec unk8; // scale of the character
    Vec unk14; // hand position
    Mtx unk20; // hand matrix
    s16 unk50; // pose
    char pad52[2];
    char *unk54[2]; // hand hook
    s16 unk5C; // input done
    s16 unk5E; // success
    s32 unk60[6]; // presses per button
    s32 unk78[6];
    char pad90[8];
    s32 unk98; // frames
    s32 unk9C; // input frames
    s32 unkA0;
    char padA4[8];
    f32 unkAC[6]; // wobble angles
    char padC4[4];
} M545Pl;

typedef struct M545Snd { // lbl_1_bss_19C, 0xA4
    s16 unk0;
    s16 unk2; // wobble phase
    s16 unk4;
    s16 unk6;
    f32 unk8; // drop speed
    f32 unkC[12]; // block fade
    f32 unk3C; // camera y at the end
    f32 unk40; // camera dist at the end
    char pad44[8];
    s16 unk4C; // winner (-1 draw)
    s16 unk4E;
    s16 unk50;
    s16 unk52; // bgm started
    s32 unk54; // bgm stream
    s32 unk58; // jingle stream
    s32 unk5C[12]; // fx
    s16 unk8C[12]; // fx used
} M545Snd;

typedef struct M545Seq { // lbl_1_bss_980, 0x4
    s16 unk0; // button
    s16 unk2; // frames
} M545Seq;

typedef struct M545Cam { // lbl_1_bss_8, 0x50
    s32 unk0;
    Vec unk4; // pos
    Vec unk10; // rot
    Vec unk1C; // target
    Vec unk28; // up
    f32 unk34; // zoom
    f32 unk38; // aspect
    f32 unk3C; // viewport x
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C; // fov
} M545Cam;

typedef struct M545CamInit { // lbl_1_data_178, 0x34
    Vec unk0; // target
    Vec unkC; // rot
    f32 unk18; // zoom
    f32 unk1C; // aspect
    f32 unk20; // viewport x
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30; // fov
} M545CamInit;

typedef struct M545Light { // lbl_1_bss_4, 0x3C
    s16 unk0;
    char pad2[2];
    Vec unk4; // pos
    Vec unk10; // rot
    Vec unk1C; // target
    Vec unk28; // direction
    f32 unk34; // distance
    GXColor unk38;
} M545Light;

typedef struct M545Shadow { // lbl_1_bss_0, 0x50
    Vec unk0; // pos
    Vec unkC; // rot
    Vec unk18; // target
    char pad24[0xC];
    Vec unk30; // up
    char pad3C[0xC];
    f32 unk48; // distance
    f32 unk4C; // tp level
} M545Shadow;

typedef struct M545Part { // particle template, 0x38 (lbl_1_data_268)
    s32 unk0;
    u8 unk4[4]; // start color
    u8 unk8[4]; // end color
    Vec unkC; // velocity
    Vec unk18; // velocity scale
    f32 unk24; // gravity
    f32 unk28;
    f32 unk2C; // scale delta
    f32 unk30; // alpha delta
    f32 unk34; // color step
} M545Part;


s32 fn_1_26BC(M545Work *work);
s32 fn_1_2E88(M545Work *work);
s32 fn_1_2FE8(M545Work *work);
s32 fn_1_3030(M545Work *work);
s32 fn_1_3480(M545Work *work);
s32 fn_1_34EC(M545Work *work);
s32 fn_1_3538(M545Work *work);
s32 fn_1_3600(M545Work *work);
s32 fn_1_3638(void);
void fn_1_3654(M545Work *work);
void fn_1_373C(M545Work *work);
void fn_1_40AC(M545Work *work);
void fn_1_41D4(M545Work *work, s16 player);
s32 fn_1_4400(s16 player);
void fn_1_44D8(M545Work *work);
s16 fn_1_499C(M545Work *work, s16 step);
s16 fn_1_4B2C(M545Work *work, s16 slot, s16 height);
s16 fn_1_5794(M545Work *work, s16 player);
s16 fn_1_5BC4(M545Work *work, s16 player);
void fn_1_6590(M545Work *work);
void fn_1_6668(M545Work *work, f32 speed);
void fn_1_695C(M545Work *work, s16 player, f32 angle);
void fn_1_6BC4(M545Work *work, s16 player, s32 unused, f32 speed);
s32 fn_1_6D40(M545Work *work);
s32 fn_1_70E8(M545Work *work);
void fn_1_762C(M545Work *work, s16 player);
void fn_1_77EC(M545Work *work, M545Model *models, u32 *dataNums);
void fn_1_7A38(s16 arg0);
void fn_1_7CE4(M545Char *chr0, M545Char *chr1);
void fn_1_7D08(s16 *mot0, s16 *mot1);
void fn_1_7D2C(void);
void fn_1_8454(void);
void fn_1_4A8(s16 cam);
void fn_1_8C4(s16 cam);
void fn_1_E3C(void);
void fn_1_106C(void);
void fn_1_1344(void);
void fn_1_1474(void);
void fn_1_17EC(void);
void fn_1_1980(Vec *pos);
s16 fn_1_1D4C(M545Part *tmpl, f32 x, f32 y, f32 z, f32 scale);
void fn_1_2338(void);
void fn_1_2368(void);
void fn_1_2398(s16 arg0, s16 arg1);
void fn_1_2400(s16 arg0);
void fn_1_2460(s16 arg0);
void fn_1_24D8(s16 arg0, s16 arg1, s16 arg2);
void fn_1_2560(s16 arg0, s16 arg1);
void fn_1_25F0(s16 arg0);
void fn_1_269C(void);
void fn_1_8944(void);
void fn_1_8F7C(void);
void fn_1_94C8(void);
void fn_1_9DAC(void);
void fn_1_A7B8(void);
s32 fn_1_26BC(M545Work *work);
s32 fn_1_2E88(M545Work *work);
s32 fn_1_2FE8(M545Work *work);
s32 fn_1_3030(M545Work *work);
s32 fn_1_3480(M545Work *work);
s32 fn_1_34EC(M545Work *work);
s32 fn_1_3538(M545Work *work);
s32 fn_1_3600(M545Work *work);
s32 fn_1_3638(void);
void fn_1_373C(M545Work *work);
void fn_1_40AC(M545Work *work);
void fn_1_44D8(M545Work *work);
s16 fn_1_499C(M545Work *work, s16 step);
s16 fn_1_4B2C(M545Work *work, s16 slot, s16 height);
s16 fn_1_5794(M545Work *work, s16 player);
s16 fn_1_5BC4(M545Work *work, s16 player);
void fn_1_6590(M545Work *work);
void fn_1_6668(M545Work *work, f32 speed);
void fn_1_6BC4(M545Work *work, s16 player, s32 unused, f32 speed);
s32 fn_1_6D40(M545Work *work);
s32 fn_1_70E8(M545Work *work);
void fn_1_762C(M545Work *work, s16 player);
void ObjectSetup(void);
void fn_1_2F0(s16 mode, s16 frameNo);
void fn_1_324(s16 mode, s16 frameNo);
void fn_1_358(s16 mode, s16 frameNo);
void fn_1_380(s16 mode, s16 frameNo);
void fn_1_3B4(s16 mode, s16 frameNo);
void fn_1_3E8(s16 mode, s16 frameNo);
void fn_1_41C(s16 mode, s16 frameNo);
void fn_1_450(s16 mode, s16 frameNo);
void fn_1_478(s16 mode, s16 frameNo);
void fn_1_4A4(omObjData *obj);
void fn_1_4A8(s16 cam);
void fn_1_8C4(s16 cam);
void fn_1_E3C(void);
void fn_1_106C(void);
void fn_1_1344(void);
void fn_1_1474(void);
void fn_1_17EC(void);
void fn_1_1980(Vec *pos);
s16 fn_1_1D4C(M545Part *tmpl, f32 x, f32 y, f32 z, f32 scale);
void fn_1_1F20(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_2368(void);
void fn_1_2398(s16 arg0, s16 arg1);
void fn_1_2460(s16 arg0);
void fn_1_24D8(s16 arg0, s16 arg1, s16 arg2);
void fn_1_77EC(M545Work *work, M545Model *models, u32 *dataNums);
void fn_1_7A38(s16 arg0);
void fn_1_7CE4(M545Char *chr0, M545Char *chr1);
void fn_1_7D08(s16 *mot0, s16 *mot1);
void fn_1_7D2C(void);
void fn_1_803C(omObjData *obj);
void fn_1_8454(void);
void fn_1_8580(omObjData *obj);
void fn_1_88F0(omObjData *obj);
void fn_1_8944(void);
void fn_1_8F7C(void);
void fn_1_94C8(void);
void fn_1_9DAC(void);
void fn_1_A7B8(void);

s16 lbl_1_data_2D8[4][7] = {
    { 0x64, 0x50, 0x28, 0, 0, 0, 0 },
    { 0x64, 0x64, 0x50, 0x3C, 0x28, 0x14, 0 },
    { 0x64, 0x64, 0x64, 0x50, 0x3C, 0x28, 0x14 },
    { 0x64, 0x64, 0x64, 0x64, 0x50, 0x3C, 0x28 },
};
Vec lbl_1_bss_8D8[0xE];
M545Seq lbl_1_bss_980[7];
s16 lbl_1_bss_99C[2][6];
MGSEQ_PARAM lbl_1_data_0 = {
    0,
    0,
    fn_1_2F0,
    fn_1_324,
    fn_1_358,
    fn_1_380,
    fn_1_3B4,
    fn_1_3E8,
    fn_1_41C,
    fn_1_450,
    fn_1_478,
};
M545Char lbl_1_data_28[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 91), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 93), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 94), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 91), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 93), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 94), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 91), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 93), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 94), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 91), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 93), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 94), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 91), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 93), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 94), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 91), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 93), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 94), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 91), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 93), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 94), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 91 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 93 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 94 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */ } },
};
u32 lbl_1_data_12C[0x13] = {
    DATA_MAKE_NUM(DATADIR_MP5_M545, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M545, 11),
};
M545CamInit lbl_1_data_178[4] = {
    {
        { 0.0f, 250.0f, 0.0f },
        { -20.0f, 0.0f, 500.0f },
        1400.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 500.0f },
        500.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 500.0f },
        500.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 500.0f },
        500.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
};
s16 lbl_1_data_248[0x10] = {
    1,
    2,
    4,
    8,
    0x10,
    0x20,
    0x40,
    0x80,
    0x100,
    0x200,
    0x400,
    0x800,
    0x1000,
    0x2000,
    0x4000,
    0x8000,
};
M545Part lbl_1_data_268 = {
    0,
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0, 0, 0, 0xFF },
    { 0.0f, 2.0f, 1.0f },
    { 0.85f, 0.85f, 0.85f },
    0.2f,
    0.0f,
    1.0f,
    -3.0f,
    0.02f,
};
s16 lbl_1_data_2A0[0xC] = {
    0x822,
    0x823,
    0x824,
    0x825,
    0x826,
    0x827,
    0x828,
    0x829,
    0x82A,
    0x82B,
    0x82C,
    0x82D,
};
M545Shadow *lbl_1_bss_0;
M545Light *lbl_1_bss_4;
M545Cam *lbl_1_bss_8;
M545Pl lbl_1_bss_C[2];
M545Snd lbl_1_bss_19C;
s16 lbl_1_bss_240[2][5];
M545Model lbl_1_bss_254[0x26];
M545Work lbl_1_bss_67C;
HUPROCESS *lbl_1_bss_8CC;
void *lbl_1_bss_8D0;
s16 lbl_1_bss_8D4;
Vec lbl_1_data_310[0xC] = {
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
void (*lbl_1_data_3A0[5])() = { fn_1_8944, fn_1_8F7C, fn_1_94C8, fn_1_9DAC, fn_1_A7B8 };
M545Work *lbl_1_bss_9B8;

s32 fn_1_26BC(M545Work *work) {
    s16 temp_r0;
    s16 temp_r26;
    s16 var_r28;
    s16 var_r28_2;
    s16 var_r29;
    s16 var_r29_2;
    s16 var_r29_3;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;
    s16 var_r31_4;
    s16 var_r31_5;
    s16 var_r31_6;
    s16 var_r31_7;
    s16 var_r31_8;

    memset(&lbl_1_bss_19C, 0, sizeof(M545Snd));
    memset((M545Snd *) lbl_1_bss_C, 0, 0x190);
    var_r31 = 0;
loop_2:
    if (var_r31 < 0xC) {
        lbl_1_bss_19C.unk8C[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_C->unk8.x = 1.0f;
    lbl_1_bss_C->unk8.y = 1.0f;
    lbl_1_bss_C->unk8.z = 1.0f;
    lbl_1_bss_C[1].unk8.x = 1.0f;
    lbl_1_bss_C[1].unk8.y = 1.0f;
    lbl_1_bss_C[1].unk8.z = 1.0f;
    lbl_1_bss_C->unk5E = 1;
    lbl_1_bss_C[1].unk5E = 1;
    lbl_1_bss_C->unk50 = 1;
    lbl_1_bss_C[1].unk50 = 1;
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        var_r29 = 0;
loop_6:
        if (var_r29 < 2) {
            lbl_1_bss_C[var_r31_2].unk54[var_r29] = CharModelItemHookGet(work->unk4[var_r31_2].unk2, 1, 0);
            var_r29 += 1;
            goto loop_6;
        }
        var_r31_2 += 1;
        goto loop_8;
    }
    var_r31_3 = 0;
loop_11:
    if (var_r31_3 < 7) {
        lbl_1_bss_980[var_r31_3].unk0 = -1;
        lbl_1_bss_980[var_r31_3].unk2 = 0;
        var_r31_3 += 1;
        goto loop_11;
    }
    var_r31_4 = 1;
loop_20:
    if (var_r31_4 < 7) {
        do {
            lbl_1_bss_980[var_r31_4].unk0 = frandmod(6U);
            var_r29_2 = 1;
            var_r28 = 0;
loop_17:
            if (var_r29_2 < 7) {
                if ((s16) lbl_1_bss_980[var_r31_4].unk0 == (s16) lbl_1_bss_980[var_r29_2].unk0) {
                    var_r28 += 1;
                }
                var_r29_2 += 1;
                goto loop_17;
            }
        } while (var_r28 > 1);
        var_r31_4 += 1;
        goto loop_20;
    }
    var_r31_5 = 0;
loop_23:
    if (var_r31_5 < 7) {
        lbl_1_bss_980[var_r31_5].unk2 = frandmod(0x79U) + 0x3C;
        var_r31_5 += 1;
        goto loop_23;
    }
    var_r31_6 = 0;
loop_26:
    if (var_r31_6 < 6) {
        temp_r0 = lbl_1_bss_980[var_r31_6 + 1].unk0 * 2;
        lbl_1_bss_99C[0][var_r31_6] = temp_r0;
        lbl_1_bss_99C[1][var_r31_6] = (s16) (temp_r0 + 1);
        var_r31_6 += 1;
        goto loop_26;
    }
    var_r31_7 = 0;
    var_r28_2 = 0;
    var_r29_3 = 0xC;
loop_29:
    if (var_r31_7 < 0xC) {
        work->unk3C[var_r28_2].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) work->unkD8[(s32) (((u32) var_r31_7 >> 0x1FU) + var_r31_7) >> 1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(work->unk3C[var_r28_2].unk0, 1U);
        Hu3DModelCameraSet(work->unk3C[var_r28_2].unk0, 1U);
        Hu3DModelLayerSet(work->unk3C[var_r28_2].unk0, 1);
        temp_r26 = frandmod(0xFU) - 7;
        work->unk3C[var_r28_2].unk10.x = 0.0f;
        work->unk3C[var_r28_2].unk10.y = (f32) temp_r26;
        work->unk3C[var_r28_2].unk10.z = 0.0f;
        work->unk3C[var_r29_3].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) work->unkD8[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(work->unk3C[var_r29_3].unk0, 9U);
        Hu3DModelCameraSet(work->unk3C[var_r29_3].unk0, 1U);
        Hu3DModelLayerSet(work->unk3C[var_r29_3].unk0, 5);
        Hu3DModelShadowSet(work->unk3C[var_r29_3].unk0);
        Hu3DModelShadowDispOn(work->unk3C[var_r29_3].unk0);
        work->unk3C[var_r29_3].unk10 = work->unk3C[var_r28_2].unk10;
        lbl_1_bss_19C.unkC[var_r31_7] = 0.0f;
        Hu3DModelTPLvlSet(work->unk3C[var_r29_3].unk0, lbl_1_bss_19C.unkC[var_r31_7]);
        var_r31_7 += 1;
        var_r28_2 += 1;
        var_r29_3 += 1;
        goto loop_29;
    }
    var_r31_8 = 0;
loop_32:
    if (var_r31_8 < 6) {
        lbl_1_bss_8D8[lbl_1_bss_99C[0][var_r31_8]].x = 0.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[0][var_r31_8]].y = 600.0f + (100.0f * (f32) var_r31_8);
        lbl_1_bss_8D8[lbl_1_bss_99C[0][var_r31_8]].z = -70.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[1][var_r31_8]].x = 0.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[1][var_r31_8]].y = 600.0f + (100.0f * (f32) var_r31_8);
        lbl_1_bss_8D8[lbl_1_bss_99C[1][var_r31_8]].z = -70.0f;
        var_r31_8 += 1;
        goto loop_32;
    }
    fn_1_40AC(work);
    fn_1_17EC();
    return 1;
}

s32 fn_1_2E88(M545Work *work) {
    M545Anim *temp_r30;
    s16 var_r29;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r28;

    var_r28 = 0;
    temp_r0 = work->unkF4;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) lbl_1_bss_19C.unk52 == 0) {
            fn_1_2368();
            lbl_1_bss_19C.unk52 = 1;
        }
        temp_r3 = work->unkF0;
        work->unkF0 = temp_r3 + 1;
        if (temp_r3 > 0x64) {
            work->unkF4 += 1;
        }
        break;
    case 1:
        if (fn_1_6D40(work) != 0) {
            work->unkF4 += 1;
        }
        break;
    case 2:
        var_r29 = 0;
loop_15:
        if (var_r29 < 2) {
            temp_r30 = &work->unk50[var_r29];
            temp_r30->unk28 = 1;
            temp_r30->unk2A = 1;
            temp_r30->unk30 = 0.0f;
            temp_r30->unk34 = 30.0f;
            temp_r30->unk2C = 0x40000001;
            var_r29 += 1;
            goto loop_15;
        }
        work->unkF4 += 1;
        break;
    case 3:
        var_r28 = 1;
        break;
    }
    fn_1_40AC(work);
    return var_r28;
}

s32 fn_1_2FE8(M545Work *work) {
    work->unkF0 = 0;
    fn_1_40AC(work);
    return 0;
}

s32 fn_1_3030(M545Work *work) {
    s32 spC;
    s32 sp8;
    M545Seq *temp_r4;
    s16 temp_r0_2;
    s16 temp_r27;
    s16 temp_r28;
    s16 temp_r3;
    s16 var_r30;
    s16 var_r30_2;
    s32 temp_r0;
    s32 var_r29;

    var_r29 = 0;
    spC = 0;
    sp8 = 0;
    temp_r0 = work->unkE0;
    if ((u32) temp_r0 <= 7U) {
        switch (temp_r0) {
        case 0:
            if (fn_1_4B2C(work, lbl_1_bss_C->unk4, lbl_1_bss_C->unk4) != 0) {
                work->unkE0 = 4;
            }
            break;
        case 1:
            fn_1_44D8(work);
            fn_1_6590(work);
            temp_r4 = &lbl_1_bss_980[lbl_1_bss_C->unk4];
            temp_r0_2 = temp_r4->unk2 - 1;
            temp_r4->unk2 = temp_r0_2;
            if ((temp_r0_2 <= 0) && ((s16) lbl_1_bss_C->unk5C == 1) && ((s16) lbl_1_bss_C->unk4 < 6)) {
                work->unkE0 = 2;
            }
            if (((s16) lbl_1_bss_C->unk5E == 0) || ((s16) lbl_1_bss_C[1].unk5E == 0)) {
                work->unkE0 = 5;
                lbl_1_bss_19C.unk4C = -1;
                if ((s16) lbl_1_bss_C->unk5E == 1) {
                    lbl_1_bss_19C.unk4C = 0;
                } else if ((s16) lbl_1_bss_C[1].unk5E == 1) {
                    lbl_1_bss_19C.unk4C = 1;
                }
            }
            break;
        case 2:
            fn_1_6590(work);
            if (fn_1_499C(work, 0) != 0) {
                work->unkE0 = 3;
            }
            break;
        case 3:
            if (fn_1_4B2C(work, lbl_1_bss_C->unk4, lbl_1_bss_C->unk4) != 0) {
                work->unkE0 = 4;
            }
            fn_1_6590(work);
            break;
        case 4:
            temp_r3 = lbl_1_bss_19C.unk4E;
            lbl_1_bss_19C.unk4E = temp_r3 + 1;
            if (temp_r3 > 0x1E) {
                lbl_1_bss_19C.unk4E = 0;
                work->unkE0 = 1;
            }
            fn_1_6590(work);
            break;
        case 5:
            if (fn_1_499C(work, 1) != 0) {
                var_r30 = 0;
loop_27:
                if (var_r30 < 2) {
                    if ((s16) lbl_1_bss_C[var_r30].unk5E == 0) {
                        CharFXPlayVolPan(work->unk4[var_r30].unk2, 0x202, 0x7F, (s16) ((var_r30 << 5) + 0x30));
                    }
                    var_r30 += 1;
                    goto loop_27;
                }
                work->unkE0 = 6;
            }
            break;
        case 6:
            var_r30_2 = 0;
loop_34:
            if (var_r30_2 < 2) {
                if (((s16) lbl_1_bss_C[var_r30_2].unk5E == 0) && (fn_1_5794(work, var_r30_2) != 0)) {
                    work->unkE0 = 7;
                }
                var_r30_2 += 1;
                goto loop_34;
            }
            break;
        case 7:
            if (((s16) lbl_1_bss_C->unk5E == 0) && ((s16) lbl_1_bss_C[1].unk5E == 0)) {
                MgSeqWinnerSet(-1, -1, -1, -1);
            } else if ((s16) lbl_1_bss_C->unk5E == 0) {
                MgSeqWinnerSet(work->unk4[1].unk2, -1, -1, -1);
                temp_r28 = work->unk4[1].unk0;
                if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                    GWPlayer[temp_r28].coin_win = 0xA;
                }
            } else if ((s16) lbl_1_bss_C[1].unk5E == 0) {
                MgSeqWinnerSet(work->unk4[0].unk2, -1, -1, -1);
                temp_r27 = work->unk4[0].unk0;
                if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                    GWPlayer[temp_r27].coin_win = 0xA;
                }
            }
            lbl_1_bss_19C.unk52 = 0;
            work->unkE0 = 0;
            var_r29 = 1;
            break;
        }
    }
    fn_1_40AC(work);
    return var_r29;
}

s32 fn_1_3480(M545Work *work) {
    M545Work *sp8;

    sp8 = work;
    if ((s16) lbl_1_bss_19C.unk52 == 0) {
        fn_1_2398(1, 0x64);
        lbl_1_bss_19C.unk52 = 1;
    }
    fn_1_40AC(sp8);
    return 1;
}

s32 fn_1_34EC(M545Work *work) {
    s32 temp_r31;

    temp_r31 = fn_1_70E8(work);
    fn_1_40AC(work);
    return temp_r31;
}

s32 fn_1_3538(M545Work *work) {
    M545Anim *temp_r31;

    if ((s32) work->unkE4 == 0) {
        temp_r31 = &work->unk50[lbl_1_bss_19C.unk4C];
        temp_r31->unk0 = 4;
        temp_r31->unk4 = 1.0f;
        temp_r31->unk18 = 0;
        temp_r31->unk20 = 0x40000001;
        temp_r31->unkC = 0.0f;
        work->unkE4 = 1;
    }
    fn_1_40AC(work);
    return 0;
}

s32 fn_1_3600(M545Work *work) {
    M545Work *sp8;

    sp8 = work;
    fn_1_40AC(work);
    return 1;
}

s32 fn_1_3638(void) {
    return 1;
}


void fn_1_373C(M545Work *work) {
    HU3DMODEL *temp_r28;
    M545Model *temp_r0_5;
    M545Model *temp_r3;
    M545Model *temp_r3_2;
    M545Model *temp_r3_3;
    M545Model *temp_r5;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r0_3;
    s16 temp_r0_4;
    s16 temp_r3_4;
    s16 var_r29;
    s16 var_r31;
    s16 var_r31_2;
    s32 temp_r3_5;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        Hu3DModelObjMtxGet(work->unk3C[var_r31 + 0x24].unk0, lbl_1_bss_C[var_r31].unk54[0], (f32 (*)[4]) lbl_1_bss_C[var_r31].unk20[0]);
        if (work->unk4[var_r31].unk2 == 5) { lbl_1_bss_C[var_r31].unk20[1][3] += 35.0f; }
        lbl_1_bss_C[var_r31].unk14.x = lbl_1_bss_C[var_r31].unk20[0][3];
        lbl_1_bss_C[var_r31].unk14.y = lbl_1_bss_C[var_r31].unk20[1][3];
        lbl_1_bss_C[var_r31].unk14.z = lbl_1_bss_C[var_r31].unk20[2][3];
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_24:
    if (var_r31_2 < 2) {
        var_r29 = 0;
loop_22:
        if (var_r29 < 6) {
            temp_r28 = &Hu3DData[work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk0];
            temp_r0 = lbl_1_bss_C[var_r31_2].unk50;
            switch (temp_r0) {                      /* irregular */
            case 0:
                if (var_r29 < (s16) lbl_1_bss_C[var_r31_2].unk4) {
                    MTXCopy((f32 (*)[4]) lbl_1_bss_C[var_r31_2].unk20[0], (f32 (*)[4]) temp_r28->mtx[0]);
                } else {
                    MTXIdentity((f32 (*)[4]) temp_r28->mtx[0]);
                    work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.x = lbl_1_bss_C[var_r31_2].unk14.x;
                    work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = lbl_1_bss_C[var_r31_2].unk14.y;
                    work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.z = lbl_1_bss_C[var_r31_2].unk14.z;
                    if (work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y <= 150.0f) {
                        work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = 150.0f;
                    }
                }
                break;
            case 1:
                MTXIdentity((f32 (*)[4]) temp_r28->mtx[0]);
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.x = lbl_1_bss_C[var_r31_2].unk14.x;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = lbl_1_bss_C[var_r31_2].unk14.y;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.z = lbl_1_bss_C[var_r31_2].unk14.z;
                if (work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y <= 150.0f) {
                    work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = 150.0f;
                }
                break;
            case 2:
                MTXIdentity((f32 (*)[4]) temp_r28->mtx[0]);
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.x = 0.0f;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.z = 0.0f;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = lbl_1_bss_C[var_r31_2].unk14.y;
                if (work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y <= 150.0f) {
                    work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = 150.0f;
                }
                break;
            case 3:
                MTXIdentity((f32 (*)[4]) temp_r28->mtx[0]);
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.x = 0.0f;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.y = 0.0f;
                work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29]].unk4.z = 0.0f;
                break;
            }
            temp_r3 = work->unk3C;
            temp_r0_2 = lbl_1_bss_99C[var_r31_2][var_r29];
            temp_r3[temp_r0_2].unk4.x += lbl_1_bss_8D8[lbl_1_bss_99C[var_r31_2][var_r29]].x;
            temp_r3_2 = work->unk3C;
            temp_r0_3 = lbl_1_bss_99C[var_r31_2][var_r29];
            temp_r3_2[temp_r0_3].unk4.y += lbl_1_bss_8D8[lbl_1_bss_99C[var_r31_2][var_r29]].y;
            temp_r3_3 = work->unk3C;
            temp_r0_4 = lbl_1_bss_99C[var_r31_2][var_r29];
            temp_r3_3[temp_r0_4].unk4.z += lbl_1_bss_8D8[lbl_1_bss_99C[var_r31_2][var_r29]].z;
            temp_r0_5 = work->unk3C;
            temp_r3_4 = lbl_1_bss_99C[var_r31_2][var_r29];
            temp_r5 = work->unk3C;
            temp_r3_5 = lbl_1_bss_99C[var_r31_2][var_r29] + 0xC;
            temp_r5[temp_r3_5].unk4 = temp_r0_5[temp_r3_4].unk4;
            work->unk3C[lbl_1_bss_99C[var_r31_2][var_r29] + 0xC].unk4.y = 101.0f;
            var_r29 += 1;
            goto loop_22;
        }
        var_r31_2 += 1;
        goto loop_24;
    }
}

void fn_1_40AC(M545Work *work) {
    s16 var_r30;

    fn_1_373C(work);
    var_r30 = 0;
loop_2:
    if (var_r30 < 0x26) {
        Hu3DModelPosSet(work->unk3C[var_r30].unk0, work->unk3C[var_r30].unk4.x, work->unk3C[var_r30].unk4.y, work->unk3C[var_r30].unk4.z);
        Hu3DModelRotSet(work->unk3C[var_r30].unk0, work->unk3C[var_r30].unk10.x, work->unk3C[var_r30].unk10.y, work->unk3C[var_r30].unk10.z);
        var_r30 += 1;
        goto loop_2;
    }
    fn_1_8C4(0);
    fn_1_106C();
    fn_1_1474();
    lbl_1_bss_C->unk98 += 1;
    lbl_1_bss_C[1].unk98 += 1;
}



void fn_1_44D8(M545Work *work) {
    M545Pl *temp_r4;
    M545Pl *temp_r4_10;
    M545Pl *temp_r4_11;
    M545Pl *temp_r4_12;
    M545Pl *temp_r4_13;
    M545Pl *temp_r4_2;
    M545Pl *temp_r4_3;
    M545Pl *temp_r4_4;
    M545Pl *temp_r4_5;
    M545Pl *temp_r4_6;
    M545Pl *temp_r4_7;
    M545Pl *temp_r4_8;
    M545Pl *temp_r4_9;
    s16 var_r26;
    s16 var_r27;
    s16 var_r28;
    s16 var_r29;
    s16 var_r29_2;
    s16 var_r31;
    s32 temp_r0;

    var_r31 = 0;
loop_35:
    if (var_r31 < 2) {
        if ((s16) work->unk4[var_r31].unk4 == 0) {
            if ((s32) (work->unk4[var_r31].unkC & 0x100) != 0) {
                temp_r4 = &lbl_1_bss_C[var_r31];
                temp_r4->unk60[0] += 1;
                temp_r4_2 = &lbl_1_bss_C[var_r31];
                temp_r4_2->unk78[0] += 1;
            }
            if ((s32) (work->unk4[var_r31].unkC & 0x200) != 0) {
                temp_r4_3 = &lbl_1_bss_C[var_r31];
                temp_r4_3->unk60[1] += 1;
                temp_r4_4 = &lbl_1_bss_C[var_r31];
                temp_r4_4->unk78[1] += 1;
            }
            if ((s32) (work->unk4[var_r31].unkC & 0x800) != 0) {
                temp_r4_5 = &lbl_1_bss_C[var_r31];
                temp_r4_5->unk60[3] += 1;
                temp_r4_6 = &lbl_1_bss_C[var_r31];
                temp_r4_6->unk78[3] += 1;
            }
            if ((s32) (work->unk4[var_r31].unkC & 0x400) != 0) {
                temp_r4_7 = &lbl_1_bss_C[var_r31];
                temp_r4_7->unk60[2] += 1;
                temp_r4_8 = &lbl_1_bss_C[var_r31];
                temp_r4_8->unk78[2] += 1;
            }
            if ((s32) (work->unk4[var_r31].unkC & 0x40) != 0) {
                temp_r4_9 = &lbl_1_bss_C[var_r31];
                temp_r4_9->unk60[4] += 1;
                temp_r4_10 = &lbl_1_bss_C[var_r31];
                temp_r4_10->unk78[4] += 1;
            }
            if ((s32) (work->unk4[var_r31].unkC & 0x20) != 0) {
                temp_r4_11 = &lbl_1_bss_C[var_r31];
                temp_r4_11->unk60[5] += 1;
                temp_r4_12 = &lbl_1_bss_C[var_r31];
                temp_r4_12->unk78[5] += 1;
            }
        }
        var_r28 = 1;
        var_r27 = 0;
loop_18:
        if (var_r28 <= (s16) lbl_1_bss_C[var_r31].unk4) {
            if ((s32) lbl_1_bss_C[var_r31].unk60[lbl_1_bss_980[var_r28].unk0] < 2) {
                var_r27 = 1;
            }
            var_r28 += 1;
            goto loop_18;
        }
        if (var_r27 == 1) {
            omVibrate(work->unk4[var_r31].unk0, 1, 0xC, 0);
        }
        temp_r4_13 = &lbl_1_bss_C[var_r31];
        temp_r0 = temp_r4_13->unk9C + 1;
        temp_r4_13->unk9C = temp_r0;
        if (temp_r0 >= 0x3C) {
            if ((s16) work->unk4[var_r31].unk4 != 0) {
                fn_1_762C(work, var_r31);
            }
            var_r26 = 1;
            var_r29 = 1;
loop_28:
            if (var_r29 <= (s16) lbl_1_bss_C[var_r31].unk4) {
                if ((s32) lbl_1_bss_C[var_r31].unk60[lbl_1_bss_980[var_r29].unk0] < 2) {
                    var_r26 = 0;
                }
                var_r29 += 1;
                goto loop_28;
            }
            var_r29_2 = 0;
loop_31:
            if (var_r29_2 < 6) {
                lbl_1_bss_C[var_r31].unk60[var_r29_2] = 0;
                var_r29_2 += 1;
                goto loop_31;
            }
            lbl_1_bss_C[var_r31].unk5E = var_r26;
            lbl_1_bss_C[var_r31].unk5C = 1;
            lbl_1_bss_C[var_r31].unk9C = 0;
            lbl_1_bss_C[var_r31].unkA0 = 0;
        } else {
            lbl_1_bss_C[var_r31].unk5C = 0;
        }
        var_r31 += 1;
        goto loop_35;
    }
}

s16 fn_1_499C(M545Work *work, s16 step) {
    f32 spC;
    f32 sp8;
    s16 temp_r3;
    s16 var_r29;
    s16 var_r30;

    var_r29 = 0;
    if ((s16) work->unk50[0].unk0 != 2) {
        lbl_1_bss_19C.unk50 = 0;
        var_r29 = 1;
    } else {
        if (step == 0) {
            sp8 = 13.0f;
            spC = 13.9f;
        } else if (step == 1) {
            sp8 = 1.0f;
            spC = 1.9f;
        }
        if (((work->unk50[0].unkC >= sp8) && (work->unk50[0].unkC <= spC)) || (temp_r3 = lbl_1_bss_19C.unk50, lbl_1_bss_19C.unk50 = temp_r3 + 1, ((temp_r3 > 0x258) != 0))) {
            lbl_1_bss_19C.unk50 = 0;
            var_r29 = 1;
        }
    }
    if ((step == 1) && (var_r29 == 1)) {
        var_r30 = 0;
loop_17:
        if (var_r30 < 2) {
            if ((s16) lbl_1_bss_C[var_r30].unk5E == 0) {
                omVibrate(work->unk4[var_r30].unk0, 0x40, 0xC, 0);
            }
            var_r30 += 1;
            goto loop_17;
        }
    }
    return var_r29;
}

s16 fn_1_4B2C(M545Work *work, s16 slot, s16 height) {
    Vec sp10;
    M545Model *spC;
    M545Model *sp8;
    M545Model *temp_r4_3;
    M545Model *temp_r4_4;
    Vec *temp_r4;
    Vec *temp_r4_2;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f27;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r27;
    s32 temp_r7;

    var_r27 = 0;
    temp_r7 = work->unkE8;
    switch (temp_r7) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(work->unk3C[lbl_1_bss_99C[0][slot]].unk0, 1U);
        Hu3DModelAttrReset(work->unk3C[lbl_1_bss_99C[1][slot]].unk0, 1U);
        Hu3DModelAttrReset(work->unk3C[lbl_1_bss_99C[0][slot] + 0xC].unk0, 1U);
        Hu3DModelAttrReset(work->unk3C[lbl_1_bss_99C[1][slot] + 0xC].unk0, 1U);
        lbl_1_bss_19C.unk8 = -8.259f;
        fn_1_2460(0);
        work->unkE8 += 1;
        break;
    case 1:
        spC = &work->unk3C[lbl_1_bss_99C[0][slot]];
        sp8 = &work->unk3C[lbl_1_bss_99C[1][slot]];
        temp_f31 = 600.0f + (100.0f * (f32) height);
        temp_f30 = 100.0f * (f32) height;
        lbl_1_bss_19C.unk8 -= 0.753f;
        temp_r4 = &lbl_1_bss_8D8[lbl_1_bss_99C[0][slot]];
        temp_r4->y += lbl_1_bss_19C.unk8;
        temp_r4_2 = &lbl_1_bss_8D8[lbl_1_bss_99C[1][slot]];
        temp_r4_2->y += lbl_1_bss_19C.unk8;
        if ((temp_f31 - temp_f30) > 0.0f) {
            var_f27 = temp_f31 - temp_f30;
        } else {
            var_f27 = temp_f31 - (-1.0f * temp_f30);
        }
        if ((temp_f31 - lbl_1_bss_8D8[lbl_1_bss_99C[0][slot]].y) > 0.0f) {
            var_f26 = temp_f31 - lbl_1_bss_8D8[lbl_1_bss_99C[0][slot]].y;
        } else {
            var_f26 = temp_f31 - (-1.0f * lbl_1_bss_8D8[lbl_1_bss_99C[0][slot]].y);
        }
        if (var_f27 <= var_f26) {
            lbl_1_bss_8D8[lbl_1_bss_99C[0][slot]].y = temp_f30;
            lbl_1_bss_8D8[lbl_1_bss_99C[1][slot]].y = temp_f30;
            work->unkE8 += 1;
            lbl_1_bss_C->unk4 += 1;
            lbl_1_bss_C[1].unk4 += 1;
        }
        lbl_1_bss_8->unk1C.y += (430.0f - 250.0f) / (6.0f * 30.0f);
        lbl_1_bss_8->unk34 += (1400.0f - 800.0f) / (6.0f * 30.0f);
        memcpy(&work->unk3C[lbl_1_bss_99C[0][slot] + 0xC].unk4, &work->unk3C[lbl_1_bss_99C[0][slot]].unk4, 0xC);
        memcpy(&work->unk3C[lbl_1_bss_99C[1][slot] + 0xC].unk4, &work->unk3C[lbl_1_bss_99C[1][slot]].unk4, 0xC);
        work->unk3C[lbl_1_bss_99C[0][slot] + 0xC].unk4.y = 101.0f;
        work->unk3C[lbl_1_bss_99C[1][slot] + 0xC].unk4.y = 101.0f;
        temp_r0 = lbl_1_bss_99C[0][slot];
        lbl_1_bss_19C.unkC[temp_r0] += 0.034f;
        temp_r3 = lbl_1_bss_99C[1][slot];
        lbl_1_bss_19C.unkC[temp_r3] += 0.034f;
        if (lbl_1_bss_19C.unkC[lbl_1_bss_99C[0][slot]] >= 1.0f) {
            lbl_1_bss_19C.unkC[lbl_1_bss_99C[0][slot]] = 1.0f;
            lbl_1_bss_19C.unkC[lbl_1_bss_99C[1][slot]] = 1.0f;
        }
        Hu3DModelTPLvlSet(work->unk3C[lbl_1_bss_99C[0][slot] + 0xC].unk0, lbl_1_bss_19C.unkC[lbl_1_bss_99C[0][slot]]);
        Hu3DModelTPLvlSet(work->unk3C[lbl_1_bss_99C[1][slot] + 0xC].unk0, lbl_1_bss_19C.unkC[lbl_1_bss_99C[1][slot]]);
        if ((s32) work->unkE8 == 2) {
            omVibrate(work->unk4[0].unk0, 0xC, 0xC, 0);
            omVibrate(work->unk4[1].unk0, 0xC, 0xC, 0);
            if (height != 0) {
                temp_r4_3 = work->unk3C;
                sp10.x = temp_r4_3[0x24].unk4.x;
                sp10.y = temp_r4_3[0x24].unk4.y;
                sp10.z = temp_r4_3[0x24].unk4.z;
                sp10.y = (lbl_1_bss_C->unk14.y - 60.0f) + (f32) (height * 0x64);
                sp10.z = lbl_1_bss_C->unk14.z - 110.0f;
                fn_1_1980(&sp10);
                sp10.x += -50.0f;
                fn_1_1980(&sp10);
                sp10.x += 100.0f;
                fn_1_1980(&sp10);
                temp_r4_4 = work->unk3C;
                sp10.x = temp_r4_4[0x25].unk4.x;
                sp10.y = temp_r4_4[0x25].unk4.y;
                sp10.z = temp_r4_4[0x25].unk4.z;
                sp10.y = (lbl_1_bss_C[1].unk14.y - 60.0f) + (f32) (height * 0x64);
                sp10.z = lbl_1_bss_C[1].unk14.z - 110.0f;
                fn_1_1980(&sp10);
                sp10.x += -50.0f;
                fn_1_1980(&sp10);
                sp10.x += 100.0f;
                fn_1_1980(&sp10);
                fn_1_2460((s16) (height + 1));
            } else {
                fn_1_2460(1);
            }
            work->unk50[0].unk4 = 0.0f;
            work->unk50[1].unk4 = 0.0f;
            lbl_1_bss_C->unk50 = 1;
            lbl_1_bss_C[1].unk50 = 1;
        }
        break;
    case 2:
        lbl_1_bss_C->unk8.y -= 0.016f;
        lbl_1_bss_C[1].unk8.y -= 0.016f;
        if (lbl_1_bss_C->unk8.y <= 0.92f) {
            work->unkE8 += 1;
        }
        Hu3DModelScaleSetV(work->unk3C[0x24].unk0, &lbl_1_bss_C->unk8);
        Hu3DModelScaleSetV(work->unk3C[0x25].unk0, &lbl_1_bss_C[1].unk8);
        break;
    case 3:
        lbl_1_bss_C->unk8.y += 0.016f;
        lbl_1_bss_C[1].unk8.y += 0.016f;
        if (lbl_1_bss_C->unk8.y >= 1.0f) {
            lbl_1_bss_19C.unk8 = 0.0f;
            work->unkE8 = 0;
            work->unk50[0].unk4 = 1.0f;
            work->unk50[1].unk4 = 1.0f;
            lbl_1_bss_C->unk50 = 1;
            lbl_1_bss_C[1].unk50 = 1;
            var_r27 = 1;
        }
        Hu3DModelScaleSetV(work->unk3C[0x24].unk0, &lbl_1_bss_C->unk8);
        Hu3DModelScaleSetV(work->unk3C[0x25].unk0, &lbl_1_bss_C[1].unk8);
        break;
    }
    return var_r27;
}

s16 fn_1_5794(M545Work *work, s16 player) {
    Vec sp8;
    M545Model *temp_r4_2;
    M545Pl *temp_r4;
    s16 var_r29;
    s16 var_r30;
    s32 temp_r0;

    var_r29 = 0;
    lbl_1_bss_C[player].unk50 = 1;
    temp_r4 = &lbl_1_bss_C[player];
    temp_r4->unk8.y -= 1.0f / 10.0f;
    if (lbl_1_bss_C[player].unk8.y <= 0.1f) {
        lbl_1_bss_C[player].unk8.x = 0.1f;
        lbl_1_bss_C[player].unk8.y = 0.1f;
        lbl_1_bss_C[player].unk8.z = 0.1f;
        var_r29 = 1;
    }
    Hu3DModelScaleSetV(work->unk3C[player + 0x24].unk0, &lbl_1_bss_C[player].unk8);
    if (var_r29 == 1) {
        temp_r4_2 = work->unk3C;
        temp_r0 = player + 0x24;
        sp8.x = temp_r4_2[temp_r0].unk4.x;
        sp8.y = temp_r4_2[temp_r0].unk4.y;
        sp8.z = temp_r4_2[temp_r0].unk4.z;
        sp8.z = lbl_1_bss_C[player].unk14.z - 40.0f;
        fn_1_1980(&sp8);
        sp8.x += -50.0f;
        fn_1_1980(&sp8);
        sp8.x += 100.0f;
        fn_1_1980(&sp8);
        lbl_1_bss_C[player].unk50 = 3;
        fn_1_24D8(9, 0x7F, (s16) ((player << 5) + 0x30));
        var_r30 = 0;
loop_5:
        if (var_r30 < (s16) lbl_1_bss_C[player].unk4) {
            lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].x = lbl_1_bss_C[player].unk14.x + lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].x;
            lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].y = 150.0f + (100.0f * (f32) var_r30);
            lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].z = lbl_1_bss_C[player].unk14.z + lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].z;
            var_r30 += 1;
            goto loop_5;
        }
    }
    return var_r29;
}

s16 fn_1_5BC4(M545Work *work, s16 player) {
    f32 sp8;
    M545Anim *temp_r31;
    M545Anim *temp_r31_2;
    M545Anim *temp_r31_3;
    M545Anim *temp_r31_4;
    Vec *temp_r4;
    Vec *temp_r4_2;
    Vec *temp_r4_3;
    Vec *temp_r6;
    f32 temp_f1;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f28;
    f32 var_f29;
    s16 temp_r3_3;
    s16 var_r27;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s32 temp_r3;
    u32 temp_r3_2;

    var_r27 = 0;
    sp8 = 50.0f;
    temp_r3 = work->unkEC;
    switch (temp_r3) {                              /* irregular */
    case 2:
        break;
    case 0:
        lbl_1_bss_19C.unk8 = 35.0f;
        temp_r31 = &work->unk50[player];
        temp_r31->unk28 = 1;
        temp_r31->unk2A = 3;
        temp_r31->unk30 = 0.0f;
        temp_r31->unk34 = 10.0f;
        temp_r31->unk2C = 0;
        temp_r31->unk20 = 0x40000001;
        lbl_1_bss_C[player].unk50 = 2;
        var_r30 = 0;
loop_10:
        if (var_r30 < (s16) lbl_1_bss_C[player].unk4) {
            lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].x = lbl_1_bss_C[player].unk14.x + lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].x;
            temp_r4 = &lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]];
            temp_r4->y += 10.0f;
            lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].z = lbl_1_bss_C[player].unk14.z + lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30]].z;
            var_r30 += 1;
            goto loop_10;
        }
        fn_1_2460((s16) (player + 0xA));
        work->unkEC += 1;
        break;
    case 1:
        temp_r31_2 = &work->unk50[player];
        if ((s16) temp_r31_2->unk28 == 0) {
            temp_r31_2->unk0 = 3;
            temp_r31_2->unk2 = 3;
            temp_r31_2->unk4 = 0.0f;
            lbl_1_bss_C[player].unk50 = 3;
            var_r30_2 = 0;
loop_15:
            if (var_r30_2 < (s16) lbl_1_bss_C[player].unk4) {
                lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_2]].y = lbl_1_bss_C[player].unk14.y + lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_2]].y;
                var_r30_2 += 1;
                goto loop_15;
            }
            work->unkEC += 1;
        }
        break;
    case 3:
        temp_r31_3 = &work->unk50[player];
        temp_r31_3->unk4 = 1.0f;
        temp_r31_3->unk28 = 1;
        temp_r31_3->unk2A = 0;
        temp_r31_3->unk30 = 0.0f;
        temp_r31_3->unk34 = 10.0f;
        temp_r31_3->unk2C = 0;
        temp_r31_3->unk20 = 0x40000001;
        work->unkEC += 1;
        break;
    case 4:
        if ((s16) work->unk50[player].unk28 == 0) {
            temp_r31_4 = &work->unk50[player];
            temp_r31_4->unk0 = 0;
            temp_r31_4->unk18 = 0x40000001;
            var_r27 = 1;
        }
        break;
    }
    if ((s32) work->unkEC == 2) {
        var_r30_3 = 0;
loop_37:
        if (var_r30_3 < (s16) lbl_1_bss_C[player].unk4) {
            temp_r4_2 = &lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]];
            temp_r4_2->y += lbl_1_bss_19C.unk8;
            temp_f31 = 250.0f + (f32) (var_r30_3 * 0x64);
            temp_f30 = 1300.0f + (f32) (var_r30_3 * 0x64);
            if (var_r30_3 != 0) {
                temp_r3_2 = (u32) var_r30_3 >> 0x1FU;
                if ((s32) (((var_r30_3 & 1) ^ temp_r3_2) - temp_r3_2) != 0) {
                    temp_r4_3 = &lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]];
                    temp_r4_3->x += 4.0f + (3.0f * (f32) ((s32) (((u32) var_r30_3 >> 0x1FU) + var_r30_3) >> 1));
                } else {
                    temp_r6 = &lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]];
                    temp_r6->x -= 4.0f + (3.0f * (f32) ((s32) (((u32) var_r30_3 >> 0x1FU) + var_r30_3) >> 1));
                }
            }
            if ((temp_f31 - temp_f30) > 0.0f) {
                var_f29 = temp_f31 - temp_f30;
            } else {
                var_f29 = temp_f31 - (-1.0f * temp_f30);
            }
            if ((temp_f31 - lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]].y) > 0.0f) {
                var_f28 = temp_f31 - lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]].y;
            } else {
                var_f28 = temp_f31 - (-1.0f * lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]].y);
            }
            if (var_f29 <= var_f28) {
                lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r30_3]].y = temp_f30;
                work->unkEC = 3;
            }
            temp_r3_3 = lbl_1_bss_99C[player][var_r30_3];
            temp_f1 = lbl_1_bss_19C.unkC[temp_r3_3] - 0.034f;
            lbl_1_bss_19C.unkC[temp_r3_3] = temp_f1;
            if (temp_f1 <= 0.0f) {
                lbl_1_bss_19C.unkC[lbl_1_bss_99C[player][var_r30_3]] = 0.0f;
            }
            Hu3DModelTPLvlSet(work->unk3C[lbl_1_bss_99C[player][var_r30_3] + 0xC].unk0, lbl_1_bss_19C.unkC[lbl_1_bss_99C[player][var_r30_3]]);
            var_r30_3 += 1;
            goto loop_37;
        }
        lbl_1_bss_19C.unk8 -= 0.4f;
    }
    return var_r27;
}

void fn_1_6590(M545Work *work) {
    switch ((s16) lbl_1_bss_C->unk4) {              /* irregular */
    case 2:
        fn_1_6668(work, 0.7f);
        return;
    case 3:
        fn_1_6668(work, 0.8f);
        return;
    case 4:
        fn_1_6668(work, 0.9f);
        return;
    case 5:
        fn_1_6668(work, 1.0f);
        return;
    case 6:
        fn_1_6668(work, 1.1f);
        return;
    }
}

void fn_1_6668(M545Work *work, f32 speed) {
    M545Anim *temp_r31;
    M545Anim *temp_r31_2;
    M545Anim *temp_r31_3;
    s16 var_r29;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;

    switch ((s16) lbl_1_bss_19C.unk2) {             /* irregular */
    case 0:
        var_r30 = 0;
loop_11:
        if (var_r30 < 2) {
            temp_r31 = &work->unk50[var_r30];
            temp_r31->unk28 = 1;
            temp_r31->unk2A = 2;
            temp_r31->unk30 = 0.0f;
            temp_r31->unk34 = 14.0f;
            temp_r31->unk2C = 0;
            temp_r31->unk20 = 0x40000001;
            lbl_1_bss_C[var_r30].unk50 = 1;
            var_r29 = 0;
loop_9:
            if (var_r29 < 6) {
                lbl_1_bss_C[var_r30].unkAC[var_r29] = (30.0f * (f32) var_r29) + (180.0f * (f32) var_r30);
                var_r29 += 1;
                goto loop_9;
            }
            var_r30 += 1;
            goto loop_11;
        }
        lbl_1_bss_19C.unk2 += 1;
        return;
    case 1:
        var_r30_2 = 0;
loop_17:
        if (var_r30_2 < 2) {
            if ((s16) work->unk50[var_r30_2].unk28 == 0) {
                temp_r31_2 = &work->unk50[var_r30_2];
                temp_r31_2->unk0 = 2;
                temp_r31_2->unk4 = speed;
                temp_r31_2->unkC = 7.0f * (f32) var_r30_2;
                temp_r31_2->unk18 = 0x40000001;
                lbl_1_bss_19C.unk2 = 2;
            }
            lbl_1_bss_C[var_r30_2].unk50 = 1;
            var_r30_2 += 1;
            goto loop_17;
        }
        return;
    case 2:
        var_r30_3 = 0;
loop_21:
        if (var_r30_3 < 2) {
            temp_r31_3 = &work->unk50[var_r30_3];
            temp_r31_3->unk4 = speed;
            lbl_1_bss_C[var_r30_3].unk50 = 1;
            fn_1_6BC4(work, var_r30_3, 1, temp_r31_3->unk4);
            var_r30_3 += 1;
            goto loop_21;
        }
        return;
    }
}


void fn_1_6BC4(M545Work *work, s16 player, s32 unused, f32 speed) {
    f32 sp8;
    M545Pl *temp_r3;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = speed;
    var_r31 = 0;
loop_2:
    if (var_r31 < (s16) lbl_1_bss_C[player].unk4) {
        lbl_1_bss_8D8[lbl_1_bss_99C[player][var_r31]].x = (f32) (1.5 * ((f64) (f32) var_r31 * sin((3.141592653589793 * (f64) lbl_1_bss_C[player].unkAC[var_r31]) / 180.0)));
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 6) {
        temp_r3 = &lbl_1_bss_C[player];
        temp_r3->unkAC[var_r31_2] += 20.0f * sp8;
        var_r31_2 += 1;
        goto loop_5;
    }
}

s32 fn_1_6D40(M545Work *work) {
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    s32 var_r31;

    var_r31 = 0;
    lbl_1_bss_8->unk1C.y += (250.0f - 430.0f) / 100.0f;
    if ((430.0f - 250.0f) > 0.0f) {
        var_f27 = 430.0f - 250.0f;
    } else {
        var_f27 = 430.0f - (-1.0f * 250.0f);
    }
    if ((430.0f - lbl_1_bss_8->unk1C.y) > 0.0f) {
        var_f26 = 430.0f - lbl_1_bss_8->unk1C.y;
    } else {
        var_f26 = 430.0f - (-1.0f * lbl_1_bss_8->unk1C.y);
    }
    if (var_f27 <= var_f26) {
        lbl_1_bss_8->unk1C.y = 250.0f;
    }
    lbl_1_bss_8->unk34 += (800.0f - 1400.0f) / 100.0f;
    if ((1400.0f - 800.0f) > 0.0f) {
        var_f25 = 1400.0f - 800.0f;
    } else {
        var_f25 = 1400.0f - (-1.0f * 800.0f);
    }
    if ((1400.0f - lbl_1_bss_8->unk34) > 0.0f) {
        var_f24 = 1400.0f - lbl_1_bss_8->unk34;
    } else {
        var_f24 = 1400.0f - (-1.0f * lbl_1_bss_8->unk34);
    }
    if (var_f25 <= var_f24) {
        lbl_1_bss_8->unk34 = 800.0f;
    }
    lbl_1_bss_8->unk10.x += (0.0f - -20.0f) / 100.0f;
    if ((-20.0f - 0.0f) > 0.0f) {
        var_f23 = -20.0f - 0.0f;
    } else {
        var_f23 = -20.0f - (-1.0f * 0.0f);
    }
    if ((-20.0f - lbl_1_bss_8->unk10.x) > 0.0f) {
        var_f22 = -20.0f - lbl_1_bss_8->unk10.x;
    } else {
        var_f22 = -20.0f - (-1.0f * lbl_1_bss_8->unk10.x);
    }
    if (var_f23 <= var_f22) {
        lbl_1_bss_8->unk10.x = 0.0f;
        var_r31 = 1;
    }
    return var_r31;
}

s32 fn_1_70E8(M545Work *work) {
    f32 temp_f30;
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    s16 temp_r3;
    s16 var_r29;
    s32 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = work->unkE0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) lbl_1_bss_19C.unk4C == -1) {
            var_r29 = 0xB4;
        } else {
            var_r29 = 0x3C;
        }
        temp_r3 = lbl_1_bss_19C.unk6;
        lbl_1_bss_19C.unk6 = temp_r3 + 1;
        if (temp_r3 > var_r29) {
            work->unkE0 += 1;
        }
        break;
    case 1:
        if ((s16) lbl_1_bss_19C.unk4C == -1) {
            work->unkE0 = 0x3E7;
        } else if (fn_1_5BC4(work, lbl_1_bss_19C.unk4C) != 0) {
            work->unkE0 += 1;
            lbl_1_bss_19C.unk3C = lbl_1_bss_8->unk1C.y;
            lbl_1_bss_19C.unk40 = lbl_1_bss_8->unk34;
        }
        break;
    case 2:
        lbl_1_bss_8->unk1C.y += (250.0f - lbl_1_bss_19C.unk3C) / 30.0f;
        if ((lbl_1_bss_19C.unk3C - 250.0f) > 0.0f) {
            var_f27 = lbl_1_bss_19C.unk3C - 250.0f;
        } else {
            var_f27 = lbl_1_bss_19C.unk3C - (-1.0f * 250.0f);
        }
        if ((lbl_1_bss_19C.unk3C - lbl_1_bss_8->unk1C.y) > 0.0f) {
            var_f26 = lbl_1_bss_19C.unk3C - lbl_1_bss_8->unk1C.y;
        } else {
            var_f26 = lbl_1_bss_19C.unk3C - (-1.0f * lbl_1_bss_8->unk1C.y);
        }
        if (var_f27 <= var_f26) {
            lbl_1_bss_8->unk1C.y = 250.0f;
        }
        temp_f30 = -150.0f + (300.0f * (f32) lbl_1_bss_19C.unk4C);
        lbl_1_bss_8->unk1C.x += (temp_f30 - 0.0f) / 30.0f;
        if ((0.0f - temp_f30) > 0.0f) {
            var_f25 = 0.0f - temp_f30;
        } else {
            var_f25 = 0.0f - (-1.0f * temp_f30);
        }
        if ((0.0f - lbl_1_bss_8->unk1C.x) > 0.0f) {
            var_f24 = 0.0f - lbl_1_bss_8->unk1C.x;
        } else {
            var_f24 = 0.0f - (-1.0f * lbl_1_bss_8->unk1C.x);
        }
        if (var_f25 <= var_f24) {
            lbl_1_bss_8->unk1C.x = temp_f30;
            work->unkE0 += 1;
            var_r30 = 1;
        }
        lbl_1_bss_8->unk34 += (550.0f - lbl_1_bss_19C.unk40) / 30.0f;
        if ((lbl_1_bss_19C.unk40 - 550.0f) > 0.0f) {
            var_f23 = lbl_1_bss_19C.unk40 - 550.0f;
        } else {
            var_f23 = lbl_1_bss_19C.unk40 - (-1.0f * 550.0f);
        }
        if ((lbl_1_bss_19C.unk40 - lbl_1_bss_8->unk34) > 0.0f) {
            var_f22 = lbl_1_bss_19C.unk40 - lbl_1_bss_8->unk34;
        } else {
            var_f22 = lbl_1_bss_19C.unk40 - (-1.0f * lbl_1_bss_8->unk34);
        }
        if (var_f23 <= var_f22) {
            lbl_1_bss_8->unk34 = 550.0f;
        }
        break;
    case 3:
        work->unkE0 = 0x3E7;
        work->unkE4 = 0;
        var_r30 = 1;
        break;
    default:
        var_r30 = 1;
        break;
    }
    return var_r30;
}

void fn_1_762C(M545Work *work, s16 player) {
    M545Pl *temp_r4;
    s16 temp_r28;
    s16 temp_r31;
    s16 var_r31;
    s16 var_r31_2;
    u32 var_r29;

    temp_r28 = work->unk4[player].unk4 - 1;
    var_r29 = frandmod(0x65U);
    temp_r31 = lbl_1_bss_C[player].unk4;
    if (temp_r31 >= 6) {
        temp_r4 = &lbl_1_bss_C[player];
        temp_r4->unk6 += 1;
    }
    if ((temp_r28 == 0) && (temp_r31 >= 3) && ((s16) lbl_1_bss_980[temp_r31].unk2 < 0x3C)) {
        var_r29 = 0x65;
    }
    if (((s16) lbl_1_data_2D8[temp_r28][lbl_1_bss_C[player].unk4 - 1] >= (s32) var_r29) && ((s16) lbl_1_bss_C[player].unk6 < 0x14)) {
        var_r31 = 0;
loop_10:
        if (var_r31 <= 5) {
            lbl_1_bss_C[player].unk60[var_r31] = 3;
            var_r31 += 1;
            goto loop_10;
        }
        return;
    }
    var_r31_2 = 0;
loop_14:
    if (var_r31_2 <= 5) {
        lbl_1_bss_C[player].unk60[var_r31_2] = 0;
        var_r31_2 += 1;
        goto loop_14;
    }
}



void ObjectSetup(void) {
    lbl_1_bss_8CC = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_8CC);
    fn_1_77EC(&lbl_1_bss_67C, lbl_1_bss_254, lbl_1_data_12C);
    lbl_1_bss_8 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x148, MEMORY_DEFAULT_NUM);
    memset((M545Snd *) lbl_1_bss_8, 0, 0x148);
    lbl_1_bss_4 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x3C, MEMORY_DEFAULT_NUM);
    memset((M545Snd *) lbl_1_bss_4, 0, 0x3C);
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x50, MEMORY_DEFAULT_NUM);
    memset((M545Snd *) lbl_1_bss_0, 0, sizeof(M545Shadow));
    fn_1_4A8(0);
    fn_1_E3C();
    fn_1_1344();
    fn_1_7A38(1);
    fn_1_7CE4(&lbl_1_data_28[Mp5CharNo(lbl_1_bss_67C.unk4[0].unk2)], &lbl_1_data_28[Mp5CharNo(lbl_1_bss_67C.unk4[1].unk2)]);
    fn_1_7D08(lbl_1_bss_240[0], lbl_1_bss_240[1]);
    fn_1_7D2C();
    fn_1_8454();
    omAddObjEx(lbl_1_bss_8CC, 0x7FDA, 0U, 0U, -1, fn_1_803C);
    omAddObjEx(lbl_1_bss_8CC, 0x7FDA, 0U, 0U, -1, fn_1_8580);
    omAddObjEx(lbl_1_bss_8CC, 0x7FDA, 0U, 0U, -1, fn_1_4A4);
    omAddObjEx(lbl_1_bss_8CC, 0x7FDA, 0U, 0U, -1, fn_1_88F0);
    Hu3DBGColorSet(0xBAU, 0xF5U, 0xFFU);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(2, 0x7D0);
    MgSeqModeDelaySet(7, 0xB4);
    MgSeqModeDelaySet(9, 0x3C);
}

void fn_1_2F0(s16 mode, s16 frameNo) {
    if (fn_1_26BC(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_324(s16 mode, s16 frameNo) {
    if (fn_1_2E88(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_358(s16 mode, s16 frameNo) {
    fn_1_2FE8(&lbl_1_bss_67C);
}

void fn_1_380(s16 mode, s16 frameNo) {
    if (fn_1_3030(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_3B4(s16 mode, s16 frameNo) {
    if (fn_1_3480(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_3E8(s16 mode, s16 frameNo) {
    if (fn_1_34EC(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_41C(s16 mode, s16 frameNo) {
    if (fn_1_3538(&lbl_1_bss_67C) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_450(s16 mode, s16 frameNo) {
    fn_1_3600(&lbl_1_bss_67C);
}

void fn_1_478(s16 mode, s16 frameNo) {
    if (fn_1_3638() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_4A4(omObjData *obj) {

}

void fn_1_4A8(s16 cam) {
    lbl_1_bss_8[cam].unk0 = (s32) cam;
    lbl_1_bss_8[cam].unk1C.x = lbl_1_data_178[cam].unk0.x;
    lbl_1_bss_8[cam].unk1C.y = lbl_1_data_178[cam].unk0.y;
    lbl_1_bss_8[cam].unk1C.z = lbl_1_data_178[cam].unk0.z;
    lbl_1_bss_8[cam].unk10.x = lbl_1_data_178[cam].unkC.x;
    lbl_1_bss_8[cam].unk10.y = lbl_1_data_178[cam].unkC.y;
    lbl_1_bss_8[cam].unk10.z = lbl_1_data_178[cam].unkC.z;
    lbl_1_bss_8[cam].unk34 = lbl_1_data_178[cam].unk18;
    lbl_1_bss_8[cam].unk38 = lbl_1_data_178[cam].unk1C;
    lbl_1_bss_8[cam].unk3C = lbl_1_data_178[cam].unk20;
    lbl_1_bss_8[cam].unk40 = lbl_1_data_178[cam].unk24;
    lbl_1_bss_8[cam].unk44 = lbl_1_data_178[cam].unk28;
    lbl_1_bss_8[cam].unk48 = lbl_1_data_178[cam].unk2C;
    lbl_1_bss_8[cam].unk4C = lbl_1_data_178[cam].unk30;
    Hu3DCameraCreate((s32) lbl_1_data_248[cam]);
    Hu3DCameraViewportSet((s32) lbl_1_data_248[cam], lbl_1_bss_8[cam].unk3C, lbl_1_bss_8[cam].unk40, lbl_1_bss_8[cam].unk44, lbl_1_bss_8[cam].unk48, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet((s32) lbl_1_data_248[cam], lbl_1_bss_8[cam].unk4C, 20.0f, 30000.0f, lbl_1_bss_8[cam].unk38);
    fn_1_8C4(cam);
}

void fn_1_8C4(s16 cam) {
    f32 sp8;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    f64 temp_f31_4;

    temp_f31 = sin((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.y) / 180.0);
    lbl_1_bss_8[cam].unk4.x = (f32) ((f64) lbl_1_bss_8[cam].unk1C.x + ((f64) lbl_1_bss_8[cam].unk34 * (cos((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0) * temp_f31)));
    lbl_1_bss_8[cam].unk4.y = (f32) ((f64) lbl_1_bss_8[cam].unk1C.y + ((f64) lbl_1_bss_8[cam].unk34 * -sin((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0)));
    temp_f31_2 = cos((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.y) / 180.0);
    lbl_1_bss_8[cam].unk4.z = (f32) ((f64) lbl_1_bss_8[cam].unk1C.z + ((f64) lbl_1_bss_8[cam].unk34 * (cos((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0) * temp_f31_2)));
    temp_f31_3 = sin((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.y) / 180.0);
    lbl_1_bss_8[cam].unk28.x = (f32) (sin((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0) * temp_f31_3);
    lbl_1_bss_8[cam].unk28.y = (f32) cos((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0);
    temp_f31_4 = cos((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.y) / 180.0);
    lbl_1_bss_8[cam].unk28.z = (f32) (sin((3.141592653589793 * (f64) lbl_1_bss_8[cam].unk10.x) / 180.0) * temp_f31_4);
    sp8 = lbl_1_bss_8[cam].unk1C.z;
    Hu3DCameraPosSet((s32) lbl_1_data_248[cam], lbl_1_bss_8[cam].unk4.x, lbl_1_bss_8[cam].unk4.y, lbl_1_bss_8[cam].unk4.z, lbl_1_bss_8[cam].unk28.x, lbl_1_bss_8[cam].unk28.y, lbl_1_bss_8[cam].unk28.z, lbl_1_bss_8[cam].unk1C.x, lbl_1_bss_8[cam].unk1C.y, lbl_1_bss_8[cam].unk1C.z);
}

void fn_1_E3C(void) {
    Hu3DLighInit();
    lbl_1_bss_4->unk4.x = 0.0f;
    lbl_1_bss_4->unk4.y = 0.0f;
    lbl_1_bss_4->unk4.z = 0.0f;
    lbl_1_bss_4->unk1C.x = 0.0f;
    lbl_1_bss_4->unk1C.y = 0.0f;
    lbl_1_bss_4->unk1C.z = 0.0f;
    lbl_1_bss_4->unk10.x = -23.0f;
    lbl_1_bss_4->unk10.y = 0.0f;
    lbl_1_bss_4->unk10.z = 0.0f;
    lbl_1_bss_4->unk34 = 1000.0f;
    lbl_1_bss_4->unk38.r = 0xFF;
    lbl_1_bss_4->unk38.g = 0xFF;
    lbl_1_bss_4->unk38.b = 0xFF;
    lbl_1_bss_4->unk38.a = 0xFF;
    VECSubtract(&lbl_1_bss_4->unk1C, &lbl_1_bss_4->unk4, &lbl_1_bss_4->unk28);
    lbl_1_bss_4->unk0 = Hu3DGLightCreateV(&lbl_1_bss_4->unk4, &lbl_1_bss_4->unk28, &lbl_1_bss_4->unk38);
    fn_1_106C();
    Hu3DGLightStaticSet(lbl_1_bss_4->unk0, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_4->unk0);
}

void fn_1_106C(void) {
    f64 temp_f31;
    f64 temp_f31_2;

    temp_f31 = sin((3.141592653589793 * (f64) lbl_1_bss_4->unk10.y) / 180.0);
    lbl_1_bss_4->unk4.x = (f32) ((f64) lbl_1_bss_4->unk1C.x + ((f64) lbl_1_bss_4->unk34 * (cos((3.141592653589793 * (f64) lbl_1_bss_4->unk10.x) / 180.0) * temp_f31)));
    lbl_1_bss_4->unk4.y = (f32) ((f64) lbl_1_bss_4->unk1C.y + ((f64) lbl_1_bss_4->unk34 * -sin((3.141592653589793 * (f64) lbl_1_bss_4->unk10.x) / 180.0)));
    temp_f31_2 = cos((3.141592653589793 * (f64) lbl_1_bss_4->unk10.y) / 180.0);
    lbl_1_bss_4->unk4.z = (f32) ((f64) lbl_1_bss_4->unk1C.z + ((f64) lbl_1_bss_4->unk34 * (cos((3.141592653589793 * (f64) lbl_1_bss_4->unk10.x) / 180.0) * temp_f31_2)));
    VECSubtract(&lbl_1_bss_4->unk1C, &lbl_1_bss_4->unk4, &lbl_1_bss_4->unk28);
    VECNormalize(&lbl_1_bss_4->unk28, &lbl_1_bss_4->unk28);
    Hu3DGLightPosSetV(lbl_1_bss_4->unk0, &lbl_1_bss_4->unk4, &lbl_1_bss_4->unk28);
    Hu3DGLightColorSet(lbl_1_bss_4->unk0, lbl_1_bss_4->unk38.r, lbl_1_bss_4->unk38.g, lbl_1_bss_4->unk38.b, lbl_1_bss_4->unk38.a);
}

void fn_1_1344(void) {
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_0->unkC.x = -90.0f;
    lbl_1_bss_0->unkC.y = 0.0f;
    lbl_1_bss_0->unkC.z = 0.0f;
    lbl_1_bss_0->unk18.x = 0.0f;
    lbl_1_bss_0->unk18.y = 0.0f;
    lbl_1_bss_0->unk18.z = -250.0f;
    lbl_1_bss_0->unk4C = 0.25f;
    lbl_1_bss_0->unk48 = 1500.0f;
    Hu3DShadowSizeSet(0xC8U);
    fn_1_1474();
}

void fn_1_1474(void) {
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    f64 temp_f31_4;

    temp_f31 = sin((3.141592653589793 * (f64) lbl_1_bss_0->unkC.y) / 180.0);
    lbl_1_bss_0->unk0.x = (f32) ((f64) lbl_1_bss_0->unk18.x + ((f64) lbl_1_bss_0->unk48 * (cos((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0) * temp_f31)));
    lbl_1_bss_0->unk0.y = (f32) ((f64) lbl_1_bss_0->unk18.y + ((f64) lbl_1_bss_0->unk48 * -sin((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0)));
    temp_f31_2 = cos((3.141592653589793 * (f64) lbl_1_bss_0->unkC.y) / 180.0);
    lbl_1_bss_0->unk0.z = (f32) ((f64) lbl_1_bss_0->unk48 * (cos((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0) * temp_f31_2));
    temp_f31_3 = sin((3.141592653589793 * (f64) lbl_1_bss_0->unkC.y) / 180.0);
    lbl_1_bss_0->unk30.x = (f32) (sin((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0) * temp_f31_3);
    lbl_1_bss_0->unk30.y = (f32) cos((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0);
    temp_f31_4 = cos((3.141592653589793 * (f64) lbl_1_bss_0->unkC.y) / 180.0);
    lbl_1_bss_0->unk30.z = (f32) (sin((3.141592653589793 * (f64) lbl_1_bss_0->unkC.x) / 180.0) * temp_f31_4);
    Hu3DShadowTPLvlSet(lbl_1_bss_0->unk4C);
    Hu3DShadowPosSet(&lbl_1_bss_0->unk0, &lbl_1_bss_0->unk30, &lbl_1_bss_0->unk18);
}

void fn_1_17EC(void) {
    ANIMDATA *temp_r27;
    s16 var_r28;
    s16 var_r29;
    HU3DPARTICLE *temp_r31;
    HU3DPARTICLEDATA *var_r30;

    var_r29 = 0;
loop_2:
    if (var_r29 < 0x10) {
        lbl_1_bss_8D4 = -1;
        var_r29 += 1;
        goto loop_2;
    }
    temp_r27 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M545, 19), MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_8D0 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x2300, MEMORY_DEFAULT_NUM);
    lbl_1_bss_8D4 = Hu3DParticleCreate(temp_r27, 0xA0);
    Hu3DParticleHookSet(lbl_1_bss_8D4, fn_1_1F20);
    Hu3DParticleBlendModeSet(lbl_1_bss_8D4, 1U);
    Hu3DModelLayerSet(lbl_1_bss_8D4, 4);
    Hu3DModelCameraSet(lbl_1_bss_8D4, 1U);
    Hu3DModelAttrSet(lbl_1_bss_8D4, 1U);
    Hu3DModelAttrReset(lbl_1_bss_8D4, 1U);
    temp_r31 = Hu3DData[lbl_1_bss_8D4].hookData;
    temp_r31->emitCnt = 0;
    temp_r31->work = (void *) lbl_1_bss_8D0;
    temp_r31->count = 0;
    var_r28 = 0;
    var_r30 = temp_r31->data;
loop_5:
    if (var_r28 < (s16) temp_r31->maxCnt) {
        var_r30->scale = 0.0f;
        var_r28 += 1;
        var_r30++;
        goto loop_5;
    }
}

void fn_1_1980(Vec *pos) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    s16 sp8;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 var_r31;

    sp8 = 0x10;
    var_r31 = 0;
loop_2:
    if (var_r31 < 0xC) {
        temp_f31 = (f32) (1.0f * (6.0 + (f64) frandmod(6U)));
        lbl_1_data_268.unkC.x = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) (30.0f * (f32) var_r31)) / 180.0));
        lbl_1_data_268.unkC.y = 0.0f;
        lbl_1_data_268.unkC.z = (f32) ((f64) temp_f31 * cos((3.141592653589793 * (f64) (30.0f * (f32) var_r31)) / 180.0));
        lbl_1_data_268.unk30 = (f32) (s16) (-frandmod(6U) - 7);
        temp_f31_2 = (f32) (1.0f * (20.0 + (f64) frandmod(0x14U)));
        spC = (f32) ((f64) pos->x + (1.0f * (20.0 * sin((3.141592653589793 * (f64) (30.0f * (f32) var_r31)) / 180.0))));
        sp10 = pos->y + (10.0f * 1.0f);
        sp14 = (f32) ((f64) pos->z + (1.0f * (20.0 * cos((3.141592653589793 * (f64) (30.0f * (f32) var_r31)) / 180.0))));
        lbl_1_data_268.unk24 = (f32) (0.01 * (f64) frandmod(0x14U));
        fn_1_1D4C(&lbl_1_data_268, spC, sp10, sp14, temp_f31_2);
        var_r31 += 1;
        goto loop_2;
    }
}

s16 fn_1_1D4C(M545Part *tmpl, f32 x, f32 y, f32 z, f32 scale) {
    s16 var_r28;
    s16 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    var_r28 = -1;
    temp_r30 = Hu3DData[lbl_1_bss_8D4].hookData;
    var_r31 = temp_r30->data + temp_r30->emitCnt;
    var_r29 = temp_r30->emitCnt;
loop_3:
    if (var_r29 < (s16) temp_r30->maxCnt) {
        if (var_r31->scale != 0.0f) {
            var_r29 += 1;
            var_r31++;
            goto loop_3;
        }
    }
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        var_r31 = temp_r30->data;
        var_r29 = 0;
loop_8:
        if (var_r29 < (s16) temp_r30->maxCnt) {
            if (var_r31->scale != 0.0f) {
                var_r29 += 1;
                var_r31++;
                goto loop_8;
            }
        }
    }
    if (var_r29 != (s16) temp_r30->maxCnt) {
        memcpy((M545Part *) temp_r30->work + var_r29, tmpl, sizeof(M545Part));
        var_r31->pos.x = x;
        var_r31->pos.y = y;
        var_r31->pos.z = z;
        var_r31->vel.x = (f32) tmpl->unkC.x;
        var_r31->vel.y = (f32) tmpl->unkC.y;
        var_r31->vel.z = (f32) tmpl->unkC.z;
        var_r31->color.r = (u8) tmpl->unk4[0];
        var_r31->color.g = (u8) tmpl->unk4[1];
        var_r31->color.b = (u8) tmpl->unk4[2];
        var_r31->color.a = (u8) tmpl->unk4[3];
        var_r31->scaleBase = scale;
        var_r31->scale = scale;
        var_r31->parManId = -1;
        temp_r30->emitCnt = var_r29;
        var_r28 = var_r29;
    }
    return var_r28;
}

static s16 M545ColorStep(u8 cur, const M545Part *w, s32 k) {
    s16 v = (s16) ((f32) cur + (w->unk34 * (f32) (w->unk8[k] - w->unk4[k])));
    return v < 0 ? 0 : v > 0xFF ? 0xFF : v;
}

void fn_1_1F20(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    M545Part *work;
    s16 temp_r29;
    s16 var_r28;

    work = particleP->work;
    var_r31 = particleP->data;
    var_r31->time = 0;
    for (var_r28 = 0; var_r28 < (s16) particleP->maxCnt; var_r28++, var_r31++) {
        if (var_r31->scale != 0.0f) {
            var_r31->vel.x *= work[var_r28].unk18.x;
            var_r31->vel.y *= work[var_r28].unk18.y;
            var_r31->vel.z *= work[var_r28].unk18.z;
            VECAdd(&var_r31->vel, &var_r31->pos, &var_r31->pos);
            var_r31->vel.y += work[var_r28].unk24;
            var_r31->color.r = (u8) M545ColorStep(var_r31->color.r, &work[var_r28], 0);
            var_r31->color.g = (u8) M545ColorStep(var_r31->color.g, &work[var_r28], 1);
            var_r31->color.b = (u8) M545ColorStep(var_r31->color.b, &work[var_r28], 2);
            temp_r29 = (s16) ((f32) var_r31->color.a + work[var_r28].unk30);
            if (temp_r29 < 1) {
                var_r31->scale = 0.0f;
            }
            var_r31->color.a = (u8) temp_r29;
            if (var_r31->scale != 0.0f) {
                var_r31->scale = var_r31->scaleBase;
                var_r31->scaleBase += work[var_r28].unk2C;
                if (var_r31->scaleBase <= 0.01f) {
                    var_r31->scale = 0.0f;
                }
            }
            var_r31->time += 1;
        }
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}


void fn_1_2368(void) {
    lbl_1_bss_19C.unk54 = HuAudBGMPlay(0x3B);
}

void fn_1_2398(s16 arg0, s16 arg1) {
    s16 spA;
    s16 sp8;
    s16 var_r31;

    sp8 = arg0;
    spA = arg1;
    if (sp8 != 0) {
        var_r31 = (s16) lbl_1_bss_19C.unk54;
    } else {
        var_r31 = (s16) lbl_1_bss_19C.unk58;
    }
    HuAudSStreamFadeOut((s32) var_r31, (s32) spA);
}


void fn_1_2460(s16 arg0) {
    lbl_1_bss_19C.unk8C[arg0] = 1;
    lbl_1_bss_19C.unk5C[arg0] = HuAudFXPlay((s32) lbl_1_data_2A0[arg0]);
}

void fn_1_24D8(s16 arg0, s16 arg1, s16 arg2) {
    s16 spA;
    s16 sp8;

    sp8 = arg1;
    spA = arg2;
    lbl_1_bss_19C.unk8C[arg0] = 1;
    lbl_1_bss_19C.unk5C[arg0] = HuAudFXPlayVolPan((s32) lbl_1_data_2A0[arg0], arg1, arg2);
}




void fn_1_77EC(M545Work *work, M545Model *models, u32 *dataNums) {
    u32 *sp10;
    M545Model *spC;
    M545Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_9B8 = sp8;
    memset((M545Snd *) lbl_1_bss_9B8, 0, sizeof(M545Work));
    lbl_1_bss_9B8->unk3C = spC;
    lbl_1_bss_9B8->unkD8 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_9B8->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_9B8->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_9B8->unk4[var_r31_2].unk0].character;
        lbl_1_bss_9B8->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_9B8->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_9B8->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_9B8->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_9B8->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_7A38(s16 arg0) {
    s16 sp8;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r31;

    sp8 = arg0;
    lbl_1_bss_9B8->unkDC = sp8;
    var_r31 = 0;
loop_4:
    if (var_r31 < 0xC) {
        temp_r0 = var_r31 + 0x18;
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_9B8->unkD8[var_r31 + 0x7], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_9B8->unk3C[temp_r0].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DModelLayerSet(temp_r3, 0);
        Hu3DModelPosSetV(temp_r3, &lbl_1_data_310[var_r31]);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(temp_r3, 0.0f);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        lbl_1_bss_9B8->unk3C[temp_r0].unk4.x = lbl_1_data_310[var_r31].x;
        lbl_1_bss_9B8->unk3C[temp_r0].unk4.y = lbl_1_data_310[var_r31].y;
        lbl_1_bss_9B8->unk3C[temp_r0].unk4.z = lbl_1_data_310[var_r31].z;
        lbl_1_bss_9B8->unk3C[temp_r0].unk10.x = 0.0f;
        lbl_1_bss_9B8->unk3C[temp_r0].unk10.y = 0.0f;
        lbl_1_bss_9B8->unk3C[temp_r0].unk10.z = 0.0f;
        Hu3DModelAttrReset(temp_r3, 1U);
        if (var_r31 == 0) {
            Hu3DModelShadowMapSet(temp_r3);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_7CE4(M545Char *chr0, M545Char *chr1) {
    lbl_1_bss_9B8->unk40[0] = chr0;
    lbl_1_bss_9B8->unk40[1] = chr1;
}

void fn_1_7D08(s16 *mot0, s16 *mot1) {
    lbl_1_bss_9B8->unk48[0] = mot0;
    lbl_1_bss_9B8->unk48[1] = mot1;
}

void fn_1_7D2C(void) {
    M545Anim *temp_r30;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk0 = CharModelCreate(lbl_1_bss_9B8->unk4[var_r31].unk2, 1);
        Hu3DModelPosSet(lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk0, -150.0f + (300.0f * (f32) var_r31), 100.0f, 0.0f);
        CharModelFxFlagSet(lbl_1_bss_9B8->unk4[var_r31].unk2, 1);
        Hu3DModelLayerSet(lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk0, 2);
        Hu3DModelShadowSet(lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk0);
        CharModelStepFxSet(lbl_1_bss_9B8->unk4[var_r31].unk2, 1);
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk4.x = -150.0f + (300.0f * (f32) var_r31);
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk4.y = 100.0f;
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk4.z = 0.0f;
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk10.x = 0.0f;
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk10.y = 0.0f;
        lbl_1_bss_9B8->unk3C[var_r31 + 0x24].unk10.z = 0.0f;
        temp_r30 = &lbl_1_bss_9B8->unk50[var_r31];
        temp_r30->unk0 = 0;
        temp_r30->unk4 = 1.0f;
        temp_r30->unk18 = 0x40000001;
        temp_r30->unk20 = 0;
        temp_r30->unkC = 0.0f;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_803C(omObjData *obj) {
    s32 var_r31;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_11:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_9B8->unk4[var_r31].unk4 != 0) {
            memset((M545Snd *) &lbl_1_bss_9B8->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_9B8->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_9B8->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_9B8->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_9B8->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_9B8->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_9B8->unk4[var_r31].unk10;
            }
            lbl_1_bss_9B8->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_9B8->unk4[var_r31].unk14 = (s8) (u8) HuPadStkY[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkX[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk16 = (s8) (u8) HuPadSubStkY[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk17 = HuPadTrigL[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk18 = HuPadTrigR[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk19 = HuPadDStk[lbl_1_bss_9B8->unk4[var_r31].unk6];
            lbl_1_bss_9B8->unk4[var_r31].unk1A = HuPadDStkRep[lbl_1_bss_9B8->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_11;
    }
}

static const s32 sDkMot[5] = { 0, 132, 132, 132, 23 };

void fn_1_8454(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 5) {
            lbl_1_bss_9B8->unk48[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_9B8->unk4[var_r31].unk2, lbl_1_bss_9B8->unk40[var_r31]->unk0[var_r30], sDkMot[var_r30]);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 2) {
        lbl_1_bss_9B8->unk50[var_r31_2].unk2 = -1;
        lbl_1_bss_9B8->unk50[var_r31_2].unk8 = -1.0f;
        var_r31_2 += 1;
        goto loop_8;
    }
}

void fn_1_8580(omObjData *obj) {
    M545Anim *temp_r31;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 var_r29;

    var_r29 = 0;
loop_24:
    if (var_r29 < 2) {
        temp_r31 = &lbl_1_bss_9B8->unk50[var_r29];
        temp_r0 = var_r29 + 0x24;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_9B8->unk3C[temp_r0].unk0, lbl_1_bss_9B8->unk48[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_9B8->unk3C[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_9B8->unk3C[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_9B8->unk3C[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_9B8->unk3C[temp_r0].unk0, temp_r31->unk20);
            temp_r31->unk20 = 0;
            temp_r31->unk18 = 0;
            temp_r31->unk1C = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_9B8->unk3C[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r0_2 = temp_r31->unk28;
        switch (temp_r0_2) {                        /* irregular */
        case 0:
            break;
        case 1:
            Hu3DMotionShiftSet(lbl_1_bss_9B8->unk3C[temp_r0].unk0, lbl_1_bss_9B8->unk48[var_r29][temp_r31->unk2A], temp_r31->unk30, temp_r31->unk34, temp_r31->unk2C);
            temp_r31->unk3C = Hu3DMotionShiftMaxTimeGet(lbl_1_bss_9B8->unk3C[temp_r0].unk0);
            temp_r31->unk28 = 2;
            break;
        case 2:
            temp_r31->unk38 = Hu3DMotionShiftTimeGet(lbl_1_bss_9B8->unk3C[temp_r0].unk0);
            if (((u32) (temp_r31->unk2C & 0x40000001) == 0) && (temp_r31->unk38 >= (temp_r31->unk34 - 1.0f))) {
                temp_r31->unk28 = 3;
            }
            break;
        case 3:
            temp_r31->unk28 = 0;
            temp_r31->unk2 = -1;
            temp_r31->unk8 = -1.0f;
            break;
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_9B8->unk3C[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        temp_r31->unk24 = Hu3DMotionEndCheck(lbl_1_bss_9B8->unk3C[temp_r0].unk0);
        var_r29 += 1;
        goto loop_24;
    }
}

void fn_1_88F0(omObjData *obj) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        lbl_1_data_3A0[var_r31]();
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_8944(void) {
    M545Model *temp_r3;
    s32 temp_r0;
    s32 temp_r3_2;

    temp_r3 = lbl_1_bss_9B8->unk3C;
    if ((s32) lbl_1_bss_9B8->unk130 == 0) {
        temp_r0 = lbl_1_bss_9B8->unk13C;
        switch (temp_r0) {                          /* irregular */
        case 0:
            lbl_1_bss_9B8->unk134 = (rand8() % 120) + 0xB4;
            lbl_1_bss_9B8->unk13C = 1;
            lbl_1_bss_9B8->unk154 = 0.4f;
            Hu3DMotionSpeedSet(temp_r3[0x1B].unk0, lbl_1_bss_9B8->unk154);
            temp_r3[0x1B].unk10.y = -60.0f;
            return;
        case 1:
            temp_r3_2 = lbl_1_bss_9B8->unk134;
            lbl_1_bss_9B8->unk134 = temp_r3_2 - 1;
            if (temp_r3_2 < 0) {
                lbl_1_bss_9B8->unk13C += 1;
                lbl_1_bss_9B8->unk134 = 0;
                lbl_1_bss_9B8->unk150 = temp_r3[0x1B].unk10.y;
                lbl_1_bss_9B8->unk138 = 0x78;
                lbl_1_bss_9B8->unk154 = (f32) ((rand8() % 10) + 0x1E);
                if (lbl_1_bss_9B8->unk150 > -45.0f) {
                    lbl_1_bss_9B8->unk154 = -lbl_1_bss_9B8->unk154;
                    return;
                }
            }
            break;
        case 2:
            lbl_1_bss_9B8->unk134 += 1;
            Hu3DMotionSpeedSet(temp_r3[0x1B].unk0, (f32) (0.4 + (0.5 * sin((3.141592653589793 * (f64) ((lbl_1_bss_9B8->unk134 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_9B8->unk134 == 0x28) {
                lbl_1_bss_9B8->unk134 = 0;
                lbl_1_bss_9B8->unk13C += 1;
                return;
            }
            break;
        case 3:
            lbl_1_bss_9B8->unk134 += 1;
            Hu3DMotionSpeedSet(temp_r3[0x1B].unk0, (f32) (0.8 + (0.2 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_9B8->unk134 * 0xB4) / (s32) lbl_1_bss_9B8->unk138)) / 180.0))));
            temp_r3[0x1B].unk10.y = (f32) ((f64) lbl_1_bss_9B8->unk150 + ((f64) lbl_1_bss_9B8->unk154 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_9B8->unk134 * 0x5A) / (s32) lbl_1_bss_9B8->unk138)) / 180.0)));
            if ((s32) lbl_1_bss_9B8->unk134 == (s32) lbl_1_bss_9B8->unk138) {
                temp_r3[0x1B].unk10.y = lbl_1_bss_9B8->unk150 + lbl_1_bss_9B8->unk154;
                lbl_1_bss_9B8->unk13C += 1;
                lbl_1_bss_9B8->unk134 = 0;
                return;
            }
            break;
        case 4:
            lbl_1_bss_9B8->unk134 += 1;
            Hu3DMotionSpeedSet(temp_r3[0x1B].unk0, (f32) (0.8 - (0.4 * sin((3.141592653589793 * (f64) ((lbl_1_bss_9B8->unk134 * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_9B8->unk134 == 0x28) {
                lbl_1_bss_9B8->unk134 = (rand8() % 120) + 0xB4;
                lbl_1_bss_9B8->unk13C = 1;
            }
            break;
        }
    }
}

void fn_1_8F7C(void) {
    M545Model *temp_r3;
    M545Model *temp_r3_2;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_9B8->unk3C;
    temp_r3_2 = lbl_1_bss_9B8->unk3C;
    if ((s32) lbl_1_bss_9B8->unk160 == 0) {
        temp_r3[0x19].unk10.y = 30.0f;
        temp_r3_2[0x1A].unk10.y = 30.0f;
        temp_r0 = lbl_1_bss_9B8->unk16C;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) lbl_1_bss_9B8->unk13C == 2) {
                lbl_1_bss_9B8->unk164 = 0;
                lbl_1_bss_9B8->unk16C += 1;
                lbl_1_bss_9B8->unk180 = 20.0f;
                lbl_1_bss_9B8->unk184 = 5.0f;
                lbl_1_bss_9B8->unk188 = -5.0f;
                return;
            }
            break;
        case 1:
            lbl_1_bss_9B8->unk164 += 1;
            temp_r3[0x19].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_9B8->unk180 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk164 * lbl_1_bss_9B8->unk184)) / 180.0)));
            temp_r3_2[0x1A].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_9B8->unk180 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk164 * lbl_1_bss_9B8->unk188)) / 180.0)));
            if ((s32) lbl_1_bss_9B8->unk13C == 4) {
                lbl_1_bss_9B8->unk16C += 1;
                lbl_1_bss_9B8->unk168 = 0;
                return;
            }
            break;
        case 2:
            lbl_1_bss_9B8->unk164 += 1;
            lbl_1_bss_9B8->unk168 += 1;
            if ((s32) lbl_1_bss_9B8->unk168 > 0x28) {
                lbl_1_bss_9B8->unk168 = 0x28;
            }
            lbl_1_bss_9B8->unk180 = (f32) (20.0 - (20.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_9B8->unk168 * 0x5A) / 40)) / 180.0)));
            temp_r3[0x19].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_9B8->unk180 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk164 * lbl_1_bss_9B8->unk184)) / 180.0)));
            temp_r3_2[0x1A].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_9B8->unk180 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk164 * lbl_1_bss_9B8->unk188)) / 180.0)));
            if ((s32) lbl_1_bss_9B8->unk13C == 1) {
                lbl_1_bss_9B8->unk16C = 0;
            }
            break;
        }
    }
}

void fn_1_94C8(void) {
    Mtx sp8;
    Mtx sp38;
    M545Model *temp_r30;
    M545Model *temp_r31;
    s32 temp_r3;

    temp_r31 = &lbl_1_bss_9B8->unk3C[0x1C];
    temp_r30 = &lbl_1_bss_9B8->unk3C[0x1D];
    if ((s32) lbl_1_bss_9B8->unk190 == 0) {
        MTXIdentity(sp38);
        MTXRotRad(sp8, 0x79, -0.7853982f);
        MTXConcat(sp38, sp8, sp38);
        temp_r31->unk10.y = 30.0f;
        temp_r3 = lbl_1_bss_9B8->unk19C;
        switch (temp_r3) {                          /* irregular */
        case 0:
            temp_r30->unk10.y = -45.0f;
            if ((s32) lbl_1_bss_9B8->unk13C == 2) {
                lbl_1_bss_9B8->unk1B0 = 10.0f;
                lbl_1_bss_9B8->unk1B4 = 5.0f;
                lbl_1_bss_9B8->unk194 = 0;
                lbl_1_bss_9B8->unk19C += 1;
            }
            break;
        case 1:
            lbl_1_bss_9B8->unk194 += 1;
            lbl_1_bss_9B8->unk1B4 = (f32) (5.0 + (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_9B8->unk194 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_9B8->unk13C == 3) {
                lbl_1_bss_9B8->unk1B4 = 10.0f;
                lbl_1_bss_9B8->unk19C += 1;
            }
            break;
        case 2:
            lbl_1_bss_9B8->unk194 += 1;
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_9B8->unk13C == 4) {
                lbl_1_bss_9B8->unk19C += 1;
                lbl_1_bss_9B8->unk198 = 0;
            }
            break;
        case 3:
            lbl_1_bss_9B8->unk198 += 1;
            lbl_1_bss_9B8->unk194 += 1;
            if ((s32) lbl_1_bss_9B8->unk198 > 0x28) {
                lbl_1_bss_9B8->unk198 = 0x28;
            }
            lbl_1_bss_9B8->unk1B0 = (f32) (10.0 - (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_9B8->unk198 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_9B8->unk1B0 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_9B8->unk194 * lbl_1_bss_9B8->unk1B4)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
loop_17:
            if (temp_r31->unk10.x >= 360.0f) {
                temp_r31->unk10.x -= 360.0f;
                goto loop_17;
            }
            if (((s32) lbl_1_bss_9B8->unk13C == 1) && ((temp_r31->unk10.x >= 359.0f) || (temp_r31->unk10.x <= 1.0f))) {
                lbl_1_bss_9B8->unk1B0 = 0.0f;
                temp_r31->unk10.x = 0.0f;
                temp_r30->unk10.x = 0.0f;
                temp_r30->unk10.y = -45.0f;
                temp_r30->unk10.z = 0.0f;
                lbl_1_bss_9B8->unk19C = 0;
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

void fn_1_9DAC(void) {
    M545Model *temp_r30;
    M545Model *temp_r31;
    s32 temp_r4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u8 temp_r3;
    u8 temp_r3_3;

    temp_r31 = &lbl_1_bss_9B8->unk3C[0x1E];
    temp_r30 = &lbl_1_bss_9B8->unk3C[0x20];
    temp_r4 = lbl_1_bss_9B8->unk1CC;
    if ((u32) temp_r4 <= 7U) {
        switch (temp_r4) {
        case 0:
            if ((s32) lbl_1_bss_9B8->unk13C == 2) {
                lbl_1_bss_9B8->unk1C4 = 0;
                if (lbl_1_bss_9B8->unk1E0 == 0.0f) {
                    lbl_1_bss_9B8->unk1CC += 1;
                    lbl_1_bss_9B8->unk1C4 = 0;
                    lbl_1_bss_9B8->unk1E0 = 15.0f;
                    temp_r3 = rand8();
                    temp_r4_2 = temp_r3 >> 0x1FU;
                    temp_r3_2 = (temp_r3 << 0x1C) - temp_r4_2;
                    lbl_1_bss_9B8->unk1E8 = (f32) ((((temp_r3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                } else {
                    lbl_1_bss_9B8->unk1CC = 4;
                    lbl_1_bss_9B8->unk1E0 = 10.0f;
                    temp_r3_3 = rand8();
                    temp_r4_3 = temp_r3_3 >> 0x1FU;
                    temp_r3_4 = (temp_r3_3 << 0x1C) - temp_r4_3;
                    lbl_1_bss_9B8->unk1E8 = (f32) ((((temp_r3_3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                }
                lbl_1_bss_9B8->unk1E4 = (250.0f * lbl_1_bss_9B8->unk1E0) / 360.0f;
            }
            break;
        case 1:
            temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
            temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
            if (temp_r31->unk4.x >= lbl_1_bss_9B8->unk1E8) {
                lbl_1_bss_9B8->unk1CC += 1;
            }
            break;
        case 2:
            lbl_1_bss_9B8->unk1C4 += 1;
            lbl_1_bss_9B8->unk1E0 = (f32) (7.5 + (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_9B8->unk1C4) / 180.0)));
            lbl_1_bss_9B8->unk1E4 = (250.0f * lbl_1_bss_9B8->unk1E0) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
            temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
            if ((s32) lbl_1_bss_9B8->unk1C4 >= 0x5A) {
                lbl_1_bss_9B8->unk1CC += 1;
            }
            break;
        case 3:
            lbl_1_bss_9B8->unk1C4 += 1;
            if ((s32) lbl_1_bss_9B8->unk1C4 >= 0xB4) {
                lbl_1_bss_9B8->unk1C4 = 0xB4;
            }
            lbl_1_bss_9B8->unk1E0 = (f32) (7.5 - (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_9B8->unk1C4) / 180.0)));
            lbl_1_bss_9B8->unk1E4 = (250.0f * lbl_1_bss_9B8->unk1E0) / 360.0f;
            if (temp_r31->unk4.x < 1000.0f) {
                temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
                temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
            } else if ((s32) lbl_1_bss_9B8->unk13C == 1) {
                lbl_1_bss_9B8->unk1CC = 0;
            }
            break;
        case 4:
            lbl_1_bss_9B8->unk1C4 += 1;
            if ((s32) lbl_1_bss_9B8->unk1C4 >= 0x14) {
                temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
                temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
                if (temp_r31->unk4.x >= lbl_1_bss_9B8->unk1E8) {
                    lbl_1_bss_9B8->unk1CC += 1;
                    lbl_1_bss_9B8->unk1C4 = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_9B8->unk1C4 += 1;
            lbl_1_bss_9B8->unk1E0 = (f32) (10.0 * cos((3.141592653589793 * (f64) lbl_1_bss_9B8->unk1C4) / 180.0));
            lbl_1_bss_9B8->unk1E4 = (250.0f * lbl_1_bss_9B8->unk1E0) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
            temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
            if ((s32) lbl_1_bss_9B8->unk1C4 == 0x5A) {
                lbl_1_bss_9B8->unk1CC += 1;
                lbl_1_bss_9B8->unk1C4 = 0;
            }
            break;
        case 6:
            if ((s32) lbl_1_bss_9B8->unk13C == 2) {
                lbl_1_bss_9B8->unk1CC += 1;
            }
            break;
        case 7:
            lbl_1_bss_9B8->unk1C4 += 1;
            if ((s32) lbl_1_bss_9B8->unk1C4 >= 0x96) {
                lbl_1_bss_9B8->unk1C4 = 0x96;
            }
            if ((s32) lbl_1_bss_9B8->unk1C4 >= 0x3C) {
                lbl_1_bss_9B8->unk1E0 = (f32) (10.0 * sin((3.141592653589793 * (f64) (lbl_1_bss_9B8->unk1C4 - 0x3C)) / 180.0));
                lbl_1_bss_9B8->unk1E4 = (250.0f * lbl_1_bss_9B8->unk1E0) / 360.0f;
                if (temp_r31->unk4.x < 1000.0f) {
                    if ((s32) lbl_1_bss_9B8->unk1C4 >= 0x46) {
                        temp_r31->unk10.z -= lbl_1_bss_9B8->unk1E0;
                    }
                    temp_r31->unk4.x += lbl_1_bss_9B8->unk1E4;
                } else if ((s32) lbl_1_bss_9B8->unk13C == 1) {
                    lbl_1_bss_9B8->unk1CC = 0;
                    lbl_1_bss_9B8->unk1E0 = 0.0f;
                }
            }
            break;
        }
    }
    temp_r30->unk4.x = temp_r31->unk4.x;
    temp_r30->unk4.y = temp_r31->unk4.y - 40.0f;
    temp_r30->unk4.z = temp_r31->unk4.z;
}

void fn_1_A7B8(void) {
    M545Model *temp_r3;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_9B8->unk3C;
    temp_r0 = lbl_1_bss_9B8->unk1FC;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s32) lbl_1_bss_9B8->unk13C == 2) {
            lbl_1_bss_9B8->unk1FC += 1;
            lbl_1_bss_9B8->unk1F4 = 0;
            Hu3DMotionSpeedSet(temp_r3[0x1F].unk0, 0.5f);
            Hu3DMotionTimeSet(temp_r3[0x1F].unk0, 0.0f);
            return;
        }
        return;
    case 1:
        lbl_1_bss_9B8->unk1F4 += 1;
        temp_r3[0x1F].unk4.x = (f32) (((lbl_1_bss_9B8->unk1F4 * 0xFA0) / 200) - 0x7D0);
        if ((s32) lbl_1_bss_9B8->unk1F4 == 0xC8) {
            lbl_1_bss_9B8->unk1FC += 1;
            return;
        }
        break;
    case 2:
        if ((s32) lbl_1_bss_9B8->unk13C == 1) {
            lbl_1_bss_9B8->unk1FC = 0;
        }
        break;
    }
}
