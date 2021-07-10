#include "skybox.h"

Skybox::Skybox()
{}

void Skybox::create_vao()
{
    GLfloat skybox_vertbuf[] =
    { -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    m_vao = VAO_texture(GL_TRIANGLES, 6*6, skybox_vertbuf, "skybox", _data);
    return;
}

void Skybox::
draw(glm::mat4& VP, const Shader& shader, GLMatrices& mat)
{
    mat.model = glm::mat4(1.0);
    glm::mat4 view = glm::mat4(glm::mat3(mat.view));
    glm::mat4 sw(
    glm::vec4(1, 0, 0,0),
    glm::vec4(0, 0, -1,0),
    glm::vec4(0, 1, 0,0),
             glm::vec4(0)
             );
    glm::mat4 MVP = mat.projection * view * mat.model*sw; // ???
    glDepthFunc(GL_LEQUAL);
    shader.use();
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    shader.set_uniform1i("skybox", 0);
    m_cubemap.render(shader);
    
    glDepthFunc(GL_LESS);
    glBindVertexArray(0);
    return;
}
