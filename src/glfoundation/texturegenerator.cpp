#include "texturegenerator.h"

namespace Cluster
{
std::shared_ptr<Texture2D> generate_empty_depth_map(const GLuint width, const GLuint height)
{
  std::shared_ptr<Texture2D> depth_map = std::make_shared<Texture2D>();
  depth_map->bind(0);
  depth_map->set_dimensions(width, height);
  depth_map->set_texture_param(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
  depth_map->set_wrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  // depth_map->release() ??
  return depth_map;
}

std::shared_ptr<TextureCubemap> generate_empty_cubemap(const GLuint resolution)
{
  return std::make_shared<TextureCubemap>();
}

std::shared_ptr<Texture2D> generate_shadow_map(const GLuint width, const GLuint height)
{
  std::shared_ptr<Texture2D> shadow_map = std::make_shared<Texture2D>();
  shadow_map->bind(0);
  shadow_map->set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadow_map->set_magmin_filter(GL_LINEAR, GL_LINEAR);

  std::vector<float> color(4, 1.0);
  glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, &color[0]);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

  shadow_map->set_dimensions(width, height);
  shadow_map->set_texture_param(GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  // TODO: release
  return shadow_map;
}

std::shared_ptr<TextureCubemap> generate_shadow_cubemap(const GLuint resolution)
{
  std::shared_ptr<TextureCubemap> shadow_map = std::make_shared<TextureCubemap>();
  shadow_map->bind(0);
  shadow_map->set_resolution(resolution);
  shadow_map->set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadow_map->set_magmin_filter(GL_LINEAR, GL_LINEAR);

  std::vector<float> color(4, 1.0);
  glTexParameterfv(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BORDER_COLOR, &color[0]);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

  for(int i = 0; i < 6; ++i)
  {
    shadow_map->set_face_texture_param(i, GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
  }

  // TODO: release
  return shadow_map;
}

std::shared_ptr<Texture2D> generate_hdr_texture(const unsigned int width, const unsigned int height)
{
  std::shared_ptr<Texture2D> hdr_texture = std::make_shared<Texture2D>();
  hdr_texture->set_dimensions(width, height);

  hdr_texture->bind(0);
  hdr_texture->set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  hdr_texture->set_magmin_filter(GL_LINEAR, GL_LINEAR);
  hdr_texture->set_texture_param(GL_RGBA16F, GL_RGBA, GL_FLOAT, nullptr);
  // release
  return hdr_texture;
}

std::shared_ptr<Texture2D> generate_ldr_texture(const unsigned int width, const unsigned int height)
{
  std::shared_ptr<Texture2D> ldr_texture = std::make_shared<Texture2D>();
  ldr_texture->set_dimensions(width, height);

  ldr_texture->bind(0);
  ldr_texture->set_wrapping(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  ldr_texture->set_magmin_filter(GL_NEAREST, GL_NEAREST);
  ldr_texture->set_texture_param(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  // release
  return ldr_texture;
}
}
