#pragma once
#ifndef MODEL_HPP
#define MODEL_HPP
#include <Mesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Model{
    public:
        Model(const char* path){
            loadModel(path);
        }
        void Draw(Shader& shader){
            for(unsigned int i = 0; i < meshes.size(); i++)
                meshes[i].Draw(shader);
        }
    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> loadedTextures;
        std::string directory;
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string _typename);
};

std::string getFullPath(const std::string& dir, const std::string& file);
#endif