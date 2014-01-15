#include "stdafx.h"
#include "PlayerCamera.h"

PlayerCamera::PlayerCamera(Player* player) :m_player(player)
{
	m_currentState = new PlayerCameraStateNormal();
	m_currentState->init(m_player->getNode());
}


PlayerCamera::~PlayerCamera()
{
	m_currentState->exit();
	delete m_currentState;
}

void PlayerCamera::update()
{
	m_currentState->update();
}
