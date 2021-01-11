#pragma once

#include "renderpass.h"
#include "shader.h"
#include "sumpass.h"

namespace Cluster
{
class GaussianBlurPass : public RenderPass
{
public:
  GaussianBlurPass();
  void resize(const unsigned int width, const unsigned int height) override;
  void render(RenderState& r_state, const Scene& scene) override;

  void set_kernel_size(unsigned int kernel_size);
  unsigned int get_kernel_size();
  void set_sigma(const float sigma);
  float get_sigma();

  static const std::string m_pass_name;
  static const unsigned int m_num_blurbuffer;

private:
  unsigned int m_kernel_size = 5;
  Shader m_shader;
  std::vector<Texture2D> m_blurtextures;
  std::vector<FrameBuffer> m_blurbuffers;
  SumPass m_sumpass;
};
}
