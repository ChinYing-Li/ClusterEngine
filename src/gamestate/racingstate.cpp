#include "src/gamestate/racingstate.h"
#include "src/foundation/shader.h"
#include "src/gamedata.h"

RacingState::RacingState(std::shared_ptr<GameData> data_ptr):
State(data_ptr),
cam(0.5f, 0.1f, 0.5f),
m_mat(),
width(800),
height(600),
dirlight()
{
    init();
    m_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    model_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("model");
    monotone_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("monotone");
    lighting_shader_ptr = m_data_ptr->resmanager_ptr->retrieve_shader("instance_w_lighting");
}

RacingState::~RacingState()
{}

//
void RacingState::init()
{
    srand(0);
    unsigned int numinstance = 2;
    cyborg = objobject("cyborg.obj", m_data_ptr, 2);
    std::vector<glm::mat4> instance_model(2, glm::mat4(1.0));
    for(int i = 0; i < numinstance; ++i)
    {
        instance_model[i] = glm::translate(instance_model[i], glm::vec3(float(rand()%100)/100.0f, 0.0f, float(rand()%100)/100.0f));
        for(int j = 0; j < 4; ++j)
        {
            std::cout << instance_model[i][j][0] << " " << instance_model[i][j][1] << std::endl;
        }
        
    }
    
    cyborg.set_instance_mat(instance_model);
    cyborg.m_scale = glm::vec3(0.05f);
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
    //eTB_GLSL_print_uniforms (lighting_shader_ptr->ID);
    
    set_light_uniform();

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

void RacingState::set_light_uniform()
{
    glUseProgram(lighting_shader_ptr->ID);
    glUniform1i(glGetUniformLocation(lighting_shader_ptr->ID, "numlight"), 1);
    
    dirlight.set_shader(0, lighting_shader_ptr->ID);
    return;
}
