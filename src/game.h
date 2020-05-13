#pragma once

enum gameState
{
    GAME_RACING;
    GAME_PAUSED;
    GAME_POSTRACING;
};

class Game
{
public:
    Game();
    ~Game();
    void render();
private:
    const float delta_t = 1.0f / 60.0f;
    gameState gstate;
    Timer m_timer;
    ShaderManager m_shadermanager;
    TextureManager m_texmanager;
    InputManager m_inputmanager;
    
    void init();
    void run();
}
