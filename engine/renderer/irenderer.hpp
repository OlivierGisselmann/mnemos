#pragma once

#include <core/isubsystem.hpp>
#include <platform/window/iwindow.hpp>
#include <core/time/itimer.hpp>

namespace Mnemos
{
    struct RendererInitInfo : public SubsystemInitInfo
    {
        IWindow* window = nullptr;
        InputSystem* input = nullptr;
    };

    class IRenderer : ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override = 0;
        void Shutdown() override = 0;

        virtual void BeginFrame() = 0;
        virtual void DrawFrame(f64 deltaTime) = 0;
        virtual void EndFrame() = 0;

        virtual ~IRenderer() = default;
    };
}
