#!/bin/bash
# Regenerates src/REL/m506Dll/main.c (Leaf Leap) from MP5's m506 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m506Dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m506Dll --types tools/mp5/types/m506Dll.h | tail -2
f=build/mp5/m506Dll.c
python tools/mp5/port.py $f | head -3
python tools/mp5/ports/m506Dll_fix.py "$f"
mkdir -p src/REL/m506Dll
{ echo '// MP5 m506 (Leaf Leap), generated from its m2c draft by tools/mp5/ports/m506Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m506Dll.h; cat $f; } > src/REL/m506Dll/main.c
