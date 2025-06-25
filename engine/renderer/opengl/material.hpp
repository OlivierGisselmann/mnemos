#pragma once

#include <renderer/opengl/shader.hpp>
#include <renderer/opengl/texture.hpp>

#include <vector>

namespace Mnemos
{
    struct Phong
    {
        vec3<f32> ambient;
        vec3<f32> diffuse;
        f32 specular;
    };

    class IMaterial
    {
    public:
        virtual void Use() = 0;
        virtual ~IMaterial() = default;
    };

    class  PhongMaterial : public IMaterial
    {
    public:
        PhongMaterial(Shader& shader, const Phong& phong);
        ~PhongMaterial() override;
        void Use() override;

    private:
        Phong mValues;
        Shader& mShader;
    };
}
