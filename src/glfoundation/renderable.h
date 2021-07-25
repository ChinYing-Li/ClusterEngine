#pragma once

#include <memory>
#include <string>

#include "texture.h"
#include "transformation.h"

namespace Cluster
{
class Shader;

/**
 * @brief The base abstract class of all shadable objects.
 */
class Renderable
{
public:
    Renderable() = default;
    Renderable(int n_vertices);
    ~Renderable() = default;

    void virtual render(const Shader& shader) = 0;
    void virtual render(const Shader* shader);

    void set_num_instances(const unsigned int num_instances);
    void set_instance_attrib();

    void virtual send_instance_matrices(std::vector<glm::mat4>& instance_model_mat){};

    void translate(const glm::vec4 translation);
    bool is_gl_init();
    void load_model_mat(glm::mat4& model_mat);

    // This should be delegate to m_transform
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

    GLenum m_primitive_mode;
    GLenum m_fill_mode;

    int m_num_vertices;
    int m_num_indices;
    int m_num_instances = 1;
    bool m_gl_init = false;
    bool m_instanced = false;
    bool m_using_EBO = false;

    Transformation m_transformation;
};

} // namespace Cluster
