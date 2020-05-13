#pragma once
#include <string>
#include "gltypes.h"
 

class Skybox
{
public:
    Skybox();
    Skybox(const std::string name);
    ~Skybox() = default;
    
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat);
private:
    VAO_texture vao;
    void create_vao();
};
