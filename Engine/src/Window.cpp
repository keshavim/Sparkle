//
// Created by overlord on 6/26/25.
//

#include "skpch.h"
#include "Sparkle/Log.h"
#include "Sparkle/Window.h"
#include "Sparkle/Engine.h"

#include <sys/syslog.h>

namespace Sparkle {
    Window::Window()
        : m_window(nullptr), m_should_close(false) {
    }

    Window::~Window() {
        Shutdown();
    }

    bool Window::Init(const std::optional<WindowData> &data) {

        if (data) {
            m_data = *data;
        }
        u32 flags = 0;
        if (m_data.resizable) {
            flags |= SDL_WINDOW_RESIZABLE;
        }
        if (m_data.fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }
        flags |= SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;

        // Create window with Vulkan graphics context
        m_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
        m_window = SDL_CreateWindow("Dear ImGui SDL3+Vulkan example", (int)(1280 * m_scale), (int)(720 * m_scale), flags);
        if (!m_window) {
            SK_LOG_ERROR("SDL_CreateWindow Error: {}\n", SDL_GetError());
            SDL_Quit();
            return false;
        }
        m_should_close = false;



        return true;
    }

    void Window::Shutdown() {
        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }

}

