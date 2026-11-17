#!/bin/bash
# Regenerates src/REL/m534Dll/main.c (Manic Mallets) from MP5's m534 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m534dll_fix.py; run from the repo root.
set -e
python tools/mp5/decomp.py m534Dll --types tools/mp5/types/m534dll.h | tail -2
f=build/mp5/m534Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m534dll_fix.py "$f"
mkdir -p src/REL/m534Dll
{ echo '// MP5 m534 (Manic Mallets), generated from its m2c draft by tools/mp5/ports/m534Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m534dll.h; cat $f; } > src/REL/m534Dll/main.c
