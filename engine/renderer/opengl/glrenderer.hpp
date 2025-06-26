#pragma once

#include <core/parsers/asset_loader.hpp>
#include <math/matrix.hpp>
#include <renderer/irenderer.hpp>
#include <renderer/opengl/debug_output.hpp>
#include <renderer/camera.hpp>
#include <renderer/renderable.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class GLRenderer : public IRenderer
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void BeginFrame() override;
        void DrawFrame(f64 deltaTime) override;
        void EndFrame() override;

        void Submit(const Renderable& renderable) override;

    private:
        void ClearScreen();

        void CheckCanvasResize();

        IWindow* mWindow = nullptr;
        InputSystem* mInput = nullptr;

        bool mPolygonMode = false;
        
        bool mResizeViewport = false;
        i16 mCanvasCurrentWidth = 0;
        i16 mCanvasCurrentHeight = 0;

        Camera* mCamera;
        mat4<f32> projection;
    };
}
