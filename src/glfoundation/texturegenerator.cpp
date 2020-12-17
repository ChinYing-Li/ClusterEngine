#include "texturegenerator.h"

namespace Cluster
{
std::shared_ptr<Texture2D> generate_empty_depth_map(const GLuint width, const GLuint height)
{
  std::shared_ptr<Texture2D> depth_map = std::make_shared<Texture2D>();
  depth_map->bind(0);
  depth_map->set_dimensions(width, height);
  depth_map->set_image_param(GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
  depth_map->set_wrap_st(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
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
  shadow_map->set_wrap_st(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadow_map->
}

std::shared_ptr<TextureCubemap> generate_shadow_cubemap(const GLuint resolution)
{
  std::shared_ptr<TextureCubemap> shadow_map = std::make_shared<TextureCubemap>();
  shadow_map->bind(0);
  shadow_map->set_wrap_st;
}
}
