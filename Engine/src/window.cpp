//
// Created by overlord on 6/26/25.
//

#include "pch.h"
#include "log.h"
#include "window.h"
namespace Sparkle {
    Window::Window()
        : m_window(nullptr), m_should_close(false) {
    }

    Window::~Window() {
        shutdown();
    }

    bool Window::init(const std::optional<WindowData>& data) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            LOG_ERROR("SDL_Init Error: {}\n", SDL_GetError());
            return false;
        }
        if (data) {
            m_data = *data;
        }
        u32 flags = 0;
        if (m_data.resizable){
            flags |= SDL_WINDOW_RESIZABLE;
        }
        if (m_data.fullscreen) {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        m_window = SDL_CreateWindow(m_data.title.c_str(), m_data.width, m_data.height, flags);
        if (!m_window) {
            LOG_ERROR("SDL_CreateWindow Error: {}\n", SDL_GetError());
            SDL_Quit();
            return false;
        }
        m_should_close = false;
        return true;
    }

    void Window::shutdown() {
        if (m_window) {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }
}