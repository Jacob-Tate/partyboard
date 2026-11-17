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

extern M542Work lbl_1_bss_1954;
extern M542Work *lbl_1_bss_1B38;
extern M542Model lbl_1_bss_1588[0x22];
extern M542Com lbl_1_bss_14[2];
extern s16 lbl_1_bss_54[2][9];
extern OMCAMERAVIEW lbl_1_bss_78[4];
extern M542Spark lbl_1_bss_E8[4][30];
extern s16 lbl_1_bss_1940[2][5];
extern M542Fx lbl_1_bss_1AA8[4];
extern s16 lbl_1_bss_1B28;
extern s16 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_8;
extern s32 lbl_1_bss_C;
extern s8 lbl_1_bss_10;
extern s32 lbl_1_data_0[0x20];
extern M542Char lbl_1_data_80[0xD];
extern MGSEQ_PARAM lbl_1_data_254;
extern void (*lbl_1_data_27C[4])(void);
extern void (*lbl_1_data_28C[3])(void);
extern void (*lbl_1_data_29C[3])(void);
extern s32 lbl_1_data_298;
extern M542Pair lbl_1_data_2A8[0xD];
extern s32 lbl_1_data_330;
extern s32 lbl_1_data_334[2];
extern M542Pair lbl_1_data_33C[0xE];
extern Vec lbl_1_data_3B0[6];
extern s32 lbl_1_rodata_11C[4];

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
