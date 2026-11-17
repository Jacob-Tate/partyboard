// MP5 m519 (Mario Mechs), generated from its m2c draft by tools/mp5/ports/m519dll.sh (do not hand-edit lightly).
#include "REL/mp5compat.h"
// m2c context for m519dll (Mario Mechs; tools/mp5/decomp.py m519dll --types tools/mp5/types/m519dll.h)
// 1 vs 3: the solo player (group 0) pilots the big mech (type 0), the team of three pilots small mechs (type 1).
// Everything is a malloc'd work struct with its own state process (state at +0, previous state at +2). Offsets are
// GameCube's; pointers are 8 bytes here, so allocate with sizeof (see m519dll_fix.py).
// var ObjectSetup temp_r3: HUPROCESS *
// var fn_1_297C temp_r3: M519Mech
// var fn_1_A204 temp_r3: M519Player
// var fn_1_AB40 temp_r3: M519Bullet
// var fn_1_C058 temp_r3: M519Bld
// var fn_1_D0BC temp_r3: M519Hud
// var fn_1_2298 temp_r3: M519Stage
// var fn_1_CC44 temp_r31: M519Part
// var fn_1_CDF4 arg0: M519Part

typedef struct M519Hdr { // the start of every work struct
    s16 state;
    s16 prevState;
} M519Hdr;

typedef struct M519Vec2 {
    f32 x, y;
} M519Vec2;

typedef struct M519Mech { // 0xFC (type 0: big mech of the solo player, type 1: small mech of a team member)
    s16 state; // 0 (0 idle, 1 fight, 2 destroyed, 3 fade out, 4 respawn)
    s16 prevState; // 2
    s16 type; // 4
    s16 idx; // 6
    s16 player; // 8 index into the player table
    s16 mdl[9]; // 0xA
    s16 mot[7]; // 0x1C
    s16 motState; // 0x2A
    s16 motPrev; // 0x2C
    s16 shootWait; // 0x2E
    s16 hp; // 0x30
    s16 hpShow; // 0x32
    s16 hpMax; // 0x34
    s16 chargeA; // 0x36
    s16 chargeB; // 0x38
    s16 dmgStage; // 0x3A
    s16 lastHitter; // 0x3C
    s16 aiSub; // 0x3E
    s16 pad40[2]; // 0x40
    s16 inputOn; // 0x44
    s16 pad46; // 0x46
    s16 turning; // 0x48
    s16 pad4A; // 0x4A
    s16 camFollow; // 0x4C
    s16 pad4E; // 0x4E
    f32 speed; // 0x50
    f32 turn; // 0x54
    f32 tgtSpeed; // 0x58
    f32 tgtTurn; // 0x5C
    f32 turnScale; // 0x60
    f32 speedScale; // 0x64
    f32 push; // 0x68
    f32 pushDir; // 0x6C
    f32 radius; // 0x70
    f32 aim; // 0x74
    f32 pad78[3]; // 0x78
    Vec pos; // 0x84
    Vec rot; // 0x90
    Vec prevPos; // 0x9C
    Vec prevRot; // 0xA8
    struct M519Part *part[2]; // 0xB4
    HUPROCESS *proc; // 0xBC
    s16 hitSame; // 0xC0
    s16 pad_C2;
    s16 aiFire; // 0xC4
    s16 pad_C6;
    s16 btnDown; // 0xC8
    s16 btn; // 0xCA
    s16 stickX; // 0xCC
    s16 stickY; // 0xCE
    s16 trigL; // 0xD0
    s16 trigR; // 0xD2
    s16 aiHasTgt; // 0xD4
    s16 pad_D6;
    f32 aiX; // 0xD8
    f32 aiY; // 0xDC
    f32 aiZ; // 0xE0
    s16 aiTarget; // 0xE4
    s16 fireCool; // 0xE6
    s16 aiTimer; // 0xE8
    s16 aiTimer2; // 0xEA
    s16 aiPush; // 0xEC
    s16 aiMode; // 0xEE
    s32 sfx; // 0xF0
    s32 pad_F4;
    f32 stepAcc; // 0xF8
} M519Mech;

typedef struct M519Player { // 0x40
    s16 state; // 0
    s16 prevState; // 2
    s16 side; // 4
    s16 idx; // 6
    s16 mech; // 8
    s16 charNo; // 0xA
    s16 isCom; // 0xC
    s16 pad_E;
    s16 dif; // 0x10
    s16 pad; // 0x12
    union { s16 mdl[2]; struct { s16 pilot, cockpit; }; }; // 0x14
    s16 mot[6]; // 0x18
    Vec pos; // 0x24
    Vec rot; // 0x30
    HUPROCESS *proc; // 0x3C
} M519Player;

typedef struct M519Bullet { // 0x50
    s16 state; // 0
    s16 prevState; // 2
    s16 active; // 4
    s16 pad_6;
    s32 stick; // 8
    s16 id; // 0xC
    s16 kind; // 0xE
    s16 dmg; // 0x10
    s16 pushPow; // 0x12
    s16 mdl[2]; // 0x14
    s16 owner; // 0x18
    s16 pad_1A;
    f32 speed; // 0x1C
    f32 curSpeed; // 0x20
    Vec pos; // 0x24
    Vec rot; // 0x30
    f32 radius0; // 0x3C
    f32 radius1; // 0x40
    f32 radius; // 0x44
    s16 life; // 0x48
    s16 ramp; // 0x4A
    HUPROCESS *proc; // 0x4C
} M519Bullet;

typedef struct M519Bld { // 0x38: a building
    s16 state; // 0
    s16 prevState; // 2
    s16 type; // 4
    s16 mdl[3]; // 6
    s16 hp; // 0xC
    s16 lastHit; // 0xE
    s16 lastShooter; // 0x10
    s16 pad_12;
    Vec pos; // 0x14
    Vec rot; // 0x20
    f32 radius; // 0x2C
    s32 respawn; // 0x30
    HUPROCESS *proc; // 0x34
} M519Bld;

typedef struct M519Stage { // 0x48
    s16 state; // 0
    s16 prevState; // 2
    s16 mdl[7]; // 4
    s16 pad_12;
    M519Bld *bld[12]; // 0x14
    HUPROCESS *proc; // 0x44
} M519Stage;

typedef struct M519Hud { // 0xCC
    s16 state; // 0
    s16 prevState; // 2
    s16 type; // 4
    s16 pad_6;
    s16 mech; // 8
    s16 spr[0x12]; // 0xA
    f32 x; // 0x30
    f32 y; // 0x34
    M519Vec2 ofs[0x12]; // 0x38
    HUPROCESS *proc; // 0xC8
} M519Hud;

typedef struct M519Part { // 0x14: a trail of fire particles
    s16 model; // 0
    s16 pad_2;
    Vec pos; // 4
    ANIMDATA *anim; // 0x10
} M519Part;

typedef struct M519Light { // 0x1C
    Vec pos;
    Vec aim;
    u8 color[4];
} M519Light;

typedef struct M519View { // 0x38
    f32 unk0, unk4, unk8, unkC; // perspective: fov, near, far, aspect
    f32 unk10, unk14, unk18, unk1C, unk20, unk24; // viewport
    f32 unk28, unk2C, unk30, unk34; // scissor
} M519View;

typedef struct M519HudInit { // 0xC
    s16 type;
    f32 x;
    f32 y;
} M519HudInit;

typedef struct M519BldInit { // 0x1C
    s16 type; // 2: none
    Vec pos;
    Vec rot;
} M519BldInit;

typedef struct M519BldSet { // 0x150: the buildings of a stage
    M519BldInit bld[12];
} M519BldSet;

typedef struct M519MechInit { // 0x10
    f32 speedScale;
    f32 turnScale;
    f32 radius;
    s16 hp;
} M519MechInit;

typedef struct M519MotShift { // 0xC
    f32 start;
    f32 time;
    u32 attr;
} M519MotShift;

typedef struct M519MotSet { // 0x54
    M519MotShift mot[7];
} M519MotSet;

typedef struct M519BulletInit { // 0x18
    f32 speed;
    f32 radius0;
    f32 radius1;
    s16 life;
    s16 ramp;
    s16 dmg;
    s16 pushPow;
    s32 stick;
} M519BulletInit;

typedef struct M519HudOfs { // 0x90
    M519Vec2 ofs[0x12];
} M519HudOfs;

typedef struct M519Ints6 {
    s32 n[6];
} M519Ints6;
typedef struct M519Ints2 {
    s32 n[2];
} M519Ints2;
typedef struct M519Ints7 {
    s32 n[7];
} M519Ints7;
typedef struct M519Ints9 {
    s32 n[9];
} M519Ints9;
typedef struct M519Ints18 {
    s32 n[18];
} M519Ints18;


void ObjectSetup(void);
void fn_1_28C(s16 mode, s16 frameNo);
void fn_1_9F4(s16 mode, s16 frameNo);
void fn_1_143C(s16 mode, s16 frameNo);
void fn_1_14E8(s16 mode, s16 frameNo);
void fn_1_1628(s16 mode, s16 frameNo);
void fn_1_19C4(s16 mode, s16 frameNo);
void fn_1_1FC0(s16 mode, s16 frameNo);
void fn_1_D64(void);
M519Stage *fn_1_2298(void);
void fn_1_2654(void);
void fn_1_26A0(void);
void fn_1_2730(M519Stage *s);
void fn_1_2790(M519Stage *s);
void fn_1_27FC(M519Stage *s);
void fn_1_2900(M519Stage *s);
M519Mech *fn_1_297C(s16 type, s16 idx);
void fn_1_2F54(void);
void fn_1_2FA0(M519Mech *m, s16 motState, f32 speed);
void fn_1_3138(M519Mech *m, Vec *pos);
void fn_1_3290(M519Mech *m, Vec *rot);
void fn_1_3518(M519Mech *m, M519Player *p);
void fn_1_35B0(M519Mech *m);
void fn_1_35BC(M519Mech *m);
void fn_1_3658(M519Mech *m);
void fn_1_3664(M519Mech *m);
void fn_1_4D40(M519Mech *m);
void fn_1_4E18(M519Mech *m);
void fn_1_5EDC(M519Mech *m);
void fn_1_68E4(M519Mech *m);
void fn_1_69BC(M519Mech *m);
void fn_1_7998(M519Mech *m);
void fn_1_817C(M519Mech *m);
void fn_1_8188(M519Mech *m);
void fn_1_82E4(M519Mech *m);
void fn_1_8450(M519Mech *m);
void fn_1_8D40(M519Mech *m);
void fn_1_8E40(M519Mech *m);
void fn_1_95B0(M519Mech *m);
void fn_1_9700(M519Mech *m);
void fn_1_98A0(M519Mech *m);
void fn_1_98AC(M519Mech *m);
void fn_1_9B9C(M519Mech *m);
void fn_1_9BA8(M519Mech *m);
void fn_1_A068(M519Mech *m);
s32 fn_1_A1D4(M519Mech *m);
M519Player *fn_1_A204(s16 side, s16 idx);
void fn_1_A40C(void);
void fn_1_A44C(M519Player *p, Vec *pos);
void fn_1_A4EC(M519Player *p, Vec *rot);
void fn_1_A598(M519Player *p);
void fn_1_A628(M519Player *p);
void fn_1_A634(M519Player *p);
void fn_1_A6B8(M519Player *p);
void fn_1_A6C4(M519Player *p);
void fn_1_A770(M519Player *p);
void fn_1_A77C(M519Player *p);
void fn_1_A828(M519Player *p);
void fn_1_A834(M519Player *p);
s32 fn_1_A9F0(s16 kind, Vec *pos, Vec *rot, s16 owner);
M519Bullet *fn_1_AB40(s16 kind);
void fn_1_ADE4(void);
void fn_1_AE24(M519Bullet *b, Vec *pos);
void fn_1_AEC4(M519Bullet *b, Vec *rot);
void fn_1_B004(M519Bullet *b);
void fn_1_B0B0(M519Bullet *b);
void fn_1_B0BC(M519Bullet *b);
s32 fn_1_B70C(M519Bullet *b);
s32 fn_1_B9BC(M519Bullet *b);
s32 fn_1_BAC8(M519Bullet *b);
s32 fn_1_BECC(M519Bullet *b);
M519Bld *fn_1_C058(s16 type);
void fn_1_C248(void);
void fn_1_C288(M519Bld *b, Vec *pos);
void fn_1_C328(M519Bld *b, Vec *rot);
void fn_1_C3C8(M519Bld *b);
void fn_1_C3D4(M519Bld *b);
void fn_1_C470(M519Bld *b);
void fn_1_C544(M519Bld *b);
void fn_1_C570(M519Bld *b);
void fn_1_C788(M519Bld *b, s32 respawn);
void fn_1_C798(M519Bld *b);
void fn_1_CBEC(M519Bld *b);
M519Part *fn_1_CC44(void);
void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CD54(M519Part *p, Vec *pos);
void fn_1_CDF0(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CDF4(M519Part *p);
void fn_1_CEE4(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
s32 fn_1_CFE8(M519Part *p);
M519Hud *fn_1_D0BC(s16 type, s16 mech);
void fn_1_D610(void);
void fn_1_D65C(M519Hud *h, Vec *pos);
void fn_1_D720(M519Hud *h);
void fn_1_D7B0(M519Hud *h);
void fn_1_D7BC(M519Hud *h);
void fn_1_DD08(M519Hud *h);
void fn_1_E168(M519Hud *h);
void fn_1_E174(M519Hud *h);
void fn_1_E298(M519Hud *h);
void fn_1_E2D4(M519Hud *h);
void fn_1_E714(M519Hud *h);
void fn_1_EA10(M519Hud *h);
void fn_1_ED78(M519Hud *h);
void fn_1_EE8C(M519Hud *h);
void fn_1_F104(M519Hud *h);
void fn_1_F2DC(M519Hud *h);
void fn_1_F2E8(M519Hud *h);
void fn_1_F568(M519Hud *h);
void fn_1_F7F0(M519Hud *h);
s32 fn_1_F860(Vec *a, Vec *b, s32 push);
s32 fn_1_FA6C(Vec *a, Vec *b, s32 push);
f32 fn_1_FC78(f32 cur, f32 target, f32 rate);
void fn_1_FD7C(s16 player, s16 type, s16 time);
s16 fn_1_FE20(u16 camBits, Vec *pos);
s16 fn_1_10244(u16 camBits, Vec *pos);
void ObjectSetup(void);
void fn_1_28C(s16 mode, s16 frameNo);
void fn_1_9F4(s16 mode, s16 frameNo);
void fn_1_D64(void);
void fn_1_143C(s16 mode, s16 frameNo);
void fn_1_14E8(s16 mode, s16 frameNo);
void fn_1_1628(s16 mode, s16 frameNo);
void fn_1_19C4(s16 mode, s16 frameNo);
void fn_1_1FC0(s16 mode, s16 frameNo);
M519Stage *fn_1_2298(void);
void fn_1_2654(void);
void fn_1_26A0(void);
void fn_1_2730(M519Stage *s);
void fn_1_2790(M519Stage *s);
void fn_1_27FC(M519Stage *s);
void fn_1_2900(M519Stage *s);
M519Mech *fn_1_297C(s16 type, s16 idx);
void fn_1_2F54(void);
void fn_1_2FA0(M519Mech *m, s16 motState, f32 speed);
void fn_1_3138(M519Mech *m, Vec *pos);
void fn_1_3290(M519Mech *m, Vec *rot);
void fn_1_3518(M519Mech *m, M519Player *p);
void fn_1_35B0(M519Mech *m);
void fn_1_35BC(M519Mech *m);
void fn_1_3658(M519Mech *m);
void fn_1_3664(M519Mech *m);
void fn_1_4D40(M519Mech *m);
void fn_1_4E18(M519Mech *m);
void fn_1_5EDC(M519Mech *m);
void fn_1_68E4(M519Mech *m);
void fn_1_69BC(M519Mech *m);
void fn_1_7998(M519Mech *m);
void fn_1_817C(M519Mech *m);
void fn_1_8188(M519Mech *m);
void fn_1_82E4(M519Mech *m);
void fn_1_8450(M519Mech *m);
void fn_1_8D40(M519Mech *m);
void fn_1_8E40(M519Mech *m);
void fn_1_95B0(M519Mech *m);
void fn_1_9700(M519Mech *m);
void fn_1_98A0(M519Mech *m);
void fn_1_98AC(M519Mech *m);
void fn_1_9B9C(M519Mech *m);
void fn_1_9BA8(M519Mech *m);
void fn_1_A068(M519Mech *m);
s32 fn_1_A1D4(M519Mech *m);
M519Player *fn_1_A204(s16 side, s16 idx);
void fn_1_A40C(void);
void fn_1_A44C(M519Player *p, Vec *pos);
void fn_1_A4EC(M519Player *p, Vec *rot);
void fn_1_A598(M519Player *p);
void fn_1_A628(M519Player *p);
void fn_1_A634(M519Player *p);
void fn_1_A6B8(M519Player *p);
void fn_1_A6C4(M519Player *p);
void fn_1_A770(M519Player *p);
void fn_1_A77C(M519Player *p);
void fn_1_A828(M519Player *p);
void fn_1_A834(M519Player *p);
s32 fn_1_A9F0(s16 kind, Vec *pos, Vec *rot, s16 owner);
M519Bullet *fn_1_AB40(s16 kind);
void fn_1_ADE4(void);
void fn_1_AE24(M519Bullet *b, Vec *pos);
void fn_1_AEC4(M519Bullet *b, Vec *rot);
void fn_1_B004(M519Bullet *b);
void fn_1_B0B0(M519Bullet *b);
void fn_1_B0BC(M519Bullet *b);
s32 fn_1_B70C(M519Bullet *b);
s32 fn_1_B9BC(M519Bullet *b);
s32 fn_1_BAC8(M519Bullet *b);
s32 fn_1_BECC(M519Bullet *b);
M519Bld *fn_1_C058(s16 type);
void fn_1_C248(void);
void fn_1_C288(M519Bld *b, Vec *pos);
void fn_1_C328(M519Bld *b, Vec *rot);
void fn_1_C3C8(M519Bld *b);
void fn_1_C3D4(M519Bld *b);
void fn_1_C470(M519Bld *b);
void fn_1_C544(M519Bld *b);
void fn_1_C570(M519Bld *b);
void fn_1_C788(M519Bld *b, s32 respawn);
void fn_1_C798(M519Bld *b);
void fn_1_CBEC(M519Bld *b);
M519Part *fn_1_CC44(void);
void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CD54(M519Part *p, Vec *pos);
void fn_1_CDF0(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CDF4(M519Part *p);
void fn_1_CEE4(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
s32 fn_1_CFE8(M519Part *p);
M519Hud *fn_1_D0BC(s16 type, s16 mech);
void fn_1_D610(void);
void fn_1_D65C(M519Hud *h, Vec *pos);
void fn_1_D720(M519Hud *h);
void fn_1_D7B0(M519Hud *h);
void fn_1_D7BC(M519Hud *h);
void fn_1_DD08(M519Hud *h);
void fn_1_E168(M519Hud *h);
void fn_1_E174(M519Hud *h);
void fn_1_E298(M519Hud *h);
void fn_1_E2D4(M519Hud *h);
void fn_1_E714(M519Hud *h);
void fn_1_EA10(M519Hud *h);
void fn_1_ED78(M519Hud *h);
void fn_1_EE8C(M519Hud *h);
void fn_1_F104(M519Hud *h);
void fn_1_F2DC(M519Hud *h);
void fn_1_F2E8(M519Hud *h);
void fn_1_F568(M519Hud *h);
void fn_1_F7F0(M519Hud *h);
s32 fn_1_F860(Vec *a, Vec *b, s32 push);
s32 fn_1_FA6C(Vec *a, Vec *b, s32 push);
f32 fn_1_FC78(f32 cur, f32 target, f32 rate);
void fn_1_FD7C(s16 player, s16 type, s16 time);
s16 fn_1_FE20(u16 camBits, Vec *pos);
s16 fn_1_10244(u16 camBits, Vec *pos);

SHARED_SYM extern u32 GlobalCounter;
typedef void (*M519StateFn)();
// MP5 state tables: each state is a function that loops until the work's state changes
static M519StateFn lbl_1_data_1C[1] = { fn_1_26A0 };
static M519StateFn lbl_1_data_20[2][5] = {
    { fn_1_35BC, fn_1_3664, fn_1_8188, fn_1_98AC, fn_1_9BA8 },
    { fn_1_35BC, fn_1_5EDC, fn_1_8188, fn_1_98AC, fn_1_A068 },
};
static M519StateFn lbl_1_data_48[5] = { fn_1_A598, fn_1_A634, fn_1_A6C4, fn_1_A77C, fn_1_A834 };
static M519StateFn lbl_1_data_5C[2] = { fn_1_B004, fn_1_B0BC };
static M519StateFn lbl_1_data_64[4] = { fn_1_C3D4, fn_1_C570, fn_1_C798, fn_1_C470 };
static void (*lbl_1_data_74[2])(void *, HU3DMODEL *, HU3DPARTICLE *, Mtx) = { fn_1_CDF0, fn_1_CEE4 };
static M519StateFn lbl_1_data_7C[4][4] = {
    { fn_1_D720, fn_1_D7BC, fn_1_E174, fn_1_F2E8 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
};
static char *lbl_1_data_14[2] = { "itemhook_c", "itemfook" };
s32 lbl_1_bss_0;
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s16 lbl_1_bss_C;
s32 lbl_1_bss_10;
s32 lbl_1_bss_14;
s16 lbl_1_bss_18[4];
M519Hud *lbl_1_bss_20[4];
s16 lbl_1_bss_30;
s16 lbl_1_bss_32;
M519Bullet *lbl_1_bss_38[0x2C];
M519Player *lbl_1_bss_E8[4];
M519Mech *lbl_1_bss_F8[4];
OMCAMERAVIEW lbl_1_bss_108[4];
M519Stage *lbl_1_bss_178;
omObjData *lbl_1_bss_17C;
u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };            /* const */
s16 lbl_1_rodata_18[2] = { 0x20, 0x60 };            /* const */
s16 lbl_1_rodata_1C[2] = { 0x30, 0x50 };            /* const */
Vec lbl_1_rodata_20[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 1800.0f, 180.0f, 180.0f },
    { 1800.0f, 45.0f, 45.0f },
    { 1800.0f, 315.0f, 315.0f },
}; /* const */
M519Light lbl_1_rodata_A4[3] = {
    {
        { 0.0f, 1500.0f, 1500.0f },
        { 0.0f, 0.0f, -1500.0f },
        { 0xFF, 0xFF, 0xFF, 0xFF },
    },
    {
        { 0.0f, 1500.0f, 1500.0f },
        { 0.0f, 0.0f, -1500.0f },
        { 0xFF, 0xFF, 0xFF, 0xFF },
    },
    {
        { 0.0f, 1500.0f, 1500.0f },
        { 0.0f, 0.0f, -1500.0f },
        { 0xFF, 0xFF, 0xFF, 0xFF },
    },
}; /* const */
s32 lbl_1_rodata_164[0xD] = {
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
}; /* const */
M519View lbl_1_rodata_198[4] = {
    {
        50.0f,
        10.0f,
        24000.0f,
        1.2f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
    },
    {
        50.0f,
        10.0f,
        24000.0f,
        1.7625275f,
        596.0f,
        0.0f,
        364.0f,
        213.33f,
        0.0f,
        1.0f,
        640.0f,
        0.0f,
        320.0f,
        173.33f,
    },
    {
        50.0f,
        10.0f,
        24000.0f,
        2.1692724f,
        596.0f,
        153.33f,
        364.0f,
        153.33f,
        0.0f,
        1.0f,
        640.0f,
        173.33f,
        320.0f,
        133.33f,
    },
    {
        50.0f,
        10.0f,
        24000.0f,
        1.7625275f,
        596.0f,
        286.66f,
        276.0f,
        193.33f,
        0.0f,
        1.0f,
        640.0f,
        306.66f,
        320.0f,
        173.33f,
    },
}; /* const */
u32 lbl_1_rodata_278[3] = { DATA_MAKE_NUM(DATADIR_MP5_M519, 71), DATA_MAKE_NUM(DATADIR_MP5_M519, 72), DATA_MAKE_NUM(DATADIR_MP5_M519, 72) }; /* const */
M519HudInit lbl_1_rodata_284[4] = {
    { 0, 128.0f, 520.0f },
    { 1, 640.0f, 87.0f },
    { 2, 640.0f, 240.5f },
    { 3, 640.0f, 394.0f },
}; /* const */
M519View lbl_1_rodata_2D0[8] = {
    {
        50.0f,
        100.0f,
        24000.0f,
        1.2f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        640.0f,
        480.0f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        1.7625275f,
        596.0f,
        0.0f,
        364.0f,
        213.33f,
        0.0f,
        1.0f,
        640.0f,
        0.0f,
        320.0f,
        173.33f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        2.1692724f,
        596.0f,
        153.33f,
        364.0f,
        153.33f,
        0.0f,
        1.0f,
        640.0f,
        173.33f,
        320.0f,
        133.33f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        1.7625275f,
        596.0f,
        286.66f,
        276.0f,
        193.33f,
        0.0f,
        1.0f,
        640.0f,
        306.66f,
        320.0f,
        173.33f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        0.6f,
        0.0f,
        0.0f,
        320.0f,
        480.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        320.0f,
        480.0f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        1.7625275f,
        276.0f,
        0.0f,
        364.0f,
        213.33f,
        0.0f,
        1.0f,
        320.0f,
        0.0f,
        320.0f,
        173.33f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        1.7625275f,
        276.0f,
        153.33f,
        364.0f,
        193.33f,
        0.0f,
        1.0f,
        320.0f,
        173.33f,
        320.0f,
        133.33f,
    },
    {
        50.0f,
        100.0f,
        24000.0f,
        1.7625275f,
        276.0f,
        286.66f,
        364.0f,
        193.33f,
        0.0f,
        1.0f,
        320.0f,
        306.66f,
        320.0f,
        173.33f,
    },
}; /* const */
f32 lbl_1_rodata_4B8[4] = { -320.0f, -60.0f, 130.0f, 320.0f }; /* const */
s16 lbl_1_rodata_4C8[4] = { 0x28, 0x38, 0x48, 0x58 }; /* const */
M519Ints7 lbl_1_rodata_508[3] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 0), DATA_MAKE_NUM(DATADIR_MP5_M519, 3), DATA_MAKE_NUM(DATADIR_MP5_M519, 1), DATA_MAKE_NUM(DATADIR_MP5_M519, 2), DATA_MAKE_NUM(DATADIR_MP5_M519, 4), DATA_MAKE_NUM(DATADIR_MP5_M519, 5), DATA_MAKE_NUM(DATADIR_MP5_M519, 6) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 0), DATA_MAKE_NUM(DATADIR_MP5_M519, 13), DATA_MAKE_NUM(DATADIR_MP5_M519, 1), DATA_MAKE_NUM(DATADIR_MP5_M519, 2), -1, -1, -1 } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 0), DATA_MAKE_NUM(DATADIR_MP5_M519, 23), DATA_MAKE_NUM(DATADIR_MP5_M519, 1), DATA_MAKE_NUM(DATADIR_MP5_M519, 2), DATA_MAKE_NUM(DATADIR_MP5_M519, 24), DATA_MAKE_NUM(DATADIR_MP5_M519, 25), -1 } },
}; /* const */
u8 lbl_1_rodata_55C[3][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0x64, 0x6E, 0x78, 0 } }; /* const */
M519BldSet lbl_1_rodata_568[3] = {
    {
        {
            { 0, { 800.0f, 0.0f, -800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 800.0f, 0.0f, 800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -800.0f, 0.0f, -800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -800.0f, 0.0f, 800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -1500.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 1500.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, -1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, 1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, -1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, 1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        },
    },
    {
        {
            { 0, { 0.0f, 0.0f, 1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 600.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -600.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { -850.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -1100.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 850.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 1100.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 0.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        },
    },
    {
        {
            { 1, { -450.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -450.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 450.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 450.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -1350.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -1350.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 1350.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 1350.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -450.0f, 0.0f, -1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -450.0f, 0.0f, 1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 450.0f, 0.0f, -1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 450.0f, 0.0f, 1350.0f }, { 0.0f, 0.0f, 0.0f } },
        },
    },
}; /* const */
M519Ints9 lbl_1_rodata_958[2] = {
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 33),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 52),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 55),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 50),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 51),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 63),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 34),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 35),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 64),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 43),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 58),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 65),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 49),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 66),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 67),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 68),
            -1,
            -1,
        },
    },
}; /* const */
M519Ints7 lbl_1_rodata_9A0[2] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 36), DATA_MAKE_NUM(DATADIR_MP5_M519, 37), DATA_MAKE_NUM(DATADIR_MP5_M519, 38), DATA_MAKE_NUM(DATADIR_MP5_M519, 40), DATA_MAKE_NUM(DATADIR_MP5_M519, 39), DATA_MAKE_NUM(DATADIR_MP5_M519, 41), DATA_MAKE_NUM(DATADIR_MP5_M519, 42) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 44), DATA_MAKE_NUM(DATADIR_MP5_M519, 45), DATA_MAKE_NUM(DATADIR_MP5_M519, 46), DATA_MAKE_NUM(DATADIR_MP5_M519, 45), DATA_MAKE_NUM(DATADIR_MP5_M519, 46), DATA_MAKE_NUM(DATADIR_MP5_M519, 47), DATA_MAKE_NUM(DATADIR_MP5_M519, 47) } },
}; /* const */
M519MechInit lbl_1_rodata_9D8[2] = {
    { 0.17857143f, 0.029761905f, 140.0f, 0x50 },
    { 0.5952381f, 0.05952381f, 80.0f, 0x28 },
}; /* const */
M519MotSet lbl_1_rodata_9F8[2] = {
    {
        {
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 0.0f, 0 },
        },
    },
    {
        {
            { 0.0f, 16.0f, 0x40000001 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 16.0f, 0 },
            { 0.0f, 16.0f, 0 },
        },
    },
}; /* const */
s32 lbl_1_rodata_AE0[4] = { 0xB4, 0xAA, 0x96, 0xA0 }; /* const */
f32 lbl_1_rodata_AF0[4] = { 15.0f, 16.0f, 17.0f, 18.0f }; /* const */
s16 lbl_1_rodata_B00[4] = { 0x1E, 0x19, 0x14, 0x14 }; /* const */
s32 lbl_1_rodata_B08[4] = { 0x280, 0x294, 0x2A8, 0x2BC }; /* const */
s32 lbl_1_rodata_B18[4] = { 0x514, 0x4B0, 0x44C, 0x3E8 }; /* const */
s16 lbl_1_rodata_B28[4] = { 0x23, 0x19, 0x14, 0xF }; /* const */
s32 lbl_1_rodata_B30[4] = { 0x258, 0x262, 0x26C, 0x276 }; /* const */
s16 lbl_1_rodata_B40[4] = { 6, 4, 2, 0 };           /* const */
f32 lbl_1_rodata_B48[4] = { 35.0f, 34.0f, 33.0f, 32.0f }; /* const */
s32 lbl_1_rodata_BA0[4] = { 0x7D0, 0x834, 0x898, 0x8FC }; /* const */
s32 lbl_1_rodata_BB0[4] = { 0x28, 0x1E, 0x14, 0xA }; /* const */
s32 lbl_1_rodata_BC0[4] = { 0xB4, 0xAA, 0x96, 0xA0 }; /* const */
s32 lbl_1_rodata_BD0[4] = { 0x226, 0x21C, 0x212, 0x208 }; /* const */
s32 lbl_1_rodata_BE0[4] = { 0xA, 0xF, 0x14, 0x19 }; /* const */
s16 lbl_1_rodata_BF0[4] = { 4, 3, 2, 0 };           /* const */
s32 lbl_1_rodata_C48[2] = { 0x711, 0x713 };         /* const */
M519Ints6 lbl_1_rodata_C60[0xD] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_MARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_LUIGIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_PEACHMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_YOSHIMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WARIOMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_DAISYMOT, 7) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 0), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 3), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 4), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 1), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 6), DATA_MAKE_NUM(DATADIR_MP5_WALUIGIMOT, 7) } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_KINOPIOMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_TERESAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
    { { 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 0 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 3 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 4 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 1 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 6 */, 0xFFFFFFFF /* TODO(mp5): DATADIR_MP5_MINIKOOPAMOT not mounted, entry 7 */ } },
}; /* const */
s32 lbl_1_rodata_D98[0xD] = {
    DATA_MAKE_NUM(DATADIR_MP5_M519, 93),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 94),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 95),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 96),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 97),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 98),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 99),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 100),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 101),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 102),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 103),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 104),
    DATA_MAKE_NUM(DATADIR_MP5_M519, 105),
}; /* const */
M519Ints2 lbl_1_rodata_DD4[5] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 53), DATA_MAKE_NUM(DATADIR_MP5_M519, 54) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 56), DATA_MAKE_NUM(DATADIR_MP5_M519, 57) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 61), DATA_MAKE_NUM(DATADIR_MP5_M519, 57) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 62), DATA_MAKE_NUM(DATADIR_MP5_M519, 57) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 59), DATA_MAKE_NUM(DATADIR_MP5_M519, 60) } },
}; /* const */
M519BulletInit lbl_1_rodata_DFC[5] = {
    { 73.333336f, 12.0f, 12.0f, 0x28, 1, 3, 0x1E, 1 },
    { 76.666664f, 80.0f, 80.0f, 0x78, 1, 0xF, 0xC8, 0 },
    { 0.0f, 500.0f, 200.0f, 0xF, 0xF, 1, 0xC8, 0 },
    { 0.0f, 1000.0f, 200.0f, 0x1E, 0x1E, 3, 0xC8, 0 },
    { 73.333336f, 12.0f, 12.0f, 0x19, 1, 1, 0xA, 1 },
}; /* const */
Vec lbl_1_rodata_E74 = { 0.0f, 0.0f, 0.0f };    /* const */
s32 lbl_1_rodata_E80[5] = { 0x70C, 0x70E, 0x70F, 0x70F, 0x712 }; /* const */
s32 lbl_1_rodata_E98[2] = { 0x714, 0x715 };         /* const */
M519Ints2 lbl_1_rodata_EA0[5] = { { { 1, 1 } }, { { 1, 1 } }, { { 1, 1 } }, { { 1, 1 } }, { { 0, 1 } } }; /* const */
s32 lbl_1_rodata_EC8[2] = { 0x71B, 0x71C };         /* const */
M519Ints6 lbl_1_rodata_ED0[3] = {
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 7), DATA_MAKE_NUM(DATADIR_MP5_M519, 8), DATA_MAKE_NUM(DATADIR_MP5_M519, 9), DATA_MAKE_NUM(DATADIR_MP5_M519, 10), DATA_MAKE_NUM(DATADIR_MP5_M519, 11), DATA_MAKE_NUM(DATADIR_MP5_M519, 12) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 17), DATA_MAKE_NUM(DATADIR_MP5_M519, 18), DATA_MAKE_NUM(DATADIR_MP5_M519, 19), DATA_MAKE_NUM(DATADIR_MP5_M519, 20), DATA_MAKE_NUM(DATADIR_MP5_M519, 21), DATA_MAKE_NUM(DATADIR_MP5_M519, 22) } },
    { { DATA_MAKE_NUM(DATADIR_MP5_M519, 27), DATA_MAKE_NUM(DATADIR_MP5_M519, 28), DATA_MAKE_NUM(DATADIR_MP5_M519, 29), DATA_MAKE_NUM(DATADIR_MP5_M519, 30), DATA_MAKE_NUM(DATADIR_MP5_M519, 31), DATA_MAKE_NUM(DATADIR_MP5_M519, 32) } },
}; /* const */
s16 lbl_1_rodata_F18[2] = { 0x8C, 0x64 };           /* const */
s16 lbl_1_rodata_F1C[2] = { 0xF, 0xA };             /* const */
s32 lbl_1_rodata_F20[2] = { 0x719, 0x71A };         /* const */
s32 lbl_1_rodata_F28[2] = { 0x717, 0x718 };         /* const */
s32 lbl_1_rodata_F30[2] = { 0x12C, 0x12C };         /* const */
M519Ints18 lbl_1_rodata_F44[4] = {
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 76),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 73),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 75),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 80),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 81),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 82),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 83),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 84),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 85),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 86),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 87),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 88),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 89),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 90),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 77),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 73),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 75),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 80),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 81),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 82),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 83),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 84),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 85),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 86),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 87),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 88),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 91),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 92),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 78),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 73),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 75),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 80),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 81),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 82),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 83),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 84),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 85),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 86),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 87),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 88),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 91),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 92),
        },
    },
    {
        {
            DATA_MAKE_NUM(DATADIR_MP5_M519, 79),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 73),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 75),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 74),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 80),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 81),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 82),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 83),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 84),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 85),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 86),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 87),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 88),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 91),
            DATA_MAKE_NUM(DATADIR_MP5_M519, 92),
        },
    },
}; /* const */
M519HudOfs lbl_1_rodata_1064[4] = {
    {
        {
            { 0.0f, 0.0f },
            { -84.0f, -16.0f },
            { -32.0f, 0.0f },
            { -84.0f, -16.0f },
            { -84.0f, -16.0f },
            { -84.0f, -16.0f },
            { -84.0f, -16.0f },
            { 111.0f, -3.0f },
            { 111.0f, -3.0f },
            { 111.0f, -3.0f },
            { 129.0f, -22.0f },
            { 129.0f, -22.0f },
            { 129.0f, -22.0f },
            { 148.5f, -41.5f },
            { 148.5f, -41.5f },
            { 148.5f, -41.5f },
            { 24.0f, -28.0f },
            { 24.0f, -28.0f },
        },
    },
    {
        {
            { 0.0f, 0.0f },
            { -88.0f, -40.0f },
            { -14.0f, 78.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { -24.0f, -15.0f },
            { -24.0f, -15.0f },
            { -24.0f, -15.0f },
            { -4.0f, -35.0f },
            { -4.0f, -35.0f },
            { -4.0f, -35.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 8.0f, -31.0f },
            { 8.0f, -31.0f },
        },
    },
    {
        {
            { 0.0f, 0.0f },
            { -88.0f, -40.0f },
            { -14.0f, 61.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { -24.0f, -33.0f },
            { -24.0f, -33.0f },
            { -24.0f, -33.0f },
            { -4.0f, -52.0f },
            { -4.0f, -52.0f },
            { -4.0f, -52.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 8.0f, -48.0f },
            { 8.0f, -48.0f },
        },
    },
    {
        {
            { 0.0f, 0.0f },
            { -88.0f, -40.0f },
            { -14.0f, 42.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { -24.0f, -49.5f },
            { -24.0f, -49.5f },
            { -24.0f, -49.5f },
            { -4.0f, -69.0f },
            { -4.0f, -69.0f },
            { -4.0f, -69.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 0.0f },
            { 8.0f, -64.0f },
            { 8.0f, -64.0f },
        },
    },
}; /* const */



void ObjectSetup(void) {
    s32 sp2C;
    s32 sp28;
    void (*sp24)(s16, s16);
    void (*sp20)(s16, s16);
    void (*sp1C)(s16, s16);
    void (*sp18)(s16, s16);
    void (*sp14)(s16, s16);
    void (*sp10)(s16, s16);
    void (*spC)(s16, s16);
    s8 spA;
    s16 sp8;
    HUPROCESS *temp_r3;

    temp_r3 = omInitObjMan(1, 0x2000);
    lbl_1_bss_17C = omAddObjEx(temp_r3, 0x1000, 0U, 0U, 0, omOutViewMulti);
    lbl_1_bss_17C->work[0] = 4;
    omGameSysInit(temp_r3);
    Hu3DNoSyncSet(1);
    MGSEQ_PARAM seqParam = { 0x3C, 0, fn_1_28C, fn_1_9F4, fn_1_143C, fn_1_14E8, fn_1_1628, fn_1_19C4, fn_1_1FC0, NULL, NULL };
    MgSeqCreate(&seqParam);
    lbl_1_bss_30 = GlobalCounter % 3; // MP5: GWSystem.subGameNo (debug stage select) == -1 in normal play
}


void fn_1_28C(s16 mode, s16 frameNo) {
    s32 sp14[4];
    Vec spC;
    s16 sp1A;
    s16 sp16;
    s16 sp8;
    M519HudInit *temp_r4;
    s16 var_r31;
    s16 var_r31_13;
    s16 var_r31_5;
    s32 temp_r0;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r30;
    s32 var_r31_10;
    s32 var_r31_11;
    s32 var_r31_12;
    s32 var_r31_14;
    s32 var_r31_15;
    s32 var_r31_2;
    s32 var_r31_3;
    s32 var_r31_4;
    s32 var_r31_6;
    s32 var_r31_7;
    s32 var_r31_8;
    s32 var_r31_9;
    u16 temp_r0_2;

    sp8 = frameNo;
    if (sp8 != 0) {

    } else {
        lbl_1_bss_178 = fn_1_2298();
        var_r31 = 0;
loop_10:
        if (var_r31 < 4) {
            if (var_r31 != 0) {
                if ((var_r31 >= 0) && (var_r31 < 4)) {
                    lbl_1_bss_F8[var_r31] = fn_1_297C(1, var_r31);
                }
            } else {
                lbl_1_bss_F8[var_r31] = fn_1_297C(0, var_r31);
            }
            var_r31 += 1;
            goto loop_10;
        }
        var_r31_2 = 0;
loop_13:
        if (var_r31_2 < 4) {
            sp14[var_r31_2] = GWPlayerCfg[var_r31_2].group;
            var_r31_2 += 1;
            goto loop_13;
        }
        var_r29 = 0;
        var_r31_3 = 0;
loop_18:
        if (var_r31_3 < 4) {
            if ((s16) sp14[var_r31_3] == 0) {
                var_r29 += 1;
            }
            var_r31_3 += 1;
            goto loop_18;
        }
        if (var_r29 == 1) {
            var_r31_4 = 0;
loop_24:
            if (var_r31_4 < 4) {
                if ((s16) sp14[var_r31_4] != 0) {
                    sp14[var_r31_4] = 1;
                }
                var_r31_4 += 1;
                goto loop_24;
            }
        } else {
            sp14[0] = 0;
            sp16 = 1;
            sp14[1] = 1;
            sp1A = 1;
        }
        var_r31_5 = 0;
loop_29:
        if (var_r31_5 < 4) {
            lbl_1_bss_E8[var_r31_5] = fn_1_A204(sp14[var_r31_5], var_r31_5);
            var_r31_5 += 1;
            goto loop_29;
        }
        var_r31_6 = 0;
loop_34:
        if (var_r31_6 < 4) {
            if ((s16) sp14[var_r31_6] == 0) {
                fn_1_3518(*lbl_1_bss_F8, lbl_1_bss_E8[var_r31_6]);
            } else {
                var_r31_6 += 1;
                goto loop_34;
            }
        }
        var_r29_2 = 1;
        var_r31_7 = 0;
loop_39:
        if (var_r31_7 < 4) {
            if ((s16) sp14[var_r31_7] != 0) {
                temp_r0 = var_r29_2;
                var_r29_2 += 1;
                fn_1_3518(lbl_1_bss_F8[temp_r0], lbl_1_bss_E8[var_r31_7]);
            }
            var_r31_7 += 1;
            goto loop_39;
        }
        var_r30 = 0;
        var_r31_8 = 0;
loop_42:
        if (var_r31_8 < 1) {
            lbl_1_bss_38[var_r30] = fn_1_AB40(3);
            var_r31_8 += 1;
            var_r30 += 1;
            goto loop_42;
        }
        var_r31_9 = 0;
loop_45:
        if (var_r31_9 < 2) {
            lbl_1_bss_38[var_r30] = fn_1_AB40(2);
            var_r31_9 += 1;
            var_r30 += 1;
            goto loop_45;
        }
        var_r31_10 = 0;
loop_48:
        if (var_r31_10 < 1) {
            lbl_1_bss_38[var_r30] = fn_1_AB40(1);
            var_r31_10 += 1;
            var_r30 += 1;
            goto loop_48;
        }
        var_r31_11 = 0;
loop_51:
        if (var_r31_11 < 8) {
            lbl_1_bss_38[var_r30] = fn_1_AB40(0);
            var_r31_11 += 1;
            var_r30 += 1;
            goto loop_51;
        }
        var_r31_12 = 0;
loop_54:
        if (var_r31_12 < 0x20) {
            lbl_1_bss_38[var_r30] = fn_1_AB40(4);
            var_r31_12 += 1;
            var_r30 += 1;
            goto loop_54;
        }
        var_r31_13 = 0;
loop_57:
        if (var_r31_13 < 4) {
            lbl_1_bss_20[var_r31_13] = fn_1_D0BC((s16) lbl_1_rodata_284[var_r31_13].type, var_r31_13);
            temp_r4 = &lbl_1_rodata_284[var_r31_13];
            spC.x = temp_r4->x;
            spC.y = temp_r4->y;
            fn_1_D65C(lbl_1_bss_20[var_r31_13], &spC);
            var_r31_13 += 1;
            goto loop_57;
        }
        var_r31_14 = 0;
loop_60:
        if (var_r31_14 < 3) {
            lbl_1_bss_18[var_r31_14] = espEntry(lbl_1_rodata_278[var_r31_14], 0, 0);
            espPriSet(lbl_1_bss_18[var_r31_14], 0x1F4);
            var_r31_14 += 1;
            goto loop_60;
        }
        lbl_1_bss_32 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0U, 0U, 0U);
        Hu3DGLightPosAimSetV(lbl_1_bss_32, &lbl_1_rodata_A4[lbl_1_bss_30].pos, &lbl_1_rodata_A4[lbl_1_bss_30].aim);
        Hu3DGLightColorSet(lbl_1_bss_32, (u8) lbl_1_rodata_A4[lbl_1_bss_30].color[0], (u8) lbl_1_rodata_A4[lbl_1_bss_30].color[1], (u8) lbl_1_rodata_A4[lbl_1_bss_30].color[2], (u8) lbl_1_rodata_A4[lbl_1_bss_30].color[3]);
        Hu3DGLightStaticSet(lbl_1_bss_32, 0);
        Hu3DCameraCreate(0xF);
        var_r31_15 = 0;
loop_63:
        if (var_r31_15 < 4) {
            temp_r0_2 = lbl_1_rodata_10[var_r31_15];
            Hu3DCameraPerspectiveSet((s32) (s16) temp_r0_2, lbl_1_rodata_198[var_r31_15].unk0, lbl_1_rodata_198[var_r31_15].unk4, lbl_1_rodata_198[var_r31_15].unk8, lbl_1_rodata_198[var_r31_15].unkC);
            Hu3DCameraViewportSet((s32) (s16) temp_r0_2, lbl_1_rodata_198[var_r31_15].unk10, lbl_1_rodata_198[var_r31_15].unk14, lbl_1_rodata_198[var_r31_15].unk18, lbl_1_rodata_198[var_r31_15].unk1C, lbl_1_rodata_198[var_r31_15].unk20, lbl_1_rodata_198[var_r31_15].unk24);
            Hu3DCameraScissorSet((s32) (s16) temp_r0_2, (u32) lbl_1_rodata_198[var_r31_15].unk28, (u32) lbl_1_rodata_198[var_r31_15].unk2C, (u32) lbl_1_rodata_198[var_r31_15].unk30, (u32) lbl_1_rodata_198[var_r31_15].unk34);
            var_r31_15 += 1;
            goto loop_63;
        }
    }
    MgSeqModeNext();
}

void fn_1_9F4(s16 mode, s16 frameNo) {
    Vec spC;
    Vec sp18;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    s16 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s32 var_r31;
    s32 var_r31_2;

    sp8 = frameNo;
    switch (sp8) {                                  /* irregular */
    case 0x0:
        lbl_1_bss_10 = HuAudFXPlay(0x708);
        var_r31 = 0;
loop_8:
        if (var_r31 < 4) {
            temp_f31 = lbl_1_rodata_20[var_r31].x;
            temp_f30 = lbl_1_rodata_20[var_r31].y;
            temp_f29 = lbl_1_rodata_20[var_r31].z;
            sp30 = (f32) ((f64) temp_f31 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
            sp38 = (f32) ((f64) temp_f31 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
            sp34 = 0.0f;
            sp24 = 0.0f;
            sp2C = 0.0f;
            sp28 = temp_f29;
            sp18.x = sp30;
            sp18.y = sp34;
            sp18.z = sp38;
            fn_1_3138(lbl_1_bss_F8[var_r31], &sp18);
            spC.x = sp24;
            spC.y = sp28;
            spC.z = sp2C;
            fn_1_3290(lbl_1_bss_F8[var_r31], &spC);
            fn_1_9B9C(lbl_1_bss_F8[var_r31]);
            var_r31 += 1;
            goto loop_8;
        }
        var_r31_2 = 0;
loop_11:
        if (var_r31_2 < 4) {
            lbl_1_bss_108[var_r31_2].center.x = 0.0f;
            lbl_1_bss_108[var_r31_2].center.y = 0.0f;
            lbl_1_bss_108[var_r31_2].center.z = 0.0f;
            lbl_1_bss_108[var_r31_2].rot.x = -10.0f;
            lbl_1_bss_108[var_r31_2].rot.y = 0.0f;
            lbl_1_bss_108[var_r31_2].rot.z = 0.0f;
            lbl_1_bss_108[var_r31_2].zoom = 1000.0f;
            omCameraViewSetMulti((s16) lbl_1_rodata_10[var_r31_2], &lbl_1_bss_108[var_r31_2]);
            var_r31_2 += 1;
            goto loop_11;
        }
        return;
    case 0x78:
        HuAudFXStop(lbl_1_bss_10);
        return;
    case 0xB4:
        fn_1_2730(lbl_1_bss_178);
        fn_1_D64();
        fn_1_2790(lbl_1_bss_178);
        MgSeqModeNext();
        return;
    }
}

void fn_1_D64(void) {
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r29;
    s32 var_r30;
    s32 var_r31;

    var_r30 = 1;
loop_14:
    if (var_r30 <= 0x3C) {
        var_r31 = 0;
loop_12:
        if (var_r31 < 4) {
            temp_r29 = (s16) lbl_1_rodata_10[var_r31];
            temp_f31 = (f32) sin((3.141592653589793 * (f64) (90.0f * (0.016666668f * (f32) var_r30))) / 180.0);
            Hu3DCameraPerspectiveSet((s32) temp_r29, lbl_1_rodata_2D0[var_r31].unk0 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk0 - lbl_1_rodata_2D0[var_r31].unk0)), lbl_1_rodata_2D0[var_r31].unk4 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk4 - lbl_1_rodata_2D0[var_r31].unk4)), lbl_1_rodata_2D0[var_r31].unk8 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk8 - lbl_1_rodata_2D0[var_r31].unk8)), lbl_1_rodata_2D0[var_r31].unkC + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unkC - lbl_1_rodata_2D0[var_r31].unkC)));
            Hu3DCameraViewportSet((s32) temp_r29, lbl_1_rodata_2D0[var_r31].unk10 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk10 - lbl_1_rodata_2D0[var_r31].unk10)), lbl_1_rodata_2D0[var_r31].unk14 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk14 - lbl_1_rodata_2D0[var_r31].unk14)), lbl_1_rodata_2D0[var_r31].unk18 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk18 - lbl_1_rodata_2D0[var_r31].unk18)), lbl_1_rodata_2D0[var_r31].unk1C + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk1C - lbl_1_rodata_2D0[var_r31].unk1C)), lbl_1_rodata_2D0[var_r31].unk20 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk20 - lbl_1_rodata_2D0[var_r31].unk20)), lbl_1_rodata_2D0[var_r31].unk24 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk24 - lbl_1_rodata_2D0[var_r31].unk24)));
            temp_f29 = lbl_1_rodata_2D0[var_r31].unk28 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk28 - lbl_1_rodata_2D0[var_r31].unk28));
            temp_f28 = lbl_1_rodata_2D0[var_r31].unk2C + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk2C - lbl_1_rodata_2D0[var_r31].unk2C));
            temp_f27 = lbl_1_rodata_2D0[var_r31].unk30 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk30 - lbl_1_rodata_2D0[var_r31].unk30));
            temp_f30 = lbl_1_rodata_2D0[var_r31].unk34 + (temp_f31 * (lbl_1_rodata_2D0[var_r31 + 4].unk34 - lbl_1_rodata_2D0[var_r31].unk34));
            Hu3DCameraScissorSet((s32) temp_r29, (u32) temp_f29, (u32) temp_f28, (u32) temp_f27, (u32) temp_f30);
            switch (var_r31) {                      /* irregular */
            case 0:
                espPosSet(lbl_1_bss_18[0], 0.9f * temp_f27, 239.0f);
                break;
            case 1:
                espPosSet(lbl_1_bss_18[1], 16.0f + (0.9f * (160.0f + temp_f29)), (temp_f28 + temp_f30) - 1.0f);
                break;
            case 2:
                espPosSet(lbl_1_bss_18[2], 16.0f + (0.9f * (160.0f + temp_f29)), (temp_f28 + temp_f30) - 1.0f);
                break;
            }
            var_r31 += 1;
            goto loop_12;
        }
        HuPrcVSleep();
        var_r30 += 1;
        goto loop_14;
    }
}

void fn_1_143C(s16 mode, s16 frameNo) {
    s16 sp8;
    s32 var_r30;
    s32 var_r31;

    sp8 = frameNo;
    switch (sp8) {                                  /* irregular */
    case 0x0:
        lbl_1_bss_14 = HuAudSStreamPlay(0x3E);
        var_r31 = 0;
loop_9:
        if (var_r31 < 4) {
            fn_1_D7B0(lbl_1_bss_20[var_r31]);
            var_r30 = 0;
loop_7:
            if (var_r30 < 0xC) {
                HuPrcVSleep();
                var_r30 += 1;
                goto loop_7;
            }
            var_r31 += 1;
            goto loop_9;
        }
        return;
    case 0x78:
        MgSeqModeNext();
        return;
    }
}

void fn_1_14E8(s16 mode, s16 frameNo) {
    s16 sp8;
    s32 var_r31;

    sp8 = frameNo;
    if (sp8 != 0) {
        if (fn_1_A1D4(lbl_1_bss_F8[0]) != 0) {
            lbl_1_bss_0 = 1;
        }
        if ((fn_1_A1D4(lbl_1_bss_F8[1]) != 0) && (fn_1_A1D4(lbl_1_bss_F8[2]) != 0) && (fn_1_A1D4(lbl_1_bss_F8[3]) != 0)) {
            lbl_1_bss_4 = 1;
        }
        if (((s32) lbl_1_bss_0 != 0) || ((s32) lbl_1_bss_4 != 0)) {
            MgSeqModeNext();
        }
        if (MgSeqTimerValueGet() == 0U) {
            MgSeqModeNext();
        }
        return;
    }
    var_r31 = 0;
loop_4:
    if (var_r31 < 4) {
        fn_1_3658(lbl_1_bss_F8[var_r31]);
        lbl_1_bss_F8[var_r31]->inputOn = 1;
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_1628(s16 mode, s16 frameNo) {
    s16 sp8;
    M519Mech *temp_r31;
    M519Mech *temp_r31_2;
    s16 temp_r26;
    s16 temp_r27;
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r30;
    s32 var_r30_2;

    sp8 = frameNo;
    switch (sp8) {                                  /* irregular */
    case 0:
        lbl_1_bss_8 = 1;
        HuAudSStreamFadeOut(lbl_1_bss_14, 0x3E8);
        var_r30 = 0;
loop_6:
        if (var_r30 < 4) {
            temp_r31 = lbl_1_bss_F8[var_r30];
            temp_r31->inputOn = 0;
            temp_r31->chargeA = 0;
            temp_r31->chargeB = 0;
            fn_1_8E40(temp_r31);
            var_r30 += 1;
            goto loop_6;
        }
        var_r30_2 = 0;
loop_11:
        if (var_r30_2 < 4) {
            temp_r31_2 = lbl_1_bss_F8[var_r30_2];
            if (fn_1_A1D4(temp_r31_2) == 0) {
                fn_1_F2DC(lbl_1_bss_20[temp_r31_2->idx]);
            }
            var_r30_2 += 1;
            goto loop_11;
        }
        return;
    case 30:
        if ((((s32) lbl_1_bss_0 == 0) && ((s32) lbl_1_bss_4 == 0)) || (((s32) lbl_1_bss_0 != 0) && ((s32) lbl_1_bss_4 != 0))) {
            MgSeqDrawSet();
            return;
        }
        if ((s32) lbl_1_bss_0 != 0) {
            MgSeqWinnerSet(lbl_1_bss_E8[lbl_1_bss_F8[1]->player]->charNo, lbl_1_bss_E8[lbl_1_bss_F8[2]->player]->charNo, lbl_1_bss_E8[lbl_1_bss_F8[3]->player]->charNo, -1);
            temp_r29 = lbl_1_bss_E8[lbl_1_bss_F8[1]->player]->idx;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r29].coin_win = 0xA;
            }
            temp_r28 = lbl_1_bss_E8[lbl_1_bss_F8[2]->player]->idx;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r28].coin_win = 0xA;
            }
            temp_r27 = lbl_1_bss_E8[lbl_1_bss_F8[3]->player]->idx;
            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r27].coin_win = 0xA;
                return;
            }
        } else {
            if ((s32) lbl_1_bss_4 != 0) {
                MgSeqWinnerSet(lbl_1_bss_E8[lbl_1_bss_F8[0]->player]->charNo, -1, -1, -1);
                temp_r26 = lbl_1_bss_E8[lbl_1_bss_F8[0]->player]->idx;
                if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                    GWPlayer[temp_r26].coin_win = 0xA;
                }
            }
            return;
        }
        break;
    }
}

void fn_1_19C4(s16 mode, s16 frameNo) {
    Vec spC;
    Vec sp18;
    Vec sp24;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s16 sp8;
    M519Mech *temp_r29;
    M519Mech *temp_r29_2;
    M519Mech *temp_r29_3;
    OMCAMERAVIEW *temp_r31;
    OMCAMERAVIEW *temp_r31_2;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r30_5;
    u16 temp_r0;

    sp8 = frameNo;
    switch (sp8) {                                  /* irregular */
    case 0x3C:
        WipeColorSet(0xFFU, 0xFFU, 0xFFU);
        WipeCreate(2, 0, 0x1E);
        HuAudFadeOut(0x1E);
        return;
    case 0x5A:
        var_r30 = 0;
loop_11:
        if (var_r30 < 4) {
            fn_1_F7F0(lbl_1_bss_20[var_r30]);
            var_r30 += 1;
            goto loop_11;
        }
        fn_1_2900(lbl_1_bss_178);
        sp3C = 0.0f;
        sp40 = -5000.0f;
        sp44 = 0.0f;
        var_r30_2 = 0;
loop_14:
        if (var_r30_2 < 4) {
            temp_r29 = lbl_1_bss_F8[var_r30_2];
            fn_1_A628(lbl_1_bss_E8[temp_r29->player]);
            fn_1_35B0(temp_r29);
            sp24.x = sp3C;
            sp24.y = sp40;
            sp24.z = sp44;
            fn_1_3138(temp_r29, &sp24);
            temp_r29->camFollow = 0;
            var_r30_2 += 1;
            goto loop_14;
        }
        var_r30_3 = 0;
loop_21:
        if (var_r30_3 < 4) {
            temp_r0 = lbl_1_rodata_10[var_r30_3];
            temp_r29_2 = lbl_1_bss_F8[var_r30_3];
            if (var_r30_3 != 0) {
                if (var_r30_3 >= 0) {

                }
            } else {
                Hu3DCameraPerspectiveSet((s32) (s16) temp_r0, 50.0f, 10.0f, 24000.0f, 1.2f);
                Hu3DCameraViewportSet((s32) (s16) temp_r0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraScissorSet((s32) (s16) temp_r0, 0U, 0U, 0x280U, 0x1E0U);
                temp_r31 = &lbl_1_bss_108[temp_r29_2->idx];
                sin(0.0);
                temp_r31->center.x = (f32) 0.0;
                cos(0.0);
                temp_r31->center.z = (f32) 0.0;
                temp_r31->center.y = 150.0f;
                temp_r31->zoom = 600.0f;
                temp_r31->rot.y = 0.0f;
                temp_r31->rot.x = -15.0f;
                temp_r31->rot.z = 0.0f;
                omCameraViewMoveMulti((u32) *lbl_1_rodata_10, temp_r31, 1, 1);
            }
            var_r30_3 += 1;
            goto loop_21;
        }
        Hu3DCameraKill(0xE);
        lbl_1_bss_17C->work[0] = 1;
        var_r30_4 = 0;
loop_24:
        if (var_r30_4 < 3) {
            espDispOff(lbl_1_bss_18[var_r30_4]);
            var_r30_4 += 1;
            goto loop_24;
        }
        var_r30_5 = 0;
loop_27:
        if (var_r30_5 < 4) {
            temp_r29_3 = lbl_1_bss_F8[var_r30_5];
            sp3C = lbl_1_rodata_4B8[var_r30_5];
            sp40 = 0.0f;
            sp44 = 0.0f;
            sp18.x = sp3C;
            sp18.y = sp40;
            sp18.z = sp44;
            fn_1_A44C(lbl_1_bss_E8[temp_r29_3->player], &sp18);
            sp30 = 0.0f;
            sp34 = 0.0f;
            sp38 = 0.0f;
            spC.x = sp30;
            spC.y = sp34;
            spC.z = sp38;
            fn_1_A4EC(lbl_1_bss_E8[temp_r29_3->player], &spC);
            CharModelVoicePanSet(lbl_1_bss_E8[temp_r29_3->player]->charNo, (s16) lbl_1_rodata_4C8[var_r30_5]);
            var_r30_5 += 1;
            goto loop_27;
        }
        return;
    case 0x78:
        WipeColorSet(0xFFU, 0xFFU, 0xFFU);
        WipeCreate(1, 0, 0x1E);
        temp_r31_2 = &lbl_1_bss_108[(*lbl_1_bss_F8)->idx];
        sin(0.0);
        temp_r31_2->center.x = (f32) 0.0;
        cos(0.0);
        temp_r31_2->center.z = (f32) 0.0;
        temp_r31_2->center.y = 150.0f;
        temp_r31_2->zoom = 1500.0f;
        temp_r31_2->rot.y = 0.0f;
        temp_r31_2->rot.x = -15.0f;
        temp_r31_2->rot.z = 0.0f;
        omCameraViewMoveMulti((u32) *lbl_1_rodata_10, temp_r31_2, 0x190, 2);
        return;
    case 0xB4:
        MgSeqModeNext();
        return;
    }
}

void fn_1_1FC0(s16 mode, s16 frameNo) {
    s16 sp8;
    M519Mech *temp_r30;
    M519Mech *temp_r30_2;
    s32 var_r31;
    s32 var_r31_2;
    s32 var_r31_3;

    sp8 = frameNo;
    switch (sp8) {                                  /* irregular */
    case 0x0:
        if ((((s32) lbl_1_bss_0 == 0) && ((s32) lbl_1_bss_4 == 0)) || (((s32) lbl_1_bss_0 != 0) && ((s32) lbl_1_bss_4 != 0))) {
            CharLoseVoicePlay(lbl_1_bss_E8[lbl_1_bss_F8[0]->player]->charNo, lbl_1_bss_E8[lbl_1_bss_F8[1]->player]->charNo, lbl_1_bss_E8[lbl_1_bss_F8[2]->player]->charNo, lbl_1_bss_E8[lbl_1_bss_F8[3]->player]->charNo);
            var_r31 = 0;
loop_10:
            if (var_r31 < 4) {
                fn_1_A770(lbl_1_bss_E8[lbl_1_bss_F8[var_r31]->player]);
                var_r31 += 1;
                goto loop_10;
            }
        } else if ((s32) lbl_1_bss_0 != 0) {
            var_r31_2 = 0;
loop_18:
            if (var_r31_2 < 4) {
                temp_r30 = lbl_1_bss_F8[var_r31_2];
                if (var_r31_2 == 0) {
                    fn_1_A770(lbl_1_bss_E8[temp_r30->player]);
                } else {
                    fn_1_A6B8(lbl_1_bss_E8[temp_r30->player]);
                }
                var_r31_2 += 1;
                goto loop_18;
            }
        } else if ((s32) lbl_1_bss_4 != 0) {
            var_r31_3 = 0;
loop_26:
            if (var_r31_3 < 4) {
                temp_r30_2 = lbl_1_bss_F8[var_r31_3];
                if (var_r31_3 == 0) {
                    fn_1_A6B8(lbl_1_bss_E8[temp_r30_2->player]);
                } else {
                    fn_1_A770(lbl_1_bss_E8[temp_r30_2->player]);
                }
                var_r31_3 += 1;
                goto loop_26;
            }
        }
        fn_1_27FC(lbl_1_bss_178);
        return;
    case 0xB3:
        HuAudFXStop(lbl_1_bss_10);
        return;
    }
}


M519Stage *fn_1_2298(void) {
    Vec sp8;
    Vec sp14;
    M519BldInit *temp_r4;
    M519BldInit *temp_r4_2;
    M519Stage *temp_r3;
    s16 temp_r0;
    s32 var_r30;
    s32 var_r30_2;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Stage), MEMORY_DEFAULT_NUM);
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 7) {
        if ((s32) lbl_1_rodata_508[lbl_1_bss_30].n[var_r30] != -1) {
            temp_r3->mdl[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_508[lbl_1_bss_30].n[var_r30], MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelAttrSet(temp_r3->mdl[var_r30], 0x4000U);
        } else {
            temp_r3->mdl[var_r30] = -1;
        }
        var_r30 += 1;
        goto loop_5;
    }
    Hu3DModelCameraSet(temp_r3->mdl[2], 1U);
    Hu3DModelCameraSet(temp_r3->mdl[3], 1U);
    Hu3DModelAttrSet(temp_r3->mdl[1], 0x40000001U);
    if ((s16) temp_r3->mdl[4] != -1) {
        Hu3DModelAttrSet(temp_r3->mdl[4], 0x40000001U);
    }
    if ((s16) temp_r3->mdl[5] != -1) {
        Hu3DModelAttrSet(temp_r3->mdl[5], 0x40000001U);
    }
    if ((s16) temp_r3->mdl[6] != -1) {
        Hu3DModelAttrSet(temp_r3->mdl[6], 0x40000001U);
    }
    Hu3DModelLayerSet(temp_r3->mdl[0], 1);
    Hu3DModelLayerSet(temp_r3->mdl[1], 0);
    Hu3DModelLayerSet(temp_r3->mdl[2], 1);
    Hu3DModelLayerSet(temp_r3->mdl[3], 2);
    if ((s16) temp_r3->mdl[4] != -1) {
        Hu3DModelLayerSet(temp_r3->mdl[4], 0);
    }
    if ((s16) temp_r3->mdl[5] != -1) {
        Hu3DModelLayerSet(temp_r3->mdl[5], 0);
    }
    if ((s16) temp_r3->mdl[6] != -1) {
        Hu3DModelLayerSet(temp_r3->mdl[6], 0);
    }
    Hu3DBGColorSet((u8) *lbl_1_rodata_55C[lbl_1_bss_30], (u8) lbl_1_rodata_55C[lbl_1_bss_30][1], (u8) lbl_1_rodata_55C[lbl_1_bss_30][2]);
    temp_r3->proc = HuPrcChildCreate(fn_1_2654, 0x1000U, 0x1000U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    var_r30_2 = 0;
loop_23:
    if (var_r30_2 < 0xC) {
        temp_r0 = lbl_1_rodata_568[lbl_1_bss_30].bld[var_r30_2].type;
        if (temp_r0 != 2) {
            temp_r3->bld[var_r30_2] = fn_1_C058(temp_r0);
            temp_r4 = &lbl_1_rodata_568[lbl_1_bss_30].bld[var_r30_2];
            sp14.x = temp_r4->pos.x;
            sp14.y = temp_r4->pos.y;
            sp14.z = temp_r4->pos.z;
            fn_1_C288(temp_r3->bld[var_r30_2], &sp14);
            temp_r4_2 = &lbl_1_rodata_568[lbl_1_bss_30].bld[var_r30_2];
            sp8.x = temp_r4_2->rot.x;
            sp8.y = temp_r4_2->rot.y;
            sp8.z = temp_r4_2->rot.z;
            fn_1_C328(temp_r3->bld[var_r30_2], &sp8);
            fn_1_C3C8(temp_r3->bld[var_r30_2]);
        } else {
            temp_r3->bld[var_r30_2] = 0;
        }
        var_r30_2 += 1;
        goto loop_23;
    }
    return temp_r3;
}

void fn_1_2654(void) {
    M519Stage *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_1C[temp_r31->state](temp_r31);
    }
}


void fn_1_26A0(void) {
    s16 temp_r29;
    s16 temp_r30;
    s32 var_r31;

loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r30 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r30;
    if (temp_r30 == temp_r29) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_2730(M519Stage *s) {
    Hu3DModelAttrSet(s->mdl[2], 1U);
    Hu3DModelAttrSet(s->mdl[3], 1U);
    Hu3DModelAttrSet(s->mdl[2], 0x40000002U);
    Hu3DModelAttrSet(s->mdl[3], 0x40000002U);
}

void fn_1_2790(M519Stage *s) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 0xC) {
        if ((M519Bld *) s->bld[var_r31] != NULL) {
            fn_1_C544(s->bld[var_r31]);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_27FC(M519Stage *s) {
    Hu3DModelAttrReset(s->mdl[2], 0x40000002U);
    Hu3DModelAttrReset(s->mdl[2], 1U);
    Hu3DMotionStartEndSet(s->mdl[2], 0.0f, Hu3DMotionMaxTimeGet(s->mdl[2]));
    Hu3DMotionTimeSet(s->mdl[2], Hu3DMotionMaxTimeGet(s->mdl[2]));
    Hu3DModelAttrSet(s->mdl[2], 0x40000004U);
    Hu3DModelAttrReset(s->mdl[2], 0x40000001U);
}


void fn_1_2900(M519Stage *s) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 0xC) {
        if ((M519Bld *) s->bld[var_r31] != NULL) {
            fn_1_C3C8(s->bld[var_r31]);
            fn_1_CBEC(s->bld[var_r31]);
        }
        var_r31 += 1;
        goto loop_4;
    }
}

M519Mech *fn_1_297C(s16 type, s16 idx) {
    M519Mech *temp_r3;
    s32 var_r30;
    s32 var_r30_2;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Mech), MEMORY_DEFAULT_NUM);
    temp_r3->type = type;
    temp_r3->lastHitter = -1;
    temp_r3->player = 0;
    temp_r3->idx = idx;
    temp_r3->shootWait = 0;
    temp_r3->dmgStage = 0;
    temp_r3->speed = 0.0f;
    temp_r3->turn = 0.0f;
    temp_r3->tgtSpeed = 0.0f;
    temp_r3->tgtTurn = 0.0f;
    temp_r3->speedScale = lbl_1_rodata_9D8[type].speedScale;
    temp_r3->turnScale = lbl_1_rodata_9D8[type].turnScale;
    temp_r3->motState = 1;
    temp_r3->motPrev = 0;
    temp_r3->pos.x = 0.0f;
    temp_r3->pos.y = 0.0f;
    temp_r3->pos.z = 0.0f;
    temp_r3->rot.x = 0.0f;
    temp_r3->rot.y = 0.0f;
    temp_r3->rot.z = 0.0f;
    temp_r3->chargeA = 0;
    temp_r3->chargeB = 0;
    temp_r3->inputOn = 0;
    temp_r3->turning = 0;
    temp_r3->camFollow = 1;
    temp_r3->aim = 0.0f;
    temp_r3->radius = lbl_1_rodata_9D8[type].radius;
    temp_r3->hpMax = lbl_1_rodata_9D8[type].hp;
    temp_r3->hp = temp_r3->hpMax;
    temp_r3->hpShow = temp_r3->hpMax;
    temp_r3->part[0] = NULL;
    temp_r3->part[1] = NULL;
    temp_r3->push = 0.0f;
    temp_r3->pushDir = 0.0f;
    temp_r3->aiHasTgt = 0;
    temp_r3->aiMode = 0;
    temp_r3->aiSub = 0;
    temp_r3->fireCool = 0;
    temp_r3->aiFire = 0;
    temp_r3->sfx = -1;
    temp_r3->hitSame = 0;
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 9) {
        if ((s32) lbl_1_rodata_958[type].n[var_r30] != -1) {
            temp_r3->mdl[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_958[type].n[var_r30], MEMORY_DEFAULT_NUM, HEAP_DATA));
            Hu3DModelAttrSet(temp_r3->mdl[var_r30], 0x4000U);
        } else {
            temp_r3->mdl[var_r30] = -1;
        }
        var_r30 += 1;
        goto loop_5;
    }
    switch (type) {                                 /* irregular */
    case 0:
        Hu3DModelAttrSet(temp_r3->mdl[6], 2U);
        Hu3DModelAttrSet(temp_r3->mdl[6], 0x40000002U);
        Hu3DModelAttrSet(temp_r3->mdl[7], 0x40000002U);
        Hu3DModelAttrSet(temp_r3->mdl[8], 0x40000002U);
        Hu3DModelAttrSet(temp_r3->mdl[0], 2U);
        Hu3DModelAttrSet(temp_r3->mdl[1], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[2], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[3], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[4], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[7], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[8], 1U);
        Hu3DModelLayerSet(temp_r3->mdl[0], 2);
        Hu3DModelLayerSet(temp_r3->mdl[1], 2);
        Hu3DModelLayerSet(temp_r3->mdl[2], 2);
        Hu3DModelLayerSet(temp_r3->mdl[3], 2);
        Hu3DModelLayerSet(temp_r3->mdl[4], 2);
        Hu3DModelLayerSet(temp_r3->mdl[5], 2);
        Hu3DModelLayerSet(temp_r3->mdl[6], 2);
        Hu3DModelLayerSet(temp_r3->mdl[7], 2);
        Hu3DModelLayerSet(temp_r3->mdl[8], 2);
        break;
    case 1:
        Hu3DModelAttrSet(temp_r3->mdl[2], 0x40000001U);
        Hu3DModelAttrSet(temp_r3->mdl[0], 2U);
        Hu3DModelAttrSet(temp_r3->mdl[3], 0x400000U);
        Hu3DModelAttrSet(temp_r3->mdl[1], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[4], 0x40000002U);
        Hu3DModelAttrSet(temp_r3->mdl[4], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[5], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[6], 1U);
        Hu3DModelLayerSet(temp_r3->mdl[0], 2);
        Hu3DModelLayerSet(temp_r3->mdl[1], 2);
        Hu3DModelLayerSet(temp_r3->mdl[2], 2);
        Hu3DModelLayerSet(temp_r3->mdl[4], 2);
        Hu3DModelLayerSet(temp_r3->mdl[5], 2);
        Hu3DModelLayerSet(temp_r3->mdl[6], 2);
        Hu3DModelLayerSet(temp_r3->mdl[3], 7);
        Hu3DModelCameraSet(temp_r3->mdl[3], (u16) lbl_1_rodata_10[idx]);
        break;
    }
    var_r30_2 = 0;
loop_14:
    if (var_r30_2 < 7) {
        temp_r3->mot[var_r30_2] = Hu3DJointMotion(temp_r3->mdl[0], HuDataSelHeapReadNum(lbl_1_rodata_9A0[type].n[var_r30_2], MEMORY_DEFAULT_NUM, HEAP_DATA));
        var_r30_2 += 1;
        goto loop_14;
    }
    fn_1_2FA0(temp_r3, 0, 1.0f);
    if (type != 1) {
        if (type < 1) {

        }
    } else {
        temp_r3->part[0] = fn_1_CC44();
        fn_1_CDF4(temp_r3->part[0]);
        temp_r3->part[1] = fn_1_CC44();
        fn_1_CDF4(temp_r3->part[1]);
    }
    temp_r3->proc = HuPrcChildCreate(fn_1_2F54, 0x800U, 0x2800U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    return temp_r3;
}

void fn_1_2F54(void) {
    M519Mech *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_20[temp_r31->type][temp_r31->state](temp_r31);
    }
}

void fn_1_2FA0(M519Mech *m, s16 motState, f32 speed) {
    f32 sp8;

    sp8 = speed;
    if ((s16) m->motPrev != (s16) m->motState) {
        Hu3DMotionShiftSet(m->mdl[0], m->mot[motState], lbl_1_rodata_9F8[m->type].mot[motState].start, lbl_1_rodata_9F8[m->type].mot[motState].time, lbl_1_rodata_9F8[m->type].mot[motState].attr);
        m->motPrev = m->motState;
        m->stepAcc = 0.0f;
    }
    m->motState = motState;
    Hu3DMotionSpeedSet(m->mdl[0], sp8);
}


void fn_1_3138(M519Mech *m, Vec *pos) {
    s16 temp_r0;
    s32 var_r29;

    m->prevPos.x = m->pos.x;
    m->prevPos.y = m->pos.y;
    m->prevPos.z = m->pos.z;
    m->pos.x = pos->x;
    m->pos.y = pos->y;
    m->pos.z = pos->z;
    var_r29 = 0;
loop_4:
    if (var_r29 < 9) {
        if ((s16) m->mdl[var_r29] != -1) {
            Hu3DModelPosSet(m->mdl[var_r29], pos->x, pos->y, pos->z);
        }
        var_r29 += 1;
        goto loop_4;
    }
    temp_r0 = m->type;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelPosSet(m->mdl[5], pos->x, 8.0f + pos->y, pos->z);
        return;
    case 1:
        Hu3DModelPosSet(m->mdl[2], pos->x, 8.0f + pos->y, pos->z);
        Hu3DModelPosSet(m->mdl[3], pos->x, 180.0f + pos->y, pos->z);
        return;
    }
}


void fn_1_3290(M519Mech *m, Vec *rot) {
    f32 *temp_r28;
    f32 var_f31;
    f64 var_f30;
    s16 temp_r0;
    s32 var_r30;

    m->prevRot.x = m->rot.x;
    m->prevRot.y = m->rot.y;
    m->prevRot.z = m->rot.z;
    m->rot.x = rot->x;
    m->rot.y = rot->y;
    m->rot.z = rot->z;
    var_r30 = 0;
loop_8:
    if (var_r30 < 9) {
        if ((((s16) m->type != 1) || (var_r30 != 2)) && (((s16) m->type != 0) || (var_r30 != 5)) && ((s16) m->mdl[var_r30] != -1)) {
            temp_r28 = Hu3DData[m->mdl[var_r30]].mtx[0];
            MTXIdentity((f32 (*)[4]) temp_r28);
            MTXRotRad((f32 (*)[4]) temp_r28, 0x7A, 0.017453292f * rot->z);
            Hu3DModelRotSet(m->mdl[var_r30], rot->x, rot->y, 0.0f);
        }
        var_r30 += 1;
        goto loop_8;
    }
    temp_r0 = m->type;
    if (temp_r0 != 1) {
        if (temp_r0 < 1) {

        }
    } else {
        MTXIdentity((f32 (*)[4]) Hu3DData[m->mdl[3]].mtx[0]);
        if (fmod((f64) (m->rot.y - m->aim), 360.0) < 0.0f) {
            var_f30 = -fmod((f64) (m->rot.y - m->aim), 360.0);
        } else {
            var_f30 = fmod((f64) (m->rot.y - m->aim), 360.0);
        }
        var_f31 = (f32) var_f30;
        if (var_f31 > 180.0f) {
            var_f31 = 180.0f - (var_f31 - 180.0f);
        }
        Hu3DModelRotSet(m->mdl[3], -45.0f + (0.5f * var_f31), m->aim, 0.0f);
    }
}


void fn_1_3518(M519Mech *m, M519Player *p) {
    Hu3DModelHookSet(m->mdl[0], lbl_1_data_14[m->type], p->mdl[1]);
    m->player = p->idx;
    p->mech = m->idx;
}


void fn_1_35B0(M519Mech *m) {
    m->state = 0;
}

void fn_1_35BC(M519Mech *m) {
    s16 temp_r28;
    s16 temp_r30;
    s32 var_r31;

loop_1:
    fn_1_95B0(m);
    fn_1_9700(m);
    fn_1_8450(m);
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r30 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r30;
    if (temp_r30 == temp_r28) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_3658(M519Mech *m) {
    m->state = 1;
}

void fn_1_3664(M519Mech *m) {
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
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
    f32 temp_f22;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f18;
    f32 var_f19;
    f32 var_f20;
    f32 var_f21;
    f32 var_f23;
    f32 var_f24;
    f32 var_f28;
    f32 var_f29;
    f64 temp_f27;
    f64 temp_f27_2;
    f64 temp_f27_3;
    s16 temp_r27;
    s16 temp_r28;
    s32 var_r29;
    s32 var_r30;

    var_r29 = 0;
loop_1:
    m->stickX = 0;
    m->stickY = 0;
    m->trigL = 0;
    m->trigR = 0;
    m->btn = 0;
    m->btnDown = 0;
    if ((s16) m->hp > 0) {
        if ((s32) m->inputOn != 0) {
            if ((s32) lbl_1_bss_E8[m->player]->isCom != 0) {
                fn_1_4E18(m);
            } else {
                fn_1_4D40(m);
            }
        }
        goto block_10;
    }
    if (var_r29 == 0) {
        HuAudFXPlayPan(lbl_1_rodata_164[Mp5CharNo(lbl_1_bss_E8[m->player]->charNo)], (s16) lbl_1_rodata_1C[m->type]);
        HuAudFXPlay(0x71E);
        Hu3DModelAttrReset(m->mdl[8], 1U);
        Hu3DModelAttrReset(m->mdl[8], 0x40000002U);
        Hu3DModelAttrSet(m->mdl[8], 0x40000001U);
        Hu3DMotionTimeSet(m->mdl[8], 0.0f);
        fn_1_FD7C(m->player, 2, 0x3C);
        var_r29 = 1;
        goto block_10;
    }
    if (m->speed <= 0.0f) {
        fn_1_817C(m);
        return;
    }
block_10:
    if (((s16) m->trigR >= 0x96) || ((s16) m->trigL >= 0x96)) {
        if ((s32) m->turning == 0) {
            m->turning = 1;
            m->speed = 0.0f;
            m->turn = 0.0f;
        }
        temp_f31 = (f32) m->stickX * -m->speedScale;
        temp_f30 = (f32) m->stickY * m->speedScale;
        temp_f22 = (f32) (180.0 * (atan2((f64) temp_f31, (f64) temp_f30) / 3.141592653589793));
        var_f21 = sqrtf(((temp_f31 * temp_f31) + (temp_f30 * temp_f30)));
        var_f24 = (f32) ((f64) var_f21 * sin((3.141592653589793 * (f64) (temp_f22 + m->rot.y)) / 180.0));
        var_f23 = (f32) ((f64) var_f21 * cos((3.141592653589793 * (f64) (temp_f22 + m->rot.y)) / 180.0));
        m->speed = var_f21;
        var_f28 = 0.0f;
        if (temp_f30 > 0.0f) {
            if (temp_f31 < 0.0f) {
                var_f20 = -temp_f31;
            } else {
                var_f20 = temp_f31;
            }
            if (temp_f30 < 0.0f) {
                var_f19 = -temp_f30;
            } else {
                var_f19 = temp_f30;
            }
            if (var_f19 > var_f20) {
                if ((s16) m->motPrev != (s16) m->motState) {
                    Hu3DMotionShiftSet(m->mdl[0], m->mot[1], lbl_1_rodata_9F8[m->type].mot[1].start, lbl_1_rodata_9F8[m->type].mot[1].time, lbl_1_rodata_9F8[m->type].mot[1].attr);
                    m->motPrev = m->motState;
                    m->stepAcc = 0.0f;
                }
                m->motState = 1;
                if ((0.5f * temp_f30) < 0.0f) {
                    var_f18 = -(0.5f * temp_f30);
                } else {
                    var_f18 = 0.5f * temp_f30;
                }
                Hu3DMotionSpeedSet(m->mdl[0], 1.0f + var_f18);
            } else {
                goto block_31;
            }
        } else {
block_31:
            if (temp_f30 < 0.0f) {
                if (temp_f31 < 0.0f) {
                    sp54 = -temp_f31;
                } else {
                    sp54 = temp_f31;
                }
                if (temp_f30 < 0.0f) {
                    sp50 = -temp_f30;
                } else {
                    sp50 = temp_f30;
                }
                if (sp50 > sp54) {
                    if ((s16) m->motPrev != (s16) m->motState) {
                        Hu3DMotionShiftSet(m->mdl[0], m->mot[2], lbl_1_rodata_9F8[m->type].mot[2].start, lbl_1_rodata_9F8[m->type].mot[2].time, lbl_1_rodata_9F8[m->type].mot[2].attr);
                        m->motPrev = m->motState;
                        m->stepAcc = 0.0f;
                    }
                    m->motState = 2;
                    if ((0.5f * temp_f30) < 0.0f) {
                        sp4C = -(0.5f * temp_f30);
                    } else {
                        sp4C = 0.5f * temp_f30;
                    }
                    Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp4C);
                } else {
                    goto block_45;
                }
            } else {
block_45:
                if (temp_f31 < 0.0f) {
                    if ((s16) m->motPrev != (s16) m->motState) {
                        Hu3DMotionShiftSet(m->mdl[0], m->mot[3], lbl_1_rodata_9F8[m->type].mot[3].start, lbl_1_rodata_9F8[m->type].mot[3].time, lbl_1_rodata_9F8[m->type].mot[3].attr);
                        m->motPrev = m->motState;
                        m->stepAcc = 0.0f;
                    }
                    m->motState = 3;
                    if ((0.5f * temp_f31) < 0.0f) {
                        sp48 = -(0.5f * temp_f31);
                    } else {
                        sp48 = 0.5f * temp_f31;
                    }
                    Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp48);
                } else if (temp_f31 > 0.0f) {
                    if ((s16) m->motPrev != (s16) m->motState) {
                        Hu3DMotionShiftSet(m->mdl[0], m->mot[4], lbl_1_rodata_9F8[m->type].mot[4].start, lbl_1_rodata_9F8[m->type].mot[4].time, lbl_1_rodata_9F8[m->type].mot[4].attr);
                        m->motPrev = m->motState;
                        m->stepAcc = 0.0f;
                    }
                    m->motState = 4;
                    if ((0.5f * temp_f31) < 0.0f) {
                        sp44 = -(0.5f * temp_f31);
                    } else {
                        sp44 = 0.5f * temp_f31;
                    }
                    Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp44);
                } else {
                    if ((s16) m->motPrev != (s16) m->motState) {
                        Hu3DMotionShiftSet(m->mdl[0], m->mot[0], lbl_1_rodata_9F8[m->type].mot[0].start, lbl_1_rodata_9F8[m->type].mot[0].time, lbl_1_rodata_9F8[m->type].mot[0].attr);
                        m->motPrev = m->motState;
                        m->stepAcc = 0.0f;
                    }
                    m->motState = 0;
                    Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
                }
            }
        }
        if (temp_f30 != 0.0f) {
            if (temp_f31 < 0.0f) {
                sp40 = -temp_f31;
            } else {
                sp40 = temp_f31;
            }
            if (temp_f30 < 0.0f) {
                sp3C = -temp_f30;
            } else {
                sp3C = temp_f30;
            }
            if (sp3C > sp40) {
                if (m->stepAcc >= 0.0f) {
                    if ((0.5f * temp_f30) < 0.0f) {
                        sp38 = -(0.5f * temp_f30);
                    } else {
                        sp38 = 0.5f * temp_f30;
                    }
                    if (m->stepAcc < sp38) {
                        HuAudFXPlayPan(0x70B, (s16) lbl_1_rodata_18[m->type]);
                    }
                }
                if ((0.5f * temp_f30) < 0.0f) {
                    sp34 = -(0.5f * temp_f30);
                } else {
                    sp34 = 0.5f * temp_f30;
                }
                m->stepAcc += 1.0f + sp34;
            } else {
                goto block_80;
            }
        } else {
block_80:
            if (temp_f31 != 0.0f) {
                if (m->stepAcc >= 0.0f) {
                    if ((0.5f * temp_f31) < 0.0f) {
                        sp30 = -(0.5f * temp_f31);
                    } else {
                        sp30 = 0.5f * temp_f31;
                    }
                    if (m->stepAcc < sp30) {
                        HuAudFXPlayPan(0x70B, (s16) lbl_1_rodata_18[m->type]);
                    }
                }
                if ((0.5f * temp_f31) < 0.0f) {
                    sp2C = -(0.5f * temp_f31);
                } else {
                    sp2C = 0.5f * temp_f31;
                }
                m->stepAcc += 1.0f + sp2C;
            }
        }
        if (m->stepAcc >= 80.0f) {
            m->stepAcc = 0.0f;
        }
    } else {
        if ((s32) m->turning != 0) {
            m->turning = 0;
            m->speed = 0.0f;
        }
        var_f28 = m->turn;
        var_f29 = m->speed;
        m->tgtTurn = (f32) m->stickX * -m->turnScale;
        m->tgtSpeed = (f32) m->stickY * m->speedScale;
        if (var_f28 < m->tgtTurn) {
            var_f28 += 0.2f;
            if (var_f28 > m->tgtTurn) {
                var_f28 = m->tgtTurn;
            }
        }
        if (var_f28 > m->tgtTurn) {
            var_f28 -= 0.2f;
            if (var_f28 < m->tgtTurn) {
                var_f28 = m->tgtTurn;
            }
        }
        if (var_f29 < m->tgtSpeed) {
            var_f29 += 0.2f;
            if (var_f29 > m->tgtSpeed) {
                var_f29 = m->tgtSpeed;
            }
        }
        if (var_f29 > m->tgtSpeed) {
            var_f29 -= 0.2f;
            if (var_f29 < m->tgtSpeed) {
                var_f29 = m->tgtSpeed;
            }
        }
        var_f24 = (f32) ((f64) var_f29 * sin((3.141592653589793 * (f64) m->rot.y) / 180.0));
        var_f23 = (f32) ((f64) var_f29 * cos((3.141592653589793 * (f64) m->rot.y) / 180.0));
        m->turn = var_f28;
        m->speed = var_f29;
        if (var_f29 > 0.0f) {
            if ((s16) m->motPrev != (s16) m->motState) {
                Hu3DMotionShiftSet(m->mdl[0], m->mot[1], lbl_1_rodata_9F8[m->type].mot[1].start, lbl_1_rodata_9F8[m->type].mot[1].time, lbl_1_rodata_9F8[m->type].mot[1].attr);
                m->motPrev = m->motState;
                m->stepAcc = 0.0f;
            }
            m->motState = 1;
            if ((0.5f * var_f29) < 0.0f) {
                sp28 = -(0.5f * var_f29);
            } else {
                sp28 = 0.5f * var_f29;
            }
            Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp28);
        } else if (var_f29 < 0.0f) {
            if ((s16) m->motPrev != (s16) m->motState) {
                Hu3DMotionShiftSet(m->mdl[0], m->mot[2], lbl_1_rodata_9F8[m->type].mot[2].start, lbl_1_rodata_9F8[m->type].mot[2].time, lbl_1_rodata_9F8[m->type].mot[2].attr);
                m->motPrev = m->motState;
                m->stepAcc = 0.0f;
            }
            m->motState = 2;
            if ((0.5f * var_f29) < 0.0f) {
                sp24 = -(0.5f * var_f29);
            } else {
                sp24 = 0.5f * var_f29;
            }
            Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp24);
        } else if (var_f28 != 0.0f) {
            if ((s16) m->motPrev != (s16) m->motState) {
                Hu3DMotionShiftSet(m->mdl[0], m->mot[1], lbl_1_rodata_9F8[m->type].mot[1].start, lbl_1_rodata_9F8[m->type].mot[1].time, lbl_1_rodata_9F8[m->type].mot[1].attr);
                m->motPrev = m->motState;
                m->stepAcc = 0.0f;
            }
            m->motState = 1;
            if ((0.5f * var_f28) < 0.0f) {
                sp20 = -(0.5f * var_f28);
            } else {
                sp20 = 0.5f * var_f28;
            }
            Hu3DMotionSpeedSet(m->mdl[0], 1.0f + sp20);
        } else {
            if ((s16) m->motPrev != (s16) m->motState) {
                Hu3DMotionShiftSet(m->mdl[0], m->mot[0], lbl_1_rodata_9F8[m->type].mot[0].start, lbl_1_rodata_9F8[m->type].mot[0].time, lbl_1_rodata_9F8[m->type].mot[0].attr);
                m->motPrev = m->motState;
                m->stepAcc = 0.0f;
            }
            m->motState = 0;
            Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
        }
        if (var_f29 != 0.0f) {
            if (m->stepAcc >= 0.0f) {
                if ((0.5f * var_f29) < 0.0f) {
                    sp1C = -(0.5f * var_f29);
                } else {
                    sp1C = 0.5f * var_f29;
                }
                if (!(m->stepAcc < sp1C)) {
                    goto block_137;
                }
                goto block_142;
            }
block_137:
            if (m->stepAcc >= 39.0f) {
                if ((0.5f * var_f29) < 0.0f) {
                    sp18 = -(0.5f * var_f29);
                } else {
                    sp18 = 0.5f * var_f29;
                }
                if (m->stepAcc < (39.0f + sp18)) {
block_142:
                    HuAudFXPlayPan(0x70A, (s16) lbl_1_rodata_18[m->type]);
                }
            }
            if ((0.5f * var_f29) < 0.0f) {
                sp14 = -(0.5f * var_f29);
            } else {
                sp14 = 0.5f * var_f29;
            }
            m->stepAcc += 1.0f + sp14;
        }
        if (var_f28 != 0.0f) {
            if (m->stepAcc >= 0.0f) {
                if ((0.5f * var_f28) < 0.0f) {
                    sp10 = -(0.5f * var_f28);
                } else {
                    sp10 = 0.5f * var_f28;
                }
                if (!(m->stepAcc < sp10)) {
                    goto block_153;
                }
                goto block_158;
            }
block_153:
            if (m->stepAcc >= 39.0f) {
                if ((0.5f * var_f28) < 0.0f) {
                    spC = -(0.5f * var_f28);
                } else {
                    spC = 0.5f * var_f28;
                }
                if (m->stepAcc < (39.0f + spC)) {
block_158:
                    HuAudFXPlayPan(0x70A, (s16) lbl_1_rodata_18[m->type]);
                }
            }
            if ((0.5f * var_f28) < 0.0f) {
                sp8 = -(0.5f * var_f28);
            } else {
                sp8 = 0.5f * var_f28;
            }
            m->stepAcc += 1.0f + sp8;
        }
        if (m->stepAcc >= 80.0f) {
            m->stepAcc = 0.0f;
        }
    }
    m->pos.x += var_f24;
    m->pos.z += var_f23;
    m->rot.y += var_f28;
    fn_1_82E4(m);
    fn_1_95B0(m);
    fn_1_9700(m);
    fn_1_8450(m);
    fn_1_8E40(m);
    var_r30 = 0;
loop_168:
    if (var_r30 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r27 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r28;
    if (temp_r28 == temp_r27) {
        var_r30 += 1;
        goto loop_168;
    }
}

void fn_1_4D40(M519Mech *m) {
    s16 temp_r31;

    temp_r31 = lbl_1_bss_E8[m->player]->pad;
    m->stickX = (s16) (s8) (u8) HuPadStkX[temp_r31];
    m->stickY = (s16) (s8) (u8) HuPadStkY[temp_r31];
    m->trigL = (s16) HuPadTrigL[temp_r31];
    m->trigR = (s16) HuPadTrigR[temp_r31];
    m->btn = (s16) HuPadBtn[temp_r31];
    m->btnDown = (s16) HuPadBtnDown[temp_r31];
}

void fn_1_4E18(M519Mech *m) {
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
    M519Mech *temp_r30;
    M519Mech *temp_r30_2;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    f32 var_f18;
    f32 var_f19;
    f32 var_f21;
    f32 var_f25;
    f32 var_f25_2;
    f32 var_f29;
    f64 temp_f22;
    f64 temp_f22_2;
    f64 temp_f22_3;
    f64 temp_f23;
    f64 temp_f23_2;
    f64 temp_f23_3;
    f64 temp_f24;
    f64 temp_f24_2;
    f64 temp_f24_3;
    f64 temp_f26;
    f64 temp_f26_2;
    f64 temp_f26_3;
    f64 temp_f26_4;
    f64 var_f20;
    s16 temp_r0;
    s16 temp_r29;
    s16 temp_r3;
    s16 temp_r4;
    s16 temp_r4_2;
    s16 var_r26;
    s16 var_r27;
    s32 var_r25;
    s32 var_r28;

    temp_r29 = lbl_1_bss_E8[m->player]->dif;
    sp34 = m->pos.x;
    sp38 = m->pos.z;
    sp3C = m->radius;
    temp_r3 = m->aiMode;
    switch (temp_r3) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if ((s32) m->aiHasTgt == 0) {
            temp_f27 = (f32) frandmod((u32) (2390.0f - m->radius));
            temp_f29 = (f32) (frand() % 360);
            m->aiX = (f32) ((f64) temp_f27 * sin((3.141592653589793 * (f64) temp_f29) / 180.0));
            m->aiZ = (f32) ((f64) temp_f27 * cos((3.141592653589793 * (f64) temp_f29) / 180.0));
            m->aiY = 0.0f;
            m->aiTimer = 0;
            m->aiPush = (frand() % 20) + 0x32;
            m->aiHasTgt = 1;
        }
        temp_f31 = m->aiX - m->pos.x;
        temp_f30 = m->aiZ - m->pos.z;
        sp30 = sqrtf(((temp_f31 * temp_f31) + (temp_f30 * temp_f30)));
        if ((sp30 < 300.0f) || (temp_r4 = m->aiTimer, m->aiTimer = temp_r4 + 1, ((temp_r4 > (s32) lbl_1_rodata_AE0[temp_r29]) != 0))) {
            m->aiPush = 0;
            m->aiMode = 1;
            m->aiTimer = 0;
            m->aiHasTgt = 0;
            m->aiTarget = frandmod(3U) + 1;
        } else {
            m->btnDown |= 0x100;
        }
        break;
    case 1:                                         /* switch 1 */
        var_r26 = 0;
        var_f21 = 4780.0f;
        var_f18 = 360.0f;
        var_r25 = 0;
        var_r27 = 0;
        var_f19 = 0.0f;
        if ((s16) m->aiTimer > 0) {
            m->aiTimer -= 1;
        }
        var_r28 = 0;
loop_44:
        if (var_r28 < 3) {
            temp_r30 = lbl_1_bss_F8[var_r28 + 1];
            if (fn_1_A1D4(temp_r30) == 0) {
                var_r27 += 1;
                temp_f31_2 = temp_r30->pos.x - m->pos.x;
                temp_f30_2 = temp_r30->pos.z - m->pos.z;
                sp28 = sqrtf(((temp_f31_2 * temp_f31_2) + (temp_f30_2 * temp_f30_2)));
                var_f19 += sp28;
                var_f29 = (f32) ((180.0 + (180.0 * (atan2((f64) (m->pos.x - temp_r30->pos.x), (f64) (m->pos.z - temp_r30->pos.z)) / 3.141592653589793))) - (f64) m->rot.y);
                if (var_f29 < 0.0f) {
                    var_f29 += 360.0f;
                }
                if (var_f29 >= 360.0f) {
                    var_f29 -= 360.0f;
                }
                if (var_f29 >= 180.0f) {
                    var_f29 -= 360.0f;
                }
                temp_f29_2 = -var_f29;
                if (temp_f29_2 < 0.0f) {
                    sp18 = -temp_f29_2;
                } else {
                    sp18 = temp_f29_2;
                }
                if (var_f18 > sp18) {
                    if (temp_f29_2 < 0.0f) {
                        sp14 = -temp_f29_2;
                    } else {
                        sp14 = temp_f29_2;
                    }
                    var_f18 = sp14;
                    if (sp28 < 2000.0f) {
                        var_r26 = var_r28 + 1;
                    }
                }
                if (var_f21 > sp28) {
                    var_f21 = sp28;
                }
                if (temp_f29_2 < 0.0f) {
                    sp10 = -temp_f29_2;
                } else {
                    sp10 = temp_f29_2;
                }
                if (sp10 < lbl_1_rodata_AF0[temp_r29]) {
                    var_r25 = 1;
                }
            }
            var_r28 += 1;
            goto loop_44;
        }
        if (var_r27 != 0) {
            if ((s16) m->aiTimer == 0) {
                if (var_r26 > 0) {
                    m->aiTarget = var_r26;
                }
                if (fn_1_A1D4(lbl_1_bss_F8[m->aiTarget]) == 0) {
                    m->aiTimer = lbl_1_rodata_B00[temp_r29];
                } else {
                    m->aiTarget = frandmod(3U) + 1;
                }
            }
            temp_r30_2 = lbl_1_bss_F8[m->aiTarget];
            m->aiX = temp_r30_2->pos.x;
            m->aiY = temp_r30_2->pos.y;
            m->aiZ = temp_r30_2->pos.z;
            temp_f31_3 = m->aiX - m->pos.x;
            temp_f30_3 = m->aiZ - m->pos.z;
            sp20 = sqrtf(((temp_f31_3 * temp_f31_3) + (temp_f30_3 * temp_f30_3)));
            if (sp20 > 500.0f) {
                m->aiPush = -(s16) (0.015 * (f64) sp20);
            }
            if (sp20 < 2000.0f) {
                m->aiPush = 0;
            } else {
                m->aiPush = (s16) (0.015 * (f64) sp20);
            }
            temp_r0 = m->aiSub;
            switch (temp_r0) {                      /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                if (var_r25 != 0) {
                    m->btnDown |= 0x100;
                    m->aiTimer2 = 0;
                    if (var_f21 < (f32) lbl_1_rodata_B08[temp_r29]) {
                        m->aiSub = 2;
                    }
                } else {
                    temp_r4_2 = m->aiTimer2;
                    m->aiTimer2 = temp_r4_2 + 1;
                    if (temp_r4_2 > (s16) lbl_1_rodata_B28[temp_r29]) {
                        if ((var_f19 / (f32) var_r27) > (f32) lbl_1_rodata_B18[temp_r29]) {
                            m->aiSub = 1;
                        } else {
                            m->aiSub = 3;
                        }
                    }
                }
                break;
            case 1:                                 /* switch 2 */
                if ((var_r25 != 0) && ((s16) m->chargeA > 0x5A)) {
                    m->aiSub = 0;
                } else {
                    m->btn |= 0x100;
                }
                break;
            case 2:                                 /* switch 2 */
                m->btnDown |= 0x200;
                if (var_f21 > (f32) lbl_1_rodata_B30[temp_r29]) {
                    m->aiSub = 0;
                }
                break;
            case 3:                                 /* switch 2 */
                if ((s16) m->chargeB > 0x5A) {
                    m->aiSub = 0;
                } else {
                    m->btn |= 0x200;
                }
                break;
            }
        }
        break;
    }
    if ((s16) m->fireCool > 0) {
        m->fireCool -= 1;
        m->btnDown &= 0xFFFFFEFF;
    } else if ((s32) (m->btnDown & 0x100) != 0) {
        m->fireCool = lbl_1_rodata_B40[temp_r29] + 8;
    }
    var_f25 = 0.0f;
    if ((m->aiX != m->pos.x) || (m->aiZ != m->pos.z)) {
        var_f25_2 = (f32) ((180.0 + (180.0 * (atan2((f64) (m->pos.x - m->aiX), (f64) (m->pos.z - m->aiZ)) / 3.141592653589793))) - (f64) m->rot.y);
        if (var_f25_2 < 0.0f) {
            var_f25_2 += 360.0f;
        }
        if (var_f25_2 >= 360.0f) {
            var_f25_2 -= 360.0f;
        }
        if (var_f25_2 >= 180.0f) {
            var_f25_2 -= 360.0f;
        }
        var_f25 = -var_f25_2;
    }
    if (var_f25 > 60.0f) {
        spC = 60.0f;
    } else {
        spC = var_f25;
    }
    if (spC < -60.0f) {
        sp8 = -60.0f;
    } else {
        sp8 = spC;
    }
    temp_f31_4 = sp8 * (f32) (s16) (68.0f / lbl_1_rodata_B48[temp_r29]);
    temp_f28 = (f32) m->aiPush;
    var_f20 = sqrtf(((temp_f31_4 * temp_f31_4) + (temp_f28 * temp_f28)));
    temp_f27_2 = (f32) var_f20;
    temp_f29_3 = (f32) (180.0 * (atan2((f64) temp_f31_4, (f64) temp_f28) / 3.141592653589793));
    temp_f31_5 = (f32) ((f64) temp_f27_2 * sin((3.141592653589793 * (f64) temp_f29_3) / 180.0));
    temp_f28_2 = (f32) ((f64) temp_f27_2 * cos((3.141592653589793 * (f64) temp_f29_3) / 180.0));
    m->stickX = (s16) temp_f31_5;
    m->stickY = (s16) temp_f28_2;
}

void fn_1_5EDC(M519Mech *m) {
    s16 spA;
    s16 sp8;
    f32 temp_f23;
    f32 temp_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f30;
    f32 var_f31;
    s16 temp_r27;
    s16 temp_r28;
    s16 temp_r3;
    s32 var_r29;
    s32 var_r30;

    var_r29 = 0;
    spA = lbl_1_bss_E8[m->player]->pad;
    sp8 = lbl_1_bss_E8[m->player]->idx;
loop_1:
    var_f30 = m->turn;
    var_f31 = m->speed;
    m->stickX = 0;
    m->stickY = 0;
    m->trigL = 0;
    m->trigR = 0;
    m->btn = 0;
    m->btnDown = 0;
    if ((s16) m->hp > 0) {
        if ((s32) m->inputOn != 0) {
            if ((s32) lbl_1_bss_E8[m->player]->isCom != 0) {
                fn_1_69BC(m);
            } else {
                fn_1_68E4(m);
            }
        }
        goto block_10;
    }
    if (var_r29 == 0) {
        HuAudFXPlay(lbl_1_rodata_164[Mp5CharNo(lbl_1_bss_E8[m->player]->charNo)]);
        HuAudFXPlay(0x71F);
        Hu3DModelAttrReset(m->mdl[4], 1U);
        Hu3DModelAttrReset(m->mdl[4], 0x40000002U);
        Hu3DModelAttrSet(m->mdl[4], 0x40000001U);
        Hu3DMotionTimeSet(m->mdl[4], 0.0f);
        fn_1_FD7C(m->player, 2, 0x3C);
        var_r29 = 1;
        goto block_10;
    }
    if (m->speed <= 0.0f) {
        fn_1_817C(m);
        return;
    }
block_10:
    m->tgtTurn = (f32) m->stickX * -m->turnScale;
    m->tgtSpeed = (f32) m->stickY * m->speedScale;
    if ((s32) (m->btn & 0x200) != 0) {
        temp_r3 = m->chargeB;
        m->chargeB = temp_r3 + 1;
        if (temp_r3 == 0) {
            if ((s32) m->sfx != -1) {
                HuAudFXStop(m->sfx);
            }
            m->sfx = HuAudFXPlay(0x721);
            Hu3DModelAttrReset(m->mdl[5], 1U);
            Hu3DMotionStartEndSet(m->mdl[5], 0.0f, 60.0f);
            Hu3DMotionTimeSet(m->mdl[5], 0.0f);
            Hu3DModelAttrSet(m->mdl[5], 0x40000001U);
        } else if ((s16) m->chargeB == 0x28) {
            Hu3DMotionStartEndSet(m->mdl[5], 40.0f, 60.0f);
            Hu3DMotionTimeSet(m->mdl[5], 0.0f);
            Hu3DModelAttrSet(m->mdl[5], 0x40000001U);
        }
        if (((s16) m->chargeB >= 0x28) && ((s32) (m->chargeB % 5) == 0)) {
            fn_1_FD7C(m->player, 1, 3);
        }
    } else if ((s16) m->chargeB > 0) {
        Hu3DModelAttrSet(m->mdl[5], 1U);
        if ((s32) m->sfx != -1) {
            HuAudFXStop(m->sfx);
            m->sfx = -1;
        }
        if ((s16) m->chargeB >= 0x5A) {
            HuAudFXPlayPan(0x71D, (s16) lbl_1_rodata_18[m->type]);
            Hu3DMotionStartEndSet(m->mdl[6], 0.0f, 60.0f);
            Hu3DMotionTimeSet(m->mdl[6], 0.0f);
            Hu3DModelAttrReset(m->mdl[6], 1U);
            m->tgtSpeed = 100.0f * m->speedScale;
            var_f31 = 100.0f * m->speedScale;
        }
        m->chargeB = 0;
    }
    if (var_f30 < m->tgtTurn) {
        var_f30 += 0.18f;
        if (var_f30 > m->tgtTurn) {
            var_f30 = m->tgtTurn;
        }
    }
    if (var_f30 > m->tgtTurn) {
        var_f30 -= 0.18f;
        if (var_f30 < m->tgtTurn) {
            var_f30 = m->tgtTurn;
        }
    }
    if (var_f31 < m->tgtSpeed) {
        var_f31 += 0.36f;
        if (var_f31 > m->tgtSpeed) {
            var_f31 = m->tgtSpeed;
        }
    }
    if (var_f31 > m->tgtSpeed) {
        var_f31 -= 0.36f;
        if (var_f31 < m->tgtSpeed) {
            var_f31 = m->tgtSpeed;
        }
    }
    m->rot.y += var_f30;
    if ((0.2f * var_f31) < 0.0f) {
        var_f27 = -(0.2f * var_f31);
    } else {
        var_f27 = 0.2f * var_f31;
    }
    m->rot.z = var_f30 * -var_f27;
    temp_f24 = (f32) ((f64) var_f31 * sin((3.141592653589793 * (f64) m->rot.y) / 180.0));
    temp_f23 = (f32) ((f64) var_f31 * cos((3.141592653589793 * (f64) m->rot.y) / 180.0));
    m->pos.x += temp_f24;
    m->pos.z += temp_f23;
    m->turn = var_f30;
    m->speed = var_f31;
    if (var_f31 > 0.0f) {
        if ((s16) m->motPrev != (s16) m->motState) {
            Hu3DMotionShiftSet(m->mdl[0], m->mot[1], lbl_1_rodata_9F8[m->type].mot[1].start, lbl_1_rodata_9F8[m->type].mot[1].time, lbl_1_rodata_9F8[m->type].mot[1].attr);
            m->motPrev = m->motState;
            m->stepAcc = 0.0f;
        }
        m->motState = 1;
        Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
    } else if (var_f31 < 0.0f) {
        if ((s16) m->motPrev != (s16) m->motState) {
            Hu3DMotionShiftSet(m->mdl[0], m->mot[2], lbl_1_rodata_9F8[m->type].mot[2].start, lbl_1_rodata_9F8[m->type].mot[2].time, lbl_1_rodata_9F8[m->type].mot[2].attr);
            m->motPrev = m->motState;
            m->stepAcc = 0.0f;
        }
        m->motState = 2;
        Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
    } else if (var_f30 != 0.0f) {
        if ((s16) m->motPrev != (s16) m->motState) {
            Hu3DMotionShiftSet(m->mdl[0], m->mot[1], lbl_1_rodata_9F8[m->type].mot[1].start, lbl_1_rodata_9F8[m->type].mot[1].time, lbl_1_rodata_9F8[m->type].mot[1].attr);
            m->motPrev = m->motState;
            m->stepAcc = 0.0f;
        }
        m->motState = 1;
        Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
    } else if (Hu3DMotionEndCheck(m->mdl[0]) != 0) {
        if ((s16) m->motPrev != (s16) m->motState) {
            Hu3DMotionShiftSet(m->mdl[0], m->mot[0], lbl_1_rodata_9F8[m->type].mot[0].start, lbl_1_rodata_9F8[m->type].mot[0].time, lbl_1_rodata_9F8[m->type].mot[0].attr);
            m->motPrev = m->motState;
            m->stepAcc = 0.0f;
        }
        m->motState = 0;
        Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
    }
    if (var_f31 < 0.0f) {
        var_f26 = -var_f31;
    } else {
        var_f26 = var_f31;
    }
    if (var_f26 > 16.0f) {
        fn_1_7998(m);
    }
    fn_1_82E4(m);
    fn_1_95B0(m);
    fn_1_9700(m);
    fn_1_8450(m);
    fn_1_8D40(m);
    if (var_f31 < 0.0f) {
        var_f25 = -var_f31;
    } else {
        var_f25 = var_f31;
    }
    if (var_f25 < 72.0f) {
        fn_1_8E40(m);
    }
    var_r30 = 0;
loop_70:
    if (var_r30 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r27 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r28;
    if (temp_r28 == temp_r27) {
        var_r30 += 1;
        goto loop_70;
    }
}

void fn_1_68E4(M519Mech *m) {
    s16 temp_r31;

    temp_r31 = lbl_1_bss_E8[m->player]->pad;
    m->stickX = (s16) (s8) (u8) HuPadStkX[temp_r31];
    m->stickY = (s16) (s8) (u8) HuPadStkY[temp_r31];
    m->trigL = (s16) HuPadTrigL[temp_r31];
    m->trigR = (s16) HuPadTrigR[temp_r31];
    m->btn = (s16) HuPadBtn[temp_r31];
    m->btnDown = (s16) HuPadBtnDown[temp_r31];
}

void fn_1_69BC(M519Mech *m) {
    Vec sp3C;
    Vec sp30;
    Vec sp24;
    s32 sp54;
    s32 sp50;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 var_f18;
    f32 var_f19;
    f32 var_f20;
    f32 var_f21;
    f32 var_f25;
    f32 var_f25_2;
    f32 var_f26;
    f32 var_f27;
    f32 var_f30;
    f64 temp_f22;
    f64 temp_f22_2;
    f64 temp_f22_3;
    f64 temp_f23;
    f64 temp_f23_2;
    f64 temp_f23_3;
    f64 temp_f24;
    f64 temp_f24_2;
    f64 temp_f24_3;
    s16 temp_r30;
    s16 temp_r3;
    s16 temp_r4_2;
    s16 temp_r5;
    s32 temp_r4;

    temp_r30 = lbl_1_bss_E8[m->player]->dif;
    sp3C.x = m->pos.x;
    sp3C.y = m->pos.z;
    sp3C.z = m->radius;
    temp_r3 = m->aiMode;
    switch (temp_r3) {                              /* irregular */
    case 0:
        if ((s32) m->aiHasTgt == 0) {
            temp_r4 = frand() % (s32) (2390.0f - (2.0f * m->radius));
            sp54 = temp_r4 ^ 0x80000000;
            sp50 = 0x43300000;
            temp_f27 = (f32) temp_r4;
            temp_f30 = (f32) (frand() % 360);
            m->aiX = (f32) ((f64) temp_f27 * sin((3.141592653589793 * (f64) temp_f30) / 180.0));
            m->aiZ = (f32) ((f64) temp_f27 * cos((3.141592653589793 * (f64) temp_f30) / 180.0));
            m->aiY = 0.0f;
            m->aiTimer = 0;
            m->aiPush = (frand() % 20) + 0x32;
            m->aiHasTgt = 1;
        }
        temp_f31 = m->aiX - m->pos.x;
        temp_f29 = m->aiZ - m->pos.z;
        var_f20 = sqrtf(((temp_f31 * temp_f31) + (temp_f29 * temp_f29)));
        if ((var_f20 > 300.0f) && (var_f20 < (f32) lbl_1_rodata_BA0[temp_r30])) {
            m->aiMode = 1;
            m->aiTimer = 0;
            if (((s32) m->aiFire == 0) && ((s32) (frand() % lbl_1_rodata_BB0[temp_r30]) == 0)) {
                m->aiFire = 1;
            }
        } else if ((var_f20 < 250.0f) || (temp_r5 = m->aiTimer, m->aiTimer = temp_r5 + 1, ((temp_r5 > (s32) lbl_1_rodata_BC0[temp_r30]) != 0))) {
            m->aiHasTgt = 0;
            m->aiTimer = 0;
        }
        break;
    case 1:
        m->aiX = (*lbl_1_bss_F8)->pos.x;
        m->aiZ = (*lbl_1_bss_F8)->pos.z;
        m->aiY = 0.0f;
        temp_f31_2 = m->aiX - m->pos.x;
        temp_f29_2 = m->aiZ - m->pos.z;
        var_f19 = sqrtf(((temp_f31_2 * temp_f31_2) + (temp_f29_2 * temp_f29_2)));
        if ((var_f19 < (f32) lbl_1_rodata_BD0[temp_r30]) || (m->push > 0.0f)) {
            m->aiMode = 2;
            m->aiHasTgt = 0;
            m->aiTimer = 0;
        } else {
            var_f30 = (f32) ((180.0 + (180.0 * (atan2((f64) (m->pos.x - m->aiX), (f64) (m->pos.z - m->aiZ)) / 3.141592653589793))) - (f64) m->rot.y);
            if (var_f30 < 0.0f) {
                var_f30 += 360.0f;
            }
            if (var_f30 >= 360.0f) {
                var_f30 -= 360.0f;
            }
            if (var_f30 >= 180.0f) {
                var_f30 -= 360.0f;
            }
            temp_f30_2 = -var_f30;
            m->aiPush = (s16) (20.0f + (var_f19 / 120.0f));
            if (temp_f30_2 < 0.0f) {
                sp14 = -temp_f30_2;
            } else {
                sp14 = temp_f30_2;
            }
            if (sp14 < (f32) lbl_1_rodata_BE0[temp_r30]) {
                m->btnDown = 0x100;
            }
        }
        break;
    case 2:
        if ((s32) m->aiHasTgt == 0) {
            var_f27 = 2300.0f + (f32) (frand() % 1700);
            temp_f30_3 = (f32) (frand() % 360);
            sp24.x = 0.0f;
            sp24.y = 0.0f;
            sp24.z = 2390.0f;
            var_f21 = 0.0f;
loop_38:
            sp30.x = (f32) (((f64) var_f27 * sin((3.141592653589793 * (f64) (temp_f30_3 + var_f21)) / 180.0)) - (f64) m->aiX);
            sp30.y = (f32) (((f64) var_f27 * cos((3.141592653589793 * (f64) (temp_f30_3 + var_f21)) / 180.0)) - (f64) m->aiZ);
            sp30.z = m->radius;
            if (fn_1_FA6C(&sp24, &sp30, 0) == 0) {
block_49:
                var_f21 += 30.0f;
                if (var_f21 >= 360.0f) {
                    var_f21 = 0.0f;
                    var_f27 -= 250.0f;
                }
                goto loop_38;
            }
            var_f26 = (f32) ((180.0 + (180.0 * (atan2((f64) (m->pos.x - sp30.x), (f64) (m->pos.z - sp30.y)) / 3.141592653589793))) - (f64) m->rot.y);
            if (var_f26 < 0.0f) {
                var_f26 += 360.0f;
            }
            if (var_f26 >= 360.0f) {
                var_f26 -= 360.0f;
            }
            if (var_f26 >= 180.0f) {
                var_f26 -= 360.0f;
            }
            temp_f26 = -var_f26;
            if (temp_f26 < 0.0f) {
                sp10 = -temp_f26;
            } else {
                sp10 = temp_f26;
            }
            if (!(sp10 > 30.0f)) {
                goto block_49;
            }
            m->aiX = sp30.x;
            m->aiZ = sp30.y;
            m->aiY = 0.0f;
            m->aiHasTgt = 1;
            m->aiTimer = 0;
            m->aiPush = (frand() % 10) + 0x3C;
        }
        if ((s16) m->chargeB >= 0x5A) {
            m->aiFire = 0;
        }
        sp30.x = m->aiX;
        sp30.y = m->aiZ;
        sp30.z = 300.0f;
        if ((fn_1_F860(&sp3C, &sp30, 0) != 0) || (temp_r4_2 = m->aiTimer, m->aiTimer = temp_r4_2 + 1, ((temp_r4_2 > 0x78) != 0))) {
            m->aiMode = 0;
            m->aiHasTgt = 0;
        }
        break;
    }
    if ((s32) m->aiFire != 0) {
        m->btn |= 0x200;
    }
    if ((s16) m->fireCool > 0) {
        m->fireCool -= 1;
        if ((s32) (m->btnDown & 0x100) != 0) {
            m->btnDown &= 0xFFFFFEFF;
        }
    } else if ((s32) (m->btnDown & 0x100) != 0) {
        m->fireCool = lbl_1_rodata_BF0[temp_r30] + 8;
    }
    if ((s32) m->hitSame != 0) {
        m->aiX = m->pos.x;
        m->aiZ = m->pos.z;
    }
    var_f25 = 0.0f;
    if ((m->aiX != m->pos.x) || (m->aiZ != m->pos.z)) {
        var_f25_2 = (f32) ((180.0 + (180.0 * (atan2((f64) (m->pos.x - m->aiX), (f64) (m->pos.z - m->aiZ)) / 3.141592653589793))) - (f64) m->rot.y);
        if (var_f25_2 < 0.0f) {
            var_f25_2 += 360.0f;
        }
        if (var_f25_2 >= 360.0f) {
            var_f25_2 -= 360.0f;
        }
        if (var_f25_2 >= 180.0f) {
            var_f25_2 -= 360.0f;
        }
        var_f25 = -var_f25_2;
    }
    if (var_f25 > 60.0f) {
        spC = 60.0f;
    } else {
        spC = var_f25;
    }
    if (spC < -60.0f) {
        sp8 = -60.0f;
    } else {
        sp8 = spC;
    }
    temp_f28 = (f32) m->aiPush;
    var_f18 = sqrtf(((sp8 * sp8) + (temp_f28 * temp_f28)));
    temp_f30_4 = (f32) (180.0 * (atan2((f64) sp8, (f64) temp_f28) / 3.141592653589793));
    temp_f31_3 = (f32) ((f64) var_f18 * sin((3.141592653589793 * (f64) temp_f30_4) / 180.0));
    temp_f28_2 = (f32) ((f64) var_f18 * cos((3.141592653589793 * (f64) temp_f30_4) / 180.0));
    m->stickX = (s16) temp_f31_3;
    m->stickY = (s16) temp_f28_2;
}

void fn_1_7998(M519Mech *m) {
    Vec sp8;
    Vec sp14;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f31;
    f32 temp_f31_2;
    s32 var_r30;
    s32 var_r30_2;

    temp_f31 = 80.0f - (2.0f * m->rot.z);
    sp38 = (f32) ((f64) m->prevPos.x + ((f64) temp_f31 * sin((3.141592653589793 * (f64) (120.0f + m->prevRot.y)) / 180.0)));
    sp40 = (f32) ((f64) m->prevPos.z + ((f64) temp_f31 * cos((3.141592653589793 * (f64) (120.0f + m->prevRot.y)) / 180.0)));
    sp3C = 100.0f + m->prevPos.y + m->prevRot.z;
    sp2C = (f32) ((f64) m->pos.x + ((f64) temp_f31 * sin((3.141592653589793 * (f64) (120.0f + m->rot.y)) / 180.0)));
    sp34 = (f32) ((f64) m->pos.z + ((f64) temp_f31 * cos((3.141592653589793 * (f64) (120.0f + m->rot.y)) / 180.0)));
    sp30 = 100.0f + m->pos.y + m->rot.z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        temp_f30 = 0.33333334f * (f32) var_r30;
        sp20 = sp38 + (temp_f30 * (sp2C - sp38));
        sp24 = sp3C + (temp_f30 * (sp30 - sp3C));
        sp28 = sp40 + (temp_f30 * (sp34 - sp40));
        sp14.x = sp20;
        sp14.y = sp24;
        sp14.z = sp28;
        fn_1_CD54(m->part[0], &sp14);
        fn_1_CFE8(m->part[0]);
        var_r30 += 1;
        goto loop_2;
    }
    temp_f31_2 = 80.0f + (2.0f * m->rot.z);
    sp38 = (f32) ((f64) m->prevPos.x + ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) (240.0f + m->prevRot.y)) / 180.0)));
    sp40 = (f32) ((f64) m->prevPos.z + ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) (240.0f + m->prevRot.y)) / 180.0)));
    sp3C = (100.0f + m->prevPos.y) - m->prevRot.z;
    sp2C = (f32) ((f64) m->pos.x + ((f64) temp_f31_2 * sin((3.141592653589793 * (f64) (240.0f + m->rot.y)) / 180.0)));
    sp34 = (f32) ((f64) m->pos.z + ((f64) temp_f31_2 * cos((3.141592653589793 * (f64) (240.0f + m->rot.y)) / 180.0)));
    sp30 = (100.0f + m->pos.y) - m->rot.z;
    var_r30_2 = 0;
loop_5:
    if (var_r30_2 < 3) {
        temp_f30_2 = 0.33333334f * (f32) var_r30_2;
        sp20 = sp38 + (temp_f30_2 * (sp2C - sp38));
        sp24 = sp3C + (temp_f30_2 * (sp30 - sp3C));
        sp28 = sp40 + (temp_f30_2 * (sp34 - sp40));
        sp8.x = sp20;
        sp8.y = sp24;
        sp8.z = sp28;
        fn_1_CD54(m->part[1], &sp8);
        fn_1_CFE8(m->part[1]);
        var_r30_2 += 1;
        goto loop_5;
    }
}



void fn_1_817C(M519Mech *m) {
    m->state = 2;
}

void fn_1_8188(M519Mech *m) {
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r30;

    if ((s16) m->motPrev != (s16) m->motState) {
        Hu3DMotionShiftSet(m->mdl[0], m->mot[5], lbl_1_rodata_9F8[m->type].mot[5].start, lbl_1_rodata_9F8[m->type].mot[5].time, lbl_1_rodata_9F8[m->type].mot[5].attr);
        m->motPrev = m->motState;
        m->stepAcc = 0.0f;
    }
    m->motState = 5;
    Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
    var_r30 = 0;
loop_5:
    if (var_r30 >= 0x32) {
        fn_1_A828(lbl_1_bss_E8[m->player]);
        fn_1_F2DC(lbl_1_bss_20[m->idx]);
        fn_1_98A0(m);
    } else {
        HuPrcVSleep();
        temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
        if (temp_r29 == temp_r28) {
            var_r30 += 1;
            goto loop_5;
        }
    }
}

void fn_1_82E4(M519Mech *m) {
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r30;

    if (!(m->push <= 0.0f)) {
        fn_1_FD7C(m->player, 2, 2);
        temp_f31 = (f32) ((f64) m->push * sin((3.141592653589793 * (f64) m->pushDir) / 180.0));
        temp_f30 = (f32) ((f64) m->push * cos((3.141592653589793 * (f64) m->pushDir) / 180.0));
        m->pos.x += temp_f31;
        m->pos.z += temp_f30;
        temp_r30 = (s16) (m->push * 0.25f);
        m->push -= (f32) temp_r30;
        if (temp_r30 == 0) {
            m->push = 0.0f;
        }
    }
}

void fn_1_8450(M519Mech *m) {
    Mtx sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    s32 sp8;
    OMCAMERAVIEW *temp_r30;
    f32 *temp_r27;
    f32 temp_r0;
    f32 temp_r0_2;
    f32 temp_r0_4;
    f32 temp_r0_5;
    f32 temp_r3;
    f32 temp_r3_2;
    f32 var_f31;
    f64 var_f30;
    s16 temp_r0_3;
    s16 temp_r0_6;
    s16 temp_r0_7;
    s16 temp_r26;
    s32 var_r28;
    s32 var_r29;

    temp_r26 = m->idx;
    if ((s32) m->camFollow != 0) {
        temp_r30 = &lbl_1_bss_108[temp_r26];
        if (temp_r26 != 0) {
            if ((temp_r26 >= 0) && (temp_r26 < 4)) {
                temp_r30->center.x = (f32) ((f64) m->pos.x + (500.0 * sin((3.141592653589793 * (f64) m->rot.y) / 180.0)));
                temp_r30->center.z = (f32) ((f64) m->pos.z + (500.0 * cos((3.141592653589793 * (f64) m->rot.y) / 180.0)));
                temp_r30->center.y = 0.0f;
                temp_r30->zoom = 1200.0f;
                temp_r30->rot.y = 180.0f + m->rot.y;
                temp_r30->rot.x = -22.5f;
                temp_r30->rot.z = 0.0f;
            }
        } else {
            temp_r30->center.x = (f32) ((f64) m->pos.x + (740.0 * sin((3.141592653589793 * (f64) m->rot.y) / 180.0)));
            temp_r30->center.z = (f32) ((f64) m->pos.z + (740.0 * cos((3.141592653589793 * (f64) m->rot.y) / 180.0)));
            temp_r30->center.y = 0.0f;
            temp_r30->zoom = 1600.0f;
            temp_r30->rot.y = 180.0f + m->rot.y;
            temp_r30->rot.x = -26.0f;
            temp_r30->rot.z = 0.0f;
        }
        omCameraViewSetMulti((s16) lbl_1_rodata_10[temp_r26], temp_r30);
    }
    temp_r3 = m->rot.x;
    temp_r0 = m->rot.y;
    sp18 = temp_r3;
    sp1C = temp_r0;
    temp_r0_2 = m->rot.z;
    sp20 = temp_r0_2;
    m->prevRot.x = m->rot.x;
    m->prevRot.y = m->rot.y;
    m->prevRot.z = m->rot.z;
    m->rot.x = temp_r3;
    m->rot.y = temp_r0;
    m->rot.z = temp_r0_2;
    var_r29 = 0;
loop_16:
    if (var_r29 < 9) {
        if ((((s16) m->type != 1) || (var_r29 != 2)) && (((s16) m->type != 0) || (var_r29 != 5)) && ((s16) m->mdl[var_r29] != -1)) {
            temp_r27 = Hu3DData[m->mdl[var_r29]].mtx[0];
            MTXIdentity((f32 (*)[4]) temp_r27);
            MTXRotRad((f32 (*)[4]) temp_r27, 0x7A, 0.017453292f * sp20);
            Hu3DModelRotSet(m->mdl[var_r29], sp18, sp1C, 0.0f);
        }
        var_r29 += 1;
        goto loop_16;
    }
    temp_r0_3 = m->type;
    if (temp_r0_3 != 1) {
        if (temp_r0_3 < 1) {

        }
    } else {
        MTXIdentity((f32 (*)[4]) Hu3DData[m->mdl[3]].mtx[0]);
        if (fmod((f64) (m->rot.y - m->aim), 360.0) < 0.0f) {
            var_f30 = -fmod((f64) (m->rot.y - m->aim), 360.0);
        } else {
            var_f30 = fmod((f64) (m->rot.y - m->aim), 360.0);
        }
        var_f31 = (f32) var_f30;
        if (var_f31 > 180.0f) {
            var_f31 = 180.0f - (var_f31 - 180.0f);
        }
        Hu3DModelRotSet(m->mdl[3], -45.0f + (0.5f * var_f31), m->aim, 0.0f);
    }
    temp_r3_2 = m->pos.x;
    temp_r0_4 = m->pos.y;
    spC = temp_r3_2;
    sp10 = temp_r0_4;
    temp_r0_5 = m->pos.z;
    sp14 = temp_r0_5;
    m->prevPos.x = m->pos.x;
    m->prevPos.y = m->pos.y;
    m->prevPos.z = m->pos.z;
    m->pos.x = temp_r3_2;
    m->pos.y = temp_r0_4;
    m->pos.z = temp_r0_5;
    var_r28 = 0;
loop_30:
    if (var_r28 < 9) {
        if ((s16) m->mdl[var_r28] != -1) {
            Hu3DModelPosSet(m->mdl[var_r28], spC, sp10, sp14);
        }
        var_r28 += 1;
        goto loop_30;
    }
    temp_r0_6 = m->type;
    switch (temp_r0_6) {                            /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        Hu3DModelPosSet(m->mdl[5], spC, 8.0f + sp10, sp14);
        break;
    case 1:                                         /* switch 1 */
        Hu3DModelPosSet(m->mdl[2], spC, 8.0f + sp10, sp14);
        Hu3DModelPosSet(m->mdl[3], spC, 180.0f + sp10, sp14);
        break;
    }
    temp_r0_7 = m->type;
    switch (temp_r0_7) {                            /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        Hu3DModelObjMtxGet(m->mdl[0], lbl_1_data_14[0], sp30);
        sp24 = sp30[0][3];
        sp28 = sp30[1][3];
        sp2C = sp30[2][3];
        Hu3DModelPosSet(m->mdl[6], sp24, sp28, sp2C);
        Hu3DModelPosSet(m->mdl[7], sp24, sp28, sp2C);
        Hu3DModelPosSet(m->mdl[8], sp24, sp28, sp2C);
        if ((s32) ((m->hpMax / 5) * (4 - m->dmgStage)) > (s16) m->hp) {
            sp8 = HuAudFXPlayPan(0x710, (s16) lbl_1_rodata_18[m->type]);
            Hu3DMotionStartEndSet(m->mdl[6], 40.0f * (f32) m->dmgStage, 40.0f + (40.0f * (f32) m->dmgStage));
            Hu3DMotionStartEndSet(m->mdl[7], 40.0f * (f32) m->dmgStage, 40.0f + (40.0f * (f32) m->dmgStage));
            Hu3DMotionTimeSet(m->mdl[6], 40.0f * (f32) m->dmgStage);
            Hu3DModelAttrReset(m->mdl[6], 0x40000001U);
            Hu3DModelAttrReset(m->mdl[6], 0x40000002U);
            Hu3DMotionTimeSet(m->mdl[7], 40.0f * (f32) m->dmgStage);
            Hu3DModelAttrReset(m->mdl[7], 0x40000001U);
            Hu3DModelAttrReset(m->mdl[7], 0x40000002U);
            m->dmgStage += 1;
            return;
        }
        return;
    case 1:                                         /* switch 2 */
        Hu3DModelObjMtxGet(m->mdl[0], lbl_1_data_14[1], sp30);
        sp24 = sp30[0][3];
        sp28 = sp30[1][3];
        sp2C = sp30[2][3];
        Hu3DModelPosSet(m->mdl[4], sp24, sp28, sp2C);
        if ((s16) m->state == 1) {
            Hu3DModelAttrReset(m->mdl[3], 1U);
            return;
        }
        Hu3DModelAttrSet(m->mdl[3], 1U);
        break;
    }
}

void fn_1_8D40(M519Mech *m) {
    m->aim = (f32) (180.0 + (180.0 * (atan2((f64) (m->pos.x - (*lbl_1_bss_F8)->pos.x), (f64) (m->pos.z - (*lbl_1_bss_F8)->pos.z)) / 3.141592653589793)));
}


void fn_1_8E40(M519Mech *m) {
    Vec sp8;
    Vec sp14;
    Vec sp20;
    Vec sp2C;
    Vec sp38;
    Vec sp44;
    Vec sp50;
    Vec sp5C;
    Vec sp68;
    Vec sp74;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r30;
    s16 temp_r30_2;
    s16 temp_r3;
    s16 temp_r3_2;

    if (((s16) m->shootWait <= 0) || (temp_r0 = m->shootWait - 1, m->shootWait = temp_r0, ((temp_r0 > 0) == 0))) {
        temp_r0_2 = m->type;
        switch (temp_r0_2) {                        /* irregular */
        case 0:
            sp8C = m->pos.x;
            sp90 = m->pos.y;
            sp94 = m->pos.z;
            sp80 = m->rot.x;
            sp84 = m->rot.y;
            sp88 = m->rot.z;
            if (((s32) (m->btnDown & 0x100) != 0) && ((s32) (m->btn & 0x200) == 0)) {
                Hu3DModelAttrReset(m->mdl[1], 1U);
                Hu3DMotionTimeSet(m->mdl[1], 0.0f);
                sp90 += 170.0f;
                sp68.x = sp80;
                sp68.y = sp84;
                sp68.z = sp88;
                sp74.x = sp8C;
                sp74.y = sp90;
                sp74.z = sp94;
                fn_1_A9F0(0, &sp74, &sp68, m->idx);
                m->shootWait = 8;
                m->chargeA = 0;
                m->chargeB = 0;
                fn_1_FD7C(m->player, 0, 3);
                goto block_23;
            }
            if (((s32) (m->btn & 0x100) != 0) && ((s32) (m->btn & 0x200) == 0)) {
                m->chargeB = 0;
                temp_r3 = m->chargeA;
                m->chargeA = temp_r3 + 1;
                if (temp_r3 == 0) {
                    if ((s32) m->sfx != -1) {
                        HuAudFXStop(m->sfx);
                    }
                    m->sfx = HuAudFXPlayPan(0x70D, (s16) lbl_1_rodata_18[m->type]);
                    Hu3DModelAttrReset(m->mdl[3], 1U);
                    Hu3DMotionShapeStartEndSet(m->mdl[3], 0.0f, 60.0f);
                    Hu3DMotionTimeSet(m->mdl[3], 0.0f);
                    Hu3DModelAttrSet(m->mdl[3], 0x40000001U);
                } else if ((s16) m->chargeA == 0x28) {
                    Hu3DMotionShapeStartEndSet(m->mdl[3], 40.0f, 60.0f);
                    Hu3DMotionTimeSet(m->mdl[3], 0.0f);
                    Hu3DModelAttrSet(m->mdl[3], 0x40000001U);
                }
                if (((s16) m->chargeA >= 0x28) && ((s32) (m->chargeA % 5) == 0)) {
                    fn_1_FD7C(m->player, 1, 3);
                }
                goto block_23;
            }
            if ((s16) m->chargeA > 0) {
                HuAudFXStop(m->sfx);
                m->sfx = -1;
                Hu3DModelAttrSet(m->mdl[3], 1U);
                temp_r30 = m->chargeA;
                m->chargeA = 0;
                if (temp_r30 >= 0x5A) {
                    Hu3DModelAttrReset(m->mdl[2], 1U);
                    Hu3DMotionTimeSet(m->mdl[2], 0.0f);
                    sp90 += 170.0f;
                    sp50.x = sp80;
                    sp50.y = sp84;
                    sp50.z = sp88;
                    sp5C.x = sp8C;
                    sp5C.y = sp90;
                    sp5C.z = sp94;
                    fn_1_A9F0(1, &sp5C, &sp50, m->idx);
                    m->shootWait = 8;
                    fn_1_FD7C(m->player, 2, 0x1E);
                    goto block_23;
                }
            } else {
block_23:
                sp8C = m->pos.x;
                sp90 = m->pos.y;
                sp94 = m->pos.z;
                sp80 = m->rot.x;
                sp84 = m->rot.y;
                sp88 = m->rot.z;
                if (((s32) (m->btnDown & 0x200) != 0) && ((s32) (m->btn & 0x100) == 0)) {
                    sp38.x = sp80;
                    sp38.y = sp84;
                    sp38.z = sp88;
                    sp44.x = sp8C;
                    sp44.y = sp90;
                    sp44.z = sp94;
                    fn_1_A9F0(2, &sp44, &sp38, m->idx);
                    m->shootWait = 0x20;
                    m->chargeB = 0;
                    m->chargeA = 0;
                    fn_1_FD7C(m->player, 0, 3);
                    return;
                }
                if (((s32) (m->btn & 0x200) != 0) && ((s32) (m->btn & 0x100) == 0)) {
                    m->chargeA = 0;
                    temp_r3_2 = m->chargeB;
                    m->chargeB = temp_r3_2 + 1;
                    if (temp_r3_2 == 0) {
                        if ((s32) m->sfx != -1) {
                            HuAudFXStop(m->sfx);
                        }
                        m->sfx = HuAudFXPlayPan(0x70D, (s16) lbl_1_rodata_18[m->type]);
                        Hu3DModelAttrReset(m->mdl[4], 1U);
                        Hu3DMotionStartEndSet(m->mdl[4], 0.0f, 60.0f);
                        Hu3DMotionTimeSet(m->mdl[4], 0.0f);
                        Hu3DModelAttrSet(m->mdl[4], 0x40000001U);
                    } else if ((s16) m->chargeB == 0x1E) {
                        Hu3DMotionStartEndSet(m->mdl[4], 30.0f, 60.0f);
                        Hu3DMotionTimeSet(m->mdl[4], 0.0f);
                        Hu3DModelAttrSet(m->mdl[4], 0x40000001U);
                    }
                    if (((s16) m->chargeB >= 0x1E) && ((s32) (m->chargeB % 5) == 0)) {
                        fn_1_FD7C(m->player, 1, 3);
                        return;
                    }
                } else if ((s16) m->chargeB > 0) {
                    HuAudFXStop(m->sfx);
                    m->sfx = -1;
                    Hu3DModelAttrSet(m->mdl[4], 1U);
                    temp_r30_2 = m->chargeB;
                    m->chargeB = 0;
                    if (temp_r30_2 >= 0x5A) {
                        sp20.x = sp80;
                        sp20.y = sp84;
                        sp20.z = sp88;
                        sp2C.x = sp8C;
                        sp2C.y = sp90;
                        sp2C.z = sp94;
                        fn_1_A9F0(3, &sp2C, &sp20, m->idx);
                        m->shootWait = 8;
                        fn_1_FD7C(m->player, 2, 0x1E);
                        return;
                    }
                }
            }
            break;
        case 1:
            sp8C = m->pos.x;
            sp90 = m->pos.y;
            sp94 = m->pos.z;
            sp80 = m->rot.x;
            sp84 = m->rot.y;
            sp88 = m->rot.z;
            if ((s32) (m->btnDown & 0x100) != 0) {
                Hu3DModelAttrReset(m->mdl[1], 1U);
                Hu3DMotionTimeSet(m->mdl[1], 0.0f);
                sp90 += 170.0f;
                sp8.x = sp80;
                sp8.y = sp84;
                sp8.z = sp88;
                sp14.x = sp8C;
                sp14.y = sp90;
                sp14.z = sp94;
                fn_1_A9F0(4, &sp14, &sp8, m->idx);
                m->shootWait = 8;
                fn_1_FD7C(m->player, 0, 3);
            }
            break;
        }
    }
}

void fn_1_95B0(M519Mech *m) {
    Vec sp8;
    Vec sp14;
    M519Mech *temp_r30;
    s32 var_r29;

    sp14.x = m->pos.x;
    sp14.y = m->pos.z;
    sp14.z = m->radius;
    m->hitSame = 0;
    var_r29 = 0;
loop_7:
    if (var_r29 < 4) {
        temp_r30 = lbl_1_bss_F8[var_r29];
        if ((temp_r30 != m) && ((s16) temp_r30->state != 3)) {
            sp8.x = temp_r30->pos.x;
            sp8.y = temp_r30->pos.z;
            sp8.z = temp_r30->radius;
            if (fn_1_F860(&sp14, &sp8, 1) != 0) {
                m->rot.y = fn_1_FC78(m->rot.y, (f32) (180.0 * (atan2((f64) (sp14.x - m->pos.x), (f64) (sp14.y - m->pos.z)) / 3.141592653589793)), 0.0009f * m->speed);
                m->pos.x = sp14.x;
                m->pos.z = sp14.y;
                if ((s16) m->type == (s16) temp_r30->type) {
                    m->hitSame = 1;
                }
            }
        }
        var_r29 += 1;
        goto loop_7;
    }
}

void fn_1_9700(M519Mech *m) {
    Vec spC;
    Vec sp18;
    f32 sp8;
    M519Bld *temp_r30;
    s32 var_r29;

    sp18.x = m->pos.x;
    sp18.y = m->pos.z;
    sp18.z = m->radius;
    var_r29 = 0;
loop_7:
    if (var_r29 < 0xC) {
        temp_r30 = lbl_1_bss_178->bld[var_r29];
        if ((temp_r30 != NULL) && (((s16) temp_r30->state == 3) || ((s16) temp_r30->state == 1))) {
            spC.x = temp_r30->pos.x;
            spC.y = temp_r30->pos.z;
            spC.z = temp_r30->radius;
            if (fn_1_F860(&sp18, &spC, 1) != 0) {
                sp8 = m->rot.y;
                m->rot.y = fn_1_FC78(m->rot.y, (f32) (180.0 * (atan2((f64) (sp18.x - m->pos.x), (f64) (sp18.y - m->pos.z)) / 3.141592653589793)), 0.0009f * m->speed);
                m->pos.x = sp18.x;
                m->pos.z = sp18.y;
            }
        }
        var_r29 += 1;
        goto loop_7;
    }
    spC.x = 0.0f;
    spC.y = 0.0f;
    spC.z = 2390.0f;
    if (fn_1_FA6C(&sp18, &spC, 1) != 0) {
        m->pos.x = sp18.x;
        m->pos.z = sp18.y;
    }
}

void fn_1_98A0(M519Mech *m) {
    m->state = 3;
}

void fn_1_98AC(M519Mech *m) {
    f32 temp_f31;
    s16 temp_r0;
    s16 temp_r22;
    s16 temp_r24;
    s16 temp_r25;
    s16 temp_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    HuAudFXPlayPan(lbl_1_rodata_C48[m->type], (s16) lbl_1_rodata_18[m->type]);
    fn_1_FD7C(m->player, 1, 0x5A);
    temp_r0 = m->type;
    switch (temp_r0) {                              /* irregular */
    case 0:
        Hu3DModelAttrSet(m->mdl[1], 1U);
        Hu3DModelAttrSet(m->mdl[2], 1U);
        Hu3DModelAttrSet(m->mdl[3], 1U);
        Hu3DModelAttrSet(m->mdl[4], 1U);
        Hu3DModelAttrSet(m->mdl[6], 1U);
        Hu3DModelAttrSet(m->mdl[7], 1U);
        Hu3DModelAttrSet(m->mdl[8], 1U);
        Hu3DModelAttrSet(m->mdl[5], 1U);
        break;
    case 1:
        Hu3DModelAttrSet(m->mdl[1], 1U);
        Hu3DModelAttrSet(m->mdl[2], 1U);
        Hu3DModelAttrSet(m->mdl[3], 1U);
        Hu3DModelAttrSet(m->mdl[4], 1U);
        break;
    }
    Hu3DModelAttrReset(m->mdl[0], 0x4000U);
    Hu3DModelAttrSet(m->mdl[0], 2U);
    var_r29 = 1;
loop_14:
    if (var_r29 > 0x3C) {
        var_r30 = 0;
loop_19:
        if (var_r30 < 4) {
            if ((s16) m->mdl[var_r30] != -1) {
                Hu3DModelTPLvlSet(m->mdl[var_r30], 0.0f);
                Hu3DModelAttrSet(m->mdl[var_r30], 0x40000002U);
                Hu3DModelAttrSet(m->mdl[var_r30], 1U);
            }
            var_r30 += 1;
            goto loop_19;
        }
loop_20:
        var_r27 = 0;
loop_23:
        if (var_r27 >= 1) {
            goto loop_20;
        }
        HuPrcVSleep();
        temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r25;
        if (temp_r25 == temp_r22) {
            var_r27 += 1;
            goto loop_23;
        }
    } else {
        temp_f31 = 0.016666668f * (f32) var_r29;
        Hu3DModelTPLvlSet(m->mdl[0], 1.0f - temp_f31);
        if ((s16) m->type == 0) {
            Hu3DModelTPLvlSet(m->mdl[5], 1.0f - temp_f31);
        }
        fn_1_8450(m);
        var_r28 = 0;
loop_12:
        if (var_r28 >= 1) {
            var_r29 += 1;
            goto loop_14;
        }
        HuPrcVSleep();
        temp_r26 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r26;
        if (temp_r26 == temp_r24) {
            var_r28 += 1;
            goto loop_12;
        }
    }
}

void fn_1_9B9C(M519Mech *m) {
    m->state = 4;
}

void fn_1_9BA8(M519Mech *m) {
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_f30;
    f32 temp_f31;
    s16 temp_r0;
    s16 temp_r22;
    s16 temp_r24;
    s16 temp_r25;
    s16 temp_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    sp14 = m->pos.x;
    sp18 = m->pos.y;
    sp1C = m->pos.z;
    Hu3DModelAttrReset(m->mdl[0], 1U);
    Hu3DModelAttrReset(m->mdl[5], 1U);
    Hu3DModelAttrReset(m->mdl[6], 1U);
    Hu3DModelAttrReset(m->mdl[7], 1U);
    Hu3DModelAttrReset(m->mdl[0], 0x4000U);
    Hu3DModelAttrSet(m->mdl[0], 2U);
    HuAudFXPlay(0x709);
    var_r29 = 1;
loop_17:
    if (var_r29 > 0x64) {
        Hu3DModelTPLvlSet(m->mdl[0], 1.0f);
        Hu3DModelTPLvlSet(m->mdl[5], 1.0f);
        Hu3DModelAttrSet(m->mdl[0], 0x4000U);
        Hu3DModelAttrReset(m->mdl[0], 2U);
        HuAudFXPlay(0x720);
        if ((s16) m->motPrev != (s16) m->motState) {
            Hu3DMotionShiftSet(m->mdl[0], m->mot[6], lbl_1_rodata_9F8[m->type].mot[6].start, lbl_1_rodata_9F8[m->type].mot[6].time, lbl_1_rodata_9F8[m->type].mot[6].attr);
            m->motPrev = m->motState;
            m->stepAcc = 0.0f;
        }
        m->motState = 6;
        Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
        fn_1_FD7C(m->player, 2, 0x1E);
        var_r27 = 0;
loop_23:
        if (var_r27 >= 0x5A) {
            if ((s16) m->motPrev != (s16) m->motState) {
                Hu3DMotionShiftSet(m->mdl[0], m->mot[0], lbl_1_rodata_9F8[m->type].mot[0].start, lbl_1_rodata_9F8[m->type].mot[0].time, lbl_1_rodata_9F8[m->type].mot[0].attr);
                m->motPrev = m->motState;
                m->stepAcc = 0.0f;
            }
            m->motState = 0;
            Hu3DMotionSpeedSet(m->mdl[0], 1.0f);
            m->state = 0;
        } else {
            HuPrcVSleep();
            temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
            temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
            ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r25;
            if (temp_r25 == temp_r22) {
                var_r27 += 1;
                goto loop_23;
            }
        }
    } else {
        temp_f31 = 0.01f * (f32) (var_r29 + 1);
        temp_f30 = (f32) cos((3.141592653589793 * (f64) (90.0f * temp_f31)) / 180.0);
        Hu3DModelTPLvlSet(m->mdl[0], temp_f31);
        Hu3DModelTPLvlSet(m->mdl[5], temp_f31);
        sp18 = 1000.0f * temp_f30;
        sp8 = sp14;
        spC = sp18;
        sp10 = sp1C;
        m->prevPos.x = m->pos.x;
        m->prevPos.y = m->pos.y;
        m->prevPos.z = m->pos.z;
        m->pos.x = sp14;
        m->pos.y = sp18;
        m->pos.z = sp1C;
        var_r30 = 0;
loop_5:
        if (var_r30 < 9) {
            if ((s16) m->mdl[var_r30] != -1) {
                Hu3DModelPosSet(m->mdl[var_r30], sp8, spC, sp10);
            }
            var_r30 += 1;
            goto loop_5;
        }
        temp_r0 = m->type;
        switch (temp_r0) {                          /* irregular */
        case 0:
            Hu3DModelPosSet(m->mdl[5], sp8, 8.0f + spC, sp10);
            break;
        case 1:
            Hu3DModelPosSet(m->mdl[2], sp8, 8.0f + spC, sp10);
            Hu3DModelPosSet(m->mdl[3], sp8, 180.0f + spC, sp10);
            break;
        }
        fn_1_8450(m);
        var_r28 = 0;
loop_15:
        if (var_r28 >= 1) {
            var_r29 += 1;
            goto loop_17;
        }
        HuPrcVSleep();
        temp_r26 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r26;
        if (temp_r26 == temp_r24) {
            var_r28 += 1;
            goto loop_15;
        }
    }
}

void fn_1_A068(M519Mech *m) {
    f32 temp_f31;
    s16 temp_r27;
    s16 temp_r28;
    s32 var_r29;
    s32 var_r30;

    Hu3DModelAttrReset(m->mdl[0], 1U);
    Hu3DModelAttrReset(m->mdl[2], 1U);
    Hu3DModelAttrReset(m->mdl[0], 0x4000U);
    Hu3DModelAttrSet(m->mdl[0], 2U);
    var_r30 = 0;
loop_6:
    if (var_r30 >= 0x5A) {
        Hu3DModelTPLvlSet(m->mdl[0], 1.0f);
        Hu3DModelTPLvlSet(m->mdl[2], 1.0f);
        Hu3DModelAttrSet(m->mdl[0], 0x4000U);
        Hu3DModelAttrReset(m->mdl[0], 2U);
        m->state = 0;
    } else {
        temp_f31 = (f32) (0.011111111111111112 * (f64) var_r30);
        Hu3DModelTPLvlSet(m->mdl[0], temp_f31);
        Hu3DModelTPLvlSet(m->mdl[2], temp_f31);
        var_r29 = 0;
loop_4:
        if (var_r29 >= 1) {
            var_r30 += 1;
            goto loop_6;
        }
        HuPrcVSleep();
        temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r27 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r28;
        if (temp_r28 == temp_r27) {
            var_r29 += 1;
            goto loop_4;
        }
    }
}

s32 fn_1_A1D4(M519Mech *m) {
    s32 var_r31;

    if ((s16) m->hp == 0) {
        var_r31 = 1;
    } else {
        var_r31 = 0;
    }
    return var_r31;
}

M519Player *fn_1_A204(s16 side, s16 idx) {
    s16 sp8;
    M519Player *temp_r3;
    s32 var_r30;

    sp8 = side;
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Player), MEMORY_DEFAULT_NUM);
    temp_r3->side = sp8;
    temp_r3->idx = idx;
    temp_r3->isCom = (s32) GWPlayerCfg[idx].iscom;
    temp_r3->charNo = GWPlayerCfg[idx].character;
    temp_r3->dif = GWPlayerCfg[idx].diff;
    temp_r3->pad = GWPlayerCfg[idx].pad_idx;
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    temp_r3->mdl[0] = CharModelCreate(temp_r3->charNo, 2);
    temp_r3->mdl[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_D98[Mp5CharNo(temp_r3->charNo)], MEMORY_DEFAULT_NUM, HEAP_DATA));
    Hu3DModelAttrSet(temp_r3->mdl[1], 0x4000U);
    Hu3DModelAttrSet(temp_r3->mdl[0], 0x4000U);
    Hu3DModelAttrSet(temp_r3->mdl[1], 2U);
    Hu3DModelAttrSet(temp_r3->mdl[0], 2U);
    Hu3DModelAttrSet(temp_r3->mdl[0], 1U);
    Hu3DModelLayerSet(temp_r3->mdl[0], 2);
    Hu3DModelLayerSet(temp_r3->mdl[1], 2);
    var_r30 = 0;
loop_2:
    if (var_r30 < 6) {
        temp_r3->mot[var_r30] = Mp5CharMotionCreateData(temp_r3->charNo, (u32) lbl_1_rodata_C60[Mp5CharNo(temp_r3->charNo)].n[var_r30], 0 /* TODO(mp5): MP4 motion for DK */);
        var_r30 += 1;
        goto loop_2;
    }
    CharMotionDataClose(temp_r3->charNo);
    Hu3DMotionSet(temp_r3->mdl[0], temp_r3->mot[0]);
    Hu3DModelAttrSet(temp_r3->mdl[0], 0x40000002U);
    temp_r3->proc = HuPrcChildCreate(fn_1_A40C, 0x1000U, 0x1000U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    return temp_r3;
}

void fn_1_A40C(void) {
    M519Player *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_48[temp_r31->state](temp_r31);
    }
}

void fn_1_A44C(M519Player *p, Vec *pos) {
    s32 var_r30;

    p->pos.x = pos->x;
    p->pos.y = pos->y;
    p->pos.z = pos->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        Hu3DModelPosSet(p->mdl[var_r30], pos->x, pos->y, pos->z);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_A4EC(M519Player *p, Vec *rot) {
    s32 var_r30;

    p->rot.x = rot->x;
    p->rot.y = rot->y;
    p->rot.z = rot->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        Hu3DModelRotSet(p->mdl[var_r30], rot->x, rot->y, rot->z);
        var_r30 += 1;
        goto loop_2;
    }
}



void fn_1_A598(M519Player *p) {
    s16 temp_r29;
    s16 temp_r30;
    s32 var_r31;

loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r30 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r30;
    if (temp_r30 == temp_r29) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_A628(M519Player *p) {
    p->state = 1;
}

void fn_1_A634(M519Player *p) {
    Hu3DModelAttrSet(p->mdl[1], 1U);
    Hu3DModelAttrReset(p->mdl[0], 1U);
    Hu3DModelTPLvlSet(p->mdl[0], 1.0f);
    Hu3DModelAttrReset(p->mdl[0], 0x40000002U); // pose it once, then pause again (see below)
    HuPrcVSleep();
    HuPrcVSleep();
    HuPrcVSleep();
    Hu3DModelAttrSet(p->mdl[0], 0x40000002U);
    Hu3DModelHookReset(lbl_1_bss_F8[p->mech]->mdl[0]);
    p->state = 0;
}

void fn_1_A6B8(M519Player *p) {
    p->state = 2;
}

void fn_1_A6C4(M519Player *p) {
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r31;

    Hu3DModelAttrReset(p->mdl[0], 0x40000002U);
    Hu3DMotionShiftSet(p->mdl[0], p->mot[4], 0.0f, 8.0f, 0U);
loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
    if (temp_r29 == temp_r28) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_A770(M519Player *p) {
    p->state = 3;
}

void fn_1_A77C(M519Player *p) {
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r31;

    Hu3DModelAttrReset(p->mdl[0], 0x40000002U);
    Hu3DMotionShiftSet(p->mdl[0], p->mot[5], 0.0f, 8.0f, 0U);
loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
    if (temp_r29 == temp_r28) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_A828(M519Player *p) {
    p->state = 4;
}

void fn_1_A834(M519Player *p) {
    s16 temp_r22;
    s16 temp_r24;
    s16 temp_r25;
    s16 temp_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;

    Hu3DModelAttrReset(p->mdl[1], 0x4000U);
    Hu3DModelAttrReset(p->mdl[0], 0x4000U);
    Hu3DModelAttrSet(p->mdl[1], 2U);
    Hu3DModelAttrSet(p->mdl[0], 2U);
    var_r29 = 0;
loop_9:
    if (var_r29 >= 0x5A) {
        var_r30 = 0;
loop_12:
        if (var_r30 < 2) {
            Hu3DModelAttrSet(p->mdl[var_r30], 1U);
            var_r30 += 1;
            goto loop_12;
        }
loop_13:
        var_r27 = 0;
loop_16:
        if (var_r27 >= 1) {
            goto loop_13;
        }
        HuPrcVSleep();
        temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r25;
        if (temp_r25 == temp_r22) {
            var_r27 += 1;
            goto loop_16;
        }
    } else {
        var_r30_2 = 0;
loop_3:
        if (var_r30_2 < 2) {
            Hu3DModelTPLvlSet(p->mdl[var_r30_2], 1.0f - (f32) (0.011111111111111112 * (f64) var_r29));
            var_r30_2 += 1;
            goto loop_3;
        }
        var_r28 = 0;
loop_7:
        if (var_r28 >= 1) {
            var_r29 += 1;
            goto loop_9;
        }
        HuPrcVSleep();
        temp_r26 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r26;
        if (temp_r26 == temp_r24) {
            var_r28 += 1;
            goto loop_7;
        }
    }
}

s32 fn_1_A9F0(s16 kind, Vec *pos, Vec *rot, s16 owner) {
    Vec spC;
    Vec sp18;
    s16 spA;
    s16 sp8;
    M519Bullet *temp_r31;
    s16 temp_r4;
    s32 var_r30;

    sp8 = kind;
    spA = owner;
    var_r30 = 0;
loop_7:
    if (var_r30 >= 0x2C) {
        return 0;
    }
    temp_r31 = lbl_1_bss_38[var_r30];
    if ((temp_r31 != NULL) && ((s16) temp_r31->state == 0) && ((s16) temp_r31->prevState == 0) && ((s16) temp_r31->kind == sp8)) {
        temp_r31->owner = spA;
        temp_r4 = lbl_1_bss_C;
        lbl_1_bss_C = temp_r4 + 1;
        temp_r31->id = temp_r4 % 32000;
        sp18.x = pos->x;
        sp18.y = pos->y;
        sp18.z = pos->z;
        fn_1_AE24(temp_r31, &sp18);
        spC.x = rot->x;
        spC.y = rot->y;
        spC.z = rot->z;
        fn_1_AEC4(temp_r31, &spC);
        fn_1_B0B0(temp_r31);
        return 1;
    }
    var_r30 += 1;
    goto loop_7;
}

M519Bullet *fn_1_AB40(s16 kind) {
    M519Bullet *temp_r3;
    s32 var_r29;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Bullet), MEMORY_DEFAULT_NUM);
    temp_r3->id = 0;
    temp_r3->kind = kind;
    temp_r3->active = 0;
    temp_r3->owner = -1;
    temp_r3->radius = 1.0f;
    temp_r3->dmg = lbl_1_rodata_DFC[kind].dmg;
    temp_r3->pushPow = lbl_1_rodata_DFC[kind].pushPow;
    temp_r3->radius1 = lbl_1_rodata_DFC[kind].radius0;
    temp_r3->radius0 = lbl_1_rodata_DFC[kind].radius1;
    temp_r3->life = lbl_1_rodata_DFC[kind].life;
    temp_r3->ramp = lbl_1_rodata_DFC[kind].ramp;
    temp_r3->speed = lbl_1_rodata_DFC[kind].speed;
    temp_r3->stick = lbl_1_rodata_DFC[kind].stick;
    temp_r3->curSpeed = 0.0f;
    temp_r3->pos.x = 0.0f;
    temp_r3->pos.y = 0.0f;
    temp_r3->pos.z = 0.0f;
    temp_r3->rot.x = 0.0f;
    temp_r3->rot.y = 0.0f;
    temp_r3->rot.z = 0.0f;
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    var_r29 = 0;
loop_2:
    if (var_r29 < 2) {
        temp_r3->mdl[var_r29] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_DD4[kind].n[var_r29], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r3->mdl[var_r29], 0x4000U);
        Hu3DModelAttrSet(temp_r3->mdl[var_r29], 1U);
        Hu3DModelLayerSet(temp_r3->mdl[var_r29], 2);
        var_r29 += 1;
        goto loop_2;
    }
    temp_r3->proc = HuPrcChildCreate(fn_1_ADE4, 0x900U, 0x2000U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    return temp_r3;
}

void fn_1_ADE4(void) {
    M519Bullet *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_5C[temp_r31->state](temp_r31);
    }
}

void fn_1_AE24(M519Bullet *b, Vec *pos) {
    s32 var_r30;

    b->pos.x = pos->x;
    b->pos.y = pos->y;
    b->pos.z = pos->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        Hu3DModelPosSet(b->mdl[var_r30], pos->x, pos->y, pos->z);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_AEC4(M519Bullet *b, Vec *rot) {
    s32 var_r30;

    b->rot.x = rot->x;
    b->rot.y = rot->y;
    b->rot.z = rot->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 2) {
        Hu3DModelRotSet(b->mdl[var_r30], rot->x, rot->y, rot->z);
        var_r30 += 1;
        goto loop_2;
    }
}



void fn_1_B004(M519Bullet *b) {
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r30;
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 2) {
        Hu3DModelAttrSet(b->mdl[var_r31], 1U);
        var_r31 += 1;
        goto loop_2;
    }
loop_3:
    var_r30 = 0;
loop_6:
    if (var_r30 >= 1) {
        goto loop_3;
    }
    HuPrcVSleep();
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
    if (temp_r29 == temp_r28) {
        var_r30 += 1;
        goto loop_6;
    }
}

void fn_1_B0B0(M519Bullet *b) {
    b->state = 1;
}

void fn_1_B0BC(M519Bullet *b) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    s32 sp10;
    s32 spC;
    s16 spA;
    s16 sp8;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_r0_2;
    f32 var_f31;
    s16 temp_r0;
    s16 temp_r0_3;
    s16 temp_r0_4;
    s16 temp_r18;
    s16 temp_r21;
    s16 temp_r22;
    s16 temp_r23;
    s16 var_r20;
    s16 var_r30;
    s32 var_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;

    HuAudFXPlayPan(lbl_1_rodata_E80[b->kind], (s16) lbl_1_rodata_18[lbl_1_bss_F8[b->owner]->type]);
    Hu3DModelAttrReset(b->mdl[0], 1U);
    temp_r0 = b->kind;
    switch (temp_r0) {                              /* irregular */
    case 1:
        Hu3DModelAttrSet(b->mdl[0], 0x40000001U);
        break;
    case 2:
    case 4:
    case 0:
        Hu3DModelAttrReset(b->mdl[0], 0x40000001U);
        break;
    }
    Hu3DMotionShapeStartEndSet(b->mdl[0], 0.0f, Hu3DMotionMaxTimeGet(b->mdl[0]));
    Hu3DMotionTimeSet(b->mdl[0], 0.0f);
    b->active = 1;
    var_r29 = 0;
    var_f31 = 0.0f;
    var_r30 = 0;
loop_43:
    if (var_r30 >= (s16) b->life) {
        goto block_44;
    }
    if (var_r30 < 0xA) {
        var_f31 += 0.1f;
    }
    if (var_r30 > (s32) (b->life - 0xA)) {
        var_f31 -= 0.1f;
    }
    b->curSpeed = b->speed;
    temp_f30 = (f32) ((f64) b->curSpeed * sin((3.141592653589793 * (f64) b->rot.y) / 180.0));
    temp_f29 = (f32) ((f64) b->curSpeed * cos((3.141592653589793 * (f64) b->rot.y) / 180.0));
    if (((s16) b->kind != 3) && ((s16) b->kind != 2)) {
        Hu3DModelScaleSet(b->mdl[0], 1.0f, 1.0f, var_f31);
    }
    temp_r0_2 = b->pos.y;
    sp2C = b->pos.x;
    sp30 = temp_r0_2;
    sp34 = b->pos.z;
    sp2C += temp_f30;
    sp34 += temp_f29;
    sp20 = sp2C;
    sp24 = temp_r0_2;
    sp28 = sp34;
    b->pos.x = sp2C;
    b->pos.y = temp_r0_2;
    b->pos.z = sp34;
    var_r28 = 0;
loop_19:
    if (var_r28 < 2) {
        Hu3DModelPosSet(b->mdl[var_r28], sp20, sp24, sp28);
        var_r28 += 1;
        goto loop_19;
    }
    if (var_r30 >= (s16) b->ramp) {
        var_r20 = b->ramp;
    } else {
        var_r20 = var_r30;
    }
    b->radius = (f32) ((f64) b->radius0 + ((f64) (b->radius1 - b->radius0) * sin((3.141592653589793 * (f64) (90.0f * (1.0f / (f32) b->ramp) * (f32) var_r20)) / 180.0)));
    if (((s16) b->kind == 0) || ((s16) b->kind == 1) || ((s16) b->kind == 4)) {
        if (fn_1_BECC(b) != 0) {
            var_r29 = 1;
        }
        if (fn_1_B9BC(b) != 0) {
            var_r29 = 1;
        }
        if ((fn_1_B70C(b) != 0) && ((s16) b->kind != 1)) {
            var_r29 = 1;
        }
        if ((fn_1_BAC8(b) != 0) && ((s16) b->kind != 1)) {
            var_r29 = 1;
        }
    } else {
        fn_1_BECC(b);
        fn_1_B70C(b);
        fn_1_BAC8(b);
    }
    if (var_r29 == 0) {
        var_r26 = 0;
loop_41:
        if (var_r26 >= 1) {
            var_r30 += 1;
            goto loop_43;
        }
        HuPrcVSleep();
        temp_r23 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r18 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r23;
        if (temp_r23 == temp_r18) {
            var_r26 += 1;
            goto loop_41;
        }
    } else {
block_44:
        b->active = 0;
        if (((s16) b->kind == 3) || ((s16) b->kind == 2)) {
            sp10 = 0x14;
            var_r25 = 0;
loop_49:
            if (var_r25 >= sp10) {
                goto block_50;
            }
            HuPrcVSleep();
            temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
            temp_r0_3 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
            spA = temp_r0_3;
            ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r22;
            if (temp_r22 == temp_r0_3) {
                var_r25 += 1;
                goto loop_49;
            }
        } else {
block_50:
            if (var_r29 != 0) {
                Hu3DModelAttrSet(b->mdl[0], 1U);
                Hu3DModelAttrReset(b->mdl[1], 1U);
                Hu3DMotionTimeSet(b->mdl[1], 0.0f);
                spC = (s32) Hu3DMotionMaxTimeGet(b->mdl[1]);
                var_r24 = 0;
loop_54:
                if (var_r24 >= spC) {
                    Hu3DModelAttrReset(b->mdl[1], 1U);
                    goto block_56;
                }
                HuPrcVSleep();
                temp_r21 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
                temp_r0_4 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
                sp8 = temp_r0_4;
                ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r21;
                if (temp_r21 == temp_r0_4) {
                    var_r24 += 1;
                    goto loop_54;
                }
            } else {
block_56:
                sp14 = lbl_1_rodata_E74.x;
                sp18 = lbl_1_rodata_E74.y;
                sp1C = lbl_1_rodata_E74.z;
                b->pos.x = lbl_1_rodata_E74.x;
                b->pos.y = lbl_1_rodata_E74.y;
                b->pos.z = lbl_1_rodata_E74.z;
                var_r27 = 0;
loop_58:
                if (var_r27 < 2) {
                    Hu3DModelPosSet(b->mdl[var_r27], sp14, sp18, sp1C);
                    var_r27 += 1;
                    goto loop_58;
                }
                b->state = 0;
            }
        }
    }
}

s32 fn_1_B70C(M519Bullet *b) {
    Vec sp14;
    Vec sp20;
    f32 sp10;
    f32 spC;
    f32 sp8;
    M519Mech *temp_r27;
    M519Mech *temp_r30;
    f32 temp_r0_2;
    f32 temp_r0_3;
    f32 temp_r3;
    s16 temp_r0;
    s32 var_r28;
    s32 var_r29;

    if ((s16) b->owner == -1) {
        return 0;
    }
    temp_r27 = lbl_1_bss_F8[b->owner];
    sp20.x = b->pos.x;
    sp20.y = b->pos.z;
    sp20.z = b->radius;
    var_r29 = 0;
loop_21:
    if (var_r29 >= 4) {
        return 0;
    }
    temp_r30 = lbl_1_bss_F8[var_r29];
    if ((temp_r30 != temp_r27) && ((s16) temp_r30->state != 3)) {
        sp14.x = temp_r30->pos.x;
        sp14.y = temp_r30->pos.z;
        sp14.z = temp_r30->radius;
        if (fn_1_F860(&sp20, &sp14, 1) != 0) {
            HuAudFXPlay(lbl_1_rodata_E98[temp_r30->type]);
            if (((s16) temp_r30->type != (s16) temp_r27->type) && ((s16) temp_r30->lastHitter != (s16) b->id) && ((s32) lbl_1_bss_8 == 0)) {
                temp_r0 = temp_r30->hp - b->dmg;
                temp_r30->hp = temp_r0;
                if (temp_r0 < 0) {
                    temp_r30->hp = 0;
                }
            }
            temp_r30->lastHitter = b->id;
            if ((s32) b->stick != 0) {
                b->pos.x = sp20.x;
                b->pos.z = sp20.y;
                temp_r3 = b->pos.x;
                temp_r0_2 = b->pos.y;
                sp8 = temp_r3;
                spC = temp_r0_2;
                temp_r0_3 = b->pos.z;
                sp10 = temp_r0_3;
                b->pos.x = temp_r3;
                b->pos.y = temp_r0_2;
                b->pos.z = temp_r0_3;
                var_r28 = 0;
loop_14:
                if (var_r28 < 2) {
                    Hu3DModelPosSet(b->mdl[var_r28], sp8, spC, sp10);
                    var_r28 += 1;
                    goto loop_14;
                }
            }
            if ((s16) temp_r30->state == 1) {
                if (b->curSpeed == 0.0f) {
                    b->rot.y = (f32) (180.0 * (atan2((f64) (temp_r30->pos.x - b->pos.x), (f64) (temp_r30->pos.z - b->pos.z)) / 3.141592653589793));
                }
                temp_r30->push = (f32) b->pushPow;
                temp_r30->pushDir = b->rot.y;
            }
            return 1;
        }
    }
    var_r29 += 1;
    goto loop_21;
}

s32 fn_1_B9BC(M519Bullet *b) {
    Vec sp14;
    Vec sp20;
    f32 sp10;
    f32 spC;
    f32 sp8;
    f32 temp_r0;
    f32 temp_r0_2;
    f32 temp_r3;
    s32 var_r30;

    sp20.x = b->pos.x;
    sp20.y = b->pos.z;
    sp20.z = b->radius;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = 2390.0f;
    if (fn_1_FA6C(&sp20, &sp14, 1) != 0) {
        b->pos.x = sp20.x;
        b->pos.z = sp20.y;
        temp_r3 = b->pos.x;
        temp_r0 = b->pos.y;
        sp8 = temp_r3;
        spC = temp_r0;
        temp_r0_2 = b->pos.z;
        sp10 = temp_r0_2;
        b->pos.x = temp_r3;
        b->pos.y = temp_r0;
        b->pos.z = temp_r0_2;
        var_r30 = 0;
loop_3:
        if (var_r30 < 2) {
            Hu3DModelPosSet(b->mdl[var_r30], sp8, spC, sp10);
            var_r30 += 1;
            goto loop_3;
        }
        return 1;
    }
    return 0;
}

s32 fn_1_BAC8(M519Bullet *b) {
    Vec sp3C;
    Vec sp18;
    Vec sp30;
    Vec sp54;
    Vec sp60;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    Vec sp24;
    f32 sp14;
    f32 sp10;
    f32 spC;
    f32 sp8;
    M519Bld *temp_r30;
    M519Mech *temp_r29;
    f32 temp_r0_2;
    f32 temp_r0_3;
    f32 temp_r3;
    f32 var_f31;
    f32 var_f31_2;
    s16 temp_r0;
    s16 temp_r22;
    s16 temp_r22_2;
    s32 var_r27;
    s32 var_r28;

    sp60.x = b->pos.x;
    sp60.y = b->pos.z;
    sp60.z = b->radius;
    var_r28 = 0;
loop_25:
    if (var_r28 >= 0xC) {
        return 0;
    }
    temp_r30 = lbl_1_bss_178->bld[var_r28];
    if ((temp_r30 != NULL) && ((s16) temp_r30->state == 3) && ((s16) temp_r30->hp > 0) && ((s16) temp_r30->lastHit != (s16) b->id)) {
        sp54.x = temp_r30->pos.x;
        sp54.y = temp_r30->pos.z;
        sp54.z = temp_r30->radius;
        if (fn_1_F860(&sp60, &sp54, 1) != 0) {
            temp_r29 = lbl_1_bss_F8[b->owner];
            sp48 = temp_r30->pos.x;
            sp4C = temp_r30->pos.y;
            sp50 = temp_r30->pos.z;
            var_f31 = 0.0f;
            if ((sp48 != temp_r29->pos.x) || (sp50 != temp_r29->pos.z)) {
                var_f31_2 = (f32) ((180.0 + (180.0 * (atan2((f64) (temp_r29->pos.x - sp48), (f64) (temp_r29->pos.z - sp50)) / 3.141592653589793))) - (f64) temp_r29->rot.y);
                if (var_f31_2 < 0.0f) {
                    var_f31_2 += 360.0f;
                }
                if (var_f31_2 >= 360.0f) {
                    var_f31_2 -= 360.0f;
                }
                if (var_f31_2 >= 180.0f) {
                    var_f31_2 -= 360.0f;
                }
                var_f31 = -var_f31_2;
            }
            sp8 = var_f31;
            sp30.x = b->pos.x;
            sp30.y = b->pos.y;
            sp30.z = b->pos.z;
            sp3C.x = b->pos.x;
            sp3C.y = b->pos.y;
            sp3C.z = b->pos.z;
            temp_r22 = fn_1_10244(1U, &sp30);
            HuAudFXPlayVolPan(lbl_1_rodata_EC8[0], fn_1_FE20(1U, &sp3C), temp_r22);
            sp18.x = b->pos.x;
            sp18.y = b->pos.y;
            sp18.z = b->pos.z;

            temp_r22_2 = fn_1_10244(0xEU, &sp18);
            HuAudFXPlayVolPan(lbl_1_rodata_EC8[1], fn_1_FE20(0xEU, &sp18), temp_r22_2);
            if (((s32) lbl_1_rodata_EA0[b->kind].n[temp_r30->type] != 0) && ((s16) temp_r30->lastHit != (s16) b->id)) {
                temp_r0 = temp_r30->hp - b->dmg;
                temp_r30->hp = temp_r0;
                if (temp_r0 < 0) {
                    temp_r30->hp = 0;
                }
            }
            temp_r30->lastHit = b->id;
            temp_r30->lastShooter = b->owner;
            if ((s32) b->stick != 0) {
                b->pos.x = sp60.x;
                b->pos.z = sp60.y;
                temp_r3 = b->pos.x;
                temp_r0_2 = b->pos.y;
                spC = temp_r3;
                sp10 = temp_r0_2;
                temp_r0_3 = b->pos.z;
                sp14 = temp_r0_3;
                b->pos.x = temp_r3;
                b->pos.y = temp_r0_2;
                b->pos.z = temp_r0_3;
                var_r27 = 0;
loop_22:
                if (var_r27 < 2) {
                    Hu3DModelPosSet(b->mdl[var_r27], spC, sp10, sp14);
                    var_r27 += 1;
                    goto loop_22;
                }
            }
            return 1;
        }
    }
    var_r28 += 1;
    goto loop_25;
}

s32 fn_1_BECC(M519Bullet *b) {
    Vec sp14;
    Vec sp20;
    f32 sp10;
    f32 spC;
    f32 sp8;
    M519Bullet *temp_r30;
    f32 temp_r0;
    f32 temp_r0_2;
    f32 temp_r3;
    s32 var_r28;
    s32 var_r29;

    if ((s16) b->kind == 1) {
        return 0;
    }
    sp20.x = b->pos.x;
    sp20.y = b->pos.z;
    sp20.z = b->radius;
    var_r29 = 0;
loop_15:
    if (var_r29 >= 0x2C) {
        return 0;
    }
    temp_r30 = lbl_1_bss_38[var_r29];
    if ((temp_r30 != NULL) && ((s16) b->state == 1) && ((s32) temp_r30->active != 0) && ((s16) temp_r30->owner != (s16) b->owner) && (temp_r30 != b)) {
        sp14.x = temp_r30->pos.x;
        sp14.y = temp_r30->pos.z;
        sp14.z = temp_r30->radius;
        if (fn_1_F860(&sp20, &sp14, 1) != 0) {
            if ((s32) b->stick != 0) {
                b->pos.x = sp20.x;
                b->pos.z = sp20.y;
                temp_r3 = b->pos.x;
                temp_r0 = b->pos.y;
                sp8 = temp_r3;
                spC = temp_r0;
                temp_r0_2 = b->pos.z;
                sp10 = temp_r0_2;
                b->pos.x = temp_r3;
                b->pos.y = temp_r0;
                b->pos.z = temp_r0_2;
                var_r28 = 0;
loop_12:
                if (var_r28 < 2) {
                    Hu3DModelPosSet(b->mdl[var_r28], sp8, spC, sp10);
                    var_r28 += 1;
                    goto loop_12;
                }
            }
            return 1;
        }
    }
    var_r29 += 1;
    goto loop_15;
}

M519Bld *fn_1_C058(s16 type) {
    M519Bld *temp_r3;
    s32 var_r30;

    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Bld), MEMORY_DEFAULT_NUM);
    temp_r3->type = type;
    temp_r3->lastHit = -1;
    temp_r3->radius = (f32) lbl_1_rodata_F18[type];
    temp_r3->hp = 1;
    temp_r3->pos.x = 0.0f;
    temp_r3->pos.y = 0.0f;
    temp_r3->pos.z = 0.0f;
    temp_r3->rot.x = 0.0f;
    temp_r3->rot.y = 0.0f;
    temp_r3->rot.z = 0.0f;
    temp_r3->respawn = 0;
    temp_r3->lastShooter = -1;
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        temp_r3->mdl[var_r30] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_ED0[lbl_1_bss_30].n[var_r30 + (type * 3)], MEMORY_DEFAULT_NUM, HEAP_DATA));
        Hu3DModelAttrSet(temp_r3->mdl[var_r30], 1U);
        Hu3DModelAttrSet(temp_r3->mdl[var_r30], 0x4000U);
        Hu3DModelLayerSet(temp_r3->mdl[var_r30], 2);
        var_r30 += 1;
        goto loop_2;
    }
    temp_r3->proc = HuPrcChildCreate(fn_1_C248, 0x900U, 0x2000U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    return temp_r3;
}

void fn_1_C248(void) {
    M519Bld *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_64[temp_r31->state](temp_r31);
    }
}

void fn_1_C288(M519Bld *b, Vec *pos) {
    s32 var_r30;

    b->pos.x = pos->x;
    b->pos.y = pos->y;
    b->pos.z = pos->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        Hu3DModelPosSet(b->mdl[var_r30], pos->x, pos->y, pos->z);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_C328(M519Bld *b, Vec *rot) {
    s32 var_r30;

    b->rot.x = rot->x;
    b->rot.y = rot->y;
    b->rot.z = rot->z;
    var_r30 = 0;
loop_2:
    if (var_r30 < 3) {
        Hu3DModelRotSet(b->mdl[var_r30], rot->x, rot->y, rot->z);
        var_r30 += 1;
        goto loop_2;
    }
}


void fn_1_C3C8(M519Bld *b) {
    b->state = 0;
}

void fn_1_C3D4(M519Bld *b) {
    s16 temp_r29;
    s16 temp_r30;
    s32 var_r31;

loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r30 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r30;
    if (temp_r30 == temp_r29) {
        var_r31 += 1;
        goto loop_4;
    }
}


void fn_1_C470(M519Bld *b) {
    s16 temp_r28;
    s16 temp_r29;
    s32 var_r30;

    Hu3DModelAttrReset(b->mdl[0], 1U);
    Hu3DMotionTimeSet(b->mdl[0], 0.0f);
    Hu3DModelAttrSet(b->mdl[1], 1U);
    Hu3DModelAttrSet(b->mdl[2], 1U);
loop_1:
    if ((s16) b->hp <= 0) {
        fn_1_C788(b, 1);
    }
    var_r30 = 0;
loop_6:
    if (var_r30 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
    if (temp_r29 == temp_r28) {
        var_r30 += 1;
        goto loop_6;
    }
}

void fn_1_C544(M519Bld *b) {
    b->hp = lbl_1_rodata_F1C[b->type];
    b->state = 1;
}

void fn_1_C570(M519Bld *b) {
    Vec sp18;
    Vec sp30;
    Vec spC;
    Vec sp24;
    M519Mech *sp8;
    s16 temp_r22;
    s16 temp_r22_2;
    s16 temp_r28;
    s16 temp_r29;
    s32 temp_r27;
    s32 var_r30;

    if ((s16) b->lastShooter != -1) {
        sp8 = lbl_1_bss_F8[b->lastShooter];
        sp24.x = b->pos.x;
        sp24.y = b->pos.y;
        sp24.z = b->pos.z;
        sp30.x = b->pos.x;
        sp30.y = b->pos.y;
        sp30.z = b->pos.z;
        temp_r22 = fn_1_10244(1U, &sp24);
        HuAudFXPlayVolPan(lbl_1_rodata_F20[0], fn_1_FE20(1U, &sp30), temp_r22);
        spC.x = b->pos.x;
        spC.y = b->pos.y;
        spC.z = b->pos.z;
        sp18.x = b->pos.x;
        sp18.y = b->pos.y;
        sp18.z = b->pos.z;
        temp_r22_2 = fn_1_10244(0xEU, &spC);
        HuAudFXPlayVolPan(lbl_1_rodata_F20[1], fn_1_FE20(0xEU, &sp18), temp_r22_2);
    }
    b->lastShooter = -1;
    Hu3DModelAttrReset(b->mdl[1], 0x40000002U);
    Hu3DModelAttrReset(b->mdl[1], 1U);
    Hu3DMotionTimeSet(b->mdl[1], 0.0f);
    Hu3DModelAttrSet(b->mdl[0], 1U);
    Hu3DModelAttrSet(b->mdl[2], 1U);
    Hu3DModelAttrSet(b->mdl[0], 0x40000002U);
    Hu3DModelAttrSet(b->mdl[2], 0x40000002U);
    temp_r27 = (s32) Hu3DMotionMaxTimeGet(b->mdl[1]);
    var_r30 = 0;
loop_5:
    if (var_r30 >= temp_r27) {
        Hu3DModelAttrReset(b->mdl[1], 0x40000002U);
        b->state = 3;
    } else {
        HuPrcVSleep();
        temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r29;
        if (temp_r29 == temp_r28) {
            var_r30 += 1;
            goto loop_5;
        }
    }
}

void fn_1_C788(M519Bld *b, s32 respawn) {
    b->respawn = respawn;
    b->state = 2;
}

void fn_1_C798(M519Bld *b) {
    Vec sp58;
    Vec sp64;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    f32 *sp18;
    f32 *sp14;
    f32 *sp10;
    f32 *spC;
    s16 spA;
    s16 sp8;
    M519Mech *temp_r29;
    s16 temp_r0;
    s16 temp_r0_2;
    s16 temp_r16;
    s16 temp_r16_2;
    s16 temp_r17;
    s16 temp_r19;
    s16 temp_r21;
    s16 temp_r22;
    s16 temp_r23;
    s16 temp_r24;
    s32 temp_r18;
    s32 temp_r20;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r30;
    s32 var_r30_2;

    if ((s16) b->lastShooter != -1) {
        Vec sndA = b->pos, sndB = b->pos, sndC = b->pos, sndD = b->pos;
        temp_r16 = fn_1_10244(1U, &sndA);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[0], fn_1_FE20(1U, &sndB), temp_r16);
        temp_r16_2 = fn_1_10244(0xEU, &sndC);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[1], fn_1_FE20(0xEU, &sndD), temp_r16_2);
    }
    Hu3DModelAttrReset(b->mdl[2], 1U);
    Hu3DModelAttrReset(b->mdl[2], 0x40000002U);
    Hu3DMotionTimeSet(b->mdl[2], 0.0f);
    Hu3DModelAttrSet(b->mdl[0], 1U);
    Hu3DModelAttrSet(b->mdl[1], 1U);
    Hu3DModelAttrSet(b->mdl[0], 0x40000002U);
    Hu3DModelAttrSet(b->mdl[1], 0x40000002U);
    temp_r18 = (s32) Hu3DMotionMaxTimeGet(b->mdl[1]);
    var_r28 = 0;
loop_5:
    if (var_r28 >= temp_r18) {
        Hu3DModelAttrSet(b->mdl[2], 1U);
        Hu3DModelAttrSet(b->mdl[2], 0x40000002U);
        temp_r20 = lbl_1_rodata_F30[b->type];
        var_r30 = 0;
loop_12:
        if (var_r30 >= temp_r20) {
            sp64.x = b->pos.x;
            sp64.y = b->pos.z;
            sp64.z = 100.0f + b->radius;
            if ((s32) b->respawn != 0) {
loop_14:
                var_r30_2 = 0;
loop_20:
                if (var_r30_2 < 4) {
                    temp_r29 = lbl_1_bss_F8[var_r30_2];
                    if ((temp_r29 == NULL) || (sp58.x = temp_r29->pos.x, sp58.y = temp_r29->pos.z, sp58.z = temp_r29->radius, ((fn_1_F860(&sp64, &sp58, 0) == 0) != 0)) || ((s32) lbl_1_bss_0 != 0) || ((s32) lbl_1_bss_4 != 0)) {
                        var_r30_2 += 1;
                        goto loop_20;
                    }
                }
                if (var_r30_2 != 4) {
                    sp20 = 1;
                    var_r26 = 0;
loop_25:
                    if (var_r26 >= sp20) {
                        goto loop_14;
                    }
                    HuPrcVSleep();
                    temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
                    temp_r0 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
                    spA = temp_r0;
                    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r22;
                    if (temp_r22 == temp_r0) {
                        var_r26 += 1;
                        goto loop_25;
                    }
                } else {
                    b->hp = lbl_1_rodata_F1C[b->type];
                    b->state = 1;
                }
            } else {
loop_27:
                sp1C = 1;
                var_r25 = 0;
loop_30:
                if (var_r25 >= sp1C) {
                    goto loop_27;
                }
                HuPrcVSleep();
                temp_r21 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
                temp_r0_2 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
                sp8 = temp_r0_2;
                ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r21;
                if (temp_r21 == temp_r0_2) {
                    var_r25 += 1;
                    goto loop_30;
                }
            }
        } else {
            sp24 = 1;
            var_r27 = 0;
loop_10:
            if (var_r27 >= sp24) {
                var_r30 += 1;
                goto loop_12;
            }
            HuPrcVSleep();
            temp_r23 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
            temp_r17 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
            ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r23;
            if (temp_r23 == temp_r17) {
                var_r27 += 1;
                goto loop_10;
            }
        }
    } else {
        HuPrcVSleep();
        temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r19 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r24;
        if (temp_r24 == temp_r19) {
            var_r28 += 1;
            goto loop_5;
        }
    }
}

void fn_1_CBEC(M519Bld *b) {
    s32 var_r31;

    var_r31 = 0;
loop_2:
    if (var_r31 < 3) {
        Hu3DModelAttrSet(b->mdl[var_r31], 1U);
        var_r31 += 1;
        goto loop_2;
    }
}

M519Part *fn_1_CC44(void) {
    M519Part *temp_r31;

    temp_r31 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Part), MEMORY_DEFAULT_NUM);
    temp_r31->anim = HuSprAnimRead(HuDataSelHeapReadNum(DATA_MAKE_NUM(DATADIR_MP5_M519, 69), MEMORY_DEFAULT_NUM, HEAP_DATA));
    temp_r31->model = Hu3DParticleCreate(temp_r31->anim, 0x2A);
    Hu3DParticleBlendModeSet(temp_r31->model, 1U);
    ((HU3DPARTICLE *) Hu3DData[temp_r31->model].hookData)->work = temp_r31;
    Hu3DParticleHookSet(temp_r31->model, fn_1_CCF4);
    return temp_r31;
}

void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    lbl_1_data_74[particleP->dataCnt](particleP->work, modelP, particleP, mtx);
}

void fn_1_CD54(M519Part *p, Vec *pos) {
    p->pos.x = pos->x;
    p->pos.y = pos->y;
    p->pos.z = pos->z;
}



void fn_1_CDF0(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {

}

void fn_1_CDF4(M519Part *p) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    Hu3DModelAttrReset(p->model, 1U);
    temp_r30 = Hu3DData[p->model].hookData;
    var_r29 = 0;
    var_r31 = temp_r30->data;
loop_2:
    if (var_r29 < (s16) temp_r30->maxCnt) {
        var_r31->time = 0;
        var_r31->parManId = 0;
        var_r31->pos.x = 0.0f;
        var_r31->pos.y = -100.0f;
        var_r31->pos.z = 0.0f;
        var_r31->color.r = 0xFF;
        var_r31->color.g = 0xFF;
        var_r31->color.b = 0xFF;
        var_r31->color.a = 0xFF;
        var_r31->scale = 1.0f;
        var_r29 += 1;
        var_r31++;
        goto loop_2;
    }
    temp_r30->dataCnt = 1;
}

void fn_1_CEE4(void *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    s16 temp_r0;
    s16 temp_r3;
    s32 var_r30;

    var_r30 = 0;
    var_r31 = particleP->data;
loop_9:
    if (var_r30 < (s16) particleP->maxCnt) {
        temp_r0 = var_r31->time;
        switch (temp_r0) {                          /* irregular */
        case 0:
            var_r31->pos.x = 0.0f;
            var_r31->pos.y = -100.0f;
            var_r31->pos.z = 0.0f;
            break;
        case 1:
            var_r31->color.a = 0x40 - (s32) (4.0f * (f32) var_r31->parManId);
            temp_r3 = var_r31->parManId;
            var_r31->parManId = temp_r3 + 1;
            if (temp_r3 > 0x10) {
                var_r31->color.a = 0;
                var_r31->time = 0;
            }
            break;
        }
        var_r30 += 1;
        var_r31++;
        goto loop_9;
    }
}

s32 fn_1_CFE8(M519Part *p) {
    s32 var_r29;
    HU3DPARTICLE *temp_r30;
    HU3DPARTICLEDATA *var_r31;

    temp_r30 = Hu3DData[p->model].hookData;
    var_r31 = temp_r30->data;
    var_r29 = 0;
loop_4:
    if (var_r29 >= (s16) temp_r30->maxCnt) {
        return 0;
    }
    if ((s16) var_r31->time == 0) {
        var_r31->time = 1;
        var_r31->parManId = 0;
        var_r31->pos.x = (f32) p->pos.x;
        var_r31->pos.y = (f32) p->pos.y;
        var_r31->pos.z = (f32) p->pos.z;
        var_r31->color.r = 0xFF;
        var_r31->color.g = 0xFF;
        var_r31->color.b = 0xFF;
        var_r31->color.a = 0xFF;
        var_r31->scale = 5.0f;
        return 1;
    }
    var_r29 += 1;
    var_r31++;
    goto loop_4;
}

M519Hud *fn_1_D0BC(s16 type, s16 mech) {
    s16 sp8;
    M519Hud *temp_r3;
    s16 temp_r0;
    s32 var_r30;
    s32 var_r30_2;

    sp8 = mech;
    temp_r3 = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Hud), MEMORY_DEFAULT_NUM);
    temp_r3->type = type;
    temp_r3->pad_6 = 0;
    temp_r3->mech = sp8;
    temp_r3->state = 0;
    temp_r3->prevState = 0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 0x12) {
        if ((s32) lbl_1_rodata_F44[type].n[var_r30] != -1) {
            temp_r3->spr[var_r30] = espEntry((u32) lbl_1_rodata_F44[type].n[var_r30], 0, 0);
            espDispOff(temp_r3->spr[var_r30]);
        } else {
            temp_r3->spr[var_r30] = -1;
        }
        var_r30 += 1;
        goto loop_5;
    }
    temp_r0 = temp_r3->type;
    if (temp_r0 != 0) {
        if ((temp_r0 >= 0) && (temp_r0 < 4)) {
            espPriSet(temp_r3->spr[0], 0x3E8);
            espPriSet(temp_r3->spr[1], 0x384);
            espPriSet(temp_r3->spr[2], 0x384);
            espPriSet(temp_r3->spr[3], 0x3B6);
            espPriSet(temp_r3->spr[4], 0x3C0);
            espPriSet(temp_r3->spr[5], 0x3CA);
            espPriSet(temp_r3->spr[6], 0x3D4);
            espPriSet(temp_r3->spr[7], 0x384);
            espPriSet(temp_r3->spr[8], 0x38E);
            espPriSet(temp_r3->spr[9], 0x398);
            espPriSet(temp_r3->spr[0xA], 0x384);
            espPriSet(temp_r3->spr[0xB], 0x38E);
            espPriSet(temp_r3->spr[0xC], 0x398);
            espPriSet(temp_r3->spr[0x10], 0x384);
            espPriSet(temp_r3->spr[0x11], 0x384);
            espScaleSet(temp_r3->spr[7], 0.6f, 0.6f);
            espScaleSet(temp_r3->spr[8], 0.6f, 0.6f);
            espScaleSet(temp_r3->spr[9], 0.6f, 0.6f);
            espScaleSet(temp_r3->spr[0xA], 0.35f, 0.35f);
            espScaleSet(temp_r3->spr[0xB], 0.35f, 0.35f);
            espScaleSet(temp_r3->spr[0xC], 0.35f, 0.35f);
            espScaleSet(temp_r3->spr[0x10], 0.58f, 0.58f);
            espScaleSet(temp_r3->spr[0x11], 0.68f, 0.68f);
        }
    } else {
        espPriSet(temp_r3->spr[0], 0x3E8);
        espPriSet(temp_r3->spr[1], 0x384);
        espPriSet(temp_r3->spr[2], 0x384);
        espPriSet(temp_r3->spr[3], 0x3B6);
        espPriSet(temp_r3->spr[4], 0x3C0);
        espPriSet(temp_r3->spr[5], 0x3CA);
        espPriSet(temp_r3->spr[6], 0x3D4);
        espPriSet(temp_r3->spr[7], 0x384);
        espPriSet(temp_r3->spr[8], 0x38E);
        espPriSet(temp_r3->spr[9], 0x398);
        espPriSet(temp_r3->spr[0xA], 0x384);
        espPriSet(temp_r3->spr[0xB], 0x38E);
        espPriSet(temp_r3->spr[0xC], 0x398);
        espPriSet(temp_r3->spr[0xD], 0x384);
        espPriSet(temp_r3->spr[0xE], 0x38E);
        espPriSet(temp_r3->spr[0xF], 0x398);
        espPriSet(temp_r3->spr[0x10], 0x384);
        espPriSet(temp_r3->spr[0x11], 0x384);
        espScaleSet(temp_r3->spr[7], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[8], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[9], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xA], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xB], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xC], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xD], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xE], 0.6f, 0.6f);
        espScaleSet(temp_r3->spr[0xF], 0.6f, 0.6f);
    }
    var_r30_2 = 0;
loop_14:
    if (var_r30_2 < 0x12) {
        temp_r3->ofs[var_r30_2] = lbl_1_rodata_1064[type].ofs[var_r30_2];
        var_r30_2 += 1;
        goto loop_14;
    }
    temp_r3->proc = HuPrcChildCreate(fn_1_D610, 0x1000U, 0x1800U, 0, HuPrcCurrentGet());
    temp_r3->proc->property = temp_r3;
    return temp_r3;
}

void fn_1_D610(void) {
    M519Hud *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_7C[temp_r31->type][temp_r31->state](temp_r31);
    }
}

void fn_1_D65C(M519Hud *h, Vec *pos) {
    s32 var_r30;

    h->x = pos->x;
    h->y = pos->y;
    var_r30 = 0;
loop_4:
    if (var_r30 < 0x12) {
        if ((s16) h->spr[var_r30] != -1) {
            espPosSet(h->spr[var_r30], pos->x + h->ofs[var_r30].x, pos->y + h->ofs[var_r30].y);
        }
        var_r30 += 1;
        goto loop_4;
    }
}



void fn_1_D720(M519Hud *h) {
    s16 temp_r29;
    s16 temp_r30;
    s32 var_r31;

loop_1:
    var_r31 = 0;
loop_4:
    if (var_r31 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r30 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r29 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r30;
    if (temp_r30 == temp_r29) {
        var_r31 += 1;
        goto loop_4;
    }
}

void fn_1_D7B0(M519Hud *h) {
    h->state = 1;
}

void fn_1_D7BC(M519Hud *h) {
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    M519Mech *sp8;
    f32 temp_f31;
    s16 temp_r20;
    s16 temp_r22;
    s16 temp_r23;
    s16 temp_r24;
    s32 var_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;

    sp8 = lbl_1_bss_F8[h->mech];
    sp24 = h->x;
    sp28 = h->y;
    espDispOn(h->spr[0]);
    var_r30 = 1;
loop_11:
    if (var_r30 > 0x3C) {
        sp28 -= 100.0f;
        spC = sp24;
        sp10 = sp28;
        h->x = sp24;
        h->y = sp28;
        var_r28 = 0;
loop_16:
        if (var_r28 < 0x12) {
            if ((s16) h->spr[var_r28] != -1) {
                espPosSet(h->spr[var_r28], spC + h->ofs[var_r28].x, sp10 + h->ofs[var_r28].y);
            }
            var_r28 += 1;
            goto loop_16;
        }
        espDispOn(h->spr[2]);
        espDispOn(h->spr[1]);
        espDispOn(h->spr[3]);
        espDispOn(h->spr[4]);
        espDispOn(h->spr[5]);
        espDispOn(h->spr[6]);
        espDispOn(h->spr[7]);
        espDispOn(h->spr[8]);
        espDispOn(h->spr[9]);
        espDispOn(h->spr[0xA]);
        espDispOn(h->spr[0xB]);
        espDispOn(h->spr[0xC]);
        espDispOn(h->spr[0xD]);
        espDispOn(h->spr[0xE]);
        espDispOn(h->spr[0xF]);
        espDispOn(h->spr[0x10]);
        fn_1_E298(h);
        fn_1_E2D4(h);
        fn_1_E714(h);
        var_r27 = 1;
loop_26:
        if (var_r27 > 0x64) {
            fn_1_E168(h);
        } else {
            temp_f31 = (f32) sin((3.141592653589793 * (f64) (90.0f * (0.01f * (f32) var_r27))) / 180.0);
            espScaleSet(h->spr[2], 108.0f * temp_f31, 0.8f);
            espTPLvlSet(h->spr[2], 0.8f * temp_f31);
            espTPLvlSet(h->spr[7], temp_f31);
            espTPLvlSet(h->spr[8], 0.0f);
            espTPLvlSet(h->spr[9], 0.0f);
            espTPLvlSet(h->spr[0xA], temp_f31);
            espTPLvlSet(h->spr[0xB], 0.0f);
            espTPLvlSet(h->spr[0xC], 0.0f);
            espTPLvlSet(h->spr[0xD], temp_f31);
            espTPLvlSet(h->spr[0xE], 0.0f);
            espTPLvlSet(h->spr[0xF], 0.0f);
            espTPLvlSet(h->spr[0x10], 0.2f * temp_f31);
            espZRotSet(h->spr[1], 720.0f * temp_f31);
            espTPLvlSet(h->spr[1], 0.5f * temp_f31);
            var_r30_2 = 0;
loop_20:
            if (var_r30_2 < 4) {
                espTPLvlSet(h->spr[var_r30_2 + 3], temp_f31);
                var_r30_2 += 1;
                goto loop_20;
            }
            var_r25 = 0;
loop_24:
            if (var_r25 >= 1) {
                var_r27 += 1;
                goto loop_26;
            }
            HuPrcVSleep();
            temp_r23 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
            temp_r20 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
            ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r23;
            if (temp_r23 == temp_r20) {
                var_r25 += 1;
                goto loop_24;
            }
        }
    } else {
        sp1C = sp24;
        sp20 = (f32) ((f64) sp28 - (100.0 * sin((3.141592653589793 * (f64) (90.0f * (0.016666668f * (f32) var_r30))) / 180.0)));
        sp14 = sp1C;
        sp18 = sp20;
        h->x = sp1C;
        h->y = sp20;
        var_r29 = 0;
loop_5:
        if (var_r29 < 0x12) {
            if ((s16) h->spr[var_r29] != -1) {
                espPosSet(h->spr[var_r29], sp14 + h->ofs[var_r29].x, sp18 + h->ofs[var_r29].y);
            }
            var_r29 += 1;
            goto loop_5;
        }
        var_r26 = 0;
loop_9:
        if (var_r26 >= 1) {
            var_r30 += 1;
            goto loop_11;
        }
        HuPrcVSleep();
        temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r22 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r24;
        if (temp_r24 == temp_r22) {
            var_r26 += 1;
            goto loop_9;
        }
    }
}

void fn_1_DD08(M519Hud *h) {
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    M519Mech *sp8;
    f32 temp_f31;
    s16 temp_r21;
    s16 temp_r23;
    s16 temp_r24;
    s16 temp_r25;
    s32 var_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;
    s32 var_r30_2;

    sp8 = lbl_1_bss_F8[h->mech];
    sp24 = h->x;
    sp28 = h->y;
    espDispOn(h->spr[0]);
    var_r30 = 1;
loop_11:
    if (var_r30 > 0x3C) {
        sp24 -= 96.0f;
        spC = sp24;
        sp10 = sp28;
        h->x = sp24;
        h->y = sp28;
        var_r28 = 0;
loop_16:
        if (var_r28 < 0x12) {
            if ((s16) h->spr[var_r28] != -1) {
                espPosSet(h->spr[var_r28], spC + h->ofs[var_r28].x, sp10 + h->ofs[var_r28].y);
            }
            var_r28 += 1;
            goto loop_16;
        }
        espDispOn(h->spr[7]);
        espDispOn(h->spr[8]);
        espDispOn(h->spr[9]);
        espDispOn(h->spr[2]);
        espDispOn(h->spr[0x10]);
        var_r30_2 = 1;
loop_23:
        if (var_r30_2 > 0x64) {
            fn_1_E168(h);
        } else {
            temp_f31 = (f32) sin((3.141592653589793 * (f64) (90.0f * (0.01f * (f32) var_r30_2))) / 180.0);
            espTPLvlSet(h->spr[7], temp_f31);
            espTPLvlSet(h->spr[8], 0.0f);
            espTPLvlSet(h->spr[9], 0.0f);
            espTPLvlSet(h->spr[0xA], temp_f31);
            espTPLvlSet(h->spr[0xB], 0.0f);
            espTPLvlSet(h->spr[0xC], 0.0f);
            espTPLvlSet(h->spr[0x10], 0.2f * temp_f31);
            espZRotSet(h->spr[2], -90.0f);
            espScaleSet(h->spr[2], 72.0f * temp_f31, 0.8f);
            espTPLvlSet(h->spr[2], 0.8f * temp_f31);
            var_r26 = 0;
loop_21:
            if (var_r26 >= 1) {
                var_r30_2 += 1;
                goto loop_23;
            }
            HuPrcVSleep();
            temp_r24 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
            temp_r21 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
            ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r24;
            if (temp_r24 == temp_r21) {
                var_r26 += 1;
                goto loop_21;
            }
        }
    } else {
        sp1C = (f32) ((f64) sp24 - (96.0 * sin((3.141592653589793 * (f64) (90.0f * (0.016666668f * (f32) var_r30))) / 180.0)));
        sp20 = sp28;
        sp14 = sp1C;
        sp18 = sp20;
        h->x = sp1C;
        h->y = sp20;
        var_r29 = 0;
loop_5:
        if (var_r29 < 0x12) {
            if ((s16) h->spr[var_r29] != -1) {
                espPosSet(h->spr[var_r29], sp14 + h->ofs[var_r29].x, sp18 + h->ofs[var_r29].y);
            }
            var_r29 += 1;
            goto loop_5;
        }
        var_r27 = 0;
loop_9:
        if (var_r27 >= 1) {
            var_r30 += 1;
            goto loop_11;
        }
        HuPrcVSleep();
        temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r23 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r25;
        if (temp_r25 == temp_r23) {
            var_r27 += 1;
            goto loop_9;
        }
    }
}

void fn_1_E168(M519Hud *h) {
    h->state = 2;
}

void fn_1_E174(M519Hud *h) {
    f32 spC;
    f32 sp8;
    f32 temp_r0;
    f32 temp_r3;
    s16 temp_r27;
    s16 temp_r28;
    s32 var_r29;
    s32 var_r30;

loop_1:
    fn_1_E298(h);
    fn_1_E2D4(h);
    fn_1_E714(h);
    fn_1_EA10(h);
    temp_r3 = h->x;
    temp_r0 = h->y;
    sp8 = temp_r3;
    spC = temp_r0;
    h->x = temp_r3;
    h->y = temp_r0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 0x12) {
        if ((s16) h->spr[var_r30] != -1) {
            espPosSet(h->spr[var_r30], sp8 + h->ofs[var_r30].x, spC + h->ofs[var_r30].y);
        }
        var_r30 += 1;
        goto loop_5;
    }
    var_r29 = 0;
loop_9:
    if (var_r29 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r27 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r28;
    if (temp_r28 == temp_r27) {
        var_r29 += 1;
        goto loop_9;
    }
}

void fn_1_E298(M519Hud *h) {
    espZRotSet(h->spr[1], 0.0f);
}

void fn_1_E2D4(M519Hud *h) {
    Vec sp4C;
    Vec sp58;
    f32 sp48;
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
    M519Mech *temp_r24;
    M519Mech *temp_r25;
    M519Mech *temp_r26;
    M519Mech *temp_r27;
    M519Vec2 *temp_r4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f29;
    f32 temp_f30;
    f32 var_f27;
    f64 temp_f31;
    f64 temp_f31_2;
    f64 temp_f31_3;
    s16 temp_r29;
    s32 temp_r28;
    s32 var_r22;
    s32 var_r30;

    sp58.x = 0.0f;
    sp58.y = 0.0f;
    sp58.z = 30.0f;
    temp_r27 = lbl_1_bss_F8[h->mech];
    sp28 = temp_r27->pos.x;
    sp2C = temp_r27->pos.y;
    sp30 = temp_r27->pos.z;
    temp_r26 = lbl_1_bss_F8[h->mech];
    sp40 = temp_r26->rot.x;
    sp44 = temp_r26->rot.y;
    sp48 = temp_r26->rot.z;
    var_r30 = 0;
loop_13:
    if (var_r30 < 4) {
        if (var_r30 != (s16) h->mech) {
            temp_r25 = lbl_1_bss_F8[var_r30];
            sp1C = temp_r25->pos.x;
            sp20 = temp_r25->pos.y;
            sp24 = temp_r25->pos.z;
            temp_r24 = lbl_1_bss_F8[var_r30];
            sp34 = temp_r24->rot.x;
            sp38 = temp_r24->rot.y;
            sp3C = temp_r24->rot.z;
            temp_f0 = sp1C - sp28;
            spC = temp_f0;
            temp_f0_2 = sp24 - sp30;
            sp10 = temp_f0_2;
            temp_f29 = (f32) (180.0 + (180.0 * (atan2((f64) spC, (f64) sp10) / 3.141592653589793)));
            temp_f30 = (spC * temp_f0) + (sp10 * temp_f0_2);
            var_f27 = sqrtf(temp_f30);
            temp_f0_3 = (f32) ((f64) (0.015f * var_f27) * sin((3.141592653589793 * (f64) (temp_f29 - sp44)) / 180.0));
            sp14 = temp_f0_3;
            temp_f0_4 = (f32) ((f64) (0.015f * var_f27) * cos((3.141592653589793 * (f64) (temp_f29 - sp44)) / 180.0));
            sp18 = temp_f0_4;
            sp4C.x = temp_f0_3;
            sp4C.y = -temp_f0_4;
            sp4C.z = 4.0f;
            sp14 -= 84.0f;
            sp18 -= 16.0f;
            temp_r28 = var_r30 + 3;
            temp_r4 = &h->ofs[temp_r28];
            temp_r4->x = sp14;
            temp_r4->y = sp18;
            temp_r29 = h->spr[temp_r28];
            if ((s16) lbl_1_bss_F8[var_r30]->hp == 0) {
                var_r22 = 1;
            } else {
                var_r22 = 0;
            }
            if ((var_r22 == 0) && (fn_1_F860(&sp58, &sp4C, 0) != 0)) {
                espZRotSet(temp_r29, sp44 - sp38);
                espDispOn(temp_r29);
            } else {
                espDispOff(temp_r29);
            }
        }
        var_r30 += 1;
        goto loop_13;
    }
}

void fn_1_E714(M519Hud *h) {
    M519Mech *temp_r31;
    f32 temp_f31;
    f32 var_f29;
    f32 var_f30;
    s16 temp_r29;

    temp_r31 = lbl_1_bss_F8[h->mech];
    espScaleSet(h->spr[2], 108.0f * ((1.0f / (f32) temp_r31->hpMax) * (f32) temp_r31->hpShow), 0.8f);
    if ((s16) temp_r31->hpShow > (s16) temp_r31->hp) {
        temp_r31->hpShow -= 1;
    } else if ((s16) temp_r31->hpShow < (s16) temp_r31->hp) {
        temp_r31->hpShow += 1;
    }
    if (temp_r31->speedScale < 0.0f) {
        var_f30 = -temp_r31->speedScale;
    } else {
        var_f30 = temp_r31->speedScale;
    }
    temp_f31 = 56.0f * var_f30;
    espTPLvlSet(h->spr[0xE], (1.0f / temp_f31) * temp_r31->speed);
    espTPLvlSet(h->spr[0xF], (1.0f / temp_f31) * temp_r31->speed);
    espTPLvlSet(h->spr[8], 0.125f * (f32) temp_r31->shootWait);
    espTPLvlSet(h->spr[9], 0.125f * (f32) temp_r31->shootWait);
    if (temp_r31->push > 10.0f) {
        var_f29 = 10.0f;
    } else {
        var_f29 = temp_r31->push;
    }
    temp_r29 = (s16) var_f29;
    espTPLvlSet(h->spr[0xB], 0.1f * (f32) temp_r29);
    espTPLvlSet(h->spr[0xC], 0.1f * (f32) temp_r29);
}

void fn_1_EA10(M519Hud *h) {
    M519Mech *temp_r31;
    s16 temp_r3_2;
    s16 temp_r3_5;
    s16 var_r28;
    s16 var_r29;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    u32 temp_r3;
    u32 temp_r3_3;
    u32 temp_r3_4;
    u32 temp_r3_6;

    temp_r31 = lbl_1_bss_F8[h->mech];
    espDispOff(h->spr[0x10]);
    espDispOff(h->spr[0x11]);
    if ((s16) temp_r31->chargeB > 0) {
        if ((s16) temp_r31->chargeB > 0) {
            if ((s16) temp_r31->chargeB >= 0x5A) {
                var_r29 = 2;
            } else if ((s16) temp_r31->chargeB > 0x28) {
                var_r29 = 1;
            } else {
                goto block_11;
            }
        } else if ((s16) temp_r31->chargeA > 0) {
            if ((s16) temp_r31->chargeA >= 0x5A) {
                var_r29 = 2;
            } else if ((s16) temp_r31->chargeA > 0x28) {
                var_r29 = 1;
            } else {
                goto block_11;
            }
        } else {
block_11:
            var_r29 = 0;
        }
        switch (var_r29) {                          /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            espDispOn(h->spr[0x11]);
            espTPLvlSet(h->spr[0x11], 0.2f + (0.008888889f * (f32) temp_r31->chargeB));
            return;
        case 1:                                     /* switch 1 */
            temp_r0 = (s16) temp_r31->chargeB / 4;
            temp_r3 = (u32) temp_r0 >> 0x1FU;
            if ((s32) (((temp_r0 & 1) ^ temp_r3) - temp_r3) == 0) {
                espDispOn(h->spr[0x11]);
                espTPLvlSet(h->spr[0x11], 1.0f);
                return;
            }
            break;
        case 2:                                     /* switch 1 */
            temp_r3_2 = temp_r31->chargeB;
            temp_r0_2 = (s32) (((u32) temp_r3_2 >> 0x1FU) + temp_r3_2) >> 1;
            temp_r3_3 = (u32) temp_r0_2 >> 0x1FU;
            if ((s32) (((temp_r0_2 & 1) ^ temp_r3_3) - temp_r3_3) == 0) {
                espDispOn(h->spr[0x11]);
                espTPLvlSet(h->spr[0x11], 1.0f);
                return;
            }
            break;
        }
    } else {
        if ((s16) temp_r31->chargeB > 0) {
            if ((s16) temp_r31->chargeB >= 0x5A) {
                var_r28 = 2;
            } else if ((s16) temp_r31->chargeB > 0x28) {
                var_r28 = 1;
            } else {
                goto block_33;
            }
        } else if ((s16) temp_r31->chargeA > 0) {
            if ((s16) temp_r31->chargeA >= 0x5A) {
                var_r28 = 2;
            } else if ((s16) temp_r31->chargeA > 0x28) {
                var_r28 = 1;
            } else {
                goto block_33;
            }
        } else {
block_33:
            var_r28 = 0;
        }
        switch (var_r28) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            espDispOn(h->spr[0x10]);
            espTPLvlSet(h->spr[0x10], 0.2f + (0.008888889f * (f32) temp_r31->chargeA));
            return;
        case 1:                                     /* switch 2 */
            temp_r0_3 = (s16) temp_r31->chargeA / 4;
            temp_r3_4 = (u32) temp_r0_3 >> 0x1FU;
            if ((s32) (((temp_r0_3 & 1) ^ temp_r3_4) - temp_r3_4) == 0) {
                espDispOn(h->spr[0x10]);
                espTPLvlSet(h->spr[0x10], 1.0f);
                return;
            }
            return;
        case 2:                                     /* switch 2 */
            temp_r3_5 = temp_r31->chargeA;
            temp_r0_4 = (s32) (((u32) temp_r3_5 >> 0x1FU) + temp_r3_5) >> 1;
            temp_r3_6 = (u32) temp_r0_4 >> 0x1FU;
            if ((s32) (((temp_r0_4 & 1) ^ temp_r3_6) - temp_r3_6) == 0) {
                espDispOn(h->spr[0x10]);
                espTPLvlSet(h->spr[0x10], 1.0f);
            }
            break;
        }
    }
}

void fn_1_ED78(M519Hud *h) {
    f32 spC;
    f32 sp8;
    f32 temp_r0;
    f32 temp_r3;
    s16 temp_r27;
    s16 temp_r28;
    s32 var_r29;
    s32 var_r30;

loop_1:
    fn_1_EE8C(h);
    fn_1_F104(h);
    temp_r3 = h->x;
    temp_r0 = h->y;
    sp8 = temp_r3;
    spC = temp_r0;
    h->x = temp_r3;
    h->y = temp_r0;
    var_r30 = 0;
loop_5:
    if (var_r30 < 0x12) {
        if ((s16) h->spr[var_r30] != -1) {
            espPosSet(h->spr[var_r30], sp8 + h->ofs[var_r30].x, spC + h->ofs[var_r30].y);
        }
        var_r30 += 1;
        goto loop_5;
    }
    var_r29 = 0;
loop_9:
    if (var_r29 >= 1) {
        goto loop_1;
    }
    HuPrcVSleep();
    temp_r28 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
    temp_r27 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
    ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r28;
    if (temp_r28 == temp_r27) {
        var_r29 += 1;
        goto loop_9;
    }
}

void fn_1_EE8C(M519Hud *h) {
    M519Mech *temp_r31;
    f32 var_f31;
    s16 temp_r29;

    temp_r31 = lbl_1_bss_F8[h->mech];
    espZRotSet(h->spr[2], -90.0f);
    espScaleSet(h->spr[2], 72.0f * ((1.0f / (f32) temp_r31->hpMax) * (f32) temp_r31->hpShow), 0.8f);
    if ((s16) temp_r31->hpShow > (s16) temp_r31->hp) {
        temp_r31->hpShow -= 1;
    } else if ((s16) temp_r31->hpShow < (s16) temp_r31->hp) {
        temp_r31->hpShow += 1;
    }
    espTPLvlSet(h->spr[8], 0.125f * (f32) temp_r31->shootWait);
    espTPLvlSet(h->spr[9], 0.125f * (f32) temp_r31->shootWait);
    if (temp_r31->push > 10.0f) {
        var_f31 = 10.0f;
    } else {
        var_f31 = temp_r31->push;
    }
    temp_r29 = (s16) var_f31;
    espTPLvlSet(h->spr[0xB], 0.1f * (f32) temp_r29);
    espTPLvlSet(h->spr[0xC], 0.1f * (f32) temp_r29);
}

void fn_1_F104(M519Hud *h) {
    M519Mech *temp_r31;
    s16 temp_r3_2;
    s16 var_r29;
    s32 temp_r0;
    s32 temp_r0_2;
    u32 temp_r3;
    u32 temp_r3_3;

    temp_r31 = lbl_1_bss_F8[h->mech];
    espDispOff(h->spr[0x10]);
    espDispOff(h->spr[0x11]);
    if ((s16) temp_r31->chargeB > 0) {
        if ((s16) temp_r31->chargeB >= 0x5A) {
            var_r29 = 2;
        } else if ((s16) temp_r31->chargeB > 0x28) {
            var_r29 = 1;
        } else {
            goto block_10;
        }
    } else if ((s16) temp_r31->chargeA > 0) {
        if ((s16) temp_r31->chargeA >= 0x5A) {
            var_r29 = 2;
        } else if ((s16) temp_r31->chargeA > 0x28) {
            var_r29 = 1;
        } else {
            goto block_10;
        }
    } else {
block_10:
        var_r29 = 0;
    }
    switch (var_r29) {                              /* irregular */
    case 0:
        espDispOn(h->spr[0x10]);
        espTPLvlSet(h->spr[0x10], 0.2f + (0.008888889f * (f32) temp_r31->chargeB));
        return;
    case 1:
        temp_r0 = (s16) temp_r31->chargeB / 4;
        temp_r3 = (u32) temp_r0 >> 0x1FU;
        if ((s32) (((temp_r0 & 1) ^ temp_r3) - temp_r3) == 0) {
            espDispOn(h->spr[0x10]);
            espTPLvlSet(h->spr[0x10], 1.0f);
            return;
        }
        return;
    case 2:
        temp_r3_2 = temp_r31->chargeB;
        temp_r0_2 = (s32) (((u32) temp_r3_2 >> 0x1FU) + temp_r3_2) >> 1;
        temp_r3_3 = (u32) temp_r0_2 >> 0x1FU;
        if ((s32) (((temp_r0_2 & 1) ^ temp_r3_3) - temp_r3_3) == 0) {
            espDispOn(h->spr[0x11]);
            espTPLvlSet(h->spr[0x11], 1.0f);
        }
        break;
    }
}

void fn_1_F2DC(M519Hud *h) {
    h->state = 3;
}

void fn_1_F2E8(M519Hud *h) {
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    M519Mech *sp8;
    s16 temp_r25;
    s16 temp_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    sp8 = lbl_1_bss_F8[h->mech];
    sp24 = h->x;
    sp28 = h->y;
    var_r28 = 1;
loop_11:
    if (var_r28 > 0x78) {
        sp28 += 104.0f;
        spC = sp24;
        sp10 = sp28;
        h->x = sp24;
        h->y = sp28;
        var_r29 = 0;
loop_16:
        if (var_r29 < 0x12) {
            if ((s16) h->spr[var_r29] != -1) {
                espPosSet(h->spr[var_r29], spC + h->ofs[var_r29].x, sp10 + h->ofs[var_r29].y);
            }
            var_r29 += 1;
            goto loop_16;
        }
        h->state = 0;
    } else {
        sp1C = sp24;
        sp20 = (f32) ((f64) sp28 + (100.0 * sin((3.141592653589793 * (f64) (90.0f * (0.008333334f * (f32) var_r28))) / 180.0)));
        sp14 = sp1C;
        sp18 = sp20;
        h->x = sp1C;
        h->y = sp20;
        var_r30 = 0;
loop_5:
        if (var_r30 < 0x12) {
            if ((s16) h->spr[var_r30] != -1) {
                espPosSet(h->spr[var_r30], sp14 + h->ofs[var_r30].x, sp18 + h->ofs[var_r30].y);
            }
            var_r30 += 1;
            goto loop_5;
        }
        var_r27 = 0;
loop_9:
        if (var_r27 >= 1) {
            var_r28 += 1;
            goto loop_11;
        }
        HuPrcVSleep();
        temp_r26 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r26;
        if (temp_r26 == temp_r25) {
            var_r27 += 1;
            goto loop_9;
        }
    }
}

void fn_1_F568(M519Hud *h) {
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 spC;
    M519Mech *sp8;
    s16 temp_r25;
    s16 temp_r26;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;
    s32 var_r30;

    sp8 = lbl_1_bss_F8[h->mech];
    sp24 = h->x;
    sp28 = h->y;
    espDispOn(h->spr[0]);
    var_r28 = 1;
loop_11:
    if (var_r28 > 0x78) {
        sp24 += 96.0f;
        spC = sp24;
        sp10 = sp28;
        h->x = sp24;
        h->y = sp28;
        var_r29 = 0;
loop_16:
        if (var_r29 < 0x12) {
            if ((s16) h->spr[var_r29] != -1) {
                espPosSet(h->spr[var_r29], spC + h->ofs[var_r29].x, sp10 + h->ofs[var_r29].y);
            }
            var_r29 += 1;
            goto loop_16;
        }
        h->state = 0;
    } else {
        sp1C = (f32) ((f64) sp24 + (96.0 * sin((3.141592653589793 * (f64) (90.0f * (0.008333334f * (f32) var_r28))) / 180.0)));
        sp20 = sp28;
        sp14 = sp1C;
        sp18 = sp20;
        h->x = sp1C;
        h->y = sp20;
        var_r30 = 0;
loop_5:
        if (var_r30 < 0x12) {
            if ((s16) h->spr[var_r30] != -1) {
                espPosSet(h->spr[var_r30], sp14 + h->ofs[var_r30].x, sp18 + h->ofs[var_r30].y);
            }
            var_r30 += 1;
            goto loop_5;
        }
        var_r27 = 0;
loop_9:
        if (var_r27 >= 1) {
            var_r28 += 1;
            goto loop_11;
        }
        HuPrcVSleep();
        temp_r26 = ((M519Hdr *) HuPrcCurrentGet()->property)->state;
        temp_r25 = ((M519Hdr *) HuPrcCurrentGet()->property)->prevState;
        ((M519Hdr *) HuPrcCurrentGet()->property)->prevState = temp_r26;
        if (temp_r26 == temp_r25) {
            var_r27 += 1;
            goto loop_9;
        }
    }
}

void fn_1_F7F0(M519Hud *h) {
    s32 var_r31;

    var_r31 = 0;
loop_4:
    if (var_r31 < 0x12) {
        if ((s16) h->spr[var_r31] != -1) {
            espDispOff(h->spr[var_r31]);
        }
        var_r31 += 1;
        goto loop_4;
    }
    h->state = 0;
}

s32 fn_1_F860(Vec *a, Vec *b, s32 push) {
    f32 sp8;
    f32 temp_f27;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;

    temp_f31 = a->x - b->x;
    temp_f30 = a->y - b->y;
    temp_f27 = a->z + b->z;
    var_f26 = sqrtf(((temp_f31 * temp_f31) + (temp_f30 * temp_f30)));
    if (var_f26 < temp_f27) {
        if (var_f26 == 0.0f) {
            var_f31 = 0.0f;
            var_f30 = -1.0f;
        } else {
            var_f31 = temp_f31 / var_f26;
            var_f30 = temp_f30 / var_f26;
        }
        if (push != 0) {
            a->x = b->x + (var_f31 * temp_f27);
            a->y = b->y + (var_f30 * temp_f27);
        }
        return 1;
    }
    return 0;
}

s32 fn_1_FA6C(Vec *a, Vec *b, s32 push) {
    f32 sp8;
    f32 temp_f27;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_f26;
    f32 var_f30;
    f32 var_f31;
    f64 temp_f29;
    f64 temp_f29_2;
    f64 temp_f29_3;

    temp_f31 = a->x - b->x;
    temp_f30 = a->y - b->y;
    temp_f27 = b->z - a->z;
    var_f26 = sqrtf(((temp_f31 * temp_f31) + (temp_f30 * temp_f30)));
    if (var_f26 > temp_f27) {
        if (var_f26 == 0.0f) {
            var_f31 = 0.0f;
            var_f30 = -1.0f;
        } else {
            var_f31 = temp_f31 / var_f26;
            var_f30 = temp_f30 / var_f26;
        }
        if (push != 0) {
            a->x = b->x + (var_f31 * temp_f27);
            a->y = b->y + (var_f30 * temp_f27);
        }
        return 1;
    }
    return 0;
}

f32 fn_1_FC78(f32 cur, f32 target, f32 rate) {
    f32 spC;
    f32 sp8;
    f32 var_f30;
    f32 var_f31;

    sp8 = target;
    spC = rate;
    var_f31 = (f32) fmod((f64) (sp8 - cur), 360.0);
    if (var_f31 < 0.0f) {
        var_f31 += 360.0f;
    }
    if (var_f31 > 180.0f) {
        var_f31 -= 360.0f;
    }
    var_f30 = (f32) fmod((f64) (cur + (var_f31 * spC)), 360.0);
    if (var_f30 < 0.0f) {
        var_f30 += 360.0f;
    }
    return var_f30;
}

void fn_1_FD7C(s16 player, s16 type, s16 time) {
    s16 sp8;

    sp8 = type;
    switch (sp8) {                                  /* irregular */
    case 0:
        omVibrate(player, time, 6, 6);
        return;
    case 1:
        omVibrate(player, time, 4, 2);
        return;
    case 2:
        omVibrate(player, time, 0xC, 0);
        return;
    }
}

s16 fn_1_FE20(u16 camBits, Vec *pos) {
    f32 spC;
    u16 sp8;
    HU3DCAMERA *temp_r31;
    f32 temp_f31;
    f32 var_f24;
    f32 var_f25;
    f32 var_f26;
    f32 var_f27;
    f32 var_f31;
    f64 temp_f28;
    f64 temp_f28_2;
    f64 temp_f28_3;
    s16 temp_r26;
    s16 var_r29;
    s32 var_r28;

    sp8 = camBits;
    var_r29 = 0;
    var_r28 = 0;
loop_24:
    if (var_r28 < 4) {
        if ((s32) (sp8 & lbl_1_rodata_10[var_r28]) != 0) {
            temp_r31 = &Hu3DCamera[var_r28];
            var_f31 = (f32) ((180.0 + (180.0 * (atan2((f64) (temp_r31->pos.x - pos->x), (f64) (temp_r31->pos.z - pos->z)) / 3.141592653589793))) - (f64) (180.0f + lbl_1_bss_108[var_r28].rot.y));
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            if (var_f31 >= 360.0f) {
                var_f31 -= 360.0f;
            }
            if (var_f31 >= 180.0f) {
                var_f31 -= 360.0f;
            }
            temp_f31 = -var_f31;
            if (temp_f31 < 0.0f) {
                var_f26 = -temp_f31;
            } else {
                var_f26 = temp_f31;
            }
            if (var_f26 < 30.0f) {
                if ((temp_r31->pos.x - pos->x) < 0.0f) {
                    var_f25 = -(temp_r31->pos.x - pos->x);
                } else {
                    var_f25 = temp_r31->pos.x - pos->x;
                }
                if ((temp_r31->pos.z - pos->z) < 0.0f) {
                    var_f24 = -(temp_r31->pos.z - pos->z);
                } else {
                    var_f24 = temp_r31->pos.z - pos->z;
                }
                var_f27 = sqrtf(((var_f25 * var_f25) + (var_f24 * var_f24)));
                temp_r26 = (s16) (127.0f - (0.016666668f * (4800.0f - var_f27)));
                if (var_r29 < temp_r26) {
                    var_r29 = temp_r26;
                }
            }
        }
        var_r28 += 1;
        goto loop_24;
    }
    if (var_r29 < 0) {
        var_r29 = 0;
    }
    if (var_r29 > 0x7F) {
        var_r29 = 0x7F;
    }
    return var_r29;
}

s16 fn_1_10244(u16 camBits, Vec *pos) {
    f32 sp10;
    f32 spC;
    u16 sp8;
    HU3DCAMERA *temp_r31;
    f32 temp_f31;
    f32 var_f29;
    f32 var_f30;
    f32 var_f31;
    s16 var_r29;
    s16 var_r29_2;
    s32 var_r24;
    s32 var_r25;
    s32 var_r27;
    s32 var_r28;

    sp8 = camBits;
    var_r29_2 = 0;
    var_r27 = 0;
    var_r28 = 0;
loop_23:
    if (var_r28 < 4) {
        if ((s32) (sp8 & lbl_1_rodata_10[var_r28]) != 0) {
            temp_r31 = &Hu3DCamera[var_r28];
            var_f31 = (f32) ((180.0 + (180.0 * (atan2((f64) (temp_r31->pos.x - pos->x), (f64) (temp_r31->pos.z - pos->z)) / 3.141592653589793))) - (f64) (180.0f + lbl_1_bss_108[var_r28].rot.y));
            if (var_f31 < 0.0f) {
                var_f31 += 360.0f;
            }
            if (var_f31 >= 360.0f) {
                var_f31 -= 360.0f;
            }
            if (var_f31 >= 180.0f) {
                var_f31 -= 360.0f;
            }
            temp_f31 = -var_f31;
            var_r25 = temp_f31 < 30.0f;
            if (var_r25 != 0) {
                if ((temp_r31->pos.x - pos->x) < 0.0f) {
                    var_f30 = -(temp_r31->pos.x - pos->x);
                } else {
                    var_f30 = temp_r31->pos.x - pos->x;
                }
                sp10 = var_f30;
                if ((temp_r31->pos.z - pos->z) < 0.0f) {
                    var_f29 = -(temp_r31->pos.z - pos->z);
                } else {
                    var_f29 = temp_r31->pos.z - pos->z;
                }
                spC = var_f29;
                if (var_r28 == 0) {
                    var_r29_2 = (s16) ((f32) var_r29_2 + (32.0f + (0.53333336f * (30.0f + temp_f31))));
                } else {
                    var_r29_2 = (s16) ((f32) var_r29_2 + (96.0f - (0.53333336f * (30.0f + temp_f31))));
                }
                var_r27 += 1;
            }
        }
        var_r28 += 1;
        goto loop_23;
    }
    if (var_r27 > 0) {
        var_r24 = var_r29_2 / var_r27;
    } else {
        var_r24 = 0x40;
    }
    var_r29 = (s16) var_r24;
    if (var_r29 < 0x20) {
        var_r29 = 0x20;
    }
    if (var_r29 > 0x60) {
        var_r29 = 0x60;
    }
    return var_r29;
}
