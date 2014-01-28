#include "stdafx.h"
#include "PlayerCamera.h"

#include "PlayerCameraStateNormal.h"
#include "PlayerCameraStateSelection.h"
#include "PlayerCameraStateLERP.h"
PlayerCamera::PlayerCamera(Player* player) :m_player(player), m_currentState{nullptr} 
{
}


PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::update()
{
	m_currentState->update();
}

void PlayerCamera::notify(BEHAVOUR_STATE newState)
{
	setNewState(newState);
}
void PlayerCamera::setNewState(BEHAVOUR_STATE newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case BEHAVOUR_STATE::NORMAL:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateNormal( m_player->getNode()) };
		break;
	case BEHAVOUR_STATE::SELECTION:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateSelection() };
		break;
	case BEHAVOUR_STATE::LERP:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateLERP(m_player->getNode()) };
		break;
	default:
		assert(0);
		break;
	}
}