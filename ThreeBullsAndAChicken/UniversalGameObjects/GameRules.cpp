#include "stdafx.h"
#include "GameRules.h"
#include "GameStateNormal.h"
#include "GameStateSelection.h"
#include "GameStateLERP.h"


GameRules::GameRules() :m_enemyHnd(nullptr), m_player(nullptr), m_currentState(nullptr)
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
	switchState(m_player->getState());
}
void GameRules::update()
{
	m_currentState->update();
	if (m_currentState->getState() != m_currentState->getOriginalState())
		switchState(m_currentState->getState());
}

void GameRules::switchState(PLAYER_STATES newState)
{
	std::vector<unsigned> mutantList;
	switch (newState)
	{
	case PLAYER_STATES::PlayerNormalState:
		m_currentState.reset();
		m_currentState = unique_ptr<GameState>( new GameStateNormal(m_player) ) ;
		break;
	case PLAYER_STATES::PlayerSelectionState:
		m_currentState.reset();
		m_currentState = unique_ptr<GameState>( new GameStateSelection());
		break;
	case PLAYER_STATES::PlayerLERPState:
		mutantList = static_cast<GameStateSelection*>(m_currentState.get())->getAttackList();
		m_currentState.reset();
		m_currentState = unique_ptr<GameState>( new GameStateLERP(mutantList, m_player));
		break;
	default:
		break;
	}

}
bool GameRules::keyPressed(const OIS::KeyEvent& e)
{
	m_currentState->keyPressed(e);
	return true;
}
bool GameRules::keyReleased(const OIS::KeyEvent& e)
{
	m_currentState->keyReleased(e);
	return true;
}