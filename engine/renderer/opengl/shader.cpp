#include <renderer/opengl/shader.hpp>

namespace Mnemos
{
    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
    {
        // Load shader contents
        LoadShader(ShaderType::VERTEX, vertexShaderPath);
        LoadShader(ShaderType::FRAGMENT, fragmentShaderPath);

        // Create program and link shaders to it
        mID = glCreateProgram();
        glAttachShader(mID, mVertex);
        glAttachShader(mID, mFragment);
        glLinkProgram(mID);

        CheckErrors(ShaderType::PROGRAM, mID);

        // Delete useless shaders once linking done
        glDeleteShader(mVertex);
        glDeleteShader(mFragment);
    }

    Shader::~Shader()
    {
        glDeleteProgram(mID);
    }

    void Shader::Use()
    {
        glUseProgram(mID);
    }

    void Shader::LoadShader(ShaderType type, const char* path)
    {
        switch (type)
        {
        case ShaderType::VERTEX:
        {
            // Read file into string and get pointer to it
            vFileContent = ReadFile(path);
            vCode = vFileContent.c_str();

            // Create shader and compile its code
            mVertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(mVertex, 1, &vCode, nullptr);
            glCompileShader(mVertex);

            CheckErrors(ShaderType::VERTEX, mVertex);
            break;
        }
        case ShaderType::FRAGMENT:
        {
            // Read file into string and get pointer to it
            fFileContent = ReadFile(path);
            fCode = fFileContent.c_str();

            // Create shader and compile its code
            mFragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(mFragment, 1, &fCode, nullptr);
            glCompileShader(mFragment);

            CheckErrors(ShaderType::FRAGMENT, mFragment);
            break;
        }
        case ShaderType::PROGRAM:
        default:
            break;
        }
    }

    void Shader::CheckErrors(ShaderType type, u32 id)
    {
        int success;
        char log[512];

        switch (type)
        {
        case ShaderType::VERTEX:
        case ShaderType::FRAGMENT:
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(id, 512, nullptr, log);
                std::cout << log << '\n';
            }
            break;
        case ShaderType::PROGRAM:
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(id, 512, nullptr, log);
                std::cout << log << '\n';
            }
        default:
            break;
        }
    }
}
