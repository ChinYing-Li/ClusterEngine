#include <iostream>

#include "windowmanager.h"
#include "glfoundation/glincludes.h"

namespace Cluster
{
    WindowManager::
    WindowManager(unsigned int width, unsigned int height)
    {
        init_glfw();
        window_ptr = init_window(width, height);
        displayGLinfo();
    }

    GLFWwindow* WindowManager::
    init_window(const int width, const int height)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,           GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window;
        window = glfwCreateWindow(width, height, "Cluster Engine", nullptr, nullptr);

        if (!window) glfwTerminate();
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cout << "Error: Failed to initialise GLEW : " << glewGetErrorString(err) << std::endl;
            exit (1);
        }
        glfwSwapInterval(1);

        /* Register function to handle window resizes */
        /* With Retina display on Mac OS X GLFW's FramebufferSize
           is different from WindowSize */
        glfwSetFramebufferSizeCallback(window, reshapeWindow);
        glfwSetWindowSizeCallback(window, reshapeWindow);

        // Register function to handle window close.
        glfwSetWindowCloseCallback(window, WindowManager::quit);

        // Register function to handle keyboard input.
        glfwSetKeyCallback(window, WindowManager::keyboard_callback);  // general keyboard input
        return window;
    }

    void WindowManager::
    keyboard_callback(GLFWwindow *window,
                      int key,
                      int scancode,
                      int action,
                      int mods)
    {
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

    void WindowManager
    ::quit(GLFWwindow *window)
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    void WindowManager::
    error_callback(int error, const char *description)
    {
        std::cerr << "Window error: "
                  << description
                  << std::endl;
    }

    void WindowManager::
    reshapeWindow(GLFWwindow *window,
                  int width,
                  int height)
    {
        int fbwidth = width, fbheight = height;
        glfwGetFramebufferSize(window, &fbwidth, &fbheight);
        glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);
        reset_screen();
    }

    void WindowManager::
    reset_screen() {
        return;
    }

    void WindowManager::
    init_glfw()
    {
        glfwSetErrorCallback(error_callback);
        if(!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW library." << std::endl;
            exit(-1);
        }
    }

    void WindowManager::
    init_glew()
    {
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Error: Failed to initialise GLEW : "
                      << glewGetErrorString(err)
                      << std::endl;
            exit (-1);
        }
    }

    void WindowManager::
    displayGLinfo()
    {
        std::cout << "VENDOR:   " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "VERSION:  " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        return;
    }
}
