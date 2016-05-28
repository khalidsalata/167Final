#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec4 position;

uniform mat4 MVP;
uniform mat4 model;

void main() {
    // Apply all matrix transformations to vert
    gl_Position = MVP * vec4(vec3(position), 1.0f);
}

