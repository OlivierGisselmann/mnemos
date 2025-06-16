#pragma once

#include <core/filesystem/filesystem.hpp>
#include <platform/types.hpp>

#include <glad/glad.h>

#include <iostream>

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
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        ~Shader();

        void Use();

    private:
        void LoadShader(ShaderType type, const char* path);
        void CheckErrors(ShaderType type, u32 id);

        u32 mID;
        u32 mVertex, mFragment;

        const char* vCode;
        const char* fCode;

        std::string vFileContent;
        std::string fFileContent;
    };
}
