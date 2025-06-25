#include <renderer/opengl/material.hpp>

namespace Mnemos
{
    // Phong Material
    PhongMaterial::PhongMaterial(Shader& shader, const Phong& phong) : mShader(shader), mValues(phong) {}
    PhongMaterial::~PhongMaterial() {}

    void PhongMaterial::Use()
    {
        mShader.Use();
        mShader.SetUniform("ambient", mValues.ambient);
        mShader.SetUniform("diffuse", mValues.diffuse);
        mShader.SetUniform("specular", mValues.specular);
    }

    // TODO - Other material types
}
