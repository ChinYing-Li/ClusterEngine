#pragma once
#include <string.h>
#include "includes/gl_headers.h"
class Shader
{
public:
    Shader() = default;
    Shader(const std::string path_vert, const std::string path_frag, const std::string path_geo, const std::string name);
    ~Shader() = default;
    
    void use();
    unsigned int ID;
    std::string m_name;
private:
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    
    std::string read_code(const std::string path_to_shader);
    void compile_shader(GLuint shaderID, const std::string& shader_code);
    void compile_check(GLuint shaderID);
};
