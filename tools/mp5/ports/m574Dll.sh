#!/bin/bash
# Regenerates src/REL/m574Dll/main.c (Panic Pinball) from MP5's m574 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m574Dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m574Dll --types tools/mp5/types/m574Dll.h | tail -2
f=build/mp5/m574Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m574Dll_fix.py "$f"
mkdir -p src/REL/m574Dll
{ echo '// MP5 m574 (Panic Pinball), generated from its m2c draft by tools/mp5/ports/m574Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m574Dll.h; cat $f; } > src/REL/m574Dll/main.c
