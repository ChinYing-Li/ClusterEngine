#include "renderstate.h"

namespace Cluster{
RenderState::
RenderState():
  m_clear_color(glm::vec4(1.0, 0.0, 0.0, 1.0)),
  m_settings(get_default_settings())
{
  glGenVertexArrays(1, &m_screen_quad_ID);
}

GL_Capabilities RenderState::get_default_settings()
{
  GL_Capabilities default_settings =
  {
    {BLEND, false},
    {CULL, false},
    {DEPTH_TEST, false},
    {STENCIL_TEST, false},
    {POLYGON_OFFSET_FILL, false}
  };
  return default_settings;
}

// TODO: Seriously, I don't think these two functions are useful
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
set_clear_color(const glm::vec4 &color)
{
  m_clear_color = color;
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

