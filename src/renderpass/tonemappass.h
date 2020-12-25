#pragma once

#include "renderpass.h"
#include "shader.h"

namespace Cluster
{
// Reference: https://bruop.github.io/tonemapping/
class TonemapPass : public RenderPass
{
public:
  TonemapPass();

  void resize(const unsigned int win_width, const unsigned int win_height) override {};
  void render() override;

  enum Curve
  {
    REINHARD = 0,
    ACES,
    GRAN_TURISMO, // TODO: implement this curve!!
  };

  void set_curve(TonemapPass::Curve);
  void set_exposure(const float exposure);

private:
  float m_exposure;
  static const std::string m_pass_name;
  Curve m_curve;
  Shader m_shader;
};
}
