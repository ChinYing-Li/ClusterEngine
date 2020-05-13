#include <cassert>
#include <iostream>
#include "texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
Texture::Texture():
m_initiated(false)
{}

Texture::Texture(const std::string name):
m_initiated(false)
{
    m_name = name;
}


Texture2D::Texture2D():
Texture(),
m_height(0),
m_width(0)
{
    m_format = GL_TEXTURE_2D;
}

Texture2D::Texture2D(const std::string name, const std::vector<std::string>& file_path):
Texture2D()
{
    m_name = name;
    
    bool init_success = init_from_file(file_path);
    if(init_success) m_initiated = true;
    m_parametermap[GL_TEXTURE_MAG_FILTER] = GL_LINEAR;
    m_parametermap[GL_TEXTURE_MIN_FILTER] = GL_LINEAR;
    m_parametermap[GL_TEXTURE_WRAP_S] = GL_REPEAT;
    m_parametermap[GL_TEXTURE_WRAP_T] = GL_REPEAT;
}

bool Texture2D::init_from_file(const std::vector<std::string>& file_path)
{
    assert(file_path.size() == 1);
    if (file_path.size() == 0) return false;
    glGenTextures(1, &(this->m_ID));
    glBindTexture(this->m_format, this->m_ID);
    for(auto it = this->m_parametermap.begin(); it != this->m_parametermap.end(); ++it)
    {
        glTexParameteri(this->m_format, it->first, it->second);
    }
    
    int nchannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file_path[0].c_str(), &m_width, &m_height, &nchannels, 0);

    if (data)
    {
        glTexImage2D(m_format, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        std::cout << "texture loaded at path: " << file_path[0] << std::endl;
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cout << "texture failed to load at path: " << file_path[0] << std::endl;
        stbi_image_free(data);
        return false;
    }
    return true;
}

TextureCubemap::TextureCubemap():
Texture()
{
    m_ID = 0;
    m_format = GL_TEXTURE_CUBE_MAP;
}

TextureCubemap::TextureCubemap(const std::string name, const std::vector<std::string>& file_path):
Texture(name)
{
    m_format = GL_TEXTURE_CUBE_MAP;
    m_parametermap[GL_TEXTURE_MAG_FILTER] = GL_LINEAR;
    m_parametermap[GL_TEXTURE_MIN_FILTER] = GL_LINEAR;
    m_parametermap[GL_TEXTURE_WRAP_S] = GL_CLAMP_TO_EDGE;
    m_parametermap[GL_TEXTURE_WRAP_T] = GL_CLAMP_TO_EDGE;
    m_parametermap[GL_TEXTURE_WRAP_R] = GL_CLAMP_TO_EDGE;
    
    m_initiated = init_from_file(file_path);
}

bool TextureCubemap::init_from_file(const std::vector<std::string>& file_path)
{
    assert(file_path.size() == 6);
    glGenTextures(1, &(this->m_ID));
    glBindTexture(this->m_format, this->m_ID);
    for(auto it = this->m_parametermap.begin(); it != this->m_parametermap.end(); ++it)
    {
        glTexParameteri(this->m_format, it->first, it->second);
    }
    int nchannels;
    for(int i = 0; i < file_path.size(); ++i)
    {
        unsigned char *data = stbi_load(file_path[i].c_str(), &m_width, &m_height, &nchannels, 0);
        if (data)
        {
          glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
          std::cout << "Cubemap texture loaded at path: " << file_path[i] << std::endl;
          stbi_image_free(data);
            return true;
        }
        else
        {
          std::cout << "Cubemap texture failed to load at path: " << file_path[i] << std::endl;
            stbi_image_free(data);
            return false;
        }
    }
    return true;
}
