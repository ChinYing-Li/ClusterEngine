#pragma once

#include "gltypes.h"
#include "../../includes/gl_headers.h"
#include "../utilities/camera.h"
#include "hitable.h"

enum carMovement
{
    forward_accelerate = 1,
    backward_accelerate = 2,
    car_turn_cw = 3,
    car_turn_ccw = 4,
    car_break = 5,
    car_not_accelerating = 6
};

const float km_to_m = 1000.0f;
const float m_to_km = 0.001f;
//in seconds
const float timer_interval = 1.0f/60.0f;

class Car: public Hitable
{
public:
    Car();
    Car(const float x, const float y);
    ~Car() = default;
    
    // update carcam
    void update(float delta_t) override;
    void update_convexhull() override;
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat) override;
    void resolve_collision() override;
    
    void set_velocity(const float new_v);
    void receive_input(const carMovement input, GameData& gamedata, float delta_t);
    
    glm::vec3 m_direction; // the tip of the car is pointed
    
    float m_velocity; // the z component is always 0
    
    color_t m_front_color;
    color_t m_back_color;
    CarCam m_cam;
    
protected:
    void set_up_collision_shape() override;
    
private:
    // in meters
    float m_height;
    float m_length;
    float m_width;
    float m_aboveground = 0.5f*m_to_km;
    
    float m_angle; // in degree
    float m_rotate_ang = 1.0f;
    
    // length unit in meter, time unit in second
    float max_velocity = 50.0f/36.0f;
    float m_acceleration = 2.0f;
    float m_break_decc = 3.4f;

    float m_decceleration = 1.0f;
    
    glm::vec3 theta_zero;
    glm::mat4 m_cw_mat;
    glm::mat4 m_ccw_mat;
    glm::mat4 m_rotatemat;
   
    
    void create_front(const glm::vec3& top_vertex,
                      const glm::vec3& front_vertex,
                      const glm::vec3& left_vertex,
                      const glm::vec3& right_vertex);
    void create_rear(const glm::vec3& top_vertex,
                     const glm::vec3& left_vertex,
                     const glm::vec3& right_vertex);
    void angle_mod();
    void cam_update();
    VAO_monotone m_front;
    VAO_monotone m_back;
    VAO_monotone m_camera;
};
