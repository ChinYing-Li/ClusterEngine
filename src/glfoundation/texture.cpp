#include <cassert>
#include <iostream>

#include "renderstate.h"
#include "texture.h"
#include "shaderregistry.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Cluster
{
unsigned int Texture2D::NUM_TEXTURE2D_TYPES = 5;

Texture::
Texture():
m_initialized(false),
  m_binding_point(-1)
{
    init();
}

bool Texture::
is_initialized()
{
    return m_initialized;
}


void Texture::
init()
{
    glGenTextures(1, &m_ID);
    m_initialized = true;
}


void Texture::
bind(const GLuint texture_binding_point)
{
  if (texture_binding_point > MAX_NUM_TEXTURE_BINDING_POINTS - 1)
  {
    std::cerr << "The given binding point is " << texture_binding_point
              <<"but the maximum allowed is " << MAX_NUM_TEXTURE_BINDING_POINTS
             << std::endl;
    return;
  }

  ShaderRegistry::activate_texture(texture_binding_point);
  ShaderRegistry::bind_texture(m_target, m_ID);
  m_binding_point = texture_binding_point;
  m_is_binded = true;
}

/*
 *
 */
void Texture::
destroy()
{
  if (!m_initialized)
  {
    return;
  }
  // TODO
}

void Texture::
set_magmin_filter(GLenum mag_filter, GLenum min_filter)
{
  glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, mag_filter);
  glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, min_filter);
}

void Texture::
set_mipmap_level(const unsigned int level)
{
  glTexParameteri(m_target, GL_TEXTURE_MAX_LEVEL, level);
}

Texture2D::
Texture2D():
    Texture(),
    m_height(0),
    m_width(0)
{
    m_target = GL_TEXTURE_2D;
}

Texture2D::
Texture2D(const fs::path& path, Texture::Type type):
Texture2D()
{
    m_vertex_size = 5;
    bool init_success = init_from_file(path, type);
    if(!init_success) throw;
}

bool Texture2D::
init_from_file(const fs::path& path, Texture::Type type)
{
    assert(m_initialized);
    int num_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data;

    switch(type)
    {
      case Texture::GRAYSCALE:
        data = stbi_load(path.c_str(), &m_width, &m_height, &num_channels, STBI_grey);
        break;
      case Texture::LDR:
        data = stbi_load(path.c_str(), &m_width, &m_height, &num_channels, STBI_rgb_alpha);
        break;
      case Texture::Type::HDR:
        data = stbi_load(path.c_str(), &m_width, &m_height, &num_channels, STBI_rgb_alpha);
        break;
    }

    if (data)
    {
        glTexImage2D(m_target, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &data);
        std::cout << "Texture loaded at path: " << path.c_str() << std::endl;
        stbi_image_free(&data);
        return true;
    }
    else
    {
        std::cout << "texture failed to load at path: " << path.c_str() << std::endl;
        stbi_image_free(&data);
        return false;
    }

    return true;
}

void Texture2D::
set_dimensions(unsigned int width, unsigned int height) noexcept
{
  m_width = width;
  m_height = height;
}

void Texture2D::
set_texture_param(GLint internal_format, GLenum format, GLenum type, void *data)
{
  glTexImage2D(m_target, 0, internal_format, m_width, m_height, 0, format, type, data);
}

void Texture2D::
set_wrapping(GLint wrap_s, GLint wrap_t)
{
  glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap_t);
}

inline void Texture2D::
set_vertexattrib()
{
    glVertexAttribPointer
       (
           0,                            // attribute 0. Vertices
           3,                            // size (x,y,z)
           GL_FLOAT,                     // type
           GL_FALSE,                     // normalized?
           5*sizeof(GLfloat),                            // stride
           (void *) 0                      // array buffer offset
        );
       glVertexAttribPointer
       (
           1,                            // attribute 0. Vertices
           2,                            // size (s, t)
           GL_FLOAT,                     // type
           GL_FALSE,                     // normalized?
           5*sizeof(GLfloat),                            // stride
           (void *) (3 *sizeof(GLfloat))                    // array buffer offset
        );
    return;
}

TextureCubemap::TextureCubemap():
Texture()
{
    m_target = GL_TEXTURE_CUBE_MAP;
}

TextureCubemap::
TextureCubemap(const std::vector<fs::path>& paths, Texture::Type type):
Texture()
{
    m_target = GL_TEXTURE_CUBE_MAP;
    m_vertex_size = 3;

    init_from_file(paths);
    std::cout << paths.size() << std::endl;
}

bool TextureCubemap::init_from_file(const std::vector<fs::path>& file_path)
{
    assert(m_initialized);
    m_num_faces = 0;

    int num_channels;
    for(int i = 0; i < file_path.size(); ++i)
    {
        unsigned char *data = stbi_load(file_path[i].c_str(), &m_width, &m_height, &num_channels, STBI_rgb_alpha);
        if (data)
        {
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0,
                       GL_RGB,
                       m_width,
                       m_height,
                       0,
                       GL_RGB, GL_UNSIGNED_BYTE,
                       data);

          std::cout << "Cubemap texture loaded at path: " << file_path[i] << std::endl;
          stbi_image_free(data);
        }
        else
        {
          std::cout << "Cubemap texture failed to load at path: " << file_path[i] << std::endl;
          stbi_image_free(data);
          return false;
        }
        this->set_face_texture_param(i, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT, data);
    }
    return true;
}

inline void TextureCubemap::set_vertexattrib()
{
    glVertexAttribPointer
    (
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        3*sizeof(GLfloat),            // stride
        (void *) 0                    // array buffer offset
     );
    return;
}

void TextureCubemap::
set_resolution(unsigned int resolution)
{
  m_resolution = resolution;
}

void TextureCubemap::
set_face_texture_param(unsigned int face,
                       GLint internal_format,
                       GLenum format,
                       GLenum type,
                       void *data)
{
  assert(m_resolution > 0);
  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
               0,
               internal_format,
               m_resolution,
               m_resolution,
               0,
               format,
               type,
               data);
}

void TextureCubemap::
set_wrapping(GLint wrap_s, GLint wrap_t, GLint wrap_r)
{
  //check whether this texture is binded
  glTexParameteri(m_target, GL_TEXTURE_WRAP_S, wrap_s);
  glTexParameteri(m_target, GL_TEXTURE_WRAP_T, wrap_t);
  glTexParameteri(m_target, GL_TEXTURE_WRAP_R, wrap_r);
}

void TextureCubemap::
set_current_face(unsigned int face)
{
  assert(face < 6);
  m_current_face = face;
}

} // namespace Cluster
