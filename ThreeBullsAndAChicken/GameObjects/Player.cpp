#include "stdafx.h"
#include "Player.h"

#include "PlayerNormalState.h"

Player::Player() 
{
	m_model.init(0.0, -10.0, 0.0);
	m_currentState = new PlayerNormalState();
	m_currentState->init();
	m_currentCameraState = new PlayerCameraStateNormal();
	m_currentCameraState->init(m_model.getNode());
}

Player::~Player()
{
	m_currentCameraState->exit();
	m_currentState->exit();
	delete m_currentCameraState;
	delete m_currentState;

}

void Player::update()
{
	m_currentState->update(m_model);
	m_currentCameraState->update();
}