#pragma once
#include <string.h>
#include "main.h"
#include "foundation/texture.h"

class GLObejct
{
public:
    GLObejct(){};
    //VAO(GLuint& vertArrID);
    ~GLObejct() = default;
    
    GLuint m_vertexarrayID;
    GLuint m_vertexbuffer;
    GLuint color_buffer;
    GLuint m_indicebuffer; // EBO
    
    GLenum m_primitivemode;
    GLenum m_fillmode;
    int    m_numvert;
    int m_numindices;
    void virtual draw(GLuint shaderID) = 0;
    void init_member(GLenum primitive_mode, int numVertices);
protected:
    bool useEBO = false;
};

class VAO_monotone: public GLObejct
{
public:
    VAO_monotone();
    VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data,  const color_t color, GLenum fill_mode);
    // using EBO
    VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, int numindices,const GLuint *indices, const color_t color, GLenum fill_mode);
    
    ~VAO_monotone() = default;
    void draw(GLuint shaderID) override;
private:
    
    void init(const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data);
    void init(const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue);
    void init(const GLfloat *vertex_buffer_data, const color_t color);
    
    // using EBO
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const color_t color);
    void init(const GLfloat *vertex_buffer_data, const GLuint *indices, const GLfloat *color_buffer_data);
};

class VAO_texture: public GLObejct
{
public:
    VAO_texture();
    VAO_texture(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture); // only lookup names at resourcemanager
    ~VAO_texture() = default;
    GLuint texture_buffer;
    
    void draw(GLuint shaderID) override;
private:
    std::vector<std::string> m_texpath;
    void init(const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture);
    std::shared_ptr<Texture> m_texptr = nullptr;
    void load_texture();
};

class Cubemap: public GLObejct
{
public:
    Cubemap();
    Cubemap(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture);
    void draw(GLuint shaderID) override;
    GLuint texture_buffer;
private:
    std::vector<std::string> m_texpath;
    void init(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture);
    void load_texture();
};
