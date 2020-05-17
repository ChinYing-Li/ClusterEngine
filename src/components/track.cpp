#include <math.h>
#include <iostream>

#include "track.h"

const color_t BLACK = {0,0,0 };
const color_t PINK = {  255, 0, 255};
#define TURNING_BLOCK_NUM 180

Track::Track(const float x, const float y, const float z,\
             const float squarelength, const float squarewidth, const float trackwidth):
m_center(glm::vec3(x, y, z)),
m_squarelength(squarelength),
m_squarewidth(squarewidth),
m_trackwidth(trackwidth)
{
    m_color = {50, 0, 255};
    create_straight_parts();
    create_turning_parts();
}

void Track::create_straight_parts()
{
    // a rectangle
    float tex_scale = 20.0f;
    GLfloat straightpart1_vertbuf_data[] =
    {
        m_center.x - m_squarewidth/2, m_center.y - m_squarelength/2, m_center.z, m_center.x - m_squarewidth/2*tex_scale, m_center.y - m_squarelength/2*tex_scale,
    
        m_center.x - m_squarewidth/2, m_center.y + m_squarelength/2, m_center.z, (m_center.x - m_squarewidth/2)*tex_scale, (m_center.y + m_squarelength/2)*tex_scale,
    
        m_center.x - m_squarewidth/2 - m_trackwidth, m_center.y + m_squarelength/2, m_center.z, (m_center.x - m_squarewidth/2 - m_trackwidth)*tex_scale, (m_center.y + m_squarelength/2)*tex_scale,
        
        m_center.x - m_squarewidth/2 - m_trackwidth, m_center.y + m_squarelength/2, m_center.z, (m_center.x - m_squarewidth/2 - m_trackwidth)*tex_scale, (m_center.y + m_squarelength/2)*tex_scale,
        m_center.x - m_squarewidth/2 - m_trackwidth, m_center.y - m_squarelength/2, m_center.z, (m_center.x - m_squarewidth/2 - m_trackwidth)*tex_scale, (m_center.y - m_squarelength/2)*tex_scale,
        m_center.x - m_squarewidth/2, m_center.y - m_squarelength/2, m_center.z, (m_center.x - m_squarewidth/2)*tex_scale, (m_center.y - m_squarelength/2)*tex_scale
    };
    
    // a rectangle
    GLfloat straightpart2_vertbuf_data[] =
    {
        m_center.x + m_squarewidth/2, m_center.y - m_squarelength/2, m_center.z,
        m_center.x + m_squarewidth/2, m_center.y + m_squarelength/2, m_center.z,
        m_center.x + m_squarewidth/2 + m_trackwidth, m_center.y + m_squarelength/2, m_center.z,
        
        m_center.x + m_squarewidth/2 + m_trackwidth, m_center.y + m_squarelength/2, m_center.z,
        m_center.x + m_squarewidth/2 + m_trackwidth, m_center.y - m_squarelength/2, m_center.z,
        m_center.x + m_squarewidth/2, m_center.y - m_squarelength/2, m_center.z
    };
    
    straight_part1 = VAO_texture(GL_TRIANGLES, 6, straightpart1_vertbuf_data, "brick", _data);
    straight_part2 = VAO_monotone(GL_TRIANGLES, 6, straightpart2_vertbuf_data, m_color, GL_FILL);
    return;
}
void Track::create_turning_parts()
{
    const float inner_radius = m_squarewidth/2;
    const float outer_radius = inner_radius + m_trackwidth;
    
    GLfloat turningyplus_vertbuf_data[3*TURNING_BLOCK_NUM*6];
    glm::vec3 turningyplus_center = m_center + glm::vec3(0, m_squarelength/2, 0);
    std::cout << turningyplus_center.x << " " << turningyplus_center.y << std::endl;
    
    float turning_block_inv = 1.0f / TURNING_BLOCK_NUM;
    
    for(int i = 0; i < TURNING_BLOCK_NUM; ++i)
    {
        float scalar = float(i)*turning_block_inv;
        float scalar_plus1 = float(i+1)*turning_block_inv;
        glm::vec3 outer1 = turningyplus_center + outer_radius*glm::vec3(cos(M_PI*scalar), sin(M_PI*scalar), 0);
        glm::vec3 outer2 = turningyplus_center + outer_radius*glm::vec3(cos(M_PI*scalar_plus1), sin(M_PI*scalar_plus1), 0);
        glm::vec3 inner1 = turningyplus_center + inner_radius*glm::vec3(cos(M_PI*scalar), sin(M_PI*scalar), 0);
        glm::vec3 inner2 = turningyplus_center + inner_radius*glm::vec3(cos(M_PI*scalar_plus1), sin(M_PI*scalar_plus1), 0);
        //std::cout << outer2.x << " " << outer2.y << std::endl;
        int start_idx = 18*i;
        turningyplus_vertbuf_data[start_idx] = outer1.x;
        turningyplus_vertbuf_data[start_idx+1] = outer1.y;
        turningyplus_vertbuf_data[start_idx+2] = outer1.z;
        
        turningyplus_vertbuf_data[start_idx+3] = inner1.x;
        turningyplus_vertbuf_data[start_idx+4] = inner1.y;
        turningyplus_vertbuf_data[start_idx+5] = inner1.z;
        
        turningyplus_vertbuf_data[start_idx+6] = inner2.x;
        turningyplus_vertbuf_data[start_idx+7] = inner2.y;
        turningyplus_vertbuf_data[start_idx+8] = inner2.z;
        
        //second triangle
        turningyplus_vertbuf_data[start_idx+9] = outer1.x;
        turningyplus_vertbuf_data[start_idx+10] = outer1.y;
        turningyplus_vertbuf_data[start_idx+11] = outer1.z;
        
        turningyplus_vertbuf_data[start_idx+12] = inner2.x;
        turningyplus_vertbuf_data[start_idx+13] = inner2.y;
        turningyplus_vertbuf_data[start_idx+14] = inner2.z;
        
        turningyplus_vertbuf_data[start_idx+15] = outer2.x;
        turningyplus_vertbuf_data[start_idx+16] = outer2.y;
        turningyplus_vertbuf_data[start_idx+17] = outer2.z;
    }
    
    GLfloat turningyminus_vertbuf_data[3*TURNING_BLOCK_NUM*6];
    glm::vec3 turningyminus_center(m_center.x, m_center.y - m_squarelength/2, m_center.z);
    for(int i = 0; i < TURNING_BLOCK_NUM; ++i)
    {
        float scalar = float(i)*turning_block_inv;
        float scalar_plus1 = float(i+1)*turning_block_inv;
        glm::vec3 outer1 = turningyminus_center + outer_radius*glm::vec3(cos(-M_PI*scalar), sin(-M_PI*scalar), 0);
        glm::vec3 outer2 = turningyminus_center + outer_radius*glm::vec3(cos(-M_PI*scalar_plus1), sin(-M_PI*scalar_plus1), 0);
        glm::vec3 inner1 = turningyminus_center + inner_radius*glm::vec3(cos(-M_PI*scalar), sin(-M_PI*scalar), 0);
        glm::vec3 inner2 = turningyminus_center + inner_radius*glm::vec3(cos(-M_PI*scalar_plus1), sin(-M_PI*scalar_plus1), 0);
        
        int start_idx = 18*i;
        turningyminus_vertbuf_data[start_idx] = outer1.x;
        turningyminus_vertbuf_data[start_idx+1] = outer1.y;
        turningyminus_vertbuf_data[start_idx+2] = outer1.z;
        
        turningyminus_vertbuf_data[start_idx+3] = inner1.x;
        turningyminus_vertbuf_data[start_idx+4] = inner1.y;
        turningyminus_vertbuf_data[start_idx+5] = inner1.z;
        
        turningyminus_vertbuf_data[start_idx+6] = inner2.x;
        turningyminus_vertbuf_data[start_idx+7] = inner2.y;
        turningyminus_vertbuf_data[start_idx+8] = inner2.z;
        
        //second triangle
        turningyminus_vertbuf_data[start_idx+9] = outer1.x;
        turningyminus_vertbuf_data[start_idx+10] = outer1.y;
        turningyminus_vertbuf_data[start_idx+11] = outer1.z;
        
        turningyminus_vertbuf_data[start_idx+12] = inner2.x;
        turningyminus_vertbuf_data[start_idx+13] = inner2.y;
        turningyminus_vertbuf_data[start_idx+14] = inner2.z;
        
        turningyminus_vertbuf_data[start_idx+15] = outer2.x;
        turningyminus_vertbuf_data[start_idx+16] = outer2.y;
        turningyminus_vertbuf_data[start_idx+17] = outer2.z;
    }
    
    turning_yplus = VAO_monotone(GL_TRIANGLES, 6*TURNING_BLOCK_NUM, turningyplus_vertbuf_data,m_color, GL_FILL); // try the GL_TRIANGLE_STRIP version
    turning_yminus = VAO_monotone(GL_TRIANGLES, 6*TURNING_BLOCK_NUM, turningyminus_vertbuf_data,m_color, GL_FILL);
    return;
}

void Track::set_position(const float x, const float y, const float z)
{
    m_center = glm::vec3(x, y, z);
}

void Track::draw(glm::mat4& VP, GLuint& shaderID1, GLuint& shaderID2, GLMatrices& mat1, GLMatrices& mat2)
{
    mat1.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (m_center);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0,1 ));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    glUseProgram(shaderID1);
    mat1.model *= (translate * rotate);
    glm::mat4 MVP = VP * mat1.model; // ???
    glUniformMatrix4fv(mat1.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    straight_part2.draw(shaderID1);
    turning_yplus.draw(shaderID1);
    turning_yminus.draw(shaderID1);
    
    glUseProgram(shaderID2);
    glUniformMatrix4fv(mat2.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform1i(glGetUniformLocation(shaderID2, "texture1"), 0);
    straight_part1.draw(shaderID2);
    
    return;
}
