// m2c context for m533dll (tools/mp5/decomp.py m533dll --types tools/mp5/types/m533dll.h)
// Written from the draft: a 2 vs 2 game where each team rides one vehicle (lbl_1_bss_84[team]) along a track;
// the two partners are hooked to it ("itemhook_play" / "itemhook_taiki"), the one in front (flag 1) pedals,
// the other (flag 2) rests. Offsets are GameCube's.
// objdata: M533Player
// objdata fn_1_165C fn_1_1840: M533Item
// objdata fn_1_1F98 fn_1_2724: M533Team
// objdata fn_1_4A44 fn_1_4CC8: M533Cloud
// objdata fn_1_4F84 fn_1_5154: M533Pillar
// objexpr lbl_1_bss_AC: M533Player
// objexpr lbl_1_bss_A8: M533Item
// objexpr lbl_1_bss_A4: M533Team
// objexpr lbl_1_bss_A0: M533Cloud
// objexpr lbl_1_bss_9C: M533Pillar

typedef struct M533Player { // OMOBJ::data of lbl_1_bss_AC[4], 0x9C
    s32 unk0; // flags: 1 pedalling, 2 resting, 4/8 swapping places, 0x20 done pedalling
    s32 unk4; // motion slot
    s32 unk8;
    s32 unkC; // player
    s32 unk10; // partner player
    s32 unk14; // character
    s32 unk18; // pad
    s32 unk1C; // team
    s32 unk20; // camera = team
    s32 unk24;
    s32 unk28; // frames until the pedal pose is frozen
    f32 unk2C; // offset from the vehicle
    f32 unk30;
    f32 unk34;
    f32 unk38; // rotation
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    s32 unk50; // buttons pressed
    s32 unk54;
    s32 unk58; // frame of the last pedal
    s32 unk5C;
    f32 unk60; // pedal speed
    s32 unk64; // swap timer
    s32 unk68;
    f32 unk6C;
    f32 unk70;
    s32 unk74; // pedals
    s32 unk78; // com difficulty
    s32 unk7C;
    s32 unk80; // com: frames to wait
    s32 unk84; // com: frames to wait (target)
    s32 unk88; // com: frame counter
    f32 unk8C; // stamina
    s32 unk90;
    s32 unk94;
    f32 unk98;
} M533Player;

typedef struct M533Item { // OMOBJ::data of lbl_1_bss_A8[4] (the shadows), 0x10
    s32 unk0; // player
    f32 unk4;
    f32 unk8;
    f32 unkC;
} M533Item;

typedef struct M533Team { // OMOBJ::data of lbl_1_bss_A4[2] (the vehicles), 0x48
    s32 unk0; // reached the goal
    s32 unk4;
    s32 unk8; // team
    f32 unkC; // position
    f32 unk10;
    f32 unk14;
    f32 unk18; // rotation
    f32 unk1C;
    f32 unk20;
    f32 unk24; // speed
    f32 unk28;
    f32 unk2C;
    f32 unk30; // distance travelled
    s32 unk34;
    f32 unk38; // bob phase
    s32 unk3C;
    s32 unk40;
    s32 unk44; // pedal motion held
} M533Team;

typedef struct M533Cloud { // OMOBJ::data of lbl_1_bss_A0[4], 0x18
    f32 unk0; // y
    f32 unk4; // angle
    f32 unk8; // speed
    s16 unkC;
    s16 unkE;
    s32 unk10; // moving
    s32 unk14; // index
} M533Cloud;

typedef struct M533Pillar { // OMOBJ::data of lbl_1_bss_9C[0x18], 0x14
    s32 unk0; // moving
    s32 unk4; // index
    f32 unk8; // speed
    s32 unkC;
    f32 unk10; // distance moved
} M533Pillar;

typedef struct M533Col { // GXColor
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} M533Col;

typedef struct M533Pt { // pillar / pillar respawn table entry, 0x14
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    f32 unk10;
} M533Pt;

extern s32 lbl_1_bss_0;
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_8;
extern s32 lbl_1_bss_C;
extern s16 lbl_1_bss_10[10];
extern f32 lbl_1_bss_24;
extern s32 lbl_1_bss_28;
extern u32 lbl_1_bss_2C;
extern s32 lbl_1_bss_30;
extern s16 lbl_1_bss_34[4];
extern s16 lbl_1_bss_3C;
extern s16 lbl_1_bss_3E;
extern s16 lbl_1_bss_40;
extern s16 lbl_1_bss_42;
extern f32 lbl_1_bss_44[2];
extern s16 lbl_1_bss_4C[2];
extern s16 lbl_1_bss_50[2];
extern s16 lbl_1_bss_54[0x18];
extern s16 lbl_1_bss_84[2];
extern s16 lbl_1_bss_88[4];
extern s16 lbl_1_bss_90[4];
extern OMOBJ *lbl_1_bss_98;
extern OMOBJ **lbl_1_bss_9C;
extern OMOBJ **lbl_1_bss_A0;
extern OMOBJ **lbl_1_bss_A4;
extern OMOBJ **lbl_1_bss_A8;
extern OMOBJ **lbl_1_bss_AC;
extern OMOBJ *lbl_1_bss_B0;
extern s32 lbl_1_bss_1BC;
extern HUPROCESS *lbl_1_bss_2B8;
extern ANIMDATA *lbl_1_bss_2C8;
extern void *lbl_1_bss_2CC;
extern s32 lbl_1_bss_2D4;
extern s32 lbl_1_data_1C;
extern M533Col lbl_1_data_18;
extern s32 lbl_1_data_84[9];
extern M533Pt lbl_1_data_108[0x18];
extern M533Pt lbl_1_data_2E8[0x18];
extern Vec lbl_1_data_4F0;
extern Vec lbl_1_data_4FC;

void ObjectSetup(void);
void fn_1_6A8(OMOBJ *obj);
void fn_1_A80(OMOBJ *obj);
void fn_1_165C(OMOBJ *obj);
void fn_1_1840(OMOBJ *obj);
void fn_1_1A5C(OMOBJ *obj, s32 motion);
void fn_1_1BA0(OMOBJ *obj);
s32 fn_1_1CD0(OMOBJ *obj);
void fn_1_1E3C(OMOBJ *obj);
void fn_1_1F98(OMOBJ *obj);
s16 fn_1_2698(s32 team);
void fn_1_2724(OMOBJ *obj);
void fn_1_2D4C(s16 frameNo);
void fn_1_3424(s16 mode, s16 frameNo);
void fn_1_3890(s16 mode, s16 frameNo);
void fn_1_3950(s16 frameNo);
void fn_1_3D50(s16 mode, s16 frameNo);
void fn_1_4080(s16 frameNo);
void fn_1_44D4(void);
f32 fn_1_45B8(s32 frames);
void fn_1_46A4(f32 farg0);
void fn_1_48B8(void);
void fn_1_48BC(s32 on);
void fn_1_4A44(OMOBJ *obj);
void fn_1_4CC8(OMOBJ *obj);
void fn_1_4F84(OMOBJ *obj);
void fn_1_5154(OMOBJ *obj);
void fn_1_52C4(void);
void fn_1_6528(void);
void fn_1_6590(OMOBJ *obj);
void fn_1_6770(OMOBJ *obj, u16 cameraBit);
void fn_1_6984(OMOBJ *obj, Vec *pos, s32 big, u16 cameraBit);
void fn_1_6B18(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_6F54(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
