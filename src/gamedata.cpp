#include "includes/gamedata.h"

GameData::GameData():
objloader()
{}

void GameData::init()
{
    inputmanager_ptr = std::make_unique<InputManager>();
    resmanager_ptr = std::make_unique<ResourceManager>();
    std::cout << "Game data initialized\n" << std::endl;
    return;
}
