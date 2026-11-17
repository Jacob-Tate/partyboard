#!/bin/bash
# Regenerates src/REL/m533Dll/main.c (Pedal vehicle game) from MP5's m533 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m533dll --types tools/mp5/types/m533dll.h | tail -2
f=build/mp5/m533dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m533dll_fix.py "$f"
mkdir -p src/REL/m533Dll
{ echo '// MP5 m533 (Pedal vehicle game), generated from its m2c draft by tools/mp5/ports/m533dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m533dll.h; cat $f; } > src/REL/m533Dll/main.c
