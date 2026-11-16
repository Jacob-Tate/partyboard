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

extern M548Work lbl_1_bss_3F0;
extern M548Work *lbl_1_bss_5F8;
extern M548Model lbl_1_bss_154[20];
extern M548Game lbl_1_bss_3D0;
extern M548Count lbl_1_bss_0[2];
extern M548Count lbl_1_bss_5DC;
extern M548Rect lbl_1_bss_384[2];
extern M548Fx lbl_1_bss_3B8;
extern OMCAMERAVIEW lbl_1_bss_58[8];
extern s16 lbl_1_bss_138[2][7];
extern u32 lbl_1_bss_20[2];
extern f32 lbl_1_bss_28;
extern Vec lbl_1_bss_38;
extern Vec lbl_1_bss_44;
extern s16 lbl_1_bss_50;
extern MGTIMER *lbl_1_bss_54;
extern s16 lbl_1_bss_3B4;
extern s16 lbl_1_bss_5D0;
extern s16 lbl_1_bss_5D2[3];
extern f32 lbl_1_bss_5D8;
extern u8 lbl_1_bss_5EC;
extern s32 lbl_1_bss_5F0;
extern s32 lbl_1_data_398;
extern MGSEQ_PARAM lbl_1_data_2F0;
extern f32 lbl_1_data_0[13][6];
extern s32 lbl_1_data_138[12];
extern s32 lbl_1_data_168[7];
extern M548Char lbl_1_data_184[13];
extern M548Pair lbl_1_data_288[13];
extern void (*lbl_1_data_318[8])(void);
extern M548Pair lbl_1_data_39C[17];
extern f32 lbl_1_data_424[13];
extern Vec lbl_1_data_458[3];
extern Vec lbl_1_data_47C[3];
extern f32 lbl_1_data_4A0[3];
extern f32 lbl_1_data_4C8[4];
extern f32 lbl_1_data_4D8[4];
extern f32 lbl_1_data_4E8[4];
extern f32 lbl_1_data_4F8[4];
extern Vec lbl_1_data_530[12];
extern void (*lbl_1_data_5C0[5])(void);
extern s32 lbl_1_rodata_C0[4];
extern s32 lbl_1_rodata_D0[2];
extern Vec lbl_1_rodata_118;
extern f32 lbl_1_rodata_15C[7];
extern f32 lbl_1_rodata_178[7];
extern Vec lbl_1_rodata_1C8;
extern s32 lbl_1_rodata_1DC[3];
extern s32 lbl_1_rodata_1E8[4];
extern s32 lbl_1_rodata_200[2];
extern s32 lbl_1_rodata_208[2];

void fn_1_6104(M548Work *work, M548Model *models, s32 *dataNums);
void fn_1_6350(s16 arg);
void fn_1_65E8(M548Char *chr0, M548Char *chr1);
void fn_1_660C(s16 *mot0, s16 *mot1);
void fn_1_4FC4(Vec *pos);
void fn_1_5014(s32 show);
s32 fn_1_4658(s16 arg0);
s32 fn_1_196C(void);
