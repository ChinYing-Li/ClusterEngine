#include "sumpass.h"

namespace Cluster
{
const std::string SumPass::m_pass_name = "sum";

SumPass::SumPass() :
  RenderPass(m_pass_name),
  m_textures(MAX_TEXTURES, nullptr),
  m_binding_points(MAX_TEXTURES, 0),
  m_texture_weights(MAX_TEXTURES, 0.0)
{
  for(int i = 0; i < MAX_TEXTURES; ++i)
  {
    m_binding_points[i] = i;
  }
}

void SumPass::
resize(const unsigned int win_width, const unsigned int win_height)
{}

void SumPass::
render(RenderState& r_state, const Scene& scene)
{
  nvtxRangePushA(m_pass_name.c_str());
  m_shader.use();

  for(size_t i = 0; i < m_num_textures_to_use; ++i)
  {
    m_textures[i]->bind(i);
  }

  m_shader.set_uniform1i("u_num_textures", m_num_textures_to_use);
  m_shader.set_uniform1iv("u_textures", m_num_textures_to_use, m_binding_points);
  m_shader.set_uniform1fv("u_weights", m_num_textures_to_use, m_texture_weights);
  r_state.draw_screen_quad();

  nvtxRangePop();
}

int SumPass::
max_textures() const noexcept
{
  return MAX_TEXTURES;
}

/*
 *
 */
void SumPass::
set_texture(const unsigned int index, Texture2D& tex)
{
  assert(index < MAX_TEXTURES);
  m_textures[index] = &tex;
}

void SumPass::
set_num_texture_to_use(const unsigned int num_texture)
{
  m_num_textures_to_use = std::min(MAX_TEXTURES, num_texture);
}

/*
 *
 */
void SumPass::
set_texture_weight(const unsigned int index, const float weight)
{
  assert(index < MAX_TEXTURES);
  m_texture_weights[index] = weight;
}

}
