#include <renderer/opengl/shader.hpp>

namespace Mnemos
{
    Shader::Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath)
    : vPath(vertexShaderPath), fPath(fragmentShaderPath)
    {
        Create();
    }

    Shader::~Shader()
    {
        glDeleteProgram(mID);
    }

    void Shader::Create()
    {
        // Load shader contents
        LoadShader(ShaderType::VERTEX);
        LoadShader(ShaderType::FRAGMENT);

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

    void Shader::Reload()
    {
        Create();
    }

    void Shader::Bind() const
    {
        glUseProgram(mID);
    }

    template<>
    void Shader::SetUniform(const std::string& name, i32 value)
    {
        glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
    }

    template<>
    void Shader::SetUniform(const std::string& name, f32 value)
    {
        glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
    }

    template<>
    void Shader::SetUniform(const std::string& name, vec3<f32> vec)
    {
        glUniform3f(glGetUniformLocation(mID, name.c_str()), vec.x, vec.y, vec.z);
    }

    template<>
    void Shader::SetUniform(const std::string& name, const f32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, matrix);
    }

    template<>
    void Shader::SetUniform(const std::string& name, f32* matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, matrix);
    }

    void Shader::LoadShader(ShaderType type)
    {
        switch (type)
        {
        case ShaderType::VERTEX:
        {
            // Read file into string and get pointer to it
            vFileContent = ResourceManager::Get().ReadTextFile(vPath);
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
            fFileContent = ResourceManager::Get().ReadTextFile(fPath);
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
