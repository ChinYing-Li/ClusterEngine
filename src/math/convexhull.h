#pragma once
#include <vector>
#include "includes/GLincludes.h"

class ConvexHull
{
public:
    ConvexHull() = default;
    ConvexHull(std::vector<glm::vec3> vertices);
    ~ConvexHull() = default;
    glm::vec3 get_farthest(const glm::vec3 direction) const;
    glm::mat4 model_RS;
    glm::vec3 displacement;
protected:
    std::vector<glm::vec3> m_vertices;
};

