#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
//uniform uint id;

void main()
{
    gl_Position = Projection * View * Model * vec4(position.x, position.y, position.z, 1.0);
}
