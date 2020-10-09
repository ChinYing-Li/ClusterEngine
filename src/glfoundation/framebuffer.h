#pragma once

#include <memory>
#include <vector>

#include "glincludes.h"
#include "texture.h"

namespace Cluster{
class FrameBuffer
{
public:
    FrameBuffer();

    ~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_FBO);
    };

    void bind() const noexcept;
    void release() const noexcept;
    void check_status() const noexcept;

    void attach_texture(GLuint attachment, std::shared_ptr<Texture2D>& texture, unsigned int mipmap_level);
    void attach_color_texture(unsigned int binding_point, std::shared_ptr<Texture2D>& texture, GLint mipmap_level);
    void attach_depth_texture(std::shared_ptr<Texture2D>& texture);
    void attach_depth_stencil_texture(std::shared_ptr<Texture2D>& texture);

    void set_cubemap(GLenum attachment, std::shared_ptr<TextureCubemap> texture_cubemap, GLint mipmap_level);
    void set_parameter(GLenum binding_target, GLenum param_name, GLint param_val);

    // add drawbuffer and read buffer??

    std::shared_ptr<Texture2D> get_color_texture(unsigned int binding_point);
    std::shared_ptr<Texture2D> get_color_texture_in_use();

    static const unsigned int MAX_NUM_COLOR_TEXTURE = 10;

private:
    GLuint m_FBO;

    std::vector<std::shared_ptr<Texture2D>> m_color_textures;
    std::shared_ptr<Texture2D> m_depth_texture;

    unsigned int m_current_drawbuffer;
    std::vector<GLenum> m_drawbuffers;

    void init();
};

}
