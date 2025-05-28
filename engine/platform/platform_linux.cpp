#include <platform/platform_linux.hpp>

namespace mnm
{
    MnemosWindow::MnemosWindow() {}
    MnemosWindow::~MnemosWindow() {}

    bool MnemosWindow::Init(const WindowConfig& conf)
    {
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
            0, 0, conf.width, conf.height, 0,
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
        XStoreName(mDisplay, mWindow, conf.title);

        // Clear window and show it
        XClearWindow(mDisplay, mWindow);
        XMapRaised(mDisplay, mWindow);

        return true;
    }

    void MnemosWindow::Update()
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

    void MnemosWindow::Shutdown()
    {
        // Free memory and close connection to XLib server
        XDestroyWindow(mDisplay, mWindow);
        XCloseDisplay(mDisplay);
    }

    bool MnemosWindow::ShoudClose() const
    {
        return mShouldClose;
    }
}
