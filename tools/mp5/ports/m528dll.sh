#!/bin/bash
# Regenerates src/REL/m528Dll/main.c (Mario Can-Can, 2 vs 2) from MP5's m528 (see tools/mp5/decomp.py for
# the prerequisites). Automatic pipeline + the hand fixes in m528dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m528Dll --types tools/mp5/types/m528Dll.h | tail -2
f=build/mp5/m528Dll.c
python tools/mp5/port.py $f | head -3
python tools/mp5/ports/m528dll_fix.py "$f"
mkdir -p src/REL/m528Dll
{ echo '// MP5 m528 (Mario Can-Can, 2 vs 2), generated from its m2c draft by tools/mp5/ports/m528dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m528Dll.h; cat $f; } > src/REL/m528Dll/main.c
