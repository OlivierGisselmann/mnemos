#include <core/logging/logger_manager.hpp>

namespace Mnemos
{
    bool LoggerManager::Init(const SubsystemInitInfo& info)
    {
        Get().SetLogLevel(LogLevel::DEBUG);
        Get().EnableFileOutput("game.log");

        return true;
    }

    void LoggerManager::Shutdown()
    {

    }
}