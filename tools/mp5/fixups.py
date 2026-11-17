"""Structural clean-ups of m2c output (run by decomp.py after m2c, before port.py).

Everything here fixes how m2c *prints* code, not what the code does. Anything it can't settle is left
in place with a `TODO(mp5)` comment; grep for those and for `M2C_` / `?` after a run.

Hints read from the --types header (plain C comments, one per line):
  // objdata: TypeName                 default type of `obj->data` work pointers
  // objdata fn_1_123 fn_1_456: Other  per-function override
  // particlework: TypeName              element type of HU3DPARTICLE::work arrays
"""
import re

GC_SIZE = {'char': 1, 's8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 'float': 4, 'Vec': 12, 'HuVecF': 12}

# HU3DPARTICLE / HU3DPARTICLEDATA: identical layouts in MP4 and MP5
PARTICLE = {'unk0': 'dataCnt', 'unk2': 'emitCnt', 'unk4': 'pos.x', 'unk8': 'pos.y', 'unkC': 'pos.z',
            'unk1C': 'work', 'unk20': 'animBank', 'unk22': 'animNo', 'unk2C': 'blendMode', 'unk2D': 'attr',
            'unk30': 'maxCnt', 'unk34': 'count', 'unk44': 'anim', 'unk48': 'data'}
PARTICLE_DATA = {'unk0': 'time', 'unk2': 'parManId', 'unk4': 'unk04', 'unk6': 'cameraBit', 'unk8': 'vel.x',
                 'unkC': 'vel.y', 'unk10': 'vel.z', 'unk14': 'accel.x', 'unk18': 'accel.y', 'unk1C': 'accel.z',
                 'unk20': 'speedDecay', 'unk24': 'colorIdx', 'unk28': 'scaleBase', 'unk2C': 'scale',
                 'unk30': 'zRot', 'unk34': 'pos.x', 'unk38': 'pos.y', 'unk3C': 'pos.z', 'unk40': 'color.r',
                 'unk41': 'color.g', 'unk42': 'color.b', 'unk43': 'color.a'}
# GameCube sizes of engine structs MP5 code walks with pointer arithmetic
ENGINE_GC_SIZE = {'HSFMATERIAL': 0x3C}

# MP5's OMOBJ (GC layout), so `// var fn v: OMOBJ` hints resolve raw offsets (->unk48->unkE = ->mtnId[7])
OMOBJ_LAYOUT = """typedef struct {
    u16 stat;
    s16 objNext, prio, prev, next, nextNo, grpNo;
    u16 memberNo;
    u32 mode;
    u32 func;
    Vec trans, rot, scale;
    u16 mdlcnt;
    s16 *mdlId;
    u16 mtncnt;
    s16 *mtnId;
    u32 work[4];
    void *data;
} OMOBJ;
"""
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
    """Functions nothing references, then (repeatedly) those only dead functions reference."""
    bodies = dict(re.findall(r'^\.fn (\w+),[^\n]*\n(.*?)^\.endfn', asm, re.M | re.S))
    outside = re.sub(r'^\.fn \w+,[^\n]*\n.*?^\.endfn[^\n]*\n', '', asm, flags=re.M | re.S)
    # a function's name in a string (OSReport("MgFlowSet : ...")) is not a reference
    outside = re.sub(r'^\s*\.string [^\n]*\n', '', outside, flags=re.M)
    dead = {'_prolog', '_epilog'}
    while True:
        new = set()
        for f in bodies:
            if f in dead or f == 'ObjectSetup':
                continue
            pat = re.compile(r'\b%s\b' % re.escape(f))
            live_refs = sum(len(pat.findall(b)) for g, b in bodies.items() if g not in dead and g != f)
            if live_refs == 0 and not pat.search(outside):
                new.add(f)
        if not new:
            return dead
        dead |= new


def parse_types(path):
    hints = {'globals': {}, 'objdata': None, 'objdata_fn': {}, 'arrays2d': {}, 'arrays1d': {}, 'particlework': None, 'layouts': {}, 'vars': {}, 'ptrarrays2d': {}}
    if not path:
        return hints
    s = open(path, encoding='utf-8').read()
    hints['layouts'] = struct_layouts(OMOBJ_LAYOUT + s)
    hints['globals'] = {g: t for t, g in re.findall(r'^extern (\w+) (\w+);', s, re.M) if t in hints['layouts']}
    hints['objexpr'] = dict(re.findall(r'^//\s*objexpr (\w+):\s*(\w+)', s, re.M))
    hints['statics'] = dict(re.findall(r'^//\s*static (\w+):\s*(.+?)\s*$', s, re.M))
    for m in re.finditer(r'^//\s*var (\w+) (\w+):\s*(\w+)', s, re.M):
        hints['vars'].setdefault(m.group(1), {})[m.group(2)] = m.group(3)
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
    for m in re.finditer(r'^extern (\w+) ?(\*?) ?(\w+)\[(\w+)\]\[(\w+)\];', s, re.M):
        if m.group(1) in GC_SIZE or m.group(2):
            if m.group(2):
                hints['ptrarrays2d'][m.group(3)] = (int(m.group(4), 0), int(m.group(5), 0))
            else:
                hints['arrays2d'][m.group(3)] = (GC_SIZE[m.group(1)], int(m.group(4), 0), int(m.group(5), 0))
    for m in re.finditer(r'^extern \w+ ?\* ?(\w+)\[(\w+)\];', s, re.M):
        hints['arrays1d'][m.group(1)] = 4
    return hints


FIELD_TYPES = {}
FIELD_DIMS = {}  # (struct, field) -> [rows, cols] of 2-D array fields
STRUCT_SIZE = {}  # --types header struct -> GC size


def element_overflow(body):
    """p->f[i].unkOFF with f a `T *` field and OFF past T's GC size: m2c's byte offset for p->f[i + OFF / size]
    (T a --types struct or a scalar: s32 *tbl; tbl[i].unk3C = tbl[i + 15])."""
    seen = {}
    for (st, name), ft in FIELD_TYPES.items():
        if ft.endswith(' *'):  # (a scalar field of the same name can't be indexed)
            seen.setdefault(name, set()).add(ft)
    for (st, name), ft in FIELD_TYPES.items():
        if not ft.endswith(' *') or len(seen[name]) > 1:
            continue
        t = ft[:-2]
        size = STRUCT_SIZE.get(t) or GC_SIZE.get(t)
        if not size:
            continue

        def sub(m, t=t, size=size):
            off = int(m.group(3), 16)
            if t in STRUCT_SIZE and off < size:
                return m.group(0)
            if t not in STRUCT_SIZE and off % size:
                return m.group(0)
            idx = '%s + 0x%X' % (m.group(2), off // size) if off // size else m.group(2)
            if t in STRUCT_SIZE:
                return '%s[%s].unk%X' % (m.group(1), idx, off % size)
            return '%s[%s]' % (m.group(1), idx)
        body = re.sub(r'((?:->|\.)%s)\[([^\[\]]+)\]\.unk([0-9A-F]+)\b' % name, sub, body)
    return body


def memset_sizeof(code, types_src):
    """memset(g or a pointer global, 0, <GC size of its struct>) -> sizeof: the PC layout differs (pointers)."""
    for t, g in re.findall(r'^extern (\w+) ?\*? ?(\w+);', types_src, re.M):
        if t in STRUCT_SIZE:
            code = re.sub(r'(\bmemset\((?:\([^()]*\) )?&?%s, 0, )0x%X\)' % (re.escape(g), STRUCT_SIZE[t]),
                          r'\1sizeof(%s))' % t, code)
    return code


def field_2d(code, globs, layouts):
    """(&g + (i * rowbytes) + (j * elem))->unkOFF on a typed global whose 2-D array field starts at OFF:
    m2c's byte arithmetic for g.f[i][j]."""
    for g, t in globs.items():
        for off, sz, cnt, name in layouts.get(t, []):
            dims = FIELD_DIMS.get((t, name))
            if not dims:
                continue
            pat = r'\(&%s \+ \((.+?) \* (?:0x%X|%d)\) \+ \((.+?) \* %d\)\)->unk%X\b' % (
                re.escape(g), sz * dims[1], sz * dims[1], sz, off)
            code = re.sub(pat, lambda m: '%s.%s[%s][%s]' % (g, name, m.group(1), m.group(2)), code)
    return code


def field_path(t, off, layouts):
    """Field path at byte `off` of struct `t` (GC layout): 'unk8[2].unk0.y', or None."""
    if t in ('Vec', 'HuVecF', 'Point3d'):
        return {0: 'x', 4: 'y', 8: 'z'}.get(off)
    for foff, sz, cnt, name in layouts.get(t, []):
        if foff <= off < foff + sz * cnt:
            idx, rem = divmod(off - foff, sz)
            p = name + ('[%d]' % idx if cnt > 1 else '')
            ft = FIELD_TYPES.get((t, name), '')
            if ft.endswith('*'):
                return p if rem == 0 else None
            if ft in layouts or ft in ('Vec', 'HuVecF', 'Point3d'):
                sub = field_path(ft, rem, layouts)
                return p + '.' + sub if sub else None
            return p if rem == 0 else None
    return None


def resolve_fields(body, var, t, layouts):
    """Accesses m2c printed as raw offsets (var was void*) -> real field paths of t."""
    def sub(m):
        p = field_path(t, int(m.group(1), 16), layouts)
        return '%s->%s' % (var, p) if p else m.group(0)
    # (not ->unkN[ or ->unkN.: m2c already typed those, when a hint names a type it inferred itself)
    return re.sub(r'\b%s->unk([0-9A-F]+)\b(?![\[.])' % re.escape(var), sub, body)


def element_pointers(body, layouts):
    """`p = v + ((i * size) + off)` / `p = v + off` into a typed work struct -> `p = &v->field[i]`."""
    for t, fields in layouts.items():
        for v in set(re.findall(r'\b%s \*(\w+);' % t, body)):
            for off, sz, cnt, name in fields:
                if off:
                    body = re.sub(r'(?<![\w.>])%s \+ (?:0x%X|%d)(?=[,)])' % (v, off, off),
                                  '&%s->%s%s' % (v, name, '[0]' if cnt > 1 else ''), body)
            for off, sz, cnt, name in fields:
                et = FIELD_TYPES.get((t, name))
                if not et:
                    continue
                pat_i = r'^(    \s*)(\w+) = %s \+ \(\(\(?([^*;]+?)\)? \* (?:0x%X|%d)\) \+ (?:0x%X|%d)\);' % (v, sz, sz, off, off)
                pat_0 = r'^(    \s*)(\w+) = %s \+ (?:0x%X|%d);' % (v, off, off) if off else None
                for pat, idx in ((pat_i, True), (pat_0, False)):
                    if not pat:
                        continue
                    for m in list(re.finditer(pat, body, re.M)):
                        p = m.group(2)
                        rep = '%s%s = &%s->%s%s;' % (m.group(1), p, v, name, ('[%s]' % m.group(3)) if idx else ('[0]' if cnt > 1 else ''))
                        body = body.replace(m.group(0), rep)
                        body = re.sub(r'^(    )(?:void|M2C_UNK|\?|f32|s32) \*%s;$' % p, r'\g<1>%s *%s;' % (et, p), body, flags=re.M)
                        body = resolve_fields(body, p, et.rstrip(' *'), layouts)
    return body


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
            fp = re.match(r'\(\*(\w+)((?:\[\w+\])*)\)\(', fm.group(3))
            if fp:  # function pointer field: `ret (*name[N])(args);`
                dims = [int(x, 0) for x in re.findall(r'\[(\w+)\]', fp.group(2))]
                cnt = 1
                for x in dims:
                    cnt *= x
                off = (off + 3) // 4 * 4
                fields.append((off, 4, cnt, fp.group(1)))
                FIELD_TYPES[(m.group(2), fp.group(1))] = 'void *'
                off += 4 * cnt
                continue
            for decl in fm.group(3).split(','):
                dm = re.match(r'\s*\*?\s*(\w+)\s*((?:\[\w+\])*)', decl)
                dims = [int(x, 0) for x in re.findall(r'\[(\w+)\]', dm.group(2))]
                cnt = 1
                for x in dims:
                    cnt *= x
                if len(dims) == 2:
                    FIELD_DIMS[(m.group(2), dm.group(1))] = dims
                sz = 4 if decl.strip().startswith('*') else esz
                al = min(sz, 4) if sz in (1, 2, 4) else 4
                off = (off + al - 1) // al * al
                fields.append((off, sz, cnt, dm.group(1)))
                FIELD_TYPES[(m.group(2), dm.group(1))] = fm.group(1) + (' *' if fm.group(2) or decl.strip().startswith('*') else '')
                off += sz * cnt
        else:
            sizes[m.group(2)] = (off + 3) // 4 * 4
            STRUCT_SIZE[m.group(2)] = sizes[m.group(2)]
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
                body = re.sub(r'\*\(%s \+ \(\(\(?([^*;]+?)\)? \* %d\) \+ (?:0x%X|%d)\)\)' % (v, sz, off, off),
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
    layouts = hints['layouts']
    # objects whose ->data type is known from the expression (a global object or object table)
    for expr, t in hints.get('objexpr', {}).items():
        e = r'\b%s(?:\[(?:[^\[\]]|\[[^\]]*\])*\])?' % re.escape(expr)
        # first element of an object table: (*tbl)->data->unkN
        body = re.sub(r'\(\*(%s)\)->data->(unk[0-9A-F]+)\b' % re.escape(expr),
                      lambda m: '((%s *)%s[0]->data)->%s' % (t, m.group(1), field_path(t, int(m.group(2)[3:], 16), layouts) or m.group(2)), body)
        body = re.sub(r'(?<![\w)])\*(%s)->data\b' % e, lambda m: '((%s *)%s->data)->%s' % (t, m.group(1), layouts[t][0][3] if layouts.get(t) else 'unk0'), body)
        body = re.sub(r'(%s)->data->(unk[0-9A-F]+)\b' % e,
                      lambda m: '((%s *)%s->data)->%s' % (t, m.group(1), field_path(t, int(m.group(2)[3:], 16), layouts) or m.group(2)), body)
        for v in set(re.findall(r'(\w+) = %s->data;' % e, body)):
            body = re.sub(r'^(    )(?:void|M2C_UNK) \*%s;$' % v, r'\g<1>%s *%s;' % (t, v), body, flags=re.M)
            body = resolve_fields(body, v, t, layouts)
    t = hints['objdata_fn'].get(name, hints['objdata'])
    if not t:
        return body
    for v in set(re.findall(r'(\w+) = [^;\n]*->data;', body)):
        if re.search(r'^    void \*%s;$' % v, body, re.M):
            body = re.sub(r'\bvoid \*%s;' % v, '%s *%s;' % (t, v), body)
            body = resolve_fields(body, v, t, layouts)
    body = re.sub(r'((?:\w+|\w+\[[^\]]+\]))->data->(unk[0-9A-F]+)\b',
                  lambda m: '((%s *)%s->data)->%s' % (t, m.group(1), field_path(t, int(m.group(2)[3:], 16), layouts) or m.group(2)), body)
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


def pow2_mod(body):
    """MWCC's signed `x % 2^n`: S = x >> 31; R = (x << (32-n)) - S; ((R << n) | (R >> (32-n))) + S -> (x % 2^n)."""
    signs = {}
    for m in re.finditer(r'^\s*(\w+) = (?:\(u32\) )?([^\n;]+?) >> 0x1FU;\n', body, re.M):
        signs[m.group(1)] = m.group(2)
    for s, x in signs.items():
        for m in list(re.finditer(r'^(\s*)(\w+) = \(%s << (0x[0-9A-F]+)\) - %s;\n' % (re.escape(x), s), body, re.M)):
            r, k = m.group(2), int(m.group(3), 16)
            n = 32 - k
            pat = r'\(\(%s << %d\) \| \(%s >> 0x%XU\)\) \+ %s' % (r, n, r, k, s)
            body, cnt = re.subn(pat, '(%s %% %d)' % (x, 1 << n), body)
            if cnt and not re.search(r'\b%s\b' % r, body.replace(m.group(0), '')):
                body = body.replace(m.group(0), '')
    return body


def lost_swaps(body):
    """`a = b; b = a;` is m2c dropping the temporary of a swap (the old value stayed in a register)."""
    return re.sub(r'^(\s*)([^\n=;]+?) = ([^\n=;]+?);\n\s*\3 = \2;\n',
                  lambda m: '%sM2C_SWAP(%s, %s); /* m2c lost the temporary */\n' % (m.group(1), m.group(2), m.group(3)),
                  body, flags=re.M)


def hoist_bitwise_calls(body):
    """f(x, (bitwise f32) g(y)) -> g(y); f(x): m2c passing a previous call's result register along."""
    def sub(m):
        return '%s%s;\n%s%s%s' % (m.group(1), m.group(3), m.group(1), m.group(2), m.group(4))
    return re.sub(r'^(\s*)(.*?), \(bitwise f32\) (\w+\((?:[^()]|\([^()]*\))*\))(\).*)$', sub, body, flags=re.M)


def prototypes_from_definitions(code):
    """m2c's forward declarations (`/* static */`) come from call-site guesses; use the definitions'."""
    sigs = []
    for m in re.finditer(r'(?m)^([A-Za-z_][^\n;=]*?\b(\w+)\((.*)\)) \{$', code):
        if m.group(2) not in ('if', 'while', 'switch', 'for'):
            sigs.append(m.group(1) + ';')
    first = re.search(r'(?m)^[^\n]*/\* static \*/\n', code)
    code = re.sub(r'(?m)^[^\n]*/\* static \*/\n', '', code)
    pos = first.start() if first else 0
    return code[:pos] + '\n'.join(sigs) + '\n\n' + code[pos:]


def deref_work(body, layouts):
    """`*v` on a work-struct pointer means its first field; `*HuPrcCurrentGet()->property` an s32."""
    body = re.sub(r'(?:\(s32\) )?\*HuPrcCurrentGet\(\)->property\b', '*(s32 *)HuPrcCurrentGet()->property', body)
    for t, fields in layouts.items():
        if not fields:
            continue
        off, sz, cnt, name = fields[0]
        first = name + ('[0]' if cnt > 1 else '')
        for v in set(re.findall(r'\b%s \*(\w+);' % t, body)):
            body = re.sub(r'((?:[=(,!<>] |\(|\[|\) ))\*%s\b(?!\s*(?:\[|->|\+|=[^=]))' % v, lambda m: '%s%s->%s' % (m.group(1), v, first), body)
    return body


def malloc_sizeof(body, layouts):
    """Work allocations: sizeof(the struct) instead of the GameCube size (pointers are 8 bytes on PC, and
    some originals write past their allocation)."""
    for t, v in re.findall(r'^    (\w+) \*(\w+);$', body, re.M):
        if t in layouts:
            body = re.sub(r'\b%s = HuMemDirectMallocNum\((\w+), (?:0x[0-9A-F]+|\d+), ' % v,
                          lambda m: '%s = HuMemDirectMallocNum(%s, sizeof(%s), ' % (v, m.group(1), t), body)
    # obj->data = HuMemDirectMallocNum(h, 0x68, ...); ... v = obj->data; with v a T*
    for t, v in re.findall(r'^    (\w+) \*(\w+);$', body, re.M):
        if t not in layouts:
            continue
        for m in re.finditer(r'\b%s = (\w+)->data;' % v, body):
            body = re.sub(r'\b(%s->data = HuMemDirectMallocNum\(\w+, )(?:0x[0-9A-F]+|\d+)(, )' % re.escape(m.group(1)),
                          lambda mm: '%ssizeof(%s)%s' % (mm.group(1), t, mm.group(2)), body)
            body = re.sub(r'\bmemset\((%s->data), 0, (?:0x[0-9A-F]+|\d+)\)' % re.escape(m.group(1)),
                          lambda mm: 'memset(%s, 0, sizeof(%s))' % (mm.group(1), t), body)
    return body


def param_types(code):
    """{function: [param type, ...]} from the definitions in the draft."""
    out = {}
    for m in re.finditer(r'(?m)^[A-Za-z_][^\n;=]*?\b(\w+)\(([^\n]*)\) \{$', code):
        ps = [p.strip() for p in m.group(2).split(',')] if m.group(2).strip() not in ('', 'void') else []
        out[m.group(1)] = [re.sub(r'\s*\b\w+$', '', p) if not p.endswith(')') else p for p in ps]
    return out


def stack_vecs(body, ptypes):
    """`F(&sp8)` where F takes a Vec* / Mtx: sp8, spC, sp10 are one Vec (or Mtx), not scalars."""
    kinds = {}
    for m in re.finditer(r'\b(\w+)\(([^;\n]*)\)', body):
        pt = ptypes.get(m.group(1))
        if not pt:
            continue
        for i, arg in enumerate(a.strip() for a in m.group(2).split(',')):
            am = re.match(r'^(?:\(\w+ \*\) )?&(sp[0-9A-F]+)$', arg)
            if am and i < len(pt) and pt[i].replace(' ', '') in ('Vec*', 'HuVecF*', 'Point3d*'):
                kinds[am.group(1)] = 'Vec'
    # engine calls (Hu3DModelPosSetV, Hu3DShadowPosSet, ...): a float local passed as a Vec * starts a Vec
    for m in re.finditer(r'\((?:Vec|Point3d|HuVecF) \*\) &(sp[0-9A-F]+)\b(?!\[)', body):
        if re.search(r'^    f32 %s;$' % m.group(1), body, re.M):
            kinds[m.group(1)] = 'Vec'
    for m in re.finditer(r'\(f32 \(\*\)\[4\]\) &(sp[0-9A-F]+)\[0\]', body):
        kinds[m.group(1)] = 'Mtx'
    for b, kind in kinds.items():
        base = int(b[2:], 16)
        n = 3 if kind == 'Vec' else 12
        names = {}
        for k in range(n):
            nm = 'sp%X' % (base + 4 * k)
            names[nm] = ('%s.%s' % (b, 'xyz'[k])) if kind == 'Vec' else '%s[%d][%d]' % (b, k // 4, k % 4)
        for nm in names:
            body = re.sub(r'^    [\w ]+?\**\s?%s(?:\[[^\]]*\])?;\n' % nm, '', body, flags=re.M)
        body = re.sub(r'\(f32 \(\*\)\[4\]\) &%s\[0\]' % b, b, body)
        body = re.sub(r'\((?:\w+ \*)\) &%s\b' % b, '&' + b, body)
        for nm, rep in names.items():
            if kind == 'Mtx' and nm == b:
                continue
            body = re.sub(r'\(bitwise (?:f32|s32)\) %s\b' % nm, rep, body)
            body = re.sub(r'(?<![&\w])%s\b(?![\[.])' % nm, rep, body)
        if kind == 'Mtx':
            body = re.sub(r'\b%s\[(\d+)\](?!\[)' % b, lambda m: '%s[%d][%d]' % (b, int(m.group(1)) // 4, int(m.group(1)) % 4), body)
        body = re.sub(r'(\) \{\n)', r'\1    %s %s;\n' % (kind, b), body, count=1)
    return body


def trim_call_args(code, ptypes):
    """m2c passes leftover registers as extra args to functions defined in this file."""
    def sub(m):
        name, args = m.group(1), m.group(2)
        n = len(ptypes.get(name, []))
        parts, depth, cur = [], 0, ''
        for c in args:
            if c == ',' and depth == 0:
                parts.append(cur); cur = ''
                continue
            depth += (c in '([') - (c in ')]')
            cur += c
        parts.append(cur)
        if name in ptypes and len(parts) > n and args.strip():
            return '%s(%s)' % (name, ','.join(parts[:n]).strip())
        return m.group(0)
    return re.sub(r'(?<![\w.>])(\w+)\(((?:[^();\n]|\((?:[^();\n]|\([^();\n]*\))*\))*)\)(?=;|\)| [!=<>])', sub, code)


def scalar_ptr_fields(body):
    """`p->unk4` on an `f32 *` / `s32 *` p (m2c's view of small float/int structs) is p[1]."""
    for t, v in re.findall(r'(?:(?<=^    )|(?<=\()|(?<=, ))(f32|s32|u32|s16|u16) \*(\w+)(?=[;,)])', body, re.M):
        es = GC_SIZE[t]
        body = re.sub(r'\b%s->unk([0-9A-F]+)\b' % v, lambda m: '%s[%d]' % (v, int(m.group(1), 16) // es), body)
    return body


def inline_sqrt(body):
    """MWCC inlines sqrtf as __frsqrte + Newton steps + NaN/inf branches; put the call back."""
    pat = re.compile(r'^(\s*)if \(([\w.\->\[\]]+) > \(bitwise f32\) 0\.0\) \{\n\s*(\w+) = __frsqrte\(\2\);\n'
                     r'(?:.*\n)*?\s*(\w+) = \(f64\) \2 \* \(0\.5 \* \w+ \* \(3\.0 - .*\n'
                     r'\s*\} else if \(\(bitwise f32\) 0\.0 == \2\) \{\n\s*\4 = 0\.0;\n'
                     r'\s*\} else if \(\2 != \(bitwise f32\) 0\.0\) \{\n\s*\4 = .*__float_nan;\n'
                     r'\s*\} else \{\n\s*\4 = .*__float_huge;\n\s*\}\n', re.M)
    # float flavour: if (x > 0.0f) { 3 Newton steps } else { r = x; }
    pat2 = re.compile(r'^(\s*)if \(([\w.\->\[\]]+) > 0\.0f\) \{\n\s*\w+ = __frsqrte\(\2\);\n'
                      r'(?:[^}\n]*\n)*?\s*\} else \{\n\s*(\w+) = \2;\n\s*\}\n', re.M)
    return pat2.sub(lambda m: '%s%s = sqrtf(%s);\n' % (m.group(1), m.group(3), m.group(2)),
                    pat.sub(lambda m: '%s%s = sqrtf(%s);\n' % (m.group(1), m.group(4), m.group(2)), body))


def unset_f9(code):
    """Hu3DCameraPosSet & co. take 9 floats; m2c loses the 9th (f9). After ..., v.x, v.y it is v.z."""
    def sub(m):
        base, f = m.group(1), m.group(2)
        return '%s%s, %s%s' % (m.group(0)[:m.start(3) - m.start(0)], '', base, {'y': '.z', 'unk4': '.unk8'}[f])
    return re.sub(r'([\w\[\]().>-]+?)\.(y|unk4), (M2C_ERROR\(/\* Read from unset register \$f9 \*/\))',
                  lambda m: '%s.%s, %s%s' % (m.group(1), m.group(2), m.group(1), {'y': '.z', 'unk4': '.unk8'}[m.group(2)]), code)


def var_types(body):
    """{var: struct type} for `T *var` params and locals of a function."""
    norm = {'Point3d': 'Vec', 'HuVecF': 'Vec'}
    return dict((v, norm.get(t, t)) for t, v in re.findall(r'(?:^    |\(|, )(?:struct )?(\w+) \*(\w+)(?=[;,)])', body, re.M))


def mixed_struct_copies(body, layouts):
    """`*a = *b;` with a: T1*, b: T2* (T1 starts with a T2): m2c's view of a copy into the first field."""
    vt = var_types(body)

    def first_of(t, want, path=''):
        for foff, sz, cnt, name in layouts.get(t, []):
            if foff != 0:
                continue
            ft = FIELD_TYPES.get((t, name), '')
            p = path + name + ('[0]' if cnt > 1 else '')
            if ft == want:
                return p
            if ft in layouts:
                return first_of(ft, want, p + '.')
        return None

    def sub(m):
        a, b = m.group(2), m.group(3)
        ta, tb = vt.get(a), vt.get(b)
        if ta and tb and ta != tb:
            p = first_of(ta, tb)
            if p:
                return '%s%s->%s = *%s;' % (m.group(1), a, p, b)
        return m.group(0)
    return re.sub(r'^(\s*)\*(\w+) = \*(\w+);', sub, body, flags=re.M)


def asm_values(asm, name):
    """Data directive values of `.obj name` in the split asm (name$123 form for local statics)."""
    m = re.search(r'^\.obj %s, \w+\n(.*?)^\.endobj' % re.escape(name), asm, re.M | re.S)
    if not m:
        return None
    vals = []
    for d, args in re.findall(r'^\s*\.(4byte|2byte|byte|float|double)\s+(.*)$', m.group(1), re.M):
        for a in args.split(','):
            a = a.strip()
            if d == 'float':
                a = a if a.endswith('f') else a + 'f'
            elif re.match(r'^-?(0x[0-9A-Fa-f]+|\d+)$', a):
                a = '0x%X' % int(a, 0) if int(a, 0) > 9 else str(int(a, 0))
            vals.append(a)
    return vals


def fill_initializers(code, asm):
    """m2c leaves `static struct _struct_X_0xN X[K]; /* unable to generate initializer ... */` empty."""
    def sub(m):
        decl, name, count = m.group(1), m.group(2), m.group(3)
        vals = asm_values(asm, re.sub(r'_(\d+)$', r'$\1', name)) or asm_values(asm, name)
        if not vals:
            return m.group(0)
        if count:
            k = int(count, 0)
            n = max(1, len(vals) // k)
            init = ', '.join('{ %s }' % ', '.join(vals[i:i + n]) for i in range(0, n * k, n))
        else:
            init = ', '.join(vals)
        return '%s = { %s };' % (decl, init)
    return re.sub(r'^((?:static )?struct _struct_\w+ (\w+)(?:\[(\w+)\])?);[^\n]*unable to generate initializer[^\n]*$',
                  sub, code, flags=re.M)


def symbol_info(symbols):
    """{name: (size, kind)} from dtk symbols.txt (kind: float/4byte/2byte/byte/string/'')."""
    info = {}
    for m in re.finditer(r'^(\S+) = \.\w+:0x[0-9A-F]+; // type:object size:(0x[0-9A-F]+)[^\n]*?(?:data:(\w+))?$', symbols or '', re.M):
        info[re.sub(r'\$(\d+)', r'_\1', m.group(1))] = (int(m.group(2), 16), m.group(3) or '')
    return info


def synth_globals(code, info):
    """Make what m2c left untyped compile: undefined `struct _struct_X_0xN` and `static ? X;`."""
    def fields(size, kind):
        t = 'f32' if kind == 'float' else 's16' if kind == '2byte' else 'u8' if kind in ('byte', 'string') else 's32'
        es = {'f32': 4, 's32': 4, 's16': 2, 'u8': 1}[t]
        return ''.join('    %s unk%X;\n' % (t, o) for o in range(0, size - size % es, es))
    defined = set(re.findall(r'^struct (_struct_\w+) \{', code, re.M))
    pre = ''

    def floaty(name):
        # dtk's data kind is a guess for bss; trust how the code uses the fields
        n = re.escape(name)
        return bool(re.search(r'\b%s(?:\[[^\]]*\])?\.unk\w+ [-+*/]?= (?:\(f32\)|[^;]*\d\.\d+f)' % n, code)
                    or re.search(r'\(f32\) %s(?:\[[^\]]*\])?\.unk\w+' % n, code)
                    or re.search(r'\b%s(?:\[[^\]]*\])?\.unk\w+ [*/] ' % n, code))
    for full, base, sz in sorted(set(re.findall(r'\bstruct (_struct_(\w+?)_0x([0-9A-F]+))\b', code))):
        if full in defined:
            continue
        kind = info.get(base, (0, ''))[1]
        if floaty(base):
            kind = 'float'
        pre += 'struct %s { // TODO(mp5): synthesized from the symbol size\n%s};\n\n' % (full, fields(int(sz, 16), kind))
        defined.add(full)
    def sub(m):
        size, kind = info.get(m.group(2), (4, ''))
        if floaty(m.group(2)):
            kind = 'float'
        if size == 4:
            return '%sstatic %s %s;' % (m.group(1), 'f32' if kind == 'float' else 's32', m.group(2))
        return '%sstatic struct { // TODO(mp5): synthesized from the symbol size\n%s} %s;' % (m.group(1), fields(size, kind), m.group(2))
    code = re.sub(r'^()static \? (\w+);[^\n]*', sub, code, flags=re.M)
    # tables of synthesized structs indexed as *(&tbl[i] + (j * 4)): row i, element j
    for full, base, sz in sorted(set(re.findall(r'\bstruct (_struct_(\w+?)_0x([0-9A-F]+))\b', code))):
        t = 'f32' if info.get(base, (0, ''))[1] == 'float' else 'u32'
        code = re.sub(r'\*\(&%s\[([^\[\]]+)\] \+ \(\(?([^()]+?)\)? \* 4\)\)' % re.escape(base),
                      lambda m: '((%s *)&%s[%s])[%s]' % (t, base, m.group(1), m.group(2)), code)
    return pre + code


def camera_move_entry(code):
    """MP5 RELs' library MgCameraMoveEntry(cam, to, frames): it returns the move object (callers keep it to
    poll the move; m2c sees no return value), and its 0x48-byte memcpys are whole-camera copies."""
    m = re.search(r'^void (MgCameraMoveEntry\((\w+) \*arg0, \w+ \*arg1, f32 farg0\)) \{\n(.*?)\n\}\n', code, re.M | re.S)
    if not m:
        return code
    body = m.group(3).replace('        return;\n', '        return NULL;\n')
    mv = re.search(r'(\w+) = (\w+)->data;', body)
    if not mv:
        return code
    body = re.sub(r'    memcpy\([^;]*&%s->unk4, [^;]*\);\n' % mv.group(1), '    %s->unk4 = *arg0;\n' % mv.group(1), body)
    body = re.sub(r'    memcpy\(\(s32\) \(%s \+ 0x48\)[^;]*\);\n' % mv.group(1), '    %s->unk4C = *arg1;\n' % mv.group(1), body)
    body += '\n    return %s;' % mv.group(2)
    code = code[:m.start()] + 'OMOBJ *%s {\n%s\n}\n' % (m.group(1), body) + code[m.end():]
    return re.sub(r'\w+ = \(bitwise f32\) MgCameraMoveEntry\(', 'MgCameraMoveEntry(', code)


def run(code, asm, types_path, symbols=None):
    hints = parse_types(types_path)
    dead = unused_functions(asm)
    chunks = []
    ptypes = param_types(code)
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
            for v, t in hints['vars'].get(name, {}).items():
                text = re.sub(r'^(    )(?:[\w ]+\*|M2C_UNK|\?|[su]32) ?%s;$' % v, r'\g<1>%s *%s;' % (t, v), text, flags=re.M)
                text = resolve_fields(text, v, t, hints['layouts'])
            text = fix_struct_arrays(text, hints['layouts'])
            text = element_pointers(text, hints['layouts'])
            text = deref_work(text, hints['layouts'])
            text = malloc_sizeof(text, hints['layouts'])
            text = stack_vecs(text, ptypes)
            text = scalar_ptr_fields(text)
            text = stack_arrays(name, text, hints['objdata_fn'].get(name, hints['objdata']))
            text = jumptable_else(text)
            text = inline_sqrt(text)
            text = hoist_bitwise_calls(text)
            text = lost_swaps(text)
            text = pow2_mod(text)
            text = struct_copies(text)
            text = mixed_struct_copies(text, hints['layouts'])
            text = re.sub(r'\bHuPrcVSleep\([^)]+\)', 'HuPrcVSleep()', text)
            # OMOBJ model/motion are s16 arrays
            text = re.sub(r'->(mdlId|mtnId)->unk([0-9A-F]+)\b', lambda m: '->%s[%d]' % (m.group(1), int(m.group(2), 16) // 2), text)
            text = re.sub(r'\bsaved_reg_\w+\b', '0 /* TODO(mp5): uninitialised in the original */', text)
            text = re.sub(r'(\(&\w+\[[^\]]+\] \+ \(\w+ \* 0x[0-9A-F]+\)\))', r'\1 /* TODO(mp5): byte offset */', text)
            text = field_2d(text, hints['globals'], hints['layouts'])
            text = element_overflow(text)
            # engine / --types struct pointers stepped by their GameCube size: one element
            for t, size in list(ENGINE_GC_SIZE.items()) + list(STRUCT_SIZE.items()):
                for v in re.findall(r'^    %s \*(\w+);$' % t, text, re.M):
                    text = re.sub(r'^(\s*)%s \+= 0x%X;$' % (v, size), r'\g<1>%s++;' % v, text, flags=re.M)
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
    for arr, (rows, cols) in hints['ptrarrays2d'].items():
        n = re.escape(arr)
        # untyped: *(&a[i] + (j * 4)); typed rows used as pointers: a[i]->unkH = a[i][H/4]
        code = re.sub(r'\*\(&%s\[([^\[\]]+)\] \+ \(\(?([^()]+?)\)? \* 4\)\)' % n, lambda m: '%s[%s][%s]' % (arr, m.group(1), m.group(2)), code)
        code = re.sub(r'\b%s\[([^\[\]]+)\]->unk([0-9A-F]+)\b' % n, lambda m: '%s[%s][%d]' % (arr, m.group(1), int(m.group(2), 16) // 4), code)
        code = re.sub(r'\(\*%s\)\[([^\[\]]+)\]' % n, lambda m: '%s[0][%s]' % (arr, m.group(1)), code)
    for arr, size in hints['arrays1d'].items():
        code = re.sub(r'\b%s->unk([0-9A-F]+)\b' % re.escape(arr), lambda m: '%s[%d]' % (arr, int(m.group(1), 16) // size), code)
    # globals m2c re-declares for the loader / inlined strings
    code = re.sub(r'^extern \? \(\*_[cd]tors\)\(\);\n', '', code, flags=re.M)
    for m in list(re.finditer(r'^static s8 (lbl_\w+)\[0x[0-9A-F]+\] = ".*";\n', code, re.M)):
        if len(re.findall(r'\b%s\b' % m.group(1), code)) == 1:
            code = code.replace(m.group(0), '')
    code = re.sub(r'^void ObjectSetup\(\);[^\n]*\n', '', code, flags=re.M)
    # MWCC function-local statics are named name$123
    code = re.sub(r'(\w)\$(\d+)', r'\1_\2', code)
    # globals only the dropped (unused) functions touched
    for m in list(re.finditer(r'^(?:static )?[\w?][\w ?]*\*? ?(lbl_\w+)(?:\[[^\]]*\])*;[^\n]*\n', code, re.M)):
        if len(re.findall(r'\b%s\b' % m.group(1), code)) == 1:
            code = code.replace(m.group(0), '')
    # m2c passes leftover registers to varargs (OSReport(fmt, (u32) (u64) x, (bitwise f32) x))
    code = re.sub(r'(OSReport\([^;]*?), \(u32\) \(u64\) \w+, \(bitwise f32\) \w+\)', r'\1)', code)
    code = re.sub(r'(OSReport\([^;]*?), \(bitwise f32\) \w+\)', r'\1)', code)
    code = unset_f9(code)
    code = re.sub(r'\(bitwise f32\) (-?\d+\.\d+)\b', r'\1f', code)
    for v in set(re.findall(r'^    (?:Vec|Point3d|HuVecF) (\w+);$', code, re.M)):
        code = re.sub(r'\(bitwise (?:f32|s32)\) %s\b(?![.\[])' % v, v + '.x', code)
    code = re.sub(r'(?m)^[^\n]*/\* extern \*/\n', '', code)
    code = fill_initializers(code, asm)
    if types_path:
        code = memset_sizeof(code, open(types_path, encoding='utf-8').read())
    # partial / odd-sized copies m2c couldn't express: a byte copy is exact
    code = code.replace('M2C_STRUCT_COPY(', 'memcpy(')
    code = camera_move_entry(code)
    code = trim_call_args(code, param_types(code))
    code = prototypes_from_definitions(code)
    for name, t in hints.get('statics', {}).items():
        arr = re.match(r'(.*?)(\[.*\])$', t)
        decl = ('%s %s%s' % (arr.group(1), name, arr.group(2))) if arr else ('%s %s' % (t, name))
        code = re.sub(r'^static (?:\?|struct _struct_\w+|struct \{[^}]*\}) ?%s(?:\[[^\]]*\])*;[^\n]*$' % name,
                      lambda _: 'static %s;' % decl, code, flags=re.M)
    return synth_globals(code, symbol_info(symbols))
