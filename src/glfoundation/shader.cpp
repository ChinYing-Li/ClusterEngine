#include <iostream>
#include <fstream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

namespace fs = std::experimental::filesystem;

namespace Cluster{

// TODO: Update this in case more shaders are added
const unsigned int Shader::m_num_usage = 7;

Shader::
Shader(const fs::path path_to_vert,
       const fs::path path_to_frag,
       const fs::path path_to_geo):
m_name()
{
  m_vert_ID = glCreateShader(GL_VERTEX_SHADER);
  m_frag_ID = glCreateShader(GL_FRAGMENT_SHADER);

  std::string vert_code = read_code(path_to_vert);
  std::string frag_code = read_code(path_to_frag);
  compile(m_vert_ID, vert_code);
  compile(m_frag_ID, frag_code);

  if(!path_to_geo.empty())
  {
        std::string geo_code = read_code(path_to_geo);
        compile(m_geom_ID, path_to_geo);
  }

  try
  {
    check_compilation(m_vert_ID);
    check_compilation(m_frag_ID);
    if(!path_to_geo.empty())
    {
      check_compilation(m_geom_ID);
    }
  }
  catch (std::exception& exc)
  {
    // TODO: create a Log class, I suppose...
  }

  // shader Program
  m_program_ID = glCreateProgram();

  glAttachShader(m_program_ID, m_vert_ID);
  glAttachShader(m_program_ID, m_frag_ID);
  if (!path_to_geo.empty()) { glAttachShader(m_program_ID, m_geom_ID); }

  glLinkProgram(m_program_ID);
  try
  {
    check_linking(m_program_ID);
  }
  catch (std::exception& excp)
  {
    // TODO
    throw excp;
  }

  glDeleteShader(m_vert_ID);
  glDeleteShader(m_frag_ID);

  if (!path_to_geo.empty())
  {
      glDeleteShader(m_geom_ID);
  }

  // TODO: print something to say that we've compiled successfully
}

void Shader::use() const
{
    glUseProgram(m_program_ID);
}

GLuint Shader::
get_ID() const noexcept
{
    return m_program_ID;
}

std::string Shader::
get_name() const noexcept
{
    return m_name;
}

void Shader::
set_uniform1i(const std::string name, const int data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1i(uniform_location, data);
}

void Shader::
set_uniform1ui(const std::string name, const unsigned int data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1ui(uniform_location, data);
};

void Shader::
set_uniform1iv(const std::string name, int count, const std::vector<int> &data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1iv(uniform_location, count, &data[0]);
}

void Shader::
set_uniform2i(const std::string name, const std::vector<int> &data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform2i(uniform_location, data[0], data[1]);
}

void Shader::
set_uniform2ui(const std::string name, const std::vector<unsigned int> &data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform2ui(uniform_location, data[0], data[1]);
}

void Shader::
set_uniform1f(const std::string name, const float value) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1f(uniform_location, value);
}

void Shader::
set_uniform1fv(const std::string name, const int count, const std::vector<float>& values) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform1fv(uniform_location, count, &values[0]);
}

void Shader::
set_uniform2f(const std::string name, const glm::vec2 &data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform2f(uniform_location, data[0], data[1]);
}

void Shader::
set_uniform3f(const std::string name, const float x, const float y, const float z) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniform3f(uniform_location, x, y, z);
}

void Shader::
set_uniform3fv(const std::string name, int count, const std::vector<glm::vec3> &data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  // TODO: Finish set_uniform3fv
}

void Shader::
set_uniformMat4f(const std::string name, const glm::mat4& data) const
{
  int uniform_location = glGetUniformLocation(m_program_ID, name.c_str());
  glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(data));
}

std::string Shader::
read_code(const fs::path& path_to_shader)
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
compile(GLuint& shader_ID, const std::string& shader_code)
{
  char const *src_ptr = shader_code.c_str();
  glShaderSource(shader_ID, 1, &src_ptr, NULL);
  glCompileShader(shader_ID);
}

void Shader::
check_compilation(GLuint shader_ID)
{
    GLint is_compiled = GL_FALSE;
    glGetShaderiv(shader_ID,  GL_COMPILE_STATUS, &is_compiled);

    if (is_compiled == GL_FALSE)
    {
      int log_length;
      glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &log_length);
      std::vector<GLchar> shader_err_message(log_length);
      glGetShaderInfoLog(shader_ID, log_length, NULL, &shader_err_message[0]);
      fprintf(stdout, "%s\n", &shader_err_message[0]);
      throw;
    }
}


void Shader::
check_linking(GLuint program_ID)
{
  GLint is_linked = 0;
  glGetProgramiv(program_ID, GL_LINK_STATUS, &is_linked);

  if (is_linked == GL_FALSE)
  {
        int log_length = 0;
        glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<GLchar> info_log(log_length);
        glGetProgramInfoLog(program_ID, log_length, &log_length, &info_log[0]);
        throw;
  }
  return;
}

} // namespace Cluster
