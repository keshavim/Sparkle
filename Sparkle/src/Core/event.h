#pragma once
#include "sprkpch.h"

#include "core.h"

namespace Sparkle {

enum class EventType {
  None = 0,
  WindowResize,
  WindowClose,
  WindowMoved,
  WindowFocus,
  WindowLostFocus,
  KeyTyped,
  KeyPressed,
  KeyReleased,
  MouseMoved,
  MouseScrolled,
  MouseButtonPressed,
  MouseButtonReleased
};

enum EventCategory {
  None = 0,
  CategoryInput = BIT(1),
  CategoryKeyboard = BIT(2),
  CategoryMouse = BIT(3),
  CategoryMouseButton = BIT(4),
  CategoryEngine = BIT(4)
};

class Event {

public:
  virtual ~Event() = default;

  bool handled = false;
  virtual EventType getType() const = 0;
  virtual int getCategories() const = 0;
  virtual const char *getName() const = 0;
  virtual std::string toString() const { return getName(); }

  bool inCategory(EventCategory catagory) { return getCategories() & catagory; }
};

// helper macros
#define GEN_EVENT_TYPE(type)                                                   \
  static EventType getStaticType() { return EventType::type; }                 \
  virtual EventType getType() const override { return getStaticType(); }       \
  virtual const char *getName() const override { return #type; }

#define GEN_EVENT_CATEGORY(category)                                           \
  virtual int getCategories() const override { return category; }

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
  return os << e.toString();
}

class EventDispatcher {
public:
  EventDispatcher(Event &event) : m_Event(event) {}

  // F will be deduced by the compiler
  template <typename T, typename F> bool dispatch(const F &func) {
    if (m_Event.getType() == T::getStaticType()) {
      m_Event.handled |= func(static_cast<T &>(m_Event));
      return true;
    }
    return false;
  }

private:
  Event &m_Event;
};

//
//
// Key events
//
//
class KeyEvent : public Event {

public:
  int getKeyCode() const { return m_keycode; }

  GEN_EVENT_CATEGORY(CategoryInput | CategoryKeyboard)
protected:
  KeyEvent(int key) : m_keycode(key) {}
  int m_keycode;
};

class KeyPressedEvent : public KeyEvent {
public:
  KeyPressedEvent(int key, bool repeat) : KeyEvent(key), m_repeat(repeat) {}

  bool isRepeat() const { return m_repeat; }
  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << m_keycode << " (repeat = " << m_repeat << ")";
    return ss.str();
  }

  GEN_EVENT_TYPE(KeyPressed)

private:
  bool m_repeat;
};

class KeyReleasedEvent : public KeyEvent {
public:
  KeyReleasedEvent(int key) : KeyEvent(key) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyRelessedEvent: " << m_keycode;
    return ss.str();
  }
  GEN_EVENT_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
  KeyTypedEvent(int key) : KeyEvent(key) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyTypedEvent: " << m_keycode;
    return ss.str();
  }
  GEN_EVENT_TYPE(KeyTyped)
};

//
//
// Mouse evnets
//
//
//

class MouseButtonEvent : public Event {

public:
  int getKeyCode() const { return m_button; }

  GEN_EVENT_CATEGORY(CategoryInput | CategoryMouse | CategoryMouseButton)
protected:
  MouseButtonEvent(int button) : m_button(button) {}
  int m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
  MouseButtonPressedEvent(int key) : MouseButtonEvent(key) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressedEvent: " << m_button;
    return ss.str();
  }

  GEN_EVENT_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseButtonRelessedEvent: " << m_button;
    return ss.str();
  }
  GEN_EVENT_TYPE(MouseButtonReleased)
};

class MouseMovedEvent : public Event {
public:
  MouseMovedEvent(float x, float y) : m_x(x), m_y(y) {}

  float getX() { return m_x; }
  float getY() { return m_y; }
  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseMovedEvent: x =" << m_x << " y = " << m_y;
    return ss.str();
  }

  GEN_EVENT_TYPE(MouseMoved);
  GEN_EVENT_CATEGORY(CategoryMouse | CategoryInput)
private:
  float m_x;
  float m_y;
};

class MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(float x, float y) : m_x(x), m_y(y) {}

  float getX() { return m_x; }
  float getY() { return m_y; }
  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseScrolledEvent: x =" << m_x << " y = " << m_y;
    return ss.str();
  }

  GEN_EVENT_TYPE(MouseScrolled);
  GEN_EVENT_CATEGORY(CategoryMouse | CategoryInput)
private:
  float m_x;
  float m_y;
};

//
//
// Window Events
//
//
//

class WindowMovedEvent : public Event {
public:
  WindowMovedEvent(int x, int y) : m_x(x), m_y(y) {}

  int getX() { return m_x; }
  int getY() { return m_y; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowMovedEvent: x =" << m_x << " y = " << m_y;
    return ss.str();
  }

  GEN_EVENT_TYPE(WindowMoved);
  GEN_EVENT_CATEGORY(CategoryEngine)
private:
  int m_x;
  int m_y;
};

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(unsigned int x, unsigned int y) : m_x(x), m_y(y) {}

  unsigned int getWidth() { return m_x; }
  unsigned int getHeight() { return m_y; }
  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: x =" << m_x << " y = " << m_y;
    return ss.str();
  }

  GEN_EVENT_TYPE(WindowResize);
  GEN_EVENT_CATEGORY(CategoryEngine)
private:
  unsigned int m_x;
  unsigned int m_y;
};

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() = default;

  GEN_EVENT_TYPE(WindowClose);
  GEN_EVENT_CATEGORY(CategoryEngine)
};
} // namespace Sparkle
