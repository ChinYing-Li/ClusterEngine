#include "textureregistry.h"

TextureRegistry::TextureRegistry():
    m_texture_in_use(nullptr),
    m_textures(Texture2D::NUM_TEXTURE2D_TYPES, nullptr)
{
}

TextureRegistry::
~TextureRegistry()
{
    // We don't have to delete the tectures as it still might be used
}
