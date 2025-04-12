#pragma once
#define SPDLOG_HEADER_ONLY

extern Sparkle::Engine *Sparkle::createApplication();

int main(int argc, char *argv[]) {

  Sparkle::Log::Init();

  auto app = Sparkle::createApplication();
  app->Run();
  delete app;
  return 0;
}
