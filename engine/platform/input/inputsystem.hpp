#pragma once

#include <core/isubsystem.hpp>
#include <core/logging/ilogger.hpp>
#include <platform/types.hpp>

namespace Mnemos
{
    enum class Key
    {
        W, A, S, D,
        Escape, Space,
        Unknown, Count
    };

    enum class MouseButton
    {
        Left, Right, Middle,
        Count
    };

    struct InputSystemInitInfo : public SubsystemInitInfo
    {
        ILogger* logger = nullptr;
    };

    class InputSystem : public ISubsystem
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown();

        void Update();
        void SetKeyDown(Key keycode, bool down);
        void SetMouseButtonDown(MouseButton button, bool down);
        void SetMousePosition(i16 x, i16 y);

        bool IsKeyPressed(Key key) const;
        bool IsKeyDown(Key key) const;
        bool IsKeyReleased(Key key) const;

        i16 GetMouseX() const;
        i16 GetMouseY() const;

    protected:
        bool mCurrentKeys[(int)Key::Count] = {};
        bool mPreviousKeys[(int)Key::Count] = {};

        bool mCurrentMouse[(int)MouseButton::Count] = {};
        bool mPreviousMouse[(int)MouseButton::Count] = {};

        i16 mMouseX = 0;
        i16 mMouseY = 0;

        ILogger* mLogger = nullptr;
    };
}
