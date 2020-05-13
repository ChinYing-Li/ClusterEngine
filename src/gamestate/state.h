#pragma once

class State
{
public:
    State() = default;
    ~State() = default;
    void virtual init() = 0;
    void virtual update() = 0;
    void virtual render() = 0;
private:
    
}
