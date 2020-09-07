#include "gbuffer.h"

Gbuffer::Gbuffer()
{
    init();
}

void Gbuffer::init()
{
    m_albedo_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_depth_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_normal_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_position_texture_ptr = std::make_unique<Texture2D>(nullptr);
    m_emission_texture_ptr = std::make_unique<Texture2D>(nullptr);
}

void Gbuffer::
setup_albedo()
{

}

void Gbuffer::
setup_depth()
{
    m_depth_texture_ptr = std::make_unique<Texture2D>();
}

void Gbuffer::setup_normal()
{
    m_normal_texture_ptr = std::make_unique<Texture2D>();
}

void Gbuffer::
setup_position()
{
    m_position_texture_ptr = std::make_unique<Texture2D>();
}

void Gbuffer::
setup_emission()
{
    m_emission_texture_ptr = std::make_unique<Texture2D>();
}
