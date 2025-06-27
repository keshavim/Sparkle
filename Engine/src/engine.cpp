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

        register_events();

    }

    Engine::~Engine() {
        LOG_INFO("Engine shutting down...");
        m_window.shutdown();
        SDL_Quit();

    }

    void Engine::run() {
        m_is_running = true;
        u64 last_time = SDL_GetTicks();
        while (m_is_running) {
            m_event_system.poll_events();

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;

            if (Input.is_key_pressed(Key::Shift)) {
                LOG_INFO("any shift is pressed");
            }
            if (Input.is_key_pressed(Key::LShift)) {
                LOG_INFO("left shift is pressed");
            }
            if (Input.is_key_pressed(Key::RShift)) {
                LOG_INFO("right shift is pressed");
            }
            if (Input.is_mouse_button_pressed(MouseButton::Left)) {
                auto [x,y] = Input.get_mouse_position();
                LOG_INFO("{} , {}", x, y);
            }


            // Call user/game logic
            on_update(delta_time);
        }
    }

    void Engine::register_events() {
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

        // Key Down
        m_event_system.register_callback(EventType::KeyDown, [](Event& e) {
            auto& key_event = dynamic_cast<KeyDownEvent&>(e);
            InputSystem::instance().set_key_pressed(key_event.keycode, true);
        });

        // Key Up
        m_event_system.register_callback(EventType::KeyUp, [](Event& e) {
            auto& key_event = dynamic_cast<KeyUpEvent&>(e);
            InputSystem::instance().set_key_pressed(key_event.keycode, false);
        });

        // Mouse Button Down
        m_event_system.register_callback(EventType::MouseButtonDown, [](Event& e) {
            auto& mouse_event = dynamic_cast<MouseButtonDownEvent&>(e);
            InputSystem::instance().set_mouse_button_pressed(mouse_event.button, true);
        });

        // Mouse Button Up
        m_event_system.register_callback(EventType::MouseButtonUp, [](Event& e) {
            auto& mouse_event = dynamic_cast<MouseButtonUpEvent&>(e);
            InputSystem::instance().set_mouse_button_pressed(mouse_event.button, false);
        });

        // Mouse Moved
        m_event_system.register_callback(EventType::MouseMoved, [](Event& e) {
            auto& moved_event = dynamic_cast<MouseMovedEvent&>(e);
            InputSystem::instance().set_mouse_position(moved_event.x, moved_event.y);
        });

        // Mouse Scrolled (if you want to track scroll)
        m_event_system.register_callback(EventType::MouseScrolled, [](Event& e) {
            auto& scroll_event = dynamic_cast<MouseScrolledEvent&>(e);
            InputSystem::instance().set_mouse_scroll(scroll_event.xoffset, scroll_event.yoffset);
        });
    }
}