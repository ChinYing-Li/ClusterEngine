#include <memory>

#include "forward.h"
#include "light.h"
#include "texturegenerator.h"

namespace Cluster
{
Forward::Forward(const Scene& scene):
  PipelineBase(),
  m_framebuffer(800, 600)
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Forward::
~Forward()
{

}

void Forward::resize(unsigned int width, unsigned int height)
{
    m_framebuffer = FrameBuffer(width, height);
    m_framebuffer.bind();
    m_framebuffer.attach_color_texture(0, generate_hdr_texture(width, height));

    for(int i = 0; i < 2; ++i)
    {
      delete m_hdr_back_buffers[i];
      m_hdr_back_buffers[i] = new FrameBuffer(width, height);

    }

    m_ldr_back_buffers.clear();


  glViewport(0, 0, width, height);
}

void Forward::
apply_direct_lighting(Scene &scene)
{
  glEnable(GL_BLEND);
  glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
  glDepthFunc(GL_LEQUAL);

  for(Light light: scene.m_lights)
}

void Forward::
post_processing(Scene &scene)
{
  for(int i = 1; i < 3; ++i)
  {
    for(int j = 0; j < 2; ++j)
    {
      auto texture = get_current_framebuffer()->get_color_texture(0);
    }
  }
}

void Forward::
render_skybox()
{

}

void Forward::
render_framebuffer(FrameBuffer& framebuffer)
{
    framebuffer.get_color_texture(0)->bind(0);
    m_renderstate.draw_screen_quad();

}
}
