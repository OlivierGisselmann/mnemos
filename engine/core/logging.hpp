#pragma once

#include <iostream>

namespace Mnemos
{
    enum LogLevel
    {
        TRACE,
        DEBUG,
        WARN,
        ERROR,
        FATAL
    };

    inline void Log(LogLevel level, const char* msg)
    {
        switch (level)
        {
            case TRACE: std::cout << "[TRACE] " << msg << '\n'; break;
            case DEBUG: std::cout << "[DEBUG] " << msg << '\n'; break;
            case WARN: std::cout << "[WARN] " << msg << '\n'; break;
            case ERROR: std::cout << "[ERROR] " << msg << '\n'; break;
            case FATAL: std::cout << "[FATAL] " << msg << '\n'; break;
        }
    }
}
