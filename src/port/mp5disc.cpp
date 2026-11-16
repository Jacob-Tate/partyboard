#include "port/mp5disc.h"

#include <aurora/dvd.h>
#include <nod.h>

#include <cstdio>
#include <cstring>
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
};

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
    NodHandle *handle = nullptr;
    std::lock_guard lock(sOpenMutex);
    if (nod_partition_open_file(sPartition, file->fstIndex, &handle) != NOD_RESULT_OK) {
        std::printf("[mp5] failed to open %s\n", file->path.c_str());
        return nullptr;
    }
    return handle;
}

void overlay_close(void *handle)
{
    nod_free(static_cast<NodHandle *>(handle));
}

int64_t overlay_read(void *handle, uint8_t *buf, size_t len)
{
    // Callers expect a full read; nod may return short reads.
    size_t got = 0;
    while (got < len) {
        const int64_t n = nod_read(static_cast<NodHandle *>(handle), buf + got, len - got);
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
    return nod_seek(static_cast<NodHandle *>(handle), offset, whence);
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
