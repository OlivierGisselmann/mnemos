#include <renderer/opengl/glrenderer.hpp>

std::vector<f32> vertices {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

std::vector<u32> indices {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

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
        //glEnable(GL_DEPTH_TEST);

        shader = new Shader("/home/thanion/dev/graphics/mnemos/resources/shaders/shader.vert", "/home/thanion/dev/graphics/mnemos/resources/shaders/shader.frag");

        texture = new Texture("/home/thanion/dev/graphics/mnemos/resources/textures/brick.jpg");

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

    void GLRenderer::DrawFrame()
    {
        // Geometry diplay mode
        if(mPolygonMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        DrawIndexed(*shader, *vao);
    }

    void GLRenderer::EndFrame()
    {
        mWindow->SwapWindowBuffers();
    }

    void GLRenderer::ClearScreen()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderer::DrawIndexed(Shader& shader, VertexArray& vao)
    {
        shader.Use();
        vao.Bind();
        texture->Bind();

        glDrawElements(GL_TRIANGLES, vao.GetIndicesSize(), GL_UNSIGNED_INT, 0);

        vao.Unbind();
    }
}
