"""Hand fixes for the m515 (Hotel Goomba) draft; run by m515Dll.sh on build/mp5/m515Dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

def fn_span(name):
    m = re.search(r'(?m)^[\w *]+ %s\([^)]*\) \{\n' % name, s)
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

# ---- raw byte offsets into the work structs (m2c could not index the arrays: stride and offset give the field)
def split_terms(inner):
    """'((a * 0xC8) + (b * 0x28) + 0x34)' -> ([(a, 0xC8), (b, 0x28)], 0x34) or None"""
    inner = inner.strip()
    if inner.startswith('(') and inner.endswith(')'):
        depth, ok = 0, True
        for i, c in enumerate(inner):
            depth += (c == '(') - (c == ')')
            if depth == 0 and i < len(inner) - 1:
                ok = False
                break
        if ok:
            inner = inner[1:-1]
    terms, depth, cur = [], 0, ''
    i = 0
    while i < len(inner):
        c = inner[i]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
        if depth == 0 and inner[i:i + 3] == ' + ':
            terms.append(cur)
            cur = ''
            i += 3
            continue
        cur += c
        i += 1
    terms.append(cur)
    idx, off = [], 0
    for t in terms:
        t = t.strip()
        if re.fullmatch(r'0x[0-9A-F]+|\d+', t):
            off += int(t, 0)
            continue
        if t.startswith('(') and t.endswith(')'):
            t = t[1:-1]
        m = re.fullmatch(r'(.+) \* (0x[0-9A-F]+|\d+)', t)
        if not m:
            return None
        a = m.group(1).strip()
        if a.startswith('(') and a.endswith(')') and a.count('(') == 1:
            a = a[1:-1]
        idx.append((a, int(m.group(2), 0)))
    return idx, off

NODE = {0: 'unk0', 4: 'unk4', 8: 'unk8', 0xC: 'unkC', 0x14: 'unk14', 0x18: 'unk18.x', 0x1C: 'unk18.y', 0x20: 'unk18.z',
        0x24: 'unk24'}
CAM = {0: 'unk0', 4: 'unk4', 8: 'unk8', 0xC: 'unkC.x', 0x10: 'unkC.y', 0x14: 'unkC.z'}
OBJ = {0: 'unk0', 4: 'unk4', 0x28: 'unk28'}

def resolve(v, idx, off, ptr):
    """C expression for v + sum(idx*stride) + off; ptr: the address of a struct element, else the value"""
    st = tuple(x[1] for x in idx)
    i = [x[0] for x in idx]
    def addr(e):
        return '&' + e
    if st == (0x28,) and off == 0x13C:
        return '%s->unk130[%s].unkC' % (v, i[0])
    if st == (0x30,) and 0x234 <= off <= 0x248:
        k = off - 0x234
        if k == 0 and ptr:
            return '&%s->unk234[%s]' % (v, i[0])
        e = '%s->unk234[%s].%s' % (v, i[0], CAM[k])
        return addr(e) if ptr else e
    if st == (0x10,) and off == 0x2F4:
        return '&%s->unk2F4[%s]' % (v, i[0])
    if st == (0x2C,) and 0x488 <= off <= 0x4B0:
        k = off - 0x488
        if k == 0 and ptr:
            return '&%s->unk488[%s]' % (v, i[0])
        e = '%s->unk488[%s].%s' % (v, i[0], OBJ[k])
        return addr(e) if ptr else e
    if st == (0x32, 2) and off == 0x5EA:
        return '%s->unk5EA[%s * 25 + %s]' % (v, i[0], i[1])
    if st == (2,) and off in (0x5EA, 0x61C, 0x64E):
        return '%s->unk5EA[%d + %s]' % (v, (off - 0x5EA) // 0x32 * 25, i[0])
    if st == (4,) and off in (0x5E, 0x60):
        return '%s->unk5E[%s * 2 + %d]' % (v, i[0], off - 0x5E >> 1)
    if st == (4,) and off in (0x96, 0x98):
        return '%s->unk96[%s * 2 + %d]' % (v, i[0], off - 0x96 >> 1)
    if st == (8,) and 0x76 <= off <= 0x7C:
        return '%s->unk76[%s * 4 + %d]' % (v, i[0], off - 0x76 >> 1)
    if st == (6,) and 0xB6 <= off <= 0xBA:
        return '%s->unkB6[%s * 3 + %d]' % (v, i[0], off - 0xB6 >> 1)
    if st == (6, 2) and off == 0x1DC:
        return '%s->unk1DC[%s * 3 + %s]' % (v, i[0], i[1])
    if st == (6, 2) and off == 0xB6:
        return '%s->unkB6[%s * 3 + %s]' % (v, i[0], i[1])
    if st == (4, 2) and off == 0x96:
        return '%s->unk96[%s * 2 + %s]' % (v, i[0], i[1])
    if st == (0xC8, 0x28) and off >= 0x10:
        k = off - 0x10
        if k == 0 and ptr:
            return '&%s->unk10[(%s) * 5 + (%s)]' % (v, i[0], i[1])
        e = '%s->unk10[(%s) * 5 + (%s)].%s' % (v, i[0], i[1], NODE[k])
        if ptr and k == 0x18:
            return '&' + e[:-2]
        return addr(e) if ptr else e
    if st == (0xC8,):
        # row r, a fixed column
        col = {0x10: (0, 'unk0'), 0x14: (0, 'unk4'), 0x38: (1, None), 0x88: (3, None), 0xB0: (4, 'unk0'),
               0xB4: (4, 'unk4')}.get(off)
        if col:
            e = '%s->unk10[(%s) * 5 + %d]' % (v, i[0], col[0])
            return (addr(e) if col[1] is None else e + '.' + col[1])
    if st == (0x28,):
        row = {0x18: (0, 'unk8'), 0x1C: (0, 'unkC'), 0xD8: (1, None), 0x268: (3, None), 0x338: (4, 'unk8'),
               0x33C: (4, 'unkC')}.get(off)
        if row:
            e = '%s->unk10[%d * 5 + %s]' % (v, row[0], i[0])
            return (addr(e) if row[1] is None else e + '.' + row[1])
    return None

def close_paren(t, i):
    """index of the ')' matching the '(' at t[i]"""
    depth = 0
    for j in range(i, len(t)):
        if t[j] == '(':
            depth += 1
        elif t[j] == ')':
            depth -= 1
            if depth == 0:
                return j
    return -1

def fix_offsets(t):
    # value forms: *(v + (...))
    out, pos = [], 0
    pat = re.compile(r'\*\((\w+) \+ \(')
    while True:
        m = pat.search(t, pos)
        if not m:
            out.append(t[pos:])
            break
        op = m.end() - 1
        cp = close_paren(t, op)
        r = None
        if cp > 0 and t[cp + 1:cp + 2] == ')':
            sp = split_terms(t[op:cp + 1])
            if sp:
                r = resolve(m.group(1), sp[0], sp[1], False)
        if r:
            out.append(t[pos:m.start()])
            out.append(r)
            pos = cp + 2
        else:
            out.append(t[pos:m.end()])
            pos = m.end()
    t = ''.join(out)
    # address forms: v + (...)
    out, pos = [], 0
    pat = re.compile(r'(?<![\w>.])(temp_r\d+(?:_\d+)?|arg\d|var_r\d+(?:_\d+)?) \+ \(')
    while True:
        m = pat.search(t, pos)
        if not m:
            out.append(t[pos:])
            break
        op = m.end() - 1
        cp = close_paren(t, op)
        r = None
        if cp > 0:
            sp = split_terms(t[op:cp + 1])
            if sp:
                r = resolve(m.group(1), sp[0], sp[1], True)
        if r:
            out.append(t[pos:m.start()])
            out.append(r)
            pos = cp + 1
        else:
            out.append(t[pos:m.end()])
            pos = m.end()
    return ''.join(out)

s = fix_offsets(s)
# **node->unk14 (the model of the Goomba object a node points to)
s = re.sub(r'\*(\w+->unk10\[[^\]]*\]\.unk14)\b', r'\1->unk0', s)
s = re.sub(r'\((\w+->unk10\[[^\]]*\]\.unk14)\)->', r'\1->', s)

s = re.sub(r'\bMgSeqModeNext\([^;]+\);', 'MgSeqModeNext();', s)
# OMOBJ raw offsets (model / motion id arrays)
s = re.sub(r'->unk68C->unk48->unk([0-9A-F]+)\b', lambda m: '->unk68C->motion[%d]' % (int(m.group(1), 16) // 2), s)
s = s.replace('->unk68C->unk40', '->unk68C->model').replace('->unk68C->unk48', '->unk68C->motion')
s = s.replace('Hu3DModelAttrReset(*(temp_r31->unk224[temp_r31->unk1D6])->unk68C->model, 0x40000001U)',
              'Hu3DModelAttrReset(*temp_r31->unk224[temp_r31->unk1D6]->unk68C->model, 0x40000001U)')
rep('(void *) (temp_r31 + 0x380)', '&temp_r31->unk10[22]')
rep('(void *) (temp_r31 + 0x60)', '&temp_r31->unk10[2]')
s = re.sub(r'\((arg\d) \+ \((\w+) \* 2\)\)->unk61C', lambda m: '%s->unk5EA[25 + %s]' % (m.group(1), m.group(2)), s)
s = re.sub(r'\((arg\d) \+ \((\w+) \* 2\)\)->unk64E', lambda m: '%s->unk5EA[50 + %s]' % (m.group(1), m.group(2)), s)
s = s.replace('MgSeqModeNext((s32 *)3);', 'MgSeqModeNext();')
s = re.sub(r'\*(\w+)->unk684 = 0;', lambda m: '%s->unk684->unk0 = 0;' % m.group(1), s)
rep('fn_1_9920(lbl_1_bss_4->data + 0x334);', 'fn_1_9920(&((M515Main *) lbl_1_bss_4->data)->unk334);')
s = re.sub(r'->motion->unk([0-9A-F]+)', lambda m: '->motion[%d]' % (int(m.group(1), 16) // 2), s)

# ---- the work structs: sizes of the 64-bit structs
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x6A0, MEMORY_DEFAULT_NUM)', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M515Player), MEMORY_DEFAULT_NUM)')
s = s.replace('*(temp_r30 + ((var_r29 * 4) + 0x224))', 'temp_r30->unk224[var_r29]')
# the 9th float argument of Hu3DCameraPosSet (target z) was lost by m2c
rep('0.0f, 150.0f, M2C_ERROR(/* Read from unset register $f9 */)', '0.0f, 150.0f, sp8')
# MP5 character tables are in MP5's order
rep('lbl_1_data_118[temp_r31->unk2][var_r30]', 'lbl_1_data_118[Mp5CharNo(temp_r31->unk2)][var_r30]')

# byte offsets into the stack copies of rodata tables (u16 / f32 elements)
rep('*(&sp10[4] + ((arg0->unk47C * 8) + (temp_r29->unk24 * 2)))', 'sp10[4 + arg0->unk47C * 4 + temp_r29->unk24]')
rep('*(&sp18[4] + (var_r30 * 0xC)) /* TODO(mp5): byte offset */, *(&sp18[4] + ((var_r30 * 0xC) + 4)), *(&sp18[4] + ((var_r30 * 0xC) + 8))',
    'sp18[4 + var_r30 * 3], sp18[5 + var_r30 * 3], sp18[6 + var_r30 * 3]')
rep('&sp18[4] + (var_r30 * 0xC), 0xC', '&sp18[4 + var_r30 * 3], 0xC')
# fn_1_9DF8: m2c put the f32 sp10 (rodata_224[0]) into the u16 pan table's 5th slot
in_fn('fn_1_9DF8', 'sp8[4]', 'sp10')
in_fn('fn_1_9DF8', 'u16 sp8[5];', 'u16 sp8[4];\n    f32 sp10;')
# fn_1_32C4: the stack Vecs (spN) m2c split into f32 locals / Vec locals live in one array, so a Vec * onto three
# consecutive floats stays valid (MSVC reorders separate locals)
def spv_fix(name):
    global s
    st, en = fn_span(name)
    body = s[st:en]
    def idx(h):
        return (int(h, 16) - 0x194) // 4
    def big(h):
        return int(h, 16) >= 0x194
    body = re.sub(r'(?m)^    (?:f32|s32|Vec) sp([0-9A-F]+);\n', lambda m: '' if big(m.group(1)) else m.group(0), body)
    body = re.sub(r'\bsp([0-9A-F]+)\.([xyz])\b', lambda m: ('spv[%d]' % (idx(m.group(1)) + 'xyz'.index(m.group(2)))) if big(m.group(1)) else m.group(0), body)
    body = re.sub(r'&sp([0-9A-F]+)\b', lambda m: ('(Vec *) &spv[%d]' % idx(m.group(1))) if big(m.group(1)) else m.group(0), body)
    body = re.sub(r'(?<![\w&])sp([0-9A-F]+)\b(?!\[)', lambda m: ('spv[%d]' % idx(m.group(1))) if big(m.group(1)) else m.group(0), body)
    body = re.sub(r'(?m)^    f32 \*(sp[0-9A-F]+);', lambda m: '    Vec *%s;' % m.group(1), body)
    body = body.replace('{\n', '{\n    f32 spv[0x170];\n', 1)
    s = s[:st] + body + s[en:]
spv_fix('fn_1_32C4')
# function pointers must not be truncated to u32 for the comparison
s = s.replace('(u32) temp_r30->unk688 ==', 'temp_r30->unk688 ==')
# byte steps of typed pointers: one element
s = re.sub(r'(var_r2[56](?:_2)?) \+= 2;', lambda m: '%s++;' % m.group(1), s)
rep('var_r27 += 8;', 'var_r27++;')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
