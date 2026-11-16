// MP5 m524, generated from its m2c draft by tools/mp5/ports/m524Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m524Dll (tools/mp5/decomp.py m524Dll --types tools/mp5/types/m524Dll.h)
// Written from the draft: player / flow / camera works, the camera parameter block and its tables.
// objdata: M524Player
// objdata fn_1_2630 fn_1_28C8 fn_1_29F4 fn_1_23C8: M524Coin
// objdata ObjectSetup fn_1_50B0 fn_1_2FB0 fn_1_30BC fn_1_31EC fn_1_32F0 fn_1_33B4 MgFlowSet MgFlowNext fn_1_5454 fn_1_54CC fn_1_55EC fn_1_56A0 fn_1_5754: M524Flow
// objexpr lbl_1_bss_20: M524Flow
// objexpr lbl_1_bss_1C: M524Player
// objexpr lbl_1_bss_8: M524CamMove
// var fn_1_35A8 temp_r3: M524Camera
// var fn_1_35A8 temp_ret: M524Camera
// var fn_1_23C8 temp_r26: M524Player
// var fn_1_28C8 temp_r27: M524Player
// var fn_1_29F4 temp_r30: M524Player
// var fn_1_2630 temp_r30: M524Player
// var fn_1_4C18 temp_r30: M524Camera
// var fn_1_4898 temp_r28: M524CamMove
// var MgCameraMoveEntry temp_r31: M524CamMove

typedef void (*M524PhaseFunc)(OMOBJ *);

typedef struct M524Light { // lbl_1_data_EC: Hu3DGLightCreateV arguments
    Vec unk0; // pos
    Vec unkC; // dir
    GXColor unk18;
} M524Light;

typedef struct M524Player { // OMOBJ::data, 0x68
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // pad
    s16 unk6; // group
    s16 unk8; // difficulty
    s16 unkA;
    s32 unkC; // com
    f32 unk10, unk14, unk18; // pos
    f32 unk1C, unk20, unk24; // rot
    u32 unk28; // mode
    f32 unk2C; // stick angle
    f32 unk30;
    s32 unk34; // spin direction
    f32 unk38; // crank motion time
    s32 unk3C;
    Vec unk40; // falling object pos
    Vec unk4C; // its velocity
    u16 unk58;
    s16 unk5A; // particle manager
    s32 unk5C; // objects left
    s32 unk60;
    s32 unk64;
} M524Player;

typedef struct M524Coin { // OMOBJ::data of the dropped coins / prize, 0x1C
    s32 unk0;
    f32 unk4, unk8, unkC; // pos
    f32 unk10, unk14, unk18; // velocity
} M524Coin;

typedef struct M524Flow { // the flow object's data, 0x68
    s32 unk0; // phase
    M524PhaseFunc *unk4; // phase table
    s32 unk8; // phase count
    s32 unkC; // message id
    MGTIMER *unk10;
    s32 unk14, unk18, unk1C, unk20; // timer type, max, end, record
    s32 unk24;
    s32 unk28[16];
} M524Flow;

typedef struct M524Camera { // camera parameters, 0x48
    s32 unk0; // camera bit
    s32 unk4; // 1: position from angles
    f32 unk8, unkC, unk10; // fov, near, far
    Vec unk14; // pos
    Vec unk20; // up
    Vec unk2C; // target
    f32 unk38, unk3C, unk40; // angles
    f32 unk44; // distance
} M524Camera;

typedef struct M524CamMove { // camera move object data, 0xA0
    M524Camera *unk0; // camera being moved
    M524Camera unk4; // from
    M524Camera unk4C; // to
    f32 unk94; // frames
    f32 unk98; // time
    s32 unk9C; // flags
} M524CamMove;


M524Camera *fn_1_35A8(M524Camera *arg0);
void fn_1_3694(M524Camera *arg0);
void fn_1_3DD0(M524Camera *arg0);
void fn_1_4494(M524Camera *arg0);
OMOBJ *MgCameraMoveEntry(M524Camera *arg0, M524Camera *arg1, f32 farg0);
void fn_1_2FB0(OMOBJ *arg0);
void fn_1_30BC(OMOBJ *arg0);
void fn_1_31EC(OMOBJ *arg0);
void fn_1_32F0(OMOBJ *arg0);
void fn_1_33B4(OMOBJ *arg0);
void MgFlowSet(OMOBJ *arg0, s32 arg1);
void MgFlowNext(OMOBJ *arg0);
void fn_1_5454(OMOBJ *arg0);
void fn_1_54CC(OMOBJ *arg0);
void fn_1_55EC(OMOBJ *arg0);
void fn_1_56A0(OMOBJ *arg0);
void fn_1_5754(OMOBJ *arg0);
void ObjectSetup(void);
void fn_1_438(void);
void fn_1_478(void);
void fn_1_6D8(void);
void fn_1_848(omObjData *arg0);
void fn_1_AD0(omObjData *arg0);
void fn_1_C24(omObjData *arg0);
void fn_1_D08(omObjData *arg0);
void fn_1_E2C(omObjData *arg0);
void fn_1_F84(omObjData *arg0);
void fn_1_11D4(omObjData *arg0);
void fn_1_161C(omObjData *arg0);
void fn_1_1CBC(omObjData *arg0);
void fn_1_1DF8(omObjData *arg0);
void fn_1_1FB8(omObjData *arg0);
void fn_1_20A0(omObjData *arg0);
void fn_1_21BC(omObjData *arg0);
void fn_1_23C8(omObjData *arg0, Vec *arg1, s32 arg2);
void fn_1_2630(omObjData *arg0);
void fn_1_2760(omObjData *arg0);
void fn_1_27D8(omObjData *arg0);
void fn_1_28C8(omObjData *arg0, Vec *arg1);
void fn_1_29F4(omObjData *arg0);
void fn_1_2D30(omObjData *arg0);
void fn_1_2DB4(omObjData *arg0);
void fn_1_2EEC(omObjData *arg0);
void fn_1_2FB0(omObjData *arg0);
void fn_1_30BC(omObjData *arg0);
void fn_1_31EC(omObjData *arg0);
void fn_1_32F0(omObjData *arg0);
void fn_1_33B4(omObjData *arg0);
M524Camera *fn_1_35A8(M524Camera *arg0);
void fn_1_3694(M524Camera *arg0);
void fn_1_3DD0(M524Camera *arg0);
void fn_1_4898(omObjData *arg0);
OMOBJ *MgCameraMoveEntry(M524Camera *arg0, M524Camera *arg1, f32 farg0);
void fn_1_4C18(omObjData *arg0);
void fn_1_50B0(omObjData *arg0);
void fn_1_5160(omObjData *arg0);
void MgFlowSet(omObjData *arg0, s32 arg1);
void MgFlowNext(omObjData *arg0);
void fn_1_5454(omObjData *arg0);
void fn_1_54CC(omObjData *arg0);
void fn_1_55EC(omObjData *arg0);
void fn_1_56A0(omObjData *arg0);
void fn_1_5754(omObjData *arg0);

M524Light lbl_1_data_EC = {
    { -800.0f, 1500.0f, 800.0f },
    { 800.0f, -1500.0f, -800.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
};
M524Camera lbl_1_data_108 = {
    1,
    1,
    20.0f,
    20.0f,
    7000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.98f, -0.17f },
    { 0.0f, 150.0f, 0.0f },
    -10.0f,
    0.0f,
    0.0f,
    2250.0f,
};
M524Camera lbl_1_data_150 = {
    1,
    1,
    20.0f,
    20.0f,
    7000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 300.0f, 0.0f },
    -0.3f,
    0.0f,
    0.0f,
    2650.0f,
};
M524Camera lbl_1_data_198 = {
    1,
    0,
    20.0f,
    20.0f,
    7000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 500.0f, 0.0f },
    -10.0f,
    0.0f,
    0.0f,
    5000.0f,
};
static Vec lbl_1_data_1E0 = { 0.0f, 0.0f, 300.0f };
void (*lbl_1_data_1EC[0xB])(omObjData *) = {
    fn_1_5454,
    fn_1_2FB0,
    fn_1_55EC,
    fn_1_5754,
    fn_1_30BC,
    fn_1_31EC,
    fn_1_32F0,
    fn_1_56A0,
    fn_1_33B4,
    fn_1_54CC,
    NULL,
};
static f32 lbl_1_data_218[4] = { -300.0f, -100.0f, 100.0f, 300.0f };
static s16 lbl_1_data_228[4] = { 0x28, 0x38, 0x48, 0x58 };
static s16 lbl_1_data_230[4] = { 0x754, 0x755, 0x756, 0x757 };
static s16 lbl_1_data_238[4] = { 0x758, 0x759, 0x75A, 0x75B };
static s16 lbl_1_data_240[4] = { 0x75C, 0x75D, 0x75E, 0x75F };
static s16 lbl_1_data_248[4] = { 0x760, 0x761, 0x762, 0x763 };
static s16 lbl_1_data_250[4] = { 0x764, 0x765, 0x766, 0x767 };
static HU3DPARMANPARAM lbl_1_data_258 = {
    0x32,
    { 0 },
    20.0f,
    100.0f,
    0.0f,
    { 0.0f, 0.0f, 0.0f },
    1.0f,
    0.0f,
    400.0f,
    0.97f,
    1,
    { { 0xFF, 0xFF, 0xFF, 0xFF }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 0xFF, 0xFF, 0xFF, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
};
static u32 lbl_1_data_2A8[0xA] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 13),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 14),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 56),
    DATA_MAKE_NUM(DATADIR_MP5_MARIO, 73),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 27),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 57),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    0,
};
static s32 lbl_1_bss_0;
static s32 lbl_1_bss_4;
omObjData *lbl_1_bss_8;
static s16 lbl_1_bss_C;
static s16 lbl_1_bss_E;
static s16 lbl_1_bss_10[4];
M524Camera *lbl_1_bss_18;
static omObjData **lbl_1_bss_1C;
static omObjData *lbl_1_bss_20;
static s16 lbl_1_bss_24[6];
static s32 lbl_1_bss_30;
static s16 lbl_1_bss_7C;
static HUPROCESS *lbl_1_bss_80;
static s32 lbl_1_rodata_94[5] = { DATA_MAKE_NUM(DATADIR_MP5_M524, 16), DATA_MAKE_NUM(DATADIR_MP5_M524, 0), DATA_MAKE_NUM(DATADIR_MP5_M524, 1), DATA_MAKE_NUM(DATADIR_MP5_M524, 3), DATA_MAKE_NUM(DATADIR_MP5_M524, 2) }; /* const */
static s32 lbl_1_rodata_A8[4] = { DATA_MAKE_NUM(DATADIR_MP5_M524, 6), DATA_MAKE_NUM(DATADIR_MP5_M524, 7), DATA_MAKE_NUM(DATADIR_MP5_M524, 8), DATA_MAKE_NUM(DATADIR_MP5_M524, 9) }; /* const */
static s32 lbl_1_rodata_B8[4] = { DATA_MAKE_NUM(DATADIR_MP5_M524, 10), DATA_MAKE_NUM(DATADIR_MP5_M524, 11), DATA_MAKE_NUM(DATADIR_MP5_M524, 12), DATA_MAKE_NUM(DATADIR_MP5_M524, 13) }; /* const */
s16 lbl_1_rodata_C8[2][4] = { { 0, 1, 2, 3 }, { 0, 0, 2, 3 } }; /* const */
static s16 lbl_1_rodata_D8[4] = { 0, 1, 0xA, 0x14 }; /* const */




void ObjectSetup(void) {
    omObjData *temp_r27;
    omObjData *temp_r3_2;
    s16 temp_r3;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;
    M524Flow *temp_r30;
    M524Flow *temp_r31;

    lbl_1_bss_80 = omInitObjMan(0xC8, 0x1000);
    lbl_1_bss_7C = -1;
    omGameSysInit(lbl_1_bss_80);
    fn_1_438();
    lbl_1_bss_18 = fn_1_35A8(&lbl_1_data_108);
    temp_r3 = Hu3DGLightCreateV(&lbl_1_data_EC.unk0, &lbl_1_data_EC.unkC, &lbl_1_data_EC.unk18);
    Hu3DGLightStaticSet(temp_r3, 1);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DShadowCreate(20.0f, 20.0f, 7000.0f);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_data_EC.unk0, &lbl_1_data_108.unk20, &lbl_1_data_1E0);
    Hu3DShadowSizeSet(0x140U);
    fn_1_478();
    omMakeGroupEx(lbl_1_bss_80, 0U, 4U);
    lbl_1_bss_1C = omGetGroupMemberListEx(lbl_1_bss_80, 0);
    var_r28 = 0;
loop_2:
    if (var_r28 < 4) {
        temp_r3_2 = omAddObjEx(lbl_1_bss_80, 0x2000, 5U, 9U, 0, fn_1_848);
        lbl_1_bss_1C[var_r28] = temp_r3_2;
        temp_r3_2->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x68, MEMORY_DEFAULT_NUM);
        temp_r3_2->work[0] = (u32) var_r28;
        var_r28 += 1;
        goto loop_2;
    }
    var_r26 = 0;
loop_5:
    if (((void (*)(omObjData *)) lbl_1_data_1EC[var_r26]) != NULL) {
        var_r26 += 1;
        goto loop_5;
    }
    temp_r27 = omAddObjEx(lbl_1_bss_80, 0x2000, 0U, 0U, -1, fn_1_50B0);
    temp_r27->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M524Flow), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r27->data;
    temp_r31->unk8 = var_r26;
    temp_r31->unk4 = lbl_1_data_1EC;
    temp_r31->unk0 = 0;
    temp_r31->unkC = -1;
    var_r25 = 0;
loop_8:
    if (var_r25 < 0x10) {
        temp_r31->unk28[var_r25] = 0;
        var_r25 += 1;
        goto loop_8;
    }
    lbl_1_bss_20 = temp_r27;
    temp_r30 = lbl_1_bss_20->data;
    temp_r30->unk14 = 0;
    temp_r30->unk18 = 0x12C;
    temp_r30->unk1C = 0;
    temp_r30->unk20 = 0;
    WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
}

void fn_1_438(void) {
    fn_1_6D8();
    lbl_1_bss_30 = 0;
    lbl_1_bss_C = -1;
}

void fn_1_478(void) {
    s32 var_r31;

    var_r31 = 0;
loop_11:
    if (var_r31 < 5) {
        lbl_1_bss_24[var_r31] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_94[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_24[var_r31], 1U);
        Hu3DModelAttrSet(lbl_1_bss_24[var_r31], 0x40000002U);
        Hu3DModelPosSet(lbl_1_bss_24[var_r31], 0.0f, 0.0f, 0.0f);
        switch (var_r31) {                          /* irregular */
        case 0:
            Hu3DCameraMotionOn(lbl_1_bss_24[var_r31], (u16) lbl_1_data_108.unk0);
            Hu3DModelPosSet(lbl_1_bss_24[var_r31], lbl_1_data_218[1], 0.0f, 200.0f);
            break;
        case 1:
            Hu3DModelShadowMapSet(lbl_1_bss_24[var_r31]);
            break;
        case 4:
            Hu3DModelAttrReset(lbl_1_bss_24[var_r31], 0x40000002U);
            Hu3DModelAttrSet(lbl_1_bss_24[var_r31], 0x40000001U);
            break;
        }
        Hu3DModelRotSet(lbl_1_bss_24[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_24[var_r31], 1U);
        var_r31 += 1;
        goto loop_11;
    }
    lbl_1_bss_E = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M524, 14), MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_E, 1U);
}

void fn_1_6D8(void) {
    s16 temp_r3;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;
    u32 temp_r29;

    temp_r29 = frandmod(2U);
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        lbl_1_bss_10[var_r31] = lbl_1_rodata_C8[temp_r29][var_r31];
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 4) {
        temp_r3 = frandmod(4U);
        M2C_SWAP(lbl_1_bss_10[var_r31_2], lbl_1_bss_10[temp_r3]); /* m2c lost the temporary */
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_8:
    if (var_r31_3 < 4) {
        GWPlayer[var_r31_3].coin_win = lbl_1_rodata_D8[lbl_1_bss_10[var_r31_3]];
        var_r31_3 += 1;
        goto loop_8;
    }
}

void fn_1_848(omObjData *arg0) {
    s16 temp_r28;
    u32 temp_r0;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = arg0->work[0];
    temp_r31->unk0 = (s16) temp_r0;
    temp_r31->unk2 = (s16) GWPlayerCfg[(s16) temp_r0].character;
    temp_r31->unk4 = (s16) GWPlayerCfg[(s16) temp_r0].pad_idx;
    temp_r31->unk6 = (s16) GWPlayerCfg[(s16) temp_r0].group;
    temp_r31->unkC = (s32) GWPlayerCfg[(s16) temp_r0].iscom;
    temp_r31->unk8 = (s16) GWPlayerCfg[(s16) temp_r0].diff;
    temp_r31->unk28 = 0;
    temp_r31->unk18 = 0.0f;
    temp_r31->unk14 = 0.0f;
    temp_r31->unk10 = 0.0f;
    temp_r31->unk24 = 0.0f;
    temp_r31->unk20 = 0.0f;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk38 = 0.0f;
    temp_r31->unk34 = 0;
    temp_r31->unk3C = 0;
    temp_r31->unk60 = 0;
    temp_r31->unk64 = 0;
    temp_r31->unk5C = -1;
    temp_r28 = temp_r31->unk2;
    *arg0->model = CharModelMotListCreate(temp_r28, 2, lbl_1_data_2A8, arg0->motion);
    Hu3DModelShadowSet(*arg0->model);
    CharModelAttrSet(temp_r28, 0x40000001U);
    CharMotionSet(temp_r28, *arg0->motion);
    CharEffectLayerSet(2);
    temp_r31->unk10 = (f32) (lbl_1_data_218[temp_r31->unk0] - 70.0f);
    temp_r31->unk14 = 0.0f;
    temp_r31->unk18 = 320.0f;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk20 = 90.0f;
    temp_r31->unk24 = 0.0f;
    omSetTra(arg0, temp_r31->unk10, temp_r31->unk14, temp_r31->unk18);
    omSetRot(arg0, temp_r31->unk1C, temp_r31->unk20, temp_r31->unk24);
    fn_1_AD0(arg0);
    fn_1_C24(arg0);
    fn_1_D08(arg0);
    CharModelVoicePanSet(temp_r31->unk2, lbl_1_data_228[temp_r31->unk0]);
    arg0->work[0] = 0;
    arg0->func = fn_1_E2C;
}

void fn_1_AD0(omObjData *arg0) {
    s16 temp_r3;
    s16 temp_r3_2;
    M524Player *temp_r29;

    temp_r29 = arg0->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M524, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[1] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000002U);
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DModelPosSet(temp_r3, lbl_1_data_218[temp_r29->unk0], 0.0f, 200.0f);
    Hu3DMotionStartEndSet(temp_r3, 0.0f, 60.0f);
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M524, 5), MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[2] = temp_r3_2;
    Hu3DModelAttrSet(temp_r3_2, 0x40000002U);
    Hu3DModelPosSet(temp_r3_2, lbl_1_data_218[temp_r29->unk0] - 6.0f, 75.0f, 238.0f);
}

void fn_1_C24(omObjData *arg0) {
    s16 temp_r3;
    M524Player *temp_r30;

    temp_r30 = arg0->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_B8[lbl_1_bss_10[temp_r30->unk0]], MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[3] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000002U);
    Hu3DModelAttrSet(temp_r3, 1U);
    Hu3DModelPosSet(temp_r3, lbl_1_data_218[temp_r30->unk0], 0.0f, 200.0f);
}

void fn_1_D08(omObjData *arg0) {
    s16 temp_r3;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_A8[lbl_1_bss_10[temp_r31->unk0]], MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->model[4] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000002U);
    Hu3DModelAttrSet(temp_r3, 1U);
    temp_r31->unk40.x = (f32) lbl_1_data_218[temp_r31->unk0];
    temp_r31->unk40.y = 1000.0f;
    temp_r31->unk40.z = -400.0f;
    temp_r31->unk4C.x = 0.0f;
    temp_r31->unk4C.y = -40.0f;
    temp_r31->unk4C.z = 0.0f;
    Hu3DModelPosSetV(temp_r3, &temp_r31->unk40);
}

void fn_1_E2C(omObjData *arg0) {
    s32 spC;
    M524Flow *sp8;
    s32 var_r28;
    u32 temp_r0;
    M524Player *temp_r30;

    temp_r30 = arg0->data;
    spC = (s32) temp_r30->unk0;
    temp_r0 = temp_r30->unk28;
    switch (temp_r0) {
    case 0:
        fn_1_F84(arg0);
        return;
    case 1:
        sp8 = lbl_1_bss_20->data;
        if ((s32) ((M524Flow *)lbl_1_bss_20->data)->unk0 == 3) {
            var_r28 = 1;
        } else {
            var_r28 = 0;
        }
        if (var_r28 != 0) {
            temp_r30->unk28 = 2U;
            return;
        }
    default:
        return;
    case 2:
        fn_1_11D4(arg0);
        if ((s32) temp_r30->unk28 != 2) {
            arg0->work[0] = 0;
            arg0->work[1] = -1U;
            return;
        }
        break;
    case 3:
        fn_1_161C(arg0);
        if ((s32) temp_r30->unk28 != 3) {
            arg0->work[0] = 0;
            return;
        }
        break;
    case 4:
        fn_1_1CBC(arg0);
        return;
    case 5:
        fn_1_1DF8(arg0);
        return;
    case 6:
        fn_1_1FB8(arg0);
        return;
    case 7:
        fn_1_20A0(arg0);
        return;
    case 8:
        fn_1_21BC(arg0);
        return;
    case 9:
        fn_1_2D30(arg0);
        return;
    case 10:
        fn_1_2DB4(arg0);
        return;
    case 11:
        fn_1_2EEC(arg0);
        break;
    }
}

void fn_1_F84(omObjData *arg0) {
    M524Flow *sp8;
    s32 var_r28;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    if ((u32) arg0->work[0] == 0) {
        sp8 = lbl_1_bss_20->data;
        if ((s32) ((M524Flow *)lbl_1_bss_20->data)->unk0 == 2) {
            var_r28 = 1;
        } else {
            var_r28 = 0;
        }
        if (var_r28 != 0) {
            Hu3DModelAttrReset(arg0->model[1], 0x40000002U);
            CharModelAttrReset(temp_r31->unk2, 0x40000001U);
            CharMotionSet(temp_r31->unk2, arg0->motion[2]);
            CharMotionStartEndSet(temp_r31->unk2, 61.0f, 120.0f);
            CharMotionTimeSet(temp_r31->unk2, 61.0f);
            CharMotionShiftSet(temp_r31->unk2, arg0->motion[1], 0.0f, 60.0f, 0x40000001U);
            goto block_6;
        }
    } else {
block_6:
        arg0->work[0] += 1;
        temp_r31->unk20 = (f32) (temp_r31->unk20 + 1.5f);
        temp_r31->unk10 = (f32) ((1.1666666f * (f32) arg0->work[0]) + (lbl_1_data_218[temp_r31->unk0] - 70.0f));
        omSetTra(arg0, temp_r31->unk10, temp_r31->unk14, temp_r31->unk18);
        omSetRot(arg0, temp_r31->unk1C, temp_r31->unk20, temp_r31->unk24);
        if ((u32) arg0->work[0] == 0x3C) {
            temp_r31->unk10 = (f32) lbl_1_data_218[temp_r31->unk0];
            omSetTra(arg0, temp_r31->unk10, temp_r31->unk14, temp_r31->unk18);
            CharModelAttrSet(temp_r31->unk2, 0x40000002U);
            CharMotionShiftSet(temp_r31->unk2, arg0->motion[4], 0.0f, 15.0f, 0x40000002U);
            arg0->work[0] = 0;
            temp_r31->unk28 = 1;
        }
    }
}

void fn_1_11D4(omObjData *arg0) {
    s32 spC;
    f32 sp8;
    f32 temp_f27;
    f32 var_f28;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r26;
    s16 temp_r29;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    spC = (s32) temp_r31->unk0;
    if (MgTimerDoneCheck(((M524Flow *)lbl_1_bss_20->data)->unk10) != 0) {
        temp_r31->unk28 = 4;
        return;
    }
    if ((s32) temp_r31->unkC != 0) {
        if ((u32) arg0->work[0] == 0) {
            arg0->work[0] = 1;
            arg0->work[1] = frandmod(0x14U) * 5;
        }
        if ((u32) arg0->work[1] == 0) {
            temp_r31->unk2C = 0.0f;
            arg0->work[0] = 0;
            temp_r31->unk28 = 3;
        }
        arg0->work[1] -= 1;
        return;
    }
    temp_r29 = temp_r31->unk4;
    temp_f27 = (f32) (((s8) (u8) HuPadStkX[temp_r29] * (s8) (u8) HuPadStkX[temp_r29]) + ((s8) (u8) HuPadStkY[temp_r29] * (s8) (u8) HuPadStkY[temp_r29]));
    var_f28 = sqrtf(temp_f27);
    if (var_f28 >= 50.0f) {
        temp_r26 = temp_r31->unk4;
        var_f29 = (f32) ((180.0 * (atan2((f64) (f32) (s8) (u8) HuPadStkY[temp_r26], (f64) (f32) (s8) (u8) HuPadStkX[temp_r26]) / 3.141592653589793)) - 90.0);
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        temp_r31->unk2C = var_f29;
        temp_r31->unk28 = 3;
    }
}


void fn_1_161C(omObjData *arg0) {
    f64 sp18;
    f64 sp10;
    s32 spC;
    f32 sp8;
    f32 temp_f1;
    f32 temp_f21;
    f32 var_f22;
    f32 var_f23;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f30;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r29;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    spC = (s32) temp_r31->unk0;
    temp_r29 = temp_r31->unk4;
    if (MgTimerDoneCheck(((M524Flow *)lbl_1_bss_20->data)->unk10) != 0) {
        temp_r31->unk28 = 4;
        return;
    }
    if ((s32) temp_r31->unkC != 0) {
        var_f23 = 20.0f;
        temp_r31->unk30 = (f32) (temp_r31->unk2C + ((f32) frandmod(0x96U) / 10.0f));
    } else {
        temp_f21 = (f32) (((s8) (u8) HuPadStkX[temp_r29] * (s8) (u8) HuPadStkX[temp_r29]) + ((s8) (u8) HuPadStkY[temp_r29] * (s8) (u8) HuPadStkY[temp_r29]));
        var_f22 = sqrtf(temp_f21);
        var_f23 = var_f22;
        var_f27 = (f32) ((180.0 * (atan2((f64) (f32) (s8) (u8) HuPadStkY[temp_r29], (f64) (f32) (s8) (u8) HuPadStkX[temp_r29]) / 3.141592653589793)) - 90.0);
        if (var_f27 < 0.0f) {
            var_f27 += 360.0f;
        }
        temp_r31->unk30 = var_f27;
    }
    if (var_f23 < 10.0f) {
        temp_r31->unk28 = 2;
        return;
    }
    var_f25 = temp_r31->unk30;
    var_f26 = temp_r31->unk2C;
    if (var_f25 > 180.0f) {
        var_f25 -= 360.0f;
    }
    if (var_f26 > 180.0f) {
        var_f26 -= 360.0f;
    }
    var_f30 = var_f25 - var_f26;
    if (var_f30 > 180.0f) {
        var_f30 -= 360.0f;
    }
    if (var_f30 < -180.0f) {
        var_f30 += 360.0f;
    }
    temp_r31->unk2C = (f32) temp_r31->unk30;
    if ((s32) temp_r31->unk34 == 0) {
        sp18 = fabs(var_f30);
        if (!((f32) sp18 < 10.0f)) {
            if (var_f30 < 0.0f) {
                temp_r31->unk34 = -1;
                temp_r31->unk38 = CharMotionMaxTimeGet(temp_r31->unk2);
            } else {
                temp_r31->unk34 = 1;
            }
            goto block_26;
        }
    } else if (!(((f32) temp_r31->unk34 * var_f30) <= 0.0f)) {
block_26:
        sp10 = fabs(var_f30);
        if (!((f32) sp10 >= 50.0f)) {
            temp_f1 = CharMotionMaxTimeGet(temp_r31->unk2);
            temp_r31->unk38 = (f32) (temp_r31->unk38 + (var_f30 / (360.0f / temp_f1)));
            if ((u32) (arg0->work[1] + 0x10000) == -1U) {
                arg0->work[1] = HuAudFXPlay((s32) lbl_1_data_230[temp_r31->unk0]);
            } else if (HuAudFXStatusGet((s32) arg0->work[1]) == 0) {
                arg0->work[1] = -1U;
            }
            if ((((s32) temp_r31->unk34 == 1) && (temp_r31->unk38 >= temp_f1)) || (((s32) temp_r31->unk34 == -1) && (temp_r31->unk38 <= 0.0f))) {
                temp_r31->unk38 = 0.0f;
                CharMotionTimeSet(temp_r31->unk2, temp_f1);
                Hu3DMotionTimeSet(arg0->model[2], 60.0f);
                Hu3DModelAttrReset(arg0->model[1], 0x40000001U);
                temp_r31->unk28 = 5;
                return;
            }
            CharMotionTimeSet(temp_r31->unk2, temp_r31->unk38);
            Hu3DMotionTimeSet(arg0->model[2], temp_r31->unk38);
        }
    }
}

void fn_1_1CBC(omObjData *arg0) {
    M524Player *temp_r30;

    temp_r30 = arg0->data;
    if ((u32) arg0->work[0] == 0) {
        CharModelAttrReset(temp_r30->unk2, 0x40000002U);
        Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
        Hu3DModelAttrReset(arg0->model[1], 0x40000001U);
        if ((s32) temp_r30->unk34 == -1) {
            CharModelAttrSet(temp_r30->unk2, 0x40000004U);
            Hu3DModelAttrSet(arg0->model[2], 0x40000004U);
        }
        arg0->work[0] = 1;
        arg0->work[2] = 0;
    }
    if (((u32) (arg0->work[1] + 0x10000) != -1U) && (HuAudFXStatusGet((s32) arg0->work[1]) == 0)) {
        arg0->work[1] = -1U;
    }
    if ((u32) (arg0->work[1] + 0x10000) == -1U) {
        arg0->work[1] = HuAudFXPlay((s32) lbl_1_data_230[temp_r30->unk0]);
    }
    if (CharMotionEndCheck(temp_r30->unk2) != 0) {
        arg0->work[0] = 0;
        temp_r30->unk28 = 5;
    }
    arg0->work[2] += 1;
}

void fn_1_1DF8(omObjData *arg0) {
    u32 temp_r0;
    M524Player *temp_r30;

    temp_r30 = arg0->data;
    temp_r0 = arg0->work[0];
    switch ((s32) temp_r0) {                        /* irregular */
    case 0:
        Hu3DMotionStartEndSet(arg0->model[1], 60.0f, 100.0f);
        Hu3DMotionTimeSet(arg0->model[1], 60.0f);
        Hu3DModelAttrReset(arg0->model[3], 1U);
        Hu3DModelAttrReset(arg0->model[3], 0x40000002U);
        arg0->work[0] = 1;
        arg0->work[1] = 0x37;
        return;
    case 1:
        if ((u32) arg0->work[1] != 0) {
            arg0->work[1] -= 1;
            if ((u32) arg0->work[1] == 0xD) {
                HuAudFXPlay((s32) lbl_1_data_238[temp_r30->unk0]);
            }
            if ((u32) arg0->work[1] == 0) {
                CharMotionShiftSet(temp_r30->unk2, arg0->motion[5], 0.0f, 30.0f, 0U);
                arg0->work[0] = 2;
                arg0->work[1] = 0x3C;
                return;
            }
        } else {
            return;
        }
        break;
    case 2:
        arg0->work[1] -= 1;
        if ((u32) arg0->work[1] == 0) {
            CharMotionShiftSet(temp_r30->unk2, arg0->motion[0], 0.0f, 20.0f, 0x40000001U);
            temp_r30->unk3C = 1;
            arg0->work[1] = 0;
            arg0->work[0] = 0;
            temp_r30->unk28 = 6;
        }
        break;
    }
}

void fn_1_1FB8(omObjData *arg0) {
    M524Flow *sp8;
    s32 var_r28;
    M524Player *temp_r30;

    temp_r30 = arg0->data;
    sp8 = lbl_1_bss_20->data;
    if ((s32) ((M524Flow *)lbl_1_bss_20->data)->unk0 == 6) {
        var_r28 = 1;
    } else {
        var_r28 = 0;
    }
    if (var_r28 != 0) {
        if ((u32) arg0->work[0] == 0) {
            arg0->work[0] = 1;
            arg0->work[1] = temp_r30->unk0 * 0x28;
        }
        if ((u32) arg0->work[1] == 0) {
            arg0->work[0] = 0;
            HuAudFXPlay((s32) lbl_1_data_240[temp_r30->unk0]);
            Hu3DModelAttrReset(arg0->model[4], 1U);
            temp_r30->unk28 = 7;
            return;
        }
        arg0->work[1] -= 1;
    }
}

void fn_1_20A0(omObjData *arg0) {
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    if (Hu3DMotionEndCheck(arg0->model[4]) != 0) {
        temp_r31->unk28 = 8;
        return;
    }
    if (!(Hu3DMotionTimeGet(arg0->model[4]) > 60.0f)) {
        if ((temp_r31->unk40.y <= 760.0f) && (temp_r31->unk4C.z == 0.0f)) {
            temp_r31->unk40.y = 760.0f;
            temp_r31->unk4C.y = -5.2f;
            temp_r31->unk4C.z = 12.333333f;
            Hu3DModelAttrReset(arg0->model[4], 0x40000002U);
        }
        temp_r31->unk40.y = (f32) (temp_r31->unk40.y + temp_r31->unk4C.y);
        temp_r31->unk40.z = (f32) (temp_r31->unk40.z + temp_r31->unk4C.z);
        Hu3DModelPosSetV(arg0->model[4], &temp_r31->unk40);
    }
}

void fn_1_21BC(omObjData *arg0) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    s16 temp_r0;
    s16 temp_r3;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    sp8 = temp_r31->unk40.x;
    spC = temp_r31->unk40.y;
    sp10 = 150.0f + temp_r31->unk40.z;
    temp_r3 = Hu3DParManCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_EFFECT, 2), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x64, &lbl_1_data_258);
    Hu3DParManRotSet(temp_r3, 0.0f, 0.0f, 0.0f);
    Hu3DParManPosSet(temp_r3, sp8, spC, sp10);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(temp_r3), 2);
    temp_r31->unk5A = temp_r3;
    Hu3DParManTimeLimitSet(temp_r31->unk5A, 1);
    Hu3DModelKill(arg0->model[4]);
    HuAudFXPlay((s32) lbl_1_data_248[temp_r31->unk0]);
    temp_r0 = lbl_1_bss_10[temp_r31->unk0];
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->unk5C = 1;
        fn_1_28C8(arg0, &temp_r31->unk40);
        break;
    case 1:
        temp_r31->unk5C = 1;
        fn_1_23C8(arg0, &temp_r31->unk40, temp_r31->unk5C);
        break;
    case 2:
        temp_r31->unk5C = 0xA;
        fn_1_23C8(arg0, &temp_r31->unk40, temp_r31->unk5C);
        break;
    case 3:
        temp_r31->unk5C = 0x14;
        fn_1_23C8(arg0, &temp_r31->unk40, temp_r31->unk5C);
        break;
    }
    CharMotionShiftSet(temp_r31->unk2, arg0->motion[6], 0.0f, 10.0f, 0U);
    temp_r31->unk58 = 0xA;
    temp_r31->unk28 = 9;
}

void fn_1_23C8(omObjData *arg0, Vec *arg1, s32 arg2) {
    s32 sp8;
    omObjData *temp_r30;
    s16 temp_r3;
    s32 var_r28;
    M524Player *temp_r26;
    M524Coin *temp_r31;

    sp8 = arg2;
    temp_r26 = arg0->data;
    var_r28 = 0;
loop_2:
    if (var_r28 < sp8) {
        temp_r30 = omAddObjEx(lbl_1_bss_80, 0x2000, 1U, 0U, -1, fn_1_2760);
        temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M524Coin), MEMORY_DEFAULT_NUM);
        temp_r30->work[0] = (u32) temp_r26->unk0;
        temp_r30->work[1] = (u32) var_r28;
        temp_r30->work[2] = var_r28 * 3;
        temp_r31 = temp_r30->data;
        temp_r3 = Hu3DModelLink(lbl_1_bss_E);
        *temp_r30->model = temp_r3;
        temp_r31->unk4 = (f32) ((arg1->x + (f32) frandmod(0x50U)) - 40.0f);
        temp_r31->unk8 = (f32) ((arg1->y + (f32) frandmod(0xC8U)) - 100.0f);
        temp_r31->unkC = (f32) ((arg1->z + (f32) frandmod(0x64U)) - 50.0f);
        temp_r31->unk10 = 0.0f;
        temp_r31->unk14 = 0.0f;
        temp_r31->unk18 = 0.0f;
        omSetTra(temp_r30, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
        omSetSca(temp_r30, 1.0f, 1.0f, 1.0f);
        Hu3DMotionTimeSet(temp_r3, (f32) frandmod(0x3AU));
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        Hu3DModelAttrReset(temp_r3, 1U);
        Hu3DModelShadowSet(temp_r3);
        var_r28 += 1;
        goto loop_2;
    }
}

void fn_1_2630(omObjData *arg0) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    M524Player *temp_r30;
    M524Coin *temp_r31;

    temp_r31 = arg0->data;
    if ((u32) arg0->work[2] != 0) {
        arg0->work[2] -= 1;
        return;
    }
    temp_r30 = lbl_1_bss_1C[arg0->work[0]]->data;
    temp_r31->unk14 = (f32) (temp_r31->unk14 + 1.96f);
    temp_r31->unk8 = (f32) (temp_r31->unk8 - temp_r31->unk14);
    omSetTra(arg0, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
    if (temp_r31->unk8 <= CharModelHeightGet(temp_r30->unk2)) {
        sp8 = temp_r30->unk10;
        spC = temp_r31->unk8;
        sp10 = temp_r30->unk18;
        HuAudFXPlayPan(7, lbl_1_data_228[temp_r30->unk0]);
        CharEffectCoinGlowCreate((s16) lbl_1_data_108.unk0, (Vec *) &sp8);
        temp_r30->unk5C = (s32) (temp_r30->unk5C - 1);
        arg0->func = fn_1_27D8;
    }
}

void fn_1_2760(omObjData *arg0) {
    M524Player *temp_r31;

    temp_r31 = lbl_1_bss_1C[arg0->work[0]]->data;
    if ((u16) temp_r31->unk58 == 0) {
        if ((s16) lbl_1_bss_10[temp_r31->unk0] == 0) {
            arg0->func = fn_1_29F4;
            return;
        }
        arg0->func = fn_1_2630;
    }
}

void fn_1_27D8(omObjData *arg0) {
    if ((s16) lbl_1_bss_10[((M524Player *)lbl_1_bss_1C[arg0->work[0]]->data)->unk0] != 0) {
        Hu3DModelKill(*arg0->model);
        omDelObjEx(lbl_1_bss_80, arg0);
        return;
    }
    if ((u32) arg0->work[1] != 0) {
        arg0->work[1] -= 1;
        if ((u32) arg0->work[1] == 0) {
            Hu3DMotionTimeSet(*arg0->model, (f32) (frandmod(0x96U) + 0x32));
        }
    }
}

void fn_1_28C8(omObjData *arg0, Vec *arg1) {
    omObjData *temp_r30;
    s16 temp_r28;
    M524Player *temp_r27;
    M524Coin *temp_r31;

    temp_r27 = arg0->data;
    temp_r28 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M524, 15), MEMORY_DEFAULT_NUM, HEAP_DATA));
    temp_r30 = omAddObjEx(lbl_1_bss_80, 0x2000, 1U, 0U, -1, fn_1_2760);
    temp_r30->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M524Coin), MEMORY_DEFAULT_NUM);
    temp_r30->work[0] = (u32) temp_r27->unk0;
    temp_r31 = temp_r30->data;
    *temp_r30->model = temp_r28;
    Hu3DModelAttrSet(temp_r28, 0x40000002U);
    Hu3DModelShadowSet(temp_r28);
    temp_r31->unk4 = (f32) arg1->x;
    temp_r31->unk8 = (f32) (arg1->y - 100.0f);
    temp_r31->unkC = (f32) arg1->z;
    temp_r31->unk10 = 0.0f;
    temp_r31->unk14 = 0.0f;
    temp_r31->unk18 = 0.0f;
    omSetTra(temp_r30, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
}

void fn_1_29F4(omObjData *arg0) {
    M524Camera *temp_r26;
    omObjData *temp_r27;
    omObjData *temp_r28;
    u32 temp_r0;
    M524Player *temp_r30;
    M524Coin *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = arg0->work[0];
    temp_r28 = lbl_1_bss_1C[(s16) temp_r0];
    temp_r30 = lbl_1_bss_1C[(s16) temp_r0]->data;
    temp_r31->unk14 = (f32) (temp_r31->unk14 + 1.96f);
    temp_r31->unk8 = (f32) (temp_r31->unk8 - temp_r31->unk14);
    omSetTra(arg0, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
    if ((temp_r31->unk8 < CharModelHeightGet(temp_r30->unk2)) && ((s32) temp_r30->unk60 == 0)) {
        CharModelAttrReset(temp_r30->unk2, 0x40000002U);
        CharMotionShiftSet(temp_r30->unk2, temp_r28->motion[7], 0.0f, 5.0f, 0U);
        Hu3DMotionShiftStartEndSet(temp_r28->model[0], 0.0f, 30.0f);
        Hu3DModelAttrReset(temp_r28->model[1], 0x40000002U);
        Hu3DModelAttrReset(temp_r28->model[1], 0x40000001U);
        Hu3DMotionStartEndSet(temp_r28->model[1], 101.0f, 105.0f);
        Hu3DMotionTimeSet(temp_r28->model[1], 101.0f);
        temp_r30->unk60 = 1;
    }
    omSetTra(arg0, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
    if (temp_r31->unk8 <= 0.0f) {
        temp_r31->unk8 = 0.0f;
        omSetTra(arg0, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
        temp_r30->unk5C = (s32) (temp_r30->unk5C - 1);
        Hu3DModelAttrReset(*arg0->model, 0x40000002U);
        Hu3DModelAttrSet(*arg0->model, 0x40000001U);
        temp_r31->unkC = (f32) (temp_r31->unkC + 150.0f);
        CharEffectSmokeCreate((s16) lbl_1_data_108.unk0, &temp_r31->unk4);
        temp_r26 = lbl_1_bss_18;
        temp_r27 = omAddObjEx(lbl_1_bss_80, 0x2000, 0U, 0U, -1, fn_1_4C18);
        temp_r27->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x48, MEMORY_DEFAULT_NUM);
        temp_r27->work[0] = 0xF;
        temp_r27->work[1] = 5;
        *(M524Camera *)temp_r27->data = *temp_r26;
        omVibrate(temp_r30->unk0, 0xF, 0xC, 0);
        HuAudFXPlayPan(0x2C1, lbl_1_data_228[temp_r30->unk0]);
        HuAudFXPlay((s32) lbl_1_data_250[temp_r30->unk0]);
        arg0->work[1] = 0x32;
        arg0->func = fn_1_27D8;
    }
}

void fn_1_2D30(omObjData *arg0) {
    s32 var_r30;
    M524Player *temp_r31;
    M524Player *temp_r31_2;

    temp_r31 = arg0->data;
    if ((u16) temp_r31->unk58 != 0) {
        temp_r31->unk58 = (u16) (temp_r31->unk58 - 1);
    }
    var_r30 = 0;
loop_5:
    if (var_r30 >= 4) {
        temp_r31_2 = arg0->data;
        temp_r31_2->unk64 = 1;
        temp_r31_2->unk28 = 0xA;
    } else if ((s32) ((M524Player *)lbl_1_bss_1C[var_r30]->data)->unk5C == 0) {
        var_r30 += 1;
        goto loop_5;
    }
}

void fn_1_2DB4(omObjData *arg0) {
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    if ((s16) lbl_1_bss_10[temp_r31->unk0] != 0) {
        if ((u32) arg0->work[0] == 0) {
            arg0->work[0] = 1;
            CharModelAttrReset(temp_r31->unk2, 0x40000002U);
            CharMotionShiftSet(temp_r31->unk2, arg0->motion[3], 1.0f, 20.0f, 0U);
            Hu3DMotionShiftStartEndSet(*arg0->model, 1.0f, 60.0f);
            return;
        }
        temp_r31->unk20 = (f32) (temp_r31->unk20 - 3.0f);
        omSetRot(arg0, temp_r31->unk1C, temp_r31->unk20, temp_r31->unk24);
        if ((CharMotionShiftIDGet(temp_r31->unk2) == -1) && (CharMotionEndCheck(temp_r31->unk2) != 0)) {
            arg0->work[0] = 0;
            temp_r31->unk28 = 0xB;
        }
    } else {
        temp_r31->unk28 = 0xB;
    }
}

void fn_1_2EEC(omObjData *arg0) {
    M524Flow *sp8;
    s32 var_r28;
    M524Player *temp_r31;

    temp_r31 = arg0->data;
    sp8 = lbl_1_bss_20->data;
    if ((s32) ((M524Flow *)lbl_1_bss_20->data)->unk0 == 8) {
        var_r28 = 1;
    } else {
        var_r28 = 0;
    }
    if (var_r28 != 0) {
        if ((s16) lbl_1_bss_10[temp_r31->unk0] != 0) {
            CharMotionShiftSet(temp_r31->unk2, arg0->motion[8], 0.0f, 20.0f, 0U);
        }
        temp_r31->unk28 = 0xC;
    }
}

void fn_1_2FB0(omObjData *arg0) {
    s32 temp_r4;
    M524Flow *temp_r31;

    if ((s32) lbl_1_bss_0 == 0) {
        Hu3DCameraMotionStart(*lbl_1_bss_24, (u16) lbl_1_data_108.unk0);
        Hu3DModelAttrReset(*lbl_1_bss_24, 0x40000002U);
        lbl_1_bss_7C = HuAudSStreamPlay(0x12);
        HuAudFXPlay(0x753);
        lbl_1_bss_0 = 1;
    }
    if (Hu3DMotionEndCheck(*lbl_1_bss_24) != 0) {
        Hu3DModelKill(*lbl_1_bss_24);
        temp_r31 = arg0->data;
        temp_r4 = temp_r31->unk0;
        if (temp_r4 == (s32) (temp_r31->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
    }
}

void fn_1_30BC(omObjData *arg0) {
    s32 temp_r4;
    s32 var_r31;
    s32 var_r31_2;
    M524Flow *temp_r29;
    M524Flow *temp_r30;

    if ((s32) lbl_1_bss_4 == 0) {
        var_r31 = 0;
loop_4:
        if (var_r31 < 4) {
            if ((s32) ((M524Player *)lbl_1_bss_1C[var_r31]->data)->unk28 >= 5) {
                var_r31 += 1;
                goto loop_4;
            }
        }
        if (var_r31 == 4) {
            temp_r30 = arg0->data;
            if ((s32) temp_r30->unk10->stopF == 0) {
                temp_r30->unk10->stopF = 1;
                temp_r30->unk10->mode = 1;
            }
            lbl_1_bss_4 = 1;
        }
    }
    var_r31_2 = 0;
loop_12:
    if (var_r31_2 >= 4) {
        temp_r29 = arg0->data;
        temp_r4 = temp_r29->unk0;
        if (temp_r4 == (s32) (temp_r29->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r29->unk0 = (s32) (temp_r29->unk0 + 1);
    } else if ((s32) ((M524Player *)lbl_1_bss_1C[var_r31_2]->data)->unk3C != 0) {
        var_r31_2 += 1;
        goto loop_12;
    }
}

void fn_1_31EC(omObjData *arg0) {
    s32 temp_r4;
    s32 var_r30;
    M524Flow *temp_r31;

    if ((omObjData *) lbl_1_bss_8 == NULL) {
        lbl_1_bss_8 = MgCameraMoveEntry(lbl_1_bss_18, &lbl_1_data_150, 30.0f);
    }
    if ((s32) (((M524CamMove *)lbl_1_bss_8->data)->unk9C & 2) != 0) {
        var_r30 = 1;
    } else {
        var_r30 = 0;
    }
    if (var_r30 == 0) {
        omDelObjEx(lbl_1_bss_80, lbl_1_bss_8);
        temp_r31 = arg0->data;
        temp_r4 = temp_r31->unk0;
        if (temp_r4 == (s32) (temp_r31->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
    }
}

void fn_1_32F0(omObjData *arg0) {
    s32 temp_r4;
    s32 var_r30;
    M524Flow *temp_r31;

    var_r30 = 0;
loop_3:
    if (var_r30 >= 4) {
        HuAudSStreamFadeOut((s32) lbl_1_bss_7C, 0x64);
        temp_r31 = arg0->data;
        temp_r4 = temp_r31->unk0;
        if (temp_r4 == (s32) (temp_r31->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
    } else if ((s32) ((M524Player *)lbl_1_bss_1C[var_r30]->data)->unk64 != 0) {
        var_r30 += 1;
        goto loop_3;
    }
}

void fn_1_33B4(omObjData *arg0) {
    f32 temp_f1;
    s32 temp_r4;
    M524Flow *temp_r30;

    if ((u32) arg0->work[0] == 0) {
        arg0->work[0] = 1;
        arg0->work[1] = 0xD2;
        lbl_1_bss_C = HuAudJinglePlay(0x79);
    }
    arg0->work[1] -= 1;
    if ((u32) arg0->work[1] == 0) {
        Mp5WipeWhite(2, 0x3C);
        lbl_1_bss_18->unk4 = 0;
        lbl_1_data_198 = *lbl_1_bss_18;
        fn_1_3DD0(&lbl_1_data_198);
        lbl_1_data_198.unk14.z += 1000.0f;
        lbl_1_data_198.unk2C.y += 400.0f;
        lbl_1_data_198.unk14.y -= 200.0f;
        MgCameraMoveEntry(lbl_1_bss_18, &lbl_1_data_198, 120.0f);
        temp_r30 = arg0->data;
        temp_r4 = temp_r30->unk0;
        if (temp_r4 == (s32) (temp_r30->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4, temp_f1);
            return;
        }
        temp_r30->unk0 = (s32) (temp_r30->unk0 + 1);
    }
}


M524Camera *fn_1_35A8(M524Camera *arg0) {
    M524Camera *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M524Camera), MEMORY_DEFAULT_NUM);
    *temp_r3 = *arg0;
    Hu3DCameraCreate(arg0->unk0);
    Hu3DCameraViewportSet(arg0->unk0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(arg0->unk0, arg0->unk8, arg0->unkC, arg0->unk10, 1.2f);
    fn_1_3694(arg0);
    return (M524Camera *) temp_r3;
}

void fn_1_3694(M524Camera *arg0) {
    if ((s32) arg0->unk4 == 1) {
        fn_1_3DD0(arg0);
    }
    Hu3DCameraPosSetV(arg0->unk0, &arg0->unk14, &arg0->unk20, &arg0->unk2C);
}





void fn_1_3DD0(M524Camera *arg0) {
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


void fn_1_4898(omObjData *arg0) {
    M524Camera *temp_r30;
    f32 temp_f31;
    M524CamMove *temp_r28;
    M524Camera *temp_r29;
    M524Camera *temp_r31;

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
        fn_1_3694(temp_r30);
    }
}

OMOBJ *MgCameraMoveEntry(M524Camera *arg0, M524Camera *arg1, f32 farg0) {
    f32 sp8;
    omObjData *temp_r29;
    M524CamMove *temp_r31;

    sp8 = farg0;
    if ((s32) arg0->unk0 != (s32) arg1->unk0) {
        OSReport("MgCameraMoveEntry : Camera Number Different\n");
        return NULL;
    }
    temp_r29 = omAddObjEx(lbl_1_bss_80, 0x2000, 0U, 0U, -1, fn_1_4898);
    temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M524CamMove), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r29->data;
    temp_r31->unk94 = sp8;
    temp_r31->unk98 = 0.0f;
    temp_r31->unk0 = arg0;
    temp_r31->unk4 = *arg0;
    temp_r31->unk4C = *arg1;
    temp_r31->unk9C = 3;
    if ((s32) arg0->unk4 == 1) {
        fn_1_3DD0(&temp_r31->unk4);
        fn_1_3DD0(&temp_r31->unk4C);
    }
    return temp_r29;
}



void fn_1_4C18(omObjData *arg0) {
    u32 temp_r29;
    M524Camera *temp_r30;

    temp_r30 = arg0->data;
    temp_r29 = arg0->work[1];
    if ((u32) arg0->work[0] == 0) {
        fn_1_3694(lbl_1_bss_18);
        omDelObjEx(lbl_1_bss_80, arg0);
        return;
    }
    temp_r30->unk2C.x = (f32) ((lbl_1_bss_18->unk2C.x + (f32) frandmod(temp_r29 * 2)) - (f32) temp_r29);
    temp_r30->unk2C.y = (f32) ((lbl_1_bss_18->unk2C.y + (f32) frandmod(temp_r29 * 2)) - (f32) temp_r29);
    fn_1_3694((M524Camera *) temp_r30);
    arg0->work[0] -= 1;
}




void fn_1_50B0(omObjData *arg0) {
    s32 temp_r4;
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    if ((s16) omSysExitReq != 0) {
        if ((s16) lbl_1_bss_7C != -1) {
            HuAudFadeOut(0x3E8);
            lbl_1_bss_7C = -1;
        }
        arg0->func = fn_1_5160;
        Mp5WipeWhite(2, 0x3C);
        return;
    }
    temp_r31->unk4[temp_r31->unk0](arg0);
}

void fn_1_5160(omObjData *arg0) {
    if (WipeCheckEnd() == 0) {
        omOvlReturnEx(1, 1);
    }
}


void MgFlowSet(omObjData *arg0, s32 arg1) {
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    if (arg1 >= (s32) temp_r31->unk8) {
        OSReport("MgFlowSet : Value is Max Over\n");
        return;
    }
    temp_r31->unk0 = arg1;
}

void MgFlowNext(omObjData *arg0) {
    s32 temp_r4;
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    temp_r4 = temp_r31->unk0;
    if (temp_r4 == (s32) (temp_r31->unk8 - 1)) {
        OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
        return;
    }
    temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
}







void fn_1_5454(omObjData *arg0) {
    s32 temp_r4;
    u8 temp_ret;
    M524Flow *temp_r31;

    temp_ret = WipeCheckEnd();
    if (temp_ret == 0) {
        temp_r31 = arg0->data;
        temp_r4 = temp_r31->unk0;
        if (temp_r4 == (s32) (temp_r31->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
    }
}

void fn_1_54CC(omObjData *arg0) {
    if ((s16) lbl_1_bss_7C != -1) {
        HuAudFadeOut(0x3E8);
        lbl_1_bss_7C = -1;
    }
    if (WipeCheckEnd() == 0) {
        omOvlReturnEx(1, 1);
    }
}


void fn_1_55EC(omObjData *arg0) {
    s32 temp_r4;
    u8 temp_ret;
    M524Flow *temp_r30;
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    if ((s16) temp_r31->unkC == -1) {
        temp_r31->unkC = MGSeqStartCreate();
        return;
    }
    temp_ret = GameMesStatGet(temp_r31->unkC);
    if (temp_ret == 0) {
        temp_r31->unkC = -1;
        temp_r30 = arg0->data;
        temp_r4 = temp_r30->unk0;
        if (temp_r4 == (s32) (temp_r30->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r30->unk0 = (s32) (temp_r30->unk0 + 1);
    }
}

void fn_1_56A0(omObjData *arg0) {
    s32 temp_r4;
    u8 temp_ret;
    M524Flow *temp_r30;
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    if ((s16) temp_r31->unkC == -1) {
        temp_r31->unkC = MGSeqFinishCreate();
        return;
    }
    temp_ret = GameMesStatGet(temp_r31->unkC);
    if (temp_ret == 0) {
        temp_r31->unkC = -1;
        temp_r30 = arg0->data;
        temp_r4 = temp_r30->unk0;
        if (temp_r4 == (s32) (temp_r30->unk8 - 1)) {
            OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
            return;
        }
        temp_r30->unk0 = (s32) (temp_r30->unk0 + 1);
    }
}

void fn_1_5754(omObjData *arg0) {
    s32 temp_r4;
    M524Flow *temp_r30;
    M524Flow *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk10 = MgTimerCreate(temp_r31->unk14);
    MgTimerParamSet(temp_r31->unk10, temp_r31->unk18, temp_r31->unk1C, temp_r31->unk20);
    MgTimerModeOnSet(temp_r31->unk10, 1);
    temp_r30 = arg0->data;
    temp_r4 = temp_r30->unk0;
    if (temp_r4 == (s32) (temp_r30->unk8 - 1)) {
        OSReport("MgFlowNext : Value is Max Over\n", temp_r4);
        return;
    }
    temp_r30->unk0 = (s32) (temp_r30->unk0 + 1);
}







