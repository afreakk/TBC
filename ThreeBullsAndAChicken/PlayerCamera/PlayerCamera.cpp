#include "stdafx.h"
#include "PlayerCamera.h"

#include "PlayerCameraStateNormal.h"
#include "PlayerCameraStateSelection.h"
#include "PlayerCameraStateLERP.h"
PlayerCamera::PlayerCamera(Player* player) :m_player(player)
{
	m_states[PLAYER_STATES::PlayerNormalState] = new PlayerCameraStateNormal();
	m_states[PLAYER_STATES::PlayerSelectionState] = new PlayerCameraStateSelection();
	m_states[PLAYER_STATES::PlayerLERPState] = new PlayerCameraStateLERP();
	setNewState(PLAYER_STATES::PlayerNormalState,false);
}


PlayerCamera::~PlayerCamera()
{
	m_states[m_currentState]->exit();
	for (auto& itt : m_states)
		delete itt.second;
}

void PlayerCamera::update()
{
	m_states[m_currentState]->update();
}

void PlayerCamera::notify(PLAYER_STATES newState)
{
	setNewState(newState,true);
}
void PlayerCamera::setNewState(PLAYER_STATES newState,bool exitLast)
{
	if (exitLast)
		m_states[m_currentState]->exit();
	m_currentState = newState;
	m_states[m_currentState]->init(m_player->getNode());
}