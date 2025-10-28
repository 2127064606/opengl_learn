#version 330 core
layout (location = 0)in vec3 aPos;
layout (location = 1)in vec3 aColor;
layout (location = 2)in vec2 texPos;
uniform float offsetx = 0.0;
out vec3 outColor;
out vec4 outPos;
out vec2 outTexPos;
uniform mat4 transform;
void main(){
    gl_Position = transform * vec4(aPos, 1.0);
    outPos = gl_Position;
    outColor = aColor;
    outTexPos = texPos;
}