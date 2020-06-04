#include <iostream>
#include <fstream>
#include <vector>
#include "src/foundation/shader.h"

Shader::Shader(const std::string path_vert, const std::string path_frag, const std::string path_geo = "", const std::string name = ""):
m_name(name)
{
  m_vert_ID = glCreateShader(GL_VERTEX_SHADER);
  m_frag_ID = glCreateShader(GL_FRAGMENT_SHADER);

  std::string   vert_code = read_code(path_vert);
  std::string   frag_code = read_code(path_frag);
    compile_shader(m_vert_ID, vert_code);
    compile_check(m_vert_ID);
    compile_shader(m_frag_ID, frag_code);
    compile_check(m_frag_ID);
 
    if(path_geo.size()>0)
    {
        std::string geo_code = read_code(path_geo);
        compile_shader(m_geom_ID, path_geo);
        compile_check(m_geom_ID);
    }
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, m_vert_ID);
    glAttachShader(ID, m_frag_ID);
    if(path_geo.size()>0)
        glAttachShader(ID, m_geom_ID);
    glLinkProgram(ID);
    link_check(ID);
    glDeleteShader(m_vert_ID);
    glDeleteShader(m_frag_ID);
    if(path_geo.size()>0)
        glDeleteShader(m_geom_ID);

}

void Shader::use()
{
    glUseProgram(ID);
        
}
        
std::string Shader::read_code(const std::string path_to_shader)
        {
            std::string  code;
            std::ifstream stream(path_to_shader, std::ios::in);
            if (stream.is_open())
        {
        std::cout << "Reading shader code..." << std::endl;
                std::string Line = "";
                while (getline(stream, Line))
                    code += "\n" + Line;
                stream.close();
            }
        return code;
        }
void Shader::compile_shader(GLuint shaderID, const std::string& shader_code)
        {
            char const *src_ptr = shader_code.c_str();
        glShaderSource(shaderID, 1, &src_ptr, NULL);
        glCompileShader(shaderID);
        return;
        }
        
void Shader::compile_check(GLuint shaderID)
{
    GLint Result = GL_FALSE;
    int   InfoLogLength;
    glGetShaderiv(shaderID,  GL_COMPILE_STATUS, &Result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
            std::vector<char> ShaderErrorMessage(InfoLogLength);
            glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
            fprintf(stdout, "%s\n", &ShaderErrorMessage[0]);
return;
        }


void Shader::link_check(GLuint& programID)
{
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

        return;
    }
}
