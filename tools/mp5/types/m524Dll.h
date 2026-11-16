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

extern M524Light lbl_1_data_EC;
extern M524Camera lbl_1_data_108;
extern M524Camera lbl_1_data_150;
extern M524Camera lbl_1_data_198;
extern M524Camera *lbl_1_bss_18;
extern M524Camera lbl_1_bss_34;
extern OMOBJ *lbl_1_bss_8;
extern s16 lbl_1_rodata_C8[2][4];
extern void (*lbl_1_data_1EC[11])(OMOBJ *);

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
