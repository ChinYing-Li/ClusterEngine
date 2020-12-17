#pragma once

#include <string>
#include <vector>

#include "glincludes.h"

namespace Cluster{
class Shader
{
public:
    Shader() = default;
    Shader(const std::string path_to_vert,
           const std::string path_to_frag,
           const std::string path_to_geo,
           const std::string name);
    ~Shader() = default;

    void use();
    GLuint get_ID() noexcept;
    std::string get_name() noexcept;

    void set_uniform1i(std::string name, int data);
    void set_uniform1ui(std::string name, unsigned int data);
    void set_uniform1iv(std::string name, int count, std::vector<int> &data);
    void set_uniform2i(std::string name, std::vector<int> &data);
    void set_uniform2ui(std::string name, std::vector<unsigned int> &data);
    void set_uniform1f(std::string name, float value);
    void set_uniform1fv(std::string name, int count, float* values);
    void set_uniform2f(std::string name, const glm::vec2 &data);
    void set_uniform3f(std::string name, const glm::vec3 &data);
    void set_uniform3fv(std::string name, int count, std::vector<glm::vec3> &data);
    void uniformMatrix4f(std::string name, glm::mat4 &data);

private:
    GLuint m_program_ID;
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    std::string m_name;

    std::string read_code(const std::string path_to_shader);
    void compile_shader(GLuint& shaderID,
                        const std::string& shader_code);
    void compile_check(GLuint shaderID);
    void link_check(GLuint programID);
};

} // namespace Cluster
