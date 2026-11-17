// Credits: TwilitRealm

#include "controller_config.hpp"

#include "bool_button.hpp"
#include "button.hpp"
#include "number_button.hpp"
#include "pane.hpp"

#include "port/button_icons.h"

#include <aurora/rmlui.hpp>


#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <fmt/format.h>

#include <array>
#include <cstdio>
#include <map>
#include <optional>
#include <span>
#include <string_view>
#include <string>
#include <utility>
#include <vector>

namespace partyboard::ui {
namespace {

    bool keyboard_active(int port)
    {
        u32 count = 0;
        return PADGetKeyButtonBindings(static_cast<u32>(port), &count) != nullptr;
    }

    Rml::String current_controller_name(int port)
    {
        const char *name = PADGetName(port);
        if (name != nullptr) {
            return name;
        }
        return keyboard_active(port) ? "Keyboard" : "None";
    }

    Rml::String controller_index_name(u32 index)
    {
        const char *name = PADGetNameForControllerIndex(index);
        if (name == nullptr) {
            return fmt::format("Controller {}", index + 1);
        }
        return name;
    }

    SDL_Gamepad *gamepad_for_port(int port)
    {
        const s32 index = PADGetIndexForPort(port);
        if (index < 0) {
            return nullptr;
        }
        return PADGetSDLGamepadForIndex(static_cast<u32>(index));
    }

    struct SpecificButtonName {
        SDL_GamepadType type;
        const char *name;
    };

    struct ButtonNames {
        SDL_GamepadButton button;
        std::vector<SpecificButtonName> names;
    };

    // clang-format off
const std::vector<ButtonNames> kGamepadButtonNames = {
    { SDL_GAMEPAD_BUTTON_LEFT_STICK, {
        {SDL_GAMEPAD_TYPE_PS3, "L3"},
        {SDL_GAMEPAD_TYPE_PS4, "L3"},
        {SDL_GAMEPAD_TYPE_PS5, "L3"},
        {SDL_GAMEPAD_TYPE_XBOX360, "Left Stick"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "Left Stick"},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "Control Stick"},
    }},
    { SDL_GAMEPAD_BUTTON_RIGHT_STICK, {
        {SDL_GAMEPAD_TYPE_PS3, "R3"},
        {SDL_GAMEPAD_TYPE_PS4, "R3"},
        {SDL_GAMEPAD_TYPE_PS5, "R3"},
        {SDL_GAMEPAD_TYPE_XBOX360, "Right Stick"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "Right Stick"},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "C Stick"},
    }},
    { SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, {
        {SDL_GAMEPAD_TYPE_PS3, "L1"},
        {SDL_GAMEPAD_TYPE_PS4, "L1"},
        {SDL_GAMEPAD_TYPE_PS5, "L1"},
        {SDL_GAMEPAD_TYPE_XBOX360, "LB"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "LB"},
    }},
    { SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, {
        {SDL_GAMEPAD_TYPE_PS3, "R1"},
        {SDL_GAMEPAD_TYPE_PS4, "R1"},
        {SDL_GAMEPAD_TYPE_PS5, "R1"},
        {SDL_GAMEPAD_TYPE_XBOX360, "RB"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "RB"},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "Z"},
    }},
    { SDL_GAMEPAD_BUTTON_BACK, {
        {SDL_GAMEPAD_TYPE_PS3, "Select"},
        {SDL_GAMEPAD_TYPE_PS4, "Share"},
        {SDL_GAMEPAD_TYPE_PS5, "Create"},
        {SDL_GAMEPAD_TYPE_XBOX360, "Back"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "View"},
    }},
    { SDL_GAMEPAD_BUTTON_START, {
        {SDL_GAMEPAD_TYPE_PS3, "Start"},
        {SDL_GAMEPAD_TYPE_PS4, "Options"},
        {SDL_GAMEPAD_TYPE_PS5, "Options"},
        {SDL_GAMEPAD_TYPE_XBOX360, "Start"},
        {SDL_GAMEPAD_TYPE_XBOXONE, "Menu"},
        {SDL_GAMEPAD_TYPE_GAMECUBE, "Start/Pause"},
    }},
};
    // clang-format on

    Rml::String native_button_name(SDL_Gamepad *gamepad, u32 buttonUntyped)
    {
        if (buttonUntyped == PAD_NATIVE_BUTTON_INVALID) {
            return "Not bound";
        }

        auto button = static_cast<SDL_GamepadButton>(buttonUntyped);
        if (gamepad != nullptr) {
            switch (SDL_GetGamepadButtonLabel(gamepad, button)) {
                case SDL_GAMEPAD_BUTTON_LABEL_A:
                    return "A";
                case SDL_GAMEPAD_BUTTON_LABEL_B:
                    return "B";
                case SDL_GAMEPAD_BUTTON_LABEL_X:
                    return "X";
                case SDL_GAMEPAD_BUTTON_LABEL_Y:
                    return "Y";
                case SDL_GAMEPAD_BUTTON_LABEL_CROSS:
                    return "Cross";
                case SDL_GAMEPAD_BUTTON_LABEL_CIRCLE:
                    return "Circle";
                case SDL_GAMEPAD_BUTTON_LABEL_TRIANGLE:
                    return "Triangle";
                case SDL_GAMEPAD_BUTTON_LABEL_SQUARE:
                    return "Square";
                default:
                    break;
            }
        }

        const SDL_GamepadType type = gamepad != nullptr ? SDL_GetGamepadType(gamepad) : SDL_GAMEPAD_TYPE_UNKNOWN;
        for (const auto &buttonNames : kGamepadButtonNames) {
            if (buttonNames.button != button) {
                continue;
            }

            for (const auto &name : buttonNames.names) {
                if (name.type == type) {
                    return name.name;
                }
            }
        }

        switch (button) {
            case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
                return "D-pad left";
            case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
                return "D-pad right";
            case SDL_GAMEPAD_BUTTON_DPAD_UP:
                return "D-pad up";
            case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
                return "D-pad down";
            default:
                break;
        }

        if (const char *name = PADGetNativeButtonName(buttonUntyped)) {
            return name;
        }
        return "Unknown";
    }

    Rml::String native_axis_name(const PADAxisMapping &mapping, SDL_Gamepad *gamepad)
    {
        if (mapping.nativeAxis.nativeAxis != -1) {
            Rml::String value = PADGetNativeAxisName(mapping.nativeAxis);
            if (mapping.padAxis != PAD_AXIS_TRIGGER_L && mapping.padAxis != PAD_AXIS_TRIGGER_R) {
                value += mapping.nativeAxis.sign == AXIS_SIGN_POSITIVE ? "+" : "-";
            }
            return value;
        }

        if (mapping.nativeButton != -1) {
            return native_button_name(gamepad, static_cast<u32>(mapping.nativeButton));
        }

        return "Not bound";
    }

    bool is_dpad_button(PADButton button)
    {
        return button == PAD_BUTTON_UP || button == PAD_BUTTON_DOWN || button == PAD_BUTTON_LEFT || button == PAD_BUTTON_RIGHT;
    }

    bool is_action_button(PADButton button)
    {
        return button == PAD_BUTTON_A || button == PAD_BUTTON_B || button == PAD_BUTTON_X || button == PAD_BUTTON_Y || button == PAD_BUTTON_START
            || button == PAD_TRIGGER_Z;
    }

    bool input_neutral(int port)
    {
        if (port < 0) {
            return true;
        }
        return PADGetNativeButtonPressed(port) == -1 && PADGetNativeAxisPulled(port).nativeAxis == -1;
    }

    // A Keydown event with KI_ESCAPE may have been dispatched from the controller bindings,
    // so instead poll the keyboard input directly for Escape-to-unbind
    bool keyboard_escape_pressed() {
        int keyCount = 0;
        const bool* keys = SDL_GetKeyboardState(&keyCount);
        if (keys == nullptr || SDL_SCANCODE_ESCAPE >= keyCount || !keys[SDL_SCANCODE_ESCAPE]) {
            return false;
        }
        for (int i = 0; i < keyCount; ++i) {
            if (i != SDL_SCANCODE_ESCAPE && keys[i]) {
                return false;
            }
        }
        return true;
    }

    Rml::String keyboard_key_name(s32 scancode)
    {
        if (scancode == PAD_KEY_INVALID) {
            return "Not bound";
        }
        switch (scancode) {
            case PAD_KEY_MOUSE_LEFT:
                return "Mouse Left";
            case PAD_KEY_MOUSE_MIDDLE:
                return "Mouse Middle";
            case PAD_KEY_MOUSE_RIGHT:
                return "Mouse Right";
            case PAD_KEY_MOUSE_X1:
                return "Mouse X1";
            case PAD_KEY_MOUSE_X2:
                return "Mouse X2";
            default:
                break;
        }
        if (scancode < 0) {
            return "Unknown";
        }
        const char *name = SDL_GetScancodeName(static_cast<SDL_Scancode>(scancode));
        if (name == nullptr || name[0] == '\0') {
            return "Unknown";
        }
        return name;
    }

    bool keyboard_neutral()
    {
        int keyCount = 0;
        const bool *keys = SDL_GetKeyboardState(&keyCount);
        if (keys != nullptr) {
            for (int i = 0; i < keyCount; ++i) {
                if (keys[i]) {
                    return false;
                }
            }
        }
        float x, y;
        if (SDL_GetMouseState(&x, &y) != 0) {
            return false;
        }
        return true;
    }

    s32 keyboard_key_pressed()
    {
        int keyCount = 0;
        const bool *keys = SDL_GetKeyboardState(&keyCount);
        if (keys != nullptr) {
            for (int i = 1; i < keyCount; ++i) {
                if (i == SDL_SCANCODE_ESCAPE) {
                    continue;
                }
                if (keys[i]) {
                    return static_cast<s32>(i);
                }
            }
        }
        float x, y;
        const auto mouseButtons = SDL_GetMouseState(&x, &y);
        for (int btn = 1; btn <= 5; ++btn) {
            if (mouseButtons & (1u << (btn - 1))) {
                return -(btn + 1); // maps to PAD_KEY_MOUSE_LEFT (-2), etc.
            }
        }
        return PAD_KEY_INVALID;
    }

    u16 percent_to_raw(int percent)
    {
        return static_cast<u16>((static_cast<float>(percent) / 100.f) * 32767.f);
    }

    int deadzone_raw_to_percent(u16 raw)
    {
        return static_cast<int>((static_cast<float>(raw) * 100.f) / 32767.f + 0.5f);
    }

    int rumble_raw_to_percent(u16 raw)
    {
        return static_cast<int>((static_cast<float>(raw) / 32767.f) * 100.f + 0.5f);
    }

} // namespace

ControllerConfigWindow::ControllerConfigWindow()
{
    listen(
        Rml::EventId::Keydown,
        [this](Rml::Event &event) {
            if (capture_active() || mSuppressNavigationUntilNeutral) {
                event.StopPropagation();
            }
        },
        true);
    if (auto *context = mDocument != nullptr ? mDocument->GetContext() : nullptr) {
        if (auto *root = context->GetRootElement()) {
            mListeners.emplace_back(
                std::make_unique<ScopedEventListener>(root, "controllerchange", [this](Rml::Event &) { refresh_controller_page(); }));
        }
    }

    for (int port = PAD_CHAN0; port < PAD_CHANMAX; ++port) {
        add_tab(fmt::format("Port {}", port + 1), [this, port](Rml::Element *content) {
            if (mPendingPort != -1 && mPendingPort != port) {
                cancel_pending_binding();
            }
            build_port_tab(content, port);
        });
    }
}

void ControllerConfigWindow::hide(bool close)
{
    stop_rumble_test();
    cancel_pending_binding();
    Window::hide(close);
}

void ControllerConfigWindow::update()
{
    poll_pending_binding();
    Window::update();
}

void ControllerConfigWindow::build_port_tab(Rml::Element *content, int port)
{
    stop_rumble_test();
    auto &leftPane = add_child<Pane>(content, Pane::Type::Controlled);
    auto &rightPane = add_child<Pane>(content, Pane::Type::Uncontrolled);
    mRightPane = &rightPane;
    mActivePort = port;

    auto addPageButton = [this, &leftPane, &rightPane, port](Page page, Rml::String key, auto getValue, auto isDisabled) {
        leftPane.register_control(leftPane.add_select_button({
                                      .key = std::move(key),
                                      .getValue = std::move(getValue),
                                      .isDisabled = std::move(isDisabled),
                                  }),
            rightPane, [this, port, page](Pane &pane) {
                mPage = page;
                render_page(pane, port, page);
            });
    };

    addPageButton(Page::Controller, "Controller", [port] { return current_controller_name(port); }, [] { return false; });
    addPageButton(Page::Buttons, "Buttons", [] { return Rml::String(">"); }, [] { return false; });
    addPageButton(Page::Triggers, "Triggers", [] { return Rml::String(">"); }, [] { return false; });
    addPageButton(Page::Sticks, "Sticks", [] { return Rml::String(">"); }, [] { return false; });
    addPageButton(Page::Rumble, "Rumble", [] { return Rml::String(">"); }, [port] { return !PADSupportsRumbleIntensity(static_cast<u32>(port)); });

    leftPane.add_section("Options");
    leftPane.register_control(leftPane.add_child<BoolButton>(BoolButton::Props {
                                  .key = "Enable Dead Zones",
                                  .getValue =
                                      [port] {
                                          PADDeadZones *deadZones = PADGetDeadZones(port);
                                          return deadZones != nullptr && deadZones->useDeadzones;
                                      },
                                  .setValue =
                                      [port](bool value) {
                                          if (PADDeadZones *deadZones = PADGetDeadZones(port)) {
                                              deadZones->useDeadzones = value;
                                              PADSerializeMappings();
                                          }
                                      },
                                  .isDisabled = [port] { return PADGetDeadZones(port) == nullptr; },
                              }),
        rightPane, [](Pane &pane) { pane.add_text("Apply configured dead zones to the sticks and analog triggers."); });
    leftPane.register_control(leftPane.add_child<BoolButton>(BoolButton::Props {
                                  .key = "Emulate Triggers",
                                  .getValue =
                                      [port] {
                                          PADDeadZones *deadZones = PADGetDeadZones(port);
                                          return deadZones != nullptr && deadZones->emulateTriggers;
                                      },
                                  .setValue =
                                      [port](bool value) {
                                          if (PADDeadZones *deadZones = PADGetDeadZones(port)) {
                                              deadZones->emulateTriggers = value;
                                              PADSerializeMappings();
                                          }
                                      },
                                  .isDisabled = [port] { return PADGetDeadZones(port) == nullptr; },
                              }),
        rightPane, [](Pane &pane) { pane.add_text("Treat analog trigger movement as digital L and R button input."); });

    render_page(rightPane, port, mPage);
}

void ControllerConfigWindow::render_page(Pane &pane, int port, Page page)
{
    pane.clear();

    switch (page) {
        case Page::Controller: {
            pane.add_button({
                                .text = "None",
                                .isSelected = [port] { return PADGetIndexForPort(port) < 0 && !keyboard_active(port); },
                            })
                .on_pressed([this, port] {
                    // mDoAud_seStartMenu(kSoundItemChange); // TODO PC
                    cancel_pending_binding();
                    PADClearPort(port);
                    PADSetKeyboardActive(static_cast<u32>(port), FALSE);
                    PADSerializeMappings();
                });

            pane.add_button({
                                .text = "Keyboard",
                                .isSelected = [port] { return keyboard_active(port); },
                            })
                .on_pressed([this, port] {
                    // mDoAud_seStartMenu(kSoundItemChange); // TODO PC
                    cancel_pending_binding();
                    PADClearPort(port);
                    PADSetKeyboardActive(static_cast<u32>(port), TRUE);
                    PADSerializeMappings();
                });

            const u32 controllerCount = PADCount();
            if (controllerCount == 0) {
                pane.add_text("No controllers detected");
                break;
            }

            for (u32 i = 0; i < controllerCount; ++i) {
                pane.add_button({
                                    .text = controller_index_name(i),
                                    .isSelected = [port, i] { return PADGetIndexForPort(port) == static_cast<s32>(i); },
                                })
                    .on_pressed([this, port, i] {
                        // mDoAud_seStartMenu(kSoundItemChange); // TODO PC
                        cancel_pending_binding();
                        PADSetKeyboardActive(static_cast<u32>(port), FALSE);
                        PADSetPortForIndex(i, port);
                        PADSerializeMappings();
                    });
            }
            break;
        }
        case Page::Buttons: {
            if (keyboard_active(port)) {
                auto addKeyButton = [&](PADButton button) {
                    pane.add_select_button({
                                               .key = PADGetButtonName(button),
                                               .getValue =
                                                   [this, port, button] {
                                                       if (mPendingKeyButton == static_cast<int>(button)) {
                                                           return pending_key_label();
                                                       }
                                                       u32 count = 0;
                                                       PADKeyButtonBinding *bindings = PADGetKeyButtonBindings(static_cast<u32>(port), &count);
                                                       if (bindings == nullptr) {
                                                           return Rml::String("Not bound");
                                                       }
                                                       for (u32 i = 0; i < PAD_BUTTON_COUNT; ++i) {
                                                           if (bindings[i].padButton == button) {
                                                               return keyboard_key_name(bindings[i].scancode);
                                                           }
                                                       }
                                                       return Rml::String("Not bound");
                                                   },
                                           })
                        .on_pressed([this, port, button] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingKeyButton = static_cast<int>(button);
                        });
                };

                pane.add_section("Buttons");
                addKeyButton(PAD_BUTTON_A);
                addKeyButton(PAD_BUTTON_B);
                addKeyButton(PAD_BUTTON_X);
                addKeyButton(PAD_BUTTON_Y);
                addKeyButton(PAD_BUTTON_START);
                addKeyButton(PAD_TRIGGER_Z);

                pane.add_section("D-Pad");
                addKeyButton(PAD_BUTTON_UP);
                addKeyButton(PAD_BUTTON_DOWN);
                addKeyButton(PAD_BUTTON_LEFT);
                addKeyButton(PAD_BUTTON_RIGHT);
                break;
            }

            u32 buttonCount = 0;
            PADButtonMapping *mappings = PADGetButtonMappings(port, &buttonCount);
            if (mappings == nullptr) {
                pane.add_text("No controller selected");
                break;
            }

            SDL_Gamepad *gamepad = gamepad_for_port(port);
            pane.add_section("Buttons");
            for (u32 i = 0; i < buttonCount; ++i) {
                PADButtonMapping &mapping = mappings[i];
                if (!is_action_button(mapping.padButton)) {
                    continue;
                }

                pane.add_select_button({
                                           .key = PADGetButtonName(mapping.padButton),
                                           .getValue =
                                               [this, &mapping, gamepad] {
                                                   if (mPendingButtonMapping == &mapping) {
                                                       return pending_button_label();
                                                   }
                                                   return native_button_name(gamepad, mapping.nativeButton);
                                               },
                                       })
                    .on_pressed([this, port, &mapping] {
                        cancel_pending_binding();
                        mPendingPort = port;
                        mPendingBindingArmed = false;
                        mPendingButtonMapping = &mapping;
                    });
            }

            pane.add_section("D-Pad");
            for (u32 i = 0; i < buttonCount; ++i) {
                PADButtonMapping &mapping = mappings[i];
                if (!is_dpad_button(mapping.padButton)) {
                    continue;
                }

                pane.add_select_button({
                                           .key = PADGetButtonName(mapping.padButton),
                                           .getValue =
                                               [this, &mapping, gamepad] {
                                                   if (mPendingButtonMapping == &mapping) {
                                                       return pending_button_label();
                                                   }
                                                   return native_button_name(gamepad, mapping.nativeButton);
                                               },
                                       })
                    .on_pressed([this, port, &mapping] {
                        cancel_pending_binding();
                        mPendingPort = port;
                        mPendingBindingArmed = false;
                        mPendingButtonMapping = &mapping;
                    });
            }
            break;
        }
        case Page::Triggers: {
            if (keyboard_active(port)) {
                auto addKeyButton = [&](PADButton button) {
                    pane.add_select_button({
                                               .key = PADGetButtonName(button),
                                               .getValue =
                                                   [this, port, button] {
                                                       if (mPendingKeyButton == static_cast<int>(button)) {
                                                           return pending_key_label();
                                                       }
                                                       u32 count = 0;
                                                       PADKeyButtonBinding *bindings = PADGetKeyButtonBindings(static_cast<u32>(port), &count);
                                                       if (bindings == nullptr) {
                                                           return Rml::String("Not bound");
                                                       }
                                                       for (u32 i = 0; i < PAD_BUTTON_COUNT; ++i) {
                                                           if (bindings[i].padButton == button) {
                                                               return keyboard_key_name(bindings[i].scancode);
                                                           }
                                                       }
                                                       return Rml::String("Not bound");
                                                   },
                                           })
                        .on_pressed([this, port, button] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingKeyButton = static_cast<int>(button);
                        });
                };

                auto addKeyAxis = [&](PADAxis axis) {
                    pane.add_select_button({
                                               .key = PADGetAxisName(axis),
                                               .getValue =
                                                   [this, port, axis] {
                                                       if (mPendingKeyAxis == static_cast<int>(axis)) {
                                                           return pending_key_label();
                                                       }
                                                       u32 count = 0;
                                                       PADKeyAxisBinding *bindings = PADGetKeyAxisBindings(static_cast<u32>(port), &count);
                                                       if (bindings == nullptr) {
                                                           return Rml::String("Not bound");
                                                       }
                                                       for (u32 i = 0; i < PAD_AXIS_COUNT; ++i) {
                                                           if (bindings[i].padAxis == axis) {
                                                               return keyboard_key_name(bindings[i].scancode);
                                                           }
                                                       }
                                                       return Rml::String("Not bound");
                                                   },
                                           })
                        .on_pressed([this, port, axis] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingKeyAxis = static_cast<int>(axis);
                        });
                };

                pane.add_section("Analog");
                addKeyAxis(PAD_AXIS_TRIGGER_L);
                addKeyAxis(PAD_AXIS_TRIGGER_R);

                pane.add_section("Digital");
                addKeyButton(PAD_TRIGGER_L);
                addKeyButton(PAD_TRIGGER_R);
                break;
            }

            u32 axisCount = 0;
            PADAxisMapping *axes = PADGetAxisMappings(port, &axisCount);
            u32 buttonCount = 0;
            PADButtonMapping *buttons = PADGetButtonMappings(port, &buttonCount);
            if (axes == nullptr && buttons == nullptr) {
                pane.add_text("No controller selected");
                break;
            }

            SDL_Gamepad *gamepad = gamepad_for_port(port);
            pane.add_section("Analog");
            constexpr std::array<PADAxis, 2> kTriggerAxes = { PAD_AXIS_TRIGGER_L, PAD_AXIS_TRIGGER_R };
            if (axes != nullptr) {
                for (PADAxis axis : kTriggerAxes) {
                    if (axis >= axisCount) {
                        continue;
                    }
                    PADAxisMapping &mapping = axes[axis];
                    pane.add_select_button({
                                               .key = PADGetAxisName(mapping.padAxis),
                                               .getValue =
                                                   [this, &mapping, gamepad] {
                                                       if (mPendingAxisMapping == &mapping) {
                                                           return pending_axis_label();
                                                       }
                                                       return native_axis_name(mapping, gamepad);
                                                   },
                                           })
                        .on_pressed([this, port, &mapping] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingAxisMapping = &mapping;
                        });
                }
            }

            pane.add_section("Digital");
            if (buttons != nullptr) {
                for (u32 i = 0; i < buttonCount; ++i) {
                    PADButtonMapping &mapping = buttons[i];
                    if (mapping.padButton != PAD_TRIGGER_L && mapping.padButton != PAD_TRIGGER_R) {
                        continue;
                    }
                    pane.add_select_button({
                                               .key = PADGetButtonName(mapping.padButton),
                                               .getValue =
                                                   [this, &mapping, gamepad] {
                                                       if (mPendingButtonMapping == &mapping) {
                                                           return pending_button_label();
                                                       }
                                                       return native_button_name(gamepad, mapping.nativeButton);
                                                   },
                                           })
                        .on_pressed([this, port, &mapping] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingButtonMapping = &mapping;
                        });
                }
            }

            if (PADDeadZones *deadZones = PADGetDeadZones(port)) {
                pane.add_section("Emulated Trigger Thresholds");
                pane.add_child<NumberButton>(NumberButton::Props {
                    .key = "L Threshold",
                    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->leftTriggerActivationZone); },
                    .setValue =
                        [deadZones](int value) {
                            deadZones->leftTriggerActivationZone = percent_to_raw(value);
                            PADSerializeMappings();
                        },
                    .isDisabled = [deadZones] { return !deadZones->emulateTriggers; },
                    .min = 0,
                    .max = 100,
                    .step = 1,
                    .suffix = "%",
                });
                pane.add_child<NumberButton>(NumberButton::Props {
                    .key = "R Threshold",
                    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->rightTriggerActivationZone); },
                    .setValue =
                        [deadZones](int value) {
                            deadZones->rightTriggerActivationZone = percent_to_raw(value);
                            PADSerializeMappings();
                        },
                    .isDisabled = [deadZones] { return !deadZones->emulateTriggers; },
                    .min = 0,
                    .max = 100,
                    .step = 1,
                    .suffix = "%",
                });
            }
            break;
        }
        case Page::Sticks: {
            if (keyboard_active(port)) {
                auto addKeyAxis = [&](PADAxis axis) {
                    pane.add_select_button({
                                               .key = PADGetAxisDirectionLabel(axis),
                                               .getValue =
                                                   [this, port, axis] {
                                                       if (mPendingKeyAxis == static_cast<int>(axis)) {
                                                           return pending_key_label();
                                                       }
                                                       u32 count = 0;
                                                       PADKeyAxisBinding *bindings = PADGetKeyAxisBindings(static_cast<u32>(port), &count);
                                                       if (bindings == nullptr) {
                                                           return Rml::String("Not bound");
                                                       }
                                                       for (u32 i = 0; i < PAD_AXIS_COUNT; ++i) {
                                                           if (bindings[i].padAxis == axis) {
                                                               return keyboard_key_name(bindings[i].scancode);
                                                           }
                                                       }
                                                       return Rml::String("Not bound");
                                                   },
                                           })
                        .on_pressed([this, port, axis] {
                            cancel_pending_binding();
                            mPendingPort = port;
                            mPendingBindingArmed = false;
                            mPendingKeyAxis = static_cast<int>(axis);
                        });
                };

                pane.add_section("Control Stick");
                addKeyAxis(PAD_AXIS_LEFT_Y_POS);
                addKeyAxis(PAD_AXIS_LEFT_Y_NEG);
                addKeyAxis(PAD_AXIS_LEFT_X_NEG);
                addKeyAxis(PAD_AXIS_LEFT_X_POS);

                pane.add_section("C Stick");
                addKeyAxis(PAD_AXIS_RIGHT_Y_POS);
                addKeyAxis(PAD_AXIS_RIGHT_Y_NEG);
                addKeyAxis(PAD_AXIS_RIGHT_X_NEG);
                addKeyAxis(PAD_AXIS_RIGHT_X_POS);
                break;
            }

            u32 axisCount = 0;
            PADAxisMapping *axes = PADGetAxisMappings(port, &axisCount);
            if (axes == nullptr) {
                pane.add_text("No controller selected");
                break;
            }

            SDL_Gamepad *gamepad = gamepad_for_port(port);
            auto addAxis = [&](PADAxis axis) {
                if (axis >= axisCount) {
                    return;
                }
                PADAxisMapping &mapping = axes[axis];
                pane.add_select_button({
                                           .key = PADGetAxisDirectionLabel(mapping.padAxis),
                                           .getValue =
                                               [this, &mapping, gamepad] {
                                                   if (mPendingAxisMapping == &mapping) {
                                                       return pending_axis_label();
                                                   }
                                                   return native_axis_name(mapping, gamepad);
                                               },
                                       })
                    .on_pressed([this, port, &mapping] {
                        cancel_pending_binding();
                        mPendingPort = port;
                        mPendingBindingArmed = false;
                        mPendingAxisMapping = &mapping;
                    });
            };

            pane.add_section("Control Stick");
            addAxis(PAD_AXIS_LEFT_Y_POS);
            addAxis(PAD_AXIS_LEFT_Y_NEG);
            addAxis(PAD_AXIS_LEFT_X_NEG);
            addAxis(PAD_AXIS_LEFT_X_POS);
            if (PADDeadZones *deadZones = PADGetDeadZones(port)) {
                pane.add_child<NumberButton>(NumberButton::Props {
                    .key = "Deadzone",
                    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->stickDeadZone); },
                    .setValue =
                        [deadZones](int value) {
                            deadZones->stickDeadZone = percent_to_raw(value);
                            PADSerializeMappings();
                        },
                    .isDisabled = [deadZones] { return !deadZones->useDeadzones; },
                    .min = 0,
                    .max = 100,
                    .step = 1,
                    .suffix = "%",
                });
            }

            pane.add_section("C Stick");
            addAxis(PAD_AXIS_RIGHT_Y_POS);
            addAxis(PAD_AXIS_RIGHT_Y_NEG);
            addAxis(PAD_AXIS_RIGHT_X_NEG);
            addAxis(PAD_AXIS_RIGHT_X_POS);
            if (PADDeadZones *deadZones = PADGetDeadZones(port)) {
                pane.add_child<NumberButton>(NumberButton::Props {
                    .key = "Deadzone",
                    .getValue = [deadZones] { return deadzone_raw_to_percent(deadZones->substickDeadZone); },
                    .setValue =
                        [deadZones](int value) {
                            deadZones->substickDeadZone = percent_to_raw(value);
                            PADSerializeMappings();
                        },
                    .isDisabled = [deadZones] { return !deadZones->useDeadzones; },
                    .min = 0,
                    .max = 100,
                    .step = 1,
                    .suffix = "%",
                });
            }

            break;
        }
        case Page::Rumble: {
            auto &rumbleTest = pane.add_select_button({
                .key = "Test Rumble",
                .getValue = [this, port] { return (mRumbleTestActive && mRumbleTestPort == port) ? Rml::String("Stop") : Rml::String("Start"); },
            });
            rumbleTest.on_pressed([this, port] {
                if (!PADSupportsRumbleIntensity(static_cast<u32>(port))) {
                    return;
                }
                // mDoAud_seStartMenu(kSoundItemChange); // TODO PC
                if (mRumbleTestActive && mRumbleTestPort == port) {
                    PADControlMotor(port, PAD_MOTOR_STOP_HARD);
                    mRumbleTestActive = false;
                    mRumbleTestPort = -1;
                }
                else {
                    if (mRumbleTestActive) {
                        PADControlMotor(mRumbleTestPort, PAD_MOTOR_STOP_HARD);
                    }
                    PADControlMotor(port, PAD_MOTOR_RUMBLE);
                    mRumbleTestActive = true;
                    mRumbleTestPort = port;
                }
            });
            pane.add_child<NumberButton>(NumberButton::Props {
                .key = "Low Rumble Frequency",
                .getValue =
                    [port] {
                        u16 low = 0;
                        u16 high = 0;
                        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
                        return rumble_raw_to_percent(low);
                    },
                .setValue =
                    [port](int value) {
                        u16 low = 0;
                        u16 high = 0;
                        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
                        PADSetRumbleIntensity(static_cast<u32>(port), percent_to_raw(value), high);
                        PADSerializeMappings();
                    },
                .isDisabled = [this] { return mRumbleTestActive; },
                .min = 0,
                .max = 100,
                .step = 1,
                .suffix = "%",
            });
            pane.add_child<NumberButton>(NumberButton::Props {
                .key = "High Rumble Frequency",
                .getValue =
                    [port] {
                        u16 low = 0;
                        u16 high = 0;
                        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
                        return rumble_raw_to_percent(high);
                    },
                .setValue =
                    [port](int value) {
                        u16 low = 0;
                        u16 high = 0;
                        PADGetRumbleIntensity(static_cast<u32>(port), &low, &high);
                        PADSetRumbleIntensity(static_cast<u32>(port), low, percent_to_raw(value));
                        PADSerializeMappings();
                    },
                .isDisabled = [this] { return mRumbleTestActive; },
                .min = 0,
                .max = 100,
                .step = 1,
                .suffix = "%",
            });
            pane.add_text("Configure your desired rumble intensities, then run a test to check how they feel.");
            break;
        }
    }
}

void ControllerConfigWindow::refresh_controller_page()
{
    if (!visible() || mPage != Page::Controller || mRightPane == nullptr) {
        return;
    }
    render_page(*mRightPane, mActivePort, Page::Controller);
}

void ControllerConfigWindow::poll_pending_binding()
{
    if (mSuppressNavigationUntilNeutral && input_neutral(mSuppressNavigationPort)) {
        mSuppressNavigationUntilNeutral = false;
        mSuppressNavigationPort = -1;
    }

    if (!capture_active()) {
        return;
    }

    if (keyboard_escape_pressed()) {
        unmap_pending_binding();
        return;
    }

    if (!mPendingBindingArmed) {
        if (pending_input_neutral()) {
            mPendingBindingArmed = true;
        }
        return;
    }

    if (mPendingKeyButton >= 0 || mPendingKeyAxis >= 0) {
        const s32 scancode = keyboard_key_pressed();
        if (scancode != PAD_KEY_INVALID) {
            if (mPendingKeyButton >= 0) {
                PADSetKeyButtonBinding(static_cast<u32>(mPendingPort), { scancode, static_cast<PADButton>(mPendingKeyButton) });
            }
            else {
                PADSetKeyAxisBinding(static_cast<u32>(mPendingPort), { scancode, static_cast<PADAxis>(mPendingKeyAxis), 0 });
            }
            finish_pending_key_binding();
        }
        return;
    }

    if (mPendingButtonMapping != nullptr) {
        const s32 nativeButton = PADGetNativeButtonPressed(mPendingPort);
        if (nativeButton != -1) {
            const int completedPort = mPendingPort;
            mPendingButtonMapping->nativeButton = static_cast<u32>(nativeButton);
            finish_pending_binding(completedPort);
        }
        return;
    }

    if (mPendingAxisMapping != nullptr) {
        const PADSignedNativeAxis nativeAxis = PADGetNativeAxisPulled(mPendingPort);
        if (nativeAxis.nativeAxis != -1) {
            const int completedPort = mPendingPort;
            mPendingAxisMapping->nativeAxis = nativeAxis;
            mPendingAxisMapping->nativeButton = -1;
            finish_pending_binding(completedPort);
            return;
        }

        const s32 nativeButton = PADGetNativeButtonPressed(mPendingPort);
        if (nativeButton != -1) {
            const int completedPort = mPendingPort;
            mPendingAxisMapping->nativeAxis = { -1, AXIS_SIGN_POSITIVE };
            mPendingAxisMapping->nativeButton = nativeButton;
            finish_pending_binding(completedPort);
        }
    }
}

void ControllerConfigWindow::finish_pending_binding(int completedPort)
{
    mPendingButtonMapping = nullptr;
    mPendingAxisMapping = nullptr;
    mPendingPort = -1;
    mPendingBindingArmed = false;
    mSuppressNavigationUntilNeutral = true;
    mSuppressNavigationPort = completedPort;
    PADSerializeMappings();
}

void ControllerConfigWindow::unmap_pending_binding()
{
    if (mPendingButtonMapping == nullptr && mPendingAxisMapping == nullptr && mPendingKeyButton < 0 && mPendingKeyAxis < 0) {
        return;
    }

    const int completedPort = mPendingPort;
    if (mPendingButtonMapping != nullptr) {
        mPendingButtonMapping->nativeButton = PAD_NATIVE_BUTTON_INVALID;
        finish_pending_binding(completedPort);
    }
    else if (mPendingAxisMapping != nullptr) {
        mPendingAxisMapping->nativeAxis = { -1, AXIS_SIGN_POSITIVE };
        mPendingAxisMapping->nativeButton = -1;
        finish_pending_binding(completedPort);
    }
    else if (mPendingKeyButton >= 0) {
        PADSetKeyButtonBinding(static_cast<u32>(completedPort), { PAD_KEY_INVALID, static_cast<PADButton>(mPendingKeyButton) });
        finish_pending_key_binding();
    }
    else if (mPendingKeyAxis >= 0) {
        PADSetKeyAxisBinding(static_cast<u32>(completedPort), { PAD_KEY_INVALID, static_cast<PADAxis>(mPendingKeyAxis), 0 });
        finish_pending_key_binding();
    }
}

bool ControllerConfigWindow::capture_active() const
{
    return mPendingButtonMapping != nullptr || mPendingAxisMapping != nullptr || mPendingKeyButton >= 0 || mPendingKeyAxis >= 0;
}

bool ControllerConfigWindow::pending_input_neutral() const
{
    if (mPendingKeyButton >= 0 || mPendingKeyAxis >= 0) {
        return keyboard_neutral();
    }
    return input_neutral(mPendingPort);
}

Rml::String ControllerConfigWindow::pending_button_label() const
{
    return mPendingBindingArmed ? "Press a button..." : "Waiting...";
}

Rml::String ControllerConfigWindow::pending_axis_label() const
{
    return mPendingBindingArmed ? "Move axis or press a button..." : "Waiting...";
}

void ControllerConfigWindow::cancel_pending_binding()
{
    if (mPendingButtonMapping == nullptr && mPendingAxisMapping == nullptr && !mSuppressNavigationUntilNeutral && mPendingKeyButton < 0
        && mPendingKeyAxis < 0) {
        return;
    }
    mPendingButtonMapping = nullptr;
    mPendingAxisMapping = nullptr;
    mPendingKeyButton = -1;
    mPendingKeyAxis = -1;
    mPendingPort = -1;
    mPendingBindingArmed = false;
    mSuppressNavigationUntilNeutral = false;
    mSuppressNavigationPort = -1;
}

void ControllerConfigWindow::finish_pending_key_binding()
{
    mPendingKeyButton = -1;
    mPendingKeyAxis = -1;
    mPendingPort = -1;
    mPendingBindingArmed = false;
    PADSerializeMappings();
}

Rml::String ControllerConfigWindow::pending_key_label() const
{
    return mPendingBindingArmed ? "Press a key or mouse button..." : "Waiting...";
}

void ControllerConfigWindow::stop_rumble_test()
{
    if (!mRumbleTestActive) {
        return;
    }
    if (mRumbleTestPort >= PAD_CHAN0 && mRumbleTestPort < PAD_CHANMAX) {
        PADControlMotor(mRumbleTestPort, PAD_MOTOR_STOP_HARD);
    }
    mRumbleTestActive = false;
    mRumbleTestPort = -1;
}


// ---------------------------------------------------------------------------------------------------- icon test

namespace {

    struct GlyphStep {
        const char *name; // the GameCube button
        int entry; // its message icon (button_icons.h)
    };
    constexpr GlyphStep kGlyphSteps[] = { { "A", 2 }, { "B", 3 }, { "X", 4 }, { "Y", 5 }, { "L", 8 }, { "R", 6 }, { "Z", 11 }, { "Start", 12 } };
    constexpr int kGlyphStepCount = sizeof(kGlyphSteps) / sizeof(kGlyphSteps[0]);

    // "pbglyph://<family>/<glyph>": a glyph in a family's art, for <img> in the test page.
    std::optional<aurora::rmlui::RuntimeTexture> serve_glyph(std::string_view source)
    {
        static std::map<std::pair<int, int>, std::vector<u8>> cache;
        const std::string text(source);
        int family = 0, glyph = 0;
        if (std::sscanf(text.c_str(), "pbglyph://%d/%d", &family, &glyph) != 2) {
            return std::nullopt;
        }
        constexpr int kSize = 128;
        auto &px = cache[{ family, glyph }];
        if (px.empty()) {
            px.resize(static_cast<size_t>(kSize) * kSize * 4);
            if (pb_button_icons_glyph_rgba_sized(static_cast<PbIconFamily>(family), glyph, kSize, px.data()) != 0) {
                cache.erase({ family, glyph });
                return std::nullopt;
            }
        }
        aurora::rmlui::RuntimeTexture tex;
        tex.width = kSize;
        tex.height = kSize;
        tex.rgba8 = std::as_bytes(std::span<const u8>(px));
        tex.generateMipmaps = true;
        return tex;
    }

    bool port_connected(int port)
    {
        return PADGetIndexForPort(static_cast<u32>(port)) >= 0;
    }

    // The button / trigger of `port` that is down (sticks are ignored: drift would flood the test). Returns false if
    // none; else *glyph is its icon glyph id (PB_GLYPH_NONE if it has none) and *name its label.
    bool pressed_input(int port, int *glyph, Rml::String *name)
    {
        // Read SDL directly and only the standard buttons: some devices report extra "misc" buttons as held, which
        // PADGetNativeButtonPressed (first one down) would return instead of the real press.
        SDL_Gamepad *gamepad = gamepad_for_port(port);
        if (gamepad == nullptr) {
            return false;
        }
        for (int b = SDL_GAMEPAD_BUTTON_SOUTH; b <= SDL_GAMEPAD_BUTTON_DPAD_RIGHT; ++b) {
            if (SDL_GetGamepadButton(gamepad, static_cast<SDL_GamepadButton>(b))) {
                *name = native_button_name(gamepad, static_cast<u32>(b));
                *glyph = pb_button_icons_glyph_for_native_button(b);
                return true;
            }
        }
        for (const SDL_GamepadAxis axis : { SDL_GAMEPAD_AXIS_LEFT_TRIGGER, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER }) {
            if (SDL_GetGamepadAxis(gamepad, axis) > 16000) {
                *name = SDL_GetGamepadStringForAxis(axis);
                *glyph = pb_button_icons_glyph_for_native_axis(axis);
                return true;
            }
        }
        return false;
    }

    bool all_neutral()
    {
        int glyph;
        Rml::String name;
        for (int p = 0; p < PAD_CHANMAX; ++p) {
            if (port_connected(p) && pressed_input(p, &glyph, &name)) {
                return false;
            }
        }
        return true;
    }

} // namespace

GlyphTestWindow::GlyphTestWindow()
{
    static bool registered = false;
    if (!registered) {
        registered = true;
        aurora::rmlui::register_texture_provider("pbglyph", serve_glyph);
    }
    listen(
        Rml::EventId::Keydown,
        [this](Rml::Event &event) {
            if (capturing()) {
                event.StopPropagation();
            }
        },
        true);

    add_tab("Button Icons", [this](Rml::Element *content) {
        auto &leftPane = add_child<Pane>(content, Pane::Type::Controlled);
        auto &rightPane = add_child<Pane>(content, Pane::Type::Uncontrolled);
        mRightPane = &rightPane;
        auto show = [this](Pane &) { render(); };
        leftPane.add_section("Test");
        leftPane.register_control(leftPane.add_button("Start Test").on_pressed([this] { start(); }), rightPane, show);
        leftPane.register_control(leftPane.add_button("Skip This Button").on_pressed([this] { skip(); }), rightPane, show);
        leftPane.register_control(leftPane.add_button("Stop Test").on_pressed([this] { stop(false); }), rightPane, show);
        mDirty = true;
    });
}

void GlyphTestWindow::hide(bool close)
{
    mRunning = false;
    Window::hide(close);
}

void GlyphTestWindow::start()
{
    mResults.clear();
    mNote.clear();
    mStep = 0;
    mFinished = false;
    mRunning = true;
    mPort = 0;
    for (int p = 0; p < PAD_CHANMAX; ++p) {
        int glyph;
        Rml::String name;
        mHeld[p] = port_connected(p) && pressed_input(p, &glyph, &name);
        if (port_connected(p) && mPort == 0 && p > 0 && !port_connected(0)) {
            mPort = p;
        }
    }
    mDirty = true;
}

void GlyphTestWindow::stop(bool finished)
{
    if (mRunning) {
        mSuppressUntilNeutral = true; // the press that ended it must not also navigate the menu
    }
    mRunning = false;
    mFinished = finished;
    mDirty = true;
}

void GlyphTestWindow::skip()
{
    if (!mRunning) {
        return;
    }
    mResults.push_back(fmt::format("{}: skipped", kGlyphSteps[mStep].name));
    mNote.clear();
    if (++mStep >= kGlyphStepCount) {
        stop(true);
    }
    mDirty = true;
}

void GlyphTestWindow::poll()
{
    if (mSuppressUntilNeutral && all_neutral()) {
        mSuppressUntilNeutral = false;
    }
    if (!mRunning) {
        return;
    }
    if (keyboard_escape_pressed()) {
        stop(false);
        return;
    }
    for (int p = 0; p < PAD_CHANMAX; ++p) {
        int pressed = PB_GLYPH_NONE;
        Rml::String name;
        const bool down = port_connected(p) && pressed_input(p, &pressed, &name);
        // a new press only: ignore what was already down (e.g. the press that started the test)
        const bool isNew = down && !mHeld[p];
        mHeld[p] = down;
        if (!isNew) {
            continue;
        }
        const PbIconFamily family = pb_button_icons_family_for_local_port(p);
        mPort = p;
        const int expected = pb_button_icons_glyph_for_local_port(p, family, kGlyphSteps[mStep].entry);
        if (pressed == expected && pressed != PB_GLYPH_NONE) {
            mResults.push_back(fmt::format("{}: your &quot;{}&quot; button", kGlyphSteps[mStep].name, name));
            mNote.clear();
            if (++mStep >= kGlyphStepCount) {
                stop(true);
            }
        }
        else {
            Rml::String as = "a button the game doesn't show a picture for";
            for (const GlyphStep &step : kGlyphSteps) {
                if (pressed != PB_GLYPH_NONE && pb_button_icons_glyph_for_local_port(p, family, step.entry) == pressed) {
                    as = fmt::format("the game's {} button", step.name);
                    break;
                }
            }
            mNote = fmt::format("You pressed &quot;{}&quot;, which is {}. Try another.", name, as);
        }
        mDirty = true;
        return;
    }
}

void GlyphTestWindow::update()
{
    poll();
    Window::update();
    if (mDirty && mRightPane != nullptr && visible()) {
        mDirty = false;
        render();
    }
}

void GlyphTestWindow::render()
{
    if (mRightPane == nullptr) {
        return;
    }
    Pane &pane = *mRightPane;
    pane.clear();
    int connected = -1;
    for (int p = 0; p < PAD_CHANMAX && connected < 0; ++p) {
        connected = port_connected(p) ? p : -1;
    }
    if (connected < 0) {
        pane.add_text("No controller detected. Connect one to test its button icons.");
        return;
    }
    const int port = mRunning ? mPort : connected;
    const PbIconFamily family = pb_button_icons_family_for_local_port(port);
    if (family == PB_FAMILY_GAMECUBE) {
        pane.add_text("Button Icons is set to GameCube, which keeps the game's own pictures. Pick another style to test.");
        return;
    }
    if (mRunning) {
        const GlyphStep &step = kGlyphSteps[mStep];
        const int glyph = pb_button_icons_glyph_for_local_port(port, family, step.entry);
        pane.add_rml(fmt::format("Port {} ({} icons). Press the button this picture shows:<br/>"
                                 "<img src=\"pbglyph://{}/{}\" style=\"width: 96dp; height: 96dp;\"/><br/>"
                                 "The game calls it {} ({} of {}).",
            port + 1, pb_button_icons_family_name(family), static_cast<int>(family), glyph, step.name, mStep + 1, kGlyphStepCount));
        if (!mNote.empty()) {
            pane.add_rml("<br/>" + mNote);
        }
        pane.add_rml(fmt::format("<br/>Listening to port {}: {}. Esc on the keyboard stops the test.", port + 1, current_controller_name(port)));
    }
    else {
        pane.add_rml(fmt::format("Port {} ({} icons). Start the test to be shown each game button's picture in turn. Press the "
                                 "button on your controller that you think the picture is. It moves on once you press the one the "
                                 "game really uses, and tells you which of your buttons that is.",
            port + 1, pb_button_icons_family_name(family)));
    }
    if (!mResults.empty()) {
        Rml::String list = mFinished ? "<br/><br/>Done. The game's buttons are on your controller's:" : "<br/><br/>So far:";
        for (const Rml::String &line : mResults) {
            list += "<br/>" + line;
        }
        pane.add_rml(list);
    }
}

} // namespace partyboard::ui

