#pragma once

#include <map>

#include "framebuffer.h"
#include "glincludes.h"

namespace Cluster{
class Shader;
class Camera;

enum GL_Capability
{
    BLEND = GL_BLEND,
    CULL = GL_CULL_FACE,
    DEPTH_TEST = GL_DEPTH_TEST,
    STENCIL_TEST = GL_STENCIL_TEST,
    POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL
};

typedef std::map<GL_Capability, bool> GL_Capabilities;

class RenderState
{
public:
  RenderState();
  void gl_enable(GL_Capability setting);
  void gl_disable(GL_Capability setting);
  void gl_change_settings(GL_Capabilities& setting);

  void draw_screen_quad();
  GLuint get_screen_quad_handle() const;

  void set_clear_color(const glm::vec4 &color);

  static GL_Capabilities get_default_settings();
  const glm::mat4* get_project_transform() const;
  const glm::mat4* get_view_transform() const;
  const glm::mat4* get_model_transform() const;

  static void set_current_framebuffer(const FrameBuffer* current_framebuffer) noexcept;
  static const FrameBuffer* get_current_framebuffer();

private:
  GLuint m_screen_quad_ID;
  unsigned int m_active_texture_binding_point;
  glm::vec4 m_clear_color;
  GL_Capabilities m_settings;
  const static FrameBuffer* m_current_framebuffer;
};

} // namespace Cluster
