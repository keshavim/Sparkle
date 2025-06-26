//
// Created by overlord on 6/26/25.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>

namespace Sparkle {
    struct WindowProps {
        std::string title;
        i32 width;
        i32 height;
    };

    class Window {
    public:
        Window();
        ~Window();

        // No copying
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // Window API
        bool init(const WindowProps& props);
        void poll_events();
        void shutdown();

        // Accessors (defined inline)
        [[nodiscard]] SDL_Window* get_sdl_window() const { return window_; }
        [[nodiscard]] bool should_close() const { return window_should_close_; }
        WindowProps& get_props() { return props_; }



    private:
        SDL_Window* window_;
        bool window_should_close_;
        WindowProps props_;
    };
}
#endif //WINDOW_H
