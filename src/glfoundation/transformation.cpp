#include "transformation.h"

namespace Cluster
{
Transformation::
Transformation():
  m_position(0.0),
  m_rotation(0.0),
  m_scale(1.0)
{

}

glm::mat4 Transformation::
get_matrix()
{

}
}
