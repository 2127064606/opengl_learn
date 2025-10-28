#version 330 core
out vec4 fragColor;
in vec3 outColor;
in vec4 outPos;
in vec2 outTexPos;
uniform sampler2D texture1;



void main(){
    fragColor = texture(texture1, outTexPos) * vec4(outColor, 1.0);
}