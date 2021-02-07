#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace Cluster{
class Shader
{
public:
    Shader() = default;
    Shader(const std::filesystem::path path_to_vert,
           const std::filesystem::path path_to_frag,
           const std::filesystem::path path_to_geo = "");
    ~Shader() = default;

    const static unsigned int m_num_usage;
    enum Usage
    {
      BLOOM,
      BLUR,
      DIRECT_LIGHTING,
      GAMMA_CORRECT,
      GBUFFER,
      SHADOW,
      SKYBOX,
      TEXTURE,
      TONEMAP,
    };

    void use();
    GLuint get_ID() noexcept;
    std::string get_name() noexcept;

    void set_uniform1i(const std::string name, const int data);
    void set_uniform1ui(const std::string name, const unsigned int data);
    void set_uniform1iv(const std::string name, const int count, const std::vector<int> &data);
    void set_uniform2i(const std::string name, const std::vector<int> &data);
    void set_uniform2ui(const std::string name, const std::vector<unsigned int> &data);
    void set_uniform1f(const std::string name, const float value);
    void set_uniform1fv(const std::string name, const int count, const std::vector<float>& values);
    void set_uniform2f(const std::string name, const glm::vec2 &data);
    void set_uniform2fv(const std::string name, const int num_element, const std::vector<glm::vec2> &data);
    void set_uniform3f(const std::string name, const glm::vec3 &data);
    void set_uniform3fv(const std::string name, const int count, const std::vector<glm::vec3> &data);
    void set_uniformMat4f(const std::string name, const glm::mat4 &data);

private:
    GLuint m_program_ID;
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    std::string m_name;

    std::string read_code(const std::filesystem::path& path_to_shader);
    void compile(GLuint& shaderID,
                        const std::string& shader_code);
    void check_compilation(GLuint shaderID);
    void check_linking(GLuint programID);
};

} // namespace Cluster
