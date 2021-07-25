// ext
#include "objloader.h"

#include "mesh.h"
#include "material.h"
#include "glfoundation/shader.h"


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

    int vertex_buffer_size = m_num_vertices * sizeof(objl::Vertex) + m_num_instances * sizeof(glm::mat4);
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

    if(m_num_instances > 0) set_instance_attrib();
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
    glBindVertexArray(m_VAO);
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
    set_material_uniform(shader);
    m_material_ptr->bind(shader);
}

void Mesh::
set_material_uniform(const Shader& shader) const
{
    shader.use();
    m_material_ptr->set_uniform(shader);
}

} // namespace Cluster
