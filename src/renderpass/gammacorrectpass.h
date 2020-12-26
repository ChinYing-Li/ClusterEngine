#pragma once

#include "renderpass.h"
#include "shader.h"

namespace Cluster
{
class GammaCorrectPass : public RenderPass
{
public:
  GammaCorrectPass();

  void resize(const unsigned int win_width, const unsigned int win_height) override {};
  void render(RenderState& r_state, const Scene& scene) override;

  void set_gamma(const float gamma);

  static const std::string m_pass_name;

private:
  float m_gamma;
  Shader m_shader;
};

}
