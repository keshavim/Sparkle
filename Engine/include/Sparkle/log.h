#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <string>

namespace Sparkle {
    class Logger {
    public:
        // Singleton accessor
        static Logger &Instance() {
            static Logger instance;
            return instance;
        }

        // Get the underlying spdlog logger
        std::shared_ptr<spdlog::logger> &Get() {
            return m_logger;
        }

        // Set log level at runtime
        void SetLevel(const spdlog::level::level_enum level) const {
            m_logger->set_level(level);
        }

        // Set log pattern at runtime
        void SetPattern(const std::string &pattern) const {
            m_logger->set_pattern(pattern);
        }

        // Non-copyable, non-movable
        Logger(const Logger &) = delete;

        Logger &operator=(const Logger &) = delete;

    private:
        Logger() {
            m_logger = spdlog::stdout_color_mt("ENGINE");
            m_logger->set_pattern("[%H:%M:%S] [%n] [%^%l%$] %v");
            m_logger->set_level(spdlog::level::trace);
        }

        ~Logger() = default;

        std::shared_ptr<spdlog::logger> m_logger;
    };
}

// Logging macros for convenience
#define LOG_TRACE(...)    ::Sparkle::Logger::Instance().Get()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Sparkle::Logger::Instance().Get()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Sparkle::Logger::Instance().Get()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Sparkle::Logger::Instance().Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Sparkle::Logger::Instance().Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Sparkle::Logger::Instance().Get()->critical(__VA_ARGS__)
