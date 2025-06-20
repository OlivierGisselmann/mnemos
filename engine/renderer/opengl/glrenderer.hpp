#pragma once

#include <core/filesystem/resource_manager.hpp>
#include <math/matrix.hpp>
#include <renderer/irenderer.hpp>
#include <renderer/camera.hpp>
#include <renderer/opengl/mesh.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>
#include <renderer/opengl/vertex_array.hpp>

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

    private:
        void ClearScreen();

        void CheckCanvasResize();

        IWindow* mWindow = nullptr;
        InputSystem* mInput = nullptr;
        ILogger* mLogger = nullptr;

        bool mPolygonMode = false;
        
        bool mResizeViewport = false;
        i16 mCanvasCurrentWidth = 0;
        i16 mCanvasCurrentHeight = 0;

        Camera* mCamera;
        mat4<f32> projection;
        mat4<f32> view;
    };
}
