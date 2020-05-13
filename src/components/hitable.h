#pragma once

#include "../../includes/gl_headers.h"

typedef float radian;

class Hitable
{
public:
    Hitable();
    Hitable(const float x, const float y, const float z);
    ~Hitable() = default;
    glm::vec3 m_position;
    radian m_orientation;
    
    void virtual draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat) = 0;
    void set_position(const float x, const float y, const float z);
    void virtual update() = 0;
private:
};
