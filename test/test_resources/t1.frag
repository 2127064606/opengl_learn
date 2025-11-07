#version 330 core
in vec3 outColor;
out vec4 FragColor;
in vec2 outTexCoord;

uniform sampler2D ourTexture;

void main(){
    FragColor = texture(ourTexture, outTexCoord);
}