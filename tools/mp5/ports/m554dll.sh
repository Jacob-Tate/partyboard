#!/bin/bash
# Regenerates src/REL/m554Dll/main.c (Wind Wavers) from MP5's m554 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m554dll --types tools/mp5/types/m554dll.h | tail -2
f=build/mp5/m554dll.c
python tools/mp5/port.py $f | head -1
python - "$f" <<'PY'
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# fan power: 6 motion speeds then a [8][6] power table by game phase, one stack copy in the original
rep('''    ? sp18[6];
    f32 sp18[7];''', '''    f32 sp18[6];''')
rep('''    memcpy((s32) &sp18[5] + 4, (s32) (lbl_1_rodata_178 - 4) + 4, 0xC0);
''', '')
rep('*(&sp18[6] + ((var_r30 * 0x18) + (lbl_1_bss_B1C.unk124[arg0].unk0 * 4)))',
    'lbl_1_rodata_178[var_r30][lbl_1_bss_B1C.unk124[arg0].unk0]')
# motion lists of the two players: lbl_1_bss_84 is s16[2][5]
rep('fn_1_6C44(*lbl_1_bss_84, lbl_1_bss_84[0][1]);', 'fn_1_6C44(lbl_1_bss_84[0], lbl_1_bss_84[1]);')
# per-character tables are in MP5 character order (DK borrows Wario's row)
s = re.sub(r'lbl_1_data_(54|1C4)\[(lbl_1_bss_B1C\.unk4\[\w+\]\.unk2)\]', r'lbl_1_data_\1[Mp5CharNo(\2)]', s)
# a float that follows the mode table in .data, never called
rep('fn_1_31C8, (void (*)())0x3F800000 }', 'fn_1_31C8, NULL }')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
PY
mkdir -p src/REL/m554Dll
{ echo '// MP5 m554 (Wind Wavers), generated from its m2c draft by tools/mp5/ports/m554dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m554dll.h; cat $f; } > src/REL/m554Dll/main.c
