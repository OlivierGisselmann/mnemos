#include <renderer/opengl/glrenderer.hpp>

std::vector<f32> vertices
{
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

std::vector<u32> indices {  // note that we start from 0!
    0,1,3,
    3,1,2,
    4,5,7,
    7,5,6,
    8,9,11,
    11,9,10,
    12,13,15,
    15,13,14,
    16,17,19,
    19,17,18,
    20,21,23,
    23,21,22
};

static f64 sDelta = 0;

namespace Mnemos
{
    VertexArray* vao;
    Texture* texture;
    Shader* shader;

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

        texture = new Texture("resources/textures/checker.png");

        vao = new VertexArray(indices, vertices);

        mLogger->LogTrace("Renderer initialized");
        mLogger->LogTrace((const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        delete vao;
        delete shader;

        mLogger->LogTrace("Renderer shutdown");
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
        
        DrawIndexed(shader, vao);
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

    void GLRenderer::DrawIndexed(Shader* shader, VertexArray* vao)
    {
        shader->Use();
        vao->Bind();
        texture->Bind();

        view = Translate(view, {0.f, 0., -3.f});

        projection = Perspective(55.0f, ((f32)mWindow->GetWidth() / (f32)mWindow->GetHeight()), 0.1f, 100.0f);
        
        angle += sDelta * 15.0f;
        model = Rotate(model, angle, {3.f, -1.f, 1.f});
        model = Translate(model, {0.f, 0.f, 0.f});

        shader->SetUniform("model", model.Data());
        shader->SetUniform("view", view.Data());
        shader->SetUniform("projection", projection.Data());

        //glDrawElements(GL_TRIANGLES, vao.GetIndicesSize(), GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        vao->Unbind();
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
