#pragma once

#include <core/isubsystem.hpp>
#include <core/logging/ilogger.hpp>
#include <core/logging/default_logger.hpp>

#define LOG(level, msg) \
    Mnemos::LoggerManager::Get().Log(level, msg, __FILE__, __LINE__, __FUNCTION__)

namespace Mnemos
{
    class LoggerManager : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        static ILogger& Get()
        {
            static DefaultLogger sLogger;
            return sLogger;
        }
    };
}
