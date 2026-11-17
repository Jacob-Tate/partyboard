"""Hand fixes for the m544 draft (called by m544dll.sh with the draft path)."""
import re, sys
p = sys.argv[1]
s = open(p, encoding='utf-8').read()

def rep(a, b, count=1):
    global s
    assert a in s, a
    s = s.replace(a, b, count)

def replace_func(name, nxt, new):
    """Replace the body of function `name` (up to the start of the function that follows it) with `new`."""
    global s
    m = re.search(r'^[^\n]*\b' + name + r'\([^;\n]*\) \{.*?\n\}\n(?=\n*[^\n]*\b' + nxt + r'\([^;\n]*\) \{)', s, re.S | re.M)
    assert m, name
    s = s[:m.start()] + new + s[m.end():]

# the Shy Guy's animation requests: &anim[0] + 0x54 bytes
rep('temp_r31 = lbl_1_bss_914->unk74 + 0x54;', 'temp_r31 = &lbl_1_bss_914->unk74[1];')
rep('temp_r31_2 = temp_r31 + 0x54;', 'temp_r31_2 = &lbl_1_bss_914->unk74[2];')

# per-player motion tables are s16[7] rows, character tables are in MP5 character order
s = s.replace('lbl_1_bss_130[0][var_r31]', 'lbl_1_bss_130[var_r31]').replace('lbl_1_bss_130[0][2]', 'lbl_1_bss_130[2]')
rep('fn_1_A3F0(var_r31, &lbl_1_data_28[lbl_1_bss_530.unk4[var_r31].unk2]);',
    'fn_1_A3F0(var_r31, &lbl_1_data_28[Mp5CharNo(lbl_1_bss_530.unk4[var_r31].unk2)]);')

# particles: the work is an array of templates
rep('memcpy(temp_r30->work + (var_r29 * 0x38), tmpl, 0x38);', 'memcpy((M544Part *) temp_r30->work + var_r29, tmpl, sizeof(M544Part));')
replace_func('fn_1_30B8', 'fn_1_34D0', '''static s16 M544ColorStep(u8 cur, const M544Part *w, s32 k) {
    s16 v = (s16) ((f32) cur + (w->unk34 * (f32) (w->unk8[k] - w->unk4[k])));
    return v < 0 ? 0 : v > 0xFF ? 0xFF : v;
}

void fn_1_30B8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx) {
    HU3DPARTICLEDATA *var_r31;
    M544Part *work;
    s16 temp_r29;
    s16 var_r28;

    work = particleP->work;
    var_r31 = particleP->data;
    var_r31->time = 0;
    for (var_r28 = 0; var_r28 < (s16) particleP->maxCnt; var_r28++, var_r31++) {
        if (var_r31->scale > 0.0f) {
            var_r31->vel.x *= work[var_r28].unk18.x;
            var_r31->vel.y *= work[var_r28].unk18.y;
            var_r31->vel.z *= work[var_r28].unk18.z;
            VECAdd(&var_r31->vel, &var_r31->pos, &var_r31->pos);
            var_r31->vel.y += work[var_r28].unk24;
            var_r31->color.r = (u8) M544ColorStep(var_r31->color.r, &work[var_r28], 0);
            var_r31->color.g = (u8) M544ColorStep(var_r31->color.g, &work[var_r28], 1);
            var_r31->color.b = (u8) M544ColorStep(var_r31->color.b, &work[var_r28], 2);
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

''')
rep('Hu3DData[lbl_1_bss_824].hookData->unk48->unk2C = 0.0f;', '((HU3DPARTICLE *) Hu3DData[lbl_1_bss_824].hookData)->data[0].scale = 0.0f;')

# the card-reveal sparkle: a particle flying from the hand of the card's owner (tables of start / end offsets per character)
replace_func('fn_1_35DC', 'fn_1_39E8', '''void fn_1_35DC(s16 player) {
    Vec sp8;
    Vec sp14;
    const f32 *tbl;
    M544Model *mdl;
    s16 chr;
    f32 scale;

    chr = lbl_1_bss_914->unk4[player].unk2;
    if (chr >= 0xD) {
        chr = 6;
    }
    if (player >= 2) {
        player = (s16) ((s32) (lbl_1_bss_D0.unk20 & 2) >> 1);
    }
    mdl = &lbl_1_bss_914->unk58[player + 0x20];
    if (player == 0) {
        tbl = lbl_1_rodata_D8[chr];
        scale = 35.0f;
    } else {
        tbl = lbl_1_rodata_210[chr];
        scale = 50.0f;
    }
    sp14.x = mdl->unk4.x + tbl[0];
    sp14.y = mdl->unk4.y + tbl[1] + lbl_1_rodata_A4[chr];
    sp14.z = mdl->unk4.z + tbl[2];
    sp8.x = mdl->unk4.x + tbl[3];
    sp8.y = mdl->unk4.y + tbl[4] + lbl_1_rodata_A4[chr];
    sp8.z = mdl->unk4.z + tbl[5];
    fn_1_39E8(&sp14, &sp8, scale);
}

''')
replace_func('fn_1_39E8', 'fn_1_3AD4', '''void fn_1_39E8(Vec *from, Vec *to, f32 scale) {
    HU3DPARTICLEDATA *data;

    data = ((HU3DPARTICLE *) Hu3DData[lbl_1_bss_824].hookData)->data;
    data->time = 0;
    data->parManId = 0;
    data->pos = *from;
    data->vel = *from;
    data->accel = *to;
    data->color.r = 0xFF;
    data->color.g = 0xFF;
    data->color.b = 0xFF;
    data->color.a = 0xFF;
    data->scale = scale;
    if (data->scale != 0.0f) {
        lbl_1_bss_D0.unk2C = 1;
    }
}

''')

open(p, 'w', encoding='utf-8', newline='\n').write(s)
