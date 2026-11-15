#pragma once
#include "window.hpp"

namespace partyboard::ui {

// "Play Online" screen opened from the prelaunch menu: host or join a room on the relay server.
// When the host starts, every player's game boots straight into the same party.
class OnlineWindow : public Window {
public:
    OnlineWindow();

    void update() override;
    void hide(bool close) override;
};

} // namespace partyboard::ui
