#include "gbuffer.h"

GBuffer::GBuffer()
{
    init();
}

void GBuffer::init()
{
    m_albedo_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_depth_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_normal_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_position_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_emission_texture_ptr = std::make_unique<Texture2D>(nullptr);
}

void GBuffer::
setup_albedo()
{
  m_albedo_texture_ptr = std::make_unique<Texture2D>();
  m_albedo_texture_ptr->bind(0);

}

void GBuffer::
setup_depth()
{
    m_depth_texture_ptr = std::make_unique<Texture2D>();
    m_depth_texture_ptr->bind(0);
}

void GBuffer::
setup_normal()
{
    m_normal_texture_ptr = std::make_unique<Texture2D>();
    m_normal_texture_ptr->bind(0);
}

void GBuffer::
setup_position()
{
    m_position_texture_ptr = std::make_unique<Texture2D>();
    m_position_texture_ptr->bind(0);
}

void GBuffer::
setup_emission()
{
    m_emission_texture_ptr = std::make_unique<Texture2D>();
    m_emission_texture_ptr->bind(0);
}
