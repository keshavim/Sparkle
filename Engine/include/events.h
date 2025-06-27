//
// Created by overlord on 6/26/25.
//

#ifndef EVENTS_H
#define EVENTS_H

#include "base.h"
    enum class EventType {
        None = 0,
        WindowResize,
        WindowClose,
        WindowFocus,
        WindowMoved,
        KeyDown,
        KeyUp,
        MouseButtonDown,
        MouseButtonUp,
        MouseMoved,
        MouseScrolled
    };


    struct Event {
        EventType type = EventType::None;
        bool handled = false;
        explicit Event(EventType t) : type(t) {}
        virtual ~Event() = default;
    };

    //a lot of events
    struct WindowResizeEvent : public Event {
        i32 width, height;
        WindowResizeEvent(i32 w, i32 h)
            : Event(EventType::WindowResize), width(w), height(h) {}
    };

    struct WindowCloseEvent : public Event {
        WindowCloseEvent() : Event(EventType::WindowClose) {}
    };

    struct WindowFocusEvent : public Event {
        bool focused;
        explicit WindowFocusEvent(bool f)
            : Event(EventType::WindowFocus), focused(f) {}
    };

    struct WindowMovedEvent : public Event {
        i32 x, y;
        WindowMovedEvent(i32 xpos, i32 ypos)
            : Event(EventType::WindowMoved), x(xpos), y(ypos) {}
    };
    struct KeyEvent : public Event {
        i32 keycode;
        bool repeat;
        KeyEvent(EventType t, i32 code, bool rep)
            : Event(t), keycode(code), repeat(rep) {}
    };

    struct KeyDownEvent : public KeyEvent {
        KeyDownEvent(i32 code, bool rep)
            : KeyEvent(EventType::KeyDown, code, rep) {}
    };

    struct KeyUpEvent : public KeyEvent {
        explicit KeyUpEvent(i32 code)
            : KeyEvent(EventType::KeyUp, code, false) {}
    };
    struct MouseButtonEvent : public Event {
        i32 button;
        i32 x, y;
        MouseButtonEvent(EventType t, i32 btn, i32 xpos, i32 ypos)
            : Event(t), button(btn), x(xpos), y(ypos) {}
    };

    struct MouseButtonDownEvent : public MouseButtonEvent {
        MouseButtonDownEvent(i32 btn, i32 xpos, i32 ypos)
            : MouseButtonEvent(EventType::MouseButtonDown, btn, xpos, ypos) {}
    };

    struct MouseButtonUpEvent : public MouseButtonEvent {
        MouseButtonUpEvent(i32 btn, i32 xpos, i32 ypos)
            : MouseButtonEvent(EventType::MouseButtonUp, btn, xpos, ypos) {}
    };

    struct MouseMovedEvent : public Event {
        i32 x, y;
        MouseMovedEvent(i32 xpos, i32 ypos)
            : Event(EventType::MouseMoved), x(xpos), y(ypos) {}
    };

    struct MouseScrolledEvent : public Event {
        i32 xoffset, yoffset;
        MouseScrolledEvent(i32 xoff, i32 yoff)
            : Event(EventType::MouseScrolled), xoffset(xoff), yoffset(yoff) {}
    };

#endif //EVENTS_H
