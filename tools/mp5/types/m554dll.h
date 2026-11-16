// m2c context for m554dll (tools/mp5/decomp.py m554dll --types tools/mp5/types/m554dll.h)
// Written from the draft: Wind Wavers (1 vs 1). Runs on MP5's MgSeq sequencer; the camera uses
// MP5's omCameraView* helpers (mp5compat.h). lbl_1_bss_1360 points at the work struct lbl_1_bss_B1C.

typedef struct M554Model { // model table entry, 0x1C (0x5C of them in lbl_1_bss_10C)
    s16 unk0; // model
    Vec unk4; // pos
    Vec unk10; // rot
} M554Model;

typedef struct M554Player { // 0x1C
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
} M554Player;

typedef struct M554Rec { // per player, 0x54
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    s32 unk24;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    u32 unk30;
    u32 unk34;
    s16 unk38;
    s16 unk3A;
    u32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    char pad50[4];
} M554Rec;

typedef struct M554Char { // per MP5 character, 0x14
    u32 unk0[5]; // MP5 motion data numbers: 2 in the character's archive, 3 in its mot archive
} M554Char;

typedef struct M554Prop { // background animation state, 0x3C
    s32 unk0; // mode
    s32 unk4[3]; // counters
    s32 unk10; // stop flag
    char pad14[0x18];
    f32 unk2C; // angle
    f32 unk30; // distance
    f32 unk34; // angle speed
    f32 unk38; // height
} M554Prop;

typedef struct M554Pow { // 0x8
    s32 unk0;
    s32 unk4;
} M554Pow;

typedef struct M554Sail { // 0x10
    f32 unk0; // distance
    f32 unk4; // angle
    f32 unk8;
    f32 unkC;
} M554Sail;

typedef struct M554Work { // lbl_1_bss_B1C, 0x814
    HUPROCESS *unk0; // object manager
    M554Player unk4[2];
    M554Model *unk3C; // model table (lbl_1_bss_10C)
    M554Char *unk40[2]; // character data per player
    s16 *unk48[2]; // motions per player (lbl_1_bss_84)
    M554Rec unk50[2];
    s32 *unkF8; // data numbers (lbl_1_data_4)
    s32 unkFC;
    s32 unk100; // mode step
    s32 unk104;
    s32 unk108;
    s32 unk10C; // winner (2: draw)
    s32 unk110[4];
    s32 unk120;
    M554Pow unk124[2];
    M554Sail unk134[2];
    s32 unk154[2][60]; // per player, per frame of the last 60: an alternating L/R press
    char pad334[0x30];
    M554Prop unk364[10]; // 0-3 fn_1_78F4, 4-7 fn_1_7D74, 8-9 fn_1_7FCC
    char pad5BC[0x258];
} M554Work;

extern M554Work lbl_1_bss_B1C;
extern M554Work *lbl_1_bss_1360;
extern M554Model lbl_1_bss_10C[0x5C];
extern OMCAMERAVIEW lbl_1_bss_98[4];
extern MGSEQ_PARAM lbl_1_data_158;
extern M554Char lbl_1_data_54[13];
extern Vec lbl_1_data_258[6];
extern s32 lbl_1_data_4[20];
extern Vec lbl_1_bss_8;
extern s32 lbl_1_data_1A8[2];
extern s16 lbl_1_bss_84[2][5];
extern f32 lbl_1_data_1B0[2];
extern f32 lbl_1_data_1B8[2];
extern s32 lbl_1_data_23C[2];
extern s16 lbl_1_data_246[3];
extern s32 lbl_1_rodata_178[8][6];
extern f32 lbl_1_rodata_238[6];
extern s32 lbl_1_rodata_264[7];
extern s32 lbl_1_rodata_2F0[6];
extern s32 lbl_1_rodata_308[12];
extern f32 lbl_1_rodata_390[5];
extern f32 lbl_1_rodata_3A4[5];
extern s32 lbl_1_rodata_3E4[5];
extern s32 lbl_1_rodata_404[2];
