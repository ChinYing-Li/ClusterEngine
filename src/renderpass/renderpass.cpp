#include "renderpass.h"

RenderPass::
RenderPass()
{

}

void RenderPass::set_clear_color(const glm::vec3 new_clear_color)
{
    m_clear_color = new_clear_color;
}
