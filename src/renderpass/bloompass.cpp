#include "bloompass.h"

namespace Cluster
{
const std::string BloomPass::m_pass_name = "bloom";

BloomPass::
BloomPass():
  RenderPass(m_pass_name),
  m_fbuffer(800, 600)
{

}

void BloomPass::render(RenderState &r_state, const Scene &scene)
{
  r_state.gl_change_settings(m_capabilities);
  nvtxRangePushA(m_pass_name.c_str());

  glStencilFunc(GL_ALWAYS, 0, 0xFF);

  // const FrameBuffer* src_framebuffer = RenderState
  m_shader.use();
  m_render_target->bind(0);

  m_shader.set_uniform1i("u_texture", );
  m_shader.set_uniform1f("u_threshold", 0.0f);
  m_fbuffer.bind();

  r_state.draw_screen_quad();
}
}
