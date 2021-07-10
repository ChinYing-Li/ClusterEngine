#pragma once

#include <experimental/filesystem>
#include <string.h>
#include <memory>

#include "objloader.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
class Texture2D;
class Shader;

/*
 * A wrapper class of objl::Material
 */
class Material
{
public:
    Material() = delete;
    explicit Material(objl::Material& objl_material, fs::path obj_root_dir);
    ~Material() = default;

    enum TextureMapType
    {
      K_AMBIENT,
      K_DIFFUSE,
      K_SPECULAR,
      N_SPECULAR,
      ALPHA,
      BUMP,
    };

    void bind(const Shader& shader);
    bool is_texture_in_use(TextureMapType type) const;
    void set_uniform(const Shader& shader) const;

    static const unsigned int N_MapType;

protected:
    objl::Material m_objl_material;
    std::string m_name;

    std::vector<Texture2D> m_textures;
};

}
