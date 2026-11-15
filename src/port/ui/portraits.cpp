#include "portraits.hpp"

#include "port/settings.h"

#include <aurora/rmlui.hpp>
#include <nod.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

extern "C" {
#include "game/data.h" // HuDecodeData
}

namespace partyboard::ui::portraits {
namespace {

    constexpr int kFormatC8 = 3;    // ANIM_BMP_C8 (RGB5A3 palette)
    constexpr int kFormatCmpr = 10; // ANIM_BMP_CMPR

    struct Image {
        int width = 0;
        int height = 0;
        std::vector<std::byte> rgba;
    };

    // One family of pictures served under a URL scheme ("portrait://N").
    struct ImageSet {
        const char *scheme;
        std::vector<Image> images;
        std::string loadedFrom; // disc image the pictures came from
        std::string failedFor;  // disc image we already failed on, so we don't retry every frame
        bool registered = false;
    };

    ImageSet gPortraits { "portrait" };
    ImageSet gBoards { "board" };

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
        if (rawLen == 0 || rawLen > 8 * 1024 * 1024 || decodeType > DATA_DECODE_RLE) {
            return std::nullopt;
        }
        std::vector<uint8_t> out(rawLen + 1024); // slack: the decoders may write a little past the end
        HuDecodeData(archive.data() + offset + 8, out.data(), rawLen, static_cast<s32>(decodeType));
        out.resize(rawLen);
        return out;
    }

    void put(Image &img, int x, int y, const uint8_t c[4])
    {
        if (x < img.width && y < img.height) {
            std::byte *dst = &img.rgba[(static_cast<size_t>(y) * img.width + x) * 4];
            for (int k = 0; k < 4; k++) {
                dst[k] = std::byte {c[k]};
            }
        }
    }

    void rgb565(uint16_t v, uint8_t out[3])
    {
        const uint8_t r = (v >> 11) & 31, g = (v >> 5) & 63, b = v & 31;
        out[0] = uint8_t(r << 3 | r >> 2);
        out[1] = uint8_t(g << 2 | g >> 4);
        out[2] = uint8_t(b << 3 | b >> 2);
    }

    void rgb5a3(uint16_t v, uint8_t out[4])
    {
        if (v & 0x8000) {
            const uint8_t r = (v >> 10) & 31, g = (v >> 5) & 31, b = v & 31;
            out[0] = uint8_t(r << 3 | r >> 2);
            out[1] = uint8_t(g << 3 | g >> 2);
            out[2] = uint8_t(b << 3 | b >> 2);
            out[3] = 255;
        } else {
            out[0] = uint8_t(((v >> 8) & 15) * 17);
            out[1] = uint8_t(((v >> 4) & 15) * 17);
            out[2] = uint8_t((v & 15) * 17);
            out[3] = uint8_t(((v >> 12) & 7) * 255 / 7);
        }
    }

    // GameCube CMPR: 8x8 tiles of four DXT1 blocks. Decodes the top `rows` rows only.
    bool decode_cmpr(const uint8_t *src, size_t srcLen, int width, int rows, Image &img)
    {
        if (width % 8 || rows % 8 || srcLen < static_cast<size_t>(width / 8) * (rows / 8) * 32) {
            return false;
        }
        img.width = width;
        img.height = rows;
        img.rgba.assign(static_cast<size_t>(width) * rows * 4, std::byte {0});
        const uint8_t *p = src;
        for (int ty = 0; ty < rows; ty += 8) {
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
                        put(img, bx + i % 4, by + i / 4, pal[(bits >> (30 - 2 * i)) & 3]);
                    }
                }
            }
        }
        return true;
    }

    // GameCube C8: 8x4 tiles of 8-bit palette indices, RGB5A3 palette.
    bool decode_c8(const uint8_t *src, size_t srcLen, const uint8_t *pal, int palNum, int width, int height, Image &img)
    {
        const int tilesX = (width + 7) / 8, tilesY = (height + 3) / 4;
        if (palNum <= 0 || palNum > 256 || srcLen < static_cast<size_t>(tilesX) * tilesY * 32) {
            return false;
        }
        std::vector<std::array<uint8_t, 4>> palette(256, std::array<uint8_t, 4> {0, 0, 0, 0});
        for (int i = 0; i < palNum; i++) {
            rgb5a3(be16(pal + 2 * i), palette[i].data());
        }
        img.width = width;
        img.height = height;
        img.rgba.assign(static_cast<size_t>(width) * height * 4, std::byte {0});
        const uint8_t *p = src;
        for (int ty = 0; ty < tilesY * 4; ty += 4) {
            for (int tx = 0; tx < tilesX * 8; tx += 8) {
                for (int i = 0; i < 32; i++) {
                    put(img, tx + i % 8, ty + i / 8, palette[*p++].data());
                }
            }
        }
        return true;
    }

    // Bitmap `index` of an ANIM sprite file. Big-endian header: s16 bankNum, patNum, bmpNum, useNum,
    // u32 bank, pat, bmp. Bitmap (20 bytes): u8 pixSize, u8 format, s16 palNum, s16 w, s16 h,
    // u32 size, u32 pal, u32 data. maxRows > 0 keeps only the top rows (stacked frames).
    bool decode_bitmap(const std::vector<uint8_t> &anim, int index, int maxRows, Image &img)
    {
        if (anim.size() < 20 || index >= static_cast<int16_t>(be16(anim.data() + 4))) {
            return false;
        }
        const uint32_t bmp = be32(anim.data() + 16) + index * 20;
        if (bmp + 20 > anim.size()) {
            return false;
        }
        const uint8_t *b = anim.data() + bmp;
        const int format = b[1] & 0xF;
        const int palNum = static_cast<int16_t>(be16(b + 2));
        const int width = static_cast<int16_t>(be16(b + 4));
        const int height = static_cast<int16_t>(be16(b + 6));
        const uint32_t pal = be32(b + 12), data = be32(b + 16);
        if (width <= 0 || height <= 0 || width > 1024 || height > 1024 || data >= anim.size()) {
            return false;
        }
        const int rows = maxRows > 0 && maxRows < height ? maxRows : height;
        if (format == kFormatCmpr) {
            return decode_cmpr(anim.data() + data, anim.size() - data, width, rows, img);
        }
        if (format == kFormatC8 && pal + 2 * static_cast<size_t>(palNum) <= anim.size()) {
            return decode_c8(anim.data() + data, anim.size() - data, anim.data() + pal, palNum, width, rows, img);
        }
        return false;
    }

    std::optional<aurora::rmlui::RuntimeTexture> serve(const ImageSet &set, std::string_view source)
    {
        // "<scheme>://N"
        const auto pos = source.find("://");
        if (pos == std::string_view::npos || pos + 4 != source.size()) {
            return std::nullopt;
        }
        const int n = source[pos + 3] - '0';
        if (n < 0 || n >= static_cast<int>(set.images.size()) || set.images[n].rgba.empty()) {
            return std::nullopt;
        }
        const Image &img = set.images[n];
        aurora::rmlui::RuntimeTexture tex;
        tex.width = static_cast<uint32_t>(img.width);
        tex.height = static_cast<uint32_t>(img.height);
        tex.rgba8 = img.rgba;
        tex.generateMipmaps = true; // drawn smaller than their native size
        return tex;
    }

    // Loads `set` with `load` (which fills the images from the disc image) once per disc image.
    bool ensure(ImageSet &set, const std::function<bool(const std::string &, std::vector<Image> &)> &load)
    {
        const std::string iso = getSettings().backend.isoPath.getValue();
        if (iso.empty()) {
            return false;
        }
        if (iso == set.loadedFrom) {
            return true;
        }
        if (iso == set.failedFor) {
            return false;
        }
        std::vector<Image> images;
        if (!load(iso, images)) {
            std::printf("[ui] %s pictures unavailable: couldn't read them from the disc image\n", set.scheme);
            set.failedFor = iso;
            return false;
        }
        set.images = std::move(images);
        set.loadedFrom = iso;
        set.failedFor.clear();
        if (!set.registered) {
            aurora::rmlui::register_texture_provider(set.scheme,
                [&set](std::string_view source) { return serve(set, source); });
            set.registered = true;
        }
        return true;
    }

} // namespace

bool ensure_loaded()
{
    return ensure(gPortraits, [](const std::string &iso, std::vector<Image> &images) {
        constexpr int kFirstEntry = 0x2E; // one face sprite per character id, in id order
        constexpr int kFrame = 64;        // each stacks three 64x64 expressions; the top one is neutral
        auto archive = read_disc_file(iso, "data/board.bin");
        if (!archive) {
            return false;
        }
        images.resize(8);
        for (int c = 0; c < 8; c++) {
            auto anim = archive_entry(*archive, kFirstEntry + c);
            if (!anim || !decode_bitmap(*anim, 0, kFrame, images[c]) || images[c].width != kFrame) {
                return false;
            }
        }
        return true;
    });
}

bool ensure_boards_loaded()
{
    return ensure(gBoards, [](const std::string &iso, std::vector<Image> &images) {
        // Party menu board pictures: entry 0x3C holds frames (bitmaps 0-4) and boards 0-4
        // (bitmaps 5-9); Bowser's board, unlocked later in the game, is entry 0x3E bitmap 1.
        auto archive = read_disc_file(iso, "data/ment.bin");
        if (!archive) {
            return false;
        }
        auto main = archive_entry(*archive, 0x3C);
        auto bowser = archive_entry(*archive, 0x3E);
        if (!main || !bowser) {
            return false;
        }
        images.resize(6);
        for (int board = 0; board < 5; board++) {
            if (!decode_bitmap(*main, 5 + board, 0, images[board])) {
                return false;
            }
        }
        return decode_bitmap(*bowser, 1, 0, images[5]);
    });
}

} // namespace partyboard::ui::portraits
