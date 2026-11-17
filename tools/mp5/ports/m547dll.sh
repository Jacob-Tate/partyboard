#!/bin/bash
# Regenerates src/REL/m547Dll/main.c (MP5 m547, a 1 vs 1 button-mashing duel) from its m2c draft (see
# tools/mp5/decomp.py for the prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m547dll --types tools/mp5/types/m547dll.h | tail -2
f=build/mp5/m547dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m547dll_fix.py "$f"
mkdir -p src/REL/m547Dll
{ echo '// MP5 m547 (a 1 vs 1 button-mashing duel), generated from its m2c draft by tools/mp5/ports/m547dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m547dll.h
  cat $f
} > src/REL/m547Dll/main.c
