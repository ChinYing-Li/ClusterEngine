#pragma once

#include <map>
#include <memory>
class GLFWwindow;

class InputManager
{
    
public:
    InputManager();
    ~InputManager() = default;
    using keyAction = int;
    static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void quit(GLFWwindow *window);
    static void error_callback(int error, const char *description);
    static void reshapeWindow(GLFWwindow *window, int width, int height);
    static void reset_screen();
    
    GLFWwindow* window_ptr;
    
protected:
    std::map<int, keyAction> m_keyaction;
    GLFWwindow* initGLFW(const int width, const int height);
    void displayGLinfo();
    friend class Game;
};
