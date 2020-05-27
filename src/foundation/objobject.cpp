//
//  OBJObject.cpp
//  BumperCarSimulation
//
//  Created by Peter Mai on 3/4/18.
//  Copyright © 2018 William Ma & Peter Mai. All rights reserved.
//

#include "src/foundation/objobject.h"
#include "src/foundation/shader.h"
#include "src/foundation/objloader.h"
#include <iostream>
#include <cmath>

VAO_mesh::VAO_mesh(objl::Mesh& mesh, GameData& gamedata):
name(mesh.MeshName),
use_maps(6, false)
{
    init(mesh);
    m_material_ptr = new objl::Material;
    *m_material_ptr = mesh.MeshMaterial;
    std::cout << m_material_ptr->illum << std::endl;
    m_numindices = mesh.Indices.size();
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_Ka"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_Ka);
        use_maps[0] = (map_ptrs["map_Ka"] != nullptr);
    }
    if(m_material_ptr->map_Kd.size())
    {
        map_ptrs["map_Kd"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_Kd);
        use_maps[1] = (map_ptrs["map_Kd"] != nullptr);
    }
    if(m_material_ptr->map_Ks.size())
    {
        map_ptrs["map_Ks"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_Ks);
        use_maps[2] = (map_ptrs["map_Ks"] != nullptr);
    }
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_Ns"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_Ns);
        use_maps[3] = (map_ptrs["map_Ns"] != nullptr);
    }
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_d"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_d);
        use_maps[4] = (map_ptrs["map_d"] != nullptr);
    }
    if(m_material_ptr->map_bump.size())
    {
        map_ptrs["map_bump"] = gamedata.resmanager_ptr->retrieve_texture(m_material_ptr->map_bump);
        use_maps[5] = (map_ptrs["map_bump"] != nullptr);
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
    
    glBufferData (GL_ARRAY_BUFFER, mesh.Vertices.size()*sizeof(objl::Vertex), &mesh.Vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        8*sizeof(float),                            // stride
        (void *) 0                      // array buffer offset
    );
    glVertexAttribPointer(
        1,      // attribute 1. Normal
        3,
        GL_FLOAT,          // type
        GL_FALSE,                     // normalized?
        8*sizeof(float),                            // stride
        (void *)(3*sizeof(GLfloat))// array buffer offset
    );
    glVertexAttribPointer(
        2,      // attribute 1. texture
        2,
        GL_FLOAT,          // type
        GL_FALSE,    // normalized?
        8*sizeof(float),                            // stride
        (void *)(6*sizeof(GLfloat))// array buffer offset
    );
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size()*sizeof(unsigned int), &mesh.Indices[0], GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void VAO_mesh::draw(GLuint& shaderID)
{
    glBindVertexArray (VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    set_material_uniform(shaderID);
    draw_textures(shaderID);
    glDrawElements(GL_TRIANGLES, m_numindices, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    return;
}

void VAO_mesh::draw_textures(GLuint shaderID)
{
    std::cout << map_ptrs.size() << std::endl;
    auto map_it = map_ptrs.begin();
    int count = 0;
    for(auto it = use_maps.begin(); it!=use_maps.end(); ++it)
    {
        //std::cout << map_it->first << std::endl;
        if(*it)
        {
            glActiveTexture(GL_TEXTURE0+count);
            glBindTexture(map_it->second->m_format, map_it->second->m_ID);
            glUniform1i(glGetUniformLocation(shaderID, (map_it->first).c_str()), count);
            ++map_it;
        }
        ++count;
    }
    return;
}

void VAO_mesh::set_material_uniform(GLuint& shaderID)
{
    glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), m_material_ptr->Ka.X, m_material_ptr->Ka.Y, m_material_ptr->Ka.Z);
    glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), m_material_ptr->Kd.X, m_material_ptr->Kd.Y, m_material_ptr->Kd.Z);
    glUniform3f(glGetUniformLocation(shaderID, "material.specular"), m_material_ptr->Ks.X, m_material_ptr->Ks.Y, m_material_ptr->Ks.Z);
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), m_material_ptr->Ns);
    
}

objobject::objobject(objl::Loader& loader, const std::string name, GameData& gamedata):
m_name(name),
m_position(0.0f),
m_scale(0.5f)
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

void objobject::draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project)
{
    glUseProgram(shaderID);
    calc_model_mat();
    m_view = view;
    m_project = project;
    set_matrices(shaderID, view, project);
    
    for(VAO_mesh m: vao_meshes)
    {
        m.draw(shaderID);
    }
    return;
}

void objobject::calc_model_mat()
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);
    m_model = glm::scale(m_model, m_scale);
    /*std::cout << "mmodel" << std::endl;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << m_model[i][j] << " ";
        }
        std::cout << "\n\n" << std::endl;
    }*/
    return;
}

void objobject::set_matrices(GLuint& shaderID, glm::mat4& view, glm::mat4& project)
{
    GLuint umodel = glGetUniformLocation(shaderID, "model");
    
    GLuint uproject = glGetUniformLocation(shaderID, "project");
    GLuint uview = glGetUniformLocation(shaderID, "view");
    std::cout << umodel << " " << uproject << " " << uview << std::endl;
    glUniformMatrix4fv(umodel, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(uproject, 1, GL_FALSE, &m_project[0][0]);
    glUniformMatrix4fv(uview, 1, GL_FALSE, &m_view[0][0]);
    return;
}
