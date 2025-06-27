//
// Created by overlord on 6/26/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "base.h"
#include <SDL3/SDL.h>

namespace Sparkle {
    struct WindowProps {
        std::string title = "window";
        i32 width = 800;
        i32 height = 600;
        bool fullscreen = false;
        bool resizable = true;
    };

    class Window {
    public:
        Window();
        ~Window();

        // No copying
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // Window API
        bool init(const std::optional<WindowProps> &props);
        void shutdown();

        // Accessors (defined inline)
        [[nodiscard]] SDL_Window* get_sdl_window() const { return m_window; }
        void should_close(bool close) { m_should_close = close; }

        WindowProps& get_props() { return m_props; }
        void on_resize(const i32 new_width, const i32 new_height) {
            m_props.width = new_width;
            m_props.height = new_height;
        }



    private:
        SDL_Window* m_window;
        bool m_should_close;
        WindowProps m_props;
    };
}
#endif //WINDOW_H
