#include <iostream>
#include "collisiondetector.h"
#include "shape.h"

GJK::GJK():
CollisionDetector()
{}

bool GJK::intersected(const Shape &lhs, const Shape &rhs)
{
    // an arbitray direction
    glm::vec3 direction(lhs.displacement - rhs.displacement);
    
    int simplex_dim = 0;
    m_c = calc_support(lhs, rhs, direction);
    direction = -m_c;
    m_b = calc_support(lhs, rhs, direction);
    if(glm::dot(m_b, direction) < 0.0f) return false;
    
    direction = glm::cross(glm::cross(m_c-m_b, -m_b), m_c-m_b);
    simplex_dim = 2;
    for(int iteration = 0; iteration < MAX_ITERATION; ++iteration)
    {
        m_a = calc_support(lhs, rhs, direction);
        //std::cout << "support" << m_a[0] << m_a[1] << std::endl;
        if(glm::dot(m_a, direction)<0) return false;
        if(simplex_dim == 2)
        {
            if(update_2simplex(direction, simplex_dim)) return true;
        }
        else
        {
            if(update_3simplex(direction)) return true;
        }
    }
    return false;
}

// a is always added last
bool GJK::update_2simplex(glm::vec3& direction, int& simlex_dim)
{
    glm::vec3 ao = -m_a;
    glm::vec3 ab = m_b - m_a;
    glm::vec3 ac = m_c - m_a;
    glm::vec3 abXac = glm::cross(ab, ac);
    
    if(glm::dot(glm::cross(ab, abXac), ao) > 0.0f)
    {
        m_c = m_b;
        m_b = m_a;
        direction = glm::cross(glm::cross(ab, ao), ab);
        return false;
    }
    
    if(glm::dot(glm::cross(abXac, ac), ao) > 0)
    {
        m_b = m_a;
        direction = glm::cross(glm::cross(ac, ao), ac);
        return false;
    }
    
    // the projection of origin on triangle is within the triangle
    if(glm::dot(abXac, ao) > 0)
    {
        m_d = m_c;
        m_c = m_b;
        m_b = m_a;
        direction = abXac;
    }
    else
    {
        m_d = m_b;
        m_b = m_a;
        direction = -abXac;
    }
    simlex_dim = 3;
    return false;
}

bool GJK::update_3simplex(glm::vec3& direction)
{
    glm::vec3 ao = -m_a;
    glm::vec3 ab = m_b - m_a;
    glm::vec3 ac = m_c - m_a;
    glm::vec3 ad = m_d - m_a;
    glm::vec3 abXac = glm::cross(ab, ac);
    glm::vec3 acXad = glm::cross(ac, ad);
    glm::vec3 adXab = glm::cross(ad, ab);
    
    // test which plan is closest to the origin
    bool above_abc = (dot(abXac, ao) > 0.0f);
    bool above_acd = (dot(acXad, ao) > 0.0f);
    bool above_adb = (dot(adXab, ao) > 0.0f);
    
    // does not handle the case where two conditions are both true
    if(above_abc)
    {
        m_d = m_c;
        m_c = m_b;
        m_b = m_a;
        direction = abXac;
        return false;
    }
    if(above_acd)
    {
        m_b = m_a;
        direction = acXad;
        return false;
    }
    if(above_adb)
    {
        m_c = m_d;
        m_d = m_b;
        m_b = m_a;
        direction = adXab;
        return false;
    }
    return true;
}

const glm::vec3 GJK::calc_support(const Shape &lhs, const Shape &rhs, const glm::vec3 dir)
{
    return lhs.get_farthest(dir) - rhs.get_farthest(-dir);
}

