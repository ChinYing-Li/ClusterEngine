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


class objobject
{
public:
    objobject() = default;
    objobject(const std::string name, std::shared_ptr<GameData> data_ptr);
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
