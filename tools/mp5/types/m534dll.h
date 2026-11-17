// m2c context for m534Dll (tools/mp5/decomp.py m534Dll --types tools/mp5/types/m534dll.h)
// Written from the draft: Manic Mallets (2 vs 2). Four players stand in a row, each pushing a button pair (one
// mallet); every hit pounds the stage (a see-saw like rig with a foot "l_han_foot") and scores for the team. The
// team with more hits wins. Plain omObj game (no MgSeq): lbl_1_bss_1C = game state object (M534Game), lbl_1_bss_34[4]
// = players (M534Player), lbl_1_bss_48 = stage (M534Stage), lbl_1_bss_58 = score boards (M534Score).
// objdata: M534Player
// objdata fn_1_36C fn_1_444 fn_1_518 fn_1_648 fn_1_924 fn_1_C1C fn_1_E28 fn_1_10F0 fn_1_1364 fn_1_1A74 fn_1_1DF4 fn_1_1F1C: M534Game
// objdata fn_1_33EC fn_1_3624 fn_1_3AC8 fn_1_3B1C fn_1_3E04 fn_1_3F04 fn_1_3FA0 fn_1_406C fn_1_426C fn_1_430C fn_1_4450 fn_1_4A3C fn_1_3BA8 fn_1_3C1C: M534Stage
// objdata fn_1_6C78 fn_1_6CBC fn_1_6CF4 fn_1_6DEC fn_1_6EE0 fn_1_6FE8: M534Score
// objexpr lbl_1_bss_1C: M534Game
// objexpr lbl_1_bss_48: M534Stage
// objexpr lbl_1_bss_58: M534Score

typedef struct M534Game { // lbl_1_bss_1C data, 0x60
    s32 unk0; // phase (0 intro, 1 camera, 2 start, 3 end, 4 abort, 5 done)
    s32 unk4; // frame counter
    s32 unk8; // paused
    s32 unkC; // game step (1 intro camera .. 5 go, 6 play)
    s32 unk10; // counter
    s32 unk14; // game state (2 playing, 3 finished)
    s32 unk18; // counter
    s32 unk1C; // result step
    s32 unk20; // counter
    s32 unk24[4]; // team of each player
    s32 unk34[4]; // character of each player
    s32 unk44[4]; // winners' characters (-1)
    s32 unk54; // winner: 0 draw, 1 team 0, 2 team 1
    s32 unk58; // players that started the hit (bit per player, 4 bits each)
    s32 unk5C; // players that finished the hit
} M534Game;

typedef struct M534Player { // OMOBJ::data of lbl_1_bss_34[4], 0x60
    s32 unk0; // player
    s32 unk4; // team
    s32 unk8; // slot (0..3, left to right)
    s32 unkC; // character
    s32 unk10; // motion
    s32 unk14; // buttons pressed
    s32 unk18; // buttons held
    s32 unk1C; // com
    f32 unk20; // com reaction time
    f32 unk24; // com timer
    s32 unk28; // state
    s32 unk2C; // counter
    s32 unk30; // counter
    s32 unk34; // hit done
    s32 unk38; // frames since the last hit
    f32 unk3C; // motion speed
    Vec unk40; // pos
    f32 unk4C; // rot y
    f32 unk50; // scale y
    f32 unk54; // scale xz
    s32 unk58;
    s32 unk5C;
} M534Player;

typedef struct M534Snd { // sound slot, 8 bytes
    s32 unk0; // sound
    s32 unk4; // handle (-1 free)
} M534Snd;

typedef struct M534Stage { // lbl_1_bss_48 data, 0x200
    M534Snd unk0[0x20];
    Vec unk100[5]; // clouds
    f32 unk13C[5]; // their speed
    s32 unk150[0x10]; // pound effect playing
    f32 unk190[4]; // base y of the 4 buttons
    f32 unk1A0[4]; // button push offset
    s32 unk1B0; // stage shake on
    s32 unk1B4; // step
    s32 unk1B8; // counter
    s32 unk1BC; // sound handle
    s32 unk1C0; // dust counter
    s32 unk1C4; // pound counter
    f32 unk1C8; // sway amplitude
    f32 unk1CC; // sway phase
    f32 unk1D0; // tilt amplitude
    f32 unk1D4; // tilt phase
    f32 unk1D8; // fall speed
    f32 unk1DC; // camera base y
    f32 unk1E0; // camera shake amplitude
    f32 unk1E4; // camera shake phase
    f32 unk1E8; // lerp rate
    f32 unk1EC; // target y
    f32 unk1F0; // y
    f32 unk1F4; // arm angle (team 0 wins)
    f32 unk1F8; // turn
    f32 unk1FC; // arm angle (team 1 wins)
} M534Stage;

typedef struct M534Board { // one of the two score boards, 0x40
    s32 unk0; // state
    f32 unk4; // blend
    f32 unk8; // radius
    f32 unkC; // angle
    f32 unk10; // pos x
    f32 unk14; // pos y
    f32 unk18; // pos z
    f32 unk1C; // vel x
    f32 unk20; // vel y
    f32 unk24; // vel z
    f32 unk28; // rot x
    f32 unk2C; // rot y
    f32 unk30; // rot z
    s32 unk34; // score
    s16 unk38[3]; // digit anims
    char pad3E[2];
} M534Board;

typedef struct M534Score { // lbl_1_bss_58 data, 0x80
    M534Board unk0[2];
} M534Score;

typedef struct M534Mot { // motion table entry, 0x14
    u16 unk0; // motion index
    char pad2[2];
    f32 unk4; // shift time (s)
    f32 unk8; // start time (s)
    f32 unkC; // end time (s) or -1
    u32 unk10; // attr
} M534Mot;

typedef struct M534Cam { // camera preset, 0x18
    Vec unk0; // center
    Vec unkC; // rot x, rot y, zoom
} M534Cam;

typedef struct M534Cloud { // 0x18
    u32 unk0; // model data number
    Vec unk4; // pos
    f32 unk10; // scale
    f32 unk14; // speed
} M534Cloud;

extern s32 lbl_1_bss_28;
extern s32 lbl_1_bss_2C;
extern s16 lbl_1_bss_30;
extern OMOBJ *lbl_1_bss_34[4];
extern OMOBJ *lbl_1_bss_48;
extern s16 lbl_1_bss_50;
extern s16 lbl_1_bss_52;
extern OMOBJ *lbl_1_bss_58;
extern MGTIMER *lbl_1_bss_0;
extern s16 lbl_1_bss_4;
extern s16 lbl_1_bss_6;
extern s32 lbl_1_bss_8;
extern s16 lbl_1_bss_C;
extern s32 lbl_1_bss_10;
extern s32 lbl_1_bss_14;
extern OMOBJ *lbl_1_bss_18;
extern OMOBJ *lbl_1_bss_1C;
extern HUPROCESS *lbl_1_bss_20;
extern M534Cam lbl_1_data_50[6];
extern u32 lbl_1_data_100[4];
extern M534Mot lbl_1_data_110[4];
extern Vec lbl_1_data_160[4];
extern M534Cloud lbl_1_data_190[5];
extern Vec lbl_1_data_208[0x10];
extern char lbl_1_data_2C8[4][8];
extern Vec lbl_1_data_2E8[2];
extern char lbl_1_data_300[0xB];
extern char lbl_1_data_30B[0xD];
extern u32 lbl_1_data_350[2];
extern char lbl_1_data_358[3][8];
extern Vec lbl_1_data_370[2];
extern Vec lbl_1_data_388[2];
extern Vec lbl_1_data_3A0[2];
extern char lbl_1_data_3B8[0xD];
extern f32 lbl_1_rodata_B0[4];

s16 fn_1_1840(f32 x);
s16 fn_1_189C(Vec *pos);
void fn_1_1930(s32 sfx, Vec *pos);
void (*fn_1_19E8(HUPROCESS *proc))(OMOBJ *);
void (*fn_1_1DF4(HUPROCESS *proc, OMOBJ *obj))(OMOBJ *);
u32 fn_1_1694(void);
u32 fn_1_16AC(void);
u32 fn_1_16C4(void);
u32 fn_1_16DC(void);
void fn_1_16F4(s32 winner);
s32 fn_1_170C(s32 idx);
void fn_1_173C(s32 player);
void fn_1_176C(s32 player);
s32 fn_1_179C(void);
s32 fn_1_17C8(void);
void fn_1_1800(s32 player, s32 team, s32 character);
void fn_1_2130(s32 from, s32 to, f32 t);
void fn_1_2F88(OMOBJ *obj, u32 motion);
s32 fn_1_3118(OMOBJ *obj);
s32 fn_1_318C(OMOBJ *obj, u32 motion);
void fn_1_3BA8(OMOBJ *stage, s32 sfx);
void fn_1_3C1C(OMOBJ *stage, s32 sfx, s32 frames);
void fn_1_4114(s32 slot);
void fn_1_43D4(s32 slot);
void fn_1_449C(s32 team);
s32 fn_1_4624(void);
f32 fn_1_46A8(void);
f32 fn_1_4848(void);
void fn_1_4970(void);
s32 fn_1_49BC(void);
s32 fn_1_49FC(void);
void fn_1_5B64(void);
void fn_1_5CB0(s32 count);
void fn_1_5E20(s32 count, Vec *center);
void fn_1_5F94(void);
void fn_1_6458(Vec *pos);
void fn_1_6938(Vec *pos, Vec *vel);
void fn_1_74B0(s32 team, s32 add);
s32 fn_1_74E8(s32 team);
