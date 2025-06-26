#pragma once

#include <math/vector.hpp>

namespace Mnemos
{
    struct Transform
    {
        vec3<f32> position;
        vec3<f32> rotation;
        vec3<f32> scale;
    };
}
