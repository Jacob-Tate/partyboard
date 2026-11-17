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

extern M547Work lbl_1_bss_488;
extern M547Work *lbl_1_bss_6E8;
extern M547Model lbl_1_bss_E8[30];
extern s16 lbl_1_bss_5C[2][7];
extern M547Fall lbl_1_bss_440[2];
extern Vec lbl_1_bss_458;
extern Vec lbl_1_bss_464;
extern s16 lbl_1_bss_470[8];
extern s16 lbl_1_bss_480[2];
extern s32 lbl_1_bss_24[4];
extern s32 lbl_1_bss_430[4];
extern f32 lbl_1_bss_6AC[4];
extern s16 lbl_1_bss_6BC[4];
extern s32 lbl_1_bss_6C4[4];
extern s32 lbl_1_bss_6D4[5];
extern s32 lbl_1_data_0[13];
extern M547Char lbl_1_data_64[13];
extern s32 lbl_1_data_34[11];
extern s32 lbl_1_data_2A4[2];
extern void (*lbl_1_data_1F8[2])(void);
extern void (*lbl_1_data_200[5])(void);
extern void (*lbl_1_data_214[3])(void);
extern void (*lbl_1_data_3EC[5])(void);
extern f32 lbl_1_rodata_90[13];
extern s32 lbl_1_rodata_130[4];

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
