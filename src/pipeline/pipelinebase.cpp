#include "pipelinebase.h"
#include "src/glfoundation/shader.h"

namespace Cluster
{
PipelineBase::
PipelineBase():
  m_hdr_framebuffer(800, 600),
  m_ldr_framebuffer(800, 600)
{

}

PipelineBase::
~PipelineBase()
{
  // PipelineBase is not responsible for cleaning m_cam.
}

void PipelineBase::
resize(unsigned int width, unsigned int height)
{
  m_width = width;
  m_height = height;
  m_hdr_framebuffer.resize(width, height);
  m_ldr_framebuffer.resize(width, height);
}

void PipelineBase::
set_hdr_pass(const std::shared_ptr<RenderPass> pass, const int index)
{
  set_pass(pass, m_hdr_passes, index);
}

void PipelineBase::
set_ldr_pass(const std::shared_ptr<RenderPass> pass, const int index)
{
  set_pass(pass, m_ldr_passes, index);
}

void PipelineBase::
print_hdr_pass_info() const noexcept
{
  print_info(m_hdr_passes);
}

void PipelineBase::
print_ldr_pass_info() const noexcept
{
  print_info(m_ldr_passes);
}

void PipelineBase::
set_camera_uniform(Shader& shader)
{
  if (!m_camera_ptr) return;
  m_camera_ptr->update_project_mat(m_project_mat);
  m_camera_ptr->update_view_mat(m_view_mat);
  shader.set_uniformMat4f("u_project_mat", m_project_mat);
  shader.set_uniformMat4f("u_view_mat", m_view_mat);
};

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
