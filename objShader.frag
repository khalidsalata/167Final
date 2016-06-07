#version 330 core

// This is a sample fragment shader.

in vec2 texCoord;
in vec3 fragVert;
in vec3 fragNormal;

out vec4 finalColor;

uniform sampler2D refMap;
uniform samplerCube skybox;
uniform vec3 cameraPos;

void main() {
    vec3 I = normalize(fragVert - cameraPos);
    I.y = -I.y;
    vec3 R = reflect(I, normalize(fragNormal));
    vec4 f = texture(skybox, R);
//    vec4 f = vec4(1.0f);
    
    finalColor = texture(refMap, texCoord);
    finalColor = f * finalColor * vec4(0.0f, 0.75f, 0.75f, 0.0f);
}
