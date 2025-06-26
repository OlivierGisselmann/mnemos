#include <core/time/frame_timer.hpp>

#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
// Needed for clock resolution
#include <mmsystem.h>

#endif

namespace Mnemos
{
    // For readability purposes
    using Clock = std::chrono::high_resolution_clock;

    bool FrameTimer::Init(const SubsystemInitInfo& info)
    {
        // Enable High Res timer if on Windows
        #if defined(MNEMOS_PLATFORM_WIN32)
            timeBeginPeriod(1);
        #endif

        // Get init info
        const auto* timerInfo = dynamic_cast<const FrameTimerInitInfo*>(&info);
        mFpsLimit =  timerInfo->targetFramerate;
        mLimitFramerate = timerInfo->limitFramerate;

        // Initialize first time point

        mStart = Clock::now();
        mCurrent = GetTime();
        mLast = 0.0;

        LOG(LogLevel::INFO, "Frame Timer initialized");

        return true;
    }

    void FrameTimer::Shutdown()
    {
        #if defined(MNEMOS_PLATFORM_WIN32)
            timeEndPeriod(1);
        #endif

        LOG(LogLevel::INFO, "Frame Timer shutdown");
    }

    bool FrameTimer::Tick()
    {
        mCurrent = GetTime();

        if((mCurrent - mLast) > GetDeltaTime())
        {
            mLast = mCurrent;
            return true;
        }
        
        return false;
    }

    f64 FrameTimer::GetDeltaTime() const
    {
        return 1.0 / mFpsLimit;
    }

    f64 FrameTimer::GetTime() const
    {
        return std::chrono::duration<f64>(Clock::now() - mStart).count();
    }
}
