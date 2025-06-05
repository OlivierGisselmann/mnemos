#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_LINUX)

#include <platform/window/window_linux.hpp>

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

        // Set attributes for window creation
        mAttributes.border_pixel = BlackPixel(mDisplay, mScreenId);
        mAttributes.background_pixel = WhitePixel(mDisplay, mScreenId);
        mAttributes.override_redirect = True;
        //mAttributes.colormap = XCreateColormap(mDisplay, RootWindow(mDisplay, mWindow), CopyFromParent, AllocNone);
        mAttributes.event_mask = ExposureMask;

        // Create window
        mWindow = XCreateWindow(
            mDisplay, RootWindow(mDisplay, mScreenId),
            0, 0, windowConfig->width, windowConfig->height, 0,
            CopyFromParent, InputOutput, CopyFromParent,
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

        mLogger->Log(LogLevel::TRACE, "X11 Window initialization");

        return true;
    }

    void LinuxWindow::Shutdown()
    {
        mLogger->Log(LogLevel::TRACE, "X11 Window shutdown");

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

    void LinuxWindow::SwapBuffers()
    {

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
