#pragma once

#include <core/time/itimer.hpp>
#include <core/logging/logger_manager.hpp>

namespace Mnemos
{
    struct FrameTimerInitInfo : public SubsystemInitInfo
    {
        i16 targetFramerate = 0;
        bool limitFramerate = false;
    };

    class FrameTimer : public ITimer
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        bool Tick() override;

        f64 GetDeltaTime() const override;
        f64 GetTime() const override;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock > mStart{};
        f64 mCurrent = 0.0;
        f64 mLast = 0.0;

        f64 mTime = 0.0;
        f64 mDeltaTime = 0.0;
        i16 mFpsLimit = 0;
        bool mLimitFramerate = false;
    };
}
