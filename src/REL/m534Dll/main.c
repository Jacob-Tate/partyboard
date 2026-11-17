// MP5 m534 (Manic Mallets), generated from its m2c draft by tools/mp5/ports/m534Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m534Dll (tools/mp5/decomp.py m534Dll --types tools/mp5/types/m534dll.h)
// Written from the draft: Manic Mallets (2 vs 2). Four players stand in a row, each pushing a button pair (one
// mallet); every hit pounds the stage (a see-saw like rig with a foot "l_han_foot") and scores for the team. The
// team with more hits wins. Plain omObj game (no MgSeq): lbl_1_bss_1C = game state object (M534Game), lbl_1_bss_34[4]
// = players (M534Player), lbl_1_bss_48 = stage (M534Stage), lbl_1_bss_58 = score boards (M534Score).
// objdata: M534Player
// objdata fn_1_36C fn_1_444 fn_1_518 fn_1_648 fn_1_924 fn_1_C1C fn_1_E28 fn_1_10F0 fn_1_1364 fn_1_1A74 fn_1_1DF4 fn_1_1F1C: M534Game
// objdata fn_1_33EC fn_1_3624 fn_1_3AC8 fn_1_3B1C fn_1_3E04 fn_1_3F04 fn_1_3FA0 fn_1_406C fn_1_426C fn_1_430C fn_1_4450 fn_1_4A3C fn_1_3BA8 fn_1_3C1C: M534Stage
// objdata fn_1_6C78 fn_1_6CBC fn_1_6CF4 fn_1_6DEC fn_1_6EE0 fn_1_6FE8: M534Score
// objexpr lbl_1_bss_1C: M534Game
// objexpr lbl_1_bss_48: M534Stage
// objexpr lbl_1_bss_58: M534Score

typedef struct M534Game { // lbl_1_bss_1C data, 0x60
    s32 unk0; // phase (0 intro, 1 camera, 2 start, 3 end, 4 abort, 5 done)
    s32 unk4; // frame counter
    s32 unk8; // paused
    s32 unkC; // game step (1 intro camera .. 5 go, 6 play)
    s32 unk10; // counter
    s32 unk14; // game state (2 playing, 3 finished)
    s32 unk18; // counter
    s32 unk1C; // result step
    s32 unk20; // counter
    s32 unk24[4]; // team of each player
    s32 unk34[4]; // character of each player
    s32 unk44[4]; // winners' characters (-1)
    s32 unk54; // winner: 0 draw, 1 team 0, 2 team 1
    s32 unk58; // players that started the hit (bit per player, 4 bits each)
    s32 unk5C; // players that finished the hit
} M534Game;

typedef struct M534Player { // OMOBJ::data of lbl_1_bss_34[4], 0x60
    s32 unk0; // player
    s32 unk4; // team
    s32 unk8; // slot (0..3, left to right)
    s32 unkC; // character
    s32 unk10; // motion
    s32 unk14; // buttons pressed
    s32 unk18; // buttons held
    s32 unk1C; // com
    f32 unk20; // com reaction time
    f32 unk24; // com timer
    s32 unk28; // state
    s32 unk2C; // counter
    s32 unk30; // counter
    s32 unk34; // hit done
    s32 unk38; // frames since the last hit
    f32 unk3C; // motion speed
    Vec unk40; // pos
    f32 unk4C; // rot y
    f32 unk50; // scale y
    f32 unk54; // scale xz
    s32 unk58;
    s32 unk5C;
} M534Player;

typedef struct M534Snd { // sound slot, 8 bytes
    s32 unk0; // sound
    s32 unk4; // handle (-1 free)
} M534Snd;

typedef struct M534Stage { // lbl_1_bss_48 data, 0x200
    M534Snd unk0[0x20];
    Vec unk100[5]; // clouds
    f32 unk13C[5]; // their speed
    s32 unk150[0x10]; // pound effect playing
    f32 unk190[4]; // base y of the 4 buttons
    f32 unk1A0[4]; // button push offset
    s32 unk1B0; // stage shake on
    s32 unk1B4; // step
    s32 unk1B8; // counter
    s32 unk1BC; // sound handle
    s32 unk1C0; // dust counter
    s32 unk1C4; // pound counter
    f32 unk1C8; // sway amplitude
    f32 unk1CC; // sway phase
    f32 unk1D0; // tilt amplitude
    f32 unk1D4; // tilt phase
    f32 unk1D8; // fall speed
    f32 unk1DC; // camera base y
    f32 unk1E0; // camera shake amplitude
    f32 unk1E4; // camera shake phase
    f32 unk1E8; // lerp rate
    f32 unk1EC; // target y
    f32 unk1F0; // y
    f32 unk1F4; // arm angle (team 0 wins)
    f32 unk1F8; // turn
    f32 unk1FC; // arm angle (team 1 wins)
} M534Stage;

typedef struct M534Board { // one of the two score boards, 0x40
    s32 unk0; // state
    f32 unk4; // blend
    f32 unk8; // radius
    f32 unkC; // angle
    f32 unk10; // pos x
    f32 unk14; // pos y
    f32 unk18; // pos z
    f32 unk1C; // vel x
    f32 unk20; // vel y
    f32 unk24; // vel z
    f32 unk28; // rot x
    f32 unk2C; // rot y
    f32 unk30; // rot z
    s32 unk34; // score
    s16 unk38[3]; // digit anims
    char pad3E[2];
} M534Board;

typedef struct M534Score { // lbl_1_bss_58 data, 0x80
    M534Board unk0[2];
} M534Score;

typedef struct M534Mot { // motion table entry, 0x14
    u16 unk0; // motion index
    char pad2[2];
    f32 unk4; // shift time (s)
    f32 unk8; // start time (s)
    f32 unkC; // end time (s) or -1
    u32 unk10; // attr
} M534Mot;

typedef struct M534Cam { // camera preset, 0x18
    Vec unk0; // center
    Vec unkC; // rot x, rot y, zoom
} M534Cam;

typedef struct M534Cloud { // 0x18
    u32 unk0; // model data number
    Vec unk4; // pos
    f32 unk10; // scale
    f32 unk14; // speed
} M534Cloud;


s16 fn_1_1840(f32 x);
s16 fn_1_189C(Vec *pos);
void fn_1_1930(s32 sfx, Vec *pos);
void (*fn_1_19E8(HUPROCESS *proc))(OMOBJ *);
void (*fn_1_1DF4(HUPROCESS *proc, OMOBJ *obj))(OMOBJ *);
u32 fn_1_1694(void);
u32 fn_1_16AC(void);
u32 fn_1_16C4(void);
u32 fn_1_16DC(void);
void fn_1_16F4(s32 winner);
s32 fn_1_170C(s32 idx);
void fn_1_173C(s32 player);
void fn_1_176C(s32 player);
s32 fn_1_179C(void);
s32 fn_1_17C8(void);
void fn_1_1800(s32 player, s32 team, s32 character);
void fn_1_2130(s32 from, s32 to, f32 t);
void fn_1_2F88(OMOBJ *obj, u32 motion);
s32 fn_1_3118(OMOBJ *obj);
s32 fn_1_318C(OMOBJ *obj, u32 motion);
void fn_1_3BA8(OMOBJ *stage, s32 sfx);
void fn_1_3C1C(OMOBJ *stage, s32 sfx, s32 frames);
void fn_1_4114(s32 slot);
void fn_1_43D4(s32 slot);
void fn_1_449C(s32 team);
s32 fn_1_4624(void);
f32 fn_1_46A8(void);
f32 fn_1_4848(void);
void fn_1_4970(void);
s32 fn_1_49BC(void);
s32 fn_1_49FC(void);
void fn_1_5B64(void);
void fn_1_5CB0(s32 count);
void fn_1_5E20(s32 count, Vec *center);
void fn_1_5F94(void);
void fn_1_6458(Vec *pos);
void fn_1_6938(Vec *pos, Vec *vel);
void fn_1_74B0(s32 team, s32 add);
s32 fn_1_74E8(s32 team);
s16 fn_1_189C(Vec *pos);
void (*fn_1_19E8(HUPROCESS *proc))(omObjData *);
void fn_1_1A74(omObjData *obj);
void (*fn_1_1DF4(HUPROCESS *proc, omObjData *obj))(omObjData *);
void fn_1_1F1C(omObjData *obj);
void fn_1_2130(s32 from, s32 to, f32 t);
void fn_1_6314(void);
void fn_1_6338(void);
void fn_1_633C(void);
void fn_1_6458(Vec *pos);
void fn_1_64EC(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_681C(void);
void fn_1_6938(Vec *pos, Vec *vel);
void fn_1_69E4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void ObjectSetup(void);
void fn_1_36C(omObjData *obj);
void fn_1_444(omObjData *arg0);
void fn_1_518(omObjData *arg0);
void fn_1_648(omObjData *obj);
void fn_1_924(omObjData *obj);
void fn_1_C1C(omObjData *obj);
void fn_1_E28(omObjData *obj);
void fn_1_10F0(omObjData *obj);
void fn_1_1364(omObjData *obj);
u32 fn_1_1694(void);
u32 fn_1_16AC(void);
u32 fn_1_16C4(void);
u32 fn_1_16DC(void);
s32 fn_1_170C(s32 idx);
void fn_1_173C(s32 player);
void fn_1_176C(s32 player);
s32 fn_1_179C(void);
s32 fn_1_17C8(void);
void fn_1_1800(s32 player, s32 team, s32 character);
void fn_1_2290(HUPROCESS *arg0);
void fn_1_2438(void);
void fn_1_245C(omObjData *obj);
void fn_1_2768(omObjData *obj);
void fn_1_2968(omObjData *obj);
void fn_1_2C50(omObjData *arg0);
void fn_1_2CB4(void);
void fn_1_2CB8(omObjData *arg0);
void fn_1_2E4C(omObjData *arg0);
void fn_1_2EB8(omObjData *arg0);
void fn_1_2F88(omObjData *obj, u32 motion);
s32 fn_1_3118(omObjData *obj);
void fn_1_6BDC(HUPROCESS *arg0);
void fn_1_6C74(void);
void fn_1_6C78(omObjData *obj);
void fn_1_6CBC(omObjData *obj);
void fn_1_6CF4(omObjData *arg0);
void fn_1_6DEC(omObjData *arg0);
void fn_1_6EE0(omObjData *arg0);
void fn_1_6FE8(omObjData *arg0);
void fn_1_74B0(s32 team, s32 add);
s32 fn_1_74E8(s32 team);
void fn_1_3360(HUPROCESS *arg0);
void fn_1_33E8(void);
void fn_1_33EC(omObjData *obj);
void fn_1_3624(omObjData *obj);
void fn_1_3674(s16 arg0, s16 arg1);
void fn_1_3AC8(omObjData *arg0);
void fn_1_3B1C(omObjData *arg0);
void fn_1_3CAC(HU3DMODEL *modelP, f32 (*mtx)[3][4]);
void fn_1_3D58(HU3DMODEL *modelP, f32 (*mtx)[3][4]);
void fn_1_3E04(omObjData *arg0);
void fn_1_3F04(omObjData *arg0);
void fn_1_3FA0(omObjData *arg0);
void fn_1_406C(omObjData *arg0);
void fn_1_4114(s32 slot);
void fn_1_426C(omObjData *arg0);
void fn_1_430C(omObjData *arg0);
void fn_1_43D4(s32 slot);
void fn_1_4450(omObjData *arg0);
void fn_1_449C(s32 team);
s32 fn_1_4624(void);
f32 fn_1_4848(void);
s32 fn_1_49BC(void);
s32 fn_1_49FC(void);
void fn_1_4A3C(omObjData *arg0);
void fn_1_5B64(void);
void fn_1_5CB0(s32 count);
void fn_1_5E20(s32 count, Vec *center);
void fn_1_5F94(void);

M534Cam lbl_1_data_50[6] = {
    { { 0.0f, 0.0f, -800.0f }, { -60.0f, 0.0f, 3200.0f } },
    { { 0.0f, 0.0f, -170.0f }, { -25.0f, 0.0f, 1000.0f } },
    { { 0.0f, 0.0f, -520.0f }, { -45.0f, 0.0f, 800.0f } },
    { { 0.0f, 200.0f, 0.0f }, { -2.5f, 0.0f, 810.0f } },
    { { -170.0f, 100.0f, 0.0f }, { -2.5f, 0.0f, 450.0f } },
    { { 170.0f, 100.0f, 0.0f }, { -2.5f, 0.0f, 450.0f } },
};
s32 lbl_1_bss_28;
s32 lbl_1_bss_2C;
s16 lbl_1_bss_50;
s16 lbl_1_bss_52;
static Vec lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };
static Vec lbl_1_data_C = { 0.3f, -0.8f, 0.3f };
static struct { // TODO(mp5): synthesized from the symbol size
    f32 unk0;
    f32 unk4;
    f32 unk8;
} lbl_1_data_18;
static GXColor lbl_1_data_24 = { 0xFF, 0xFF, 0xFF, 0xFF };
static Vec lbl_1_data_28 = { 200.0f, 3000.0f, 100.0f };
static Vec lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };
static Vec lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };
MGTIMER *lbl_1_bss_0;
s16 lbl_1_bss_4;
s16 lbl_1_bss_6;
s32 lbl_1_bss_8;
s16 lbl_1_bss_C;
s32 lbl_1_bss_10;
s32 lbl_1_bss_14;
omObjData *lbl_1_bss_18;
omObjData *lbl_1_bss_1C;
HUPROCESS *lbl_1_bss_20;
u32 lbl_1_data_100[4] = { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 68), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 69) };
M534Mot lbl_1_data_110[4] = {
    { 0, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 1, 0.2f, 0.0f, -1.0f, 0 },
    { 2, 0.2f, 0.0f, -1.0f, 0x40000001 },
    { 3, 0.1f, 0.0f, -1.0f, 0 },
};
Vec lbl_1_data_160[4] = {
    { -257.24f, 0.0f, -40.0f },
    { -109.67f, 0.0f, -40.0f },
    { 109.67f, 0.0f, -40.0f },
    { 257.24f, 0.0f, -40.0f },
};
s16 lbl_1_bss_30;
omObjData *lbl_1_bss_34[4];
u32 lbl_1_data_350[2] = { DATA_MAKE_NUM(DATADIR_MP5_M534, 16), DATA_MAKE_NUM(DATADIR_MP5_M534, 17) };
s8 lbl_1_data_358[3][8] = {
    { 0x70, 0x6F, 0x73, 0x30, 0x31, 0, 0, 0 },
    { 0x70, 0x6F, 0x73, 0x30, 0x32, 0, 0, 0 },
    { 0x70, 0x6F, 0x73, 0x30, 0x33, 0, 0, 0 },
};
Vec lbl_1_data_370[2] = { { -800.0f, 800.0f, -600.0f }, { 800.0f, 800.0f, -600.0f } };
Vec lbl_1_data_388[2] = { { -250.0f, 280.0f, -100.0f }, { 250.0f, 280.0f, -100.0f } };
Vec lbl_1_data_3A0[2] = { { -360.0f, 340.0f, -270.0f }, { 360.0f, 340.0f, -270.0f } };
s8 lbl_1_data_3B8[0xD] = "itemhook_sao";
omObjData *lbl_1_bss_58;
M534Cloud lbl_1_data_190[5] = {
    { DATA_MAKE_NUM(DATADIR_MP5_M534, 1), { -5000.0f, 1900.0f, -4000.0f }, 0.5f, 3.0f },
    { DATA_MAKE_NUM(DATADIR_MP5_M534, 2), { -1000.0f, 1700.0f, -4800.0f }, 0.45f, 2.0f },
    { DATA_MAKE_NUM(DATADIR_MP5_M534, 3), { -4000.0f, 1500.0f, -6000.0f }, 0.4f, 1.5f },
    { DATA_MAKE_NUM(DATADIR_MP5_M534, 4), { -2000.0f, 1300.0f, -6500.0f }, 0.35f, 1.2f },
    { DATA_MAKE_NUM(DATADIR_MP5_M534, 5), { 1000.0f, 1200.0f, -7000.0f }, 0.25f, 0.8f },
};
Vec lbl_1_data_208[0x10] = {
    { -257.24f, 17.81f, 98.81f },
    { -109.67f, 17.81f, 98.81f },
    { 109.67f, 17.81f, 98.81f },
    { 257.24f, 17.81f, 98.81f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
s8 lbl_1_data_2C8[4][8] = {
    { 0x62, 0x75, 0x74, 0x74, 0x5F, 0x6C, 0x6C, 0 },
    { 0x62, 0x75, 0x74, 0x74, 0x5F, 0x6C, 0x72, 0 },
    { 0x62, 0x75, 0x74, 0x74, 0x5F, 0x72, 0x6C, 0 },
    { 0x62, 0x75, 0x74, 0x74, 0x5F, 0x72, 0x72, 0 },
};
Vec lbl_1_data_2E8[2] = { { -200.0f, 20.0f, 110.0f }, { 200.0f, 20.0f, 110.0f } };
s8 lbl_1_data_300[0xB] = "l_han_foot";
s8 lbl_1_data_30B[0xD] = { 0x6C, 0x5F, 0x68, 0x61, 0x6E, 0x5F, 0x62, 0x6F, 0x64, 0x79, 0, 0, 0 };
omObjData *lbl_1_bss_48;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
    s32 unk8;
} lbl_1_rodata_10;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
    s32 unk8;
} lbl_1_rodata_1C;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
} lbl_1_rodata_A0;
static struct { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
} lbl_1_rodata_A8;
f32 lbl_1_rodata_B0[4] = { 6.5f, 5.8f, 4.8f, 4.0f }; /* const */
static struct { // TODO(mp5): synthesized from the symbol size
    u8 unk0;
} lbl_1_rodata_14C;
static struct { // TODO(mp5): synthesized from the symbol size
    u8 unk0;
} lbl_1_rodata_160;


s16 fn_1_189C(Vec *pos) {
    Vec spC;
    Vec *sp8;
    s16 var_r31;

    sp8 = pos;
    Hu3D3Dto2D(pos, 1, &spC);
    var_r31 = (s16) (32.0f + (spC.x * 0.11111111f));
    if (var_r31 < 0x20) {
        var_r31 = 0x20;
    }
    if (var_r31 > 0x60) {
        var_r31 = 0x60;
    }
    return var_r31;
}


void (*fn_1_19E8(HUPROCESS *proc))(omObjData *) {
    memcpy(&Center, lbl_1_data_50, 0xC);
    CRot.x = lbl_1_data_50->unkC.x;
    CRot.y = lbl_1_data_50->unkC.y;
    CRot.z = 0.0f;
    CZoom = lbl_1_data_50->unkC.z;
    return fn_1_1A74;
}

void fn_1_1A74(omObjData *obj) {
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r27;
    s32 var_r30;
    u32 temp_r0;
    u32 var_r28;
    u32 var_r29;
    M534Game *temp_r31;

    temp_r31 = obj->data;
    var_r30 = -1;
    var_r27 = -1;
    var_r29 = 0U;
    var_f29 = 1.0f;
    var_f30 = 0.0f;
    fn_1_444(obj);
    temp_r0 = temp_r31->unkC;
    switch (temp_r0) {
    case 0:
        lbl_1_bss_28 = -1;
        /* fallthrough */
    case 1:
        var_r30 = 1;
        var_r27 = 1;
        var_r29 = 0x3CU;
        var_r28 = 2;
block_15:
        if ((u32) temp_r31->unk10 < var_r29) {
            var_f31 = 0.0f;
        } else {
            temp_f31 = (1.0f / var_f29) * (f32) (temp_r31->unk10 - var_r29);
            if (temp_f31 >= 1.0f) {
                var_f31 = 1.0f;
            } else {
                var_f31 = (f32) sin(1.5707963267948966 * (f64) temp_f31);
            }
        }
        if (var_f31 >= 1.0f) {
            temp_r31->unkC = var_r28;
            temp_r31->unk10 = 0U;
        }
        if (var_r30 >= 0) {
            fn_1_2130(var_r30, var_r27, var_f31);
        }
        if (var_f30 > 0.0f) {
            temp_f31_2 = (f32) (1.5707963267948966 * (f64) (f32) (temp_r31->unk10 & 3));
            Center.x = (f32) ((f64) Center.x + ((f64) var_f30 * sin((f64) temp_f31_2)));
            Center.z = (f32) ((f64) Center.z + ((f64) var_f30 * cos((f64) temp_f31_2)));
        }
        return;
    case 2:
        var_r28 = 3;
        goto block_15;
    case 3:
        var_r30 = 1;
        var_r27 = 2;
        var_r29 = 0x1EU;
        var_f29 = 24.0f;
        var_r28 = 4;
        goto block_15;
    case 4:
        var_r27 = 2;
        var_r30 = 2;
        var_f30 = (f32) (f32) temp_r31->unkC;
        if (var_f30 > 10.0f) {
            var_f30 = 10.0f;
        }
        var_r29 = 0x2AU;
        var_r28 = 5;
        if ((s32) lbl_1_bss_28 == -1) {
            lbl_1_bss_28 = HuAudFXPlay(0x7BB);
        }
        goto block_15;
    case 5:
        var_r27 = 2;
        var_r30 = 2;
        var_f30 = 20.0f;
        var_r29 = 0xCU;
        var_r28 = 6;
        if ((s32) lbl_1_bss_28 != -1) {
            HuAudFXFadeOut(lbl_1_bss_28, 0x1E);
            lbl_1_bss_28 = -1;
        }
        goto block_15;
    case 6:
        var_r30 = 2;
        var_r27 = 3;
        var_r29 = 0xCU;
        var_f29 = 60.0f;
        var_r28 = 7;
        goto block_15;
    case 7:
        fn_1_518(obj);
        /* fallthrough */
    default:
        return;
    }
}

void (*fn_1_1DF4(HUPROCESS *proc, omObjData *obj))(omObjData *) {
    s32 temp_r3;
    s32 var_r30;
    M534Game *temp_r31;

    temp_r31 = obj->data;
    temp_r3 = fn_1_4624();
    switch (temp_r3) {                              /* irregular */
    case 1:
        temp_r31->unk54 = 1U;
        break;
    case -1:
        temp_r31->unk54 = 2U;
        break;
    default:
    case 0:
        temp_r31->unk54 = 0U;
        break;
    }
    var_r30 = 0;
loop_16:
    if (var_r30 < 4) {
        temp_r31->unk44[var_r30] = -1;
        if ((((u32) temp_r31->unk54 == 1U) && ((u32) temp_r31->unk24[var_r30] == 0U)) || (((u32) temp_r31->unk54 == 2U) && ((u32) temp_r31->unk24[var_r30] == 1U))) {
            temp_r31->unk44[var_r30] = temp_r31->unk34[var_r30];
        }
        var_r30 += 1;
        goto loop_16;
    }
    temp_r31->unk1C = 1;
    temp_r31->unk20 = 0;
    lbl_1_bss_2C = -1;
    return fn_1_1F1C;
}

void fn_1_1F1C(omObjData *obj) {
    f64 temp_f1;
    s16 temp_r28;
    s32 temp_r0;
    s32 temp_ret;
    s32 var_r30;
    M534Game *temp_r31;

    temp_r31 = obj->data;
    fn_1_444(obj);
    temp_r0 = temp_r31->unk1C;
    switch (temp_r0) {                              /* irregular */
    case 1:
        temp_ret = fn_1_49BC();
        if (temp_ret != 0) {
            temp_r31->unk20 = 0U;
            if ((u32) temp_r31->unk54 == 0U) {
                lbl_1_bss_2C = (s32) MGSeqDrawCreate();
                temp_r31->unk1C = 4;
                HuAudJinglePlay(0x7B);
                return;
            }
            temp_r31->unk1C = 2;
            return;
        }
        return;
    case 2:
        temp_r31->unk1C = 3;
        temp_r31->unk20 = 0U;
        return;
    case 3:
        temp_f1 = (f64) temp_r31->unk20;
        if (!((f32) temp_f1 < 12.0f)) {
            lbl_1_bss_2C = (s32) MGSeqWinCreate(temp_r31->unk44[0], temp_r31->unk44[1], temp_r31->unk44[2], temp_r31->unk44[3]);
            temp_r31->unk1C = 4;
            temp_r31->unk20 = 0U;
            var_r30 = 0;
loop_18:
            if (var_r30 < 4) {
                if ((s32) temp_r31->unk44[var_r30] >= 0) {
                    temp_r28 = GWPlayer[var_r30].coin_win + 0xA;
                    if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                        GWPlayer[var_r30].coin_win = temp_r28;
                    }
                }
                var_r30 += 1;
                goto loop_18;
            }
            HuAudJinglePlay(0x79);
            return;
        }
        break;
    case 4:
        if (!((f32) (f64) temp_r31->unk20 < 210.0f)) {
            temp_r31->unk1C = 5;
            fn_1_518(obj);
        }
        break;
    }
}

void fn_1_2130(s32 from, s32 to, f32 t) {
    Vec sp8;
    M534Cam *temp_r28;
    M534Cam *temp_r31;
    s32 var_r29;
    s32 var_r30;

    var_r29 = from;
    var_r30 = to;
    if (var_r29 < 0) {
        if (var_r30 >= 0) {
            var_r29 = var_r30;
            goto block_3;
        }
    } else {
block_3:
        if (var_r30 < 0) {
            var_r30 = var_r29;
        }
        temp_r31 = &lbl_1_data_50[var_r29];
        temp_r28 = &lbl_1_data_50[var_r30];
        VECSubtract(&temp_r28->unk0, &temp_r31->unk0, &sp8);
        VECScale(&sp8, &sp8, t);
        VECAdd(&temp_r31->unk0, &sp8, &sp8);
        Center.x = sp8.x;
        Center.y = sp8.y;
        Center.z = sp8.z;
        VECSubtract(&temp_r28->unkC, &temp_r31->unkC, &sp8);
        VECScale(&sp8, &sp8, t);
        VECAdd(&temp_r31->unkC, &sp8, &sp8);
        CRot.x = sp8.x;
        CRot.y = sp8.y;
        CRot.z = 0.0f;
        CZoom = sp8.z;
    }
}

void fn_1_6314(void) {
    fn_1_633C();
    fn_1_681C();
}

void fn_1_6338(void) {

}

void fn_1_633C(void) {
    s16 temp_r3;
    s32 var_r28;
    HU3DPARTICLE *temp_r29;
    HU3DPARTICLEDATA *var_r31;

    temp_r3 = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 12), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x80);
    lbl_1_bss_52 = temp_r3;
    temp_r29 = Hu3DData[temp_r3].hookData;
    Hu3DParticleColSet(temp_r3, 0xDAU, 0xCBU, 0x9EU);
    Hu3DParticleBlendModeSet(temp_r3, 0U);
    Hu3DParticleHookSet(temp_r3, fn_1_64EC);
    Hu3DModelLayerSet(temp_r3, 6);
    Hu3DModelPosSet(temp_r3, 0.0f, 0.0f, 0.0f);
    var_r31 = temp_r29->data;
    var_r28 = 0;
loop_2:
    if (var_r28 < (s16) temp_r29->maxCnt) {
        var_r31->time = -1;
        var_r31->scale = 0.0f;
        var_r28 += 1;
        var_r31++;
        goto loop_2;
    }
}

void fn_1_6458(Vec *pos) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    temp_r30 = Hu3DData[lbl_1_bss_52].hookData;
    var_r31 = temp_r30->data;
    var_r29 = 0;
loop_4:
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        return;
    }
    if ((s16) var_r31->time < 0) {
        var_r31->time = 0;
        var_r31->pos.x = (f32) pos->x;
        var_r31->pos.y = (f32) pos->y;
        var_r31->pos.z = (f32) pos->z;
        return;
    }
    var_r29 += 1;
    var_r31++;
    goto loop_4;
}

void fn_1_64EC(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    s16 temp_r0;
    s32 var_r30;

    var_r31 = particleP->data;
    var_r30 = 0;
loop_12:
    if (var_r30 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31->time += 1;
            var_r31->accel.x = (f32) (0.8 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
            var_r31->accel.y = (f32) (0.1 + (0.2 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
            var_r31->accel.z = (f32) (0.8 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
            var_r31->scale = (f32) (10.0 + (40.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
            var_r31->zRot = 0.0f;
            var_r31->color.a = 0xB4;
            /* fallthrough */
        case 1:
            var_r31->scale += 8.0f;
            var_r31->zRot = (f32) ((f64) var_r31->zRot + 0.008726646192371845);
            var_r31->color.a -= 2;
            if ((var_r31->pos.y < -200.0f) || (var_r31->scale <= 0.0f) || ((u8) var_r31->color.a > 0xF0U)) {
                var_r31->time = -1;
                var_r31->scale = 0.0f;
            } else {
                var_r31->pos.x += var_r31->accel.x;
                var_r31->pos.y += var_r31->accel.y;
                var_r31->pos.z += var_r31->accel.z;
                var_r31->accel.x = (f32) ((f64) var_r31->accel.x * 0.9);
                var_r31->accel.y = (f32) ((f64) var_r31->accel.y - 0.05);
                var_r31->accel.z = (f32) ((f64) var_r31->accel.z * 0.9);
            }
            break;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_12;
    }
}

void fn_1_681C(void) {
    s16 temp_r3;
    s32 var_r28;
    HU3DPARTICLE *temp_r29;
    HU3DPARTICLEDATA *var_r31;

    temp_r3 = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 13), MEMORY_DEFAULT_NUM, HEAP_DATA)), 0x200);
    lbl_1_bss_50 = temp_r3;
    temp_r29 = Hu3DData[temp_r3].hookData;
    Hu3DParticleColSet(temp_r3, 0xDAU, 0xCBU, 0x9EU);
    Hu3DParticleBlendModeSet(temp_r3, 0U);
    Hu3DParticleHookSet(temp_r3, fn_1_69E4);
    Hu3DModelLayerSet(temp_r3, 0);
    Hu3DModelPosSet(temp_r3, 0.0f, 0.0f, 0.0f);
    var_r31 = temp_r29->data;
    var_r28 = 0;
loop_2:
    if (var_r28 < (s16) temp_r29->maxCnt) {
        var_r31->time = -1;
        var_r31->scale = 0.0f;
        var_r28 += 1;
        var_r31++;
        goto loop_2;
    }
}

void fn_1_6938(Vec *pos, Vec *vel) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    temp_r30 = Hu3DData[lbl_1_bss_50].hookData;
    var_r31 = temp_r30->data;
    var_r29 = 0;
loop_4:
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        return;
    }
    if ((s16) var_r31->time < 0) {
        var_r31->time = 0;
        var_r31->pos.x = (f32) pos->x;
        var_r31->pos.y = (f32) pos->y;
        var_r31->pos.z = (f32) pos->z;
        var_r31->accel.x = (f32) vel->x;
        var_r31->accel.y = (f32) vel->y;
        var_r31->accel.z = (f32) vel->z;
        return;
    }
    var_r29 += 1;
    var_r31++;
    goto loop_4;
}

void fn_1_69E4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    s16 temp_r0;
    s32 var_r30;

    var_r31 = particleP->data;
    var_r30 = 0;
loop_12:
    if (var_r30 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31->time += 1;
            var_r31->scale = (f32) (5.0 + (5.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
            var_r31->zRot = 0.0f;
            var_r31->color.a = 0x32;
            /* fallthrough */
        case 1:
            var_r31->scale = (f32) ((f64) var_r31->scale + 0.1);
            if ((var_r31->pos.y < -100.0f) || (var_r31->scale <= 0.0f) || ((u8) var_r31->color.a > 0xF0U)) {
                var_r31->time = -1;
                var_r31->scale = 0.0f;
            } else {
                var_r31->pos.x += var_r31->accel.x;
                var_r31->pos.y += var_r31->accel.y;
                var_r31->pos.z += var_r31->accel.z;
                var_r31->accel.x = (f32) ((f64) var_r31->accel.x * 0.88);
                var_r31->accel.y = (f32) ((f64) var_r31->accel.y - 0.15);
                var_r31->accel.z = (f32) ((f64) var_r31->accel.z * 0.88);
            }
            break;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_12;
    }
}



void ObjectSetup(void) {
    Mtx sp38;
    Vec sp14;
    Vec sp8;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    HUPROCESS *temp_r3;

    sp2C = lbl_1_rodata_10.unk0;
    sp30 = lbl_1_rodata_10.unk4;
    sp34 = lbl_1_rodata_10.unk8;
    sp20 = lbl_1_rodata_1C.unk0;
    sp24 = lbl_1_rodata_1C.unk4;
    sp28 = lbl_1_rodata_1C.unk8;
    lbl_1_bss_8 = -1;
    lbl_1_bss_0 = NULL;
    lbl_1_bss_C = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_C);
    Hu3DGLightStaticSet(lbl_1_bss_C, 1);
    sp14.z = 0.0f;
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp8.z = 0.0f;
    sp8.x = 0.0f;
    sp8.y = lbl_1_data_18.unk8;
    mtxRot(sp38, lbl_1_data_18.unk0, lbl_1_data_18.unk4, 0.0f);
    MTXMultVec(sp38, &sp8, &sp8);
    Hu3DGLightPosAimSetV(lbl_1_bss_C, &sp8, &sp14);
    Hu3DShadowCreate(80.0f, 20.0f, 10000.0f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    Hu3DShadowColSet(0U, 0U, 0x40U);
    temp_r3 = omInitObjMan(0x32, 0x2000);
    lbl_1_bss_20 = temp_r3;
    omGameSysInit(temp_r3);
    lbl_1_bss_14 = 0;
    lbl_1_bss_10 = 0;
    lbl_1_bss_4 = -1;
    lbl_1_bss_6 = -1;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 10.0f, 20000.0f, 1.2f);
    lbl_1_bss_18 = omAddObjEx(temp_r3, 0x7FDA, 0U, 0U, -1, omOutView);
    lbl_1_bss_1C = omAddObjEx(temp_r3, 0xA, 0U, 0U, -1, fn_1_36C);
    fn_1_6BDC(temp_r3);
    fn_1_6314();
    fn_1_3360(temp_r3);
    fn_1_2290(temp_r3);
}

void fn_1_36C(omObjData *obj) {
    M534Game *temp_r31;

    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M534Game), MEMORY_DEFAULT_NUM);
    temp_r31 = obj->data;
    memset(temp_r31, 0, 0x60);
    temp_r31->unk0 = 0;
    temp_r31->unk4 = 0;
    temp_r31->unkC = 0;
    temp_r31->unk10 = 0;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r31->unk1C = 0;
    temp_r31->unk20 = 0;
    temp_r31->unk8 = 0;
    temp_r31->unk54 = 3;
    temp_r31->unk44[3] = -1;
    temp_r31->unk44[2] = -1;
    temp_r31->unk44[1] = -1;
    temp_r31->unk44[0] = -1;
    temp_r31->unk58 = 0;
    temp_r31->unk5C = 0;
    obj->func = fn_1_648;
}

void fn_1_444(omObjData *arg0) {
    M534Game *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk4 = (s32) (temp_r31->unk4 + 1);
    temp_r31->unk10 = (s32) (temp_r31->unk10 + 1);
    temp_r31->unk18 = (s32) (temp_r31->unk18 + 1);
    temp_r31->unk20 = (s32) (temp_r31->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r31->unk0 != 5U)) {
        temp_r31->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        fn_1_518(arg0);
    }
}

void fn_1_518(omObjData *arg0) {
    s32 temp_r0;
    M534Game *temp_r31;

    temp_r31 = arg0->data;
    if ((s32) temp_r31->unk8 == 0) {
        temp_r0 = temp_r31->unk0;
        if (temp_r0 != 2) {
            if (temp_r0 < 2) {
                if (temp_r0 != 0) {
                    if (temp_r0 < 0) {
                        goto block_13;
                    }
                    temp_r31->unk0 = 2;
                    temp_r31->unk18 = 0;
                    arg0->func = fn_1_E28;
                } else {
                    WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                    temp_r31->unk0 = 1;
                    temp_r31->unk10 = 0;
                    arg0->func = fn_1_19E8(lbl_1_bss_20);
                }
            } else if ((temp_r0 != 5) && (temp_r0 < 5)) {
                temp_r31->unk8 = 1;
                temp_r31->unk0 = 5;
                arg0->func = fn_1_924;
            } else {
block_13:
                temp_r31->unk0 = 5;
                arg0->func = fn_1_C1C;
            }
        } else {
            temp_r31->unk0 = 3;
            temp_r31->unk20 = 0;
            arg0->func = fn_1_1DF4(lbl_1_bss_20, arg0);
        }
        temp_r31->unk4 = 0;
    }
}

void fn_1_648(omObjData *obj) {
    u32 temp_r0;
    u32 temp_r0_2;
    M534Game *temp_r28;
    M534Game *temp_r29;
    M534Game *temp_r30;

    temp_r28 = obj->data;
    temp_r28->unk4 = (s32) (temp_r28->unk4 + 1);
    temp_r28->unk10 = (s32) (temp_r28->unk10 + 1);
    temp_r28->unk18 = (s32) (temp_r28->unk18 + 1);
    temp_r28->unk20 = (s32) (temp_r28->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r28->unk0 != 5U)) {
        temp_r28->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r29 = obj->data;
        if ((s32) temp_r29->unk8 == 0) {
            temp_r0 = temp_r29->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_17;
                        }
                        temp_r29->unk0 = 2U;
                        temp_r29->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r29->unk0 = 1U;
                        temp_r29->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r29->unk8 = 1;
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_17:
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r29->unk0 = 3U;
                temp_r29->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r29->unk4 = 0;
        }
    }
    temp_r30 = obj->data;
    if ((s32) temp_r30->unk8 == 0) {
        temp_r0_2 = temp_r30->unk0;
        if ((s32) temp_r0_2 != 2) {
            if ((s32) temp_r0_2 < 2) {
                if ((s32) temp_r0_2 != 0) {
                    if ((s32) temp_r0_2 < 0) {
                        goto block_32;
                    }
                    temp_r30->unk0 = 2U;
                    temp_r30->unk18 = 0;
                    obj->func = fn_1_E28;
                } else {
                    WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                    temp_r30->unk0 = 1U;
                    temp_r30->unk10 = 0;
                    obj->func = fn_1_19E8(lbl_1_bss_20);
                }
            } else if (((s32) temp_r0_2 != 5) && ((s32) temp_r0_2 < 5)) {
                temp_r30->unk8 = 1;
                temp_r30->unk0 = 5U;
                obj->func = fn_1_924;
            } else {
block_32:
                temp_r30->unk0 = 5U;
                obj->func = fn_1_C1C;
            }
        } else {
            temp_r30->unk0 = 3U;
            temp_r30->unk20 = 0;
            obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
        }
        temp_r30->unk4 = 0;
    }
}

void fn_1_924(omObjData *obj) {
    u32 temp_r0;
    u32 temp_r0_2;
    M534Game *temp_r27;
    M534Game *temp_r28;
    M534Game *temp_r29;
    M534Game *temp_r30;

    temp_r27 = obj->data;
    temp_r28 = obj->data;
    temp_r28->unk4 = (s32) (temp_r28->unk4 + 1);
    temp_r28->unk10 = (s32) (temp_r28->unk10 + 1);
    temp_r28->unk18 = (s32) (temp_r28->unk18 + 1);
    temp_r28->unk20 = (s32) (temp_r28->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r28->unk0 != 5U)) {
        temp_r28->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r29 = obj->data;
        if ((s32) temp_r29->unk8 == 0) {
            temp_r0 = temp_r29->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_17;
                        }
                        temp_r29->unk0 = 2U;
                        temp_r29->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r29->unk0 = 1U;
                        temp_r29->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r29->unk8 = 1;
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_17:
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r29->unk0 = 3U;
                temp_r29->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r29->unk4 = 0;
        }
    }
    if (WipeCheckEnd() == 0) {
        Mp5WipeWhite(2, 0x3C);
        temp_r27->unk8 = 0;
        temp_r30 = obj->data;
        if ((s32) temp_r30->unk8 == 0) {
            temp_r0_2 = temp_r30->unk0;
            if ((s32) temp_r0_2 != 2) {
                if ((s32) temp_r0_2 < 2) {
                    if ((s32) temp_r0_2 != 0) {
                        if ((s32) temp_r0_2 < 0) {
                            goto block_33;
                        }
                        temp_r30->unk0 = 2U;
                        temp_r30->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r30->unk0 = 1U;
                        temp_r30->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0_2 != 5) && ((s32) temp_r0_2 < 5)) {
                    temp_r30->unk8 = 1;
                    temp_r30->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_33:
                    temp_r30->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r30->unk0 = 3U;
                temp_r30->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r30->unk4 = 0;
        }
    }
}

void fn_1_C1C(omObjData *obj) {
    u32 temp_r0;
    M534Game *temp_r29;
    M534Game *temp_r31;

    temp_r29 = obj->data;
    temp_r29->unk4 = (s32) (temp_r29->unk4 + 1);
    temp_r29->unk10 = (s32) (temp_r29->unk10 + 1);
    temp_r29->unk18 = (s32) (temp_r29->unk18 + 1);
    temp_r29->unk20 = (s32) (temp_r29->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r29->unk0 != 5U)) {
        temp_r29->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r31 = obj->data;
        if ((s32) temp_r31->unk8 == 0) {
            temp_r0 = temp_r31->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_17;
                        }
                        temp_r31->unk0 = 2U;
                        temp_r31->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r31->unk0 = 1U;
                        temp_r31->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r31->unk8 = 1;
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_17:
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r31->unk0 = 3U;
                temp_r31->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r31->unk4 = 0;
        }
    }
    if (WipeCheckEnd() == 0) {
        fn_1_33E8();
        fn_1_2438();
        fn_1_6338();
        fn_1_6C74();
        GameMesClose();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

void fn_1_E28(omObjData *obj) {
    s32 temp_r0_2;
    u32 temp_r0;
    M534Game *temp_r28;
    M534Game *temp_r29;
    M534Game *temp_r31;

    temp_r29 = obj->data;
    temp_r28 = obj->data;
    temp_r28->unk4 = (s32) (temp_r28->unk4 + 1);
    temp_r28->unk10 = (s32) (temp_r28->unk10 + 1);
    temp_r28->unk18 = (s32) (temp_r28->unk18 + 1);
    temp_r28->unk20 = (s32) (temp_r28->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r28->unk0 != 5U)) {
        temp_r28->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r31 = obj->data;
        if ((s32) temp_r31->unk8 == 0) {
            temp_r0 = temp_r31->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_17;
                        }
                        temp_r31->unk0 = 2U;
                        temp_r31->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r31->unk0 = 1U;
                        temp_r31->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r31->unk8 = 1;
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_17:
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r31->unk0 = 3U;
                temp_r31->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r31->unk4 = 0;
        }
    }
    temp_r0_2 = temp_r29->unk14;
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        lbl_1_bss_6 = MGSeqStartCreate();
        lbl_1_bss_8 = HuAudBGMPlay(0x37);
        temp_r29->unk14 = 1;
        temp_r29->unk18 = 0;
        return;
    case 1:
        if ((GameMesStatGet(lbl_1_bss_6) == 0) && ((s32) temp_r29->unk8 == 0)) {
            lbl_1_bss_0 = MgTimerCreate(0);
            MgTimerParamSet(lbl_1_bss_0, 0x258, 0, 0);
            MgTimerModeOnSet(lbl_1_bss_0, 1);
            temp_r29->unk14 = 2;
            temp_r29->unk18 = 0;
            obj->func = fn_1_10F0;
        }
        return;
    }
}

void fn_1_10F0(omObjData *obj) {
    s32 temp_ret;
    s32 var_r27;
    u32 temp_r0;
    M534Game *temp_r28;
    M534Game *temp_r29;
    M534Game *temp_r31;

    temp_r28 = obj->data;
    var_r27 = 0;
    temp_r29 = obj->data;
    temp_r29->unk4 = (s32) (temp_r29->unk4 + 1);
    temp_r29->unk10 = (s32) (temp_r29->unk10 + 1);
    temp_r29->unk18 = (s32) (temp_r29->unk18 + 1);
    temp_r29->unk20 = (s32) (temp_r29->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r29->unk0 != 5U)) {
        temp_r29->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r31 = obj->data;
        if ((s32) temp_r31->unk8 == 0) {
            temp_r0 = temp_r31->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_17;
                        }
                        temp_r31->unk0 = 2U;
                        temp_r31->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r31->unk0 = 1U;
                        temp_r31->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r31->unk8 = 1;
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_17:
                    temp_r31->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r31->unk0 = 3U;
                temp_r31->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r31->unk4 = 0;
        }
    }
    temp_ret = MgTimerDoneCheck(lbl_1_bss_0);
    if (temp_ret != 0) {
        var_r27 = 1;
    }
    if (var_r27 != 0) {
        lbl_1_bss_4 = MGSeqFinishCreate();
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x64);
            lbl_1_bss_8 = -1;
        }
        temp_r28->unk14 = 3;
        temp_r28->unk18 = 0;
        if ((s32) temp_r28->unk8 == 0) {
            obj->func = fn_1_1364;
        }
    }
}

void fn_1_1364(omObjData *obj) {
    u32 temp_r0;
    u32 temp_r0_2;
    M534Game *temp_r27;
    M534Game *temp_r28;
    M534Game *temp_r29;
    M534Game *temp_r30;

    temp_r27 = obj->data;
    if (lbl_1_bss_0 != NULL) {
        MgTimerKill(lbl_1_bss_0);
        lbl_1_bss_0 = NULL;
    }
    temp_r28 = obj->data;
    temp_r28->unk4 = (s32) (temp_r28->unk4 + 1);
    temp_r28->unk10 = (s32) (temp_r28->unk10 + 1);
    temp_r28->unk18 = (s32) (temp_r28->unk18 + 1);
    temp_r28->unk20 = (s32) (temp_r28->unk20 + 1);
    if (((s16) omSysExitReq != 0) && ((u32) temp_r28->unk0 != 5U)) {
        temp_r28->unk0 = 4U;
        if ((s32) lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(0x3E8);
        temp_r29 = obj->data;
        if ((s32) temp_r29->unk8 == 0) {
            temp_r0 = temp_r29->unk0;
            if ((s32) temp_r0 != 2) {
                if ((s32) temp_r0 < 2) {
                    if ((s32) temp_r0 != 0) {
                        if ((s32) temp_r0 < 0) {
                            goto block_19;
                        }
                        temp_r29->unk0 = 2U;
                        temp_r29->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r29->unk0 = 1U;
                        temp_r29->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0 != 5) && ((s32) temp_r0 < 5)) {
                    temp_r29->unk8 = 1;
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_19:
                    temp_r29->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r29->unk0 = 3U;
                temp_r29->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r29->unk4 = 0;
        }
    }
    if ((fn_1_17C8() != 0) && ((u32) temp_r27->unk58 == 0x1111U)) {
        temp_r27->unk14 = 4;
        temp_r27->unk18 = 0;
        temp_r30 = obj->data;
        if ((s32) temp_r30->unk8 == 0) {
            temp_r0_2 = temp_r30->unk0;
            if ((s32) temp_r0_2 != 2) {
                if ((s32) temp_r0_2 < 2) {
                    if ((s32) temp_r0_2 != 0) {
                        if ((s32) temp_r0_2 < 0) {
                            goto block_36;
                        }
                        temp_r30->unk0 = 2U;
                        temp_r30->unk18 = 0;
                        obj->func = fn_1_E28;
                    } else {
                        WipeCreate(1, WIPE_TYPE_NORMAL, 0x3C);
                        temp_r30->unk0 = 1U;
                        temp_r30->unk10 = 0;
                        obj->func = fn_1_19E8(lbl_1_bss_20);
                    }
                } else if (((s32) temp_r0_2 != 5) && ((s32) temp_r0_2 < 5)) {
                    temp_r30->unk8 = 1;
                    temp_r30->unk0 = 5U;
                    obj->func = fn_1_924;
                } else {
block_36:
                    temp_r30->unk0 = 5U;
                    obj->func = fn_1_C1C;
                }
            } else {
                temp_r30->unk0 = 3U;
                temp_r30->unk20 = 0;
                obj->func = fn_1_1DF4(lbl_1_bss_20, obj);
            }
            temp_r30->unk4 = 0;
        }
    }
}

u32 fn_1_1694(void) {
    return ((M534Game *)lbl_1_bss_1C->data)->unk0;
}

u32 fn_1_16AC(void) {
    return ((M534Game *)lbl_1_bss_1C->data)->unkC;
}

u32 fn_1_16C4(void) {
    return ((M534Game *)lbl_1_bss_1C->data)->unk14;
}

u32 fn_1_16DC(void) {
    return ((M534Game *)lbl_1_bss_1C->data)->unk1C;
}


s32 fn_1_170C(s32 idx) {
    return ((M534Game *)lbl_1_bss_1C->data)->unk44[idx];
}

void fn_1_173C(s32 player) {
    M534Game *temp_r6;

    temp_r6 = lbl_1_bss_1C->data;
    temp_r6->unk58 = (s32) (temp_r6->unk58 | (1 << ((player & 3) * 4)));
}

void fn_1_176C(s32 player) {
    M534Game *temp_r6;

    temp_r6 = lbl_1_bss_1C->data;
    temp_r6->unk5C = (s32) (temp_r6->unk5C | (1 << ((player & 3) * 4)));
}

s32 fn_1_179C(void) {
    return (s16) lbl_1_bss_4 != -1;
}

s32 fn_1_17C8(void) {
    return GameMesStatGet(lbl_1_bss_4) == 0;
}

void fn_1_1800(s32 player, s32 team, s32 character) {
    s32 temp_r3;
    M534Game *temp_r31;

    temp_r31 = lbl_1_bss_1C->data;
    temp_r3 = player & 3;
    temp_r31->unk24[temp_r3] = team;
    temp_r31->unk34[temp_r3] = character;
}

void fn_1_2290(HUPROCESS *arg0) {
    s32 sp18[4];
    s32 sp10[2];
    u32 sp8[2];
    omObjData *temp_r3;
    s16 temp_r29;
    s32 temp_r29_2;
    s32 var_r28;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    sp10[0] = lbl_1_rodata_A0.unk0;
    sp10[1] = lbl_1_rodata_A0.unk4;
    sp8[0] = lbl_1_rodata_A8.unk0;
    sp8[1] = 2;
    var_r28 = 0;
    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        temp_r29 = GWPlayerCfg[var_r31].group;
        sp18[var_r31] = (s32) temp_r29;
        if (temp_r29 >= 2) {
            var_r28 = 1;
        } else {
            sp10[temp_r29] += 1;
        }
        var_r31 += 1;
        goto loop_5;
    }
    if ((sp10[0] != 2) || (sp10[1] != 2)) {
        var_r28 = 1;
    }
    if (var_r28 != 0) {
        var_r31_2 = 0;
loop_12:
        if (var_r31_2 < 4) {
            sp18[var_r31_2] = var_r31_2 >> 1;
            var_r31_2 += 1;
            goto loop_12;
        }
    }
    omMakeGroupEx(arg0, 0U, 4U);
    lbl_1_bss_30 = -1;
    var_r31_3 = 0;
loop_15:
    if (var_r31_3 < 4) {
        temp_r3 = omAddObjEx(arg0, 0x1E, 1U, 4U, 0, fn_1_245C);
        lbl_1_bss_34[var_r31_3] = temp_r3;
        temp_r3->work[0] = (u32) var_r31_3;
        temp_r29_2 = sp18[var_r31_3];
        temp_r3->work[1] = (u32) temp_r29_2;
        temp_r3->work[2] = sp8[temp_r29_2];
        sp8[temp_r29_2] += 1;
        var_r31_3 += 1;
        goto loop_15;
    }
}

void fn_1_2438(void) {
    CharModelKill(-1);
}

void fn_1_245C(omObjData *obj) {
    f32 sp8[4];
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    s16 temp_r27;
    s16 temp_r3;
    s16 var_r25;
    s32 var_r29;
    u32 temp_r26;
    u32 temp_r28;
    M534Player *temp_r31;

    sp8[0] = lbl_1_rodata_B0[0];
    sp8[1] = lbl_1_rodata_B0[1];
    sp8[2] = lbl_1_rodata_B0[2];
    sp8[3] = lbl_1_rodata_B0[3];
    obj->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M534Player), MEMORY_DEFAULT_NUM);
    temp_r31 = obj->data;
    memset(temp_r31, 0, 0x60);
    obj->stat |= 0x100;
    temp_r28 = obj->work[0];
    temp_r31->unk0 = temp_r28;
    temp_r31->unk4 = (u32) obj->work[1];
    temp_r26 = obj->work[2];
    temp_r31->unk8 = temp_r26;
    temp_r27 = GWPlayerCfg[temp_r28].character;
    temp_r31->unkC = (s32) temp_r27;
    fn_1_1800((s32) temp_r28, (s32) temp_r31->unk4, temp_r31->unkC);
    temp_r31->unk20 = (f32) sp8[GWPlayerCfg[temp_r28].diff & 3];
    temp_r31->unk1C = (s32) GWPlayerCfg[temp_r28].iscom;
    temp_r31->unk24 = (f32) (2.0f + (f32) (frand() & 3));
    *obj->model = CharModelCreate(temp_r27, 2);
    Hu3DModelLayerSet(*obj->model, 4);
    Hu3DModelShadowSet(*obj->model);
    var_r29 = 0;
loop_2:
    if (var_r29 < 4) {
        obj->motion[var_r29] = Mp5CharMotionCreateData(temp_r27, lbl_1_data_100[var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionDataClose(temp_r27);
    temp_r31->unk10 = -1;
    fn_1_2F88(obj, 2U);
    if ((s16) lbl_1_bss_30 < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 9), MEMORY_DEFAULT_NUM, HEAP_DATA));
        lbl_1_bss_30 = temp_r3;
        var_r25 = temp_r3;
    } else {
        var_r25 = Hu3DModelLink(lbl_1_bss_30);
    }
    Hu3DModelHookSet(*obj->model, CharModelItemHookGet(temp_r27, 2, 0), var_r25);
    temp_f0 = lbl_1_data_160[temp_r26].x;
    temp_r31->unk40.x = temp_f0;
    obj->trans.x = temp_f0;
    temp_f0_2 = lbl_1_data_160[temp_r26].y;
    temp_r31->unk40.y = temp_f0_2;
    obj->trans.y = temp_f0_2;
    temp_f0_3 = lbl_1_data_160[temp_r26].z;
    temp_r31->unk40.z = temp_f0_3;
    obj->trans.z = temp_f0_3;
    temp_r31->unk4C = 0.0f;
    temp_r31->unk54 = 1.0f;
    temp_r31->unk50 = 1.0f;
    temp_r31->unk58 = 0;
    temp_r31->unk5C = 0;
    temp_r31->unk34 = 0;
    temp_r31->unk3C = 1.0f;
    temp_r31->unk28 = 0;
    obj->func = fn_1_2768;
}

void fn_1_2768(omObjData *obj) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r29;
    M534Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (fn_1_16AC() == 2) {
            temp_r31->unk14 = 0x100;
            temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
        case 1:
            if (fn_1_16C4() == 2) {
                temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
                temp_r31->unk38 = 0;
            case 2:
                if (fn_1_16C4() != 2) {
                    temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
                    temp_r31->unk2C = 0x14;
                } else if ((s32) temp_r31->unk1C != 0) {
                    fn_1_2EB8(obj);
                } else {
                    temp_r29 = temp_r31->unk0;
                    temp_r31->unk18 = (s32) HuPadBtn[GWPlayerCfg[temp_r29].pad_idx];
                    temp_r31->unk14 = (s32) HuPadBtnDown[GWPlayerCfg[temp_r29].pad_idx];
                }
            }
        }
        break;
    case 3:
        temp_r0_2 = temp_r31->unk2C - 1;
        temp_r31->unk2C = temp_r0_2;
        if (temp_r0_2 == 0) {
            temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
            CharModelHookDustCreate((s16) temp_r31->unkC, CharModelItemHookGet((s16) temp_r31->unkC, 2, 0));
            fn_1_2F88(obj, 0U);
        case 4:
            if ((fn_1_16C4() == 3) && (fn_1_17C8() != 0)) {
                temp_r31->unk28 = 0;
                obj->func = fn_1_2968;
            }
        }
        break;
    }
    fn_1_2CB8(obj);
    fn_1_2CB4();
    fn_1_2C50(obj);
    fn_1_2E4C(obj);
}

void fn_1_2968(omObjData *obj) {
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f31;
    s32 temp_r0;
    s32 temp_r0_2;
    M534Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->unk14 = 0;
    temp_r31->unk18 = 0;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 0:
        fn_1_173C(temp_r31->unk0);
        temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
        break;
    case 1:
        if (fn_1_16DC() != 0) {
            if (fn_1_170C(temp_r31->unk0) < 0) {
                temp_r31->unk28 = 4;
                temp_r31->unk2C = 8;
            } else {
                temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
            }
        }
        break;
    case 2:
        if (fn_1_16DC() == 4) {
            fn_1_2F88(obj, 1U);
            temp_r31->unk28 = (s32) (temp_r31->unk28 + 1);
        }
        break;
    case 3:
        if (fn_1_3118(obj) != 0) {
            fn_1_176C(temp_r31->unk0);
        }
        break;
    case 4:
        temp_f1 = fn_1_4848();
        if (temp_f1 >= 0.75f) {
            var_f31 = (f32) ((1.0 - (f64) temp_f1) * (1.0 / (1.0 - 0.75f)));
            if ((s32) temp_r31->unk5C == 0) {
                CharFXPlayPan((s16) temp_r31->unkC, 0x202, fn_1_189C(&temp_r31->unk40));
                temp_r31->unk5C = 1;
            }
            if ((var_f31 < 0.1f) && ((s32) temp_r31->unk58 == 0)) {
                var_f31 = 0.1f;
                temp_r31->unk58 = 1;
                omVibrate((s16) temp_r31->unk0, 0x28, 0xC, 0);
                Hu3DModelAttrSet(*obj->model, 0x40000002U);
                fn_1_176C(temp_r31->unk0);
            }
            if (var_f31 < temp_r31->unk50) {
                temp_r31->unk50 = var_f31;
            }
            if (temp_r31->unk50 <= 0.1f) {
                temp_r0_2 = temp_r31->unk2C - 1;
                temp_r31->unk2C = temp_r0_2;
                if (temp_r0_2 < 0) {
                    temp_r31->unk54 = (f32) ((f64) temp_r31->unk54 * 0.8);
                }
            }
            if (temp_r31->unk54 < 0.1f) {
                Hu3DModelAttrSet(*obj->model, 1U);
            } else {
                temp_f30 = temp_r31->unk54;
                Hu3DModelScaleSet(*obj->model, temp_f30, temp_r31->unk50, temp_f30);
            }
        }
        break;
    }
    fn_1_2CB8(obj);
    fn_1_2CB4();
    fn_1_2C50(obj);
    fn_1_2E4C(obj);
}

void fn_1_2C50(omObjData *arg0) {
    M534Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk30 = (s32) (temp_r31->unk30 + 1);
    temp_r31->unk38 = (s32) (temp_r31->unk38 + 1);
    CharModelVoicePanSet((s16) temp_r31->unkC, fn_1_189C(&temp_r31->unk40));
}

void fn_1_2CB4(void) {

}

void fn_1_2CB8(omObjData *arg0) {
    f32 var_f31;
    f32 var_f31_2;
    M534Player *temp_r31;

    temp_r31 = arg0->data;
    if ((u32) (temp_r31->unk14 & 0x100) != 0) {
        fn_1_449C(temp_r31->unk4);
        var_f31 = 0.016666668f * (f32) temp_r31->unk38;
        if (var_f31 == 0.0f) {
            var_f31 = 1.0f;
        }
        temp_r31->unk38 = 0;
        var_f31_2 = (f32) (0.1666666753590107 / (f64) var_f31);
        if (var_f31_2 < 1.0f) {
            var_f31_2 = 1.0f;
        }
        temp_r31->unk3C = var_f31_2;
        temp_r31->unk10 = -1;
        fn_1_2F88(arg0, 3U);
        temp_r31->unk34 = 0;
    }
    if ((s32) temp_r31->unk10 == 3) {
        if (fn_1_3118(arg0) != 0) {
            fn_1_2F88(arg0, 2U);
            return;
        }
        CharMotionSpeedSet((s16) temp_r31->unkC, temp_r31->unk3C);
        if (((s32) temp_r31->unk34 == 0) && (CharMotionTimeGet((s16) temp_r31->unkC) >= 4.0f)) {
            temp_r31->unk34 = 1;
            fn_1_43D4(temp_r31->unk8);
            fn_1_4114(temp_r31->unk8);
        }
    }
}

void fn_1_2E4C(omObjData *arg0) {
    M534Player *temp_r30;

    temp_r30 = arg0->data;
    Hu3DModelPosSetV(*arg0->model, &temp_r30->unk40);
    Hu3DModelRotSet(*arg0->model, 0.0f, temp_r30->unk4C, 0.0f);
}

void fn_1_2EB8(omObjData *arg0) {
    f32 temp_f1;
    M534Player *temp_r31;

    temp_r31 = arg0->data;
    temp_f1 = (f32) ((f64) temp_r31->unk24 - 1.0);
    temp_r31->unk24 = temp_f1;
    if (temp_f1 <= 0.0f) {
        temp_r31->unk14 = (s32) (temp_r31->unk14 | 0x100);
        temp_r31->unk24 = (f32) ((f64) temp_r31->unk20 + (2.5 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))));
    }
}

void fn_1_2F88(omObjData *obj, u32 motion) {
    f32 var_f31;
    M534Player *temp_r30;

    temp_r30 = obj->data;
    if (((u32) temp_r30->unk10 != motion) && (motion < 4U)) {
        if ((s32) temp_r30->unk10 < 0) {
            var_f31 = 0.0f;
        } else {
            var_f31 = 60.0f * lbl_1_data_110[motion].unk4;
        }
        temp_r30->unk10 = motion;
        CharMotionShiftSet((s16) temp_r30->unkC, obj->motion[lbl_1_data_110[motion].unk0], 60.0f * lbl_1_data_110[motion].unk8, var_f31, lbl_1_data_110[motion].unk10);
        if (lbl_1_data_110[motion].unkC >= 0.0f) {
            Hu3DMotionShiftStartEndSet(*obj->model, 60.0f * lbl_1_data_110[motion].unk8, 60.0f * lbl_1_data_110[motion].unkC);
        }
    }
}

s32 fn_1_3118(omObjData *obj) {
    s32 var_r30;
    M534Player *temp_r31;

    temp_r31 = obj->data;
    var_r30 = 0;
    if ((CharMotionEndCheck((s16) temp_r31->unkC) != 0) && (CharMotionShiftIDGet((s16) temp_r31->unkC) < 0)) {
        var_r30 = 1;
    }
    return var_r30;
}


void fn_1_6BDC(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    omObjData *temp_r3;
    void *temp_r3_2;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x32, 4U, 0U, -1, fn_1_6C78);
    lbl_1_bss_58 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x80, MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 0x80);
    temp_r3->stat |= 0x100;
}

void fn_1_6C74(void) {

}

void fn_1_6C78(omObjData *obj) {
    fn_1_6CF4(obj);
    fn_1_6EE0(obj);
    obj->func = fn_1_6CBC;
}

void fn_1_6CBC(omObjData *obj) {
    fn_1_6DEC(obj);
    fn_1_6FE8(obj);
}

void fn_1_6CF4(omObjData *arg0) {
    s16 temp_r3;
    s32 var_r30;
    s32 var_r31;
    void *temp_r25;
    M534Score *temp_r26;
    M534Board *temp_r29;

    temp_r26 = arg0->data;
    temp_r25 = HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_MGCONST, 50), MEMORY_DEFAULT_NUM, HEAP_DATA);
    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        temp_r29 = &temp_r26->unk0[var_r31];
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_350[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31] = temp_r3;
        Hu3DModelLayerSet(temp_r3, 0);
        var_r30 = 0;
loop_3:
        if (var_r30 < 3) {
            temp_r29->unk38[var_r30] = Hu3DAnimCreate(temp_r25, temp_r3, lbl_1_data_358[var_r30]);
            Hu3DAnimAttrSet(temp_r29->unk38[var_r30], 1U);
            var_r30 += 1;
            goto loop_3;
        }
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6DEC(omObjData *arg0) {
    s32 var_r29;
    s32 var_r30;
    M534Score *temp_r28;
    M534Board *temp_r31;

    temp_r28 = arg0->data;
    var_r29 = 0;
loop_4:
    if (var_r29 < 2) {
        temp_r31 = &temp_r28->unk0[var_r29];
        var_r30 = temp_r31->unk34;
        if (var_r30 > 0x3E7) {
            var_r30 = 0x3E7;
        }
        Hu3DAnimBankSet(temp_r31->unk38[0], (s32) (u16) (var_r30 / 100));
        Hu3DAnimBankSet(temp_r31->unk38[1], (s32) (u16) ((var_r30 % 100) / 10));
        Hu3DAnimBankSet(temp_r31->unk38[2], (s32) (u16) ((var_r30 % 100) % 10));
        var_r29 += 1;
        goto loop_4;
    }
}

void fn_1_6EE0(omObjData *arg0) {
    M534Score *sp8;
    s16 var_r27;
    s16 var_r28;
    s16 var_r31;
    s32 var_r30;

    var_r27 = 0 /* TODO(mp5): uninitialised in the original */;
    var_r28 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = arg0->data;
    var_r30 = 0;
loop_5:
    if (var_r30 < 2) {
        if (var_r30 == 0) {
            var_r28 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 14), MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r31 = var_r28;
            var_r27 = Hu3DJointMotion(var_r31, HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 15), MEMORY_DEFAULT_NUM, HEAP_DATA));
        } else {
            var_r31 = Hu3DModelLink(var_r28);
        }
        arg0->model[var_r30 + 2] = var_r31;
        Hu3DMotionSet(var_r31, var_r27);
        Hu3DModelAttrSet(var_r31, 0x40000001U);
        Hu3DModelLayerSet(var_r31, 0);
        Hu3DModelHookSet(var_r31, "itemhook_sao", arg0->model[var_r30]);
        Hu3DModelAttrSet(var_r31, 1U);
        var_r30 += 1;
        goto loop_5;
    }
}

void fn_1_6FE8(omObjData *arg0) {
    Vec sp8;
    Vec *temp_r4;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r29;
    s32 temp_r0;
    s32 var_r30;
    M534Score *temp_r27;
    M534Board *temp_r31;

    temp_r27 = arg0->data;
    var_r30 = 0;
loop_20:
    if (var_r30 < 2) {
        temp_r31 = &temp_r27->unk0[var_r30];
        temp_r29 = arg0->model[var_r30 + 2];
        temp_r0 = temp_r31->unk0;
        switch (temp_r0) {                          /* irregular */
        case 0:
            temp_r31->unk8 = 20.0f;
            temp_r31->unkC = (f32) (90.0f * (f32) var_r30);
            temp_r4 = &lbl_1_data_370[var_r30];
            temp_r31->unk10 = (f32) temp_r4->x;
            temp_r31->unk14 = (f32) temp_r4->y;
            temp_r31->unk18 = (f32) temp_r4->z;
            temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            break;
        case 1:
            if ((fn_1_179C() != 0) && (fn_1_17C8() != 0)) {
                Hu3DModelAttrReset(temp_r29, 1U);
                temp_r31->unk4 = 0.0f;
                temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            }
            break;
        case 2:
            temp_r31->unk4 = (f32) ((f64) temp_r31->unk4 + 0.02);
            if (temp_r31->unk4 > 1.0f) {
                temp_r31->unk4 = 1.0f;
            }
            temp_f31 = (f32) sin(1.5707963267948966 * (f64) temp_r31->unk4);
            temp_r31->unk10 = (f32) (lbl_1_data_370[var_r30].x + (temp_f31 * (lbl_1_data_388[var_r30].x - lbl_1_data_370[var_r30].x)));
            temp_r31->unk14 = (f32) (lbl_1_data_370[var_r30].y + (temp_f31 * (lbl_1_data_388[var_r30].y - lbl_1_data_370[var_r30].y)));
            temp_r31->unk18 = (f32) (lbl_1_data_370[var_r30].z + (temp_f31 * (lbl_1_data_388[var_r30].z - lbl_1_data_370[var_r30].z)));
            if (fn_1_49FC() != 0) {
                temp_r31->unk4 = 0.0f;
                temp_r31->unk0 = (s32) (temp_r31->unk0 + 1);
            }
            break;
        case 3:
            temp_r31->unk4 = (f32) ((f64) temp_r31->unk4 + 0.02);
            if (temp_r31->unk4 > 1.0f) {
                temp_r31->unk4 = 1.0f;
            }
            temp_f31_2 = temp_r31->unk4;
            temp_r31->unk10 = (f32) (lbl_1_data_388[var_r30].x + (temp_f31_2 * (lbl_1_data_3A0[var_r30].x - lbl_1_data_388[var_r30].x)));
            temp_r31->unk14 = (f32) (lbl_1_data_388[var_r30].y + (temp_f31_2 * (lbl_1_data_3A0[var_r30].y - lbl_1_data_388[var_r30].y)));
            temp_r31->unk18 = (f32) (lbl_1_data_388[var_r30].z + (temp_f31_2 * (lbl_1_data_3A0[var_r30].z - lbl_1_data_388[var_r30].z)));
            break;
        }
        temp_r31->unkC = (f32) ((f64) temp_r31->unkC + 1.0);
        VECAdd((Vec *)&temp_r31->unk10, (Vec *)&temp_r31->unk1C, (Vec *)&temp_r31->unk10);
        sp8.x = (f32) ((f64) temp_r31->unk10 + ((f64) temp_r31->unk8 * sin((3.141592653589793 * (f64) temp_r31->unkC) / 180.0)));
        sp8.y = (f32) ((f64) temp_r31->unk14 + ((f64) temp_r31->unk8 * cos((3.141592653589793 * (f64) temp_r31->unkC) / 180.0)));
        sp8.z = temp_r31->unk18;
        Hu3DModelPosSetV(temp_r29, &sp8);
        Hu3DModelRotSetV(temp_r29, (Vec *)&temp_r31->unk28);
        var_r30 += 1;
        goto loop_20;
    }
}

void fn_1_74B0(s32 team, s32 add) {
    s32 temp_r5;
    M534Score *temp_r31;

    temp_r31 = lbl_1_bss_58->data;
    temp_r31->unk0[team].unk34 += add;
}

s32 fn_1_74E8(s32 team) {
    return ((M534Score *)lbl_1_bss_58->data)->unk0[team].unk34;
}

void fn_1_3360(HUPROCESS *arg0) {
    HUPROCESS *sp8;
    omObjData *temp_r3;
    void *temp_r3_2;

    sp8 = arg0;
    temp_r3 = omAddObjEx(arg0, 0x14, 0x1CU, 0U, -1, fn_1_33EC);
    lbl_1_bss_48 = temp_r3;
    temp_r3_2 = HuMemDirectMallocNum(HEAP_SYSTEM, 0x200, MEMORY_DEFAULT_NUM);
    temp_r3->data = temp_r3_2;
    memset(temp_r3_2, 0, 0x200);
}

void fn_1_33E8(void) {

}

void fn_1_33EC(omObjData *obj) {
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;

    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 0), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[0] = temp_r3;
    Hu3DModelAttrSet(temp_r3, 0x40000001U);
    Hu3DModelClusterAttrSet(temp_r3, 0, -0x3FFFFFFF);
    Hu3DModelShadowMapSet(temp_r3);
    Hu3DModelLayerSet(temp_r3, 0);
    temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 11), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[1] = temp_r3_2;
    Hu3DModelAttrSet(temp_r3_2, 0x40000001U);
    Hu3DModelClusterAttrSet(temp_r3_2, 0, -0x3FFFFFFF);
    Hu3DModelLayerSet(temp_r3_2, 2);
    temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 6), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[2] = temp_r3_3;
    Hu3DModelShadowMapSet(temp_r3_3);
    Hu3DModelAttrSet(temp_r3_3, 0x40000002U);
    Hu3DModelLayerSet(temp_r3_3, 0);
    temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 7), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[3] = temp_r3_4;
    Hu3DModelLayerSet(temp_r3_4, 0);
    fn_1_3674(temp_r3_4, 1);
    temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 8), MEMORY_DEFAULT_NUM, HEAP_DATA));
    obj->model[4] = temp_r3_5;
    Hu3DModelAttrSet(temp_r3_5, 1U);
    Hu3DModelAttrSet(temp_r3_5, 0x40000002U);
    Hu3DModelAttrReset(temp_r3_5, 0x40000001U);
    Hu3DModelLayerSet(temp_r3_5, 0);
    fn_1_3AC8(obj);
    temp_r3_6 = Hu3DHookFuncCreate(fn_1_3CAC);
    obj->model[26] = temp_r3_6;
    Hu3DModelLayerSet(temp_r3_6, 1);
    temp_r3_7 = Hu3DHookFuncCreate(fn_1_3D58);
    obj->model[27] = temp_r3_7;
    Hu3DModelLayerSet(temp_r3_7, 3);
    fn_1_4450(obj);
    fn_1_3E04(obj);
    fn_1_3FA0(obj);
    fn_1_426C(obj);
    obj->func = fn_1_3624;
}

void fn_1_3624(omObjData *obj) {
    fn_1_3B1C(obj);
    fn_1_3F04(obj);
    fn_1_406C(obj);
    fn_1_4A3C(obj);
    fn_1_430C(obj);
}

void fn_1_3674(s16 arg0, s16 arg1) {
    Mtx sp38;
    Vec sp2C;
    Vec sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    s16 sp8;
    HSFDATA *temp_r27;
    HSFOBJECT *var_r26;
    HU3DMODEL *temp_r28;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f28;
    f32 temp_f29;
    f32 var_f26;
    f32 var_f27;
    f64 temp_f30;
    f64 temp_f30_2;
    f64 temp_f30_3;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r3;
    s16 var_r25;
    u8 temp_r0;

    sp8 = arg1;
    temp_r28 = &Hu3DData[arg0];
    temp_r27 = temp_r28->hsf;
    if ((s16) temp_r28->lLightId[0] == -1) {
        var_r26 = temp_r27->object;
        var_r25 = 0;
loop_19:
        if (var_r25 < (s16) temp_r27->objectNum) {
            if ((u32) var_r26->type == 8) {
                sp14 = var_r26->light.target.x - var_r26->light.pos.x;
                sp18 = var_r26->light.target.y - var_r26->light.pos.y;
                sp1C = var_r26->light.target.z - var_r26->light.pos.z;
                temp_r3 = Hu3DLLightCreate(arg0, var_r26->light.pos.x, var_r26->light.pos.y, var_r26->light.pos.z, sp14, sp18, sp1C, var_r26->light.r, var_r26->light.g, var_r26->light.b);
                Hu3DLLightStaticSet(arg0, temp_r3, (s32) sp8);
                temp_r0 = var_r26->light.type;
                switch ((s32) temp_r0) {            /* irregular */
                case 0:
                    Hu3DLLightSpotSet(arg0, temp_r3, var_r26->light.cutoff, 2);
                    break;
                case 1:
                    Hu3DLLightPointSet(arg0, temp_r3, var_r26->light.ref_brightness - var_r26->light.ref_distance, 1.0f, 2);
                    temp_f29 = (sp14 * sp14) + (sp1C * sp1C);
                    var_f27 = sqrtf(temp_f29);
                    temp_f25 = (f32) atan2((f64) sp18, (f64) var_f27);
                    temp_f24 = (f32) atan2(-sp14, -sp1C);
                    sp2C.z = 0.0f;
                    sp2C.y = 0.0f;
                    sp2C.x = 0.0f;
                    sp20.z = 0.0f;
                    sp20.x = 0.0f;
                    temp_f28 = (sp1C * sp1C) + ((sp14 * sp14) + (sp18 * sp18));
                    var_f26 = sqrtf(temp_f28);
                    sp20.y = var_f26;
                    mtxRot(sp38, 57.29578f * temp_f25, 57.29578f * temp_f24, 0.0f);
                    MTXMultVec(sp38, &sp20, &sp20);
                    Hu3DLLightPosAimSetV(arg0, temp_r3, &sp20, &sp2C);
                    break;
                case 2:
                    Hu3DLLightInfinitytSet(arg0, temp_r3);
                    break;
                }
            }
            var_r25 += 1;
            var_r26++;
            goto loop_19;
        }
    }
}

void fn_1_3AC8(omObjData *arg0) {
    s32 var_r30;
    M534Stage *var_r31;

    var_r31 = arg0->data;
    var_r30 = 0;
loop_2:
    if (var_r30 < 0x20) {
        var_r31->unk0[0].unk0 = -1;
        var_r31->unk0[0].unk4 = -1;
        var_r30 += 1;
        var_r31 += 8;
        goto loop_2;
    }
}

void fn_1_3B1C(omObjData *arg0) {
    s32 var_r30;
    M534Stage *var_r31;

    var_r31 = arg0->data;
    var_r30 = 0;
loop_5:
    if (var_r30 < 0x20) {
        if (((s32) var_r31->unk0[0].unk4 != -1) && (HuAudFXStatusGet(var_r31->unk0[0].unk4) != 2)) {
            var_r31->unk0[0].unk0 = -1;
            var_r31->unk0[0].unk4 = -1;
        }
        var_r30 += 1;
        var_r31 += 8;
        goto loop_5;
    }
}



void fn_1_3CAC(HU3DMODEL *modelP, f32 (*mtx)[3][4]) {
    GXColor fogColor = { 200, 200, 255, 0 };

    GXSetFog(GX_FOG_LIN, 1000.0f, 8000.0f, 10.0f, 20000.0f, fogColor);
}

void fn_1_3D58(HU3DMODEL *modelP, f32 (*mtx)[3][4]) {
    GXColor fogColor = { 255, 255, 255, 0 };

    GXSetFog(GX_FOG_NONE, 1000.0f, 8000.0f, 10.0f, 20000.0f, fogColor);
}

void fn_1_3E04(omObjData *arg0) {
    M534Cloud *var_r31;
    f32 temp_f31;
    s16 temp_r3;
    s32 var_r30;
    M534Stage *temp_r28;
    Vec *temp_r4;

    temp_r28 = arg0->data;
    var_r31 = lbl_1_data_190;
    var_r30 = 0;
loop_2:
    if (var_r30 < 5) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) var_r31->unk0, MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r30 + 5] = temp_r3;
        temp_r4 = &temp_r28->unk100[var_r30];
        temp_r4->x = (f32) var_r31->unk4.x;
        temp_r4->y = (f32) var_r31->unk4.y;
        temp_r4->z = (f32) var_r31->unk4.z;
        temp_r28->unk13C[var_r30] = var_r31->unk14;
        temp_f31 = var_r31->unk10;
        Hu3DModelPosSetV(temp_r3, &var_r31->unk4);
        Hu3DModelScaleSet(temp_r3, temp_f31, temp_f31, temp_f31);
        Hu3DModelAttrSet(temp_r3, 0x40000001U);
        Hu3DModelLayerSet(temp_r3, 0);
        var_r30 += 1;
        var_r31++;
        goto loop_2;
    }
}

void fn_1_3F04(omObjData *arg0) {
    s32 temp_r4;
    s32 var_r31;
    M534Stage *temp_r30;

    temp_r30 = arg0->data;
    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        temp_r30->unk100[var_r31].x += temp_r30->unk13C[var_r31];
        Hu3DModelPosSetV(arg0->model[var_r31 + 5], &temp_r30->unk100[var_r31]);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_3FA0(omObjData *arg0) {
    s16 temp_r3;
    s32 var_r31;
    M534Stage *temp_r28;

    temp_r28 = arg0->data;
    var_r31 = 0;
loop_2:
    if (var_r31 < 0x10) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M534, 10), MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->model[var_r31 + 0xA] = temp_r3;
        Hu3DModelAttrSet(temp_r3, 1U);
        Hu3DModelAttrSet(temp_r3, 0x40000002U);
        Hu3DModelAttrReset(temp_r3, 0x40000001U);
        Hu3DModelLayerSet(temp_r3, 6);
        temp_r28->unk150[var_r31] = 0;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_406C(omObjData *arg0) {
    s16 temp_r28;
    s32 var_r31;
    M534Stage *temp_r30;

    temp_r30 = arg0->data;
    var_r31 = 0;
loop_5:
    if (var_r31 < 0x10) {
        if ((s32) temp_r30->unk150[var_r31] != 0) {
            temp_r28 = arg0->model[var_r31 + 0xA];
            if (Hu3DMotionEndCheck(temp_r28) != 0) {
                Hu3DModelAttrSet(temp_r28, 1U);
                temp_r30->unk150[var_r31] = 0;
            }
        }
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_4114(s32 slot) {
    s32 sp8;
    s16 temp_r30;
    s32 var_r31;
    M534Stage *temp_r28;

    sp8 = slot;
    temp_r28 = lbl_1_bss_48->data;
    var_r31 = 0;
loop_4:
    if (var_r31 >= 0x10) {
        return;
    }
    if ((s32) temp_r28->unk150[var_r31] == 0) {
        temp_r28->unk150[var_r31] = 1;
        temp_r30 = lbl_1_bss_48->model[var_r31 + 0xA];
        Hu3DModelPosSetV(temp_r30, &lbl_1_data_208[sp8]);
        Hu3DModelRotSet(temp_r30, 0.0f, (f32) (360.0 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))), 0.0f);
        Hu3DModelAttrReset(temp_r30, 1U);
        Hu3DModelAttrReset(temp_r30, 0x40000002U);
        Hu3DMotionTimeSet(temp_r30, 0.0f);
        return;
    }
    var_r31 += 1;
    goto loop_4;
}

void fn_1_426C(omObjData *arg0) {
    HSFOBJECT *temp_r3;
    s16 temp_r27;
    s32 var_r31;
    M534Stage *temp_r30;

    temp_r30 = arg0->data;
    temp_r27 = *arg0->model;
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        temp_r3 = Hu3DModelObjPtrGet(temp_r27, lbl_1_data_2C8[var_r31]);
        if (temp_r3 != NULL) {
            temp_r30->unk190[var_r31] = temp_r3->mesh.base.pos.y;
        }
        temp_r30->unk1A0[var_r31] = 0.0f;
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_430C(omObjData *arg0) {
    HSFOBJECT *temp_r3;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r27;
    s32 var_r31;
    M534Stage *temp_r30;

    temp_r30 = arg0->data;
    temp_r27 = *arg0->model;
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        temp_f31 = (f32) ((f64) temp_r30->unk1A0[var_r31] * 0.5);
        temp_r30->unk1A0[var_r31] = temp_f31;
        temp_f31_2 = temp_f31 + temp_r30->unk190[var_r31];
        temp_r3 = Hu3DModelObjPtrGet(temp_r27, lbl_1_data_2C8[var_r31]);
        if (temp_r3 != NULL) {
            temp_r3->mesh.base.pos.y = temp_f31_2;
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_43D4(s32 slot) {
    ((M534Stage *)lbl_1_bss_48->data)->unk1A0[slot] = -12.0f;
    if (slot < 2) {
        HuAudFXPlay(0x7BD);
        return;
    }
    HuAudFXPlay(0x7BE);
}

void fn_1_4450(omObjData *arg0) {
    M534Stage *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk1B4 = 0;
    temp_r31->unk1C4 = 0xC;
    temp_r31->unk1E8 = 0.5f;
    temp_r31->unk1F0 = -710.0f;
    temp_r31->unk1EC = -710.0f;
}

void fn_1_449C(s32 team) {
    s32 sp8;
    omObjData *temp_r28;
    s32 temp_r0;
    s32 temp_r3;
    s32 var_r26;
    s32 var_r27;
    M534Stage *temp_r31;
    M534Snd *var_r29;
    M534Snd *var_r30;

    sp8 = team;
    temp_r28 = lbl_1_bss_48;
    temp_r31 = temp_r28->data;
    if (((s32) temp_r31->unk1B4 == 4) && (fn_1_74B0(sp8, 1), temp_r0 = temp_r31->unk1C4 - 1, temp_r31->unk1C4 = temp_r0, ((temp_r0 > 0) == 0))) {
        temp_r31->unk1C4 = 0x3C;
        if (temp_r31->unk1EC < 0.0f) {
            temp_r31->unk1EC = (f32) ((f64) temp_r31->unk1EC + 60.0);
        }
        fn_1_5CB0(8);
        temp_r31->unk1C0 = 0x14;
        temp_r31->unk1C8 = 3.0f;
        temp_r31->unk1D0 = 0.2f;
        temp_r31->unk1D4 = 0.0f;
        temp_r3 = fn_1_4624();
        if (temp_r3 != -1) {
            var_r30 = ((M534Stage *)temp_r28->data)->unk0;
            var_r27 = 0;
loop_9:
            if (var_r27 < 0x20) {
                if ((s32) var_r30->unk4 == -1) {
                    var_r30->unk0 = 0x7BF;
                    var_r30->unk4 = HuAudFXPlay(0x7BF);
                } else {
                    var_r27 += 1;
                    var_r30++;
                    goto loop_9;
                }
            }
        }
        if (temp_r3 != 1) {
            var_r29 = ((M534Stage *)temp_r28->data)->unk0;
            var_r26 = 0;
loop_15:
            if (var_r26 >= 0x20) {

            } else {
                if ((s32) var_r29->unk4 == -1) {
                    var_r29->unk0 = 0x7C0;
                    var_r29->unk4 = HuAudFXPlay(0x7C0);
                    return;
                }
                var_r26 += 1;
                var_r29++;
                goto loop_15;
            }
        }
    }
}

s32 fn_1_4624(void) {
    M534Stage *sp8;
    s32 temp_r30;
    s32 temp_r3;

    sp8 = lbl_1_bss_48->data;
    temp_r30 = fn_1_74E8(0);
    temp_r3 = fn_1_74E8(1);
    if (temp_r30 > temp_r3) {
        return 1;
    }
    if (temp_r30 < temp_r3) {
        return -1;
    }
    return 0;
}


f32 fn_1_4848(void) {
    M534Stage *sp8;
    f32 var_f31;
    s32 temp_r27;
    s32 temp_r3;
    s32 var_r30;
    M534Stage *temp_r31;

    temp_r31 = lbl_1_bss_48->data;
    sp8 = lbl_1_bss_48->data;
    temp_r27 = fn_1_74E8(0);
    temp_r3 = fn_1_74E8(1);
    if (temp_r27 > temp_r3) {
        var_r30 = 1;
    } else if (temp_r27 < temp_r3) {
        var_r30 = -1;
    } else {
        var_r30 = 0;
    }
    if (var_r30 != 0) {
        var_f31 = (f32) ((f64) temp_r31->unk1F4 / 76.0);
    } else {
        var_f31 = (f32) ((f64) temp_r31->unk1FC / 90.0);
    }
    if (var_f31 < 0.0f) {
        var_f31 = 0.0f;
    }
    if (var_f31 > 1.0f) {
        var_f31 = 1.0f;
    }
    return var_f31;
}


s32 fn_1_49BC(void) {
    return ((M534Stage *)lbl_1_bss_48->data)->unk1B4 == 0xC;
}

s32 fn_1_49FC(void) {
    return ((M534Stage *)lbl_1_bss_48->data)->unk1B4 == 8;
}

void fn_1_4A3C(omObjData *arg0) {
    Vec sp70;
    M534Stage *sp6C;
    omObjData *sp68;
    s32 sp64;
    s32 sp60;
    M534Stage *sp5C;
    omObjData *sp58;
    M534Stage *sp54;
    M534Stage *sp50;
    M534Stage *sp4C;
    s32 sp48;
    M534Stage *sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    M534Stage *sp34;
    omObjData *sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    M534Stage *sp20;
    omObjData *sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    M534Stage *spC;
    omObjData *sp8;
    HSFOBJECT *temp_r3_8;
    HSFOBJECT *temp_r3_9;
    f32 temp_f27;
    f32 temp_f31;
    f32 var_f30;
    f32 var_f31;
    f32 var_f31_2;
    s16 temp_r22;
    s16 temp_r22_2;
    s16 var_r21;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 var_r17;
    s32 var_r18;
    s32 var_r19;
    s32 var_r20;
    s32 var_r23;
    u32 temp_r5;
    M534Stage *temp_r31;
    M534Snd *var_r25;
    M534Snd *var_r26;
    M534Snd *var_r27;
    M534Snd *var_r28;

    temp_r31 = arg0->data;
    temp_r5 = temp_r31->unk1B4;
    switch (temp_r5) {
    case 0:
        if (fn_1_16AC() == 5) {
            Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
            var_r21 = 0;
loop_5:
            if (var_r21 < 4) {
                omVibrate(var_r21, 0x28, 0xC, 0);
                var_r21 += 1;
                goto loop_5;
            }
            temp_r31->unk1B4 = 1U;
        }
        break;
    case 1:
        fn_1_5B64();
        if (fn_1_16AC() == 6) {
            temp_r31->unk1B4 = 2U;
            temp_r31->unk1B8 = 0;
            temp_r31->unk1E8 = 0.1f;
            temp_r31->unk1EC = -400.0f;
            Hu3DModelAttrReset(arg0->model[4], 0x40000002U);
            Hu3DModelAttrReset(arg0->model[4], 1U);
            temp_r31->unk1B0 = 1;
            HuAudFXPlay(0x7BC);
        }
        break;
    case 2:
        temp_r3 = temp_r31->unk1B8 + 1;
        temp_r31->unk1B8 = temp_r3;
        if ((s32) (temp_r3 & 1) == 0) {
            fn_1_5B64();
        }
        if (temp_r31->unk1F0 < -500.0f) {
            Hu3DModelShadowSet(arg0->model[3]);
            temp_r31->unk1C8 = 3.0f;
            temp_r31->unk1D0 = 0.2f;
            temp_r31->unk1D4 = 0.0f;
        }
        if (!(temp_r31->unk1F0 < -400.1f)) {
            temp_r31->unk1E8 = 0.02f;
            temp_r31->unk1B4 = 3U;
        }
        break;
    case 3:
        temp_r31->unk1C0 = 5;
        if (fn_1_1694() == 2) {
            temp_r31->unk1B4 = 4U;
            temp_r31->unk1B8 = 0;
        }
        break;
    case 4:
        if (fn_1_1694() != 3) {
            if (fn_1_179C() == 0) {
                sp68 = lbl_1_bss_48;
                sp6C = lbl_1_bss_48->data;
                temp_f27 = (f32) fn_1_74E8(1);
                temp_f31 = (f32) fn_1_74E8(0) - temp_f27;
                if (temp_f31 >= 0.0f) {
                    if (temp_f31 <= 4.0f) {
                        var_f31 = 0.0f;
                    } else {
                        var_f31 = (f32) ((f64) temp_f31 - 4.0);
                    }
                } else if (temp_f31 >= -4.0f) {
                    var_f31 = 0.0f;
                } else {
                    var_f31 = (f32) ((f64) temp_f31 + 4.0);
                }
                var_f31_2 = (f32) ((f64) var_f31 * 5.0);
                if (var_f31_2 > 20.0f) {
                    var_f31_2 = 20.0f;
                }
                if (var_f31_2 < -20.0f) {
                    var_f31_2 = -20.0f;
                }
                temp_r31->unk1F8 = (f32) ((f64) temp_r31->unk1F8 + (0.1 * (f64) (var_f31_2 - temp_r31->unk1F8)));
            }
        } else {
            temp_r31->unk1B4 = 5U;
            temp_r31->unk1B8 = 0;
            temp_r31->unk1DC = (f32) Center.y;
            sp58 = lbl_1_bss_48;
            sp5C = lbl_1_bss_48->data;
            sp60 = fn_1_74E8(0);
            temp_r3_2 = fn_1_74E8(1);
            sp64 = temp_r3_2;
            if (sp60 > temp_r3_2) {
                var_r20 = 1;
            } else if (sp60 < sp64) {
                var_r20 = -1;
            } else {
                var_r20 = 0;
            }
            if (var_r20 != -1) {
                var_r28 = ((M534Stage *)arg0->data)->unk0;
                var_r19 = 0;
loop_41:
                if (var_r19 < 0x20) {
                    if ((s32) var_r28->unk4 == -1) {
                        var_r28->unk0 = 0x7BF;
                        var_r28->unk4 = HuAudFXPlay(0x7BF);
                    } else {
                        var_r19 += 1;
                        var_r28++;
                        goto loop_41;
                    }
                }
            }
            if (var_r20 != 1) {
                var_r27 = ((M534Stage *)arg0->data)->unk0;
                var_r18 = 0;
loop_47:
                if (var_r18 >= 0x20) {

                } else if ((s32) var_r27->unk4 == -1) {
                    var_r27->unk0 = 0x7C0;
                    var_r27->unk4 = HuAudFXPlay(0x7C0);
                } else {
                    var_r18 += 1;
                    var_r27++;
                    goto loop_47;
                }
            }
        }
        break;
    case 5:
        temp_r31->unk1D0 = 0.15f;
        temp_r31->unk1D4 = 0.0f;
        temp_r3_3 = temp_r31->unk1B8 + 1;
        temp_r31->unk1B8 = temp_r3_3;
        if ((s32) (temp_r3_3 & 3) == 0) {
            fn_1_5CB0(3);
            temp_r31->unk1C0 = 8;
            temp_r31->unk1C8 = 5.0f;
            temp_r31->unk1EC = (f32) ((f64) temp_r31->unk1EC + 20.0);
            if (!(temp_r31->unk1EC < 0.0f)) {
                temp_r31->unk1EC = 0.0f;
                temp_r31->unk1B4 = 6U;
                temp_r31->unk1B8 = 0;
                var_r26 = ((M534Stage *)arg0->data)->unk0;
                var_r17 = 0;
loop_56:
                if (var_r17 < 0x20) {
                    if (((s32) var_r26->unk4 != -1) && ((s32) var_r26->unk0 == 0x7BF)) {
                        HuAudFXFadeOut(var_r26->unk4, 0x1F4);
                    }
                    var_r17 += 1;
                    var_r26++;
                    goto loop_56;
                }
                var_r25 = ((M534Stage *)arg0->data)->unk0;
                sp48 = 0;
loop_62:
                if (sp48 < 0x20) {
                    if (((s32) var_r25->unk4 != -1) && ((s32) var_r25->unk0 == 0x7C0)) {
                        HuAudFXFadeOut(var_r25->unk4, 0x1F4);
                    }
                    sp48 += 1;
                    var_r25++;
                    goto loop_62;
                }
            }
        }
        break;
    case 6:
        temp_r31->unk1D0 = 0.1f;
        temp_r31->unk1B4 = 7U;
        temp_r31->unk1B8 = 0;
        break;
    case 7:
        temp_r31->unk1D0 = 0.1f;
        temp_r0 = temp_r31->unk1B8 + 1;
        temp_r31->unk1B8 = temp_r0;
        if (!((f32) (f64) temp_r0 < 42.0f)) {
            temp_r31->unk1B4 = 8U;
            temp_r31->unk1B8 = 0;
        }
        break;
    case 8:
        temp_r31->unk1D8 = (f32) ((f64) temp_r31->unk1D8 - 0.1);
        sp30 = lbl_1_bss_48;
        sp34 = sp30->data;
        temp_r3_4 = fn_1_74E8(0);
        sp38 = temp_r3_4;
        sp3C = fn_1_74E8(1);
        if (temp_r3_4 > sp3C) {
            sp40 = 1;
        } else if (sp38 < sp3C) {
            sp40 = -1;
        } else {
            sp40 = 0;
        }
        if (sp40 != 0) {
            temp_r31->unk1F4 = (f32) (temp_r31->unk1F4 + temp_r31->unk1D8);
            if (!(temp_r31->unk1F4 > -40.0f)) {
                goto block_76;
            }
        } else {
            temp_r31->unk1F8 = (f32) ((f64) temp_r31->unk1F8 + (0.1 * (f64) (90.0f - temp_r31->unk1F8)));
            temp_r31->unk1FC = (f32) (temp_r31->unk1FC + temp_r31->unk1D8);
            if (!(temp_r31->unk1FC > -40.0f)) {
block_76:
                temp_r31->unk1B4 = 9U;
                temp_r31->unk1B8 = 0;
            }
        }
        break;
    case 9:
        temp_r31->unk1D8 = (f32) ((f64) temp_r31->unk1D8 + 0.2);
        if (temp_r31->unk1D8 > 0.0f) {
            temp_r31->unk1D8 = 0.0f;
        }
        sp1C = lbl_1_bss_48;
        sp20 = sp1C->data;
        temp_r3_5 = fn_1_74E8(0);
        sp24 = temp_r3_5;
        sp28 = fn_1_74E8(1);
        if (temp_r3_5 > sp28) {
            sp2C = 1;
        } else if (sp24 < sp28) {
            sp2C = -1;
        } else {
            sp2C = 0;
        }
        if (sp2C != 0) {
            temp_r31->unk1F4 = (f32) (temp_r31->unk1F4 + temp_r31->unk1D8);
        } else {
            temp_r31->unk1F8 = (f32) ((f64) temp_r31->unk1F8 + (0.1 * (f64) (90.0f - temp_r31->unk1F8)));
            temp_r31->unk1FC = (f32) (temp_r31->unk1FC + temp_r31->unk1D8);
        }
        if (!(temp_r31->unk1D8 < 0.0f)) {
            temp_r0_2 = temp_r31->unk1B8 + 1;
            temp_r31->unk1B8 = temp_r0_2;
            if (temp_r0_2 >= 0xF) {
                temp_r31->unk1B4 = 0xAU;
                temp_r31->unk1B8 = 0;
                temp_r31->unk1BC = -1;
            }
        }
        break;
    case 10:
        var_r23 = 0;
        sp8 = lbl_1_bss_48;
        spC = sp8->data;
        temp_r3_6 = fn_1_74E8(0);
        sp10 = temp_r3_6;
        sp14 = fn_1_74E8(1);
        if (temp_r3_6 > sp14) {
            sp18 = 1;
        } else if (sp10 < sp14) {
            sp18 = -1;
        } else {
            sp18 = 0;
        }
        temp_r31->unk1D8 = (f32) ((f64) temp_r31->unk1D8 + 0.3);
        if (sp18 != 0) {
            temp_r31->unk1F4 = (f32) (temp_r31->unk1F4 + temp_r31->unk1D8);
            if (temp_r31->unk1F4 >= 76.0f) {
                temp_r31->unk1D0 = 0.0f;
                temp_r31->unk1C8 = 0.0f;
                temp_r31->unk1F4 = 76.0f;
                temp_r31->unk1D8 = (f32) (0.5 * -temp_r31->unk1D8);
                if (temp_r31->unk1D8 < -1.0f) {
                    temp_r31->unk1E0 = (f32) (-20.0 * (f64) temp_r31->unk1D8);
                } else {
                    var_r23 = 1;
                }
            }
            if (temp_r31->unk1F4 >= 61.0f) {
                temp_r3_7 = temp_r31->unk1B8 + 1;
                temp_r31->unk1B8 = temp_r3_7;
                if (temp_r3_7 < 0xA) {
                    if (sp18 == -1) {
                        fn_1_5E20(2, lbl_1_data_2E8);
                    } else {
                        fn_1_5E20(2, &lbl_1_data_2E8[1]);
                    }
                }
            }
            temp_r31->unk1F8 = (f32) ((f64) temp_r31->unk1F8 + (0.05 * (f64) ((20.0f * (f32) sp18) - temp_r31->unk1F8)));
            if (((s32) temp_r31->unk1BC == -1) && (temp_r31->unk1F4 >= 50.0f)) {
                if (sp18 == -1) {
                    temp_r31->unk1BC = HuAudFXPlay(0x7C1);
                }
                if (sp18 == 1) {
                    temp_r31->unk1BC = HuAudFXPlay(0x7C2);
                }
            }
        } else {
            temp_r31->unk1FC = (f32) (temp_r31->unk1FC + temp_r31->unk1D8);
            if (temp_r31->unk1FC >= 90.0f) {
                temp_r31->unk1D0 = 0.0f;
                temp_r31->unk1C8 = 0.0f;
                temp_r31->unk1FC = 90.0f;
                temp_r31->unk1D8 = (f32) (0.3 * -temp_r31->unk1D8);
                if (temp_r31->unk1D8 < -1.0f) {
                    temp_r31->unk1E0 = (f32) (-20.0 * (f64) temp_r31->unk1D8);
                } else {
                    var_r23 = 1;
                }
            }
            if (temp_r31->unk1FC >= 75.0f) {
                temp_r0_3 = temp_r31->unk1B8 + 1;
                temp_r31->unk1B8 = temp_r0_3;
                if (temp_r0_3 < 0xA) {
                    fn_1_5E20(2, lbl_1_data_2E8);
                    fn_1_5E20(2, &lbl_1_data_2E8[1]);
                }
            }
            temp_r31->unk1F8 = (f32) ((f64) temp_r31->unk1F8 + (0.1 * (f64) (90.0f - temp_r31->unk1F8)));
            if (((s32) temp_r31->unk1BC == -1) && (temp_r31->unk1FC >= 60.0f)) {
                temp_r31->unk1BC = HuAudFXPlay(0x7C1);
                temp_r31->unk1BC = HuAudFXPlay(0x7C2);
            }
        }
        if (var_r23 != 0) {
            temp_r31->unk1B4 = 0xBU;
            temp_r31->unk1B8 = 0;
        }
        break;
    case 11:
        if (temp_r31->unk1E0 == 0.0f) {
            temp_r31->unk1B4 = 0xCU;
            temp_r31->unk1B8 = 0;
            Center.y = temp_r31->unk1DC;
        }
        break;
    }
    if (temp_r31->unk1E0 >= 1.0f) {
        Center.y = (f32) ((f64) temp_r31->unk1DC + ((f64) temp_r31->unk1E0 * sin((3.141592653589793 * (f64) temp_r31->unk1E4) / 180.0)));
        temp_r31->unk1E4 = (f32) (temp_r31->unk1E4 + 70.0f);
        temp_r31->unk1E0 = (f32) ((f64) temp_r31->unk1E0 * 0.9);
    } else {
        temp_r31->unk1E0 = 0.0f;
    }
    temp_r31->unk1F0 = (f32) (temp_r31->unk1F0 + (temp_r31->unk1E8 * (temp_r31->unk1EC - temp_r31->unk1F0)));
    temp_r31->unk1C8 = (f32) (0.98 * (f64) temp_r31->unk1C8);
    temp_r31->unk1CC = (f32) (temp_r31->unk1CC + 70.0f);
    temp_r31->unk1D0 = (f32) (0.98 * (f64) temp_r31->unk1D0);
    temp_r31->unk1D4 = (f32) (temp_r31->unk1D4 + 8.0f);
    temp_r22 = arg0->model[3];
    temp_r3_8 = Hu3DModelObjPtrGet(temp_r22, "l_han_foot");
    if (temp_r3_8 != NULL) {
        temp_r3_8->mesh.base.pos.x = (f32) ((f64) temp_r31->unk1C8 * sin((3.141592653589793 * (f64) temp_r31->unk1CC) / 180.0));
        temp_r3_8->mesh.base.pos.y = temp_r31->unk1F0;
        temp_r3_8->mesh.base.rot.y = temp_r31->unk1F8;
    }
    temp_r3_9 = Hu3DModelObjPtrGet(temp_r22, lbl_1_data_30B);
    if (temp_r3_9 != NULL) {
        temp_r3_9->mesh.base.rot.x = (f32) ((f64) temp_r31->unk1F4 + (2.0 * ((f64) temp_r31->unk1C8 * sin((3.141592653589793 * (f64) temp_r31->unk1D4) / 180.0))));
        temp_r3_9->mesh.base.rot.z = (f32) ((f64) temp_r31->unk1FC + ((f64) temp_r31->unk1D0 * sin((3.141592653589793 * (f64) temp_r31->unk1D4) / 180.0)));
    }
    if ((s32) temp_r31->unk1B0 != 0) {
        temp_r22_2 = arg0->model[4];
        if (Hu3DMotionEndCheck(temp_r22_2) != 0) {
            Hu3DModelAttrSet(temp_r22_2, 1U);
            temp_r31->unk1B0 = 0;
        } else {
            sp70.x = 0.0f;
            sp70.y = temp_r31->unk1F0;
            sp70.z = 0.0f;
            Hu3DModelPosSetV(temp_r22_2, &sp70);
        }
    }
    if ((s32) temp_r31->unk1C0 > 0) {
        var_f30 = (f32) temp_r31->unk1C0;
loop_139:
        if (var_f30 > 0.0f) {
            fn_1_5F94();
            var_f30 -= 2.0f;
            goto loop_139;
        }
        temp_r31->unk1C0 = (s32) ((f64) temp_r31->unk1C0 - 1.0);
    }
}

void fn_1_5B64(void) {
    Vec sp8;

    sp8.x = (f32) (250.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
    sp8.y = (f32) (80.0 + (100.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))));
    sp8.z = (f32) ((250.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))) - 500.0);
    fn_1_6458(&sp8);
}

void fn_1_5CB0(s32 count) {
    Vec spC;
    s32 sp8;
    s32 var_r31;

    sp8 = count;
    var_r31 = 0;
loop_2:
    if (var_r31 < sp8) {
        spC.x = (f32) (150.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
        spC.y = (f32) ((50.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))) - 50.0);
        spC.z = (f32) ((150.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))) - 500.0);
        fn_1_6458(&spC);
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_5E20(s32 count, Vec *center) {
    Vec spC;
    s32 sp8;
    s32 var_r30;

    sp8 = count;
    var_r30 = 0;
loop_2:
    if (var_r30 < sp8) {
        spC.x = (f32) ((f64) center->x + (100.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))));
        spC.y = (f32) ((f64) center->y + (100.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))));
        spC.z = (f32) ((f64) center->z + (100.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000))));
        fn_1_6458(&spC);
        var_r30 += 1;
        goto loop_2;
    }
}

void fn_1_5F94(void) {
    Vec sp8;
    Vec sp14;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f29;
    M534Stage *temp_r31;

    temp_r31 = lbl_1_bss_48->data;
    sp14.y = (f32) ((f64) temp_r31->unk1F0 + (640.0 + (10.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)))));
    sp8.y = (f32) ((0.2 * (1.52587890625e-05 * (f64) (f32) (frand() & 0xFFFF))) - 1.5);
    temp_f27 = temp_r31->unk1F8;
    temp_f31 = (f32) sin((3.141592653589793 * (f64) temp_f27) / 180.0);
    temp_f30 = (f32) cos((3.141592653589793 * (f64) temp_f27) / 180.0);
    if (fabs(temp_f27) < 8.0f) {
        var_f29 = 130.0f;
    } else {
        var_f29 = 140.0f;
    }
    temp_f28 = (f32) (200.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
    sp14.x = (temp_f30 * -var_f29) + (temp_f31 * temp_f28);
    sp14.z = (f32) ((f64) ((temp_f31 * -var_f29) + (temp_f30 * temp_f28)) - 500.0);
    sp8.x = (f32) (-5.0 * (f64) temp_f30);
    sp8.z = (f32) (-5.0 * (f64) temp_f31);
    fn_1_6938(&sp14, &sp8);
    temp_f28_2 = (f32) (200.0 * (3.0517578125e-05 * (f64) (f32) ((frand() & 0xFFFF) - 0x8000)));
    sp14.x = (temp_f30 * var_f29) + (temp_f31 * temp_f28_2);
    sp14.z = (f32) ((f64) ((temp_f31 * var_f29) + (temp_f30 * temp_f28_2)) - 500.0);
    sp8.x = (f32) (5.0 * (f64) temp_f30);
    sp8.z = (f32) (5.0 * (f64) temp_f31);
    fn_1_6938(&sp14, &sp8);
}
