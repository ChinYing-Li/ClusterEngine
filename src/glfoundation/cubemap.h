#pragma once

#include "renderable.h"

namespace Cluster
{

class Cubemap final : public Renderable
{
public:
    Cubemap();
    Cubemap(GLenum primitive_mode,
            int numVertices,
            const GLfloat *vertex_buffer_data,
            std::vector<std::string>& path_to_texture);

    void render(const Shader& shader) override;
    GLuint texture_buffer;
private:
    std::vector<std::string> m_texpath;
    void init(GLenum primitive_mode,
              int numVertices,
              const GLfloat *vertex_buffer_data,
              std::vector<std::string>& path_to_texture);
    void load_texture();
};

}
