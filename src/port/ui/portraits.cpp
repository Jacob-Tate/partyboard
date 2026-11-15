#include "portraits.hpp"

#include "port/settings.h"

#include <aurora/rmlui.hpp>
#include <nod.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

extern "C" {
#include "game/data.h" // HuDecodeData
}

namespace partyboard::ui::portraits {
namespace {

    constexpr int kChars = 8;
    constexpr int kFirstEntry = 0x2E; // board.bin: one face sprite per character id, in id order
    constexpr int kSize = 64;         // each sprite stacks 64x64 expressions; the top one is neutral
    constexpr int kFormatCmpr = 10;   // ANIM_BMP_CMPR

    struct Portrait {
        std::vector<std::byte> rgba; // kSize * kSize * 4, empty if missing
    };

    std::array<Portrait, kChars> gPortraits;
    std::string gLoadedFrom; // disc image the portraits came from ("" = none yet)
    std::string gFailedFor;  // disc image we already failed on, to avoid retrying every frame
    bool gProviderRegistered = false;

    uint32_t be32(const uint8_t *p)
    {
        return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3];
    }
    uint16_t be16(const uint8_t *p)
    {
        return uint16_t((p[0] << 8) | p[1]);
    }

    std::optional<std::vector<uint8_t>> read_disc_file(const std::string &iso, const char *path)
    {
        NodHandle *disc = nullptr;
        NodHandle *partition = nullptr;
        NodHandle *file = nullptr;
        std::optional<std::vector<uint8_t>> result;
        if (nod_disc_open(iso.c_str(), nullptr, &disc) == NOD_RESULT_OK &&
            nod_disc_open_partition(disc, 0, nullptr, &partition) == NOD_RESULT_OK) {
            NodNodeKind kind;
            uint32_t length = 0;
            const uint32_t index = nod_partition_find_file(partition, path, &kind, &length);
            if (index != NOD_FST_STOP && nod_partition_open_file(partition, index, &file) == NOD_RESULT_OK) {
                std::vector<uint8_t> data(length);
                size_t got = 0;
                while (got < length) {
                    const int64_t n = nod_read(file, data.data() + got, length - got);
                    if (n <= 0) {
                        break;
                    }
                    got += static_cast<size_t>(n);
                }
                if (got == length) {
                    result = std::move(data);
                }
            }
        }
        nod_free(file);
        nod_free(partition);
        nod_free(disc);
        return result;
    }

    // One archive entry, decompressed (archive: u32 count, u32 offsets[count]; entry: u32 rawLen,
    // u32 decodeType, data).
    std::optional<std::vector<uint8_t>> archive_entry(std::vector<uint8_t> &archive, int num)
    {
        if (archive.size() < 8 || static_cast<uint32_t>(num) >= be32(archive.data())) {
            return std::nullopt;
        }
        const uint32_t offset = be32(archive.data() + 4 + num * 4);
        if (offset + 8 > archive.size()) {
            return std::nullopt;
        }
        const uint32_t rawLen = be32(archive.data() + offset);
        const uint32_t decodeType = be32(archive.data() + offset + 4);
        if (rawLen == 0 || rawLen > 4 * 1024 * 1024) {
            return std::nullopt;
        }
        std::vector<uint8_t> out(rawLen + 1024); // slack: the decoders may write a little past the end
        HuDecodeData(archive.data() + offset + 8, out.data(), rawLen, static_cast<s32>(decodeType));
        out.resize(rawLen);
        return out;
    }

    void rgb565(uint16_t v, uint8_t out[3])
    {
        const uint8_t r = (v >> 11) & 31, g = (v >> 5) & 63, b = v & 31;
        out[0] = uint8_t(r << 3 | r >> 2);
        out[1] = uint8_t(g << 2 | g >> 4);
        out[2] = uint8_t(b << 3 | b >> 2);
    }

    // Decodes the top kSize x kSize of a GameCube CMPR texture (8x8 tiles of four DXT1 blocks).
    bool decode_cmpr_top(const uint8_t *src, size_t srcLen, int width, std::vector<std::byte> &rgba)
    {
        const size_t needed = static_cast<size_t>(width / 8) * (kSize / 8) * 32;
        if (width < kSize || width % 8 || srcLen < needed) {
            return false;
        }
        rgba.assign(kSize * kSize * 4, std::byte {0});
        const uint8_t *p = src;
        for (int ty = 0; ty < kSize; ty += 8) {
            for (int tx = 0; tx < width; tx += 8) {
                for (int sub = 0; sub < 4; sub++, p += 8) {
                    const uint16_t c0 = be16(p), c1 = be16(p + 2);
                    const uint32_t bits = be32(p + 4);
                    uint8_t pal[4][4];
                    rgb565(c0, pal[0]);
                    rgb565(c1, pal[1]);
                    pal[0][3] = pal[1][3] = pal[2][3] = 255;
                    pal[3][3] = c0 > c1 ? 255 : 0;
                    for (int k = 0; k < 3; k++) {
                        if (c0 > c1) {
                            pal[2][k] = uint8_t((2 * pal[0][k] + pal[1][k]) / 3);
                            pal[3][k] = uint8_t((pal[0][k] + 2 * pal[1][k]) / 3);
                        } else {
                            pal[2][k] = uint8_t((pal[0][k] + pal[1][k]) / 2);
                            pal[3][k] = 0;
                        }
                    }
                    const int bx = tx + (sub & 1) * 4, by = ty + (sub >> 1) * 4;
                    for (int i = 0; i < 16; i++) {
                        const int x = bx + i % 4, y = by + i / 4;
                        if (x >= kSize) {
                            continue;
                        }
                        const uint8_t *c = pal[(bits >> (30 - 2 * i)) & 3];
                        std::byte *dst = &rgba[(static_cast<size_t>(y) * kSize + x) * 4];
                        for (int k = 0; k < 4; k++) {
                            dst[k] = std::byte {c[k]};
                        }
                    }
                }
            }
        }
        return true;
    }

    // The first bitmap of an ANIM sprite file (big-endian header: s16 bankNum, patNum, bmpNum, useNum,
    // u32 bank, pat, bmp; bitmap: u8 pixSize, u8 format, s16 palNum, s16 w, s16 h, u32 size, u32 pal,
    // u32 data).
    bool decode_face(const std::vector<uint8_t> &anim, std::vector<std::byte> &rgba)
    {
        if (anim.size() < 20 || be16(anim.data() + 4) < 1) {
            return false;
        }
        const uint32_t bmp = be32(anim.data() + 16);
        if (bmp + 20 > anim.size()) {
            return false;
        }
        const uint8_t *b = anim.data() + bmp;
        const int format = b[1] & 0xF;
        const int width = be16(b + 4);
        const uint32_t data = be32(b + 16);
        if (format != kFormatCmpr || data >= anim.size()) {
            return false;
        }
        return decode_cmpr_top(anim.data() + data, anim.size() - data, width, rgba);
    }

    std::optional<aurora::rmlui::RuntimeTexture> provide(std::string_view source)
    {
        // "portrait://N"
        const auto pos = source.find("://");
        if (pos == std::string_view::npos || pos + 4 != source.size()) {
            return std::nullopt;
        }
        const int c = source[pos + 3] - '0';
        if (c < 0 || c >= kChars || gPortraits[c].rgba.empty()) {
            return std::nullopt;
        }
        aurora::rmlui::RuntimeTexture tex;
        tex.width = kSize;
        tex.height = kSize;
        tex.rgba8 = gPortraits[c].rgba;
        tex.generateMipmaps = true; // drawn smaller than 64 px
        return tex;
    }

} // namespace

bool ensure_loaded()
{
    const std::string iso = getSettings().backend.isoPath.getValue();
    if (iso.empty()) {
        return false;
    }
    if (iso == gLoadedFrom) {
        return true;
    }
    if (iso == gFailedFor) {
        return false;
    }
    auto archive = read_disc_file(iso, "data/board.bin");
    int loaded = 0;
    std::array<Portrait, kChars> portraits;
    if (archive) {
        for (int c = 0; c < kChars; c++) {
            if (auto anim = archive_entry(*archive, kFirstEntry + c); anim && decode_face(*anim, portraits[c].rgba)) {
                loaded++;
            }
        }
    }
    if (loaded != kChars) {
        std::printf("[ui] character portraits unavailable (%d of %d read from the disc image)\n", loaded, kChars);
        gFailedFor = iso;
        return false;
    }
    gPortraits = std::move(portraits);
    gLoadedFrom = iso;
    gFailedFor.clear();
    if (!gProviderRegistered) {
        aurora::rmlui::register_texture_provider("portrait", provide);
        gProviderRegistered = true;
    }
    return true;
}

} // namespace partyboard::ui::portraits
