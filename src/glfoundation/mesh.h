#pragma once

#include "renderable.h"
#include "src/utilities/material.h"

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
 * A wrapper object of objl::Mesh
 */
class Mesh final : public Renderable
{
public:
    Mesh(objl::Mesh& mesh, unsigned int num_instance);
    ~Mesh();

    void render(const Shader& shader) override;
    void send_instance_matrices(std::vector<glm::mat4>& instance_models) override;

protected:

private:
    unsigned int m_numinstance;
    void init(objl::Mesh& mesh);
    void draw_textures(const Shader& shader);
    void set_material_uniform(const Shader& shader);

    Material* m_material_ptr = nullptr;
    std::map<std::string, std::shared_ptr<Texture>> map_ptrs;
/*map_Ka_ptr -->GL_TEXTURE0
map_Kd_ptr = nullptr; GL_TEXTURE1
map_Ks_ptr = nullptr; GL_TEXTURE2
map_Ns_ptr = nullptr;GL_TEXTURE3
map_d_ptr = nullptr; GL_TEXTURE4
map_bump_ptr = nullptr; GL_TEXTURE5*/
};

} // namespace Cluster

