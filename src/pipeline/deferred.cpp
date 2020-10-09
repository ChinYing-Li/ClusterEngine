#include "deferred.h"
#include "Irenderpass.h"
#include "scene.h"

namespace Cluster{

Deferred::Deferred():
  m_gbuffer(800, 600),
  m_framebuffer(),
  m_gbuffer_shader("src/shader/model.vert", "src/shader/gbuffer.frag", "", ""),
  m_texture_shader("src/shader/quad.vert", "src/shader/texture.frag", "", ""),
  m_shadow_shader("src/shader/model.vert", "src/shader/shadow.frag", "", "")
{
}

void Deferred::
setup_pipeline(unsigned int width, unsigned int height, Scene& scene)
{
  std::shared_ptr<LightPass> light_pass = std::make_shared<LightPass>();
  light_pass->set_gbuffer(m_gbuffer);

  m_renderstate.gl_enable(RenderState::GS_cull);
  render_shadow_maps();
}

void Deferred::
resize_window(unsigned int width, unsigned int height)
{

}



void Deferred::
render_scene()
{

}
void Deferred::render_objects()
{

}

void Deferred::create_backbuffer(unsigned int width, unsigned int height)
{
  m_framebuffer.bind();
  m
}

void Deferred::create_shadowmaps(Scene& scene)
{
  for (std::shared_ptr<Light> light : scene.get_all_lights())
  {

  }
}

void Deferred::render_gbuffer()
{

}

void Deferred::render_framebuffers()
{

}

void Deferred::render_depth_map()
{

}

void Deferred::render_shadow_maps()
{

}
}
