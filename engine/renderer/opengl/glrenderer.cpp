#include <renderer/opengl/glrenderer.hpp>
#include <renderer/opengl/vertex_array.hpp>

#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

std::vector<f32> vertices = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
std::vector<u32> indices = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

u32 vShader;
u32 fShader;
u32 program;

namespace Mnemos
{
    VertexArray* vao;

    bool GLRenderer::Init(const SubsystemInitInfo& info)
    {
        // Get the renderer configuration from init info
        const auto* rendererConfig = dynamic_cast<const RendererInitInfo*>(&info);
        mLogger = rendererConfig->logger;
        mWindow = rendererConfig->window;

        // Setup OpenGL properties
        //glEnable(GL_DEPTH_TEST);

        vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vShader);

        fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fShader);

        program = glCreateProgram();
        glAttachShader(program, vShader);
        glAttachShader(program, fShader);
        glLinkProgram(program);

        vao = new VertexArray(indices, vertices);

        mLogger->LogTrace("Renderer initialized");
        mLogger->LogTrace((const char*)glGetString(GL_VERSION));

        return true;
    }

    void GLRenderer::Shutdown()
    {
        glDeleteProgram(program);

        delete vao;

        mLogger->LogTrace("Renderer shutdown");
    }

    void GLRenderer::BeginFrame()
    {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderer::DrawFrame()
    {
        glUseProgram(program);
        vao->Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

    void GLRenderer::EndFrame()
    {
        mWindow->SwapWindowBuffers();

        vao->Unbind();
    }
}
