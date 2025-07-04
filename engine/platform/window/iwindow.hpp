#pragma once

#include <core/isubsystem.hpp>
#include <core/logging/logger_manager.hpp>
#include <platform/input/inputsystem.hpp>
#include <platform/types.hpp>

namespace Mnemos
{
    struct WindowInitInfo : SubsystemInitInfo
    {
        i16 width = 0;
        i16 height = 0;
        const char* title = nullptr;
        bool fullscreen = false;
        InputSystem* inputSystem;
    };

    class IWindow : public ISubsystem
    {
    public:
        virtual bool Init(const SubsystemInitInfo& info) override = 0;
        virtual void Shutdown() override = 0;

        virtual void PollEvents() = 0;
        virtual void SwapWindowBuffers() = 0;
        virtual bool CloseRequested() const = 0;

        virtual void Resize(i16 width, i16 height) = 0;
        virtual i16 GetWidth() const = 0;
        virtual i16 GetHeight() const = 0;

        virtual ~IWindow() = default;

    protected:
        i16 mWidth;
        i16 mHeight;
        InputSystem* mInputSystem;
    };
}
