#pragma once

#include <cstddef>

#include "includes/GLincludes.h"

class AABB
{
public:
    AABB() = delete;
    AABB(glm::vec3& mincoords, glm::vec3& maxcoords);
    AABB(const glm::vec3 mincoords, const glm::vec3 maxcoords);
    ~AABB();

    bool collided(AABB& rhs);
    //void update(); 
    static bool is_between(const float target, const float lo, const float hi);

private:
    glm::vec3 m_mincoords;
    glm::vec3 m_maxcoords;
};
