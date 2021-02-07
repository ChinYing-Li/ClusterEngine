#pragma once

#include <memory>
#include <string>

#include "texture.h"
#include "src/glfoundation/transformation.h"
#include "Imanagers.h"

namespace Cluster
{
class Shader;
/**
 * @brief The base class of all shadable objects
 */
class Renderable
{
public:
    Renderable();
    Renderable(int n_vertices);
    ~Renderable() = default;

    void virtual render(Shader& shader) = 0;
    void set_instance_attrib();
    void virtual send_instance_matrices(std::vector<glm::mat4>& instance_models){};

    void translate(const glm::vec4 translation);
    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);

    void scale_x(float scale);
    void scale_y(float scale);
    void scale_z(float scale);

protected:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_CBO; // Color buffer object
    GLuint m_EBO; // EBO

    GLenum m_primitivemode;
    GLenum m_fillmode;

    int m_num_vertices;
    int m_num_indices;
    bool m_instanced = false;
    bool m_using_EBO = false;

    Transformation m_transformation;
};

} // namespace Cluster
