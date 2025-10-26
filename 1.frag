#version 330 core
out vec4 fragColor;
in vec3 outColor;
in vec4 outPos;

void main(){
    fragColor = vec4(outPos);
}