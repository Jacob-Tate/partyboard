// m2c context for m567Dll (Quilt for Speed; tools/mp5/decomp.py m567Dll --types tools/mp5/types/m567Dll.h)
// Written from the draft: 1 vs 3. Two "sides" (side[0] = the solo player, side[1] = the team of three, grp 0 / 1), each
// with a quilt grid, a cursor (the needle), a slot machine of three reels and a camera. Offsets are GameCube's.
// objdata: M567Player
// objexpr lbl_1_bss_4: M567Main
// var fn_1_1FC temp_r31: M567Main
// var fn_1_32C temp_r31: M567Main
// var fn_1_FB8 temp_r31: M567Main
// var fn_1_108C temp_r31: M567Main
// var fn_1_1160 temp_r31: M567Main
// var fn_1_1474 temp_r31: M567Main
// var ObjectSetup temp_r30: M567Main
// var fn_1_9470 temp_r31: M567Player
// var fn_1_979C temp_r31: M567Cursor
// var fn_1_9828 temp_r31: M567Reel
// var fn_1_988C temp_r31: M567Cursor
// var fn_1_98F0 temp_r31: M567Blink
// var fn_1_32CC temp_r30: M567Cursor
// var fn_1_362C temp_r31: M567Cursor

static s32 m567Ready; // player objects initialised (see m567Dll_fix.py)

typedef struct M567Cam { // 0x38
    Vec target;
    f32 az; // 0xC
    f32 el; // 0x10
    f32 dist; // 0x14
    u8 pad18[0x1C];
    s16 camBit; // 0x34
    s16 pad36;
} M567Cam;

typedef struct M567View { // 0xC: split of the screen
    f32 split; // x of the border (640 = whole screen for the solo side)
    f32 unk4;
    s32 unk8;
} M567View;

typedef struct M567Reel { // 0x20: one reel of the slot machine
    HSFMATERIAL *mat;
    s16 state; // 4
    s16 timer; // 6
    s16 model; // 8
    s16 unkA;
    s16 unkC;
    s16 model2; // 0xE
    s16 model3; // 0x10
    s16 pad12;
    s16 pos; // 0x14
    s16 period; // 0x16
    s16 run; // 0x18
    s16 target; // 0x1A
    s16 unit; // 0x1C
    s16 idx; // 0x1E
} M567Reel;

typedef struct M567Blink { // 8
    HSFMATERIAL *mat;
    s16 state;
    s16 timer;
} M567Blink;

typedef struct M567Slot { // 0xD6 (inside M567Side at 0xCC)
    M567Cam *cam;
    M567Blink blink[3]; // 4
    Vec pos2d; // 0x1C
    Vec pos[3]; // 0x28
    Vec rot; // 0x4C
    M567Reel reel[3]; // 0x58
    s16 type; // 0xB8
    s16 flag; // 0xBA
    s16 model; // 0xBC
    s16 bandMdl[3]; // 0xBE
    s16 unkC4[3];
    s16 unkCA[3];
    s16 unkD0;
    s16 unkD2;
    s16 unkD4;
} M567Slot;

typedef struct M567Cursor { // 0x4C (inside M567Side at 0x80)
    Vec pos;
    Vec rot; // 0xC
    Vec from; // 0x18
    Vec to; // 0x24
    s16 model; // 0x30
    s16 mot32;
    s16 mot34;
    s16 mot36;
    s16 mot38;
    s16 mini[3]; // 0x3A
    s16 pum[3]; // 0x40
    s16 fx; // 0x46
    M567Cam *cam; // 0x48
} M567Cursor;

typedef struct M567Node { // 0x14: an effect running in the pool of the main work
    struct M567Node *prev;
    struct M567Node *next;
    struct M567Pool *pool;
    void *func; // s32 (*)(M567Node *): returns nonzero when done
    void *arg;
} M567Node;

typedef struct M567Pool { // 8: a linked list of running effects and the free nodes
    M567Node *head;
    M567Node *free;
} M567Pool;

typedef struct M567Player { // OMOBJ::data, 0x44
    Vec pos;
    Vec rot; // 0xC
    OMOBJ *obj; // 0x18
    M567Reel *reel; // 0x1C
    struct M567Side *side; // 0x20
    s16 model; // 0x24
    s16 player; // 0x26
    s16 charNo; // 0x28
    s16 group; // 0x2A
    s16 pad; // 0x2C
    s16 unk2E;
    s16 unk30;
    s16 isCom; // 0x32
    s16 dif; // 0x34
    s16 idx; // 0x36
    s16 state; // 0x38
    s16 pumMdl; // 0x3A
    s16 aiState; // 0x3C
    s16 aiTimer; // 0x3E
    s16 aiWait; // 0x40
    s16 aiChoice; // 0x42
} M567Player;

typedef struct M567Side { // 0x1B4
    M567Player *ply[3];
    s16 grid[11][5]; // 0xC
    s16 plan[3]; // 0x7A
    M567Cursor cur; // 0x80
    M567Slot slot; // 0xCC
    s16 isTeam; // 0x1A4
    s16 row; // 0x1A6
    s16 col; // 0x1A8
    s16 nrow; // 0x1AA
    s16 ncol; // 0x1AC
    s16 state; // 0x1AE
    s16 timer; // 0x1B0
    s16 limit; // 0x1B2
} M567Side;


typedef struct M567Main { // 0xD8C
    M567Player *ply[4]; // 0: by player number
    M567Side side[2]; // 0x10
    M567Pool pool; // 0x378
    M567Node nodes[100]; // 0x380
    M567Cam cam[2]; // 0xB50
    M567View view; // 0xBC0
    u8 padBCC[0x78];
    s16 fieldMdl[0x20]; // 0xC44
    s16 tileA[24]; // 0xC84
    s16 tileB[24]; // 0xCB4
    s16 unkCE4[3];
    s16 unkCEA; // the winning side (-1: none)
    s16 unkCEC; // step
    s16 unkCEE; // timer
    s16 unkCF0;
    s16 unkCF2;
    s16 unkCF4; // input enabled
    s16 unkCF6;
    s16 modelCache[0x41]; // 0xCF8
    s16 motionCache[9]; // 0xD7A
} M567Main;

extern s32 lbl_1_bss_0;
extern OMOBJ *lbl_1_bss_4;
extern HUPROCESS *lbl_1_bss_8;
extern MGSEQ_PARAM lbl_1_data_0;
extern u32 lbl_1_data_12C[0x41];
extern u32 lbl_1_data_230[9];
extern f32 lbl_1_data_254[0x3C];
extern s16 lbl_1_data_344[5][24];
extern s32 lbl_1_data_434[2];
extern s32 lbl_1_data_43C[2];
extern const u16 lbl_1_rodata_10[4];
extern const u16 lbl_1_rodata_70[4];
extern const Vec lbl_1_rodata_E0;
extern const Vec lbl_1_rodata_EC;
extern const Vec lbl_1_rodata_F8;
extern const Vec lbl_1_rodata_104;
extern const Vec lbl_1_rodata_110;
extern const Vec lbl_1_rodata_11C;
extern const s16 lbl_1_rodata_138[9][5];
extern const u16 lbl_1_rodata_192[3];
extern const s32 lbl_1_rodata_198[3];
extern const s32 lbl_1_rodata_1A4[2];
extern const s32 lbl_1_rodata_1AC[2];
extern const u16 lbl_1_rodata_1B4[4];
extern const s32 lbl_1_rodata_1F0[2];
extern const s32 lbl_1_rodata_204[2][4];
extern const s32 lbl_1_rodata_224[2][4];
extern const s32 lbl_1_rodata_244[4][4];

void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_32C(s16 mode, s16 frameNo);
void fn_1_FB8(s16 mode, s16 frameNo);
void fn_1_108C(s16 mode, s16 frameNo);
void fn_1_1160(s16 mode, s16 frameNo);
void fn_1_1474(s16 mode, s16 frameNo);
void fn_1_32CC(s16 mode, s16 frameNo);
void fn_1_362C(s16 mode, s16 frameNo);
void fn_1_371C(s16 mode, s16 frameNo);
void fn_1_3758(OMOBJ *obj);
void fn_1_3908(OMOBJ *obj);
void fn_1_3990(void);
void fn_1_3994(OMOBJ *obj);
void fn_1_39F8(OMOBJ *obj);
void fn_1_3B74(void);
void fn_1_3B78(M567Main *m);
void fn_1_3BF8(void);
void fn_1_3C80(M567Main *m);
void fn_1_3E94(M567View *v);
void fn_1_3EEC(M567View *v);
void fn_1_4164(void);
void fn_1_4168(void);
void fn_1_42A8(M567Main *m, s32 side);
void fn_1_439C(M567Cam *cam, s16 camBit);
void fn_1_4404(M567Cam *cam, Vec *pos);
void fn_1_4680(M567Pool *pool, M567Node *nodes, s32 count);
M567Node *fn_1_4704(M567Pool *pool, s32 (*func)(M567Node *), void *arg);
void fn_1_4758(M567Node *node);
void fn_1_47D0(M567Pool *pool);
void fn_1_48B0(M567Main *m);
void fn_1_5BD4(s16 (*grid)[5]);
s16 fn_1_5F04(s32 arg0);
s16 fn_1_5FC0(s32 arg0);
void fn_1_6094(s32 arg0, s32 arg1);
void fn_1_60F8(M567Main *m);
void fn_1_69B4(M567Cursor *cur, s32 team);
s32 fn_1_7084(M567Side *side);
void fn_1_7DB4(M567Slot *slot, M567Cam *cam, s16 type);
void fn_1_8330(M567Slot *slot);
void fn_1_8794(M567Reel *reel, s32 type);
void fn_1_89F4(M567Reel *reel);
void fn_1_8DE0(M567Reel *reel);
void fn_1_8EC8(M567Player *p);
void fn_1_8F1C(M567Player *p);
void fn_1_92B0(M567Player *p);
s32 fn_1_9470(M567Node *node);
void fn_1_959C(s16 (*grid)[5], s16 row, s16 col);
s32 fn_1_9694(s16 (*grid)[5], s16 row, s16 col);
s32 fn_1_979C(M567Node *node);
s32 fn_1_9828(M567Node *node);
s32 fn_1_988C(M567Node *node);
s32 fn_1_98F0(M567Node *node);
