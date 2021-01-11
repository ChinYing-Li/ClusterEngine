#include "gammacorrectpass.h"

namespace Cluster
{
const std::string GammaCorrectPass::m_pass_name = "gamma";

GammaCorrectPass::GammaCorrectPass() :
  RenderPass(m_pass_name),
  m_gamma(2.2)
{
  m_capabilities[STENCIL_TEST] = false;
  m_capabilities[DEPTH_TEST] = false;
}

void GammaCorrectPass::
render(RenderState& r_state, const Scene& scene)
{
  // TODO: finish the render function of GammaCorrectPass
  r_state.gl_change_settings(m_capabilities);
  m_shader.use();
  m_render_target->bind(0);
  m_shader.set_uniform1f("u_gamma", m_gamma);
  r_state.draw_screen_quad();
}

void GammaCorrectPass::
set_gamma(const float gamma)
{
  m_gamma = gamma;
}
}

