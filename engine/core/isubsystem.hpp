#pragma once

namespace Mnemos
{
    struct SubsystemInitInfo
    {
        virtual ~SubsystemInitInfo() = default;
    };

    class ISubsystem
    {
    public:
        virtual bool Init(const SubsystemInitInfo& info) = 0;
        virtual void Shutdown() = 0;

        virtual ~ISubsystem() = default;
    };
}
