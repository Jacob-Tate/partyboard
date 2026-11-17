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

extern s32 lbl_1_bss_0;
extern OMOBJ *lbl_1_bss_4;
extern HUPROCESS *lbl_1_bss_8;
extern MGSEQ_PARAM lbl_1_data_0;
extern f32 lbl_1_data_28[0x3C];
extern s32 lbl_1_data_118[0xD][8];
extern s32 lbl_1_data_2B8[0x1A];
extern s32 lbl_1_data_320[0x11];
extern s32 lbl_1_data_364[0x11];
extern s32 lbl_1_data_3A8[8];
extern s32 lbl_1_data_3C8[0xE];
extern u16 *lbl_1_data_1094[10];
extern u16 *lbl_1_data_10BC[10];
extern u16 *lbl_1_data_10E4[10];
extern M515Place *lbl_1_data_110C[10];
extern M515Place *lbl_1_data_1134[10];
extern M515Place *lbl_1_data_115C[10];
extern u16 lbl_1_rodata_10[4];
extern f32 lbl_1_rodata_18[9];
extern f32 lbl_1_rodata_3C[4];
extern Vec lbl_1_rodata_A4;
extern f32 lbl_1_rodata_B0[4];
extern u16 lbl_1_rodata_C0[4];
extern Vec lbl_1_rodata_FC;
extern Vec lbl_1_rodata_108;
extern Vec lbl_1_rodata_114;
extern Vec lbl_1_rodata_120;
extern Vec lbl_1_rodata_12C;
extern Vec lbl_1_rodata_138;
extern f32 lbl_1_rodata_148[4];
extern u16 lbl_1_rodata_15C[4];
extern u16 lbl_1_rodata_164[16];
extern u16 lbl_1_rodata_184[4];
extern f32 lbl_1_rodata_194[4];
extern f32 lbl_1_rodata_1FC[4];
extern f32 lbl_1_rodata_20C[4];
extern f32 lbl_1_rodata_224[4];
extern u16 lbl_1_rodata_234[4];
extern f32 lbl_1_rodata_24C[2];
extern f32 lbl_1_rodata_254[2];
extern Vec lbl_1_rodata_260;
extern Vec lbl_1_rodata_27C[4];
extern f32 lbl_1_rodata_2AC[4];
extern s32 lbl_1_rodata_2BC[4];
extern u16 lbl_1_rodata_2E4[4];
extern u16 lbl_1_rodata_2EC[4];
extern u16 lbl_1_rodata_2F4[4];
extern u16 lbl_1_rodata_2FC[4];
extern u16 lbl_1_rodata_304[4];
extern u16 lbl_1_rodata_30C[4];
extern u16 lbl_1_rodata_314[6];

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
