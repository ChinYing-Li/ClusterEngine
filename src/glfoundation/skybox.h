#pragma once
#include <string>

#include "renderable.h"

class Skybox
{
public:
    Skybox();
    ~Skybox() = default;
    
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat);
private:
    VAO_texture vao;
    void create_vao();
};
