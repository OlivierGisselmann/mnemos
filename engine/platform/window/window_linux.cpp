#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_LINUX)

#include <platform/window/window_linux.hpp>

typedef GLXContext (*PFNGLXCREATECONTEXTATTRIBSARBPROC)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace Mnemos
{
    bool LinuxWindow::Init(const SubsystemInitInfo& info)
    {
        // Get the window configuration from init info
        const auto* windowConfig = dynamic_cast<const WindowInitInfo*>(&info);
        mWidth = windowConfig->width;
        mHeight = windowConfig->height;
        mLogger = windowConfig->logger;

        // Get XLib display
        mDisplay = XOpenDisplay(nullptr);
        if(nullptr == mDisplay)
            return false;

        // Get screen and screen ID
        mScreen = DefaultScreenOfDisplay(mDisplay);
        mScreenId = DefaultScreen(mDisplay);

        // Set framebuffer configuration
        static int visualAttributes[] = 
        {
            GLX_X_RENDERABLE    , True,
            GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
            GLX_RENDER_TYPE     , GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
            GLX_RED_SIZE        , 8,
            GLX_GREEN_SIZE      , 8,
            GLX_BLUE_SIZE       , 8,
            GLX_ALPHA_SIZE      , 8,
            GLX_DEPTH_SIZE      , 24,
            GLX_STENCIL_SIZE    , 8,
            GLX_DOUBLEBUFFER    , True,
            None
        };

        // Get framebuffer configuration
        int framebufferCount = 0;
        GLXFBConfig* framebufferConfig = glXChooseFBConfig(mDisplay, mScreenId, visualAttributes, &framebufferCount);

        if(!framebufferConfig || 0 == framebufferCount)
            return false;

        XVisualInfo* visualInfo = glXGetVisualFromFBConfig(mDisplay, framebufferConfig[0]);
        
        // Set attributes for window creation
        mAttributes.colormap = XCreateColormap(mDisplay, RootWindow(mDisplay, visualInfo->screen), visualInfo->visual, AllocNone);
        mAttributes.border_pixel = BlackPixel(mDisplay, mScreenId);
        mAttributes.background_pixel = WhitePixel(mDisplay, mScreenId);
        mAttributes.override_redirect = True;
        mAttributes.event_mask = ExposureMask | KeyPressMask;

        // Create window
        mWindow = XCreateWindow(
            mDisplay, RootWindow(mDisplay, visualInfo->screen),
            0, 0, windowConfig->width, windowConfig->height, 0,
            visualInfo->depth, InputOutput, visualInfo->visual,
            CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
            &mAttributes
        );
        
        // Check for window creation error
        if(BadAlloc == mWindow)
            return false;

        // Redirect close event
        mDeleteWindow = XInternAtom(mDisplay, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(mDisplay, mWindow, &mDeleteWindow, 1);

        // Set window title
        XStoreName(mDisplay, mWindow, windowConfig->title);

        // Clear window and show it
        XClearWindow(mDisplay, mWindow);
        XMapRaised(mDisplay, mWindow);

        // Create temporary GLXContext
        GLXContext tempContext = glXCreateContext(mDisplay, visualInfo, 0, GL_TRUE);
        glXMakeCurrent(mDisplay, mWindow, tempContext);

        // Get glXCreateContextAttribsARB
        PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
        (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddressARB(
            (const GLubyte*)"glXCreateContextAttribsARB");

        if(!glXCreateContextAttribsARB)
        {
            mLogger->Log(LogLevel::ERR, "glXCreateCOntextAttribsARB not supported");
            return false;
        }

        // Create modern OpenGL context
        int contextAttributes[] = 
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
            GLX_CONTEXT_MINOR_VERSION_ARB, 5,
            GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
            None
        };

        mContext = glXCreateContextAttribsARB(mDisplay, framebufferConfig[0], 0, True, contextAttributes);

        // Cleanup temporary context
        glXMakeCurrent(mDisplay, None, nullptr);
        glXDestroyContext(mDisplay, tempContext);

        // Make new context current
        glXMakeCurrent(mDisplay, mWindow, mContext);

        // Load GL Functions with GLAD
        if (!gladLoadGLLoader((GLADloadproc)glXGetProcAddress))
        {
            mLogger->Log(LogLevel::ERR, "Failed to load OpenGL functions");
            return false;
        }

        mLogger->Log(LogLevel::TRACE, "X11 Window initialized");

        return true;
    }

    void LinuxWindow::Shutdown()
    {
        mLogger->Log(LogLevel::TRACE, "X11 Window shutdown");

        // Destroy OpenGL context
        glXMakeCurrent(mDisplay, None, nullptr);
        glXDestroyContext(mDisplay, mContext);

        // Free memory and close connection to XLib server
        XDestroyWindow(mDisplay, mWindow);
        XCloseDisplay(mDisplay);
    }

    void LinuxWindow::Update()
    {
        
    }

    void LinuxWindow::PollEvents()
    {
        // Poll events
        if(XPending(mDisplay) > 0)
        {
            XNextEvent(mDisplay, &mEvent);

            // Close event
            if(mEvent.xclient.data.l[0] == mDeleteWindow)
                mShouldClose = true;
            else if(mEvent.type == DestroyNotify)
                mShouldClose = true;
        }
    }

    void LinuxWindow::SwapWindowBuffers()
    {
        glXSwapBuffers(mDisplay, mWindow);
    }

    bool LinuxWindow::CloseRequested() const
    {
        return mShouldClose;
    }

    i16 LinuxWindow::GetWidth() const
    {
        return mWidth;
    }

    i16 LinuxWindow::GetHeight() const
    {
        return mHeight;
    }
}

#endif
