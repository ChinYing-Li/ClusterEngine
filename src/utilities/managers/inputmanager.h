#pragma once

#include <map>

class GLFWwindow;

class InputManager
{
    
public:
    InputManager();
    ~InputManager() = default;
    using keyAction = int;
protected:
    std::map<int, keyAction> m_keyaction;
    
    // mouse action?
    // callbacks
    static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void keyboard_char(GLFWwindow *window, unsigned int key);
    static void quit(GLFWwindow *window);
    static void error_callback(int error, const char *description);
    static void reshapeWindow(GLFWwindow *window, int width, int height);
    static void reset_screen();
    friend class Game;
};
