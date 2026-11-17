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

extern s32 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_8;
extern s16 lbl_1_bss_C;
extern s32 lbl_1_bss_10;
extern s32 lbl_1_bss_14;
extern s16 lbl_1_bss_18[4];
extern M519Hud *lbl_1_bss_20[4];
extern s16 lbl_1_bss_30;
extern s16 lbl_1_bss_32;
extern M519Bullet *lbl_1_bss_38[0x2C];
extern M519Player *lbl_1_bss_E8[4];
extern M519Mech *lbl_1_bss_F8[4];
extern OMCAMERAVIEW lbl_1_bss_108[4];
extern M519Stage *lbl_1_bss_178;
extern OMOBJ *lbl_1_bss_17C;
extern const u16 lbl_1_rodata_10[4];
extern const s16 lbl_1_rodata_18[2];
extern const s16 lbl_1_rodata_1C[2];
extern const Vec lbl_1_rodata_20[4];
extern const M519Light lbl_1_rodata_A4[3];
extern const s32 lbl_1_rodata_164[0xD];
extern const M519View lbl_1_rodata_198[4];
extern const u32 lbl_1_rodata_278[3];
extern const M519HudInit lbl_1_rodata_284[4];
extern const M519View lbl_1_rodata_2D0[8];
extern const f32 lbl_1_rodata_4B8[4];
extern const s16 lbl_1_rodata_4C8[4];
extern const M519Ints7 lbl_1_rodata_508[3];
extern const u8 lbl_1_rodata_55C[3][4];
extern const M519BldSet lbl_1_rodata_568[3];
extern const M519Ints9 lbl_1_rodata_958[2];
extern const M519Ints7 lbl_1_rodata_9A0[2];
extern const M519MechInit lbl_1_rodata_9D8[2];
extern const M519MotSet lbl_1_rodata_9F8[2];
extern const s32 lbl_1_rodata_AE0[4];
extern const f32 lbl_1_rodata_AF0[4];
extern const s16 lbl_1_rodata_B00[4];
extern const s32 lbl_1_rodata_B08[4];
extern const s32 lbl_1_rodata_B18[4];
extern const s16 lbl_1_rodata_B28[4];
extern const s32 lbl_1_rodata_B30[4];
extern const s16 lbl_1_rodata_B40[4];
extern const f32 lbl_1_rodata_B48[4];
extern const s32 lbl_1_rodata_BA0[4];
extern const s32 lbl_1_rodata_BB0[4];
extern const s32 lbl_1_rodata_BC0[4];
extern const s32 lbl_1_rodata_BD0[4];
extern const s32 lbl_1_rodata_BE0[4];
extern const s16 lbl_1_rodata_BF0[4];
extern const s32 lbl_1_rodata_C48[2];
extern const M519Ints6 lbl_1_rodata_C60[0xD];
extern const s32 lbl_1_rodata_D98[0xD];
extern const M519Ints2 lbl_1_rodata_DD4[5];
extern const M519BulletInit lbl_1_rodata_DFC[5];
extern const Vec lbl_1_rodata_E74;
extern const s32 lbl_1_rodata_E80[5];
extern const s32 lbl_1_rodata_E98[2];
extern const M519Ints2 lbl_1_rodata_EA0[5];
extern const s32 lbl_1_rodata_EC8[2];
extern const M519Ints6 lbl_1_rodata_ED0[3];
extern const s16 lbl_1_rodata_F18[2];
extern const s16 lbl_1_rodata_F1C[2];
extern const s32 lbl_1_rodata_F20[2];
extern const s32 lbl_1_rodata_F28[2];
extern const s32 lbl_1_rodata_F30[2];
extern const M519Ints18 lbl_1_rodata_F44[4];
extern const M519HudOfs lbl_1_rodata_1064[4];

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
