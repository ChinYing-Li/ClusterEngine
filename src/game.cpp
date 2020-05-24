#include <iostream>
#include "game.h"
const int default_width = 800;
const int default_height = 600;
Game::Game():
m_windowptr(nullptr)
{
    init();
}

Game::~Game()
{}

void Game::init()
{
    m_windowptr = initGLFW(800, 600);
    
}
GLFWwindow* Game::initGLFW(const int width, const int height) {
    GLFWwindow *window;
    glfwSetErrorCallback(InputManager::error_callback);
    if (!glfwInit()) {
        // exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,                 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,                 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,           GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Sample OpenGL 3.3 Application", NULL, NULL);

    if (!window) glfwTerminate();
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "Error: Failed to initialise GLEW : " << glewGetErrorString(err) << std::endl;
        exit (1);
    }
    glfwSwapInterval(1);

    // should be handled by input manager??
    /* Register function to handle window resizes */
    /* With Retina display on Mac OS X GLFW's FramebufferSize
       is different from WindowSize */
    glfwSetFramebufferSizeCallback(window, InputManager::reshapeWindow);
    glfwSetWindowSizeCallback(window, InputManager::reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, InputManager::quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, InputManager::keyboard_callback);  // general keyboard input
    glfwSetCharCallback(window, InputManager::keyboard_char); // simpler specific character handling
    return window;
}


