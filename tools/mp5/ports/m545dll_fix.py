import re, sys
p = sys.argv[1]; s = open(p, encoding='utf-8').read()
def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)
# per-character tables are in MP5 character order
rep('fn_1_7CE4(&lbl_1_data_28[lbl_1_bss_67C.unk4[0].unk2], &lbl_1_data_28[lbl_1_bss_67C.unk4[1].unk2]);',
    'fn_1_7CE4(&lbl_1_data_28[Mp5CharNo(lbl_1_bss_67C.unk4[0].unk2)], &lbl_1_data_28[Mp5CharNo(lbl_1_bss_67C.unk4[1].unk2)]);')
rep('fn_1_7D08(*lbl_1_bss_240, lbl_1_bss_240[0][1]);', 'fn_1_7D08(lbl_1_bss_240[0], lbl_1_bss_240[1]);')
# the particle work is an array of templates
m = re.search(r'void fn_1_1F20\(HU3DMODEL \*modelP, HU3DPARTICLE \*particleP, Mtx mtx\) \{.*?\n\}\n', s, re.S)
assert m
s = s[:m.start()] + '''static s16 M545ColorStep(u8 cur, const M545Part *w, s32 k) {
    s16 v = (s16) ((f32) cur + (w->unk34 * (f32) (w->unk8[k] - w->unk4[k])));
    return v < 0 ? 0 : v > 0xFF ? 0xFF : v;
}

void fn_1_1F20(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    M545Part *work;
    s16 temp_r29;
    s16 var_r28;

    work = particleP->work;
    var_r31 = particleP->data;
    var_r31->time = 0;
    for (var_r28 = 0; var_r28 < (s16) particleP->maxCnt; var_r28++, var_r31++) {
        if (var_r31->scale != 0.0f) {
            var_r31->vel.x *= work[var_r28].unk18.x;
            var_r31->vel.y *= work[var_r28].unk18.y;
            var_r31->vel.z *= work[var_r28].unk18.z;
            VECAdd(&var_r31->vel, &var_r31->pos, &var_r31->pos);
            var_r31->vel.y += work[var_r28].unk24;
            var_r31->color.r = (u8) M545ColorStep(var_r31->color.r, &work[var_r28], 0);
            var_r31->color.g = (u8) M545ColorStep(var_r31->color.g, &work[var_r28], 1);
            var_r31->color.b = (u8) M545ColorStep(var_r31->color.b, &work[var_r28], 2);
            temp_r29 = (s16) ((f32) var_r31->color.a + work[var_r28].unk30);
            if (temp_r29 < 1) {
                var_r31->scale = 0.0f;
            }
            var_r31->color.a = (u8) temp_r29;
            if (var_r31->scale != 0.0f) {
                var_r31->scale = var_r31->scaleBase;
                var_r31->scaleBase += work[var_r28].unk2C;
                if (var_r31->scaleBase <= 0.01f) {
                    var_r31->scale = 0.0f;
                }
            }
            var_r31->time += 1;
        }
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}
''' + s[m.end():]
rep('memcpy(temp_r30->work + (var_r29 * 0x38), tmpl, 0x38);', 'memcpy((M545Part *) temp_r30->work + var_r29, tmpl, sizeof(M545Part));')
# DK has no MP5 motions: idle, raising the stack (0x5B), holding it (loops while a block is added), the pose frozen
# when a block lands (0x5E), win. The stack hangs off the hand hook, so DK needs a hand-overhead motion: MP4 132 (one arm
# raised) for all three carry slots (carry-walk 89 held it at his chest and the stack swallowed him; 118 starts crouched).
rep('unk0[var_r30], 0 /* TODO(mp5): MP4 motion for DK */)', 'unk0[var_r30], sDkMot[var_r30])')
rep('void fn_1_8454(void) {', 'static const s32 sDkMot[5] = { 0, 132, 132, 132, 23 };\n\nvoid fn_1_8454(void) {')
# DK's raised hand is level with his head (MP5 characters hold the stack above it): lift the stack so his face shows.
rep('''        Hu3DModelObjMtxGet(work->unk3C[var_r31 + 0x24].unk0, lbl_1_bss_C[var_r31].unk54[0], (f32 (*)[4]) lbl_1_bss_C[var_r31].unk20[0]);
''', '''        Hu3DModelObjMtxGet(work->unk3C[var_r31 + 0x24].unk0, lbl_1_bss_C[var_r31].unk54[0], (f32 (*)[4]) lbl_1_bss_C[var_r31].unk20[0]);
        if (work->unk4[var_r31].unk2 == 5) { lbl_1_bss_C[var_r31].unk20[1][3] += 35.0f; }
''')
open(p, 'w', encoding='utf-8', newline='\n').write(s)
