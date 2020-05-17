#pragma once

#include "../../includes/gl_headers.h"

#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texcoords;
};

struct MeshTex
{
    unsigned int ID;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Vertex>& v_vertex, std::vector<MeshTex>& v_meshtex, std::vector<unsigned int> indices);
    ~Mesh() = default;
    
    std::vector<Vertex> m_vertices;
    std::vector<MeshTex> m_meshtex;
    std::vector<unsigned int> m_indices;
    void draw(GLuint shaderID);
private:
    // TO DO: use VAO handle instead
    
    GLuint VAO, VBO, EBO;
    void init();
};
