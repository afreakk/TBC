#pragma once
#include "stdafx.h"
#include "PlayerModelHandler.h"
enum class PLAYER_STATES
{
	PlayerNormalState,
	PlayerSelectionState,
	PlayerLERPState,
	PlayerAttackState
};
class PlayerState
{
public:
	PlayerState(PLAYER_STATES state) :m_state(state), m_nextState(m_state)
	{
	}
	virtual ~PlayerState()
	{
	}
	virtual void update(PlayerModelHandler& )=0;
	PLAYER_STATES getState()
	{
		return m_state;
	}
	PLAYER_STATES getNextState()
	{
		return m_nextState;
	}
protected:
	PLAYER_STATES m_state;
	PLAYER_STATES m_nextState;
};

