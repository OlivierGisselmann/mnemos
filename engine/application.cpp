#include <application.hpp>

#if defined(MNEMOS_PLATFORM_LINUX)
    #include <platform/window/window_linux.hpp>
    static Mnemos::LinuxWindow sWindow;
#elif defined(MNEMOS_PLATFORM_WIN32)
    #include <platform/window/window_win32.hpp>
    static Mnemos::Win32Window sWindow;
#endif

namespace Mnemos
{
    void Application::Run()
    {
        // Get reference to platform window with polymorphism
        mWindow = &sWindow;

        // Window configuration
        WindowInitInfo windowConfig;
        windowConfig.width = 800;
        windowConfig.height = 600;
        windowConfig.title = "Yahoooo";
        windowConfig.fullscreen = false;

        // Window subsystem initialization
        mWindow->Init(windowConfig);

        OnStart();

        // TODO - Remove timer from here and put inside subsystem
        auto last = std::chrono::high_resolution_clock::now();

        while(mRunning)
        {
            auto now = std::chrono::high_resolution_clock::now();
            float delta = std::chrono::duration<float>(now - last).count();
            last = now;

            // TODO - Check for window close & engine stop events
            mWindow->PollEvents();
            mWindow->Update();
            OnUpdate(delta);

            // TODO - Render loop
            mWindow->SwapBuffers();
            OnRender();

            if(mWindow->CloseRequested())
                mRunning = false;
        }

        // TODO - Shutdown subsystems & cleanup
        OnShutdown();
        mWindow->Shutdown();
    }
}
