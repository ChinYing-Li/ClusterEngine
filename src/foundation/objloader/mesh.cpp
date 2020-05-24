#include <cstddef>
#include <iostream>
#include "mesh.h"
Mesh::Mesh()
{
}
Mesh::Mesh(std::vector<Vertex>& v_vertex, std::vector<MeshTex>& v_meshtex, std::vector<unsigned int> indices):
m_vertices(v_vertex),
m_meshtex(v_meshtex),
m_indices(indices)
{
    init();
}

void Mesh::draw(GLuint shaderID)
{
    glUseProgram(shaderID);
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    
    for(unsigned int i = 0; i < m_meshtex.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_meshtex[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
         else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream
        //std::cout << name+number << std::endl;
        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_meshtex[i].ID);
    }
    
    // draw mesh
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    //glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    std::cout << m_indices.size() << std::endl;
    glPointSize(10);
    glDrawArrays(GL_POINT, 0, m_vertices.size());
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(0);
    return;
}

void Mesh::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (m_vertices.size()*sizeof(Vertex)), &m_vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size()*sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
                          0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
    1,
    3,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, m_normal));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
    2,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex),
    (void*)offsetof(Vertex, m_texcoords));
    glBindVertexArray(0);
    return;
}

