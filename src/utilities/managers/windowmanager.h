#pragma once

#include <map>
#include <memory>

class GLFWwindow;
namespace Cluster
{
    class WindowManager
    {

    public:
        WindowManager() = delete;
        WindowManager(unsigned int width, unsigned int height);
        ~WindowManager() = default;

        using keyAction = int;
        static void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void quit(GLFWwindow *window);
        static void error_callback(int error, const char *description);
        static void reshapeWindow(GLFWwindow *window, int width, int height);
        static void reset_screen();
        static void displayGLinfo();

        GLFWwindow* window_ptr;

    protected:
        std::map<int, keyAction> m_keyaction;

    private:
        void init_glfw();
        void init_glew();
        GLFWwindow* init_window(const int width, const int height);
    };
} // namespace Cluster
