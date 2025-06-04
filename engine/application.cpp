#include <application.hpp>

// Global Static Instances
#if defined(MNEMOS_PLATFORM_LINUX)
    #include <platform/window/window_linux.hpp>
    static Mnemos::LinuxWindow sWindow;
#elif defined(MNEMOS_PLATFORM_WIN32)
    #include <platform/window/window_win32.hpp>
    static Mnemos::Win32Window sWindow;
#endif

static Mnemos::FrameTimer sTimer;

namespace Mnemos
{
    void Application::Run()
    {
        if(!InitSubsystems())
            return;

        OnStart();

        while(mRunning)
        {
            mTimer->Tick();

            // TODO - Check for window close & engine stop events
            mWindow->PollEvents();
            mWindow->Update();
            OnUpdate(mTimer->GetDeltaTime());

            // TODO - Render loop
            mWindow->SwapBuffers();
            OnRender();

            if(mWindow->CloseRequested())
                mRunning = false;

            mTimer->Sleep();
        }

        // TODO - Shutdown subsystems & cleanup
        OnShutdown();
        ShutdownSubsystems();
    }

    // TODO - Implement priority queue for instances init
    bool Application::InitSubsystems()
    {
        // Timer initialization
        mTimer = &sTimer;
        FrameTimerInitInfo timerConfig;
        timerConfig.targetFramerate = 60;
        timerConfig.limitFramerate = true;
        if(!mTimer->Init(timerConfig))
        {
            Log(FATAL, "Failed to initialize timer");
            return false;
        }

        // Window initialization
        mWindow = &sWindow;
        WindowInitInfo windowConfig;
        windowConfig.width = 1280;
        windowConfig.height = 720;
        windowConfig.title = "Youpiii";
        windowConfig.fullscreen = false;
        if(!mWindow->Init(windowConfig))
        {
            Log(FATAL, "Failed to initialize window");
            return false;
        }

        return true;
    }

    void Application::ShutdownSubsystems()
    {
        mWindow->Shutdown();
        mTimer->Shutdown();
    }
}
