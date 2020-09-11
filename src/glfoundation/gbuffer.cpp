#include "gbuffer.h"

GBuffer::GBuffer()
{
    init();
}

void GBuffer::init()
{
    m_albedo_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_depth_stencil_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_normal_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_position_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_emission_texture_ptr = std::make_unique<Texture2D>(nullptr);

    setup_texture(m_albedo_texture_ptr, m_width, m_height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
    setup_texture(m_depth_stencil_texture_ptr, m_width, m_height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8);
    setup_texture(m_position_texture_ptr, m_width, m_height, GL_RGBA32F, GL_RGBA, GL_FLOAT);
    setup_texture(m_normal_texture_ptr, m_width, m_height, GL_RGBA16, GL_RGBA, GL_UNSIGNED_BYTE);
    setup_texture(m_emission_texture_ptr, m_width, m_height, GL_RGBA16F, GL_RGBA, GL_FLOAT);

    m_framebuffer.b
}

void GBuffer::
setup_texture(std::unique_ptr<Texture2D>& texture,
              unsigned int width, unsigned int height,
              GLint internal_format,
              GLenum format,
              GLenum type)
{
  texture->bind(0);
  texture->set_dimensions(width, height);
  texture->set_image_param(internal_format, format, type, nullptr);
  texture->set_wrap_st(GL_CLAMP, GL_CLAMP);
  texture->set_sampling(GL_NEAREST, GL_NEAREST);
}
