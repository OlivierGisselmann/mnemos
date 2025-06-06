#include <application.hpp>

// Global Static Instances
#if defined(MNEMOS_PLATFORM_LINUX)
    #include <platform/window/window_linux.hpp>
    static Mnemos::LinuxWindow sWindow;
#elif defined(MNEMOS_PLATFORM_WIN32)
    #include <platform/window/window_win32.hpp>
    static Mnemos::Win32Window sWindow;
#endif

static Mnemos::ConsoleLogger sLogger;
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
            mContext.timer->Tick();

            // TODO - Check for window close & engine stop events
            mContext.window->PollEvents();
            mContext.window->Update();
            OnUpdate(mContext.timer->GetDeltaTime());

            // TODO - Render loop
            mContext.window->SwapBuffers();
            OnRender();

            if(mContext.window->CloseRequested())
                mRunning = false;

            mContext.timer->Sleep();
        }

        // TODO - Shutdown subsystems & cleanup
        OnShutdown();
        ShutdownSubsystems();
    }

    // TODO - Implement priority queue for instances init
    bool Application::InitSubsystems()
    {
        // Logger initialization
        mContext.logger = &sLogger;
        if(!mContext.logger->Init({}))
        {
            return false;
        }

        // Timer initialization
        mContext.timer = &sTimer;
        FrameTimerInitInfo timerConfig;
        timerConfig.targetFramerate = 60;
        timerConfig.limitFramerate = true;
        timerConfig.logger = mContext.logger;
        if(!mContext.timer->Init(timerConfig))
        {
            mContext.logger->Log(LogLevel::FATAL, "Failed to initialize timer");
            return false;
        }

        // Window initialization
        mContext.window = &sWindow;
        WindowInitInfo windowConfig;
        windowConfig.width = 1280;
        windowConfig.height = 720;
        windowConfig.title = "Youpiii";
        windowConfig.fullscreen = false;
        windowConfig.logger = mContext.logger;
        if(!mContext.window->Init(windowConfig))
        {
            mContext.logger->Log(LogLevel::FATAL, "Failed to initialize window");
            return false;
        }

        return true;
    }

    void Application::ShutdownSubsystems()
    {
        mContext.window->Shutdown();
        mContext.timer->Shutdown();
        mContext.logger->Shutdown();
    }
}
