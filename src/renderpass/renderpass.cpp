#include "renderpass.h"

namespace Cluster
{
RenderPass::
RenderPass(const std::string& passname) :
  m_pass_name(passname)
{}

// A private constructor not to be used.
RenderPass::
RenderPass()
{}

void RenderPass::
set_clear_color(const glm::vec3 new_clear_color) noexcept
{
    m_clear_color = new_clear_color;
}
}
