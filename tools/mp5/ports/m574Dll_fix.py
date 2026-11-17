"""Hand fixes for the m574 draft; run by m574Dll.sh on build/mp5/m574Dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

s = re.sub(r'(?ms)^struct _struct_lbl_1_bss_\w+ \{.*?\n\};[^\n]*\n\n', '', s)
# team of a player: MP5 reads GWPlayerCfg .group (0/1); the launcher/MP4 numbering differs (see m533): a team is
# the rank of the player by (group, player) halved
s = re.sub(r'GWPlayerCfg\[([^\[\]]+)\]\.group', r'Mp5TeamNo(\1)', s)
rep('void ObjectSetup(void) {', '''static s16 Mp5TeamNo(s16 player)
{
    s16 i, slot = 0;
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].group < GWPlayerCfg[player].group || (GWPlayerCfg[i].group == GWPlayerCfg[player].group && i < player)) {
            slot++;
        }
    }
    return slot / 2;
}

void ObjectSetup(void) {''')

# ---- typed replacements of m2c's byte arithmetic ----------------------------------------------------------
STAGE = [(0xA8, 0x50, 'unkA8'), (0x1E8, 0x5C, 'unk1E8'), (0x2A0, 0x88, 'unk2A0'), (0x3B0, 0x88, 'unk3B0'),
         (0xB20, 0x88, 'unkB20'), (0xE50, 0x88, 'unkE50')]
SB = r'((?:\w+|\w+->data))'

def stage_elem(base, idx, stride, off):
    c = [(a, st, name) for a, st, name in STAGE if st == stride and a <= off]
    a, st, name = max(c)
    return '((M574Stage *)%s)->%s[%s]' % (base, name, idx), off - a

def stage_sub(m):
    base, idx, stride, off = m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16)
    e, sub = stage_elem(base, idx, stride, off)
    assert e, m.group(0)
    return '%s.unk%X' % (e, sub)

# *(base + ((i * 0xS) + 0xO))  -> stage array element field;  (base + ((i * 0xS) + 0xO))->unkN -> same
s = re.sub(r'\*\(' + SB + r' \+ \(\((\w+) \* 0x([0-9A-F]+)\) \+ 0x([0-9A-F]+)\)\)', stage_sub, s)
s = re.sub(r'\(' + SB + r' \+ \(\((\w+) \* 0x([0-9A-F]+)\) \+ 0x([0-9A-F]+)\)\)->', lambda m: stage_elem(m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16))[0] + '.', s)
# pointer to a stage element: X = base + ((i * 0xS) + 0xO);  or  &base->data...
s = re.sub(r'(?m)^(\s+\w+) = ' + SB + r' \+ \(\((\w+) \* 0x([0-9A-F]+)\) \+ 0x([0-9A-F]+)\);',
           lambda m: '%s = &%s%s;' % (m.group(1), *(lambda e: (e[0], '' if e[1] == 0 else '.unk%X' % e[1]))(stage_elem(m.group(2), m.group(3), int(m.group(4), 16), int(m.group(5), 16)))), s)
s = re.sub(r'\(' + SB + r' \+ \(\((\w+) \* 0x([0-9A-F]+)\) \+ 0x([0-9A-F]+)\)\)', lambda m: '(&' + stage_elem(m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16))[0] + ')', s)
# *(p + (i * 4)) and *(p + ((i * 4) + 0xO)): array member unk<O>
s = re.sub(r'\*\((\w+) \+ \((\w+) \* 4\)\)', r'\1->unk0[\2]', s)
s = re.sub(r'\*\((\w+) \+ \(\((\w+) \* 4\) \+ 0x([0-9A-F]+)\)\)', r'\1->unk\3[\2]', s)

# X = base + (i * 0xS): cast to X's declared type
def fn_of(pos):
    st = [m for m in re.finditer(r'(?m)^[\w *]+ \w+\([^)]*\) \{\n', s[:pos])][-1]
    return st.start()
def bytestep(m):
    x = m.group(1).strip()
    st = fn_of(m.start())
    d = re.search(r'(?m)^    ([\w ]+?) \*%s;' % re.escape(x), s[st:m.start()])
    assert d, x
    return '%s%s = (%s *)((u8 *)%s + %s * 0x%s);' % (m.group(1)[:len(m.group(1)) - len(x)], x, d.group(1), m.group(2), m.group(3), m.group(4))
s = re.sub(r'(?m)^(\s+\w+) = ((?:\w+->data)|\w+) \+ \((\w+) \* 0x([0-9A-F]+)\);', bytestep, s)

# m2c lost the 16-bit mask of MP5's frand16-style random numbers (clrlwi 16): frand() is 32-bit here
s = s.replace('(f32) (frand() - 0x8000)', '(f32) ((s32) (frand() & 0xFFFF) - 0x8000)').replace('(f32) frand()', '(f32) (frand() & 0xFFFF)')

# a ball is 0x6C on GC but its M574Hit holds pointers: stride by the real size
s = s.replace('* 0x6C)', '* sizeof(M574Ball))')

# ---- hand fixes ----------------------------------------------------------------------------------------------
def fn_span(name):
    m = re.search(r'(?m)^[\w *]+ %s\([^)]*\) \{\n' % name, s)
    assert m, name
    return m.start(), s.index('\n}\n', m.end()) + 3

def set_fn(name, text):
    global s
    a, b = fn_span(name)
    s = s[:a] + text.strip('\n') + '\n' + s[b:]

def in_fn(name, a, b):
    global s
    st, en = fn_span(name)
    body = s[st:en]
    assert a in body, (name, a)
    s = s[:st] + body.replace(a, b) + s[en:]

s = s.replace('((? (*)(', '((s32 (*)(')
set_fn('fn_1_6B38', """
s32 fn_1_6B38(M574Ball *arg0) {
    if (arg0->unk18.x < -170.0f) {
        return 0;
    }
    if (arg0->unk18.x > 170.0f) {
        return 0;
    }
    if (arg0->unk18.y < 598.0f) {
        return 0;
    }
    if (arg0->unk18.y > 817.0f) {
        return 0;
    }
    return 1;
}
""")
set_fn('fn_1_6BD4', """
void fn_1_6BD4(M574Ball *arg0) {
    Hu3DModelPosSetV(arg0->unk14, &arg0->unk18);
    arg0->unk3C.unk20 = arg0->unk18.x;
    arg0->unk3C.unk24 = arg0->unk18.y;
    arg0->unk3C.unk28 = arg0->unk18.z;
}
""")
s = s.replace('s32 fn_1_6B38(void *arg0);', 's32 fn_1_6B38(M574Ball *arg0);').replace('void fn_1_6BD4(void *arg0);', 'void fn_1_6BD4(M574Ball *arg0);')
s = s.replace('temp_r31->unk18 = temp_r30 + 0x18;', 'temp_r31->unk18 = &temp_r30->unk18;').replace('temp_r31->unk1C = temp_r30 + 0x24;', 'temp_r31->unk1C = &temp_r30->unk24;')
s = s.replace('return temp_r31 + 0x3C;', 'return &temp_r31->unk3C;')
in_fn('fn_1_7AE4', 'if ((temp_r26_2 != NULL) && (((s32 (*)(s32)) temp_r26_2->unk14) != NULL)) {\n            temp_r26_2->unk14(temp_r26_2->unk10);',
      'if ((temp_r26_2 != NULL) && (temp_r26_2->unk14 != NULL)) {\n            ((void (*)(void *)) temp_r26_2->unk14)(temp_r26_2->unk10);')
# float class checks: "is not NaN"
s = re.sub(r'(?s)        spC = sp10\.x;\n        temp_r3 = \(bitwise s32\) spC.*?        if \(var_r26 != 1\) \{\n            sp8 = sp10\.y;.*?            if \(var_r25 != 1\) \{\n(.*?)\n            \}\n        \}\n',
           lambda m: '', s) if False else s

# float class switches (NaN checks) of the reflection
a = s.index('                        spC = sp10.x;\n')
m = '                            if (var_r25 != 1) {\n'
b = s.index(m, a) + len(m)
s = s[:a] + '                        if (!isnan(sp10.x)) {\n                            if (!isnan(sp10.y)) {\n' + s[b:]
set_fn('fn_1_8AD0', """
s32 fn_1_8AD0(M574Hit *hit) {
    s32 i;
    M574Reg *reg = lbl_1_bss_60->data;

    for (i = 0; i < 0x52; i++) {
        if (reg->unk0[i] == NULL) {
            reg->unk0[i] = hit;
            return i;
        }
    }
    return -1;
}
""")
set_fn('fn_1_8B48', """
s32 fn_1_8B48(M574Circle *hit) {
    s32 i;
    M574Reg *reg = lbl_1_bss_60->data;

    for (i = 0; i < 0x14; i++) {
        if (reg->unk148[i] == NULL) {
            reg->unk148[i] = hit;
            return i + 0x52;
        }
    }
    return -1;
}
""")
set_fn('fn_1_8C94', """
void fn_1_8C94(M574Mesh *mesh, HSFOBJECT *objs, s32 count) {
    HSFOBJECT *obj;
    HSFTRANSFORM **tp;
    Mtx *mtx;
    M574Seg *seg;
    s32 total = 0;
    s32 i, f, k;

    for (i = 0, obj = objs; i < count; i++, obj++) {
        if (obj->type == 2) {
            HSFFACE *face = obj->mesh.face->data;
            for (f = 0; f < obj->mesh.face->count; f++) {
                if (face[f].type == 3) {
                    total++;
                }
            }
        }
    }
    seg = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Seg), MEMORY_DEFAULT_NUM);
    mesh->unk28 = seg;
    memset(seg, 0, total * sizeof(M574Seg));
    mesh->unk20 = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Line), MEMORY_DEFAULT_NUM);
    memset(mesh->unk20, 0, total * sizeof(M574Line));
    mesh->unk24 = HuMemDirectMallocNum(HEAP_SYSTEM, total * sizeof(M574Line), MEMORY_DEFAULT_NUM);
    memset(mesh->unk24, 0, total * sizeof(M574Line));
    mesh->unk2C = count;
    tp = HuMemDirectMallocNum(HEAP_SYSTEM, count * sizeof(HSFTRANSFORM *), MEMORY_DEFAULT_NUM);
    mesh->unk30 = tp;
    memset(tp, 0, count * sizeof(HSFTRANSFORM *));
    mtx = HuMemDirectMallocNum(HEAP_SYSTEM, count * sizeof(Mtx), MEMORY_DEFAULT_NUM);
    mesh->unk34 = mtx;
    memset(mtx, 0, count * sizeof(Mtx));
    mesh->unk1C = 0;
    for (i = 0, obj = objs; i < count; i++, obj++) {
        if (obj->type == 2) {
            Vec *vtx = obj->mesh.vertex->data;
            HSFFACE *face = obj->mesh.face->data;
            for (f = 0; f < obj->mesh.face->count; f++) {
                if (face[f].type == 3) {
                    for (k = 0; k < 4; k++) {
                        Vec *a = &vtx[face[f].indices[lbl_1_data_5D8[k]][0]];
                        Vec *b = &vtx[face[f].indices[lbl_1_data_5D8[(k + 1) & 3]][0]];
                        if ((a->z > -50.0f) && (b->z > -50.0f)) {
                            seg->unk0 = a->x;
                            seg->unk4 = a->y;
                            seg->unkC = b->x;
                            seg->unk10 = b->y;
                            seg->unk18 = mtx;
                            seg++;
                            mesh->unk1C += 1;
                            break;
                        }
                    }
                }
            }
        }
        *tp++ = &obj->mesh.base;
        mtx++;
    }
}
""")
in_fn('fn_1_8FDC', 'void *var_r26;', 'Mtx *var_r26;')
in_fn('fn_1_8FDC', 'MTXConcat(sp8, sp38, (f32 (*)[4]) var_r26);', 'MTXConcat(sp8, sp38, *var_r26);')
in_fn('fn_1_8FDC', 'var_r30 += 4;', 'var_r30++;')
in_fn('fn_1_8FDC', 'var_r26 += 0x30; /* TODO(mp5): byte step? */', 'var_r26++;')
s = s.replace('(f64) (bitwise f32) *__float_nan', '(f64) NAN').replace('(f64) (bitwise f32) *__float_huge', '(f64) HUGE_VAL')
s = re.sub(r'(lbl_1_data_(?:290|2D8|31C|3A8|3D0))\[0\]\[([^\]]+)\]', r'\1[\2]', s)
# `ptr + 0xOFF` on a typed pointer = address of the member at that offset
def addr_of(m):
    name, off = m.group(1), m.group(2)
    st = fn_of(m.start())
    d = re.search(r'(?m)^    M574\w+ \*%s;' % re.escape(name), s[st:m.start()])
    if not d:
        return m.group(0)
    return '&%s->unk%s' % (name, off)
s = re.sub(r'\b(\w+) \+ 0x([0-9A-F]+)\b', addr_of, s)
s = re.sub(r'\((\w+)->data \+ 0x14\)', r'(&((M574Stage *)\1->data)->unk14)', s)
s = re.sub(r'(?m)(\w+) = arg0->data \+ 0x14;', r'\1 = &((M574Stage *)arg0->data)->unk14;', s)
s = re.sub(r'->unk1C->unk0\b', '->unk1C->x', s)
s = re.sub(r'->unk1C->unk4\b', '->unk1C->y', s)
s = re.sub(r'->unk1C->unk8\b', '->unk1C->z', s)
s = s.replace('*(lbl_1_bss_58->data + (arg0 * 0x1C))', '((M574Score *)lbl_1_bss_58->data)->unk0[arg0].unk0')
s = s.replace('*(temp_r31 + (var_r30 * 0x1C))', 'temp_r31->unk0[var_r30].unk0')
in_fn('fn_1_26F4', 'temp_r4 = var_r31 * 4;\n', '')
in_fn('fn_1_26F4', 'temp_r0 = *(temp_r30 + temp_r4) - 1;', 'temp_r0 = temp_r30->unk0[var_r31] - 1;')
in_fn('fn_1_26F4', '*(temp_r30 + temp_r4) = temp_r0;', 'temp_r30->unk0[var_r31] = temp_r0;')
in_fn('fn_1_3A1C', 'temp_r4 = (var_r30_2 * 4) + 0x38;\n', '')
in_fn('fn_1_3A1C', '*(temp_r31 + temp_r4) = *(temp_r31 + temp_r4) + temp_r31->unk44[var_r30_2];', 'temp_r31->unk38[var_r30_2] = temp_r31->unk38[var_r30_2] + temp_r31->unk44[var_r30_2];')
s = re.sub(r'->unk18->unk0\b', '->unk18->x', s)
s = re.sub(r'->unk18->unk4\b', '->unk18->y', s)
in_fn('fn_1_3A1C', 'void *temp_r25;', 'HSFOBJECT *temp_r25;')
in_fn('fn_1_3A1C', 'temp_r25->unk28 =', 'temp_r25->mesh.base.rot.x =')
in_fn('fn_1_4660', 'temp_r30->unk1C =', 'temp_r30->mesh.base.pos.x =')
in_fn('fn_1_4660', 'temp_r30->unk20 =', 'temp_r30->mesh.base.pos.y =')
in_fn('fn_1_5934', 'temp_r29->unk1C =', 'temp_r29->mesh.base.pos.x =')
in_fn('fn_1_5934', 'temp_r29->unk20 =', 'temp_r29->mesh.base.pos.y =')
in_fn('fn_1_47DC', 's32 *temp_r26;', 'M574Prop *temp_r26;')
in_fn('fn_1_47DC', 'temp_r26 = temp_r19 + (((var_r29 + (var_r21 * 7)) * 0x88) + 0x3B0);', 'temp_r26 = &temp_r19->unk3B0[var_r29 + (var_r21 * 7)];')
in_fn('fn_1_47DC', '(s32) *temp_r26 == 0', 'temp_r26->unk0 == 0')
in_fn('fn_1_47DC', '*temp_r26 += 1;', 'temp_r26->unk0 += 1;')
in_fn('fn_1_47DC', 'fn_1_5680(temp_r26 + 0x10);', 'fn_1_5680(&temp_r26->unk10);')
in_fn('fn_1_4EE8', 'temp_r26 = arg0->data + (temp_r3 + 0x1E8);', 'temp_r26 = &((M574Stage *)arg0->data)->unk1E8[var_r29].unk0;')
in_fn('fn_1_4EE8', 'MgSeqModeGet((s32 *) temp_r3)', 'MgSeqModeGet()')
in_fn('fn_1_4EE8', 'temp_r3 = var_r29 * 0x5C;\n', '')
s = s.replace('(lbl_1_bss_48->data + ((self->unk8 * 0x88) + 0xE50))->unk38', '((M574Stage *)lbl_1_bss_48->data)->unkE50[self->unk8].unk38')
s = s.replace('*(lbl_1_bss_48->data + (((4 - count) * 2) + 0x9C))', '((M574Stage *)lbl_1_bss_48->data)->unk9C[4 - count]')
in_fn('fn_1_4660', 'void *temp_r30;', 'HSFOBJECT *temp_r30;')
in_fn('fn_1_5934', 'void *temp_r29;', 'HSFOBJECT *temp_r29;')
for sz, t in (('0x21C0', 'M574Balls'), ('0x198', 'M574Reg'), ('0x4C', 'M574Score'), ('0x108C', 'M574Stage')):
    nl = chr(10)
    rep('sizeof(M574Seg), MEMORY_DEFAULT_NUM);' + nl + '    temp_r3->data = temp_r3_2;' + nl + '    memset(temp_r3_2, 0, %s);' % sz,
        'sizeof(%s), MEMORY_DEFAULT_NUM);' % t + nl + '    temp_r3->data = temp_r3_2;' + nl + '    memset(temp_r3_2, 0, sizeof(%s));' % t)
s = 'static double __frsqrte(double x)' + chr(10) + '{' + chr(10) + '    return 1.0 / sqrt(x);' + chr(10) + '}' + chr(10) + chr(10) + s  # MWCC inlined sqrtf (Newton steps on frsqrte)
# C_VECReflect isn't exported by dol.dll (it would pull aurora_mtx into the link): the Dolphin routine
REFL = ['static void Mp5VecReflect(Vec *src, Vec *normal, Vec *dst)', '{', '    Vec uI;', '    f32 cosA;', '',
        '    uI.x = -src->x;', '    uI.y = -src->y;', '    uI.z = -src->z;', '    VECNormalize(&uI, &uI);',
        '    cosA = VECDotProduct(&uI, normal);', '    dst->x = 2.0f * normal->x * cosA - uI.x;',
        '    dst->y = 2.0f * normal->y * cosA - uI.y;', '    dst->z = 2.0f * normal->z * cosA - uI.z;', '}', '', '']
s = chr(10).join(REFL) + s
s = s.replace('C_VECReflect(', 'Mp5VecReflect(')
open(p, 'w', encoding='utf-8').write(s)
