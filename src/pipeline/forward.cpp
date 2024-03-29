#include <experimental/filesystem>
#include <memory>

#include "pipeline/forward.h"
#include "glfoundation/light.h"
#include "glfoundation/scene.h"
#include "glfoundation/texturemanager.h"

#include "utilities/debug/debug.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
extern const fs::path shader_dir;
const glm::vec4 Forward::M_CLEAR_COLOR = glm::vec4(1.0, 0.0, 1.0, 1.0);

Forward::
Forward(const Scene& scene):
  PipelineBase::PipelineBase(),
  m_framebuffer(800, 600)
{
  m_renderstate.gl_enable(DEPTH_TEST);
  m_renderstate.gl_enable(CULL);
  glCullFace(GL_BACK);

  fs::path world_vert = shader_dir / fs::path("position.vert");
  fs::path quad_vert = shader_dir / fs::path("quad.vert");

  try
  {
    m_shaders.insert({Shader::BLOOM, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("bloom.frag"))});
    m_shaders.insert({Shader::BLUR, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("blur.frag"))});
    m_shaders.insert({Shader::DIRECT_LIGHTING, std::make_unique<Shader>(world_vert, shader_dir / fs::path("lighting.frag"))});
    m_shaders.insert({Shader::GAMMA_CORRECT, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("gammacorrect.frag"))});
    // TODO: check the implementation of the skybox vertex shader;
    m_shaders.insert({Shader::SKYBOX, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("skybox.frag"))});
    m_shaders.insert({Shader::TONEMAP, std::make_unique<Shader>(quad_vert, shader_dir / fs::path("tonemap.frag"))});
  }
  catch (std::exception& excp)
  {
    // TODO:
    throw;
  }
}


void Forward::
resize(unsigned int width, unsigned int height)
{
    m_framebuffer.reset();
    m_framebuffer.create(width, height);
    m_framebuffer.bind(FrameBuffer::NORMAL);
    m_framebuffer.attach_color_texture(0, TextureManager::generate_hdr_texture(width, height));
    m_framebuffer.attach_depth_texture(TextureManager::generate_empty_depth_map(width, height));
    m_framebuffer.check_status();
    m_framebuffer.release();

    for(FrameBuffer& buffer: m_hdr_back_buffers)
    {
      buffer.reset();
      buffer.create(width, height);
      buffer.attach_color_texture(0, TextureManager::generate_hdr_texture(width, height));
      buffer.check_status();
      buffer.release();
    }

    for(FrameBuffer& buffer: m_ldr_back_buffers)
    {
      buffer.reset();
      buffer.create(width, height);
      buffer.attach_color_texture(0, TextureManager::generate_ldr_texture(width, height));
      buffer.check_status();
      buffer.release();
    }

  m_renderstate.set_clear_color(M_CLEAR_COLOR);
  glViewport(0, 0, width, height);
}

void Forward::
render_scene(const Shader &shader, Scene &scene)
{
  // TODO: set the lights
  for(int i = 0; i < scene.object_count(); ++i)
  {
    std::shared_ptr<Renderable> object = scene.get_object(i);
    object->render(shader);
  }
}

    void Forward::
    render_objects(const Shader& shader, const Scene& scene)
    {

    }

void Forward::
update_frame(Scene &scene)
{
  gl_debug();
  m_hdr_framebuffer.bind(FrameBuffer::NORMAL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render_skybox(scene);
  post_processing(scene);

  m_framebuffer.release();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  render_framebuffer(*RenderState::get_current_framebuffer());
}

void Forward::
apply_direct_lighting(Scene &scene)
{
  glEnable(GL_BLEND);
  glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
  glDepthFunc(GL_LEQUAL);

  m_shaders.at(Shader::DIRECT_LIGHTING)->use();
  for(int i = 0; i < scene.light_count(); ++i)
  {
      std::shared_ptr<Light> light = scene.get_light(i);
    switch (light->get_type()) {
    case Light::POINTLIGHT:

      break;
    case Light::DIRECTIONAL:
      break;

    default:
      break;
    }
  }
  m_renderstate.gl_disable(GL_Capability::BLEND);
}

void Forward::
post_processing(const Scene& scene)
{
  nvtxRangePushA("Post processing");

  m_shaders[Shader::BLOOM]->use();
  m_shaders[Shader::BLOOM]->set_uniform1f("u_threshold", 0.0);
  m_shaders[Shader::BLOOM]->set_uniform1i("u_texture", 0);
  m_renderstate.draw_screen_quad();

  FrameBuffer* current_framebuffer_ptr = m_renderstate.get_current_framebuffer();

  for(int i = 1; i < 3; ++i)
  {
    for(int j = 0; j < 2; ++j)
    {
      auto texture = current_framebuffer_ptr->get_color_texture(0);
      texture->bind(0);
      glGenerateMipmap(GL_TEXTURE_2D);
      m_shaders[Shader::BLUR]->use();
      m_shaders[Shader::BLUR]->set_uniform1i("u_texture", 0);
      // TODO: Complete tbe implementation
      // m_shaders[Shader::BLUR]->set_uniform2f("u_horizontal", )
      m_renderstate.draw_screen_quad();
    }
  }

  nvtxRangePop();
}

void Forward::
render_skybox(Scene& scene)
{
  nvtxRangePushA("Render skybox");

  m_shader_ins[Shader::SKYBOX].use();
  Cubemap* skybox = scene.get_skybox();
  skybox->render(m_shader_ins[Shader::SKYBOX]);

  nvtxRangePop();
}

void Forward::
render_framebuffer(FrameBuffer& framebuffer)
{
    auto tex = framebuffer.get_color_texture(0);
    tex->bind(0);
    m_renderstate.draw_screen_quad();
}
}
