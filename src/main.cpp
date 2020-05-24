#include <memory>

#include "main.h"
#include "components/Icomponents.h"

#include "utilities/timer.h"
#include "utilities/camera.h"
#include "foundation/shader.h"
#include "gltypes.h"
#include "physics/collisiondetector.h"
std::shared_ptr<Shader> monotone_shader_ptr;
std::shared_ptr<Shader> skybox_shader_ptr;
std::shared_ptr<Shader> tex_shader_ptr;
std::shared_ptr<Shader> model_shader_ptr;
std::shared_ptr<Shader> lighting_shader_ptr;

GLMatrices monotone_mat;
GLMatrices skybox_mat;
GLMatrices tex_mat;
GLMatrices model_mat;

PointLight plight;
GLFWwindow *window;
bool drag = false;
double cxpos, pxpos, cypos, pypos;

FreeCam cam(0.5f, 0.5f, 0.01f);
Skybox sky;
Car car;
Coin coin;
Track track;
Terrain ter;
//Model model;

GameData _data;

int flag2 = 0;
int flag1 = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

int camera = 1;
int yes = 0;
float delta_t = 1.0f/60.0f;
Timer t60(delta_t);
Timer t1(1.0f);

void displayGLinfo();
void dispScore();
void endGame();

void draw(GLMatrices& mat) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(camera == 1)
    {
        //*cos(obstacle.rotation*M_PI/180)
        glm::vec3 eye (car.m_position.x+2.0 ,car.m_position.y+0.5, car.m_position.z + 1.5);
        glm::vec3 target (car.m_position.x-0.2,car.m_position.y-0.2,car.m_position.z);
        glm::vec3 up (0, 0, 1);
        mat.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    }
    glm::mat4 VP = mat.projection * mat.view;
    
    //obstacle.draw(VP);
    //track.draw(VP, monotone_programID, tex_programID, monotone_mat, tex_mat);
    car.draw(VP, monotone_shader_ptr->ID, monotone_mat);
    coin.draw(VP, monotone_shader_ptr->ID, monotone_mat);
}

void print_mat4(glm::mat4& m)
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << "\n\n" << std::endl;
    }
    return;
}

void draw_cam(int width, int height)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //*cos(obstacle.rotation*M_PI/180)
    cam.update_matrices(monotone_mat);
    cam.update_matrices(skybox_mat);
    cam.update_matrices(tex_mat);
    cam.update_matrices(model_mat);
    
    monotone_mat.projection = glm::perspective(glm::radians(55.0f), (float)width / (float)height, 0.1f, 100.0f);
    skybox_mat.projection = glm::perspective(glm::radians(55.0f), (float)width / (float)height, 0.1f, 100.0f);
    tex_mat.projection = glm::perspective(glm::radians(55.0f), (float)width / (float)height, 0.1f, 100.0f);
    model_mat.projection = glm::perspective(glm::radians(55.0f), (float)width / (float)height, 0.1f, 100.0f);
    
    glm::mat4 VP = monotone_mat.projection * monotone_mat.view;
    
    car.draw(VP, monotone_shader_ptr->ID, monotone_mat);
    coin.draw(VP, monotone_shader_ptr->ID, monotone_mat);
    ter.draw(VP, monotone_shader_ptr->ID, monotone_mat, tex_shader_ptr->ID, tex_mat);
    track.draw(VP, monotone_shader_ptr->ID, tex_shader_ptr->ID, monotone_mat, tex_mat);
    //model.draw(VP, model_shader_ptr->ID, model_mat);
    sky.draw(VP, skybox_shader_ptr->ID, skybox_mat);
    return;
}

void draw_carcam(int width, int height)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //*cos(obstacle.rotation*M_PI/180)
    car.m_cam.update_matrices(monotone_mat);
    car.m_cam.update_matrices(skybox_mat);
    car.m_cam.update_matrices(tex_mat);
    //print_mat4(monotone_mat.view);
    monotone_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    skybox_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    tex_mat.projection = glm::perspective(glm::radians(15.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 VP = monotone_mat.projection * monotone_mat.view;
    
    car.draw(VP, monotone_shader_ptr->ID, monotone_mat);
    coin.draw(VP, monotone_shader_ptr->ID, monotone_mat);
    //ter.draw(VP, monotone_program.ID, monotone_mat, tex_program.ID, tex_mat);
    track.draw(VP, monotone_shader_ptr->ID, tex_shader_ptr->ID, monotone_mat, tex_mat);
    sky.draw(VP, skybox_shader_ptr->ID, skybox_mat);
    return;
}

void tick_elements() {
    coin.update(0.0f);
    return;
}

void initGL(GLFWwindow *window, int width, int height) {
    const float x1 = 0.0f;
    const float x2 = 0.0f;
    
    glEnable(GL_DEPTH_TEST);
    _data.init();
    monotone_shader_ptr = _data.resmanager_ptr->retrieve_shader("monotone");
    skybox_shader_ptr = _data.resmanager_ptr->retrieve_shader("skybox");
    tex_shader_ptr = _data.resmanager_ptr->retrieve_shader("texture");
    model_shader_ptr = _data.resmanager_ptr->retrieve_shader("model");
    //lighting_shader_ptr = _data.resmanager_ptr->retrieve_shader("lighting");
    
    monotone_mat.MatrixID = glGetUniformLocation(monotone_shader_ptr->ID, "MVP");
    monotone_mat.Tr = glGetUniformLocation(monotone_shader_ptr->ID, "T");
    skybox_mat.MatrixID = glGetUniformLocation(skybox_shader_ptr->ID, "MVP");
    tex_mat.MatrixID = glGetUniformLocation(tex_shader_ptr->ID, "MVP");
    model_mat.MatrixID = glGetUniformLocation(model_shader_ptr->ID, "MVP");
    
    track = Track(x1, x2, 0, 1.0f, 1.0f, 0.1f);
    car = Car(x1, x2);
    coin = Coin(0.2f, 0.2f, 0.0f, 0.01f, 0.01f);
    ter = Terrain(-0.01f, 0.1f, 1.4f);
    sky = Skybox("skybox");
    //model = Model("cyborg.obj");
    
    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f);
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    displayGLinfo();
    return;
}

void step_input(GLFWwindow *window) {
    int forward  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int car_break = glfwGetKey(window, GLFW_KEY_SPACE);
    
    int rearview = glfwGetKey(window, GLFW_KEY_1);
    int frontview = glfwGetKey(window,GLFW_KEY_2);
    
    if(rearview)
    {
        camera = 1;
        return;
    }
    if(frontview)
    {
        camera = 2;
        return;
    }
    if(right)
    {
        cam.update_cam(turn_cw);
        return;
    }
    if(left)
    {
        cam.update_cam(turn_ccw);
    }
    if(forward)
    {
        cam.update_cam(move_forward);
    }
    double deltax, deltay;
    pxpos = cxpos;
    pypos = cypos;
    
    return;
}

void car_input(GLFWwindow *window) {
    int forward  = glfwGetKey(window, GLFW_KEY_UP);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int left = glfwGetKey(window, GLFW_KEY_LEFT);
    int car_break = glfwGetKey(window, GLFW_KEY_SPACE);
    
    int camforward = glfwGetKey(window, GLFW_KEY_2);
    int camright = glfwGetKey(window,GLFW_KEY_3);
    int camleft = glfwGetKey(window,GLFW_KEY_1);
    if(right)
    {
        car.receive_input(car_turn_cw, _data, delta_t);
        return;
    }
    if(left)
    {
        car.receive_input(car_turn_ccw, _data, delta_t);
        return;
    }
    if(forward)
    {
        car.receive_input(forward_accelerate, _data, delta_t);
        std::cout << "forward" << std::endl;
        return;
    }
    if(camforward)
    {
        cam.update_cam(move_forward);
    }
    if(camleft)
    {
        cam.update_cam(turn_ccw);
    }
    if(camright)
    {
        cam.update_cam(turn_cw);
    }
    car.receive_input(car_not_accelerating, _data, delta_t);
    return;
}

void tick_input(GLFWwindow *window)
{
    return;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;
    window = initGLFW(width, height);
    
    initGL (window, width, height);
    GJK collisiondetect;
    
    while (!glfwWindowShouldClose(window))
    {
        bool collided = false;
        if (t60.processTick()) {
            car.update(delta_t);
            draw_cam(width, height);
            glfwSwapBuffers(window);
            tick_elements();
            car_input(window);
            collided = collisiondetect.intersected(car.collision_shape, coin.collision_shape);
            if(collided)
            {
                std::cout << "collided" << std::endl;
                car.resolve_collision();
                coin.resolve_collision();
            }
        }
        glfwPollEvents();
    }
    quit(window);
}

void displayGLinfo()
{
    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    return;
}
