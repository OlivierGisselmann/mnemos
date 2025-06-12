#pragma once

#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_WIN32)

#include <platform/window/iwindow.hpp>
#include <platform/types.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <glad/glad.h>
#include <gl/GL.h>

namespace Mnemos
{
    class Win32Window : public IWindow
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void PollEvents() override;
        void SwapWindowBuffers() override;
        bool CloseRequested() const override;

        i16 GetWidth() const override;
        i16 GetHeight() const override;

    private:
        static LRESULT CALLBACK MessageRouter(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        HINSTANCE mHInstance;
        WNDCLASSA mWndClass;
        HWND mHwnd;
        HDC mHDC;
        HGLRC mGLContext;
        MSG mMsg;

        bool mShouldClose = false;
        ILogger* mLogger = nullptr;
    };
}

#endif