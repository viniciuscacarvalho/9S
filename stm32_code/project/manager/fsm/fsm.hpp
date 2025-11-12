#ifndef __FSM_HEADER__
#define __FSM_HEADER__

#include "../states/state.hpp"

int setup_fsm();

int execute();

void* transition (state_enum older, state_enum newer);


#endif
