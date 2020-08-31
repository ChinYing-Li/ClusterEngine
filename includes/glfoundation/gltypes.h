#pragma once

#include <memory>
#include <string>

#include "includes/glfoundation/texture.h"
#include "gamestate/state.h"
#include "utilities/managers/Imanagers.h"


// Forward declarations
namespace objl
{
class Loader;
class Material;
class Mesh;
}

class GameData;

class VAO
{
public:
    VAO(){};
    //VAO(GLuint& vertArrID);
    ~VAO() = default;
    
    GLuint m_vertexarray;
    GLuint m_vertexbuffer;
    GLuint color_buffer;
    GLuint m_indicebuffer; // EBO
    
    GLenum m_primitivemode;
    GLenum m_fillmode;
    bool isinstancing = false;
    
    int m_numvert;
    int m_numindices;
    
    void virtual draw(GLuint& shaderID) = 0;
    void set_instance_attrib();
    void virtual send_instance_matrices(std::vector<glm::mat4>& instance_models){};
    void init(GLenum primitive_mode, int numVertices);

protected:
    bool useEBO = false;
};

class VAO_mesh final : public VAO
{
public:
    VAO_mesh(objl::Mesh& mesh, std::shared_ptr<GameData> data_ptr, unsigned int numinstance);
    ~VAO_mesh() = default;
    void draw(GLuint& shaderID) override;
    
    std::string name;
    void send_instance_matrices(std::vector<glm::mat4>& instance_models) override;
private:
    unsigned int m_numinstance;
    void init(objl::Mesh& mesh);
    void draw_textures(GLuint shaderID);
    void set_material_uniform(GLuint& shaderID);
    
    objl::Material* m_material_ptr = nullptr;
    std::map<std::string, std::shared_ptr<Texture>> map_ptrs;
    std::vector<bool> use_maps;
    
    /*map_Ka_ptr -->GL_TEXTURE0
    map_Kd_ptr = nullptr; GL_TEXTURE1
    map_Ks_ptr = nullptr; GL_TEXTURE2
    map_Ns_ptr = nullptr;GL_TEXTURE3
    map_d_ptr = nullptr; GL_TEXTURE4
    map_bump_ptr = nullptr; GL_TEXTURE5*/
};

class VAO_monotone final : public VAO
{
public:
    VAO_monotone();
    VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data,  const color_t color, GLenum fill_mode);
    // using EBO
    VAO_monotone(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, int numindices,const GLuint *indices, const color_t color, GLenum fill_mode);
    
    ~VAO_monotone() = default;
    void draw(GLuint& shaderID) override;
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
    
    void draw(GLuint& shaderID) override;
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
    void draw(GLuint& shaderID);
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
