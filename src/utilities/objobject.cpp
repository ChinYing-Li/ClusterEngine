#include <iostream>
#include <cmath>

#include "gamedata.h"
#include "shader.h"
#include "objobject.h"

objobject::objobject(const std::string name, std::shared_ptr<GameData> data_ptr, unsigned int num_instance):
m_name(name),
m_position(0.0f),
m_scale(0.5f),
m_instance(num_instance)
{
    bool load_out = data_ptr->objloader.LoadFile(name);
    if(load_out)
    {
        for(int i = 0; i < data_ptr->objloader.LoadedMeshes.size(); ++i)
        {
            vao_meshes.push_back(VAO_mesh(data_ptr->objloader.LoadedMeshes[i], data_ptr, m_instance));
        }
    }
}

objobject::~objobject()
{}

void objobject::draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project)
{
    //std::cout << "shaderID" << shaderID << std::endl;
    glUseProgram(shaderID);
    calc_model_mat();
    set_matrices(shaderID, view, project);
    
    for(VAO_mesh m: vao_meshes)
    {
        m.draw(shaderID);
    }
    return;
}

void objobject::draw(GLuint& shaderID, glm::mat4& model, glm::mat4& view, glm::mat4& project)
{
    glUseProgram(shaderID);
    set_matrices(shaderID, model, view, project);
    for(VAO_mesh m: vao_meshes)
    {
        m.draw(shaderID);
    }
    return;
}

void objobject::set_instance_mat(std::vector<glm::mat4> &instance_mat)
{
    for(VAO_mesh m: vao_meshes)
    {
        m.send_instance_matrices(instance_mat);
    }
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

void objobject::get_matrices_ID(GLuint &shaderID)
{
    m_umodel = glGetUniformLocation(shaderID, "model");
    m_uproject = glGetUniformLocation(shaderID, "project");
    m_uview = glGetUniformLocation(shaderID, "view");
    
    return;
}

void objobject::set_matrices(GLuint& shaderID, glm::mat4& view, glm::mat4& project)
{
    get_matrices_ID(shaderID);
    calc_model_mat();
    glUniformMatrix4fv(m_umodel, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_uproject, 1, GL_FALSE, &project[0][0]);
    glUniformMatrix4fv(m_uview, 1, GL_FALSE, &view[0][0]);
    return;
}

void objobject::set_matrices(GLuint& shaderID, glm::mat4& model, glm::mat4& view, glm::mat4& project)
{
    get_matrices_ID(shaderID);
    glUniformMatrix4fv(m_umodel, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(m_uproject, 1, GL_FALSE, &project[0][0]);
    glUniformMatrix4fv(m_uview, 1, GL_FALSE, &view[0][0]);
    return;
}
