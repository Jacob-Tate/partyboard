// MP5 m528 (Mario Can-Can, 2 vs 2), generated from its m2c draft by tools/mp5/ports/m528dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
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
void fn_1_113C(omObjData *obj);
void fn_1_1368(omObjData *obj);
void fn_1_13D0(omObjData *obj);
void fn_1_1458(omObjData *obj);
void fn_1_1538(M528Work *work);
void fn_1_15EC();
void fn_1_16C4();
void fn_1_17B0();
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
void fn_1_50B0(M528Work *work);
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

MGSEQ_PARAM lbl_1_data_0 = {
    0x12C,
    0,
    fn_1_1E8,
    fn_1_238,
    fn_1_8E4,
    fn_1_954,
    fn_1_9CC,
    fn_1_B10,
    fn_1_ED0,
    fn_1_1118,
    fn_1_111C,
};
M528Char lbl_1_data_28[0xD] = {
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 3),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 4),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 8),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 10),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 9),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6),
            DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7),
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 7 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 7 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        },
    },
    {
        {
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 8 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 10 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 9 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
            0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        },
    },
};
s32 lbl_1_data_1C8[0x36] = {
    DATA_MAKE_NUM(DATADIR_MP5_M528, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 31),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 32),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 33),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 34),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 35),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 36),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 37),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 38),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 39),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 40),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 41),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 42),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 43),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 44),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 45),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 46),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 47),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 48),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 49),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 51),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 53),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 55),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 56),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 57),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 58),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 59),
    DATA_MAKE_NUM(DATADIR_MP5_M528, 60),
};
u32 lbl_1_data_2A0[7] = { DATA_MAKE_NUM(DATADIR_MP5_M528, 11), DATA_MAKE_NUM(DATADIR_MP5_M528, 12), DATA_MAKE_NUM(DATADIR_MP5_M528, 15), DATA_MAKE_NUM(DATADIR_MP5_M528, 16), DATA_MAKE_NUM(DATADIR_MP5_M528, 50), DATA_MAKE_NUM(DATADIR_MP5_M528, 52), DATA_MAKE_NUM(DATADIR_MP5_M528, 54) };
M528CamKey lbl_1_data_2BC[4] = {
    { { 0.0f, 717.0f, 0.0f }, 90.0f, 37.0f, 8680.0f },
    { { 0.0f, 124.0f, 0.0f }, 90.0f, 26.0f, 3810.0f },
    { { -300.0f, 124.0f, 0.0f }, 90.0f, 21.0f, 3810.0f },
    { { 300.0f, 124.0f, 0.0f }, 90.0f, 21.0f, 3810.0f },
};
Vec lbl_1_data_31C[0x37] = {
    { 76.3527f, -28.65594f, 303.8886f },
    { 89.36818f, -20.12116f, 627.3725f },
    { 132.45467f, -7.8856f, 617.07947f },
    { 175.47755f, 5.14328f, 603.90344f },
    { 213.52226f, 19.1923f, 583.2219f },
    { 258.0741f, 35.48818f, 558.334f },
    { 307.4178f, 53.50759f, 528.4491f },
    { 351.7477f, 71.07372f, 488.91357f },
    { 387.29947f, 86.45116f, 453.47565f },
    { 423.9798f, 102.31677f, 416.9127f },
    { 453.92682f, 114.74768f, 374.23383f },
    { 482.55255f, 128.153f, 327.6315f },
    { 506.63617f, 140.91176f, 280.20404f },
    { 523.21515f, 149.26572f, 234.10138f },
    { 536.4226f, 157.65977f, 186.78319f },
    { 545.4938f, 165.1289f, 144.12125f },
    { 550.5082f, 169.3213f, 99.43111f },
    { 555.52264f, 173.5137f, 54.74098f },
    { 554.31415f, 178.93967f, 10.26389f },
    { 548.245f, 182.21725f, -43.50827f },
    { 540.7429f, 184.87166f, -94.25285f },
    { 526.2494f, 189.22081f, -148.9162f },
    { 508.16705f, 190.19507f, -199.4755f },
    { 485.3958f, 191.22429f, -246.7632f },
    { 455.54944f, 191.06044f, -297.0153f },
    { 422.8942f, 189.8421f, -342.977f },
    { 387.02106f, 188.64108f, -381.5805f },
    { 347.565f, 184.92625f, -416.4199f },
    { 297.2428f, 181.25046f, -457.2818f },
    { 241.78398f, 175.96623f, -490.8356f },
    { 182.54707f, 170.04622f, -518.3706f },
    { 126.37634f, 165.11037f, -538.3222f },
    { 64.86789f, 158.29259f, -552.0461f },
    { 5.82033f, 152.42786f, -559.9274f },
    { -56.36307f, 144.40205f, -559.3981f },
    { -127.3225f, 136.82695f, -552.8494f },
    { -175.3741f, 132.81107f, -542.1f },
    { -219.185f, 128.13605f, -528.8677f },
    { -271.0152f, 123.20982f, -509.1224f },
    { -328.317f, 119.05633f, -478.0202f },
    { -383.0389f, 115.4856f, -437.4594f },
    { -429.5695f, 112.6725f, -396.8103f },
    { -477.0712f, 112.08831f, -339.5657f },
    { -511.2278f, 113.79501f, -290.2382f },
    { -544.9306f, 114.67406f, -219.9456f },
    { -565.2117f, 118.71691f, -148.9897f },
    { -576.6864f, 124.72604f, -55.24234f },
    { -571.7904f, 132.87604f, 20.97713f },
    { -559.52f, 138.74858f, 81.16179f },
    { -541.5015f, 145.87262f, 143.0994f },
    { -516.2133f, 150.99301f, 190.12534f },
    { -486.0693f, 159.3626f, 235.53607f },
    { -453.4974f, 169.35678f, 280.1392f },
    { -419.3569f, 178.96738f, 310.31488f },
    { -205.5353f, 173.01883f, 111.80605f },
};
s32 lbl_1_bss_0;
Vec lbl_1_bss_4[0x37];
omObjData *lbl_1_bss_298;
HUPROCESS *lbl_1_bss_29C;
u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };            /* const */
u16 lbl_1_rodata_18[4] = { 2, 0xD, 0x19, 0x27 };    /* const */
void (*lbl_1_rodata_78[8])(M528Work *) = {
    fn_1_C314,
    fn_1_C3DC,
    fn_1_C530,
    fn_1_C728,
    fn_1_C8B4,
    fn_1_CA34,
    fn_1_CAEC,
    fn_1_CC40,
}; /* const */
s32 lbl_1_rodata_98[8] = { 1, 1, 1, 1, 1, 0, 1, 0 }; /* const */
Vec lbl_1_rodata_E0 = { 0.0f, 1.0f, 0.0f };     /* const */
Vec lbl_1_rodata_EC = { 0.0f, 4000.0f, 1000.0f }; /* const */
Vec lbl_1_rodata_F8 = { 0.0f, 0.0f, 0.0f };     /* const */
u16 lbl_1_rodata_108[4] = { 0x28, 0x38, 0x48, 0x58 }; /* const */
f32 lbl_1_rodata_120[2] = { 25.0f, 39.0f };         /* const */
s32 lbl_1_rodata_130[8] = { 0x32, 0x50, 0x5F, 0x63, 0x19, 0xF, 0xA, 5 }; /* const */
s32 lbl_1_rodata_150[8] = { 0xA, 5, 0, 0, 0xA, 5, 0, 0 }; /* const */
s32 lbl_1_rodata_170[8] = { 0x1E, 0x3C, 0x37, 0x32, 0x1E, 0x3C, 0x37, 0x32 }; /* const */
s32 lbl_1_rodata_190[8] = { 0x50, 0x55, 0x5A, 0x5F, 0x50, 0x55, 0x5A, 0x5F }; /* const */
f32 lbl_1_rodata_1D8[2] = { 1.0f, -1.0f };          /* const */
s16 lbl_1_rodata_210[2];                            /* unable to generate initializer: not enough data; const */
f32 lbl_1_rodata_218[2];                            /* unable to generate initializer: not enough data; const */
s32 lbl_1_rodata_248[8] = { 0x14, 0x14, 0xF, 0xF, 0xA, 0xA, 7, 3 }; /* const */



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

void ObjectSetup(void) {
    omObjData *temp_r31;
    omObjData *temp_r3;
    s32 var_r30;
    M528Work *temp_r29;

    lbl_1_bss_29C = omInitObjMan(0xA, 0x2000);
    omGameSysInit(lbl_1_bss_29C);
    temp_r3 = omAddObjEx(lbl_1_bss_29C, 0x65, 0U, 0U, -1, fn_1_13D0);
    lbl_1_bss_298 = temp_r3;
    temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M528Work), MEMORY_DEFAULT_NUM);
    temp_r29 = temp_r3->data;
    fn_1_16C4();
    fn_1_15EC();
    fn_1_17B0();
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        temp_r31 = omAddObjEx(lbl_1_bss_29C, 0x64, 1U, 8U, 0, fn_1_113C);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M528Player), MEMORY_DEFAULT_NUM);
        temp_r31->work[0] = (u32) var_r30;
        var_r30 += 1;
        goto loop_2;
    }
    fn_1_1538((M528Work *) temp_r29);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DNoSyncSet(1);
    MgSeqCreate(&lbl_1_data_0);
}

void fn_1_1E8(s16 mode, s16 frameNo) {
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    temp_r31->unk4CAC = 0;
    temp_r31->unk4CA8[0] = -1;
    temp_r31->unk4CA8[1] = -1;
    MgSeqModeNext();
}

void fn_1_238(s16 mode, s16 frameNo) {
    u16 sp8[4];
    s16 temp_r0;
    s32 var_r30;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r3_4;
    M528Player *temp_r29;
    M528Work *temp_r31;

    sp8[0] = lbl_1_rodata_18[0];
    sp8[1] = lbl_1_rodata_18[1];
    sp8[2] = lbl_1_rodata_18[2];
    sp8[3] = lbl_1_rodata_18[3];
    temp_r31 = lbl_1_bss_298->data;
    temp_r0 = temp_r31->unk4CAC;
    if ((u32) temp_r0 <= 8U) {
        switch (temp_r0) {
        case 0:
            MgSeqModeChangeOff();
            temp_r31->unk4C98 = 0.0f;
            temp_r31->unk4CAE = 0;
            temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            /* fallthrough */
        case 1:
            temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
            if ((s16) temp_r31->unk4CAE >= 0x3C) {
                temp_r31->unk4C94 = (f32) (3.0f + ((f32) frandmod(0x64U) / 100.0f));
                temp_r31->unk4CAE = 0;
                HuAudFXPlay(0x786);
                HuAudFXPlay(0x78E);
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            }
            break;
        case 2:
            temp_r31->unk4C9C = (f32) (0.5 * ((f64) temp_r31->unk4C94 * (1.0 + cos((3.141592653589793 * (f64) ((180.0f * ((f32) temp_r31->unk4CAE / 60.0f)) - 180.0f)) / 180.0))));
            temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 - temp_r31->unk4C9C);
            if (temp_r31->unk4C98 < 0.0f) {
                temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 + 360.0f);
            }
            if ((s16) temp_r31->unk4CAE == 0x32) {
                temp_r31->unk3CC = fn_1_3CA0;
            }
            temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
            if ((s16) temp_r31->unk4CAE > 0x3C) {
                temp_r31->unk4CAE = 0;
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            }
            break;
        case 3:
            temp_r31->unk4C9C = (f32) (0.20000000298023224 + (0.5 * ((f64) temp_r31->unk4C94 * (1.0 + cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unk4CAE / 120.0f))) / 180.0)))));
            temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 - temp_r31->unk4C9C);
            if (temp_r31->unk4C98 < 0.0f) {
                temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 + 360.0f);
            }
            temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
            if ((s16) temp_r31->unk4CAE >= 0x78) {
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
                temp_r31->unk4CA0 = (f32) (22.5f * (f32) (s32) (temp_r31->unk4C98 / 22.5f));
            }
            break;
        case 4:
            temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 - temp_r31->unk4C9C);
            if (temp_r31->unk4C98 <= temp_r31->unk4CA0) {
                temp_r31->unk4C98 = (f32) temp_r31->unk4CA0;
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            }
            break;
        case 5:
            if (temp_r31->unk4C98 < 0.0f) {
                temp_r31->unk4C98 = (f32) (temp_r31->unk4C98 + 360.0f);
            }
            temp_r3 = 0x10 - (s32) (temp_r31->unk4C98 / 22.5f);
            temp_r3_2 = temp_r3 >> 0x1FU;
            temp_r0_2 = (temp_r3 << 0x1C) - temp_r3_2;
            temp_r31->unk4CA8[0] = (s16) ((temp_r3 % 16));
            temp_r3_3 = temp_r31->unk4CA8[0] + 1;
            temp_r3_4 = temp_r3_3 >> 0x1FU;
            temp_r0_3 = (temp_r3_3 << 0x1C) - temp_r3_4;
            temp_r31->unk4CA8[1] = (s16) ((temp_r3_3 % 16));
            temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            temp_r31->unk4CAE = 0;
            fn_1_46CC((M528Work *) temp_r31);
            break;
        case 6:
            temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
            if ((s16) temp_r31->unk4CAE == 1) {
                temp_r31->unk3D0[0] = fn_1_47F0;
            }
            if ((s16) temp_r31->unk4CAE == 5) {
                temp_r31->unk3D0[1] = fn_1_47F0;
            }
            if ((s16) temp_r31->unk4CAE >= 8) {
                fn_1_B384((M528Work *) temp_r31);
                temp_r31->unk4BE4[0].unk22 = (s16) (temp_r31->unk4BE4[0].unk22 + 1);
                temp_r31->unk4BE4[1].unk22 = (s16) (temp_r31->unk4BE4[1].unk22 + 1);
                temp_r31->unk4BE4[2].unk22 = (s16) (temp_r31->unk4BE4[2].unk22 + 1);
                temp_r31->unk4BE4[3].unk22 = (s16) (temp_r31->unk4BE4[3].unk22 + 1);
                temp_r31->unk4CAE = 0;
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            }
            break;
        case 7:
            temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
            var_r30 = 0;
loop_30:
            if (var_r30 < 4) {
                if ((s16) temp_r31->unk4CAE == (s16) sp8[var_r30]) {
                    temp_r29 = temp_r31->unk0[var_r30];
                    temp_r29->unk20 = 0;
                    temp_r29->unk1C = fn_1_1ECC;
                }
                var_r30 += 1;
                goto loop_30;
            }
            if ((s16) temp_r31->unk4CAE >= 0x28) {
                temp_r31->unk4CAE = 0;
                temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
            }
            break;
        case 8:
            lbl_1_bss_0 = HuAudBGMPlay(0x3C);
            MgSeqModeNext();
            break;
        }
    }
    fn_1_3A00((M528Work *) temp_r31);
    if ((((s32 (*)(M528Camera *)) temp_r31->unk3CC) != NULL) && (temp_r31->unk3CC(&temp_r31->unk20) != 0)) {
        temp_r31->unk3CC = NULL;
    }
    if ((((s32 (*)(M528Team *)) temp_r31->unk3D0[0]) != NULL) && (temp_r31->unk3D0[0](&temp_r31->unk3C[0]) != 0)) {
        HuAudFXPlay(0x787);
        temp_r31->unk3CC = fn_1_43B4;
        temp_r31->unk20.unk18 = 0;
        temp_r31->unk3D0[0] = NULL;
    }
    if ((((s32 (*)(M528Team *)) temp_r31->unk3D0[1]) != NULL) && (temp_r31->unk3D0[1](&temp_r31->unk3C[1]) != 0)) {
        HuAudFXPlay(0x788);
        temp_r31->unk3D0[1] = NULL;
    }
}

void fn_1_8E4(s16 mode, s16 frameNo) {
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    if ((((s32 (*)(void *)) temp_r31->unk3CC) != NULL) && (temp_r31->unk3CC(&temp_r31->unk20) != 0)) {
        temp_r31->unk3CC = NULL;
    }
    temp_r31->unk4CAC = 0;
    temp_r31->unk4D6E = 0;
}

void fn_1_954(s16 mode, s16 frameNo) {
    M528Slice *temp_r3;
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    temp_r31->unk4CB2 = 1;
    if ((s16) temp_r31->unk4CB0 >= 0) {
        temp_r31->unk3D8 = fn_1_4C84;
        temp_r3 = temp_r31->unk3C[temp_r31->unk4CB0].unk54;
        temp_r3->unk26 = 0;
        temp_r31->unk4CB2 = 0;
        MgSeqModeNext();
    }
}

void fn_1_9CC(s16 mode, s16 frameNo) {
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    temp_r31->unk4CB2 = 0;
    if ((s16) temp_r31->unk4D6E == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0, 0x3E8);
        temp_r31->unk4D6E = (s16) (temp_r31->unk4D6E + 1);
    }
    if ((s16) temp_r31->unk4CB0 < 0) {
        MgSeqWinnerSet(-1, -1, -1, -1);
    } else {
        MgSeqWinnerSet((temp_r31->unk10[temp_r31->unk4CB0][0])->unk2A, (temp_r31->unk10[temp_r31->unk4CB0][1])->unk2A, -1, -1);
        fn_1_4E80((M528Work *) temp_r31);
        temp_r31->unk3D0[temp_r31->unk4CB0 ^ 1] = fn_1_495C;
        temp_r31->unk3C[temp_r31->unk4CB0 ^ 1].unk62 = 0;
    }
    if ((((s32 (*)(s32)) temp_r31->unk3D8) != NULL) && (temp_r31->unk3D8(temp_r31->unk3C[temp_r31->unk4CB0].unk54) != 0)) {
        temp_r31->unk3D8 = NULL;
    }
}

void fn_1_B10(s16 mode, s16 frameNo) {
    s32 sp8[8];
    s16 temp_r0;
    s32 (*var_r27)(M528Camera *);
    s32 temp_r29;
    s32 temp_r4;
    s32 var_r30;
    M528Work *temp_r31;

    sp8[0] = lbl_1_rodata_98[0];
    sp8[1] = lbl_1_rodata_98[1];
    sp8[2] = lbl_1_rodata_98[2];
    sp8[3] = lbl_1_rodata_98[3];
    sp8[4] = lbl_1_rodata_98[4];
    sp8[5] = lbl_1_rodata_98[5];
    sp8[6] = lbl_1_rodata_98[6];
    sp8[7] = lbl_1_rodata_98[7];
    temp_r31 = lbl_1_bss_298->data;
    temp_r0 = temp_r31->unk4CAC;
    switch (temp_r0) {                              /* irregular */
    case 0:
        MgSeqModeChangeOff();
        if ((s16) temp_r31->unk4CB0 >= 0) {
            if ((s16) temp_r31->unk4CB0 != 0) {
                var_r27 = fn_1_4158;
            } else {
                var_r27 = fn_1_3EFC;
            }
            temp_r31->unk3CC = var_r27;
        }
        temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        /* fallthrough */
    case 1:
        if (((s32 (*)(M528Camera *)) temp_r31->unk3CC) == NULL) {
            temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        }
        break;
    case 2:
        var_r30 = 0;
loop_20:
        if (var_r30 < 4) {
            if ((temp_r31->unk0[var_r30])->unk1C == fn_1_1F8C) {
                var_r30 += 1;
                goto loop_20;
            }
        }
        if (var_r30 == 4) {
            temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        }
        break;
    case 3:
        if ((s16) temp_r31->unk4CB0 >= 0) {
            temp_r31->unk3D8 = fn_1_4B04;
            (temp_r31->unk3C[temp_r31->unk4CB0].unk54)->unk26 = 0;
            omVibrate((temp_r31->unk10[temp_r31->unk4CB0][0])->unk28, 0xC, 0xC, 0);
            omVibrate((temp_r31->unk10[temp_r31->unk4CB0][1])->unk28, 0xC, 0xC, 0);
        }
        temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        break;
    case 4:
        if ((s16) temp_r31->unk4CB0 >= 0) {
            lbl_1_rodata_78[(temp_r31->unk3C[temp_r31->unk4CB0].unk54)->unk2A]((M528Work *) temp_r31);
            if ((s32) sp8[(temp_r31->unk3C[temp_r31->unk4CB0].unk54)->unk2A] != 0) {
                HuAudFXPlay(0x78C);
            }
            if ((s16) (temp_r31->unk3C[temp_r31->unk4CB0].unk54)->unk2A == 7) {
                HuAudFXPlay(0x78D);
            }
        }
        temp_r31->unk4CAE = 0;
        temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        break;
    case 5:
        temp_r31->unk4CAE = (s16) (temp_r31->unk4CAE + 1);
        if ((s16) temp_r31->unk4CAE > 0x1E) {
            MgSeqModeNext();
            temp_r31->unk4CAC = 0;
        }
        break;
    }
    if ((((s32 (*)(M528Camera *)) temp_r31->unk3CC) != NULL) && (temp_r31->unk3CC(&temp_r31->unk20) != 0)) {
        temp_r31->unk3CC = NULL;
    }
    if ((((s32 (*)(M528Slice *)) temp_r31->unk3D8) != NULL) && (temp_r31->unk3D8(temp_r31->unk3C[temp_r31->unk4CB0].unk54) != 0)) {
        temp_r31->unk3D8 = NULL;
    }
    if ((s16) temp_r31->unk4CB0 >= 0) {
        temp_r29 = temp_r31->unk4CB0 ^ 1;
        if (temp_r31->unk3D0[temp_r29] != NULL) {
            temp_r4 = temp_r29 * 4;
            if (temp_r31->unk3D0[temp_r29](&temp_r31->unk3C[temp_r29]) != 0) {
                temp_r31->unk3D0[temp_r29] = 0;
            }
        }
    }
}

void fn_1_ED0(s16 mode, s16 frameNo) {
    s16 temp_r0;
    s16 temp_r27;
    s16 temp_r28;
    s32 var_r29;
    s32 var_r29_2;
    M528Player *temp_r30;
    M528Player *temp_r30_2;
    M528Player *temp_r30_3;
    M528Player *temp_r30_4;
    M528Player *temp_r30_5;
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    temp_r0 = temp_r31->unk4CAC;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        if ((s16) temp_r31->unk4CB0 < 0) {
            CharLoseVoicePlay(temp_r31->unk0[0]->unk2A, temp_r31->unk0[1]->unk2A, temp_r31->unk0[2]->unk2A, temp_r31->unk0[3]->unk2A);
            var_r29 = 0;
loop_7:
            if (var_r29 < 4) {
                temp_r30 = temp_r31->unk0[var_r29];
                temp_r30->unk1C = fn_1_25FC;
                temp_r30->unk20 = 0;
                var_r29 += 1;
                goto loop_7;
            }
        } else {
            var_r29_2 = 0;
loop_18:
            if (var_r29_2 < 2) {
                if (var_r29_2 == (s16) temp_r31->unk4CB0) {
                    temp_r30_2 = temp_r31->unk10[var_r29_2][0];
                    temp_r30_2->unk1C = fn_1_2680;
                    temp_r30_2->unk20 = 0;
                    temp_r28 = temp_r30_2->unk28;
                    if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                        GWPlayer[temp_r28].coin_win = 0xA;
                    }
                    CharModelVoicePanSet(temp_r30_2->unk2A, 0x40);
                    temp_r30_3 = temp_r31->unk10[var_r29_2][1];
                    temp_r30_3->unk1C = fn_1_2680;
                    temp_r30_3->unk20 = 0;
                    temp_r27 = temp_r30_3->unk28;
                    if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                        GWPlayer[temp_r27].coin_win = 0xA;
                    }
                    CharModelVoicePanSet(temp_r30_3->unk2A, 0x40);
                } else {
                    temp_r30_4 = temp_r31->unk10[var_r29_2][0];
                    temp_r30_4->unk1C = fn_1_25FC;
                    temp_r30_4->unk20 = 0;
                    temp_r30_5 = temp_r31->unk10[var_r29_2][1];
                    temp_r30_5->unk1C = fn_1_25FC;
                    temp_r30_5->unk20 = 0;
                }
                var_r29_2 += 1;
                goto loop_18;
            }
        }
        temp_r31->unk4CAC = (s16) (temp_r31->unk4CAC + 1);
        break;
    }
    if ((((s32 (*)(s32)) temp_r31->unk3D8) != NULL) && (temp_r31->unk3D8(temp_r31->unk3C[temp_r31->unk4CB0].unk54) != 0)) {
        temp_r31->unk3D8 = NULL;
    }
    if ((((s32 (*)(void *)) temp_r31->unk3CC) != NULL) && (temp_r31->unk3CC(&temp_r31->unk20) != 0)) {
        temp_r31->unk3CC = NULL;
    }
}

void fn_1_1118(s16 mode, s16 frameNo) {

}

void fn_1_111C(s16 mode, s16 frameNo) {
    M528Work *sp8;

    sp8 = lbl_1_bss_298->data;
}

void fn_1_113C(omObjData *obj) {
    s32 temp_r29;
    s32 var_r29;
    M528Work *temp_r28;
    M528Player *temp_r31;

    temp_r31 = obj->data;
    temp_r28 = lbl_1_bss_298->data;
    temp_r31->unk28 = (s16) obj->work[0];
    temp_r31->unk2A = (s16) GWPlayerCfg[temp_r31->unk28].character;
    temp_r31->unk2C = (s16) Mp5TeamNo(temp_r31->unk28);
    temp_r31->unk2E = (s16) GWPlayerCfg[temp_r31->unk28].pad_idx;
    temp_r31->unk34 = (s16) GWPlayerCfg[temp_r31->unk28].iscom;
    temp_r31->unk36 = (s16) GWPlayerCfg[temp_r31->unk28].diff;
    temp_r31->unk18 = obj;
    temp_r28->unk0[temp_r31->unk28] = temp_r31;
    temp_r29 = temp_r28->unk10[temp_r31->unk2C][0] != 0;
    temp_r28->unk10[temp_r31->unk2C][temp_r29] = temp_r31;
    temp_r31->unk58 = &temp_r28->unk3C[temp_r31->unk2C].unk0[temp_r29];
    *obj->model = CharModelCreate(temp_r31->unk2A, 2);
    var_r29 = 0;
loop_2:
    if (var_r29 < 8) {
        obj->motion[var_r29] = Mp5CharMotionCreateData(temp_r31->unk2A, lbl_1_data_28[Mp5CharNo(temp_r31->unk2A)].unk0[var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionSet(temp_r31->unk2A, *obj->motion);
    CharModelAttrSet(temp_r31->unk2A, 0x40000001U);
    Hu3DModelLayerSet(*obj->model, 2);
    Hu3DModelShadowSet(*obj->model);
    CharEffectLayerSet(3);
    CharMotionDataClose(temp_r31->unk2A);
    temp_r31->unk1C = fn_1_1DFC;
    temp_r31->unk20 = 0;
    temp_r31->unk3E = 0;
    temp_r31->unk50 = 0;
    obj->func = fn_1_1368;
}

void fn_1_1368(omObjData *obj) {
    M528Work *sp8;
    M528Player *temp_r31;

    temp_r31 = obj->data;
    sp8 = lbl_1_bss_298->data;
    if (((s32 (*)(M528Player *)) temp_r31->unk1C) != NULL) {
        temp_r31->unk1C(temp_r31);
    }
}


void fn_1_13D0(omObjData *obj) {
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    fn_1_51A8((M528Work *) temp_r31);
    fn_1_1918(&temp_r31->unk20);
    fn_1_198C(&temp_r31->unk20, 0);
    fn_1_1CAC((M528Work *) temp_r31);
    fn_1_38F8((M528Work *) temp_r31);
    fn_1_4F30((M528Work *) temp_r31);
    fn_1_6320((M528Work *) temp_r31);
    obj->func = fn_1_1458;
}

void fn_1_1458(omObjData *obj) {
    s32 temp_r29;
    s32 temp_r30;
    M528Work *temp_r31;

    temp_r31 = lbl_1_bss_298->data;
    temp_r30 = fn_1_2EC0(&temp_r31->unk3C[0]);
    temp_r29 = fn_1_2EC0(&temp_r31->unk3C[1]);
    if ((temp_r30 != 0) && (temp_r29 != 0)) {
        temp_r31->unk4CB0 = frandmod(2U);
    } else if (temp_r30 != 0) {
        temp_r31->unk4CB0 = 0;
    } else if (temp_r29 != 0) {
        temp_r31->unk4CB0 = 1;
    }
    fn_1_1A20(&temp_r31->unk20);
    fn_1_3330((M528Work *) temp_r31);
    fn_1_B6D4(&temp_r31->unk4BE4[0]);
    fn_1_B6D4(&temp_r31->unk4BE4[1]);
    fn_1_B6D4(&temp_r31->unk4BE4[2]);
    fn_1_B6D4(&temp_r31->unk4BE4[3]);
    fn_1_50B0((M528Work *) temp_r31);
}


void fn_1_1538(M528Work *work) {
    s32 var_r30;

    work->unk4CB2 = 0;
    work->unk4CB0 = -1;
    fn_1_1874(work);
    fn_1_18E0(work);
    var_r30 = 0;
loop_2:
    if (var_r30 < 0x10) {
        fn_1_36DC(&work->unk10C[var_r30]);
        var_r30 += 1;
        goto loop_2;
    }
    work->unk10[0][0] = NULL;
    work->unk10[0][1] = NULL;
    work->unk10[1][0] = NULL;
    work->unk10[1][1] = NULL;
    work->unk3CC = NULL;
    work->unk3D0[0] = NULL;
    work->unk3D0[1] = NULL;
    work->unk3D8 = NULL;
}

void fn_1_15EC() {
    s16 temp_r3;

    temp_r3 = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -0.5f, 0xFFU, 0xFFU, 0xFFU);
    Hu3DGLightPosAimSet(temp_r3, 0.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(temp_r3);
}

void fn_1_16C4() {
    f32 sp8;

    Hu3DCameraCreate((s32) *lbl_1_rodata_10);
    Hu3DCameraPerspectiveSet((s32) *lbl_1_rodata_10, 15.0f, 20.0f, 20000.0f, 1.2f);
    sp8 = 0.0f;
    Hu3DCameraPosSet((s32) *lbl_1_rodata_10, 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, 0.0f);
}

void fn_1_17B0() {
    Vec sp8;
    Vec sp20;
    Vec sp14;

    sp20.x = lbl_1_rodata_E0.x;
    sp20.y = lbl_1_rodata_E0.y;
    sp20.z = lbl_1_rodata_E0.z;
    sp14.x = lbl_1_rodata_EC.x;
    sp14.y = lbl_1_rodata_EC.y;
    sp14.z = lbl_1_rodata_EC.z;
    sp8.x = lbl_1_rodata_F8.x;
    sp8.y = lbl_1_rodata_F8.y;
    sp8.z = lbl_1_rodata_F8.z;
    Hu3DShadowCreate(15.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&sp14, &sp20, &sp8);
}

void fn_1_1874(M528Work *work) {
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x36) {
        work->unk4CB4[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 0x10) {
        work->unk4D2E[var_r31_2] = -1;
        work->unk4D4E[var_r31_2] = -1;
        var_r31_2 += 1;
        goto loop_5;
    }
}

void fn_1_18E0(M528Work *work) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 7) {
        work->unk4D20[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_1918(M528Camera *cam) {
    cam->unkC = 0.0f;
    cam->unk10 = 0.0f;
    cam->unk14 = 1000.0f;
    cam->unk0.x = 0.0f;
    cam->unk0.y = 0.0f;
    cam->unk0.z = 0.0f;
    cam->unk18 = 0;
    cam->unk1A = 0;
}

void fn_1_198C(M528Camera *cam, s32 key) {
    cam->unkC = lbl_1_data_2BC[key].unkC;
    cam->unk10 = lbl_1_data_2BC[key].unk10;
    cam->unk14 = lbl_1_data_2BC[key].unk14;
    cam->unk0.x = lbl_1_data_2BC[key].unk0.x;
    cam->unk0.y = lbl_1_data_2BC[key].unk0.y;
    cam->unk0.z = lbl_1_data_2BC[key].unk0.z;
}

void fn_1_1A20(M528Camera *cam) {
    f32 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f64 temp_f28;
    f64 temp_f28_2;

    if (cam->unkC > 360.0f) {
        cam->unkC -= 360.0f;
    }
    if (cam->unkC < 0.0f) {
        cam->unkC += 360.0f;
    }
    if (cam->unk10 > 360.0f) {
        cam->unk10 -= 360.0f;
    }
    if (cam->unk10 < 0.0f) {
        cam->unk10 += 360.0f;
    }
    temp_f28 = cos((3.141592653589793 * (f64) cam->unkC) / 180.0);
    temp_f31 = (f32) ((f64) cam->unk0.x + ((f64) cam->unk14 * cos((3.141592653589793 * (f64) cam->unk10) / 180.0) * temp_f28));
    temp_f30 = (f32) ((f64) cam->unk0.y + ((f64) cam->unk14 * sin((3.141592653589793 * (f64) cam->unk10) / 180.0)));
    temp_f28_2 = sin((3.141592653589793 * (f64) cam->unkC) / 180.0);
    temp_f29 = (f32) ((f64) cam->unk0.z + ((f64) cam->unk14 * cos((3.141592653589793 * (f64) cam->unk10) / 180.0) * temp_f28_2));
    sp8 = cam->unk0.z;
    Hu3DCameraPosSet((s32) *lbl_1_rodata_10, temp_f31, temp_f30, temp_f29, 0.0f, 1.0f, 0.0f, cam->unk0.x, cam->unk0.y, cam->unk0.z);
}

void fn_1_1CAC(M528Work *work) {
    u16 spE;
    u16 spC;
    u16 spA;
    u16 sp8;
    s32 var_r29;
    s32 var_r30;
    M528Player *temp_r31;

    sp8 = lbl_1_rodata_108[0];
    spA = lbl_1_rodata_108[1];
    spC = lbl_1_rodata_108[2];
    spE = lbl_1_rodata_108[3];
    var_r30 = 0;
loop_5:
    if (var_r30 < 2) {
        var_r29 = 0;
loop_3:
        if (var_r29 < 2) {
            temp_r31 = work->unk10[var_r30][var_r29];
            temp_r31->unk0 = (f32) temp_r31->unk58->unk4;
            temp_r31->unk4 = 2501.0f;
            temp_r31->unk8 = (f32) (75.0f + temp_r31->unk58->unkC);
            temp_r31->unkC = 0.0f;
            temp_r31->unk10 = 0.0f;
            temp_r31->unk14 = 0.0f;
            omSetTra(temp_r31->unk18, temp_r31->unk0, temp_r31->unk4, temp_r31->unk8);
            omSetRot(temp_r31->unk18, temp_r31->unkC, temp_r31->unk10, temp_r31->unk14);
            CharModelVoicePanSet(temp_r31->unk2A, lbl_1_rodata_108[var_r30 * 2 + var_r29]);
            var_r29 += 1;
            goto loop_3;
        }
        var_r30 += 1;
        goto loop_5;
    }
}

s32 fn_1_1DFC(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        CharMotionSet(p->unk2A, p->unk18->motion[1]);
        CharModelAttrReset(p->unk2A, 0x40000001U);
        CharModelAttrSet(p->unk2A, 0x40000002U);
        p->unk20 += 1;
        break;
    case 1:
        CharMotionTimeSet(p->unk2A, CharMotionMaxTimeGet(p->unk2A));
        CharModelAttrReset(p->unk2A, 0x40000002U);
        p->unk20 += 1;
        break;
    }
    return 0;
}

s32 fn_1_1ECC(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk4 = 1000.0f;
        p->unk44 = 0.0f;
        p->unk40 = 200.0f;
        p->unk24 = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        p->unk24 += 1;
        p->unk4 -= 2.4f * (f32) p->unk24;
        break;
    }
    return 0;
}

s32 fn_1_1F8C(M528Player *p) {
    s32 temp_r0;
    s32 var_r30;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk58->unk14 = 1.0f;
        p->unk3E = 1;
        p->unk3A = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        if ((s16) p->unk34 != 0) {
            var_r30 = fn_1_27AC(p);
        } else {
            var_r30 = fn_1_2704(p);
        }
        if (var_r30 != 0) {
            CharMotionShiftSet(p->unk2A, p->unk18->motion[1], 0.0f, 3.0f, 0U);
            p->unk20 = 0;
            p->unk1C = fn_1_2080;
        }
        break;
    }
    return 0;
}

s32 fn_1_2080(M528Player *p) {
    f32 sp8[2];
    s32 temp_r0;
    s32 var_r30;

    sp8[0] = lbl_1_rodata_120[0];
    sp8[1] = lbl_1_rodata_120[1];
    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk24 = 0;
        p->unk3A = 0;
        p->unk3C = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        if ((s16) p->unk34 != 0) {
            p->unk3C = fn_1_2E3C(p);
        } else {
            p->unk3C = fn_1_2D7C(p);
        }
        p->unk24 += 1;
        if ((s32) p->unk24 == 6) {
            p->unk24 = 0;
            p->unk20 += 1;
        }
        break;
    case 2:
        p->unk3E = 0;
        p->unk58->unk14 = 0.0f;
        p->unk40 = p->unk4;
        p->unk44 = p->unk4;
        p->unk48 = 0.0f;
        p->unk20 += 1;
        /* fallthrough */
    case 3:
        p->unk24 += 1;
        p->unk4 += sp8[p->unk3C] - (2.4f * (f32) p->unk24);
        if (p->unk4 > p->unk40) {
            p->unk40 = p->unk4;
        }
        if ((s16) p->unk34 != 0) {
            var_r30 = fn_1_2A00(p);
        } else {
            var_r30 = fn_1_2758(p);
        }
        if (var_r30 != 0) {
            p->unk40 = p->unk4;
            CharMotionShiftSet(p->unk2A, p->unk18->motion[3], 0.0f, 3.0f, 0U);
            p->unk20 = 0;
            p->unk1C = fn_1_237C;
        }
        break;
    }
    return 0;
}

s32 fn_1_22B4(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk24 = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        p->unk24 += 1;
        if ((s32) p->unk24 == 9) {
            CharMotionShiftSet(p->unk2A, *p->unk18->motion, 0.0f, 3.0f, 0x40000001U);
        }
        if ((s32) p->unk24 >= 0xC) {
            p->unk20 = 0;
            p->unk1C = fn_1_1F8C;
        }
        break;
    }
    return 0;
}

s32 fn_1_237C(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk24 = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        p->unk24 += 1;
        if ((s32) p->unk24 >= 3) {
            p->unk24 = 0;
            p->unk20 += 1;
        }
        break;
    case 2:
        if (CharMotionEndCheck(p->unk2A) != 0) {
            p->unk20 += 1;
        }
        break;
    case 3:
        p->unk24 += 1;
        p->unk4 -= 6.3f * (f32) p->unk24;
        break;
    }
    return 0;
}

s32 fn_1_2488(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 0:
        p->unk24 = 0;
        p->unk20 += 1;
        /* fallthrough */
    case 1:
        p->unk24 += 1;
        if ((s32) p->unk24 >= 3) {
            p->unk20 += 1;
        }
        break;
    case 2:
        if (CharMotionEndCheck(p->unk2A) != 0) {
            CharMotionSet(p->unk2A, p->unk18->motion[5]);
            CharMotionSpeedSet(p->unk2A, 1.5f);
            p->unk20 = 0;
            p->unk1C = fn_1_2564;
        }
        break;
    }
    return 0;
}

s32 fn_1_2564(M528Player *p) {
    if ((s32) p->unk20 != 0) {

    } else if (CharMotionEndCheck(p->unk2A) != 0) {
        CharMotionSet(p->unk2A, *p->unk18->motion);
        CharMotionSpeedSet(p->unk2A, 1.0f);
        CharModelAttrSet(p->unk2A, 0x40000001U);
        p->unk20 = 0;
        p->unk1C = fn_1_1F8C;
    }
    return 0;
}

s32 fn_1_25FC(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        CharMotionShiftSet(p->unk2A, p->unk18->motion[7], 0.0f, 3.0f, 0U);
        p->unk20 += 1;
        break;
    }
    return 0;
}

s32 fn_1_2680(M528Player *p) {
    s32 temp_r0;

    temp_r0 = p->unk20;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        CharMotionShiftSet(p->unk2A, p->unk18->motion[6], 0.0f, 3.0f, 0U);
        p->unk20 += 1;
        break;
    }
    return 0;
}

s32 fn_1_2704(M528Player *p) {
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    return HuPadBtnDown[p->unk2E] & 0x100;
}

s32 fn_1_2758(M528Player *p) {
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    return HuPadBtnDown[p->unk2E] & 0x140;
}

s32 fn_1_27AC(M528Player *p) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s16 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;

    var_r28 = 0;
    sp28 = lbl_1_rodata_130[0];
    sp2C = lbl_1_rodata_130[1];
    sp30 = lbl_1_rodata_130[2];
    sp34 = lbl_1_rodata_130[3];
    sp38 = lbl_1_rodata_130[4];
    sp3C = lbl_1_rodata_130[5];
    sp40 = lbl_1_rodata_130[6];
    sp44 = lbl_1_rodata_130[7];
    sp8 = lbl_1_rodata_150[0];
    spC = lbl_1_rodata_150[1];
    sp10 = lbl_1_rodata_150[2];
    sp14 = lbl_1_rodata_150[3];
    sp18 = lbl_1_rodata_150[4];
    sp1C = lbl_1_rodata_150[5];
    sp20 = lbl_1_rodata_150[6];
    sp24 = lbl_1_rodata_150[7];
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    temp_r0 = p->unk50;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r26 = 1;
        var_r25 = 1;
        if ((((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_1F8C) && (((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_22B4)) {
            var_r25 = 0;
        }
        if ((var_r25 == 0) && (((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_2488)) {
            var_r26 = 0;
        }
        if (frandmod(0x64U) < (s32) lbl_1_rodata_130[var_r26 * 4 + p->unk36]) {
            p->unk52 = 0;
            if (var_r26 != 0) {
                p->unk54 = frandmod(0x12U) + 9;
            } else {
                p->unk54 = frandmod(8U) + 4;
            }
            p->unk50 += 1;
        } else {
            p->unk52 = lbl_1_rodata_150[var_r26 * 4 + p->unk36] <= frandmod(0x64U);
            var_r28 = 1;
        }
        break;
    case 1:
        p->unk52 += 1;
        if ((s16) p->unk52 > (s16) p->unk54) {
            p->unk52 = 0;
            p->unk50 = 0;
        }
        break;
    }
    return var_r28;
}

s32 fn_1_2A00(M528Player *p) {
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s16 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r29;

    var_r29 = 0;
    sp28 = lbl_1_rodata_170[0];
    sp2C = lbl_1_rodata_170[1];
    sp30 = lbl_1_rodata_170[2];
    sp34 = lbl_1_rodata_170[3];
    sp38 = lbl_1_rodata_170[4];
    sp3C = lbl_1_rodata_170[5];
    sp40 = lbl_1_rodata_170[6];
    sp44 = lbl_1_rodata_170[7];
    sp8 = lbl_1_rodata_190[0];
    spC = lbl_1_rodata_190[1];
    sp10 = lbl_1_rodata_190[2];
    sp14 = lbl_1_rodata_190[3];
    sp18 = lbl_1_rodata_190[4];
    sp1C = lbl_1_rodata_190[5];
    sp20 = lbl_1_rodata_190[6];
    sp24 = lbl_1_rodata_190[7];
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    temp_r0 = p->unk50;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r26 = 1;
        var_r25 = 1;
        if ((((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_1F8C) && (((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_22B4)) {
            var_r25 = 0;
        }
        if ((var_r25 == 0) && (((s32 (*)(M528Player *)) p->unk4C->unk1C) != fn_1_2488)) {
            var_r26 = 0;
        }
        if ((s16) p->unk3C != 0) {
            if (frandmod(0x64U) < (s32) lbl_1_rodata_190[var_r26 * 4 + p->unk36]) {
                p->unk54 = fn_1_2C40(p->unk3C, (s32) p->unk36);
            } else {
                p->unk54 = 0;
            }
        } else if (frandmod(0x64U) < (s32) lbl_1_rodata_170[var_r26 * 4 + p->unk36]) {
            p->unk54 = fn_1_2C40(p->unk3C, (s32) p->unk36);
        } else {
            p->unk54 = 0;
        }
        p->unk50 += 1;
        /* fallthrough */
    case 1:
        p->unk52 += 1;
        if ((s16) p->unk52 == (s16) p->unk54) {
            p->unk52 = 0;
            var_r29 = 1;
        }
        break;
    }
    return var_r29;
}

s16 fn_1_2C40(s16 power, s32 dif) {
    s32 sp8;
    s16 var_r31;

    sp8 = dif;
    var_r31 = 0;
    if (sp8 != 0) {
        switch (power) {                            /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            var_r31 = frandmod(9U) + 0xD;
            break;
        case 1:                                     /* switch 1 */
            var_r31 = frandmod(8U) + 0xB;
            break;
        case 2:                                     /* switch 1 */
            var_r31 = frandmod(7U) + 9;
            break;
        case 3:                                     /* switch 1 */
            var_r31 = frandmod(6U) + 7;
            break;
        }
    } else {
        switch (power) {                            /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            var_r31 = frandmod(5U) + 5;
            break;
        case 1:                                     /* switch 2 */
            var_r31 = frandmod(4U) + 7;
            break;
        case 2:                                     /* switch 2 */
            var_r31 = frandmod(3U) + 9;
            break;
        case 3:                                     /* switch 2 */
            var_r31 = frandmod(2U) + 0xB;
            break;
        }
    }
    return var_r31;
}

s16 fn_1_2D7C(M528Player *p) {
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    if ((s32) (HuPadBtnDown[p->unk2E] & 0x100) != 0) {
        p->unk3A = 0;
    } else if ((s32) (HuPadBtn[p->unk2E] & 0x100) != 0) {
        p->unk3A += 1;
    }
    return (s16) ((s16) p->unk3A > 5);
}

s16 fn_1_2E3C(M528Player *p) {
    if ((s16) ((M528Work *)lbl_1_bss_298->data)->unk4CB2 == 0) {
        return 0;
    }
    if ((s16) p->unk52 != 0) {
        p->unk3A += 1;
    }
    return (s16) ((s16) p->unk3A > 5);
}

s32 fn_1_2EC0(M528Team *team) {
    f32 temp_f26;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f27;
    f32 var_f31;
    s32 var_r28;
    M528Work *temp_r27;

    var_r28 = 0;
    temp_r27 = lbl_1_bss_298->data;
    temp_f26 = team->unk0[0].unk10 - team->unk0[1].unk10;
    temp_f28 = team->unk0[0].unk14 - team->unk0[1].unk14;
    if (temp_f28 == 0.0f) {
        var_f27 = 5.0f * (-team->unk58 / 25.0f);
    } else {
        var_f27 = 0.0f;
    }
    fn_1_32D0(team->unk0);
    fn_1_32D0(&team->unk0[1]);
    team->unk58 += var_f27 + ((6.4f * temp_f26) + (0.5f * temp_f28));
    if ((s32) (team->unk0[0].unk18 - team->unk0[1].unk18) == 0) {
        var_f31 = 0.0f;
    } else {
        var_f31 = (f32) fabs(team->unk0[0].unk10 - team->unk0[1].unk10);
        if (var_f31 > 1.0f) {
            var_f31 = 1.0f;
        }
        if (((s16) team->unk0[0].unk1C != 0) || ((s16) team->unk0[1].unk1C != 0)) {
            HuAudFXPlay((s32) team->unk66);
        }
    }
    team->unk0[0].unk1C = 0;
    team->unk0[1].unk1C = 0;
    if (team->unk58 > 25.0f) {
        var_f31 = 0.0f;
        team->unk58 = 25.0f;
    }
    if (team->unk58 < -25.0f) {
        var_f31 = 0.0f;
        team->unk58 = -25.0f;
    }
    if ((s16) temp_r27->unk4CB2 != 0) {
        var_r28 = fn_1_3750(team->unk54, var_f31);
    }
    team->unk40 += 6.0f * var_f31;
    if (team->unk40 > 360.0f) {
        team->unk40 -= 360.0f;
    }
    temp_f30 = (f32) (150.0 * cos((3.141592653589793 * (f64) team->unk58) / 180.0));
    temp_f29 = (f32) (150.0 * sin((3.141592653589793 * (f64) team->unk58) / 180.0));
    Hu3DModelRotSet(team->unk60, 0.0f, 0.0f, team->unk58);
    team->unk0[0].unk4 = team->unk48.x - temp_f30;
    team->unk0[0].unk8 = team->unk48.y - temp_f29;
    team->unk0[1].unk4 = team->unk48.x + temp_f30;
    team->unk0[1].unk8 = team->unk48.y + temp_f29;
    Hu3DModelPosSet(team->unk0[0].unk1A, team->unk0[0].unk4, team->unk0[0].unk8, team->unk0[0].unkC);
    Hu3DModelPosSet(team->unk0[1].unk1A, team->unk0[1].unk4, team->unk0[1].unk8, team->unk0[1].unkC);
    Hu3DModelRotSet(team->unk44, 0.0f, 0.0f, team->unk40);
    return var_r28;
}

void fn_1_32D0(M528Half *half) {
    if ((s16) half->unk18 != 0) {
        half->unk18 -= 1;
        return;
    }
    half->unk10 *= 0.95f;
    if (half->unk10 < 0.01f) {
        half->unk10 = 0.0f;
    }
}

void fn_1_3330(M528Work *work) {
    f32 spC;
    f32 sp8;
    f32 var_f30;
    f32 var_f31;
    s16 var_r27;
    s16 var_r28;
    s32 var_r29;
    s32 var_r30;
    M528Player *temp_r31;

    sp8 = lbl_1_rodata_1D8[0];
    spC = lbl_1_rodata_1D8[1];
    var_r30 = 0;
loop_26:
    if (var_r30 < 2) {
        var_r29 = 0;
loop_24:
        if (var_r29 < 2) {
            temp_r31 = work->unk10[var_r30][var_r29];
            if ((s16) temp_r31->unk3E != 0) {
                temp_r31->unk0 = (f32) temp_r31->unk58->unk4;
                temp_r31->unk4 = (f32) temp_r31->unk58->unk8;
            } else if (temp_r31->unk4 <= temp_r31->unk58->unk8) {
                temp_r31->unk48 = (f32) ((temp_r31->unk40 - temp_r31->unk44) / 500.0f);
                temp_r31->unk4 = (f32) temp_r31->unk58->unk8;
                if (((s32 (*)(M528Player *)) temp_r31->unk1C) == fn_1_2080) {
                    CharMotionSet(temp_r31->unk2A, temp_r31->unk18->motion[2]);
                    temp_r31->unk20 = 0;
                    temp_r31->unk3E = 1;
                    temp_r31->unk58->unk14 = 1.0f;
                    if ((s16) temp_r31->unk3C != 0) {
                        var_r28 = 6;
                    } else {
                        var_r28 = 3;
                    }
                    temp_r31->unk58->unk18 = var_r28;
                    if (temp_r31->unk48 > 1.0f) {
                        var_f31 = 1.0f;
                    } else {
                        var_f31 = temp_r31->unk48;
                    }
                    temp_r31->unk58->unk10 = var_f31;
                    temp_r31->unk1C = fn_1_22B4;
                    temp_r31->unk58->unk1C = 1;
                } else if (((s32 (*)(M528Player *)) temp_r31->unk1C) == fn_1_237C) {
                    omVibrate(temp_r31->unk28, 0xC, 6, 6);
                    CharMotionShiftSet(temp_r31->unk2A, temp_r31->unk18->motion[4], 0.0f, 3.0f, 0U);
                    CharMotionSpeedSet(temp_r31->unk2A, 1.5f);
                    temp_r31->unk20 = 0;
                    temp_r31->unk48 = (f32) (temp_r31->unk48 * 2.0f);
                    temp_r31->unk3E = 1;
                    temp_r31->unk58->unk14 = 1.0f;
                    if ((s16) temp_r31->unk3C != 0) {
                        var_r27 = 9;
                    } else {
                        var_r27 = 6;
                    }
                    temp_r31->unk58->unk18 = var_r27;
                    if (temp_r31->unk48 > 1.0f) {
                        var_f30 = 1.0f;
                    } else {
                        var_f30 = temp_r31->unk48;
                    }
                    temp_r31->unk58->unk10 = var_f30;
                    temp_r31->unk1C = fn_1_2488;
                    temp_r31->unk58->unk1C = 1;
                } else if (((s32 (*)(M528Player *)) temp_r31->unk1C) == fn_1_1ECC) {
                    omVibrate(temp_r31->unk28, 0xC, 6, 6);
                    CharMotionSet(temp_r31->unk2A, temp_r31->unk18->motion[2]);
                    temp_r31->unk20 = 0;
                    temp_r31->unk3E = 1;
                    temp_r31->unk58->unk14 = 1.0f;
                    temp_r31->unk58->unk18 = 6;
                    temp_r31->unk58->unk10 = (f32) temp_r31->unk48;
                    temp_r31->unk1C = fn_1_22B4;
                    temp_r31->unk58->unk1C = 1;
                }
            }
            omSetTra(temp_r31->unk18, temp_r31->unk0, temp_r31->unk4, temp_r31->unk8);
            Hu3DModelPosSet(*temp_r31->unk18->model, temp_r31->unk0, temp_r31->unk4, temp_r31->unk8);
            var_r29 += 1;
            goto loop_24;
        }
        var_r30 += 1;
        goto loop_26;
    }
}

void fn_1_36DC(M528Slice *slice) {
    slice->unk0.x = 0.0f;
    slice->unk0.y = 0.0f;
    slice->unk0.z = 0.0f;
    slice->unk18 = 0.0f;
    slice->unk1C = 0.0f;
    slice->unk26 = 0;
    slice->unk20 = -1;
    slice->unk22 = -1;
    slice->unk24 = -1;
}

s32 fn_1_3750(M528Slice *slice, f32 speed) {
    f32 sp8;
    f32 temp_f31;
    s32 var_r30;

    sp8 = speed;
    var_r30 = 0;
    slice->unk18 += (1.8f * sp8) / 360.0f;
    if (slice->unk18 >= 1.0f) {
        slice->unk18 = 1.0f;
        var_r30 = 1;
    }
    temp_f31 = ((M528Work *)lbl_1_bss_298->data)->unk4C98 + (slice->unk1C - (360.0f * slice->unk18));
    Hu3DModelRotSet(slice->unk20, 0.0f, temp_f31, 0.0f);
    Hu3DModelRotSet(slice->unk22, 0.0f, temp_f31, 0.0f);
    Hu3DModelRotSet(slice->unk24, 0.0f, temp_f31, 0.0f);
    Hu3DMotionShapeTimeSet(slice->unk22, 1198.0f * slice->unk18);
    Hu3DMotionShapeTimeSet(slice->unk24, 1198.0f * slice->unk18);
    Hu3DMotionTimeSet(slice->unk24, 1198.0f * slice->unk18);
    return var_r30;
}

void fn_1_38F8(M528Work *work) {
    u32 temp_r3;
    u32 temp_r3_2;

    work->unk10[0][0]->unk4C = work->unk10[0][1];
    work->unk10[0][1]->unk4C = work->unk10[0][0];
    work->unk10[1][0]->unk4C = work->unk10[1][1];
    work->unk10[1][1]->unk4C = work->unk10[1][0];
    temp_r3 = frandmod(2U);
    work->unk10[0][temp_r3]->unk52 = 0;
    work->unk10[0][temp_r3]->unk54 = frandmod(0xFU) + 0x1E;
    work->unk10[0][temp_r3]->unk50 = 1;
    temp_r3_2 = frandmod(2U);
    work->unk10[1][temp_r3_2]->unk52 = 0;
    work->unk10[1][temp_r3_2]->unk54 = frandmod(0xFU) + 0x1E;
    work->unk10[1][temp_r3_2]->unk50 = 1;
}

void fn_1_3A00(M528Work *work) {
    M528Slice *temp_r28;
    f32 temp_f31;
    s16 temp_r29;
    s16 temp_r29_2;
    s16 temp_r29_3;
    s32 var_r30;

    var_r30 = 0;
loop_2:
    if (var_r30 < 0x10) {
        temp_r28 = &work->unk10C[var_r30];
        temp_f31 = work->unk4C98 + temp_r28->unk1C;
        work->unk10C[var_r30].unk0.x = (f32) (1480.0 * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        work->unk10C[var_r30].unk0.y = -620.0f;
        work->unk10C[var_r30].unk0.z = (f32) ((1480.0 * cos((3.141592653589793 * (f64) temp_f31) / 180.0)) - 1680.0);
        temp_r29 = temp_r28->unk20;
        Hu3DModelPosSet(temp_r29, work->unk10C[var_r30].unk0.x, work->unk10C[var_r30].unk0.y, work->unk10C[var_r30].unk0.z);
        Hu3DModelRotSet(temp_r29, 0.0f, temp_f31, 0.0f);
        temp_r29_2 = temp_r28->unk22;
        Hu3DModelPosSet(temp_r29_2, work->unk10C[var_r30].unk0.x, work->unk10C[var_r30].unk0.y, work->unk10C[var_r30].unk0.z);
        Hu3DModelRotSet(temp_r29_2, 0.0f, temp_f31, 0.0f);
        temp_r29_3 = temp_r28->unk24;
        Hu3DModelPosSet(temp_r29_3, work->unk10C[var_r30].unk0.x, work->unk10C[var_r30].unk0.y, work->unk10C[var_r30].unk0.z);
        Hu3DModelRotSet(temp_r29_3, 0.0f, temp_f31, 0.0f);
        var_r30 += 1;
        goto loop_2;
    }
    Hu3DModelRotSet(work->unk4CB4[4], 0.0f, work->unk4C98, 0.0f);
    Hu3DModelRotSet(work->unk4CB4[5], 0.0f, work->unk4C98, 0.0f);
    Hu3DModelRotSet(work->unk4CB4[7], 0.0f, work->unk4C98, 0.0f);
}

s32 fn_1_3CA0(M528Camera *cam) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->unk18;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->unk1A = 0;
        cam->unk18 += 1;
        /* fallthrough */
    case 1:
        cam->unk1A += 1;
        if ((s16) cam->unk1A >= 0x64) {
            cam->unk18 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) cam->unk1A / 100.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        cam->unkC = (lbl_1_data_2BC->unkC * temp_f30) + (lbl_1_data_2BC[1].unkC * temp_f31);
        cam->unk10 = (lbl_1_data_2BC->unk10 * temp_f30) + (lbl_1_data_2BC[1].unk10 * temp_f31);
        cam->unk14 = (lbl_1_data_2BC->unk14 * temp_f30) + (lbl_1_data_2BC[1].unk14 * temp_f31);
        cam->unk0.x = (lbl_1_data_2BC->unk0.x * temp_f30) + (lbl_1_data_2BC[1].unk0.x * temp_f31);
        cam->unk0.y = (lbl_1_data_2BC->unk0.y * temp_f30) + (lbl_1_data_2BC[1].unk0.y * temp_f31);
        cam->unk0.z = (lbl_1_data_2BC->unk0.z * temp_f30) + (lbl_1_data_2BC[1].unk0.z * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_3EFC(M528Camera *cam) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->unk18;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->unk1A = 0;
        cam->unk18 += 1;
        /* fallthrough */
    case 1:
        cam->unk1A += 1;
        if ((s16) cam->unk1A >= 0x5A) {
            cam->unk18 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) cam->unk1A / 90.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        cam->unkC = (lbl_1_data_2BC[1].unkC * temp_f30) + (lbl_1_data_2BC[2].unkC * temp_f31);
        cam->unk10 = (lbl_1_data_2BC[1].unk10 * temp_f30) + (lbl_1_data_2BC[2].unk10 * temp_f31);
        cam->unk14 = (lbl_1_data_2BC[1].unk14 * temp_f30) + (lbl_1_data_2BC[2].unk14 * temp_f31);
        cam->unk0.x = (lbl_1_data_2BC[1].unk0.x * temp_f30) + (lbl_1_data_2BC[2].unk0.x * temp_f31);
        cam->unk0.y = (lbl_1_data_2BC[1].unk0.y * temp_f30) + (lbl_1_data_2BC[2].unk0.y * temp_f31);
        cam->unk0.z = (lbl_1_data_2BC[1].unk0.z * temp_f30) + (lbl_1_data_2BC[2].unk0.z * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_4158(M528Camera *cam) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->unk18;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->unk1A = 0;
        cam->unk18 += 1;
        /* fallthrough */
    case 1:
        cam->unk1A += 1;
        if ((s16) cam->unk1A >= 0x5A) {
            cam->unk18 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) cam->unk1A / 90.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        cam->unkC = (lbl_1_data_2BC[1].unkC * temp_f30) + (lbl_1_data_2BC[3].unkC * temp_f31);
        cam->unk10 = (lbl_1_data_2BC[1].unk10 * temp_f30) + (lbl_1_data_2BC[3].unk10 * temp_f31);
        cam->unk14 = (lbl_1_data_2BC[1].unk14 * temp_f30) + (lbl_1_data_2BC[3].unk14 * temp_f31);
        cam->unk0.x = (lbl_1_data_2BC[1].unk0.x * temp_f30) + (lbl_1_data_2BC[3].unk0.x * temp_f31);
        cam->unk0.y = (lbl_1_data_2BC[1].unk0.y * temp_f30) + (lbl_1_data_2BC[3].unk0.y * temp_f31);
        cam->unk0.z = (lbl_1_data_2BC[1].unk0.z * temp_f30) + (lbl_1_data_2BC[3].unk0.z * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_43B4(M528Camera *cam) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->unk18;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->unk1A = 0;
        cam->unk18 += 1;
        /* fallthrough */
    case 1:
        cam->unk1A += 1;
        if ((s16) cam->unk1A >= 0x1E) {
            cam->unk18 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) cam->unk1A / 30.0f;
        cam->unk0.y = (f32) ((f64) lbl_1_data_2BC[1].unk0.y + ((f64) (15.0f * (1.0f - temp_f31)) * sin((3.141592653589793 * (f64) ((cam->unk1A * 0x24) % 360)) / 180.0)));
        break;
    }
    return var_r30;
}

s32 fn_1_4540(M528Camera *cam) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->unk18;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->unk1A = 0;
        cam->unk18 += 1;
        /* fallthrough */
    case 1:
        cam->unk1A += 1;
        if ((s16) cam->unk1A >= 0x1E) {
            cam->unk18 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) cam->unk1A / 30.0f;
        cam->unk0.y = (f32) ((f64) lbl_1_data_2BC[1].unk0.y + ((f64) (30.0f * (1.0f - temp_f31)) * sin((3.141592653589793 * (f64) ((cam->unk1A * 0x24) % 360)) / 180.0)));
        break;
    }
    return var_r30;
}

void fn_1_46CC(M528Work *work) {
    s32 spC;
    s32 sp8;
    s32 var_r30;
    s32 var_r30_2;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r3_4;

    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        work->unk3C[var_r30].unk54 = &work->unk10C[work->unk4CA8[var_r30]];
        var_r30 += 1;
        goto loop_2;
    }
    temp_r3 = work->unk4CA8[0] + 0xF;
    temp_r3_2 = temp_r3 >> 0x1FU;
    temp_r0 = (temp_r3 << 0x1C) - temp_r3_2;
    sp8 = (temp_r3 % 16);
    temp_r3_3 = work->unk4CA8[1] + 1;
    temp_r3_4 = temp_r3_3 >> 0x1FU;
    temp_r0_2 = (temp_r3_3 << 0x1C) - temp_r3_4;
    spC = (temp_r3_3 % 16);
    var_r30_2 = 0;
loop_10:
    if (var_r30_2 < 0x10) {
        if ((var_r30_2 != (s16) work->unk4CA8[0]) && (var_r30_2 != (s16) work->unk4CA8[1]) && (var_r30_2 != sp8) && (var_r30_2 != spC)) {
            Hu3DModelAttrSet(work->unk10C[var_r30_2].unk22, 1U);
            Hu3DModelAttrSet(work->unk10C[var_r30_2].unk24, 1U);
        }
        var_r30_2 += 1;
        goto loop_10;
    }
}

s32 fn_1_47F0(M528Team *team) {
    s16 temp_r0;
    s32 var_r29;

    var_r29 = 0;
    temp_r0 = team->unk62;
    switch (temp_r0) {                              /* irregular */
    case 0:
        team->unk48.y = 1000.0f;
        team->unk64 = 0;
        team->unk62 += 1;
        /* fallthrough */
    case 1:
        team->unk64 += 1;
        team->unk48.y -= 2.4f * (f32) team->unk64;
        if (team->unk48.y < 0.0f) {
            team->unk48.y = 0.0f;
            var_r29 = 1;
        }
        team->unk0[0].unk8 = team->unk48.y;
        team->unk0[1].unk8 = team->unk48.y;
        Hu3DModelPosSet(team->unk60, team->unk48.x, team->unk48.y, team->unk48.z);
        Hu3DModelPosSet(team->unk0[0].unk1A, team->unk0[0].unk4, team->unk0[0].unk8, team->unk0[0].unkC);
        Hu3DModelPosSet(team->unk0[1].unk1A, team->unk0[1].unk4, team->unk0[1].unk8, team->unk0[1].unkC);
        Hu3DModelPosSet(team->unk44, team->unk48.x, team->unk48.y, team->unk48.z);
        break;
    }
    return var_r29;
}

s32 fn_1_495C(M528Team *team) {
    u16 sp8[2];
    s16 temp_r0;
    s32 var_r29;

    var_r29 = 0;
    sp8[0] = (u16) lbl_1_rodata_210[0];
    sp8[1] = (u16) lbl_1_rodata_210[1];
    temp_r0 = team->unk62;
    switch (temp_r0) {                              /* irregular */
    case 0:
        HuAudFXPlayPan(0x78F, (s16) sp8[((M528Work *)lbl_1_bss_298->data)->unk4CB0 ^ 1]);
        team->unk64 = 0;
        team->unk62 += 1;
        /* fallthrough */
    case 1:
        team->unk64 += 1;
        team->unk48.y += 20.0f - (2.4f * (f32) team->unk64);
        if (team->unk48.y < -1000.0f) {
            var_r29 = 1;
        }
        team->unk0[0].unk8 = team->unk48.y;
        team->unk0[1].unk8 = team->unk48.y;
        Hu3DModelPosSet(team->unk60, team->unk48.x, team->unk48.y, team->unk48.z);
        Hu3DModelPosSet(team->unk0[0].unk1A, team->unk0[0].unk4, team->unk0[0].unk8, team->unk0[0].unkC);
        Hu3DModelPosSet(team->unk0[1].unk1A, team->unk0[1].unk4, team->unk0[1].unk8, team->unk0[1].unkC);
        Hu3DModelPosSet(team->unk44, team->unk48.x, team->unk48.y, team->unk48.z);
        break;
    }
    return var_r29;
}

s32 fn_1_4B04(M528Slice *slice) {
    f32 sp8[2];
    s16 temp_r0;
    s32 var_r30;
    M528Work *temp_r29;

    var_r30 = 0;
    sp8[0] = lbl_1_rodata_218[0];
    sp8[1] = lbl_1_rodata_218[1];
    temp_r29 = lbl_1_bss_298->data;
    temp_r0 = slice->unk26;
    switch (temp_r0) {                              /* irregular */
    case 0:
        slice->unkC.x = slice->unk0.x;
        slice->unkC.y = slice->unk0.y;
        slice->unkC.z = slice->unk0.z;
        slice->unk28 = 0;
        slice->unk26 += 1;
        HuAudFXPlay(0x78B);
        /* fallthrough */
    case 1:
        slice->unk28 += 1;
        if ((s16) slice->unk28 >= 0x78) {
            var_r30 = 1;
        }
        slice->unkC.y = (f32) ((f64) slice->unkC.y + (100.0 - (2.4 * (f64) slice->unk28)));
        slice->unkC.x += sp8[temp_r29->unk4CB0];
        slice->unk0.z += 1.0f;
        Hu3DModelPosSet(slice->unk22, slice->unkC.x, slice->unkC.y, slice->unkC.z);
        break;
    }
    return var_r30;
}

s32 fn_1_4C84(M528Slice *slice) {
    M528Work *sp8;
    s16 temp_r0;

    sp8 = lbl_1_bss_298->data;
    temp_r0 = slice->unk26;
    switch (temp_r0) {                              /* irregular */
    case 0:
        slice->unk28 = 0;
        slice->unk26 += 1;
        /* fallthrough */
    case 1:
        slice->unk28 += 1;
        if ((s16) slice->unk28 == 3) {
            slice->unk26 += 1;
        }
        break;
    case 2:
        slice->unk0.y -= 5.0f;
        slice->unk28 += 1;
        if ((s16) slice->unk28 == 0x12) {
            slice->unkC.x = slice->unk0.x;
            slice->unkC.y = slice->unk0.y;
            slice->unkC.z = slice->unk0.z;
            slice->unk28 = 0;
            slice->unk26 += 1;
        }
        Hu3DModelPosSet(slice->unk22, slice->unk0.x, slice->unk0.y, slice->unk0.z);
        break;
    case 3:
        slice->unk28 += 1;
        if ((s16) slice->unk28 >= 5) {
            slice->unk28 = 0;
        }
        slice->unkC.y = (f32) ((f64) slice->unkC.y + (2.0 * sin((3.141592653589793 * (f64) ((360.0f * (f32) slice->unk28) / 5.0f)) / 180.0)));
        Hu3DModelPosSet(slice->unk22, slice->unkC.x, slice->unkC.y, slice->unkC.z);
        break;
    }
    return 0;
}

void fn_1_4E80(M528Work *work) {
    s32 var_r30;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r3_4;

    if ((s16) work->unk4CB0 != 0) {
        temp_r3 = work->unk4CA8[1] + 5;
        temp_r3_2 = temp_r3 >> 0x1FU;
        temp_r0 = (temp_r3 << 0x1C) - temp_r3_2;
        var_r30 = (temp_r3 % 16);
    } else {
        temp_r3_3 = work->unk4CA8[0] + 0xB;
        temp_r3_4 = temp_r3_3 >> 0x1FU;
        temp_r0_2 = (temp_r3_3 << 0x1C) - temp_r3_4;
        var_r30 = (temp_r3_3 % 16);
    }
    Hu3DModelAttrReset(work->unk10C[var_r30].unk22, 1U);
    Hu3DModelAttrReset(work->unk10C[var_r30].unk24, 1U);
}

void fn_1_4F30(M528Work *work) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0xFF) {
        work->unk3E4[var_r31].unk0 = NULL;
        work->unk3E4[var_r31].unk4 = &work->unk3E4[var_r31 + 1];
        work->unk3E4[var_r31].unk8 = NULL;
        work->unk3E4[var_r31].unkC = NULL;
        var_r31 += 1;
        goto loop_2;
    }
    work->unk3E4[var_r31].unk0 = NULL;
    work->unk3E4[var_r31].unk4 = NULL;
    work->unk3E4[var_r31].unk8 = NULL;
    work->unk3E4[var_r31].unkC = NULL;
    work->unk3DC = NULL;
    work->unk3E0 = work->unk3E4;
}



void fn_1_50B0(M528Work *work) {
    M528Node *temp_r28;
    M528Node *var_r30;

    var_r30 = work->unk3DC;
loop_11:
    if (var_r30 != NULL) {
        temp_r28 = var_r30->unk4;
        if ((((s32 (*)(M528Node *)) var_r30->unk8) != NULL) && (var_r30->unk8(var_r30) != 0) && (var_r30 != NULL)) {
            if ((M528Node *) var_r30->unk0 != NULL) {
                var_r30->unk0->unk4 = var_r30->unk4;
            } else {
                work->unk3DC = var_r30->unk4;
            }
            if ((M528Node *) var_r30->unk4 != NULL) {
                var_r30->unk4->unk0 = var_r30->unk0;
            }
            var_r30->unk0 = NULL;
            var_r30->unk4 = work->unk3E0;
            var_r30->unk8 = NULL;
            work->unk3E0 = var_r30;
        }
        var_r30 = temp_r28;
        goto loop_11;
    }
}


void fn_1_51A8(M528Work *work) {
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s16 var_r30_4;
    s16 var_r30_5;
    s16 var_r30_6;
    s16 var_r30_7;
    s16 var_r30_8;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;

    if ((s16) work->unk4CB4[4] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[4] = temp_r3;
        var_r30 = temp_r3;
    } else {
        var_r30 = Hu3DModelLink(work->unk4CB4[4]);
    }
    Hu3DModelAttrSet(var_r30, 1U);
    Hu3DModelAttrSet(var_r30, 0x40000002U);
    Hu3DModelLayerSet(var_r30, 0);
    Hu3DModelPosSet(var_r30, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30, 1U);
    if ((s16) work->unk4CB4[8] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[8] = temp_r3_2;
        var_r30_2 = temp_r3_2;
    } else {
        var_r30_2 = Hu3DModelLink(work->unk4CB4[8]);
    }
    Hu3DModelAttrSet(var_r30_2, 1U);
    Hu3DModelAttrSet(var_r30_2, 0x40000001U);
    Hu3DModelLayerSet(var_r30_2, 0);
    Hu3DModelPosSet(var_r30_2, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(var_r30_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30_2, 1U);
    if ((s16) work->unk4CB4[5] < 0) {
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[5] = temp_r3_3;
        var_r30_3 = temp_r3_3;
    } else {
        var_r30_3 = Hu3DModelLink(work->unk4CB4[5]);
    }
    Hu3DModelAttrSet(var_r30_3, 1U);
    Hu3DModelAttrSet(var_r30_3, 0x40000002U);
    Hu3DModelLayerSet(var_r30_3, 0);
    Hu3DModelPosSet(var_r30_3, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(var_r30_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30_3, 1U);
    if ((s16) work->unk4CB4[6] < 0) {
        temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[6] = temp_r3_4;
        var_r30_4 = temp_r3_4;
    } else {
        var_r30_4 = Hu3DModelLink(work->unk4CB4[6]);
    }
    Hu3DModelAttrSet(var_r30_4, 1U);
    Hu3DModelAttrSet(var_r30_4, 0x40000002U);
    Hu3DModelLayerSet(var_r30_4, 0);
    Hu3DModelPosSet(var_r30_4, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(var_r30_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30_4, 1U);
    if ((s16) work->unk4CB4[7] < 0) {
        temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[7] = temp_r3_5;
        var_r30_5 = temp_r3_5;
    } else {
        var_r30_5 = Hu3DModelLink(work->unk4CB4[7]);
    }
    Hu3DModelAttrSet(var_r30_5, 1U);
    Hu3DModelAttrSet(var_r30_5, 0x40000002U);
    Hu3DModelLayerSet(var_r30_5, 0);
    Hu3DModelPosSet(var_r30_5, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(var_r30_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30_5, 1U);
    Hu3DReflectMapSet(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M528, 61), MEMORY_DEFAULT_NUM, HEAP_DATA));
    fn_1_5BF8(work);
    var_r29 = 0;
loop_23:
    if (var_r29 < 2) {
        if ((s16) work->unk4CB4[0] < 0) {
            temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[0] = temp_r3_6;
            var_r30_6 = temp_r3_6;
        } else {
            var_r30_6 = Hu3DModelLink(work->unk4CB4[0]);
        }
        work->unk3C[var_r29].unk60 = var_r30_6;
        work->unk3C[var_r29].unk58 = 0.0f;
        work->unk3C[var_r29].unk5C = 0.0f;
        work->unk3C[var_r29].unk48.x = (600.0f * (f32) var_r29) - 300.0f;
        work->unk3C[var_r29].unk48.y = 2500.0f;
        work->unk3C[var_r29].unk48.z = 0.0f;
        work->unk3C[var_r29].unk62 = 0;
        if (var_r29 == 0) {
            work->unk3C[var_r29].unk66 = 0x789;
        } else {
            work->unk3C[var_r29].unk66 = 0x78A;
        }
        Hu3DModelAttrSet(var_r30_6, 1U);
        Hu3DModelAttrSet(var_r30_6, 0x40000002U);
        Hu3DModelLayerSet(var_r30_6, 2);
        Hu3DModelPosSet(var_r30_6, work->unk3C[var_r29].unk48.x, work->unk3C[var_r29].unk48.y, work->unk3C[var_r29].unk48.z);
        Hu3DModelRotSet(var_r30_6, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r30_6, 1U);
        var_r29 += 1;
        goto loop_23;
    }
    var_r29_2 = 0;
loop_32:
    if (var_r29_2 < 2) {
        var_r28 = 0;
loop_30:
        if (var_r28 < 2) {
            if ((s16) work->unk4CB4[var_r29_2 + 1] < 0) {
                temp_r3_7 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r29_2 + 1], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4CB4[var_r29_2 + 1] = temp_r3_7;
                var_r30_7 = temp_r3_7;
            } else {
                var_r30_7 = Hu3DModelLink(work->unk4CB4[var_r29_2 + 1]);
            }
            work->unk3C[var_r29_2].unk0[var_r28].unk1A = var_r30_7;
            work->unk3C[var_r29_2].unk0[var_r28].unk4 = (work->unk3C[var_r29_2].unk48.x + (300.0f * (f32) var_r28)) - 150.0f;
            work->unk3C[var_r29_2].unk0[var_r28].unk8 = work->unk3C[var_r29_2].unk48.y;
            work->unk3C[var_r29_2].unk0[var_r28].unkC = work->unk3C[var_r29_2].unk48.z;
            work->unk3C[var_r29_2].unk0[var_r28].unk14 = 0.0f;
            work->unk3C[var_r29_2].unk0[var_r28].unk10 = 0.0f;
            work->unk3C[var_r29_2].unk0[var_r28].unk0 = &work->unk3C[var_r29_2];
            work->unk3C[var_r29_2].unk0[var_r28].unk1C = 0;
            Hu3DModelAttrSet(var_r30_7, 1U);
            Hu3DModelAttrSet(var_r30_7, 0x40000002U);
            Hu3DModelLayerSet(var_r30_7, 2);
            Hu3DModelPosSet(var_r30_7, work->unk3C[var_r29_2].unk0[var_r28].unk4, work->unk3C[var_r29_2].unk0[var_r28].unk8, work->unk3C[var_r29_2].unk0[var_r28].unkC);
            Hu3DModelRotSet(var_r30_7, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(var_r30_7, 1U);
            Hu3DModelShadowMapSet(var_r30_7);
            var_r28 += 1;
            goto loop_30;
        }
        var_r29_2 += 1;
        goto loop_32;
    }
    var_r29_3 = 0;
loop_38:
    if (var_r29_3 < 2) {
        if ((s16) work->unk4CB4[3] < 0) {
            temp_r3_8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[3] = temp_r3_8;
            var_r30_8 = temp_r3_8;
        } else {
            var_r30_8 = Hu3DModelLink(work->unk4CB4[3]);
        }
        work->unk3C[var_r29_3].unk44 = var_r30_8;
        work->unk3C[var_r29_3].unk40 = 0.0f;
        Hu3DModelAttrSet(var_r30_8, 1U);
        Hu3DModelAttrSet(var_r30_8, 0x40000002U);
        Hu3DModelLayerSet(var_r30_8, 2);
        Hu3DModelPosSet(var_r30_8, work->unk3C[var_r29_3].unk48.x, work->unk3C[var_r29_3].unk48.y, work->unk3C[var_r29_3].unk48.z);
        Hu3DModelRotSet(var_r30_8, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r30_8, 1U);
        var_r29_3 += 1;
        goto loop_38;
    }
    fn_1_6410(work);
    fn_1_654C(work);
    fn_1_6688(work);
    fn_1_67C4(work);
    fn_1_6900(work);
    fn_1_6A3C(work);
    fn_1_6B78(work);
    fn_1_6CB4(work);
    fn_1_B528(work->unk4BE4, 0);
    fn_1_B528(&work->unk4BE4[1], 0x96);
    fn_1_B528(&work->unk4BE4[2], 0x14A);
    fn_1_B528(&work->unk4BE4[3], 0x384);
}

void fn_1_5BF8(M528Work *work) {
    s32 sp8[8];
    f32 temp_f31;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r3_9;
    s16 var_r27;
    s16 var_r28;
    s16 var_r28_2;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s32 var_r26;
    s32 var_r29;
    u32 temp_r25;

    sp8[0] = lbl_1_rodata_248[0];
    sp8[1] = lbl_1_rodata_248[1];
    sp8[2] = lbl_1_rodata_248[2];
    sp8[3] = lbl_1_rodata_248[3];
    sp8[4] = lbl_1_rodata_248[4];
    sp8[5] = lbl_1_rodata_248[5];
    sp8[6] = lbl_1_rodata_248[6];
    sp8[7] = lbl_1_rodata_248[7];
    var_r29 = 0;
loop_39:
    if (var_r29 < 0x10) {
        temp_r25 = frandmod(0x64U);
        var_r26 = 0;
        var_r27 = 0;
loop_4:
        if (var_r27 < 8) {
            if ((s32) temp_r25 >= (s32) (var_r26 + sp8[var_r27])) {
                var_r26 += sp8[var_r27];
                var_r27 += 1;
                goto loop_4;
            }
        }
        if ((s16) work->unk4CB4[var_r27 + 0xD] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r27 + 0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r27 + 0xD] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r27 + 0xD]);
        }
        work->unk10C[var_r29].unk20 = var_r30;
        temp_f31 = (22.5f * (f32) var_r29) - 11.25f;
        work->unk10C[var_r29].unk0.x = (f32) (1480.0 * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        work->unk10C[var_r29].unk0.y = -620.0f;
        work->unk10C[var_r29].unk0.z = (f32) ((1480.0 * cos((3.141592653589793 * (f64) temp_f31) / 180.0)) - 1680.0);
        work->unk10C[var_r29].unk1C = temp_f31;
        work->unk10C[var_r29].unk2A = var_r27;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 1);
        Hu3DModelPosSet(var_r30, work->unk10C[var_r29].unk0.x, work->unk10C[var_r29].unk0.y, work->unk10C[var_r29].unk0.z);
        Hu3DModelRotSet(var_r30, 0.0f, work->unk10C[var_r29].unk1C, 0.0f);
        Hu3DModelAttrReset(var_r30, 1U);
        if (var_r27 == 7) {
            if ((s16) work->unk4D2E[var_r29] < 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D2E[var_r29] = temp_r3_2;
                var_r30_2 = temp_r3_2;
            } else {
                var_r30_2 = Hu3DModelLink(work->unk4D2E[var_r29]);
            }
            if ((s16) work->unk4D20[2] < 0) {
                temp_r3_3 = Hu3DJointMotion(var_r30_2, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D20[2] = temp_r3_3;
                var_r28 = temp_r3_3;
            } else {
                var_r28 = work->unk4D20[2];
            }
            Hu3DMotionSet(var_r30_2, var_r28);
        } else {
            if ((s16) work->unk4D2E[var_r29] < 0) {
                temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D2E[var_r29] = temp_r3_4;
                var_r30_2 = temp_r3_4;
            } else {
                var_r30_2 = Hu3DModelLink(work->unk4D2E[var_r29]);
            }
            if ((s16) work->unk4D20[0] < 0) {
                temp_r3_5 = Hu3DJointMotion(var_r30_2, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D20[0] = temp_r3_5;
                var_r28 = temp_r3_5;
            } else {
                var_r28 = work->unk4D20[0];
            }
            Hu3DMotionSet(var_r30_2, var_r28);
        }
        work->unk10C[var_r29].unk22 = var_r30_2;
        Hu3DModelAttrSet(var_r30_2, 1U);
        Hu3DModelAttrSet(var_r30_2, 0x40000002U);
        Hu3DModelAttrSet(var_r30_2, 0x40000080U);
        Hu3DModelLayerSet(var_r30_2, 1);
        Hu3DModelPosSet(var_r30_2, work->unk10C[var_r29].unk0.x, work->unk10C[var_r29].unk0.y, work->unk10C[var_r29].unk0.z);
        Hu3DModelRotSet(var_r30_2, 0.0f, work->unk10C[var_r29].unk1C, 0.0f);
        Hu3DMotionSet(var_r30_2, var_r28);
        Hu3DMotionShapeSet(var_r30_2, var_r28);
        Hu3DModelAttrReset(var_r30_2, 1U);
        if (var_r27 == 7) {
            if ((s16) work->unk4D4E[var_r29] < 0) {
                temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D4E[var_r29] = temp_r3_6;
                var_r30_3 = temp_r3_6;
            } else {
                var_r30_3 = Hu3DModelLink(work->unk4D4E[var_r29]);
            }
            if ((s16) work->unk4D20[3] < 0) {
                temp_r3_7 = Hu3DJointMotion(var_r30_3, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D20[3] = temp_r3_7;
                var_r28_2 = temp_r3_7;
            } else {
                var_r28_2 = work->unk4D20[3];
            }
            Hu3DMotionSet(var_r30_3, var_r28_2);
        } else {
            if ((s16) work->unk4D4E[var_r29] < 0) {
                temp_r3_8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D4E[var_r29] = temp_r3_8;
                var_r30_3 = temp_r3_8;
            } else {
                var_r30_3 = Hu3DModelLink(work->unk4D4E[var_r29]);
            }
            if ((s16) work->unk4D20[1] < 0) {
                temp_r3_9 = Hu3DJointMotion(var_r30_3, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
                work->unk4D20[1] = temp_r3_9;
                var_r28_2 = temp_r3_9;
            } else {
                var_r28_2 = work->unk4D20[1];
            }
            Hu3DMotionSet(var_r30_3, var_r28_2);
        }
        work->unk10C[var_r29].unk24 = var_r30_3;
        Hu3DModelAttrSet(var_r30_3, 1U);
        Hu3DModelAttrSet(var_r30_3, 0x40000002U);
        Hu3DModelAttrSet(var_r30_3, 0x40000080U);
        Hu3DModelLayerSet(var_r30_3, 1);
        Hu3DModelPosSet(var_r30_3, work->unk10C[var_r29].unk0.x, work->unk10C[var_r29].unk0.y, work->unk10C[var_r29].unk0.z);
        Hu3DModelRotSet(var_r30_3, 0.0f, work->unk10C[var_r29].unk1C, 0.0f);
        Hu3DMotionSet(var_r30_3, var_r28_2);
        Hu3DMotionShapeSet(var_r30_3, var_r28_2);
        Hu3DModelAttrReset(var_r30_3, 1U);
        var_r29 += 1;
        goto loop_39;
    }
}

void fn_1_6320(M528Work *work) {
    s16 temp_r3;
    s16 var_r31;

    if ((s16) work->unk4CB4[0x15] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
        work->unk4CB4[0x15] = temp_r3;
        var_r31 = temp_r3;
    } else {
        var_r31 = Hu3DModelLink(work->unk4CB4[0x15]);
    }
    Hu3DModelAttrSet(var_r31, 1U);
    Hu3DModelAttrSet(var_r31, 0x40000002U);
    Hu3DModelLayerSet(var_r31, 2);
    Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
}

void fn_1_6410(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 8) {
        if ((s16) work->unk4CB4[var_r31 + 0x16] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x16] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x16]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_654C(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 6) {
        if ((s16) work->unk4CB4[var_r31 + 0x1E] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x1E], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x1E] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x1E]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6688(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 5) {
        if ((s16) work->unk4CB4[var_r31 + 0x24] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x24], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x24] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x24]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_67C4(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 5) {
        if ((s16) work->unk4CB4[var_r31 + 0x29] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x29], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x29] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x29]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6900(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 1) {
        if ((s16) work->unk4CB4[var_r31 + 0x2E] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x2E], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x2E] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x2E]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6A3C(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 1) {
        if ((s16) work->unk4CB4[var_r31 + 0x2F] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x2F], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x2F] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x2F]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6B78(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 4) {
        if ((s16) work->unk4CB4[var_r31 + 0x30] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x30], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x30] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x30]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

void fn_1_6CB4(M528Work *work) {
    s16 temp_r3;
    s16 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_5:
    if (var_r31 < 2) {
        if ((s16) work->unk4CB4[var_r31 + 0x34] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r31 + 0x34], MEMORY_DEFAULT_NUM, HEAP_DATA));
            work->unk4CB4[var_r31 + 0x34] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(work->unk4CB4[var_r31 + 0x34]);
        }
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r31 += 1;
        goto loop_5;
    }
}

s32 fn_1_6DF0(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r28;
    u32 var_r27;
    M528Work *temp_r30;

    var_r27 = 0 /* TODO(mp5): uninitialised in the original */;
    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            var_r27 = frandmod(8U);
            if ((s16) temp_r30->unk4CB4[var_r27 + 0x16] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r27 + 0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[var_r27 + 0x16] = temp_r3;
                var_r28 = temp_r3;
            } else {
                var_r28 = Hu3DModelLink(temp_r30->unk4CB4[var_r27 + 0x16]);
            }
            temp_r31->unk36 = var_r28;
        } else {
            var_r28 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r28, 1U);
        Hu3DModelAttrSet(var_r28, 0x40000002U);
        Hu3DModelLayerSet(var_r28, 2);
        temp_f31 = (f32) frandmod(0x46U);
        temp_f30 = (f32) (frandmod(0x55U) - 0x2A);
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 220.0);
        temp_r31->unkC.x = 0.0f;
        if ((s32) var_r27 < 5) {
            temp_r31->unkC.y = (f32) frandmod(0xB4U);
            temp_r31->unkC.z = (f32) frandmod(0x1FU) - 15.0f;
        } else {
            temp_r31->unkC.y = 0.0f;
            temp_r31->unkC.z = 0.0f;
        }
        temp_f31_2 = (f32) (frandmod(3U) + 6);
        temp_f29 = (f32) (frandmod(0x28U) + 0x28);
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f29;
        temp_r31->unk18.z = (f32) (0.10000000149011612 + ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)));
        temp_r31->unk32 = 0;
        temp_r31->unk34 = frandmod(0x1EU) + 1;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_72E4(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r3_2;
    s16 var_r28;
    u32 temp_r3;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            temp_r3 = frandmod(5U);
            if ((s16) temp_r30->unk4CB4[temp_r3 + 0x1F] < 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[temp_r3 + 0x1F], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[temp_r3 + 0x1F] = temp_r3_2;
                var_r28 = temp_r3_2;
            } else {
                var_r28 = Hu3DModelLink(temp_r30->unk4CB4[temp_r3 + 0x1F]);
            }
            temp_r31->unk36 = var_r28;
        } else {
            var_r28 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r28, 1U);
        Hu3DModelAttrSet(var_r28, 0x40000002U);
        Hu3DModelLayerSet(var_r28, 2);
        temp_f31 = (f32) frandmod(0x32U);
        temp_f30 = (f32) (frandmod(0x55U) - 0x2A);
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = (f32) frandmod(0xB4U);
        temp_r31->unkC.z = (f32) frandmod(0x1FU) - 15.0f;
        temp_f31_2 = (f32) (frandmod(4U) + 5);
        temp_f29 = (f32) (frandmod(0x28U) + 0x28);
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f29;
        temp_r31->unk18.z = (f32) ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk32 = 0;
        temp_r31->unk34 = frandmod(0x1EU) + 1;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_7794(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r29;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[30] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x1E], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[30] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[30]);
            }
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_r31->unk0.x = (600.0f * (f32) temp_r30->unk4CB0) - 300.0f;
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = -200.0f;
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = (f32) frandmod(0xB4U);
        temp_r31->unkC.z = (f32) frandmod(0x1FU) - 15.0f;
        temp_f31 = (f32) 0xA;
        temp_f30 = (f32) 0;
        temp_r31->unk18.x = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = (f32) 0x46;
        temp_r31->unk18.z = (f32) ((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk32 = 0;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == 0x50) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 2.4f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_7B44(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 var_r27;
    s16 var_r29;
    u32 temp_r3;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            temp_r3 = frandmod(5U);
            if ((s16) temp_r30->unk4CB4[temp_r3 + 0x29] < 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[temp_r3 + 0x29], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[temp_r3 + 0x29] = temp_r3_2;
                var_r29 = temp_r3_2;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[temp_r3 + 0x29]);
            }
            if ((s16) temp_r30->unk4D20[4] < 0) {
                temp_r3_3 = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4D20[4] = temp_r3_3;
                var_r27 = temp_r3_3;
            } else {
                var_r27 = temp_r30->unk4D20[4];
            }
            Hu3DMotionSet(var_r29, var_r27);
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000001U);
        Hu3DModelAttrReset(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_f30 = 1.0f - (0.2f * ((f32) frandmod(0x2711U) / 10000.0f));
        Hu3DModelScaleSet(var_r29, temp_f30, temp_f30, temp_f30);
        temp_f31 = 15.0f * (f32) temp_r31->unk32;
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + (70.0 * sin((3.141592653589793 * (f64) temp_f31) / 180.0))) - 300.0);
        temp_r31->unk0.y = -200.0f;
        temp_r31->unk0.z = (f32) ((70.0 * cos((3.141592653589793 * (f64) temp_f31) / 180.0)) - 200.0);
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = 360.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk18.x = (f32) (3.0f * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        temp_r31->unk18.y = 11.0f;
        temp_r31->unk18.z = 0.0f;
        temp_r31->unk32 = 0;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_800C(M528Node *node) {
    M528Part *temp_r31;
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r28;
    s16 var_r29;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[47] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x2F], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[47] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[47]);
            }
            if ((s16) temp_r30->unk4D20[6] < 0) {
                temp_r3_2 = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4D20[6] = temp_r3_2;
                var_r28 = temp_r3_2;
            } else {
                var_r28 = temp_r30->unk4D20[6];
            }
            Hu3DMotionSet(var_r29, var_r28);
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000001U);
        Hu3DModelAttrReset(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_r31->unk0.x = (600.0f * (f32) temp_r30->unk4CB0) - 300.0f;
        temp_r31->unk0.y = -400.0f;
        temp_r31->unk0.z = -200.0f;
        temp_r31->unkC.x = -10.0f;
        temp_r31->unkC.y = 0.0f;
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk18.x = 0.0f;
        temp_r31->unk18.y = 45.0f;
        temp_r31->unk18.z = 0.0f;
        temp_r31->unk32 = 0;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        Hu3DModelAttrReset(temp_r31->unk36, 1U);
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 2:
        temp_r31->unk18.y -= 1.5f;
        if (temp_r31->unk18.y < 0.0f) {
            temp_r31->unk32 = 0;
            temp_r31->unk18.y = 0.0f;
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.y += temp_r31->unk18.y;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 3:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == 5) {
            temp_r31->unk30 += 1;
        }
        break;
    case 4:
        temp_r31->unk18.y -= 1.5f;
        temp_r31->unk0.y += temp_r31->unk18.y;
        if (temp_r31->unk0.y < -400.0f) {
            HuAudFXPlay(0x2C0);
            temp_r30->unk3CC = fn_1_4540;
            temp_r31->unk32 = 0;
            temp_r31->unk30 += 1;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 5:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == 7) {
            temp_r31->unk32 = 0;
            temp_r31->unk18.y = 45.0f;
            temp_r31->unk30 = 2;
        }
        break;
    }
    return 0;
}

s32 fn_1_83E4(M528Node *node) {
    M528Part *temp_r31;
    f32 var_f30;
    f32 var_f31;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r29;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[48] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x30], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[48] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[48]);
            }
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_r31->unk0.x = (600.0f * (f32) temp_r30->unk4CB0) - 300.0f;
        temp_r31->unk0.y = -200.0f;
        temp_r31->unk0.z = -200.0f;
        temp_r31->unkC.x = 0.0f;
        if ((s16) temp_r30->unk4CB0 != 0) {
            var_f31 = -20.0f;
        } else {
            var_f31 = 20.0f;
        }
        temp_r31->unkC.y = var_f31;
        temp_r31->unkC.z = 0.0f;
        if ((s16) temp_r30->unk4CB0 != 0) {
            var_f30 = 3.7f;
        } else {
            var_f30 = -3.7f;
        }
        temp_r31->unk18.x = var_f30;
        temp_r31->unk18.y = 55.0f;
        temp_r31->unk18.z = 1.0f;
        temp_r31->unk2C = 5.0f;
        temp_r31->unk32 = 0;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == 5) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 1.2f;
        if (temp_r31->unk0.y > 100.0f) {
            temp_r31->unk18.x *= 1.5f;
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.z += temp_r31->unk2C;
        if (temp_r31->unkC.z > 360.0f) {
            temp_r31->unkC.x -= 360.0f;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 3:
        temp_r31->unk18.y -= 1.2f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.z += temp_r31->unk2C;
        if (temp_r31->unkC.z > 360.0f) {
            temp_r31->unkC.z -= 360.0f;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_87F4(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s16 temp_r3_2;
    s16 var_r29;
    u32 temp_r3;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            temp_r3 = frandmod(3U);
            if ((s16) temp_r30->unk4CB4[temp_r3 + 0x31] < 0) {
                temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[temp_r3 + 0x31], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[temp_r3 + 0x31] = temp_r3_2;
                var_r29 = temp_r3_2;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[temp_r3 + 0x31]);
            }
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_r31->unk0.x = (600.0f * (f32) temp_r30->unk4CB0) - 300.0f;
        temp_r31->unk0.y = -200.0f;
        temp_r31->unk0.z = -200.0f;
        temp_f31 = (84.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 42.0f;
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = temp_f31;
        temp_r31->unkC.z = 0.0f;
        temp_f30 = 6.1f + (3.3f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) temp_f30 * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        temp_r31->unk18.y = 40.0f + (20.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.z = (f32) ((f64) temp_f30 * cos((3.141592653589793 * (f64) temp_f31) / 180.0));
        temp_r31->unk2C = -5.0f - (3.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk32 = 0;
        temp_r31->unk34 = (frandmod(0x3CU) * 2) + 0x1E;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 1.2f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.z += temp_r31->unk2C;
        if (temp_r31->unkC.z > 360.0f) {
            temp_r31->unkC.x -= 360.0f;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_8CD0(M528Node *node) {
    M528Part *temp_r31;
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r30;
    s16 var_r30_2;
    M528Work *temp_r29;

    temp_r29 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r29->unk4CB4[52] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x34], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r29->unk4CB4[52] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(temp_r29->unk4CB4[52]);
        }
        temp_r31->unk36 = var_r30;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000001U);
        Hu3DModelAttrReset(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 2);
        Hu3DModelScaleSet(var_r30, 2.7f, 2.7f, 2.7f);
        if ((s16) temp_r29->unk4CB4[53] < 0) {
            temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x35], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r29->unk4CB4[53] = temp_r3_2;
            var_r30_2 = temp_r3_2;
        } else {
            var_r30_2 = Hu3DModelLink(temp_r29->unk4CB4[53]);
        }
        temp_r31->unk34 = var_r30_2;
        Hu3DModelAttrSet(var_r30_2, 1U);
        Hu3DModelAttrSet(var_r30_2, 0x40000001U);
        Hu3DModelAttrReset(var_r30_2, 0x40000002U);
        Hu3DModelLayerSet(var_r30_2, 2);
        Hu3DModelScaleSet(var_r30_2, 2.7f, 2.7f, 2.7f);
        temp_r31->unk0.x = (600.0f * (f32) temp_r29->unk4CB0) - 300.0f;
        temp_r31->unk0.y = -400.0f;
        temp_r31->unk0.z = -200.0f;
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = 0.0f;
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk32 = 0;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        Hu3DModelPosSetV(temp_r31->unk34, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk34, &temp_r31->unkC);
        Hu3DModelAttrReset(temp_r31->unk36, 1U);
        Hu3DModelAttrReset(temp_r31->unk34, 1U);
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == 5) {
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        if (temp_r31->unk0.y >= -40.0f) {
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.y += 5.0f;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelPosSetV(temp_r31->unk34, &temp_r31->unk0);
        break;
    }
    return 0;
}

s32 fn_1_8FFC(M528Node *node) {
    HSFDATA *temp_r27;
    HSFMATERIAL *var_r29;
    M528Part *temp_r31;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r24;
    s16 temp_r3;
    s16 var_r28;
    s32 var_r25;
    s32 var_r26;
    M528Work *temp_r30;

    var_r25 = 0;
    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[21] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[21] = temp_r3;
                var_r28 = temp_r3;
            } else {
                var_r28 = Hu3DModelLink(temp_r30->unk4CB4[21]);
            }
            temp_r31->unk36 = var_r28;
        } else {
            var_r28 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r28, 1U);
        Hu3DModelAttrSet(var_r28, 0x40000002U);
        Hu3DModelLayerSet(var_r28, 2);
        temp_f31 = 135.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_f30 = (84.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 42.0f;
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = 180.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk32 = 0;
        temp_f31_2 = 4.0f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_f29 = 40.0f + (40.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f29;
        temp_r31->unk18.z = (f32) (0.10000000149011612 + ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)));
        temp_r31->unk24 = 1.0f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk28 = 1.0f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk2C = 0.0f;
        temp_r27 = Hu3DData[temp_r31->unk36].hsf;
        var_r29 = temp_r27->material;
        temp_r24 = temp_r27->materialNum;
        var_r26 = 0;
loop_16:
        if (var_r26 < temp_r24) {
            var_r29->color[0] = frandmod(0x80U) + 0x80;
            var_r29->color[1] = frandmod(0x80U) + 0x80;
            var_r29->color[2] = frandmod(0x80U) + 0x80;
            var_r26 += 1;
            var_r29++;
            goto loop_16;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk34 = frandmod(5U) + 1;
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        if (temp_r31->unk18.y < 0.0f) {
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 3:
        temp_r31->unk18.y = -3.0f - ((30.0f * ((f32) frandmod(0x2711U) / 10000.0f)) / 10.0f);
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 4:
        temp_r31->unk18.x *= 0.9f;
        temp_r31->unk18.z *= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.x += temp_r31->unk24;
        temp_r31->unkC.y += temp_r31->unk28;
        temp_r31->unkC.z += temp_r31->unk2C;
        if (temp_r31->unk0.y < -800.0f) {
            var_r25 = 1;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return var_r25;
}

s32 fn_1_97C8(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f31;
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r28;
    s16 var_r29;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[46] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x2E], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[46] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[46]);
            }
            if ((s16) temp_r30->unk4D20[5] < 0) {
                temp_r3_2 = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4D20[5] = temp_r3_2;
                var_r28 = temp_r3_2;
            } else {
                var_r28 = temp_r30->unk4D20[5];
            }
            Hu3DMotionSet(var_r29, var_r28);
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000001U);
        Hu3DModelAttrReset(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_f30 = (f32) temp_r31->unk32;
        temp_f31 = 50.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = 360.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unkC.z = 0.0f;
        var_f31 = 4.3f + (2.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        if ((temp_f30 > 90.0f) && (temp_f30 < 270.0f)) {
            var_f31 *= 0.7f;
        }
        temp_f29 = 45.0f + (40.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) var_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f29;
        temp_r31->unk18.z = (f32) ((f64) var_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk32 = 0;
        temp_r31->unk34 = (frandmod(6U) * 5) + 1;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        if (temp_r31->unk0.y < -700.0f) {
            temp_r31->unk30 += 1;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_9D5C(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r29;
    u32 var_r28;
    M528Work *temp_r30;

    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            var_r28 = frandmod(3U);
            if ((s32) var_r28 == 2) {
                var_r28 = 4;
            }
            if ((s16) temp_r30->unk4CB4[var_r28 + 0x24] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[var_r28 + 0x24], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[var_r28 + 0x24] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[var_r28 + 0x24]);
            }
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000001U);
        Hu3DModelAttrReset(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_f29 = 0.7f + ((f32) frandmod(0x2711U) / 10000.0f);
        Hu3DModelScaleSet(var_r29, temp_f29, temp_f29, 1.0f);
        temp_f30 = (84.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 42.0f;
        temp_f31 = 40.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_r31->unkC.x = 0.0f;
        temp_r31->unkC.y = 0.0f;
        temp_r31->unkC.z = 0.0f;
        temp_f31_2 = 4.2f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_f28 = 35.0f + (28.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f28;
        temp_r31->unk18.z = (f32) ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk2C = 5.0f + (5.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk32 = 0;
        temp_r31->unk34 = (frandmod(6U) * 5) + 1;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk30 += 1;
        break;
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.z += temp_r31->unk2C;
        if (temp_r31->unkC.z >= 360.0f) {
            temp_r31->unkC.z -= 360.0f;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return 0;
}

s32 fn_1_A3A0(M528Node *node) {
    u8 sp8[3];
    HSFDATA *temp_r27;
    HSFMATERIAL *var_r29;
    M528Part *temp_r31;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r23;
    s16 temp_r3;
    s16 var_r28;
    s32 var_r25;
    s32 var_r26;
    u32 temp_r24;
    M528Work *temp_r30;

    var_r25 = 0;
    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[38] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x26], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[38] = temp_r3;
                var_r28 = temp_r3;
            } else {
                var_r28 = Hu3DModelLink(temp_r30->unk4CB4[38]);
            }
            temp_r31->unk36 = var_r28;
        } else {
            var_r28 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r28, 1U);
        Hu3DModelAttrSet(var_r28, 0x40000002U);
        Hu3DModelLayerSet(var_r28, 2);
        temp_f29 = 0.1f + (0.5f * ((f32) frandmod(0x2711U) / 10000.0f));
        Hu3DModelScaleSet(var_r28, temp_f29, temp_f29, temp_f29);
        temp_f31 = 100.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_f30 = (84.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 42.0f;
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_f28 = (f32) frandmod(0x2711U) / 10000.0f;
        temp_r31->unkC.x = 350.0f - (60.0f * temp_f28);
        temp_r31->unkC.y = 180.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk32 = 0;
        temp_f31_2 = 4.0f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_f27 = 30.0f + (30.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f27;
        temp_r31->unk18.z = (f32) ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk24 = temp_f28;
        temp_r31->unk28 = 4.0f + (8.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk2C = 0.0f;
        temp_r27 = Hu3DData[temp_r31->unk36].hsf;
        var_r29 = temp_r27->material;
        temp_r23 = temp_r27->materialNum;
        temp_r24 = frandmod(3U);
        sp8[0] = 0x60;
        sp8[1] = 0x60;
        sp8[2] = 0x60;
        sp8[temp_r24] = frandmod(0x80U) + sp8[temp_r24] + 0x20;
        var_r26 = 0;
loop_16:
        if (var_r26 < temp_r23) {
            var_r29->color[0] = sp8[0];
            var_r29->color[1] = sp8[1];
            var_r29->color[2] = sp8[2];
            var_r26 += 1;
            var_r29++;
            goto loop_16;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk34 = (frandmod(3U) * 3) + 1;
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        if (temp_r31->unk18.y < 0.0f) {
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 3:
        temp_r31->unk18.y = -4.0f - ((30.0f * temp_r31->unk24) / 10.0f);
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 4:
        temp_r31->unk18.x *= 0.9f;
        temp_r31->unk18.z *= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        temp_r31->unkC.y += temp_r31->unk28;
        if (temp_r31->unk0.y < -800.0f) {
            var_r25 = 1;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return var_r25;
}

s32 fn_1_ABAC(M528Node *node) {
    M528Part *temp_r31;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s16 temp_r3;
    s16 var_r29;
    s32 var_r28;
    M528Work *temp_r30;

    var_r28 = 0;
    temp_r30 = lbl_1_bss_298->data;
    temp_r31 = node->unkC;
    temp_r0 = temp_r31->unk30;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unk36 < 0) {
            if ((s16) temp_r30->unk4CB4[39] < 0) {
                temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x27], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r30->unk4CB4[39] = temp_r3;
                var_r29 = temp_r3;
            } else {
                var_r29 = Hu3DModelLink(temp_r30->unk4CB4[39]);
            }
            temp_r31->unk36 = var_r29;
        } else {
            var_r29 = temp_r31->unk36;
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        temp_f29 = 0.1f + (0.5f * ((f32) frandmod(0x2711U) / 10000.0f));
        Hu3DModelScaleSet(var_r29, temp_f29, temp_f29, temp_f29);
        temp_f31 = 100.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_f30 = (84.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 42.0f;
        temp_r31->unk0.x = (f32) (((f64) (600.0f * (f32) temp_r30->unk4CB0) + ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0))) - 300.0);
        temp_r31->unk0.y = -300.0f;
        temp_r31->unk0.z = (f32) (((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0)) - 210.0);
        temp_f28 = (f32) frandmod(0x2711U) / 10000.0f;
        temp_r31->unkC.x = 350.0f - (60.0f * temp_f28);
        temp_r31->unkC.y = 180.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        temp_r31->unkC.z = 0.0f;
        temp_r31->unk32 = 0;
        temp_f31_2 = 4.0f + (4.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_f27 = 30.0f + (30.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk18.x = (f32) ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk18.y = temp_f27;
        temp_r31->unk18.z = (f32) ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
        temp_r31->unk24 = temp_f28;
        temp_r31->unk28 = 4.0f + (8.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->unk2C = 0.0f;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        temp_r31->unk32 = 0;
        temp_r31->unk34 = (frandmod(3U) * 3) + 1;
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 1:
        temp_r31->unk32 += 1;
        if ((s16) temp_r31->unk32 == (s16) temp_r31->unk34) {
            Hu3DModelAttrReset(temp_r31->unk36, 1U);
            temp_r31->unk30 += 1;
        }
        break;
    case 2:
        temp_r31->unk18.y -= 0.9f;
        if (temp_r31->unk18.y < 0.0f) {
            temp_r31->unk30 += 1;
        }
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unk0.y += temp_r31->unk18.y;
        temp_r31->unk0.z += temp_r31->unk18.z;
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    case 3:
        temp_r31->unk18.y = -4.0f - ((30.0f * temp_r31->unk24) / 10.0f);
        temp_r31->unk30 += 1;
        /* fallthrough */
    case 4:
        temp_r31->unk18.x *= 0.9f;
        temp_r31->unk18.z *= 0.9f;
        temp_r31->unk0.x += temp_r31->unk18.x;
        temp_r31->unkC.y += temp_r31->unk28;
        temp_r31->unk0.z = (f32) ((f64) temp_r31->unk0.z + ((f64) temp_r31->unk18.x + sin((3.141592653589793 * (f64) temp_r31->unkC.y) / 180.0)));
        temp_r31->unk0.y = (f32) ((f64) temp_r31->unk0.y + ((f64) temp_r31->unk18.y + cos((3.141592653589793 * (f64) temp_r31->unkC.y) / 180.0)));
        if (temp_r31->unk0.y < -800.0f) {
            var_r28 = 1;
        }
        Hu3DModelPosSetV(temp_r31->unk36, &temp_r31->unk0);
        Hu3DModelRotSetV(temp_r31->unk36, &temp_r31->unkC);
        break;
    }
    return var_r28;
}

void fn_1_B384(M528Work *work) {
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r31;

    temp_f31 = (f32) sin((3.141592653589793 * (f64) work->unk4C98) / 180.0);
    temp_f30 = (f32) cos((3.141592653589793 * (f64) work->unk4C98) / 180.0);
    var_r31 = 0;
loop_2:
    if (var_r31 < 0x37) {
        lbl_1_bss_4[var_r31].x = (temp_f30 * lbl_1_data_31C[var_r31].x) + (temp_f31 * lbl_1_data_31C[var_r31].z);
        lbl_1_bss_4[var_r31].z = ((temp_f31 * -lbl_1_data_31C[var_r31].x) + (temp_f30 * lbl_1_data_31C[var_r31].z)) - 1680.0f;
        lbl_1_bss_4[var_r31].y = lbl_1_data_31C[var_r31].y - 600.0f;
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_B528(M528Rail *rail, s16 delay) {
    s16 sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r28;
    s16 var_r29;
    M528Work *temp_r30;

    sp8 = delay;
    temp_r30 = lbl_1_bss_298->data;
    if ((s16) temp_r30->unk4CB4[46] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C8[0x2E], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->unk4CB4[46] = temp_r3;
        var_r29 = temp_r3;
    } else {
        var_r29 = Hu3DModelLink(temp_r30->unk4CB4[46]);
    }
    if ((s16) temp_r30->unk4D20[5] < 0) {
        temp_r3_2 = Hu3DJointMotion(var_r29, HuDataSelHeapReadNum((s32) lbl_1_data_2A0[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->unk4D20[5] = temp_r3_2;
        var_r28 = temp_r3_2;
    } else {
        var_r28 = temp_r30->unk4D20[5];
    }
    Hu3DMotionSet(var_r29, var_r28);
    Hu3DModelAttrSet(var_r29, 1U);
    Hu3DModelAttrSet(var_r29, 0x40000001U);
    Hu3DModelAttrReset(var_r29, 0x40000002U);
    Hu3DModelLayerSet(var_r29, 0);
    rail->unk20 = var_r29;
    rail->unk0 = lbl_1_bss_4[0];
    rail->unkC.x = 0.0f;
    rail->unkC.y = 0.0f;
    rail->unkC.z = 0.0f;
    rail->unk22 = 0;
    rail->unk24 = 0;
    rail->unk26 = 0;
    rail->unk28 = sp8;
    rail->unk2A = 0x37;
    Hu3DModelPosSetV(var_r29, &rail->unk0);
    Hu3DModelRotSetV(var_r29, &rail->unkC);
}

void fn_1_B6D4(M528Rail *rail) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    Vec *temp_r29;
    Vec *temp_r29_2;
    Vec *temp_r29_3;
    Vec *temp_r30;
    Vec *temp_r30_2;
    Vec *temp_r30_3;
    Vec *temp_r30_4;
    Vec *temp_r30_5;
    Vec *temp_r30_6;
    Vec *temp_r3;
    Vec *temp_r3_2;
    Vec *temp_r5;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f18;
    f32 temp_f19;
    f32 temp_f20;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    f32 var_f21;
    f32 var_f22;
    f32 var_f23;
    f32 var_f24;
    f32 var_f25;
    f32 var_f30;
    f32 var_f30_2;
    f32 var_f30_3;
    f32 var_f30_4;
    f32 var_f30_5;
    s16 temp_r0;
    s16 temp_r28;
    s16 temp_r28_2;
    s16 temp_r28_3;

    temp_r0 = rail->unk22;
    if ((u32) temp_r0 <= 0xCU) {
        switch (temp_r0) {
        case 1:
            rail->unk24 = 0;
            rail->unk22 += 1;
            /* fallthrough */
        case 2:
            rail->unk24 += 1;
            if ((s16) rail->unk24 >= (s16) rail->unk28) {
                rail->unk24 = 0;
                rail->unk22 += 1;
                return;
            }
            break;
        case 3:
            rail->unk24 = 0;
            rail->unk26 = 0;
            rail->unk0 = lbl_1_bss_4[0];
            if ((lbl_1_bss_4[1].z - lbl_1_bss_4->z) == 0.0f) {
                if ((lbl_1_bss_4[1].x - lbl_1_bss_4->x) >= 0.0f) {
                    var_f25 = 1.5707964f;
                } else {
                    var_f25 = -1.5707964f;
                }
            } else {
                sp18 = (f32) atan2((f64) (lbl_1_bss_4[1].x - lbl_1_bss_4->x), (f64) (lbl_1_bss_4[1].z - lbl_1_bss_4->z));
                var_f25 = sp18;
            }
            var_f30 = (f32) ((f64) (180.0f * var_f25) / acos(-1.0));
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            rail->unkC.y = var_f30;
            rail->unk18 = var_f30;
            if ((lbl_1_bss_4[2].z - lbl_1_bss_4[1].z) == 0.0f) {
                if ((lbl_1_bss_4[2].x - lbl_1_bss_4[1].x) >= 0.0f) {
                    var_f24 = 1.5707964f;
                } else {
                    var_f24 = -1.5707964f;
                }
            } else {
                sp14 = (f32) atan2((f64) (lbl_1_bss_4[2].x - lbl_1_bss_4[1].x), (f64) (lbl_1_bss_4[2].z - lbl_1_bss_4[1].z));
                var_f24 = sp14;
            }
            var_f30_2 = (f32) ((f64) (180.0f * var_f24) / acos(-1.0));
            if (var_f30_2 < 0.0f) {
                var_f30_2 += 360.0f;
            }
            rail->unk1C = var_f30_2;
            if (rail->unk1C < rail->unk18) {
                rail->unk1C += 360.0f;
            }
            Hu3DModelAttrReset(rail->unk20, 1U);
            rail->unk22 += 1;
            /* fallthrough */
        case 4:
            rail->unk24 += 1;
            temp_f31 = (f32) rail->unk24 / 120.0f;
            temp_r28 = rail->unk26;
            temp_r30 = &lbl_1_bss_4[temp_r28];
            temp_r3 = &lbl_1_bss_4[temp_r28];
            temp_r29 = temp_r3 + 1;
            rail->unk0.x = (temp_r30->x * (1.0f - temp_f31)) + (temp_r3[1].x * temp_f31);
            rail->unk0.y = (temp_r30->y * (1.0f - temp_f31)) + (temp_r29->y * temp_f31);
            rail->unk0.z = (temp_r30->z * (1.0f - temp_f31)) + (temp_r29->z * temp_f31);
            Hu3DModelPosSetV(rail->unk20, &rail->unk0);
            Hu3DModelRotSetV(rail->unk20, &rail->unkC);
            if ((s16) rail->unk24 == 0x78) {
                rail->unk24 = 0;
                rail->unk26 += 1;
                rail->unk22 += 1;
                return;
            }
            break;
        case 5:
            rail->unk18 = rail->unkC.y;
            rail->unk22 += 1;
            /* fallthrough */
        case 6:
            rail->unk24 += 1;
            temp_f31_2 = (f32) rail->unk24 / 60.0f;
            rail->unkC.y = (rail->unk18 * (1.0f - temp_f31_2)) + (rail->unk1C * temp_f31_2);
            Hu3DModelPosSetV(rail->unk20, &rail->unk0);
            Hu3DModelRotSetV(rail->unk20, &rail->unkC);
            if ((s16) rail->unk24 == 0x3C) {
                rail->unk18 = rail->unkC.y;
                temp_r30_2 = &lbl_1_bss_4[rail->unk26];
                temp_f19 = temp_r30_2[1].z - temp_r30_2->z;
                temp_f20 = temp_r30_2[1].x - temp_r30_2->x;
                if (temp_f19 == 0.0f) {
                    if (temp_f20 >= 0.0f) {
                        var_f23 = 1.5707964f;
                    } else {
                        var_f23 = -1.5707964f;
                    }
                } else {
                    sp10 = (f32) atan2((f64) temp_f20, (f64) temp_f19);
                    var_f23 = sp10;
                }
                var_f30_3 = (f32) ((f64) (180.0f * var_f23) / acos(-1.0));
loop_33:
                if (var_f30_3 < rail->unk18) {
                    var_f30_3 += 360.0f;
                    goto loop_33;
                }
                rail->unk1C = var_f30_3;
                rail->unk24 = 0;
                rail->unk22 += 1;
                return;
            }
            break;
        case 7:
            rail->unk18 = rail->unkC.y;
            temp_r30_3 = &lbl_1_bss_4[rail->unk26];
            temp_f0 = temp_r30_3[1].z - temp_r30_3->z;
            sp24 = temp_f0;
            temp_f18 = temp_r30_3[1].x - temp_r30_3->x;
            if (temp_f0 == 0.0f) {
                if (temp_f18 >= 0.0f) {
                    var_f22 = 1.5707964f;
                } else {
                    var_f22 = -1.5707964f;
                }
            } else {
                spC = (f32) atan2((f64) temp_f18, (f64) sp24);
                var_f22 = spC;
            }
            var_f30_4 = (f32) ((f64) (180.0f * var_f22) / acos(-1.0));
loop_42:
            if (var_f30_4 < rail->unk18) {
                var_f30_4 += 360.0f;
                goto loop_42;
            }
            if ((var_f30_4 - rail->unk18) > 180.0f) {
                var_f30_4 = rail->unk18;
            }
            rail->unk1C = var_f30_4;
            rail->unk22 += 1;
            /* fallthrough */
        case 8:
            rail->unk24 += 1;
            temp_f31_3 = (f32) rail->unk24 / 30.0f;
            temp_r28_2 = rail->unk26;
            temp_r30_4 = &lbl_1_bss_4[temp_r28_2];
            temp_r3_2 = &lbl_1_bss_4[temp_r28_2];
            temp_r29_2 = temp_r3_2 + 1;
            rail->unk0.x = (temp_r30_4->x * (1.0f - temp_f31_3)) + (temp_r3_2[1].x * temp_f31_3);
            rail->unk0.y = (temp_r30_4->y * (1.0f - temp_f31_3)) + (temp_r29_2->y * temp_f31_3);
            rail->unk0.z = (temp_r30_4->z * (1.0f - temp_f31_3)) + (temp_r29_2->z * temp_f31_3);
            rail->unkC.y = (rail->unk18 * (1.0f - temp_f31_3)) + (rail->unk1C * temp_f31_3);
            Hu3DModelPosSetV(rail->unk20, &rail->unk0);
            Hu3DModelRotSetV(rail->unk20, &rail->unkC);
            if ((s16) rail->unk24 == 0x1E) {
                rail->unk26 += 1;
                rail->unk24 = 0;
                if ((s16) rail->unk26 == (s32) (rail->unk2A - 2)) {
                    rail->unk22 += 1;
                    return;
                }
                rail->unk22 -= 1;
                return;
            }
            break;
        case 9:
            rail->unk18 = rail->unkC.y;
            temp_r30_5 = &lbl_1_bss_4[rail->unk26];
            temp_f0_2 = temp_r30_5[1].z - temp_r30_5->z;
            sp1C = temp_f0_2;
            sp20 = temp_r30_5[1].x - temp_r30_5->x;
            if (temp_f0_2 == 0.0f) {
                if (sp20 >= 0.0f) {
                    var_f21 = 1.5707964f;
                } else {
                    var_f21 = -1.5707964f;
                }
            } else {
                sp8 = (f32) atan2((f64) sp20, (f64) sp1C);
                var_f21 = sp8;
            }
            var_f30_5 = (f32) ((f64) (180.0f * var_f21) / acos(-1.0));
loop_57:
            if (var_f30_5 < rail->unk18) {
                var_f30_5 += 360.0f;
                goto loop_57;
            }
            rail->unk1C = var_f30_5;
            rail->unk22 += 1;
            /* fallthrough */
        case 10:
            rail->unk24 += 1;
            temp_f31_4 = (f32) rail->unk24 / 60.0f;
            rail->unkC.y = (rail->unk18 * (1.0f - temp_f31_4)) + (rail->unk1C * temp_f31_4);
            Hu3DModelPosSetV(rail->unk20, &rail->unk0);
            Hu3DModelRotSetV(rail->unk20, &rail->unkC);
            if ((s16) rail->unk24 == 0x3C) {
                rail->unk24 = 0;
                rail->unk22 += 1;
                return;
            }
            break;
        case 11:
            rail->unk24 += 1;
            temp_f31_5 = (f32) rail->unk24 / 120.0f;
            temp_r28_3 = rail->unk26;
            temp_r30_6 = &lbl_1_bss_4[temp_r28_3];
            temp_r5 = &lbl_1_bss_4[temp_r28_3];
            temp_r29_3 = temp_r5 + 1;
            rail->unk0.x = (temp_r30_6->x * (1.0f - temp_f31_5)) + (temp_r5[1].x * temp_f31_5);
            rail->unk0.y = (temp_r30_6->y * (1.0f - temp_f31_5)) + (temp_r29_3->y * temp_f31_5);
            rail->unk0.z = (temp_r30_6->z * (1.0f - temp_f31_5)) + (temp_r29_3->z * temp_f31_5);
            Hu3DModelPosSetV(rail->unk20, &rail->unk0);
            Hu3DModelRotSetV(rail->unk20, &rail->unkC);
            if ((s16) rail->unk24 == 0x78) {
                rail->unk24 = 0;
                rail->unk26 += 1;
                rail->unk22 += 1;
                return;
            }
            break;
        case 12:
            rail->unk24 += 1;
            if ((s16) rail->unk24 == 0x5A) {
                rail->unk24 = 0;
                rail->unk22 = 3;
            }
            break;
        }
    }
}

void fn_1_C314(M528Work *work) {
    M528Node *temp_r31;
    s32 var_r30;

    var_r30 = 0;
loop_8:
    if (var_r30 < 0x80) {
        temp_r31 = work->unk3E0;
        if (temp_r31 != NULL) {
            work->unk3E0 = temp_r31->unk4;
            temp_r31->unk8 = fn_1_6DF0;
            temp_r31->unkC = &work->unk13E4[var_r30];
            temp_r31->unk4 = work->unk3DC;
            if ((M528Node *) temp_r31->unk4 != NULL) {
                temp_r31->unk4->unk0 = temp_r31;
            }
            work->unk3DC = temp_r31;
        }
        if (temp_r31 != NULL) {
            work->unk13E4[var_r30].unk30 = 0;
            work->unk13E4[var_r30].unk36 = -1;
        }
        var_r30 += 1;
        goto loop_8;
    }
}

void fn_1_C3DC(M528Work *work) {
    M528Node *temp_r30;
    M528Node *temp_r31;
    s32 var_r29;

    temp_r31 = work->unk3E0;
    if (temp_r31 != NULL) {
        work->unk3E0 = temp_r31->unk4;
        temp_r31->unk8 = fn_1_7794;
        temp_r31->unkC = &work->unk13E4[0];
        temp_r31->unk4 = work->unk3DC;
        if ((M528Node *) temp_r31->unk4 != NULL) {
            temp_r31->unk4->unk0 = temp_r31;
        }
        work->unk3DC = temp_r31;
    }
    if (temp_r31 != NULL) {
        work->unk13E4[0].unk30 = 0;
        work->unk13E4[0].unk36 = -1;
    }
    var_r29 = 1;
loop_14:
    if (var_r29 < 0x80) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_72E4;
            temp_r30->unkC = &work->unk13E4[var_r29];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r29].unk30 = 0;
            work->unk13E4[var_r29].unk36 = -1;
        }
        var_r29 += 1;
        goto loop_14;
    }
}

void fn_1_C530(M528Work *work) {
    M528Node *temp_r28;
    M528Node *temp_r29;
    M528Node *temp_r30;
    s32 var_r31;

    var_r31 = 0;
loop_8:
    if (var_r31 < 0xA) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_9D5C;
            temp_r30->unkC = &work->unk13E4[var_r31];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r31].unk30 = 0;
            work->unk13E4[var_r31].unk36 = -1;
        }
        var_r31 += 1;
        goto loop_8;
    }
loop_17:
    if (var_r31 < 0x5A) {
        temp_r29 = work->unk3E0;
        if (temp_r29 != NULL) {
            work->unk3E0 = temp_r29->unk4;
            temp_r29->unk8 = fn_1_A3A0;
            temp_r29->unkC = &work->unk13E4[var_r31];
            temp_r29->unk4 = work->unk3DC;
            if ((M528Node *) temp_r29->unk4 != NULL) {
                temp_r29->unk4->unk0 = temp_r29;
            }
            work->unk3DC = temp_r29;
        }
        if (temp_r29 != NULL) {
            work->unk13E4[var_r31].unk30 = 0;
            work->unk13E4[var_r31].unk36 = -1;
        }
        var_r31 += 1;
        goto loop_17;
    }
loop_26:
    if (var_r31 < 0x5F) {
        temp_r28 = work->unk3E0;
        if (temp_r28 != NULL) {
            work->unk3E0 = temp_r28->unk4;
            temp_r28->unk8 = fn_1_ABAC;
            temp_r28->unkC = &work->unk13E4[var_r31];
            temp_r28->unk4 = work->unk3DC;
            if ((M528Node *) temp_r28->unk4 != NULL) {
                temp_r28->unk4->unk0 = temp_r28;
            }
            work->unk3DC = temp_r28;
        }
        if (temp_r28 != NULL) {
            work->unk13E4[var_r31].unk30 = 0;
            work->unk13E4[var_r31].unk36 = -1;
        }
        var_r31 += 1;
        goto loop_26;
    }
}

void fn_1_C728(M528Work *work) {
    s32 sp8[0x18];
    M528Node *temp_r30;
    s16 temp_r28;
    s16 temp_r3;
    s16 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x18) {
        sp8[var_r31] = var_r31;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 0xC) {
        temp_r28 = frandmod(0x18U);
        temp_r3 = frandmod(0x18U);
        { s32 swapTmp = sp8[temp_r28]; sp8[temp_r28] = sp8[temp_r3]; sp8[temp_r3] = swapTmp; }
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_14:
    if (var_r31_3 < 0x18) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_7B44;
            temp_r30->unkC = &work->unk13E4[var_r31_3];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r31_3].unk30 = 0;
            work->unk13E4[var_r31_3].unk36 = -1;
            work->unk13E4[var_r31_3].unk32 = sp8[var_r31_3];
            work->unk13E4[var_r31_3].unk34 = (var_r31_3 * 0xA) + 0xA;
        }
        var_r31_3 += 1;
        goto loop_14;
    }
}

void fn_1_C8B4(M528Work *work) {
    s32 sp8[0x18];
    M528Node *temp_r30;
    s16 temp_r28;
    s16 temp_r3;
    s16 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x18) {
        sp8[var_r31] = var_r31;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 0xC) {
        temp_r28 = frandmod(0x18U);
        temp_r3 = frandmod(0x18U);
        { s32 swapTmp = sp8[temp_r28]; sp8[temp_r28] = sp8[temp_r3]; sp8[temp_r3] = swapTmp; }
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_14:
    if (var_r31_3 < 0x18) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_97C8;
            temp_r30->unkC = &work->unk13E4[var_r31_3];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r31_3].unk30 = 0;
            work->unk13E4[var_r31_3].unk36 = -1;
            work->unk13E4[var_r31_3].unk32 = (sp8[var_r31_3] * 4) - 0x2E;
        }
        var_r31_3 += 1;
        goto loop_14;
    }
}

void fn_1_CA34(M528Work *work) {
    M528Node *temp_r31;

    temp_r31 = work->unk3E0;
    if (temp_r31 != NULL) {
        work->unk3E0 = temp_r31->unk4;
        temp_r31->unk8 = fn_1_800C;
        temp_r31->unkC = &work->unk13E4[0];
        temp_r31->unk4 = work->unk3DC;
        if ((M528Node *) temp_r31->unk4 != NULL) {
            temp_r31->unk4->unk0 = temp_r31;
        }
        work->unk3DC = temp_r31;
    }
    if (temp_r31 != NULL) {
        work->unk13E4[0].unk30 = 0;
        work->unk13E4[0].unk36 = -1;
    }
}

void fn_1_CAEC(M528Work *work) {
    M528Node *temp_r30;
    M528Node *temp_r31;
    s32 var_r29;

    temp_r31 = work->unk3E0;
    if (temp_r31 != NULL) {
        work->unk3E0 = temp_r31->unk4;
        temp_r31->unk8 = fn_1_83E4;
        temp_r31->unkC = &work->unk13E4[0];
        temp_r31->unk4 = work->unk3DC;
        if ((M528Node *) temp_r31->unk4 != NULL) {
            temp_r31->unk4->unk0 = temp_r31;
        }
        work->unk3DC = temp_r31;
    }
    if (temp_r31 != NULL) {
        work->unk13E4[0].unk30 = 0;
        work->unk13E4[0].unk36 = -1;
    }
    var_r29 = 1;
loop_14:
    if (var_r29 < 0x23) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_87F4;
            temp_r30->unkC = &work->unk13E4[var_r29];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r29].unk30 = 0;
            work->unk13E4[var_r29].unk36 = -1;
        }
        var_r29 += 1;
        goto loop_14;
    }
}

void fn_1_CC40(M528Work *work) {
    M528Node *temp_r30;
    M528Node *temp_r31;
    s32 var_r29;

    temp_r31 = work->unk3E0;
    if (temp_r31 != NULL) {
        work->unk3E0 = temp_r31->unk4;
        temp_r31->unk8 = fn_1_8CD0;
        temp_r31->unkC = &work->unk13E4[0];
        temp_r31->unk4 = work->unk3DC;
        if ((M528Node *) temp_r31->unk4 != NULL) {
            temp_r31->unk4->unk0 = temp_r31;
        }
        work->unk3DC = temp_r31;
    }
    if (temp_r31 != NULL) {
        work->unk13E4[0].unk30 = 0;
        work->unk13E4[0].unk36 = -1;
    }
    var_r29 = 1;
loop_14:
    if (var_r29 < 0x80) {
        temp_r30 = work->unk3E0;
        if (temp_r30 != NULL) {
            work->unk3E0 = temp_r30->unk4;
            temp_r30->unk8 = fn_1_8FFC;
            temp_r30->unkC = &work->unk13E4[var_r29];
            temp_r30->unk4 = work->unk3DC;
            if ((M528Node *) temp_r30->unk4 != NULL) {
                temp_r30->unk4->unk0 = temp_r30;
            }
            work->unk3DC = temp_r30;
        }
        if (temp_r30 != NULL) {
            work->unk13E4[var_r29].unk30 = 0;
            work->unk13E4[var_r29].unk36 = -1;
        }
        var_r29 += 1;
        goto loop_14;
    }
}
