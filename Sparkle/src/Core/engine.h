#pragma once

namespace Sparkle {

class Engine {

public:
  Engine();
  virtual ~Engine();

  void Run();

private:
};

Engine *createApplication();
} // namespace Sparkle
