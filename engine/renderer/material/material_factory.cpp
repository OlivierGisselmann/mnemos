#include <renderer/material/material_factory.hpp>

namespace Mnemos
{
    Material* MaterialFactory::CreateDefault()
    {
        Shader* shader = new Shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");
        Texture* texture = new Texture("resources/textures/checker.png");

        Material* mat = new Material();
        mat->shader = shader;
        mat->diffuse = texture;
        mat->albedo = vec3<f32>(1.f, 0.f, 1.f);

        return mat;
    }
}
