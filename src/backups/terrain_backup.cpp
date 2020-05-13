/*
class Terrain
{
public:
    Terrain();
    Terrain(const int altitute, const int steepness, const int central_rad);
    ~Terrain();
private:
    float altitute;
    float steepness;
    VAO_monotone m_central;
    std::vector<VAO_monotone> m_sorroundings;
}*/

#include <random>
#include <iostream>
#include "terrain.h"

#define N_SIDES 20

Terrain::Terrain()
{}

Terrain::Terrain(const float altitute, const float steepness, const float central_rad):
m_altitute(altitute),
m_steepness(steepness),
m_central_rad(central_rad),
m_center(0.0f, 0.0f, altitute),
m_surroundings(m_nextension, VAO_monotone())
{
    create_central();
    create_surroundings();
    create_test();
    
}

void Terrain::create_central()
{
    GLfloat central_vertbuf_data[3*(N_SIDES+2)];
    central_vertbuf_data[0] = m_center.x;
    central_vertbuf_data[1] = m_center.y;
    central_vertbuf_data[2] = m_center.z;
    
    for(int i = 1; i < N_SIDES+1; ++i)
    {
        central_vertbuf_data[3*i] = m_center.x + m_central_rad*cos(twopi*float(i-1)/N_SIDES);
        central_vertbuf_data[3*i+1] = m_center.y + m_central_rad*sin(twopi*float(i-1)/N_SIDES);
        central_vertbuf_data[3*i+2] = m_center.z;
    }
    central_vertbuf_data[3*(N_SIDES+1)] = m_center.x + m_central_rad*cos(0);
    central_vertbuf_data[3*(N_SIDES+1)+1] = m_center.x + m_central_rad*sin(0);
    central_vertbuf_data[3*(N_SIDES+1)+2] = m_center.z;
    m_central = VAO_monotone(GL_TRIANGLE_FAN, N_SIDES+2, central_vertbuf_data, m_color, GL_FILL);
    return;
}

void Terrain::create_surroundings()
{
    std::random_device r;
    
    // Choose a random mean between 1 and 6
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(-5, 5);
    int mean = uniform_dist(e1);
    // Generate a normal distribution around that mean
    std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937 e2(seed2);
    std::normal_distribution<> normal_dist(mean, 3);

    GLfloat vertbuf_data[3*2*(N_SIDES+1)];
  
    for(int i = 0; i < m_nextension+1; ++i)
    {
        float radius = m_central_rad + m_extensionstep * i;
        float height = m_extensionstep*m_steepness * i;
        int flag = i%2;
        for(int v = 0; v < N_SIDES; ++v)
        {
            int idx = 3*(2*v+flag);
            vertbuf_data[idx] = m_center.x+radius * cos(twopi*float(v)/N_SIDES);
            vertbuf_data[idx+1] = m_center.y+radius * sin(twopi*float(v)/N_SIDES);
            vertbuf_data[idx+2] = m_center.z+height;
            if(i!=0)
            {
                vertbuf_data[idx] += normal_dist(e2)/50.0f;
                vertbuf_data[idx] += normal_dist(e2)/50.0f;
                vertbuf_data[idx] += normal_dist(e2)/50.0f;
            }
        }
        vertbuf_data[3*(2*N_SIDES+flag)] = vertbuf_data[3*flag];
        vertbuf_data[3*(2*N_SIDES+flag)+1] = vertbuf_data[3*flag+1];
        vertbuf_data[3*(2*N_SIDES+flag)+2] = vertbuf_data[3*flag+2];
        
        if(i>0)
        {
            color_t col = {30*i, 30*i, 0};
            m_surroundings[i-1] = VAO_monotone(GL_TRIANGLE_STRIP, 2*(N_SIDES+1), vertbuf_data, col, GL_FILL);
        }
    }
    /*color_t col = {128, 0, 0};
    glPointSize(5.5f);
    
    m_position = VAO_monotone(GL_POINTS, sizeof(vertbuf_data)/(3*sizeof(float)), vertbuf_data, col, GL_POINT);*/
    return;
}

void Terrain::create_test()
{
    GLfloat vertbuf_data[] =
    {
        0.3f, 0.3f, 0.0f,
        0.3f, 0.4f, 0.0f,
        0.4f, 0.3f, 0.0f,
        0.4f, 0.4f, 0.0f,
        0.8f, 0.3f, 0.0f,
        0.8f, 0.4f, 0.0f,
    };
    
    GLuint indices[] =
    {
        0, 1, 2,3
    };
    color_t c = {255, 0, 0};
    m_test = VAO_monotone(GL_TRIANGLE_STRIP, 6, vertbuf_data, 4, indices, c, GL_FILL);
    return;
}

void Terrain::draw(glm::mat4& VP, GLuint& shaderID, GLMatrices& mat)
{
    mat.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (m_center);    // glTranslatef
    
    glUseProgram(shaderID);
    mat.model *= translate;
    glm::mat4 MVP = VP * mat.model; // ???
    glUniformMatrix4fv(mat.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    m_central.draw(shaderID);
    for(auto it = m_surroundings.begin(); it != m_surroundings.end(); ++it)
    {
        it->draw(shaderID);
    }
    m_test.draw(shaderID);
    //m_position.draw(shaderID);
    return;
}

