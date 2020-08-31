#pragma once
#include <memory>
#include "src/utilities/managers/resourcemanager.h"
#include "src/utilities/managers/inputmanager.h"
#include "src/foundation/objloader.h"
#include "src/gamestate/statemachine.h"

class GameData
{
public:
    GameData();
    //GameData(bool glcontext_created);
    ~GameData() = default;
    std::unique_ptr<ResourceManager> resmanager_ptr = nullptr;
    std::unique_ptr<InputManager> inputmanager_ptr = nullptr;
    StateMachine machine;
    objl::Loader objloader;
    
    void init();
private:
    
};
