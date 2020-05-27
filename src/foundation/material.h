#pragma once
#include <string.h>
#include <memory>
#include "includes/gl_headers.h"
class Texture2D;
class Material
{
public:
    Material();
    Material(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 emission, const float shininess);
    Material(const std::string path_to_mtl);
    ~Material() = default;
    
    void set_properties_in_shader(GLuint shadeID);
    
    std::string m_name;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_emission;
    
    float Ns; // shininess
    int illum; // Illumination
    
    bool use_map_Ka = false;
    bool use_map_Kd = false;
    bool use_map_Ks = false;
    bool use_map_Ns = false;
    bool use_map_d = false;
    bool use_map_bump = false;
    // Ambient Texture Map
    std::shared_ptr<Texture2D> map_Ka;
    // Diffuse Texture Map
    std::shared_ptr<Texture2D> map_Kd;
    // Specular Texture Map
    std::shared_ptr<Texture2D> map_Ks;
    // Specular Hightlight Map
    std::shared_ptr<Texture2D> map_Ns;
    // Alpha Texture Map
    std::shared_ptr<Texture2D> map_d;
    // Bump Map
    std::shared_ptr<Texture2D> map_bump;
protected:
     // emission not in use
    void parse_from_file(std::string filepath);
};
