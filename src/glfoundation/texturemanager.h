#pragma once

#include <experimental/filesystem>
#include <map>
#include <memory>

#include "texture.h"

namespace fs = std::experimental::filesystem;

namespace Cluster
{
    class TextureManager
    {
    public:
        TextureManager() = default;
        ~TextureManager() = default;

        static Texture2D load_texture2d_from_file(fs::path texture_path, Texture::Type type);
        static TextureCubemap load_cubemap_from_file(fs::path texture_path, Texture::Type type);

        static Texture2D generate_empty_depth_map(const GLuint width, const GLuint height);
        static TextureCubemap generate_empty_cubemap(const GLuint resolution);

        static Texture2D generate_shadow_map(const GLuint width, const GLuint height);
        static TextureCubemap generate_shadow_cubemap(const GLuint resolution);
        static Texture2D generate_hdr_texture(const unsigned int width, const unsigned int height);
        static Texture2D generate_ldr_texture(const unsigned int width, const unsigned int height);

    private:
        std::map<fs::path, Texture2D> m_loaded_texture;
    };
}
