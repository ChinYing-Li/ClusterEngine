#pragma once

#include "renderpass.h"
#include "shader.h"

class SkyBoxPass final : public RenderPass
{
public:
    SkyBoxPass();
    ~SkyBoxPass() = default;

    void resize() override;
    void render() override;

private:
    void setup();
    Shader m_sky_shader;
    Shader m_skybox_shader;
    Shader m_texture_shader;
};
