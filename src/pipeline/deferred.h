#pragma once

#include <memory>

#include "framebuffer.h"
#include "gbuffer.h"
#include "pipelinebase.h"
#include "renderstate.h"
#include "shader.h"

namespace Cluster {

class Scene;

class Deferred : public PipelineBase
{
public:
  Deferred();

  void virtual setup(unsigned int width, unsigned int height, Scene& scene) override;
  void virtual resize(unsigned int width, unsigned int height) override;
  void virtual render_scene(const Shader& shader, const Scene& scene) override;
  void virtual render_objects(const Shader& shader, const Scene& scene) override;

protected:
  static float m_poly_offset_factor;
  static float m_poly_offset_units;

  void virtual create_backbuffer(unsigned int width, unsigned int height);
  void virtual create_shadowmaps(Scene& scene);

  void virtual render_gbuffer();
  void virtual render_framebuffers(const FrameBuffer& framebuffe);
  void virtual render_depth_map(const Scene& scene);
  void virtual render_shadow_maps(const Scene& scene);

  std::shared_ptr<GBuffer> m_gbuffer;

  Shader m_gbuffer_shader;
  Shader m_texture_shader;
  Shader m_shadow_shader;
};

}
