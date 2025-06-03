#pragma once

#include <core/isubsystem.hpp>
#include <platform/types.hpp>

namespace Mnemos
{
    struct WindowInitInfo : SubsystemInitInfo
    {
        i16 width;
        i16 height;
        const char* title;
        bool fullscreen = false;
    };

    class IWindow : public ISubsystem
    {
    public:
        virtual bool Init(const SubsystemInitInfo& info) override = 0;
        virtual void Shutdown() override = 0;

        virtual void PollEvents() = 0;
        virtual void Update() = 0;
        virtual void SwapBuffers() = 0;
        virtual bool CloseRequested() const = 0;

        virtual ~IWindow() = default;
    };
}
