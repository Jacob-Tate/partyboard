#!/bin/bash
# Regenerates src/REL/m529Dll/main.c (Handy Hoppers) from MP5's m529 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m529dll --types tools/mp5/types/m529dll.h | tail -2
f=build/mp5/m529dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m529dll_fix.py "$f"
mkdir -p src/REL/m529Dll
{ echo '// MP5 m529 (Handy Hoppers), generated from its m2c draft by tools/mp5/ports/m529dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m529dll.h; cat $f; } > src/REL/m529Dll/main.c
