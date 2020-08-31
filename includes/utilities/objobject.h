#pragma once

#include <vector>
#include <string.h>
#include <map>
#include <memory>

#include "includes/GLincludes.h"
#include "src/gltypes.h"
#include "includes/glfoundation/texture.h"

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
    objobject(const std::string name, std::shared_ptr<GameData> data_ptr, unsigned int numinstance);
    ~objobject();

    void draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project);
    void draw(GLuint& shaderID, glm::mat4& model, glm::mat4& view, glm::mat4& project);
    void set_instance_mat(std::vector<glm::mat4>& instance_mat);

    std::string m_name;
    glm::mat4 m_model;
    glm::mat4 m_project;
    glm::mat4 m_view;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    unsigned int m_instance = 0;

protected:
    void virtual calc_model_mat();
    void get_matrices_ID(GLuint& shaderID);
    void set_matrices(GLuint& shaderID, glm::mat4& view, glm::mat4& project);
    void set_matrices(GLuint& shaderID, glm::mat4& model, glm::mat4& view, glm::mat4& project);

    GLuint m_umodel;
    GLuint m_uproject;
    GLuint m_uview;

    std::vector<VAO_mesh> vao_meshes;
};
