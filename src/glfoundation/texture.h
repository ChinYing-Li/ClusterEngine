#pragma once

#include <map>
#include <string>
#include <vector>

#include "glincludes.h"


///////////////////////////////////////////////////////////////////////////////
/// \brief The Texture class
///
class Texture
{
public:
    Texture();
    Texture(const std::string name);
    ~Texture() = default;

    GLuint get_ID() const
    {
        return m_ID;
    }

    GLenum get_format() const
    {
        return m_format;
    }

    void set_vertex_size(unsigned int vertex_size)
    {
        m_vertex_size = vertex_size;
    }

protected:
    bool m_initialized = false;
    unsigned int m_vertex_size;
    std::string m_name; // name for lookup in texture manager
    GLuint m_ID;
    GLenum m_format;

    void init();
    // functions only accessed by texturemanager
    void set_texture_param();
    std::map<GLenum, GLenum> m_parameter_map;
    inline void virtual set_vertexattrib() = 0;
};

class Texture2D final : public Texture
{
public:
    Texture2D();
    Texture2D(const std::string name, const std::vector<std::string>& file_path);
    ~Texture2D() = default;
    
    int m_height;
    int m_width;

    inline void set_vertexattrib() override;

    static void init_type();
    static unsigned int NUM_TEXTURE2D_TYPES;

    enum Texture2DUsage
    {
        TU_albedo = 0,
        TU_bump,
        TU_emission,
        TU_normal,
        TU_stencil,
    };

protected:
    bool init_from_file(const std::vector<std::string>& file_path);
};

class TextureCubemap final : public Texture
{
public:
    TextureCubemap();
    TextureCubemap(const std::string name, const std::vector<std::string>& file_path);
    ~TextureCubemap() = default;

    inline void set_vertexattrib() override;

protected:
    bool init_from_file(const std::vector<std::string>& file_path);

private:
    int m_height;
    int m_width;
    int m_num_faces = 0;
};
