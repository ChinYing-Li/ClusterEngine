#include "src/gamestate/state.h"
#include "src/game.h"
State::State(std::shared_ptr<GameData> data_ptr):
m_data_ptr(data_ptr)
{}
