#pragma once

#include "shader.h"

class SkyBoxPass
{
public:
    SkyBoxPass();
    ~SkyBoxPass();

private:
    Shader m_sky_shader;
    Shader m_skybox_shader;
    Shader m_texture_shader;
};
