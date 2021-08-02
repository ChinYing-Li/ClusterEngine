#include <assert.h>
#include <iostream>

#include "light.h"
#include "glfoundation/texturemanager.h"

namespace Cluster{
Light::Light():
  m_const_atten(10.0f),
  m_linear_atten(10.0f),
  m_shadowbuffer(800, 600)
{}

bool Light::
is_enabled()
{
    return m_on_state;
}

void Light::
turn_on()
{
    m_on_state = true;
    return;
}

void Light::
turn_off()
{
    m_on_state = false;
    return;
}

void Light::
setup_shadowbuffer(unsigned int width, unsigned int height)
{
  m_shadowbuffer.create(width, height);
  m_shadowbuffer.bind(FrameBuffer::NORMAL);
  m_shadowbuffer.disable_color();
  m_shadowbuffer.release();
}

Light::Type Light::
get_type() const
{
    return m_type;
}

void Light::
set_color(const glm::vec3 new_color)
{
    m_color = new_color;
}

void Light::
set_const_attenuation(const float const_atten)
{
    m_const_atten = const_atten;
}

void Light::
set_linear_attenuation(const float linear_atten)
{
    m_linear_atten = linear_atten;
}

void Light::
set_quadratic_attenuation(const float quad_atten)
{
    m_quadratic_atten = quad_atten;
    return;
}

void Light::
set_ambient_strength(const glm::vec3 new_amb_strength)
{
    m_ambient_strength = new_amb_strength;
}

void Light::
set_shader(int index,
           GLuint& shaderID)
{
    glUseProgram(shaderID);
    glUniform1i(glGetUniformLocation(shaderID, "lights[0].is_enabled"), int(m_on_state));
    glUniform1i(glGetUniformLocation(shaderID, "lights[0].is_local"), int(m_is_local));
    glUniform1i(glGetUniformLocation(shaderID, "lights[0].is_spotlight"), int(m_is_spotlight));
    glUniform3f(glGetUniformLocation(shaderID, "lights[0].color"), m_color.r, m_color.g, m_color.b);
    glUniform3f(glGetUniformLocation(shaderID, "lights[0].ambient_strength"), m_ambient_strength.r, m_ambient_strength.g, m_ambient_strength.b);

    glUniform1f(glGetUniformLocation(shaderID, "lights[0].constant_atten"), m_const_atten);
    glUniform1f(glGetUniformLocation(shaderID, "lights[0].linear_atten"), m_linear_atten);
    glUniform1f(glGetUniformLocation(shaderID, "lights[0].quadratic_atten"), m_quadratic_atten);
    return;
}

/*
 *
 */
SpotLight::
SpotLight():
Light(),
  m_type(Type::POINTLIGHT)
{
    m_is_local = true;
    m_is_spotlight = true;
}

SpotLight::
SpotLight(const glm::vec3 position,
          glm::vec3 conedirection,
          const float cutoff,
          const float exponent):
    Light(),
    m_cutoff(cutoff),
    m_exponent(exponent),
    m_position(position),
    m_conedirection(conedirection)
{
    m_is_local = true;
    m_is_spotlight = true;
}

void SpotLight::
set_shader(int index,
           GLuint& shaderID)
{
    Light::set_shader(index, shaderID);
    glUniform3fv(glGetUniformLocation(shaderID, "lights[0].position"), 1, &m_position[0]);
    glUniform3fv(glGetUniformLocation(shaderID, "lights[0].cone_direction"), 1, &m_conedirection[0]);
    glUniform1f(glGetUniformLocation(shaderID, "lights[0].spot_cos_cutoff"), m_cutoff);
    glUniform1f(glGetUniformLocation(shaderID, "lights[0].exponent"), m_exponent);
    return;
}

/*
 *
 */
PointLight::
PointLight():
Light()
{
    m_is_local = true;
}

PointLight::
PointLight(const glm::vec3 position):
Light()
{
    m_position = position;
}

void PointLight::
set_shader(int index,
           GLuint& shaderID)
{
    glUseProgram(shaderID);
    Light::set_shader(index, shaderID);

    glUniform3fv(glGetUniformLocation(shaderID, "lights[0].position"), 1, &m_position[0]);
}

void PointLight::
setup_shadow_map(const std::vector<int>& dimension)
{
    assert (dimension.size() >= 1);
    m_shadow_cubemap = std::make_shared<TextureCubemap>(TextureManager::generate_shadow_cubemap(dimension[0]));
}

std::shared_ptr<Texture> PointLight::
get_shadowmap()
{
    return m_shadow_cubemap;
}

/*
 *
 */
DirectionalLight::
DirectionalLight(const glm::vec3 direction):
Light(),
m_direction(direction)
{}

void DirectionalLight::
set_shader(int index,
           GLuint& shaderID)
{
    Light::set_shader(index, shaderID);
    glUniform3fv(glGetUniformLocation(shaderID, "lights[0].direction"), 1, &m_direction[0]);
}

void DirectionalLight::
set_direction(const glm::vec3 direction)
{
    m_direction = direction;
}

void DirectionalLight::
setup_shadow_map(const std::vector<int>& dimension)
{
    assert (dimension.size() >= 2);
    m_shadow_map = std::make_shared<Texture2D>(TextureManager::generate_shadow_map(dimension[0], dimension[1]));
}

std::shared_ptr<Texture> DirectionalLight::
get_shadowmap()
{
    return m_shadow_map;
}

} // namespace Cluster
