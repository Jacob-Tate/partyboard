// MP5 m529 (Handy Hoppers), generated from its m2c draft by tools/mp5/ports/m529dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m529dll (tools/mp5/decomp.py m529dll --types tools/mp5/types/m529dll.h)
// Written from the draft: Handy Hoppers (2 vs 2). Four hoppers (OMOBJ::data), a controller (lbl_1_bss_118,
// its work[0] is the phase 0x3E8..0x3F2) and a score display object (lbl_1_bss_110). Offsets are GameCube's.
// objdata: M529Player
// objdata ObjectSetup fn_1_5204 fn_1_553C fn_1_5680: M529Hud
// objexpr lbl_1_bss_110: M529Hud
// objexpr lbl_1_bss_11C: M529Player

typedef struct M529Player { // OMOBJ::data of lbl_1_bss_11C[4], 0xD0
    s32 unk0; // role: 0xBB8/0xBBA jumper (button A), 0xBB9/0xBBB flapper (L/R)
    s32 unk4; // motion slot
    s32 unk8; // mode 0x7D0..0x7D7
    s32 unkC; // jumper: 0 ground 1 hit 2 recover
    s32 unk10;
    s32 unk14; // player
    s32 unk18; // position / team slot 0..3
    s32 unk1C; // partner player
    s32 unk20; // partner's slot
    s32 unk24; // slot
    s32 unk28; // character
    s32 unk2C; // pad
    s32 unk30; // buttons held
    s32 unk34; // buttons pressed
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    f32 unk68; // speed
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    Vec unk84; // position
    Vec unk90; // velocity
    f32 unk9C;
    s32 unkA0;
    f32 unkA4; // y rotation
    f32 unkA8;
    Vec unkAC;
    s32 unkB8; // com difficulty
    s32 unkBC;
    s32 unkC0;
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
} M529Player;

typedef struct M529Hud { // lbl_1_bss_110->data, 0x1C
    s32 unk0;
    MGSCORE *unk4; // record
    MGSCORE *unk8; // team 0 score
    MGSCORE *unkC; // team 1 score
    s16 unk10;
    s16 unk12; // esp sprite
    s32 unk14;
    f32 unk18; // pulse scale
} M529Hud;

typedef struct M529Col { // GXColor
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} M529Col;

typedef struct M529Cache {
    u32 unk0;
    s16 unk4;
    char pad6[2];
} M529Cache;


void ObjectSetup(void);
void fn_1_5E0(OMOBJ *obj);
void fn_1_B98(OMOBJ *obj);
void fn_1_1780(OMOBJ *obj);
void fn_1_187C(OMOBJ *obj);
void fn_1_1C8C(OMOBJ *obj);
void fn_1_2714(OMOBJ *obj);
void fn_1_2B70(OMOBJ *obj);
void fn_1_2BEC(OMOBJ *obj);
void fn_1_4290(OMOBJ *obj);
void fn_1_4370(OMOBJ *obj);
s32 fn_1_444C(OMOBJ *obj);
s32 fn_1_4488(OMOBJ *obj);
void fn_1_44C4(OMOBJ *obj);
void fn_1_4780(OMOBJ *obj);
u16 fn_1_4F10(OMOBJ *obj);
u16 fn_1_500C(OMOBJ *obj);
u16 fn_1_5084(OMOBJ *obj);
u16 fn_1_5170(OMOBJ *obj);
s32 fn_1_51B4(s32 min, s32 max);
void fn_1_5204(OMOBJ *obj);
void fn_1_553C(OMOBJ *obj);
void fn_1_5680(s16 phase);
void fn_1_57BC(void);
s16 fn_1_5960(s16 slot);
s32 fn_1_59BC(s32 slot);
s16 fn_1_6334(s32 player);
void fn_1_63E4(void);
void ObjectSetup(void);
void fn_1_5E0(omObjData *obj);
void fn_1_B98(omObjData *obj);
void fn_1_1780(omObjData *obj);
void fn_1_187C(omObjData *obj);
void fn_1_1C8C(omObjData *obj);
void fn_1_2714(omObjData *obj);
void fn_1_2B70(omObjData *obj);
void fn_1_2BEC(omObjData *obj);
void fn_1_3CE0(void);
void fn_1_4048(void);
void fn_1_4290(omObjData *obj);
void fn_1_4370(omObjData *obj);
s32 fn_1_444C(omObjData *obj);
s32 fn_1_4488(omObjData *obj);
void fn_1_44C4(omObjData *obj);
void fn_1_4780(omObjData *obj);
u16 fn_1_4F10(omObjData *obj);
u16 fn_1_500C(omObjData *obj);
u16 fn_1_5084(omObjData *obj);
u16 fn_1_5170(omObjData *obj);
s32 fn_1_51B4(s32 min, s32 max);
void fn_1_5204(omObjData *obj);
void fn_1_553C(omObjData *obj);
void fn_1_5680(s16 phase);
void fn_1_57BC(void);
s16 fn_1_5960(s16 slot);
s32 fn_1_59BC(s32 slot);
s16 fn_1_6334(s32 player);
void fn_1_63E4(void);

extern s32 fontcolor;
s32 lbl_1_data_0 = -1;
M529Col lbl_1_data_4 = { 255, 255, 255, 255 };
u32 lbl_1_data_8[8] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MP5_MARIO, 67),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 56),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 58),
};
Vec lbl_1_data_28[4] = {
    { -470.0f, 0.0f, 300.0f },
    { -145.0f, 0.0f, 300.0f },
    { 145.0f, 0.0f, 300.0f },
    { 470.0f, 0.0f, 300.0f },
};
Vec lbl_1_data_58[4] = {
    { -265.0f, 0.0f, 500.0f },
    { -115.0f, 0.0f, 500.0f },
    { 115.0f, 0.0f, 500.0f },
    { 265.0f, 0.0f, 500.0f },
};
Vec lbl_1_data_88[4] = {
    { -470.0f, 250.0f, 300.0f },
    { -145.0f, 0.0f, 300.0f },
    { 145.0f, 250.0f, 300.0f },
    { 470.0f, 0.0f, 300.0f },
};
Vec lbl_1_data_B8[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 270.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 270.0f, 0.0f },
};
Vec lbl_1_data_E8[2] = { { -470.0f, 0.0f, 300.0f }, { 145.0f, 0.0f, 300.0f } };
Vec lbl_1_data_100 = { 0.0f, 4.0f, 200.0f };
Vec lbl_1_data_10C = { -1300.0f, -350.0f, -2500.0f };
Vec lbl_1_data_118 = { 0.0f, 30.0f, 0.0f };
Vec lbl_1_data_124[4] = {
    { -600.0f, 600.0f, 600.0f },
    { 0.0f, 600.0f, 600.0f },
    { 0.0f, 0.0f, 600.0f },
    { -600.0f, 0.0f, 600.0f },
};
Vec lbl_1_data_154[4] = {
    { 0.0f, 600.0f, 600.0f },
    { 600.0f, 600.0f, 600.0f },
    { 600.0f, 0.0f, 600.0f },
    { 0.0f, 0.0f, 600.0f },
};
Vec lbl_1_data_184[4] = {
    { -350.0f, 200.0f, 600.0f },
    { 0.0f, 200.0f, 600.0f },
    { 0.0f, 50.0f, 600.0f },
    { -350.0f, 50.0f, 600.0f },
};
Vec lbl_1_data_1B4[4] = {
    { 0.0f, -135.0f, 0.0f },
    { 0.0f, 135.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, -45.0f, 0.0f },
};
Vec lbl_1_data_1E4[4] = {
    { 0.0f, 200.0f, 600.0f },
    { 350.0f, 200.0f, 600.0f },
    { 350.0f, 50.0f, 600.0f },
    { 0.0f, 50.0f, 600.0f },
};
Vec lbl_1_data_214[4] = {
    { 0.0f, -135.0f, 0.0f },
    { 0.0f, 135.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, -45.0f, 0.0f },
};
s32 lbl_1_data_244[0xE] = {
    DATA_MAKE_NUM(DATADIR_MP5_M529, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M529, 12),
};
Vec lbl_1_data_27C[2] = { { 0.0f, 10.0f, -100.0f }, { 0.0f, 1.0f, 0.0f } };
Vec lbl_1_data_294 = { -210.0f, 120.0f, -500.0f };
Vec lbl_1_data_2A0[2] = { { 0.0f, 500.0f, 1720.0f }, { 0.0f, 1.0f, 0.0f } };
Vec lbl_1_data_2B8 = { 0.0f, 200.0f, -500.0f };
Vec lbl_1_data_2C4[2] = { { 1618.0f, 1121.0f, 2276.0f }, { 0.0f, 1.0f, 0.0f } };
Vec lbl_1_data_2DC = { -100.0f, 200.0f, 300.0f };
Vec lbl_1_data_2E8[2] = { { 0.0f, 919.0f, 2529.0f }, { 0.0f, 1.0f, 0.0f } };
Vec lbl_1_data_300 = { 0.0f, 50.0f, -100.0f };
OMCAMERAVIEW lbl_1_data_30C = { { -150.0f, 120.0f, -500.0f }, { 0.0f, 11.4f, 0.0f }, 465.0f };
OMCAMERAVIEW lbl_1_data_328 = { { 0.0f, 200.0f, -500.0f }, { -7.7f, -0.0f, 0.0f }, 2240.2f };
OMCAMERAVIEW lbl_1_data_344 = { { -100.0f, 200.0f, 300.0f }, { -19.4f, 41.0f, 0.0f }, 2775.7f };
OMCAMERAVIEW lbl_1_data_360 = { { 0.0f, 50.0f, -100.0f }, { -18.3f, -0.0f, 0.0f }, 2768.9f };
Vec lbl_1_data_37C = { 0.0f, 4000.0f, 6000.0f };
Vec lbl_1_data_388 = { 0.0f, 0.0f, 0.0f };
Vec lbl_1_data_398 = { 0.0f, 4000.0f, 300.0f };
Vec lbl_1_data_3A4 = { 0.0f, 1.0f, 0.0f };
Vec lbl_1_data_3B0 = { 0.0f, 0.0f, 0.0f };
static s8 lbl_1_data_3E0[0x20] = {
    0x2A,
    0x2A,
    0x2A,
    0x20,
    0x70,
    0x6C,
    0x61,
    0x79,
    0x65,
    0x72,
    0x20,
    0x6D,
    0x6F,
    0x64,
    0x65,
    0x20,
    0x65,
    0x72,
    0x72,
    0x6F,
    0x72,
    0x28,
    0x25,
    0x64,
    0x29,
    0x21,
    0x21,
    0xA,
    0,
    0,
    0,
    0,
};
static s8 lbl_1_data_424[0x1C] = {
    0x2A,
    0x2A,
    0x2A,
    0x20,
    0x6D,
    0x61,
    0x69,
    0x6E,
    0x20,
    0x6D,
    0x6F,
    0x64,
    0x65,
    0x20,
    0x65,
    0x72,
    0x72,
    0x6F,
    0x72,
    0x28,
    0x25,
    0x64,
    0x29,
    0x21,
    0x21,
    0xA,
    0,
    0,
};
s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s32 lbl_1_bss_C;
s32 lbl_1_bss_10;
MGTIMER *lbl_1_bss_14;
u32 lbl_1_bss_18;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_20[2];
s32 lbl_1_bss_28;
s32 lbl_1_bss_2C;
s16 lbl_1_bss_30;
s16 lbl_1_bss_32;
s16 lbl_1_bss_34;
f32 lbl_1_bss_38;
f32 lbl_1_bss_3C;
s16 lbl_1_bss_40;
f32 lbl_1_bss_44[4];
Vec lbl_1_bss_54[4];
s16 lbl_1_bss_84[4];
f32 lbl_1_bss_8C[4];
Vec lbl_1_bss_9C[4];
s16 lbl_1_bss_CC[4];
s32 lbl_1_bss_D4;
s16 lbl_1_bss_D8;
s32 lbl_1_bss_DC;
s32 lbl_1_bss_E0;
s32 lbl_1_bss_E4;
s32 lbl_1_bss_E8;
s16 lbl_1_bss_EC[0xE];
f32 lbl_1_bss_108;
omObjData *lbl_1_bss_10C;
omObjData *lbl_1_bss_110;
omObjData *lbl_1_bss_114;
omObjData *lbl_1_bss_118;
omObjData **lbl_1_bss_11C;
f32 lbl_1_bss_220;
s32 lbl_1_bss_228;
s16 lbl_1_bss_22C;
s16 lbl_1_bss_22E;
s32 lbl_1_bss_230;
Vec lbl_1_bss_2F4;
Vec lbl_1_bss_30C;
HUPROCESS *lbl_1_bss_324;



static s16 Mp5Slot(s16 player)
{
    s16 i, slot = 0;
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].group < GWPlayerCfg[player].group || (GWPlayerCfg[i].group == GWPlayerCfg[player].group && i < player)) {
            slot++;
        }
    }
    return slot;
}

void ObjectSetup(void) {
    omObjData *temp_r3;
    s32 var_r31;

    lbl_1_bss_22E = -1;
    lbl_1_bss_22C = -1;
    lbl_1_bss_228 = -1;
    lbl_1_bss_20[0] = 0;
    lbl_1_bss_20[1] = 0;
    lbl_1_bss_1C = -1;
    lbl_1_bss_DC = 0;
    OSReport("******* M529 ObjectSetup *********\n");
    lbl_1_bss_324 = omInitObjMan(0xC8, 0x2000);
    omGameSysInit(lbl_1_bss_324);
    lbl_1_bss_230 = 0;
    lbl_1_bss_18 = GWMgRecordGet(6);
    lbl_1_bss_220 = -1.0f;
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f);
    omCameraViewSet(&lbl_1_data_30C);
    lbl_1_bss_10C = omAddObjEx(lbl_1_bss_324, 0x7FDA, 0U, 0U, -1, omOutView);
    lbl_1_bss_10C->work[0] = 1;
    lbl_1_bss_28 = (s32) Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0U, 0U, 0U);
    Hu3DGLightPosAimSetV((s16) lbl_1_bss_28, &lbl_1_data_37C, &lbl_1_data_388);
    Hu3DGLightStaticSet((s16) lbl_1_bss_28, 1);
    Hu3DGLightColorSet((s16) lbl_1_bss_28, lbl_1_data_4.unk0, lbl_1_data_4.unk1, lbl_1_data_4.unk2, lbl_1_data_4.unk3);
    Hu3DGLightInfinitytSet((s16) lbl_1_bss_28);
    Hu3DShadowCreate(20.0f, 20.0f, 30000.0f);
    Hu3DShadowColSet(0U, 0U, 0x40U);
    Hu3DShadowTPLvlSet(0.8f);
    Hu3DShadowPosSet(&lbl_1_data_398, &lbl_1_data_3A4, &lbl_1_data_3B0);
    omMakeGroupEx(lbl_1_bss_324, 0U, 4U);
    lbl_1_bss_11C = omGetGroupMemberListEx(lbl_1_bss_324, 0);
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        temp_r3 = omAddObjEx(lbl_1_bss_324, 0x64, 1U, 8U, 0, fn_1_5E0);
        lbl_1_bss_11C[var_r31] = temp_r3;
        temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0xD0, MEMORY_DEFAULT_NUM);
        temp_r3->work[0] = (u32) var_r31;
        var_r31 += 1;
        goto loop_2;
    }
    lbl_1_bss_118 = omAddObjEx(lbl_1_bss_324, 0x65, 0xEU, 0U, -1, fn_1_1C8C);
    lbl_1_bss_118->work[0] = 0x3E8;
    lbl_1_bss_114 = omAddObjEx(lbl_1_bss_324, 0x67, 8U, 0U, -1, fn_1_2714);
    lbl_1_bss_114->work[0] = 0;
    lbl_1_bss_114->work[1] = 0;
    lbl_1_bss_108 = 0.0f;
    lbl_1_bss_110 = omAddObjEx(lbl_1_bss_324, 0x66, 0U, 0U, -1, fn_1_5204);
    lbl_1_bss_14 = MgTimerCreate(0);
    MgTimerParamSet(lbl_1_bss_14, 0x708, 0, 0);
    lbl_1_bss_10 = -1;
    lbl_1_bss_C = -1;
    lbl_1_bss_8 = -1;
}

void fn_1_5E0(omObjData *obj) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    s16 temp_r0;
    s32 temp_r0_2;
    s32 var_r29;
    s32 var_r29_2;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk14 = (u32) obj->work[0];
    temp_r31->unk28 = (s32) GWPlayerCfg[temp_r31->unk14].character;
    temp_r0 = Mp5Slot(temp_r31->unk14);
    temp_r31->unk24 = (s32) temp_r0;
    temp_r31->unk18 = (s32) temp_r0;
    temp_r31->unk2C = (s32) GWPlayerCfg[temp_r31->unk14].pad_idx;
    temp_r31->unk8 = 0x7D0;
    temp_r31->unkC = 0;
    temp_r31->unk4 = 0;
    temp_r31->unk10 = 0;
    temp_r31->unk38 = 0;
    temp_r31->unk3C = 0;
    temp_r31->unk40 = 0;
    temp_r31->unk44 = 0;
    temp_r31->unk48 = 0;
    temp_r31->unk4C = 0;
    temp_r31->unk50 = 0x1E;
    temp_r31->unk54 = 0;
    temp_r31->unk58 = 0;
    temp_r31->unk5C = 0;
    temp_r31->unk60 = 0;
    temp_r31->unk64 = 0;
    temp_r31->unk68 = 0.0f;
    temp_r31->unk7C = -1;
    temp_r31->unk80 = 0;
    temp_r31->unkAC.z = 0.0f;
    temp_r31->unkAC.y = 0.0f;
    temp_r31->unkAC.x = 0.0f;
    temp_r31->unk90.z = 0.0f;
    temp_r31->unk90.y = 0.0f;
    temp_r31->unk90.x = 0.0f;
    temp_r31->unk74 = 0x3C;
    temp_r31->unk70 = 0x3C;
    temp_r31->unk78 = 0;
    temp_r31->unk6C = 0;
    switch ((s32) temp_r31->unk18) {                /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        temp_r31->unk0 = 0xBB8;
        temp_r31->unk20 = 1;
        break;
    case 1:                                         /* switch 1 */
        temp_r31->unk0 = 0xBB9;
        temp_r31->unk20 = 0;
        break;
    case 2:                                         /* switch 1 */
        temp_r31->unk0 = 0xBBA;
        temp_r31->unk20 = 3;
        break;
    case 3:                                         /* switch 1 */
        temp_r31->unk0 = 0xBBB;
        temp_r31->unk20 = 2;
        break;
    }
    var_r29 = 0;
loop_13:
    if (var_r29 < 4) {
        if ((var_r29 != (s32) temp_r31->unk14) && ((s32) temp_r31->unk20 == (s16) Mp5Slot(var_r29))) {
            temp_r31->unk1C = var_r29;
        } else {
            var_r29 += 1;
            goto loop_13;
        }
    }
    temp_r31->unkB8 = (s32) GWPlayerCfg[temp_r31->unk14].diff;
    temp_r31->unkC4 = 0;
    temp_r0_2 = temp_r31->unkB8;
    switch (temp_r0_2) {                            /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        temp_r31->unkC8 = 0x23;
        temp_r31->unkCC = 0x37;
        temp_r31->unkC4 = (s32) temp_r31->unkC8;
        temp_r31->unkC0 = 0xA;
        temp_r31->unkBC = 0xA;
        break;
    case 1:                                         /* switch 2 */
        temp_r31->unkC8 = 0x14;
        temp_r31->unkCC = 0x32;
        temp_r31->unkC4 = (s32) temp_r31->unkC8;
        temp_r31->unkC0 = 0x14;
        temp_r31->unkBC = 5;
        break;
    case 2:                                         /* switch 2 */
        temp_r31->unkC8 = 8;
        temp_r31->unkCC = 0x28;
        temp_r31->unkC4 = (s32) temp_r31->unkC8;
        temp_r31->unkC0 = 0xF;
        temp_r31->unkBC = 0x28;
        break;
    case 3:                                         /* switch 2 */
        temp_r31->unkC8 = 1;
        temp_r31->unkCC = 0x19;
        temp_r31->unkC4 = (s32) temp_r31->unkC8;
        temp_r31->unkC0 = 0x32;
        temp_r31->unkBC = 0x32;
        break;
    }
    *obj->model = CharModelCreate((s16) temp_r31->unk28, 2);
    Hu3DModelShadowSet(*obj->model);
    CharModelStepFxSet((s16) temp_r31->unk28, 0);
    var_r29_2 = 0;
loop_27:
    if (var_r29_2 < 8) {
        obj->motion[var_r29_2] = Mp5CharMotionCreateData((s16) temp_r31->unk28, lbl_1_data_8[var_r29_2], 0 /* TODO(mp5): MP4 motion for DK */);
        CharMotionSet((s16) temp_r31->unk28, obj->motion[var_r29_2]);
        var_r29_2 += 1;
        goto loop_27;
    }
    CharModelAttrSet((s16) temp_r31->unk28, 1U);
    CharModelAttrSet((s16) temp_r31->unk28, 0x40000001U);
    Hu3DModelLayerSet(*obj->model, 3);
    CharMotionSet((s16) temp_r31->unk28, obj->motion[0]);
    CharEffectLayerSet(2);
    if (((s32) temp_r31->unk0 == 0xBB8) || ((s32) temp_r31->unk0 == 0xBBA)) {
        temp_r31->unkA4 = 0.0f;
    } else {
        temp_r31->unkA4 = 270.0f;
        CharMotionSet((s16) temp_r31->unk28, obj->motion[6]);
        CharMotionSpeedSet((s16) temp_r31->unk28, 0.0f);
        CharMotionTimeSet((s16) temp_r31->unk28, 0.0f);
    }
    temp_r31->unkA8 = 0.0f;
    temp_r31->unk84.x = 0.0f;
    temp_r31->unk84.y = 0.0f;
    temp_r31->unk84.z = 0.0f;
    temp_r31->unk9C = 0.0f;
    temp_f0 = lbl_1_data_28[temp_r31->unk18].x;
    temp_r31->unk84.x = temp_f0;
    obj->trans.x = temp_f0;
    temp_f0_2 = lbl_1_data_28[temp_r31->unk18].y;
    temp_r31->unk84.y = temp_f0_2;
    obj->trans.y = temp_f0_2;
    temp_f0_3 = lbl_1_data_28[temp_r31->unk18].z;
    temp_r31->unk84.z = temp_f0_3;
    obj->trans.z = temp_f0_3;
    omSetTra(obj, temp_r31->unk84.x, temp_r31->unk84.y, temp_r31->unk84.z);
    omSetRot(obj, 0.0f, temp_r31->unkA4, 0.0f);
    CharModelAttrReset((s16) temp_r31->unk28, 1U);
    CharMotionDataClose((s16) temp_r31->unk28);
    obj->func = fn_1_B98;
}

void fn_1_B98(omObjData *obj) {
    Vec sp20;
    Vec sp14;
    Vec sp8;
    f32 temp_f26;
    f32 temp_f27;
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 temp_r3;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    temp_r3 = temp_r31->unk8;
    switch (temp_r3) {
    case 0x7D0:
        if ((u32) lbl_1_bss_118->work[0] >= 0x3ECU) {
            temp_r31->unk8 = (s32) (temp_r31->unk8 + 1);
        }
        break;
    case 0x7D1:
        if ((u32) lbl_1_bss_118->work[0] == 0x3EC) {
            if (((s32) temp_r31->unk0 == 0xBB8) || ((s32) temp_r31->unk0 == 0xBBA)) {
                if ((s16) GWPlayerCfg[temp_r31->unk14].iscom != 0) {
                    temp_r31->unk30 = (s32) fn_1_500C(obj);
                    temp_r31->unk34 = (s32) fn_1_4F10(obj);
                } else {
                    temp_r31->unk30 = (s32) HuPadBtn[temp_r31->unk2C];
                    temp_r31->unk34 = (s32) HuPadBtnDown[temp_r31->unk2C];
                }
                fn_1_187C(obj);
            } else {
                if ((s16) GWPlayerCfg[temp_r31->unk14].iscom != 0) {
                    temp_r31->unk34 = 0;
                    temp_r31->unk34 = (s32) fn_1_5084(obj);
                } else {
                    temp_r31->unk34 = 0;
                    temp_r31->unk34 = (s32) HuPadBtnDown[temp_r31->unk2C];
                }
                if ((((s32) (temp_r31->unk34 & 0x40) == 0) || ((s32) (temp_r31->unk34 & 0x20) == 0)) && ((s32) temp_r31->unk34 != 0)) {
                    if ((s32) (temp_r31->unk34 & 0x40) != 0) {
                        if (((s32) temp_r31->unk7C == 1) || ((s32) temp_r31->unk7C == -1)) {
                            temp_r31->unk74 = (s32) (lbl_1_bss_E8 - temp_r31->unk78);
                            temp_r31->unk78 = (s32) lbl_1_bss_E8;
                            temp_r31->unk7C = 0;
                            fn_1_1780(obj);
                        }
                    } else if (((s32) (temp_r31->unk34 & 0x20) != 0) && (((s32) temp_r31->unk7C == 0) || ((s32) temp_r31->unk7C == -1))) {
                        temp_r31->unk74 = (s32) (lbl_1_bss_E8 - temp_r31->unk78);
                        temp_r31->unk78 = (s32) lbl_1_bss_E8;
                        temp_r31->unk7C = 1;
                        fn_1_1780(obj);
                    }
                }
                if ((s32) (lbl_1_bss_E8 - temp_r31->unk78) >= 0x3D) {
                    temp_r31->unk80 = 1;
                }
                fn_1_4780(obj);
            }
        }
        if ((u32) lbl_1_bss_118->work[0] >= 0x3EDU) {
            temp_r31->unk8 = 0x7D2;
        }
        break;
    case 0x7D2:
        if (((s32) temp_r31->unk0 == 0xBB8) || ((s32) temp_r31->unk0 == 0xBBA)) {
            CharModelAttrReset((s16) temp_r31->unk28, 1U);
            if (fn_1_444C(obj) != 0) {
                fn_1_44C4(obj);
            }
            if ((s32) temp_r31->unk4 != 0) {
                temp_r31->unk4 = 0;
                CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0x40000001U);
            }
        } else if (fn_1_4488(obj) != 0) {
            fn_1_4780(obj);
        } else if ((s32) temp_r31->unk0 == 0xBB9) {
            if ((s32) lbl_1_bss_10 != -1) {
                HuAudFXStop(lbl_1_bss_10);
                lbl_1_bss_10 = -1;
            }
        } else if ((s32) lbl_1_bss_C != -1) {
            HuAudFXStop(lbl_1_bss_C);
            lbl_1_bss_C = -1;
        }
        if ((u32) lbl_1_bss_118->work[0] >= 0x3EEU) {
            temp_r31->unk8 = 0x7D3;
            temp_r31->unk4 = 0;
            CharMotionShiftSet((s16) temp_r31->unk28, *obj->motion, 0.0f, 8.0f, 0x40000001U);
        }
        break;
    case 0x7D3:
        temp_f27 = temp_r31->unkA4;
        var_f31 = (f32) fmod((f64) (0.0f - temp_f27), 360.0);
        if (var_f31 < 0.0f) {
            var_f31 += 360.0f;
        }
        if (var_f31 > 180.0f) {
            var_f31 -= 360.0f;
        }
        var_f29 = (f32) fmod((f64) (temp_f27 + (var_f31 * 0.5f)), 360.0);
        if (var_f29 < 0.0f) {
            var_f29 += 360.0f;
        }
        temp_r31->unkA4 = var_f29;
        if ((u32) lbl_1_bss_118->work[0] >= 0x3EFU) {
            temp_r31->unk8 = 0x7D4;
        }
        break;
    case 0x7D4:
        if ((s32) temp_r31->unk4 != 2) {
            temp_r31->unk4 = 2;
            CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0x40000001U);
        }
        if ((u32) lbl_1_bss_118->work[0] == 0x3F0) {
            temp_r31->unk8 = 0x7D5;
            temp_r31->unk4 = 0;
            CharMotionShiftSet((s16) temp_r31->unk28, *obj->motion, 0.0f, 8.0f, 0x40000001U);
        } else if ((u32) lbl_1_bss_118->work[0] == 0x3F1) {
            temp_r31->unk8 = 0x7D6;
            temp_r31->unk4 = 0;
            CharMotionShiftSet((s16) temp_r31->unk28, *obj->motion, 0.0f, 8.0f, 0x40000001U);
        } else {
            temp_r31->unkAC.x = (f32) ((lbl_1_data_58[temp_r31->unk18].x - lbl_1_data_28[temp_r31->unk18].x) / 80.0f);
            temp_r31->unkAC.y = (f32) ((lbl_1_data_58[temp_r31->unk18].y - lbl_1_data_28[temp_r31->unk18].y) / 80.0f);
            temp_r31->unkAC.z = (f32) ((lbl_1_data_58[temp_r31->unk18].z - lbl_1_data_28[temp_r31->unk18].z) / 80.0f);
            temp_r31->unk84.x = (f32) (temp_r31->unk84.x + temp_r31->unkAC.x);
            temp_r31->unk84.y = (f32) (temp_r31->unk84.y + temp_r31->unkAC.y);
            temp_r31->unk84.z = (f32) (temp_r31->unk84.z + temp_r31->unkAC.z);
        }
        break;
    case 0x7D5:
        if ((u32) lbl_1_bss_118->work[0] == 0x3F1) {
            temp_r31->unk8 = 0x7D6;
        }
        break;
    case 0x7D6:
        if ((u32) lbl_1_bss_118->work[0] >= 0x3F1U) {
            temp_r31->unk8 = 0x7D7;
            if (((s32) temp_r31->unk0 == 0xBB9) || ((s32) temp_r31->unk0 == 0xBB8)) {
                if ((s32) lbl_1_bss_1C == 0) {
                    temp_r31->unk4 = 4;
                    if ((s32) lbl_1_bss_4 == -1) {
                        lbl_1_bss_4 = HuAudFXPlay(0x794);
                    }
                } else {
                    temp_r31->unk4 = 5;
                    if (((s32) lbl_1_bss_1C == 2) && ((s32) temp_r31->unk14 == 0)) {
                        Hu3D3Dto2D(&temp_r31->unk84, 1, &sp20);
                        CharFXPlayPan((s16) temp_r31->unk28, 0x200, (s16) (32.0f + ((sp20.x / 576.0f) * 64.0f)));
                    }
                }
                CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0U);
            } else {
                if ((s32) lbl_1_bss_1C == 1) {
                    temp_r31->unk4 = 4;
                    if ((s32) lbl_1_bss_0 == -1) {
                        lbl_1_bss_0 = HuAudFXPlay(0x795);
                    }
                } else {
                    temp_r31->unk4 = 5;
                    if ((s32) lbl_1_bss_1C == 2) {
                        Hu3D3Dto2D(&temp_r31->unk84, 1, &sp14);
                        CharFXPlayPan((s16) temp_r31->unk28, 0x200, (s16) (32.0f + ((sp14.x / 576.0f) * 64.0f)));
                    }
                }
                CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0U);
            }
        }
        break;
    case 0x7D7:
        temp_f26 = temp_r31->unkA4;
        var_f30 = (f32) fmod((f64) (0.0f - temp_f26), 360.0);
        if (var_f30 < 0.0f) {
            var_f30 += 360.0f;
        }
        if (var_f30 > 180.0f) {
            var_f30 -= 360.0f;
        }
        var_f28 = (f32) fmod((f64) (temp_f26 + (var_f30 * 0.4f)), 360.0);
        if (var_f28 < 0.0f) {
            var_f28 += 360.0f;
        }
        temp_r31->unkA4 = var_f28;
        break;
    default:
        OSReport(lbl_1_data_3E0, temp_r31->unk8);
        break;
    }
    if ((s32) temp_r31->unk8 > 0x7D2) {
        Hu3D3Dto2D(&temp_r31->unk84, 1, &sp8);
        CharModelVoicePanSet((s16) temp_r31->unk28, (s16) (32.0f + ((sp8.x / 576.0f) * 64.0f)));
    }
    omSetTra(obj, temp_r31->unk84.x, temp_r31->unk84.y, temp_r31->unk84.z);
    omSetRot(obj, 0.0f, temp_r31->unkA4, 0.0f);
}

void fn_1_1780(omObjData *obj) {
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if (((s32) temp_r31->unk74 >= 1) && ((s32) temp_r31->unk74 <= 7)) {
        temp_r31->unk80 = 5;
        temp_r31->unk54 = 1;
    } else if (((s32) temp_r31->unk74 >= 8) && ((s32) temp_r31->unk74 <= 0x14)) {
        temp_r31->unk80 = 4;
        temp_r31->unk54 = 1;
    } else if (((s32) temp_r31->unk74 >= 0x15) && ((s32) temp_r31->unk74 <= 0x28)) {
        temp_r31->unk80 = 3;
        temp_r31->unk54 = 1;
    } else if (((s32) temp_r31->unk74 >= 0x29) && ((s32) temp_r31->unk74 <= 0x3B)) {
        temp_r31->unk80 = 2;
        temp_r31->unk54 = 1;
    } else {
        temp_r31->unk80 = 1;
        temp_r31->unk54 = 0;
    }
    if (((s32) temp_r31->unk80 != 1) && ((s32) temp_r31->unk64 >= (s32) temp_r31->unk70)) {
        temp_r31->unk60 = 0;
    }
}

void fn_1_187C(omObjData *obj) {
    Vec sp14;
    Vec sp8;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if (((s32) temp_r31->unkC == 0) || ((s32) temp_r31->unkC == 2)) {
        if ((s32) temp_r31->unkC == 2) {
            temp_r31->unk10 = (s32) (temp_r31->unk10 + 1);
            if ((s32) temp_r31->unk10 > 0x78) {
                temp_r31->unkC = 0;
                temp_r31->unk10 = 0;
            }
        }
        if (((s32) (temp_r31->unk34 & 0x100) != 0) && ((s32) temp_r31->unk40 == 0)) {
            temp_r31->unk3C = 1;
        }
        fn_1_44C4(obj);
    } else if ((s32) temp_r31->unkC == 1) {
        if ((s32) temp_r31->unk4 != 7) {
            temp_r31->unk4 = 7;
            CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0x40000001U);
            if ((s32) temp_r31->unk0 == 0xBB8) {
                Hu3DMotionTimeSet(lbl_1_bss_EC[0xB], 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_EC[0xB], 1.0f);
                HuAudFXPlay(0x792);
                Hu3D3Dto2D(&temp_r31->unk84, 1, &sp14);
                CharFXPlayPan((s16) temp_r31->unk28, 0x1FD, (s16) (32.0f + ((sp14.x / 576.0f) * 64.0f)));
            } else {
                Hu3DMotionTimeSet(lbl_1_bss_EC[0xC], 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_EC[0xC], 1.0f);
                HuAudFXPlay(0x793);
                Hu3D3Dto2D(&temp_r31->unk84, 1, &sp8);
                CharFXPlayPan((s16) temp_r31->unk28, 0x1FD, (s16) (32.0f + ((sp8.x / 576.0f) * 64.0f)));
            }
            omVibrate((s16) temp_r31->unk14, 0xC, 0xC, 0);
        }
        temp_r31->unk10 = (s32) (temp_r31->unk10 + 1);
        if ((s32) temp_r31->unk10 > 0x1E) {
            temp_r31->unkC = 2;
            temp_r31->unk10 = 0;
            if ((s32) temp_r31->unk4 != 0) {
                temp_r31->unk4 = 0;
                CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0x40000001U);
            }
        }
    }
    if (((s32) temp_r31->unkC == 1) || ((s32) temp_r31->unkC == 2)) {
        temp_r31->unk4C = (s32) (temp_r31->unk4C + 1);
        if ((s32) (temp_r31->unk4C & 1) == 0) {
            CharModelAttrSet((s16) temp_r31->unk28, 1U);
        } else {
            CharModelAttrReset((s16) temp_r31->unk28, 1U);
        }
        if ((s32) temp_r31->unk0 == 0xBB8) {
            if (Hu3DMotionEndCheck(0xB) != 0) {
                Hu3DMotionSpeedSet(lbl_1_bss_EC[0xB], 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_EC[0xB], 0.0f);
            }
        } else if (Hu3DMotionEndCheck(0xC) != 0) {
            Hu3DMotionSpeedSet(lbl_1_bss_EC[0xC], 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_EC[0xC], 0.0f);
        }
    } else {
        temp_r31->unk4C = 0;
        CharModelAttrReset((s16) temp_r31->unk28, 1U);
    }
}

void fn_1_1C8C(omObjData *obj) {
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;
    s32 var_r31_6;

    lbl_1_bss_EC[5] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_EC[5], 1U);
    Hu3DModelAttrSet(lbl_1_bss_EC[5], 0x40000001U);
    Hu3DModelPosSet(lbl_1_bss_EC[5], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_EC[5], 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_EC[5], 0.02f);
    lbl_1_bss_EC[6] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_EC[6], 1U);
    Hu3DModelAttrSet(lbl_1_bss_EC[6], 0x40000001U);
    Hu3DModelRotSet(lbl_1_bss_EC[6], lbl_1_data_118.x, lbl_1_data_118.y, lbl_1_data_118.z);
    Hu3DModelPosSet(lbl_1_bss_EC[6], lbl_1_data_10C.x, lbl_1_data_10C.y, lbl_1_data_10C.z);
    lbl_1_bss_EC[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_EC[0], 1U);
    Hu3DModelLayerSet(lbl_1_bss_EC[0], 0);
    Hu3DMotionSpeedSet(lbl_1_bss_EC[0], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_EC[0], 0.0f);
    Hu3DModelShadowMapSet(lbl_1_bss_EC[0]);
    Hu3DModelPosSet(lbl_1_bss_EC[0], lbl_1_data_100.x, lbl_1_data_100.y, lbl_1_data_100.z);
    Hu3DModelRotSet(lbl_1_bss_EC[0], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_2C = (s32) Hu3DMotionMaxTimeGet(lbl_1_bss_EC[0]);
    lbl_1_bss_E4 = 0;
    lbl_1_bss_E0 = lbl_1_bss_2C;
    lbl_1_bss_D8 = Hu3DJointMotion(lbl_1_bss_EC[0], HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M529, 11), MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_D4 = 0;
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        lbl_1_bss_EC[var_r31 + 7] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[var_r31 + 7], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelShadowMapSet(lbl_1_bss_EC[var_r31 + 7]);
        Hu3DModelAttrSet(lbl_1_bss_EC[var_r31 + 7], 1U);
        Hu3DModelLayerSet(lbl_1_bss_EC[var_r31 + 7], 1);
        Hu3DModelPosSet(lbl_1_bss_EC[var_r31 + 7], lbl_1_data_E8[var_r31].x, lbl_1_data_E8[var_r31].y, lbl_1_data_E8[var_r31].z);
        Hu3DModelRotSet(lbl_1_bss_EC[var_r31 + 7], 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 2) {
        lbl_1_bss_EC[var_r31_2 + 0xB] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[var_r31_2 + 0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelShadowMapSet(lbl_1_bss_EC[var_r31_2 + 0xB]);
        Hu3DModelAttrSet(lbl_1_bss_EC[var_r31_2 + 0xB], 1U);
        Hu3DModelLayerSet(lbl_1_bss_EC[var_r31_2 + 0xB], 2);
        Hu3DModelPosSet(lbl_1_bss_EC[var_r31_2 + 0xB], lbl_1_data_E8[var_r31_2].x, lbl_1_data_E8[var_r31_2].y, lbl_1_data_E8[var_r31_2].z);
        Hu3DModelRotSet(lbl_1_bss_EC[var_r31_2 + 0xB], 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r31_2 + 0xB], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_EC[var_r31_2 + 0xB], 0.0f);
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_8:
    if (var_r31_3 < 4) {
        lbl_1_bss_EC[var_r31_3 + 1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[var_r31_3 + 1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelShadowSet(lbl_1_bss_EC[var_r31_3 + 1]);
        Hu3DModelAttrSet(lbl_1_bss_EC[var_r31_3 + 1], 1U);
        Hu3DModelAttrSet(lbl_1_bss_EC[var_r31_3 + 1], 0x40000001U);
        Hu3DModelLayerSet(lbl_1_bss_EC[var_r31_3 + 1], 4);
        Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r31_3 + 1], 0.0f);
        Hu3DModelPosSet(lbl_1_bss_EC[var_r31_3 + 1], lbl_1_data_88[var_r31_3].x, lbl_1_data_88[var_r31_3].y, lbl_1_data_88[var_r31_3].z);
        Hu3DModelRotSet(lbl_1_bss_EC[var_r31_3 + 1], lbl_1_data_B8[var_r31_3].x, lbl_1_data_B8[var_r31_3].y, lbl_1_data_B8[var_r31_3].z);
        Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r31_3 + 1], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_EC[var_r31_3 + 1], 0.0f);
        var_r31_3 += 1;
        goto loop_8;
    }
    Hu3DModelAttrReset(lbl_1_bss_EC[5], 1U);
    Hu3DModelAttrReset(lbl_1_bss_EC[6], 1U);
    Hu3DModelAttrReset(lbl_1_bss_EC[0], 1U);
    var_r31_4 = 0;
loop_11:
    if (var_r31_4 < 2) {
        Hu3DModelAttrReset(lbl_1_bss_EC[var_r31_4 + 7], 1U);
        var_r31_4 += 1;
        goto loop_11;
    }
    var_r31_5 = 0;
loop_14:
    if (var_r31_5 < 2) {
        Hu3DModelAttrReset(lbl_1_bss_EC[var_r31_5 + 0xB], 1U);
        var_r31_5 += 1;
        goto loop_14;
    }
    var_r31_6 = 0;
loop_17:
    if (var_r31_6 < 4) {
        Hu3DModelAttrReset(lbl_1_bss_EC[var_r31_6 + 1], 1U);
        var_r31_6 += 1;
        goto loop_17;
    }
    lbl_1_bss_38 = 90.0f;
    lbl_1_bss_3C = 0.0f;
    lbl_1_bss_40 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelPosSet(lbl_1_bss_40, 0.0f, (f32) ((f64) lbl_1_bss_3C + (470.0 * sin((3.141592653589793 * (f64) lbl_1_bss_38) / 180.0))), 0.0f);
    Hu3DModelRotSet(lbl_1_bss_40, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(lbl_1_bss_40, 0x40000001U);
    Hu3DModelShadowSet(lbl_1_bss_40);
    lbl_1_bss_E8 = 0;
    WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
    obj->func = fn_1_2BEC;
}

void fn_1_2714(omObjData *obj) {
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        lbl_1_bss_CC[var_r31] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelShadowSet(lbl_1_bss_CC[var_r31]);
        Hu3DModelAttrSet(lbl_1_bss_CC[var_r31], 1U);
        Hu3DModelAttrSet(lbl_1_bss_CC[var_r31], 0x40000001U);
        lbl_1_bss_9C[var_r31].x = lbl_1_data_124[var_r31].x;
        lbl_1_bss_9C[var_r31].y = lbl_1_data_124[var_r31].y;
        lbl_1_bss_9C[var_r31].z = lbl_1_data_124[var_r31].z;
        Hu3DModelPosSet(lbl_1_bss_84[var_r31], lbl_1_bss_9C[var_r31].x, lbl_1_bss_9C[var_r31].y, lbl_1_bss_9C[var_r31].z);
        Hu3DModelRotSet(lbl_1_bss_CC[var_r31], lbl_1_data_1B4[var_r31].x, lbl_1_data_1B4[var_r31].y, lbl_1_data_1B4[var_r31].z);
        lbl_1_bss_8C[var_r31] = 0.5f * (f32) var_r31;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 4) {
        lbl_1_bss_84[var_r31_2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_244[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelShadowSet(lbl_1_bss_84[var_r31_2]);
        Hu3DModelAttrSet(lbl_1_bss_84[var_r31_2], 1U);
        Hu3DModelAttrSet(lbl_1_bss_84[var_r31_2], 0x40000001U);
        lbl_1_bss_54[var_r31_2].x = lbl_1_data_154[var_r31_2].x;
        lbl_1_bss_54[var_r31_2].y = lbl_1_data_154[var_r31_2].y;
        lbl_1_bss_54[var_r31_2].z = lbl_1_data_154[var_r31_2].z;
        Hu3DModelPosSet(lbl_1_bss_84[var_r31_2], lbl_1_bss_54[var_r31_2].x, lbl_1_bss_54[var_r31_2].y, lbl_1_bss_54[var_r31_2].z);
        Hu3DModelRotSet(lbl_1_bss_84[var_r31_2], lbl_1_data_214[var_r31_2].x, lbl_1_data_214[var_r31_2].y, lbl_1_data_214[var_r31_2].z);
        lbl_1_bss_44[var_r31_2] = 0.5f * (f32) var_r31_2;
        var_r31_2 += 1;
        goto loop_5;
    }
    lbl_1_bss_4 = -1;
    lbl_1_bss_0 = -1;
    obj->func = fn_1_2B70;
}

void fn_1_2B70(omObjData *obj) {
    u32 temp_r0;

    temp_r0 = obj->work[0];
    if ((s32) temp_r0 != 1) {
        if ((s32) temp_r0 < 1) {

        }
    } else if ((u32) obj->work[1] > 0x3CU) {
        obj->work[0] = 2;
        obj->work[1] = 0;
    } else {
        fn_1_3CE0();
        obj->work[1] += 1;
    }
    fn_1_4048();
}

void fn_1_2BEC(omObjData *obj) {
    M529Player *sp1C[4];
    s16 sp18;
    s16 sp16;
    s16 sp14;
    s16 sp12;
    s16 sp10;
    s16 spE;
    s16 spC;
    s16 spA;
    s16 sp8;
    s16 temp_r3;
    s32 temp_r23;
    s32 temp_r25;
    s32 temp_r27;
    s32 temp_r29;
    s32 temp_ret;
    s32 temp_ret_2;
    s32 var_r30;
    u32 var_r5;

    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        sp1C[var_r30] = lbl_1_bss_11C[var_r30]->data;
        var_r30 += 1;
        goto loop_2;
    }
    if ((s16) omSysExitReq != 0) {
        Mp5WipeWhite(2, 0x3C);
        HuAudSeqAllFadeOut(0x3E8);
        HuAudSStreamAllFadeOut(0x3E8);
        fn_1_63E4();
        obj->func = fn_1_4370;
    }
    var_r5 = obj->work[0];
    switch (var_r5) {
    case 0x3E8:
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 >= 15.0f) {
            obj->work[0] += 1;
            lbl_1_bss_108 = 0.0f;
            lbl_1_bss_30C = *lbl_1_data_2A0;
            lbl_1_bss_2F4 = lbl_1_data_2B8;
            Hu3DMotionSpeedSet(*lbl_1_bss_EC, 1.0f);
            lbl_1_data_0 = HuAudFXPlay(0x797);
        }
        break;
    case 0x3E9:
        if (lbl_1_bss_108 == 0.0f) {
            omCameraViewMoveSimple(&lbl_1_data_328, 0x3C);
        }
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 >= 60.0f) {
            obj->work[0] += 1;
            lbl_1_bss_108 = 0.0f;
            lbl_1_bss_30C = *lbl_1_data_2C4;
            lbl_1_bss_2F4 = lbl_1_data_2DC;
        }
        break;
    case 0x3EA:
        if (lbl_1_bss_108 == 0.0f) {
            omCameraViewMoveSimple(&lbl_1_data_344, 0x50);
        }
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 >= 80.0f) {
            obj->work[0] += 1;
            lbl_1_bss_108 = 0.0f;
        }
        if (lbl_1_bss_108 > 40.0f) {
            lbl_1_bss_38 -= 0.85f;
            if (lbl_1_bss_38 < 0.0f) {
                lbl_1_bss_38 = 0.0f;
            }
        }
        break;
    case 0x3EB:
        lbl_1_bss_38 -= 0.85f;
        if (lbl_1_bss_38 < 0.0f) {
            lbl_1_bss_38 = 0.0f;
        }
        if ((s16) lbl_1_bss_22E < 0) {
            lbl_1_bss_22E = MGSeqStartCreate();
            if ((s32) lbl_1_bss_228 < 0) {
                lbl_1_bss_228 = HuAudSStreamPlay(0x3C);
            }
        } else if (GameMesStatGet(lbl_1_bss_22E) == 0) {
            obj->work[0] += 1;
            lbl_1_bss_22E = -1;
            MgTimerModeOnSet(lbl_1_bss_14, 1);
        }
        break;
    case 0x3EC:
        lbl_1_bss_E8 += 1;
        if (MgTimerDoneCheck(lbl_1_bss_14) != 0) {
            obj->work[0] = 0x3ED;
            lbl_1_bss_108 = 0.0f;
            if ((s32) lbl_1_bss_20[0] > (s32) lbl_1_bss_20[1]) {
                lbl_1_bss_1C = 0;
            } else if ((s32) lbl_1_bss_20[0] < (s32) lbl_1_bss_20[1]) {
                lbl_1_bss_1C = 1;
            } else {
                lbl_1_bss_1C = 2;
            }
        }
        break;
    case 0x3ED:
        if ((s16) lbl_1_bss_22E < 0) {
            lbl_1_bss_22E = MGSeqFinishCreate();
            HuAudSStreamFadeOut(lbl_1_bss_228, 0x64);
        } else if (GameMesStatGet(lbl_1_bss_22E) == 0) {
            obj->work[0] = 0x3EE;
            lbl_1_bss_22E = -1;
            lbl_1_bss_108 = 0.0f;
        }
        break;
    case 0x3EE:
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 >= 30.0f) {
            obj->work[0] = 0x3EF;
            lbl_1_bss_108 = 0.0f;
            lbl_1_bss_30C = *lbl_1_data_2E8;
            lbl_1_bss_2F4 = lbl_1_data_300;
        }
        break;
    case 0x3EF:
        lbl_1_bss_38 += 1.0f;
        if (lbl_1_bss_38 > 90.0f) {
            lbl_1_bss_38 = 90.0f;
        }
        if (lbl_1_bss_108 == 0.0f) {
            omCameraViewMoveSimple(&lbl_1_data_360, 0x50);
        }
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 >= 80.0f) {
            if ((s32) lbl_1_bss_1C == 2) {
                if ((s32) lbl_1_bss_20[0] > (s32) lbl_1_bss_18) {
                    if (((s16) GWPlayerCfg[sp1C[0]->unk14].iscom != 0) && ((s16) GWPlayerCfg[sp1C[1]->unk14].iscom != 0)) {
                        obj->work[0] = 0x3F1;
                    } else {
                        GWMgRecordSet(6, (u32) lbl_1_bss_20[0]);
                        lbl_1_bss_18 = (u32) lbl_1_bss_20[0];
                        obj->work[0] = 0x3F0;
                    }
                } else {
                    obj->work[0] = 0x3F1;
                }
            } else if ((s32) lbl_1_bss_20[lbl_1_bss_1C] > (s32) lbl_1_bss_18) {
                if ((s32) lbl_1_bss_1C == 0) {
                    if (((s16) GWPlayerCfg[fn_1_59BC(0)].iscom != 0) && ((s16) GWPlayerCfg[fn_1_59BC(1)].iscom != 0)) {
                        obj->work[0] = 0x3F1;
                    } else {
                        GWMgRecordSet(6, (u32) lbl_1_bss_20[lbl_1_bss_1C]);
                        lbl_1_bss_18 = (u32) lbl_1_bss_20[lbl_1_bss_1C];
                        obj->work[0] = 0x3F0;
                    }
                } else if (((s16) GWPlayerCfg[fn_1_59BC(2)].iscom != 0) && ((s16) GWPlayerCfg[fn_1_59BC(3)].iscom != 0)) {
                    obj->work[0] = 0x3F1;
                } else {
                    GWMgRecordSet(6, (u32) lbl_1_bss_20[lbl_1_bss_1C]);
                    lbl_1_bss_18 = (u32) lbl_1_bss_20[lbl_1_bss_1C];
                    obj->work[0] = 0x3F0;
                }
            } else {
                obj->work[0] = 0x3F1;
            }
            lbl_1_bss_108 = 0.0f;
        }
        break;
    case 0x3F0:
        if ((s16) lbl_1_bss_22E < 0) {
            lbl_1_bss_DC = 1;
            lbl_1_bss_22E = MGSeqRecordCreate(lbl_1_bss_18);
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                HuAudJinglePlay(0x86);
            }
        } else if (GameMesStatGet(lbl_1_bss_22E) == 0) {
            obj->work[0] = 0x3F1;
            lbl_1_bss_108 = 0.0f;
            lbl_1_bss_22E = -1;
        }
        break;
    case 0x3F1:
        if (lbl_1_bss_108 > 210.0f) {
            obj->work[0] = 0x3F2;
            lbl_1_bss_108 = 0.0f;
            lbl_1_bss_22E = -1;
        } else {
            if (lbl_1_bss_108 == 0.0f) {
                if ((s32) lbl_1_bss_1C != 2) {
                    if ((s32) lbl_1_bss_1C == 0) {
                        sp16 = fn_1_5960(0);
                        sp18 = fn_1_5960(1);
                        sp14 = GWPlayer[fn_1_59BC(0)].coin_win;
                        temp_r29 = fn_1_59BC(0);
                        if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                            GWPlayer[temp_r29].coin_win = sp14 + 0xA;
                        }
                        sp12 = GWPlayer[fn_1_59BC(1)].coin_win;
                        sp10 = sp12;
                        temp_r27 = fn_1_59BC(1);
                        temp_ret = _CheckFlag(MP5_PRACTICE_FLAG);
                        if (temp_ret == 0) {
                            GWPlayer[temp_r27].coin_win = sp10 + 0xA;
                        }
                    } else {
                        sp16 = fn_1_5960(2);
                        sp18 = fn_1_5960(3);
                        spE = GWPlayer[fn_1_59BC(2)].coin_win;
                        spC = spE;
                        temp_r25 = fn_1_59BC(2);
                        if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                            GWPlayer[temp_r25].coin_win = spC + 0xA;
                        }
                        temp_r3 = GWPlayer[fn_1_59BC(3)].coin_win;
                        spA = temp_r3;
                        sp8 = temp_r3;
                        temp_r23 = fn_1_59BC(3);
                        temp_ret_2 = _CheckFlag(MP5_PRACTICE_FLAG);
                        if (temp_ret_2 == 0) {
                            GWPlayer[temp_r23].coin_win = temp_r3 + 0xA;
                        }
                    }
                    lbl_1_bss_22E = MGSeqWinCreate(sp16, sp18, -1, -1);
                    HuAudJinglePlay(0x79);
                    lbl_1_bss_E0 = lbl_1_bss_2C;
                } else {
                    lbl_1_bss_22E = MGSeqDrawCreate();
                    HuAudJinglePlay(0x7B);
                }
            }
            if (lbl_1_bss_108 == 60.0f) {
                lbl_1_bss_114->work[0] = 1;
            }
            lbl_1_bss_108 += 1.0f;
        }
        break;
    case 0x3F2:
        lbl_1_bss_108 += 1.0f;
        if (lbl_1_bss_108 > 1.0f) {
            HuAudSeqAllFadeOut(0x3E8);
            HuAudSStreamAllFadeOut(0x3E8);
            fn_1_63E4();
            lbl_1_bss_22E = -1;
            Mp5WipeWhite(2, 0x3C);
            obj->func = fn_1_4290;
        }
        break;
    default:
        OSReport(lbl_1_data_424, obj->work[0], var_r5);
        break;
    }
    Hu3DModelPosSet(lbl_1_bss_40, 0.0f, (f32) ((f64) lbl_1_bss_3C + (470.0 * sin((3.141592653589793 * (f64) lbl_1_bss_38) / 180.0))), 0.0f);
    fn_1_5680((s16) obj->work[0]);
    if (((u32) obj->work[0] >= 0x3F1U) && ((s32) lbl_1_bss_1C != 2) && (((s32) lbl_1_bss_20[0] > 0x31) || ((s32) lbl_1_bss_20[1] > 0x31))) {
        if ((s32) lbl_1_bss_1C == 0) {
            if (((s16) GWPlayerCfg[sp1C[0]->unk14].iscom == 0) || ((s16) GWPlayerCfg[sp1C[1]->unk14].iscom == 0)) {
                fn_1_57BC();
            }
        } else if (((s16) GWPlayerCfg[sp1C[2]->unk14].iscom == 0) || ((s16) GWPlayerCfg[sp1C[3]->unk14].iscom == 0)) {
            fn_1_57BC();
        }
    }
}

void fn_1_3CE0(void) {
    Vec *temp_r5;
    Vec *temp_r5_2;
    Vec *temp_r5_3;
    Vec *temp_r5_4;
    Vec *temp_r5_5;
    Vec *temp_r5_6;
    s32 var_r31;
    s32 var_r31_2;

    switch ((s32) lbl_1_bss_1C) {                   /* irregular */
    case 0:
        var_r31 = 0;
loop_3:
        if (var_r31 < 4) {
            Hu3DModelAttrReset(lbl_1_bss_CC[var_r31], 1U);
            temp_r5 = &lbl_1_bss_9C[var_r31];
            temp_r5->x += (lbl_1_data_184[var_r31].x - lbl_1_data_124[var_r31].x) / 60.0f;
            temp_r5_2 = &lbl_1_bss_9C[var_r31];
            temp_r5_2->y += (lbl_1_data_184[var_r31].y - lbl_1_data_124[var_r31].y) / 60.0f;
            temp_r5_3 = &lbl_1_bss_9C[var_r31];
            temp_r5_3->z += (lbl_1_data_184[var_r31].z - lbl_1_data_124[var_r31].z) / 60.0f;
            Hu3DModelPosSet(lbl_1_bss_CC[var_r31], lbl_1_bss_9C[var_r31].x, lbl_1_bss_9C[var_r31].y, lbl_1_bss_9C[var_r31].z);
            var_r31 += 1;
            goto loop_3;
        }
        return;
    case 1:
        var_r31_2 = 0;
loop_8:
        if (var_r31_2 < 4) {
            Hu3DModelAttrReset(lbl_1_bss_84[var_r31_2], 1U);
            temp_r5_4 = &lbl_1_bss_54[var_r31_2];
            temp_r5_4->x += (lbl_1_data_1E4[var_r31_2].x - lbl_1_data_154[var_r31_2].x) / 60.0f;
            temp_r5_5 = &lbl_1_bss_54[var_r31_2];
            temp_r5_5->y += (lbl_1_data_1E4[var_r31_2].y - lbl_1_data_154[var_r31_2].y) / 60.0f;
            temp_r5_6 = &lbl_1_bss_54[var_r31_2];
            temp_r5_6->z += (lbl_1_data_1E4[var_r31_2].z - lbl_1_data_154[var_r31_2].z) / 60.0f;
            Hu3DModelPosSet(lbl_1_bss_84[var_r31_2], lbl_1_bss_54[var_r31_2].x, lbl_1_bss_54[var_r31_2].y, lbl_1_bss_54[var_r31_2].z);
            var_r31_2 += 1;
            goto loop_8;
        }
        return;
    }
}

void fn_1_4048(void) {
    f32 *temp_r4;
    f32 *temp_r4_2;
    f32 temp_f31;
    f32 temp_f31_2;
    s32 var_r31;
    s32 var_r31_2;

    switch ((s32) lbl_1_bss_1C) {                   /* irregular */
    case 0:
        var_r31 = 0;
loop_3:
        if (var_r31 < 4) {
            temp_f31 = (f32) sin((3.141592653589793 * (f64) (180.0f * lbl_1_bss_8C[var_r31])) / 180.0);
            Hu3DModelPosSet(lbl_1_bss_CC[var_r31], lbl_1_bss_9C[var_r31].x, (25.0f * (temp_f31 * temp_f31)) + lbl_1_bss_9C[var_r31].y, lbl_1_bss_9C[var_r31].z);
            temp_r4 = &lbl_1_bss_8C[var_r31];
            *temp_r4 += 0.011111111f;
            var_r31 += 1;
            goto loop_3;
        }
        return;
    case 1:
        var_r31_2 = 0;
loop_8:
        if (var_r31_2 < 4) {
            temp_f31_2 = (f32) sin((3.141592653589793 * (f64) (180.0f * lbl_1_bss_44[var_r31_2])) / 180.0);
            Hu3DModelPosSet(lbl_1_bss_84[var_r31_2], lbl_1_bss_54[var_r31_2].x, (25.0f * (temp_f31_2 * temp_f31_2)) + lbl_1_bss_54[var_r31_2].y, lbl_1_bss_54[var_r31_2].z);
            temp_r4_2 = &lbl_1_bss_44[var_r31_2];
            *temp_r4_2 += 0.011111111f;
            var_r31_2 += 1;
            goto loop_8;
        }
        return;
    }
}

void fn_1_4290(omObjData *obj) {
    s32 var_r31;

    if (WipeCheckEnd() == 0) {
        if ((s16) lbl_1_bss_22E >= 0) {
            GameMesKill(lbl_1_bss_22E);
        }
        if ((s16) lbl_1_bss_22C >= 0) {
            GameMesKill(lbl_1_bss_22C);
        }
        GameMesClose();
        HuAudAllStop();
        var_r31 = 0;
loop_7:
        if (var_r31 < 4) {
            CharModelKill((s16) ((M529Player *)lbl_1_bss_11C[var_r31]->data)->unk28);
            var_r31 += 1;
            goto loop_7;
        }
        MgTimerKill(lbl_1_bss_14);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_4370(omObjData *obj) {
    s32 var_r31;

    if (WipeCheckEnd() == 0) {
        if ((s16) lbl_1_bss_22E >= 0) {
            GameMesKill(lbl_1_bss_22E);
        }
        if ((s16) lbl_1_bss_22C >= 0) {
            GameMesKill(lbl_1_bss_22C);
        }
        GameMesClose();
        var_r31 = 0;
loop_7:
        if (var_r31 < 4) {
            CharModelKill((s16) ((M529Player *)lbl_1_bss_11C[var_r31]->data)->unk28);
            var_r31 += 1;
            goto loop_7;
        }
        MgTimerKill(lbl_1_bss_14);
        omOvlReturnEx(1, 1);
    }
}

s32 fn_1_444C(omObjData *obj) {
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if (((s32) temp_r31->unk40 == 0) && ((s32) temp_r31->unk3C != 0)) {
        return 0;
    }
    return 1;
}

s32 fn_1_4488(omObjData *obj) {
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if (((s32) temp_r31->unk58 == 0) && ((s32) temp_r31->unk54 != 0)) {
        return 0;
    }
    return 1;
}

void fn_1_44C4(omObjData *obj) {
    Vec sp14;
    Vec sp8;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if (((s32) temp_r31->unk40 == 0) && ((s32) temp_r31->unk3C != 0)) {
        temp_r31->unk44 = 0;
        temp_r31->unk40 = 1;
        temp_r31->unk3C = 0;
        temp_r31->unk38 = 0;
        temp_r31->unk90.y = 1300.0f;
        temp_r31->unk4 = 3;
        CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[3], 0.0f, 4.0f, 0U);
        Hu3D3Dto2D(&temp_r31->unk84, 1, &sp8);
        CharFXPlayPan((s16) temp_r31->unk28, 0x9E, (s16) (32.0f + ((sp8.x / 576.0f) * 64.0f)));
    }
    if ((s32) temp_r31->unk40 != 0) {
        if ((s32) temp_r31->unk44 == 6) {
            if ((s32) (temp_r31->unk30 & 0x100) != 0) {
                temp_r31->unk38 = 1;
            } else {
                temp_r31->unk38 = 0;
            }
        }
        if ((s32) temp_r31->unk38 == 1) {
            temp_r31->unk90.y = (f32) ((f64) temp_r31->unk90.y + -36.00000251332922);
        } else {
            temp_r31->unk90.y = (f32) ((f64) temp_r31->unk90.y + -146.25001021039995);
        }
        temp_r31->unk84.y = (f32) (temp_r31->unk84.y + (1.35f * (0.016666668f * temp_r31->unk90.y)));
        temp_r31->unk44 = (s32) (temp_r31->unk44 + 1);
        if (temp_r31->unk84.y <= 0.0f) {
            temp_r31->unk40 = 0;
            temp_r31->unk84.y = 0.0f;
            temp_r31->unk38 = 0;
            sp14.x = temp_r31->unk84.x;
            sp14.y = temp_r31->unk84.y;
            sp14.z = temp_r31->unk84.z;
            CharModelLandDustCreate((s16) temp_r31->unk28, &sp14);
        }
        if ((temp_r31->unk9C > temp_r31->unk84.y) && (temp_r31->unk84.y <= 65.0f) && ((s32) temp_r31->unk4 != 0)) {
            temp_r31->unk4 = 0;
            CharMotionShiftSet((s16) temp_r31->unk28, obj->motion[0], 0.0f, 5.0f, 0x40000001U);
        }
        temp_r31->unk9C = (f32) temp_r31->unk84.y;
    }
}

void fn_1_4780(omObjData *obj) {
    s16 var_r28;
    s16 var_r29;
    s32 temp_r0;
    s32 temp_r3;
    M529Player *temp_r30;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    temp_r30 = lbl_1_bss_11C[temp_r31->unk1C]->data;
    if ((s32) temp_r31->unk0 == 0xBB9) {
        var_r29 = 1;
        var_r28 = 2;
    } else {
        var_r29 = 3;
        var_r28 = 4;
    }
    if ((s32) temp_r31->unk60 != 0) {
        temp_r31->unk54 = 1;
    }
    temp_r0 = temp_r31->unk80;
    switch (temp_r0) {                              /* irregular */
    case 5:
        temp_r31->unk68 = 2.0f;
        break;
    case 4:
        temp_r31->unk68 = 1.5f;
        break;
    case 3:
        temp_r31->unk68 = 1.2f;
        break;
    case 2:
        temp_r31->unk68 = 1.0f;
        break;
    case 1:
        temp_r31->unk68 = 1.0f;
        break;
    case 0:
        temp_r31->unk68 = 0.0f;
        temp_r31->unk60 = 0;
        break;
    }
    if (((s16) GWPlayerCfg[temp_r31->unk14].iscom != 0) && ((s32) temp_r31->unk6C == 0)) {
        temp_r31->unk68 = 1.0f;
    }
    if ((s32) temp_r31->unk0 == 0xBB9) {
        if ((s32) lbl_1_bss_10 != -1) {
            HuAudFXPitchSet(lbl_1_bss_10, fn_1_6334(temp_r31->unk14));
        }
    } else if ((s32) lbl_1_bss_C != -1) {
        HuAudFXPitchSet(lbl_1_bss_C, fn_1_6334(temp_r31->unk14));
    }
    if (((s32) temp_r31->unk58 == 0) && ((s32) temp_r31->unk54 != 0)) {
        temp_r31->unk6C = (s32) (temp_r31->unk6C + 1);
        temp_r31->unk48 = 1;
        if (temp_r31->unk68 < 1.0f) {
            temp_r31->unk68 = 1.0f;
        }
        if (temp_r31->unk68 >= 2.0f) {
            temp_r31->unk68 = 2.0f;
        }
        temp_r31->unk70 = (s32) ((1.0f + Hu3DMotionMaxTimeGet(lbl_1_bss_EC[var_r29])) / temp_r31->unk68);
        temp_r3 = temp_r31->unk70;
        temp_r31->unk50 = (s32) (((s32) (((u32) temp_r3 >> 0x1FU) + temp_r3) >> 1) - 1);
        temp_r31->unk64 = 0;
        temp_r31->unk58 = 1;
        temp_r31->unk54 = 0;
        Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r29], temp_r31->unk68);
        Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r28], temp_r31->unk68);
        CharMotionSpeedSet((s16) temp_r31->unk28, temp_r31->unk68);
        Hu3DMotionTimeSet(lbl_1_bss_EC[var_r29], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_EC[var_r28], 0.0f);
        CharMotionTimeSet((s16) temp_r31->unk28, 0.0f);
    }
    if ((s32) temp_r31->unk58 != 0) {
        temp_r31->unk64 = (s32) (temp_r31->unk64 + 1);
        if ((s32) (temp_r31->unk50 + 1) == (s32) temp_r31->unk64) {
            temp_r31->unk5C = 1;
        } else {
            temp_r31->unk5C = 0;
        }
        if ((s32) temp_r31->unk64 >= (s32) temp_r31->unk70) {
            temp_r31->unk58 = 0;
            if ((s32) temp_r31->unk60 != 0) {
                Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r29], temp_r31->unk68);
                Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r28], temp_r31->unk68);
                Hu3DMotionSpeedSet(*obj->model, temp_r31->unk68);
            } else {
                Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r29], 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_EC[var_r28], 0.0f);
                Hu3DMotionSpeedSet(*obj->model, 0.0f);
            }
            Hu3DMotionTimeSet(lbl_1_bss_EC[var_r29], 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_EC[var_r28], 0.0f);
            CharMotionTimeSet((s16) temp_r31->unk28, 0.0f);
            temp_r31->unk64 = 0;
        }
    }
    if (((s32) temp_r31->unk5C != 0) && (((s32) temp_r30->unkC == 0) || ((s32) temp_r30->unkC == 2))) {
        if ((s32) temp_r30->unk40 != 0) {
            if ((s32) temp_r31->unk8 == 0x7D1) {
                if ((s32) temp_r31->unk48 != 0) {
                    if ((s32) temp_r31->unk0 == 0xBB9) {
                        lbl_1_bss_20[0] += 1;
                    } else {
                        lbl_1_bss_20[1] += 1;
                    }
                }
                temp_r31->unk48 = 0;
            }
        } else if ((s32) temp_r30->unkC == 0) {
            temp_r30->unkC = 1;
        }
    }
    if ((s32) temp_r31->unk0 == 0xBB9) {
        if (((s32) temp_r31->unk58 == 0) && ((s32) temp_r31->unk54 == 0)) {
            if ((s32) lbl_1_bss_10 != -1) {
                HuAudFXStop(lbl_1_bss_10);
                lbl_1_bss_10 = -1;
            }
        } else if ((s32) lbl_1_bss_10 == -1) {
            lbl_1_bss_10 = HuAudFXPlay(0x790);
        }
    } else if (((s32) temp_r31->unk58 == 0) && ((s32) temp_r31->unk54 == 0)) {
        if ((s32) lbl_1_bss_C != -1) {
            HuAudFXStop(lbl_1_bss_C);
            lbl_1_bss_C = -1;
        }
    } else if ((s32) lbl_1_bss_C == -1) {
        lbl_1_bss_C = HuAudFXPlay(0x791);
    }
}



u16 fn_1_4F10(omObjData *obj) {
    s32 temp_r0;
    s32 temp_r0_2;
    u16 var_r30;
    M529Player *temp_r29;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    temp_r29 = lbl_1_bss_11C[temp_r31->unk1C]->data;
    var_r30 = 0;
    temp_r0 = temp_r31->unkB8;
    if (temp_r0 != 0) {
        if ((temp_r0 >= 0) && (temp_r0 < 4)) {
            if ((s32) temp_r31->unk40 == 0) {
                if (frandmod(temp_r31->unkBC) != 0) {
                    if ((s32) temp_r29->unk64 == (s32) temp_r29->unk50) {
                        var_r30 = 0x100;
                    }
                } else {
                    var_r30 = 0;
                }
            }
        } else {
            var_r30 = 0;
        }
    } else if ((s32) temp_r31->unk40 == 0) {
        temp_r0_2 = temp_r31->unkC4 - 1;
        temp_r31->unkC4 = temp_r0_2;
        if (temp_r0_2 < 0) {
            var_r30 = 0x100;
            temp_r31->unkC4 = (s32) (frandmod(0x1EU) + 0x1E);
        }
    }
    return var_r30;
}

u16 fn_1_500C(omObjData *obj) {
    M529Player *sp8;
    s32 temp_r0;
    u16 var_r30;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    sp8 = lbl_1_bss_11C[temp_r31->unk1C]->data;
    temp_r0 = temp_r31->unkB8;
    if (temp_r0 != 0) {
        if ((temp_r0 >= 0) && (temp_r0 < 4)) {
            var_r30 = 0;
        } else {
            var_r30 = 0;
        }
    } else {
        var_r30 = 0x100;
    }
    return var_r30;
}

u16 fn_1_5084(omObjData *obj) {
    M529Player *sp8;
    s32 temp_r0;
    s32 temp_r0_2;
    u16 var_r30;
    M529Player *temp_r31;

    temp_r31 = obj->data;
    sp8 = lbl_1_bss_11C[temp_r31->unk1C]->data;
    var_r30 = 0;
    temp_r0 = temp_r31->unkB8;
    if (temp_r0 < 4) {
        if (temp_r0 < 0) {

        } else {
            if ((s32) temp_r31->unkCC == -1) {
                temp_r31->unkC4 = 0;
            }
            temp_r0_2 = temp_r31->unkC4 - 1;
            temp_r31->unkC4 = temp_r0_2;
            if (temp_r0_2 < 0) {
                if ((s32) temp_r31->unk7C == -1) {
                    var_r30 = 0x40;
                } else if (frandmod(temp_r31->unkC0) != 0) {
                    var_r30 = fn_1_5170(obj);
                } else {
                    var_r30 = 0;
                }
                temp_r31->unkC4 = fn_1_51B4(temp_r31->unkC8, temp_r31->unkCC);
            }
        }
    }
    return var_r30;
}

u16 fn_1_5170(omObjData *obj) {
    M529Player *temp_r31;

    temp_r31 = obj->data;
    if ((s32) temp_r31->unk7C == -1) {
        return 0x40U;
    }
    if ((s32) temp_r31->unk7C == 0) {
        return 0x20U;
    }
    return 0x40U;
}

s32 fn_1_51B4(s32 min, s32 max) {
    if (min > max) {
        return 0;
    }
    return min + frandmod(max - min);
}

void fn_1_5204(omObjData *obj) {
    M529Hud *temp_r31;

    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M529Hud), MEMORY_DEFAULT_NUM);
    temp_r31 = obj->data;
    lbl_1_bss_34 = MgScoreWinCreate(0x40, 0x28);
    MgScoreWinColorSet(lbl_1_bss_34, 0xFAU, 0U, 0x1EU);
    MgScoreWinTPLvlSet(lbl_1_bss_34, 0.7f);
    MgScoreWinPosSet(lbl_1_bss_34, 48.0f, 60.0f);
    temp_r31->unk8 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 49), -1, 1);
    MgScoreValueSet(temp_r31->unk8, lbl_1_bss_20[0]);
    MgScorePosSet(temp_r31->unk8, 38.0f, 60.0f);
    MgScoreMaxDigitSet(temp_r31->unk8, 2);
    MgScoreDispOff(temp_r31->unk8);
    lbl_1_bss_32 = MgScoreWinCreate(0x40, 0x28);
    MgScoreWinColorSet(lbl_1_bss_32, 0U, 0x32U, 0xFAU);
    MgScoreWinTPLvlSet(lbl_1_bss_32, 0.7f);
    MgScoreWinPosSet(lbl_1_bss_32, 528.0f, 60.0f);
    temp_r31->unkC = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 49), -1, 1);
    MgScoreValueSet(temp_r31->unkC, lbl_1_bss_20[1]);
    MgScorePosSet(temp_r31->unkC, 518.0f, 60.0f);
    MgScoreMaxDigitSet(temp_r31->unkC, 2);
    MgScoreDispOff(temp_r31->unkC);
    lbl_1_bss_30 = MgScoreWinCreate(0x48, 0x30);
    MgScoreWinTPLvlSet(lbl_1_bss_30, 0.7f);
    MgScoreWinPosSet(lbl_1_bss_30, 288.0f, 416.0f);
    temp_r31->unk12 = espEntry(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 69), 0xA, 0);
    espDispOff(temp_r31->unk12);
    espDrawNoSet(temp_r31->unk12, 0);
    espPosSet(temp_r31->unk12, 269.0f, 416.0f);
    temp_r31->unk4 = MgScoreCreate(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 48), -1, 1);
    MgScoreValueSet(temp_r31->unk4, (s32) lbl_1_bss_18);
    MgScorePosSet(temp_r31->unk4, 290.0f, 416.0f);
    MgScoreMaxDigitSet(temp_r31->unk4, 2);
    MgScoreDispOff(temp_r31->unk4);
    MgScoreColorSet(temp_r31->unk4, 0x42U, 0xFFU, 0x7AU);
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 1.0f;
    obj->func = fn_1_553C;
}

void fn_1_553C(omObjData *obj) {
    f32 temp_f1;
    f32 temp_f1_2;
    M529Hud *temp_r31;

    temp_r31 = lbl_1_bss_110->data;
    MgScoreValueSet(temp_r31->unk4, (s32) lbl_1_bss_18);
    if ((s32) lbl_1_bss_DC != 0) {
        if ((s32) temp_r31->unk14 == 0) {
            temp_f1 = temp_r31->unk18 + 0.02f;
            temp_r31->unk18 = temp_f1;
            if (temp_f1 >= 1.2f) {
                temp_r31->unk18 = 1.2f;
                temp_r31->unk14 = 1;
            }
        } else {
            temp_f1_2 = temp_r31->unk18 - 0.04f;
            temp_r31->unk18 = temp_f1_2;
            if (temp_f1_2 <= 1.0f) {
                temp_r31->unk18 = 1.0f;
                temp_r31->unk14 = 0;
            }
        }
        MgScoreDigitScaleSet(temp_r31->unk4, temp_r31->unk18, temp_r31->unk18);
        espScaleSet(temp_r31->unk12, temp_r31->unk18, temp_r31->unk18);
    }
    MgScoreValueSet(temp_r31->unk8, lbl_1_bss_20[0]);
    MgScoreValueSet(temp_r31->unkC, lbl_1_bss_20[1]);
}

void fn_1_5680(s16 phase) {
    s16 sp8;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r31;
    s32 var_r31_2;
    M529Hud *temp_r30;

    sp8 = phase;
    temp_r30 = lbl_1_bss_110->data;
    if (sp8 >= 0x3EC) {
        var_r29 = 0;
loop_6:
        if (var_r29 < 2) {
            MgScoreWinDispSet(lbl_1_bss_34, 1);
            MgScoreWinDispSet(lbl_1_bss_32, 1);
            var_r31 = 0;
loop_4:
            if (var_r31 < 2) {
                MgScoreDispOn(var_r31 == 0 ? temp_r30->unk8 : temp_r30->unkC);
                var_r31 += 1;
                goto loop_4;
            }
            var_r29 += 1;
            goto loop_6;
        }
    } else {
        var_r29_2 = 0;
loop_13:
        if (var_r29_2 < 2) {
            MgScoreWinDispSet(lbl_1_bss_34, 0);
            MgScoreWinDispSet(lbl_1_bss_32, 0);
            var_r31_2 = 0;
loop_11:
            if (var_r31_2 < 2) {
                MgScoreDispOff(var_r31_2 == 0 ? temp_r30->unk8 : temp_r30->unkC);
                var_r31_2 += 1;
                goto loop_11;
            }
            var_r29_2 += 1;
            goto loop_13;
        }
    }
    MgScoreWinDispSet(lbl_1_bss_30, 1);
    espDispOn(temp_r30->unk12);
    MgScoreDispOn(temp_r30->unk4);
}

void fn_1_57BC(void) {
    if ((s32) lbl_1_bss_8 == -1) {
        lbl_1_bss_8 = HuAudFXPlay(0x796);
    }
    if ((s32) lbl_1_bss_D4 == 0) {
        Hu3DMotionSet(*lbl_1_bss_EC, lbl_1_bss_D8);
    }
    Hu3DMotionTimeSet(*lbl_1_bss_EC, (f32) lbl_1_bss_E0);
    Hu3DMotionSpeedSet(*lbl_1_bss_EC, 1.5f);
    if ((s32) lbl_1_bss_E4 != 0) {
        lbl_1_bss_E0 += 1;
        if ((s32) lbl_1_bss_2C < (s32) lbl_1_bss_E0) {
            lbl_1_bss_E4 = 0;
        }
    } else {
        lbl_1_bss_E0 -= 1;
        if ((s32) (lbl_1_bss_2C - 0x28) > (s32) lbl_1_bss_E0) {
            lbl_1_bss_E4 = 1;
        }
    }
}


s16 fn_1_5960(s16 slot) {
    s32 var_r30;
    M529Player *temp_r31;

    var_r30 = 0;
loop_4:
    if (var_r30 >= 4) {
        return slot;
    }
    temp_r31 = lbl_1_bss_11C[var_r30]->data;
    if ((s32) temp_r31->unk24 == slot) {
        return (s16) temp_r31->unk28;
    }
    var_r30 += 1;
    goto loop_4;
}

s32 fn_1_59BC(s32 slot) {
    s32 var_r30;
    M529Player *temp_r31;

    var_r30 = 0;
loop_4:
    if (var_r30 >= 4) {
        return slot;
    }
    temp_r31 = lbl_1_bss_11C[var_r30]->data;
    if ((s32) temp_r31->unk24 == slot) {
        return temp_r31->unk14;
    }
    var_r30 += 1;
    goto loop_4;
}




s16 fn_1_6334(s32 player) {
    M529Player *temp_r31;

    temp_r31 = lbl_1_bss_11C[player]->data;
    if (temp_r31->unk68 == 2.0f) {
        return 0x2000;
    }
    if (temp_r31->unk68 == 1.5f) {
        return 0x1000;
    }
    if (temp_r31->unk68 == 1.2f) {
        return 0x6A4;
    }
    return 0;
}

void fn_1_63E4(void) {
    if (HuAudFXStatusGet(lbl_1_data_0) != 0) {
        HuAudFXFadeOut(lbl_1_data_0, 0x3E8);
    }
    if ((s32) lbl_1_bss_10 != -1) {
        HuAudFXFadeOut(lbl_1_bss_10, 0x3E8);
    }
    if ((s32) lbl_1_bss_C != -1) {
        HuAudFXFadeOut(lbl_1_bss_C, 0x3E8);
    }
    if ((s32) lbl_1_bss_8 != -1) {
        HuAudFXFadeOut(lbl_1_bss_8, 0x3E8);
    }
    if ((s32) lbl_1_bss_4 != -1) {
        HuAudFXFadeOut(lbl_1_bss_4, 0x3E8);
    }
    if ((s32) lbl_1_bss_0 != -1) {
        HuAudFXFadeOut(lbl_1_bss_0, 0x3E8);
    }
}
















