#include "sumpass.h"

namespace Cluster
{
const std::string SumPass::m_pass_name = "sum";

SumPass::SumPass() :
  RenderPass(m_pass_name),
  m_textures(MAX_TEXTURES, nullptr),
  m_texture_weights(MAX_TEXTURES, 0.0)
{

}

void SumPass::
resize(const unsigned int win_width, const unsigned int win_height)
{

}

void SumPass::
render(RenderState& r_state, const Scene& scene)
{
  // TODO: implement render function for SumPass
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
set_texture(const unsigned int index, std::shared_ptr<Texture2D> tex)
{
  if (index < 0 || index >= MAX_TEXTURES)
  {

  }
  m_textures[index] = tex;
}

/*
 *
 */
void SumPass::
set_texture_weight(const unsigned int index, const float weight)
{
  if (index < 0 || index >= MAX_TEXTURES)
  {

  }
  m_texture_weights[index] = weight;
}

}
