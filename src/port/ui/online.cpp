#include "online.hpp"

#include "number_button.hpp"
#include "pane.hpp"
#include "port/config.hpp"
#include "port/netplay.h"
#include "port/settings.h"
#include "string_button.hpp"

#include <array>
#include <cctype>
#include <cstdlib>

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

    Rml::String gJoinCode;

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
            return partyboard_netplay_is_host() ? "Hosting - start when ready" : "Waiting for the host to start";
        case PB_LOBBY_STARTED:
            return "Starting!";
        case PB_LOBBY_FAILED:
            return Rml::String("Error: ") + partyboard_netplay_error();
        }
        return "";
    }

    Rml::String players_text()
    {
        const int count = partyboard_netplay_member_count();
        if (count == 0) {
            return "-";
        }
        Rml::String text;
        for (int i = 0; i < count; i++) {
            if (i) {
                text += ", ";
            }
            text += "P" + std::to_string(i + 1) + " " + partyboard_netplay_member_name(i);
        }
        return text;
    }

    void save()
    {
        config::Save();
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
                                      .key = "Board",
                                      .getValue = [] {
                                          const int board = getSettings().netplay.board.getValue();
                                          return Rml::String(kBoardNames[board >= 0 && board < 6 ? board : 0]);
                                      },
                                  }),
            rightPane, [](Pane &pane) {
                for (int i = 0; i < static_cast<int>(kBoardNames.size()); i++) {
                    pane.add_button({
                                        .text = kBoardNames[i],
                                        .isSelected = [i] { return getSettings().netplay.board.getValue() == i; },
                                    })
                        .on_pressed([i] {
                            getSettings().netplay.board.setValue(i);
                            save();
                        });
                }
            });
        leftPane.register_control(leftPane.add_child<NumberButton>(NumberButton::Props {
                                      .key = "Turns",
                                      .getValue = [] { return getSettings().netplay.turns.getValue(); },
                                      .setValue = [](int value) {
                                          getSettings().netplay.turns.setValue(value);
                                          save();
                                      },
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
                             "(each frame is about 17 ms).");
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
                                          partyboard_netplay_begin(getSettings().netplay.server.getValue().c_str(),
                                              player_name().c_str(), 1, nullptr);
                                      }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Create a room and get a 4-letter code to share. You'll be player 1; others "
                             "become players 2-4 in the order they join, and CPUs fill the rest.");
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
                                          partyboard_netplay_begin(getSettings().netplay.server.getValue().c_str(),
                                              player_name().c_str(), 0, gJoinCode.c_str());
                                      }),
            rightPane, [](Pane &pane) { pane.add_rml("Join the room with the code above."); });

        // ---- Room ----
        leftPane.add_section("Room");
        leftPane.register_control(leftPane.add_select_button({
                                      .key = "Status",
                                      .getValue = [] { return status_text(); },
                                      .submit = false,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("Connection and room status."); });
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
                                      .key = "Players",
                                      .getValue = [] { return players_text(); },
                                      .submit = false,
                                  }),
            rightPane, [](Pane &pane) { pane.add_rml("Everyone in the room, in port order."); });
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
                                          static const int chars[4] = { 0, 1, 2, 3 };
                                          partyboard_netplay_start_game(s.board.getValue(), s.turns.getValue(),
                                              s.inputDelay.getValue(), 1, chars, 0);
                                      }),
            rightPane, [](Pane &pane) {
                pane.add_rml("Host only: start the party for everyone in the room. It boots straight into the "
                             "board with Mario, Luigi, Peach and Yoshi.");
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
