#pragma once

#include <core/logging/ilogger.hpp>

class MockLogger : public Mnemos::ILogger
{
    inline bool Init(const Mnemos::SubsystemInitInfo& info) override
    {
        return true;
    }

    inline void Shutdown() override
    {

    }

    inline void LogTrace(const std::string& message) override {}
    inline void LogDebug(const std::string& message) override {}
    inline void LogWarn(const std::string& message) override {}
    inline void LogError(const std::string& message) override {}
    inline void LogFatal(const std::string& message) override {}
};
