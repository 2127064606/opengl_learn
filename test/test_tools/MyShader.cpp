#include <MyShader.hpp>


std::string MyShader::read_from_shader_file(const char* shader_path){
    std::string shader_res;
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        shader_file.open(shader_path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_res = shader_stream.str();
        shader_file.close();
    }catch(std::ifstream::failure& e){
        std::cout << "读取shader文件失败" << std::endl;
    }
   // std::cout<< shader_res << std::endl;
    return shader_res;
}

MyShader::MyShader(const char* vertex_path, const char* fragment_path){
    std::string v_shader_sr = read_from_shader_file(vertex_path).c_str();
    std::string f_shader_sr = read_from_shader_file(fragment_path).c_str();
    const char* v_shader_sr_c = v_shader_sr.c_str();
    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, &v_shader_sr_c, NULL);
    glCompileShader(v_shader);
    int success;
    char info_log[512];
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(v_shader, 512, NULL, info_log);
        std::cout << "编译顶点shader失败" << info_log << std::endl;
    }
    unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f_shader_sr_c = f_shader_sr.c_str();
    glShaderSource(f_shader, 1, &f_shader_sr_c, NULL);
    glCompileShader(f_shader);
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(f_shader, 512, NULL, info_log);
        std::cout << "编译片段shader失败" << info_log << std::endl;
    }
    id = glCreateProgram();
    glAttachShader(id, v_shader);
    glAttachShader(id, f_shader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(id, 512, NULL, info_log);
        std::cout << "链接shader程序失败" << info_log << std::endl;
    }
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);
}


void MyShader::use(){
    glUseProgram(id);
}

void MyShader::setInt(const std::string& name, int value){
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void MyShader::setFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void MyShader::setBool(const std::string& name, bool value){
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void MyShader::setVec3(const std::string& name, glm::vec3 value){
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}
void MyShader::setMat4(const std::string& name, glm::mat4 value){
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void MyShader::setFloat3(const std::string& name, float x, float y, float z){
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
