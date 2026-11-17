#!/bin/bash
# Regenerates src/REL/m577Dll/main.c (Curvy Curbs) from MP5's m577 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes below; run from the repo root.
set -e
python tools/mp5/ports/m577Dll_gen_types.py .
python tools/mp5/decomp.py m577Dll --types tools/mp5/types/m577Dll.h | tail -2
f=build/mp5/m577Dll.c
python tools/mp5/port.py $f | head -1
python tools/mp5/ports/m577Dll_fix.py "$f"
mkdir -p src/REL/m577Dll
{ echo '// MP5 m577 (Curvy Curbs), generated from its m2c draft by tools/mp5/ports/m577Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m577Dll.h; cat $f; } > src/REL/m577Dll/main.c
