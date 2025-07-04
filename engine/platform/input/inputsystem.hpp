#pragma once

#include <core/isubsystem.hpp>
#include <core/logging/logger_manager.hpp>
#include <platform/input/keycodes.hpp>
#include <platform/types.hpp>

namespace Mnemos
{
    class InputSystem : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown();

        void Update();
        void SetKeyDown(Key keycode, bool down);
        void SetMouseButtonDown(MouseButton button, bool down);
        void SetMousePosition(i16 x, i16 y);
        void SetMouseDelta(f32 dx, f32 dy);

        bool IsKeyPressed(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyReleased(Key key) const;

        bool IsMouseButtonPressed(MouseButton button) const;
        bool IsMouseButtonDown(MouseButton button) const;
        bool IsMouseButtonReleased(MouseButton button) const;

        i16 GetMouseX() const;
        i16 GetMouseY() const;

        f32 GetMouseDeltaX() const;
        f32 GetMouseDeltaY() const;

    protected:
        bool mCurrentKeys[(int)Key::Count] = {};
        bool mPreviousKeys[(int)Key::Count] = {};

        bool mCurrentMouse[(int)MouseButton::Count] = {};
        bool mPreviousMouse[(int)MouseButton::Count] = {};

        i16 mMouseX = 0;
        i16 mMouseY = 0;
        f32 mDeltaX = 0;
        f32 mDeltaY = 0;
    };
}
