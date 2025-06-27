//
// Created by overlord on 6/26/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "base.h"
#include <SDL3/SDL.h>

namespace Sparkle {
    //struct containing window data
    struct WindowData {
        std::string title = "window";
        i32 width = 800;
        i32 height = 600;
        bool fullscreen = false;
        bool resizable = true;
    };

    // The Window class manages the SDL window and its properties.
    // It provides methods to initialize, poll events, and shut down the window.
    class Window {
    public:
        Window();
        ~Window();

        // No copying
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // Window API
        bool init(const std::optional<WindowData> &data);
        void shutdown();

        // Accessors (defined inline)
        [[nodiscard]] SDL_Window* get_sdl_window() const { return m_window; }
        void should_close(bool close) { m_should_close = close; }

        WindowData& get_props() { return m_data; }
        void on_resize(const i32 new_width, const i32 new_height) {
            m_data.width = new_width;
            m_data.height = new_height;
        }



    private:
        SDL_Window* m_window;
        bool m_should_close;
        WindowData m_data;
    };
}
#endif //WINDOW_H
