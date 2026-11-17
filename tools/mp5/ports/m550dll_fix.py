"""Hand fixes for the m550 draft (called by m550dll.sh with the draft path)."""
import re, sys
p = sys.argv[1]
s = open(p, encoding='utf-8').read()

def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

# fn_1_8190: m2c lost the rodata copies (a Vec[4] and two int/float tables) into stack arrays
m = re.search(r'void fn_1_8190\(void\) \{.*?\n\}\n', s, re.S)
assert m
s = s[:m.start()] + '''void fn_1_8190(void) {
    M550Model *temp_r31;
    s32 var_r30;

    for (var_r30 = 0; var_r30 < 4; var_r30++) {
        temp_r31 = &lbl_1_bss_1FC0->unk3C[lbl_1_rodata_3B0[var_r30]];
        Hu3DModelAttrReset(temp_r31->unk0, 1U);
        Hu3DMotionSpeedSet(temp_r31->unk0, 1.0f);
        Hu3DMotionTimeSet(temp_r31->unk0, 50.0f);
        temp_r31->unk4 = lbl_1_rodata_370[var_r30];
        Hu3DModelPosSetV(temp_r31->unk0, &temp_r31->unk4);
        Hu3DModelScaleSet(temp_r31->unk0, lbl_1_rodata_3A0[var_r30], lbl_1_rodata_3A0[var_r30], lbl_1_rodata_3A0[var_r30]);
    }
}
''' + s[m.end():]


# the motion tables are s16[2][5]; m2c read them as structs / byte offsets
s = s.replace('lbl_1_bss_14AC.unk48[temp_r31]->unk4', 'lbl_1_bss_14AC.unk48[temp_r31][2]')
s = s.replace('lbl_1_bss_14AC.unk48[temp_r30]->unk8', 'lbl_1_bss_14AC.unk48[temp_r30][4]')
rep('fn_1_5918(*lbl_1_bss_24, lbl_1_bss_24[0][1]);', 'fn_1_5918(lbl_1_bss_24[0], lbl_1_bss_24[1]);')
rep('sp8 = sp8.x + (f32) (0x1E - (player * 0x3C));', 'sp8.x += (f32) (0x1E - (player * 0x3C));')
# a background prop's three frame counters are consecutive s32 (unk4, unk8, unkC)
rep('*(temp_r31 + temp_r4) = *(temp_r31 + temp_r4) + 1;', '(&temp_r31->unk4)[var_r28] += 1;')
s = s.replace('*(temp_r31 + ((var_r28 * 4) + 4))', '(&temp_r31->unk4)[var_r28]')

# m2c's signed-modulo expansion of rand8() % N (rand8 is a u8): the % is already printed, drop the leftovers
rep('''                temp_r4 = temp_r3 >> 0x1FU;
                temp_r31 = ((temp_r3 & 1) ^ temp_r4) - temp_r4;
''', '''                temp_r31 = temp_r3 & 1;
''')
s = re.sub(r'\n[ ]+temp_r\w+ = temp_r\w+ >> 0x1FU;', '', s)
s = re.sub(r'\n[ ]+temp_r\w+ = \(temp_r\w+ << 0x1[ED]\) - temp_r\w+;', '', s)

# per-player state words at 0x104 + 4 * player (m2c printed them as a byte offset from the work struct)
s = re.sub(r'\(&lbl_1_bss_14AC \+ \((.*?) \* 4\)\)->unk100', r'lbl_1_bss_14AC.unk104[\1 - 1]', s)

# DK's MP4 hand hook draws hooked models at a fraction of their size (the blowpipe was a dot in his fist): scale the
# hooked blowpipe up for DK, and back to 1 where the game unhooks it and drops it in world space at the finish.
# TODO(mp5 DK): the blowpipe points diagonally down instead of level at the opponent (needs a hooked-model rotation for
# DK), and in the win pose the balloon (placed at the body hook, a-itemhook-body, in fn_1_D64) covers DK's face.
rep('''        Hu3DModelHookSet(lbl_1_bss_A8[var_r29 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r29].unk2, 1, 0), temp_r31_4->unk0);
''', '''        Hu3DModelHookSet(lbl_1_bss_A8[var_r29 + 2].unk0, CharModelItemHookGet(lbl_1_bss_14AC.unk4[var_r29].unk2, 1, 0), temp_r31_4->unk0);
        if (lbl_1_bss_14AC.unk4[var_r29].unk2 == 5) {
            Hu3DModelScaleSet(temp_r31_4->unk0, 2.5f, 2.5f, 2.5f);
        }
''')
for v in ('temp_r30', 'temp_r31'):
    rep(f'''Hu3DModelRotSetV({v}->unk0, &sp8);
''', f'''Hu3DModelRotSetV({v}->unk0, &sp8);
        Hu3DModelScaleSet({v}->unk0, 1.0f, 1.0f, 1.0f);
''')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
