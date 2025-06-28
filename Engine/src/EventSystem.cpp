//
// Created by overlord on 6/26/25.
//
#include "skpch.h"
#include "Sparkle/EventSystem.h"
#include <SDL3/SDL.h>
#include "Sparkle/Log.h"

namespace Sparkle {
    void EventSystem::RegisterCallback(EventType type, const EventCallbackFn &callback) {
        callbacks_[type] = callback;
    }

    void EventSystem::Dispatch(Event &event) {
        auto it = callbacks_.find(event.type);
        if (it != callbacks_.end() && it->second) {
            it->second(event);
        }
    }

    void EventSystem::PollEvents(const SDL_Event &sdl_event) {
        switch (sdl_event.type) {
            case SDL_EVENT_QUIT: {
                WindowCloseEvent event;
                Dispatch(event);
                break;
            }
            case SDL_EVENT_WINDOW_RESIZED: {
                WindowResizeEvent event(sdl_event.window.data1, sdl_event.window.data2);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_WINDOW_FOCUS_GAINED: {
                WindowFocusEvent event(true);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_WINDOW_FOCUS_LOST: {
                WindowFocusEvent event(false);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_WINDOW_MOVED: {
                WindowMovedEvent event(sdl_event.window.data1, sdl_event.window.data2);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_KEY_DOWN: {
                KeyDownEvent event(static_cast<Key>(sdl_event.key.scancode), sdl_event.key.repeat != 0);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_KEY_UP: {
                KeyUpEvent event(static_cast<Key>(sdl_event.key.scancode));
                Dispatch(event);
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                MouseButtonDownEvent event(static_cast<MouseButton>(sdl_event.button.button), sdl_event.button.x,
                                           sdl_event.button.y);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_MOUSE_BUTTON_UP: {
                MouseButtonUpEvent event(static_cast<MouseButton>(sdl_event.button.button), sdl_event.button.x,
                                         sdl_event.button.y);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_MOUSE_MOTION: {
                MouseMovedEvent event(sdl_event.motion.x, sdl_event.motion.y);
                Dispatch(event);
                break;
            }
            case SDL_EVENT_MOUSE_WHEEL: {
                MouseScrolledEvent event(sdl_event.wheel.x, sdl_event.wheel.y);
                Dispatch(event);
                break;
            }
            default:
                // Unhandled event type
                break;
        }
    }
}
