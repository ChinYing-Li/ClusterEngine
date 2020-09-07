#pragma once

#include <map>
#include <memory>

#include "texture.h"

class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    void activate_texture(Texture2D::Texture2DUsage usage);

    void register_texture(GLenum texture_target, std::shared_ptr<Texture2D> texture, Texture2D::Texture2DUsage usage);
    void bind_texture(GLenum texture_target, Texture2D::Texture2DUsage usage);

    void get_texture_in_use();
    void get_texture(Texture2D::Texture2DUsage usage);

private:
    std::shared_ptr<Texture> m_texture_in_use;
    std::vector<std::vector<std::shared_ptr<Texture2D>>> m_textures;
    static unsigned int MAX_NUMBER_OF_SLOTS_PER_USAGE;
};
