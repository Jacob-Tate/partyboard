import re, sys, os
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
here = os.path.dirname(os.path.abspath(__file__))
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
def fn_span(name):
    m = re.search(r'(?m)^[A-Za-z_][^\n;=]*\b%s\([^\n;]*\) \{\n.*?^\}\n' % re.escape(name), s, re.S)
    assert m, name
    return m
def replace_fn(name, new):
    global s
    m = fn_span(name)
    s = s[:m.start()] + new + s[m.end():]
def sub_in_fn(name, a, b, count=0, regex=False):
    global s
    m = fn_span(name)
    body = m.group(0)
    new = re.sub(a, b, body, count=count) if regex else body.replace(a, b) if count == 0 else body.replace(a, b, count)
    assert new != body, (name, a)
    s = s[:m.start()] + new + s[m.end():]

# ---- the four effect hooks and what drives them: hand-written (see the .inc) ----
inc = open(os.path.join(here, 'm514Dll_effects.inc'), encoding='utf-8').read()
inc = inc.replace('0x480020', 'DATA_MAKE_NUM(DATADIR_MP5_M514, 32)')
hand = ['fn_1_5C34', 'fn_1_5CD4', 'fn_1_5DE4', 'fn_1_6588', 'fn_1_6644', 'fn_1_68EC', 'fn_1_6C44', 'fn_1_6D7C',
        'fn_1_6ED4', 'fn_1_79F8', 'fn_1_7B8C', 'fn_1_585C', 'fn_1_54DC', 'fn_1_5574', 'fn_1_5610', 'fn_1_56AC']
for f in hand:
    m = fn_span(f)
    s = s[:m.start()] + s[m.end():]
m = fn_span('fn_1_5B04')
s = s[:m.start()] + inc + '\n' + s[m.start():]
# the remaining arc / spark / footprint users reach the hook data through byte-scaled pointers
rep('Hu3DData[(s16) *lbl_1_bss_218->model].hookData + (arg0 * 0x44);', '&((M514Arc *) Hu3DData[lbl_1_bss_218->model[0]].hookData)[arg0];')
rep('Hu3DData[(s16) lbl_1_bss_218->model[1]].hookData + ((var_r29 * 0x24) + 4);', '&((M514Sparks *) Hu3DData[lbl_1_bss_218->model[1]].hookData)->unk4[var_r29];')
rep('        temp_r31->unk10 = -1;\n', '        temp_r31->unk10.r = temp_r31->unk10.g = temp_r31->unk10.b = temp_r31->unk10.a = 0xFF;\n')
rep('    var_r31 = Hu3DData[(s16) lbl_1_bss_218->model[2]].hookData;\n', '    var_r31 = ((M514Foots *) Hu3DData[lbl_1_bss_218->model[2]].hookData)->unk0;\n')
s = s.replace('    var_r31 += 0x1C; /* TODO(mp5): byte step? */\n', '    var_r31++;\n')
s = s.replace('var_r30 += 0x1C; /* TODO(mp5): byte step? */', 'var_r30++;')
s = re.sub(r'(?m)^(\s*)temp_r31->unk4 = frand\(\);', r'\1temp_r31->unk4 = frand();', s)
# ObjectSetup: the three MP5 stores into element 4 of s16[4] arrays are the per-player resets
rep('        lbl_1_bss_10[4] = -1;\n        lbl_1_bss_18[4] = -1;\n        lbl_1_bss_8[4] = 0;\n',
    '        lbl_1_bss_10[var_r31] = -1;\n        lbl_1_bss_18[var_r31] = -1;\n        lbl_1_bss_20[var_r31] = -1;\n        lbl_1_bss_8[var_r31] = 0;\n')

# ---- score slots (4 x 0x24 bytes in the score object's data) reached with byte offsets ----
# the two-step position easing
rep('''        temp_r4 = (var_r30_3 * 0x24) + 0x20;
        *(temp_r31 + temp_r4) = (f32) ((f64) *(temp_r31 + temp_r4) + (0.2 * (f64) (*(temp_r31 + ((var_r30_3 * 0x24) + 0x28)) - *(temp_r31 + ((var_r30_3 * 0x24) + 0x20)))));
        temp_r4_2 = (var_r30_3 * 0x24) + 0x24;
        *(temp_r31 + temp_r4_2) = (f32) ((f64) *(temp_r31 + temp_r4_2) + (0.2 * (f64) (*(temp_r31 + ((var_r30_3 * 0x24) + 0x2C)) - *(temp_r31 + ((var_r30_3 * 0x24) + 0x24)))));
''', '''        temp_r31->unk0[var_r30_3].unk20 = (f32) ((f64) temp_r31->unk0[var_r30_3].unk20 + (0.2 * (f64) (temp_r31->unk0[var_r30_3].unk28 - temp_r31->unk0[var_r30_3].unk20)));
        temp_r31->unk0[var_r30_3].unk24 = (f32) ((f64) temp_r31->unk0[var_r30_3].unk24 + (0.2 * (f64) (temp_r31->unk0[var_r30_3].unk2C - temp_r31->unk0[var_r30_3].unk24)));
''')
S = 'M514Score'
def slot(base, idx, off):
    return '%s->unk0[%s].unk%X' % (base, idx, int(off, 16))
s = re.sub(r'\*\((\w+) \+ \(\((\w+) \* 0x24\) \+ (0x[0-9A-F]+)\)\)', lambda m: slot(m.group(1), m.group(2), m.group(3)), s)
s = re.sub(r'\*\(lbl_1_bss_220->data \+ \(\((\w+) \* 0x24\) \+ (0x[0-9A-F]+)\)\)',
           lambda m: slot('((M514Score *)lbl_1_bss_220->data)', m.group(1), m.group(2)), s)
s = re.sub(r'memcpy\((\w+) \+ \(\((\w+) \* 0x24\) \+ (0x[0-9A-F]+)\), ',
           lambda m: 'memcpy(&%s, ' % slot(m.group(1), m.group(2), m.group(3)), s)
s = s.replace('lbl_1_data_53C[*(temp_r23 + ((var_r24 * 0x24) + 0x10))]', 'lbl_1_data_53C[temp_r23->unk0[var_r24].unk10]')
# bubble sort of the ranks: the m2c swaps lost their temporaries
rep('''                M2C_SWAP(temp_r31->unk0[temp_r20].unk10, temp_r31->unk0[temp_r21].unk10); /* m2c lost the temporary */
                M2C_SWAP(sp8[var_r28], sp8[var_r28 + 1]); /* m2c lost the temporary */
''', '''                {
                    s32 swap = temp_r31->unk0[temp_r20].unk10;
                    temp_r31->unk0[temp_r20].unk10 = temp_r31->unk0[temp_r21].unk10;
                    temp_r31->unk0[temp_r21].unk10 = swap;
                    swap = sp8[var_r28];
                    sp8[var_r28] = sp8[var_r28 + 1];
                    sp8[var_r28 + 1] = swap;
                }
''')

# ---- score slot fields past the 0x24-byte stride (the original keeps them in the next slot's first bytes) ----
s = re.sub(r'memcpy\(&(\w+)->unk0\[(\w+)\]\.unk20, &(lbl_1_data_53C\[[^;]*\]), 8\);',
           r'\1->unk0[\2].unk20 = \3.unk0;\n        \1->unkB8[\2] = \3.unk4;', s)
s = re.sub(r'memcpy\(&(\w+)->unk0\[(\w+)\]\.unk28, &(lbl_1_data_53C\[[^;]*\]), 8\);',
           r'\1->unkC8[\2][0] = \3.unk0;\n        \1->unkC8[\2][1] = \3.unk4;', s)
s = re.sub(r'->unk0\[(\w+)\]\.unk24\b', r'->unkB8[\1]', s)
s = re.sub(r'->unk0\[(\w+)\]\.unk28\b', r'->unkC8[\1][0]', s)
s = re.sub(r'->unk0\[(\w+)\]\.unk2C\b', r'->unkC8[\1][1]', s)

# ---- obstacles ----
s = s.replace('temp_r0_2 = *temp_r31->unk0;', 'temp_r0_2 = temp_r31->unk0->unk0;')
s = re.sub(r'\*temp_r24 = (\d);', r'temp_r24->unk0 = \1;', s)
s = s.replace('temp_r25 = temp_r27->unk0->unkC + 0xC;', 'temp_r25 = temp_r27->unk0->unkC + 1;')
s = s.replace('temp_r3->unk0 = (ANIMDATA *) arg1;', 'temp_r3->unk0 = arg1;')
s = s.replace('temp_r31 = *arg0->data;', 'temp_r31 = ((M514Player *) arg0->data)->unk0;')

# the walk-to-point distance: an inlined sqrtf (reciprocal square root estimate + Newton steps)
s, n = re.subn(r'    if \(\(\(var_f31 \* var_f31\) \+ \(temp_f30 \* temp_f30\)\) > 0\.0f\) \{\n.*?    \} else \{\n        var_f26 = [^\n]*\n    \}\n',
               '    var_f26 = sqrtf((var_f31 * var_f31) + (temp_f30 * temp_f30));\n', s, count=1, flags=re.S)
assert n == 1
s = s.replace('(&temp_r27->unk40)->unk8 - (&temp_r26->unk40)->unk8', 'temp_r27->unk40.z - temp_r26->unk40.z')
s = s.replace('*temp_r30 = fn_1_9794();', '((M514Goal *) temp_r30)->unk0 = fn_1_9794();')
s = s.replace('(void (*)(HU3DMODEL *, f32 (*)[3][4])) ', '')

# ---- frand: MP5's frand16 is `frand() & 0xFFFF` (16 of the 16 calls; the three plain ones in fn_1_7EBC stay 32-bit) ----
s = s.replace('(frand() - 0x8000)', '((s32) (frand() & 0xFFFF) - 0x8000)')
s = s.replace('(f32) frand())', '(f32) (frand() & 0xFFFF))')

# ---- per-character tables are in MP5 order ----
s = s.replace('lbl_1_data_1B0[temp_r31->unkC]', 'lbl_1_data_1B0[Mp5CharNo(temp_r31->unkC)]')
s = re.sub(r'lbl_1_data_500\[GWPlayerCfg\[(\w+)\]\.character\]', r'lbl_1_data_500[Mp5CharNo(GWPlayerCfg[\1].character)]', s)
s = re.sub(r'lbl_1_data_500\[GWPlayerCfg\[(\w+)\]\.character\]', r'lbl_1_data_500[Mp5CharNo(GWPlayerCfg[\1].character)]', s)

# ---- the camera: m2c dropped the .x of two stack vectors ----
sub_in_fn('fn_1_9E4', '        sp48 = (f32)', '        sp48.x = (f32)')
sub_in_fn('fn_1_9E4', '        sp30 = (f32)', '        sp30.x = (f32)')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
