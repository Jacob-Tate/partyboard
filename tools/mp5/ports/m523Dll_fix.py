"""Hand fixes for the m523 draft; run by m523Dll.sh on build/mp5/m523Dll.c."""
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

# the model table lbl_1_bss_8C is an s16 array
s = s.replace('lbl_1_bss_8C->unk0', 'lbl_1_bss_8C[0]')

# fn_1_12C: the three UFO-less ring models live in a local s16[3]; the light arguments come straight from rodata
in_fn('fn_1_12C', '    s32 sp8[4];\n    Vec sp1C;\n    s32 sp28;\n', '    s16 sp8[3];\n')
in_fn('fn_1_12C', r'    sp8\[2\]\.x = .*\n(?:    sp(?:8\[2\]|1C|28).*\n)+    temp_r3 = Hu3DGLightCreateV\(&sp8\[2\], &sp1C, \(GXColor \*\) &sp28\);\n',
      '    temp_r3 = Hu3DGLightCreateV(&lbl_1_rodata_A0.unk0, &lbl_1_rodata_A0.unkC, &lbl_1_rodata_A0.unk18);\n', True)

# fn_1_BB0: the winners are four s16 characters
in_fn('fn_1_BB0', '    f32 sp8[4];', '    s16 sp8[4];')
rep('MgSeqWinnerSet(sp8[0], spA, sp8[1], spE);', 'MgSeqWinnerSet(sp8[0], sp8[1], sp8[2], sp8[3]);')

# COM probability tables read straight from rodata (m2c copied them into separate stack locals)
in_fn('fn_1_85A8', r'    s32 sp18\[4\];\n', '', True)
in_fn('fn_1_85A8', r'    sp18\[0\] = .*\n    sp18\[1\] = .*\n    sp18\[2\] = .*\n    sp18\[3\] = .*\n', '', True)
in_fn('fn_1_85A8', 'sp18[arg0->unk8]', 'lbl_1_rodata_240[arg0->unk8]')

# the model slots of a player object (omObjData::model): GC read them through the unk40 pointer
s = re.sub(r'->unk40->unk0\b', '->model[0]', s)
s = re.sub(r'->unk40->unk2\b', '->model[1]', s)
s = re.sub(r'->unk40->unk4\b', '->model[2]', s)
# a Vec's first element taken as the Vec
s = re.sub(r'&(\w+)->unk10\.x\b', r'&\1->unk10', s)
in_fn('fn_1_34D8', '            sp20 = (f32)', '            sp20.x = (f32)')

def replace_fn(name, code):
    global s
    st, en = fn_span(name)
    s = s[:st] + code + s[en:]

replace_fn('fn_1_7488', """void fn_1_7488(void) {
    s16 order[3];
    M523Player *team[2];
    Vec sp24;
    Vec sp18;
    f32 temp_f31;
    s32 i;
    s32 n;

    for (i = 0; i < 3; i++) {
        order[i] = -1;
    }
    order[0] = lbl_1_bss_13C->unk58;
    n = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i]->unk30 != 0 && i != lbl_1_bss_13C->unk58) {
            team[n++] = lbl_1_bss_140[i];
        }
    }
    VECSubtract(&team[0]->unk10, &lbl_1_data_2A8[1], &sp24);
    VECSubtract(&team[1]->unk10, &lbl_1_data_2A8[1], &sp18);
    temp_f31 = VECMag(&sp18);
    if (VECMag(&sp24) < temp_f31) {
        order[1] = team[0]->unk0;
        order[2] = team[1]->unk0;
    } else {
        order[1] = team[1]->unk0;
        order[2] = team[0]->unk0;
    }
    for (i = 0; i < 3; i++) {
        if (order[i] >= 0) {
            lbl_1_bss_140[order[i]]->unk48 = lbl_1_data_2A8[i];
        }
    }
}
""")

# fn_1_6294: the else branch repeats block_38's body (MSVC: label redefined)
in_fn('fn_1_6294', '    } else {\n        block_38:\n', '    } else {\n')
# fn_1_7C84: the 4x4 "these two collided" flag matrix
s = re.sub(r'&([\w>\[\]-]+?)->unk(10|1C|3C|48|5C|68|74|A4)\.x\b', r'&\1->unk\2', s)
in_fn('fn_1_7C84', '    s32 sp14[4];\n    s32 spE[4];\n', '    s16 sp14[3];\n    s16 spE[3];\n    Vec sp1C;\n')
in_fn('fn_1_7C84', 'sp14[2]', 'sp1C')
in_fn('fn_1_7C84', '    ? sp40;', '    s32 sp40[4][4];')
in_fn('fn_1_7C84', r'\*\(&sp40 \+ \(\((\w+) \* 0x10\) \+ \((\w+) \* 4\)\)\)', r'sp40[\1][\2]', True)

# the player work holds pointers (64-bit): sizeof, not GC's 0xB0
in_fn('fn_1_39DC', 'memset((M523Player *) var_r27->data, 0, 0xB0);', 'memset(var_r27->data, 0, sizeof(M523Player));')
# the solo player's object keeps 8 motions (data_208) but MP5 allocated 5 slots (heap overflow on GC, harmless there)
in_fn('fn_1_39DC', '3U, 5U, -1, fn_1_4900', '3U, 8U, -1, fn_1_4900')
# string data
s = re.sub(r's8 lbl_1_data_350\[0x10\] = \{.*?\};', 'char lbl_1_data_350[0x10] = "itemhook_ufo";', s, flags=re.S)
s = s.replace('static s8 lbl_1_data_394[6] = "cyl10";', 'static char lbl_1_data_394[6] = "cyl10";')

# fn_1_58A8: copies the caught player's pos (a 0xC copy at +0x10), not the whole player
in_fn('fn_1_58A8', '    *temp_r31 = *lbl_1_bss_140[temp_r31->unk58];', '    temp_r31->unk10 = lbl_1_bss_140[temp_r31->unk58]->unk10;')

replace_fn('fn_1_90EC', """s32 fn_1_90EC(M523Player *arg0) {
    Vec sp18;

    VECSubtract(&lbl_1_bss_13C->unk10, &arg0->unk10, &sp18);
    sp18.y = 0.0f;
    if (VECMag(&sp18) < 100.0f) {
        if (frandmod(0x64U) < lbl_1_rodata_260[arg0->unk8]) {
            if ((s16) arg0->unk8 <= 2) {
                return 1;
            }
            VECSubtract(&arg0->unkA4, &arg0->unk10, &sp18);
            if (VECMag(&sp18) < 50.0f) {
                return 1;
            }
            return 0;
        }
        if (frandmod(0x64U) < lbl_1_rodata_260[arg0->unk8]) {
            return 1;
        }
    }
    return 0;
}
""")

open(p, 'w', encoding='utf-8', newline='\n').write(s)
