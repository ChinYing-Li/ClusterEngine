#include <memory>

#include "forward.h"
#include "texturegenerator.h"

namespace Cluster
{
Forward::Forward():
  PipelineBase(),
  m_framebuffer(800, 600)
{}

void Forward::resize_window(unsigned int width, unsigned int height)
{
    m_framebuffer = FrameBuffer(width, height);
    m_framebuffer.bind();
    m_framebuffer.attach_color_texture(0, generate_hdr_texutre(width, height));

  glViewport(0, 0, width, height);
}

void Forward::render_skybox()
{

}

void Forward::render_framebuffer(FrameBuffer& framebuffer)
{
    framebuffer.get_color_texture(0)->bind();
    m_renderstate.draw_screen_quad();

}
}
