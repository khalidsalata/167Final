#version 330 core

// This is a sample fragment shader.

out vec4 finalColor;

uniform uint id;

void main() {
    
    finalColor = vec4(id/255.0f, 0.0f, 0.0f, 1.0f);
}
