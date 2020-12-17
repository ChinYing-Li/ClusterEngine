#include <GLFW/glfw3.h>

#include "src/glfoundation/glincludes.h"
#include "src/utilities/fpscounter.h"


namespace Cluster
{
FPSCounter::FPSCounter()
{}

void FPSCounter::update()
{
    double time_difference = glfwGetTime() - m_prev_time;
    ++ m_frames;

    if (time_difference > 1.0)
    {
        m_frames = 0; // Start counting again.
        m_prev_time += 1.0;
    }
}

}
