#pragma once
#include "includes/GLincludes.h"

class ConvexHull;
class CollisionDetector
{
public:
    CollisionDetector() = default;
    ~CollisionDetector() = default;
    bool virtual intersected(const ConvexHull& lhs, const ConvexHull& rhs) = 0;
private:
};

class GJK: public CollisionDetector
{
public:
    GJK();
    ~GJK() = default;
    bool intersected(const ConvexHull& lhs, const ConvexHull& rhs) override;
private:
    const int MAX_ITERATION = 50;
    glm::vec3 m_a, m_b, m_c, m_d; //vertices of simplex
    
    // check if origin is within the simplex and updates the simplex
    bool update_2simplex(glm::vec3& direction, int& dimension); // triangle
    bool update_3simplex(glm::vec3& direction); //tetrahedral
    const glm::vec3 calc_support(const ConvexHull& lhs, const ConvexHull& rhs, const glm::vec3 dir);
};

