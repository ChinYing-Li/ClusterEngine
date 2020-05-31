#pragma once

#include "src/gamestate/state.h"

// during car racing
class RacingState: public State
{
public:
    RacingState();
    ~RacingState();
    
    void virtual init() = 0;
    void virtual update() = 0;
    void virtual render() = 0;
};
