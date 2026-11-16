#!/usr/bin/env python3
"""Guess work-struct layouts from an m2c draft (raw or fixed-up) to start a --types header.

Objects in MP5 minigames are usually `<Prefix>Create()` (allocating the work), `<Prefix>Main()` (process
reading HuPrcCurrentGet()->property) and `<Prefix><Something>(work, ...)`. All `->unkXX` accesses through
that work pointer are collected, with type evidence, and printed as typedefs with explicit padding.

Usage: python tools/mp5/infer.py build/mp5/m526Dll.c [--prefix M526Player ...]
Review the output: fields with weak evidence are marked `// ?`.
"""
import argparse, re, sys
from collections import defaultdict

SIZE = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 'ptr': 4}
S16_FUNCS = r'(?:Hu3DModelCreate\w*|CharModelCreate|Hu3DMotionCreate\w*|CharMotionCreate|Hu3DJointMotion\w*|' \
            r'espEntry|HuSprGrpCreate|HuSprCreate|Hu3DParticleCreate|Hu3DGLightCreate\w*|Hu3DLLightCreate\w*|' \
            r'MGSeq\w*Create|Hu3DModelLink|Hu3DHookFuncCreate|Hu3DModelCameraCreate)'


def functions(code):
    for m in re.finditer(r'(?m)^([A-Za-z_][^\n;=]*?)\b(\w+)\(([^\n;]*)\) \{\n(.*?)^\}', code, re.S):
        yield m.group(2), m.group(3), m.group(4)


def evidence(body, var):
    """{offset: [type evidence]} for var->unkXX in body."""
    ev = defaultdict(list)
    v = re.escape(var)
    for m in re.finditer(r'\b%s->unk([0-9A-F]+)\b' % v, body):
        off = int(m.group(1), 16)
        line = body[body.rfind('\n', 0, m.start()) + 1: body.find('\n', m.end())]
        acc = m.group(0)
        a = re.escape(acc)
        if re.search(a + r' = -?[\d.]+f;', line) or re.search(a + r' [-+*/]?= [^;]*\b\d+\.\d+f', line) \
                or re.search(r'\(f32\) ' + a, line) or re.search(a + r' = \(f32\)', line):
            ev[off].append('f32')
        elif re.search(a + r' = \((s16|u16|s8|u8|s32|u32)\)', line):
            ev[off].append(re.search(a + r' = \((\w+)\)', line).group(1))
        elif re.search(a + r' = ' + S16_FUNCS + r'\(', line):
            ev[off].append('s16')
        elif re.search(a + r' = HuPrc\w*Create\(|' + a + r'->property', line):
            ev[off].append('proc')
        elif re.search(a + r'->unk[0-9A-F]+', line):
            ev[off].append('ptr')
        elif re.search(r'\((s16|u16|s8|u8)\) ' + a, line):
            ev[off].append(re.search(r'\((\w+)\) ' + a, line).group(1) + '?')
        elif re.search(a + r' = -?(?:0x[0-9A-F]+|\d+)U?;', line) or re.search(a + r' (\+|-)= 1;', line):
            ev[off].append('int')
        else:
            ev[off].append('')
    # s16/f32 arrays: *(var + ((i * 2) + 0x52))
    for m in re.finditer(r'\*\(%s \+ \(\((\w+) \* (\d+)\) \+ (0x[0-9A-F]+|\d+)\)\)' % v, body):
        ev[int(m.group(3), 0)].append('array%s' % m.group(2))
    return ev


def pick(evs):
    evs = [e for e in evs if e]
    for t in ('array2', 'array4', 'array1', 'proc', 'ptr', 'f32', 's16', 'u16', 's8', 'u8', 'u32', 's32'):
        if t in evs:
            return t, len(evs) > 1
    for t in ('s16?', 'u16?', 's8?', 'u8?'):
        if t in evs:
            return t[:-1], False
    return 's32', False


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('draft')
    ap.add_argument('--prefix', nargs='*')
    ap.add_argument('--protos', help='first-pass prototypes (build/mp5/<rel>_protos.h) to retype')
    a = ap.parse_args()
    code = open(a.draft, encoding='utf-8').read()
    fns = list(functions(code))
    names = [n for n, _, _ in fns]
    prefixes = a.prefix or sorted({n[:-6] for n in names if n.endswith('Create')})
    sizes = {}
    for name, params, body in fns:
        if name.endswith('Create'):
            m = re.search(r'HuMemDirectMallocNum\(\w+, (0x[0-9A-F]+|\d+)', body)
            if m:
                sizes[name[:-6]] = int(m.group(1), 0)
    for prefix in sorted(prefixes, key=len, reverse=False):
        ev = defaultdict(list)
        for name, params, body in fns:
            if not name.startswith(prefix) or any(name.startswith(p) and len(p) > len(prefix) for p in prefixes):
                continue
            vars_ = set()
            if name.endswith('Create'):
                vars_ |= set(re.findall(r'(\w+) = (?:temp_ret|HuMemDirectMallocNum\([^;]*\));', body))
            vars_ |= set(re.findall(r'(\w+) = HuPrcCurrentGet\(\)->property;', body))
            p0 = re.match(r'\s*[\w ]+\*\s*(arg\w+)', params)
            if p0 and not name.endswith('Create'):
                vars_.add(p0.group(1))
            for v in vars_:
                for off, e in evidence(body, v).items():
                    ev[off] += e
        if not ev:
            continue
        size = sizes.get(prefix)
        tname = prefix + 'Work'
        print('typedef struct %s { // %s' % (tname, ('size 0x%X' % size) if size else 'size ?'))
        off = 0
        offs = sorted(ev)
        for i, o in enumerate(offs):
            if o < off:
                continue
            t, strong = pick(ev[o])
            if o > off:
                print('    char pad%X[0x%X];' % (off, o - off))
            if t.startswith('array'):
                es = int(t[5:])
                nxt = next((x for x in offs[i + 1:] if x >= o + es and not str(pick(ev[x])[0]).startswith('array')), None)
                end = nxt if nxt else (size or o + es)
                n = max(1, (end - o) // es)
                ct = {1: 'u8', 2: 's16', 4: 's32'}[es]
                print('    %s unk%X[%d]; // array, count guessed' % (ct, o, n))
                off = o + n * es
                continue
            ct = {'ptr': 'void *', 'proc': 'HUPROCESS *', 'int': 's32'}.get(t, t)
            al = 4 if t in ('ptr', 'proc') else SIZE.get(ct, 4)
            if o % al:
                ct, al = ('s16', 2) if o % 2 == 0 else ('u8', 1)
            print('    %s%sunk%X;%s' % (ct, '' if ct.endswith('*') else ' ', o, '' if strong or t in ('f32', 'ptr', 'proc') else ' // ?'))
            off = o + (4 if t in ('ptr', 'proc') else SIZE.get(ct, 4))
        if size and size > off:
            print('    char pad%X[0x%X];' % (off, size - off))
        print('} %s;\n' % tname)
    if a.protos:
        out, hints = protos_and_hints(code, a.protos, prefixes)
        print('\n'.join(sorted(set(hints))))
        print()
        print('\n'.join(out))



def protos_and_hints(code, protos_path, prefixes):
    """Prototypes with the first pointer param retyped to its object's work struct, and `// var` hints for
    process mains (`x = HuPrcCurrentGet()->property`) and creators."""
    out, hints = [], []
    def owner(name):
        best = [p for p in prefixes if name.startswith(p)]
        return max(best, key=len) if best else None
    bodies = {n: b for n, _, b in functions(code)}

    def work_param(name, params):
        """The pointer param with the deepest field accesses is the work (not always the first:
        XPosGet(Vec *out, XWork *work))."""
        best, depth = None, -1
        for pm in re.finditer(r'\*\s*(arg\w+)', params):
            offs = [int(x, 16) for x in re.findall(r'\b%s->unk([0-9A-F]+)' % pm.group(1), bodies.get(name, ''))]
            d = max(offs) if offs else 0
            if d > depth:
                best, depth = pm.group(1), d
        return best

    for line in open(protos_path).read().split('\n'):
        m = re.match(r'(.*?)\b(\w+)\((.*)\);$', line)
        if not m:
            continue
        p = owner(m.group(2))
        ret, params = m.group(1), m.group(3)
        if p:
            t = p + 'Work'
            if m.group(2) == p + 'Create' and ret.strip().endswith('*'):
                ret = t + ' *'
            elif not m.group(2).endswith('Create'):
                wp = work_param(m.group(2), params)
                if wp:
                    params = re.sub(r'[\w ]+\*\s*%s\b' % wp, '%s *%s' % (t, wp), params, count=1)
        out.append('%s%s(%s);' % (ret, m.group(2), params))
    # tables of state functions: void (*XModeTbl[N])(...) = { fn, ((cast) fn), ... }
    for m in re.finditer(r'^(?:static )?\w+ \(\*(\w+)\[(\w+)\]\)\([^\n]*\) = \{(.*?)\};', code, re.M | re.S):
        fns = re.findall(r'\b(M\w+|fn_\w+)\)?(?:,|\s*$)', m.group(3), re.M)
        p = owner(fns[0]) if fns else None
        if p:
            out.append('extern void (*%s[%s])(%sWork *);' % (m.group(1), m.group(2), p))
    for name, params, body in functions(code):
        p = owner(name)
        if not p:
            continue
        for v in set(re.findall(r'(\w+) = HuPrcCurrentGet\(\)->property;', body)) | \
                (set(re.findall(r'(\w+) = (?:temp_ret|HuMemDirectMallocNum\([^;]*\));', body)) if name.endswith('Create') else set()):
            hints.append('// var %s %s: %sWork' % (name, v, p))
    return out, hints


if __name__ == '__main__':
    main()
