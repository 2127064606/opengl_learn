#version 330 core
layout (location = 0)in vec3 aPos;
layout (location = 1)in vec3 aColor;
uniform float offsetx = 0.0;
out vec3 outColor;
out vec4 outPos;
void main(){
    gl_Position = vec4(aPos.x + offsetx, aPos.y, aPos.z, 1.0);
    outPos = gl_Position;
    outColor = aColor;
}