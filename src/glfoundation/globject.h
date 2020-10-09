#pragma once

#include <memory>
#include <string>

#include "texture.h"
#include "state.h"
#include "Imanagers.h"

namespace Cluster{
/*! GLObject stands for "Vertex Array Object", and is the base class
 *
 *
 */
class GLObejct
{
public:
    GLObejct() = default;
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

protected:
    bool is_using_EBO = false;
};

} // namespace Cluster
