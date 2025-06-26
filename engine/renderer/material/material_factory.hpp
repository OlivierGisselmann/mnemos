#pragma once

#include <renderer/material/material.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>

namespace Mnemos
{
    class MaterialFactory
    {
    public:
        static Material* CreateDefault();
    };
}
