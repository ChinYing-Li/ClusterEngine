#pragma once

#include "renderpass.h"
#include "shader.h"

namespace Cluster
{
class SkyBoxPass final : public RenderPass
{
public:
    SkyBoxPass();
    ~SkyBoxPass() = default;

    void resize() override;
    void render() override;

private:
    void setup();

    static std::string m_pass_name;
    Shader m_sky_shader;
    Shader m_skybox_shader;
    Shader m_texture_shader;
};
}
