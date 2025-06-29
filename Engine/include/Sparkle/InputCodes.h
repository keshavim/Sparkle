//
// Created by overlord on 6/27/25.
//

#ifndef INPUT_CODES_H
#define INPUT_CODES_H

#include <SDL3/SDL.h>

namespace Sparkle {
    // Wrapper for SDL scancodes (physical keyboard layout)
    enum class Key : int {
        Unknown = SDL_SCANCODE_UNKNOWN,
        A = SDL_SCANCODE_A,
        B = SDL_SCANCODE_B,
        C = SDL_SCANCODE_C,
        D = SDL_SCANCODE_D,
        E = SDL_SCANCODE_E,
        F = SDL_SCANCODE_F,
        G = SDL_SCANCODE_G,
        H = SDL_SCANCODE_H,
        I = SDL_SCANCODE_I,
        J = SDL_SCANCODE_J,
        K = SDL_SCANCODE_K,
        L = SDL_SCANCODE_L,
        M = SDL_SCANCODE_M,
        N = SDL_SCANCODE_N,
        O = SDL_SCANCODE_O,
        P = SDL_SCANCODE_P,
        Q = SDL_SCANCODE_Q,
        R = SDL_SCANCODE_R,
        S = SDL_SCANCODE_S,
        T = SDL_SCANCODE_T,
        U = SDL_SCANCODE_U,
        V = SDL_SCANCODE_V,
        W = SDL_SCANCODE_W,
        X = SDL_SCANCODE_X,
        Y = SDL_SCANCODE_Y,
        Z = SDL_SCANCODE_Z,

        Num0 = SDL_SCANCODE_0,
        Num1 = SDL_SCANCODE_1,
        Num2 = SDL_SCANCODE_2,
        Num3 = SDL_SCANCODE_3,
        Num4 = SDL_SCANCODE_4,
        Num5 = SDL_SCANCODE_5,
        Num6 = SDL_SCANCODE_6,
        Num7 = SDL_SCANCODE_7,
        Num8 = SDL_SCANCODE_8,
        Num9 = SDL_SCANCODE_9,


        LCtrl = SDL_SCANCODE_LCTRL,
        LShift = SDL_SCANCODE_LSHIFT,
        LAlt = SDL_SCANCODE_LALT,
        LGui = SDL_SCANCODE_LGUI,
        RCtrl = SDL_SCANCODE_RCTRL,
        RShift = SDL_SCANCODE_RSHIFT,
        RAlt = SDL_SCANCODE_RALT,
        RGui = SDL_SCANCODE_RGUI,

        Ctrl,
        Shift,
        Alt,
        Gui,

        Escape = SDL_SCANCODE_ESCAPE,
        Space = SDL_SCANCODE_SPACE,
        Enter = SDL_SCANCODE_RETURN,
        Backspace = SDL_SCANCODE_BACKSPACE,
        Tab = SDL_SCANCODE_TAB,
        CapsLock = SDL_SCANCODE_CAPSLOCK,

        F1 = SDL_SCANCODE_F1,
        F2 = SDL_SCANCODE_F2,
        F3 = SDL_SCANCODE_F3,
        F4 = SDL_SCANCODE_F4,
        F5 = SDL_SCANCODE_F5,
        F6 = SDL_SCANCODE_F6,
        F7 = SDL_SCANCODE_F7,
        F8 = SDL_SCANCODE_F8,
        F9 = SDL_SCANCODE_F9,
        F10 = SDL_SCANCODE_F10,
        F11 = SDL_SCANCODE_F11,
        F12 = SDL_SCANCODE_F12,

        Up = SDL_SCANCODE_UP,
        Down = SDL_SCANCODE_DOWN,
        Left = SDL_SCANCODE_LEFT,
        Right = SDL_SCANCODE_RIGHT,

        Insert = SDL_SCANCODE_INSERT,
        Delete = SDL_SCANCODE_DELETE,
        Home = SDL_SCANCODE_HOME,
        End = SDL_SCANCODE_END,
        PageUp = SDL_SCANCODE_PAGEUP,
        PageDown = SDL_SCANCODE_PAGEDOWN
        // ...add more as needed...


    };




    // Wrapper for SDL mouse buttons
    enum class MouseButton : int {
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE,
        Right = SDL_BUTTON_RIGHT,
        X1 = SDL_BUTTON_X1,
        X2 = SDL_BUTTON_X2
    };
} // namespace Sparkle


#endif //INPUT_CODES_H
