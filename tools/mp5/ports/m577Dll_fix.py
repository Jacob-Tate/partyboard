"""Hand fixes for the m577 draft; run by m577Dll.sh on build/mp5/m577Dll.c."""
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

def in_fn(name, a, b, regex=False, count=0):
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

def rn(prefix, table):
    """rename `<prefix>->unkXX` using an offset -> accessor table"""
    global s
    def f(m):
        return m.group(1) + '->' + table[m.group(2)] if m.group(2) in table else m.group(0)
    s = re.sub(r'(' + prefix + r')->unk([0-9A-F]+)\b', f, s)

PLY = {'18': 'obj', '1C': 'side', '20': 'lane', '34': 'blink', '36': 'model', '3A': 'charNo'}
LANE = {'20': 'pos.x', '24': 'pos.y', '40': 'extra', '54': 'baseY', '5C': 'model', '5E': 'wheel', '60': 'shadow',
        '62': 'unk62', '64': 'unk64'}
EXTRA = {'28': 'model', '2C': 'shadow'}
CAM = {'0': 'target.x', '4': 'target.y', '8': 'target.z', 'C': 'az', '10': 'el', '14': 'dist'}
MOT = {'4': 'motion[2]', '6': 'motion[3]', '8': 'motion[4]', 'A': 'motion[5]', 'C': 'motion[6]', 'E': 'motion[7]', '10': 'motion[8]'}
COURSE = {('%X' % o): 'mdl[%d]' % ((o - 4) // 2) for o in range(4, 0x3C, 2)}

# the inlined "take a node from the pool" -> fn_1_26C0
pat = re.compile(r'(\w+) = (\w+)->pool\.free;\n(\s*)if \(\1 != NULL\) \{\n\s*\2->pool\.free = \(\? \*\) \1->next;\n\s*\1->func = (\w+);\n\s*\1->arg = ([^;]+);\n'
                 r'\s*\1->next = \(\? \*\) \2->pool\.head;\n\s*if \(\(\? \*\) \1->next != NULL\) \{\n\s*\*\1->next = \1;\n\s*\}\n\s*\2->pool\.head = \1;\n\s*\}\n')
s, n = pat.subn(lambda m: '%s = fn_1_26C0(&%s->pool, %s, %s);\n' % (m.group(1), m.group(2), m.group(4), m.group(5)), s)
print('pool allocs:', n)
s = re.sub(r'\? \*(temp_r\d+);', r'M577Node *\1;', s)
rep('var_r4->next = var_r4 + 0x14;', 'var_r4->next = var_r4 + 1;')
rep('var_r29 += 0x44; /* TODO(mp5): byte step? */', 'var_r29++;')
rep('0.0f, 150.0f, M2C_ERROR(/* Read from unset register $f9 */));', '0.0f, 150.0f, 0.0f);')
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x54, MEMORY_DEFAULT_NUM)', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M577Ply), MEMORY_DEFAULT_NUM)')
rep('*(temp_r30 + (var_r29 * 4)) = temp_r31->data;', 'temp_r30->ply[var_r29] = temp_r31->data;')
# particle hook: work is the M577Fx; its emitPos is the point to follow
rep('''                temp_r4 = particleP->work->unk8;
                var_r31->pos.x = temp_r4->par;
                var_r31->pos.y = temp_r4->anim;
                var_r31->pos.z = temp_r4->emitPos;''', '''                temp_r4 = ((M577Fx *) particleP->work)->emitPos;
                var_r31->pos.x = temp_r4->x;
                var_r31->pos.y = temp_r4->y;
                var_r31->pos.z = temp_r4->z;''')
rep('M577Fx *temp_r4;', 'Vec *temp_r4;')

# stack Vec2s: m2c split them into separate f32 locals but passes &spXX (MSVC reorders them) -> arrays
def stackvec(fn, groups):
    global s
    st, en = fn_span(fn)
    body = s[st:en]
    decl = ''
    for arr, names in groups:
        body = re.sub(r'&%s\b' % names[0], arr, body)
        for i, n in enumerate(names):
            body = re.sub(r'\b%s\b(?!\[)' % n, '%s[%d]' % (arr, i), body)
            body = body.replace('    f32 %s[%d];\n' % (arr, i), '')
        decl += '    f32 %s[2];\n' % arr
    body = re.sub(r'(\) \{\n)', lambda m: m.group(1) + decl, body, count=1)
    s = s[:st] + body + s[en:]

A_ = ('spA', ['sp1C', 'sp20'])
stackvec('fn_1_72D0', [A_, ('spB', ['sp14', 'sp18']), ('spP', ['spC', 'sp10'])])
stackvec('fn_1_7D24', [A_, ('spB', ['sp14', 'sp18']), ('spP', ['spC', 'sp10'])])
stackvec('fn_1_85F4', [A_, ('spB', ['sp10', 'sp14']), ('spP', ['sp8', 'spC'])])
stackvec('fn_1_8BB8', [A_, ('spB', ['sp10', 'sp14']), ('spP', ['sp8', 'spC'])])
stackvec('fn_1_3E10', [('spA', ['sp14', 'sp18']), ('spB', ['spC', 'sp10'])])
s = s.replace('var_r29 += 0x10; /* TODO(mp5): byte step? */', 'var_r29 += 4;')
s = s.replace('var_r29_2 += 0x10; /* TODO(mp5): byte step? */', 'var_r29_2 += 4;')
s = s.replace('var_r25 += 0x10; /* TODO(mp5): byte step? */', 'var_r25 += 4;')
# per-character tables are in MP5 order
rep('lbl_1_data_28[temp_r31->charNo][var_r29]', 'lbl_1_data_28[Mp5CharNo(temp_r31->charNo)][var_r29]')
s = s.replace('lbl_1_data_2A8[temp_r28->charNo]', 'lbl_1_data_2A8[Mp5CharNo(temp_r28->charNo)]')
s = s.replace('lbl_1_data_2A8[temp_r28_2->charNo]', 'lbl_1_data_2A8[Mp5CharNo(temp_r28_2->charNo)]')

# lost swap temp in the lane shuffle (asm: lhzx a, lhzx b, sthx b->a, sthx a->b)
rep('        sp8[temp_r28] = (u16) (s16) sp8[temp_r3];\n        sp8[temp_r3] = (u16) (s16) sp8[temp_r28];',
    '        {\n            u16 swp = sp8[temp_r28];\n            sp8[temp_r28] = sp8[temp_r3];\n            sp8[temp_r3] = swp;\n        }')
# --- pointer-offset expressions on the main work / sides (GC offsets -> fields) ---
s = re.sub(r'(\w+) \+ 0xA4C\b', r'&\1->course[1].ctrA', s)
s = re.sub(r'(\w+) \+ 0xA4E\b', r'&\1->course[1].ctrB', s)
s = re.sub(r'(\w+) \+ 0x5C\b', r'&\1->side[1]', s)
s = re.sub(r'(\w+) \+ 0x9F4\b', r'&\1->course[1]', s)
s = re.sub(r'(\w+) \+ 0x10F0\b', r'&\1->chain[1]', s)
s = re.sub(r'(\w+) \+ 0x15DC\b', r'&\1->chain[2]', s)
s = re.sub(r'(\w+) \+ 0x958\b', r'&\1->cam[1]', s)
s = re.sub(r'(\w+) \+ \(\((\w+) \* 0x10\) \+ 0x1B04\)', r'&\1->fx[\2]', s)
s = re.sub(r'\*\((\w+) \+ \(\(\(\1->winner \^ 1\) \* 0x4C\) \+ 0x5A\)\)', r'\1->side[\1->winner ^ 1].stop', s)
s = re.sub(r'\*\((\w+) \+ \(\(\(\1->winner \^ 1\) \* 0x4C\) \+ 0x3C\)\)', r'\1->side[\1->winner ^ 1].func', s)
s = re.sub(r'\*\((\w+) \+ \(\(\1->winner \* 0x4C\) \+ \((\w+) \* 4\) \+ 0x10\)\)', r'\1->side[\1->winner].ply[\2]', s)
s = re.sub(r'\*\((\w+) \+ \((\w+) \* 4\)\)', r'\1->ply[\2]', s)       # main (BF8/1600) and side (BF8 temp_r31_2) alike
s = re.sub(r'\*\*\((\w+) \+ \((\w+) \* 4\)\)', r'\1->ply[\2]->pos.x', s)
rep('*(lbl_1_bss_C->data + (temp_r31->player * 4)) = temp_r31;', '((M577Main *) lbl_1_bss_C->data)->ply[temp_r31->player] = temp_r31;')
s = s.replace('(? (*)(void *)) ', '')
s = re.sub(r'\(\(\(\? \(\*\)\(void \*\)\) temp_r31->func\) != NULL\)', 'temp_r31->func != NULL', s)
s = s.replace('(u32) ', '(u32) ') # (kept)
# function pointers kept as void * in the header: compare/call through casts
s = re.sub(r'\(u32\) ([\w>.\[\]\- ^]+\.func) == (fn_1_\w+)', r'\1 == (void *) \2', s)
s = re.sub(r'\(u32\) (\w+->side\[\w+\]\.func) == (fn_1_\w+)', r'\1 == (void *) \2', s)
s = re.sub(r'\(u32\) (\w+->side\[[^\]]*\]\.func) == (fn_1_\w+)', r'\1 == (void *) \2', s)
s = re.sub(r'\((?:u32)\) (\w+->side\[\d\]\.func) == (fn_1_\w+)', r'\1 == (void *) \2', s)

s = re.sub(r'\((\w+->ply\[\w+\])\)->', r'\1->', s)
s = re.sub(r'\*\(((?:\w+->)?course) \+ \(\((\w+) \* 2\) \+ 0x22\)\)', r'\1->mdl[0xF + \2]', s)
s = re.sub(r'\*lbl_1_data_32C\[0\]\[(\w+)\]', r'lbl_1_data_32C[\1][0]', s)
s = s.replace('->side->unk44', '->side->state')
rep('temp_r31->func(temp_r31);', '((void (*)(M577Ply *)) temp_r31->func)(temp_r31);')
rep('temp_r31->side[0].func(&temp_r31->side[0]);', '((void (*)(M577Side *)) temp_r31->side[0].func)(&temp_r31->side[0]);')
rep('temp_r31->side[1].func(&temp_r31->side[1]);', '((void (*)(M577Side *)) temp_r31->side[1].func)(&temp_r31->side[1]);')
in_fn('fn_1_B3CC', 'void *temp_r31;', 's16 *temp_r31;')
# --- fields m2c could not type ---
PL = r'(?:\w+->)?(?:side\[\d\]\.)?ply\[\w+\]'
rn(PL, PLY)
rn(PL + r'->lane', LANE)
rn(PL + r'->lane->extra', EXTRA)
rn(r'\w+->lane(?:\[\w+\])?', LANE)
rn(r'\(\w+->lane\[\w+\]\)', LANE)
rn(r'\w+->lane(?:\[\w+\])?->extra', EXTRA)
rn(r'\w+->extra', EXTRA)
rn(r'\w+->cam', CAM)
rn(r'\w+->obj->unk48', MOT) if False else None
s = re.sub(r'->obj->unk48->unk([0-9A-F]+)\b', lambda m: '->obj->' + MOT[m.group(1)], s)
rn(r'\w+->course', COURSE)
s = re.sub(r'->road->unk8\b', '->road->len', s)
s = re.sub(r'\(temp_r30 \+ \(var_r29_3 \* 4\)\)', 'temp_r30->ply[var_r29_3]', s)
s = re.sub(r'(lbl_1_(?:data_270|data_32C)\[0\])\[(\w+)\]->unk0', lambda m: m.group(1)[:-3] + '[%s][0]' % m.group(2), s)
s = re.sub(r'(lbl_1_rodata_\w+)->unk0\b', r'\1[0]', s)
s = re.sub(r'lbl_1_data_270\[0\]\[var_r31\]->unk0', 'lbl_1_data_270[var_r31][0]', s)
s = s.replace('temp_r31->cam[1].dist', 'temp_r31->cam[1].dist')
s = s.replace('->unk34 = 1;', '->blink = 1;')
s = s.replace('Hu3DModelPosSetV(temp_r31_2->lane[0]->model, temp_r31_2->lane[0] + 0x20)', 'Hu3DModelPosSetV(temp_r31_2->lane[0]->model, &temp_r31_2->lane[0]->pos)')
for i in range(3):
    s = s.replace('Hu3DModelPosSetV(temp_r31_2->lane[%d]->model, temp_r31_2->lane[%d] + 0x20)' % (i, i), 'Hu3DModelPosSetV(temp_r31_2->lane[%d]->model, &temp_r31_2->lane[%d]->pos)' % (i, i))
s = s.replace('temp_r31_2->lane[0] + 0x20', '&temp_r31_2->lane[0]->pos')
s = re.sub(r'Hu3DModelPosSetV\((\w+)->extra->model, \1->extra\)', r'Hu3DModelPosSetV(\1->extra->model, &\1->extra->pos)', s)
s = re.sub(r'Hu3DModelPosSetV\((\w+)->extra->shadow, \1->extra\)', r'Hu3DModelPosSetV(\1->extra->shadow, &\1->extra->pos)', s)
s = re.sub(r'Hu3DModelPosSetV\((\w+->lane\[0\])->extra->model, \1->extra\)', r'Hu3DModelPosSetV(\1->extra->model, &\1->extra->pos)', s)
s = re.sub(r'Hu3DModelPosSetV\(temp_r31_2->lane\[0\]->extra->model, temp_r31_2->lane\[0\]->extra\)', 'Hu3DModelPosSetV(temp_r31_2->lane[0]->extra->model, &temp_r31_2->lane[0]->extra->pos)', s)
s = s.replace('*temp_r31_2->ply[0]->lane->extra = 100.0f;', 'temp_r31_2->ply[0]->lane->extra->pos.x = 100.0f;')
s = re.sub(r'temp_r4(_2)?->y ([-+])= ', r'temp_r4\1->pos.y \2= ', s)
s = s.replace('Hu3DModelPosSetV((temp_r31_2->ply[var_r29_8])->model, temp_r31_2->ply[var_r29_8]);', 'Hu3DModelPosSetV(temp_r31_2->ply[var_r29_8]->model, &temp_r31_2->ply[var_r29_8]->pos);')
s = re.sub(r'omSetTra\(\(temp_r31_2->ply\[var_r29_8\]\)->obj, temp_r31_2->ply\[var_r29_8\]->pos\.x, \(temp_r31_2->ply\[var_r29_8\]\)->unk4, \(temp_r31_2->ply\[var_r29_8\]\)->unk8\)',
           'omSetTra(temp_r31_2->ply[var_r29_8]->obj, temp_r31_2->ply[var_r29_8]->pos.x, temp_r31_2->ply[var_r29_8]->pos.y, temp_r31_2->ply[var_r29_8]->pos.z)', s)
s = re.sub(r'\((temp_r31_2->ply\[var_r29_8\])\)->', r'\1->', s)
rep('Hu3DModelPosSetV(temp_r31_2->ply[var_r29_8]->model, temp_r31_2->ply[var_r29_8]);', 'Hu3DModelPosSetV(temp_r31_2->ply[var_r29_8]->model, &temp_r31_2->ply[var_r29_8]->pos);')
rep('omSetTra(temp_r31_2->ply[var_r29_8]->obj, *temp_r31_2->ply[var_r29_8], temp_r31_2->ply[var_r29_8]->unk4, temp_r31_2->ply[var_r29_8]->unk8);', 'omSetTra(temp_r31_2->ply[var_r29_8]->obj, temp_r31_2->ply[var_r29_8]->pos.x, temp_r31_2->ply[var_r29_8]->pos.y, temp_r31_2->ply[var_r29_8]->pos.z);')
s = s.replace('(? *) ', '')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
