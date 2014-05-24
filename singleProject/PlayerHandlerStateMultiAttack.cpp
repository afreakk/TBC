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
, m_teleporter(player)
{
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
	MutantContainer::getSingleton().registerSubscriber(this, "PlayerHandlerStateMultiAttack");
    setNewState(Vector3::ZERO);
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
		setNewState(Vector3::ZERO);
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
		new BehaviourStateLERP(true, targetObject, &PlayerGlobalStats::getSingleton().getLERPSpeed_Energy(), lerpConfiguration, targetPos) };
    m_player->setState(m_currentLerpState.get());
	if (targetObject != nullptr)
		m_teleporter.teleport( (m_player->getNode()->getPosition() - targetObject->getNode()->getPosition()).normalisedCopy()*200.0 + targetObject->getNode()->getPosition() );
	
}
void PlayerHandlerStateMultiAttack::notify(std::string victim) //victim got killed to set next target
{
	if (*m_currentTargetIndex == victim && !m_currentLerpState->enemyKilled())
		setNextTarget();
}
void PlayerHandlerStateMultiAttack::update()
{
	bool isTeleporting = m_teleporter.handleTeleport();
    m_currentLerpState->setPause(isTeleporting);
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
