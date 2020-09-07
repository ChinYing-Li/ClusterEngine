#include <iostream>

#include "glincludes.h"
#include "textureregistry.h"

TextureRegistry::TextureRegistry():
    m_texture_in_use(nullptr),
    m_textures(Texture2D::NUM_TEXTURE2D_TYPES, std::vector<std::shared_ptr<Texture2D>>(MAX_NUMBER_OF_SLOTS_PER_USAGE, nullptr))
{
}


TextureRegistry::
~TextureRegistry()
{
    // We don't have to delete the tectures as it still might be used
    // somewhere else.
}

/*
 *
 */
void TextureRegistry::
activate_texture(Texture2D::Texture2DUsage usage)
{

}

/*
 *
 */
void TextureRegistry::
register_texture(GLenum texture_target,
                 std::shared_ptr<Texture2D> texture,
                 Texture2D::Texture2DUsage usage)
{

}

/*
 *
 */
void TextureRegistry::
bind_texture(GLenum texture_target,
             Texture2D::Texture2DUsage usage)
{
    int index = (unsigned int)usage;
    if(m_textures[index] == nullptr)
    {
        std::cerr << "There's no texture registed for usage "
                  <<  index << std::endl;
    }

    glBindTexture(texture_target, m_textures[index]->get_ID());
}
