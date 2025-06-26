//
// Created by overlord on 6/26/25.
//
#include "base.h"
#include "engine.h"

namespace Sparkle {
    Engine::Engine()
        : is_running_(false)
    {}

    Engine::~Engine() {
        // Cleanup handled by member destructors
    }

    void Engine::run(const WindowProps& props) {
        LOG_INFO("Engine starting...");

        if (!window_.init(props)) {
            LOG_ERROR("Failed to initialize window system.");
            return;
        }

        is_running_ = true;
        u64 last_time = SDL_GetTicks();
        while (is_running_ && !window_.should_close()) {
            window_.poll_events();

            const u64 now = SDL_GetTicks();
            const f32 delta_time = static_cast<f32>(now - last_time) / 1000.0f;
            last_time = now;

            // Call user/game logic
            on_update(delta_time);
        }

        LOG_INFO("Engine shutting down...");
        window_.shutdown();
    }
}