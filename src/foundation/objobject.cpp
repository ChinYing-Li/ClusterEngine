//
//  OBJObject.cpp
//  BumperCarSimulation
//
//  Created by Peter Mai on 3/4/18.
//  Copyright © 2018 William Ma & Peter Mai. All rights reserved.
//

#include "objobject.h"
#include "objloader.h"
#include "shader.h"
#include <iostream>
#include <cmath>

VAO_mesh::VAO_mesh(objl::Mesh& mesh, GameData& gamedata):
name(mesh.MeshName),
use_maps(6, false)
{
    init(mesh);
    m_material = mesh.MeshMaterial;
    m_numindices = mesh.Indices.size();
    if(m_material.map_Ka.size())
    {
        map_ptrs[0] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_Ka);
        use_map_Ka = (map_ptrs[0] != nullptr);
    }
    if(m_material.map_Kd.size())
    {
        map_ptrs[1] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_Kd);
        use_map_Kd = (map_ptrs[1] != nullptr);
    }
    if(m_material.map_Ks.size())
    {
        map_ptrs[2] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_Ks);
        use_map_Ks = (map_ptrs[2] != nullptr);
    }
    if(m_material.map_Ka.size())
    {
        map_ptrs[3] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_Ns);
        use_map_Ns = (map_ptrs[3] != nullptr);
    }
    if(m_material.map_Ka.size())
    {
        map_ptrs[4] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_d);
        use_map_d = (map_ptrs[4] != nullptr);
    }
    if(m_material.map_bump.size())
    {
        map_ptrs[5] = gamedata.resmanager_ptr->retrieve_texture(m_material.map_bump);
        use_map_bump = (map_ptrs[5] != nullptr);
    }
    return;
}

void VAO_mesh::init(objl::Mesh& mesh)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers (1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray (VAO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
    
    glBufferSubData (GL_ARRAY_BUFFER, 0, mesh.Vertices.size()*sizeof(objl::Vertex), &mesh.Vertices[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size()*sizeof(unsigned int), &mesh.Indices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        sizeof(objl::Vertex),                            // stride
        (void *) 0                      // array buffer offset
    );
    glVertexAttribPointer(
        1,      // attribute 1. Normal
        3,
        GL_FLOAT,          // type
        GL_FALSE,                     // normalized?
        sizeof(objl::Vertex),                            // stride
        (void *)(3*sizeof(GLfloat))// array buffer offset
    );
    glVertexAttribPointer(
        2,      // attribute 1. Normal
        2,
        GL_FLOAT,          // type
        GL_FALSE,    // normalized?
        sizeof(objl::Vertex),                            // stride
        (void *)(6*sizeof(GLfloat))// array buffer offset
    );
    
    glBindVertexArray(0);
}

void VAO_mesh::draw(Shader& shader)
{
    glBindVertexArray (VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    enable_textures();
    glDrawElements(GL_TRIANGLES, m_numindices, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
    return;
}

void VAO_mesh::enable_textures()
{
    for(auto it = map_ptrs.cbegin(); it != map_ptrs.cend(); ++i)
    {
        if(use_maps[it->first])
        {
            glActiveTexture(GL_TEXTURE0 + it->first);
            glBindTexture(GL_TEXTURE_2D, (it->second)->m_ID);
        }
    }
    return;
}

objobject::objobject(objl::Loader& loader, const std::string name, GameData& gamedata):
m_name(name),
m_position(0.0f),
m_scale(0.0f)
{
    bool load_out = loader.LoadFile(name);
    if(load_out)
    {
        for(int i = 0; i < loader.LoadedMeshes.size(); ++i)
        {
            vao_meshes.push_back(VAO_mesh(loader.LoadedMeshes[i], gamedata));
        }
    }
}

objobject::~objobject()
{}

void objobject::draw(Shader& shaderprogram, glm::mat4& view, glm::mat4& project)
{
    glUseProgram(shaderprogram.ID);
    set_matrices(Shader& shaderprogram, glm::mat4& view, glm::mat4& project);
    
    for(VAO_Mesh m: vao_meshes)
    {
        m.draw(shaderprogram);
    }
    return;
}

void objobject::set_model_mat()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::scale(m_model, m_scale);
    m_model = m_model*glm::translate(m_position);
}

void objobject::set_matrices(Shader& shaderprogram, glm::mat4& view, glm::mat4& project)
{
    GLuint umodel = glGetUniformLocation(shaderprogram.ID, "model");
    GLuint uproject = glGetUniformLocation(shaderprogram.ID, "project");
    GLuint uview = glGetUniformLocation(shaderprogram.ID, "view");
    glUniformMatrix4fv(umodel, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(uproject, 1, GL_FALSE, &project[0][0]);
    glUniformMatrix4fv(uview, 1, GL_FALSE, &view[0][0]);
    return;
}
