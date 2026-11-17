// MP5 m567 (Quilt for Speed), generated from its m2c draft by tools/mp5/ports/m567Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
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
struct _struct_lbl_1_data_28_0x14 { // TODO(mp5): synthesized from the symbol size
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
};

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
void fn_1_3758(omObjData *obj);
void fn_1_3908(omObjData *obj);
void fn_1_3994(omObjData *obj);
void fn_1_39F8(omObjData *obj);
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
void fn_1_47D0(M567Pool *pool);
void fn_1_48B0(M567Main *m);
void fn_1_5BD4(s16 (*grid)[5]);
s16 fn_1_5F04(s32 arg0);
s16 fn_1_5FC0(s32 arg0);
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

MGSEQ_PARAM lbl_1_data_0 = {
    0x12C,
    0,
    fn_1_1FC,
    fn_1_32C,
    fn_1_FB8,
    fn_1_108C,
    fn_1_1160,
    fn_1_1474,
    fn_1_32CC,
    fn_1_362C,
    fn_1_371C,
};
static struct _struct_lbl_1_data_28_0x14 lbl_1_data_28[0xD] = { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 23) }, { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 106), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 63), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 23) }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 23 */ }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 23 */ }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */ }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */ }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */ }, { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 106 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 63 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */ } };
u32 lbl_1_data_12C[0x41] = {
    DATA_MAKE_NUM(DATADIR_MP5_M567, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 18),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 20),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 24),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 31),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 32),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 33),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 34),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 35),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 36),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 37),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 38),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 39),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 40),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 41),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 42),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 43),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 44),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 45),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 46),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 47),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 48),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 49),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 50),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 51),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 52),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 53),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 54),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 55),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 56),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 57),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 58),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 59),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 60),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 61),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 62),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 63),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 64),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 65),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 66),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 67),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 68),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 69),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 70),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 71),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 72),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 73),
};
u32 lbl_1_data_230[9] = {
    DATA_MAKE_NUM(DATADIR_MP5_M567, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M567, 8),
};
f32 lbl_1_data_254[0x3C] = {
    0.0f,
    0.0f,
    2600.0f,
    90.0f,
    41.0f,
    1890.0f,
    0.0f,
    0.0f,
    -2150.0f,
    270.0f,
    41.0f,
    1890.0f,
    0.0f,
    0.0f,
    -2400.0f,
    90.0f,
    41.0f,
    1400.0f,
    0.0f,
    500.0f,
    2150.0f,
    90.0f,
    50.0f,
    1700.0f,
    0.0f,
    0.0f,
    2150.0f,
    90.0f,
    41.0f,
    1890.0f,
    0.0f,
    500.0f,
    -2150.0f,
    270.0f,
    50.0f,
    1700.0f,
    0.0f,
    0.0f,
    -2150.0f,
    270.0f,
    41.0f,
    1890.0f,
    0.0f,
    0.0f,
    2000.0f,
    90.0f,
    31.0f,
    1730.0f,
    0.0f,
    0.0f,
    -2000.0f,
    270.0f,
    31.0f,
    1730.0f,
    0.0f,
    0.0f,
    -781.0f,
    90.0f,
    21.0f,
    2120.0f,
};
s16 lbl_1_data_344[5][0x18] = {
    { 2, 6, 7, 0, 5, 2, 3, 6, 0, 2, 0, 3, 1, 5, 7, 0, 2, 6, 1, 4, 5, 2, 1, 2 },
    { 0, 2, 7, 7, 6, 1, 5, 4, 2, 0, 7, 6, 5, 1, 4, 7, 5, 7, 3, 0, 2, 0, 7, 5 },
    { 7, 1, 4, 6, 5, 6, 0, 7, 0, 4, 6, 2, 3, 2, 7, 2, 4, 6, 1, 0, 2, 6, 3, 0 },
    { 1, 0, 5, 3, 7, 3, 0, 2, 6, 5, 1, 2, 7, 3, 6, 6, 4, 5, 7, 2, 1, 3, 5, 3 },
    { 4, 6, 4, 5, 3, 7, 0, 1, 5, 7, 4, 0, 6, 5, 6, 4, 2, 4, 1, 0, 2, 0, 6, 3 },
};
s32 lbl_1_data_434[2] = { -1, -1 };
s32 lbl_1_data_43C[2] = { -1, -1 };
static s8 lbl_1_data_54B[9] = "m567-3pa";
static s8 lbl_1_data_554[9] = "m567-3pb";
static s8 lbl_1_data_55D[0xB] = { 0x6D, 0x35, 0x36, 0x37, 0x2D, 0x33, 0x70, 0x63, 0, 0, 0 };
s32 lbl_1_bss_0;
omObjData *lbl_1_bss_4;
HUPROCESS *lbl_1_bss_8;
u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };            /* const */
u16 lbl_1_rodata_70[4] = { 0x20, 0x40, 0x60, 0 };   /* const */
Vec lbl_1_rodata_E0 = { 0.0f, 1.0f, 0.0f };     /* const */
Vec lbl_1_rodata_EC = { 0.0f, 2000.0f, 2000.0f }; /* const */
Vec lbl_1_rodata_F8 = { 0.1f, 0.0f, 2000.0f };  /* const */
Vec lbl_1_rodata_104 = { 0.0f, 1.0f, 0.0f };    /* const */
Vec lbl_1_rodata_110 = { 0.0f, 2000.0f, -300.0f }; /* const */
Vec lbl_1_rodata_11C = { 0.1f, 0.0f, -300.0f }; /* const */
s16 lbl_1_rodata_138[9][5] = {
    { -1, 0, 0, 0, -1 },
    { -1, -1, 0, 0, -1 },
    { -1, 0, -1, 0, -1 },
    { -1, -1, -1, 0, -1 },
    { -1, 0, 0, -1, -1 },
    { -1, -1, 0, -1, -1 },
    { -1, 0, -1, -1, -1 },
    { -1, 0, 0, 0, -1 },
    { -1, 2, 2, 2, -1 },
}; /* const */
u16 lbl_1_rodata_192[3] = { 1, 2, 4 };              /* const */
s32 lbl_1_rodata_198[3] = { 0, 2, 4 };              /* const */
s32 lbl_1_rodata_1A4[2] = { 0, 4 };                 /* const */
s32 lbl_1_rodata_1AC[2] = { 0, 1 };                 /* const */
u16 lbl_1_rodata_1B4[4] = { 0x20, 0x40, 0x60, 0 };  /* const */
s32 lbl_1_rodata_1F0[2] = { 0x8F3, 0x8F4 };         /* const */
static struct { // TODO(mp5): synthesized from the symbol size
    s16 unk0;
} lbl_1_rodata_1F8;
s32 lbl_1_rodata_204[2][4] = { { 0x32, 0x1E, 0x14, 0xA }, { 0x3C, 0x28, 0x19, 0xF } }; /* const */
s32 lbl_1_rodata_224[2][4] = { { 0x1E, 0x1E, 0x14, 0xA }, { 0x1E, 0x28, 0x19, 0xF } }; /* const */
s32 lbl_1_rodata_244[4][4] = {
    { 0x2D, 0x41, 0x4B, 0x55 },
    { 0x2D, 0x41, 0x4B, 0x55 },
    { 0x2D, 0x3C, 0x4B, 0x50 },
    { 0x2D, 0x37, 0x4B, 0x4B },
}; /* const */



void ObjectSetup(void) {
    omObjData *temp_r31;
    omObjData *temp_r3;
    s32 var_r29;
    M567Main *temp_r30;

    m567Ready = 0;
    lbl_1_bss_8 = omInitObjMan(0xA, 0x2000);
    omGameSysInit(lbl_1_bss_8);
    temp_r3 = omAddObjEx(lbl_1_bss_8, 0x65, 0U, 0U, -1, fn_1_3994);
    lbl_1_bss_4 = temp_r3;
    temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M567Main), MEMORY_DEFAULT_NUM);
    temp_r30 = temp_r3->data;
    temp_r30->unkCF4 = 0;
    temp_r30->unkCF6 = 0;
    fn_1_3C80((M567Main *) temp_r30);
    fn_1_3BF8();
    var_r29 = 0;
loop_2:
    if (var_r29 < 4) {
        temp_r31 = omAddObjEx(lbl_1_bss_8, 0x64, 1U, 5U, 0, fn_1_3758);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, 0x44, MEMORY_DEFAULT_NUM);
        temp_r31->work[0] = (u32) var_r29;
        temp_r30->ply[var_r29] = temp_r31->data;
        var_r29 += 1;
        goto loop_2;
    }
    fn_1_3B78((M567Main *) temp_r30);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DNoSyncSet(1);
    MgSeqCreate(&lbl_1_data_0);
}

void fn_1_1FC(s16 mode, s16 frameNo) {
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    if (m567Ready < 4) {
        return;
    }
    temp_r31->unkCF4 = 0;
    temp_r31->unkCF6 = 0;
    temp_r31->unkCEC = 0;
    temp_r31->unkCF2 = 0;
    fn_1_60F8((M567Main *) temp_r31);
    fn_1_48B0((M567Main *) temp_r31);
    fn_1_3E94(&temp_r31->view);
    temp_r31->cam[0].az = (f32) lbl_1_data_254[0xF];
    temp_r31->cam[0].el = (f32) lbl_1_data_254[0x10];
    temp_r31->cam[0].dist = (f32) lbl_1_data_254[0x11];
    temp_r31->cam[0].target.x = (f32) lbl_1_data_254[0xC];
    temp_r31->cam[0].target.y = (f32) lbl_1_data_254[0xD];
    temp_r31->cam[0].target.z = (f32) lbl_1_data_254[0xE];
    temp_r31->cam[1].az = (f32) lbl_1_data_254[0x21];
    temp_r31->cam[1].el = (f32) lbl_1_data_254[0x22];
    temp_r31->cam[1].dist = (f32) lbl_1_data_254[0x23];
    temp_r31->cam[1].target.x = (f32) lbl_1_data_254[0x1E];
    temp_r31->cam[1].target.y = (f32) lbl_1_data_254[0x1F];
    temp_r31->cam[1].target.z = (f32) lbl_1_data_254[0x20];
    MgSeqModeNext();
}

void fn_1_32C(s16 mode, s16 frameNo) {
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    s16 temp_r3;
    s32 temp_r3_2;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r3 = temp_r31->unkCEC;
    if ((u32) temp_r3 <= 7U) {
        switch (temp_r3) {
        case 0:
            MgSeqModeChangeOff();
            HuAudFXPlay(0x8FD);
            temp_r31->unkCF0 = 0;
            temp_r31->unkCEE = 0;
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            /* fallthrough */
        case 1:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0x96) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unkCEE / 150.0f))) / 180.0))));
            temp_f29 = 1.0f - temp_f31;
            temp_r31->cam[0].az = (f32) ((lbl_1_data_254[0xF] * temp_f29) + (lbl_1_data_254[0x15] * temp_f31));
            temp_r31->cam[0].el = (f32) ((lbl_1_data_254[0x10] * temp_f29) + (lbl_1_data_254[0x16] * temp_f31));
            temp_r31->cam[0].dist = (f32) ((lbl_1_data_254[0x11] * temp_f29) + (lbl_1_data_254[0x17] * temp_f31));
            temp_r31->cam[0].target.x = (f32) ((lbl_1_data_254[0xC] * temp_f29) + (lbl_1_data_254[0x12] * temp_f31));
            temp_r31->cam[0].target.y = (f32) ((lbl_1_data_254[0xD] * temp_f29) + (lbl_1_data_254[0x13] * temp_f31));
            temp_r31->cam[0].target.z = (f32) ((lbl_1_data_254[0xE] * temp_f29) + (lbl_1_data_254[0x14] * temp_f31));
            return;
        case 2:
            temp_r31->unkCEE = 0;
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            /* fallthrough */
        case 3:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0x1E) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            temp_f31_2 = (f32) temp_r31->unkCEE / 30.0f;
            temp_r31->view.split = (f32) ((640.0f * (1.0f - temp_f31_2)) + (320.0f * temp_f31_2));
            return;
        case 4:
            HuAudFXPlay(0x8EC);
            Hu3DModelAttrSet(temp_r31->modelCache[12], 1U);
            temp_r31->unkCEE = 0;
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            /* fallthrough */
        case 5:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0xF) {
                HuAudFXPlay(0x8FE);
                Hu3DModelAttrReset(temp_r31->side[0].slot.unkCA[0], 0x40000002U);
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[0], 0x40000002U);
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[1], 0x40000002U);
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[2], 0x40000002U);
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            temp_f31_3 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unkCEE / 15.0f))) / 180.0))));
            temp_r31->side[0].slot.pos2d.y = (f32) ((500.0f * (1.0f - temp_f31_3)) + (401.0f * temp_f31_3));
            temp_r31->side[1].slot.pos2d.y = (f32) ((500.0f * (1.0f - temp_f31_3)) + (401.0f * temp_f31_3));
            temp_f31_4 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unkCEE / 240.0f))) / 180.0))));
            temp_f28 = 1.0f - temp_f31_4;
            temp_r31->cam[0].az = (f32) ((lbl_1_data_254[0x15] * temp_f28) + (lbl_1_data_254[0x1B] * temp_f31_4));
            temp_r31->cam[0].el = (f32) ((lbl_1_data_254[0x16] * temp_f28) + (lbl_1_data_254[0x1C] * temp_f31_4));
            temp_r31->cam[0].dist = (f32) ((lbl_1_data_254[0x17] * temp_f28) + (lbl_1_data_254[0x1D] * temp_f31_4));
            temp_r31->cam[0].target.x = (f32) ((lbl_1_data_254[0x12] * temp_f28) + (lbl_1_data_254[0x18] * temp_f31_4));
            temp_r31->cam[0].target.y = (f32) ((lbl_1_data_254[0x13] * temp_f28) + (lbl_1_data_254[0x19] * temp_f31_4));
            temp_r31->cam[0].target.z = (f32) ((lbl_1_data_254[0x14] * temp_f28) + (lbl_1_data_254[0x1A] * temp_f31_4));
            temp_f27 = 1.0f - temp_f31_4;
            temp_r31->cam[1].az = (f32) ((lbl_1_data_254[0x21] * temp_f27) + (lbl_1_data_254[0x27] * temp_f31_4));
            temp_r31->cam[1].el = (f32) ((lbl_1_data_254[0x22] * temp_f27) + (lbl_1_data_254[0x28] * temp_f31_4));
            temp_r31->cam[1].dist = (f32) ((lbl_1_data_254[0x23] * temp_f27) + (lbl_1_data_254[0x29] * temp_f31_4));
            temp_r31->cam[1].target.x = (f32) ((lbl_1_data_254[0x1E] * temp_f27) + (lbl_1_data_254[0x24] * temp_f31_4));
            temp_r31->cam[1].target.y = (f32) ((lbl_1_data_254[0x1F] * temp_f27) + (lbl_1_data_254[0x25] * temp_f31_4));
            temp_r31->cam[1].target.z = (f32) ((lbl_1_data_254[0x20] * temp_f27) + (lbl_1_data_254[0x26] * temp_f31_4));
            return;
        case 6:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0x23) {
                Hu3DModelAttrSet(temp_r31->side[0].slot.unkCA[0], 0x40000002U);
                Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[0], 0x40000002U);
                Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[1], 0x40000002U);
                Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[2], 0x40000002U);
            }
            if ((s16) temp_r31->unkCEE == 0xAF) {
                Hu3DModelAttrReset(temp_r31->side[0].slot.unkCA[0], 0x40000002U);
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[0], 0x40000002U);
            }
            if ((s16) temp_r31->unkCEE == 0xB9) {
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[1], 0x40000002U);
            }
            if ((s16) temp_r31->unkCEE == 0xC3) {
                Hu3DModelAttrReset(temp_r31->side[1].slot.unkCA[2], 0x40000002U);
            }
            if ((s16) temp_r31->unkCEE == 0xBE) {
                HuAudFXPlayPan(0x8ED, 0x30);
                HuAudFXPlayPan(0x8EE, 0x48);
                Hu3DModelAttrReset(temp_r31->side[0].slot.bandMdl[0], 0x40000002U);
                Hu3DModelAttrReset(temp_r31->side[1].slot.bandMdl[0], 0x40000002U);
                fn_1_4704(&temp_r31->pool, fn_1_98F0, &temp_r31->side[0].slot.blink[0]);
                temp_r31->side[0].slot.blink[0].state = 2;
                temp_r31->side[0].slot.blink[0].timer = 0xF;
                fn_1_4704(&temp_r31->pool, fn_1_98F0, &temp_r31->side[0].slot.blink[1]);
                temp_r31->side[0].slot.blink[1].state = 2;
                temp_r31->side[0].slot.blink[1].timer = 0xF;
                fn_1_4704(&temp_r31->pool, fn_1_98F0, &temp_r31->side[1].slot.blink[0]);
                temp_r31->side[1].slot.blink[0].state = 2;
                temp_r31->side[1].slot.blink[0].timer = 0xF;
            }
            if ((s16) temp_r31->unkCEE == 0xC8) {
                HuAudFXPlayPan(0x8EF, 0x50);
                Hu3DModelAttrReset(temp_r31->side[1].slot.bandMdl[1], 0x40000002U);
                fn_1_4704(&temp_r31->pool, fn_1_98F0, &temp_r31->side[1].slot.blink[1]);
                temp_r31->side[1].slot.blink[1].state = 2;
                temp_r31->side[1].slot.blink[1].timer = 0xF;
            }
            if ((s16) temp_r31->unkCEE == 0xD2) {
                HuAudFXPlayPan(0x8F0, 0x58);
                Hu3DModelAttrReset(temp_r31->side[1].slot.bandMdl[2], 0x40000002U);
                fn_1_4704(&temp_r31->pool, fn_1_98F0, &temp_r31->side[1].slot.blink[2]);
                temp_r31->side[1].slot.blink[2].state = 2;
                temp_r31->side[1].slot.blink[2].timer = 0xF;
            }
            if ((s16) temp_r31->unkCEE == 0xF0) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            temp_f31_5 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unkCEE / 240.0f))) / 180.0))));
            temp_f26 = 1.0f - temp_f31_5;
            temp_r31->cam[0].az = (f32) ((lbl_1_data_254[0x15] * temp_f26) + (lbl_1_data_254[0x1B] * temp_f31_5));
            temp_r31->cam[0].el = (f32) ((lbl_1_data_254[0x16] * temp_f26) + (lbl_1_data_254[0x1C] * temp_f31_5));
            temp_r31->cam[0].dist = (f32) ((lbl_1_data_254[0x17] * temp_f26) + (lbl_1_data_254[0x1D] * temp_f31_5));
            temp_r31->cam[0].target.x = (f32) ((lbl_1_data_254[0x12] * temp_f26) + (lbl_1_data_254[0x18] * temp_f31_5));
            temp_r31->cam[0].target.y = (f32) ((lbl_1_data_254[0x13] * temp_f26) + (lbl_1_data_254[0x19] * temp_f31_5));
            temp_r31->cam[0].target.z = (f32) ((lbl_1_data_254[0x14] * temp_f26) + (lbl_1_data_254[0x1A] * temp_f31_5));
            temp_f25 = 1.0f - temp_f31_5;
            temp_r31->cam[1].az = (f32) ((lbl_1_data_254[0x21] * temp_f25) + (lbl_1_data_254[0x27] * temp_f31_5));
            temp_r31->cam[1].el = (f32) ((lbl_1_data_254[0x22] * temp_f25) + (lbl_1_data_254[0x28] * temp_f31_5));
            temp_r31->cam[1].dist = (f32) ((lbl_1_data_254[0x23] * temp_f25) + (lbl_1_data_254[0x29] * temp_f31_5));
            temp_r31->cam[1].target.x = (f32) ((lbl_1_data_254[0x1E] * temp_f25) + (lbl_1_data_254[0x24] * temp_f31_5));
            temp_r31->cam[1].target.y = (f32) ((lbl_1_data_254[0x1F] * temp_f25) + (lbl_1_data_254[0x25] * temp_f31_5));
            temp_r31->cam[1].target.z = (f32) ((lbl_1_data_254[0x20] * temp_f25) + (lbl_1_data_254[0x26] * temp_f31_5));
            return;
        case 7:
            temp_r3_2 = HuAudBGMPlay(0x34);
            lbl_1_bss_0 = temp_r3_2;
            MgSeqModeNext();
            break;
        }
    }
}

void fn_1_FB8(s16 mode, s16 frameNo) {
    s16 temp_r0;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unkCF0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrSet(temp_r31->side[0].slot.bandMdl[0], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.bandMdl[0], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.bandMdl[1], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.bandMdl[2], 1U);
        Hu3DModelAttrSet(temp_r31->side[0].slot.unkCA[0], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[0], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[1], 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.unkCA[2], 1U);
        temp_r31->side[0].slot.flag = 1;
        temp_r31->side[1].slot.flag = 1;
        temp_r31->unkCEC = 0;
        temp_r31->unkCF0 = (s16) (temp_r31->unkCF0 + 1);
        /* fallthrough */
    case 1:
        return;
    }
}

void fn_1_108C(s16 mode, s16 frameNo) {
    s16 temp_r0;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unkCEC;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->side[0].state = 1;
        temp_r31->side[1].state = 1;
        temp_r31->unkCF0 = 0;
        temp_r31->unkCF4 = 1;
        temp_r31->unkCF6 = 1;
        temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
        /* fallthrough */
    case 1:
        if ((s16) temp_r31->unkCEA >= 0) {
            temp_r31->unkCF4 = 0;
            MgSeqModeChangeOff();
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            return;
        }
        return;
    case 2:
        if ((s16) temp_r31->side[temp_r31->unkCEA].state == 7) {
            MgSeqModeNext();
        }
        break;
    }
}

void fn_1_1160(s16 mode, s16 frameNo) {
    f32 temp_f31;
    s16 temp_r0;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unkCF0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if (((s16) temp_r31->side[0].state != 4) && ((s16) temp_r31->side[0].state != 7) && ((s16) temp_r31->side[0].state != 8)) {
            temp_r31->side[0].state = 7;
        }
        if (((s16) temp_r31->side[1].state != 4) && ((s16) temp_r31->side[1].state != 7) && ((s16) temp_r31->side[1].state != 8)) {
            temp_r31->side[1].state = 7;
        }
        if ((s16) temp_r31->unkCEA < 0) {
            if ((s16) temp_r31->side[0].nrow == 9) {
                temp_r31->side[0].nrow = (s16) temp_r31->side[0].row;
                temp_r31->side[0].cur.to.z = (f32) temp_r31->side[0].cur.from.z;
            }
            if ((s16) temp_r31->side[1].nrow == 9) {
                temp_r31->side[1].nrow = (s16) temp_r31->side[1].row;
                temp_r31->side[1].cur.to.z = (f32) temp_r31->side[1].cur.from.z;
            }
            MgSeqWinnerSet(-1, -1, -1, -1);
        } else if ((s16) temp_r31->unkCEA == 0) {
            MgSeqWinnerSet(temp_r31->side[0].ply[0]->charNo, -1, -1, -1);
        } else {
            MgSeqWinnerSet(temp_r31->side[1].ply[0]->charNo, temp_r31->side[1].ply[1]->charNo, temp_r31->side[1].ply[2]->charNo, -1);
        }
        temp_r31->unkCEC = 0;
        temp_r31->unkCF4 = 0;
        temp_r31->unkCF6 = 0;
        temp_r31->unkCEE = 0;
        HuAudSStreamFadeOut(lbl_1_bss_0, 0x3E8);
        temp_r31->unkCF0 = (s16) (temp_r31->unkCF0 + 1);
        /* fallthrough */
    case 1:
        temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
        if ((s16) temp_r31->unkCEE == 0xF) {
            temp_r31->unkCF0 = (s16) (temp_r31->unkCF0 + 1);
        }
        temp_f31 = (f32) (1.0 - (0.5 + (0.5 * cos((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->unkCEE / 15.0f))) / 180.0))));
        temp_r31->side[0].slot.pos2d.y = (f32) ((401.0f * (1.0f - temp_f31)) + (500.0f * temp_f31));
        temp_r31->side[1].slot.pos2d.y = (f32) ((401.0f * (1.0f - temp_f31)) + (500.0f * temp_f31));
        return;
    case 2:
        Hu3DModelAttrSet(temp_r31->side[0].slot.model, 1U);
        Hu3DModelAttrSet(temp_r31->side[1].slot.model, 1U);
        temp_r31->unkCF0 = (s16) (temp_r31->unkCF0 + 1);
        return;
    }
}

void fn_1_1474(s16 mode, s16 frameNo) {
    Mtx sp10;
    u16 sp8[3];
    Vec *temp_r3_2;
    Vec *temp_r4;
    Vec *temp_r4_2;
    Vec *temp_r4_3;
    Vec *temp_r4_4;
    Vec *temp_r4_5;
    Vec *temp_r4_6;
    Vec *temp_r5;
    Vec *temp_r5_2;
    Vec *temp_r5_3;
    Vec *temp_r5_4;
    Vec *temp_r6;
    f32 temp_f1;
    f32 temp_f1_2;
    s16 temp_r3;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r29_4;
    s32 var_r29_5;
    M567Cursor *temp_r30;
    M567Cursor *temp_r30_2;
    M567Main *temp_r31;

    sp8[0] = lbl_1_rodata_70[0];
    sp8[1] = lbl_1_rodata_70[1];
    sp8[2] = lbl_1_rodata_70[2];
    temp_r31 = lbl_1_bss_4->data;
    temp_r3 = temp_r31->unkCEC;
    if ((u32) temp_r3 <= 8U) {
        switch (temp_r3) {
        case 0:
            MgSeqModeChangeOff();
            temp_r31->unkCF0 = 0;
            temp_r31->unkCEE = 0;
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            return;
        case 1:
            if ((s16) temp_r31->unkCEA < 0) {
                Hu3DMotionShiftSet(temp_r31->side[0].cur.model, temp_r31->side[0].cur.mot36, 0.0f, 5.0f, 0U);
                Hu3DMotionShiftSet(temp_r31->side[1].cur.model, temp_r31->side[1].cur.mot36, 0.0f, 5.0f, 0U);
            } else {
                Hu3DMotionShiftSet(temp_r31->side[temp_r31->unkCEA ^ 1].cur.model, temp_r31->side[temp_r31->unkCEA ^ 1].cur.mot36, 0.0f, 5.0f, 0U);
            }
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            return;
        case 2:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0x28) {
                if ((s16) temp_r31->unkCEA != 0) {
                    Hu3DModelObjMtxGet(temp_r31->side[0].cur.model, "m567-play0", sp10);
                    Hu3DMtxTransGet(sp10, &temp_r31->side[0].ply[0]->pos);
                    Hu3DMtxRotGet(sp10, &temp_r31->side[0].ply[0]->rot);
                    Hu3DModelPosSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->pos);
                    omSetTra(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->pos.x, temp_r31->side[0].ply[0]->pos.y, temp_r31->side[0].ply[0]->pos.z);
                    Hu3DModelRotSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->rot);
                    omSetRot(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->rot.x, temp_r31->side[0].ply[0]->rot.y, temp_r31->side[0].ply[0]->rot.z);
                    Hu3DModelHookObjReset(temp_r31->side[0].cur.model, "m567-play0");
                    omVibrate(temp_r31->side[0].ply[0]->player, 0x19, 0xC, 0);
                    HuAudFXPlayPan(0x8FB, (s16) sp8[temp_r31->side[0].ncol - 1]);
                }
                if ((s16) temp_r31->unkCEA != 1) {
                    Hu3DModelObjMtxGet(temp_r31->side[1].cur.model, "m567-play3", sp10);
                    Hu3DMtxTransGet(sp10, &temp_r31->side[1].ply[0]->pos);
                    Hu3DMtxRotGet(sp10, &temp_r31->side[1].ply[0]->rot);
                    Hu3DModelPosSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->pos);
                    omSetTra(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->pos.x, temp_r31->side[1].ply[0]->pos.y, temp_r31->side[1].ply[0]->pos.z);
                    Hu3DModelRotSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->rot);
                    omSetRot(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->rot.x, temp_r31->side[1].ply[0]->rot.y, temp_r31->side[1].ply[0]->rot.z);
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play3");
                    Hu3DModelObjMtxGet(temp_r31->side[1].cur.model, "m567-play1", sp10);
                    Hu3DMtxTransGet(sp10, &temp_r31->side[1].ply[1]->pos);
                    Hu3DMtxRotGet(sp10, &temp_r31->side[1].ply[1]->rot);
                    Hu3DModelPosSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->pos);
                    omSetTra(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->pos.x, temp_r31->side[1].ply[1]->pos.y, temp_r31->side[1].ply[1]->pos.z);
                    Hu3DModelRotSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->rot);
                    omSetRot(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->rot.x, temp_r31->side[1].ply[1]->rot.y, temp_r31->side[1].ply[1]->rot.z);
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play1");
                    Hu3DModelObjMtxGet(temp_r31->side[1].cur.model, "m567-play2", sp10);
                    Hu3DMtxTransGet(sp10, &temp_r31->side[1].ply[2]->pos);
                    Hu3DMtxRotGet(sp10, &temp_r31->side[1].ply[2]->rot);
                    Hu3DModelPosSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->pos);
                    omSetTra(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->pos.x, temp_r31->side[1].ply[2]->pos.y, temp_r31->side[1].ply[2]->pos.z);
                    Hu3DModelRotSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->rot);
                    omSetRot(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->rot.x, temp_r31->side[1].ply[2]->rot.y, temp_r31->side[1].ply[2]->rot.z);
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play2");
                    omVibrate(temp_r31->side[1].ply[0]->player, 0x23, 0xC, 0);
                    omVibrate(temp_r31->side[1].ply[1]->player, 0x23, 0xC, 0);
                    omVibrate(temp_r31->side[1].ply[2]->player, 0x23, 0xC, 0);
                    HuAudFXPlayPan(0x8FC, (s16) sp8[temp_r31->side[1].ncol - 1]);
                }
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
                return;
            }
            break;
        case 3:
            temp_r31->unkCEE = (s16) (temp_r31->unkCEE + 1);
            if ((s16) temp_r31->unkCEE == 0x32) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            if ((s16) temp_r31->unkCEA != 0) {
                temp_r5 = &temp_r31->side[0].ply[0]->pos;
                temp_r5->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->pos);
                omSetTra(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->pos.x, temp_r31->side[0].ply[0]->pos.y, temp_r31->side[0].ply[0]->pos.z);
            }
            if ((s16) temp_r31->unkCEA != 1) {
                temp_r5_2 = &temp_r31->side[1].ply[0]->pos;
                temp_r5_2->y += 50.0f;
                temp_r31->side[1].ply[0]->pos.x = temp_r31->side[1].ply[0]->pos.x + 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->pos);
                omSetTra(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->pos.x, temp_r31->side[1].ply[0]->pos.y, temp_r31->side[1].ply[0]->pos.z);
                temp_r5_3 = &temp_r31->side[1].ply[1]->pos;
                temp_r5_3->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->pos);
                omSetTra(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->pos.x, temp_r31->side[1].ply[1]->pos.y, temp_r31->side[1].ply[1]->pos.z);
                temp_r5_4 = &temp_r31->side[1].ply[2]->pos;
                temp_r5_4->y += 50.0f;
                temp_r31->side[1].ply[2]->pos.x = temp_r31->side[1].ply[2]->pos.x - 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->pos);
                omSetTra(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->pos.x, temp_r31->side[1].ply[2]->pos.y, temp_r31->side[1].ply[2]->pos.z);
                return;
            }
            break;
        case 4:
            WipeColorSet(0xFFU, 0xFFU, 0xFFU);
            WipeCreate(2, 0, 0x3C);
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            if ((s16) temp_r31->unkCEA != 0) {
                temp_r4 = &temp_r31->side[0].ply[0]->pos;
                temp_r4->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->pos);
                omSetTra(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->pos.x, temp_r31->side[0].ply[0]->pos.y, temp_r31->side[0].ply[0]->pos.z);
            }
            if ((s16) temp_r31->unkCEA != 1) {
                temp_r4_2 = &temp_r31->side[1].ply[0]->pos;
                temp_r4_2->y += 50.0f;
                temp_r31->side[1].ply[0]->pos.x = temp_r31->side[1].ply[0]->pos.x + 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->pos);
                omSetTra(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->pos.x, temp_r31->side[1].ply[0]->pos.y, temp_r31->side[1].ply[0]->pos.z);
                temp_r4_3 = &temp_r31->side[1].ply[1]->pos;
                temp_r4_3->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->pos);
                omSetTra(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->pos.x, temp_r31->side[1].ply[1]->pos.y, temp_r31->side[1].ply[1]->pos.z);
                temp_r4_4 = &temp_r31->side[1].ply[2]->pos;
                temp_r4_4->y += 50.0f;
                temp_r31->side[1].ply[2]->pos.x = temp_r31->side[1].ply[2]->pos.x - 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->pos);
                omSetTra(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->pos.x, temp_r31->side[1].ply[2]->pos.y, temp_r31->side[1].ply[2]->pos.z);
                return;
            }
            break;
        case 5:
            if ((s16) temp_r31->unkCEA != 0) {
                temp_r4_5 = &temp_r31->side[0].ply[0]->pos;
                temp_r4_5->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->pos);
                omSetTra(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->pos.x, temp_r31->side[0].ply[0]->pos.y, temp_r31->side[0].ply[0]->pos.z);
            }
            if ((s16) temp_r31->unkCEA != 1) {
                temp_r4_6 = &temp_r31->side[1].ply[0]->pos;
                temp_r4_6->y += 50.0f;
                temp_r31->side[1].ply[0]->pos.x = temp_r31->side[1].ply[0]->pos.x + 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->pos);
                omSetTra(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->pos.x, temp_r31->side[1].ply[0]->pos.y, temp_r31->side[1].ply[0]->pos.z);
                temp_r3_2 = &temp_r31->side[1].ply[1]->pos;
                temp_r3_2->y += 50.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->pos);
                omSetTra(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->pos.x, temp_r31->side[1].ply[1]->pos.y, temp_r31->side[1].ply[1]->pos.z);
                temp_r6 = &temp_r31->side[1].ply[2]->pos;
                temp_r6->y += 50.0f;
                temp_r31->side[1].ply[2]->pos.x = temp_r31->side[1].ply[2]->pos.x - 5.0f;
                Hu3DModelPosSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->pos);
                omSetTra(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->pos.x, temp_r31->side[1].ply[2]->pos.y, temp_r31->side[1].ply[2]->pos.z);
            }
            if (WipeCheckEnd() == 0) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
                return;
            }
            break;
        case 6:
            var_r29 = 0;
loop_33:
            if (var_r29 < 0x20) {
                if ((s16) temp_r31->fieldMdl[var_r29] >= 0) {
                    Hu3DModelAttrSet(temp_r31->fieldMdl[var_r29], 1U);
                }
                var_r29 += 1;
                goto loop_33;
            }
            if ((s16) temp_r31->unkCEA != 0) {
                Hu3DModelAttrSet(temp_r31->side[0].cur.model, 1U);
                Hu3DModelAttrReset(temp_r31->modelCache[63], 1U);
                CharMotionSet(temp_r31->side[0].ply[0]->charNo, temp_r31->side[0].ply[0]->obj->motion[4]);
                CharModelAttrReset(temp_r31->side[0].ply[0]->charNo, 0x40000002U);
                CharModelAttrSet(temp_r31->side[0].ply[0]->charNo, 0x40000001U);
            }
            if ((s16) temp_r31->unkCEA != 1) {
                Hu3DModelAttrSet(temp_r31->side[1].cur.model, 1U);
                Hu3DModelAttrReset(temp_r31->modelCache[64], 1U);
                CharMotionSet(temp_r31->side[1].ply[0]->charNo, temp_r31->side[1].ply[0]->obj->motion[4]);
                CharMotionSet(temp_r31->side[1].ply[1]->charNo, temp_r31->side[1].ply[1]->obj->motion[4]);
                CharMotionSet(temp_r31->side[1].ply[2]->charNo, temp_r31->side[1].ply[2]->obj->motion[4]);
                CharModelAttrReset(temp_r31->side[1].ply[0]->charNo, 0x40000002U);
                CharModelAttrReset(temp_r31->side[1].ply[1]->charNo, 0x40000002U);
                CharModelAttrReset(temp_r31->side[1].ply[2]->charNo, 0x40000002U);
                CharModelAttrSet(temp_r31->side[1].ply[0]->charNo, 0x40000001U);
                CharModelAttrSet(temp_r31->side[1].ply[1]->charNo, 0x40000001U);
                CharModelAttrSet(temp_r31->side[1].ply[2]->charNo, 0x40000001U);
            }
            if ((s16) temp_r31->unkCEA >= 0) {
                temp_r31->view.split = 640.0f;
                fn_1_42A8((M567Main *) temp_r31, (s32) temp_r31->unkCEA);
                temp_r31->cam[0].az = (f32) lbl_1_data_254[0x39];
                temp_r31->cam[0].el = (f32) lbl_1_data_254[0x3A];
                temp_r31->cam[0].dist = (f32) lbl_1_data_254[0x3B];
                temp_r31->cam[0].target.x = (f32) lbl_1_data_254[0x36];
                temp_r31->cam[0].target.y = (f32) lbl_1_data_254[0x37];
                temp_r31->cam[0].target.z = (f32) lbl_1_data_254[0x38];
                Hu3DModelAttrReset(temp_r31->modelCache[11], 1U);
                Hu3DModelCameraSet(temp_r31->side[0].ply[0]->model, (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[0]->model, (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[1]->model, (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[2]->model, (u16) lbl_1_rodata_10[0]);
                var_r29_2 = 0;
loop_44:
                if (var_r29_2 < 7) {
                    var_r28 = 0;
loop_42:
                    if (var_r28 < 3) {
                        Hu3DModelAttrSet(temp_r31->tileA[var_r29_2 * 3 + var_r28], 1U);
                        Hu3DModelCameraSet(temp_r31->tileB[var_r29_2 * 3 + var_r28], (u16) lbl_1_rodata_10[0]);
                        var_r28 += 1;
                        goto loop_42;
                    }
                    var_r29_2 += 1;
                    goto loop_44;
                }
                Hu3DModelCameraSet(temp_r31->tileA[21], (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->tileA[22], (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->tileA[23], (u16) lbl_1_rodata_10[0]);
                Hu3DModelAttrReset(temp_r31->modelCache[8], 1U);
                Hu3DModelAttrSet(temp_r31->modelCache[9], 1U);
                temp_r31->side[temp_r31->unkCEA].cur.pos.x = 0.0f;
                temp_r31->side[temp_r31->unkCEA].cur.pos.y = 0.0f;
                temp_r31->side[temp_r31->unkCEA].cur.pos.z = -300.0f;
                temp_r31->side[temp_r31->unkCEA].cur.rot.x = 0.0f;
                temp_r31->side[temp_r31->unkCEA].cur.rot.y = 0.0f;
                temp_r31->side[temp_r31->unkCEA].cur.rot.z = 0.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.pos.x = 150.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.pos.y = 0.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.pos.z = -900.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.rot.x = 0.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.rot.y = 0.0f;
                temp_r31->side[temp_r31->unkCEA ^ 1].cur.rot.z = 0.0f;
                Hu3DModelPosSetV(temp_r31->side[temp_r31->unkCEA].cur.model, &temp_r31->side[temp_r31->unkCEA].cur.pos);
                Hu3DModelRotSetV(temp_r31->side[temp_r31->unkCEA].cur.model, &temp_r31->side[temp_r31->unkCEA].cur.rot);
                var_r29_3 = 0;
loop_47:
                if (var_r29_3 < 3) {
                    Hu3DModelShadowMapSet(temp_r31->tileB[21 + var_r29_3]);
                    Hu3DModelShadowMapSet(temp_r31->unkCE4[var_r29_3]);
                    var_r29_3 += 1;
                    goto loop_47;
                }
                temp_r31->side[temp_r31->unkCEA].cur.fx = temp_r31->modelCache[29];
                if ((s16) temp_r31->unkCEA == 0) {
                    Hu3DModelHookObjReset(temp_r31->side[0].cur.model, "m567-play0");
                    temp_r31->side[0].ply[0]->pos.x = 0.0f;
                    temp_r31->side[0].ply[0]->pos.y = 0.0f;
                    temp_r31->side[0].ply[0]->pos.z = 0.0f;
                    temp_r31->side[0].ply[0]->rot.x = 0.0f;
                    temp_r31->side[0].ply[0]->rot.y = 0.0f;
                    temp_r31->side[0].ply[0]->rot.z = 0.0f;
                    temp_r31->side[1].ply[0]->pos.x = -300.0f;
                    temp_r31->side[1].ply[0]->pos.y = 0.0f;
                    temp_r31->side[1].ply[0]->pos.z = -200.0f;
                    temp_r31->side[1].ply[0]->rot.x = 0.0f;
                    temp_r31->side[1].ply[0]->rot.y = 0.0f;
                    temp_r31->side[1].ply[0]->rot.z = 0.0f;
                    temp_r31->side[1].ply[1]->pos.x = 225.0f;
                    temp_r31->side[1].ply[1]->pos.y = 0.0f;
                    temp_r31->side[1].ply[1]->pos.z = -200.0f;
                    temp_r31->side[1].ply[1]->rot.x = 0.0f;
                    temp_r31->side[1].ply[1]->rot.y = 0.0f;
                    temp_r31->side[1].ply[1]->rot.z = 0.0f;
                    temp_r31->side[1].ply[2]->pos.x = 375.0f;
                    temp_r31->side[1].ply[2]->pos.y = 0.0f;
                    temp_r31->side[1].ply[2]->pos.z = -200.0f;
                    temp_r31->side[1].ply[2]->rot.x = 0.0f;
                    temp_r31->side[1].ply[2]->rot.y = 0.0f;
                    temp_r31->side[1].ply[2]->rot.z = 0.0f;
                    Hu3DModelPosSetV(temp_r31->modelCache[64], &temp_r31->side[1].cur.pos);
                    Hu3DModelRotSetV(temp_r31->modelCache[64], &temp_r31->side[1].cur.rot);
                    CharMotionSet(temp_r31->side[0].ply[0]->charNo, temp_r31->side[0].ply[0]->obj->motion[3]);
                    Hu3DMotionSet(temp_r31->side[0].cur.model, temp_r31->side[0].cur.mot38);
                    Hu3DModelAttrSet(temp_r31->side[0].cur.model, 0x40000001U);
                    Hu3DModelCameraSet(temp_r31->side[0].cur.model, (u16) lbl_1_rodata_10[0]);
                } else {
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play3");
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play1");
                    Hu3DModelHookObjReset(temp_r31->side[1].cur.model, "m567-play2");
                    temp_r31->side[0].ply[0]->pos.x = -300.0f;
                    temp_r31->side[0].ply[0]->pos.y = 0.0f;
                    temp_r31->side[0].ply[0]->pos.z = -200.0f;
                    temp_r31->side[0].ply[0]->rot.x = 0.0f;
                    temp_r31->side[0].ply[0]->rot.y = 0.0f;
                    temp_r31->side[0].ply[0]->rot.z = 0.0f;
                    temp_r31->side[1].ply[0]->pos.x = -200.0f;
                    temp_r31->side[1].ply[0]->pos.y = 0.0f;
                    temp_r31->side[1].ply[0]->pos.z = 0.0f;
                    temp_r31->side[1].ply[0]->rot.x = 0.0f;
                    temp_r31->side[1].ply[0]->rot.y = 0.0f;
                    temp_r31->side[1].ply[0]->rot.z = 0.0f;
                    temp_r31->side[1].ply[1]->pos.x = 0.0f;
                    temp_r31->side[1].ply[1]->pos.y = 0.0f;
                    temp_r31->side[1].ply[1]->pos.z = 0.0f;
                    temp_r31->side[1].ply[1]->rot.x = 0.0f;
                    temp_r31->side[1].ply[1]->rot.y = 0.0f;
                    temp_r31->side[1].ply[1]->rot.z = 0.0f;
                    temp_r31->side[1].ply[2]->pos.x = 200.0f;
                    temp_r31->side[1].ply[2]->pos.y = 0.0f;
                    temp_r31->side[1].ply[2]->pos.z = 0.0f;
                    temp_r31->side[1].ply[2]->rot.x = 0.0f;
                    temp_r31->side[1].ply[2]->rot.y = 0.0f;
                    temp_r31->side[1].ply[2]->rot.z = 0.0f;
                    Hu3DModelPosSetV(temp_r31->modelCache[63], &temp_r31->side[0].cur.pos);
                    Hu3DModelRotSetV(temp_r31->modelCache[63], &temp_r31->side[0].cur.rot);
                    CharMotionSet(temp_r31->side[1].ply[0]->charNo, temp_r31->side[1].ply[0]->obj->motion[3]);
                    CharMotionSet(temp_r31->side[1].ply[1]->charNo, temp_r31->side[1].ply[1]->obj->motion[3]);
                    CharMotionSet(temp_r31->side[1].ply[2]->charNo, temp_r31->side[1].ply[2]->obj->motion[3]);
                    Hu3DModelRotSet(temp_r31->modelCache[23], 0.0f, 180.0f, 0.0f);
                    Hu3DModelRotSet(temp_r31->unkCE4[0], 0.0f, 180.0f, 0.0f);
                    Hu3DModelRotSet(temp_r31->unkCE4[1], 0.0f, 180.0f, 0.0f);
                    Hu3DModelRotSet(temp_r31->unkCE4[2], 0.0f, 180.0f, 0.0f);
                    Hu3DMotionSet(temp_r31->side[1].cur.model, temp_r31->side[1].cur.mot38);
                    Hu3DModelAttrSet(temp_r31->side[1].cur.model, 0x40000001U);
                    Hu3DModelCameraSet(temp_r31->side[1].cur.model, (u16) lbl_1_rodata_10[0]);
                }
            } else {
                fn_1_4168();
                temp_r31->side[0].cur.pos.x = 0.0f;
                temp_r31->side[0].cur.pos.y = 0.0f;
                temp_r31->side[0].cur.pos.z = 2100.0f;
                temp_r31->side[0].cur.rot.x = 0.0f;
                temp_r31->side[0].cur.rot.y = 0.0f;
                temp_r31->side[0].cur.rot.z = 0.0f;
                temp_r31->side[0].ply[0]->pos.x = 0.0f;
                temp_r31->side[0].ply[0]->pos.y = 0.0f;
                temp_r31->side[0].ply[0]->pos.z = 2400.0f;
                temp_r31->side[0].ply[0]->rot.x = 0.0f;
                temp_r31->side[0].ply[0]->rot.y = 0.0f;
                temp_r31->side[0].ply[0]->rot.z = 0.0f;
                temp_r31->side[1].cur.pos.x = 0.0f;
                temp_r31->side[1].cur.pos.y = 0.0f;
                temp_r31->side[1].cur.pos.z = -2100.0f;
                temp_r31->side[1].cur.rot.x = 0.0f;
                temp_r31->side[1].cur.rot.y = 180.0f;
                temp_r31->side[1].cur.rot.z = 0.0f;
                temp_r31->side[1].ply[0]->pos.x = 200.0f;
                temp_r31->side[1].ply[0]->pos.y = 0.0f;
                temp_r31->side[1].ply[0]->pos.z = -2400.0f;
                temp_r31->side[1].ply[0]->rot.x = 0.0f;
                temp_r31->side[1].ply[0]->rot.y = 180.0f;
                temp_r31->side[1].ply[0]->rot.z = 0.0f;
                temp_r31->side[1].ply[1]->pos.x = 0.0f;
                temp_r31->side[1].ply[1]->pos.y = 0.0f;
                temp_r31->side[1].ply[1]->pos.z = -2400.0f;
                temp_r31->side[1].ply[1]->rot.x = 0.0f;
                temp_r31->side[1].ply[1]->rot.y = 180.0f;
                temp_r31->side[1].ply[1]->rot.z = 0.0f;
                temp_r31->side[1].ply[2]->pos.x = -200.0f;
                temp_r31->side[1].ply[2]->pos.y = 0.0f;
                temp_r31->side[1].ply[2]->pos.z = -2400.0f;
                temp_r31->side[1].ply[2]->rot.x = 0.0f;
                temp_r31->side[1].ply[2]->rot.y = 180.0f;
                temp_r31->side[1].ply[2]->rot.z = 0.0f;
                temp_r31->cam[0].az = (f32) lbl_1_data_254[0x2D];
                temp_r31->cam[0].el = (f32) lbl_1_data_254[0x2E];
                temp_r31->cam[0].dist = (f32) lbl_1_data_254[0x2F];
                temp_r31->cam[0].target.x = (f32) lbl_1_data_254[0x2A];
                temp_r31->cam[0].target.y = (f32) lbl_1_data_254[0x2B];
                temp_r31->cam[0].target.z = (f32) lbl_1_data_254[0x2C];
                temp_r31->cam[1].az = (f32) lbl_1_data_254[0x33];
                temp_r31->cam[1].el = (f32) lbl_1_data_254[0x34];
                temp_r31->cam[1].dist = (f32) lbl_1_data_254[0x35];
                temp_r31->cam[1].target.x = (f32) lbl_1_data_254[0x30];
                temp_r31->cam[1].target.y = (f32) lbl_1_data_254[0x31];
                temp_r31->cam[1].target.z = (f32) lbl_1_data_254[0x32];
                Hu3DModelCameraSet(temp_r31->side[0].ply[0]->model, (u16) lbl_1_rodata_10[0]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[0]->model, (u16) lbl_1_rodata_10[1]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[1]->model, (u16) lbl_1_rodata_10[1]);
                Hu3DModelCameraSet(temp_r31->side[1].ply[2]->model, (u16) lbl_1_rodata_10[1]);
                Hu3DModelPosSetV(temp_r31->modelCache[63], &temp_r31->side[0].cur.pos);
                Hu3DModelPosSetV(temp_r31->modelCache[64], &temp_r31->side[1].cur.pos);
                Hu3DModelRotSetV(temp_r31->modelCache[63], &temp_r31->side[0].cur.rot);
                Hu3DModelRotSetV(temp_r31->modelCache[64], &temp_r31->side[1].cur.rot);
                var_r29_4 = 0;
loop_53:
                if (var_r29_4 < 3) {
                    Hu3DModelCameraSet(temp_r31->tileA[var_r29_4], (u16) lbl_1_rodata_10[0]);
                    Hu3DModelShadowMapSet(temp_r31->tileA[var_r29_4]);
                    Hu3DModelCameraSet(temp_r31->tileB[var_r29_4], (u16) lbl_1_rodata_10[1]);
                    Hu3DModelShadowMapSet(temp_r31->tileB[var_r29_4]);
                    var_r29_4 += 1;
                    goto loop_53;
                }
                var_r29_5 = 0;
loop_59:
                if (var_r29_5 < 8) {
                    var_r28_2 = 0;
loop_57:
                    if (var_r28_2 < 3) {
                        Hu3DModelAttrReset(temp_r31->tileA[var_r29_5 * 3 + var_r28_2], 1U);
                        Hu3DModelAttrReset(temp_r31->tileB[var_r29_5 * 3 + var_r28_2], 1U);
                        var_r28_2 += 1;
                        goto loop_57;
                    }
                    var_r29_5 += 1;
                    goto loop_59;
                }
            }
            Hu3DModelPosSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->pos);
            omSetTra(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->pos.x, temp_r31->side[0].ply[0]->pos.y, temp_r31->side[0].ply[0]->pos.z);
            Hu3DModelRotSetV(temp_r31->side[0].ply[0]->model, &temp_r31->side[0].ply[0]->rot);
            omSetRot(temp_r31->side[0].ply[0]->obj, temp_r31->side[0].ply[0]->rot.x, temp_r31->side[0].ply[0]->rot.y, temp_r31->side[0].ply[0]->rot.z);
            Hu3DModelPosSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->pos);
            omSetTra(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->pos.x, temp_r31->side[1].ply[0]->pos.y, temp_r31->side[1].ply[0]->pos.z);
            Hu3DModelRotSetV(temp_r31->side[1].ply[0]->model, &temp_r31->side[1].ply[0]->rot);
            omSetRot(temp_r31->side[1].ply[0]->obj, temp_r31->side[1].ply[0]->rot.x, temp_r31->side[1].ply[0]->rot.y, temp_r31->side[1].ply[0]->rot.z);
            Hu3DModelPosSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->pos);
            omSetTra(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->pos.x, temp_r31->side[1].ply[1]->pos.y, temp_r31->side[1].ply[1]->pos.z);
            Hu3DModelRotSetV(temp_r31->side[1].ply[1]->model, &temp_r31->side[1].ply[1]->rot);
            omSetRot(temp_r31->side[1].ply[1]->obj, temp_r31->side[1].ply[1]->rot.x, temp_r31->side[1].ply[1]->rot.y, temp_r31->side[1].ply[1]->rot.z);
            Hu3DModelPosSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->pos);
            omSetTra(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->pos.x, temp_r31->side[1].ply[2]->pos.y, temp_r31->side[1].ply[2]->pos.z);
            Hu3DModelRotSetV(temp_r31->side[1].ply[2]->model, &temp_r31->side[1].ply[2]->rot);
            omSetRot(temp_r31->side[1].ply[2]->obj, temp_r31->side[1].ply[2]->rot.x, temp_r31->side[1].ply[2]->rot.y, temp_r31->side[1].ply[2]->rot.z);
            Hu3DModelShadowSet(temp_r31->side[0].ply[0]->model);
            Hu3DModelShadowSet(temp_r31->side[1].ply[0]->model);
            Hu3DModelShadowSet(temp_r31->side[1].ply[1]->model);
            Hu3DModelShadowSet(temp_r31->side[1].ply[2]->model);
            WipeCreate(1, 0, 0x3C);
            temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            return;
        case 7:
            if (WipeCheckEnd() == 0) {
                temp_r31->unkCEC = (s16) (temp_r31->unkCEC + 1);
            }
            if (((s16) temp_r31->unkCEA >= 0) && (temp_r30 = &temp_r31->side[temp_r31->unkCEA].cur, temp_f1 = Hu3DMotionTimeGet(temp_r30->model), ((temp_f1 >= 40.0f) != 0)) && (temp_f1 < 41.0f)) {
                fn_1_4704(&temp_r31->pool, fn_1_988C, temp_r30);
                Hu3DModelAttrReset(temp_r30->fx, 1U);
                Hu3DModelAttrReset(temp_r30->fx, 0x40000002U);
                Hu3DMotionTimeSet(temp_r30->fx, 0.0f);
                Hu3DModelPosSet(temp_r30->fx, temp_r30->pos.x, temp_r30->pos.y, temp_r30->pos.z);
                if ((s16) temp_r31->unkCEA == 0) {
                    lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                }
                if ((s16) temp_r31->unkCEA == 1) {
                    lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                    return;
                }
            }
            break;
        case 8:
            if ((s16) temp_r31->unkCEA >= 0) {
                temp_r30_2 = &temp_r31->side[temp_r31->unkCEA].cur;
                temp_f1_2 = Hu3DMotionTimeGet(temp_r30_2->model);
                if ((temp_f1_2 >= 40.0f) && (temp_f1_2 < 41.0f)) {
                    fn_1_4704(&temp_r31->pool, fn_1_988C, temp_r30_2);
                    Hu3DModelAttrReset(temp_r30_2->fx, 1U);
                    Hu3DModelAttrReset(temp_r30_2->fx, 0x40000002U);
                    Hu3DMotionTimeSet(temp_r30_2->fx, 0.0f);
                    Hu3DModelPosSet(temp_r30_2->fx, temp_r30_2->pos.x, temp_r30_2->pos.y, temp_r30_2->pos.z);
                    if ((s16) temp_r31->unkCEA == 0) {
                        lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                    }
                    if ((s16) temp_r31->unkCEA == 1) {
                        lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                    }
                }
            }
            MgSeqModeNext();
            break;
        }
    }
}

void fn_1_32CC(s16 mode, s16 frameNo) {
    M567Cursor *temp_r30;
    f32 temp_f1;
    s16 temp_r0;
    s16 temp_r26;
    s16 temp_r27;
    s16 temp_r28;
    s16 temp_r29;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r0 = temp_r31->unkCF0;
    switch (temp_r0) {                              /* irregular */
    case 0:
        if ((s16) temp_r31->unkCEA == 0) {
            temp_r29 = temp_r31->side[0].ply[0]->player;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r29].coin_win = 0xA;
            }
            CharModelAttrReset(temp_r31->side[0].ply[0]->charNo, 0x40000002U);
        }
        if ((s16) temp_r31->unkCEA == 1) {
            temp_r28 = temp_r31->side[1].ply[0]->player;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r28].coin_win = 0xA;
            }
            temp_r27 = temp_r31->side[1].ply[1]->player;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r27].coin_win = 0xA;
            }
            temp_r26 = temp_r31->side[1].ply[2]->player;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r26].coin_win = 0xA;
            }
            CharModelAttrReset(temp_r31->side[1].ply[0]->charNo, 0x40000002U);
            CharModelAttrReset(temp_r31->side[1].ply[1]->charNo, 0x40000002U);
            CharModelAttrReset(temp_r31->side[1].ply[2]->charNo, 0x40000002U);
        }
        if ((s16) temp_r31->unkCEA < 0) {
            CharModelVoicePanSet(temp_r31->side[0].ply[0]->charNo, 0x30);
            CharModelVoicePanSet(temp_r31->side[1].ply[0]->charNo, 0x50);
            CharModelVoicePanSet(temp_r31->side[1].ply[1]->charNo, 0x50);
            CharModelVoicePanSet(temp_r31->side[1].ply[2]->charNo, 0x50);
            CharLoseVoicePlay(temp_r31->ply[0]->charNo, temp_r31->ply[1]->charNo, temp_r31->ply[2]->charNo, temp_r31->ply[3]->charNo);
        }
        temp_r31->unkCF0 = (s16) (temp_r31->unkCF0 + 1);
        /* fallthrough */
    case 1:
        if (((s16) temp_r31->unkCEA >= 0) && (temp_r31->unkCF2 = (s16) (temp_r31->unkCF2 + 1), temp_r30 = &temp_r31->side[temp_r31->unkCEA].cur, temp_f1 = Hu3DMotionTimeGet(temp_r30->model), ((temp_f1 >= 40.0f) != 0)) && (temp_f1 < 41.0f)) {
            fn_1_4704(&temp_r31->pool, fn_1_988C, temp_r30);
            Hu3DModelAttrReset(temp_r30->fx, 1U);
            Hu3DModelAttrReset(temp_r30->fx, 0x40000002U);
            Hu3DMotionTimeSet(temp_r30->fx, 0.0f);
            Hu3DModelPosSetV(temp_r30->fx, &temp_r30->pos);
            if ((s16) temp_r31->unkCF2 < 0xB4) {
                if ((s16) temp_r31->unkCEA == 0) {
                    lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                }
                if ((s16) temp_r31->unkCEA == 1) {
                    lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                    return;
                }
            } else if (HuAudFXStatusGet(lbl_1_data_43C[temp_r31->unkCEA]) == 2) {
                HuAudFXFadeOut(lbl_1_data_43C[temp_r31->unkCEA], 0x3E8);
            }
        } else {
            return;
        }
        break;
    }
}

void fn_1_362C(s16 mode, s16 frameNo) {
    M567Cursor *temp_r31;
    f32 temp_f1;
    M567Main *temp_r30;

    temp_r30 = lbl_1_bss_4->data;
    if ((s16) temp_r30->unkCEA >= 0) {
        temp_r31 = &temp_r30->side[temp_r30->unkCEA].cur;
        temp_f1 = Hu3DMotionTimeGet(temp_r31->model);
        if ((temp_f1 >= 40.0f) && (temp_f1 < 41.0f)) {
            fn_1_4704(&temp_r30->pool, fn_1_988C, temp_r31);
            Hu3DModelAttrReset(temp_r31->fx, 1U);
            Hu3DModelAttrReset(temp_r31->fx, 0x40000002U);
            Hu3DMotionTimeSet(temp_r31->fx, 0.0f);
            Hu3DModelPosSetV(temp_r31->fx, &temp_r31->pos);
        }
    }
}

void fn_1_371C(s16 mode, s16 frameNo) {
    fn_1_4164();
}

void fn_1_3758(omObjData *obj) {
    s32 var_r29;
    M567Player *temp_r31;

    temp_r31 = obj->data;
    temp_r31->player = (s16) obj->work[0];
    temp_r31->charNo = (s16) GWPlayerCfg[temp_r31->player].character;
    temp_r31->group = (s16) GWPlayerCfg[temp_r31->player].group;
    temp_r31->pad = (s16) GWPlayerCfg[temp_r31->player].pad_idx;
    temp_r31->isCom = (s16) GWPlayerCfg[temp_r31->player].iscom;
    temp_r31->dif = (s16) GWPlayerCfg[temp_r31->player].diff;
    temp_r31->obj = obj;
    ((M567Main *) lbl_1_bss_4->data)->ply[temp_r31->player] = temp_r31;
    *obj->model = CharModelCreate(temp_r31->charNo, 8);
    temp_r31->model = (s16) *obj->model;
    var_r29 = 0;
loop_2:
    if (var_r29 < 5) {
        obj->motion[var_r29] = Mp5CharMotionCreateData(temp_r31->charNo, ((u32 *)&lbl_1_data_28[Mp5CharNo(temp_r31->charNo)])[var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionSet(temp_r31->charNo, obj->motion[1]);
    obj->work[1] = 0;
    Hu3DModelLayerSet(*obj->model, 2);
    CharEffectLayerSet(4);
    CharMotionDataClose(temp_r31->charNo);
    m567Ready++;
    obj->func = fn_1_3908;
}

void fn_1_3908(omObjData *obj) {
    M567Player *temp_r31;

    temp_r31 = obj->data;
    if (obj->work[1] < 3 && ++obj->work[1] == 3) {
        Hu3DMotionTimeSet(*obj->model, 0.0f);
        CharModelAttrSet(temp_r31->charNo, 0x40000002U);
    }
    if (((s16) ((M567Main *)lbl_1_bss_4->data)->unkCF4 != 0) && ((s16) temp_r31->reel->state == 0xF)) {
        if ((s16) temp_r31->isCom != 0) {
            fn_1_8F1C((M567Player *) temp_r31);
            return;
        }
        fn_1_8EC8((M567Player *) temp_r31);
    }
}


void fn_1_3994(omObjData *obj) {
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    fn_1_4680(&temp_r31->pool, &temp_r31->nodes[0], 0x64);
    temp_r31->unkCEA = -1;
    obj->func = fn_1_39F8;
}

void fn_1_39F8(omObjData *obj) {
    Vec sp8;
    s32 temp_r28;
    s32 temp_r29;
    M567Side *temp_r30;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r28 = fn_1_7084(&temp_r31->side[0]);
    temp_r29 = fn_1_7084(&temp_r31->side[1]);
    if ((temp_r28 != 0) || (temp_r29 != 0)) {
        if (temp_r28 != 0) {
            if (temp_r29 != 0) {
                temp_r31->unkCEA = frandmod(2U);
            } else {
                temp_r31->unkCEA = 0;
            }
        } else if (temp_r29 != 0) {
            temp_r31->unkCEA = 1;
        }
        if (((s16) temp_r31->side[0].state != 4) && ((s16) temp_r31->side[0].state != 7) && ((s16) temp_r31->side[0].state != 8)) {
            temp_r31->side[0].state = 7;
        }
        if (((s16) temp_r31->side[1].state != 4) && ((s16) temp_r31->side[1].state != 7) && ((s16) temp_r31->side[1].state != 8)) {
            temp_r31->side[1].state = 7;
        }
        temp_r30 = &temp_r31->side[temp_r31->unkCEA ^ 1];
        if ((s16) temp_r30->nrow == 9) {
            temp_r30->nrow = (s16) temp_r30->row;
            temp_r30->cur.to.z = (f32) temp_r30->cur.from.z;
        }
    }
    fn_1_4404(&temp_r31->cam[0], &sp8);
    fn_1_8330(&temp_r31->side[0].slot);
    fn_1_4404(&temp_r31->cam[1], &sp8);
    fn_1_8330(&temp_r31->side[1].slot);
    fn_1_3EEC(&temp_r31->view);
    fn_1_47D0(&temp_r31->pool);
}


void fn_1_3B78(M567Main *m) {
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x41) {
        m->modelCache[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 9) {
        m->motionCache[var_r31_2] = -1;
        var_r31_2 += 1;
        goto loop_5;
    }
    var_r31_3 = 0;
loop_8:
    if (var_r31_3 < 0x20) {
        m->fieldMdl[var_r31_3] = -1;
        var_r31_3 += 1;
        goto loop_8;
    }
}

void fn_1_3BF8(void) {
    Hu3DGLightInfinitytSet(Hu3DGLightCreate(0.0f, 4000.0f, 0.0f, 0.0f, -1.0f, -1.0f, 0x7FU, 0x7FU, 0x7FU));
}

void fn_1_3C80(M567Main *m) {
    f32 sp8;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        Hu3DCameraCreate((s32) lbl_1_rodata_10[var_r31]);
        Hu3DCameraPerspectiveSet((s32) lbl_1_rodata_10[var_r31], 45.0f, 20.0f, 20000.0f, 0.6f);
        sp8 = 0.0f;
        Hu3DCameraPosSet((s32) lbl_1_rodata_10[var_r31], 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, 0.0f);
        fn_1_439C(&m->cam[var_r31], (s16) lbl_1_rodata_10[var_r31]);
        m->cam[var_r31].az = lbl_1_data_254[var_r31 * 6 + 3];
        m->cam[var_r31].el = lbl_1_data_254[var_r31 * 6 + 4];
        m->cam[var_r31].dist = lbl_1_data_254[var_r31 * 6 + 5];
        m->cam[var_r31].target.x = lbl_1_data_254[var_r31 * 6];
        m->cam[var_r31].target.y = lbl_1_data_254[var_r31 * 6 + 1];
        m->cam[var_r31].target.z = lbl_1_data_254[var_r31 * 6 + 2];
        var_r31 += 1;
        goto loop_2;
    }
}

void fn_1_3E94(M567View *v) {
    v->split = 640.0f;
    v->unk4 = 0.0f;
    v->unk8 = 0;
    fn_1_3EEC(v);
}

void fn_1_3EEC(M567View *v) {
    f32 var_f31;

    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[0], 0.0f, 0.0f, 16.0f + v->split, 480.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet((s32) lbl_1_rodata_10[1], v->split - 16.0f, 0.0f, 16.0f + (640.0f - v->split), 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[0], 0U, 0U, (u32) (v->split - 1.0f), 0x1E0U);
    Hu3DCameraScissorSet((s32) lbl_1_rodata_10[1], (u32) (1.0f + v->split), 0U, (u32) ((640.0f - v->split) - 1.0f), 0x1E0U);
    var_f31 = (0.9f * v->split) / 480.0f;
    if (var_f31 < 0.0f) {
        var_f31 = 0.0f;
    }
    Hu3DCameraPerspectiveSet((s32) lbl_1_rodata_10[0], 45.0f, 20.0f, 20000.0f, var_f31);
}

void fn_1_4164(void) {

}

void fn_1_4168(void) {
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
    Hu3DShadowMultiCreate(45.0f, 20.0f, 20000.0f, (s16) (lbl_1_rodata_10[0] | lbl_1_rodata_10[1]));
    Hu3DShadowMultiPosSet(&sp14, &sp20, &sp8, (s16) lbl_1_rodata_10[0]);
    sp14.z *= -1.0f;
    sp8.z *= -1.0f;
    Hu3DShadowMultiPosSet(&sp14, &sp20, &sp8, (s16) lbl_1_rodata_10[1]);
}

void fn_1_42A8(M567Main *m, s32 side) {
    Vec spC;
    Vec sp24;
    Vec sp18;
    s32 sp8;

    sp8 = side;
    sp24.x = lbl_1_rodata_104.x;
    sp24.y = lbl_1_rodata_104.y;
    sp24.z = lbl_1_rodata_104.z;
    sp18.x = lbl_1_rodata_110.x;
    sp18.y = lbl_1_rodata_110.y;
    sp18.z = lbl_1_rodata_110.z;
    spC.x = lbl_1_rodata_11C.x;
    spC.y = lbl_1_rodata_11C.y;
    spC.z = lbl_1_rodata_11C.z;
    Hu3DShadowCreate(45.0f, 20.0f, 20000.0f);
    if (sp8 != 0) {
        sp18.z *= -1.0f;
        spC.z *= -1.0f;
    }
    Hu3DShadowPosSet(&sp18, &sp24, &spC);
}

void fn_1_439C(M567Cam *cam, s16 camBit) {
    cam->target.x = 0.0f;
    cam->target.y = 0.0f;
    cam->target.z = 0.0f;
    cam->az = 0.0f;
    cam->el = 0.0f;
    cam->dist = 3000.0f;
    cam->camBit = camBit;
}

void fn_1_4404(M567Cam *cam, Vec *pos) {
    f32 sp8;
    f64 temp_f31;
    f64 temp_f31_2;

loop_2:
    if (cam->az > 360.0f) {
        cam->az -= 360.0f;
        goto loop_2;
    }
loop_5:
    if (cam->az < 0.0f) {
        cam->az += 360.0f;
        goto loop_5;
    }
loop_8:
    if (cam->el > 360.0f) {
        cam->el -= 360.0f;
        goto loop_8;
    }
loop_11:
    if (cam->el < 0.0f) {
        cam->el += 360.0f;
        goto loop_11;
    }
    temp_f31 = cos((3.141592653589793 * (f64) cam->az) / 180.0);
    pos->x = (f32) ((f64) cam->target.x + ((f64) cam->dist * cos((3.141592653589793 * (f64) cam->el) / 180.0) * temp_f31));
    pos->y = (f32) ((f64) cam->target.y + ((f64) cam->dist * sin((3.141592653589793 * (f64) cam->el) / 180.0)));
    temp_f31_2 = sin((3.141592653589793 * (f64) cam->az) / 180.0);
    pos->z = (f32) ((f64) cam->target.z + ((f64) cam->dist * cos((3.141592653589793 * (f64) cam->el) / 180.0) * temp_f31_2));
    sp8 = cam->target.z;
    Hu3DCameraPosSet((s32) cam->camBit, pos->x, pos->y, pos->z, 0.0f, 1.0f, 0.0f, cam->target.x, cam->target.y, cam->target.z);
}

void fn_1_4680(M567Pool *pool, M567Node *nodes, s32 count) {
    M567Node *var_r4;
    s32 var_r31;

    var_r4 = nodes;
    pool->head = NULL;
    pool->free = var_r4;
    var_r31 = 0;
loop_2:
    if (var_r31 < (s32) (count - 1)) {
        var_r4->prev = NULL;
        var_r4->next = var_r4 + 1;
        var_r4->func = NULL;
        var_r4->arg = NULL;
        var_r4->pool = pool;
        var_r31 += 1;
        var_r4++;
        goto loop_2;
    }
    var_r4->prev = NULL;
    var_r4->next = NULL;
    var_r4->func = NULL;
    var_r4->arg = NULL;
    var_r4->pool = pool;
}

M567Node *fn_1_4704(M567Pool *pool, s32 (*func)(M567Node *), void *arg) {
    M567Node *temp_r31;

    temp_r31 = pool->free;
    if (temp_r31 != NULL) {
        pool->free = temp_r31->next;
        temp_r31->func = func;
        temp_r31->arg = arg;
        temp_r31->next = pool->head;
        if ((M567Node *) temp_r31->next != NULL) {
            temp_r31->next->prev = temp_r31;
        }
        pool->head = temp_r31;
    }
    return temp_r31;
}


void fn_1_47D0(M567Pool *pool) {
    M567Node *temp_r29;
    M567Node *var_r31;
    M567Pool *temp_r30;

    var_r31 = pool->head;
loop_11:
    if (var_r31 != NULL) {
        temp_r29 = var_r31->next;
        if (((void *) var_r31->func != NULL) && (((s32 (*)(M567Node *)) var_r31->func)(var_r31) != 0) && (var_r31 != NULL)) {
            temp_r30 = var_r31->pool;
            if ((M567Node *) var_r31->prev != NULL) {
                var_r31->prev->next = var_r31->next;
            } else {
                temp_r30->head = var_r31->next;
            }
            if ((M567Node *) var_r31->next != NULL) {
                var_r31->next->prev = var_r31->prev;
            }
            var_r31->prev = NULL;
            var_r31->next = temp_r30->free;
            var_r31->func = NULL;
            temp_r30->free = var_r31;
        }
        var_r31 = temp_r29;
        goto loop_11;
    }
}

void fn_1_48B0(M567Main *m) {
    s16 spC[24];
    s32 sp8;
    s16 *temp_r24;
    s16 temp_r3;
    s16 temp_r3_10;
    s16 temp_r3_11;
    s16 temp_r3_12;
    s16 temp_r3_13;
    s16 temp_r3_14;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r3_9;
    s16 var_r31;
    s16 var_r31_10;
    s16 var_r31_11;
    s16 var_r31_12;
    s16 var_r31_13;
    s16 var_r31_14;
    s16 var_r31_15;
    s16 var_r31_16;
    s16 var_r31_2;
    s16 var_r31_3;
    s16 var_r31_4;
    s16 var_r31_5;
    s16 var_r31_6;
    s16 var_r31_7;
    s16 var_r31_8;
    s16 var_r31_9;
    s32 var_r25;
    s32 var_r27;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    u32 temp_r26;

    if ((s16) m->modelCache[8] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[8] = temp_r3;
        var_r31 = temp_r3;
    } else {
        var_r31 = Hu3DModelLink(m->modelCache[8]);
    }
    Hu3DModelAttrSet(var_r31, 1U);
    Hu3DModelAttrSet(var_r31, 0x40000002U);
    Hu3DModelLayerSet(var_r31, 0);
    Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(var_r31, (u16) *lbl_1_rodata_10);
    if ((s16) m->modelCache[9] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[9], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[9] = temp_r3_2;
        var_r31_2 = temp_r3_2;
    } else {
        var_r31_2 = Hu3DModelLink(m->modelCache[9]);
    }
    Hu3DModelAttrSet(var_r31_2, 1U);
    Hu3DModelAttrSet(var_r31_2, 0x40000002U);
    Hu3DModelLayerSet(var_r31_2, 0);
    Hu3DModelPosSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_2, 1U);
    if ((s16) m->modelCache[0xA] < 0) {
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0xA] = temp_r3_3;
        var_r31_3 = temp_r3_3;
    } else {
        var_r31_3 = Hu3DModelLink(m->modelCache[0xA]);
    }
    Hu3DModelAttrSet(var_r31_3, 1U);
    Hu3DModelAttrSet(var_r31_3, 0x40000002U);
    Hu3DModelLayerSet(var_r31_3, 1);
    Hu3DModelPosSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_3, 1U);
    if ((s16) m->modelCache[0xB] < 0) {
        temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0xB] = temp_r3_4;
        var_r31_4 = temp_r3_4;
    } else {
        var_r31_4 = Hu3DModelLink(m->modelCache[0xB]);
    }
    Hu3DModelAttrSet(var_r31_4, 1U);
    Hu3DModelAttrSet(var_r31_4, 0x40000001U);
    Hu3DModelLayerSet(var_r31_4, 1);
    Hu3DModelPosSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(var_r31_4, (u16) *lbl_1_rodata_10);
    if ((s16) m->modelCache[0xC] < 0) {
        temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0xC] = temp_r3_5;
        var_r31_5 = temp_r3_5;
    } else {
        var_r31_5 = Hu3DModelLink(m->modelCache[0xC]);
    }
    Hu3DModelAttrSet(var_r31_5, 1U);
    Hu3DModelAttrSet(var_r31_5, 0x40000002U);
    Hu3DModelLayerSet(var_r31_5, 1);
    Hu3DModelPosSet(var_r31_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(var_r31_5, (u16) *lbl_1_rodata_10);
    Hu3DModelAttrReset(var_r31_5, 1U);
    if ((s16) m->modelCache[0x17] < 0) {
        temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x17], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x17] = temp_r3_6;
        var_r31_6 = temp_r3_6;
    } else {
        var_r31_6 = Hu3DModelLink(m->modelCache[0x17]);
    }
    Hu3DModelAttrSet(var_r31_6, 1U);
    Hu3DModelAttrSet(var_r31_6, 0x40000002U);
    Hu3DModelLayerSet(var_r31_6, 1);
    Hu3DModelPosSet(var_r31_6, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_6, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_6, 1U);
    if ((s16) m->modelCache[0x19] < 0) {
        temp_r3_7 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x19], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x19] = temp_r3_7;
        var_r31_7 = temp_r3_7;
    } else {
        var_r31_7 = Hu3DModelLink(m->modelCache[0x19]);
    }
    Hu3DModelAttrSet(var_r31_7, 1U);
    Hu3DModelAttrSet(var_r31_7, 0x40000002U);
    Hu3DModelLayerSet(var_r31_7, 1);
    Hu3DModelPosSet(var_r31_7, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_7, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_7, 1U);
    if ((s16) m->modelCache[0x1A] < 0) {
        temp_r3_8 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x1A], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x1A] = temp_r3_8;
        var_r31_8 = temp_r3_8;
    } else {
        var_r31_8 = Hu3DModelLink(m->modelCache[0x1A]);
    }
    Hu3DModelAttrSet(var_r31_8, 1U);
    Hu3DModelAttrSet(var_r31_8, 0x40000002U);
    Hu3DModelLayerSet(var_r31_8, 1);
    Hu3DModelPosSet(var_r31_8, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_8, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_8, 1U);
    if ((s16) m->modelCache[0x3F] < 0) {
        temp_r3_9 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x3F], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x3F] = temp_r3_9;
        var_r31_9 = temp_r3_9;
    } else {
        var_r31_9 = Hu3DModelLink(m->modelCache[0x3F]);
    }
    Hu3DModelAttrSet(var_r31_9, 1U);
    Hu3DModelAttrSet(var_r31_9, 0x40000002U);
    Hu3DModelLayerSet(var_r31_9, 2);
    Hu3DModelPosSet(var_r31_9, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_9, 0.0f, 0.0f, 0.0f);
    if ((s16) m->modelCache[0x40] < 0) {
        var_r31_10 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x40], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x40] = var_r31_10;
    } else {
        var_r31_10 = Hu3DModelLink(m->modelCache[0x40]);
    }
    Hu3DModelAttrSet(var_r31_10, 1U);
    Hu3DModelAttrSet(var_r31_10, 0x40000002U);
    Hu3DModelLayerSet(var_r31_10, 2);
    Hu3DModelPosSet(var_r31_10, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_10, 0.0f, 0.0f, 0.0f);
    if ((s16) m->modelCache[0x1D] < 0) {
        temp_r3_10 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x1D], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[0x1D] = temp_r3_10;
        var_r31_11 = temp_r3_10;
    } else {
        var_r31_11 = Hu3DModelLink(m->modelCache[0x1D]);
    }
    Hu3DModelAttrSet(var_r31_11, 1U);
    Hu3DModelAttrSet(var_r31_11, 0x40000002U);
    Hu3DModelLayerSet(var_r31_11, 4);
    Hu3DModelPosSet(var_r31_11, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_11, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(var_r31_11, (u16) *lbl_1_rodata_10);
    temp_r24 = m->side[0].grid[0];
    var_r25 = 0;
    temp_r26 = frandmod(5U);
    var_r27 = 0;
    sp8 = 0;
    var_r28 = 1;
loop_46:
    if (var_r28 < 9) {
        var_r29 = 1;
loop_44:
        if (var_r29 < 4) {
            if ((s16) *(s16 *) ((u8 *) temp_r24 + ((var_r28 * 0xA) + (var_r29 * 2))) == -1) {
                spC[(var_r28 - 1) * 3 + (var_r29 - 1)] = frandmod(4U);
                if ((s16) m->modelCache[spC[(var_r28 - 1) * 3 + (var_r29 - 1)] + 0xD] < 0) {
                    temp_r3_11 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[spC[(var_r28 - 1) * 3 + (var_r29 - 1)] + 0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
                    m->modelCache[spC[(var_r28 - 1) * 3 + (var_r29 - 1)] + 0xD] = temp_r3_11;
                    var_r31_12 = temp_r3_11;
                } else {
                    var_r31_12 = Hu3DModelLink(m->modelCache[spC[(var_r28 - 1) * 3 + (var_r29 - 1)] + 0xD]);
                }
                m->fieldMdl[var_r25] = var_r31_12;
                var_r25 += 1;
                Hu3DModelAttrSet(var_r31_12, 1U);
                Hu3DModelAttrSet(var_r31_12, 0x40000002U);
                Hu3DModelLayerSet(var_r31_12, 0);
                Hu3DModelPosSet(var_r31_12, 300.0f * (f32) (var_r29 - 2), 0.0f, 2700.0f - (300.0f * (f32) var_r28));
                Hu3DModelRotSet(var_r31_12, 0.0f, 180.0f, 0.0f);
                Hu3DModelAttrReset(var_r31_12, 1U);
            }
            if ((s16) m->modelCache[lbl_1_data_344[temp_r26][var_r27]] < 0) {
                temp_r3_12 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[lbl_1_data_344[temp_r26][var_r27]], MEMORY_DEFAULT_NUM, HEAP_DATA));
                m->modelCache[lbl_1_data_344[temp_r26][var_r27]] = temp_r3_12;
                var_r31_13 = temp_r3_12;
            } else {
                var_r31_13 = Hu3DModelLink(m->modelCache[lbl_1_data_344[temp_r26][var_r27]]);
            }
            var_r27 += 1;
            Hu3DModelAttrSet(var_r31_13, 1U);
            Hu3DModelAttrSet(var_r31_13, 0x40000002U);
            Hu3DModelLayerSet(var_r31_13, 0);
            Hu3DModelPosSet(var_r31_13, 300.0f * (f32) (var_r29 - 2), 0.0f, 2700.0f - (300.0f * (f32) var_r28));
            Hu3DModelRotSet(var_r31_13, 0.0f, 180.0f, 0.0f);
            Hu3DModelAttrReset(var_r31_13, 1U);
            m->tileA[(var_r28 - 1) * 3 + (var_r29 - 1)] = var_r31_13;
            var_r29 += 1;
            goto loop_44;
        }
        var_r28 += 1;
        goto loop_46;
    }
    var_r29_2 = 1;
loop_52:
    if (var_r29_2 < 4) {
        if ((s16) m->modelCache[0x11] < 0) {
            temp_r3_13 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x11], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->modelCache[0x11] = temp_r3_13;
            var_r31_14 = temp_r3_13;
        } else {
            var_r31_14 = Hu3DModelLink(m->modelCache[0x11]);
        }
        Hu3DModelAttrSet(var_r31_14, 1U);
        Hu3DModelAttrSet(var_r31_14, 0x40000002U);
        Hu3DModelLayerSet(var_r31_14, 0);
        Hu3DModelPosSet(var_r31_14, 300.0f * (f32) (var_r29_2 - 2), 0.0f, 0.0f);
        Hu3DModelRotSet(var_r31_14, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r31_14, 1U);
        m->unkCE4[var_r29_2 - 1] = var_r31_14;
        var_r29_2 += 1;
        goto loop_52;
    }
    var_r27_2 = 0;
    var_r28_2 = 1;
loop_66:
    if (var_r28_2 < 9) {
        var_r29_3 = 1;
loop_64:
        if (var_r29_3 < 4) {
            if ((s16) *(s16 *) ((u8 *) temp_r24 + ((var_r28_2 * 0xA) + (var_r29_3 * 2))) == -1) {
                if ((s16) m->modelCache[spC[(var_r28_2 - 1) * 3 + (var_r29_3 - 1)] + 0xD] < 0) {
                    var_r31_15 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[spC[(var_r28_2 - 1) * 3 + (var_r29_3 - 1)] + 0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
                    m->modelCache[spC[(var_r28_2 - 1) * 3 + (var_r29_3 - 1)] + 0xD] = var_r31_15;
                } else {
                    var_r31_15 = Hu3DModelLink(m->modelCache[spC[(var_r28_2 - 1) * 3 + (var_r29_3 - 1)] + 0xD]);
                }
                m->fieldMdl[var_r25] = var_r31_15;
                var_r25 += 1;
                Hu3DModelAttrSet(var_r31_15, 1U);
                Hu3DModelAttrSet(var_r31_15, 0x40000002U);
                Hu3DModelLayerSet(var_r31_15, 0);
                Hu3DModelPosSet(var_r31_15, 300.0f * (f32) -(var_r29_3 - 2), 0.0f, -2700.0f + (300.0f * (f32) var_r28_2));
                Hu3DModelRotSet(var_r31_15, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrReset(var_r31_15, 1U);
            }
            if ((s16) m->modelCache[lbl_1_data_344[temp_r26][var_r27_2]] < 0) {
                temp_r3_14 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[lbl_1_data_344[temp_r26][var_r27_2]], MEMORY_DEFAULT_NUM, HEAP_DATA));
                m->modelCache[lbl_1_data_344[temp_r26][var_r27_2]] = temp_r3_14;
                var_r31_16 = temp_r3_14;
            } else {
                var_r31_16 = Hu3DModelLink(m->modelCache[lbl_1_data_344[temp_r26][var_r27_2]]);
            }
            var_r27_2 += 1;
            Hu3DModelAttrSet(var_r31_16, 1U);
            Hu3DModelAttrSet(var_r31_16, 0x40000002U);
            Hu3DModelLayerSet(var_r31_16, 0);
            Hu3DModelPosSet(var_r31_16, 300.0f * (f32) -(var_r29_3 - 2), 0.0f, -2700.0f + (300.0f * (f32) var_r28_2));
            Hu3DModelRotSet(var_r31_16, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(var_r31_16, 1U);
            m->tileB[(var_r28_2 - 1) * 3 + (var_r29_3 - 1)] = var_r31_16;
            var_r29_3 += 1;
            goto loop_64;
        }
        var_r28_2 += 1;
        goto loop_66;
    }
}

void fn_1_5BD4(s16 (*grid)[5]) {
    u16 sp8[6];
    s16 var_r27;
    s16 var_r28;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_5;

    sp8[0] = lbl_1_rodata_192[0];
    sp8[1] = lbl_1_rodata_192[1];
    sp8[2] = lbl_1_rodata_192[2];
    var_r30 = 0;
loop_2:
    if (var_r30 < 5) {
        (*grid)[var_r30] = -1;
        *(s16 *) ((u8 *) grid + ((var_r30 * 2) + 0x64)) = -1;
        var_r30 += 1;
        goto loop_2;
    }
    var_r30_2 = 0;
loop_5:
    if (var_r30_2 < 5) {
        *(s16 *) ((u8 *) grid + ((var_r30_2 * 2) + 0xA)) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((var_r30_2 * 2) + 0x46));
        *(s16 *) ((u8 *) grid + ((var_r30_2 * 2) + 0x5A)) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((var_r30_2 * 2) + 0x50));
        var_r30_2 += 1;
        goto loop_5;
    }
    var_r28 = (s16) sp8[frandmod(3U)];
    var_r31 = 0;
loop_8:
    if (var_r31 < 5) {
        *(s16 *) ((u8 *) grid + ((var_r31 * 2) + 0x14)) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((var_r28 * 0xA) + (var_r31 * 2)));
        var_r31 += 1;
        goto loop_8;
    }
    var_r30_3 = 3;
loop_38:
    if (var_r30_3 < 9) {
        sp8[3] = 0;
        sp8[4] = 0;
        sp8[5] = 0;
        if (var_r30_3 >= 5) {
            var_r31_2 = var_r30_3 - 4;
loop_13:
            if (var_r31_2 < var_r30_3) {
                sp8[3] += (s16) grid[var_r31_2][1] == 0;
                sp8[4] += (s16) grid[var_r31_2][2] == 0;
                sp8[5] += (s16) grid[var_r31_2][3] == 0;
                var_r31_2 += 1;
                goto loop_13;
            }
        }
        var_r27 = 0;
        if (sp8[3] == 4) {
            var_r27 = 1;
        }
        if (sp8[4] == 4) {
            var_r27 += 2;
        }
        if (sp8[5] == 4) {
            var_r27 += 4;
        }
        if ((var_r27 != 0) && (var_r30_3 < 8)) {
            if (var_r28 != 0) {
                var_r31_3 = 0;
loop_25:
                if (var_r31_3 < 5) {
                    *(s16 *) ((u8 *) grid + ((var_r30_3 * 0xA) + (var_r31_3 * 2))) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((0 * 0xA) + (var_r31_3 * 2)));
                    var_r31_3 += 1;
                    goto loop_25;
                }
                var_r30_3 += 1;
            }
            var_r28 = var_r27;
            var_r31_4 = 0;
loop_29:
            if (var_r31_4 < 5) {
                *(s16 *) ((u8 *) grid + ((var_r30_3 * 0xA) + (var_r31_4 * 2))) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((var_r28 * 0xA) + (var_r31_4 * 2)));
                var_r31_4 += 1;
                goto loop_29;
            }
        } else {
            if (var_r30_3 == 8) {
                var_r28 = fn_1_5FC0((s32) var_r28);
            } else {
                var_r28 = fn_1_5F04((s32) var_r28);
            }
            var_r31_5 = 0;
loop_36:
            if (var_r31_5 < 5) {
                *(s16 *) ((u8 *) grid + ((var_r30_3 * 0xA) + (var_r31_5 * 2))) = *(s16 *) ((u8 *) lbl_1_rodata_138 + ((var_r28 * 0xA) + (var_r31_5 * 2)));
                var_r31_5 += 1;
                goto loop_36;
            }
        }
        var_r30_3 += 1;
        goto loop_38;
    }
}

s16 fn_1_5F04(s32 arg0) {
    s32 spC[3];
    s32 sp8;
    s32 var_r31;

    var_r31 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = arg0;
    spC[0] = lbl_1_rodata_198[0];
    spC[1] = lbl_1_rodata_198[1];
    spC[2] = lbl_1_rodata_198[2];
    switch (sp8) {                                  /* irregular */
    case 0:
        var_r31 = frandmod(6U) + 1;
        break;
    case 1:
        var_r31 = spC[frandmod(3U)];
        break;
    case 4:
        var_r31 = frandmod(3U);
        break;
    default:
        var_r31 = 0;
        break;
    }
    return (s16) var_r31;
}

s16 fn_1_5FC0(s32 arg0) {
    s32 sp14[2];
    s32 spC[2];
    s32 sp8;
    s32 var_r31;

    var_r31 = 0 /* TODO(mp5): uninitialised in the original */;
    sp8 = arg0;
    sp14[0] = lbl_1_rodata_1A4[0];
    sp14[1] = lbl_1_rodata_1A4[1];
    spC[0] = lbl_1_rodata_1AC[0];
    spC[1] = lbl_1_rodata_1AC[1];
    switch (sp8) {                                  /* irregular */
    case 0:
        var_r31 = frandmod(6U) + 1;
        break;
    case 1:
        var_r31 = sp14[frandmod(2U)];
        break;
    case 4:
        var_r31 = spC[frandmod(2U)];
        break;
    default:
        var_r31 = 0;
        break;
    }
    return (s16) var_r31;
}


void fn_1_60F8(M567Main *m) {
    M567Player *sp8[4];
    M567Cursor *temp_r29;
    M567Cursor *temp_r29_2;
    M567Player *temp_r30;
    M567Player *temp_r30_2;
    M567Player *temp_r30_3;
    s16 temp_r23;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 var_r27;
    s16 var_r27_2;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    s32 var_r28_4;
    s32 var_r28_5;

    m->side[0].isTeam = 0;
    m->side[1].isTeam = 1;
    m->side[0].row = 1;
    m->side[0].col = 2;
    m->side[1].row = 1;
    m->side[1].col = 2;
    var_r24 = 0;
    var_r28 = 0;
loop_5:
    if (var_r28 < 4) {
        temp_r30 = m->ply[var_r28];
        if ((s16) temp_r30->group == 0) {
            m->side[0].ply[0] = temp_r30;
        } else {
            sp8[var_r24] = temp_r30;
            var_r24 += 1;
        }
        var_r28 += 1;
        goto loop_5;
    }
    var_r28_2 = 0;
loop_8:
    if (var_r28_2 < 3) {
        temp_r23 = frandmod(3U);
        temp_r3 = frandmod(3U);
        M2C_SWAP(sp8[temp_r23], sp8[temp_r3]); /* m2c lost the temporary */
        var_r28_2 += 1;
        goto loop_8;
    }
    var_r28_3 = 0;
loop_11:
    if (var_r28_3 < 3) {
        m->side[1].ply[var_r28_3] = sp8[var_r28_3];
        var_r28_3 += 1;
        goto loop_11;
    }
    m->side[0].ply[0]->idx = 0;
    m->side[1].ply[0]->idx = 0;
    m->side[1].ply[1]->idx = 1;
    m->side[1].ply[2]->idx = 2;
    m->side[0].ply[0]->side = m->side;
    m->side[1].ply[0]->side = &m->side[1];
    m->side[1].ply[1]->side = &m->side[1];
    m->side[1].ply[2]->side = &m->side[1];
    m->side[0].cur.cam = m->cam;
    m->side[1].cur.cam = &m->cam[1];
    fn_1_5BD4((s16 (*)[5]) m->side[0].grid[0]);
    var_r25 = 0;
loop_17:
    if (var_r25 < 0xC) {
        var_r26 = 0;
loop_15:
        if (var_r26 < 5) {
            ((s16 *) m->side[1].grid)[var_r25 * 5 + var_r26] = ((s16 *) m->side[0].grid)[var_r25 * 5 + var_r26];
            var_r26 += 1;
            goto loop_15;
        }
        var_r25 += 1;
        goto loop_17;
    }
    temp_r30_2 = m->side[0].ply[0];
    temp_r30_2->pos.x = 0.0f;
    temp_r30_2->pos.y = 0.0f;
    temp_r30_2->pos.z = 0.0f;
    temp_r30_2->rot.x = 0.0f;
    temp_r30_2->rot.y = 0.0f;
    temp_r30_2->rot.z = 0.0f;
    Hu3DModelPosSetV(temp_r30_2->model, &temp_r30_2->pos);
    omSetTra(temp_r30_2->obj, temp_r30_2->pos.x, temp_r30_2->pos.y, temp_r30_2->pos.z);
    Hu3DModelRotSetV(temp_r30_2->model, &temp_r30_2->rot);
    omSetRot(temp_r30_2->obj, temp_r30_2->rot.x, temp_r30_2->rot.y, temp_r30_2->rot.z);
    var_r28_4 = 0;
loop_20:
    if (var_r28_4 < 3) {
        temp_r30_3 = m->side[1].ply[var_r28_4];
        temp_r30_3->pos.x = 0.0f;
        temp_r30_3->pos.y = 0.0f;
        temp_r30_3->pos.z = 0.0f;
        temp_r30_3->rot.x = 0.0f;
        temp_r30_3->rot.y = 0.0f;
        temp_r30_3->rot.z = 0.0f;
        Hu3DModelPosSetV(temp_r30_3->model, &temp_r30_3->pos);
        omSetTra(temp_r30_3->obj, temp_r30_3->pos.x, temp_r30_3->pos.y, temp_r30_3->pos.z);
        Hu3DModelRotSetV(temp_r30_3->model, &temp_r30_3->rot);
        omSetRot(temp_r30_3->obj, temp_r30_3->rot.x, temp_r30_3->rot.y, temp_r30_3->rot.z);
        var_r28_4 += 1;
        goto loop_20;
    }
    temp_r29 = &m->side[0].cur;
    fn_1_69B4(temp_r29, 0);
    m->side[0].cur.pos.x = 0.0f;
    m->side[0].cur.pos.y = 0.0f;
    m->side[0].cur.pos.z = 2400.0f;
    m->side[0].cur.rot.x = 0.0f;
    m->side[0].cur.rot.y = 180.0f;
    m->side[0].cur.rot.z = 0.0f;
    Hu3DModelPosSetV(m->side[0].cur.model, &temp_r29->pos);
    Hu3DModelRotSetV(m->side[0].cur.model, &temp_r29->rot);
    temp_r29_2 = &m->side[1].cur;
    fn_1_69B4(temp_r29_2, 1);
    m->side[1].cur.pos.x = 0.0f;
    m->side[1].cur.pos.y = 0.0f;
    m->side[1].cur.pos.z = -2400.0f;
    m->side[1].cur.rot.x = 0.0f;
    m->side[1].cur.rot.y = 0.0f;
    m->side[1].cur.rot.z = 0.0f;
    Hu3DModelPosSetV(m->side[1].cur.model, &temp_r29_2->pos);
    Hu3DModelRotSetV(m->side[1].cur.model, &temp_r29_2->rot);
    m->side[0].slot.reel[0].model3 = m->side[0].cur.mini[0];
    m->side[1].slot.reel[0].model3 = m->side[1].cur.mini[0];
    m->side[1].slot.reel[1].model3 = m->side[1].cur.mini[1];
    m->side[1].slot.reel[2].model3 = m->side[1].cur.mini[2];
    fn_1_7DB4(&m->side[0].slot, m->side[0].cur.cam, 0);
    fn_1_7DB4(&m->side[1].slot, m->side[1].cur.cam, 1);
    Hu3DModelHookSet(m->side[0].cur.model, "m567-play0", m->side[0].ply[0]->model);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-play3", m->side[1].ply[0]->model);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-play1", m->side[1].ply[1]->model);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-play2", m->side[1].ply[2]->model);
    Hu3DModelHookSet(m->side[0].cur.model, "m567-1pa_mini", m->side[0].cur.mini[0]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-3pa_mini", m->side[1].cur.mini[0]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-3pb_mini", m->side[1].cur.mini[1]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-3pc_mini", m->side[1].cur.mini[2]);
    Hu3DModelHookSet(m->side[0].cur.model, "m567-pum0", m->side[0].cur.pum[0]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-pum3", m->side[1].cur.pum[0]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-pum1", m->side[1].cur.pum[1]);
    Hu3DModelHookSet(m->side[1].cur.model, "m567-pum2", m->side[1].cur.pum[2]);
    m->side[0].ply[0]->reel = m->side[0].slot.reel;
    m->side[1].ply[0]->reel = m->side[1].slot.reel;
    m->side[1].ply[1]->reel = &m->side[1].slot.reel[1];
    m->side[1].ply[2]->reel = &m->side[1].slot.reel[2];
    m->side[0].ply[0]->pumMdl = m->side[0].cur.pum[0];
    m->side[1].ply[0]->pumMdl = m->side[1].cur.pum[0];
    m->side[1].ply[1]->pumMdl = m->side[1].cur.pum[1];
    m->side[1].ply[2]->pumMdl = m->side[1].cur.pum[2];
    m->side[0].state = 0;
    m->side[1].state = 0;
    m->side[0].limit = 0x14;
    m->side[1].limit = 0x1E;
    if ((s16) m->modelCache[Mp5CharNo(m->side[0].ply[0]->charNo) + 0x1E] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[Mp5CharNo(m->side[0].ply[0]->charNo) + 0x1E], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->modelCache[Mp5CharNo(m->side[0].ply[0]->charNo) + 0x1E] = temp_r3_2;
        var_r27 = temp_r3_2;
    } else {
        var_r27 = Hu3DModelLink(m->modelCache[Mp5CharNo(m->side[0].ply[0]->charNo) + 0x1E]);
    }
    m->side[0].slot.bandMdl[0] = var_r27;
    Hu3DModelAttrSet(var_r27, 1U);
    Hu3DModelAttrSet(var_r27, 0x40000002U);
    Hu3DModelLayerSet(var_r27, 6);
    Hu3DModelPosSet(var_r27, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r27, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r27, 1U);
    var_r28_5 = 0;
loop_29:
    if (var_r28_5 < 3) {
        if ((s16) m->modelCache[Mp5CharNo(m->side[1].ply[var_r28_5]->charNo) + 0x2B] < 0) {
            temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[Mp5CharNo(m->side[1].ply[var_r28_5]->charNo) + 0x2B], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->modelCache[Mp5CharNo(m->side[1].ply[var_r28_5]->charNo) + 0x2B] = temp_r3_3;
            var_r27_2 = temp_r3_3;
        } else {
            var_r27_2 = Hu3DModelLink(m->modelCache[Mp5CharNo(m->side[1].ply[var_r28_5]->charNo) + 0x2B]);
        }
        m->side[1].slot.bandMdl[var_r28_5] = var_r27_2;
        Hu3DModelAttrSet(var_r27_2, 1U);
        Hu3DModelAttrSet(var_r27_2, 0x40000002U);
        Hu3DModelLayerSet(var_r27_2, 6);
        Hu3DModelPosSet(var_r27_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r27_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r27_2, 1U);
        var_r28_5 += 1;
        goto loop_29;
    }
}

void fn_1_69B4(M567Cursor *cur, s32 team) {
    s16 temp_r3;
    s16 temp_r3_10;
    s16 temp_r3_11;
    s16 temp_r3_12;
    s16 temp_r3_13;
    s16 temp_r3_14;
    s16 temp_r3_15;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r3_9;
    s16 var_r29;
    s16 var_r29_2;
    s16 var_r29_3;
    s16 var_r29_4;
    s16 var_r29_5;
    s16 var_r29_6;
    s16 var_r29_7;
    s16 var_r29_8;
    s16 var_r29_9;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s16 var_r30_4;
    s32 var_r26;
    s32 var_r27;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    if (team == 0) {
        if ((s16) temp_r31->modelCache[18] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x12], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->modelCache[18] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(temp_r31->modelCache[18]);
        }
        if ((s16) temp_r31->motionCache[1] < 0) {
            temp_r3_2 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[1] = temp_r3_2;
            var_r29 = temp_r3_2;
        } else {
            var_r29 = temp_r31->motionCache[1];
        }
        cur->mot32 = var_r29;
        Hu3DMotionSet(var_r30, var_r29);
        if ((s16) temp_r31->motionCache[2] < 0) {
            temp_r3_3 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[2] = temp_r3_3;
            var_r29_2 = temp_r3_3;
        } else {
            var_r29_2 = temp_r31->motionCache[2];
        }
        cur->mot34 = var_r29_2;
        if ((s16) temp_r31->motionCache[3] < 0) {
            temp_r3_4 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[3], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[3] = temp_r3_4;
            var_r29_3 = temp_r3_4;
        } else {
            var_r29_3 = temp_r31->motionCache[3];
        }
        cur->mot36 = var_r29_3;
        if ((s16) temp_r31->motionCache[4] < 0) {
            temp_r3_5 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[4], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[4] = temp_r3_5;
            var_r29_4 = temp_r3_5;
        } else {
            var_r29_4 = temp_r31->motionCache[4];
        }
        cur->mot38 = var_r29_4;
    } else {
        if ((s16) temp_r31->modelCache[19] < 0) {
            temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x13], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->modelCache[19] = temp_r3_6;
            var_r30 = temp_r3_6;
        } else {
            var_r30 = Hu3DModelLink(temp_r31->modelCache[19]);
        }
        if ((s16) temp_r31->motionCache[5] < 0) {
            temp_r3_7 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[5], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[5] = temp_r3_7;
            var_r29_5 = temp_r3_7;
        } else {
            var_r29_5 = temp_r31->motionCache[5];
        }
        cur->mot32 = var_r29_5;
        Hu3DMotionSet(var_r30, var_r29_5);
        if ((s16) temp_r31->motionCache[6] < 0) {
            temp_r3_8 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[6], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[6] = temp_r3_8;
            var_r29_6 = temp_r3_8;
        } else {
            var_r29_6 = temp_r31->motionCache[6];
        }
        cur->mot34 = var_r29_6;
        if ((s16) temp_r31->motionCache[7] < 0) {
            temp_r3_9 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[7], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[7] = temp_r3_9;
            var_r29_7 = temp_r3_9;
        } else {
            var_r29_7 = temp_r31->motionCache[7];
        }
        cur->mot36 = var_r29_7;
        if ((s16) temp_r31->motionCache[8] < 0) {
            temp_r3_10 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum((s32) lbl_1_data_230[8], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[8] = temp_r3_10;
            var_r29_8 = temp_r3_10;
        } else {
            var_r29_8 = temp_r31->motionCache[8];
        }
        cur->mot38 = var_r29_8;
    }
    cur->model = var_r30;
    Hu3DModelAttrSet(var_r30, 1U);
    Hu3DModelAttrSet(var_r30, 0x40000001U);
    Hu3DModelLayerSet(var_r30, 2);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30, 1U);
    if (team != 0) {
        var_r26 = 3;
    } else {
        var_r26 = 1;
    }
    var_r27 = 0;
loop_51:
    if (var_r27 < var_r26) {
        if ((s16) temp_r31->modelCache[56] < 0) {
            temp_r3_11 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x38], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->modelCache[56] = temp_r3_11;
            var_r30_2 = temp_r3_11;
        } else {
            var_r30_2 = Hu3DModelLink(temp_r31->modelCache[56]);
        }
        cur->mini[var_r27] = var_r30_2;
        Hu3DModelAttrSet(var_r30_2, 1U);
        Hu3DModelAttrSet(var_r30_2, 0x40000002U);
        Hu3DModelLayerSet(var_r30_2, 2);
        Hu3DModelPosSet(var_r30_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r30_2, 1U);
        if (team != 0) {
            if ((s16) temp_r31->modelCache[62] < 0) {
                temp_r3_12 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x3E], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r31->modelCache[62] = temp_r3_12;
                var_r30_3 = temp_r3_12;
            } else {
                var_r30_3 = Hu3DModelLink(temp_r31->modelCache[62]);
            }
        } else if ((s16) temp_r31->modelCache[61] < 0) {
            temp_r3_13 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x3D], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->modelCache[61] = temp_r3_13;
            var_r30_3 = temp_r3_13;
        } else {
            var_r30_3 = Hu3DModelLink(temp_r31->modelCache[61]);
        }
        cur->pum[var_r27] = var_r30_3;
        if ((s16) temp_r31->motionCache[0] < 0) {
            temp_r3_14 = Hu3DJointMotion(var_r30_3, HuDataSelHeapReadNum((s32) lbl_1_data_230[0], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r31->motionCache[0] = temp_r3_14;
            var_r29_9 = temp_r3_14;
        } else {
            var_r29_9 = temp_r31->motionCache[0];
        }
        Hu3DMotionSet(var_r30_3, var_r29_9);
        Hu3DModelAttrSet(var_r30_3, 1U);
        Hu3DModelAttrSet(var_r30_3, 0x40000002U);
        Hu3DModelLayerSet(var_r30_3, 2);
        Hu3DModelPosSet(var_r30_3, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30_3, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(var_r30_3, 1U);
        var_r27 += 1;
        goto loop_51;
    }
    if ((s16) temp_r31->modelCache[28] < 0) {
        temp_r3_15 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x1C], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r31->modelCache[28] = temp_r3_15;
        var_r30_4 = temp_r3_15;
    } else {
        var_r30_4 = Hu3DModelLink(temp_r31->modelCache[28]);
    }
    cur->fx = var_r30_4;
    Hu3DModelAttrSet(var_r30_4, 1U);
    Hu3DModelAttrSet(var_r30_4, 0x40000002U);
    Hu3DModelLayerSet(var_r30_4, 4);
    Hu3DModelPosSet(var_r30_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r30_4, 0.0f, 0.0f, 0.0f);
}

s32 fn_1_7084(M567Side *side) {
    u16 sp8[3];
    M567Node *temp_r26;
    M567Node *temp_r27;
    M567Node *temp_r28;
    f32 var_f31;
    s16 temp_r0;
    s16 temp_r29;
    s32 var_r20;
    s32 var_r21;
    s32 var_r22;
    s32 var_r23;
    s32 var_r24;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    M567Main *temp_r30;

    var_r24 = 0;
    sp8[0] = lbl_1_rodata_1B4[0];
    sp8[1] = lbl_1_rodata_1B4[1];
    sp8[2] = lbl_1_rodata_1B4[2];
    temp_r30 = lbl_1_bss_4->data;
    if ((s16) temp_r30->unkCF6 != 0) {
        if ((s16) side->isTeam != 0) {
            side->cur.cam->target.x = 0.5f * side->cur.pos.x;
            side->cur.cam->target.z = 250.0f + side->cur.pos.z;
        } else {
            side->cur.cam->target.x = 0.5f * side->cur.pos.x;
            side->cur.cam->target.z = side->cur.pos.z - 250.0f;
        }
    }
    temp_r0 = side->state;
    if ((u32) temp_r0 <= 0xAU) {
        switch (temp_r0) {
        case 1:
            side->timer = 0;
            if ((s16) side->isTeam != 0) {
                var_r23 = 3;
            } else {
                var_r23 = 1;
            }
            var_r29 = 0;
loop_11:
            if (var_r29 < var_r23) {
                side->ply[var_r29]->reel->state = 0xA;
                side->ply[var_r29]->aiState = 0;
                var_r29 += 1;
                goto loop_11;
            }
            if ((s16) temp_r30->unkCF4 != 0) {
                if ((s16) side->isTeam == 0) {
                    if ((s32) lbl_1_data_434[0] < 0) {
                        lbl_1_data_434[0] = HuAudFXPlayPan(0x8F1, 0x30);
                    }
                } else if ((s32) lbl_1_data_434[1] < 0) {
                    lbl_1_data_434[1] = HuAudFXPlayPan(0x8F2, 0x50);
                }
            }
            side->slot.unkD4 = 2;
            fn_1_959C((s16 (*)[5]) side->grid[0], side->row, side->col);
            side->state += 1;
            /* fallthrough */
        case 2:
            if ((s16) side->isTeam != 0) {
                var_r22 = 3;
            } else {
                var_r22 = 1;
            }
            var_r29_2 = 0;
loop_25:
            if (var_r29_2 < var_r22) {
                if ((s16) side->ply[var_r29_2]->reel->state == 0x3C) {
                    var_r29_2 += 1;
                    goto loop_25;
                }
            }
            if (var_r29_2 == var_r22) {
                if ((s16) side->isTeam == 0) {
                    if ((s32) lbl_1_data_434[0] >= 0) {
                        HuAudFXStop(lbl_1_data_434[0]);
                        lbl_1_data_434[0] = -1;
                    }
                } else if ((s32) lbl_1_data_434[1] >= 0) {
                    HuAudFXStop(lbl_1_data_434[1]);
                    lbl_1_data_434[1] = -1;
                }
                side->state += 1;
                side->slot.unkD0 = 0;
            }
            break;
        case 3:
            side->nrow = side->row + side->ply[side->slot.unkD0]->reel->unkC;
            side->ncol = side->col + side->ply[side->slot.unkD0]->reel->unkA;
            if (((s16) side->grid[side->nrow][side->ncol] != 0) && ((s16) side->grid[side->nrow][side->ncol] != 2)) {
                side->nrow = side->row;
                side->ncol = side->col;
                if ((s16) side->isTeam == 0) {
                    omVibrate(side->ply[0]->player, 0x19, 4, 2);
                } else {
                    omVibrate(side->ply[0]->player, 0x19, 4, 2);
                    omVibrate(side->ply[1]->player, 0x19, 4, 2);
                    omVibrate(side->ply[2]->player, 0x19, 4, 2);
                }
                temp_r29 = side->slot.unkD0;
                Hu3DModelAttrReset(side->slot.unkC4[temp_r29], 1U);
                Hu3DModelPosSetV(side->slot.unkC4[temp_r29], &side->slot.pos[temp_r29]);
                Hu3DModelRotSetV(side->slot.unkC4[temp_r29], &side->slot.rot);
                if ((s16) side->isTeam == 0) {
                    HuAudFXPlayPan(0x8F9, 0x30);
                } else {
                    HuAudFXPlayPan(0x8FA, 0x50);
                }
            }
            if ((s16) side->isTeam == 0) {
                side->cur.from.x = (300.0f * (f32) side->col) - 600.0f;
                side->cur.from.z = 2700.0f + (300.0f * (f32) -side->row);
                side->cur.to.x = (300.0f * (f32) side->ncol) - 600.0f;
                side->cur.to.z = 2700.0f + (300.0f * (f32) -side->nrow);
                HuAudFXPlayPan(0x8F5, (s16) sp8[side->ncol - 1]);
            } else {
                side->cur.from.x = 600.0f + (300.0f * (f32) -side->col);
                side->cur.from.z = (300.0f * (f32) side->row) - 2700.0f;
                side->cur.to.x = (f32) (600.0 + (300.0 * (f64) -side->ncol));
                side->cur.to.z = (300.0f * (f32) side->nrow) - 2700.0f;
                HuAudFXPlayPan(0x8F7, (s16) sp8[side->ncol - 1]);
            }
            if ((s16) side->nrow == 9) {
                var_r24 = 1;
            }
            side->state += 1;
            side->timer = 0;
            Hu3DMotionShiftSet(side->cur.model, side->cur.mot34, 0.0f, 5.0f, 0U);
            temp_r28 = fn_1_4704(&temp_r30->pool, fn_1_979C, &side->cur);
            break;
        case 4:
            side->timer += 1;
            if ((s16) side->timer == (s16) side->limit) {
                side->row = side->nrow;
                side->col = side->ncol;
                if ((s16) temp_r30->unkCF4 != 0) {
                    side->state += 1;
                } else {
                    side->state = 7;
                }
                Hu3DModelAttrSet(side->slot.unkC4[side->slot.unkD0], 1U);
            }
            if ((s16) side->isTeam != 0) {
                if ((s16) side->timer < 0x11) {
                    var_f31 = 0.0f;
                } else if ((s16) side->timer < 0x1C) {
                    var_f31 = ((f32) side->timer - 16.0f) / 11.0f;
                } else {
                    var_f31 = 1.0f;
                }
                if ((s16) side->timer == 0x1C) {
                    temp_r27 = fn_1_4704(&temp_r30->pool, fn_1_988C, &side->cur);
                    Hu3DModelAttrReset(side->cur.fx, 1U);
                    Hu3DModelAttrReset(side->cur.fx, 0x40000002U);
                    Hu3DMotionTimeSet(side->cur.fx, 0.0f);
                    Hu3DModelPosSetV(side->cur.fx, &side->cur.pos);
                    HuAudFXPlayPan(0x8F8, (s16) sp8[side->ncol - 1]);
                }
                if (((s16) side->nrow == 9) && ((s16) side->timer == 0x16)) {
                    Hu3DModelAttrReset(temp_r30->modelCache[25], 0x40000002U);
                    Hu3DModelAttrReset(temp_r30->modelCache[26], 0x40000002U);
                }
            } else {
                if ((s16) side->timer < 0xB) {
                    var_f31 = 0.0f;
                } else if ((s16) side->timer < 0x13) {
                    var_f31 = ((f32) side->timer - 10.0f) * 0.125f;
                } else {
                    var_f31 = 1.0f;
                }
                if ((s16) side->timer == 0x13) {
                    temp_r26 = fn_1_4704(&temp_r30->pool, fn_1_988C, &side->cur);
                    Hu3DModelAttrReset(side->cur.fx, 1U);
                    Hu3DModelAttrReset(side->cur.fx, 0x40000002U);
                    Hu3DMotionTimeSet(side->cur.fx, 0.0f);
                    Hu3DModelPosSetV(side->cur.fx, &side->cur.pos);
                    HuAudFXPlayPan(0x8F6, (s16) sp8[side->ncol - 1]);
                }
                if (((s16) side->nrow == 9) && ((s16) side->timer == 0xF)) {
                    Hu3DModelAttrReset(temp_r30->modelCache[25], 0x40000002U);
                    Hu3DModelAttrReset(temp_r30->modelCache[26], 0x40000002U);
                }
            }
            side->cur.pos.x = (side->cur.from.x * (1.0f - var_f31)) + (side->cur.to.x * var_f31);
            side->cur.pos.z = (side->cur.from.z * (1.0f - var_f31)) + (side->cur.to.z * var_f31);
            Hu3DModelPosSetV(side->cur.model, &side->cur.pos);
            break;
        case 5:
            side->ply[side->slot.unkD0]->reel->state = 0x46;
            side->state += 1;
            /* fallthrough */
        case 6:
            if ((s16) side->ply[side->slot.unkD0]->reel->state == 1) {
                side->slot.unkD0 += 1;
                if ((s16) side->isTeam != 0) {
                    var_r21 = 3;
                } else {
                    var_r21 = 1;
                }
                if ((s16) side->slot.unkD0 == var_r21) {
                    side->state = 1;
                } else {
                    side->state = 9;
                }
            }
            break;
        case 7:
            if ((s16) side->isTeam != 0) {
                var_r20 = 3;
            } else {
                var_r20 = 1;
            }
            var_r29_3 = 0;
loop_98:
            if (var_r29_3 < var_r20) {
                side->ply[var_r29_3]->reel->state = 0x46;
                var_r29_3 += 1;
                goto loop_98;
            }
            Hu3DMotionShiftSet(side->cur.model, side->cur.mot32, 0.0f, 5.0f, 0x40000001U);
            if ((s16) side->isTeam == 0) {
                if ((s32) lbl_1_data_434[0] >= 0) {
                    HuAudFXStop(lbl_1_data_434[0]);
                    lbl_1_data_434[0] = -1;
                }
            } else if ((s32) lbl_1_data_434[1] >= 0) {
                HuAudFXStop(lbl_1_data_434[1]);
                lbl_1_data_434[1] = -1;
            }
            side->state += 1;
            break;
        case 9:
            side->timer = 0;
            side->state += 1;
            /* fallthrough */
        case 10:
            side->timer += 1;
            if ((s16) side->timer == 0x1E) {
                side->state = 3;
            }
            break;
        }
    }
    return var_r24;
}

void fn_1_7DB4(M567Slot *slot, M567Cam *cam, s16 type) {
    M567Cam *sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 var_r30;
    s16 var_r30_2;
    s16 var_r30_3;
    s32 var_r26;
    s32 var_r28;
    M567Main *temp_r29;

    sp8 = cam;
    temp_r29 = lbl_1_bss_4->data;
    slot->cam = sp8;
    slot->type = type;
    if (type == 0) {
        if ((s16) temp_r29->modelCache[20] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x14], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r29->modelCache[20] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(temp_r29->modelCache[20]);
        }
    } else if ((s16) temp_r29->modelCache[21] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r29->modelCache[21] = temp_r3_2;
        var_r30 = temp_r3_2;
    } else {
        var_r30 = Hu3DModelLink(temp_r29->modelCache[21]);
    }
    slot->model = var_r30;
    Hu3DModelAttrSet(var_r30, 1U);
    Hu3DModelAttrSet(var_r30, 0x40000002U);
    Hu3DModelLayerSet(var_r30, 6);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(var_r30, (u16) slot->cam->camBit);
    Hu3DModelAttrReset(var_r30, 1U);
    if (type == 0) {
        slot->blink[0].mat = Hu3DData[var_r30].hsf->material + 3;
        slot->blink[1].mat = Hu3DData[var_r30].hsf->material + 4;
    } else {
        slot->blink[0].mat = Hu3DData[var_r30].hsf->material + 6;
        slot->blink[1].mat = Hu3DData[var_r30].hsf->material + 5;
        slot->blink[2].mat = Hu3DData[var_r30].hsf->material + 7;
    }
    if (type == 0) {
        var_r26 = 1;
    } else {
        var_r26 = 3;
    }
    var_r28 = 0;
loop_25:
    if (var_r28 < var_r26) {
        if ((s16) temp_r29->modelCache[24] < 0) {
            temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x18], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r29->modelCache[24] = temp_r3_3;
            var_r30_2 = temp_r3_3;
        } else {
            var_r30_2 = Hu3DModelLink(temp_r29->modelCache[24]);
        }
        slot->unkC4[var_r28] = var_r30_2;
        Hu3DModelAttrSet(var_r30_2, 1U);
        Hu3DModelAttrSet(var_r30_2, 0x40000001U);
        Hu3DModelLayerSet(var_r30_2, 6);
        Hu3DModelPosSet(var_r30_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30_2, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(var_r30_2, (u16) slot->cam->camBit);
        if (type == 0) {
            if ((s16) temp_r29->modelCache[57] < 0) {
                temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x39], MEMORY_DEFAULT_NUM, HEAP_DATA));
                temp_r29->modelCache[57] = temp_r3_4;
                var_r30_3 = temp_r3_4;
            } else {
                var_r30_3 = Hu3DModelLink(temp_r29->modelCache[57]);
            }
        } else if ((s16) temp_r29->modelCache[var_r28 + 0x3A] < 0) {
            temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[var_r28 + 0x3A], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r29->modelCache[var_r28 + 0x3A] = temp_r3_5;
            var_r30_3 = temp_r3_5;
        } else {
            var_r30_3 = Hu3DModelLink(temp_r29->modelCache[var_r28 + 0x3A]);
        }
        slot->unkCA[var_r28] = var_r30_3;
        Hu3DModelAttrSet(var_r30_3, 1U);
        Hu3DModelAttrSet(var_r30_3, 0x40000002U);
        Hu3DModelLayerSet(var_r30_3, 6);
        Hu3DModelPosSet(var_r30_3, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30_3, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(var_r30_3, (u16) slot->cam->camBit);
        Hu3DModelAttrReset(var_r30_3, 1U);
        fn_1_8794(&slot->reel[var_r28], (s32) type);
        var_r28 += 1;
        goto loop_25;
    }
    if (type == 0) {
        Hu3DModelHookSet(slot->model, "slot04-1pa", slot->reel[0].model);
    } else {
        Hu3DModelHookSet(slot->model, "m567-3pa", slot->reel[0].model);
        Hu3DModelHookSet(slot->model, "m567-3pb", slot->reel[1].model);
        Hu3DModelHookSet(slot->model, lbl_1_data_55D, slot->reel[2].model);
    }
    slot->pos2d.x = 288.0f;
    slot->pos2d.y = 500.0f;
    slot->pos2d.z = 494.0f;
    slot->unkD4 = 0;
    slot->flag = 0;
}

void fn_1_8330(M567Slot *slot) {
    Vec sp8;
    M567Node *temp_r25;
    M567Node *temp_r26;
    M567Node *temp_r27;
    M567Node *temp_r28;
    M567Node *temp_r29;
    M567Cam *temp_r23;
    s16 temp_r0;
    s16 temp_r0_2;
    s32 var_r21;
    s32 var_r24;
    s32 var_r24_2;
    M567Main *temp_r30;

    temp_r30 = lbl_1_bss_4->data;
    temp_r23 = slot->cam;
    Hu3D2Dto3D(&slot->pos2d, temp_r23->camBit, &sp8);
    slot->rot.x = -temp_r23->el;
    slot->rot.y = 90.0f - temp_r23->az;
    slot->rot.z = 0.0f;
    Hu3DModelPosSetV(slot->model, &sp8);
    Hu3DModelRotSetV(slot->model, &slot->rot);
    if ((s16) slot->type != 0) {
        Hu3DModelObjPosGet(slot->model, "m567-3pa", slot->pos);
        Hu3DModelObjPosGet(slot->model, "m567-3pb", &slot->pos[1]);
        Hu3DModelObjPosGet(slot->model, lbl_1_data_55D, &slot->pos[2]);
    } else {
        Hu3DModelObjPosGet(slot->model, "slot04-1pa", slot->pos);
    }
    if ((s16) slot->type != 0) {
        var_r21 = 3;
    } else {
        var_r21 = 1;
    }
    var_r24 = 0;
loop_8:
    if (var_r24 < var_r21) {
        fn_1_89F4(&slot->reel[var_r24]);
        var_r24 += 1;
        goto loop_8;
    }
    if ((s16) slot->flag == 0) {
        var_r24_2 = 0;
loop_12:
        if (var_r24_2 < var_r21) {
            Hu3DModelPosSetV(slot->bandMdl[var_r24_2], &slot->pos[var_r24_2]);
            Hu3DModelRotSetV(slot->bandMdl[var_r24_2], &slot->rot);
            Hu3DModelPosSetV(slot->unkCA[var_r24_2], &slot->pos[var_r24_2]);
            Hu3DModelRotSetV(slot->unkCA[var_r24_2], &slot->rot);
            var_r24_2 += 1;
            goto loop_12;
        }
    }
    if ((s16) slot->type == 0) {
        temp_r0 = slot->unkD4;
        switch (temp_r0) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            slot->unkD2 = 0;
            slot->unkD4 += 1;
            return;
        case 2:                                     /* switch 1 */
            temp_r29 = fn_1_4704(&temp_r30->pool, fn_1_98F0, slot->blink);
            slot->blink[0].state = 0;
            slot->unkD4 += 1;
            /* fallthrough */
        case 3:                                     /* switch 1 */
            slot->unkD2 += 1;
            if ((s16) slot->unkD2 == 0xF) {
                temp_r28 = fn_1_4704(&temp_r30->pool, fn_1_98F0, &slot->blink[1]);
                slot->blink[1].state = 0;
                slot->unkD4 = 0;
                return;
            }
            break;
        }
    } else {
        temp_r0_2 = slot->unkD4;
        switch (temp_r0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            slot->unkD2 = 0;
            slot->unkD4 += 1;
            return;
        case 2:                                     /* switch 2 */
            temp_r27 = fn_1_4704(&temp_r30->pool, fn_1_98F0, slot->blink);
            slot->blink[0].state = 0;
            slot->unkD4 += 1;
            /* fallthrough */
        case 3:                                     /* switch 2 */
            slot->unkD2 += 1;
            if ((s16) slot->unkD2 == 5) {
                temp_r26 = fn_1_4704(&temp_r30->pool, fn_1_98F0, &slot->blink[1]);
                slot->blink[1].state = 0;
                slot->unkD4 += 1;
                return;
            }
            return;
        case 4:                                     /* switch 2 */
            slot->unkD2 += 1;
            if ((s16) slot->unkD2 == 0xA) {
                temp_r25 = fn_1_4704(&temp_r30->pool, fn_1_98F0, &slot->blink[2]);
                slot->blink[2].state = 0;
                slot->unkD4 = 0;
            }
            break;
        }
    }
}

void fn_1_8794(M567Reel *reel, s32 type) {
    s32 sp8;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r30;
    s16 var_r30_2;
    M567Main *temp_r29;

    sp8 = type;
    temp_r29 = lbl_1_bss_4->data;
    if ((s16) temp_r29->modelCache[22] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r29->modelCache[22] = temp_r3;
        var_r30 = temp_r3;
    } else {
        var_r30 = Hu3DModelLink(temp_r29->modelCache[22]);
    }
    reel->model = var_r30;
    Hu3DModelAttrSet(var_r30, 1U);
    Hu3DModelAttrSet(var_r30, 0x40000001U);
    Hu3DModelAttrSet(var_r30, 0x40000002U);
    Hu3DModelLayerSet(var_r30, 6);
    Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r30, 1U);
    if ((s16) temp_r29->modelCache[27] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum((s32) lbl_1_data_12C[0x1B], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r29->modelCache[27] = temp_r3_2;
        var_r30_2 = temp_r3_2;
    } else {
        var_r30_2 = Hu3DModelLink(temp_r29->modelCache[27]);
    }
    reel->model2 = var_r30_2;
    Hu3DModelAttrSet(var_r30_2, 1U);
    Hu3DModelLayerSet(var_r30_2, 6);
    Hu3DModelPosSet(var_r30_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r30_2, 0.0f, 0.0f, 0.0f);
    reel->state = 0;
    reel->timer = 0;
    reel->mat = Hu3DData[reel->model].hsf->material;
    reel->mat->color[0] = 0x7F;
    reel->mat->color[1] = 0x7F;
    reel->mat->color[2] = 0x7F;
    reel->run = 0;
    reel->pos = 0;
    reel->period = 0x3C;
    reel->unit = 0x14;
    reel->idx = (s16) sp8;
}

void fn_1_89F4(M567Reel *reel) {
    s32 spC[2];
    u16 sp8[2];
    s16 temp_r0;
    s32 temp_r30;

    spC[0] = lbl_1_rodata_1F0[0];
    spC[1] = lbl_1_rodata_1F0[1];
    temp_r0 = reel->state;
    if ((u32) temp_r0 <= 0x51U) {
        switch (temp_r0) {
        case 0x0:
            reel->run = 0;
            reel->state += 1;
            break;
        case 0xA:
            reel->mat->color[0] = 0x7F;
            reel->mat->color[1] = 0x7F;
            reel->mat->color[2] = 0x7F;
            reel->timer = 0;
            reel->state += 1;
            /* fallthrough */
        case 0xB:
            reel->timer += 1;
            if ((s16) reel->timer == 5) {
                reel->state += 1;
            }
            break;
        case 0xC:
            reel->run = 1;
            reel->timer = 0;
            reel->state += 1;
            /* fallthrough */
        case 0xD:
            reel->timer += 1;
            if ((s16) reel->timer == 0x19) {
                reel->state += 1;
            }
            break;
        case 0xE:
            reel->mat->color[0] = 0xFF;
            reel->mat->color[1] = 0xFF;
            reel->mat->color[2] = 0xFF;
            reel->state += 1;
            break;
        case 0x14:
            if ((s16) reel->pos < (s16) reel->unit) {
                reel->target = reel->unit;
                reel->state = 0x1E;
                reel->unkA = 1;
                reel->unkC = 0;
            } else if ((s16) reel->pos < (s32) (reel->unit * 2)) {
                reel->target = reel->unit * 2;
                reel->state = 0x28;
                reel->unkA = -1;
                reel->unkC = 0;
            } else {
                reel->target = reel->unit * 2;
                reel->state = 0x32;
                reel->unkA = 0;
                reel->unkC = 1;
            }
            break;
        case 0x1E:
        case 0x28:
            if ((s16) reel->pos >= (s16) reel->target) {
                reel->pos = reel->target;
                reel->run = 0;
                reel->state = 0x3C;
                HuAudFXPlayPan(spC[reel->idx], (s16) sp8[reel->idx]);
            }
            break;
        case 0x32:
            if ((s16) reel->pos < (s16) reel->target) {
                reel->pos = 0;
                reel->run = 0;
                reel->state = 0x3C;
                HuAudFXPlayPan(spC[reel->idx], (s16) sp8[reel->idx]);
            }
            break;
        case 0x46:
            reel->timer = 0;
            reel->state += 1;
            /* fallthrough */
        case 0x47:
            reel->timer += 1;
            if ((s16) reel->timer == 5) {
                reel->state = 0;
            }
            temp_r30 = (s32) (128.0f * (1.0f - ((f32) reel->timer / 5.0f)));
            reel->mat->color[0] = temp_r30 + 0x7F;
            reel->mat->color[1] = temp_r30 + 0x7F;
            reel->mat->color[2] = temp_r30 + 0x7F;
            break;
        case 0x50:
            reel->mat->color[0] = 0x7F;
            reel->mat->color[1] = 0x7F;
            reel->mat->color[2] = 0x7F;
            reel->state += 1;
            break;
        }
    }
    fn_1_8DE0(reel);
    Hu3DMotionTimeSet(reel->model3, Hu3DMotionTimeGet(reel->model));
}

void fn_1_8DE0(M567Reel *reel) {
    s16 temp_r0;

    temp_r0 = reel->run;
    if (temp_r0 != 1) {
        if (temp_r0 < 1) {

        }
    } else {
        reel->pos += 1;
        reel->pos %= reel->period;
    }
    Hu3DMotionTimeSet(reel->model, (60.0f * (f32) reel->pos) / (f32) reel->period);
}

void fn_1_8EC8(M567Player *p) {
    if ((s32) (HuPadBtnDown[p->pad] & 0x100) != 0) {
        fn_1_92B0(p);
    }
}

void fn_1_8F1C(M567Player *p) {
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
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
    s16 temp_r0_2;
    s32 temp_r30;

    sp28 = lbl_1_rodata_204[0][0];
    sp2C = lbl_1_rodata_204[0][1];
    sp30 = lbl_1_rodata_204[0][2];
    sp34 = lbl_1_rodata_204[0][3];
    sp38 = lbl_1_rodata_204[1][0];
    sp3C = lbl_1_rodata_204[1][1];
    sp40 = lbl_1_rodata_204[1][2];
    sp44 = lbl_1_rodata_204[1][3];
    sp8 = lbl_1_rodata_224[0][0];
    spC = lbl_1_rodata_224[0][1];
    sp10 = lbl_1_rodata_224[0][2];
    sp14 = lbl_1_rodata_224[0][3];
    sp18 = lbl_1_rodata_224[1][0];
    sp1C = lbl_1_rodata_224[1][1];
    sp20 = lbl_1_rodata_224[1][2];
    sp24 = lbl_1_rodata_224[1][3];
    sp48 = lbl_1_rodata_244[0][0];
    sp4C = lbl_1_rodata_244[0][1];
    sp50 = lbl_1_rodata_244[0][2];
    sp54 = lbl_1_rodata_244[0][3];
    sp58 = lbl_1_rodata_244[1][0];
    sp5C = lbl_1_rodata_244[1][1];
    sp60 = lbl_1_rodata_244[1][2];
    sp64 = lbl_1_rodata_244[1][3];
    sp68 = lbl_1_rodata_244[2][0];
    sp6C = lbl_1_rodata_244[2][1];
    sp70 = lbl_1_rodata_244[2][2];
    sp74 = lbl_1_rodata_244[2][3];
    sp78 = lbl_1_rodata_244[3][0];
    sp7C = lbl_1_rodata_244[3][1];
    sp80 = lbl_1_rodata_244[3][2];
    sp84 = lbl_1_rodata_244[3][3];
    temp_r0 = p->aiState;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        p->aiWait = lbl_1_rodata_224[p->group][p->dif] + frandmod(lbl_1_rodata_204[p->group][p->dif]);
        p->aiTimer = 0;
        p->aiState += 1;
        /* fallthrough */
    case 1:                                         /* switch 1 */
        p->aiTimer += 1;
        if ((s16) p->aiTimer == (s16) p->aiWait) {
            p->aiState += 1;
            return;
        }
        return;
    case 2:                                         /* switch 1 */
        temp_r30 = p->group + p->idx;
        if (frandmod(0x64U) < (s32) lbl_1_rodata_244[temp_r30][p->dif]) {
            p->aiChoice = p->side->plan[p->idx];
        } else {
            p->aiChoice = (p->side->plan[p->idx] + (frandmod(2U) + 1)) % 3;
        }
        p->aiState += 1;
        return;
    case 3:                                         /* switch 1 */
        temp_r0_2 = p->aiChoice;
        switch (temp_r0_2) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if ((s16) p->reel->pos > (s32) (p->reel->unit * 2)) {
                fn_1_92B0(p);
                p->aiState += 1;
                return;
            }
            break;
        case 1:                                     /* switch 2 */
            if (((s16) p->reel->pos <= (s16) p->reel->unit) && ((s16) p->reel->pos > 0)) {
                fn_1_92B0(p);
                p->aiState += 1;
                return;
            }
            break;
        case 2:                                     /* switch 2 */
            if (((s16) p->reel->pos <= (s32) (p->reel->unit * 2)) && ((s16) p->reel->pos > (s16) p->reel->unit)) {
                fn_1_92B0(p);
                p->aiState += 1;
            }
            break;
        }
        break;
    }
}

void fn_1_92B0(M567Player *p) {
    M567Node *temp_r29;
    M567Node *temp_r30;
    M567Reel *temp_r28;
    M567Side *temp_r3;
    M567Slot *temp_r27;
    s16 temp_r25;
    M567Main *temp_r31;

    temp_r31 = lbl_1_bss_4->data;
    temp_r28 = p->reel;
    temp_r3 = p->side;
    temp_r27 = &temp_r3->slot;
    temp_r25 = p->idx;
    temp_r30 = fn_1_4704(&temp_r31->pool, fn_1_9828, temp_r28);
    if (temp_r30 != NULL) {
        Hu3DModelPosSet(temp_r28->model2, temp_r27->pos[temp_r25].x, temp_r27->pos[temp_r25].y, temp_r27->pos[temp_r25].z - 2.0f);
        Hu3DModelRotSetV(temp_r28->model2, &temp_r27->rot);
        Hu3DModelAttrReset(temp_r28->model2, 1U);
        Hu3DModelAttrReset(temp_r28->model2, 0x40000002U);
        Hu3DMotionTimeSet(temp_r28->model2, 0.0f);
    }
    temp_r29 = fn_1_4704(&temp_r31->pool, fn_1_9470, (M567Reel *) p);
    if (temp_r29 != NULL) {
        p->state = 0;
    }
    if ((s16) p->group == 0) {
        temp_r3->slot.blink[0].state += 1;
        temp_r3->slot.blink[1].state += 1;
    } else {
        temp_r27->blink[temp_r25].state += 1;
    }
    omVibrate(p->player, 0xC, 6, 6);
    temp_r28->state = 0x14;
}

s32 fn_1_9470(M567Node *node) {
    s16 temp_r0;
    s32 var_r30;
    M567Player *temp_r31;

    var_r30 = 0;
    temp_r31 = node->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        CharModelAttrReset(temp_r31->charNo, 0x40000002U);
        Hu3DModelAttrReset(temp_r31->pumMdl, 0x40000002U);
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        if (CharMotionEndCheck(temp_r31->charNo) != 0) {
            CharModelAttrSet(temp_r31->charNo, 0x40000004U);
            Hu3DModelAttrSet(temp_r31->pumMdl, 0x40000004U);
            temp_r31->state = (s16) (temp_r31->state + 1);
        }
        break;
    case 2:
        if (CharMotionEndCheck(temp_r31->charNo) != 0) {
            CharModelAttrReset(temp_r31->charNo, 0x40000004U);
            Hu3DModelAttrReset(temp_r31->pumMdl, 0x40000004U);
            CharModelAttrSet(temp_r31->charNo, 0x40000002U);
            Hu3DModelAttrSet(temp_r31->pumMdl, 0x40000002U);
            var_r30 = 1;
        }
        break;
    }
    return var_r30;
}

void fn_1_959C(s16 (*grid)[5], s16 row, s16 col) {
    s16 var_r26;
    s16 var_r28;
    s16 var_r29;
    s32 temp_r3;
    s32 var_r30;

    var_r29 = row;
    var_r28 = col;
    var_r30 = 0;
loop_10:
    if (var_r30 < 3) {
        if (((s16) *(s16 *) ((u8 *) grid + (((var_r29 + 1) * 0xA) + (var_r28 * 2))) == 0) || ((s16) *(s16 *) ((u8 *) grid + (((var_r29 + 1) * 0xA) + (var_r28 * 2))) == 2)) {
            *(s16 *) ((u8 *) grid + ((var_r30 * 2) + 0x6E)) = 0;
            if (var_r29 < 8) {
                var_r29 += 1;
            }
        } else {
            temp_r3 = fn_1_9694(grid, var_r29, var_r28);
            if (temp_r3 < 0) {
                var_r26 = 2;
            } else {
                var_r26 = 1;
            }
            *(s16 *) ((u8 *) grid + ((var_r30 * 2) + 0x6E)) = var_r26;
            var_r28 += temp_r3;
        }
        var_r30 += 1;
        goto loop_10;
    }
}

s32 fn_1_9694(s16 (*grid)[5], s16 row, s16 col) {
    s32 temp_r28;
    s32 temp_r29;
    s32 var_r27;
    s32 var_r30;

    temp_r29 = col + 1;
    temp_r28 = col - 1;
    if ((s16) *(s16 *) ((u8 *) grid + ((row * 0xA) + (temp_r28 * 2))) == -1) {
        return 1;
    }
    if ((s16) *(s16 *) ((u8 *) grid + ((row * 0xA) + (temp_r29 * 2))) == -1) {
        return -1;
    }
    var_r30 = row + 1;
loop_10:
    if (var_r30 >= 9) {
        if (frandmod(2U) != 0) {
            var_r27 = 1;
        } else {
            var_r27 = -1;
        }
        return var_r27;
    }
    if ((s16) *(s16 *) ((u8 *) grid + ((var_r30 * 0xA) + (temp_r28 * 2))) == -1) {
        return 1;
    }
    if ((s16) *(s16 *) ((u8 *) grid + ((var_r30 * 0xA) + (temp_r29 * 2))) == -1) {
        return -1;
    }
    var_r30 += 1;
    goto loop_10;
}

s32 fn_1_979C(M567Node *node) {
    s32 var_r30;
    M567Cursor *temp_r31;

    var_r30 = 0;
    temp_r31 = node->arg;
    if (((s16) temp_r31->mot34 == Hu3DMotionIDGet(temp_r31->model)) && (Hu3DMotionEndCheck(temp_r31->model) != 0)) {
        Hu3DMotionSet(temp_r31->model, temp_r31->mot32);
        Hu3DModelAttrSet(temp_r31->model, 0x40000001U);
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_9828(M567Node *node) {
    s32 var_r30;
    M567Reel *temp_r31;

    var_r30 = 0;
    temp_r31 = node->arg;
    if (Hu3DMotionEndCheck(temp_r31->model2) != 0) {
        Hu3DModelAttrSet(temp_r31->model2, 1U);
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_988C(M567Node *node) {
    s32 var_r30;
    M567Cursor *temp_r31;

    var_r30 = 0;
    temp_r31 = node->arg;
    if (Hu3DMotionEndCheck(temp_r31->fx) != 0) {
        Hu3DModelAttrSet(temp_r31->fx, 1U);
        var_r30 = 1;
    }
    return var_r30;
}

s32 fn_1_98F0(M567Node *node) {
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s32 var_r28;
    M567Blink *temp_r31;

    var_r28 = 0;
    temp_r31 = node->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->timer = 0;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        temp_r31->timer = (s16) (temp_r31->timer % 30);
        temp_f31 = (f32) sin((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->timer / 30.0f))) / 180.0);
        temp_r31->mat->color[0] = (s8) (150.0f + (94.0f * temp_f31));
        temp_r31->mat->color[1] = (s8) (100.0f + (100.0f * temp_f31));
        temp_r31->mat->color[2] = 0;
        break;
    case 2:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x1E) {
            var_r28 = 1;
        }
        temp_f31_2 = (f32) sin((3.141592653589793 * (f64) (180.0f * ((f32) temp_r31->timer / 30.0f))) / 180.0);
        temp_r31->mat->color[0] = (s8) (150.0f + (94.0f * temp_f31_2));
        temp_r31->mat->color[1] = (s8) (100.0f + (100.0f * temp_f31_2));
        temp_r31->mat->color[2] = 0;
        break;
    }
    return var_r28;
}
