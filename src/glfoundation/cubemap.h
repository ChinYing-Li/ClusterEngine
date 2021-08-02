#pragma once

#include <experimental/filesystem>
#include <vector>

#include "renderable.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
class Cubemap : public Renderable
{
public:
    Cubemap();
    Cubemap(GLenum primitive_mode,
            int numVertices,
            const GLfloat *vertex_buffer_data);
    ~Cubemap() = default;
    bool initialize_texture(std::vector<fs::path>& path_to_texture);
    void render(const Shader& shader) override;
    bool is_usable();

private:
    std::unique_ptr<TextureCubemap> m_texture_ptr;
    std::vector<fs::path> m_texpath;

    void init(GLenum primitive_mode,
              int numVertices,
              const GLfloat *vertex_buffer_data);
};

}
