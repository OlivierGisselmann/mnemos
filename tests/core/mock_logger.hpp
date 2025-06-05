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

    inline void Log(Mnemos::LogLevel level, const char* message, ...) override
    {

    }
};
