#pragma once
#include <string>

#include "renderable.h"
#include "texture.h"

class Skybox: Renderable
{
public:
    Skybox();
    ~Skybox() = default;
    void render(const Shader& shaderID) override;

    void set_mat(glm::mat4& VP, GLMatrices& mat)

private:
    TextureCubemap m_cubemap;
};
