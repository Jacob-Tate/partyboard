// Online autosave and continue (port/online_save.h).

#include <filesystem>

#include "port/online_save.h"

#include "netplay/protocol.h"
#include "port/main.h"
#include "port/netplay.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <string>
#include <system_error>
#include <vector>

extern "C" {
#include "game/gamework_data.h"
#include "port/byteswap.h"
}

static_assert(sizeof(SystemState) + 4 * sizeof(PlayerState) == PB_ONLINE_SAVE_STATE_SIZE, "board state size");

namespace {

constexpr size_t kStateSize = PB_ONLINE_SAVE_STATE_SIZE;

struct Save {
    std::filesystem::path path; // empty until the first checkpoint of this game
    u64 created = 0;
    bool finished = false;
    bool hasResume = false;
    bool hasLatest = false;
    std::array<u8, kStateSize> resume{};
    std::array<u8, kStateSize> latest{};
};

Save gSave;
PbNetSettings gSaveFor{};          // the game the save belongs to (a new game, with a new seed, starts a new file)
std::filesystem::path gContinueInto; // set by partyboard_online_save_continue_into for the next hosted game

const char *const kBoardFiles[] = { "toad", "goomba", "shyguy", "boo", "koopa", "bowser" };

std::filesystem::path online_dir()
{
    return PartyBoard_ConfigPath / "online";
}

// The board state as the game's party save keeps it, in GameCube byte order. player >= 0 sets player_curr.
void capture(int player, std::array<u8, kStateSize> &out)
{
    SystemState sys = GWSystem;
    if (player >= 0) {
        sys.player_curr = static_cast<s8>(player);
    }
    byteswap_systemstate(&sys);
    std::memcpy(out.data(), &sys, sizeof(sys));
    for (int i = 0; i < 4; i++) {
        PlayerState p = GWPlayer[i];
        byteswap_playerstate(&p);
        std::memcpy(out.data() + sizeof(SystemState) + i * sizeof(PlayerState), &p, sizeof(p));
    }
}

void put_u64(PbNetWriter *w, u64 v)
{
    pbw_u32(w, static_cast<u32>(v));
    pbw_u32(w, static_cast<u32>(v >> 32));
}

u64 get_u64(PbNetReader *r)
{
    const u64 lo = pbr_u32(r);
    const u64 hi = pbr_u32(r);
    return lo | (hi << 32);
}

bool write_file()
{
    const PbNetSettings *s = partyboard_netplay_game_settings();
    if (s == nullptr) {
        return false;
    }
    std::vector<u8> buf(4096);
    PbNetWriter w;
    pbw_init(&w, buf.data(), buf.size());
    pbw_bytes(&w, PB_ONLINE_SAVE_MAGIC, 8);
    pbw_u32(&w, PB_ONLINE_SAVE_VERSION);
    pbw_str(&w, partyboard_netplay_build_id(), PB_NET_MAX_BUILD_ID);
    put_u64(&w, gSave.created);
    put_u64(&w, static_cast<u64>(std::time(nullptr)));
    pbw_u8(&w, gSave.finished ? 1 : 0);
    pbw_u8(&w, s->board);
    pbw_u8(&w, static_cast<u8>(GWSystem.max_turn));
    pbw_u8(&w, s->cpuLevel);
    pbw_u8(&w, s->inputDelay);
    for (int i = 0; i < 4; i++) {
        pbw_u8(&w, s->chars[i]);
        pbw_u8(&w, s->portOwner[i] != PB_NET_PORT_CPU ? 1 : 0);
        pbw_str(&w, partyboard_netplay_port_name(i), PB_NET_MAX_NAME);
    }
    pbw_u8(&w, gSave.hasResume ? 1 : 0);
    pbw_u16(&w, static_cast<u16>(kStateSize));
    pbw_bytes(&w, gSave.resume.data(), kStateSize);
    pbw_u8(&w, gSave.hasLatest ? 1 : 0);
    pbw_u16(&w, static_cast<u16>(kStateSize));
    pbw_bytes(&w, gSave.latest.data(), kStateSize);
    if (w.overflow) {
        return false;
    }

    // Write a temp file, then replace: a crash mid-write leaves the previous checkpoint intact.
    std::error_code ec;
    std::filesystem::create_directories(gSave.path.parent_path(), ec);
    std::filesystem::path tmp = gSave.path;
    tmp += ".tmp";
    FILE *f = std::fopen(tmp.string().c_str(), "wb");
    if (f == nullptr) {
        return false;
    }
    const bool ok = std::fwrite(buf.data(), 1, w.pos, f) == w.pos;
    std::fflush(f);
    std::fclose(f);
    if (!ok) {
        return false;
    }
    std::filesystem::rename(tmp, gSave.path, ec); // replaces an existing file
    return !ec;
}

// The save for the game now running (only on the host), started for a new game.
bool begin()
{
    const PbNetSettings *s = partyboard_netplay_game_settings();
    if (s == nullptr || !partyboard_netplay_is_host()) {
        return false;
    }
    if (std::memcmp(&gSaveFor, s, sizeof(gSaveFor)) != 0 || gSave.path.empty()) {
        gSave = Save{};
        gSaveFor = *s;
        PbOnlineSave old;
        if (!gContinueInto.empty() && partyboard_online_save_load(reinterpret_cast<const char *>(gContinueInto.u8string().c_str()), &old)) {
            // A continued game keeps its file, and the checkpoints it had until it makes new ones.
            gSave.path = gContinueInto;
            gSave.created = old.created;
            gSave.hasResume = old.hasResume != 0;
            std::memcpy(gSave.resume.data(), old.resumeState, kStateSize);
            gContinueInto.clear();
            return true;
        }
        gContinueInto.clear();
        gSave.created = static_cast<u64>(std::time(nullptr));
        const std::time_t created = static_cast<std::time_t>(gSave.created);
        std::tm local{};
#ifdef _WIN32
        localtime_s(&local, &created);
#else
        localtime_r(&created, &local);
#endif
        char name[96];
        std::snprintf(name, sizeof(name), "%04d-%02d-%02d_%02d%02d%02d_%s.pbsave", local.tm_year + 1900,
            local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec,
            s->board < 6 ? kBoardFiles[s->board] : "board");
        gSave.path = online_dir() / name;
    }
    return true;
}

void report(const char *what)
{
    if (write_file()) {
        std::printf("[save] %s: %s\n", what, gSave.path.filename().string().c_str());
    } else {
        std::printf("[save] could not write %s\n", gSave.path.string().c_str());
    }
    std::fflush(stdout);
}

} // namespace

extern "C" void partyboard_online_save_turn(int player)
{
    if (!partyboard_netplay_active() || player < 0 || player > 3 || !begin()) {
        return;
    }
    capture(player, gSave.latest);
    gSave.hasLatest = true;
    char what[64];
    std::snprintf(what, sizeof(what), "turn %d, player %d starts", GWSystem.turn, player + 1);
    report(what);
}

extern "C" void partyboard_online_save_resume_point(void)
{
    if (!partyboard_netplay_active() || !begin()) {
        return;
    }
    capture(-1, gSave.resume);
    gSave.hasResume = true;
    char what[64];
    std::snprintf(what, sizeof(what), "resume point after turn %d's minigame", GWSystem.turn);
    report(what);
}

extern "C" void partyboard_online_save_party_over(void)
{
    if (!partyboard_netplay_active() || !begin() || (!gSave.hasLatest && !gSave.hasResume)) {
        return;
    }
    gSave.finished = true;
    report("party over, marked finished");
}

extern "C" int partyboard_online_save_load(const char *pathUtf8, PbOnlineSave *out)
{
    std::memset(out, 0, sizeof(*out));
    const std::filesystem::path path = std::filesystem::u8path(pathUtf8);
    FILE *f = std::fopen(path.string().c_str(), "rb");
    if (f == nullptr) {
        return 0;
    }
    std::vector<u8> buf(8192);
    const size_t n = std::fread(buf.data(), 1, buf.size(), f);
    std::fclose(f);
    PbNetReader r;
    pbr_init(&r, buf.data(), n);
    char magic[8];
    pbr_bytes(&r, magic, 8);
    if (std::memcmp(magic, PB_ONLINE_SAVE_MAGIC, 8) != 0 || pbr_u32(&r) != PB_ONLINE_SAVE_VERSION) {
        return 0;
    }
    std::snprintf(out->path, sizeof(out->path), "%s", pathUtf8);
    pbr_str(&r, out->build, sizeof(out->build));
    out->created = get_u64(&r);
    out->updated = get_u64(&r);
    out->finished = pbr_u8(&r);
    out->board = pbr_u8(&r);
    out->maxTurns = pbr_u8(&r);
    out->cpuLevel = pbr_u8(&r);
    out->inputDelay = pbr_u8(&r);
    for (int i = 0; i < 4; i++) {
        out->chars[i] = pbr_u8(&r);
        out->wasHuman[i] = pbr_u8(&r);
        pbr_str(&r, out->names[i], sizeof(out->names[i]));
    }
    out->hasResume = pbr_u8(&r);
    if (pbr_u16(&r) != kStateSize) {
        return 0;
    }
    pbr_bytes(&r, out->resumeState, kStateSize);
    out->hasLatest = pbr_u8(&r);
    if (pbr_u16(&r) != kStateSize) {
        return 0;
    }
    std::array<u8, kStateSize> latest{};
    pbr_bytes(&r, latest.data(), kStateSize);
    if (r.error) {
        return 0;
    }
    // GWSystem (big-endian bytes): turn at 0x04, player_curr at 0x0A
    out->resumeTurn = out->resumeState[4];
    out->latestTurn = latest[4];
    out->latestPlayer = static_cast<s8>(latest[0x0A]);
    return 1;
}

extern "C" int partyboard_online_save_list(PbOnlineSave *out, int max)
{
    std::vector<PbOnlineSave> found;
    std::error_code ec;
    for (const auto &entry : std::filesystem::directory_iterator(online_dir(), ec)) {
        if (entry.path().extension() != ".pbsave") {
            continue;
        }
        PbOnlineSave save;
        if (partyboard_online_save_load(reinterpret_cast<const char *>(entry.path().u8string().c_str()), &save) && !save.finished && save.hasResume &&
            std::strcmp(save.build, partyboard_netplay_build_id()) == 0) {
            found.push_back(save);
        }
    }
    std::sort(found.begin(), found.end(), [](const PbOnlineSave &a, const PbOnlineSave &b) { return a.updated > b.updated; });
    const int count = std::min<int>(max, static_cast<int>(found.size()));
    std::copy(found.begin(), found.begin() + count, out);
    return count;
}

extern "C" void partyboard_online_save_continue_into(const char *path)
{
    gContinueInto = path ? std::filesystem::u8path(path) : std::filesystem::path();
}
