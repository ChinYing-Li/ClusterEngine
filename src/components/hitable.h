#pragma once

#include "../../includes/gl_headers.h"
#include "../foundation/shape.h"

typedef float radian;

class Hitable
{
public:
    Hitable();
    Hitable(const float x, const float y, const float z);
    ~Hitable() = default;
    Shape collision_shape;
    glm::vec3 m_position;
    
    void virtual draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat) = 0;
    void set_position(const float x, const float y, const float z);
    void virtual update(float delta_t) = 0;
    void virtual update_shape() = 0;
    void virtual resolve_collision() = 0;
protected:
    
    void virtual set_up_collision_shape() = 0;
};
