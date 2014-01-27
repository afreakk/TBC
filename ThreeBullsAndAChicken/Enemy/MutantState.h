#pragma once
#include "stdafx.h"
#include "MutantModelHandler.h"
enum class MUTANT_STATES
{
	STATE_NORMAL,
	STATE_LERP,
	STATE_ATTACK,
	STATE_DEAD
};
class MutantState : public boost::noncopyable
{
public:
	MutantState(MUTANT_STATES state) : m_state(state),m_nextState(m_state) {}
	virtual void update(MutantModelHandler*) = 0;
	MUTANT_STATES getState() const 
	{
		return m_state;
	}
	MUTANT_STATES getNextState() const
	{
		return m_nextState;
	}
protected:
	MUTANT_STATES m_state;
	MUTANT_STATES m_nextState;
};

