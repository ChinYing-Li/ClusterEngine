#pragma once

#include <map>

#include "framebuffer.h"
#include "glincludes.h"

class RenderState
{
public:
  RenderState();

  enum GL_SETTING
  {
      GS_blend = GL_BLEND,
      GS_cull = GL_CULL_FACE,
      GS_depth_test = GL_DEPTH_TEST,
      GS_stencil_test = GL_STENCIL_TEST,
      GS_polygon_offset_fill = GL_POLYGON_OFFSET_FILL
  };

  void gl_enable(GL_SETTING setting);
  void gl_disable(GL_SETTING setting);

  void draw_screen_quad();
  GLuint get_screen_quad_handle();

  void set_clear_color(glm::vec3 &color);
  glm::mat4* get_project_transform();
  glm::mat4* get_view_transform();
  glm::mat4* get_model_transform();

  static void set_current_framebuffer(const FrameBuffer* current_framebuffer) noexcept;

private:
  GLuint m_screen_quad_ID;
  unsigned int m_active_texture_binding_point;

  glm::vec3 m_clear_color;

  glm::mat4 m_project_transform;
  glm::mat4 m_view_transform;
  glm::mat4 m_model_transform;

  std::map<GL_SETTING, bool> m_state_settings;

  static FrameBuffer* m_current_framebuffer;
};
