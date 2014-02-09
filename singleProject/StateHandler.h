#pragma once
#include "HandlerState.h"
#include "PlayerHandlerEnums.h"
template <typename T>
class StateHandler
{
public:
	StateHandler(HandlerState<T>* startingState) : m_currentState(startingState) {  }
	virtual ~StateHandler() { }
	void update()
	{
		m_currentState->update();
		if (m_currentState->getState() != m_currentState->getOriginalState())
			switchState(m_currentState->getState());
	}
	virtual void switchState(T newState)=0;
protected:
	std::unique_ptr<HandlerState<T>> m_currentState;
};


