GL#pragma once

#include <memory>
#include <vector>

#include "glincludes.h"
#include "texture.h"
#include "texturegenerator.h"

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

    void reset();
    void create(const unsigned int width, const unsigned int height);

    void attach_texture(GLuint attachment, std::shared_ptr<Texture2D> texture, unsigned int mipmap_level = 0);
    void attach_color_texture(unsigned int index, const TextureFormat format, unsigned int mipmap_level = 0);
    void attach_color_texture(unsigned int index, std::shared_ptr<Texture2D> texture, unsigned int mipmap_level = 0);

    void attach_depth_texture(std::shared_ptr<Texture2D> texture);
    void attach_depth_stencil_texture(std::shared_ptr<Texture2D> texture);

    void set_cubemap(GLenum attachment, TextureCubemap& texture_cubemap, GLint mipmap_level);
    void set_parameter(GLenum binding_target, GLenum param_name, GLint param_val);

    // add drawbuffer and read buffer??

    std::shared_ptr<Texture2D>& get_color_texture(unsigned int binding_point);
    std::shared_ptr<Texture2D>& get_color_texture_in_use() const;

    unsigned int get_current_draw_buffer() const;
    void set_current_draw_buffer(unsigned int color_attachment);

    static const unsigned int MAX_NUM_COLOR_TEXTURE = 10;

private:
    unsigned int m_width;
    unsigned int m_height;
    GLuint m_fbo;

    std::vector<std::shared_ptr<Texture2D>> m_color_textures;
    std::shared_ptr<Texture2D> m_depth_texture;

    unsigned int m_current_drawbuffer;
    std::vector<GLenum> m_drawbuffers;
};

}
