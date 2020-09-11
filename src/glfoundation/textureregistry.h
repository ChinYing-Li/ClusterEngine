#pragma once

#include <map>
#include <memory>

#include "texture.h"

class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    static void activate_texture(unsigned int texture_binding_point);
    void register_texture(GLenum texture_target, std::shared_ptr<Texture2D> texture, Texture2D::Texture2DUsage usage);
    static void bind_texture(GLenum texture_target, GLuint texture_ID);

    void get_texture_in_use();
    void get_texture(Texture2D::Texture2DUsage usage);

    static Texture2D create_empty_depth_map(GLuint width, GLuint height);
    static TextureCubemap create_empty_cubemap(GLuint resolution);
    static Texture2D create_shadow_map(GLuint width, GLuint height);
    static TextureCubemap create_shadow_cubemap(GLuint resolution);

private:
    unsigned int m_texture_unit_in_use;
    std::vector<std::shared_ptr<Texture>> m_textures;
    //static unsigned int MAX_NUMBER_OF_SLOTS_PER_USAGE;
};
