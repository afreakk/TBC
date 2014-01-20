#pragma once
#include "stdafx.h"
#include "MutantModelHandler.h"
#include "../Player/Player.h"
enum class MUTANT_STATES
{
	STATE_NORMAL,
	STATE_LERP,
	STATE_ATTACK,
	STATE_DEAD
};
class MutantState
{
public:
	MutantState(MUTANT_STATES state) : m_state(state),m_player(nullptr),m_nextState(m_state) {}
	virtual void update(MutantModelHandler*) = 0;
	virtual void init(MutantModelHandler*) = 0;
	virtual void exit() = 0;
	MUTANT_STATES getState() const 
	{
		return m_state;
	}
	MUTANT_STATES getNextState() const
	{
		return m_nextState;
	}
	void setPlayer(Player* player)
	{
		m_player = player;
	}
protected:
	MUTANT_STATES m_state;
	MUTANT_STATES m_nextState;
	Player* m_player;
};

