#version 330 core

in vec3 fragColor;
in vec2 texCoord;

uniform sampler2D text;

out vec4 fColor;

void main()
{
    fColor = texture(text, texCoord) * vec4(fragColor, 1.0f);
}
