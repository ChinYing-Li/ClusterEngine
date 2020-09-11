#pragma once

#include <map>
#include <string>
#include <vector>

#include "glincludes.h"

#define MAX_NUM_TEXTURE_BINDING_POINTS 8

///////////////////////////////////////////////////////////////////////////////
/// \brief The Texture class
///
class Texture
{
public:
    Texture();
    Texture(const std::string name);
    ~Texture() = default;

    void init();
    void bind(const GLuint texture_binding_point);

    void set_magmin_filter(GLenum mag_filter, GLenum min_filter);
    void set_mipmap_level(const unsigned int level);

    GLuint get_ID() const { return m_ID; }

    GLenum get_target() const { return m_target; }

    void set_vertex_size(unsigned int vertex_size)
    {
        m_vertex_size = vertex_size;
    }

protected:
    bool m_initialized = false;
    bool m_is_binded = false;
    unsigned int m_vertex_size;
    unsigned int m_binding_point;

    std::string m_name; // name for lookup in texture manager
    GLuint m_ID;
    GLenum m_target;

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

    void set_dimensions(unsigned int width, unsigned int height) noexcept;
    void set_image_param(GLint internal_format, GLenum format, GLenum tyoe, void* data);
    void set_wrap_st(GLint wrap_s, GLint wrap_t);
    void set_sampling(GLint mag_gilter, GLint min_filter);
protected:
    int m_height;
    int m_width;

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
