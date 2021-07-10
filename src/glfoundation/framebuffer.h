#pragma once

#include <memory>
#include <vector>

#include "glincludes.h"
#include "texture.h"
#include "texturemanager.h"

namespace Cluster{
class FrameBuffer
{
public:
    FrameBuffer(unsigned int width, unsigned int height);
    ~FrameBuffer();

    enum Usage
    {
      NORMAL = GL_FRAMEBUFFER,
      DRAW   = GL_DRAW_FRAMEBUFFER,
      READ   = GL_READ_FRAMEBUFFER,
    };

    void bind(const Usage usage) const noexcept;
    void release() const noexcept;
    void check_status() const noexcept;
    void enable_color(GLenum mode);
    void disable_color();

    void resize(const unsigned int width, const unsigned int height);
    void reset();
    void create(const unsigned int width, const unsigned int height);

    void attach_texture(GLuint attachment, Texture2D texture, unsigned int mipmap_level = 0);
    // void attach_color_texture(unsigned int index, const TextureFormat format, unsigned int mipmap_level = 0);
    void attach_color_texture(unsigned int index, Texture2D texture, unsigned int mipmap_level = 0);

    void attach_depth_texture(Texture2D texture);
    void attach_depth_stencil_texture(Texture2D texture);

    void set_cubemap(GLenum attachment, const TextureCubemap texture_cubemap, GLint mipmap_level);
    void set_parameter(GLenum binding_target, GLenum param_name, GLint param_val);

    //TODO: add drawbuffer and read buffer??
    Texture2D get_color_texture(unsigned int binding_point);
    Texture2D get_color_texture_in_use() const;

    unsigned int get_current_draw_buffer() const;
    void set_current_draw_buffer(unsigned int color_attachment);

    static const unsigned int MAX_NUM_COLOR_TEXTURE = 10;

private:
    unsigned int m_width;
    unsigned int m_height;
    Usage m_usage;
    GLuint m_fbo;

    std::vector<Texture2D> m_color_textures;
    Texture2D m_depth_texture;

    unsigned int m_current_drawbuffer;
    std::vector<GLenum> m_drawbuffers;
};

}
