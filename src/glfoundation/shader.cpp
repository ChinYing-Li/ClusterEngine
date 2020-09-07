#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"

Shader::
Shader(const std::string path_to_vert,
       const std::string path_to_frag,
       const std::string path_to_geo = "",
       const std::string name = ""):
m_name(name)
{
  m_vert_ID = glCreateShader(GL_VERTEX_SHADER);
  m_frag_ID = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vert_code = read_code(path_to_vert);
  std::string frag_code = read_code(path_to_frag);
  compile_shader(m_vert_ID, vert_code);
  compile_check(m_vert_ID);
  compile_shader(m_frag_ID, frag_code);
  compile_check(m_frag_ID);
 
  if(!path_to_geo.empty())
  {
        std::string geo_code = read_code(path_to_geo);
        compile_shader(m_geom_ID, path_to_geo);
        compile_check(m_geom_ID);
  }

  // shader Program
  m_program_ID = glCreateProgram();

  glAttachShader(m_program_ID, m_vert_ID);
  glAttachShader(m_program_ID, m_frag_ID);

  if (!path_to_geo.empty())
  {
      glAttachShader(m_program_ID, m_geom_ID);
  }

  glLinkProgram(m_program_ID);
  link_check(m_program_ID);

  glDeleteShader(m_vert_ID);
  glDeleteShader(m_frag_ID);

  if (!path_to_geo.empty())
  {
      glDeleteShader(m_geom_ID);
  }
}

void Shader::use()
{
    glUseProgram(m_program_ID);
}

GLuint Shader::
get_ID() noexcept
{
    return m_program_ID;
}

std::string Shader::
get_name() noexcept
{
    return m_name;
}
        
std::string Shader::
read_code(const std::string path_to_shader)
{
  std::string  code;
  std::ifstream stream(path_to_shader, std::ios::in);

  if (stream.is_open())
  {
    std::cout << "reading shader code: " << std::endl;

    std::string Line = "";

    while (getline(stream, Line))
      code += "\n" + Line;

    stream.close();
  }
  return code;
}


void Shader::
compile_shader(GLuint& shader_ID,
               const std::string& shader_code)
{
  char const *src_ptr = shader_code.c_str();
  glShaderSource(shader_ID, 1, &src_ptr, NULL);
  glCompileShader(shader_ID);
}
        
void Shader::
compile_check(GLuint shader_ID)
{
    GLint result = GL_FALSE;
    int   info_log_length;

    glGetShaderiv(shader_ID,  GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &info_log_length);

    std::vector<GLchar> shader_err_message(info_log_length);

    glGetShaderInfoLog(shader_ID, info_log_length, NULL, &shader_err_message[0]);

    fprintf(stdout, "%s\n", &shader_err_message[0]);
}


void Shader::
link_check(GLuint program_ID)
{
  GLint is_linked = 0;
  glGetProgramiv(program_ID, GL_LINK_STATUS, &is_linked);

  if (is_linked == GL_FALSE)
  {
        GLint max_length = 0;
        glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program_ID, max_length, &max_length, &info_log[0]);

        return;
  }
}
