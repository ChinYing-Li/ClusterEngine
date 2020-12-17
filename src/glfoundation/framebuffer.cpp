#include <iostream>

#include "framebuffer.h"
#include "renderstate.h"

namespace Cluster{
FrameBuffer::FrameBuffer(unsigned int width, unsigned int height):
    m_width(width),
    m_height(height),
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
bind() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    RenderState::set_current_framebuffer(this);
}

void FrameBuffer::
release() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::
check_status() const noexcept
{
  GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    switch (status)
    {
      std::cerr << "ERROR: ";

    case GL_FRAMEBUFFER_UNDEFINED:
        std::cerr << "Framebuffer undefined." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        std::cerr << "Framebuffer incomplete attachment." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        std::cerr << "Framebuffer missing attachment." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        std::cerr << "Framebuffer incomplete draw buffer." << std::endl;
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        std::cerr << "Framebuffer incomplete read buffer." << std::endl;
        break;
    default:
        std::cerr << "Frambuffer...something went wrong." << std::endl;
    }
  }
}

void FrameBuffer::
attach_texture(GLuint attachment, std::shared_ptr<Texture2D>& texture, unsigned int level)
{
    glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture->get_ID(), level);
}

void FrameBuffer::
attach_color_texture(unsigned int binding_point,
                     std::shared_ptr<Texture2D>& texture,
                     GLint mipmap_level)
{
  if (binding_point > MAX_NUM_COLOR_TEXTURE)
  {
    std::cerr << "The intended binding point is at " << binding_point
              << " but the maximum allowed is at " << MAX_NUM_COLOR_TEXTURE
              << std::endl;
  }

  attach_texture(GL_COLOR_ATTACHMENT0 + binding_point, texture, mipmap_level);
  m_color_textures[binding_point] = texture;
}

void FrameBuffer::
attach_depth_texture(std::shared_ptr<Texture2D>& texture)
{
  attach_texture(GL_DEPTH_ATTACHMENT, texture, 0);
}

void FrameBuffer::
attach_depth_stencil_texture(std::shared_ptr<Texture2D>& texture)
{
  attach_texture(GL_DEPTH_STENCIL_ATTACHMENT, texture, 0);
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

}
