//
// Created by overlord on 6/26/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "Sparkle/Base.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

namespace Sparkle {
    //struct containing window data
    struct WindowData {
        std::string title = "window";
        i32 width = 1280;
        i32 height = 720;
        bool fullscreen = false;
        bool resizable = true;
        bool vsync = true;
        bool focused = true;
        bool minimized = false;
    };

    // The Window class manages the SDL window and its properties.
    // It provides methods to initialize, poll events, and shut down the window.
    class Window {
    public:
        Window();

        ~Window();

        // No copying
        Window(const Window &) = delete;

        Window &operator=(const Window &) = delete;

        // Window API
        bool Init(const std::optional<WindowData> &data);

        void Shutdown();

        // Accessors (defined inline)
        // Vulkan-specific getters
        SDL_Window* GetSDLWindow() const { return m_window; }
        void ShouldClose(bool close) { m_should_close = close; }
        f32 GetScale() const { return m_scale; }

        WindowData &GetData() { return m_data; }

        void OnResize(const i32 new_width, const i32 new_height) {
            m_data.width = new_width;
            m_data.height = new_height;
        }

        void SetFocus(bool focused) { m_data.focused = focused; }

    private:
        SDL_Window *m_window;
        bool m_should_close;
        WindowData m_data;

        f32 m_scale = 1.0f;
    };
}
#endif //WINDOW_H
