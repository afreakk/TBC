#pragma once
#include "stdafx.h"
#include "HandlerState.h"
#include "../PlayerHandler/PlayerHandlerEnums.h"
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
protected:
	unique_ptr<HandlerState<T>> m_currentState;
	virtual void switchState(T newState)=0;
};


