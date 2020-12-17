#include "src/components/drawable.h"

Drawable::Drawable():
m_position(0.0f)
{}

Drawable::Drawable(const float x, const float y, const float z):
m_position(x, y, z)
{}

void Drawable::set_position(const float x, const float y, const float z)
{
    m_position = glm::vec3(x, y, z);
}
