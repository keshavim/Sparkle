//
// Created by overlord on 6/26/25.
//
#include "pch.h"
#include "engine.h"
#include "log.h"

namespace Sparkle {
    Engine::Engine()
        : m_is_running(false)
    {}

    Engine::~Engine() {
        // Cleanup handled by member destructors
    }

    void Engine::run() {
        LOG_INFO("Engine starting...");

        if (!m_window.init(std::nullopt)) {
            LOG_ERROR("Failed to initialize window system.");
            return;
        }

        m_is_running = true;
        u64 last_time = SDL_GetTicks();
        while (m_is_running && !m_window.should_close()) {
            m_window.poll_events();

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;

            // Call user/game logic
            on_update(delta_time);
        }

        LOG_INFO("Engine shutting down...");
        m_window.shutdown();
    }
}