//
// Created by overlord on 6/26/25.
//

#ifndef EVENT_H
#define EVENT_H

#include "Sparkle/Events.h"
#include <SDL3/SDL.h>
#include <vector>
#include <functional>

namespace Sparkle {
    // Callback: takes a reference to base Event
    using EventCallbackFn = std::function<void(Event &)>;

    class EventSystem {
    public:
        // Register a callback to receive engine events
        void RegisterCallback(EventType type, const EventCallbackFn &callback);

        // Poll SDL events, convert to Sparkle events, and dispatch
        void PollEvents(const SDL_Event &sdl_event);

    private:
        std::unordered_map<EventType, EventCallbackFn> callbacks_;

        // Dispatch the event to the registered callback for its type.
        void Dispatch(Event &event);
    };
}

#endif //EVENT_H
