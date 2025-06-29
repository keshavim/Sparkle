//
// Created by overlord on 6/26/25.
//
#include "skpch.h"
#include "Sparkle/Engine.h"

#include "Sparkle/ImGuiLayer.h"
#include "Sparkle/Log.h"
#include "Sparkle/InputSystem.h"
#include "backends/imgui_impl_sdl3.h"


namespace Sparkle {
    Engine *Engine::s_instance = nullptr;

    Engine::Engine()
        : m_is_running(false) {
        assert(s_instance == nullptr && "Engine already initialized");
        s_instance = this;
        SK_LOG_INFO("Engine starting...");

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
            SK_LOG_ERROR("SDL_Init Error: {}\n", SDL_GetError());
            return;
        }

        if (!m_window.Init(std::nullopt)) {
            SK_LOG_ERROR("Failed to initialize window system.");
            return;
        }

        m_renderer.Init();

        pushOverlay(new ImGuiLayer(true, false, ImVec4(0.45f, 0.55f, 0.60f, 1.00f)));

        register_events();
    }

    Engine::~Engine() {
        SK_LOG_INFO("Engine shutting down...");
        m_layers.clear();

        m_renderer.Cleanup();

        m_window.Shutdown();
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
        m_layers.on_update(delta_time);
    }



    void Engine::run() {

        m_is_running = true;
        u64 last_time = SDL_GetTicks();

        // Main loop
        while (m_is_running) {
            SDL_Event sdl_event;
            while (SDL_PollEvent(&sdl_event)) {
                //may try to change to use oure events
                ImGui_ImplSDL3_ProcessEvent(&sdl_event);
                m_event_system.PollEvents(sdl_event);
            }

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;

            m_renderer.Render();

            m_layers.on_update(delta_time);

            m_layers.on_render();
        }
        VkResult err = vkDeviceWaitIdle(m_renderer.getContext().device);
        Renderer::check_vk_result(err);
    }


    void Engine::register_events() {
        //may make multiple windows possible so this is temp
        m_event_system.RegisterCallback(EventType::WindowClose, [&](Event &e) {
            m_window.ShouldClose(true);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::WindowResize, [&](Event &e) {
            auto &resize_event = dynamic_cast<WindowResizeEvent &>(e);
            m_window.OnResize(resize_event.width, resize_event.height);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::WindowFocus, [&](Event &e) {
            m_window.SetFocus(dynamic_cast<WindowFocusEvent &>(e).focused);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::WindowMoved, [&](Event &e) {
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::KeyDown, [&](Event &e) {
            auto &key_event = dynamic_cast<KeyDownEvent &>(e);
            InputSystem::instance().SetKeyPressed(key_event.keycode, true);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::KeyUp, [&](Event &e) {
            auto &key_event = dynamic_cast<KeyUpEvent &>(e);
            InputSystem::instance().SetKeyPressed(key_event.keycode, false);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::MouseButtonDown, [&](Event &e) {
            auto &mouse_event = dynamic_cast<MouseButtonDownEvent &>(e);
            InputSystem::instance().SetMouseBtnPressed(mouse_event.button, true);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::MouseButtonUp, [&](Event &e) {
            auto &mouse_event = dynamic_cast<MouseButtonUpEvent &>(e);
            InputSystem::instance().SetMouseBtnPressed(mouse_event.button, false);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::MouseMoved, [&](Event &e) {
            auto &moved_event = dynamic_cast<MouseMovedEvent &>(e);
            InputSystem::instance().SetMousePosition(moved_event.x, moved_event.y);
            on_event(e);
        });

        m_event_system.RegisterCallback(EventType::MouseScrolled, [&](Event &e) {
            auto &scroll_event = dynamic_cast<MouseScrolledEvent &>(e);
            InputSystem::instance().SetMouseScroll(scroll_event.xoffset, scroll_event.yoffset);
            on_event(e);
        });
    }
}
