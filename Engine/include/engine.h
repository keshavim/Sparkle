//
// Created by overlord on 6/26/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "base.h"
#include "window.h"
#include "eventsystem.h"
#include "input_system.h"

namespace Sparkle {
    class Engine {
    public:
        Engine();
        virtual ~Engine();

        // No copying
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        // Main entry point
        void run();

    protected:
        // Game-specific logic:
        virtual void on_update(f32 delta_time) = 0;

        // Accessors for systems
        Window& get_window() { return m_window; }

    private:
        //create defaule callbacks for all events
        void register_events();

        Window m_window;
        EventSystem m_event_system;
        bool m_is_running;
    };
}
#endif //ENGINE_H
