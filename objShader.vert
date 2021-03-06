#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertNormal;

out vec2 texCoord;
out vec3 fragVert;
out vec3 fragNormal;

uniform mat4 MVP;
uniform mat4 model;
uniform mat4 invModel;
uniform mat4 depthBiasMVP;

void main() {
    fragNormal = mat3(transpose(invModel)) * vertNormal;
    fragVert = vec3(model * vec4(position, 1.0f));
    
    vec2 temp = vec2((position.x + 10.0f) / 20.0f, (position.z + 10.0f) / 20.0f);
    texCoord = temp;
        
    // Apply all matrix transformations to vert
    gl_Position = MVP * vec4(position, 1.0f);
    
    
}

