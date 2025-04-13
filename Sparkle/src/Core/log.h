#pragma once

#include <spdlog/spdlog.h>

namespace Sparkle {

class Log {
public:
  inline static std::shared_ptr<spdlog::logger> &getCoreLogger() {
    return s_core_logger;
  }
  inline static std::shared_ptr<spdlog::logger> &getClientLogger() {
    return s_client_logger;
  }

  static void Init();

private:
  static std::shared_ptr<spdlog::logger> s_core_logger;
  static std::shared_ptr<spdlog::logger> s_client_logger;
};

} // namespace Sparkle

#define SPRK_CORE_TRACE(msg, ...)                                              \
  ::Sparkle::Log::getCoreLogger()->trace("[{}:{}]\n" msg, __FILE__, __LINE__,  \
                                         ##__VA_ARGS__)
#define SPRK_CORE_INFO(msg, ...)                                               \
  ::Sparkle::Log::getCoreLogger()->info("[{}:{}]]\n" msg, __FILE__, __LINE__,  \
                                        ##__VA_ARGS__)
#define SPRK_CORE_WARN(msg, ...)                                               \
  ::Sparkle::Log::getCoreLogger()->warn("[{}:{}]\n" msg, __FILE__, __LINE__,   \
                                        ##__VA_ARGS__)
#define SPRK_CORE_ERROR(msg, ...)                                              \
  ::Sparkle::Log::getCoreLogger()->error("[{}:{}]\n" msg, __FILE__, __LINE__,  \
                                         ##__VA_ARGS__)
#define SPRK_CORE_CRITICAL(msg, ...)                                           \
  ::Sparkle::Log::getCoreLogger()->critical("[{}:{}]\n" msg, __FILE__,         \
                                            __LINE__, ##__VA_ARGS__)

#define SPRK_TRACE(msg, ...)                                                   \
  ::Sparkle::Log::getClientLogger()->trace("[{}:{}]\n" msg, __FILE__,          \
                                           __LINE__, ##__VA_ARGS__)
#define SPRK_INFO(msg, ...)                                                    \
  ::Sparkle::Log::getClientLogger()->info("[{}:{}]\n" msg, __FILE__, __LINE__, \
                                          ##__VA_ARGS__)
#define SPRK_WARN(msg, ...)                                                    \
  ::Sparkle::Log::getClientLogger()->warn("[{}:{}]\n" msg, __FILE__, __LINE__, \
                                          ##__VA_ARGS__)
#define SPRK_ERROR(msg, ...)                                                   \
  ::Sparkle::Log::getClientLogger()->error("[{}:{}]\n" msg, __FILE__,          \
                                           __LINE__, ##__VA_ARGS__)
#define SPRK_CRITICAL(msg, ...)                                                \
  ::Sparkle::Log::getClientLogger()->critical("[{}:{}]\n" msg, __FILE__,       \
                                              __LINE__, ##__VA_ARGS__)
