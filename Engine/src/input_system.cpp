#include "pch.h"
#include "Sparkle/input_system.h"
#include <SDL3/SDL.h>

#include "Sparkle/base.h"

namespace Sparkle {
    InputSystem &InputSystem::instance() {
        static InputSystem instance;
        return instance;
    }


    bool InputSystem::is_key_pressed(Key key) const {
        switch (key) {
            case Key::Ctrl:
                return m_keys_down.contains(Key::LCtrl) || m_keys_down.contains(Key::RCtrl);
            case Key::Shift:
                return m_keys_down.contains(Key::LShift) || m_keys_down.contains(Key::RShift);
            case Key::Alt:
                return m_keys_down.contains(Key::LAlt) || m_keys_down.contains(Key::RAlt);
            case Key::Gui:
                return m_keys_down.contains(Key::LGui) || m_keys_down.contains(Key::RGui);
            default:
                return m_keys_down.contains(key);
        }
    }

    bool InputSystem::is_mouse_button_pressed(MouseButton button) const {
        return m_mouse_buttons_down.contains(button);
    }

    std::pair<i32, i32> InputSystem::get_mouse_position() const {
        return {m_mouse_x, m_mouse_y};
    }

    void InputSystem::set_key_pressed(Key key, bool down) {
        if (down)
            m_keys_down.insert(key);
        else
            m_keys_down.erase(key);
    }

    void InputSystem::set_mouse_button_pressed(MouseButton button, bool down) {
        if (down)
            m_mouse_buttons_down.insert(button);
        else
            m_mouse_buttons_down.erase(button);
    }

    void InputSystem::set_mouse_position(i32 x, i32 y) {
        m_mouse_x = x;
        m_mouse_y = y;
    }

    void InputSystem::set_mouse_scroll(i32 xoffset, i32 yoffset) {
        m_mouse_scroll_x = xoffset;
        m_mouse_scroll_y = yoffset;
    }

    void InputSystem::next_frame() {
        // For "just pressed/released" logic, clear per-frame state here.
        TODO();
    }
}
