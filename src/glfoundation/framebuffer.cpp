#include "src/glfoundation/framebuffer.h"

void FrameBuffer::
init()
{
    glGenFramebuffers(1, &m_FBO);
}

void FrameBuffer::
bind(GLenum binding_target) const
{
    glBindFramebuffer(binding_target, m_FBO);
}

void FrameBuffer::
release() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::
set_texture2D(GLenum attachment_target, std::shared_ptr<Texture2D> texture_ptr, GLint level)
{
    glFramebufferTexture(GL_FRAMEBUFFER, attachment_target, texture_ptr->get_ID(), 0);
}

void FrameBuffer::
set_cubemap(GLenum attachment_target,
            std::shared_ptr<TextureCubemap> texture_cubemap,
            GLint mipmap_level)
{
    for (int i = 0; i < 6; ++i)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               attachment_target,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                               texture_cubemap->get_ID(),
                               mipmap_level);
    }
}
