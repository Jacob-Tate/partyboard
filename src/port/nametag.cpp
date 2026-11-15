#include "port/nametag.h"

#include "port/netplay.h"

#include <SDL3/SDL_filesystem.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "game/gamework_data.h"
#include "game/memory.h"
#include "game/sprite.h"
}

namespace {

constexpr int kScale = PARTYBOARD_NAMETAG_SCALE;
constexpr int kTextPx = 16 * kScale;  // letter size, in texels
constexpr int kMinTextPx = 11 * kScale; // below this, cut the name off instead of shrinking it more
constexpr int kMaxWidth = 100 * kScale; // fits under the face without reaching the coin/star counts
constexpr int kOutline = 2 * kScale;
constexpr int kPad = kOutline + kScale;
constexpr uint8_t kOutlineRgb[3] = { 16, 16, 40 };
constexpr char32_t kEllipsis = 0x2026;

FT_Library gLib = nullptr;
FT_Face gFace = nullptr;     // FOT-NewRodin (the game's UI typeface family)
FT_Face gFallback = nullptr; // Inter, for characters Rodin lacks
bool gTriedInit = false;

bool init_fonts()
{
    if (gTriedInit) {
        return gFace != nullptr;
    }
    gTriedInit = true;
    if (FT_Init_FreeType(&gLib) != 0) {
        return false;
    }
    const char *base = SDL_GetBasePath();
    const std::string res = std::string(base ? base : "") + "res/";
    if (FT_New_Face(gLib, (res + "FOT-NewRodin Pro DB.otf").c_str(), 0, &gFace) != 0) {
        std::printf("[nametag] can't load %sFOT-NewRodin Pro DB.otf\n", res.c_str());
        gFace = nullptr;
        return false;
    }
    if (FT_New_Face(gLib, (res + "Inter-Bold.ttf").c_str(), 0, &gFallback) != 0) {
        gFallback = nullptr;
    }
    return true;
}

std::u32string decode_utf8(const char *s)
{
    std::u32string out;
    const auto *p = reinterpret_cast<const unsigned char *>(s);
    while (*p) {
        char32_t cp;
        int extra;
        if (*p < 0x80) {
            cp = *p;
            extra = 0;
        } else if ((*p & 0xE0) == 0xC0) {
            cp = *p & 0x1F;
            extra = 1;
        } else if ((*p & 0xF0) == 0xE0) {
            cp = *p & 0x0F;
            extra = 2;
        } else if ((*p & 0xF8) == 0xF0) {
            cp = *p & 0x07;
            extra = 3;
        } else {
            p++;
            continue;
        }
        p++;
        for (int i = 0; i < extra && (*p & 0xC0) == 0x80; i++, p++) {
            cp = (cp << 6) | (*p & 0x3F);
        }
        out.push_back(cp);
    }
    return out;
}

struct Glyph {
    FT_Face face;
    FT_UInt index;
};

Glyph glyph_for(char32_t cp)
{
    if (const FT_UInt i = FT_Get_Char_Index(gFace, cp)) {
        return { gFace, i };
    }
    if (gFallback) {
        if (const FT_UInt i = FT_Get_Char_Index(gFallback, cp)) {
            return { gFallback, i };
        }
    }
    return { nullptr, 0 };
}

void set_size(int px)
{
    FT_Set_Pixel_Sizes(gFace, 0, px);
    if (gFallback) {
        FT_Set_Pixel_Sizes(gFallback, 0, px);
    }
}

// Pen advance of the whole string, in texels.
int measure(const std::u32string &text)
{
    int width = 0;
    for (char32_t cp : text) {
        const Glyph g = glyph_for(cp);
        if (g.face && FT_Load_Glyph(g.face, g.index, FT_LOAD_DEFAULT) == 0) {
            width += static_cast<int>(g.face->glyph->advance.x >> 6);
        }
    }
    return width;
}

// Top of 'A' and bottom of 'g' relative to the baseline, so every tag shares one baseline.
void vertical_extent(int &ascent, int &descent)
{
    ascent = kTextPx * 3 / 4;
    descent = kTextPx / 4;
    if (FT_Load_Char(gFace, 'A', FT_LOAD_RENDER) == 0) {
        ascent = gFace->glyph->bitmap_top;
    }
    if (FT_Load_Char(gFace, 'g', FT_LOAD_RENDER) == 0) {
        descent = static_cast<int>(gFace->glyph->bitmap.rows) - gFace->glyph->bitmap_top;
    }
}

// Square dilation of an 8-bit mask by `r` (the outline), separable.
std::vector<uint8_t> dilate(const std::vector<uint8_t> &src, int w, int h, int r)
{
    std::vector<uint8_t> tmp(src.size()), out(src.size());
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint8_t m = 0;
            for (int k = std::max(0, x - r); k <= std::min(w - 1, x + r); k++) {
                m = std::max(m, src[y * w + k]);
            }
            tmp[y * w + x] = m;
        }
    }
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint8_t m = 0;
            for (int k = std::max(0, y - r); k <= std::min(h - 1, y + r); k++) {
                m = std::max(m, tmp[k * w + x]);
            }
            out[y * w + x] = m;
        }
    }
    return out;
}

} // namespace

extern "C" ANIMDATA *partyboard_nametag_anim(int player)
{
    // `player` is a player record; the board orders those by turn order, and pad_idx is the seat it plays.
    const int port = GWPlayerCfg[player].pad_idx;
    const char *name = partyboard_netplay_port_name(port);
    if (!name || !name[0] || !init_fonts()) {
        return nullptr;
    }
    std::u32string text = decode_utf8(name);
    if (text.empty()) {
        return nullptr;
    }

    // Shrink long names down to kMinTextPx, then cut them off with an ellipsis.
    int px = kTextPx;
    set_size(px);
    while (measure(text) + 2 * kPad > kMaxWidth && px > kMinTextPx) {
        px -= kScale;
        set_size(px);
    }
    if (measure(text) + 2 * kPad > kMaxWidth) {
        while (!text.empty() && measure(text + kEllipsis) + 2 * kPad > kMaxWidth) {
            text.pop_back();
        }
        text += kEllipsis;
    }

    int ascent, descent;
    vertical_extent(ascent, descent);
    const int textW = measure(text);
    // RGBA8 textures are stored in 4x4 tiles.
    const int w = (textW + 2 * kPad + 3) & ~3;
    const int h = (ascent + descent + 2 * kPad + 3) & ~3;

    std::vector<uint8_t> mask(static_cast<size_t>(w) * h, 0);
    int pen = kPad;
    const int baseline = kPad + ascent;
    for (char32_t cp : text) {
        const Glyph g = glyph_for(cp);
        if (!g.face || FT_Load_Glyph(g.face, g.index, FT_LOAD_RENDER) != 0) {
            continue;
        }
        const FT_GlyphSlot slot = g.face->glyph;
        const FT_Bitmap &bm = slot->bitmap;
        for (unsigned row = 0; row < bm.rows; row++) {
            const int y = baseline - slot->bitmap_top + static_cast<int>(row);
            if (y < 0 || y >= h) {
                continue;
            }
            for (unsigned col = 0; col < bm.width; col++) {
                const int x = pen + slot->bitmap_left + static_cast<int>(col);
                if (x < 0 || x >= w) {
                    continue;
                }
                uint8_t &dst = mask[y * w + x];
                dst = std::max(dst, bm.buffer[row * bm.pitch + col]);
            }
        }
        pen += static_cast<int>(slot->advance.x >> 6);
    }
    const std::vector<uint8_t> outline = dilate(mask, w, h, kOutline);

    ANIMDATA *anim = HuSprAnimMake(static_cast<s16>(w), static_cast<s16>(h), ANIM_BMP_RGBA8);
    if (!anim) {
        return nullptr;
    }
    const size_t size = static_cast<size_t>(w) * h * 4;
    auto *data = static_cast<uint8_t *>(HuMemDirectMallocNum(HEAP_DATA, size, MEMORY_DEFAULT_NUM));
    if (!data) {
        HuSprAnimKill(anim);
        return nullptr;
    }
    anim->bmp->data = data;

    // GX RGBA8: 4x4 tiles of 64 bytes, first the 16 AR pairs, then the 16 GB pairs.
    uint8_t *tile = data;
    for (int ty = 0; ty < h; ty += 4) {
        for (int tx = 0; tx < w; tx += 4) {
            for (int i = 0; i < 16; i++) {
                const int x = tx + i % 4, y = ty + i / 4;
                const uint8_t t = mask[y * w + x]; // white text over the outline colour
                const uint8_t a = std::max(outline[y * w + x], t);
                uint8_t rgb[3];
                for (int k = 0; k < 3; k++) {
                    rgb[k] = static_cast<uint8_t>((kOutlineRgb[k] * (255 - t) + 255 * t) / 255);
                }
                tile[2 * i] = a;
                tile[2 * i + 1] = rgb[0];
                tile[32 + 2 * i] = rgb[1];
                tile[32 + 2 * i + 1] = rgb[2];
            }
            tile += 64;
        }
    }
    return anim;
}
