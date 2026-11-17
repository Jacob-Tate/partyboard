// MP5 m544 (Shy Guy Showdown), generated from its m2c draft by tools/mp5/ports/m544dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m544dll (tools/mp5/decomp.py m544Dll --types tools/mp5/types/m544dll.h)
// Written from the draft: m544 Shy Guy Showdown (1 vs 1 duel: a Shy Guy flips a card with a number / hand sign, the
// duelists press the matching button). Same framework as m545/m547: a work struct (lbl_1_bss_530, also reached
// through the pointers lbl_1_bss_914 / lbl_1_bss_918) on MP5's MgSeq sequencer; a third "player" slot is the Shy Guy.

typedef struct M544Model { // model table entry, 0x1C (0x23 of them in lbl_1_bss_15C)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M544Model;

typedef struct M544Player { // 0x1C
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
} M544Player;

typedef struct M544Char { // per MP5 character, 0x1C
    u32 unk0[7]; // MP5 motion data numbers
} M544Char;

typedef struct M544Anim { // per character / Shy Guy animation request, 0x54 (fn_1_AF60 applies it)
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
    s16 unk28; // a follow-up motion is queued
    s16 unk2A; // follow-up motion index
    f32 unk2C; // follow-up time
    u32 unk30; // follow-up attrs
    u32 unk34; // follow-up attrs to reset
    s16 unk38; // shift state
    s16 unk3A; // shift motion index
    u32 unk3C; // shift attrs
    f32 unk40; // shift start time
    f32 unk44; // shift length
    f32 unk48; // shift time
    f32 unk4C; // shift max time
    char pad50[4];
} M544Anim;

typedef struct M544Work { // lbl_1_bss_530, 0x2E8
    char pad0[4];
    M544Player unk4[3]; // the duelists (the third is unused)
    M544Model *unk58; // model table (lbl_1_bss_15C)
    M544Char *unk5C[3]; // character data per player (+ the Shy Guy)
    s16 *unk68[3]; // motions per player (lbl_1_bss_130)
    M544Anim unk74[3];
    u32 *unk170; // data numbers (lbl_1_data_1A4)
    s16 unk174;
    char pad176[2];
    s32 unk178; // ending poses started
    char pad17C[0x4C];
    s32 unk1C8; // Shy Guy head turn off
    s32 unk1CC; // counter
    s32 unk1D0;
    s32 unk1D4; // Shy Guy mode (1 idle, 2 flip start, 3, 4)
    char pad1D8[0x10];
    f32 unk1E8;
    f32 unk1EC;
    char pad1F0[8];
    s32 unk1F8; // arms off
    s32 unk1FC;
    s32 unk200;
    s32 unk204;
    char pad208[0x10];
    f32 unk218;
    f32 unk21C;
    f32 unk220;
    char pad224[4];
    s32 unk228; // body sway off
    s32 unk22C;
    s32 unk230;
    s32 unk234;
    char pad238[0x10];
    f32 unk248;
    f32 unk24C;
    char pad250[0xC];
    s32 unk25C; // card spin
    char pad260[4];
    s32 unk264;
    char pad268[0x10];
    f32 unk278;
    f32 unk27C;
    f32 unk280;
    char pad284[8];
    s32 unk28C; // cloud scroll
    char pad290[4];
    s32 unk294;
    char pad298[0x50];
} M544Work;

typedef struct M544Hand { // lbl_1_bss_C, the Shy Guy's card, 0x74
    s16 unk0; // step
    s16 unk2; // step of the card effect
    s16 unk4; // card state (0 in the hand, 1 free, 2 faded)
    s16 unk6;
    f32 unk8; // card transparency
    s16 unkC; // wait counter
    s16 unkE; // reaction counter
    s16 unk10;
    s16 unk12; // round
    s16 unk14;
    s16 unk16; // card used
    char unk18[0x2C]; // hook name
    Mtx unk44; // hand matrix
} M544Hand;

typedef struct M544Pl { // lbl_1_bss_80, per duelist game state, 0x28
    s16 unk0;
    s16 unk2;
    s16 unk4; // step
    s16 unk6; // step of the item
    s16 unk8; // timer
    s16 unkA; // sound played
    s16 unkC; // result (0 wait, 1 won, 2 lost, 3 pressed wrong)
    s16 unkE; // hits
    Vec unk10; // item scale
    char *unk1C; // item hook
    char pad20[2];
    s16 unk22; // com: frames to wait
    s16 unk24; // com: plan
    s16 unk26; // com: target round
} M544Pl;

typedef struct M544Game { // lbl_1_bss_D0, 0x60
    s16 unk0; // mode step
    s16 unk2; // sub step
    s16 unk4;
    s16 unk6; // counter
    char pad8[0x18];
    s16 unk20; // winner bits (0 draw)
    char pad22[2];
    MGTIMER *unk24; // timer
    s16 unk28; // press window open
    char pad2A[2];
    s16 unk2C; // fx particle running
    s16 unk2E; // bgm started
    s32 unk30; // bgm stream
    s32 unk34; // jingle stream
    s16 unk38; // counter
    char pad3A[2];
    s32 unk3C[6]; // fx
    s16 unk54[6]; // fx used
} M544Game;

typedef struct M544Fx { // lbl_1_bss_828, an item flying to the other duelist, 0x2C
    Vec unk0; // from
    Vec unkC; // to
    s32 unk18; // frame
    s32 unk1C; // step
    s32 unk20; // active
    s32 unk24; // owner
    f32 unk28; // fade
} M544Fx;

typedef struct M544Seq { // lbl_1_bss_8D8, one round, 0x6
    s16 unk0; // frames to wait
    s16 unk2; // frames to wait (com)
    s16 unk4; // card: 0..5 buttons, 6..9 specials
} M544Seq;

typedef struct M544Cpu { // lbl_1_data_3EC, per difficulty, 0xA
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} M544Cpu;

typedef struct M544Cam { // lbl_1_bss_8, 0x50
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
} M544Cam;

typedef struct M544CamInit { // lbl_1_data_210, 0x34
    Vec unk0; // target
    Vec unkC; // rot
    f32 unk18; // zoom
    f32 unk1C; // aspect
    f32 unk20; // viewport x
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30; // fov
} M544CamInit;

typedef struct M544Light { // lbl_1_bss_4, 0x3C
    s16 unk0;
    char pad2[2];
    Vec unk4; // pos
    Vec unk10; // rot
    Vec unk1C; // target
    Vec unk28; // direction
    f32 unk34; // distance
    GXColor unk38;
} M544Light;

typedef struct M544Shadow { // lbl_1_bss_0, 0x50
    Vec unk0; // pos
    Vec unkC; // rot
    Vec unk18; // target
    char pad24[0xC];
    Vec unk30; // up
    char pad3C[0xC];
    f32 unk48; // distance
    f32 unk4C; // tp level
} M544Shadow;

typedef struct M544Part { // particle template, 0x38 (lbl_1_data_370)
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
} M544Part;


s32 fn_1_4328(M544Work *work);
s32 fn_1_4E08(void);
s32 fn_1_4E3C(void);
s32 fn_1_4EB4(void);
s32 fn_1_5098(void);
s16 fn_1_511C(void);
s32 fn_1_5158(void);
s32 fn_1_5514(void);
s32 fn_1_5544(void);
void fn_1_5574(void);
void fn_1_5B0C(void);
void fn_1_5C48(void);
s16 fn_1_5E38(void);
s32 fn_1_5EFC(s16 player);
s32 fn_1_614C(s16 player);
s32 fn_1_6274(s16 player);
s32 fn_1_65EC(void);
s32 fn_1_6B64(void);
void fn_1_6E9C(s16 round);
s32 fn_1_6F38(s16 player, s16 arg1);
s32 fn_1_7288(void);
s16 fn_1_753C(void);
s32 fn_1_7F30(void);
s16 fn_1_817C(void);
void fn_1_86BC(void);
void fn_1_8710(s32 player, s16 slot);
void fn_1_89AC(OMOBJ *obj);
void fn_1_8E98(s32 slot, s32 step);
void fn_1_91B4(s32 slot, s32 frame);
s32 fn_1_9364(s32 slot, s32 mode);
void fn_1_95D8(s32 arg0, s32 arg1);
void fn_1_9798(s16 player);
s16 fn_1_9C84(s16 player);
void ObjectSetup(void);
void fn_1_37C(void);
void fn_1_3B0(void);
void fn_1_3DC(void);
void fn_1_3FC(void);
void fn_1_428(void);
void fn_1_448(void);
void fn_1_474(void);
void fn_1_4A0(void);
void fn_1_4C0(void);
void fn_1_4EC(OMOBJ *obj);
void fn_1_4F0(s16 cam);
void fn_1_9C0(s16 cam);
void fn_1_F38(void);
void fn_1_1168(void);
void fn_1_1440(void);
void fn_1_1570(void);
s16 fn_1_18E8(f32 *val, f32 frames, f32 from, f32 to);
MGTIMER *fn_1_1A1C(s32 arg0, s32 arg1, s32 arg2, f32 x, f32 y);
void fn_1_1A90(MGTIMER *timer);
void fn_1_1ABC(MGTIMER *timer);
void fn_1_1AE4(MGTIMER *timer);
void fn_1_2330(void);
void fn_1_24AC(Vec *pos);
void fn_1_2834(Vec *pos, s16 mode);
s16 fn_1_2EE4(M544Part *tmpl, f32 x, f32 y, f32 z, f32 scale);
void fn_1_30B8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_34D0(void);
void fn_1_35DC(s16 player);
void fn_1_39E8(Vec *from, Vec *to, f32 scale);
void fn_1_3AD4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_3EF8(void);
void fn_1_3F28(void);
void fn_1_3F58(s16 arg0, s16 arg1);
void fn_1_3FC0(s16 arg0);
void fn_1_4020(s16 arg0);
void fn_1_4098(s16 arg0, s16 arg1, s16 arg2);
void fn_1_4120(s16 arg0, s16 arg1);
void fn_1_41B0(s16 arg0);
void fn_1_425C(s16 arg0);
void fn_1_4308(void);
void fn_1_9EF8(M544Work *work, M544Model *models, u32 *dataNums);
void fn_1_A144(s16 arg0);
void fn_1_A3F0(s16 slot, M544Char *chr);
void fn_1_A410(s16 slot, s16 *mot);
void fn_1_A430(void);
void fn_1_A9A4(OMOBJ *obj);
void fn_1_ADBC(void);
void fn_1_AF60(OMOBJ *obj);
void fn_1_B318(OMOBJ *obj);
void fn_1_B36C(void);
void fn_1_B384(void);
void fn_1_B990(void);
void fn_1_BEDC(void);
void fn_1_C7C0(void);
void fn_1_D1CC(void);
s32 fn_1_4328(M544Work *work);
s32 fn_1_4E08(void);
s32 fn_1_4E3C(void);
s32 fn_1_4EB4(void);
s32 fn_1_5098(void);
s16 fn_1_511C(void);
s32 fn_1_5158(void);
s32 fn_1_5514(void);
s32 fn_1_5544(void);
void fn_1_5574(void);
void fn_1_5C48(void);
s16 fn_1_5E38(void);
s32 fn_1_5EFC(s16 player);
s32 fn_1_614C(s16 player);
s32 fn_1_6274(s16 player);
s32 fn_1_65EC(void);
s32 fn_1_6B64(void);
void fn_1_6E9C(s16 round);
s16 fn_1_753C(void);
s32 fn_1_7F30(void);
s16 fn_1_817C(void);
void fn_1_86BC(void);
void fn_1_8710(s32 player, s16 slot);
void fn_1_89AC(omObjData *obj);
void fn_1_8E98(s32 slot, s32 step);
void fn_1_91B4(s32 slot, s32 frame);
s32 fn_1_9364(s32 slot, s32 mode);
void fn_1_95D8(s32 arg0, s32 arg1);
void fn_1_9798(s16 player);
s16 fn_1_9C84(s16 player);
void ObjectSetup(void);
void fn_1_37C(void);
void fn_1_3B0(void);
void fn_1_3DC(void);
void fn_1_3FC(void);
void fn_1_428(void);
void fn_1_448(void);
void fn_1_474(void);
void fn_1_4A0(void);
void fn_1_4C0(void);
void fn_1_4EC(omObjData *obj);
void fn_1_4F0(s16 cam);
void fn_1_9C0(s16 cam);
void fn_1_F38(void);
void fn_1_1168(void);
void fn_1_1440(void);
void fn_1_1570(void);
s16 fn_1_18E8(f32 *val, f32 frames, f32 from, f32 to);
MGTIMER *fn_1_1A1C(s32 arg0, s32 arg1, s32 arg2, f32 x, f32 y);
void fn_1_1A90(MGTIMER *timer);
void fn_1_1AE4(MGTIMER *timer);
void fn_1_2330(void);
void fn_1_2834(Vec *pos, s16 mode);
s16 fn_1_2EE4(M544Part *tmpl, f32 x, f32 y, f32 z, f32 scale);
void fn_1_30B8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_34D0(void);
void fn_1_35DC(s16 player);
void fn_1_39E8(Vec *from, Vec *to, f32 scale);
void fn_1_3AD4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_3EF8(void);
void fn_1_3F28(void);
void fn_1_3F58(s16 arg0, s16 arg1);
void fn_1_4020(s16 arg0);
void fn_1_4098(s16 arg0, s16 arg1, s16 arg2);
void fn_1_4120(s16 arg0, s16 arg1);
void fn_1_425C(s16 arg0);
void fn_1_4308(void);
void fn_1_9EF8(M544Work *work, M544Model *models, u32 *dataNums);
void fn_1_A144(s16 arg0);
void fn_1_A3F0(s16 slot, M544Char *chr);
void fn_1_A410(s16 slot, s16 *mot);
void fn_1_A430(void);
void fn_1_A9A4(omObjData *obj);
void fn_1_ADBC(void);
void fn_1_AF60(omObjData *obj);
void fn_1_B318(omObjData *obj);
void fn_1_B36C(void);
void fn_1_B384(void);
void fn_1_B990(void);
void fn_1_BEDC(void);
void fn_1_C7C0(void);
void fn_1_D1CC(void);

extern s32 fontcolor;
s8 lbl_1_data_3BB[0x15] = {
    0x67,
    0x30,
    0x30,
    0x33,
    0x6D,
    0x31,
    0x2D,
    0x69,
    0x74,
    0x65,
    0x6D,
    0x68,
    0x6F,
    0x6F,
    0x6B,
    0x5F,
    0x52,
    0,
    0,
    0,
    0,
};
M544Cpu lbl_1_data_3EC[4] = {
    { 0x46, 0x5A, 0x55, 0x46, 0x5A },
    { 0x32, 0x46, 0x5A, 0x50, 0x5F },
    { 0x23, 0x2D, 0x5F, 0x5A, 0x64 },
    { 0x1E, 0x23, 0x64, 0x64, 0x64 },
};
void *lbl_1_bss_820;
s16 lbl_1_bss_824;
s16 lbl_1_bss_826;
M544Fx lbl_1_bss_828[4];
M544Seq lbl_1_bss_8D8[0xA];
M544Work *lbl_1_bss_914;
MGSEQ_PARAM lbl_1_data_0 = {
    0,
    0,
    ((void (*)(s16, s16)) fn_1_37C),
    ((void (*)(s16, s16)) fn_1_3B0),
    ((void (*)(s16, s16)) fn_1_3DC),
    ((void (*)(s16, s16)) fn_1_3FC),
    ((void (*)(s16, s16)) fn_1_428),
    ((void (*)(s16, s16)) fn_1_448),
    ((void (*)(s16, s16)) fn_1_474),
    ((void (*)(s16, s16)) fn_1_4A0),
    ((void (*)(s16, s16)) fn_1_4C0),
};
M544Char lbl_1_data_28[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 38), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 39), DATA_MAKE_NUM(DATADIR_MP5_MARIO, 40), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 38), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 39), DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 40), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 38), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 39), DATA_MAKE_NUM(DATADIR_MP5_PEACH, 40), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 38), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 39), DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 40), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 38), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 39), DATA_MAKE_NUM(DATADIR_MP5_WARIO, 40), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 38), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 39), DATA_MAKE_NUM(DATADIR_MP5_DAISY, 40), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 26), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 38), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 39), DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 40), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 26 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 38 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 39 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 40 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
};
u32 lbl_1_data_194[4] = { DATA_MAKE_NUM(DATADIR_MP5_M544, 26), DATA_MAKE_NUM(DATADIR_MP5_M544, 27), DATA_MAKE_NUM(DATADIR_MP5_M544, 28), DATA_MAKE_NUM(DATADIR_MP5_M544, 29) };
u32 lbl_1_data_1A4[0x1B] = {
    DATA_MAKE_NUM(DATADIR_MP5_M544, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M544, 25),
    0,
};
M544CamInit lbl_1_data_210[4] = {
    {
        { -12.0f, 208.0f, -120.0f },
        { -11.0f, 0.0f, 500.0f },
        141.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
    {
        { -220.0f, 218.0f, 0.0f },
        { -11.0f, -29.0f, 0.0f },
        275.0f,
        1.33f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        45.0f,
    },
    {
        { 0.0f, 238.0f, 0.0f },
        { -6.0f, 0.0f, 0.0f },
        695.0f,
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
s16 lbl_1_data_2E0[0x10] = {
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
M544Part lbl_1_data_370 = {
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
s16 lbl_1_data_3A8[8] = { 0x81D, 0x81E, 0x81F, 0x820, 0x821, 0x2C4, 0, 0 };
M544Shadow *lbl_1_bss_0;
M544Light *lbl_1_bss_4;
M544Cam *lbl_1_bss_8;
M544Hand lbl_1_bss_C;
M544Pl lbl_1_bss_80[2];
M544Game lbl_1_bss_D0;
s16 lbl_1_bss_130[3][7];
M544Model lbl_1_bss_15C[0x23];
M544Work lbl_1_bss_530;
HUPROCESS *lbl_1_bss_818;
Vec lbl_1_data_418[0xC] = {
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
void (*lbl_1_data_4A8[5])() = { fn_1_B384, fn_1_B990, fn_1_BEDC, fn_1_C7C0, fn_1_D1CC };
M544Work *lbl_1_bss_918;
s16 lbl_1_rodata_350[0xA] = { 5, 6, 7, 8, 9, 9, 9, 9, 9, 9 }; /* const */
f32 lbl_1_rodata_A4[0xD] = {
    150.0f,
    170.0f,
    188.0f,
    169.0f,
    164.0f,
    180.0f,
    204.0f,
    103.0f,
    150.0f,
    150.0f,
    150.0f,
    150.0f,
    150.0f,
}; /* const */
f32 lbl_1_rodata_D8[0xD][6] = {
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { -10.0f, -50.0f, 0.0f, -10.0f, 50.0f, 0.0f },
    { -10.0f, -50.0f, 0.0f, -10.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { -10.0f, -50.0f, 0.0f, -10.0f, 50.0f, 0.0f },
    { 40.0f, -50.0f, 0.0f, 40.0f, 50.0f, 0.0f },
    { -5.0f, -50.0f, -10.0f, -5.0f, 60.0f, -10.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
    { 0.0f, -50.0f, 0.0f, 0.0f, 50.0f, 0.0f },
}; /* const */
f32 lbl_1_rodata_210[0xD][6] = {
    { 20.0f, -50.0f, 0.0f, 20.0f, 50.0f, 0.0f },
    { 20.0f, -50.0f, 0.0f, 20.0f, 50.0f, 0.0f },
    { 20.0f, -50.0f, -5.0f, 20.0f, 50.0f, -5.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 20.0f, -50.0f, -5.0f, 20.0f, 50.0f, -5.0f },
    { -25.0f, -50.0f, 0.0f, -25.0f, 50.0f, 0.0f },
    { 30.0f, -50.0f, 0.0f, 30.0f, 60.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
    { 10.0f, -50.0f, 0.0f, 10.0f, 50.0f, 0.0f },
}; /* const */

s32 fn_1_4328(M544Work *work) {
    u16 spC[10];
    M544Work *sp8;
    s16 temp_r27;
    s16 var_r29;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;
    s16 var_r31_4;
    s16 var_r31_5;
    s16 var_r31_6;
    s16 var_r31_7;

    sp8 = work;
    spC[0] = (u16) lbl_1_rodata_350[0];
    spC[1] = (u16) lbl_1_rodata_350[1];
    spC[2] = (u16) lbl_1_rodata_350[2];
    spC[3] = (u16) lbl_1_rodata_350[3];
    spC[4] = (u16) lbl_1_rodata_350[4];
    spC[5] = (u16) lbl_1_rodata_350[5];
    spC[6] = (u16) lbl_1_rodata_350[6];
    spC[7] = (u16) lbl_1_rodata_350[7];
    spC[8] = (u16) lbl_1_rodata_350[8];
    spC[9] = (u16) lbl_1_rodata_350[9];
    memset(&lbl_1_bss_D0, 0, 0x60);
    memset((M544Game *) lbl_1_bss_80, 0, 0x50);
    memset((M544Game *) &lbl_1_bss_C, 0, 0x74);
    var_r31 = 0;
loop_2:
    if (var_r31 < 6) {
        lbl_1_bss_D0.unk54[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_914 = sp8;
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 2) {
        lbl_1_bss_80[var_r31_2].unk10.x = 1.0f;
        lbl_1_bss_80[var_r31_2].unk10.y = 1.0f;
        lbl_1_bss_80[var_r31_2].unk10.z = 1.0f;
        lbl_1_bss_80[var_r31_2].unk1C = CharModelItemHookGet(lbl_1_bss_914->unk4[var_r31_2].unk2, 1, 0);
        var_r31_2 += 1;
        goto loop_5;
    }
    sprintf(lbl_1_bss_C.unk18, "%s", lbl_1_data_3BB);
    lbl_1_bss_C.unk8 = 1.0f;
    var_r31_3 = 0;
loop_12:
    if (var_r31_3 < 0xA) {
        lbl_1_bss_8D8[var_r31_3].unk0 = (frandmod(0x2DU) + 5) * 6;
        lbl_1_bss_8D8[var_r31_3].unk2 = (frandmod(0xFU) + 5) * 6;
        temp_r27 = frandmod(0xBU);
        if ((var_r31_3 >= 0xA) || (temp_r27 <= (s16) spC[var_r31_3])) {
            lbl_1_bss_8D8[var_r31_3].unk4 = frandmod(6U);
        } else {
            lbl_1_bss_8D8[var_r31_3].unk4 = frandmod(4U) + 6;
        }
        var_r31_3 += 1;
        goto loop_12;
    }
    var_r31_4 = 0;
loop_17:
    if (var_r31_4 < 2) {
        if ((s16) lbl_1_bss_914->unk4[var_r31_4].unk4 != 0) {
            fn_1_9798(var_r31_4);
        }
        var_r31_4 += 1;
        goto loop_17;
    }
    var_r31_5 = 0;
    var_r29 = 0;
    var_r30 = 0;
loop_20:
    if (var_r31_5 < 0xA) {
        lbl_1_bss_914->unk58[var_r30].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_bss_914->unk170[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_914->unk58[var_r30].unk0, 1U);
        Hu3DModelCameraSet(lbl_1_bss_914->unk58[var_r30].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_914->unk58[var_r30].unk0, 2);
        Hu3DModelShadowSet(lbl_1_bss_914->unk58[var_r30].unk0);
        lbl_1_bss_914->unk58[var_r30].unk4.x = 0.0f;
        lbl_1_bss_914->unk58[var_r30].unk4.y = 0.0f;
        lbl_1_bss_914->unk58[var_r30].unk4.z = 0.0f;
        lbl_1_bss_914->unk58[var_r30].unk10.x = 0.0f;
        lbl_1_bss_914->unk58[var_r30].unk10.y = 0.0f;
        lbl_1_bss_914->unk58[var_r30].unk10.z = -50.0f;
        var_r31_5 += 1;
        var_r29 += 1;
        var_r30 += 1;
        goto loop_20;
    }
    Hu3DModelAttrReset(lbl_1_bss_914->unk58[lbl_1_bss_8D8->unk4].unk0, 1U);
    Hu3DModelHookSet(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18, lbl_1_bss_914->unk58[lbl_1_bss_8D8->unk4].unk0);
    var_r31_6 = 0;
    var_r30_2 = 0xA;
loop_23:
    if (var_r31_6 < 2) {
        lbl_1_bss_914->unk58[var_r30_2].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_bss_914->unk170[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_914->unk58[var_r30_2].unk0, 1U);
        Hu3DModelCameraSet(lbl_1_bss_914->unk58[var_r30_2].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_914->unk58[var_r30_2].unk0, 0);
        Hu3DModelShadowSet(lbl_1_bss_914->unk58[var_r30_2].unk0);
        Hu3DModelAttrReset(lbl_1_bss_914->unk58[var_r30_2].unk0, 1U);
        lbl_1_bss_914->unk58[var_r30_2].unk4.x = 0.0f;
        lbl_1_bss_914->unk58[var_r30_2].unk4.y = 0.0f;
        lbl_1_bss_914->unk58[var_r30_2].unk4.z = 0.0f;
        lbl_1_bss_914->unk58[var_r30_2].unk10.x = 0.0f;
        lbl_1_bss_914->unk58[var_r30_2].unk10.y = 0.0f;
        lbl_1_bss_914->unk58[var_r30_2].unk10.z = 0.0f;
        Hu3DModelHookSet(lbl_1_bss_914->unk58[var_r31_6 + 0x20].unk0, lbl_1_bss_80[var_r31_6].unk1C, lbl_1_bss_914->unk58[var_r30_2].unk0);
        var_r31_6 += 1;
        var_r30_2 += 1;
        goto loop_23;
    }
    var_r31_7 = 0;
loop_26:
    if (var_r31_7 < 4) {
        lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_bss_914->unk170[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 1U);
        Hu3DModelCameraSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 0);
        Hu3DMotionSpeedSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 0.0f);
        var_r31_7 += 1;
        goto loop_26;
    }
    var_r30_3 = 0x10;
loop_29:
    if (var_r30_3 <= 0x13) {
        lbl_1_bss_914->unk58[var_r30_3].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_bss_914->unk170[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_914->unk58[var_r30_3].unk0, 1U);
        Hu3DModelCameraSet(lbl_1_bss_914->unk58[var_r30_3].unk0, 1U);
        Hu3DModelLayerSet(lbl_1_bss_914->unk58[var_r30_3].unk0, 0);
        Hu3DMotionSpeedSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_914->unk58[var_r31_7 + 0xC].unk0, 0.0f);
        var_r30_3 += 1;
        goto loop_29;
    }
    fn_1_2330();
    fn_1_34D0();
    fn_1_5C48();
    lbl_1_bss_D0.unk24 = fn_1_1A1C(0, 5, 0, 292.0f, 64.0f);
    return 1;
}

s32 fn_1_4E08(void) {
    fn_1_7F30();
    fn_1_5C48();
    return 0;
}

s32 fn_1_4E3C(void) {
    if ((s16) lbl_1_bss_D0.unk2E == 0) {
        fn_1_3F28();
        lbl_1_bss_D0.unk2E = 1;
    }
    lbl_1_bss_D0.unk0 = 0;
    lbl_1_bss_D0.unk6 = 0;
    fn_1_5C48();
    return 1;
}

s32 fn_1_4EB4(void) {
    s16 temp_r29;
    s32 temp_r31;
    s32 var_r30;

    var_r30 = 0;
    switch ((s16) lbl_1_bss_D0.unk0) {              /* irregular */
    case 0:
        temp_r31 = fn_1_6B64();
        if ((s16) (temp_r31 + fn_1_65EC()) != 0) {
            fn_1_1AE4(lbl_1_bss_D0.unk24);
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 1:
        if (fn_1_5E38() != 0) {
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 2:
        lbl_1_bss_D0.unk0 += 1;
        break;
    case 3:
        if ((s16) lbl_1_bss_D0.unk20 != 0) {
            MgSeqWinnerSet(lbl_1_bss_914->unk4[lbl_1_bss_D0.unk20 & 1].unk2, -1, -1, -1);
            temp_r29 = lbl_1_bss_914->unk4[lbl_1_bss_D0.unk20 & 1].unk0;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r29].coin_win = 0xA;
            }
        } else {
            MgSeqWinnerSet(-1, -1, -1, -1);
        }
        lbl_1_bss_D0.unk2E = 0;
        var_r30 = 1;
        break;
    }
    fn_1_5C48();
    return var_r30;
}

s32 fn_1_5098(void) {
    if ((s16) lbl_1_bss_D0.unk2E == 0) {
        fn_1_3F58(1, 0x64);
        lbl_1_bss_D0.unk2E = 1;
    }
    lbl_1_bss_D0.unk6 = 0;
    lbl_1_bss_D0.unk0 = 0;
    fn_1_753C();
    fn_1_5C48();
    return 0;
}

s16 fn_1_511C(void) {
    s16 temp_r31;

    temp_r31 = fn_1_817C();
    fn_1_753C();
    fn_1_5C48();
    return temp_r31;
}

s32 fn_1_5158(void) {
    M544Anim *temp_r31;
    M544Anim *temp_r31_2;

    if ((s32) lbl_1_bss_914->unk178 == 0) {
        if ((s16) lbl_1_bss_D0.unk20 != 0) {
            CharModelVoicePanSet(lbl_1_bss_914->unk4[lbl_1_bss_D0.unk20 & 1].unk2, 0x40);
            CharModelFxFlagSet(lbl_1_bss_914->unk4[lbl_1_bss_D0.unk20 & 1].unk2, 1);
            temp_r31 = &lbl_1_bss_914->unk74[lbl_1_bss_D0.unk20 & 1];
            temp_r31->unk0 = 5;
            temp_r31->unk4 = 1.0f;
            temp_r31->unkC = 0.0f;
            temp_r31->unk18 = 0;
            temp_r31->unk20 = 0x40000001;
            temp_r31_2 = &lbl_1_bss_914->unk74[(s32) (lbl_1_bss_D0.unk20 & 2) >> 1];
            temp_r31_2->unk0 = 6;
            temp_r31_2->unk4 = 1.0f;
            temp_r31_2->unkC = 0.0f;
            temp_r31_2->unk18 = 0;
            temp_r31_2->unk20 = 0x40000001;
        } else {
            lbl_1_bss_914->unk74[0].unk0 = 6;
            lbl_1_bss_914->unk74[0].unk4 = 1.0f;
            lbl_1_bss_914->unk74[0].unkC = 0.0f;
            lbl_1_bss_914->unk74[0].unk18 = 0;
            lbl_1_bss_914->unk74[0].unk20 = 0x40000001;
            lbl_1_bss_914->unk74[1].unk0 = 6;
            lbl_1_bss_914->unk74[1].unk4 = 1.0f;
            lbl_1_bss_914->unk74[1].unkC = 0.0f;
            lbl_1_bss_914->unk74[1].unk18 = 0;
            lbl_1_bss_914->unk74[1].unk20 = 0x40000001;
            CharModelVoicePanSet(lbl_1_bss_914->unk4[0].unk2, 0x30);
            CharModelVoicePanSet(lbl_1_bss_914->unk4[1].unk2, 0x50);
            CharLoseVoicePlay(lbl_1_bss_914->unk4[0].unk2, lbl_1_bss_914->unk4[1].unk2, -1, -1);
        }
        lbl_1_bss_914->unk178 = 1;
    }
    if ((s16) lbl_1_bss_D0.unk20 == 0) {
        fn_1_18E8(&lbl_1_bss_914->unk58[0x20].unk10.y, 10.0f, 90.0f, 0.0f);
        fn_1_18E8(&lbl_1_bss_914->unk58[0x21].unk10.y, 10.0f, -90.0f, 0.0f);
    } else if ((s32) (lbl_1_bss_D0.unk20 & 1) != 0) {
        fn_1_18E8(&lbl_1_bss_914->unk58[0x21].unk10.y, 10.0f, -90.0f, -30.0f);
    } else {
        fn_1_18E8(&lbl_1_bss_914->unk58[0x20].unk10.y, 10.0f, 90.0f, 29.0f);
    }
    fn_1_5C48();
    return 0;
}

s32 fn_1_5514(void) {
    fn_1_5C48();
    return 1;
}

s32 fn_1_5544(void) {
    fn_1_4308();
    return 1;
}

void fn_1_5574(void) {
    HU3DMODEL *temp_r30;
    M544Anim *temp_r31;

    temp_r31 = &lbl_1_bss_914->unk74[2];
    Hu3DModelObjMtxGet(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18, (f32 (*)[4]) lbl_1_bss_C.unk44[0]);
    temp_r30 = &Hu3DData[lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0];
    if ((s16) temp_r31->unk0 == 0) {
        temp_r30->rot.z = -50.0f;
        if (((s16) temp_r31->unk0 == (s16) temp_r31->unk2) && (temp_r31->unkC == 1.0f)) {
            Hu3DModelHookSet(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18, lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0);
            lbl_1_bss_C.unk4 = 0;
        }
    }
    if ((s16) temp_r31->unk0 == 1) {
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DModelHookObjReset(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18);
        }
        lbl_1_bss_C.unk4 = 1;
    }
    if ((s16) lbl_1_bss_C.unk16 == 1) {
        lbl_1_bss_C.unk4 = 2;
    }
    switch ((s16) lbl_1_bss_C.unk4) {               /* irregular */
    case 0:
        MTXIdentity((f32 (*)[4]) temp_r30->mtx[0]);
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.x = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.y = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.z = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.x = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.y = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.z = -50.0f;
        return;
    case 1:
        MTXIdentity((f32 (*)[4]) temp_r30->mtx[0]);
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.x = lbl_1_bss_C.unk44[0][3];
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.y = lbl_1_bss_C.unk44[1][3];
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk4.z = lbl_1_bss_C.unk44[2][3];
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.x = -7.5f * (1.0f + temp_r31->unkC);
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.y = 0.0f;
        lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.z = 0.0f;
        return;
    }
}


void fn_1_5C48(void) {
    s16 var_r31;

    fn_1_5574();
    var_r31 = 0;
loop_2:
    if (var_r31 < 0x23) {
        Hu3DModelPosSet(lbl_1_bss_914->unk58[var_r31].unk0, lbl_1_bss_914->unk58[var_r31].unk4.x, lbl_1_bss_914->unk58[var_r31].unk4.y, lbl_1_bss_914->unk58[var_r31].unk4.z);
        Hu3DModelRotSet(lbl_1_bss_914->unk58[var_r31].unk0, lbl_1_bss_914->unk58[var_r31].unk10.x, lbl_1_bss_914->unk58[var_r31].unk10.y, lbl_1_bss_914->unk58[var_r31].unk10.z);
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_9C0(0);
    lbl_1_bss_4->unk10.x = lbl_1_bss_8->unk10.x;
    lbl_1_bss_4->unk10.y = lbl_1_bss_8->unk10.y;
    lbl_1_bss_4->unk34 = lbl_1_bss_8->unk34;
    lbl_1_bss_4->unk1C.x = lbl_1_bss_8->unk1C.x;
    lbl_1_bss_4->unk1C.z = lbl_1_bss_8->unk1C.y;
    fn_1_1168();
    fn_1_1570();
}

s16 fn_1_5E38(void) {
    s16 temp_r0;
    s16 var_r30;
    s16 var_r31;

    var_r31 = 1;
    var_r30 = 0;
loop_12:
    if (var_r30 < 2) {
        temp_r0 = lbl_1_bss_80[var_r30].unkC;
        switch (temp_r0) {                          /* irregular */
        case 0:
            break;
        case 1:
            var_r31 *= fn_1_5EFC(var_r30);
            break;
        case 2:
            var_r31 *= fn_1_614C(var_r30);
            break;
        case 3:
            var_r31 *= fn_1_6274(var_r30);
            break;
        }
        var_r30 += 1;
        goto loop_12;
    }
    return var_r31;
}

s32 fn_1_5EFC(s16 player) {
    M544Anim *temp_r31;
    M544Pl *temp_r4;
    M544Pl *temp_r4_2;
    M544Pl *temp_r4_3;
    M544Pl *temp_r4_4;
    M544Pl *temp_r4_5;
    s16 temp_r0;
    s16 temp_r3;
    s32 var_r29;

    temp_r31 = &lbl_1_bss_914->unk74[player];
    var_r29 = 0;
    temp_r0 = lbl_1_bss_80[player].unk4;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->unk0 = 2;
        temp_r31->unk4 = 1.0f;
        temp_r31->unkC = 0.0f;
        temp_r31->unk18 = 0;
        temp_r31->unk20 = 0x40000001;
        temp_r4 = &lbl_1_bss_80[player];
        temp_r4->unk4 += 1;
        break;
    case 1:
        if ((s32) temp_r31->unk24 != 0) {
            if ((s16) lbl_1_bss_80[player].unkE >= 1) {
                temp_r4_2 = &lbl_1_bss_80[player];
                temp_r4_2->unk4 += 1;
            } else {
                fn_1_8710((s32) player, lbl_1_bss_80[player].unkE);
                temp_r31->unk0 = 3;
                temp_r31->unk4 = 1.0f;
                temp_r31->unkC = 0.0f;
                temp_r31->unk18 = 0;
                temp_r31->unk20 = 0;
                fn_1_4098(2, 0x7F, (s16) ((player << 5) + 0x30));
            }
            temp_r4_3 = &lbl_1_bss_80[player];
            temp_r4_3->unkE += 1;
        }
        break;
    case 2:
        temp_r4_4 = &lbl_1_bss_80[player];
        temp_r3 = temp_r4_4->unk8;
        temp_r4_4->unk8 = temp_r3 + 1;
        if (temp_r3 > 0x3C) {
            lbl_1_bss_80[player].unk8 = 0;
            temp_r4_5 = &lbl_1_bss_80[player];
            temp_r4_5->unk4 += 1;
        }
        break;
    case 3:
        var_r29 = 1;
        break;
    }
    return var_r29;
}

s32 fn_1_614C(s16 player) {
    M544Anim *sp8;
    M544Pl *temp_r4;
    s16 temp_r3;
    s16 var_r31;
    s32 var_r29;

    sp8 = &lbl_1_bss_914->unk74[player];
    var_r29 = 0;
    if ((s16) lbl_1_bss_80[player].unkA == 0) {
        var_r31 = 0x10;
loop_5:
        if (var_r31 <= 0x13) {
            if ((u32) (Hu3DModelAttrGet(lbl_1_bss_914->unk58[var_r31].unk0) & 1) == 0) {
                fn_1_4098(3, 0x7F, (s16) ((player << 5) + 0x30));
                lbl_1_bss_80[player].unkA = 1;
            }
            var_r31 += 1;
            goto loop_5;
        }
    }
    temp_r4 = &lbl_1_bss_80[player];
    temp_r3 = temp_r4->unk8;
    temp_r4->unk8 = temp_r3 + 1;
    if (temp_r3 > 0x3C) {
        var_r29 = 1;
    }
    return var_r29;
}

s32 fn_1_6274(s16 player) {
    M544Anim *temp_r30;
    M544Pl *temp_r4;
    M544Pl *temp_r4_10;
    M544Pl *temp_r4_2;
    M544Pl *temp_r4_3;
    M544Pl *temp_r4_4;
    M544Pl *temp_r4_5;
    M544Pl *temp_r4_6;
    M544Pl *temp_r4_7;
    M544Pl *temp_r4_8;
    M544Pl *temp_r4_9;
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s32 var_r29;

    temp_r30 = &lbl_1_bss_914->unk74[player];
    var_r29 = 0;
    temp_r0 = lbl_1_bss_80[player].unk4;
    if ((u32) temp_r0 <= 6U) {
        switch (temp_r0) {
        case 0:
            temp_r30->unk0 = 2;
            temp_r30->unk4 = 1.0f;
            temp_r30->unkC = 0.0f;
            temp_r30->unk18 = 0;
            temp_r30->unk20 = 0x40000001;
            temp_r4 = &lbl_1_bss_80[player];
            temp_r4->unk4 += 1;
            break;
        case 1:
            if ((s32) temp_r30->unk24 != 0) {
                temp_r4_2 = &lbl_1_bss_80[player];
                temp_r4_2->unk4 += 1;
            }
            break;
        case 2:
            temp_r4_3 = &lbl_1_bss_80[player];
            temp_r3 = temp_r4_3->unk8;
            temp_r4_3->unk8 = temp_r3 + 1;
            if (temp_r3 > 0x3C) {
                fn_1_35DC(player);
                lbl_1_bss_80[player].unk8 = 0;
                temp_r4_4 = &lbl_1_bss_80[player];
                temp_r4_4->unk4 += 1;
            }
            break;
        case 3:
            if ((s16) lbl_1_bss_D0.unk2C == 0) {
                fn_1_35DC(player);
            }
            temp_r4_5 = &lbl_1_bss_80[player];
            temp_r3_2 = temp_r4_5->unk8;
            temp_r4_5->unk8 = temp_r3_2 + 1;
            if ((temp_r3_2 > 0xB4) || ((s16) lbl_1_bss_D0.unk2C != 0)) {
                lbl_1_bss_80[player].unk8 = 0;
                temp_r4_6 = &lbl_1_bss_80[player];
                temp_r4_6->unk4 += 1;
            }
            break;
        case 4:
            temp_r4_7 = &lbl_1_bss_80[player];
            temp_r3_3 = temp_r4_7->unk8;
            temp_r4_7->unk8 = temp_r3_3 + 1;
            if (temp_r3_3 > 0x3C) {
                fn_1_4098(4, 0x7F, (s16) ((player << 5) + 0x30));
                lbl_1_bss_80[player].unk8 = 0;
                temp_r4_8 = &lbl_1_bss_80[player];
                temp_r4_8->unk4 += 1;
            }
            break;
        case 5:
            if (((s16) lbl_1_bss_80->unkC == 3) && ((s16) lbl_1_bss_80[1].unkC == 3)) {
                if (player == 0) {
                    fn_1_95D8(1, 2);
                }
            } else if (player != 0) {
                fn_1_95D8(-1, 1);
            } else {
                fn_1_95D8(1, -1);
            }
            temp_r4_9 = &lbl_1_bss_80[player];
            temp_r4_9->unk4 += 1;
            break;
        case 6:
            temp_r4_10 = &lbl_1_bss_80[player];
            temp_r3_4 = temp_r4_10->unk8;
            temp_r4_10->unk8 = temp_r3_4 + 1;
            if (temp_r3_4 > 0x3C) {
                var_r29 = 1;
            }
            break;
        }
    }
    return var_r29;
}

s32 fn_1_65EC(void) {
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 var_r30;
    s16 var_r31;
    s32 var_r29;

    var_r29 = 0;
    var_r30 = 1;
loop_31:
    if (var_r30 >= 0) {
        var_r31 = 0;
        if ((s16) lbl_1_bss_914->unk4[var_r30].unk4 == 0) {
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x100) != 0) {
                var_r31 = 0x80;
            }
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x200) != 0) {
                var_r31 += 0x81; /* TODO(mp5): byte step? */
            }
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x400) != 0) {
                var_r31 += 0x82; /* TODO(mp5): byte step? */
            }
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x800) != 0) {
                var_r31 += 0x83; /* TODO(mp5): byte step? */
            }
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x40) != 0) {
                var_r31 += 0x84; /* TODO(mp5): byte step? */
            }
            if ((s32) (lbl_1_bss_914->unk4[var_r30].unkC & 0x20) != 0) {
                var_r31 += 0x85; /* TODO(mp5): byte step? */
            }
        } else {
            var_r31 = fn_1_9C84(var_r30);
        }
        if (var_r31 != 0) {
            var_r29 = 1;
            if ((s16) lbl_1_bss_D0.unk28 != 0) {
                temp_r0 = var_r31 & 0x7F;
                if (temp_r0 == (s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4) {
                    if ((s32) (lbl_1_bss_D0.unk20 & 1) != 0) {
                        lbl_1_bss_D0.unk20 = 0;
                        temp_r3 = frandmod(2U);
                        lbl_1_bss_D0.unk20 = temp_r3 | ((temp_r3 ^ 1) * 2);
                        lbl_1_bss_80[lbl_1_bss_D0.unk20 & 1].unkC = 1;
                        lbl_1_bss_80[(s32) (lbl_1_bss_D0.unk20 & 2) >> 1].unkC = 2;
                    } else {
                        lbl_1_bss_80[var_r30].unkC = 1;
                        lbl_1_bss_80[var_r30 ^ 1].unkC = 2;
                        lbl_1_bss_D0.unk20 |= var_r30;
                        lbl_1_bss_D0.unk20 |= (var_r30 ^ 1) * 2;
                    }
                } else if (temp_r0 != (s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4) {
                    if ((s16) lbl_1_bss_80[var_r30].unkC == 0) {
                        lbl_1_bss_80[var_r30].unkC = 3;
                    }
                    if ((s32) (lbl_1_bss_D0.unk20 & 2) != 0) {
                        lbl_1_bss_D0.unk20 = 0;
                        temp_r3_2 = frandmod(2U);
                        lbl_1_bss_D0.unk20 = temp_r3_2 | ((temp_r3_2 ^ 1) * 2);
                        lbl_1_bss_80[lbl_1_bss_D0.unk20 & 1].unkC = 0;
                        lbl_1_bss_80[(s32) (lbl_1_bss_D0.unk20 & 2) >> 1].unkC = 3;
                    } else {
                        lbl_1_bss_D0.unk20 |= var_r30 * 2;
                        lbl_1_bss_D0.unk20 |= var_r30 ^ 1;
                    }
                }
            } else if ((s32) (lbl_1_bss_D0.unk20 & 2) != 0) {
                lbl_1_bss_D0.unk20 = 0;
                temp_r3_3 = frandmod(2U);
                lbl_1_bss_D0.unk20 = temp_r3_3 | ((temp_r3_3 ^ 1) * 2);
                lbl_1_bss_80[lbl_1_bss_D0.unk20 & 1].unkC = 0;
                lbl_1_bss_80[(s32) (lbl_1_bss_D0.unk20 & 2) >> 1].unkC = 3;
            } else {
                lbl_1_bss_80[var_r30].unkC = 3;
                lbl_1_bss_80[var_r30 ^ 1].unkC = 0;
                lbl_1_bss_D0.unk20 |= var_r30 * 2;
                lbl_1_bss_D0.unk20 |= var_r30 ^ 1;
            }
        }
        var_r30 -= 1;
        goto loop_31;
    }
    return var_r29;
}

s32 fn_1_6B64(void) {
    M544Anim *temp_r31;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s32 var_r30;

    temp_r31 = &lbl_1_bss_914->unk74[2];
    var_r30 = 0;
    switch ((s16) lbl_1_bss_C.unk0) {               /* irregular */
    case 0:
        temp_r3 = lbl_1_bss_C.unkC;
        lbl_1_bss_C.unkC = temp_r3 + 1;
        if (temp_r3 >= (s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk0) {
            if ((s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4 < 6) {
                lbl_1_bss_D0.unk28 = 1;
            }
            lbl_1_bss_914->unk74[2].unk0 = 1;
            lbl_1_bss_914->unk74[2].unk4 = 1.0f;
            lbl_1_bss_914->unk74[2].unkC = 0.0f;
            lbl_1_bss_914->unk74[2].unk18 = 0;
            lbl_1_bss_914->unk74[2].unk20 = 0x40000005;
            fn_1_4020(1);
            lbl_1_bss_C.unkC = 0;
            lbl_1_bss_C.unkE = 0;
            lbl_1_bss_C.unk0 += 1;
        }
        break;
    case 1:
        if ((s16) lbl_1_bss_D0.unk28 != 0) {
            temp_r3_2 = lbl_1_bss_C.unkE;
            lbl_1_bss_C.unkE = temp_r3_2 + 1;
            if (temp_r3_2 >= 0x258) {
                lbl_1_bss_80->unkC = 0;
                lbl_1_bss_80[1].unkC = 0;
                lbl_1_bss_D0.unk20 = 0;
                lbl_1_bss_C.unk0 = 3;
                var_r30 = 1;
            }
            if ((s16) lbl_1_bss_C.unkE == 0x12C) {
                fn_1_1A90(lbl_1_bss_D0.unk24);
            }
        } else {
            temp_r3_3 = lbl_1_bss_C.unkE;
            lbl_1_bss_C.unkE = temp_r3_3 + 1;
            if (temp_r3_3 >= (s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk2) {
                lbl_1_bss_914->unk74[2].unk0 = 1;
                lbl_1_bss_914->unk74[2].unk4 = 1.0f;
                lbl_1_bss_914->unk74[2].unkC = 11.0f;
                lbl_1_bss_914->unk74[2].unk18 = 0x40000004;
                lbl_1_bss_914->unk74[2].unk20 = 0;
                lbl_1_bss_C.unk0 += 1;
            }
        }
        break;
    case 2:
        if (lbl_1_bss_914->unk74[2].unkC < 1.0f) {
            lbl_1_bss_C.unk12 += 1;
            fn_1_6E9C(lbl_1_bss_C.unk12);
            temp_r31->unk0 = 0;
            temp_r31->unk4 = 1.0f;
            temp_r31->unkC = 0.0f;
            temp_r31->unk18 = 0x40000001;
            temp_r31->unk20 = 0x40000004;
            lbl_1_bss_C.unk0 = 0;
        }
        break;
    }
    return var_r30;
}

void fn_1_6E9C(s16 round) {
    Hu3DModelAttrSet(lbl_1_bss_914->unk58[lbl_1_bss_8D8[round - 1].unk4].unk0, 1U);
    Hu3DModelAttrReset(lbl_1_bss_914->unk58[lbl_1_bss_8D8[round].unk4].unk0, 1U);
}



s16 fn_1_753C(void) {
    Vec sp8;
    Vec sp14;
    M544Anim *temp_r31;
    M544Anim *temp_r31_2;
    M544Model *temp_r5;
    M544Model *temp_r5_2;
    M544Model *temp_r7;
    M544Pl *temp_r4_2;
    M544Pl *temp_r4_3;
    M544Pl *temp_r4_4;
    M544Pl *temp_r4_5;
    M544Pl *temp_r5_3;
    f32 temp_f1;
    f32 temp_f1_2;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r3;
    s16 temp_r4;
    s16 var_r26;
    s16 var_r29;
    s16 var_r30;
    s32 var_r27;

    var_r29 = 0;
    switch ((s16) lbl_1_bss_D0.unk2) {              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        lbl_1_bss_914->unk74[0].unk38 = 1;
        lbl_1_bss_914->unk74[0].unk3A = 0;
        lbl_1_bss_914->unk74[0].unk40 = 0.0f;
        lbl_1_bss_914->unk74[0].unk44 = 20.0f;
        lbl_1_bss_914->unk74[0].unk3C = 0x40000001;
        lbl_1_bss_914->unk74[0].unk20 = 0;
        temp_r31 = &lbl_1_bss_914->unk74[1];
        temp_r31->unk38 = 1;
        temp_r31->unk3A = 0;
        temp_r31->unk40 = 0.0f;
        temp_r31->unk44 = 20.0f;
        temp_r31->unk3C = 0x40000001;
        temp_r31->unk20 = 0;
        temp_r31_2 = &lbl_1_bss_914->unk74[2];
        temp_r31_2->unk38 = 1;
        temp_r31_2->unk3A = 0;
        temp_r31_2->unk40 = 0.0f;
        temp_r31_2->unk44 = 20.0f;
        temp_r31_2->unk3C = 0x40000001;
        temp_r31_2->unk20 = 0;
        lbl_1_bss_C.unk16 = 1;
        switch ((s16) lbl_1_bss_C.unk2) {           /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            Hu3DModelObjPosGet(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18, &sp14);
            if ((s16) lbl_1_bss_914->unk74[2].unk0 == 0) {
                fn_1_2834(&sp14, 1);
            } else {
                Hu3DModelHookObjReset(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18);
                temp_r7 = lbl_1_bss_914->unk58;
                temp_r3 = lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4;
                temp_r7[temp_r3].unk4.x = sp14.x;
                temp_r7[temp_r3].unk4.y = sp14.y;
                temp_r7[temp_r3].unk4.z = sp14.z;
                lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.x = -90.0f;
                lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.z = 0.0f;
                fn_1_2834(&sp14, 0);
            }
            lbl_1_bss_C.unk2 += 1;
            break;
        case 1:                                     /* switch 2 */
            Hu3DModelTPLvlSet(lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0, lbl_1_bss_C.unk8);
            temp_f1 = lbl_1_bss_C.unk8 - 0.05f;
            lbl_1_bss_C.unk8 = temp_f1;
            if (temp_f1 <= 0.0f) {
                Hu3DModelAttrSet(lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0, 1U);
                lbl_1_bss_C.unk2 += 1;
            }
            break;
        }
        lbl_1_bss_D0.unk2 += 1;
        break;
    case 1:                                         /* switch 1 */
        var_r26 = 0;
        switch ((s16) lbl_1_bss_C.unk2) {           /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            Hu3DModelObjPosGet(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18, &sp8);
            if ((s16) lbl_1_bss_914->unk74[2].unk0 == 0) {
                fn_1_2834(&sp8, 1);
            } else {
                Hu3DModelHookObjReset(lbl_1_bss_914->unk58[0x22].unk0, lbl_1_bss_C.unk18);
                temp_r5 = lbl_1_bss_914->unk58;
                temp_r0 = lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4;
                temp_r5[temp_r0].unk4.x = sp8.x;
                temp_r5[temp_r0].unk4.y = sp8.y;
                temp_r5[temp_r0].unk4.z = sp8.z;
                lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.x = -90.0f;
                lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk10.z = 0.0f;
                fn_1_2834(&sp8, 0);
            }
            lbl_1_bss_C.unk2 += 1;
            break;
        case 1:                                     /* switch 3 */
            Hu3DModelTPLvlSet(lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0, lbl_1_bss_C.unk8);
            temp_f1_2 = lbl_1_bss_C.unk8 - 0.05f;
            lbl_1_bss_C.unk8 = temp_f1_2;
            if (temp_f1_2 <= 0.0f) {
                Hu3DModelAttrSet(lbl_1_bss_914->unk58[lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4].unk0, 1U);
                lbl_1_bss_C.unk2 += 1;
            }
            break;
        case 2:                                     /* switch 3 */
            var_r26 = 1;
            break;
        }
        var_r29 = var_r26;
        var_r30 = 0;
loop_48:
        if (var_r30 < 2) {
            if (((s16) lbl_1_bss_80[var_r30].unkC == 0) || ((s16) lbl_1_bss_80[var_r30].unkC == 1)) {
                var_r27 = 0;
                temp_r0_2 = var_r30 + 0xA;
                temp_r4 = lbl_1_bss_80[var_r30].unk6;
                switch (temp_r4) {                  /* switch 4; irregular */
                case 0:                             /* switch 4 */
                    Hu3DModelObjPosGet(lbl_1_bss_914->unk58[var_r30 + 0x20].unk0, lbl_1_bss_80[var_r30].unk1C, &lbl_1_bss_914->unk58[temp_r0_2].unk4);
                    lbl_1_bss_914->unk58[temp_r0_2].unk10.y = 90.0f - (180.0f * (f32) var_r30);
                    Hu3DModelHookObjReset(lbl_1_bss_914->unk58[var_r30 + 0x20].unk0, lbl_1_bss_80[var_r30].unk1C);
                    temp_r4_2 = &lbl_1_bss_80[var_r30];
                    temp_r4_2->unk6 += 1;
                    break;
                case 1:                             /* switch 4 */
                    temp_r4_3 = &lbl_1_bss_80[var_r30];
                    temp_r4_3->unk10.x -= 0.05f;
                    temp_r4_4 = &lbl_1_bss_80[var_r30];
                    temp_r4_4->unk10.y -= 0.05f;
                    temp_r4_5 = &lbl_1_bss_80[var_r30];
                    temp_r4_5->unk10.z -= 0.05f;
                    temp_r5_2 = lbl_1_bss_914->unk58;
                    temp_r5_2[temp_r0_2].unk10.x += 20.0f;
                    Hu3DModelScaleSetV(lbl_1_bss_914->unk58[temp_r0_2].unk0, &lbl_1_bss_80[var_r30].unk10);
                    if (lbl_1_bss_80[var_r30].unk10.x <= 0.1f) {
                        Hu3DModelAttrSet(lbl_1_bss_914->unk58[temp_r0_2].unk0, 1U);
                        temp_r5_3 = &lbl_1_bss_80[var_r30];
                        temp_r5_3->unk6 += 1;
                    }
                    break;
                case 2:                             /* switch 4 */
                    var_r27 = 1;
                    break;
                }
                var_r29 *= var_r27;
            }
            var_r30 += 1;
            goto loop_48;
        }
        if (var_r29 != 0) {
            lbl_1_bss_D0.unk2 += 1;
        }
        break;
    case 2:                                         /* switch 1 */
        var_r29 = 1;
        break;
    }
    return var_r29;
}

s32 fn_1_7F30(void) {
    s16 temp_r31;
    s16 temp_r3;
    s32 temp_r31_2;
    s32 temp_r31_3;
    s32 temp_r31_4;
    s32 temp_r31_5;

    switch ((s16) lbl_1_bss_D0.unk0) {              /* irregular */
    case 0:
        fn_1_3EF8();
        fn_1_B36C();
        lbl_1_bss_D0.unk0 += 1;
        break;
    case 1:
        temp_r3 = lbl_1_bss_D0.unk6;
        lbl_1_bss_D0.unk6 = temp_r3 + 1;
        if (temp_r3 > 0xF0) {
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 2:
        temp_r31 = fn_1_18E8(&lbl_1_bss_8->unk1C.x, 60.0f, -12.0f, -211.0f);
        temp_r31_2 = temp_r31 + fn_1_18E8(&lbl_1_bss_8->unk1C.y, 60.0f, 208.0f, 218.0f);
        temp_r31_3 = temp_r31_2 + fn_1_18E8(&lbl_1_bss_8->unk1C.z, 60.0f, -120.0f, 0.0f);
        temp_r31_4 = temp_r31_3 + fn_1_18E8(&lbl_1_bss_8->unk10.x, 60.0f, -11.0f, -11.0f);
        temp_r31_5 = temp_r31_4 + fn_1_18E8(&lbl_1_bss_8->unk10.y, 60.0f, 0.0f, -29.0f);
        if ((s16) (temp_r31_5 + fn_1_18E8(&lbl_1_bss_8->unk34, 60.0f, 141.0f, 310.0f)) == 0) {
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    }
    return 0;
}

s16 fn_1_817C(void) {
    s16 temp_r31;
    s16 temp_r31_3;
    s16 temp_r31_6;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r29;
    s32 temp_r31_2;
    s32 temp_r31_4;
    s32 temp_r31_5;
    s32 temp_r31_7;
    s32 temp_r31_8;

    var_r29 = 0;
    switch ((s16) lbl_1_bss_D0.unk0) {              /* irregular */
    case 0:
        temp_r3 = lbl_1_bss_D0.unk6;
        lbl_1_bss_D0.unk6 = temp_r3 + 1;
        if (temp_r3 > 0x3C) {
            if ((s16) lbl_1_bss_D0.unk20 != 0) {
                lbl_1_bss_914->unk74[2].unk38 = 1;
                lbl_1_bss_914->unk74[2].unk3A = (lbl_1_bss_D0.unk20 & 1) + 2;
                lbl_1_bss_914->unk74[2].unk40 = 0.0f;
                lbl_1_bss_914->unk74[2].unk44 = 14.0f;
                lbl_1_bss_914->unk74[2].unk3C = 0;
                lbl_1_bss_914->unk74[2].unk20 = 0x40000001;
                fn_1_4020(5);
            }
            lbl_1_bss_D0.unk6 = 0;
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 1:
        if ((s16) lbl_1_bss_D0.unk20 != 0) {
            if ((s16) lbl_1_bss_914->unk74[2].unk38 == 3) {
                lbl_1_bss_D0.unk0 += 1;
            }
        } else {
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 2:
        if ((s16) lbl_1_bss_D0.unk20 != 0) {
            temp_r3_2 = lbl_1_bss_D0.unk6;
            lbl_1_bss_D0.unk6 = temp_r3_2 + 1;
            if (temp_r3_2 >= 0x1E) {
                lbl_1_bss_D0.unk0 += 1;
            }
        } else {
            lbl_1_bss_D0.unk0 += 1;
        }
        break;
    case 3:
        if ((s16) lbl_1_bss_D0.unk20 == 0) {
            temp_r31 = fn_1_18E8(&lbl_1_bss_8->unk1C.x, 30.0f, -211.0f, 0.0f);
            temp_r31_2 = temp_r31 + fn_1_18E8(&lbl_1_bss_8->unk10.y, 30.0f, -29.0f, 0.0f);
            if ((s16) (temp_r31_2 + fn_1_18E8(&lbl_1_bss_8->unk34, 30.0f, 310.0f, 560.0f)) == 0) {
                lbl_1_bss_D0.unk0 += 1;
            }
        } else if ((s32) (lbl_1_bss_D0.unk20 & 1) == 0) {
            temp_r31_3 = fn_1_18E8(&lbl_1_bss_8->unk1C.x, 30.0f, -211.0f, -217.0f);
            temp_r31_4 = temp_r31_3 + fn_1_18E8(&lbl_1_bss_8->unk1C.z, 30.0f, 0.0f, -120.0f);
            temp_r31_5 = temp_r31_4 + fn_1_18E8(&lbl_1_bss_8->unk10.y, 30.0f, -29.0f, 32.0f);
            if ((s16) (temp_r31_5 + fn_1_18E8(&lbl_1_bss_8->unk34, 30.0f, 310.0f, 304.0f)) == 0) {
                lbl_1_bss_D0.unk0 += 1;
            }
        } else {
            temp_r31_6 = fn_1_18E8(&lbl_1_bss_8->unk1C.x, 30.0f, -211.0f, 229.0f);
            temp_r31_7 = temp_r31_6 + fn_1_18E8(&lbl_1_bss_8->unk1C.z, 30.0f, 0.0f, -115.0f);
            temp_r31_8 = temp_r31_7 + fn_1_18E8(&lbl_1_bss_8->unk10.y, 30.0f, -29.0f, -28.0f);
            if ((s16) (temp_r31_8 + fn_1_18E8(&lbl_1_bss_8->unk34, 30.0f, 310.0f, 314.0f)) == 0) {
                lbl_1_bss_D0.unk0 += 1;
            }
        }
        break;
    case 4:
        var_r29 = 1;
        lbl_1_bss_D0.unk38 += 1;
        break;
    }
    return var_r29;
}

void fn_1_86BC(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        memset((M544Game *) &lbl_1_bss_828[var_r31], 0, 0x2C);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_8710(s32 player, s16 slot) {
    M544Fx *temp_r4;
    M544Fx *temp_r4_2;
    M544Fx *temp_r4_3;
    M544Fx *temp_r4_4;
    M544Fx *temp_r4_5;

    if (slot < 4) {
        memset((M544Game *) &lbl_1_bss_828[slot], 0, 0x2C);
        lbl_1_bss_828[slot].unk20 = 1;
        lbl_1_bss_828[slot].unk24 = player;
        lbl_1_bss_828[slot].unk28 = 1.0f;
        Hu3DModelObjPosGet(lbl_1_bss_914->unk58[player + 0x20].unk0, CharModelItemHookGet(lbl_1_bss_914->unk4[player].unk2, 1, 0), &lbl_1_bss_828[slot].unk0);
        Hu3DModelObjPosGet(lbl_1_bss_914->unk58[(player ^ 1) + 0x20].unk0, CharModelItemHookGet(lbl_1_bss_914->unk4[player ^ 1].unk2, 1, 4), &lbl_1_bss_828[slot].unkC);
        if ((s16) lbl_1_bss_914->unk4[player ^ 1].unk2 == 6) {
            lbl_1_bss_828[slot].unkC.y = 180.0f;
            if ((s32) (player ^ 1) != 0) {
                temp_r4 = &lbl_1_bss_828[slot];
                temp_r4->unkC.x -= 30.0f;
            } else {
                temp_r4_2 = &lbl_1_bss_828[slot];
                temp_r4_2->unkC.x += 30.0f;
            }
        }
        temp_r4_3 = &lbl_1_bss_828[slot];
        temp_r4_3->unkC.y += 20.0f;
        if ((s32) (player ^ 1) != 0) {
            temp_r4_4 = &lbl_1_bss_828[slot];
            temp_r4_4->unkC.x -= 50.0f;
            return;
        }
        temp_r4_5 = &lbl_1_bss_828[slot];
        temp_r4_5->unkC.x += 45.0f;
    }
}

void fn_1_89AC(omObjData *obj) {
    M544Anim *temp_r31;
    M544Anim *temp_r31_2;
    M544Anim *temp_r31_3;
    M544Anim *temp_r31_4;
    M544Fx *temp_r4;
    M544Fx *temp_r4_2;
    M544Fx *temp_r4_3;
    M544Fx *temp_r4_4;
    M544Fx *temp_r4_5;
    M544Fx *temp_r4_6;
    s32 temp_r0;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r30;

    var_r30 = 0;
loop_21:
    if (var_r30 < 4) {
        if ((s32) lbl_1_bss_828[var_r30].unk20 != 0) {
            temp_r0 = lbl_1_bss_828[var_r30].unk1C;
            switch (temp_r0) {                      /* irregular */
            case 0:
                fn_1_8E98(var_r30, 0);
                temp_r4 = &lbl_1_bss_828[var_r30];
                temp_r4->unk1C += 1;
                break;
            case 1:
                temp_r31 = &lbl_1_bss_914->unk74[lbl_1_bss_828[var_r30].unk24 ^ 1];
                temp_r4_2 = &lbl_1_bss_828[var_r30];
                temp_r4_2->unk18 += 1;
                fn_1_91B4(var_r30, lbl_1_bss_828[var_r30].unk18);
                if ((s32) lbl_1_bss_828[var_r30].unk18 >= 0xA) {
                    fn_1_8E98(var_r30, 1);
                    temp_r4_3 = &lbl_1_bss_828[var_r30];
                    temp_r4_3->unk1C += 1;
                    lbl_1_bss_828[var_r30].unk18 = 0;
                    temp_r31->unk38 = 1;
                    temp_r31->unk3A = 1;
                    temp_r31->unk40 = 0.0f;
                    temp_r31->unk44 = 10.0f;
                    temp_r31->unk3C = 0;
                    temp_r31->unk20 = 0;
                    lbl_1_bss_828[var_r30].unk18 = 0;
                    Hu3DModelAttrSet(lbl_1_bss_914->unk58[(s16) ((s16) (lbl_1_bss_828[var_r30].unk24 ^ 1) + 0xA)].unk0, 1U);
                    omVibrate(lbl_1_bss_914->unk4[lbl_1_bss_828[var_r30].unk24 ^ 1].unk0, 0xC, 0xC, 0);
                }
                break;
            case 2:
                temp_r31_2 = &lbl_1_bss_914->unk74[lbl_1_bss_828[var_r30].unk24 ^ 1];
                temp_r4_4 = &lbl_1_bss_828[var_r30];
                temp_r3 = temp_r4_4->unk18;
                temp_r4_4->unk18 = temp_r3 + 1;
                if (temp_r3 == 0x2D) {
                    temp_r31_2->unk38 = 1;
                    temp_r31_2->unk3A = 0;
                    temp_r31_2->unk40 = 0.0f;
                    temp_r31_2->unk44 = 10.0f;
                    temp_r31_2->unk3C = 0x40000001;
                    temp_r31_2->unk20 = 0;
                    lbl_1_bss_828[var_r30].unk20 = 0;
                }
                fn_1_9364(var_r30, 0);
                break;
            case 3:
                temp_r31_3 = &lbl_1_bss_914->unk74[lbl_1_bss_828[var_r30].unk24];
                fn_1_8E98(var_r30, 2);
                temp_r31_3->unk38 = 1;
                temp_r31_3->unk3A = 1;
                temp_r31_3->unk40 = 0.0f;
                temp_r31_3->unk44 = 10.0f;
                temp_r31_3->unk3C = 0;
                temp_r31_3->unk20 = 0;
                Hu3DModelAttrSet(lbl_1_bss_914->unk58[(s16) ((s16) lbl_1_bss_828[var_r30].unk24 + 0xA)].unk0, 1U);
                lbl_1_bss_828[var_r30].unk18 = 0;
                temp_r4_5 = &lbl_1_bss_828[var_r30];
                temp_r4_5->unk1C += 1;
                break;
            case 4:
                temp_r31_4 = &lbl_1_bss_914->unk74[lbl_1_bss_828[var_r30].unk24];
                temp_r4_6 = &lbl_1_bss_828[var_r30];
                temp_r3_2 = temp_r4_6->unk18;
                temp_r4_6->unk18 = temp_r3_2 + 1;
                if (temp_r3_2 == 0x2D) {
                    temp_r31_4->unk38 = 1;
                    temp_r31_4->unk3A = 0;
                    temp_r31_4->unk40 = 0.0f;
                    temp_r31_4->unk44 = 10.0f;
                    temp_r31_4->unk3C = 0x40000001;
                    temp_r31_4->unk20 = 0;
                    lbl_1_bss_828[var_r30].unk20 = 0;
                }
                fn_1_9364(var_r30, 1);
                break;
            }
        }
        var_r30 += 1;
        goto loop_21;
    }
}

void fn_1_8E98(s32 slot, s32 step) {
    s32 sp8;
    M544Model *temp_r31;
    M544Model *temp_r31_2;
    M544Model *temp_r31_3;

    sp8 = step;
    switch (sp8) {                                  /* irregular */
    case 0:
        temp_r31 = &lbl_1_bss_914->unk58[slot + 0xC];
        Hu3DMotionSpeedSet(temp_r31->unk0, 10.0f);
        Hu3DMotionTimeSet(temp_r31->unk0, 0.0f);
        Hu3DModelAttrReset(temp_r31->unk0, 1U);
        temp_r31->unk4.x = lbl_1_bss_828[slot].unk0.x;
        temp_r31->unk4.y = lbl_1_bss_828[slot].unk0.y;
        temp_r31->unk4.z = lbl_1_bss_828[slot].unk0.z;
        return;
    case 1:
        Hu3DModelAttrSet(lbl_1_bss_914->unk58[slot + 0xC].unk0, 1U);
        temp_r31_2 = &lbl_1_bss_914->unk58[slot + 0x10];
        Hu3DModelAttrReset(temp_r31_2->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31_2->unk0, 6.0f);
        Hu3DMotionTimeSet(temp_r31_2->unk0, 0.0f);
        temp_r31_2->unk4.x = lbl_1_bss_828[slot].unkC.x;
        temp_r31_2->unk4.y = lbl_1_bss_828[slot].unkC.y;
        temp_r31_2->unk4.z = lbl_1_bss_828[slot].unkC.z;
        Hu3DModelPosSetV(temp_r31_2->unk0, &temp_r31_2->unk4);
        if ((s32) lbl_1_bss_828[slot].unk24 != 0) {
            temp_r31_2->unk10.y = -45.0f;
        } else {
            temp_r31_2->unk10.y = 90.0f;
        }
        Hu3DModelRotSetV(temp_r31_2->unk0, &temp_r31_2->unk10);
        return;
    case 2:
        temp_r31_3 = &lbl_1_bss_914->unk58[slot + 0x10];
        Hu3DModelAttrReset(temp_r31_3->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31_3->unk0, 8.0f);
        Hu3DMotionTimeSet(temp_r31_3->unk0, 0.0f);
        temp_r31_3->unk4.x = lbl_1_bss_828[slot].unk0.x;
        temp_r31_3->unk4.y = lbl_1_bss_828[slot].unk0.y;
        temp_r31_3->unk4.z = lbl_1_bss_828[slot].unk0.z;
        temp_r31_3->unk4.y += 20.0f;
        Hu3DModelPosSetV(temp_r31_3->unk0, &temp_r31_3->unk4);
        if ((s32) lbl_1_bss_828[slot].unk24 != 0) {
            temp_r31_3->unk10.y = 90.0f;
        } else {
            temp_r31_3->unk10.y = -45.0f;
        }
        Hu3DModelRotSetV(temp_r31_3->unk0, &temp_r31_3->unk10);
        return;
    }
}

void fn_1_91B4(s32 slot, s32 frame) {
    M544Model *temp_r31;

    temp_r31 = &lbl_1_bss_914->unk58[slot + 0xC];
    temp_r31->unk4.x = lbl_1_bss_828[slot].unk0.x + (((f32) frame * (lbl_1_bss_828[slot].unkC.x - lbl_1_bss_828[slot].unk0.x)) / 10.0f);
    temp_r31->unk4.y = lbl_1_bss_828[slot].unk0.y + (((f32) frame * (lbl_1_bss_828[slot].unkC.y - lbl_1_bss_828[slot].unk0.y)) / 10.0f);
    temp_r31->unk4.z = lbl_1_bss_828[slot].unk0.z + (((f32) frame * (lbl_1_bss_828[slot].unkC.z - lbl_1_bss_828[slot].unk0.z)) / 10.0f);
}

s32 fn_1_9364(s32 slot, s32 mode) {
    s32 sp8;
    HSFMATERIAL *var_r31;
    HU3DMODEL *var_r30;
    M544Fx *temp_r6;
    f32 temp_f31;
    s32 var_r29;

    sp8 = 1;
    if (mode != 0) {
        var_r30 = &Hu3DData[lbl_1_bss_914->unk58[lbl_1_bss_828[slot].unk24 + 0x20].unk0];
    } else {
        var_r30 = &Hu3DData[lbl_1_bss_914->unk58[(lbl_1_bss_828[slot].unk24 ^ 1) + 0x20].unk0];
    }
    var_r31 = var_r30->hsf->material;
    temp_r6 = &lbl_1_bss_828[slot];
    temp_r6->unk28 = (f32) ((f64) temp_r6->unk28 * 0.99);
    if (lbl_1_bss_828[slot].unk28 < 0.05f) {
        lbl_1_bss_828[slot].unk28 = 0.0f;
    }
    temp_f31 = lbl_1_bss_828[slot].unk28;
    if (temp_f31 > 0.865f) {
        var_r29 = 0;
loop_8:
        if (var_r29 < (s16) var_r30->hsf->materialNum) {
            var_r31->color[0] = (u8) (s32) ((f32) var_r31->color[0] * temp_f31);
            var_r31->color[1] = (u8) (s32) ((f32) var_r31->color[1] * temp_f31);
            var_r31->color[2] = (u8) (s32) ((f32) var_r31->color[2] * temp_f31);
            var_r29 += 1;
            var_r31++;
            goto loop_8;
        }
    }
    if (lbl_1_bss_828[slot].unk28 == 0.0f) {
        return 1;
    }
    return 0;
}

void fn_1_95D8(s32 arg0, s32 arg1) {
    s32 sp14[2];
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r31;

    sp8 = arg0;
    spC = arg1;
    sp14[0] = sp8;
    sp14[1] = spC;
    var_r31 = 0;
    sp10 = -1;
loop_4:
    if (var_r31 < 2) {
        if ((s32) sp14[var_r31] >= 0) {
            memset((M544Game *) &lbl_1_bss_828[sp14[var_r31]], 0, 0x2C);
            lbl_1_bss_828[sp14[var_r31]].unk20 = 1;
            lbl_1_bss_828[sp14[var_r31]].unk1C = 3;
            lbl_1_bss_828[sp14[var_r31]].unk24 = var_r31;
            lbl_1_bss_828[sp14[var_r31]].unk28 = 1.0f;
            Hu3DModelObjPosGet(lbl_1_bss_914->unk58[var_r31 + 0x20].unk0, CharModelItemHookGet(lbl_1_bss_914->unk4[var_r31].unk2, 1, 0), &lbl_1_bss_828[sp14[var_r31]].unk0);
            omVibrate(lbl_1_bss_914->unk4[var_r31].unk0, 0xC, 0xC, 0);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_9798(s16 player) {
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r0_3;
    s16 temp_r30;
    s16 var_r26;
    s16 var_r29;

    temp_r30 = lbl_1_bss_914->unk4[player].unk4 - 1;
    var_r26 = 0;
    var_r29 = 0;
loop_3:
    if (var_r26 < 0xA) {
        if ((s16) lbl_1_bss_8D8[var_r26].unk4 >= 6) {
            var_r29 += 1;
            var_r26 += 1;
            goto loop_3;
        }
    }
    if ((frandmod(0x64U) > (s32) (lbl_1_data_3EC[temp_r30].unk6 - (var_r29 * 5))) && ((s16) lbl_1_bss_80[player].unk24 == 0) && (var_r29 != 0)) {
        lbl_1_bss_80[player].unk24 = 2;
    }
    if ((frandmod(0x64U) > (s16) lbl_1_data_3EC[temp_r30].unk4) && ((s16) lbl_1_bss_80[player].unk24 == 0)) {
        lbl_1_bss_80[player].unk24 = 1;
    }
    if ((frandmod(0x64U) > (s16) lbl_1_data_3EC[temp_r30].unk8) && ((s16) lbl_1_bss_80[player].unk24 == 0)) {
        lbl_1_bss_80[player].unk24 = 3;
    }
    temp_r0 = lbl_1_bss_80[player].unk24;
    switch (temp_r0) {                              /* irregular */
    default:
        lbl_1_bss_80[player].unk22 = lbl_1_data_3EC[temp_r30].unk0 + frandmod(lbl_1_data_3EC[temp_r30].unk2 - lbl_1_data_3EC[temp_r30].unk0);
        return;
    case 2:
        if (var_r29 != 0) {
            lbl_1_bss_80[player].unk26 = frandmod((u32) var_r29);
        } else {
            lbl_1_bss_80[player].unk26 = 0;
        }
        temp_r0_2 = lbl_1_bss_8D8[lbl_1_bss_80[player].unk26].unk2 - 0x1D;
        if (temp_r0_2 > 0) {
            lbl_1_bss_80[player].unk22 = frandmod((u32) temp_r0_2) + 0x1E;
        } else {
            lbl_1_bss_80[player].unk22 = 0x1E;
        }
        if ((s16) lbl_1_data_3EC[temp_r30].unk2 < (s16) lbl_1_bss_80[player].unk22) {
            lbl_1_bss_80[player].unk22 = lbl_1_data_3EC[temp_r30].unk0 + frandmod(lbl_1_data_3EC[temp_r30].unk2 - lbl_1_data_3EC[temp_r30].unk0);
            return;
        }
        return;
    case 3:
        if (var_r29 != 0) {
            lbl_1_bss_80[player].unk26 = frandmod((u32) var_r29);
        } else {
            lbl_1_bss_80[player].unk26 = 0;
        }
        temp_r0_3 = lbl_1_bss_8D8[lbl_1_bss_80[player].unk26].unk0 - 0x1D;
        if (temp_r0_3 > 0) {
            lbl_1_bss_80[player].unk22 = frandmod((u32) temp_r0_3) + 0x1E;
            return;
        }
        lbl_1_bss_80[player].unk22 = 0x1E;
        break;
    }
}

s16 fn_1_9C84(s16 player) {
    s16 sp8;
    M544Pl *temp_r5;
    M544Pl *temp_r5_2;
    M544Pl *temp_r5_3;
    M544Pl *temp_r5_4;
    s16 temp_r0;
    s16 temp_r4;
    s16 temp_r4_2;
    s16 temp_r4_3;
    s16 temp_r4_4;
    s16 var_r30;
    s16 var_r31;

    var_r31 = 0;
    sp8 = lbl_1_bss_914->unk4[player].unk4 - 1;
    temp_r0 = lbl_1_bss_80[player].unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) lbl_1_bss_D0.unk28 != 0) {
            temp_r5 = &lbl_1_bss_80[player];
            temp_r4 = temp_r5->unk22;
            temp_r5->unk22 = temp_r4 - 1;
            if (temp_r4 <= 0) {
                var_r31 = lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4 | 0x80;
            }
        }
        break;
    case 1:
        if ((s16) lbl_1_bss_D0.unk28 != 0) {
            temp_r5_2 = &lbl_1_bss_80[player];
            temp_r4_2 = temp_r5_2->unk22;
            temp_r5_2->unk22 = temp_r4_2 - 1;
            if (temp_r4_2 <= 0) {
                var_r30 = 0;
loop_15:
                if (var_r30 <= 5) {
                    if (var_r30 == (s16) lbl_1_bss_8D8[lbl_1_bss_C.unk12].unk4) {
                        var_r30 += 1;
                        goto loop_15;
                    }
                }
                var_r31 = var_r30 | 0x80;
            }
        }
        break;
    case 2:
        if (((s16) lbl_1_bss_C.unk12 == (s16) lbl_1_bss_80[player].unk26) && ((s16) lbl_1_bss_C.unk0 == 1)) {
            temp_r5_3 = &lbl_1_bss_80[player];
            temp_r4_3 = temp_r5_3->unk22;
            temp_r5_3->unk22 = temp_r4_3 - 1;
            if (temp_r4_3 <= 0) {
                var_r31 = 0x80;
            }
        }
        break;
    case 3:
        if (((s16) lbl_1_bss_C.unk12 == (s16) lbl_1_bss_80[player].unk26) && ((s16) lbl_1_bss_C.unk0 == 0)) {
            temp_r5_4 = &lbl_1_bss_80[player];
            temp_r4_4 = temp_r5_4->unk22;
            temp_r5_4->unk22 = temp_r4_4 - 1;
            if (temp_r4_4 <= 0) {
                var_r31 = 0x80;
            }
        }
        break;
    }
    return var_r31;
}



void ObjectSetup(void) {
    s16 var_r31;

    lbl_1_bss_818 = omInitObjMan(0x32, 0x2000);
    omGameSysInit(lbl_1_bss_818);
    fn_1_9EF8(&lbl_1_bss_530, lbl_1_bss_15C, lbl_1_data_1A4);
    lbl_1_bss_8 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x148, MEMORY_DEFAULT_NUM);
    memset((M544Game *) lbl_1_bss_8, 0, 0x148);
    lbl_1_bss_4 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x3C, MEMORY_DEFAULT_NUM);
    memset((M544Game *) lbl_1_bss_4, 0, 0x3C);
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x50, MEMORY_DEFAULT_NUM);
    memset((M544Game *) lbl_1_bss_0, 0, sizeof(M544Shadow));
    fn_1_4F0(0);
    fn_1_F38();
    fn_1_1440();
    fn_1_A144(1);
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        fn_1_A3F0(var_r31, &lbl_1_data_28[Mp5CharNo(lbl_1_bss_530.unk4[var_r31].unk2)]);
        fn_1_A410(var_r31, lbl_1_bss_130[var_r31]);
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_A3F0(2, (M544Char *) lbl_1_data_194);
    fn_1_A410(2, lbl_1_bss_130[2]);
    fn_1_A430();
    fn_1_ADBC();
    omAddObjEx(lbl_1_bss_818, 0x7FDA, 0U, 0U, -1, fn_1_A9A4);
    omAddObjEx(lbl_1_bss_818, 0x7FDA, 0U, 0U, -1, fn_1_AF60);
    omAddObjEx(lbl_1_bss_818, 0x7FDA, 0U, 0U, -1, fn_1_4EC);
    fn_1_86BC();
    omAddObjEx(lbl_1_bss_818, 0x7FDA, 0U, 0U, -1, fn_1_89AC);
    omAddObjEx(lbl_1_bss_818, 0x7FDA, 0U, 0U, -1, fn_1_B318);
    Hu3DBGColorSet(0xBAU, 0xF5U, 0xFFU);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 0x12C);
    MgSeqModeDelaySet(2, 0x140);
    MgSeqModeDelaySet(7, 0xB4);
    MgSeqModeDelaySet(9, 0x3C);
}

void fn_1_37C(void) {
    if (fn_1_4328(&lbl_1_bss_530) != 0) {
        MgSeqModeNext();
    }
}

void fn_1_3B0(void) {
    if (fn_1_4E08() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_3DC(void) {
    fn_1_4E3C();
}

void fn_1_3FC(void) {
    if (fn_1_4EB4() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_428(void) {
    fn_1_5098();
}

void fn_1_448(void) {
    if (fn_1_511C() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_474(void) {
    if (fn_1_5158() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_4A0(void) {
    fn_1_5514();
}

void fn_1_4C0(void) {
    if (fn_1_5544() != 0) {
        MgSeqModeNext();
    }
}

void fn_1_4EC(omObjData *obj) {

}

void fn_1_4F0(s16 cam) {
    lbl_1_bss_8[cam].unk0 = (s32) cam;
    lbl_1_bss_8[cam].unk1C.x = lbl_1_data_210[cam].unk0.x;
    lbl_1_bss_8[cam].unk1C.y = lbl_1_data_210[cam].unk0.y;
    lbl_1_bss_8[cam].unk1C.z = lbl_1_data_210[cam].unk0.z;
    lbl_1_bss_8[cam].unk10.x = lbl_1_data_210[cam].unkC.x;
    lbl_1_bss_8[cam].unk10.y = lbl_1_data_210[cam].unkC.y;
    lbl_1_bss_8[cam].unk10.z = lbl_1_data_210[cam].unkC.z;
    lbl_1_bss_8[cam].unk34 = lbl_1_data_210[cam].unk18;
    lbl_1_bss_8[cam].unk38 = lbl_1_data_210[cam].unk1C;
    lbl_1_bss_8[cam].unk3C = lbl_1_data_210[cam].unk20;
    lbl_1_bss_8[cam].unk40 = lbl_1_data_210[cam].unk24;
    lbl_1_bss_8[cam].unk44 = lbl_1_data_210[cam].unk28;
    lbl_1_bss_8[cam].unk48 = lbl_1_data_210[cam].unk2C;
    lbl_1_bss_8[cam].unk4C = lbl_1_data_210[cam].unk30;
    Hu3DCameraCreate((s32) lbl_1_data_2E0[cam]);
    Hu3DCameraViewportSet((s32) lbl_1_data_2E0[cam], lbl_1_bss_8[cam].unk3C, lbl_1_bss_8[cam].unk40, lbl_1_bss_8[cam].unk44, lbl_1_bss_8[cam].unk48, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet((s32) lbl_1_data_2E0[cam], lbl_1_bss_8[cam].unk4C, 20.0f, 30000.0f, lbl_1_bss_8[cam].unk38);
    fn_1_9C0(cam);
    Center.x = lbl_1_data_210->unk0.x;
    Center.y = lbl_1_data_210->unk0.y;
    Center.z = lbl_1_data_210->unk0.z;
    CRot.x = lbl_1_data_210->unkC.x;
    CRot.y = lbl_1_data_210->unkC.y;
    CRot.z = lbl_1_data_210->unkC.z;
    CZoom = lbl_1_data_210[cam].unk18;
}

void fn_1_9C0(s16 cam) {
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
    Hu3DCameraPosSet((s32) lbl_1_data_2E0[cam], lbl_1_bss_8[cam].unk4.x, lbl_1_bss_8[cam].unk4.y, lbl_1_bss_8[cam].unk4.z, lbl_1_bss_8[cam].unk28.x, lbl_1_bss_8[cam].unk28.y, lbl_1_bss_8[cam].unk28.z, lbl_1_bss_8[cam].unk1C.x, lbl_1_bss_8[cam].unk1C.y, lbl_1_bss_8[cam].unk1C.z);
}

void fn_1_F38(void) {
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
    fn_1_1168();
    Hu3DGLightStaticSet(lbl_1_bss_4->unk0, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_4->unk0);
}

void fn_1_1168(void) {
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

void fn_1_1440(void) {
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
    fn_1_1570();
}

void fn_1_1570(void) {
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

s16 fn_1_18E8(f32 *val, f32 frames, f32 from, f32 to) {
    f32 temp_f31;
    f32 var_f29;
    f32 var_f30;
    s16 var_r31;

    temp_f31 = (to - from) / frames;
    *val += temp_f31;
    if (temp_f31 != 0.0f) {
        var_r31 = (s16) ((to - *val) / temp_f31);
    } else {
        var_r31 = 0;
    }
    if (var_r31 == 0) {
        var_r31 = 1;
    }
    if ((from - to) > 0.0f) {
        var_f30 = from - to;
    } else {
        var_f30 = from - (-1.0f * to);
    }
    if ((from - *val) > 0.0f) {
        var_f29 = from - *val;
    } else {
        var_f29 = from - (-1.0f * *val);
    }
    if (var_f30 <= var_f29) {
        *val = to;
        var_r31 = 0;
    }
    return var_r31;
}

MGTIMER *fn_1_1A1C(s32 arg0, s32 arg1, s32 arg2, f32 x, f32 y) {
    f32 sp18;
    f32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    MGTIMER *temp_r3;

    sp8 = arg0;
    spC = arg1;
    sp10 = arg2;
    sp14 = x;
    sp18 = y;
    temp_r3 = MgTimerCreate(arg0);
    MgTimerParamSet(temp_r3, spC * 0x3C, sp10 * 0x3C, 0);
    MgTimerPosSet(temp_r3, x, y);
    return temp_r3;
}

void fn_1_1A90(MGTIMER *timer) {
    MGTIMER *sp8;

    sp8 = timer;
    MgTimerModeOnSet(timer, 1);
}


void fn_1_1AE4(MGTIMER *timer) {
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}



void fn_1_2330(void) {
    ANIMDATA *temp_r28;
    s16 var_r29;
    HU3DPARTICLE *temp_r31;
    HU3DPARTICLEDATA *var_r30;

    temp_r28 = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M544, 31), MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_820 = HuMemDirectMallocNum(HEAP_SYSTEM, 0xAF0, MEMORY_DEFAULT_NUM);
    lbl_1_bss_826 = Hu3DParticleCreate(temp_r28, 0x32);
    Hu3DParticleHookSet(lbl_1_bss_826, fn_1_30B8);
    Hu3DModelLayerSet(lbl_1_bss_826, 3);
    Hu3DModelCameraSet(lbl_1_bss_826, 1U);
    Hu3DModelAttrSet(lbl_1_bss_826, 1U);
    Hu3DModelAttrReset(lbl_1_bss_826, 1U);
    Hu3DParticleBlendModeSet(lbl_1_bss_826, 1U);
    temp_r31 = Hu3DData[lbl_1_bss_826].hookData;
    temp_r31->emitCnt = 0;
    temp_r31->work = (void *) lbl_1_bss_820;
    temp_r31->count = 0;
    var_r29 = 0;
    var_r30 = temp_r31->data;
loop_2:
    if (var_r29 < (s16) temp_r31->maxCnt) {
        var_r30->scale = 0.0f;
        var_r29 += 1;
        var_r30++;
        goto loop_2;
    }
}


void fn_1_2834(Vec *pos, s16 mode) {
    f32 sp14;
    f32 sp10;
    f32 spC;
    s16 sp8;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 var_r30;
    s16 var_r30_2;

    sp8 = mode;
    if (sp8 == 0) {
        pos->y += 50.0f;
        var_r30 = 0;
loop_3:
        if (var_r30 < 0x30) {
            temp_f31 = 5.0f + (f32) frandmod(5U);
            lbl_1_data_370.unkC.x = (f32) frandmod(0xAU) - 5.0f;
            lbl_1_data_370.unkC.y = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) (7.5f * (f32) var_r30)) / 180.0));
            lbl_1_data_370.unkC.z = (f32) frandmod(2U);
            lbl_1_data_370.unk30 = (f32) (s16) (-frandmod(6U) - 5);
            spC = (pos->x + (f32) frandmod(0x1EU)) - 15.0f;
            sp10 = (f32) ((f64) pos->y + (40.0 * sin((3.141592653589793 * (f64) (7.5f * (f32) var_r30)) / 180.0)));
            sp14 = 20.0f + pos->z;
            lbl_1_data_370.unk24 = 0.01f * (f32) frandmod(0x14U);
            fn_1_2EE4(&lbl_1_data_370, spC, sp10, sp14, (f32) (20.0 + (f64) frandmod(0x14U)));
            var_r30 += 1;
            goto loop_3;
        }
        return;
    }
    pos->x -= 20.0f;
    pos->z += 50.0f;
    var_r30_2 = 0;
loop_7:
    if (var_r30_2 < 0x24) {
        temp_f31_2 = 5.0f + (f32) frandmod(5U);
        lbl_1_data_370.unkC.x = (f32) frandmod(4U) - 2.0f;
        lbl_1_data_370.unkC.y = (f32) frandmod(6U) - 3.0f;
        lbl_1_data_370.unkC.z = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) (10.0f * (f32) var_r30_2)) / 180.0));
        lbl_1_data_370.unk30 = (f32) (s16) (-frandmod(6U) - 5);
        spC = pos->x + (f32) frandmod(3U);
        sp10 = (pos->y + (f32) frandmod(0x1EU)) - 15.0f;
        sp14 = (f32) ((f64) pos->z + (40.0 * sin((3.141592653589793 * (f64) (10.0f * (f32) var_r30_2)) / 180.0)));
        lbl_1_data_370.unk24 = 0.01f * (f32) frandmod(0x14U);
        fn_1_2EE4(&lbl_1_data_370, spC, sp10, sp14, (f32) (20.0 + (f64) frandmod(0x14U)));
        var_r30_2 += 1;
        goto loop_7;
    }
}

s16 fn_1_2EE4(M544Part *tmpl, f32 x, f32 y, f32 z, f32 scale) {
    s16 var_r26;
    s16 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    var_r26 = -1;
    temp_r30 = Hu3DData[lbl_1_bss_826].hookData;
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
        memcpy((M544Part *) temp_r30->work + var_r29, tmpl, sizeof(M544Part));
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
        var_r26 = var_r29;
    }
    return var_r26;
}

static s16 M544ColorStep(u8 cur, const M544Part *w, s32 k) {
    s16 v = (s16) ((f32) cur + (w->unk34 * (f32) (w->unk8[k] - w->unk4[k])));
    return v < 0 ? 0 : v > 0xFF ? 0xFF : v;
}

void fn_1_30B8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    M544Part *work;
    s16 temp_r29;
    s16 var_r28;

    work = particleP->work;
    var_r31 = particleP->data;
    var_r31->time = 0;
    for (var_r28 = 0; var_r28 < (s16) particleP->maxCnt; var_r28++, var_r31++) {
        if (var_r31->scale > 0.0f) {
            var_r31->vel.x *= work[var_r28].unk18.x;
            var_r31->vel.y *= work[var_r28].unk18.y;
            var_r31->vel.z *= work[var_r28].unk18.z;
            VECAdd(&var_r31->vel, &var_r31->pos, &var_r31->pos);
            var_r31->vel.y += work[var_r28].unk24;
            var_r31->color.r = (u8) M544ColorStep(var_r31->color.r, &work[var_r28], 0);
            var_r31->color.g = (u8) M544ColorStep(var_r31->color.g, &work[var_r28], 1);
            var_r31->color.b = (u8) M544ColorStep(var_r31->color.b, &work[var_r28], 2);
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


void fn_1_34D0(void) {
    lbl_1_bss_824 = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M544, 30), MEMORY_DEFAULT_NUM, HEAP_DATA)), 1);
    Hu3DParticleHookSet(lbl_1_bss_824, fn_1_3AD4);
    Hu3DParticleBlendModeSet(lbl_1_bss_824, 0U);
    Hu3DModelLayerSet(lbl_1_bss_824, 7);
    Hu3DModelAttrSet(lbl_1_bss_824, 1U);
    Hu3DModelAttrReset(lbl_1_bss_824, 1U);
    lbl_1_bss_D0.unk2C = 0;
    ((HU3DPARTICLE *) Hu3DData[lbl_1_bss_824].hookData)->data[0].scale = 0.0f;
}

void fn_1_35DC(s16 player) {
    Vec sp8;
    Vec sp14;
    const f32 *tbl;
    M544Model *mdl;
    s16 chr;
    f32 scale;

    chr = lbl_1_bss_914->unk4[player].unk2;
    if (chr >= 0xD) {
        chr = 6;
    }
    if (player >= 2) {
        player = (s16) ((s32) (lbl_1_bss_D0.unk20 & 2) >> 1);
    }
    mdl = &lbl_1_bss_914->unk58[player + 0x20];
    if (player == 0) {
        tbl = lbl_1_rodata_D8[chr];
        scale = 35.0f;
    } else {
        tbl = lbl_1_rodata_210[chr];
        scale = 50.0f;
    }
    sp14.x = mdl->unk4.x + tbl[0];
    sp14.y = mdl->unk4.y + tbl[1] + lbl_1_rodata_A4[chr];
    sp14.z = mdl->unk4.z + tbl[2];
    sp8.x = mdl->unk4.x + tbl[3];
    sp8.y = mdl->unk4.y + tbl[4] + lbl_1_rodata_A4[chr];
    sp8.z = mdl->unk4.z + tbl[5];
    fn_1_39E8(&sp14, &sp8, scale);
}


void fn_1_39E8(Vec *from, Vec *to, f32 scale) {
    HU3DPARTICLEDATA *data;

    data = ((HU3DPARTICLE *) Hu3DData[lbl_1_bss_824].hookData)->data;
    data->time = 0;
    data->parManId = 0;
    data->pos = *from;
    data->vel = *from;
    data->accel = *to;
    data->color.r = 0xFF;
    data->color.g = 0xFF;
    data->color.b = 0xFF;
    data->color.a = 0xFF;
    data->scale = scale;
    if (data->scale != 0.0f) {
        lbl_1_bss_D0.unk2C = 1;
    }
}


void fn_1_3AD4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *temp_r31;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    f32 var_f25;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r28;
    s16 var_r29;
    u8 temp_r0_2;

    temp_r31 = particleP->data;
    if (temp_r31->scale > 0.0f) {
        temp_r0 = temp_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            temp_f29 = temp_r31->accel.y;
            temp_f31 = temp_r31->vel.y;
            temp_f27 = (temp_f29 - temp_f31) / 10.0f;
            temp_r31->pos.y += temp_f27;
            if (temp_f27 != 0.0f) {
                var_r29 = (s16) ((temp_f29 - temp_r31->pos.y) / temp_f27);
            } else {
                var_r29 = 0;
            }
            if (var_r29 == 0) {
                var_r29 = 1;
            }
            if ((temp_f31 - temp_f29) > 0.0f) {
                var_f25 = temp_f31 - temp_f29;
            } else {
                var_f25 = temp_f31 - (-1.0f * temp_f29);
            }
            if ((temp_f31 - temp_r31->pos.y) > 0.0f) {
                var_f24 = temp_f31 - temp_r31->pos.y;
            } else {
                var_f24 = temp_f31 - (-1.0f * temp_r31->pos.y);
            }
            if (var_f25 <= var_f24) {
                temp_r31->pos.y = temp_f29;
                var_r29 = 0;
            }
            if (var_r29 == 0) {
                temp_r31->vel.x = temp_r31->pos.x;
                temp_r31->vel.y = temp_r31->pos.y;
                temp_r31->vel.z = temp_r31->pos.z;
                temp_r31->accel.x = temp_r31->pos.x;
                temp_r31->accel.y = temp_r31->pos.y;
                temp_r31->accel.z = temp_r31->pos.z;
                temp_r31->accel.y -= 20.0f;
                temp_r31->speedDecay = 3.0f;
                temp_r31->time += 1;
            }
            break;
        case 1:
            temp_f28 = temp_r31->accel.y;
            temp_f30 = temp_r31->vel.y;
            temp_f26 = (temp_f28 - temp_f30) / 3.0f;
            temp_r31->pos.y += temp_f26;
            if (temp_f26 != 0.0f) {
                var_r28 = (s16) ((temp_f28 - temp_r31->pos.y) / temp_f26);
            } else {
                var_r28 = 0;
            }
            if (var_r28 == 0) {
                var_r28 = 1;
            }
            if ((temp_f30 - temp_f28) > 0.0f) {
                var_f23 = temp_f30 - temp_f28;
            } else {
                var_f23 = temp_f30 - (-1.0f * temp_f28);
            }
            if ((temp_f30 - temp_r31->pos.y) > 0.0f) {
                var_f22 = temp_f30 - temp_r31->pos.y;
            } else {
                var_f22 = temp_f30 - (-1.0f * temp_r31->pos.y);
            }
            if (var_f23 <= var_f22) {
                temp_r31->pos.y = temp_f28;
                var_r28 = 0;
            }
            if (var_r28 == 0) {
                temp_r31->time += 1;
            }
            break;
        case 2:
            temp_r3 = temp_r31->parManId;
            temp_r31->parManId = temp_r3 + 1;
            if (temp_r3 > 0x28) {
                temp_r31->time += 1;
            }
            break;
        case 3:
            temp_r0_2 = temp_r31->color.a - 0x32;
            temp_r31->color.a = temp_r0_2;
            if (temp_r0_2 < 0x32U) {
                temp_r31->color.a = 0;
                temp_r31->scale = 0.0f;
            }
            break;
        }
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}

void fn_1_3EF8(void) {
    lbl_1_bss_D0.unk34 = HuAudJinglePlay(0x83);
}

void fn_1_3F28(void) {
    lbl_1_bss_D0.unk30 = HuAudBGMPlay(0x3B);
}

void fn_1_3F58(s16 arg0, s16 arg1) {
    s16 spA;
    s16 sp8;
    s16 var_r31;

    sp8 = arg0;
    spA = arg1;
    if (sp8 != 0) {
        var_r31 = (s16) lbl_1_bss_D0.unk30;
    } else {
        var_r31 = (s16) lbl_1_bss_D0.unk34;
    }
    HuAudSStreamFadeOut((s32) var_r31, (s32) spA);
}


void fn_1_4020(s16 arg0) {
    lbl_1_bss_D0.unk54[arg0] = 1;
    lbl_1_bss_D0.unk3C[arg0] = HuAudFXPlay((s32) lbl_1_data_3A8[arg0]);
}

void fn_1_4098(s16 arg0, s16 arg1, s16 arg2) {
    s16 spA;
    s16 sp8;

    sp8 = arg1;
    spA = arg2;
    lbl_1_bss_D0.unk54[arg0] = 1;
    lbl_1_bss_D0.unk3C[arg0] = HuAudFXPlayVolPan((s32) lbl_1_data_3A8[arg0], arg1, arg2);
}

void fn_1_4120(s16 arg0, s16 arg1) {
    s16 sp8;

    sp8 = arg1;
    if (((s16) lbl_1_bss_D0.unk54[arg0] == 1) && (HuAudFXStatusGet(lbl_1_bss_D0.unk3C[arg0]) == 2)) {
        HuAudFXPanning(lbl_1_bss_D0.unk3C[arg0], sp8);
    }
}


void fn_1_425C(s16 arg0) {
    if (((s16) lbl_1_bss_D0.unk54[arg0] == 1) && ((HuAudFXStatusGet(lbl_1_bss_D0.unk3C[arg0]) == 2) || (HuAudFXStatusGet(lbl_1_bss_D0.unk3C[arg0]) == 3))) {
        HuAudFXStop(lbl_1_bss_D0.unk3C[arg0]);
    }
}

void fn_1_4308(void) {
    HuAudAllStop();
}

void fn_1_9EF8(M544Work *work, M544Model *models, u32 *dataNums) {
    u32 *sp10;
    M544Model *spC;
    M544Work *sp8;
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;

    sp8 = work;
    spC = models;
    sp10 = dataNums;
    lbl_1_bss_918 = sp8;
    memset((M544Game *) lbl_1_bss_918, 0, sizeof(M544Work));
    lbl_1_bss_918->unk58 = spC;
    lbl_1_bss_918->unk170 = sp10;
    var_r30 = 0;
    do {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            if ((var_r30 != (s16) GWPlayerCfg[var_r31].group) || (lbl_1_bss_918->unk4[var_r30].unk0 = var_r31, var_r30 += 1, ((var_r30 < 2) != 0))) {
                var_r31 += 1;
                goto loop_5;
            }
        }
    } while (var_r30 < 2);
    var_r31_2 = 0;
loop_11:
    if (var_r31_2 < 2) {
        lbl_1_bss_918->unk4[var_r31_2].unk2 = GWPlayerCfg[lbl_1_bss_918->unk4[var_r31_2].unk0].character;
        lbl_1_bss_918->unk4[var_r31_2].unk6 = GWPlayerCfg[lbl_1_bss_918->unk4[var_r31_2].unk0].pad_idx;
        if ((s16) GWPlayerCfg[lbl_1_bss_918->unk4[var_r31_2].unk0].iscom != 0) {
            lbl_1_bss_918->unk4[var_r31_2].unk4 = GWPlayerCfg[lbl_1_bss_918->unk4[var_r31_2].unk0].diff + 1;
        }
        var_r31_2 += 1;
        goto loop_11;
    }
}

void fn_1_A144(s16 arg0) {
    s16 sp8;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r31;

    sp8 = arg0;
    lbl_1_bss_918->unk174 = sp8;
    var_r31 = 0;
loop_4:
    if (var_r31 < 0xC) {
        temp_r0 = var_r31 + 0x14;
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_918->unk170[var_r31 + 0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_918->unk58[temp_r0].unk0 = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelCameraSet(temp_r3, 1U);
        Hu3DModelLayerSet(temp_r3, 0);
        Hu3DModelPosSetV(temp_r3, &lbl_1_data_418[var_r31]);
        Hu3DModelRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(temp_r3, 0.0f);
        Hu3DMotionTimeSet(temp_r3, 0.0f);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        lbl_1_bss_918->unk58[temp_r0].unk4.x = lbl_1_data_418[var_r31].x;
        lbl_1_bss_918->unk58[temp_r0].unk4.y = lbl_1_data_418[var_r31].y;
        lbl_1_bss_918->unk58[temp_r0].unk4.z = lbl_1_data_418[var_r31].z;
        lbl_1_bss_918->unk58[temp_r0].unk10.x = 0.0f;
        lbl_1_bss_918->unk58[temp_r0].unk10.y = 0.0f;
        lbl_1_bss_918->unk58[temp_r0].unk10.z = 0.0f;
        Hu3DModelAttrReset(temp_r3, 1U);
        if (var_r31 == 0) {
            Hu3DModelShadowMapSet(temp_r3);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_A3F0(s16 slot, M544Char *chr) {
    lbl_1_bss_918->unk5C[slot] = chr;
}

void fn_1_A410(s16 slot, s16 *mot) {
    lbl_1_bss_918->unk68[slot] = mot;
}

void fn_1_A430(void) {
    M544Anim *temp_r31;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        lbl_1_bss_918->unk58[var_r30 + 0x20].unk0 = CharModelCreate(lbl_1_bss_918->unk4[var_r30].unk2, 1);
        Hu3DModelPosSet(lbl_1_bss_918->unk58[var_r30 + 0x20].unk0, -150.0f + (300.0f * (f32) var_r30), 100.0f, 0.0f);
        CharModelFxFlagSet(lbl_1_bss_918->unk4[var_r30].unk2, 1);
        Hu3DModelLayerSet(lbl_1_bss_918->unk58[var_r30].unk0, 0);
        Hu3DModelShadowSet(lbl_1_bss_918->unk58[var_r30 + 0x20].unk0);
        CharModelStepFxSet(lbl_1_bss_918->unk4[var_r30].unk2, 1);
        CharModelFxFlagSet(lbl_1_bss_918->unk4[var_r30].unk2, 0);
        temp_r31 = &lbl_1_bss_918->unk74[var_r30];
        temp_r31->unk0 = 4;
        temp_r31->unk4 = 1.0f;
        temp_r31->unk18 = 0x40000001;
        temp_r31->unk20 = 0;
        temp_r31->unkC = 0.0f;
        var_r30 += 1;
        goto loop_2;
    }
    lbl_1_bss_918->unk58[0x22].unk0 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_bss_918->unk170[0x19], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_918->unk58[0x22].unk0, 1U);
    Hu3DModelCameraSet(lbl_1_bss_918->unk58[0x22].unk0, 1U);
    Hu3DModelLayerSet(lbl_1_bss_918->unk58[0x22].unk0, 2);
    Hu3DModelShadowSet(lbl_1_bss_918->unk58[0x22].unk0);
    Hu3DModelAmbSet(lbl_1_bss_918->unk58[0x22].unk0, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(lbl_1_bss_918->unk58[0x22].unk0, 1U);
    lbl_1_bss_918->unk74[2].unk0 = 0;
    lbl_1_bss_918->unk74[2].unk4 = 1.0f;
    lbl_1_bss_918->unk74[2].unk18 = 0x40000001;
    lbl_1_bss_918->unk74[2].unk20 = 0;
    lbl_1_bss_918->unk74[2].unkC = 0.0f;
    lbl_1_bss_918->unk58[0x20].unk4.x = -300.0f;
    lbl_1_bss_918->unk58[0x20].unk4.y = 100.0f;
    lbl_1_bss_918->unk58[0x20].unk4.z = -240.0f;
    lbl_1_bss_918->unk58[0x20].unk10.x = 0.0f;
    lbl_1_bss_918->unk58[0x20].unk10.y = 90.0f;
    lbl_1_bss_918->unk58[0x20].unk10.z = 0.0f;
    lbl_1_bss_918->unk58[0x21].unk4.x = 300.0f;
    lbl_1_bss_918->unk58[0x21].unk4.y = 100.0f;
    lbl_1_bss_918->unk58[0x21].unk4.z = -240.0f;
    lbl_1_bss_918->unk58[0x21].unk10.x = 0.0f;
    lbl_1_bss_918->unk58[0x21].unk10.y = -90.0f;
    lbl_1_bss_918->unk58[0x21].unk10.z = 0.0f;
    lbl_1_bss_918->unk58[0x22].unk4.x = -0.0f;
    lbl_1_bss_918->unk58[0x22].unk4.y = 100.0f;
    lbl_1_bss_918->unk58[0x22].unk4.z = -400.0f;
    lbl_1_bss_918->unk58[0x22].unk10.x = 0.0f;
    lbl_1_bss_918->unk58[0x22].unk10.y = 0.0f;
    lbl_1_bss_918->unk58[0x22].unk10.z = 0.0f;
}

void fn_1_A9A4(omObjData *obj) {
    s32 var_r31;
    s8 var_r29;
    s8 var_r30;

    var_r31 = 0;
loop_11:
    if (var_r31 < 2) {
        if ((s16) lbl_1_bss_918->unk4[var_r31].unk4 != 0) {
            memset((M544Game *) &lbl_1_bss_918->unk4[var_r31].unk8, 0, 0x14);
        } else {
            lbl_1_bss_918->unk4[var_r31].unk8 = (s32) HuPadBtn[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unkC = (s32) HuPadBtnDown[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk12 = HuPadBtnRep[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk10 = (s8) (u8) HuPadStkX[lbl_1_bss_918->unk4[var_r31].unk6];
            if ((s8) (u8) lbl_1_bss_918->unk4[var_r31].unk10 >= 0) {
                var_r30 = (s8) (u8) lbl_1_bss_918->unk4[var_r31].unk10;
            } else {
                var_r30 = -(s8) (u8) lbl_1_bss_918->unk4[var_r31].unk10;
            }
            if (var_r30 < 0xA) {
                var_r29 = 0;
            } else {
                var_r29 = (s8) (u8) lbl_1_bss_918->unk4[var_r31].unk10;
            }
            lbl_1_bss_918->unk4[var_r31].unk10 = var_r29;
            lbl_1_bss_918->unk4[var_r31].unk14 = (s8) (u8) HuPadStkY[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk15 = (s8) (u8) HuPadSubStkX[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk16 = (s8) (u8) HuPadSubStkY[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk17 = HuPadTrigL[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk18 = HuPadTrigR[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk19 = HuPadDStk[lbl_1_bss_918->unk4[var_r31].unk6];
            lbl_1_bss_918->unk4[var_r31].unk1A = HuPadDStkRep[lbl_1_bss_918->unk4[var_r31].unk6];
        }
        var_r31 += 1;
        goto loop_11;
    }
}

void fn_1_ADBC(void) {
    s16 var_r30;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        var_r30 = 0;
loop_3:
        if (var_r30 < 7) {
            lbl_1_bss_918->unk68[var_r31][var_r30] = Mp5CharMotionCreateData(lbl_1_bss_918->unk4[var_r31].unk2, lbl_1_bss_918->unk5C[var_r31]->unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 4) {
        lbl_1_bss_918->unk68[2][var_r31_2] = Hu3DJointMotion(lbl_1_bss_918->unk58[0x22].unk0, HuDataSelHeapReadNum((s32) lbl_1_bss_918->unk5C[2]->unk0[var_r31_2], MEMORY_DEFAULT_NUM, HEAP_DATA));
        var_r31_2 += 1;
        goto loop_8;
    }
    var_r31_3 = 0;
loop_11:
    if (var_r31_3 < 3) {
        lbl_1_bss_918->unk74[var_r31_3].unk2 = -1;
        lbl_1_bss_918->unk74[var_r31_3].unk8 = -1.0f;
        var_r31_3 += 1;
        goto loop_11;
    }
}

void fn_1_AF60(omObjData *obj) {
    M544Anim *temp_r31;
    s16 temp_r0;
    s16 temp_r0_4;
    s16 var_r29;
    u32 temp_r0_2;
    u32 temp_r0_3;

    var_r29 = 0;
loop_27:
    if (var_r29 < 3) {
        temp_r31 = &lbl_1_bss_918->unk74[var_r29];
        temp_r0 = var_r29 + 0x20;
        if ((s16) temp_r31->unk0 != (s16) temp_r31->unk2) {
            Hu3DMotionSet(lbl_1_bss_918->unk58[temp_r0].unk0, lbl_1_bss_918->unk68[var_r29][temp_r31->unk0]);
            temp_r31->unk2 = temp_r31->unk0;
            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_918->unk58[temp_r0].unk0);
        }
        if (temp_r31->unk4 != temp_r31->unk8) {
            Hu3DMotionSpeedSet(lbl_1_bss_918->unk58[temp_r0].unk0, temp_r31->unk4);
            temp_r31->unk8 = temp_r31->unk4;
        }
        if ((u32) temp_r31->unk18 != (u32) temp_r31->unk1C) {
            Hu3DModelAttrSet(lbl_1_bss_918->unk58[temp_r0].unk0, temp_r31->unk18);
            temp_r31->unk1C = temp_r31->unk18;
        }
        if ((u32) temp_r31->unk20 != 0) {
            Hu3DModelAttrReset(lbl_1_bss_918->unk58[temp_r0].unk0, temp_r31->unk20);
            temp_r0_2 = temp_r31->unk20;
            temp_r31->unk20 = ~(temp_r0_2 | temp_r0_2);
            temp_r0_3 = temp_r31->unk18 & temp_r31->unk20;
            temp_r31->unk18 = temp_r0_3;
            temp_r31->unk1C = temp_r0_3;
            temp_r31->unk20 = 0;
        }
        if (temp_r31->unkC != temp_r31->unk10) {
            Hu3DMotionTimeSet(lbl_1_bss_918->unk58[temp_r0].unk0, temp_r31->unkC);
        }
        temp_r0_4 = temp_r31->unk38;
        switch (temp_r0_4) {                        /* irregular */
        case 0:
            break;
        case 1:
            Hu3DMotionShiftSet(lbl_1_bss_918->unk58[temp_r0].unk0, lbl_1_bss_918->unk68[var_r29][temp_r31->unk3A], temp_r31->unk40, temp_r31->unk44, temp_r31->unk3C);
            temp_r31->unk4C = Hu3DMotionShiftMaxTimeGet(lbl_1_bss_918->unk58[temp_r0].unk0);
            temp_r31->unk38 = 2;
            break;
        case 2:
            temp_r31->unk48 = Hu3DMotionShiftTimeGet(lbl_1_bss_918->unk58[temp_r0].unk0);
            if (((u32) (temp_r31->unk3C & 0x40000001) == 0) && (temp_r31->unk48 >= (temp_r31->unk44 - 1.0f))) {
                temp_r31->unk38 = 3;
            }
            break;
        case 3:
            temp_r31->unk38 = 0;
            break;
        }
        temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_918->unk58[temp_r0].unk0);
        temp_r31->unk10 = temp_r31->unkC;
        temp_r31->unk24 = Hu3DMotionEndCheck(lbl_1_bss_918->unk58[temp_r0].unk0);
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

void fn_1_B318(omObjData *obj) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        lbl_1_data_4A8[var_r31]();
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_B36C(void) {
    lbl_1_bss_918->unk1CC = 0;
}

void fn_1_B384(void) {
    M544Model *temp_r3;
    s32 temp_r0;
    s32 temp_r3_2;

    temp_r3 = lbl_1_bss_918->unk58;
    if ((s32) lbl_1_bss_918->unk1C8 == 0) {
        temp_r0 = lbl_1_bss_918->unk1D4;
        switch (temp_r0) {                          /* irregular */
        case 0:
            lbl_1_bss_918->unk1CC = 0x2710;
            lbl_1_bss_918->unk1D4 = 1;
            lbl_1_bss_918->unk1EC = 0.4f;
            Hu3DMotionSpeedSet(temp_r3[0x17].unk0, lbl_1_bss_918->unk1EC);
            temp_r3[0x17].unk10.y = -60.0f;
            return;
        case 1:
            temp_r3_2 = lbl_1_bss_918->unk1CC;
            lbl_1_bss_918->unk1CC = temp_r3_2 - 1;
            if (temp_r3_2 < 0) {
                lbl_1_bss_918->unk1D4 += 1;
                lbl_1_bss_918->unk1CC = 0;
                lbl_1_bss_918->unk1E8 = temp_r3[0x17].unk10.y;
                lbl_1_bss_918->unk1D0 = 0x78;
                lbl_1_bss_918->unk1EC = (f32) ((rand8() % 10) + 0x1E);
                if (lbl_1_bss_918->unk1E8 > -45.0f) {
                    lbl_1_bss_918->unk1EC = -lbl_1_bss_918->unk1EC;
                    return;
                }
            }
            break;
        case 2:
            lbl_1_bss_918->unk1CC += 1;
            Hu3DMotionSpeedSet(temp_r3[0x17].unk0, (f32) (0.4 + (0.5 * sin((3.141592653589793 * (f64) ((lbl_1_bss_918->unk1CC * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_918->unk1CC == 0x28) {
                lbl_1_bss_918->unk1CC = 0;
                lbl_1_bss_918->unk1D4 += 1;
                return;
            }
            break;
        case 3:
            lbl_1_bss_918->unk1CC += 1;
            Hu3DMotionSpeedSet(temp_r3[0x17].unk0, (f32) (0.8 + (0.2 * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_918->unk1CC * 0xB4) / (s32) lbl_1_bss_918->unk1D0)) / 180.0))));
            temp_r3[0x17].unk10.y = (f32) ((f64) lbl_1_bss_918->unk1E8 + ((f64) lbl_1_bss_918->unk1EC * sin((3.141592653589793 * (f64) ((s32) (lbl_1_bss_918->unk1CC * 0x5A) / (s32) lbl_1_bss_918->unk1D0)) / 180.0)));
            if ((s32) lbl_1_bss_918->unk1CC == (s32) lbl_1_bss_918->unk1D0) {
                temp_r3[0x17].unk10.y = lbl_1_bss_918->unk1E8 + lbl_1_bss_918->unk1EC;
                lbl_1_bss_918->unk1D4 += 1;
                lbl_1_bss_918->unk1CC = 0;
                return;
            }
            break;
        case 4:
            lbl_1_bss_918->unk1CC += 1;
            Hu3DMotionSpeedSet(temp_r3[0x17].unk0, (f32) (0.8 - (0.4 * sin((3.141592653589793 * (f64) ((lbl_1_bss_918->unk1CC * 0x5A) / 40)) / 180.0))));
            if ((s32) lbl_1_bss_918->unk1CC == 0x28) {
                lbl_1_bss_918->unk1CC = (rand8() % 120) + 0xB4;
                lbl_1_bss_918->unk1D4 = 1;
            }
            break;
        }
    }
}

void fn_1_B990(void) {
    M544Model *temp_r3;
    M544Model *temp_r3_2;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_918->unk58;
    temp_r3_2 = lbl_1_bss_918->unk58;
    if ((s32) lbl_1_bss_918->unk1F8 == 0) {
        temp_r3[0x15].unk10.y = 30.0f;
        temp_r3_2[0x16].unk10.y = 30.0f;
        temp_r0 = lbl_1_bss_918->unk204;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if ((s32) lbl_1_bss_918->unk1D4 == 2) {
                lbl_1_bss_918->unk1FC = 0;
                lbl_1_bss_918->unk204 += 1;
                lbl_1_bss_918->unk218 = 20.0f;
                lbl_1_bss_918->unk21C = 5.0f;
                lbl_1_bss_918->unk220 = -5.0f;
                return;
            }
            break;
        case 1:
            lbl_1_bss_918->unk1FC += 1;
            temp_r3[0x15].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_918->unk218 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk1FC * lbl_1_bss_918->unk21C)) / 180.0)));
            temp_r3_2[0x16].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_918->unk218 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk1FC * lbl_1_bss_918->unk220)) / 180.0)));
            if ((s32) lbl_1_bss_918->unk1D4 == 4) {
                lbl_1_bss_918->unk204 += 1;
                lbl_1_bss_918->unk200 = 0;
                return;
            }
            break;
        case 2:
            lbl_1_bss_918->unk1FC += 1;
            lbl_1_bss_918->unk200 += 1;
            if ((s32) lbl_1_bss_918->unk200 > 0x28) {
                lbl_1_bss_918->unk200 = 0x28;
            }
            lbl_1_bss_918->unk218 = (f32) (20.0 - (20.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_918->unk200 * 0x5A) / 40)) / 180.0)));
            temp_r3[0x15].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_918->unk218 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk1FC * lbl_1_bss_918->unk21C)) / 180.0)));
            temp_r3_2[0x16].unk10.y = (f32) (30.0 + ((f64) lbl_1_bss_918->unk218 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk1FC * lbl_1_bss_918->unk220)) / 180.0)));
            if ((s32) lbl_1_bss_918->unk1D4 == 1) {
                lbl_1_bss_918->unk204 = 0;
            }
            break;
        }
    }
}

void fn_1_BEDC(void) {
    Mtx sp8;
    Mtx sp38;
    M544Model *temp_r30;
    M544Model *temp_r31;
    s32 temp_r3;

    temp_r31 = &lbl_1_bss_918->unk58[0x18];
    temp_r30 = &lbl_1_bss_918->unk58[0x19];
    if ((s32) lbl_1_bss_918->unk228 == 0) {
        MTXIdentity(sp38);
        MTXRotRad(sp8, 0x79, -0.7853982f);
        MTXConcat(sp38, sp8, sp38);
        temp_r31->unk10.y = 30.0f;
        temp_r3 = lbl_1_bss_918->unk234;
        switch (temp_r3) {                          /* irregular */
        case 0:
            temp_r30->unk10.y = -45.0f;
            if ((s32) lbl_1_bss_918->unk1D4 == 2) {
                lbl_1_bss_918->unk248 = 10.0f;
                lbl_1_bss_918->unk24C = 5.0f;
                lbl_1_bss_918->unk22C = 0;
                lbl_1_bss_918->unk234 += 1;
            }
            break;
        case 1:
            lbl_1_bss_918->unk22C += 1;
            lbl_1_bss_918->unk24C = (f32) (5.0 + (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_918->unk22C * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_918->unk1D4 == 3) {
                lbl_1_bss_918->unk24C = 10.0f;
                lbl_1_bss_918->unk234 += 1;
            }
            break;
        case 2:
            lbl_1_bss_918->unk22C += 1;
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
            if ((s32) lbl_1_bss_918->unk1D4 == 4) {
                lbl_1_bss_918->unk234 += 1;
                lbl_1_bss_918->unk230 = 0;
            }
            break;
        case 3:
            lbl_1_bss_918->unk230 += 1;
            lbl_1_bss_918->unk22C += 1;
            if ((s32) lbl_1_bss_918->unk230 > 0x28) {
                lbl_1_bss_918->unk230 = 0x28;
            }
            lbl_1_bss_918->unk248 = (f32) (10.0 - (5.0 * sin((3.141592653589793 * (f64) ((lbl_1_bss_918->unk230 * 0x5A) / 40)) / 180.0)));
            temp_r31->unk10.x = (f32) ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0));
            MTXRotRad(sp8, 0x7A, (f32) (0.01745329238474369 * ((f64) lbl_1_bss_918->unk248 * sin((3.141592653589793 * (f64) ((f32) lbl_1_bss_918->unk22C * lbl_1_bss_918->unk24C)) / 180.0))));
            MTXConcat(sp38, sp8, sp38);
            Hu3DMtxRotGet(sp38, &temp_r30->unk10);
loop_17:
            if (temp_r31->unk10.x >= 360.0f) {
                temp_r31->unk10.x -= 360.0f;
                goto loop_17;
            }
            if (((s32) lbl_1_bss_918->unk1D4 == 1) && ((temp_r31->unk10.x >= 359.0f) || (temp_r31->unk10.x <= 1.0f))) {
                lbl_1_bss_918->unk248 = 0.0f;
                temp_r31->unk10.x = 0.0f;
                temp_r30->unk10.x = 0.0f;
                temp_r30->unk10.y = -45.0f;
                temp_r30->unk10.z = 0.0f;
                lbl_1_bss_918->unk234 = 0;
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

void fn_1_C7C0(void) {
    M544Model *temp_r30;
    M544Model *temp_r31;
    s32 temp_r4;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u8 temp_r3;
    u8 temp_r3_3;

    temp_r31 = &lbl_1_bss_918->unk58[0x1A];
    temp_r30 = &lbl_1_bss_918->unk58[0x1C];
    temp_r4 = lbl_1_bss_918->unk264;
    if ((u32) temp_r4 <= 7U) {
        switch (temp_r4) {
        case 0:
            if ((s32) lbl_1_bss_918->unk1D4 == 2) {
                lbl_1_bss_918->unk25C = 0;
                if (lbl_1_bss_918->unk278 == 0.0f) {
                    lbl_1_bss_918->unk264 += 1;
                    lbl_1_bss_918->unk25C = 0;
                    lbl_1_bss_918->unk278 = 15.0f;
                    temp_r3 = rand8();
                    temp_r4_2 = temp_r3 >> 0x1FU;
                    temp_r3_2 = (temp_r3 << 0x1C) - temp_r4_2;
                    lbl_1_bss_918->unk280 = (f32) ((((temp_r3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                } else {
                    lbl_1_bss_918->unk264 = 4;
                    lbl_1_bss_918->unk278 = 10.0f;
                    temp_r3_3 = rand8();
                    temp_r4_3 = temp_r3_3 >> 0x1FU;
                    temp_r3_4 = (temp_r3_3 << 0x1C) - temp_r4_3;
                    lbl_1_bss_918->unk280 = (f32) ((((temp_r3_3 % 16)) * 0x19) - 0x28A);
                    temp_r31->unk10.z = 0.0f;
                    temp_r31->unk4.x = -1000.0f;
                }
                lbl_1_bss_918->unk27C = (250.0f * lbl_1_bss_918->unk278) / 360.0f;
            }
            break;
        case 1:
            temp_r31->unk10.z -= lbl_1_bss_918->unk278;
            temp_r31->unk4.x += lbl_1_bss_918->unk27C;
            if (temp_r31->unk4.x >= lbl_1_bss_918->unk280) {
                lbl_1_bss_918->unk264 += 1;
            }
            break;
        case 2:
            lbl_1_bss_918->unk25C += 1;
            lbl_1_bss_918->unk278 = (f32) (7.5 + (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_918->unk25C) / 180.0)));
            lbl_1_bss_918->unk27C = (250.0f * lbl_1_bss_918->unk278) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_918->unk278;
            temp_r31->unk4.x += lbl_1_bss_918->unk27C;
            if ((s32) lbl_1_bss_918->unk25C >= 0x5A) {
                lbl_1_bss_918->unk264 += 1;
            }
            break;
        case 3:
            lbl_1_bss_918->unk25C += 1;
            if ((s32) lbl_1_bss_918->unk25C >= 0xB4) {
                lbl_1_bss_918->unk25C = 0xB4;
            }
            lbl_1_bss_918->unk278 = (f32) (7.5 - (7.5 * cos((3.141592653589793 * (f64) lbl_1_bss_918->unk25C) / 180.0)));
            lbl_1_bss_918->unk27C = (250.0f * lbl_1_bss_918->unk278) / 360.0f;
            if (temp_r31->unk4.x < 1000.0f) {
                temp_r31->unk10.z -= lbl_1_bss_918->unk278;
                temp_r31->unk4.x += lbl_1_bss_918->unk27C;
            } else if ((s32) lbl_1_bss_918->unk1D4 == 1) {
                lbl_1_bss_918->unk264 = 0;
            }
            break;
        case 4:
            lbl_1_bss_918->unk25C += 1;
            if ((s32) lbl_1_bss_918->unk25C >= 0x14) {
                temp_r31->unk10.z -= lbl_1_bss_918->unk278;
                temp_r31->unk4.x += lbl_1_bss_918->unk27C;
                if (temp_r31->unk4.x >= lbl_1_bss_918->unk280) {
                    lbl_1_bss_918->unk264 += 1;
                    lbl_1_bss_918->unk25C = 0;
                }
            }
            break;
        case 5:
            lbl_1_bss_918->unk25C += 1;
            lbl_1_bss_918->unk278 = (f32) (10.0 * cos((3.141592653589793 * (f64) lbl_1_bss_918->unk25C) / 180.0));
            lbl_1_bss_918->unk27C = (250.0f * lbl_1_bss_918->unk278) / 360.0f;
            temp_r31->unk10.z -= lbl_1_bss_918->unk278;
            temp_r31->unk4.x += lbl_1_bss_918->unk27C;
            if ((s32) lbl_1_bss_918->unk25C == 0x5A) {
                lbl_1_bss_918->unk264 += 1;
                lbl_1_bss_918->unk25C = 0;
            }
            break;
        case 6:
            if ((s32) lbl_1_bss_918->unk1D4 == 2) {
                lbl_1_bss_918->unk264 += 1;
            }
            break;
        case 7:
            lbl_1_bss_918->unk25C += 1;
            if ((s32) lbl_1_bss_918->unk25C >= 0x96) {
                lbl_1_bss_918->unk25C = 0x96;
            }
            if ((s32) lbl_1_bss_918->unk25C >= 0x3C) {
                lbl_1_bss_918->unk278 = (f32) (10.0 * sin((3.141592653589793 * (f64) (lbl_1_bss_918->unk25C - 0x3C)) / 180.0));
                lbl_1_bss_918->unk27C = (250.0f * lbl_1_bss_918->unk278) / 360.0f;
                if (temp_r31->unk4.x < 1000.0f) {
                    if ((s32) lbl_1_bss_918->unk25C >= 0x46) {
                        temp_r31->unk10.z -= lbl_1_bss_918->unk278;
                    }
                    temp_r31->unk4.x += lbl_1_bss_918->unk27C;
                } else if ((s32) lbl_1_bss_918->unk1D4 == 1) {
                    lbl_1_bss_918->unk264 = 0;
                    lbl_1_bss_918->unk278 = 0.0f;
                }
            }
            break;
        }
    }
    temp_r30->unk4.x = temp_r31->unk4.x;
    temp_r30->unk4.y = temp_r31->unk4.y - 40.0f;
    temp_r30->unk4.z = temp_r31->unk4.z;
}

void fn_1_D1CC(void) {
    M544Model *temp_r3;
    s32 temp_r0;

    temp_r3 = lbl_1_bss_918->unk58;
    temp_r0 = lbl_1_bss_918->unk294;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if ((s32) lbl_1_bss_918->unk1D4 == 2) {
            lbl_1_bss_918->unk294 += 1;
            lbl_1_bss_918->unk28C = 0;
            Hu3DMotionSpeedSet(temp_r3[0x1B].unk0, 0.5f);
            Hu3DMotionTimeSet(temp_r3[0x1B].unk0, 0.0f);
            switch ((s16) lbl_1_bss_D0.unk38) {     /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                fn_1_4098(0, 0x7F, 0x24);
                return;
            case 1:                                 /* switch 2 */
                fn_1_425C(0);
                lbl_1_bss_D0.unk38 += 1;
                return;
            }
        } else {
            return;
        }
        break;
    case 1:                                         /* switch 1 */
        lbl_1_bss_918->unk28C += 1;
        if ((s16) lbl_1_bss_D0.unk38 != 1) {
            fn_1_4120(0, (s16) (((lbl_1_bss_918->unk28C << 6) / 200) + 0x20));
        }
        temp_r3[0x1B].unk4.x = (f32) (((lbl_1_bss_918->unk28C * 0xFA0) / 200) - 0x7D0);
        if ((s32) lbl_1_bss_918->unk28C == 0xC8) {
            lbl_1_bss_918->unk294 += 1;
            return;
        }
        break;
    case 2:                                         /* switch 1 */
        if ((s32) lbl_1_bss_918->unk1D4 == 1) {
            lbl_1_bss_918->unk294 = 0;
        }
        break;
    }
}
