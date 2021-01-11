#include <iostream>

#include "glincludes.h"
#include "shaderregistry.h"

namespace Cluster{
/*
 * OpenGL gurantees that there's at least 16 available texture unit.
 */
ShaderRegistry::ShaderRegistry()
{
}


ShaderRegistry::
~ShaderRegistry()
{
    // We don't have to delete the tectures as it still might be used
    // somewhere else.
}

/*
 *
 */
void ShaderRegistry::
activate_texture(unsigned int texture_unit)
{
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    m_texture_unit_in_use = texture_unit;
}

/*
 *
 */
void ShaderRegistry::
register_texture(GLenum texture_target,
                 std::shared_ptr<Texture2D> texture,
                 Texture2D::Texture2DUsage usage)
{

}

/*
 *
 */
void ShaderRegistry::
bind_texture(GLenum texture_target,
             GLuint texture_ID)
{
    glBindTexture(texture_target, texture_ID);
    _textures[_texture_unit_in_use] = texture_ID;
}

} // namespace Cluster
