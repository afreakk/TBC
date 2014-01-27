#include "stdafx.h"
#include "GameStateNormal.h"


GameStateNormal::GameStateNormal(Player* player) : GameState(PLAYER_STATES::PlayerNormalState), m_player(player), m_spaceDown(false)
{
}


GameStateNormal::~GameStateNormal()
{
}
void GameStateNormal::update()
{
	if (m_spaceDown)
	{
		m_spaceDown = true;
		m_player->setState(PLAYER_STATES::PlayerSelectionState);
		m_state = PLAYER_STATES::PlayerSelectionState;
	}
}

void GameStateNormal::keyPressed(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_SPACE)
		m_spaceDown = true;
}
void GameStateNormal::keyReleased(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_SPACE)
		m_spaceDown = false;

}