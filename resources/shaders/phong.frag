#version 330 core

in vec3 fNormal;
in vec3 fPosition;
in vec2 fTexCoord;

// Model
uniform vec3 albedo;
uniform sampler2D diffuseTexture;

// Light
uniform vec3 lightColor;
uniform vec3 lightPos;

// Camera
uniform vec3 viewPos;

out vec4 fColor;

void main()
{
    // Ambient
    float ambientStrength = 0.4;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(lightPos - fPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 2.0;
    vec3 viewDir = normalize(viewPos - fPosition);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128.0);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * albedo;

    fColor = texture(diffuseTexture, fTexCoord) * vec4(result, 1.f);
}
