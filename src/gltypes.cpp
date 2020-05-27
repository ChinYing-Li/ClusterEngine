#include "src/gltypes.h"


#include <iostream>

GameData::GameData()
{}

void GameData::init()
{
    resmanager_ptr = std::make_unique<ResourceManager>();
    inputmanager_ptr = std::make_unique<InputManager>();
    std::cout << "DataManager initialized\n" << std::endl;
    return;
}

void VAO::init(GLenum primitive_mode, int numVertices)
{
    m_primitivemode = primitive_mode;
    m_numvert   = numVertices;
    return;
}

VAO_monotone::VAO_monotone():
VAO()
{}

VAO_monotone::VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode):
VAO()
{
    VAO::init(primitive_mode, numVertices);
    m_fillmode      = fill_mode;
    init(vertex_buffer_data, color);
}



VAO_monotone::VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, int numindices, const GLuint *indices, const color_t color, GLenum fill_mode):
VAO()
{
    VAO::init(primitive_mode,numVertices);
    useEBO = true;
    m_numindices = numindices;
    m_fillmode      = fill_mode;
    
    GLfloat *color_buffer_data = new GLfloat[3 * m_numvert];
    for (int i = 0; i < m_numvert; i++) {
        color_buffer_data[3 * i]     = float(color.r)/256.0;
        color_buffer_data[3 * i + 1] = float(color.g)/256.0;
        color_buffer_data[3 * i + 2] = float(color.b)/256.0;
    }
    
    init(vertex_buffer_data, indices, color_buffer_data);
}

void VAO_monotone::init(const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data)
{
    // Create Vertex Array Object
    // Should be done after CreateWindow and before any other GL calls
    glGenVertexArrays(1, &m_vertexarrayID); // VAO
    glGenBuffers (1, &m_vertexbuffer); // VBO - vertices
    glGenBuffers (1, &color_buffer); // VBO - colors

    glBindVertexArray (m_vertexarrayID); // Bind the VAO
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*(m_numvert)*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void *) 0                      // array buffer offset
    );
    
    glBindBuffer (GL_ARRAY_BUFFER, color_buffer); // Bind the VBO colors
    glBufferData (GL_ARRAY_BUFFER, 3 * m_numvert * sizeof(GLfloat), color_buffer_data, GL_STATIC_DRAW); // Copy the vertex colors
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

void VAO_monotone::init(const GLfloat *vertex_buffer_data, const GLuint *indices, const GLfloat *color_buffer_data)
{
    init(vertex_buffer_data, color_buffer_data);
    
    glGenBuffers(1, &m_indicebuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicebuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m_numindices, indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
    return;
}



/* Render the VBOs handled by VAO */
void VAO_monotone::draw(GLuint shaderID) {
    // Change the Fill Mode for this object
    glPolygonMode (GL_FRONT_AND_BACK, m_fillmode);

    // Bind the VAO to use
    glBindVertexArray (m_vertexarrayID);
    // Enable Vertex Attribute 0 - 3d Vertices
    glEnableVertexAttribArray(0);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);

    // Enable Vertex Attribute 1 - Color
    glEnableVertexAttribArray(1);
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    
    if(useEBO)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicebuffer);
        
    }
    // Draw the geometry !
    
    glDrawArrays(m_primitivemode, 0, m_numvert);
    // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
}

/* Generate VAO, VBOs and return VAO handle - Common Color for all vertices */
void VAO_monotone::init(const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue)
{
    GLfloat *color_buffer_data = new GLfloat[3 * m_numvert];
    for (int i = 0; i < m_numvert; i++) {
        color_buffer_data[3 * i]     = red;
        color_buffer_data[3 * i + 1] = green;
        color_buffer_data[3 * i + 2] = blue;
    }

    init(vertex_buffer_data, color_buffer_data);
    return;
}

void VAO_monotone::init(const GLfloat *vertex_buffer_data, const color_t color) {
    init(vertex_buffer_data, color.r / 256.0, color.g / 256.0, color.b / 256.0);
    return;
}

VAO_texture::VAO_texture():
VAO()
{}

VAO_texture::VAO_texture(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const std::string texname, GameData& gamedata):
VAO(),
m_texname(texname)
{
    VAO::init(primitive_mode, numVertices);
    init(vertex_buffer_data, gamedata);
}

void VAO_texture::draw(GLuint shaderID) {
    // Change the Fill Mode for this object
    //glPolygonMode (GL_FRONT_AND_BACK, m_fillmode);
    
    // Bind the VAO to use
    glBindVertexArray (m_vertexarrayID);

    // Enable Vertex Attribute 0 - 3d (x, y, z)
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    // Enable Vertex Attribute 1 - Color
    
    glBindTexture(m_texptr->m_format, m_texptr->m_ID);
    // Draw the geometry !
    glDrawArrays(m_primitivemode, 0, m_numvert);
    glBindVertexArray(0);
    return;
}

void VAO_texture::init(const GLfloat *vertex_buffer_data, GameData& gamedata)
{
    glGenVertexArrays(1, &(m_vertexarrayID)); // VAO
    glGenBuffers (1, &(m_vertexbuffer)); // VBO - vertices

    glBindVertexArray (m_vertexarrayID); // Bind the VAO
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer); // Bind the VBO vertices
    
    m_texptr = gamedata.resmanager_ptr->retrieve_texture(m_texname);
    if(m_texptr == nullptr) std::cout << "m_texptr points to NULL" <<  std::endl;
    glBufferData (GL_ARRAY_BUFFER, m_texptr->m_vertexsize*m_numvert*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    m_texptr->set_vertexattrib();
    glBindVertexArray(0);
    
    return;
}

void VAO_texture::load_texture()
{
    
    return;
}

VAO_material::VAO_material():
VAO()
{}

VAO_material::VAO_material(GLenum primitive_mode, int num_vertices, const GLfloat* vertex_position, const GLfloat* vertex_normal, GameData& gamedata):
VAO()
{
    VAO::init(primitive_mode, num_vertices);
    init(vertex_position, vertex_normal, gamedata);
}

void VAO_material::init(const GLfloat *vertex_buffer_data, const GLfloat* vertex_normal, GameData& gamedata)
{
    glGenVertexArrays(1, &(m_vertexarrayID));
    glGenBuffers (1, &(m_vertexbuffer));

    glBindVertexArray (m_vertexarrayID);
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer);
    glBufferSubData (GL_ARRAY_BUFFER, 0, 3*(m_numvert)*sizeof(GLfloat), vertex_buffer_data); // Copy the vertices into VBO
    glBufferSubData (GL_ARRAY_BUFFER, 3*(m_numvert)*sizeof(GLfloat), 3*(m_numvert)*sizeof(GLfloat), vertex_normal);
    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void *) 0                      // array buffer offset
    );
    glVertexAttribPointer(
        1,                            // attribute 1. Normal
        3,                            // size (r,g,b)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        0,                            // stride
        (void *)(3*(m_numvert)*sizeof(GLfloat))// array buffer offset
    );
    glBindVertexArray(0);
}

void VAO_material::draw(GLuint shaderID)
{
    glBindVertexArray (m_vertexarrayID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(m_primitivemode, 0, m_numvert);
    glBindVertexArray(0);
    return;
}


/*
VAO_cubemap::VAO_cubemap():
VAO()
{}

VAO_cubemap::VAO_cubemap(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string> &path_to_texture):
VAO()
{
    init(primitive_mode, numVertices, vertex_buffer_data, path_to_texture);
}

void VAO_cubemap::init(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string> &path_to_texture)
{
    m_primitivemode = primitive_mode;
    m_numvert   = numVertices;
    m_texpath = path_to_texture;
    
    glGenVertexArrays(1, &(m_vertexarrayID)); // VAO
    glGenBuffers (1, &(m_vertexbuffer)); // VBO - vertices

    glBindVertexArray (m_vertexarrayID); // Bind the VAO
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

void VAO_cubemap::load_texture()
{
    
    if (m_texpath.size() == 0) {
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

void VAO_cubemap::draw(GLuint shaderID)
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
*/
