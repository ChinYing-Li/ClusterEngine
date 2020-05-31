#include <iostream>
#include "src/game.h"
#include "src/gamestate/Istate.h"


Game::Game()
{
    glfwSetErrorCallback(InputManager::error_callback);
    if(!glfwInit())
    {
        std::cout << "failed to initialize GLFW library" << std::endl;
    }
    data = std::make_shared<GameData>();
    data->init();
    data->machine.add_state(std::make_unique<RacingState>(data), false);
    std::cout << "game init" << std::endl;
    run();
}

Game::~Game()
{}

void Game::run()
{
    int count = 0;
    while(!glfwWindowShouldClose(data->inputmanager_ptr->window_ptr))
    {
        
        if (m_timer.processTick())
        {
            std::cout << count << std::endl;
            ++count;
            data->machine.update_statestack();
            glfwSwapBuffers(data->inputmanager_ptr->window_ptr);
            data->machine.retrieve_active_state()->handle_input(data->inputmanager_ptr->window_ptr);
            data->machine.retrieve_active_state()->render();
            
        }
        glfwPollEvents();
    }
    return;
}
