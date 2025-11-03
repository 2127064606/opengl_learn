#version 330 core
struct Material {
    vec3 ambient;//环境光
    vec3 diffuse;//漫反射
    vec3 specular;//镜面反射
    float shininess;//高光指数(镜面)
};

uniform Material material;

void main(){
    
}
