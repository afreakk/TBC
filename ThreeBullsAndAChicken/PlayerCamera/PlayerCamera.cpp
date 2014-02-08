#include "stdafx.h"
#include "PlayerCamera.h"

#include "PlayerCameraStateNormal.h"
#include "PlayerCameraStateSelection.h"
#include "PlayerCameraStateLERP.h"
PlayerCamera::PlayerCamera() 
: m_player(nullptr)
, m_currentState{nullptr} 
, m_playerCameraVars(new PlayerCameraVars())
{
}
void PlayerCamera::init(Player* player)
{
	m_player = player;
}


PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::update()
{
	if (m_currentState)
	    m_currentState->update();
}

void PlayerCamera::notify(PLAYER_HANDLER_STATE newState)
{
	setNewState(newState);
}
void PlayerCamera::setNewState(PLAYER_HANDLER_STATE newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case PLAYER_HANDLER_STATE::NORMAL:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateNormal( m_player->getNode()) };
		break;
	case PLAYER_HANDLER_STATE::SELECTION:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateSelection() };
		break;
	case PLAYER_HANDLER_STATE::LERP:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateLERP(m_player->getNode()) };
		break;
	case PLAYER_HANDLER_STATE::DEAD:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateLERP(m_player->getNode()) };
		break;
	case PLAYER_HANDLER_STATE::TUMBLE:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateNormal( m_player->getNode()) };
		break;
	default:
		assert(0);
		break;
	}
}