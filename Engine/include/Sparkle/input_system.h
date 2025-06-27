//
// Created by overlord on 6/27/25.
//

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <unordered_set>
#include "Sparkle/input_codes.h"
#include "Sparkle/base.h"

namespace Sparkle {
    // Singleton InputSystem for SDL3. Tracks state via events.
    class InputSystem {
    public:
        static InputSystem &instance();

        // Query functions
        bool is_key_pressed(Key key) const;

        bool is_mouse_button_pressed(MouseButton button) const;

        std::pair<i32, i32> get_mouse_position() const;

        // Setters for event system to update state
        void set_key_pressed(Key key, bool down);

        void set_mouse_button_pressed(MouseButton button, bool down);

        void set_mouse_position(i32 x, i32 y);

        void set_mouse_scroll(i32 xoffset, i32 yoffset);

        // Call once per frame to reset per-frame states if needed
        void next_frame();


        InputSystem(const InputSystem &) = delete;

        InputSystem &operator=(const InputSystem &) = delete;

    private:
        InputSystem() = default;

        ~InputSystem() = default;

        std::unordered_set<Key> m_keys_down;
        std::unordered_set<MouseButton> m_mouse_buttons_down;
        i32 m_mouse_x = 0;
        i32 m_mouse_y = 0;
        i32 m_mouse_scroll_x = 0;
        i32 m_mouse_scroll_y = 0;
    };
}


#define Input ::Sparkle::InputSystem::instance()

#endif //INPUT_SYSTEM_H
