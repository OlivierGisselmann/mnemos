#pragma once

#include <core/logging/ilogger.hpp>

#include <iostream>

namespace Mnemos
{
    class ConsoleLogger : public ILogger
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void Log(LogLevel level, const char* message, ...) override;
    };
}
