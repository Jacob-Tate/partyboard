// Night Light Fright, ported from the Mario Party 5 decompilation (mariopartyrd/marioparty5,
// src/REL/m507dll/m507.c). See include/REL/m507Dll.h.

#include "REL/mp5compat.h"

#include "REL/m507Dll.h"

// Sound: MP5's sound bank isn't loaded, so its effect ids map to MP4 sounds from Chain Chomp Fever
// (m438, the same kind of hopping monster), whose group this overlay loads (sndGrpTable).
// -1: no MP4 counterpart, stay silent.
static int M507SeMap(int mp5SeId)
{
    switch (mp5SeId) {
        case 0x678: // the monster lands at the start
        case 0x67A: // ... and after each hop (even / odd players)
        case 0x67B:
        case 0x684: // its footsteps during the intro camera move
            return 0x6FE;
        case 0x2D8:
            return 0x6FC;
        case 0x67C: // scenery knocked over
        case 0x67D:
        case 0x67E:
        case 0x67F:
            return 0x6FB;
        case 0x680: // a player is knocked away
        case 0x681:
            return 0x6FA;
        case 0x682: // flashlight on
        case 0x683:
            return 0x6F9;
        default:
            return -1;
    }
}

static int M507FXPlay(int seId)
{
    seId = M507SeMap(seId);
    return seId < 0 ? -1 : HuAudFXPlay(seId);
}

static int M507FXPlayVol(int seId, s16 vol)
{
    seId = M507SeMap(seId);
    return seId < 0 ? -1 : HuAudFXPlayVol(seId, vol);
}

static int M507FXPlayVolPan(int seId, s16 vol, s16 pan)
{
    seId = M507SeMap(seId);
    return seId < 0 ? -1 : HuAudFXPlayVolPan(seId, vol, pan);
}

// Player motions: idle holding the flashlight (c000m1_347, kept in the character archive), shine (353),
// win (306), lose (360), knocked away (376). DK uses MP4's idle, idle, win, lose, lose.
static s16 M507MotionCreate(s16 charNo, s32 i)
{
    static const s32 mp5Num[5] = { 45, 42, 6, 49, 63 };
    static const s32 mp4Num[5] = { 0x00, 0x00, 0x17, 0x72, 0x72 };
    return Mp5CharMotionCreate(charNo, mp5Num[i], i == 0, mp4Num[i]);
}

// Shadow scale per character (MP5's table, re-indexed to MP4 characters).
static float M507CharScale(s16 charNo)
{
    static const float scale[8] = { 0.7f, 0.7f, 0.9f, 0.7f, 1.0f, 1.0f, 0.9f, 1.0f };
    return (charNo >= 0 && charNo < 8) ? scale[charNo] : 0.7f;
}

#include "math.inc"

void ObjectSetup(void);
void fn_1_4BC(omObjData *obj);
void fn_1_4F0(omObjData *obj);
void fn_1_610C(float arg0, float arg1);
u32 fn_1_6468(u32 arg0, u32 arg1);
void fn_1_64A4(s32 arg0, u16 arg1, float arg2, float arg3, float arg4);
void fn_1_64F4(s32 arg0, s32 arg1, u32 arg2);
void fn_1_7FF0(void);
void fn_1_4268(void);
void fn_1_527C(s32 arg0);
void fn_1_790(omObjData *temp_r30);
void fn_1_1120(omObjData *arg0);
s32 fn_1_1A68(omObjData *arg0);
void fn_1_1B00(omObjData *arg0);
void fn_1_2E1C(omObjData *arg0);
s32 fn_1_3C2C(void);
s16 fn_1_4EE4(s32 arg0, u32 arg1, u16 arg2, float arg3, float arg4, float arg5, float arg6, float arg7, float arg8, s32 arg9);
s32 fn_1_4048(void);
void fn_1_40CC(omObjData *arg0);
void fn_1_419C(omObjData *obj);
void fn_1_562C(s32 arg0, s32 arg1);
s32 fn_1_60A0(s32 arg0, s32 arg1, s32 arg2);
void fn_1_65AC(void);
s32 fn_1_668C(s32 arg0);
void fn_1_7770(s16 arg0, Vec *arg1);

typedef struct M507SoundEvent_s {
    s32 unk0;
    s16 unk4;
    s16 unk6;
} M507SoundEvent;

s32 lbl_1_data_0 = -1;
Vec lbl_1_data_4 = { 0, 3000, 4000 };
Vec lbl_1_data_10 = { 0, 0, 0 };
GXColor lbl_1_data_1C = { 0x80, 0x80, 0x80, 0xFF };
Vec lbl_1_data_20 = { 0, 100, 625 };
Vec lbl_1_data_2C = { 0, 1, 0 };

s32 lbl_1_data_38[23][2] = { 3, 1, 2, 2, 2, 3, 0, 0x4F, 3, 1, 3, 1, 3, 1, 2, 2, 3, 1, 1, 3, 0, 0x2E, 2, 5, 3, 1, 1, 2, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
    3, 1, 3, 1, 3, 1, 5, 0 };

s32 lbl_1_data_F0[17][2] = { 1, 5, 3, 1, 3, 1, 3, 1, 2, 5, 3, 1, 3, 1, 1, 5, 3, 1, 0, 0x1E, 2, 5, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 5, 0 };

float lbl_1_data_178[4][2] = { 80.0f, 60.0f, 496.0f, 60.0f, 80.0f, 420.0f, 496.0f, 420.0f };


u32 lbl_1_data_1AC[13] = { DATA_MAKE_NUM(DATADIR_MP5_M507, 0), DATA_MAKE_NUM(DATADIR_MP5_M507, 1), DATA_MAKE_NUM(DATADIR_MP5_M507, 3), DATA_MAKE_NUM(DATADIR_MP5_M507, 2), DATA_MAKE_NUM(DATADIR_MP5_M507, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M507, 5), DATA_MAKE_NUM(DATADIR_MP5_M507, 6), DATA_MAKE_NUM(DATADIR_MP5_M507, 7), DATA_MAKE_NUM(DATADIR_MP5_M507, 10), DATA_MAKE_NUM(DATADIR_MP5_M507, 11), DATA_MAKE_NUM(DATADIR_MP5_M507, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M507, 8), DATA_MAKE_NUM(DATADIR_MP5_M507, 9) };

u32 lbl_1_data_1E0[8] = { DATA_MAKE_NUM(DATADIR_MP5_M507, 14), DATA_MAKE_NUM(DATADIR_MP5_M507, 15), DATA_MAKE_NUM(DATADIR_MP5_M507, 16), DATA_MAKE_NUM(DATADIR_MP5_M507, 17), DATA_MAKE_NUM(DATADIR_MP5_M507, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M507, 19), DATA_MAKE_NUM(DATADIR_MP5_M507, 20), DATA_MAKE_NUM(DATADIR_MP5_M507, 21) };


M507SoundEvent lbl_1_data_234[14] = {
    { 0x18, 0x3C, 0x30 },
    { 0x24, 0x44, 0x30 },
    { 0x32, 0x3C, 0x30 },
    { 0x38, 0x44, 0x30 },
    { 0x40, 0x4B, 0x37 },
    { 0x4C, 0x4B, 0x37 },
    { 0x50, 0x53, 0x37 },
    { 0x5A, 0x4B, 0x3C },
    { 0x62, 0x53, 0x3C },
    { 0x66, 0x20, 0x46 },
    { 0x6C, 0x60, 0x46 },
    { 0x70, 0x60, 0x50 },
    { 0x73, 0x60, 0x64 },
    { 0, 0, 0 },
};

typedef struct M507ModelCacheEntry_s {
    u32 dataNum;
    s16 modelId;
    u8 pad[2];
} M507ModelCacheEntry;

typedef struct M507ModelCache_s {
    M507ModelCacheEntry entry[32];
    u8 pad[4];
} M507ModelCache;

typedef struct M507ListNode_s {
    u16 unk0;
    s16 unk2;
    struct M507ListNode_s *prev;
    struct M507ListNode_s *next;
} M507ListNode;

typedef struct M507Struct3_s {
    Vec unk0;
    Vec unkC;
    s16 unk18;
    u8 pad1A[2];
    s32 unk1C;
    s32 unk20;
} M507Struct3;

typedef struct M507Struct0_s {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    Vec unkC;
    Vec unk18;
    float unk24;
    float unk28;
    float unk2C;
    float unk30;
    s32 unk34;
    u32 unk38;
    s32 unk3C;
    u32 unk40;
    u32 unk44;
    float unk48;
    float unk4C;
    s32 unk50;
    s32 unk54;
} M507Struct0;

typedef struct M507Struct1_s {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    u8 pad10[4];
    s32 unk14;
    s32 unk18;
    u8 pad1C[4];
    Vec unk20;
    s32 unk2C;
    Vec unk30;
    Vec unk3C;
    Vec unk48;
    Vec unk54;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    float unk6C;
    float unk70;
    float unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    float unk90;
    float unk94;
    float unk98;
    s32 unk9C;
    float unkA0;
    u8 padA4[4];
    float unkA8;
    float unkAC;
    float unkB0;
    float unkB4;
    float unkB8;
    u8 padBC[2];
    s16 unkBE;
    s16 unkC0[6];
} M507Struct1;

typedef struct M507Struct2_s {
    s16 unk0[4];
    s16 unk8[4];
    s16 unk10[4];
    s16 unk18[4];
    s16 unk20[12];
    s16 unk38[4];
    s16 unk40[4];
    s16 unk48[4];
    s16 unk50[4];
    s16 unk58[4];
    s16 unk60[4];
} M507Struct2;

M507ListNode lbl_1_bss_1328;
Process *lbl_1_bss_1324;
Vec lbl_1_bss_1318;
Vec lbl_1_bss_130C;
Vec lbl_1_bss_1300;
Vec lbl_1_bss_12F4;
Vec lbl_1_bss_12C4[4];
Vec lbl_1_bss_1294[4];
Vec lbl_1_bss_1264[4];
Vec lbl_1_bss_1234[4];
s16 lbl_1_bss_122E[3];
s16 lbl_1_bss_122C;
s32 lbl_1_bss_1228;
s32 lbl_1_bss_1224;
M507ModelCache lbl_1_bss_1120;
omObjData **lbl_1_bss_111C;
omObjData *lbl_1_bss_1118;
omObjData *lbl_1_bss_1114;
omObjData *lbl_1_bss_1110;
float lbl_1_bss_110C;
M507Struct2 lbl_1_bss_10A4;
s16 lbl_1_bss_109C[4];
s16 lbl_1_bss_108C[8];
float lbl_1_bss_1088;
s32 lbl_1_bss_1084;
s32 lbl_1_bss_1080;
s32 lbl_1_bss_107C;
float lbl_1_bss_1078;
float lbl_1_bss_1074;
Vec lbl_1_bss_1044[4];
Vec lbl_1_bss_1014[4];
Vec lbl_1_bss_FE4[4];
Vec lbl_1_bss_FB4[4];
s16 lbl_1_bss_F74[8][4];
M507Struct0 lbl_1_bss_E14[4];
M507Struct3 lbl_1_bss_4[25][4];
s32 lbl_1_bss_0;

void ObjectSetup(void)
{
    s32 i;
    s32 j;
    omObjData *obj;

    lbl_1_bss_122E[0] = -1;
    lbl_1_bss_122C = -1;
    lbl_1_bss_1228 = -1;
    fn_1_7720();
    lbl_1_bss_1078 = 645.0f;
    lbl_1_bss_1074 = 485.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 25; j++) {
            lbl_1_bss_4[j][i].unk18 = -1;
            lbl_1_bss_4[j][i].unk1C = 0;
        }
    }
    OSReport("############### M507 ObjectSetup ###############\n");
    lbl_1_bss_1324 = omInitObjMan(0xC8, 0x2000);
    omGameSysInit(lbl_1_bss_1324);
    Hu3DCameraCreate(0xF);
    Hu3DCameraPerspectiveSet(0xF, 40.0f, 20.0f, 30000.0f, 1.2f);
    fn_1_610C(640.0f, 480.0f);
    lbl_1_bss_107C = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_107C, &lbl_1_data_4, &lbl_1_data_10);
    Hu3DGLightStaticSet(lbl_1_bss_107C, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_107C);
    Hu3DGLightColorSet(lbl_1_bss_107C, lbl_1_data_1C.r, lbl_1_data_1C.g, lbl_1_data_1C.b, lbl_1_data_1C.a);
    omMakeGroupEx(lbl_1_bss_1324, 0, 4);
    lbl_1_bss_111C = omGetGroupMemberListEx(lbl_1_bss_1324, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_1324, 0x64, 1, 5, 0, fn_1_790);
        lbl_1_bss_111C[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M507Struct1), MEMORY_DEFAULT_NUM);
        obj->work[0] = i;
    }
    lbl_1_bss_1118 = omAddObjEx(lbl_1_bss_1324, 0x65, 0xD, 0, -1, fn_1_1B00);
    lbl_1_bss_1118->work[0] = 0x3E8;
    lbl_1_bss_1114 = omAddObjEx(lbl_1_bss_1324, 0x66, 0, 0, -1, fn_1_4F0);
    lbl_1_bss_1084 = 0;
    lbl_1_bss_1110 = omAddObjEx(lbl_1_bss_1324, 0x66, 0, 0, -1, fn_1_4BC);
    lbl_1_bss_1080 = 0;
    lbl_1_bss_110C = 0.0f;
}

void fn_1_4BC(omObjData *obj)
{
    if (lbl_1_bss_1080 != 0) {
        fn_1_4268();
    }
}

void fn_1_4F0(omObjData *obj)
{
    s32 i;

    if (lbl_1_bss_1084 != 0) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_E14[i].unkC.y > 0.0f) {
                lbl_1_bss_0++;
                lbl_1_bss_E14[i].unk28 -= 5.0f;
            }
            lbl_1_bss_E14[i].unkC.y += lbl_1_bss_E14[i].unk28;
            if (lbl_1_bss_E14[i].unkC.y < 0.0f) {
                lbl_1_bss_E14[i].unk28 = 0.0f;
                lbl_1_bss_E14[i].unkC.y = 0.0f;
                Hu3DCameraPosSetV(1 << i, &lbl_1_bss_1044[i], &lbl_1_bss_1014[i], &lbl_1_bss_FE4[i]);
                omVibrate(i, 0x1E, 0xC, 0);
                fn_1_7770(1 << i, &lbl_1_bss_E14[i].unkC);
                if (i == 0) {
                    M507FXPlay(0x678);
                }
                fn_1_64A4(0, 0x1E, 25.0f, 0.95f, 90.0f);
                fn_1_64F4(i, 4, 0);
                HuPrcVSleep();
                if (i == 0) {
                    M507FXPlay(0x2D8);
                }
                Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk8[i], 1.0f);
            }
            Hu3DModelPosSet(lbl_1_bss_10A4.unk18[i], lbl_1_bss_E14[i].unkC.x, lbl_1_bss_E14[i].unkC.y, lbl_1_bss_E14[i].unkC.z);
        }
    }
}

void fn_1_790(omObjData *temp_r30)
{
    M507Struct1 *temp_r31;
    s32 var_r28;
    s32 i;
    u32 var_r27;

    var_r28 = -0xC;
    temp_r31 = temp_r30->data;
    temp_r31->unk0C = temp_r30->work[0];
    temp_r31->unk14 = GWPlayerCfg[temp_r31->unk0C].character;
    temp_r31->unk18 = GWPlayerCfg[temp_r31->unk0C].pad_idx;
    temp_r31->unk08 = 0x7D0;
    temp_r31->unk00 = 0;
    temp_r31->unk04 = -1;
    temp_r31->unk60 = 0;
    temp_r31->unk64 = 0;
    temp_r31->unk68 = 0;
    temp_r31->unk70 = -1.0f;
    temp_r31->unk74 = 3000.0f;
    temp_r31->unk78 = 0;
    temp_r31->unk80 = 0;
    temp_r31->unk3C.x = temp_r31->unk3C.y = temp_r31->unk3C.z = 0.0f;
    temp_r31->unk2C = temp_r31->unk0C;
    temp_r31->unk48.x = temp_r31->unk48.y = temp_r31->unk48.z = 0.0f;
    temp_r31->unk54.x = temp_r31->unk54.y = temp_r31->unk54.z = 0.0f;
    temp_r31->unk9C = 0;
    temp_r31->unkA0 = 0.0f;
    temp_r31->unk84 = GWPlayerCfg[temp_r31->unk0C].diff;
    switch (temp_r31->unk84) {
        case 0:
            temp_r31->unk88 = 2;
            temp_r31->unk90 = 800.0f;
            temp_r31->unk94 = 1500.0f;
            break;
        case 1:
            temp_r31->unk88 = 3;
            temp_r31->unk90 = 500.0f;
            temp_r31->unk94 = 1000.0f;
            break;
        case 2:
            temp_r31->unk88 = 0xA;
            temp_r31->unk90 = 300.0f;
            temp_r31->unk94 = 700.0f;
            break;
        case 3:
            temp_r31->unk88 = 0x14;
            temp_r31->unk90 = 100.0f;
            temp_r31->unk94 = 300.0f;
            break;
    }
    if (frandmod(temp_r31->unk88) == 0) {
        temp_r31->unk8C = 0;
        temp_r31->unk98 = 0.0f;
    }
    else {
        temp_r31->unk8C = 1;
        var_r27 = temp_r31->unk94;
        temp_r31->unk98 = fn_1_6468(temp_r31->unk90, var_r27);
    }
    temp_r30->model[0] = CharModelCreate(temp_r31->unk14, 4);
    lbl_1_bss_109C[temp_r31->unk0C] = temp_r30->model[0];
    Hu3DModelCameraSet(temp_r30->model[0], 1 << temp_r31->unk2C);
    CharModelStepFxSet(temp_r31->unk14, 0);
    for (i = 0; i < 5; i++) {
        temp_r30->motion[i] = M507MotionCreate(temp_r31->unk14, i);
        CharMotionSet(temp_r31->unk14, temp_r30->motion[i]);
    }
    Hu3DModelAttrSet(temp_r30->model[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(temp_r30->model[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(temp_r30->model[0], 5);
    Hu3DMotionSet(temp_r30->model[0], temp_r30->motion[0]);
    Hu3DMotionSpeedSet(temp_r30->model[0], 1.0f);
    temp_r31->unk30.x = temp_r31->unk30.y = temp_r31->unk30.z = 0.0f;
    temp_r31->unk20.x = 0.0f;
    temp_r31->unk20.y = 0.0f;
    temp_r31->unk20.z = 0.0f;
    temp_r30->trans.x = temp_r31->unk20.x = 0.0f;
    temp_r30->trans.y = temp_r31->unk20.y = 0.0f;
    temp_r30->trans.z = temp_r31->unk20.z = 0.0f;
    omSetTra(temp_r30, temp_r31->unk20.x, temp_r31->unk20.y, temp_r31->unk20.z);
    omSetRot(temp_r30, temp_r31->unk30.x, temp_r31->unk30.y, temp_r31->unk30.z);
    Hu3DModelAttrReset(temp_r30->model[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose(temp_r31->unk14);
    temp_r31->unkBE = MgScoreWinCreate(0x80, 0x28);
    MgScoreWinTPLvlSet(temp_r31->unkBE, 0.85f);
    MgScoreWinPosSet(temp_r31->unkBE, lbl_1_data_178[temp_r31->unk0C][0], lbl_1_data_178[temp_r31->unk0C][1]);
    MgScoreWinDispSet(temp_r31->unkBE, 0);
    temp_r31->unkC0[0] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), 0, 0);
    espDispOff(temp_r31->unkC0[0]);
    espDrawNoSet(temp_r31->unkC0[0], 0);
    espPosSet(temp_r31->unkC0[0], var_r28 + (8.0f + (8.0f + (lbl_1_data_178[temp_r31->unk0C][0] - 48.0f))), lbl_1_data_178[temp_r31->unk0C][1]);
    espAttrSet(temp_r31->unkC0[0], HUSPR_ATTR_NOANIM);
    temp_r31->unkC0[1] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), 0, 0);
    espDispOff(temp_r31->unkC0[1]);
    espDrawNoSet(temp_r31->unkC0[1], 0);
    espPosSet(temp_r31->unkC0[1], var_r28 + (8.0f + (8.0f + (lbl_1_data_178[temp_r31->unk0C][0] - 32.0f))), lbl_1_data_178[temp_r31->unk0C][1]);
    espAttrSet(temp_r31->unkC0[1], HUSPR_ATTR_NOANIM);
    temp_r31->unkC0[4] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), 0, 0xC);
    espDispOff(temp_r31->unkC0[4]);
    espDrawNoSet(temp_r31->unkC0[4], 0);
    espPosSet(temp_r31->unkC0[4], var_r28 + (8.0f + (8.0f + (lbl_1_data_178[temp_r31->unk0C][0] - 16.0f))), lbl_1_data_178[temp_r31->unk0C][1]);
    espAttrSet(temp_r31->unkC0[4], HUSPR_ATTR_NOANIM);
    temp_r31->unkC0[2] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), 0, 0);
    espDispOff(temp_r31->unkC0[2]);
    espDrawNoSet(temp_r31->unkC0[2], 0);
    espPosSet(temp_r31->unkC0[2], (var_r28 + (8.0f + (8.0f + lbl_1_data_178[temp_r31->unk0C][0]))) - 8.0f, lbl_1_data_178[temp_r31->unk0C][1]);
    espAttrSet(temp_r31->unkC0[2], HUSPR_ATTR_NOANIM);
    temp_r31->unkC0[5] = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 53), 0, 1);
    espDispOff(temp_r31->unkC0[5]);
    espDrawNoSet(temp_r31->unkC0[5], 0);
    espPosSet(
        temp_r31->unkC0[5], 3.0f + (var_r28 + (8.0f + (16.0f + (16.0f + lbl_1_data_178[temp_r31->unk0C][0])))), lbl_1_data_178[temp_r31->unk0C][1]);
    espAttrSet(temp_r31->unkC0[5], HUSPR_ATTR_NOANIM);
    for (i = 0; i < 3; i++) {
        espColorSet(temp_r31->unkC0[i], 0xFF, 0xD8, 0x15);
    }
    espColorSet(temp_r31->unkC0[4], 0xFF, 0xD8, 0x15);
    espColorSet(temp_r31->unkC0[5], 0xFF, 0xD8, 0x15);
    temp_r30->func = fn_1_1120;
}

void fn_1_1120(omObjData *temp_r30)
{
    s16 sp14[4];
    s32 sp10;
    M507Struct1 *temp_r31;
    s32 var_r28;
    s32 i;
    float var_f31;
    float var_f30;

    temp_r31 = temp_r30->data;
    sp10 = temp_r31->unk0C;
    switch (temp_r31->unk08) {
        case 0x7D0:
            if (lbl_1_bss_1118->work[0] >= 0x3EEU) {
                temp_r31->unk08++;
            }
            break;
        case 0x7D1:
            if (temp_r31->unk68 == 0) {
                if (GWPlayerCfg[temp_r31->unk0C].iscom != 0) {
                    temp_r31->unk7C = (u16)fn_1_1A68(temp_r30);
                }
                else {
                    temp_r31->unk7C = HuPadBtnDown[temp_r31->unk18];
                }
                if (temp_r31->unk64 == 0 && temp_r31->unk68 == 0 && (temp_r31->unk7C & PAD_BUTTON_A)) {
                    temp_r31->unk64 = 1;
                    temp_r31->unk6C = 0.0f;
                    var_r28 = 1;
                    if (temp_r31->unk00 != var_r28) {
                        temp_r31->unk00 = var_r28;
                        Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[temp_r31->unk00], 0.0f, 8.0f, HU3D_ATTR_NONE);
                    }
                }
                if (temp_r31->unk64 != 0) {
                    if (temp_r31->unk6C++ > 30.0f) {
                        if (temp_r31->unk60 == 0) {
                            lbl_1_bss_E14[temp_r31->unk0C].unk8 = 5;
                        }
                        temp_r31->unk60 = 1;
                        if ((temp_r31->unk0C % 2) == 0) {
                            if (temp_r31->unk04 != 0x682) {
                                temp_r31->unk04 = 0x682;
                                M507FXPlay(0x682);
                            }
                        }
                        else {
                            if (temp_r31->unk04 != 0x683) {
                                temp_r31->unk04 = 0x683;
                                M507FXPlay(0x683);
                            }
                        }
                        if (temp_r31->unk74 > 0.0f) {
                            Hu3DModelAttrReset(lbl_1_bss_10A4.unk40[temp_r31->unk0C], HU3D_ATTR_DISPOFF);
                            var_f31 = (s16)temp_r31->unk74;
                            sp14[0] = var_f31 / 1000.0f;
                            var_f31 -= sp14[0] * 1000;
                            sp14[1] = var_f31 / 100.0f;
                            var_f31 -= sp14[1] * 100;
                            sp14[2] = var_f31 / 10.0f;
                            var_f31 -= sp14[2] * 10;
                            sp14[3] = var_f31;
                            MgScoreWinDispSet(temp_r31->unkBE, 1);
                            for (i = 0; i < 3; i++) {
                                espBankSet(temp_r31->unkC0[i], sp14[i]);
                                espDispOn(temp_r31->unkC0[i]);
                                espDispOn(temp_r31->unkC0[4]);
                                espDispOn(temp_r31->unkC0[5]);
                            }
                            if (sp14[0] == 0) {
                                espDispOff(temp_r31->unkC0[0]);
                            }
                        }
                    }
                    else {
                        temp_r31->unk60 = 0;
                        temp_r31->unk30.y += 6.0f;
                    }
                }
            }
            if (lbl_1_bss_1118->work[0] >= 0x3EFU) {
                temp_r31->unk08 = 0x7D3;
            }
            break;
        case 0x7D3:
            if (lbl_1_bss_1118->work[0] >= 0x3EFU) {
                temp_r31->unk08 = 0x7D7;
            }
            break;
        case 0x7D7:
            if (lbl_1_bss_1118->work[0] >= 0x3F1U) {
                temp_r31->unk08 = 0x7D9;
            }
            break;
        case 0x7D9:
            break;
        default:
            OSReport("*** player mode error(%d)!!\n", temp_r31->unk08);
            break;
    }
    if (!0 && temp_r31->unk08 >= 0x7D9 && temp_r31->unk30.y < 360.0f) {
        temp_r31->unk30.y += 6.0f;
    }
    if (lbl_1_bss_1118->work[0] <= 0x3EFU && temp_r31->unk68 != 0) {
        var_r28 = 4;
        if (temp_r31->unk00 != var_r28) {
            temp_r31->unk00 = var_r28;
            if ((temp_r31->unk0C % 2) == 0) {
                if (temp_r31->unk04 != 0x680) {
                    temp_r31->unk04 = 0x680;
                    M507FXPlay(0x680);
                }
            }
            else {
                if (temp_r31->unk04 != 0x681) {
                    temp_r31->unk04 = 0x681;
                    M507FXPlay(0x681);
                }
            }
            if ((temp_r31->unk0C % 2) == 0) {
                CharFXPlay(temp_r31->unk14, 0x123);
            }
            else {
                CharFXPlay(temp_r31->unk14, 0x123);
            }
            Hu3DMotionShiftSet(temp_r30->model[0], temp_r30->motion[temp_r31->unk00], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            temp_r31->unk48.y = fn_1_6468(0xF, 0x1E);
            temp_r31->unk48.z = fn_1_6468(8, 0xF);
            temp_r31->unk54.z = fn_1_6468(0xA, 0x1E);
        }
        temp_r31->unk20.x += temp_r31->unk48.x;
        temp_r31->unk20.y += temp_r31->unk48.y;
        temp_r31->unk20.z += temp_r31->unk48.z;
        temp_r31->unk30.x += temp_r31->unk54.x;
        temp_r31->unk30.y += temp_r31->unk54.y;
        temp_r31->unk30.z += temp_r31->unk54.z;
    }
    temp_r31->unkB8 = 0.0f;
    if (temp_r31->unk9C > 0) {
        temp_r31->unkB8 = temp_r31->unkA8 * sind(temp_r31->unkB0);
        temp_r31->unkB0 += temp_r31->unkB4;
        temp_r31->unkA8 *= temp_r31->unkAC;
        temp_r31->unk9C--;
        Hu3DCameraPosSet(1 << temp_r31->unk2C, lbl_1_bss_1044[temp_r31->unk0C].x, lbl_1_bss_1044[temp_r31->unk0C].y,
            lbl_1_bss_1044[temp_r31->unk0C].z, lbl_1_bss_1014[temp_r31->unk0C].x, lbl_1_bss_1014[temp_r31->unk0C].y,
            lbl_1_bss_1014[temp_r31->unk0C].z, lbl_1_bss_FE4[temp_r31->unk0C].x, temp_r31->unkB8 + lbl_1_bss_FE4[temp_r31->unk0C].y,
            lbl_1_bss_FE4[temp_r31->unk0C].z);
    }
    omSetTra(temp_r30, temp_r31->unk20.x, temp_r31->unk20.y, temp_r31->unk20.z);
    omSetRot(temp_r30, temp_r31->unk30.x, temp_r31->unk30.y, temp_r31->unk30.z);
    Hu3DModelPosSet(lbl_1_bss_10A4.unk60[temp_r31->unk0C], temp_r31->unk20.x, 0.0f, temp_r31->unk20.z);
    var_f30 = M507CharScale(temp_r31->unk14);
    Hu3DModelScaleSet(lbl_1_bss_10A4.unk60[temp_r31->unk0C], var_f30, var_f30, 1.0f);
}

s32 fn_1_1A68(omObjData *arg0)
{
    s32 sp8;
    M507Struct1 *temp_r31;

    temp_r31 = arg0->data;
    sp8 = temp_r31->unk0C;
    switch (temp_r31->unk84) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (temp_r31->unk8C != 0) {
                if (300.0f + temp_r31->unk98 >= temp_r31->unk74) {
                    return 0x100;
                }
            }
            else {
                if (50.0f >= temp_r31->unk74) {
                    return 0x100;
                }
            }
            break;
    }
    return 0;
}

void fn_1_1B00(omObjData *temp_r28)
{
    s32 var_r31;
    s16 var_r30;
    char *var_r29;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        lbl_1_bss_10A4.unk0[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[0]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk0[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk0[var_r31], HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk0[var_r31], 1 << var_r31);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk0[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk0[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk0[var_r31], 0);

        lbl_1_bss_10A4.unk8[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[1]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk8[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk8[var_r31], 1 << var_r31);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk8[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk8[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk8[var_r31], 0);
        Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk8[var_r31], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_10A4.unk8[var_r31], 0.0f);

        fn_1_4EE4(var_r31, lbl_1_data_1AC[5], 1 << var_r31, 280.0f, 0.0f, -250.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[6], 1 << var_r31, -280.0f, 0.0f, -750.0f, 0.0f, 0.0f, 5.0f, 1);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[6], 1 << var_r31, 280.0f, 0.0f, -1250.0f, 0.0f, 0.0f, 5.0f, 1);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[4], 1 << var_r31, -280.0f, 0.0f, -1500.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[5], 1 << var_r31, 280.0f, 0.0f, -1750.0f, 0.0f, 0.0f, 0.0f, 0);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[6], 1 << var_r31, -280.0f, 0.0f, -2250.0f, 0.0f, 0.0f, 5.0f, 1);
        fn_1_4EE4(var_r31, lbl_1_data_1AC[6], 1 << var_r31, 280.0f, 0.0f, -2500.0f, 0.0f, 0.0f, 5.0f, 1);

        lbl_1_bss_108C[var_r31] = Hu3DMotionCreate(HuDataSelHeapReadNum(lbl_1_data_1AC[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_10A4.unk10[var_r31] = Hu3DModelCameraCreate(lbl_1_bss_108C[var_r31], 1 << var_r31);
        HuPrcVSleep();
        lbl_1_bss_1088 = Hu3DMotionMotionMaxTimeGet(lbl_1_bss_108C[0]);
        Mp5CameraPosGet(1 << var_r31, &lbl_1_bss_1044[var_r31], &lbl_1_bss_1014[var_r31], &lbl_1_bss_FE4[var_r31]);
        HuPrcVSleep();
        Hu3DModelKill(lbl_1_bss_10A4.unk10[var_r31]);
        HuPrcVSleep();

        lbl_1_bss_10A4.unk18[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[3]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk18[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk18[var_r31], HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk18[var_r31], 1 << var_r31);
        Hu3DModelScaleSet(lbl_1_bss_10A4.unk18[var_r31], 3.0f, 3.0f, 3.0f);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk18[var_r31], 0.0f, 1500.0f, -3300.0f);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk18[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk18[var_r31], 2);
        lbl_1_bss_F74[0][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[1][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[2][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[3][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[4][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[5][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[6][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_F74[7][var_r31]
            = Hu3DJointMotion(lbl_1_bss_10A4.unk18[var_r31], HuDataSelHeapReadNum(lbl_1_data_1E0[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DMotionSet(lbl_1_bss_10A4.unk18[var_r31], lbl_1_bss_F74[1][var_r31]);

        lbl_1_bss_E14[var_r31].unk0 = 0;
        lbl_1_bss_E14[var_r31].unk0 = 5;
        lbl_1_bss_E14[var_r31].unk4 = var_r31;
        lbl_1_bss_E14[var_r31].unk8 = 0;
        lbl_1_bss_E14[var_r31].unkC.x = 0.0f;
        lbl_1_bss_E14[var_r31].unkC.y = 1500.0f;
        lbl_1_bss_E14[var_r31].unkC.z = -3300.0f;
        lbl_1_bss_E14[var_r31].unk18.x = 0.0f;
        lbl_1_bss_E14[var_r31].unk18.y = 0.0f;
        lbl_1_bss_E14[var_r31].unk18.z = 0.0f;
        lbl_1_bss_E14[var_r31].unk24 = 0.0f;
        lbl_1_bss_E14[var_r31].unk28 = 0.0f;
        lbl_1_bss_E14[var_r31].unk2C = 0.0f;
        lbl_1_bss_E14[var_r31].unk30 = 0.0f;
        lbl_1_bss_E14[var_r31].unk34 = 0;
        lbl_1_bss_E14[var_r31].unk3C = 0;
        lbl_1_bss_E14[var_r31].unk40 = 0;
        lbl_1_bss_E14[var_r31].unk50 = 0;
        lbl_1_bss_E14[var_r31].unk54 = 0;

        lbl_1_bss_10A4.unk58[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[11]);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk58[var_r31], 1 << var_r31);
        Hu3DModelScaleSet(lbl_1_bss_10A4.unk58[var_r31], 1.0f, 1.0f, 1.0f);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk58[var_r31], lbl_1_bss_E14[var_r31].unkC.x, 0.0f, lbl_1_bss_E14[var_r31].unkC.z);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk58[var_r31], 1);

        lbl_1_bss_10A4.unk60[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[12]);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk60[var_r31], 1 << var_r31);
        Hu3DModelScaleSet(lbl_1_bss_10A4.unk60[var_r31], 1.0f, 1.0f, 1.0f);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk60[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk60[var_r31], 1);

        fn_1_7FF0();

        lbl_1_bss_10A4.unk40[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[8]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk40[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk40[var_r31], 1 << var_r31);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk40[var_r31], 0.0f, 0.0f, -25.0f);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk40[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk40[var_r31], 4);

        lbl_1_bss_10A4.unk50[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[10]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk50[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk50[var_r31], 1 << var_r31);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk50[var_r31], 0.0f, 130.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk50[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk50[var_r31], 4);
        Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk50[var_r31], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_10A4.unk50[var_r31], 0.0f);

        lbl_1_bss_10A4.unk38[var_r31] = Hu3DModelCreateFile(lbl_1_data_1AC[7]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk38[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_10A4.unk38[var_r31], 1 << var_r31);
        Hu3DModelRotSet(lbl_1_bss_10A4.unk38[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_10A4.unk38[var_r31], 5);

        var_r30 = ((M507Struct1 *)lbl_1_bss_111C[var_r31]->data)->unk14;
        var_r29 = CharModelItemHookGet(var_r30, 4, 0);
        Hu3DModelHookSet(lbl_1_bss_109C[var_r31], var_r29, lbl_1_bss_10A4.unk38[var_r31]);
    }

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        Hu3DModelAttrReset(lbl_1_bss_10A4.unk0[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_10A4.unk8[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_10A4.unk18[var_r31], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_10A4.unk38[var_r31], HU3D_ATTR_DISPOFF);
    }

    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    OSReport("############### main start ##########\n");
    temp_r28->func = fn_1_2E1C;
}

void fn_1_2E1C(omObjData *temp_r30)
{
    M507Struct1 *sp24[4];
    Vec sp18;
    Vec spC;
    s32 sp8;
    s32 var_r31;
    s32 var_r27;
    s32 var_r24;
    s32 var_r23;
    s32 var_r22;
    s32 var_r21;
    Vec *var_r25;
    Vec *var_r26;
    Vec *var_r28;
    Vec *var_r29;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;

    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        sp24[var_r31] = omObjGetDataAs(lbl_1_bss_111C[var_r31], M507Struct1);
    }

    if (omSysExitReq != 0) {
        Mp5WipeWhite(WIPE_MODE_OUT, 60);
        HuAudSeqAllFadeOut(0x3E8);
        HuAudSStreamAllFadeOut(0x3E8);
        if (lbl_1_data_0 >= 0 && HuAudFXStatusGet(lbl_1_data_0)) {
            HuAudFXFadeOut(lbl_1_data_0, 0x3E8);
        }
        temp_r30->func = fn_1_419C;
    }

    switch (temp_r30->work[0]) {
        case 0x3E8:
            if (WipeStatGet() == 0) {
                temp_r30->work[0]++;
                lbl_1_bss_110C = 0.0f;
                lbl_1_bss_0 = 0;
            }
            break;

        case 0x3E9:
            lbl_1_bss_1084 = 1;
            lbl_1_bss_110C += 1.0f;
            if (100.0f <= lbl_1_bss_110C) {
                temp_r30->work[0]++;
                lbl_1_bss_110C = 0.0f;
                lbl_1_bss_1084 = 0;
            }
            break;

        case 0x3EA:
            lbl_1_bss_110C += 1.0f;
            if (lbl_1_bss_110C > 30.0f) {
                temp_r30->work[0]++;
                lbl_1_bss_110C = 0.0f;
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    lbl_1_bss_E14[var_r31].unk28 = 0.0f;
                    lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                    lbl_1_bss_10A4.unk10[var_r31] = Hu3DModelCameraCreate(lbl_1_bss_108C[var_r31], 1 << var_r31);
                    Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk10[var_r31], 1.0f);
                    Hu3DCameraMotionStart(lbl_1_bss_10A4.unk10[var_r31], 1 << var_r31);
                    fn_1_64F4(var_r31, 0, HU3D_MOTATTR_LOOP);
                }
            }
            break;

        case 0x3EB:
            lbl_1_bss_110C += 1.0f;
            if (lbl_1_bss_1088 <= lbl_1_bss_110C) {
                temp_r30->work[0]++;
                lbl_1_bss_110C = 0.0f;
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    Mp5CameraPosGet(1 << var_r31, &lbl_1_bss_1044[var_r31], &lbl_1_bss_1014[var_r31], &lbl_1_bss_FE4[var_r31]);
                }
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    Hu3DModelKill(lbl_1_bss_10A4.unk10[var_r31]);
                    var_r23 = Hu3DMotionKill(lbl_1_bss_108C[var_r31]);
                    if (var_r23 != 0) {
                        lbl_1_bss_108C[var_r31] = -1;
                    }
                }
            }
            break;

        case 0x3EC:
            lbl_1_bss_110C += 1.0f;
            lbl_1_bss_1078 -= 7.2222223f;
            lbl_1_bss_1074 -= 5.4444447f;
            fn_1_610C(lbl_1_bss_1078, lbl_1_bss_1074);
            if (45.0f <= lbl_1_bss_110C) {
                temp_r30->work[0]++;
                lbl_1_bss_110C = 0.0f;
                fn_1_610C(320.0f, 240.0f);
            }
            break;

        case 0x3ED:
            if (lbl_1_bss_122E[0] < 0) {
                lbl_1_bss_122E[0] = MGSeqStartCreate();
                if (lbl_1_bss_1228 < 0) {
                    lbl_1_bss_1228 = HuAudSeqPlay(0x49); // MP5 stream 0x39 -> Chain Chomp Fever music
                }
            }
            else if (MGSeqStatGet(lbl_1_bss_122E[0]) == 0) {
                temp_r30->work[0]++;
                lbl_1_bss_122E[0] = -1;
            }
            break;

        case 0x3EE:
            lbl_1_bss_1080 = 1;
            if (fn_1_4048() != 0) {
                temp_r30->work[0] = 0x3EF;
                lbl_1_bss_110C = 0.0f;
                lbl_1_bss_1080 = 0;
            }
            break;

        case 0x3EF:
            lbl_1_bss_1080 = 1;
            if (lbl_1_bss_122E[0] < 0) {
                lbl_1_bss_122E[0] = MGSeqFinishCreate();
                HuAudSeqFadeOut(lbl_1_bss_1228, 0x64);
                lbl_1_bss_1228 = -1;
            }
            else if (MGSeqStatGet(lbl_1_bss_122E[0]) == 0) {
                temp_r30->work[0]++;
                lbl_1_bss_122E[0] = -1;
                lbl_1_bss_110C = 0.0f;
                lbl_1_bss_1080 = 0;
                for (var_r31 = 0; var_r31 < 4; var_r31++) {
                    lbl_1_bss_FB4[var_r31].x = lbl_1_bss_E14[var_r31].unkC.x;
                    lbl_1_bss_FB4[var_r31].y = 300.0f + lbl_1_bss_E14[var_r31].unkC.y;
                    lbl_1_bss_FB4[var_r31].z = lbl_1_bss_E14[var_r31].unkC.z;
                    lbl_1_bss_12C4[var_r31] = lbl_1_bss_1044[var_r31];
                    lbl_1_bss_1264[var_r31] = lbl_1_bss_FE4[var_r31];
                    lbl_1_bss_1294[var_r31] = lbl_1_data_20;
                    lbl_1_bss_1234[var_r31] = lbl_1_bss_FB4[var_r31];
                }
            }
            break;

        case 0x3F0:
            lbl_1_bss_110C += 1.0f;
            var_f29 = lbl_1_bss_110C / 60.0f;
            for (var_r27 = 0; var_r27 < 4; var_r27++) {
                var_r25 = &lbl_1_bss_1294[var_r27];
                var_r28 = &lbl_1_bss_12C4[var_r27];
                var_f31 = var_f29;
                if (1.0f < var_f31) {
                    var_f31 = 1.0f;
                }
                var_f28 = sind(90.0f * var_f31) * sind(90.0f * var_f31);
                spC.x = var_r28->x + (var_f28 * (var_r25->x - var_r28->x));
                spC.y = var_r28->y + (var_f28 * (var_r25->y - var_r28->y));
                spC.z = var_r28->z + (var_f28 * (var_r25->z - var_r28->z));

                var_r26 = &lbl_1_bss_1234[var_r27];
                var_r29 = &lbl_1_bss_1264[var_r27];
                var_f30 = var_f29;
                if (1.0f < var_f30) {
                    var_f30 = 1.0f;
                }
                var_f27 = sind(90.0f * var_f30) * sind(90.0f * var_f30);
                sp18.x = var_r29->x + (var_f27 * (var_r26->x - var_r29->x));
                sp18.y = var_r29->y + (var_f27 * (var_r26->y - var_r29->y));
                sp18.z = var_r29->z + (var_f27 * (var_r26->z - var_r29->z));
                Hu3DCameraPosSetV(1 << var_r27, &spC, &lbl_1_data_2C, &sp18);
            }
            if (1.0f <= var_f29) {
                var_r24 = 1;
            }
            else {
                lbl_1_bss_1224 = 1;
                var_r24 = 0;
            }
            if (var_r24 != 0) {
                if (0 != 0) {
                    temp_r30->work[0] = 0x3F2;
                }
                else {
                    temp_r30->work[0]++;
                    lbl_1_bss_122E[0] = -1;
                    lbl_1_bss_110C = 0.0f;
                }
            }
            break;

        case 0x3F1:
            if (0.0f == lbl_1_bss_110C) {
                sp8 = fn_1_3C2C();
            }
            if (lbl_1_bss_110C > 210.0f) {
                temp_r30->work[0] = 0x3F2;
                lbl_1_bss_110C = 0.0f;
            }
            if (MGSeqStatGet(lbl_1_bss_122E[0]) == 0) {
                lbl_1_bss_122E[0] = -1;
            }
            lbl_1_bss_110C += 1.0f;
            break;

        case 0x3F2:
            lbl_1_bss_110C += 1.0f;
            if (1.0f < lbl_1_bss_110C) {
                lbl_1_bss_122E[0] = -1;
                if (0 != 0) {
                    for (var_r31 = 0; var_r31 < 4; var_r31++) {
                        var_r21 = 10.0f * (s32)sp24[var_r31]->unk74;
                        var_r22 = sp24[var_r31]->unk0C;
                        (void)var_r21; // decathlon scores: MP5 only
                        (void)var_r22;
                    }
                    Mp5WipeWhite(WIPE_MODE_OUT, 60);
                }
                else {
                    Mp5WipeWhite(WIPE_MODE_OUT, 60);
                }
                temp_r30->func = fn_1_40CC;
            }
            break;

        default:
            OSReport("*** main mode error(%d)!!\n", temp_r30->work[0]);
            break;
    }
    fn_1_65AC();
}

s32 fn_1_3C2C(void)
{
    char *spC;
    s32 sp8;
    s16 sp10[4];
    float sp18[4];
    M507Struct1 *temp_r31;
    s32 i;
    s32 var_r29;
    s16 var_r28;
    s32 var_r27;
    s16 var_r26;
    s16 var_r25;
    float var_f31;

    var_f31 = 3300.0f;
    sp8 = -1;
    for (i = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_111C[i]->data;
        if (temp_r31->unk68 != 0) {
            sp18[i] = -1.0f;
        }
        else {
            sp18[i] = temp_r31->unk70;
        }
    }
    if ((-1.0f == sp18[0]) && (-1.0f == sp18[1]) && (-1.0f == sp18[2]) && (-1.0f == sp18[3])) {
        lbl_1_bss_122E[0] = MGSeqDrawCreate();
        HuAudSStreamPlay(4);
        return -1;
    }
    for (i = 0; i < 4; i++) {
        if ((var_f31 > sp18[i]) && (sp18[i] > 0.0f)) {
            var_f31 = sp18[i];
        }
    }
    for (i = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_111C[i]->data;
        if (var_f31 == sp18[i]) {
            sp10[i] = temp_r31->unk14;
            temp_r31->unk78 = 1;
        }
        else {
            sp10[i] = -1;
            temp_r31->unk78 = 0;
        }
    }
    lbl_1_bss_122E[0] = MGSeqWinCreate(sp10[0], sp10[1], sp10[2], sp10[3]);
    HuAudSStreamPlay(1);
    for (i = 0; i < 4; i++) {
        temp_r31 = lbl_1_bss_111C[i]->data;
        if (sp10[temp_r31->unk0C] == -1) {
            if (temp_r31->unk68 == 0) {
                Hu3DMotionShiftSet(lbl_1_bss_111C[temp_r31->unk0C]->model[0], lbl_1_bss_111C[temp_r31->unk0C]->motion[3], 0.0f, 8.0f, HU3D_ATTR_NONE);
            }
        }
        else {
            Hu3DMotionShiftSet(lbl_1_bss_111C[temp_r31->unk0C]->model[0], lbl_1_bss_111C[temp_r31->unk0C]->motion[2], 0.0f, 8.0f, HU3D_ATTR_NONE);
            var_r27 = temp_r31->unk0C;
            var_r26 = GWPlayer[var_r27].coin_win;
            var_r25 = var_r26;
            var_r28 = var_r25 + 0xA;
            var_r29 = temp_r31->unk0C;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[var_r29].coin_win = var_r28;
            }
        }
        spC = CharModelItemHookGet(temp_r31->unk14, 4, 0);
        Hu3DModelHookReset(lbl_1_bss_109C[temp_r31->unk0C]);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk40[temp_r31->unk0C], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_10A4.unk38[temp_r31->unk0C], HU3D_ATTR_DISPOFF);
    }
    return 0;
}

s32 fn_1_4048(void)
{
    s32 sp8[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        sp8[i] = lbl_1_bss_E14[i].unk50;
    }
    if (sp8[0] != 0 && sp8[1] != 0 && sp8[2] != 0 && sp8[3] != 0) {
        return 1;
    }
    return 0;
}

void fn_1_40CC(omObjData *arg0)
{
    s32 i;
    M507Struct1 *temp_r30;

    if (!WipeStatGet()) {
        if (lbl_1_bss_122E[0] >= 0) {
            MGSeqKill(lbl_1_bss_122E[0]);
        }
        if (lbl_1_bss_122C >= 0) {
            MGSeqKill(lbl_1_bss_122C);
        }
        MGSeqKillAll();
        HuAudAllStop();
        for (i = 0; i < 4; i++) {
            temp_r30 = lbl_1_bss_111C[i]->data;
            CharModelKill(temp_r30->unk14);
        }
        omOvlReturnEx(1, 1);
    }
}

void fn_1_419C(omObjData *obj)
{
    s32 i;
    M507Struct1 *temp_r30;

    if (!WipeStatGet()) {
        if (lbl_1_bss_122E[0] >= 0) {
            MGSeqKill(lbl_1_bss_122E[0]);
        }
        if (lbl_1_bss_122C >= 0) {
            MGSeqKill(lbl_1_bss_122C);
        }
        MGSeqKillAll();
        for (i = 0; i < 4; i++) {
            temp_r30 = lbl_1_bss_111C[i]->data;
            CharModelKill(temp_r30->unk14);
        }
        omOvlReturnEx(1, 1);
    }
}

void fn_1_4268(void)
{
    s32 var_r31;
    M507Struct1 *var_r30;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;
    float var_f27;
    for (var_r31 = 0; var_r31 < 4; var_r31++) {
        var_r30 = lbl_1_bss_111C[var_r31]->data;
        if (var_r30->unk60 != 0) {
            lbl_1_bss_E14[var_r31].unk2C = 0.0f;
            lbl_1_bss_E14[var_r31].unk50 = 1;
            var_r30->unk70 = fabs(lbl_1_bss_E14[var_r31].unkC.z);
        }
        switch (lbl_1_bss_E14[var_r31].unk8) {
            case 0:
                lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                if (lbl_1_bss_E14[var_r31].unk3C++ >= lbl_1_bss_E14[var_r31].unk40) {
                    fn_1_562C(var_r31, lbl_1_bss_E14[var_r31].unk8);
                }
                break;
            case 1:
                lbl_1_bss_E14[var_r31].unk2C = lbl_1_bss_E14[var_r31].unk30;
                lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                if (lbl_1_bss_E14[var_r31].unk34++ >= lbl_1_bss_E14[var_r31].unk38) {
                    fn_1_562C(var_r31, lbl_1_bss_E14[var_r31].unk8);
                }
                break;
            case 2:
                lbl_1_bss_E14[var_r31].unk2C = lbl_1_bss_E14[var_r31].unk30;
                lbl_1_bss_E14[var_r31].unk4C += lbl_1_bss_E14[var_r31].unk48;
                lbl_1_bss_E14[var_r31].unkC.y = 300.0 * sind(lbl_1_bss_E14[var_r31].unk4C);
                if (lbl_1_bss_E14[var_r31].unkC.y <= 0.0f) {
                    lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                }
                if (lbl_1_bss_E14[var_r31].unk34++ >= lbl_1_bss_E14[var_r31].unk38) {
                    fn_1_562C(var_r31, lbl_1_bss_E14[var_r31].unk8);
                }
                break;
            case 3:
                fn_1_64F4(var_r31, 7, HU3D_MOTATTR_LOOP);
                var_r30 = lbl_1_bss_111C[var_r31]->data;
                lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                lbl_1_bss_E14[var_r31].unk2C = 0.0f;
                var_r30->unk68 = 1;
                Hu3DModelAttrSet(lbl_1_bss_10A4.unk40[var_r30->unk0C], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_10A4.unk50[var_r31], HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk50[var_r31], 1.0f);
                break;
            case 5:
                Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk18[var_r31], 0.0f);
                lbl_1_bss_E14[var_r31].unk8 = 6;
                lbl_1_bss_E14[var_r31].unk40 = 0;
                lbl_1_bss_E14[var_r31].unk3C = 0;
                lbl_1_bss_E14[var_r31].unk44 = 0;
                break;
            case 6:
                fn_1_64F4(var_r31, 5, 0);
                if (lbl_1_bss_E14[var_r31].unk44++ >= 0x32) {
                    if (lbl_1_bss_E14[var_r31].unkC.y > 0.0f) {
                        lbl_1_bss_E14[var_r31].unk8 = 7;
                    }
                    else {
                        lbl_1_bss_E14[var_r31].unk8 = 4;
                    }
                    lbl_1_bss_E14[var_r31].unk40 = 0;
                    lbl_1_bss_E14[var_r31].unk3C = 0;
                    lbl_1_bss_E14[var_r31].unk44 = 0;
                }
                break;
            case 7:
                if (lbl_1_bss_E14[var_r31].unkC.y > 0.0f) {
                    lbl_1_bss_E14[var_r31].unk28 -= 1.0f;
                }
                else if (lbl_1_bss_E14[var_r31].unkC.y < 0.0f) {
                    lbl_1_bss_E14[var_r31].unk28 = 0.0f;
                    lbl_1_bss_E14[var_r31].unkC.y = 0.0f;
                    lbl_1_bss_E14[var_r31].unk8 = 4;
                    omVibrate(var_r31, ((s32)(33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f))) / 2, 0xC, 0);
                    fn_1_7770(1 << var_r31, &lbl_1_bss_E14[var_r31].unkC);
                    if ((var_r31 % 2) == 0) {
                        M507FXPlayVol(0x67A, (s16)fn_1_668C(var_r31));
                    }
                    else {
                        M507FXPlayVol(0x67B, (s16)fn_1_668C(var_r31));
                    }
                    fn_1_64A4(var_r31, 0x1E, 33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f), 0.95f, 90.0f);
                }
                break;
            case 4:
                Hu3DMotionSpeedSet(lbl_1_bss_10A4.unk18[var_r31], 1.0f);
                fn_1_64F4(var_r31, 6, HU3D_MOTATTR_LOOP);
                lbl_1_bss_E14[var_r31].unk2C = 0.0f;
                if (lbl_1_bss_E14[var_r31].unkC.y > 0.0f) {
                    lbl_1_bss_E14[var_r31].unk8 = 5;
                    lbl_1_bss_E14[var_r31].unk44 = 0;
                }
                break;
        }
        lbl_1_bss_E14[var_r31].unkC.x += lbl_1_bss_E14[var_r31].unk24;
        lbl_1_bss_E14[var_r31].unkC.y += lbl_1_bss_E14[var_r31].unk28;
        lbl_1_bss_E14[var_r31].unkC.z += lbl_1_bss_E14[var_r31].unk2C;
        if (lbl_1_bss_E14[var_r31].unkC.z >= -300.0f) {
            lbl_1_bss_E14[var_r31].unk34 = 0;
            lbl_1_bss_E14[var_r31].unk3C = 0;
            lbl_1_bss_E14[var_r31].unk40 = 0;
            lbl_1_bss_E14[var_r31].unk2C = 0.0f;
            lbl_1_bss_E14[var_r31].unk8 = 3;
            if (lbl_1_bss_E14[var_r31].unk50 == 0) {
                omVibrate(var_r31, 0x3C, 0xC, 0);
            }
            lbl_1_bss_E14[var_r31].unk50 = 1;
            fn_1_64F4(var_r31, 7, HU3D_MOTATTR_LOOP);
        }
        var_r30->unk74 = fabs(300.0f + lbl_1_bss_E14[var_r31].unkC.z);
        Hu3DModelPosSet(
            lbl_1_bss_10A4.unk18[var_r31], lbl_1_bss_E14[var_r31].unkC.x, lbl_1_bss_E14[var_r31].unkC.y, lbl_1_bss_E14[var_r31].unkC.z - 50.0f);
        Hu3DModelPosSet(lbl_1_bss_10A4.unk58[var_r31], lbl_1_bss_E14[var_r31].unkC.x, 0.5f, lbl_1_bss_E14[var_r31].unkC.z - 50.0f);
        if (lbl_1_bss_E14[var_r31].unkC.y > 0.0f) {
            var_f31 = (300.0f - lbl_1_bss_E14[var_r31].unkC.y) / 300.0f;
        }
        else {
            var_f31 = 1.0f;
        }
        var_f31 += 0.5f;
        Hu3DModelScaleSet(lbl_1_bss_10A4.unk58[var_r31], var_f31, 1.0f, var_f31);
        fn_1_527C(var_r31);
    }
}

s16 fn_1_4EE4(s32 arg0, u32 arg1, u16 arg2, float var_f29, float var_f30, float var_f31, float arg7, float arg8, float arg9, s32 arg3)
{
    s32 var_r31;
    s32 i;
    s16 var_r28;

    for (i = 0, var_r31 = -1; i < 25; i++) {
        if (lbl_1_bss_4[i][arg0].unk18 == -1) {
            var_r31 = i;
            break;
        }
    }
    if (var_r31 == -1) {
        OSReport("==== Can't Entry EffObj playn:%d====\n", arg0);
        return -1;
    }
    lbl_1_bss_4[var_r31][arg0].unk20 = arg3;
    lbl_1_bss_4[var_r31][arg0].unk18 = Hu3DModelCreateFile(arg1);
    Hu3DModelAttrSet(lbl_1_bss_4[var_r31][arg0].unk18, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_4[var_r31][arg0].unk18, arg2);
    Hu3DModelPosSet(lbl_1_bss_4[var_r31][arg0].unk18, var_f29, var_f30, var_f31);
    Hu3DModelRotSet(lbl_1_bss_4[var_r31][arg0].unk18, 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_4[var_r31][arg0].unk18, 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_4[var_r31][arg0].unk18, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_4[var_r31][arg0].unk18, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(lbl_1_bss_4[var_r31][arg0].unk18, 0);
    lbl_1_bss_4[var_r31][arg0].unk0.x = var_f29;
    lbl_1_bss_4[var_r31][arg0].unk0.y = var_f30;
    lbl_1_bss_4[var_r31][arg0].unk0.z = var_f31;
    lbl_1_bss_4[var_r31][arg0].unkC.x = arg7;
    lbl_1_bss_4[var_r31][arg0].unkC.y = arg8;
    lbl_1_bss_4[var_r31][arg0].unkC.z = arg9;
    lbl_1_bss_4[var_r31][arg0].unk1C = 0;
    var_r28 = lbl_1_bss_4[var_r31][arg0].unk18;
    return var_r28;
}

void fn_1_527C(s32 arg0)
{
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 25; var_r30++) {
        if (lbl_1_bss_4[var_r30][arg0].unk18 != -1) {
            if (lbl_1_bss_4[var_r30][arg0].unk1C != 0) {
                if (Hu3DMotionEndCheck(lbl_1_bss_4[var_r30][arg0].unk18) == 0) {
                    lbl_1_bss_4[var_r30][arg0].unk0.x += lbl_1_bss_4[var_r30][arg0].unkC.x;
                    lbl_1_bss_4[var_r30][arg0].unk0.y += lbl_1_bss_4[var_r30][arg0].unkC.y;
                    lbl_1_bss_4[var_r30][arg0].unk0.z += lbl_1_bss_4[var_r30][arg0].unkC.z;
                    Hu3DModelPosSet(lbl_1_bss_4[var_r30][arg0].unk18, lbl_1_bss_4[var_r30][arg0].unk0.x, lbl_1_bss_4[var_r30][arg0].unk0.y,
                        lbl_1_bss_4[var_r30][arg0].unk0.z);
                }
                else {
                    lbl_1_bss_4[var_r30][arg0].unkC.x = 0.0f;
                    lbl_1_bss_4[var_r30][arg0].unkC.y = 0.0f;
                    lbl_1_bss_4[var_r30][arg0].unkC.z = 0.0f;
                }
            }
            else if ((300.0f + lbl_1_bss_E14[arg0].unkC.z) >= lbl_1_bss_4[var_r30][arg0].unk0.z) {
                Hu3DMotionSpeedSet(lbl_1_bss_4[var_r30][arg0].unk18, 1.0f);
                lbl_1_bss_4[var_r30][arg0].unk1C = 1;
                if (lbl_1_bss_4[var_r30][arg0].unk20 == 0) {
                    if ((arg0 % 2) == 0) {
                        M507FXPlayVol(0x67E, (s16)fn_1_668C(arg0));
                    }
                    else {
                        M507FXPlayVol(0x67F, (s16)fn_1_668C(arg0));
                    }
                }
                else {
                    if ((arg0 % 2) == 0) {
                        M507FXPlayVol(0x67C, (s16)fn_1_668C(arg0));
                    }
                    else {
                        M507FXPlayVol(0x67D, (s16)fn_1_668C(arg0));
                    }
                }
            }
        }
    }
}

void fn_1_562C(s32 var_r31, s32 var_r26)
{
    M507Struct1 *var_r29;
    s32 var_r30;
    s32 var_r28;
    s32 var_r27;
    float var_f31;
    float var_f30;
    float var_f29;
    float var_f28;

    var_r29 = lbl_1_bss_111C[var_r31]->data;
    var_r27 = lbl_1_bss_E14[var_r31].unk54;
    var_r30 = var_r29->unk84;
    if ((GWPlayerCfg[var_r29->unk0C].iscom != 0) && ((var_r30 == 2) || (var_r30 == 3))) {
        var_r28 = fn_1_60A0(var_r30, var_r27, 0);
    }
    else if (var_r26 == 2) {
        var_r28 = 0;
    }
    else {
        while (TRUE) {
            var_r28 = frandmod(5);
            if (var_r28 == 0) {
                if (var_r26 != 0) {
                    break;
                }
                continue;
            }
            else if (var_r28 == 1) {
                if (!(lbl_1_bss_E14[var_r31].unkC.z > -1000.0f)) {
                    break;
                }
                continue;
            }
            else if (var_r28 == 2) {
                if (lbl_1_bss_E14[var_r31].unkC.z > -800.0f) {
                    continue;
                }
            }
            break;
        }
    }
    lbl_1_bss_E14[var_r31].unk2C = 0.0f;
    lbl_1_bss_E14[var_r31].unk3C = 0;
    switch (var_r28) {
        case 0:
            lbl_1_bss_E14[var_r31].unk8 = 0;
            lbl_1_bss_E14[var_r31].unk30 = 0.0f;
            lbl_1_bss_E14[var_r31].unk40 = fn_1_6468(0x1E, 0x78);
            fn_1_64F4(var_r31, 0, HU3D_MOTATTR_LOOP);
            break;
        case 1:
            if ((GWPlayerCfg[var_r29->unk0C].iscom != 0) && ((var_r30 == 2) || (var_r30 == 3))) {
                lbl_1_bss_E14[var_r31].unk38 = (100.0f * fn_1_60A0(var_r30, var_r27, 1)) / 20.0f;
            }
            else {
                lbl_1_bss_E14[var_r31].unk38 = (100.0f * fn_1_6468(3, 5)) / 20.0f;
            }
            lbl_1_bss_E14[var_r31].unk8 = 2;
            lbl_1_bss_E14[var_r31].unk30 = 20.0f;
            lbl_1_bss_E14[var_r31].unk34 = 0;
            lbl_1_bss_E14[var_r31].unk40 = 0;
            lbl_1_bss_E14[var_r31].unk48 = 180.0f / lbl_1_bss_E14[var_r31].unk38;
            lbl_1_bss_E14[var_r31].unk4C = 0.0f;
            fn_1_64F4(var_r31, 2, HU3D_MOTATTR_LOOP);
            break;
        case 2:
            if ((GWPlayerCfg[var_r29->unk0C].iscom != 0) && ((var_r30 == 2) || (var_r30 == 3))) {
                lbl_1_bss_E14[var_r31].unk38 = (100.0f * fn_1_60A0(var_r30, var_r27, 1)) / 20.0f;
            }
            else {
                lbl_1_bss_E14[var_r31].unk38 = (100.0f * fn_1_6468(2, 5)) / 20.0f;
            }
            lbl_1_bss_E14[var_r31].unk8 = 1;
            lbl_1_bss_E14[var_r31].unk30 = 20.0f;
            lbl_1_bss_E14[var_r31].unk34 = 0;
            lbl_1_bss_E14[var_r31].unk40 = 0;
            fn_1_64F4(var_r31, 3, HU3D_MOTATTR_LOOP);
            break;
        case 3:
        case 4:
            lbl_1_bss_E14[var_r31].unk8 = 1;
            lbl_1_bss_E14[var_r31].unk38 = 0xA;
            lbl_1_bss_E14[var_r31].unk30 = 10.0f;
            lbl_1_bss_E14[var_r31].unk34 = 0;
            lbl_1_bss_E14[var_r31].unk40 = 0;
            fn_1_64F4(var_r31, 1, HU3D_MOTATTR_LOOP);
            break;
        case 5:
            lbl_1_bss_E14[var_r31].unk8 = 0;
            lbl_1_bss_E14[var_r31].unk30 = 0.0f;
            if ((GWPlayerCfg[var_r29->unk0C].iscom != 0) && ((var_r30 == 2) || (var_r30 == 3))) {
                lbl_1_bss_E14[var_r31].unk40 = fn_1_60A0(var_r30, var_r27, 1);
            }
            else {
                lbl_1_bss_E14[var_r31].unk40 = fn_1_6468(0x1E, 0x78);
            }
            fn_1_64F4(var_r31, 0, HU3D_MOTATTR_LOOP);
            break;
    }
    switch (var_r26) {
        case 2:
            omVibrate(var_r31, ((s32)(33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f))) / 2, 0xC, 0);
            fn_1_7770(1 << var_r31, &lbl_1_bss_E14[var_r31].unkC);
            if ((var_r31 % 2) == 0) {
                M507FXPlayVol(0x67A, (s16)fn_1_668C(var_r31));
            }
            else {
                M507FXPlayVol(0x67B, (s16)fn_1_668C(var_r31));
            }
            fn_1_64A4(var_r31, 0x1E, 33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f), 0.95f, 90.0f);
            break;
        case 1:
            omVibrate(var_r31, ((s32)(33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f))) / 2, 0xC, 0);
            fn_1_7770(1 << var_r31, &lbl_1_bss_E14[var_r31].unkC);
            if ((var_r31 % 2) == 0) {
                M507FXPlayVol(0x67A, (s16)fn_1_668C(var_r31));
            }
            else {
                M507FXPlayVol(0x67B, (s16)fn_1_668C(var_r31));
            }
            fn_1_64A4(var_r31, 0x1E, 33.0 - fabs(lbl_1_bss_E14[var_r31].unkC.z / 100.0f), 0.95f, 90.0f);
            break;
    }
    if (var_r28 != 5) {
        lbl_1_bss_E14[var_r31].unk54++;
    }
}

s32 fn_1_60A0(s32 arg0, s32 arg1, s32 arg2)
{
    s32 var_r31;

    switch (arg0) {
        case 3:
            var_r31 = lbl_1_data_F0[arg1][arg2];
            break;
        case 2:
            var_r31 = lbl_1_data_38[arg1][arg2];
            break;
    }
    return var_r31;
}

void fn_1_610C(float arg0, float arg1)
{
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, arg0 - 1.0f, arg1 - 1.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, arg0 - 1.0f, arg1 - 1.0f);
    Hu3DCameraViewportSet(2, 2.0f + arg0, 0.0f, 640.0f - arg0, arg1 - 1.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 2.0f + arg0, 0, 640.0f - arg0, arg1 - 1.0f);
    Hu3DCameraViewportSet(4, 0.0f, -20.0f + (2.0f + arg1), arg0 - 1.0f, 480.0f - arg1, 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 0, 2.0f + arg1, arg0 - 1.0f, 480.0f - arg1);
    Hu3DCameraViewportSet(8, 2.0f + arg0, -20.0f + (2.0f + arg1), 640.0f - arg0, 480.0f - arg1, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 2.0f + arg0, 2.0f + arg1, 640.0f - arg0, 480.0f - arg1);
}

u32 fn_1_6468(u32 arg0, u32 arg1)
{
    return arg0 + frandmod(arg1 - arg0);
}

void fn_1_64A4(s32 arg0, u16 arg1, float arg2, float arg3, float arg4)
{
    M507Struct1 *temp_r31;

    temp_r31 = lbl_1_bss_111C[arg0]->data;
    temp_r31->unk9C = arg1;
    temp_r31->unkA8 = arg2;
    temp_r31->unkAC = arg3;
    temp_r31->unkB4 = arg4;
    temp_r31->unkB0 = 90.0f;
}

void fn_1_64F4(s32 arg0, s32 arg1, u32 arg2)
{
    if (lbl_1_bss_E14[arg0].unk0 != arg1) {
        lbl_1_bss_E14[arg0].unk0 = arg1;
        Hu3DMotionShiftSet(lbl_1_bss_10A4.unk18[arg0], lbl_1_bss_F74[arg1][arg0], 0.0f, 8.0f, arg2);
    }
}

void fn_1_65AC(void)
{
    s32 var_r31;
    s32 var_r30;
    s32 var_r29;

    var_r30 = Hu3DMotionTimeGet(lbl_1_bss_10A4.unk8[0]);
    var_r29 = 0x77;
    if (var_r30 > 0 && var_r30 < var_r29) {
        for (var_r31 = 0; var_r31 < 14; var_r31++) {
            if (var_r30 == lbl_1_data_234[var_r31].unk0) {
                M507FXPlayVolPan(0x684, lbl_1_data_234[var_r31].unk6, lbl_1_data_234[var_r31].unk4);
                if (var_r31 == 0) {
                    lbl_1_data_0 = M507FXPlay(0x685);
                }
            }
        }
    }
}

s32 fn_1_668C(s32 arg0)
{
    float var_f31;
    s32 var_r31;

    var_r31 = 64.0 + (63.0 * ((3300.0 - fabs(lbl_1_bss_E14[arg0].unkC.z)) / 3300.0));
    if (arg0 == 0) {
        OSReport("VOL:%d PLAYN:%d\n", arg0, (s16)var_r31);
    }
    return var_r31;
}

void fn_1_6778(void)
{
    lbl_1_bss_1328.prev = NULL;
    lbl_1_bss_1328.next = NULL;
}

void fn_1_679C(u16 arg0, s16 arg1)
{
    M507ListNode *node;
    M507ListNode *head;
    M507ListNode *next;

    node = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M507ListNode), MEMORY_DEFAULT_NUM);
    node->unk0 = arg0;
    node->unk2 = arg1;
    head = &lbl_1_bss_1328;
    next = head->next;
    head->next = node;
    if (NULL != next) {
        next->prev = node;
    }
    node->prev = head;
    node->next = next;
}

s16 fn_1_6824(s16 arg0)
{
    M507ListNode *node;
    M507ListNode *next;
    M507ListNode *prev;
    s16 value;

    node = lbl_1_bss_1328.next;
    while (NULL != node) {
        if (arg0 == node->unk0) {
            value = node->unk2;
            prev = node->prev;
            next = node->next;
            prev->next = next;
            if (NULL != next) {
                next->prev = prev;
            }
            HuMemDirectFree(node);
            return value;
        }
        node = node->next;
    }
    return -1;
}

void fn_1_68C8(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_1120.entry[i].dataNum = 0;
        lbl_1_bss_1120.entry[i].modelId = -1;
    }
}

s16 fn_1_6920(u32 arg0)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (arg0 == lbl_1_bss_1120.entry[i].dataNum) {
            return Hu3DModelLink(lbl_1_bss_1120.entry[i].modelId);
        }
    }
    for (i = 0; i < 32; i++) {
        if (lbl_1_bss_1120.entry[i].dataNum == 0) {
            lbl_1_bss_1120.entry[i].dataNum = arg0;
            lbl_1_bss_1120.entry[i].modelId = Hu3DModelCreateFile(arg0);
            return lbl_1_bss_1120.entry[i].modelId;
        }
    }
    return Hu3DModelCreateFile(arg0);
}
