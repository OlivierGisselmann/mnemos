#pragma once

#include <core/logging/ilogger.hpp>
#include <platform/types.hpp>

#include <iostream>

namespace Mnemos
{
    class ConsoleLogger : public ILogger
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void LogTrace(const std::string& message) override;
        void LogDebug(const std::string& message) override;
        void LogWarn(const std::string& message) override;
        void LogError(const std::string& message) override;
        void LogFatal(const std::string& message) override;
    };
}
