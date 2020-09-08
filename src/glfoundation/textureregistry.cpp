#include <iostream>

#include "glincludes.h"
#include "textureregistry.h"

/*
 * OpenGL gurantees that there's at least 16 available texture unit.
 */
TextureRegistry::TextureRegistry():
    m_texture_unit_in_use(0),
    m_textures(16, std::shared_ptr<Texture2D>(nullptr))
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
activate_texture(unsigned int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    m_texture_unit_in_use = texture_unit;
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
             std::shared_ptr<Texture> texture)
{
    glBindTexture(texture_target, texture->get_ID());
    m_textures[m_texture_unit_in_use] = texture;
}
