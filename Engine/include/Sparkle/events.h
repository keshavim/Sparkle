//
// Created by overlord on 6/26/25.
//

#ifndef EVENTS_H
#define EVENTS_H

#include "Sparkle/base.h"
#include "Sparkle/input_codes.h"
#include <string>
#include <format> // C++20 std::format, or use fmtlib

namespace Sparkle {
    // Enum for all event types in the engine
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

    // Base event struct for all event types
    struct Event {
        EventType type = EventType::None;
        bool handled = false;

        explicit Event(EventType t) : type(t) {
        }

        virtual ~Event() = default;

        // Returns the event type as a string
        virtual std::string name() const { return "Event"; }
        // Returns a string with event details (override in derived)
        virtual std::string to_string() const { return name(); }
    };

    // --- Window Events ---

    struct WindowResizeEvent : public Event {
        i32 width, height;

        WindowResizeEvent(i32 w, i32 h)
            : Event(EventType::WindowResize), width(w), height(h) {
        }

        std::string name() const override { return "WindowResizeEvent"; }

        std::string to_string() const override {
            return std::format("{}: {}x{}", name(), width, height);
        }
    };

    struct WindowCloseEvent : public Event {
        WindowCloseEvent() : Event(EventType::WindowClose) {
        }

        std::string name() const override { return "WindowCloseEvent"; }
        std::string to_string() const override { return name(); }
    };

    struct WindowFocusEvent : public Event {
        bool focused;

        explicit WindowFocusEvent(bool f)
            : Event(EventType::WindowFocus), focused(f) {
        }

        std::string name() const override { return "WindowFocusEvent"; }

        std::string to_string() const override {
            return std::format("{}: {}", name(), focused ? "focused" : "unfocused");
        }
    };

    struct WindowMovedEvent : public Event {
        i32 x, y;

        WindowMovedEvent(i32 xpos, i32 ypos)
            : Event(EventType::WindowMoved), x(xpos), y(ypos) {
        }

        std::string name() const override { return "WindowMovedEvent"; }

        std::string to_string() const override {
            return std::format("{}: {}, {}", name(), x, y);
        }
    };

    // --- Keyboard Events ---

    struct KeyEvent : public Event {
        Key keycode;
        bool repeat;

        KeyEvent(EventType t, Key code, bool rep)
            : Event(t), keycode(code), repeat(rep) {
        }

        // Base name for key events
        std::string name() const override { return "KeyEvent"; }
        // Base to_string (should be overridden)
        std::string to_string() const override {
            return std::format("{}: keycode={}, repeat={}", name(), static_cast<int>(keycode), repeat);
        }
    };

    struct KeyDownEvent : public KeyEvent {
        KeyDownEvent(Key code, bool rep)
            : KeyEvent(EventType::KeyDown, code, rep) {
        }

        std::string name() const override { return "KeyDownEvent"; }

        std::string to_string() const override {
            return std::format("{}: keycode={}, repeat={}", name(), static_cast<int>(keycode), repeat);
        }
    };

    struct KeyUpEvent : public KeyEvent {
        explicit KeyUpEvent(Key code)
            : KeyEvent(EventType::KeyUp, code, false) {
        }

        std::string name() const override { return "KeyUpEvent"; }

        std::string to_string() const override {
            return std::format("{}: keycode={}", name(), static_cast<int>(keycode));
        }
    };

    // --- Mouse Events ---

    struct MouseButtonEvent : public Event {
        MouseButton button;
        i32 x, y;

        MouseButtonEvent(EventType t, MouseButton btn, i32 xpos, i32 ypos)
            : Event(t), button(btn), x(xpos), y(ypos) {
        }

        std::string name() const override { return "MouseButtonEvent"; }

        std::string to_string() const override {
            return std::format("{}: button={}, x={}, y={}", name(), static_cast<int>(button), x, y);
        }
    };

    struct MouseButtonDownEvent : public MouseButtonEvent {
        MouseButtonDownEvent(MouseButton btn, i32 xpos, i32 ypos)
            : MouseButtonEvent(EventType::MouseButtonDown, btn, xpos, ypos) {
        }

        std::string name() const override { return "MouseButtonDownEvent"; }

        std::string to_string() const override {
            return std::format("{}: button={}, x={}, y={}", name(), static_cast<int>(button), x, y);
        }
    };

    struct MouseButtonUpEvent : public MouseButtonEvent {
        MouseButtonUpEvent(MouseButton btn, i32 xpos, i32 ypos)
            : MouseButtonEvent(EventType::MouseButtonUp, btn, xpos, ypos) {
        }

        std::string name() const override { return "MouseButtonUpEvent"; }

        std::string to_string() const override {
            return std::format("{}: button={}, x={}, y={}", name(), static_cast<int>(button), x, y);
        }
    };

    struct MouseMovedEvent : public Event {
        i32 x, y;

        MouseMovedEvent(i32 xpos, i32 ypos)
            : Event(EventType::MouseMoved), x(xpos), y(ypos) {
        }

        std::string name() const override { return "MouseMovedEvent"; }

        std::string to_string() const override {
            return std::format("{}: x={}, y={}", name(), x, y);
        }
    };

    struct MouseScrolledEvent : public Event {
        i32 xoffset, yoffset;

        MouseScrolledEvent(i32 xoff, i32 yoff)
            : Event(EventType::MouseScrolled), xoffset(xoff), yoffset(yoff) {
        }

        std::string name() const override { return "MouseScrolledEvent"; }

        std::string to_string() const override {
            return std::format("{}: xoffset={}, yoffset={}", name(), xoffset, yoffset);
        }
    };
} // namespace Sparkle

#endif //EVENTS_H
