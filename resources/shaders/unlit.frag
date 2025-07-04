#version 330 core

in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoord;

uniform sampler2D diffuse;
uniform vec3 albedo;

out vec4 fColor;

void main()
{
    fColor = vec4(fNormal, 1.f);
}
