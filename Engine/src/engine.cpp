//
// Created by overlord on 6/26/25.
//
#include "pch.h"
#include "Sparkle/engine.h"
#include "Sparkle/log.h"
#include "Sparkle/input_system.h"


namespace Sparkle {
    Engine::Engine()
        : m_is_running(false) {
        LOG_INFO("Engine starting...");

        if (!m_window.init(std::nullopt)) {
            LOG_ERROR("Failed to initialize window system.");
            return;
        }

        register_events();
    }

    Engine::~Engine() {
        LOG_INFO("Engine shutting down...");
        m_layers.clear();
        m_window.shutdown();
        SDL_Quit();
    }

    void Engine::pushLayer(Layer *layer) {
        m_layers.push_layer(layer);
    }

    void Engine::pushOverlay(Layer *layer) {
        m_layers.push_overlay(layer);
    }

    void Engine::on_event(Event &e) {
        if (e.type == EventType::WindowClose) {
            m_is_running = false;
        }

        m_layers.on_event(e);
    }

    void Engine::on_update(f32 delta_time) {
        if (Input.is_key_pressed(Key::Shift)) {
            LOG_INFO("any shift is pressed");
        }

        m_layers.on_update(delta_time);
    }

    void Engine::run() {
        m_is_running = true;
        u64 last_time = SDL_GetTicks();
        while (m_is_running) {
            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event)) {
                m_event_system.poll_events(sdl_event);
            }

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;


            on_update(delta_time);
        }
    }

    void Engine::register_events() {
        //may make multiple windows possible so this is temp
        m_event_system.register_callback(EventType::WindowClose, [&](Event &e) {
            m_window.should_close(true);
            on_event(e);
        });

        m_event_system.register_callback(EventType::WindowResize, [&](Event &e) {
            auto &resize_event = dynamic_cast<WindowResizeEvent &>(e);
            m_window.on_resize(resize_event.width, resize_event.height);
            on_event(e);
        });

        m_event_system.register_callback(EventType::WindowFocus, [&](Event &e) {
            m_window.set_focus(dynamic_cast<WindowFocusEvent &>(e).focused);
            on_event(e);
        });

        m_event_system.register_callback(EventType::WindowMoved, [&](Event &e) {
            on_event(e);
        });

        // Key Down
        m_event_system.register_callback(EventType::KeyDown, [&](Event &e) {
            auto &key_event = dynamic_cast<KeyDownEvent &>(e);
            InputSystem::instance().set_key_pressed(key_event.keycode, true);
            on_event(e);
        });

        // Key Up
        m_event_system.register_callback(EventType::KeyUp, [&](Event &e) {
            auto &key_event = dynamic_cast<KeyUpEvent &>(e);
            InputSystem::instance().set_key_pressed(key_event.keycode, false);
            on_event(e);
        });

        // Mouse Button Down
        m_event_system.register_callback(EventType::MouseButtonDown, [&](Event &e) {
            auto &mouse_event = dynamic_cast<MouseButtonDownEvent &>(e);
            InputSystem::instance().set_mouse_button_pressed(mouse_event.button, true);
            on_event(e);
        });

        // Mouse Button Up
        m_event_system.register_callback(EventType::MouseButtonUp, [&](Event &e) {
            auto &mouse_event = dynamic_cast<MouseButtonUpEvent &>(e);
            InputSystem::instance().set_mouse_button_pressed(mouse_event.button, false);
            on_event(e);
        });

        // Mouse Moved
        m_event_system.register_callback(EventType::MouseMoved, [&](Event &e) {
            auto &moved_event = dynamic_cast<MouseMovedEvent &>(e);
            InputSystem::instance().set_mouse_position(moved_event.x, moved_event.y);
            on_event(e);
        });

        // Mouse Scrolled (if you want to track scroll)
        m_event_system.register_callback(EventType::MouseScrolled, [&](Event &e) {
            auto &scroll_event = dynamic_cast<MouseScrolledEvent &>(e);
            InputSystem::instance().set_mouse_scroll(scroll_event.xoffset, scroll_event.yoffset);
            on_event(e);
        });
    }
}