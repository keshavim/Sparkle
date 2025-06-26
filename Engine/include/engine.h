//
// Created by overlord on 6/26/25.
//

#ifndef ENGINE_H
#define ENGINE_H


#include "window.h"
#include "log.h"
namespace Sparkle {
    class Engine {
    public:
        Engine();
        virtual ~Engine();

        // No copying
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        // Main entry point
        void run(const WindowProps& props);

    protected:
        // Game-specific logic:
        virtual void on_update(f32 delta_time) = 0;

        // Accessors for systems
        Window& get_window() { return window_; }

    private:
        Window window_;
        bool is_running_;
    };
}
#endif //ENGINE_H
