#pragma once

#include <renderer/renderable.hpp>
#include <renderer/material/material_factory.hpp>

namespace Mnemos::AssetLoader
{
    Renderable* LoadOBJ(const std::string& path);
}
