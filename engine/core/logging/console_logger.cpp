#include <core/logging/console_logger.hpp>

namespace Mnemos
{
    static const char* sLevels[5] = {"[FATAL] ", "[ERROR] ", "[WARN] ", "[DEBUG] ", "[TRACE] "};

    bool ConsoleLogger::Init(const SubsystemInitInfo& info)
    {
        return true;
    }

    void ConsoleLogger::Shutdown() {}

    void ConsoleLogger::LogTrace(const std::string& message)
    {
        std::cout << "[TRACE] " << message << '\n';
    }

    void ConsoleLogger::LogDebug(const std::string& message)
    {
        std::cout << "[DEBUG] " << message << '\n';
    }

    void ConsoleLogger::LogWarn(const std::string& message)
    {
        std::cout << "[WARN] " << message << '\n';
    }

    void ConsoleLogger::LogError(const std::string& message)
    {
        std::cout << "[ERROR] " << message << '\n';
    }

    void ConsoleLogger::LogFatal(const std::string& message)
    {
        std::cout << "[FATAL] " << message << '\n';
    }
}
