#include <iostream>

#include "renderable.h"
#include "objloader.h"

namespace Cluster{

Renderable::
Renderable(int n_vertices)
{
  m_num_vertices = n_vertices;
}

void Renderable::set_num_instances(const unsigned int num_instances)
{
  m_num_instances = num_instances;
}

void Renderable::set_instance_attrib()
{
    glBindVertexArray(m_VAO);

    // set attribute pointers for matrix (4 x vec4)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(8*sizeof(float)*m_num_vertices));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(8*sizeof(float)*m_num_vertices+sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(8*sizeof(float)*m_num_vertices+2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(8*sizeof(float)*m_num_vertices+3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glBindVertexArray(0);
    return;
}

void Renderable::
rotate_x(float angle)
{

}

void Renderable::
rotate_y(float angle)
{

}

void Renderable::
rotate_z(float angle)
{

}

void Renderable::
scale_x(float scale)
{

}

void Renderable::
scale_y(float scale)
{

}

void Renderable::
scale_z(float scale)
{

}

void Renderable::
load_model_mat(glm::mat4& model_mat)
{
  model_mat = m_transformation.get_matrix();
}
}
