#ifndef _M507DLL_H
#define _M507DLL_H

// Night Light Fright, ported from the Mario Party 5 decompilation (mariopartyrd/marioparty5,
// src/REL/m507dll). Its models, sprites and character motions come from the user's MP5 image
// (DATADIR_MP5_*, port/mp5disc.h); everything else runs on MP4's engine.

#include "dolphin.h"
#include "game/hu3d.h"

extern Vec lbl_1_bss_12F4;
extern Vec lbl_1_bss_1300;
extern Vec lbl_1_bss_130C;
extern Vec lbl_1_bss_1318;
extern s32 lbl_1_bss_1224;
extern s32 lbl_1_bss_1228;
extern Vec lbl_1_bss_1234[4];
extern Vec lbl_1_bss_12C4[4];
extern Vec lbl_1_bss_1264[4];
extern Vec lbl_1_bss_1294[4];

void fn_1_7720(void);
void fn_1_7770(s16 arg0, HuVecF *arg1);
void fn_1_7FF0(void);

#endif
