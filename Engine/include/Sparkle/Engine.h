//
// Created by overlord on 6/26/25.
//

#ifndef ENGINE_H
#define ENGINE_H

#include "Renderer.h"
#include "Sparkle/Base.h"
#include "Sparkle/Window.h"
#include "Sparkle/EventSystem.h"
#include "Sparkle/LayerStack.h"
#include "Sparkle/Renderer.h"

#include "vulkan/vulkan.h"

namespace Sparkle {

    //mopve this to renderer ------------------------------------------------------------------------


    class Engine {
    public:
        // Get the singleton instance
        Engine();

        virtual ~Engine();

        // No copying or moving
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        Engine(Engine&&) = delete;
        Engine& operator=(Engine&&) = delete;

        // Main entry point
        void run();

        void pushLayer(Layer *layer);

        void pushOverlay(Layer *layer);

        // Accessors for systems
        static Engine& Get() {return *s_instance;}
        Window& get_window() { return m_window; }

    private:
        void on_update(f32 delta_time);

        void on_event(Event &e);

        //create defaule callbacks for all events
        void register_events();

        Window m_window;
        EventSystem m_event_system;
        LayerStack m_layers;
        Renderer m_renderer;
        bool m_is_running;


        static Engine *s_instance;
    };
}
#endif //ENGINE_H
