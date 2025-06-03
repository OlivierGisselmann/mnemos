#pragma once

#include <core/logging.hpp>
#include <platform/platform.hpp>
#include <platform/window/iwindow.hpp>

#include <chrono>

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
        bool mRunning {true};

        IWindow* mWindow {nullptr};
    };
}