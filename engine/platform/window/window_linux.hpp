#pragma once

#include <platform/platform.hpp>
#if defined(MNEMOS_PLATFORM_LINUX)

#include <platform/window/iwindow.hpp>
#include <platform/types.hpp>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace Mnemos
{
    class LinuxWindow : public IWindow
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void PollEvents() override;
        void Update() override;
        void SwapBuffers() override;
        bool CloseRequested() const override;

        i16 GetWidth() const override;
        i16 GetHeight() const override;

    private:
        Display* mDisplay;
        Screen* mScreen;
        i8 mScreenId;
        Window mWindow;
        XSetWindowAttributes mAttributes{};
        bool mShouldClose;

        XEvent mEvent;
        Atom mDeleteWindow;

        ILogger* mLogger = nullptr;
    };
}

#endif