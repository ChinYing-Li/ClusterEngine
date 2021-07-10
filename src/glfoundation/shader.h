#pragma once

#include <experimental/filesystem>
#include <string>
#include <vector>

#include "glfoundation/glincludes.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
class Shader
{
public:
    Shader() = default;
    Shader(const fs::path path_to_vert,
           const fs::path path_to_frag,
           const fs::path path_to_geo = "");
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

    void use() const;
    GLuint get_ID() const noexcept;
    std::string get_name() const noexcept;

    void set_uniform1i(const std::string name, const int data) const;
    void set_uniform1ui(const std::string name, const unsigned int data) const;
    void set_uniform1iv(const std::string name, const int count, const std::vector<int> &data) const;
    void set_uniform2i(const std::string name, const std::vector<int> &data) const;
    void set_uniform2ui(const std::string name, const std::vector<unsigned int> &data) const;
    void set_uniform1f(const std::string name, const float value) const;
    void set_uniform1fv(const std::string name, const int count, const std::vector<float>& values) const;
    void set_uniform2f(const std::string name, const glm::vec2 &data) const;
    void set_uniform2fv(const std::string name, const int num_element, const std::vector<glm::vec2> &data) const;
    void set_uniform3f(const std::string name, const float x, const float y, const float z) const;
    void set_uniform3fv(const std::string name, const int count, const std::vector<glm::vec3> &data) const;
    void set_uniformMat4f(const std::string name, const glm::mat4 &data) const;

private:
    GLuint m_program_ID;
    GLuint m_vert_ID;
    GLuint m_frag_ID;
    GLuint m_geom_ID;
    std::string m_name;

    std::string read_code(const fs::path& path_to_shader);
    void compile(GLuint& shaderID,
                        const std::string& shader_code);
    void check_compilation(GLuint shaderID);
    void check_linking(GLuint programID);
};

} // namespace Cluster
