#pragma once

#include <experimental/filesystem>

#include "renderable.h"
#include "material.h"

namespace fs = std::experimental::filesystem;

// Forward declarations
namespace objl
{
class Loader;
struct Material;
struct Mesh;
}

namespace Cluster
{
class Shader;

/*
 * A wrapper object of objl::Mesh.
 */
class Mesh final : public Renderable
{
public:
    Mesh(objl::Mesh& mesh, fs::path obj_root_dir);
    ~Mesh();

    void render(const Shader& shader) override;

    using Renderable::set_num_instances;
    void send_instance_matrices(std::vector<glm::mat4>& instance_models) override;

protected:

private:
    void init(objl::Mesh& mesh);
    void draw_textures(const Shader& shader);
    void set_material_uniform(const Shader& shader);

    Material* m_material_ptr = nullptr;
};

} // namespace Cluster

