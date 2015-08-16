#include "StateMachine.h"

void StateMachine::changeState(enum State state) {
	currentState = state;
}

const State StateMachine::getCurrentState() {
	return currentState;
}

StateMachine::~StateMachine() {
}

