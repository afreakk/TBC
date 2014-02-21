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
		if (m_quedState.first)
		{
			m_quedState.first = false;
			switchState(m_quedState.second);
		}
		m_currentState->update();
		if (m_currentState->getState() != m_currentState->getOriginalState())
			switchState(m_currentState->getState());
	}
	virtual void switchState(T newState)=0;
	void queSwitchState(T newState)
	{
		m_quedState.first = true;
		m_quedState.second = newState;
	}
protected:
	std::unique_ptr<HandlerState<T>> m_currentState;
	std::pair<bool,T> m_quedState;
};


