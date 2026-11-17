"""Hand fixes for the m519 draft; run by m519dll.sh on build/mp5/m519dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

def fn_span(name):
    m = re.search(r'(?m)^[\w *]*?\b%s\([^\n]*\) \{\n' % name, s)
    assert m, name
    return m.start(), s.index('\n}\n', m.end()) + 3

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

def set_fn(name, text):
    global s
    a, b = fn_span(name)
    s = s[:a] + text.strip('\n') + '\n' + s[b:]

# ---- tables of state functions ------------------------------------------------------------------------------
s = re.sub(r'(?ms)^struct _struct_lbl_1_data_\w+ \{.*?\n\};\n\n', '', s)
s = re.sub(r'(?ms)^static (?:void \(\*lbl_1_data_(?:1C|48|5C|64|74)|struct _struct_lbl_1_data_(?:20|7C)_\w+ lbl_1_data_(?:20|7C)).*?;\n(?=\w)', '', s)
rep('extern s32 GlobalCounter;', '''SHARED_SYM extern u32 GlobalCounter;
typedef void (*M519StateFn)();
// MP5 state tables: each state is a function that loops until the work's state changes
static M519StateFn lbl_1_data_1C[1] = { fn_1_26A0 };
static M519StateFn lbl_1_data_20[2][5] = {
    { fn_1_35BC, fn_1_3664, fn_1_8188, fn_1_98AC, fn_1_9BA8 },
    { fn_1_35BC, fn_1_5EDC, fn_1_8188, fn_1_98AC, fn_1_A068 },
};
static M519StateFn lbl_1_data_48[5] = { fn_1_A598, fn_1_A634, fn_1_A6C4, fn_1_A77C, fn_1_A834 };
static M519StateFn lbl_1_data_5C[2] = { fn_1_B004, fn_1_B0BC };
static M519StateFn lbl_1_data_64[4] = { fn_1_C3D4, fn_1_C570, fn_1_C798, fn_1_C470 };
static void (*lbl_1_data_74[2])(void *, HU3DMODEL *, HU3DPARTICLE *, Mtx) = { fn_1_CDF0, fn_1_CEE4 };
static M519StateFn lbl_1_data_7C[4][4] = {
    { fn_1_D720, fn_1_D7BC, fn_1_E174, fn_1_F2E8 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
    { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 },
};''')
s = s.replace('static s8 lbl_1_data_B[9] = "itemfook";\n', '')
s = re.sub(r'static s8 \*lbl_1_data_14\[2\] = [^;]*;', 'static char *lbl_1_data_14[2] = { "itemhook_c", "itemfook" };', s)
set_fn('fn_1_2654', '''void fn_1_2654(void) {
    M519Stage *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_1C[temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_2F54', '''void fn_1_2F54(void) {
    M519Mech *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_20[temp_r31->type][temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_A40C', '''void fn_1_A40C(void) {
    M519Player *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_48[temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_ADE4', '''void fn_1_ADE4(void) {
    M519Bullet *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_5C[temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_C248', '''void fn_1_C248(void) {
    M519Bld *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_64[temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_D610', '''void fn_1_D610(void) {
    M519Hud *temp_r31 = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_7C[temp_r31->type][temp_r31->state](temp_r31);
    }
}''')
set_fn('fn_1_CCF4', '''void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    lbl_1_data_74[particleP->dataCnt](particleP->work, modelP, particleP, mtx);
}''')

# ---- "wait a frame; leave the state function when the state changed" -----------------------------------------
s = s.replace('*(s32 *)HuPrcCurrentGet()->property', '((M519Hdr *) HuPrcCurrentGet()->property)->state')
s = s.replace('HuPrcCurrentGet()->property->unk2', '((M519Hdr *) HuPrcCurrentGet()->property)->prevState')

# ---- field names m2c left as offsets -------------------------------------------------------------------------
for a, b in [('unk44', 'inputOn'), ('unk48', 'turning'), ('unk4C', 'camFollow'), ('unkD4', 'aiHasTgt'), ('unkC4', 'aiFire'),
             ('unkC0', 'hitSame')]:
    s = re.sub(r'\b(m|temp_r29|temp_r31|lbl_1_bss_F8\[\w+\])->' + a + r'\b', r'\1->' + b, s)
# the 2D0 table's second half is addressed past the 0x38-byte entries
def view_sub(m):
    off = int(m.group(2), 16)
    return 'lbl_1_rodata_2D0[%s + %d].unk%X' % (m.group(1), off // 0x38, off % 0x38)
s = re.sub(r'lbl_1_rodata_2D0\[(\w+)\]\.unk([0-9A-F]+)', lambda m: view_sub(m) if int(m.group(2), 16) >= 0x38 else m.group(0), s)

# MWCC's inlined sqrtf (__frsqrte + Newton steps) -> sqrtf
# ---- struct member / table fixes -----------------------------------------------------------------------------
s = s.replace('lbl_1_bss_E8[m->player]->unkC', 'lbl_1_bss_E8[m->player]->isCom')
s = re.sub(r'\*\(p \+ \(\((\w+) \* 2\) \+ 0x14\)\)', r'p->mdl[\1]', s)
for a, b in (('unk24', 'pos.x'), ('unk28', 'pos.y'), ('unk2C', 'pos.z'), ('unk30', 'rot.x'), ('unk34', 'rot.y'), ('unk38', 'rot.z')):
    s = s.replace('p->%s = ' % a, 'p->%s = ' % b)
s = s.replace('b->unk4 = ', 'b->active = ')
s = s.replace('temp_r3->unkC = (s32) GWPlayerCfg', 'temp_r3->isCom = (s32) GWPlayerCfg')
s = s.replace('*(temp_r3 + ((var_r30 * 2) + 0x18)) = ', 'temp_r3->mot[var_r30] = ')
s = s.replace('(s32) temp_r30->unk4 != 0)', '(s32) temp_r30->active != 0)')
rep('''    if ((s16) GwSystem.subGameNo == -1) {
        lbl_1_bss_30 = GlobalCounter % 3;
        return;
    }
    lbl_1_bss_30 = GwSystem.subGameNo;''', '    lbl_1_bss_30 = GlobalCounter % 3; // MP5: GWSystem.subGameNo (debug stage select) == -1 in normal play')
rep('frandmod((u32) &lbl_1_rodata_B58)', 'frandmod((u32) (2390.0f - m->radius))')  # MP5 passes a float to frandmod (stale r3); intended
rep('lbl_1_data_14->unk0', 'lbl_1_data_14[0]')
s = re.sub(r'lbl_1_rodata_(EC8|F20|F28)->unk0', r'lbl_1_rodata_\1[0]', s)
in_fn('fn_1_BAC8', '            memcpy(sp - 0xC0, b, 0xC);', '')
in_fn('fn_1_BAC8', '&sp24), temp_r22_2', '&sp18), temp_r22_2')
s = s.replace('Hu3DData[temp_r31->model].hookData->unk1C = temp_r31;', '((HU3DPARTICLE *) Hu3DData[temp_r31->model].hookData)->work = temp_r31;')
in_fn('fn_1_10244', r"""            if ((f32) (temp_f31 < 30.0f) < 0.0f) {
                var_r25 = -(temp_f31 < 30.0f);
            } else {
                var_r25 = (s32) ((u32) M2C_ERROR(/* unknown instruction: mfcr $r0 */) >> 0x1FU);
            }
""", "            var_r25 = temp_f31 < 30.0f;\n")
in_fn('fn_1_C798', r"""        sp40 = b->pos.x;
        sp44 = b->pos.y;
        sp48 = b->pos.z;
        sp18 = &sp40;
        sp4C = b->pos.x;
        sp50 = b->pos.y;
        sp54 = b->pos.z;
        sp14 = &sp4C;
        temp_r16 = fn_1_10244(1U, (Vec *) sp18);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[0], fn_1_FE20(1U, (Vec *) sp14), temp_r16);
        sp28 = b->pos.x;
        sp2C = b->pos.y;
        sp30 = b->pos.z;
        sp10 = &sp28;
        sp34 = b->pos.x;
        sp38 = b->pos.y;
        sp3C = b->pos.z;
        spC = &sp34;
        temp_r16_2 = fn_1_10244(0xEU, (Vec *) sp10);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[1], fn_1_FE20(0xEU, (Vec *) spC), temp_r16_2);
""", """        Vec sndA = b->pos, sndB = b->pos, sndC = b->pos, sndD = b->pos;
        temp_r16 = fn_1_10244(1U, &sndA);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[0], fn_1_FE20(1U, &sndB), temp_r16);
        temp_r16_2 = fn_1_10244(0xEU, &sndC);
        HuAudFXPlayVolPan(lbl_1_rodata_F28[1], fn_1_FE20(0xEU, &sndD), temp_r16_2);
""")
in_fn('ObjectSetup', r"""    sp8 = 0x3C;
    spA = 0;
    spC = fn_1_28C;
    sp10 = fn_1_9F4;
    sp14 = fn_1_143C;
    sp18 = fn_1_14E8;
    sp1C = fn_1_1628;
    sp20 = fn_1_19C4;
    sp24 = fn_1_1FC0;
    sp28 = 0;
    sp2C = 0;
    MgSeqCreate((MGSEQ_PARAM *) &sp8);
""", """    MGSEQ_PARAM seqParam = { 0x3C, 0, fn_1_28C, fn_1_9F4, fn_1_143C, fn_1_14E8, fn_1_1628, fn_1_19C4, fn_1_1FC0, NULL, NULL };
    MgSeqCreate(&seqParam);
""")
rep('memcpy(temp_r3 + ((var_r30_2 * 8) + 0x38), &lbl_1_rodata_1064[type].ofs[var_r30_2], 8);', 'temp_r3->ofs[var_r30_2] = lbl_1_rodata_1064[type].ofs[var_r30_2];')
rep('HuMemDirectMallocNum(HEAP_SYSTEM, 0x40, MEMORY_DEFAULT_NUM)', 'HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M519Player), MEMORY_DEFAULT_NUM)')

# MP4 never evaluates a paused model before its first update (T-pose): let the result poses run
rep('    Hu3DMotionShiftSet(p->mdl[0], p->mot[4], 0.0f, 8.0f, 0U);', '    Hu3DModelAttrReset(p->mdl[0], 0x40000002U);' + chr(10) + '    Hu3DMotionShiftSet(p->mdl[0], p->mot[4], 0.0f, 8.0f, 0U);')
rep('    Hu3DMotionShiftSet(p->mdl[0], p->mot[5], 0.0f, 8.0f, 0U);', '    Hu3DModelAttrReset(p->mdl[0], 0x40000002U);' + chr(10) + '    Hu3DMotionShiftSet(p->mdl[0], p->mot[5], 0.0f, 8.0f, 0U);')
in_fn('fn_1_A634', '    Hu3DModelTPLvlSet(p->mdl[0], 1.0f);', '    Hu3DModelTPLvlSet(p->mdl[0], 1.0f);' + chr(10) + '    Hu3DModelAttrReset(p->mdl[0], 0x40000002U); // pose it once, then pause again (see below)' + chr(10) + '    HuPrcVSleep();' + chr(10) + '    HuPrcVSleep();' + chr(10) + '    HuPrcVSleep();' + chr(10) + '    Hu3DModelAttrSet(p->mdl[0], 0x40000002U);')
# MP5-ordered per-character tables: index with Mp5CharNo (MP4 chars Daisy/Waluigi/DK shift)
s = re.sub(r'lbl_1_rodata_(C60|D98|164)\[([^\[\]]*(?:\[[^\[\]]*\][^\[\]]*)*->charNo)\]', r'lbl_1_rodata_\1[Mp5CharNo(\2)]', s)
def inline_sqrt(src):
    lines = src.split('\n'); out = []; i = 0
    while i < len(lines):
        m = re.match(r'^(\s*)if \((.*) > 0\.0f\) \{$', lines[i])
        if m and i + 1 < len(lines) and '__frsqrte' in lines[i + 1]:
            ind, x = m.group(1), m.group(2)
            j = i + 1
            while not lines[j].startswith(ind + '} else'):
                j += 1
            if lines[j].strip() == '} else {':
                var = re.match(r'\s*(\w+) = ', lines[j + 1]).group(1)
                k = j + 2
                assert lines[k].strip() == '}', lines[k]
            else:  # } else if (0.0f == x) {  ... nan/huge chain
                var = re.match(r'\s*(\w+) = ', lines[j + 1]).group(1)
                k = j
                while lines[k].strip() != '}' or lines[k] is None or not lines[k].startswith(ind + '}'):
                    k += 1
                while lines[k].startswith(ind + '} else'):
                    k += 1
                    while not lines[k].startswith(ind + '}'):
                        k += 1
            out.append('%s%s = sqrtf(%s);' % (ind, var, x))
            i = k + 1
            continue
        out.append(lines[i]); i += 1
    return '\n'.join(out)
s = inline_sqrt(s)

open(p, 'w', encoding='utf-8', newline='\n').write(s)
