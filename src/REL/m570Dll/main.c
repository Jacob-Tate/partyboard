// MP5 m570 (Fight Cards), generated from its m2c draft by tools/mp5/ports/m570Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
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
void ObjectSetup(void);
void fn_1_120(s16 mode, s16 frameNo);
void fn_1_520(s16 mode, s16 frameNo);
void fn_1_A78(s16 mode, s16 frameNo);
void fn_1_A7C(s16 mode, s16 frameNo);
void fn_1_ABC(s16 mode, s16 frameNo);
void fn_1_D88(s16 mode, s16 frameNo);
void fn_1_DEC(s16 mode, s16 frameNo);
void fn_1_F54(s16 mode, s16 frameNo);
void fn_1_1034(s16 mode, s16 frameNo);
void fn_1_1038(void);
void fn_1_1098(void);
void fn_1_1174(void);
void fn_1_12F0(void);
void fn_1_1354(omObjData *arg0);
void fn_1_1464(void);
void fn_1_14A8(omObjData *arg0);
void fn_1_15FC(s32 arg0);
void fn_1_1674(omObjData *arg0);
s16 fn_1_16D4(Vec *arg0);
s16 fn_1_17DC(Vec *arg0);
void fn_1_1864(Vec *arg0, s16 arg1);
M570Camera *fn_1_1964(M570Camera *arg0);
void fn_1_1A50(M570Camera *arg0);
void fn_1_2050(M570Camera *arg0);
void fn_1_2B18(omObjData *arg0);
omObjData *MgCameraMoveEntry(M570Camera *arg0, M570Camera *arg1, f32 farg0);
void fn_1_3A74(M570Player *arg0, s16 arg1);
s32 fn_1_3B40(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0);
f32 fn_1_3C64(f32 farg0, f32 farg1, f32 farg2);
void fn_1_4210(void);
void fn_1_4440(M570Player *arg0, s16 arg1);
void fn_1_457C(omObjData *arg0);
void fn_1_45E4(omObjData *obj);
void fn_1_4AC8(M570Player *arg0);
void fn_1_4BB0(M570Player *arg0);
void fn_1_4CC8(M570Player *arg0);
void fn_1_4D2C(void);
void fn_1_4DC4(void);
void fn_1_4EF8(void);
void fn_1_5048(void);
void fn_1_51A8(void);
void fn_1_5354(void);
s32 fn_1_5538(void);
void fn_1_558C(omObjData *arg0);
void fn_1_56A0(void);
void fn_1_5820(s16 arg0);
void fn_1_58EC(omObjData *arg0);
void fn_1_5A78(void);
void fn_1_5E38(void);
void fn_1_5F24(s32 arg0);

MGSEQ_PARAM lbl_1_data_6C = {
    0,
    0,
    fn_1_120,
    fn_1_520,
    fn_1_A78,
    fn_1_ABC,
    fn_1_D88,
    fn_1_DEC,
    fn_1_F54,
    NULL,
    fn_1_1034,
};
M570Light lbl_1_data_94 = {
    { 0.0f, 300.0f, 0.001f },
    { 0.0f, -300.0f, 0.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
};
static Vec lbl_1_data_B0 = { 0.0f, 1250.0f, 0.0f };
static Vec lbl_1_data_BC = { 1.0f, 0.0f, 0.0f };
static Vec lbl_1_data_C8 = { 0.0f, 0.0f, 0.0f };
static f32 lbl_1_data_D4[5] = { 244.0f, 266.0f, 288.0f, 310.0f, 332.0f };
M570Camera lbl_1_data_E8 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { -300.0f, 100.0f, 50.0f },
    -15.0f,
    90.0f,
    0.0f,
    500.0f,
};
M570Camera lbl_1_data_130 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { -300.0f, 100.0f, 50.0f },
    -15.0f,
    0.0f,
    0.0f,
    500.0f,
};
M570Camera lbl_1_data_178 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 300.0f, 100.0f, 50.0f },
    -15.0f,
    -90.0f,
    0.0f,
    600.0f,
};
M570Camera lbl_1_data_1C0 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 300.0f, 100.0f, 50.0f },
    -15.0f,
    0.0f,
    0.0f,
    600.0f,
};
M570Camera lbl_1_data_208 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 100.0f, -300.0f },
    -10.0f,
    0.0f,
    0.0f,
    400.0f,
};
M570Camera lbl_1_data_250 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 150.0f, 0.0f },
    -15.0f,
    0.0f,
    0.0f,
    1000.0f,
};
M570Camera lbl_1_data_298 = {
    1,
    1,
    40.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 150.0f, 0.0f },
    -15.0f,
    0.0f,
    0.0f,
    1600.0f,
};
static HU3DPARMANPARAM lbl_1_data_2FC = {
    0x1E,
    { 0 },
    100.0f,
    15.0f,
    180.0f,
    { 0.0f, 0.0f, 0.0f },
    1.2f,
    0.98f,
    30.0f,
    1.0f,
    1,
    { { 0xFF, 0xFF, 0xFF, 0x70 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0xFF, 0xFF, 0xFF, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
};
static s32 lbl_1_bss_0;
omObjData *lbl_1_bss_4;
static s32 lbl_1_bss_8;
omObjData *lbl_1_bss_C[8];
static s16 lbl_1_bss_2C[5];
static s16 lbl_1_bss_36[5];
static s16 lbl_1_bss_40;
static s32 lbl_1_bss_44;
static s32 lbl_1_bss_48;
static s16 lbl_1_bss_4C;
static s16 lbl_1_bss_4E;
static s16 lbl_1_bss_50;
static s16 lbl_1_bss_52;
M570Camera lbl_1_bss_54;
MGTIMER *lbl_1_bss_9C;
static s16 lbl_1_bss_A0[0xE];
static s16 lbl_1_bss_104;
static HUPROCESS *lbl_1_bss_108;
static u32 lbl_1_data_350[0xB] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MP5_MARIO, 202),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 131),
    DATA_MAKE_NUM(DATADIR_MP5_MARIO, 191),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 15),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 81),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7),
    0,
};
M570MotParam lbl_1_data_37C[0xA] = {
    { 10.0f, 0x40000001, 0 },
    { 10.0f, 0x40000001, 0 },
    { 10.0f, 0x40000001, 0 },
    { 10.0f, 0x40000001, 1 },
    { 10.0f, 0x40000001, 1 },
    { 10.0f, 0x40000001, 1 },
    { 10.0f, 0, 0 },
    { 10.0f, 0x40000001, 0 },
    { 10.0f, 0, 0 },
    { 10.0f, 0, 0 },
};
Vec lbl_1_data_3F4[4] = {
    { 0.0f, 90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f },
};
Vec lbl_1_data_424[4] = {
    { -300.0f, 0.0f, 50.0f },
    { 220.0f, 0.0f, -100.0f },
    { 280.0f, 0.0f, 50.0f },
    { 340.0f, 0.0f, 200.0f },
};
Vec lbl_1_data_454[4] = {
    { -200.0f, 0.0f, 50.0f },
    { 150.0f, 0.0f, -100.0f },
    { 175.0f, 0.0f, 50.0f },
    { 200.0f, 0.0f, 200.0f },
};
Vec lbl_1_data_484[4] = {
    { 0.0f, 0.0f, 300.0f },
    { -200.0f, 0.0f, 300.0f },
    { 0.0f, 0.0f, 300.0f },
    { 200.0f, 0.0f, 300.0f },
};
static s32 lbl_1_data_4B4[3] = { DATA_MAKE_NUM(DATADIR_MP5_M570, 11), DATA_MAKE_NUM(DATADIR_MP5_M570, 12), DATA_MAKE_NUM(DATADIR_MP5_M570, 13) };
static u16 lbl_1_data_4C0[4] = { 0x100, 0x200, 0x400, 0 };
Vec lbl_1_data_4C8[0x28] = {
    { -350.0f, -50.0f, -600.0f },
    { -250.0f, -50.0f, -600.0f },
    { -150.0f, -50.0f, -600.0f },
    { 350.0f, -50.0f, -600.0f },
    { 250.0f, -50.0f, -600.0f },
    { 150.0f, -50.0f, -600.0f },
    { -450.0f, -50.0f, -700.0f },
    { -350.0f, -50.0f, -700.0f },
    { -250.0f, -50.0f, -700.0f },
    { -150.0f, -50.0f, -700.0f },
    { 450.0f, -50.0f, -700.0f },
    { 350.0f, -50.0f, -700.0f },
    { 250.0f, -50.0f, -700.0f },
    { 150.0f, -50.0f, -700.0f },
    { -600.0f, -50.0f, -450.0f },
    { -600.0f, -50.0f, -325.0f },
    { -600.0f, -50.0f, -200.0f },
    { -600.0f, -50.0f, -75.0f },
    { -600.0f, -50.0f, 50.0f },
    { -600.0f, -50.0f, 175.0f },
    { -600.0f, -50.0f, 300.0f },
    { -600.0f, -50.0f, 425.0f },
    { -775.0f, -50.0f, -525.0f },
    { -775.0f, -50.0f, -325.0f },
    { -800.0f, -50.0f, -225.0f },
    { -925.0f, -50.0f, -350.0f },
    { -925.0f, -50.0f, -150.0f },
    { 600.0f, -50.0f, -450.0f },
    { 600.0f, -50.0f, -325.0f },
    { 600.0f, -50.0f, -200.0f },
    { 600.0f, -50.0f, -75.0f },
    { 600.0f, -50.0f, 50.0f },
    { 600.0f, -50.0f, 175.0f },
    { 600.0f, -50.0f, 300.0f },
    { 600.0f, -50.0f, 425.0f },
    { 750.0f, -50.0f, -650.0f },
    { 750.0f, -50.0f, -450.0f },
    { 750.0f, -50.0f, -175.0f },
    { 925.0f, -50.0f, -275.0f },
    { 900.0f, -50.0f, -475.0f },
};
M570Fan *lbl_1_bss_110[0x28];
static omObjData *lbl_1_bss_1B0;
M570Player *lbl_1_bss_1B4[3];
M570Player *lbl_1_bss_1C0;
M570Player *lbl_1_bss_1C4[4];
static s32 lbl_1_rodata_8C[0xD] = {
    DATA_MAKE_NUM(DATADIR_MP5_M570, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M570, 24),
}; /* const */
static u32 lbl_1_rodata_C0[5] = { DATA_MAKE_NUM(DATADIR_MP5_M570, 26), DATA_MAKE_NUM(DATADIR_MP5_M570, 28), DATA_MAKE_NUM(DATADIR_MP5_M570, 30), DATA_MAKE_NUM(DATADIR_MP5_M570, 32), DATA_MAKE_NUM(DATADIR_MP5_M570, 34) }; /* const */
static u32 lbl_1_rodata_D4[5] = { DATA_MAKE_NUM(DATADIR_MP5_M570, 25), DATA_MAKE_NUM(DATADIR_MP5_M570, 27), DATA_MAKE_NUM(DATADIR_MP5_M570, 29), DATA_MAKE_NUM(DATADIR_MP5_M570, 31), DATA_MAKE_NUM(DATADIR_MP5_M570, 33) }; /* const */
static s32 lbl_1_rodata_128[4] = { DATA_MAKE_NUM(DATADIR_MP5_M570, 15), DATA_MAKE_NUM(DATADIR_MP5_M570, 16), DATA_MAKE_NUM(DATADIR_MP5_M570, 17), DATA_MAKE_NUM(DATADIR_MP5_M570, 18) }; /* const */
static s32 lbl_1_rodata_138[2] = { DATA_MAKE_NUM(DATADIR_MP5_M570, 21), DATA_MAKE_NUM(DATADIR_MP5_M570, 22) }; /* const */
u32 lbl_1_rodata_160[4] = { 0x40000001, 0, 0, 0x40000001 }; /* const */



void ObjectSetup(void) {
    lbl_1_bss_108 = omInitObjMan(0xC8, 0x1000);
    lbl_1_bss_104 = -1;
    omGameSysInit(lbl_1_bss_108);
    MgSeqCreatePrio(&lbl_1_data_6C, 0x7D0);
    MgSeqModeHookAdd(4, fn_1_A7C);
    MgSeqModeDelaySet(2, 0x5DC);
}

void fn_1_120(s16 mode, s16 frameNo) {
    s16 temp_r3;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0xD) {
        lbl_1_bss_A0[var_r31] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_8C[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_A0[var_r31], 0x40000001U);
        Hu3DModelPosSet(lbl_1_bss_A0[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_A0[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_A0[var_r31], 0);
        Hu3DModelAmbSet(lbl_1_bss_A0[var_r31], 1.0f, 1.0f, 1.0f);
        var_r31 += 1;
        goto loop_2;
    }
    Hu3DModelPosSet(lbl_1_bss_A0[4], 0.0f, 0.0f, -270.0f);
    Hu3DModelAttrReset(lbl_1_bss_A0[0xA], 0x40000001U);
    Hu3DModelAttrSet(lbl_1_bss_A0[0xA], 0x40000002U);
    Hu3DModelAttrSet(lbl_1_bss_A0[0xB], 1U);
    Hu3DModelAttrSet(lbl_1_bss_A0[0xC], 1U);
    Hu3DModelAttrReset(lbl_1_bss_A0[0xB], 0x40000001U);
    Hu3DModelAttrReset(lbl_1_bss_A0[0xC], 0x40000001U);
    Hu3DModelAttrSet(lbl_1_bss_A0[0xB], 0x40000002U);
    Hu3DModelAttrSet(lbl_1_bss_A0[0xC], 0x40000002U);
    Hu3DModelPosSet(lbl_1_bss_A0[0xB], -350.0f, 0.0f, 540.0f);
    Hu3DModelPosSet(lbl_1_bss_A0[0xC], 350.0f, 0.0f, 540.0f);
    fn_1_1964(&lbl_1_data_E8);
    lbl_1_bss_54 = lbl_1_data_E8;
    temp_r3 = Hu3DGLightCreateV(&lbl_1_data_94.unk0, &lbl_1_data_94.unkC, &lbl_1_data_94.unk18);
    Hu3DGLightStaticSet(temp_r3, 1);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DShadowCreate(lbl_1_bss_54.unk8, lbl_1_bss_54.unkC, lbl_1_bss_54.unk10);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lbl_1_data_B0, &lbl_1_data_BC, &lbl_1_data_C8);
    Hu3DModelShadowMapSet(lbl_1_bss_A0[3]);
    fn_1_4210();
    lbl_1_bss_50 = 0;
    lbl_1_bss_4E = 0;
    lbl_1_bss_4C = 0;
    lbl_1_bss_52 = -1;
    lbl_1_bss_48 = -1;
    fn_1_56A0();
    fn_1_5A78();
    fn_1_1174();
    MgSeqModeNext();
}

void fn_1_520(s16 mode, s16 frameNo) {
    s32 var_r24;
    s32 var_r27;
    s32 var_r30;
    s32 var_r31;

    if ((WipeCheckEnd() == 0) && ((s32) lbl_1_bss_48 == -1)) {
        lbl_1_bss_48 = HuAudSStreamPlay(0x25);
    }
    if ((u32) lbl_1_bss_50 <= 6U) {
        switch (lbl_1_bss_50) {
        case 0:
            *lbl_1_bss_C = MgCameraMoveEntry(&lbl_1_data_E8, &lbl_1_data_130, 120.0f);
            fn_1_4440(lbl_1_bss_1C0, 3);
            lbl_1_bss_50 = 1;
            lbl_1_bss_44 = HuAudFXPlay(0x39C);
            return;
        case 1:
            if ((s32) (((M570CamMove *)lbl_1_bss_C[0]->data)->unk9C & 2) != 0) {
                var_r30 = 1;
            } else {
                var_r30 = 0;
            }
            if (var_r30 == 0) {
                omDelObjEx(lbl_1_bss_108, *lbl_1_bss_C);
                lbl_1_bss_50 = 2;
                lbl_1_bss_8 = 0;
                return;
            }
            break;
        case 2:
            lbl_1_bss_8 += 1;
            if ((s32) lbl_1_bss_8 == 0x1D) {
                WipeCreate(2, WIPE_TYPE_CROSS, 1);
            }
            if ((s32) lbl_1_bss_8 == 0x1E) {
                *lbl_1_bss_C = MgCameraMoveEntry(&lbl_1_data_178, &lbl_1_data_1C0, 120.0f);
                lbl_1_bss_50 = 3;
                Mp5WipeCrossIn(0x3C);
                lbl_1_bss_8 = 0;
                return;
            }
            break;
        case 3:
            if ((s32) lbl_1_bss_8 == 0) {
                fn_1_4440(lbl_1_bss_1B4[0], 3);
            } else if ((s32) lbl_1_bss_8 == 0x14) {
                fn_1_4440(lbl_1_bss_1B4[1], 3);
            } else if ((s32) lbl_1_bss_8 == 0x28) {
                fn_1_4440(lbl_1_bss_1B4[2], 3);
            }
            lbl_1_bss_8 += 1;
            if ((s32) (((M570CamMove *)lbl_1_bss_C[0]->data)->unk9C & 2) != 0) {
                var_r27 = 1;
            } else {
                var_r27 = 0;
            }
            if (var_r27 == 0) {
                omDelObjEx(lbl_1_bss_108, *lbl_1_bss_C);
                lbl_1_bss_50 = 4;
                lbl_1_bss_8 = 0;
                return;
            }
            break;
        case 4:
            lbl_1_bss_8 += 1;
            if ((s32) lbl_1_bss_8 == 0x1D) {
                WipeCreate(2, WIPE_TYPE_CROSS, 1);
            }
            if ((s32) lbl_1_bss_8 == 0x1E) {
                fn_1_1A50(&lbl_1_data_208);
                lbl_1_bss_50 = 5;
                Mp5WipeCrossIn(0x3C);
                fn_1_5E38();
                fn_1_4DC4();
                HuAudFXStop(lbl_1_bss_44);
                lbl_1_bss_8 = 0;
                return;
            }
            break;
        case 5:
            if (WipeCheckEnd() == 0) {
                if ((s32) lbl_1_bss_8 == 0) {
                    Hu3DModelAttrReset(lbl_1_bss_A0[0xA], 0x40000002U);
                    Hu3DModelAttrSet(lbl_1_bss_A0[8], 1U);
                    Hu3DModelAttrSet(lbl_1_bss_A0[9], 1U);
                }
                if (Hu3DMotionEndCheck(lbl_1_bss_A0[0xA]) != 0) {
                    *lbl_1_bss_C = MgCameraMoveEntry(&lbl_1_data_208, &lbl_1_data_250, 30.0f);
                    lbl_1_bss_50 = 6;
                }
                lbl_1_bss_8 += 1;
                return;
            }
            break;
        case 6:
            if ((s32) (((M570CamMove *)lbl_1_bss_C[0]->data)->unk9C & 2) != 0) {
                var_r24 = 1;
            } else {
                var_r24 = 0;
            }
            if (var_r24 == 0) {
                omDelObjEx(lbl_1_bss_108, *lbl_1_bss_C);
                lbl_1_bss_50 = 8;
                var_r31 = 0;
loop_42:
                if (var_r31 < 4) {
                    fn_1_4440(lbl_1_bss_1C4[var_r31], 4);
                    var_r31 += 1;
                    goto loop_42;
                }
                return;
            }
            break;
        }
    } else {
        MgSeqModeNext();
    }
}

void fn_1_A78(s16 mode, s16 frameNo) {

}

void fn_1_A7C(s16 mode, s16 frameNo) {
    lbl_1_bss_50 = 9;
    lbl_1_bss_4C = 0;
    fn_1_12F0();
}

void fn_1_ABC(s16 mode, s16 frameNo) {
    s16 temp_r4;
    s16 temp_r4_2;

    switch ((s16) lbl_1_bss_50) {                   /* switch 1; irregular */
    case 9:                                         /* switch 1 */
        if ((s16) lbl_1_bss_4C == 0) {
            fn_1_4D2C();
            fn_1_5820(1);
        }
        temp_r4 = lbl_1_bss_4C;
        lbl_1_bss_4C = temp_r4 + 1;
        if (temp_r4 == 0x14) {
            fn_1_1038();
            lbl_1_bss_44 = HuAudFXPlayVol(0x39C, 0x60);
            fn_1_5F24(1);
            fn_1_15FC((s32) lbl_1_bss_4E);
            lbl_1_bss_50 = 0xA;
            lbl_1_bss_4C = 0;
            return;
        }
        return;
    case 10:                                        /* switch 1 */
        temp_r4_2 = lbl_1_bss_4C;
        lbl_1_bss_4C = temp_r4_2 + 1;
        if (temp_r4_2 == 0x3C) {
            HuAudFXStop(lbl_1_bss_44);
        }
        if (MgTimerDoneCheck(lbl_1_bss_9C) != 0) {
            lbl_1_bss_50 = 0xB;
            fn_1_5048();
            lbl_1_bss_4C = 0;
            return;
        }
        break;
    case 11:                                        /* switch 1 */
        lbl_1_bss_4C += 1;
        switch ((s16) lbl_1_bss_4C) {               /* switch 2; irregular */
        case 0x5A:                                  /* switch 2 */
            lbl_1_bss_4E += 1;
            MgTimerKill(lbl_1_bss_9C);
            fn_1_51A8();
            if ((fn_1_5538() != 0) || ((s16) lbl_1_bss_4E == 5)) {
                if (fn_1_5538() != 0) {
                    lbl_1_bss_52 = 0;
                } else {
                    lbl_1_bss_52 = 1;
                    lbl_1_bss_1C0->unk48 = 1;
                    lbl_1_bss_1C0->unk28 = 5;
                    fn_1_4440(lbl_1_bss_1C0, 6);
                }
                fn_1_1098();
                lbl_1_bss_50 = 0xD;
                fn_1_5820(2);
                lbl_1_bss_44 = HuAudFXPlayVol(0x39C, 0x60);
                fn_1_5F24(2);
                fn_1_1464();
                MgSeqModeNext();
                return;
            }
            break;
        case 0xB4:                                  /* switch 2 */
            lbl_1_bss_4C = 0;
            lbl_1_bss_50 = 9;
            break;
        }
        break;
    }
}

void fn_1_D88(s16 mode, s16 frameNo) {
    s16 sp8;

    sp8 = frameNo;
    if ((sp8 == 0) && ((s32) lbl_1_bss_48 != -1)) {
        HuAudSStreamFadeOut(lbl_1_bss_48, 0x64);
    }
    lbl_1_bss_50 = 0xD;
}

void fn_1_DEC(s16 mode, s16 frameNo) {
    s16 sp8;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 == 0) {
        HuAudFXStop(lbl_1_bss_44);
    }
    switch ((s16) lbl_1_bss_50) {                   /* irregular */
    case 13:
        lbl_1_bss_4 = MgCameraMoveEntry(&lbl_1_data_250, &lbl_1_data_298, 80.0f);
        fn_1_4EF8();
        lbl_1_bss_50 = 0xE;
        return;
    case 14:
        if ((s32) (((M570CamMove *)lbl_1_bss_4->data)->unk9C & 2) != 0) {
            var_r31 = 1;
        } else {
            var_r31 = 0;
        }
        if (var_r31 == 0) {
            lbl_1_bss_0 = 0;
            omDelObjEx(lbl_1_bss_108, lbl_1_bss_4);
            lbl_1_bss_50 = 0xF;
            fn_1_5354();
            fn_1_5820(3);
            lbl_1_bss_44 = HuAudFXPlayVol(0x39C, 0x60);
            fn_1_5F24(0x14);
            MgSeqModeNext();
        }
        return;
    }
}

void fn_1_F54(s16 mode, s16 frameNo) {
    s16 var_r31;

    if (frameNo == 0) {
        lbl_1_bss_50 = 0x11;
    }
    if (frameNo == 0x64) {
        var_r31 = 0;
loop_5:
        if (var_r31 < 4) {
            omVibrate(var_r31, 0x3C, 0xC, 0);
            var_r31 += 1;
            goto loop_5;
        }
        HuAudFXPlay(0x914);
        Hu3DModelAttrReset(lbl_1_bss_A0[0xB], 1U);
        Hu3DModelAttrReset(lbl_1_bss_A0[0xC], 1U);
        Hu3DModelAttrReset(lbl_1_bss_A0[0xB], 0x40000002U);
        Hu3DModelAttrReset(lbl_1_bss_A0[0xC], 0x40000002U);
    }
}

void fn_1_1034(s16 mode, s16 frameNo) {

}

void fn_1_1038(void) {
    lbl_1_bss_9C = MgTimerCreate(0);
    MgTimerParamSet(lbl_1_bss_9C, 0xB4, 0, 0);
    MgTimerModeOnSet(lbl_1_bss_9C, 1);
}

void fn_1_1098(void) {
    s16 sp8[4];
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        sp8[var_r31] = -1;
        if ((s16) lbl_1_bss_52 == (s16) lbl_1_bss_1C4[var_r31]->unk6) {
            sp8[var_r31] = lbl_1_bss_1C4[var_r31]->unk2;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[var_r31].coin_win = 0xA;
            }
        }
        var_r31 += 1;
        goto loop_5;
    }
    MgSeqWinnerSet(sp8[0], sp8[1], sp8[2], sp8[3]);
}

void fn_1_1174(void) {
    s16 temp_r3;
    s16 temp_r3_2;
    s32 var_r31;

    lbl_1_bss_40 = MgScoreWinCreate(0x84, 0x28);
    MgScoreWinPosSet(lbl_1_bss_40, 288.0f, 420.0f);
    MgScoreWinDispSet(lbl_1_bss_40, 0);
    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        temp_r3 = espEntry(lbl_1_rodata_D4[var_r31], 0x20, 0);
        espDrawNoSet(temp_r3, 0);
        espPosSet(temp_r3, lbl_1_data_D4[var_r31], 420.0f);
        espDispOff(temp_r3);
        lbl_1_bss_2C[var_r31] = temp_r3;
        temp_r3_2 = espEntry(lbl_1_rodata_C0[var_r31], 0x10, 0);
        espDrawNoSet(temp_r3_2, 0);
        espPosSet(temp_r3_2, lbl_1_data_D4[var_r31], 420.0f);
        espDispOff(temp_r3_2);
        lbl_1_bss_36[var_r31] = temp_r3_2;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_12F0(void) {
    s32 var_r31;

    MgScoreWinDispSet(lbl_1_bss_40, 1);
    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        espDispOn(lbl_1_bss_2C[var_r31]);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_1354(omObjData *arg0) {
    f32 temp_f31;
    s32 var_r30;

    arg0->work[0] += 1;
    temp_f31 = 1.0f - (0.05f * (f32) arg0->work[0]);
    MgScoreWinTPLvlSet(lbl_1_bss_40, temp_f31);
    var_r30 = 0;
loop_2:
    if (var_r30 < 5) {
        espTPLvlSet(lbl_1_bss_2C[var_r30], temp_f31);
        espTPLvlSet(lbl_1_bss_36[var_r30], temp_f31);
        var_r30 += 1;
        goto loop_2;
    }
    if ((u32) arg0->work[0] == 0x14) {
        omDelObjEx(lbl_1_bss_108, arg0);
    }
}

void fn_1_1464(void) {
    omAddObjEx(lbl_1_bss_108, 0x1300, 0U, 0U, -1, fn_1_1354);
}

void fn_1_14A8(omObjData *arg0) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r30;

    temp_r30 = (s16) arg0->work[0];
    if ((u32) arg0->work[1] == 0) {
        espDispOn((s16) arg0->work[0]);
    }
    temp_f30 = (f32) sin((3.141592653589793 * (f64) ((90.0f * (f32) arg0->work[1]) / 60.0f)) / 180.0);
    temp_f31 = 1.0f + (2.0f - (2.0f * temp_f30));
    espScaleSet(temp_r30, temp_f31, temp_f31);
    espTPLvlSet(temp_r30, temp_f30);
    arg0->work[1] += 1;
    if ((u32) arg0->work[1] > 0x3CU) {
        omDelObjEx(lbl_1_bss_108, arg0);
    }
}

void fn_1_15FC(s32 arg0) {
    s32 sp8;
    omObjData *temp_r3;

    sp8 = arg0;
    temp_r3 = omAddObjEx(lbl_1_bss_108, 0x1300, 0U, 0U, -1, fn_1_14A8);
    temp_r3->work[0] = (u32) lbl_1_bss_36[sp8];
    temp_r3->work[1] = 0;
}

void fn_1_1674(omObjData *arg0) {
    arg0->work[0] -= 1;
    if ((u32) arg0->work[0] == 0) {
        Hu3DParManKill((s16) arg0->work[1]);
        omDelObjEx(lbl_1_bss_108, arg0);
    }
}

s16 fn_1_16D4(Vec *arg0) {
    omObjData *temp_r3_2;
    s16 temp_r3;

    temp_r3 = Hu3DParManCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_EFFECT, 2), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x64, &lbl_1_data_2FC);
    Hu3DParManPosSet(temp_r3, arg0->x, arg0->y, arg0->z);
    Hu3DParManVecSet(temp_r3, 0.0f, 0.0f, 1.0f);
    Hu3DParManTimeLimitSet(temp_r3, 0x1E);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(temp_r3), 3);
    temp_r3_2 = omAddObjEx(lbl_1_bss_108, 0x1300, 0U, 0U, -1, fn_1_1674);
    temp_r3_2->work[0] = 0x1E;
    temp_r3_2->work[1] = (u32) temp_r3;
    return temp_r3;
}

s16 fn_1_17DC(Vec *arg0) {
    Vec spC;
    Vec *sp8;

    sp8 = arg0;
    Hu3D3Dto2D(arg0, (s16) lbl_1_bss_54.unk0, &spC);
    return (s16) (32.0f + (64.0f * (spC.x / 576.0f)));
}

void fn_1_1864(Vec *arg0, s16 arg1) {
    Vec sp10;
    s16 spC;
    Vec *sp8;

    sp8 = arg0;
    spC = arg1;
    Hu3D3Dto2D(arg0, (s16) lbl_1_bss_54.unk0, &sp10);
    HuAudFXPlayPan((s32) spC, (s16) (32.0f + (64.0f * (sp10.x / 576.0f))));
}


M570Camera *fn_1_1964(M570Camera *arg0) {
    M570Camera *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M570Camera), MEMORY_DEFAULT_NUM);
    *temp_r3 = *arg0;
    Hu3DCameraCreate(arg0->unk0);
    Hu3DCameraViewportSet(arg0->unk0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(arg0->unk0, arg0->unk8, arg0->unkC, arg0->unk10, 1.2f);
    fn_1_1A50(arg0);
    return (M570Camera *) temp_r3;
}

void fn_1_1A50(M570Camera *arg0) {
    if ((s32) arg0->unk4 == 1) {
        fn_1_2050(arg0);
    }
    Hu3DCameraPosSetV(arg0->unk0, &arg0->unk14, &arg0->unk20, &arg0->unk2C);
}





void fn_1_2050(M570Camera *arg0) {
    Vec sp8;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f64 temp_f24;
    f64 temp_f24_10;
    f64 temp_f24_11;
    f64 temp_f24_12;
    f64 temp_f24_2;
    f64 temp_f24_3;
    f64 temp_f24_4;
    f64 temp_f24_5;
    f64 temp_f24_6;
    f64 temp_f24_7;
    f64 temp_f24_8;
    f64 temp_f24_9;
    f64 temp_f25;
    f64 temp_f25_2;
    f64 temp_f25_3;
    f64 temp_f25_4;

    temp_f30 = arg0->unk38;
    temp_f29 = arg0->unk3C;
    temp_f31 = arg0->unk40;
    temp_f24 = cos((3.141592653589793 * (f64) temp_f30) / 180.0);
    arg0->unk14.x = (f32) ((f64) arg0->unk2C.x + ((f64) arg0->unk44 * (sin((3.141592653589793 * (f64) temp_f29) / 180.0) * temp_f24)));
    arg0->unk14.y = (f32) ((f64) arg0->unk2C.y + ((f64) arg0->unk44 * -sin((3.141592653589793 * (f64) temp_f30) / 180.0)));
    temp_f24_2 = cos((3.141592653589793 * (f64) temp_f30) / 180.0);
    arg0->unk14.z = (f32) ((f64) arg0->unk2C.z + ((f64) arg0->unk44 * (cos((3.141592653589793 * (f64) temp_f29) / 180.0) * temp_f24_2)));
    VECSubtract(&arg0->unk14, &arg0->unk2C, &sp8);
    VECNormalize(&sp8, &sp8);
    temp_f24_3 = sin((3.141592653589793 * (f64) temp_f30) / 180.0);
    temp_f28 = (f32) (sin((3.141592653589793 * (f64) temp_f29) / 180.0) * temp_f24_3);
    temp_f27 = (f32) cos((3.141592653589793 * (f64) temp_f30) / 180.0);
    temp_f24_4 = sin((3.141592653589793 * (f64) temp_f30) / 180.0);
    temp_f26 = (f32) (cos((3.141592653589793 * (f64) temp_f29) / 180.0) * temp_f24_4);
    temp_f24_5 = (f64) sp8.y * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f25 = (f64) temp_f26 * (((f64) (sp8.x * sp8.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f24_5);
    temp_f24_6 = (f64) sp8.z * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f24_7 = (f64) temp_f27 * (((f64) (sp8.x * sp8.y) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f24_6);
    arg0->unk20.x = (f32) (((f64) temp_f28 * ((f64) (sp8.x * sp8.x) + ((f64) (1.0f - (sp8.x * sp8.x)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f24_7 + temp_f25);
    temp_f24_8 = (f64) sp8.x * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f25_2 = (f64) temp_f26 * (((f64) (sp8.y * sp8.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f24_8);
    temp_f24_9 = (f64) sp8.z * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f24_10 = (f64) temp_f28 * (((f64) (sp8.x * sp8.y) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f24_9);
    arg0->unk20.y = (f32) (((f64) temp_f27 * ((f64) (sp8.y * sp8.y) + ((f64) (1.0f - (sp8.y * sp8.y)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f24_10 + temp_f25_2);
    temp_f24_11 = (f64) sp8.x * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f24_12 = (f64) temp_f27 * (((f64) (sp8.y * sp8.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) + temp_f24_11);
    temp_f25_3 = (f64) sp8.y * sin((3.141592653589793 * (f64) temp_f31) / 180.0);
    temp_f25_4 = ((f64) temp_f28 * (((f64) (sp8.x * sp8.z) * (1.0 - cos((3.141592653589793 * (f64) temp_f31) / 180.0))) - temp_f25_3)) + temp_f24_12;
    arg0->unk20.z = (f32) (((f64) temp_f26 * ((f64) (sp8.z * sp8.z) + ((f64) (1.0f - (sp8.z * sp8.z)) * cos((3.141592653589793 * (f64) temp_f31) / 180.0)))) + temp_f25_4);
    VECNormalize(&arg0->unk20, &arg0->unk20);
}


void fn_1_2B18(omObjData *arg0) {
    M570Camera *temp_r30;
    f32 temp_f31;
    M570CamMove *temp_r28;
    M570Camera *temp_r29;
    M570Camera *temp_r31;

    temp_r28 = arg0->data;
    if ((s32) (temp_r28->unk9C & 2) != 0) {
        temp_r30 = temp_r28->unk0;
        temp_r31 = &temp_r28->unk4;
        temp_r29 = &temp_r28->unk4C;
        temp_r28->unk98 = (f32) (temp_r28->unk98 + 1.0f);
        temp_f31 = temp_r28->unk98 / temp_r28->unk94;
        if ((s32) temp_r30->unk4 == 0) {
            temp_r30->unk14.x = temp_r31->unk14.x + (temp_f31 * (temp_r29->unk14.x - temp_r31->unk14.x));
            temp_r30->unk14.y = temp_r31->unk14.y + (temp_f31 * (temp_r29->unk14.y - temp_r31->unk14.y));
            temp_r30->unk14.z = temp_r31->unk14.z + (temp_f31 * (temp_r29->unk14.z - temp_r31->unk14.z));
        } else {
            temp_r30->unk44 = temp_r31->unk44 + (temp_f31 * (temp_r29->unk44 - temp_r31->unk44));
            temp_r30->unk38 = temp_r31->unk38 + (temp_f31 * (temp_r29->unk38 - temp_r31->unk38));
            temp_r30->unk3C = temp_r31->unk3C + (temp_f31 * (temp_r29->unk3C - temp_r31->unk3C));
        }
        temp_r30->unk2C.x = temp_r31->unk2C.x + (temp_f31 * (temp_r29->unk2C.x - temp_r31->unk2C.x));
        temp_r30->unk2C.y = temp_r31->unk2C.y + (temp_f31 * (temp_r29->unk2C.y - temp_r31->unk2C.y));
        temp_r30->unk2C.z = temp_r31->unk2C.z + (temp_f31 * (temp_r29->unk2C.z - temp_r31->unk2C.z));
        if (temp_r28->unk98 >= temp_r28->unk94) {
            *temp_r30 = *temp_r29;
            temp_r28->unk9C = (s32) (temp_r28->unk9C & 0xFFFFFFFD);
        }
        fn_1_1A50(temp_r30);
    }
}

omObjData *MgCameraMoveEntry(M570Camera *arg0, M570Camera *arg1, f32 farg0) {
    f32 sp8;
    omObjData *temp_r29;
    M570CamMove *temp_r31;

    sp8 = farg0;
    if ((s32) arg0->unk0 != (s32) arg1->unk0) {
        OSReport("MgCameraMoveEntry : Camera Number Different\n");
        return NULL;
    }
    temp_r29 = omAddObjEx(lbl_1_bss_108, 0x2000, 0U, 0U, -1, fn_1_2B18);
    temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M570CamMove), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r29->data;
    temp_r31->unk94 = sp8;
    temp_r31->unk98 = 0.0f;
    temp_r31->unk0 = arg0;
    temp_r31->unk4 = *arg0;
    temp_r31->unk4C = *arg1;
    temp_r31->unk9C = 3;
    if ((s32) arg0->unk4 == 1) {
        fn_1_2050(&temp_r31->unk4);
        fn_1_2050(&temp_r31->unk4C);
    }
    return temp_r29;
}
























void fn_1_3A74(M570Player *arg0, s16 arg1) {
    arg0->unk0 = arg1;
    arg0->unk2 = GWPlayerCfg[arg1].character;
    arg0->unk4 = GWPlayerCfg[arg1].pad_idx;
    arg0->unk6 = GWPlayerCfg[arg1].group;
    arg0->unkC = (s32) GWPlayerCfg[arg1].iscom;
    arg0->unk8 = GWPlayerCfg[arg1].diff;
    arg0->unk28 = 0;
    arg0->unk10.z = 0.0f;
    arg0->unk10.y = 0.0f;
    arg0->unk10.x = 0.0f;
    arg0->unk1C.z = 0.0f;
    arg0->unk1C.y = 0.0f;
    arg0->unk1C.x = 0.0f;
}

s32 fn_1_3B40(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0) {
    Vec spC;
    f32 sp8;
    f32 temp_f1;

    sp8 = farg0;
    VECSubtract(arg1, arg0, &spC);
    temp_f1 = VECMag(&spC);
    if (temp_f1 == 0.0f) {
        return 1;
    }
    VECNormalize(&spC, &spC);
    VECScale(&spC, &spC, sp8);
    if (VECMag(&spC) >= temp_f1) {
        *arg0 = *arg1;
        return 1;
    }
    VECAdd(arg0, &spC, arg0);
    arg2->y = (f32) (180.0 * (atan2((f64) spC.x, (f64) spC.z) / 3.141592653589793));
    return 0;
}

f32 fn_1_3C64(f32 farg0, f32 farg1, f32 farg2) {
    f32 sp8;
    f32 var_f30;
    f32 var_f31;

    sp8 = farg1;
    var_f31 = (f32) fmod((f64) (sp8 - farg0), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    if (fabs(var_f31) > farg2) {
        if (var_f31 < 0.0f) {
            var_f31 = -farg2;
        } else {
            var_f31 = farg2;
        }
    }
    var_f30 = (f32) fmod((f64) (farg0 + var_f31), 360.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    return var_f30;
}





void fn_1_4210(void) {
    omObjData *temp_r30;
    Vec *temp_r4;
    Vec *temp_r4_2;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r29;
    s32 temp_r0;
    s32 var_r26;
    s32 var_r27;
    M570Player *temp_r31;

    var_r26 = 0;
    var_r29 = 0;
loop_8:
    if (var_r29 < 4) {
        temp_r30 = omAddObjEx(lbl_1_bss_108, (s16) (var_r29 + 0x1000), 4U, 0xAU, -1, fn_1_457C);
        temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M570Player), MEMORY_DEFAULT_NUM);
        memset(temp_r30->data, 0, sizeof(M570Player));
        temp_r31 = temp_r30->data;
        temp_r31->unk2C = temp_r30;
        fn_1_3A74((M570Player *) temp_r31, var_r29);
        if ((s16) temp_r31->unk6 == 0) {
            temp_r31->unk34 = 0;
            lbl_1_bss_1C0 = (M570Player *) temp_r31;
        } else {
            temp_r31->unk34 = (s16) (var_r26 + 1);
            temp_r0 = var_r26;
            var_r26 += 1;
            lbl_1_bss_1B4[temp_r0] = (M570Player *) temp_r31;
        }
        lbl_1_bss_1C4[var_r29] = (M570Player *) temp_r31;
        temp_r4 = &lbl_1_data_424[temp_r31->unk34];
        temp_r31->unk10.x = (f32) temp_r4->x;
        temp_r31->unk10.y = (f32) temp_r4->y;
        temp_r31->unk10.z = (f32) temp_r4->z;
        temp_r4_2 = &lbl_1_data_3F4[temp_r31->unk34];
        temp_r31->unk1C.x = (f32) temp_r4_2->x;
        temp_r31->unk1C.y = (f32) temp_r4_2->y;
        temp_r31->unk1C.z = (f32) temp_r4_2->z;
        temp_r31->unk28 = 0;
        temp_r31->unk48 = 0;
        temp_r31->unk36 = -1;
        temp_r3 = CharModelMotListCreate(temp_r31->unk2, 2, lbl_1_data_350, temp_r30->motion);
        *temp_r30->model = temp_r3;
        CharMotionSet(temp_r31->unk2, *temp_r30->motion);
        Hu3DModelLayerSet(temp_r3, 2);
        Hu3DModelShadowSet(temp_r3);
        fn_1_4440((M570Player *) temp_r31, 0);
        var_r27 = 0;
loop_6:
        if (var_r27 < 3) {
            temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4B4[var_r27], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r30->model[var_r27 + 1] = temp_r3_2;
            Hu3DModelAttrSet(temp_r3_2, 1U);
            var_r27 += 1;
            goto loop_6;
        }
        var_r29 += 1;
        goto loop_8;
    }
    CharEffectLayerSet(3);
}

void fn_1_4440(M570Player *arg0, s16 arg1) {
    omObjData *temp_r29;
    f32 var_f31;

    if ((s16) arg0->unk36 != arg1) {
        temp_r29 = arg0->unk2C;
        if (((s16) arg0->unk36 == 5) && (arg1 == 4)) {
            var_f31 = 75.0f;
        } else {
            var_f31 = 0.0f;
        }
        CharMotionShiftSet(arg0->unk2, temp_r29->motion[arg1], var_f31, lbl_1_data_37C[arg1].unk0, lbl_1_data_37C[arg1].unk4);
        if ((s32) lbl_1_data_37C[arg1].unk8 != 0) {
            Hu3DMotionAttrSet(temp_r29->motion[arg1], 1U);
        } else {
            Hu3DMotionAttrReset(temp_r29->motion[arg1], 1U);
        }
        arg0->unk36 = arg1;
    }
}

void fn_1_457C(omObjData *arg0) {
    M570Player *temp_r31;

    temp_r31 = arg0->data;
    arg0->func = fn_1_45E4;
    omSetRot(arg0, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
    omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
}

void fn_1_45E4(omObjData *obj) {
    Vec sp8;
    f32 var_f29;
    s32 temp_r3;
    s32 temp_r3_2;
    u32 temp_r0;
    omObjData *temp_r27;
    omObjData *temp_r28;
    omObjData *temp_r29;
    omObjData *temp_r30;
    M570Player *temp_r31;

    temp_r31 = obj->data;
    CharModelVoicePanSet(temp_r31->unk2, fn_1_17DC(&temp_r31->unk10));
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {
    case 7:
        if (fn_1_3B40(&temp_r31->unk10, &temp_r31->unk38, &sp8, 5.0f) != 0) {
            temp_r31->unk28 = 0U;
            if ((s16) temp_r31->unk36 != 0) {
                temp_r30 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, *temp_r30->motion, 0.0f, lbl_1_data_37C->unk0, lbl_1_data_37C->unk4);
                if ((s32) lbl_1_data_37C->unk8 != 0) {
                    Hu3DMotionAttrSet(*temp_r30->motion, 1U);
                } else {
                    Hu3DMotionAttrReset(*temp_r30->motion, 1U);
                }
                temp_r31->unk36 = 0;
            }
        }
        break;
    case 8:
        if (fn_1_3B40(&temp_r31->unk10, &temp_r31->unk38, &temp_r31->unk1C, 10.0f) != 0) {
            temp_r31->unk28 = 9U;
        }
        break;
    case 9:
        temp_r31->unk1C.y = fn_1_3C64(temp_r31->unk1C.y, 0.0f, 10.0f);
        if (temp_r31->unk1C.y <= 0.1f) {
            if ((s16) temp_r31->unk36 != 0) {
                temp_r29 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, *temp_r29->motion, 0.0f, lbl_1_data_37C->unk0, lbl_1_data_37C->unk4);
                if ((s32) lbl_1_data_37C->unk8 != 0) {
                    Hu3DMotionAttrSet(*temp_r29->motion, 1U);
                } else {
                    Hu3DMotionAttrReset(*temp_r29->motion, 1U);
                }
                temp_r31->unk36 = 0;
            }
            temp_r31->unk28 = 0U;
        }
        break;
    case 1:
        fn_1_4AC8((M570Player *) temp_r31);
        break;
    case 2:
        temp_r3 = temp_r31->unk44;
        temp_r31->unk44 = (s32) (temp_r3 + 1);
        if (temp_r3 == 0xF) {
            fn_1_4BB0((M570Player *) temp_r31);
        }
        if ((s32) temp_r31->unk44 == 0x14) {
            fn_1_4CC8((M570Player *) temp_r31);
            temp_r31->unk28 = 0U;
        }
        break;
    case 4:
        temp_r31->unk44 = (s32) (temp_r31->unk44 + 1);
        if ((s32) temp_r31->unk44 == 0x14) {
            if ((s16) temp_r31->unk36 != 4) {
                temp_r28 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {
                    var_f29 = 75.0f;
                } else {
                    var_f29 = 0.0f;
                }
                CharMotionShiftSet(temp_r31->unk2, temp_r28->motion[4], var_f29, lbl_1_data_37C[4].unk0, lbl_1_data_37C[4].unk4);
                if ((s32) lbl_1_data_37C[4].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r28->motion[4], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r28->motion[4], 1U);
                }
                temp_r31->unk36 = 4;
            }
            temp_r31->unk44 = 0;
            temp_r31->unk28 = 0U;
        }
        break;
    case 5:
        if ((s32) temp_r31->unk44 == 0) {
            omVibrate(temp_r31->unk0, 0x1E, 0xC, 0);
            fn_1_1864(&temp_r31->unk10, 0x913);
        }
        if ((s16) temp_r31->unk6 == 0) {
            temp_r31->unk10.x = (f32) (temp_r31->unk10.x - 3.0f);
        } else {
            temp_r31->unk10.x = (f32) (temp_r31->unk10.x + 3.0f);
        }
        temp_r3_2 = temp_r31->unk44;
        temp_r31->unk44 = (s32) (temp_r3_2 + 1);
        if (temp_r3_2 == 0x23) {
            temp_r31->unk48 = 1;
            if ((s16) temp_r31->unk36 != 7) {
                temp_r27 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, temp_r27->motion[7], 0.0f, lbl_1_data_37C[7].unk0, lbl_1_data_37C[7].unk4);
                if ((s32) lbl_1_data_37C[7].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r27->motion[7], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r27->motion[7], 1U);
                }
                temp_r31->unk36 = 7;
            }
            temp_r31->unk28 = 6U;
        }
        break;
    }
    omSetRot(obj, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
    omSetTra(obj, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
}

void fn_1_4AC8(M570Player *arg0) {
    s16 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 >= 3) {
        return;
    }
    if ((s32) (HuPadBtnDown[arg0->unk4] & lbl_1_data_4C0[var_r31]) != 0) {
        omVibrate(arg0->unk0, 0xC, 6, 6);
        arg0->unk4C = var_r31;
        return;
    }
    var_r31 += 1;
    goto loop_4;
}


void fn_1_4BB0(M570Player *arg0) {
    s16 temp_r30;

    temp_r30 = arg0->unk2C->model[arg0->unk4C + 1];
    Hu3DModelHookSet(*arg0->unk2C->model, CharModelItemHookGet(arg0->unk2, 2, 0), temp_r30);
    Hu3DModelLayerSet(temp_r30, 3);
    Hu3DModelAttrReset(temp_r30, 1U);
    Hu3DModelRotSet(temp_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(temp_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(temp_r30, 1.0f, 1.0f, 1.0f);
}

void fn_1_4CC8(M570Player *arg0) {
    Vec sp8;

    Hu3DModelObjPosGet(*arg0->unk2C->model, CharModelItemHookGet(arg0->unk2, 2, 0), &sp8);
    fn_1_16D4(&sp8);
}

void fn_1_4D2C(void) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        if ((s32) lbl_1_bss_1C4[var_r31]->unk48 == 0) {
            lbl_1_bss_1C4[var_r31]->unk28 = 1;
            lbl_1_bss_1C4[var_r31]->unk4C = frandmod(3U);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_4DC4(void) {
    M570Player *temp_r31;
    omObjData *temp_r30;
    Vec *temp_r4;
    s32 var_r29;

    var_r29 = 0;
loop_8:
    if (var_r29 < 4) {
        temp_r31 = lbl_1_bss_1C4[var_r29];
        temp_r31->unk28 = 7;
        temp_r4 = &lbl_1_data_454[temp_r31->unk34];
        temp_r31->unk38.x = temp_r4->x;
        temp_r31->unk38.y = temp_r4->y;
        temp_r31->unk38.z = temp_r4->z;
        if ((s16) temp_r31->unk36 != 1) {
            temp_r30 = temp_r31->unk2C;
            if ((s16) temp_r31->unk36 == 5) {

            }
            CharMotionShiftSet(temp_r31->unk2, temp_r30->motion[1], 0.0f, lbl_1_data_37C[1].unk0, lbl_1_data_37C[1].unk4);
            if ((s32) lbl_1_data_37C[1].unk8 != 0) {
                Hu3DMotionAttrSet(temp_r30->motion[1], 1U);
            } else {
                Hu3DMotionAttrReset(temp_r30->motion[1], 1U);
            }
            temp_r31->unk36 = 1;
        }
        var_r29 += 1;
        goto loop_8;
    }
}

void fn_1_4EF8(void) {
    M570Player *temp_r31;
    omObjData *temp_r30;
    Vec *temp_r4;
    s32 var_r29;

    var_r29 = 0;
loop_9:
    if (var_r29 < 4) {
        temp_r31 = lbl_1_bss_1C4[var_r29];
        if ((s16) temp_r31->unk6 == (s16) lbl_1_bss_52) {
            temp_r31->unk28 = 8;
            temp_r4 = &lbl_1_data_484[temp_r31->unk34];
            temp_r31->unk38.x = temp_r4->x;
            temp_r31->unk38.y = temp_r4->y;
            temp_r31->unk38.z = temp_r4->z;
            if ((s16) temp_r31->unk36 != 2) {
                temp_r30 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, temp_r30->motion[2], 0.0f, lbl_1_data_37C[2].unk0, lbl_1_data_37C[2].unk4);
                if ((s32) lbl_1_data_37C[2].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r30->motion[2], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r30->motion[2], 1U);
                }
                temp_r31->unk36 = 2;
            }
        }
        var_r29 += 1;
        goto loop_9;
    }
}

void fn_1_5048(void) {
    M570Player *temp_r31;
    omObjData *temp_r29;
    s32 var_r30;

    HuAudFXPlay(0x911);
    var_r30 = 0;
loop_9:
    if (var_r30 < 4) {
        if ((s32) lbl_1_bss_1C4[var_r30]->unk48 == 0) {
            lbl_1_bss_1C4[var_r30]->unk28 = 2;
            lbl_1_bss_1C4[var_r30]->unk44 = 0;
            temp_r31 = lbl_1_bss_1C4[var_r30];
            if ((s16) temp_r31->unk36 != 5) {
                temp_r29 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, temp_r29->motion[5], 0.0f, lbl_1_data_37C[5].unk0, lbl_1_data_37C[5].unk4);
                if ((s32) lbl_1_data_37C[5].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r29->motion[5], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r29->motion[5], 1U);
                }
                temp_r31->unk36 = 5;
            }
        }
        var_r30 += 1;
        goto loop_9;
    }
}

void fn_1_51A8(void) {
    M570Player *temp_r31;
    omObjData *temp_r30;
    s32 var_r28;
    s32 var_r29;

    HuAudFXPlay(0x912);
    var_r29 = 0;
loop_17:
    if (var_r29 < 4) {
        temp_r31 = lbl_1_bss_1C4[var_r29];
        if ((s32) temp_r31->unk48 == 0) {
            CharModelHookDustCreate(temp_r31->unk2, CharModelItemHookGet(temp_r31->unk2, 2, 0));
            if ((M570Player *) lbl_1_bss_1C0 == temp_r31) {
                var_r28 = 0;
            } else if ((s16) lbl_1_bss_1C0->unk4C == (s16) temp_r31->unk4C) {
                var_r28 = 1;
            } else {
                var_r28 = 0;
            }
            if (var_r28 != 0) {
                temp_r31->unk48 = 1;
                temp_r31->unk28 = 5;
                if ((s16) temp_r31->unk36 != 6) {
                    temp_r30 = temp_r31->unk2C;
                    if ((s16) temp_r31->unk36 == 5) {

                    }
                    CharMotionShiftSet(temp_r31->unk2, temp_r30->motion[6], 0.0f, lbl_1_data_37C[6].unk0, lbl_1_data_37C[6].unk4);
                    if ((s32) lbl_1_data_37C[6].unk8 != 0) {
                        Hu3DMotionAttrSet(temp_r30->motion[6], 1U);
                    } else {
                        Hu3DMotionAttrReset(temp_r30->motion[6], 1U);
                    }
                    temp_r31->unk36 = 6;
                }
            } else {
                temp_r31->unk28 = 4;
            }
            temp_r31->unk44 = 0;
        }
        var_r29 += 1;
        goto loop_17;
    }
}

void fn_1_5354(void) {
    M570Player *temp_r30;
    M570Player *temp_r31;
    omObjData *temp_r27;
    omObjData *temp_r28;
    s32 var_r29;

    var_r29 = 0;
loop_15:
    if (var_r29 < 4) {
        if ((s16) lbl_1_bss_52 == (s16) lbl_1_bss_1C4[var_r29]->unk6) {
            temp_r31 = lbl_1_bss_1C4[var_r29];
            if ((s16) temp_r31->unk36 != 8) {
                temp_r28 = temp_r31->unk2C;
                if ((s16) temp_r31->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r31->unk2, temp_r28->motion[8], 0.0f, lbl_1_data_37C[8].unk0, lbl_1_data_37C[8].unk4);
                if ((s32) lbl_1_data_37C[8].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r28->motion[8], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r28->motion[8], 1U);
                }
                temp_r31->unk36 = 8;
            }
        } else {
            temp_r30 = lbl_1_bss_1C4[var_r29];
            if ((s16) temp_r30->unk36 != 9) {
                temp_r27 = temp_r30->unk2C;
                if ((s16) temp_r30->unk36 == 5) {

                }
                CharMotionShiftSet(temp_r30->unk2, temp_r27->motion[9], 0.0f, lbl_1_data_37C[9].unk0, lbl_1_data_37C[9].unk4);
                if ((s32) lbl_1_data_37C[9].unk8 != 0) {
                    Hu3DMotionAttrSet(temp_r27->motion[9], 1U);
                } else {
                    Hu3DMotionAttrReset(temp_r27->motion[9], 1U);
                }
                temp_r30->unk36 = 9;
            }
        }
        var_r29 += 1;
        goto loop_15;
    }
}

s32 fn_1_5538(void) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 >= 3) {
        return 1;
    }
    if ((s32) lbl_1_bss_1B4[var_r31]->unk48 == 0) {
        return 0;
    }
    var_r31 += 1;
    goto loop_4;
}

void fn_1_558C(omObjData *arg0) {
    Vec sp8;
    u32 temp_r0;

    temp_r0 = arg0->work[0];
    switch ((s32) temp_r0) {                        /* irregular */
    case 1:
        arg0->work[1] += 1;
        if ((u32) arg0->work[1] == 0x14) {
            HuAudFXPlay(0x910);
            return;
        }
        return;
    case 2:
        arg0->work[1] += 1;
        if (((u32) arg0->work[1] == (u32) ((arg0->work[2] * 0xF) + 0x19)) && ((u32) arg0->work[2] < 5U)) {
            HuAudFXPlay(0x910);
            arg0->work[2] += 1;
        }
        if ((Hu3DMotionEndCheck(arg0->model[0]) != 0) && (Hu3DMotionShiftIDGet(arg0->model[0]) < 0)) {
            Hu3DModelObjPosGet(arg0->model[0], "itemhook_R", &sp8);
            CharEffectSmokeCreate(1, &sp8);
            Hu3DModelAttrSet(arg0->model[1], 1U);
            fn_1_5820(0);
        }
        break;
    }
}

void fn_1_56A0(void) {
    omObjData *temp_r31;
    s16 temp_r3;
    s16 temp_r3_2;
    s32 var_r29;

    temp_r31 = omAddObjEx(lbl_1_bss_108, 0x1100, 2U, 4U, -1, fn_1_558C);
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M570, 14), MEMORY_DEFAULT_NUM, HEAP_DATA));
    temp_r31->model[0] = temp_r3;
    var_r29 = 0;
loop_2:
    if (var_r29 < 4) {
        temp_r31->motion[var_r29] = Hu3DJointMotion(temp_r3, HuDataSelHeapReadNum(lbl_1_rodata_128[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
        var_r29 += 1;
        goto loop_2;
    }
    Hu3DModelShadowSet(temp_r3);
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DMotionSet(temp_r3, *temp_r31->motion);
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M570, 19), MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelHookSet(temp_r31->model[0], "itemhook_R", temp_r3_2);
    temp_r31->model[1] = temp_r3_2;
    Hu3DModelShadowSet(temp_r3_2);
    omSetTra(temp_r31, 0.0f, 0.0f, -345.0f);
    lbl_1_bss_1B0 = temp_r31;
}

void fn_1_5820(s16 arg0) {
    u32 sp8[4];
    omObjData *temp_r31;

    sp8[0] = lbl_1_rodata_160[0];
    sp8[1] = lbl_1_rodata_160[1];
    sp8[2] = lbl_1_rodata_160[2];
    sp8[3] = lbl_1_rodata_160[3];
    temp_r31 = lbl_1_bss_1B0;
    temp_r31->work[0] = (u32) arg0;
    temp_r31->work[1] = 0;
    Hu3DModelAttrReset(*temp_r31->model, 0x40000001U);
    Hu3DMotionShiftSet(*temp_r31->model, temp_r31->motion[arg0], 0.0f, 10.0f, sp8[arg0]);
}

void fn_1_58EC(omObjData *arg0) {
    f32 temp_f31;
    s16 temp_r29;
    s32 temp_r0;
    M570Fan *temp_r31;

    temp_r31 = arg0->data;
    temp_r29 = *arg0->model;
    temp_r0 = temp_r31->unk10;
    switch (temp_r0) {                              /* irregular */
    case 1:
        temp_r31->unk8 = (s32) (temp_r31->unk8 - 1);
        if ((s32) temp_r31->unk8 <= 0) {
            Hu3DMotionSet(temp_r29, arg0->motion[1]);
            temp_r31->unk10 = 2;
            return;
        }
    case 0:
        return;
    case 2:
        temp_f31 = Hu3DMotionMaxTimeGet(temp_r29) - 1.0f;
        if (Hu3DMotionTimeGet(temp_r29) == temp_f31) {
            temp_r31->unkC = (s32) (temp_r31->unkC - 1);
            if ((s32) temp_r31->unkC == 0) {
                Hu3DMotionSet(temp_r29, arg0->motion[0]);
                Hu3DMotionTimeSet(temp_r29, 0.0f);
                temp_r31->unk10 = 0;
                return;
            }
        }
        break;
    case 3:
        Hu3DModelAttrSet(temp_r29, 0x40000001U);
        Hu3DMotionSet(temp_r29, arg0->motion[0]);
        temp_r31->unk10 = 0;
        return;
    case 4:
        if (Hu3DMotionEndCheck(temp_r29) != 0) {
            Hu3DModelAttrSet(temp_r29, 0x40000001U);
            Hu3DMotionSet(temp_r29, arg0->motion[0]);
            temp_r31->unk10 = 0;
        }
        break;
    }
}

void fn_1_5A78(void) {
    HSFDATA *temp_r25;
    HSFMATERIAL *var_r28;
    omObjData *temp_r31;
    s16 temp_r3;
    s16 var_r30;
    s32 var_r29;
    s32 var_r29_2;
    M570Fan *temp_r26;

    var_r30 = 0;
loop_13:
    if (var_r30 < 0x28) {
        temp_r31 = omAddObjEx(lbl_1_bss_108, (s16) (var_r30 + 0x1200), 1U, 2U, -1, fn_1_58EC);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M570Fan), MEMORY_DEFAULT_NUM);
        memset(temp_r31->data, 0, sizeof(M570Fan));
        temp_r26 = temp_r31->data;
        lbl_1_bss_110[var_r30] = (M570Fan *) temp_r26;
        temp_r26->unk0 = var_r30;
        temp_r26->unk4 = temp_r31;
        temp_r26->unk10 = 0;
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M570, 20), MEMORY_DEFAULT_NUM, HEAP_DATA));
        *temp_r31->model = temp_r3;
        var_r29 = 0;
loop_3:
        if (var_r29 < 2) {
            temp_r31->motion[var_r29] = Hu3DJointMotion(temp_r3, HuDataSelHeapReadNum(lbl_1_rodata_138[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r29 += 1;
            goto loop_3;
        }
        Hu3DMotionSet(temp_r3, temp_r31->motion[1]);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        Hu3DMotionTimeSet(temp_r3, (f32) frandmod((u32) Hu3DMotionMaxTimeGet(temp_r3)));
        omSetTra(temp_r31, lbl_1_data_4C8[var_r30].x, lbl_1_data_4C8[var_r30].y, lbl_1_data_4C8[var_r30].z);
        if (lbl_1_data_4C8[var_r30].x < -500.0f) {
            omSetRot(temp_r31, 0.0f, 90.0f, 0.0f);
        } else if (lbl_1_data_4C8[var_r30].x > 500.0f) {
            omSetRot(temp_r31, 0.0f, -90.0f, 0.0f);
        } else {
            omSetRot(temp_r31, 0.0f, 0.0f, 0.0f);
        }
        temp_r25 = Hu3DData[temp_r3].hsf;
        var_r29_2 = 0;
        var_r28 = temp_r25->material;
loop_11:
        if (var_r29_2 < (s16) temp_r25->materialNum) {
            var_r28->color[0] = 0xB2;
            var_r28->color[1] = 0xB2;
            var_r28->color[2] = 0xB2;
            var_r29_2 += 1;
            var_r28++;
            goto loop_11;
        }
        var_r30 += 1;
        goto loop_13;
    }
}



void fn_1_5E38(void) {
    s16 temp_r30;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x28) {
        lbl_1_bss_110[var_r31]->unk10 = 0;
        temp_r30 = *lbl_1_bss_110[var_r31]->unk4->model;
        Hu3DMotionSet(temp_r30, *lbl_1_bss_110[var_r31]->unk4->motion);
        Hu3DModelAttrSet(temp_r30, 0x40000001U);
        Hu3DMotionTimeSet(temp_r30, (f32) frandmod((u32) Hu3DMotionMaxTimeGet(temp_r30)));
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_5F24(s32 arg0) {
    s32 sp8;
    s32 var_r31;

    sp8 = arg0;
    var_r31 = 0;
loop_2:
    if (var_r31 < 0x28) {
        lbl_1_bss_110[var_r31]->unk10 = 1;
        lbl_1_bss_110[var_r31]->unk8 = frandmod(0x3CU);
        lbl_1_bss_110[var_r31]->unkC = sp8;
        var_r31 += 1;
        goto loop_2;
    }
}
