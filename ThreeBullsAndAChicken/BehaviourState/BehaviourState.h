#pragma once
#include "stdafx.h"
#include "../ModelBehaviour/ModelHandler.h"

enum class BEHAVOUR_STATE
{
	NORMAL,
	SELECTION,
	LERP,
	DEAD
};
class BehaviourState : public boost::noncopyable
{
public:
	BehaviourState(BEHAVOUR_STATE state) :m_state(state), m_nextState(m_state)
	{
	}
	virtual ~BehaviourState()
	{
	}
	virtual void update(ModelHandler& )=0;
	const BEHAVOUR_STATE& getState() const 
	{
		return m_state;
	}
	BEHAVOUR_STATE getNextState() const
	{
		return m_nextState;
	}
protected:
	const BEHAVOUR_STATE m_state;
	BEHAVOUR_STATE m_nextState;
};
