#include <iostream>

#include "framebuffer.h"
#include "renderstate.h"

namespace Cluster{
FrameBuffer::
FrameBuffer(unsigned int width, unsigned int height):
  m_width(width),
  m_height(height),
  m_color_textures(MAX_NUM_COLOR_TEXTURE, nullptr)
{
  glGenFramebuffers(1, &m_fbo);
}

FrameBuffer::~FrameBuffer()
{
  glDeleteFramebuffers(1, &m_fbo);
}

void FrameBuffer::
bind(const Usage usage) const noexcept
{
    glBindFramebuffer(usage, m_fbo);

    if (usage == Usage::NORMAL)
    {
      RenderState::set_current_framebuffer(this);
    }
}

void FrameBuffer::
release() const noexcept
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::
check_status() const noexcept
{
  GLuint status = glCheckNamedFramebufferStatus(m_fbo, GL_FRAMEBUFFER);
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
enable_color(GLenum mode)
{
  glReadBuffer(mode);
  glDrawBuffer(mode);
}

void FrameBuffer::
disable_color()
{
  glReadBuffer(GL_NONE);
  glDrawBuffer(GL_NONE);
}

void FrameBuffer::
resize(const unsigned int width, const unsigned int height)
{
  glDeleteFramebuffers(1, &m_fbo);
  create(width, height);
}

void FrameBuffer::
reset()
{
  std::fill(m_color_textures.begin(), m_color_textures.end(), nullptr);
  m_depth_texture = nullptr;
  m_width = m_height = 0;
  glDeleteFramebuffers(1, &m_fbo);
  m_fbo = -1;
}

void FrameBuffer::
create(const unsigned int width, const unsigned int height)
{
  m_width = width;
  m_height = height;
  glGenFramebuffers(1, &m_fbo);
}

void FrameBuffer::
attach_texture(GLuint attachment,
               std::shared_ptr<Texture2D> texture,
               unsigned int mipmap_level)
{
    glNamedFramebufferTexture(m_fbo, attachment, texture->get_ID(), mipmap_level);
}

void FrameBuffer::
attach_color_texture(unsigned int binding_point,
                     std::shared_ptr<Texture2D> texture,
                     unsigned int mipmap_level)
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
attach_depth_texture(std::shared_ptr<Texture2D> texture)
{
  attach_texture(GL_DEPTH_ATTACHMENT, texture, 0);
}

void FrameBuffer::
attach_depth_stencil_texture(std::shared_ptr<Texture2D> texture)
{
  attach_texture(GL_DEPTH_STENCIL_ATTACHMENT, texture, 0);
}

void FrameBuffer::
set_cubemap(GLenum attachment_target,
            TextureCubemap& texture_cubemap,
            GLint mipmap_level)
{
    for (int i = 0; i < 6; ++i)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               attachment_target,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                               texture_cubemap.get_ID(),
                               mipmap_level);
    }
}

std::shared_ptr<Texture2D>& FrameBuffer::
get_color_texture(unsigned int binding_point)
{
  return m_color_textures[binding_point];
}
}
