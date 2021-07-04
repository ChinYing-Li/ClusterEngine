#include "transformation.h"
#include "utilities/mathconst.h"

namespace Cluster
{
Transformation::
Transformation():
  m_position(0.0),
  m_rotation(0.0),
  m_scale(1.0)
{}

void Transformation::
translate(const glm::vec4 offset)
{
  m_position += offset;
}

const glm::mat4& Transformation::
get_matrix()
{
  m_mat = glm::translate(glm::rotate(m_rotation.z, unit_z) *
                         glm::rotate(m_rotation.y, unit_y) *
                         glm::rotate(m_rotation.x, unit_x) *
                         glm::scale(identity_mat4, glm::vec3(m_scale)), m_position);
  return m_mat;
}

const glm::vec3& Transformation::
get_position()
{
  return m_position;
}

const glm::vec3& Transformation::
get_rotation()
{
  return m_rotation;
}

const glm::vec3& Transformation::
get_scale()
{
  return m_scale;
}
}
