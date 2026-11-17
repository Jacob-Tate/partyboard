"""Writes tools/mp5/types/m577Dll.h = m577Dll.head.h + the COM input tables (48 streams of 1681 s16 and the two
pointer tables over them), whose symbol names come from the split asm. Run by m577Dll.sh from the repo root."""
import re, sys
root = sys.argv[1] if len(sys.argv) > 1 else '.'
d = open(root + '/build/mp5/m577Dll.s', encoding='utf-8').read()
head = open(root + '/tools/mp5/types/m577Dll.head.h', encoding='utf-8').read()
out = [head.rstrip('\n'), '']
for tbl, n in (('lbl_1_data_B120', 12), ('lbl_1_data_28A18', 0x24)):
    m = re.search(r'\.obj %s, global\n(.*?)\.endobj' % tbl, d, re.S)
    names = re.findall(r'\.4byte (lbl_1_data_\w+)', m.group(1))
    assert len(names) == n
    out += ['extern s16 %s[1681];' % x for x in names]
    out.append('extern s16 *%s[%d];' % (tbl, n))
open(root + '/tools/mp5/types/m577Dll.h', 'w', encoding='utf-8', newline='\n').write('\n'.join(out) + '\n')
