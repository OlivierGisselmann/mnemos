#include <core/logging/console_logger.hpp>

namespace Mnemos
{
    bool ConsoleLogger::Init(const SubsystemInitInfo& info)
    {
        return true;
    }

    void ConsoleLogger::Shutdown()
    {

    }

    void ConsoleLogger::Log(LogLevel level, const char* message, ...)
    {
        const char* levels[5] = {"[FATAL] ", "[ERROR] ", "[WARN] ", "[DEBUG] ", "[TRACE] "};
        std::cout << levels[(int)level] << message << '\n';
    }
}
