#include <core/parsers/asset_loader.hpp>

namespace Mnemos
{
    Renderable* AssetLoader::LoadOBJ(const std::string& path)
    {
        const Vertex vertices[] = {
        {{-0.5f, -0.5f, 0.0f}, {0.f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {0.f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.f}, {0.0f, 1.0f}}
        };

        const u32 indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        Mesh* mesh = new Mesh(vertices, sizeof(Vertex), 4, indices, 6);
        Material* material = MaterialFactory::CreateDefault();

        return new Renderable {mesh, material, mat4<f32>(1.0f)};
    }
}
