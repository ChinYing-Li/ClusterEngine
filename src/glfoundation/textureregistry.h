#pragma once

#include <map>
#include <memory>

#include "texture.h"

namespace Cluster
{
/*
 * A
 */
class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    static void activate_texture(unsigned int texture_binding_point);
    void register_texture(GLenum texture_target, std::shared_ptr<Texture2D> texture, Texture2D::Texture2DUsage usage);
    static void bind_texture(GLenum texture_target, GLuint texture_ID);

    void get_texture_in_use();
    void get_texture(Texture2D::Texture2DUsage usage);

    static std::shared_ptr<Texture2D> create_empty_depth_map(GLuint width, GLuint height);
    static std::shared_ptr<TextureCubemap> create_empty_cubemap(GLuint resolution);
    static std::shared_ptr<Texture2D> create_shadow_map(GLuint width, GLuint height);
    static std::shared_ptr<TextureCubemap> create_shadow_cubemap(GLuint resolution);

    static const int max_texture_slot = 16;

    static void init()
    {
      _texture_unit_in_use = 0;
      _textures = std::vector<std::shared_ptr<Texture>>(TextureRegistry::max_texture_slot, nullptr);
    }

private:
    static unsigned int _texture_unit_in_use;
    static std::vector<std::shared_ptr<Texture>> _textures;
};

} // namespace Cluster
