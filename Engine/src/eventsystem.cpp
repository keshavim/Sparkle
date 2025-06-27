//
// Created by overlord on 6/26/25.
//
#include "eventsystem.h"
#include <SDL3/SDL.h>
#include "log.h"

namespace Sparkle {

    void EventSystem::register_callback(EventType type, const EventCallbackFn& callback) {
        callbacks_[type] = callback;
    }

    void EventSystem::dispatch(Event& event) {
        auto it = callbacks_.find(event.type);
        if (it != callbacks_.end() && it->second) {
            it->second(event);
        }
    }

    void EventSystem::poll_events() {
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_EVENT_QUIT: {
                    WindowCloseEvent event;
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_WINDOW_RESIZED: {
                    WindowResizeEvent event(sdl_event.window.data1, sdl_event.window.data2);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_WINDOW_FOCUS_GAINED: {
                    WindowFocusEvent event(true);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_WINDOW_FOCUS_LOST: {
                    WindowFocusEvent event(false);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_WINDOW_MOVED: {
                    WindowMovedEvent event(sdl_event.window.data1, sdl_event.window.data2);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    KeyDownEvent event(sdl_event.key.key, sdl_event.key.repeat != 0);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_KEY_UP: {
                    KeyUpEvent event(sdl_event.key.key);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    MouseButtonDownEvent event(sdl_event.button.button, sdl_event.button.x, sdl_event.button.y);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    MouseButtonUpEvent event(sdl_event.button.button, sdl_event.button.x, sdl_event.button.y);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    MouseMovedEvent event(sdl_event.motion.x, sdl_event.motion.y);
                    dispatch(event);
                    break;
                }
                case SDL_EVENT_MOUSE_WHEEL: {
                    MouseScrolledEvent event(sdl_event.wheel.x, sdl_event.wheel.y);
                    dispatch(event);
                    break;
                }
                default:
                    // Unhandled event type
                    break;
            }
        }
    }

}
