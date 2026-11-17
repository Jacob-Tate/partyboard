
// ---- DK pose tweak panel (see m548dll_tweak_head.inc) ----
static const char *const sDkTwName[DKTW_N] = { "R hand rot X", "R hand rot Y", "R hand rot Z", "L hand rot X", "L hand rot Y",
    "L hand rot Z", "head raise", "initial head x", "catch head y", "catch head x", "DK head rot X", "DK head rot Y",
    "DK head rot Z", "eyes forward", "eyes up", "eyes spread", "eyes size", "eyes rot X", "eyes rot Y", "eyes rot Z" };

// Adds `d` to every value of a rotation track (constant, linear/step pairs or bezier points).
static void Mp5DkTrackAdd(HSFTRACK *tr, f32 d)
{
    s32 k;
    switch (tr->curveType) {
        case HSF_CURVE_CONST:
            tr->value += d;
            break;
        case HSF_CURVE_LINEAR:
        case HSF_CURVE_STEP:
            for (k = 0; k < tr->numKeyframes; k++) {
                ((f32(*)[2])tr->data)[k][1] += d;
            }
            break;
        case HSF_CURVE_BEZIER:
            for (k = 0; k < tr->numKeyframes; k++) {
                ((f32(*)[4])tr->data)[k][1] += d;
            }
            break;
    }
}

void Mp5DkTweak(omObjData *obj)
{
    static f32 raiseApplied = 14.0f;
    static f32 applied[2][DKTW_N]; // rotation deltas already added to DK's carry motion, per player
    static s32 found[2][DKTW_N];
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
        if (sDkSel < 6 || (sDkSel >= 10 && sDkSel < 13) || sDkSel >= 17) {
            step = (held & PAD_TRIGGER_L) ? 1.0f : 5.0f; // rotations
        } else if (sDkSel >= 13 && sDkSel < 16) {
            step = (held & PAD_TRIGGER_L) ? 0.25f : 1.0f; // eye position
        } else if (sDkSel == 16) {
            step = (held & PAD_TRIGGER_L) ? 0.1f : 0.5f; // eye size
        }
        if ((rep & PAD_BUTTON_UP) && sDkSel > 0) {
            sDkSel--;
        }
        if ((rep & PAD_BUTTON_DOWN) && sDkSel < DKTW_N - 1) {
            sDkSel++;
        }
        if (rep & PAD_BUTTON_LEFT) {
            sDkTw[sDkSel] -= step;
        }
        if (rep & PAD_BUTTON_RIGHT) {
            sDkTw[sDkSel] += step;
        }
        if (down & PAD_BUTTON_X) {
            OSReport("DKTWEAK handR=(%.1f,%.1f,%.1f) handL=(%.1f,%.1f,%.1f) raise=%.1f initX=%.1f catchY=%.1f catchX=%.1f head=(%.1f,%.1f,%.1f) eyes fwd=%.2f up=%.2f spread=%.2f size=%.2f rot=(%.1f,%.1f,%.1f)\n",
                sDkTw[0], sDkTw[1], sDkTw[2], sDkTw[3], sDkTw[4], sDkTw[5], sDkTw[6], sDkTw[7], sDkTw[8], sDkTw[9], sDkTw[10],
                sDkTw[11], sDkTw[12], sDkTw[13], sDkTw[14], sDkTw[15], sDkTw[16], sDkTw[17], sDkTw[18], sDkTw[19]);
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
        // hand / head rotation: offsets on the rotation tracks of DK's carry motion
        hsf = Hu3DData[lbl_1_bss_3F0.unk3C[p + 0xC].unk0].hsf;
        mo = Hu3DMotion[lbl_1_bss_3F0.unk48[p][1]].hsf->motion;
        for (ti = 0; ti < mo->numTracks; ti++) {
            HSFTRACK *tr = &mo->track[ti];
            if (tr->type == HSF_TRACK_TRANSFORM && tr->target < hsf->objectNum) {
                s32 ch = tr->channel;
                s32 axis = ch - HSF_CHANNEL_ROTX;
                const char *name = hsf->object[tr->target].name;
                s32 idx = -1;
                f32 sign = 1.0f;
                if (ch >= HSF_CHANNEL_ROTX && ch <= HSF_CHANNEL_ROTZ) {
                    if (strcmp(name, "root_R_hand") == 0) {
                        idx = axis;
                    } else if (strcmp(name, "root_L_hand") == 0) {
                        idx = 3 + axis;
                    } else if (strcmp(name, "root_head") == 0) {
                        idx = 10 + axis;
                    } else if (strcmp(name, "donkey_L_eye") == 0 || strcmp(name, "donkey_R_eye") == 0) {
                        idx = 17 + axis;
                    }
                } else if (strcmp(name, "donkey_L_eye") == 0 || strcmp(name, "donkey_R_eye") == 0) {
                    if (ch >= HSF_CHANNEL_POSX && ch <= HSF_CHANNEL_POSZ) {
                        idx = 13 + (ch - HSF_CHANNEL_POSX);
                        if (idx == 15 && name[6] == 'R') {
                            sign = -1.0f; // spread: the eyes move apart
                        }
                    } else if (ch >= HSF_CHANNEL_SCALEX && ch <= HSF_CHANNEL_SCALEZ) {
                        idx = 16;
                    }
                }
                if (idx >= 0) {
                    if (!found[p][idx]) {
                        OSReport("DKTWEAK track for %d: %s ch %d curve %d n %d\n", idx, name, ch, tr->curveType, tr->numKeyframes);
                        found[p][idx] = 1;
                    }
                    Mp5DkTrackAdd(tr, sign * (sDkTw[idx] - applied[p][idx]));
                }
            }
        }
        for (i = 0; i < DKTW_N; i++) {
            applied[p][i] = sDkTw[i];
        }
    }
    raiseApplied = sDkTw[6];
    if (sDkTweak && lbl_1_bss_3F0.unkA0 != 1) {
        s32 turn = lbl_1_bss_3D0.unk6;
        if (lbl_1_bss_3D0.unk4 == 9 && !Mp5CharHasMotions(lbl_1_bss_3F0.unk4[0].unk2)) {
            // the first hold (DK is player 1): head x/y follow the values
            lbl_1_bss_44.x = -lbl_1_bss_384[0].unk10 + sDkTw[7];
            lbl_1_bss_44.y = lbl_1_bss_384[0].unk14;
        } else if (!Mp5CharHasMotions(lbl_1_bss_3F0.unk4[turn].unk2)) {
            // DK holds the head after a catch: place it like the catch does, so the values show up
            Vec pos;
            Hu3DModelObjPosGet(lbl_1_bss_3F0.unk3C[turn + 0xC].unk0, lbl_1_data_4AC, &pos);
            if (turn == 0) {
                lbl_1_bss_44.x = pos.x - (lbl_1_bss_384[0].unk10 - lbl_1_bss_384[0].unk0);
            } else {
                lbl_1_bss_44.x = pos.x + (lbl_1_bss_384[1].unk10 - lbl_1_bss_384[1].unk0);
            }
            lbl_1_bss_44.y = pos.y + (lbl_1_bss_384[turn].unk14 - lbl_1_bss_384[turn].unk4) + sDkTw[8];
            lbl_1_bss_44.x += sDkTw[9];
        }
    }
    if (sDkTweak) {
        GXColor color;
        color.a = 160;
        color.r = 0;
        color.g = 0;
        color.b = 64;
        printWin(404, 70, 232, 24 + 16 * (DKTW_N + 1), &color);
        fontcolor = FONT_COLOR_YELLOW;
        print8(410, 76, 0.85f, "DK TWEAK Z:close X:log L:fine");
        for (i = 0; i < DKTW_N; i++) {
            print8(410, 94 + 16 * i, 1.0f, "%s %s %.1f", (i == sDkSel) ? ">" : " ", sDkTwName[i], sDkTw[i]);
        }
    }
}
