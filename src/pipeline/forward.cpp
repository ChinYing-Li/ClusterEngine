#include "forward.h"

namespace Cluster
{
Forward::Forward(): PipelineBase()
{}

void Forward::resize_window(unsigned int width, unsigned int height)
{
    m_framebuffer = FrameBuffer(width, height);

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
