#pragma once

#include "framebuffer.h"
#include "gaussianblurpass.h"
#include "renderpass.h"
#include "shader.h"
#include "sumpass.h"

namespace Cluster
{
class BloomPass : public RenderPass
{
public:
  BloomPass();
  void resize(const unsigned int win_width, const unsigned int win_height) override;
  void render(RenderState& r_state, const Scene& scene) override;

  static const std::string m_pass_name;

private:
  SumPass m_sumpass;
  GaussianBlurPass m_blurpass;
  Shader m_shader;
  FrameBuffer m_fbuffer;
};
}
