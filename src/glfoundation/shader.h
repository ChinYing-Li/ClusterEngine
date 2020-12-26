#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "glincludes.h"

namespace Cluster{
class Shader
{
public:
    Shader() = default;
    Shader(const std::filesystem::path path_to_vert,
           const std::filesystem::path path_to_frag,
           const std::filesystem::path path_to_geo,
           const std::filesystem::path name);
    ~Shader() = default;

    void use();
    GLuint get_ID() noexcept;
    std::string get_name() noexcept;

    void set_uniform1i(const std::string name, const int data);
    void set_uniform1ui(const std::string name, const unsigned int data);
    void set_uniform1iv(const std::string name, const int count, const std::vector<int> &data);
    void set_uniform2i(const std::string name, const std::vector<int> &data);
    void set_uniform2ui(const std::string name, const std::vector<unsigned int> &data);
    void set_uniform1f(const std::string name, const float value);
    void set_uniform1fv(const std::string name, const int count, const std::vector<float> values);
    void set_uniform2f(const std::string name, const glm::vec2 &data);
    void set_uniform3f(const std::string name, const glm::vec3 &data);
    void set_uniform3fv(const std::string name, const int count, const std::vector<glm::vec3> &data);
    void set_uniformMat4f(const std::string name, const glm::mat4 &data);

private:
    GLuint m_program_ID;
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    std::string m_name;

    std::string read_shader_code(const std::filesystem::path& path_to_shader);
    void compile_shader(GLuint& shaderID,
                        const std::string& shader_code);
    void compile_check(GLuint shaderID);
    void link_check(GLuint programID);
};

} // namespace Cluster
