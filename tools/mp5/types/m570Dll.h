// m2c context for m570Dll (tools/mp5/decomp.py m570Dll --types tools/mp5/types/m570Dll.h)
// Written from the draft: Fight Cards (1 vs 3, pick a card with A/B/X; a team player who matches the solo
// player's card is out). Runs on MP5's MgSeq sequencer; camera code is the same library copy as m524's.
// objdata fn_1_457C fn_1_45E4: M570Player
// objdata fn_1_58EC: M570Fan
// objdata fn_1_2B18: M570CamMove
// objexpr lbl_1_bss_C: M570CamMove
// objexpr lbl_1_bss_4: M570CamMove
// var fn_1_1964 temp_r3: M570Camera
// var MgCameraMoveEntry temp_r31: M570CamMove
// var fn_1_4210 temp_r31: M570Player
// var fn_1_45E4 temp_r27: OMOBJ
// var fn_1_45E4 temp_r28: OMOBJ
// var fn_1_45E4 temp_r29: OMOBJ
// var fn_1_45E4 temp_r30: OMOBJ
// var fn_1_4440 temp_r29: OMOBJ
// var fn_1_4DC4 temp_r31: M570Player
// var fn_1_4DC4 temp_r30: OMOBJ
// var fn_1_4EF8 temp_r31: M570Player
// var fn_1_4EF8 temp_r30: OMOBJ
// var fn_1_5048 temp_r31: M570Player
// var fn_1_5048 temp_r29: OMOBJ
// var fn_1_51A8 temp_r31: M570Player
// var fn_1_51A8 temp_r30: OMOBJ
// var fn_1_5354 temp_r31: M570Player
// var fn_1_5354 temp_r30: M570Player
// var fn_1_5354 temp_r28: OMOBJ
// var fn_1_5354 temp_r27: OMOBJ
// var fn_1_5A78 temp_r26: M570Fan

typedef struct M570Light { // lbl_1_data_94: Hu3DGLightCreateV arguments
    Vec unk0; // pos
    Vec unkC; // dir
    GXColor unk18;
} M570Light;

typedef struct M570Camera { // camera parameters, 0x48
    s32 unk0; // camera bit
    s32 unk4; // 1: position from angles
    f32 unk8, unkC, unk10; // fov, near, far
    Vec unk14; // pos
    Vec unk20; // up
    Vec unk2C; // target
    f32 unk38, unk3C, unk40; // angles
    f32 unk44; // distance
} M570Camera;

typedef struct M570CamMove { // camera move object data, 0xA0
    M570Camera *unk0; // camera being moved
    M570Camera unk4; // from
    M570Camera unk4C; // to
    f32 unk94; // frames
    f32 unk98; // time
    s32 unk9C; // flags (2: moving)
} M570CamMove;

typedef struct M570Player { // OMOBJ::data, 0x54
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // pad
    s16 unk6; // group (0: the solo player)
    s16 unk8; // difficulty
    s16 unkA;
    s32 unkC; // com
    Vec unk10; // pos
    Vec unk1C; // rot
    u32 unk28; // mode
    OMOBJ *unk2C; // its object
    s32 unk30;
    s16 unk34; // seat (0: solo, 1-3: team)
    s16 unk36; // current motion
    Vec unk38; // walk target
    s32 unk44; // mode timer
    s32 unk48; // out
    s16 unk4C; // card (0-2)
    s16 unk4E;
    s32 unk50;
} M570Player;

typedef struct M570Fan { // audience member, OMOBJ::data, 0x14
    s32 unk0; // index
    OMOBJ *unk4; // its object
    s32 unk8; // cheer delay
    s32 unkC; // cheer count
    s32 unk10; // mode
} M570Fan;

typedef struct M570MotParam { // per motion: shift time, attribute, MP5 reset-lock flag
    f32 unk0;
    u32 unk4;
    s32 unk8;
} M570MotParam;

extern MGSEQ_PARAM lbl_1_data_6C;
extern M570Light lbl_1_data_94;
extern M570Camera lbl_1_data_E8;
extern M570Camera lbl_1_data_130;
extern M570Camera lbl_1_data_178;
extern M570Camera lbl_1_data_1C0;
extern M570Camera lbl_1_data_208;
extern M570Camera lbl_1_data_250;
extern M570Camera lbl_1_data_298;
extern M570Camera lbl_1_bss_54;
extern OMOBJ *lbl_1_bss_4;
extern OMOBJ *lbl_1_bss_C[8];
extern MGTIMER *lbl_1_bss_9C;
extern M570MotParam lbl_1_data_37C[10];
extern Vec lbl_1_data_3F4[4];
extern Vec lbl_1_data_424[4];
extern Vec lbl_1_data_454[4];
extern Vec lbl_1_data_484[4];
extern Vec lbl_1_data_4C8[40];
extern M570Fan *lbl_1_bss_110[40];
extern M570Player *lbl_1_bss_1B4[3];
extern M570Player *lbl_1_bss_1C0;
extern M570Player *lbl_1_bss_1C4[4];
extern u32 lbl_1_rodata_160[4];

void fn_1_120(s16 mode, s16 frameNo);
void fn_1_520(s16 mode, s16 frameNo);
void fn_1_A78(s16 mode, s16 frameNo);
void fn_1_A7C(s16 mode, s16 frameNo);
void fn_1_ABC(s16 mode, s16 frameNo);
void fn_1_D88(s16 mode, s16 frameNo);
void fn_1_DEC(s16 mode, s16 frameNo);
void fn_1_F54(s16 mode, s16 frameNo);
void fn_1_1034(s16 mode, s16 frameNo);
s16 fn_1_16D4(Vec *arg0);
s16 fn_1_17DC(Vec *arg0);
void fn_1_1864(Vec *arg0, s16 arg1);
M570Camera *fn_1_1964(M570Camera *arg0);
void fn_1_1A50(M570Camera *arg0);
void fn_1_2050(M570Camera *arg0);
OMOBJ *MgCameraMoveEntry(M570Camera *arg0, M570Camera *arg1, f32 farg0);
void fn_1_3A74(M570Player *arg0, s16 arg1);
void fn_1_4440(M570Player *arg0, s16 arg1);
void fn_1_4AC8(M570Player *arg0);
void fn_1_4BB0(M570Player *arg0);
void fn_1_4CC8(M570Player *arg0);
