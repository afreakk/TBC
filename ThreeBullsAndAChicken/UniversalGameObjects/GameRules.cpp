#include "stdafx.h"
#include "GameRules.h"


GameRules::GameRules() :m_enemyHnd(nullptr), m_player(nullptr)
{
}

GameRules::~GameRules()
{
	OISCore::getSingletonPtr()->removeKeyListener("GameRules");
}

void GameRules::init(EnemyHandler* enemyHandler, Player* player)
{
	m_enemyHnd = enemyHandler;
	m_player = player;

	OISCore::getSingletonPtr()->addKeyListener(this, "GameRules");
}
void GameRules::update()
{

}

bool GameRules::keyPressed(const OIS::KeyEvent& e)
{
	PLAYER_STATES pState = m_player->getState();
	switch (pState)
	{
	case PLAYER_STATES::PlayerNormalState:
		if (e.key == OIS::KeyCode::KC_SPACE)
			m_player->setState(PLAYER_STATES::PlayerSelectionState);
		break;
	case PLAYER_STATES::PlayerSelectionState:
		break;
	case PLAYER_STATES::PlayerLERPState:
		break;
	case PLAYER_STATES::PlayerAttackState:
		break;
	default:
		break;
	}

	return true;
}
bool GameRules::keyReleased(const OIS::KeyEvent& e)
{

	return true;
}