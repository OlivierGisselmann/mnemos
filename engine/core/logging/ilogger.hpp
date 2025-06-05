#pragma once

#include <core/isubsystem.hpp>

namespace Mnemos
{
    enum class LogLevel
    {
        FATAL,
        ERR,
        WARN,
        DEBUG,
        TRACE
    };

    class ILogger : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override = 0;
        void Shutdown() override = 0;

        virtual void Log(LogLevel level, const char* message, ...) = 0;

        virtual ~ILogger() = default;
    };
}
