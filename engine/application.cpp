#include <application.hpp>
#include <core/assert.hpp>

// Global Static Instances
static Mnemos::LoggerManager sLoggerManager;
static Mnemos::ITimer* sTimer = new Mnemos::FrameTimer();
static Mnemos::IRenderer* sRenderer = new Mnemos::GLRenderer();
static Mnemos::InputSystem sInputSystem;

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
        if(!InitSubsystems())
            return;

        OnStart();

        while(mRunning)
        {
            mContext.window->PollEvents();

            if(mContext.timer->Tick())
            {
                Draw();
                Update();
            }

            // Check for close request (input and destroy window)
            if (mContext.window->CloseRequested() || mContext.inputSystem->IsKeyDown(Key::Escape))
            {
                LOG(LogLevel::INFO, "Close requested");
                mRunning = false;
            }
        }

        OnShutdown();
        ShutdownSubsystems();
    }

    // TODO - Implement priority queue for instances init
    bool Application::InitSubsystems()
    {
        // Logger initialization
        mContext.loggerManager = &sLoggerManager;
        if(!mContext.loggerManager->Init({}))
            return false;

        // ResourceManager initialization
        ResourceManager::Get().SetAssetRoot("../../../");

        // Timer initialization
        mContext.timer = sTimer;
        FrameTimerInitInfo timerConfig;
        timerConfig.targetFramerate = 120;
        timerConfig.limitFramerate = true;
        if(!mContext.timer->Init(timerConfig))
        {
            LOG(LogLevel::FATAL, "Failed to initialize timer");
            return false;
        }

        // Input System initialization
        mContext.inputSystem = &sInputSystem;
        if(!mContext.inputSystem->Init({}))
        {
            LOG(LogLevel::FATAL, "Failed to initialize input system");
            return false;
        }

        // Window initialization
        mContext.window = &sWindow;
        WindowInitInfo windowConfig;
        windowConfig.width = 1280;
        windowConfig.height = 720;
        windowConfig.title = "eskesamarch?";
        windowConfig.fullscreen = false;
        windowConfig.inputSystem = mContext.inputSystem;
        if(!mContext.window->Init(windowConfig))
        {
            LOG(LogLevel::FATAL, "Failed to initialize window");
            return false;
        }

        // Renderer initialization
        mContext.renderer = sRenderer;
        RendererInitInfo rendererConfig;
        rendererConfig.window = mContext.window;
        rendererConfig.input = mContext.inputSystem;
        if(!mContext.renderer->Init(rendererConfig))
        {
            LOG(LogLevel::FATAL, "Failed to initialize renderer");
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
        mContext.loggerManager->Shutdown();
    }

    void Application::Update()
    {
        OnUpdate(mContext.timer->GetDeltaTime());
        mContext.inputSystem->Update();
    }

    void Application::Draw()
    {
        mContext.renderer->BeginFrame();
        mContext.renderer->DrawFrame(mContext.timer->GetDeltaTime());
        mContext.renderer->EndFrame();
    }
}
