#pragma once

#include <core/isubsystem.hpp>
#include <platform/types.hpp>

#include <chrono>

namespace Mnemos
{
    class ITimer : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override = 0;
        void Shutdown() override = 0;

        virtual void Tick() = 0;
        virtual void Sleep() = 0;
        virtual f64 GetDeltaTime() const = 0;
    };
}
