//
// Created by overlord on 6/26/25.
//
#include "pch.h"
#include "engine.h"
#include "log.h"

namespace Sparkle {
    Engine::Engine()
        : m_is_running(false)
    {
        LOG_INFO("Engine starting...");

        if (!m_window.init(std::nullopt)) {
            LOG_ERROR("Failed to initialize window system.");
            return;
        }

        //may make multiple windows possible so this is temp
        m_event_system.register_callback(EventType::WindowClose, [&](Event& e) {
            m_window.should_close(true);
            m_is_running = false;
            LOG_INFO("Window close event handled.");
        });

        m_event_system.register_callback(EventType::WindowResize, [&](Event& e) {
            auto& resize_event = dynamic_cast<WindowResizeEvent&>(e);
            m_window.on_resize(resize_event.width, resize_event.height);
            LOG_INFO("Window resized to {}x{}", resize_event.width, resize_event.height);
        });

        m_event_system.register_callback(EventType::WindowFocus, [&](Event& e) {
            auto& focus_event = dynamic_cast<WindowFocusEvent&>(e);
            LOG_INFO("Window focus: {}", focus_event.focused ? "gained" : "lost");
        });

        m_event_system.register_callback(EventType::WindowMoved, [&](Event& e) {
            auto& moved_event = dynamic_cast<WindowMovedEvent&>(e);
            LOG_INFO("Window moved to {}, {}", moved_event.x, moved_event.y);
        });

        // Register key and mouse events (stubs for now)
        m_event_system.register_callback(EventType::KeyDown, [&](Event& e) {
            auto& key_event = dynamic_cast<KeyDownEvent&>(e);
            LOG_INFO("key pressed {}, {}", key_event.keycode, key_event.repeat);
        });
        m_event_system.register_callback(EventType::KeyUp, [&](Event& e) {/* ... */});
        m_event_system.register_callback(EventType::MouseButtonDown, [&](Event& e) {/* ... */});
        m_event_system.register_callback(EventType::MouseButtonUp, [&](Event& e) {/* ... */});
        m_event_system.register_callback(EventType::MouseMoved, [&](Event& e) {
            auto& moved_event = dynamic_cast<MouseMovedEvent&>(e);
            LOG_INFO("mose moved to {}, {}", moved_event.x, moved_event.y);
        });
        m_event_system.register_callback(EventType::MouseScrolled, [&](Event& e) {/* ... */});

    }

    Engine::~Engine() {
        LOG_INFO("Engine shutting down...");
        m_window.shutdown();
    }

    void Engine::run() {
        m_is_running = true;
        u64 last_time = SDL_GetTicks();
        while (m_is_running) {
            m_event_system.poll_events();

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;

            // Call user/game logic
            on_update(delta_time);
        }
    }
}