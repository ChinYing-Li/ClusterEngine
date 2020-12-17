#pragma once

namespace Cluster
{
class FPSCounter {
public:
    FPSCounter();

    void update();

private:
    unsigned int m_frames;
    double m_prev_time;
};
}
