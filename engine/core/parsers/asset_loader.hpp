#pragma once

#include <core/logging/logger_manager.hpp>
#include <renderer/renderable.hpp>
#include <renderer/material/material_factory.hpp>

#include <vector>

namespace Mnemos::AssetLoader
{
    Renderable* LoadOBJ(const std::string& path);
}
