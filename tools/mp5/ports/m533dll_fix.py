"""Hand fixes for the m533 draft; run by m533dll.sh on build/mp5/m533dll.c."""
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

# unused leftover structs of the m2c draft
s = re.sub(r'(?ms)^struct _struct_lbl_1_bss_\w+ \{.*?\n\};[^\n]*\n\n', '', s)
# the light colour is one symbol of 4 bytes whose last 3 are in the padding
s = re.sub(r'(?m)^static M533Col lbl_1_data_18;', 'M533Col lbl_1_data_18 = { 255, 255, 255, 255 };', s)
s = re.sub(r'(?m)^M533Col lbl_1_data_18;', 'M533Col lbl_1_data_18 = { 255, 255, 255, 255 };', s)
# the debug string of ObjectSetup: only its address was passed, the two -1 of rodata_54 are the team slots
rep('    spC[0] = lbl_1_rodata_54.unk0;\n    spC[1] = lbl_1_rodata_54.unk4;\n', '    spC[0] = -1;\n    spC[1] = -1;\n')
s = re.sub(r'(?ms)^static struct \{ // TODO\(mp5\): synthesized from the symbol size\n    s32 unk0;\n    s32 unk4;\n\} lbl_1_rodata_54;\n', '', s)
s = s.replace('OSReport("******* M533 ObjectSetup *********\\n", &lbl_1_rodata_54);', 'OSReport("******* M533 ObjectSetup *********\\n");')
# team of a player: MP5 reads GWPlayerCfg .group (0/1); MP4's group numbers differ (see m529), so a team is the
# rank of the player by (group, player) halved
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
# m2c's "x + 0x10000 == -1": a compare with -1
s = s.replace('(u32) (lbl_1_bss_30 + 0x10000) == -1U', 'lbl_1_bss_30 == -1')
s = s.replace('MgSeqModeGet((bitwise omObjData *) temp_f1)', 'MgSeqModeGet()')
s = s.replace('MgSeqModeGet(&lbl_1_rodata_D0)', 'MgSeqModeGet()')

# the object data pointers m2c saw as one type
in_fn('fn_1_1F98', 'M533Team *sp8[4];', 'M533Player *sp8[4];')
in_fn('fn_1_1840', 'M533Item *temp_r28;', 'M533Team *temp_r28;')
in_fn('fn_1_2724', 'M533Team *sp18[4];\n    M533Team *sp8[4];', 'M533Pillar *sp18[0x18];\n    M533Cloud *sp8[4];')
in_fn('fn_1_2724', r'(?<!Pillar )\*(sp18\[\w+\])', r'\1->unk0', True)
in_fn('fn_1_1F98', '*sp8[temp_r3] & 1', 'sp8[temp_r3]->unk0 & 1')
in_fn('fn_1_1F98', '*sp8[temp_r3_2] & 1', 'sp8[temp_r3_2]->unk0 & 1')
in_fn('fn_1_2D4C', 'M533Player *sp8[4];', 'M533Team *sp8[4];')
in_fn('fn_1_2D4C', '*sp20[var_r25] & 1', 'sp20[var_r25]->unk0 & 1')
in_fn('fn_1_3424', 'M533Player *spC[4];', 'M533Team *spC[4];')
in_fn('fn_1_3D50', 'M533Player *spC[4];', 'M533Team *spC[4];')
# the winning team: both teams' "finished" flags
in_fn('fn_1_3950', 'M533Player *sp10[4];', 'M533Team *sp10[2];')
in_fn('fn_1_3950', 'f32 sp8[4];', 's32 sp8[4];')
in_fn('fn_1_3950', '(s32) *sp8[3]', '(s32) sp10[1]->unk0')
in_fn('fn_1_3950', '(s32) *sp10[0]', '(s32) sp10[0]->unk0')
in_fn('fn_1_3950', '*sp18[var_r31] & 1', 'sp18[var_r31]->unk0 & 1')
in_fn('fn_1_3950', '*sp18[sp8[0]] & 1', 'sp18[sp8[0]]->unk0 & 1')
in_fn('fn_1_4080', '*sp8[var_r25] & 1', 'sp8[var_r25]->unk0 & 1')

in_fn('fn_1_4080', r'(void|M533\w+) \*(temp_r4(?:_2)?);', r'M533Player *\2;', True)
in_fn('fn_1_52C4', 'M533Player *sp18[4];\n    M533Player *sp8[4];', 'M533Pillar *sp18[0x18];\n    M533Cloud *sp8[4];')
in_fn('fn_1_52C4', r'\*(sp8\[\w+\]) = ', r'\1->unk0 = ', True)
in_fn('fn_1_52C4', r'\*(sp18\[\w+\]) = ', r'\1->unk0 = ', True)
# DK (no MP5 motions): MP4 motion per slot where MP5's has no MP4 equivalent. Slot 3 is the pedalling pose
# (hand on the crank): MP4 132, one arm extended forward, face stays visible. The rest idle.
rep('lbl_1_data_20[var_r29_2], 0 /* TODO(mp5): MP4 motion for DK */)', 'lbl_1_data_20[var_r29_2], m533DkMot[var_r29_2])')
rep('void ObjectSetup(void) {', 'static const s16 m533DkMot[10] = { 0, 0, 0, 132, 0, 0, 0, 0, 0, 0 };\n\nvoid ObjectSetup(void) {')
# character numbers: the draft compares / indexes with MP5's numbering (Waluigi 6, no DK)
in_fn('fn_1_4080', '(s32) sp8[var_r31_3]->unk14 == 6', 'Mp5CharNo(sp8[var_r31_3]->unk14) == 6')
in_fn('fn_1_4080', '(s32) sp8[var_r31_3]->unk14 == 8', 'Mp5CharNo(sp8[var_r31_3]->unk14) == 8')
s = s.replace('lbl_1_data_50[temp_r29->unk14]', 'lbl_1_data_50[Mp5CharNo(temp_r29->unk14)]')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
