#include "cubemap.h"

Cubemap::Cubemap():
GLObject()
{}

Cubemap::
Cubemap(GLenum primitive_mode,
        int numVertices,
        const GLfloat *vertex_buffer_data,
        std::vector<std::string> &path_to_texture):
GLObject()
{
    init(primitive_mode, numVertices, vertex_buffer_data, path_to_texture);
}

void Cubemap::
init(GLenum primitive_mode,
     int numVertices,
     const GLfloat *vertex_buffer_data,
     std::vector<std::string> &path_to_texture)
{
    m_primitivemode = primitive_mode;
    m_numvert   = numVertices;
    m_texpath = path_to_texture;

    glGenVertexArrays(1, &(m_vertexarrayID)); // GLObject
    glGenBuffers (1, &(m_vertexbuffer)); // VBO - vertices

    glBindVertexArray (m_vertexarrayID); // Bind the GLObject
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*m_numvert*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer
    (0,
     3,
     GL_FLOAT,
     GL_FALSE,
     3 * sizeof(float),
     (void*)0);
    glBindVertexArray(0);
    load_texture();
    return;
}

void Cubemap::
load_texture()
{
    if (m_texpath.empty()) {
      return ;
    }

    glGenTextures(1, &(texture_buffer));
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_buffer);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // set the texture wrapping parameters
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    for(int i = 0; i < m_texpath.size(); ++i)
      {
          unsigned char *data = stbi_load(m_texpath[i].c_str(), &width, &height, &nrChannels, 0);
          if (data)
          {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            std::cout << "Cubemap texture loaded at path: " << m_texpath[i] << std::endl;
              //std::cout << width << " " << height << std::endl;
            stbi_image_free(data);
          }
          else
          {
            std::cout << "Cubemap texture failed to load at path: " << m_texpath[i] << std::endl;
            stbi_image_free(data);
          }
      }

    //std::cout << "texture id" << textureID << std::endl;
    return;
}

void Cubemap::
draw(GLuint& shaderID)
{
    // Enable Vertex Attribute 1 - Color
    glBindVertexArray (m_vertexarrayID);
    glEnableVertexAttribArray(0);
    //glActiveTexture(GL_TEXTURE0);

    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_buffer);

    // Draw the geometry !
    glDrawArrays(m_primitivemode, 0, m_numvert); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
    return;
}
