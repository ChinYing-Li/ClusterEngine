//
//  OBJObject.cpp
//  BumperCarSimulation
//
//  Created by Peter Mai on 3/4/18.
//  Copyright © 2018 William Ma & Peter Mai. All rights reserved.
//

#include "src/gamedata.h"
#include "src/foundation/shader.h"
#include "src/foundation/objobject.h"
#include <iostream>
#include <cmath>

objobject::objobject(const std::string name, std::shared_ptr<GameData> data_ptr):
m_name(name),
m_position(0.0f),
m_scale(0.5f)
{
    bool load_out = data_ptr->objloader.LoadFile(name);
    if(load_out)
    {
        for(int i = 0; i < data_ptr->objloader.LoadedMeshes.size(); ++i)
        {
            vao_meshes.push_back(VAO_mesh(data_ptr->objloader.LoadedMeshes[i], data_ptr));
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
    glUniformMatrix4fv(umodel, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(uproject, 1, GL_FALSE, &m_project[0][0]);
    glUniformMatrix4fv(uview, 1, GL_FALSE, &m_view[0][0]);
    return;
}
