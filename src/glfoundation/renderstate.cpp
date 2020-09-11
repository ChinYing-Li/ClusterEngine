#include "renderstate.h"

RenderState::RenderState():
  m_clear_color(0.0, 1.0, 0.0)
{
  m_state_settings[GS_blend] = m_state_settings[GS_cull] = m_state_settings[GS_depth_test] \
      = m_state_settings[GS_stencil_test] = m_state_settings[GS_polygon_offset_fill] = false;

  glGenVertexArrays(1, &m_screen_quad_ID);
}

void RenderState::
gl_enable(RenderState::GL_SETTING setting)
{
  if (!m_state_settings[setting])
  {
    m_state_settings[setting] = true;
    glEnable(setting);
  }
}

void RenderState::
gl_disable(GL_SETTING setting)
{
  if (m_state_settings[setting])
  {
    m_state_settings[setting] = false;
    glDisable(setting);
  }
}

void RenderState::
draw_screen_quad()
{
  glBindVertexArray(m_screen_quad_ID);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint RenderState::
get_screen_quad_handle()
{
  return m_screen_quad_ID;
}

void RenderState::
set_clear_color(glm::vec3 &color)
{
  m_clear_color = color;
}

glm::mat4* RenderState::
get_project_transform()
{
  return &m_project_transform;
}

glm::mat4* RenderState::
get_view_transform()
{
  return &m_view_transform;
}

glm::mat4* RenderState::
get_model_transform()
{
  return &m_model_transform;
}
