#!/bin/bash
# Regenerates src/REL/m550Dll/main.c (MP5 m550, a 1 vs 1 button-mashing duel) from its m2c draft (see
# tools/mp5/decomp.py for the prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m550dll --types tools/mp5/types/m550dll.h | tail -2
f=build/mp5/m550dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m550dll_fix.py "$f"
mkdir -p src/REL/m550Dll
{ echo '// MP5 m550 (a 1 vs 1 button-mashing duel), generated from its m2c draft by tools/mp5/ports/m550dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m550dll.h
  cat $f
} > src/REL/m550Dll/main.c
