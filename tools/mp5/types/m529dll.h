// m2c context for m529dll (tools/mp5/decomp.py m529dll --types tools/mp5/types/m529dll.h)
// Written from the draft: Handy Hoppers (2 vs 2). Four hoppers (OMOBJ::data), a controller (lbl_1_bss_118,
// its work[0] is the phase 0x3E8..0x3F2) and a score display object (lbl_1_bss_110). Offsets are GameCube's.
// objdata: M529Player
// objdata ObjectSetup fn_1_5204 fn_1_553C fn_1_5680: M529Hud
// objexpr lbl_1_bss_110: M529Hud
// objexpr lbl_1_bss_11C: M529Player

typedef struct M529Player { // OMOBJ::data of lbl_1_bss_11C[4], 0xD0
    s32 unk0; // role: 0xBB8/0xBBA jumper (button A), 0xBB9/0xBBB flapper (L/R)
    s32 unk4; // motion slot
    s32 unk8; // mode 0x7D0..0x7D7
    s32 unkC; // jumper: 0 ground 1 hit 2 recover
    s32 unk10;
    s32 unk14; // player
    s32 unk18; // position / team slot 0..3
    s32 unk1C; // partner player
    s32 unk20; // partner's slot
    s32 unk24; // slot
    s32 unk28; // character
    s32 unk2C; // pad
    s32 unk30; // buttons held
    s32 unk34; // buttons pressed
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    f32 unk68; // speed
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    Vec unk84; // position
    Vec unk90; // velocity
    f32 unk9C;
    s32 unkA0;
    f32 unkA4; // y rotation
    f32 unkA8;
    Vec unkAC;
    s32 unkB8; // com difficulty
    s32 unkBC;
    s32 unkC0;
    s32 unkC4;
    s32 unkC8;
    s32 unkCC;
} M529Player;

typedef struct M529Hud { // lbl_1_bss_110->data, 0x1C
    s32 unk0;
    MGSCORE *unk4; // record
    MGSCORE *unk8; // team 0 score
    MGSCORE *unkC; // team 1 score
    s16 unk10;
    s16 unk12; // esp sprite
    s32 unk14;
    f32 unk18; // pulse scale
} M529Hud;

typedef struct M529Col { // GXColor
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} M529Col;

typedef struct M529Cache {
    u32 unk0;
    s16 unk4;
    char pad6[2];
} M529Cache;

extern s32 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_8;
extern s32 lbl_1_bss_C;
extern s32 lbl_1_bss_10;
extern MGTIMER *lbl_1_bss_14;
extern u32 lbl_1_bss_18;
extern s32 lbl_1_bss_1C;
extern s32 lbl_1_bss_20[2];
extern s32 lbl_1_bss_28;
extern s32 lbl_1_bss_2C;
extern s16 lbl_1_bss_30;
extern s16 lbl_1_bss_32;
extern s16 lbl_1_bss_34;
extern f32 lbl_1_bss_38;
extern f32 lbl_1_bss_3C;
extern s16 lbl_1_bss_40;
extern f32 lbl_1_bss_44[4];
extern Vec lbl_1_bss_54[4];
extern s16 lbl_1_bss_84[4];
extern f32 lbl_1_bss_8C[4];
extern Vec lbl_1_bss_9C[4];
extern s16 lbl_1_bss_CC[4];
extern s32 lbl_1_bss_D4;
extern s16 lbl_1_bss_D8;
extern s32 lbl_1_bss_DC;
extern s32 lbl_1_bss_E0;
extern s32 lbl_1_bss_E4;
extern s32 lbl_1_bss_E8;
extern s16 lbl_1_bss_EC[14];
extern f32 lbl_1_bss_108;
extern OMOBJ *lbl_1_bss_10C;
extern OMOBJ *lbl_1_bss_110;
extern OMOBJ *lbl_1_bss_114;
extern OMOBJ *lbl_1_bss_118;
extern OMOBJ **lbl_1_bss_11C;
extern M529Cache lbl_1_bss_120[32];
extern f32 lbl_1_bss_220;
extern s32 lbl_1_bss_224;
extern s32 lbl_1_bss_228;
extern s16 lbl_1_bss_22C;
extern s16 lbl_1_bss_22E;
extern s32 lbl_1_bss_230;
extern Vec lbl_1_bss_234[4];
extern Vec lbl_1_bss_264[4];
extern Vec lbl_1_bss_294[4];
extern Vec lbl_1_bss_2C4[4];
extern Vec lbl_1_bss_2F4;
extern Vec lbl_1_bss_300;
extern Vec lbl_1_bss_30C;
extern Vec lbl_1_bss_318;
extern HUPROCESS *lbl_1_bss_324;
extern s32 lbl_1_data_0;
extern M529Col lbl_1_data_4;
extern u32 lbl_1_data_8[8];
extern Vec lbl_1_data_28[4];
extern Vec lbl_1_data_58[4];
extern Vec lbl_1_data_88[4];
extern Vec lbl_1_data_B8[4];
extern Vec lbl_1_data_E8[2];
extern Vec lbl_1_data_100;
extern Vec lbl_1_data_10C;
extern Vec lbl_1_data_118;
extern Vec lbl_1_data_124[4];
extern Vec lbl_1_data_154[4];
extern Vec lbl_1_data_184[4];
extern Vec lbl_1_data_1B4[4];
extern Vec lbl_1_data_1E4[4];
extern Vec lbl_1_data_214[4];
extern s32 lbl_1_data_244[14];
extern Vec lbl_1_data_27C[2];
extern Vec lbl_1_data_294;
extern Vec lbl_1_data_2A0[2];
extern Vec lbl_1_data_2B8;
extern Vec lbl_1_data_2C4[2];
extern Vec lbl_1_data_2DC;
extern Vec lbl_1_data_2E8[2];
extern Vec lbl_1_data_300;
extern OMCAMERAVIEW lbl_1_data_30C;
extern OMCAMERAVIEW lbl_1_data_328;
extern OMCAMERAVIEW lbl_1_data_344;
extern OMCAMERAVIEW lbl_1_data_360;
extern Vec lbl_1_data_37C;
extern Vec lbl_1_data_388;
extern Vec lbl_1_data_398;
extern Vec lbl_1_data_3A4;
extern Vec lbl_1_data_3B0;

void ObjectSetup(void);
void fn_1_5E0(OMOBJ *obj);
void fn_1_B98(OMOBJ *obj);
void fn_1_1780(OMOBJ *obj);
void fn_1_187C(OMOBJ *obj);
void fn_1_1C8C(OMOBJ *obj);
void fn_1_2714(OMOBJ *obj);
void fn_1_2B70(OMOBJ *obj);
void fn_1_2BEC(OMOBJ *obj);
void fn_1_4290(OMOBJ *obj);
void fn_1_4370(OMOBJ *obj);
s32 fn_1_444C(OMOBJ *obj);
s32 fn_1_4488(OMOBJ *obj);
void fn_1_44C4(OMOBJ *obj);
void fn_1_4780(OMOBJ *obj);
u16 fn_1_4F10(OMOBJ *obj);
u16 fn_1_500C(OMOBJ *obj);
u16 fn_1_5084(OMOBJ *obj);
u16 fn_1_5170(OMOBJ *obj);
s32 fn_1_51B4(s32 min, s32 max);
void fn_1_5204(OMOBJ *obj);
void fn_1_553C(OMOBJ *obj);
void fn_1_5680(s16 phase);
void fn_1_57BC(void);
s16 fn_1_5960(s16 slot);
s32 fn_1_59BC(s32 slot);
s16 fn_1_6334(s32 player);
void fn_1_63E4(void);
