#include <iostream>

#include "globject.h"
#include "objloader.h"
#include "game.h"

namespace Cluster{

Renderable::Renderable(int n_vertices)
{
  m_num_vertices = n_vertices;
}

void Renderable::set_instance_attrib()
{
    glBindVertexArray(m_VAO);

    // set attribute pointers for matrix (4 times vec4)
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

void rotate_y(float angle)
{

}

void rotate_z(float angle)
{

}

void scale_x(float scale)
{

}

void scale_y(float scale)
{

}

void scale_z(float scale)
{

}

}

/*
VAO_mesh::VAO_mesh(objl::Mesh& mesh, std::shared_ptr<GameData> data_ptr, unsigned int numinstance = 0):
VAO(),
name(mesh.MeshName),
m_numinstance(numinstance),
use_maps(6, false)
{
    useEBO = true;
    m_numindices = mesh.Indices.size();
    m_numvert = mesh.Vertices.size();
    GLObejct::init(GL_TRIANGLES, 0);
    init(mesh);
    
    m_material_ptr = new objl::Material;
    *m_material_ptr = mesh.MeshMaterial;
    
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_Ka"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_Ka);
        use_maps[0] = (map_ptrs["map_Ka"] != nullptr);
    }
    if(m_material_ptr->map_Kd.size())
    {
        map_ptrs["map_Kd"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_Kd);
        use_maps[1] = (map_ptrs["map_Kd"] != nullptr);
    }
    if(m_material_ptr->map_Ks.size())
    {
        map_ptrs["map_Ks"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_Ks);
        use_maps[2] = (map_ptrs["map_Ks"] != nullptr);
    }
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_Ns"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_Ns);
        use_maps[3] = (map_ptrs["map_Ns"] != nullptr);
    }
    if(m_material_ptr->map_Ka.size())
    {
        map_ptrs["map_d"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_d);
        use_maps[4] = (map_ptrs["map_d"] != nullptr);
    }
    if(m_material_ptr->map_bump.size())
    {
        map_ptrs["map_bump"] = data_ptr->resmanager_ptr->retrieve_texture(m_material_ptr->map_bump);
        use_maps[5] = (map_ptrs["map_bump"] != nullptr);
    }
    return;
}


void VAO_mesh::init(objl::Mesh& mesh)
{
    glGenVertexArrays(1, &m_vertexarray);
    glGenBuffers (1, &m_vertexbuffer);
    glGenBuffers(1, &m_indicebuffer);
    glBindVertexArray (m_vertexarray);
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, m_indicebuffer);

    int vertexbuffersize = m_numvert*sizeof(objl::Vertex) + m_numinstance * sizeof(glm::mat4);
    std::cout << vertexbuffersize << " buffer size" << std::endl;
    glBufferData (GL_ARRAY_BUFFER, vertexbuffersize, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_numvert*sizeof(objl::Vertex), &mesh.Vertices[0]);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size()*sizeof(unsigned int), &mesh.Indices[0], GL_STATIC_DRAW);
    glDebug();
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
    if(m_numinstance > 0) set_instance_attrib();
    glDebug();
    glBindVertexArray(0);
}

void VAO_mesh::send_instance_matrices(std::vector<glm::mat4>& instance_models)
{
    if(m_numinstance == 0) return;
    glBindVertexArray (m_vertexarray);
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer);
    glBufferSubData (GL_ARRAY_BUFFER,
                     m_numvert*sizeof(objl::Vertex), //offsest
                     m_numinstance*sizeof(glm::mat4),
                     &instance_models[0][0][0]);
    return;
}

void VAO_mesh::draw(GLuint& shaderID)
{
    glBindVertexArray (m_vertexarray);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicebuffer);
    glDebug();
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDebug();

    if(m_numinstance>0)
    {
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);
        glEnableVertexAttribArray(6);
        set_material_uniform(shaderID);
        draw_textures(shaderID);
        glDrawElementsInstanced(GL_TRIANGLES, m_numindices, GL_UNSIGNED_INT, nullptr, 2);
    }
    else
    {
        set_material_uniform(shaderID);
        draw_textures(shaderID);
        glDrawElements(GL_TRIANGLES, m_numindices, GL_UNSIGNED_INT, nullptr);
    }
    
    glBindVertexArray(0);
    return;
}

void VAO_mesh::draw_textures(GLuint shaderID)
{
    auto map_it = map_ptrs.begin();
    int count = 0;
    std::string prefix = "material.use_";
    for(auto it = use_maps.begin(); it!=use_maps.end(); ++it)
    {
        std::cout << map_it->first << "map texture" << map_it->second->m_ID << std::endl;
        if(*it)
        {
            glActiveTexture(GL_TEXTURE0+count);
            glBindTexture(map_it->second->m_format, map_it->second->m_ID);
            glUniform1i(glGetUniformLocation(shaderID, (map_it->first).c_str()), count);
            std::string uniform_name = prefix + map_it->first;
            glUniform1i(glGetUniformLocation(shaderID, uniform_name.c_str()), int(true));
            ++map_it;
            ++count;
        }
        
    }
    return;
}

void VAO_mesh::set_material_uniform(GLuint& shaderID)
{
    glUseProgram(shaderID);
    glUniform3f(glGetUniformLocation(shaderID, "material.ambient"), m_material_ptr->Ka.X, m_material_ptr->Ka.Y, m_material_ptr->Ka.Z);
    glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"), m_material_ptr->Kd.X, m_material_ptr->Kd.Y, m_material_ptr->Kd.Z);
    glUniform3f(glGetUniformLocation(shaderID, "material.specular"), m_material_ptr->Ks.X, m_material_ptr->Ks.Y, m_material_ptr->Ks.Z);
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"), m_material_ptr->Ns);
    
}





/*
VAO_cubemap::VAO_cubemap():
VAO()
{}

VAO_cubemap::VAO_cubemap(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string> &path_to_texture):
VAO()
{
    init(primitive_mode, numVertices, vertex_buffer_data, path_to_texture);
}

void VAO_cubemap::init(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, std::vector<std::string> &path_to_texture)
{
    m_primitivemode = primitive_mode;
    m_numvert   = numVertices;
    m_texpath = path_to_texture;
    
    glGenVertexArrays(1, &(m_vertexarrayID)); // VAO
    glGenBuffers (1, &(m_vertexbuffer)); // VBO - vertices

    glBindVertexArray (m_vertexarrayID); // Bind the VAO
    glBindBuffer (GL_ARRAY_BUFFER, m_vertexbuffer); // Bind the VBO vertices
    glBufferData (GL_ARRAY_BUFFER, 3*m_numvert*sizeof(GLfloat), vertex_buffer_data, GL_STATIC_DRAW); // Copy the vertices into VBO
    glVertexAttribPointer
    (0,
     3,
     GL_FLOAT,
     GL_FALSE,
     3 * sizeof(float),
     (void*)0);
    glBindVertexArray(0);
    load_texture();
    return;
}

void VAO_cubemap::load_texture()
{
    
    if (m_texpath.size() == 0) {
      return ;
    }
    glGenTextures(1, &(texture_buffer));
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_buffer);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // set the texture wrapping parameters
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

    for(int i = 0; i < m_texpath.size(); ++i)
      {
          unsigned char *data = stbi_load(m_texpath[i].c_str(), &width, &height, &nrChannels, 0);
          if (data)
          {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            std::cout << "Cubemap texture loaded at path: " << m_texpath[i] << std::endl;
              //std::cout << width << " " << height << std::endl;
            stbi_image_free(data);
          }
          else
          {
            std::cout << "Cubemap texture failed to load at path: " << m_texpath[i] << std::endl;
            stbi_image_free(data);
          }
      }
    
    //std::cout << "texture id" << textureID << std::endl;
    return;
}

void VAO_cubemap::draw(GLuint shaderID)
{
    // Enable Vertex Attribute 1 - Color
    glBindVertexArray (m_vertexarrayID);
    glEnableVertexAttribArray(0);
    //glActiveTexture(GL_TEXTURE0);
    
    // Bind the VBO to use
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_buffer);
    
    // Draw the geometry !
    glDrawArrays(m_primitivemode, 0, m_numvert); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBindVertexArray(0);
    return;
}
*/
