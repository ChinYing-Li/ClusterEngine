#pragma once

namespace Cluster
{
class Timer {
public:
  Timer();
  double get_frame_per_second() const;
  bool update();

private:
  unsigned int m_frames;
  double m_prev_time;
  double m_frame_per_second;
};
} // namespace Cluster
