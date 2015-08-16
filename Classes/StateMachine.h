#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

enum class State {
	INITIAL, CONNECTING, CONNECTED, SWAP, CHANGE_COLOR, REMOVE_DOT
};

class StateMachine {
public:

	void changeState(enum State state);

	const State getCurrentState();

	virtual ~StateMachine();

private:
	State currentState;
};

#endif /* STATEMACHINE_H_ */
