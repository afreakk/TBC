#include "stdafx.h"
#include "PlayerHandlerStateLERP.h"
#include "../Containers/MutantContainer.h"
PlayerHandlerStateLERP::PlayerHandlerStateLERP(std::vector<unsigned> mutantList, Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::LERP)
, m_mutantList(mutantList)
, m_player(player)
, m_mutantIndex(0)
, m_currentLerpState(nullptr)
{
	attackNextTarget();
}

PlayerHandlerStateLERP::~PlayerHandlerStateLERP()
{
}

void PlayerHandlerStateLERP::goNormal()
{
	m_state = PLAYER_HANDLER_STATE::NORMAL;
}
void PlayerHandlerStateLERP::attackNextTarget()
{
	if (m_mutantIndex < m_mutantList.size())
	{
		SceneNode*const node = MutantContainer::getSingleton().getMutants()[m_mutantList[m_mutantIndex]]->getModelHandler().getNode();
		m_currentLerpState.reset();
		m_currentLerpState = unique_ptr<BehaviourStateLERP>{ new BehaviourStateLERP(node) };
		m_player->setState(m_currentLerpState.get());
		m_mutantIndex++;
	}
	else
		goNormal();
}

void PlayerHandlerStateLERP::update()
{
	if (m_currentLerpState->nextTarget())
		attackNextTarget();
}
void PlayerHandlerStateLERP::keyPressed(const OIS::KeyEvent&)
{

}
void PlayerHandlerStateLERP::keyReleased(const OIS::KeyEvent&)
{

}