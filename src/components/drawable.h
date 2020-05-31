#pragma once
#include <vector>
#include <memory>
#include "includes/gl_headers.h"
#include "src/gltypes.h"

// Anything that can be seen by Camera
// Inherited by Hitable and other "components" that is unhitable

class Drawable
{
public:
    Drawable();
    Drawable(const float x, const float y, const float z);
    ~Drawable() = default;
    void set_position(const float x, const float y, const float z);
    void virtual draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat){};
    void virtual update(float delta_t) = 0;
    glm::vec3 m_position;
protected:
    
    std::vector<std::shared_ptr<VAO>> VAO_handles;
};
