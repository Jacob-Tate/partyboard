#!/bin/bash
# Regenerates src/REL/m523Dll/main.c (Beam Team) from MP5's m523 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m523Dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m523Dll --types tools/mp5/types/m523Dll.h | tail -2
f=build/mp5/m523Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m523Dll_fix.py "$f"
mkdir -p src/REL/m523Dll
{ echo '// MP5 m523 (Beam Team), generated from its m2c draft by tools/mp5/ports/m523Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m523Dll.h; cat $f; } > src/REL/m523Dll/main.c
