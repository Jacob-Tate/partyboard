// MP5 m533 (Pedal vehicle game), generated from its m2c draft by tools/mp5/ports/m533dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m533dll (tools/mp5/decomp.py m533dll --types tools/mp5/types/m533dll.h)
// Written from the draft: a 2 vs 2 game where each team rides one vehicle (lbl_1_bss_84[team]) along a track;
// the two partners are hooked to it ("itemhook_play" / "itemhook_taiki"), the one in front (flag 1) pedals,
// the other (flag 2) rests. Offsets are GameCube's.
// objdata: M533Player
// objdata fn_1_165C fn_1_1840: M533Item
// objdata fn_1_1F98 fn_1_2724: M533Team
// objdata fn_1_4A44 fn_1_4CC8: M533Cloud
// objdata fn_1_4F84 fn_1_5154: M533Pillar
// objexpr lbl_1_bss_AC: M533Player
// objexpr lbl_1_bss_A8: M533Item
// objexpr lbl_1_bss_A4: M533Team
// objexpr lbl_1_bss_A0: M533Cloud
// objexpr lbl_1_bss_9C: M533Pillar

typedef struct M533Player { // OMOBJ::data of lbl_1_bss_AC[4], 0x9C
    s32 unk0; // flags: 1 pedalling, 2 resting, 4/8 swapping places, 0x20 done pedalling
    s32 unk4; // motion slot
    s32 unk8;
    s32 unkC; // player
    s32 unk10; // partner player
    s32 unk14; // character
    s32 unk18; // pad
    s32 unk1C; // team
    s32 unk20; // camera = team
    s32 unk24;
    s32 unk28; // frames until the pedal pose is frozen
    f32 unk2C; // offset from the vehicle
    f32 unk30;
    f32 unk34;
    f32 unk38; // rotation
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    s32 unk50; // buttons pressed
    s32 unk54;
    s32 unk58; // frame of the last pedal
    s32 unk5C;
    f32 unk60; // pedal speed
    s32 unk64; // swap timer
    s32 unk68;
    f32 unk6C;
    f32 unk70;
    s32 unk74; // pedals
    s32 unk78; // com difficulty
    s32 unk7C;
    s32 unk80; // com: frames to wait
    s32 unk84; // com: frames to wait (target)
    s32 unk88; // com: frame counter
    f32 unk8C; // stamina
    s32 unk90;
    s32 unk94;
    f32 unk98;
} M533Player;

typedef struct M533Item { // OMOBJ::data of lbl_1_bss_A8[4] (the shadows), 0x10
    s32 unk0; // player
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M533Item;

typedef struct M533Team { // OMOBJ::data of lbl_1_bss_A4[2] (the vehicles), 0x48
    s32 unk0; // reached the goal
    s32 unk4;
    s32 unk8; // team
    f32 unkC; // position
    f32 unk10;
    f32 unk14;
    f32 unk18; // rotation
    f32 unk1C;
    f32 unk20;
    f32 unk24; // speed
    f32 unk28;
    f32 unk2C;
    f32 unk30; // distance travelled
    s32 unk34;
    f32 unk38; // bob phase
    s32 unk3C;
    s32 unk40;
    s32 unk44; // pedal motion held
} M533Team;

typedef struct M533Cloud { // OMOBJ::data of lbl_1_bss_A0[4], 0x18
    f32 unk0; // y
    f32 unk4; // angle
    f32 unk8; // speed
    s16 unkC;
    s16 unkE;
    s32 unk10; // moving
    s32 unk14; // index
} M533Cloud;

typedef struct M533Pillar { // OMOBJ::data of lbl_1_bss_9C[0x18], 0x14
    s32 unk0; // moving
    s32 unk4; // index
    f32 unk8; // speed
    s32 unkC;
    f32 unk10; // distance moved
} M533Pillar;

typedef struct M533Col { // GXColor
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} M533Col;

typedef struct M533Pt { // pillar / pillar respawn table entry, 0x14
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    f32 unk10;
} M533Pt;


void ObjectSetup(void);
void fn_1_6A8(OMOBJ *obj);
void fn_1_A80(OMOBJ *obj);
void fn_1_165C(OMOBJ *obj);
void fn_1_1840(OMOBJ *obj);
void fn_1_1A5C(OMOBJ *obj, s32 motion);
void fn_1_1BA0(OMOBJ *obj);
s32 fn_1_1CD0(OMOBJ *obj);
void fn_1_1E3C(OMOBJ *obj);
void fn_1_1F98(OMOBJ *obj);
s16 fn_1_2698(s32 team);
void fn_1_2724(OMOBJ *obj);
void fn_1_2D4C(s16 frameNo);
void fn_1_3424(s16 mode, s16 frameNo);
void fn_1_3890(s16 mode, s16 frameNo);
void fn_1_3950(s16 frameNo);
void fn_1_3D50(s16 mode, s16 frameNo);
void fn_1_4080(s16 frameNo);
void fn_1_44D4(void);
f32 fn_1_45B8(s32 frames);
void fn_1_46A4(f32 farg0);
void fn_1_48B8(void);
void fn_1_48BC(s32 on);
void fn_1_4A44(OMOBJ *obj);
void fn_1_4CC8(OMOBJ *obj);
void fn_1_4F84(OMOBJ *obj);
void fn_1_5154(OMOBJ *obj);
void fn_1_52C4(void);
void fn_1_6528(void);
void fn_1_6590(OMOBJ *obj);
void fn_1_6770(OMOBJ *obj, u16 cameraBit);
void fn_1_6984(OMOBJ *obj, Vec *pos, s32 big, u16 cameraBit);
void fn_1_6B18(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_6F54(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void ObjectSetup(void);
void fn_1_6A8(omObjData *obj);
void fn_1_A80(omObjData *obj);
void fn_1_165C(omObjData *obj);
void fn_1_1840(omObjData *obj);
void fn_1_1A5C(omObjData *obj, s32 motion);
void fn_1_1BA0(omObjData *obj);
s32 fn_1_1CD0(omObjData *obj);
void fn_1_1E3C(omObjData *obj);
void fn_1_1F98(omObjData *obj);
s16 fn_1_2698(s32 team);
void fn_1_2724(omObjData *obj);
void fn_1_2D4C(s16 frameNo);
void fn_1_3424(s16 mode, s16 frameNo);
void fn_1_3890(s16 mode, s16 frameNo);
void fn_1_3950(s16 frameNo);
void fn_1_3D50(s16 mode, s16 frameNo);
void fn_1_4080(s16 frameNo);
void fn_1_44D4(void);
f32 fn_1_45B8(s32 frames);
void fn_1_46A4(f32 farg0);
void fn_1_48B8(void);
void fn_1_48BC(s32 on);
void fn_1_4A44(omObjData *obj);
void fn_1_4CC8(omObjData *obj);
void fn_1_4F84(omObjData *obj);
void fn_1_5154(omObjData *obj);
void fn_1_52C4(void);
void fn_1_6528(void);
void fn_1_6590(omObjData *obj);
void fn_1_6770(omObjData *obj, u16 cameraBit);
void fn_1_6984(omObjData *obj, Vec *pos, s32 big, u16 cameraBit);
void fn_1_6B18(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_6F54(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

struct _struct_lbl_1_data_540_0x18 {
    /* 0x00 */ s32 unk0;                            /* inferred */
    /* 0x04 */ s32 unk4;                            /* inferred */
    /* 0x08 */ s32 unk8;                            /* inferred */
    /* 0x0C */ s32 unkC;                            /* inferred */
    /* 0x10 */ s32 unk10;                           /* inferred */
    /* 0x14 */ s32 unk14;                           /* inferred */
};                                                  /* size = 0x18 */

struct _struct_lbl_1_data_670_0xC {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
    /* 0x8 */ f32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

struct _struct_lbl_1_data_A8_0xC {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
    /* 0x8 */ f32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

struct _struct_lbl_1_data_D8_0xC {
    /* 0x0 */ f32 unk0;                             /* inferred */
    /* 0x4 */ f32 unk4;                             /* inferred */
    /* 0x8 */ f32 unk8;                             /* inferred */
};                                                  /* size = 0xC */

extern s32 fontcolor;
static Vec lbl_1_data_0 = { 13000.0f, 10000.0f, 0.0f };
static Vec lbl_1_data_C = { 0.0f, 0.0f, 0.0f };
M533Col lbl_1_data_18 = { 255, 255, 255, 255 };                              /* unable to generate initializer: not enough data */
s32 lbl_1_data_1C = -1;
static u32 lbl_1_data_20[0xA] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 49),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 76),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 81),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 75),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 50),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 50),
};
static s32 lbl_1_data_48[2] = { DATA_MAKE_NUM(DATADIR_MP5_M533, 17), DATA_MAKE_NUM(DATADIR_MP5_M533, 18) };
static f32 lbl_1_data_50[0xD] = {
    1.0f,
    1.0f,
    2.0f,
    1.0f,
    1.5f,
    2.0f,
    1.3f,
    1.0f,
    1.0f,
    1.0f,
    0.0f,
    0.0f,
    0.0f,
};
s32 lbl_1_data_84[9] = {
    DATA_MAKE_NUM(DATADIR_MP5_M533, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M533, 9),
};
static struct _struct_lbl_1_data_A8_0xC lbl_1_data_A8[4] = {
    { 4800.0f, -850.0f, 550.0f },
    { 4800.0f, -850.0f, 550.0f },
    { 5100.0f, -850.0f, 550.0f },
    { 5100.0f, -850.0f, 550.0f },
};
static struct _struct_lbl_1_data_D8_0xC lbl_1_data_D8[4] = {
    { 11920.0f, -850.0f, 550.0f },
    { 11920.0f, -850.0f, 550.0f },
    { 12220.0f, -850.0f, 550.0f },
    { 12220.0f, -850.0f, 550.0f },
};
M533Pt lbl_1_data_108[0x18] = {
    { 7500.0f, 100.0f, -150.0f, 0, -10.0f },
    { 7500.0f, 100.0f, -150.0f, 0, -10.0f },
    { 7500.0f, -50.0f, -200.0f, 1, -15.0f },
    { 7500.0f, -50.0f, -200.0f, 1, -15.0f },
    { 7500.0f, -200.0f, -250.0f, 2, -12.0f },
    { 7500.0f, -200.0f, -250.0f, 2, -12.0f },
    { 7700.0f, 125.0f, -200.0f, 2, -12.0f },
    { 7700.0f, 125.0f, -200.0f, 2, -12.0f },
    { 7700.0f, -50.0f, -250.0f, 0, -8.5f },
    { 7700.0f, -50.0f, -250.0f, 0, -8.5f },
    { 7700.0f, -180.0f, -150.0f, 1, -10.0f },
    { 7700.0f, -180.0f, -150.0f, 1, -10.0f },
    { -1000.0f, 100.0f, -250.0f, 0, -10.0f },
    { -1000.0f, 100.0f, -250.0f, 0, -10.0f },
    { -1000.0f, 100.0f, -250.0f, 1, -12.5f },
    { -1000.0f, 100.0f, -250.0f, 1, -12.5f },
    { -1000.0f, 100.0f, -250.0f, 2, -15.0f },
    { -1000.0f, 100.0f, -250.0f, 2, -15.0f },
    { -1000.0f, 100.0f, -250.0f, 0, -10.0f },
    { -1000.0f, 100.0f, -250.0f, 0, -10.0f },
    { -1000.0f, 100.0f, -250.0f, 1, -12.5f },
    { -1000.0f, 100.0f, -250.0f, 1, -12.5f },
    { -1000.0f, 100.0f, -250.0f, 2, -15.0f },
    { -1000.0f, 100.0f, -250.0f, 2, -15.0f },
};
M533Pt lbl_1_data_2E8[0x18] = {
    { 13370.0f, 212.5f, -250.0f, -1, -10.0f },
    { 13370.0f, 212.5f, -250.0f, -1, -10.0f },
    { 13370.0f, 37.5f, -250.0f, -1, -8.0f },
    { 13370.0f, 37.5f, -250.0f, -1, -8.0f },
    { 13670.0f, 300.0f, -250.0f, -1, -8.0f },
    { 13670.0f, 300.0f, -250.0f, -1, -8.0f },
    { 13690.0f, 125.0f, -250.0f, -1, -11.0f },
    { 13690.0f, 125.0f, -250.0f, -1, -11.0f },
    { 13670.0f, -50.0f, -250.0f, -1, -9.5f },
    { 13670.0f, -50.0f, -250.0f, -1, -9.5f },
    { 13970.0f, 212.5f, -250.0f, -1, -8.5f },
    { 13970.0f, 212.5f, -250.0f, -1, -8.5f },
    { 14020.0f, 37.5f, -250.0f, -1, -12.0f },
    { 14020.0f, 37.5f, -250.0f, -1, -12.0f },
    { 14270.0f, 400.0f, -250.0f, -1, -10.0f },
    { 14270.0f, 400.0f, -250.0f, -1, -10.0f },
    { 14310.0f, 125.0f, -250.0f, -1, -11.0f },
    { 14310.0f, 125.0f, -250.0f, -1, -11.0f },
    { 14420.0f, -100.0f, -250.0f, -1, -7.5f },
    { 14420.0f, -100.0f, -250.0f, -1, -7.5f },
    { 14570.0f, 212.5f, -250.0f, -1, -10.5f },
    { 14570.0f, 212.5f, -250.0f, -1, -10.5f },
    { 14620.0f, 37.5f, -250.0f, -1, -12.0f },
    { 14620.0f, 37.5f, -250.0f, -1, -12.0f },
};
static MGSEQ_PARAM lbl_1_data_4C8 = {
    0x12C,
    0,
    ((void (*)(s16, s16)) fn_1_2D4C),
    fn_1_3424,
    NULL,
    fn_1_3890,
    ((void (*)(s16, s16)) fn_1_3950),
    fn_1_3D50,
    ((void (*)(s16, s16)) fn_1_4080),
    NULL,
    NULL,
};
Vec lbl_1_data_4F0 = { 0.0f, 300.0f, 0.0f };
Vec lbl_1_data_4FC = { 1500.0f, -100.0f, 0.0f };
static OMCAMERAVIEW lbl_1_data_508 = { { 0.5f, 500.0f, 0.0f }, { -2.0f, 0.0f, 0.0f }, 4100.0f };
static OMCAMERAVIEW lbl_1_data_524 = { { 1500.0f, 0.0f, 0.0f }, { -6.0f, 0.0f, 0.0f }, 2700.0f };
static struct _struct_lbl_1_data_540_0x18 lbl_1_data_540[4] = {
    { 0x10, 0x15, 0x15, 0x1A, 0x1A, 0x1E },
    { 0xD, 0x12, 0x12, 0x17, 0x17, 0x1C },
    { 0xA, 0xF, 0xF, 0x14, 0x15, 0x19 },
    { 7, 0xC, 0xC, 0x11, 0x11, 0x16 },
};
static f32 lbl_1_data_5A0[5] = { 3.0f, 2.5f, 2.0f, 1.5f, 1.5f };
static f32 lbl_1_data_5B4[5] = { 10.0f, 15.0f, 20.0f, 25.0f, 25.0f };
s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s32 lbl_1_bss_C;
s16 lbl_1_bss_10[0xA];
f32 lbl_1_bss_24;
s32 lbl_1_bss_28;
u32 lbl_1_bss_2C;
s32 lbl_1_bss_30;
s16 lbl_1_bss_34[4];
s16 lbl_1_bss_3C;
s16 lbl_1_bss_3E;
s16 lbl_1_bss_40;
s16 lbl_1_bss_42;
f32 lbl_1_bss_44[2];
s16 lbl_1_bss_4C[2];
s16 lbl_1_bss_50[2];
s16 lbl_1_bss_54[0x18];
s16 lbl_1_bss_84[2];
s16 lbl_1_bss_88[4];
s16 lbl_1_bss_90[4];
omObjData *lbl_1_bss_98;
omObjData **lbl_1_bss_9C;
omObjData **lbl_1_bss_A0;
omObjData **lbl_1_bss_A4;
omObjData **lbl_1_bss_A8;
omObjData **lbl_1_bss_AC;
omObjData *lbl_1_bss_B0;
s32 lbl_1_bss_1BC;
HUPROCESS *lbl_1_bss_2B8;
static struct _struct_lbl_1_data_670_0xC lbl_1_data_670[0xD] = {
    { -800.0f, -700.0f, 600.0f },
    { 1100.0f, -700.0f, 420.0f },
    { 2000.0f, -600.0f, -700.0f },
    { 2900.0f, -700.0f, 220.0f },
    { 3900.0f, -600.0f, 350.0f },
    { 5600.0f, -700.0f, -750.0f },
    { 6800.0f, -500.0f, 220.0f },
    { 7600.0f, -700.0f, -700.0f },
    { 8600.0f, -700.0f, 700.0f },
    { 10300.0f, -700.0f, -700.0f },
    { 12400.0f, -700.0f, -700.0f },
    { 14000.0f, -700.0f, 350.0f },
    { 0.0f, 0.0f, 0.0f },
};
ANIMDATA *lbl_1_bss_2C8;
void *lbl_1_bss_2CC;
s32 lbl_1_bss_2D4;



static s16 Mp5TeamNo(s16 player)
{
    s16 i, slot = 0;
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].group < GWPlayerCfg[player].group || (GWPlayerCfg[i].group == GWPlayerCfg[player].group && i < player)) {
            slot++;
        }
    }
    return slot / 2;
}

static const s16 m533DkMot[10] = { 0, 0, 0, 132, 0, 0, 0, 0, 0, 0 };

void ObjectSetup(void) {
    s32 spC[2];
    s32 sp8;
    omObjData *var_r31;
    s16 temp_r29;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;

    var_r31 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = 0;
    spC[0] = -1;
    spC[1] = -1;
    OSReport("******* M533 ObjectSetup *********\n");
    lbl_1_bss_2B8 = omInitObjMan(0xC8, 0x2000);
    omGameSysInit(lbl_1_bss_2B8);
    lbl_1_bss_1BC = -1;
    omCameraViewSetMulti(3, &lbl_1_data_508);
    Hu3DCameraCreate(3);
    fn_1_46A4(0.0f);
    lbl_1_bss_98 = omAddObjEx(lbl_1_bss_2B8, 0x7FDA, 0U, 0U, -1, omOutViewMulti);
    lbl_1_bss_98->work[0] = 2;
    lbl_1_bss_42 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0U, 0U, 0U);
    Hu3DGLightPosAimSetV(lbl_1_bss_42, &lbl_1_data_0, &lbl_1_data_C);
    Hu3DGLightStaticSet(lbl_1_bss_42, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_42);
    Hu3DGLightColorSet(lbl_1_bss_42, lbl_1_data_18.unk0, lbl_1_data_18.unk1, lbl_1_data_18.unk2, lbl_1_data_18.unk3);
    omMakeGroupEx(lbl_1_bss_2B8, 0U, 4U);
    lbl_1_bss_AC = omGetGroupMemberListEx(lbl_1_bss_2B8, 0);
    var_r30 = 0;
loop_7:
    if (var_r30 < 4) {
        var_r31 = omAddObjEx(lbl_1_bss_2B8, 0x64, 1U, 0xAU, 0, fn_1_6A8);
        lbl_1_bss_AC[var_r30] = var_r31;
        var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x9C, MEMORY_DEFAULT_NUM);
        var_r31->work[0] = (u32) var_r30;
        temp_r29 = Mp5TeamNo(var_r30);
        var_r31->work[1] = (u32) temp_r29;
        if ((s32) spC[temp_r29] == -1) {
            spC[temp_r29] = frandmod(2U);
            var_r31->work[2] = (u32) spC[temp_r29];
        } else if ((s32) spC[temp_r29] == 0) {
            var_r31->work[2] = 1;
        } else {
            var_r31->work[2] = 0;
        }
        var_r30 += 1;
        goto loop_7;
    }
    omMakeGroupEx(lbl_1_bss_2B8, 1U, 4U);
    lbl_1_bss_A8 = omGetGroupMemberListEx(lbl_1_bss_2B8, 1);
    var_r30_2 = 0;
loop_10:
    if (var_r30_2 < 4) {
        var_r31 = omAddObjEx(lbl_1_bss_2B8, 0x65, 1U, 1U, 1, fn_1_165C);
        lbl_1_bss_A8[var_r30_2] = var_r31;
        var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x10, MEMORY_DEFAULT_NUM);
        var_r31->work[0] = (u32) var_r30_2;
        var_r30_2 += 1;
        goto loop_10;
    }
    omMakeGroupEx(lbl_1_bss_2B8, 2U, 2U);
    lbl_1_bss_A4 = omGetGroupMemberListEx(lbl_1_bss_2B8, 2);
    var_r30_3 = 0;
loop_13:
    if (var_r30_3 < 2) {
        var_r31 = omAddObjEx(lbl_1_bss_2B8, 0x64, 1U, 3U, 2, fn_1_1F98);
        lbl_1_bss_A4[var_r30_3] = var_r31;
        var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x48, MEMORY_DEFAULT_NUM);
        var_r31->work[0] = (u32) var_r30_3;
        var_r30_3 += 1;
        goto loop_13;
    }
    lbl_1_bss_C = -1;
    lbl_1_bss_8 = -1;
    lbl_1_bss_4 = -1;
    lbl_1_bss_0 = -1;
    omMakeGroupEx(lbl_1_bss_2B8, 4U, 4U);
    lbl_1_bss_A0 = omGetGroupMemberListEx(lbl_1_bss_2B8, 4);
    var_r30_4 = 0;
loop_16:
    if (var_r30_4 < 4) {
        var_r31 = omAddObjEx(lbl_1_bss_2B8, 0x68, 1U, 2U, 4, fn_1_4A44);
        lbl_1_bss_A0[var_r30_4] = var_r31;
        var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x18, MEMORY_DEFAULT_NUM);
        var_r31->work[0] = (u32) var_r30_4;
        var_r30_4 += 1;
        goto loop_16;
    }
    omMakeGroupEx(lbl_1_bss_2B8, 5U, 0x18U);
    lbl_1_bss_9C = omGetGroupMemberListEx(lbl_1_bss_2B8, 5);
    var_r30_5 = 0;
loop_19:
    if (var_r30_5 < 0x18) {
        var_r31 = omAddObjEx(lbl_1_bss_2B8, 0x69, 1U, 1U, 5, fn_1_4F84);
        lbl_1_bss_9C[var_r30_5] = var_r31;
        var_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x14, MEMORY_DEFAULT_NUM);
        var_r31->work[0] = (u32) var_r30_5;
        var_r30_5 += 1;
        goto loop_19;
    }
    fn_1_6528();
    fn_1_6590(var_r31);
    lbl_1_bss_B0 = var_r31;
    MgSeqCreate(&lbl_1_data_4C8);
}

void fn_1_6A8(omObjData *obj) {
    s32 var_r29;
    s32 var_r29_2;
    M533Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unkC = (u32) obj->work[0];
    temp_r31->unk14 = (s32) GWPlayerCfg[temp_r31->unkC].character;
    temp_r31->unk1C = (u32) obj->work[1];
    temp_r31->unk0 = 0;
    temp_r31->unk28 = 0;
    if ((u32) (obj->work[2] & 1) == 0) {
        temp_r31->unk0 = (s32) (temp_r31->unk0 | 1);
        temp_r31->unk3C = -90.0f;
    } else {
        temp_r31->unk0 = (s32) (temp_r31->unk0 | 2);
        temp_r31->unk3C = 0.0f;
    }
    temp_r31->unk18 = (s32) GWPlayerCfg[temp_r31->unkC].pad_idx;
    temp_r31->unk4 = 0;
    temp_r31->unk20 = (u32) temp_r31->unk1C;
    temp_r31->unk50 = 0;
    temp_r31->unk54 = 0;
    temp_r31->unk74 = 0;
    temp_r31->unk64 = 0;
    temp_r31->unk6C = 180.0f;
    temp_r31->unk70 = 3.0f;
    temp_r31->unk8C = 100.0f;
    temp_r31->unk4C = 0.0f;
    temp_r31->unk48 = 0.0f;
    temp_r31->unk44 = 0.0f;
    var_r29 = 0;
loop_8:
    if (var_r29 < 4) {
        if ((var_r29 != (s32) temp_r31->unkC) && ((s32) temp_r31->unk1C == (s16) Mp5TeamNo(var_r29))) {
            temp_r31->unk10 = var_r29;
        } else {
            var_r29 += 1;
            goto loop_8;
        }
    }
    temp_r31->unk78 = (s32) GWPlayerCfg[temp_r31->unkC].diff;
    if ((s16) GWPlayerCfg[temp_r31->unkC].iscom != 0) {
        temp_r31->unk7C = (s32) temp_r31->unk78;
    } else {
        temp_r31->unk7C = 4;
    }
    temp_r31->unk98 = 50.0f;
    fn_1_1E3C(obj);
    temp_r31->unk88 = 0;
    *obj->model = CharModelCreate((s16) temp_r31->unk14, 4);
    lbl_1_bss_90[temp_r31->unkC] = *obj->model;
    Hu3DModelCameraSet(*obj->model, (u16) (1 << temp_r31->unk20));
    var_r29_2 = 0;
loop_14:
    if (var_r29_2 < 0xA) {
        obj->motion[var_r29_2] = Mp5CharMotionCreateData((s16) temp_r31->unk14, lbl_1_data_20[var_r29_2], m533DkMot[var_r29_2]);
        CharMotionSet((s16) temp_r31->unk14, obj->motion[var_r29_2]);
        var_r29_2 += 1;
        goto loop_14;
    }
    CharMotionVoiceOnSet((s16) temp_r31->unk14, 0x4B, 0);
    Hu3DModelAttrSet(*obj->model, 1U);
    Hu3DModelAttrSet(*obj->model, 0x40000001U);
    Hu3DMotionSet(*obj->model, *obj->motion);
    temp_r31->unk40 = 0.0f;
    temp_r31->unk38 = 0.0f;
    temp_r31->unk2C = 0.0f;
    obj->trans.x = 0.0f;
    temp_r31->unk30 = 0.0f;
    obj->trans.y = 0.0f;
    temp_r31->unk34 = 0.0f;
    obj->trans.z = 0.0f;
    temp_r31->unk2C = 0.0f;
    temp_r31->unk30 = 0.0f;
    temp_r31->unk34 = 0.0f;
    omSetTra(obj, temp_r31->unk2C, temp_r31->unk30, temp_r31->unk34);
    omSetRot(obj, temp_r31->unk38, temp_r31->unk3C, temp_r31->unk40);
    Hu3DModelAttrReset(*obj->model, 1U);
    CharMotionDataClose((s16) temp_r31->unk14);
    obj->func = fn_1_A80;
}

void fn_1_A80(omObjData *obj) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    M533Player *temp_r28;
    M533Team *temp_r29;
    M533Player *temp_r31;

    temp_r31 = obj->data;
    temp_r28 = lbl_1_bss_AC[temp_r31->unk10]->data;
    temp_r29 = lbl_1_bss_A4[temp_r31->unk1C]->data;
    if ((u32) (temp_r31->unk0 & 4) != 0) {
        fn_1_1A5C(obj, 5);
        temp_r3 = temp_r31->unk64 - 1;
        temp_r31->unk64 = temp_r3;
        if (temp_r3 < 0) {
            fn_1_1A5C(obj, 0);
            temp_r31->unk0 = (s32) (temp_r31->unk0 & 0xFFFFFFFB);
            temp_r31->unk0 = (s32) (temp_r31->unk0 | 2);
            temp_r31->unk0 = (s32) (temp_r31->unk0 & 0xFFFFFFFE);
            temp_r31->unk64 = 0;
            temp_r31->unk6C = 180.0f;
            temp_r31->unk3C = 0.0f;
            temp_r28->unk0 = (s32) (temp_r28->unk0 & 0xFFFFFFF7);
            temp_r28->unk0 = (s32) (temp_r28->unk0 | 1);
            temp_r28->unk0 = (s32) (temp_r28->unk0 & 0xFFFFFFFD);
            temp_r28->unk64 = 0;
            temp_r28->unk6C = 180.0f;
            temp_r28->unk3C = -90.0f;
        } else {
            temp_r31->unk6C = (f32) (temp_r31->unk6C - temp_r31->unk70);
            temp_r31->unk34 = (f32) (100.0 * -sin((3.141592653589793 * (f64) temp_r31->unk6C) / 180.0));
            temp_r31->unk3C = (f32) (temp_r31->unk3C - temp_r31->unk70);
            temp_r31->unk2C = (f32) (temp_r31->unk2C + 3.1666667f);
            Hu3DModelAttrReset(lbl_1_bss_4C[temp_r31->unk1C], 0x40000001U);
            temp_r29->unk44 = 0;
            temp_r31->unk60 = 0.0f;
            Hu3DMotionTimeSet(lbl_1_bss_4C[temp_r31->unk1C], 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_4C[temp_r31->unk1C], 0.0f);
        }
    } else if ((u32) (temp_r31->unk0 & 8) != 0) {
        lbl_1_bss_44[temp_r31->unk1C] = 99.0f;
        fn_1_1A5C(obj, 5);
        temp_r0 = temp_r31->unk64 - 1;
        temp_r31->unk64 = temp_r0;
        if (temp_r0 < 0) {
            fn_1_1A5C(obj, 0);
            fn_1_1E3C(obj);
        } else {
            temp_r31->unk6C = (f32) (temp_r31->unk6C - temp_r31->unk70);
            temp_r31->unk34 = (f32) (100.0 * sin((3.141592653589793 * (f64) temp_r31->unk6C) / 180.0));
            temp_r31->unk3C = (f32) (temp_r31->unk3C - temp_r31->unk70);
            temp_r31->unk2C = (f32) (temp_r31->unk2C - 3.1666667f);
        }
    }
    if ((MgSeqModeGet() == 3) && ((u32) (temp_r31->unk0 & 1) != 0)) {
        fn_1_1BA0(obj);
    }
    if ((MgSeqModeGet() == 6) && (MgSeqFrameNoGet() == 0)) {
        fn_1_1A5C(obj, 0);
    }
    if (MgSeqModeGet() >= 6U) {
        temp_f0 = temp_r29->unkC;
        sp8 = temp_f0;
        temp_f0_2 = temp_r29->unk10;
        spC = temp_f0_2;
        temp_f0_3 = temp_r29->unk14;
        sp10 = temp_f0_3;
        omSetTra(obj, temp_r31->unk2C + temp_f0, temp_r31->unk30 + temp_f0_2, temp_r31->unk34 + temp_f0_3);
        omSetRot(obj, temp_r31->unk38, temp_r31->unk3C, temp_r31->unk40);
        return;
    }
    if (MgSeqModeGet() == 5) {
        if (MgSeqModeGet() == 5) {
            if (MgSeqFrameNoGet() == 0) {
                if ((u32) (temp_r31->unk0 & 1) != 0) {
                    temp_f0_4 = lbl_1_data_4FC.x - 80.0f;
                    temp_r31->unk2C = temp_f0_4;
                    obj->trans.x = temp_f0_4;
                } else {
                    temp_f0_5 = 110.0f + lbl_1_data_4FC.x;
                    temp_r31->unk2C = temp_f0_5;
                    obj->trans.x = temp_f0_5;
                }
                temp_r31->unk30 = (f32) lbl_1_data_4FC.y;
                obj->trans.y = lbl_1_data_4FC.y;
                temp_r31->unk34 = (f32) lbl_1_data_4FC.z;
                obj->trans.z = lbl_1_data_4FC.z;
                omSetTra(obj, temp_r31->unk2C, temp_r31->unk30, temp_r31->unk34);
                return;
            }
            if (MgSeqFrameNoGet() == 1) {
                if ((u32) (temp_r31->unk0 & 1) != 0) {
                    temp_r31->unk2C = -80.0f;
                    obj->trans.x = -80.0f;
                } else {
                    temp_r31->unk2C = 110.0f;
                    obj->trans.x = 110.0f;
                }
                temp_r31->unk30 = 0.0f;
                obj->trans.y = 0.0f;
                temp_r31->unk34 = 0.0f;
                obj->trans.z = 0.0f;
                omSetTra(obj, temp_r31->unk2C, temp_r31->unk30, temp_r31->unk34);
            }
            goto block_28;
        }
block_28:
        if ((u32) (temp_r31->unk0 & 1) != 0) {
            fn_1_1BA0(obj);
            if (Hu3DMotionShiftIDGet(*obj->model) == 0) {
                Hu3DMotionSpeedSet(*obj->model, 2.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_4C[temp_r31->unk1C], 2.0f);
            }
            if ((u32) (temp_r31->unk0 & 0x20) == 0) {
                if ((s16) GWPlayerCfg[temp_r31->unkC].iscom != 0) {
                    temp_r31->unk50 = (u16) (temp_r31->unk50 | fn_1_1CD0(obj));
                } else {
                    temp_r31->unk50 = (u16) (temp_r31->unk50 | HuPadBtnDown[temp_r31->unk18]);
                }
            }
            if (((s32) (temp_r31->unk50 & 0x800) != 0) && ((u32) (temp_r31->unk0 & 0x20) == 0)) {
                temp_r31->unk0 = (s32) (temp_r31->unk0 | 0x20);
            }
            if (((u32) (temp_r31->unk0 & 0x20) != 0) && ((s32) temp_r31->unk4 == 3) && ((Hu3DMotionEndCheck(*obj->model) != 0) || (Hu3DMotionTimeGet(*obj->model) == 0.0f))) {
                temp_r31->unk50 = 0U;
                temp_r31->unk0 = (s32) (temp_r31->unk0 & 0xFFFFFFFE);
                temp_r31->unk0 = (s32) (temp_r31->unk0 | 4);
                temp_r31->unk64 = 0x3C;
                temp_r31->unk3C = 180.0f;
                temp_r31->unk0 = (s32) (temp_r31->unk0 & 0xFFFFFFDF);
                temp_r28->unk0 = (s32) (temp_r28->unk0 & 0xFFFFFFFD);
                temp_r28->unk0 = (s32) (temp_r28->unk0 | 8);
                temp_r28->unk64 = 0x3C;
                temp_r28->unk3C = 0.0f;
            }
            if ((s32) (temp_r31->unk50 & 0x60) == 0x60) {
                temp_r31->unk50 = (u16) (temp_r31->unk50 & ~0x60);
                temp_r31->unk54 = 0;
                temp_r31->unk5C = (s32) (MgSeqFrameNoGet() - temp_r31->unk58);
                temp_r31->unk58 = MgSeqFrameNoGet();
                temp_r31->unk60 = (f32) (0.25f * (2.0f * fn_1_45B8(temp_r31->unk5C)));
                Hu3DMotionSpeedSet(*obj->model, temp_r31->unk60);
                Hu3DMotionSpeedSet(lbl_1_bss_4C[temp_r31->unk1C], temp_r31->unk60);
                temp_r29->unk24 = (f32) (temp_r29->unk24 + 1.5f);
                temp_r31->unk74 = (s32) (temp_r31->unk74 + 1);
                if (temp_r29->unkC < 10670.0f) {
                    temp_r31->unk8C = (f32) (temp_r31->unk8C - lbl_1_data_5A0[temp_r31->unk7C]);
                    if (temp_r31->unk8C < 0.0f) {
                        temp_r31->unk8C = 0.0f;
                    }
                }
            }
            if ((u16) temp_r31->unk50 != 0) {
                temp_r0_2 = temp_r31->unk54 + 1;
                temp_r31->unk54 = temp_r0_2;
                if (temp_r0_2 >= 6) {
                    temp_r31->unk50 = (u16) (temp_r31->unk50 & ~0x60);
                    temp_r31->unk54 = 0;
                }
            }
            if ((s32) temp_r31->unk4 == 3) {
                if ((u32) (MgSeqFrameNoGet() - temp_r31->unk58) > 0x1EU) {
                    Hu3DModelAttrReset(*obj->model, 0x40000001U);
                    Hu3DModelAttrReset(lbl_1_bss_4C[temp_r31->unk1C], 0x40000001U);
                    temp_r29->unk44 = 0;
                } else {
                    Hu3DModelAttrSet(*obj->model, 0x40000001U);
                    Hu3DModelAttrSet(lbl_1_bss_4C[temp_r31->unk1C], 0x40000001U);
                    temp_r29->unk44 = 1;
                }
            }
        }
        if ((u32) (temp_r31->unk0 & 2) != 0) {
            temp_r31->unk50 = (u16) HuPadBtnDown[temp_r31->unk18];
            if (((s16) GWPlayerCfg[temp_r31->unkC].iscom == 0) && ((s32) (temp_r31->unk50 & 0x100) != 0) && (Hu3DMotionEndCheck(lbl_1_bss_50[temp_r31->unk1C]) != 0)) {
                HuAudFXPlay(0x7BA);
                Hu3DMotionTimeSet(lbl_1_bss_50[temp_r31->unk1C], 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_50[temp_r31->unk1C], 1.0f);
                Hu3DMotionClusterSpeedSet(lbl_1_bss_50[temp_r31->unk1C], 0, 1.0f);
                Hu3DMotionClusterTimeSet(lbl_1_bss_50[temp_r31->unk1C], 0, 0.0f);
            }
            if (temp_r31->unk8C < 100.0f) {
                fn_1_1A5C(obj, 6);
                temp_r31->unk8C = (f32) (temp_r31->unk8C + (lbl_1_data_5B4[temp_r31->unk7C] / 60.0f));
                if (temp_r31->unk8C > 100.0f) {
                    temp_r31->unk8C = 100.0f;
                }
            } else {
                fn_1_1A5C(obj, 0);
            }
        }
        temp_f0_6 = temp_r29->unkC;
        sp8 = temp_f0_6;
        temp_f0_7 = temp_r29->unk10;
        spC = temp_f0_7;
        temp_f0_8 = temp_r29->unk14;
        sp10 = temp_f0_8;
        omSetTra(obj, temp_r31->unk2C + temp_f0_6, temp_r31->unk30 + temp_f0_7, temp_r31->unk34 + temp_f0_8);
        omSetRot(obj, temp_r31->unk38, temp_r31->unk3C, temp_r31->unk40);
        if ((temp_r29->unk24 > 0.0f) && ((u32) (temp_r31->unk0 & 1) != 0)) {
            temp_f1 = Hu3DMotionTimeGet(lbl_1_bss_4C[temp_r31->unk1C]);
            if (temp_f1 < lbl_1_bss_44[temp_r31->unk1C]) {
                if ((s32) temp_r29->unk8 == 0) {
                    HuAudFXPlay(0x7B8);
                } else if ((s32) temp_r29->unk8 == 1) {
                    HuAudFXPlay(0x7B8);
                }
            }
            lbl_1_bss_44[temp_r31->unk1C] = temp_f1;
        }
    }
}

void fn_1_165C(omObjData *obj) {
    M533Player *temp_r29;
    M533Item *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk0 = (u32) obj->work[0];
    temp_r29 = lbl_1_bss_AC[temp_r31->unk0]->data;
    *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 9), MEMORY_DEFAULT_NUM, HEAP_DATA));
    lbl_1_bss_88[temp_r31->unk0] = *obj->model;
    Hu3DModelAttrSet(*obj->model, 1U);
    Hu3DModelCameraSet(*obj->model, (u16) (1 << temp_r29->unk20));
    temp_r31->unk4 = 0.0f;
    obj->trans.x = 0.0f;
    temp_r31->unk8 = 0.0f;
    obj->trans.y = 0.0f;
    temp_r31->unkC = 0.0f;
    obj->trans.z = 0.0f;
    temp_r31->unk4 = 0.0f;
    temp_r31->unk8 = 0.0f;
    temp_r31->unkC = 0.0f;
    omSetTra(obj, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, lbl_1_data_50[Mp5CharNo(temp_r29->unk14)], lbl_1_data_50[Mp5CharNo(temp_r29->unk14)], lbl_1_data_50[Mp5CharNo(temp_r29->unk14)]);
    Hu3DModelAttrReset(*obj->model, 1U);
    obj->func = fn_1_1840;
}

void fn_1_1840(omObjData *obj) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    omObjData *temp_r3;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    M533Team *temp_r28;
    M533Player *temp_r29;
    M533Item *temp_r31;

    temp_r31 = obj->data;
    temp_r29 = lbl_1_bss_AC[temp_r31->unk0]->data;
    temp_r3 = lbl_1_bss_A4[temp_r29->unk1C];
    temp_r28 = temp_r3->data;
    if (MgSeqModeGet() >= 5U) {
        if (MgSeqModeGet() == 5) {
            if (MgSeqFrameNoGet() == 0) {
                if ((u32) (temp_r29->unk0 & 1) != 0) {
                    temp_f0 = lbl_1_data_4FC.x - 80.0f;
                    temp_r31->unk4 = temp_f0;
                    obj->trans.x = temp_f0;
                } else {
                    temp_f0_2 = 110.0f + lbl_1_data_4FC.x;
                    temp_r31->unk4 = temp_f0_2;
                    obj->trans.x = temp_f0_2;
                }
                temp_r31->unk8 = (f32) lbl_1_data_4FC.y;
                obj->trans.y = lbl_1_data_4FC.y;
                temp_r31->unkC = (f32) lbl_1_data_4FC.z;
                obj->trans.z = lbl_1_data_4FC.z;
                omSetTra(obj, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
                return;
            }
            if (MgSeqFrameNoGet() == 1) {
                if ((u32) (temp_r29->unk0 & 1) != 0) {
                    temp_r31->unk4 = -80.0f;
                    obj->trans.x = -80.0f;
                } else {
                    temp_r31->unk4 = 110.0f;
                    obj->trans.x = 110.0f;
                }
                temp_r31->unk8 = 0.0f;
                obj->trans.y = 0.0f;
                temp_r31->unkC = 0.0f;
                obj->trans.z = 0.0f;
                omSetTra(obj, temp_r31->unk4, temp_r31->unk8, temp_r31->unkC);
            }
            goto block_12;
        }
block_12:
        temp_f0_3 = temp_r28->unkC;
        sp8 = temp_f0_3;
        temp_f0_4 = temp_r28->unk10;
        spC = temp_f0_4;
        temp_f0_5 = temp_r28->unk14;
        sp10 = temp_f0_5;
        temp_r31->unk4 = (f32) temp_r29->unk2C;
        temp_r31->unk8 = (f32) temp_r29->unk30;
        temp_r31->unkC = (f32) temp_r29->unk34;
        omSetTra(obj, temp_r31->unk4 + temp_f0_3, temp_r31->unk8 + temp_f0_4, temp_r31->unkC + temp_f0_5);
    }
}

void fn_1_1A5C(omObjData *obj, s32 motion) {
    M533Player *temp_r31;

    temp_r31 = obj->data;
    if ((s32) temp_r31->unk4 != motion) {
        temp_r31->unk4 = motion;
        CharMotionShiftSet((s16) temp_r31->unk14, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0x40000001U);
    }
}


void fn_1_1BA0(omObjData *obj) {
    s32 temp_r3;
    M533Player *temp_r31;

    temp_r31 = obj->data;
    if ((s32) temp_r31->unk4 != 3) {
        temp_r31->unk4 = 3;
        Hu3DMotionShiftSet(*obj->model, obj->motion[temp_r31->unk4], 0.0f, 8.0f, 0U);
        temp_r31->unk28 = 8;
        return;
    }
    temp_r3 = temp_r31->unk28;
    temp_r31->unk28 = (s32) (temp_r3 - 1);
    if (temp_r3 == 0) {
        Hu3DMotionTimeSet(*obj->model, 0.0f);
        Hu3DMotionSpeedSet(*obj->model, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_4C[temp_r31->unk1C], 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_4C[temp_r31->unk1C], 0.0f);
        temp_r31->unk60 = 0.0f;
    }
}

s32 fn_1_1CD0(omObjData *obj) {
    s32 var_r30;
    M533Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk80 = (s32) temp_r31->unk84;
    if ((temp_r31->unk8C > temp_r31->unk98) || (((M533Team *)lbl_1_bss_A4[temp_r31->unk1C]->data)->unkC >= 10670.0f)) {
        if ((s32) temp_r31->unk88 >= (s32) temp_r31->unk80) {
            var_r30 = 0x60;
            temp_r31->unk88 = 0;
            fn_1_1E3C(obj);
        } else {
            temp_r31->unk88 = (s32) (temp_r31->unk88 + 1);
            var_r30 = 0;
        }
    } else {
        var_r30 = 0x800;
    }
    return var_r30;
}


void fn_1_1E3C(omObjData *obj) {
    s32 var_r29;
    s32 var_r30;
    M533Player *temp_r31;

    temp_r31 = obj->data;
    if ((temp_r31->unk8C <= 100.0f) && (temp_r31->unk8C >= 80.0f)) {
        var_r29 = lbl_1_data_540[temp_r31->unk7C].unk4;
        var_r30 = lbl_1_data_540[temp_r31->unk7C].unk0;
    } else if ((temp_r31->unk8C <= 79.0f) && (temp_r31->unk8C >= 60.0f)) {
        var_r29 = lbl_1_data_540[temp_r31->unk7C].unkC;
        var_r30 = lbl_1_data_540[temp_r31->unk7C].unk8;
    } else {
        var_r29 = lbl_1_data_540[temp_r31->unk7C].unk14;
        var_r30 = lbl_1_data_540[temp_r31->unk7C].unk10;
    }
    temp_r31->unk84 = (s32) (var_r30 + frandmod(var_r29 - var_r30));
}

void fn_1_1F98(omObjData *obj) {
    M533Player *sp8[4];
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r25;
    s16 var_r26;
    s32 var_r27;
    M533Team *temp_r31;

    temp_r31 = obj->data;
    var_r27 = 0;
loop_2:
    if (var_r27 < 4) {
        sp8[var_r27] = lbl_1_bss_AC[var_r27]->data;
        var_r27 += 1;
        goto loop_2;
    }
    temp_r31->unk8 = (u32) obj->work[0];
    temp_r31->unk38 = 0.0f;
    temp_r31->unk3C = 0;
    temp_r31->unk40 = 0;
    temp_r31->unk2C = 0.0f;
    temp_r31->unk28 = 0.0f;
    temp_r31->unk24 = 0.0f;
    temp_r31->unk30 = 0.0f;
    temp_r31->unk0 = 0;
    if ((s32) temp_r31->unk8 == 0) {
        temp_r3 = fn_1_2698(0);
        if ((u32) (sp8[temp_r3]->unk0 & 1) != 0) {
            var_r26 = temp_r3;
            var_r25 = (s16) sp8[temp_r3]->unk10;
        } else {
            var_r25 = temp_r3;
            var_r26 = (s16) sp8[temp_r3]->unk10;
        }
        *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    } else {
        temp_r3_2 = fn_1_2698(1);
        if ((u32) (sp8[temp_r3_2]->unk0 & 1) != 0) {
            var_r26 = temp_r3_2;
            var_r25 = (s16) sp8[temp_r3_2]->unk10;
        } else {
            var_r25 = temp_r3_2;
            var_r26 = (s16) sp8[temp_r3_2]->unk10;
        }
        *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    }
    lbl_1_bss_84[temp_r31->unk8] = *obj->model;
    Hu3DModelCameraSet(*obj->model, (u16) (1 << temp_r31->unk8));
    Hu3DMotionSpeedSet(*obj->model, 0.0f);
    Hu3DModelAttrSet(*obj->model, 1U);
    temp_r31->unk20 = 0.0f;
    temp_r31->unk1C = 0.0f;
    temp_r31->unk18 = 0.0f;
    temp_r31->unkC = 0.0f;
    temp_r31->unk10 = 0.0f;
    temp_r31->unk14 = 0.0f;
    temp_r31->unkC = (f32) lbl_1_data_4F0.x;
    obj->trans.x = lbl_1_data_4F0.x;
    temp_r31->unk10 = (f32) lbl_1_data_4F0.y;
    obj->trans.y = lbl_1_data_4F0.y;
    temp_r31->unk14 = (f32) lbl_1_data_4F0.z;
    obj->trans.z = lbl_1_data_4F0.z;
    omSetTra(obj, temp_r31->unkC, temp_r31->unk10, temp_r31->unk14);
    omSetRot(obj, temp_r31->unk18, temp_r31->unk1C, temp_r31->unk20);
    lbl_1_bss_50[temp_r31->unk8] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_50[temp_r31->unk8], 1U);
    Hu3DModelCameraSet(lbl_1_bss_50[temp_r31->unk8], (u16) (1 << temp_r31->unk8));
    Hu3DModelPosSet(lbl_1_bss_50[temp_r31->unk8], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_50[temp_r31->unk8], 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_50[temp_r31->unk8], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_50[temp_r31->unk8], Hu3DMotionMaxTimeGet(lbl_1_bss_50[temp_r31->unk8]));
    lbl_1_bss_4C[temp_r31->unk8] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_4C[temp_r31->unk8], 1U);
    Hu3DModelCameraSet(lbl_1_bss_4C[temp_r31->unk8], (u16) (1 << temp_r31->unk8));
    Hu3DModelPosSet(lbl_1_bss_4C[temp_r31->unk8], 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_4C[temp_r31->unk8], 0.0f, 0.0f, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_4C[temp_r31->unk8], 0.0f);
    lbl_1_bss_44[temp_r31->unk8] = 99.0f;
    Hu3DModelHookSet(lbl_1_bss_84[temp_r31->unk8], "itemhook_play", lbl_1_bss_90[var_r26]);
    Hu3DModelHookSet(lbl_1_bss_84[temp_r31->unk8], "itemhook_taiki", lbl_1_bss_90[var_r25]);
    Hu3DModelHookSet(lbl_1_bss_84[temp_r31->unk8], "front_itemhook", lbl_1_bss_50[temp_r31->unk8]);
    Hu3DModelHookSet(lbl_1_bss_84[temp_r31->unk8], "back_itemhook", lbl_1_bss_4C[temp_r31->unk8]);
    Hu3DModelAttrReset(*obj->model, 1U);
    Hu3DModelAttrReset(lbl_1_bss_50[temp_r31->unk8], 1U);
    Hu3DModelAttrReset(lbl_1_bss_4C[temp_r31->unk8], 1U);
    obj->func = fn_1_2724;
}

s16 fn_1_2698(s32 team) {
    M533Player *sp8[4];
    s16 var_r30;
    s16 var_r31_2;
    s32 var_r31;

    var_r30 = 0 /* TODO(mp5): uninitialised in the original */;
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp8[var_r31] = lbl_1_bss_AC[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_7:
    if (var_r31_2 < 4) {
        if (team == (s32) sp8[var_r31_2]->unk1C) {
            var_r30 = var_r31_2;
        } else {
            var_r31_2 += 1;
            goto loop_7;
        }
    }
    return var_r30;
}

void fn_1_2724(omObjData *obj) {
    M533Pillar *sp18[0x18];
    M533Cloud *sp8[4];
    f32 temp_f1;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    M533Team *temp_r31;

    temp_r31 = obj->data;
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        sp8[var_r30] = lbl_1_bss_A0[var_r30]->data;
        var_r30 += 1;
        goto loop_2;
    }
    var_r30_2 = 0;
loop_5:
    if (var_r30_2 < 0x18) {
        sp18[var_r30_2] = lbl_1_bss_9C[var_r30_2]->data;
        var_r30_2 += 1;
        goto loop_5;
    }
    if (temp_r31->unk24 > 5.0f) {
        temp_r31->unk24 = 5.0f;
    }
    temp_r31->unkC = (f32) (temp_r31->unkC + temp_r31->unk24);
    temp_f1 = temp_r31->unk30;
    temp_r31->unk30 = (f32) (temp_f1 + temp_r31->unk24);
    if (MgSeqModeGet() >= 5U) {
        temp_r31->unk38 = (f32) (temp_r31->unk38 + 2.0f);
        if (temp_r31->unk38 > 360.0f) {
            temp_r31->unk38 = 0.0f;
        }
        temp_r31->unk10 = (f32) ((f64) lbl_1_data_4FC.y + (20.0 * sin((3.141592653589793 * (f64) temp_r31->unk38) / 180.0)));
    }
    if (((s32) temp_r31->unk3C == 0) && (temp_r31->unk30 > 3333.0f)) {
        if ((s32) temp_r31->unk8 == 0) {
            if ((s32) sp8[0]->unk10 == 0) {
                sp8[0]->unk10 = 1;
                sp8[2]->unk10 = 1;
            }
        } else if ((s32) sp8[1]->unk10 == 0) {
            sp8[1]->unk10 = 1;
            sp8[3]->unk10 = 1;
        }
        temp_r31->unk3C = 1;
    }
    if (((s32) temp_r31->unk40 == 0) && (temp_r31->unkC > 6000.0f)) {
        if ((s32) temp_r31->unk8 == 0) {
            if ((s32) sp18[0]->unk0 == 0) {
                var_r30_3 = 0;
loop_28:
                if (var_r30_3 < 0x18) {
                    sp18[var_r30_3]->unk0 = 1;
                    if (var_r30_3 > 0xC) {
                        Hu3DModelAttrSet(lbl_1_bss_54[var_r30_3], 1U);
                    }
                    var_r30_3 += 2;
                    goto loop_28;
                }
            }
        } else if ((s32) sp18[1]->unk0 == 0) {
            var_r30_4 = 1;
loop_35:
            if (var_r30_4 < 0x18) {
                sp18[var_r30_4]->unk0 = 1;
                if (var_r30_4 > 0xC) {
                    Hu3DModelAttrSet(lbl_1_bss_54[var_r30_4], 1U);
                }
                var_r30_4 += 2;
                goto loop_35;
            }
        }
        temp_r31->unk40 = 1;
    }
    if (MgSeqModeGet() == 5) {
        temp_r31->unk24 = (f32) (temp_r31->unk24 - 0.05f);
        if (temp_r31->unk24 < 0.0f) {
            temp_r31->unk24 = 0.0f;
        }
    }
    if ((MgSeqModeGet() == 5) && (MgSeqFrameNoGet() == 0)) {
        temp_r31->unkC = (f32) lbl_1_data_4FC.x;
        obj->trans.x = lbl_1_data_4FC.x;
        temp_r31->unk10 = (f32) lbl_1_data_4FC.y;
        obj->trans.y = lbl_1_data_4FC.y;
        temp_r31->unk14 = (f32) lbl_1_data_4FC.z;
        obj->trans.z = lbl_1_data_4FC.z;
        Hu3DMotionTimeSet(*obj->model, 0.0f);
        Hu3DMotionSpeedSet(*obj->model, 0.0f);
        Hu3DModelAttrReset(*obj->model, 0x40000001U);
        Hu3DModelHookObjReset(*obj->model, "itemhook_play");
        Hu3DModelHookObjReset(*obj->model, "itemhook_taiki");
        Hu3DModelHookObjReset(*obj->model, "itemhook_p_shadow");
        Hu3DModelHookObjReset(*obj->model, "itemhook_t_shadow");
    }
    omSetTra(obj, temp_r31->unkC, temp_r31->unk10, temp_r31->unk14);
    omSetRot(obj, temp_r31->unk18, temp_r31->unk1C, temp_r31->unk20);
    if (MgSeqModeGet() >= 5U) {
        CenterM[temp_r31->unk8].x = temp_r31->unkC;
        CenterM[temp_r31->unk8].y = 0.0f;
        CenterM[temp_r31->unk8].z = temp_r31->unk14;
    }
    if (temp_r31->unkC >= 11170.0f) {
        temp_r31->unk30 = 9670.0f;
        temp_r31->unk0 = 1;
        if (MgSeqModeGet() == 5) {
            MgSeqModeNext();
            lbl_1_bss_2C = MgSeqFrameNoGet();
        }
    }
    if ((s32) temp_r31->unk8 == 0) {
        if (temp_r31->unk24 > 0.0f) {
            if ((s32) lbl_1_bss_C == -1) {
                lbl_1_bss_C = HuAudFXPlay(0x7B7);
            }
        } else if ((s32) lbl_1_bss_C != -1) {
            HuAudFXStop(lbl_1_bss_C);
            lbl_1_bss_C = -1;
        }
    } else if (temp_r31->unk24 > 0.0f) {
        if ((s32) lbl_1_bss_8 == -1) {
            lbl_1_bss_8 = HuAudFXPlay(0x7B7);
        }
    } else if ((s32) lbl_1_bss_8 != -1) {
        HuAudFXStop(lbl_1_bss_8);
        lbl_1_bss_8 = -1;
    }
}

void fn_1_2D4C(s16 frameNo) {
    M533Player *sp20[4];
    M533Player *sp10[4];
    M533Team *sp8[4];
    s16 var_r25;
    s16 var_r27;
    s16 var_r28;
    s16 var_r30_2;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    var_r25 = 0 /* TODO(mp5): uninitialised in the original */;
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        sp8[var_r31] = lbl_1_bss_A4[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 4) {
        sp20[var_r31_2] = lbl_1_bss_AC[var_r31_2]->data;
        var_r31_2 += 1;
        goto loop_5;
    }
    lbl_1_bss_28 = 0;
    fn_1_44D4();
    lbl_1_bss_24 = 0.0f;
    lbl_1_bss_10[5] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_10[5], 1U);
    Hu3DModelAttrSet(lbl_1_bss_10[5], 0x40000001U);
    Hu3DModelCameraSet(lbl_1_bss_10[5], 3U);
    Hu3DModelPosSet(lbl_1_bss_10[5], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[5], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[4] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_10[4], 1U);
    Hu3DModelCameraSet(lbl_1_bss_10[4], 3U);
    Hu3DModelPosSet(lbl_1_bss_10[4], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[4], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[6] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_10[6], 1U);
    Hu3DModelCameraSet(lbl_1_bss_10[6], 3U);
    Hu3DModelPosSet(lbl_1_bss_10[6], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[6], 0.0f, 0.0f, 0.0f);
    lbl_1_bss_10[7] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_84[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(lbl_1_bss_10[7], 1U);
    Hu3DModelCameraSet(lbl_1_bss_10[7], 3U);
    Hu3DModelPosSet(lbl_1_bss_10[7], 0.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_10[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_10[5], 1U);
    Hu3DModelAttrReset(lbl_1_bss_10[4], 1U);
    Hu3DModelAttrReset(lbl_1_bss_10[6], 1U);
    Hu3DModelAttrReset(lbl_1_bss_10[7], 1U);
    lbl_1_bss_40 = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M533, 13), 0xA, 0);
    espDispOff(lbl_1_bss_40);
    espDrawNoSet(lbl_1_bss_40, 0);
    espPosSet(lbl_1_bss_40, 16.0f, 224.0f);
    lbl_1_bss_3E = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M533, 14), 0xA, 0);
    espDispOff(lbl_1_bss_3E);
    espDrawNoSet(lbl_1_bss_3E, 0);
    espPosSet(lbl_1_bss_3E, 16.0f, 256.0f);
    lbl_1_bss_3C = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M533, 12), 0xB, 0);
    espDispOff(lbl_1_bss_3C);
    espDrawNoSet(lbl_1_bss_3C, 0);
    espPosSet(lbl_1_bss_3C, 320.0f, 240.0f);
    fn_1_48BC(0);
    var_r31_3 = 0;
loop_19:
    if (var_r31_3 < 2) {
        var_r30 = 0;
loop_9:
        if (var_r30 < 4) {
            sp10[var_r30] = lbl_1_bss_AC[var_r30]->data;
            var_r30 += 1;
            goto loop_9;
        }
        var_r30_2 = 0;
loop_14:
        if (var_r30_2 < 4) {
            if (var_r31_3 == (s32) sp10[var_r30_2]->unk1C) {
                var_r25 = var_r30_2;
            } else {
                var_r30_2 += 1;
                goto loop_14;
            }
        }
        if ((u32) (sp20[var_r25]->unk0 & 1) != 0) {
            var_r28 = var_r25;
            var_r27 = (s16) sp20[var_r25]->unk10;
        } else {
            var_r27 = var_r25;
            var_r28 = (s16) sp20[var_r25]->unk10;
        }
        Hu3DModelHookSet(lbl_1_bss_84[sp8[var_r31_3]->unk8], "itemhook_p_shadow", lbl_1_bss_88[var_r28]);
        Hu3DModelHookSet(lbl_1_bss_84[sp8[var_r31_3]->unk8], "itemhook_t_shadow", lbl_1_bss_88[var_r27]);
        var_r31_3 += 1;
        goto loop_19;
    }
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
    }
}

void fn_1_3424(s16 mode, s16 frameNo) {
    M533Player *sp14[4];
    M533Team *spC[4];
    s16 sp8;
    omObjData *temp_r27;
    omObjData *temp_r28;
    f32 temp_f31;
    f32 var_f30;
    s16 var_r31_4;
    s32 var_r31;
    s32 var_r31_10;
    s32 var_r31_11;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_5;
    s32 var_r31_6;
    s32 var_r31_7;
    s32 var_r31_8;
    s32 var_r31_9;
    M533Player *temp_r29;
    M533Player *temp_r30;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        spC[var_r31] = lbl_1_bss_A4[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 4) {
        sp14[var_r31_2] = lbl_1_bss_AC[var_r31_2]->data;
        var_r31_2 += 1;
        goto loop_5;
    }
    fn_1_46A4(0.0f);
    lbl_1_data_1C = HuAudFXPlay(0x7B9);
    Hu3DModelAttrReset(lbl_1_bss_10[4], 0x40000001U);
    Hu3DModelAttrReset(lbl_1_bss_10[6], 0x40000001U);
    Hu3DModelAttrReset(lbl_1_bss_10[7], 0x40000001U);
    var_r31_3 = 0;
loop_8:
    if (var_r31_3 < 0x7D) {
        HuPrcVSleep();
        var_r31_3 += 1;
        goto loop_8;
    }
    var_r31_4 = 0;
loop_11:
    if (var_r31_4 < 4) {
        omVibrate(var_r31_4, 0xF, 0xC, 0);
        var_r31_4 += 1;
        goto loop_11;
    }
    HuAudFXPlay(0x7B6);
    var_r31_5 = 0;
loop_14:
    if (var_r31_5 < 2) {
        Hu3DMotionTimeSet(lbl_1_bss_84[var_r31_5], 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_84[var_r31_5], 1.0f);
        var_r31_5 += 1;
        goto loop_14;
    }
    var_r31_6 = 0;
loop_17:
    if (var_r31_6 < 0xA) {
        HuPrcVSleep();
        var_r31_6 += 1;
        goto loop_17;
    }
    sp8 = omCameraViewMoveSimpleMulti(3U, &lbl_1_data_524, 0xF0);
    var_r31_7 = 0;
loop_24:
    if (var_r31_7 < 4) {
        temp_r28 = lbl_1_bss_AC[var_r31_7];
        temp_r29 = temp_r28->data;
        if ((s32) temp_r29->unk4 != 7) {
            temp_r29->unk4 = 7;
            CharMotionShiftSet((s16) temp_r29->unk14, temp_r28->motion[temp_r29->unk4], 0.0f, 8.0f, 0x40000001U);
        }
        if ((s32) sp14[var_r31_7]->unk1C == 0) {
            CharFXPlay((s16) sp14[var_r31_7]->unk14, 0x1FF);
        }
        var_r31_7 += 1;
        goto loop_24;
    }
    var_r31_8 = 0;
loop_27:
    if (var_r31_8 < 0x78) {
        HuPrcVSleep();
        var_r31_8 += 1;
        goto loop_27;
    }
    var_r31_9 = 0;
loop_32:
    if (var_r31_9 < 4) {
        temp_r27 = lbl_1_bss_AC[var_r31_9];
        temp_r30 = temp_r27->data;
        if ((s32) temp_r30->unk4 != 0) {
            temp_r30->unk4 = 0;
            CharMotionShiftSet((s16) temp_r30->unk14, temp_r27->motion[temp_r30->unk4], 0.0f, 10.0f, 0x40000001U);
            if (lbl_1_bss_30 == -1) {

            }
        }
        var_r31_9 += 1;
        goto loop_32;
    }
    var_r31_10 = 0;
loop_35:
    if (var_r31_10 < 0x11) {
        HuPrcVSleep();
        var_r31_10 += 1;
        goto loop_35;
    }
    var_r31_11 = 0;
loop_38:
    if ((f32) var_r31_11 < 55.0f) {
        HuPrcVSleep();
        var_r31_11 += 1;
        goto loop_38;
    }
    var_f30 = 0.0f;
    do {
        temp_f31 = (f32) sin((3.141592653589793 * (f64) (90.0f * var_f30)) / 180.0);
        fn_1_46A4(0.5f * (temp_f31 * temp_f31));
        HuPrcVSleep();
        var_f30 += 0.016666668f;
    } while (var_f30 < 1.0f);
    fn_1_48BC(1);
    lbl_1_bss_1BC = HuAudSStreamPlay(0x33);
    MgSeqModeNext();
}

void fn_1_3890(s16 mode, s16 frameNo) {
    M533Player *sp10[4];
    M533Player *sp8[4];
    s32 var_r31;
    s32 var_r31_2;

    fn_1_44D4();
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp10[var_r31] = lbl_1_bss_AC[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 2) {
        sp8[var_r31_2] = lbl_1_bss_AC[var_r31_2]->data;
        var_r31_2 += 1;
        goto loop_5;
    }
    fn_1_48B8();
    if (MgSeqTimerValueGet() == 0U) {
        MgSeqModeNext();
    }
    fn_1_48BC(1);
}

void fn_1_3950(s16 frameNo) {
    M533Player *sp18[4];
    M533Team *sp10[2];
    s32 sp8[4];
    omObjData *temp_r28;
    s16 temp_r27;
    s32 var_r29;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    M533Player *temp_r30;

    fn_1_44D4();
    if (MgSeqFrameNoGet() == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_1BC, 0x64);
        var_r31 = 0;
loop_6:
        if (var_r31 < 4) {
            lbl_1_bss_34[var_r31] = -1;
            sp18[var_r31] = lbl_1_bss_AC[var_r31]->data;
            if ((u32) (sp18[var_r31]->unk0 & 1) != 0) {
                temp_r28 = lbl_1_bss_AC[var_r31];
                temp_r30 = temp_r28->data;
                if ((s32) temp_r30->unk4 != 0) {
                    temp_r30->unk4 = 0;
                    CharMotionShiftSet((s16) temp_r30->unk14, temp_r28->motion[temp_r30->unk4], 0.0f, 8.0f, 0x40000001U);
                    if (lbl_1_bss_30 == -1) {

                    }
                }
            }
            var_r31 += 1;
            goto loop_6;
        }
        var_r31_2 = 0;
loop_9:
        if (var_r31_2 < 2) {
            sp10[var_r31_2] = lbl_1_bss_A4[var_r31_2]->data;
            Hu3DModelAttrReset(lbl_1_bss_4C[var_r31_2], 0x40000001U);
            sp10[var_r31_2]->unk44 = 0;
            var_r31_2 += 1;
            goto loop_9;
        }
        if (((s32) sp10[0]->unk0 == 0) && ((s32) sp10[1]->unk0 == 0)) {
            lbl_1_bss_30 = -1;
        } else if (((s32) sp10[0]->unk0 != 0) && ((s32) sp10[1]->unk0 != 0)) {
            lbl_1_bss_30 = frandmod(2U);
        } else if ((s32) sp10[0]->unk0 != 0) {
            lbl_1_bss_30 = 0;
        } else {
            lbl_1_bss_30 = 1;
        }
        if ((u32) lbl_1_bss_30 == 0U) {
            fn_1_6770(lbl_1_bss_B0, 1U);
        } else if ((u32) lbl_1_bss_30 == 1U) {
            fn_1_6770(lbl_1_bss_B0, 2U);
        }
        var_r31_3 = 0;
        var_r29 = 0;
loop_28:
        if (var_r31_3 < 4) {
            if ((u32) lbl_1_bss_30 == (u32) sp18[var_r31_3]->unk1C) {
                lbl_1_bss_34[var_r29] = (s16) sp18[var_r31_3]->unk14;
                sp8[var_r29] = sp18[var_r31_3]->unkC;
                var_r29 += 1;
                temp_r27 = GWPlayer[var_r31_3].coin_win + 0xA;
                if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                    GWPlayer[var_r31_3].coin_win = temp_r27;
                }
            }
            var_r31_3 += 1;
            goto loop_28;
        }
        if (lbl_1_bss_30 == -1) {
            MgSeqWinnerSet(-1, -1, -1, -1);
            return;
        }
        if ((u32) (sp18[sp8[0]]->unk0 & 1) != 0) {
            MgSeqWinnerSet(lbl_1_bss_34[0], lbl_1_bss_34[1], -1, -1);
            return;
        }
        MgSeqWinnerSet(lbl_1_bss_34[1], lbl_1_bss_34[0], -1, -1);
    }
}

void fn_1_3D50(s16 mode, s16 frameNo) {
    M533Player *sp14[4];
    M533Team *spC[4];
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s16 sp8;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f30;
    s32 var_r31;
    s32 var_r31_2;

    sp8 = frameNo;
    fn_1_44D4();
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp14[var_r31] = lbl_1_bss_AC[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 2) {
        spC[var_r31_2] = lbl_1_bss_A4[var_r31_2]->data;
        var_r31_2 += 1;
        goto loop_5;
    }
    if (lbl_1_bss_30 == -1) {
        if (sp8 == 0x3C) {
            MgSeqModeNext();
        }
        return;
    }
    if (MgSeqFrameNoGet() >= 0x3CU) {
        sp24 = 50.0f + spC[lbl_1_bss_30]->unkC;
        sp28 = 100.0f + spC[lbl_1_bss_30]->unk10;
        sp2C = spC[lbl_1_bss_30]->unk14;
        sp30 = 0.0f;
        sp34 = 0.0f;
        sp38 = 0.0f;
        sp3C = 1200.0f;
        if ((u32) lbl_1_bss_2C < 0x960U) {
            fn_1_52C4();
        }
        fn_1_48BC(0);
        var_f30 = 0.0f;
        if ((u32) lbl_1_bss_30 == 0U) {
            do {
                temp_f31 = (f32) sin((3.141592653589793 * (f64) (90.0f * var_f30)) / 180.0);
                fn_1_46A4(0.5f - (0.5f * (temp_f31 * temp_f31)));
                HuPrcVSleep();
                var_f30 += 0.016666668f;
            } while (var_f30 < 1.0f);
            fn_1_46A4(0.0f);
        } else {
            do {
                temp_f31_2 = (f32) sin((3.141592653589793 * (f64) (90.0f * var_f30)) / 180.0);
                fn_1_46A4(0.5f + (0.5f * (temp_f31_2 * temp_f31_2)));
                HuPrcVSleep();
                var_f30 += 0.016666668f;
            } while (var_f30 < 1.0f);
            fn_1_46A4(1.0f);
        }
        MgSeqModeNext();
    }
}

void fn_1_4080(s16 frameNo) {
    M533Player *sp8[4];
    omObjData *temp_r20;
    omObjData *temp_r21;
    omObjData *temp_r22;
    omObjData *temp_r23;
    omObjData *temp_r24;
    s32 var_r25;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    M533Player *temp_r26;
    M533Player *temp_r27;
    M533Player *temp_r28;
    M533Player *temp_r29;
    M533Player *temp_r30;
    M533Player *temp_r4;
    M533Player *temp_r4_2;

    fn_1_44D4();
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp8[var_r31] = lbl_1_bss_AC[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    if (lbl_1_bss_30 == -1) {
        var_r31_2 = 0;
loop_9:
        if (var_r31_2 < 4) {
            temp_r24 = lbl_1_bss_AC[var_r31_2];
            temp_r30 = temp_r24->data;
            if ((s32) temp_r30->unk4 != 2) {
                temp_r30->unk4 = 2;
                CharMotionShiftSet((s16) temp_r30->unk14, temp_r24->motion[temp_r30->unk4], 0.0f, 8.0f, 0U);
                if (lbl_1_bss_30 == -1) {
                    CharFXPlay((s16) temp_r30->unk14, 0x200);
                }
            }
            var_r31_2 += 1;
            goto loop_9;
        }
    } else {
        var_r31_3 = 0;
loop_28:
        if (var_r31_3 < 4) {
            if ((u32) lbl_1_bss_30 == (u32) sp8[var_r31_3]->unk1C) {
                if (Mp5CharNo(sp8[var_r31_3]->unk14) == 6) {
                    temp_r23 = lbl_1_bss_AC[var_r31_3];
                    temp_r29 = temp_r23->data;
                    if ((s32) temp_r29->unk4 != 8) {
                        temp_r29->unk4 = 8;
                        CharMotionShiftSet((s16) temp_r29->unk14, temp_r23->motion[temp_r29->unk4], 0.0f, 8.0f, 0U);
                        if (lbl_1_bss_30 == -1) {

                        }
                    }
                } else if (Mp5CharNo(sp8[var_r31_3]->unk14) == 8) {
                    temp_r22 = lbl_1_bss_AC[var_r31_3];
                    temp_r28 = temp_r22->data;
                    if ((s32) temp_r28->unk4 != 9) {
                        temp_r28->unk4 = 9;
                        CharMotionShiftSet((s16) temp_r28->unk14, temp_r22->motion[temp_r28->unk4], 0.0f, 8.0f, 0U);
                        if (lbl_1_bss_30 == -1) {

                        }
                    }
                } else {
                    temp_r21 = lbl_1_bss_AC[var_r31_3];
                    temp_r27 = temp_r21->data;
                    if ((s32) temp_r27->unk4 != 1) {
                        temp_r27->unk4 = 1;
                        CharMotionShiftSet((s16) temp_r27->unk14, temp_r21->motion[temp_r27->unk4], 0.0f, 8.0f, 0U);
                        if (lbl_1_bss_30 == -1) {

                        }
                    }
                }
            } else {
                temp_r20 = lbl_1_bss_AC[var_r31_3];
                temp_r26 = temp_r20->data;
                if ((s32) temp_r26->unk4 != 2) {
                    temp_r26->unk4 = 2;
                    CharMotionShiftSet((s16) temp_r26->unk14, temp_r20->motion[temp_r26->unk4], 0.0f, 8.0f, 0U);
                    if (lbl_1_bss_30 == -1) {
                        CharFXPlay((s16) temp_r26->unk14, 0x200);
                    }
                }
            }
            var_r31_3 += 1;
            goto loop_28;
        }
    }
    var_r25 = 0;
loop_35:
    if (var_r25 < 4) {
        if ((u32) (sp8[var_r25]->unk0 & 1) != 0) {
            if (sp8[var_r25]->unk3C < 0.0f) {
                temp_r4 = sp8[var_r25];
                temp_r4->unk3C = (f32) (temp_r4->unk3C + 11.25f);
                temp_r4_2 = sp8[var_r25];
                temp_r4_2->unk2C = (f32) (temp_r4_2->unk2C + 1.25f);
            } else {
                sp8[var_r25]->unk3C = 0.0f;
            }
        }
        var_r25 += 1;
        goto loop_35;
    }
}

void fn_1_44D4(void) {

}


f32 fn_1_45B8(s32 frames) {
    f32 var_f31;

    if ((frames >= 1) && (frames <= 5)) {
        var_f31 = 4.0f;
    } else if ((frames >= 6) && (frames <= 0xA)) {
        var_f31 = 3.5f;
    } else if ((frames >= 0xB) && (frames <= 0xF)) {
        var_f31 = 3.0f;
    } else if ((frames >= 0x10) && (frames <= 0x14)) {
        var_f31 = 2.5f;
    } else if ((frames >= 0x15) && (frames <= 0x19)) {
        var_f31 = 2.0f;
    } else if ((frames >= 0x1A) && (frames <= 0x1E)) {
        var_f31 = 1.5f;
    } else {
        var_f31 = 1.0f;
    }
    return var_f31;
}

void fn_1_46A4(f32 farg0) {
    Hu3DCameraPerspectiveSet(1, 30.0f, 10.0f, 10000.0f, 1.3333334f);
    Hu3DCameraViewportSet(1, 0.0f, -(480.0f * farg0 * 0.5f), 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0U, 0U, 0x280U, (u32) (480.0f * (1.0f - farg0)));
    Hu3DCameraPerspectiveSet(2, 30.0f, 10.0f, 10000.0f, 1.3333334f);
    Hu3DCameraViewportSet(2, 0.0f, (480.0f - (480.0f * farg0)) * 0.5f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0U, (u32) (480.0f - (480.0f * farg0)), 0x280U, (u32) (480.0f * farg0));
}

void fn_1_48B8(void) {

}

void fn_1_48BC(s32 on) {
    M533Player *spC[4];
    s32 sp8;
    s32 var_r31;

    sp8 = on;
    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        spC[var_r31] = lbl_1_bss_A4[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    espPosSet(lbl_1_bss_40, 32.0f + (512.0f * (spC[0]->unk30 / 10000.0f)), 224.0f);
    espPosSet(lbl_1_bss_3E, 32.0f + (512.0f * (spC[1]->unk30 / 10000.0f)), 256.0f);
    if (sp8 != 0) {
        espDispOn(lbl_1_bss_40);
        espDispOn(lbl_1_bss_3E);
        espDispOn(lbl_1_bss_3C);
        return;
    }
    espDispOff(lbl_1_bss_40);
    espDispOff(lbl_1_bss_3E);
    espDispOff(lbl_1_bss_3C);
}

void fn_1_4A44(omObjData *obj) {
    s16 temp_r0;
    s32 var_r29;
    u32 temp_r0_2;
    u32 temp_r4;
    M533Cloud *temp_r30;

    temp_r30 = obj->data;
    *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 16), MEMORY_DEFAULT_NUM, HEAP_DATA));
    var_r29 = 0;
loop_2:
    if (var_r29 < 2) {
        obj->motion[var_r29] = Hu3DJointMotion(*obj->model, HuDataSelHeapReadNum(lbl_1_data_48[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
        var_r29 += 1;
        goto loop_2;
    }
    temp_r30->unk14 = (u32) obj->work[0];
    temp_r30->unk0 = (f32) (-250.0f + (0.003921569f * (100.0f * (f32) frand())));
    temp_r30->unk4 = (f32) (180.0 * (atan2((f64) (500.0f + obj->trans.x), (f64) (100.0f + obj->trans.y)) / 3.141592653589793));
    temp_r30->unk10 = 0;
    temp_r0 = (frand() % 30) + 0x1E;
    temp_r30->unkC = temp_r0;
    temp_r30->unkE = temp_r0;
    temp_r30->unk8 = 0.0f;
    temp_r0_2 = temp_r30->unk14;
    temp_r4 = temp_r0_2 >> 0x1FU;
    Hu3DModelCameraSet(*obj->model, (u16) (1 << (((temp_r0_2 & 1) ^ temp_r4) - temp_r4)));
    obj->trans.x = lbl_1_data_A8[temp_r30->unk14].unk0;
    obj->trans.y = 300.0f + lbl_1_data_A8[temp_r30->unk14].unk4;
    obj->trans.z = lbl_1_data_A8[temp_r30->unk14].unk8;
    omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    obj->func = fn_1_4CC8;
}

void fn_1_4CC8(omObjData *obj) {
    s16 temp_r0;
    M533Cloud *temp_r31;

    temp_r31 = obj->data;
    if ((s32) temp_r31->unk10 != 0) {
        if (temp_r31->unk8 == 0.0f) {
            if ((s16) temp_r31->unkC == 0) {
                temp_r31->unk8 = (f32) (8.0f + (0.003921569f * (10.0f * (f32) frand())));
            } else {
                if ((s16) temp_r31->unkC == 6) {
                    Hu3DMotionShiftSet(*obj->model, obj->motion[1], 0.0f, 8.0f, 0U);
                    Hu3DModelAttrReset(*obj->model, 0x40000001U);
                }
                temp_r31->unkC = (s16) (temp_r31->unkC - 1);
                temp_r31->unk0 = (f32) (temp_r31->unk0 - 1.5f);
            }
        } else {
            temp_r31->unk0 = (f32) ((f64) temp_r31->unk0 + ((f64) temp_r31->unk8 * sin((3.141592653589793 * (f64) temp_r31->unk4) / 180.0)));
            obj->trans.x += 5.0f;
            temp_r31->unk8 = (f32) (temp_r31->unk8 * 0.94f);
            if (temp_r31->unk8 < 0.1f) {
                temp_r31->unk8 = 0.0f;
                temp_r0 = (frand() % 30) + 0x1E;
                temp_r31->unkC = temp_r0;
                temp_r31->unkE = temp_r0;
                Hu3DMotionSet(*obj->model, obj->motion[0]);
                Hu3DModelAttrSet(*obj->model, 0x40000001U);
            }
        }
        omSetTra(obj, obj->trans.x, temp_r31->unk0, obj->trans.z);
        if (obj->trans.y > 1000.0f) {
            Hu3DModelAttrSet(*obj->model, 1U);
            omSetTra(obj, lbl_1_data_D8[temp_r31->unk14].unk0, lbl_1_data_D8[temp_r31->unk14].unk4, lbl_1_data_D8[temp_r31->unk14].unk8);
            temp_r31->unk10 = 0;
        }
    }
}

void fn_1_4F84(omObjData *obj) {
    M533Pt *temp_r29;
    s32 temp_r0_2;
    u32 temp_r0;
    u32 temp_r0_3;
    u32 temp_r3;
    u32 temp_r4;
    M533Pillar *temp_r30;

    temp_r30 = obj->data;
    temp_r30->unk4 = (u32) obj->work[0];
    temp_r30->unk0 = 0;
    temp_r0 = temp_r30->unk4;
    temp_r3 = temp_r0 >> 0x1FU;
    temp_r30->unkC = (s32) (((temp_r0 & 1) ^ temp_r3) - temp_r3);
    temp_r30->unk10 = 0.0f;
    temp_r29 = &lbl_1_data_108[temp_r30->unk4];
    temp_r30->unk8 = (f32) temp_r29->unk10;
    temp_r0_2 = temp_r29->unkC;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 6), MEMORY_DEFAULT_NUM, HEAP_DATA));
        break;
    case 1:
        *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 7), MEMORY_DEFAULT_NUM, HEAP_DATA));
        break;
    case 2:
        *obj->model = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 8), MEMORY_DEFAULT_NUM, HEAP_DATA));
        break;
    }
    lbl_1_bss_54[temp_r30->unk4] = *obj->model;
    temp_r0_3 = temp_r30->unk4;
    temp_r4 = temp_r0_3 >> 0x1FU;
    Hu3DModelCameraSet(*obj->model, (u16) (1 << (((temp_r0_3 & 1) ^ temp_r4) - temp_r4)));
    obj->trans.x = temp_r29->unk0;
    obj->trans.y = temp_r29->unk4;
    obj->trans.z = temp_r29->unk8;
    omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    obj->func = fn_1_5154;
}

void fn_1_5154(omObjData *obj) {
    M533Pt *temp_r29;
    f32 var_f31;
    M533Pillar *temp_r31;

    temp_r31 = obj->data;
    temp_r29 = &lbl_1_data_2E8[temp_r31->unk4];
    if ((s32) temp_r31->unk0 != 0) {
        if (MgSeqModeGet() == 5) {
            if ((s32) temp_r31->unk4 < 0xC) {
                Hu3DModelAttrReset(*obj->model, 1U);
            } else {
                Hu3DModelAttrSet(*obj->model, 1U);
            }
        } else {
            Hu3DModelAttrReset(*obj->model, 1U);
        }
        obj->trans.x += temp_r31->unk8;
        if (temp_r31->unk8 < 0.0f) {
            var_f31 = -temp_r31->unk8;
        } else {
            var_f31 = temp_r31->unk8;
        }
        temp_r31->unk10 = (f32) (temp_r31->unk10 + var_f31);
        omSetTra(obj, obj->trans.x, obj->trans.y, obj->trans.z);
        if (temp_r31->unk10 > 3000.0f) {
            Hu3DModelAttrSet(*obj->model, 1U);
            omSetTra(obj, temp_r29->unk0, temp_r29->unk4, temp_r29->unk8);
            temp_r31->unk0 = 0;
            temp_r31->unk8 = (f32) temp_r29->unk10;
            temp_r31->unk10 = 0.0f;
        }
    }
}

void fn_1_52C4(void) {
    M533Pillar *sp18[0x18];
    M533Cloud *sp8[4];
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    u32 temp_r4;
    u32 temp_r4_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp8[var_r31] = lbl_1_bss_A0[var_r31]->data;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 0x18) {
        sp18[var_r31_2] = lbl_1_bss_9C[var_r31_2]->data;
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_10:
    if (var_r31_3 < 4) {
        temp_r4 = (u32) var_r31_3 >> 0x1FU;
        if ((u32) lbl_1_bss_30 == (u32) (((var_r31_3 & 1) ^ temp_r4) - temp_r4)) {
            sp8[var_r31_3]->unk10 = 1;
            sp8[var_r31_3]->unk8 = 0.0f;
            sp8[var_r31_3]->unk4 = (f32) (180.0 * (atan2((f64) (500.0f + lbl_1_bss_A0[var_r31_3]->trans.x), (f64) (100.0f + lbl_1_bss_A0[var_r31_3]->trans.y)) / 3.141592653589793));
            sp8[var_r31_3]->unk0 = (f32) (-250.0f + (0.003921569f * (100.0f * (f32) frand())));
            Hu3DModelAttrReset(*lbl_1_bss_A0[var_r31_3]->model, 1U);
        }
        var_r31_3 += 1;
        goto loop_10;
    }
    var_r31_4 = 0;
loop_15:
    if (var_r31_4 < 0x18) {
        temp_r4_2 = (u32) var_r31_4 >> 0x1FU;
        if ((u32) lbl_1_bss_30 == (u32) (((var_r31_4 & 1) ^ temp_r4_2) - temp_r4_2)) {
            sp18[var_r31_4]->unk0 = 1;
            Hu3DModelAttrReset(*lbl_1_bss_9C[var_r31_4]->model, 1U);
        }
        var_r31_4 += 1;
        goto loop_15;
    }
}


















void fn_1_6528(void) {
    lbl_1_bss_2CC = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M533, 15), MEMORY_DEFAULT_NUM, HEAP_DATA);
    lbl_1_bss_2C8 = HuSprAnimRead(lbl_1_bss_2CC);
    lbl_1_bss_2D4 = 0;
}

void fn_1_6590(omObjData *obj) {
    Vec spC;
    omObjData *sp8;
    s32 var_r31;

    sp8 = obj;
    var_r31 = 0;
loop_9:
    if (var_r31 >= 0xC) {
        return;
    }
    if ((lbl_1_data_670[lbl_1_bss_2D4].unk0 == 0.0f) && (lbl_1_data_670[lbl_1_bss_2D4].unk4 == 0.0f) && (lbl_1_data_670[lbl_1_bss_2D4].unk8 == 0.0f)) {
        OSReport("******* No entry PillarPoint *********\n", lbl_1_bss_2D4 * 0xC, 0.0f);
        return;
    }
    spC.x = lbl_1_data_670[lbl_1_bss_2D4].unk0;
    spC.y = 300.0f + lbl_1_data_670[lbl_1_bss_2D4].unk4;
    spC.z = lbl_1_data_670[lbl_1_bss_2D4].unk8;
    if (spC.z < 0.0f) {

    }
    fn_1_6984(sp8, &spC, 0, 3U);
    lbl_1_bss_2D4 += 1;
    var_r31 += 1;
    goto loop_9;
}

void fn_1_6770(omObjData *obj, u16 cameraBit) {
    Vec sp8;

    sp8.x = 11400.0f;
    sp8.y = -400.0f;
    sp8.z = -600.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
    sp8.x = 11500.0f;
    sp8.y = -400.0f;
    sp8.z = -600.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
    sp8.x = 11600.0f;
    sp8.y = -400.0f;
    sp8.z = -600.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
    sp8.x = 11400.0f;
    sp8.y = -400.0f;
    sp8.z = 1000.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
    sp8.x = 11500.0f;
    sp8.y = -400.0f;
    sp8.z = 1000.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
    sp8.x = 11600.0f;
    sp8.y = -400.0f;
    sp8.z = 1000.0f;
    fn_1_6984(obj, &sp8, 1, cameraBit);
}

void fn_1_6984(omObjData *obj, Vec *pos, s32 big, u16 cameraBit) {
    u16 sp8;

    sp8 = cameraBit;
    if (big == 0) {
        *obj->model = Hu3DParticleCreate(lbl_1_bss_2C8, 0x32);
    } else {
        *obj->model = Hu3DParticleCreate(lbl_1_bss_2C8, 0x64);
    }
    Hu3DModelCameraSet(*obj->model, sp8);
    Hu3DModelAttrSet(*obj->model, 1U);
    Hu3DModelPosSet(*obj->model, pos->x, pos->y, pos->z);
    Hu3DModelLayerSet(*obj->model, 5);
    if (big == 0) {
        Hu3DParticleHookSet(*obj->model, fn_1_6B18);
    } else {
        Hu3DParticleHookSet(*obj->model, fn_1_6F54);
    }
    Hu3DParticleBlendModeSet(*obj->model, 0U);
    Hu3DParticleColSet(*obj->model, 0xFFU, 0xFFU, 0xFFU);
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    omSetTra(obj, pos->x, pos->y, pos->z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(*obj->model, 1U);
}

void fn_1_6B18(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    HU3DPARTICLEDATA *var_r31_2;
    HU3DPARTICLEDATA *var_r31_3;
    s32 temp_r4;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    u32 temp_r3;
    u32 temp_ret;

    if ((u32) particleP->count == 0) {
        var_r31 = particleP->data;
        var_r29 = 0;
loop_3:
        if (var_r29 < (s16) particleP->maxCnt) {
            var_r31->color.a = 0;
            var_r31->scale = 0.0f;
            var_r29 += 1;
            var_r31++;
            goto loop_3;
        }
        particleP->dataCnt = 0;
    }
    if ((s16) particleP->dataCnt == 0) {
        var_r29_2 = 0;
loop_14:
        if (var_r29_2 < 2) {
            var_r31_2 = particleP->data;
            var_r28 = 0;
loop_10:
            if (var_r28 < (s16) particleP->maxCnt) {
                if ((u8) var_r31_2->color.a != 0) {
                    var_r28 += 1;
                    var_r31_2++;
                    goto loop_10;
                }
            }
            if (var_r28 != (s16) particleP->maxCnt) {
                var_r31_2->vel.x = -50.0f + (0.3921569f * (f32) frand());
                var_r31_2->vel.y = 0.058823533f * (f32) frand();
                var_r31_2->accel.x = 0.3529412f * (f32) frand();
                var_r31_2->accel.y = 5.0f + (0.098039225f * (f32) frand());
                var_r31_2->accel.z = 8.0f + (f32) (frand() % 10);
                var_r31_2->pos.z = -5.0f + (0.043137256f * (f32) frand());
                temp_ret = frand();
                temp_r3 = temp_ret;
                temp_r4 = temp_ret / 31;
                var_r31_2->pos.y = -5.0f + (f32) (temp_r3 - (((u32) (((u32) (temp_r3 - temp_r4) >> 1U) + temp_r4) >> 4U) * 0x1F));
                var_r31_2->scale = 35.0f + var_r31_2->vel.y;
                var_r31_2->color.a = 0xFF;
                var_r31_2->vel.y = (f32) (5.0 + (0.2 * (f64) var_r31_2->vel.y));
                particleP->dataCnt = (frand() % 10) + 0xA;
            }
            var_r29_2 += 1;
            goto loop_14;
        }
    } else {
        particleP->dataCnt -= 1;
    }
    var_r31_3 = particleP->data;
    var_r29_3 = 0;
loop_23:
    if (var_r29_3 < (s16) particleP->maxCnt) {
        if ((u8) var_r31_3->color.a != 0) {
            var_r31_3->pos.x = (f32) ((f64) var_r31_3->vel.x + ((f64) var_r31_3->accel.z * sin((3.141592653589793 * (f64) var_r31_3->accel.x) / 180.0)));
            var_r31_3->accel.x += var_r31_3->accel.y;
            if (var_r31_3->accel.x >= 360.0f) {
                var_r31_3->accel.x -= 360.0f;
            }
            var_r31_3->pos.y += var_r31_3->vel.y;
            var_r31_3->color.a -= 1;
        }
        var_r29_3 += 1;
        var_r31_3++;
        goto loop_23;
    }
}

void fn_1_6F54(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    HU3DPARTICLEDATA *var_r31_2;
    HU3DPARTICLEDATA *var_r31_3;
    s32 temp_r4;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    u32 temp_r3;
    u32 temp_ret;

    if ((u32) particleP->count == 0) {
        var_r31 = particleP->data;
        var_r29 = 0;
loop_3:
        if (var_r29 < (s16) particleP->maxCnt) {
            var_r31->color.a = 0;
            var_r31->scale = 0.0f;
            var_r29 += 1;
            var_r31++;
            goto loop_3;
        }
        particleP->dataCnt = 0;
    }
    if ((s16) particleP->dataCnt == 0) {
        var_r29_2 = 0;
loop_14:
        if (var_r29_2 < 5) {
            var_r31_2 = particleP->data;
            var_r28 = 0;
loop_10:
            if (var_r28 < (s16) particleP->maxCnt) {
                if ((u8) var_r31_2->color.a != 0) {
                    var_r28 += 1;
                    var_r31_2++;
                    goto loop_10;
                }
            }
            if (var_r28 != (s16) particleP->maxCnt) {
                var_r31_2->vel.x = -50.0f + (0.3921569f * (f32) frand());
                var_r31_2->vel.y = 0.058823533f * (f32) frand();
                var_r31_2->accel.x = 0.3529412f * (f32) frand();
                var_r31_2->accel.y = 10.0f + (0.098039225f * (f32) frand());
                var_r31_2->accel.z = 8.0f + (f32) (frand() % 10);
                var_r31_2->pos.z = -5.0f + (0.043137256f * (f32) frand());
                temp_ret = frand();
                temp_r3 = temp_ret;
                temp_r4 = temp_ret / 31;
                var_r31_2->pos.y = -5.0f + (f32) (temp_r3 - (((u32) (((u32) (temp_r3 - temp_r4) >> 1U) + temp_r4) >> 4U) * 0x1F));
                var_r31_2->scale = 45.0f + var_r31_2->vel.y;
                var_r31_2->color.a = 0xFF;
                var_r31_2->vel.y = (f32) (15.0 + (0.2 * (f64) var_r31_2->vel.y));
                particleP->dataCnt = (frand() % 10) + 0xA;
            }
            var_r29_2 += 1;
            goto loop_14;
        }
    } else {
        particleP->dataCnt -= 1;
    }
    var_r31_3 = particleP->data;
    var_r29_3 = 0;
loop_23:
    if (var_r29_3 < (s16) particleP->maxCnt) {
        if ((u8) var_r31_3->color.a != 0) {
            var_r31_3->pos.x = (f32) ((f64) var_r31_3->vel.x + ((f64) var_r31_3->accel.z * sin((3.141592653589793 * (f64) var_r31_3->accel.x) / 180.0)));
            var_r31_3->accel.x += var_r31_3->accel.y;
            if (var_r31_3->accel.x >= 360.0f) {
                var_r31_3->accel.x -= 360.0f;
            }
            var_r31_3->pos.y += var_r31_3->vel.y;
            var_r31_3->color.a -= 1;
        }
        var_r29_3 += 1;
        var_r31_3++;
        goto loop_23;
    }
}
















