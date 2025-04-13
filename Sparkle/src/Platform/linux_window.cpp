#include "sprkpch.h"

#include "Core/log.h"
#include "linux_window.h"

namespace Sparkle {

static bool is_initalized = false;

Window *Window::create(const char *name, const u32 width, const u32 height) {
  return new LinuxWindow(name, width, height);
}
LinuxWindow::LinuxWindow(const char *name, u32 width, u32 height) {
  init(name, width, height);
}
LinuxWindow::~LinuxWindow() { shutdown(); }

void LinuxWindow::init(const char *name, const u32 width, const u32 height) {

  m_data = {.title = name, .width = width, .height = height};

  SPRK_CORE_INFO("creating window title: {}, w: h: ", name, width, height);

  if (!is_initalized) {
    int result = glfwInit();
  }

  m_handle = glfwCreateWindow(width, height, name, nullptr, nullptr);
  glfwMakeContextCurrent(m_handle);
  glfwSetWindowUserPointer(m_handle, &m_data);
  setVsync(true);
}

void LinuxWindow::onUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_handle);
}

void LinuxWindow::shutdown() { glfwDestroyWindow(m_handle); }

void LinuxWindow::setVsync(bool enabled) {
  glfwSwapInterval((i32)enabled);
  m_data.vsync = enabled;
}

} // namespace Sparkle
