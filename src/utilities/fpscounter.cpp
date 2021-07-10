#include <GLFW/glfw3.h>

#include "glfoundation/glincludes.h"
#include "fpscounter.h"


namespace Cluster
{
Timer::
Timer()
{}

double Timer::
get_frame_per_second() const
{
  return m_frame_per_second;
}

void Timer::
update()
{
  double cur_time = glfwGetTime();
  double time_difference = cur_time - m_prev_time;
  ++m_frames;

    if (time_difference >= 1.0)
    {
      m_frame_per_second = double(m_frames) / time_difference;
      m_frames = 0; // Start counting again.
      m_prev_time = cur_time;
    }
}

}
