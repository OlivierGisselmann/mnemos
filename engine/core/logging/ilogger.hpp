#pragma once

#include <core/isubsystem.hpp>

#include <format>
#include <string>

namespace Mnemos
{
    class ILogger : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override = 0;
        void Shutdown() override = 0;

        virtual void LogTrace(const std::string& message) = 0;
        virtual void LogDebug(const std::string& message) = 0;
        virtual void LogWarn(const std::string& message) = 0;
        virtual void LogError(const std::string& message) = 0;
        virtual void LogFatal(const std::string& message) = 0;

        virtual ~ILogger() = default;
    };
}
