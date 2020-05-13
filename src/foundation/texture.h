#pragma once
#include <map>
#include <string>
#include <vector>

#include "gl_headers.h"

class Texture // only holds the data...
{
public:
    Texture();
    Texture(const std::string name);
    ~Texture() = default;
    bool m_initiated;
    std::string m_name; // name for lookup in texture manager
    GLuint m_ID;
    GLenum m_format;
    std::map<GLenum, GLenum> m_parametermap;
    
protected:
    // functions only accessed by texturemanager

};

class Texture2D: public Texture
{
public:
    Texture2D();
    Texture2D(const std::string name, const std::vector<std::string>& file_path);
    ~Texture2D() = default;
    int m_height;
    int m_width;
    
protected:
    bool init_from_file(const std::vector<std::string>& file_path);
};

class TextureCubemap: public Texture
{
public:
    TextureCubemap();
    TextureCubemap(const std::string name, const std::vector<std::string>& file_path);
    ~TextureCubemap() = default;
    int m_height;
    int m_width;
protected:
    bool init_from_file(const std::vector<std::string>& file_path);
};
