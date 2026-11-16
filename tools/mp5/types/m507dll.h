// m2c context for m507dll (tools/mp5/decomp.py m507dll --types tools/mp5/types/m507dll.h)
// Inferred from the draft only: layouts, globals and prototypes, so m2c indexes arrays and passes
// float args correctly. Offsets are the GameCube ones.
// objdata: M507Player
// particlework: M507EffParam

typedef struct M507Player { // OMOBJ::data, 0xCC
    s32 unk0; // current motion slot
    s32 unk4; // last voice sfx
    s32 unk8; // mode 2000..2009
    s32 unkC; // player no
    s32 unk10;
    s32 unk14; // character
    s32 unk18; // pad no
    s32 unk1C;
    f32 unk20, unk24, unk28; // pos
    s32 unk2C; // camera no
    f32 unk30, unk34, unk38; // rot
    f32 unk3C, unk40, unk44;
    f32 unk48, unk4C, unk50; // vel
    f32 unk54, unk58, unk5C; // rot vel
    s32 unk60, unk64, unk68;
    f32 unk6C, unk70, unk74;
    s32 unk78, unk7C, unk80, unk84;
    u32 unk88;
    s32 unk8C;
    f32 unk90, unk94, unk98;
    s32 unk9C;
    f32 unkA0, unkA4, unkA8, unkAC, unkB0, unkB4, unkB8;
    s16 unkBC, unkBE;
    s16 unkC0[3];
    s16 unkC6, unkC8, unkCA;
} M507Player;

typedef struct M507Ghost { // lbl_1_bss_E14[4], 0x58
    s32 unk0; // motion slot
    s32 unk4;
    u32 unk8; // mode 0..7
    f32 unkC, unk10, unk14; // pos
    f32 unk18, unk1C, unk20;
    f32 unk24, unk28, unk2C; // vel
    f32 unk30;
    u32 unk34, unk38, unk3C;
    s32 unk40;
    u32 unk44;
    f32 unk48, unk4C;
    s32 unk50, unk54;
} M507Ghost;

typedef struct M507Eff { // lbl_1_bss_4[25][4], 0x24
    f32 unk0, unk4, unk8;
    f32 unkC, unk10, unk14;
    s16 unk18; // model
    s16 unk1A;
    s32 unk1C, unk20;
} M507Eff;

typedef struct M507EffParam { // particle emit params, 0x38
    u32 unk0;
    u8 unk4, unk5, unk6, unk7; // color
    u8 unk8, unk9, unkA, unkB; // color target
    f32 unkC, unk10, unk14; // vel
    f32 unk18, unk1C, unk20; // vel decay
    f32 unk24; // gravity
    f32 unk28, unk2C, unk30, unk34;
} M507EffParam;

typedef struct M507ModelCache {
    u32 unk0;
    s16 unk4;
} M507ModelCache;

extern s32 lbl_1_bss_0;
extern M507Eff lbl_1_bss_4[25][4];
extern M507Ghost lbl_1_bss_E14[4];
extern s16 lbl_1_bss_F74[8][4];
extern Vec lbl_1_bss_FB4[4];
extern Vec lbl_1_bss_FE4[4];
extern Vec lbl_1_bss_1014[4];
extern Vec lbl_1_bss_1044[4];
extern s16 lbl_1_bss_108C[8];
extern s16 lbl_1_bss_109C[4];
extern s16 lbl_1_bss_10A4[13][4];
extern M507ModelCache lbl_1_bss_1120[32];
extern Vec lbl_1_bss_1234[4];
extern Vec lbl_1_bss_1264[4];
extern Vec lbl_1_bss_1294[4];
extern Vec lbl_1_bss_12C4[4];
extern s16 lbl_1_bss_133C[16];
extern void *lbl_1_bss_1338;

extern GXColor lbl_1_data_1C;
extern Vec lbl_1_data_20;
extern s32 lbl_1_data_38[23][2];
extern s32 lbl_1_data_F0[17][2];
extern u32 lbl_1_data_1AC[13];
extern u32 lbl_1_data_1E0[8];
extern M507EffParam lbl_1_data_3E8;

void fn_1_1120(OMOBJ *obj);
u16 fn_1_1A68(OMOBJ *obj);
void fn_1_1B00(OMOBJ *obj);
void fn_1_2E1C(OMOBJ *obj);
s32 fn_1_3C2C(void);
s32 fn_1_4048(void);
void fn_1_40CC(OMOBJ *obj);
void fn_1_419C(OMOBJ *obj);
void fn_1_4268(void);
void fn_1_4BC(OMOBJ *obj);
s16 fn_1_4EE4(s32 player, s32 dataNum, u16 camBit, s32 type, f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz);
void fn_1_4F0(OMOBJ *obj);
void fn_1_527C(s16 player);
void fn_1_562C(s16 player, s32 mode);
s32 fn_1_60A0(s32 dif, s32 idx, s32 col);
void fn_1_610C(f32 w, f32 h);
u32 fn_1_6468(u32 lo, u32 hi);
void fn_1_64A4(s16 player, u16 time, f32 amp, f32 decay, f32 speed);
void fn_1_64F4(s16 player, s32 mot, u32 attr);
void fn_1_65AC(void);
s16 fn_1_668C(s16 player);
void fn_1_790(OMOBJ *obj);
void fn_1_7720(void);
void fn_1_7770(s16 camBit, Vec *pos);
s16 fn_1_7AE8(s16 camBit, M507EffParam *param, f32 x, f32 y, f32 z, f32 scale);
void fn_1_7D8C(void);
void fn_1_7FF0(void);
void fn_1_8214(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
