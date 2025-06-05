#pragma once

#include <core/logging/console_logger.hpp>
#include <platform/platform.hpp>
#include <platform/window/iwindow.hpp>
#include <core/time/frame_timer.hpp>

namespace Mnemos
{
    struct ApplicationContext
    {
        ILogger* logger = nullptr;
        IWindow* window = nullptr;
        ITimer* timer = nullptr;
    };

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
        ApplicationContext mContext;
        bool mRunning {true};
    };
}