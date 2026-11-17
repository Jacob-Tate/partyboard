"""Writes tools/mp5/types/m515Dll.h = m515Dll.head.h + the externs of the data tables whose types only the symbol
list knows (COM input scripts, room decoration lists and their pointer tables). Run by m515Dll.sh from the repo root."""
import re, sys
root = sys.argv[1] if len(sys.argv) > 1 else '.'
sym = open(root + '/../mp5ref/config/GP5E01_00/rels/m515Dll/symbols.txt', encoding='utf-8').read()
head = open(root + '/tools/mp5/types/m515Dll.head.h', encoding='utf-8').read()
sizes = {m.group(1): (int(m.group(2), 16), int(m.group(3), 16))
         for m in re.finditer(r'^(lbl_1_data_\w+) = \.data:0x(\w+); // type:object size:0x(\w+)', sym, re.M)}
sizes = {k: (v[0], v[1]) for k, v in sizes.items()}
out = [head.rstrip('\n'), '']
for name, (off, size) in sizes.items():
    if 0xB0C <= off < 0x1094:
        out.append('extern M515Place %s[%d];' % (name, size // 8))
    elif 0x1184 <= off < 0x3978:
        out.append('extern u16 %s[%d];' % (name, size // 2))
for name, n in (('lbl_1_data_39B8', 60), ('lbl_1_data_3AA8', 60), ('lbl_1_data_3B98', 120)):
    assert sizes[name][1] == n * 4
    out.append('extern u16 *%s[%d];' % (name, n))
open(root + '/tools/mp5/types/m515Dll.h', 'w', encoding='utf-8', newline='\n').write('\n'.join(out) + '\n')
