#pragma once

#include "gltypes.h"
#include "../../includes/gl_headers.h"
#include "../foundation/aabb.h"
#include "../utilities/camera.h"

enum carMovement
{
    forward_accelerate = 1,
    backward_accelerate = 2,
    car_turn_cw = 3,
    car_turn_ccw = 4,
    car_break = 5,
};

class Car
{
public:
    Car();
    Car(const float x, const float y);
    ~Car() = default;
    
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat);
    
    void set_position(const float x, const float y, const float z);
    void set_velocity(const float vx, const float vy, const float vz);
    void user_update(const carMovement input);
    
    glm::vec3 m_position;
    glm::vec3 m_direction; // the tip of the car is pointed 
    glm::vec3 m_velocity; // the z component is always 0
    
    color_t m_front_color;
    color_t m_back_color;
    CarCam m_cam;
    
private:
    float m_height;
    float m_length;
    float m_width;
    float m_aboveground = 0.08f;
    
    float max_velocity = 2.0f;
    float acceleration = 0.5f;
    float break_decc = 1.0f;
    
    AABB m_aabb; // how to update aabb?
    
    void create_front(const glm::vec3& top_vertex,
                      const glm::vec3& front_vertex,
                      const glm::vec3& left_vertex,
                      const glm::vec3& right_vertex);
    void create_rear(const glm::vec3& top_vertex,
                     const glm::vec3& left_vertex,
                     const glm::vec3& right_vertex);
    VAO_monotone m_front;
    VAO_monotone m_back;
};
