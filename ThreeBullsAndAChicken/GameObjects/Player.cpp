#include "stdafx.h"
#include "Player.h"

#include "PlayerNormalState.h"

Player::Player() 
{
	m_currentState = new PlayerNormalState();
	m_model.init(Ogre::Vector3(0.0f, 0.0f, -10.0f));
}

Player::~Player()
{
}

void Player::update()
{
	m_currentState->update();
}