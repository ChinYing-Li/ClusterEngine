#pragma once

#include <memory>

#include "glincludes.h"
#include "texture.h"

class Gbuffer
{
public:
    Gbuffer();
    ~Gbuffer();

private:
    void init();
    void setup_albedo();
    void setup_depth();
    void setup_normal();
    void setup_position();
    void setup_emission();

    std::unique_ptr<Texture2D> m_albedo_texture_ptr;
    std::unique_ptr<Texture2D> m_depth_texture_ptr;
    std::unique_ptr<Texture2D> m_normal_texture_ptr;
    std::unique_ptr<Texture2D> m_position_texture_ptr;
    std::unique_ptr<Texture2D> m_emission_texture_ptr;

    GLuint m_buffer_id; // ???
};
