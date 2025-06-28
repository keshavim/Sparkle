//
// Created by overlord on 6/27/25.
//

#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <unordered_set>
#include "Sparkle/InputCodes.h"
#include "Sparkle/Base.h"

namespace Sparkle {
    // Singleton InputSystem for SDL3. Tracks state via events.
    class InputSystem {
    public:
        static InputSystem &instance();

        // Query functions
        bool IsKeyPressed(Key key) const;

        bool IsMouseBtnPressed(MouseButton button) const;

        std::pair<i32, i32> get_mouse_position() const;

        // Setters for event system to update state
        void SetKeyPressed(Key key, bool down);

        void SetMouseBtnPressed(MouseButton button, bool down);

        void SetMousePosition(i32 x, i32 y);

        void SetMouseScroll(i32 xoffset, i32 yoffset);

        // Call once per frame to reset per-frame states if needed
        void NextFrame();


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
