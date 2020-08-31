#pragma once
#include <memory>

#include "src/gamedata.h"
#include "src/utilities/managers/inputmanager.h"
#include "src/utilities/timer.h"

/*
#ifndef _DATA
#define _DATA
extern GameData _data;
#endif
*/
class Game
{
public:
    Game();
    ~Game();
    void run();
    
private:
    std::shared_ptr<GameData> data;
    const float delta_t = 1.0f / 60.0f;
    Timer m_timer;
    float prev_time;
    float cur_time;
    
};
