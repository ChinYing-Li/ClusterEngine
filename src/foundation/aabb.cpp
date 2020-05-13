#include "aabb.h"

AABB::AABB(glm::vec3& mincoords, glm::vec3& maxcoords):
m_mincoords(mincoords),
m_maxcoords(maxcoords)
{}

AABB::AABB(const glm::vec3 mincoords, const glm::vec3 maxcoords):
m_mincoords(mincoords),
m_maxcoords(maxcoords)
{}

AABB::~AABB()
{}

bool AABB::is_between(const float target, const float lo, const float hi)
{
    return(target > lo && target < hi);
}

bool AABB::collided(AABB& rhs)
{
    bool flag = false;
    flag ^= (is_between(m_mincoords.x, rhs.m_mincoords.x, rhs.m_maxcoords.x));
    flag ^= (is_between(m_maxcoords.x, rhs.m_mincoords.x, rhs.m_maxcoords.x));
    if(!flag) return false;
    
    flag = false;
    flag ^= (is_between(m_mincoords.y, rhs.m_mincoords.y, rhs.m_maxcoords.y));
    flag ^= (is_between(m_maxcoords.y, rhs.m_mincoords.y, rhs.m_maxcoords.y));
    if(!flag) return false;
    
    flag = false;
    flag ^= (is_between(m_mincoords.z, rhs.m_mincoords.z, rhs.m_maxcoords.z));
    flag ^= (is_between(m_maxcoords.z, rhs.m_mincoords.z, rhs.m_maxcoords.z));
    return flag;
}
