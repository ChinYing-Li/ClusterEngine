#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "glincludes.h"

#define MAX_NUM_TEXTURE_BINDING_POINTS 8

namespace Cluster
{
///////////////////////////////////////////////////////////////////////////////
/// \brief The Texture class
///
class Texture
{
public:
    Texture();
    Texture(const std::string name);
    ~Texture();

    void init();
    void bind(const GLuint binding_point);
    void destroy();

    void set_magmin_filter(GLenum mag_filter, GLenum min_filter);
    void set_mipmap_level(const unsigned int level);

    GLuint get_ID() const { return m_ID; }
    GLenum get_target() const { return m_target; }
    bool is_bound();

    void set_vertex_size(unsigned int vertex_size) // TODO:　remove this weird function
    {
        m_vertex_size = vertex_size;
    }

    enum Type
    {
      GRAYSCALE = 0,
      RGBA,
      HDR,
    };

protected:
    bool m_initialized = false;
    bool m_is_binded = false;
    unsigned int m_vertex_size;
    unsigned int m_binding_point;

    GLuint m_ID;
    GLenum m_target;
    Type m_type;

    std::map<GLenum, GLenum> m_parameter_map; // Not sure if this should be present
    inline void virtual set_vertexattrib() = 0;
};

class Texture2D final : public Texture
{
public:
    Texture2D();
    Texture2D(const std::filesystem::path& path, Texture::Type type);
    ~Texture2D() = default;

    inline void set_vertexattrib() override;

    static void init_type();
    static unsigned int NUM_TEXTURE2D_TYPES;

    enum T2D_Usage
    {
        TU_albedo = 0,
        TU_bump,
        TU_emission,
        TU_normal,
        TU_stencil,
    };

    void set_dimensions(unsigned int width, unsigned int height) noexcept;
    void set_texture_param(GLint internal_format, GLenum format, GLenum tyoe, void* data);
    void set_wrap_st(GLint wrap_s, GLint wrap_t);
    void set_sampling(GLint mag_gilter, GLint min_filter);

    int get_height() const noexcept;
    int get_weight() const noexcept;

private:
    int m_height;
    int m_width;
    bool init_from_file(const std::filesystem::path& path, Texture::Type type);
};

class TextureCubemap final : public Texture
{
public:
    TextureCubemap();
    TextureCubemap(const std::vector<std::filesystem::path>& path, Texture::Type type);
    ~TextureCubemap() = default;

    inline void set_vertexattrib() override;
    int get_height() const noexcept;
    int get_weight() const noexcept;
    int get_num_faces() const noexcept;

protected:
    bool init_from_file(const std::vector<std::filesystem::path>& path, Texture::Type type);

private:
    int m_height;
    int m_width;
    int m_num_faces = 0;
};

} // namespace Cluster
