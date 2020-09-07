#pragma once

#include <memory>
#include <vector>

#include "glincludes.h"
#include "texture.h"

class FrameBuffer
{
public:
    FrameBuffer() = default;

    ~FrameBuffer()
    {
        glDeleteFramebuffers(1, &m_FBO);
    };


    void bind(GLenum binding_target) const;
    void release() const;
    void check_status() const;

    void set_texture2D(GLenum attachment_target, std::shared_ptr<Texture2D> texture, GLint mipmap_level);
    void set_cubemap(GLenum attachment_target, std::shared_ptr<TextureCubemap> texture_cubemap, GLint mipmap_level);
    void set_parameter(GLenum binding_target, GLenum param_name, GLint param_val);

private:
    void init();
    GLuint m_FBO;

    std::vector<Texture2D> m_color_texture;
};
