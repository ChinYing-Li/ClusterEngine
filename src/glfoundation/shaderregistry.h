#pragma once

#include <map>
#include <memory>

#include "shader.h"

namespace Cluster
{
/*
 * A
 */
class ShaderRegistry
{
public:
    ShaderRegistry();
    ~ShaderRegistry();

    static void activate_texture(unsigned int texture_binding_point);
    void register_texture(GLenum texture_target, std::shared_ptr<Texture2D> texture, Texture2D::Texture2DUsage usage);
    static void bind_texture(GLenum texture_target, GLuint texture_ID);

    static const int max_texture_slot = 16;

    static void init()
    {
      _texture_unit_in_use = 0;
      _textures = std::vector<std::shared_ptr<Texture>>(ShaderRegistry::max_texture_slot, nullptr);
    }

private:
    static unsigned int _texture_unit_in_use;
    static std::vector<std::shared_ptr<Texture>> _textures;
};

} // namespace Cluster
