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

extern s32 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_8;
extern OMOBJ *lbl_1_bss_C;
extern HUPROCESS *lbl_1_bss_10;
extern MGSEQ_PARAM lbl_1_data_0;
extern s32 lbl_1_data_28[13][11];
extern s32 lbl_1_data_264[0x1D];
extern s32 lbl_1_data_2D8[3];
extern M538CamTbl lbl_1_data_2E4;
extern s32 lbl_1_data_394[13];
extern s32 lbl_1_data_3C8[13];
extern char lbl_1_data_418[12];
extern const u16 lbl_1_rodata_10[4];
extern const Vec lbl_1_rodata_60;
extern const Vec lbl_1_rodata_6C;
extern const Vec lbl_1_rodata_78;
extern const s16 lbl_1_rodata_B8[4];
extern const s16 lbl_1_rodata_C0[4];
extern const s16 lbl_1_rodata_C8[4];
extern const s16 lbl_1_rodata_D0[4];
extern const f32 lbl_1_rodata_EC[4];
extern const s32 lbl_1_rodata_FC[4];
extern const f32 lbl_1_rodata_158[4];
extern const f32 lbl_1_rodata_168[4];
extern const s16 lbl_1_rodata_190[4];
extern const M538RingFunc lbl_1_rodata_1A0[3];
extern const f32 lbl_1_rodata_1CC[4];
extern const u8 lbl_1_rodata_1EC[8][3];
extern const u8 lbl_1_rodata_21C[16][3];
extern const u8 lbl_1_rodata_258[16][3];
extern const s32 lbl_1_rodata_2A4[4];

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
