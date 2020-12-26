#pragma once

namespace Cluster
{
class Timer {
public:
  Timer();
  double get_frame_per_second() const;

private:
  void update();
  unsigned int m_frames;
  double m_prev_time;
  double m_frame_per_second;
};
}
