#pragma once

#include "../../includes/gl_headers.h"
#include "gltypes.h"

class Track {
public:
    Track() {};
    Track(const float x, const float y, const float z, const float squarelength, const float squarewidth, const float trackwidth);
    void draw(glm::mat4& VP, GLuint& shaderID1, GLuint& shaderID2, GLMatrices& mat1, GLMatrices& mat2);
    void set_position(const float x, const float y, const float z);
    void step();
    
    glm::vec3 m_center;
    float m_squarelength;
    float m_squarewidth;
    float m_trackwidth;
    color_t m_color;
private:
    void create_straight_parts();
    void create_turning_parts();
    VAO_texture straight_part1;
    VAO_texture straight_part2;
    VAO_monotone turning_yplus;
    VAO_monotone turning_yminus;
};
