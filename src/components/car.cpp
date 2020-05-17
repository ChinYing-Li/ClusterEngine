
#include <algorithm>
#include <cassert>

#include "car.h"

const float deg_per_rad = M_PI / 180.0f;

Car::Car():
m_position(0.0f),
m_height(1.0f*m_to_km),
m_length(2.5f*m_to_km),
m_width(2.0f*m_to_km),
m_cam(0.0, 0.0, 0.3f),
theta_zero(0.0, 1.0, 0.0),
m_aabb(m_position - glm::vec3(m_width/2, m_length/2, 0), m_position + glm::vec3(m_width/2, m_length/2, m_height))
{}

Car::Car(const float x, const float y):
m_position(0.35, 0.5, 0.0f),
m_height(2.0f*m_to_km),
m_length(2.5f*m_to_km),
m_width(2.0f*m_to_km),
m_cam(x, y, m_to_km/2),
m_angle(0.0f),
m_velocity(0.0f),
m_direction(0.0f, 1.0f, 0.0f),
theta_zero(0.0, 1.0, 0.0),
m_ccw_mat(glm::rotate(-m_rotate_ang, glm::vec3(0.0, 0.0, 1.0f))),
m_cw_mat(glm::rotate(m_rotate_ang, glm::vec3(0.0, 0.0, 1.0f))),
m_rotatemat(glm::rotate(m_angle, glm::vec3(0.0, 0.0, 1.0f))),
m_aabb(m_position - glm::vec3(m_width/2, m_length/2, 0), m_position + glm::vec3(m_width/2, m_length/2, m_height))
{
    m_front_color = {0, 123, 123};
    m_back_color = {200, 120, 0};
    m_cam.set_eye(glm::vec3(-5.0f*m_to_km*m_direction.x, -5.0f*m_to_km*m_direction.y, m_height/1.5f));
    m_cam.set_direction(m_direction);
    glm::vec3 top_vertex(0.0f,0.0f, m_height+m_aboveground);
    glm::vec3 front_vertex(0.0f, m_length, m_aboveground);
    glm::vec3 left_vertex(-m_width/2, -0.05f*m_to_km, m_aboveground);
    glm::vec3 right_vertex(m_width/2, -0.05f*m_to_km, m_aboveground);
    create_front(top_vertex, front_vertex, left_vertex, right_vertex);
    create_rear(top_vertex, left_vertex, right_vertex);
    GLfloat camerapoint [] = {
        -5.0f*m_to_km*m_direction.x, -5.0f*m_to_km*m_direction.y, m_height/1.5f
    };
    
    m_camera = VAO_monotone(GL_POINTS, 1, camerapoint, m_front_color, GL_FILL);
    return;
}

void Car::update(float delta_t) // called based on timers's frequency
{
    m_velocity = std::min(m_velocity, max_velocity);
    
    m_velocity -= m_decceleration*delta_t;
    m_velocity = std::max(m_velocity, 0.0f);
    m_position += m_velocity*delta_t*m_direction;
    cam_update();
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
    // need to update this as well
    //glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0,1 ));
   
    mat.model *= (translate * m_rotatemat);
    glm::mat4 MVP = VP * mat.model; // ???
    glUseProgram(shaderID);
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glPointSize(10);
    m_front.draw(shaderID);
    m_back.draw(shaderID);
    m_camera.draw(shaderID);
    glBindVertexArray(0);
    return;
}

void Car::set_position(const float x, const float y, const float z)
{
    m_position = glm::vec3(x, y, z);
    return;
}

void Car::set_velocity(const float new_v)
{
    m_velocity = new_v;
    return;
}

void Car::angle_mod()
{
    int winding = (m_angle/360.0f);
    m_angle -= winding*360.0f;
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
void Car::receive_input(const carMovement input, GameData& gamedata, float delta_t)
{
    if(input == forward_accelerate)
    {
        float diff = max_velocity - m_velocity;
        if(diff <= 0)
        {
            m_velocity = max_velocity;
            return;
        }
        m_velocity += std::min(diff, m_acceleration)*delta_t;
        std::cout << m_velocity << std::endl;
        return;
    }
    
    if(input == backward_accelerate)
    {
        return;
    }
    
    if(input == car_turn_cw)
    {
        m_angle -= m_rotate_ang;
        angle_mod();
        m_rotatemat = glm::rotate(m_angle*deg_per_rad, glm::vec3(0.0, 0.0, 1.0f));
        glm::vec4 turned = m_rotatemat * glm::vec4(theta_zero.x, theta_zero.y, theta_zero.z,  0.0f);
        m_direction.x = turned.x;
        m_direction.y = turned.y;
        return;
    }
    if(input == car_turn_ccw)
    {
        m_angle += m_rotate_ang;
        angle_mod();
        m_rotatemat = glm::rotate(m_angle*deg_per_rad, glm::vec3(0.0, 0.0, 1.0f));
        glm::vec4 turned = m_rotatemat * glm::vec4(theta_zero.x, theta_zero.y, theta_zero.z,  0.0f);
        m_direction.x = turned.x;
        m_direction.y = turned.y;
        return;
    }
    if(input == car_not_accelerating)
    {
        m_velocity -= m_decceleration*delta_t;
        m_velocity = std::max(m_velocity, 0.0f);
    }
    
    return;
};

void Car::cam_update()
{
    m_cam.set_eye(glm::vec3(m_position.x - 100.0f*m_to_km*m_direction.x, m_position.y - 100.0f*m_to_km*m_direction.y, m_aboveground+m_height*0.5f));
    m_cam.set_direction(m_direction);
    return;
}
