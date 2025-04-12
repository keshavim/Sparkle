#pragma once

#include "Core/engine.h"
extern Sparkle::Engine *Sparkle::createApplication();

int main(int argc, char *argv[]) {
  auto app = Sparkle::createApplication();
  app->Run();
  delete app;
  return 0;
}
