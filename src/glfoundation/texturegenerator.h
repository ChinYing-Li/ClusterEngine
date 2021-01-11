#pragma once

#include<memory>

#include "texture.h"

namespace Cluster
{
  std::shared_ptr<Texture2D> generate_empty_depth_map(const GLuint width, const GLuint height);
  std::shared_ptr<TextureCubemap> generate_empty_cubemap(const GLuint resolution);

  std::shared_ptr<Texture2D> generate_shadow_map(const GLuint width, const GLuint height);
  std::shared_ptr<TextureCubemap> generate_shadow_cubemap(const GLuint resolution);

  enum TextureFormat
  {
    HDR,
    LDR,
    CUSTOM
  };

  std::shared_ptr<Texture2D> generate_hdr_texture(const unsigned int width, const unsigned int height);
  std::shared_ptr<Texture2D> generate_ldr_texture(const unsigned int width, const unsigned int height);
}
