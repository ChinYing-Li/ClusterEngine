#include "lightingpass.h"

namespace Cluster
{
std::string LightingPass::m_pass_name = "";

LightingPass::LightingPass() :
  RenderPass(m_pass_name)
{
    m_shader = Shader("shader/quad.vert", "shader/deferredlighting.frag", "", "directlight");
}

void LightingPass::set_gbuffer(std::shared_ptr<GBuffer> gbuffer)
{
    m_gbuffer_ptr = gbuffer;
}
}
