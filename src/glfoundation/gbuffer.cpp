#include "gbuffer.h"

namespace Cluster{

GBuffer::GBuffer(unsigned int width, unsigned int height):
  m_albedo_texture(),
  m_depth_stencil_texture(),
  m_normal_texture(),
  m_position_texture(),
  m_emission_texture(),
  m_framebuffer(width, height)
{
  init();
}

GBuffer::~GBuffer()
{}

void GBuffer::init()
{
    setup_texture(m_albedo_texture, m_width, m_height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
    setup_texture(m_depth_stencil_texture, m_width, m_height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);
    setup_texture(m_position_texture, m_width, m_height, GL_RGBA32F, GL_RGBA, GL_FLOAT);
    setup_texture(m_normal_texture, m_width, m_height, GL_RGBA16, GL_RGBA, GL_UNSIGNED_BYTE);
    setup_texture(m_emission_texture, m_width, m_height, GL_RGBA16F, GL_RGBA, GL_FLOAT);

    m_framebuffer.bind();
    m_framebuffer.attach_depth_stencil_texture(m_depth_stencil_texture);
    m_framebuffer.attach_color_texture(0, m_albedo_texture, 0);
    m_framebuffer.attach_color_texture(1, m_position_texture, 0);
    m_framebuffer.attach_color_texture(2, m_normal_texture, 0);
    m_framebuffer.attach_color_texture(3, m_emission_texture, 0);
}

void GBuffer::
setup_texture(Texture2D& texture,
              unsigned int width, unsigned int height,
              GLint internal_format,
              GLenum format,
              GLenum type)
{
  texture.bind(0);
  texture.set_dimensions(width, height);
  texture.set_texture_param(internal_format, format, type, nullptr);
  texture.set_wrapping(GL_CLAMP, GL_CLAMP);
  texture.set_magmin_filter(GL_NEAREST, GL_NEAREST);
}

}

