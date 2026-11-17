"""Hand fixes for the m538 draft; run by m538Dll.sh on build/mp5/m538Dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

def fn_span(name):
    m = re.search(r'(?m)^[\w *]+ %s\([^\n]*\) \{\n' % name, s)
    assert m, name
    e = s.index('\n}\n', m.end()) + 3
    return m.start(), e

def in_fn(name, a, b, regex=False):
    """replace a -> b inside function `name` only"""
    global s
    st, en = fn_span(name)
    body = s[st:en]
    if regex:
        nb = re.sub(a, b, body)
    else:
        assert a in body, (name, a)
        nb = body.replace(a, b)
    assert nb != body or a == b, (name, a)
    s = s[:st] + nb + s[en:]

PLY = {'EA': 'place', 'EC': 'alive', 'F0': 'player', 'F2': 'charNo', 'E6': 'hitF', '84': 'func', '88': 'step',
       '102': 'timerB', '8': 'pos.z', '0': 'pos.x'}
# the main work's player table indexed by hand: (*(m + (i * 4)))->unkNN
s = re.sub(r'\(\*\((\w+) \+ \(([\w>.\[\]-]+) \* 4\)\)\)->unk([0-9A-F]+)\b',
           lambda m: '%s->ply[%s]->%s' % (m.group(1), m.group(2), PLY[m.group(3)]), s)
s = re.sub(r'\*\*\((\w+) \+ \(([\w>.\[\]-]+) \* 4\)\)', r'\1->ply[\2]->pos.x', s)
s = re.sub(r'\*\((\w+) \+ \(([\w>.\[\]-]+) \* 4\)\)', r'\1->ply[\2]', s)
s = re.sub(r'(\w+)->ply\[(\d)\]->unkF2', r'\1->ply[\2]->charNo', s)
s = re.sub(r'(lbl_1_rodata_\w+)->unk0\b', r'\1[0]', s)

# the inlined "take a node from the effect list" -> fn_1_6D98
pat = re.compile(r'(\w+) = (\w+)->eff\.free;\n(\s*)if \(\1 != NULL\) \{\n\s*\2->eff\.free = (?:\(\? \*\) )?\1->next;\n\s*\1->func = (\w+);\n\s*\1->arg = ([^;]+);\n'
                 r'\s*\1->next = (?:\(\? \*\) )?\2->eff\.head;\n\s*if \((?:\(\? \*\) )?\1->next != NULL\) \{\n\s*\*\1->next = \1;\n\s*\}\n\s*\2->eff\.head = \1;\n\s*\}\n')
s, n = pat.subn(lambda m: '%s = fn_1_6D98(%s, %s, %s);\n' % (m.group(1), m.group(2), m.group(4), m.group(5)), s)
print('eff allocs:', n)
s = s.replace('? *temp_r', 'M538Eff *temp_r')

# camera: the 9th float arg (target z) was lost
rep('0.0f, 150.0f, M2C_ERROR(/* Read from unset register $f9 */));', '0.0f, 150.0f, 0.0f);')
# function pointers are 64-bit: never truncate them
s = re.sub(r'\(u32\) ([\w>.\[\]-]+(?:func|spinFunc)) (==|!=) (fn_1_\w+)', r'\1 \2 \3', s)
s = re.sub(r'\(u32\) ([\w>.\[\]-]+(?:func|spinFunc)) (==|!=) 0U', r'\1 \2 NULL', s)
s = re.sub(r'\(\((?:\?|s32) \(\*\)\((?:void|M538Spin) \*\)\) ([\w>.\[\]-]+)\) != NULL', r'\1 != NULL', s)
rep('temp_r31->ring[1].func(temp_r31 + 0x264)', 'temp_r31->ring[1].func(&temp_r31->ring[1])')
rep('temp_r31->ring[2].func(temp_r31 + 0x27C)', 'temp_r31->ring[2].func(&temp_r31->ring[2])')
rep('fn_1_5FC4(temp_r31 + 0x264, 1);', 'fn_1_5FC4(&temp_r31->ring[1], 1);')
rep('fn_1_5FC4(temp_r31 + 0x27C, 2);', 'fn_1_5FC4(&temp_r31->ring[2], 2);')
# ring function table (rodata_1A0 holds fn pointers)
st, en = fn_span('fn_1_61F8')
b = s[st:en]
b = re.sub(r'    s32 sp8\[4\];\n(?:    s32 \(\*sp8\[\d\]\)\(M538Ring \*\);\n)+', '', b)
b = re.sub(r'    sp8\[\d\] = lbl_1_rodata_1A0[^;]*;\n', '', b)
b = b.replace('sp8[ring->type]', 'lbl_1_rodata_1A0[ring->type]')
s = s[:st] + b + s[en:]
in_fn('fn_1_4F74', '    s32 sp18[4];\n    s32 sp8[4];\n', '    f32 sp18[4];\n    f32 sp8[4];\n')
rep('var_r4->next = var_r4 + 0x38;', 'var_r4->next = var_r4 + 1;')
# MP4 battle (type 3) result: coin_win 1 for the survivors (everybody on a draw), 0 for the others. MP5 stored the
# place (0 = best) in mgCoinBonus here.
rep('''            if (_CheckFlag(MP5_PRACTICE_FLAG) == 0) {
                GWPlayer[temp_r25].coin_win = temp_r24;
            }
''', '''            GWPlayerCoinWinSet(temp_r25, (temp_r31->tie != 0 || temp_r29->alive != 0) ? 1 : 0);
''')
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x104,', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M538Ply),')
# material colours from the rodata tables
for fn, tbl in (('fn_1_8CD8', '1EC'), ('fn_1_94DC', '21C'), ('fn_1_9C04', '258')):
    st, en = fn_span(fn)
    b = s[st:en]
    b = re.sub(r'    u8 sp[0-9A-F]+;\n', '', b)
    b = re.sub(r'    sp[0-9A-F]+ = lbl_1_rodata_%s[^;]*;\n' % tbl, '', b)
    b = re.sub(r'\*\(&sp8 \+ (.+)\);\n', lambda m: '((const u8 *) lbl_1_rodata_%s)[%s];\n' % (tbl, m.group(1)), b)
    b = b.replace('temp_r31 + 0x3C', 'temp_r31 + 1').replace('temp_r31_2 + 0x3C', 'temp_r31_2 + 1').replace('var_r30 += 0x3C', 'var_r30++')
    s = s[:st] + b + s[en:]
# per-character tables are in MP5 order
s = s.replace('lbl_1_data_28[temp_r31->charNo]', 'lbl_1_data_28[Mp5CharNo(temp_r31->charNo)]')
s = s.replace('lbl_1_data_394[ply->charNo]', 'lbl_1_data_394[Mp5CharNo(ply->charNo)]')
s = s.replace('lbl_1_data_3C8[ply->charNo]', 'lbl_1_data_3C8[Mp5CharNo(ply->charNo)]')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
