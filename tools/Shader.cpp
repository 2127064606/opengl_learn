#include "Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexSource;
    std::string fragmentSource;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStrem,fShaderStrem;
        vShaderStrem << vShaderFile.rdbuf();
        fShaderStrem << fShaderFile.rdbuf();
        //关闭文件
        vShaderFile.close();
        fShaderFile.close();
        //转换为C字符串
        vertexSource = vShaderStrem.str();
        fragmentSource = fShaderStrem.str();
    }catch(std::ifstream::failure e){
        std::cout << "ERROR::SHADER::FILE_COULD_NOT_BE_READ" << std::endl;
    }

    //编译着色器
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* vertexSourcePtr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourcePtr, NULL);
    glCompileShader(vertexShader);
    int success;
    char info_log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }else{
        std::cout << "VERTEX SHADER COMPILE SUCCESS" << std::endl;
    }
    const char* fragmentSourcePtr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourcePtr, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }else{
        std::cout << "FRAGMENT SHADER COMPILE SUCCESS" << std::endl;
    }
    //链接着色器程序
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }else{
        std::cout << "SHADER PROGRAM LINK SUCCESS" << std::endl;
    }
    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value)const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value)const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()),value);
}

void Shader::setFloat(const std::string& name, float value)const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()),value);
}