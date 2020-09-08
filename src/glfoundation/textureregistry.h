#pragma once

#include <map>
#include <memory>

#include "texture.h"

class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    void activate_texture(unsigned int texture_unit);
    void register_texture(GLenum texture_target, std::shared_ptr<Texture2D> texture, Texture2D::Texture2DUsage usage);
    void bind_texture(GLenum texture_target, std::shared_ptr<Texture> texture);

    void get_texture_in_use();
    void get_texture(Texture2D::Texture2DUsage usage);

private:
    unsigned int m_texture_unit_in_use;
    std::vector<std::shared_ptr<Texture>> m_textures;
    //static unsigned int MAX_NUMBER_OF_SLOTS_PER_USAGE;
};
