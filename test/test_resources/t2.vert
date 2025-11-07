#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1)in vec3 normalPos;
layout (location = 2) in vec2 vTexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

out vec3 outNormalPos;
out vec3 FragPos;
void main(){
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    FragPos = vec3(model * vec4(vPos, 1.0));
    // 计算法线矩阵, 用于将法线从局部空间转换到世界空间
    outNormalPos = mat3(transpose(inverse(model))) * normalPos;
    // 计算纹理坐标
    TexCoord = vTexCoord;
}