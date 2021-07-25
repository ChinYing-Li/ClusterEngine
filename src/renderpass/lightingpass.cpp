#include "lightingpass.h"

namespace Cluster
{
const std::string LightingPass::m_pass_name = "lighting";

LightingPass::LightingPass() :
  RenderPass(m_pass_name),
  m_shader(RenderPass::SHADER_ROOT / "quad.vert", RenderPass::SHADER_ROOT / "deferredlighting.frag")
{
}

void LightingPass::set_gbuffer(std::shared_ptr<GBuffer> gbuffer)
{
    m_gbuffer_ptr = gbuffer;
}
}
