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

extern M545Work lbl_1_bss_67C;
extern M545Work *lbl_1_bss_9B8;
extern M545Model lbl_1_bss_254[0x26];
extern M545Pl lbl_1_bss_C[2];
extern M545Snd lbl_1_bss_19C;
extern M545Seq lbl_1_bss_980[7];
extern s16 lbl_1_bss_99C[2][6];
extern Vec lbl_1_bss_8D8[14];
extern M545Cam *lbl_1_bss_8;
extern M545Light *lbl_1_bss_4;
extern M545Shadow *lbl_1_bss_0;
extern s16 lbl_1_bss_240[2][5];
extern HUPROCESS *lbl_1_bss_8CC;
extern void *lbl_1_bss_8D0;
extern s16 lbl_1_bss_8D4;
extern MGSEQ_PARAM lbl_1_data_0;
extern M545Char lbl_1_data_28[0xD];
extern u32 lbl_1_data_12C[0x13];
extern M545CamInit lbl_1_data_178[4];
extern s16 lbl_1_data_248[0x10];
extern M545Part lbl_1_data_268;
extern s16 lbl_1_data_2A0[0xC];
extern s16 lbl_1_data_2D8[4][7];
extern Vec lbl_1_data_310[0xC];
extern void (*lbl_1_data_3A0[5])(void);

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
