#pragma once
#ifndef MY_MESH_HPP
#define MY_MESH_HPP
#include <glad/glad.h>
#include <stb_image.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <MyShader.hpp>
#include <string>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};


struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
    unsigned int loadTexture(const char* path){
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if(!data){
            std::cout << "加载纹理失败" << std::endl;
            return -1;
        }
        GLenum format;
        if(nrChannels == 1){
            format = GL_RED;
        }else if(nrChannels == 3){
            format = GL_RGB;
        }else if(nrChannels == 4){
            format = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return id;
    }  
};

class MyMesh{
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int vao, vbo, ebo;
        MyMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            setupMesh();
        }
        void draw(MyShader& shader);
    private:
        void setupMesh();
};

#endif