// ---- Triple Jump's four immediate-mode effect hooks and the code driving them (hand-written from the asm) ----
// Each hook sets its whole GX state (nothing is left to the previous draw). The fixed-function pipeline
// writes are GXBegin / GXPosition3f32 / GXColor4u8 / GXTexCoord2f32 / GXEnd on Aurora.

static void M514ColorPassInit(void)
{
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
}

static void M514Vtx(f32 x, f32 y, f32 z, GXColor color)
{
    GXPosition3f32(x, y, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
}

void fn_1_5C34(omObjData *arg0)
{
    s16 mdl;

    mdl = Hu3DHookFuncCreate(fn_1_5DE4);
    arg0->model[0] = mdl;
    Hu3DModelLayerSet(mdl, 6);
    Hu3DData[mdl].hookData = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Arc) * 3, MEMORY_DEFAULT_NUM);
    memset(Hu3DData[mdl].hookData, 0, sizeof(M514Arc) * 3);
}

void fn_1_5CD4(omObjData *arg0)
{
    M514Arc *arc;
    s32 i;

    arc = Hu3DData[arg0->model[0]].hookData;
    for (i = 0; i < 3; i++, arc++) {
        switch (arc->unk0) {
            case 1:
                arc->unk0++;
                arc->unk18 = 0.0f;
                arc->unk20 = 5.0f;
                arc->unk1C = 5.0f;
                arc->unk28 = 1.0f;
                break;
            case 3:
                arc->unk14 = (f32)((f64)arc->unk14 - 0.01);
                if (!(arc->unk14 > 0.0f)) {
                    arc->unk0 = 0;
                }
                break;
            default:
                break;
        }
    }
}

// the jump arcs: 24 segments of a half ring of 6 colour bands each, standing on the ground between the
// jump's start and end
void fn_1_5DE4(HU3DMODEL *modelP, Mtx mtx)
{
    M514Arc *arc;
    GXColor cols0[7];
    GXColor cols1[7];
    Vec radius;
    Mtx m;
    f32 cx, cz, scaleY, rad, width, step, ang, a0, a1, frac, r0, r1;
    s32 i, seg, ring, k, alpha0, alpha1;

    arc = modelP->hookData;
    M514ColorPassInit();
    memcpy(cols0, lbl_1_data_4D8, sizeof(cols0));
    memcpy(cols1, lbl_1_data_4D8, sizeof(cols1));
    for (i = 0; i < 3; i++, arc++) {
        if (arc->unk0 < 2) {
            continue;
        }
        cx = (f32)((f64)arc->unk2C + 0.5 * (f64)(arc->unk38 - arc->unk2C));
        cz = (f32)((f64)arc->unk34 + 0.5 * (f64)(arc->unk40 - arc->unk34));
        scaleY = arc->unk28;
        radius.x = arc->unk38 - cx;
        radius.y = arc->unk3C - 0.0f;
        radius.z = arc->unk40 - cz;
        rad = VECMag(&radius);
        width = arc->unkC;
        step = arc->unk1C / 24.0f;
        MTXIdentity(m);
        MTXTrans(m, cx, 0.0f, cz);
        MTXConcat(mtx, m, m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        ang = 0.0f;
        for (seg = 0; seg < 24; seg++) {
            a0 = (f32)(270.0 + (f64)(ang + arc->unk18));
            a1 = a0 + step;
            if (0.0 != (f64)arc->unk1C) {
                frac = (f32)(180.0 * (f64)(ang / arc->unk1C));
            } else {
                frac = 0.0f;
            }
            alpha0 = (s32)(128.0f * (f32)sin(3.141592653589793 * (f64)frac / 180.0) * arc->unk14);
            alpha1 = (s32)(128.0f * (f32)sin(3.141592653589793 * (f64)(frac + step) / 180.0) * arc->unk14);
            for (k = 0; k < 7; k++) {
                cols0[k].a = (u8)alpha0;
                cols1[k].a = (u8)alpha1;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 24);
            for (ring = 0; ring < 6; ring++) {
                r0 = rad - width * (f32)ring;
                if (r0 < 0.0f) {
                    r0 = 0.0f;
                }
                r1 = r0 - width;
                if (r1 < 0.0f) {
                    r1 = 0.0f;
                }
                M514Vtx(r0 * (f32)sin(3.141592653589793 * (f64)a0 / 180.0),
                    (f32)((f64)scaleY * ((f64)r0 * cos(3.141592653589793 * (f64)a0 / 180.0))), 0.0f, cols0[ring]);
                M514Vtx(r0 * (f32)sin(3.141592653589793 * (f64)a1 / 180.0),
                    (f32)((f64)scaleY * ((f64)r0 * cos(3.141592653589793 * (f64)a1 / 180.0))), 0.0f, cols1[ring]);
                M514Vtx(r1 * (f32)sin(3.141592653589793 * (f64)a1 / 180.0),
                    (f32)((f64)scaleY * ((f64)r1 * cos(3.141592653589793 * (f64)a1 / 180.0))), 0.0f, cols1[ring + 1]);
                M514Vtx(r1 * (f32)sin(3.141592653589793 * (f64)a0 / 180.0),
                    (f32)((f64)scaleY * ((f64)r1 * cos(3.141592653589793 * (f64)a0 / 180.0))), 0.0f, cols0[ring + 1]);
            }
            GXEnd();
            ang += step;
        }
    }
}

void fn_1_6588(omObjData *arg0)
{
    s16 mdl;
    M514Sparks *sparks;

    mdl = Hu3DHookFuncCreate(fn_1_68EC);
    arg0->model[1] = mdl;
    Hu3DModelLayerSet(mdl, 6);
    sparks = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Sparks), MEMORY_DEFAULT_NUM);
    Hu3DData[mdl].hookData = sparks;
    memset(sparks, 0, sizeof(M514Sparks));
    sparks->unk0 = HuSprAnimRead(HuDataSelHeapReadNum(0x480020, MEMORY_DEFAULT_NUM, HEAP_DATA));
}

void fn_1_6644(omObjData *arg0)
{
    M514Sparks *sparks;
    M514Spark *s;
    s32 i, t0, t1, t2;

    sparks = Hu3DData[arg0->model[1]].hookData;
    for (i = 0; i < 0x100; i++) {
        s = &sparks->unk4[i];
        if (s->unk0 == 0) {
            continue;
        }
        s->unk14 = (f32)((f64)s->unk14 - 0.5);
        s->unk1C = (f32)((f64)s->unk1C + 2.0);
        s->unk10.a = (u8)(s->unk10.a - 6);
        t0 = s->unk4;
        s->unk4 = t0 + 1;
        s->unk10.r = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t0 & 0x1F)) / 180.0));
        t1 = s->unk8;
        s->unk8 = t1 + 1;
        s->unk10.g = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t1 & 0x1F)) / 180.0));
        t2 = s->unkC;
        s->unkC = t2 + 1;
        s->unk10.b = (u8)(s32)(255.0 * sin(3.141592653589793 * (f64)(f32)(5.625 * (f64)(f32)(t2 & 0x1F)) / 180.0));
        if (s->unk14 <= 0.0f || s->unk10.a == 0) {
            s->unk0 = 0;
        }
    }
}

// the sparks: textured, additive quads (all in the z = 0 plane of the hook's matrix)
void fn_1_68EC(HU3DMODEL *modelP, Mtx mtx)
{
    M514Sparks *sparks;
    M514Spark *s;
    s32 i;
    f32 size, x, y;

    sparks = modelP->hookData;
    HuSprTexLoad(sparks->unk0, 0, 0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_OR);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    for (i = 0; i < 0x100; i++) {
        s = &sparks->unk4[i];
        if (s->unk0 == 0) {
            continue;
        }
        size = s->unk14;
        x = s->unk18;
        y = s->unk1C;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        M514Vtx(x - size, y - size, 0.0f, s->unk10);
        GXTexCoord2f32(0.0f, 0.0f);
        M514Vtx(x + size, y - size, 0.0f, s->unk10);
        GXTexCoord2f32(1.0f, 0.0f);
        M514Vtx(x + size, y + size, 0.0f, s->unk10);
        GXTexCoord2f32(1.0f, 1.0f);
        M514Vtx(x - size, y + size, 0.0f, s->unk10);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}

void fn_1_6C44(omObjData *arg0)
{
    s16 mdl;
    M514Foots *foots;
    s32 i;
    f64 deg;

    mdl = Hu3DHookFuncCreate(fn_1_6ED4);
    arg0->model[2] = mdl;
    Hu3DModelLayerSet(mdl, 4);
    foots = HuMemDirectMallocNum(HEAP_SYSTEM, sizeof(M514Foots), MEMORY_DEFAULT_NUM);
    Hu3DData[mdl].hookData = foots;
    memset(foots, 0, sizeof(M514Foots));
    deg = 0.0;
    for (i = 0; i < 0x10; i++) {
        foots->unk3800[i] = (f32)sin(3.141592653589793 * deg / 180.0);
        foots->unk3840[i] = (f32)cos(3.141592653589793 * deg / 180.0);
        deg = (f64)((f32)deg + 22.0f);
    }
}

void fn_1_6D7C(omObjData *arg0)
{
    M514Foots *foots;
    M514Foot *f;
    s32 i;

    foots = Hu3DData[arg0->model[2]].hookData;
    f = foots->unk0;
    for (i = 0; i < 0x200; i++, f++) {
        switch (f->unk0) {
            case 1:
                f->unk0++;
                f->unkC.r = f->unkC.g = f->unkC.b = f->unkC.a = 0;
                // fall through
            case 2:
                f->unkC.a += 4;
                if (f->unkC.a < 0x30) {
                    break;
                }
                f->unk0++;
                f->unk4 = 0;
                f->unkC.a = 0x30;
                // fall through
            case 3:
                f->unk4++;
                if ((f32)f->unk4 < 300.0f) {
                    break;
                }
                f->unk0++;
                // fall through
            case 4:
                f->unkC.a--;
                if (f->unkC.a > 4) {
                    break;
                }
                f->unk0 = 0;
                break;
            default:
                break;
        }
    }
}

// the footprints: translucent discs (a 16-sided fan) on the ground
void fn_1_6ED4(HU3DMODEL *modelP, Mtx mtx)
{
    M514Foots *foots;
    M514Foot *f;
    Mtx m;
    s32 i, k;
    f32 r;

    foots = modelP->hookData;
    M514ColorPassInit();
    f = foots->unk0;
    for (i = 0; i < 0x200; i++, f++) {
        if (f->unk0 < 2) {
            continue;
        }
        r = f->unk8;
        MTXIdentity(m);
        MTXTrans(m, f->unk10, f->unk14, f->unk18);
        MTXConcat(mtx, m, m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 18);
        M514Vtx(0.0f, 0.0f, 0.0f, f->unkC);
        for (k = 0; k < 0x10; k++) {
            M514Vtx(r * foots->unk3800[k], 0.0f, r * foots->unk3840[k], f->unkC);
        }
        M514Vtx(foots->unk3800[0] * r, 0.0f, foots->unk3840[0] * r, f->unkC);
        GXEnd();
    }
}

s32 fn_1_79F8(Vec *arg0, f32 farg0)
{
    M514Arc *arc;
    s32 i;

    arc = Hu3DData[lbl_1_bss_218->model[0]].hookData;
    for (i = 0; i < 3; i++, arc++) {
        if (arc->unk0 == 0) {
            arc->unk0++;
            arc->unk8 = 1;
            arc->unk2C = arg0->x;
            arc->unk30 = arg0->y;
            arc->unk34 = arg0->z;
            arc->unk38 = arg0->x;
            arc->unk3C = arg0->y;
            arc->unk40 = arg0->z;
            arc->unk10 = farg0;
            arc->unkC = farg0;
            arc->unk14 = 1.0f;
            arc->unk20 = 5.0f;
            arc->unk1C = 5.0f;
            arc->unk24 = 0.0f;
            arc->unk28 = 1.0f;
            return i;
        }
    }
    return -1;
}

void fn_1_7B8C(s32 arg0)
{
    M514Arc *arc;

    if (arg0 >= 0 && arg0 < 3) {
        arc = &((M514Arc *)Hu3DData[lbl_1_bss_218->model[0]].hookData)[arg0];
        if (arc->unk0 != 0) {
            arc->unk0 = 3;
        }
    }
}

void fn_1_585C(HU3DMODEL *modelP, Mtx mtx)
{
    Mtx m;
    GXColor color;

    color.r = (lbl_1_data_4D0 >> 24) & 0xFF;
    color.g = (lbl_1_data_4D0 >> 16) & 0xFF;
    color.b = (lbl_1_data_4D0 >> 8) & 0xFF;
    color.a = lbl_1_data_4D0 & 0xFF;
    MTXIdentity(m);
    MTXTrans(m, ((M514Goal *)lbl_1_bss_210->data)->unk0, 0.0f, 0.0f);
    MTXConcat(mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    M514ColorPassInit();
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    M514Vtx(-15.0f, 1.0f, -240.0f, color);
    M514Vtx(15.0f, 1.0f, -240.0f, color);
    M514Vtx(15.0f, 1.0f, 230.0f, color);
    M514Vtx(-15.0f, 1.0f, 230.0f, color);
    GXEnd();
}

// the layer hooks set the fog of the layers they precede
static void M514FogSet(s32 idx, GXFogType type)
{
    f32 fov, nnear, ffar;
    GXColor color;

    Hu3DCameraPerspectiveGet(1, &fov, &nnear, &ffar);
    color.r = lbl_1_data_4A0[idx].unk8;
    color.g = lbl_1_data_4A0[idx].unk9;
    color.b = lbl_1_data_4A0[idx].unkA;
    color.a = lbl_1_data_4A0[idx].unkB;
    GXSetFog(type, lbl_1_data_4A0[idx].unk0, lbl_1_data_4A0[idx].unk4 * lbl_1_bss_214, nnear, ffar, color);
}

void fn_1_54DC(s16 layerNo)
{
    M514FogSet(0, GX_FOG_LIN);
}

void fn_1_5574(s16 layerNo)
{
    M514FogSet(1, GX_FOG_LIN);
}

void fn_1_5610(s16 layerNo)
{
    M514FogSet(2, GX_FOG_LIN);
}

void fn_1_56AC(s16 layerNo)
{
    M514FogSet(0, GX_FOG_NONE);
}
