#include "stb_image.h"
#include "texturemanager.h"

namespace Cluster
{
    Texture2D TextureManager::
    load_texture2d_from_file(fs::path texture_path, Texture::Type type)
    {
      Texture2D tex(texture_path, type);
      return tex;
    }

Texture2D TextureManager::
generate_empty_depth_map(const GLuint width, const GLuint height)
{
  Texture2D depth_map;
  depth_map.bind(0);
  depth_map.set_dimensions(width, height);
  depth_map.set_texture_param(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
  depth_map.set_wrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  // depth_map->release() ??
  return depth_map;
}

TextureCubemap TextureManager::
generate_empty_cubemap(const GLuint resolution)
{
  // TODO: resolution?
  return TextureCubemap();
}

Texture2D TextureManager::
generate_shadow_map(const GLuint width, const GLuint height)
{
  Texture2D shadow_map();
  shadow_map.bind(0);
  shadow_map.set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadow_map.set_magmin_filter(GL_LINEAR, GL_LINEAR);

  std::vector<float> color(4, 1.0);
  glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, &color[0]);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

  shadow_map.set_dimensions(width, height);
  shadow_map.set_texture_param(GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  // TODO: release
  return shadow_map;
}

TextureCubemap TextureManager::
generate_shadow_cubemap(const GLuint resolution)
{
  TextureCubemap> shadow_map();
  shadow_map.bind(0);
  shadow_map.set_resolution(resolution);
  shadow_map.set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadow_map.set_magmin_filter(GL_LINEAR, GL_LINEAR);

  std::vector<float> color(4, 1.0);
  glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, &color[0]);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

  for(int i = 0; i < 6; ++i)
  {
    shadow_map.set_face_texture_param(i, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  }

  // TODO: release
  return shadow_map;
}

Texture2D TextureManager::
generate_hdr_texture(const unsigned int width, const unsigned int height)
{
  Texture2D hdr_texture();
  hdr_texture.set_dimensions(width, height);

  hdr_texture.bind(0);
  hdr_texture.set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  hdr_texture.set_magmin_filter(GL_LINEAR, GL_LINEAR);
  hdr_texture.set_texture_param(GL_RGBA16F, GL_RGBA, GL_FLOAT, nullptr);
  // release
  return hdr_texture;
}

Texture2D TextureManager::
generate_ldr_texture(const unsigned int width, const unsigned int height)
{
  Texture2D ldr_texture();
  ldr_texture.set_dimensions(width, height);

  ldr_texture.bind(0);
  ldr_texture.set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  ldr_texture.set_magmin_filter(GL_NEAREST, GL_NEAREST);
  ldr_texture.set_texture_param(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  // release
  return ldr_texture;
}
}
