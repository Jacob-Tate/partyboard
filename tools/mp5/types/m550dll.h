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

extern M550Work lbl_1_bss_14AC;
extern M550Work *lbl_1_bss_1FC0;
extern M550Model lbl_1_bss_A8[0xB7];
extern M550Ai lbl_1_bss_4[2];
extern MGTIMER *lbl_1_bss_0;
extern s16 lbl_1_bss_24[2][5];
extern OMCAMERAVIEW lbl_1_bss_38[4];
extern s32 lbl_1_bss_1EC0[2];
extern s16 lbl_1_bss_1EC8;
extern s32 lbl_1_bss_1ECC[2][0x1E];
extern s32 lbl_1_data_0[2];
extern s32 lbl_1_data_8[0x3C];
extern M550Char lbl_1_data_F8[13];
extern MGSEQ_PARAM lbl_1_data_1FC;
extern void (*lbl_1_data_224[3])(void);
extern void (*lbl_1_data_230[3])(void);
extern void (*lbl_1_data_23C[5])(void);
extern Vec lbl_1_data_250[0x1E];
extern s32 lbl_1_data_3B8;
extern Vec lbl_1_data_3D8[6];
extern s16 lbl_1_data_420[2];
extern void (*lbl_1_data_424[7])(void);
extern s32 lbl_1_rodata_C8[13];
extern s32 lbl_1_rodata_158[3];
extern s32 lbl_1_rodata_164[3];
extern s32 lbl_1_rodata_1A0[5];
extern f32 lbl_1_rodata_1B4[5];
extern f32 lbl_1_rodata_1C8[5];
extern f32 lbl_1_rodata_1DC[5];
extern s32 lbl_1_rodata_220[4];
extern s32 lbl_1_rodata_274[6];
extern f32 lbl_1_rodata_28C[5];
extern f32 lbl_1_rodata_2A0[5];
extern f32 lbl_1_rodata_2B4[5];
extern f32 lbl_1_rodata_2C8[6];
extern Vec lbl_1_rodata_370[4];
extern f32 lbl_1_rodata_3A0[4];
extern s32 lbl_1_rodata_3B0[4];
extern s32 lbl_1_rodata_3C0[4];

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
