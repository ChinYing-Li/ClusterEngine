#pragma once

#include "globject.h"

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

    void render(GLuint& shaderID) override;
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
