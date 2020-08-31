#pragma once
#include "includes/GLincludes.h"

class Light
{
public:
    Light();
    ~Light() = default;
    
    bool is_enabled();
    void turn_off();
    void turn_on();
    void set_color(const glm::vec3 new_color);

    void set_const_attenuation(const float const_atten);
    void set_lin_attenuation(const float linear_atten);
    void set_quad_attenuation(const float quad_atten);
    void set_ambient_strength(const glm::vec3 new_amb_strength);

    void virtual set_shader(int index, GLuint& shaderID);

protected:
    bool on_state = true;
    bool is_spotlight = false;
    bool is_local = false;

    float m_const_atten;
    float m_linear_atten;
    float m_quadratic_atten;

    glm::vec3 m_ambient_strength;
    glm::vec3 m_color;
};

class SpotLight final : public Light
{
public:
    SpotLight();
    SpotLight(const glm::vec3 position, glm::vec3 conedirection, const float cutoff, const float exponent);
    ~SpotLight() = default;

    void set_shader(int index, GLuint& shaderID) override;

protected:
    float m_cutoff;
    float m_exponent;
    glm::vec3 m_position;
    glm::vec3 m_conedirection;
};

class PointLight final : public Light
{
public:
    PointLight();
    PointLight(const glm::vec3 position);
    ~PointLight() = default;

    void set_shader(int index, GLuint& shaderID) override;

protected:
    glm::vec3 m_position;
};

class DirectionalLight final : public Light
{
public:
    DirectionalLight() = default;
    DirectionalLight(const glm::vec3 halfvec);
    ~DirectionalLight() = default;

    void set_shader(int index, GLuint& shaderID) override;
    void set_direction(const glm::vec3 halfvec);

protected:
    glm::vec3 m_direction;
};
