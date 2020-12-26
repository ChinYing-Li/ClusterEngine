#include "tonemappass.h"

namespace Cluster
{
const std::string TonemapPass::m_pass_name = "tonemap";

TonemapPass::
TonemapPass() :
  RenderPass(m_pass_name)
{
  m_capabilities[GS_stencil_test] = false;
  m_capabilities[GS_depth_test] = false;
}

void TonemapPass::
render(RenderState& r_state, const Scene& scene)
{
  r_state.gl_change_settings(m_capabilities);
  nvtxRangePushA(get_pass_name().c_str());

  m_shader.use();
  m_render_target->bind(0);
  m_shader.set_uniform1i("u_input", 0);
  m_shader.set_uniform1i("u_curve", m_curve);
  m_shader.set_uniform1f("u_exposure", m_exposure);

  r_state.draw_screen_quad();
  nvtxRangePop();
};



void TonemapPass::
set_curve(TonemapPass::Curve curve)
{
  m_curve = curve;
}

void TonemapPass::
set_exposure(const float exposure)
{
  m_exposure = exposure;
}
}

