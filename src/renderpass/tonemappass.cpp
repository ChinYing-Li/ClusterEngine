#include "tonemappass.h"

namespace Cluster
{
const std::string TonemapPass::m_pass_name = "tonemap";

TonemapPass::
TonemapPass() :
  RenderPass(m_pass_name)
{

}

void TonemapPass::
render()
{
  m_shader.use();

}


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

