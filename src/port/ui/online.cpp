#include "online.hpp"

#include "number_button.hpp"
#include "pane.hpp"
#include "port/config.hpp"
#include "netplay/protocol.h"
#include "port/netplay.h"
#include "port/online_save.h"
#include "port/settings.h"
#include "portraits.hpp"
#include "string_button.hpp"
#include "ui.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <functional>
#include <string>
#include <utility>

namespace partyboard::ui {
namespace {

    constexpr std::array<const char *, 6> kBoardNames = {
        "Toad's Midway Madness",
        "Goomba's Greedy Gala",
        "Shy Guy's Jungle Jam",
        "Boo's Haunted Bash",
        "Koopa's Seaside Soiree",
        "Bowser's Gnarly Party",
    };

    // CPU difficulty levels, as the game names them (GWPlayerCfg diff 0-3).
    constexpr std::array<const char *, 4> kCpuLevelNames = { "Easy", "Normal", "Hard", "Very Hard" };

    int cpu_level()
    {
        const int level = getSettings().netplay.cpuLevel.getValue();
        return level >= 0 && level < static_cast<int>(kCpuLevelNames.size()) ? level : 1;
    }

    constexpr int kPorts = 4;
    constexpr int kChars = 8;
    constexpr uint8_t kCpu = 0xFF;  // PB_NET_PORT_CPU
    constexpr uint8_t kAuto = 0xFF; // PB_NET_CHAR_AUTO

    Rml::String gJoinCode;

    // A right-pane button whose label follows the room state (the pane is only rebuilt on focus).
    class LiveButton : public ControlledButton {
    public:
        LiveButton(Rml::Element *parent, std::function<Rml::String()> getText, std::function<bool()> isSelected)
            : ControlledButton(parent, { getText(), std::move(isSelected) })
            , mGetText(std::move(getText))
        {
        }
        void update() override
        {
            set_text(mGetText());
            ControlledButton::update();
        }

    private:
        std::function<Rml::String()> mGetText;
    };

    // A list row with a picture from the disc (if it could be read) before its live label.
    // cssClass sets the picture size (see window.rcss).
    class PictureButton : public ControlledButton {
    public:
        PictureButton(Rml::Element *parent, Rml::String imageSrc, bool hasImage, const char *cssClass,
            std::function<Rml::String()> getText, std::function<bool()> isSelected)
            : ControlledButton(parent, { getText(), std::move(isSelected) })
            , mImageSrc(std::move(imageSrc))
            , mHasImage(hasImage)
            , mGetText(std::move(getText))
        {
            if (mHasImage) {
                root()->SetClass("picture-button", true);
                root()->SetClass(cssClass, true);
            }
            refresh();
        }
        void update() override
        {
            refresh();
            ControlledButton::update();
        }

    private:
        void refresh()
        {
            const auto text = mGetText();
            if (!mHasImage) {
                set_text(text);
                return;
            }
            if (text == mShown) {
                return;
            }
            mShown = text;
            root()->SetInnerRML("<img src=\"" + mImageSrc + "\"/><span>" + escape(text) + "</span>");
        }

        Rml::String mImageSrc;
        bool mHasImage;
        Rml::String mShown;
        std::function<Rml::String()> mGetText;
    };

    // A picture that follows a setting (e.g. the chosen board), shown at the top of a right pane.
    class LivePicture : public Component {
    public:
        LivePicture(Rml::Element *parent, const char *cssClass, std::function<Rml::String()> getSrc)
            : Component(append(parent, "div"))
            , mGetSrc(std::move(getSrc))
        {
            mRoot->SetClass(cssClass, true);
            refresh();
        }
        void update() override
        {
            refresh();
            Component::update();
        }

    private:
        void refresh()
        {
            const auto src = mGetSrc();
            if (src != mShown) {
                mShown = src;
                mRoot->SetInnerRML("<img src=\"" + src + "\"/>");
            }
        }

        std::function<Rml::String()> mGetSrc;
        Rml::String mShown;
    };

    Rml::String default_name()
    {
        const char *user = std::getenv("USERNAME");
        return user && user[0] ? user : "Player";
    }

    Rml::String player_name()
    {
        const auto &name = getSettings().netplay.name.getValue();
        return name.empty() ? default_name() : Rml::String(name);
    }

    bool in_lobby()
    {
        const auto state = partyboard_netplay_state();
        return state != PB_LOBBY_IDLE && state != PB_LOBBY_FAILED;
    }

    bool in_room()
    {
        return partyboard_netplay_state() == PB_LOBBY_IN_ROOM;
    }

    bool hosting()
    {
        return in_room() && partyboard_netplay_is_host();
    }

    // The online save the next hosted room continues (Host a Game > Saved Game), or nullptr for a new game.
    const PbOnlineSave *continuing_save()
    {
        return partyboard_netplay_pending_continue();
    }

    Rml::String save_date(u64 when)
    {
        const std::time_t t = static_cast<std::time_t>(when);
        std::tm local {};
        localtime_s(&local, &t);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%b %d, %H:%M", &local);
        return buf;
    }

    // "Toad's Midway Madness, turn 4/10"
    Rml::String save_title(const PbOnlineSave &save)
    {
        return Rml::String(kBoardNames[save.board < 6 ? save.board : 0]) + ", turn " + std::to_string(save.resumeTurn) +
            "/" + std::to_string(save.maxTurns);
    }

    // "Jacob, Sam and 2 CPUs - Nov 15, 03:43"
    Rml::String save_players(const PbOnlineSave &save)
    {
        Rml::String names;
        int cpus = 0;
        for (int i = 0; i < 4; i++) {
            if (!save.wasHuman[i]) {
                cpus++;
                continue;
            }
            names += (names.empty() ? "" : ", ") + Rml::String(save.names[i]);
        }
        if (cpus) {
            names += (names.empty() ? "" : " and ") + std::to_string(cpus) + (cpus == 1 ? " CPU" : " CPUs");
        }
        return names + " - " + save_date(save.updated);
    }

    Rml::String char_name(int character)
    {
        return partyboard_netplay_char_name(character);
    }

    // The character this player has (in a room) or will ask for (before joining); -1 = any.
    int my_char()
    {
        if (in_room()) {
            return partyboard_netplay_slot_char(partyboard_netplay_my_port());
        }
        const int pref = getSettings().netplay.character.getValue();
        return pref >= 0 && pref < kChars ? pref : -1;
    }

    // "Alice - Mario", "CPU - Peach (auto)"
    Rml::String slot_text(int port)
    {
        if (!in_room()) {
            return "-";
        }
        Rml::String text = Rml::String(partyboard_netplay_slot_name(port)) + " - " +
            char_name(partyboard_netplay_slot_char(port));
        if (partyboard_netplay_slot_auto(port)) {
            text += " (auto)";
        }
        const int ping = partyboard_netplay_slot_ping(port);
        if (ping >= 0) {
            text += "  " + std::to_string(ping) + " ms";
        }
        if (partyboard_netplay_is_host() && getSettings().netplay.teams.getValue()) {
            text += port < 2 ? "  [team A]" : "  [team B]";
        }
        const char *saved = partyboard_netplay_saved_name(port);
        if (partyboard_netplay_slot_owner(port) == kCpu && saved[0]) {
            text += Rml::String("  (") + saved + "'s seat)";
        }
        if (port == partyboard_netplay_my_port()) {
            text += "  (you)";
        }
        return text;
    }

    // Who holds a character in the room, other than this player: "" if nobody.
    Rml::String holder_of(int character)
    {
        if (!in_room()) {
            return "";
        }
        for (int port = 0; port < kPorts; port++) {
            if (port != partyboard_netplay_my_port() && partyboard_netplay_slot_char(port) == character) {
                return partyboard_netplay_slot_auto(port) ? "CPU, auto" : partyboard_netplay_slot_name(port);
            }
        }
        return "";
    }

    Rml::String member_name(int id)
    {
        for (int i = 0; i < partyboard_netplay_member_count(); i++) {
            if (partyboard_netplay_member_id(i) == id) {
                return partyboard_netplay_member_name(i);
            }
        }
        return "(left)";
    }

    // The room's layout as SET_LAYOUT expects it (auto CPUs stay auto).
    void current_layout(uint8_t owner[kPorts], uint8_t chars[kPorts])
    {
        for (int port = 0; port < kPorts; port++) {
            owner[port] = static_cast<uint8_t>(partyboard_netplay_slot_owner(port));
            chars[port] = partyboard_netplay_slot_auto(port) ? kAuto : static_cast<uint8_t>(partyboard_netplay_slot_char(port));
        }
    }

    // Host: put a member on a port, swapping with whoever (person or CPU) is there.
    void host_seat(int memberId, int port)
    {
        uint8_t owner[kPorts], chars[kPorts];
        current_layout(owner, chars);
        for (int from = 0; from < kPorts; from++) {
            if (owner[from] == memberId && from != port) {
                std::swap(owner[from], owner[port]);
                std::swap(chars[from], chars[port]);
                partyboard_netplay_set_layout(owner, chars);
                return;
            }
        }
    }

    // Host: set a CPU port's character (kAuto = pick automatically).
    void host_cpu_char(int port, uint8_t character)
    {
        uint8_t owner[kPorts], chars[kPorts];
        current_layout(owner, chars);
        if (owner[port] != kCpu) {
            return;
        }
        chars[port] = character;
        partyboard_netplay_set_layout(owner, chars);
    }

    Rml::String status_text()
    {
        switch (partyboard_netplay_state()) {
        case PB_LOBBY_IDLE:
            return "Not connected";
        case PB_LOBBY_CONNECTING:
        case PB_LOBBY_HELLO:
            return "Connecting...";
        case PB_LOBBY_JOINING:
            return "Entering room...";
        case PB_LOBBY_IN_ROOM:
            if (partyboard_netplay_notice()[0]) {
                return Rml::String("Can't: ") + partyboard_netplay_notice();
            }
            if (partyboard_netplay_room_phase() == PB_ROOM_IN_GAME) {
                return "Game in progress - you're back in after this round's minigame";
            }
            if (partyboard_netplay_room_phase() == PB_ROOM_RELOADING) {
                return "The game restarts once everyone is back";
            }
            return partyboard_netplay_is_host() ? "Hosting - start when ready" : "Waiting for the host to start";
        case PB_LOBBY_STARTED:
            return "Starting!";
        case PB_LOBBY_FAILED:
            return Rml::String("Error: ") + partyboard_netplay_error();
        }
        return "";
    }

    void save()
    {
        config::Save();
    }

    void begin(int create, const char *code)
    {
        partyboard_netplay_set_preference(-1, getSettings().netplay.character.getValue());
        partyboard_netplay_begin(getSettings().netplay.server.getValue().c_str(), player_name().c_str(), create, code);
    }

} // namespace

OnlineWindow::OnlineWindow()
{
    add_tab("Online", [this](Rml::Element *content) {
        auto &leftPane = add_child<Pane>(content, Pane::Type::Controlled);
        auto &rightPane = add_child<Pane>(content, Pane::Type::Uncontrolled);

        // ---- Connection ----
        leftPane.add_section("Connection");
        leftPane.register_control(leftPane.add_child<StringButton>(StringButton::Props {
                                      .key = "Server",
                                      .getValue = [] {
                                          const auto &server = getSettings().netplay.server.getValue();
                                          return server.empty() ? Rml::String("(not set)") : Rml::String(server);
                                      },
                                      .setValue = [](Rml::String value) {
                                          getSettings().netplay.server.setValue(value);
                                          save();
                                      },
                                      .maxLength = 120,
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Address of the Party Board relay server, as <b>host</b> or <b>host:port</b>.<br/><br/>"
                             "The default port is 7845 (UDP).");
            });
        leftPane.register_control(leftPane.add_child<StringButton>(StringButton::Props {
                                      .key = "Your Name",
                                      .getValue = [] { return player_name(); },
                                      .setValue = [](Rml::String value) {
                                          getSettings().netplay.name.setValue(value);
                                          save();
                                      },
                                      .maxLength = 24,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("The name other players see in the room."); });

        // ---- Host ----
        leftPane.add_section("Host a Game");
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Saved Game",
                                      .getValue = [] {
                                          const PbOnlineSave *save = continuing_save();
                                          return save ? save_title(*save) : Rml::String("New game");
                                      },
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Start a new party, or continue an online party that was interrupted. The host's "
                             "game saves after every minigame; a continue starts from the last one.<br/><br/>"
                             "Everyone gets their seat back by joining with the same name; anyone else can take a "
                             "CPU's seat. Seats nobody takes stay CPUs.");
                pane.add_button({
                                    .text = "New game",
                                    .isSelected = [] { return continuing_save() == nullptr; },
                                })
                    .on_pressed([] { partyboard_netplay_set_continue(nullptr); });
                static std::vector<PbOnlineSave> saves;
                saves.assign(32, PbOnlineSave {});
                saves.resize(partyboard_online_save_list(saves.data(), static_cast<int>(saves.size())));
                if (saves.empty()) {
                    pane.add_rml("<br/>No interrupted online parties saved on this PC (with this build).");
                }
                for (size_t i = 0; i < saves.size(); i++) {
                    const std::string path = saves[i].path;
                    pane.add_button({
                                        .text = save_title(saves[i]) + "  -  " + save_players(saves[i]),
                                        .isSelected = [path] {
                                            const PbOnlineSave *save = continuing_save();
                                            return save && path == save->path;
                                        },
                                    })
                        .on_pressed([i] { partyboard_netplay_set_continue(&saves[i]); });
                }
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Board",
                                      .getValue = [] {
                                          const PbOnlineSave *save = continuing_save();
                                          const int board = save ? save->board : getSettings().netplay.board.getValue();
                                          return Rml::String(kBoardNames[board >= 0 && board < 6 ? board : 0]);
                                      },
                                      .isDisabled = [] { return continuing_save() != nullptr; },
                                  }),
            rightPane, [](Pane &pane) {
                const bool pictures = portraits::ensure_boards_loaded();
                if (pictures) {
                    pane.add_child<LivePicture>("board-preview", [] {
                        const int board = getSettings().netplay.board.getValue();
                        return "board://" + std::to_string(board >= 0 && board < 6 ? board : 0);
                    });
                }
                for (int i = 0; i < static_cast<int>(kBoardNames.size()); i++) {
                    pane.add_child<PictureButton>("board://" + std::to_string(i), pictures, "board-button",
                            [i] { return Rml::String(kBoardNames[i]); },
                            [i] { return getSettings().netplay.board.getValue() == i; })
                        .on_pressed([i] {
                            getSettings().netplay.board.setValue(i);
                            save();
                        });
                }
            });
        leftPane.register_control(leftPane.add_child<NumberButton>(NumberButton::Props {
                                      .key = "Turns",
                                      .getValue = [] {
                                          const PbOnlineSave *save = continuing_save();
                                          return save ? static_cast<int>(save->maxTurns) : getSettings().netplay.turns.getValue();
                                      },
                                      .setValue = [](int value) {
                                          getSettings().netplay.turns.setValue(value);
                                          save();
                                      },
                                      .isDisabled = [] { return continuing_save() != nullptr; },
                                      .min = 10,
                                      .max = 50,
                                      .step = 5,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("Number of turns in the party (10 to 50)."); });
        leftPane.register_control(leftPane.add_child<NumberButton>(NumberButton::Props {
                                      .key = "Input Delay",
                                      .getValue = [] { return getSettings().netplay.inputDelay.getValue(); },
                                      .setValue = [](int value) {
                                          getSettings().netplay.inputDelay.setValue(value);
                                          save();
                                      },
                                      .min = 1,
                                      .max = 10,
                                      .suffix = " frames",
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Frames between pressing a button and it taking effect, for everyone.<br/><br/>"
                             "4 suits a local network. Raise it if the game stutters over the internet "
                             "(each frame is about 17 ms).<br/><br/>"
                             "Once people are in your room, their pings (shown under Room) give a suggestion:");
                pane.add_child<LiveButton>(
                        [] {
                            const int suggested = partyboard_netplay_suggested_delay();
                            return suggested > 0 ? "Use suggested: " + std::to_string(suggested) + " frames"
                                                 : Rml::String("Suggestion: needs two people in the room");
                        },
                        [] {
                            const int suggested = partyboard_netplay_suggested_delay();
                            return suggested > 0 && suggested == getSettings().netplay.inputDelay.getValue();
                        })
                    .on_pressed([] {
                        const int suggested = partyboard_netplay_suggested_delay();
                        if (suggested > 0) {
                            getSettings().netplay.inputDelay.setValue(std::min(suggested, 10));
                            save();
                        }
                    });
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Teams",
                                      .getValue = [] {
                                          return Rml::String(getSettings().netplay.teams.getValue() ? "2 vs 2" : "Off");
                                      },
                                      .isDisabled = [] { return continuing_save() != nullptr; },
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Team battle: P1 and P2 against P3 and P4, as the game's own 2 vs 2 party. Arrange "
                             "the teams by seating people under Room.");
                for (int on = 0; on < 2; on++) {
                    pane.add_button({
                                        .text = on ? "2 vs 2" : "Off",
                                        .isSelected = [on] { return getSettings().netplay.teams.getValue() == (on != 0); },
                                    })
                        .on_pressed([on] {
                            getSettings().netplay.teams.setValue(on != 0);
                            save();
                        });
                }
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Bonus Stars",
                                      .getValue = [] {
                                          return Rml::String(getSettings().netplay.bonusStars.getValue() ? "On" : "Off");
                                      },
                                      .isDisabled = [] { return continuing_save() != nullptr; },
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("The bonus stars handed out at the end of the party (most minigame coins, most coins, "
                             "most happening spaces).");
                for (int on = 1; on >= 0; on--) {
                    pane.add_button({
                                        .text = on ? "On" : "Off",
                                        .isSelected = [on] { return getSettings().netplay.bonusStars.getValue() == (on != 0); },
                                    })
                        .on_pressed([on] {
                            getSettings().netplay.bonusStars.setValue(on != 0);
                            save();
                        });
                }
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "CPU Difficulty",
                                      .getValue = [] { return Rml::String(kCpuLevelNames[cpu_level()]); },
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("How well the CPU players play, including any CPU that takes over for someone "
                             "who disconnects.");
                for (int i = 0; i < static_cast<int>(kCpuLevelNames.size()); i++) {
                    pane.add_button({
                                        .text = kCpuLevelNames[i],
                                        .isSelected = [i] { return cpu_level() == i; },
                                    })
                        .on_pressed([i] {
                            getSettings().netplay.cpuLevel.setValue(i);
                            save();
                        });
                }
            });
        leftPane.register_control(leftPane
                                      .add_select_button({
                                          .key = "Create Room",
                                          .getValue = [] { return Rml::String(">"); },
                                          .isDisabled = [] { return in_lobby(); },
                                      })
                                      .on_pressed([] {
                                          if (in_lobby()) {
                                              return;
                                          }
                                          begin(1, nullptr);
                                      }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Create a room and get a 4-letter code to share. Players take the first free "
                             "port when they join and can switch to another free one; as host you can "
                             "rearrange everyone and choose the CPUs' characters under <b>Room</b>.");
            });

        // ---- Join ----
        leftPane.add_section("Join a Game");
        leftPane.register_control(leftPane.add_child<StringButton>(StringButton::Props {
                                      .key = "Room Code",
                                      .getValue = [] { return gJoinCode.empty() ? Rml::String("----") : gJoinCode; },
                                      .setValue = [](Rml::String value) {
                                          for (auto &ch : value) {
                                              ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
                                          }
                                          gJoinCode = value;
                                      },
                                      .maxLength = 4,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("The 4-letter code shown on the host's screen."); });
        leftPane.register_control(leftPane
                                      .add_select_button({
                                          .key = "Join Room",
                                          .getValue = [] { return Rml::String(">"); },
                                          .isDisabled = [] { return in_lobby() || gJoinCode.size() != 4; },
                                      })
                                      .on_pressed([] {
                                          if (in_lobby() || gJoinCode.size() != 4) {
                                              return;
                                          }
                                          begin(0, gJoinCode.c_str());
                                      }),
            rightPane, [](Pane &pane) { pane.add_rml("Join the room with the code above."); });

        // ---- Room ----
        leftPane.add_section("Room");
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Status",
                                      .getValue = [] { return status_text(); },
                                      .submit = false,
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Connection and room status.<br/><br/>Dropped out of a game? Join the same room code "
                             "with the same name: you get your seat back after the current round's minigame, when "
                             "everyone's game restarts from that save point.");
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Room Code",
                                      .getValue = [] {
                                          const char *code = partyboard_netplay_room_code();
                                          return code[0] ? Rml::String(code) : Rml::String("-");
                                      },
                                      .submit = false,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("Share this code with the other players."); });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Your Character",
                                      .getValue = [] {
                                          const int c = my_char();
                                          return c >= 0 ? char_name(c) : Rml::String("Any");
                                      },
                                      .isDisabled = [] {
                                          return partyboard_netplay_room_continuing() != 0 ||
                                                 partyboard_netplay_room_phase() != PB_ROOM_LOBBY;
                                      },
                                  }),
            rightPane, [](Pane &pane) {
                const bool pictures = portraits::ensure_loaded();
                pane.add_rml("Your character. Nobody can pick one someone else already has; CPUs marked "
                             "<i>auto</i> give theirs up. Remembered for next time.");
                for (int c = 0; c < kChars; c++) {
                    pane.add_child<PictureButton>("portrait://" + std::to_string(c), pictures, "portrait-button",
                            [c] {
                                const auto holder = holder_of(c);
                                return holder.empty() ? char_name(c) : char_name(c) + "  (" + holder + ")";
                            },
                            [c] { return my_char() == c; })
                        .on_pressed([c] {
                            getSettings().netplay.character.setValue(c);
                            save();
                            if (in_room()) {
                                partyboard_netplay_choose(-1, c);
                            }
                        });
                }
            });
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Your Port",
                                      .getValue = [] {
                                          const int port = partyboard_netplay_my_port();
                                          return port >= 0 ? "P" + std::to_string(port + 1) : Rml::String("-");
                                      },
                                      .isDisabled = [] { return !in_room(); },
                                  }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Your player number. Pick a port a CPU has; the CPU moves to your old one.");
                for (int port = 0; port < kPorts; port++) {
                    pane.add_child<LiveButton>(
                            [port] { return "P" + std::to_string(port + 1) + "  " + slot_text(port); },
                            [port] { return partyboard_netplay_my_port() == port; })
                        .on_pressed([port] { partyboard_netplay_choose(port, -1); });
                }
            });
        for (int port = 0; port < kPorts; port++) {
            leftPane.register_control(leftPane.add_select_button({
                                          .key = "P" + std::to_string(port + 1),
                                          .getValue = [port] { return slot_text(port); },
                                      }),
                rightPane, [port](Pane &pane) {
                    if (!hosting()) {
                        pane.add_rml("Who plays player " + std::to_string(port + 1) +
                                     ", and as whom. The host can rearrange ports and choose the CPUs' "
                                     "characters.");
                        return;
                    }
                    pane.add_rml("Host: choose who plays P" + std::to_string(port + 1) +
                                 " (swaps with their current port). Ports without a person are CPUs.");
                    const int members = partyboard_netplay_member_count();
                    for (int i = 0; i < members; i++) {
                        const int id = partyboard_netplay_member_id(i);
                        pane.add_child<LiveButton>(
                                [id] { return Rml::String("Seat ") + member_name(id); },
                                [id, port] { return partyboard_netplay_slot_owner(port) == id; })
                            .on_pressed([id, port] { host_seat(id, port); });
                    }
                    pane.add_section("CPU character (when a CPU plays this port)");
                    pane.add_child<LiveButton>([] { return Rml::String("Auto (first free)"); },
                            [port] {
                                return partyboard_netplay_slot_owner(port) == kCpu && partyboard_netplay_slot_auto(port);
                            })
                        .on_pressed([port] { host_cpu_char(port, kAuto); });
                    for (int c = 0; c < kChars; c++) {
                        pane.add_child<LiveButton>([c] { return char_name(c); },
                                [port, c] {
                                    return partyboard_netplay_slot_owner(port) == kCpu &&
                                        !partyboard_netplay_slot_auto(port) && partyboard_netplay_slot_char(port) == c;
                                })
                            .on_pressed([port, c] { host_cpu_char(port, static_cast<uint8_t>(c)); });
                    }
                });
        }
        leftPane.register_control(leftPane
                                      .add_select_button({
                                          .key = "Start Game",
                                          .getValue = [] { return Rml::String(">"); },
                                          .isDisabled = [] {
                                              return partyboard_netplay_state() != PB_LOBBY_IN_ROOM || !partyboard_netplay_is_host();
                                          },
                                      })
                                      .on_pressed([] {
                                          const auto &s = getSettings().netplay;
                                          partyboard_netplay_start_game(s.board.getValue(), s.turns.getValue(),
                                              s.inputDelay.getValue(), cpu_level(), 0, s.teams.getValue() ? 1 : 0, s.bonusStars.getValue() ? 1 : 0);
                                      }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Host only: start the party for everyone in the room, with the ports and "
                             "characters shown above. It boots straight into the board.");
            });
        leftPane.register_control(leftPane
                                      .add_select_button({
                                          .key = "Leave Room",
                                          .getValue = [] { return Rml::String(">"); },
                                          .isDisabled = [] { return !in_lobby(); },
                                      })
                                      .on_pressed([] { partyboard_netplay_leave(); }),
            rightPane, [](Pane &pane) { pane.add_rml("Leave the room and disconnect."); });
    });
}

void OnlineWindow::update()
{
    partyboard_netplay_update();
    if (partyboard_netplay_state() == PB_LOBBY_STARTED) {
        // The prelaunch screen boots the game when it sees the started state.
        hide(true);
        return;
    }
    Window::update();
}

void OnlineWindow::hide(bool close)
{
    if (close && partyboard_netplay_state() != PB_LOBBY_STARTED) {
        partyboard_netplay_leave();
    }
    Window::hide(close);
}

} // namespace partyboard::ui
