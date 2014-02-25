#include "stdafx.h"
#include "PlayerHandlerStateMultiAttack.h"
#include "MutantContainer.h"
#include "PlayerGlobalStats.h"
#include "GlobalVariables.h"
#include "BehaviourStateLERP.h"
#include "Player.h"
#include "ModelHandler.h"
#include "LERPWalkAttack.h"
#include "LERPWalk.h"
#include "LaneSettings.h"
#include "CoreCompositor.h"

PlayerHandlerStateMultiAttack::PlayerHandlerStateMultiAttack(std::vector<std::string> mutantList, Player* player) 
: HandlerState(PLAYER_HANDLER_STATE::MULTI_ATTACK)
, m_attackList(mutantList)
, m_player(player)
, m_currentLerpState(nullptr)
, m_currentTargetIndex(m_attackList.begin())
, m_currentTargetKilled(false)
, m_lerpingTowardsLane(false)
{
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
	MutantContainer::getSingleton().registerSubscriber(this, "PlayerHandlerStateMultiAttack");
    setNewState();
    CoreCompositor::getSingleton().blackAndWhite(true);
}

PlayerHandlerStateMultiAttack::~PlayerHandlerStateMultiAttack()
{
    CoreCompositor::getSingleton().blackAndWhite(false);
	MutantContainer::getSingleton().removeSubscriber("PlayerHandlerStateMultiAttack");
	GlobalVariables::getSingleton().setSpeed(1.0);
}

void PlayerHandlerStateMultiAttack::setNextTarget()
{
	if ((m_currentTargetIndex+1) != m_attackList.end())
	{
        m_currentTargetIndex++;
		setNewState();
	}
	else if (!m_lerpingTowardsLane)
	{
		setNewState(getClosestLanePosition());
		m_lerpingTowardsLane = true;
	}
	else
	{
        m_state = PLAYER_HANDLER_STATE::NORMAL;
	}
}

Ogre::Vector3 PlayerHandlerStateMultiAttack::getClosestLanePosition()
{
    unsigned idx = LaneSettings::getSingleton().getClosestLane(m_player->getNode()->getPosition());
	return LaneSettings::getSingleton().getVectorOf(idx, m_player->getPolarCoordinates().theta, m_player->getPolarCoordinates().h);
}
void PlayerHandlerStateMultiAttack::setNewState( const Ogre::Vector3& targetPos)
{
	BehaviourObject* targetObject = nullptr;
	LERPBase* lerpConfiguration;
	if (targetPos == Vector3::ZERO)
	{
		if ((targetObject = MutantContainer::getSingleton().getMutant(*m_currentTargetIndex)) == nullptr)
		{
			setNextTarget();
			return;
		}
		lerpConfiguration = new LERPWalkAttack();
	}
	else
		lerpConfiguration = new LERPWalk();
    m_currentLerpState.reset();
    m_currentLerpState = unique_ptr<BehaviourStateLERP>{ 
		new BehaviourStateLERP(targetObject, &PlayerGlobalStats::getSingleton().getLERPSpeed_Energy(), lerpConfiguration, targetPos) };
    m_player->setState(m_currentLerpState.get());
}

void PlayerHandlerStateMultiAttack::notify(std::string victim)
{
	if (*m_currentTargetIndex == victim && !m_currentLerpState->enemyKilled())
		setNextTarget();
}
void PlayerHandlerStateMultiAttack::update()
{
	if (!m_currentTargetKilled && m_currentLerpState->enemyKilled())
	{
        MutantContainer::getSingleton().killMutantPlayer(*m_currentTargetIndex);
		m_currentTargetKilled = true;
	}
	else if (m_currentLerpState->nextTarget())
	{
		setNextTarget();
		m_currentTargetKilled = false;
	}
}
