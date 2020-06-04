#include "src/gamestate/racingstate.h"
#include "src/foundation/shader.h"
#include "src/gamedata.h"
#include "src/debug/debug.h"
RacingState::RacingState(std::shared_ptr<GameData> data_ptr):
State(data_ptr),
cam(0.5f, 0.5f, 0.01f),
m_mat(),
width(800),
height(600),
dirlight()
{
    init();
    m_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    model_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("model");
    monotone_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("monotone");
    lighting_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("lighting");
}

RacingState::~RacingState()
{}

//
void RacingState::init()
{
    cyborg = objobject("cyborg.obj", m_data_ptr);
    
    cyborg.m_scale = glm::vec3(0.2f);
    cyborg.m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    dirlight.set_color(glm::vec3(1.0, 0.5, 0.5));
    dirlight.set_ambient_strength(glm::vec3(0.1, 0.1, 0.1));
    dirlight.set_const_attenuation(10.0);
    dirlight.set_lin_attenuation(10.0);
    dirlight.set_quad_attenuation(10.0f);
    dirlight.set_direction(glm::vec3(1.0, 0.3,1.0));
    glClearColor (0.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glEnable(GL_BLEND);
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
    glm::mat4 VP = m_mat.projection*m_mat.view;
    //eTB_GLSL_print_uniforms (lighting_shader_ptr->ID);
    dirlight.set_shader(0, lighting_shader_ptr->ID);
    glUseProgram(lighting_shader_ptr->ID);
    int light = glGetUniformLocation(lighting_shader_ptr->ID, "numlight");
    std::cout << light << "light" << std::endl;
    glUniform1i(light, 1);

    glUniform3f(glGetUniformLocation(lighting_shader_ptr->ID, "eye_position"), cam.m_eye[0], cam.m_eye[1], cam.m_eye[2]);
    cyborg.draw(lighting_shader_ptr->ID, m_mat.view, m_mat.projection);
    
    //cyborg2.draw(model_shader_ptr->ID, m_mat.view, m_mat.projection);
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
