#include <iostream>

#include "stbi_header.h"

#include "model.h"
#include "mesh.h"

Model::Model(const std::string path_to_model)
{
    load(path_to_model);
}

void Model::load(const std::string path_to_model)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path_to_model, aiProcess_Triangulate);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << (scene == nullptr) << std::endl;
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    m_directory = path_to_model.substr(0, path_to_model.find_last_of('/'));
    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene *scene)
{
    for(std::size_t i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(process_mesh(mesh, scene));
    }
    for(std::size_t i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene);
    }
    return;
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTex> textures;
    
    for(std::size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex v;
        v.m_position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        v.m_normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        
        if(mesh->mTextureCoords[0])
        {
            //std::cout << "has texture coords " << std::endl;
            v.m_texcoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else
        {
            v.m_texcoords = glm::vec2(0.0f);
        }
        vertices.push_back(v);
    }
    
    for(std::size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for(std::size_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[i]);
        }
    }
    
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<MeshTex> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<MeshTex> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<MeshTex> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<MeshTex> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
       
    return Mesh(vertices, textures, indices);
}

void Model::draw(glm::mat4& VP, GLuint shaderID, GLMatrices& mat)
{
    glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::translate (m_center);    // glTranslatef
    glm::mat4 translate = glm::translate (glm::vec3(0.0f, 0.0, 0.1f));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0,1 ));
    glUseProgram(shaderID);
    model *= (translate * rotate);
    glm::mat4 MVP = VP * mat.model; // ???
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //std::cout << m_meshes.size() << std::endl;
    for(size_t i = 0; i < m_meshes.size(); ++i)
    {
        m_meshes[i].draw(shaderID);
        //std::cout << "drawing model" << std::endl;
    }
    return;
}

std::vector<MeshTex> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string typeName)
{
    std::cout << typeName << std::endl;
    std::vector<MeshTex> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        std::cout << str.C_Str() << std::endl;
        bool skip = false;
        for(unsigned int j = 0; j < m_loaded_texture.size(); j++)
        {
            
            if(std::strcmp(m_loaded_texture[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(m_loaded_texture[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            std::cout << "loading texture" << std::endl;
            MeshTex texture;
            texture.ID = TextureFromFile(str.C_Str(), this->m_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_loaded_texture.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
