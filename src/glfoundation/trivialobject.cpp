#include "trivialobject.h"

namespace Cluster{
TrivialObject::
TrivialObject(): GLObject()
{}

TrivialObject::
TrivialObject(GLenum primitive_mode,
              int numVertices,
              const GLfloat *vertex_buffer_data,
              const color_t color,
              GLenum fill_mode):
Renderable()
{
    Renderable::init(primitive_mode, numVertices);
    m_fill_mode      = fill_mode;
    init(vertex_buffer_data, color);
}



TrivialObject::
TrivialObject(GLenum primitive_mode,
              int numVertices,
              const GLfloat *vertex_buffer_data,
              int numindices,
              const GLuint *indices,
              const color_t color,
              GLenum fill_mode):
Renderable()
{
    Renderable::init(primitive_mode,numVertices);
    m_using_EBO = true;
    m_num_indices = numindices;
    m_fill_mode      = fill_mode;

    GLfloat *color_buffer_data = new GLfloat[3 * m_num_vertices];
    for (int i = 0; i < m_num_vertices; i++) {
        color_buffer_data[3 * i]     = float(color.r)/256.0;
        color_buffer_data[3 * i + 1] = float(color.g)/256.0;
        color_buffer_data[3 * i + 2] = float(color.b)/256.0;
    }

    init(vertex_buffer_data, indices, color_buffer_data);
}

void TrivialObject::
init(const GLfloat *vertex_buffer_data,
     const GLfloat *color_buffer_data)
{
    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &m_VAO); // GLObject
    glGenBuffers (1, &m_VBO); // VBO - vertices
    glGenBuffers (1, &m_CBO); // VBO - colors

    glBindVertexArray (m_VAO); // Bind the GLObject
    glBindBuffer (GL_ARRAY_BUFFER, m_VBO); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*(m_num_vertices)*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void *) 0                      // array buffer offset
    );

    glBindBuffer (GL_ARRAY_BUFFER, m_CBO); // Bind the VBO colors
    glBufferData (GL_ARRAY_BUFFER, 3 * m_num_vertices * sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW); // Copy the vertex colors
    glVertexAttribPointer(
        1,                            // attribute 1. Color
        3,                            // size (r,g,b)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void *) 0                    // array buffer offset
    );
    glBindVertexArray(0);
    return;
}

void TrivialObject::
init(const GLfloat *vertex_buffer_data,
     const GLuint *indices,
     const GLfloat *color_buffer_data)
{
    init(vertex_buffer_data, color_buffer_data);

    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_num_indices, indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
    return;
}



/* Render the VBOs handled by GLObject */
void TrivialObject::
render(GLuint& shaderID) {
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, m_fill_mode);

    // Bind the GLObject to use
    glBindVertexArray (m_VAO);
    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_CBO);

    if(m_using_EBO)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    }
    // Draw the geometry !

    glDrawArrays(m_primitive_mode, 0, m_num_vertices);
    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
}

/* Generate GLObject, VBOs and return GLObject handle - Common Color for all vertices */
void TrivialObject::
init(const GLfloat *vertex_buffer_data,
     const GLfloat red,
     const GLfloat green,
     const GLfloat blue)
{
    GLfloat *color_buffer_data = new GLfloat[3 * m_num_vertices];
    for (int i = 0; i < m_num_vertices; i++) {
        color_buffer_data[3 * i]     = red;
        color_buffer_data[3 * i + 1] = green;
        color_buffer_data[3 * i + 2] = blue;
    }

    init(vertex_buffer_data, color_buffer_data);
    return;
}

} // namespace Cluster
