#!/bin/bash
# Regenerates src/REL/m545Dll/main.c (m545, button-sequence duel) from MP5's m545 (see tools/mp5/decomp.py for
# the prerequisites). Automatic pipeline + the hand fixes in m545dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m545Dll --types tools/mp5/types/m545dll.h | tail -2
f=build/mp5/m545Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m545dll_fix.py "$f"
mkdir -p src/REL/m545Dll
{ echo '// MP5 m545 (button-sequence duel), generated from its m2c draft by tools/mp5/ports/m545dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m545dll.h; cat $f; } > src/REL/m545Dll/main.c
