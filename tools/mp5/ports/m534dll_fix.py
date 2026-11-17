"""Hand fixes for the m534 draft; run by m534dll.sh on build/mp5/m534Dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
def func(name):
    """(start, end) of the function definition `name`"""
    m = re.search(r'(?m)^[\w *()]+\b%s\([^;{]*\) \{\n' % re.escape(name), s)
    e = s.index('\n}\n', m.end()) + 3
    return m.start(), e
def sub_in(name, a, b, count=0):
    global s
    st, e = func(name)
    body = s[st:e]
    assert a in body, (name, a)
    s = s[:st] + body.replace(a, b) + s[e:]

s = re.sub(r'(?ms)^struct _struct_lbl_1_bss_\w+ \{.*?\n\};[^\n]*\n\n', '', s)

# ---- frand: MP5 frand16 is frand() & 0xFFFF (m2c drops the mask); the one `& 3` (frandmod-like) is kept ----------
n_before = len(re.findall(r'frand\(\)', s))
s = re.sub(r'frand\(\)(?! & 3\))', '(frand() & 0xFFFF)', s)
assert n_before == 21, n_before
assert s.count('(frand() & 0xFFFF)') == 20

# the synthesized rodata struct has no initializer: first slot of each team is 0 / 2 (rodata_A8 = { 0, 2 })
rep('sp8[1] = lbl_1_rodata_A8.unk4;', 'sp8[1] = 2;')

# ---- game state: per-player team (unk24) / character (unk34) / winner character (unk44) ---------------------------
s = re.sub(r'\*\(temp_r31 \+ \(\(var_r30 \* 4\) \+ 0x(24|34|44)\)\)', lambda m: 'temp_r31->unk%s[var_r30]' % m.group(1), s)
s = s.replace('    void *temp_r31;\n', '    M534Game *temp_r31;\n', 1) if False else s
rep('return *(lbl_1_bss_1C->data + ((idx * 4) + 0x44));', 'return ((M534Game *)lbl_1_bss_1C->data)->unk44[idx];')

# ---- score boards -------------------------------------------------------------------------------------------------
rep('return *(lbl_1_bss_58->data + ((team << 6) + 0x34));', 'return ((M534Score *)lbl_1_bss_58->data)->unk0[team].unk34;')
rep('''    temp_r31 = lbl_1_bss_58->data;
    temp_r5 = (team << 6) + 0x34;
    *(temp_r31 + temp_r5) = *(temp_r31 + temp_r5) + add;''', '''    temp_r31 = lbl_1_bss_58->data;
    temp_r31->unk0[team].unk34 += add;''')
s = s.replace('temp_r31 = temp_r26 + (var_r31 << 6);', 'temp_r31 = &temp_r26->unk0[var_r31];')
s = s.replace('temp_r29 = temp_r26 + (var_r31 << 6);', 'temp_r29 = &temp_r26->unk0[var_r31];')
s = re.sub(r'\*\(temp_r29 \+ \(\(var_r30 \* 2\) \+ 0x38\)\)', 'temp_r29->unk38[var_r30]', s)
s = s.replace('temp_r31 = temp_r28 + (var_r29 << 6);', 'temp_r31 = &temp_r28->unk0[var_r29];')
s = s.replace('temp_r31 = temp_r27 + (var_r30 << 6);', 'temp_r31 = &temp_r27->unk0[var_r30];')
s = s.replace('Hu3DAnimBankSet(temp_r31->unk38,', 'Hu3DAnimBankSet(temp_r31->unk38[0],')
s = s.replace('Hu3DAnimBankSet(temp_r31->unk3A,', 'Hu3DAnimBankSet(temp_r31->unk38[1],')
s = s.replace('Hu3DAnimBankSet(temp_r31->unk3C,', 'Hu3DAnimBankSet(temp_r31->unk38[2],')
s = s.replace('VECAdd(temp_r31 + 0x10, temp_r31 + 0x1C, temp_r31 + 0x10);',
              'VECAdd((Vec *)&temp_r31->unk10, (Vec *)&temp_r31->unk1C, (Vec *)&temp_r31->unk10);')
s = s.replace('Hu3DModelRotSetV(temp_r29, temp_r31 + 0x28);', 'Hu3DModelRotSetV(temp_r29, (Vec *)&temp_r31->unk28);')
s = s.replace('    void *temp_r29;\n', '    M534Board *temp_r29;\n')
s = s.replace('    void *temp_r31;\n', '    M534Board *temp_r31;\n')   # only the score board functions keep a void *temp_r31 (fn_1_1DF4 fixed below)

sub_in('fn_1_1DF4', 'M534Board *temp_r31;', 'M534Game *temp_r31;')

# ---- stage: sound slots / clouds / buttons --------------------------------------------------------------------------
sub_in('fn_1_449C', 'M534Player *temp_r31;', 'M534Stage *temp_r31;')
sub_in('fn_1_449C', 'M534Player *var_r29;', 'M534Snd *var_r29;')
sub_in('fn_1_449C', 'M534Player *var_r30;', 'M534Snd *var_r30;')
s = s.replace('var_r30 = temp_r28->data;', 'var_r30 = ((M534Stage *)temp_r28->data)->unk0;')
s = s.replace('var_r29 = temp_r28->data;', 'var_r29 = ((M534Stage *)temp_r28->data)->unk0;')
s = re.sub(r'(var_r(?:25|26|27|28|29|30)) \+= 8;', r'\1++;', s)
s = re.sub(r'void \*(var_r2[5-8]);', r'M534Snd *\1;', s)
s = re.sub(r'(?m)^(\s+)sp(54|50|4C|44) = arg0->data;\n(\s+)(var_r\d+) = sp\2;',
           r'\1\4 = ((M534Stage *)arg0->data)->unk0;', s)
rep('''        temp_r4 = (var_r31 * 0xC) + 0x100;
        *(temp_r30 + temp_r4) = *(temp_r30 + temp_r4) + temp_r30->unk13C[var_r31];
        Hu3DModelPosSetV(arg0->model[var_r31 + 5], temp_r30 + ((var_r31 * 0xC) + 0x100));''',
    '''        temp_r30->unk100[var_r31].x += temp_r30->unk13C[var_r31];
        Hu3DModelPosSetV(arg0->model[var_r31 + 5], &temp_r30->unk100[var_r31]);''')
rep('*(lbl_1_bss_48->data + ((slot * 4) + 0x1A0)) = -12.0f;', '((M534Stage *)lbl_1_bss_48->data)->unk1A0[slot] = -12.0f;')

# ---- fog hooks: a real GXColor ----------------------------------------------------------------------------------------
for fn, col, mode in (('fn_1_3CAC', '{ 200, 200, 255, 0 }', 'GX_FOG_LIN'), ('fn_1_3D58', '{ 255, 255, 255, 0 }', 'GX_FOG_NONE')):
    st, e = func(fn)
    hdr = s[st:s.index('{' + chr(10), st) + 2]
    s = s[:st] + hdr + '''    GXColor fogColor = %s;

    GXSetFog(%s, 1000.0f, 8000.0f, 10.0f, 20000.0f, fogColor);
}
''' % (col, mode) + s[e:]

# m2c lost the stripped call arguments; the Seq creators return the process id
s = s.replace('MGSeqDrawCreate() temp_ret)', 'MGSeqDrawCreate()').replace('MGSeqFinishCreate() temp_ret)', 'MGSeqFinishCreate()')
s = re.sub(r'\(MGTIMER \*\) lbl_1_bss_0', 'lbl_1_bss_0', s)
s = s.replace('lbl_1_bss_0 = 0;', 'lbl_1_bss_0 = NULL;').replace('(u32) lbl_1_bss_0 != 0', 'lbl_1_bss_0 != NULL')
s = s.replace('lbl_1_data_358[0][var_r30]', 'lbl_1_data_358[var_r30]').replace('lbl_1_data_2C8[0][var_r31]', 'lbl_1_data_2C8[var_r31]')

# ---- model light setup from the HSF's light objects (MP5 object layout == HSFLIGHT at +0x10) ------------------------
rep('''                sp14 = var_r26->mesh.base.pos.x - (bitwise f32) var_r26->mesh.parent;
                sp18 = var_r26->mesh.base.pos.y - (bitwise f32) var_r26->mesh.childNum;
                sp1C = var_r26->mesh.base.pos.z - (bitwise f32) var_r26->mesh.child;''',
'''                sp14 = var_r26->light.target.x - var_r26->light.pos.x;
                sp18 = var_r26->light.target.y - var_r26->light.pos.y;
                sp1C = var_r26->light.target.z - var_r26->light.pos.z;''')
s = re.sub(r'Hu3DLLightCreate\(arg0, \(bitwise f32\) var_r26->mesh.parent, \(bitwise f32\) var_r26->mesh.childNum, \(bitwise f32\) var_r26->mesh.child,',
           'Hu3DLLightCreate(arg0, var_r26->light.pos.x, var_r26->light.pos.y, var_r26->light.pos.z,', s)
rep('Hu3DLLightSpotSet(arg0, temp_r3, GX_SP_COS, var_r26->mesh.base.scale.y);', 'Hu3DLLightSpotSet(arg0, temp_r3, var_r26->light.cutoff, 2);')
rep('var_r26->mesh.base.scale.x - var_r26->mesh.base.rot.z', 'var_r26->light.ref_brightness - var_r26->light.ref_distance')
rep('1.0f, GX_DA_MEDIUM);', '1.0f, 2);')
rep('var_r26 += 0x144; /* TODO(mp5): byte step? */', 'var_r26++;')

open(p, 'w', encoding='utf-8').write(s)
