#pragma once

#include <filesystem>
#include <string.h>
#include <memory>

#include "src/ext/objloader.h"

namespace fs = std::filesystem;

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
    explicit Material(objl::Material& objl_material);
    ~Material() = default;

    void set_uniform(const Shader& shader);

    static const unsigned int N_MapType;
    enum TextureMapType
    {
      K_AMBIENT,
      K_DIFFUSE,
      K_SPECULAR,
      N_SPECULAR,
      ALPHA,
      BUMP,
    };

protected:
    objl::Material m_objl_material;
    std::string m_name;

    std::vector<int> m_use_texture_map;
    std::vector<std::shared_ptr<Texture2D>> m_map_ptr;
};

}
