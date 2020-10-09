#include <iostream>

#include "glincludes.h"
#include "textureregistry.h"

namespace Cluster{
/*
 * OpenGL gurantees that there's at least 16 available texture unit.
 */
TextureRegistry::TextureRegistry()
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
             GLuint texture_ID)
{
    glBindTexture(texture_target, texture_ID);
    _textures[_texture_unit_in_use] = texture_ID;
}

std::shared_ptr<Texture2D> TextureRegistry::
create_empty_depth_map(GLuint width, GLuint height)
{
  std::shared_ptr<Texture2D> depth_map_ptr = std::make_shared<Texture2D>();
  depth_map_ptr->bind(0);
  depth_map_ptr->set_dimensions(width, height);
  depth_map_ptr->set_image_param( GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
  depth_map_ptr->set_wrap_st(GL_CLAMP, GL_CLAMP);
  // depth_map_ptr->release();
  return depth_map_ptr;
}

std::shared_ptr<TextureCubemap> TextureRegistry::
create_empty_cubemap(GLuint resolution)
{

}

std::shared_ptr<Texture2D> TextureRegistry::
create_shadow_map(GLuint width, GLuint height)
{

}
std::shared_ptr<TextureCubemap> TextureRegistry::
create_shadow_cubemap(GLuint resolution)
{

}
} // namespace Cluster
