// m2c context for m574Dll (tools/mp5/decomp.py m574Dll --types tools/mp5/types/m574Dll.h)
// Written from the draft: Panic Pinball (2 vs 2; one pinball table, each team has two flippers (a player each)
// and shoots balls at the targets, bumpers and slot machines). Runs on MP5's MgSeq sequencer.
// Source files in MP5: m574.c (sequence), player.c (lbl_1_bss_38), stage.c (lbl_1_bss_48), ball.c (lbl_1_bss_50),
// score.c (lbl_1_bss_58), collide.c (lbl_1_bss_60: the collision registry + mesh colliders).
// objdata: M574Stage
// objdata fn_1_1068 fn_1_1264 fn_1_1588 fn_1_17A0 fn_1_1830 fn_1_1938 fn_1_19AC fn_1_1D54 fn_1_1E4C fn_1_1F28 fn_1_1F9C: M574Player
// objdata fn_1_7238 fn_1_7328 fn_1_7468 fn_1_75EC fn_1_71BC fn_1_7200: M574Score
// objdata fn_1_6758 fn_1_686C: M574Balls
// objdata fn_1_7AE4: M574Reg
// objexpr lbl_1_bss_48: M574Stage
// objexpr lbl_1_bss_50: M574Balls
// objexpr lbl_1_bss_58: M574Score
// objexpr lbl_1_bss_60: M574Reg
// objexpr lbl_1_bss_38: M574Player

// var fn_1_6758 temp_r30: M574Ball
// var fn_1_686C temp_r31: M574Ball
// var fn_1_6C2C temp_r31: M574Ball
// var fn_1_6CC8 temp_r31: M574Ball
// var fn_1_6D7C temp_r31: M574Ball
// var fn_1_70B0 temp_r31: M574Ball
// var fn_1_7AE4 temp_r26_2: M574Hit
// var fn_1_7238 temp_r29: M574Side
// var fn_1_7328 temp_r31: M574Side
// var fn_1_7874 temp_r30: M574Side
// var fn_1_26F4 temp_r29: M574Prop
// var fn_1_3240 temp_r27: M574Prop
// var fn_1_34B0 var_r30: M574Hit
// var fn_1_4660 temp_r31: M574Prop
// var fn_1_47DC temp_r27: M574Kicker
// var fn_1_5680 temp_r31: M574Prop
// var fn_1_5750 temp_r31: M574Prop
// var fn_1_5934 temp_r26: M574Prop
// var fn_1_6478 temp_r31: M574Flipper
// var fn_1_6568 temp_r31: M574Flipper

typedef struct M574Pair {
    f32 unk0;
    f32 unk4;
} M574Pair;

typedef struct M574Hit { // a ball's collision shape (kind 0), 0x30
    s32 unk0; // 1 active, 2 held by a kicker
    s32 unk4;
    s32 unk8; // index
    s32 unkC; // kind: 0 ball
    void *unk10; // owner (M574Ball)
    void *unk14; // update callback (void (*)(owner))
    Vec *unk18; // pos
    Vec *unk1C; // vel
    f32 unk20; // previous pos
    f32 unk24;
    f32 unk28;
    f32 unk2C; // radius
} M574Hit;

typedef struct M574Circle { // a round obstacle (kind 0 of the second collision table), 0x24
    s32 unk0; // 1 active
    s32 unk4; // type
    s32 unk8; // index
    s32 unkC; // kind: 0 circle
    void *unk10; // owner
    void *unk14;
    void *unk18; // on-hit callback: s32 (*)(M574Circle *, M574Hit *)
    Vec *unk1C; // center
    f32 unk20; // radius
} M574Circle;

typedef struct M574Line { // collision line (current frame / previous frame), 0x28
    f32 unk0; // from
    f32 unk4;
    f32 unk8;
    f32 unkC; // to
    f32 unk10;
    f32 unk14;
    f32 unk18; // normal
    f32 unk1C;
    f32 unk20;
    f32 unk24; // plane offset
} M574Line;

typedef struct M574Seg { // a collision line of the model (local), 0x1C
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void *unk18; // matrix of its object
} M574Seg;

typedef struct M574Mesh { // collision lines taken from a model (kind 1), 0x3C
    s32 unk0; // 1 active
    s32 unk4; // type
    s32 unk8; // index
    s32 unkC; // kind: 1 mesh
    void *unk10; // owner
    void *unk14;
    void *unk18; // on-hit callback: s32 (*)(M574Mesh *, M574Hit *)
    s32 unk1C; // line count
    M574Line *unk20; // lines (current)
    M574Line *unk24; // lines (previous)
    M574Seg *unk28; // lines (local)
    s32 unk2C; // object count
    HSFTRANSFORM **unk30; // object transforms
    void *unk34; // their matrices
    M574Line *unk38; // line hit last
} M574Mesh;

typedef struct M574Reg { // lbl_1_bss_60 data, 0x198
    M574Hit *unk0[0x52]; // balls
    M574Circle *unk148[0x14]; // obstacles (circles and meshes)
} M574Reg;

typedef struct M574Ball { // 0x6C
    s32 unk0; // state
    s32 unk4;
    s32 unk8;
    s32 unkC; // 1: beyond the plunger line
    s32 unk10; // in the goal zone
    s16 unk14; // model
    char pad16[2];
    Vec unk18; // pos
    Vec unk24; // vel
    char pad30[0xC];
    M574Hit unk3C;
} M574Ball;

typedef struct M574Balls { // lbl_1_bss_50 data, 0x21C0
    M574Ball unk0[0x50];
} M574Balls;

typedef struct M574Player { // OMOBJ::data of lbl_1_bss_38[4], 0x78
    s32 unk0; // player
    s32 unk4; // team
    s32 unk8; // slot in the team (the flipper)
    s32 unkC; // character
    s32 unk10; // motion
    s32 unk14; // buttons pressed
    s32 unk18; // buttons held
    f32 unk1C;
    f32 unk20; // flipper power
    s32 unk24; // com
    s32 unk28; // com level
    s32 unk2C; // com state
    s32 unk30; // com timer
    s32 unk34; // com: fast ball
    s32 unk38; // mode step
    s32 unk3C;
    s32 unk40; // frame counter
    s32 unk44;
    Vec unk48; // pos
    Vec unk54; // vel
    char pad60[0xC];
    f32 unk6C; // rot y
    s32 unk70;
    s32 unk74;
} M574Player;

typedef struct M574Side { // score of a team, 0x1C
    s32 unk0; // score
    s32 unk4; // shown
    s32 unk8; // blink timer
    s32 unkC; // last added
    s16 unk10[5]; // digit anims
    char pad1A[2];
} M574Side;

typedef struct M574Score { // lbl_1_bss_58 data, 0x4C
    M574Side unk0[2];
    s32 unk38; // step
    s32 unk3C;
    s32 unk40; // record
    s16 unk44; // score window
    s16 unk46; // sprite group
    MGSCORE *unk48;
} M574Score;

typedef struct M574Prop { // targets, bumpers, the centre bumper, the enemies: 0x88
    s32 unk0; // state
    s32 unk4; // timer
    s32 unk8;
    s32 unkC; // side
    Vec unk10; // pos
    Vec unk1C; // offset / velocity
    Vec unk28; // rot
    f32 unk34;
    s32 unk38; // hit flag
    Vec unk3C; // scale / offsets
    HSFOBJECT *unk48; // object of the model
    M574Circle unk4C;
    char pad70[0x18];
} M574Prop;

typedef struct M574Flipper { // 0x50
    f32 unk0; // power
    f32 unk4; // shown
    f32 unk8; // angle
    f32 unkC; // target angle
    s32 unk10; // 1: layers changed
    M574Mesh unk14;
} M574Flipper;

typedef struct M574Slot { // slot machine, 0x5C
    s32 unk0; // state
    s32 unk4; // timer
    s32 unk8; // timer 2
    s32 unkC; // sound
    s32 unk10; // spinning
    s32 unk14[3]; // reel stopped
    s32 unk20[3]; // symbol
    f32 unk2C[3]; // angle
    f32 unk38[3]; // target angle
    f32 unk44[3]; // speed
    HSFOBJECT *unk50[3];
} M574Slot;

typedef struct M574Kicker { // 0x88
    s32 unk0; // state
    char pad4[0xC];
    f32 unk10; // pos
    f32 unk14;
    char pad18[0x1C];
    f32 unk34; // offset
    char pad38[0x10];
    M574Hit *unk48; // ball held
    char pad4C[0x3C];
} M574Kicker;

typedef struct M574Stage { // lbl_1_bss_48 data, 0x108C
    s32 unk0[2]; // ball spawn timers
    s32 unk8;
    s32 unkC; // balls left
    char pad10[4];
    M574Prop unk14; // centre bumper
    s16 unk9C[5]; // particles
    char padA6[2];
    M574Flipper unkA8[4];
    M574Slot unk1E8[2];
    M574Kicker unk2A0[2];
    M574Prop unk3B0[14];
    M574Prop unkB20[6];
    M574Prop unkE50[2];
    M574Mesh unkF60; // cage
    M574Mesh unkF9C[4];
} M574Stage;

extern OMOBJ *lbl_1_bss_30;
extern HUPROCESS *lbl_1_bss_34;
extern OMOBJ *lbl_1_bss_38[4];
extern OMOBJ *lbl_1_bss_48;
extern OMOBJ *lbl_1_bss_50;
extern OMOBJ *lbl_1_bss_58;
extern OMOBJ *lbl_1_bss_60;
extern s16 lbl_1_bss_0[4];
extern s16 lbl_1_bss_8[4];
extern s16 lbl_1_bss_10[4];
extern s32 lbl_1_bss_18;
extern s16 lbl_1_bss_1C;
extern s16 lbl_1_bss_1E;
extern s32 lbl_1_bss_20;
extern s32 lbl_1_bss_24;
extern s32 lbl_1_bss_28;
extern s32 lbl_1_bss_2C;
extern OMCAMERAVIEW lbl_1_data_0[2];
extern Point3d lbl_1_data_38;
extern Point3d lbl_1_data_44;
extern Vec lbl_1_data_50;
extern Vec lbl_1_data_100[4];
extern Vec lbl_1_data_130[4];
extern Vec lbl_1_data_250[4];
extern Vec lbl_1_data_48C[2];
extern M574Pair lbl_1_data_570;
extern M574Pair lbl_1_data_510[10];
extern char lbl_1_data_5AC[2][5][4];
extern char lbl_1_data_290[4][10];
extern u8 lbl_1_data_2C4[0x14];
extern char lbl_1_data_2D8[6][10];
extern char lbl_1_data_31C[14][10];
extern char lbl_1_data_3A8[4][10];
extern char lbl_1_data_3D0[9][10];
extern char lbl_1_data_4A4[12];
extern char lbl_1_data_504[12];
extern s32 lbl_1_rodata_10[3];
extern s32 lbl_1_rodata_1C[3];
extern s32 lbl_1_rodata_60[2];
extern s32 lbl_1_rodata_68[2];

void fn_1_6C2C(Vec *pos, Vec *vel);
s32 fn_1_6CC8(s32 side);
s32 fn_1_6D7C(s32 side, Vec *pos, f32 farg0, f32 farg1, f32 farg2);
M574Hit *fn_1_70B0(s32 idx, Vec *pos, Vec *vel);
s32 fn_1_7C88(M574Hit *a, M574Hit *b);
s32 fn_1_7FD8(M574Hit *a, M574Circle *b);
s32 fn_1_82AC(M574Hit *ball, M574Mesh *mesh, M574Line *lines, f32 *prev);
s32 fn_1_87B8(M574Hit *ball, M574Mesh *mesh);
s32 fn_1_8AD0(M574Hit *hit);
s32 fn_1_8B48(M574Circle *hit);
void fn_1_8C94(M574Mesh *mesh, HSFOBJECT *objs, s32 count);
void fn_1_8F54(M574Mesh *mesh, s16 model);
void fn_1_8FA8(M574Mesh *mesh, HSFOBJECT *obj);
void fn_1_8FDC(M574Mesh *mesh);
s32 fn_1_2D88(M574Mesh *mesh, M574Hit *ball);
s32 fn_1_3240(M574Circle *self, M574Hit *ball);
s32 fn_1_47DC(M574Mesh *mesh, M574Hit *ball);
s32 fn_1_5628(M574Circle *self, M574Hit *ball);
s32 fn_1_5D64(M574Circle *self, M574Hit *ball);
void fn_1_5680(Vec *pos);
void fn_1_63B0(Vec *pos, Vec *accel, s32 count);
void fn_1_6478(s32 flipper, f32 power);
f64 fn_1_6568(s32 flipper);
s32 fn_1_4330(f32 angle);
f32 fn_1_CC8(f32 cur, f32 target, f32 rate);
void fn_1_C10(s32 sound, Vec *pos);
void fn_1_77D4(s32 team, s32 prize);
void fn_1_7874(s32 team, s32 prize);
