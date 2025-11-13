#pragma once
#ifndef MESH_HPP
#define MESH_HPP
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <stb_image.h>
#include <iostream>
#include <vector>
#include <Shader.hpp>
struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
    static unsigned int loadTexture(const char* path){
        unsigned int id;
        GLenum format;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        int width, height, nrChannels;
        //stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if(!data){
            std::cout << "Failed to load texture" << std::endl;
            return 0;
        }
        if(nrChannels == 3){
            format = GL_RGB;
        }else if(nrChannels == 4){
            format = GL_RGBA;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return id;
    }
};


class Mesh{
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int vao, vbo, ebo;
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            setupMesh();
        }
        
        void Draw(Shader& shader);
        private:
            void setupMesh();
};




#endif