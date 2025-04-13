
#include "sprkpch.h"

#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace Sparkle {

std::shared_ptr<spdlog::logger> Log::s_core_logger;
std::shared_ptr<spdlog::logger> Log::s_client_logger;

void Log::Init() {
  spdlog::set_pattern("%^[%n:%l] %v%$");
  s_core_logger = spdlog::stdout_color_mt("Sparkle");
  s_core_logger->set_level(spdlog::level::trace);

  s_client_logger = spdlog::stdout_color_mt("App");
  s_client_logger->set_level(spdlog::level::trace);
}

} // namespace Sparkle
