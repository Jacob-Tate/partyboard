// MP5 m523 (Beam Team), generated from its m2c draft by tools/mp5/ports/m523Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m523Dll (tools/mp5/decomp.py m523Dll --types tools/mp5/types/m523Dll.h)
// Written from the draft: Beam Team (1 vs 3). The solo player (group 0) is a character that gets chased by a UFO's
// tractor beam... precisely: the three team players (group 1) run around; the solo player picks up / bumps them and
// they get beamed by the UFO (beam list lbl_1_bss_10C/E8). Runs on MP5's MgSeq sequencer; the camera code is the
// same library copy as m524/m570 (MgFlow in the draft is dead library code and is dropped by the fix script).
// objdata: M523Player
// objexpr lbl_1_bss_0: M523CamMove
// objexpr lbl_1_bss_4: M523CamMove
// objdata fn_1_221C: M523CamMove
// objdata fn_1_962C fn_1_9798: M523Beam
// var fn_1_39DC temp_r31: M523Player
// var fn_1_39DC var_r27: OMOBJ
// var MgCameraMoveEntry temp_r31: M523CamMove
// var fn_1_9798 temp_r31: M523Beam
// var fn_1_1068 temp_r3: M523Camera
// var fn_1_6294 temp_r28: OMOBJ
// var fn_1_6294 temp_r29: M523Player
// var fn_1_4CCC temp_r29: M523Player
// var fn_1_4900 temp_r26: M523Player
// var fn_1_4900 temp_r27: M523Player
// var fn_1_4900 temp_r28: M523Player
// var fn_1_4900 temp_r29: M523Player
// var fn_1_54A8 temp_r28: M523Player
// var fn_1_54A8 temp_r29: M523Player
// var fn_1_76E4 temp_r28: M523Player
// var fn_1_76E4 temp_r29: M523Player
// var fn_1_7898 temp_r27: M523Player
// var fn_1_7898 temp_r28: M523Player
// var fn_1_7898 temp_r29: M523Player
// var fn_1_4ED4 temp_r27: M523Player
// var fn_1_4ED4 temp_r28: M523Player
// var fn_1_4ED4 temp_r29: M523Player
// var fn_1_7C84 temp_r26: M523Player
// var fn_1_7C84 temp_r29: M523Player
// var fn_1_7C84 temp_r30: M523Player
// var fn_1_7C84 temp_r31: M523Player
// var fn_1_7C84 temp_r31_2: M523Player
// var fn_1_6800 temp_r30: M523Player
// var fn_1_427C temp_r31: M523Player
// var fn_1_8D14 temp_r30: M523Player
// var fn_1_4654 temp_r30: M523Player
// var fn_1_BB0 temp_r31: M523Player
// var fn_1_59F0 temp_r30: OMOBJ
// var fn_1_59F0 temp_r31: M523Player

typedef struct M523Light { // lbl_1_rodata_A0: Hu3DGLightCreateV arguments
    Vec unk0; // pos
    Vec unkC; // dir
    GXColor unk18;
} M523Light;

typedef struct M523Camera { // camera parameters, 0x48
    s32 unk0; // camera bit
    s32 unk4; // 1: position from angles
    f32 unk8, unkC, unk10; // fov, near, far
    Vec unk14; // pos
    Vec unk20; // up
    Vec unk2C; // target
    f32 unk38, unk3C, unk40; // angles
    f32 unk44; // distance
} M523Camera;

typedef struct M523CamMove { // camera move object data, 0xA0
    M523Camera *unk0; // camera being moved
    M523Camera unk4; // from
    M523Camera unk4C; // to
    f32 unk94; // frames
    f32 unk98; // time
    s32 unk9C; // flags (2: moving)
} M523CamMove;

typedef struct M523Beam { // a beam (UFO ray), OMOBJ::data and a doubly linked list node (lbl_1_bss_10C head, lbl_1_bss_E8 tail), GC 0x24
    struct M523Beam *unk0; // next
    struct M523Beam *unk4; // prev
    s16 unk8; // model (-1 on the list ends)
    s16 pad0A;
    Vec unkC; // pos (y = 0)
    s16 unk18; // list index
    s16 unk1A; // timer
    s16 unk1C; // state
    s16 pad1E;
    s32 unk20; // cancel
} M523Beam;

typedef struct M523Player { // OMOBJ::data, GC 0xB0 (zero filled at creation)
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // pad
    s16 unk6; // group (0: the solo player)
    s16 unk8; // difficulty
    s16 unkA;
    s32 unkC; // com
    Vec unk10; // pos
    Vec unk1C; // rot
    s32 unk28; // mode
    OMOBJ *unk2C; // its object
    s16 unk30; // seat (0: solo, 1-3: team)
    s16 unk32; // current motion
    f32 unk34; // radius
    s8 unk38; // stick x (-> input)
    s8 unk39; // stick y
    s16 pad3A;
    Vec unk3C; // velocity
    Vec unk48; // target pos
    s32 unk54; // arrived / ready
    s16 unk58; // index of the caught player (-1)
    s16 pad5A;
    Vec unk5C; // previous pos
    Vec unk68; // start pos
    Vec unk74; // previous velocity
    s16 unk80; // hit timer
    s16 unk82; // counter
    s32 unk84; // beaming
    s32 unk88; // sound
    M523Beam *unk8C; // its beam
    s16 unk90; // hooked item model
    s16 unk92; // its motion
    s16 unk94, unk96, unk98; // its joint motions
    s16 pad9A;
    s32 unk9C; // COM timer
    s16 unkA0;
    s16 unkA2; // COM state
    Vec unkA4; // COM target
} M523Player;

typedef struct M523MotParam { // per motion: solo motion index, team motion index, shift time, attr
    s16 unk0;
    s16 unk2;
    f32 unk4;
    u32 unk8;
} M523MotParam;


void fn_1_12C(s16 mode, s16 frameNo);
void fn_1_524(s16 mode, s16 frameNo);
void fn_1_634(s16 mode, s16 frameNo);
void fn_1_674(s16 mode, s16 frameNo);
void fn_1_6CC(s16 mode, s16 frameNo);
void fn_1_714(s16 mode, s16 frameNo);
void fn_1_76C(s16 mode, s16 frameNo);
void fn_1_8C0(s16 mode, s16 frameNo);
void fn_1_8D4(s16 mode, s16 frameNo);
void fn_1_BB0(void);
f32 fn_1_C88(Vec *arg0, Vec *arg1);
f32 fn_1_CEC(f32 farg0, f32 farg1);
f32 fn_1_D58(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_E58(Vec *arg0, s16 *arg1, s16 *arg2);
s32 fn_1_F34(Vec *arg0, s32 arg1);
M523Camera *fn_1_1068(M523Camera *arg0);
void fn_1_1154(M523Camera *arg0);
void fn_1_1754(M523Camera *arg0);
void fn_1_221C(OMOBJ *arg0);
OMOBJ *MgCameraMoveEntry(M523Camera *arg0, M523Camera *arg1, f32 farg0);
void fn_1_3178(M523Player *arg0, s16 arg1);
s32 fn_1_3244(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0);
f32 fn_1_3368(f32 farg0, f32 farg1, f32 farg2);
s32 fn_1_34D8(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0);
void fn_1_39DC(void);
void fn_1_3F68(OMOBJ *arg0, s16 arg1);
void fn_1_405C(void);
void fn_1_4534(OMOBJ *arg0);
void fn_1_4654(OMOBJ *arg0);
void fn_1_4858(void);
void fn_1_4900(OMOBJ *arg0);
void fn_1_4CCC(OMOBJ *arg0);
void fn_1_4ED4(OMOBJ *arg0);
void fn_1_54A8(OMOBJ *arg0);
void fn_1_58A8(OMOBJ *arg0);
void fn_1_595C(M523Player *arg0);
void fn_1_5AFC(M523Player *arg0);
void fn_1_5CB8(OMOBJ *arg0);
void fn_1_6294(OMOBJ *arg0);
void fn_1_6800(OMOBJ *arg0);
void fn_1_6DA4(OMOBJ *arg0);
s32 fn_1_7358(M523Player *arg0);
s32 fn_1_73D4(M523Player *arg0);
void fn_1_7488(void);
void fn_1_76E4(OMOBJ *arg0);
void fn_1_7898(OMOBJ *arg0);
void fn_1_7C84(OMOBJ *arg0);
f32 fn_1_85A8(M523Player *arg0);
void fn_1_8874(M523Player *arg0);
void fn_1_8A80(M523Player *arg0, s16 arg1);
void fn_1_8B60(M523Player *arg0, s32 arg1);
s16 fn_1_8D14(M523Player *arg0);
f32 fn_1_8DF0(M523Player *arg0);
s32 fn_1_90EC(M523Player *arg0);
s16 fn_1_9218(void);
void fn_1_92F4(M523Player *arg0);
void fn_1_9440(M523Player *arg0);
void fn_1_9574(void);
M523Beam *fn_1_9798(Vec *arg0);
void fn_1_98E8(M523Beam *arg0);
void fn_1_992C(void);
void fn_1_962C(OMOBJ *arg0);
void fn_1_9978(HU3DMODEL *modelP, Mtx mtx);
void ObjectSetup(void);
void fn_1_12C(s16 mode, s16 frameNo);
void fn_1_524(s16 mode, s16 frameNo);
void fn_1_634(s16 mode, s16 frameNo);
void fn_1_674(s16 mode, s16 frameNo);
void fn_1_6CC(s16 mode, s16 frameNo);
void fn_1_714(s16 mode, s16 frameNo);
void fn_1_76C(s16 mode, s16 frameNo);
void fn_1_8C0(s16 mode, s16 frameNo);
void fn_1_8D4(s16 mode, s16 frameNo);
void fn_1_8E8(omObjData *arg0);
void fn_1_BB0(void);
f32 fn_1_C88(Vec *arg0, Vec *arg1);
f32 fn_1_CEC(f32 farg0, f32 farg1);
f32 fn_1_D58(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3);
void fn_1_E58(Vec *arg0, s16 *arg1, s16 *arg2);
s32 fn_1_F34(Vec *arg0, s32 arg1);
M523Camera *fn_1_1068(M523Camera *arg0);
void fn_1_1154(M523Camera *arg0);
void fn_1_1754(M523Camera *arg0);
void fn_1_221C(omObjData *arg0);
omObjData *MgCameraMoveEntry(M523Camera *arg0, M523Camera *arg1, f32 farg0);
void fn_1_3178(M523Player *arg0, s16 arg1);
s32 fn_1_3244(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0);
f32 fn_1_3368(f32 farg0, f32 farg1, f32 farg2);
s32 fn_1_34D8(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0);
void fn_1_39DC(void);
void fn_1_3F68(omObjData *arg0, s16 arg1);
void fn_1_405C(void);
void fn_1_4534(omObjData *arg0);
void fn_1_4654(omObjData *arg0);
void fn_1_4858(void);
void fn_1_4900(omObjData *arg0);
void fn_1_4CCC(omObjData *arg0);
void fn_1_4ED4(omObjData *arg0);
void fn_1_54A8(omObjData *arg0);
void fn_1_58A8(omObjData *arg0);
void fn_1_595C(M523Player *arg0);
void fn_1_5AFC(M523Player *arg0);
void fn_1_5CB8(omObjData *arg0);
void fn_1_6294(omObjData *arg0);
void fn_1_6800(omObjData *arg0);
void fn_1_6DA4(omObjData *arg0);
s32 fn_1_7358(M523Player *arg0);
s32 fn_1_73D4(M523Player *arg0);
void fn_1_7488(void);
void fn_1_76E4(omObjData *arg0);
void fn_1_7898(omObjData *arg0);
void fn_1_7C84(omObjData *arg0);
f32 fn_1_85A8(M523Player *arg0);
void fn_1_8874(M523Player *arg0);
void fn_1_8A80(M523Player *arg0, s16 arg1);
void fn_1_8B60(M523Player *arg0, s32 arg1);
s16 fn_1_8D14(M523Player *arg0);
f32 fn_1_8DF0(M523Player *arg0);
s32 fn_1_90EC(M523Player *arg0);
s16 fn_1_9218(void);
void fn_1_92F4(M523Player *arg0);
void fn_1_9440(M523Player *arg0);
void fn_1_9574(void);
void fn_1_962C(omObjData *arg0);
M523Beam *fn_1_9798(Vec *arg0);
void fn_1_98E8(M523Beam *arg0);
void fn_1_992C(void);
void fn_1_9978(HU3DMODEL *modelP, Mtx mtx);

M523Camera lbl_1_data_6C = {
    1,
    1,
    20.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 190.0f, 72.0f },
    -20.0f,
    0.0f,
    0.0f,
    1000.0f,
};
M523Camera lbl_1_data_B4 = {
    1,
    1,
    20.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 259.0f, 72.0f },
    -42.5f,
    0.0f,
    0.0f,
    4886.4f,
};
M523Camera lbl_1_data_FC = {
    1,
    1,
    20.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 300.0f, 72.0f },
    -30.0f,
    0.0f,
    0.0f,
    2800.0f,
};
M523Camera lbl_1_data_144 = {
    1,
    1,
    20.0f,
    20.0f,
    8000.0f,
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 400.0f, 72.0f },
    -8.6f,
    0.0f,
    0.0f,
    2800.0f,
};
static Vec lbl_1_data_18C = { 0.0f, 100000.0f, 1.0f };
static Vec lbl_1_data_198 = { 0.0f, 1.0f, 0.0f };
static Vec lbl_1_data_1A4 = { 0.0f, 0.0f, 0.0f };
MGSEQ_PARAM lbl_1_data_1BC = {
    0x1E,
    2,
    fn_1_12C,
    fn_1_524,
    fn_1_634,
    fn_1_6CC,
    fn_1_714,
    fn_1_76C,
    fn_1_8C0,
    NULL,
    fn_1_8D4,
};
Vec lbl_1_data_1E4[3] = {
    { 0.0f, 0.0f, 600.0f },
    { -485.0f, 0.0f, -342.0f },
    { 570.0f, 0.0f, -120.0f },
};
omObjData *lbl_1_bss_0;
omObjData *lbl_1_bss_4;
static s32 lbl_1_bss_8;
static s32 lbl_1_bss_C;
static s32 lbl_1_bss_10;
static s32 lbl_1_bss_14;
static s32 lbl_1_bss_18;
static s32 lbl_1_bss_1C;
static s32 lbl_1_bss_20;
static s32 lbl_1_bss_24[8];
M523Camera lbl_1_bss_44;
static s16 lbl_1_bss_8C[6];
static s16 lbl_1_bss_E0;
static HUPROCESS *lbl_1_bss_E4;
static u32 lbl_1_data_208[9] = {
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 27),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 25),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 81),
    DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
    0,
};
static u32 lbl_1_data_22C[7] = { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 77), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 23), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 47), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 63), 0, 0x80005 };
Vec lbl_1_data_248[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, -300.0f },
    { -350.0f, 0.0f, 200.0f },
    { 350.0f, 0.0f, 200.0f },
};
Vec lbl_1_data_278[4] = {
    { 0.0f, 0.0f, 150.0f },
    { -350.0f, 0.0f, -300.0f },
    { 0.0f, 0.0f, -300.0f },
    { 350.0f, 0.0f, -300.0f },
};
Vec lbl_1_data_2A8[3] = {
    { 0.0f, 0.0f, 200.0f },
    { -350.0f, 0.0f, -250.0f },
    { 350.0f, 0.0f, -250.0f },
};
M523MotParam lbl_1_data_2CC[0xB] = {
    { 0, 0, 10.0f, 0x40000001 },
    { 1, -1, 10.0f, 0x40000001 },
    { 2, -1, 10.0f, 0x40000001 },
    { 3, -1, 10.0f, 0 },
    { 4, -1, 10.0f, 0x40000001 },
    { 5, -1, 10.0f, 0x40000001 },
    { 6, -1, 10.0f, 0x40000001 },
    { -1, 1, 10.0f, 0x40000001 },
    { 7, 2, 10.0f, 0 },
    { -1, 3, 10.0f, 0x40000001 },
    { -1, 4, 10.0f, 0 },
};
char lbl_1_data_350[0x10] = "itemhook_ufo";
static char lbl_1_data_394[6] = "cyl10";
M523Beam lbl_1_bss_E8;
M523Beam lbl_1_bss_10C;
static s32 lbl_1_bss_130[3];
M523Player *lbl_1_bss_13C;
M523Player *lbl_1_bss_140[4];
Vec lbl_1_bss_150[0xA];
static s32 lbl_1_rodata_8C[5] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 0), DATA_MAKE_NUM(DATADIR_MP5_M523, 1), DATA_MAKE_NUM(DATADIR_MP5_M523, 2), DATA_MAKE_NUM(DATADIR_MP5_M523, 5), DATA_MAKE_NUM(DATADIR_MP5_M523, 3) }; /* const */
M523Light lbl_1_rodata_A0 = {
    { -800.0f, 1500.0f, 800.0f },
    { 800.0f, -1500.0f, -800.0f },
    { 0xFF, 0xFF, 0xFF, 0xFF },
}; /* const */
static s16 lbl_1_rodata_F0[0xE] = { 1, 1, 0, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0 }; /* const */
static s32 lbl_1_rodata_10C[3] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 6), DATA_MAKE_NUM(DATADIR_MP5_M523, 7), DATA_MAKE_NUM(DATADIR_MP5_M523, 8) }; /* const */
static s32 lbl_1_rodata_118[3] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 9), DATA_MAKE_NUM(DATADIR_MP5_M523, 10), DATA_MAKE_NUM(DATADIR_MP5_M523, 11) }; /* const */
static s32 lbl_1_rodata_124[3] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 12), DATA_MAKE_NUM(DATADIR_MP5_M523, 13), DATA_MAKE_NUM(DATADIR_MP5_M523, 14) }; /* const */
static s32 lbl_1_rodata_130[3] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 15), DATA_MAKE_NUM(DATADIR_MP5_M523, 16), DATA_MAKE_NUM(DATADIR_MP5_M523, 17) }; /* const */
static s32 lbl_1_rodata_13C[3] = { DATA_MAKE_NUM(DATADIR_MP5_M523, 21), DATA_MAKE_NUM(DATADIR_MP5_M523, 22), DATA_MAKE_NUM(DATADIR_MP5_M523, 23) }; /* const */
s32 lbl_1_rodata_240[4] = { 0, 0, 0x23, 0x19 };     /* const */
s32 lbl_1_rodata_260[4] = { 0xA, 0xF, 0x14, 0x14 }; /* const */



void ObjectSetup(void) {
    lbl_1_bss_E4 = omInitObjMan(0xC8, 0x1000);
    lbl_1_bss_E0 = -1;
    omGameSysInit(lbl_1_bss_E4);
    MgSeqCreatePrio(&lbl_1_data_1BC, 0x7D0);
    MgSeqModeHookAdd(4, fn_1_674);
    MgSeqModeDelaySet(2, 0x12C);
    MgSeqModeDelaySet(7, 0x12C);
}

void fn_1_12C(s16 mode, s16 frameNo) {
    s16 sp8[3];
    s16 temp_r30;
    s16 temp_r3;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    var_r31 = 0;
loop_2:
    if (var_r31 < 5) {
        lbl_1_bss_8C[var_r31] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_8C[var_r31], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(lbl_1_bss_8C[var_r31], 0x40000001U);
        Hu3DModelPosSet(lbl_1_bss_8C[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_8C[var_r31], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_8C[var_r31], 0);
        var_r31 += 1;
        goto loop_2;
    }
    Hu3DModelLayerSet(lbl_1_bss_8C[1], 3);
    Hu3DMotionSpeedSet(lbl_1_bss_8C[3], 0.4f);
    temp_r30 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M523, 4), MEMORY_DEFAULT_NUM, HEAP_DATA));
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 3) {
        if (var_r31_2 == 0) {
            sp8[var_r31_2] = temp_r30;
        } else {
            sp8[var_r31_2] = Hu3DModelLink(temp_r30);
        }
        Hu3DModelPosSetV(sp8[var_r31_2], &lbl_1_data_1E4[var_r31_2]);
        Hu3DModelLayerSet(sp8[var_r31_2], 2);
        var_r31_2 += 1;
        goto loop_8;
    }
    fn_1_1068(&lbl_1_data_6C);
    lbl_1_bss_44 = lbl_1_data_6C;
    temp_r3 = Hu3DGLightCreateV(&lbl_1_rodata_A0.unk0, &lbl_1_rodata_A0.unkC, &lbl_1_rodata_A0.unk18);
    Hu3DGLightStaticSet(temp_r3, 1);
    Hu3DGLightInfinitytSet(temp_r3);
    Hu3DShadowCreate(1.0f, lbl_1_data_B4.unkC, 100000.0f);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_data_18C, &lbl_1_data_198, &lbl_1_data_1A4);
    Hu3DModelShadowMapSet(lbl_1_bss_8C[0]);
    Hu3DModelShadowMapSet(lbl_1_bss_8C[1]);
    var_r31_3 = 0;
loop_11:
    if (var_r31_3 < 3) {
        Hu3DModelShadowMapSet(sp8[var_r31_3]);
        var_r31_3 += 1;
        goto loop_11;
    }
    fn_1_39DC();
    lbl_1_bss_8 = -1;
    *lbl_1_bss_24 = 0xA;
    lbl_1_bss_20 = 0;
    Hu3DModelAttrSet(lbl_1_bss_8C[0], 0x40000002U);
    Hu3DModelAttrReset(lbl_1_bss_8C[0], 0x40000001U);
    omAddObjEx(lbl_1_bss_E4, 0x1300, 0U, 0U, -1, fn_1_8E8);
    lbl_1_bss_C = HuAudFXPlay(0x751);
    lbl_1_bss_18 = 0;
    lbl_1_bss_14 = 0;
    MgSeqModeNext();
}

void fn_1_524(s16 mode, s16 frameNo) {
    s16 sp8;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 == 0x1E) {
        HuAudFXPlay(0x74A);
    }
    switch ((s32) lbl_1_bss_14) {                   /* irregular */
    case 3:
        lbl_1_bss_4 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_B4, 30.0f);
        lbl_1_bss_14 = 4;
        return;
    case 4:
        if ((s32) (((M523CamMove *)lbl_1_bss_4->data)->unk9C & 2) != 0) {
            var_r31 = 1;
        } else {
            var_r31 = 0;
        }
        if (var_r31 == 0) {
            omDelObjEx(lbl_1_bss_E4, lbl_1_bss_4);
            MgSeqModeNext();
        }
        return;
    }
}

void fn_1_634(s16 mode, s16 frameNo) {
    s16 sp8;

    sp8 = frameNo;
    if (sp8 == 0) {
        lbl_1_bss_10 = HuAudSStreamPlay(0x34);
    }
}

void fn_1_674(s16 mode, s16 frameNo) {
    lbl_1_bss_1C = 0;
    fn_1_405C();
    omAddObjEx(lbl_1_bss_E4, 0x1100, 0U, 0U, -1, fn_1_7C84);
}

void fn_1_6CC(s16 mode, s16 frameNo) {
    if ((s32) lbl_1_bss_13C->unk28 == 2) {
        lbl_1_bss_1C = 1;
        MgSeqModeNext();
    }
}

void fn_1_714(s16 mode, s16 frameNo) {
    s16 sp8;

    sp8 = frameNo;
    lbl_1_bss_18 = 2;
    if (sp8 == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_10, 0x64);
        fn_1_BB0();
        fn_1_4858();
    }
}

void fn_1_76C(s16 mode, s16 frameNo) {
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    var_r30 = 1;
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        if ((s32) lbl_1_bss_140[var_r31]->unk54 == 0) {
            var_r30 = 0;
        }
        var_r31 += 1;
        goto loop_4;
    }
    if ((omObjData *) lbl_1_bss_0 == NULL) {
        if (var_r30 != 0) {
            if ((s32) lbl_1_bss_1C == 0) {
                lbl_1_bss_0 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_FC, 30.0f);
                return;
            }
            lbl_1_bss_0 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_144, 30.0f);
        }
    } else {
        if ((s32) (((M523CamMove *)lbl_1_bss_0->data)->unk9C & 2) != 0) {
            var_r29 = 1;
        } else {
            var_r29 = 0;
        }
        if (var_r29 == 0) {
            omDelObjEx(lbl_1_bss_E4, lbl_1_bss_0);
            MgSeqModeNext();
        }
    }
}

void fn_1_8C0(s16 mode, s16 frameNo) {
    lbl_1_bss_18 = 4;
}

void fn_1_8D4(s16 mode, s16 frameNo) {
    lbl_1_bss_18 = 5;
}

void fn_1_8E8(omObjData *arg0) {
    s32 var_r30;
    s32 var_r31;

    if ((s32) lbl_1_bss_18 != 5) {
        HuAudFXVolSet(lbl_1_bss_C, (s16) (127.0f - (63.0f * ((lbl_1_bss_44.unk44 - lbl_1_data_6C.unk44) / (lbl_1_data_B4.unk44 - lbl_1_data_6C.unk44)))));
        var_r30 = 0;
        var_r31 = 0;
loop_7:
        if (var_r31 < 4) {
            if (((s16) lbl_1_bss_140[var_r31]->unk6 != 0) && ((s32) lbl_1_bss_140[var_r31]->unk28 != 6) && (VECMag(&lbl_1_bss_140[var_r31]->unk3C) > 0.1f)) {
                var_r30 = 1;
            }
            var_r31 += 1;
            goto loop_7;
        }
        if (var_r30 != 0) {
            if ((s32) lbl_1_bss_8 == -1) {
                lbl_1_bss_8 = HuAudFXPlay(0x74B);
            }
        } else if ((s32) lbl_1_bss_8 != -1) {
            HuAudFXStop(lbl_1_bss_8);
            lbl_1_bss_8 = -1;
        }
        if ((s32) lbl_1_bss_20 != 0) {
            if (Hu3DMotionEndCheck(*lbl_1_bss_8C) != 0) {
                Hu3DModelAttrSet(*lbl_1_bss_8C, 0x40000002U);
                *lbl_1_bss_24 = frandmod(0x78U) + 0x78;
                lbl_1_bss_20 = 0;
            }
        } else if ((s32) *lbl_1_bss_24 > 0) {
            *lbl_1_bss_24 -= 1;
            if ((s32) *lbl_1_bss_24 == 0) {
                HuAudFXPlay(0x752);
                Hu3DModelAttrReset(*lbl_1_bss_8C, 0x40000002U);
                Hu3DMotionTimeSet(*lbl_1_bss_8C, 0.0f);
                lbl_1_bss_20 = 1;
            }
        }
    }
}

void fn_1_BB0(void) {
    s16 sp8[4];
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        sp8[var_r31] = -1;
        if ((s32) lbl_1_bss_1C == (s16) lbl_1_bss_140[var_r31]->unk6) {
            sp8[var_r31] = lbl_1_bss_140[var_r31]->unk2;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[var_r31].coin_win = 0xA;
            }
        }
        var_r31 += 1;
        goto loop_5;
    }
    MgSeqWinnerSet(sp8[0], sp8[1], sp8[2], sp8[3]);
}

f32 fn_1_C88(Vec *arg0, Vec *arg1) {
    Vec sp10;
    Vec *spC;
    Vec *sp8;

    sp8 = arg0;
    spC = arg1;
    VECSubtract(spC, sp8, &sp10);
    return (f32) (180.0 * (atan2((f64) sp10.x, (f64) sp10.z) / 3.141592653589793));
}

f32 fn_1_CEC(f32 farg0, f32 farg1) {
    f32 var_f31;

    var_f31 = farg1 - farg0;
    if (var_f31 < -180.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    return var_f31;
}

f32 fn_1_D58(Vec *arg0, Vec *arg1, Vec *arg2, Vec *arg3) {
    Vec sp38;
    Vec sp2C;
    Vec sp20;
    Vec sp14;
    Vec *sp10;
    Vec *spC;
    Vec *sp8;
    f32 temp_f30;
    f32 temp_f31;

    sp8 = arg0;
    spC = arg2;
    sp10 = arg3;
    VECSubtract(spC, arg1, &sp38);
    VECSubtract(sp8, arg1, &sp2C);
    temp_f30 = VECSquareMag(&sp38);
    temp_f31 = VECDotProduct(&sp38, &sp2C) / temp_f30;
    if ((temp_f31 < 0.0f) || (temp_f31 > 1.0f)) {
        return -1.0f;
    }
    VECScale(&sp38, &sp20, temp_f31);
    VECAdd(arg1, &sp20, sp10);
    VECSubtract(&sp20, &sp2C, &sp14);
    return VECMag(&sp14);
}

void fn_1_E58(Vec *arg0, s16 *arg1, s16 *arg2) {
    Vec spC;
    Vec *sp8;

    sp8 = arg0;
    Hu3D3Dto2D(arg0, (s16) lbl_1_bss_44.unk0, &spC);
    *arg2 = (s16) (48.0f + (32.0f * (spC.x / 576.0f)));
    *arg1 = (s16) (96.0f + (31.0f * (spC.y / 480.0f)));
}

s32 fn_1_F34(Vec *arg0, s32 arg1) {
    Vec sp10;
    s16 spC;
    Vec *sp8;

    sp8 = arg0;
    spC = (s16) arg1;
    Hu3D3Dto2D(arg0, (s16) lbl_1_bss_44.unk0, &sp10);
    return HuAudFXPlayVolPan((s32) spC, (s16) (96.0f + (31.0f * (sp10.y / 480.0f))), (s16) (48.0f + (32.0f * (sp10.x / 576.0f))));
}


M523Camera *fn_1_1068(M523Camera *arg0) {
    M523Camera *temp_r3;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M523Camera), MEMORY_DEFAULT_NUM);
    *temp_r3 = *arg0;
    Hu3DCameraCreate(arg0->unk0);
    Hu3DCameraViewportSet(arg0->unk0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(arg0->unk0, arg0->unk8, arg0->unkC, arg0->unk10, 1.2f);
    fn_1_1154(arg0);
    return (M523Camera *) temp_r3;
}

void fn_1_1154(M523Camera *arg0) {
    if ((s32) arg0->unk4 == 1) {
        fn_1_1754(arg0);
    }
    Hu3DCameraPosSetV(arg0->unk0, &arg0->unk14, &arg0->unk20, &arg0->unk2C);
}





void fn_1_1754(M523Camera *arg0) {
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


void fn_1_221C(omObjData *arg0) {
    M523Camera *temp_r30;
    f32 temp_f31;
    M523CamMove *temp_r28;
    M523Camera *temp_r29;
    M523Camera *temp_r31;

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
        fn_1_1154(temp_r30);
    }
}

omObjData *MgCameraMoveEntry(M523Camera *arg0, M523Camera *arg1, f32 farg0) {
    f32 sp8;
    omObjData *temp_r29;
    M523CamMove *temp_r31;

    sp8 = farg0;
    if ((s32) arg0->unk0 != (s32) arg1->unk0) {
        OSReport("MgCameraMoveEntry : Camera Number Different\n");
        return NULL;
    }
    temp_r29 = omAddObjEx(lbl_1_bss_E4, 0x2000, 0U, 0U, -1, fn_1_221C);
    temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M523CamMove), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r29->data;
    temp_r31->unk94 = sp8;
    temp_r31->unk98 = 0.0f;
    temp_r31->unk0 = arg0;
    temp_r31->unk4 = *arg0;
    temp_r31->unk4C = *arg1;
    temp_r31->unk9C = 3;
    if ((s32) arg0->unk4 == 1) {
        fn_1_1754(&temp_r31->unk4);
        fn_1_1754(&temp_r31->unk4C);
    }
    return temp_r29;
}
























void fn_1_3178(M523Player *arg0, s16 arg1) {
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

s32 fn_1_3244(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0) {
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

f32 fn_1_3368(f32 farg0, f32 farg1, f32 farg2) {
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

s32 fn_1_34D8(Vec *arg0, Vec *arg1, Vec *arg2, f32 farg0) {
    Vec sp20;
    Vec sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f1;
    f32 temp_f30;
    f32 temp_f31;

    sp8 = arg1->x;
    spC = arg1->y;
    sp10 = arg1->z;
loop_1:
    VECSubtract(arg1, arg0, &sp20);
    if (VECMag(&sp20) == 0.0f) {
        return 0;
    }
    VECSubtract(arg1, arg2, &sp14);
    temp_f1 = VECMag(&sp14);
    if (temp_f1 < farg0) {
        if (temp_f1 != 0.0f) {
            VECNormalize(&sp14, &sp14);
            VECScale(&sp14, &sp14, farg0);
            VECAdd(arg2, &sp14, arg1);
        } else {
            *arg1 = *arg0;
        }
        VECSubtract(arg1, arg0, &sp14);
        if (VECMag(&sp14) < 0.001f) {
            temp_f31 = VECMag(&sp20);
            temp_f30 = (f32) (180.0 * (atan2((f64) sp14.z, (f64) sp14.x) / 3.141592653589793)) + 30.0f;
            sp20.x = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
            sp20.z = (f32) ((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
            VECAdd(arg0, &sp20, arg1);
            goto loop_1;
        }
        return 1;
    }
    return 0;
}





void fn_1_39DC(void) {
    omObjData *var_r27;
    s16 temp_r0;
    s16 temp_r24;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 var_r25;
    s16 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    M523Player *temp_r31;

    var_r25 = 1;
    var_r28 = 0;
loop_8:
    if (var_r28 < 4) {
        temp_r24 = GWPlayerCfg[var_r28].group;
        if (temp_r24 == 0) {
            var_r27 = omAddObjEx(lbl_1_bss_E4, (s16) (temp_r24 + 0x1000), 3U, 8U, -1, fn_1_4900);
        } else {
            var_r27 = omAddObjEx(lbl_1_bss_E4, (s16) (temp_r24 + 0x1000), 3U, 8U, -1, fn_1_5CB8);
        }
        var_r27->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M523Player), MEMORY_DEFAULT_NUM);
        memset(var_r27->data, 0, sizeof(M523Player));
        temp_r31 = var_r27->data;
        lbl_1_bss_140[var_r28] = (M523Player *) temp_r31;
        fn_1_3178((M523Player *) temp_r31, var_r28);
        temp_r31->unk2C = var_r27;
        temp_r31->unk58 = -1;
        temp_r31->unk8C = 0;
        temp_r31->unk80 = 0;
        temp_r31->unk82 = 0;
        temp_r31->unk84 = 0;
        temp_r31->unk88 = -1;
        temp_r31->unk54 = 0;
        temp_r31->unk9C = 0;
        temp_r31->unk74.z = 0.0f;
        temp_r31->unk74.y = 0.0f;
        temp_r31->unk74.x = 0.0f;
        temp_r31->unk3C.z = 0.0f;
        temp_r31->unk3C.y = 0.0f;
        temp_r31->unk3C.x = 0.0f;
        temp_r31->unkA4.z = 0.0f;
        temp_r31->unkA4.y = 0.0f;
        temp_r31->unkA4.x = 0.0f;
        if ((s16) temp_r31->unk6 == 0) {
            lbl_1_bss_13C = (M523Player *) temp_r31;
            temp_r31->unk30 = 0;
            temp_r31->unk34 = 50.0f;
            temp_r31->unk10.x = (f32) lbl_1_data_248[1].x;
            temp_r31->unk10.y = (f32) lbl_1_data_248[1].y;
            temp_r31->unk10.z = (f32) lbl_1_data_248[1].z;
            temp_r31->unk28 = 0xE;
            temp_r31->unkA2 = 0;
            temp_r31->unk9C = 0;
            temp_r3 = CharModelMotListCreate(temp_r31->unk2, 2, lbl_1_data_208, var_r27->motion);
            var_r27->model[0] = temp_r3;
            CharMotionSet(temp_r31->unk2, *var_r27->motion);
            Hu3DModelLayerSet(temp_r3, 4);
            Hu3DModelShadowSet(temp_r3);
        } else {
            omSetStatBit(var_r27, 0x100U);
            temp_r31->unk30 = var_r25;
            var_r25 += 1;
            temp_r31->unk34 = 150.0f;
            fn_1_5AFC((M523Player *) temp_r31);
            temp_r31->unk68.x = (f32) temp_r31->unk10.x;
            temp_r31->unk68.y = (f32) temp_r31->unk10.y;
            temp_r31->unk68.z = (f32) temp_r31->unk10.z;
            temp_r31->unk28 = 0x13;
            temp_r31->unkA2 = 0;
            temp_r31->unk9C = 0x1E;
            temp_r3_2 = CharModelMotListCreate(temp_r31->unk2, 2, lbl_1_data_22C, var_r27->motion);
            var_r27->model[0] = temp_r3_2;
            CharMotionSet(temp_r31->unk2, *var_r27->motion);
            Hu3DModelLayerSet(temp_r3_2, 4);
            Hu3DModelShadowSet(temp_r3_2);
            CharMotionVoiceOnSet(temp_r31->unk2, (s16) lbl_1_data_22C[4], 0);
            temp_r0 = lbl_1_rodata_F0[temp_r31->unk2];
            temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_10C[temp_r0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelAttrSet(temp_r3_3, 0x40000001U);
            var_r27->model[1] = temp_r3_3;
            Hu3DModelLayerSet(temp_r3_3, 4);
            Hu3DModelShadowSet(temp_r3_3);
            Hu3DModelHookSet(temp_r3_3, lbl_1_data_350, var_r27->model[0]);
            temp_r31->unk90 = temp_r3_3;
            temp_r31->unk92 = Hu3DMotionIDGet(temp_r3_3);
            temp_r31->unk94 = Hu3DJointMotion(temp_r3_3, HuDataSelHeapReadNum(lbl_1_rodata_118[temp_r0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->unk96 = Hu3DJointMotion(temp_r3_3, HuDataSelHeapReadNum(lbl_1_rodata_124[temp_r0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->unk98 = Hu3DJointMotion(temp_r3_3, HuDataSelHeapReadNum(lbl_1_rodata_130[temp_r0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelPosSetV(var_r27->model[1], &temp_r31->unk10);
            Hu3DModelRotSetV(var_r27->model[1], &temp_r31->unk1C);
            temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M523, 18), MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelAttrSet(temp_r3_4, 0x40000002U);
            var_r27->model[2] = temp_r3_4;
            Hu3DModelLayerSet(temp_r3_4, 4);
            Hu3DModelPosSetV(var_r27->model[2], &temp_r31->unk10);
            Hu3DModelRotSetV(var_r27->model[2], &temp_r31->unk1C);
        }
        temp_r31->unk32 = -1;
        fn_1_3F68(var_r27, 0);
        var_r28 += 1;
        goto loop_8;
    }
    CharEffectLayerSet(5);
    fn_1_9574();
    var_r28_2 = 0;
loop_11:
    if (var_r28_2 < 3) {
        lbl_1_bss_130[var_r28_2] = 0;
        var_r28_2 += 1;
        goto loop_11;
    }
    var_r28_3 = 0;
loop_14:
    if (var_r28_3 < 0xA) {
        lbl_1_bss_150[var_r28_3].x = 0.0f;
        lbl_1_bss_150[var_r28_3].y = 0.0f;
        lbl_1_bss_150[var_r28_3].z = 0.0f;
        var_r28_3 += 1;
        goto loop_14;
    }
}

void fn_1_3F68(omObjData *arg0, s16 arg1) {
    s16 var_r28;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    if ((s16) temp_r31->unk32 != arg1) {
        if ((s16) temp_r31->unk30 == 0) {
            var_r28 = lbl_1_data_2CC[arg1].unk0;
        } else {
            var_r28 = lbl_1_data_2CC[arg1].unk2;
        }
        CharMotionShiftSet(temp_r31->unk2, arg0->motion[var_r28], 0.0f, lbl_1_data_2CC[arg1].unk4, lbl_1_data_2CC[arg1].unk8);
        temp_r31->unk32 = arg1;
    }
}

void fn_1_405C(void) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        lbl_1_bss_140[var_r31]->unk28 = 1;
        lbl_1_bss_140[var_r31]->unk54 = 0;
        var_r31 += 1;
        goto loop_2;
    }
}






void fn_1_4534(omObjData *arg0) {
    if (Hu3DMotionEndCheck(*arg0->model) != 0) {
        Hu3DModelKill(*arg0->model);
        omDelObjEx(lbl_1_bss_E4, arg0);
    }
}


void fn_1_4654(omObjData *arg0) {
    M523Player *temp_r30;

    if (Hu3DMotionEndCheck(*arg0->model) != 0) {
        lbl_1_bss_130[arg0->work[1]] = 0;
        Hu3DModelKill(*arg0->model);
        omDelObjEx(lbl_1_bss_E4, arg0);
    }
    temp_r30 = lbl_1_bss_140[arg0->work[0]];
    omSetTra(arg0, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
}


void fn_1_4858(void) {
    M523Player *temp_r4;
    Vec *temp_r5;
    s32 var_r31;

    if ((s32) lbl_1_bss_1C == 0) {
        var_r31 = 0;
loop_3:
        if (var_r31 < 4) {
            temp_r5 = &lbl_1_data_278[lbl_1_bss_140[var_r31]->unk30];
            temp_r4 = lbl_1_bss_140[var_r31];
            temp_r4->unk48.x = temp_r5->x;
            temp_r4->unk48.y = temp_r5->y;
            temp_r4->unk48.z = temp_r5->z;
            var_r31 += 1;
            goto loop_3;
        }
        return;
    }
    fn_1_7488();
}

void fn_1_4900(omObjData *arg0) {
    Vec sp8;
    Vec *temp_r4;
    s16 var_r22;
    s16 var_r23;
    s16 var_r24;
    s16 var_r25;
    s32 temp_r0;
    u32 temp_r3;
    M523Player *temp_r26;
    M523Player *temp_r27;
    M523Player *temp_r28;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 14:
        arg0->work[0] += 1;
        if ((s32) lbl_1_bss_14 == 1) {
            temp_r29 = arg0->data;
            if ((s16) temp_r29->unk32 != 4) {
                if ((s16) temp_r29->unk30 == 0) {
                    var_r25 = lbl_1_data_2CC[4].unk0;
                } else {
                    var_r25 = lbl_1_data_2CC[4].unk2;
                }
                CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r25], 0.0f, lbl_1_data_2CC[4].unk4, lbl_1_data_2CC[4].unk8);
                temp_r29->unk32 = 4;
            }
            temp_r31->unk28 = 0xF;
        }
        break;
    case 15:
        CharMotionSpeedSet(temp_r31->unk2, 3.0f);
        if ((s32) lbl_1_bss_14 == 2) {
            temp_r28 = arg0->data;
            if ((s16) temp_r28->unk32 != 3) {
                if ((s16) temp_r28->unk30 == 0) {
                    var_r24 = lbl_1_data_2CC[3].unk0;
                } else {
                    var_r24 = lbl_1_data_2CC[3].unk2;
                }
                CharMotionShiftSet(temp_r28->unk2, arg0->motion[var_r24], 0.0f, lbl_1_data_2CC[3].unk4, lbl_1_data_2CC[3].unk8);
                temp_r28->unk32 = 3;
            }
            temp_r31->unk28 = 0x10;
            arg0->work[0] = 0;
        }
        break;
    case 16:
        temp_r3 = arg0->work[0];
        arg0->work[0] = temp_r3 + 1;
        if (temp_r3 >= 0x19U) {
            temp_r27 = arg0->data;
            if ((s16) temp_r27->unk32 != 2) {
                if ((s16) temp_r27->unk30 == 0) {
                    var_r23 = lbl_1_data_2CC[2].unk0;
                } else {
                    var_r23 = lbl_1_data_2CC[2].unk2;
                }
                CharMotionShiftSet(temp_r27->unk2, arg0->motion[var_r23], 0.0f, lbl_1_data_2CC[2].unk4, lbl_1_data_2CC[2].unk8);
                temp_r27->unk32 = 2;
            }
            temp_r4 = &lbl_1_data_248[temp_r31->unk30];
            temp_r31->unk48.x = (f32) temp_r4->x;
            temp_r31->unk48.y = (f32) temp_r4->y;
            temp_r31->unk48.z = (f32) temp_r4->z;
            temp_r31->unk28 = 0x11;
            lbl_1_bss_14 = 3;
        }
        break;
    case 17:
        VECSubtract(&temp_r31->unk48, &temp_r31->unk10, &sp8);
        if (VECMag(&sp8) < 15.0f) {
            temp_r31->unk10.x = (f32) temp_r31->unk48.x;
            temp_r31->unk10.y = (f32) temp_r31->unk48.y;
            temp_r31->unk10.z = (f32) temp_r31->unk48.z;
            temp_r31->unk28 = 0x12;
            temp_r26 = arg0->data;
            if ((s16) temp_r26->unk32 != 6) {
                if ((s16) temp_r26->unk30 == 0) {
                    var_r22 = lbl_1_data_2CC[6].unk0;
                } else {
                    var_r22 = lbl_1_data_2CC[6].unk2;
                }
                CharMotionShiftSet(temp_r26->unk2, arg0->motion[var_r22], 0.0f, lbl_1_data_2CC[6].unk4, lbl_1_data_2CC[6].unk8);
                temp_r26->unk32 = 6;
            }
            arg0->func = fn_1_4CCC;
        } else {
            VECNormalize(&sp8, &sp8);
            VECScale(&sp8, &sp8, 15.0f);
            VECAdd(&temp_r31->unk10, &sp8, &temp_r31->unk10);
        }
        break;
    }
    omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
}

void fn_1_4CCC(omObjData *arg0) {
    Vec spC;
    Vec sp18;
    s16 spA;
    s16 sp8;
    M523Player *temp_r4;
    s16 var_r28;
    s32 temp_r0;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    fn_1_E58(&temp_r31->unk10, &spA, &sp8);
    CharModelVoicePanSet(temp_r31->unk2, sp8);
    CharModelVoiceVolSet(temp_r31->unk2, spA);
    temp_r31->unk3C.z = 0.0f;
    temp_r31->unk3C.x = 0.0f;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 1:
        if ((s32) lbl_1_bss_18 == 2) {
            temp_r29 = arg0->data;
            if ((s16) temp_r29->unk32 != 2) {
                if ((s16) temp_r29->unk30 == 0) {
                    var_r28 = lbl_1_data_2CC[2].unk0;
                } else {
                    var_r28 = lbl_1_data_2CC[2].unk2;
                }
                CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r28], 0.0f, lbl_1_data_2CC[2].unk4, lbl_1_data_2CC[2].unk8);
                temp_r29->unk32 = 2;
            }
            arg0->func = fn_1_54A8;
            return;
        }
        fn_1_4ED4(arg0);
    default:
block_14:
        omSetRot(arg0, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
        omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
        return;
    case 2:
        temp_r4 = lbl_1_bss_140[temp_r31->unk58];
        sp18.x = temp_r4->unk10.x;
        sp18.y = temp_r4->unk10.y;
        sp18.z = temp_r4->unk10.z;
        sp18.y = 200.0f;
        temp_r31->unk1C.y = (f32) (temp_r31->unk1C.y + 4.0f);
        if (fn_1_3244(&temp_r31->unk10, &sp18, &spC, 3.0f) != 0) {
            temp_r31->unk54 = 1;
            temp_r31->unk28 = 7;
            arg0->func = fn_1_58A8;
        }
        goto block_14;
    }
}

void fn_1_4ED4(omObjData *arg0) {
    Vec spC;
    f32 sp8;
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 var_r23;
    s16 var_r24;
    s16 var_r25;
    s32 var_r26;
    M523Player *temp_r27;
    M523Player *temp_r28;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    if ((s32) temp_r31->unkC != 0) {
        var_f29 = fn_1_85A8((M523Player *) temp_r31);
    } else {
        temp_r31->unk38 = (u8) HuPadStkX[temp_r31->unk4];
        temp_r31->unk39 = (s8) -(s8) (u8) HuPadStkY[temp_r31->unk4];
        temp_f30 = (f32) (((s8) temp_r31->unk38 * (s8) temp_r31->unk38) + ((s8) (u8) temp_r31->unk39 * (s8) (u8) temp_r31->unk39));
        var_f27 = sqrtf(temp_f30);
        var_f29 = var_f27;
    }
    if (var_f29 >= 10.0f) {
        temp_r31->unk3C.x = (f32) (0.26785713f * (f32) (s8) temp_r31->unk38);
        temp_r31->unk3C.z = (f32) (0.26785713f * (f32) (s8) (u8) temp_r31->unk39);
    }
    temp_f1 = VECMag(&temp_r31->unk3C);
    if (temp_f1 < 0.1f) {
        temp_r29 = arg0->data;
        if ((s16) temp_r29->unk32 != 4) {
            if ((s16) temp_r29->unk30 == 0) {
                var_r25 = lbl_1_data_2CC[4].unk0;
            } else {
                var_r25 = lbl_1_data_2CC[4].unk2;
            }
            CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r25], 0.0f, lbl_1_data_2CC[4].unk4, lbl_1_data_2CC[4].unk8);
            temp_r29->unk32 = 4;
        }
    } else if (temp_f1 < 7.5f) {
        temp_r28 = arg0->data;
        if ((s16) temp_r28->unk32 != 1) {
            if ((s16) temp_r28->unk30 == 0) {
                var_r24 = lbl_1_data_2CC[1].unk0;
            } else {
                var_r24 = lbl_1_data_2CC[1].unk2;
            }
            CharMotionShiftSet(temp_r28->unk2, arg0->motion[var_r24], 0.0f, lbl_1_data_2CC[1].unk4, lbl_1_data_2CC[1].unk8);
            temp_r28->unk32 = 1;
        }
    } else {
        temp_r27 = arg0->data;
        if ((s16) temp_r27->unk32 != 2) {
            if ((s16) temp_r27->unk30 == 0) {
                var_r23 = lbl_1_data_2CC[2].unk0;
            } else {
                var_r23 = lbl_1_data_2CC[2].unk2;
            }
            CharMotionShiftSet(temp_r27->unk2, arg0->motion[var_r23], 0.0f, lbl_1_data_2CC[2].unk4, lbl_1_data_2CC[2].unk8);
            temp_r27->unk32 = 2;
        }
    }
    if (temp_f1 >= 0.1f) {
        temp_r31->unk1C.y = (f32) (180.0 * (atan2((f64) temp_r31->unk3C.x, (f64) temp_r31->unk3C.z) / 3.141592653589793));
        fn_1_595C((M523Player *) temp_r31);
        if ((s16) temp_r31->unk30 == 0) {
            var_f28 = temp_r31->unk34;
        } else {
            var_f28 = temp_r31->unk34 - 50.0f;
        }
        VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &spC);
        spC.y = 0.0f;
        if (VECMag(&spC) > (800.0f - var_f28)) {
            VECNormalize(&spC, &spC);
            VECScale(&spC, &spC, 800.0f - var_f28);
            VECSubtract(&spC, &temp_r31->unk10, &temp_r31->unk3C);
            temp_r31->unk3C.y = 0.0f;
        }
        VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &temp_r31->unk10);
    }
    var_r26 = 1;
loop_34:
    if (var_r26 < 0xA) {
        memcpy(&lbl_1_bss_150[var_r26 - 1], &lbl_1_bss_150[var_r26], 0xC);
        var_r26 += 1;
        goto loop_34;
    }
    lbl_1_bss_150[9].x = temp_r31->unk3C.x;
    lbl_1_bss_150[9].y = temp_r31->unk3C.y;
    lbl_1_bss_150[9].z = temp_r31->unk3C.z;
}

void fn_1_54A8(omObjData *arg0) {
    Vec sp14;
    Vec sp8;
    f32 var_f31;
    s16 var_r26;
    s16 var_r27;
    s32 temp_r0;
    M523Player *temp_r28;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk3C.z = 0.0f;
    temp_r31->unk3C.y = 0.0f;
    temp_r31->unk3C.x = 0.0f;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* irregular */
    case 1:
        VECSubtract(lbl_1_data_278, &temp_r31->unk10, &sp14);
        sp14.y = 0.0f;
        if (VECMag(&sp14) < 15.0f) {
            temp_r29 = arg0->data;
            if ((s16) temp_r29->unk32 != 0) {
                if ((s16) temp_r29->unk30 == 0) {
                    var_r27 = lbl_1_data_2CC->unk0;
                } else {
                    var_r27 = lbl_1_data_2CC->unk2;
                }
                CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r27], 0.0f, lbl_1_data_2CC->unk4, lbl_1_data_2CC->unk8);
                temp_r29->unk32 = 0;
            }
            temp_r31->unk28 = 4;
            temp_r31->unk3C.x = sp14.x;
            temp_r31->unk3C.y = sp14.y;
            temp_r31->unk3C.z = sp14.z;
        } else {
            VECNormalize(&sp14, &sp14);
            temp_r31->unk3C.x = (f32) (15.0f * sp14.x);
            temp_r31->unk3C.z = (f32) (15.0f * sp14.z);
        }
        temp_r31->unk1C.y = (f32) (180.0 * (atan2((f64) temp_r31->unk3C.x, (f64) temp_r31->unk3C.z) / 3.141592653589793));
        fn_1_595C((M523Player *) temp_r31);
        if ((s16) temp_r31->unk30 == 0) {
            var_f31 = temp_r31->unk34;
        } else {
            var_f31 = temp_r31->unk34 - 50.0f;
        }
        VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &sp8);
        sp8.y = 0.0f;
        if (VECMag(&sp8) > (800.0f - var_f31)) {
            VECNormalize(&sp8, &sp8);
            VECScale(&sp8, &sp8, 800.0f - var_f31);
            VECSubtract(&sp8, &temp_r31->unk10, &temp_r31->unk3C);
            temp_r31->unk3C.y = 0.0f;
        }
        VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &temp_r31->unk10);
        break;
    case 4:
        temp_r31->unk1C.y = fn_1_3368(temp_r31->unk1C.y, 0.0f, 15.0f);
        if (fabs(temp_r31->unk1C.y) <= 1.0f) {
            temp_r31->unk54 = 1;
            temp_r31->unk28 = 5;
        }
        break;
    case 5:
        if ((s32) lbl_1_bss_18 == 4) {
            temp_r31->unk28 = 6;
            temp_r28 = arg0->data;
            if ((s16) temp_r28->unk32 != 8) {
                if ((s16) temp_r28->unk30 == 0) {
                    var_r26 = lbl_1_data_2CC[8].unk0;
                } else {
                    var_r26 = lbl_1_data_2CC[8].unk2;
                }
                CharMotionShiftSet(temp_r28->unk2, arg0->motion[var_r26], 0.0f, lbl_1_data_2CC[8].unk4, lbl_1_data_2CC[8].unk8);
                temp_r28->unk32 = 8;
            }
        }
        break;
    }
    omSetRot(arg0, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
    omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
}

void fn_1_58A8(omObjData *arg0) {
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk10 = lbl_1_bss_140[temp_r31->unk58]->unk10;
    temp_r31->unk10.y = 200.0f;
    temp_r31->unk1C.y = (f32) (temp_r31->unk1C.y + 4.0f);
    omSetRot(arg0, temp_r31->unk1C.x, temp_r31->unk1C.y, temp_r31->unk1C.z);
    omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
}

void fn_1_595C(M523Player *arg0) {
    Vec sp8;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        VECAdd(&arg0->unk10, &arg0->unk3C, &sp8);
        fn_1_34D8(&arg0->unk10, &sp8, &lbl_1_data_1E4[var_r30], 50.0f + arg0->unk34);
        VECSubtract(&sp8, &arg0->unk10, &arg0->unk3C);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_5AFC(M523Player *arg0) {
    f32 sp10;
    f32 sp8;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;

    temp_f0 = (f32) ((f64) lbl_1_data_248[1].x + (300.0 * sin(2.9670597283903604)));
    sp8 = temp_f0;
    temp_f0_2 = (f32) ((f64) lbl_1_data_248[1].z + (300.0 * cos(2.9670597283903604)));
    sp10 = temp_f0_2;
    arg0->unk48.x = temp_f0;
    arg0->unk48.z = temp_f0_2;
    arg0->unk48.y = 0.0f;
    temp_f0_3 = (f32) ((f64) temp_f0 + ((f64) (1500.0f + (628.31854f * (f32) (arg0->unk30 - 1))) * sin(4.537856055185257)));
    sp8 = temp_f0_3;
    temp_f0_4 = (f32) ((f64) temp_f0_2 + ((f64) (1500.0f + (628.31854f * (f32) (arg0->unk30 - 1))) * cos(4.537856055185257)));
    sp10 = temp_f0_4;
    arg0->unk10.x = temp_f0_3;
    arg0->unk10.z = temp_f0_4;
    arg0->unk10.y = 0.0f;
}

void fn_1_5CB8(omObjData *arg0) {
    Vec sp8;
    Vec *temp_r4;
    f32 var_f31;
    s32 temp_r0;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = temp_r31->unk28;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 19:                                        /* switch 1 */
        VECSubtract(&temp_r31->unk48, &temp_r31->unk10, &sp8);
        if (VECMag(&sp8) < 30.0f) {
            arg0->work[0] = 0x12C;
            arg0->work[1] = 0;
            temp_r31->unk10.x = (f32) temp_r31->unk48.x;
            temp_r31->unk10.y = (f32) temp_r31->unk48.y;
            temp_r31->unk10.z = (f32) temp_r31->unk48.z;
            temp_r31->unk28 = 0x14;
            temp_r31->unk1C.y = 170.0f;
            lbl_1_bss_14 = 1;
        } else {
            VECNormalize(&sp8, &sp8);
            VECScale(&sp8, &sp8, 30.0f);
            VECAdd(&temp_r31->unk10, &sp8, &temp_r31->unk10);
        }
        break;
    case 20:                                        /* switch 1 */
        temp_r31->unk1C.y = (f32) (temp_r31->unk1C.y - 5.729578f);
        temp_r31->unk1C.x = (f32) (temp_r31->unk1C.x + 5.729578f);
        if (temp_r31->unk1C.x >= (495.0f - (65.0f * (f32) (temp_r31->unk30 - 2)))) {
            if ((s16) temp_r31->unk30 >= 2) {
                temp_r31->unk28 = 0x15;
            } else if ((u32) arg0->work[0] > 5U) {
                arg0->work[0] -= 5;
                if (((u32) arg0->work[0] < 0x6EU) && ((u32) arg0->work[1] == 0)) {
                    lbl_1_bss_14 = 2;
                    arg0->work[1] = 1;
                }
            } else {
                arg0->work[0] = 0;
                temp_r31->unk28 = 0x16;
            }
        }
        var_f31 = (f32) arg0->work[0];
        if (var_f31 == 0.0f) {
            var_f31 = 0.0f;
        }
        temp_r31->unk10.x = (f32) ((f64) lbl_1_data_248[1].x + ((f64) var_f31 * sin((3.141592653589793 * (f64) temp_r31->unk1C.y) / 180.0)));
        temp_r31->unk10.z = (f32) ((f64) lbl_1_data_248[1].z + ((f64) var_f31 * cos((3.141592653589793 * (f64) temp_r31->unk1C.y) / 180.0)));
        break;
    case 21:                                        /* switch 1 */
        VECSubtract(&lbl_1_data_248[temp_r31->unk30], &temp_r31->unk10, &sp8);
        if (VECMag(&sp8) < 30.0f) {
            temp_r4 = &lbl_1_data_248[temp_r31->unk30];
            temp_r31->unk10.x = (f32) temp_r4->x;
            temp_r31->unk10.y = (f32) temp_r4->y;
            temp_r31->unk10.z = (f32) temp_r4->z;
            temp_r31->unk28 = 0x19;
        } else {
            VECNormalize(&sp8, &sp8);
            VECScale(&sp8, &sp8, 30.0f);
            VECAdd(&temp_r31->unk10, &sp8, &temp_r31->unk10);
        }
        break;
    case 22:                                        /* switch 1 */
        switch ((u32) arg0->work[0]) {              /* switch 2; irregular */
        case 0x0:                                   /* switch 2 */
            omVibrate(temp_r31->unk0, 0x5A, 6, 6);
            Hu3DMotionTimeSet(arg0->model[2], 0.0f);
            Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
            temp_r31->unk88 = fn_1_F34(&temp_r31->unk10, 0x74C);
            break;
        case 0xE:                                   /* switch 2 */
            fn_1_9798(&temp_r31->unk10);
            Hu3DModelAttrSet(arg0->model[2], 0x40000002U);
            break;
        case 0x4A:                                  /* switch 2 */
            Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
            break;
        case 0x59:                                  /* switch 2 */
            temp_r31->unk28 = 0x19;
            Hu3DMotionTimeSet(arg0->model[2], 0.0f);
            Hu3DModelAttrSet(arg0->model[2], 0x40000002U);
            HuAudFXStop(temp_r31->unk88);
            break;
        }
        arg0->work[0] += 1;
        break;
    case 25:                                        /* switch 1 */
        arg0->func = fn_1_6294;
        temp_r31->unk1C.y = 0.0f;
        temp_r31->unk1C.x = 0.0f;
        Hu3DModelRotSetV(temp_r31->unk2C->model[1], &temp_r31->unk1C);
        Hu3DModelRotSetV(temp_r31->unk2C->model[2], &temp_r31->unk1C);
        break;
    }
    Hu3DModelPosSetV(temp_r31->unk2C->model[1], &temp_r31->unk10);
    Hu3DModelPosSetV(temp_r31->unk2C->model[2], &temp_r31->unk10);
}


void fn_1_6294(omObjData *arg0) {
    s16 spA;
    s16 sp8;
    omObjData *temp_r28;
    s16 var_r27;
    s32 temp_r0;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    fn_1_E58(&temp_r31->unk10, &spA, &sp8);
    CharModelVoicePanSet(temp_r31->unk2, sp8);
    CharModelVoiceVolSet(temp_r31->unk2, spA);
    temp_r31->unk74.x = (f32) temp_r31->unk3C.x;
    temp_r31->unk74.y = (f32) temp_r31->unk3C.y;
    temp_r31->unk74.z = (f32) temp_r31->unk3C.z;
    temp_r31->unk3C.z = 0.0f;
    temp_r31->unk3C.y = 0.0f;
    temp_r31->unk3C.x = 0.0f;
    if (((s32) lbl_1_bss_18 == 2) && ((s32) temp_r31->unk84 != 0) && ((s32) temp_r31->unk28 != 2)) {
        Hu3DMotionTimeSet(temp_r31->unk2C->model[2], 0.0f);
        Hu3DModelAttrSet(temp_r31->unk2C->model[2], 0x40000002U);
        temp_r31->unk84 = 0;
        temp_r31->unk82 = 0;
        if ((s32) temp_r31->unk88 != -1) {
            HuAudFXStop(temp_r31->unk88);
            temp_r31->unk88 = -1;
        }
        HuPadRumbleStop(temp_r31->unk4);
        if ((M523Beam *) temp_r31->unk8C != NULL) {
            temp_r31->unk8C->unk20 = 1;
            temp_r31->unk8C = NULL;
        }
        temp_r31->unk28 = 3;
        arg0->func = fn_1_6800;
        return;
    }
    temp_r0 = temp_r31->unk28;
    if ((u32) temp_r0 <= 0xCU) {
        switch (temp_r0) {
        case 1:
            if ((s32) lbl_1_bss_18 == 2) {
                temp_r31->unk28 = 3;
                arg0->func = fn_1_6800;
                return;
            }
            fn_1_6DA4(arg0);
            goto block_38;
        case 2:
            if ((s32) lbl_1_bss_18 == 2) {
                if ((s32) lbl_1_bss_13C->unk28 == 7) {
                    temp_r31->unk28 = 3;
                    arg0->func = fn_1_6800;
                }
                return;
            }
            goto block_38;
        case 8:
            omVibrate(temp_r31->unk0, 0x5A, 6, 6);
            Hu3DMotionTimeSet(arg0->model[2], 0.0f);
            Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
            temp_r31->unk28 = 9;
            temp_r31->unk84 = 1;
            temp_r31->unk88 = fn_1_F34(&temp_r31->unk10, 0x74C);
            goto block_38;
        case 9:
            if (Hu3DMotionTimeGet(arg0->model[2]) >= 14.0f) {
                Hu3DModelAttrSet(arg0->model[2], 0x40000002U);
                temp_r31->unk8C = fn_1_9798(&temp_r31->unk10);
                temp_r31->unk28 = 0xA;
                temp_r31->unk82 = 0;
            }
            goto block_38;
        case 10:
            temp_r31->unk82 = (s16) (temp_r31->unk82 + 1);
            if ((s16) temp_r31->unk82 == 0x3C) {
                temp_r31->unk8C = NULL;
                Hu3DModelAttrReset(arg0->model[2], 0x40000002U);
                temp_r31->unk28 = 0xB;
            }
            if (fn_1_73D4((M523Player *) temp_r31) != 0) {
                temp_r31->unk82 = 0;
                omVibrate(lbl_1_bss_13C->unk0, 0x3C, 0xC, 0);
                temp_r28 = lbl_1_bss_13C->unk2C;
                temp_r29 = temp_r28->data;
                if ((s16) temp_r29->unk32 != 5) {
                    if ((s16) temp_r29->unk30 == 0) {
                        var_r27 = lbl_1_data_2CC[5].unk0;
                    } else {
                        var_r27 = lbl_1_data_2CC[5].unk2;
                    }
                    CharMotionShiftSet(temp_r29->unk2, temp_r28->motion[var_r27], 0.0f, lbl_1_data_2CC[5].unk4, lbl_1_data_2CC[5].unk8);
                    temp_r29->unk32 = 5;
                }
                lbl_1_bss_13C->unk28 = 2;
                fn_1_F34(&lbl_1_bss_13C->unk10, 0x74E);
                temp_r31->unk28 = 2;
                lbl_1_bss_13C->unk58 = temp_r31->unk0;
            }
            goto block_38;
        case 11:
            if (Hu3DMotionEndCheck(arg0->model[2]) != 0) {
                temp_r31->unk28 = 1;
                Hu3DMotionTimeSet(arg0->model[2], 0.0f);
                Hu3DModelAttrSet(arg0->model[2], 0x40000002U);
                temp_r31->unk82 = 0;
                HuPadRumbleStop(temp_r31->unk4);
                temp_r31->unk84 = 0;
                if ((s32) temp_r31->unk88 != -1) {
                    HuAudFXStop(temp_r31->unk88);
                    temp_r31->unk88 = -1;
                }
            }
            goto block_38;
        case 12:
            if (((s32) temp_r31->unk84 != 0) && ((s16) lbl_1_bss_13C->unk58 == -1)) {
                Hu3DMotionTimeSet(arg0->model[2], 0.0f);
                Hu3DModelAttrSet(arg0->model[2], 0x40000002U);
                temp_r31->unk82 = 0;
                temp_r31->unk84 = 0;
                if ((s32) temp_r31->unk88 != -1) {
                    HuAudFXStop(temp_r31->unk88);
                    temp_r31->unk88 = -1;
                }
            }
            temp_r31->unk80 = (s16) (temp_r31->unk80 - 1);
            if ((s16) temp_r31->unk80 == 0) {
                temp_r31->unk28 = 1;
                Hu3DMotionSet(temp_r31->unk90, temp_r31->unk92);
            }
            goto block_38;
        case 0:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            block_38:
            VECScale(&temp_r31->unk3C, &temp_r31->unk3C, 0.2f);
            VECScale(&temp_r31->unk74, &temp_r31->unk74, 0.8f);
            VECAdd(&temp_r31->unk3C, &temp_r31->unk74, &temp_r31->unk3C);
            break;
        }
    } else {
        VECScale(&temp_r31->unk3C, &temp_r31->unk3C, 0.2f);
        VECScale(&temp_r31->unk74, &temp_r31->unk74, 0.8f);
        VECAdd(&temp_r31->unk3C, &temp_r31->unk74, &temp_r31->unk3C);
    }
}

void fn_1_6800(omObjData *arg0) {
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    f32 spC;
    f32 sp8;
    M523Player *temp_r30;
    M523Player *temp_r4;
    M523Player *temp_r5;
    f32 temp_f30;
    f32 var_f28;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s32 var_r27;
    s32 var_r28;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    temp_r31->unk39 = 0;
    temp_r31->unk38 = 0;
    temp_r31->unk3C.z = 0.0f;
    temp_r31->unk3C.y = 0.0f;
    temp_r31->unk3C.x = 0.0f;
    if ((s32) temp_r31->unk54 != 0) {
        temp_r31->unk28 = 5;
        if ((s32) lbl_1_bss_1C == 0) {
            arg0->work[0] = (3 - temp_r31->unk30) * 0x14;
            arg0->func = fn_1_7898;
        } else {
            arg0->func = fn_1_76E4;
        }
        return;
    }
    VECSubtract(&temp_r31->unk48, &temp_r31->unk10, &sp28);
    sp28.y = 0.0f;
    if (VECMag(&sp28) < 15.0f) {
        temp_r31->unk54 = 1;
        temp_r31->unk3C.x = sp28.x;
        temp_r31->unk3C.y = sp28.y;
        temp_r31->unk3C.z = sp28.z;
    } else {
        VECNormalize(&sp28, &sp28);
        temp_r31->unk38 = (s8) (56.0f * sp28.x);
        temp_r31->unk39 = (s8) (56.0f * sp28.z);
        temp_f30 = (f32) (((s8) (u8) temp_r31->unk38 * (s8) (u8) temp_r31->unk38) + ((s8) (u8) temp_r31->unk39 * (s8) (u8) temp_r31->unk39));
        var_f28 = sqrtf(temp_f30);
        spC = var_f28;
        temp_r31->unk3C.x = (f32) (0.26785713f * (f32) (s8) (u8) temp_r31->unk38);
        temp_r31->unk3C.z = (f32) (0.26785713f * (f32) (s8) (u8) temp_r31->unk39);
        temp_r31->unk3C.y = 0.0f;
    }
    if ((s16) temp_r31->unk30 == 0) {
        var_f29 = temp_r31->unk34;
    } else {
        var_f29 = temp_r31->unk34 - 50.0f;
    }
    VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &sp1C);
    sp1C.y = 0.0f;
    if (VECMag(&sp1C) > (800.0f - var_f29)) {
        VECNormalize(&sp1C, &sp1C);
        VECScale(&sp1C, &sp1C, 800.0f - var_f29);
        VECSubtract(&sp1C, &temp_r31->unk10, &temp_r31->unk3C);
        temp_r31->unk3C.y = 0.0f;
    }
    var_r28 = 0;
loop_18:
    if (var_r28 < 4) {
        temp_r5 = lbl_1_bss_140[var_r28];
        temp_r4 = lbl_1_bss_140[var_r28];
        temp_r4->unk5C.x = temp_r5->unk10.x;
        temp_r4->unk5C.y = temp_r5->unk10.y;
        temp_r4->unk5C.z = temp_r5->unk10.z;
        var_r28 += 1;
        goto loop_18;
    }
    VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &temp_r31->unk10);
    VECSubtract(&temp_r31->unk5C, &temp_r31->unk10, &sp10);
    if (!(VECMag(&sp10) < 0.01f)) {
        var_r27 = 0;
loop_27:
        if (var_r27 < 4) {
            temp_r30 = lbl_1_bss_140[var_r27];
            if ((temp_r31 != temp_r30) && (temp_r30 != (M523Player *) lbl_1_bss_13C) && ((s32) temp_r30->unk28 != 6)) {
                VECSubtract(&temp_r31->unk10, &temp_r30->unk10, &sp10);
                if (!(VECMag(&sp10) >= (temp_r31->unk34 + temp_r30->unk34))) {
                    VECNormalize(&sp10, &sp10);
                    VECScale(&sp10, &sp10, temp_r31->unk34 + temp_r30->unk34);
                    VECAdd(&temp_r30->unk10, &sp10, &temp_r31->unk10);
                    temp_r31->unk10.y = 0.0f;
                }
            }
            var_r27 += 1;
            goto loop_27;
        }
    }
    Hu3DModelPosSetV(temp_r31->unk2C->model[1], &temp_r31->unk10);
    Hu3DModelRotSetV(temp_r31->unk2C->model[1], &temp_r31->unk1C);
    Hu3DModelPosSetV(temp_r31->unk2C->model[2], &temp_r31->unk10);
    Hu3DModelRotSetV(temp_r31->unk2C->model[2], &temp_r31->unk1C);
}

void fn_1_6DA4(omObjData *arg0) {
    f32 sp8;
    f32 temp_f29;
    f32 var_f28;
    f32 var_f30;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    if (fn_1_7358((M523Player *) temp_r31) != 0) {
        temp_r31->unk82 = 0;
        temp_r31->unk28 = 8;
        return;
    }
    if ((s32) temp_r31->unkC != 0) {
        var_f30 = fn_1_8DF0((M523Player *) temp_r31);
    } else {
        temp_r31->unk38 = (u8) HuPadStkX[temp_r31->unk4];
        temp_r31->unk39 = (s8) -(s8) (u8) HuPadStkY[temp_r31->unk4];
        temp_f29 = (f32) (((s8) temp_r31->unk38 * (s8) temp_r31->unk38) + ((s8) (u8) temp_r31->unk39 * (s8) (u8) temp_r31->unk39));
        var_f28 = sqrtf(temp_f29);
        var_f30 = var_f28;
    }
    if (var_f30 > 30.0f) {
        temp_r31->unk38 = (u8) (s32) ((f32) ((s8) temp_r31->unk38 * 0x1E) / var_f30);
        temp_r31->unk39 = (s8) ((f32) ((s8) (u8) temp_r31->unk39 * 0x1E) / var_f30);
        var_f30 = 30.0f;
    }
    if (var_f30 >= 15.0f) {
        temp_r31->unk3C.x = (f32) (1.6666666f * (f32) (s8) temp_r31->unk38);
        temp_r31->unk3C.z = (f32) (1.6666666f * (f32) (s8) (u8) temp_r31->unk39);
        return;
    }
    if (var_f30 > 0.0f) {
        temp_r31->unk3C.x = (f32) (0.16666667f * (f32) (s8) temp_r31->unk38);
        temp_r31->unk3C.z = (f32) (0.16666667f * (f32) (s8) (u8) temp_r31->unk39);
    }
}


s32 fn_1_7358(M523Player *arg0) {
    s32 var_r30;

    var_r30 = 0;
    if ((s32) arg0->unkC != 0) {
        var_r30 = fn_1_90EC(arg0);
    } else if ((s32) (HuPadBtnDown[arg0->unk4] & 0x100) != 0) {
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_73D4(M523Player *arg0) {
    Vec spC;
    M523Player *sp8;

    sp8 = arg0;
    if ((s32) lbl_1_bss_13C->unk28 != 1) {
        return 0;
    }
    if ((s32) lbl_1_bss_18 == 2) {
        return 0;
    }
    VECSubtract(&lbl_1_bss_13C->unk10, &sp8->unk10, &spC);
    spC.y = 0.0f;
    if (VECMag(&spC) < 100.0f) {
        return 1;
    }
    return 0;
}

void fn_1_7488(void) {
    s16 order[3];
    M523Player *team[2];
    Vec sp24;
    Vec sp18;
    f32 temp_f31;
    s32 i;
    s32 n;

    for (i = 0; i < 3; i++) {
        order[i] = -1;
    }
    order[0] = lbl_1_bss_13C->unk58;
    n = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i]->unk30 != 0 && i != lbl_1_bss_13C->unk58) {
            team[n++] = lbl_1_bss_140[i];
        }
    }
    VECSubtract(&team[0]->unk10, &lbl_1_data_2A8[1], &sp24);
    VECSubtract(&team[1]->unk10, &lbl_1_data_2A8[1], &sp18);
    temp_f31 = VECMag(&sp18);
    if (VECMag(&sp24) < temp_f31) {
        order[1] = team[0]->unk0;
        order[2] = team[1]->unk0;
    } else {
        order[1] = team[1]->unk0;
        order[2] = team[0]->unk0;
    }
    for (i = 0; i < 3; i++) {
        if (order[i] >= 0) {
            lbl_1_bss_140[order[i]]->unk48 = lbl_1_data_2A8[i];
        }
    }
}


void fn_1_76E4(omObjData *arg0) {
    s16 var_r26;
    s16 var_r27;
    s32 temp_r0;
    M523Player *temp_r28;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    if ((s32) lbl_1_bss_18 == 4) {
        temp_r0 = temp_r31->unk28;
        switch (temp_r0) {                          /* irregular */
        case 5:
            temp_r29 = arg0->data;
            if ((s16) temp_r29->unk32 != 9) {
                if ((s16) temp_r29->unk30 == 0) {
                    var_r27 = lbl_1_data_2CC[9].unk0;
                } else {
                    var_r27 = lbl_1_data_2CC[9].unk2;
                }
                CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r27], 0.0f, lbl_1_data_2CC[9].unk4, lbl_1_data_2CC[9].unk8);
                temp_r29->unk32 = 9;
            }
            Hu3DMotionSet(temp_r31->unk90, temp_r31->unk96);
            Hu3DModelAttrReset(temp_r31->unk90, 0x40000001U);
            temp_r31->unk28 = 6;
            fn_1_F34(&temp_r31->unk10, 0x74F);
            return;
        case 6:
            if (Hu3DMotionEndCheck(temp_r31->unk90) != 0) {
                temp_r28 = arg0->data;
                if ((s16) temp_r28->unk32 != 8) {
                    if ((s16) temp_r28->unk30 == 0) {
                        var_r26 = lbl_1_data_2CC[8].unk0;
                    } else {
                        var_r26 = lbl_1_data_2CC[8].unk2;
                    }
                    CharMotionShiftSet(temp_r28->unk2, arg0->motion[var_r26], 0.0f, lbl_1_data_2CC[8].unk4, lbl_1_data_2CC[8].unk8);
                    temp_r28->unk32 = 8;
                }
                temp_r31->unk28 = 0;
            }
            break;
        case 0:
            break;
        }
    } else {
    }
}

void fn_1_7898(omObjData *arg0) {
    Vec sp8;
    s16 var_r24;
    s16 var_r25;
    s16 var_r26;
    s32 temp_r0;
    M523Player *temp_r27;
    M523Player *temp_r28;
    M523Player *temp_r29;
    M523Player *temp_r31;

    temp_r31 = arg0->data;
    if (((s32) lbl_1_bss_18 == 4) && (((u32) arg0->work[0] == 0) || (arg0->work[0] -= 1, (((u32) arg0->work[0] == 0) != 0)))) {
        temp_r0 = temp_r31->unk28;
        switch (temp_r0) {                          /* irregular */
        case 5:
            temp_r29 = arg0->data;
            if ((s16) temp_r29->unk32 != 9) {
                if ((s16) temp_r29->unk30 == 0) {
                    var_r26 = lbl_1_data_2CC[9].unk0;
                } else {
                    var_r26 = lbl_1_data_2CC[9].unk2;
                }
                CharMotionShiftSet(temp_r29->unk2, arg0->motion[var_r26], 0.0f, lbl_1_data_2CC[9].unk4, lbl_1_data_2CC[9].unk8);
                temp_r29->unk32 = 9;
            }
            Hu3DMotionSet(temp_r31->unk90, temp_r31->unk94);
            Hu3DModelAttrReset(temp_r31->unk90, 0x40000001U);
            temp_r31->unk28 = 0xD;
            omVibrate(temp_r31->unk0, 0x3C, 0xC, 0);
            fn_1_F34(&temp_r31->unk10, 0x750);
            arg0->work[1] = 0;
            return;
        case 13:
            if (Hu3DMotionTimeGet(temp_r31->unk90) >= 49.0f) {
                Hu3DModelObjPosGet(temp_r31->unk90, lbl_1_data_350, &temp_r31->unk10);
                omResetStatBit(arg0, 0x100U);
                Hu3DModelHookReset(temp_r31->unk90);
                temp_r31->unk28 = 6;
                temp_r31->unk3C.z = 0.0f;
                temp_r31->unk3C.y = 0.0f;
                temp_r31->unk3C.x = 0.0f;
                temp_r28 = arg0->data;
                if ((s16) temp_r28->unk32 != 0xA) {
                    if ((s16) temp_r28->unk30 == 0) {
                        var_r25 = lbl_1_data_2CC[0xA].unk0;
                    } else {
                        var_r25 = lbl_1_data_2CC[0xA].unk2;
                    }
                    CharMotionShiftSet(temp_r28->unk2, arg0->motion[var_r25], 0.0f, lbl_1_data_2CC[0xA].unk4, lbl_1_data_2CC[0xA].unk8);
                    temp_r28->unk32 = 0xA;
                }
                omSetTra(arg0, temp_r31->unk10.x, temp_r31->unk10.y, temp_r31->unk10.z);
                arg0->work[1] = 0;
                return;
            }
            break;
        case 6:
            arg0->work[1] += 1;
            temp_r31->unk3C.y = (f32) (1000.0 * sin((3.141592653589793 * (f64) (2.8f * (f32) arg0->work[1])) / 180.0));
            temp_r31->unk3C.z = (f32) (temp_r31->unk3C.z + 3.5f);
            VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &sp8);
            if (sp8.y < 0.0f) {
                temp_r27 = arg0->data;
                if ((s16) temp_r27->unk32 != 7) {
                    if ((s16) temp_r27->unk30 == 0) {
                        var_r24 = lbl_1_data_2CC[7].unk0;
                    } else {
                        var_r24 = lbl_1_data_2CC[7].unk2;
                    }
                    CharMotionShiftSet(temp_r27->unk2, arg0->motion[var_r24], 0.0f, lbl_1_data_2CC[7].unk4, lbl_1_data_2CC[7].unk8);
                    temp_r27->unk32 = 7;
                }
                temp_r31->unk3C.z = 0.0f;
                temp_r31->unk3C.y = 0.0f;
                temp_r31->unk3C.x = 0.0f;
                sp8.y = 0.0f;
                temp_r31->unk28 = 0;
            }
            omSetTra(arg0, sp8.x, sp8.y, sp8.z);
            break;
        case 0:
            break;
        }
    } else {
    }
}

void fn_1_7C84(omObjData *arg0) {
    s16 sp14[3];
    s16 spE[3];
    Vec sp1C;
    Vec sp34;
    s32 sp40[4][4];
    Vec sp28;
    s16 spC;
    omObjData *sp8;
    M523Player *temp_r26;
    M523Player *temp_r29;
    M523Player *temp_r30;
    M523Player *temp_r31;
    M523Player *temp_r31_2;
    omObjData *temp_r3_2;
    omObjData *temp_r3_4;
    omObjData *temp_r3_6;
    f32 temp_f1;
    f32 var_f30;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r3;
    s16 temp_r3_3;
    s16 temp_r3_5;
    s16 var_r20;
    s16 var_r21;
    s16 var_r24;
    s16 var_r24_2;
    s16 var_r25;
    s16 var_r25_2;
    s32 var_r27;
    s32 var_r27_2;
    s32 var_r27_3;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 var_r28_4;

    sp8 = arg0;
    if ((s32) lbl_1_bss_18 == 2) {
        omDelObjEx(lbl_1_bss_E4, sp8);
        return;
    }
    if ((s32) lbl_1_bss_13C->unk28 != 2) {
        var_r28 = 0;
loop_8:
        if (var_r28 < 4) {
            var_r27 = 0;
loop_6:
            if (var_r27 < 4) {
                sp40[var_r28][var_r27] = 0;
                var_r27 += 1;
                goto loop_6;
            }
            var_r28 += 1;
            goto loop_8;
        }
        var_r28_2 = 0;
loop_48:
        if (var_r28_2 < 4) {
            temp_r31 = lbl_1_bss_140[var_r28_2];
            if (temp_r31 != (M523Player *) lbl_1_bss_13C) {
                if ((s16) temp_r31->unk30 == 0) {
                    var_f30 = temp_r31->unk34;
                } else {
                    var_f30 = temp_r31->unk34 - 50.0f;
                }
                VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &sp1C);
                sp1C.y = 0.0f;
                if (VECMag(&sp1C) > (800.0f - var_f30)) {
                    VECNormalize(&sp1C, &sp1C);
                    VECScale(&sp1C, &sp1C, 800.0f - var_f30);
                    VECSubtract(&sp1C, &temp_r31->unk10, &temp_r31->unk3C);
                    temp_r31->unk3C.y = 0.0f;
                }
                VECAdd(&temp_r31->unk10, &temp_r31->unk3C, &temp_r31->unk10);
                var_r27_2 = 0;
loop_46:
                if (var_r27_2 < 4) {
                    temp_r26 = lbl_1_bss_140[var_r27_2];
                    if ((temp_r31 != temp_r26) && (temp_r26 != (M523Player *) lbl_1_bss_13C)) {
                        VECSubtract(&temp_r31->unk10, &temp_r26->unk10, &sp34);
                        if (!(VECMag(&sp34) > (temp_r31->unk34 + temp_r26->unk34))) {
                            VECSubtract(&temp_r31->unk3C, &temp_r26->unk3C, &sp28);
                            VECNormalize(&sp34, &sp34);
                            temp_f1 = VECDotProduct(&sp28, &sp34);
                            temp_r31->unk3C.x = (f32) ((f64) temp_r31->unk3C.x + (-1.800000011920929 * (f64) (sp34.x * temp_f1) * 0.5));
                            temp_r31->unk3C.y = (f32) ((f64) temp_r31->unk3C.y + (-1.800000011920929 * (f64) (sp34.y * temp_f1) * 0.5));
                            temp_r31->unk3C.z = (f32) ((f64) temp_r31->unk3C.z + (-1.800000011920929 * (f64) (sp34.z * temp_f1) * 0.5));
                            temp_r26->unk3C.x = (f32) ((f64) temp_r26->unk3C.x + (1.800000011920929 * (f64) (sp34.x * temp_f1) * 0.5));
                            temp_r26->unk3C.y = (f32) ((f64) temp_r26->unk3C.y + (1.800000011920929 * (f64) (sp34.y * temp_f1) * 0.5));
                            temp_r26->unk3C.z = (f32) ((f64) temp_r26->unk3C.z + (1.800000011920929 * (f64) (sp34.z * temp_f1) * 0.5));
                            sp40[var_r28_2][var_r27_2] = 1;
                            temp_r30 = lbl_1_bss_140[var_r28_2];
                            temp_r30->unk80 = 0x28;
                            Hu3DMotionSet(temp_r30->unk90, temp_r30->unk98);
                            omVibrate(temp_r30->unk0, 0xC, 0xC, 0);
                            temp_r30->unkA2 = 0;
                            if ((s32) temp_r30->unk28 != 0xC) {
                                temp_r30->unk28 = 0xC;
                                if ((M523Beam *) temp_r30->unk8C != NULL) {
                                    temp_r30->unk8C->unk20 = 1;
                                    temp_r30->unk8C = NULL;
                                }
                                var_r21 = 0;
                                var_r25 = 0;
loop_27:
                                if (var_r25 < 3) {
                                    if ((s32) lbl_1_bss_130[var_r25] == 0) {
                                        temp_r0 = var_r21;
                                        var_r21 += 1;
                                        sp14[temp_r0] = var_r25;
                                    }
                                    var_r25 += 1;
                                    goto loop_27;
                                }
                                if (var_r21 == 0) {
                                    var_r25_2 = 0;
                                } else {
                                    var_r25_2 = sp14[frandmod((u32) var_r21)];
                                }
                                lbl_1_bss_130[var_r25_2] = 1;
                                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_13C[var_r25_2], MEMORY_DEFAULT_NUM, HEAP_DATA));
                                Hu3DModelLayerSet(temp_r3, 5);
                                temp_r3_2 = omAddObjEx(lbl_1_bss_E4, 0x1400, 1U, 0U, -1, fn_1_4654);
                                *temp_r3_2->model = temp_r3;
                                temp_r3_2->work[0] = (u32) temp_r30->unk0;
                                temp_r3_2->work[1] = (u32) var_r25_2;
                                omSetTra(temp_r3_2, temp_r30->unk10.x, temp_r30->unk10.y, temp_r30->unk10.z);
                            }
                            temp_r29 = lbl_1_bss_140[var_r27_2];
                            temp_r29->unk80 = 0x28;
                            Hu3DMotionSet(temp_r29->unk90, temp_r29->unk98);
                            omVibrate(temp_r29->unk0, 0xC, 0xC, 0);
                            temp_r29->unkA2 = 0;
                            if ((s32) temp_r29->unk28 != 0xC) {
                                temp_r29->unk28 = 0xC;
                                if ((M523Beam *) temp_r29->unk8C != NULL) {
                                    temp_r29->unk8C->unk20 = 1;
                                    temp_r29->unk8C = NULL;
                                }
                                var_r20 = 0;
                                var_r24 = 0;
loop_39:
                                if (var_r24 < 3) {
                                    if ((s32) lbl_1_bss_130[var_r24] == 0) {
                                        temp_r0_2 = var_r20;
                                        var_r20 += 1;
                                        spE[temp_r0_2] = var_r24;
                                    }
                                    var_r24 += 1;
                                    goto loop_39;
                                }
                                if (var_r20 == 0) {
                                    var_r24_2 = 0;
                                } else {
                                    var_r24_2 = spE[frandmod((u32) var_r20)];
                                }
                                lbl_1_bss_130[var_r24_2] = 1;
                                temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_13C[var_r24_2], MEMORY_DEFAULT_NUM, HEAP_DATA));
                                spC = temp_r3_3;
                                Hu3DModelLayerSet(temp_r3_3, 5);
                                temp_r3_4 = omAddObjEx(lbl_1_bss_E4, 0x1400, 1U, 0U, -1, fn_1_4654);
                                *temp_r3_4->model = spC;
                                temp_r3_4->work[0] = (u32) temp_r29->unk0;
                                temp_r3_4->work[1] = (u32) var_r24_2;
                                omSetTra(temp_r3_4, temp_r29->unk10.x, temp_r29->unk10.y, temp_r29->unk10.z);
                            }
                            VECScale(&sp34, &sp34, 1.0f + (temp_r31->unk34 + temp_r26->unk34));
                            VECAdd(&temp_r26->unk10, &sp34, &temp_r31->unk10);
                        }
                    }
                    var_r27_2 += 1;
                    goto loop_46;
                }
            }
            var_r28_2 += 1;
            goto loop_48;
        }
        var_r28_3 = 0;
loop_53:
        if (var_r28_3 < 4) {
            if ((s16) lbl_1_bss_140[var_r28_3]->unk30 != 0) {
                temp_r31_2 = lbl_1_bss_140[var_r28_3];
                Hu3DModelPosSetV(temp_r31_2->unk2C->model[1], &temp_r31_2->unk10);
                Hu3DModelRotSetV(temp_r31_2->unk2C->model[1], &temp_r31_2->unk1C);
                Hu3DModelPosSetV(temp_r31_2->unk2C->model[2], &temp_r31_2->unk10);
                Hu3DModelRotSetV(temp_r31_2->unk2C->model[2], &temp_r31_2->unk1C);
            }
            var_r28_3 += 1;
            goto loop_53;
        }
        var_r28_4 = 0;
loop_61:
        if (var_r28_4 < 4) {
            var_r27_3 = 0;
loop_59:
            if (var_r27_3 < 4) {
                if ((s32) sp40[var_r28_4][var_r27_3] == 1) {
                    VECAdd(&lbl_1_bss_140[var_r28_4]->unk10, &lbl_1_bss_140[var_r27_3]->unk10, &sp34);
                    VECScale(&sp34, &sp34, 0.5f);
                    temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M523, 20), MEMORY_DEFAULT_NUM, HEAP_DATA));
                    Hu3DModelLayerSet(temp_r3_5, 5);
                    temp_r3_6 = omAddObjEx(lbl_1_bss_E4, 0x1400, 1U, 0U, -1, fn_1_4534);
                    *temp_r3_6->model = temp_r3_5;
                    sp34.y = 530.0f;
                    omSetTra(temp_r3_6, sp34.x, sp34.y, sp34.z);
                    fn_1_F34(&sp34, 0x74D);
                }
                var_r27_3 += 1;
                goto loop_59;
            }
            var_r28_4 += 1;
            goto loop_61;
        }
    }
}

f32 fn_1_85A8(M523Player *arg0) {
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r0;
    s16 temp_r3;

    arg0->unk39 = 0;
    arg0->unk38 = 0;
    VECSubtract(&arg0->unkA4, &arg0->unk10, &spC);
    spC.y = 0.0f;
    if (VECMag(&spC) < 15.0f) {
        arg0->unkA2 = 0;
    }
    temp_r0 = arg0->unkA2;
    switch (temp_r0) {                              /* irregular */
    case 0:
        fn_1_8874(arg0);
        arg0->unkA2 = 1;
        arg0->unk9C = 0x64;
        /* fallthrough */
    case 1:
        if (((s16) arg0->unk8 >= 2) && (temp_r3 = fn_1_8D14(arg0), ((temp_r3 == -1) == 0)) && (frandmod(0x64U) <= (s32) lbl_1_rodata_240[arg0->unk8])) {
            if ((s16) arg0->unk8 <= 2) {
                arg0->unkA2 = 0;
            } else {
                fn_1_8A80(arg0, temp_r3);
            }
        } else {
            arg0->unk9C -= 1;
            if ((s32) arg0->unk9C == 0) {
                arg0->unkA2 = 0;
            }
            fn_1_8B60(arg0, 1);
        }
        break;
    }
    temp_f30 = (f32) (((s8) (u8) arg0->unk38 * (s8) (u8) arg0->unk38) + ((s8) (u8) arg0->unk39 * (s8) (u8) arg0->unk39));
    var_f29 = sqrtf(temp_f30);
    return var_f29;
}

void fn_1_8874(M523Player *arg0) {
    Vec sp8;
    f32 temp_f30;
    f32 var_f31;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    var_r28 = 0;
    do {
        var_r29 = 0;
        var_r28 += 1;
        if ((s16) arg0->unk8 == 0) {
            var_f31 = 800.0f - arg0->unk34;
        } else {
            var_f31 = (f32) frandmod((u32) (s32) (800.0f - arg0->unk34));
        }
        temp_f30 = (f32) frandmod(0x168U);
        arg0->unkA4.x = (f32) ((f64) var_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        arg0->unkA4.z = (f32) ((f64) var_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        arg0->unkA4.y = 0.0f;
        var_r30 = 0;
loop_8:
        if (var_r30 < 3) {
            VECSubtract(&arg0->unkA4, &lbl_1_data_1E4[var_r30], &sp8);
            if (VECMag(&sp8) < (50.0f + arg0->unk34)) {
                var_r29 = 1;
            }
            var_r30 += 1;
            goto loop_8;
        }
        VECSubtract(&arg0->unk10, &arg0->unkA4, &sp8);
        if ((VECMag(&sp8) < 300.0f) && (var_r28 <= 0xA)) {
            var_r29 = 1;
        }
    } while (var_r29 != 0);
}

void fn_1_8A80(M523Player *arg0, s16 arg1) {
    Vec spC;
    s16 sp8;
    f32 temp_f31;

    sp8 = arg1;
    VECSubtract(&arg0->unk10, &lbl_1_bss_140[sp8]->unk10, &spC);
    VECScale(&spC, &spC, 200.0f);
    VECAdd(&arg0->unk10, &spC, &arg0->unkA4);
    temp_f31 = arg0->unk34;
    if (VECMag(&arg0->unkA4) > (800.0f - temp_f31)) {
        VECNormalize(&arg0->unkA4, &arg0->unkA4);
        VECScale(&arg0->unkA4, &arg0->unkA4, 800.0f - temp_f31);
    }
}

void fn_1_8B60(M523Player *arg0, s32 arg1) {
    Vec spC;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f31;
    f32 var_f31;

    sp8 = arg1;
    if (sp8 != 0) {
        temp_f31 = arg0->unk1C.y;
        temp_f1 = fn_1_CEC(temp_f31, fn_1_C88(&arg0->unk10, &arg0->unkA4));
        if (fabs(temp_f1) < 15.0f) {
            var_f31 = temp_f31 + temp_f1;
        } else if (temp_f1 < 0.0f) {
            var_f31 = temp_f31 - 15.0f;
        } else {
            var_f31 = temp_f31 + 15.0f;
        }
        spC.x = (f32) sin((3.141592653589793 * (f64) var_f31) / 180.0);
        spC.z = (f32) cos((3.141592653589793 * (f64) var_f31) / 180.0);
        spC.y = 0.0f;
    } else {
        VECNormalize(&spC, &spC);
    }
    arg0->unk38 = (s8) (56.0f * spC.x);
    arg0->unk39 = (s8) (56.0f * spC.z);
}

s16 fn_1_8D14(M523Player *arg0) {
    Vec sp8;
    M523Player *temp_r30;
    f32 temp_f1;
    s16 var_r29;
    s16 var_r31;

    var_r29 = -1;
    var_r31 = 0;
loop_7:
    if (var_r31 < 4) {
        temp_r30 = lbl_1_bss_140[var_r31];
        if ((temp_r30 != arg0) && ((s32) temp_r30->unk84 != 0) && (temp_f1 = fn_1_D58(&temp_r30->unk10, &arg0->unk10, &arg0->unkA4, &sp8), ((temp_f1 < 0.0f) == 0)) && (temp_f1 < 100.0f)) {
            var_r29 = var_r31;
        } else {
            var_r31 += 1;
            goto loop_7;
        }
    }
    return var_r29;
}

f32 fn_1_8DF0(M523Player *arg0) {
    Vec spC;
    f32 sp8;
    f32 temp_f30;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r0;

    temp_r0 = arg0->unkA2;
    switch (temp_r0) {                              /* irregular */
    case 1:
        if ((s16) arg0->unk0 == fn_1_9218()) {
            fn_1_9440(arg0);
            arg0->unkA2 = 2;
        }
    default:
block_12:
        VECSubtract(&arg0->unkA4, &arg0->unk10, &spC);
        spC.y = 0.0f;
        if (VECMag(&spC) < 50.0f) {
            arg0->unkA2 = 0;
            if ((s16) arg0->unk8 == 0) {
                arg0->unk9C = frandmod(0x1EU) + 0x2D;
            } else if ((s16) arg0->unk8 == 1) {
                arg0->unk9C = frandmod(0x1EU) + 0xF;
            } else {
                arg0->unk9C = 0;
            }
            return 0.0f;
        }
        VECNormalize(&spC, &spC);
        arg0->unk38 = (s8) (56.0f * spC.x);
        arg0->unk39 = (s8) (56.0f * spC.z);
        temp_f30 = (f32) (((s8) (u8) arg0->unk38 * (s8) (u8) arg0->unk38) + ((s8) (u8) arg0->unk39 * (s8) (u8) arg0->unk39));
        var_f29 = sqrtf(temp_f30);
        return var_f29;
    case 2:
        fn_1_9440(arg0);
        goto block_12;
    case 0:
        if ((s32) arg0->unk9C == 0) {
            fn_1_92F4(arg0);
            arg0->unkA2 = 1;
            goto block_12;
        }
        arg0->unk9C -= 1;
        return 0.0f;
    }
}

s32 fn_1_90EC(M523Player *arg0) {
    Vec sp18;

    VECSubtract(&lbl_1_bss_13C->unk10, &arg0->unk10, &sp18);
    sp18.y = 0.0f;
    if (VECMag(&sp18) < 100.0f) {
        if (frandmod(0x64U) < lbl_1_rodata_260[arg0->unk8]) {
            if ((s16) arg0->unk8 <= 2) {
                return 1;
            }
            VECSubtract(&arg0->unkA4, &arg0->unk10, &sp18);
            if (VECMag(&sp18) < 50.0f) {
                return 1;
            }
            return 0;
        }
        if (frandmod(0x64U) < lbl_1_rodata_260[arg0->unk8]) {
            return 1;
        }
    }
    return 0;
}

s16 fn_1_9218(void) {
    Vec sp8;
    f32 var_f31;
    s16 var_r30;
    s16 var_r31;

    var_f31 = 9999.9f;
    var_r30 = -1;
    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        if ((M523Player *) lbl_1_bss_140[var_r31] != (M523Player *) lbl_1_bss_13C) {
            VECSubtract(&lbl_1_bss_13C->unk10, &lbl_1_bss_140[var_r31]->unk10, &sp8);
            if (VECMag(&sp8) < var_f31) {
                var_f31 = VECMag(&sp8);
                var_r30 = var_r31;
            }
        }
        var_r31 += 1;
        goto loop_5;
    }
    return var_r30;
}

void fn_1_92F4(M523Player *arg0) {
    Vec sp8;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r30;

    do {
        var_r30 = 0;
        temp_f30 = (800.0f - arg0->unk34) - 5.0f;
        temp_f31 = (f32) frandmod(0x168U);
        arg0->unkA4.x = (f32) ((f64) temp_f30 * cos((3.141592653589793 * (f64) temp_f31) / 180.0));
        arg0->unkA4.z = (f32) ((f64) temp_f30 * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        arg0->unkA4.y = 0.0f;
        VECSubtract(&arg0->unk10, &arg0->unkA4, &sp8);
        if (VECMag(&sp8) < 200.0f) {
            var_r30 = 1;
        }
    } while (var_r30 != 0);
}

void fn_1_9440(M523Player *arg0) {
    Vec sp8;
    f32 temp_f31;
    s32 var_r30;

    if ((s16) arg0->unk8 < 2) {
        arg0->unkA4.x = lbl_1_bss_13C->unk10.x;
        arg0->unkA4.y = lbl_1_bss_13C->unk10.y;
        arg0->unkA4.z = lbl_1_bss_13C->unk10.z;
    } else {
        sp8.z = 0.0f;
        sp8.y = 0.0f;
        sp8.x = 0.0f;
        var_r30 = 0;
loop_4:
        if (var_r30 < 0xA) {
            VECAdd(&sp8, &lbl_1_bss_150[var_r30], &sp8);
            var_r30 += 1;
            goto loop_4;
        }
        VECAdd(&sp8, &lbl_1_bss_13C->unk10, &arg0->unkA4);
    }
    temp_f31 = arg0->unk34 - 50.0f;
    if (VECMag(&arg0->unkA4) > (800.0f - temp_f31)) {
        VECNormalize(&arg0->unkA4, &arg0->unkA4);
        VECScale(&arg0->unkA4, &arg0->unkA4, 800.0f - temp_f31);
    }
}

void fn_1_9574(void) {
    lbl_1_bss_10C.unk0 = &lbl_1_bss_E8;
    lbl_1_bss_10C.unk4 = NULL;
    lbl_1_bss_10C.unk18 = 0;
    lbl_1_bss_10C.unk8 = -1;
    lbl_1_bss_E8.unk0 = NULL;
    lbl_1_bss_E8.unk4 = &lbl_1_bss_10C;
    lbl_1_bss_E8.unk8 = -1;
    Hu3DModelLayerSet(Hu3DHookFuncCreate((void (*)(HU3DMODEL *, f32 (*)[3][4])) fn_1_9978), 1);
}

void fn_1_962C(omObjData *arg0) {
    s16 temp_r0;
    M523Beam *temp_r31;

    temp_r31 = arg0->data;
    temp_r0 = temp_r31->unk1C;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (((s32) temp_r31->unk20 != 0) || (Hu3DMotionEndCheck(*arg0->model) != 0)) {
            Hu3DModelAttrSet(*arg0->model, 0x40000002U);
            temp_r31->unk1C = 1;
            temp_r31->unk1A = 0xB4;
            return;
        }
        return;
    case 1:
        temp_r31->unk1A = (s16) (temp_r31->unk1A - 1);
        if ((s16) temp_r31->unk1A <= 0) {
            temp_r31->unk1C = 2;
            return;
        }
        break;
    case 2:
        temp_r31->unk1A = (s16) (temp_r31->unk1A + 1);
        Hu3DModelTPLvlSet(*arg0->model, 1.0f - (0.02f * (f32) temp_r31->unk1A));
        if ((s16) temp_r31->unk1A >= 0x32) {
            temp_r31->unk1C = 3;
            return;
        }
        break;
    case 3:
        fn_1_98E8((M523Beam *) temp_r31);
        Hu3DModelKill(*arg0->model);
        omDelObjEx(lbl_1_bss_E4, arg0);
        break;
    }
}

M523Beam *fn_1_9798(Vec *arg0) {
    omObjData *temp_r29;
    s16 temp_r3;
    M523Beam *temp_r31;

    temp_r29 = omAddObjEx(lbl_1_bss_E4, 0x1200, 1U, 0U, -1, fn_1_962C);
    temp_r29->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M523Beam), MEMORY_DEFAULT_NUM);
    temp_r31 = temp_r29->data;
    temp_r31->unk1C = 0;
    temp_r31->unk20 = 0;
    lbl_1_bss_E8.unk4->unk0 = (M523Beam *) temp_r31;
    temp_r31->unk4 = (M523Beam *) lbl_1_bss_E8.unk4;
    temp_r31->unk0 = &lbl_1_bss_E8;
    lbl_1_bss_E8.unk4 = (M523Beam *) temp_r31;
    temp_r31->unk18 = (s16) (temp_r31->unk4->unk18 + 1);
    temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M523, 19), MEMORY_DEFAULT_NUM, HEAP_DATA));
    temp_r31->unk8 = temp_r3;
    *temp_r29->model = temp_r3;
    Hu3DModelLayerSet(temp_r3, 1);
    Hu3DModelAttrSet(temp_r3, 0x400000U);
    omSetTra(temp_r29, 5000.0f, 0.0f, 0.0f);
    temp_r31->unkC.x = (f32) arg0->x;
    temp_r31->unkC.y = (f32) arg0->y;
    temp_r31->unkC.z = (f32) arg0->z;
    temp_r31->unkC.y = 0.0f;
    return (M523Beam *) temp_r31;
}

void fn_1_98E8(M523Beam *arg0) {
    arg0->unk0->unk4 = arg0->unk4;
    arg0->unk4->unk0 = arg0->unk0;
    fn_1_992C();
}

void fn_1_992C(void) {
    M523Beam *var_r31;
    s16 temp_r0;
    s16 var_r30;

    var_r30 = 0;
    var_r31 = &lbl_1_bss_10C;
loop_2:
    if ((M523Beam *) var_r31->unk0 != NULL) {
        temp_r0 = var_r30;
        var_r30 += 1;
        var_r31->unk18 = temp_r0;
        var_r31 = var_r31->unk0;
        goto loop_2;
    }
}

void fn_1_9978(HU3DMODEL *modelP, Mtx mtx) {
    Mtx sp10;
    HU3DMODEL *spC;
    f32 (*sp8)[4];
    M523Beam *var_r31;

    sp8 = mtx;
    Hu3DModelObjDrawInit();
    var_r31 = &lbl_1_bss_10C;
loop_4:
    if ((M523Beam *) var_r31->unk0 != NULL) {
        if ((s16) var_r31->unk8 != -1) {
            spC = &Hu3DData[var_r31->unk8];
            MTXTrans(sp10, var_r31->unkC.x, var_r31->unkC.y, var_r31->unkC.z);
            MTXConcat(sp8, sp10, sp10);
            Hu3DModelObjDraw(var_r31->unk8, "cyl10", sp10);
        }
        var_r31 = var_r31->unk0;
        goto loop_4;
    }
}
