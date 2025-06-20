#include <renderer/opengl/glrenderer.hpp>

static f64 sDelta = 0;

namespace Mnemos
{
    Texture* texture;
    Shader* shader;
    Mesh* mesh;

    bool GLRenderer::Init(const SubsystemInitInfo& info)
    {
        // Get the renderer configuration from init info
        const auto* rendererConfig = dynamic_cast<const RendererInitInfo*>(&info);
        mLogger = rendererConfig->logger;
        mInput = rendererConfig->input;
        mWindow = rendererConfig->window;

        // Setup OpenGL properties
        glEnable(GL_DEPTH_TEST);

        // Load resources
        shader = new Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");

        // Camera
        mCamera = new Camera(mInput, {0.f, 0.f, -3.f});
        projection = Perspective(55.0f, ((f32)mWindow->GetWidth() / (f32)mWindow->GetHeight()), 0.1f, 100.0f);

        vec3<f32> camPos(0.f, 0.f, -10.f);
        vec3<f32> camCenter(0.f);
        vec3<f32> up(0.f, 1.f, 0.f);

        Transform transform({2.f}, {0.f, 0.f, 30.f}, {1.f});
        mesh = new Mesh(shader, transform);

        mLogger->LogTrace("Renderer initialized");
        mLogger->LogTrace((const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        delete mesh;
        delete shader;
        delete texture;
        delete mCamera;

        mLogger->LogTrace("Renderer shutdown");
    }

    void GLRenderer::BeginFrame()
    {
        CheckCanvasResize();

        ClearScreen();

        mCamera->Update(sDelta);

        // Switch geometry display mode on input
        if(mInput->IsKeyPressed(Key::W))
            mPolygonMode = !mPolygonMode;

        if(mInput->IsKeyPressed(Key::R))
        {
            shader->Reload();
            mLogger->LogTrace("Shaders reloaded");
        }
    }

    void GLRenderer::DrawFrame(f64 deltaTime)
    {
        sDelta = deltaTime;

        // Geometry diplay mode
        if(mPolygonMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        shader->Use();
        shader->SetUniform("view", mCamera->GetViewMatrix().Data());
        shader->SetUniform("projection", projection.Data());

        mesh->Draw();
    }

    void GLRenderer::EndFrame()
    {
        mWindow->SwapWindowBuffers();

        mCanvasCurrentWidth = mWindow->GetWidth();
        mCanvasCurrentHeight = mWindow->GetHeight();
    }

    void GLRenderer::ClearScreen()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderer::CheckCanvasResize()
    {
        // Check if the viewport is not the same size as the window
        if(mCanvasCurrentWidth != mWindow->GetWidth() || mCanvasCurrentHeight != mWindow->GetHeight())
            mResizeViewport = true;

        if(mResizeViewport)
        {
            glViewport(0, 0, mWindow->GetWidth(), mWindow->GetHeight());
            mResizeViewport = false;
        }
    }
}
