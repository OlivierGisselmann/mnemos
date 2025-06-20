#include <platform/input/inputsystem.hpp>

#include <iostream>

namespace Mnemos
{
    bool InputSystem::Init(const SubsystemInitInfo& info)
    {
        const auto* inputConfig = dynamic_cast<const InputSystemInitInfo*>(&info);
        mLogger = inputConfig->logger;

        mLogger->LogTrace("Input System initialized");

        return true;
    }

    void InputSystem::Shutdown()
    {
        mLogger->LogTrace("Input System shutdown");
    }

    void InputSystem::Update()
    {
        // Swap key state from current to previous each frame
        for(int i = 0; i < (int)Key::Count; ++i)
        {
            mPreviousKeys[i] = mCurrentKeys[i];           
        }

        for(int i = 0; i < (int)MouseButton::Count; ++i)
        {
            mPreviousMouse[i] = mCurrentMouse[i];
        }
    }

    void InputSystem::SetKeyDown(Key keycode, bool down)
    {
        mCurrentKeys[(int)keycode] = down;
    }

    void InputSystem::SetMouseButtonDown(MouseButton button, bool down)
    {
        mCurrentMouse[(int)button] = down;
    }

    void InputSystem::SetMousePosition(i16 x, i16 y)
    {
        mMouseX = x;
        mMouseY = y;
    }

    void InputSystem::SetMouseDelta(f32 dx, f32 dy)
    {
        mDeltaX = dx;
        mDeltaY = dy;
    }

    bool InputSystem::IsKeyPressed(Key key) const
    {
        int i = (int)key;

        // If key is pressed this frame but wasn't last frame
        return mCurrentKeys[i] && !mPreviousKeys[i];
    }

    bool InputSystem::IsKeyDown(Key key) const
    {
        return mCurrentKeys[(int)key];
    }

    bool InputSystem::IsKeyReleased(Key key) const
    {
        int i = (int)key;

        // If key isn't pressed this frame but was last frame
        return !mCurrentKeys[i] && mPreviousKeys[i];
    }

    bool InputSystem::IsMouseButtonPressed(MouseButton button) const
    {
        int i = (int)button;

        // If button is pressed this frame but wasn't last frame
        return mCurrentMouse[i] && !mPreviousMouse[i];
    }

    bool InputSystem::IsMouseButtonDown(MouseButton button) const
    {
        return mCurrentMouse[(int)button];
    }

    bool InputSystem::IsMouseButtonReleased(MouseButton button) const
    {
        int i = (int)button;

        // If button isn't pressed this frame but was last frame
        return !mCurrentMouse[i] && mPreviousMouse[i];
    }

    i16 InputSystem::GetMouseX() const
    {
        return mMouseX;
    }

    i16 InputSystem::GetMouseY() const
    {
        return mMouseY;
    }

    f32 InputSystem::GetMouseDeltaX() const
    {
        return mDeltaX;
    }

    f32 InputSystem::GetMouseDeltaY() const
    {
        return mDeltaY;
    }
}
