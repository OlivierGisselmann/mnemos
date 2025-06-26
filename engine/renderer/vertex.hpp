#pragma once

#include <math/vector.hpp>

namespace Mnemos
{
    struct Vertex
    {
        vec3<f32> position;
        vec3<f32> normal;
        vec2<f32> texCoords;
    };
}
