#pragma once

#include <core/filesystem/resource_manager.hpp>
#include <math/matrix.hpp>
#include <platform/types.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    class Shader
    {
    public:
        Shader(const std::string vertexShaderPath, const std::string fragmentShaderPath);
        ~Shader();

        void Use();
        void Reload();

        template<typename T>
        void SetUniform(const std::string& name, T value);

    private:
        void Create();
        void LoadShader(ShaderType type);
        void CheckErrors(ShaderType type, u32 id);

        u32 mID;
        u32 mVertex, mFragment;

        const char* vCode;
        const char* fCode;
        std::string vPath;
        std::string fPath;
        std::string vFileContent;
        std::string fFileContent;
    };
}
