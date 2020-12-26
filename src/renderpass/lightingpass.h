#pragma once

#include <memory>

#include "gbuffer.h"
#include "renderpass.h"
#include "shader.h"

namespace Cluster
{
class LightingPass final : public RenderPass
{
public:
    LightingPass();

    void resize(const unsigned int win_width, const unsigned int win_height) override;
    void render(RenderState& r_state, const Scene& scene) override;

    void set_gbuffer(std::shared_ptr<GBuffer> gbuffer_ptr);

private:
    static std::string m_pass_name;

    std::shared_ptr<GBuffer> m_gbuffer_ptr;
    Shader m_shader;
    Texture2D m_light_texture;
};

}
