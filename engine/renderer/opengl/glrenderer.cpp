#include <renderer/opengl/glrenderer.hpp>

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

        mLogger->Log(LogLevel::TRACE, "Renderer initialized");

        return true;
    }

    void GLRenderer::Shutdown()
    {
        mLogger->Log(LogLevel::TRACE, "Renderer shutdown");
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
