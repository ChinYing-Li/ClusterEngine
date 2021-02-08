#pragma once

#include "renderable.h"

// Forward declarations
namespace objl
{
class Loader;
class Material;
class Mesh;
}

namespace Cluster
{
class Shader;
/*
 *
 */
class Mesh final : public Renderable
{
public:
    Mesh(objl::Mesh& mesh, unsigned int num_instance);
    ~Mesh() = default;

    void render(Shader& shader) override;
    void send_instance_matrices(std::vector<glm::mat4>& instance_models) override;

protected:

private:
    unsigned int m_numinstance;
    void init(objl::Mesh& mesh);
    void draw_textures(Shader& shader);
    void set_material_uniform(Shader& shader);

    objl::Material* m_material_ptr = nullptr;
    std::map<std::string, std::shared_ptr<Texture>> map_ptrs;
/*map_Ka_ptr -->GL_TEXTURE0
map_Kd_ptr = nullptr; GL_TEXTURE1
map_Ks_ptr = nullptr; GL_TEXTURE2
map_Ns_ptr = nullptr;GL_TEXTURE3
map_d_ptr = nullptr; GL_TEXTURE4
map_bump_ptr = nullptr; GL_TEXTURE5*/
};

} // namespace Cluster

