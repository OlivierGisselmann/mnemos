#pragma once

#include <core/filesystem/resource_manager.hpp>
#include <core/logging/console_logger.hpp>
#include <core/time/frame_timer.hpp>
#include <platform/platform.hpp>
#include <platform/input/inputsystem.hpp>
#include <platform/window/iwindow.hpp>
#include <renderer/opengl/glrenderer.hpp>

namespace Mnemos
{
    struct ApplicationContext
    {
        ILogger* logger = nullptr;
        InputSystem* inputSystem;
        IWindow* window = nullptr;
        ITimer* timer = nullptr;
        IRenderer* renderer = nullptr;
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