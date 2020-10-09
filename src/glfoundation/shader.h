#pragma once

#include <string>

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
