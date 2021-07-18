#include <boost/log/trivial.hpp>
#include <iostream>

#include "stb_image.h"
#include "cubemap.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{

Cubemap::Cubemap():
Renderable()
{}

Cubemap::
Cubemap(GLenum primitive_mode,
        int numVertices,
        const GLfloat *vertex_buffer_data):
Renderable()
{
    init(primitive_mode, numVertices, vertex_buffer_data);
}

bool Cubemap::
is_usable()
{
    return m_texture_ptr != nullptr;
}

void Cubemap::
init(GLenum primitive_mode,
     int numVertices,
     const GLfloat *vertex_buffer_data)
{
    m_primitive_mode = primitive_mode;
    m_num_vertices   = numVertices;

    glGenVertexArrays(1, &(m_VAO)); // GLObject
    glGenBuffers (1, &(m_VBO)); // VBO - vertices

    glBindVertexArray(m_VAO); // Bind the GLObject
    glBindBuffer (GL_ARRAY_BUFFER, m_VBO); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER,
                  3*m_num_vertices*sizeof(GLfloat),
                  vertex_buffer_data,
                  GL_STATIC_DRAW); // Copy the vertices into VBO

    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(GLfloat),
                          (void*)0);
    glBindVertexArray(0);
    return;
}

bool Cubemap::
initialize_texture(std::vector<fs::path>& path_to_texture)
{
    if (m_texpath.empty())
    {
      // BOOST_TRIVIAL_LOG(warning) << "Did not specify the path to texture yet. Can't loading cubemap texture" ;
      return false;
    }
    m_texture_ptr = std::make_unique<TextureCubemap>();
    m_texture_ptr->bind(0);
    bool res = m_texture_ptr->init_from_file(path_to_texture);
    if(!res)
    {
        return res;
    }
    m_texture_ptr->set_magmin_filter(GL_LINEAR, GL_LINEAR);
    m_texture_ptr->set_wrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    return res;
    //std::cout << "texture id" << textureID << std::endl;
}

void Cubemap::
render(const Shader& shader)
{
    // Enable Vertex Attribute 1 - Color
    glBindVertexArray (m_VAO);
    glEnableVertexAttribArray(0);
    //glActiveTexture(GL_TEXTURE0);

    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_ptr->get_ID());

    // Draw the geometry !
    glDrawArrays(m_primitive_mode, 0, m_num_vertices); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
    return;
}

} // namespace Cluster
