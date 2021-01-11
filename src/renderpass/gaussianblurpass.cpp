#include "gaussianblurpass.h"

namespace Cluster
{
const std::string GaussianBlurPass::m_pass_name = "blur";
const unsigned int GaussianBlurPass::m_num_blurbuffer = 6;

GaussianBlurPass::
GaussianBlurPass():
  RenderPass(m_pass_name)
{

}

void GaussianBlurPass::resize(const unsigned int width, const unsigned int height)
{
  RenderPass::resize(width, height);

}

void GaussianBlurPass::
render(RenderState &r_state, const Scene &scene)
{
  r_state.gl_change_settings(m_capabilities);

  nvtxRangePushA(m_pass_name.c_str());

  const FrameBuffer* framebuffer = r_state.get_current_framebuffer();
  m_shader.use();
  m_render_target->bind(0);
  glGenerateMipmap(GL_TEXTURE_2D);

  m_shader.set_uniform1i("u_texture", 0);
  m_shader.set_uniform1i("u_kernel_size", m_kernel_size);
  m_shader.set_uniform1i("u_horizontal", true);

  for(int i = 0; i < m_blurbuffers.size(); i+= 2)
  {

  }

  nvtxRangePop();
// TODO: Finish the render function of GaussianBlurPass
}

void GaussianBlurPass::
set_kernel_size(unsigned int kernel_size)
{
  m_kernel_size = kernel_size;
}
}
