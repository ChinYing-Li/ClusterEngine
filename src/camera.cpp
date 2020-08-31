
#include "includes/utilities/camera.h"

Camera::Camera():
m_eye(0.0f, 0.5f, 0.0f),
m_direction(1.0f, 0.0f, -0.1f),
m_up(0, 1, 0)
{}

Camera::Camera(const float x, const float y, const float z):
m_eye(x, y, z),
m_direction(1.0f, -0.1f, 0.0f),
m_up(0, 1, 0)
{}

Camera::Camera(const glm::vec3 position):
m_eye(position),
m_direction(1.0f, -0.1f, 0.0f),
m_up(0, 1, 0)
{}

void Camera::update_matrices(GLMatrices& mat)
{
    mat.view = glm::lookAt(m_eye, m_eye+m_direction, m_up);
    return;
}

CarCam::CarCam(const float x, const float y, const float z):
Camera(x, y, z)
{}

CarCam::CarCam(const glm::vec3 position):
Camera(position)
{}

void CarCam::set_eye(const glm::vec3 pos)
{
    m_eye = pos;
    return;
}

void CarCam::set_direction(const glm::vec3 dir)
{
    m_direction = dir;
    return;
}

FreeCam::FreeCam():
Camera(),
m_rotate_ang(M_PI/180.0f),
m_stepsize(0.01f, 0.0f, 0.01f)
{
    m_cw_mat = glm::rotate(-m_rotate_ang, m_up);
    m_ccw_mat = glm::rotate(m_rotate_ang, m_up);
}

FreeCam::FreeCam(const float x, const float y, const float z):
Camera(x, y, z),
m_rotate_ang(M_PI/180.0f),
m_stepsize(0.01f, 0.0f, 0.01f)
{
    m_cw_mat = glm::rotate(-m_rotate_ang, m_up);
    m_ccw_mat = glm::rotate(m_rotate_ang, m_up);
}

FreeCam::FreeCam(const glm::vec3 position):
Camera(position),
m_rotate_ang(M_PI/180.0f),
m_stepsize(0.01f, 0.0f, 0.01f)
{
    m_cw_mat = glm::rotate(-m_rotate_ang, m_up);
    m_ccw_mat = glm::rotate(m_rotate_ang, m_up);
}

void FreeCam::update_cam(const int user_input)
{
    if(user_input == move_forward)
    {
        m_eye += m_stepsize * m_direction;
        return;
    }
    
    if(user_input == move_backward)
    {
        m_eye -= m_stepsize * m_direction;
        return;
    }
    if(user_input == turn_cw)
    {
        glm::vec4 turned = m_cw_mat * glm::vec4(m_direction.x, m_direction.y, m_direction.z, 0.0f);
        m_direction.x = turned.x;
        m_direction.z = turned.z;
        return;
    }
    if(user_input == turn_ccw)
    {
        glm::vec4 turned = m_ccw_mat * glm::vec4(m_direction.x, m_direction.y, m_direction.z, 0.0f);
        m_direction.x = turned.x;
        m_direction.z = turned.z;
        return;
    }
}

void FreeCam::set_stepsize(const glm::vec3 new_stepsize)
{
    m_stepsize = new_stepsize;
    return;
}
