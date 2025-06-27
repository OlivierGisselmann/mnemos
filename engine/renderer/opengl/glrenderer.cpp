#include <renderer/opengl/glrenderer.hpp>

static f64 sDelta = 0;

namespace Mnemos
{
    Renderable* cube = nullptr;
    static f32 angle = 0.f;

    // Lighting
    static const vec3<f32> lightColor {1.f};
    static const vec3<f32> lightPos {3.f};

    bool GLRenderer::Init(const SubsystemInitInfo& info)
    {
        // Get the renderer configuration from init info
        const auto* rendererConfig = dynamic_cast<const RendererInitInfo*>(&info);
        mInput = rendererConfig->input;
        mWindow = rendererConfig->window;

        // Enable debug output
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        // Setup OpenGL properties
        glEnable(GL_DEPTH_TEST);

        // Camera
        mCamera = new Camera(mInput, {0.f, 0.f, -3.f});
        projection = Perspective(55.0f, ((f32)mWindow->GetWidth() / (f32)mWindow->GetHeight()), 0.01f, 100.0f);

        // Model
        cube = AssetLoader::LoadOBJ("resources/models/apples.obj");

        LOG(LogLevel::INFO, "Renderer initialized");
        LOG(LogLevel::INFO, (const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        delete mCamera;
        delete cube;

        LOG(LogLevel::INFO, "Renderer shutdown");
    }

    void GLRenderer::BeginFrame()
    {
        CheckCanvasResize();

        ClearScreen();

        // Switch geometry display mode on input
        if(mInput->IsKeyPressed(Key::W))
            mPolygonMode = !mPolygonMode;

        if(mInput->IsKeyPressed(Key::R))
        {
            // TODO - Add shader hot reload
            //cube->material->shader->Reload();
            LOG(LogLevel::INFO, "Shaders reloaded");
        }

        mCamera->Update(sDelta);
    }

    void GLRenderer::DrawFrame(f64 deltaTime)
    {
        sDelta = deltaTime;
        angle += deltaTime * 5.f;

        // Geometry diplay mode
        if(mPolygonMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        cube->transform = RotateY(cube->transform, angle);

        Submit(*cube);
    }

    void GLRenderer::EndFrame()
    {
        mWindow->SwapWindowBuffers();

        mCanvasCurrentWidth = mWindow->GetWidth();
        mCanvasCurrentHeight = mWindow->GetHeight();
    }

    void GLRenderer::ClearScreen()
    {
        glClearColor(0.617f, 0.715f, 0.895f, 1.0f);
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

    void GLRenderer::Submit(const Renderable& renderable)
    {
        renderable.material->Bind();
        renderable.material->shader->SetUniform("model", renderable.transform.Data());
        renderable.material->shader->SetUniform("view", mCamera->GetViewMatrix().Data());
        renderable.material->shader->SetUniform("projection", projection.Data());

        renderable.material->shader->SetUniform("viewPos", mCamera->GetPosition());
        renderable.material->shader->SetUniform("lightColor", lightColor);
        renderable.material->shader->SetUniform("lightPos", lightPos);

        renderable.mesh->Bind();
        glDrawElements(GL_TRIANGLES, renderable.mesh->GetIndexCount(), GL_UNSIGNED_INT, nullptr);
        renderable.mesh->Unbind();
    }
}
