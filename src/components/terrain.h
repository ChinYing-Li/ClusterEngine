#pragma once

#include <vector>

#include "../../includes/gl_headers.h"
#include "gltypes.h"
#include "math.h"

class Terrain
{
public:
    Terrain();
    Terrain(const float altitute, const float steepness, const float central_rad);
    ~Terrain() = default;
    void draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat);
private:
    float m_altitute;
    float m_extensionstep = 0.5f;
    float m_steepness;
    float m_central_rad;
    int m_nextension = 8;
    float twopi = M_PI*2;
    
    color_t m_color = {0, 255, 0};
    glm::vec3 m_center;
    
    void create_central();
    void create_surroundings();
    void create_test();
    
    VAO_monotone m_central;
    std::vector<VAO_monotone> m_surroundings;
    VAO_monotone m_test;
    VAO_monotone m_position;
};


