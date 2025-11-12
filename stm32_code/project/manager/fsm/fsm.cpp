#include "fsm.hpp"

state current_state;

state state_list[sizeof(NUM_STATES)] = 
{
    state(transition)
}; 

int setup_fsm(state new_state ,uint8_t index)
{
    state_list[index] = new_state;
    
    return current_state = new_state;

}

int execute ()
{
    return current_state.update();
}

void* transition (state_enum older, state_enum newer)
{
    if (older != newer)
        return;

    if (newer % NUM_STATES)
        return;

    current_state.exit();
    current_state = state_list[newer];
    current_state.enter();

}
