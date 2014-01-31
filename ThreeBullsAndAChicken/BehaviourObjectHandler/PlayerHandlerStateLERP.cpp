#include "stdafx.h"
#include "PlayerHandlerStateLERP.h"
#include "../Containers/MutantContainer.h"
#include "../Stats/PlayerGlobalStats.h"
#include "../Stats/GlobalVariables.h"
PlayerHandlerStateLERP::PlayerHandlerStateLERP(std::vector<unsigned> mutantList, Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::LERP)
, m_attackList(mutantList)
, m_player(player)
, m_listIndex(0)
, m_currentLerpState(nullptr)
{
	attackNextTarget();
	GlobalVariables::getSingleton().setSpeed(1.0 / 20.0);
}

PlayerHandlerStateLERP::~PlayerHandlerStateLERP()
{
	GlobalVariables::getSingleton().setSpeed(1.0);
	MutantContainer::getSingleton().removeKilledMutants();
}

void PlayerHandlerStateLERP::goNormal()
{
	m_state = PLAYER_HANDLER_STATE::NORMAL;
}
void PlayerHandlerStateLERP::attackNextTarget()
{
	if (m_listIndex < m_attackList.size())
	{
		SceneNode*const node = MutantContainer::getSingleton().getMutants()[m_attackList[m_listIndex]]->getModelHandler().getNode();
		m_currentLerpState.reset();
		m_currentLerpState = unique_ptr<BehaviourStateLERP>{ new BehaviourStateLERP(node, &PlayerGlobalStats::getSingleton().getLERPSpeed() ) };
		m_player->setState(m_currentLerpState.get());
		m_listIndex++;
	}
	else
		goNormal();
}

void PlayerHandlerStateLERP::update()
{
	if (m_currentLerpState->nextTarget())
	{
		MutantContainer::getSingleton().killMutant(m_attackList[m_listIndex - 1]);
		attackNextTarget();
	}
}
void PlayerHandlerStateLERP::keyPressed(const OIS::KeyEvent&)
{

}
void PlayerHandlerStateLERP::keyReleased(const OIS::KeyEvent&)
{

}