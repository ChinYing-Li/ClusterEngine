#pragma once
#include "../../includes/gl_headers.h"
class Light
{
public:
    Light();
    ~Light() = default;
    
    bool is_enabled();
    void turn_off();
    void turn_on();
    void set_color(const color_t new_color);
    void virtual set_shader(int index, GLuint shaderID);
protected:
    bool on_state = true;
    color_t m_color;
    glm::vec3 m_ambient_contrib; // do we really need this?
};

class SpotLight: public Light
{
public:
    SpotLight();
    SpotLight(const glm::vec3 position, glm::vec3 conedirection, const float cutoff, const float exponent);
    ~SpotLight();
    
    void set_color(const color_t new_color);
    void set_shader(int index, GLuint shaderID);
protected:
    glm::vec3 m_position;
    glm::vec3 m_conedirection;
    float m_cutoff;
    float m_exponent;
};

class PointLight: public Light
{
public:
    PointLight();
    PointLight(const glm::vec3 position);
    ~PointLight();
    
    void set_color(const color_t new_color);
    void set_shader(int index, GLuint shaderID);
protected:
    glm::vec3 m_position;
};

class DirectionalLight: public Light
{
public:
    DirectionalLight();
    DirectionalLight(const glm::vec3 halfvec);
    ~DirectionalLight();
    
    void set_color(const color_t new_color);
    void set_shader(int index, GLuint shaderID);
protected:
    glm::vec3 m_halfvec;
    
};
