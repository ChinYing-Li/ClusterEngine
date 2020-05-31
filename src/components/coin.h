#pragma once

#include "hitable.h"
#include "gltypes.h"

class Coin: public Hitable
{
public:
    Coin();
    Coin(const float x, const float y, const float z, const float radius, const float thickness);
    ~Coin() = default;
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat) override;
    void update(float delta_t) override;
    void update_convexhull() override;
    void resolve_collision() override;
    
protected:
    void set_up_collision_shape() override;
private:
    float m_radius;
    float m_thickness;
    float m_orientation;
    color_t m_color = {255, 255, 0};
    
    void create_head_tail();
    void create_side();
    VAO_monotone m_head;
    VAO_monotone m_tail;
    VAO_monotone m_side;
  
};
