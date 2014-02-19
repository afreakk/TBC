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
, m_currentTargetIndex(0)
, m_currentTargetKilled(false)
{
	setNextTarget();
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
	MutantContainer::getSingleton().compensateThis(&m_attackList);
}

PlayerHandlerStateMultiAttack::~PlayerHandlerStateMultiAttack()
{
	MutantContainer::getSingleton().unCompensateThis(&m_attackList);
	GlobalVariables::getSingleton().setSpeed(1.0);
}

void PlayerHandlerStateMultiAttack::setNextTarget()
{
	if (m_listIndex < m_attackList.size())
	{
		m_currentTargetIndex = m_attackList[m_listIndex++];
		SceneNode*const node = MutantContainer::getSingleton().getMutants()[ m_currentTargetIndex ]->getModelHandler().getNode();
		setNewState(node);
	}
	else
        m_state = PLAYER_HANDLER_STATE::NORMAL;
}

void PlayerHandlerStateMultiAttack::setNewState(Ogre::SceneNode* targetNode)
{
    m_currentLerpState.reset();
    m_currentLerpState = unique_ptr<BehaviourStateLERP>{ new BehaviourStateLERP(targetNode, &PlayerGlobalStats::getSingleton().getLERPSpeed_Energy() ) };
    m_player->setState(m_currentLerpState.get());
}

void PlayerHandlerStateMultiAttack::update()
{
	if (!m_currentTargetKilled && m_currentLerpState->enemyKilled())
	{
		killTarget(m_currentTargetIndex);
		m_currentTargetKilled = true;
	}
	if (m_currentLerpState->nextTarget())
	{
		setNextTarget();
		m_currentTargetKilled = false;
	}
}
void PlayerHandlerStateMultiAttack::killTarget(unsigned idx)
{
    MutantContainer::getSingleton().killMutantPlayer(idx);
}
void PlayerHandlerStateMultiAttack::keyPressed(const OIS::KeyEvent&)
{

}
void PlayerHandlerStateMultiAttack::keyReleased(const OIS::KeyEvent&)
{

}
