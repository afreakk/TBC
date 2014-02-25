#include "stdafx.h"
#include "PlayerHandlerStateSingleAttack.h"
#include "BehaviourStateLERP.h"
#include "MutantContainer.h"
#include "Mutant.h"
#include "Player.h"
#include "PlayerGlobalStats.h"
#include "LERPWalkAttack.h"
#include "LERPWalk.h"
#include "LaneSettings.h"


PlayerHandlerStateSingleAttack::PlayerHandlerStateSingleAttack( Player* player ,  std::string targetIndex)
: HandlerState(PLAYER_HANDLER_STATE::SINGLE_ATTACK)
, m_targetIndex(targetIndex)
, m_player(player)
, m_lerpState(new BehaviourStateLERP( MutantContainer::getSingleton().getMutant(m_targetIndex), 
&PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy(), new LERPWalkAttack()))
, m_currentTargetKilled(false)
, m_lerpingTowardsLane(false)
{
    m_player->setState(m_lerpState.get());
}


PlayerHandlerStateSingleAttack::~PlayerHandlerStateSingleAttack()
{
}

void PlayerHandlerStateSingleAttack::update()
{
	if (m_lerpState->nextTarget() && !m_lerpingTowardsLane)
	{
		setLerpToLane();
		m_lerpingTowardsLane = true;
	}
	else if (m_lerpingTowardsLane)
	{
		if (m_lerpState->nextTarget())
            m_state = PLAYER_HANDLER_STATE::NORMAL;
	}
	else
        handleMurder();
}
void PlayerHandlerStateSingleAttack::setLerpToLane()
{
	m_lerpState.reset();
    unsigned idx = LaneSettings::getSingleton().getClosestLane(m_player->getNode()->getPosition());
    Vector3 targetPos = LaneSettings::getSingleton().getVectorOf(idx, m_player->getPolarCoordinates().theta, m_player->getPolarCoordinates().h);
	m_lerpState = unique_ptr<BehaviourStateLERP>(new BehaviourStateLERP( nullptr, &PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy(), new LERPWalk(), targetPos ));
	m_player->setState(m_lerpState.get());
}
void PlayerHandlerStateSingleAttack::handleMurder()
{
	if (m_lerpState->enemyKilled() && !m_currentTargetKilled)
	{
		MutantContainer::getSingleton().killMutantPlayer(m_targetIndex);
		m_currentTargetKilled = true;
	}
}