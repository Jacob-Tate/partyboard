"""Hand fixes for the m547 draft (called by m547dll.sh with the draft path)."""
import re, sys
p = sys.argv[1]
s = open(p, encoding='utf-8').read()

def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

# press counts are s32[2] at 0xB4; m2c printed them as a byte offset from the work (0xB0 + 4 * (player + 1))
s = re.sub(r'\(&lbl_1_bss_488 \+ \(\((\w+) \+ 1\) \* 4\)\)->unkB0', r'lbl_1_bss_488.unkB4[\1]', s)
s = re.sub(r'temp_r4(\w*) = &lbl_1_bss_488 \+ \(\((\w+) \+ 1\) \* 4\);', r'temp_r4\1 = &lbl_1_bss_488.unkB4[\2];', s)
rep('temp_r4_6 = &lbl_1_bss_488 + (((((temp_r3_3 & 1) ^ temp_r4_5) - temp_r4_5) + 1) * 4);',
    'temp_r4_6 = &lbl_1_bss_488.unkB4[temp_r3_3 & 1];')
s = re.sub(r'(temp_r4\w*)->unkB0 = \(s32\) \(\1->unkB0 ([-+]) 1\);', r'*\1 \2= 1;', s)
s = re.sub(r'\bvoid \*(temp_r4(?:_4|_6|_2|_3)?);', r's32 *\1;', s)
# motion tables are s16[7] per player; m2c read them as structs
def motidx(m):
    return 'unk48[%s][%d]' % (m.group(1), int(m.group(2), 16) // 2)
s = re.sub(r'unk48\[(\w+)\]->unk([0-9A-F]+)', motidx, s)
s = re.sub(r'\*lbl_1_bss_488\.unk48\[(\w+)\]', r'lbl_1_bss_488.unk48[\1][0]', s)
s = re.sub(r'\*lbl_1_bss_6E8->unk48\[(\w+)\]', r'lbl_1_bss_6E8->unk48[\1][0]', s)

s = s.replace('CZoomM->unk0', 'CZoomM[0]')

rep('fn_1_8BC0(*lbl_1_bss_5C, lbl_1_bss_5C[0][1]);', 'fn_1_8BC0(lbl_1_bss_5C[0], lbl_1_bss_5C[1]);')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
