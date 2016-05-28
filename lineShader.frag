#version 330 core

// This is a sample fragment shader.
//in vec3 fragVert;

out vec4 finalColor;

uniform int type;

void main() {
    if(type == 0){ finalColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); }
    else{ finalColor = vec4(1.0f, 1.0f, 0.0f, 1.0f); }
}
