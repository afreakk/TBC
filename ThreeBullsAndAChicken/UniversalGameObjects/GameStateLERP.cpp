#include "stdafx.h"
#include "GameStateLERP.h"
#include "../Enemy/EnemyHandler.h"
GameStateLERP::GameStateLERP(std::vector<unsigned> mutantList, Player* player) : GameState(PLAYER_STATES::PlayerLERPState), m_mutantList(mutantList), m_player(player)
, m_mutantIndex(0)
{
	attackNextTarget();
}

GameStateLERP::~GameStateLERP()
{
}

void GameStateLERP::goNormal()
{
	m_state = PLAYER_STATES::PlayerNormalState;
	m_player->setState(PLAYER_STATES::PlayerNormalState);
}
void GameStateLERP::attackNextTarget()
{
	if (m_mutantIndex < m_mutantList.size())
	{
		Mutant& mutant = EnemyHandler::getSingleton().getMutantHandlers()[m_mutantList[m_mutantIndex]]->getMutant();
		SceneNode*const node = mutant.getModelHandler().getNode();
		m_currentLerpState = new PlayerLERPState(node);
		m_player->setState(m_currentLerpState);
		m_mutantIndex++;
	}
	else
		goNormal();
}

void GameStateLERP::update()
{
	if (m_currentLerpState->nextTarget())
		attackNextTarget();
}
void GameStateLERP::keyPressed(const OIS::KeyEvent&)
{

}
void GameStateLERP::keyReleased(const OIS::KeyEvent&)
{

}