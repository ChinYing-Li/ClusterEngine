#include "renderstate.h"

namespace Cluster{
RenderState::
RenderState():
  m_clear_color(0.0, 1.0, 0.0),
  m_settings(get_default_settings())
{
  glGenVertexArrays(1, &m_screen_quad_ID);
}

GL_Capabilities RenderState::get_default_settings()
{
  GL_Capabilities default_settings = {{GS_blend, false},
                                  {GS_cull, false},
                                  {GS_depth_test, false},
                                  {GS_stencil_test, false},
                                  {GS_polygon_offset_fill, false}};
  return default_settings;
}

void RenderState::
gl_enable(GL_Capability setting)
{
  if (!m_settings[setting])
  {
    m_settings[setting] = true;
    glEnable(setting);
  }
}

void RenderState::
gl_disable(GL_Capability setting)
{
  if (m_settings[setting])
  {
    m_settings[setting] = false;
    glDisable(setting);
  }
}

void RenderState::
gl_change_settings(GL_Capabilities& settings)
{
  auto it = settings.begin();

  for(int i = 0; i < m_settings.size(); ++i)
  {
    if (it->second && !m_settings[it->first])
    {
      gl_enable(it->first);
    }
    else if (!it->second && m_settings[it->first])
    {
      gl_disable(it->first);
    }
  }
}

void RenderState::
draw_screen_quad()
{
  glBindVertexArray(m_screen_quad_ID);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint RenderState::
get_screen_quad_handle() const
{
  return m_screen_quad_ID;
}

void RenderState::
set_clear_color(glm::vec3 &color)
{
  m_clear_color = color;
}

const glm::mat4* RenderState::
get_project_transform() const
{
  return &m_project_transform;
}

const glm::mat4* RenderState::
get_view_transform() const
{
  return &m_view_transform;
}

const glm::mat4* RenderState::
get_model_transform() const
{
  return &m_model_transform;
}

void RenderState::
set_current_framebuffer(const FrameBuffer* current_framebuffer) noexcept
{
  m_current_framebuffer = current_framebuffer;
}

const FrameBuffer* RenderState::
get_current_framebuffer()
{
  return m_current_framebuffer;
}

} // namespace Cluster

