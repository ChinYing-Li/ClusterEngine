#include <iostream>
#include <fstream>
#include <vector>

#include "shader.h"

namespace Cluster{
Shader::
Shader(const std::string path_to_vert,
       const std::string path_to_frag,
       const std::string path_to_geo = "",
       const std::string name = ""):
m_name(name)
{
  m_vert_ID = glCreateShader(GL_VERTEX_SHADER);
  m_frag_ID = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vert_code = read_shader_code(path_to_vert);
  std::string frag_code = read_shader_code(path_to_frag);
  compile_shader(m_vert_ID, vert_code);
  compile_check(m_vert_ID);
  compile_shader(m_frag_ID, frag_code);
  compile_check(m_frag_ID);

  if(!path_to_geo.empty())
  {
        std::string geo_code = read_shader_code(path_to_geo);
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

void Shader::
set_uniform1i(const std::string name, const int data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1i(uniform_location, data);
}

void Shader::
set_uniform1ui(const std::string name, const unsigned int data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1ui(uniform_location, data);
};

void Shader::
set_uniform1iv(const std::string name, int count, const std::vector<int> &data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1iv(uniform_location, count, &data[0]);
}

void Shader::
set_uniform2i(const std::string name, const std::vector<int> &data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform2i(uniform_location, data[0], data[1]);
}

void Shader::
set_uniform2ui(const std::string name, const std::vector<unsigned int> &data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform2ui(uniform_location, data[0], data[1]);
}

void Shader::
set_uniform1f(const std::string name, const float value)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1f(uniform_location, value);
}

void Shader::
set_uniform1fv(const std::string name, const float* values)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
}

void Shader::
set_uniform2f(const std::string name, const glm::vec2 &data)
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
}

void Shader::
set_uniform3f(const std::string name, const glm::vec3 &data)
{

}

void Shader::
set_uniform3fv(const std::string name, int count, const std::vector<glm::vec3> &data)
{

}

void Shader::
set_uniformMat4f(const std::string name, const glm::mat4 &data)
{

}

std::string Shader::
read_shader_code(const std::filesystem::path& path_to_shader)
{
  std::string  code;
  std::ifstream stream(path_to_shader.c_str(), std::ios::in);

  if (stream.is_open())
  {
    std::cout << "Reading shader code: " << std::endl;
    std::string line = "";

    while (getline(stream, line))
      code += "\n" + line;

    stream.close();
  }
  return code;
}


void Shader::
compile_shader(GLuint& shader_ID, const std::string& shader_code)
{
  char const *src_ptr = shader_code.c_str();
  glShaderSource(shader_ID, 1, &src_ptr, NULL);
  glCompileShader(shader_ID);
}

void Shader::
compile_check(GLuint shader_ID)
{
    GLint result = GL_FALSE;
    int info_log_length;

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

} // namespace Cluster
