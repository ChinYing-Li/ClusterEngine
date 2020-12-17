#pragma once
#include <vector>
#include <memory>
#include "includes/gl_headers.h"
#include "src/gltypes.h"
#include "src/foundation/objobject.h"

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
    void virtual draw(GLuint& shaderID, glm::mat4& view, glm::mat4& project){};
    void virtual update(float delta_t) = 0;
    void virtual set_instanced_models() = 0;
    
    glm::vec3 m_position;
protected:
    bool is_instanced = false;
    std::vector<glm::vec3> m_offsets; // use only if is_instanced = true
    std::vector<std::shared_ptr<objobject>> m_obj;
    std::vector<std::shared_ptr<VAO>> VAO_handles;
};
