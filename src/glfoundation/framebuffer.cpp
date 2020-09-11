#include <iostream>

#include "framebuffer.h"
#include "renderstate.h"

FrameBuffer::FrameBuffer():
  m_color_textures(MAX_NUM_COLOR_TEXTURE, nullptr)
{
  init();
}

void FrameBuffer::
init()
{
    glGenFramebuffers(1, &m_FBO);
}

void FrameBuffer::
bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    RenderState::set_current_framebuffer(this);
}

void FrameBuffer::
release() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::
attach_texture(GLuint attachment, std::shared_ptr<Texture2D>& texture, unsigned int level)
{
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture->get_ID(), level);
}

void FrameBuffer::
attach_color_texture(unsigned int binding_point,
                     std::shared_ptr<Texture2D> texture,
                     GLint mipmap_level)
{
  if (binding_point > MAX_NUM_COLOR_TEXTURE)
  {
    std::cerr << "The intended binding point is at " << binding_point
              << " but the maximum allowed is at " << MAX_NUM_COLOR_TEXTURE
              << std::endl;
  }

  attach_texture(GL_COLOR_ATTACHMENT0 + binding_point, texture, mipmap_level);
}

void FrameBuffer::
attach_depth_texture(std::shared_ptr<Texture2D>& texture)
{

}

void FrameBuffer::
attach_depth_stencil_texture(std::shared_ptr<Texture2D>& texture)
{

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
