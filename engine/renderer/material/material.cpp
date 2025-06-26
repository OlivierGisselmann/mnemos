#include <renderer/material/material.hpp>

namespace Mnemos
{
    void Material::Bind() const
    {
        shader->Bind();
        
        if(diffuse)
        {
            diffuse->Bind();
            shader->SetUniform("diffuse", 0);
        }

        shader->SetUniform("albedo", albedo);
    }
}
