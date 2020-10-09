#include "pipelinebase.h"

namespace Cluster
{
PipelineBase::
PipelineBase()
{

}

void PipelineBase::
set_window_size(glm::vec2 window_size)
{
    assert(window_size.x > 0 && window_size.y > 0);
    m_window_size = window_size;
}

void PipelineBase::
set_resource_mng(std::unique_ptr<ResourceManager> resource_mng)
{
    m_resmanager_ptr = std::move(resource_mng);
}

std::unique_ptr<ResourceManager> PipelineBase::
return_resource_mng() noexcept
{
    return std::move(m_resmanager_ptr);
}

std::shared_ptr<FrameBuffer> PipelineBase::
get_current_framebuffer() noexcept
{
    return m_current_frambuffer_ptr;
}

void PipelineBase::
enable(GL_SETTING setting)
{
    m_glsetting[setting] = true;
}

void PipelineBase::
disable(GL_SETTING setting)
{
    m_glsetting[setting] = false;
}


}
