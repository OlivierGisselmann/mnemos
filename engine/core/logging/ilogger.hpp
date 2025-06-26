#pragma once

#include <core/isubsystem.hpp>

#include <string>

namespace Mnemos
{
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERR,
        FATAL
    };

    class ILogger
    {
    public:
        virtual ~ILogger() = default;

        virtual void SetLogLevel(LogLevel level) = 0;
        virtual void EnableFileOutput(const std::string& filename) = 0;

        virtual void Log(LogLevel level, const std::string& message, const char* file, int line, const char* function) = 0;
    };
}
