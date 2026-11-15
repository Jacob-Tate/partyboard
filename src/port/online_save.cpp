// Online autosave (port/online_save.h).

#include "port/online_save.h"

#include <filesystem>

#include "netplay/protocol.h"
#include "port/main.h"
#include "port/netplay.h"

#include <array>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <string>
#include <system_error>
#include <vector>

extern "C" {
#include "game/gamework_data.h"
#include "port/byteswap.h"
}

namespace {

constexpr size_t kStateSize = sizeof(SystemState) + 4 * sizeof(PlayerState);

struct Save {
    std::filesystem::path path; // empty until the first checkpoint of this game
    std::time_t created = 0;
    bool finished = false;
    bool hasLatest = false;
    bool hasRoundStart = false;
    std::array<u8, kStateSize> latest{};
    std::array<u8, kStateSize> roundStart{};
};

Save gSave;
PbNetSettings gSaveFor{}; // the game the save belongs to (a new game, with a new seed, starts a new file)

const char *const kBoardFiles[] = { "toad", "goomba", "shyguy", "boo", "koopa", "bowser" };

// The board state as the game's party save keeps it, with player_curr = `player`, in GameCube byte order.
void capture(int player, std::array<u8, kStateSize> &out)
{
    SystemState sys = GWSystem;
    sys.player_curr = static_cast<s8>(player);
    byteswap_systemstate(&sys);
    std::memcpy(out.data(), &sys, sizeof(sys));
    for (int i = 0; i < 4; i++) {
        PlayerState p = GWPlayer[i];
        byteswap_playerstate(&p);
        std::memcpy(out.data() + sizeof(SystemState) + i * sizeof(PlayerState), &p, sizeof(p));
    }
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
    const auto now = static_cast<u64>(std::time(nullptr));
    pbw_u32(&w, static_cast<u32>(static_cast<u64>(gSave.created))); // u64 as two u32 (low, high)
    pbw_u32(&w, static_cast<u32>(static_cast<u64>(gSave.created) >> 32));
    pbw_u32(&w, static_cast<u32>(now));
    pbw_u32(&w, static_cast<u32>(now >> 32));
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
    pbw_u8(&w, gSave.hasLatest ? 1 : 0);
    pbw_u16(&w, static_cast<u16>(kStateSize));
    pbw_bytes(&w, gSave.latest.data(), kStateSize);
    pbw_u8(&w, gSave.hasRoundStart ? 1 : 0);
    pbw_u16(&w, static_cast<u16>(kStateSize));
    pbw_bytes(&w, gSave.roundStart.data(), kStateSize);
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

// The save for the game now running, started fresh for a new game.
bool begin()
{
    const PbNetSettings *s = partyboard_netplay_game_settings();
    if (s == nullptr || !partyboard_netplay_is_host()) {
        return false;
    }
    if (std::memcmp(&gSaveFor, s, sizeof(gSaveFor)) != 0 || gSave.path.empty()) {
        gSave = Save{};
        gSaveFor = *s;
        gSave.created = std::time(nullptr);
        char name[96];
        std::tm local{};
#ifdef _WIN32
        localtime_s(&local, &gSave.created);
#else
        localtime_r(&gSave.created, &local);
#endif
        std::snprintf(name, sizeof(name), "%04d-%02d-%02d_%02d%02d%02d_%s.pbsave", local.tm_year + 1900,
            local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec,
            s->board < 6 ? kBoardFiles[s->board] : "board");
        gSave.path = PartyBoard_ConfigPath / "online" / name;
    }
    return true;
}

} // namespace

extern "C" void partyboard_online_save_turn(int player)
{
    if (!partyboard_netplay_active() || player < 0 || player > 3 || !begin()) {
        return;
    }
    capture(player, gSave.latest);
    gSave.hasLatest = true;
    if (player == 0) {
        gSave.roundStart = gSave.latest;
        gSave.hasRoundStart = true;
    }
    if (write_file()) {
        std::printf("[save] turn %d, player %d: %s\n", GWSystem.turn, player + 1, gSave.path.filename().string().c_str());
    } else {
        std::printf("[save] could not write %s\n", gSave.path.string().c_str());
    }
    std::fflush(stdout);
}

extern "C" void partyboard_online_save_party_over(void)
{
    if (!partyboard_netplay_active() || !begin() || !gSave.hasLatest) {
        return;
    }
    gSave.finished = true;
    if (write_file()) {
        std::printf("[save] party over: %s marked finished\n", gSave.path.filename().string().c_str());
        std::fflush(stdout);
    }
}
