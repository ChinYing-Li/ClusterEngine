#pragma once

#include <memory>

#include "framebuffer.h"
#include "glincludes.h"
#include "texture.h"

namespace Cluster{

    class Shader;
class GBuffer
{
public:
    GBuffer() = delete;
    GBuffer(unsigned int width, unsigned int height);
    ~GBuffer();

    void bind(Texture2D::Usage usage, Shader& shader);

private:
    unsigned int m_width;
    unsigned int m_height;

    void init();
    void setup_texture(Texture2D& texture, unsigned int width, unsigned int height,
                       GLint internal_format, GLenum format, GLenum type);

    Texture2D m_albedo_texture;
    Texture2D m_depth_stencil_texture;
    Texture2D m_normal_texture;
    Texture2D m_position_texture;
    Texture2D m_emission_texture;

    FrameBuffer m_framebuffer; // ???
};

}
