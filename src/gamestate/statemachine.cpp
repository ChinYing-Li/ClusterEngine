#include "src/gamestate/statemachine.h"
#include <iostream>
StateMachine::StateMachine():
m_adding(false),
m_removing(false),
m_replacing(false)
{}

void StateMachine::add_state(std::unique_ptr<State> new_state, bool replacing)
{
    m_adding = true;
    m_new_state = std::move(new_state);
    m_replacing = replacing;
}

std::unique_ptr<State>& StateMachine::retrieve_active_state()
{
    if(m_state_stack.empty())
    {
        std::cout << "stack empty" << std::endl;
    }
    return m_state_stack.top();
}

void StateMachine::remove_state()
{
    m_removing = true;
}

void StateMachine::update_statestack()
{
    if(!m_state_stack.empty())
    {
        if(m_removing)
        {
            m_state_stack.pop();
            m_removing = false;
        }
    }
    if(m_adding)
    {
        if(!m_state_stack.empty())
        {
            if(m_replacing)
            {
                m_state_stack.pop();
            }
            else m_state_stack.top()->pause();
        }
        m_state_stack.push(std::move(m_new_state));
        m_state_stack.top()->resume();
        m_adding= false;
    }
    return;
}
