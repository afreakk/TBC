#pragma once
#include "stdafx.h"
#include"../Player/Player.h"
class GameState
{
public:
	GameState(PLAYER_STATES thisState) :m_state(thisState), m_originalState(m_state){}
	virtual ~GameState()
	{
	}
	virtual void update()=0;
	virtual void keyPressed(const OIS::KeyEvent&)=0;
	virtual void keyReleased(const OIS::KeyEvent&)=0;
	PLAYER_STATES getState()
	{
		return m_state;
	}
	PLAYER_STATES getOriginalState()
	{
		return m_originalState;
	}
	void setState(PLAYER_STATES newState)
	{
		m_state = newState;
	}
protected:
	PLAYER_STATES m_state;
	const PLAYER_STATES m_originalState;
};

