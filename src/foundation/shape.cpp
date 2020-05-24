#include <iostream>
#include "shape.h"

Shape::Shape(std::vector<glm::vec3> vertices):
m_vertices(vertices)
{}

glm::vec3 Shape::get_farthest(const glm::vec3 direction) const
{
    glm::vec4 p = model_RS*glm::vec4(m_vertices[0][0], m_vertices[0][1], m_vertices[0][2], 1.0f);
    glm::vec3 farthest(p[0], p[1], p[2]);
    glm::vec3 temp(farthest);
    float maximum_dot = glm::dot(farthest, direction);
    
    for(int i = 1; i < m_vertices.size(); ++i)
    {
        p = model_RS*glm::vec4(m_vertices[i][0], m_vertices[i][1], m_vertices[i][2], 1.0f);
        temp = glm::vec3(p[0], p[1], p[2]);
        float temp_dot = glm::dot(temp, direction);
        if( temp_dot > maximum_dot)
        {
            maximum_dot = temp_dot;
            farthest = temp;
        }
    }
    //std::cout << "farthest" << farthest[0] << farthest[1] << std::endl;
    return farthest + displacement;
}
