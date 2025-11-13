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
in vec2 TexCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;//镜面反射
    float shininess;//高光指数(镜面)
};
uniform Material material;

//点光源
struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    // 衰减系数
    float constant;
    float linear;
    float quadratic;
};
uniform Light light[4];

//平行光
struct ParallelLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform ParallelLight parallelLight;

//聚光灯
struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform SpotLight spotLight;

vec3 calculatePointLightRes(Light light, vec3 norm, vec3 lightDir){
    //计算环境光分量
    vec3 amibent = light.ambient * vec3(texture(material.diffuse, TexCoord));
    //计算漫反射分量
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    //计算镜面反射分量
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));

    //计算衰减系数
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // 应用衰减系数
    amibent *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (amibent + diffuse + specular);
}

vec3 calculateParallelLightRes(ParallelLight parallelLight, vec3 norm, vec3 parallelLightDir){
    //计算环境光分量
    vec3 amibent = parallelLight.ambient * vec3(texture(material.diffuse, TexCoord));
    //计算漫反射分量
    float diff = max(dot(norm, parallelLightDir), 0.0);
    vec3 diffuse = parallelLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    //计算镜面反射分量
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-parallelLightDir, norm);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = parallelLight.specular * spec * vec3(texture(material.specular, TexCoord));
    return (amibent + diffuse + specular);
}

vec3 calculateSpotLightRes(SpotLight spotLight, vec3 norm, vec3 spotLightDir){
    //计算环境光分量
    vec3 amibent = spotLight.ambient * vec3(texture(material.diffuse, TexCoord));
    //计算漫反射分量
    float diff = max(dot(norm, spotLightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(material.diffuse, TexCoord));
    //计算镜面反射分量
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-spotLightDir, norm);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * vec3(texture(material.specular, TexCoord));

    //计算作用范围及强度因子
    float theta = dot(spotLightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    // 应用强度因子
    amibent *= intensity;
    diffuse *= intensity;
    specular *= intensity;
    
    return (amibent + diffuse + specular);
}
void main()
{
    
   vec3 res = vec3(0.0); 
   for(int i = 0; i < 4; i++){
         vec3 lightDir = normalize(light[i].position - FragPos);
       res += calculatePointLightRes(light[i], outNormalPos, lightDir);
   }
   vec3 parallelLightDir = normalize(-parallelLight.direction);
   res += calculateParallelLightRes(parallelLight, outNormalPos, parallelLightDir);
   vec3 spotLightDir = normalize(spotLight.position - FragPos);
   res += calculateSpotLightRes(spotLight, outNormalPos, spotLightDir);
   FragColor = vec4(res, 1.0);
}