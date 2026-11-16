#!/bin/bash
# Regenerates src/REL/m524Dll/main.c from MP5's m524 (see tools/mp5/decomp.py for the prerequisites).
# Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m524Dll --types tools/mp5/types/m524Dll.h | tail -2
f=build/mp5/m524Dll.c
python tools/mp5/port.py $f | head -1
# the MP5 timer fields the game touches (stopF at 0x14, mode at 0x0)
sed -i -e 's/->unk10->unk14/->unk10->stopF/g' -e 's/->unk10->unk0 = /->unk10->mode = /g' $f
python - "$f" <<'PY'
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# camera shake: MP5 kept the camera pointer in work[2] (32-bit); it is always lbl_1_bss_18
rep('*temp_r27->data = *temp_r26;', '*(M524Camera *)temp_r27->data = *temp_r26;')
rep('        temp_r27->work[2] = (u32) temp_r26;\n', '')
rep('fn_1_3694((M524Camera *) arg0->work[2]);', 'fn_1_3694(lbl_1_bss_18);')
rep('arg0->work[2]->unk2C', 'lbl_1_bss_18->unk2C.x')
rep('arg0->work[2]->unk30', 'lbl_1_bss_18->unk2C.y')
# flow: call the current phase
rep('    temp_r4 = temp_r31->unk4;\n    *(temp_r4 + (temp_r31->unk0 * 4))(arg0, temp_r4);', '    temp_r31->unk4[temp_r31->unk0](arg0);')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
PY
mkdir -p src/REL/m524Dll
{ echo '// MP5 m524, generated from its m2c draft by tools/mp5/ports/m524Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m524Dll.h; cat $f; } > src/REL/m524Dll/main.c
