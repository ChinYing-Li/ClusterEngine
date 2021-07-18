#pragma once
#include <experimental/filesystem>
#include <string>

#include "glfoundation/cubemap.h"
#include "glfoundation/texture.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
    class Skybox: Cubemap
    {
    public:
        Skybox();
        Skybox();
        ~Skybox() = default;
        void bind(const GLuint binding_point);
        void render(const Shader& shaderID) override;
    private:
        TextureCubemap m_cubemap;
    };
} // namespace Cluster
