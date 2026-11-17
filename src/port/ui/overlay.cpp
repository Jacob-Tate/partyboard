// Credits: TwilitRealm

#include "overlay.hpp"

#include "aurora/lib/logging.hpp"
#include "port/achievements.h"
#include "magic_enum.hpp"
#include "window.hpp"

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_timer.h>
#include <algorithm>
#include <dolphin/pad.h>
#include <port/settings.h>
#include <port/autotest.h>
#include <port/netplay.h>

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

namespace partyboard::ui {
namespace {
    aurora::Module Log { "partyboard::ui::overlay" };

    const Rml::String kDocumentSource = R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/overlay.rcss" />
</head>
<body>
    <fps id="fps" />
    <netstats id="netstats" />
</body>
</rml>
)RML";

    constexpr auto kMenuNotificationDuration = std::chrono::milliseconds(2500);

    constexpr std::array<const char *, 4> kFpsCorners = { "tl", "tr", "bl", "br" };

    Rml::Element *create_toast(Rml::Element *parent, const Toast &toast)
    {
        auto *elem = append(parent, "toast");
        if (!toast.type.empty()) {
            elem->SetClass(toast.type, true);
        }
        {
            auto *heading = append(elem, "heading");
            if (toast.title.starts_with("<")) {
                heading->SetInnerRML(toast.title);
            }
            else {
                auto *span = append(heading, "span");
                span->SetInnerRML(toast.title);
            }
            if (toast.type == "achievement") {
                auto *icon = append(heading, "icon");
                icon->SetClass("trophy", true);
                // mDoAud_seStartMenu(kSoundAchievementUnlock); // TODO PC
            }
            else if (toast.type == "controller") {
                auto *icon = append(heading, "icon");
                icon->SetClass("controller", true);
            }
        }
        {
            auto *message = append(elem, "message");
            if (toast.content.starts_with("<")) {
                message->SetInnerRML(toast.content);
            }
            else {
                auto *span = append(message, "span");
                span->SetInnerRML(toast.content);
            }
        }
        {
            auto *progress = append(elem, "progress");
            progress->SetAttribute("value", 1.f);
        }
        return elem;
    }

    Rml::Element *create_controller_warning(Rml::Element *parent)
    {
        auto *elem = append(parent, "toast");
        elem->SetClass("controller-warning", true);

        auto *heading = append(elem, "heading");
        auto *title = append(heading, "span");
        title->SetInnerRML("No controller assigned");
        auto *icon = append(heading, "icon");
        icon->SetClass("warning", true);

        auto *message = append(elem, "message");
        auto *content = append(message, "span");
        content->SetInnerRML("Configure controller port 1 in Settings.");

        return elem;
    }

    SDL_Gamepad *gamepad_for_port(u32 port) noexcept
    {
        const s32 index = PADGetIndexForPort(port);
        if (index < 0) {
            return nullptr;
        }
        return PADGetSDLGamepadForIndex(static_cast<u32>(index));
    }

    Rml::String back_button_name()
    {
        if (auto *gamepad = gamepad_for_port(PAD_CHAN0)) {
            switch (SDL_GetGamepadType(gamepad)) {
                case SDL_GAMEPAD_TYPE_PS3:
                    return "Select";
                case SDL_GAMEPAD_TYPE_PS4:
                    return "Share";
                case SDL_GAMEPAD_TYPE_PS5:
                    return "Create";
                case SDL_GAMEPAD_TYPE_XBOX360:
                    return "Back";
                case SDL_GAMEPAD_TYPE_XBOXONE:
                    return "View";
                case SDL_GAMEPAD_TYPE_GAMECUBE:
                    return "R + Start";
                default:
                    break;
            }
        }
        return "Back";
    }

#if defined(TARGET_ANDROID) || (defined(__APPLE__) && TARGET_OS_IOS && !TARGET_OS_MACCATALYST)
    constexpr auto kMenuNotificationPrefix = "3-finger tap or";
#else
    constexpr auto kMenuNotificationPrefix = "Press F1 or";
#endif

    Rml::Element *create_menu_notification(Rml::Element *parent)
    {
        auto *elem = append(parent, "toast");
        elem->SetClass("menu-notification", true);

        auto *message = append(elem, "message");
        auto *row = append(message, "row");
        append(row, "span")->SetInnerRML(kMenuNotificationPrefix);
        auto *icon = append(row, "icon");
        icon->SetClass("controller", true);
        append(row, "span")->SetInnerRML(escape(back_button_name()));
        append(row, "span")->SetInnerRML("to open menu");

        return elem;
    }

    // F2 panel: one row per seat, then the latest notable stutters.
    Rml::String netstats_rml()
    {
        PbNetSeatStats seats[4];
        if (!partyboard_netplay_get_stats(seats)) {
            return "<h>Online stutters</h><p class=\"muted\">Shows who is holding the game up during an online game.</p>"
                   "<p class=\"muted\">F2 to close</p>";
        }
        const int secs = partyboard_netplay_stats_seconds();
        Rml::String out = fmt::format("<h>Online stutters</h><table><tr class=\"head\"><td>Player</td>"
                                      "<td>Ping</td><td>Jitter</td><td>Loss</td><td>Late {}s</td><td>Late all</td>"
                                      "<td>Worst</td><td>Slow {}s</td><td>Slow all</td><td>Worst</td><td>Waited</td>"
                                      "<td>Verdict</td></tr>",
            secs, secs);
        for (int port = 0; port < 4; port++) {
            const PbNetSeatStats &st = seats[port];
            if (!st.human) {
                out += fmt::format("<tr class=\"muted\"><td>P{} CPU</td></tr>", port + 1);
                continue;
            }
            const std::string_view verdict = st.verdict;
            const char *cls = verdict == "Slow PC" || verdict == "Connection" ? "bad" : verdict == "Unstable link" ? "warn" : "good";
            const Rml::String name = fmt::format("P{} {}{}", port + 1, escape(st.name), st.isMe ? " (you)" : "");
            if (!st.known) {
                out += fmt::format("<tr><td>{}</td><td>...</td></tr>", name);
                continue;
            }
            const auto ms = [](int v) { return v > 0 ? fmt::format("{} ms", v) : Rml::String("-"); };
            out += fmt::format("<tr><td>{}</td><td>{} ms</td><td>{} ms</td><td>{}.{}%</td><td>{}</td><td>{}</td><td>{}</td>"
                               "<td>{}</td><td>{}</td><td>{}</td><td>{}</td><td class=\"verdict {}\">{}</td></tr>",
                name, st.pingMs, st.jitterMs, st.lossPermille / 10, st.lossPermille % 10, st.lateRecent, st.lateTotal,
                ms(st.lateWorstMs), st.slowRecent, st.slowTotal, ms(st.slowWorstMs), st.stallTotal, cls, st.verdict);
        }
        out += "</table>";
        out += "<p class=\"muted\">Late: frames everyone waited for this player's input. Slow: frames their own PC "
               "took 25+ ms. Late + slow = their PC; late alone = their connection. Waited: their own hitches "
               "caused by someone else.</p>";
        bool any = false;
        for (int i = 0; const char *ev = partyboard_netplay_stats_event(i); i++) {
            if (!any) {
                out += "<h2>Recent</h2>";
                any = true;
            }
            out += fmt::format("<p>{}</p>", escape(ev));
        }
        out += "<p class=\"muted\">F2 to close. Also written to partyboard.log ([netstats]).</p>";
        return out;
    }

    void remove_element(Rml::Element *&elem) noexcept
    {
        if (elem == nullptr) {
            return;
        }
        if (auto *parent = elem->GetParentNode()) {
            parent->RemoveChild(elem);
        }
        elem = nullptr;
    }

} // namespace

// https://vplesko.com/posts/how_to_implement_an_fps_counter.html
void Overlay::advance_fps_counter(float &outFps, Uint64 perfFreq)
{
    if (perfFreq == 0) {
        outFps = 0.f;
        return;
    }

    const Uint64 curr = SDL_GetPerformanceCounter();
    if (!mFpsHavePrevCounter) {
        mFpsPrevCounter = curr;
        mFpsHavePrevCounter = true;
        outFps = 0.f;
        return;
    }

    const Uint64 processingTicks = curr - mFpsPrevCounter;
    mFpsPrevCounter = curr;

    mFpsFrameEvents.push_back({ curr, processingTicks });
    mFpsSumTicks += processingTicks;

    while (!mFpsFrameEvents.empty() && mFpsFrameEvents.front().endCounter + perfFreq < curr) {
        mFpsSumTicks -= mFpsFrameEvents.front().processingTicks;
        mFpsFrameEvents.pop_front();
    }

    const auto n = mFpsFrameEvents.size();
    if (n == 0 || mFpsSumTicks == 0) {
        outFps = 0.f;
        return;
    }

    const double avgSeconds = static_cast<double>(mFpsSumTicks) / static_cast<double>(n) / static_cast<double>(perfFreq);
    outFps = static_cast<float>(1.0 / avgSeconds);
}

Overlay::Overlay()
    : Document(kDocumentSource)
{
    mFpsCounter = mDocument->GetElementById("fps");
    mNetStats = mDocument->GetElementById("netstats");

    listen(mDocument, Rml::EventId::Focus, [](Rml::Event &) { Log.warn("Overlay received focus"); });
    listen(mDocument, Rml::EventId::Transitionend, [this](Rml::Event &event) {
        if (event.GetTargetElement() == mCurrentToast) {
            if (get_toasts().empty() || clock::now() >= mCurrentToastStartTime + get_toasts().front().duration) {
                mCurrentToast->SetPseudoClass("done", true);
            }
        }
        else if (mControllerWarning != nullptr && event.GetTargetElement() == mControllerWarning && !mControllerWarning->HasAttribute("open")) {
            mControllerWarning->SetPseudoClass("done", true);
        }
        else if (mMenuNotification != nullptr && event.GetTargetElement() == mMenuNotification && !mMenuNotification->HasAttribute("open")) {
            mMenuNotification->SetPseudoClass("done", true);
        }
    });
}

void Overlay::show()
{
    if (mDocument != nullptr) {
        mDocument->Show(Rml::ModalFlag::None, Rml::FocusFlag::None, Rml::ScrollFlag::None);
    }
}

void Overlay::update()
{
    Document::update();
    if (mDocument == nullptr) {
        return;
    }

    if (mFpsCounter != nullptr) {
        if (getSettings().video.enableFpsOverlay.getValue()) {
            const int idx = getSettings().video.fpsOverlayCorner.getValue();
            mFpsCounter->SetAttribute("open", "");
            mFpsCounter->SetAttribute("corner", kFpsCorners[idx]);

            const Uint64 perfFreq = SDL_GetPerformanceFrequency();
            float fps = 0.f;
            advance_fps_counter(fps, perfFreq);

            const Uint64 now = SDL_GetPerformanceCounter();
            // Limit updates to twice per second
            const bool refreshLabel
                = perfFreq == 0 || mFpsLastUpdate == 0 || static_cast<double>(now - mFpsLastUpdate) >= 0.5 * static_cast<double>(perfFreq);
            if (refreshLabel) {
                mFpsLastUpdate = now;
                mFpsCounter->SetInnerRML(escape(fmt::format("{:.0f} FPS", fps)));
            }
        }
        else {
            mFpsCounter->RemoveAttribute("open");
            mFpsFrameEvents.clear();
            mFpsSumTicks = 0;
            mFpsHavePrevCounter = false;
            mFpsLastUpdate = 0;
        }
    }

    if (mNetStats != nullptr) {
        if (netstats_open()) {
            const Uint64 now = SDL_GetPerformanceCounter();
            if (!mNetStats->HasAttribute("open") ||
                static_cast<double>(now - mNetStatsLastUpdate) >= 0.5 * static_cast<double>(SDL_GetPerformanceFrequency())) {
                mNetStatsLastUpdate = now;
                mNetStats->SetInnerRML(netstats_rml());
            }
            mNetStats->SetAttribute("open", "");
        }
        else if (mNetStats->HasAttribute("open")) {
            mNetStats->RemoveAttribute("open");
        }
    }

    u32 buttonCount;
    // All-CPU quickstart runs don't need a controller; any game with a human (local or online) does.
    const bool showControllerWarning = (!partyboard_autotest_quickstart() || partyboard_autotest_get()->humanMask != 0)
        && PADGetIndexForPort(PAD_CHAN0) < 0 && PADGetKeyButtonBindings(PAD_CHAN0, &buttonCount) == nullptr
        && dynamic_cast<Window *>(top_document()) == nullptr && dynamic_cast<WindowSmall *>(top_document()) == nullptr;
    if (showControllerWarning && mControllerWarning == nullptr) {
        mControllerWarning = create_controller_warning(mDocument);
    }
    else if (showControllerWarning && mControllerWarning != nullptr) {
        mControllerWarning->SetAttribute("open", "");
        mControllerWarning->SetPseudoClass("opened", true);
        mControllerWarning->SetPseudoClass("done", false);
    }
    else if (!showControllerWarning && mControllerWarning != nullptr) {
        if (mControllerWarning->IsPseudoClassSet("done") || !mControllerWarning->IsPseudoClassSet("opened")) {
            remove_element(mControllerWarning);
        }
        else {
            mControllerWarning->RemoveAttribute("open");
        }
    }

    if (mMenuNotification != nullptr) {
        if (clock::now() >= mMenuNotificationStartTime + kMenuNotificationDuration) {
            if (mMenuNotification->IsPseudoClassSet("done") || !mMenuNotification->IsPseudoClassSet("opened")) {
                remove_element(mMenuNotification);
            }
            else {
                mMenuNotification->RemoveAttribute("open");
            }
        }
        else {
            mMenuNotification->SetAttribute("open", "");
            mMenuNotification->SetPseudoClass("opened", true);
            mMenuNotification->SetPseudoClass("done", false);
        }
    }
    if (consume_menu_notification_request()) {
        if (mMenuNotification == nullptr) {
            mMenuNotification = create_menu_notification(mDocument);
        }
        mMenuNotificationStartTime = clock::now();
    }

    auto &toasts = get_toasts();
    if (mCurrentToast == nullptr) {
        if (!toasts.empty()) {
            const auto &toast = toasts.front();
            mCurrentToast = create_toast(mDocument, toast);
            mCurrentToastStartTime = clock::now();
        }
    }
    else if (!toasts.empty()) {
        const auto &toast = toasts.front();
        const float duration = std::chrono::duration<float>(toast.duration).count();
        const float elapsed = std::chrono::duration<float>(clock::now() - mCurrentToastStartTime).count();
        const float ratio = duration > 0.0f ? std::clamp(elapsed / duration, 0.0f, 1.0f) : 1.0f;
        const auto remaining = 1.f - ratio;
        Rml::ElementList list;
        mDocument->GetElementsByTagName(list, "progress");
        for (auto *elem : list) {
            elem->SetAttribute("value", remaining);
        }
        if (remaining == 0.f) {
            if (mCurrentToast->IsPseudoClassSet("done") ||
                // Fallback for large gaps in time where we never actually opened it
                !mCurrentToast->IsPseudoClassSet("opened")) {
                remove_element(mCurrentToast);
                toasts.pop_front();
            }
            else {
                mCurrentToast->RemoveAttribute("open");
            }
        }
        else {
            mCurrentToast->SetAttribute("open", "");
            mCurrentToast->SetPseudoClass("opened", true);
        }
    }
}

bool Overlay::handle_nav_command(Rml::Event &event, NavCommand cmd)
{
    Log.warn("Overlay received nav command: {}", magic_enum::enum_name(cmd));
    return false;
}

} // namespace partyboard::ui
