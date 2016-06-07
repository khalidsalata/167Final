#version 330 core
out vec4 color;
in vec2 TexCoords;

uniform sampler2D depthMap;

void main()
{
    float Depth = texture(depthMap, TexCoords).x;
    Depth = 1.0 - (1.0 - Depth) * 25.0;
    color = vec4(Depth);
}