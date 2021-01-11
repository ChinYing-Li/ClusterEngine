#pragma once

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
  void virtual render_scene() override;
  void virtual render_objects() override;

protected:
  void virtual create_backbuffer(unsigned int width, unsigned int height);
  void virtual create_shadowmaps(Scene& scene);

  void virtual render_gbuffer();
  void virtual render_framebuffers();
  void virtual render_depth_map();
  void virtual render_shadow_maps();

  GBuffer m_gbuffer;
  FrameBuffer m_framebuffer;

  Shader m_gbuffer_shader;
  Shader m_texture_shader;
  Shader m_shadow_shader;
};

}
