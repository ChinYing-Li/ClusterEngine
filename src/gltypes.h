#pragma once
#include <memory>
#include <string>
#include "foundation/texture.h"
#include "gamestate/state.h"
#include "utilities/managers/Imanagers.h"

class GameData
{
public:
    GameData();
    //GameData(bool glcontext_created);
    ~GameData() = default;
    std::unique_ptr<ResourceManager> resmanager_ptr = nullptr;
    std::unique_ptr<InputManager> inputmanager_ptr = nullptr;
    GLFWwindow* m_windowptr;
    void init();
    //State gstate;
};

#ifndef _DATA
#define _DATA
extern GameData _data;
#endif

class VAO
{
public:
    VAO(){};
    //VAO(GLuint& vertArrID);
    ~VAO() = default;
    
    GLuint m_vertexarrayID;
    GLuint m_vertexbuffer;
    GLuint color_buffer;
    GLuint m_indicebuffer; // EBO
    
    GLenum m_primitivemode;
    GLenum m_fillmode;
    int    m_numvert;
    int m_numindices;
    void virtual draw(GLuint shaderID) = 0;
    void init(GLenum primitive_mode, int numVertices);
protected:
    bool useEBO = false;
};

class VAO_monotone: public VAO
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

class VAO_texture: public VAO
{
public:
    VAO_texture();
    VAO_texture(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const std::string texname, GameData& gamedata); // only lookup names at resourcemanager
    ~VAO_texture() = default;
    
    void draw(GLuint shaderID) override;
private:
    std::vector<std::string> m_texpath;
    void init(const GLfloat *vertex_buffer_data, GameData& gamedata);
    
    std::shared_ptr<Texture> m_texptr = nullptr;
    std::string m_texname;
    void load_texture();
};

class VAO_material: public VAO
{
public:
    VAO_material();
    VAO_material(GLenum primitive_mode, int num_vertices, const GLfloat* vertex_position, const GLfloat* vertex_normal, GameData& gamedata);
    ~VAO_material();
    void draw(GLuint shaderID);
private:
    void init(const GLfloat *vertex_buffer_data, const GLfloat* vertex_normal, GameData& gamedata);
};


/*
class VAO_cubemap: public VAO
{
public:
    VAO_cubemap();
    VAO_cubemap(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture);
    void draw(GLuint shaderID) override;
    GLuint texture_buffer;
private:
    std::vector<std::string> m_texpath;
    void init(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string>& path_to_texture);
    void load_texture();
};
*/
