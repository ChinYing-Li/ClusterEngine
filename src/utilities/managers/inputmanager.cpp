#include <iostream>

#include "inputmanager.h"
#include "includes/GLincludes.h"

InputManager::InputManager()
{
    window_ptr = initGLFW(800, 600);
    displayGLinfo();
}

GLFWwindow* InputManager::initGLFW(const int width, const int height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,           GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window;
    
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
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);

    /* Register function to handle window close */
    glfwSetWindowCloseCallback(window, InputManager::quit);

    /* Register function to handle keyboard input */
    glfwSetKeyCallback(window, InputManager::keyboard_callback);  // general keyboard input
    return window;
}

void InputManager::keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE)
    {
    }
    else if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

void InputManager::quit(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void InputManager::error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void InputManager::reshapeWindow(GLFWwindow *window, int width, int height) {
    int fbwidth = width, fbheight = height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
       is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);
    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
    reset_screen();
}

void InputManager::reset_screen() {
    return;
}

void InputManager::displayGLinfo()
{
    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    return;
}
