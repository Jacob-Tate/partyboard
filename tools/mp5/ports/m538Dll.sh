#!/bin/bash
# Regenerates src/REL/m538Dll/main.c (Twist 'n' Out) from MP5's m538 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m538Dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m538Dll --types tools/mp5/types/m538Dll.h | tail -2
f=build/mp5/m538Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m538Dll_fix.py "$f"
mkdir -p src/REL/m538Dll
{ echo "// MP5 m538 (Twist 'n' Out), generated from its m2c draft by tools/mp5/ports/m538Dll.sh (do not hand-edit lightly)."
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m538Dll.h; cat $f; } > src/REL/m538Dll/main.c
