#pragma once

#include <math/matrix.hpp>
#include <renderer/opengl/mesh.hpp>
#include <renderer/material/material.hpp>

namespace Mnemos
{
    struct Renderable
    {
        Mesh* mesh;
        Material* material;
        mat4<f32> transform;
    };
}
