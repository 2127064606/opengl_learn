#include <Model.hpp>


void Model::loadModel(std::string path){
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    std::cout << "模型加载成功" << std::endl;
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
    //处理当前节点的所有网格
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    //std::cout << "节点 " << node->mName.C_Str() << " 处理完成" << std::endl;
    //递归处理子节点
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene * scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    //处理顶点
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if(mesh->mTextureCoords[0]){
            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        vertices.push_back(vertex);
    }

    //处理索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    //处理材质
    if(mesh -> mMaterialIndex >= 0){
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        //获取漫反射纹理
        unsigned int diffuseCount = mat->GetTextureCount(aiTextureType_DIFFUSE);
        std::cout << "材质中漫反射纹理数量: " << diffuseCount << std::endl;
        //获取高光纹理
        unsigned int specularCount = mat->GetTextureCount(aiTextureType_SPECULAR);
        std::cout << "材质中高光纹理数量: " << specularCount << std::endl;

        std::vector<Texture> diffuseMap = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());
        std::vector<Texture> specularMap = loadMaterialTextures(mat, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMap.begin(), specularMap.end());
    }
    return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string _typename){
    std::vector<Texture> textures;
   // std::vector<Texture> loadedTextures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        //检查是否已经加载过该纹理
        bool found = false;
        for(unsigned int j = 0; j < loadedTextures.size(); j++){
            if(std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0){
                textures.push_back(loadedTextures[j]);
                found = true;
                break;
            }
        }
        if(!found){
            Texture texture;
            texture.id = Texture::loadTexture(getFullPath(directory, str.C_Str()).c_str());
            texture.type = _typename;
            texture.path = str.C_Str();
            textures.push_back(texture);
            std::cout << "加载纹理 " << str.C_Str() << " 成功" << std::endl;
            loadedTextures.push_back(texture);
        }
    }
    return textures;
}

std::string getFullPath(const std::string& dir, const std::string& file){
    if(dir.empty()) return file;
    char last = dir.back();
    if(last != '/' || last != '\\'){
        return dir + "/" + file;
    }
    return dir + file;
}