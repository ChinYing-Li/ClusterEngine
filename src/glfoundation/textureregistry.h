#pragma once

#include <map>

#include "texture.h"

class TextureRegistry
{
public:
    TextureRegistry();
    ~TextureRegistry();

    static void activate_texture(GLuint texture_ID);
    //static
private:
    static unsigned int MAX_NUMBER_OF_SLOTS;
    std::vector<GLuint> m_textures;
};
