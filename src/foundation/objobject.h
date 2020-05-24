#pragma once

#include <vector>
#include <string.h>
#include <map>
#include <memory>
#include "gl_headers.h"
#include "gltypes.h"
#include "texture.h"
#include "objloader.h"

class Shader;

class VAO_mesh
{
public:
    VAO_mesh(objl::Mesh& mesh, GameData& gamedata);
    ~VAO_mesh() = default;
    void draw(Shader& shader);
    std::string name;
private:
    GLuint VAO, VBO, EBO;
    int m_numindices;
    void init(objl::Mesh& mesh);
    void enable_textures();
    objl::Material m_material;
    std::map<int, std::shared_ptr<Texture>> map_ptrs;
    vector<bool> use_maps;
    
    /*map_Ka_ptr -->GL_TEXTURE0
    map_Kd_ptr = nullptr; GL_TEXTURE1
    map_Ks_ptr = nullptr; GL_TEXTURE2
    map_Ns_ptr = nullptr;GL_TEXTURE3
    map_d_ptr = nullptr; GL_TEXTURE4
    map_bump_ptr = nullptr; GL_TEXTURE5*/
};

class objobject
{
public:
    objobject() = delete;
    objobject(objl::Loader& loader, const std::string name, GameData& gamedata);
    ~objobject();
    void virtual draw(Shader& shaderprogram, glm::mat4& view, glm::mat4& project);
    std::string m_name;
    glm::mat4 m_model;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    
protected:
    std::vector<VAO_mesh> vao_meshes;
    void virtual set_model_mat();
    void set_matrices(Shader& shaderprogram, glm::mat4& view, glm::mat4& project);
};
