#version 330 core
out vec4 FragColor;
//in vec3 outColor;
in vec2 outTexCoord;
//uniform sampler2D texture1;
in vec3 outNormal;
in vec3 FragPos;
uniform vec3 viewPos;
uniform sampler2D diffuse1;
//uniform sampler2D texture_diffuse1;

struct Material{
   sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLight;

struct ParralLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform ParralLight parralLight;

struct SpotLight{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

uniform SpotLight spotLight;


vec3 calculatePointLightRes(PointLight light){
    vec3 amibent = light.ambient * vec3(texture(material.diffuse, outTexCoord));
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(outNormal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTexCoord));
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-lightDir, outNormal);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTexCoord));
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    amibent *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (amibent + diffuse + specular);
}

vec3 calculateParralLightRes(ParralLight light){
    vec3 amibent = light.ambient * vec3(texture(material.diffuse, outTexCoord));
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(outNormal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTexCoord));
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-lightDir, outNormal);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTexCoord));
    return (amibent + diffuse + specular);
}

vec3 calculateSpotLightRes(SpotLight light){
    vec3 amibent = light.ambient * vec3(texture(material.diffuse, outTexCoord));
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(outNormal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTexCoord));
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 relectDir = reflect(-lightDir, outNormal);
    float spec = pow(max(dot(viewDir, relectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, outTexCoord));
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    amibent *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    return (amibent + diffuse + specular) * intensity;
}

void main(){
   FragColor = texture(diffuse1, outTexCoord);
}