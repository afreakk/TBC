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

void PlayerCamera::notify(PLAYER_STATES newState)
{
	setNewState(newState);
}
void PlayerCamera::setNewState(PLAYER_STATES newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case PLAYER_STATES::PlayerNormalState:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateNormal( m_player->getNode()) };
		break;
	case PLAYER_STATES::PlayerSelectionState:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateSelection() };
		break;
	case PLAYER_STATES::PlayerLERPState:
		m_currentState = unique_ptr<PlayerCameraState>{ new PlayerCameraStateLERP(m_player->getNode()) };
		break;
	default:
		assert(0);
		break;
	}
}