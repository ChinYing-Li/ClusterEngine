#include "mesh.h"
#include "src/utilities/material.h"
#include "objloader.h"
#include "src/glfoundation/shader.h"

namespace Cluster
{
Mesh::
Mesh(objl::Mesh& mesh, fs::path obj_root_dir):
Renderable()
{
    m_using_EBO = true;
    m_num_indices = mesh.Indices.size();
    m_num_vertices = mesh.Vertices.size();
    m_primitive_mode = GL_TRIANGLES;

    init(mesh);
    m_material_ptr = new Material(mesh.MeshMaterial, obj_root_dir);
}

Mesh::~Mesh()
{
  delete m_material_ptr;
}

void Mesh::
init(objl::Mesh& mesh)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers (1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray (m_VAO);
    glBindBuffer (GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    int vertex_buffer_size = m_num_vertices * sizeof(objl::Vertex) + m_numinstance * sizeof(glm::mat4);
    std::cout << vertex_buffer_size << " buffer size" << std::endl;
    glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_num_vertices*sizeof(objl::Vertex), &mesh.Vertices[0]);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size()*sizeof(unsigned int), &mesh.Indices[0], GL_STATIC_DRAW);
    gl_debug();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(
        0,                            // attribute 0. Vertices
        3,                            // size (x,y,z)
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        8*sizeof(float),              // stride
        (void *) 0                    // array buffer offset
    );

    glVertexAttribPointer(
        1,                            // attribute 1. Normal
        3,                            //
        GL_FLOAT,                     // type
        GL_FALSE,                     // normalized?
        8*sizeof(float),              // stride
        (void *)(3*sizeof(GLfloat))   // array buffer offset
    );

    glVertexAttribPointer(
        2,      // attribute 2. texture
        2,
        GL_FLOAT,          // type
        GL_FALSE,    // normalized?
        8*sizeof(float),                            // stride
        (void *)(6*sizeof(GLfloat))// array buffer offset
    );

    if(m_numinstance > 0) set_instance_attrib();
    gl_debug();
    glBindVertexArray(0);
}

void Mesh::
send_instance_matrices(std::vector<glm::mat4>& instance_models)
{
    if (!m_instanced) return;

    glBindVertexArray (m_VAO);
    glBindBuffer (GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData (GL_ARRAY_BUFFER,
                     m_num_vertices * sizeof(objl::Vertex), //offsest
                     m_num_instances * sizeof(glm::mat4),
                     &instance_models[0][0][0]);
    return;
}

void Mesh::
render(const Shader& shader)
{
    glBindVertexArray (m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    gl_debug();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    gl_debug();

    if (m_instanced)
    {
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        set_material_uniform(shader);
        draw_textures(shader);
        glDrawElementsInstanced(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, nullptr, 2);
    }
    else
    {
        set_material_uniform(shader);
        draw_textures(shader);
        glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
    return;
}

void Mesh::
draw_textures(const Shader& shader)
{
    auto map_it = map_ptrs.begin();
    int count = 0;
    std::string prefix = "material.use_";
    GLuint shader_id = shader.get_ID();

    for(auto it = use_maps.begin(); it != use_maps.end(); ++it)
    {
        std::cout << map_it->first << "map texture" << map_it->second->m_ID << std::endl;
        if(*it)
        {
            glActiveTexture(GL_TEXTURE0+count);
            glBindTexture(map_it->second->m_format, map_it->second->m_ID);
            glUniform1i(glGetUniformLocation(shader_id, (map_it->first).c_str()), count);
            std::string uniform_name = prefix + map_it->first;
            glUniform1i(glGetUniformLocation(shader_id, uniform_name.c_str()), int(true));
            ++map_it;
            ++count;
        }
    }
    return;
}

void Mesh::
set_material_uniform(const Shader& shader)
{
    shader.use();
    glUniform3f(glGetUniformLocation(shader_id, "material.ambient"), m_material_ptr->Ka.X, m_material_ptr->Ka.Y, m_material_ptr->Ka.Z);
    glUniform3f(glGetUniformLocation(shader_id, "material.diffuse"), m_material_ptr->Kd.X, m_material_ptr->Kd.Y, m_material_ptr->Kd.Z);
    glUniform3f(glGetUniformLocation(shader_id, "material.specular"), m_material_ptr->Ks.X, m_material_ptr->Ks.Y, m_material_ptr->Ks.Z);
    glUniform1f(glGetUniformLocation(shader_id, "material.shininess"), m_material_ptr->Ns);
}

} // namespace Cluster
