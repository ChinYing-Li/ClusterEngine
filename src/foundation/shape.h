#pragma once
#include <vector>
#include "../../includes/gl_headers.h"

class Shape
{
public:
    Shape() = default;
    Shape(std::vector<glm::vec3> vertices);
    ~Shape() = default;
    glm::vec3 get_farthest(const glm::vec3 direction) const;
    glm::mat4 model_RS;
    glm::vec3 displacement;
protected:
    std::vector<glm::vec3> m_vertices;
};

