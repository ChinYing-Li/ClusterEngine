#pragma once

#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
    Shader() = default;
    Shader(const std::string path_to_vert, const std::string path_to_frag, const std::string path_to_geo, const std::string name);
    ~Shader() = default;
    
    void use();

    unsigned int m_program_ID;
    std::string m_name;

private:
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    
    std::string read_code(const std::string path_to_shader);
    void compile_shader(GLuint shaderID, const std::string& shader_code);
    void compile_check(GLuint shaderID);
    void link_check(GLuint& programID);
};