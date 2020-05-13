/*#pragma once
#include "main.h"
class Material
{
public:
    Material();
    Material(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
    ~Material();
    
    void set_properties_in_shader(GLuint shadeID);
protected:
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
}*/

#include "material.h"

Material::Material():
m_ambient(0.5f),
m_diffuse(0.5f),
m_specular(0.5f),
m_emission(0.0f),
m_shininess(0.0f)
{}

Material::Material(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 emission, const float shininess):
m_ambient(ambient),
m_diffuse(diffuse),
m_specular(specular)
{}

void Material::set_properties_in_shader(GLuint shaderID)
{
    glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.specular"), m_specular.x, m_specular.y, m_specular.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.emission"), m_emission.x, m_emission.y, m_emission.z);
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), m_shininess);
    return;
}
