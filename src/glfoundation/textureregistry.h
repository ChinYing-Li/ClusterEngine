#pragma once

#include <map>
#include <memory>

#include "texture.h"

class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    static void activate_texture(std::shared_ptr<Texture>);
    static void register_texture(GLenum texture_target, std::shared_ptr<Texture>);
    static void bind_texture(GLenum texture_target, std::shared_ptr<Texture>);

private:
    std::shared_ptr<Texture> m_texture_in_use;
    std::vector<std::shared_ptr<Texture2D>> m_textures;
    static unsigned int MAX_NUMBER_OF_SLOTS;
};
