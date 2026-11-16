#!/bin/bash
# Regenerates src/REL/m570Dll/main.c (Fight Cards) from MP5's m570 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m570Dll --types tools/mp5/types/m570Dll.h | tail -2
f=build/mp5/m570Dll.c
python tools/mp5/port.py $f | head -1
python - "$f" <<'PY'
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# winners: an s16[4] of characters (m2c typed it f32 and lost two elements)
rep('''    f32 sp8[4];
    s32 var_r31;

    var_r31 = 0;
loop_5:''', '''    s16 sp8[4];
    s32 var_r31;

    var_r31 = 0;
loop_5:''')
rep('MgSeqWinnerSet(sp8[0], spA, sp8[1], spE);', 'MgSeqWinnerSet(sp8[0], sp8[1], sp8[2], sp8[3]);')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
PY
mkdir -p src/REL/m570Dll
{ echo '// MP5 m570 (Fight Cards), generated from its m2c draft by tools/mp5/ports/m570Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m570Dll.h; cat $f; } > src/REL/m570Dll/main.c
