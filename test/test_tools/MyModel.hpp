#pragma once
#ifndef MY_MODEL_HPP
#define MY_MODEL_HPP
#include <MyMesh.hpp>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Info.hpp>

class MyModel
{
public:
    MyModel(const char *path)
    {
        loadModel(path);
    }
    void loadModel(const char *path);
    void processNode(aiNode *node, const aiScene *scene);
    MyMesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string _typename);
    void draw(MyShader &shader);

private:
    std::vector<MyMesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string directory;
    std::string getFullPath(const std::string &dir, const std::string &path)
    {
        if (dir.empty())
            return path;
        char last = dir.back();
        if (last != '/' && last != '\\')
        {
           return dir + "/" + path;
        }
        return dir + path;
    }
};

#endif