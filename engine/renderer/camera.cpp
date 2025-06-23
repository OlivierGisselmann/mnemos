#include <renderer/camera.hpp>

#include <iostream>

namespace Mnemos
{
    static vec3<f32> movement(0.f);

    Camera::Camera(InputSystem* input, const vec3<f32>& position)
    : mPosition(position), mFront({0.f, 0.f, -1.f}), mUp({0.f, 1.f, 0.f}), mWorldUp(mUp), mRight({0.f}), mInput(input)
    {
        mYaw = -90.f;
        mPitch = 0.f;

        mSpeed = 5.f;
        mMouseSensitivity = .15f;
        mZoom = 45.0f;

        UpdateVectors();
    }

    Camera::~Camera(){}
    
    const mat4<f32>& Camera::GetViewMatrix() const
    {
        return mViewMatrix;
    }

    void Camera::Update(f32 delta)
    {
        ProcessMouse(delta);
        ProcessInput(delta);
        UpdateVectors();
    }

    void Camera::ProcessInput(f32 delta)
    {
        f32 velocity = mSpeed * delta;

        if(mInput->IsKeyDown(Key::Z))
            mPosition -= mFront * velocity;
        if(mInput->IsKeyDown(Key::S))
            mPosition += mFront * velocity;
        if(mInput->IsKeyDown(Key::Q))
            mPosition -= mRight * velocity;
        if(mInput->IsKeyDown(Key::D))
            mPosition += mRight * velocity;
        if(mInput->IsKeyDown(Key::A))
            mPosition += mUp * velocity;
        if(mInput->IsKeyDown(Key::E))
            mPosition -= mUp * velocity;
    }

    void Camera::ProcessMouse(f32 delta)
    {
        f32 xPos = mInput->GetMouseX();
        f32 yPos = mInput->GetMouseY();

        mXOffset = (xPos - mLastX) * mMouseSensitivity;
        mYOffset = (yPos - mLastY) * mMouseSensitivity;
        mLastX = xPos;
        mLastY = yPos;

        // Only rotate camera if RMB is down
        if(mInput->IsMouseButtonDown(MouseButton::Right))
        {
            mYaw += mXOffset;
            mPitch -= mYOffset;
        }

        // Constrain axis
        if(mPitch > 89.f)
            mPitch = 89.f;
        if(mPitch < -89.f)
            mPitch = -89.f;
    }

    void Camera::UpdateVectors()
    {
        vec3<f32> front(0.f);
        front.x = cos(Radians(mYaw)) * cos(Radians(mPitch));
        front.y = sin(Radians(mPitch));
        front.z = sin(Radians(mYaw)) * cos(Radians(mPitch));

        mFront = Normalize(front);
        mRight = Normalize(Cross(mWorldUp, mFront));
        mUp = Normalize(Cross(mFront, mRight));

        mViewMatrix = LookAt(mPosition, mPosition + mFront, mUp);
    }
}
