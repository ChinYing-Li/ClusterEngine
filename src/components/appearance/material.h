#pragma once
#include "main.h"
class Material
{
public:
    Material();
    Material(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 emission, const float shininess);
    ~Material() = default;
    
    void set_properties_in_shader(GLuint shadeID);
protected:
    float m_shininess;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_emission; // emission not in use
    
};
