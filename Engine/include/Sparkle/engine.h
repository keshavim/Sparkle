//
// Created by overlord on 6/26/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Sparkle/base.h"
#include "Sparkle/window.h"
#include "Sparkle/eventsystem.h"
#include "Sparkle/layer_stack.h"

namespace Sparkle {
    class Engine {
    public:
        Engine();

        virtual ~Engine();

        // No copying
        Engine(const Engine &) = delete;

        Engine &operator=(const Engine &) = delete;

        // Main entry point
        void run();

        void pushLayer(Layer *layer);

        void pushOverlay(Layer *layer);

    protected:
        // Accessors for systems
        Window &get_window() { return m_window; }

    private:
        void on_update(f32 delta_time);

        void on_event(Event &e);

        //create defaule callbacks for all events
        void register_events();

        Window m_window;
        EventSystem m_event_system;
        LayerStack m_layers;
        bool m_is_running;
    };
}
#endif //ENGINE_H
