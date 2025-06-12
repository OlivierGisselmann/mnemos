#include <renderer/opengl/glrenderer.hpp>

#include <iostream>

namespace Mnemos
{
    bool GLRenderer::Init(const SubsystemInitInfo& info)
    {
        // Get the renderer configuration from init info
        const auto* rendererConfig = dynamic_cast<const RendererInitInfo*>(&info);
        mLogger = rendererConfig->logger;
        mWindow = rendererConfig->window;

        // Setup OpenGL properties
        //glEnable(GL_DEPTH_TEST);

        mLogger->LogTrace("Renderer initialized");
        mLogger->LogTrace((const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        mLogger->LogTrace("Renderer shutdown");
    }

    void GLRenderer::BeginFrame()
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderer::DrawFrame()
    {

    }

    void GLRenderer::EndFrame()
    {
        mWindow->SwapWindowBuffers();
    }
}
