#pragma once

#include <experimental/filesystem>
#include <map>
#include <string>
#include <vector>

#include "glincludes.h"

namespace fs = std::experimental::filesystem;

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
    ~Texture() = default;

    void init();
    void bind(const GLuint binding_point);
    void destroy();

    void set_magmin_filter(GLenum mag_filter, GLenum min_filter);
    void set_mipmap_level(const unsigned int level);

    const GLuint get_ID() const { return m_ID; }
    GLenum get_target() const { return m_target; }
    bool is_bound();
    bool is_initialized();

    void set_vertex_size(unsigned int vertex_size) // TODO:　remove this weird function
    {
        m_vertex_size = vertex_size;
    }

    enum Type
    {
      GRAYSCALE = 0,
      LDR,
      HDR,
    };

    static const unsigned int ALBEDO = 0;

protected:
    bool m_initialized = false;
    bool m_is_binded = false;
    unsigned int m_vertex_size;
    unsigned int m_binding_point;

    GLuint m_ID;
    GLenum m_target;
    Type m_type;

    inline void virtual set_vertexattrib() = 0;
};

class Texture2D final : public Texture
{
public:
    Texture2D();
    Texture2D(const fs::path& path, Texture::Type type);
    ~Texture2D() = default;

    inline void set_vertexattrib() override;
    static unsigned int NUM_TEXTURE2D_TYPES;

    enum Usage
    {
        ALBEDO = 0,
        BUMP,
        EMISSION,
        NORMAL,
        STENCIL,
    };

    void set_dimensions(unsigned int width, unsigned int height) noexcept;
    void set_texture_param(GLint internal_format, GLenum format, GLenum tyoe, void* data);
    void set_wrapping(GLint wrap_s, GLint wrap_t);

    int get_height() const noexcept;
    int get_weight() const noexcept;

private:
    int m_height;
    int m_width;
    bool init_from_file(const fs::path& path, Texture::Type type);
};

class TextureCubemap final : public Texture
{
public:
    TextureCubemap();
    TextureCubemap(const std::vector<fs::path>& path, Texture::Type type);
    ~TextureCubemap() = default;

    inline void set_vertexattrib() override;
    void set_resolution(unsigned int resolution);
    void set_face_texture_param(unsigned int face, GLint internal_format, GLenum format, GLenum type, void* data);
    void set_wrapping(GLint wrap_s, GLint wrap_t, GLint wrap_r);
    void set_current_face(unsigned int face);

    int get_height() const noexcept;
    int get_weight() const noexcept;
    int get_current_face() const noexcept;
    bool init_from_file(const std::vector<fs::path>& path);

private:
    int m_height;
    int m_width;
    unsigned int m_current_face = 0;
    unsigned int m_num_faces = 0;
    unsigned int m_resolution;
};

} // namespace Cluster
