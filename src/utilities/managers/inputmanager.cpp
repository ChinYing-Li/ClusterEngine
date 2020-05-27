#include "inputmanager.h"

#include "includes/gl_headers.h"

InputManager::InputManager()
{}

void InputManager::keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void InputManager::keyboard_char(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
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
