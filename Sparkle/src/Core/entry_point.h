#pragma once
#define SPDLOG_HEADER_ONLY

extern Sparkle::Engine *Sparkle::createApplication();

int main(int argc, char *argv[]) {

  Sparkle::Log::Init();
  SPRK_CORE_TRACE("this also works");
  SPRK_CORE_INFO("this also works");
  SPRK_CORE_WARN("this also works");
  SPRK_CORE_ERROR("this also works");

  auto app = Sparkle::createApplication();
  app->Run();
  delete app;
  return 0;
}
