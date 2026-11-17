#!/bin/bash
# Regenerates src/REL/m548Dll/main.c (Head Waiter) from MP5's m548 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m548dll --types tools/mp5/types/m548dll.h | tail -2
f=build/mp5/m548dll.c
python tools/mp5/port.py $f | head -1
python - "$f" <<'PY'
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# the pad's stack slot holds a Vec after the two table entries
rep('    s32 sp8[3];\n\n    sp8[0] = lbl_1_rodata_D0[0];', '    s32 sp8[2];\n    Vec pos;\n\n    sp8[0] = lbl_1_rodata_D0[0];')
s = s.replace('&sp8[2]', '&pos').replace('sp8[2].y', 'pos.y').replace('(bitwise f32) sp8[2]', 'pos.x')
# a Vec on the stack built from a rodata Vec
rep('''            sp8 = lbl_1_rodata_118.x;
            spC = lbl_1_rodata_118.y;
            sp10 = lbl_1_rodata_118.z;
            sp8 = -120.0f + (f32) (lbl_1_bss_3D0.unk6 * 0xF0);
            sp14.x = sp8.unk0;
            sp14.y = sp8.unk4;
            sp14.z = sp8.unk8;
''', '''            sp14 = lbl_1_rodata_118;
            sp14.x = -120.0f + (f32) (lbl_1_bss_3D0.unk6 * 0xF0);
''')
rep('''    sp8 = lbl_1_rodata_1C8.x;
    spC = lbl_1_rodata_1C8.y;
    sp10 = lbl_1_rodata_1C8.z;
    lbl_1_bss_3B8.unkC.x = sp8.unk0;
    lbl_1_bss_3B8.unkC.y = sp8.unk4;
    lbl_1_bss_3B8.unkC.z = sp8.unk8;
''', '''    lbl_1_bss_3B8.unkC = lbl_1_rodata_1C8;
''')
rep('fn_1_660C(*lbl_1_bss_138, lbl_1_bss_138[0][1]);', 'fn_1_660C(lbl_1_bss_138[0], lbl_1_bss_138[1]);')
s = s.replace('*lbl_1_bss_5D2', 'lbl_1_bss_5D2[0]')
# per-character tables are in MP5 character order (DK borrows Wario's row)
rep('lbl_1_bss_3F0.unk48[temp_r31]->unk6', 'lbl_1_bss_3F0.unk48[temp_r31][3]')
s = re.sub(r'lbl_1_data_(0|184|288|424)\[((?:[^\[\]]|\[[^\[\]]*\])*\.unk2)\]', r'lbl_1_data_\1[Mp5CharNo(\2)]', s)
# the Bowser head is held at the character's hand height (Wario's row for DK); MP4's DK carries it higher
rep('''        lbl_1_bss_384[var_r31].unk14 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][5];
''', '''        lbl_1_bss_384[var_r31].unk14 = lbl_1_data_0[Mp5CharNo(lbl_1_bss_3F0.unk4[var_r31].unk2)][5];
        if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[var_r31].unk2)) {
            lbl_1_bss_384[var_r31].unk14 += 20.0f;
        }
''')
# DK's initial hold sits a little further right, and when he catches the head it is held a little higher
rep('''    lbl_1_bss_44.x = -lbl_1_bss_384->unk10;
''', '''    lbl_1_bss_44.x = -lbl_1_bss_384->unk10;
    if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[0].unk2)) {
        lbl_1_bss_44.x += 12.0f;
    }
''')
assert s.count('unkC == 49.0f') == 1
rep('        if (lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC == 49.0f) {', '''        if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[lbl_1_bss_3D0.unk6 ^ 1].unk2)) {
            lbl_1_bss_44.y += 12.0f;
        }
        if (lbl_1_bss_3F0.unk50[lbl_1_bss_3D0.unk6 ^ 1].unkC == 49.0f) {''')
# Motion time drives the game (the pass completes at time 50, the blast at 110...). DK's MP4 stand-in motions
# have other lengths than MP5's (the carrying pose is 32 frames, MP5's 119), so for DK the motion's time and
# speed are stretched to MP5's length per state (59, 119, 9; state 3 is the win, state 4 a 19-29 frame loop).
rep('void fn_1_6EA0(omObjData *obj) {', '''static const f32 sMp5MotLen[5] = { 59.0f, 119.0f, 9.0f, 0.0f, 24.0f };
static f32 sDkMotScale[2] = { 1.0f, 1.0f }; // MP4 motion length / MP5 motion length

void fn_1_6EA0(omObjData *obj) {''')
rep('''            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0);
''', '''            temp_r31->unk14 = Hu3DMotionMaxTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0);
            sDkMotScale[var_r29] = 1.0f;
            if (!Mp5CharHasMotions(lbl_1_bss_5F8->unk4[var_r29].unk2) && sMp5MotLen[temp_r31->unk0] > 0.0f) {
                sDkMotScale[var_r29] = temp_r31->unk14 / sMp5MotLen[temp_r31->unk0];
                temp_r31->unk14 = sMp5MotLen[temp_r31->unk0];
                temp_r31->unk8 = temp_r31->unk4 + 1.0f; // re-apply the (scaled) speed below
            }
''')
rep('Hu3DMotionSpeedSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unk4);',
    'Hu3DMotionSpeedSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unk4 * sDkMotScale[var_r29]);')
rep('Hu3DMotionTimeSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unkC);',
    'Hu3DMotionTimeSet(lbl_1_bss_5F8->unk3C[temp_r0].unk0, temp_r31->unkC * sDkMotScale[var_r29]);')
# the game compares the time with == (49, 110...): snap the stretched time to the integer it stands for
rep('temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0);', '''temp_r31->unkC = Hu3DMotionTimeGet(lbl_1_bss_5F8->unk3C[temp_r0].unk0) / sDkMotScale[var_r29];
        if (sDkMotScale[var_r29] != 1.0f) {
            f32 whole = (f32)(s32)(temp_r31->unkC + 0.5f);
            if (temp_r31->unkC - whole < 0.01f && whole - temp_r31->unkC < 0.01f) {
                temp_r31->unkC = whole;
            }
        }''')
# M548_TWEAK=1: a live tweak panel for DK's pose (tools/mp5/ports/m548dll_tweak_*.inc); never committed
import os
if os.environ.get('M548_TWEAK'):
    rep('lbl_1_bss_384[var_r31].unk14 += 20.0f;', 'lbl_1_bss_384[var_r31].unk14 += sDkTw[6];')
    rep('lbl_1_bss_44.x += 12.0f;', 'lbl_1_bss_44.x += sDkTw[7];')
    rep('lbl_1_bss_44.y += 12.0f;', 'lbl_1_bss_44.y += sDkTw[8];\n            lbl_1_bss_44.x += sDkTw[9];')
    rep('temp_r31->unk4 * sDkMotScale[var_r29]);', '(sDkTweak ? 0.0f : temp_r31->unk4 * sDkMotScale[var_r29]));')
    rep('    var_r29 = 0;\nloop_12:', """    {
        static int prevTweak;
        if (prevTweak != sDkTweak) {
            lbl_1_bss_5F8->unk50[0].unk8 = lbl_1_bss_5F8->unk50[0].unk4 + 1.0f;
            lbl_1_bss_5F8->unk50[1].unk8 = lbl_1_bss_5F8->unk50[1].unk4 + 1.0f;
            prevTweak = sDkTweak;
        }
    }
    var_r29 = 0;
loop_12:""")
    rep('void fn_1_9B4(s16 mode, s16 frameNo) {\n', 'void fn_1_9B4(s16 mode, s16 frameNo) {\n    if (sDkTweak && lbl_1_bss_3F0.unkA0 != 1) {\n        fn_1_202C();\n        return;\n    }\n')
    rep('    fn_1_6D4C();\n', '    fn_1_6D4C();\n    sDkMotReady = 1;\n')
    rep('    MgSeqCreate(&lbl_1_data_2F0);', '    omAddObjEx(lbl_1_bss_3F0.unk0, 0x7FDA, 0U, 0U, -1, Mp5DkTweak);\n    MgSeqCreate(&lbl_1_data_2F0);')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
PY
mkdir -p src/REL/m548Dll
{ echo '// MP5 m548 (Head Waiter), generated from its m2c draft by tools/mp5/ports/m548dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m548dll.h
  [ -n "$M548_TWEAK" ] && cat tools/mp5/ports/m548dll_tweak_head.inc
  cat $f
  [ -n "$M548_TWEAK" ] && cat tools/mp5/ports/m548dll_tweak_tail.inc; true; } > src/REL/m548Dll/main.c
