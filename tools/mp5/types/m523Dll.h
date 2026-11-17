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

extern M523Camera lbl_1_data_6C;
extern M523Camera lbl_1_data_B4;
extern M523Camera lbl_1_data_FC;
extern M523Camera lbl_1_data_144;
extern MGSEQ_PARAM lbl_1_data_1BC;
extern Vec lbl_1_data_1E4[3];
extern Vec lbl_1_data_248[4];
extern Vec lbl_1_data_278[4];
extern Vec lbl_1_data_2A8[3];
extern M523MotParam lbl_1_data_2CC[11];
extern char lbl_1_data_350[0x10];
extern OMOBJ *lbl_1_bss_0;
extern OMOBJ *lbl_1_bss_4;
extern M523Camera lbl_1_bss_44;
extern M523Camera lbl_1_bss_98;
extern M523Beam lbl_1_bss_E8;
extern M523Beam lbl_1_bss_10C;
extern M523Player *lbl_1_bss_13C;
extern M523Player *lbl_1_bss_140[4];
extern Vec lbl_1_bss_150[10];
extern M523Light lbl_1_rodata_A0;
extern s32 lbl_1_rodata_240[4];
extern s32 lbl_1_rodata_260[4];

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
