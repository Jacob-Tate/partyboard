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

extern M544Work lbl_1_bss_530;
extern M544Work *lbl_1_bss_914;
extern M544Work *lbl_1_bss_918;
extern M544Model lbl_1_bss_15C[0x23];
extern M544Hand lbl_1_bss_C;
extern M544Pl lbl_1_bss_80[2];
extern M544Game lbl_1_bss_D0;
extern s16 lbl_1_bss_130[3][7];
extern M544Fx lbl_1_bss_828[4];
extern M544Seq lbl_1_bss_8D8[10];
extern M544Cam *lbl_1_bss_8;
extern M544Light *lbl_1_bss_4;
extern M544Shadow *lbl_1_bss_0;
extern HUPROCESS *lbl_1_bss_818;
extern void *lbl_1_bss_820;
extern s16 lbl_1_bss_824;
extern s16 lbl_1_bss_826;
extern MGSEQ_PARAM lbl_1_data_0;
extern M544Char lbl_1_data_28[0xD];
extern u32 lbl_1_data_194[4];
extern u32 lbl_1_data_1A4[0x1B];
extern M544CamInit lbl_1_data_210[4];
extern s16 lbl_1_data_2E0[0x10];
extern M544Part lbl_1_data_370;
extern s16 lbl_1_data_3A8[8];
extern M544Cpu lbl_1_data_3EC[4];
extern Vec lbl_1_data_418[0xC];
extern void (*lbl_1_data_4A8[5])(void);
extern s16 lbl_1_rodata_350[10];
extern f32 lbl_1_rodata_A4[13];
extern f32 lbl_1_rodata_D8[13][6];
extern f32 lbl_1_rodata_210[13][6];
extern char lbl_1_data_3BB[];

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
