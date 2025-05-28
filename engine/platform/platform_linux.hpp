#pragma once

#include <platform/types.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

namespace Mnemos
{
    struct WindowConfig
    {
        i16 width;
        i16 height;
        const char* title;
    };

    class MnemosWindow
    {
    public:
        MnemosWindow();
        ~MnemosWindow();

        bool Init(const WindowConfig& conf);
        void Update();
        void Shutdown();

        bool ShoudClose() const;

    private:
        Display* mDisplay;
        Screen* mScreen;
        i8 mScreenId;
        Window mWindow;
        XSetWindowAttributes mAttributes{};
        bool mShouldClose;

        XEvent mEvent;
        Atom mDeleteWindow;
    };
}
