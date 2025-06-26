//
// Created by overlord on 6/26/25.
//
#include "base.h"
#include "log.h"
#include "window.h"
namespace Sparkle {
    Window::Window()
        : window_(nullptr), window_should_close_(false), props_("",0,0) {
    }

    Window::~Window() {
        shutdown();
    }

    bool Window::init(const WindowProps& props) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            LOG_ERROR("SDL_Init Error: {}\n", SDL_GetError());
            return false;
        }
        props_ = props;
        window_ = SDL_CreateWindow(props.title.c_str(), props.width, props.height, 0);
        if (!window_) {
            LOG_ERROR("SDL_CreateWindow Error: {}\n", SDL_GetError());
            SDL_Quit();
            return false;
        }
        window_should_close_ = false;
        return true;
    }

    void Window::poll_events() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                window_should_close_ = true;
            }
        }
    }

    void Window::shutdown() {
        if (window_) {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
        SDL_Quit();
    }
}