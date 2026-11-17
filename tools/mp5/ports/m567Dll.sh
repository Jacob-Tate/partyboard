#!/bin/bash
# Regenerates src/REL/m567Dll/main.c (Quilt for Speed) from MP5's m567 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/decomp.py m567Dll --types tools/mp5/types/m567Dll.h | tail -2
f=build/mp5/m567Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m567Dll_fix.py "$f"
mkdir -p src/REL/m567Dll
{ echo '// MP5 m567 (Quilt for Speed), generated from its m2c draft by tools/mp5/ports/m567Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m567Dll.h; cat $f; } > src/REL/m567Dll/main.c
