#include "main.h"
#include "components/Icomponents.h"
#include "utilities/timer.h"
#include "utilities/camera.h"

#include "gltypes.h"

GLuint monotone_programID;
GLuint skybox_programID;
GLuint tex_programID;

GLMatrices monotone_mat;
GLMatrices skybox_mat;
GLMatrices tex_mat;

GLFWwindow *window;
bool drag = false;
double cxpos, pxpos, cypos, pypos;
/**************************
* Customizable functions *
**************************/
glm::vec3 helcamEye = glm::vec3(0,-1.0, 9.0f);
glm::vec3 helcamTarget = glm::vec3(0, 1.0f, 0.0f);

FreeCam cam(0.0f, 0.0f, 0.5f);
Skybox sky;
Car car;
Coin coin;
//Track track;
Terrain ter;



int flag2 = 0;
int flag1 = 1;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

int camera = 1;
int yes = 0;
Timer t60(1.0 / 60);

void displayGLinfo();
void dispScore();
void endGame();

void draw(GLMatrices& mat) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glUseProgram(monotone_programID);
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
    car.draw(VP, monotone_programID, monotone_mat);
    coin.draw(VP, monotone_programID, monotone_mat);
}

void print_mat4(glm::mat4& m)
{
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}

void draw_cam(int width, int height)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glUseProgram(monotone_programID);

    //*cos(obstacle.rotation*M_PI/180)
    cam.update_matrices(monotone_mat);
    cam.update_matrices(skybox_mat);
    cam.update_matrices(tex_mat);
    
    monotone_mat.projection = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);
    skybox_mat.projection = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);
    tex_mat.projection = glm::perspective(glm::radians(35.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 VP = monotone_mat.projection * monotone_mat.view;
    
    //track.draw(VP, monotone_programID, tex_programID,monotone_mat, tex_mat);
    car.draw(VP, monotone_programID, monotone_mat);
    coin.draw(VP, monotone_programID, monotone_mat);
    ter.draw(VP, monotone_programID, monotone_mat);
    sky.draw(VP, skybox_programID, skybox_mat);
    return;
}
void tick_elements() {
    coin.update();
    return;
}

void initGL(GLFWwindow *window, int width, int height) {
    const float x1 = 0.0f;
    const float x2 = 0.0f;
    //obstacle = Obstacle(x1,x2,0,1);
    std::vector<std::string> skybox_files = {
        "right.jpg", "left.jpg",
        "bottom.jpg", "top.jpg",
        "front.jpg", "back.jpg"
    };
    
    glEnable(GL_DEPTH_TEST);
    extern GameData _data(false);
    monotone_programID = LoadShaders("monotone.vert", "monotone.frag");
    skybox_programID = LoadShaders("skybox.vert", "skybox.frag");
    tex_programID = LoadShaders("singletex.vert", "singletex.frag");
    
    std::cout << monotone_programID << "ID Comp" << skybox_programID << std::endl;
    monotone_mat.MatrixID = glGetUniformLocation(monotone_programID, "MVP");
    monotone_mat.Tr = glGetUniformLocation(monotone_programID, "T");
    skybox_mat.MatrixID = glGetUniformLocation(skybox_programID, "MVP");
    tex_mat.MatrixID = glGetUniformLocation(tex_programID, "MVP");
    
    //track = Track(x1, x2, 0, 1.0f, 1.0f, 0.1f);
    car = Car(x1, x2);
    coin = Coin(0.2f, 0.2f, 0.2f, 0.05f, 0.01f);
    ter = Terrain(-0.01f, 0.1f, 1.4f);
    sky = Skybox("skybox");
    
    
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
    }
    if(frontview)
    {
        camera = 2;
    }
    if(right)
    {
        cam.update_cam(turn_cw);
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
    while (!glfwWindowShouldClose(window))
    {
        if (t60.processTick()) {
            draw_cam(width, height);
            glfwSwapBuffers(window);
            tick_elements();
            step_input(window);
        }
        glfwPollEvents();
    }
    quit(window);
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    skybox_mat.projection = glm::perspective(1.0f, 1.0f,1.0f,500.0f);
    monotone_mat.projection = skybox_mat.projection;
}

void dispScore(){
    std::string s("display");
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
}

void scroll_call(double x_scroll, double y_scroll){
    glm::vec3 delta = helcamTarget - helcamEye;
    helcamEye.x += (y_scroll)*delta.x/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
    helcamEye.y += (y_scroll)*delta.y/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
    helcamEye.z += (y_scroll)*delta.z/sqrt(delta.x*delta.x + delta.y*delta.y + delta.z*delta.z);
}
int ind = 0;

void endGame(){
    std::string s = " Game Over ";
    std::string b = " Score : ";

    s = b+s;
    glfwSetWindowTitle(window, const_cast<char*>(s.c_str()));
    ind++;
    if(ind == 30)
    {
        exit(0);
    }

}

void displayGLinfo()
{
    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    return;
}
