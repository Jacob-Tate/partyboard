"""Hand fixes for the m528 (Mario Can-Can) draft; run by m528dll.sh on build/mp5/m528Dll.c."""
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

# ---- teams: MP5 reads GWPlayerCfg .group (0/1) as the team; MP4's numbering differs (see m533): a team is the
# rank of the player by (group, player), halved (--minigame: P1+P2 = team 0, P3+P4 = team 1)
s = re.sub(r'GWPlayerCfg\[([^\[\]]+)\]\.group\b', r'Mp5TeamNo(\1)', s)
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
# MP5 character tables are in MP5's order
s = s.replace('lbl_1_data_28[temp_r31->unk2A]', 'lbl_1_data_28[Mp5CharNo(temp_r31->unk2A)]')
# work objects: sizes of the 64-bit structs
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x5C, MEMORY_DEFAULT_NUM)', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M528Player), MEMORY_DEFAULT_NUM)')
# the 9th float argument of Hu3DCameraPosSet (target z) was lost by m2c
rep('0.0f, 150.0f, M2C_ERROR(/* Read from unset register $f9 */)', '0.0f, 150.0f, 0.0f')
# functions that take no arguments
s = re.sub(r'\b(fn_1_(?:16C4|15EC|17B0))\(\w+\)', r'\1()', s)
s = re.sub(r'\bMgSeqModeNext\([^;]*\);', 'MgSeqModeNext();', s)

# ---- raw offsets into the work struct (m2c lost the type of the pointer arithmetic)
HALF_X = None
TEAM = {0x3C: 'unk0', 0x7C: 'unk40', 0x80: 'unk44', 0x84: 'unk48.x', 0x88: 'unk48.y', 0x8C: 'unk48.z', 0x90: 'unk54',
        0x94: 'unk58', 0x98: 'unk5C', 0x9C: 'unk60', 0x9E: 'unk62', 0xA2: 'unk66'}
HALF = {0x0: 'unk0', 0x4: 'unk4', 0x8: 'unk8', 0xC: 'unkC', 0x10: 'unk10', 0x14: 'unk14', 0x1A: 'unk1A', 0x1C: 'unk1C'}
def team_f(m):
    return '%s->unk3C[%s].%s' % (m.group(1), m.group(2), TEAM[int(m.group(3), 16)])
def half_f(m):
    return '%s->unk3C[%s].unk0[%s].%s' % (m.group(1), m.group(2), m.group(3), HALF[int(m.group(4), 16) - 0x3C])
E = r'([^()]+?)'
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 0x68\) \+ \(%s << 5\) \+ 0x([0-9A-F]+)\)\)' % (E, E), half_f, s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 0x68\) \+ 0x([0-9A-F]+)\)\)' % E, team_f, s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 8\) \+ \(%s \* 4\) \+ 0x10\)\)' % (E, E), r'\1->unk10[\2][\3]', s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 8\) \+ 0x10\)\)' % E, r'\1->unk10[\2][0]', s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 8\) \+ 0x14\)\)' % E, r'\1->unk10[\2][1]', s)
s = re.sub(r'\*\((\w+) \+ \(%s \* 4\)\)' % E, r'\1->unk0[\2]', s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 0x38\) \+ 0x13E4 \+ 0x(30|36)\)\)' % E, lambda m: '%s->unk13E4[%s].unk%s' % (m.group(1), m.group(2), m.group(3)), s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 0x38\) \+ 0x1416\)\)' % E, r'\1->unk13E4[\2].unk32', s)
s = re.sub(r'\*\((\w+) \+ \(\(%s \* 0x38\) \+ 0x1418\)\)' % E, r'\1->unk13E4[\2].unk34', s)
s = re.sub(r'\((\w+) \+ 0xA4\)', r'(&\1->unk3C[1])', s)
s = re.sub(r'\((\w+) \+ \(\((\w+) \* 0x68\) \+ 0x3C\)', r'(&\1->unk3C[\2]', s)
for i, off in enumerate((0x4C10, 0x4C3C, 0x4C68), 1):
    s = s.replace('(temp_r31 + 0x%X)' % off, '(&temp_r31->unk4BE4[%d])' % i)
s = s.replace('(&temp_r31->unk3C[1])', '(&temp_r31->unk3C[1])')
s = re.sub(r'fn_1_2EC0\(temp_r31 \+ 0xA4\)', 'fn_1_2EC0(&temp_r31->unk3C[1])', s)
s = re.sub(r'fn_1_B6D4\(temp_r31 \+ 0x(4C10|4C3C|4C68)\)',
           lambda m: 'fn_1_B6D4(&temp_r31->unk4BE4[%d])' % {'4C10': 1, '4C3C': 2, '4C68': 3}[m.group(1)], s)
rep('temp_r31->unk58 = (void *) (temp_r28 + ((temp_r31->unk2C * 0x68) + (temp_r29 << 5) + 0x3C));',
    'temp_r31->unk58 = &temp_r28->unk3C[temp_r31->unk2C].unk0[temp_r29];')
rep('*(temp_r31 + (((temp_r31->unk4CB0 ^ 1) * 0x68) + 0x9E)) = 0;', 'temp_r31->unk3C[temp_r31->unk4CB0 ^ 1].unk62 = 0;')
rep('if (*(temp_r31 + (temp_r4 + 0x3D0))(&temp_r31->unk3C[temp_r29], temp_r4) != 0) {', 'if (temp_r31->unk3D0[temp_r29](&temp_r31->unk3C[temp_r29]) != 0) {')
rep('((? (*)(void *)) temp_r31->unk1C)', '((s32 (*)(M528Player *)) temp_r31->unk1C)')
# untyped pointers of the draft
in_fn('fn_1_238', 'void *temp_r29;', 'M528Player *temp_r29;')
in_fn('fn_1_954', 'omObjData *temp_r3;', 'M528Slice *temp_r3;')
in_fn('fn_1_ED0', r'void \*(temp_r30(?:_\d)?);', r'M528Player *\1;', True)
in_fn('fn_1_1CAC', 'void *temp_r31;', 'M528Player *temp_r31;')
in_fn('fn_1_3330', 'void *temp_r31;', 'M528Player *temp_r31;')
# fn_1_B6D4 walks the points of lbl_1_bss_4 (pointer arithmetic in bytes: +0xC is the next point)
s = s.replace('*rail = *lbl_1_bss_4;', 'rail->unk0 = lbl_1_bss_4[0];')
in_fn('fn_1_B6D4', r'\((temp_r\d+(?:_\d+)?) \+ 0xC\)->', r'\1[1].', True)
in_fn('fn_1_B6D4', r'= (temp_r\d+(?:_\d+)?) \+ 0xC;', r'= \1 + 1;', True)
in_fn('fn_1_B6D4', r'\b(temp_r\d+(?:_\d+)?)->unkC\b', r'\1[1].x', True)
# m2c lost the temporary of the shuffle swaps
s = s.replace('M2C_SWAP(sp8[temp_r28], sp8[temp_r3]); /* m2c lost the temporary */',
              '{ s32 swapTmp = sp8[temp_r28]; sp8[temp_r28] = sp8[temp_r3]; sp8[temp_r3] = swapTmp; }')
in_fn('fn_1_C728', 's32 sp8[4];', 's32 sp8[0x18];')
in_fn('fn_1_C8B4', 's32 sp8[4];', 's32 sp8[0x18];')
# the effect started for the winning slice: MP5 copied the table of functions to the stack
s = re.sub(r'\n    (?:s32 sp28\[8\]|void \(\*sp28\[\d\]\)\(M528Work \*\));', '', s)
s = re.sub(r'\n    sp28\[\d\] = lbl_1_rodata_78(?:->unk0|\[\d\]);', '', s)
s = s.replace('sp28[', 'lbl_1_rodata_78[')
s = s.replace('(u32) (temp_r31->unk0[var_r30])->unk1C == fn_1_1F8C', '(temp_r31->unk0[var_r30])->unk1C == fn_1_1F8C')
# tables read through "&spN + bytes" (the draft's stack copies are separate locals): index the rodata tables
for fn, t8, t28 in (('fn_1_27AC', '150', '130'), ('fn_1_2A00', '190', '170')):
    in_fn(fn, r'\*\(&sp8 \+ \(\((\w+) \* 0x10\) \+ \(p->unk36 \* 4\)\)\)', r'lbl_1_rodata_%s[\1 * 4 + p->unk36]' % t8, True)
    in_fn(fn, r'\*\(&sp28 \+ \(\((\w+) \* 0x10\) \+ \(p->unk36 \* 4\)\)\)', r'lbl_1_rodata_%s[\1 * 4 + p->unk36]' % t28, True)
s = s.replace('*(&sp8 + ((var_r30 * 4) + (var_r29 * 2)))', 'lbl_1_rodata_108[var_r30 * 2 + var_r29]')
s = s.replace('(u32) temp_r31->unk3D0[temp_r29] != 0U', 'temp_r31->unk3D0[temp_r29] != NULL')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
