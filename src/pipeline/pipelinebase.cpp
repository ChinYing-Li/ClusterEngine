#include "pipelinebase.h"

namespace Cluster
{
PipelineBase::
PipelineBase():
  m_current_frambuffer(800, 600)
{

}

PipelineBase::
~PipelineBase()
{
  for(FrameBuffer* fb_ptr: m_hdr_back_buffers)
  {
    delete fb_ptr;
  }

  for(FrameBuffer* fb_ptr: m_ldr_back_buffers)
  {
    delete fb_ptr;
  }
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

const FrameBuffer* PipelineBase::
get_current_framebuffer() const noexcept
{
    return &m_current_frambuffer;
}

void PipelineBase::
set_hdr_pass(const std::shared_ptr<RenderPass> pass, const int index)
{
  set_pass(pass, m_hdr_passes, index);
}

void PipelineBase::
set_ldr_pass(const std::shared_ptr<RenderPass> pass, const int index)
{
  set_pass(pass, m_passes, index);
}

void PipelineBase::
print_hdr_pass_info() const noexcept
{
  print_info(m_hdr_passes);
}

void PipelineBase::
print_ldr_pass_info() const noexcept
{
  print_info(m_passes);
}

void PipelineBase::
set_pass(const std::shared_ptr<RenderPass> pass, std::vector<std::shared_ptr<RenderPass>>& passes, const int index)
{
  if(index == -1)
  {
    passes.push_back(pass);
  }
  else
  {
    assert(index < passes.size());
    passes[index] = pass;
  }
}

void PipelineBase::
print_info(const std::vector<std::shared_ptr<RenderPass>>& passes) const noexcept
{
    for(auto pass: passes)
    {
      std::cout << pass->get_pass_name() << std::endl;
    }
}

void PipelineBase::
reset_backbuffer(std::vector<FrameBuffer*>& back_buffer)
{
  for (FrameBuffer* ptr: back_buffer)
  {
    delete ptr;
    ptr = nullptr;
  }
  back_buffer.clear();
}
}
