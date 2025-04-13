#pragma once

#include "window.h"

namespace Sparkle {

class Engine {

public:
  Engine();
  virtual ~Engine();

  void Run();

private:
  std::unique_ptr<Window> m_window;
  bool m_running = true;
};

Engine *createApplication();
} // namespace Sparkle
