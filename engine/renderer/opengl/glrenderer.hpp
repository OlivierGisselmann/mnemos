#pragma once

#include <renderer/irenderer.hpp>
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
        void DrawFrame() override;
        void EndFrame() override;

    private:
        void ClearScreen();
        void DrawIndexed(Shader& shader, VertexArray& vao);

        IWindow* mWindow = nullptr;
        InputSystem* mInput = nullptr;
        ILogger* mLogger = nullptr;

        bool mPolygonMode = false;
    };
}
