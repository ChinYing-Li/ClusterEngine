#include <experimental/filesystem>

#include "renderpass/Irenderpass.h"
#include "glfoundation/scene.h"
#include "glfoundation/texturemanager.h"

#include "deferred.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
extern fs::path shader_dir;
float Deferred::m_poly_offset_factor = 3.0;

Deferred::
Deferred():
  PipelineBase()
{
  m_gbuffer = std::make_unique<GBuffer>(800, 600);
  fs::path world_vert = shader_dir / fs::path("position.vert");
  fs::path quad_vert = shader_dir / fs::path("quad.vert");

  try
  {
    m_shaders.insert({Shader::GBUFFER, std::make_unique<Shader>(world_vert, shader_dir / fs::path("gbuffer.frag"))});
    m_shaders.insert({Shader::SHADOW, std::make_unique<Shader>(world_vert, shader_dir / fs::path("shadow.frag"))});
    // TODO: write texture.frag
    m_shaders.insert({Shader::TEXTURE, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("texture.frag"))});
  }
  catch (std::exception& excp)
  {
    // TODO:
    throw;
  }
}

void Deferred::
setup(unsigned int width, unsigned int height, Scene& scene)
{
  std::shared_ptr<LightingPass> light_pass = std::make_shared<LightingPass>();
  light_pass->set_gbuffer(m_gbuffer);

  m_renderstate.gl_enable(GL_Capability::CULL);
  render_shadow_maps(scene);
}

void Deferred::
resize(unsigned int width, unsigned int height)
{
  PipelineBase::resize(width, height);
  m_gbuffer = std::make_shared<GBuffer>(m_width, m_height);
  create_backbuffer(width, height);

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
render_scene(const Shader& shader, const Scene& scene)
{

}

void Deferred::
render_objects(const Shader& shader, const Scene& scene)
{

}

void Deferred::update_frame(const Scene &scene)
{
  gl_debug();
  m_renderstate.set_clear_color(glm::vec4(1.0, 0.0, 1.0, 0.4));
  render_shadow_maps(scene);
  render_gbuffer(scene);

  // High dynamic range rendering
  m_hdr_framebuffer.bind(FrameBuffer::NORMAL);
  for(const std::shared_ptr<RenderPass>& pass: m_hdr_passes)
  {
    pass->set_render_target(m_hdr_framebuffer.get_color_texture(0));
    pass->render(m_renderstate, scene);
  }

  // Tonemapping
  m_tonemap_pass->set_render_target(m_hdr_framebuffer.get_color_texture(0));
  m_ldr_framebuffer.bind(FrameBuffer::DRAW);
  m_tonemap_pass->render(m_renderstate, scene);

  // Low dynamic range rendering
  for(const std::shared_ptr<RenderPass>& pass: m_ldr_passes)
  {
    pass->set_render_target(m_ldr_framebuffer.get_color_texture(0));

  }
  render_framebuffers(m_ldr_framebuffer);
}

void Deferred::
create_backbuffer(unsigned int width, unsigned int height)
{
  m_ldr_framebuffer.reset();
  m_ldr_framebuffer.create(width, height);
  m_hdr_framebuffer.reset();
  m_hdr_framebuffer.create(width, height);

  for(int i = 0; i < 2; ++i)
  {
    m_ldr_framebuffer.attach_color_texture(i, TextureManager::generate_ldr_texture(width, height));
    m_hdr_framebuffer.attach_color_texture(i, TextureManager::generate_hdr_texture(width, height));
  }

  m_ldr_framebuffer.check_status();
  m_ldr_framebuffer.release();
  m_hdr_framebuffer.check_status();
  m_hdr_framebuffer.release();
}

void Deferred::
create_shadowmaps(Scene& scene)
{
  for (auto light : scene.get_light_vec())
  {
    light->setup_shadowbuffer(m_width, m_height);
    TextureCubemap& shadowmap = light->get_shadowmap();
    switch (light->get_type())
    {
    case Light::DIRECTIONAL:
      // TODO: Light classes have their own shadowbuffer !>
      break;
    case Light::POINTLIGHT:
      break;

    }
  }
}

void Deferred::
render_gbuffer(const Scene& scene)
{
  nvtxRangePushA("Render GBuffer");

  m_renderstate.gl_enable(STENCIL_TEST);
  m_renderstate.gl_enable(DEPTH_TEST);

  glViewport(0, 0, m_width, m_height);

  m_gbuffer->bind();
  m_gbuffer_shader.use();

  glStencilMask(0xFF);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_scene(m_gbuffer_shader, scene);
  glStencilMask(0x00);

  nvtxRangePop();
}

void Deferred::
render_framebuffers(FrameBuffer& framebuffer)
{
  nvtxRangePushA("Render FrameBuffer");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glDrawBuffer(GL_BACK);
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.0, 0.5, 0.2, 1.0);

  m_texture_shader.use();
  framebuffer.get_color_texture_in_use()->bind(0);
  m_texture_shader.set_uniform1i("u_texture", 0);
  m_renderstate.draw_screen_quad();

  nvtxRangePop();
}

void Deferred::
render_depth_map(const Scene& scene)
{
  nvtxRangePushA("DEPTH");

  m_renderstate.gl_enable(DEPTH_TEST);
  m_shadow_shader.use();

  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  glClear(GL_DEPTH_BUFFER_BIT);
  render_scene(m_shadow_shader, scene);
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

  nvtxRangePop();
}

void Deferred::
render_shadow_maps(const Scene& scene)
{
  nvtxRangePushA("Render Shadow maps");

  m_renderstate.gl_enable(DEPTH_TEST);
  m_renderstate.gl_enable(POLYGON_OFFSET_FILL);

  glPolygonOffset(m_poly_offset_factor, m_poly_offset_units);
  glDepthMask(GL_TRUE);

  for(auto light_ptr: scene.get_light_vec())
  {

  }
}
}
