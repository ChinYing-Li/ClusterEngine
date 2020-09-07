#pragma once

#include "globject.h"

class TrivialObject final : public GLObejct
{
public:
    TrivialObject();
    TrivialObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data,  const color_t color, GLenum fill_mode);
        // using EBO
    TrivialObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, int numindices,const GLuint *indices, const color_t color, GLenum fill_mode);

    ~TrivialObject() = default;
    void draw(GLuint& shaderID) override;
private:
    void init(const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data);
    void init(const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue);
    void init(const GLfloat *vertex_buffer_data, const color_t color);

        // using EBO
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const color_t color);
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const GLfloat *color_buffer_data);
};
