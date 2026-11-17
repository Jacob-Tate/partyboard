// m2c context for m528Dll (tools/mp5/decomp.py m528Dll --types tools/mp5/types/m528Dll.h)
// Written from the draft: Mario Can-Can (2 vs 2). Runs on MP5's MgSeq sequencer. lbl_1_bss_298 is the work object
// (OMOBJ::data = M528Work, 0x4D70); four players (OMOBJ::data = M528Player, 0x5C). Offsets are GameCube's.
// objdata: M528Player
// objdata ObjectSetup fn_1_13D0 fn_1_1458: M528Work
// objexpr lbl_1_bss_298: M528Work

typedef struct M528Half { // one of a team's two cans, 0x20
    struct M528Team *unk0; // owning team
    f32 unk4; // position
    f32 unk8;
    f32 unkC;
    f32 unk10; // push speed
    f32 unk14; // pushed
    s16 unk18; // push timer
    s16 unk1A; // model
    s16 unk1C; // hit flag
    char pad1E[2];
} M528Half;

struct M528Slice;

typedef struct M528Team { // 0x68 (two in M528Work::unk3C)
    M528Half unk0[2];
    f32 unk40; // spin rotation
    s16 unk44; // spinner model
    char pad46[2];
    Vec unk48; // position
    struct M528Slice *unk54; // target slice
    f32 unk58; // see-saw angle
    f32 unk5C;
    s16 unk60; // see-saw model
    s16 unk62; // state
    s16 unk64; // timer
    s16 unk66; // sound
} M528Team;

typedef struct M528Slice { // wheel slice, 0x2C (16 in M528Work::unk10C)
    Vec unk0; // position
    Vec unkC; // position (copy)
    f32 unk18; // spin progress
    f32 unk1C; // angle
    s16 unk20; // model
    s16 unk22; // model
    s16 unk24; // model
    s16 unk26; // state
    s16 unk28; // timer
    s16 unk2A; // kind
} M528Slice;

typedef struct M528Player { // OMOBJ::data, 0x5C
    f32 unk0; // position
    f32 unk4;
    f32 unk8;
    f32 unkC; // rotation
    f32 unk10;
    f32 unk14;
    OMOBJ *unk18;
    s32 (*unk1C)(struct M528Player *); // state function
    s32 unk20; // step
    s32 unk24; // timer
    s16 unk28; // player
    s16 unk2A; // character
    s16 unk2C; // team
    s16 unk2E; // pad
    char pad30[4];
    s16 unk34; // com
    s16 unk36; // difficulty
    char pad38[2];
    s16 unk3A; // button held time
    s16 unk3C; // push strength
    s16 unk3E; // in the air
    f32 unk40; // top height
    f32 unk44; // start height
    f32 unk48; // fall speed
    struct M528Player *unk4C; // partner
    s16 unk50; // com state
    s16 unk52;
    s16 unk54;
    char pad56[2];
    M528Half *unk58;
} M528Player;

typedef struct M528Camera { // M528Work::unk20, 0x1C
    Vec unk0; // target
    f32 unkC; // y rotation
    f32 unk10; // x rotation
    f32 unk14; // distance
    s16 unk18; // step
    s16 unk1A; // timer
} M528Camera;

typedef struct M528Node { // effect list node, 0x10
    struct M528Node *unk0; // previous
    struct M528Node *unk4; // next
    s32 (*unk8)(struct M528Node *);
    struct M528Part *unkC;
} M528Node;

typedef struct M528Part { // effect particle, 0x38
    Vec unk0; // position
    Vec unkC; // rotation
    Vec unk18; // velocity
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    s16 unk30; // step
    s16 unk32; // timer
    s16 unk34;
    s16 unk36; // model
} M528Part;

typedef struct M528Rail { // camera-less walker along lbl_1_bss_4, 0x2C (4 in M528Work::unk4BE4)
    Vec unk0; // position
    Vec unkC; // rotation
    f32 unk18; // start angle
    f32 unk1C; // end angle
    s16 unk20; // model
    s16 unk22; // step
    s16 unk24; // timer
    s16 unk26; // point
    s16 unk28; // start delay
    s16 unk2A; // point count
} M528Rail;

typedef struct M528Work { // lbl_1_bss_298->data, 0x4D70
    M528Player *unk0[4];
    M528Player *unk10[2][2]; // by team
    M528Camera unk20;
    M528Team unk3C[2];
    M528Slice unk10C[0x10];
    s32 (*unk3CC)(M528Camera *); // camera move
    s32 (*unk3D0[2])(M528Team *); // per team
    s32 (*unk3D8)(M528Slice *);
    M528Node *unk3DC; // used nodes
    M528Node *unk3E0; // free nodes
    M528Node unk3E4[0x100];
    M528Part unk13E4[0x100];
    M528Rail unk4BE4[4];
    f32 unk4C94; // wheel speed
    f32 unk4C98; // wheel angle
    f32 unk4C9C;
    f32 unk4CA0;
    char pad4CA4[4];
    s16 unk4CA8[2]; // winning slices (per team)
    s16 unk4CAC; // step
    s16 unk4CAE; // timer
    s16 unk4CB0; // winning team (-1 none)
    s16 unk4CB2; // input enabled
    s16 unk4CB4[0x36]; // shared model ids
    s16 unk4D20[7]; // shared motion ids
    s16 unk4D2E[0x10];
    s16 unk4D4E[0x10];
    s16 unk4D6E;
} M528Work;

typedef struct M528CamKey { // lbl_1_data_2BC, 0x18
    Vec unk0; // target
    f32 unkC; // y rotation
    f32 unk10; // x rotation
    f32 unk14; // distance
} M528CamKey;

typedef struct M528Char { // MP5 motion data numbers, per MP5 character
    u32 unk0[8];
} M528Char;

extern OMOBJ *lbl_1_bss_298;
extern HUPROCESS *lbl_1_bss_29C;
extern s32 lbl_1_bss_0;
extern Vec lbl_1_bss_4[0x37];
extern MGSEQ_PARAM lbl_1_data_0;
extern M528Char lbl_1_data_28[0xD];
extern s32 lbl_1_data_1C8[0x36];
extern u32 lbl_1_data_2A0[7];
extern M528CamKey lbl_1_data_2BC[4];
extern Vec lbl_1_data_31C[0x37];
extern u16 lbl_1_rodata_10[4];
extern u16 lbl_1_rodata_18[4];
extern void (*lbl_1_rodata_78[8])(M528Work *);
extern s32 lbl_1_rodata_98[8];
extern Vec lbl_1_rodata_E0;
extern Vec lbl_1_rodata_EC;
extern Vec lbl_1_rodata_F8;
extern u16 lbl_1_rodata_108[4];
extern f32 lbl_1_rodata_120[2];
extern s32 lbl_1_rodata_130[8];
extern s32 lbl_1_rodata_150[8];
extern s32 lbl_1_rodata_170[8];
extern s32 lbl_1_rodata_190[8];
extern f32 lbl_1_rodata_1D8[2];
extern s16 lbl_1_rodata_210[2];
extern f32 lbl_1_rodata_218[2];
extern s32 lbl_1_rodata_248[8];

void ObjectSetup(void);
void fn_1_1E8(s16 mode, s16 frameNo);
void fn_1_238(s16 mode, s16 frameNo);
void fn_1_8E4(s16 mode, s16 frameNo);
void fn_1_954(s16 mode, s16 frameNo);
void fn_1_9CC(s16 mode, s16 frameNo);
void fn_1_B10(s16 mode, s16 frameNo);
void fn_1_ED0(s16 mode, s16 frameNo);
void fn_1_1118(s16 mode, s16 frameNo);
void fn_1_111C(s16 mode, s16 frameNo);
void fn_1_113C(OMOBJ *obj);
void fn_1_1368(OMOBJ *obj);
void fn_1_13D0(OMOBJ *obj);
void fn_1_1458(OMOBJ *obj);
void fn_1_1538(M528Work *work);
void fn_1_15EC(void);
void fn_1_16C4(void);
void fn_1_17B0(void);
void fn_1_1874(M528Work *work);
void fn_1_18E0(M528Work *work);
void fn_1_1918(M528Camera *cam);
void fn_1_198C(M528Camera *cam, s32 key);
void fn_1_1A20(M528Camera *cam);
void fn_1_1CAC(M528Work *work);
s32 fn_1_1DFC(M528Player *p);
s32 fn_1_1ECC(M528Player *p);
s32 fn_1_1F8C(M528Player *p);
s32 fn_1_2080(M528Player *p);
s32 fn_1_22B4(M528Player *p);
s32 fn_1_237C(M528Player *p);
s32 fn_1_2488(M528Player *p);
s32 fn_1_2564(M528Player *p);
s32 fn_1_25FC(M528Player *p);
s32 fn_1_2680(M528Player *p);
s32 fn_1_2704(M528Player *p);
s32 fn_1_2758(M528Player *p);
s32 fn_1_27AC(M528Player *p);
s32 fn_1_2A00(M528Player *p);
s16 fn_1_2C40(s16 power, s32 dif);
s16 fn_1_2D7C(M528Player *p);
s16 fn_1_2E3C(M528Player *p);
s32 fn_1_2EC0(M528Team *team);
void fn_1_32D0(M528Half *half);
void fn_1_3330(M528Work *work);
void fn_1_36DC(M528Slice *slice);
s32 fn_1_3750(M528Slice *slice, f32 speed);
void fn_1_38F8(M528Work *work);
void fn_1_3A00(M528Work *work);
s32 fn_1_3CA0(M528Camera *cam);
s32 fn_1_3EFC(M528Camera *cam);
s32 fn_1_4158(M528Camera *cam);
s32 fn_1_43B4(M528Camera *cam);
s32 fn_1_4540(M528Camera *cam);
void fn_1_46CC(M528Work *work);
s32 fn_1_47F0(M528Team *team);
s32 fn_1_495C(M528Team *team);
s32 fn_1_4B04(M528Slice *slice);
s32 fn_1_4C84(M528Slice *slice);
void fn_1_4E80(M528Work *work);
void fn_1_4F30(M528Work *work);
M528Node *fn_1_4FF4(M528Work *work, s32 (*func)(M528Node *), M528Part *part);
void fn_1_5048(M528Work *work, M528Node *node);
void fn_1_50B0(M528Work *work);
void fn_1_5194(void);
void fn_1_51A8(M528Work *work);
void fn_1_5BF8(M528Work *work);
void fn_1_6320(M528Work *work);
void fn_1_6410(M528Work *work);
void fn_1_654C(M528Work *work);
void fn_1_6688(M528Work *work);
void fn_1_67C4(M528Work *work);
void fn_1_6900(M528Work *work);
void fn_1_6A3C(M528Work *work);
void fn_1_6B78(M528Work *work);
void fn_1_6CB4(M528Work *work);
s32 fn_1_6DF0(M528Node *node);
s32 fn_1_72E4(M528Node *node);
s32 fn_1_7794(M528Node *node);
s32 fn_1_7B44(M528Node *node);
s32 fn_1_800C(M528Node *node);
s32 fn_1_83E4(M528Node *node);
s32 fn_1_87F4(M528Node *node);
s32 fn_1_8CD0(M528Node *node);
s32 fn_1_8FFC(M528Node *node);
s32 fn_1_97C8(M528Node *node);
s32 fn_1_9D5C(M528Node *node);
s32 fn_1_A3A0(M528Node *node);
s32 fn_1_ABAC(M528Node *node);
void fn_1_B384(M528Work *work);
void fn_1_B528(M528Rail *rail, s16 delay);
void fn_1_B6D4(M528Rail *rail);
void fn_1_C314(M528Work *work);
void fn_1_C3DC(M528Work *work);
void fn_1_C530(M528Work *work);
void fn_1_C728(M528Work *work);
void fn_1_C8B4(M528Work *work);
void fn_1_CA34(M528Work *work);
void fn_1_CAEC(M528Work *work);
void fn_1_CC40(M528Work *work);
