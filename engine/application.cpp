#include <application.hpp>

#include <platform/platform_linux.hpp>

#include <chrono>

static mnm::MnemosWindow sWindow;

namespace mnm
{
    void Application::Run()
    {
        // TODO - Init subsystems
        const WindowConfig config
        {
            800,
            600,
            "Mnemos Engine"
        };

        if(!sWindow.Init(config))
            return;

        OnStart();

        // TODO - Remove timer from here and put inside subsystem
        auto last = std::chrono::high_resolution_clock::now();

        while(mRunning)
        {
            auto now = std::chrono::high_resolution_clock::now();
            float delta = std::chrono::duration<float>(now - last).count();
            last = now;

            // TODO - Check for window close & engine stop events
            sWindow.Update();
            OnUpdate(delta);

            // TODO - Render loop
            OnRender();

            if(sWindow.ShoudClose())
                mRunning = false;
        }

        // TODO - Shutdown subsystems & cleanup
        OnShutdown();
        sWindow.Shutdown();
    }
}
