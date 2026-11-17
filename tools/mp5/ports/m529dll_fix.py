"""Hand fixes for the m529 (Handy Hoppers) draft; run by m529dll.sh on build/mp5/m529dll.c."""
import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

# strings of the dead camera debug print
s = re.sub(r'(?m)^static s8 lbl_1_data_4(?:F1|F5)\b[^\n]*\n', '', s)
# the light colour is split over two symbols
s = re.sub(r'(?m)^M529Col lbl_1_data_4;[^\n]*\n', 'M529Col lbl_1_data_4 = { 255, 255, 255, 255 };\n', s)
# the game was written for 4 players with the 2 teams in slots 0,1 and 2,3: MP5's 2 vs 2 gives the teams'
# group numbers, MP4's the same (or, outside the board, one group per player), so a slot is the rank of the
# player when sorted by (group, player)
s = re.sub(r'GWPlayerCfg\[([^\[\]]+)\]\.group\b', r'Mp5Slot(\1)', s)
rep('void ObjectSetup(void) {', '''static s16 Mp5Slot(s16 player)
{
    s16 i, slot = 0;
    for (i = 0; i < 4; i++) {
        if (GWPlayerCfg[i].group < GWPlayerCfg[player].group || (GWPlayerCfg[i].group == GWPlayerCfg[player].group && i < player)) {
            slot++;
        }
    }
    return slot;
}

void ObjectSetup(void) {''')
# m2c leftovers from the GameMes calls' extra arguments
s = re.sub(r'\n\s*var_f1 = \(bitwise f32\) temp_ret(?:_2)?;', '', s)
s = re.sub(r'\n    f32 var_f1;', '', s)
rep('''            var_r5 = (u32) &lbl_1_rodata_38;
            lbl_1_bss_38 = *(u32) &lbl_1_rodata_38;''', '            lbl_1_bss_38 = 0.0f;')
# the new-record message
rep('GameMesCreate(0xE, lbl_1_bss_18, &lbl_1_bss_18)', 'MGSeqRecordCreate(lbl_1_bss_18)')
# a result global of MP5's minigame manager (always 0 here)
rep('            lbl_80288A28 = lbl_1_bss_230;\n', '')
# the scores of both teams are shown together
rep('MgScoreDispOn(*(temp_r30 + ((var_r31 * 4) + 8)));', 'MgScoreDispOn(var_r31 == 0 ? temp_r30->unk8 : temp_r30->unkC);')
rep('MgScoreDispOff(*(temp_r30 + ((var_r31_2 * 4) + 8)));', 'MgScoreDispOff(var_r31_2 == 0 ? temp_r30->unk8 : temp_r30->unkC);')
# the pitch for the speed: a switch on the float's bits
rep('''    switch (temp_r31->unk68) {                      /* irregular */
    case 0x40000000:
        return 0x2000;
    case 0x3FC00000:
        return 0x1000;
    case 0x3F99999A:
        return 0x6A4;
    case 0x3F800000:
        return 0;
    default:
        return 0;
    }
''', '''    if (temp_r31->unk68 == 2.0f) {
        return 0x2000;
    }
    if (temp_r31->unk68 == 1.5f) {
        return 0x1000;
    }
    if (temp_r31->unk68 == 1.2f) {
        return 0x6A4;
    }
    return 0;
''')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
