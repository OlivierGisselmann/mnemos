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
static Mnemos::GLRenderer sRenderer;
static Mnemos::InputSystem sInputSystem;

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

            // Update engine state
            mContext.window->PollEvents();
            mContext.inputSystem->Update();
            OnUpdate(mContext.timer->GetDeltaTime());

            // Draw frame
            mContext.renderer->BeginFrame();
            mContext.renderer->DrawFrame();
            mContext.renderer->EndFrame();
            OnRender();

            // Check for close request (input and destroy window)
            if (mContext.window->CloseRequested() || mContext.inputSystem->IsKeyDown(Key::Escape))
            {
                mContext.logger->LogTrace("Close requested");
                mRunning = false;
            }

            // Limit framerate if enabled
            mContext.timer->Sleep();
        }

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
            mContext.logger->LogFatal("Failed to initialize timer");
            return false;
        }

        // Input System initialization
        mContext.inputSystem = &sInputSystem;
        InputSystemInitInfo inputConfig;
        inputConfig.logger = mContext.logger;
        if(!mContext.inputSystem->Init(inputConfig))
        {
            mContext.logger->LogFatal("Failed to initialize input system");
            return false;
        }

        // Window initialization
        mContext.window = &sWindow;
        WindowInitInfo windowConfig;
        windowConfig.width = 1280;
        windowConfig.height = 720;
        windowConfig.title = "eskesamarch?";
        windowConfig.fullscreen = false;
        windowConfig.logger = mContext.logger;
        windowConfig.inputSystem = mContext.inputSystem;
        if(!mContext.window->Init(windowConfig))
        {
            mContext.logger->LogFatal("Failed to initialize window");
            return false;
        }

        // Renderer initialization
        mContext.renderer = &sRenderer;
        RendererInitInfo rendererConfig;
        rendererConfig.window = mContext.window;
        rendererConfig.logger = mContext.logger;
        if(!mContext.renderer->Init(rendererConfig))
        {
            mContext.logger->LogFatal("Failed to initialize renderer");
            return false;
        }

        return true;
    }

    void Application::ShutdownSubsystems()
    {
        mContext.renderer->Shutdown();
        mContext.window->Shutdown();
        mContext.inputSystem->Shutdown();
        mContext.timer->Shutdown();
        mContext.logger->Shutdown();
    }
}
