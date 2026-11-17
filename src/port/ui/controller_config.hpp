// Credits: TwilitRealm

#pragma once

#include "window.hpp"

#include <pad.h>

#include <vector>

namespace partyboard::ui {

class ControllerConfigWindow : public Window {
public:
    ControllerConfigWindow();

    void update() override;
    void hide(bool close) override;

private:
    enum class Page {
        Controller,
        Buttons,
        Triggers,
        Sticks,
        Rumble,
    };

    void build_port_tab(Rml::Element *content, int port);
    void render_page(class Pane &pane, int port, Page page);
    void refresh_controller_page();
    void poll_pending_binding();
    void finish_pending_binding(int completedPort);
    void unmap_pending_binding();
    bool capture_active() const;
    bool pending_input_neutral() const;
    Rml::String pending_button_label() const;
    Rml::String pending_axis_label() const;
    void cancel_pending_binding();
    void finish_pending_key_binding();
    Rml::String pending_key_label() const;
    void stop_rumble_test();

    Page mPage = Page::Controller;
    Pane *mRightPane = nullptr;
    int mActivePort = 0;
    int mPendingPort = -1;
    bool mPendingBindingArmed = false;
    bool mSuppressNavigationUntilNeutral = false;
    int mSuppressNavigationPort = -1;
    PADButtonMapping *mPendingButtonMapping = nullptr;
    PADAxisMapping *mPendingAxisMapping = nullptr;
    int mPendingKeyButton = -1;
    int mPendingKeyAxis = -1;
    bool mRumbleTestActive = false;
    int mRumbleTestPort = -1;
};

// Button icon test: shows each game button's picture (as the Button Icons setting draws it for this controller) and
// waits for you to press the button you think it is; the result names the physical button it really is.
class GlyphTestWindow : public Window {
public:
    GlyphTestWindow();

    void update() override;
    void hide(bool close) override;

private:
    void start();
    void stop(bool finished);
    void skip();
    void poll();
    void render();
    bool capturing() const { return mRunning || mSuppressUntilNeutral; }

    class Pane *mRightPane = nullptr;
    bool mRunning = false;
    bool mHeld[4] = {};
    bool mDirty = true;
    bool mSuppressUntilNeutral = false;
    bool mFinished = false;
    int mStep = 0;
    int mPort = 0;
    Rml::String mNote;
    std::vector<Rml::String> mResults;
};

} // namespace partyboard::ui
