import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# per-player slots the draft reaches through byte-scaled pointer math
s = re.sub(r'\(&lbl_1_bss_1954 \+ \(\((.+?) \+ 2\) \* 4\)\)->unkA0', r'lbl_1_bss_1954.unkA8[\1]', s)
s = re.sub(r'\(&lbl_1_bss_1954 \+ \((\w+) \* 8\)\)->unkFC', r'lbl_1_bss_1954.unkFC[\1 * 2]', s)
s = re.sub(r'\(&lbl_1_bss_1954 \+ \((\w+) \* 8\)\)->unk100', r'lbl_1_bss_1954.unkFC[\1 * 2 + 1]', s)
# motion lists are s16[9]: member offsets become indices
s = re.sub(r'unk48\[([^\]]+)\]->unk([0-9A-F]+)\b', lambda m: 'unk48[%s][0x%X]' % (m.group(1), int(m.group(2), 16) // 2), s)
s = re.sub(r'\*lbl_1_bss_1954\.unk48\[([^\]]+)\]', r'lbl_1_bss_1954.unk48[\1][0]', s)
s = s.replace('fn_1_8A00(*lbl_1_bss_54, lbl_1_bss_54[0][1]);', 'fn_1_8A00(lbl_1_bss_54[0], lbl_1_bss_54[1]);')
# per-character tables are in MP5 character order (the motion table is indexed by player number in the original)
s = s.replace('lbl_1_data_2A8[lbl_1_bss_1954.unk4[var_r30_6].unk2]', 'lbl_1_data_2A8[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_6].unk2)]')
s = s.replace('lbl_1_data_2A8[lbl_1_bss_1954.unk4[var_r30_6].unk2]', 'lbl_1_data_2A8[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_6].unk2)]')
s = s.replace('(s16) lbl_1_bss_1954.unk4[var_r30_4].unk2 > 9', 'Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_4].unk2) > 9')
s = s.replace('lbl_1_data_0[lbl_1_bss_1954.unk4[var_r30_4].unk2 + 0xD]', 'lbl_1_data_0[Mp5CharNo(lbl_1_bss_1954.unk4[var_r30_4].unk2) + 0xD]')
# MgSeqModeNext takes no arguments (m2c left registers in)
s = re.sub(r'MgSeqModeNext\(\(M542Work \*\) temp_r3_3, &lbl_1_bss_1954\);', 'MgSeqModeNext();', s)
s = s.replace('MgSeqModeNext(&lbl_1_bss_1954);', 'MgSeqModeNext();')
# the fullscreen red pulse (alpha lbl_1_bss_10) is written by hand
m = re.search(r'void fn_1_2524\(HU3DMODEL \*modelP, f32 \(\*mtx\)\[3\]\[4\]\) \{.*?\n\}\n', s, re.S)
assert m
s = s[:m.start()] + '''void fn_1_2524(HU3DMODEL *modelP, Mtx mtx) {
    Mtx44 proj;
    GXColor color = { 255, 0, 0, 0 };

    color.a = (u8) lbl_1_bss_10;
    if (color.a == 0) {
        return;
    }
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 1000.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXPosition3f32(640.0f, 480.0f, 0.0f);
    GXPosition3f32(0.0f, 480.0f, 0.0f);
    GXEnd();
}
''' + s[m.end():]
s = re.sub(r'static struct \{ // TODO\(mp5\): synthesized from the symbol size\n    u8 unk0;\n\} lbl_1_rodata_A4;\n', '', s)
s = s.replace('void fn_1_2524(HU3DMODEL *modelP, f32 (*mtx)[3][4]);', 'void fn_1_2524(HU3DMODEL *modelP, Mtx mtx);')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
