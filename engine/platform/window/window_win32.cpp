#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_WIN32)

#include <platform/window/window_win32.hpp>
#include <wgl/wglext.h>

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

namespace Mnemos
{
    static Key TranslateWin32Key(WPARAM wParam)
    {
        switch (wParam) {
            case 'W': return Key::W;
            case 'A': return Key::A;
            case 'S': return Key::S;
            case 'D': return Key::D;

            case VK_SPACE: return Key::Space;
            case VK_ESCAPE: return Key::Escape;

            default: return Key::Unknown;
        }
    }

    bool Win32Window::Init(const SubsystemInitInfo& info)
    {
        // Get the window configuration from init info
        const auto* windowConfig = dynamic_cast<const WindowInitInfo*>(&info);
        mWidth = windowConfig->width;
        mHeight = windowConfig->height;
        mLogger = windowConfig->logger;
        mInputSystem = windowConfig->inputSystem;
        
        mHInstance = GetModuleHandle(0);

        // Create Window Class
        const char* CLASS_NAME = "MainWindowClass";
        mWndClass = {};
        mWndClass.lpfnWndProc = MessageRouter;
        mWndClass.hInstance = mHInstance;
        mWndClass.lpszClassName = CLASS_NAME;
        mWndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        mWndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

        if (!RegisterClassA(&mWndClass))
            return false;

        // Create window with attributes
        mHwnd = CreateWindowExA
        (
            0, mWndClass.lpszClassName, windowConfig->title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, windowConfig->width, windowConfig->height,
            nullptr, nullptr, mHInstance, this
        );

        // Check that window creation didn't fail
        if(!mHwnd)
            return false;

        // Get HDC
        mHDC = GetDC(mHwnd);

        // Set dummy pixel format
        PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
        };

        int pf = ChoosePixelFormat(mHDC, &pixelFormatDescriptor);
        SetPixelFormat(mHDC, pf, &pixelFormatDescriptor);

        // Create dummy GL context
        HGLRC tempContext = wglCreateContext(mHDC);
        wglMakeCurrent(mHDC, tempContext);

        // Load WGL extensions
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
            wglGetProcAddress("wglCreateContextAttribsARB");

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
            wglGetProcAddress("wglChoosePixelFormatARB");

        if (!wglCreateContextAttribsARB)
            return false;

        // Set real pixel format
        int pixelAttribs[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
            WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB,     32,
            WGL_DEPTH_BITS_ARB,     24,
            WGL_STENCIL_BITS_ARB,   8,
            0
        };

        int pixelFormat;
        UINT numFormats;
        wglChoosePixelFormatARB(mHDC, pixelAttribs, nullptr, 1, &pixelFormat, &numFormats);

        DescribePixelFormat(mHDC, pixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor);
        SetPixelFormat(mHDC, pixelFormat, &pixelFormatDescriptor);

        // Create real GL context
        int contextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_FLAGS_ARB, 0,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0
        };

        mGLContext = wglCreateContextAttribsARB(mHDC, nullptr, contextAttribs);

        // Cleanup dummy context
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(tempContext);

        // Make real context current
        wglMakeCurrent(mHDC, mGLContext);

        // Load GL functions with GLAD
        if (!gladLoadGL())
        {
            mLogger->LogError("Failed to load OpenGL functions");
            return false;
        }

        ShowWindow(mHwnd, SW_SHOWDEFAULT);
        UpdateWindow(mHwnd);

        mLogger->LogTrace("Win32 Window initialization");

        return true;
    }

    void Win32Window::Shutdown()
    {
        mLogger->LogTrace("Win32 Window shutdown");

        wglMakeCurrent(mHDC, nullptr);
        wglDeleteContext(mGLContext);
        ReleaseDC(mHwnd, mHDC);
        DestroyWindow(mHwnd);
        UnregisterClass("MainWindowClass", GetModuleHandle(nullptr));

        mHwnd = nullptr;
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

    void Win32Window::SwapWindowBuffers()
    {
        SwapBuffers(mHDC);
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
                if (MessageBox(hwnd, "Quit application?", "Mnemos Engine", MB_OKCANCEL) == IDOK)
                    DestroyWindow(hwnd);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                mShouldClose = true;
                return 0;
            case WM_KEYDOWN:
                mInputSystem->SetKeyDown(TranslateWin32Key(wParam), true);
                break;
            case WM_KEYUP:
                mInputSystem->SetKeyDown(TranslateWin32Key(wParam), false);
                break;
            case WM_MOUSEMOVE:
                mInputSystem->SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
                break;
            case WM_LBUTTONDOWN:
                mInputSystem->SetMouseButtonDown(MouseButton::Left, true);
                break;
            case WM_LBUTTONUP:
                mInputSystem->SetMouseButtonDown(MouseButton::Left, false);
                break;
            case WM_RBUTTONDOWN:
                mInputSystem->SetMouseButtonDown(MouseButton::Right, true);
                break;
            case WM_RBUTTONUP:
                mInputSystem->SetMouseButtonDown(MouseButton::Right, false);
                break;
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
