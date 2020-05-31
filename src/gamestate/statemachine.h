#pragma once
#include <memory>
#include <stack>
#include "src/gamestate/state.h"

class StateMachine
{
public:
    StateMachine();
    ~StateMachine() = default;
    void add_state(std::unique_ptr<State> new_state, bool is_replacing = true);
    void remove_state();
    void update_statestack();
    std::unique_ptr<State>& retrieve_active_state();
private:
    std::stack<std::unique_ptr<State>> m_state_stack;
    std::unique_ptr<State> m_new_state;
    bool m_adding;
    //this is to avoid data racing
    bool m_removing;
    bool m_replacing;
};
