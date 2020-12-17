#include "lightpass.h"

LightPass::LightPass()
{
    m_shader = Shader("shader/quad.vert", "shader/deferredlighting.frag", "", "directlight");

}

void LightPass::set_gbuffer(std::shared_ptr<GBuffer> gbuffer)
{
    m_gbuffer_ptr = gbuffer;
}

