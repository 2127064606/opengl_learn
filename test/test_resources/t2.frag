#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 viewPos;
uniform float specularStrength;
uniform vec3 lightPos;
in vec3 outNormalPos;
in vec3 FragPos;

struct Material {
    vec3 ambient;//环境光
    vec3 diffuse;//漫反射
    vec3 specular;//镜面反射
    float shininess;//高光指数(镜面)
};
uniform Material material;

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;
void main()
{
    
   vec3 ambient = light.ambient * material.ambient;
   vec3 norm = normalize(outNormalPos);
   vec3 lightDir = normalize(light.position - FragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * diff * material.diffuse;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * spec * material.specular;
   FragColor = vec4(ambient + diffuse + specular, 1.0);
}