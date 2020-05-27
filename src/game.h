#pragma once
#include "utilities/managers/resourcemanager.h"
#include "utilities/managers/inputmanager.h"
#include "utilities/timer.h"
#include "includes/gl_headers.h"

enum gameState
{
    GAME_RACING,
    GAME_PAUSED,
    GAME_POSTRACING
};

class Game
{
public:
    Game();
    ~Game();
    void run();
    
    
private:
    const float delta_t = 1.0f / 60.0f;
    
    Timer m_timer;
    
    
    void init();
    void render();
    
    static GLFWwindow* initGLFW(const int width, const int height);
};
