#!/bin/bash
# Regenerates src/REL/m515Dll/main.c (Hotel Goomba) from MP5's m515 (see tools/mp5/decomp.py for the
# prerequisites). Automatic pipeline + the hand fixes in m515Dll_fix.py; run from the repo root.
set -e
python tools/mp5/ports/m515Dll_gen_types.py .
python tools/mp5/decomp.py m515Dll --types tools/mp5/types/m515Dll.h | tail -2
f=build/mp5/m515Dll.c
python tools/mp5/port.py $f | head -3
python tools/mp5/ports/m515Dll_fix.py "$f"
mkdir -p src/REL/m515Dll
{ echo '// MP5 m515 (Hotel Goomba), generated from its m2c draft by tools/mp5/ports/m515Dll.sh (do not hand-edit lightly).'
  echo '#include "REL/mp5compat.h"'; grep -v "^extern" tools/mp5/types/m515Dll.h; cat $f; } > src/REL/m515Dll/main.c
