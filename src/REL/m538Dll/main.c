// MP5 m538 (Twist 'n' Out), generated from its m2c draft by tools/mp5/ports/m538Dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m538Dll (Twist 'n' Out; tools/mp5/decomp.py m538Dll --types tools/mp5/types/m538Dll.h)
// Written from the draft: a free-for-all battle. Four players run around a round disc "arena" that shrinks in three
// stages (rings), each can spin ("twist") to knock the others off; whoever falls off is out (place = number of
// players out before). The game ends when 3 are out (or the rings are used up). Offsets in comments are GameCube's
// (m2c lays these structs out with 4-byte pointers); the code only uses field names.
// objdata: M538Ply
// objdata fn_1_1198 fn_1_12F0: M538Main
// objexpr lbl_1_bss_C: M538Main
// var ObjectSetup temp_r30: M538Main
// var fn_1_614 temp_r29: M538Ply
// var fn_1_848 temp_r30: M538Ply
// var fn_1_848 temp_r30_2: M538Ply
// var fn_1_BB4 temp_r30: M538Ply
// var fn_1_1DC8 var_r27: M538Ply
// var fn_1_6F24 temp_r31: M538Fly
// var fn_1_9024 temp_r31: M538Fly
// var fn_1_AB54 temp_r31: M538Fly
// var fn_1_B0D0 temp_r31: M538Wave
// var fn_1_7FAC temp_r30: M538Eff
// var fn_1_A8A0 temp_r26: M538Eff
// var fn_1_A8A0 temp_r27: M538Eff
// var fn_1_A8A0 temp_r28: M538Eff
// var fn_1_A8A0 temp_r29: M538Eff
// var fn_1_A8A0 temp_r30: M538Fly
// var fn_1_A8A0 temp_r30_2: M538Fly
// var fn_1_A8A0 temp_r30_3: M538Fly
// var fn_1_A8A0 temp_r30_4: M538Fly

struct M538Eff;
struct M538Part;
struct M538Ply;
struct M538Ring;
struct M538Spin;
struct M538Blink;
typedef s32 (*M538EffFunc)(struct M538Eff *);
typedef s32 (*M538PartFunc)(struct M538Part *);
typedef s32 (*M538PlyFunc)(struct M538Ply *);
typedef s32 (*M538RingFunc)(struct M538Ring *);
typedef s32 (*M538SpinFunc)(struct M538Spin *);
typedef s32 (*M538BlinkFunc)(struct M538Blink *);

typedef struct M538Eff { // 0x10: node of the small effect list in the main work
    struct M538Eff *prev;
    struct M538Eff *next;
    s32 (*func)(struct M538Eff *); // returns nonzero when done
    void *arg;
} M538Eff;

typedef struct M538EffPool { // 0x208
    M538Eff *head; // 0x0
    M538Eff *free; // 0x4
    M538Eff nodes[0x20]; // 0x8
} M538EffPool;

typedef struct M538PartPool { // 8
    struct M538Part *head;
    struct M538Part *free;
} M538PartPool;

typedef struct M538Part { // 0x38: a particle / dust / star node
    struct M538Part *prev; // 0x0
    struct M538Part *next; // 0x4
    M538PartPool *pool; // 0x8
    s32 (*func)(struct M538Part *); // 0xC
    Vec pos; // 0x10
    Vec rot; // 0x1C
    f32 unk28; // radius / speed
    f32 unk2C; // angle
    s16 state; // 0x30
    s16 timer; // 0x32
    s16 model; // 0x34
    s16 pad36;
} M538Part;

typedef struct M538Fly { // 0x30: a flying, spinning model (thrown item / rock / hit player's item)
    Vec pos; // 0x0
    Vec rot; // 0xC
    f32 unk18; // angle
    f32 unk1C; // radius
    f32 unk20;
    f32 unk24;
    s16 model; // 0x28
    s16 state; // 0x2A
    s16 timer; // 0x2C
    s16 pad2E;
} M538Fly;

typedef struct M538Blink { // 8: blink of the model after it was hit
    s16 model; // 0x0
    s16 cnt; // 0x2
    s32 (*func)(struct M538Blink *); // 0x4
} M538Blink;

typedef struct M538Ply { // OMOBJ::data of a player, 0x104
    Vec pos; // 0x0
    Vec rot; // 0xC
    Vec vel; // 0x18
    Vec knock; // 0x24
    Vec holdPos; // 0x30
    Vec holdRot; // 0x3C
    M538Fly fly; // 0x48
    s16 itemMdl; // 0x78
    s16 pad7A;
    M538Blink blink; // 0x7C
    s32 (*func)(struct M538Ply *); // 0x84
    s32 step; // 0x88
    u8 pad8C[0x18];
    f32 twistAng; // 0xA4
    f32 twistRad; // 0xA8
    u8 padAC[0x10];
    f32 faceTarget; // 0xBC
    f32 turnSpd; // 0xC0
    OMOBJ *obj; // 0xC4
    M538PartPool *poolA; // 0xC8
    M538PartPool *poolB; // 0xCC
    struct M538Ply *target; // 0xD0 (COM)
    s16 comState; // 0xD4
    s16 comTimer; // 0xD6
    s16 comLimit; // 0xD8
    s16 comHasTarget; // 0xDA
    s32 sndHandle; // 0xDC
    s16 pan; // 0xE0
    s16 vol; // 0xE2
    s16 charge; // 0xE4
    s16 hitF; // 0xE6
    s16 cnt; // 0xE8
    s16 place; // 0xEA
    s16 alive; // 0xEC
    s16 model; // 0xEE
    s16 player; // 0xF0
    s16 charNo; // 0xF2
    s16 group; // 0xF4
    s16 padNo; // 0xF6
    s16 padF8[2];
    s16 isCom; // 0xFC
    s16 dif; // 0xFE
    s16 timerA; // 0x100
    s16 timerB; // 0x102
} M538Ply;

typedef struct M538CamKey { // 0x18
    Vec tgt;
    f32 az;
    f32 el;
    f32 dist;
} M538CamKey;

typedef struct M538Cam { // 0x34
    M538CamKey cur; // 0x0
    M538CamKey sv; // 0x18
    s16 state; // 0x30
    s16 timer; // 0x32
} M538Cam;

typedef struct M538Ring { // 0x18: one stage of the arena
    f32 radius; // 0x0
    s32 active; // 0x4
    s32 (*func)(struct M538Ring *); // 0x8
    s16 state; // 0xC
    s16 timer; // 0xE
    s16 type; // 0x10
    s16 mdl[3]; // 0x12
} M538Ring;

typedef struct M538Intro { // 0x30
    u8 pad0[0x18];
    Vec v; // 0x18
    s16 state; // 0x24
    s16 cnt; // 0x26
    s16 mdl[4]; // 0x28
} M538Intro;

typedef struct M538Spin { // 4: the platform spin-up at the start/end
    s16 state;
    s16 timer;
} M538Spin;

typedef struct M538Wave { // 0x10
    u8 pad0[4];
    s16 model; // 0x4
    s16 state; // 0x6
    s16 timer; // 0x8
    u8 padA[6];
} M538Wave;

typedef struct M538Rocks { // 0xD4
    u8 pad0[0x10];
    M538Fly fly[4]; // 0x10
    s16 state; // 0xD0
    s16 timer; // 0xD2
} M538Rocks;

typedef struct M538Main { // lbl_1_bss_C data, 0x1920
    struct M538Ply *ply[4]; // 0x0
    M538EffPool eff; // 0x10
    M538Cam cam; // 0x218
    M538Ring ring[3]; // 0x24C
    M538Intro intro; // 0x294
    M538PartPool partA; // 0x2C4
    M538PartPool partB; // 0x2CC
    M538PartPool partC; // 0x2D4
    M538Part partsA[0x10]; // 0x2DC
    M538Part partsB[0x10]; // 0x65C
    M538Part partsC[0x40]; // 0x9DC
    M538Spin spin; // 0x17DC
    M538Wave wave; // 0x17E0
    s32 (*spinFunc)(struct M538Spin *); // 0x17F0
    M538Rocks rocks; // 0x17F4
    s16 light; // 0x18C8
    s16 pad18CA;
    f32 radius; // 0x18CC
    s16 outCount; // 0x18D0
    s16 tie; // 0x18D2
    s16 fxCnt; // 0x18D4
    s16 step; // 0x18D6
    s16 timer; // 0x18D8
    s16 sub; // 0x18DA
    s16 playing; // 0x18DC
    s16 mdlCache[0x1D]; // 0x18DE
    s16 motCache[3]; // 0x1918
    s16 finished; // 0x191E
} M538Main;

typedef struct M538CamTbl { // 0xB0
    M538CamKey key[3];
    f32 extra[26];
} M538CamTbl;


void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_264(s16 mode, s16 frameNo);
void fn_1_4A4(s16 mode, s16 frameNo);
void fn_1_4F8(s16 mode, s16 frameNo);
void fn_1_614(s16 mode, s16 frameNo);
void fn_1_848(s16 mode, s16 frameNo);
void fn_1_BB4(s16 mode, s16 frameNo);
void fn_1_CC0(s16 mode, s16 frameNo);
void fn_1_CFC(s16 mode, s16 frameNo);
void fn_1_D1C(OMOBJ *obj);
void fn_1_FD0(OMOBJ *obj);
void fn_1_1198(OMOBJ *obj);
void fn_1_12F0(OMOBJ *obj);
void fn_1_137C(M538Main *m);
void fn_1_13D8(M538Main *m);
void fn_1_1488(void);
void fn_1_1574(void);
void fn_1_1650(M538Cam *cam);
void fn_1_16BC(M538Cam *cam);
void fn_1_1958(M538Main *m);
s32 fn_1_1B94(M538Ply *ply);
s32 fn_1_1DC8(M538Ply *ply);
s32 fn_1_2988(M538Ply *ply);
s32 fn_1_29F8(M538Ply *ply);
s32 fn_1_2CB8(M538Ply *ply);
s32 fn_1_32C4(M538Ply *ply);
s32 fn_1_39DC(M538Ply *ply);
s32 fn_1_3B2C(M538Ply *ply);
s32 fn_1_3CD4(M538Ply *ply);
s32 fn_1_3E7C(M538Ply *ply);
s32 fn_1_3F60(M538Ply *ply);
s32 fn_1_4428(M538Ply *ply);
s32 fn_1_44AC(M538Blink *blink);
void fn_1_4534(M538Ply *ply);
void fn_1_4714(M538Main *m);
void fn_1_4968(M538Main *m);
void fn_1_4C38(M538Main *m);
void fn_1_4F74(M538Main *m);
s32 fn_1_55C8(M538Ply *ply, f32 *x, f32 *z);
void fn_1_56A4(M538Main *m);
void fn_1_5FC4(M538Ring *ring, s16 type);
s32 fn_1_61F8(M538Ring *ring);
s32 fn_1_62B4(M538Ring *ring);
s32 fn_1_6400(M538Ring *ring);
s32 fn_1_6558(M538Ring *ring);
s32 fn_1_66A4(M538Ring *ring);
s32 fn_1_6918(void);
void fn_1_69C4(M538Fly *fly);
void fn_1_6AE4(M538Ply *ply);
void fn_1_6C24(M538Ply *ply);
void fn_1_6CD4(M538Main *m);
M538Eff *fn_1_6D98(M538Main *m, M538EffFunc func, void *arg);
void fn_1_6DEC(M538Main *m, M538Eff *eff);
void fn_1_6E50(M538Main *m);
s32 fn_1_6F24(M538Eff *eff);
void fn_1_72CC(M538Intro *intro);
void fn_1_765C(M538Intro *intro);
void fn_1_77A4(M538Intro *intro);
s32 fn_1_788C(M538Cam *cam);
s32 fn_1_7AA0(M538Cam *cam);
s32 fn_1_7CB0(M538Cam *cam);
s32 fn_1_7F04(M538Ply *ply);
s32 fn_1_7FAC(M538Ply *ply);
s32 fn_1_8554(M538Ply *ply);
void fn_1_87E4(M538PartPool *pool, M538Part *nodes, s32 count);
M538Part *fn_1_8858(M538PartPool *pool, M538PartFunc func);
void fn_1_88A8(M538Part *part);
void fn_1_8920(M538PartPool *pool);
void fn_1_8A00(M538Main *m);
void fn_1_8B6C(M538Main *m);
s32 fn_1_8CD8(M538Part *part);
s32 fn_1_8F58(M538Part *part);
s32 fn_1_9024(M538Eff *eff);
s32 fn_1_91D8(Vec *pos);
void fn_1_93C4(M538Main *m);
s32 fn_1_94DC(M538Part *part);
s32 fn_1_9C04(M538Part *part);
void fn_1_A2A4(M538Main *m);
void fn_1_A368(M538Main *m);
s32 fn_1_A424(M538Spin *spin);
void fn_1_A6F8(M538Main *m);
void fn_1_A8A0(M538Rocks *rocks);
s32 fn_1_AB54(M538Eff *eff);
s32 fn_1_B0D0(M538Eff *eff);
void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_264(s16 mode, s16 frameNo);
void fn_1_4A4(s16 mode, s16 frameNo);
void fn_1_4F8(s16 mode, s16 frameNo);
void fn_1_614(s16 mode, s16 frameNo);
void fn_1_848(s16 mode, s16 frameNo);
void fn_1_BB4(s16 mode, s16 frameNo);
void fn_1_CC0(s16 mode, s16 frameNo);
void fn_1_CFC(s16 mode, s16 frameNo);
void fn_1_D1C(omObjData *obj);
void fn_1_FD0(omObjData *obj);
void fn_1_1198(omObjData *obj);
void fn_1_12F0(omObjData *obj);
void fn_1_137C(M538Main *m);
void fn_1_13D8(M538Main *m);
void fn_1_1488(void);
void fn_1_1574(void);
void fn_1_1650(M538Cam *cam);
void fn_1_16BC(M538Cam *cam);
void fn_1_1958(M538Main *m);
s32 fn_1_1DC8(M538Ply *ply);
s32 fn_1_2CB8(M538Ply *ply);
s32 fn_1_32C4(M538Ply *ply);
s32 fn_1_39DC(M538Ply *ply);
s32 fn_1_3B2C(M538Ply *ply);
s32 fn_1_3CD4(M538Ply *ply);
s32 fn_1_3E7C(M538Ply *ply);
s32 fn_1_3F60(M538Ply *ply);
s32 fn_1_4428(M538Ply *ply);
s32 fn_1_44AC(M538Blink *blink);
void fn_1_4534(M538Ply *ply);
void fn_1_4714(M538Main *m);
void fn_1_4968(M538Main *m);
void fn_1_4C38(M538Main *m);
void fn_1_4F74(M538Main *m);
s32 fn_1_55C8(M538Ply *ply, f32 *x, f32 *z);
void fn_1_56A4(M538Main *m);
void fn_1_5FC4(M538Ring *ring, s16 type);
s32 fn_1_61F8(M538Ring *ring);
s32 fn_1_62B4(M538Ring *ring);
s32 fn_1_6400(M538Ring *ring);
s32 fn_1_6558(M538Ring *ring);
s32 fn_1_66A4(M538Ring *ring);
s32 fn_1_6918(void);
void fn_1_6AE4(M538Ply *ply);
void fn_1_6C24(M538Ply *ply);
void fn_1_6CD4(M538Main *m);
M538Eff *fn_1_6D98(M538Main *m, s32 (*func)(M538Eff *), void *arg);
void fn_1_6E50(M538Main *m);
s32 fn_1_6F24(M538Eff *eff);
void fn_1_72CC(M538Intro *intro);
void fn_1_765C(M538Intro *intro);
void fn_1_77A4(M538Intro *intro);
s32 fn_1_788C(M538Cam *cam);
s32 fn_1_7AA0(M538Cam *cam);
s32 fn_1_7CB0(M538Cam *cam);
s32 fn_1_7F04(M538Ply *ply);
s32 fn_1_7FAC(M538Ply *ply);
s32 fn_1_8554(M538Ply *ply);
void fn_1_87E4(M538PartPool *pool, M538Part *nodes, s32 count);
M538Part *fn_1_8858(M538PartPool *pool, s32 (*func)(M538Part *));
void fn_1_8920(M538PartPool *pool);
void fn_1_8A00(M538Main *m);
void fn_1_8B6C(M538Main *m);
s32 fn_1_8CD8(M538Part *part);
s32 fn_1_8F58(M538Part *part);
s32 fn_1_9024(M538Eff *eff);
s32 fn_1_91D8(Vec *pos);
void fn_1_93C4(M538Main *m);
s32 fn_1_94DC(M538Part *part);
s32 fn_1_9C04(M538Part *part);
void fn_1_A2A4(M538Main *m);
void fn_1_A368(M538Main *m);
s32 fn_1_A424(M538Spin *spin);
void fn_1_A6F8(M538Main *m);
void fn_1_A8A0(M538Rocks *rocks);
s32 fn_1_AB54(M538Eff *eff);
s32 fn_1_B0D0(M538Eff *eff);

MGSEQ_PARAM lbl_1_data_0 = {
    0,
    0,
    fn_1_1FC,
    fn_1_264,
    fn_1_4A4,
    fn_1_4F8,
    fn_1_614,
    fn_1_848,
    fn_1_BB4,
    fn_1_CC0,
    fn_1_CFC,
};
s32 lbl_1_data_28[0xD][0xB] = {
    {
        DATA_MAKE_NUM(DATADIR_MP5_MARIO, 122),
        DATA_MAKE_NUM(DATADIR_MP5_MARIO, 124),
        DATA_MAKE_NUM(DATADIR_MP5_MARIO, 125),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_MARIO, 126),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 122),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 124),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 125),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGI, 126),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_PEACH, 122),
        DATA_MAKE_NUM(DATADIR_MP5_PEACH, 124),
        DATA_MAKE_NUM(DATADIR_MP5_PEACH, 125),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_PEACH, 126),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 122),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 124),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 125),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHI, 126),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_WARIO, 122),
        DATA_MAKE_NUM(DATADIR_MP5_WARIO, 124),
        DATA_MAKE_NUM(DATADIR_MP5_WARIO, 125),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_WARIO, 126),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_DAISY, 122),
        DATA_MAKE_NUM(DATADIR_MP5_DAISY, 124),
        DATA_MAKE_NUM(DATADIR_MP5_DAISY, 125),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_DAISY, 126),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0),
    },
    {
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 122),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 124),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 125),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 92),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 93),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGI, 126),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 43),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 1),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 23),
        DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0),
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIO not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESA not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
    },
    {
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 122 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 124 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 125 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 92 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 93 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPA not mounted, entry 126 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 43 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 23 */,
        0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */,
    },
};
s32 lbl_1_data_264[0x1D] = {
    DATA_MAKE_NUM(DATADIR_MP5_M538, 9),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 0),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 1),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 2),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 3),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 4),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 5),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 6),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 7),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 8),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 10),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 11),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 12),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 13),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 14),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 15),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 16),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 17),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 19),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 21),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 22),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 23),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 25),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 26),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 27),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 28),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 29),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 30),
    DATA_MAKE_NUM(DATADIR_MP5_M538, 31),
};
s32 lbl_1_data_2D8[3] = { DATA_MAKE_NUM(DATADIR_MP5_M538, 18), DATA_MAKE_NUM(DATADIR_MP5_M538, 20), DATA_MAKE_NUM(DATADIR_MP5_M538, 24) };
M538CamTbl lbl_1_data_2E4 = {
    {
        { { 0.0f, 190.0f, -44.0f }, 90.0f, 7.0f, 3900.0f },
        { { 0.0f, 0.0f, -44.0f }, 90.0f, 60.0f, 6700.0f },
        { { 0.0f, 0.0f, -44.0f }, 90.0f, 60.0f, 3000.0f },
    },
    {
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
        177.0f,
        0.0f,
    },
};
s32 lbl_1_data_394[0xD] = {
    0x1F9,
    0x1E5,
    0x25D,
    0x2AD,
    0x285,
    0x1BD,
    0x299,
    0x1D1,
    0x271,
    0x235,
    0x249,
    0x221,
    0x20D,
};
s32 lbl_1_data_3C8[0xD] = {
    0x1FD,
    0x1E9,
    0x261,
    0x2B1,
    0x289,
    0x1C1,
    0x29D,
    0x1D5,
    0x275,
    0x239,
    0x24D,
    0x225,
    0x211,
};
s8 lbl_1_data_418[0xC] = { 0x6D, 0x35, 0x33, 0x38, 0x5F, 0x74, 0x73, 0x75, 0x6D, 0x75, 0, 0 };
s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
omObjData *lbl_1_bss_C;
HUPROCESS *lbl_1_bss_10;
u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };            /* const */
Vec lbl_1_rodata_60 = { 0.0f, 1.0f, 0.0f };     /* const */
Vec lbl_1_rodata_6C = { 0.0f, 4800.0f, 751.0f }; /* const */
Vec lbl_1_rodata_78 = { 0.0f, 0.0f, 0.0f };     /* const */
s16 lbl_1_rodata_B8[4] = { 0x50, 0x5A, 0x5F, 0 };   /* const */
s16 lbl_1_rodata_C0[4] = { 0x14, 0x32, 0x3C, 0x50 }; /* const */
s16 lbl_1_rodata_C8[4] = { 0x3C, 0x28, 0xA, 0 };    /* const */
s16 lbl_1_rodata_D0[4] = { 0, 0, 0x1E, 0x32 };      /* const */
f32 lbl_1_rodata_EC[4] = { 26244.0f, 24964.0f, 23716.0f, 22500.0f }; /* const */
s32 lbl_1_rodata_FC[4] = { 0x32, 0x46, 0x5A, 0x64 }; /* const */
f32 lbl_1_rodata_158[4] = { -100.0f, -100.0f, 100.0f, 100.0f }; /* const */
f32 lbl_1_rodata_168[4] = { 0.0f, 150.0f, 150.0f, 0.0f }; /* const */
s16 lbl_1_rodata_190[4] = { 1, 4, 7, 0 };           /* const */
s32 (*lbl_1_rodata_1A0[3])(M538Ring *) = { fn_1_62B4, fn_1_6400, fn_1_6558 }; /* const */
f32 lbl_1_rodata_1CC[4] = { -400.0f, -200.0f, 200.0f, 400.0f }; /* const */
u8 lbl_1_rodata_1EC[8][3] = {
    { 0xD9, 0x99, 0x52 },
    { 0xB3, 0xCC, 0 },
    { 0xE0, 0x99, 0x52 },
    { 0xE6, 0x66, 0x33 },
    { 0x99, 0x66, 0x99 },
    { 0xBF, 0x33, 0x99 },
    { 0xFF, 0xB3, 0xCC },
    { 0xE6, 0x7F, 0x99 },
}; /* const */
u8 lbl_1_rodata_21C[0x10][3] = {
    { 0xFF, 0xB3, 0 },
    { 0xE5, 0xFF, 0x66 },
    { 0xFF, 0xE5, 0x4D },
    { 0xCC, 0xB3, 0 },
    { 0xCC, 0x66, 0x33 },
    { 0xFF, 0xE5, 0x4D },
    { 0xFF, 0xA6, 0x4D },
    { 0x7F, 0x33, 0 },
    { 0xB3, 0x4D, 0xB3 },
    { 0xE5, 0xB3, 0xE5 },
    { 0xCC, 0x7F, 0xE5 },
    { 0x7F, 0x33, 0x7F },
    { 0xCC, 0x66, 0x7F },
    { 0xFF, 0xBF, 0xCC },
    { 0xFF, 0x7F, 0x99 },
    { 0xA6, 0x4D, 0x7F },
}; /* const */
u8 lbl_1_rodata_258[0x10][3] = {
    { 0xFF, 0xB3, 0 },
    { 0xE5, 0xFF, 0x66 },
    { 0xFF, 0xE5, 0x4D },
    { 0xCC, 0xB3, 0 },
    { 0xCC, 0x66, 0x33 },
    { 0xFF, 0xE5, 0x4D },
    { 0xFF, 0xA6, 0x4D },
    { 0x7F, 0x33, 0 },
    { 0xB3, 0x4D, 0xB3 },
    { 0xE5, 0xB3, 0xE5 },
    { 0xCC, 0x7F, 0xE5 },
    { 0x7F, 0x33, 0x7F },
    { 0xCC, 0x66, 0x7F },
    { 0xFF, 0xBF, 0xCC },
    { 0xFF, 0x7F, 0x99 },
    { 0xA6, 0x4D, 0x7F },
}; /* const */
s32 lbl_1_rodata_2A4[4] = { 0x1A, 0x1A, 0x19, 0x1B }; /* const */



void ObjectSetup(void) {
    omObjData *temp_r31;
    omObjData *temp_r3;
    s32 var_r29;
    M538Main *temp_r30;

    lbl_1_bss_10 = omInitObjMan(0xA, 0x2000);
    omGameSysInit(lbl_1_bss_10);
    temp_r3 = omAddObjEx(lbl_1_bss_10, 0x65, 0U, 0U, -1, fn_1_1198);
    lbl_1_bss_C = temp_r3;
    temp_r3->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M538Main), MEMORY_DEFAULT_NUM);
    temp_r30 = temp_r3->data;
    temp_r30->playing = 0;
    fn_1_1488();
    fn_1_13D8((M538Main *) temp_r30);
    fn_1_1574();
    var_r29 = 0;
loop_2:
    if (var_r29 < 4) {
        temp_r31 = omAddObjEx(lbl_1_bss_10, 0x64, 1U, 0xBU, 0, fn_1_D1C);
        temp_r31->data = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M538Ply), MEMORY_DEFAULT_NUM);
        temp_r31->work[0] = (u32) var_r29;
        temp_r30->ply[var_r29] = temp_r31->data;
        var_r29 += 1;
        goto loop_2;
    }
    fn_1_137C((M538Main *) temp_r30);
    Hu3DBGColorSet(0U, 0U, 0U);
    Hu3DNoSyncSet(1);
    MgSeqCreate(&lbl_1_data_0);
}

void fn_1_1FC(s16 mode, s16 frameNo) {
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    fn_1_1958((M538Main *) temp_r31);
    temp_r31->playing = 0;
    temp_r31->step = 0;
    temp_r31->sub = 0;
    temp_r31->outCount = 0;
    temp_r31->finished = 0;
    MgSeqModeNext();
}

void fn_1_264(s16 mode, s16 frameNo) {
    s16 temp_r0;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = temp_r31->step;
    if ((u32) temp_r0 <= 6U) {
        switch (temp_r0) {
        case 0:
            MgSeqModeChangeOff();
            temp_r31->timer = 0;
            temp_r31->step = (s16) (temp_r31->step + 1);
            /* fallthrough */
        case 1:
            temp_r31->timer = (s16) (temp_r31->timer + 1);
            if ((s16) temp_r31->timer == 0x3C) {
                temp_r31->timer = 0;
                temp_r31->step = (s16) (temp_r31->step + 1);
            }
            break;
        case 2:
            HuAudFXPlay(0x7DD);
            temp_r31->intro.state = 0;
            temp_r31->step = (s16) (temp_r31->step + 1);
            /* fallthrough */
        case 3:
            temp_r31->timer = (s16) (temp_r31->timer + 1);
            fn_1_765C(&temp_r31->intro);
            if ((s16) temp_r31->timer == 0xB4) {
                temp_r31->timer = 0;
                temp_r31->step = (s16) (temp_r31->step + 1);
            }
            break;
        case 4:
            temp_r31->ring[0].func = fn_1_61F8;
            temp_r31->ring[0].state = 0;
            temp_r31->ring[1].func = fn_1_61F8;
            temp_r31->ring[1].state = 0;
            temp_r31->ring[2].func = fn_1_61F8;
            temp_r31->ring[2].state = 0;
            temp_r31->spin.state = 0;
            temp_r31->spinFunc = fn_1_A424;
            temp_r31->cam.state = 0;
            HuAudFXPlay(0x7DE);
            lbl_1_bss_4 = HuAudFXPlay(0x7DF);
            lbl_1_bss_0 = HuAudFXPlay(0x7E1);
            temp_r31->step = (s16) (temp_r31->step + 1);
            /* fallthrough */
        case 5:
            fn_1_765C(&temp_r31->intro);
            if (fn_1_788C(&temp_r31->cam) != 0) {
                Hu3DModelAttrSet(temp_r31->mdlCache[13], 1U);
                Hu3DModelAttrSet(temp_r31->mdlCache[14], 1U);
                Hu3DModelAttrSet(temp_r31->mdlCache[15], 1U);
                temp_r31->cam.state = 0;
                temp_r31->step = (s16) (temp_r31->step + 1);
            }
            break;
        case 6:
            fn_1_765C(&temp_r31->intro);
            lbl_1_bss_8 = HuAudBGMPlay(0x37);
            temp_r31->timer = 0;
            temp_r31->step = 0;
            MgSeqModeNext();
            break;
        }
    }
    fn_1_6918();
    if ((temp_r31->spinFunc != NULL) && (temp_r31->spinFunc(&temp_r31->spin) != 0)) {
        temp_r31->spinFunc = NULL;
    }
}

void fn_1_4A4(s16 mode, s16 frameNo) {
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    fn_1_765C(&temp_r31->intro);
    fn_1_6918();
    temp_r31->step = 0;
    temp_r31->sub = 0;
}

void fn_1_4F8(s16 mode, s16 frameNo) {
    s16 temp_r0;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = temp_r31->sub;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        temp_r31->playing = 1;
        temp_r31->sub = (s16) (temp_r31->sub + 1);
        temp_r31->step = 0;
        if (temp_r31->spinFunc != NULL) {
            temp_r31->spinFunc = 0U;
        }
        temp_r31->ring[0].state = (s16) (temp_r31->ring[0].state + 1);
        temp_r31->ring[1].state = (s16) (temp_r31->ring[1].state + 1);
        temp_r31->ring[2].state = (s16) (temp_r31->ring[2].state + 1);
        break;
    }
    fn_1_7AA0(&temp_r31->cam);
    if ((s16) temp_r31->outCount >= 3) {
        MgSeqModeNext();
        temp_r31->playing = 0;
        temp_r31->ring[0].active = 0;
        temp_r31->ring[1].active = 0;
        temp_r31->ring[2].active = 0;
    } else if (fn_1_6918() != 0) {
        MgSeqModeNext();
        temp_r31->playing = 0;
        temp_r31->ring[0].active = 0;
        temp_r31->ring[1].active = 0;
        temp_r31->ring[2].active = 0;
    }
    fn_1_A8A0(&temp_r31->rocks);
}

void fn_1_614(s16 mode, s16 frameNo) {
    s32 sp8[4];
    s16 temp_r0;
    s16 temp_r24;
    s16 temp_r25;
    s16 temp_r26;
    s16 var_r27;
    s16 var_r28;
    s16 var_r28_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    M538Ply *temp_r29;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = temp_r31->step;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        var_r28 = 0;
        var_r30 = 0;
loop_6:
        if (var_r30 < 4) {
            var_r28 += temp_r31->ply[var_r30]->place;
            var_r30 += 1;
            goto loop_6;
        }
        if (var_r28 == 0) {
            var_r30_2 = 0;
loop_10:
            if (var_r30_2 < 4) {
                sp8[var_r30_2] = 3;
                var_r30_2 += 1;
                goto loop_10;
            }
            temp_r31->tie = 1;
        } else {
            var_r27 = 0;
            var_r28_2 = 3;
loop_19:
            if (var_r27 < 4) {
                temp_r26 = var_r27;
                var_r30_3 = 0;
loop_17:
                if (var_r30_3 < 4) {
                    if ((s16) temp_r31->ply[var_r30_3]->place == var_r28_2) {
                        sp8[var_r30_3] = temp_r26;
                        var_r27 += 1;
                    }
                    var_r30_3 += 1;
                    goto loop_17;
                }
                var_r28_2 -= 1;
                goto loop_19;
            }
            temp_r31->tie = 0;
        }
        var_r30_4 = 0;
loop_27:
        if (var_r30_4 < 4) {
            temp_r29 = temp_r31->ply[var_r30_4];
            temp_r24 = sp8[var_r30_4];
            temp_r25 = temp_r29->player;
            GWPlayerCoinWinSet(temp_r25, (temp_r31->tie != 0 || temp_r29->alive != 0) ? 1 : 0);
            if ((s16) temp_r29->alive != 0) {
                temp_r29->func = fn_1_7FAC;
                temp_r29->step = 0;
            }
            var_r30_4 += 1;
            goto loop_27;
        }
        temp_r31->step = (s16) (temp_r31->step + 1);
        temp_r31->sub = 0;
        temp_r31->ring[0].func = fn_1_66A4;
        temp_r31->ring[0].state = 0;
        temp_r31->ring[1].func = fn_1_66A4;
        temp_r31->ring[1].state = 0;
        temp_r31->ring[2].func = fn_1_66A4;
        temp_r31->ring[2].state = 0;
        HuAudSStreamFadeOut(lbl_1_bss_8, 0x3E8);
        HuAudFXStop(lbl_1_bss_4);
        HuAudFXStop(lbl_1_bss_0);
        HuAudFXPlay(0x7E0);
        break;
    }
    fn_1_6918();
}

void fn_1_848(s16 mode, s16 frameNo) {
    s16 temp_r0;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    M538Ply *temp_r30;
    M538Ply *temp_r30_2;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = temp_r31->sub;
    switch (temp_r0) {                              /* irregular */
    case 0:
        MgSeqModeChangeOff();
        temp_r31->timer = 0;
        temp_r31->step = 0;
        temp_r31->spinFunc = fn_1_A424;
        temp_r31->spin.state = 2;
        if (fn_1_6D98((M538Main *) temp_r31, fn_1_B0D0, &temp_r31->wave) != NULL) {
            temp_r31->wave.model = (s16) temp_r31->mdlCache[24];
            temp_r31->wave.state = 0;
        }
        temp_r31->sub = (s16) (temp_r31->sub + 1);
        temp_r31->cam.state = 0;
        /* fallthrough */
    case 1:
        var_r29 = 0;
loop_18:
        if (var_r29 < 4) {
            temp_r30 = temp_r31->ply[var_r29];
            if ((s16) temp_r30->alive != 0) {
                if (temp_r30->func == fn_1_7F04) {
                    goto block_17;
                }
            } else if (temp_r30->func == fn_1_4428) {
block_17:
                var_r29 += 1;
                goto loop_18;
            }
        }
        if (var_r29 == 4) {
            Hu3DModelAttrReset(temp_r31->mdlCache[13], 1U);
            Hu3DModelAttrReset(temp_r31->mdlCache[14], 1U);
            Hu3DModelAttrReset(temp_r31->mdlCache[15], 1U);
            Hu3DModelAttrReset(temp_r31->mdlCache[28], 1U);
            temp_r31->intro.state = 0;
            temp_r31->sub = (s16) (temp_r31->sub + 1);
        }
        break;
    case 2:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        fn_1_77A4(&temp_r31->intro);
        fn_1_7CB0(&temp_r31->cam);
        if ((s16) temp_r31->timer == 0x78) {
            temp_r31->timer = 0;
            temp_r31->sub = (s16) (temp_r31->sub + 1);
        }
        break;
    case 3:
        fn_1_A368((M538Main *) temp_r31);
        fn_1_77A4(&temp_r31->intro);
        if (fn_1_7CB0(&temp_r31->cam) != 0) {
            temp_r31->sub = (s16) (temp_r31->sub + 1);
        }
        break;
    case 4:
        fn_1_A368((M538Main *) temp_r31);
        fn_1_77A4(&temp_r31->intro);
        var_r29_2 = 0;
loop_29:
        if (var_r29_2 < 4) {
            temp_r30_2 = temp_r31->ply[var_r29_2];
            if ((s16) temp_r30_2->alive == 0) {
                temp_r30_2->func = fn_1_8554;
                temp_r30_2->step = 0;
                temp_r30_2->timerB = (s16) ((temp_r30_2->place * 0x14) + 0x1E);
            }
            var_r29_2 += 1;
            goto loop_29;
        }
        Hu3DModelAttrReset(temp_r31->mdlCache[13], 0x40000002U);
        Hu3DModelAttrReset(temp_r31->mdlCache[14], 0x40000002U);
        Hu3DModelAttrReset(temp_r31->mdlCache[16], 0x40000002U);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[13], 0.5f);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[14], 0.5f);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[16], 0.5f);
        temp_r31->sub = (s16) (temp_r31->sub + 1);
        /* fallthrough */
    case 5:
        fn_1_A368((M538Main *) temp_r31);
        fn_1_77A4(&temp_r31->intro);
        var_r28 = 0;
        var_r29_3 = 0;
loop_35:
        if (var_r29_3 < 4) {
            if (temp_r31->ply[var_r29_3]->func == NULL) {
                var_r28 += 1;
            }
            var_r29_3 += 1;
            goto loop_35;
        }
        if (var_r28 >= 3) {
            temp_r31->step = 0;
            temp_r31->sub = 0;
            MgSeqModeNext();
        }
        break;
    }
    fn_1_6918();
    if ((temp_r31->spinFunc != NULL) && (temp_r31->spinFunc(&temp_r31->spin) != 0)) {
        temp_r31->spinFunc = NULL;
    }
}

void fn_1_BB4(s16 mode, s16 frameNo) {
    s16 temp_r0;
    s32 var_r29;
    M538Ply *temp_r30;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = temp_r31->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->finished = 1;
        var_r29 = 0;
loop_8:
        if (var_r29 < 4) {
            temp_r30 = temp_r31->ply[var_r29];
            if ((s16) temp_r30->alive != 0) {
                temp_r30->step = (s32) (temp_r30->step + 1);
            }
            CharModelVoicePanSet(temp_r30->charNo, 0x40);
            CharModelVoiceVolSet(temp_r30->charNo, 0x73);
            var_r29 += 1;
            goto loop_8;
        }
        if ((s16) temp_r31->tie != 0) {
            HuAudJinglePlay(0x7B);
            CharLoseVoicePlay(temp_r31->ply[0]->charNo, temp_r31->ply[1]->charNo, temp_r31->ply[2]->charNo, temp_r31->ply[3]->charNo);
        } else {
            HuAudJinglePlay(0x79);
        }
        temp_r31->step = (s16) (temp_r31->step + 1);
        /* fallthrough */
    case 1:
        fn_1_A368((M538Main *) temp_r31);
        return;
    }
}

void fn_1_CC0(s16 mode, s16 frameNo) {
    fn_1_A368((M538Main *) lbl_1_bss_C->data);
}

void fn_1_CFC(s16 mode, s16 frameNo) {
    M538Main *sp8;

    sp8 = lbl_1_bss_C->data;
}

void fn_1_D1C(omObjData *obj) {
    s32 var_r29;
    M538Main *temp_r28;
    M538Ply *temp_r31;

    temp_r31 = obj->data;
    temp_r28 = lbl_1_bss_C->data;
    temp_r31->player = (s16) obj->work[0];
    temp_r31->charNo = (s16) GWPlayerCfg[temp_r31->player].character;
    temp_r31->group = (s16) GWPlayerCfg[temp_r31->player].group;
    temp_r31->padNo = (s16) GWPlayerCfg[temp_r31->player].pad_idx;
    temp_r31->isCom = (s16) GWPlayerCfg[temp_r31->player].iscom;
    temp_r31->dif = (s16) GWPlayerCfg[temp_r31->player].diff;
    temp_r31->obj = obj;
    temp_r28->ply[temp_r31->player] = temp_r31;
    temp_r31->knock.x = 0.0f;
    temp_r31->knock.y = 0.0f;
    temp_r31->knock.z = 0.0f;
    fn_1_4534((M538Ply *) temp_r31);
    temp_r31->func = fn_1_2CB8;
    temp_r31->step = 0;
    temp_r31->charge = 0;
    temp_r31->hitF = 0;
    temp_r31->alive = 1;
    temp_r31->turnSpd = 30.0f;
    *obj->model = CharModelCreate(temp_r31->charNo, 8);
    temp_r31->model = (s16) *obj->model;
    temp_r31->blink.func = 0;
    temp_r31->blink.model = (s16) temp_r31->model;
    temp_r31->blink.cnt = 0;
    temp_r31->place = 3;
    var_r29 = 0;
loop_2:
    if (var_r29 < 0xB) {
        obj->motion[var_r29] = Mp5CharMotionCreateData(temp_r31->charNo, (u32) lbl_1_data_28[Mp5CharNo(temp_r31->charNo)][var_r29], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r29 += 1;
        goto loop_2;
    }
    CharMotionSet(temp_r31->charNo, *obj->motion);
    Hu3DModelAttrSet(*obj->model, 0x40000001U);
    Hu3DModelLayerSet(*obj->model, 2);
    Hu3DModelShadowSet(*obj->model);
    CharEffectLayerSet(4);
    CharMotionDataClose(temp_r31->charNo);
    fn_1_6AE4((M538Ply *) temp_r31);
    temp_r31->poolA = (void *) (&temp_r28->partA);
    temp_r31->poolB = (void *) (&temp_r28->partB);
    temp_r31->comState = 0;
    temp_r31->comHasTarget = 0;
    temp_r31->target = 0;
    CharMotionVoiceOnSet(temp_r31->charNo, 0x2B, 0);
    CharMotionVoiceOnSet(temp_r31->charNo, 0x5C, 0);
    CharMotionVoiceOnSet(temp_r31->charNo, 0x5D, 0);
    obj->func = fn_1_FD0;
}

void fn_1_FD0(omObjData *obj) {
    f32 temp_f31;
    M538Main *temp_r30;
    M538Ply *temp_r31;

    temp_r30 = lbl_1_bss_C->data;
    temp_r31 = obj->data;
    temp_f31 = temp_r30->ring[1].radius;
    if ((s16) temp_r30->finished == 0) {
        temp_r31->pan = (s16) (64.0f + (32.0f * (temp_r31->pos.x / temp_f31)));
        temp_r31->vol = (s16) (115.5f + (11.5f * (temp_r31->pos.z / temp_f31)));
        if ((s16) temp_r31->pan < 0x20) {
            temp_r31->pan = 0x20;
        }
        if ((s16) temp_r31->pan > 0x60) {
            temp_r31->pan = 0x60;
        }
        if ((s16) temp_r31->vol < 0x68) {
            temp_r31->vol = 0x68;
        }
        if ((s16) temp_r31->vol > 0x7F) {
            temp_r31->vol = 0x7F;
        }
        CharModelVoicePanSet(temp_r31->charNo, temp_r31->pan);
        CharModelVoiceVolSet(temp_r31->charNo, temp_r31->vol);
    }
    fn_1_4534((M538Ply *) temp_r31);
    if ((temp_r31->func != NULL) && (temp_r31->func(temp_r31) != 0)) {
        temp_r31->func = NULL;
    }
    if ((temp_r31->blink.func != NULL) && (temp_r31->blink.func(&temp_r31->blink) != 0)) {
        temp_r31->blink.func = NULL;
    }
}


void fn_1_1198(omObjData *obj) {
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    fn_1_56A4((M538Main *) temp_r31);
    fn_1_5FC4(&temp_r31->ring[0], 0);
    fn_1_5FC4(&temp_r31->ring[1], 1);
    fn_1_5FC4(&temp_r31->ring[2], 2);
    fn_1_1650(&temp_r31->cam);
    fn_1_72CC(&temp_r31->intro);
    temp_r31->cam.cur.tgt.x = (f32) lbl_1_data_2E4.key[0].tgt.x;
    temp_r31->cam.cur.tgt.y = (f32) lbl_1_data_2E4.key[0].tgt.y;
    temp_r31->cam.cur.tgt.z = (f32) lbl_1_data_2E4.key[0].tgt.z;
    temp_r31->cam.cur.az = (f32) lbl_1_data_2E4.key[0].az;
    temp_r31->cam.cur.el = (f32) lbl_1_data_2E4.key[0].el;
    temp_r31->cam.cur.dist = (f32) lbl_1_data_2E4.key[0].dist;
    fn_1_6CD4((M538Main *) temp_r31);
    fn_1_8A00((M538Main *) temp_r31);
    fn_1_8B6C((M538Main *) temp_r31);
    fn_1_93C4((M538Main *) temp_r31);
    fn_1_87E4(&temp_r31->partA, &temp_r31->partsA[0], 0x10);
    fn_1_87E4(&temp_r31->partB, &temp_r31->partsB[0], 0x10);
    fn_1_87E4(&temp_r31->partC, &temp_r31->partsC[0], 0x40);
    temp_r31->fxCnt = 0;
    temp_r31->spin.state = 0;
    temp_r31->spinFunc = 0;
    fn_1_A6F8((M538Main *) temp_r31);
    obj->func = fn_1_12F0;
}

void fn_1_12F0(omObjData *obj) {
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    fn_1_16BC(&temp_r31->cam);
    fn_1_4C38((M538Main *) temp_r31);
    fn_1_4F74((M538Main *) temp_r31);
    if ((s32) temp_r31->ring[1].active != 0) {
        fn_1_4968((M538Main *) temp_r31);
    }
    fn_1_4714((M538Main *) temp_r31);
    fn_1_6E50((M538Main *) temp_r31);
    fn_1_8920(&temp_r31->partA);
    fn_1_8920(&temp_r31->partB);
    fn_1_8920(&temp_r31->partC);
}


void fn_1_137C(M538Main *m) {
    s32 var_r31;
    s32 var_r31_2;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x1D) {
        m->mdlCache[var_r31] = -1;
        var_r31 += 1;
        goto loop_2;
    }
    var_r31_2 = 0;
loop_5:
    if (var_r31_2 < 3) {
        m->motCache[var_r31_2] = -1;
        var_r31_2 += 1;
        goto loop_5;
    }
}

void fn_1_13D8(M538Main *m) {
    s16 temp_r3;

    temp_r3 = Hu3DGLightCreate(0.0f, 4800.0f, 3600.0f, 0.0f, -1.0f, -1.0f, 0x7FU, 0x7FU, 0x7FU);
    Hu3DGLightInfinitytSet(temp_r3);
    m->light = temp_r3;
    Hu3DGLightColorSet(m->light, 0x7FU, 0x7FU, 0x7FU, 0U);
}

void fn_1_1488(void) {
    f32 sp8;

    Hu3DCameraCreate((s32) *lbl_1_rodata_10);
    Hu3DCameraPerspectiveSet((s32) *lbl_1_rodata_10, 15.0f, 20.0f, 20000.0f, 1.2f);
    sp8 = 0.0f;
    Hu3DCameraPosSet((s32) *lbl_1_rodata_10, 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, 0.0f);
}

void fn_1_1574(void) {
    Vec sp8;
    Vec sp20;
    Vec sp14;

    sp20.x = lbl_1_rodata_60.x;
    sp20.y = lbl_1_rodata_60.y;
    sp20.z = lbl_1_rodata_60.z;
    sp14.x = lbl_1_rodata_6C.x;
    sp14.y = lbl_1_rodata_6C.y;
    sp14.z = lbl_1_rodata_6C.z;
    sp8.x = lbl_1_rodata_78.x;
    sp8.y = lbl_1_rodata_78.y;
    sp8.z = lbl_1_rodata_78.z;
    Hu3DShadowCreate(15.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&sp14, &sp20, &sp8);
    Hu3DShadowSizeSet(0x80U);
    Hu3DShadowColSet(0xFU, 0xFU, 0xFU);
}

void fn_1_1650(M538Cam *cam) {
    cam->cur.az = 0.0f;
    cam->cur.el = 0.0f;
    cam->cur.dist = 1000.0f;
    cam->cur.tgt.x = 0.0f;
    cam->cur.tgt.y = 0.0f;
    cam->cur.tgt.z = 0.0f;
    cam->state = 0;
}

void fn_1_16BC(M538Cam *cam) {
    f32 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f64 temp_f28;
    f64 temp_f28_2;

loop_2:
    if (cam->cur.az > 360.0f) {
        cam->cur.az -= 360.0f;
        goto loop_2;
    }
loop_5:
    if (cam->cur.az < 0.0f) {
        cam->cur.az += 360.0f;
        goto loop_5;
    }
loop_8:
    if (cam->cur.el > 360.0f) {
        cam->cur.el -= 360.0f;
        goto loop_8;
    }
loop_11:
    if (cam->cur.el < 0.0f) {
        cam->cur.el += 360.0f;
        goto loop_11;
    }
    temp_f28 = cos((3.141592653589793 * (f64) cam->cur.az) / 180.0);
    temp_f31 = (f32) ((f64) cam->cur.tgt.x + ((f64) cam->cur.dist * cos((3.141592653589793 * (f64) cam->cur.el) / 180.0) * temp_f28));
    temp_f30 = (f32) ((f64) cam->cur.tgt.y + ((f64) cam->cur.dist * sin((3.141592653589793 * (f64) cam->cur.el) / 180.0)));
    temp_f28_2 = sin((3.141592653589793 * (f64) cam->cur.az) / 180.0);
    temp_f29 = (f32) ((f64) cam->cur.tgt.z + ((f64) cam->cur.dist * cos((3.141592653589793 * (f64) cam->cur.el) / 180.0) * temp_f28_2));
    sp8 = cam->cur.tgt.z;
    Hu3DCameraPosSet((s32) *lbl_1_rodata_10, temp_f31, temp_f30, temp_f29, 0.0f, 1.0f, 0.0f, cam->cur.tgt.x, cam->cur.tgt.y, cam->cur.tgt.z);
}

void fn_1_1958(M538Main *m) {
    M538Ply *temp_r31;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f31;
    s32 var_r30;
    u32 temp_r3;

    var_r30 = 0;
loop_7:
    if (var_r30 < 4) {
        temp_r31 = m->ply[var_r30];
        temp_r3 = (u32) var_r30 >> 0x1FU;
        temp_r31->pos.x = (300.0f * (f32) (((var_r30 & 1) ^ temp_r3) - temp_r3)) - 150.0f;
        temp_r31->pos.y = 0.0f;
        temp_r31->pos.z = (300.0f * (f32) ((s32) (((u32) var_r30 >> 0x1FU) + var_r30) >> 1)) - 150.0f;
        temp_f28 = -temp_r31->pos.z;
        temp_f29 = -temp_r31->pos.x;
        if (temp_f28 == 0.0f) {
            if (temp_f29 >= 0.0f) {
                var_f31 = 1.5707964f;
            } else {
                var_f31 = -1.5707964f;
            }
        } else {
            var_f31 = (f32) atan2((f64) temp_f29, (f64) temp_f28);
        }
        temp_f30 = (f32) ((f64) (180.0f * var_f31) / 3.141592653589793);
        temp_r31->faceTarget = temp_f30;
        temp_r31->rot.x = 0.0f;
        temp_r31->rot.y = temp_f30;
        temp_r31->rot.z = 0.0f;
        omSetTra(temp_r31->obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        omSetRot(temp_r31->obj, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
        var_r30 += 1;
        goto loop_7;
    }
}


s32 fn_1_1DC8(M538Ply *ply) {
    u16 sp60[4];
    u16 sp58[4];
    u16 sp50[4];
    u16 sp48[4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
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
    M538Ply *var_r27;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f18;
    f32 temp_f19;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    f32 temp_f31;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    s16 temp_r0;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r28_3;
    u32 var_r23;
    M538Main *temp_r29;

    var_r26 = 0;
    sp60[0] = (u16) lbl_1_rodata_B8[0];
    sp60[1] = (u16) lbl_1_rodata_B8[1];
    sp60[2] = (u16) lbl_1_rodata_B8[2];
    sp60[3] = (u16) lbl_1_rodata_B8[3];
    sp58[0] = (u16) lbl_1_rodata_C0[0];
    sp58[1] = (u16) lbl_1_rodata_C0[1];
    sp58[2] = (u16) lbl_1_rodata_C0[2];
    sp58[3] = (u16) lbl_1_rodata_C0[3];
    sp50[0] = (u16) lbl_1_rodata_C8[0];
    sp50[1] = (u16) lbl_1_rodata_C8[1];
    sp50[2] = (u16) lbl_1_rodata_C8[2];
    sp50[3] = (u16) lbl_1_rodata_C8[3];
    sp48[0] = (u16) lbl_1_rodata_D0[0];
    sp48[1] = (u16) lbl_1_rodata_D0[1];
    sp48[2] = (u16) lbl_1_rodata_D0[2];
    sp48[3] = (u16) lbl_1_rodata_D0[3];
    temp_r29 = lbl_1_bss_C->data;
    if ((s16) temp_r29->playing == 0) {
        return 0;
    }
    temp_r0 = ply->comState;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->target = NULL;
        ply->comHasTarget = 0;
        ply->comState += 1;
        /* fallthrough */
    case 1:
        temp_f31 = (ply->pos.x * ply->pos.x) + (ply->pos.z * ply->pos.z);
        temp_f0 = (temp_r29->radius - 200.0f) * (temp_r29->radius - 200.0f);
        sp44 = temp_f0;
        if ((temp_f31 > temp_f0) && (frandmod(0x64U) < (s16) sp60[ply->dif])) {
            temp_f19 = -ply->pos.z;
            temp_f20 = -ply->pos.x;
            if (temp_f19 == 0.0f) {
                if (temp_f20 >= 0.0f) {
                    var_f29 = 1.5707964f;
                } else {
                    var_f29 = -1.5707964f;
                }
            } else {
                sp1C = (f32) atan2((f64) temp_f20, (f64) temp_f19);
                var_f29 = sp1C;
            }
            ply->faceTarget = (f32) (((f64) (180.0f * var_f29) / 3.141592653589793) + (f64) (20.0f * (((f32) frandmod(0x2711U) / 10000.0f) - 0.5f)));
            ply->comTimer = 0;
            ply->comLimit = frandmod(0xAU) + 0xA;
            ply->comState = 2;
            var_r26 = 1;
        } else {
            var_f30 = 2250000.0f;
            var_r27 = NULL;
            var_r28 = 0;
loop_27:
            if (var_r28 < 4) {
                if ((var_r28 != (s16) ply->player) && ((s16) temp_r29->ply[var_r28]->alive != 0) && ((s16) temp_r29->ply[var_r28]->hitF == 0)) {
                    temp_f22 = ply->pos.x - temp_r29->ply[var_r28]->pos.x;
                    temp_f21 = ply->pos.z - temp_r29->ply[var_r28]->pos.z;
                    temp_f23 = (temp_f22 * temp_f22) + (temp_f21 * temp_f21);
                    if (temp_f23 < var_f30) {
                        var_f30 = temp_f23;
                        var_r27 = temp_r29->ply[var_r28];
                    }
                }
                var_r28 += 1;
                goto loop_27;
            }
            if ((var_f30 < 160000.0f) && (var_r27 != NULL)) {
                if (frandmod(0x64U) < (s16) sp58[ply->dif]) {
                    ply->comHasTarget = 1;
                    ply->target = var_r27;
                    temp_f0_2 = var_r27->pos.z - ply->pos.z;
                    sp40 = temp_f0_2;
                    temp_f18 = var_r27->pos.x - ply->pos.x;
                    if (temp_f0_2 == 0.0f) {
                        if (temp_f18 >= 0.0f) {
                            var_f28 = 1.5707964f;
                        } else {
                            var_f28 = -1.5707964f;
                        }
                    } else {
                        sp18 = (f32) atan2((f64) temp_f18, (f64) sp40);
                        var_f28 = sp18;
                    }
                    ply->faceTarget = (f32) ((f64) (180.0f * var_f28) / 3.141592653589793);
                    ply->comTimer = 0;
                    ply->comLimit = frandmod(0xAU) + 0xA;
                    ply->comState = 3;
                    var_r26 = 1;
                } else {
                    ply->target = var_r27;
                    temp_f0_3 = ply->pos.z - var_r27->pos.z;
                    sp38 = temp_f0_3;
                    sp3C = ply->pos.x - var_r27->pos.x;
                    if (temp_f0_3 == 0.0f) {
                        if (sp3C >= 0.0f) {
                            var_f27 = 1.5707964f;
                        } else {
                            var_f27 = -1.5707964f;
                        }
                    } else {
                        sp14 = (f32) atan2((f64) sp3C, (f64) sp38);
                        var_f27 = sp14;
                    }
                    temp_f0_4 = -ply->pos.z;
                    sp30 = temp_f0_4;
                    sp34 = -ply->pos.x;
                    if (temp_f0_4 == 0.0f) {
                        if (sp34 >= 0.0f) {
                            var_f26 = 1.5707964f;
                        } else {
                            var_f26 = -1.5707964f;
                        }
                    } else {
                        sp10 = (f32) atan2((f64) sp34, (f64) sp30);
                        var_f26 = sp10;
                    }
                    ply->faceTarget = (f32) (((f64) (180.0f * var_f27) / 3.141592653589793) + ((f64) (180.0f * var_f26) / 3.141592653589793));
                    ply->comTimer = 0;
                    ply->comLimit = frandmod(0xAU) + 0xA;
                    ply->comState = 2;
                    var_r26 = 1;
                }
            } else if (frandmod(0x64U) < (s16) sp48[ply->dif]) {
                if (temp_f31 > 40000.0f) {
                    temp_f0_5 = -ply->pos.z;
                    sp28 = temp_f0_5;
                    sp2C = -ply->pos.x;
                    if (temp_f0_5 == 0.0f) {
                        if (sp2C >= 0.0f) {
                            var_f25 = 1.5707964f;
                        } else {
                            var_f25 = -1.5707964f;
                        }
                    } else {
                        spC = (f32) atan2((f64) sp2C, (f64) sp28);
                        var_f25 = spC;
                    }
                    ply->faceTarget = (f32) (((f64) (180.0f * var_f25) / 3.141592653589793) + (f64) (20.0f * (((f32) frandmod(0x2711U) / 10000.0f) - 0.5f)));
                    ply->comTimer = 0;
                    ply->comLimit = frandmod(0xAU) + 0xA;
                    ply->comState = 5;
                    var_r26 = 1;
                } else if (var_r27 != NULL) {
                    ply->comHasTarget = 1;
                    ply->target = var_r27;
                    ply->comTimer = 0;
                    ply->comLimit = frandmod(3U) + 3;
                    ply->comState = 3;
                } else {
                    ply->comTimer = 0;
                    ply->comLimit = frandmod(3U) + 3;
                    ply->comState = 4;
                }
            } else if (frandmod(0x64U) < (s16) sp50[ply->dif]) {
                ply->comTimer = 0;
                ply->comLimit = frandmod(0xAU) + 0xA;
                ply->comState = 4;
            } else {
                var_r25 = 0;
                var_r28_2 = 0;
loop_66:
                if (var_r28_2 < 4) {
                    if ((var_r28_2 != (s16) ply->player) && ((s16) temp_r29->ply[var_r28_2]->alive != 0)) {
                        var_r25 += 1;
                    }
                    var_r28_2 += 1;
                    goto loop_66;
                }
                if (var_r25 > 1) {
                    var_r23 = frandmod((u32) var_r25);
                } else {
                    var_r23 = 0;
                }
                var_r24 = 0;
                var_r28_3 = 0;
loop_77:
                if (var_r28_3 < 4) {
                    if ((var_r28_3 != (s16) ply->player) && ((s16) temp_r29->ply[var_r28_3]->alive != 0)) {
                        if ((s32) var_r23 == var_r24) {
                            var_r27 = temp_r29->ply[var_r28_3];
                        } else {
                            var_r24 += 1;
                            goto block_76;
                        }
                    } else {
block_76:
                        var_r28_3 += 1;
                        goto loop_77;
                    }
                }
                ply->comHasTarget = 1;
                ply->target = var_r27;
                temp_f0_6 = var_r27->pos.z - ply->pos.z;
                sp20 = temp_f0_6;
                sp24 = var_r27->pos.x - ply->pos.x;
                if (temp_f0_6 == 0.0f) {
                    if (sp24 >= 0.0f) {
                        var_f24 = 1.5707964f;
                    } else {
                        var_f24 = -1.5707964f;
                    }
                } else {
                    sp8 = (f32) atan2((f64) sp24, (f64) sp20);
                    var_f24 = sp8;
                }
                ply->faceTarget = (f32) ((f64) (180.0f * var_f24) / 3.141592653589793);
                ply->comTimer = 0;
                ply->comLimit = frandmod(0xAU) + 0xA;
                ply->comState = 3;
                var_r26 = 1;
            }
        }
        break;
    case 2:
        ply->comTimer += 1;
        if ((s16) ply->comTimer == (s16) ply->comLimit) {
            ply->comState = 0;
        }
        var_r26 = 1;
        break;
    case 3:
        ply->comTimer += 1;
        if (((s16) ply->comTimer == (s16) ply->comLimit) || ((s16) ply->comHasTarget == 0)) {
            ply->comState = 0;
        }
        var_r26 = 1;
        break;
    case 4:
        ply->comTimer += 1;
        if ((s16) ply->comTimer == (s16) ply->comLimit) {
            ply->comState = 0;
        }
        break;
    case 5:
        ply->comTimer += 1;
        if (((s16) ply->comTimer == (s16) ply->comLimit) || (((ply->pos.x * ply->pos.x) + (ply->pos.z * ply->pos.z)) < 40000.0f)) {
            ply->comState = 0;
        }
        var_r26 = 1;
        break;
    }
    return var_r26;
}



s32 fn_1_2CB8(M538Ply *ply) {
    s32 sp38[4];
    f32 sp28[4];
    f64 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f0_2;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f19;
    f32 var_f20;
    f32 var_f25;
    f32 var_f26;
    f32 var_f31;
    f64 temp_f0;
    s32 temp_r0;
    s32 var_r20;
    s32 var_r22;
    s32 var_r23;
    s32 var_r25;
    s32 var_r26;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->hitF = 0;
        CharMotionShiftSet(ply->charNo, *ply->obj->motion, 0.0f, 5.0f, 0x40000001U);
        ply->step += 1;
        /* fallthrough */
    case 1:
        if ((s16) ply->isCom != 0) {
            var_r26 = 0;
            sp28[0] = lbl_1_rodata_EC[0];
            sp28[1] = lbl_1_rodata_EC[1];
            sp28[2] = lbl_1_rodata_EC[2];
            sp28[3] = lbl_1_rodata_EC[3];
            sp38[0] = lbl_1_rodata_FC[0];
            sp38[1] = lbl_1_rodata_FC[1];
            sp38[2] = lbl_1_rodata_FC[2];
            sp38[3] = lbl_1_rodata_FC[3];
            if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                var_r28 = 0;
            } else {
                if (((s16) ply->comHasTarget != 0) && ((M538Ply *) ply->target != NULL)) {
                    temp_f27 = ply->target->pos.x - ply->pos.x;
                    temp_f28 = ply->target->pos.z - ply->pos.z;
                    if (((temp_f27 * temp_f27) + (temp_f28 * temp_f28)) < sp28[ply->dif]) {
                        if (temp_f28 == 0.0f) {
                            if (temp_f27 >= 0.0f) {
                                var_f26 = 1.5707964f;
                            } else {
                                var_f26 = -1.5707964f;
                            }
                        } else {
                            sp14 = (f32) atan2((f64) temp_f27, (f64) temp_f28);
                            var_f26 = sp14;
                        }
                        var_f31 = (f32) (((f64) (180.0f * var_f26) / 3.141592653589793) - (f64) ply->faceTarget);
loop_18:
                        if (var_f31 > 180.0f) {
                            var_f31 -= 360.0f;
                            goto loop_18;
                        }
loop_21:
                        if (var_f31 < -180.0f) {
                            var_f31 += 360.0f;
                            goto loop_21;
                        }
                        sp18 = var_f31;
                        temp_f0 = fabs(sp18);
                        sp20 = temp_f0;
                        temp_f0_2 = (f32) temp_f0;
                        sp10 = temp_f0_2;
                        spC = temp_f0_2;
                        if ((spC < 90.0f) && (frandmod(0x64U) < (s32) sp38[ply->dif])) {
                            ply->comHasTarget = 0;
                            var_r26 = 1;
                        }
                    }
                }
                var_r28 = var_r26;
            }
            var_r29 = var_r28;
        } else {
            var_r23 = 0;
            if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                var_r25 = 0;
            } else {
                if ((s32) (HuPadBtnDown[ply->padNo] & 0x100) != 0) {
                    var_r23 = 1;
                }
                var_r25 = var_r23;
            }
            var_r29 = var_r25;
        }
        if (var_r29 != 0) {
            ply->func = fn_1_39DC;
            ply->step = 0;
        } else {
            if ((s16) ply->isCom != 0) {
                var_r29_2 = fn_1_1DC8(ply);
            } else {
                var_r20 = 0;
                if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                    var_r22 = 0;
                } else {
                    temp_f29 = (f32) (s8) (u8) HuPadStkX[ply->padNo];
                    temp_f30 = (f32) -(s8) (u8) HuPadStkY[ply->padNo];
                    if (temp_f30 < 0.0f) {
                        var_f20 = -temp_f30;
                    } else {
                        var_f20 = temp_f30;
                    }
                    if (temp_f29 < 0.0f) {
                        var_f19 = -temp_f29;
                    } else {
                        var_f19 = temp_f29;
                    }
                    sp1C = var_f19 + var_f20;
                    if (sp1C > 32.0f) {
                        if (temp_f30 == 0.0f) {
                            if (temp_f29 >= 0.0f) {
                                var_f25 = 1.5707964f;
                            } else {
                                var_f25 = -1.5707964f;
                            }
                        } else {
                            sp8 = (f32) atan2((f64) temp_f29, (f64) temp_f30);
                            var_f25 = sp8;
                        }
                        ply->faceTarget = (f32) ((f64) (180.0f * var_f25) / 3.141592653589793);
                        var_r20 = 1;
                    }
                    var_r22 = var_r20;
                }
                var_r29_2 = var_r22;
            }
            if (var_r29_2 != 0) {
                ply->func = fn_1_32C4;
                ply->step = 0;
            }
        }
        break;
    }
    return 0;
}

s32 fn_1_32C4(M538Ply *ply) {
    s32 sp40[4];
    f32 sp30[4];
    f64 sp28;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    M538Part *temp_r3;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f18;
    f32 var_f19;
    f32 var_f25;
    f32 var_f26;
    f32 var_f31;
    f64 temp_f0;
    s32 temp_r0;
    s32 var_r19;
    s32 var_r21;
    s32 var_r22;
    s32 var_r24;
    s32 var_r25;
    s32 var_r27;
    s32 var_r29;
    s32 var_r29_2;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->hitF = 0;
        CharMotionShiftSet(ply->charNo, ply->obj->motion[1], 0.0f, 5.0f, 0x40000001U);
        ply->step += 1;
        /* fallthrough */
    case 1:
        if ((s16) ply->isCom != 0) {
            var_r25 = 0;
            sp30[0] = lbl_1_rodata_EC[0];
            sp30[1] = lbl_1_rodata_EC[1];
            sp30[2] = lbl_1_rodata_EC[2];
            sp30[3] = lbl_1_rodata_EC[3];
            sp40[0] = lbl_1_rodata_FC[0];
            sp40[1] = lbl_1_rodata_FC[1];
            sp40[2] = lbl_1_rodata_FC[2];
            sp40[3] = lbl_1_rodata_FC[3];
            if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                var_r27 = 0;
            } else {
                if (((s16) ply->comHasTarget != 0) && ((M538Ply *) ply->target != NULL)) {
                    temp_f27 = ply->target->pos.x - ply->pos.x;
                    temp_f28 = ply->target->pos.z - ply->pos.z;
                    sp20 = (temp_f27 * temp_f27) + (temp_f28 * temp_f28);
                    if (sp20 < sp30[ply->dif]) {
                        if (temp_f28 == 0.0f) {
                            if (temp_f27 >= 0.0f) {
                                var_f26 = 1.5707964f;
                            } else {
                                var_f26 = -1.5707964f;
                            }
                        } else {
                            sp14 = (f32) atan2((f64) temp_f27, (f64) temp_f28);
                            var_f26 = sp14;
                        }
                        var_f31 = (f32) (((f64) (180.0f * var_f26) / 3.141592653589793) - (f64) ply->faceTarget);
loop_18:
                        if (var_f31 > 180.0f) {
                            var_f31 -= 360.0f;
                            goto loop_18;
                        }
loop_21:
                        if (var_f31 < -180.0f) {
                            var_f31 += 360.0f;
                            goto loop_21;
                        }
                        sp18 = var_f31;
                        temp_f0 = fabs(sp18);
                        sp28 = temp_f0;
                        temp_f0_2 = (f32) temp_f0;
                        sp10 = temp_f0_2;
                        spC = temp_f0_2;
                        if ((spC < 90.0f) && (frandmod(0x64U) < (s32) sp40[ply->dif])) {
                            ply->comHasTarget = 0;
                            var_r25 = 1;
                        }
                    }
                }
                var_r27 = var_r25;
            }
            var_r29 = var_r27;
        } else {
            var_r22 = 0;
            if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                var_r24 = 0;
            } else {
                if ((s32) (HuPadBtnDown[ply->padNo] & 0x100) != 0) {
                    var_r22 = 1;
                }
                var_r24 = var_r22;
            }
            var_r29 = var_r24;
        }
        if (var_r29 != 0) {
            ply->func = fn_1_39DC;
            ply->step = 0;
        } else {
            if ((s16) ply->isCom != 0) {
                var_r29_2 = fn_1_1DC8(ply);
            } else {
                var_r19 = 0;
                if ((s16) ((M538Main *)lbl_1_bss_C->data)->playing == 0) {
                    var_r21 = 0;
                } else {
                    temp_f29 = (f32) (s8) (u8) HuPadStkX[ply->padNo];
                    temp_f30 = (f32) -(s8) (u8) HuPadStkY[ply->padNo];
                    if (temp_f30 < 0.0f) {
                        var_f19 = -temp_f30;
                    } else {
                        var_f19 = temp_f30;
                    }
                    if (temp_f29 < 0.0f) {
                        var_f18 = -temp_f29;
                    } else {
                        var_f18 = temp_f29;
                    }
                    sp1C = var_f18 + var_f19;
                    if (sp1C > 32.0f) {
                        if (temp_f30 == 0.0f) {
                            if (temp_f29 >= 0.0f) {
                                var_f25 = 1.5707964f;
                            } else {
                                var_f25 = -1.5707964f;
                            }
                        } else {
                            sp8 = (f32) atan2((f64) temp_f29, (f64) temp_f30);
                            var_f25 = sp8;
                        }
                        ply->faceTarget = (f32) ((f64) (180.0f * var_f25) / 3.141592653589793);
                        var_r19 = 1;
                    }
                    var_r21 = var_r19;
                }
                var_r29_2 = var_r21;
            }
            if (var_r29_2 != 0) {
                ply->vel.x = (f32) ((f64) ply->vel.x + (7.5 * sin((3.141592653589793 * (f64) ply->faceTarget) / 180.0)));
                ply->vel.z = (f32) ((f64) ply->vel.z + (7.5 * cos((3.141592653589793 * (f64) ply->faceTarget) / 180.0)));
                temp_f1 = Hu3DMotionTimeGet(ply->model);
                if ((temp_f1 == 15.0f) || (temp_f1 == 30.0f)) {
                    temp_r3 = fn_1_8858(ply->poolA, fn_1_8CD8);
                    if (temp_r3 != NULL) {
                        temp_r3->pos.x = ply->pos.x;
                        temp_r3->pos.y = ply->pos.y;
                        temp_r3->pos.z = ply->pos.z;
                        temp_r3->state = 0;
                    }
                }
            } else {
                ply->func = fn_1_2CB8;
                ply->step = 0;
            }
        }
        break;
    }
    return 0;
}

s32 fn_1_39DC(M538Ply *ply) {
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->hitF = 0;
        CharMotionShiftSet(ply->charNo, ply->obj->motion[2], 0.0f, 5.0f, 0U);
        HuAudFXPlayVolPan(0x7E2, ply->vol, ply->pan);
        ply->cnt = 0;
        ply->step += 1;
        /* fallthrough */
    case 1:
        if ((s16) ply->obj->motion[2] == Hu3DMotionIDGet(ply->model)) {
            CharMotionSpeedSet(ply->charNo, 1.2f);
            ply->step += 1;
        }
        break;
    case 2:
        ply->cnt += 1;
        if (((s16) ply->cnt >= 9) && ((s16) ply->charge <= 5)) {
            ply->charge += 1;
        }
        if (Hu3DMotionEndCheck(ply->model) != 0) {
            ply->func = fn_1_2CB8;
            ply->step = 0;
            ply->charge = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_3B2C(M538Ply *ply) {
    M538Part *temp_r3;
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->comState = 0;
        ply->charge = 0;
        ply->hitF = 1;
        CharMotionShiftSet(ply->charNo, ply->obj->motion[3], 0.0f, 5.0f, 0U);
        temp_r3 = fn_1_8858(ply->poolB, fn_1_8F58);
        if (temp_r3 != NULL) {
            temp_r3->pos.x = ply->pos.x;
            temp_r3->pos.y = ply->pos.y;
            temp_r3->pos.z = ply->pos.z;
            temp_r3->state = 0;
        }
        HuAudFXPlayVolPan(0x7E3, ply->vol, ply->pan);
        HuAudFXPlayVolPan(lbl_1_data_3C8[Mp5CharNo(ply->charNo)], ply->vol, ply->pan);
        ply->step += 1;
        /* fallthrough */
    case 1:
        ply->vel.x = ply->knock.x;
        ply->vel.z = ply->knock.z;
        if ((s16) ply->obj->motion[3] == Hu3DMotionIDGet(ply->model)) {
            CharMotionSpeedSet(ply->charNo, 2.0f);
            ply->step += 1;
        }
        break;
    case 2:
        ply->vel.x = ply->knock.x;
        ply->vel.z = ply->knock.z;
        if (Hu3DMotionEndCheck(ply->model) != 0) {
            ply->func = fn_1_3E7C;
            ply->step = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_3CD4(M538Ply *ply) {
    M538Part *temp_r3;
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->comState = 0;
        ply->charge = 0;
        ply->hitF = 1;
        CharMotionShiftSet(ply->charNo, ply->obj->motion[4], 0.0f, 5.0f, 0U);
        temp_r3 = fn_1_8858(ply->poolB, fn_1_8F58);
        if (temp_r3 != NULL) {
            temp_r3->pos.x = ply->pos.x;
            temp_r3->pos.y = ply->pos.y;
            temp_r3->pos.z = ply->pos.z;
            temp_r3->state = 0;
        }
        HuAudFXPlayVolPan(0x7E3, ply->vol, ply->pan);
        HuAudFXPlayVolPan(lbl_1_data_3C8[Mp5CharNo(ply->charNo)], ply->vol, ply->pan);
        ply->step += 1;
        /* fallthrough */
    case 1:
        ply->vel.x = ply->knock.x;
        ply->vel.z = ply->knock.z;
        if ((s16) ply->obj->motion[4] == Hu3DMotionIDGet(ply->model)) {
            CharMotionSpeedSet(ply->charNo, 2.0f);
            ply->step += 1;
        }
        break;
    case 2:
        ply->vel.x = ply->knock.x;
        ply->vel.z = ply->knock.z;
        if (Hu3DMotionEndCheck(ply->model) != 0) {
            ply->func = fn_1_3E7C;
            ply->step = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_3E7C(M538Ply *ply) {
    M538Part *temp_r3;
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->comState = 0;
        CharMotionSet(ply->charNo, ply->obj->motion[5]);
        temp_r3 = fn_1_8858(ply->poolA, fn_1_8CD8);
        if (temp_r3 != NULL) {
            temp_r3->pos.x = ply->pos.x;
            temp_r3->pos.y = ply->pos.y;
            temp_r3->pos.z = ply->pos.z;
            temp_r3->state = 0;
        }
        ply->step += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(ply->model) != 0) {
            ply->blink.func = fn_1_44AC;
            ply->func = fn_1_32C4;
            ply->step = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_3F60(M538Ply *ply) {
    f32 sp8;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f26;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s32 temp_r0;
    M538Main *temp_r30;

    temp_r30 = lbl_1_bss_C->data;
    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        fn_1_6C24(ply);
        CharMotionShiftSet(ply->charNo, ply->obj->motion[6], 0.0f, 5.0f, 0x40000001U);
        temp_f27 = ply->pos.z;
        temp_f28 = ply->pos.x;
        if (temp_f27 == 0.0f) {
            if (temp_f28 >= 0.0f) {
                var_f29 = 1.5707964f;
            } else {
                var_f29 = -1.5707964f;
            }
        } else {
            var_f29 = (f32) atan2((f64) temp_f28, (f64) temp_f27);
        }
        ply->twistAng = (f32) ((f64) (180.0f * var_f29) / 3.141592653589793);
        temp_f30 = (ply->pos.x * ply->pos.x) + (ply->pos.z * ply->pos.z);
        var_f26 = sqrtf(temp_f30);
        ply->twistRad = var_f26;
        ply->rot.y = ply->faceTarget;
        if (fn_1_6D98((M538Main *) temp_r30, fn_1_6F24, &ply->fly) != NULL) {
            ply->fly.pos.x = ply->holdPos.x;
            ply->fly.pos.y = ply->holdPos.y;
            ply->fly.pos.z = ply->holdPos.z;
            ply->fly.rot.x = ply->holdRot.x;
            ply->fly.rot.y = ply->holdRot.y;
            ply->fly.rot.z = ply->holdRot.z;
            ply->fly.model = ply->itemMdl;
            ply->fly.state = 0;
        }
        ply->timerA = 0;
        omVibrate(ply->player, 0x1E, 0xC, 0);
        ply->sndHandle = HuAudFXPlay(lbl_1_data_394[Mp5CharNo(ply->charNo)]);
        ply->step += 1;
        /* fallthrough */
    case 1:
        HuAudFXPanning(ply->sndHandle, ply->pan);
        HuAudFXVolSet(ply->sndHandle, ply->vol);
        ply->twistAng -= 6.3f;
        ply->vel.y = 2.0f;
        ply->twistRad += 4.3f;
        temp_f25 = (f32) ((f64) ply->twistRad * sin((3.141592653589793 * (f64) ply->twistAng) / 180.0));
        temp_f24 = (f32) ((f64) ply->twistRad * cos((3.141592653589793 * (f64) ply->twistAng) / 180.0));
        ply->pos.x = temp_f25;
        ply->pos.z = temp_f24;
        ply->faceTarget += 1.0f;
loop_17:
        if (ply->faceTarget > 180.0f) {
            ply->faceTarget -= 360.0f;
            goto loop_17;
        }
        ply->rot.y += 3.0f;
loop_20:
        if (ply->rot.y > 180.0f) {
            ply->rot.y -= 360.0f;
            goto loop_20;
        }
        ply->timerA += 1;
        if ((s16) ply->timerA == 0xB4) {
            ply->func = fn_1_4428;
            ply->step = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_4428(M538Ply *ply) {
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        CharMotionSet(ply->charNo, ply->obj->motion[10]);
        CharModelAttrSet(ply->charNo, 1U);
        CharModelAttrSet(ply->charNo, 0x40000002U);
        ply->step += 1;
        break;
    }
    return 0;
}

s32 fn_1_44AC(M538Blink *blink) {
    s32 var_r30;

    var_r30 = 0;
    blink->cnt += 1;
    if ((s16) blink->cnt == 0x3C) {
        blink->cnt = 0;
        var_r30 = 1;
    }
    if ((s32) (blink->cnt & 1) != 0) {
        Hu3DModelAttrSet(blink->model, 1U);
    } else {
        Hu3DModelAttrReset(blink->model, 1U);
    }
    return var_r30;
}

void fn_1_4534(M538Ply *ply) {
    ply->vel.x = 0.0f;
    ply->vel.y = 0.0f;
    ply->vel.z = 0.0f;
    ply->knock.x *= 0.9f;
    ply->knock.y *= 0.9f;
    ply->knock.z *= 0.9f;
    if ((f32) fabs(ply->knock.x) < 0.01f) {
        ply->knock.x = 0.0f;
    }
    if ((f32) fabs(ply->knock.y) < 0.01f) {
        ply->knock.y = 0.0f;
    }
    if ((f32) fabs(ply->knock.z) < 0.01f) {
        ply->knock.z = 0.0f;
    }
}

void fn_1_4714(M538Main *m) {
    M538Ply *temp_r31;
    f32 var_f31;
    s32 var_r30;

    var_r30 = 0;
loop_18:
    if (var_r30 < 4) {
        temp_r31 = m->ply[var_r30];
        temp_r31->pos.x += temp_r31->vel.x;
        temp_r31->pos.y += temp_r31->vel.y;
        temp_r31->pos.z += temp_r31->vel.z;
        var_f31 = temp_r31->faceTarget;
        if ((f32) fabs(temp_r31->rot.y - temp_r31->faceTarget) > 180.0f) {
            if (temp_r31->rot.y < temp_r31->faceTarget) {
                var_f31 = temp_r31->faceTarget - 360.0f;
            } else if (temp_r31->rot.y > temp_r31->faceTarget) {
                var_f31 = 360.0f + temp_r31->faceTarget;
            }
        }
        if (temp_r31->rot.y < var_f31) {
            temp_r31->rot.y += temp_r31->turnSpd;
            if (temp_r31->rot.y > var_f31) {
                temp_r31->rot.y = var_f31;
            }
        } else if (temp_r31->rot.y > var_f31) {
            temp_r31->rot.y -= temp_r31->turnSpd;
            if (temp_r31->rot.y < var_f31) {
                temp_r31->rot.y = var_f31;
            }
        }
loop_13:
        if (temp_r31->rot.y > 180.0f) {
            temp_r31->rot.y -= 360.0f;
            goto loop_13;
        }
loop_16:
        if (temp_r31->rot.y < -180.0f) {
            temp_r31->rot.y += 360.0f;
            goto loop_16;
        }
        Hu3DModelPosSetV(temp_r31->model, &temp_r31->pos);
        omSetTra(temp_r31->obj, temp_r31->pos.x, temp_r31->pos.y, temp_r31->pos.z);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        omSetRot(temp_r31->obj, temp_r31->rot.x, temp_r31->rot.y, temp_r31->rot.z);
        var_r30 += 1;
        goto loop_18;
    }
}

void fn_1_4968(M538Main *m) {
    M538Ply *temp_r31;
    f32 temp_f31;
    s32 var_r29;
    s32 var_r30;

    temp_f31 = m->ring[1].radius;
    m->radius = temp_f31;
    var_r29 = 0;
    var_r30 = 0;
loop_13:
    if (var_r30 < 4) {
        temp_r31 = m->ply[var_r30];
        if ((((s32 (*)(M538Ply *)) temp_r31->func) != fn_1_3F60) && (((s32 (*)(M538Ply *)) temp_r31->func) != fn_1_4428) && ((s16) temp_r31->alive != 0) && (((temp_r31->pos.x * temp_r31->pos.x) + (temp_r31->pos.z * temp_r31->pos.z)) > (temp_f31 * temp_f31))) {
            temp_r31->vel.x = 0.0f;
            temp_r31->vel.y = 0.0f;
            temp_r31->vel.z = 0.0f;
            temp_r31->knock.x *= 0.9f;
            temp_r31->knock.y *= 0.9f;
            temp_r31->knock.z *= 0.9f;
            if ((f32) fabs(temp_r31->knock.x) < 0.01f) {
                temp_r31->knock.x = 0.0f;
            }
            if ((f32) fabs(temp_r31->knock.y) < 0.01f) {
                temp_r31->knock.y = 0.0f;
            }
            if ((f32) fabs(temp_r31->knock.z) < 0.01f) {
                temp_r31->knock.z = 0.0f;
            }
            temp_r31->func = fn_1_3F60;
            temp_r31->step = 0;
            temp_r31->alive = 0;
            temp_r31->place = m->outCount;
            var_r29 += 1;
        }
        var_r30 += 1;
        goto loop_13;
    }
    m->outCount += var_r29;
}

void fn_1_4C38(M538Main *m) {
    M538Ply *temp_r30;
    M538Ply *temp_r31;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f28;
    s32 var_r28;
    s32 var_r29;

    var_r29 = 0;
loop_18:
    if (var_r29 < 3) {
        temp_r31 = m->ply[var_r29];
        if ((((s32 (*)(M538Ply *)) temp_r31->func) != fn_1_3F60) && (((s32 (*)(M538Ply *)) temp_r31->func) != fn_1_4428) && ((s16) temp_r31->alive != 0)) {
            var_r28 = var_r29 + 1;
loop_16:
            if (var_r28 < 4) {
                temp_r30 = m->ply[var_r28];
                if ((((s32 (*)(M538Ply *)) temp_r30->func) != fn_1_3F60) && (((s32 (*)(M538Ply *)) temp_r30->func) != fn_1_4428) && ((s16) temp_r30->alive != 0)) {
                    temp_f31 = temp_r31->pos.x - temp_r30->pos.x;
                    temp_f30 = temp_r31->pos.z - temp_r30->pos.z;
                    if (((temp_f31 * temp_f31) + (temp_f30 * temp_f30)) < 12100.0f) {
                        if (temp_f30 == 0.0f) {
                            if (temp_f31 >= 0.0f) {
                                var_f28 = 1.5707964f;
                            } else {
                                var_f28 = -1.5707964f;
                            }
                        } else {
                            var_f28 = (f32) atan2((f64) temp_f31, (f64) temp_f30);
                        }
                        temp_f29 = (f32) ((f64) (180.0f * var_f28) / 3.141592653589793);
                        temp_r31->vel.x = (f32) ((f64) (0.5f * temp_r31->vel.x) + (3.75 * sin((3.141592653589793 * (f64) temp_f29) / 180.0)));
                        temp_r31->vel.z = (f32) ((f64) (0.5f * temp_r31->vel.z) + (3.75 * cos((3.141592653589793 * (f64) temp_f29) / 180.0)));
                        temp_r30->vel.x = (f32) ((f64) (0.5f * temp_r30->vel.x) - (3.75 * sin((3.141592653589793 * (f64) temp_f29) / 180.0)));
                        temp_r30->vel.z = (f32) ((f64) (0.5f * temp_r30->vel.z) - (3.75 * cos((3.141592653589793 * (f64) temp_f29) / 180.0)));
                    }
                }
                var_r28 += 1;
                goto loop_16;
            }
        }
        var_r29 += 1;
        goto loop_18;
    }
}

void fn_1_4F74(M538Main *m) {
    f32 sp18[4];
    f32 sp8[4];
    f32 sp38[4];
    f32 sp28[4];
    M538Ply *temp_r30;
    M538Ply *temp_r31;
    f32 temp_f24;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 var_f28;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;

    sp38[0] = lbl_1_rodata_158[0];
    sp38[1] = lbl_1_rodata_158[1];
    sp38[2] = lbl_1_rodata_158[2];
    sp38[3] = lbl_1_rodata_158[3];
    sp28[0] = lbl_1_rodata_168[0];
    sp28[1] = lbl_1_rodata_168[1];
    sp28[2] = lbl_1_rodata_168[2];
    sp28[3] = lbl_1_rodata_168[3];
    var_r28 = 0;
loop_52:
    if (var_r28 < 4) {
        temp_r30 = m->ply[var_r28];
        if ((s16) temp_r30->charge != 0) {
            var_f29 = (temp_r30->rot.y - 60.0f) + ((120.0f * (f32) temp_r30->charge) / 5.0f);
loop_4:
            if (var_f29 > 180.0f) {
                var_f29 -= 360.0f;
                goto loop_4;
            }
loop_7:
            if (var_f29 < -180.0f) {
                var_f29 += 360.0f;
                goto loop_7;
            }
            temp_f25 = (f32) sin((3.141592653589793 * (f64) var_f29) / 180.0);
            temp_f24 = (f32) cos((3.141592653589793 * (f64) var_f29) / 180.0);
            var_r29 = 0;
loop_10:
            if (var_r29 < 4) {
                sp18[var_r29] = temp_r30->pos.x + ((temp_f24 * sp38[var_r29]) + (temp_f25 * sp28[var_r29]));
                sp8[var_r29] = temp_r30->pos.z + ((temp_f25 * -sp38[var_r29]) + (temp_f24 * sp28[var_r29]));
                var_r29 += 1;
                goto loop_10;
            }
            var_r29_2 = 0;
loop_50:
            if (var_r29_2 < 4) {
                if (var_r28 != var_r29_2) {
                    temp_r31 = m->ply[var_r29_2];
                    if (((s16) temp_r31->hitF == 0) && (((s32 (*)(M538Blink *)) temp_r31->blink.func) == NULL) && (fn_1_55C8(temp_r31, &sp18[0], &sp8[0]) != 0)) {
                        omVibrate(temp_r30->player, 0xC, 6, 6);
                        omVibrate(temp_r31->player, 0xC, 0xC, 0);
                        temp_f27 = temp_r30->pos.x - temp_r31->pos.x;
                        temp_f26 = temp_r30->pos.z - temp_r31->pos.z;
                        if (temp_f26 == 0.0f) {
                            if (temp_f27 >= 0.0f) {
                                var_f28 = 1.5707964f;
                            } else {
                                var_f28 = -1.5707964f;
                            }
                        } else {
                            var_f28 = (f32) atan2((f64) temp_f27, (f64) temp_f26);
                        }
                        var_f31 = (f32) (180.0 + ((f64) (180.0f * var_f28) / 3.141592653589793));
loop_23:
                        if (var_f31 > 180.0f) {
                            var_f31 -= 360.0f;
                            goto loop_23;
                        }
loop_26:
                        if (var_f31 < -180.0f) {
                            var_f31 += 360.0f;
                            goto loop_26;
                        }
                        temp_r31->knock.x = (f32) (35.0 * sin((3.141592653589793 * (f64) var_f31) / 180.0));
                        temp_r31->knock.z = (f32) (35.0 * cos((3.141592653589793 * (f64) var_f31) / 180.0));
                        var_f30 = temp_r31->rot.y - var_f31;
loop_29:
                        if (var_f30 > 180.0f) {
                            var_f30 -= 360.0f;
                            goto loop_29;
                        }
loop_32:
                        if (var_f30 < -180.0f) {
                            var_f30 += 360.0f;
                            goto loop_32;
                        }
                        if ((f32) fabs(var_f30) < 90.0f) {
                            temp_r31->faceTarget = var_f31;
loop_36:
                            if (temp_r31->faceTarget > 180.0f) {
                                temp_r31->faceTarget -= 360.0f;
                                goto loop_36;
                            }
loop_39:
                            if (temp_r31->faceTarget < -180.0f) {
                                temp_r31->faceTarget += 360.0f;
                                goto loop_39;
                            }
                            temp_r31->func = fn_1_3B2C;
                        } else {
                            temp_r31->faceTarget = 180.0f + var_f31;
loop_43:
                            if (temp_r31->faceTarget > 180.0f) {
                                temp_r31->faceTarget -= 360.0f;
                                goto loop_43;
                            }
loop_46:
                            if (temp_r31->faceTarget < -180.0f) {
                                temp_r31->faceTarget += 360.0f;
                                goto loop_46;
                            }
                            temp_r31->func = fn_1_3CD4;
                        }
                        temp_r31->step = 0;
                    }
                }
                var_r29_2 += 1;
                goto loop_50;
            }
        }
        var_r28 += 1;
        goto loop_52;
    }
}

s32 fn_1_55C8(M538Ply *ply, f32 *x, f32 *z) {
    s32 var_r31;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r6;
    u32 temp_r6_2;
    u32 temp_r6_3;
    u32 temp_r6_4;

    var_r31 = 0;
loop_4:
    if (var_r31 >= 4) {
        return 1;
    }
    temp_r6 = var_r31 + 1;
    temp_r6_2 = temp_r6 >> 0x1FU;
    temp_r0 = (temp_r6 << 0x1E) - temp_r6_2;
    temp_r6_3 = var_r31 + 1;
    temp_r6_4 = temp_r6_3 >> 0x1FU;
    temp_r0_2 = (temp_r6_3 << 0x1E) - temp_r6_4;
    if ((((ply->pos.x - x[var_r31]) * (z[(temp_r6 % 4)] - z[var_r31])) - ((ply->pos.z - z[var_r31]) * (x[(temp_r6_3 % 4)] - x[var_r31]))) < 0.0f) {
        return 0;
    }
    var_r31 += 1;
    goto loop_4;
}

void fn_1_56A4(M538Main *m) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r3;
    s16 temp_r3_10;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r3_6;
    s16 temp_r3_7;
    s16 temp_r3_8;
    s16 temp_r3_9;
    s16 var_r28;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;
    s16 var_r31_4;
    s16 var_r31_5;
    s16 var_r31_6;
    s16 var_r31_7;
    s16 var_r31_8;
    s16 var_r31_9;
    s32 var_r29;

    if ((s16) m->mdlCache[0xB] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xB], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0xB] = temp_r3;
        var_r31 = temp_r3;
    } else {
        var_r31 = Hu3DModelLink(m->mdlCache[0xB]);
    }
    Hu3DModelAttrSet(var_r31, 1U);
    Hu3DModelAttrSet(var_r31, 0x40000002U);
    Hu3DModelLayerSet(var_r31, 0);
    Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(var_r31);
    Hu3DModelAttrReset(var_r31, 1U);
    Hu3DMotionSpeedSet(var_r31, 0.0f);
    if ((s16) m->mdlCache[0xC] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xC], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0xC] = temp_r3_2;
        var_r31_2 = temp_r3_2;
    } else {
        var_r31_2 = Hu3DModelLink(m->mdlCache[0xC]);
    }
    Hu3DModelAttrSet(var_r31_2, 1U);
    Hu3DModelAttrSet(var_r31_2, 0x40000002U);
    Hu3DModelLayerSet(var_r31_2, 3);
    Hu3DModelPosSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(var_r31_2);
    Hu3DModelAttrReset(var_r31_2, 1U);
    Hu3DMotionSpeedSet(var_r31_2, 0.0f);
    if ((s16) m->mdlCache[0xD] < 0) {
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xD], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0xD] = temp_r3_3;
        var_r31_3 = temp_r3_3;
    } else {
        var_r31_3 = Hu3DModelLink(m->mdlCache[0xD]);
    }
    Hu3DModelAttrSet(var_r31_3, 1U);
    Hu3DModelAttrSet(var_r31_3, 0x40000002U);
    Hu3DModelLayerSet(var_r31_3, 0);
    Hu3DModelPosSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_3, 1U);
    if ((s16) m->mdlCache[0xE] < 0) {
        temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xE], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0xE] = temp_r3_4;
        var_r31_4 = temp_r3_4;
    } else {
        var_r31_4 = Hu3DModelLink(m->mdlCache[0xE]);
    }
    Hu3DModelAttrSet(var_r31_4, 1U);
    Hu3DModelAttrSet(var_r31_4, 0x40000002U);
    Hu3DModelLayerSet(var_r31_4, 0);
    Hu3DModelPosSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_4, 1U);
    if ((s16) m->mdlCache[0xF] < 0) {
        temp_r3_5 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xF], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0xF] = temp_r3_5;
        var_r31_5 = temp_r3_5;
    } else {
        var_r31_5 = Hu3DModelLink(m->mdlCache[0xF]);
    }
    Hu3DModelAttrSet(var_r31_5, 1U);
    Hu3DModelAttrSet(var_r31_5, 0x40000001U);
    Hu3DModelLayerSet(var_r31_5, 0);
    Hu3DModelPosSet(var_r31_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_5, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_5, 1U);
    if ((s16) m->mdlCache[0x10] < 0) {
        temp_r3_6 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x10], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0x10] = temp_r3_6;
        var_r31_6 = temp_r3_6;
    } else {
        var_r31_6 = Hu3DModelLink(m->mdlCache[0x10]);
    }
    Hu3DModelAttrSet(var_r31_6, 1U);
    Hu3DModelAttrSet(var_r31_6, 0x40000002U);
    Hu3DModelLayerSet(var_r31_6, 0);
    Hu3DModelPosSet(var_r31_6, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_6, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_6, 1U);
    if ((s16) m->mdlCache[0x18] < 0) {
        temp_r3_7 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x18], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0x18] = temp_r3_7;
        var_r31_7 = temp_r3_7;
    } else {
        var_r31_7 = Hu3DModelLink(m->mdlCache[0x18]);
    }
    Hu3DModelAttrSet(var_r31_7, 1U);
    Hu3DModelAttrSet(var_r31_7, 0x40000002U);
    Hu3DModelLayerSet(var_r31_7, 3);
    Hu3DModelPosSet(var_r31_7, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_7, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(var_r31_7, 1U);
    if ((s16) m->mdlCache[0x1C] < 0) {
        temp_r3_8 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x1C], MEMORY_DEFAULT_NUM, HEAP_DATA));
        m->mdlCache[0x1C] = temp_r3_8;
        var_r31_8 = temp_r3_8;
    } else {
        var_r31_8 = Hu3DModelLink(m->mdlCache[0x1C]);
    }
    Hu3DModelAttrSet(var_r31_8, 1U);
    Hu3DModelAttrSet(var_r31_8, 0x40000001U);
    Hu3DModelLayerSet(var_r31_8, 3);
    Hu3DModelPosSet(var_r31_8, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_8, 0.0f, 0.0f, 0.0f);
    var_r29 = 0;
loop_32:
    if (var_r29 < 0x18) {
        if ((s16) m->mdlCache[0x11] < 0) {
            temp_r3_9 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x11], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->mdlCache[0x11] = temp_r3_9;
            var_r31_9 = temp_r3_9;
        } else {
            var_r31_9 = Hu3DModelLink(m->mdlCache[0x11]);
        }
        if ((s16) m->motCache[0] < 0) {
            temp_r3_10 = Hu3DJointMotion(var_r31_9, HuDataSelHeapReadNum(*lbl_1_data_2D8, MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->motCache[0] = temp_r3_10;
            var_r28 = temp_r3_10;
        } else {
            var_r28 = m->motCache[0];
        }
        Hu3DMotionSet(var_r31_9, var_r28);
        Hu3DModelAttrSet(var_r31_9, 1U);
        Hu3DModelAttrSet(var_r31_9, 0x40000002U);
        Hu3DModelLayerSet(var_r31_9, 1);
        temp_f31 = (f32) ((3.141592653589793 * (f64) (15.0f * (f32) var_r29)) / 180.0);
        temp_f30 = (f32) (750.0 * sin((f64) temp_f31));
        Hu3DModelPosSet(var_r31_9, temp_f30, 0.0f, (f32) (750.0 * cos((f64) temp_f31)));
        Hu3DModelRotSet(var_r31_9, 0.0f, 15.0f * (f32) var_r29, 0.0f);
        Hu3DModelShadowMapSet(var_r31_9);
        Hu3DMotionSpeedSet(var_r31_9, 0.0f);
        Hu3DMotionTimeSet(var_r31_9, (f32) frandmod(0x10U));
        Hu3DModelAttrReset(var_r31_9, 1U);
        var_r29 += 1;
        goto loop_32;
    }
}

void fn_1_5FC4(M538Ring *ring, s16 type) {
    u16 sp8[3];
    f32 var_f31;
    s16 temp_r3;
    s16 var_r30;
    s32 var_r29;
    M538Main *temp_r28;

    sp8[0] = (u16) lbl_1_rodata_190[0];
    sp8[1] = (u16) lbl_1_rodata_190[1];
    sp8[2] = (u16) lbl_1_rodata_190[2];
    if (type == 1) {
        var_f31 = 50.0f;
    } else {
        var_f31 = 0.0f;
    }
    temp_r28 = lbl_1_bss_C->data;
    var_r29 = 0;
loop_11:
    if (var_r29 < 3) {
        if ((s16) temp_r28->mdlCache[var_r29 + (s16) sp8[type]] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[var_r29 + (s16) sp8[type]], MEMORY_DEFAULT_NUM, HEAP_DATA));
            temp_r28->mdlCache[var_r29 + (s16) sp8[type]] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(temp_r28->mdlCache[var_r29 + (s16) sp8[type]]);
        }
        ring->mdl[var_r29] = var_r30;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        if (type == 1) {
            Hu3DModelLayerSet(var_r30, 7);
        } else {
            Hu3DModelLayerSet(var_r30, 6);
        }
        Hu3DModelPosSet(var_r30, 0.0f, var_f31, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r29 += 1;
        goto loop_11;
    }
    ring->radius = 750.0f;
    ring->state = 0;
    ring->timer = 0;
    ring->active = 1;
    ring->func = NULL;
    ring->type = type;
}

s32 fn_1_61F8(M538Ring *ring) {
    s16 temp_r0;

    temp_r0 = ring->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(ring->mdl[0], 1U);
        Hu3DModelAttrReset(ring->mdl[0], 0x40000002U);
        ring->state += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(ring->mdl[0]) != 0) {
            ring->func = lbl_1_rodata_1A0[ring->type];
            ring->state = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_62B4(M538Ring *ring) {
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = ring->state;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        Hu3DModelAttrReset(ring->mdl[1], 1U);
        Hu3DModelAttrReset(ring->mdl[1], 0x40000002U);
        Hu3DModelAttrSet(ring->mdl[1], 0x40000001U);
        Hu3DModelAttrSet(ring->mdl[0], 1U);
        ring->state += 1;
        break;
    case 2:
        ring->timer += 1;
        if ((s16) ring->timer == 0x708) {
            ring->state += 1;
            var_r30 = 1;
        }
        Hu3DModelPosSet(ring->mdl[1], 0.0f, (630.0f * (f32) ring->timer) / 1800.0f, 0.0f);
        break;
    }
    return var_r30;
}

s32 fn_1_6400(M538Ring *ring) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = ring->state;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        Hu3DModelAttrReset(ring->mdl[1], 1U);
        Hu3DModelAttrReset(ring->mdl[1], 0x40000002U);
        Hu3DModelAttrSet(ring->mdl[1], 0x40000001U);
        Hu3DModelAttrSet(ring->mdl[0], 1U);
        ring->state += 1;
        break;
    case 2:
        ring->timer += 1;
        if ((s16) ring->timer == 0x708) {
            ring->state += 1;
            var_r30 = 1;
        }
        temp_f31 = 1.0f - ((f32) ring->timer / 1800.0f);
        ring->radius = 750.0f * temp_f31;
        Hu3DModelScaleSet(ring->mdl[1], temp_f31, 1.0f, temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_6558(M538Ring *ring) {
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = ring->state;
    switch (temp_r0) {                              /* irregular */
    case 1:
        break;
    case 0:
        Hu3DModelAttrReset(ring->mdl[1], 1U);
        Hu3DModelAttrReset(ring->mdl[1], 0x40000002U);
        Hu3DModelAttrSet(ring->mdl[1], 0x40000001U);
        Hu3DModelAttrSet(ring->mdl[0], 1U);
        ring->state += 1;
        break;
    case 2:
        ring->timer += 1;
        if ((s16) ring->timer == 0x708) {
            ring->state += 1;
            var_r30 = 1;
        }
        Hu3DModelPosSet(ring->mdl[1], 0.0f, (270.0f * (f32) ring->timer) / 1800.0f, 0.0f);
        break;
    }
    return var_r30;
}

s32 fn_1_66A4(M538Ring *ring) {
    f32 temp_f30;
    s16 temp_r0;

    temp_r0 = ring->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(ring->mdl[1], 0x40000001U);
        ring->state += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(ring->mdl[1]) != 0) {
            ring->state += 1;
        }
        break;
    case 2:
        Hu3DModelAttrReset(ring->mdl[2], 1U);
        Hu3DModelAttrReset(ring->mdl[2], 0x40000002U);
        Hu3DModelAttrSet(ring->mdl[1], 1U);
        if ((s16) ring->type == 0) {
            Hu3DModelPosSet(ring->mdl[2], 0.0f, (630.0f * (f32) ring->timer) / 1800.0f, 0.0f);
        }
        if ((s16) ring->type == 1) {
            temp_f30 = 1.0f - ((f32) ring->timer / 1800.0f);
            Hu3DModelScaleSet(ring->mdl[2], temp_f30, 1.0f, temp_f30);
        }
        if ((s16) ring->type == 2) {
            Hu3DModelPosSet(ring->mdl[2], 0.0f, (270.0f * (f32) ring->timer) / 1800.0f, 0.0f);
        }
        ring->state += 1;
        /* fallthrough */
    case 3:
        if (Hu3DMotionEndCheck(ring->mdl[2]) != 0) {
            Hu3DModelAttrSet(ring->mdl[2], 1U);
            ring->func = NULL;
            ring->state = 0;
        }
        break;
    }
    return 0;
}

s32 fn_1_6918(void) {
    s32 var_r30;
    M538Main *temp_r31;

    var_r30 = 0;
    temp_r31 = lbl_1_bss_C->data;
    if (temp_r31->ring[0].func != NULL) {
        temp_r31->ring[0].func(&temp_r31->ring[0]);
    }
    if (temp_r31->ring[1].func != NULL) {
        var_r30 = temp_r31->ring[1].func(&temp_r31->ring[1]);
    }
    if (temp_r31->ring[2].func != NULL) {
        temp_r31->ring[2].func(&temp_r31->ring[2]);
        fn_1_A2A4((M538Main *) temp_r31);
    }
    return var_r30 & temp_r31->ring[1].active;
}


void fn_1_6AE4(M538Ply *ply) {
    s16 temp_r3;
    s16 var_r31;
    M538Main *temp_r29;

    temp_r29 = lbl_1_bss_C->data;
    if ((s16) temp_r29->mdlCache[0] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(*lbl_1_data_264, MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r29->mdlCache[0] = temp_r3;
        var_r31 = temp_r3;
    } else {
        var_r31 = Hu3DModelLink(temp_r29->mdlCache[0]);
    }
    ply->itemMdl = var_r31;
    Hu3DModelAttrSet(var_r31, 1U);
    Hu3DModelAttrSet(var_r31, 0x40000002U);
    Hu3DModelLayerSet(var_r31, 2);
    Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(var_r31);
    Hu3DModelAttrReset(var_r31, 1U);
    Hu3DModelHookSet(ply->model, CharModelItemHookGet(ply->charNo, 8, 0), ply->itemMdl);
}

void fn_1_6C24(M538Ply *ply) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;

    Hu3DModelObjMtxGet(ply->model, CharModelItemHookGet(ply->charNo, 8, 0), sp20);
    Hu3DMtxTransGet(sp20, &sp14);
    Hu3DMtxRotGet(sp20, &sp8);
    Hu3DModelHookReset(ply->model);
    ply->holdPos.x = sp14.x;
    ply->holdPos.y = sp14.y;
    ply->holdPos.z = sp14.z;
    ply->holdRot.x = sp8.x;
    ply->holdRot.y = sp8.y;
    ply->holdRot.z = sp8.z;
    Hu3DModelPosSetV(ply->itemMdl, &sp14);
    Hu3DModelRotSetV(ply->itemMdl, &sp8);
}

void fn_1_6CD4(M538Main *m) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 0x1F) {
        m->eff.nodes[var_r31].prev = NULL;
        m->eff.nodes[var_r31].next = &m->eff.nodes[var_r31 + 1];
        m->eff.nodes[var_r31].func = NULL;
        m->eff.nodes[var_r31].arg = NULL;
        var_r31 += 1;
        goto loop_2;
    }
    m->eff.nodes[var_r31].prev = NULL;
    m->eff.nodes[var_r31].next = NULL;
    m->eff.nodes[var_r31].func = NULL;
    m->eff.nodes[var_r31].arg = NULL;
    m->eff.head = NULL;
    m->eff.free = m->eff.nodes;
}

M538Eff *fn_1_6D98(M538Main *m, s32 (*func)(M538Eff *), void *arg) {
    M538Eff *temp_r31;

    temp_r31 = m->eff.free;
    if (temp_r31 != NULL) {
        m->eff.free = temp_r31->next;
        temp_r31->func = func;
        temp_r31->arg = arg;
        temp_r31->next = m->eff.head;
        if ((M538Eff *) temp_r31->next != NULL) {
            temp_r31->next->prev = temp_r31;
        }
        m->eff.head = temp_r31;
    }
    return temp_r31;
}


void fn_1_6E50(M538Main *m) {
    M538Eff *temp_r29;
    M538Eff *var_r31;

    var_r31 = m->eff.head;
loop_11:
    if (var_r31 != NULL) {
        temp_r29 = var_r31->next;
        if ((((s32 (*)(M538Eff *)) var_r31->func) != NULL) && (var_r31->func(var_r31) != 0) && (var_r31 != NULL)) {
            if ((M538Eff *) var_r31->prev != NULL) {
                var_r31->prev->next = var_r31->next;
            } else {
                m->eff.head = var_r31->next;
            }
            if ((M538Eff *) var_r31->next != NULL) {
                var_r31->next->prev = var_r31->prev;
            }
            var_r31->prev = NULL;
            var_r31->next = m->eff.free;
            var_r31->func = NULL;
            m->eff.free = var_r31;
        }
        var_r31 = temp_r29;
        goto loop_11;
    }
}

s32 fn_1_6F24(M538Eff *eff) {
    f32 sp8;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f26;
    f32 var_f29;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r0;
    s32 var_r30;
    M538Fly *temp_r31;

    var_r30 = 0;
    temp_r31 = eff->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_f27 = temp_r31->pos.z;
        temp_f28 = temp_r31->pos.x;
        if (temp_f27 == 0.0f) {
            if (temp_f28 >= 0.0f) {
                var_f29 = 1.5707964f;
            } else {
                var_f29 = -1.5707964f;
            }
        } else {
            var_f29 = (f32) atan2((f64) temp_f28, (f64) temp_f27);
        }
        temp_r31->unk18 = (f32) ((f64) (180.0f * var_f29) / 3.141592653589793);
        temp_f30 = (temp_r31->pos.x * temp_r31->pos.x) + (temp_r31->pos.z * temp_r31->pos.z);
        var_f26 = sqrtf(temp_f30);
        temp_r31->unk1C = var_f26;
        temp_r31->timer = 0;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0xF0) {
            Hu3DModelAttrSet(temp_r31->model, 1U);
            var_r30 = 1;
        }
        temp_r31->unk18 = (f32) (temp_r31->unk18 - 6.1f);
        temp_r31->unk1C = (f32) (temp_r31->unk1C + 4.1f);
        temp_r31->pos.x = (f32) ((f64) temp_r31->unk1C * sin((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->pos.z = (f32) ((f64) temp_r31->unk1C * cos((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->rot.y = (f32) (temp_r31->rot.y + 4.0f);
loop_17:
        if (temp_r31->rot.y > 180.0f) {
            temp_r31->rot.y = (f32) (temp_r31->rot.y - 360.0f);
            goto loop_17;
        }
loop_20:
        if (temp_r31->rot.y < -180.0f) {
            temp_r31->rot.y = (f32) (temp_r31->rot.y + 360.0f);
            goto loop_20;
        }
        Hu3DModelPosSetV(temp_r31->model, (Vec *) temp_r31);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        break;
    }
    return var_r30;
}

void fn_1_72CC(M538Intro *intro) {
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 var_r31;
    s16 var_r31_2;
    s16 var_r31_3;
    s16 var_r31_4;
    M538Main *temp_r30;

    temp_r30 = lbl_1_bss_C->data;
    if ((s16) temp_r30->mdlCache[10] < 0) {
        temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0xA], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->mdlCache[10] = temp_r3;
        var_r31 = temp_r3;
    } else {
        var_r31 = Hu3DModelLink(temp_r30->mdlCache[10]);
    }
    intro->mdl[0] = var_r31;
    Hu3DModelAttrSet(var_r31, 1U);
    Hu3DModelAttrSet(var_r31, 0x40000001U);
    Hu3DModelLayerSet(var_r31, 7);
    Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
    if ((s16) temp_r30->mdlCache[19] < 0) {
        temp_r3_2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x13], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->mdlCache[19] = temp_r3_2;
        var_r31_2 = temp_r3_2;
    } else {
        var_r31_2 = Hu3DModelLink(temp_r30->mdlCache[19]);
    }
    intro->mdl[1] = var_r31_2;
    Hu3DModelAttrSet(var_r31_2, 1U);
    Hu3DModelAttrSet(var_r31_2, 0x40000002U);
    Hu3DModelLayerSet(var_r31_2, 2);
    Hu3DModelPosSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_2, 0.0f, 0.0f, 0.0f);
    if ((s16) temp_r30->mdlCache[20] < 0) {
        temp_r3_3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x14], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->mdlCache[20] = temp_r3_3;
        var_r31_3 = temp_r3_3;
    } else {
        var_r31_3 = Hu3DModelLink(temp_r30->mdlCache[20]);
    }
    intro->mdl[2] = var_r31_3;
    Hu3DModelAttrSet(var_r31_3, 1U);
    Hu3DModelAttrSet(var_r31_3, 0x40000002U);
    Hu3DModelLayerSet(var_r31_3, 2);
    Hu3DModelPosSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_3, 0.0f, 0.0f, 0.0f);
    if ((s16) temp_r30->mdlCache[23] < 0) {
        temp_r3_4 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x17], MEMORY_DEFAULT_NUM, HEAP_DATA));
        temp_r30->mdlCache[23] = temp_r3_4;
        var_r31_4 = temp_r3_4;
    } else {
        var_r31_4 = Hu3DModelLink(temp_r30->mdlCache[23]);
    }
    intro->mdl[3] = var_r31_4;
    Hu3DModelAttrSet(var_r31_4, 1U);
    Hu3DModelAttrSet(var_r31_4, 0x40000002U);
    Hu3DModelLayerSet(var_r31_4, 7);
    Hu3DModelPosSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(var_r31_4, 0.0f, 0.0f, 0.0f);
    intro->v.x = 0.0f;
    intro->v.z = 150.0f;
    intro->v.y = 0.0f;
    intro->state = 0;
}

void fn_1_765C(M538Intro *intro) {
    s16 temp_r0;

    temp_r0 = intro->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        intro->cnt = 0;
        intro->v.x = 30.0f;
        Hu3DModelAttrReset(intro->mdl[0], 1U);
        Hu3DModelAttrReset(intro->mdl[1], 1U);
        Hu3DModelAttrReset(intro->mdl[1], 0x40000002U);
        Hu3DModelAttrReset(intro->mdl[3], 1U);
        Hu3DModelAttrReset(intro->mdl[3], 0x40000002U);
        Hu3DMotionSpeedSet(intro->mdl[3], 0.6f);
        Hu3DModelHookSet(intro->mdl[1], lbl_1_data_418, intro->mdl[0]);
        intro->state += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(intro->mdl[1]) != 0) {
            Hu3DModelHookReset(intro->mdl[1]);
            Hu3DModelAttrSet(intro->mdl[0], 1U);
            Hu3DModelAttrSet(intro->mdl[1], 1U);
            intro->state += 1;
            return;
        }
        return;
    case 2:
        if (Hu3DMotionEndCheck(intro->mdl[3]) != 0) {
            Hu3DModelAttrSet(intro->mdl[3], 1U);
            intro->state += 1;
        }
        break;
    }
}

void fn_1_77A4(M538Intro *intro) {
    s16 temp_r0;

    temp_r0 = intro->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        intro->cnt = 0;
        intro->state += 1;
        intro->v.x = 30.0f;
        Hu3DModelAttrReset(intro->mdl[0], 1U);
        Hu3DModelAttrReset(intro->mdl[2], 1U);
        Hu3DModelAttrReset(intro->mdl[2], 0x40000002U);
        Hu3DModelHookSet(intro->mdl[2], lbl_1_data_418, intro->mdl[0]);
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(intro->mdl[2]) != 0) {
            Hu3DModelHookReset(intro->mdl[2]);
            Hu3DModelAttrSet(intro->mdl[0], 1U);
            Hu3DModelAttrSet(intro->mdl[2], 1U);
            intro->state += 1;
        }
        return;
    }
}

s32 fn_1_788C(M538Cam *cam) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->timer = 0;
        cam->state += 1;
        /* fallthrough */
    case 1:
        cam->timer += 1;
        if ((s16) cam->timer == 0xB4) {
            var_r30 = 1;
        }
        temp_f31 = (f32) sin((3.141592653589793 * (f64) ((90.0f * (f32) cam->timer) / 180.0f)) / 180.0);
        temp_f30 = 1.0f - temp_f31;
        cam->cur.az = (lbl_1_data_2E4.key[0].az * temp_f30) + (lbl_1_data_2E4.key[1].az * temp_f31);
        cam->cur.el = (lbl_1_data_2E4.key[0].el * temp_f30) + (lbl_1_data_2E4.key[1].el * temp_f31);
        cam->cur.dist = (lbl_1_data_2E4.key[0].dist * temp_f30) + (lbl_1_data_2E4.key[1].dist * temp_f31);
        cam->cur.tgt.x = (lbl_1_data_2E4.key[0].tgt.x * temp_f30) + (lbl_1_data_2E4.key[1].tgt.x * temp_f31);
        cam->cur.tgt.y = (lbl_1_data_2E4.key[0].tgt.y * temp_f30) + (lbl_1_data_2E4.key[1].tgt.y * temp_f31);
        cam->cur.tgt.z = (lbl_1_data_2E4.key[0].tgt.z * temp_f30) + (lbl_1_data_2E4.key[1].tgt.z * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_7AA0(M538Cam *cam) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;

    temp_r0 = cam->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->timer = 0;
        cam->state += 1;
        /* fallthrough */
    case 1:
        if ((s16) cam->timer < 0x708) {
            cam->timer += 1;
        }
        temp_f31 = (f32) sin((3.141592653589793 * (f64) ((90.0f * (f32) cam->timer) / 1800.0f)) / 180.0);
        temp_f30 = 1.0f - temp_f31;
        cam->cur.az = (lbl_1_data_2E4.key[1].az * temp_f30) + (lbl_1_data_2E4.key[2].az * temp_f31);
        cam->cur.el = (lbl_1_data_2E4.key[1].el * temp_f30) + (lbl_1_data_2E4.key[2].el * temp_f31);
        cam->cur.dist = (lbl_1_data_2E4.key[1].dist * temp_f30) + (lbl_1_data_2E4.key[2].dist * temp_f31);
        cam->cur.tgt.x = (lbl_1_data_2E4.key[1].tgt.x * temp_f30) + (lbl_1_data_2E4.key[2].tgt.x * temp_f31);
        cam->cur.tgt.y = (lbl_1_data_2E4.key[1].tgt.y * temp_f30) + (lbl_1_data_2E4.key[2].tgt.y * temp_f31);
        cam->cur.tgt.z = (lbl_1_data_2E4.key[1].tgt.z * temp_f30) + (lbl_1_data_2E4.key[2].tgt.z * temp_f31);
        break;
    }
    return 0;
}

s32 fn_1_7CB0(M538Cam *cam) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = cam->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        cam->timer = 0;
        cam->sv.az = cam->cur.az;
        cam->sv.el = cam->cur.el;
        cam->sv.dist = cam->cur.dist;
        cam->sv.tgt.x = cam->cur.tgt.x;
        cam->sv.tgt.y = cam->cur.tgt.y;
        cam->sv.tgt.z = cam->cur.tgt.z;
        cam->state += 1;
        /* fallthrough */
    case 1:
        cam->timer += 1;
        if ((s16) cam->timer == 0x96) {
            var_r30 = 1;
        }
        temp_f31 = (f32) sin((3.141592653589793 * (f64) ((90.0f * (f32) cam->timer) / 150.0f)) / 180.0);
        cam->cur.az = (cam->sv.az * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].az * temp_f31);
        cam->cur.el = (cam->sv.el * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].el * temp_f31);
        cam->cur.dist = (cam->sv.dist * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].dist * temp_f31);
        cam->cur.tgt.x = (cam->sv.tgt.x * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].tgt.x * temp_f31);
        cam->cur.tgt.y = (cam->sv.tgt.y * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].tgt.y * temp_f31);
        cam->cur.tgt.z = (cam->sv.tgt.z * (1.0f - temp_f31)) + (lbl_1_data_2E4.key[0].tgt.z * temp_f31);
        break;
    }
    return var_r30;
}

s32 fn_1_7F04(M538Ply *ply) {
    s32 temp_r0;

    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        ply->step += 1;
        break;
    case 2:
        CharMotionShiftSet(ply->charNo, ply->obj->motion[8], 0.0f, 5.0f, 0U);
        ply->step += 1;
        break;
    }
    return 0;
}

s32 fn_1_7FAC(M538Ply *ply) {
    Mtx sp20;
    Vec sp14;
    Vec sp8;
    M538Eff *temp_r30;
    M538Part *temp_r3;
    M538Part *temp_r3_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f28;
    f32 temp_f29;
    f32 var_f30;
    s32 temp_r0;
    M538Main *temp_r28;

    temp_r28 = lbl_1_bss_C->data;
    temp_r0 = ply->step;
    if ((u32) temp_r0 <= 7U) {
        switch (temp_r0) {
        case 0:
            temp_f28 = -ply->pos.z;
            temp_f29 = -ply->pos.x;
            if (temp_f28 == 0.0f) {
                if (temp_f29 >= 0.0f) {
                    var_f30 = 1.5707964f;
                } else {
                    var_f30 = -1.5707964f;
                }
            } else {
                var_f30 = (f32) atan2((f64) temp_f29, (f64) temp_f28);
            }
            ply->faceTarget = (f32) ((f64) (180.0f * var_f30) / 3.141592653589793);
            CharMotionShiftSet(ply->charNo, *ply->obj->motion, 0.0f, 5.0f, 0x40000001U);
            ply->step += 1;
            /* fallthrough */
        case 1:
            if (((s16) *ply->obj->motion == Hu3DMotionIDGet(ply->model)) && (Hu3DMotionShiftIDGet(ply->model) == -1)) {
                ply->step += 1;
            }
            break;
        case 2:
            CharMotionSet(ply->charNo, ply->obj->motion[1]);
            ply->step += 1;
            /* fallthrough */
        case 3:
            if (((ply->pos.x * ply->pos.x) + (ply->pos.z * ply->pos.z)) < 225.0f) {
                ply->step += 1;
            } else {
                ply->vel.x = (f32) (7.5 * sin((3.141592653589793 * (f64) ply->faceTarget) / 180.0));
                ply->vel.z = (f32) (7.5 * cos((3.141592653589793 * (f64) ply->faceTarget) / 180.0));
                temp_f1 = Hu3DMotionTimeGet(ply->model);
                if ((temp_f1 == 15.0f) || (temp_f1 == 30.0f)) {
                    temp_r3 = fn_1_8858(ply->poolA, fn_1_8CD8);
                    if (temp_r3 != NULL) {
                        temp_r3->pos.x = ply->pos.x;
                        temp_r3->pos.y = ply->pos.y;
                        temp_r3->pos.z = ply->pos.z;
                        temp_r3->state = 0;
                    }
                }
            }
            break;
        case 4:
            ply->faceTarget = 0.0f;
            ply->turnSpd = 5.0f;
            ply->step += 1;
            /* fallthrough */
        case 5:
            temp_f1_2 = Hu3DMotionTimeGet(ply->model);
            if ((temp_f1_2 == 15.0f) || (temp_f1_2 == 30.0f)) {
                temp_r3_2 = fn_1_8858(ply->poolA, fn_1_8CD8);
                if (temp_r3_2 != NULL) {
                    temp_r3_2->pos.x = ply->pos.x;
                    temp_r3_2->pos.y = ply->pos.y;
                    temp_r3_2->pos.z = ply->pos.z;
                    temp_r3_2->state = 0;
                }
            }
            if ((f32) fabs(ply->rot.y) < 1.0f) {
                ply->step += 1;
            }
            break;
        case 6:
            Hu3DModelObjMtxGet(ply->model, CharModelItemHookGet(ply->charNo, 8, 0), sp20);
            Hu3DMtxTransGet(sp20, &sp8);
            Hu3DMtxRotGet(sp20, &sp14);
            Hu3DModelHookReset(ply->model);
            ply->holdPos.x = sp8.x;
            ply->holdPos.y = sp8.y;
            ply->holdPos.z = sp8.z;
            ply->holdRot.x = sp14.x;
            ply->holdRot.y = sp14.y;
            ply->holdRot.z = sp14.z;
            Hu3DModelPosSetV(ply->itemMdl, &sp8);
            Hu3DModelRotSetV(ply->itemMdl, &sp14);
            temp_r30 = fn_1_6D98(temp_r28, fn_1_9024, &ply->fly);
            if (temp_r30 != NULL) {
                ply->fly.pos.x = ply->holdPos.x;
                ply->fly.pos.y = ply->holdPos.y;
                ply->fly.pos.z = ply->holdPos.z;
                ply->fly.rot.x = ply->holdRot.x;
                ply->fly.rot.y = ply->holdRot.y;
                ply->fly.rot.z = ply->holdRot.z;
                ply->fly.model = ply->itemMdl;
                ply->fly.state = 0;
            }
            CharMotionShiftSet(ply->charNo, ply->obj->motion[10], 0.0f, 5.0f, 0x40000001U);
            ply->step += 1;
            /* fallthrough */
        case 7:
            ply->func = fn_1_7F04;
            ply->step = 0;
            break;
        }
    }
    return 0;
}

s32 fn_1_8554(M538Ply *ply) {
    f32 sp8[4];
    M538Part *temp_r3;
    s32 temp_r0;

    sp8[0] = lbl_1_rodata_1CC[0];
    sp8[1] = lbl_1_rodata_1CC[1];
    sp8[2] = lbl_1_rodata_1CC[2];
    sp8[3] = lbl_1_rodata_1CC[3];
    temp_r0 = ply->step;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelShadowReset(*ply->obj->model);
        ply->timerA = 0;
        ply->step += 1;
        /* fallthrough */
    case 1:
        ply->timerA += 1;
        if ((s16) ply->timerA == (s16) ply->timerB) {
            ply->timerA = 0;
            ply->timerB = 0;
            ply->step += 1;
        }
        break;
    case 2:
        CharModelAttrReset(ply->charNo, 1U);
        CharMotionSet(ply->charNo, ply->obj->motion[9]);
        CharModelAttrSet(ply->charNo, 0x40000001U);
        CharModelAttrReset(ply->charNo, 0x40000002U);
        ply->pos.x = sp8[ply->player];
        ply->pos.y = 800.0f;
        ply->pos.z = 0.0f;
        ply->step += 1;
        /* fallthrough */
    case 3:
        if (ply->pos.y < 600.0f) {
            Hu3DModelShadowSet(*ply->obj->model);
            ply->step += 1;
        }
        /* fallthrough */
    case 4:
        ply->timerA += 1;
        ply->pos.y -= 1.3f * (f32) ply->timerA;
        if (ply->pos.y <= 10.0f) {
            temp_r3 = fn_1_8858(ply->poolA, fn_1_8CD8);
            if (temp_r3 != NULL) {
                temp_r3->pos.x = ply->pos.x;
                temp_r3->pos.y = ply->pos.y;
                temp_r3->pos.z = ply->pos.z;
                temp_r3->state = 0;
            }
            ply->pos.y = 0.0f;
            ply->step += 1;
        }
        break;
    case 5:
        ply->func = NULL;
        ply->step = 0;
        break;
    }
    return 0;
}

void fn_1_87E4(M538PartPool *pool, M538Part *nodes, s32 count) {
    M538Part *var_r4;
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
        var_r4->pool = pool;
        var_r31 += 1;
        var_r4++;
        goto loop_2;
    }
    var_r4->prev = NULL;
    var_r4->next = NULL;
    var_r4->func = NULL;
    var_r4->pool = pool;
}

M538Part *fn_1_8858(M538PartPool *pool, s32 (*func)(M538Part *)) {
    M538Part *temp_r31;

    temp_r31 = pool->free;
    if (temp_r31 != NULL) {
        pool->free = temp_r31->next;
        temp_r31->func = func;
        temp_r31->next = pool->head;
        if ((M538Part *) temp_r31->next != NULL) {
            temp_r31->next->prev = temp_r31;
        }
        pool->head = temp_r31;
    }
    return temp_r31;
}


void fn_1_8920(M538PartPool *pool) {
    M538Part *temp_r29;
    M538Part *var_r31;
    M538PartPool *temp_r30;

    var_r31 = pool->head;
loop_11:
    if (var_r31 != NULL) {
        temp_r29 = var_r31->next;
        if ((((s32 (*)(M538Part *)) var_r31->func) != NULL) && (var_r31->func(var_r31) != 0) && (var_r31 != NULL)) {
            temp_r30 = var_r31->pool;
            if ((M538Part *) var_r31->prev != NULL) {
                var_r31->prev->next = var_r31->next;
            } else {
                temp_r30->head = var_r31->next;
            }
            if ((M538Part *) var_r31->next != NULL) {
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

void fn_1_8A00(M538Main *m) {
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r28;
    s16 var_r30;
    s32 var_r29;

    var_r29 = 0;
loop_8:
    if (var_r29 < 0x10) {
        if ((s16) m->mdlCache[0x15] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x15], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->mdlCache[0x15] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(m->mdlCache[0x15]);
        }
        if ((s16) m->motCache[2] < 0) {
            temp_r3_2 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum(lbl_1_data_2D8[2], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->motCache[2] = temp_r3_2;
            var_r28 = temp_r3_2;
        } else {
            var_r28 = m->motCache[2];
        }
        Hu3DMotionSet(var_r30, var_r28);
        m->partsA[var_r29].model = var_r30;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 4);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r29 += 1;
        goto loop_8;
    }
}

void fn_1_8B6C(M538Main *m) {
    s16 temp_r3;
    s16 temp_r3_2;
    s16 var_r28;
    s16 var_r30;
    s32 var_r29;

    var_r29 = 0;
loop_8:
    if (var_r29 < 0x10) {
        if ((s16) m->mdlCache[0x12] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x12], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->mdlCache[0x12] = temp_r3;
            var_r30 = temp_r3;
        } else {
            var_r30 = Hu3DModelLink(m->mdlCache[0x12]);
        }
        if ((s16) m->motCache[1] < 0) {
            temp_r3_2 = Hu3DJointMotion(var_r30, HuDataSelHeapReadNum(lbl_1_data_2D8[1], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->motCache[1] = temp_r3_2;
            var_r28 = temp_r3_2;
        } else {
            var_r28 = m->motCache[1];
        }
        Hu3DMotionSet(var_r30, var_r28);
        m->partsB[var_r29].model = var_r30;
        Hu3DModelAttrSet(var_r30, 1U);
        Hu3DModelAttrSet(var_r30, 0x40000002U);
        Hu3DModelLayerSet(var_r30, 4);
        Hu3DModelPosSet(var_r30, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r30, 0.0f, 0.0f, 0.0f);
        var_r29 += 1;
        goto loop_8;
    }
}

s32 fn_1_8CD8(M538Part *part) {
    HSFMATERIAL *temp_r31;
    HSFMATERIAL *temp_r31_2;
    HSFMATERIAL *temp_r31_3;
    s16 temp_r0;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 var_r28;

    var_r28 = 0;
    temp_r0 = part->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(part->model, 1U);
        Hu3DModelAttrReset(part->model, 0x40000002U);
        Hu3DModelPosSetV(part->model, &part->pos);
        Hu3DMotionTimeSet(part->model, 0.0f);
        temp_r31 = Hu3DData[part->model].hsf->material;
        temp_r29 = fn_1_91D8(&part->pos) * 2;
        temp_r31->color[0] = ((const u8 *) lbl_1_rodata_1EC)[(temp_r29 * 3)];
        temp_r31->color[1] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29 * 3) + 1)];
        temp_r31->color[2] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29 * 3) + 2)];
        temp_r31_2 = temp_r31 + 1;
        temp_r31_2->color[0] = ((const u8 *) lbl_1_rodata_1EC)[(temp_r29 * 3)];
        temp_r31_2->color[1] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29 * 3) + 1)];
        temp_r31_2->color[2] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29 * 3) + 2)];
        temp_r31_3 = temp_r31_2 + 1;
        temp_r29_2 = temp_r29 + 1;
        temp_r31_3->color[0] = ((const u8 *) lbl_1_rodata_1EC)[(temp_r29_2 * 3)];
        temp_r31_3->color[1] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29_2 * 3) + 1)];
        temp_r31_3->color[2] = ((const u8 *) lbl_1_rodata_1EC)[((temp_r29_2 * 3) + 2)];
        part->state += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(part->model) != 0) {
            Hu3DModelAttrSet(part->model, 1U);
            Hu3DModelAttrSet(part->model, 0x40000002U);
            var_r28 = 1;
        }
        break;
    }
    return var_r28;
}

s32 fn_1_8F58(M538Part *part) {
    s16 temp_r0;
    s32 var_r30;

    var_r30 = 0;
    temp_r0 = part->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(part->model, 1U);
        Hu3DModelAttrReset(part->model, 0x40000002U);
        Hu3DModelPosSetV(part->model, &part->pos);
        Hu3DMotionTimeSet(part->model, 0.0f);
        part->state += 1;
        /* fallthrough */
    case 1:
        if (Hu3DMotionEndCheck(part->model) != 0) {
            Hu3DModelAttrSet(part->model, 1U);
            Hu3DModelAttrSet(part->model, 0x40000002U);
            var_r30 = 1;
        }
        break;
    }
    return var_r30;
}

s32 fn_1_9024(M538Eff *eff) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;
    M538Fly *temp_r31;

    var_r30 = 0;
    temp_r31 = eff->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->timer = 0;
        temp_r31->unk1C = (f32) temp_r31->rot.y;
        temp_r31->unk18 = (f32) temp_r31->rot.z;
        temp_r31->rot.x = 0.0f;
        temp_r31->rot.y = 0.0f;
        temp_r31->rot.z = 0.0f;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        temp_r31->rot.x = (f32) (temp_r31->rot.x - 40.0f);
        temp_r31->pos.y = (f32) (temp_r31->pos.y + 3.0f);
        temp_r31->pos.z = (f32) (temp_r31->pos.z - 6.0f);
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x3C) {
            var_r30 = 1;
        }
        temp_f31 = 1.0f - ((f32) temp_r31->timer / 60.0f);
        temp_r31->rot.y = (f32) (temp_r31->unk1C * temp_f31);
        temp_r31->rot.z = (f32) (temp_r31->unk18 * temp_f31);
        Hu3DModelScaleSet(temp_r31->model, temp_f31, temp_f31, temp_f31);
        Hu3DModelPosSetV(temp_r31->model, (Vec *) temp_r31);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        break;
    }
    return var_r30;
}

s32 fn_1_91D8(Vec *pos) {
    f32 temp_f25;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f30;
    f32 var_f31;
    s32 var_r30;

    temp_f30 = (pos->x * pos->x) + (pos->z * pos->z);
    if (temp_f30 < 62500.0f) {
        var_r30 = 0;
    } else if (temp_f30 < 250000.0f) {
        temp_f27 = pos->z;
        temp_f28 = pos->x;
        if (temp_f27 == 0.0f) {
            if (temp_f28 >= 0.0f) {
                var_f31 = 1.5707964f;
            } else {
                var_f31 = -1.5707964f;
            }
        } else {
            var_f31 = (f32) atan2((f64) temp_f28, (f64) temp_f27);
        }
        temp_f25 = (f32) fabs((f32) ((f64) (180.0f * var_f31) / 3.141592653589793));
        if ((temp_f25 >= 45.0f) && (temp_f25 < 135.0f)) {
            var_r30 = 2;
        } else {
            var_r30 = 1;
        }
    } else {
        var_r30 = 3;
    }
    return var_r30;
}

void fn_1_93C4(M538Main *m) {
    s16 temp_r3;
    s16 var_r31;
    s32 var_r29;

    var_r29 = 0;
loop_5:
    if (var_r29 < 0x40) {
        if ((s16) m->mdlCache[0x16] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[0x16], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->mdlCache[0x16] = temp_r3;
            var_r31 = temp_r3;
        } else {
            var_r31 = Hu3DModelLink(m->mdlCache[0x16]);
        }
        m->partsC[var_r29].model = var_r31;
        Hu3DModelAttrSet(var_r31, 1U);
        Hu3DModelAttrSet(var_r31, 0x40000002U);
        Hu3DModelLayerSet(var_r31, 4);
        Hu3DModelPosSet(var_r31, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r31, 0.0f, 0.0f, 0.0f);
        var_r29 += 1;
        goto loop_5;
    }
}

s32 fn_1_94DC(M538Part *part) {
    HSFMATERIAL *var_r30;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f31;
    f32 var_f30;
    s16 temp_r0;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;

    var_r26 = 0;
    temp_r0 = part->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        part->unk2C = 360.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        part->pos.x = (f32) ((f64) part->unk28 * sin((3.141592653589793 * (f64) part->unk2C) / 180.0));
        part->pos.y = 0.0f;
        part->pos.z = (f32) ((f64) part->unk28 * cos((3.141592653589793 * (f64) part->unk2C) / 180.0));
        part->rot.x = 50.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        part->rot.y = 360.0f + ((f32) frandmod(0x2711U) / 10000.0f);
        part->rot.z = 0.0f;
        Hu3DModelAttrReset(part->model, 1U);
        var_r30 = Hu3DData[part->model].hsf->material;
        temp_f28 = (part->pos.x * part->pos.x) + (part->pos.z * part->pos.z);
        if (temp_f28 < 62500.0f) {
            var_r28 = 0;
        } else if (temp_f28 < 250000.0f) {
            temp_f26 = part->pos.z;
            temp_f27 = part->pos.x;
            if (temp_f26 == 0.0f) {
                if (temp_f27 >= 0.0f) {
                    var_f30 = 1.5707964f;
                } else {
                    var_f30 = -1.5707964f;
                }
            } else {
                var_f30 = (f32) atan2((f64) temp_f27, (f64) temp_f26);
            }
            temp_f24 = (f32) fabs((f32) ((f64) (180.0f * var_f30) / 3.141592653589793));
            if ((temp_f24 >= 45.0f) && (temp_f24 < 135.0f)) {
                var_r28 = 2;
            } else {
                var_r28 = 1;
            }
        } else {
            var_r28 = 3;
        }
        var_r29 = var_r28 * 4;
        var_r27 = 0;
loop_19:
        if (var_r27 < 4) {
            var_r30->color[0] = ((const u8 *) lbl_1_rodata_21C)[(var_r29 * 3)];
            var_r30->color[1] = ((const u8 *) lbl_1_rodata_21C)[((var_r29 * 3) + 1)];
            var_r30->color[2] = ((const u8 *) lbl_1_rodata_21C)[((var_r29 * 3) + 2)];
            var_r27 += 1;
            var_r30++;
            var_r29 += 1;
            goto loop_19;
        }
        part->timer = 0;
        part->state += 1;
        /* fallthrough */
    case 1:
        part->timer += 1;
        if ((s16) part->timer == 0xB4) {
            Hu3DModelAttrSet(part->model, 1U);
            var_r26 = 1;
        }
        temp_f31 = 1.0f + ((f32) part->timer / 240.0f);
        part->unk2C -= 5.3f;
        part->unk28 += 1.1f;
        part->pos.x = (f32) ((f64) part->unk28 * sin((3.141592653589793 * (f64) part->unk2C) / 180.0));
        part->pos.y += 4.1f;
        part->pos.z = (f32) ((f64) part->unk28 * cos((3.141592653589793 * (f64) part->unk2C) / 180.0));
        part->rot.y -= 1.1f;
        Hu3DModelPosSetV(part->model, &part->pos);
        Hu3DModelRotSetV(part->model, &part->rot);
        Hu3DModelScaleSet(part->model, temp_f31, temp_f31, temp_f31);
        break;
    }
    return var_r26;
}

s32 fn_1_9C04(M538Part *part) {
    HSFMATERIAL *var_r30;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s32 var_r26;
    s32 var_r27;
    s32 var_r29;
    M538Main *temp_r28;

    var_r26 = 0;
    temp_r28 = lbl_1_bss_C->data;
    temp_r0 = part->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_f31 = (180.0f * ((f32) frandmod(0x2711U) / 10000.0f)) - 90.0f;
        temp_f30 = 500.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        part->pos.x = (f32) ((f64) temp_f30 * sin((3.141592653589793 * (f64) temp_f31) / 180.0));
        part->pos.y = 700.0f;
        part->pos.z = (f32) ((f64) temp_f30 * cos((3.141592653589793 * (f64) temp_f31) / 180.0));
        part->unk28 = 2.0f * (2.0f + ((f32) frandmod(0x2711U) / 10000.0f));
        part->unk2C = 0.0f;
        part->rot.x = 50.0f * ((f32) frandmod(0x2711U) / 10000.0f);
        part->rot.y = 360.0f + ((f32) frandmod(0x2711U) / 10000.0f);
        part->rot.z = 0.0f;
        Hu3DModelAttrReset(part->model, 1U);
        Hu3DModelScaleSet(part->model, 1.0f, 1.0f, 1.0f);
        var_r30 = Hu3DData[part->model].hsf->material;
        if (temp_r28->radius < 250.0f) {
            var_r29 = frandmod(4U) * 4;
        } else if (temp_r28->radius < 500.0f) {
            var_r29 = (frandmod(3U) + 1) * 4;
        } else {
            var_r29 = 0xC;
        }
        var_r27 = 0;
loop_11:
        if (var_r27 < 4) {
            var_r30->color[0] = ((const u8 *) lbl_1_rodata_258)[(var_r29 * 3)];
            var_r30->color[1] = ((const u8 *) lbl_1_rodata_258)[((var_r29 * 3) + 1)];
            var_r30->color[2] = ((const u8 *) lbl_1_rodata_258)[((var_r29 * 3) + 2)];
            var_r27 += 1;
            var_r30++;
            var_r29 += 1;
            goto loop_11;
        }
        part->timer = 0;
        part->state += 1;
        /* fallthrough */
    case 1:
        part->unk2C += 15.0f;
        if (part->unk2C > 180.0f) {
            part->unk2C -= 360.0f;
        }
        temp_f31_2 = (f32) sin((3.141592653589793 * (f64) part->unk2C) / 180.0);
        part->pos.y = (f32) ((f64) part->pos.y - ((f64) part->unk28 + (0.30000001192092896 * sin((3.141592653589793 * (f64) part->unk2C) / 180.0))));
        part->pos.x += 0.5f * part->unk28 * temp_f31_2;
        part->rot.y -= 2.0f * part->unk28;
        if (part->pos.y < 0.0f) {
            Hu3DModelAttrSet(part->model, 1U);
            var_r26 = 1;
        }
        Hu3DModelPosSetV(part->model, &part->pos);
        Hu3DModelRotSetV(part->model, &part->rot);
        break;
    }
    return var_r26;
}

void fn_1_A2A4(M538Main *m) {
    M538Part *temp_r31;

    m->fxCnt += 1;
    m->fxCnt %= 6;
    if ((s16) m->fxCnt == 0) {
        temp_r31 = m->partC.free;
        if (temp_r31 != NULL) {
            m->partC.free = temp_r31->next;
            temp_r31->func = fn_1_94DC;
            temp_r31->next = m->partC.head;
            if ((M538Part *) temp_r31->next != NULL) {
                temp_r31->next->prev = temp_r31;
            }
            m->partC.head = temp_r31;
        }
        if (temp_r31 != NULL) {
            temp_r31->unk28 = m->radius;
            temp_r31->state = 0;
        }
    }
}

void fn_1_A368(M538Main *m) {
    M538Part *temp_r31;

    m->fxCnt += 1;
    m->fxCnt %= 3;
    if ((s16) m->fxCnt == 0) {
        temp_r31 = m->partC.free;
        if (temp_r31 != NULL) {
            m->partC.free = temp_r31->next;
            temp_r31->func = fn_1_9C04;
            temp_r31->next = m->partC.head;
            if ((M538Part *) temp_r31->next != NULL) {
                temp_r31->next->prev = temp_r31;
            }
            m->partC.head = temp_r31;
        }
        if (temp_r31 != NULL) {
            temp_r31->state = 0;
        }
    }
}

s32 fn_1_A424(M538Spin *spin) {
    f32 temp_f31;
    f32 temp_f31_2;
    s16 temp_r0;
    s32 var_r28;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    M538Main *temp_r31;

    var_r28 = 0;
    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = spin->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        var_r29 = 0;
loop_9:
        if (var_r29 < 0x18) {
            Hu3DModelAttrReset((s16) (temp_r31->mdlCache[17] + var_r29), 0x40000002U);
            Hu3DModelAttrSet((s16) (temp_r31->mdlCache[17] + var_r29), 0x40000001U);
            var_r29 += 1;
            goto loop_9;
        }
        Hu3DModelAttrReset(temp_r31->mdlCache[11], 0x40000002U);
        Hu3DModelAttrSet(temp_r31->mdlCache[11], 0x40000001U);
        Hu3DModelAttrReset(temp_r31->mdlCache[12], 0x40000002U);
        Hu3DModelAttrSet(temp_r31->mdlCache[12], 0x40000001U);
        Hu3DModelAttrReset(temp_r31->mdlCache[24], 0x40000002U);
        Hu3DModelAttrSet(temp_r31->mdlCache[24], 0x40000001U);
        spin->timer = 0;
        spin->state += 1;
        /* fallthrough */
    case 1:
        spin->timer += 1;
        temp_f31 = (1.5f * (f32) spin->timer) / 120.0f;
        var_r29_2 = 0;
loop_13:
        if (var_r29_2 < 0x18) {
            Hu3DMotionSpeedSet((s16) (temp_r31->mdlCache[17] + var_r29_2), temp_f31);
            var_r29_2 += 1;
            goto loop_13;
        }
        Hu3DMotionSpeedSet(temp_r31->mdlCache[11], temp_f31);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[12], temp_f31);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[24], temp_f31);
        if ((s16) spin->timer == 0x78) {
            var_r28 = 1;
        }
        break;
    case 2:
        spin->timer = 0;
        spin->state += 1;
        /* fallthrough */
    case 3:
        spin->timer += 1;
        temp_f31_2 = 1.5f * (1.0f - ((f32) spin->timer / 180.0f));
        var_r29_3 = 0;
loop_19:
        if (var_r29_3 < 0x18) {
            Hu3DMotionSpeedSet((s16) (temp_r31->mdlCache[17] + var_r29_3), temp_f31_2);
            var_r29_3 += 1;
            goto loop_19;
        }
        Hu3DMotionSpeedSet(temp_r31->mdlCache[11], temp_f31_2);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[12], temp_f31_2);
        Hu3DMotionSpeedSet(temp_r31->mdlCache[24], temp_f31_2);
        if ((s16) spin->timer == 0xB4) {
            var_r28 = 1;
        }
        break;
    }
    return var_r28;
}

void fn_1_A6F8(M538Main *m) {
    s32 sp8[4];
    s16 temp_r3;
    s16 var_r29;
    s32 var_r30;

    sp8[0] = lbl_1_rodata_2A4[0];
    sp8[1] = lbl_1_rodata_2A4[1];
    sp8[2] = lbl_1_rodata_2A4[2];
    sp8[3] = lbl_1_rodata_2A4[3];
    m->rocks.state = 0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 4) {
        if ((s16) m->mdlCache[sp8[var_r30]] < 0) {
            temp_r3 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_264[sp8[var_r30]], MEMORY_DEFAULT_NUM, HEAP_DATA));
            m->mdlCache[sp8[var_r30]] = temp_r3;
            var_r29 = temp_r3;
        } else {
            var_r29 = Hu3DModelLink(m->mdlCache[sp8[var_r30]]);
        }
        Hu3DModelAttrSet(var_r29, 1U);
        Hu3DModelAttrSet(var_r29, 0x40000002U);
        Hu3DModelLayerSet(var_r29, 2);
        Hu3DModelPosSet(var_r29, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(var_r29, 0.0f, 0.0f, 0.0f);
        m->rocks.fly[var_r30].model = var_r29;
        m->rocks.fly[var_r30].state = 0;
        var_r30 += 1;
        goto loop_5;
    }
}

void fn_1_A8A0(M538Rocks *rocks) {
    M538Eff *temp_r26;
    M538Eff *temp_r27;
    M538Eff *temp_r28;
    M538Eff *temp_r29;
    s16 temp_r0;
    M538Main *temp_r31;

    temp_r31 = lbl_1_bss_C->data;
    temp_r0 = rocks->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        rocks->timer = 0;
        rocks->state += 1;
        /* fallthrough */
    case 1:
        rocks->timer += 1;
        if ((s16) rocks->timer == 0x168) {
            temp_r29 = fn_1_6D98(temp_r31, fn_1_AB54, rocks->fly);
            if (temp_r29 != NULL) {
                rocks->fly[0].unk1C = temp_r31->radius;
                rocks->fly[0].state = 0;
            }
            rocks->state += 1;
            return;
        }
        return;
    case 2:
        rocks->timer += 1;
        if ((s16) rocks->timer == 0x2D0) {
            temp_r28 = fn_1_6D98(temp_r31, fn_1_AB54, &rocks->fly[1]);
            if (temp_r28 != NULL) {
                rocks->fly[1].unk1C = temp_r31->radius;
                rocks->fly[1].state = 0;
            }
            rocks->state += 1;
            return;
        }
        break;
    case 3:
        rocks->timer += 1;
        if ((s16) rocks->timer == 0x438) {
            temp_r27 = fn_1_6D98(temp_r31, fn_1_AB54, &rocks->fly[2]);
            if (temp_r27 != NULL) {
                rocks->fly[2].unk1C = temp_r31->radius;
                rocks->fly[2].state = 0;
            }
            rocks->state += 1;
            return;
        }
        break;
    case 4:
        rocks->timer += 1;
        if ((s16) rocks->timer == 0x5A0) {
            temp_r26 = fn_1_6D98(temp_r31, fn_1_AB54, &rocks->fly[3]);
            if (temp_r26 != NULL) {
                rocks->fly[3].unk1C = 250.0f + temp_r31->radius;
                rocks->fly[3].state = 0;
            }
            rocks->state += 1;
        }
        break;
    }
}

s32 fn_1_AB54(M538Eff *eff) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;
    M538Fly *temp_r31;

    var_r30 = 0;
    temp_r31 = eff->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrReset(temp_r31->model, 1U);
        temp_r31->timer = 0;
        temp_r31->rot.x = 0.0f;
        temp_r31->rot.y = 0.0f;
        temp_r31->rot.z = 0.0f;
        temp_r31->unk18 = (f32) (360.0f * ((f32) frandmod(0x2711U) / 10000.0f));
        temp_r31->pos.x = (f32) ((f64) temp_r31->unk1C * sin((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->pos.y = 300.0f;
        temp_r31->pos.z = (f32) ((f64) temp_r31->unk1C * cos((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x3C) {
            temp_r31->state = (s16) (temp_r31->state + 1);
        }
        temp_r31->unk18 = (f32) (temp_r31->unk18 - 4.9f);
        temp_r31->rot.x = (f32) (temp_r31->rot.x + 5.0f);
        temp_r31->rot.y = (f32) (temp_r31->rot.y + 5.0f);
        temp_f30 = 1.0f - ((f32) temp_r31->timer / 60.0f);
        temp_f31 = temp_r31->unk1C + (temp_r31->unk1C * (0.5f * temp_f30 * temp_f30));
        temp_r31->pos.x = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->pos.z = (f32) ((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        Hu3DModelPosSetV(temp_r31->model, (Vec *) temp_r31);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        break;
    case 2:
        temp_r31->timer = 0;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 3:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x3C) {
            temp_r31->state = (s16) (temp_r31->state + 1);
        }
        temp_r31->unk18 = (f32) (temp_r31->unk18 - 4.9f);
        temp_r31->rot.x = (f32) (temp_r31->rot.x + 5.0f);
        temp_r31->rot.y = (f32) (temp_r31->rot.y + 5.0f);
        temp_r31->pos.x = (f32) ((f64) temp_r31->unk1C * sin((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        temp_r31->pos.z = (f32) ((f64) temp_r31->unk1C * cos((3.141592653589793 * (f64) temp_r31->unk18) / 180.0));
        Hu3DModelPosSetV(temp_r31->model, (Vec *) temp_r31);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        break;
    case 4:
        temp_r31->unk18 = (f32) (temp_r31->unk18 - 90.0f);
        temp_r31->unk1C = (f32) ((3.141592653589793 * (f64) (2.0f * temp_r31->unk1C)) / 72.0);
        temp_r31->timer = 0;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 5:
        temp_r31->pos.x = (f32) ((f64) temp_r31->pos.x + ((f64) temp_r31->unk1C * sin((3.141592653589793 * (f64) temp_r31->unk18) / 180.0)));
        temp_r31->pos.z = (f32) ((f64) temp_r31->pos.z + ((f64) temp_r31->unk1C * cos((3.141592653589793 * (f64) temp_r31->unk18) / 180.0)));
        temp_r31->rot.x = (f32) (temp_r31->rot.x + 5.0f);
        temp_r31->rot.y = (f32) (temp_r31->rot.y + 5.0f);
        Hu3DModelPosSetV(temp_r31->model, (Vec *) temp_r31);
        Hu3DModelRotSetV(temp_r31->model, &temp_r31->rot);
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x3C) {
            Hu3DModelAttrSet(temp_r31->model, 1U);
            var_r30 = 1;
        }
        break;
    }
    return var_r30;
}

s32 fn_1_B0D0(M538Eff *eff) {
    f32 temp_f31;
    s16 temp_r0;
    s32 var_r30;
    M538Wave *temp_r31;

    var_r30 = 0;
    temp_r31 = eff->arg;
    temp_r0 = temp_r31->state;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r31->timer = 0;
        temp_r31->state = (s16) (temp_r31->state + 1);
        /* fallthrough */
    case 1:
        temp_r31->timer = (s16) (temp_r31->timer + 1);
        if ((s16) temp_r31->timer == 0x3C) {
            var_r30 = 1;
        }
        temp_f31 = 1.0f + ((3.0f * (f32) temp_r31->timer) / 60.0f);
        Hu3DModelScaleSet(temp_r31->model, temp_f31, 1.0f, temp_f31);
        break;
    }
    return var_r30;
}
