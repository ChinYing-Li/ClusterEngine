#include <math.h>
#include <vector>
#include <iostream>
#include "coin.h"
#include "../foundation/math/constants.h"

#define CIRCLE_POINTS 360

Coin::Coin():
Hitable(0, 0, 0),
m_radius(0.01),
m_thickness(0.005)
{}

Coin::Coin(const float x, const float y, const float z, const float radius, const float thickness):
Hitable(x, y, z),
m_radius(radius),
m_thickness(thickness)
m_coin_obj()
{
    //create_head_tail();
    //create_side();
    //set_up_collision_shape();
    
}
/*
void Coin::create_head_tail()
{
    
    GLfloat head_vertbuf_data[3*(1+CIRCLE_POINTS)];
    // center
    head_vertbuf_data[0] = 0.0f;
    head_vertbuf_data[1] = 0.0f;
    head_vertbuf_data[2] = 0.0f;
    for(int vertex = 1; vertex < CIRCLE_POINTS+1; ++vertex)
    {
        head_vertbuf_data[3*vertex] = head_vertbuf_data[0]+m_radius*cos((M_PI/180.0f)*vertex);
        head_vertbuf_data[3*vertex+1] = 0.0f;
        head_vertbuf_data[3*vertex+2] = head_vertbuf_data[2]+m_radius*sin((M_PI/180.0f)*vertex);
    }
    m_head = VAO_monotone(GL_TRIANGLE_FAN, CIRCLE_POINTS+1, head_vertbuf_data, m_color, GL_FILL);
    
    GLfloat* tail_vertbuf_data(head_vertbuf_data);
    for(int vertex = 0; vertex < CIRCLE_POINTS+1; ++vertex)
    {
        tail_vertbuf_data[3*vertex + 1] += m_thickness;
    }
    m_tail = VAO_monotone(GL_TRIANGLE_FAN, CIRCLE_POINTS+1, tail_vertbuf_data, m_color, GL_FILL);
    return;
}

void Coin::create_side()
{
    return;
}
*/
void Coin::draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(m_position);
    model *= (translate * collision_shape.model_RS);
    m_coin_obj.draw(shaderID, model, view, project);
    
    return;
}
 

void Coin::update(float delta_t)
{
    m_orientation += 1.0f;
    collision_shape.model_RS = glm::rotate((float) (m_orientation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    collision_shape.displacement = m_position;
    return;
}

void Coin::set_up_collision_shape()
{
    std::vector<glm::vec3> vertices = {
        glm::vec3(-m_radius, 0.0f, m_radius),
        glm::vec3(-m_radius, 0.0f, -m_radius),
        glm::vec3(m_radius, 0.0f, m_radius),
        glm::vec3(m_radius, 0.0f, m_radius),
    };
    for(int i = 0; i < 4; ++i)
    {
        vertices.push_back(vertices[i] + glm::vec3(0.0f, m_thickness, 0.0f));
    }
    collision_shape = ConvexHull(vertices);
    return;
}

void Coin::update_convexhull()
{
    return;
}

void Coin::resolve_collision()
{
    return;
}

void Coin::set_instanced_models()
{
    return;
}
