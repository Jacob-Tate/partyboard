
// ---- DK pose tweak panel (see m548dll_tweak_head.inc) ----
static const char *const sDkTwName[9] = { "R hand rot X", "R hand rot Y", "R hand rot Z", "L hand rot X", "L hand rot Y",
    "L hand rot Z", "head raise", "initial head x", "catch head y" };

void Mp5DkTweak(omObjData *obj)
{
    static f32 raiseApplied = 20.0f;
    static f32 base[2][2][3]; // [player][R/L][X/Y/Z]
    static s32 haveBase[2][2][3];
    s32 i, p;
    u16 down = 0, rep = 0, held = 0;
    for (i = 0; i < 4; i++) {
        down |= HuPadBtnDown[i];
        rep |= HuPadBtnRep[i];
        held |= HuPadBtn[i];
    }
    if (down & PAD_TRIGGER_Z) {
        sDkTweak ^= 1;
    }
    {
        static int frame; // test hook: PB_TWEAK_OPEN=<frame> opens the panel by itself
        if (getenv("PB_TWEAK_OPEN") && ++frame == atoi(getenv("PB_TWEAK_OPEN"))) {
            sDkTweak = 1;
        }
    }
    if (sDkTweak) {
        f32 step = (held & PAD_TRIGGER_L) ? 0.5f : 2.0f;
        if (sDkSel < 6) {
            step = (held & PAD_TRIGGER_L) ? 1.0f : 5.0f;
        }
        if ((rep & PAD_BUTTON_UP) && sDkSel > 0) {
            sDkSel--;
        }
        if ((rep & PAD_BUTTON_DOWN) && sDkSel < 8) {
            sDkSel++;
        }
        if (rep & PAD_BUTTON_LEFT) {
            sDkTw[sDkSel] -= step;
        }
        if (rep & PAD_BUTTON_RIGHT) {
            sDkTw[sDkSel] += step;
        }
        if (down & PAD_BUTTON_X) {
            OSReport("DKTWEAK handR=(%.1f,%.1f,%.1f) handL=(%.1f,%.1f,%.1f) raise=%.1f initX=%.1f catchY=%.1f\n", sDkTw[0], sDkTw[1],
                sDkTw[2], sDkTw[3], sDkTw[4], sDkTw[5], sDkTw[6], sDkTw[7], sDkTw[8]);
        }
    }
    MgTimerPauseSet(lbl_1_bss_54, sDkTweak);
    if (!sDkMotReady) {
        return;
    }
    for (p = 0; p < 2; p++) {
        HSFDATA *hsf;
        HSFMOTION *mo;
        s32 ti;
        if (Mp5CharHasMotions(lbl_1_bss_3F0.unk4[p].unk2)) {
            continue;
        }
        // held head height, live
        lbl_1_bss_384[p].unk14 += sDkTw[6] - raiseApplied;
        // hand rotation: offsets on the constant rotation tracks of DK's carry motion
        hsf = Hu3DData[lbl_1_bss_3F0.unk3C[p + 0xC].unk0].hsf;
        mo = Hu3DMotion[lbl_1_bss_3F0.unk48[p][1]].hsf->motion;
        for (ti = 0; ti < mo->numTracks; ti++) {
            HSFTRACK *tr = &mo->track[ti];
            if (tr->type == HSF_TRACK_TRANSFORM && tr->curveType == HSF_CURVE_CONST && tr->channel >= HSF_CHANNEL_ROTX
                && tr->channel <= HSF_CHANNEL_ROTZ && tr->target < hsf->objectNum) {
                s32 hand = -1;
                s32 axis = tr->channel - HSF_CHANNEL_ROTX;
                if (strcmp(hsf->object[tr->target].name, "root_R_hand") == 0) {
                    hand = 0;
                } else if (strcmp(hsf->object[tr->target].name, "root_L_hand") == 0) {
                    hand = 1;
                }
                if (hand >= 0) {
                    if (!haveBase[p][hand][axis]) {
                        base[p][hand][axis] = tr->value;
                        haveBase[p][hand][axis] = 1;
                    }
                    tr->value = base[p][hand][axis] + sDkTw[hand * 3 + axis];
                }
            }
        }
    }
    raiseApplied = sDkTw[6];
    // the first hold (DK is player 1): head x/y follow the values
    if (lbl_1_bss_3D0.unk4 == 9 && !Mp5CharHasMotions(lbl_1_bss_3F0.unk4[0].unk2)) {
        lbl_1_bss_44.x = -lbl_1_bss_384[0].unk10 + sDkTw[7];
        lbl_1_bss_44.y = lbl_1_bss_384[0].unk14;
    }
    if (sDkTweak) {
        GXColor color;
        color.a = 160;
        color.r = 0;
        color.g = 0;
        color.b = 64;
        printWin(404, 70, 232, 24 + 16 * 10, &color);
        fontcolor = FONT_COLOR_YELLOW;
        print8(410, 76, 0.85f, "DK TWEAK Z:close X:log L:fine");
        for (i = 0; i < 9; i++) {
            print8(410, 94 + 16 * i, 1.0f, "%s %s %.1f", (i == sDkSel) ? ">" : " ", sDkTwName[i], sDkTw[i]);
        }
    }
}
