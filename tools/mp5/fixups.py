"""Structural clean-ups of m2c output (run by decomp.py after m2c, before port.py).

Everything here fixes how m2c *prints* code, not what the code does. Anything it can't settle is left
in place with a `TODO(mp5)` comment; grep for those and for `M2C_` / `?` after a run.

Hints read from the --types header (plain C comments, one per line):
  // objdata: TypeName                 default type of `obj->data` work pointers
  // objdata fn_1_123 fn_1_456: Other  per-function override
  // particlework: TypeName              element type of HU3DPARTICLE::work arrays
"""
import re

GC_SIZE = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 'float': 4, 'Vec': 12, 'HuVecF': 12}

# HU3DPARTICLE / HU3DPARTICLEDATA: identical layouts in MP4 and MP5
PARTICLE = {'unk0': 'dataCnt', 'unk2': 'emitCnt', 'unk4': 'pos.x', 'unk8': 'pos.y', 'unkC': 'pos.z',
            'unk1C': 'work', 'unk20': 'animBank', 'unk22': 'animNo', 'unk2C': 'blendMode', 'unk2D': 'attr',
            'unk30': 'maxCnt', 'unk34': 'count', 'unk44': 'anim', 'unk48': 'data'}
PARTICLE_DATA = {'unk0': 'time', 'unk2': 'parManId', 'unk4': 'unk04', 'unk6': 'cameraBit', 'unk8': 'vel.x',
                 'unkC': 'vel.y', 'unk10': 'vel.z', 'unk14': 'accel.x', 'unk18': 'accel.y', 'unk1C': 'accel.z',
                 'unk20': 'speedDecay', 'unk24': 'colorIdx', 'unk28': 'scaleBase', 'unk2C': 'scale',
                 'unk30': 'zRot', 'unk34': 'pos.x', 'unk38': 'pos.y', 'unk3C': 'pos.z', 'unk40': 'color.r',
                 'unk41': 'color.g', 'unk42': 'color.b', 'unk43': 'color.a'}
FN_START = re.compile(r'(?m)^(?=[A-Za-z_][^\n;=]*\b\w+\([^\n;]*\) \{$)')


def split_functions(code):
    """[(name or None, text)]: top-level chunks, each function on its own."""
    out = []
    for part in FN_START.split(code):
        m = re.match(r'[^\n(]*?\b(\w+)\([^\n]*\) \{\n', part)
        if m:
            end = re.search(r'(?m)^\}\n?', part)
            out.append((m.group(1), part[:end.end()]))
            if part[end.end():]:
                out.append((None, part[end.end():]))
        else:
            out.append((None, part))
    return out


def join(chunks):
    return ''.join(t for _, t in chunks)


def unused_functions(asm):
    fns = re.findall(r'^\.fn (\w+),', asm, re.M)
    dead = []
    for f in fns:
        refs = len(re.findall(r'\b%s\b' % re.escape(f), asm)) - 2  # .fn + .endfn
        if refs <= 0 and f not in ('ObjectSetup',):
            dead.append(f)
    return set(dead) | {'_prolog', '_epilog'}


def parse_types(path):
    hints = {'objdata': None, 'objdata_fn': {}, 'arrays2d': {}, 'arrays1d': {}, 'particlework': None, 'layouts': {}}
    if not path:
        return hints
    s = open(path, encoding='utf-8').read()
    hints['layouts'] = struct_layouts(s)
    for m in re.finditer(r'^extern (\w+) (\w+)\[(\w+)\];', s, re.M):
        if m.group(1) in GC_SIZE:
            hints['arrays1d'][m.group(2)] = GC_SIZE[m.group(1)]
    for m in re.finditer(r'^//\s*objdata((?: \w+)*):\s*(\w+)', s, re.M):
        if m.group(1).strip():
            for f in m.group(1).split():
                hints['objdata_fn'][f] = m.group(2)
        else:
            hints['objdata'] = m.group(2)
    m = re.search(r'^//\s*particlework:\s*(\w+)', s, re.M)
    if m:
        hints['particlework'] = m.group(1)
    for m in re.finditer(r'^extern (\w+) (\w+)\[(\w+)\]\[(\w+)\];', s, re.M):
        if m.group(1) in GC_SIZE:
            hints['arrays2d'][m.group(2)] = (GC_SIZE[m.group(1)], int(m.group(3), 0), int(m.group(4), 0))
    return hints


def struct_layouts(s):
    """{struct: [(offset, elemsize, count, name)]} for the --types header's typedef structs (GC layout)."""
    sizes = dict(GC_SIZE)
    layouts = {}
    for m in re.finditer(r'typedef struct \w* ?\{(.*?)\} (\w+);', s, re.S):
        off, fields = 0, []
        for line in m.group(1).split('\n'):
            line = re.sub(r'//.*', '', line).strip()
            fm = re.match(r'(?:struct )?(\w+)\s*(\*?)\s*(.+);$', line)
            if not fm:
                continue
            esz = 4 if fm.group(2) else sizes.get(fm.group(1))
            if esz is None:
                break
            for decl in fm.group(3).split(','):
                dm = re.match(r'\s*\*?\s*(\w+)\s*(?:\[(\w+)\])?', decl)
                cnt = int(dm.group(2), 0) if dm.group(2) else 1
                sz = 4 if decl.strip().startswith('*') else esz
                al = min(sz, 4) if sz in (1, 2, 4) else 4
                off = (off + al - 1) // al * al
                fields.append((off, sz, cnt, dm.group(1)))
                off += sz * cnt
        else:
            sizes[m.group(2)] = (off + 3) // 4 * 4
            layouts[m.group(2)] = fields
    return layouts


def fix_struct_arrays(body, layouts):
    for t, fields in layouts.items():
        arrays = [f for f in fields if f[2] > 1]
        if not arrays:
            continue
        for v in set(re.findall(r'\b%s \*(\w+);' % t, body)):
            for off, sz, cnt, name in arrays:
                for k in range(cnt):
                    body = re.sub(r'\b%s->unk%X\b(?!\[)' % (v, off + k * sz), '%s->%s[%d]' % (v, name, k), body)
                body = re.sub(r'\b%s->%s\b(?!\[)' % (v, name), '%s->%s[0]' % (v, name), body)
                body = re.sub(r'\*\(%s \+ \(\((\w+) \* %d\) \+ 0x%X\)\)' % (v, sz, off),
                              lambda m: '%s->%s[%s]' % (v, name, m.group(1)), body)
    return body


def fix_2d(code, name, size, rows, cols):
    """m2c prints flattened scalar 2D arrays as a[x].unkH / (*a)[x] / a[x]: byte offset x*size + H."""
    stride = size * cols

    def idx(x, off):
        if off % size:
            return None
        row, col = off // stride, (off % stride) // size
        try:
            v = int(x, 0) + col
            return '%s[%d][%d]' % (name, row + v // cols, v % cols)
        except ValueError:
            return '%s[%d][%s]' % (name, row, x if col == 0 else '%s + %d' % (x, col))

    def sub(m):
        off = int(m.group(3), 16) if m.group(3) else 0
        r = idx(m.group(2).strip(), off)
        return r if r else m.group(0)

    n = re.escape(name)
    code = re.sub(r'(\(\*%s\)|\b%s)\[([^\[\]]+)\](?!\[)(?:\.unk([0-9A-F]+))?' % (n, n), sub, code)
    # *(a + (i * stride) + (j * size))
    code = re.sub(r'\*\(%s \+ \((\w+) \* %s\) \+ \((\w+) \* %d\)\)' % (n, hex(stride).upper().replace('0X', '0x'), size),
                  r'%s[\1][\2]' % name, code)
    code = re.sub(r'\*\(%s \+ \((\w+) \* %d\) \+ \((\w+) \* %d\)\)' % (n, stride, size), r'%s[\1][\2]' % name, code)
    return code


def fix_particle_work(body, t):
    for v in set(re.findall(r'(\w+) = \w+->work;', body)):
        body = re.sub(r'\b(?:void|HU3DPARTICLE|M2C_UNK) \*%s;' % v, '%s *%s;' % (t, v), body)
        body = re.sub(r'\*\(%s \+ \(\((\w+) \* 0x[0-9A-F]+\) \+ (0x[0-9A-F]+|\d+)\)\)' % v,
                      lambda m: '%s[%s].unk%X' % (v, m.group(1), int(m.group(2), 0)), body)
        body = re.sub(r'\*\(%s \+ \((\w+) \* 0x[0-9A-F]+\)\)' % v, lambda m: '%s[%s].unk0' % (v, m.group(1)), body)
    body = re.sub(r'M2C_STRUCT_COPY\((\w+)->work \+ \((\w+) \* 0x[0-9A-F]+\), (\w+), 0x[0-9A-F]+\);',
                  lambda m: '((%s *)%s->work)[%s] = *%s;' % (t, m.group(1), m.group(2), m.group(3)), body)
    return body


def fix_particles(name, body):
    parts = set(re.findall(r'(\w+) = Hu3DData\[[^;\n]*\]\.hookData;', body))
    if re.search(r'HU3DPARTICLE \*particleP', body):
        parts.add('particleP')
    if not parts:
        return body
    datas = set()
    for p in parts:
        body = re.sub(r'\b(?:void|M2C_UNK) \*%s;' % p, 'HU3DPARTICLE *%s;' % p, body)
        datas |= set(re.findall(r'(\w+) = %s->(?:data|unk48)\b' % p, body))
        body = re.sub(r'\b%s->(unk[0-9A-F]+)\b' % p, lambda m: '%s->%s' % (p, PARTICLE.get(m.group(1), m.group(1))), body)
    datas |= set(re.findall(r'HU3DPARTICLEDATA \*(\w+);', body))
    for d in datas:
        body = re.sub(r'\b(?:void|M2C_UNK|s32) \*%s;' % d, 'HU3DPARTICLEDATA *%s;' % d, body)
        body = body.replace('%s += 0x44;' % d, '%s++;' % d)
        body = re.sub(r'\b%s->(unk[0-9A-F]+)\b' % d, lambda m: '%s->%s' % (d, PARTICLE_DATA.get(m.group(1), m.group(1))), body)
    body = re.sub(r'->data \+ \((\w+)->emitCnt \* 0x44\)', r'->data + \1->emitCnt', body)
    body = re.sub(r'->maxCnt \* 0x44\b', '->maxCnt * sizeof(HU3DPARTICLEDATA)', body)
    return body


def fix_objdata(name, body, hints):
    t = hints['objdata_fn'].get(name, hints['objdata'])
    if not t:
        return body
    for v in set(re.findall(r'(\w+) = [^;\n]*->data;', body)):
        body = re.sub(r'\bvoid \*%s;' % v, '%s *%s;' % (t, v), body)
    body = re.sub(r'((?:\w+|\w+\[[^\]]+\]))->data->', r'((%s *)\1->data)->' % t, body)
    return body


def stack_arrays(name, body, objtype=None):
    """`(&sp18[0])[i]` / `(&sp14)[i]` with neighbours sp1C, sp20.. -> one array sp18[n]."""
    bases = sorted(set(re.findall(r'\(&(sp[0-9A-F]+)(?:\[0\])?\)\[', body)), key=lambda b: int(b[2:], 16))
    starts = [int(b[2:], 16) for b in bases]
    for b in bases:
        decl = re.search(r'^    ([\w ]+?\**) ?%s;\n' % b, body, re.M)
        if decl:
            t = decl.group(1).strip()
        else:  # m2c didn't declare it: guess from use
            if re.search(r'\(&%s\[0\]\)\[[^\]]+\] = [^;]*->data;' % b, body):
                t = (objtype + ' *') if objtype else 'void *'
            elif re.search(r'\(&%s\[0\]\)\[[^\]]+\] = (?:-?[\d.]+f|[^;]*->unk\w+);|\b%s\[0\] == -?[\d.]+f' % (b, b), body) \
                    and not re.search(r'\(&%s\[0\]\)\[[^\]]+\] = \((?:s16|s32|u16|u8)\)' % b, body):
                t = 'f32'
            elif re.search(r'\(&%s\[0\]\)\[[^\]]+\] = \(s16\)' % b, body):
                t = 's16'
            else:
                t = 's32'
        size = 4 if t.endswith('*') else GC_SIZE.get(t, 4)
        base = int(b[2:], 16)
        used = {int(x, 16) for x in re.findall(r'\bsp([0-9A-F]+)\b', body)}
        n, off = 1, base + size
        while off in used and off not in starts:
            n, off = n + 1, off + size
        n = max(n, 4) if not decl else n
        for k in range(1, n):
            nm = 'sp%X' % (base + k * size)
            body = re.sub(r'^    [\w ]+?\**\s?%s;\n' % nm, '', body, flags=re.M)
            body = re.sub(r'\b%s\b(?!\[)' % nm, '%s[%d]' % (b, k), body)
        body = re.sub(r'\(&%s(?:\[0\])?\)\[' % b, '%s[' % b, body)
        body = re.sub(r'\b%s\b(?!\[)' % b, '%s[0]' % b, body)
        arr = '    %s%s%s[%d];\n' % (t, '' if t.endswith('*') else ' ', b, n)
        if decl:
            body = re.sub(r'^    [\w ]+?\**\s?%s\[0\];\n' % b, arr, body, count=1, flags=re.M)
        else:
            body = re.sub(r'(\) \{\n)', r'\1' + arr, body, count=1)
    return body


def jumptable_else(body):
    """m2c puts the cases of a jump table that share the out-of-range target in the `else` of the bounds
    check, as bare case labels. Move them into the switch (and keep the body for the else)."""
    pat = re.compile(r'(\n(\s*)\}\n)(\s*)\} else \{\n((?:\s*case [^\n]+:\n)+)((?:(?!\s*case )[^\n]*\n)*?)\3\}\n')

    def sub(m):
        ind = m.group(2)
        cases = ''.join('%s%s\n' % (ind, c.strip()) for c in m.group(4).strip('\n').split('\n'))
        stmts = [l.strip() for l in m.group(5).strip('\n').split('\n') if l.strip()]
        inner = ''.join('%s    %s\n' % (ind, l) for l in stmts)
        outer = ''.join('%s    %s\n' % (m.group(3), l) for l in stmts)
        return '\n%s%s%s    break;\n%s}\n%s} else {\n%s%s}\n' % (cases, inner, ind, ind, m.group(3), outer, m.group(3))

    return pat.sub(sub, body)


def struct_copies(body):
    # partial copy + last field (8 bytes then z) of a Vec
    body = re.sub(r'M2C_STRUCT_COPY\((&?[\w.\[\]>-]+), (&?[\w.\[\]>-]+), 8\);\n\s*(?:\1->|\1\.)?\S*z = [^;]+;',
                  lambda m: '%s = %s;' % (deref(m.group(1)), deref(m.group(2))), body)
    body = re.sub(r'M2C_STRUCT_COPY\((&?[\w.\[\]>-]+), (&?[\w.\[\]>-]+), 0x[0-9A-F]+\);',
                  lambda m: '%s = %s;' % (deref(m.group(1)), deref(m.group(2))), body)
    return body


def deref(x):
    return x[1:] if x.startswith('&') else '*' + x


def run(code, asm, types_path):
    hints = parse_types(types_path)
    dead = unused_functions(asm)
    chunks = []
    for name, text in split_functions(code):
        if name in dead:
            continue
        if name:
            text = re.sub(r', \? arg_sp0\)', ')', text)
            text = text.replace('(? arg_sp0)', '(void)')
            text = fix_particles(name, text)
            if hints['particlework']:
                text = fix_particle_work(text, hints['particlework'])
            text = text.replace('f32 (*mtx)[4]', 'Mtx mtx')
            text = fix_objdata(name, text, hints)
            text = fix_struct_arrays(text, hints['layouts'])
            text = stack_arrays(name, text, hints['objdata_fn'].get(name, hints['objdata']))
            text = jumptable_else(text)
            text = struct_copies(text)
            text = re.sub(r'\bHuPrcVSleep\([^)]+\)', 'HuPrcVSleep()', text)
            # OMOBJ model/motion are s16 arrays
            text = re.sub(r'->(mdlId|mtnId)->unk([0-9A-F]+)\b', lambda m: '->%s[%d]' % (m.group(1), int(m.group(2), 16) // 2), text)
            text = re.sub(r'\bsaved_reg_\w+\b', '0 /* TODO(mp5): uninitialised in the original */', text)
            text = re.sub(r'(\(&\w+\[[^\]]+\] \+ \(\w+ \* 0x[0-9A-F]+\)\))', r'\1 /* TODO(mp5): byte offset */', text)
            text = re.sub(r'^(\s*\w+ \+= 0x[0-9A-F]+;)$', r'\1 /* TODO(mp5): byte step? */', text, flags=re.M)
        chunks.append((name, text))
    code = join(chunks)
    for arr, (size, rows, cols) in hints['arrays2d'].items():
        n = re.escape(arr)
        code = fix_2d(code, arr, size, rows, cols)
        # p = &a[0][x]; p->unkH = ...  (pointer into the array, then a byte offset)
        code = re.sub(r'(\w+) = &%s\[0\]\[([^\[\]]+)\];\n(\s*)\1->unk([0-9A-F]+) = ' % n,
                      lambda m: '%s%s[%d][%s] = ' % (m.group(3), arr, int(m.group(4), 16) // (size * cols), m.group(2)), code)
        code = re.sub(r'(\w+) = &%s\[([^\[\]]+)\];\n(\s*)\1->unk([0-9A-F]+) = ' % n,
                      lambda m: '%s%s[%d][%s] = ' % (m.group(3), arr, int(m.group(4), 16) // (size * cols), m.group(2)), code)
    for arr, size in hints['arrays1d'].items():
        code = re.sub(r'\b%s->unk([0-9A-F]+)\b' % re.escape(arr), lambda m: '%s[%d]' % (arr, int(m.group(1), 16) // size), code)
    # globals m2c re-declares for the loader / inlined strings
    code = re.sub(r'^extern \? \(\*_[cd]tors\)\(\);\n', '', code, flags=re.M)
    for m in list(re.finditer(r'^static s8 (lbl_\w+)\[0x[0-9A-F]+\] = ".*";\n', code, re.M)):
        if len(re.findall(r'\b%s\b' % m.group(1), code)) == 1:
            code = code.replace(m.group(0), '')
    code = re.sub(r'^void ObjectSetup\(\);[^\n]*\n', '', code, flags=re.M)
    # globals only the dropped (unused) functions touched
    for m in list(re.finditer(r'^(?:static )?[\w?][\w ?]*\*? ?(lbl_\w+)(?:\[[^\]]*\])*;[^\n]*\n', code, re.M)):
        if len(re.findall(r'\b%s\b' % m.group(1), code)) == 1:
            code = code.replace(m.group(0), '')
    return code
