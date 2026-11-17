#!/bin/bash
# Regenerates src/REL/m519Dll/main.c (Mario Mechs) from MP5's m519 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m519dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m519dll --types tools/mp5/types/m519dll.h | tail -2
f=build/mp5/m519dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m519dll_fix.py "$f"
mkdir -p src/REL/m519Dll
{ echo '// MP5 m519 (Mario Mechs), generated from its m2c draft by tools/mp5/ports/m519dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m519dll.h; cat $f; } > src/REL/m519Dll/main.c
