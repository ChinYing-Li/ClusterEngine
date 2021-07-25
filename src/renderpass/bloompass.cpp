#include <experimental/filesystem>

#include "bloompass.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
const std::string BloomPass::m_pass_name = "bloom";

BloomPass::
BloomPass():
  RenderPass(m_pass_name),
  m_fbuffer(800, 600),
  m_shader(RenderPass::SHADER_ROOT / "quad.vert", RenderPass::SHADER_ROOT / "bloom.frag")
{
  try
  {
    RenderPass::init();
  }
  catch (const std::exception& e)
  {
    throw e;
  }

}

void BloomPass::
resize(const unsigned int win_width, const unsigned int win_height)
{
  // TODO
}

void BloomPass::
render(RenderState &r_state, const Scene &scene)
{
  r_state.gl_change_settings(m_capabilities);
  nvtxRangePushA(m_pass_name.c_str());

  glStencilFunc(GL_ALWAYS, 0, 0xFF);

  const FrameBuffer* src_framebuffer = RenderState::get_current_framebuffer();
  m_shader.use();
  m_render_target_ptr->bind(0);

  m_shader.set_uniform1i("u_texture", 0);
  m_shader.set_uniform1f("u_threshold", 0.0f);
  m_fbuffer.bind(FrameBuffer::Usage::NORMAL);

  r_state.draw_screen_quad();

  // TODO: Finish the logic

  nvtxRangePop();
}
}
