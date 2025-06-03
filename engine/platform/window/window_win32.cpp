#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_WIN32)

#include <platform/window/window_win32.hpp>
#include <core/logging.hpp>


namespace Mnemos
{
    bool Win32Window::Init(const SubsystemInitInfo& info)
    {
        // Get the window configuration from init info
        const auto* windowConfig = dynamic_cast<const WindowInitInfo*>(&info);

        mHInstance = GetModuleHandle(nullptr);

        const char* CLASS_NAME = "MainWindowClass";

        mWndClass = {};
        mWndClass.lpfnWndProc = MessageRouter;
        mWndClass.hInstance = mHInstance;
        mWndClass.lpszClassName = CLASS_NAME;

        RegisterClassA(&mWndClass);

        mHwnd = CreateWindowExA
        (
            0, CLASS_NAME, windowConfig->title, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, windowConfig->width, windowConfig->height,
            nullptr, nullptr, mHInstance, this
        );

        if(!mHwnd)
        {
            Log(FATAL, "Unable to create the Win32 window");
            return false;
        }

        ShowWindow(mHwnd, SW_SHOWDEFAULT);

        Log(TRACE, "Win32 Window initialization");

        return true;
    }

    void Win32Window::Shutdown()
    {
        Log(TRACE, "Win32 Window shutdown");

        // Free memory and close connection to XLib server
        XDestroyWindow(mDisplay, mWindow);
        XCloseDisplay(mDisplay);
    }

    void Win32Window::Update()
    {
        
    }

    void Win32Window::PollEvents()
    {
        // Loop through all events
        while(GetMessage(&mMsg, nullptr, 0, 0))
        {
            TranslateMessage(&mMsg);
            DispatchMessage(&mMsg);
        }
    }

    void Win32Window::SwapBuffers()
    {

    }

    bool Win32Window::CloseRequested() const
    {
        return mShouldClose;
    }

    LRESULT CALLBACK Win32Window::MessageRouter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Win32Window* app;

        // Get instance of window to reroute message
        if (uMsg == WM_CREATE)
        {
            app = (Win32Window*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)app);
        }
        else
            app = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

        // Route events to window's method
        return app->WindowProc(hwnd, uMsg, wParam, lParam);
    }

    LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch(uMsg)
        {
            case WM_CLOSE:
                if(MessageBox(hwnd, "Quit?", "CloverEngine", MB_OKCANCEL) == IDOK)
                    DestroyWindow(hwnd);
                else
                    return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                mRunning = false;
                return 0;
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                Input::OnKeyChange((int)wParam, true);
                break;
            case WM_KEYUP:
            case WM_SYSKEYUP:
                Input::OnKeyChange((int)wParam, false);
                break;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

#endif
