#pragma once

#include <math/matrix.hpp>
#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>
#include <renderer/opengl/vertex_array.hpp>

namespace Mnemos
{
    struct Transform
    {
        vec3<f32> position;
        vec3<f32> rotation;
        vec3<f32> scale;
    };

    class Mesh
    {
    public:
        Mesh(Shader* shader, Transform transform);
        ~Mesh();

        void Draw();
        void LoadData(const std::vector<f32>& vertices, const std::vector<u32>& indices);

    private:
        Shader* mShader = nullptr;
        VertexArray* mVertexArray = nullptr;
        Texture* mTexture = nullptr;

        Transform mTransform;
        mat4<f32> mModel;
    };
}
