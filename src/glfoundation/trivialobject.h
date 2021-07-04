#pragma once

#include <memory>
#include <vector>

#include "renderable.h"
#include "texture.h"

namespace Cluster
{
class TrivialObject final : public Renderable
{
public:
    TrivialObject();
    TrivialObject(GLenum primitive_mode,
                  int num_vertices,
                  const GLfloat *vertex_buffer_data,
                  const color_t color,
                  GLenum fill_mode);
    // using EBO
    TrivialObject(GLenum primitive_mode,
                  int numVertices,
                  const GLfloat *vertex_buffer_data,
                  int num_indices,
                  const GLuint *indices,
                  const color_t color,
                  GLenum fill_mode);
    ~TrivialObject() = default;

    void virtual render(const Shader& shader) override;
    void use_texture(bool use_texture);

protected:
    bool m_use_texture = false;

    std::vector<std::shared_ptr<Texture>> m_textures;

private:
    void init(const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data);
    void init(const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue);
    void init(const GLfloat *vertex_buffer_data, const color_t color);

    // using EBO
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const color_t color);
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const GLfloat *color_buffer_data);
};

} // namespace Cluster
