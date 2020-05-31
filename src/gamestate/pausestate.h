#pragma once

#include "src/gamestate/state.h"

// when the user paused during RacingState
class PauseState: public State
{
public:
    PauseState();
    ~PauseState();
    
    void virtual init() = 0;
    void virtual update() = 0;
    void virtual render() = 0;
}
