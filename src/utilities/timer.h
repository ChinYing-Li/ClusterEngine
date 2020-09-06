#pragma once

class Timer {
public:
    Timer();
    Timer(double interval);
    bool processTick();
    double m_interval;
private:
    double m_prev;
};
