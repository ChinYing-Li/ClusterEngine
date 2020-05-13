#include "light.h"

Light::Light()
{}

bool Light::is_enabled()
{
    return on_state;
}

void Light::turn_on()
{
    on_state = true;
    return;
}

void Light::turn_off()
{
    on_state = false;
    return;
}

void Light::set_color(const color_t new_color)
{
    m_color = new_color;
    return;
}

void Light::set_shader(GLuint shaderID)
{
    glUniform1i(glGetUniformLocation(shaderID, "light.is_enabled"), int(on_state));
    glUniform3f(glGetUniformLocation(shaderID, "light.color"), m_color.r/255.0f, m_color.g/255.0f, m_color.b/255.0f);
    return;
}

SpotLight::SpotLight():
Light()
{
    
}

SpotLight::SpotLight(const glm::vec3 position, glm::vec3 conedirection, const float cutoff, const float exponent):
Light(),
m_position(position),
m_conedirection(conedirection),
m_cutoff(cutoff),
m_exponent(exponent)
{
    
}

void SpotLight::set_color(const color_t new_color)
{
    Light::set_color(new_color);
    return;
}

void SpotLight::set_shader(GLuint shaderID)
{
    Light::set_shader(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "light.is_local"), int(false));
    glUniform1i(glGetUniformLocation(shaderID, "light.is_spotlight"), int(true));
    
    glUniform3fv(glGetUniformLocation(shaderID, "light.position"), 1, &m_position[0]);
    glUniform3fv(glGetUniformLocation(shaderID, "light.cone_direction"), 1, &m_conedirection[0]);
    glUniform1f(glGetUniformLocation(shaderID, "light.spot_cos_cutoff"), m_cutoff);
    glUniform1f(glGetUniformLocation(shaderID, "light.exponent"), m_exponent);
    return;
}
PointLight::PointLight():
Light()
{}

PointLight::~PointLight()
{
}

void PointLight::set_color(const color_t new_color)
{
    Light::set_color(new_color);
    return;
}

void PointLight::set_shader(GLuint shaderID)
{
    Light::set_shader(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "light.is_local"), int(true));
    glUniform1i(glGetUniformLocation(shaderID, "light.is_spotlight"), int(false));
    glUniform3fv(glGetUniformLocation(shaderID, "light.position"), 1, &m_position[0]);
    return;
}

DirectionalLight::DirectionalLight():
Light()
{}

DirectionalLight::DirectionalLight(const glm::vec3 halfvec):
Light(),
m_halfvec(halfvec)
{}

DirectionalLight::~DirectionalLight()
{}

void DirectionalLight::set_color(const color_t new_color)
{
    Light::set_color(new_color);
    return;
}

void DirectionalLight::set_shader(GLuint shaderID)
{
    Light::set_shader(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "light.is_local"), int(false));
    glUniform1i(glGetUniformLocation(shaderID, "light.is_spotlight"), int(false));
    glUniform3fv(glGetUniformLocation(shaderID, "light.halfvec"), 1, &m_halfvec[0]);
    return;
}
