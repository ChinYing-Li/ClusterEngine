#pragma once

#include <glm/glm.hpp>

namespace Cluster
{

class Transformation
{
public:
  Transformation();

  void translate(const glm::vec4 offset);
  void rotate_x(const float angle);
  void rotate_y(const float angle);
  void rotate_z(const float angle);

  void scale_x(const float scale);
  void scale_y(const float scale);
  void scale_z(const float scale);

  const glm::mat4& get_matrix();
  const glm::vec3& get_position();
  const glm::vec3& get_rotation();
  const glm::vec3& get_scale();

private:
  glm::mat4 m_mat; // Only updates when get_matrix is called.
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;
};

}
