#include <math.h>

#include "coin.h"
#include "../foundation/math/constants.h"

#define CIRCLE_POINTS 360

Coin::Coin():
Hitable(0, 0, 0),
m_radius(0.01),
m_thickness(0.005),
m_aabb(m_position - glm::vec3(sqrt2*m_radius), m_position + glm::vec3(sqrt2*m_radius))
{}

Coin::Coin(const float x, const float y, const float z, const float radius, const float thickness):
Hitable(x, y, z),
m_radius(radius),
m_thickness(thickness),
m_aabb(m_position - glm::vec3(sqrt2*m_radius), m_position + glm::vec3(sqrt2*m_radius))
{
    create_head_tail();
    create_side();
}

void Coin::create_head_tail()
{
    //GL_TRIANGLE_FAN;
    GLfloat head_vertbuf_data[3*(1+CIRCLE_POINTS)];
    // center
    head_vertbuf_data[0] = 0.0f;
    head_vertbuf_data[1] = 0.0f;
    head_vertbuf_data[2] = std::min(m_position.z, m_radius);
    for(int vertex = 1; vertex < CIRCLE_POINTS+1; ++vertex)
    {
        head_vertbuf_data[3*vertex] = 0.0f+m_radius*cos((M_PI/180.0f)*vertex);
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

void Coin::draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat)
{
    mat.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (m_position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (m_orientation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glUseProgram(shaderID);
    mat.model *= (translate * rotate);
    glm::mat4 MVP = VP * mat.model; // ???
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    m_head.draw(shaderID);
    m_tail.draw(shaderID);
    
    return;
}

void Coin::update()
{
    m_orientation += 1.0f;
}

