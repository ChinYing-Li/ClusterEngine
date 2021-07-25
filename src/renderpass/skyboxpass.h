#pragma once

#include "renderpass.h"
#include "glfoundation/shader.h"

namespace Cluster
{
class SkyBoxPass final : public RenderPass
{
public:
    SkyBoxPass();
    ~SkyBoxPass() = default;

    void resize(const unsigned int win_width, const unsigned int win_height) override;
    void render(RenderState& r_state, const Scene& scene) override;

private:
    static std::string m_pass_name;
    Shader m_sky_shader;
    Shader m_skybox_shader;
    Shader m_texture_shader;
};
}
