#pragma once

#include <core/time/itimer.hpp>

namespace Mnemos
{
    struct FrameTimerInitInfo : public SubsystemInitInfo
    {
        i16 targetFramerate;
        bool limitFramerate;
    };

    class FrameTimer : public ITimer
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void Tick() override;
        void Sleep();

        f64 GetDeltaTime() const override;

    private:
        std::chrono::_V2::system_clock::time_point mStart{};
        std::chrono::_V2::system_clock::time_point mLast{};

        f64 mDeltaTime = 0;
        f64 mTargetFrameTime = 0;
        bool mLimitFramerate;
    };
}
