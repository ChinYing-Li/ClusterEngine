#pragma once

#include <memory>

#include "framebuffer.h"
#include "glincludes.h"
#include "texture.h"

class GBuffer
{
public:
    GBuffer() = delete;
    GBuffer(unsigned int width, unsigned int height);
    ~GBuffer();


private:
    unsigned int m_width;
    unsigned int m_height;

    void init();
    void setup_texture(std::unique_ptr<Texture2D>& texture, unsigned int width, unsigned int height,
                       GLint internal_format, GLenum format, GLenum type);
    void setup_albedo(unsigned int width, unsigned int height);
    void setup_depth_stencil(unsigned int width, unsigned int height);
    void setup_normal(unsigned int width, unsigned int height);
    void setup_position(unsigned int width, unsigned int height);
    void setup_emission(unsigned int width, unsigned int height);

    std::unique_ptr<Texture2D> m_albedo_texture_ptr;
    std::unique_ptr<Texture2D> m_depth_stencil_texture_ptr;
    std::unique_ptr<Texture2D> m_normal_texture_ptr;
    std::unique_ptr<Texture2D> m_position_texture_ptr;
    std::unique_ptr<Texture2D> m_emission_texture_ptr;

    FrameBuffer m_framebuffer; // ???
};
