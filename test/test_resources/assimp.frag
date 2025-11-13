#version 330 core
in vec2 outTexCoords;
out vec4 FragColor;
uniform sampler2D diffuse1;

void main(){
    FragColor = texture(diffuse1, outTexCoords);
}
