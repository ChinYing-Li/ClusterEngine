#include "deferred.h"
#include "Irenderpass.h"
#include "scene.h"

namespace Cluster{

float Deferred::m_poly_offset_factor = 3.0;

Deferred::Deferred():
  m_gbuffer(800, 600),
  m_framebuffer(800, 600),
  m_gbuffer_shader("src/shader/model.vert", "src/shader/gbuffer.frag", "", ""),
  m_texture_shader("src/shader/quad.vert", "src/shader/texture.frag", "", ""),
  m_shadow_shader("src/shader/model.vert", "src/shader/shadow.frag", "", "")
{
}

void Deferred::
setup(unsigned int width, unsigned int height, Scene& scene)
{
  std::shared_ptr<LightingPass> light_pass = std::make_shared<LightingPass>();
  light_pass->set_gbuffer(m_gbuffer);

  m_renderstate.gl_enable(GL_Capability::CULL);
  render_shadow_maps();
}

void Deferred::
resize(unsigned int width, unsigned int height)
{
  m_width = width; m_height = height;
  m_gbuffer = std::make_shared<GBuffer>(m_width, m_height);

  for(auto pass_ptr: m_hdr_passes)
  {
    pass_ptr->resize(m_width, m_height);
  }

  for(auto pass_ptr: m_ldr_passes)
  {
    pass_ptr->resize(m_width, m_height);
  }
}



void Deferred::
render_scene(const Scene& scene)
{

}
void Deferred::render_objects()
{

}

void Deferred::create_backbuffer(unsigned int width, unsigned int height)
{
  m_framebuffer.bind(FrameBuffer::NORMAL);
  m_framebuffer.attach_color_texture(0, );
  m_framebuffer.attach_color_texture(1, );
  m_framebuffer.attach_depth_stencil_texture();
}

void Deferred::create_shadowmaps(Scene& scene)
{
  for (auto light : scene.get_light_vec())
  {
    if (light->get_type() == Light::Type::DIRECTIONAL)
    {
      // light->m_shadowbuffer.;

    }
  }
}

void Deferred::render_gbuffer()
{
  m_renderstate.gl_enable(STENCIL_TEST);
  m_renderstate.gl_enable(DEPTH_TEST);

  glViewport(0, 0, m_width, m_height);

  m_gbuffer->bind();
  m_gbuffer_shader.use();

  glStencilMask(0xFF);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_scene();
  glStencilMask(0x00);
}

void Deferred::render_framebuffers(const FrameBuffer& framebuffer)
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDrawBuffer(GL_BACK);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 0.5, 0.2, 1.0);

  m_texture_shader.use();
  m_framebuffer.get_color_texture_in_use().bind(0);
  m_texture_shader.set_uniform1i("u_texture", 0);
  m_renderstate.draw_screen_quad();
}

void Deferred::render_depth_map(const Scene& scene)
{
  nvtxRangePushA("DEPTH");

  m_renderstate.gl_enable(DEPTH_TEST);
  m_shadow_shader.use();

  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glClear(GL_DEPTH_BUFFER_BIT);
  render_scene(scene, m_shadow_shader);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  nvtxRangePop();
}

void Deferred::render_shadow_maps(const Scene& scene)
{
  nvtxRangePushA("DEPTH");

  m_renderstate.gl_enable(DEPTH_TEST);
  m_renderstate.gl_enable(POLYGON_OFFSET_FILL);

  glPolygonOffset(m_poly_offset_factor, m_poly_offset_units);
  glDepthMask(GL_TRUE);

  for(auto light_ptr: scene.get_light_vec())
  {

  }
}
}
