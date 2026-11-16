#!/usr/bin/env python3
"""Draft C for a Mario Party 5 REL straight from its assembly (non-matching, for porting).

Pipeline: MP5 decomp split asm -> asm syntax fixups -> m2c (with MP5 headers as context)
-> post-pass (GX FIFO writes -> GXPosition/GXColor/GXTexCoord calls).

Prereqs (one-time):
  pip install git+https://github.com/matt-kempster/m2c ; ninja on PATH
  clone the MP5 decomp next to partyboard (../mp5ref), copy the MP5 disc image into
  ../mp5ref/orig/GP5E01_00/, then:  cd ../mp5ref && python configure.py && ninja build/GP5E01_00/config.json

Usage:
  python tools/mp5/decomp.py m505Dll                 # whole REL -> build/mp5/m505Dll.c
  python tools/mp5/decomp.py m505Dll -f fn_1_A90     # one function to stdout
  python tools/mp5/decomp.py m505Dll --types build/mp5/m505_types.h   # extra typed context
The --types file is plain C (structs, typedefs, prototypes, `extern Foo lbl_1_bss_X;`) that m2c
uses to name fields and globals; iterate on it and re-run instead of hand-fixing every access.
"""
import argparse, glob, os, re, shutil, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.normpath(os.path.join(HERE, '..', '..'))
OUT = os.path.join(ROOT, 'build', 'mp5')

CTX_HEADERS = """typedef int bool;
#include "game/charman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/hsfex.h"
#include "game/mgdata.h"
#include "game/mg/timer.h"
#include "math.h"
"""


def find_clang():
    c = shutil.which('clang')
    if c:
        return c
    hits = sorted(glob.glob(r'C:/Program Files/Microsoft Visual Studio/*/*/VC/Tools/Llvm/x64/bin/clang.exe'))
    if hits:
        return hits[-1]
    sys.exit('clang not found (install LLVM or the VS "C++ Clang tools" component)')


def strip_bodies(s):
    """m2c only needs declarations; drop top-level function bodies (incl. inline asm ones)."""
    out, depth, i, n = [], 0, 0, len(s)
    while i < n:
        c = s[i]
        if c == '{' and depth == 0 and re.search(r'\)\s*$', ''.join(out[-200:])):
            k = 0
            while True:
                if s[i] == '{':
                    k += 1
                elif s[i] == '}':
                    k -= 1
                    if k == 0:
                        break
                i += 1
            out.append(';')
            i += 1
            continue
        depth += (c == '{') - (c == '}')
        out.append(c)
        i += 1
    s = ''.join(out)
    s = re.sub(r'\bstatic inline\b|\binline\b', '', s)
    s = re.sub(r'(\w)\s+\(\(0x8000 << 16\) \| 0x[0-9A-Fa-f]+\);', r'\1;', s)  # AT_ADDRESS leftovers
    return s


def build_context(mp5ref, extras):
    os.makedirs(OUT, exist_ok=True)
    src = os.path.join(OUT, 'ctx_in.c')
    with open(src, 'w') as f:
        f.write(CTX_HEADERS)
        for extra in extras:
            if extra:
                f.write('#include "%s"\n' % os.path.abspath(extra).replace('\\', '/'))
    raw = os.path.join(OUT, 'ctx.raw')
    inc = [os.path.join(mp5ref, d) for d in ('include', 'src', 'include/dolphin')]
    cmd = [find_clang(), '-E', '-P', '-nostdinc', '--target=powerpc-eabi', '-DM2CTX',
           '-D__attribute__(x)=', '-D__declspec(x)=', src, '-o', raw] + ['-I' + d for d in inc]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode:
        sys.exit(r.stderr)
    ctx = os.path.join(OUT, 'ctx.h')
    with open(raw) as f, open(ctx, 'w') as g:
        g.write(strip_bodies(f.read()))
    return ctx


def find_asm(mp5ref, rel):
    hits = glob.glob(os.path.join(mp5ref, 'build', 'GP5E01_00', rel, 'asm', '**', '*.s'), recursive=True)
    if not hits:
        sys.exit('no asm for %s; run the split in mp5ref first (see --help)' % rel)
    return sorted(hits)


def fix_asm(paths, dst):
    with open(dst, 'w') as g:
        for p in paths:
            s = open(p).read()
            s = s.replace('cror eq, gt, eq', 'cror 2, 1, 2').replace('cror eq, lt, eq', 'cror 2, 0, 2')
            g.write(s + '\n')


# ---- GX FIFO post-pass --------------------------------------------------------------------
ENUM = {'GX_POS_XY': 0, 'GX_POS_XYZ': 1, 'GX_NRM_XYZ': 0, 'GX_CLR_RGB': 0, 'GX_CLR_RGBA': 1,
        'GX_TEX_S': 0, 'GX_TEX_ST': 1,
        'GX_U8': 0, 'GX_S8': 1, 'GX_U16': 2, 'GX_S16': 3, 'GX_F32': 4,
        'GX_RGB565': 0, 'GX_RGB8': 1, 'GX_RGBX8': 2, 'GX_RGBA4': 3, 'GX_RGBA6': 4, 'GX_RGBA8': 5}
CT = {0: 'u8', 1: 's8', 2: 'u16', 3: 's16', 4: 'f32'}
FIFO = re.compile(r'^(\s*)\*\((?:[\w ]+\*)\)0xCC008000 = (.*);\s*$')


def ev(tok):
    tok = tok.strip().rstrip('U')
    if tok in ENUM:
        return ENUM[tok]
    try:
        return int(tok, 0)
    except ValueError:
        return None


def vertex_layout(desc, fmt):
    """[(func, ncomponents)] per vertex, in GX attribute order."""
    lay = []
    for attr in ('GX_VA_PNMTXIDX', 'GX_VA_POS', 'GX_VA_NRM', 'GX_VA_CLR0', 'GX_VA_CLR1',
                 'GX_VA_TEX0', 'GX_VA_TEX1', 'GX_VA_TEX2', 'GX_VA_TEX3'):
        mode = desc.get(attr)
        if not mode or mode == 'GX_NONE':
            continue
        if attr == 'GX_VA_PNMTXIDX':
            lay.append(('GXMatrixIndex1x8', 1)); continue
        kind = attr[6:9]
        name = {'POS': 'GXPosition', 'NRM': 'GXNormal', 'CLR': 'GXColor', 'TEX': 'GXTexCoord'}[kind]
        if mode in ('GX_INDEX8', 'GX_INDEX16'):
            lay.append(('%s1x%s' % (name, mode[8:]), 1)); continue
        cnt, typ = fmt.get(attr, (None, None))
        if cnt is None:
            return None
        if kind == 'CLR':
            if typ == 5:
                lay.append(('GXColor4u8', 4))
            elif typ in (1, 2):
                lay.append(('GXColor3u8', 3))
            else:
                return None
            continue
        n = {'POS': 2 + cnt, 'NRM': 3, 'TEX': 1 + cnt}[kind]
        lay.append(('%s%d%s' % (name, n, CT.get(typ, '?')), n))
    return lay


def fifo_pass(code):
    """Each FIFO write fills the next component of the current vertex layout; a GX call is
    emitted where its last component is written (temps computed in between stay in place).
    The cursor restarts at GXBegin; anything that doesn't line up is left raw with a TODO."""
    out, desc, fmt, todo = [], {}, {}, 0
    lay, slot, pend = None, 0, []

    def flush_raw():
        nonlocal todo
        if pend:
            todo += 1
            out.append(pend[0].group(1) + '/* TODO(mp5): raw GX FIFO writes, vtx layout %s */' % lay)
            out.extend(p.group(0) for p in pend)
            pend.clear()

    for ln in code.split('\n'):
        if re.match(r'^\S.*\)\s*\{$', ln):  # new function
            flush_raw(); desc, fmt, lay = {}, {}, None
        if 'GXClearVtxDesc()' in ln:
            desc = {}
        m = re.search(r'GXSetVtxDesc\((GX_VA_\w+), (\w+)\)', ln)
        if m:
            desc[m.group(1)] = m.group(2)
        m = re.search(r'GXSetVtxAttrFmt\(\w+, (GX_VA_\w+), (\w+), (\w+), ', ln)
        if m:
            fmt[m.group(1)] = (ev(m.group(2)), ev(m.group(3)))
        if 'GXBegin(' in ln:
            flush_raw(); lay, slot = vertex_layout(desc, fmt), 0
        f = FIFO.match(ln)
        if not f:
            if pend and re.match(r'^\s*(}|.*\{\s*$|goto |loop_|block_|return)', ln):
                flush_raw()  # control flow inside a vertex: give up on this one
            out.append(ln); continue
        if not lay:
            pend.append(f); continue
        pend.append(f)
        fn, n = lay[slot]
        if len(pend) == n:
            out.append('%s%s(%s);' % (pend[0].group(1), fn, ', '.join(p.group(2) for p in pend)))
            pend.clear()
            slot = (slot + 1) % len(lay)
    flush_raw()
    return '\n'.join(out), todo


def fix_denormals(code):
    """m2c bug: an lfs'd constant kept in a register and then used in double math is printed as
    the float's bits read as a double (10.0f -> 5.398241246e-315). Re-read those bits as f32."""
    import struct

    def sub(m):
        bits = round(float(m.group(0)) / 5e-324)
        if not 0 < bits < 1 << 32:
            return m.group(0)
        f = struct.unpack('>f', bits.to_bytes(4, 'big'))[0]
        return '%sf' % repr(f)

    return re.sub(r'\b\d\.\d+e-3[01]\d\b', sub, code)


def split_params(s):
    out, depth, cur = [], 0, ''
    for c in s:
        if c == ',' and depth == 0:
            out.append(cur.strip()); cur = ''
            continue
        depth += (c == '(') - (c == ')')
        cur += c
    if cur.strip() and cur.strip() != 'void':
        out.append(cur.strip())
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('rel', help='MP5 REL dir name as in mp5ref/config (e.g. m505Dll, m502dll)')
    ap.add_argument('-f', '--func', help='only this function (prints to stdout)')
    ap.add_argument('--types', help='extra C header with types/externs for this REL')
    ap.add_argument('--mp5ref', default=os.path.join(ROOT, '..', 'mp5ref'))
    ap.add_argument('-o', '--out')
    ap.add_argument('--raw', action='store_true', help='skip the structural clean-ups (tools/mp5/fixups.py)')
    ap.add_argument('--absorb', action='store_true', help='write fields m2c inferred for --types structs back into it')
    a = ap.parse_args()

    mp5ref = os.path.abspath(a.mp5ref)
    asm = os.path.join(OUT, a.rel + '.s')
    fix_asm(find_asm(mp5ref, a.rel), asm)
    from m2c.main import parse_flags, run
    import io, contextlib

    def m2c(extras, func=None):
        ctx = build_context(mp5ref, extras)
        argv = ['--target', 'ppc-mwcc-c', '--context', ctx, '--globals', 'used', '--no-cache']
        if func:
            argv += ['-f', func]
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            run(parse_flags(argv + [asm]))
        return buf.getvalue()

    # pass 1: each function's own signature (decompiled from its body) is reliable; call sites in other
    # functions guess wrongly (float args as pointers, missing args). Feed the signatures back as context.
    first = m2c([a.types])
    declared = open(a.types).read() if a.types else ''
    protos = []
    for m in re.finditer(r'^([A-Za-z_][\w \*]*?)\b(\w+)\((.*)\) \{$', first, re.M):
        if m.group(2) in ('_prolog', '_epilog'):
            continue
        sig = m.group(0)[:-2]
        # stack-spill "params" m2c invents (arg_sp0, void (**arg_sp0)(...)) aren't real
        params = [p for p in split_params(m.group(3)) if 'arg_sp' not in p]
        # pointer params only touched at +0/+4/+8 are Vecs (m2c types them by the first field it sees)
        body = first[m.end():first.find('\n}', m.end())]
        for i, p in enumerate(params):
            pm = re.match(r'(?:f32|s32|u32|void|\?) \*(arg\w+)$', p)
            if pm:
                offs = {x for x in re.findall(r'\b%s->unk([0-9A-F]+)\b' % pm.group(1), body)}
                if offs and offs <= {'0', '4', '8'} and '(bitwise s32) %s->' % pm.group(1) not in body:
                    params[i] = 'Vec *%s' % pm.group(1)
        sig = '%s%s(%s)' % (m.group(1), m.group(2), ', '.join(params) or 'void')
        sig = re.sub(r'\? \*', 'void *', sig)
        if '?' in sig or '_struct_' in sig or re.search(r'\b%s\(' % m.group(2), declared):
            continue
        protos.append(sig.replace('f32 (*mtx)[4]', 'Mtx mtx') + ';')
    proto_h = os.path.join(OUT, a.rel + '_protos.h')
    with open(proto_h, 'w') as f:
        f.write('\n'.join(protos) + '\n')
    raw = m2c([a.types, proto_h], a.func)
    code, todo = fifo_pass(raw)
    code = fix_denormals(code)
    # unparsed jump tables: `idx *= 4; switch (*(&jumptable_X + idx)) {` -> `switch (idx) {`
    # (the case labels m2c prints are already table indices)
    code = re.sub(r'(\w+) \*= 4;\n(\s*)switch \(\*\(&jumptable_\w+ \+ \1\)\) \{ /\* unable to parse jump table \*/',
                  r'\2switch (\1) { /* jump table */', code)

    if not a.func and not a.raw:
        sys.path.insert(0, HERE)
        import fixups
        sym = os.path.join(mp5ref, 'config', 'GP5E01_00', 'rels', a.rel, 'symbols.txt')
        code = fixups.run(code, open(asm).read(), a.types, open(sym).read() if os.path.exists(sym) else None)
    # m2c re-prints --types structs it found more fields for (in padding); drop them from the code, and
    # with --absorb write m2c's version (comments stripped) back into the types header
    if a.types:
        th = open(a.types, encoding='utf-8').read()
        for m in list(re.finditer(r'^typedef struct (\w+) \{\n.*?^\} \1;[^\n]*\n\n?', code, re.M | re.S)):
            if not re.search(r'\} %s;' % m.group(1), th):
                continue
            code = code.replace(m.group(0), '')
            if a.absorb:
                new = re.sub(r'/\*.*?\*/ ?', '', m.group(0)).rstrip() + '\n'
                new = re.sub(r'[ \t]+\n', '\n', new)
                th = re.sub(r'typedef struct %s \{.*?\} %s;[^\n]*\n' % (m.group(1), m.group(1)), lambda _: new, th, flags=re.S)
                print('  absorbed m2c fields for', m.group(1))
        if a.absorb:
            open(a.types, 'w', encoding='utf-8', newline='\n').write(th)
    errs = re.findall(r'M2C_ERROR\(/\* (.*?) \*/\)', code)
    if a.func:
        print(code)
        return
    dst = a.out or os.path.join(OUT, a.rel + '.c')
    with open(dst, 'w', newline='\n') as f:
        f.write(code)
    fns = re.findall(r'^\S[^\n;]*\b(\w+)\([^;\n]*\) \{$', code, re.M)
    print('%s: %d lines, %d functions -> %s' % (a.rel, code.count('\n'), len(fns), dst))
    print('  m2c errors: %d %s' % (len(errs), sorted(set(errs))[:5]))
    print('  unknown types (?): %d   unk field accesses: %d   gotos: %d   FIFO runs left: %d'
          % (len(re.findall(r'\? ', code)), len(set(re.findall(r'\bunk[0-9A-F]+\b', code))),
             code.count('goto '), todo))


if __name__ == '__main__':
    main()
