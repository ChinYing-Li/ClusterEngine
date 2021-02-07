#pragma once

#include <memory>
#include <string>

#include "texture.h"
#include "src/glfoundation/transformation.h"
#include "Imanagers.h"

namespace Cluster{
/**
 * @brief The base class of all shadable objects
 */
class GLObejct
{
public:
    GLObejct();
    ~GLObejct() = default;

    GLuint m_VAO;
    GLuint m_VBO;
    GLuint color_buffer;
    GLuint m_EBO; // EBO

    GLenum m_primitivemode;
    GLenum m_fillmode;
    bool isinstancing = false;

    int m_num_vertices;
    int m_num_indices;

    void virtual draw(GLuint& shaderID) = 0;
    void set_instance_attrib();
    void virtual send_instance_matrices(std::vector<glm::mat4>& instance_models){};
    void init(GLenum primitive_mode, int numVertices);

    void translate(const glm::vec4 translation);
    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);

    void scale_x(float scale);
    void scale_y(float scale);
    void scale_z(float scale);

protected:
    bool is_using_EBO = false;
    Transformation m_transformation;
};

} // namespace Cluster
