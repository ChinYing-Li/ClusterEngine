
#include "src/utilities/timer.h"
#include <GLFW/glfw3.h>

Timer::Timer():
m_prev(0)
{}

Timer::Timer(double interval):
m_interval(interval),
m_prev(0)
{}

bool Timer::processTick() {
    double cur = glfwGetTime();
    if (cur - m_prev >= m_interval)
    {
        m_prev = cur;
        return true;
    }
    else
        return false;
}
