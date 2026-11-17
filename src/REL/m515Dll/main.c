// MP5 m515 (Hotel Goomba), generated from its m2c draft by tools/mp5/ports/m515Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m515Dll (tools/mp5/decomp.py m515Dll --types tools/mp5/types/m515Dll.h)
// Written from the draft: Hotel Goomba (4 players, free for all). Every player has a 5x5 grid of room tiles (a doubly
// linked graph, walked with the stick; A hits a Goomba in the next room) in its own quarter of the screen. COM players
// follow scripted input lists (lbl_1_data_1184.., picked in fn_1_E274). Runs on MP5's MgSeq sequencer.
// Offsets are GameCube's (pointers 4 bytes there, 8 here: allocate with sizeof, see m515Dll_fix.py).
// objdata: M515Player
// objdata ObjectSetup fn_1_29D0 fn_1_2AC0: M515Main
// objexpr lbl_1_bss_4: M515Main
// var fn_1_26C temp_r30: M515Player
// var fn_1_968 temp_r31: M515Player
// var fn_1_B08 temp_r31: M515Player
// var fn_1_D30 temp_r30: M515Player
// var fn_1_D30 temp_r30_2: M515Player
// var fn_1_D30 temp_r30_3: M515Player
// var fn_1_D30 temp_r30_4: M515Player
// var fn_1_D30 temp_r30_5: M515Player
// var fn_1_D30 temp_r30_6: M515Player
// var fn_1_1B58 temp_r30: M515Player
// var fn_1_1B58 temp_r30_2: M515Player
// var fn_1_1D60 temp_r4_2: M515Node
// var fn_1_1D60 temp_r4_3: M515Node
// var fn_1_1D60 temp_r5: M515Node
// var fn_1_2AC0 temp_r4: M515Player
// var fn_1_6FE8 temp_r4: Vec
// var fn_1_6FE8 temp_r4_2: Vec
// var fn_1_6FE8 temp_r5: M515Obj
// var fn_1_6FE8 temp_r5_2: M515Obj
// var fn_1_C2B0 temp_r4_3: Vec
// var fn_1_C2B0 temp_r4_4: Vec
// var fn_1_C2B0 temp_r5: M515Obj
// var fn_1_C2B0 temp_r5_2: M515Obj
// var fn_1_D384 temp_r4_6: Vec
// var fn_1_D384 temp_r4_7: Vec
// var fn_1_D384 temp_r5: M515Obj
// var fn_1_D384 temp_r5_2: M515Obj
// var fn_1_CC20 temp_r30: M515Player
// var fn_1_CC20 temp_r30_2: M515Player

struct M515Node;
struct M515Obj;
struct M515Main;
struct M515Player;
struct M515Cam;
struct M515Fx;

typedef struct M515Place { // a piece of room decoration (lbl_1_data_B0C..): model piece, tile, rotation; piece -1 ends
    s16 piece;
    s16 pos;
    f32 rot;
} M515Place;

typedef struct M515Obj { // a Goomba and its shadow, 0x2C (M515Player::unk488[8])
    s16 unk0; // model
    s16 unk2; // motion
    s16 unk4; // second model
    s16 unk6;
    Vec unk8; // from
    Vec unk14; // to
    s16 unk20; // state
    s16 unk22; // timer
    s16 unk24; // facing / kind
    s16 unk26;
    f32 unk28; // wobble angle
} M515Obj;

typedef struct M515Node { // a room tile, 0x28
    struct M515Node *unk0; // +x
    struct M515Node *unk4; // -x
    struct M515Node *unk8; // +z
    struct M515Node *unkC; // -z
    s32 unk10;
    struct M515Obj *unk14; // Goomba standing here
    Vec unk18; // position
    u16 unk24; // type: 0 floor, 2 Goomba, 3/4 entrance / exit
    u16 unk26;
} M515Node;

typedef struct M515Com { // COM brain (M515Player::unk690), 0x10
    s16 unk0; // state
    s16 unk2; // timer
    s16 unk4; // level
    s16 unk6; // script index
    s16 unk8; // random wait
    s16 unkA;
    u16 *unkC; // input script
} M515Com;

typedef struct M515Cam { // 0x30
    f32 unk0; // elevation
    f32 unk4; // azimuth
    f32 unk8; // distance
    Vec unkC; // target
    Vec unk18; // saved target
    s16 unk24; // state
    s16 unk26; // timer
    s16 unk28; // player
    s16 unk2A;
    s32 unk2C;
} M515Cam;

typedef struct M515Seq { // per player state machine, 0x10
    s16 unk0; // state
    s16 unk2; // timer
    struct M515Cam *unk4; // camera
    s32 (*unk8)(struct M515Cam *); // running camera move
    s32 unkC; // player
} M515Seq;

typedef struct M515Player { // OMOBJ::data, 0x6A0
    s16 unk0; // player
    s16 unk2; // character
    s16 unk4; // pad
    s16 unk6;
    s16 unk8;
    s16 unkA; // COM
    s16 unkC; // difficulty
    s16 unkE; // side of the hotel (0 front, 1 back, 2 top)
    struct M515Node unk10[25]; // room tiles
    struct M515Node *unk3F8; // current tile
    struct M515Node unk3FC; // entrance below
    struct M515Node unk424; // entrance above
    Vec unk44C; // position
    Vec unk458; // rotation
    Vec unk464; // move from
    Vec unk470; // move to
    s16 unk47C; // facing
    s16 unk47E; // wanted facing
    s16 unk480; // hit timer
    s16 unk482; // mode
    s16 unk484; // move timer
    s16 unk486; // turn timer
    struct M515Obj unk488[8];
    s16 unk5E8; // Goomba count
    s16 unk5EA[75]; // decoration models
    u16 unk680; // input
    s16 unk682; // buffered A
    struct M515Seq *unk684;
    s32 (*unk688)(struct M515Seq *, struct M515Player *);
    OMOBJ *unk68C;
    struct M515Com unk690;
} M515Player;

typedef struct M515Gate { // an opening door, 0x28 (M515Main::unk130)
    s32 unk0; // state
    s32 unk4; // frames
    s32 unk8; // timer
    s16 unkC; // model
    s16 unkE;
    f32 unk10; // wobble angle
    f32 unk14;
    f32 unk18; // wobble speed
    Vec unk1C; // position
} M515Gate;

typedef struct M515Wipe { // the screen split (0x334)
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M515Wipe;

typedef struct M515Fx { // a model shown / hidden with its motion, 0x14
    s16 unk0; // model
    s16 unk2; // motion
    s16 unk4; // state
    s16 unk6;
    s32 (*unk8)(struct M515Fx *);
    struct M515Fx *unkC; // previous
    struct M515Fx *unk10; // next
} M515Fx;

typedef struct M515Main { // 0xCB0
    s16 unk0;
    s16 unk2[3]; // layout set of each side
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE[4];
    s16 unk16[4];
    s16 unk1E[4];
    s16 unk26[4];
    s16 unk2E[4];
    s16 unk36[4];
    s16 unk3E[4];
    s16 unk46[4];
    s16 unk4E[4];
    s16 unk56[4];
    s16 unk5E[8];
    s16 unk6E[4];
    s16 unk76[16];
    s16 unk96[8];
    s16 unkA6[4];
    s16 unkAE[4];
    s16 unkB6[12];
    s16 unkCE[4];
    s16 unkD6;
    s16 unkD8;
    s16 unkDA;
    s16 unkDC;
    s16 unkDE;
    s16 unkE0[8];
    s16 unkF0;
    s16 unkF2;
    s16 unkF4;
    s16 unkF6;
    s16 unkF8;
    s16 unkFA;
    s16 unkFC;
    s16 unkFE;
    s16 unk100;
    s16 unk102;
    s16 unk104;
    s16 unk106;
    s16 unk108;
    s16 unk10A;
    s16 unk10C[17];
    s16 unk12E;
    struct M515Gate unk130[4];
    s16 unk1D0;
    s16 unk1D2;
    s16 unk1D4;
    s16 unk1D6;
    s16 unk1D8;
    s16 unk1DA;
    s16 unk1DC[12];
    s32 unk1F4;
    s16 unk1F8[6];
    s16 unk204[6];
    s16 unk210[6];
    s16 unk21C;
    s16 unk21E;
    s16 unk220;
    s16 unk222;
    struct M515Player *unk224[4];
    struct M515Cam unk234[4];
    struct M515Seq unk2F4[4];
    struct M515Wipe unk334;
    struct M515Fx *unk344; // active list
    struct M515Fx *unk348; // free list
    struct M515Fx unk34C[0x78];
    s16 unkCAC;
    s16 unkCAE;
} M515Main;


void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_26C(s16 mode, s16 frameNo);
void fn_1_928(s16 mode, s16 frameNo);
void fn_1_968(s16 mode, s16 frameNo);
void fn_1_B08(s16 mode, s16 frameNo);
void fn_1_D30(s16 mode, s16 frameNo);
void fn_1_1B58(s16 mode, s16 frameNo);
void fn_1_1D20(s16 mode, s16 frameNo);
void fn_1_1D24(s16 mode, s16 frameNo);
void fn_1_1D60(OMOBJ *obj);
void fn_1_2684(OMOBJ *obj);
void fn_1_29D0(OMOBJ *obj);
void fn_1_2AC0(OMOBJ *obj);
void fn_1_2B6C(M515Main *arg0);
void fn_1_2EB4(void);
void fn_1_2F3C(M515Main *arg0);
void fn_1_32C4(M515Main *arg0);
void fn_1_5C40(M515Main *arg0);
M515Fx *fn_1_5CE4(M515Main *arg0);
void fn_1_5D48(M515Main *arg0, M515Fx *arg1);
void fn_1_5DB0(M515Main *arg0);
void fn_1_5E88(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit);
void fn_1_5F2C(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit);
s32 fn_1_5FD0(M515Player *arg0);
void fn_1_60E8(M515Player *arg0, M515Node *arg1);
s32 fn_1_611C(M515Player *arg0);
void fn_1_62FC(M515Player *arg0, s16 arg1);
void fn_1_6318(M515Player *arg0);
s32 fn_1_6324(M515Player *arg0, M515Main *arg1);
s16 fn_1_66D0(M515Player *arg0);
void fn_1_6980(M515Player *arg0);
void fn_1_69B8(M515Player *arg0, M515Main *arg1);
void fn_1_6FE8(M515Player *arg0);
void fn_1_72E4(M515Player *arg0);
void fn_1_73B0(M515Player *arg0, s32 arg1);
void fn_1_7768(M515Player *arg0, s32 arg1);
void fn_1_77F0(M515Player *arg0, s32 arg1);
s16 fn_1_7878(M515Player *arg0);
u16 fn_1_7924(M515Player *arg0);
void fn_1_7BE8(M515Obj *arg0, M515Main *arg1);
void fn_1_7E5C(M515Cam *arg0, s16 arg1);
void fn_1_7EE0(M515Cam *arg0);
void fn_1_81A8(M515Cam *arg0, M515Player *arg1);
s32 fn_1_83E8(M515Cam *arg0);
s32 fn_1_86F4(M515Cam *arg0);
s32 fn_1_8964(M515Cam *arg0);
s32 fn_1_8BD4(M515Cam *arg0);
s32 fn_1_8E44(M515Cam *arg0);
s32 fn_1_90B4(M515Cam *arg0);
s32 fn_1_9324(M515Cam *arg0);
s32 fn_1_9594(M515Cam *arg0);
void fn_1_9804(M515Seq *arg0, M515Cam *arg1, s32 arg2);
void fn_1_9828(M515Wipe *arg0);
void fn_1_9920(M515Wipe *arg0);
void fn_1_9958(M515Wipe *arg0);
s32 fn_1_9DF8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_B0B8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_B5D8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_BA64(M515Seq *arg0, M515Player *arg1);
f32 fn_1_BD10(s16 mdl, s16 side, f32 t);
void fn_1_BE78(M515Main *arg0, s16 mdl, s16 arg2);
void fn_1_BF24(M515Main *arg0, s16 mdl, s16 arg2);
s32 fn_1_BFD0(M515Fx *arg0);
s32 fn_1_C0D0(M515Fx *arg0);
s32 fn_1_C150(M515Fx *arg0);
s32 fn_1_C26C(M515Fx *arg0);
void fn_1_C2B0(M515Player *arg0);
void fn_1_C83C(void);
void fn_1_C958(s32 arg0, Vec *arg1, s32 arg2);
void fn_1_CAF0(M515Main *arg0, s32 arg1);
void fn_1_CB60(M515Main *arg0, s32 arg1);
void fn_1_CC20(s16 layerNo);
void fn_1_CE98(M515Main *arg0);
void fn_1_D0D8(M515Main *arg0);
void fn_1_D384(M515Player *arg0);
s32 fn_1_D928(M515Seq *arg0, M515Player *arg1);
u16 fn_1_DD18(M515Player *arg0);
void fn_1_E274(M515Com *arg0, s16 side, s16 dif);
void fn_1_E548(M515Player *arg0);

void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_26C(s16 mode, s16 frameNo);
void fn_1_928(s16 mode, s16 frameNo);
void fn_1_968(s16 mode, s16 frameNo);
void fn_1_B08(s16 mode, s16 frameNo);
void fn_1_D30(s16 mode, s16 frameNo);
void fn_1_1B58(s16 mode, s16 frameNo);
void fn_1_1D20(s16 mode, s16 frameNo);
void fn_1_1D24(s16 mode, s16 frameNo);
void fn_1_1D60(omObjData *obj);
void fn_1_2684(omObjData *obj);
void fn_1_29D0(omObjData *obj);
void fn_1_2AC0(omObjData *obj);
void fn_1_2B6C(M515Main *arg0);
void fn_1_2EB4(void);
void fn_1_2F3C(M515Main *arg0);
void fn_1_32C4(M515Main *arg0);
void fn_1_5C40(M515Main *arg0);
void fn_1_5DB0(M515Main *arg0);
void fn_1_5E88(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit);
void fn_1_5F2C(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit);
s32 fn_1_5FD0(M515Player *arg0);
s32 fn_1_611C(M515Player *arg0);
void fn_1_6318(M515Player *arg0);
s32 fn_1_6324(M515Player *arg0, M515Main *arg1);
s16 fn_1_66D0(M515Player *arg0);
void fn_1_6980(M515Player *arg0);
void fn_1_69B8(M515Player *arg0, M515Main *arg1);
void fn_1_6FE8(M515Player *arg0);
void fn_1_73B0(M515Player *arg0, s32 arg1);
void fn_1_7768(M515Player *arg0, s32 arg1);
void fn_1_77F0(M515Player *arg0, s32 arg1);
s16 fn_1_7878(M515Player *arg0);
u16 fn_1_7924(M515Player *arg0);
void fn_1_7BE8(M515Obj *arg0, M515Main *arg1);
void fn_1_7E5C(M515Cam *arg0, s16 arg1);
void fn_1_7EE0(M515Cam *arg0);
void fn_1_81A8(M515Cam *arg0, M515Player *arg1);
s32 fn_1_83E8(M515Cam *arg0);
s32 fn_1_86F4(M515Cam *arg0);
s32 fn_1_8964(M515Cam *arg0);
s32 fn_1_8BD4(M515Cam *arg0);
s32 fn_1_8E44(M515Cam *arg0);
s32 fn_1_90B4(M515Cam *arg0);
s32 fn_1_9324(M515Cam *arg0);
s32 fn_1_9594(M515Cam *arg0);
void fn_1_9804(M515Seq *arg0, M515Cam *arg1, s32 arg2);
void fn_1_9828(M515Wipe *arg0);
void fn_1_9920(M515Wipe *arg0);
void fn_1_9958(M515Wipe *arg0);
s32 fn_1_9DF8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_B0B8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_B5D8(M515Seq *arg0, M515Player *arg1);
s32 fn_1_BA64(M515Seq *arg0, M515Player *arg1);
f32 fn_1_BD10(s16 mdl, s16 side, f32 t);
void fn_1_BE78(M515Main *arg0, s16 mdl, s16 arg2);
void fn_1_BF24(M515Main *arg0, s16 mdl, s16 arg2);
s32 fn_1_BFD0(M515Fx *arg0);
s32 fn_1_C0D0(M515Fx *arg0);
s32 fn_1_C150(M515Fx *arg0);
s32 fn_1_C26C(M515Fx *arg0);
void fn_1_C2B0(M515Player *arg0);
void fn_1_C83C(void);
void fn_1_C958(s32 arg0, Vec *arg1, s32 arg2);
void fn_1_CAF0(M515Main *arg0, s32 arg1);
void fn_1_CB60(M515Main *arg0, s32 arg1);
void fn_1_CC20(s16 layerNo);
void fn_1_CE98(M515Main *arg0);
void fn_1_D0D8(M515Main *arg0);
void fn_1_D384(M515Player *arg0);
s32 fn_1_D928(M515Seq *arg0, M515Player *arg1);
u16 fn_1_DD18(M515Player *arg0);
void fn_1_E274(M515Com *arg0, s16 side, s16 dif);
void fn_1_E548(M515Player *arg0);

MGSEQ_PARAM lbl_1_data_0 = {
    0x12C,
    0,
    fn_1_1FC,
    fn_1_26C,
    fn_1_928,
    fn_1_968,
    fn_1_B08,
    fn_1_D30,
    fn_1_1B58,
    fn_1_1D20,
    fn_1_1D24,
};
f32 lbl_1_data_28[0x3C] = {
    270.0f,
    10.0f,
    4240.0f,
    0.0f,
    108.0f,
    204.0f,
    420.0f,
    40.0f,
    6000.0f,
    25.0f,
    25.0f,
    75.0f,
    420.0f,
    40.0f,
    6000.0f,
    25.0f,
    25.0f,
    -900.0f,
    240.0f,
    40.0f,
    6000.0f,
    -25.0f,
    425.0f,
    -675.0f,
    240.0f,
    40.0f,
    6000.0f,
    -25.0f,
    425.0f,
    -75.0f,
    240.0f,
    40.0f,
    6000.0f,
    -25.0f,
    425.0f,
    900.0f,
    60.0f,
    40.0f,
    6000.0f,
    25.0f,
    825.0f,
    675.0f,
    60.0f,
    40.0f,
    6000.0f,
    25.0f,
    825.0f,
    75.0f,
    90.0f,
    15.0f,
    1900.0f,
    0.0f,
    1000.0f,
    -225.0f,
    90.0f,
    4.0f,
    1970.0f,
    0.0f,
    150.0f,
    -225.0f,
};
s32 lbl_1_data_118[0xD][8] = {
    {
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 49),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 14),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 2),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 5),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 13),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 14),
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 14 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 14 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 14 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 14 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 14 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 2 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 5 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 13 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 14 */,
    },
};
s32 lbl_1_data_2B8[0x1A] = {
    DATA_MAKE_NUM(DATADIR_MP5_M515, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 38),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 39),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 32),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 33),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 34),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 35),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 36),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 37),
};
s32 lbl_1_data_320[0x11] = {
    DATA_MAKE_NUM(DATADIR_MP5_M515, 40),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 41),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 42),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 43),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 44),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 45),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 46),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 47),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 48),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 49),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 50),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 51),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 52),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 53),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 54),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 55),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 56),
};
s32 lbl_1_data_364[0x11] = { DATA_MAKE_NUM(DATADIR_MP5_M515, 57), DATA_MAKE_NUM(DATADIR_MP5_M515, 58), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s32 lbl_1_data_3A8[8] = {
    DATA_MAKE_NUM(DATADIR_MP5_M515, 59),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 60),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 61),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 62),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 63),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 64),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 65),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 66),
};
s32 lbl_1_data_3C8[0xE] = {
    DATA_MAKE_NUM(DATADIR_MP5_M515, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M515, 31),
};
static u16 lbl_1_data_530[0x19] = { 1, 1, 0, 0, 1, 1, 1, 0, 2, 0, 1, 1, 1, 0, 0, 1, 1, 0, 2, 0, 1, 1, 0, 1, 0 };
static u16 lbl_1_data_562[0x19] = { 1, 1, 0, 0, 0, 1, 1, 0, 2, 0, 1, 1, 1, 0, 2, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0 };
static u16 lbl_1_data_594[0x19] = { 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 2, 2, 0, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_5C6[0x19] = { 0, 0, 0, 1, 1, 2, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 2, 0, 1, 1 };
static u16 lbl_1_data_5F8[0x19] = { 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 2, 1, 1, 1, 1, 0, 0, 1, 1 };
static u16 lbl_1_data_62A[0x19] = { 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 2, 1, 1, 0, 0, 0 };
static u16 lbl_1_data_65C[0x19] = { 1, 1, 0, 0, 1, 1, 1, 0, 2, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 2, 0 };
static u16 lbl_1_data_68E[0x19] = { 0, 0, 0, 1, 1, 2, 2, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1 };
static u16 lbl_1_data_6C0[0x19] = { 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 2, 2, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
static u16 lbl_1_data_6F2[0x19] = { 1, 1, 0, 0, 0, 1, 1, 1, 0, 2, 1, 1, 0, 1, 0, 1, 1, 2, 0, 0, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_724[0x19] = { 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 1, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_756[0x19] = { 0, 2, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_788[0x19] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 2, 1, 1, 2, 1, 0, 1, 1, 0, 0, 0 };
static u16 lbl_1_data_7BA[0x19] = { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0 };
static u16 lbl_1_data_7EC[0x19] = { 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 2, 1, 2, 1, 1, 0, 0, 0, 0 };
static u16 lbl_1_data_81E[0x19] = { 1, 0, 0, 0, 1, 1, 0, 2, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_850[0x19] = { 1, 0, 0, 1, 1, 1, 2, 2, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_882[0x19] = { 1, 0, 2, 0, 0, 1, 1, 0, 2, 2, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_8B4[0x19] = { 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 2, 0, 2, 0, 1, 0, 2, 0, 1 };
static u16 lbl_1_data_8E6[0x19] = { 1, 0, 2, 0, 1, 0, 2, 0, 1, 1, 1, 0, 2, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1 };
static u16 lbl_1_data_918[0x19] = { 0, 2, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 2, 0, 1, 0, 2, 0, 1, 0, 2, 0, 2, 0 };
static u16 lbl_1_data_94A[0x19] = { 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_97C[0x19] = { 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 1, 0, 0, 0, 1, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_9AE[0x19] = { 0, 0, 0, 0, 0, 1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_9E0[0x19] = { 1, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 2, 1, 0, 2, 2, 2, 0, 0, 1, 0, 0, 0 };
static u16 lbl_1_data_A12[0x19] = { 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1, 0, 0, 0, 2, 0, 0 };
static u16 lbl_1_data_A44[0x19] = { 1, 0, 2, 0, 0, 0, 1, 0, 2, 0, 2, 0, 2, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_A76[0x19] = { 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 2, 0, 1, 0, 0, 0, 1 };
static u16 lbl_1_data_AA8[0x19] = { 1, 0, 2, 0, 1, 1, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0 };
static u16 lbl_1_data_ADA[0x19] = { 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 1, 0, 1, 1, 0, 1, 2, 1, 1, 0, 0, 0, 1 };
M515Place lbl_1_data_B0C[5] = {
    { 0x10, 0, 0.0f },
    { 6, 0xC, 0.0f },
    { 1, 0x17, 0.0f },
    { 4, 4, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_B34[4] = { { 0x10, 0, 0.0f }, { 6, 0xC, 180.0f }, { 4, 0x12, 180.0f }, { -1, 0, 0.0f } };
M515Place lbl_1_data_B54[7] = {
    { 0x10, 0, 0.0f },
    { 8, 4, 0.0f },
    { 7, 7, 0.0f },
    { 3, 9, 270.0f },
    { 6, 0x17, 0.0f },
    { 1, 0x18, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_B8C[6] = {
    { 6, 7, 180.0f },
    { 4, 0xB, 0.0f },
    { 7, 0xC, 0.0f },
    { 6, 0x11, 0.0f },
    { 0x10, 0x18, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_BBC[8] = {
    { 8, 0, 0.0f },
    { 4, 1, 0.0f },
    { 3, 0xA, 90.0f },
    { 6, 0xF, 0.0f },
    { 7, 0x11, 0.0f },
    { 1, 0x14, 0.0f },
    { 0x10, 0x18, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_BFC[7] = {
    { 0x10, 0, 0.0f },
    { 8, 3, 0.0f },
    { 2, 4, 0.0f },
    { 6, 8, 0.0f },
    { 7, 0x11, 0.0f },
    { 4, 0x12, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_C34[6] = {
    { 0x10, 0, 0.0f },
    { 2, 4, 0.0f },
    { 7, 0xC, 0.0f },
    { 4, 0xD, 0.0f },
    { 6, 0x11, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_C64[6] = {
    { 4, 0xB, 0.0f },
    { 6, 0xC, 180.0f },
    { 7, 0x11, 0.0f },
    { 1, 0x14, 0.0f },
    { 0x10, 0x18, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_C94[6] = {
    { 8, 0, 0.0f },
    { 2, 1, 0.0f },
    { 6, 0x10, 0.0f },
    { 7, 0x11, 0.0f },
    { 0x10, 0x18, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_CC4[6] = {
    { 0x10, 0, 0.0f },
    { 7, 7, 0.0f },
    { 4, 0xD, 0.0f },
    { 6, 0x17, 0.0f },
    { 1, 0x18, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_CF4[4] = { { 0xB, 6, 0.0f }, { 0xC, 0x10, 0.0f }, { 0xA, 0x13, 0.0f }, { -1, 0, 0.0f } };
M515Place lbl_1_data_D14[6] = {
    { 0xB, 6, 0.0f },
    { 0xC, 8, 270.0f },
    { 0xC, 0x10, 90.0f },
    { 9, 0xC, 0.0f },
    { 0xB, 0x12, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_D44[6] = {
    { 0xA, 0xA, 0.0f },
    { 0xB, 0xB, 270.0f },
    { 0xC, 0xD, 270.0f },
    { 0xC, 0x14, 90.0f },
    { 9, 0x15, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_D74[5] = {
    { 2, 4, 0.0f },
    { 0xA, 0xA, 0.0f },
    { 0xB, 0xC, 270.0f },
    { 9, 0xD, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_D9C[5] = {
    { 0xA, 7, 0.0f },
    { 0xC, 0xC, 270.0f },
    { 9, 0x13, 0.0f },
    { 9, 0x14, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_DC4[9] = {
    { 0xC, 0, 270.0f },
    { 0xB, 4, 270.0f },
    { 0xB, 0xA, 0.0f },
    { 0xC, 0xD, 270.0f },
    { 0xA, 0xE, 0.0f },
    { 0xB, 0x13, 270.0f },
    { 0xE, 0x15, 90.0f },
    { 9, 0x17, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_E0C[9] = {
    { 0xB, 0, 270.0f },
    { 0xC, 3, 0.0f },
    { 0xB, 9, 270.0f },
    { 2, 0xA, 90.0f },
    { 9, 0xF, 0.0f },
    { 0xC, 0x10, 270.0f },
    { 0xF, 0x12, 270.0f },
    { 0xA, 0x14, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_E54[9] = {
    { 9, 0, 0.0f },
    { 9, 5, 0.0f },
    { 0xB, 6, 270.0f },
    { 0xA, 0xA, 0.0f },
    { 0xC, 0x12, 270.0f },
    { 9, 0x13, 0.0f },
    { 0xE, 0x15, 90.0f },
    { 0xA, 0x18, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_E9C[8] = {
    { 0xC, 3, 270.0f },
    { 0xA, 4, 0.0f },
    { 0xE, 6, 90.0f },
    { 0xB, 9, 270.0f },
    { 0xA, 0xA, 0.0f },
    { 9, 0x14, 0.0f },
    { 0xA, 0x18, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_EDC[8] = {
    { 0xA, 0, 0.0f },
    { 0xA, 4, 0.0f },
    { 0xC, 9, 180.0f },
    { 0xB, 0xA, 270.0f },
    { 9, 0xE, 0.0f },
    { 0xF, 0x12, 270.0f },
    { 0xC, 0x15, 180.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_F1C[5] = {
    { 0xD, 5, 90.0f },
    { 4, 9, 0.0f },
    { 4, 0xF, 0.0f },
    { 0x11, 0x13, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_F44[7] = {
    { 0x11, 0, 0.0f },
    { 0xD, 1, 0.0f },
    { 0xD, 3, 0.0f },
    { 0x11, 4, 0.0f },
    { 4, 0x10, 0.0f },
    { 4, 0x12, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_F7C[3] = { { 0xD, 0xA, 90.0f }, { 0x11, 0xE, 0.0f }, { -1, 0, 0.0f } };
M515Place lbl_1_data_F94[3] = { { 0xD, 5, 90.0f }, { 0x11, 9, 0.0f }, { -1, 0, 0.0f } };
M515Place lbl_1_data_FAC[5] = {
    { 0x11, 0, 0.0f },
    { 0x11, 0xE, 0.0f },
    { 0xD, 0x15, 90.0f },
    { 0xD, 3, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_FD4[3] = { { 0xD, 6, 90.0f }, { 4, 0x12, 0.0f }, { -1, 0, 0.0f } };
M515Place lbl_1_data_FEC[5] = {
    { 0xD, 0, 90.0f },
    { 0x11, 6, 0.0f },
    { 4, 0x10, 0.0f },
    { 5, 0x11, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_1014[5] = {
    { 0x11, 0, 0.0f },
    { 0xD, 4, 90.0f },
    { 0xD, 0x14, 90.0f },
    { 0x11, 0x18, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_103C[5] = {
    { 0xD, 4, 0.0f },
    { 3, 5, 90.0f },
    { 4, 0x10, 0.0f },
    { 5, 0x11, 0.0f },
    { -1, 0, 0.0f },
};
M515Place lbl_1_data_1064[6] = {
    { 0xD, 0xC, 0.0f },
    { 0x11, 0xE, 0.0f },
    { 4, 0x11, 0.0f },
    { 5, 0x13, 270.0f },
    { 3, 0x14, 90.0f },
    { -1, 0, 0.0f },
};
u16 *lbl_1_data_1094[0xA] = {
    lbl_1_data_530,
    lbl_1_data_562,
    lbl_1_data_594,
    lbl_1_data_5C6,
    lbl_1_data_5F8,
    lbl_1_data_62A,
    lbl_1_data_65C,
    lbl_1_data_68E,
    lbl_1_data_6C0,
    lbl_1_data_6F2,
};
u16 *lbl_1_data_10BC[0xA] = {
    lbl_1_data_724,
    lbl_1_data_756,
    lbl_1_data_788,
    lbl_1_data_7BA,
    lbl_1_data_7EC,
    lbl_1_data_81E,
    lbl_1_data_850,
    lbl_1_data_882,
    lbl_1_data_8B4,
    lbl_1_data_8E6,
};
u16 *lbl_1_data_10E4[0xA] = {
    lbl_1_data_918,
    lbl_1_data_94A,
    lbl_1_data_97C,
    lbl_1_data_9AE,
    lbl_1_data_9E0,
    lbl_1_data_A12,
    lbl_1_data_A44,
    lbl_1_data_A76,
    lbl_1_data_AA8,
    lbl_1_data_ADA,
};
M515Place *lbl_1_data_110C[0xA] = {
    lbl_1_data_B0C,
    lbl_1_data_B34,
    lbl_1_data_B54,
    lbl_1_data_B8C,
    lbl_1_data_BBC,
    lbl_1_data_BFC,
    lbl_1_data_C34,
    lbl_1_data_C64,
    lbl_1_data_C94,
    lbl_1_data_CC4,
};
M515Place *lbl_1_data_1134[0xA] = {
    lbl_1_data_CF4,
    lbl_1_data_D14,
    lbl_1_data_D44,
    lbl_1_data_D74,
    lbl_1_data_D9C,
    lbl_1_data_DC4,
    lbl_1_data_E0C,
    lbl_1_data_E54,
    lbl_1_data_E9C,
    lbl_1_data_EDC,
};
M515Place *lbl_1_data_115C[0xA] = {
    lbl_1_data_F1C,
    lbl_1_data_F44,
    lbl_1_data_F7C,
    lbl_1_data_F94,
    lbl_1_data_FAC,
    lbl_1_data_FD4,
    lbl_1_data_FEC,
    lbl_1_data_1014,
    lbl_1_data_103C,
    lbl_1_data_1064,
};
u16 lbl_1_data_1184[0xB] = { 1, 1, 2, 0x10, 2, 1, 0x10, 1, 4, 1, 1 };
u16 lbl_1_data_119A[0xE] = { 1, 1, 2, 0x10, 2, 1, 2, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_11B6[0x14] = { 8, 2, 2, 8, 0x10, 8, 0x10, 8, 4, 4, 4, 8, 4, 8, 2, 0x10, 2, 0x10, 2, 8 };
u16 lbl_1_data_11DE[0x10] = { 8, 4, 8, 0x10, 8, 0x10, 8, 4, 8, 8, 2, 0x10, 2, 0x10, 2, 8 };
u16 lbl_1_data_11FE[0x12] = { 1, 4, 0x10, 4, 1, 2, 0x10, 2, 1, 4, 0x10, 4, 1, 2, 0x10, 2, 1, 1 };
u16 lbl_1_data_1222[0xE] = { 1, 0x10, 1, 4, 1, 0x10, 2, 2, 1, 0x10, 1, 4, 0x10, 0x20 };
u16 lbl_1_data_123E[0xD] = { 1, 2, 2, 1, 0x10, 1, 4, 1, 0x10, 1, 4, 1, 1 };
u16 lbl_1_data_1258[0xD] = { 8, 2, 2, 8, 8, 8, 8, 4, 0x10, 4, 0x10, 4, 8 };
u16 lbl_1_data_1272[0x13] = { 1, 1, 0x10, 8, 4, 4, 1, 0x10, 1, 2, 0x10, 2, 1, 2, 0x10, 2, 1, 1, 1 };
u16 lbl_1_data_1298[0xE] = { 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_12B4[0x17] = {
    8,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    1,
    1,
    2,
    2,
    2,
    2,
    8,
    8,
    8,
    8,
    4,
    0x10,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_12E2[6] = { 1, 1, 0x10, 1, 0x10, 0x20 };
u16 lbl_1_data_12EE[0xB] = { 1, 0x10, 1, 2, 0x10, 2, 1, 1, 1, 4, 1 };
u16 lbl_1_data_1304[0xC] = { 8, 4, 4, 8, 0x10, 8, 0x10, 8, 2, 2, 8, 8 };
u16 lbl_1_data_131C[0x11] = { 1, 0x10, 1, 4, 0x10, 4, 1, 0x10, 2, 0x10, 2, 1, 0x10, 1, 2, 0x10, 0x20 };
u16 lbl_1_data_133E[0xB] = { 1, 0x10, 1, 2, 0x10, 2, 1, 1, 1, 4, 1 };
u16 lbl_1_data_1354[0xD] = { 8, 0x10, 8, 0x10, 8, 0x10, 8, 2, 8, 4, 0x10, 4, 8 };
u16 lbl_1_data_136E[0x17] = {
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_139C[0xD] = { 1, 4, 0x10, 4, 1, 4, 1, 0x10, 1, 2, 1, 2, 1 };
u16 lbl_1_data_13B6[0xC] = { 8, 4, 0x10, 4, 8, 4, 8, 8, 2, 2, 8, 8 };
u16 lbl_1_data_13CE[0x21] = {
    1,
    4,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_1410[0xF] = { 1, 4, 0x10, 4, 1, 4, 2, 4, 1, 0x10, 1, 2, 1, 2, 1 };
u16 lbl_1_data_142E[0xA] = { 8, 2, 8, 0x10, 8, 0x10, 8, 4, 8, 8 };
u16 lbl_1_data_1442[0x18] = {
    1,
    2,
    1,
    0x10,
    1,
    8,
    4,
    4,
    4,
    1,
    0x10,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    2,
    1,
    0x20,
};
u16 lbl_1_data_1472[0xB] = { 1, 4, 1, 0x10, 1, 0x10, 1, 2, 1, 1, 1 };
u16 lbl_1_data_1488[0xC] = { 8, 2, 8, 0x10, 8, 2, 8, 8, 8, 4, 4, 8 };
u16 lbl_1_data_14A0[0x11] = { 1, 0x10, 1, 4, 0x10, 4, 1, 0x10, 1, 0x10, 1, 2, 0x10, 2, 1, 1, 1 };
u16 lbl_1_data_14C2[0xD] = { 1, 4, 1, 0x10, 1, 0x10, 1, 2, 4, 2, 1, 1, 1 };
u16 lbl_1_data_14DC[0x10] = { 8, 4, 8, 0x10, 8, 0x10, 8, 4, 8, 8, 2, 0x10, 2, 0x10, 2, 8 };
u16 lbl_1_data_14FC[0x1E] = {
    1,
    0x10,
    2,
    2,
    1,
    4,
    8,
    4,
    4,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    1,
    0x10,
    0x20,
};
u16 lbl_1_data_1538[0xD] = { 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 4, 1, 1, 1 };
u16 lbl_1_data_1552[0xB] = { 8, 8, 8, 0x10, 8, 2, 8, 4, 0x10, 4, 8 };
u16 lbl_1_data_1568[0x15] = {
    0x10,
    1,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_1592[0x10] = { 1, 2, 2, 8, 2, 1, 0x10, 1, 0x10, 1, 2, 4, 4, 1, 1, 1 };
u16 lbl_1_data_15B2[0xC] = { 8, 8, 8, 0x10, 8, 4, 8, 0x10, 2, 0x10, 2, 8 };
u16 lbl_1_data_15CA[0xF] = { 0x10, 1, 2, 2, 1, 0x10, 1, 4, 1, 0x10, 1, 4, 1, 0x10, 0x20 };
u16 lbl_1_data_15E8[0xE] = { 1, 2, 0x10, 2, 1, 2, 1, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_1604[0xC] = { 8, 8, 8, 2, 8, 0x10, 8, 4, 0x10, 4, 8, 8 };
u16 lbl_1_data_161C[0x13] = { 1, 4, 4, 1, 0x10, 1, 2, 0x10, 2, 1, 2, 0x10, 2, 1, 4, 0x10, 4, 1, 1 };
u16 lbl_1_data_1642[0xF] = { 1, 2, 0x10, 2, 1, 2, 1, 1, 0x10, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_1660[0xC] = { 8, 8, 8, 2, 8, 0x10, 4, 8, 0x10, 8, 0x10, 0x20 };
u16 lbl_1_data_1678[0x14] = {
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    4,
    0x10,
    4,
    1,
    2,
    8,
    2,
    0x20,
};
u16 lbl_1_data_16A0[0xD] = { 1, 4, 1, 4, 1, 0x10, 1, 2, 0x10, 2, 1, 2, 1 };
u16 lbl_1_data_16BA[0x10] = { 8, 8, 8, 4, 4, 8, 0x10, 8, 2, 0x10, 2, 8, 2, 0x10, 2, 8 };
u16 lbl_1_data_16DA[0x1C] = {
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_1712[0xF] = { 1, 4, 1, 4, 1, 0x10, 1, 2, 0x10, 8, 1, 2, 1, 2, 1 };
u16 lbl_1_data_1730[0xA] = { 8, 8, 8, 4, 8, 0x10, 8, 2, 1, 0x20 };
u16 lbl_1_data_1744[0x1D] = {
    1,
    4,
    2,
    2,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    4,
    8,
    4,
    0x20,
};
u16 lbl_1_data_177E[0xD] = { 1, 4, 4, 1, 0x10, 1, 2, 0x10, 2, 1, 2, 1, 1 };
u16 lbl_1_data_1798[0xE] = { 0x10, 8, 0x10, 8, 4, 0x10, 4, 8, 2, 0x10, 2, 8, 8, 8 };
u16 lbl_1_data_17B4[0x15] = { 1, 4, 4, 1, 1, 2, 0x10, 2, 0x10, 2, 1, 2, 0x10, 2, 1, 4, 0x10, 4, 1, 1, 1 };
u16 lbl_1_data_17DE[0xF] = { 1, 4, 1, 4, 1, 0x10, 1, 2, 0x10, 2, 0x10, 1, 2, 1, 1 };
u16 lbl_1_data_17FC[0x15] = {
    0x10,
    8,
    4,
    8,
    0x10,
    8,
    2,
    0x10,
    1,
    2,
    2,
    8,
    0x10,
    8,
    4,
    0x10,
    4,
    8,
    8,
    8,
    8,
};
u16 lbl_1_data_1826[0x10] = { 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 1, 0x10, 1, 4, 0x10, 1, 0x20 };
u16 lbl_1_data_1846[0xC] = { 1, 0x10, 1, 2, 2, 1, 0x10, 1, 4, 1, 4, 1 };
u16 lbl_1_data_185E[0x10] = { 8, 8, 2, 8, 4, 0x10, 4, 8, 2, 0x10, 2, 8, 4, 0x10, 4, 8 };
u16 lbl_1_data_187E[0x10] = { 1, 4, 1, 0x10, 1, 4, 1, 1, 2, 0x10, 2, 0x10, 2, 1, 1, 1 };
u16 lbl_1_data_189E[0xF] = { 1, 0x10, 1, 2, 2, 1, 4, 2, 1, 0x10, 1, 4, 1, 4, 1 };
u16 lbl_1_data_18BC[0xB] = { 8, 8, 2, 8, 0x10, 8, 4, 1, 0x10, 1, 0x20 };
u16 lbl_1_data_18D2[0x10] = { 1, 2, 1, 0x10, 1, 0x10, 1, 0x10, 1, 4, 0x10, 4, 0x10, 1, 1, 1 };
u16 lbl_1_data_18F2[0xE] = { 1, 1, 2, 0x10, 2, 1, 2, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_190E[0xF] = { 8, 4, 8, 0x10, 8, 0x10, 8, 2, 2, 2, 8, 8, 4, 4, 8 };
u16 lbl_1_data_192C[0x17] = {
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    8,
    1,
    1,
    2,
    0x10,
    1,
    1,
};
u16 lbl_1_data_195A[0x12] = { 1, 1, 2, 0x10, 2, 1, 2, 8, 0x10, 1, 4, 0x10, 4, 1, 4, 8, 0x10, 1 };
u16 lbl_1_data_197E[0x21] = {
    8,
    4,
    8,
    2,
    2,
    2,
    8,
    0x10,
    8,
    0x10,
    8,
    0x10,
    8,
    1,
    1,
    1,
    4,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    8,
    4,
    8,
    8,
    2,
    0x10,
    2,
    0x10,
    2,
    8,
};
u16 lbl_1_data_19C0[0x13] = { 1, 0x10, 1, 2, 1, 0x10, 4, 4, 1, 0x10, 1, 2, 0x10, 2, 1, 0x10, 1, 8, 0x20 };
u16 lbl_1_data_19E6[0x10] = { 1, 2, 2, 1, 0x10, 1, 4, 1, 0x10, 1, 2, 4, 1, 2, 0x10, 1 };
u16 lbl_1_data_1A06[0x17] = {
    8,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    1,
    1,
    2,
    2,
    2,
    2,
    8,
    8,
    8,
    8,
    4,
    0x10,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_1A34[0x14] = { 1, 1, 0x10, 8, 2, 2, 1, 0x10, 1, 4, 0x10, 4, 1, 4, 0x10, 4, 0x10, 1, 1, 1 };
u16 lbl_1_data_1A5C[0x17] = {
    1,
    1,
    8,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    8,
    4,
    1,
    0x10,
    2,
    1,
    4,
    4,
    1,
    8,
    1,
    1,
};
u16 lbl_1_data_1A8A[0x1D] = {
    8,
    2,
    4,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    8,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    8,
    8,
    8,
    8,
    4,
    0x10,
    4,
    0x10,
    2,
    4,
    4,
    8,
};
u16 lbl_1_data_1AC4[0x15] = {
    1,
    1,
    0x10,
    8,
    4,
    4,
    1,
    0x10,
    1,
    2,
    8,
    8,
    2,
    2,
    1,
    1,
    4,
    0x10,
    1,
    0x10,
    0x20,
};
u16 lbl_1_data_1AEE[0xF] = { 1, 0x10, 1, 2, 0x10, 2, 1, 1, 1, 8, 8, 1, 1, 4, 1 };
u16 lbl_1_data_1B0C[0xF] = { 8, 0x10, 8, 1, 4, 4, 8, 0x10, 8, 0x10, 8, 2, 2, 8, 8 };
u16 lbl_1_data_1B2A[0x1D] = {
    1,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    4,
    4,
    1,
    2,
    0x10,
    2,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_1B64[0x16] = {
    1,
    0x10,
    1,
    2,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    1,
    1,
    8,
    8,
    8,
    2,
    0x10,
    1,
    1,
    1,
    4,
    1,
};
u16 lbl_1_data_1B90[0x16] = {
    8,
    0x10,
    4,
    4,
    8,
    0x10,
    8,
    1,
    1,
    2,
    2,
    8,
    0x10,
    8,
    0x10,
    8,
    2,
    8,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_1BBC[0x1A] = {
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    4,
    2,
    8,
    2,
    0x20,
};
u16 lbl_1_data_1BF0[0x11] = { 1, 4, 0x10, 4, 1, 4, 1, 0x10, 1, 2, 4, 8, 1, 2, 1, 2, 1 };
u16 lbl_1_data_1C12[0xF] = { 8, 2, 8, 0x10, 1, 4, 0x10, 2, 8, 8, 0x10, 8, 4, 8, 8 };
u16 lbl_1_data_1C30[0x25] = {
    1,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    8,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    2,
    0x10,
    1,
    1,
};
u16 lbl_1_data_1C7A[0x1B] = {
    1,
    4,
    0x10,
    4,
    1,
    4,
    2,
    8,
    2,
    4,
    1,
    4,
    1,
    0x10,
    1,
    2,
    4,
    8,
    8,
    2,
    4,
    1,
    1,
    2,
    1,
    2,
    1,
};
u16 lbl_1_data_1CB0[0x20] = {
    8,
    2,
    2,
    8,
    4,
    8,
    0x10,
    8,
    1,
    1,
    4,
    0x10,
    4,
    0x10,
    8,
    4,
    2,
    1,
    2,
    2,
    8,
    8,
    0x10,
    8,
    2,
    8,
    4,
    0x10,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_1CF0[0x1F] = {
    1,
    4,
    4,
    1,
    0x10,
    2,
    1,
    0x10,
    2,
    2,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    2,
    2,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    8,
    8,
    1,
    1,
    0x20,
};
u16 lbl_1_data_1D2E[0x11] = { 1, 4, 1, 0x10, 1, 0x10, 1, 2, 4, 8, 8, 1, 1, 2, 1, 1, 1 };
u16 lbl_1_data_1D50[0x13] = { 8, 2, 4, 4, 8, 0x10, 8, 0x10, 8, 4, 8, 8, 2, 0x10, 2, 0x10, 2, 0x10, 8 };
u16 lbl_1_data_1D76[0x17] = {
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    1,
    1,
    1,
};
u16 lbl_1_data_1DA4[0x19] = {
    1,
    4,
    2,
    4,
    1,
    0x10,
    1,
    8,
    1,
    0x10,
    1,
    2,
    1,
    8,
    4,
    8,
    8,
    1,
    1,
    2,
    1,
    4,
    0x10,
    1,
    1,
};
u16 lbl_1_data_1DD6[0x28] = {
    8,
    4,
    4,
    2,
    2,
    2,
    8,
    0x10,
    8,
    0x10,
    8,
    0x10,
    1,
    1,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    8,
    4,
    8,
    8,
    1,
    1,
    2,
    1,
    1,
    2,
    2,
    8,
    8,
    8,
    2,
    8,
    4,
    0x10,
    4,
    0x20,
};
u16 lbl_1_data_1E26[0x1B] = {
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x20,
};
u16 lbl_1_data_1E5C[0x11] = { 1, 2, 2, 4, 4, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 4, 1, 1, 1 };
u16 lbl_1_data_1E7E[0xD] = { 8, 8, 8, 0x10, 8, 2, 8, 1, 8, 4, 0x10, 4, 8 };
u16 lbl_1_data_1E98[0x1B] = {
    0x10,
    1,
    4,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    2,
    0x10,
    2,
    8,
    0x10,
    1,
    2,
    0x10,
    2,
    4,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_1ECE[0x18] = {
    1,
    2,
    2,
    1,
    4,
    4,
    2,
    2,
    1,
    0x10,
    1,
    8,
    1,
    0x10,
    1,
    4,
    2,
    8,
    1,
    4,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_1EFE[0x1B] = {
    8,
    8,
    8,
    1,
    1,
    8,
    8,
    0x10,
    8,
    4,
    8,
    1,
    2,
    1,
    1,
    1,
    8,
    8,
    8,
    2,
    4,
    4,
    8,
    2,
    0x10,
    2,
    8,
};
u16 lbl_1_data_1F34[0x23] = {
    0x10,
    1,
    4,
    1,
    0x10,
    2,
    2,
    2,
    1,
    0x10,
    1,
    4,
    2,
    1,
    0x10,
    4,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    4,
    8,
    8,
    1,
    1,
    4,
    0x10,
    4,
    2,
    4,
    1,
    1,
};
u16 lbl_1_data_1F7A[0x10] = { 1, 2, 0x10, 2, 1, 8, 1, 2, 1, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_1F9A[0x14] = { 8, 8, 8, 4, 8, 1, 2, 2, 8, 0x10, 8, 1, 4, 4, 8, 2, 0x10, 2, 8, 8 };
u16 lbl_1_data_1FC2[0x19] = {
    1,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    1,
    0x10,
    4,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_1FF4[0x17] = {
    1,
    2,
    0x10,
    2,
    4,
    2,
    1,
    2,
    1,
    1,
    8,
    8,
    0x10,
    4,
    2,
    1,
    1,
    4,
    0x10,
    4,
    1,
    4,
    1,
};
u16 lbl_1_data_2022[0x1E] = {
    8,
    8,
    8,
    2,
    4,
    4,
    2,
    1,
    1,
    8,
    8,
    2,
    8,
    0x10,
    8,
    1,
    4,
    4,
    2,
    8,
    0x10,
    4,
    8,
    2,
    4,
    1,
    2,
    8,
    1,
    0x20,
};
u16 lbl_1_data_205E[0x10] = { 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 0x10, 1, 0x10, 4, 1, 2, 0x20 };
u16 lbl_1_data_207E[0x11] = { 1, 4, 1, 8, 1, 4, 1, 0x10, 1, 8, 1, 2, 0x10, 2, 1, 2, 1 };
u16 lbl_1_data_20A0[0x16] = { 8, 8, 8, 4, 4, 2, 2, 4, 4, 8, 0x10, 2, 2, 8, 4, 0x10, 4, 8, 2, 0x10, 2, 8 };
u16 lbl_1_data_20CC[0x24] = {
    1,
    4,
    2,
    2,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    4,
    2,
    1,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_2114[0x18] = {
    1,
    8,
    4,
    2,
    4,
    1,
    4,
    1,
    0x10,
    1,
    8,
    8,
    2,
    4,
    1,
    1,
    2,
    0x10,
    8,
    1,
    2,
    1,
    2,
    1,
};
u16 lbl_1_data_2144[0x18] = {
    8,
    8,
    8,
    4,
    4,
    2,
    2,
    1,
    8,
    8,
    1,
    4,
    4,
    2,
    2,
    4,
    4,
    8,
    0x10,
    2,
    8,
    0x10,
    8,
    0x20,
};
u16 lbl_1_data_2174[0x14] = { 1, 2, 1, 4, 1, 0x10, 1, 4, 0x10, 4, 1, 0x10, 1, 0x10, 1, 2, 2, 4, 4, 0x20 };
u16 lbl_1_data_219C[0x11] = { 1, 4, 4, 1, 8, 1, 0x10, 8, 1, 1, 2, 0x10, 2, 1, 2, 1, 1 };
u16 lbl_1_data_21BE[0x16] = {
    0x10,
    8,
    4,
    2,
    2,
    4,
    4,
    8,
    0x10,
    2,
    2,
    8,
    0x10,
    8,
    2,
    4,
    0x10,
    4,
    8,
    8,
    8,
    8,
};
u16 lbl_1_data_21EA[0x1A] = {
    1,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    4,
    0x10,
    1,
    2,
    4,
    2,
    8,
    2,
    1,
    0x10,
    1,
    4,
    2,
    8,
    4,
    1,
    0x20,
};
u16 lbl_1_data_221E[0x1A] = {
    1,
    4,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    8,
    2,
    0x10,
    2,
    1,
    1,
    4,
    0x10,
    8,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_2252[0x19] = {
    1,
    4,
    4,
    2,
    2,
    4,
    4,
    1,
    0x10,
    8,
    1,
    1,
    8,
    1,
    2,
    0x10,
    2,
    4,
    1,
    0x10,
    2,
    1,
    2,
    1,
    1,
};
u16 lbl_1_data_2284[0xF] = { 0x10, 8, 0x10, 8, 0x10, 2, 0x10, 2, 8, 4, 4, 2, 8, 0x10, 0x20 };
u16 lbl_1_data_22A2[0x15] = { 1, 0x10, 1, 8, 1, 2, 2, 1, 8, 4, 4, 1, 2, 2, 1, 0x10, 1, 4, 1, 4, 1 };
u16 lbl_1_data_22CC[0x19] = {
    8,
    8,
    2,
    8,
    1,
    4,
    2,
    8,
    4,
    0x10,
    4,
    8,
    1,
    2,
    8,
    4,
    8,
    2,
    0x10,
    2,
    8,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_22FE[0x1C] = {
    1,
    4,
    1,
    8,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    8,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_2336[0x20] = {
    1,
    8,
    4,
    1,
    2,
    1,
    0x10,
    1,
    2,
    2,
    4,
    2,
    4,
    4,
    2,
    2,
    1,
    0x10,
    8,
    4,
    4,
    1,
    0x10,
    2,
    2,
    1,
    1,
    0x10,
    4,
    1,
    4,
    1,
};
u16 lbl_1_data_2376[0x12] = { 8, 8, 2, 8, 1, 4, 2, 8, 0x10, 4, 0x10, 4, 8, 2, 2, 4, 4, 0x20 };
u16 lbl_1_data_239A[0x1F] = {
    1,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    8,
    8,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    4,
    8,
    8,
    2,
    8,
    8,
    2,
    2,
    1,
    1,
    0x20,
};
u16 lbl_1_data_23D8[0xE] = { 1, 1, 2, 0x10, 2, 1, 0x10, 1, 4, 2, 1, 4, 1, 1 };
u16 lbl_1_data_23F4[0x10] = { 8, 4, 8, 0x10, 8, 0x10, 8, 2, 2, 1, 2, 8, 8, 4, 4, 8 };
u16 lbl_1_data_2414[0x15] = { 1, 4, 0x10, 4, 1, 2, 0x10, 2, 1, 2, 0x10, 2, 1, 4, 0x10, 4, 1, 2, 4, 1, 1 };
u16 lbl_1_data_243E[0x15] = { 1, 1, 0x10, 2, 0x10, 2, 1, 2, 1, 4, 8, 4, 1, 2, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_2468[0x11] = { 8, 4, 8, 0x10, 8, 0x10, 8, 4, 8, 2, 8, 2, 0x10, 2, 0x10, 2, 8 };
u16 lbl_1_data_248A[0xF] = { 1, 0x10, 4, 1, 4, 1, 0x10, 2, 2, 1, 0x10, 1, 4, 0x10, 0x20 };
u16 lbl_1_data_24A8[0xE] = { 1, 2, 2, 1, 0x10, 1, 4, 0x10, 1, 0x10, 1, 4, 1, 1 };
u16 lbl_1_data_24C4[0x10] = { 4, 8, 4, 2, 2, 2, 8, 8, 8, 8, 4, 0x10, 4, 0x10, 4, 8 };
u16 lbl_1_data_24E4[0x15] = { 1, 1, 0x10, 8, 2, 2, 1, 0x10, 1, 2, 4, 0x10, 4, 1, 2, 4, 0x10, 4, 1, 1, 1 };
u16 lbl_1_data_250E[0x11] = { 1, 1, 8, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 0x10, 4, 1, 2, 4, 1 };
u16 lbl_1_data_2530[0x1B] = {
    8,
    4,
    4,
    8,
    0x10,
    8,
    0x10,
    1,
    1,
    2,
    2,
    2,
    2,
    8,
    8,
    8,
    8,
    4,
    8,
    4,
    8,
    4,
    0x10,
    4,
    0x10,
    4,
    8,
};
u16 lbl_1_data_2566[0x1F] = {
    1,
    1,
    0x10,
    1,
    4,
    8,
    8,
    2,
    2,
    1,
    0x10,
    8,
    4,
    4,
    4,
    1,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_25A4[0xC] = { 1, 0x10, 1, 0x10, 2, 0x10, 2, 1, 1, 1, 4, 1 };
u16 lbl_1_data_25BC[0x11] = { 2, 8, 4, 4, 1, 4, 8, 0x10, 8, 4, 8, 0x10, 8, 2, 2, 8, 8 };
u16 lbl_1_data_25DE[0x1D] = {
    1,
    4,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    1,
    2,
    1,
    0x10,
    1,
    4,
    8,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_2618[0xE] = { 2, 1, 0x10, 1, 2, 0x10, 2, 1, 4, 1, 4, 1, 4, 1 };
u16 lbl_1_data_2634[0x11] = { 8, 0x10, 8, 2, 8, 0x10, 8, 4, 8, 0x10, 8, 4, 8, 2, 0x10, 2, 8 };
u16 lbl_1_data_2656[0x1D] = {
    1,
    4,
    1,
    0x10,
    1,
    8,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    4,
    2,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    0x10,
    1,
    1,
};
u16 lbl_1_data_2690[0x11] = { 1, 8, 1, 4, 0x10, 4, 1, 4, 1, 2, 1, 0x10, 1, 2, 1, 2, 1 };
u16 lbl_1_data_26B2[0xE] = { 8, 4, 0x10, 4, 8, 4, 8, 8, 2, 2, 2, 4, 8, 8 };
u16 lbl_1_data_26CE[0x26] = {
    4,
    1,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    8,
    8,
    4,
    1,
    4,
    1,
    0x10,
    1,
    4,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_271A[0x10] = { 1, 8, 4, 0x10, 4, 0x10, 1, 4, 1, 0x10, 1, 2, 1, 4, 2, 1 };
u16 lbl_1_data_273A[0x12] = { 8, 4, 0x10, 2, 8, 0x10, 8, 0x10, 2, 8, 2, 8, 4, 0x10, 4, 0x10, 4, 8 };
u16 lbl_1_data_275E[0x1F] = {
    1,
    4,
    4,
    1,
    0x10,
    2,
    2,
    2,
    2,
    1,
    0x10,
    4,
    1,
    0x10,
    4,
    1,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    8,
    2,
    0x10,
    0x20,
};
u16 lbl_1_data_279C[0xE] = { 1, 2, 4, 1, 0x10, 1, 2, 1, 0x10, 1, 2, 1, 1, 1 };
u16 lbl_1_data_27B8[0xE] = { 8, 2, 4, 2, 8, 0x10, 8, 2, 8, 8, 8, 4, 4, 8 };
u16 lbl_1_data_27D4[0x14] = {
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    1,
    1,
    1,
};
u16 lbl_1_data_27FC[0x13] = { 1, 4, 1, 4, 0x10, 1, 0x10, 1, 2, 1, 0x10, 1, 0x10, 2, 4, 2, 1, 1, 1 };
u16 lbl_1_data_2822[0x19] = {
    8,
    4,
    8,
    0x10,
    8,
    0x10,
    8,
    0x10,
    4,
    8,
    8,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    2,
    8,
    2,
    0x10,
    2,
    0x10,
    8,
};
u16 lbl_1_data_2854[0x21] = {
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    4,
    0x10,
    8,
    1,
    4,
    1,
    2,
    0x10,
    0x20,
};
u16 lbl_1_data_2896[0x11] = { 1, 2, 8, 2, 1, 0x10, 1, 0x10, 1, 2, 0x10, 4, 4, 1, 1, 2, 1 };
u16 lbl_1_data_28B8[0xD] = { 8, 8, 8, 0x10, 8, 4, 8, 1, 8, 2, 0x10, 2, 8 };
u16 lbl_1_data_28D2[0x18] = {
    0x10,
    1,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_2902[0x13] = { 1, 4, 1, 2, 2, 8, 1, 0x10, 1, 0x10, 1, 0x10, 4, 2, 4, 4, 1, 1, 1 };
u16 lbl_1_data_2928[0x11] = { 8, 8, 4, 8, 4, 8, 0x10, 8, 0x10, 2, 8, 4, 0x10, 4, 1, 8, 8 };
u16 lbl_1_data_294A[0x1F] = {
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    0x10,
    8,
    8,
    2,
    1,
    8,
    2,
    2,
    2,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    4,
    1,
    2,
    8,
    0x20,
};
u16 lbl_1_data_2988[0x14] = { 1, 2, 0x10, 2, 8, 1, 2, 1, 1, 2, 8, 8, 1, 1, 4, 0x10, 4, 1, 4, 1 };
u16 lbl_1_data_29B0[0x10] = { 8, 8, 8, 2, 4, 2, 8, 0x10, 8, 4, 0x10, 4, 1, 8, 8, 8 };
u16 lbl_1_data_29D0[0x18] = {
    1,
    4,
    2,
    4,
    4,
    1,
    0x10,
    1,
    4,
    2,
    0x10,
    2,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_2A00[0x17] = { 1, 8, 2, 0x10, 2, 1, 2, 4, 2, 1, 1, 4, 8, 1, 4, 0x10, 1, 4, 1, 4, 2, 4, 1 };
u16 lbl_1_data_2A2E[0x11] = { 8, 8, 8, 0x10, 2, 4, 2, 8, 0x10, 8, 4, 4, 2, 2, 1, 4, 0x20 };
u16 lbl_1_data_2A50[0x29] = {
    1,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    8,
    2,
    2,
    8,
    8,
    4,
    4,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    2,
    4,
    1,
    2,
    0x20,
};
u16 lbl_1_data_2AA2[0x10] = { 1, 2, 4, 1, 4, 1, 8, 1, 0x10, 1, 2, 0x10, 2, 1, 2, 1 };
u16 lbl_1_data_2AC2[0x15] = { 8, 8, 8, 4, 2, 8, 4, 1, 4, 4, 8, 0x10, 8, 2, 0x10, 2, 8, 2, 0x10, 2, 8 };
u16 lbl_1_data_2AEC[0x26] = {
    1,
    2,
    1,
    4,
    2,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    2,
    1,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_2B38[0x15] = { 1, 4, 1, 2, 8, 1, 4, 1, 8, 2, 4, 1, 0x10, 4, 1, 2, 0x10, 2, 1, 2, 1 };
u16 lbl_1_data_2B62[0xC] = { 8, 8, 8, 4, 8, 0x10, 4, 8, 0x10, 8, 2, 0x20 };
u16 lbl_1_data_2B7A[0x19] = {
    1,
    0x10,
    1,
    4,
    0x10,
    1,
    0x10,
    4,
    1,
    2,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    8,
    4,
    0x20,
};
u16 lbl_1_data_2BAC[0x14] = { 4, 1, 4, 4, 1, 0x10, 1, 2, 8, 1, 2, 0x10, 2, 1, 2, 1, 4, 8, 1, 1 };
u16 lbl_1_data_2BD4[0x12] = { 0x10, 8, 0x10, 4, 2, 8, 2, 0x10, 4, 0x10, 4, 8, 2, 0x10, 2, 8, 8, 8 };
u16 lbl_1_data_2BF8[0x18] = {
    1,
    2,
    4,
    4,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    0x10,
    8,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_2C28[0x13] = { 1, 4, 4, 1, 0x10, 1, 8, 8, 2, 4, 1, 1, 2, 0x10, 2, 1, 2, 1, 1 };
u16 lbl_1_data_2C4E[0x12] = { 0x10, 8, 0x10, 2, 4, 4, 8, 0x10, 8, 2, 0x10, 1, 2, 8, 8, 4, 0x10, 0x20 };
u16 lbl_1_data_2C72[0x1F] = {
    1,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    4,
    0x10,
    4,
    2,
    1,
    4,
    8,
    4,
    1,
    0x10,
    2,
    2,
    2,
    1,
    4,
    4,
    1,
    2,
    0x10,
    1,
    0x10,
    0x20,
};
u16 lbl_1_data_2CB0[0x12] = { 1, 4, 2, 1, 0x10, 1, 2, 2, 8, 1, 0x10, 1, 4, 1, 4, 2, 4, 1 };
u16 lbl_1_data_2CD4[0x15] = { 8, 8, 2, 8, 4, 0x10, 4, 8, 1, 8, 2, 0x10, 8, 2, 1, 8, 8, 4, 0x10, 4, 8 };
u16 lbl_1_data_2CFE[0x16] = {
    1,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    2,
    8,
    0x10,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_2D2A[0x16] = { 1, 2, 4, 1, 0x10, 1, 0x10, 2, 4, 2, 2, 8, 4, 2, 1, 0x10, 1, 4, 1, 4, 8, 1 };
u16 lbl_1_data_2D56[0x12] = { 8, 8, 2, 8, 4, 0x10, 4, 1, 8, 2, 8, 0x10, 8, 0x10, 4, 8, 0x10, 0x20 };
u16 lbl_1_data_2D7A[0x20] = {
    1,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    8,
    8,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    8,
    8,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    0x20,
};
u16 lbl_1_data_2DBA[0x15] = {
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_2DE4[0x17] = {
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    4,
    1,
    1,
};
u16 lbl_1_data_2E12[0x1D] = {
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    2,
    2,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    2,
    0x10,
    1,
    1,
};
u16 lbl_1_data_2E4C[0x10] = { 1, 4, 0x10, 4, 1, 2, 0x10, 1, 0x10, 1, 2, 0x10, 2, 1, 8, 0x20 };
u16 lbl_1_data_2E6C[8] = { 1, 0x10, 1, 4, 2, 2, 4, 0x20 };
u16 lbl_1_data_2E7C[0xD] = { 1, 2, 0x10, 2, 1, 4, 0x10, 4, 1, 0x10, 1, 4, 0x20 };
u16 lbl_1_data_2E96[0x17] = {
    1,
    1,
    0x10,
    1,
    2,
    0x10,
    8,
    8,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_2EC4[0x19] = {
    1,
    1,
    8,
    4,
    4,
    1,
    0x10,
    1,
    8,
    8,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_2EF6[0x1A] = {
    1,
    1,
    0x10,
    8,
    2,
    2,
    1,
    0x10,
    8,
    4,
    4,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_2F2A[0x11] = { 1, 1, 0x10, 1, 8, 8, 2, 2, 1, 0x10, 8, 4, 4, 1, 1, 0x10, 0x20 };
u16 lbl_1_data_2F4C[0x1F] = {
    1,
    4,
    4,
    1,
    0x10,
    8,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    8,
    8,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_2F8A[0x15] = {
    1,
    4,
    4,
    1,
    8,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    2,
    8,
    0x10,
    8,
    0x10,
    8,
    1,
    0x20,
};
u16 lbl_1_data_2FB4[0x1E] = {
    1,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    8,
    4,
    4,
    1,
    0x10,
    2,
    2,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_2FF0[0x1A] = {
    1,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3024[0x1C] = {
    1,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    8,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    2,
    1,
    4,
    0x10,
    4,
    0x10,
    4,
    0x10,
    1,
    1,
};
u16 lbl_1_data_305C[0x12] = { 1, 0x10, 1, 2, 0x10, 2, 1, 0x10, 1, 2, 1, 4, 0x10, 4, 0x10, 4, 1, 1 };
u16 lbl_1_data_3080[0x13] = { 1, 2, 1, 0x10, 1, 2, 1, 4, 8, 4, 1, 0x10, 1, 8, 4, 1, 0x10, 1, 0x20 };
u16 lbl_1_data_30A6[0x1A] = {
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    8,
    2,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_30DA[0x1D] = {
    1,
    2,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    4,
    0x10,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_3114[0x22] = {
    1,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    4,
    0x10,
    1,
    1,
};
u16 lbl_1_data_3158[0x17] = {
    1,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    8,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    4,
    0x10,
    2,
    0x10,
    0x20,
};
u16 lbl_1_data_3186[0x22] = {
    1,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    8,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_31CA[0x1A] = {
    1,
    4,
    4,
    1,
    0x10,
    2,
    2,
    4,
    1,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    1,
    0x10,
    2,
    1,
    0x10,
    1,
    0x20,
};
u16 lbl_1_data_31FE[0x25] = {
    1,
    2,
    2,
    1,
    0x10,
    4,
    2,
    1,
    4,
    0x10,
    8,
    4,
    4,
    4,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    1,
    0x10,
    8,
    2,
    0x10,
    1,
    4,
    1,
    0x20,
};
u16 lbl_1_data_3248[0x1A] = {
    1,
    0x10,
    1,
    8,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    4,
    1,
    2,
    0x10,
    8,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_327C[0x17] = {
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    4,
    1,
    1,
    1,
};
u16 lbl_1_data_32AA[0x1D] = {
    1,
    2,
    2,
    4,
    4,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    4,
    8,
    0x10,
    1,
    8,
    2,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    1,
    1,
};
u16 lbl_1_data_32E4[0x19] = {
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    4,
    1,
    0x10,
    1,
    0x20,
};
u16 lbl_1_data_3316[0x1D] = {
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    8,
    1,
    8,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x20,
};
u16 lbl_1_data_3350[0x26] = {
    1,
    2,
    2,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    4,
    0x10,
    2,
    4,
    4,
    1,
    0x10,
    8,
    2,
    1,
    2,
    1,
    4,
    0x10,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    8,
    2,
    1,
    0x10,
    0x20,
};
u16 lbl_1_data_339C[0x15] = {
    0x10,
    1,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    0x10,
    1,
    1,
};
u16 lbl_1_data_33C6[0x1A] = {
    0x10,
    1,
    2,
    2,
    1,
    8,
    4,
    4,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_33FA[0x12] = { 0x10, 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 0x10, 4, 1, 4, 0x10, 4, 1, 1 };
u16 lbl_1_data_341E[0x24] = {
    0x10,
    1,
    4,
    4,
    2,
    2,
    2,
    2,
    1,
    8,
    4,
    4,
    4,
    1,
    0x10,
    1,
    8,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3466[0x1B] = {
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    8,
    8,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    0x20,
};
u16 lbl_1_data_349C[0x23] = {
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    8,
    8,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_34E2[0x18] = {
    1,
    2,
    2,
    4,
    4,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3512[0x1F] = {
    1,
    4,
    4,
    1,
    8,
    1,
    0x10,
    8,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3550[0x19] = {
    1,
    2,
    2,
    1,
    0x10,
    4,
    4,
    4,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3582[0x18] = {
    1,
    4,
    4,
    1,
    8,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    1,
    0x10,
    4,
    1,
    0x10,
    4,
    0x20,
};
u16 lbl_1_data_35B2[0xF] = { 1, 4, 4, 1, 0x10, 1, 2, 0x10, 2, 0x10, 2, 1, 0x10, 1, 0x20 };
u16 lbl_1_data_35D0[0x23] = {
    1,
    4,
    4,
    1,
    0x10,
    1,
    2,
    4,
    8,
    8,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    1,
    8,
    4,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3616[0x24] = {
    1,
    4,
    2,
    2,
    1,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    8,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_365E[0x1F] = {
    1,
    0x10,
    1,
    4,
    0x10,
    2,
    0x10,
    4,
    1,
    0x10,
    2,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    4,
    0x10,
    2,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_369C[0x11] = { 1, 0x10, 1, 0x10, 2, 0x10, 2, 1, 0x10, 4, 0x10, 4, 1, 0x10, 1, 0x10, 0x20 };
u16 lbl_1_data_36BE[0x22] = {
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    8,
    2,
    8,
    2,
    4,
    1,
    2,
    0x10,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    4,
    0x10,
    4,
    1,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_3702[0x1B] = {
    1,
    4,
    2,
    2,
    4,
    1,
    0x10,
    1,
    2,
    4,
    0x10,
    2,
    1,
    0x10,
    1,
    8,
    4,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    1,
    0x20,
};
u16 lbl_1_data_3738[0x20] = {
    1,
    2,
    4,
    4,
    2,
    1,
    0x10,
    1,
    4,
    0x10,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    8,
    2,
    1,
    0x10,
    1,
    4,
    1,
    0x10,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    0x20,
};
u16 lbl_1_data_3778[0xF] = { 1, 2, 2, 1, 0x10, 1, 0x10, 1, 4, 4, 0x10, 1, 8, 1, 0x20 };
u16 lbl_1_data_3796[0x1C] = {
    1,
    4,
    2,
    2,
    4,
    4,
    4,
    1,
    1,
    2,
    0x10,
    2,
    1,
    8,
    2,
    0x10,
    2,
    1,
    0x10,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_37CE[0x1C] = {
    1,
    2,
    2,
    1,
    0x10,
    1,
    8,
    4,
    4,
    4,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3806[0x19] = {
    1,
    4,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    0x10,
    2,
    4,
    2,
    4,
    1,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
};
u16 lbl_1_data_3838[0x12] = { 1, 2, 4, 4, 4, 1, 1, 2, 0x10, 2, 1, 0x10, 1, 2, 0x10, 2, 1, 0x20 };
u16 lbl_1_data_385C[0x1C] = {
    1,
    4,
    4,
    2,
    2,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    4,
    4,
    0x10,
    1,
    8,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    1,
    2,
    8,
    0x20,
};
u16 lbl_1_data_3894[0x13] = { 1, 4, 1, 8, 2, 2, 1, 0x10, 1, 0x10, 1, 0x10, 1, 4, 0x10, 4, 1, 1, 1 };
u16 lbl_1_data_38BA[0x13] = { 1, 2, 4, 4, 2, 4, 1, 0x10, 1, 4, 1, 1, 2, 0x10, 2, 0x10, 2, 1, 1 };
u16 lbl_1_data_38E0[0x17] = {
    1,
    4,
    2,
    2,
    1,
    0x10,
    1,
    8,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    1,
};
u16 lbl_1_data_390E[0x17] = {
    1,
    4,
    2,
    2,
    4,
    4,
    1,
    0x10,
    8,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    1,
    2,
    1,
    4,
    0x10,
    0x20,
};
u16 lbl_1_data_393C[0x1E] = {
    1,
    4,
    1,
    8,
    2,
    2,
    1,
    0x10,
    1,
    0x10,
    1,
    0x10,
    8,
    8,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    2,
    8,
    0x10,
    8,
    1,
    0x20,
};
static u16 lbl_1_data_3978[0x20] = {
    1,
    4,
    2,
    2,
    1,
    0x10,
    4,
    4,
    1,
    0x10,
    1,
    4,
    1,
    1,
    2,
    0x10,
    2,
    8,
    0x10,
    8,
    2,
    0x10,
    2,
    0x10,
    2,
    1,
    4,
    0x10,
    4,
    1,
    1,
    0,
};
u16 *lbl_1_data_39B8[0x3C] = {
    lbl_1_data_1184,
    lbl_1_data_18F2,
    lbl_1_data_23D8,
    lbl_1_data_119A,
    lbl_1_data_195A,
    lbl_1_data_243E,
    lbl_1_data_123E,
    lbl_1_data_19E6,
    lbl_1_data_24A8,
    lbl_1_data_1298,
    lbl_1_data_1A5C,
    lbl_1_data_250E,
    lbl_1_data_12EE,
    lbl_1_data_1AEE,
    lbl_1_data_25A4,
    lbl_1_data_133E,
    lbl_1_data_1B64,
    lbl_1_data_2618,
    lbl_1_data_139C,
    lbl_1_data_1BF0,
    lbl_1_data_2690,
    lbl_1_data_1410,
    lbl_1_data_1C7A,
    lbl_1_data_271A,
    lbl_1_data_1472,
    lbl_1_data_1D2E,
    lbl_1_data_279C,
    lbl_1_data_14C2,
    lbl_1_data_1DA4,
    lbl_1_data_27FC,
    lbl_1_data_1538,
    lbl_1_data_1E5C,
    lbl_1_data_2896,
    lbl_1_data_1592,
    lbl_1_data_1ECE,
    lbl_1_data_2902,
    lbl_1_data_15E8,
    lbl_1_data_1F7A,
    lbl_1_data_2988,
    lbl_1_data_1642,
    lbl_1_data_1FF4,
    lbl_1_data_2A00,
    lbl_1_data_16A0,
    lbl_1_data_207E,
    lbl_1_data_2AA2,
    lbl_1_data_1712,
    lbl_1_data_2114,
    lbl_1_data_2B38,
    lbl_1_data_177E,
    lbl_1_data_219C,
    lbl_1_data_2BAC,
    lbl_1_data_17DE,
    lbl_1_data_2252,
    lbl_1_data_2C28,
    lbl_1_data_1846,
    lbl_1_data_22A2,
    lbl_1_data_2CB0,
    lbl_1_data_189E,
    lbl_1_data_2336,
    lbl_1_data_2D2A,
};
u16 *lbl_1_data_3AA8[0x3C] = {
    lbl_1_data_11B6,
    lbl_1_data_190E,
    lbl_1_data_23F4,
    lbl_1_data_11DE,
    lbl_1_data_197E,
    lbl_1_data_2468,
    lbl_1_data_1258,
    lbl_1_data_1A06,
    lbl_1_data_24C4,
    lbl_1_data_12B4,
    lbl_1_data_1A8A,
    lbl_1_data_2530,
    lbl_1_data_1304,
    lbl_1_data_1B0C,
    lbl_1_data_25BC,
    lbl_1_data_1354,
    lbl_1_data_1B90,
    lbl_1_data_2634,
    lbl_1_data_13B6,
    lbl_1_data_1C12,
    lbl_1_data_26B2,
    lbl_1_data_142E,
    lbl_1_data_1CB0,
    lbl_1_data_273A,
    lbl_1_data_1488,
    lbl_1_data_1D50,
    lbl_1_data_27B8,
    lbl_1_data_14DC,
    lbl_1_data_1DD6,
    lbl_1_data_2822,
    lbl_1_data_1552,
    lbl_1_data_1E7E,
    lbl_1_data_28B8,
    lbl_1_data_15B2,
    lbl_1_data_1EFE,
    lbl_1_data_2928,
    lbl_1_data_1604,
    lbl_1_data_1F9A,
    lbl_1_data_29B0,
    lbl_1_data_1660,
    lbl_1_data_2022,
    lbl_1_data_2A2E,
    lbl_1_data_16BA,
    lbl_1_data_20A0,
    lbl_1_data_2AC2,
    lbl_1_data_1730,
    lbl_1_data_2144,
    lbl_1_data_2B62,
    lbl_1_data_1798,
    lbl_1_data_21BE,
    lbl_1_data_2BD4,
    lbl_1_data_17FC,
    lbl_1_data_2284,
    lbl_1_data_2C4E,
    lbl_1_data_185E,
    lbl_1_data_22CC,
    lbl_1_data_2CD4,
    lbl_1_data_18BC,
    lbl_1_data_2376,
    lbl_1_data_2D56,
};
u16 *lbl_1_data_3B98[0x78] = {
    lbl_1_data_11FE,
    lbl_1_data_192C,
    lbl_1_data_2414,
    lbl_1_data_2DBA,
    lbl_1_data_2DE4,
    lbl_1_data_2E12,
    lbl_1_data_1222,
    lbl_1_data_19C0,
    lbl_1_data_248A,
    lbl_1_data_2E4C,
    lbl_1_data_2E6C,
    lbl_1_data_2E7C,
    lbl_1_data_1272,
    lbl_1_data_1A34,
    lbl_1_data_24E4,
    lbl_1_data_2E96,
    lbl_1_data_2EC4,
    lbl_1_data_2EF6,
    lbl_1_data_12E2,
    lbl_1_data_1AC4,
    lbl_1_data_2566,
    lbl_1_data_2F2A,
    lbl_1_data_2F4C,
    lbl_1_data_2F8A,
    lbl_1_data_136E,
    lbl_1_data_1B2A,
    lbl_1_data_25DE,
    lbl_1_data_2FB4,
    lbl_1_data_2FF0,
    lbl_1_data_305C,
    lbl_1_data_131C,
    lbl_1_data_1BBC,
    lbl_1_data_2656,
    lbl_1_data_3024,
    lbl_1_data_3080,
    lbl_1_data_30A6,
    lbl_1_data_13CE,
    lbl_1_data_1C30,
    lbl_1_data_26CE,
    lbl_1_data_30DA,
    lbl_1_data_3114,
    lbl_1_data_3186,
    lbl_1_data_1442,
    lbl_1_data_1CF0,
    lbl_1_data_275E,
    lbl_1_data_3158,
    lbl_1_data_31CA,
    lbl_1_data_31FE,
    lbl_1_data_14A0,
    lbl_1_data_1D76,
    lbl_1_data_27D4,
    lbl_1_data_3248,
    lbl_1_data_327C,
    lbl_1_data_32AA,
    lbl_1_data_14FC,
    lbl_1_data_1E26,
    lbl_1_data_2854,
    lbl_1_data_32E4,
    lbl_1_data_3316,
    lbl_1_data_3350,
    lbl_1_data_1568,
    lbl_1_data_1E98,
    lbl_1_data_28D2,
    lbl_1_data_339C,
    lbl_1_data_33C6,
    lbl_1_data_33FA,
    lbl_1_data_15CA,
    lbl_1_data_1F34,
    lbl_1_data_294A,
    lbl_1_data_341E,
    lbl_1_data_3466,
    lbl_1_data_349C,
    lbl_1_data_161C,
    lbl_1_data_1FC2,
    lbl_1_data_29D0,
    lbl_1_data_34E2,
    lbl_1_data_3512,
    lbl_1_data_3550,
    lbl_1_data_1678,
    lbl_1_data_205E,
    lbl_1_data_2A50,
    lbl_1_data_3582,
    lbl_1_data_35B2,
    lbl_1_data_35D0,
    lbl_1_data_16DA,
    lbl_1_data_20CC,
    lbl_1_data_2AEC,
    lbl_1_data_3616,
    lbl_1_data_365E,
    lbl_1_data_36BE,
    lbl_1_data_1744,
    lbl_1_data_2174,
    lbl_1_data_2B7A,
    lbl_1_data_369C,
    lbl_1_data_3702,
    lbl_1_data_3738,
    lbl_1_data_17B4,
    lbl_1_data_221E,
    lbl_1_data_2BF8,
    lbl_1_data_3796,
    lbl_1_data_37CE,
    lbl_1_data_3806,
    lbl_1_data_1826,
    lbl_1_data_21EA,
    lbl_1_data_2C72,
    lbl_1_data_3778,
    lbl_1_data_3838,
    lbl_1_data_385C,
    lbl_1_data_187E,
    lbl_1_data_22FE,
    lbl_1_data_2CFE,
    lbl_1_data_3894,
    lbl_1_data_38BA,
    lbl_1_data_38E0,
    lbl_1_data_18D2,
    lbl_1_data_239A,
    lbl_1_data_2D7A,
    lbl_1_data_390E,
    lbl_1_data_393C,
    lbl_1_data_3978,
};
s32 lbl_1_bss_0;
omObjData *lbl_1_bss_4;
HUPROCESS *lbl_1_bss_8;
u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };            /* const */
f32 lbl_1_rodata_18[9] = { -150.0f, 25.0f, 1000.0f, 0.0f, 25.0f, 1000.0f, 0.0f, 25.0f, 450.0f }; /* const */
f32 lbl_1_rodata_3C[4] = { 160.0f, 180.0f, 195.0f, 200.0f }; /* const */
Vec lbl_1_rodata_A4 = { -150.0f, 25.0f, 1000.0f }; /* const */
f32 lbl_1_rodata_B0[4] = { 180.0f, 90.0f, 270.0f, 0.0f }; /* const */
u16 lbl_1_rodata_C0[4] = { 0x30, 0x50, 0x30, 0x50 }; /* const */
Vec lbl_1_rodata_FC = { 0.0f, 0.0f, 0.0f };     /* const */
Vec lbl_1_rodata_108 = { 0.0f, 0.0f, 0.0f };    /* const */
Vec lbl_1_rodata_114 = { 0.0f, 180.0f, 0.0f };  /* const */
Vec lbl_1_rodata_120 = { 0.0f, 400.0f, 0.0f };  /* const */
Vec lbl_1_rodata_12C = { 0.0f, 800.0f, 0.0f };  /* const */
Vec lbl_1_rodata_138 = { 0.0f, 0.0f, 0.0f };    /* const */
f32 lbl_1_rodata_148[4] = { 180.0f, 90.0f, 270.0f, 0.0f }; /* const */
u16 lbl_1_rodata_15C[4] = { 3, 2, 1, 0 };           /* const */
u16 lbl_1_rodata_164[0x10] = { 0, 2, 1, 3, 1, 0, 3, 2, 2, 3, 0, 1, 3, 1, 2, 0 }; /* const */
u16 lbl_1_rodata_184[4] = { 0x30, 0x50, 0x30, 0x50 }; /* const */
f32 lbl_1_rodata_194[4] = { 180.0f, 90.0f, 270.0f, 0.0f }; /* const */
f32 lbl_1_rodata_1FC[4] = { 8.0f, -8.0f, 8.0f, -8.0f }; /* const */
f32 lbl_1_rodata_20C[4] = { 20.0f, 20.0f, -20.0f, -20.0f }; /* const */
f32 lbl_1_rodata_224[4] = { -450.0f, -600.0f, -750.0f, -900.0f }; /* const */
u16 lbl_1_rodata_234[4] = { 0x30, 0x50, 0x30, 0x50 }; /* const */
f32 lbl_1_rodata_24C[2] = { 0.0f, 400.0f };         /* const */
f32 lbl_1_rodata_254[2] = { 400.0f, 800.0f };       /* const */
Vec lbl_1_rodata_260 = { 0.0f, 1.0f, 0.0f };    /* const */
Vec lbl_1_rodata_27C[4] = {
    { 130.0f, 110.0f, -800.0f },
    { 30.0f, 100.0f, -780.0f },
    { -40.0f, 120.0f, -810.0f },
    { -120.0f, 110.0f, -800.0f },
}; /* const */
f32 lbl_1_rodata_2AC[4] = { 3.9f, 5.7f, 9.3f, 7.5f }; /* const */
s32 lbl_1_rodata_2BC[4] = { 0xF, 0x12, 0x10, 0xE }; /* const */
u16 lbl_1_rodata_2E4[4] = { 0x78, 0x3C, 0x2D, 0x1E }; /* const */
u16 lbl_1_rodata_2EC[4] = { 0x3C, 0x1E, 0xF, 0 };   /* const */
u16 lbl_1_rodata_2F4[4] = { 0x78, 0x3C, 0x2D, 0x1E }; /* const */
u16 lbl_1_rodata_2FC[4] = { 0x78, 0x5A, 0x3C, 0x2D }; /* const */
u16 lbl_1_rodata_304[4] = { 0x1E, 0, 0, 0 };        /* const */
u16 lbl_1_rodata_30C[4] = { 0x3C, 0x2D, 0x1E, 0xF }; /* const */
u16 lbl_1_rodata_314[6] = { 3, 4, 6, 9, 0, 0 };     /* const */



void ObjectSetup(void) {
    omObjData *temp_r31;
    omObjData *temp_r3;
    s32 var_r29;
    M515Main *temp_r30;

    lbl_1_bss_8 = omInitObjMan(0x1F4, 0x2000);
    omGameSysInit(lbl_1_bss_8);
    temp_r3 = omAddObjEx(lbl_1_bss_8, 0x65, 0U, 0U, -1, fn_1_29D0);
    lbl_1_bss_4 = temp_r3;
    temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M515Main), MEMORY_DEFAULT_NUM);
    temp_r30 = temp_r3->data;
    fn_1_2B6C((M515Main *) temp_r30);
    fn_1_2EB4();
    fn_1_C83C();
    var_r29 = 0;
loop_2:
    if (var_r29 < 4) {
        temp_r31 = omAddObjEx(lbl_1_bss_8, 0x64, 1U, 8U, 0, fn_1_1D60);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M515Player), MEMORY_DEFAULT_NUM);
        temp_r31->work[0] = (u32) var_r29;
        temp_r30->unk224[var_r29] = temp_r31->data;
        var_r29 += 1;
        goto loop_2;
    }
    fn_1_2F3C((M515Main *) temp_r30);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DNoSyncSet(1);
    MgSeqCreate(&lbl_1_data_0);
    temp_r30->unkCAC = 0;
}

void fn_1_1FC(s16 mode, s16 frameNo) {
    M515Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r31->unk1D0 = 0;
    temp_r31->unk1DA = 0;
    temp_r31->unk1D2 = 0;
    temp_r31->unk1D6 = -1;
    temp_r31->unk1F4 = 0;
    fn_1_32C4((M515Main *) temp_r31);
    fn_1_CE98((M515Main *) temp_r31);
    MgSeqModeNext();
}

void fn_1_26C(s16 mode, s16 frameNo) {
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f31;
    s16 temp_r0;
    s32 var_r29;
    M515Player *temp_r30;
    M515Main *temp_r31;

    sp18 = lbl_1_rodata_18[0];
    sp1C = lbl_1_rodata_18[1];
    sp20 = lbl_1_rodata_18[2];
    sp24 = lbl_1_rodata_18[3];
    sp28 = lbl_1_rodata_18[4];
    sp2C = lbl_1_rodata_18[5];
    sp30 = lbl_1_rodata_18[6];
    sp34 = lbl_1_rodata_18[7];
    sp38 = lbl_1_rodata_18[8];
    sp8 = lbl_1_rodata_3C[0];
    spC = lbl_1_rodata_3C[1];
    sp10 = lbl_1_rodata_3C[2];
    sp14 = lbl_1_rodata_3C[3];
    temp_r31 = lbl_1_bss_4->data;
    temp_r30 = temp_r31->unk224[0];
    temp_r0 = temp_r31->unk1DA;
    if ((u32) temp_r0 <= 6U) {
        switch (temp_r0) {
        case 0:
            HuAudFXPlay(0x6E8);
            MgSeqModeChangeOff();
            temp_r31->unk1D2 = 0;
            temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            /* fallthrough */
        case 1:
            fn_1_D0D8((M515Main *) temp_r31);
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            temp_f31 = (f32) temp_r31->unk1D2 / 40.0f;
            temp_r30->unk44C.x = (f32) ((sp18 * (1.0f - temp_f31)) + (sp24 * temp_f31));
            omSetTra(temp_r30->unk68C, temp_r30->unk44C.x, temp_r30->unk44C.y, temp_r30->unk44C.z);
            if ((s16) temp_r31->unk1D2 >= 0x28) {
                Hu3DMotionShiftSet(*temp_r30->unk68C->model, *temp_r30->unk68C->motion, 0.0f, 5.0f, 0U);
                temp_r31->unk1D2 = 0;
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                return;
            }
            break;
        case 2:
            fn_1_D0D8((M515Main *) temp_r31);
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 >= 0x1E) {
                Hu3DMotionShiftSet(*temp_r30->unk68C->model, temp_r30->unk68C->motion[6], 60.0f, 5.0f, 0U);
                temp_r31->unk1D2 = 0;
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                return;
            }
            break;
        case 3:
            fn_1_D0D8((M515Main *) temp_r31);
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 == 0x37) {
                Hu3DMotionShiftSet(*temp_r30->unk68C->model, *temp_r30->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
            }
            temp_f31_2 = (f32) temp_r31->unk1D2 / 60.0f;
            temp_r30->unk458.y = (f32) ((90.0f * (1.0f - temp_f31_2)) + (180.0f * temp_f31_2));
            omSetRot(temp_r30->unk68C, temp_r30->unk458.x, temp_r30->unk458.y, temp_r30->unk458.z);
            if ((s16) temp_r31->unk1D2 >= 0x3C) {
                HuAudFXPlay(0x6DF);
                Hu3DModelAttrReset(temp_r31->unkA6[0], 0x40000002U);
                temp_r31->unk1D2 = 0;
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                temp_r31->unk130[0].unk0 = (s32) (temp_r31->unk130[0].unk0 + 1);
                temp_r31->unk130[1].unk0 = (s32) (temp_r31->unk130[1].unk0 + 1);
                temp_r31->unk130[2].unk0 = (s32) (temp_r31->unk130[2].unk0 + 1);
                temp_r31->unk130[3].unk0 = (s32) (temp_r31->unk130[3].unk0 + 1);
                return;
            }
            break;
        case 4:
            fn_1_D0D8((M515Main *) temp_r31);
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 >= 0x50) {
                Hu3DMotionShiftSet(*temp_r30->unk68C->model, temp_r30->unk68C->motion[1], 0.0f, 5.0f, 0x40000001U);
                temp_r31->unk1D2 = 0;
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                return;
            }
            break;
        case 5:
            fn_1_D0D8((M515Main *) temp_r31);
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            var_f31 = (f32) temp_r31->unk1D2 / 120.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
                if (((s16) *temp_r30->unk68C->motion != Hu3DMotionIDGet(*temp_r30->unk68C->model)) && ((s16) *temp_r30->unk68C->motion != Hu3DMotionShiftIDGet(*temp_r30->unk68C->model))) {
                    Hu3DMotionShiftSet(*temp_r30->unk68C->model, *temp_r30->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
                }
            }
            temp_r30->unk44C.z = (f32) ((sp2C * (1.0f - var_f31)) + (sp38 * var_f31));
            omSetTra(temp_r30->unk68C, temp_r30->unk44C.x, temp_r30->unk44C.y, temp_r30->unk44C.z);
            if ((s16) temp_r31->unk1D2 == 0x3C) {
                Hu3DModelAttrSet(temp_r31->unkA6[0], 0x40000004U);
            }
            if ((s16) temp_r31->unk1D2 == 0x2D) {
                Hu3DModelAttrReset(temp_r31->unk1E[0], 1U);
            }
            if ((s16) temp_r31->unk1D2 > 0x14) {
                if (fn_1_83E8(&temp_r31->unk234[0]) != 0) {
                    var_r29 = 0;
loop_25:
                    if (var_r29 < 4) {
                        Hu3DModelAttrSet(temp_r31->unk130[var_r29].unkC, 1U);
                        var_r29 += 1;
                        goto loop_25;
                    }
                    temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                }
                temp_f30 = (f32) temp_r31->unk234[0].unk26 / 120.0f;
                temp_r31->unk334.unk4 = (f32) ((640.0f * (1.0f - temp_f30)) + (320.0f * temp_f30));
                temp_r31->unk334.unk8 = (f32) ((480.0f * (1.0f - temp_f30)) + (240.0f * temp_f30));
                fn_1_9958(&temp_r31->unk334);
                return;
            }
            break;
        case 6:
            lbl_1_bss_0 = HuAudBGMPlay(0x37);
            MgSeqModeNext();
            break;
        }
    }
}

void fn_1_928(s16 mode, s16 frameNo) {
    Hu3DModelAttrSet(((M515Main *)lbl_1_bss_4->data)->unkC, 1U);
}

void fn_1_968(s16 mode, s16 frameNo) {
    s32 sp8[4];
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    M515Main *temp_r30;
    M515Player *temp_r31;

    temp_r30 = lbl_1_bss_4->data;
    var_r28 = 0;
    var_r29 = 0;
loop_4:
    if (var_r29 < 4) {
        sp8[var_r28] = -1;
        if ((s16) (temp_r30->unk224[var_r29])->unk482 == 5) {
            sp8[var_r28] = var_r29;
            var_r28 += 1;
        }
        var_r29 += 1;
        goto loop_4;
    }
    if (var_r28 != 0) {
        temp_r30->unkCAC = 1;
        if (var_r28 == 1) {
            temp_r30->unk1D6 = (s16) sp8[0];
        } else {
            temp_r30->unk1D6 = (s16) sp8[rand8() / (s32) ((0xFF / var_r28) + 1)];
        }
        MgSeqModeNext();
        var_r29_2 = 0;
loop_17:
        if (var_r29_2 < 4) {
            temp_r31 = temp_r30->unk224[var_r29_2];
            if (((s32 (*)(M515Seq *, M515Player *)) temp_r31->unk688) != fn_1_9DF8) {
                if (var_r29_2 == (s16) temp_r30->unk1D6) {
                    temp_r31->unk688 = fn_1_B5D8;
                } else {
                    temp_r31->unk688 = fn_1_B0B8;
                    if ((s16) temp_r31->unk482 == 5) {
                        temp_r31->unk470.x = (s32) temp_r31->unk464.x;
                        temp_r31->unk470.y = (s32) temp_r31->unk464.y;
                        temp_r31->unk470.z = (s32) temp_r31->unk464.z;
                        temp_r31->unk484 = 0;
                    }
                }
                temp_r31->unk684->unk0 = 0;
            }
            temp_r31->unk680 = 0;
            temp_r31->unk682 = 0;
            var_r29_2 += 1;
            goto loop_17;
        }
        return;
    }
    temp_r30->unk1D4 = 1;
}

void fn_1_B08(s16 mode, s16 frameNo) {
    M515Player *temp_r31_2;
    s16 temp_r0;
    s32 var_r29;
    s32 var_r29_2;
    M515Main *temp_r30;
    M515Player *temp_r31;

    temp_r30 = lbl_1_bss_4->data;
    temp_r30->unk1D4 = 0;
    temp_r0 = temp_r30->unk1D0;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        HuAudSStreamFadeOut(lbl_1_bss_0, 0x3E8);
        temp_r30->unkCAC = 1;
        if ((s16) temp_r30->unk1D6 >= 0) {
            MgSeqWinnerSet((temp_r30->unk224[temp_r30->unk1D6])->unk2, -1, -1, -1);
        } else {
            var_r29 = 0;
loop_10:
            if (var_r29 < 4) {
                temp_r31 = temp_r30->unk224[var_r29];
                if (((s32 (*)(M515Seq *, M515Player *)) temp_r31->unk688) != fn_1_9DF8) {
                    temp_r31->unk688 = fn_1_B0B8;
                    temp_r31->unk684->unk0 = 0;
                }
                temp_r31->unk680 = 0;
                temp_r31->unk682 = 0;
                var_r29 += 1;
                goto loop_10;
            }
            MgSeqWinnerSet(-1, -1, -1, -1);
        }
        temp_r30->unk1DA = 0;
        temp_r30->unk1D0 = (s16) (temp_r30->unk1D0 + 1);
        break;
    }
    var_r29_2 = 0;
loop_23:
    if (var_r29_2 < 4) {
        temp_r31_2 = temp_r30->unk224[var_r29_2];
        if (((s32 (*)(M515Seq *, M515Player *)) temp_r31_2->unk688) != NULL) {
            if ((temp_r31_2->unk688(temp_r31_2->unk684, temp_r31_2) != 0) && (((s32 (*)(M515Seq *, M515Player *)) temp_r31_2->unk688) == fn_1_9DF8)) {
                temp_r31_2->unk688 = fn_1_B0B8;
                temp_r31_2->unk684->unk0 = 0;
            }
            if (((s32 (*)(M515Seq *, M515Player *)) temp_r31_2->unk688) == fn_1_9DF8) {
                fn_1_5FD0(temp_r31_2);
                fn_1_611C(temp_r31_2);
                omSetTra(temp_r31_2->unk68C, temp_r31_2->unk44C.x, temp_r31_2->unk44C.y, temp_r31_2->unk44C.z);
                omSetRot(temp_r31_2->unk68C, temp_r31_2->unk458.x, temp_r31_2->unk458.y, temp_r31_2->unk458.z);
            }
            if (((s32 (*)(M515Seq *, M515Player *)) temp_r31_2->unk688) == fn_1_D928) {
                temp_r31_2->unk688 = fn_1_B0B8;
                temp_r31_2->unk684->unk0 = 0;
            }
        }
        var_r29_2 += 1;
        goto loop_23;
    }
}

void fn_1_D30(s16 mode, s16 frameNo) {
    M515Player *temp_r30_7;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 var_f31;
    f32 var_f31_2;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r4;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    M515Player *temp_r30;
    M515Player *temp_r30_2;
    M515Player *temp_r30_3;
    M515Player *temp_r30_4;
    M515Player *temp_r30_5;
    M515Player *temp_r30_6;
    M515Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unk1DA;
    if ((u32) temp_r0 <= 7U) {
        switch (temp_r0) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            MgSeqModeChangeOff();
            temp_r31->unk1D2 = 0;
            temp_r31->unk1D0 = 0;
            temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            /* fallthrough */
        case 1:                                     /* switch 1 */
            var_r27 = 0;
            var_r29 = 0;
loop_8:
            if (var_r29 < 4) {
                temp_r30 = temp_r31->unk224[var_r29];
                if ((temp_r30->unk688 == fn_1_B0B8) || (temp_r30->unk688 == fn_1_B5D8)) {
                    var_r27 += 1;
                }
                var_r29 += 1;
                goto loop_8;
            }
            if (var_r27 >= 4) {
                if ((s16) temp_r31->unk1D6 < 0) {
                    temp_r31->unk1D0 = 3;
                    MgSeqModeNext();
                } else {
                    (temp_r31->unk224[temp_r31->unk1D6])->unk688 = fn_1_BA64;
                    temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                }
            }
            break;
        case 2:                                     /* switch 1 */
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 == 0x14) {
                WipeColorSet(0xFFU, 0xFFU, 0xFFU);
                WipeCreate(2, 0, 0x3C);
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            }
            temp_f31 = (f32) temp_r31->unk1D2 / 60.0f;
            temp_r0_2 = temp_r31->unk1D6;
            switch (temp_r0_2) {                    /* switch 2; irregular */
            case -1:                                /* switch 2 */
                break;
            case 0:                                 /* switch 2 */
                temp_r31->unk334.unk4 = (f32) ((320.0f * (1.0f - temp_f31)) + (640.0f * temp_f31));
                temp_r31->unk334.unk8 = (f32) ((240.0f * (1.0f - temp_f31)) + (480.0f * temp_f31));
                break;
            case 1:                                 /* switch 2 */
                temp_r31->unk334.unk4 = (f32) (320.0f * (1.0f - temp_f31));
                temp_r31->unk334.unk8 = (f32) ((240.0f * (1.0f - temp_f31)) + (480.0f * temp_f31));
                break;
            case 2:                                 /* switch 2 */
                temp_r31->unk334.unk4 = (f32) ((320.0f * (1.0f - temp_f31)) + (640.0f * temp_f31));
                temp_r31->unk334.unk8 = (f32) (240.0f * (1.0f - temp_f31));
                break;
            case 3:                                 /* switch 2 */
                temp_r31->unk334.unk4 = (f32) (320.0f * (1.0f - temp_f31));
                temp_r31->unk334.unk8 = (f32) (240.0f * (1.0f - temp_f31));
                break;
            }
            fn_1_9958(&temp_r31->unk334);
            break;
        case 3:                                     /* switch 1 */
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 > 0x3C) {
                temp_r31->unk1D2 = 0x3C;
            }
            temp_f31_2 = (f32) temp_r31->unk1D2 / 60.0f;
            temp_r4 = temp_r31->unk1D6;
            switch (temp_r4) {                      /* switch 3; irregular */
            case -1:                                /* switch 3 */
                break;
            case 0:                                 /* switch 3 */
                temp_r31->unk334.unk4 = (f32) ((320.0f * (1.0f - temp_f31_2)) + (640.0f * temp_f31_2));
                temp_r31->unk334.unk8 = (f32) ((240.0f * (1.0f - temp_f31_2)) + (480.0f * temp_f31_2));
                break;
            case 1:                                 /* switch 3 */
                temp_r31->unk334.unk4 = (f32) (320.0f * (1.0f - temp_f31_2));
                temp_r31->unk334.unk8 = (f32) ((240.0f * (1.0f - temp_f31_2)) + (480.0f * temp_f31_2));
                break;
            case 2:                                 /* switch 3 */
                temp_r31->unk334.unk4 = (f32) ((320.0f * (1.0f - temp_f31_2)) + (640.0f * temp_f31_2));
                temp_r31->unk334.unk8 = (f32) (240.0f * (1.0f - temp_f31_2));
                break;
            case 3:                                 /* switch 3 */
                temp_r31->unk334.unk4 = (f32) (320.0f * (1.0f - temp_f31_2));
                temp_r31->unk334.unk8 = (f32) (240.0f * (1.0f - temp_f31_2));
                break;
            }
            fn_1_9958(&temp_r31->unk334);
            if (WipeCheckEnd() == 0) {
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            }
            break;
        case 4:                                     /* switch 1 */
            HuAudFXPlay(0x39E);
            WipeCreate(1, 0, 0x3C);
            temp_r30_2 = temp_r31->unk224[temp_r31->unk1D6];
            temp_r30_2->unk44C.x = 0.0f;
            temp_r30_2->unk44C.y = 25.0f;
            temp_r30_2->unk44C.z = 100.0f;
            temp_r30_2->unk458.x = 0.0f;
            temp_r30_2->unk458.y = 180.0f;
            temp_r30_2->unk458.z = 0.0f;
            temp_r30_2->unk688 = 0;
            omSetTra(temp_r30_2->unk68C, temp_r30_2->unk44C.x, temp_r30_2->unk44C.y, temp_r30_2->unk44C.z);
            omSetRot(temp_r30_2->unk68C, temp_r30_2->unk458.x, temp_r30_2->unk458.y, temp_r30_2->unk458.z);
            Hu3DShadowMultiSizeSet(0xF0U, (s16) lbl_1_rodata_10[temp_r30_2->unk0]);
            Hu3DShadowMultiColSet(0x19U, 0U, 0U, (s16) lbl_1_rodata_10[temp_r30_2->unk0]);
            CharMotionSet(temp_r30_2->unk2, temp_r30_2->unk68C->motion[1]);
            Hu3DCameraPerspectiveSet((s32) lbl_1_rodata_10[temp_r30_2->unk0], 45.0f, 20.0f, 12000.0f, 1.2f);
            temp_r31->unk234[temp_r30_2->unk0].unk0 = lbl_1_data_28[0x36];
            temp_r31->unk234[temp_r30_2->unk0].unk4 = lbl_1_data_28[0x37];
            temp_r31->unk234[temp_r30_2->unk0].unk8 = lbl_1_data_28[0x38];
            temp_r31->unk234[temp_r30_2->unk0].unkC.x = lbl_1_data_28[0x39];
            temp_r31->unk234[temp_r30_2->unk0].unkC.y = lbl_1_data_28[0x3A];
            temp_r31->unk234[temp_r30_2->unk0].unkC.z = lbl_1_data_28[0x3B];
            temp_r31->unk1F4 = 1;
            Hu3DModelAttrReset(temp_r31->unkD6, 1U);
            Hu3DModelAttrReset(temp_r31->unkD6, 0x40000002U);
            Hu3DModelAttrSet(temp_r31->unkD6, 0x40000001U);
            Hu3DModelAttrReset(temp_r31->unkD8, 1U);
            Hu3DModelAttrReset(temp_r31->unkDA, 1U);
            fn_1_BF24((M515Main *) temp_r31, temp_r31->unk8, 0);
            fn_1_BF24((M515Main *) temp_r31, temp_r31->unkA, 0);
            var_r29_2 = 0;
loop_58:
            if (var_r29_2 < 4) {
                Hu3DModelAttrSet(temp_r31->unkE[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk16[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk1E[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk26[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk2E[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk36[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk3E[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk46[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk4E[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk56[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk5E[var_r29_2 * 2 + 0], 1U);
                Hu3DModelAttrSet(temp_r31->unk5E[var_r29_2 * 2 + 1], 1U);
                Hu3DModelAttrSet(temp_r31->unk6E[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unk76[var_r29_2 * 4 + 0], 1U);
                Hu3DModelAttrSet(temp_r31->unk76[var_r29_2 * 4 + 1], 1U);
                Hu3DModelAttrSet(temp_r31->unk76[var_r29_2 * 4 + 2], 1U);
                Hu3DModelAttrSet(temp_r31->unk76[var_r29_2 * 4 + 3], 1U);
                Hu3DModelAttrSet(temp_r31->unk96[var_r29_2 * 2 + 0], 1U);
                Hu3DModelAttrSet(temp_r31->unk96[var_r29_2 * 2 + 1], 1U);
                Hu3DModelAttrSet(temp_r31->unkA6[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unkAE[var_r29_2], 1U);
                Hu3DModelAttrSet(temp_r31->unkB6[var_r29_2 * 3 + 0], 1U);
                Hu3DModelAttrSet(temp_r31->unkB6[var_r29_2 * 3 + 1], 1U);
                Hu3DModelAttrSet(temp_r31->unkB6[var_r29_2 * 3 + 2], 1U);
                temp_r30_3 = temp_r31->unk224[var_r29_2];
                var_r28 = 0;
loop_47:
                if (var_r28 < (s16) temp_r30_3->unk5E8) {
                    Hu3DModelAttrSet(temp_r30_3->unk488[var_r28].unk0, 1U);
                    Hu3DModelAttrSet(temp_r30_3->unk488[var_r28].unk4, 1U);
                    var_r28 += 1;
                    goto loop_47;
                }
                var_r28_2 = 0;
loop_56:
                if (var_r28_2 < 0x19) {
                    if ((s16) temp_r30_3->unk5EA[var_r28_2] >= 0) {
                        Hu3DModelAttrSet(temp_r30_3->unk5EA[var_r28_2], 1U);
                    }
                    if ((s16) temp_r30_3->unk5EA[25 + var_r28_2] >= 0) {
                        Hu3DModelAttrSet(temp_r30_3->unk5EA[25 + var_r28_2], 1U);
                    }
                    if ((s16) temp_r30_3->unk5EA[50 + var_r28_2] >= 0) {
                        Hu3DModelAttrSet(temp_r30_3->unk5EA[50 + var_r28_2], 1U);
                    }
                    var_r28_2 += 1;
                    goto loop_56;
                }
                var_r29_2 += 1;
                goto loop_58;
            }
            temp_r31->unk1D2 = 0;
            temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            break;
        case 5:                                     /* switch 1 */
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            var_f31 = (f32) temp_r31->unk1D2 / 120.0f;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            temp_r30_4 = temp_r31->unk224[temp_r31->unk1D6];
            temp_r30_4->unk44C.z = (f32) ((100.0f * (1.0f - var_f31)) - (200.0f * var_f31));
            omSetTra(temp_r30_4->unk68C, temp_r30_4->unk44C.x, temp_r30_4->unk44C.y, temp_r30_4->unk44C.z);
            if (WipeCheckEnd() == 0) {
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
                temp_r31->unk1D2 = 0;
                temp_r30_5 = temp_r31->unk224[temp_r31->unk1D6];
                Hu3DMotionShiftSet(*temp_r30_5->unk68C->model, temp_r30_5->unk68C->motion[7], 0.0f, 5.0f, 0U);
            }
            break;
        case 6:                                     /* switch 1 */
            temp_r30_6 = temp_r31->unk224[temp_r31->unk1D6];
            temp_r31->unk1D2 = (s16) (temp_r31->unk1D2 + 1);
            if ((s16) temp_r31->unk1D2 == 0x36) {
                Hu3DMotionShiftSet(*temp_r30_6->unk68C->model, *temp_r30_6->unk68C->motion, 0.0f, 5.0f, 0U);
            }
            if ((s16) temp_r31->unk1D2 >= 0x3C) {
                temp_r31->unk1DA = (s16) (temp_r31->unk1DA + 1);
            }
            var_f31_2 = (f32) temp_r31->unk1D2 / 60.0f;
            if (var_f31_2 > 1.0f) {
                var_f31_2 = 1.0f;
            }
            temp_r30_6->unk458.y = (f32) (180.0f * (1.0f - var_f31_2));
            omSetRot(temp_r30_6->unk68C, temp_r30_6->unk458.x, temp_r30_6->unk458.y, temp_r30_6->unk458.z);
            break;
        case 7:                                     /* switch 1 */
            temp_r31->unk1D0 = 0;
            MgSeqModeNext();
            break;
        }
    }
    var_r29_3 = 0;
loop_82:
    if (var_r29_3 < 4) {
        temp_r30_7 = temp_r31->unk224[var_r29_3];
        if (((s32 (*)(M515Seq *, M515Player *)) temp_r30_7->unk688) != NULL) {
            if ((temp_r30_7->unk688(temp_r30_7->unk684, temp_r30_7) != 0) && (((s32 (*)(M515Seq *, M515Player *)) temp_r30_7->unk688) == fn_1_9DF8)) {
                temp_r30_7->unk688 = fn_1_B0B8;
                temp_r30_7->unk684->unk0 = 0;
            }
            if (((s32 (*)(M515Seq *, M515Player *)) temp_r30_7->unk688) == fn_1_9DF8) {
                fn_1_5FD0(temp_r30_7);
                fn_1_611C(temp_r30_7);
                omSetTra(temp_r30_7->unk68C, temp_r30_7->unk44C.x, temp_r30_7->unk44C.y, temp_r30_7->unk44C.z);
                omSetRot(temp_r30_7->unk68C, temp_r30_7->unk458.x, temp_r30_7->unk458.y, temp_r30_7->unk458.z);
            }
            if (((s32 (*)(M515Seq *, M515Player *)) temp_r30_7->unk688) == fn_1_D928) {
                temp_r30_7->unk688 = fn_1_B0B8;
                temp_r30_7->unk684->unk0 = 0;
            }
        }
        var_r29_3 += 1;
        goto loop_82;
    }
}

void fn_1_1B58(s16 mode, s16 frameNo) {
    s16 temp_r0;
    s16 temp_r28;
    s32 var_r29;
    M515Player *temp_r30;
    M515Player *temp_r30_2;
    M515Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unk1D0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r30 = temp_r31->unk224[temp_r31->unk1D6];
        Hu3DMotionShiftSet(*temp_r30->unk68C->model, temp_r30->unk68C->motion[4], 0.0f, 5.0f, 0U);
        temp_r28 = temp_r30->unk0;
        if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
            GWPlayer[temp_r28].coin_win = 0xA;
        }
        temp_r31->unk1D2 = 0;
        temp_r31->unk1D0 = (s16) (temp_r31->unk1D0 + 1);
        /* fallthrough */
    case 1:
        Hu3DModelAttrReset(*temp_r31->unk224[temp_r31->unk1D6]->unk68C->model, 0x40000001U);
        temp_r31->unk1D0 = (s16) (temp_r31->unk1D0 + 1);
        return;
    case 3:
        var_r29 = 0;
loop_14:
        if (var_r29 < 4) {
            temp_r30_2 = temp_r31->unk224[var_r29];
            Hu3DMotionShiftSet(*temp_r30_2->unk68C->model, temp_r30_2->unk68C->motion[5], 0.0f, 5.0f, 0U);
            var_r29 += 1;
            goto loop_14;
        }
        CharLoseVoicePlay(temp_r31->unk224[0]->unk2, temp_r31->unk224[1]->unk2, temp_r31->unk224[2]->unk2, temp_r31->unk224[3]->unk2);
        temp_r31->unk1D0 = (s16) (temp_r31->unk1D0 + 1);
        /* fallthrough */
    case 2:
    case 4:
        return;
    }
}

void fn_1_1D20(s16 mode, s16 frameNo) {

}

void fn_1_1D24(s16 mode, s16 frameNo) {
    fn_1_9920(&((M515Main *) lbl_1_bss_4->data)->unk334);
}

void fn_1_1D60(omObjData *obj) {
    f32 sp10[7];
    u16 sp8[4];
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r29_4;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    s32 var_r30_6;
    s32 var_r30_7;
    s32 var_r30_8;
    s32 var_r30_9;
    u16 *var_r26;
    u16 temp_r4;
    M515Main *temp_r27;
    M515Player *temp_r31;
    M515Node *temp_r4_2;
    M515Node *temp_r4_3;
    M515Node *temp_r5;

    sp10[4] = lbl_1_rodata_A4.x;
    sp10[5] = lbl_1_rodata_A4.y;
    sp10[6] = lbl_1_rodata_A4.z;
    sp10[0] = lbl_1_rodata_B0[0];
    sp10[1] = lbl_1_rodata_B0[1];
    sp10[2] = lbl_1_rodata_B0[2];
    sp10[3] = lbl_1_rodata_B0[3];
    sp8[0] = lbl_1_rodata_C0[0];
    sp8[1] = lbl_1_rodata_C0[1];
    sp8[2] = lbl_1_rodata_C0[2];
    sp8[3] = lbl_1_rodata_C0[3];
    temp_r31 = obj->data;
    temp_r27 = lbl_1_bss_4->data;
    temp_r31->unkE = 0;
    temp_r31->unk0 = (s16) obj->work[0];
    temp_r31->unk2 = (s16) GWPlayerCfg[temp_r31->unk0].character;
    temp_r31->unk4 = (s16) GWPlayerCfg[temp_r31->unk0].pad_idx;
    temp_r31->unkA = (s16) GWPlayerCfg[temp_r31->unk0].iscom;
    temp_r31->unkC = (s16) GWPlayerCfg[temp_r31->unk0].diff;
    *obj->model = CharModelCreate(temp_r31->unk2, 8);
    var_r30 = 0;
loop_2:
    if (var_r30 < 8) {
        obj->motion[var_r30] = Mp5CharMotionCreateData(temp_r31->unk2, (u32) lbl_1_data_118[Mp5CharNo(temp_r31->unk2)][var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r30 += 1;
        goto loop_2;
    }
    CharMotionSet(temp_r31->unk2, obj->motion[0]);
    Hu3DModelAttrSet(*obj->model, 0x40000001U);
    Hu3DModelLayerSet(*obj->model, 3);
    Hu3DModelCameraSet(*obj->model, (u16) lbl_1_rodata_10[temp_r31->unk0]);
    Hu3DModelShadowSet(*obj->model);
    CharEffectLayerSet(4);
    CharModelStepFxSet(temp_r31->unk2, 1);
    CharMotionDataClose(temp_r31->unk2);
    var_r26 = lbl_1_data_1094[temp_r27->unk2[temp_r31->unkE]];
    var_r30_2 = 0;
loop_8:
    if (var_r30_2 < 5) {
        var_r29 = 0;
loop_6:
        if (var_r29 < 5) {
            temp_r4 = *var_r26;
            var_r26++;
            temp_r31->unk10[(var_r30_2) * 5 + (var_r29)].unk24 = temp_r4;
            temp_r31->unk10[(var_r30_2) * 5 + (var_r29)].unk18.x = (150.0f * (f32) var_r29) - 300.0f;
            temp_r31->unk10[(var_r30_2) * 5 + (var_r29)].unk18.y = 0.0f;
            temp_r31->unk10[(var_r30_2) * 5 + (var_r29)].unk18.z = (150.0f * (f32) var_r30_2) - 300.0f;
            var_r29 += 1;
            goto loop_6;
        }
        var_r30_2 += 1;
        goto loop_8;
    }
    var_r30_3 = 0;
loop_11:
    if (var_r30_3 < 5) {
        temp_r31->unk10[0 * 5 + var_r30_3].unkC = 0;
        temp_r31->unk10[0 * 5 + var_r30_3].unk8 = &temp_r31->unk10[1 * 5 + var_r30_3];
        var_r30_3 += 1;
        goto loop_11;
    }
    var_r30_4 = 0;
loop_14:
    if (var_r30_4 < 5) {
        temp_r31->unk10[4 * 5 + var_r30_4].unk8 = 0;
        temp_r31->unk10[4 * 5 + var_r30_4].unkC = &temp_r31->unk10[3 * 5 + var_r30_4];
        var_r30_4 += 1;
        goto loop_14;
    }
    var_r30_5 = 0;
loop_17:
    if (var_r30_5 < 5) {
        temp_r31->unk10[(var_r30_5) * 5 + 0].unk4 = 0;
        temp_r31->unk10[(var_r30_5) * 5 + 0].unk0 = &temp_r31->unk10[(var_r30_5) * 5 + 1];
        var_r30_5 += 1;
        goto loop_17;
    }
    var_r30_6 = 0;
loop_20:
    if (var_r30_6 < 5) {
        temp_r31->unk10[(var_r30_6) * 5 + 4].unk0 = 0;
        temp_r31->unk10[(var_r30_6) * 5 + 4].unk4 = &temp_r31->unk10[(var_r30_6) * 5 + 3];
        var_r30_6 += 1;
        goto loop_20;
    }
    var_r30_7 = 1;
loop_26:
    if (var_r30_7 < 4) {
        var_r29_2 = 0;
loop_24:
        if (var_r29_2 < 5) {
            temp_r31->unk10[(var_r30_7) * 5 + (var_r29_2)].unkC = &temp_r31->unk10[(var_r30_7 - 1) * 5 + (var_r29_2)];
            temp_r31->unk10[(var_r30_7) * 5 + (var_r29_2)].unk8 = &temp_r31->unk10[(var_r30_7 + 1) * 5 + (var_r29_2)];
            var_r29_2 += 1;
            goto loop_24;
        }
        var_r30_7 += 1;
        goto loop_26;
    }
    var_r30_8 = 0;
loop_32:
    if (var_r30_8 < 5) {
        var_r29_3 = 1;
loop_30:
        if (var_r29_3 < 4) {
            temp_r31->unk10[(var_r30_8) * 5 + (var_r29_3)].unk4 = &temp_r31->unk10[(var_r30_8) * 5 + (var_r29_3 - 1)];
            temp_r31->unk10[(var_r30_8) * 5 + (var_r29_3)].unk0 = &temp_r31->unk10[(var_r30_8) * 5 + (var_r29_3 + 1)];
            var_r29_3 += 1;
            goto loop_30;
        }
        var_r30_8 += 1;
        goto loop_32;
    }
    temp_r31->unk10[2].unkC = (void *) (&temp_r31->unk424);
    temp_r31->unk10[22].unk8 = (void *) (&temp_r31->unk3FC);
    temp_r31->unk3FC.unkC = &temp_r31->unk10[22];
    temp_r31->unk3FC.unk0 = 0;
    temp_r31->unk3FC.unk4 = 0;
    temp_r31->unk3FC.unk8 = 0;
    temp_r31->unk3FC.unk24 = 3;
    temp_r31->unk3FC.unk18.x = 0.0f;
    temp_r31->unk3FC.unk18.y = 25.0f;
    temp_r31->unk3FC.unk18.z = 450.0f;
    temp_r31->unk424.unkC = 0;
    temp_r31->unk424.unk0 = 0;
    temp_r31->unk424.unk4 = 0;
    temp_r31->unk424.unk8 = &temp_r31->unk10[2];
    temp_r31->unk424.unk24 = 4;
    temp_r31->unk424.unk18.x = 0.0f;
    temp_r31->unk424.unk18.y = 25.0f;
    temp_r31->unk424.unk18.z = -450.0f;
    temp_r31->unk3F8 = (void *) (&temp_r31->unk3FC);
    if ((s16) temp_r31->unk0 == 0) {
        temp_r31->unk44C.x = sp10[4];
        temp_r31->unk44C.y = sp10[5];
        temp_r31->unk44C.z = sp10[6];
        temp_r31->unk458.x = 0.0f;
        temp_r31->unk458.y = 90.0f;
        temp_r31->unk458.z = 0.0f;
        CharMotionSet(temp_r31->unk2, obj->motion[1]);
    } else {
        temp_r4_2 = temp_r31->unk3F8;
        temp_r31->unk44C.x = (f32) temp_r4_2->unk18.x;
        temp_r31->unk44C.y = (f32) temp_r4_2->unk18.y;
        temp_r31->unk44C.z = (f32) temp_r4_2->unk18.z;
        temp_r31->unk458.x = 0.0f;
        temp_r31->unk458.y = 180.0f;
        temp_r31->unk458.z = 0.0f;
    }
    omSetTra(obj, temp_r31->unk44C.x, temp_r31->unk44C.y, temp_r31->unk44C.z);
    omSetRot(obj, temp_r31->unk458.x, temp_r31->unk458.y, temp_r31->unk458.z);
    temp_r31->unk482 = 0;
    temp_r31->unk484 = 0xF;
    temp_r31->unk486 = 5;
    temp_r31->unk480 = 0;
    temp_r31->unk47C = 0;
    temp_r31->unk47E = 0;
    temp_r4_3 = temp_r31->unk3F8;
    temp_r31->unk464.x = (f32) temp_r4_3->unk18.x;
    temp_r31->unk464.y = (f32) temp_r4_3->unk18.y;
    temp_r31->unk464.z = (f32) temp_r4_3->unk18.z;
    temp_r5 = temp_r31->unk3F8;
    temp_r31->unk470.x = (f32) temp_r5->unk18.x;
    temp_r31->unk470.y = (f32) temp_r5->unk18.y;
    temp_r31->unk470.z = (f32) temp_r5->unk18.z;
    temp_r31->unk680 = 0;
    temp_r31->unk682 = 0;
    temp_r31->unk684 = (void *) (&temp_r27->unk2F4[temp_r31->unk0]);
    temp_r31->unk688 = 0;
    fn_1_73B0((M515Player *) temp_r31, 0);
    fn_1_73B0((M515Player *) temp_r31, 1);
    fn_1_73B0((M515Player *) temp_r31, 2);
    fn_1_7768((M515Player *) temp_r31, 0);
    fn_1_77F0((M515Player *) temp_r31, 1);
    fn_1_77F0((M515Player *) temp_r31, 2);
    fn_1_69B8((M515Player *) temp_r31, (M515Main *) temp_r27);
    fn_1_6FE8((M515Player *) temp_r31);
    var_r30_9 = 0;
loop_43:
    if (var_r30_9 < 5) {
        var_r29_4 = 0;
loop_41:
        if (var_r29_4 < 5) {
            if ((u16) temp_r31->unk10[(var_r30_9) * 5 + (var_r29_4)].unk24 == 2) {
                temp_r31->unk10[(var_r30_9) * 5 + (var_r29_4)].unk14->unk24 = (s16) ((rand8() / 86) + 1);
                Hu3DModelRotSet(temp_r31->unk10[(var_r30_9) * 5 + (var_r29_4)].unk14->unk0, 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(temp_r31->unk10[(var_r30_9) * 5 + (var_r29_4)].unk14->unk0, 0.0f, sp10[temp_r31->unk10[(var_r30_9) * 5 + (var_r29_4)].unk14->unk24], 0.0f);
            }
            var_r29_4 += 1;
            goto loop_41;
        }
        var_r30_9 += 1;
        goto loop_43;
    }
    temp_r31->unk68C = obj;
    fn_1_E274(&temp_r31->unk690, 0, temp_r31->unkC);
    CharModelVoicePanSet(temp_r31->unk2, (s16) sp8[temp_r31->unk0]);
    obj->func = fn_1_2684;
}

void fn_1_2684(omObjData *obj) {
    s16 temp_r0;
    s32 temp_r26;
    s32 temp_r27;
    s32 var_r28;
    M515Main *temp_r29;
    M515Player *temp_r31;

    temp_r29 = lbl_1_bss_4->data;
    temp_r31 = obj->data;
    fn_1_E548((M515Player *) temp_r31);
    if ((s16) temp_r29->unk1D4 != 0) {
        if ((s16) temp_r31->unk482 == 4) {
            temp_r31->unk682 = 0;
            if (fn_1_7878((M515Player *) temp_r31) != 0) {
                temp_r31->unk482 = 0;
            }
            fn_1_5FD0((M515Player *) temp_r31);
            fn_1_611C((M515Player *) temp_r31);
            goto block_32;
        }
        if ((s16) temp_r31->unk482 == 3) {
            if (fn_1_6324((M515Player *) temp_r31, (M515Main *) temp_r29) != 0) {
                temp_r31->unk482 = 0;
            }
            goto block_32;
        }
        if ((s16) temp_r31->unkA != 0) {
            temp_r31->unk680 = fn_1_DD18((M515Player *) temp_r31);
        } else {
            temp_r31->unk680 = fn_1_7924((M515Player *) temp_r31);
        }
        if ((u16) temp_r31->unk680 == 0x20) {
            temp_r31->unk682 = 0;
            temp_r31->unk482 = 4;
            temp_r31->unk688 = fn_1_D928;
            return;
        }
        temp_r27 = fn_1_5FD0((M515Player *) temp_r31);
        temp_r26 = fn_1_611C((M515Player *) temp_r31);
        fn_1_6980((M515Player *) temp_r31);
        if ((temp_r27 != 0) && (temp_r26 != 0) && ((temp_r31->unk482 = fn_1_66D0((M515Player *) temp_r31), (((s16) temp_r31->unk482 == 0) != 0)) || ((s16) temp_r31->unk482 == 2)) && ((s16) temp_r31->unk682 > 0)) {
            temp_r31->unk482 = 3;
            fn_1_6318((M515Player *) temp_r31);
            temp_r31->unk682 = 0;
        }
        temp_r0 = temp_r31->unk482;
        switch (temp_r0) {                          /* irregular */
        case 0:
            if (((s16) obj->motion[0] != Hu3DMotionIDGet(*obj->model)) && ((s16) obj->motion[0] != Hu3DMotionShiftIDGet(*obj->model))) {
                Hu3DMotionShiftSet(*obj->model, obj->motion[0], 0.0f, 5.0f, 0x40000001U);
            }
            break;
        default:
            if (((s16) obj->motion[2] != Hu3DMotionIDGet(*obj->model)) && ((s16) obj->motion[2] != Hu3DMotionShiftIDGet(*obj->model))) {
                Hu3DMotionShiftSet(*obj->model, obj->motion[2], 0.0f, 5.0f, 0x40000001U);
            }
            break;
        case 3:
            Hu3DMotionShiftSet(*obj->model, obj->motion[3], 0.0f, 5.0f, 0x40000001U);
            break;
        }
        fn_1_81A8(temp_r31->unk684->unk4, (M515Player *) temp_r31);
block_32:
        if ((s16) temp_r31->unk482 != 5) {
            omSetTra(obj, temp_r31->unk44C.x, temp_r31->unk44C.y, temp_r31->unk44C.z);
            omSetRot(obj, temp_r31->unk458.x, temp_r31->unk458.y, temp_r31->unk458.z);
        }
        var_r28 = 0;
loop_36:
        if (var_r28 < (s16) temp_r31->unk5E8) {
            fn_1_7BE8(&temp_r31->unk488[var_r28], (M515Main *) temp_r29);
            var_r28 += 1;
            goto loop_36;
        }
    }
}


void fn_1_29D0(omObjData *obj) {
    s16 var_r31;
    s32 var_r29;
    s32 var_r31_2;
    M515Main *temp_r30;

    temp_r30 = obj->data;
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        fn_1_7E5C(&temp_r30->unk234[var_r31], var_r31);
        fn_1_9804(&temp_r30->unk2F4[var_r31], &temp_r30->unk234[var_r31], (s32) var_r31);
        var_r31 += 1;
        goto loop_2;
    }
    fn_1_5C40((M515Main *) temp_r30);
    var_r31_2 = 0;
loop_8:
    if (var_r31_2 < 4) {
        var_r29 = 0;
loop_6:
        if (var_r29 < 3) {
            temp_r30->unk1DC[var_r31_2 * 3 + var_r29] = 0;
            var_r29 += 1;
            goto loop_6;
        }
        var_r31_2 += 1;
        goto loop_8;
    }
    Hu3DLayerHookSet(1, fn_1_CC20);
    obj->func = fn_1_2AC0;
}

void fn_1_2AC0(omObjData *obj) {
    Vec sp8;
    s32 var_r30;
    M515Main *temp_r31;
    M515Player *temp_r4;

    temp_r31 = obj->data;
    fn_1_5DB0((M515Main *) temp_r31);
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        fn_1_7EE0(&temp_r31->unk234[var_r30]);
        temp_r4 = temp_r31->unk224[var_r30];
        sp8.x = temp_r4->unk44C.x;
        sp8.y = temp_r4->unk44C.y;
        sp8.z = temp_r4->unk44C.z;
        fn_1_C958(var_r30, &sp8, temp_r31->unk1F4);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_2B6C(M515Main *arg0) {
    s32 sp14;
    s32 sp10;
    f32 sp8;
    s32 var_r31;
    u32 temp_r3;

    arg0->unk0 = 0;
    var_r31 = 0;
loop_2:
    if (var_r31 < 4) {
        sp14 = (s32) (((u32) var_r31 >> 0x1FU) + var_r31) >> 1;
        temp_r3 = (u32) var_r31 >> 0x1FU;
        sp10 = ((var_r31 & 1) ^ temp_r3) - temp_r3;
        Hu3DCameraCreate((s32) lbl_1_rodata_10[var_r31]);
        Hu3DCameraPerspectiveSet((s32) lbl_1_rodata_10[var_r31], 15.0f, 20.0f, 12000.0f, 1.17f);
        sp8 = 0.0f;
        Hu3DCameraPosSet((s32) lbl_1_rodata_10[var_r31], 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, sp8);
        var_r31 += 1;
        goto loop_2;
    }
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[0], 8.0f, 20.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[1], 312.0f, 20.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[2], 8.0f, 220.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[3], 312.0f, 220.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[0], 0U, 0U, 0x13FU, 0xEFU);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[1], 0x141U, 0U, 0x13FU, 0xEFU);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[2], 0U, 0xF1U, 0x13FU, 0xEFU);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[3], 0x141U, 0xF1U, 0x13FU, 0xEFU);
    fn_1_9828(&arg0->unk334);
    fn_1_9958(&arg0->unk334);
}

void fn_1_2EB4(void) {
    Hu3DGLightInfinitytSet(Hu3DGLightCreate(0.0f, 4800.0f, 3600.0f, 0.0f, -1.0f, -1.0f, 0xFFU, 0xFFU, 0xFFU));
}

void fn_1_2F3C(M515Main *arg0) {
    s16 temp_r29;
    s16 temp_r29_2;
    s16 temp_r29_3;
    s16 temp_r29_4;
    s16 var_r30_4;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_5;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;

    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        arg0->unk2[var_r30] = (s16) (rand8() / 26);
        var_r30 += 1;
        goto loop_2;
    }
    arg0->unk1D8 = 0;
    arg0->unkDC = -1;
    arg0->unkDE = -1;
    var_r30_2 = 0;
loop_5:
    if (var_r30_2 < 0x11) {
        arg0->unk10C[var_r30_2] = -1;
        var_r30_2 += 1;
        goto loop_5;
    }
    var_r30_3 = 0;
loop_8:
    if (var_r30_3 < 8) {
        arg0->unkE0[var_r30_3] = -1;
        var_r30_3 += 1;
        goto loop_8;
    }
    arg0->unk21C = 0;
    arg0->unk21E = 0;
    arg0->unk220 = 0;
    var_r30_4 = 0;
loop_11:
    if (var_r30_4 < 3) {
        arg0->unk1F8[var_r30_4] = var_r30_4;
        arg0->unk204[var_r30_4] = var_r30_4;
        arg0->unk210[var_r30_4] = var_r30_4;
        var_r30_4 += 1;
        goto loop_11;
    }
loop_14:
    if (var_r30_4 < 6) {
        arg0->unk1F8[var_r30_4] = 0;
        arg0->unk204[var_r30_4] = 0;
        arg0->unk210[var_r30_4] = var_r30_4;
        var_r30_4 += 1;
        goto loop_14;
    }
    var_r30_5 = 2;
loop_17:
    if (var_r30_5 < 2) {
        temp_r29 = (s16) (rand8() / 86);
        temp_r0 = rand8() / 86;
        M2C_SWAP(arg0->unk1F8[temp_r29], arg0->unk1F8[(s16) temp_r0]); /* m2c lost the temporary */
        temp_r29_2 = (s16) (rand8() / 86);
        temp_r0_2 = rand8() / 86;
        M2C_SWAP(arg0->unk204[temp_r29_2], arg0->unk204[(s16) temp_r0_2]); /* m2c lost the temporary */
        temp_r29_3 = (s16) (rand8() / 43);
        temp_r0_3 = rand8() / 43;
        M2C_SWAP(arg0->unk210[temp_r29_3], arg0->unk210[(s16) temp_r0_3]); /* m2c lost the temporary */
        var_r30_5 += 1;
        goto loop_17;
    }
    temp_r29_4 = (s16) (rand8() / 43);
    temp_r0_4 = rand8() / 43;
    M2C_SWAP(arg0->unk210[temp_r29_4], arg0->unk210[(s16) temp_r0_4]); /* m2c lost the temporary */
    arg0->unk1D4 = 0;
}

void fn_1_32C4(M515Main *arg0) {
    f32 spv[0x170];
    Vec *sp190;
    Vec *sp18C;
    Vec *sp188;
    Vec *sp184;
    Vec *sp180;
    Vec *sp17C;
    Vec *sp178;
    Vec *sp174;
    Vec *sp170;
    Vec *sp16C;
    Vec *sp168;
    Vec *sp164;
    Vec *sp160;
    Vec *sp15C;
    Vec *sp158;
    Vec *sp154;
    Vec *sp150;
    Vec *sp14C;
    Vec *sp148;
    Vec *sp144;
    Vec *sp140;
    Vec *sp13C;
    Vec *sp138;
    Vec *sp134;
    Vec *sp130;
    Vec *sp12C;
    Vec *sp128;
    Vec *sp124;
    Vec *sp120;
    Vec *sp11C;
    Vec *sp118;
    Vec *sp114;
    Vec *sp110;
    Vec *sp10C;
    Vec *sp108;
    Vec *sp104;
    Vec *sp100;
    Vec *spFC;
    Vec *spF8;
    Vec *spF4;
    Vec *spF0;
    Vec *spEC;
    Vec *spE8;
    Vec *spE4;
    Vec *spE0;
    Vec *spDC;
    Vec *spD8;
    Vec *spD4;
    Vec *spD0;
    Vec *spCC;
    Vec *spC8;
    Vec *spC4;
    Vec *spC0;
    Vec *spBC;
    Vec *spB8;
    Vec *spB4;
    Vec *spB0;
    Vec *spAC;
    Vec *spA8;
    Vec *spA4;
    Vec *spA0;
    Vec *sp9C;
    Vec *sp98;
    Vec *sp94;
    Vec *sp90;
    Vec *sp8C;
    Vec *sp88;
    Vec *sp84;
    Vec *sp80;
    Vec *sp7C;
    Vec *sp78;
    Vec *sp74;
    Vec *sp70;
    Vec *sp6C;
    Vec *sp68;
    Vec *sp64;
    Vec *sp60;
    Vec *sp5C;
    Vec *sp58;
    Vec *sp54;
    Vec *sp50;
    Vec *sp4C;
    Vec *sp48;
    Vec *sp44;
    Vec *sp40;
    Vec *sp3C;
    Vec *sp38;
    Vec *sp34;
    Vec *sp30;
    Vec *sp2C;
    Vec *sp28;
    Vec *sp24;
    Vec *sp20;
    Vec *sp1C;
    Vec *sp18;
    Vec *sp14;
    Vec *sp10;
    Vec *spC;
    Vec *sp8;
    s32 var_r30;

    spv[351] = lbl_1_rodata_FC.x;
    spv[352] = lbl_1_rodata_FC.y;
    spv[353] = lbl_1_rodata_FC.z;
    spv[348] = lbl_1_rodata_108.x;
    spv[349] = lbl_1_rodata_108.y;
    spv[350] = lbl_1_rodata_108.z;
    spv[345] = lbl_1_rodata_114.x;
    spv[346] = lbl_1_rodata_114.y;
    spv[347] = lbl_1_rodata_114.z;
    spv[342] = lbl_1_rodata_120.x;
    spv[343] = lbl_1_rodata_120.y;
    spv[344] = lbl_1_rodata_120.z;
    spv[339] = lbl_1_rodata_12C.x;
    spv[340] = lbl_1_rodata_12C.y;
    spv[341] = lbl_1_rodata_12C.z;
    spv[336] = lbl_1_rodata_138.x;
    spv[337] = lbl_1_rodata_138.y;
    spv[338] = lbl_1_rodata_138.z;
    arg0->unk8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[330] = spv[348];
    spv[331] = spv[349];
    spv[332] = spv[350];
    spv[333] = spv[351];
    spv[334] = spv[352];
    spv[335] = spv[353];
    fn_1_5E88(arg0->unk8, (Vec *) &spv[333], (Vec *) &spv[330], 0, (u16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DModelAttrReset(arg0->unk8, 1U);
    Hu3DModelShadowMapSet(arg0->unk8);
    arg0->unkA = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[324] = spv[348];
    spv[325] = spv[349];
    spv[326] = spv[350];
    spv[327] = spv[351];
    spv[328] = spv[352];
    spv[329] = spv[353];
    fn_1_5E88(arg0->unkA, (Vec *) &spv[327], (Vec *) &spv[324], 0, (u16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DModelAttrReset(arg0->unkA, 1U);
    arg0->unkC = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[318] = spv[348];
    spv[319] = spv[349];
    spv[320] = spv[350];
    spv[321] = spv[336];
    spv[322] = spv[337];
    spv[323] = spv[338];
    fn_1_5E88(arg0->unkC, (Vec *) &spv[321], (Vec *) &spv[318], 0, (u16) lbl_1_rodata_10[0]);
    Hu3DModelAttrReset(arg0->unkC, 0x40000002U);
    Hu3DModelAttrReset(arg0->unkC, 1U);
    Hu3DMotionSpeedSet(arg0->unkC, 0.7f);
    arg0->unkD6 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x13], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[312] = spv[348];
    spv[313] = spv[349];
    spv[314] = spv[350];
    spv[315] = spv[351];
    spv[316] = spv[352];
    spv[317] = spv[353];
    fn_1_5E88(arg0->unkD6, (Vec *) &spv[315], (Vec *) &spv[312], 0, (u16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    arg0->unkD8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x14], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[306] = spv[348];
    spv[307] = spv[349];
    spv[308] = spv[350];
    spv[309] = spv[351];
    spv[310] = spv[352];
    spv[311] = spv[353];
    fn_1_5E88(arg0->unkD8, (Vec *) &spv[309], (Vec *) &spv[306], 0, (u16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DModelShadowMapSet(arg0->unkD8);
    arg0->unkDA = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[300] = spv[348];
    spv[301] = spv[349];
    spv[302] = spv[350];
    spv[303] = spv[351];
    spv[304] = spv[352];
    spv[305] = spv[353];
    fn_1_5E88(arg0->unkDA, (Vec *) &spv[303], (Vec *) &spv[300], 0, (u16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DModelShadowSet(arg0->unkDA);
    arg0->unkE[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[294] = spv[348];
    spv[295] = spv[349];
    spv[296] = spv[350];
    spv[297] = spv[351];
    spv[298] = spv[352];
    spv[299] = spv[353];
    sp190 = (Vec *) &spv[297];
    fn_1_5E88(arg0->unkE[0], (Vec *) sp190, (Vec *) &spv[294], 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkF0 = Hu3DJointMotion(arg0->unkE[0], HuDataSelHeapReadNum(lbl_1_data_3C8[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unkE[0], arg0->unkF0);
    arg0->unk16[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[288] = spv[348];
    spv[289] = spv[349];
    spv[290] = spv[350];
    sp18C = (Vec *) &spv[288];
    spv[291] = spv[351];
    spv[292] = spv[352];
    spv[293] = spv[353];
    sp188 = (Vec *) &spv[291];
    fn_1_5E88(arg0->unk16[0], (Vec *) sp188, (Vec *) sp18C, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkF2 = Hu3DJointMotion(arg0->unk16[0], HuDataSelHeapReadNum(lbl_1_data_3C8[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk16[0], arg0->unkF2);
    arg0->unk1E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[282] = spv[348];
    spv[283] = spv[349];
    spv[284] = spv[350];
    sp184 = (Vec *) &spv[282];
    spv[285] = spv[351];
    spv[286] = spv[352];
    spv[287] = spv[353];
    sp180 = (Vec *) &spv[285];
    fn_1_5E88(arg0->unk1E[0], (Vec *) sp180, (Vec *) sp184, 2, (u16) lbl_1_rodata_10[0]);
    arg0->unk26[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[276] = spv[348];
    spv[277] = spv[349];
    spv[278] = spv[350];
    sp17C = (Vec *) &spv[276];
    spv[279] = spv[351];
    spv[280] = spv[352];
    spv[281] = spv[353];
    sp178 = (Vec *) &spv[279];
    fn_1_5E88(arg0->unk26[0], (Vec *) sp178, (Vec *) sp17C, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkF4 = Hu3DJointMotion(arg0->unk26[0], HuDataSelHeapReadNum(lbl_1_data_3C8[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk26[0], arg0->unkF4);
    arg0->unk2E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[270] = spv[345];
    spv[271] = spv[346];
    spv[272] = spv[347];
    sp174 = (Vec *) &spv[270];
    spv[273] = spv[351];
    spv[274] = spv[352];
    spv[275] = spv[353];
    sp170 = (Vec *) &spv[273];
    fn_1_5E88(arg0->unk2E[0], (Vec *) sp170, (Vec *) sp174, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkF6 = Hu3DJointMotion(arg0->unk2E[0], HuDataSelHeapReadNum(lbl_1_data_3C8[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk2E[0], arg0->unkF6);
    arg0->unk36[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[264] = spv[345];
    spv[265] = spv[346];
    spv[266] = spv[347];
    sp16C = (Vec *) &spv[264];
    spv[267] = spv[351];
    spv[268] = spv[352];
    spv[269] = spv[353];
    sp168 = (Vec *) &spv[267];
    fn_1_5E88(arg0->unk36[0], (Vec *) sp168, (Vec *) sp16C, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkF8 = Hu3DJointMotion(arg0->unk36[0], HuDataSelHeapReadNum(lbl_1_data_3C8[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk36[0], arg0->unkF8);
    arg0->unk3E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[258] = spv[345];
    spv[259] = spv[346];
    spv[260] = spv[347];
    sp164 = (Vec *) &spv[258];
    spv[261] = spv[351];
    spv[262] = spv[352];
    spv[263] = spv[353];
    sp160 = (Vec *) &spv[261];
    fn_1_5E88(arg0->unk3E[0], (Vec *) sp160, (Vec *) sp164, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkFA = Hu3DJointMotion(arg0->unk3E[0], HuDataSelHeapReadNum(lbl_1_data_3C8[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk3E[0], arg0->unkFA);
    arg0->unk46[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[252] = spv[348];
    spv[253] = spv[349];
    spv[254] = spv[350];
    sp15C = (Vec *) &spv[252];
    spv[255] = spv[351];
    spv[256] = spv[352];
    spv[257] = spv[353];
    sp158 = (Vec *) &spv[255];
    fn_1_5E88(arg0->unk46[0], (Vec *) sp158, (Vec *) sp15C, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkFC = Hu3DJointMotion(arg0->unk46[0], HuDataSelHeapReadNum(lbl_1_data_3C8[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk46[0], arg0->unkFC);
    arg0->unk4E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[246] = spv[348];
    spv[247] = spv[349];
    spv[248] = spv[350];
    sp154 = (Vec *) &spv[246];
    spv[249] = spv[351];
    spv[250] = spv[352];
    spv[251] = spv[353];
    sp150 = (Vec *) &spv[249];
    fn_1_5E88(arg0->unk4E[0], (Vec *) sp150, (Vec *) sp154, 2, (u16) lbl_1_rodata_10[0]);
    arg0->unk56[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[240] = spv[348];
    spv[241] = spv[349];
    spv[242] = spv[350];
    sp14C = (Vec *) &spv[240];
    spv[243] = spv[351];
    spv[244] = spv[352];
    spv[245] = spv[353];
    sp148 = (Vec *) &spv[243];
    fn_1_5E88(arg0->unk56[0], (Vec *) sp148, (Vec *) sp14C, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unkFE = Hu3DJointMotion(arg0->unk56[0], HuDataSelHeapReadNum(lbl_1_data_3C8[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk56[0], arg0->unkFE);
    arg0->unk5E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[234] = spv[345];
    spv[235] = spv[346];
    spv[236] = spv[347];
    sp144 = (Vec *) &spv[234];
    spv[237] = spv[351];
    spv[238] = spv[352];
    spv[239] = spv[353];
    sp140 = (Vec *) &spv[237];
    fn_1_5E88(arg0->unk5E[0], (Vec *) sp140, (Vec *) sp144, 2, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unk5E[0]);
    arg0->unk5E[1] = Hu3DModelLink(arg0->unk5E[0]);
    spv[228] = spv[348];
    spv[229] = spv[349];
    spv[230] = spv[350];
    sp13C = (Vec *) &spv[228];
    spv[231] = spv[342];
    spv[232] = spv[343];
    spv[233] = spv[344];
    sp138 = (Vec *) &spv[231];
    fn_1_5E88(arg0->unk5E[1], (Vec *) sp138, (Vec *) sp13C, 2, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unk5E[1]);
    arg0->unk6E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xE], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[222] = spv[348];
    spv[223] = spv[349];
    spv[224] = spv[350];
    sp134 = (Vec *) &spv[222];
    spv[225] = spv[351];
    spv[226] = spv[352];
    spv[227] = spv[353];
    sp130 = (Vec *) &spv[225];
    fn_1_5E88(arg0->unk6E[0], (Vec *) sp130, (Vec *) sp134, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unk100 = Hu3DJointMotion(arg0->unk6E[0], HuDataSelHeapReadNum(lbl_1_data_3C8[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk6E[0], arg0->unk100);
    arg0->unk76[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0xF], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[216] = spv[348];
    spv[217] = spv[349];
    spv[218] = spv[350];
    sp12C = (Vec *) &spv[216];
    spv[219] = spv[351];
    spv[220] = spv[352];
    spv[221] = spv[353];
    sp128 = (Vec *) &spv[219];
    fn_1_5E88(arg0->unk76[0], (Vec *) sp128, (Vec *) sp12C, 5, (u16) lbl_1_rodata_10[0]);
    arg0->unk102 = Hu3DJointMotion(arg0->unk76[0], HuDataSelHeapReadNum(lbl_1_data_3C8[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unk76[0], arg0->unk102);
    arg0->unk76[1] = Hu3DModelLink(arg0->unk76[0]);
    spv[210] = spv[348];
    spv[211] = spv[349];
    spv[212] = spv[350];
    sp124 = (Vec *) &spv[210];
    spv[213] = spv[342];
    spv[214] = spv[343];
    spv[215] = spv[344];
    sp120 = (Vec *) &spv[213];
    fn_1_5E88(arg0->unk76[1], (Vec *) &spv[213], (Vec *) sp124, 5, (u16) lbl_1_rodata_10[0]);
    Hu3DMotionSet(arg0->unk76[1], arg0->unk102);
    arg0->unk76[2] = Hu3DModelLink(arg0->unk76[0]);
    spv[204] = spv[345];
    spv[205] = spv[346];
    spv[206] = spv[347];
    sp11C = (Vec *) &spv[204];
    spv[207] = spv[342];
    spv[208] = spv[343];
    spv[209] = spv[344];
    sp118 = (Vec *) &spv[207];
    fn_1_5E88(arg0->unk76[2], (Vec *) sp118, (Vec *) sp11C, 5, (u16) lbl_1_rodata_10[0]);
    Hu3DMotionSet(arg0->unk76[2], arg0->unk102);
    arg0->unk76[3] = Hu3DModelLink(arg0->unk76[0]);
    spv[198] = spv[345];
    spv[199] = spv[346];
    spv[200] = spv[347];
    sp114 = (Vec *) &spv[198];
    spv[201] = spv[339];
    spv[202] = spv[340];
    spv[203] = spv[341];
    sp110 = (Vec *) &spv[201];
    fn_1_5E88(arg0->unk76[3], (Vec *) sp110, (Vec *) sp114, 5, (u16) lbl_1_rodata_10[0]);
    Hu3DMotionSet(arg0->unk76[3], arg0->unk102);
    arg0->unk96[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x10], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[192] = spv[348];
    spv[193] = spv[349];
    spv[194] = spv[350];
    sp10C = (Vec *) &spv[192];
    spv[195] = spv[351];
    spv[196] = spv[352];
    spv[197] = spv[353];
    sp108 = (Vec *) &spv[195];
    fn_1_5E88(arg0->unk96[0], (Vec *) sp108, (Vec *) sp10C, 3, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unk96[0]);
    arg0->unk96[1] = Hu3DModelLink(arg0->unk96[0]);
    spv[186] = spv[345];
    spv[187] = spv[346];
    spv[188] = spv[347];
    sp104 = (Vec *) &spv[186];
    spv[189] = spv[342];
    spv[190] = spv[343];
    spv[191] = spv[344];
    sp100 = (Vec *) &spv[189];
    fn_1_5E88(arg0->unk96[1], (Vec *) sp100, (Vec *) sp104, 3, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unk96[1]);
    arg0->unkA6[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x11], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[180] = spv[348];
    spv[181] = spv[349];
    spv[182] = spv[350];
    spFC = (Vec *) &spv[180];
    spv[183] = spv[351];
    spv[184] = spv[352];
    spv[185] = spv[353];
    spF8 = (Vec *) &spv[183];
    fn_1_5E88(arg0->unkA6[0], (Vec *) spF8, (Vec *) spFC, 2, (u16) lbl_1_rodata_10[0]);
    arg0->unk104 = Hu3DJointMotion(arg0->unkA6[0], HuDataSelHeapReadNum(lbl_1_data_3C8[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unkA6[0], arg0->unk104);
    arg0->unkAE[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x12], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[174] = spv[348];
    spv[175] = spv[349];
    spv[176] = spv[350];
    spF4 = (Vec *) &spv[174];
    spv[177] = spv[351];
    spv[178] = spv[352];
    spv[179] = spv[353];
    spF0 = (Vec *) &spv[177];
    fn_1_5E88(arg0->unkAE[0], (Vec *) spF0, (Vec *) spF4, 6, (u16) lbl_1_rodata_10[0]);
    arg0->unk106 = Hu3DJointMotion(arg0->unkAE[0], HuDataSelHeapReadNum(lbl_1_data_3C8[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionSet(arg0->unkAE[0], arg0->unk106);
    arg0->unk108 = Hu3DJointMotion(arg0->unkAE[0], HuDataSelHeapReadNum(lbl_1_data_3C8[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
    arg0->unkB6[0 * 3 + 0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x17], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[168] = spv[348];
    spv[169] = spv[349];
    spv[170] = spv[350];
    spEC = (Vec *) &spv[168];
    spv[171] = spv[351];
    spv[172] = spv[352];
    spv[173] = spv[353];
    spE8 = (Vec *) &spv[171];
    fn_1_5E88(arg0->unkB6[0 * 3 + 0], (Vec *) spE8, (Vec *) spEC, 1, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unkB6[0 * 3 + 0]);
    arg0->unkB6[0 * 3 + 1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x18], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[162] = spv[345];
    spv[163] = spv[346];
    spv[164] = spv[347];
    spE4 = (Vec *) &spv[162];
    spv[165] = spv[342];
    spv[166] = spv[343];
    spv[167] = spv[344];
    spE0 = (Vec *) &spv[165];
    fn_1_5E88(arg0->unkB6[0 * 3 + 1], (Vec *) spE0, (Vec *) spE4, 1, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unkB6[0 * 3 + 1]);
    arg0->unkB6[0 * 3 + 2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x19], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[156] = spv[348];
    spv[157] = spv[349];
    spv[158] = spv[350];
    spDC = (Vec *) &spv[156];
    spv[159] = spv[339];
    spv[160] = spv[340];
    spv[161] = spv[341];
    spD8 = (Vec *) &spv[159];
    fn_1_5E88(arg0->unkB6[0 * 3 + 2], (Vec *) spD8, (Vec *) spDC, 1, (u16) lbl_1_rodata_10[0]);
    Hu3DModelShadowMapSet(arg0->unkB6[0 * 3 + 2]);
    arg0->unkCE[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
    spv[150] = spv[348];
    spv[151] = spv[349];
    spv[152] = spv[350];
    spD4 = (Vec *) &spv[150];
    spv[153] = spv[351];
    spv[154] = spv[352];
    spv[155] = spv[353];
    spD0 = (Vec *) &spv[153];
    fn_1_5F2C(arg0->unkCE[0], (Vec *) spD0, (Vec *) spD4, 7, (u16) lbl_1_rodata_10[0]);
    arg0->unk10A = Hu3DJointMotion(arg0->unkCE[0], HuDataSelHeapReadNum(lbl_1_data_3C8[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DMotionShapeSet(arg0->unkCE[0], arg0->unk10A);
    var_r30 = 1;
loop_2:
    if (var_r30 < 4) {
        arg0->unkE[var_r30] = Hu3DModelLink(arg0->unkE[0]);
        spv[144] = spv[348];
        spv[145] = spv[349];
        spv[146] = spv[350];
        spCC = (Vec *) &spv[144];
        spv[147] = spv[351];
        spv[148] = spv[352];
        spv[149] = spv[353];
        spC8 = (Vec *) &spv[147];
        fn_1_5E88(arg0->unkE[var_r30], (Vec *) spC8, (Vec *) spCC, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unkE[var_r30], arg0->unkF0);
        arg0->unk16[var_r30] = Hu3DModelLink(arg0->unk16[0]);
        spv[138] = spv[348];
        spv[139] = spv[349];
        spv[140] = spv[350];
        spC4 = (Vec *) &spv[138];
        spv[141] = spv[351];
        spv[142] = spv[352];
        spv[143] = spv[353];
        spC0 = (Vec *) &spv[141];
        fn_1_5E88(arg0->unk16[var_r30], (Vec *) spC0, (Vec *) spC4, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk16[var_r30], arg0->unkF2);
        arg0->unk1E[var_r30] = Hu3DModelLink(arg0->unk1E[0]);
        spv[132] = spv[348];
        spv[133] = spv[349];
        spv[134] = spv[350];
        spBC = (Vec *) &spv[132];
        spv[135] = spv[351];
        spv[136] = spv[352];
        spv[137] = spv[353];
        spB8 = (Vec *) &spv[135];
        fn_1_5E88(arg0->unk1E[var_r30], (Vec *) spB8, (Vec *) spBC, 2, (u16) lbl_1_rodata_10[var_r30]);
        arg0->unk26[var_r30] = Hu3DModelLink(arg0->unk26[0]);
        spv[126] = spv[348];
        spv[127] = spv[349];
        spv[128] = spv[350];
        spB4 = (Vec *) &spv[126];
        spv[129] = spv[351];
        spv[130] = spv[352];
        spv[131] = spv[353];
        spB0 = (Vec *) &spv[129];
        fn_1_5E88(arg0->unk26[var_r30], (Vec *) spB0, (Vec *) spB4, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk26[var_r30], arg0->unkF4);
        arg0->unk2E[var_r30] = Hu3DModelLink(arg0->unk2E[0]);
        spv[120] = spv[345];
        spv[121] = spv[346];
        spv[122] = spv[347];
        spAC = (Vec *) &spv[120];
        spv[123] = spv[351];
        spv[124] = spv[352];
        spv[125] = spv[353];
        spA8 = (Vec *) &spv[123];
        fn_1_5E88(arg0->unk2E[var_r30], (Vec *) spA8, (Vec *) spAC, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk2E[var_r30], arg0->unkF6);
        arg0->unk36[var_r30] = Hu3DModelLink(arg0->unk36[0]);
        spv[114] = spv[345];
        spv[115] = spv[346];
        spv[116] = spv[347];
        spA4 = (Vec *) &spv[114];
        spv[117] = spv[351];
        spv[118] = spv[352];
        spv[119] = spv[353];
        spA0 = (Vec *) &spv[117];
        fn_1_5E88(arg0->unk36[var_r30], (Vec *) spA0, (Vec *) spA4, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk36[var_r30], arg0->unkF8);
        arg0->unk3E[var_r30] = Hu3DModelLink(arg0->unk3E[0]);
        spv[108] = spv[345];
        spv[109] = spv[346];
        spv[110] = spv[347];
        sp9C = (Vec *) &spv[108];
        spv[111] = spv[351];
        spv[112] = spv[352];
        spv[113] = spv[353];
        sp98 = (Vec *) &spv[111];
        fn_1_5E88(arg0->unk3E[var_r30], (Vec *) sp98, (Vec *) sp9C, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk3E[var_r30], arg0->unkFA);
        arg0->unk46[var_r30] = Hu3DModelLink(arg0->unk46[0]);
        spv[102] = spv[348];
        spv[103] = spv[349];
        spv[104] = spv[350];
        sp94 = (Vec *) &spv[102];
        spv[105] = spv[351];
        spv[106] = spv[352];
        spv[107] = spv[353];
        sp90 = (Vec *) &spv[105];
        fn_1_5E88(arg0->unk46[var_r30], (Vec *) sp90, (Vec *) sp94, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk46[var_r30], arg0->unkFC);
        arg0->unk4E[var_r30] = Hu3DModelLink(arg0->unk4E[0]);
        spv[96] = spv[348];
        spv[97] = spv[349];
        spv[98] = spv[350];
        sp8C = (Vec *) &spv[96];
        spv[99] = spv[351];
        spv[100] = spv[352];
        spv[101] = spv[353];
        sp88 = (Vec *) &spv[99];
        fn_1_5E88(arg0->unk4E[var_r30], (Vec *) sp88, (Vec *) sp8C, 2, (u16) lbl_1_rodata_10[var_r30]);
        arg0->unk56[var_r30] = Hu3DModelLink(arg0->unk56[0]);
        spv[90] = spv[348];
        spv[91] = spv[349];
        spv[92] = spv[350];
        sp84 = (Vec *) &spv[90];
        spv[93] = spv[351];
        spv[94] = spv[352];
        spv[95] = spv[353];
        sp80 = (Vec *) &spv[93];
        fn_1_5E88(arg0->unk56[var_r30], (Vec *) sp80, (Vec *) sp84, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk56[var_r30], arg0->unkFE);
        arg0->unk5E[var_r30 * 2 + 0] = Hu3DModelLink(arg0->unk5E[0]);
        spv[84] = spv[345];
        spv[85] = spv[346];
        spv[86] = spv[347];
        sp7C = (Vec *) &spv[84];
        spv[87] = spv[351];
        spv[88] = spv[352];
        spv[89] = spv[353];
        sp78 = (Vec *) &spv[87];
        fn_1_5E88(arg0->unk5E[var_r30 * 2 + 0], (Vec *) sp78, (Vec *) sp7C, 2, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unk5E[var_r30 * 2 + 0]);
        arg0->unk5E[var_r30 * 2 + 1] = Hu3DModelLink(arg0->unk5E[0]);
        spv[78] = spv[348];
        spv[79] = spv[349];
        spv[80] = spv[350];
        sp74 = (Vec *) &spv[78];
        spv[81] = spv[342];
        spv[82] = spv[343];
        spv[83] = spv[344];
        sp70 = (Vec *) &spv[81];
        fn_1_5E88(arg0->unk5E[var_r30 * 2 + 1], (Vec *) sp70, (Vec *) sp74, 2, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unk5E[var_r30 * 2 + 1]);
        arg0->unk6E[var_r30] = Hu3DModelLink(arg0->unk6E[0]);
        spv[72] = spv[348];
        spv[73] = spv[349];
        spv[74] = spv[350];
        sp6C = (Vec *) &spv[72];
        spv[75] = spv[351];
        spv[76] = spv[352];
        spv[77] = spv[353];
        sp68 = (Vec *) &spv[75];
        fn_1_5E88(arg0->unk6E[var_r30], (Vec *) sp68, (Vec *) sp6C, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk6E[var_r30], arg0->unk100);
        arg0->unk76[var_r30 * 4 + 0] = Hu3DModelLink(arg0->unk76[0]);
        spv[66] = spv[348];
        spv[67] = spv[349];
        spv[68] = spv[350];
        sp64 = (Vec *) &spv[66];
        spv[69] = spv[351];
        spv[70] = spv[352];
        spv[71] = spv[353];
        sp60 = (Vec *) &spv[69];
        fn_1_5E88(arg0->unk76[var_r30 * 4 + 0], (Vec *) sp60, (Vec *) sp64, 5, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk76[var_r30 * 4 + 0], arg0->unk102);
        arg0->unk76[var_r30 * 4 + 1] = Hu3DModelLink(arg0->unk76[0]);
        spv[60] = spv[348];
        spv[61] = spv[349];
        spv[62] = spv[350];
        sp5C = (Vec *) &spv[60];
        spv[63] = spv[342];
        spv[64] = spv[343];
        spv[65] = spv[344];
        sp58 = (Vec *) &spv[63];
        fn_1_5E88(arg0->unk76[var_r30 * 4 + 1], (Vec *) sp58, (Vec *) sp5C, 5, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk76[var_r30 * 4 + 1], arg0->unk102);
        arg0->unk76[var_r30 * 4 + 2] = Hu3DModelLink(arg0->unk76[0]);
        spv[54] = spv[345];
        spv[55] = spv[346];
        spv[56] = spv[347];
        sp54 = (Vec *) &spv[54];
        spv[57] = spv[342];
        spv[58] = spv[343];
        spv[59] = spv[344];
        sp50 = (Vec *) &spv[57];
        fn_1_5E88(arg0->unk76[var_r30 * 4 + 2], (Vec *) sp50, (Vec *) sp54, 5, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk76[var_r30 * 4 + 2], arg0->unk102);
        arg0->unk76[var_r30 * 4 + 3] = Hu3DModelLink(arg0->unk76[0]);
        spv[48] = spv[345];
        spv[49] = spv[346];
        spv[50] = spv[347];
        sp4C = (Vec *) &spv[48];
        spv[51] = spv[339];
        spv[52] = spv[340];
        spv[53] = spv[341];
        sp48 = (Vec *) &spv[51];
        fn_1_5E88(arg0->unk76[var_r30 * 4 + 3], (Vec *) &spv[51], (Vec *) sp4C, 5, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unk76[var_r30 * 4 + 3], arg0->unk102);
        arg0->unk96[var_r30 * 2 + 0] = Hu3DModelLink(arg0->unk96[0]);
        spv[42] = spv[348];
        spv[43] = spv[349];
        spv[44] = spv[350];
        sp44 = (Vec *) &spv[42];
        spv[45] = spv[351];
        spv[46] = spv[352];
        spv[47] = spv[353];
        sp40 = (Vec *) &spv[45];
        fn_1_5E88(arg0->unk96[var_r30 * 2 + 0], (Vec *) &spv[45], (Vec *) sp44, 3, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unk96[var_r30 * 2 + 0]);
        arg0->unk96[var_r30 * 2 + 1] = Hu3DModelLink(arg0->unk96[0]);
        spv[36] = spv[345];
        spv[37] = spv[346];
        spv[38] = spv[347];
        sp3C = (Vec *) &spv[36];
        spv[39] = spv[342];
        spv[40] = spv[343];
        spv[41] = spv[344];
        sp38 = (Vec *) &spv[39];
        fn_1_5E88(arg0->unk96[var_r30 * 2 + 1], (Vec *) sp38, (Vec *) sp3C, 3, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unk96[var_r30 * 2 + 1]);
        arg0->unkA6[var_r30] = Hu3DModelLink(arg0->unkA6[0]);
        spv[30] = spv[348];
        spv[31] = spv[349];
        spv[32] = spv[350];
        sp34 = (Vec *) &spv[30];
        spv[33] = spv[351];
        spv[34] = spv[352];
        spv[35] = spv[353];
        sp30 = (Vec *) &spv[33];
        fn_1_5E88(arg0->unkA6[var_r30], (Vec *) &spv[33], (Vec *) sp34, 2, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unkA6[var_r30], arg0->unk104);
        arg0->unkAE[var_r30] = Hu3DModelLink(arg0->unkAE[0]);
        spv[24] = spv[348];
        spv[25] = spv[349];
        spv[26] = spv[350];
        sp2C = (Vec *) &spv[24];
        spv[27] = spv[351];
        spv[28] = spv[352];
        spv[29] = spv[353];
        sp28 = (Vec *) &spv[27];
        fn_1_5E88(arg0->unkAE[var_r30], (Vec *) sp28, (Vec *) sp2C, 6, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionSet(arg0->unkAE[var_r30], arg0->unk106);
        Hu3DMotionSet(arg0->unkAE[var_r30], arg0->unk108);
        arg0->unkCE[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_2B8[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
        spv[18] = spv[348];
        spv[19] = spv[349];
        spv[20] = spv[350];
        sp24 = (Vec *) &spv[18];
        spv[21] = spv[351];
        spv[22] = spv[352];
        spv[23] = spv[353];
        sp20 = (Vec *) &spv[21];
        fn_1_5F2C(arg0->unkCE[var_r30], (Vec *) sp20, (Vec *) sp24, 7, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DMotionShapeSet(arg0->unkCE[var_r30], arg0->unk10A);
        arg0->unkB6[var_r30 * 3 + 0] = Hu3DModelLink(arg0->unkB6[0]);
        spv[12] = spv[348];
        spv[13] = spv[349];
        spv[14] = spv[350];
        sp1C = (Vec *) &spv[12];
        spv[15] = spv[351];
        spv[16] = spv[352];
        spv[17] = spv[353];
        sp18 = (Vec *) &spv[15];
        fn_1_5E88(arg0->unkB6[var_r30 * 3 + 0], (Vec *) sp18, (Vec *) sp1C, 1, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unkB6[var_r30 * 3 + 0]);
        arg0->unkB6[var_r30 * 3 + 1] = Hu3DModelLink(arg0->unkB6[1]);
        spv[6] = spv[345];
        spv[7] = spv[346];
        spv[8] = spv[347];
        sp14 = (Vec *) &spv[6];
        spv[9] = spv[342];
        spv[10] = spv[343];
        spv[11] = spv[344];
        sp10 = (Vec *) &spv[9];
        fn_1_5E88(arg0->unkB6[var_r30 * 3 + 1], (Vec *) sp10, (Vec *) sp14, 1, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unkB6[var_r30 * 3 + 1]);
        arg0->unkB6[var_r30 * 3 + 2] = Hu3DModelLink(arg0->unkB6[2]);
        spv[0] = spv[348];
        spv[1] = spv[349];
        spv[2] = spv[350];
        spC = (Vec *) &spv[0];
        spv[3] = spv[339];
        spv[4] = spv[340];
        spv[5] = spv[341];
        sp8 = (Vec *) &spv[3];
        fn_1_5E88(arg0->unkB6[var_r30 * 3 + 2], (Vec *) sp8, (Vec *) spC, 1, (u16) lbl_1_rodata_10[var_r30]);
        Hu3DModelShadowMapSet(arg0->unkB6[var_r30 * 3 + 2]);
        var_r30 += 1;
        goto loop_2;
    }
    fn_1_CAF0(arg0, 0);
    fn_1_CB60(arg0, 1);
    fn_1_CB60(arg0, 2);
    fn_1_CB60(arg0, 3);
}

void fn_1_5C40(M515Main *arg0) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x77) {
        arg0->unk34C[var_r31].unkC = NULL;
        arg0->unk34C[var_r31].unk10 = &arg0->unk34C[var_r31 + 1];
        arg0->unk34C[var_r31].unk8 = NULL;
        var_r31 += 1;
        goto loop_2;
    }
    arg0->unk34C[var_r31].unkC = NULL;
    arg0->unk34C[var_r31].unk10 = NULL;
    arg0->unk34C[var_r31].unk8 = NULL;
    arg0->unk344 = NULL;
    arg0->unk348 = arg0->unk34C;
}



void fn_1_5DB0(M515Main *arg0) {
    M515Fx *temp_r28;
    M515Fx *var_r30;

    var_r30 = arg0->unk344;
loop_10:
    if (var_r30 != NULL) {
        temp_r28 = var_r30->unk10;
        if ((var_r30->unk8(var_r30) != 0) && (var_r30 != NULL)) {
            if ((M515Fx *) var_r30->unkC != NULL) {
                var_r30->unkC->unk10 = var_r30->unk10;
            } else {
                arg0->unk344 = var_r30->unk10;
            }
            if ((M515Fx *) var_r30->unk10 != NULL) {
                var_r30->unk10->unkC = var_r30->unkC;
            }
            var_r30->unkC = NULL;
            var_r30->unk10 = arg0->unk348;
            var_r30->unk8 = NULL;
            arg0->unk348 = var_r30;
        }
        var_r30 = temp_r28;
        goto loop_10;
    }
}

void fn_1_5E88(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit) {
    u16 spA;
    s16 sp8;

    sp8 = layer;
    spA = cameraBit;
    Hu3DModelAttrSet(mdl, 1U);
    Hu3DModelAttrSet(mdl, 0x40000002U);
    Hu3DModelLayerSet(mdl, sp8);
    Hu3DModelCameraSet(mdl, spA);
    Hu3DModelPosSet(mdl, pos->x, pos->y, pos->z);
    Hu3DModelRotSet(mdl, rot->x, rot->y, rot->z);
}

void fn_1_5F2C(s16 mdl, Vec *pos, Vec *rot, s16 layer, u16 cameraBit) {
    u16 spA;
    s16 sp8;

    sp8 = layer;
    spA = cameraBit;
    Hu3DModelAttrSet(mdl, 1U);
    Hu3DModelAttrSet(mdl, 0x40000080U);
    Hu3DModelLayerSet(mdl, sp8);
    Hu3DModelCameraSet(mdl, spA);
    Hu3DModelPosSet(mdl, pos->x, pos->y, pos->z);
    Hu3DModelRotSet(mdl, rot->x, rot->y, rot->z);
}

s32 fn_1_5FD0(M515Player *arg0) {
    f32 temp_f31;
    s32 var_r31;

    var_r31 = 0;
    arg0->unk484 += 1;
    if ((s16) arg0->unk484 >= 0xF) {
        arg0->unk484 = 0xF;
        arg0->unk464.x = arg0->unk470.x;
        arg0->unk464.y = arg0->unk470.y;
        arg0->unk464.z = arg0->unk470.z;
        var_r31 = 1;
    }
    temp_f31 = (f32) arg0->unk484 / 15.0f;
    arg0->unk44C.x = ((1.0f - temp_f31) * arg0->unk464.x) + (temp_f31 * arg0->unk470.x);
    arg0->unk44C.y = ((1.0f - temp_f31) * arg0->unk464.y) + (temp_f31 * arg0->unk470.y);
    arg0->unk44C.z = ((1.0f - temp_f31) * arg0->unk464.z) + (temp_f31 * arg0->unk470.z);
    return var_r31;
}


s32 fn_1_611C(M515Player *arg0) {
    f32 sp8[4];
    f32 temp_f31;
    s32 var_r31;

    var_r31 = 0;
    sp8[0] = lbl_1_rodata_148[0];
    sp8[1] = lbl_1_rodata_148[1];
    sp8[2] = lbl_1_rodata_148[2];
    sp8[3] = lbl_1_rodata_148[3];
    arg0->unk486 += 1;
    if ((s16) arg0->unk486 >= 5) {
        arg0->unk486 = 5;
        arg0->unk47C = arg0->unk47E;
        var_r31 = 1;
    }
    if ((((s16) arg0->unk47C == 2) && ((s16) arg0->unk47E == 3)) || (((s16) arg0->unk47C == 3) && ((s16) arg0->unk47E == 2))) {
        sp8[3] += 360.0f;
    }
    if ((s16) arg0->unkE == 1) {
        if ((((s16) arg0->unk47C == 0) && ((s16) arg0->unk47E == 3)) || (((s16) arg0->unk47C == 3) && ((s16) arg0->unk47E == 0))) {
            sp8[3] += 360.0f;
        }
    } else if ((((s16) arg0->unk47C == 2) && ((s16) arg0->unk47E == 1)) || (((s16) arg0->unk47C == 1) && ((s16) arg0->unk47E == 2))) {
        sp8[1] += 360.0f;
    }
    temp_f31 = (f32) arg0->unk486 / 5.0f;
    arg0->unk458.y = ((1.0f - temp_f31) * sp8[arg0->unk47C]) + (temp_f31 * sp8[arg0->unk47E]);
    return var_r31;
}


void fn_1_6318(M515Player *arg0) {
    arg0->unk480 = 0;
}

s32 fn_1_6324(M515Player *arg0, M515Main *arg1) {
    u16 sp10[20];
    u16 sp8[4];
    M515Node *var_r28;
    M515Node *var_r31;
    M515Obj *temp_r29;
    s16 temp_r0;
    s32 var_r27;

    var_r27 = 0;
    sp10[0] = lbl_1_rodata_15C[0];
    sp10[1] = lbl_1_rodata_15C[1];
    sp10[2] = lbl_1_rodata_15C[2];
    sp10[3] = lbl_1_rodata_15C[3];
    sp10[4] = lbl_1_rodata_164[0];
    sp10[5] = lbl_1_rodata_164[1];
    sp10[6] = lbl_1_rodata_164[2];
    sp10[7] = lbl_1_rodata_164[3];
    sp10[8] = lbl_1_rodata_164[4];
    sp10[9] = lbl_1_rodata_164[5];
    sp10[10] = lbl_1_rodata_164[6];
    sp10[11] = lbl_1_rodata_164[7];
    sp10[12] = lbl_1_rodata_164[8];
    sp10[13] = lbl_1_rodata_164[9];
    sp10[14] = lbl_1_rodata_164[0xA];
    sp10[15] = lbl_1_rodata_164[0xB];
    sp10[16] = lbl_1_rodata_164[0xC];
    sp10[17] = lbl_1_rodata_164[0xD];
    sp10[18] = lbl_1_rodata_164[0xE];
    sp10[19] = lbl_1_rodata_164[0xF];
    sp8[0] = lbl_1_rodata_184[0];
    sp8[1] = lbl_1_rodata_184[1];
    sp8[2] = lbl_1_rodata_184[2];
    sp8[3] = lbl_1_rodata_184[3];
    var_r31 = NULL;
    var_r28 = NULL;
    arg0->unk480 += 1;
    if ((s16) arg0->unk480 == 0xA) {
        temp_r0 = arg0->unk47C;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31 = arg0->unk3F8->unkC;
            if ((var_r31 != NULL) && ((M515Node *) var_r31->unkC != NULL)) {
                var_r28 = var_r31->unkC;
            }
            break;
        case 1:
            var_r31 = arg0->unk3F8->unk0;
            if ((var_r31 != NULL) && ((M515Node *) var_r31->unk0 != NULL)) {
                var_r28 = var_r31->unk0;
            }
            break;
        case 2:
            var_r31 = arg0->unk3F8->unk4;
            if ((var_r31 != NULL) && ((M515Node *) var_r31->unk4 != NULL)) {
                var_r28 = var_r31->unk4;
            }
            break;
        case 3:
            var_r31 = arg0->unk3F8->unk8;
            if ((var_r31 != NULL) && ((M515Node *) var_r31->unk8 != NULL)) {
                var_r28 = var_r31->unk8;
            }
            break;
        }
        if ((var_r31 != NULL) && ((u16) var_r31->unk24 == 2)) {
            if ((s32) (arg0->unk0 & 1) != 0) {
                HuAudFXPlayPan(0x6E2, (s16) sp8[arg0->unk0]);
            } else {
                HuAudFXPlayPan(0x6E1, (s16) sp8[arg0->unk0]);
            }
            omVibrate(arg0->unk0, 0xC, 4, 2);
            CharModelHitCreate(arg0->unk2);
            temp_r29 = var_r31->unk14;
            if ((var_r28 != NULL) && ((u16) var_r28->unk24 == 0)) {
                if (temp_r29 != NULL) {
                    temp_r29->unk8.x = var_r31->unk18.x;
                    temp_r29->unk8.y = var_r31->unk18.y;
                    temp_r29->unk8.z = var_r31->unk18.z;
                    temp_r29->unk14.x = var_r28->unk18.x;
                    temp_r29->unk14.y = var_r28->unk18.y;
                    temp_r29->unk14.z = var_r28->unk18.z;
                }
                var_r28->unk24 = var_r31->unk24;
                var_r31->unk24 = 0;
                var_r28->unk14 = var_r31->unk14;
                var_r31->unk14 = NULL;
            } else if (temp_r29 != NULL) {
                temp_r29->unk8.x = var_r31->unk18.x;
                temp_r29->unk8.y = var_r31->unk18.y;
                temp_r29->unk8.z = var_r31->unk18.z;
                temp_r29->unk14.x = var_r31->unk18.x;
                temp_r29->unk14.y = var_r31->unk18.y;
                temp_r29->unk14.z = var_r31->unk18.z;
            }
            if (temp_r29 != NULL) {
                temp_r29->unk20 = 1;
                temp_r29->unk2 = arg1->unkE0[(s16) sp10[sp10[4 + arg0->unk47C * 4 + temp_r29->unk24]]];
            }
        }
    }
    if ((s16) arg0->unk480 == 0x19) {
        Hu3DMotionShiftSet(*arg0->unk68C->model, *arg0->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
    }
    if ((s16) arg0->unk480 > 0x1D) {
        var_r27 = 1;
    }
    return var_r27;
}

s16 fn_1_66D0(M515Player *arg0) {
    M515Node *temp_r31;
    M515Node *temp_r31_2;
    M515Node *temp_r31_3;
    M515Node *temp_r31_4;
    s16 var_r30;
    u32 temp_r0;

    var_r30 = 0;
    temp_r0 = arg0->unk680 & 0xF;
    switch (temp_r0) {
    case 0:
    case 3:
    case 5:
    case 6:
    case 7:
        break;
    case 1:
        var_r30 = 2;
        temp_r31 = arg0->unk3F8->unkC;
        if ((temp_r31 != NULL) && (((u16) temp_r31->unk24 == 0) || ((u16) temp_r31->unk24 == 4))) {
            if ((s16) arg0->unk484 == 0xF) {
                arg0->unk470.x = temp_r31->unk18.x;
                arg0->unk470.y = temp_r31->unk18.y;
                arg0->unk470.z = temp_r31->unk18.z;
                arg0->unk3F8 = temp_r31;
                arg0->unk484 = 0;
            }
            if ((u16) temp_r31->unk24 == 4) {
                if ((s16) arg0->unkE == 2) {
                    var_r30 = 5;
                } else {
                    arg0->unk688 = fn_1_9DF8;
                    var_r30 = 4;
                }
            } else {
                var_r30 = 1;
            }
        }
        if ((s16) arg0->unk486 == 5) {
            arg0->unk47E = 0;
            arg0->unk486 = 0;
        }
        break;
    case 2:
        var_r30 = 2;
        temp_r31_2 = arg0->unk3F8->unk0;
        if ((temp_r31_2 != NULL) && (((u16) temp_r31_2->unk24 == 0) || ((u16) temp_r31_2->unk24 == 4))) {
            if ((s16) arg0->unk484 == 0xF) {
                arg0->unk470.x = temp_r31_2->unk18.x;
                arg0->unk470.y = temp_r31_2->unk18.y;
                arg0->unk470.z = temp_r31_2->unk18.z;
                arg0->unk3F8 = temp_r31_2;
                arg0->unk484 = 0;
            }
            var_r30 = 1;
        }
        if ((s16) arg0->unk486 == 5) {
            arg0->unk47E = 1;
            arg0->unk486 = 0;
        }
        break;
    case 4:
        var_r30 = 2;
        temp_r31_3 = arg0->unk3F8->unk4;
        if ((temp_r31_3 != NULL) && (((u16) temp_r31_3->unk24 == 0) || ((u16) temp_r31_3->unk24 == 4))) {
            if ((s16) arg0->unk484 == 0xF) {
                arg0->unk470.x = temp_r31_3->unk18.x;
                arg0->unk470.y = temp_r31_3->unk18.y;
                arg0->unk470.z = temp_r31_3->unk18.z;
                arg0->unk3F8 = temp_r31_3;
                arg0->unk484 = 0;
            }
            var_r30 = 1;
        }
        if ((s16) arg0->unk486 == 5) {
            arg0->unk47E = 2;
            arg0->unk486 = 0;
        }
        break;
    case 8:
        var_r30 = 2;
        temp_r31_4 = arg0->unk3F8->unk8;
        if ((temp_r31_4 != NULL) && (((u16) temp_r31_4->unk24 == 0) || ((u16) temp_r31_4->unk24 == 4))) {
            if ((s16) arg0->unk484 == 0xF) {
                arg0->unk470.x = temp_r31_4->unk18.x;
                arg0->unk470.y = temp_r31_4->unk18.y;
                arg0->unk470.z = temp_r31_4->unk18.z;
                arg0->unk3F8 = temp_r31_4;
                arg0->unk484 = 0;
            }
            if ((u16) temp_r31_4->unk24 == 4) {
                if ((s16) arg0->unkE == 2) {
                    var_r30 = 5;
                } else {
                    arg0->unk688 = fn_1_9DF8;
                    var_r30 = 4;
                }
            } else {
                var_r30 = 1;
            }
        }
        if ((s16) arg0->unk486 == 5) {
            arg0->unk47E = 3;
            arg0->unk486 = 0;
        }
        break;
    }
    return var_r30;
}

void fn_1_6980(M515Player *arg0) {
    if ((s16) arg0->unk682 > 0) {
        arg0->unk682 -= 1;
    }
    if ((s32) (arg0->unk680 & 0x10) != 0x10) {
        return;
    }
    arg0->unk682 = 5;
}

void fn_1_69B8(M515Player *arg0, M515Main *arg1) {
    s32 var_r28;
    s32 var_r30;
    s32 var_r30_2;

    if ((s16) arg1->unkDC < 0) {
        arg1->unkDC = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_364[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->unk488[0].unk0 = arg1->unkDC;
        var_r28 = 0;
loop_3:
        if (var_r28 < 8) {
            arg1->unkE0[var_r28] = Hu3DJointMotion(arg1->unkDC, HuDataSelHeapReadNum(lbl_1_data_3A8[var_r28], MEMORY_DEFAULT_NUM, HEAP_DATA));
            var_r28 += 1;
            goto loop_3;
        }
        Hu3DMotionSet(arg1->unkDC, arg1->unkE0[4]);
    } else {
        arg0->unk488[0].unk0 = Hu3DModelLink(arg1->unkDC);
    }
    Hu3DModelAttrSet(arg0->unk488[0].unk0, 1U);
    Hu3DModelAttrSet(arg0->unk488[0].unk0, 0x40000002U);
    Hu3DModelLayerSet(arg0->unk488[0].unk0, 3);
    Hu3DModelPosSet(arg0->unk488[0].unk0, 0.0f, 1.0f, 0.0f);
    Hu3DModelRotSet(arg0->unk488[0].unk0, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->unk488[0].unk0, (u16) lbl_1_rodata_10[arg0->unk0]);
    Hu3DModelScaleSet(arg0->unk488[0].unk0, 1.1f, 1.1f, 1.1f);
    arg0->unk488[0].unk20 = 0;
    arg0->unk488[0].unk28 = 45.0f * (f32) (rand8() / 32);
    var_r30 = 1;
loop_8:
    if (var_r30 < 8) {
        arg0->unk488[var_r30].unk0 = Hu3DModelLink(arg1->unkDC);
        Hu3DModelAttrSet(arg0->unk488[var_r30].unk0, 1U);
        Hu3DModelAttrSet(arg0->unk488[var_r30].unk0, 0x40000002U);
        Hu3DModelLayerSet(arg0->unk488[var_r30].unk0, 3);
        Hu3DModelPosSet(arg0->unk488[var_r30].unk0, 0.0f, 1.0f, 0.0f);
        Hu3DModelRotSet(arg0->unk488[var_r30].unk0, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(arg0->unk488[var_r30].unk0, (u16) lbl_1_rodata_10[arg0->unk0]);
        Hu3DModelScaleSet(arg0->unk488[var_r30].unk0, 1.1f, 1.1f, 1.1f);
        arg0->unk488[var_r30].unk20 = 0;
        arg0->unk488[var_r30].unk28 = 45.0f * (f32) (rand8() / 32);
        var_r30 += 1;
        goto loop_8;
    }
    if ((s16) arg1->unkDE < 0) {
        arg1->unkDE = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_364[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
        arg0->unk488[0].unk4 = arg1->unkDE;
    } else {
        arg0->unk488[0].unk4 = Hu3DModelLink(arg1->unkDE);
    }
    Hu3DModelAttrSet(arg0->unk488[0].unk4, 1U);
    Hu3DModelAttrSet(arg0->unk488[0].unk4, 0x40000002U);
    Hu3DModelLayerSet(arg0->unk488[0].unk4, 2);
    Hu3DModelPosSet(arg0->unk488[0].unk4, 0.0f, 0.5f, 0.0f);
    Hu3DModelRotSet(arg0->unk488[0].unk4, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->unk488[0].unk4, (u16) lbl_1_rodata_10[arg0->unk0]);
    Hu3DModelScaleSet(arg0->unk488[0].unk0, 1.1f, 1.1f, 1.1f);
    var_r30_2 = 1;
loop_14:
    if (var_r30_2 < 8) {
        arg0->unk488[var_r30_2].unk4 = Hu3DModelLink(arg1->unkDE);
        Hu3DModelAttrSet(arg0->unk488[var_r30_2].unk4, 1U);
        Hu3DModelAttrSet(arg0->unk488[var_r30_2].unk4, 0x40000002U);
        Hu3DModelLayerSet(arg0->unk488[var_r30_2].unk4, 2);
        Hu3DModelPosSet(arg0->unk488[var_r30_2].unk4, 0.0f, 0.5f, 0.0f);
        Hu3DModelRotSet(arg0->unk488[var_r30_2].unk4, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(arg0->unk488[var_r30_2].unk4, (u16) lbl_1_rodata_10[arg0->unk0]);
        Hu3DModelScaleSet(arg0->unk488[var_r30_2].unk4, 1.1f, 1.1f, 1.1f);
        var_r30_2 += 1;
        goto loop_14;
    }
}

void fn_1_6FE8(M515Player *arg0) {
    f32 sp8[4];
    s32 var_r29;
    s32 var_r30;
    Vec *temp_r4;
    Vec *temp_r4_2;
    M515Obj *temp_r5;
    M515Obj *temp_r5_2;

    sp8[0] = lbl_1_rodata_194[0];
    sp8[1] = lbl_1_rodata_194[1];
    sp8[2] = lbl_1_rodata_194[2];
    sp8[3] = lbl_1_rodata_194[3];
    arg0->unk5E8 = 0;
    var_r30 = 0;
loop_7:
    if (var_r30 < 5) {
        var_r29 = 0;
loop_5:
        if (var_r29 < 5) {
            if ((u16) arg0->unk10[(var_r30) * 5 + (var_r29)].unk24 == 2) {
                arg0->unk10[(var_r30) * 5 + (var_r29)].unk14 = &arg0->unk488[arg0->unk5E8];
                arg0->unk5E8 += 1;
                temp_r5 = arg0->unk10[(var_r30) * 5 + (var_r29)].unk14;
                temp_r4 = &arg0->unk10[(var_r30) * 5 + (var_r29)].unk18;
                temp_r5->unk8.x = (s32) temp_r4->x;
                temp_r5->unk8.y = (s32) temp_r4->y;
                temp_r5->unk8.z = (s32) temp_r4->z;
                temp_r5_2 = arg0->unk10[(var_r30) * 5 + (var_r29)].unk14;
                temp_r4_2 = &arg0->unk10[(var_r30) * 5 + (var_r29)].unk18;
                temp_r5_2->unk14.x = (s32) temp_r4_2->x;
                temp_r5_2->unk14.y = (s32) temp_r4_2->y;
                temp_r5_2->unk14.z = (s32) temp_r4_2->z;
                arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk24 = (s16) (rand8() / 64);
                Hu3DModelAttrReset(arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk0, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk0, arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.x, 1.0f + arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.y, arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.z);
                Hu3DModelRotSet(arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk0, 0.0f, sp8[arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk24], 0.0f);
                Hu3DModelAttrReset(arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk4, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r30) * 5 + (var_r29)].unk14->unk4, arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.x, 0.5f + arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.y, arg0->unk10[(var_r30) * 5 + (var_r29)].unk18.z);
            }
            var_r29 += 1;
            goto loop_5;
        }
        var_r30 += 1;
        goto loop_7;
    }
}


void fn_1_73B0(M515Player *arg0, s32 arg1) {
    M515Place *var_r27;
    f32 var_f31;
    s16 var_r25;
    s32 temp_r26;
    s32 var_r30;
    M515Main *temp_r28;

    temp_r28 = lbl_1_bss_4->data;
    if (arg1 == 0) {
        var_r27 = lbl_1_data_110C[temp_r28->unk2[arg1]];
        var_f31 = 0.0f;
    } else if (arg1 == 1) {
        var_r27 = lbl_1_data_1134[temp_r28->unk2[arg1]];
        var_f31 = 180.0f;
    } else {
        var_r27 = lbl_1_data_115C[temp_r28->unk2[arg1]];
        var_f31 = 0.0f;
    }
    var_r30 = 0;
loop_14:
    if (var_r30 >= 0x19) {

    } else if ((s16) var_r27->piece >= 0) {
        temp_r26 = var_r27->piece - 1;
        if ((s16) temp_r28->unk10C[temp_r26] < 0) {
            temp_r28->unk10C[temp_r26] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_320[temp_r26], MEMORY_DEFAULT_NUM, HEAP_DATA));
            arg0->unk5EA[arg1 * 25 + var_r30] = temp_r28->unk10C[temp_r26];
        } else {
            arg0->unk5EA[arg1 * 25 + var_r30] = Hu3DModelLink(temp_r28->unk10C[temp_r26]);
        }
        if (arg1 == 1) {
            var_r25 = 0x18 - var_r27->pos;
        } else {
            var_r25 = var_r27->pos;
        }
        Hu3DModelAttrSet(arg0->unk5EA[arg1 * 25 + var_r30], 1U);
        Hu3DModelAttrSet(arg0->unk5EA[arg1 * 25 + var_r30], 0x40000002U);
        Hu3DModelLayerSet(arg0->unk5EA[arg1 * 25 + var_r30], 1);
        Hu3DModelPosSet(arg0->unk5EA[arg1 * 25 + var_r30], (150.0f * (f32) (var_r25 % 5)) - 300.0f, 400.0f * (f32) arg1, (150.0f * (f32) (var_r25 / 5)) - 300.0f);
        Hu3DModelRotSet(arg0->unk5EA[arg1 * 25 + var_r30], 0.0f, var_r27->rot + var_f31, 0.0f);
        Hu3DModelCameraSet(arg0->unk5EA[arg1 * 25 + var_r30], (u16) lbl_1_rodata_10[arg0->unk0]);
        var_r30 += 1;
        var_r27++;
        goto loop_14;
    }
loop_17:
    if (var_r30 < 0x19) {
        arg0->unk5EA[arg1 * 25 + var_r30] = -1;
        var_r30 += 1;
        goto loop_17;
    }
}

void fn_1_7768(M515Player *arg0, s32 arg1) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 0x19) {
        if ((s16) arg0->unk5EA[arg1 * 25 + var_r31] >= 0) {
            Hu3DModelAttrReset(arg0->unk5EA[arg1 * 25 + var_r31], 1U);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_77F0(M515Player *arg0, s32 arg1) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 0x19) {
        if ((s16) arg0->unk5EA[arg1 * 25 + var_r31] >= 0) {
            Hu3DModelAttrSet(arg0->unk5EA[arg1 * 25 + var_r31], 1U);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

s16 fn_1_7878(M515Player *arg0) {
    s16 var_r30;
    M515Main *temp_r29;

    var_r30 = 0;
    temp_r29 = lbl_1_bss_4->data;
    if ((((s32 (*)(M515Seq *, M515Player *)) arg0->unk688) != NULL) && (arg0->unk688(arg0->unk684, arg0) != 0)) {
        if ((s16) temp_r29->unkCAC == 0) {
            arg0->unk688 = NULL;
            var_r30 = 1;
        } else {
            arg0->unk688 = fn_1_B0B8;
            arg0->unk684->unk0 = 0;
        }
    }
    return var_r30;
}

u16 fn_1_7924(M515Player *arg0) {
    f32 temp_f29;
    f32 var_f27;
    f32 var_f28;
    f32 var_f30;
    f32 var_f31;
    u16 var_r30;

    var_r30 = 0;
    var_f31 = (f32) (s8) (u8) HuPadStkX[arg0->unk4];
    var_f30 = (f32) (s8) (u8) HuPadStkY[arg0->unk4];
    if ((s16) arg0->unkE == 1) {
        var_f31 *= -1.0f;
        var_f30 *= -1.0f;
    }
    temp_f29 = (f32) (180.0 * (atan2((f64) var_f31, (f64) var_f30) / 3.141592653589793));
    if (var_f30 < 0.0f) {
        var_f28 = -var_f30;
    } else {
        var_f28 = var_f30;
    }
    if (var_f31 < 0.0f) {
        var_f27 = -var_f31;
    } else {
        var_f27 = var_f31;
    }
    if ((var_f27 + var_f28) > 32.0f) {
        if ((temp_f29 >= -30.0f) && (temp_f29 < 60.0f)) {
            var_r30 = 1;
        } else if ((temp_f29 >= 60.0f) && (temp_f29 < 150.0f)) {
            var_r30 = 2;
        } else if ((temp_f29 >= -120.0f) && (temp_f29 < -30.0f)) {
            var_r30 = 4;
        } else {
            var_r30 = 8;
        }
    }
    if ((s32) (HuPadBtnDown[arg0->unk4] & 0x800) != 0) {
        arg0->unk682 = 0;
        var_r30 = 0x20;
    } else if ((s32) (HuPadBtnDown[arg0->unk4] & 0x200) != 0) {
        var_r30 |= 0x10;
    }
    return var_r30;
}

void fn_1_7BE8(M515Obj *arg0, M515Main *arg1) {
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f31;
    s16 temp_r0;

    temp_r0 = arg0->unk20;
    switch (temp_r0) {                              /* irregular */
    case 1:
        arg0->unk22 = 0;
        Hu3DMotionSet(arg0->unk0, arg0->unk2);
        Hu3DModelAttrSet(arg0->unk0, 0x40000001U);
        Hu3DModelAttrReset(arg0->unk0, 0x40000002U);
        arg0->unk20 += 1;
        /* fallthrough */
    case 2:
        arg0->unk22 += 1;
        if ((s16) arg0->unk22 >= 2) {
            arg0->unk20 += 1;
            return;
        }
        return;
    case 3:
        arg0->unk22 += 1;
        if ((s16) arg0->unk22 >= 0xA) {
            arg0->unk20 += 1;
        }
        temp_f31 = ((f32) arg0->unk22 - 2.0f) * 0.125f;
        sp8 = ((1.0f - temp_f31) * arg0->unk8.x) + (temp_f31 * arg0->unk14.x);
        spC = 1.0f + arg0->unk14.y;
        sp10 = ((1.0f - temp_f31) * arg0->unk8.z) + (temp_f31 * arg0->unk14.z);
        Hu3DModelPosSet(arg0->unk0, sp8, spC, sp10);
        spC = 0.5f + arg0->unk14.y;
        Hu3DModelPosSet(arg0->unk4, sp8, spC, sp10);
        return;
    case 4:
        arg0->unk22 += 1;
        if ((s16) arg0->unk22 >= 0x14) {
            Hu3DMotionShiftSet(arg0->unk0, arg1->unkE0[7], 0.0f, 3.0f, 0x40000001U);
            arg0->unk20 += 1;
            return;
        }
        break;
    case 5:
        arg0->unk22 += 1;
        if ((s16) arg0->unk22 >= 0x64) {
            Hu3DModelAttrSet(arg0->unk0, 0x40000002U);
        }
        break;
    }
}

void fn_1_7E5C(M515Cam *arg0, s16 arg1) {
    f32 *var_r31;

    if (arg1 == 0) {
        var_r31 = lbl_1_data_28;
    } else {
        var_r31 = &lbl_1_data_28[6];
    }
    arg0->unk0 = var_r31[0];
    arg0->unk4 = var_r31[1];
    arg0->unk8 = var_r31[2];
    arg0->unkC.x = var_r31[3];
    arg0->unkC.y = var_r31[4];
    arg0->unkC.z = var_r31[5];
    arg0->unk24 = 0;
    arg0->unk26 = 0;
    arg0->unk28 = arg1;
    arg0->unk2C = 0;
}

void fn_1_7EE0(M515Cam *arg0) {
    f32 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f64 temp_f28;
    f64 temp_f28_2;

    if (arg0->unk0 > 360.0f) {
        arg0->unk0 -= 360.0f;
    }
    if (arg0->unk0 < 0.0f) {
        arg0->unk0 += 360.0f;
    }
    if (arg0->unk4 > 360.0f) {
        arg0->unk4 -= 360.0f;
    }
    if (arg0->unk4 < 0.0f) {
        arg0->unk4 += 360.0f;
    }
    temp_f28 = cos((3.141592653589793 * (f64) arg0->unk0) / 180.0);
    temp_f31 = (f32) ((f64) arg0->unkC.x + ((f64) (0.5f * arg0->unk8) * cos((3.141592653589793 * (f64) arg0->unk4) / 180.0) * temp_f28));
    temp_f30 = (f32) ((f64) arg0->unkC.y + ((f64) (0.5f * arg0->unk8) * sin((3.141592653589793 * (f64) arg0->unk4) / 180.0)));
    temp_f28_2 = sin((3.141592653589793 * (f64) arg0->unk0) / 180.0);
    temp_f29 = (f32) ((f64) arg0->unkC.z + ((f64) (0.5f * arg0->unk8) * cos((3.141592653589793 * (f64) arg0->unk4) / 180.0) * temp_f28_2));
    sp8 = arg0->unkC.z;
    Hu3DCameraPosSet((s32) lbl_1_rodata_10[arg0->unk28], temp_f31, temp_f30, temp_f29, 0.0f, 1.0f, 0.0f, arg0->unkC.x, arg0->unkC.y, arg0->unkC.z);
}

void fn_1_81A8(M515Cam *arg0, M515Player *arg1) {
    f32 var_f31;
    f32 var_f31_2;

    if ((s16) arg1->unkE == 1) {
        if (arg1->unk44C.x > 150.0f) {
            var_f31 = arg1->unk44C.x - 150.0f;
        } else if (arg1->unk44C.x < -150.0f) {
            var_f31 = 0.5f * (150.0f + arg1->unk44C.x);
        } else {
            var_f31 = 0.0f;
        }
    } else if (arg1->unk44C.x > 150.0f) {
        var_f31 = 0.5f * (arg1->unk44C.x - 150.0f);
    } else if (arg1->unk44C.x < -150.0f) {
        var_f31 = 150.0f + arg1->unk44C.x;
    } else {
        var_f31 = 0.0f;
    }
    if ((s16) arg1->unkE == 1) {
        arg0->unkC.x = var_f31 - 25.0f;
    } else {
        arg0->unkC.x = 25.0f + var_f31;
    }
    if (arg1->unk44C.z > 150.0f) {
        var_f31_2 = arg1->unk44C.z - 150.0f;
    } else if (arg1->unk44C.z < -150.0f) {
        var_f31_2 = 150.0f + arg1->unk44C.z;
    } else {
        var_f31_2 = 0.0f;
    }
    if (var_f31_2 > 150.0f) {
        var_f31_2 = 150.0f;
    }
    if (var_f31_2 < -150.0f) {
        var_f31_2 = -150.0f;
    }
    if ((s16) arg1->unkE == 1) {
        arg0->unkC.z = 75.0f + var_f31_2;
        return;
    }
    arg0->unkC.z = var_f31_2 - 75.0f;
}

s32 fn_1_83E8(M515Cam *arg0) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r29;
    M515Main *temp_r30;

    var_r29 = 0;
    temp_r30 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 == 0x37) {
            fn_1_BE78((M515Main *) temp_r30, temp_r30->unk16[arg0->unk28], 0);
            fn_1_BF24((M515Main *) temp_r30, temp_r30->unk26[arg0->unk28], 1);
        }
        if ((s16) arg0->unk26 >= 0x78) {
            fn_1_BE78((M515Main *) temp_r30, temp_r30->unk96[arg0->unk28 * 2 + 0], 0);
            fn_1_BE78((M515Main *) temp_r30, temp_r30->unk76[arg0->unk28 * 4 + 0], 0);
            fn_1_BE78((M515Main *) temp_r30, temp_r30->unk76[arg0->unk28 * 4 + 1], 0);
            arg0->unk24 = 0;
            var_r29 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 120.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0] * temp_f30) + (lbl_1_data_28[6] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[1] * temp_f30) + (lbl_1_data_28[7] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[2] * temp_f30) + (lbl_1_data_28[8] * temp_f31);
        arg0->unkC.x = (lbl_1_data_28[3] * temp_f30) + (lbl_1_data_28[9] * temp_f31);
        arg0->unkC.y = (lbl_1_data_28[4] * temp_f30) + (lbl_1_data_28[0xA] * temp_f31);
        arg0->unkC.z = (lbl_1_data_28[5] * temp_f30) + (lbl_1_data_28[0xB] * temp_f31);
        break;
    }
    return var_r29;
}

s32 fn_1_86F4(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk18.x = arg0->unkC.x;
        arg0->unk18.y = arg0->unkC.y;
        arg0->unk18.z = arg0->unkC.z;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x46) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 70.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[6] * temp_f30) + (lbl_1_data_28[0xC] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[7] * temp_f30) + (lbl_1_data_28[0xD] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[8] * temp_f30) + (lbl_1_data_28[0xE] * temp_f31);
        arg0->unkC.x = (arg0->unk18.x * temp_f30) + (lbl_1_data_28[0xF] * temp_f31);
        arg0->unkC.y = (arg0->unk18.y * temp_f30) + (lbl_1_data_28[0x10] * temp_f31);
        arg0->unkC.z = (arg0->unk18.z * temp_f30) + (lbl_1_data_28[0x11] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_8964(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x64) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 100.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0xC] * temp_f30) + (lbl_1_data_28[0x12] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0xD] * temp_f30) + (lbl_1_data_28[0x13] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0xE] * temp_f30) + (lbl_1_data_28[0x14] * temp_f31);
        arg0->unkC.x = (lbl_1_data_28[0xF] * temp_f30) + (lbl_1_data_28[0x15] * temp_f31);
        arg0->unkC.y = (lbl_1_data_28[0x10] * temp_f30) + (lbl_1_data_28[0x16] * temp_f31);
        arg0->unkC.z = (lbl_1_data_28[0x11] * temp_f30) + (lbl_1_data_28[0x17] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_8BD4(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x2D) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 45.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0x12] * temp_f30) + (lbl_1_data_28[0x18] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0x13] * temp_f30) + (lbl_1_data_28[0x19] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0x14] * temp_f30) + (lbl_1_data_28[0x1A] * temp_f31);
        arg0->unkC.x = (lbl_1_data_28[0x15] * temp_f30) + (lbl_1_data_28[0x1B] * temp_f31);
        arg0->unkC.y = (lbl_1_data_28[0x16] * temp_f30) + (lbl_1_data_28[0x1C] * temp_f31);
        arg0->unkC.z = (lbl_1_data_28[0x17] * temp_f30) + (lbl_1_data_28[0x1D] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_8E44(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk18.x = arg0->unkC.x;
        arg0->unk18.y = arg0->unkC.y;
        arg0->unk18.z = arg0->unkC.z;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x46) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 70.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0x18] * temp_f30) + (lbl_1_data_28[0x1E] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0x19] * temp_f30) + (lbl_1_data_28[0x1F] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0x1A] * temp_f30) + (lbl_1_data_28[0x20] * temp_f31);
        arg0->unkC.x = (arg0->unk18.x * temp_f30) + (lbl_1_data_28[0x21] * temp_f31);
        arg0->unkC.y = (arg0->unk18.y * temp_f30) + (lbl_1_data_28[0x22] * temp_f31);
        arg0->unkC.z = (arg0->unk18.z * temp_f30) + (lbl_1_data_28[0x23] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_90B4(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x64) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 100.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0x1E] * temp_f30) + (lbl_1_data_28[0x24] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0x1F] * temp_f30) + (lbl_1_data_28[0x25] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0x20] * temp_f30) + (lbl_1_data_28[0x26] * temp_f31);
        arg0->unkC.x = (lbl_1_data_28[0x21] * temp_f30) + (lbl_1_data_28[0x27] * temp_f31);
        arg0->unkC.y = (lbl_1_data_28[0x22] * temp_f30) + (lbl_1_data_28[0x28] * temp_f31);
        arg0->unkC.z = (lbl_1_data_28[0x23] * temp_f30) + (lbl_1_data_28[0x29] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_9324(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x2D) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 45.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0x24] * temp_f30) + (lbl_1_data_28[0x2A] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0x25] * temp_f30) + (lbl_1_data_28[0x2B] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0x26] * temp_f30) + (lbl_1_data_28[0x2C] * temp_f31);
        arg0->unkC.x = (lbl_1_data_28[0x27] * temp_f30) + (lbl_1_data_28[0x2D] * temp_f31);
        arg0->unkC.y = (lbl_1_data_28[0x28] * temp_f30) + (lbl_1_data_28[0x2E] * temp_f31);
        arg0->unkC.z = (lbl_1_data_28[0x29] * temp_f30) + (lbl_1_data_28[0x2F] * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_9594(M515Cam *arg0) {
    M515Main *sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    sp8 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk24;
    switch (temp_r0) {                              /* irregular */
    case 0:
        arg0->unk26 = 0;
        arg0->unk18.x = arg0->unkC.x;
        arg0->unk18.y = arg0->unkC.y;
        arg0->unk18.z = arg0->unkC.z;
        arg0->unk24 += 1;
        /* fallthrough */
    case 1:
        arg0->unk26 += 1;
        if ((s16) arg0->unk26 >= 0x50) {
            arg0->unk24 = 0;
            var_r30 = 1;
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) arg0->unk26 / 80.0f))) / 180.0))));
        temp_f30 = 1.0f - temp_f31;
        arg0->unk0 = (lbl_1_data_28[0x2A] * temp_f30) + (lbl_1_data_28[0x30] * temp_f31);
        arg0->unk4 = (lbl_1_data_28[0x2B] * temp_f30) + (lbl_1_data_28[0x31] * temp_f31);
        arg0->unk8 = (lbl_1_data_28[0x2C] * temp_f30) + (lbl_1_data_28[0x32] * temp_f31);
        arg0->unkC.x = (arg0->unk18.x * temp_f30) + (lbl_1_data_28[0x33] * temp_f31);
        arg0->unkC.y = (arg0->unk18.y * temp_f30) + (lbl_1_data_28[0x34] * temp_f31);
        arg0->unkC.z = (arg0->unk18.z * temp_f30) + (lbl_1_data_28[0x35] * temp_f31);
        break;
    }
    return var_r30;
}

void fn_1_9804(M515Seq *arg0, M515Cam *arg1, s32 arg2) {
    arg0->unk2 = 0;
    arg0->unk0 = 0;
    arg0->unk4 = arg1;
    arg0->unkC = arg2;
    arg0->unk8 = NULL;
}

void fn_1_9828(M515Wipe *arg0) {
    arg0->unk0 = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M515, 67), 0xA, 0);
    espDrawNoSet(arg0->unk0, 0);
    espPosSet(arg0->unk0, 576.0f, 240.0f);
    espAttrSet(arg0->unk0, 1U);
    arg0->unk2 = espEntry(DATA_MAKE_NUM(DATADIR_MP5_M515, 68), 0xA, 0);
    espDrawNoSet(arg0->unk2, 0);
    espPosSet(arg0->unk2, 576.0f, 240.0f);
    espAttrSet(arg0->unk2, 1U);
    arg0->unk4 = 640.0f;
    arg0->unk8 = 480.0f;
    arg0->unkC = 0.0f;
}

void fn_1_9920(M515Wipe *arg0) {
    espKill(arg0->unk0);
    espKill(arg0->unk2);
}

void fn_1_9958(M515Wipe *arg0) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    s32 sp14;
    s32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;

    sp28 = lbl_1_rodata_1FC[0];
    sp2C = lbl_1_rodata_1FC[1];
    sp30 = lbl_1_rodata_1FC[2];
    sp34 = lbl_1_rodata_1FC[3];
    sp18 = lbl_1_rodata_20C[0];
    sp1C = lbl_1_rodata_20C[1];
    sp20 = lbl_1_rodata_20C[2];
    sp24 = lbl_1_rodata_20C[3];
    temp_f31 = arg0->unk4;
    temp_f30 = arg0->unk8;
    sp14 = 8;
    sp10 = 0x14;
    spC = 8.0f;
    sp8 = 20.0f;
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[0], 0.0f, 0.0f, 16.0f + temp_f31, 40.0f + temp_f30, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[1], temp_f31 - 16.0f, 0.0f, 16.0f + (640.0f - temp_f31), 40.0f + temp_f30, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[2], 0.0f, temp_f30 - 40.0f, 16.0f + temp_f31, 40.0f + (480.0f - temp_f30), 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[3], temp_f31 - 16.0f, temp_f30 - 40.0f, 16.0f + (640.0f - temp_f31), 40.0f + (480.0f - temp_f30), 0.0f, 1.0f);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[0], 0U, 0U, (u32) temp_f31, (u32) temp_f30);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[1], (u32) temp_f31, 0U, (u32) (640.0f - temp_f31), (u32) temp_f30);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[2], 0U, (u32) temp_f30, (u32) temp_f31, (u32) (480.0f - temp_f30));
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[3], (u32) temp_f31, (u32) temp_f30, (u32) (640.0f - temp_f31), (u32) (480.0f - temp_f30));
    espPosSet(arg0->unk0, 576.0f * (temp_f31 / 640.0f), 240.0f);
    espPosSet(arg0->unk2, 288.0f, 480.0f * (temp_f30 / 480.0f));
}

s32 fn_1_9DF8(M515Seq *arg0, M515Player *arg1) {
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    u16 sp8[4];
    f32 sp10;
    f32 temp_f1;
    s16 temp_r4;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    M515Main *temp_r24;
    M515Main *temp_r30;

    var_r25 = 0;
    sp10 = lbl_1_rodata_224[0];
    sp14 = lbl_1_rodata_224[1];
    sp18 = lbl_1_rodata_224[2];
    sp1C = lbl_1_rodata_224[3];
    sp8[0] = lbl_1_rodata_234[0];
    sp8[1] = lbl_1_rodata_234[1];
    sp8[2] = lbl_1_rodata_234[2];
    sp8[3] = lbl_1_rodata_234[3];
    temp_r30 = lbl_1_bss_4->data;
    arg1->unk680 = 0;
    temp_r4 = arg0->unk0;
    if ((u32) temp_r4 <= 0x13U) {
        switch (temp_r4) {
        case 0:
            arg0->unk2 = 0;
            arg1->unk486 = 0;
            if ((s16) arg1->unkE == 0) {
                arg1->unk47E = 0;
                arg0->unk8 = fn_1_86F4;
                arg1->unk470.z = sp10;
                arg1->unk470.y = 25.0f;
                fn_1_BF24((M515Main *) temp_r30, temp_r30->unk16[arg1->unk0], 1);
            } else {
                arg1->unk47E = 3;
                arg0->unk8 = fn_1_8E44;
                arg1->unk470.z = -sp10;
                arg1->unk470.y = 425.0f;
                fn_1_BF24((M515Main *) temp_r30, temp_r30->unk36[arg1->unk0], 1);
                fn_1_BE78((M515Main *) temp_r30, temp_r30->unk26[arg1->unk0], 0);
                fn_1_BE78((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 3], 0);
                fn_1_BE78((M515Main *) temp_r30, temp_r30->unk96[arg1->unk0 * 2 + 0], 0);
            }
            arg1->unk484 = 0;
            Hu3DMotionShiftSet(*arg1->unk68C->model, arg1->unk68C->motion[2], 0.0f, 5.0f, 0x40000001U);
            arg0->unk0 += 1;
            /* fallthrough */
        case 1:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xF) {
                arg0->unk0 += 1;
            }
            break;
        case 2:
            if ((s16) arg1->unkE == 0) {
                arg1->unk470.z = sp14;
            } else {
                arg1->unk470.z = -sp14;
            }
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 3:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xF) {
                arg0->unk0 += 1;
            }
            break;
        case 4:
            if ((s16) arg1->unkE == 0) {
                Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 0], 0x40000002U);
                arg1->unk470.z = sp18;
            } else {
                Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 2], 0x40000002U);
                arg1->unk470.z = -sp18;
            }
            if ((s32) (arg1->unk0 & 1) != 0) {
                HuAudFXPlayPan(0x6E6, (s16) sp8[arg1->unk0]);
            } else {
                HuAudFXPlayPan(0x6E5, (s16) sp8[arg1->unk0]);
            }
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 5:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xF) {
                if ((s16) arg1->unkE == 0) {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkE[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk3E[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk46[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk4E[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk56[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkAE[arg1->unk0], 0);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 0], 0x40000002U);
                } else {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkE[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk2E[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk56[arg1->unk0], 1);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk6E[arg1->unk0], 1);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 2], 0x40000002U);
                }
                arg0->unk0 += 1;
            }
            break;
        case 6:
            if ((s16) arg1->unkE == 0) {
                arg1->unk470.z = sp1C;
            } else {
                arg1->unk470.z = -sp1C;
            }
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 7:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xF) {
                if ((s16) arg1->unkE == 0) {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk16[arg1->unk0], 1);
                    Hu3DModelAttrSet(temp_r30->unk76[arg1->unk0 * 4 + 0], 0x40000004U);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 0], 0x40000002U);
                    var_r27 = 0;
loop_36:
                    if (var_r27 < 0x19) {
                        if ((s16) arg1->unk5EA[var_r27] >= 0) {
                            Hu3DModelAttrSet(arg1->unk5EA[var_r27], 1U);
                        }
                        var_r27 += 1;
                        goto loop_36;
                    }
                } else {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk36[arg1->unk0], 1);
                    Hu3DModelAttrSet(temp_r30->unk76[arg1->unk0 * 4 + 2], 0x40000004U);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 2], 0x40000002U);
                    var_r26 = 0;
loop_42:
                    if (var_r26 < 0x19) {
                        if ((s16) arg1->unk5EA[25 + var_r26] >= 0) {
                            Hu3DModelAttrSet(arg1->unk5EA[25 + var_r26], 1U);
                        }
                        var_r26 += 1;
                        goto loop_42;
                    }
                }
                temp_r24 = lbl_1_bss_4->data;
                var_r28 = 0;
loop_45:
                if (var_r28 < 8) {
                    Hu3DModelAttrSet(arg1->unk488[var_r28].unk0, 1U);
                    Hu3DMotionSet(arg1->unk488[var_r28].unk0, temp_r24->unkE0[4]);
                    Hu3DMotionTimeSet(arg1->unk488[var_r28].unk0, 0.0f);
                    Hu3DModelAttrSet(arg1->unk488[var_r28].unk0, 0x40000002U);
                    Hu3DModelAttrSet(arg1->unk488[var_r28].unk4, 1U);
                    var_r28 += 1;
                    goto loop_45;
                }
                arg0->unk0 += 1;
            }
            break;
        case 8:
            arg1->unk486 = 0;
            arg0->unk2 = 0;
            if ((s16) arg1->unkE == 0) {
                arg1->unk47E = 1;
            } else {
                arg1->unk47E = 2;
            }
            arg0->unk0 += 1;
            /* fallthrough */
        case 9:
            if ((s16) arg1->unkE == 0) {
                if (((s16) arg1->unk47C == 1) && ((s16) arg1->unk486 == 5)) {
                    if (((s16) *arg1->unk68C->motion != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) *arg1->unk68C->motion != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
                        Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
                    }
                    arg1->unk47E = 3;
                    arg1->unk486 = 0;
                }
            } else if (((s16) arg1->unk47C == 2) && ((s16) arg1->unk486 == 5)) {
                if (((s16) *arg1->unk68C->motion != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) *arg1->unk68C->motion != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
                    Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
                }
                arg1->unk47E = 0;
                arg1->unk486 = 0;
            }
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xA) {
                arg0->unk0 += 1;
            }
            break;
        case 10:
            if (((s32 (*)(M515Cam *)) arg0->unk8) == NULL) {
                arg0->unk2 = 0;
                arg0->unk0 += 1;
                if ((s16) arg1->unkE == 0) {
                    arg0->unk8 = fn_1_8964;
                } else {
                    arg0->unk8 = fn_1_90B4;
                }
                if ((s32) (arg1->unk0 & 1) != 0) {
                    HuAudFXPlayPan(0x6E4, (s16) sp8[arg1->unk0]);
                } else {
                    HuAudFXPlayPan(0x6E3, (s16) sp8[arg1->unk0]);
                }
                omVibrate(arg1->unk0, 0xF, 6, 6);
            }
            break;
        case 11:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 == 5) {
                if ((s16) arg1->unkE == 0) {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk26[arg1->unk0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk2E[arg1->unk0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk36[arg1->unk0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkB6[arg1->unk0 * 3 + 1], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk5E[arg1->unk0 * 2 + 0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 2], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 3], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk96[arg1->unk0 * 2 + 1], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unkB6[arg1->unk0 * 3 + 0], 0);
                    Hu3DModelLayerSet(temp_r30->unk3E[arg1->unk0], 2);
                } else {
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk46[arg1->unk0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk4E[arg1->unk0], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkB6[arg1->unk0 * 3 + 2], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unk5E[arg1->unk0 * 2 + 1], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unkB6[arg1->unk0 * 3 + 1], 0);
                }
            }
            if ((s16) arg0->unk2 == 0x55) {
                omVibrate(arg1->unk0, 0xF, 6, 6);
            }
            if ((s16) arg0->unk2 >= 0x64) {
                if ((s16) arg1->unkE == 1) {
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk5E[arg1->unk0 * 2 + 0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk96[arg1->unk0 * 2 + 0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unkA6[arg1->unk0], 0);
                }
                arg0->unk0 = 0x12;
            }
            temp_f1 = fn_1_BD10(temp_r30->unk96[arg1->unk0 * 2 + arg1->unkE], arg1->unkE, (f32) arg0->unk2 / 100.0f);
            arg1->unk464.y = 25.0f + temp_f1;
            arg1->unk470.y = 25.0f + temp_f1;
            break;
        case 12:
            arg1->unkE += 1;
            if ((s16) arg1->unkE == 1) {
                arg0->unk8 = fn_1_8BD4;
                arg1->unk470.z = sp18;
                arg1->unk470.y = 425.0f;
            } else {
                arg0->unk8 = fn_1_9324;
                arg1->unk470.z = -sp18;
                arg1->unk470.y = 825.0f;
            }
            fn_1_C2B0(arg1);
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            if (((s16) arg1->unk68C->motion[2] != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) arg1->unk68C->motion[2] != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
                Hu3DMotionShiftSet(*arg1->unk68C->model, arg1->unk68C->motion[2], 0.0f, 5.0f, 0x40000001U);
            }
            arg0->unk0 += 1;
            /* fallthrough */
        case 13:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 == 0xA) {
                if ((s16) arg1->unkE == 1) {
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unkE[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk26[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk2E[arg1->unk0], 1);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk46[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk4E[arg1->unk0], 1);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk56[arg1->unk0], 1);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 3], 0);
                    Hu3DMotionSet(temp_r30->unkAE[arg1->unk0], temp_r30->unk108);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unkAE[arg1->unk0], 1);
                } else {
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk16[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk46[arg1->unk0], 1);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 1], 0);
                    fn_1_BE78((M515Main *) temp_r30, temp_r30->unkAE[arg1->unk0], 0);
                }
            }
            if ((s16) arg0->unk2 >= 0xF) {
                if ((s16) arg1->unkE == 1) {
                    Hu3DModelAttrSet(temp_r30->unk76[arg1->unk0 * 4 + 1], 0x40000004U);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 1], 0x40000002U);
                } else {
                    Hu3DModelAttrSet(temp_r30->unk76[arg1->unk0 * 4 + 3], 0x40000004U);
                    Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 3], 0x40000002U);
                }
                arg0->unk0 += 1;
            }
            break;
        case 14:
            if ((s16) arg1->unkE == 1) {
                arg1->unk470.z = sp14;
            } else {
                arg1->unk470.z = -sp14;
            }
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 15:
            arg0->unk2 += 1;
            if (((s16) arg0->unk2 == 5) && ((s16) arg1->unkE == 2)) {
                fn_1_BF24((M515Main *) temp_r30, temp_r30->unk6E[arg1->unk0], 1);
                Hu3DModelLayerSet(temp_r30->unk3E[arg1->unk0], 6);
            }
            if ((s16) arg0->unk2 >= 0xF) {
                arg0->unk0 += 1;
            }
            break;
        case 16:
            if ((s16) arg1->unkE == 1) {
                arg1->unk470.z = sp10;
            } else {
                arg1->unk470.z = -sp10;
            }
            arg1->unk484 = 0;
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 17:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xF) {
                if ((s16) arg1->unkE == 1) {
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 0], 0);
                } else {
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk1E[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk2E[arg1->unk0], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk76[arg1->unk0 * 4 + 2], 0);
                    fn_1_BF24((M515Main *) temp_r30, temp_r30->unk26[arg1->unk0], 0);
                }
                arg0->unk0 = 0;
                var_r25 = 1;
            }
            break;
        case 18:
            if ((s16) arg1->unkE == 0) {
                Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 1], 0x40000002U);
            } else {
                Hu3DModelAttrReset(temp_r30->unk76[arg1->unk0 * 4 + 3], 0x40000002U);
            }
            if ((s32) (arg1->unk0 & 1) != 0) {
                HuAudFXPlayPan(0x6E6, (s16) sp8[arg1->unk0]);
            } else {
                HuAudFXPlayPan(0x6E5, (s16) sp8[arg1->unk0]);
            }
            arg0->unk2 = 0;
            arg0->unk0 += 1;
            /* fallthrough */
        case 19:
            arg0->unk2 += 1;
            if ((s16) arg0->unk2 >= 0xA) {
                arg0->unk0 = 0xC;
            }
            break;
        }
    }
    if ((((s32 (*)(M515Cam *)) arg0->unk8) != NULL) && (arg0->unk8(arg0->unk4) != 0)) {
        arg0->unk8 = NULL;
    }
    return var_r25;
}

s32 fn_1_B0B8(M515Seq *arg0, M515Player *arg1) {
    f32 sp8[4];
    HU3DMODEL *temp_r29;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    M515Main *temp_r30;

    temp_r30 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) arg1->unk482 == 3) {
            if (fn_1_6324(arg1, (M515Main *) temp_r30) != 0) {
                arg0->unk0 += 1;
            }
        } else {
            var_r26 = 0;
            arg1->unk484 += 1;
            if ((s16) arg1->unk484 >= 0xF) {
                arg1->unk484 = 0xF;
                arg1->unk464.x = arg1->unk470.x;
                arg1->unk464.y = arg1->unk470.y;
                arg1->unk464.z = arg1->unk470.z;
                var_r26 = 1;
            }
            temp_f31 = (f32) arg1->unk484 / 15.0f;
            arg1->unk44C.x = ((1.0f - temp_f31) * arg1->unk464.x) + (temp_f31 * arg1->unk470.x);
            arg1->unk44C.y = ((1.0f - temp_f31) * arg1->unk464.y) + (temp_f31 * arg1->unk470.y);
            arg1->unk44C.z = ((1.0f - temp_f31) * arg1->unk464.z) + (temp_f31 * arg1->unk470.z);
            var_r25 = 0;
            sp8[0] = lbl_1_rodata_148[0];
            sp8[1] = lbl_1_rodata_148[1];
            sp8[2] = lbl_1_rodata_148[2];
            sp8[3] = lbl_1_rodata_148[3];
            arg1->unk486 += 1;
            if ((s16) arg1->unk486 >= 5) {
                arg1->unk486 = 5;
                arg1->unk47C = arg1->unk47E;
                var_r25 = 1;
            }
            if ((((s16) arg1->unk47C == 2) && ((s16) arg1->unk47E == 3)) || (((s16) arg1->unk47C == 3) && ((s16) arg1->unk47E == 2))) {
                sp8[3] += 360.0f;
            }
            if ((s16) arg1->unkE == 1) {
                if ((((s16) arg1->unk47C == 0) && ((s16) arg1->unk47E == 3)) || (((s16) arg1->unk47C == 3) && ((s16) arg1->unk47E == 0))) {
                    sp8[3] += 360.0f;
                }
            } else if ((((s16) arg1->unk47C == 2) && ((s16) arg1->unk47E == 1)) || (((s16) arg1->unk47C == 1) && ((s16) arg1->unk47E == 2))) {
                sp8[1] += 360.0f;
            }
            temp_f30 = (f32) arg1->unk486 / 5.0f;
            arg1->unk458.y = ((1.0f - temp_f30) * sp8[arg1->unk47C]) + (temp_f30 * sp8[arg1->unk47E]);
            if ((var_r26 != 0) && (var_r25 != 0)) {
                arg0->unk0 += 1;
            }
            Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
        }
        omSetTra(arg1->unk68C, arg1->unk44C.x, arg1->unk44C.y, arg1->unk44C.z);
        omSetRot(arg1->unk68C, arg1->unk458.x, arg1->unk458.y, arg1->unk458.z);
        break;
    case 1:
        if (((s16) *arg1->unk68C->motion != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) *arg1->unk68C->motion != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
            Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
        }
        break;
    }
    if ((u32) (Hu3DModelAttrGet(temp_r30->unkCE[arg1->unk0]) & 1) == 0) {
        temp_r29 = &Hu3DData[temp_r30->unkCE[arg1->unk0]];
        if (temp_r29->motShapeWork.time >= temp_r29->motShapeWork.end) {
            temp_r29->motShapeWork.time = temp_r29->motShapeWork.end;
            Hu3DModelAttrSet(temp_r30->unkCE[arg1->unk0], 1U);
        }
    }
    var_r27 = 0;
loop_40:
    if (var_r27 < (s16) arg1->unk5E8) {
        fn_1_7BE8(&arg1->unk488[var_r27], (M515Main *) temp_r30);
        var_r27 += 1;
        goto loop_40;
    }
    return 0;
}

s32 fn_1_B5D8(M515Seq *arg0, M515Player *arg1) {
    f32 sp8[4];
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    M515Main *temp_r25;

    temp_r25 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DMotionShiftSet(*arg1->unk68C->model, arg1->unk68C->motion[2], 0.0f, 5.0f, 0x40000001U);
        arg0->unk0 += 1;
        /* fallthrough */
    case 1:
        var_r28 = 0;
        arg1->unk484 += 1;
        if ((s16) arg1->unk484 >= 0xF) {
            arg1->unk484 = 0xF;
            arg1->unk464.x = arg1->unk470.x;
            arg1->unk464.y = arg1->unk470.y;
            arg1->unk464.z = arg1->unk470.z;
            var_r28 = 1;
        }
        temp_f31 = (f32) arg1->unk484 / 15.0f;
        arg1->unk44C.x = ((1.0f - temp_f31) * arg1->unk464.x) + (temp_f31 * arg1->unk470.x);
        arg1->unk44C.y = ((1.0f - temp_f31) * arg1->unk464.y) + (temp_f31 * arg1->unk470.y);
        arg1->unk44C.z = ((1.0f - temp_f31) * arg1->unk464.z) + (temp_f31 * arg1->unk470.z);
        var_r27 = 0;
        sp8[0] = lbl_1_rodata_148[0];
        sp8[1] = lbl_1_rodata_148[1];
        sp8[2] = lbl_1_rodata_148[2];
        sp8[3] = lbl_1_rodata_148[3];
        arg1->unk486 += 1;
        if ((s16) arg1->unk486 >= 5) {
            arg1->unk486 = 5;
            arg1->unk47C = arg1->unk47E;
            var_r27 = 1;
        }
        if ((((s16) arg1->unk47C == 2) && ((s16) arg1->unk47E == 3)) || (((s16) arg1->unk47C == 3) && ((s16) arg1->unk47E == 2))) {
            sp8[3] += 360.0f;
        }
        if ((s16) arg1->unkE == 1) {
            if ((((s16) arg1->unk47C == 0) && ((s16) arg1->unk47E == 3)) || (((s16) arg1->unk47C == 3) && ((s16) arg1->unk47E == 0))) {
                sp8[3] += 360.0f;
            }
        } else if ((((s16) arg1->unk47C == 2) && ((s16) arg1->unk47E == 1)) || (((s16) arg1->unk47C == 1) && ((s16) arg1->unk47E == 2))) {
            sp8[1] += 360.0f;
        }
        temp_f30 = (f32) arg1->unk486 / 5.0f;
        arg1->unk458.y = ((1.0f - temp_f30) * sp8[arg1->unk47C]) + (temp_f30 * sp8[arg1->unk47E]);
        if ((var_r28 != 0) && (var_r27 != 0)) {
            if (((s16) *arg1->unk68C->motion != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) *arg1->unk68C->motion != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
                Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
            }
            arg0->unk0 += 1;
        }
        omSetTra(arg1->unk68C, arg1->unk44C.x, arg1->unk44C.y, arg1->unk44C.z);
        omSetRot(arg1->unk68C, arg1->unk458.x, arg1->unk458.y, arg1->unk458.z);
        break;
    }
    var_r29 = 0;
loop_35:
    if (var_r29 < (s16) arg1->unk5E8) {
        fn_1_7BE8(&arg1->unk488[var_r29], (M515Main *) temp_r25);
        var_r29 += 1;
        goto loop_35;
    }
    return 0;
}

s32 fn_1_BA64(M515Seq *arg0, M515Player *arg1) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r28;
    M515Main *temp_r29;

    temp_r29 = lbl_1_bss_4->data;
    temp_r0 = arg0->unk0;
    switch (temp_r0) {                              /* irregular */
    case 2:
        Hu3DMotionShiftSet(*arg1->unk68C->model, arg1->unk68C->motion[1], 0.0f, 5.0f, 0x40000001U);
        arg1->unk470.z = -900.0f;
        arg0->unk8 = fn_1_9594;
        arg0->unk2 = 0;
        arg0->unk0 += 1;
        /* fallthrough */
    case 3:
        arg0->unk2 += 1;
        if ((s16) arg0->unk2 >= 0x87) {
            arg0->unk0 += 1;
        }
        if ((s16) arg0->unk2 == 0x32) {
            Hu3DMotionSet(temp_r29->unkAE[arg1->unk0], temp_r29->unk106);
            Hu3DMotionTimeSet(temp_r29->unkAE[arg1->unk0], 0.0f);
            Hu3DModelAttrReset(temp_r29->unkAE[arg1->unk0], 0x40000002U);
        }
        temp_f31 = (f32) arg0->unk2 / 135.0f;
        arg1->unk44C.x = ((1.0f - temp_f31) * arg1->unk464.x) + (temp_f31 * arg1->unk470.x);
        arg1->unk44C.y = ((1.0f - temp_f31) * arg1->unk464.y) + (temp_f31 * arg1->unk470.y);
        arg1->unk44C.z = ((1.0f - temp_f31) * arg1->unk464.z) + (temp_f31 * arg1->unk470.z);
        omSetRot(arg1->unk68C, arg1->unk458.x, arg1->unk458.y, arg1->unk458.z);
        omSetTra(arg1->unk68C, arg1->unk44C.x, arg1->unk44C.y, arg1->unk44C.z);
        break;
    }
    var_r28 = 0;
loop_13:
    if (var_r28 < (s16) arg1->unk5E8) {
        fn_1_7BE8(&arg1->unk488[var_r28], (M515Main *) temp_r29);
        var_r28 += 1;
        goto loop_13;
    }
    if ((((s32 (*)(M515Cam *)) arg0->unk8) != NULL) && (arg0->unk8(arg0->unk4) != 0)) {
        arg0->unk8 = NULL;
    }
    return 0;
}

f32 fn_1_BD10(s16 mdl, s16 side, f32 t) {
    f32 sp18[2];
    f32 sp10[2];
    f32 spC;
    s16 sp8;
    f32 temp_f30;
    f32 var_f31;

    sp8 = mdl;
    spC = t;
    sp18[0] = lbl_1_rodata_24C[0];
    sp18[1] = lbl_1_rodata_24C[1];
    sp10[0] = lbl_1_rodata_254[0];
    sp10[1] = lbl_1_rodata_254[1];
    var_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * spC)) / 180.0))));
    if (var_f31 > 1.0f) {
        var_f31 = 1.0f;
    }
    temp_f30 = ((1.0f - var_f31) * sp18[side]) + (var_f31 * sp10[side]);
    Hu3DModelPosSet(sp8, 0.0f, temp_f30, 0.0f);
    return temp_f30;
}

void fn_1_BE78(M515Main *arg0, s16 mdl, s16 arg2) {
    M515Fx *temp_r31;

    temp_r31 = arg0->unk348;
    if (temp_r31 != NULL) {
        arg0->unk348 = temp_r31->unk10;
        temp_r31->unk0 = -1;
        temp_r31->unk2 = -1;
        temp_r31->unk4 = 0;
        temp_r31->unk10 = arg0->unk344;
        if ((M515Fx *) temp_r31->unk10 != NULL) {
            temp_r31->unk10->unkC = temp_r31;
        }
        arg0->unk344 = temp_r31;
    }
    if (temp_r31 != NULL) {
        if (arg2 != 0) {
            temp_r31->unk8 = fn_1_BFD0;
        } else {
            temp_r31->unk8 = fn_1_C0D0;
        }
        temp_r31->unk0 = mdl;
    }
}

void fn_1_BF24(M515Main *arg0, s16 mdl, s16 arg2) {
    M515Fx *temp_r31;

    temp_r31 = arg0->unk348;
    if (temp_r31 != NULL) {
        arg0->unk348 = temp_r31->unk10;
        temp_r31->unk0 = -1;
        temp_r31->unk2 = -1;
        temp_r31->unk4 = 0;
        temp_r31->unk10 = arg0->unk344;
        if ((M515Fx *) temp_r31->unk10 != NULL) {
            temp_r31->unk10->unkC = temp_r31;
        }
        arg0->unk344 = temp_r31;
    }
    if (temp_r31 != NULL) {
        if (arg2 != 0) {
            temp_r31->unk8 = fn_1_C150;
        } else {
            temp_r31->unk8 = fn_1_C26C;
        }
        temp_r31->unk0 = mdl;
    }
}

s32 fn_1_BFD0(M515Fx *arg0) {
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = arg0->unk4;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) arg0->unk0 >= 0) {
            Hu3DModelAttrReset(arg0->unk0, 1U);
            arg0->unk2 = Hu3DMotionIDGet(arg0->unk0);
            if ((s16) arg0->unk2 >= 0) {
                Hu3DMotionTimeSet(arg0->unk0, Hu3DMotionMaxTimeGet(arg0->unk0) - 1.0f);
                Hu3DModelAttrSet(arg0->unk0, 0x40000004U);
                Hu3DModelAttrReset(arg0->unk0, 0x40000002U);
                arg0->unk4 += 1;
            } else {
                var_r30 = 1;
            }
        } else {
            var_r30 = 1;
        }
        break;
    case 1:
        if (Hu3DMotionEndCheck(arg0->unk0) != 0) {
            var_r30 = fn_1_C0D0(arg0);
        }
        break;
    }
    return var_r30;
}

s32 fn_1_C0D0(M515Fx *arg0) {
    if ((s16) arg0->unk0 >= 0) {
        Hu3DModelAttrReset(arg0->unk0, 1U);
        arg0->unk2 = Hu3DMotionIDGet(arg0->unk0);
        if ((s16) arg0->unk2 >= 0) {
            Hu3DMotionTimeSet(arg0->unk0, 0.0f);
            Hu3DModelAttrSet(arg0->unk0, 0x40000002U);
        }
    }
    return 1;
}

s32 fn_1_C150(M515Fx *arg0) {
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = arg0->unk4;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) arg0->unk0 >= 0) {
            arg0->unk2 = Hu3DMotionIDGet(arg0->unk0);
            if ((s16) arg0->unk2 >= 0) {
                Hu3DMotionTimeSet(arg0->unk0, 0.0f);
                Hu3DModelAttrReset(arg0->unk0, 0x40000004U);
                Hu3DModelAttrReset(arg0->unk0, 0x40000002U);
                arg0->unk4 += 1;
            } else {
                Hu3DModelAttrSet(arg0->unk0, 1U);
                var_r30 = 1;
            }
        } else {
            var_r30 = 1;
        }
        break;
    case 1:
        if (Hu3DMotionEndCheck(arg0->unk0) != 0) {
            arg0->unk4 += 1;
        }
        break;
    case 2:
        Hu3DModelAttrSet(arg0->unk0, 1U);
        var_r30 = fn_1_C26C(arg0);
        break;
    }
    return var_r30;
}

s32 fn_1_C26C(M515Fx *arg0) {
    if ((s16) arg0->unk0 >= 0) {
        Hu3DModelAttrSet(arg0->unk0, 1U);
    }
    return 1;
}

void fn_1_C2B0(M515Player *arg0) {
    f32 sp8[4];
    f32 temp_f31;
    f32 temp_f31_2;
    s32 var_r24;
    s32 var_r25;
    s32 var_r27;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r30;
    u16 *var_r26;
    u16 *var_r26_2;
    u16 temp_r4;
    u16 temp_r4_2;
    M515Main *temp_r23;
    Vec *temp_r4_3;
    Vec *temp_r4_4;
    M515Obj *temp_r5;
    M515Obj *temp_r5_2;

    temp_r23 = lbl_1_bss_4->data;
    if ((s16) arg0->unkE == 1) {
        var_r26 = lbl_1_data_10BC[temp_r23->unk2[arg0->unkE]];
        temp_f31 = 400.0f * (f32) arg0->unkE;
        var_r28 = 4;
loop_6:
        if (var_r28 >= 0) {
            var_r27 = 4;
loop_4:
            if (var_r27 >= 0) {
                temp_r4 = *var_r26;
                var_r26++;
                arg0->unk10[(var_r28) * 5 + (var_r27)].unk24 = temp_r4;
                arg0->unk10[(var_r28) * 5 + (var_r27)].unk18.y = temp_f31;
                var_r27 -= 1;
                goto loop_4;
            }
            var_r28 -= 1;
            goto loop_6;
        }
        arg0->unk3F8 = &arg0->unk424;
        arg0->unk3FC.unk24 = 4;
        arg0->unk3FC.unk18.y = 25.0f + temp_f31;
        arg0->unk424.unk24 = 3;
        arg0->unk424.unk18.y = 25.0f + temp_f31;
        var_r25 = 0;
loop_11:
        if (var_r25 < 0x19) {
            if ((s16) arg0->unk5EA[25 + var_r25] >= 0) {
                Hu3DModelAttrReset(arg0->unk5EA[25 + var_r25], 1U);
            }
            var_r25 += 1;
            goto loop_11;
        }
    } else {
        var_r26_2 = lbl_1_data_10E4[temp_r23->unk2[arg0->unkE]];
        temp_f31_2 = 400.0f * (f32) arg0->unkE;
        var_r28_2 = 0;
loop_18:
        if (var_r28_2 < 5) {
            var_r27_2 = 0;
loop_16:
            if (var_r27_2 < 5) {
                temp_r4_2 = *var_r26_2;
                var_r26_2++;
                arg0->unk10[(var_r28_2) * 5 + (var_r27_2)].unk24 = temp_r4_2;
                arg0->unk10[(var_r28_2) * 5 + (var_r27_2)].unk18.y = temp_f31_2;
                var_r27_2 += 1;
                goto loop_16;
            }
            var_r28_2 += 1;
            goto loop_18;
        }
        arg0->unk3F8 = &arg0->unk3FC;
        arg0->unk3FC.unk24 = 3;
        arg0->unk3FC.unk18.y = 25.0f + temp_f31_2;
        arg0->unk424.unk24 = 4;
        arg0->unk424.unk18.y = 25.0f + temp_f31_2;
        var_r24 = 0;
loop_23:
        if (var_r24 < 0x19) {
            if ((s16) arg0->unk5EA[50 + var_r24] >= 0) {
                Hu3DModelAttrReset(arg0->unk5EA[50 + var_r24], 1U);
            }
            var_r24 += 1;
            goto loop_23;
        }
    }
    sp8[0] = lbl_1_rodata_194[0];
    sp8[1] = lbl_1_rodata_194[1];
    sp8[2] = lbl_1_rodata_194[2];
    sp8[3] = lbl_1_rodata_194[3];
    arg0->unk5E8 = 0;
    var_r29 = 0;
loop_31:
    if (var_r29 < 5) {
        var_r30 = 0;
loop_29:
        if (var_r30 < 5) {
            if ((u16) arg0->unk10[(var_r29) * 5 + (var_r30)].unk24 == 2) {
                arg0->unk10[(var_r29) * 5 + (var_r30)].unk14 = &arg0->unk488[arg0->unk5E8];
                arg0->unk5E8 += 1;
                temp_r5 = arg0->unk10[(var_r29) * 5 + (var_r30)].unk14;
                temp_r4_3 = &arg0->unk10[(var_r29) * 5 + (var_r30)].unk18;
                temp_r5->unk8.x = (s32) temp_r4_3->x;
                temp_r5->unk8.y = (s32) temp_r4_3->y;
                temp_r5->unk8.z = (s32) temp_r4_3->z;
                temp_r5_2 = arg0->unk10[(var_r29) * 5 + (var_r30)].unk14;
                temp_r4_4 = &arg0->unk10[(var_r29) * 5 + (var_r30)].unk18;
                temp_r5_2->unk14.x = (s32) temp_r4_4->x;
                temp_r5_2->unk14.y = (s32) temp_r4_4->y;
                temp_r5_2->unk14.z = (s32) temp_r4_4->z;
                arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk24 = (s16) (rand8() / 64);
                Hu3DModelAttrReset(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.x, 1.0f + arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.y, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.z);
                Hu3DModelRotSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, 0.0f, sp8[arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk24], 0.0f);
                Hu3DModelAttrReset(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk4, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk4, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.x, 0.5f + arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.y, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.z);
            }
            var_r30 += 1;
            goto loop_29;
        }
        var_r29 += 1;
        goto loop_31;
    }
    fn_1_E274(&arg0->unk690, arg0->unkE, arg0->unkC);
}

void fn_1_C83C(void) {
    Hu3DShadowMultiCreate(15.0f, 20.0f, 12000.0f, (s16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DShadowMultiTPLvlSet(0.3f, (s16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
    Hu3DShadowMultiSizeSet(0x18U, (s16) (lbl_1_rodata_10[3] | (lbl_1_rodata_10[2] | (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]))));
}

void fn_1_C958(s32 arg0, Vec *arg1, s32 arg2) {
    Vec sp4C;
    Vec sp34;
    Vec sp40;
    Vec sp28;
    Vec sp1C;
    Vec sp10;
    s32 spC;
    s32 sp8;

    sp8 = arg0;
    spC = arg2;
    sp4C.x = lbl_1_rodata_260.x;
    sp4C.y = lbl_1_rodata_260.y;
    sp4C.z = lbl_1_rodata_260.z;
    sp40.x = arg1->x;
    sp40.y = arg1->y;
    sp40.z = arg1->z;
    if (spC != 0) {
        sp34.x = arg1->x;
        sp34.y = 800.0f + arg1->y;
        sp34.z = arg1->z - 2400.0f;
    } else {
        sp34.x = arg1->x;
        sp34.y = 1200.0f + arg1->y;
        sp34.z = arg1->z;
    }
    VECSubtract(&sp40, &sp34, &sp10);
    VECNormalize(&sp10, &sp10);
    if ((sp10.x == 0.0f) && (sp10.z == 0.0f)) {
        sp10.z = 0.0001f;
    }
    VECCrossProduct(&sp4C, &sp10, &sp28);
    VECNormalize(&sp28, &sp28);
    VECCrossProduct(&sp10, &sp28, &sp1C);
    VECNormalize(&sp1C, &sp1C);
    Hu3DShadowMultiPosSet(&sp34, &sp1C, &sp40, (s16) lbl_1_rodata_10[sp8]);
}

void fn_1_CAF0(M515Main *arg0, s32 arg1) {
    Hu3DModelAttrReset(arg0->unkB6[arg1 * 3 + 0], 1U);
    Hu3DModelAttrReset(arg0->unk26[arg1], 1U);
    Hu3DModelAttrReset(arg0->unkA6[arg1], 1U);
}

void fn_1_CB60(M515Main *arg0, s32 arg1) {
    Hu3DModelAttrReset(arg0->unkB6[arg1 * 3 + 0], 1U);
    Hu3DModelAttrReset(arg0->unk16[arg1], 1U);
    Hu3DModelAttrReset(arg0->unk1E[arg1], 1U);
    Hu3DModelAttrReset(arg0->unk96[arg1 * 2 + 0], 1U);
    Hu3DModelAttrReset(arg0->unk76[arg1 * 4 + 0], 1U);
    Hu3DModelAttrReset(arg0->unk76[arg1 * 4 + 1], 1U);
    Hu3DModelAttrReset(arg0->unkA6[arg1], 1U);
}

void fn_1_CC20(s16 layerNo) {
    s32 var_r27;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    M515Main *temp_r29;
    M515Player *temp_r30;
    M515Player *temp_r30_2;

    temp_r29 = lbl_1_bss_4->data;
    if ((s32) (omUPauseFlag + omPauseChk()) != 0) {
        if ((s16) temp_r29->unk1D8 == 0) {
            temp_r29->unk1D8 = 1;
            var_r28 = 0;
loop_16:
            if (var_r28 < 4) {
                temp_r30 = temp_r29->unk224[var_r28];
                var_r31 = 0;
loop_11:
                if (var_r31 < 3) {
                    if ((u32) (Hu3DModelAttrGet(temp_r29->unkB6[var_r28 * 3 + var_r31]) & 1) == 0) {
                        temp_r29->unk1DC[var_r28 * 3 + var_r31] = 1;
                        var_r27 = 0;
loop_9:
                        if (var_r27 < 0x19) {
                            if ((s16) temp_r30->unk5EA[var_r31 * 25 + var_r27] >= 0) {
                                Hu3DModelAttrSet(temp_r30->unk5EA[var_r31 * 25 + var_r27], 1U);
                            }
                            var_r27 += 1;
                            goto loop_9;
                        }
                    }
                    var_r31 += 1;
                    goto loop_11;
                }
                var_r31_2 = 0;
loop_14:
                if (var_r31_2 < (s16) temp_r30->unk5E8) {
                    Hu3DModelAttrSet(temp_r30->unk488[var_r31_2].unk0, 1U);
                    Hu3DModelAttrSet(temp_r30->unk488[var_r31_2].unk4, 1U);
                    var_r31_2 += 1;
                    goto loop_14;
                }
                var_r28 += 1;
                goto loop_16;
            }
        }
    } else if ((s16) temp_r29->unk1D8 != 0) {
        temp_r29->unk1D8 = 0;
        var_r28_2 = 0;
loop_33:
        if (var_r28_2 < 4) {
            temp_r30_2 = temp_r29->unk224[var_r28_2];
            var_r31_3 = 0;
loop_28:
            if (var_r31_3 < 3) {
                if ((s16) temp_r29->unk1DC[var_r28_2 * 3 + var_r31_3] != 0) {
                    temp_r29->unk1DC[var_r28_2 * 3 + var_r31_3] = 0;
                    var_r27_2 = 0;
loop_26:
                    if (var_r27_2 < 0x19) {
                        if ((s16) temp_r30_2->unk5EA[var_r31_3 * 25 + var_r27_2] >= 0) {
                            Hu3DModelAttrReset(temp_r30_2->unk5EA[var_r31_3 * 25 + var_r27_2], 1U);
                        }
                        var_r27_2 += 1;
                        goto loop_26;
                    }
                }
                var_r31_3 += 1;
                goto loop_28;
            }
            var_r31_4 = 0;
loop_31:
            if (var_r31_4 < (s16) temp_r30_2->unk5E8) {
                Hu3DModelAttrReset(temp_r30_2->unk488[var_r31_4].unk0, 1U);
                Hu3DModelAttrReset(temp_r30_2->unk488[var_r31_4].unk4, 1U);
                var_r31_4 += 1;
                goto loop_31;
            }
            var_r28_2 += 1;
            goto loop_33;
        }
    }
}

void fn_1_CE98(M515Main *arg0) {
    f32 sp18[16];
    s32 sp8[4];
    M515Player *temp_r29;
    s32 var_r30;

    sp18[4] = lbl_1_rodata_27C->x;
    sp18[5] = lbl_1_rodata_27C->y;
    sp18[6] = lbl_1_rodata_27C->z;
    sp18[7] = lbl_1_rodata_27C[1].x;
    sp18[8] = lbl_1_rodata_27C[1].y;
    sp18[9] = lbl_1_rodata_27C[1].z;
    sp18[10] = lbl_1_rodata_27C[2].x;
    sp18[11] = lbl_1_rodata_27C[2].y;
    sp18[12] = lbl_1_rodata_27C[2].z;
    sp18[13] = lbl_1_rodata_27C[3].x;
    sp18[14] = lbl_1_rodata_27C[3].y;
    sp18[15] = lbl_1_rodata_27C[3].z;
    sp18[0] = lbl_1_rodata_2AC[0];
    sp18[1] = lbl_1_rodata_2AC[1];
    sp18[2] = lbl_1_rodata_2AC[2];
    sp18[3] = lbl_1_rodata_2AC[3];
    sp8[0] = lbl_1_rodata_2BC[0];
    sp8[1] = lbl_1_rodata_2BC[1];
    sp8[2] = lbl_1_rodata_2BC[2];
    sp8[3] = lbl_1_rodata_2BC[3];
    temp_r29 = arg0->unk224[0];
    var_r30 = 0;
loop_2:
    if (var_r30 < 4) {
        arg0->unk130[var_r30].unkC = temp_r29->unk488[var_r30 + 2].unk0;
        Hu3DModelAttrReset(arg0->unk130[var_r30].unkC, 1U);
        Hu3DModelPosSet(arg0->unk130[var_r30].unkC, sp18[4 + var_r30 * 3], sp18[5 + var_r30 * 3], sp18[6 + var_r30 * 3]);
        Hu3DModelRotSet(arg0->unk130[var_r30].unkC, 0.0f, 0.0f, 0.0f);
        arg0->unk130[var_r30].unk10 = 0.0f;
        arg0->unk130[var_r30].unk18 = sp18[var_r30];
        arg0->unk130[var_r30].unk0 = 0;
        arg0->unk130[var_r30].unk4 = sp8[var_r30];
        arg0->unk130[var_r30].unk8 = 0;
        memcpy(&arg0->unk130[var_r30].unk1C, &sp18[4 + var_r30 * 3], 0xC);
        var_r30 += 1;
        goto loop_2;
    }
}

void fn_1_D0D8(M515Main *arg0) {
    f32 temp_f30;
    f32 var_f31;
    s32 temp_r0;
    s32 var_r30;

    var_r30 = 0;
loop_16:
    if (var_r30 < 4) {
        temp_r0 = arg0->unk130[var_r30].unk0;
        switch (temp_r0) {                          /* irregular */
        case 1:
            arg0->unk130[var_r30].unk8 += 1;
            if ((s32) arg0->unk130[var_r30].unk8 >= (s32) arg0->unk130[var_r30].unk4) {
                arg0->unk130[var_r30].unk0 += 1;
            }
            temp_f30 = (f32) arg0->unk130[var_r30].unk8 / (f32) arg0->unk130[var_r30].unk4;
            if (var_r30 < 2) {
                var_f31 = (f32) (180.0 * (f64) temp_f30);
            } else {
                var_f31 = -180.0f * temp_f30;
            }
            Hu3DModelRotSet(arg0->unk130[var_r30].unkC, 0.0f, var_f31, 0.0f);
            break;
        case 2:
            arg0->unk130[var_r30].unk1C.z -= 6.0f;
            break;
        }
        arg0->unk130[var_r30].unk10 += arg0->unk130[var_r30].unk18;
        if (arg0->unk130[var_r30].unk10 > 360.0f) {
            arg0->unk130[var_r30].unk10 -= 360.0f;
        }
        Hu3DModelPosSet(arg0->unk130[var_r30].unkC, arg0->unk130[var_r30].unk1C.x, (f32) ((f64) arg0->unk130[var_r30].unk1C.y + (3.0 * sin((3.141592653589793 * (f64) arg0->unk130[var_r30].unk10) / 180.0))), arg0->unk130[var_r30].unk1C.z);
        var_r30 += 1;
        goto loop_16;
    }
}

void fn_1_D384(M515Player *arg0) {
    f32 sp8[4];
    M515Node *temp_r4_3;
    M515Node *temp_r4_4;
    M515Node *temp_r4_5;
    f32 var_f31;
    s16 var_r23;
    s32 var_r26;
    s32 var_r27;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r30;
    u16 *var_r25;
    u16 *var_r25_2;
    u16 temp_r4;
    u16 temp_r4_2;
    M515Main *temp_r22;
    M515Main *temp_r24;
    Vec *temp_r4_6;
    Vec *temp_r4_7;
    M515Obj *temp_r5;
    M515Obj *temp_r5_2;

    temp_r24 = lbl_1_bss_4->data;
    if ((s16) arg0->unkE == 1) {
        var_r25 = lbl_1_data_10BC[temp_r24->unk2[arg0->unkE]];
        var_r28 = 4;
loop_6:
        if (var_r28 >= 0) {
            var_r27 = 4;
loop_4:
            if (var_r27 >= 0) {
                temp_r4 = *var_r25;
                var_r25++;
                arg0->unk10[(var_r28) * 5 + (var_r27)].unk24 = temp_r4;
                var_r27 -= 1;
                goto loop_4;
            }
            var_r28 -= 1;
            goto loop_6;
        }
        arg0->unk3F8 = &arg0->unk424;
        var_f31 = 0.0f;
        var_r23 = 3;
    } else {
        if ((s16) arg0->unkE == 0) {
            var_r25_2 = lbl_1_data_1094[temp_r24->unk2[arg0->unkE]];
        } else {
            var_r25_2 = lbl_1_data_10E4[temp_r24->unk2[arg0->unkE]];
        }
        var_r28_2 = 0;
loop_16:
        if (var_r28_2 < 5) {
            var_r27_2 = 0;
loop_14:
            if (var_r27_2 < 5) {
                temp_r4_2 = *var_r25_2;
                var_r25_2++;
                arg0->unk10[(var_r28_2) * 5 + (var_r27_2)].unk24 = temp_r4_2;
                var_r27_2 += 1;
                goto loop_14;
            }
            var_r28_2 += 1;
            goto loop_16;
        }
        arg0->unk3F8 = &arg0->unk3FC;
        var_f31 = 180.0f;
        var_r23 = 0;
    }
    temp_r4_3 = arg0->unk3F8;
    arg0->unk44C.x = temp_r4_3->unk18.x;
    arg0->unk44C.y = temp_r4_3->unk18.y;
    arg0->unk44C.z = temp_r4_3->unk18.z;
    arg0->unk458.x = 0.0f;
    arg0->unk458.y = var_f31;
    arg0->unk458.z = 0.0f;
    arg0->unk484 = 0xF;
    arg0->unk486 = 5;
    arg0->unk480 = 0;
    arg0->unk47C = var_r23;
    arg0->unk47E = var_r23;
    temp_r4_4 = arg0->unk3F8;
    arg0->unk464.x = temp_r4_4->unk18.x;
    arg0->unk464.y = temp_r4_4->unk18.y;
    arg0->unk464.z = temp_r4_4->unk18.z;
    temp_r4_5 = arg0->unk3F8;
    arg0->unk470.x = temp_r4_5->unk18.x;
    arg0->unk470.y = temp_r4_5->unk18.y;
    arg0->unk470.z = temp_r4_5->unk18.z;
    omSetTra(arg0->unk68C, arg0->unk44C.x, arg0->unk44C.y, arg0->unk44C.z);
    omSetRot(arg0->unk68C, arg0->unk458.x, arg0->unk458.y, arg0->unk458.z);
    temp_r22 = lbl_1_bss_4->data;
    var_r26 = 0;
loop_20:
    if (var_r26 < 8) {
        Hu3DModelAttrSet(arg0->unk488[var_r26].unk0, 1U);
        Hu3DMotionSet(arg0->unk488[var_r26].unk0, temp_r22->unkE0[4]);
        Hu3DMotionTimeSet(arg0->unk488[var_r26].unk0, 0.0f);
        Hu3DModelAttrSet(arg0->unk488[var_r26].unk0, 0x40000002U);
        Hu3DModelAttrSet(arg0->unk488[var_r26].unk4, 1U);
        var_r26 += 1;
        goto loop_20;
    }
    sp8[0] = lbl_1_rodata_194[0];
    sp8[1] = lbl_1_rodata_194[1];
    sp8[2] = lbl_1_rodata_194[2];
    sp8[3] = lbl_1_rodata_194[3];
    arg0->unk5E8 = 0;
    var_r29 = 0;
loop_28:
    if (var_r29 < 5) {
        var_r30 = 0;
loop_26:
        if (var_r30 < 5) {
            if ((u16) arg0->unk10[(var_r29) * 5 + (var_r30)].unk24 == 2) {
                arg0->unk10[(var_r29) * 5 + (var_r30)].unk14 = &arg0->unk488[arg0->unk5E8];
                arg0->unk5E8 += 1;
                temp_r5 = arg0->unk10[(var_r29) * 5 + (var_r30)].unk14;
                temp_r4_6 = &arg0->unk10[(var_r29) * 5 + (var_r30)].unk18;
                temp_r5->unk8.x = (s32) temp_r4_6->x;
                temp_r5->unk8.y = (s32) temp_r4_6->y;
                temp_r5->unk8.z = (s32) temp_r4_6->z;
                temp_r5_2 = arg0->unk10[(var_r29) * 5 + (var_r30)].unk14;
                temp_r4_7 = &arg0->unk10[(var_r29) * 5 + (var_r30)].unk18;
                temp_r5_2->unk14.x = (s32) temp_r4_7->x;
                temp_r5_2->unk14.y = (s32) temp_r4_7->y;
                temp_r5_2->unk14.z = (s32) temp_r4_7->z;
                arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk24 = (s16) (rand8() / 64);
                Hu3DModelAttrReset(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.x, 1.0f + arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.y, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.z);
                Hu3DModelRotSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk0, 0.0f, sp8[arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk24], 0.0f);
                Hu3DModelAttrReset(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk4, 1U);
                Hu3DModelPosSet(arg0->unk10[(var_r29) * 5 + (var_r30)].unk14->unk4, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.x, 0.5f + arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.y, arg0->unk10[(var_r29) * 5 + (var_r30)].unk18.z);
            }
            var_r30 += 1;
            goto loop_26;
        }
        var_r29 += 1;
        goto loop_28;
    }
}

s32 fn_1_D928(M515Seq *arg0, M515Player *arg1) {
    M515Cam *temp_r30;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f31;
    f64 temp_f28;
    f64 temp_f28_2;
    s16 temp_r0;
    s32 var_r27;
    M515Main *temp_r28;

    var_r27 = 0;
    temp_r28 = lbl_1_bss_4->data;
    arg1->unk680 = 0;
    temp_r30 = arg0->unk4;
    temp_r0 = arg0->unk0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(temp_r28->unkCE[arg1->unk0], 1U);
        Hu3DModelAttrReset(temp_r28->unkCE[arg1->unk0], 0x40000080U);
        Hu3DMotionShapeTimeSet(temp_r28->unkCE[arg1->unk0], 0.0f);
        if (((s16) *arg1->unk68C->motion != Hu3DMotionIDGet(*arg1->unk68C->model)) && ((s16) *arg1->unk68C->motion != Hu3DMotionShiftIDGet(*arg1->unk68C->model))) {
            Hu3DMotionShiftSet(*arg1->unk68C->model, *arg1->unk68C->motion, 0.0f, 5.0f, 0x40000001U);
        }
        arg0->unk2 = 0;
        arg0->unk0 += 1;
        break;
    case 1:
        arg0->unk2 += 1;
        if ((s16) arg0->unk2 == 0x2D) {
            fn_1_D384(arg1);
            fn_1_81A8(arg0->unk4, arg1);
        }
        if ((s16) arg0->unk2 >= 0x5A) {
            fn_1_E274(&arg1->unk690, arg1->unkE, arg1->unkC);
            Hu3DModelAttrSet(temp_r28->unkCE[arg1->unk0], 1U);
            arg0->unk0 = 0;
            arg0->unk2 = 0;
            var_r27 = 1;
        }
        break;
    }
    temp_f28 = cos((3.141592653589793 * (f64) temp_r30->unk0) / 180.0);
    temp_f30 = (f32) ((f64) temp_r30->unkC.x + ((f64) (0.39f * temp_r30->unk8) * cos((3.141592653589793 * (f64) temp_r30->unk4) / 180.0) * temp_f28));
    temp_f31 = (f32) ((f64) temp_r30->unkC.y + ((f64) (0.39f * temp_r30->unk8) * sin((3.141592653589793 * (f64) temp_r30->unk4) / 180.0)));
    temp_f28_2 = sin((3.141592653589793 * (f64) temp_r30->unk0) / 180.0);
    temp_f29 = (f32) ((f64) temp_r30->unkC.z + ((f64) (0.39f * temp_r30->unk8) * cos((3.141592653589793 * (f64) temp_r30->unk4) / 180.0) * temp_f28_2));
    if ((s16) arg1->unk0 < 2) {
        var_f31 = temp_f31 + 8.0f;
    } else {
        var_f31 = temp_f31 - 8.0f;
    }
    Hu3DModelPosSet(temp_r28->unkCE[arg1->unk0], temp_f30, var_f31, temp_f29);
    Hu3DModelRotSet(temp_r28->unkCE[arg1->unk0], -temp_r30->unk4, 90.0f - temp_r30->unk0, 0.0f);
    return var_r27;
}

u16 fn_1_DD18(M515Player *arg0) {
    u16 sp30[4];
    u16 sp28[4];
    u16 sp20[4];
    u16 sp18[4];
    u16 sp8[8];
    s16 temp_r0;
    u16 var_r29;

    var_r29 = 0;
    sp30[0] = lbl_1_rodata_2E4[0];
    sp30[1] = lbl_1_rodata_2E4[1];
    sp30[2] = lbl_1_rodata_2E4[2];
    sp30[3] = lbl_1_rodata_2E4[3];
    sp28[0] = lbl_1_rodata_2EC[0];
    sp28[1] = lbl_1_rodata_2EC[1];
    sp28[2] = lbl_1_rodata_2EC[2];
    sp28[3] = lbl_1_rodata_2EC[3];
    sp20[0] = lbl_1_rodata_2F4[0];
    sp20[1] = lbl_1_rodata_2F4[1];
    sp20[2] = lbl_1_rodata_2F4[2];
    sp20[3] = lbl_1_rodata_2F4[3];
    sp18[0] = lbl_1_rodata_2FC[0];
    sp18[1] = lbl_1_rodata_2FC[1];
    sp18[2] = lbl_1_rodata_2FC[2];
    sp18[3] = lbl_1_rodata_2FC[3];
    sp8[4] = lbl_1_rodata_304[0];
    sp8[5] = lbl_1_rodata_304[1];
    sp8[6] = lbl_1_rodata_304[2];
    sp8[7] = lbl_1_rodata_304[3];
    sp8[0] = lbl_1_rodata_30C[0];
    sp8[1] = lbl_1_rodata_30C[1];
    sp8[2] = lbl_1_rodata_30C[2];
    sp8[3] = lbl_1_rodata_30C[3];
    temp_r0 = arg0->unk690.unk0;
    if ((u32) temp_r0 <= 0x1FU) {
        switch (temp_r0) {
        case 0:
            arg0->unk690.unk2 = 0;
            arg0->unk690.unk6 = 0;
            arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
            arg0->unk690.unk0 += 1;
            break;
        case 1:
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 > (s32) (arg0->unk690.unk8 + (s16) sp30[arg0->unkC])) {
                arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
                arg0->unk690.unk2 = 0;
                arg0->unk690.unk0 += 1;
            }
            break;
        case 2:
            if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x10) {
                arg0->unk690.unk0 = 0xA;
            } else if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x20) {
                arg0->unk690.unk0 = 0x14;
            } else {
                arg0->unk690.unk0 = 0x1E;
            }
            break;
        case 10:
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 >= (s32) (arg0->unk690.unk8 + (s16) sp28[arg0->unkC])) {
                arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
                arg0->unk690.unk0 = 0xB;
            case 11:
                var_r29 = arg0->unk690.unkC[arg0->unk690.unk6];
                arg0->unk690.unk0 = 0xC;
                arg0->unk690.unk2 = 0;
            }
            break;
        case 12:
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 >= (s32) (arg0->unk690.unk8 + (s16) sp20[arg0->unkC])) {
                arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
                arg0->unk690.unk6 += 1;
                if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x10) {
                    arg0->unk690.unk0 = 0xA;
                } else if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x20) {
                    arg0->unk690.unk0 = 0x14;
                } else {
                    arg0->unk690.unk0 = 0x1E;
                }
                arg0->unk690.unk2 = 0;
            }
            break;
        case 20:
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 >= (s32) (arg0->unk690.unk8 + (s16) sp18[arg0->unkC])) {
                arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
                var_r29 = arg0->unk690.unkC[arg0->unk690.unk6];
                arg0->unk690.unk0 = 0x15;
            }
            break;
        case 30:
            var_r29 = arg0->unk690.unkC[arg0->unk690.unk6];
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 >= 0xF) {
                arg0->unk690.unk6 += 1;
                if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x10) {
                    arg0->unk690.unk0 = 0xA;
                } else if ((u16) arg0->unk690.unkC[arg0->unk690.unk6] == 0x20) {
                    arg0->unk690.unk0 = 0x14;
                } else if (var_r29 == (u16) arg0->unk690.unkC[arg0->unk690.unk6]) {
                    arg0->unk690.unk0 = 0x1E;
                } else if ((s16) arg0->unkC >= 2) {
                    arg0->unk690.unk0 = 0x1E;
                } else {
                    arg0->unk690.unk0 = 0x1F;
                }
                arg0->unk690.unk2 = 0;
            }
            break;
        case 31:
            arg0->unk690.unk2 += 1;
            if ((s16) arg0->unk690.unk2 >= (s32) (arg0->unk690.unk8 + 0xF)) {
                arg0->unk690.unk8 = (s16) (rand8() / (s32) ((0xFF / (s16) sp8[arg0->unkC]) + 1));
                arg0->unk690.unk0 = 0x1E;
                arg0->unk690.unk2 = 0;
            }
            break;
        }
    }
    return var_r29;
}

void fn_1_E274(M515Com *arg0, s16 side, s16 dif) {
    u16 spA[4];
    s16 sp8;
    s16 var_r28;
    s16 var_r28_2;
    s16 var_r28_3;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    M515Main *temp_r31;

    sp8 = side;
    spA[0] = lbl_1_rodata_314[0];
    spA[1] = lbl_1_rodata_314[1];
    spA[2] = lbl_1_rodata_314[2];
    spA[3] = lbl_1_rodata_314[3];
    temp_r31 = lbl_1_bss_4->data;
    arg0->unk0 = 0;
    arg0->unk4 = dif;
    switch (sp8) {                                  /* irregular */
    case 0:
        if ((s32) (rand8() / (s32) ((0xFF / (s16) spA[dif]) + 1)) == 0) {
            var_r30 = 3;
        } else {
            var_r30 = 0;
        }
        if ((s16) temp_r31->unk21C < 3) {
            var_r28 = temp_r31->unk1F8[temp_r31->unk21C] + var_r30;
            temp_r31->unk21C = (s16) (temp_r31->unk21C + 1);
        } else {
            var_r28 = var_r30 + (rand8() / 86);
        }
        arg0->unkC = lbl_1_data_39B8[var_r28 + (temp_r31->unk2[0] * 6)];
        return;
    case 1:
        if ((s32) (rand8() / (s32) ((0xFF / (s16) spA[dif]) + 1)) == 0) {
            var_r30_2 = 3;
        } else {
            var_r30_2 = 0;
        }
        if ((s16) temp_r31->unk21E < 3) {
            var_r28_2 = temp_r31->unk204[temp_r31->unk21E] + var_r30_2;
            temp_r31->unk21E = (s16) (temp_r31->unk21E + 1);
        } else {
            var_r28_2 = var_r30_2 + (rand8() / 86);
        }
        arg0->unkC = lbl_1_data_3AA8[var_r28_2 + (temp_r31->unk2[1] * 6)];
        return;
    case 2:
        if ((s32) (rand8() / (s32) ((0xFF / (s16) spA[dif]) + 1)) == 0) {
            var_r30_3 = 6;
        } else {
            var_r30_3 = 0;
        }
        if ((s16) temp_r31->unk220 < 6) {
            var_r28_3 = temp_r31->unk210[temp_r31->unk220] + var_r30_3;
            temp_r31->unk220 = (s16) (temp_r31->unk220 + 1);
        } else {
            var_r28_3 = var_r30_3 + (rand8() / 43);
        }
        arg0->unkC = lbl_1_data_3B98[var_r28_3 + (temp_r31->unk2[2] * 0xC)];
        return;
    }
}

void fn_1_E548(M515Player *arg0) {
    f32 temp_f31;
    s32 var_r30;

    var_r30 = 0;
loop_4:
    if (var_r30 < (s16) arg0->unk5E8) {
        arg0->unk488[var_r30].unk28 += 2.0f;
        if (arg0->unk488[var_r30].unk28 > 360.0f) {
            arg0->unk488[var_r30].unk28 -= 360.0f;
        }
        temp_f31 = (f32) (0.05000000074505806 * sin((3.141592653589793 * (f64) arg0->unk488[var_r30].unk28) / 180.0));
        Hu3DModelScaleSet(arg0->unk488[var_r30].unk0, 1.1f, 1.05f + temp_f31, 1.1f);
        Hu3DModelScaleSet(arg0->unk488[var_r30].unk4, 1.1f - temp_f31, 1.1f, 1.1f - temp_f31);
        var_r30 += 1;
        goto loop_4;
    }
}
