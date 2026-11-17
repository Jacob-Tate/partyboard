#!/bin/bash
# Regenerates src/REL/m514Dll/main.c (Triple Jump) from MP5's m514 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m514Dll_fix.py (and the four GX hooks in
# m514Dll_effects.inc); run from the repo root.
set -e
python tools/mp5/decomp.py m514Dll --types tools/mp5/types/m514Dll.h | tail -2
f=build/mp5/m514Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m514Dll_fix.py "$f"
mkdir -p src/REL/m514Dll
{ echo '// MP5 m514 (Triple Jump), generated from its m2c draft by tools/mp5/ports/m514Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m514Dll.h; cat $f; } > src/REL/m514Dll/main.c
