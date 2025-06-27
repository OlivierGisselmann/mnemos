#pragma once

#include <math/matrix.hpp>
#include <platform/input/inputsystem.hpp>

namespace Mnemos
{
    class Camera
    {
    public:
        Camera(InputSystem* input, const vec3<f32>& position);
        ~Camera();

        const mat4<f32>& GetViewMatrix() const;
        const vec3<f32>& GetPosition() const;

        void Update(f32 delta);

    private:
        void ProcessInput(f32 delta);
        void ProcessMouse(f32 delta);
        void UpdateVectors();

        mat4<f32> mViewMatrix;

        vec3<f32> mPosition;
        vec3<f32> mFront;
        vec3<f32> mRight;
        vec3<f32> mUp;
        vec3<f32> mWorldUp;

        f32 mYaw = 0.f;
        f32 mPitch = 0.f;

        f32 mSpeed = 0.f;
        f32 mMouseSensitivity = 0.f;
        f32 mZoom = 0.f;
        
        bool mFirstMouse;
        f32 mLastX = 0.f;
        f32 mLastY = 0.f;
        f32 mXOffset = 0.f;
        f32 mYOffset = 0.f;

        InputSystem* mInput = nullptr;
    };
}
