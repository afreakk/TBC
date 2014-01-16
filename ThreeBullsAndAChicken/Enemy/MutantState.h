#pragma once
#include "stdafx.h"
#include "MutantModelHandler.h"
enum class MUTANT_STATES
{
	STATE_NORMAL,
	STATE_LERP,
	STATE_ATTACK
};
class MutantState
{
public:
	MutantState(MUTANT_STATES state) : m_state(state) {}
	virtual void update(MutantModelHandler*) = 0;
	MUTANT_STATES getState() const 
	{
		return m_state;
	}
protected:
	MUTANT_STATES m_state;
};

