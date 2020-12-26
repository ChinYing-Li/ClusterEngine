#pragma once

#include <memory>
#include <vector>

#include "renderpass.h"

namespace Cluster
{
class SumPass final : public RenderPass
{
public:
  SumPass();

  void resize(const unsigned int win_width, const unsigned int win_height) override;
  void render(RenderState& r_state, const Scene& scene) override;

  int max_textures() const noexcept;
  void set_texture(const unsigned int index, std::shared_ptr<Texture2D> tex);
  void set_texture_weight(const unsigned int index, const float weight);
  void reset_all_textures(std::vector<std::shared_ptr<Texture2D>>& tex_vec);
  static const std::string m_pass_name;

private:
  static const unsigned int MAX_TEXTURES = 10;

  std::unique_ptr<Shader> m_shader;
  std::vector<std::shared_ptr<Texture2D>> m_textures;
  std::vector<int> m_binding_points;
  std::vector<float> m_texture_weights;
};
}
