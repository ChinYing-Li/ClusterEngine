#include "forward.h"

namespace Cluster
{
Forward::Forward(): PipelineBase()
{}

void Forward::render_skybox()
{
    m_resmanager_ptr->
}

void Forward::render_framebuffer(FrameBuffer& framebuffer)
{
    framebuffer.get_color_texture(0)->bind();
    m_renderstate.draw_screen_quad();

}
}
