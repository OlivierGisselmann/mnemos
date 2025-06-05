#include <core/time/frame_timer.hpp>

#include <thread>

namespace Mnemos
{
    // For readability purposes
    using Clock = std::chrono::high_resolution_clock;

    bool FrameTimer::Init(const SubsystemInitInfo& info)
    {
        // Get init info
        const auto* timerInfo = dynamic_cast<const FrameTimerInitInfo*>(&info);
        mTargetFrameTime = 1.0 / timerInfo->targetFramerate;
        mLimitFramerate = timerInfo->limitFramerate;
        mLogger = timerInfo->logger;

        // Initialize first time point
        mLast = Clock::now();

        mLogger->Log(LogLevel::TRACE, "Frame Timer initialized");

        return true;
    }

    void FrameTimer::Shutdown()
    {
        mLogger->Log(LogLevel::TRACE, "Frame Timer shutdown");
    }

    void FrameTimer::Tick()
    {
        mStart = Clock::now();
        mDeltaTime = std::chrono::duration<f64, std::milli>(mStart - mLast).count();
    }

    void FrameTimer::Sleep()
    {
        // Get actual frame duration from start of loop to end
        auto frameEnd = Clock::now();
        f64 frameDuration = std::chrono::duration<f64>(frameEnd - mStart).count();

        if(mLimitFramerate)
        {
            // If sleep time is positive, then frame was too fast and need to sleep
            f64 remaining = mTargetFrameTime - frameDuration;

            if(remaining > 0)
            {
                // If the remaining time is less than a millisecond, sleeping will cost too much time, spinlock instead
                const f64 spinThreshold = 0.001; // 1 ms

                // If enough time to sleep
                if(remaining > spinThreshold)
                {
                    f64 sleepTime = remaining - spinThreshold;
                    std::this_thread::sleep_for(std::chrono::duration<f64>(sleepTime));
                }

                // Spin lock for the remaining time
                while(true)
                {
                    auto now = Clock::now();
                    f64 totalFrame = std::chrono::duration<f64>(now - mStart).count();

                    if(totalFrame >= mTargetFrameTime)
                        break;
                }

                frameEnd = Clock::now();
                frameDuration = std::chrono::duration<f64>(frameEnd - mStart).count();
            }
        }

        mDeltaTime = frameDuration;
        mLast = frameEnd;
    }

    f64 FrameTimer::GetDeltaTime() const
    {
        return mDeltaTime;
    }
}
