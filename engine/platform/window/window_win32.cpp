#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_WIN32)

#include <platform/window/window_win32.hpp>

namespace Mnemos
{
    bool Win32Window::Init(const SubsystemInitInfo& info)
    {
        // Get the window configuration from init info
        const auto* windowConfig = dynamic_cast<const WindowInitInfo*>(&info);
        mWidth = windowConfig->width;
        mHeight = windowConfig->height;
        mLogger = windowConfig->logger;
        
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
            return false;

        ShowWindow(mHwnd, SW_SHOWDEFAULT);

        mLogger->Log(LogLevel::TRACE, "Win32 Window initialization");

        return true;
    }

    void Win32Window::Shutdown()
    {
        mLogger->Log(LogLevel::TRACE, "Win32 Window shutdown");
    }

    void Win32Window::Update()
    {
        
    }

    void Win32Window::PollEvents()
    {
        // Loop through all events
        while (PeekMessage(&mMsg, nullptr, 0, 0, PM_REMOVE))
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
        Win32Window* pThis;

        // Get a reference to the Win32Window instance via window's user set pointer
        if (uMsg == WM_NCCREATE)
        {
            LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
            pThis = static_cast<Win32Window*>(lpcs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        }
        else
        {
            pThis = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        // If it exists, send messages to its method
        if (pThis)
            return pThis->WindowProc(hwnd, uMsg, wParam, lParam);

        // Default return
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    LRESULT CALLBACK Win32Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            case WM_CLOSE:
                if(MessageBox(hwnd, "Quit application?", "Mnemos Engine", MB_OKCANCEL) == IDOK)
                    DestroyWindow(hwnd);
                else
                    return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                mShouldClose = true;
                return 0;
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    i16 Win32Window::GetWidth() const
    {
        return mWidth;
    }

    i16 Win32Window::GetHeight() const
    {
        return mHeight;
    }
}

#endif
