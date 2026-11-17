#include "port/mp5disc.h"
#include "port/netplay.h"

#include <aurora/dvd.h>
#include <nod.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <mutex>
#include <string>
#include <vector>

// Serves files of a Mario Party 5 disc image through aurora's DVD overlay, under /mp5/<disc path>.
// Reads go straight to the image (nod handles the RVZ/ISO/... decoding), so nothing is unpacked to disk.

namespace {

struct Mp5File {
    std::string path; // "/mp5/data/m507.bin"
    uint32_t fstIndex;
    uint32_t size;
    const std::vector<uint8_t> *mem = nullptr; // set: served from memory (DK mod files), not from the disc
};

// An open overlay file: a nod handle for disc files, or a position in a file kept in memory.
struct OpenFile {
    NodHandle *nod;
    const std::vector<uint8_t> *mem;
    int64_t pos;
};

// The optional "DK in Mario Party 5" mod (by OverBoo): it puts DK in Boo's place, so its teresa.bin and
// teresamot.bin are DK's MP5 <char>.bin / <char>mot.bin, same entry layout as mario.bin / mariomot.bin, rigged
// to the same skeleton as MP4's DK. Served as /mp5dk/data/teresa.bin and /mp5dk/data/teresamot.bin.
std::string sDkModDir;
std::vector<uint8_t> sDkModData[2];
bool sDkMod = false;

NodHandle *sDisc = nullptr;
NodHandle *sPartition = nullptr;
std::mutex sOpenMutex; // nod partition handles are not documented as thread safe for opens
std::vector<Mp5File> sFiles;
bool sMounted = false;

struct FstWalk {
    std::vector<std::pair<std::string, uint32_t>> dirs; // name, end index
    std::vector<Mp5File> *out;
};

uint32_t fst_visit(uint32_t index, NodNodeKind kind, const char *name, uint32_t size, void *user)
{
    auto *walk = static_cast<FstWalk *>(user);
    while (!walk->dirs.empty() && index >= walk->dirs.back().second) {
        walk->dirs.pop_back();
    }
    if (index == 0) { // root
        return index + 1;
    }
    std::string path = "/mp5";
    for (const auto &d : walk->dirs) {
        path += "/" + d.first;
    }
    path += "/";
    path += name;
    if (kind == NOD_NODE_KIND_DIRECTORY) {
        walk->dirs.emplace_back(name, size);
    } else {
        walk->out->push_back(Mp5File { path, index, size });
    }
    return index + 1;
}

void *overlay_open(void *userData)
{
    const auto *file = static_cast<const Mp5File *>(userData);
    if (file->mem != nullptr) {
        return new OpenFile { nullptr, file->mem, 0 };
    }
    NodHandle *handle = nullptr;
    std::lock_guard lock(sOpenMutex);
    if (nod_partition_open_file(sPartition, file->fstIndex, &handle) != NOD_RESULT_OK) {
        std::printf("[mp5] failed to open %s\n", file->path.c_str());
        return nullptr;
    }
    return new OpenFile { handle, nullptr, 0 };
}

void overlay_close(void *handle)
{
    auto *file = static_cast<OpenFile *>(handle);
    if (file->nod != nullptr) {
        nod_free(file->nod);
    }
    delete file;
}

int64_t overlay_read(void *handle, uint8_t *buf, size_t len)
{
    auto *file = static_cast<OpenFile *>(handle);
    if (file->mem != nullptr) {
        const int64_t size = static_cast<int64_t>(file->mem->size());
        const int64_t n = std::max<int64_t>(0, std::min<int64_t>(static_cast<int64_t>(len), size - file->pos));
        std::memcpy(buf, file->mem->data() + file->pos, static_cast<size_t>(n));
        file->pos += n;
        return n;
    }
    // Callers expect a full read; nod may return short reads.
    size_t got = 0;
    while (got < len) {
        const int64_t n = nod_read(file->nod, buf + got, len - got);
        if (n < 0) {
            return got > 0 ? static_cast<int64_t>(got) : -1;
        }
        if (n == 0) {
            break;
        }
        got += static_cast<size_t>(n);
    }
    return static_cast<int64_t>(got);
}

int64_t overlay_seek(void *handle, int64_t offset, int32_t whence)
{
    auto *file = static_cast<OpenFile *>(handle);
    if (file->mem == nullptr) {
        return nod_seek(file->nod, offset, whence);
    }
    const int64_t size = static_cast<int64_t>(file->mem->size());
    int64_t pos = whence == SEEK_SET ? offset : whence == SEEK_CUR ? file->pos + offset : size + offset;
    if (pos < 0 || pos > size) {
        return -1;
    }
    file->pos = pos;
    return pos;
}

// Number of entries of a Hudson data archive (big-endian u32 count first), or 0.
uint32_t archive_count(const std::vector<uint8_t> &data)
{
    if (data.size() < 4) {
        return 0;
    }
    return (uint32_t(data[0]) << 24) | (uint32_t(data[1]) << 16) | (uint32_t(data[2]) << 8) | data[3];
}

// Loads the DK mod's two archives from `dir`: the extracted mod folder (or its files/ or files/data/ folder,
// or a folder holding the extracted mod folder). Returns true when both are there with MP5's entry counts.
bool load_dk_mod(const std::string &dir)
{
    namespace fs = std::filesystem;
    std::error_code ec;
    const fs::path root(std::u8string(reinterpret_cast<const char8_t *>(dir.c_str())));
    std::vector<fs::path> candidates { root / "files" / "data", root / "data", root };
    for (const auto &entry : fs::directory_iterator(root, ec)) {
        if (entry.is_directory(ec)) {
            candidates.push_back(entry.path() / "files" / "data");
        }
    }
    static const char *names[2] = { "teresa.bin", "teresamot.bin" };
    static const uint32_t counts[2] = { 224, 146 }; // as mario.bin / mariomot.bin
    for (const auto &c : candidates) {
        bool ok = true;
        for (int i = 0; i < 2 && ok; i++) {
            std::ifstream in(c / names[i], std::ios::binary);
            sDkModData[i].assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
            ok = archive_count(sDkModData[i]) == counts[i];
        }
        if (ok) {
            std::printf("[mp5] DK mod: %s\n", reinterpret_cast<const char *>(c.u8string().c_str()));
            return true;
        }
    }
    sDkModData[0].clear();
    sDkModData[1].clear();
    std::printf("[mp5] DK mod: no teresa.bin + teresamot.bin (DK in Mario Party 5) found under %s\n", dir.c_str());
    return false;
}

} // namespace

extern "C" int partyboard_mp5_mount(const char *path)
{
    if (sMounted || path == nullptr || path[0] == '\0') {
        return sMounted;
    }
    if (nod_disc_open(path, nullptr, &sDisc) != NOD_RESULT_OK) {
        std::printf("[mp5] can't open disc image %s\n", path);
        return 0;
    }
    NodDiscHeader header {};
    if (nod_disc_header(sDisc, &header) != NOD_RESULT_OK || std::memcmp(header.game_id, "GP5E01", 6) != 0) {
        std::printf("[mp5] %s is not Mario Party 5 (USA)\n", path);
        nod_free(sDisc);
        sDisc = nullptr;
        return 0;
    }
    if (nod_disc_open_partition(sDisc, 0, nullptr, &sPartition) != NOD_RESULT_OK) {
        std::printf("[mp5] can't open the data partition of %s\n", path);
        nod_free(sDisc);
        sDisc = nullptr;
        return 0;
    }
    FstWalk walk { {}, &sFiles };
    nod_partition_iterate_fst(sPartition, fst_visit, &walk);
    if (!sDkModDir.empty() && load_dk_mod(sDkModDir)) {
        sFiles.push_back(Mp5File { "/mp5dk/data/teresa.bin", 0, uint32_t(sDkModData[0].size()), &sDkModData[0] });
        sFiles.push_back(Mp5File { "/mp5dk/data/teresamot.bin", 0, uint32_t(sDkModData[1].size()), &sDkModData[1] });
        sDkMod = true;
    }

    // sFiles must not reallocate from here on: the overlay keeps pointers into it.
    std::vector<AuroraOverlayFile> overlay;
    overlay.reserve(sFiles.size());
    for (auto &f : sFiles) {
        overlay.push_back(AuroraOverlayFile { f.path.c_str(), &f, f.size });
    }
    static const AuroraOverlayCallbacks callbacks { overlay_open, overlay_close, overlay_read, overlay_seek };
    aurora_dvd_overlay_callbacks(&callbacks);
    aurora_dvd_overlay_files(overlay.data(), overlay.size(), nullptr);
    sMounted = true;
    std::printf("[mp5] mounted %s (%zu files under /mp5)\n", path, sFiles.size());
    return 1;
}

extern "C" int partyboard_mp5_available(void)
{
    return sMounted ? 1 : 0;
}

extern "C" void partyboard_mp5_set_dk_mod(const char *dir)
{
    if (!sMounted) {
        sDkModDir = dir != nullptr ? dir : "";
    }
}

extern "C" int partyboard_mp5_dk_mod(void)
{
    return (sDkMod && !partyboard_netplay_active()) ? 1 : 0;
}
