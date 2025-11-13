#pragma once
#ifndef MY_SHADER_HPP
#define MY_SHADER_HPP
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class MyShader
{
    public:
        unsigned int id;
        MyShader(const char* vertex_path, const char* fragment_path);
        void use();
        std::string read_from_shader_file(const char* shader_path);
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void setBool(const std::string& name, bool value);
        void setVec3(const std::string& name, glm::vec3 value);
        void setMat4(const std::string& name, glm::mat4 value);
        void setFloat3(const std::string& name, float x, float y, float z);
};

#endif