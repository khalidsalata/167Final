#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;

// Output data ; will be interpolated for each fragment.
out vec4 ShadowCoord;
out vec3 fragVert;
out vec3 fragNormal;
out vec2 texCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 depthBiasMVP;
uniform mat4 model;
uniform mat4 invModel;

void main(){
    
    fragNormal = mat3(transpose(invModel)) * vertNormal;
    fragVert = vec3(model * vec4(position, 1.0f));
    
    ShadowCoord = depthBiasMVP * vec4(position, 1.0f);
    
    vec2 temp = vec2((position.x + 10.0f) / 20.0f, (position.z + 10.0f) / 20.0f);
    
    texCoord = temp;
    
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(position, 1.0f);
    
    
    
    
}