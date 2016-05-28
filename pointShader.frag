#version 330 core

// This is a sample fragment shader.
flat in float index;

out vec4 finalColor;


void main() {
    if(index == 0.0f){ finalColor = vec4(0.0f, 0.0f, 1.0f, 1.0f); }
    else{ finalColor = vec4(0.0f, 1.0f, 0.0f, 1.0f); }
     
}
