#version 330 core

// This is a sample fragment shader.

in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main() {
    vec3 I = normalize(fragVert - cameraPos);
    vec3 R = reflect(I, normalize(fragNormal));
    finalColor = texture(skybox, R);
    
}
