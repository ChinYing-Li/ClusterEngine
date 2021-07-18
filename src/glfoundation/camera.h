#pragma once

#include <math.h>
#include <iostream>

#include "glincludes.h"

namespace Cluster {

class Shader;

class Camera
{
public:
    Camera();
    Camera(const float x, const float y, const float z);
    ~Camera() = default;

    void load_proj_mat(glm::mat4& mat) const noexcept;
    void load_view_mat(glm::mat4& mat) const noexcept;

    void set_aspect_ratio(const float aspect_ratio);
    float get_aspect_ratio() const noexcept;

    // In degrees
    void set_fovy(const float fovy);
    float get_fovy() const noexcept;

    float get_near_plane() const noexcept;
    float get_far_plane() const noexcept;
    void set_near_plane(float near);
    void set_far_plane(float far);

    void set_eye(const glm::vec3 eye);
    glm::vec3 get_eye() const;
    void set_direction(const glm::vec3 direction);
    void set_up(const glm::vec3 up);

private:
    float m_aspect_ratio = 1.0f;
    float m_fovy;
    float m_near_plane = 0.1f;
    float m_far_plane = 100.0f;
    glm::vec2 m_screenspace_bottomleft_coordinate = glm::vec2(-1);
    glm::vec2 m_screenspace_top_coordinate = glm::vec2(1);

    glm::vec3 m_eye;
    glm::vec3 m_direction;
    glm::vec3 m_up;
};
}
