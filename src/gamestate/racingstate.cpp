#include "src/gamestate/racingstate.h"
#include "src/foundation/shader.h"
#include "src/gamedata.h"
RacingState::RacingState(std::shared_ptr<GameData> data_ptr):
State(data_ptr),
cam(0.5f, 0.5f, 0.01f),
coin(0.0, 0.0, 0.0, 0.5, 0.4),
m_mat(),
width(800),
height(600)
{
    init();
    m_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    model_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("model");
    monotone_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("monotone");
}

RacingState::~RacingState()
{}

//
void RacingState::init()
{
    cyborg = objobject("cyborg.obj", m_data_ptr);
    cyborg.m_scale = glm::vec3(0.3f);
    cyborg.m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f);
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
}

void RacingState::update()
{
    return;
}

void RacingState::render()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //*cos(obstacle.rotation*M_PI/180)
    cam.update_matrices(m_mat);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << m_mat.view[i][j] << " ";
        }
        std::cout << "\n\n" << std::endl;
    }
    glm::mat4 VP = m_mat.projection*m_mat.view;
    cyborg.draw(model_shader_ptr->ID, m_mat.view, m_mat.projection);
    coin.draw(VP, monotone_shader_ptr->ID, m_mat);
    std::cout << "racing state drawing" << std::endl;
    return;
}

void RacingState::handle_input(GLFWwindow *window)
{
    int camforward = glfwGetKey(window, GLFW_KEY_2);
    int camright = glfwGetKey(window,GLFW_KEY_3);
    int camleft = glfwGetKey(window,GLFW_KEY_1);
    
    std::cout << "handling input" << std::endl;
    if(camforward)
    {
        cam.update_cam(move_forward);
        std::cout << "forward" << std::endl;
    }
    if(camleft)
    {
        cam.update_cam(turn_ccw);
        std::cout << "left" << std::endl;
    }
    if(camright)
    {
        cam.update_cam(turn_cw);
        std::cout << "right" << std::endl;
    }
    return;
}

void RacingState::pause()
{
    return;
}

void RacingState::resume()
{
    return;
}
