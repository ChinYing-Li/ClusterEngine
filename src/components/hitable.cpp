#include "hitable.h"

Hitable::Hitable():
m_position(0, 0, 0)
{}

Hitable::Hitable(const float x, const float y, const float z):
m_position(x, y, z)
{}

void Hitable::set_position(const float x, const float y, const float z)
{
    m_position = glm::vec3(x, y, z);
}

