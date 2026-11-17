"""Hand fixes for the m567 draft; run by m567Dll.sh on build/mp5/m567Dll.c."""
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

# the inlined "take a node from the pool" -> fn_1_4704
pat = re.compile(r'(\w+) = (\w+)->pool\.free;\n(\s*)if \(\1 != NULL\) \{\n\s*\2->pool\.free = \(\? \*\) \1->unk4;\n\s*\1->unkC = (\w+);\n'
                 r'\s*\1->unk10 = ([^;]+);\n\s*\1->unk4 = \(\? \*\) \2->pool\.head;\n\s*if \(\(\? \*\) \1->unk4 != NULL\) \{\n\s*\*\1->unk4 = \1;\n\s*\}\n\s*\2->pool\.head = \1;\n\s*\}\n')
s, n = pat.subn(lambda m: '%s = fn_1_4704(&%s->pool, %s, %s);\n' % (m.group(1), m.group(2), m.group(4), m.group(5)), s)
print('pool allocs:', n)
s = re.sub(r'\? \*(temp_r\d+);', r'M567Node *\1;', s)

# cameras: the 9th argument (target z) is lost by m2c
rep('0.0f, 150.0f, M2C_ERROR(/* Read from unset register $f9 */));', '0.0f, 150.0f, 0.0f);')
rep('    v->unkA = 0;', '    v->unk8 = 0;')
in_fn('fn_1_4680', 'var_r4->next = var_r4 + 0x14;', 'var_r4->next = var_r4 + 1;')

# ply[i] fields (m2c lost the player type of the side's ply[] entries)
PL = r'((?:[\w\[\]\.]|->)*ply\[\w+\])'
for a, b in [('unk24','model'),('unk26','player'),('unk28','charNo'),('unk18','obj'),('unk2A','group'),('x','pos.x'),('y','pos.y'),('z','pos.z'),
             ('unkC','rot.x'),('unk10','rot.y'),('unk14','rot.z')]:
    s = re.sub(PL + r'->' + a + r'\b', r'\1->' + b, s)
s = re.sub(r', ' + PL + r' \+ 0xC\)', r', &\1->rot)', s)
s = re.sub(r', ' + PL + r'\)', r', &\1->pos)', s) if False else s
s = re.sub(r'(Hu3DMtxTransGet\(\w+, )' + PL + r'\)', r'\1&\2->pos)', s)
s = s.replace('lbl_1_rodata_70->unk0', 'lbl_1_rodata_70[0]')
s = s.replace('MgSeqModeNext((f32 *) &lbl_1_bss_0, temp_r3_2);', 'MgSeqModeNext();')
s = s.replace('sizeof(M567Player), MEMORY_DEFAULT_NUM);\n    temp_r30 = temp_r3->data;', 'sizeof(M567Main), MEMORY_DEFAULT_NUM);\n    temp_r30 = temp_r3->data;')
s = s.replace('*(temp_r30 + (var_r29 * 4)) = temp_r31->data;', 'temp_r30->ply[var_r29] = temp_r31->data;')

s = re.sub(r'(lbl_1_rodata_\w+)->unk0\b', r'\1[0]', s)
s = re.sub(r'\*\((\w+) \+ \(\(var_r29_2 \* 6\) \+ \(var_r28 \* 2\) \+ 0xCB4\)\)', r'\1->tileB[var_r29_2 * 3 + var_r28]', s)
s = re.sub(r'((?:PosSetV|TransGet)\([^;]*?, )(' + PL + r')\);', r'\1&\2->pos);', s)

# raw offsets into the side blocks (M567Main + 0x10 + side * 0x1B4)
SIDE_F = {0x80:'cur.pos.x',0x84:'cur.pos.y',0x88:'cur.pos.z',0x8C:'cur.rot.x',0x90:'cur.rot.y',0x94:'cur.rot.z',
          0x98:'cur.from.x',0x9C:'cur.from.y',0xA0:'cur.from.z',0xA4:'cur.to.x',0xA8:'cur.to.y',0xAC:'cur.to.z',
          0xB0:'cur.model',0xB2:'cur.mot32',0xB4:'cur.mot34',0xB6:'cur.mot36',0xB8:'cur.mot38',0xBA:'cur.mini[0]',0xBC:'cur.mini[1]',
          0xBE:'cur.mini[2]',0xC0:'cur.pum[0]',0xC2:'cur.pum[1]',0xC4:'cur.pum[2]',0xC6:'cur.fx',
          0x1A4:'isTeam',0x1A6:'row',0x1A8:'col',0x1AA:'nrow',0x1AC:'ncol',0x1AE:'state',0x1B0:'timer',0x1B2:'limit'}
for i in range(3): SIDE_F[0x7A + 2*i] = 'plan[%d]' % i
def sfield(off):
    if off in SIDE_F: return SIDE_F[off]
    if off >= 0xCC and off < 0x1A4: return 'slot.unk%X' % (off - 0xCC) if False else None
    return None
E = r'(\([^()]*\)|[\w>-]+)'
def sub_deref(m):
    f = sfield(int(m.group(3), 16) - 0x10)
    return '%s->side[%s].%s' % (m.group(1), m.group(2).strip('()') if m.group(2).startswith('(') else m.group(2), f) if f else m.group(0)
s = re.sub(r'\*\((\w+) \+ \(\(' + E + r' \* 0x1B4\) \+ (0x[0-9A-Fa-f]+)\)\)', sub_deref, s)
def sub_addr(m):
    f = sfield(int(m.group(3), 16) - 0x10)
    if f and f.endswith('.x'): f = f[:-2]
    return '&%s->side[%s].%s' % (m.group(1), m.group(2).strip('()') if m.group(2).startswith('(') else m.group(2), f) if f else m.group(0)
s = re.sub(r'(\w+) \+ \(\(' + E + r' \* 0x1B4\) \+ (0x[0-9A-Fa-f]+)\)', sub_addr, s)
def sub_abs(m):
    off = int(m.group(2), 16)
    if 0x10 <= off < 0x378:
        i, o = divmod(off - 0x10, 0x1B4)
        f = sfield(o)
        if f and f.endswith('.x'): f = f[:-2]
        if f: return '&%s->side[%d].%s' % (m.group(1), i, f)
    return m.group(0)
s = re.sub(r'(temp_r\d+) \+ (0x[0-9A-Fa-f]+)(?=\))', sub_abs, s)
s = re.sub(r'\*\((\w+) \+ \(\(var_r29_\d \* 6\) \+ \(var_r28 \* 2\) \+ 0xC84\)\)', lambda m: m.group(0), s)
s = re.sub(r'\*\((\w+) \+ \(\((var_r29\w*) \* 2\) \+ 0xCDE\)\)', r'\1->tileB[21 + \2]', s)
s = re.sub(r'\*\((\w+) \+ \(\((var_r29\w*) \* 6\) \+ \((var_r28\w*) \* 2\) \+ 0xC84\)\)', r'\1->tileA[\2 * 3 + \3]', s)

s = re.sub(r'\*\((\w+) \+ \(\((var\w+) \* 6\) \+ \((var\w+) \* 2\) \+ 0xCB4\)\)', r'\1->tileB[\2 * 3 + \3]', s)
def _ply_tmp(m):
    fnb = s[s.rfind('\n}\n', 0, m.start()):m.start()]
    if re.search(r'Vec \*%s;' % m.group(1), fnb):
        return '%s = &%s->pos;' % (m.group(1), m.group(2))
    return m.group(0)
s = re.sub(r'(temp_r\d+(?:_\d)?) = (\w[\w\[\]\.>-]*ply\[\w+\]);', _ply_tmp, s)
in_fn('fn_1_60F8', 's32 sp8[4];', 'M567Player *sp8[4];')
in_fn('fn_1_1474', 'void *temp_r30;', 'M567Cursor *temp_r30;')
in_fn('fn_1_1474', '.cur.pos, temp_f1 = Hu3DMotionTimeGet(temp_r30->unk30)', '.cur, temp_f1 = Hu3DMotionTimeGet(temp_r30->model)')
in_fn('fn_1_1474', 'temp_r30->unk46', 'temp_r30->fx')

in_fn('fn_1_1474', 'temp_r30->unk0, temp_r30->unk4, temp_r30->unk8', 'temp_r30->pos.x, temp_r30->pos.y, temp_r30->pos.z')
in_fn('fn_1_1474', 'void *temp_r30_2;', 'M567Cursor *temp_r30_2;')
in_fn('fn_1_1474', '.cur.pos;\n                temp_f1_2', '.cur;\n                temp_f1_2')
in_fn('fn_1_1474', 'temp_r30_2->unk30', 'temp_r30_2->model')
in_fn('fn_1_1474', 'temp_r30_2->unk46', 'temp_r30_2->fx')

in_fn('fn_1_1474', 'temp_r30_2->unk0, temp_r30_2->unk4, temp_r30_2->unk8', 'temp_r30_2->pos.x, temp_r30_2->pos.y, temp_r30_2->pos.z')
s = re.sub(r'\.cur\.pos(?=[;,])', '.cur', s)
s = re.sub(r'(Hu3DModelPosSetV\(\w+->fx, )(temp_r3\w*)\)', r'\1&\2->pos)', s)
in_fn('fn_1_32CC', 'temp_r30->unk0, temp_r30->unk4, temp_r30->unk8', 'temp_r30->pos.x, temp_r30->pos.y, temp_r30->pos.z') if False else None
s = s.replace('*(lbl_1_bss_4->data + (temp_r31->player * 4)) = temp_r31;', '((M567Main *) lbl_1_bss_4->data)->ply[temp_r31->player] = temp_r31;')
s = s.replace('temp_r31->reel->unk4', 'temp_r31->reel->state')
for a, b in [('0x1C4', '&temp_r31->side[1]'), ('0xDC', '&temp_r31->side[0].slot'), ('0xB88', '&temp_r31->cam[1]'), ('0x290', '&temp_r31->side[1].slot'), ('0xB50', '&temp_r31->cam[0]')]:
    s = s.replace('temp_r31 + ' + a + ')', b + ')').replace('temp_r31 + ' + a + ',', b + ',')
s = re.sub(r'\(lbl_1_data_254 \+ \((\w+) \* 0x18\)\)->unk([0-9A-F]+)', lambda m: 'lbl_1_data_254[%s * 6 + %d]' % (m.group(1), int(m.group(2), 16) // 4), s)

# fn_1_5BD4: the grid builder (stack copy of rodata_138 inside sp8)
in_fn('fn_1_5BD4', '    ? sp8[6];\n    u16 sp8[7];', '    u16 sp8[6];')
in_fn('fn_1_5BD4', r'    void \*temp_r4;\n', '', True)
in_fn('fn_1_5BD4', r'    temp_r4 = lbl_1_rodata_138 - 2;\n.*\n.*\n', '', True)
in_fn('fn_1_5BD4', r'\*\(&sp8\[6\] \+ (\(.*\))\);', r'*(s16 *) ((u8 *) lbl_1_rodata_138 + \1);', True)
in_fn('fn_1_5BD4', r'\*\(grid \+ (\(.*?\))\) = ', r'*(s16 *) ((u8 *) grid + \1) = ', True)

s = s.replace('    ? spC;\n    s32 sp8;', '    s16 spC[24];\n    s32 sp8;')
s = re.sub(r'\*\(&spC \+ \(\(\((\w+) - 1\) \* 6\) \+ \(\((\w+) - 1\) \* 2\)\)\)', r'spC[(\1 - 1) * 3 + (\2 - 1)]', s)
s = re.sub(r'\*\(m \+ \(\(\((\w+) - 1\) \* 6\) \+ \(\((\w+) - 1\) \* 2\) \+ 0xC84\)\)', r'm->tileA[(\1 - 1) * 3 + (\2 - 1)]', s)
s = re.sub(r'\*\(m \+ \(\(\((\w+) - 1\) \* 6\) \+ \(\((\w+) - 1\) \* 2\) \+ 0xCB4\)\)', r'm->tileB[(\1 - 1) * 3 + (\2 - 1)]', s)

s = re.sub(r'\*\(side \+ \(\(side->nrow \* 0xA\) \+ \(side->ncol \* 2\) \+ 0xC\)\)', 'side->grid[side->nrow][side->ncol]', s)
s = re.sub(r'\*\(grid \+ (\(.*?\))\) = ', r'*(s16 *) ((u8 *) grid + \1) = ', s)
s = re.sub(r'\(m \+ \(var_r25 \* 0xA\) \+ \(var_r26 \* 2\)\)->unk1D0 = \(s16\) \(m \+ \(var_r25 \* 0xA\) \+ \(var_r26 \* 2\)\)->unk1C;',
           '((s16 *) m->side[1].grid)[var_r25 * 5 + var_r26] = ((s16 *) m->side[0].grid)[var_r25 * 5 + var_r26];', s)
s = s.replace('    sp8[0] = lbl_1_rodata_1F8.unk0;\n    sp8[1] = lbl_1_rodata_1F8.unk2;\n', '')
s = re.sub(r'mat->unkE = ', 'mat->color[0] = ', s)
s = re.sub(r'mat->unkF = ', 'mat->color[1] = ', s)
s = re.sub(r'mat->unk10 = ', 'mat->color[2] = ', s)

# stack copies of rodata tables, byte-offset grid reads
for sp, tb in [('sp8', '224'), ('sp28', '204'), ('sp48', '244')]:
    s = re.sub(r'\*\(&' + sp + r' \+ \(\((\w+(?:->\w+)?) \* 0x10\) \+ \((\w+(?:->\w+)?) \* 4\)\)\)', r'lbl_1_rodata_' + tb + r'[\1][\2]', s)
s = s.replace('*(lbl_1_data_254 + (var_r31 * 0x18))', 'lbl_1_data_254[var_r31 * 6]')
def _bytes(name, ty):
    global s
    key = '*(%s + (' % name
    out = ''; i = 0
    while True:
        j = s.find(key, i)
        if j < 0: break
        k = j + len(key) - 1; d = 0; e = k
        while True:
            if s[e] == '(': d += 1
            elif s[e] == ')':
                d -= 1
                if d == 0: break
            e += 1
        out += s[i:j] + '*(%s *) ((u8 *) %s + %s)' % (ty, name, s[k:e + 1])
        i = e + 2
    s = out + s[i:]
_bytes('grid', 's16'); _bytes('temp_r24', 's16')

# MP5 runs the sequence's init hook only after the player objects' first update; here it starts at once
in_fn('fn_1_3758', '    obj->func = fn_1_3908;', '    m567Ready++;\n    obj->func = fn_1_3908;')
in_fn('fn_1_1FC', '    temp_r31 = lbl_1_bss_4->data;\n', '    temp_r31 = lbl_1_bss_4->data;\n    if (m567Ready < 4) {\n        return;\n    }\n')
s = s.replace('    lbl_1_bss_8 = omInitObjMan(0xA, 0x2000);', '    m567Ready = 0;\n    lbl_1_bss_8 = omInitObjMan(0xA, 0x2000);')

# GC HsfMaterial is 0x3C bytes: m2c's pointer math is in bytes
s = re.sub(r'(hsf->material) \+ (0x[0-9A-F]+);', lambda m: '%s + %d;' % (m.group(1), int(m.group(2), 16) // 0x3C), s)

for a, b in [('0xE0', 'side[0].slot.blink[0]'), ('0xE8', 'side[0].slot.blink[1]'), ('0x294', 'side[1].slot.blink[0]'),
             ('0x29C', 'side[1].slot.blink[1]'), ('0x2A4', 'side[1].slot.blink[2]')]:
    s = s.replace('fn_1_98F0, temp_r31 + %s);' % a, 'fn_1_98F0, &temp_r31->%s);' % b)

# per-character tables are in MP5 character order
s = re.sub(r'(m->side\[\d\]\.ply\[\w+\])->charNo \+ (0x1E|0x2B)\]', r'Mp5CharNo(\1->charNo) + \2]', s)
s = s.replace('lbl_1_data_28[temp_r31->charNo]', 'lbl_1_data_28[Mp5CharNo(temp_r31->charNo)]')

# MP5 shows frame 0 of the motion on a model paused at once (0x40000002); MP4 never evaluates a model that was paused
# before its first update (T-pose): pause it two frames after the motion was set instead.
in_fn('fn_1_3758', '    CharModelAttrSet(temp_r31->charNo, 0x40000002U);\n', '    obj->work[1] = 0;\n')
in_fn('fn_1_3908', '    temp_r31 = obj->data;\n', '    temp_r31 = obj->data;\n    if (obj->work[1] < 3 && ++obj->work[1] == 3) {\n        Hu3DMotionTimeSet(*obj->model, 0.0f);\n        CharModelAttrSet(temp_r31->charNo, 0x40000002U);\n    }\n')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
