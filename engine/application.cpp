#include <application.hpp>

namespace Mnemos
{
    static MnemosWindow sWindow;

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
        {
            Log(FATAL, "Failed to create window");
            return;
        }

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
