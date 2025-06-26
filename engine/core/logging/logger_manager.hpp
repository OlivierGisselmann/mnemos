#pragma once

#include <core/isubsystem.hpp>
#include <core/logging/ilogger.hpp>
#include <core/logging/default_logger.hpp>

#define LOG(level, msg) \
    Mnemos::LoggerManager::Get().Log(level, msg, __FILE__, __LINE__, __FUNCTION__)

#define LOGF(level) \
    LogStream(level, __FILE__, __LINE__, __FUNCTION__).Stream()

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

    class LogStream
    {
    public:
        LogStream(LogLevel level, const char* file, int line, const char* func)
            : level(level), file(file), line(line), func(func) {}

        ~LogStream() {
            LoggerManager::Get().Log(level, oss.str(), file, line, func);
        }

        std::ostringstream& Stream() { return oss; }

    private:
        std::ostringstream oss;
        LogLevel level;
        const char* file;
        int line;
        const char* func;
    };
}
