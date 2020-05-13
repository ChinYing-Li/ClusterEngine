
#include "car.h"
Car::Car():
m_position(0.0f),
m_height(0.05f),
m_length(0.15f),
m_width(0.1f),
m_cam(m_position), //wrong
m_aabb(m_position - glm::vec3(m_width/2, m_length/2, 0), m_position + glm::vec3(m_width/2, m_length/2, m_height))
{}

Car::Car(const float x, const float y):
m_position(x, y, 0.0f),
m_height(0.05f),
m_length(0.15f),
m_width(0.1f),
m_cam(x, y, 0.0f),
m_aabb(m_position - glm::vec3(m_width/2, m_length/2, 0), m_position + glm::vec3(m_width/2, m_length/2, m_height))
{
    m_front_color = {0, 255, 0};
    m_back_color = {200, 120, 0};
    
    glm::vec3 top_vertex(0.0f, 0.0f, m_height+m_aboveground);
    glm::vec3 front_vertex(0.0f, m_length, m_aboveground);
    glm::vec3 left_vertex(-m_width/2, -0.05f, m_aboveground);
    glm::vec3 right_vertex(m_width/2, -0.05f, m_aboveground);
    create_front(top_vertex, front_vertex, left_vertex, right_vertex);
    create_rear(top_vertex, left_vertex, right_vertex);
    return;
}

void Car::create_front(const glm::vec3& top,
                       const glm::vec3& front,
                       const glm::vec3& left,
                       const glm::vec3& right)
{
    GLfloat front_vertbuf_data[] =
    {
        top.x, top.y, top.z,
        front.x, front.y, front.z,
        left.x, left.y, left.z,
        
        top.x, top.y, top.z,
        front.x, front.y, front.z,
        right.x, right.y, right.z,
    };
    
    m_front = VAO_monotone(GL_TRIANGLES, 6, front_vertbuf_data, m_front_color, GL_FILL);
    return;
}

void Car::create_rear(const glm::vec3& top_vertex,
                      const glm::vec3& left_vertex,
                      const glm::vec3& right_vertex)
{
    GLfloat back_vertbuf_data[] =
    {
        top_vertex.x, top_vertex.y, top_vertex.z,
        left_vertex.x, left_vertex.y, left_vertex.z,
        right_vertex.x, right_vertex.y, right_vertex.z
    };
    
    m_back = VAO_monotone(GL_TRIANGLES, 3, back_vertbuf_data, m_back_color, GL_FILL);
    return;
}


void Car::draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat)
{
    mat.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (m_position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0,1 ));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    mat.model *= (translate * rotate);
    glm::mat4 MVP = VP * mat.model; // ???
    glUseProgram(shaderID);
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    m_front.draw(shaderID);
    m_back.draw(shaderID);
    glBindVertexArray(0);
    return;
}

void Car::set_position(const float x, const float y, const float z)
{
    m_position = glm::vec3(x, y, z);
    return;
}

void Car::set_velocity(const float vx, const float vy, const float vz)
{
    m_velocity = glm::vec3(vx, vy, vz);
    return;
}

/*
 enum carMovement
 {
     forward_accelerate = 1;
     backward_accelerate = 2;
     turn_cw = 3;
     turn_ccw = 4;
     car_break = 5;
 }

 */
void Car::user_update(const carMovement input)
{
    return;
};


