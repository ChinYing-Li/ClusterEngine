#pragma once

#include <vector>
#include <string.h>
#include <map>
#include <memory>
#include "includes/gl_headers.h"
#include "src/gltypes.h"
#include "src/foundation/texture.h"
namespace objl
{
class Loader;
class Material;
class Mesh;
}

class Shader;

class VAO_mesh
{
public:
    VAO_mesh(objl::Mesh& mesh, GameData& gamedata);
    ~VAO_mesh() = default;
    void draw(GLuint& shaderID);
    std::string name;
private:
    GLuint VAO, VBO, EBO;
    int m_numindices;
    void init(objl::Mesh& mesh);
    
    void draw_textures(GLuint shaderID);
    void set_material_uniform(GLuint& shaderID);
    
    objl::Material* m_material_ptr = nullptr;
    std::map<std::string, std::shared_ptr<Texture>> map_ptrs;
    std::vector<bool> use_maps;
    
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
    objobject() = default;
    objobject(objl::Loader& loader, const std::string name, GameData& gamedata);
    ~objobject();
    void virtual draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project);
    std::string m_name;
    glm::mat4 m_model;
    glm::mat4 m_project;
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    
protected:
    std::vector<VAO_mesh> vao_meshes;
    void virtual calc_model_mat();
    void set_matrices(GLuint& shaderID, glm::mat4& view, glm::mat4& project);
};
