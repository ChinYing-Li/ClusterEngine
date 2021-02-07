#pragma once

#include <glm/glm.hpp>

namespace Cluster
{
class Transformation
{
public:
  Transformation();
  glm::mat4 get_matrix();
  void translate(const glm::vec4 offset);
  void rotate_x(const float angle);
  void rotate_y(const float angle);
  void rotate_z(const float angle);

  void scale_x(const float scale);
  void scale_y(const float scale);
  void scale_z(const float scale);

private:
  glm::vec4 m_position;
  glm::vec4 m_rotation;
  glm::vec4 m_scale;
};

}
