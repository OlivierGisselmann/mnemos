#include <renderer/material/material_factory.hpp>

namespace Mnemos
{
    Material* MaterialFactory::CreateDefault()
    {
        Shader* shader = new Shader("resources/shaders/shader.vert", "resources/shaders/phong.frag");
        Texture* texture = new Texture("resources/textures/apple2_diffuse.jpg");

        Material* mat = new Material();
        mat->shader = shader;
        mat->diffuse = texture;
        mat->albedo = vec3<f32>(1.f, 0.5f, 0.3f);

        return mat;
    }
}
