#pragma once

#include <memory>

#include "gbuffer.h"
#include "renderpass.h"
#include "shader.h"

class LightPass final : public RenderPass
{
public:
    LightPass();

    void render() override;
    void resize() override;

    void set_gbuffer(std::shared_ptr<GBuffer> gbuffer_ptr);
    
private:
    std::shared_ptr<GBuffer> m_gbuffer_ptr;
    Shader m_shader;
    Texture2D m_light_texture;
};
