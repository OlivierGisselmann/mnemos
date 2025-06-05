#pragma once

#include <core/time/itimer.hpp>
#include <core/logging/ilogger.hpp>

namespace Mnemos
{
    struct FrameTimerInitInfo : public SubsystemInitInfo
    {
        i16 targetFramerate = 0;
        bool limitFramerate = false;
        ILogger* logger = nullptr;
    };

    class FrameTimer : public ITimer
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void Tick() override;
        void Sleep() override;

        f64 GetDeltaTime() const override;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock > mStart{};
        std::chrono::time_point<std::chrono::high_resolution_clock > mLast{};

        f64 mDeltaTime = 0;
        f64 mTargetFrameTime = 0;
        bool mLimitFramerate = false;

        ILogger* mLogger = nullptr;
    };
}
