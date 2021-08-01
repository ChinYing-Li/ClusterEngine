#include "glfoundation/camera.h"
#include "glfoundation/renderstate.h"
#include "glfoundation/shader.h"

namespace Cluster
{
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
set_camera(Shader& shader, Camera& cam)
{
  cam.load_proj_mat(m_proj_mat);
  cam.load_view_mat(m_view_mat);
  shader.set_uniformMat4f("u_proj_mat", m_proj_mat);
  shader.set_uniformMat4f("u_view_mat", m_view_mat);
  glm::vec3 cam_eye = cam.get_eye();
  shader.set_uniform3f("u_eye_position", cam_eye[0], cam_eye[1], cam_eye[2]);
}

void RenderState::
set_current_framebuffer(FrameBuffer* current_framebuffer) noexcept
{
  RenderState::m_current_framebuffer = current_framebuffer;
}

FrameBuffer* RenderState::
get_current_framebuffer()
{
  return RenderState::m_current_framebuffer;
}

} // namespace Cluster

