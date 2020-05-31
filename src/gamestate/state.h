#pragma once
#include <memory>

class GameData;
class GLFWwindow;

class State
{
public:
    State() = delete;
    State(std::shared_ptr<GameData> data_ptr);
    virtual ~State() = default;
    void virtual init() = 0;
    void virtual update() = 0;
    void virtual render() = 0;
    void virtual handle_input(GLFWwindow *window) = 0; // handle input from inputmanager
    void virtual pause(){};
    void virtual resume(){};
protected:
    std::shared_ptr<GameData> m_data_ptr;
};
