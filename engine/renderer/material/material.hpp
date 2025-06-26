#pragma once

#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>

#include <vector>

namespace Mnemos
{
    struct Material
    {
        Shader* shader;
        Texture* diffuse;
        vec3<f32> albedo;

        void Bind() const;
    };
}
