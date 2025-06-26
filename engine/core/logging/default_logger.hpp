#pragma once

#include <core/logging/ilogger.hpp>
#include <platform/platform.hpp>

#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <mutex>
#include <sstream>

namespace Mnemos
{
    class DefaultLogger : public ILogger
    {
    public:
        DefaultLogger() : mLevel(LogLevel::DEBUG), mFileOutput(false) {}

        void SetLogLevel(LogLevel level) override
        {
            mLevel = level;
        }

        void EnableFileOutput(const std::string& file) override
        {
            // Lock guard the file to be thread safe
            std::lock_guard<std::mutex> lock(mMutex);

            if(mFile.is_open())
                mFile.close();

            // Open file
            mFile.open(file, std::ios::out | std::ios::app);
            mFileOutput = mFile.is_open();
        }

        void Log(LogLevel level, const std::string& message, const char* file, int line, const char* function) override
        {
            if(level < mLevel)
                return;

            // Build output string
            std::ostringstream oss;
            oss << '[' << Timestamp() << "] "
                << '[' << LevelToString(level) << "] "
                << '[' << ShortFileName(file) << ':' << line << " (" << function << ")] "
                << message;
            
            std::lock_guard<std::mutex> lock(mMutex);
            std::string output = oss.str();

            std::cout << output << '\n';

            if(mFileOutput)
                mFile << output << '\n';
        }

    private:
        std::string Timestamp()
        {
            std::ostringstream oss;
            std::time_t t = std::time(nullptr);
            std::tm tm;
            #if defined(MNEMOS_PLATFORM_WIN32)
                localtime_s(&tm, &t);
            #else
                localtime_r(&t, &tm);
            #endif

            oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }
        
        std::string LevelToString(LogLevel level)
        {
            static const std::map<LogLevel, std::string> levelNames = 
            {
                {LogLevel::DEBUG, "DEBUG"},
                {LogLevel::INFO,  "INFO"},
                {LogLevel::WARN, "WARNING"},
                {LogLevel::ERR, "ERROR"},
                {LogLevel::FATAL, "FATAL"}
            };

            return levelNames.at(level);
        }

        std::string ShortFileName(const std::string& path)
        {
            std::size_t pos = path.find_last_of("/\\");
            return (pos != std::string::npos) ? path.substr(pos + 1) : path;
        }

        std::mutex mMutex;
        std::ofstream mFile;
        LogLevel mLevel;
        bool mFileOutput;
    };
}
