#pragma once

#include <vector>
#include <filesystem>

#include "glincludes.h"
#include "renderable.h"
#include "src/glfoundation/mesh.h"
#include "texture.h"

namespace fs = std::filesystem;

namespace objl
{
    class Loader;
    class Material;
    class Mesh;
}

namespace Cluster
{
class Shader;

class Obj : public Renderable
{
public:
    Obj() = delete;
    Obj(fs::path obj_path, unsigned int num_instance = 1);
    ~Obj() = default;

    void virtual render(Shader& shader) override;
    void set_instance_mat(std::vector<glm::mat4>& instance_mat);

protected:
    unsigned int m_instance = 1;
    std::vector<Mesh> m_meshes;
};
} // namespace Cluster
