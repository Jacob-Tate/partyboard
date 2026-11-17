"""Hand fixes for the m506 draft; run by m506Dll.sh on build/mp5/m506Dll.c."""
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


# ---- rodata the draft lost (m2c gives a zeroed struct): the tables the code copies to the stack ----------
def table(name, decl):
    global s
    pat = re.compile(r'static struct \{ // TODO\(mp5\): synthesized from the symbol size\n(?:    [^\n]*\n)*?\} %s;\n' % name)
    assert pat.search(s), name
    s = pat.sub(lambda m: decl + '\n', s, count=1)


table('lbl_1_rodata_18', 'static const f32 lbl_1_rodata_18[4] = { 90.0f, 170.0f, 390.0f, 470.0f };')
table('lbl_1_rodata_28', 'static const f32 lbl_1_rodata_28[4] = { 200.0f, 280.0f, 500.0f, 580.0f };')
table('lbl_1_rodata_25C', 'static const f32 lbl_1_rodata_25C[2] = { -64.5f, 64.5f };')
table('lbl_1_rodata_280', 'static const s16 lbl_1_rodata_280[4] = { 0x28, 0x38, 0x48, 0x58 };')
table('lbl_1_rodata_338', 'static const f32 lbl_1_rodata_338[3] = { 144.0f, 288.0f, 432.0f };')
table('rotTbl_700', 'static const f32 rotTbl_700[6] = { 0.0f, 90.0f, 15.0f, 30.0f, 10.0f, 45.0f };')
for i in range(4):
    s = s.replace('lbl_1_rodata_18.unk%X' % (i * 4), 'lbl_1_rodata_18[%d]' % i)
    s = s.replace('lbl_1_rodata_28.unk%X' % (i * 4), 'lbl_1_rodata_28[%d]' % i)
for i in range(2):
    s = s.replace('lbl_1_rodata_25C.unk%X' % (i * 4), 'lbl_1_rodata_25C[%d]' % i)
for i in range(3):
    s = s.replace('lbl_1_rodata_338.unk%X' % (i * 4), 'lbl_1_rodata_338[%d]' % i)
for i in range(4):
    s = s.replace('lbl_1_rodata_280.unk%X' % (i * 2), 'lbl_1_rodata_280[%d]' % i)
for i, n in enumerate(['unk0', 'unk4', 'unk8', 'unkC', 'unk10', 'unk14']):
    s = s.replace('rotTbl_700.%s' % n, 'rotTbl_700[%d]' % i)

# ---- byte offsets into the big M506_WORK -> its fields -------------------------------------------------
# (name, GC offset, element size, dims)
WORK = [('stageMdlId', 0, 2, ()), ('bgMdlId', 2, 2, (2,)), ('mameMdlId', 6, 2, (4, 60)), ('mameVineMdlId', 0x1E6, 2, (4, 31)),
        ('mameSmallMdlId', 0x2DE, 2, (4, 10)), ('mameSpiralMdlId', 0x32E, 2, (4, 10)), ('kumoMdlId', 0x37E, 2, (4,)),
        ('starMdlId', 0x38E, 2, (2,)), ('starfighterMdlId', 0x398, 2, (4,)), ('kumo2MdlId', 0x3A4, 2, (4,)),
        ('smokeMdlId', 0x3AC, 2, (3,)), ('mameShadowMdlId', 0x3B2, 2, (4,)), ('mameShadowTexScrId', 0x3C4, 2, (4,)),
        ('mameSide', 0x3CC, 1, (4, 60)), ('mameSmallFlag', 0x4BC, 1, (4, 10)), ('mameSpiralFlag', 0x4E4, 1, (4, 10)),
        ('mameVinePosY', 0x50C, 4, (4,)), ('mameVineRotY', 0x51C, 4, (4,)), ('mameVineTime', 0x52C, 2, (4,)),
        ('mameEnterTime', 0x534, 2, (4,)), ('unk53C', 0x53C, 2, (4,)), ('mameMissTime', 0x544, 2, (4,)),
        ('mameSpiralPosY', 0x54C, 4, (4, 10)), ('mameSmallPosY', 0x5EC, 4, (4, 10)),
        ('mameSpiralTime', 0x68C, 2, (4, 10)), ('mameSmallTime', 0x6DC, 2, (4, 10)),
        ('kumoDir', 0x72C, 4, (4,)), ('kumoPosX', 0x73C, 4, (4,)), ('kumoAngle', 0x74C, 4, (4,)), ('starTime', 0x75C, 2, (2,))]


def prod(t):
    r = 1
    for x in t:
        r *= x
    return r


def split_top(e, sep):
    out, depth, cur, i = [], 0, '', 0
    while i < len(e):
        c = e[i]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
        if depth == 0 and e.startswith(sep, i):
            out.append(cur); cur = ''; i += len(sep); continue
        cur += c; i += 1
    out.append(cur)
    return out


def unwrap(e):
    e = e.strip()
    while e.startswith('(') and e.endswith(')') and len(split_top(e[1:-1], ' + ')) >= 1:
        # only if the outer parens match each other
        d = 0
        ok = True
        for k, c in enumerate(e):
            d += (c == '(') - (c == ')')
            if d == 0 and k < len(e) - 1:
                ok = False; break
        if not ok:
            break
        e = e[1:-1].strip()
    return e


def num(t):
    try:
        return int(t, 0)
    except ValueError:
        return None


def work_field(expr):
    """expr = byte offset (m2c) into M506_WORK -> 'field[i][j]' or None"""
    const, idx = 0, []
    for t in split_top(unwrap(expr), ' + '):
        t = unwrap(t)
        n = num(t)
        if n is not None:
            const += n
            continue
        m = re.match(r'^(.*) \* (0x[0-9A-F]+|\d+)$', t)
        if m and num(m.group(2)) is not None:
            idx.append((unwrap(m.group(1)), num(m.group(2))))
        else:
            idx.append((t, 1))
    for name, off, esz, dims in WORK:
        total = esz * (prod(dims) if dims else 1)
        lo = off - (1 if name == 'mameSide' else 0)  # mameSide is also read at -1 (the 0x3CB accesses)
        if not (lo <= const < off + total):
            continue
        rem = const - off
        if rem % esz:
            continue
        units = [esz * prod(dims[k + 1:]) for k in range(len(dims))]
        sub = [None] * len(dims)
        ok = True
        for e, st in idx:
            k = [i for i, u in enumerate(units) if u == st and sub[i] is None]
            if not k:
                ok = False
                break
            sub[k[0]] = e
        if not ok:
            continue
        extra = rem // esz
        if not dims:
            if idx or extra:
                continue
            return name
        if extra:
            last = len(dims) - 1
            sub[last] = ('%s %s %d' % (sub[last], '+' if extra > 0 else '-', abs(extra))) if sub[last] is not None else str(extra)
        return name + ''.join('[%s]' % (x if x is not None else '0') for x in sub)
    return None


def fix_work_access(fn_name):
    """In fn_name: `*(V + (offset expr))` / `(V + (offset expr))->unkXXX` on an M506_WORK V -> V->field[...]"""
    global s
    st, en = fn_span(fn_name)
    body = s[st:en]
    # offset temps computed once and used twice: temp = expr; *(V + temp) = *(V + temp) + x;
    for m in list(re.finditer(r'(?m)^( *)(temp_r\d+(?:_\d+)?) = ([^;\n]*0x[0-9A-F]+\)?);\n', body)):
        t, e = m.group(2), m.group(3)
        if re.search(r'\*\(\w[\w>.\-]* \+ %s\)' % t, body):
            body = body.replace(m.group(0), '')
            body = re.sub(r'\(([\w>.\-]+) \+ %s\)' % t, lambda mm: '(%s + (%s))' % (mm.group(1), e), body)
    # player pointers used as ints in the offsets (*sp50[x], *temp_r23): their first field is `no`
    body = re.sub(r'\*(sp50\[\w+\])(?=\s)', r'\1->no', body)
    pv = set(re.findall(r'M506_PLAYER_WORK \*(\w+)', body))
    for v in pv:
        body = re.sub(r'\(\*%s(?= \*)' % v, '(%s->no' % v, body)
    def sub(m):
        f = work_field(m.group(2))
        return '%s->%s' % (m.group(1), f) if f else m.group(0)
    var = r'(\w[\w>.\-]*?)'
    body = re.sub(r'\*\(' + var + r' \+ (\(.*?\)|\w+)\)(?=[ ,;)\]])', lambda m: (lambda f: ('%s->%s' % (m.group(1), f)) if f else m.group(0))(work_field(m.group(2))), body)
    s = s[:st] + body + s[en:]


# an M506_WORK that came out as `void *` / `s32`
for fn in ['M506Create', 'M506MameVineScrollUp', 'M506MameIn', 'M506MameSpiralIn', 'M506MameSmallIn',
           'M506MameUpdate', 'M506MameModeEnter', 'M506MameModeMiss', 'M506MameModeJump', 'M506ModelUpdate',
           'M506ObjShadowMapSet', 'M506ObjShadowMapReset', 'M506KumoUpdate', 'M506StarUpdate', 'M506FlowMameSetup',
           'M506StarfighterStart', 'M506StarfighterUpdate', 'M506FlowModeEndSetup', 'M506FlowModeStart',
           'M506MameShadowOff', 'M506MameShadowOn', 'M506MameShadowScrollOn', 'M506PlayerInputRead',
           'M506ComInputDelayGet', 'M506ComInputCheck']:
    try:
        st, en = fn_span(fn)
    except AssertionError:
        continue
    body = s[st:en]
    for v in set(re.findall(r'\b(\w+) = M506MainObj->data\b', body)):
        body = re.sub(r'\bvoid \*%s;' % v, 'M506_WORK *%s;' % v, body)
    for v in set(re.findall(r'\b(\w+) = sp50\[', body)):
        body = re.sub(r'\bvoid \*%s;' % v, 'M506_PLAYER_WORK *%s;' % v, body)
    s = s[:st] + body + s[en:]
    fix_work_access(fn)
    s = s.replace('M506MainObj->data->', '((M506_WORK *) M506MainObj->data)->')

# mameSide bytes read at +1/+2 (the next entries of a 3-step) and -1
def side_sub(m):
    k = {'B': -1, 'D': 1, 'E': 2}[m.group(4)]
    return '%s->mameSide[%s][%s %s %d]' % (m.group(1), m.group(2), m.group(3), '+' if k > 0 else '-', abs(k))
s = re.sub(r'\(([\w>.\-]+) \+ \(([\w>.\-]+) \* 0x3C\) \+ ([\w>.\-\[\]]+)\)->unk3C([BDE])', side_sub, s)
s = re.sub(r'\(([\w>.\-]+) \+ ([\w>.\-]+) \* 0x3C \+ ([\w>.\-\[\]]+)\)->unk3C([BDE])', side_sub, s)
s = re.sub(r'\((\w+) \+ (work)\)->unk3C([DE])', lambda m: 'work->mameSide[0][%s + %d]' % (m.group(1), {'D': 1, 'E': 2}[m.group(3)]), s)

# ---- hand fixes -------------------------------------------------------------------------------------------
rep('*ComMaxDelayTbl[0][temp_r31->comDif]', 'ComMaxDelayTbl[temp_r31->comDif][0]', 2)
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x60, MEMORY_DEFAULT_NUM)', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M506_PLAYER_WORK), MEMORY_DEFAULT_NUM)')
rep('M506TimerCreate((M506_WORK *) temp_r29);', 'M506TimerCreate(temp_r29);')
s = re.sub(r'OSReport\(("M506Y\w+ Error\.\.\.\\n"), [^;]*\);', r'OSReport(\1);', s)
rep('M506CameraBit->unk0', 'M506CameraBit[0]')
s = s.replace('M506YLightUpdate(M506YLight);', 'M506YLightUpdate();')
s = s.replace('M506YLight->unk0', 'M506YLight->lightId')
# ScorePos[i * 3]: x/y of the player's score
rep('((f32) *(ScorePos + (var_r30 * 0xC)) - 20.0f) - 8.0f, 12.0f + (f32) (ScorePos + (var_r30 * 0xC))->unk2',
    '((f32) ScorePos[var_r30 * 3].x - 20.0f) - 8.0f, 12.0f + (f32) ScorePos[var_r30 * 3].y')
# FlowModeEndSetup: the winners table lives on the stack
in_fn('M506FlowModeEndSetup', r'\*\(&sp8 \+ (\w+)\)', r'winner[\1]', regex=True)
in_fn('M506FlowModeEndSetup', '    ? sp8;\n', '    s8 winner[4];\n')
in_fn('M506FlowModeEndSetup', 'spC[(flow->work + (var_r31_11 * 0x3C) + (s8) (u8) flow->score[var_r31_11])->unk3CB]',
      'spC[flow->work->mameSide[var_r31_11][(s8) (u8) flow->score[var_r31_11] - 1]]')
in_fn('M506FlowUpdate', 'u32 *temp_r30;', 'uintptr_t *temp_r30;')
in_fn('M506ModelUpdate', r'\*sp50\[(\w+)\]', r'sp50[\1]->no', regex=True)
in_fn('M506ModelUpdate', 'sp50[var_r29]->unk18', 'sp50[var_r29]->height')
in_fn('M506ModelUpdate', 'M506_PLAYER_WORK sp50[4]->no;', 'M506_PLAYER_WORK *sp50[4];')
# the seed particles start (time 1) all at once
in_fn('M506SeedUpdate', 's16 *var_r30;', 'HU3DPARTICLEDATA *var_r30;')
in_fn('M506SeedUpdate', '*var_r30 = 1;', 'var_r30->time = 1;')

# per-character tables are in MP5's character order
s = s.replace('PlayerMotionTbl[temp_r31->charNo]', 'PlayerMotionTbl[Mp5CharNo(temp_r31->charNo)]')
s = s.replace('CharFallFXTbl[temp_r31->charNo]', 'CharFallFXTbl[Mp5CharNo(temp_r31->charNo)]')
s = s.replace('LookUpRotTbl[flow->player[0]->charNo]', 'LookUpRotTbl[Mp5CharNo(flow->player[0]->charNo)]')
s = s.replace('LookUpRotLockFlag[flow->player[0]->charNo]', 'LookUpRotLockFlag[Mp5CharNo(flow->player[0]->charNo)]')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
