#!/bin/bash
# Regenerates src/REL/m544Dll/main.c (MP5 m544 Shy Guy Showdown, a 1 vs 1 card-matching duel) from MP5's m544 (see
# tools/mp5/decomp.py for the prerequisites). Automatic pipeline + the hand fixes in m544dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m544Dll --types tools/mp5/types/m544dll.h | tail -2
f=build/mp5/m544Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m544dll_fix.py "$f"
mkdir -p src/REL/m544Dll
{ echo '// MP5 m544 (Shy Guy Showdown), generated from its m2c draft by tools/mp5/ports/m544dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m544dll.h; cat $f; } > src/REL/m544Dll/main.c
