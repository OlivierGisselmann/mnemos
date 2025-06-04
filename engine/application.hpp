#pragma once

#include <core/logging.hpp>
#include <platform/platform.hpp>
#include <platform/window/iwindow.hpp>
#include <core/time/frame_timer.hpp>

namespace Mnemos
{
    class Application
    {
    public:
        virtual ~Application() = default;

        void Run();

    protected:
        virtual void OnStart() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnShutdown() {}

    private:
        bool InitSubsystems();
        void ShutdownSubsystems();

    private:
        bool mRunning {true};

        IWindow* mWindow {nullptr};
        FrameTimer* mTimer {nullptr};
    };
}