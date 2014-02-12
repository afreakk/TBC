#include "stdafx.h"
#include "PlayerHandlerStateMultiAttack.h"
#include "MutantContainer.h"
#include "PlayerGlobalStats.h"
#include "GlobalVariables.h"
#include "BehaviourStateLERP.h"
#include "Player.h"
#include "ModelHandler.h"
PlayerHandlerStateMultiAttack::PlayerHandlerStateMultiAttack(std::vector<unsigned> mutantList, Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::MULTI_ATTACK)
, m_attackList(mutantList)
, m_player(player)
, m_listIndex(0)
, m_currentLerpState(nullptr)
{
	attackNextTarget();
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
}

PlayerHandlerStateMultiAttack::~PlayerHandlerStateMultiAttack()
{
	GlobalVariables::getSingleton().setSpeed(1.0);
	MutantContainer::getSingleton().removeKilledMutants();
}

void PlayerHandlerStateMultiAttack::goNormal()
{
	m_state = PLAYER_HANDLER_STATE::NORMAL;
}
void PlayerHandlerStateMultiAttack::attackNextTarget()
{
	if (m_listIndex < m_attackList.size())
	{
		SceneNode*const node = MutantContainer::getSingleton().getMutants()[m_attackList[m_listIndex]]->getModelHandler().getNode();
		m_currentLerpState.reset();
		m_currentLerpState = unique_ptr<BehaviourStateLERP>{ new BehaviourStateLERP(node, &PlayerGlobalStats::getSingleton().getLERPSpeed_Energy() ) };
		m_player->setState(m_currentLerpState.get());
		m_listIndex++;
	}
	else
		goNormal();
}

void PlayerHandlerStateMultiAttack::update()
{
	if (m_currentLerpState->nextTarget())
	{
		MutantContainer::getSingleton().killMutant(m_attackList[m_listIndex - 1]);
		attackNextTarget();
	}
}
void PlayerHandlerStateMultiAttack::keyPressed(const OIS::KeyEvent&)
{

}
void PlayerHandlerStateMultiAttack::keyReleased(const OIS::KeyEvent&)
{

}