#!/bin/bash
# Regenerates src/REL/m542Dll/main.c (Countdown Pound) from MP5's m542 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m542dll --types tools/mp5/types/m542dll.h | tail -2
f=build/mp5/m542dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m542dll_fix.py "$f"
mkdir -p src/REL/m542Dll
{ echo '// MP5 m542 (Countdown Pound), generated from its m2c draft by tools/mp5/ports/m542dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m542dll.h; cat $f; } > src/REL/m542Dll/main.c
