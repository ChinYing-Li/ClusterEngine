#include <iostream>
#include <fstream>
#include <sstream>
#include "material.h"

Material::Material():
m_ambient(0.5f),
m_diffuse(0.5f),
m_specular(0.5f),
m_emission(0.0f),
Ns(0.0f)
{}

Material::Material(const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular, const glm::vec3 emission, const float shininess):
m_ambient(ambient),
m_diffuse(diffuse),
m_specular(specular)
{}

Material::Material(const std::string path_to_mtl):
m_ambient(0.0f),
m_diffuse(0.0f),
m_specular(0.0f),
m_emission(0.0f)
{
    
}

void Material::set_properties_in_shader(GLuint shaderID)
{
    glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), m_ambient.x, m_ambient.y, m_ambient.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), m_diffuse.x, m_diffuse.y, m_diffuse.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.specular"), m_specular.x, m_specular.y, m_specular.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.emission"), m_emission.x, m_emission.y, m_emission.z);
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), Ns);
    return;
}

void Material::parse_from_file(std::string filepath) {
    
    std::ifstream inFile;
    inFile.open( filepath, std::ifstream::in );
    if( !inFile ) {
        std::cout << "Unable to read: " << filepath << std::endl;
        exit(-1);
    }
    
    // Read in line by line until end of file
    std::string curLine;
    std::string curMaterial = "";
    while(getline(inFile, curLine)) {
        std::istringstream ss(curLine);
        std::string lineType;
        ss >> lineType;
        
        if( lineType.compare("newmtl") == 0 ) {
            ss >> m_name;
        }
        
        // Reading in ambient color
        else if( lineType.compare("Ka") == 0 ) {
            float r, g, b;
            ss >> r >> g >> b;
            m_ambient = glm::vec3(r,g,b);
        }
        
        // Read in diffuse color
        else if( lineType.compare("Kd") == 0 ) {
            float r, g, b;
            ss >> r >> g >> b;
            m_diffuse = glm::vec3(r,g,b);
        }
        
        // Read in specular color
        else if( lineType.compare("Ks") == 0 ){
            float r, g, b;
            ss >> r >> g >> b;
            m_specular = glm::vec3(r,g,b);
        }
        
        else if(lineType.compare("Ns"))
        {
            ss >> Ns;
        }
        
        else if (lineType.compare("illum"))
        {
            ss >> illum;
        }
        
        else if (lineType.compare("map_Ka"))
        {
            use_map_Ka = true;
            
        }
        else if (lineType.compare("map_Kd"))
        {
            use_map_Kd = true;
        }
        else if (lineType.compare("map_Ks"))
        {
            use_map_Ks = true;
        }
        else if (lineType.compare("map_Ns"))
        {
            use_map_Ns = true;
        }
        else if (lineType.compare("map_d"))
        {
            use_map_d = true;
        }
        else
        {
            continue;
        }
    }
    
    inFile.close();
}

