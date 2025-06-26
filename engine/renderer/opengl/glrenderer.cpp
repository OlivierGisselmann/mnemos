#include <renderer/opengl/glrenderer.hpp>

#include <core/parsers/obj_parser.hpp>

static f64 sDelta = 0;

namespace Mnemos
{
    Shader* shader;
    Mesh mesh;

    bool GLRenderer::Init(const SubsystemInitInfo& info)
    {
        // Get the renderer configuration from init info
        const auto* rendererConfig = dynamic_cast<const RendererInitInfo*>(&info);
        mInput = rendererConfig->input;
        mWindow = rendererConfig->window;

        LoadOBJ("resources/models/cube.obj");

        // Enable debug output
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        // Setup OpenGL properties
        glEnable(GL_DEPTH_TEST);

        // Load resources
        shader = new Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");

        // Camera
        mCamera = new Camera(mInput, {0.f, 0.f, -3.f});
        projection = Perspective(55.0f, ((f32)mWindow->GetWidth() / (f32)mWindow->GetHeight()), 0.1f, 100.0f);

        // Mesh & material
        Phong phong = {{0.f, 0.f, 1.f}, {0.f, 1.f, 0.f}, 128.f};
        PhongMaterial mat(*shader, phong);
        Transform t = {{0.f}, {0.f}, {1.f}};
        mesh = LoadOBJ("resources/models/cube.obj");
        mesh.SetTransform(t);
        mesh.SetMaterial(&mat);

        // Lighting
        vec3<f32> lightPosition {0.f, 2.f, 0.f};
        shader->Use();
        shader->SetUniform("lightPos", lightPosition);

        LOG(LogLevel::INFO, "Renderer initialized");
        LOG(LogLevel::INFO, (const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        //delete mesh;
        delete shader;
        delete mCamera;

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
            shader->Reload();
            LOG(LogLevel::INFO, "Shaders reloaded");
        }

        mCamera->Update(sDelta);
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

        //mesh->Draw();
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
}
