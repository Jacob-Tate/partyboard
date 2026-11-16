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
open(p, 'w', encoding='utf-8', newline='\n').write(s)
PY
mkdir -p src/REL/m548Dll
{ echo '// MP5 m548 (Head Waiter), generated from its m2c draft by tools/mp5/ports/m548dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m548dll.h; cat $f; } > src/REL/m548Dll/main.c
