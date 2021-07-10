#pragma once

#include <map>
#include <memory>

#include "shader.h"
#include "texture.h"

namespace Cluster
{
/*
 * A
 */
class ShaderRegistry
{
public:
    ShaderRegistry();
    ~ShaderRegistry();

    static void activate_texture(unsigned int texture_binding_point);
    static void bind_texture(GLenum texture_target, GLuint texture_ID);
    static const int MAX_TEXTURE_SLOT = 16;
};

} // namespace Cluster
